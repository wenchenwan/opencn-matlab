function [ ctx, window, NWindow ] = feedratePlanningForceZeroStop( ctx, window, NWindow )
%#codegen
% feedratePlanningForceZeroStop : LP 优化不可行时的强制零速停顿恢复机制
%
% 【触发场景】
%   当进给速度 LP 优化求解失败（无可行解）时，说明当前窗口内存在无法满足的
%   约束（通常是窗口末端速度约束太紧，导致减速段太短无法将速度降到要求值）。
%
%   恢复策略：在当前窗口末尾强制插入一个零速停顿：
%     1. 将窗口最后一段（curv1）末端切出零速减速段（NZ），存入 zero_forced_buffer
%     2. 将下一段（curv2）起端切出零速加速段（ZN），存入 zero_forced_buffer
%     3. 重新取窗口（现在末端变为 NZ 段，构成自然边界）
%     4. 重新设置边界条件
%
% 【zero_forced_buffer 的作用】
%   buffer[1] = curvE（NZ 段，放在当前窗口末尾）
%   buffer[2] = curvS（ZN 段，放在下一个窗口开头）
%   这两段在 main FSM 的后续迭代中会被正确处理（分别作为新窗口的边界）。
%
% 【注意事项】
%   - 仅适用于 NN（普通-普通）场景，窗口首尾不能已经是零速段
%   - 强制零速后，加工精度不受影响（零速停顿由平滑阶段的过渡曲线保证 G2），
%     但节拍时间会增加（因为额外停顿）
%
% Inputs :
%   ctx     : 计算链上下文
%   window  : 当前优化窗口
%   NWindow : 窗口曲线数
%
% Outputs :
%   ctx     : 更新后的上下文（zero_forced=true，zero_forced_buffer 已填入）
%   window  : 重新取窗口（末尾追加 curvE）
%   NWindow : 更新后的窗口大小
%

% NN case : Optimization failed due to small coefficient, so force a stop
% （NN = 普通起始、普通终止，首尾均无零速段的场景）

curvQueue       = ctx.q_split;
ctx.zero_forced = true;   % 标记本次迭代强制插入了零速停顿

% 断言：第一次优化不应触发强制零速（k0=1 表示队列起始，无法回溯修改）
ocn_assert( ctx.k0 > 1, "Should not be called one the first set of curves", ...
    mfilename );

curv0           = window( 1 );
curv1           = window( NWindow );
ind1            = ctx.k0 + NWindow;   % curv1 在队列中的全局索引

% 断言当前窗口首尾均为普通段（非零速段）
msg = "Curve should be a Zero Stop";
ocn_assert( ~isAZeroStart( curv0 ), msg, mfilename );
ocn_assert( ~isAZeroEnd( curv1 ),   msg, mfilename );

% ── 步骤 1：在 curv1 末端切出零速减速段 ─────────────────────────────────
curv1.Info.zspdmode = ZSpdMode.NZ;   % 将 curv1 标记为零速终止
% cutZeroEnd 切出：curv1NN（主段）+ curv1NZ（零速减速尾段）
[ ~, curv1NN, curv1NZ ]     = cutZeroEnd( ctx,  curv1 );
ctx.zero_forced_buffer( 1 ) = curv1NZ;     % buffer[1]：零速减速尾段（NZ）
curvQueue.set( ind1, curv1NN );            % 将主段写回队列，替换原 curv1

% ── 步骤 2：在下一段 curv2 起端切出零速加速段 ───────────────────────────
ind2            = ind1 + 1;
if( ind2 <= curvQueue.size() )
    curv2       = ctx.q_split.get( ind2 );
    curv2.Info.zspdmode = ZSpdMode.ZN;   % 标记 curv2 为零速起始
    % cutZeroStart 切出：curv2ZN（零速加速头段）+ curv2NN（主段）
    [ ~, curv2ZN, curv2NN ]     = cutZeroStart( ctx, curv2 );
    ctx.zero_forced_buffer( 2 ) = curv2ZN;   % buffer[2]：零速加速头段（ZN）
    curvQueue.set( ind2, curv2NN );          % 将主段写回队列
else
    % 队列已到末尾：buffer[2] 置空
    ctx.zero_forced_buffer( 2 ) = constrCurvStructType;
end

% ── 步骤 3：重新获取优化窗口 ─────────────────────────────────────────────
% 此时 curv1NN（队列中的 ind1）末端仍是 NN，但紧随其后的 curv1NZ 在 buffer 中。
% feedratePlanningGetwindow 从 k0 重新取窗口，末端为 curv1NN（NN 段）。
[ window, NWindow ] = feedratePlanningGetwindow( ctx.k0, NWindow, curvQueue );

% 手动追加 zero_forced_buffer[1]（curvE=NZ）到窗口末尾，
% 使得窗口末段为 NZ，触发 feedratePlanningSetupCurves 的零速终止处理逻辑
window  = [ window, ctx.zero_forced_buffer( 1 ) ];
NWindow = NWindow + 1;

% ── 步骤 4：重新设置边界条件 ─────────────────────────────────────────────
% 此时窗口末端为 NZ 段，SetupCurves 将从中提取零速终止的边界约束
[ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
    ctx, window, NWindow );

ctx.q_split = curvQueue;
end
