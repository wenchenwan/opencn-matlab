function [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, windowCurv, amax, ...
    v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec )
%#codegen
% buildConstr : 为进给率优化 LP 问题构建完整约束矩阵
%
% ═══════════════════════════════════════════════════════════════════════════
% 【LP 问题结构】
%
%   决策变量 x ∈ R^(N × Nwindow)：
%     x(:,k) = 第 k 段曲线的 B 样条系数向量（N 维）
%     物理含义：x(k)(u) ≈ w(u) = ud²(u)，即参数速度的平方
%
%     注意：w(u) = ud² 不等于物理速度平方 v²(u)，二者关系：
%       v²(u) = |r'(u)|² × ud²(u)
%     用 ud² 而非 v² 作为决策变量，是因为加速度约束可以写成线性形式。
%
%   目标函数（FeedratePlanning_LP 中定义）：
%     最大化 Σ_k ∫ w_k(u) du ≈ 最大化 Σ ud²，等价于最小化加工时间
%
% ═══════════════════════════════════════════════════════════════════════════
% 【约束分类与维度】
%
%   符号约定：
%     M       = 每段离散点数（u_vec 的长度）
%     N       = 每段 B 样条基函数个数（= 系数个数）
%     Nwindow = 窗口内的曲线段数
%     Ndim    = 激活轴数（= NumberAxis）
%     Nx      = N × Nwindow（决策变量总维度）
%
%   ┌─────────────────────────────────────────────────────────────────────┐
%   │  不等式约束 A·x ≤ b                                                  │
%   │                                                                     │
%   │  每段在 M 个离散点处各有 Nc = 2 + 2×Ndim 行约束：                     │
%   │    行组 1（1 行 × M 点）: 速度上限   v² ≤ f_max                       │
%   │    行组 2（1 行 × M 点）: 速度非负  -v² ≤ 0                           │
%   │    行组 3（Ndim 行× M 点）: 加速度上限  a_k ≤ a_max_k                  │
%   │    行组 4（Ndim 行× M 点）: 加速度下限 -a_k ≤ a_max_k（即 a_k ≥ -max）  │
%   │                                                                     │
%   │  A 尺寸：(Nc × M × Nwindow) × Nx                                    │
%   │  A 是块对角结构：第 k 段的约束只涉及 x(:,k)                             │
%   │                                                                     │
%   │  等式约束 Aeq·x = beq                                                │
%   │                                                                     │
%   │  Nec = 2 × (Nwindow + 1) 行：                                       │
%   │    行 1~2   : 窗口起端边界（v²=v_0²，切向加速度=at_0）                  │
%   │    行 3~4   : 段1末端 = 段2起端（速度²连续，切向加速度连续）              │
%   │    行 5~6   : 段2末端 = 段3起端                                        │
%   │    ...                                                               │
%   │    行 end-1~end : 窗口末端边界（v²=v_1²，切向加速度=at_1）              │
%   └─────────────────────────────────────────────────────────────────────┘
%
% ═══════════════════════════════════════════════════════════════════════════
% Inputs :
%   ctx        : 上下文（NumberAxis、vmax、maskTot、indCart、kin 等）
%   windowCurv : 优化窗口内曲线数组（长度 Nwindow）
%   amax       : 各轴最大加速度（完整 6 轴向量，用 maskTot 选出激活轴）
%   v_0 / v_1  : 窗口起/末端速度边界（速度范数，标量）
%   at_0/at_1  : 窗口起/末端切向加速度边界（标量）
%   BasisVal   : [M×N] 在 u_vec 处的 B 样条基函数值（用于 w(u) = B(u)·x）
%   BasisValD  : [M×N] 在 u_vec 处的 B 样条基函数一阶导数（用于 dw/du）
%   u_vec      : [1×M] 离散化参数向量 [0,1]
%
% Outputs :
%   A, b        : 不等式约束矩阵和右端向量
%   Aeq, beq    : 等式约束矩阵和右端向量
%   continuity  : [2×N] 最后一段（段1）末端的连续性行（v²行 + 切向加速度行）
%                 供 FeedratePlanning_LP 提取下一窗口的 v_0/at_0 边界条件

c_prof_in(mfilename); % 性能计时开始

% ── 维度定义 ─────────────────────────────────────────────────────────────
Ndim        = ctx.cfg.NumberAxis;     % 激活轴数（如 5 轴机为 5）
Nwindow     = length( windowCurv );   % 当前窗口曲线段数
[ M, N ]    = size( BasisVal );       % M: 离散点数, N: 每段基函数数
Nx          = N * Nwindow;            % 决策变量总数 = N × Nwindow
Nc          = ( 2 + 2 * Ndim );       % 每个离散点的不等式约束行数
                                      %   2 = 速度上限 + 速度非负
                                      %   2*Ndim = 各轴加速度上限 + 下限
Nec         = 2 * ( Nwindow + 1 );    % 等式约束总行数
                                      %   (Nwindow+1) 个连接点（含两端边界）
                                      %   每个连接点 2 行（v² 连续 + at 连续）

% ── 预分配约束矩阵 ───────────────────────────────────────────────────────
A           = zeros( Nc * M * Nwindow, Nx );  % 不等式约束矩阵（块对角）
b           = zeros( Nc * M * Nwindow, 1 );   % 不等式约束右端向量
Aeq         = zeros( Nec, Nx );               % 等式约束矩阵（带状结构）
beq         = zeros( Nec, 1 );                % 等式约束右端向量
amaxTot     = amax( ctx.cfg.maskTot );        % 提取激活轴的加速度上限
b_amax      = repmat( amaxTot, M, 1 );        % [M×Ndim → M*Ndim × 1]，广播到所有离散点

% ── 工作变量 ────────────────────────────────────────────────────────────
at_norm     = zeros( 2, N, Nwindow );    % [起/末端 × N × Nwindow] 切向加速度约束行
t_vec       = zeros( Ndim, 2, Nwindow ); % [Ndim × 起/末端 × Nwindow] 切线单位向量
v2_vec      = zeros( 2, N, Nwindow );    % [起/末端 × N × Nwindow] 速度²约束行
Acc         = zeros( M * Ndim, N, 2 );   % 加速度约束矩阵（两种坐标系：关节/笛卡尔）

% indAT：从 Acc 中提取起端（第 1 行）和末端（第 M 行）的行索引
%   Acc 的行排列：[轴1的M行, 轴2的M行, ..., 轴Ndim的M行]
%   轴 j 的起端行 = (j-1)*M + 1，末端行 = j*M
%   indAT(1, :) → 各轴的第 1 行（起端），indAT(2, :) → 各轴的第 M 行（末端）
indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );

% mask_continuity：连续性等式的符号约定
%   等式：[前段末端行] - [后段起端行] = 0
%   在 Aeq 中通过 +=（符号相反的两次叠加）实现：
%     前段末端 +1（v²行, at行）
%     后段起端 -1（v²行, at行）
mask_continuity = [ 1; 1; -1; -1 ];

v_max       = zeros( Ndim + 1, M );   % 速度上限矩阵（Ndim 轴限制 + 1 编程进给率限制）

% ════════════════════════════════════════════════════════════════════════
% 主循环：逐段构建约束
% ════════════════════════════════════════════════════════════════════════
for k = 1 : Nwindow

    % 在 u_vec 处求当前曲线的几何导数（对参数 u 求导，0~3 阶）
    %   r0D : [Ndim × M] 位置
    %   r1D : [Ndim × M] 一阶导数（切线方向，未归一化）
    %   r2D : [Ndim × M] 二阶导数（曲率相关）
    %   r3D : [Ndim × M] 三阶导数（跃度相关，buildConstr 内未直接使用）
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec ); %u_vec 1*M
    ctx.kin = ctx.kin.set_tool_length( -windowCurv( k ).tool.offset.z );

    if( windowCurv( k ).Info.TRAFO )
        % ── 运动学变换模式（TRAFO=true，5 轴机，工件坐标模式）─────────────
        %
        % G 代码坐标系：TRAFO=true 时，G 代码中的 (X,Y,Z) 已是刀尖在工件坐标
        %   系中的笛卡尔位置，(A/B/C) 是刀轴方向角。
        %   → EvalCurvStruct 读出的 r1D 已经是工件坐标下的笛卡尔导数。
        %
        % 进给率约束（F 指令）：F 指定刀尖路径速度，定义在工件坐标系中，
        %   r1D 本身已是工件坐标导数，vecnorm(r1D) 直接给出路径速度方向模长。
        %   → r1D_r = r1D （无需额外变换）
        %
        % 加速度/跃度约束：机床驱动器的 amax/jmax 作用于各关节轴的物理运动。
        %   五轴机的旋转轴（B/C）导致笛卡尔运动与关节运动存在耦合，
        %   必须通过逆雅可比将工件坐标导数映射到关节空间：
        %     v_joint  = J_jt(q) × v_cart          （一阶：逆雅可比）
        %     a_joint  = J_jt×a_cart + dJ_jt/dt×v_cart （二阶：含雅可比时间导数）
        %   ctx.kin.joint 封装了上述变换（同时处理 1~3 阶导数）。
        %   → r1D_a, r2D_a 是关节空间下的等效导数，用于 Acc 矩阵
        [ ~, r1D_a, r2D_a ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
        r1D_r = r1D; % 进给率约束直接用工件坐标导数
    else
        % ── 关节坐标模式（TRAFO=false，3 轴机或关节坐标编程）─────────────
        %
        % G 代码坐标系：TRAFO=false 时，G 代码中的 (X,Y,Z,B,C) 是机床各关节
        %   轴的运动量（关节坐标），不是刀尖在工件坐标系中的位置。
        %   → EvalCurvStruct 读出的 r1D 各行是各关节轴对参数 u 的导数（关节速度方向）。
        %
        % 加速度/跃度约束：约束天然在关节空间中，r1D/r2D 无需变换。
        %   → r1D_a = r1D, r2D_a = r2D （直接复用）
        %
        % 进给率约束（F 指令）：F 指定刀尖在工件坐标系中的路径速度，
        %   但 r1D 是关节空间导数，不能直接取 vecnorm 得路径速度。
        %   需要通过正运动学雅可比将关节速度映射到刀尖工具空间速度：
        %     v_tool = J_tj(q) × v_joint    （5×5 正雅可比，由符号工具箱自动生成）
        %   J_tj 包含 cos(B)/sin(B)/cos(C)/sin(C) 和机床几何偏置项，
        %   当旋转轴 B/C 处于非零角度时，关节运动与刀尖工件坐标运动不等比。
        %   ctx.kin.v_relative 封装了逐点计算 J_tj × r1D 的操作。
        %   → r1D_r = v_relative(r0D, r1D)：刀尖相对工件坐标的实际速度方向
        [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
        r1D_a     = r1D;   % 关节空间导数直接用于加速度约束
        r2D_a     = r2D;
    end
    %
    % 三个导数变量的后续用途汇总：
    %   r1D_r → 编程进给率速度上限（F 指令，vecnorm 取工件坐标路径速度模长）
    %   r1D_a → 各轴速度上限（vmax）+ 加速度约束矩阵 Acc(:,:,1)
    %   r1D   → 连续性等式约束 Acc(:,:,2)（始终笛卡尔/工件坐标，几何连续性无关坐标系）

    % 切线单位向量（起端和末端）：用于切向加速度的投影
    %   t = r'(u) / |r'(u)|，在起端（u=0）和末端（u=1）各取一个
    normR1D = vecnorm( r1D );
    t_vec( :, :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );

    % ── 约束组 1：速度上限 ───────────────────────────────────────────────
    % 约束形式：w(u) ≤ f_max(u)
    %   其中 w = ud²（参数速度平方），f_max = min(v_axis_max²/|r'_axis|²)
    %
    % 推导：每轴速度约束 |v_j| ≤ vmax_j 等价于
    %   |r'_j(u)| × ud ≤ vmax_j
    %   ud² ≤ (vmax_j / r'_j(u))²  = f_max_j(u)
    %
    % v_max 行：各轴限制（Ndim 行）+ 编程进给率限制（1 行）
    v_max( 1 : Ndim, : ) = ( ctx.cfg.vmax( ctx.cfg.maskTot ).'./ r1D_a ).^2;

    % 编程进给率约束：F（G-code 指令进给率）作用于笛卡尔路径线速度
    %   |v_cart| = vecnorm(r1D_r_cart × ud) ≤ F
    %   ud² ≤ (F / vecnorm(r1D_r_cart))²
    v_max( end, : ) = ( windowCurv( k ).Info.FeedRate ./ ...
        vecnorm( r1D_r( ctx.cfg.indCart, : ) ) ).^2;

    % 取所有速度上限中最紧的一个（逐点取最小值）
    f_max = min( v_max, [], 1 );  % [1 × M]

    % ── 约束组 3/4：加速度约束矩阵 Acc ──────────────────────────────────
    % 加速度的链式法则（笛卡尔空间，对时间 t 求导）：
    %   a_j(t) = d²r_j/dt² = r''_j(u)·ud² + r'_j(u)·udd
    %
    % 其中：
    %   w = ud² = B(u)·x          （决策变量的 B 样条展开）
    %   dw/du = ud²'(u) = B'(u)·x （对 u 求导，利用 B 样条微分性质）
    %   由 udd = (dw/du) / (2·ud) = (B'(u)·x) / (2·sqrt(B(u)·x))，
    %   但 LP 需要线性约束，故直接用 w 表达：
    %     r'_j(u)·udd = r'_j(u) × (dw/du)/(2ud)
    %   近似为：
    %     a_j ≈ r''_j(u)·w + 0.5·r'_j(u)·(dw/du)
    %         = r''_j(u)·(B(u)·x) + 0.5·r'_j(u)·(B'(u)·x)
    %         = [r''_j(u)·BasisVal + 0.5·r'_j(u)·BasisValD] · x
    %         = Acc_j · x
    %
    % Acc 尺寸：[M×Ndim × N × 2]
    %   第三维 1：用于不等式约束（r1D_a / r2D_a，关节或笛卡尔坐标）
    %   第三维 2：用于等式约束中的切向加速度（r1D / r2D，原始笛卡尔坐标）
    for j = 1 : Ndim
        ind = int32( 1 : M ) + ( j - 1 ) * M;
        % 第三维 1：用于不等式约束，轴上的加速度约束
        Acc( ind, :, 1 ) = r2D_a( j, : )' .* BasisVal + 0.5 * r1D_a( j, : )' .* BasisValD;
        % 第三维 2：用于连续性等式（切向加速度投影，在原始笛卡尔坐标下计算）【原始笛卡尔空间下的加速度】
        Acc( ind, :, 2 ) = r2D( j, : )'   .* BasisVal + 0.5 * r1D( j, : )'   .* BasisValD;
    end

    % ── 组装第 k 段的不等式约束块 ────────────────────────────────────────
    %
    % A 是块对角矩阵，第 k 段的约束块占：
    %   行：indAL = [(k-1)×Nc×M + 1] 到 [k×Nc×M]
    %   列：indAC = [(k-1)×N + 1] 到 [k×N]
    %
    % 块结构（行从上到下）：
    %   ┌─────────────────────────────────────────────────────────────┐
    %   │ 行 1     ~ M      :  BasisVal       ≤  f_max'   （速度上限） │
    %   │ 行 M+1   ~ 2M     : -BasisVal       ≤  0        （速度非负） │
    %   │ 行 2M+1  ~ 2M+M*Ndim  :  Acc(:,:,1)≤  b_amax   （加速度上）  │
    %   │ 行 2M+M*Ndim+1 ~ end : -Acc(:,:,1) ≤  b_amax   （加速度下）  │
    %   └─────────────────────────────────────────────────────────────┘
    % Nc = ( 2 + 2 * Ndim )
    indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
    indAC   = int32( 1 : N )      + ( k - 1 ) * N;
    A( indAL, indAC ) = [ BasisVal; -BasisVal; Acc(:,:,1); -Acc(:,:,1) ];
    b( indAL )        = [ f_max'; zeros( size(f_max) )';
                          b_amax(:); b_amax(:) ];

    % ── 构建段间连续性等式约束 ────────────────────────────────────────────
    %
    % 等式约束 Aeq 的结构（Nec 行 = 2×(Nwindow+1) 行）：
    %
    %   行编号规律：第 k 段对应行 [(k-1)×2+1] ~ [k×2+2]（起端 + 末端各 2 行）
    %   具体通过 indAEL = [1:4] + (k-1)×2 寻址：
    %     indAEL(1) = (k-1)*2+1 → 第 k 段起端的 v² 行
    %     indAEL(2) = (k-1)*2+2 → 第 k 段起端的 at 行
    %     indAEL(3) = (k-1)*2+3 → 第 k 段末端的 v² 行（= 第 k+1 段起端）
    %     indAEL(4) = (k-1)*2+4 → 第 k 段末端的 at 行（= 第 k+1 段起端）
    %
    % continuity = [v²_start; at_start; v²_end; at_end]（4×N，每行对应 N 个系数）
    %   v²_start(u=0) = normR1D(1)² × BasisVal(1,:)   （起端速度²行向量）
    %   at_start(u=0) = t(0)' × Acc(起端行, :, 2)     （起端切向加速度行向量）
    %   v²_end(u=1)   = normR1D(end)² × BasisVal(M,:) （末端速度²行向量）
    %   at_end(u=1)   = t(1)' × Acc(末端行, :, 2)     （末端切向加速度行向量）
    %
    % 用 mask_continuity = [+1;+1;-1;-1] 叠加到 Aeq：
    %   第 k 段 +1 → 在对应行写入 +continuity（前段末端 += +1）
    %   第 k+1 段 -1 → 在对应行写入 -continuity（后段起端 += -1）
    %   最终 Aeq 的那一行 = 前段末 - 后段起 = 0（等价于连续性条件）
    indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2;
    indAEC  = int32( 1 : N ) + ( k - 1 ) * N;

    % 切向加速度行：t(u)' × a(u) = t(u)' × Acc(u,x)
    %   indAT(1,:) 取各轴的第 1 行（u=0，起端）
    %   indAT(2,:) 取各轴的第 M 行（u=1，末端）
    at_norm( 1, :, k ) = t_vec( :, 1, k )' * Acc( indAT( 1, : ), :, 2 ); % 起端切向加速度系数行
    at_norm( 2, :, k ) = t_vec( :, 2, k )' * Acc( indAT( 2, : ), :, 2 ); % 末端切向加速度系数行

    % 速度²行：|r'(u)|² × B(u)·x = v²(u)
    %   BasisVal(1,:)   = B 样条在起端（u=0）处的基函数值行
    %   BasisVal(end,:) = B 样条在末端（u=1）处的基函数值行
    v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [1; end], : );

    continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
                   v2_vec( 2, :, k ); at_norm( 2, :, k ) ];

    % 叠加到 Aeq（mask_continuity 的 +/- 符号实现"前段末端 = 后段起端"）
    Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity .* mask_continuity;
end

% ── 设置窗口两端的边界条件（等式约束右端 beq）────────────────────────────
%
% Aeq 第 1、2 行对应窗口起端（第 1 段的起端 v² 和 at），
% Aeq 最后 2 行对应窗口末端（最后段的末端 v² 和 at）。
% mask_continuity([1,2]) = +1：起端行符号为正，beq = +v_0²/+at_0
% mask_continuity([3,4]) = -1：末端行符号为负，beq = -v_1²/-at_1
%   （等效于：Aeq_end·x = v_1² 和 at_1，因为 Aeq_end 中已含 -1 符号）
beq( [1, 2, end-1, end] ) = [ v_0^2; at_0; v_1^2; at_1 ] .* mask_continuity;

% ── 速度/加速度斜坡（Ramp）：放宽窗口末尾约束以保留速度余量 ──────────────
%
% 【问题根源】
%   滑动窗口 LP 每次仅"提交"第一段（k=1）的解，其余段下次重新优化。
%   若不干预，LP 会让末尾段的速度/加速度达到约束上限（满载）。
%   当下一帧窗口右侧加入新曲线时，其真实约束可能更紧，
%   迫使末尾段急剧减速 → 轨迹速度出现不平滑突变。
%
% 【解决方案】
%   对末尾段的约束右端 b 乘以 ramp > 1，人为放宽约束上限，
%   使 LP 解在窗口后半段倾向于"留有余地"，不把约束用满。
%   下一帧到来时，末尾段有足够调整空间，速度过渡平滑。
%
% 【vel_ramp / acc_ramp 的形状】
%
%   vel_ramp = linspace(1, VEL_RAMP, M)'    → [M × 1]
%     第 1 行（u=0 处）系数 = 1，末行（u=1 处）系数 = VEL_RAMP
%     段内从起端到末端线性增大，仅用于速度上限约束（b 中速度列）
%
%   acc_ramp = repmat(linspace(1,ACC_RAMP,M)', 1, Nc-1) → [M × (Nc-1)]
%     同样从 1 线性增到 ACC_RAMP，横向复制 Nc-1 列，
%     对应速度非负约束（1 列）+ 加速度上下限（2×Ndim 列）共 Nc-1 列
%
% 【ramp 矩阵的拼接（Nwindow=3，M=20，Nc=12 为例）】
%
%   ramp 尺寸：[M × (Nc × Nwindow)] = [20 × 36]
%   按段横向拼接，每段占 Nc=12 列（对应 b 中该段的 Nc×M 个元素）：
%
%     列  1~12  → 段 k=1（第一段，将被提交）
%       全 ones(M,Nc)：不施加 ramp，约束保持真实物理上限
%
%     列 13~24  → 段 k=2（Nwindow=3 时为中间段）
%       [vel_ramp, acc_ramp]：段内从 1 线性增到 VEL_RAMP/ACC_RAMP
%       第 1 列（速度上限）= vel_ramp；第 2~12 列（其余约束）= acc_ramp
%
%     列 25~36  → 段 k=3（末尾段）
%       repmat([vel_ramp(end), acc_ramp(end,:)], M, 1)
%       全行统一用最大斜坡值（VEL_RAMP/ACC_RAMP），约束最宽松
%
%   当 Nwindow > 3 时，中间段（k=2 到 k=Nwindow-1）均用最大值统一放宽：
%     repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)
%     复制 Nwindow-2 列组，覆盖第 2 段到末尾段
%
%   各段 ramp 策略汇总：
%     k=1       → 全 1（真实约束，提交段）
%     k=2       → 线性斜坡（1 → 最大值，段内渐变）
%     k=3~N     → 固定最大值（VEL_RAMP / ACC_RAMP，统一最宽松）
%
% 【b .* ramp(:) 的维度对齐】
%
%   b 是列向量 [Nc×M×Nwindow × 1]，在主循环中按段顺序填入。
%   ramp(:) 按列优先展开同样得 [Nc×M×Nwindow × 1]。
%   逐元素相乘：每行约束的上限 = 原上限 × 对应斜坡系数。
%   注意 ramp 列优先展开顺序与 b 的行排列一致（段内先按点、再按约束类型）。
vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )', 1, Nc-1 );

if( Nwindow > 1 )
    % 拼接 ramp：[M × Nc×Nwindow]
    %   列 1~Nc        : 段 k=1，全 1（提交段不放宽）
    %   列 Nc+1~2*Nc   : 段 k=2，线性斜坡（1 → 最大值）
    %   列 2*Nc+1~end  : 段 k=3~N，统一最大值（Nwindow-2 组）
    ramp = [ ones(M, Nc), vel_ramp, acc_ramp, ...
             repmat( [vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2 ) ];
    b  = b .* ramp(:);  % 逐元素放宽末尾约束上限
end

% ── 返回连续性行（供下一窗口使用）──────────────────────────────────────────
%
% 下一窗口调用时需要当前窗口第一段（k=1）末端的 v²、at，
% 作为其起始边界条件 v_0 / at_0（由 FeedratePlanning_LP 第 100~101 行读取）。
% 因此这里取 k=1（: , :, 1）的末端（第 2 行）。
continuity = [ v2_vec( 2, :, 1 ); at_norm( 2, :, 1 ) ];

checkValidity( A, b, Aeq, beq, continuity );

c_prof_out(mfilename);
end


function checkValidity( A, b, Aeq, beq, continuity )
% checkValidity : 检查约束矩阵的数值合法性
%   NaN → 说明几何求值或链式法则中出现了数值异常，断言终止
%   b < 0 → 不等式约束右端为负，意味着约束无论如何都无法满足（如速度上限为负）
    ocn_assert( ~any( isnan( A ), 'all' ),           "A has NaN",            mfilename );
    ocn_assert( ~any( isnan( b ), 'all' ),           "b has NaN",            mfilename );
    ocn_assert( ~any( find( b < 0 ), 'all' ),        "b should be positive", mfilename );
    ocn_assert( ~any( isnan( Aeq ), 'all' ),         "Aeq has NaN",          mfilename );
    ocn_assert( ~any( isnan( beq ), 'all' ),         "beq has NaN",          mfilename );
    ocn_assert( ~any( isnan( continuity ), 'all' ),  "continuity has NaN",   mfilename );
end
