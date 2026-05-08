function [ k_vec ] = constJerkTime( pseudoJerk, u_vec, isEnd )
% constJerkTime : 恒定跃度速度曲线的逆运算——由路径参数 u 计算对应的伪时间 k
%
% 【逆函数推导】
%   constJerkU 正向定义：u(k) = jps · k³ / 6
%   反解 k：
%     k = (6·u / jps)^(1/3)
%
%   对于终止零速段（isEnd=true），时间和位置均已反向：
%     先将 u 翻转：u' = 1 - u（还原到正向参数）
%     再计算 k'  = (6·u' / jps)^(1/3)
%     最后翻转时间：k = k_max - k'（还原到反向时间轴）
%
% 【用途】
%   在插补阶段，已知当前路径参数 u_vec，需要计算对应的伪时间 k，
%   进而通过 constJerkU 计算该时刻的速度和加速度（用于 setpoint 生成）。
%
% Inputs :
%   pseudoJerk : 恒定跃度值（jps，标量或列向量）
%   u_vec      : 路径参数向量（行向量）
%   isEnd      : true = 终止零速段（时间反向）；false = 起始零速段
%
% Outputs :
%   k_vec      : 对应的伪时间向量（与 u_vec 同形）
%

if( coder.target( "MATLAB" ) )
    % 统一方向：jps 列向量，u_vec 行向量（便于广播）
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( u_vec ) ),   u_vec = u_vec'; end
end

if( isEnd )
    % 终止零速段：先将 u 翻转为正向参数
    u_vec = 1 - u_vec;
end

% 正向逆运算：k = (6u/jps)^(1/3)
k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );

if( isEnd )
    % 终止零速段：将时间轴反向还原
    k_max   = ( 6 / pseudoJerk )^( 1 / 3 );
    k_vec   = k_max - k_vec;
end

end
