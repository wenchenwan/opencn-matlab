function [ L ] = splineLength( cfg, spline, u1, u2 )
% splineLength : 计算 B 样条在全局参数 [u1, u2] 之间的弧长
%
% 策略："两端 GL 积分，中间查 Lk 表"
%
%   B 样条节点把参数域分成 K 个区间，SplineLengthApproxGL_tot 已预算
%   每个区间的弧长存入 sp.Lk。
%
%   对于任意 [u1, u2]：
%     - u1/u2 未必恰好在节点上，需 GL 积分处理两端不完整区间
%     - 中间的完整区间直接查表求和
%
%   L = sum(Lk[kStart : kEnd-1]) - LStart - LEnd
%       ↑ 完整区间累加        ↑减去两端超出的部分
%
% Inputs :
%   cfg    : 配置结构体（含 GaussLegendreX/W）
%   spline : B 样条结构体（sp.Lk 为预计算区间弧长）
%   u1     : 积分起点（全局参数）
%   u2     : 积分终点（全局参数，u2 > u1）
%
% Outputs :
%   L : 弧长（mm）
%

sp = spline.sp;
IND_KNOTS_MULT = sp.Bl.order;
% 去掉端点重节点，得到不重复的节点序列
Knots = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk    = sp.Lk;

ocn_assert( u2 > u1,          'u2 must be greater than u1', mfilename);
ocn_assert( u1 >= Knots(1),   'u1 must be greater or equal than the first spline knot', mfilename);
ocn_assert( u2 <= Knots(end), 'u2 must be smaller or equal than the last spline knot', mfilename);

% 找 u1 所在的节点区间（最后一个 ≤ u1 的节点）
kStartVec = find( Knots <= u1, 1, "last" );
% 找 u2 所在的节点区间（第一个 ≥ u2 的节点）
kEndVec   = find( Knots >= u2, 1, "first" );
kStart    = kStartVec( 1 );
kEnd      = kEndVec( 1 );

% 左端不完整区间：从 Knots[kStart] 到 u1 的弧长（需从 Lk[kStart] 中扣掉）
if( Knots( kStart ) < u1 )
    LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u1, false );
else
    LStart = 0;  % u1 恰好在节点上，无需扣除
end

% 右端不完整区间：从 u2 到 Knots[kEnd] 的弧长（需从 Lk[kEnd-1] 中扣掉）
if( Knots( kEnd ) > u2 )
    LEnd = splineLengthApprox_Interval( cfg, spline, u2, Knots( kEnd ), false );
else
    LEnd = 0;  % u2 恰好在节点上，无需扣除
end

% 累加 [kStart, kEnd-1] 范围内所有完整区间的预计算弧长，
% 再减去两端超出 u1/u2 的部分
L = sum( Lk( kStart : ( kEnd - 1 ) ) ) - LStart - LEnd;
end
