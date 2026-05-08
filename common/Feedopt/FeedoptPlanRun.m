function [ ctx ] = FeedoptPlanRun( ctx )
% FeedoptPlanRun : 有限状态机（FSM）的外层驱动循环
% 持续调用 FeedoptPlan（单步状态机），直到状态变为 Finished
%
% Inputs :
%   ctx : 计算链上下文（由 initFeedoptPlan 创建）
% Outputs :
%   ctx : 更新后的上下文（含优化结果队列 q_opt）
%

% 代码生成配置：显示带颜色的编译诊断信息
coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')

prev_operation  = Fopt.Init; % 记录上一次状态，用于在状态切换时打印队列长度

% 主循环：直到 FSM 到达 Finished 状态
while ctx.op ~= Fopt.Finished

    % MATLAB 模式下：检测到状态发生跳转时，打印上一阶段产出的队列长度
    if( coder.target( 'MATLAB') )
        if prev_operation ~= ctx.op
            switch prev_operation
                case Fopt.GCode
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op GCODE : " + ctx.q_gcode.size(), mfilename );
                case Fopt.Check
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op CHECK : " + ctx.q_gcode.size(), mfilename );
                case Fopt.Compress
                    if( coder.target( "MATLAB" ) )
                        DebugCusp.getInstance.print( ctx );       % 打印尖点调试信息
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op COMPRESS : " + ctx.q_compress.size(), mfilename );
                case Fopt.Smooth
                    if( coder.target( "MATLAB" ) )
                        DebugCompressing.getInstance.print;       % 打印压缩调试信息
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op SMOOTH : " + ctx.q_smooth.size(), mfilename );
                case Fopt.Split
                    if( coder.target( "MATLAB" ) )
                        DebugTransition.getInstance.print( ctx ); % 打印过渡曲线调试信息
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op SPLIT : " + ctx.q_split.size(), mfilename );
                case Fopt.Opt
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op OPT : " + ctx.q_opt.size(), mfilename );
            end
            prev_operation = ctx.op; % 更新"上一状态"记录
        end
    end

    % 执行 FSM 单步：返回时 ctx.op 可能已经跳转到下一状态
    try
        [ ctx, optimized, opt_curv ] = FeedoptPlan( ctx );
    catch ME
        % 捕获异常：记录发生错误时的状态，并强制进入 Finished
        ctx.errcode     = ctx.op;
        ctx.errmsg      = constrMsgStruct( ME.message );
        ctx.op          = Fopt.Finished;
    end
end

end
