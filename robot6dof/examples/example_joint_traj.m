% example_joint_traj.m
% 6-DOF 机器人时间最优关节空间轨迹规划示例（UR5 参数）
%
% 本示例展示：
%   1. 如何配置 UR5 机器人参数（DH 参数、关节约束）
%   2. 如何定义关节空间路径点（5 个路径点 → 4 段直线）
%   3. 调用 robot_traj_opt 完成时间最优优化
%   4. 验证约束满足性：max|qd| ≤ vmax, max|qdd| ≤ amax
%   5. 绘制关节角、速度、加速度时间历程图
%
% 验证目标（参考方案设计文档）：
%   - q(t) 在路径点之间单调过渡
%   - 段间速度连续（无跳变）
%   - max(abs(qd))  ≤ vmax 的 100%
%   - max(abs(qdd)) ≤ amax 的 100%
%   - 轨迹总时间合理（参考手动梯形曲线估算值）
%
% 运行前需要将以下路径加入 MATLAB path：
%   addpath(genpath('<opencn-root>/agency/usr/matlab/opencn-matlab'))

clear; clc; close all;

%% ─────────────────────────────────────────────────────────────────────────
%  1. 机器人参数配置（UR5）
% ─────────────────────────────────────────────────────────────────────────

% UR5 标准 DH 参数（Craig 约定，单位：m/rad）
% 列顺序：[a_{i-1}, d_i, alpha_{i-1}, theta_offset_i]
robot_params.dh = [
     0,      0.0892,  pi/2,   0;   % 关节 1
    -0.4250, 0,       0,      0;   % 关节 2
    -0.3922, 0,       0,      0;   % 关节 3
     0,      0.1093,  pi/2,   0;   % 关节 4
     0,      0.0948, -pi/2,   0;   % 关节 5
     0,      0.0823,  0,      0;   % 关节 6
];

% UR5 关节速度/加速度/跃度上限
robot_params.vmax = [3.15, 3.15, 3.15, 3.20, 3.20, 3.20];  % rad/s
robot_params.amax = [40,   40,   40,   40,   40,   40  ];   % rad/s²
robot_params.jmax = [400,  400,  400,  400,  400,  400 ];   % rad/s³
robot_params.dt   = 1e-3;                                    % 1ms 输出

% 关节限位（UR5：±360°）
robot_params.q_lim   = repmat([-2*pi, 2*pi], 6, 1);
robot_params.config  = 'elbow_up';
robot_params.feedrate = 1.0;  % 进给率上限（关节等效速度 rad/s），可被 vmax 约束覆盖

%% ─────────────────────────────────────────────────────────────────────────
%  2. 定义关节空间路径点（单位：rad）
% ─────────────────────────────────────────────────────────────────────────
% 5 个关节角路径点，每列一个位形
% 路径设计：从全零（竖直初态）经一系列中间位形到目标位形
Q = [
    0.0,  0.3,  0.8,  1.2,  1.5;   % q1（绕基座旋转）
    0.0, -0.4, -0.6, -0.8, -1.0;   % q2（肩部）
    0.0,  0.5,  0.8,  1.0,  1.2;   % q3（肘部）
    0.0,  0.2,  0.4,  0.6,  0.8;   % q4（腕部 1）
    0.0,  0.1,  0.2,  0.3,  0.5;   % q5（腕部 2）
    0.0,  0.0,  0.1,  0.2,  0.3;   % q6（腕部旋转）
];

fprintf('路径点数量：%d 点，共 %d 段\n', size(Q,2), size(Q,2)-1);

%% ─────────────────────────────────────────────────────────────────────────
%  3. 运行时间最优轨迹规划
% ─────────────────────────────────────────────────────────────────────────
fprintf('开始时间最优优化...\n');
tic;
result = robot_traj_opt(Q, robot_params, 'joint');
elapsed = toc;
fprintf('优化完成，耗时 %.2f s，轨迹时长 %.3f s\n', elapsed, result.t(end));

%% ─────────────────────────────────────────────────────────────────────────
%  4. 约束验证
% ─────────────────────────────────────────────────────────────────────────
fprintf('\n── 约束满足性验证 ──\n');
fprintf('%-8s  %-12s  %-12s  %-10s\n', '关节', 'max|qd|', 'vmax', '满足?');
for i = 1:6
    max_qd = max(abs(result.qd(i,:)));
    ok = max_qd <= robot_params.vmax(i) * 1.001;  % 允许 0.1% 数值误差
    fprintf('关节 %d   %.4f rad/s  %.4f rad/s  %s\n', i, max_qd, robot_params.vmax(i), ...
        conditional_str(ok, '✓ OK', '✗ 违反'));
end

fprintf('\n%-8s  %-12s  %-12s  %-10s\n', '关节', 'max|qdd|', 'amax', '满足?');
for i = 1:6
    max_qdd = max(abs(result.qdd(i,:)));
    ok = max_qdd <= robot_params.amax(i) * 1.001;
    fprintf('关节 %d   %.4f rad/s² %.4f rad/s² %s\n', i, max_qdd, robot_params.amax(i), ...
        conditional_str(ok, '✓ OK', '✗ 违反'));
end

% 零速边界验证
fprintf('\n── 边界条件验证 ──\n');
fprintf('起点速度：max|qd(:,1)|  = %.6f rad/s（期望 ≈ 0）\n', max(abs(result.qd(:,1))));
fprintf('终点速度：max|qd(:,end)| = %.6f rad/s（期望 ≈ 0）\n', max(abs(result.qd(:,end))));

%% ─────────────────────────────────────────────────────────────────────────
%  5. 绘图
% ─────────────────────────────────────────────────────────────────────────
t  = result.t;
q  = result.q;
qd = result.qd;

joint_names = {'q1','q2','q3','q4','q5','q6'};
colors = lines(6);

figure('Name', '关节空间时间最优轨迹', 'Position', [100, 100, 1200, 800]);

% 上图：关节角
subplot(2,1,1);
hold on;
for i = 1:6
    plot(t, q(i,:), 'Color', colors(i,:), 'LineWidth', 1.5, 'DisplayName', joint_names{i});
end
% 标记路径点（用简化的弧长时间估算，仅作参考）
grid on; legend('Location', 'best');
xlabel('时间 (s)'); ylabel('关节角 (rad)');
title('6-DOF UR5 关节角轨迹 q(t)');
hold off;

% 下图：关节速度
subplot(2,1,2);
hold on;
for i = 1:6
    plot(t, qd(i,:), 'Color', colors(i,:), 'LineWidth', 1.5, 'DisplayName', joint_names{i});
    % 速度上限参考线
    yline(robot_params.vmax(i),  '--', 'Color', colors(i,:), 'Alpha', 0.3);
    yline(-robot_params.vmax(i), '--', 'Color', colors(i,:), 'Alpha', 0.3);
end
grid on; legend('Location', 'best');
xlabel('时间 (s)'); ylabel('关节速度 (rad/s)');
title('关节速度 qd(t)（虚线 = ±vmax）');
hold off;

fprintf('\n示例运行完成。结果存储在 result 变量中。\n');
fprintf('  result.t   : 时间向量 [1×%d]\n', length(t));
fprintf('  result.q   : 关节角   [6×%d]\n', size(q,2));
fprintf('  result.qd  : 关节速度 [6×%d]\n', size(qd,2));


%% 辅助函数
function s = conditional_str(cond, s_true, s_false)
    if cond; s = s_true; else; s = s_false; end
end
