function [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
    ctx, window, NWindow )
%#codegen
% feedratePlanningSetupCurves : 设置优化窗口的边界条件（速度和加速度约束）
%
% 【窗口结构与边界条件】
%   从 feedratePlanningGetwindow 获取的窗口可能包含零速起始/终止段：
%
%   ┌──────────────────────────────────────────────────────────────────┐
%   │ 窗口布局示例：                                                    │
%   │   [curvS_ZN] | [曲线1] [曲线2] ... [曲线N] | [curvE_NZ]           │
%   │      ↑                                              ↑            │
%   │   零速起始段（从队列中剥离，仅用于计算边界条件）  零速终止段（同上）   │
%   └──────────────────────────────────────────────────────────────────┘
%
%   - 零速段（curvS/curvE）已在 splitCurvStruct 阶段用恒定跃度速度曲线描述
%   - 它们不参与 LP 优化（不是决策变量），只提供边界条件
%   - 本函数将它们从窗口中剥离，并计算连接点处的速度/加速度约束
%
% 【边界条件类型】
%   zero_start=true：窗口左侧有零速起始段（曲线从零速出发）
%     v_0  = 连接点处的速度范数（= LP 问题在 u=0 处的速度初值约束）
%     at_0 = 连接点处的切向加速度范数
%
%   zero_end=true：窗口右侧有零速终止段（曲线减速到零速）
%     v_1  = 连接点处的速度范数（取负值存储，适配 LP 约束形式）
%     at_1 = 连接点处的切向加速度范数（同样取负）
%
%   zero_start=false：窗口左侧无零速起始段（中间段，速度连续性传递）
%     v_0  和 at_0 不在本函数中更新，沿用 ctx 中上一窗口 LP 写入的值：
%       FeedratePlanning_LP 在每次求解成功后（非 zero_start 路径）执行：
%         ctx.v_0  = sqrt( continuity * Coeff(:,1) 的速度项 )
%         ctx.at_0 = continuity * Coeff(:,1) 的切向加速度项
%       含义：当前窗口第一段的末端速度/加速度 → 传给下一窗口作起始约束，
%       保证相邻窗口之间的速度和加速度连续（跨窗口 C¹ 连续性）。
%     整个优化开始时的初始值来自 cfg.v_0 / cfg.at_0（通常为 0，即从静止出发）。
%
%   zero_end=false：窗口右侧是普通曲线（速度连续即可）
%     v_1  = -cfg.v_1（配置中预设的终端速度约束）
%     at_1 = -cfg.at_1
%
% Inputs / Outputs :
%   ctx     : 计算链上下文（zero_start / zero_end / v_0 / at_0 / v_1 / at_1 更新）
%   window  : 窗口内的曲线数组（前后零速段被剥离后的主段数组）
%   NWindow : 实际参与优化的曲线数量（剥离零速段后减小）
%

% 获取窗口首尾两条曲线
first = window( 1 );
last  = window( NWindow );

% ── 处理零速起始段 ────────────────────────────────────────────────────────
if ( isAZeroStart( first ) )
    % 首段是零速起始段：从窗口中剥离，NWindow 减 1
    ctx.zero_start  = true;
    window          = window( 2 : end );
    NWindow         = NWindow -1;
else
    ctx.zero_start  = false;
end

% ── 处理零速终止段 ────────────────────────────────────────────────────────
if( isAZeroEnd( last ) )
    % 末段是零速终止段：从窗口中剥离，NWindow 减 1
    ctx.zero_end    = true;
    NWindow         = NWindow -1;
    window          = window( 1 : end-1 );
else
    ctx.zero_end    = false;
end

% ── 计算边界条件 ──────────────────────────────────────────────────────────
if( ctx.zero_start )
    % 在起始零速段与主段的连接点（u=1 of curvS）处计算速度和加速度
    % isEnd=false 表示从起点出发的零速加速段
    [ v_0, at_0 ]   = calcZeroConstraints( ctx, first, false );
    ctx.v_0         = v_0;
    ctx.at_0        = at_0;
end

if( ctx.zero_end )
    % 在主段与终止零速段的连接点（u=0 of curvE）处计算速度和加速度
    % 取负值：LP 形式中右端边界条件以 -v_1 形式参与约束
    [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true );
    ctx.v_1         = -v_1;
    ctx.at_1        = -at_1;
else
    % 无零速终止段：使用配置中预设的终端速度约束
    ctx.v_1         = -ctx.cfg.v_1;
    ctx.at_1        = -ctx.cfg.at_1;
end

end
