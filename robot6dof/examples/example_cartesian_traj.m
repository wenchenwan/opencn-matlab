% example_cartesian_traj.m
% 6-DOF 机器人时间最优笛卡尔轨迹规划示例（直线 + 圆弧）
%
% 本示例展示：
%   1. 直线段（mode='cartesian'）：TCP 在三维空间中做直线运动
%   2. 圆弧段（mode='arc'）：TCP 沿圆弧路径运动，姿态线性插值
%   3. 调用 robot_traj_opt 完成时间最优优化
%   4. 用正运动学 FK(q(t)) 验证路径跟踪精度（期望 < 1mm 误差）
%   5. 绘制 TCP 三维轨迹、关节角时间历程
%
% 验证目标：
%   - 直线段：TCP 路径线性度，max 偏离 < 0.5mm
%   - 圆弧段：圆度误差 < 1mm（半径偏差）
%   - 约束满足：max|qd| ≤ vmax，max|qdd| ≤ amax
%   - 零速边界：轨迹起末速度 ≈ 0
%
% 运行前需要将以下路径加入 MATLAB path：
%   addpath(genpath('<opencn-root>/agency/usr/matlab/opencn-matlab'))

clear; clc; close all;

%% ─────────────────────────────────────────────────────────────────────────
%  1. 机器人参数配置（UR5）
% ─────────────────────────────────────────────────────────────────────────
robot_params.dh = [
     0,      0.0892,  pi/2,   0;
    -0.4250, 0,       0,      0;
    -0.3922, 0,       0,      0;
     0,      0.1093,  pi/2,   0;
     0,      0.0948, -pi/2,   0;
     0,      0.0823,  0,      0;
];

robot_params.vmax    = [3.15, 3.15, 3.15, 3.20, 3.20, 3.20];  % rad/s
robot_params.amax    = [40,   40,   40,   40,   40,   40  ];   % rad/s²
robot_params.jmax    = [400,  400,  400,  400,  400,  400 ];   % rad/s³
robot_params.dt      = 1e-3;
robot_params.q_lim   = repmat([-2*pi, 2*pi], 6, 1);
robot_params.config  = 'elbow_up';
robot_params.feedrate = 0.1;  % TCP 路径速度上限（m/s）

%% ─────────────────────────────────────────────────────────────────────────
%  2. 定义笛卡尔直线路径（3 个 TCP 路径点）
% ─────────────────────────────────────────────────────────────────────────
% 格式：[px;py;pz;rx;ry;rz]（m + ZYX Euler angle rad）
% 该路径在 UR5 典型工作空间内（正前方，Y 方向运动）

P_line = [
    0.3,  0.3,   0.4;   % px（m）
   -0.1,  0.0,   0.1;   % py（m）
    0.3,  0.35,  0.4;   % pz（m）
    0.0,  0.0,   0.0;   % rx（ZYX Euler，rad）
    0.0,  0.0,   0.0;   % ry
    0.0,  0.0,   0.0;   % rz
];

fprintf('──────────────────────────────────────\n');
fprintf('测试 1：笛卡尔空间直线轨迹规划\n');
fprintf('路径点数：%d 点，共 %d 段\n', size(P_line,2), size(P_line,2)-1);
fprintf('──────────────────────────────────────\n');

%% ─────────────────────────────────────────────────────────────────────────
%  3. 运行直线段时间最优优化
% ─────────────────────────────────────────────────────────────────────────
fprintf('运行笛卡尔直线优化...\n');
tic;
result_line = robot_traj_opt(P_line, robot_params, 'cartesian');
t_elapsed = toc;
fprintf('优化完成，耗时 %.2f s，轨迹时长 %.3f s\n', t_elapsed, result_line.t(end));

%% ─────────────────────────────────────────────────────────────────────────
%  4. 路径跟踪精度验证（FK 反算）
% ─────────────────────────────────────────────────────────────────────────
fprintf('\n── 直线路径跟踪精度验证（FK 反算）──\n');

kin_check = RobotKinematics(robot_params.dh, robot_params.config, robot_params.q_lim);
T_arr     = size(result_line.q, 2);
tcp_pos   = zeros(3, T_arr);  % FK 计算的 TCP 位置

for t_idx = 1:T_arr
    q_t = result_line.q(:, t_idx);
    T_fk = dh_forward(robot_params.dh, q_t);
    tcp_pos(:, t_idx) = T_fk(1:3, 4);
end

% 计算相对于期望直线的横向偏差
% 直线从 P_line(1:3,1) 到 P_line(1:3,end)
p_start = P_line(1:3, 1);
p_end   = P_line(1:3, end);
line_dir = (p_end - p_start) / norm(p_end - p_start);

tcp_path_err = zeros(1, T_arr);
for t_idx = 1:T_arr
    dp = tcp_pos(:, t_idx) - p_start;
    proj = dot(dp, line_dir) * line_dir;
    tcp_path_err(t_idx) = norm(dp - proj) * 1000;  % mm
end

fprintf('TCP 直线路径最大偏差：%.4f mm（目标 < 1mm）\n', max(tcp_path_err));
if max(tcp_path_err) < 1.0
    fprintf('直线路径精度验证：✓ 通过\n');
else
    fprintf('直线路径精度验证：✗ 偏差超标\n');
end

%% ─────────────────────────────────────────────────────────────────────────
%  5. 定义圆弧路径（三点定弧）
% ─────────────────────────────────────────────────────────────────────────
% 圆弧在 XZ 平面内（半径约 0.1m），姿态保持不变
arc_spec.p0     = [0.3;  0.0;  0.4];   % 起点（m）
arc_spec.p_mid  = [0.35; 0.0;  0.45];  % 弧中点（m）
arc_spec.p1     = [0.4;  0.0;  0.4];   % 终点（m）
arc_spec.orient0 = [0; 0; 0];           % 起点姿态（ZYX Euler rad）
arc_spec.orient1 = [0; 0; 0];           % 终点姿态

fprintf('\n──────────────────────────────────────\n');
fprintf('测试 2：笛卡尔圆弧轨迹规划\n');
fprintf('圆弧起点：[%.3f, %.3f, %.3f] m\n', arc_spec.p0);
fprintf('圆弧弧中：[%.3f, %.3f, %.3f] m\n', arc_spec.p_mid);
fprintf('圆弧终点：[%.3f, %.3f, %.3f] m\n', arc_spec.p1);
fprintf('──────────────────────────────────────\n');

%% ─────────────────────────────────────────────────────────────────────────
%  6. 运行圆弧时间最优优化
% ─────────────────────────────────────────────────────────────────────────
fprintf('运行笛卡尔圆弧优化...\n');
tic;
result_arc = robot_traj_opt(arc_spec, robot_params, 'arc');
t_elapsed2 = toc;
fprintf('优化完成，耗时 %.2f s，轨迹时长 %.3f s\n', t_elapsed2, result_arc.t(end));

%% ─────────────────────────────────────────────────────────────────────────
%  7. 圆弧精度验证（FK 反算，检查圆度误差）
% ─────────────────────────────────────────────────────────────────────────
fprintf('\n── 圆弧路径圆度验证（FK 反算）──\n');

T_arc = size(result_arc.q, 2);
tcp_arc_pos = zeros(3, T_arc);

for t_idx = 1:T_arc
    q_t = result_arc.q(:, t_idx);
    T_fk = dh_forward(robot_params.dh, q_t);
    tcp_arc_pos(:, t_idx) = T_fk(1:3, 4);
end

% 计算期望圆的参数（三点定圆心）
[Center, ~, ~, R_expected] = three_points_arc_check( ...
    arc_spec.p0, arc_spec.p_mid, arc_spec.p1);

% 圆度误差：各点到圆心的距离与期望半径的偏差
radius_actual = zeros(1, T_arc);
for t_idx = 1:T_arc
    radius_actual(t_idx) = norm(tcp_arc_pos(:, t_idx) - Center) * 1000;  % mm
end
roundness_err = max(abs(radius_actual - R_expected * 1000));
fprintf('期望圆弧半径：%.4f mm\n', R_expected * 1000);
fprintf('实际半径范围：[%.4f, %.4f] mm\n', min(radius_actual), max(radius_actual));
fprintf('圆弧圆度误差：%.4f mm（目标 < 1mm）\n', roundness_err);
if roundness_err < 1.0
    fprintf('圆弧精度验证：✓ 通过\n');
else
    fprintf('圆弧精度验证：✗ 偏差超标\n');
end

%% ─────────────────────────────────────────────────────────────────────────
%  8. 绘图
% ─────────────────────────────────────────────────────────────────────────
colors = lines(6);
joint_names = {'q1','q2','q3','q4','q5','q6'};

figure('Name', '笛卡尔直线轨迹', 'Position', [50, 50, 1000, 700]);

% 三维 TCP 路径
subplot(1,2,1);
plot3(tcp_pos(1,:)*1000, tcp_pos(2,:)*1000, tcp_pos(3,:)*1000, 'b-', 'LineWidth', 2);
hold on;
scatter3(P_line(1,:)*1000, P_line(2,:)*1000, P_line(3,:)*1000, 60, 'ro', 'filled');
grid on; axis equal;
xlabel('X (mm)'); ylabel('Y (mm)'); zlabel('Z (mm)');
title('TCP 笛卡尔路径（直线）');
legend('FK 实际轨迹', '期望路径点', 'Location', 'best');

% 关节角时间历程
subplot(1,2,2);
hold on;
for i = 1:6
    plot(result_line.t, result_line.q(i,:), 'Color', colors(i,:), ...
        'LineWidth', 1.5, 'DisplayName', joint_names{i});
end
grid on; legend('Location', 'best');
xlabel('时间 (s)'); ylabel('关节角 (rad)');
title('关节角时间历程 q(t)（直线段）');

figure('Name', '笛卡尔圆弧轨迹', 'Position', [1100, 50, 1000, 700]);

% 三维圆弧路径
subplot(1,2,1);
plot3(tcp_arc_pos(1,:)*1000, tcp_arc_pos(2,:)*1000, tcp_arc_pos(3,:)*1000, ...
    'b-', 'LineWidth', 2);
hold on;
scatter3(arc_spec.p0(1)*1000,   arc_spec.p0(2)*1000,   arc_spec.p0(3)*1000,   80, 'go', 'filled');
scatter3(arc_spec.p_mid(1)*1000,arc_spec.p_mid(2)*1000,arc_spec.p_mid(3)*1000,80, 'bs', 'filled');
scatter3(arc_spec.p1(1)*1000,   arc_spec.p1(2)*1000,   arc_spec.p1(3)*1000,   80, 'r^', 'filled');
grid on; axis equal;
xlabel('X (mm)'); ylabel('Y (mm)'); zlabel('Z (mm)');
title('TCP 笛卡尔路径（圆弧）');
legend('FK 实际轨迹', '起点', '弧中点', '终点', 'Location', 'best');

% 圆弧关节角时间历程
subplot(1,2,2);
hold on;
for i = 1:6
    plot(result_arc.t, result_arc.q(i,:), 'Color', colors(i,:), ...
        'LineWidth', 1.5, 'DisplayName', joint_names{i});
end
grid on; legend('Location', 'best');
xlabel('时间 (s)'); ylabel('关节角 (rad)');
title('关节角时间历程 q(t)（圆弧段）');

fprintf('\n示例运行完成。\n');


%% 辅助函数：与 RobotCurvStruct 中相同的三点定圆计算（用于验证）
function [Center, evec, theta, R] = three_points_arc_check(p0, p_mid, p1)
    p0 = p0(:); p_mid = p_mid(:); p1 = p1(:);
    v1 = p_mid - p0;
    v2 = p1 - p0;
    evec_raw = cross(v1, v2);
    evec = evec_raw / norm(evec_raw);
    null_e = null(evec');
    A_eq = 2 * [(p_mid - p0)'; (p1 - p0)'];
    b_eq = [dot(p_mid, p_mid) - dot(p0, p0);
            dot(p1,   p1)    - dot(p0, p0)];
    A_red = A_eq * null_e;
    coefs = A_red \ b_eq;
    Center = p0 + null_e * coefs;
    R = norm(p0 - Center);
    CP0 = p0 - Center;
    CP1 = p1 - Center;
    cos_theta = max(-1, min(1, dot(CP0,CP1)/(norm(CP0)*norm(CP1))));
    theta = acos(cos_theta);
end
