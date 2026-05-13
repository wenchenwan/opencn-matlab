function [ ctx, Coeff, success, status, msg ] = ...
    FeedratePlanning_LP( ctx, window, amax, jmax, BasisVal, ...
    BasisValD, BasisValDD, BasisIntegr, u_vec, NWindow )
%#codegen
% FeedratePlanning_LP : 构建并求解进给率优化 LP 问题
%
% 两阶段 LP 策略：
%   第一阶段：仅含速度和加速度约束（线性，较宽松）
%   第二阶段：在第一阶段解的基础上线性化跃度约束，再次求解（更严格）
%   每次都添加松弛变量（slack），避免约束不可行导致无解
%
% 决策变量：x = [w_1; w_2; ...; w_Nwindow; slack]
%   其中 w_k = [c_1, ..., c_N] 为第 k 段的 B 样条系数
%   物理意义：w_k(u) ≈ v²(u)，速度平方的 B 样条近似
%
% 目标函数：最小化 -∫v²du（等价于最大化 ∫v²du，近似最小化时间）
%   加上 slack 惩罚项，鼓励约束满足
%
% Inputs :
%   ctx        : 上下文（含 v_0/v_1/at_0/at_1 边界条件）
%   window     : 优化窗口曲线数组
%   amax/jmax  : 各轴加速度/跃度上限
%   BasisVal~  : 预计算的 B 样条基值及各阶导数
%   BasisIntegr : B 样条基积分（用于构造目标函数）
%   u_vec      : 离散化参数向量
%   NWindow    : 窗口内有效曲线段数
%
% Outputs :
%   ctx        : 更新后的上下文（含新的 v_0/at_0 边界，为下一窗口准备）
%   Coeff      : [N×NWindow] 优化得到的 B 样条系数
%   success    : 是否成功求解
%   status/msg : 求解器返回的状态和消息
%

[ M, N ]    = size( BasisVal );
LP          = ctx.cfg.opt;              % LP 参数（SLACK_PENALTY 等）
CurvArray   = window( 1 : NWindow );    % 当前窗口的曲线数组

%% 第一阶段 LP：速度 + 加速度约束

% 计算长度缩放矩阵 D（用于改善 LP 数值条件数）
[ D, Dinv ] = compute_scaling_matrix( ctx, CurvArray, N );
DCon        = D( [ 1 : N ], [ 1 : N ] ); % 单段缩放矩阵（用于连续性方程）

% 构造目标函数：f = -∫B(u)du（最大化速度积分 = 最小化时间）
% BasisIntegr 是每个 B 样条基函数在 [0,1] 上的积分值
f = -repmat( BasisIntegr, 1, NWindow );
f = reshape( f( : )' * D, [], NWindow ); % 应用缩放矩阵

% 构造速度和加速度约束（不含跃度）
[ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax, ctx.v_0, ...
    ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD, u_vec);

% 对约束矩阵应用缩放（变量变换 x = D·y，使问题更数值稳定）
A           = A * D;
Aeq         = Aeq * D;
continuity  = continuity * DCon;

indSlack    = []; % 第一阶段不对约束添加松弛（仅对整体添加一个 slack）

% 添加松弛变量到 LP（防止不可行）
[ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( ctx.cfg.opt, f, ...
    A, b, Aeq, beq, indSlack, LP );

% 调用 LP 求解器（COIN-OR CLP 或 linprog）
[ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack, ASlack, bSlack, ...
    AeqSlack, beqSlack, ctx, N, NWindow, "First LP" );

if( ~success ), return; end

%% 第二阶段 LP：在速度+加速度基础上叠加跃度约束

if( ctx.cfg.opt.USE_JERK_CONSTRAINTS )
    % 反缩放：将第一阶段解转回原始变量空间（用于构造跃度约束的线性化）
    Coeff = reshape( D * Coeff( : ), N, [] );

    % 基于第一阶段解线性化跃度约束（跃度约束本身非线性，此处做 Taylor 线性化）
    [ Aj, bj ] = buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
        BasisVal, BasisValD, BasisValDD, u_vec );

    Aj   = Aj * D;
    Atot = [ A; Aj ]; btot = [ b; bj ]; % 合并后 Atot 行结构：
    %   行  1 ~ numel(b)                  ← A（速度 + 加速度约束，精确线性）
    %   行  numel(b)+1 ~ numel(b)+numel(bj) ← Aj（跃度约束，线性化近似）

    % 计算跃度约束行在 Atot 中的全局行索引，作为 indSlack 传给 add_slack：
    %   numel(b) + [1 : numel(bj)] → Atot 中跃度约束的连续行号
    % 这些行在 add_slack 中会被软化（vecSlack = -1）：Aj·x - s ≤ bj
    % 速度/加速度约束行（1~numel(b)）不在 indSlack 中，保持硬约束。
    % 原因：跃度约束由第一阶段解线性化近似得来，存在近似误差可能导致微小
    %       不可行，需要松弛保底；速度/加速度约束已在第一阶段验证可行，
    %       保持硬约束确保物理安全性。
    indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];

    [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( ctx.cfg.opt, ...
        f, Atot, btot, Aeq, beq, indSlack, LP );

    % 第二次求解（含跃度约束）
    [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack, ASlack, bSlack, ...
        AeqSlack, beqSlack, ctx, N, NWindow, "Second LP" );
end

if( ~success ), return; end

% 更新下一窗口的起始边界条件（滑动窗口的连续性传递）
if( ~ctx.zero_start )
    X           = continuity * Coeff( : , 1 ); % 取第一段末端的连续性值
    ctx.v_0     = mysqrt( X( 1 ) );            % 下一窗口的起始速度 = 当前窗口第一段末速度
    ctx.at_0    = X( 2 );                      % 下一窗口的起始切向加速度
end

Coeff       = reshape( D * Coeff( : ), N, [] ); % 反缩放得到最终系数
ctx.Coeff   = Coeff;                            % 存入上下文供分发

end

%--------------------------------------------------------------------------
% 内部辅助函数
%--------------------------------------------------------------------------

function [ ctx, Coeff, success, status, msg, beq ] = solve_LP( f, A, b, Aeq, ...
    beq, ctx, N, NWindow, optName )
% 调用 LP 求解器，处理零速边界时的松弛迭代
[ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, Aeq, ...
    beq, ctx );

if( ~success && ( ctx.zero_start || ctx.zero_end ) )
    % 零速边界时：LP 可能因约束过紧而失败，逐步放松 ConstJerk 重试
    Ntot        = NWindow;
    maxIter     = 15;

    if( ~success && ctx.zero_start )
        Ntot        = Ntot + 1;
        indStart    = ctx.k0;
        % 松弛起始端的恒跃度约束（每次除以 8，最多重试 15 次）
        [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
            f, A, b, Aeq, beq, ctx, indStart, false, maxIter);
    end

    if( ~success && ctx.zero_end )
        Ntot        = Ntot + 1;
        indEnd      = ctx.k0 + Ntot - 1;
        % 松弛末尾端的恒跃度约束
        [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
            f, A, b, Aeq, beq, ctx, indEnd, true, maxIter);
    end
end

% 提取求解结果
Coeff = [];
if( success )
    % 去掉松弛变量（最后一个元素），重塑为 [N × NWindow]
    Coeff   = reshape( Coeff0( 1 : end - 1 ), N, NWindow );

    if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
        fprintf( "Slack : " + Coeff0( end ) + "\n" ); % 松弛变量非零则打印警告
    end
else
    msg = optName + " failed...";
end

end

function [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( opt, ...
    f, A, b, Aeq, beq, indSlack, LP )
% add_slack : 向 LP 引入松弛变量，将硬约束软化为带惩罚的软约束
%
% ═══════════════════════════════════════════════════════════════════════════
% 【为什么需要松弛变量】
%
%   标准 LP：A·x ≤ b。若约束不可行（无解），LP 直接失败，轨迹规划中断。
%   原因：
%     - 跃度约束由第一阶段解线性化近似，近似误差可能导致第二阶段略微不可行
%     - 零速起/末端的边界条件过紧时，速度约束本身可能矛盾
%
%   引入松弛变量 s ≥ 0 后，硬约束改为软约束：
%     A·x - s ≤ b   ←→   A·x ≤ b + s
%   s = 0 时约束完全满足；s > 0 时约束被违反了 s 的量。
%   在目标函数中加惩罚项 SLACK_PENALTY × s，迫使 LP 尽量让 s → 0。
%   即使约束略微不可行，LP 也能给出"最接近可行"的解，不会崩溃。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【决策变量扩展：x → [x; s]】
%
%   原变量 x ∈ R^Nx（各段 B 样条系数），加入一个标量松弛 s 后：
%     [x; s] ∈ R^(Nx+1)
%   所有矩阵均在最右侧增加一列，对应 s 的系数。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【indSlack 控制松弛作用在哪些约束行】
%
%   vecSlack(indSlack) = -1，其余行为 0。
%   只有 indSlack 指定的行变成软约束（A_i·x - s ≤ b_i），其余行仍是硬约束。
%
%   两阶段中 indSlack 的用法：
%     第一阶段（速度+加速度）：indSlack = []
%       vecSlack 全零，s 只出现在目标函数惩罚项，约束保持硬约束。
%       速度/加速度约束线性良好，一般可行，无需软化。
%
%     第二阶段（叠加跃度）：indSlack = 跃度约束的所有行索引
%       跃度约束行的 vecSlack = -1，变成 Aj·x - s ≤ bj（软化）。
%       跃度约束由线性化近似得来，可能因近似误差导致略微不可行，需要软化。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【Apos：强制 B 样条系数非负（可选）】
%
%   决策变量 x 的物理含义是参数速度平方 w(u) = ud² ≥ 0 的 B 样条系数。
%   B 样条的凸包性质保证：若所有系数 ≥ 0，则函数值在全域 ≥ 0。
%   LP 求解器不了解此物理约束，可能给出负系数（速度平方为负，物理无意义）。
%
%   Apos 将"xᵢ ≥ 1e-4"翻译为 LP 不等式"-xᵢ ≤ -1e-4"，加入约束矩阵：
%     Apos 尺寸：(nAc-4) × (nAc+1)
%     中间 nAc-4 列（跳过首尾各 2 个）填 -I（单位负矩阵）
%     bpos = -1e-4 × ones（对应 xᵢ ≥ 1e-4）
%
%   为何跳过首尾各 2 个系数：
%     首尾系数由等式约束（Aeq·x = beq）精确固定为边界速度值，
%     边界速度值本身已非负，无需重复约束，跳过可减少冗余，改善数值条件。
%
%   此选项可能收紧可行域，对极端曲率路径可能导致 LP 更难求解，故设为可选。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【完整扩展后的 LP 结构（以扩展变量 [x; s] 为决策变量）】
%
%   目标函数：[f(:); SLACK_PENALTY]' · [x; s]
%   约束矩阵（纵向拼接）：
%     行组 1：Apos（可选，强制系数非负）
%     行组 2：[A, vecSlack]（原约束 + 松弛列，指定行软化）
%     行组 3：[0, ..., 0, -1]（强制 s ≥ 0：-s ≤ 0）
%   等式约束：[Aeq, 0]·[x; s] = beq（补零列，s 不参与等式）

[ nAL, nAc ] = size( A );

if( opt.FORCE_POSITIV_COEFFS )
    % 构造非负约束：-x_middle ≤ -1e-4（即 x_middle ≥ 1e-4）
    % 尺寸：(nAc-4) × (nAc+1)，中间 nAc-4 列 = -I，首2列和末3列为0
    % 末3列：最后2个 x 系数列 + 最后1个松弛 s 列，均跳过
    Apos = zeros( nAc-4 , nAc + 1 ); bpos = -1e-4 * ones( nAc-4 , 1);
    Apos( : , 3 : end-3 ) = -eye( nAc-4 );
else
    Apos = [];
    bpos = [];
end

% vecSlack：松弛列，indSlack 指定的约束行为 -1（软化），其余为 0（硬约束）
vecSlack    = zeros( nAL, 1 ); vecSlack( indSlack ) = -1;

% 目标函数：原 f 末尾追加 SLACK_PENALTY（惩罚 s > 0，鼓励约束满足）
fSlack      = [ f( : ); LP.SLACK_PENALTY ];

% 约束矩阵（纵向拼接三组）：
%   [Apos]                          → 可选非负约束（nAc-4 行）
%   [A, vecSlack]                   → 原约束 + 松弛列（nAL 行）
%   [zeros(1,nAc), -1]              → -s ≤ 0，即 s ≥ 0（1 行）
ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];

% 右端向量（与 ASlack 行对应）：
%   bpos（非负约束右端）→ b（原约束右端）→ 0（s ≥ 0 的右端）
bSlack      = [ bpos; b; 0 ];

% 等式约束：补一列零（松弛变量 s 不参与等式约束）
AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
beqSlack    = beq;

end

function [ curv, vNorm, atNorm ] = decrease_constjerk( ctx, curv, isEnd )
% 将零速段的恒跃度约束降低（除以 8），用于松弛迭代中
curv.ConstJerk = curv.ConstJerk / 8;
[ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
end

function [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
    f, A, b, Aeq, beq, ctx, indCurv, isEnd, maxIter)
% 松弛零速段的初始约束（逐步降低 ConstJerk），重试 LP 直到成功或超过 maxIter 次
success     = false;
count       = 0;
curv        = ctx.q_split.get( indCurv );
atNorm      = 0;
vNorm       = 0;
status      = int32( 0 );
Coeff0      = zeros( size( f ) );
msg         = "";

while( ~success && count < maxIter )
    [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd );

    if( isEnd )
        beq( end-1 ) = -vNorm^2;  % 更新末端速度约束（负号因 mask_continuity）
        beq( end )   = atNorm;
    else
        beq( 1 ) = vNorm^2;       % 更新起端速度约束
        beq( 2 ) = atNorm;
    end

    [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, ...
        Aeq, beq, ctx );
    count = count + 1;
end

% 将松弛后的曲线写回队列，并更新上下文的边界条件
ctx.q_split.set( indCurv, curv );
if( isEnd )
    ctx.at_1 = -atNorm;
    ctx.v_1  = -vNorm;
else
    ctx.at_0 = atNorm;
    ctx.v_0  = vNorm;
end

end

function [ D, Dinv ] = compute_scaling_matrix( ctx, curvArray, NCoeff )
% 计算决策变量的对角缩放矩阵 D（用于改善 LP 数值稳定性）
% 若 USE_LENGTH_SCALING=true，按各段弧长平方缩放；否则为单位矩阵
    N = length( curvArray );

    if( ctx.cfg.opt.USE_LENGTH_SCALING )
        lCurvs = zeros( NCoeff, N );
        for ind = 1 : N
            lCurvs( :, ind ) = ones( NCoeff, 1 ) * LengthCurv( ctx, ...
                curvArray( ind ), 0, 1 );
        end
        t = lCurvs( : ).^2;
    else
        t = ones( N * NCoeff, 1 ); % 不缩放：D = I
    end

    D    = diag( 1 ./ t );  % 缩放矩阵（对角）
    Dinv = diag( t );       % 反缩放矩阵
end
