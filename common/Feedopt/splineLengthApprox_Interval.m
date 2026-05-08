function [ L ] = splineLengthApprox_Interval( cfg, spline, u0, u1, isEnd )
%#codegen
% splineLengthApprox_Interval : 用 GL-5 积分计算 [u0, u1] 区间的弧长
%
% 弧长公式：L = ∫_{u0}^{u1} ‖r'(u)‖ du
% 无解析表达式，用 Gauss-Legendre 数值积分（5 个节点）近似。
%
% GL 积分原理：
%   将 [-1,1] 上的 GL 节点 GL_X 和权重 GL_W 线性映射到 [u0, u1]：
%       uvec = (u0*(1-GL_X) + u1*(1+GL_X)) / 2
%   然后加权求和：
%       L ≈ ‖r'(uvec)‖ · GL_W · (u1-u0)/2
%
% IMPORTANT：u0 和 u1 应在同一个 B 样条节点区间内，
%   跨区间请用 SplineLengthApproxGL_tot 或 splineLength。
%
% isEnd=true 时坐标翻转（由 splineLengthFindU 传入，外部无需关心）。
%
% Inputs :
%   cfg    : 配置结构体（含预存的 GaussLegendreX、GaussLegendreW）
%   spline : B 样条结构体
%   u0     : 积分下限（全局参数）
%   u1     : 积分上限（全局参数）
%   isEnd  : true = 翻转坐标后积分（配合 isEnd 镜像使用）
%
% Outputs :
%   L : 弧长近似值（mm）
%

GL_X = cfg.GaussLegendreX;
GL_W = cfg.GaussLegendreW;

% isEnd 镜像翻转：将镜像坐标下的 [u0,u1] 还原为原始坐标
if( isEnd )
    a  = 1 - u0;
    u0 = 1 - u1;
    u1 = a;
end

% 将 [-1,1] 上的 GL 节点线性映射到 [u0, u1]
uvec = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2 ).';

% 求各 GL 节点处的参数导数 r'(u)，再取模 ‖r'(u)‖
[ ~, r1D ] = EvalBSpline( spline, uvec );
r1Dnorm    = MyNorm( r1D );

% GL 积分：L = Σ w_k · ‖r'(u_k)‖ · (u1-u0)/2
L = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
L = L( 1 ); % 标量化（满足 Matlab Coder 要求）
