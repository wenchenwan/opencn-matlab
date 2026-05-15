function ctx = initRobotPlan(cfg, robot_kin)
% initRobotPlan : 初始化 6-DOF 机器人轨迹规划上下文
%
% 以 initFeedoptPlan 为基础，覆盖运动学对象，并设置机器人模式标志。
% 调用方式：
%   cfg = RobotDefaultConfig(robot_params);
%   kin = RobotKinematics(cfg.dh_params, cfg.robot_config, cfg.q_lim);
%   ctx = initRobotPlan(cfg, kin);
%
% Inputs :
%   cfg       : 由 RobotDefaultConfig 生成的配置结构体
%   robot_kin : RobotKinematics 对象（已构造好的运动学适配层）
%
% Outputs :
%   ctx : 初始化完成的上下文结构体，包含：
%         - 所有 initFeedoptPlan 的标准字段（B 样条基、队列、FSM 状态等）
%         - ctx.kin       : 替换为 RobotKinematics 对象
%         - ctx.robot_mode: true（激活 EvalCurvStruct 中的机器人分支）

% ── 第一步：调用通用初始化（B 样条、队列、FSM 状态、控制变量）──
% initFeedoptPlan 中会调用 Kinematics(cfg.kin_type, cfg.kin_params)，
% 但 cfg.kin_type='robot6dof' 在原 Kinematics.m 中不存在，
% 因此必须在此之后立即覆盖 ctx.kin。
try
    ctx = initFeedoptPlan(cfg);
catch ME
    % initFeedoptPlan 可能因 kin_type='robot6dof' 不识别而报错
    % 这里捕获该错误，手动完成剩余初始化
    if contains(ME.message, 'robot6dof') || contains(ME.message, 'kin_type')
        % 使用已知可工作的占位运动学类型完成初始化
        cfg_tmp            = cfg;
        cfg_tmp.kin_type   = 'xyzbc_tt';   % 临时占位，不影响机器人模式
        cfg_tmp.kin_params = zeros(15, 1);
        ctx = initFeedoptPlan(cfg_tmp);
        ctx.cfg = cfg;  % 还原为真实配置（含 dh_params 等机器人字段）
    else
        rethrow(ME);
    end
end

% ── 第二步：覆盖运动学对象 ──
% 替换 initFeedoptPlan 中创建的 CNC 五轴运动学对象，
% 改用 RobotKinematics（实现了相同的 v_relative/joint 接口）。
ctx.kin = robot_kin;

% ── 第三步：设置机器人模式标志 ──
% EvalCurvStruct 在函数体开头检查此标志：
%   if isfield(ctx, 'robot_mode') && ctx.robot_mode → 调用 EvalRobotCurv
% 这样可以在不修改任何 common/ 内核文件（EvalCurvStruct 除外那 3 行）的前提下
% 实现机器人曲线求值的切换。
ctx.robot_mode = true;

end
