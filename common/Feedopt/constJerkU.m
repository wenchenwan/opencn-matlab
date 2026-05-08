function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, forceLimits )
% constJerkU : 恒定跃度速度曲线——由伪时间 k 计算路径参数 u 及其各阶导数
%
% 【恒定跃度速度曲线的推导】
%   "恒定跃度"指 u 对伪时间 k 的三阶导数为常数 jps（pseudoJerk）：
%     u'''(k) = jps（常数）
%   积分三次（初始条件均为零：u(0)=0, u'(0)=0, u''(0)=0）：
%     u''(k) = jps · k
%     u'(k)  = jps · k² / 2
%     u(k)   = jps · k³ / 6
%
%   "伪时间" k 不是物理时间，而是规范化参数（量纲：[1/unit^(1/3)]），
%   使得 u(k_end) = 1 时有 k_end = (6/jps)^(1/3)。
%
%   速度曲线特性：
%   - 从零速出发（u=0, u'=0），速度随 k² 增长（平方加速）
%   - 只有起点处速度和加速度为零，在段末端（u=1）速度/加速度均不为零
%   - 终止零速段（isEnd=true）将时间反向，使末端（u=1）处速度和加速度为零
%
% 【isEnd=true 的时间反向处理】
%   为了在曲线终点（u=1）实现零速，将时间轴反向：
%     k_max = (6/jps)^(1/3)（u=1 对应的最大时间）
%     k_rev = k_max - k_vec  （反向时间）
%   然后计算正向 u'(k_rev) 后再翻转：
%     u(k)    = 1 - jps·k_rev³/6   → 从 1 倒退到 0
%     u'(k)   = u'_fwd(k_rev)      → 速度不变号（始终 ≥ 0）
%     u''(k)  = -u''_fwd(k_rev)    → 加速度取反（减速阶段）
%     u'''(k) = jps                 → 跃度不变（始终为正）
%
% Inputs :
%   pseudoJerk  : [N×1] 恒定跃度值（N 个轴或 N 个曲线的 jps，列向量）
%   k_vec       : [1×M] 伪时间向量（行向量）
%   isEnd       : (bool) true = 终止零速段（时间反向）；false = 起始零速段
%   forceLimits : (bool) true = 强制将 u 夹到 [0,1]（防止数值溢出）
%
% Outputs :
%   u    : [N×M] 路径参数
%   ud   : [N×M] u 对 k 的一阶导（参数速度）
%   udd  : [N×M] u 对 k 的二阶导（参数加速度）
%   uddd : [N×M] u 对 k 的三阶导（恒等于 pseudoJerk）
%

if( coder.target( "MATLAB" ) )
    % 统一向量方向：jps 为列向量，k_vec 为行向量（便于广播计算 N×M 矩阵）
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( k_vec ) ),   k_vec = k_vec'; end
end

if( isEnd )
    % 时间反向：k_rev = k_max - k_vec，使末端（k=0 → k_rev=k_max → u=1）为零速
    k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_vec  = k_max - k_vec;
end

% ── 恒定跃度公式（正向）────────────────────────────────────────────────────
% u'''(k) = jps
uddd    = pseudoJerk .* ones( size( k_vec ) );
% u''(k) = jps · k
udd     = pseudoJerk .* k_vec;
% u'(k)  = jps · k² / 2
ud      = pseudoJerk .* k_vec .^2 / 2;
% u(k)   = jps · k³ / 6
u       = pseudoJerk .* k_vec .^3 / 6;

if( forceLimits )
    % 防止数值误差导致 u 越出 [0,1]（理论上恰好在边界内）
    u( u > 1 ) = 1;
    u( u < 0 ) = 0;
end

if( isEnd )
    % 翻转位置和加速度（时间反向的链式法则效果）
    u    = 1 - u;      % 从 1 倒退到 0
    ud   = ud;         % 速度方向不变（du/dk 保持正值）
    udd  = -udd;       % 加速度取反（减速阶段）
    uddd = uddd;       % 跃度符号不变（始终正向）
end

end
