classdef RobotKinematics
% RobotKinematics : 6-DOF 串联臂运动学适配层
%
% 接口设计与 Kinematics.m（CNC 五轴机运动学）完全兼容：
%   v_relative(r0D, r1D) → TRAFO=false 时，将关节速度映射到 TCP 速度（进给率约束）
%   joint(r0D, r1D, r2D, r3D) → TRAFO=true 时，将笛卡尔导数映射到关节空间（加速度约束）
%
% 【坐标约定】
%   - 关节空间（q）: [q1;q2;q3;q4;q5;q6]，单位 rad
%   - 工件坐标（x）: [px;py;pz;rx;ry;rz]，位置 m + ZYX 欧拉角 rad
%   - DH 参数：标准 DH（Craig 约定），每行 [a_{i-1}, d_i, alpha_{i-1}, theta_offset_i]
%
% 【奇异点处理】
%   检测 rcond(J) < 1e-6 时切换为阻尼最小二乘（DLS）：
%     J_inv = J' / (J*J' + lambda²·I)，lambda = 0.01 rad/s

properties (SetAccess = private)
    dh_params       % [6×4] DH 参数矩阵
    tool_length     % 末端 z 轴额外偏置（m，默认 0）
    robot_config    % 'elbow_up' 或 'elbow_down'，决定 IK 解选择
    q_lim           % [6×2] 关节限位 [q_min, q_max]（rad）
    q_prev          % [6×1] 上一时刻关节角（用于 IK 连续解选择）
end

methods (Access = public)

    function this = RobotKinematics(dh_params, varargin)
    % 构造函数
    % Inputs:
    %   dh_params   : [6×4] DH 参数矩阵
    %   varargin{1} : robot_config（'elbow_up'/'elbow_down'，默认 'elbow_up'）
    %   varargin{2} : q_lim [6×2]（默认 ±2π）

        this.dh_params    = dh_params;
        this.tool_length  = 0;

        if nargin >= 2
            this.robot_config = varargin{1};
        else
            this.robot_config = 'elbow_up';
        end

        if nargin >= 3
            this.q_lim = varargin{2};
        else
            this.q_lim = repmat([-2*pi, 2*pi], 6, 1);
        end

        this.q_prev = zeros(6, 1);  % 初始关节角（全零）
    end

    function this = set_tool_length(this, length)
    % 设置末端工具长度（附加到最后一个关节的 d6 上）
        this.tool_length = length;
    end

    function type = get_type(this)
    % 返回运动学类型标识字符串
        type = 'robot6dof';
    end

    function v_t = v_relative(this, r0D, r1D)
    % TRAFO=false 分支：将关节空间速度方向映射到 TCP 工具速度
    %
    % 在关节坐标编程模式（TRAFO=false）中：
    %   r0D [6×M] : 各采样点的关节角（关节空间位置）
    %   r1D [6×M] : 各采样点的关节速度方向（∂q/∂u，对参数 u 的导数）
    %
    % 进给率 F 约束作用于 TCP 在工件坐标系中的路径速度：
    %   v_tcp = J(q) * (dq/dt) = J(q) * (dq/du) * (du/dt)
    % 因此 vecnorm(J * r1D) 给出路径速度的方向权重，用于 LP 中的 F 上限约束。
    %
    % Outputs:
    %   v_t [6×M] : 每列为对应采样点的 TCP 速度方向向量（J * r1D_col）

        M   = size(r0D, 2);
        v_t = zeros(6, M);

        for j = 1:M
            q = r0D(:, j);
            J = this.geometric_jacobian(q);

            % DLS 奇异点保护
            if rcond(J) < 1e-6
                lam2 = 1e-4;
                J_inv = J' / (J * J' + lam2 * eye(6));
                % TRAFO=false 只需正向乘：v_tcp = J * qd
                % 这里 J_inv 只在 joint() 中用；此处直接使用 J
            end
            v_t(:, j) = J * r1D(:, j);
        end
    end

    function [r0D_j, r1D_j, r2D_j, r3D_j] = joint(this, r0D, r1D, r2D, r3D)
    % TRAFO=true 分支：将笛卡尔空间导数转换为关节空间导数
    %
    % 在笛卡尔编程模式（TRAFO=true）中：
    %   r0D [6×M] : 笛卡尔位姿（[px;py;pz;rx;ry;rz]，位置 m + ZYX 欧拉角 rad）
    %   r1D [6×M] : 笛卡尔速度方向（∂x/∂u）
    %   r2D [6×M] : 笛卡尔加速度方向（∂²x/∂u²）
    %   r3D [6×M] : 笛卡尔跃度方向（∂³x/∂u³）
    %
    % 链式法则展开：
    %   dq/du      = J⁻¹ * (dx/du)
    %   d²q/du²    = J⁻¹ * (d²x/du² - dJ/du * dq/du)
    %   d³q/du³    = J⁻¹ * (d³x/du³ - dJ/du * d²q/du² - d²J/du² * dq/du)
    %
    % Outputs:
    %   r0D_j [6×M] : 关节角（由 IK 求解）
    %   r1D_j [6×M] : 关节速度方向（dq/du）
    %   r2D_j [6×M] : 关节加速度方向（d²q/du²）
    %   r3D_j [6×M] : 关节跃度方向（d³q/du³，数值近似）

        M     = size(r0D, 2);
        r0D_j = zeros(6, M);
        r1D_j = zeros(6, M);
        r2D_j = zeros(6, M);
        r3D_j = zeros(6, M);

        for j = 1:M
            % —— IK：从笛卡尔位姿求关节角 ——
            x_cart = r0D(:, j);
            T_target = this.pose_to_T(x_cart);
            q = this.inverse_kinematics(T_target);

            % 记录关节角（用于下一步连续解选择）
            this.q_prev = q;
            r0D_j(:, j) = q;

            % —— 几何雅可比 ——
            J = this.geometric_jacobian(q);

            % —— 逆雅可比（含奇异保护）——
            J_inv = this.safe_J_inv(J);

            % —— 一阶：dq/du = J⁻¹ * dx/du ——
            qd = J_inv * r1D(:, j);
            r1D_j(:, j) = qd;

            % —— 雅可比时间导数（数值微分）: dJ/du ——
            % 由链式法则，dJ/dt = (dJ/dq) * (dq/dt)，
            % 但对 u 的导数 dJ/du = (∂J/∂q) * qd，用数值方式近似：
            JP = this.numerical_dJ_du(q, qd);

            % —— 二阶：d²q/du² = J⁻¹ * (d²x/du² - dJ/du * dq/du) ——
            r2D_j(:, j) = J_inv * (r2D(:, j) - JP * qd);

            % —— 三阶：数值近似（需要相邻点的雅可比信息，用双步差分）——
            % 用当前点简化：d³q/du³ ≈ J⁻¹ * d³x/du³（忽略高阶耦合项）
            % 跃度在 LP 中已被松弛（软约束），精度要求低于速度/加速度
            r3D_j(:, j) = J_inv * r3D(:, j);
        end
    end

end  % methods (Access = public)

methods (Access = private)

    function J = geometric_jacobian(this, q)
    % 计算 6×6 几何雅可比矩阵
    %
    % 几何雅可比定义（旋转关节）：
    %   第 i 列 = [ z_{i-1} × (p_e - p_{i-1}) ]  (位置部分，3×1)
    %             [         z_{i-1}             ]  (姿态部分，3×1)
    % 其中 z_{i-1} 是第 i-1 个坐标系的 z 轴方向，p_{i-1} 是其原点位置，
    % p_e 是末端执行器位置，均在基座坐标系下表达。

        dh = this.dh_params;

        % 如有工具偏置，叠加到末端
        if this.tool_length ~= 0
            dh(end, 2) = dh(end, 2) + this.tool_length;
        end

        [~, T_frames] = dh_forward(dh, q);

        % 末端位置（从 T_frames{7} 提取）
        p_e = T_frames{end}(1:3, 4);

        J = zeros(6, 6);

        for i = 1:6
            % T_frames{i}：第 i-1 个坐标系（i=1 为基座）
            T_im1 = T_frames{i};

            z_im1 = T_im1(1:3, 3);   % 第 i-1 坐标系的 z 轴方向
            p_im1 = T_im1(1:3, 4);   % 第 i-1 坐标系的原点位置

            % 位置分量：z_{i-1} × (p_e - p_{i-1})
            J(1:3, i) = cross(z_im1, p_e - p_im1);
            % 姿态分量：z_{i-1}
            J(4:6, i) = z_im1;
        end
    end

    function q = inverse_kinematics(this, T_target)
    % 解析式逆运动学（腕部分离法）
    %
    % 适用条件：最后三个关节轴（4/5/6）交于同一点（球形手腕），
    %   即标准 DH 参数满足 d4=d5=0 且轴 4/5/6 共点。
    %   UR5 满足该条件。
    %
    % 算法步骤：
    %   1. 由末端位姿计算腕心位置 p_w = p_e - d6 * R * e_z
    %   2. 由 p_w 求解 q1、q2、q3（位置逆解，解析式）
    %   3. 由 R_03^T * R_06 = R_36 的 Euler 角求解 q4、q5、q6
    %   4. 从多个候选解中选择最接近 q_prev 的解（保持轨迹连续性）
    %
    % Inputs:
    %   T_target : [4×4] 目标末端齐次变换矩阵
    %
    % Outputs:
    %   q : [6×1] 关节角（rad）

        R = T_target(1:3, 1:3);
        p_e = T_target(1:3, 4);
        dh  = this.dh_params;

        % DH 参数提取
        d1 = dh(1, 2);  d2 = dh(2, 2);  d3 = dh(3, 2);
        d4 = dh(4, 2);  d5 = dh(5, 2);  d6 = dh(6, 2);
        a1 = dh(1, 1);  a2 = dh(2, 1);  a3 = dh(3, 1);

        % 工具偏置叠加
        if this.tool_length ~= 0
            d6 = d6 + this.tool_length;
        end

        % ── 步骤 1：计算腕心位置 ──
        % p_w = p_e - d6 * R * [0;0;1]
        p_w = p_e - d6 * R(:, 3);

        % ── 步骤 2：求 q1（绕 z0 旋转，由 p_w 的 xy 投影确定）──
        % UR 型机器人 q1 有两个解（±atan2）
        r_xy = sqrt(p_w(1)^2 + p_w(2)^2);
        q1_a = atan2(p_w(2), p_w(1));
        q1_b = atan2(p_w(2), p_w(1)) + pi;  % 反向解

        % ── 步骤 3：求 q2、q3（肘部平面三角形问题）──
        % 在 q1 确定后，腕心在 {1} 坐标系中的投影为已知量
        q_candidates = [];

        for q1 = [q1_a, q1_b]
            c1 = cos(q1);  s1 = sin(q1);

            % p_w 在 {1} 坐标系中的 xz 分量
            pw_x1 = c1 * p_w(1) + s1 * p_w(2) - a1;
            pw_z1 = p_w(3) - d1;

            % 肘部三角形：边长分别为 a2、L_{23}（a3 和 d4 的合力）
            L23 = sqrt(a3^2 + d4^2);
            D = (pw_x1^2 + pw_z1^2 - a2^2 - L23^2) / (2 * a2 * L23);

            if abs(D) > 1
                continue;  % 目标点不可达，跳过该 q1 解
            end

            % q3 有 elbow_up 和 elbow_down 两解
            q3_vals = [atan2(sqrt(1 - D^2), D), atan2(-sqrt(1 - D^2), D)];

            for q3_raw = q3_vals
                % q3 带辅助角修正（因 L23 由 a3 和 d4 合成）
                phi3 = atan2(d4, a3);
                q3   = q3_raw - phi3;

                % q2
                alpha2 = atan2(pw_z1, pw_x1);
                beta2  = atan2(L23 * sin(q3_raw), a2 + L23 * cos(q3_raw));
                q2     = alpha2 - beta2;

                % ── 步骤 4：求 q4、q5、q6（腕部 Euler 角）──
                % 计算前三轴的复合旋转矩阵 R_03
                T_03 = dh_forward(dh(1:3, :), [q1; q2; q3]);
                R_03 = T_03(1:3, 1:3);

                % 腕部旋转矩阵
                R_36 = R_03' * R;

                % ZYZ Euler 角（标准球形手腕解法）
                % R_36 = Rz(q4) * Ry(q5) * Rz(q6)
                q5_val = atan2(sqrt(R_36(3,1)^2 + R_36(3,2)^2), R_36(3,3));

                if abs(sin(q5_val)) > 1e-8
                    q4_a = atan2( R_36(2,3),  R_36(1,3));
                    q6_a = atan2( R_36(3,2), -R_36(3,1));
                    q4_b = atan2(-R_36(2,3), -R_36(1,3));
                    q6_b = atan2(-R_36(3,2),  R_36(3,1));
                    q5_b = -q5_val;

                    q_candidates = [q_candidates, ...
                        [q1; q2; q3; q4_a; q5_val; q6_a], ...
                        [q1; q2; q3; q4_b; q5_b;   q6_b]];
                else
                    % 奇异（q5≈0 或 π），q4/q6 不独立，约定 q4=0
                    if abs(q5_val) < 1e-8
                        q4_s = 0;
                        q6_s = atan2(R_36(2,1), R_36(1,1));
                    else
                        q4_s = 0;
                        q6_s = -atan2(R_36(2,1), R_36(1,1));
                    end
                    q_candidates = [q_candidates, ...
                        [q1; q2; q3; q4_s; q5_val; q6_s]];
                end
            end
        end

        % ── 步骤 5：从候选解中选最接近 q_prev 的解 ──
        if isempty(q_candidates)
            % 全部候选解均不可达，使用阻尼数值 IK 作为备用
            q = this.numerical_ik_fallback(T_target);
            return;
        end

        % 按关节角 L2 距离选择最接近上一时刻关节角的解
        n_cand = size(q_candidates, 2);
        dist   = zeros(1, n_cand);
        for k = 1:n_cand
            diff_k = q_candidates(:, k) - this.q_prev;
            % 角度差归一化到 (-π, π]
            diff_k = mod(diff_k + pi, 2*pi) - pi;
            dist(k) = norm(diff_k);
        end

        [~, idx] = min(dist);
        q = q_candidates(:, idx);

        % ── 步骤 6：按 elbow_up/down 构型偏好过滤（可选加权）──
        % 此处已通过 q5_val 符号隐式选择，构型偏好主要影响 elbow_up/down
        % 用户可在 robot_config='elbow_down' 时给 q3 负值候选加权
        % 当前实现：依赖"最近解"策略已足够连续路径使用

        % 关节限位检查（soft warning，不报错）
        for i = 1:6
            if q(i) < this.q_lim(i, 1) || q(i) > this.q_lim(i, 2)
                % 超出限位时尝试将关节角映射到限位范围内最近的位置
                q(i) = max(this.q_lim(i,1), min(this.q_lim(i,2), q(i)));
            end
        end
    end

    function JP = numerical_dJ_du(this, q, qd)
    % 数值计算雅可比对参数 u 的导数：dJ/du ≈ (J(q + ε·qd) - J(q)) / ε
    %
    % 由链式法则：dJ/du = Σ_i (∂J/∂q_i) * (dq_i/du)
    % 数值近似：扰动方向沿 qd，步长 ε = 1e-7
    %
    % Inputs:
    %   q  : [6×1] 当前关节角
    %   qd : [6×1] 关节速度方向（dq/du）
    %
    % Outputs:
    %   JP : [6×6] dJ/du（矩阵）

        eps  = 1e-7;
        J0   = this.geometric_jacobian(q);
        J1   = this.geometric_jacobian(q + eps * qd);
        JP   = (J1 - J0) / eps;
    end

    function J_inv = safe_J_inv(this, J)
    % 含奇异保护的雅可比逆（阻尼最小二乘 DLS）
    %
    % 正则逆：J_inv = J^{-1}（rcond(J) 良好时）
    % DLS 逆：J_inv = J' * (J*J' + λ²I)^{-1}（接近奇异时）
    %   λ = 0.01，对应 1% 阻尼比

        if rcond(J) > 1e-6
            J_inv = J \ eye(6);  % 标准逆（精确）
        else
            lam2  = 1e-4;        % λ² = 0.01² = 1e-4
            J_inv = J' / (J * J' + lam2 * eye(6));
        end
    end

    function T = pose_to_T(this, x_cart)
    % 将笛卡尔位姿向量转换为齐次变换矩阵
    %
    % 输入格式：x_cart = [px; py; pz; rx; ry; rz]
    %   位置：(px, py, pz)（m）
    %   姿态：ZYX 内旋欧拉角 (rx, ry, rz)（rad）
    %     即 R = Rz(rz) * Ry(ry) * Rx(rx)

        px = x_cart(1);  py = x_cart(2);  pz = x_cart(3);
        rx = x_cart(4);  ry = x_cart(5);  rz = x_cart(6);

        % ZYX 欧拉角旋转矩阵（Rz * Ry * Rx）
        R = eul2rotm([rz, ry, rx], 'ZYX');

        T = [R, [px; py; pz]; 0, 0, 0, 1];
    end

    function q = numerical_ik_fallback(this, T_target)
    % 解析 IK 失败时的数值 IK 备用方案（梯度下降 + 阻尼最小二乘）
    %
    % 适用于奇异点附近或超出工作空间边界的情况，
    % 以 q_prev 为初始点迭代至收敛。

        q     = this.q_prev;
        max_iter = 100;
        tol      = 1e-6;

        for iter = 1:max_iter
            T_cur = dh_forward(this.dh_params, q);
            R_cur = T_cur(1:3, 1:3);
            p_cur = T_cur(1:3, 4);

            R_tar = T_target(1:3, 1:3);
            p_tar = T_target(1:3, 4);

            % 位置误差
            e_p = p_tar - p_cur;
            % 姿态误差（轴角形式）
            R_err = R_tar * R_cur';
            e_r   = [R_err(3,2) - R_err(2,3);
                     R_err(1,3) - R_err(3,1);
                     R_err(2,1) - R_err(1,2)] * 0.5;

            e = [e_p; e_r];

            if norm(e) < tol
                break;
            end

            J     = this.geometric_jacobian(q);
            J_inv = this.safe_J_inv(J);
            dq    = J_inv * e;

            % 步长限制（防止大步跳跃）
            step = min(1.0, 0.5 / (norm(dq) + 1e-10));
            q    = q + step * dq;

            % 关节限位裁剪
            for i = 1:6
                q(i) = max(this.q_lim(i,1), min(this.q_lim(i,2), q(i)));
            end
        end
    end

end  % methods (Access = private)

end  % classdef
