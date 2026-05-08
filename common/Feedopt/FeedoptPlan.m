function [ ctx, optimized, opt_struct ] = FeedoptPlan( ctx )
%#codegen
% FeedoptPlan : 进给率优化有限状态机（FSM）——单步推进
%
% 每次调用推进 FSM 一个状态。对于 Init/GCode/Check/Compress/Smooth/Split
% 这些一次性阶段，单次调用即可完成并跳入下一状态；对于 Opt 阶段，
% 每次调用仅产出一段优化结果（滑动窗口一步），外层 FeedoptPlanRun 循环
% 反复调用直至 ctx.op 到达 Finished。
%
% 状态转换顺序：
%   Init → GCode → Check → Compress → Smooth → Split → Opt → Finished
%
% Inputs :
%   ctx        : 流水线上下文（含 FSM 状态 ctx.op、各阶段队列、配置等）
%
% Outputs :
%   ctx        : 更新后的上下文
%   optimized  : 本次调用是否产出了一段优化结果（仅 Opt 阶段可为 true）
%   opt_struct : 当 optimized=true 时，包含优化进给率系数的 CurvStruct
%
optimized  = false;
opt_struct = constrCurvStructType;

% 进入 FSM 前先确认上一次的错误码已被处理，否则不应继续推进
ocn_assert( ctx.errcode == FeedoptPlanError.NoError, ...
    "FeedoptPlan: error code was not handled...", mfilename );

switch ctx.op

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Init
    % 初始化阶段：initFeedoptPlan 已完成所有预计算，此处仅跳转到 GCode。
    % ══════════════════════════════════════════════════════════════════════
        ctx.op = Fopt.GCode;

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.GCode
    % G-Code 解析阶段：调用 rs274ngc 解释器逐条读取 G-Code 指令，
    % 将每条有效曲线转换为 CurvStruct 并压入 q_gcode。
    %
    % 主要处理：
    %   1. 换刀检测 → 在换刀前后的曲线两端插入零速标记（NZ/ZN）
    %   2. 刀具长度偏移补偿（add_tool_offset）
    %   3. 旋转轴单位转换：度 → 弧度
    %   4. NaN 坐标归零（未指定轴保持前一位置，简化处理为 0）
    %   5. 最后一段末端强制设零速（NZ 或 ZZ）
    %   6. assert_queue 三项几何合法性验证
    % ══════════════════════════════════════════════════════════════════════
        ctx.k0      = int32( 1 );
        status      = ReadGCode( ctx.cfg, ReadGCodeCmd.Load, ctx.cfg.source );
        CurvStruct  = opt_struct;
        CurvStruct.Info.Type = CurveType.None;
        DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );

        while status < ReadGCodeError.InterpNotOpen
            % 上一次读取到的有效曲线延迟推入队列（在本次循环开头处理）
            if( CurvStruct.Info.Type ~= CurveType.None )
                ctx.q_gcode.push( CurvStruct );
                ctx.k0 = ctx.k0 + 1;
            end

            if( status == ReadGCodeError.InterpExit )
                break;  % 解释器已读完文件，退出读取循环
            end

            [ status, CurvStruct ] = ReadGCode( ctx.cfg, ReadGCodeCmd.Read, ...
                ctx.cfg.source );

            if( CurvStruct.Info.Type ~= CurveType.None )
                if( ctx.q_gcode.isempty )
                    prev_tool = constrToolStructType;  % 队列为空，使用默认刀具
                else
                    prev_tool = ctx.q_gcode.rget(1).tool;

                    % ── 换刀检测 ──────────────────────────────────────────
                    % 前后两段刀具不同 → 在边界插入零速停顿：
                    %   前一段末端设 NZ（若已是 ZN 则设 ZZ）
                    %   当前段起端设 ZN（若已是 NZ 则设 ZZ）
                    if( ~toolIsEqual(prev_tool, CurvStruct.tool ) )
                        curv1 = ctx.q_gcode.rget(1);
                        if( isAZeroStart(curv1) )
                            curv1.Info.zspdmode = ZSpdMode.ZZ;
                        else
                            curv1.Info.zspdmode = ZSpdMode.NZ;
                        end
                        ctx.q_gcode.set(ctx.q_gcode.size, curv1);

                        if( isAZeroEnd(CurvStruct) )
                            CurvStruct.Info.zspdmode = ZSpdMode.ZZ;
                        else
                            CurvStruct.Info.zspdmode = ZSpdMode.ZN;
                        end
                    end
                end

                % ── 刀具长度偏移补偿 ──────────────────────────────────────
                % 换刀过渡在当前 CurvStruct 段内完成：
                %   R0（起点）使用 prev_tool 偏移 → 与前段终点几何连续
                %   R1（终点）使用 CurvStruct.tool 偏移 → 新刀生效
                % 因此新刀的完整坐标从下一段起才是纯新刀空间，
                % 而零速停顿（NZ/ZN）已打在本段起端，机床换刀后再执行本段。
                [CurvStruct] = add_tool_offset( CurvStruct, ...
                    ctx.cfg.indCart, prev_tool );

                % ── 旋转轴单位转换：度 → 弧度（第 4 轴起为旋转轴）──────────
                CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
                CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );

                % ── NaN 归零（G-Code 中未指定的轴坐标为 NaN）────────────────
                for j = 1 : StructTypeName.NumberAxisMax
                    if isnan( CurvStruct.R0( j ) )
                        CurvStruct.R0( j ) = 0 ;
                    end
                    if isnan( CurvStruct.R1( j ) )
                        CurvStruct.R1( j ) = 0;
                    end
                end

                ocn_assert( CurvStruct.Info.FeedRate > 0.0, ...
                    "Feedrate is not valide...", mfilename );
            end
        end

        ocn_assert( ~ctx.q_gcode.isempty(), "Gcode queue is empty", mfilename );

        % ── 最后一段末端强制设零速 ────────────────────────────────────────
        % 程序结束必须停止，末段末端始终为零速（NZ；若起端也是零速则为 ZZ）
        last = ctx.q_gcode.rget(1);
        if( isAZeroStart(last) )
            last.Info.zspdmode = ZSpdMode.ZZ;
        else
            last.Info.zspdmode = ZSpdMode.NZ;
        end
        ctx.q_gcode.set( ctx.q_gcode.size, last );

        ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        ctx.op = Fopt.Check;

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Check
    % 几何检查阶段：遍历相邻曲线对，检测方向突变（尖点）。
    % 超过 cfg.Cusp.Threshold 角度阈值的相邻段边界插入零速停顿。
    % cfg.Cusp.Skip=true 时跳过，直接进入下一阶段（调试用）。
    % ══════════════════════════════════════════════════════════════════════
        if ~ctx.cfg.Cusp.Skip
            ctx = CheckCurvStructs( ctx );
        end

        ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        ctx.op = Fopt.Compress;

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Compress
    % 曲线压缩阶段：将连续的共线短直线段批次拟合为一条 B 样条（Lee 算法），
    % 减少后续处理的曲线数量。
    % cfg.Compressing.Skip=true 时直接复制 q_gcode → q_compress（调试用）。
    % 完成后按需释放 q_gcode 内存。
    % ══════════════════════════════════════════════════════════════════════
        if ctx.cfg.Compressing.Skip
            for j = 1 : ctx.q_gcode.size
                ctx.q_compress.push( ctx.q_gcode.get( j ) );
            end
        else
            ctx = compressCurvStructs(ctx);
        end

        ctx = assert_queue( ctx, ctx.op, ctx.q_compress );
        ctx.op = Fopt.Smooth;
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_gcode.delete(); end

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Smooth
    % 平滑过渡阶段：在几何不连续的相邻曲线之间插入 G2 Hermite 五次多项式
    % 过渡曲线（TransP5），保证曲率连续；无法过渡时退化为零速停顿。
    % 完成后按需释放 q_compress 内存。
    % ══════════════════════════════════════════════════════════════════════
        ctx = smoothCurvStructs(ctx);
        ctx.op = Fopt.Split;

        ctx = assert_queue( ctx, ctx.op, ctx.q_smooth );
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_compress.delete(); end

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Split
    % 曲线分割阶段：
    %   1. 零速起始/终止段从两端切出恒定跃度加减速小段（cutZeroStart/End）
    %   2. 其余曲线按等弧长（cfg.LSplit）或 B 样条断点分割为短段
    % 分割后 q_split 段数通常远多于 q_smooth（10× 量级）。
    % 完成后初始化 DebugOptimization 并按需释放 q_smooth 内存。
    % ══════════════════════════════════════════════════════════════════════
        ctx    = splitQueue( ctx );
        ctx.op = Fopt.Opt;

        if( coder.target( 'MATLAB' ) )
            DebugOptimization.getInstance.reset;
        end

        ctx = assert_queue( ctx, ctx.op, ctx.q_split );
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_smooth.delete(); end

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Opt
    % 进给率优化阶段（多次重入）：
    %   每次调用通过滑动窗口取出 NHorz 段，求解两阶段 LP，产出一段优化结果。
    %   feedratePlanning 返回 optimized=true 时将结果压入 q_opt 并前移游标；
    %   返回 quit=true 时所有段已处理完毕，直接 return 让外层检测 Finished。
    % ══════════════════════════════════════════════════════════════════════
        if( ctx.q_opt.size() == 0 ), ctx.k0 = int32( 1 ); end

        [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        if optimized
            ctx.go_next = true;
            ctx.q_opt.push( opt_struct );
        end

        if( quit ), return; end

    % ══════════════════════════════════════════════════════════════════════
    case Fopt.Finished
    % 终止状态：保持 Finished，外层循环检测到此状态后退出。
    % ══════════════════════════════════════════════════════════════════════
        ctx.op = Fopt.Finished;

    otherwise
        % 不应出现的非法状态，记录日志后强制终止
        DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;

end

end

% ══════════════════════════════════════════════════════════════════════════
function [ ctx ] = assert_queue( ctx, op, queue )
% assert_queue : 对指定队列执行三项合法性断言
%
% 在每个阶段结束、状态跳转前调用，确保产出队列满足后续阶段的前提条件。
%
% 三项检验：
%   1. checkGeometry        — 相邻曲线几何首尾连续（R1_k ≈ R0_{k+1}）
%   2. checkZSpdmode        — 零速模式传递合法（NZ 后必须接 ZN/ZZ 等）
%   3. checkParametrisation — 每段参数窗口合法（a>0, b≥0, a+b≤1）
%
% 任一检验失败则 ocn_assert 抛出异常，由 FeedoptPlanRun 捕获并终止流水线。
% ══════════════════════════════════════════════════════════════════════════
msg = string( op );

ocn_assert( checkGeometry( queue ), ...
    msg + " - Check geometry failed...", mfilename );

[ isValid, ctx ] = checkZSpdmode( ctx, queue );
ocn_assert( isValid, ...
    msg + " - Check zspdmode failed...", mfilename );

isValid = checkParametrisationQueue( queue );
ocn_assert( isValid, ...
    msg + " - Check parametrisation failed...", mfilename );
end
