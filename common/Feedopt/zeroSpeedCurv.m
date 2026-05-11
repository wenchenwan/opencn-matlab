function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
% zeroSpeedCurv : 为零速起始或零速终止段计算恒定伪跃度下的参数 u 曲线
%
% 【算法思想】
%   零速段（ZeroStart / ZeroEnd）需要在起点或终点处速度精确为 0。
%   本函数采用"恒定伪跃度（constant pseudo-jerk）"方案：
%     在参数空间将 u(t) 规划为三次多项式（常值跃度剖面），
%     使得 u 从 0 到 1（或反向）时，速度从 0 连续增大（或减小）到最大值。
%
%   物理速度 = |r'(u)| × du/dt，由于曲率 |r'(u)| 非常数，
%   参数空间的常跃度并不等于物理空间的常跃度，
%   故称之为"伪跃度 jps"（pseudo jerk in parameter space）。
%
% 【u(t) 推导】
%   恒定伪跃度下：du³/dt³ = jps（常数）
%   积分三次并令初始速度 = 0：u(t) = jps * t³ / 6
%   令 u(T) = 1，得总时间 T = (6/jps)^(1/3)
%   离散步数：k = T / dt = (6/jps)^(1/3) / dt
%
% 【迭代策略】
%   1. 以最大跃度限制初始化 jps：jps₀ = min(jmax) / max(|r'(u_peak)|)
%      其中 u_peak 是速度最大处（零起段取 u=1，零止段取 u=0）
%   2. 迭代缩减 jps，直到速度/加速度/跃度/进给率均在约束内
%
% Inputs  :
%   ctx     : 计算链上下文（含运动学 kin、约束 cfg、采样周期 dt）
%   curv    : 曲线结构体
%   isEnd   : true = 零速终止（ZeroEnd），false = 零速起始（ZeroStart）
%
% Outputs :
%   u       : 参数序列（从 0 到 1 或反向）
%   ud      : du/dt 序列（参数速度）
%   udd     : d²u/dt² 序列（参数加速度）
%   jps     : 收敛后的伪跃度值
%

% 确定速度最大点（用于初始化 jps）：
%   零起段（isEnd=false）：速度在 u=1 处最大 → uk=1
%   零止段（isEnd=true） ：速度在 u=0 处最大 → uk=0
uk = 1;
if( isEnd ), uk = 1 - uk; end

% 在速度峰值点处求 dr/du，用于将物理跃度限制折算到参数空间
[ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );

ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );

if( curv.Info.TRAFO )
    % TRAFO 模式：将笛卡尔导数转换到关节空间
    r1D = ctx.kin.v_joint( r0D, r1D );
end

% 初始伪跃度：由最严格轴的跃度限制 / 该点最大参数导数分量折算
%   物理跃度 ≈ jps × |r'(u)|，故 jps = jmax / |r'(u)|_max
jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );

% 迭代缩减 jps，直到所有物理约束（进给率、速度、加速度、跃度）均满足
searchJps = true;
ind = 0;
while searchJps
    ind = ind + 1;
    [ k_vec ]          = compute_k( jps, ctx.cfg.dt, 1 );
    [ searchJps, jps ] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
end

% 用收敛后的 jps 生成最终 u / ud / udd 序列
[ k_vec ]      = compute_k( jps, ctx.cfg.dt, 1 );
[ u, ud, udd ] = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true );

end

function [ k_vec ] = compute_k( jps, dt, uk )
% compute_k : 计算参数 u 从 0 走到 uk 所需的离散时间步索引向量
%
% 推导：恒定伪跃度下 u(t) = jps * t³/6
%   令 u(T) = uk → T = (6*uk/jps)^(1/3)
%   离散步数（非整数）：k = T / dt
%
% k_vec 为整数步 0:floor(k)，再追加精确终点 k（保证 u 恰好到达 uk）

k = ( 6 * uk / jps )^( 1 / 3 ) / dt;

if( k > 0 )
    k_vec = 0 : k;
    % floor(k) < k 时追加精确终点，确保 u 序列覆盖完整区间
    if( k_vec( end ) < k ), k_vec = [ k_vec, k ]; end
else
    k_vec = 1;
end

end

function [ searchJps, jps, u, ud, udd ] = calc_u( isEnd, searchJps, jps, ctx, ...
    curv, k_vec  )
% calc_u : 验证当前 jps 下的运动剖面是否满足所有物理约束，超限则缩减 jps
%
% 【约束检查顺序（优先级从高到低）】
%   1. 进给率 feed > fmax   → 路径线速度超限（最优先）
%   2. 关节速度 |V| > vmax
%   3. 关节加速度 |A| > amax
%   4. 关节跃度 |J| > jmax  （最后检查）
%   每轮迭代只处理最高优先级的违约项；多轮后所有约束逐步满足。
%
% 【jps 缩减公式】
%   超限量 delta = actual - limit（均为正值）
%   缩减比例：jps_new = jps × (1 - ratio × (1 - limit/actual))
%            = jps × ((1-ratio) + ratio × limit/actual)
%   · actual >> limit 时：limit/actual ≈ 0，jps 缩减约 ratio 倍（激进）
%   · actual ≈ limit  时：limit/actual ≈ 1，jps 几乎不变（稳定）
%   ratio=0.9 时收敛快且不振荡。
%
% 【安全系数 safetyFactor = 0.5】
%   约束限制取额定值的 50%，为后续全局优化（feedratePlanning）保留裕量。
%
% Inputs :
%   isEnd     : true = 零速终止，false = 零速起始
%   searchJps : 当前是否仍在搜索（迭代控制标志）
%   jps       : 当前伪跃度
%   ctx       : 上下文（含约束参数）
%   curv      : 曲线结构体
%   k_vec     : 时间步索引向量（由 compute_k 生成）
% Outputs :
%   searchJps : 是否需要继续迭代（false = 收敛）
%   jps       : 更新后的伪跃度

% ratio 控制每轮缩减的激进程度，persistent 避免重复初始化
persistent ratio
if( isempty( ratio ) ), ratio = 0.9; end

% 用当前 jps 生成 u / ud / udd / uddd 序列
[ u, ud, udd, uddd ] = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true );

% 将参数域剖面转换为物理速度 V、加速度 A、跃度 J（关节空间）
[ ~, V, A, J ] = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );

% 计算路径进给率（笛卡尔轴线速度）：feed = |r'(u)|_cart × ud
[ r0D, r1D ] = EvalCurvStruct( ctx, curv, u );
ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
if( curv.Info.TRAFO )
    r1D_r = r1D;                            % TRAFO 模式：已在关节空间
else
    [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );  % 转换到相对（工具）坐标
end

% 约束上限取额定值的 50%（为全局进给规划保留裕量）
safetyFactor = 0.5;
fmax = curv.Info.FeedRate               * safetyFactor;
vmax = ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
amax = ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
jmax = ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;

feed = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud;

% 按优先级检查约束，发现超限则按比例缩减 jps 并继续迭代
if( any( feed > fmax ) )
    % 进给率超限：按最大超限点的超限比例缩减
    [ f_delta, ind ] = max( feed - fmax );
    jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
elseif( any( abs( V ) > vmax, 'all' ) )
    % 关节速度超限
    [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) ) );
elseif( any( abs( A ) > amax, 'all' ) )
    % 关节加速度超限
    [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) ) ) );
elseif( any( abs( J ) > jmax, 'all' ) )
    % 关节跃度超限
    [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind ) ) ) );
else
    % 所有约束均满足，退出迭代
    searchJps = false;
end
end
