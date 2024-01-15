function [ ctx ] = FeedoptPlanRun( ctx )
% FeedoptPlanRun : Entry point of the FSM
%
% Inputs :
%   ctx : The context of the computational chain
% Outputs :
%   ctx : The context of the computational chain
%
coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')

prev_operation  = Fopt.Init;

while ctx.op ~= Fopt.Finished
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
                        DebugCusp.getInstance.print( ctx );
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op COMPRESS : " + ctx.q_compress.size(), mfilename );
                case Fopt.Smooth
                    if( coder.target( "MATLAB" ) )
                        DebugCompressing.getInstance.print;
                    end
                    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, ...
        "Queue length after op SMOOTH : " + ctx.q_smooth.size(), mfilename );
                case Fopt.Split
                    if( coder.target( "MATLAB" ) )
                        DebugTransition.getInstance.print( ctx );
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

    try
        [ ctx, optimized, opt_curv ] = FeedoptPlan( ctx );
    catch ME
        ctx.errcode     = ctx.op;
        ctx.errmsg      = constrMsgStruct( ME.message );
        ctx.op          = Fopt.Finished;
    end
end

end
