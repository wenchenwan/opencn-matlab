function [r0D, r1D, r2D, r3D] = EvalRobotCurv(ctx, curv, u_vec)
% EvalRobotCurv : 机器人模式曲线求值分发函数
%
% 替代 EvalCurvStruct 在机器人模式（ctx.robot_mode=true）下的行为。
% 根据曲线类型（Line/Helix）和坐标模式（TRAFO），分发到对应的求值函数。
%
% 【支持的曲线类型】
%   CurveType.Line  : 直线段 → EvalLine（关节或笛卡尔坐标均支持）
%   CurveType.Helix : 圆弧段 → EvalHelix（位置轴）+ EvalLine（姿态轴，线性插值）
%
% 【坐标维度】
%   机器人模式固定为 6 维：
%     关节空间 (TRAFO=false): [q1;q2;q3;q4;q5;q6]
%     笛卡尔空间 (TRAFO=true): [px;py;pz;rx;ry;rz]（位置 m + ZYX 欧拉角 rad）
%
% Inputs :
%   ctx   : 上下文结构体（含 cfg.maskTot，cfg.NumberAxis 等）
%   curv  : 曲线结构体（由 RobotCurvStruct 或 RobotArcSegment 创建）
%   u_vec : [1×M] 参数向量（u ∈ [0,1]）
%
% Outputs :
%   r0D : [6×M] 位置（0 阶导）
%   r1D : [6×M] 一阶参数导数（∂r/∂u）
%   r2D : [6×M] 二阶参数导数（∂²r/∂u²）
%   r3D : [6×M] 三阶参数导数（∂³r/∂u³）
%
% 【参数变换缩放】
%   与 EvalCurvStructNoCtx 完全一致：
%     a = curv.a_param（缩放系数）
%     r1D_out = a   * r1D_raw
%     r2D_out = a^2 * r2D_raw
%     r3D_out = a^3 * r3D_raw

nD   = ctx.cfg.NumberAxis;   % 激活轴数（机器人模式固定为 6）
M    = length(u_vec);
mask = ctx.cfg.maskTot;      % [1×6] logical，机器人模式全为 true

switch curv.Info.Type

    case CurveType.Line
        % ── 直线段：对所有 6 轴调用 EvalLine ──
        % EvalLine 仅使用 R0/R1 端点，维度由 mask 选取。
        [r0D, r1D, r2D, r3D] = EvalLine(curv, u_vec, mask);

    case CurveType.Helix
        % ── 圆弧段：位置轴（1:3）用 EvalHelix，姿态轴（4:6）用线性插值 ──
        %
        % 设计依据：
        %   圆弧仅定义在 XYZ 空间，EvalHelix 输出 3 维位置导数。
        %   姿态（RX/RY/RZ）在圆弧运动中沿用线性（SLERP 简化）插值，
        %   SLERP 对参数 u 的 1/2/3 阶导数通过 EvalLine 等效近似。

        r0D = zeros(nD, M);
        r1D = zeros(nD, M);
        r2D = zeros(nD, M);
        r3D = zeros(nD, M);

        % 位置轴（前 3 轴）：调用 EvalHelix
        mask_cart = false(1, 6);
        mask_cart(1:3) = true;
        [r0D_h, r1D_h, r2D_h, r3D_h] = EvalHelix(curv, u_vec, mask_cart);
        r0D(1:3, :) = r0D_h;
        r1D(1:3, :) = r1D_h;
        r2D(1:3, :) = r2D_h;
        r3D(1:3, :) = r3D_h;

        if nD > 3
            % 姿态轴（后 3 轴）：线性插值（等效 SLERP 一阶近似）
            % 构造仅含姿态端点的子曲线结构体（复用原 curv 的 R0/R1 姿态部分）
            curv_orient        = curv;
            curv_orient.R0     = curv.R0(4:end);  % 姿态起点 [rx0;ry0;rz0]
            curv_orient.R1     = curv.R1(4:end);  % 姿态终点 [rx1;ry1;rz1]
            mask_orient        = true(1, nD - 3);

            [r0D_o, r1D_o, r2D_o, r3D_o] = EvalLine(curv_orient, u_vec, mask_orient);
            r0D(4:end, :) = r0D_o;
            r1D(4:end, :) = r1D_o;
            r2D(4:end, :) = r2D_o;
            r3D(4:end, :) = r3D_o;
        end

    otherwise
        error('EvalRobotCurv: 不支持的曲线类型 %d（仅支持 Line 和 Helix）', ...
              int32(curv.Info.Type));
end

% ── 参数变换缩放（与 EvalCurvStructNoCtx 行为一致）──
% a_param = 1 时为恒等变换；若曲线被分割，a_param 包含子段缩放信息
a   = curv.a_param;
r1D = a   .* r1D;
r2D = a^2 .* r2D;
r3D = a^3 .* r3D;

end
