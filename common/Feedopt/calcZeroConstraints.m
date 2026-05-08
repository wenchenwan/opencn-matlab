function [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd )
%#codegen
% calcZeroConstraints : 计算零速边界处的速度范数与切向加速度范数
%
% 【用途】
%   在分割阶段，零速段（curvS/curvE）已预计算了恒定跃度（ConstJerk）速度曲线。
%   LP 优化阶段需要确保：主段与零速段在连接点处的速度和加速度连续。
%   本函数在连接点处（零速段的"自由端"，即与主段相接的端点）
%   计算恒定跃度速度曲线的速度范数 vNorm 和切向加速度范数 atNorm，
%   作为 LP 优化的边界约束值。
%
% 【连接点的参数位置】
%   恒定跃度速度曲线：u(k) = jps * k³/6，其中 k 是伪时间，jps = ConstJerk
%   当 u=1（curvS 的末端，即与主段相接处）时：
%     k_end = (6/jps)^(1/3)
%
%   对于起始零速段（isEnd=false）：连接点在 u=1，伪时间 k = (6/jps)^(1/3)
%   对于终止零速段（isEnd=true） ：连接点在 u=0，伪时间 k = 0（对应反向时间）
%
% Inputs :
%   ctx   : 计算链上下文
%   curv  : 零速段曲线结构体（含 ConstJerk = 预计算的恒定跃度值）
%   isEnd : true = 零速终止段（从末端驶入零速）；false = 零速起始段（从零速驶出）
%
% Outputs :
%   vNorm  : 连接点处的速度范数（mm/s，标量）
%   atNorm : 连接点处的切向加速度范数（mm/s²，标量）
%

jps = curv.ConstJerk;   % 恒定跃度参数（u 空间的三阶导数常数）

% 确定连接点处的伪时间 k（零速端 k=0，自由端 k=k_end）
if( isEnd )
    % 终止零速段：连接点是 u=0（反向时间中 k=0 对应 u=1-u'=0，即原始参数起点）
    k  = 0;
else
    % 起始零速段：连接点是 u=1，对应伪时间 k_end = (6/jps)^(1/3)
    k   = ( 6 / jps )^( 1 / 3 );
end

% 用恒定跃度公式计算连接点处的参数及其各阶导数（对伪时间 k 的导数）
[ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );

% 在参数 u 处求曲线的位置和各阶参数导数
[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );

% 从参数导数和伪时间导数（ud, udd, uddd）计算物理速度向量 V 和加速度向量 A
% calcRVAJfromUWithoutCurv 用链式法则将参数空间导数转换为时间域物理量
[ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd, r0D, ...
                          r1D, r2D, r3D );

% 计算速度范数（标量速度）和切向加速度范数（沿切向的加速度分量）
% calcNormVNormAT 利用 r1D 方向分解 A 为切向分量
[ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
end
