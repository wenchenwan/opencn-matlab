function [ ctx ] = splitCurvStruct( ctx, curv )
%#codegen
% splitCurvStruct : 分割阶段主函数——将单条曲线按长度和零速条件切割成子段
%
% 【分割阶段的任务】
%   平滑阶段输出的曲线可能很长（几十 mm 甚至更长）。
%   优化阶段的 LP 规划窗口有固定大小（LSplit），若曲线太长，
%   单条曲线就会占满整个窗口，导致速度规划分辨率不足。
%   本函数将每条曲线切割成长度约为 LSplitZero/LSplit 的短段，
%   并对零速端额外切出一个"恒定跃度"子段用于准确的减速/加速规划。
%
% 【处理流程】
%
%   ① TransP5 过渡曲线 → 直接 push，不分割（过渡曲线本已极短）
%
%   ② 零速起始段（ZeroStart）→ cutZeroStart：
%        从曲线头部切出长度 Lcut（≤ L/3）的子段 curvS
%        curvS.UseConstJerk = true（以恒定跃度速度曲线驶出零速）
%        剩余部分 curv 继续后续处理
%
%   ③ 零速终止段（ZeroEnd）→ cutZeroEnd：
%        从曲线尾部切出长度 Lcut 的子段 curvE（先记录，最后 push）
%        curvE.UseConstJerk = true（以恒定跃度驶入零速）
%        剩余部分 curv 继续后续处理
%
%   ④ 中间段分割（两种策略）：
%      • SplitSpecialSpline=true 且当前曲线是 Spline：
%          在 B 样条节点向量的内部断点处分割（子段在样条段边界对齐）
%      • 其他（直线/圆弧/普通分割）：
%          将曲线等长分成 N 段（N = ceil(L/LSplit)），
%          每段长度 L/N，通过 cutCurvStruct 顺序切割
%
%   ⑤ 若有 curvE（第 ③ 步），最后追加 push
%
% Inputs  :
%   ctx   : 计算链上下文（含 q_compress / q_split / q_spline / cfg）
%   curv  : 来自 q_compress 的单条曲线结构体
%
% Outputs  :
%   ctx   : 更新后的上下文（分割结果已 push 入 q_split）
%

if( ~coder.target( 'MATLAB' ) ), curvE = constrCurvStructType; end

% ── ① TransP5：过渡曲线不分割，直接推入输出队列 ─────────────────────────
if ( curv.Info.Type == CurveType.TransP5 )
    ctx.q_split.push( curv ); return;
end

% ── ② 处理零速起始段（ZeroStart）────────────────────────────────────────
if( isAZeroStart( curv ) )
    % 从头部切出 Lcut 长度的子段，标记为恒定跃度（UseConstJerk）
    % cutZeroStart 返回：curvS（零速头段）、curv（剩余主段）
    [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
    ctx.q_split.push( curvS );
    if( ret < 0 ), return; end   % 切割失败（曲线过短）：直接结束
end

% ── ③ 处理零速终止段（ZeroEnd）──────────────────────────────────────────
hasEndSpeed = false;
if( isAZeroEnd( curv ) )
    % 从尾部切出 Lcut 长度的子段，标记为恒定跃度
    % cutZeroEnd 返回：curv（主段）、curvE（零速尾段）
    [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
    if( ret < 0 )
        % 切割失败（曲线过短）：整段推入后直接结束
        ctx.q_split.push( curv );
        return;
    end
    hasEndSpeed     = true;   % 标记：最后需要追加 curvE
end

% ── ④ 中间段分割 ─────────────────────────────────────────────────────────
if( ctx.cfg.SplitSpecialSpline && curv.Info.Type == CurveType.Spline )
    % 策略 A：B 样条断点对齐分割
    % 在样条的内部断点（breakpoints）处分割，确保每个子段对应完整的样条跨度。
    % 这样每个子段的 a_param/b_param 恰好覆盖一个或多个完整的 Bézier 段，
    % 避免子段跨越样条节点带来的数值问题。
    bspline     = ctx.q_spline.get( curv.sp_index );
    breakPoints = bspline.sp.Bl.breakpoints;   % B 样条的所有内部断点（全局参数）
    uMin        = curv.b_param;                % 当前曲线的全局参数起点
    uMax        = curv.b_param + curv.a_param; % 当前曲线的全局参数终点
    % 筛选落在 (uMin, uMax) 区间内的内部断点，并加上首尾端点组成完整分割点列
    ind         = find( breakPoints > uMin & breakPoints < uMax );
    breakPoints = [ uMin, breakPoints( ind ), uMax ] ;
    deltaU      = diff( breakPoints );   % 每个子段的参数宽度（即 a_param）
    uPrevious   = uMin;
    for j = 1 : length( deltaU )
        curvSplited         = curv;
        % 直接修改 a_param/b_param 实现子段切割（无需重新采样几何数据）
    	curvSplited.a_param = deltaU( j );
        curvSplited.b_param = uPrevious;
        uPrevious           = curvSplited.a_param + curvSplited.b_param;
        ctx.q_split.push( curvSplited );
    end
else
    % 策略 B：等弧长均匀分割（直线/圆弧/TransP5/普通 Spline）
    L       = LengthCurv( ctx, curv, 0, 1 );   % 计算曲线总弧长（mm）
    L_split = ctx.cfg.LSplit;                    % 目标子段长度（mm），来自配置

    % 向上取整确定子段数 N，再重新均分使每段精确等长
    N = ceil( L / L_split );
    L_split = L / N;   % 均分后的实际子段长度（略小于等于 cfg.LSplit）

    % 循环切割 N-1 段（最后一段不需要 cut，直接 push 剩余部分）
    for k = 1 : N - 1
        % cutCurvStruct(ctx, curv, isEnd=0, L, false)
        % 从 curv 头部切出弧长 L_split 的子段 curvSplited，curv 更新为剩余段
        [ ret, curvSplited, curv ] = cutCurvStruct( ctx, curv, 0, L_split, false );
        if( ret < 0 ), break; end   % 剩余段过短，提前结束循环

        % 调试断言：验证切出的子段弧长与目标一致（公差 1e-3 mm）
        ocn_assert( check_curv_length( ctx, curvSplited, L_split ), ...
            "Curve Length not valide", mfilename );

        ctx.q_split.push( curvSplited );
    end
    % 推入最后一段（循环提前退出时 curv 仍为剩余部分）
    ctx.q_split.push( curv );
end

% ── ⑤ 追加零速尾段 ───────────────────────────────────────────────────────
if( hasEndSpeed )
    % curvE 在第③步已计算，此处推入保证尾部零速约束段处于队列末尾
    ctx.q_split.push( curvE );
end

end

function [ isValid ] = check_curv_length( ctx, curv, L )
% 验证曲线实际弧长与期望值 L 之差在公差（1e-3 mm）内
tol = 1E-3;
isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
