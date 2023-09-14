function ctx = FeedoptPlanRun( ctx )

coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')

prev_operation  = Fopt.Init;

while ctx.op ~= Fopt.Finished
    if( coder.target( 'MATLAB') ) 
        if prev_operation ~= ctx.op
            switch prev_operation
                case Fopt.GCode
                    disp("Queue length after op GCODE : " + ctx.q_gcode.size());
                case Fopt.Check
                    disp("Queue length after op CHECK : " + ctx.q_gcode.size());
                case Fopt.Compress
                    disp("Queue length after op COMPRESS : " + ctx.q_compress.size());
                case Fopt.Smooth
                    disp("Queue length after op SMOOTH : " + ctx.q_smooth.size());
                case Fopt.Split
                    disp("Queue length after op SPLIT : " + ctx.q_split.size());
                case Fopt.Opt
                    disp("Queue length after op OPT : " + ctx.q_opt.size());
            end
            prev_operation = ctx.op;
        end
    end

    [ ctx, optimized, opt_curv ] = FeedoptPlan( ctx );
end

end