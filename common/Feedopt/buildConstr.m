function [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, windowCurv, amax, ...
    v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec )
%#codegen
% buildConstr : 构建 LP 问题的约束矩阵
%
% LP 问题形式：
%   决策变量 x ∈ R^(N×Nwindow)：每段曲线上 N 个 B 样条系数
%   物理含义：x = w(u) ≈ v²(u)，即各离散点处速度的平方
%
%   目标函数（在 FeedratePlanning_LP 中定义）：最大化加工进给量（最小化时间）
%
%   不等式约束（A·x ≤ b）：
%     行组 1：v² ≤ v_max²（速度上限）
%     行组 2：-v² ≤ 0   （速度非负）
%     行组 3：加速度分量 ≤ a_max（各轴加速度上限）
%     行组 4：加速度分量 ≥ -a_max（各轴加速度下限）
%
%   等式约束（Aeq·x = beq）：
%     窗口两端：速度² = v_0² 和 v_1²（边界速度条件）
%     窗口两端：切向加速度 = at_0 和 at_1（边界加速度条件）
%     段间连续性：相邻段在连接处速度²和切向加速度相等
%
% Inputs :
%   ctx       : 上下文（含 NumberAxis、vmax、indCart 等）
%   windowCurv : 优化窗口内的曲线数组（长度 Nwindow）
%   amax      : 各轴最大加速度（完整 6 轴向量）
%   v_0/v_1   : 窗口起/末端速度边界条件
%   at_0/at_1 : 窗口起/末端切向加速度边界条件
%   BasisVal  : [M×N] 在 u_vec 处的 B 样条基函数值
%   BasisValD : [M×N] 在 u_vec 处的 B 样条基函数一阶导
%   u_vec     : [1×M] 离散化参数向量
%
% Outputs :
%   A, b      : 不等式约束矩阵和向量（A·x ≤ b）
%   Aeq, beq  : 等式约束矩阵和向量（Aeq·x = beq）
%   continuity : 最后一段末端的连续性方程（供下一窗口用作起始边界）
%

c_prof_in(mfilename); % 性能计时开始

% 维度定义
Ndim        = ctx.cfg.NumberAxis;     % 激活轴数（如 5 轴机为 5）
Nwindow     = length( windowCurv );   % 当前窗口曲线段数

% B 样条维度
[ M, N ]    = size( BasisVal );       % M: 离散点数, N: 基函数个数（= 样条系数数）
Nx          = N * Nwindow;            % 决策变量总数 = 系数数 × 窗口段数
Nc          = ( 2 + 2 * Ndim );       % 每个离散点的不等式约束行数
                                      % = 2（速度上下界）+ 2*Ndim（加速度上下界）
Nec         = 2 * ( Nwindow + 1 );    % 等式约束总行数
                                      % = 2 × (窗口段数 + 1 个连接点)

% 预分配约束矩阵
A           = zeros( Nc * M * Nwindow,  Nx ); % 不等式约束矩阵
b           = zeros( Nc * M * Nwindow,  1 );  % 不等式约束向量
Aeq         = zeros( Nec, Nx );               % 等式约束矩阵
beq         = zeros( Nec, 1 );                % 等式约束向量
amaxTot     = amax( ctx.cfg.maskTot );        % 提取激活轴的加速度限制
b_amax      = repmat( amaxTot, M, 1 );        % 按离散点数复制（广播到所有 M 个点）

% 工作变量初始化
at_norm     = zeros( 2, N, Nwindow );  % 段起/末端的切向加速度行（用于连续性方程）
t_vec       = zeros( Ndim, 2, Nwindow ); % 段起/末端的切线单位向量
v2_vec      = zeros( 2, N, Nwindow );  % 段起/末端的速度²行（用于连续性方程）
Acc         = zeros( M * Ndim , N, 2 ); % 加速度约束矩阵（两种坐标系）
% indAT：用于从 Acc 中取起/末端行的索引（尺寸：[2×Ndim]）
indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );
% mask_continuity：连续性方程的符号，相邻段在连接点：前段末 = 后段起
mask_continuity = [ 1; 1; -1; -1 ]; % 前段末 +，后段起 -，等式=0
v_max       = zeros( Ndim + 1, M );   % 速度上限（含各轴限制和编程进给率限制）

for k = 1 : Nwindow
    % 在 u_vec 处求当前曲线的几何导数（0阶~3阶，对参数 u 求导）
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
    ctx.kin = ctx.kin.set_tool_length( -windowCurv( k ).tool.offset.z );

    if( windowCurv( k ).Info.TRAFO )
        % 运动学变换模式：将笛卡尔速度转换为关节速度（用于 5 轴机）
        [ ~, r1D_a, r2D_a ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
        r1D_r    = r1D; % 相对速度保持笛卡尔坐标
    else
        % 非变换模式：计算相对速度（用于进给率约束）
        [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
        r1D_a    = r1D;   % 加速度约束用笛卡尔坐标
        r2D_a    = r2D;
    end

    % 切线单位向量（起点和终点）：用于连续性方程中的切向加速度计算
    normR1D = vecnorm( r1D );
    t_vec( : , :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );

    % 计算各轴速度上限（v_max = (v_axis_max / r')^2）
    % 约束形式：v²(u) ≤ (v_axis / r'(u))^2
    v_max( 1 : Ndim, : ) = ( ctx.cfg.vmax( ctx.cfg.maskTot ).'./ r1D_a ).^2;

    % 编程进给率约束（G-code 中的 F 指令值，作用于笛卡尔空间）
    v_max( end, : ) = ( windowCurv( k ).Info.FeedRate ./ ...
        vecnorm( r1D_r( ctx.cfg.indCart, : ) ) ).^2;

    % 取所有约束中的最小值（最紧的限制）
    f_max = min( v_max, [], 1 );

    % 构建加速度约束矩阵 Acc：
    % 加速度 = r''(u)·w·BasisVal + 0.5·r'(u)·dw/du·BasisValD
    % 其中 w = v² = B(u)·x（x 为决策变量）
    for j = 1 : Ndim
        ind = int32( 1 : M ) + ( j - 1 ) * M;
        Acc( ind, :, 1 ) = r2D_a( j, : )' .* BasisVal + 0.5 * r1D_a( j, : )' .* BasisValD;
        Acc( ind, :, 2 ) = r2D( j, : )'   .* BasisVal + 0.5 * r1D( j, : )'   .* BasisValD;
    end

    % 组装本段的不等式约束块：
    %   [  BasisVal    ]        ≤ f_max     （速度上限：v² ≤ f_max）
    %   [ -BasisVal    ]        ≤ 0         （速度非负：v² ≥ 0）
    %   [  Acc(:,:,1)  ]        ≤ a_max     （加速度上限）
    %   [ -Acc(:,:,1)  ]        ≤ a_max     （加速度下限，即 ≥ -a_max）
    indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M; % 行索引
    indAC   = int32( 1 : N  ) + ( k - 1 ) * N;           % 列索引
    A( indAL, indAC )   = [ BasisVal; -BasisVal; Acc( :, :, 1); -Acc( :, :, 1) ];
    b( indAL )          = [ f_max'; zeros( size(f_max) )';
                            b_amax( : ); b_amax( : ) ];

    % 构建段间连续性等式约束：
    %   起端：v²(u=0) = v_0²，at(u=0) = at_0
    %   末端：v²(u=1) 和 at(u=1) 传递给下一段的起始条件
    indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2;   % 等式约束行索引（每段 4 行：起/末各 2）
    indAEC  = int32( 1 : N ) + ( k - 1 ) * N;    % 等式约束列索引
    at_norm( 1, :, k )   = t_vec( : , 1, k )' * Acc( indAT( 1, : ) , :, 2 ); % 起端切向加速度
    at_norm( 2, :, k )   = t_vec( : , 2, k )' * Acc( indAT( 2, : ) , :, 2 ); % 末端切向加速度

    v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [ 1; end ], :); % 起/末端速度²
    continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
                   v2_vec( 2, :, k ); at_norm( 2, :, k ) ];
    % 叠加到 Aeq（通过 mask_continuity 的符号来实现"前段末 = 后段起"）
    Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity .* mask_continuity;
end

% 设置边界条件：窗口起端和末端的速度²和切向加速度固定值
beq( [ 1, 2, end-1, end ] ) = [ v_0^2; at_0; v_1^2; at_1 ] .* mask_continuity;

% 在窗口末尾施加速度/加速度斜坡（ramp），避免末尾过优化（避免只有最后一段满载）
vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )', 1, Nc-1 );

if( Nwindow > 1 )
    % 对末尾段应用约束斜坡（降低末尾约束上限，使解更稳定）
    ramp = [ones(M, Nc), vel_ramp, acc_ramp, ...
            repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)];
    b  = b .* ramp(:);
end

% 返回最后一段末端的连续性方程（供下一次窗口调用时作为起始边界）
continuity = [ v2_vec( 2, : , 1 ); at_norm( 2, :, 1 ) ];

checkValidity( A, b, Aeq, beq, continuity ); % 检查矩阵中无 NaN，b 非负

c_prof_out(mfilename); % 性能计时结束
end


function checkValidity( A, b, Aeq, beq, continuity )
% 合法性检查：约束矩阵不含 NaN，不等式右端向量 b 非负
    ocn_assert( ~any( isnan( A ) , 'all' ),             "A has NaN", mfilename );
    ocn_assert( ~any( isnan( b ) , 'all' ),             "b has NaN", mfilename );
    ocn_assert( ~any( find( b < 0 ) , 'all' ),          "b should be positive", mfilename );
    ocn_assert( ~any( isnan( Aeq ) , 'all' ),           "Aeq has NaN", mfilename );
    ocn_assert( ~any( isnan( beq ) , 'all' ),           "beq has NaN", mfilename );
    ocn_assert( ~any( isnan( continuity ) , 'all' ),    "continuity has NaN", mfilename );
end
