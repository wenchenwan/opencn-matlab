function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
%#codegen
% feedratePlanning : 进给率优化主控函数（滑动窗口策略）
%
% 设计思路（滑动窗口）：
%   q_split 中存放已分割好的短曲线段，本函数从 k0 处取 NHorz 段组成
%   一个优化"窗口"，调用 FeedratePlanning_LP 求解 LP 问题，
%   取第一段（k0 段）的优化结果推入 q_opt，然后 k0++，滑动到下一段。
%   如此滚动直到 k0 超过 q_split.size，整条轨迹优化完成。
%
% 零速处理：
%   零速段（ZeroStart/ZeroEnd）需要特殊处理，此时跳过正常优化，
%   直接从 ctx.Coeff 中取上一次优化的剩余系数（ctx.zero_end 为 true）。
%
% Inputs :
%   ctx : 计算链上下文
%
% Outputs :
%   ctx        : 更新后的上下文
%   optimized  : 本次是否产出了一个优化结果
%   opt_struct : 产出的优化曲线段（含 Coeff 进给率系数）
%   quit       : true 表示 q_split 处理完毕，外层应停止
%

% persistent 保持窗口内曲线段的计数器（跨多次调用）
persistent kopt;
if( isempty( kopt ) ), kopt = 1; end

opt_struct  = constrCurvStructType; % 默认空输出
quit        = false;
optimized   = false;
ctx.op      = Fopt.Opt;             % 保持当前状态标记

% 若 q_split 为空（全部曲线被标记为零速），直接结束
if ctx.q_split.isempty
    [ ctx.op, quit ] = empty_queue_split( ctx.cfg.ENABLE_PRINT_MSG );
    return;
end

ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + ...
    ctx.q_split.size, mfilename );

% 若上一次优化成功（go_next=true），游标前进到下一段
if ctx.go_next, ctx.k0 = ctx.k0 + 1; end

if ( ctx.k0 <= ctx.q_split.size )

    if ~ctx.zero_end
        % ----------------------------------------------------------------
        % 正常路径：构造窗口 → 建立边界条件 → 调用 LP → 提取结果
        % ----------------------------------------------------------------

        % 取从 k0 开始的 NHorz 条曲线作为当前优化窗口
        [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0, ...
                                ctx.cfg.NHorz, ctx.q_split );

        % 设置窗口两端的速度/切向加速度边界条件（v_0, at_0, v_1, at_1）
        [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
                ctx, window, NWindow );

        % 第一次 LP 求解（速度 + 加速度约束，不含跃度）
        [ ctx, Coeff, success, status, msg ] = ...
            FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
            ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
            ctx.u_vec, NWindow );

        % 若第一次优化失败（且非零速边界），强制插入零速停止点后重试
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
                % 调试：记录本次优化窗口的结果
                curvArray = window( 1 : NWindow );
                DebugOptimization.getInstance().add_result( ctx, ctx.Bl, ...
                    ctx.BasisVal, curvArray, Coeff );
            end

            kopt = 1; % 重置窗口内游标

            optimized   = true;
            opt_struct  = ctx.q_split.get( ctx.k0 ); % 取当前游标指向的曲线段

            if( ~isAZeroStart( opt_struct ) )
                % 正常段：将 LP 解中第 kopt 列系数写入曲线
                opt_struct.Coeff = Coeff( :, kopt );
                kopt = kopt + 1;
            else
                % 零速起始段：不写系数，仅重置标记
                ctx.zero_start = false;
            end

            % 检查是否到达末尾（零速结束判断）
            if( ctx.zero_end && ( ctx.k0 + NWindow ) >= ctx.q_split.size )
                ctx.reached_end = true;
            end

        else
            % 优化彻底失败：触发断言终止（不应到达此分支）
            ocn_assert( true, "OPTIMIZATION FAILED...", mfilename );
        end

    else
        % ----------------------------------------------------------------
        % 零速结束路径：从上次优化的 ctx.Coeff 中逐段取系数
        % （已提前求解，此时只需按序分发）
        % ----------------------------------------------------------------
        optimized   = true;

        if( ctx.zero_forced && ( kopt > size( ctx.Coeff, 2 ) ) )
            % 强制零速缓冲区中有备用曲线（回退一段并重新分配）
            opt_struct  = ctx.zero_forced_buffer( 1 );
            ctx.q_split.set( ctx.k0, ctx.zero_forced_buffer( 2 ) );
            ctx.k0      = ctx.k0 - 1;
            ctx.zero_forced = false;
        else
            opt_struct = ctx.q_split.get( ctx.k0 );
        end

        if( ~isAZeroEnd( opt_struct ) )
            % 非零速结束段：分发下一列系数
            opt_struct.Coeff = ctx.Coeff( :, kopt );
        else
            % 零速结束段：清除标记，不写系数
            ctx.zero_end = false;
        end

        kopt = kopt + 1; % 移动到下一段

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
