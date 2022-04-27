function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
%#codegen
% See InitFeedoptPlan for information about the context variable ctx

c_assert(ctx.errcode == FeedoptPlanError.Success, 'FeedoptPlan: error code was not handled');


optimized = false;
% end_flag = false;

trafo = false; % TRAFO flag disable
HSC = false;
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

opt_struct = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
                               U1, 0.2, ZSpdMode.NN);

switch ctx.op
    case Fopt.Init
        ctx.op = Fopt.GCode;
    case Fopt.GCode

        status = int32(ReadGCode(ReadGCodeCmd.Load, ctx.cfg.source));
        DebugLog(DebugCfg.Validate, 'Reading G-code...\n');
        while status
            [status, CurvStruct] = ReadGCode(ReadGCodeCmd.Read, '');
            if( CurvStruct.FeedRate == 0 )
                CurvStruct.FeedRate = ctx.cfg.vmax; 
            end
            if status == 1 && CurvStruct.Type ~= 0
                if ( CurvStruct.FeedRate == 0.0 ) 
                    % check for undefined feedrate
                    CurvStruct.FeedRate = ctx.cfg.vmax;
                end
                ctx.q_gcode.push(CurvStruct);
            end
        end
        if ctx.q_gcode.isempty()
            ctx.op = Fopt.Finished;
            DebugLog(DebugCfg.Warning, ...
                'ERROR: Optimization failed, Gcode queue is empty\n');
            return;
        end
        last = ctx.q_gcode.rget(1);
        if last.zspdmode == ZSpdMode.NN
            last.zspdmode = ZSpdMode.NZ;
        elseif last.zspdmode == ZSpdMode.ZN
            last.zspdmode = ZSpdMode.ZZ;
        end
        ctx.q_gcode.set(ctx.q_gcode.size, last);
        ctx.op = Fopt.Check;
    
    case Fopt.Check
        ctx = CheckCurvStructs(ctx);
        ctx.op = Fopt.Compress;

    case Fopt.Compress
        if ctx.cfg.Compressing.Skip
            ctx = ExpandZeroStructs(ctx);
        else
            ctx = CompressCurvStructs(ctx);
        end
        ctx.op = Fopt.Smooth;
        if( coder.target( 'MATLAB') ), ctx.q_gcode.delete(); end        
    
    case Fopt.Smooth
        ctx = SmoothCurvStructs(ctx);
        ctx.op = Fopt.Split;
        if( coder.target( 'MATLAB') ), ctx.q_compress.delete(); end        
            
    case Fopt.Split
        ctx = SplitCurvStructs(ctx);
        
        ctx.op = Fopt.Opt;
        if( coder.target( 'MATLAB') ), ctx.q_smooth.delete(); end        
    
        DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
        if coder.target('matlab')
            diary off;
        end
    
    case Fopt.Opt
        [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
        
        if optimized
            ctx.go_next = true;
            ctx.q_opt.push( opt_curv );
        end

        if( quit ), return; end

    case Fopt.Finished
        ctx.op = Fopt.Finished;
        
    otherwise
        DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;
        
end

end