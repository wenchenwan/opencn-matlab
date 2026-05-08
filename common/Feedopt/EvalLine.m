function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, mask )
%#codegen
% EvalLine : 在给定参数点处求直线段的位置和各阶参数导数
%
% 直线参数化（均匀，u ∈ [0,1]）：
%   r(u) = P0·(1-u) + P1·u = P0 + (P1-P0)·u
%
% 导数：
%   r'(u)  = P1 - P0   （常向量，与 u 无关）
%   r''(u) = 0
%   r'''(u)= 0
%
% 弧长均匀性：‖r'(u)‖ = ‖P1-P0‖ = const，这是 LengthCurv 中
%   Line/Helix 可以用 ‖r'(u0)‖×(u1-u0) 解析计算弧长的原因。
%
% Inputs :
%   CurvStruct : 曲线结构体（R0=起点，R1=终点，全轴坐标）
%   u_vec      : 全局参数向量（经 a_param/b_param 映射后传入）
%   mask       : 轴掩码（logical 向量，选出需要求值的轴）
%
% Outputs :
%   r0D : [sum(mask) × N] 位置
%   r1D : [sum(mask) × N] 一阶导（各列相同，= P1-P0）
%   r2D : [sum(mask) × N] 二阶导（全零）
%   r3D : [sum(mask) × N] 三阶导（全零）
%

if ~coder.target('MATLAB')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.inline('never')
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
end

P0 = CurvStruct.R0( mask );   % 起点（激活轴）
P1 = CurvStruct.R1( mask );   % 终点（激活轴）
nD = sum( mask );              % 激活轴数量

% 位置：线性插值 r(u) = P0 + (P1-P0)·u
r0D = P1 .* u_vec + P0 .* ( 1 - u_vec );

% 一阶导：常向量，广播到 N 列
N   = length( u_vec );
r1D = repmat( P1 - P0, 1, N );

% 二阶、三阶导均为零（直线曲率为零）
r2D = zeros( nD, N );
r3D = zeros( nD, N );
