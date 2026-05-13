function [ Aj, bj ] = buildConstrJerk( ctx, windowCurv, coeff, jmax, ...
                    BasisVal, BasisValD, BasisValDD, u_vec )
%#codegen
% buildConstrJerk : 构建进给率 LP 问题中的跃度（Jerk）不等式约束矩阵
%
% ═══════════════════════════════════════════════════════════════════════════
% 【与 buildConstr 的分工】
%
%   buildConstr    构建速度约束 + 加速度约束（线性，第一阶段 LP）
%   buildConstrJerk 构建跃度约束（线性化，第二阶段 LP）
%
%   两阶段策略：
%     第一阶段（无跃度约束）→ 得到初始解 coeff₀
%     第二阶段（在 coeff₀ 处线性化跃度）→ 在第一阶段解附近施加跃度约束
%   这样将非线性跃度约束拆成两次线性 LP，保持问题可解性。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【跃度的链式法则推导】
%
%   LP 决策变量：x_k ∈ R^N，满足
%       w(u) = dot{u}² = B(u)·x_k   （参数速度平方，B 样条展开）
%
%   记 f  = B(u)·x，  f' = B'(u)·x，  f'' = B''(u)·x
%      v  = sqrt(f)   （参数速度，标量）
%
%   对参数导数 dot{u}, ddot{u}, dddot{u} 由链式法则（calcUfromQ）：
%       dot{u}   = sqrt(f)          = v
%       ddot{u}  = f'  / 2          （一阶导：d(v)/dt = f'/(2v)·v = f'/2）
%       dddot{u} = f'' / 2 · v      （二阶导：d(f'/2)/dt = f''/(2)·dot{u} = f''v/2）
%
%   第 j 轴的笛卡尔加速度（参考 buildConstr 推导）：
%       a_j = r''_j·f + 0.5·r'_j·f'
%
%   对 a_j 再对时间 t 求导，得第 j 轴跃度：
%       jerk_j = d(a_j)/dt
%              = d/dt[ r''_j·f + 0.5·r'_j·f' ]
%
%   展开（注意 r'_j, r''_j 是 u 的函数，需再用链式法则）：
%       d(r''_j·f)/dt  = r'''_j·dot{u}·f + r''_j·f'·dot{u}
%                      = r'''_j·v·f       + r''_j·v·f'
%       d(0.5·r'_j·f')/dt = 0.5·r''_j·dot{u}·f' + 0.5·r'_j·f''·dot{u}
%                         = 0.5·r''_j·v·f'        + 0.5·r'_j·v·f''
%
%   合并（r''_j·v·f' 出现两次）：
%       jerk_j = v · [ r'''_j·f + (1 + 0.5)·r''_j·f' + 0.5·r'_j·f'' ]
%              = v · [ r'''_j·f + 1.5·r''_j·f'        + 0.5·r'_j·f'' ]
%
%   用 B 样条展开替换 f, f', f''：
%       jerk_j = v · [ r'''_j·B(u) + 1.5·r''_j·B'(u) + 0.5·r'_j·B''(u) ] · x_k
%              = Jerk_j(u) · x_k
%
%   其中 v = sqrt( B(u)·coeff_k )（用第一阶段解 coeff 在当前点求 v，视为常数）
%   → 跃度关于 x_k 是线性的，可以直接加入 LP。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【约束形式】
%
%   上限：Jerk_j · x_k ≤  jmax_j    （jerk_j ≤  jmax_j）
%   下限：-Jerk_j · x_k ≤  jmax_j   （jerk_j ≥ -jmax_j）
%
%   每段曲线，每个离散点，每个轴，各有 2 行约束（正/负各一）：
%   Aj 总行数 = 2 × Ndim × M × Nwindow
%   Aj 总列数 = N × Nwindow（与 buildConstr 的 A 相同）
%
%   Aj 与 buildConstr 的 A 行数对比：
%     A  行数 = (2 + 2×Ndim) × M × Nwindow  （速度 + 加速度）
%     Aj 行数 =  2×Ndim      × M × Nwindow  （仅跃度）
%   二者在 FeedratePlanning_LP 中垂直拼接为完整约束矩阵。
%
% ═══════════════════════════════════════════════════════════════════════════
% Inputs :
%   ctx        : 计算链上下文（cfg.NumberAxis / cfg.maskTot / kin 等）
%   windowCurv : 滑动窗口内的曲线数组（长度 Nwindow）
%   coeff      : 第一阶段 LP 的解，[N × Nwindow]（用于在此处线性化 v=sqrt(f)）
%   jmax       : 各轴最大允许跃度（完整 6 轴向量）
%   BasisVal   : [M × N] B 样条基函数值（在 u_vec 各点预计算）
%   BasisValD  : [M × N] B 样条基函数一阶导数值
%   BasisValDD : [M × N] B 样条基函数二阶导数值
%   u_vec      : [1 × M] 离散化参数向量 [0,1]
%
% Outputs :
%   Aj : [2·Ndim·M·Nwindow  ×  N·Nwindow] 跃度不等式约束矩阵（块对角）
%   bj : [2·Ndim·M·Nwindow  ×  1]         约束右端（各轴 jmax 重复排列）

c_prof_in(mfilename);

% ── 维度定义 ─────────────────────────────────────────────────────────────
Ndim        = ctx.cfg.NumberAxis;   % 激活轴数
Nwindow     = length( windowCurv ); % 窗口内曲线段数
[ M, N ]    = size( BasisVal );     % M: 离散点数, N: 每段基函数数
Nx          = N * Nwindow;          % 决策变量总数
Nc          = 2 * Ndim;             % 每点约束行数：正向 Ndim 行 + 负向 Ndim 行

% ── 预分配 ──────────────────────────────────────────────────────────────
Aj          = zeros( Nc * M * Nwindow, Nx );
bj          = zeros( Nc * M * Nwindow, 1 );

jmaxTot     = jmax( ctx.cfg.maskTot );  % 提取激活轴的 jmax
% b_jmax：将各轴 jmax 重复 M 次，与 Jerk 矩阵行数对齐
% 布局：[轴1的M行 jmax₁; 轴2的M行 jmax₂; ...; 轴Ndim的M行 jmaxₙ]
b_jmax      = repmat( jmaxTot, M, 1 );

% Jerk：当前段的跃度约束矩阵，[M·Ndim × N]
%   行 (j-1)*M+1 ~ j*M  对应第 j 轴在 M 个点处的跃度系数行
Jerk        = zeros( M * Ndim, N );

for k = 1 : Nwindow

    % ── 步骤 1：在 u_vec 各点处求曲线的位置和各阶参数导数 ────────────────
    %   r0D : [Ndim×M] 位置
    %   r1D : [Ndim×M] 一阶参数导数 r'(u)  （切线方向）
    %   r2D : [Ndim×M] 二阶参数导数 r''(u） （曲率相关）
    %   r3D : [Ndim×M] 三阶参数导数 r'''(u）（跃度推导所需）
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );

    % ── 步骤 2：更新刀具长度补偿（影响运动学变换）───────────────────────
    ctx.kin = ctx.kin.set_tool_length( -windowCurv( k ).tool.offset.z );

    % ── 步骤 3：五轴联动坐标变换（TRAFO=true 时）─────────────────────────
    % 将笛卡尔空间的 r1D/r2D/r3D 变换到关节空间，
    % 使跃度约束直接作用于关节轴（A/B/C 轴跃度），而非笛卡尔空间
    if( windowCurv( k ).Info.TRAFO )
        [ ~, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
    end

    % ── 步骤 4：逐轴构建跃度系数矩阵 Jerk ───────────────────────────────
    %
    % 【公式回顾】
    %   jerk_j(u) = v(u) × [ r'''_j·B(u) + 1.5·r''_j·B'(u) + 0.5·r'_j·B''(u) ] · x_k
    %
    % v(u) = sqrt( B(u)·coeff_k )：在当前迭代解 coeff_k 处求速度（视为已知常数）
    %   → mysqrt 做安全开方（避免 q<0 时出现复数）
    %
    % 对 M 个离散点同时计算（向量化）：
    %   r3D(j,:)  [1×M]' = [M×1]，与 BasisVal  [M×N] 逐行广播（.*）→ [M×N]
    %   r2D(j,:)  [1×M]' 同理
    %   r1D(j,:)  [1×M]' 同理
    %   mysqrt(BasisVal*coeff(:,k))  [M×1]：第 k 段在各点的速度
    %   最终 Jerk(ind,:) = [M×N]，每行是该轴该点处跃度关于 x_k 的线性系数
    for j = 1 : Ndim
        ind = int32( 1 : M ) + ( j - 1 ) * M;  % 第 j 轴在 Jerk 中的行范围
        Jerk( ind, : ) = ( r3D( j, : ).'   .* BasisVal    ...  % r'''_j · B(u)
                       + 1.5 * r2D( j, : ).' .* BasisValD  ...  % 1.5·r''_j · B'(u)
                       + 0.5 * r1D( j, : ).' .* BasisValDD ) ...% 0.5·r'_j · B''(u)
                       .* mysqrt( BasisVal * coeff( :, k ) );    % × v(u)（线性化系数）
    end

    % ── 步骤 5：装配到全局约束矩阵 ─────────────────────────────────────
    %
    % Aj 是块对角矩阵，与 buildConstr 的 A 结构相同：
    %   第 k 段占行 indAL，列 indAC，其他位置为 0
    %
    % 每段的约束块（2·Ndim·M 行 × N 列）：
    %   上半（Ndim·M 行）：  Jerk · x_k ≤  jmax   （正向，jerk_j ≤  jmax_j）
    %   下半（Ndim·M 行）： -Jerk · x_k ≤  jmax   （负向，jerk_j ≥ -jmax_j）
    indAL = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
    indAC = int32( 1 : N )      + ( k - 1 ) * N;
    Aj( indAL, indAC ) = [  Jerk; -Jerk ];
    bj( indAL )        = [ b_jmax(:); b_jmax(:) ];
end

% 数值有效性检查：NaN 会导致 LP 求解器内部失败，提前拦截
checkValidity( Aj, bj );

c_prof_out(mfilename);
end

function checkValidity( A, b )
% checkValidity : 断言约束矩阵与右端向量中不含 NaN
ocn_assert( ~any( isnan( A ), 'all' ), "A has NaN", mfilename );
ocn_assert( ~any( isnan( b ), 'all' ), "b has NaN", mfilename );
end
