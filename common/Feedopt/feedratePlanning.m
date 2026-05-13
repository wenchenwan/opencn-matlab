function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
%#codegen
% feedratePlanning : 进给率优化主控函数（后退视界滑动窗口 / Receding Horizon）
%
% ═══════════════════════════════════════════════════════════════════════════
% 【一、滑动窗口机制（Receding Horizon / MPC 风格）】
%
%   本函数每次被外层循环调用一次，处理 q_split 队列中的一段曲线（k0 段）。
%   每次调用都重新构造一个包含 NHorz 段的"前瞻窗口"，联合求解 LP，
%   但只把窗口第一段（k0 段）的结果写入输出，然后 k0 前进一格。
%
%   窗口重叠量 = NHorz - 1（相邻两次调用共享 NHorz-1 段）：
%
%     调用1: k0=1  窗口=[1  2  3  4]  → LP → 只写段1的 Coeff
%     调用2: k0=2  窗口=  [2  3  4  5] → LP → 只写段2的 Coeff
%     调用3: k0=3  窗口=    [3  4  5  6]→ LP → 只写段3的 Coeff
%
%   为什么不直接用一次 LP 的全部结果？
%     窗口末尾每次都新加入一段曲线，新约束（如急转弯、速度上限）会
%     反向影响窗口内所有段的最优速度。重新求解保证当前段的 Coeff 始终
%     是在最新前瞻信息下的最优解——这是 MPC 策略的核心代价与收益。
%
%   窗口截断例外（feedratePlanningGetwindow）：
%     遇到 ZeroEnd 段时窗口提前截断，零速停顿两侧完全解耦，
%     无需跨停顿点联合优化。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【二、两条执行路径】
%
%   路径 A（~ctx.zero_end，正常路径）：
%     构造窗口 → 剥离零速边界段，计算边界条件 → LP 求解 → 写入系数
%     本函数每次调用产出一段结果。
%
%   路径 B（ctx.zero_end=true，零速结束路径）：
%     上一次 LP（包含 ZeroEnd 段的那次）已将该窗口的全部系数保存在
%     ctx.Coeff 中，此路径不再调用 LP，直接按 kopt 游标逐段分发系数。
%     适用场景：紧接在 ZeroEnd 段之前的若干段，速度必须从某值减速到零，
%     这些段的系数在发现 ZeroEnd 时已一次性求出。
%
% ═══════════════════════════════════════════════════════════════════════════
% 【三、零速段处理摘要】
%
%   ZeroStart 段（curv.UseConstJerk=true）：
%     速度剖面已在 cutZeroStart → zeroSpeedCurv 阶段预算，存于 ConstJerk。
%     LP 结果不适用于该段；本函数跳过写 Coeff，仅清除 ctx.zero_start 标记。
%
%   ZeroEnd 段：
%     作为窗口右侧边界，被 feedratePlanningSetupCurves 剥离出窗口，
%     其末端速度 = 0 作为 LP 的右端约束（v_1=0）传入。
%     该段本身也不写 Coeff（插补时由 ConstJerk 驱动）。
%
% ═══════════════════════════════════════════════════════════════════════════
% Inputs :
%   ctx : 计算链上下文（含 q_split、k0、zero_start/end、Coeff 等字段）
%
% Outputs :
%   ctx        : 更新后的上下文
%   optimized  : 本次是否产出了一个优化结果（false 表示跳过）
%   opt_struct : 产出的优化曲线段（Coeff 或 ConstJerk 已填写）
%   quit       : true 表示 q_split 全部处理完毕，外层应停止循环
%

% kopt：窗口内的列游标，用于 zero_end 路径按序分发 ctx.Coeff 的各列。
%   正常路径（每次 LP 重新求解）：kopt 在 LP 成功后重置为 1，
%   只取 Coeff(:,1)（窗口第一段），随后 kopt=2（但下次调用又重置为 1）。
%   zero_end 路径：kopt 从 1 连续递增，将 ctx.Coeff(:,1..N) 分发给 N 段曲线。
persistent kopt;
if( isempty( kopt ) ), kopt = 1; end

opt_struct  = constrCurvStructType; % 默认空输出（本次无产出时返回）
quit        = false;
optimized   = false;
ctx.op      = Fopt.Opt;             % 保持 Opt 状态，外层据此继续调用

% 特殊情况：q_split 为空说明所有曲线均为零速段（纯停顿轨迹），直接结束
if ctx.q_split.isempty
    [ ctx.op, quit ] = empty_queue_split( ctx.cfg.ENABLE_PRINT_MSG );
    return;
end

ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + ...
    ctx.q_split.size, mfilename );

% go_next 由上一次调用的成功标志驱动：
%   上次成功产出一段 → 本次 k0 前进；上次失败/跳过 → k0 保持不动重试
if ctx.go_next, ctx.k0 = ctx.k0 + 1; end

if ( ctx.k0 <= ctx.q_split.size )

    if ~ctx.zero_end
        % ════════════════════════════════════════════════════════════════
        % 路径 A：正常优化路径
        %   流程：构造窗口 → 剥离零速边界 → LP 求解 → 写入当前段系数
        %   每次调用 LP 重新求解整个窗口（滑动窗口 MPC）。
        % ════════════════════════════════════════════════════════════════

        % 从 k0 取 NHorz 段构成前瞻窗口；遇 ZeroEnd 提前截断
        % → 保证窗口内速度约束可以在停顿边界处自然解耦
        % 如果遇到零速边界，就终止窗口
        [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0, ...
                                ctx.cfg.NHorz, ctx.q_split );

        % 剥离窗口首/尾的零速段，计算连接点处的边界条件：
        %   ZeroStart → v_0, at_0（窗口左端速度/切向加速度初值）
        %   ZeroEnd   → v_1, at_1（窗口右端速度/切向加速度终值 = 0）
        %   普通末端  → v_1 = cfg.v_1（配置预设的终端速度约束）
        [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
                ctx, window, NWindow );

        % LP 求解：以速度平方系数 Coeff 为决策变量，
        %   满足各段的速度/加速度约束及窗口边界条件。
        %   Coeff 尺寸 = (基函数数) × NWindow，每列对应窗口内一段曲线。
        [ ctx, Coeff, success, status, msg ] = ...
            FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
            ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
            ctx.u_vec, NWindow );

        % LP 失败回退：在窗口内强制插入零速停止点，将窗口拆成两个解耦子问题，
        %   再次求解。典型失败原因：窗口内曲率突变导致联合约束不可行。
        if( ~( success || ctx.zero_start || ctx.zero_end ) )
            [ ctx, window, NWindow ] = feedratePlanningForceZeroStop( ...
                ctx, window, NWindow );
            [ ctx, Coeff, success, status, msg ] = ...
                FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
                ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
                ctx.u_vec, NWindow );
        end

        if( success )
            if( coder.target( 'MATLAB' ) )
                % 调试记录：保存本次窗口结果供可视化分析
                curvArray = window( 1 : NWindow );
                DebugOptimization.getInstance().add_result( ctx, ctx.Bl, ...
                    ctx.BasisVal, curvArray, Coeff );
            end

            % 每次 LP 成功后 kopt 重置为 1：
            %   滑动窗口每次只消费 Coeff 的第 1 列（k0 段），
            %   kopt>1 仅在 zero_end 路径（路径 B）跨调用递增时有意义。
            kopt = 1;

            optimized  = true;
            opt_struct = ctx.q_split.get( ctx.k0 ); % 当前待输出的曲线段

            if( ~isAZeroStart( opt_struct ) )
                % ── 正常段 ──────────────────────────────────────────────
                % 将 LP 结果第 kopt 列写入曲线，插补阶段据此生成速度指令。
                % 正常路径下 kopt 恒为 1（每次 LP 后重置），写完即递增。
                opt_struct.Coeff = Coeff( :, kopt );
                kopt = kopt + 1;
            else
                % ── ZeroStart 段 ────────────────────────────────────────
                % 该段速度剖面已在 cutZeroStart → zeroSpeedCurv 中预算：
                %   opt_struct.ConstJerk = jps（恒定伪跃度值）
                % 插补时走 constJerkU 方案，与 LP Coeff 无关，故跳过写入。
                % kopt 不递增：该段未消耗 LP 的一列，下一段仍从列1取系数。
                ctx.zero_start = false;
            end

            % 若当前窗口已延伸到队列末尾，标记"已到达终点"
            % （供外层判断是否可以安全结束整条轨迹的优化）
            if( ctx.zero_end && ( ctx.k0 + NWindow ) >= ctx.q_split.size )
                ctx.reached_end = true;
            end

        else
            % 两次 LP 均失败：不应发生，断言终止以暴露问题
            ocn_assert( true, "OPTIMIZATION FAILED...", mfilename );
        end

    else
        % ════════════════════════════════════════════════════════════════
        % 路径 B：零速结束路径（ctx.zero_end = true）
        %
        %   触发时机：上一次正常路径的 LP 窗口包含了 ZeroEnd 段，
        %   feedratePlanningSetupCurves 将 ZeroEnd 段剥离并将 v_1=0 作为
        %   右端约束传给 LP，LP 求出的 Coeff 已包含减速到零的完整系数，
        %   保存在 ctx.Coeff 中。
        %
        %   此后若干次调用（直到 zero_end 被清除）不再调用 LP，
        %   只按 kopt 游标从 ctx.Coeff 中逐列分发系数，效率更高。
        %
        %   kopt 在路径 B 跨调用持续递增（1→2→3…），与路径 A 重置为 1 不同。
        % ════════════════════════════════════════════════════════════════
        optimized = true;

        if( ctx.zero_forced && ( kopt > size( ctx.Coeff, 2 ) ) )
            % 强制零速（feedratePlanningForceZeroStop）产生了额外的备用曲线，
            % 系数已全部分发完（kopt 越界）。从 zero_forced_buffer 取回备用段，
            % 回退 k0 重新纳入队列，下次用正常路径处理。
            opt_struct          = ctx.zero_forced_buffer( 1 );
            ctx.q_split.set( ctx.k0, ctx.zero_forced_buffer( 2 ) );
            ctx.k0              = ctx.k0 - 1;
            ctx.zero_forced     = false;
        else
            opt_struct = ctx.q_split.get( ctx.k0 );
        end

        if( ~isAZeroEnd( opt_struct ) )
            % 普通减速段：分发对应列的预存系数
            opt_struct.Coeff = ctx.Coeff( :, kopt );
        else
            % ZeroEnd 段本身：使用 ConstJerk 驱动，不写 LP 系数；
            % 清除 zero_end 标记，下次调用恢复路径 A。
            ctx.zero_end = false;
        end

        kopt = kopt + 1; % 游标前移，下次分发下一列

    end

else
    % q_split 全部处理完毕，状态机进入 Finished
    ctx.op = Fopt.Finished;
end
end

function [ op, quit ] = empty_queue_split( enablePrint )
% q_split 为空时的处理：直接标记为完成
if coder.target( 'MATLAB' )
    diary on;
end
ocn_print( enablePrint, "Queue empty...", mfilename );
op   = Fopt.Finished;
quit = true;
end
