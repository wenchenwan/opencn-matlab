function [ Aj, bj ] = buildConstrJerk( ctx, windowCurv, coeff, jmax, ...
                    BasisVal, BasisValD, BasisValDD, u_vec )
%#codegen
% buildConstrJerk : 构建进给速度优化 LP 问题中的跃度（Jerk）不等式约束
%
% 【LP 优化变量与目标】
%   进给速度优化将速度平方 v²(u) 表示为 B 样条基函数的线性组合：
%     v²(u) = BasisVal(u) · x_k        (x_k = 第 k 段曲线的决策变量)
%
%   决策变量 x = [x_1; x_2; ...; x_Nwindow]（所有窗口曲线的系数拼接）
%   每个 x_k 是长度 N 的列向量（N 个 B 样条节点处的 v² 值）
%
% 【跃度约束的推导】
%   跃度（Jerk）是加速度对时间的导数，第 j 轴的跃度为 d³r_j/dt³。
%   用链式法则从路径参数 u → 时间 t 展开：
%     设 f = v²(u) = BasisVal · x_k
%     f'  = dv²/du = BasisValD  · x_k
%     f'' = d²v²/du² = BasisValDD · x_k
%     v   = sqrt(f)（速度）
%
%   第 j 轴跃度（离散点处的线性化近似）：
%     jerk_j ≈ [r'''_j · f + 1.5·r''_j · f' + 0.5·r'_j · f''] · v
%            = [r3D_j·BasisVal + 1.5·r2D_j·BasisValD + 0.5·r1D_j·BasisValDD] · x_k · v
%
%   其中 v = sqrt(BasisVal · coeff)（用当前迭代点处的 v 值线性化）。
%   这将跃度表达为关于决策变量 x_k 的线性函数，构成 LP 可用的不等式约束：
%     Jerk_k · x_k ≤ jmax_j  （正向约束）
%    -Jerk_k · x_k ≤ jmax_j  （负向约束）
%
% 【五轴联动坐标变换】
%   若曲线标记了 TRAFO（需要运动学变换），在计算跃度前将笛卡尔导数
%   变换到关节空间（ctx.kin.joint），约束直接作用于关节轴跃度。
%
% Inputs :
%   ctx        : 计算链上下文（含 cfg.NumberAxis / cfg.maskTot / kin 等）
%   windowCurv : 滑动窗口内的曲线数组（长度 = Nwindow）
%   coeff      : 当前迭代点的 B 样条系数矩阵 [N × Nwindow]（用于计算 v=sqrt(f)）
%   jmax       : 各轴最大允许跃度向量（全轴）
%   BasisVal   : B 样条基函数值矩阵 [M × N]（在 u_vec 各点处预计算）
%   BasisValD  : B 样条基函数一阶导矩阵 [M × N]
%   BasisValDD : B 样条基函数二阶导矩阵 [M × N]
%   u_vec      : 离散参数向量（长度 M，均匀分布在 [0,1] 内）
%
% Outputs :
%   Aj : 跃度不等式约束矩阵 [2·Ndim·M·Nwindow × N·Nwindow]
%   bj : 跃度不等式约束右端向量（对应各轴 jmax 的重复排列）
%

c_prof_in(mfilename);

% Ndim    : 激活轴数量（Number of dimensions）
% Nwindow : 滑动窗口内的曲线段数
Ndim        = ctx.cfg.NumberAxis;
Nwindow     = length( windowCurv );

% M : 离散化采样点数（= length(u_vec)）
% N : 每段曲线的 B 样条系数数量（= 决策变量维数/段）
% Nx : 总决策变量数（所有窗口曲线系数拼接）
% Nc : 每个采样点处的约束数（正/负各一，共 2·Ndim 个不等式）
[ M, N ]    = size( BasisVal );
Nx          = N * Nwindow;
Nc          = 2 * Ndim;   % 正向 + 负向约束

% Aj, bj : 跃度约束矩阵与右端向量（全零预分配，逐段填入）
Aj          = zeros( Nc * M * Nwindow,  Nx );
bj          = zeros( Nc * M * Nwindow,  1 );

% jmaxTot : 仅保留激活轴的 jmax（与 Ndim 维对齐）
% b_jmax  : 每个采样点处的 jmax 列向量（重复 M 次，长度 M·Ndim）
jmaxTot     = jmax( ctx.cfg.maskTot );
b_jmax      = repmat( jmaxTot, M, 1 );

% Jerk : 跃度约束矩阵（当前曲线，[M·Ndim × N]）
%   Jerk(ind_j, :) 是第 j 轴在 M 个采样点处的跃度行向量
Jerk         = zeros( M * Ndim , N );

for k = 1 : Nwindow
    % ── 步骤 1：计算曲线导数 ─────────────────────────────────────────────
    % 在 u_vec 各点处求曲线的位置和各阶参数导数（对局部参数 u 的导数）
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );

    % ── 步骤 2：更新运动学变换（刀具长度补偿）───────────────────────────
    ctx.kin = ctx.kin.set_tool_length( -windowCurv( k ).tool.offset.z );

    % ── 步骤 3：五轴联动坐标变换（若需要）──────────────────────────────
    % TRAFO=true 时将笛卡尔空间导数变换到关节空间，跃度约束作用于关节轴
    if( windowCurv( k ).Info.TRAFO )
        [ ~, r1D, r2D, r3D ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
    end

    % ── 步骤 4：逐轴构建跃度矩阵 ────────────────────────────────────────
    for j = 1 : Ndim
        ind = int32( 1 : M ) + ( j - 1 ) * M ;   % 第 j 轴对应的行索引
        % Jerk_j = [r'''_j·BasisVal + 1.5·r''_j·BasisValD + 0.5·r'_j·BasisValDD] · v
        % 其中 v = sqrt(BasisVal * coeff(:,k))（当前迭代点的速度，逐采样点列向量）
        % 这将跃度线性化为关于 x_k 的线性函数（v 视为已知常数）
        Jerk( ind, : ) = ( r3D( j, : ).' .* BasisVal + 1.5 * r2D( j, : ).' ...
                        .* BasisValD + 0.5 * r1D( j, : ).' .* BasisValDD ) ...
                        .* mysqrt( BasisVal * coeff( :, k ) );
    end

    % ── 步骤 5：装配全局约束矩阵 ────────────────────────────────────────
    % indAL : 当前曲线对应的约束行索引（正向 + 负向，各 M·Ndim 行）
    % indAC : 当前曲线对应的决策变量列索引（N 列）
    indAL   = int32( 1 : Nc * M )   + ( k - 1 ) * Nc * M;
    indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
    % 正向约束：Jerk * x_k ≤ jmax
    % 负向约束：-Jerk * x_k ≤ jmax（等价于 jerk_j ≥ -jmax）
    Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
    bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
end

% 数值有效性检查：约束矩阵不得含 NaN
checkValidity( Aj, bj );

c_prof_out(mfilename);

end

function checkValidity( A, b )
% 断言约束矩阵与右端向量中不含 NaN（NaN 会导致 LP 求解器失败）
ocn_assert( ~any( isnan( A ) , 'all' ), "A has NaN", mfilename );
ocn_assert( ~any( isnan( b ) , 'all' ), "b has NaN", mfilename );
end
