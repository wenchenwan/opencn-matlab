function [ k_vec ] = constJerkTime( pseudoJerk, u_vec, isEnd )
% constJerkTime : 恒定跃度速度曲线的逆运算——由路径参数 u 计算对应的伪时间 k
%
% 【逆函数推导】
%   constJerkU 正向定义：u(k) = jps · k³ / 6
%   反解 k：
%     k = (6·u / jps)^(1/3)
%
% 【终止零速段的对称处理（isEnd=true）】
%   终止零速段是起始零速段在时间轴上的镜像：
%     起始段：u=0（速度=0）→ u=1（速度最大），k 从 0 增大
%     终止段：u=0（速度最大）→ u=1（速度=0），k 从 k_max 减小
%
%   两段在物理上完全对称，因此利用对称性复用正向公式，分三步处理：
%     步骤1：u' = 1 - u          把终止段 u 翻转为等效正向参数
%                                  u=1（末端停止）→ u'=0，u=0（入口）→ u'=1
%     步骤2：k' = (6u'/jps)^(1/3) 在正向坐标系里套用起始段逆公式
%     步骤3：k  = k_max - k'     把正向时间翻回终止段实际时间
%                                  k'=0 → k=k_max（入口，速度最大）
%                                  k'=k_max → k=0（末端，速度=0）
%
%   数轴对照：
%     正向（起始段） k':  0 ──────────────→ k_max   u': 0→1
%                              ↕ 镜像（k = k_max - k'）
%     终止段        k:  k_max ←────────────  0       u:  0→1
%
%   本质：避免单独推导反向逆函数，利用对称性统一为一套计算流程。
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
    % 步骤1：翻转位置参数，将终止段 u 映射为等效正向参数 u'=1-u
    u_vec = 1 - u_vec;
end

% 步骤2（或起始段直接计算）：正向逆运算 k = (6u/jps)^(1/3)
k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );

if( isEnd )
    % 步骤3：翻转时间轴，k_max 为整段曲线的最大伪时间（u=1 处对应的 k 值）
    % k = k_max - k'，将正向时间还原为终止段实际时间
    k_max   = ( 6 / pseudoJerk )^( 1 / 3 );  % 即 u'=1 时的正向 k 值
    k_vec   = k_max - k_vec;
end

end
