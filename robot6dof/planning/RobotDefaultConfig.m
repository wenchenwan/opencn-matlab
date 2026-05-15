function cfg = RobotDefaultConfig(robot_params)
% RobotDefaultConfig : 创建 6-DOF 工业机器人进给率优化配置结构体
%
% 以 FeedoptDefaultConfig 为基础，覆盖机器人专用字段。
% 调用方式：
%   params.vmax  = [rad/s × 6]
%   params.amax  = [rad/s² × 6]
%   params.jmax  = [rad/s³ × 6]
%   params.dt    = 时间步长（s），默认 1e-3
%   params.dh    = [6×4] DH 参数矩阵（标准 DH：[a, d, alpha, theta_offset]）
%   params.q_lim = [6×2] 关节限位 [q_min, q_max]（rad）
%   params.config = 'elbow_up' 或 'elbow_down'（默认 'elbow_up'）
%   cfg = RobotDefaultConfig(params)
%
% Inputs :
%   robot_params : 机器人参数结构体（见上述字段说明）
%
% Outputs :
%   cfg : 完整的配置结构体，可直接传入 initRobotPlan
%

% -------------------------------------------------------------------------
% 第一步：从 FeedoptDefaultConfig 获取通用默认值
% -------------------------------------------------------------------------
cfg = FeedoptDefaultConfig();

% -------------------------------------------------------------------------
% 第二步：覆盖轴配置——6-DOF 机器人全部激活
% -------------------------------------------------------------------------
% 所有 6 个关节均参与约束，无"旋转轴"与"平动轴"之分
% 注意：setMachineAxisInConfig 会将前 3 轴视为 Cart、后 3 轴视为 Rot，
%   但在机器人模式中，buildConstr 通过 robot_mode 标志绕过该分类，
%   indCart/indRot 仅在非机器人分支中用于坐标缩放。
cfg.maskTot    = logical([1, 1, 1, 1, 1, 1]);  % 全部 6 轴激活

% -------------------------------------------------------------------------
% 第三步：覆盖运动约束（关节空间，单位：rad/s, rad/s², rad/s³）
% -------------------------------------------------------------------------
if isfield(robot_params, 'vmax')
    cfg.vmax = robot_params.vmax(:)';   % 确保行向量，长度 6
else
    % UR5 典型关节速度限制（rad/s）
    cfg.vmax = [3.15, 3.15, 3.15, 3.20, 3.20, 3.20];
end

if isfield(robot_params, 'amax')
    cfg.amax = robot_params.amax(:)';
else
    % UR5 典型关节加速度限制（rad/s²）
    cfg.amax = [40, 40, 40, 40, 40, 40];
end

if isfield(robot_params, 'jmax')
    cfg.jmax = robot_params.jmax(:)';
else
    % 典型关节跃度限制（rad/s³）
    cfg.jmax = [400, 400, 400, 400, 400, 400];
end

% -------------------------------------------------------------------------
% 第四步：覆盖采样时间步长
% -------------------------------------------------------------------------
if isfield(robot_params, 'dt')
    cfg.dt = robot_params.dt;
else
    cfg.dt = 1e-3;  % 默认 1ms（1000Hz 输出）
end

% -------------------------------------------------------------------------
% 第五步：跳过 CNC 专用几何预处理阶段
% -------------------------------------------------------------------------
% 机器人路径无需尖点检测与段压缩；平滑可选（关节过渡圆化）
cfg.Cusp.Skip        = true;   % 跳过尖点检测（机器人路径无尖点概念）
cfg.Compressing.Skip = true;   % 跳过段压缩（机器人段已是最小粒度）
cfg.Smoothing.Skip   = false;  % 保留平滑：在关节路径点间可做 G2 过渡

% -------------------------------------------------------------------------
% 第六步：存储机器人特有参数（运动学和关节限位）
% -------------------------------------------------------------------------
if isfield(robot_params, 'dh')
    cfg.dh_params = robot_params.dh;       % [6×4] DH 参数
else
    % UR5 DH 参数默认值（标准 DH，单位：m/rad）
    % 列顺序：[a, d, alpha, theta_offset]
    cfg.dh_params = [
         0,      0.0892,  pi/2,   0;   % 关节 1
        -0.4250, 0,       0,      0;   % 关节 2
        -0.3922, 0,       0,      0;   % 关节 3
         0,      0.1093,  pi/2,   0;   % 关节 4
         0,      0.0948, -pi/2,   0;   % 关节 5
         0,      0.0823,  0,      0;   % 关节 6
    ];
end

if isfield(robot_params, 'q_lim')
    cfg.q_lim = robot_params.q_lim;       % [6×2] 关节限位 [q_min, q_max]
else
    % UR5 关节限位（±360° 转换为 rad）
    cfg.q_lim = repmat([-2*pi, 2*pi], 6, 1);
end

if isfield(robot_params, 'config')
    cfg.robot_config = robot_params.config;  % 'elbow_up' 或 'elbow_down'
else
    cfg.robot_config = 'elbow_up';
end

% -------------------------------------------------------------------------
% 第七步：覆盖运动学类型（标记为机器人模式，绕过 CNC 运动学函数）
% -------------------------------------------------------------------------
cfg.kin_type   = 'robot6dof';
cfg.kin_params = zeros(15, 1);  % 占位，机器人模式中不使用 CNC 偏置参数

% -------------------------------------------------------------------------
% 第八步：重新计算轴派生字段（6 轴全激活）
% -------------------------------------------------------------------------
% 注意：setMachineAxisInConfig 将 maskTot 前 3 轴映射为 Cart（平动）、
%   后 3 轴映射为 Rot（旋转），并据此设置 indCart/indRot/NCart/NRot。
%   机器人模式中 buildConstr 不依赖 Cart/Rot 分类做坐标变换，
%   该调用仅用于确保 NumberAxis=6、D=ones(6,1) 等字段正确。
cfg = setMachineAxisInConfig(cfg, cfg.maskTot);

end
