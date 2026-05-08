function [ u ]  = splineLengthFindU( cfg, spline, L, u0, isEnd )
% splineLengthFindU : 弧长反演 —— 给定弧长 L 求对应的参数 u
%
% 问题：找 u 使得 s(u0, u) = L，其中 s = ∫‖r'(t)‖dt（弧长积分无解析逆）。
%
% 两阶段策略：
%   阶段1（粗查，O(K)）：利用预存的各节点区间弧长 sp.Lk，
%       cumsum 快速定位 L 落在哪个节点区间 [uLeft, uRight]。
%   阶段2（精确，O(log(1/tol))）：在该区间内二分搜索，
%       每步用 GL-5 积分算弧长，精度 tol=1e-7，最多 1000 次。
%
% isEnd=true 时从末端往回截：将参数空间关于 0.5 镜像后正常跑，
% 最后再翻回原坐标（u = 1 - u）。
%
% Inputs :
%   cfg    : 配置结构体（含 GL 节点/权重）
%   spline : B 样条结构体（sp.Lk 为预计算的区间弧长）
%   L      : 目标弧长（mm）
%   u0     : 起始全局参数
%   isEnd  : true = 从末端往回截 L；false = 从 u0 向前截 L
%
% Outputs :
%   u : 截点的全局参数；-1 表示失败（L 过大或二分不收敛）
%

ITER_MAX    = 1000;
DEFAULT_TOL = 1E-7;

sp = spline.sp;

% 去掉端点重节点（夹紧样条两端各有 order 重节点，只保留不重复的部分）
IND_KNOTS_MULT = sp.Bl.order;
Knots = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk    = sp.Lk;
kMax  = numel( Lk );

% isEnd 镜像：把"从末端往回量 L"转化为"从起端向前量 L"
if( isEnd )
    u0    = 1 - u0;
    Knots = flip( 1 - Knots );  % 节点向量镜像并反转顺序
    Lk    = flip( Lk );         % 区间弧长对应反转
end

C_ASSERT_MSG = 'u0 must be %s or equal than the first spline knot';
ocn_assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater'), mfilename );
ocn_assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller'), mfilename );

% ── 阶段 1：粗查 ─────────────────────────────────────────────────────────

% ① u0 所在的节点区间（最后一个 ≤ u0 的节点索引）
kStartVec = find( Knots <= u0, 1, "last" );
kStart    = kStartVec( 1 );

% ② u0 可能在区间中间，先算从区间左端到 u0 的弧长（要从累积和里扣掉）
if( Knots( kStart ) < u0 )
    LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u0, isEnd );
else
    LStart = 0;  % u0 恰在节点上，不需要扣
end

% ③ 从 kStart 起累积各区间弧长，减去 LStart 得到"从 u0 出发"的累积弧长
LEnd = cumsum( Lk( kStart : kMax) ) - LStart;

% ④ 找第一个累积弧长 ≥ L 的区间
LkEndVec = find( LEnd >= L, 1, "first" );
if( isempty( LkEndVec ) )
    u = -1; return;   % L 超过曲线剩余总长，失败
else
    LkEnd = LkEndVec( 1 );
    % 计算在目标区间内还需走的弧长 LDiff
    if( LkEnd > 1 )
        LDiff = L - LEnd( LkEnd - 1 );  % 减去前面区间的累积弧长
    else
        LDiff = L + LStart;  % 目标在第一个区间内，LEnd(1) 已减过 LStart，需加回
    end
end

kEnd   = LkEnd + kStart;
uLeft  = Knots( kEnd - 1 );
uRight = Knots( kEnd );

% ── 阶段 2：区间内二分 ───────────────────────────────────────────────────
% 在 [uLeft, uRight] 内找 u 使 s(uLeft, u) = LDiff
[ u, ~ ] = bisection( uLeft, uRight, cfg, spline, LDiff, ITER_MAX, DEFAULT_TOL, isEnd );

ocn_assert(~(u < 0), "Fails to compute length", mfilename);

% isEnd 镜像还原
if( isEnd && u >= 0 )
    u = 1 - u;
end

end

%-------------------------------------------------------------------------%

function [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff, iterMax, tol, isEnd )
% bisection : 在 [uLeft, uRight] 内二分搜索满足 s(uLeft, u) = LDiff 的 u
%
% 每步：计算 s(uLeft, uMiddle)，与 LDiff 比较：
%   > LDiff → 超了，目标在左边 → 右边界收缩
%   < LDiff → 不足，目标在右边 → 左边界收缩
% 精度 tol=1e-7，约 log2(1e7)≈23 次即可收敛，上限 1000 次防止极端情况
%
count   = 0;
uStart  = uLeft;
fk      = tol * 1.1;  % 初始化为大于 tol，确保至少进入一次循环

uMiddle = ( uLeft + uRight ) / 2;

while( count < iterMax && abs( fk ) > tol )
    uMiddle = ( uLeft + uRight ) / 2;

    % 计算从 uStart 到 uMiddle 的弧长，与目标 LDiff 的误差
    fk = splineLengthApprox_Interval( cfg, spline, uStart, uMiddle, isEnd ) - LDiff;

    if( fk > 0 )
        uRight = uMiddle;  % 积分超了，目标在左边
    else
        uLeft  = uMiddle;  % 积分不足，目标在右边
    end
    count = count + 1;
end

if( count >= iterMax )
    u = -1;   % 未收敛，标记失败
else
    u = uMiddle;
end

end
