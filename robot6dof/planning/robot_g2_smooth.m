function path_g2 = robot_g2_smooth(ctx, path_segments, delta_max)
% robot_g2_smooth : 对分段笛卡尔路径做 G2 连续平滑（路径过渡/zone 处理）
%
% 对每对相邻段调用 calcTransition（common/Feedopt），在交接点两侧各截去
% delta_max（zone 距离），插入 TransP5 五次多项式过渡段，实现 G2 连续。
%
% 与工业机器人控制器的 zone 参数对应：
%   delta_max ↔ ABB z5/z10、KUKA C_DIS、FANUC CNT 等 zone 半径设定
%   过渡段（TransP5）替代角点，TCP 不停顿地通过路径点
%
% 内部完全复用项目已有函数（不重写任何核心算法）：
%   calcTransition    → common/Feedopt/（含截短、G2插值、连续性验证全流程）
%   calcTransition 内部依次调用：
%     LengthCurv      → 计算段弧长（zone 上限判断）
%     cutCurvStruct   → 弧长截短（实现 zone 截断）
%     EvalCurvStruct  → 截短端点处导数（含 robot_mode 分支）
%     G2_Hermite_Interpolation_nAxis → Frenet 框架最优 alpha0/alpha1 求解
%     constrTransP5Struct → 构造 TransP5 过渡曲线结构体
%     check_continuity → G2 连续性验证
%
% Inputs:
%   ctx           : 机器人模式上下文（initRobotPlan 返回值）
%                   ctx.cfg.CutOff = zone 距离（m），由 delta_max 覆盖
%                   ctx.robot_mode = true（激活 EvalRobotCurv 分支）
%   path_segments : CurvStruct 数组（直线/圆弧段，G0/G1 连续）
%   delta_max     : zone 距离（m），可选；若提供则覆盖 ctx.cfg.CutOff
%
% Outputs:
%   path_g2 : 增广 CurvStruct 数组，格式：
%             [seg1_cut, trans12, seg2_cut, trans23, ..., segN_cut]
%             其中 trans_ij 为 TransP5 类型过渡段（G2 连续）
%             若某对相邻段过渡失败（段太短或无正实根），保留原始角点（G1 退化）

% 覆盖 zone 距离（若用户显式指定）
if nargin >= 3 && ~isempty(delta_max)
    ctx.cfg.CutOff = delta_max;
end

n_segs  = length(path_segments);
path_g2 = [];

for j = 1 : n_segs - 1
    curv1 = path_segments(j);
    curv2 = path_segments(j + 1);

    % calcTransition 完成全部 G2 过渡计算（截短 + Hermite插值 + 验证）
    [status, curv1C, curv2C, curvT] = calcTransition(ctx, curv1, curv2);

    if status == TransitionResult.Ok
        % 成功：追加截短段 + TransP5 过渡段
        % curv2C（截短后的右段）在下一次循环中作为 curv1 的替代
        path_g2 = [path_g2, curv1C, curvT]; %#ok<AGROW>
        % 将截短后的 curv2C 存回，供下一段迭代使用
        path_segments(j + 1) = curv2C;
    else
        % 失败（段太短 / 无正实根 / G2验证不通过）：保留原始段（G1 退化）
        path_g2 = [path_g2, curv1]; %#ok<AGROW>
    end
end

% 追加最后一段（末段无后续段，无需过渡）
if n_segs >= 1
    path_g2 = [path_g2, path_segments(end)];
end

end
