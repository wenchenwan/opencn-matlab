function [ ctx ] = FeedoptPlanRun( ctx )
% FeedoptPlanRun : 进给率优化 FSM 的顶层驱动循环
%
% 本函数是整个七阶段流水线的入口。它反复调用 FeedoptPlan（一步步推进 FSM），
% 直到状态机到达 Fopt.Finished 为止。
%
% 流程概览：
%   Init → GCode → Check → Compress → Smooth → Split → Opt → Finished
%
% 调试输出（仅在 MATLAB 环境下，非 codegen）：
%   每当 FSM 状态发生切换时，打印上一阶段对应队列的当前长度，并触发各阶段
%   的调试单例打印（DebugCusp / DebugCompressing / DebugTransition）。
%
% 异常处理：
%   若 FeedoptPlan 抛出异常，则将错误码和错误信息记录到 ctx，并强制
%   跳转到 Fopt.Finished，使循环正常退出。
%
% Inputs :
%   ctx : 流水线上下文结构体（含 FSM 状态 ctx.op、各阶段队列、配置 ctx.cfg 等）
%
% Outputs :
%   ctx : 执行完毕后的上下文（ctx.op == Fopt.Finished；
%         若有错误则 ctx.errcode / ctx.errmsg 已填写）
%
coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')

prev_operation  = Fopt.Init;

while ctx.op ~= Fopt.Finished

    % ── 调试信息打印（codegen 时跳过）────────────────────────────────────
    % 仅在 MATLAB 解释器下执行；每次状态切换后打印上一阶段的队列长度。
    if( coder.target( 'MATLAB') )
        if prev_operation ~= ctx.op
            switch prev_operation
                case Fopt.GCode
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op GCODE : " + ctx.q_gcode.size(), mfilename );
                case Fopt.Check
                    % Check 阶段原地修改 q_gcode，故打印的仍是 q_gcode 的长度
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op CHECK : " + ctx.q_gcode.size(), mfilename );
                case Fopt.Compress
                    if( coder.target( "MATLAB" ) )
                        DebugCusp.getInstance.print( ctx );   % 打印尖点检测统计
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op COMPRESS : " + ctx.q_compress.size(), mfilename );
                case Fopt.Smooth
                    if( coder.target( "MATLAB" ) )
                        DebugCompressing.getInstance.print;   % 打印压缩统计
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op SMOOTH : " + ctx.q_smooth.size(), mfilename );
                case Fopt.Split
                    if( coder.target( "MATLAB" ) )
                        DebugTransition.getInstance.print( ctx );  % 打印过渡曲线统计
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op SPLIT : " + ctx.q_split.size(), mfilename );
                case Fopt.Opt
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
                        "Queue length after op OPT : " + ctx.q_opt.size(), mfilename );
            end
            prev_operation = ctx.op;
        end
    end

    % ── 推进 FSM 一步 ────────────────────────────────────────────────────
    % FeedoptPlan 每次调用仅推进一个逻辑步骤（对 Opt 阶段而言是一个窗口）。
    % 若抛出异常，则记录错误并将状态设为 Finished，以保证循环能正常退出。
    try
        [ ctx, ~, ~ ] = FeedoptPlan( ctx );
    catch ME
        ctx.errcode     = ctx.op;                      % 记录出错时所在的阶段
        ctx.errmsg      = constrMsgStruct( ME.message );
        ctx.op          = Fopt.Finished;               % 强制终止循环
    end
end

end
