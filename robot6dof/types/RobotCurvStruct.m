function curv = RobotCurvStruct(type, r0, r1, feedrate, trafo)
% RobotCurvStruct : 构造 6-DOF 机器人曲线段结构体（兼容 CurvStruct 格式）
%
% 直线段构造。圆弧段请使用 RobotArcSegment()。
%
% 【字段约定】
%   关节空间模式（TRAFO=false）：
%     r0、r1 = [6×1] 关节角（rad）
%   笛卡尔空间模式（TRAFO=true）：
%     r0、r1 = [6×1] TCP 位姿，[px;py;pz;rx;ry;rz]（m + ZYX 欧拉角 rad）
%
% Inputs :
%   type     : CurveType.Line 或 CurveType.Helix
%   r0       : [6×1] 段起点
%   r1       : [6×1] 段终点
%   feedrate : 进给率上限（关节空间模式：rad/s TCP 等效；笛卡尔：m/s）
%   trafo    : logical，true = 笛卡尔编程，false = 关节坐标编程
%
% Outputs :
%   curv : 结构体，可直接推入 ctx.q_gcode 队列并被 EvalRobotCurv 处理

% 使用 OpenCN 原始结构体模板（保证字段完整性）
curv = constrCurvStructType();

% ── 曲线基本信息 ──
curv.Info.Type     = type;          % CurveType.Line 或 CurveType.Helix
curv.Info.TRAFO    = trafo;         % 坐标模式标志
curv.Info.FeedRate = feedrate;      % 进给率上限（LP 约束用）
curv.Info.zspdmode = ZSpdMode.NN;   % 默认两端均非零速（robot_traj_opt 负责设置首末段）

% ── 路径端点 ──
curv.R0 = r0(:);   % [6×1] 段起点（确保列向量）
curv.R1 = r1(:);   % [6×1] 段终点

% ── 参数变换：a_param = ‖P1-P0‖，使弧长参数化（对直线段）──
% EvalLine 的 r1D = (P1-P0)，LP 约束矩阵中 r1D 代表"单位参数增量"的方向向量。
% a_param 是参数变换的缩放系数，LP 内部通过 r1D *= a, r2D *= a^2 还原。
% 对直线段，a_param = 1 是合理的（P1-P0 已包含尺度信息）。
curv.a_param = 1;
curv.b_param = 0;

% ── 工具补偿：机器人模式无刀具补偿 ──
curv.tool.offset.z = 0;
curv.tool.offset.x = 0;
curv.tool.offset.y = 0;

end


function curv = RobotArcSegment(p0, p_mid, p1, orient0, orient1, feedrate, trafo)
% RobotArcSegment : 由三点构造笛卡尔圆弧段曲线结构体
%
% 圆弧由三个空间点 p0（起点）、p_mid（弧上任一点）、p1（终点）唯一确定。
% 姿态部分（orient0→orient1）使用线性参数化（SLERP 在 EvalRobotCurv 中处理）。
%
% Inputs :
%   p0, p_mid, p1 : [3×1] 三个空间位置（m）
%   orient0, orient1 : [3×1] ZYX 欧拉角（rad），起末姿态
%   feedrate : TCP 路径速度上限（m/s）
%   trafo    : logical（圆弧段通常为 true）
%
% Outputs :
%   curv : Helix 类型曲线结构体，可推入 ctx.q_gcode

curv = constrCurvStructType();

% ── 由三点计算圆弧参数 ──
[Center, evec, theta, R] = three_points_arc(p0(:), p_mid(:), p1(:));

% ── 填写 Helix 型结构体字段 ──
curv.Info.Type     = CurveType.Helix;
curv.Info.TRAFO    = trafo;
curv.Info.FeedRate = feedrate;
curv.Info.zspdmode = ZSpdMode.NN;

% 起末点（6 维：位置 + 姿态）
curv.R0 = [p0(:);      orient0(:)];
curv.R1 = [p1(:);      orient1(:)];

% Helix 几何参数
curv.evec                  = evec;    % 螺旋轴单位向量（纯圆弧时 = 法向量）
curv.theta                 = theta;   % 总圆心角（rad）
curv.pitch                 = 0;       % 纯平面圆弧，无螺旋分量
curv.CorrectedHelixCenter  = Center;  % 圆心位置（3×1，仅位置分量）

curv.a_param = 1;
curv.b_param = 0;
curv.tool.offset.z = 0;
curv.tool.offset.x = 0;
curv.tool.offset.y = 0;

end


function [Center, evec, theta, R] = three_points_arc(p0, p_mid, p1)
% three_points_arc : 由三个空间点计算圆弧的圆心、轴向量、圆心角和半径
%
% 算法：
%   1. 计算平面法向量 ê = (p_mid-p0) × (p1-p0)（归一化）
%   2. 求三点外接圆圆心（在该平面内的线性方程组）
%   3. 计算总圆心角 θ（从 p0 到 p1，按 ê 方向为正）

% 平面法向量
v1 = p_mid - p0;
v2 = p1    - p0;
evec_raw = cross(v1, v2);

if norm(evec_raw) < 1e-10
    error('RobotArcSegment: 三点共线，无法确定圆弧平面');
end

evec = evec_raw / norm(evec_raw);  % 归一化法向量

% 三点外接圆圆心（解析法）
% 在平面内建立两条弦的垂直平分线方程，交点即圆心
A = 2 * [v1'; v2'];
b_rhs = [dot(v1, v1 + 2*p0); dot(v2, v2 + 2*p0)];
% 实际上更简洁的表达：
% |p0-Center|² = |p_mid-Center|² → 2*(p_mid-p0)'*Center = |p_mid|²-|p0|²
% 类似第二方程
A_eq = 2 * [(p_mid - p0)'; (p1 - p0)'];
b_eq = [dot(p_mid, p_mid) - dot(p0, p0);
        dot(p1,   p1)    - dot(p0, p0)];

% 最小范数解（平面约束下取三维圆心）
% 利用 Lagrange 乘数法：圆心 = p0 + A_eq^† * b_eq（在平面内）
% 简化：在 evec 法平面内用 svd 求最小范数解
null_e = null(evec');  % [3×2] 法平面基底
A_red  = A_eq * null_e;  % [2×2] 在平面坐标下的方程

if abs(det(A_red)) < 1e-12
    error('RobotArcSegment: 三点近似共线，无法确定唯一圆心');
end

coefs  = A_red \ b_eq;
Center = p0 + null_e * coefs;

% 半径验证
R = norm(p0 - Center);

% 圆心角计算
CP0 = p0    - Center;
CP1 = p1    - Center;
cos_theta = dot(CP0, CP1) / (norm(CP0) * norm(CP1));
cos_theta = max(-1, min(1, cos_theta));  % 数值裁剪

% 方向：通过 p_mid 的位置判断圆弧方向（顺/逆时针）
CPm = p_mid - Center;
cross_check = dot(cross(CP0, CP1), evec);

theta_mag = acos(cos_theta);

if cross_check >= 0
    theta = theta_mag;
else
    theta = -theta_mag;
end

% 若 p_mid 在劣弧一侧（|theta| < π），需检查是否取优弧（|theta| > π）
% 判断方法：CPm 与 CP0/CP1 的中间向量是否与圆心角内侧对应
CP0_unit = CP0 / norm(CP0);
CP1_unit = CP1 / norm(CP1);
mid_dir  = (CP0_unit + CP1_unit);
if norm(mid_dir) > 1e-10
    mid_dir = mid_dir / norm(mid_dir);
    if dot(CPm / norm(CPm), mid_dir) < 0
        % p_mid 在优弧一侧，使用 2π - |theta|
        if theta >= 0
            theta = theta - 2*pi;
        else
            theta = theta + 2*pi;
        end
    end
end

end
