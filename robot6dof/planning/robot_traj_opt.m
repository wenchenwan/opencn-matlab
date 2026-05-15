function result = robot_traj_opt(waypoints, robot_params, mode, varargin)
% robot_traj_opt : 6-DOF 工业机器人时间最优轨迹规划主入口
%
% 基于 OpenCN LP 进给率优化框架（buildConstr + FeedratePlanning_LP），
% 对机器人关节/笛卡尔路径做时间最优处理，输出满足速度、加速度、跃度约束的轨迹。
%
% ─────────────────────────────────────────────────────────────────────────
% 【基本用法】
%
%   关节空间模式（mode='joint'）：
%     waypoints : [6×N] 关节角矩阵，每列一个路径点（rad）
%     result 包含时间序列的关节角 q(t)、速度 qd(t)、加速度 qdd(t)
%
%   笛卡尔空间模式（mode='cartesian'）：
%     waypoints : [6×N] TCP 位姿矩阵，每列 [px;py;pz;rx;ry;rz]（m + ZYX Euler rad）
%     result 包含时间序列的关节角 q(t)（需内部 IK）
%
%   圆弧模式（mode='arc'）：
%     waypoints : struct 数组，每个元素包含 p0/p_mid/p1/orient0/orient1 字段
%
% ─────────────────────────────────────────────────────────────────────────
% Inputs :
%   waypoints     : [6×N] 路径点矩阵（关节或笛卡尔），或 struct 数组（圆弧模式）
%   robot_params  : 机器人参数结构体（见 RobotDefaultConfig 说明）
%     .vmax       : [6×1] 关节速度上限（rad/s）
%     .amax       : [6×1] 关节加速度上限（rad/s²）
%     .jmax       : [6×1] 关节跃度上限（rad/s³）
%     .dt         : 重采样时间步长（s，默认 1e-3）
%     .dh         : [6×4] DH 参数矩阵
%     .q_lim      : [6×2] 关节限位 [q_min, q_max]（rad）
%     .config     : 'elbow_up'/'elbow_down'（默认 'elbow_up'）
%     .feedrate   : 进给率上限（rad/s 或 m/s），默认 = min(vmax)
%   mode          : 'joint'（关节空间）| 'cartesian'（笛卡尔直线）| 'arc'（圆弧）
%   varargin{1}   : 可选 feedrate 覆盖值（若不在 robot_params 中指定）
%
% Outputs :
%   result : 结构体，包含：
%     .t    : [1×T] 时间向量（s）
%     .q    : [6×T] 关节角轨迹（rad）
%     .qd   : [6×T] 关节速度轨迹（rad/s）
%     .qdd  : [6×T] 关节加速度轨迹（rad/s²）
%     .ctx  : 上下文（调试用，含 q_opt 队列）
%     .raw  : 临时文件路径（重采样原始数据）

% ── 参数预处理 ──
if ~isfield(robot_params, 'feedrate')
    if isfield(robot_params, 'vmax')
        robot_params.feedrate = min(robot_params.vmax);
    else
        robot_params.feedrate = 1.0;  % 默认 1 rad/s（关节空间）
    end
end

if nargin >= 4 && ~isempty(varargin{1})
    robot_params.feedrate = varargin{1};
end

% ─────────────────────────────────────────────────────────────────────────
% 第一阶段：初始化
% ─────────────────────────────────────────────────────────────────────────
cfg = RobotDefaultConfig(robot_params);
kin = RobotKinematics(cfg.dh_params, cfg.robot_config, cfg.q_lim);
ctx = initRobotPlan(cfg, kin);

% ─────────────────────────────────────────────────────────────────────────
% 第二阶段：构造曲线段数组
% ─────────────────────────────────────────────────────────────────────────
switch lower(mode)

    case 'joint'
        % 关节空间直线段：相邻路径点之间用直线连接（关节角线性插值）
        CurvArray = build_joint_curves(waypoints, robot_params.feedrate);

    case 'cartesian'
        % 笛卡尔空间直线段：TCP 路径点之间的空间直线
        CurvArray = build_cartesian_curves(waypoints, robot_params.feedrate);

    case 'arc'
        % 圆弧段：struct 数组，每个元素为一个圆弧
        CurvArray = build_arc_curves(waypoints, robot_params.feedrate);

    otherwise
        error('robot_traj_opt: 不支持的 mode = "%s"（支持：joint/cartesian/arc）', mode);
end

% ─────────────────────────────────────────────────────────────────────────
% 第三阶段：标记首末段零速边界条件
% ─────────────────────────────────────────────────────────────────────────
n_segs = length(CurvArray);

if n_segs == 0
    error('robot_traj_opt: 路径点不足（至少需要 2 个点）');
end

% 首段：零速起始（ZN）
CurvArray(1).Info.zspdmode = ZSpdMode.ZN;
% 末段：零速结束（NZ）
CurvArray(end).Info.zspdmode = ZSpdMode.NZ;
% 仅一段时：同时零速起末（ZZ）
if n_segs == 1
    CurvArray(1).Info.zspdmode = ZSpdMode.ZZ;
end

% ─────────────────────────────────────────────────────────────────────────
% 第四阶段：将曲线段注入 q_gcode 队列，跳过 G-code 解析阶段
% ─────────────────────────────────────────────────────────────────────────
for k = 1:n_segs
    ctx.q_gcode.push(CurvArray(k));
end

% ─────────────────────────────────────────────────────────────────────────
% 第五阶段：从 Check 阶段开始运行 FSM（跳过 GCode 解析阶段）
% ─────────────────────────────────────────────────────────────────────────
% 直接将状态设为 Check（跳过 Init → GCode），因为曲线已手动注入 q_gcode
ctx.op = Fopt.Check;
ctx    = FeedoptPlanRun(ctx);

% ─────────────────────────────────────────────────────────────────────────
% 第六阶段：重采样——将 LP 系数转换为时间序列轨迹
% ─────────────────────────────────────────────────────────────────────────
tmp_file = tempname;
tmp_file = [tmp_file, '.csv'];

resample2file(ctx, tmp_file);

% ─────────────────────────────────────────────────────────────────────────
% 第七阶段：加载结果并打包到输出结构体
% ─────────────────────────────────────────────────────────────────────────
result = load_robot_result(tmp_file, cfg);
result.ctx = ctx;
result.raw = tmp_file;

end


% ═════════════════════════════════════════════════════════════════════════
%  辅助函数：构造关节空间直线段数组
% ═════════════════════════════════════════════════════════════════════════
function CurvArray = build_joint_curves(waypoints, feedrate)
% waypoints : [6×N]，每列一个路径点（关节角 rad）
% CurvArray : 1×(N-1) 曲线结构体数组（直线段，TRAFO=false）

N = size(waypoints, 2);
if N < 2
    error('build_joint_curves: 至少需要 2 个路径点');
end

% 预分配（使用第一段初始化数组类型）
CurvArray = repmat(RobotCurvStruct(CurveType.Line, ...
    waypoints(:,1), waypoints(:,2), feedrate, false), 1, N-1);

for k = 1:N-1
    CurvArray(k) = RobotCurvStruct(CurveType.Line, ...
        waypoints(:, k), waypoints(:, k+1), feedrate, false);
end

end


% ═════════════════════════════════════════════════════════════════════════
%  辅助函数：构造笛卡尔空间直线段数组
% ═════════════════════════════════════════════════════════════════════════
function CurvArray = build_cartesian_curves(waypoints, feedrate)
% waypoints : [6×N]，每列 [px;py;pz;rx;ry;rz]（m + ZYX Euler rad）
% CurvArray : 1×(N-1) 曲线结构体数组（直线段，TRAFO=true）

N = size(waypoints, 2);
if N < 2
    error('build_cartesian_curves: 至少需要 2 个路径点');
end

CurvArray = repmat(RobotCurvStruct(CurveType.Line, ...
    waypoints(:,1), waypoints(:,2), feedrate, true), 1, N-1);

for k = 1:N-1
    CurvArray(k) = RobotCurvStruct(CurveType.Line, ...
        waypoints(:, k), waypoints(:, k+1), feedrate, true);
end

end


% ═════════════════════════════════════════════════════════════════════════
%  辅助函数：构造圆弧段数组
% ═════════════════════════════════════════════════════════════════════════
function CurvArray = build_arc_curves(arc_specs, feedrate)
% arc_specs : struct 数组，每个元素包含：
%   .p0, .p_mid, .p1     : [3×1] 三个空间位置（m）
%   .orient0, .orient1   : [3×1] 起末姿态（ZYX Euler rad）
%   .feedrate            : 可选，覆盖全局 feedrate

n = length(arc_specs);
if n < 1
    error('build_arc_curves: 至少需要 1 个圆弧段');
end

CurvArray = repmat(RobotCurvStruct(CurveType.Line, ...
    zeros(6,1), zeros(6,1), feedrate, true), 1, n);

for k = 1:n
    spec = arc_specs(k);
    fr_k = feedrate;
    if isfield(spec, 'feedrate') && ~isempty(spec.feedrate)
        fr_k = spec.feedrate;
    end
    CurvArray(k) = RobotArcSegment(spec.p0, spec.p_mid, spec.p1, ...
        spec.orient0, spec.orient1, fr_k, true);
end

end


% ═════════════════════════════════════════════════════════════════════════
%  辅助函数：从 CSV 文件加载重采样结果
% ═════════════════════════════════════════════════════════════════════════
function result = load_robot_result(csv_file, cfg)
% 读取 resample2file 输出的 CSV，提取时间、关节角、速度、加速度

if ~exist(csv_file, 'file')
    error('load_robot_result: 结果文件不存在：%s', csv_file);
end

% CSV 格式：[t, u_global, f_norm, feed, cf, r(6轴)', a(6轴)', j(6轴)', ...]
raw = readmatrix(csv_file);

if isempty(raw)
    error('load_robot_result: 结果文件为空');
end

n_axis = cfg.NumberAxis;   % = 6

% 列布局（参考 resample2file 输出格式说明）
% 列 1     : 时间步编号 t
% 列 2     : u_global
% 列 3     : f_norm
% 列 4     : feed
% 列 5     : cf
% 列 6~11  : r（位置/关节角）
% 列 12~17 : a（加速度）
% 列 18~23 : j（跃度）
col_r_start = 6;
col_a_start = col_r_start + n_axis;
col_j_start = col_a_start + n_axis;

T = size(raw, 1);

result.t   = (0:T-1) * cfg.dt;
result.q   = raw(:, col_r_start   : col_r_start + n_axis - 1)';
result.qd  = raw(:, col_a_start   : col_a_start + n_axis - 1)';  % 注意：列名是 a（加速度），但对应 v
result.qdd = raw(:, col_j_start   : col_j_start + n_axis - 1)';

% 实际上 resample2file 输出的 r/a/j 对应物理量 [位置, 速度, 加速度]
% 重新映射到正确语义名称
result.pos = result.q;    % 位置（关节角或笛卡尔位姿）
result.vel = result.qd;   % 速度
result.acc = result.qdd;  % 加速度

end
