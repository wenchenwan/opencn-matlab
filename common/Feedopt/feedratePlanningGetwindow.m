function [ window, NWindow ] = feedratePlanningGetwindow( k0, NHorz, q_curves )
%#codegen
% feedratePlanningGetwindow : 从曲线队列中提取一个滑动优化窗口
%
% 【滑动窗口机制】
%   进给速度优化采用滑动窗口（Receding Horizon）策略：
%   每次优化一个包含 NHorz 条曲线的窗口，然后将窗口向前滑动一步。
%   窗口内所有曲线的速度平方系数（v²(u)）联合优化，
%   以满足速度/加速度/跃度约束，同时保证相邻窗口之间的速度连续。
%
% 【窗口截断规则】
%   若在 NHorz 条曲线范围内遇到零速终止段（isAZeroEnd），
%   窗口在该段处截断（含该段）。原因：
%   - 零速停顿是窗口的自然边界（两侧速度均为零，相互解耦）
%   - 零速段之后的曲线不影响当前窗口的优化结果
%
% Inputs :
%   k0       : 当前窗口在 q_curves 队列中的起始索引
%   NHorz    : 窗口最大容量（曲线数量上限）
%   q_curves : 曲线段队列（q_split 输出）
%
% Outputs :
%   window  : 窗口内的曲线数组（长度 = NHorz，实际有效段为前 NWindow 个）
%   NWindow : 窗口内实际曲线数量（≤ NHorz）
%

% 预分配最大容量数组（codegen 要求固定大小）
window = repmat( constrCurvStructType, 1, NHorz );

% 窗口结束索引（不超过队列末尾）
kend = min( double( k0 + NHorz -1 ), q_curves.size );

ind = 0;

for curv_ind = k0 : int32( kend )
    ind = ind + 1;

    % 从队列取出曲线并存入窗口
    curv            = q_curves.get( curv_ind );
    window( ind )   = curv;

    % 遇到零速终止段则截断窗口（零速停顿是优化的自然边界）
    if( isAZeroEnd( curv ) ), break; end
end

NWindow = ind;
end
