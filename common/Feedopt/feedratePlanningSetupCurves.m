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
% 【ctx.v_1 / ctx.at_1 的完整生命周期（三个来源）】
%
%   来源1 — 初始化（initFeedoptPlan）：
%     ctx.v_1 = cfg.v_1 = 0;  ctx.at_1 = cfg.at_1 = 0
%     整个路径规划开始时设为零（默认终端静止）。
%
%   来源2 — 本函数（feedratePlanningSetupCurves）：
%     zero_end=true：
%       ctx.v_1 = -v_1;  ctx.at_1 = -at_1
%       （v_1、at_1 来自 calcZeroConstraints，即恒定跃度曲线的连接点速度/加速度）
%     zero_end=false（普通中间窗口）：
%       ctx.v_1 = -cfg.v_1 = 0;  ctx.at_1 = -cfg.at_1 = 0
%       ← MPC"保守停止"策略：LP 假设窗口末端需要减速到零；
%         但实际上只提交第一段系数，下一个窗口重新规划，
%         因此整体轨迹在窗口边界处是平滑连续的，并不会真正停下。
%
%   来源3 — LP 约束松弛（FeedratePlanning_LP / relax_intial_constraints）：
%     LP 求解失败时，将零速曲线的 ConstJerk 减半重试。
%     松弛成功后用新的连接点速度更新：
%       ctx.v_1 = -vNorm;  ctx.at_1 = -atNorm
%     这保证写入 q_split 的曲线与 LP 约束中的边界条件始终一致。
%
% 【负号约定：为何 ctx.v_1 / ctx.at_1 存储为负值？】
%
%   buildConstr.m 构造 Aeq 时，末端边界行由 mask_continuity = [-1, -1] 决定：
%
%     beq([end-1, end]) = [v_1^2; at_1] .* mask_continuity
%                       = [-ctx.v_1^2;  ctx.at_1] * (-1)    （两处负号相消）
%                       = [v_actual^2; at_actual]
%
%   因此 ctx.v_1 = -v_actual（以正值的负数存储），和 mask_continuity 的 -1
%   结合后恢复出正确的物理约束（末端速度平方 = v_actual²）。
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
    % 在主段与终止零速段的连接点（u=0 of curvE）处计算速度和加速度。
    % isEnd=true → calcZeroConstraints 以 k=0 为连接点（恒定跃度曲线起始端）。
    % 取负值存储：ctx.v_1 = -v_actual，与 mask_continuity=[-1,-1] 组合后恢复正确约束
    %   见 buildConstr.m: beq(end-1) = v_1^2 * mask(end-1) = (-v_actual)^2 * (-1) = -v_actual^2 ✗
    %   实际写法：beq(end-1) = ctx.v_1^2 → 注意 LP 中速度平方已是正值，负号在 ctx.v_1 层。
    [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true );
    ctx.v_1         = -v_1;    % 负号适配 buildConstr 的 mask_continuity 符号约定
    ctx.at_1        = -at_1;
else
    % 无零速终止段（普通中间窗口）：采用 MPC "保守停止" 策略。
    % cfg.v_1=0 令 LP 假设窗口末端必须减速到零，但实际只提交第一段系数，
    % 下一窗口重新规划，整体轨迹在窗口边界平滑衔接而不会真正停止。
    ctx.v_1         = -ctx.cfg.v_1;   % = 0（保守终端约束）
    ctx.at_1        = -ctx.cfg.at_1;  % = 0
end

end
