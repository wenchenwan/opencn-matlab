function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
%#codegen
% See InitFeedoptPlan for information about the context variable ctx

c_assert( ctx.errcode == FeedoptPlanError.Success, ...
                                'FeedoptPlan: error code was not handled');

optimized = false;

opt_struct = constrCurvStructType;

switch ctx.op
    case Fopt.Init
        ctx.op = Fopt.GCode;
        %
    case Fopt.GCode
        status = int32( ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source ) );
        DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
        %
        while status
            [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, '' );

            for i = 1:6
                if isnan(CurvStruct.R0(i))
                    CurvStruct.R0(i) = 0;
                end
                if isnan(CurvStruct.R1(i))
                    CurvStruct.R1(i) = 0;
                end
            end

            if( CurvStruct.Info.FeedRate == 0 )
                CurvStruct.Info.FeedRate = ctx.cfg.vmax; 
            end
            if( status == 1 && CurvStruct.Info.Type ~= 0 )
                if ( CurvStruct.Info.FeedRate == 0.0 ) 
                    % check for undefined feedrate
                    CurvStruct.Info.FeedRate = ctx.cfg.vmax;
                end
%                 PrintCurvStruct( ctx, CurvStruct );
                ctx.q_gcode.push( CurvStruct );
            end
        end
        if ctx.q_gcode.isempty()
            ctx.op = Fopt.Finished;
            DebugLog(DebugCfg.Warning, ...
                'ERROR: Optimization failed, Gcode queue is empty\n');
            return;
        end
        last = ctx.q_gcode.rget(1);
        if last.Info.zspdmode == ZSpdMode.NN
            last.Info.zspdmode = ZSpdMode.NZ;
        elseif last.Info.zspdmode == ZSpdMode.ZN
            last.Info.zspdmode = ZSpdMode.ZZ;
        end
        ctx.q_gcode.set( ctx.q_gcode.size, last );
        % For testing
        sizeGcode = ctx.q_gcode.size
%         geometricPlot( ctx )
        ctx.op = Fopt.Check;
    
    case Fopt.Check
        ctx     = CheckCurvStructs( ctx );
        ctx.op  = Fopt.Compress;

    case Fopt.Compress
        if ctx.cfg.Compressing.Skip
            ctx = ExpandZeroStructs(ctx);
        else
            ctx = compressCurvStructs(ctx);
        end

        % For testing
        sizeCompress = ctx.q_compress.size
%         geometricPlot( ctx )

        ctx.op = Fopt.Smooth;
        if( coder.target( 'MATLAB') ), ctx.q_gcode.delete(); end        
    
    case Fopt.Smooth
        ctx = smoothCurvStructs(ctx);

        % For testing
        sizeSmooth = ctx.q_smooth.size
%         geometricPlot( ctx )
         % Check of the zspdmode
        zspmodevec = zeros(1, sizeSmooth);
        for i = 1:sizeSmooth
            Curv = ctx.q_smooth.get(i);      % Get Curv in the queue
            Curv.Info.zspdmode
            zspmodevec(i) = Curv.Info.zspdmode;
        end

        ctx.op = Fopt.Split;
        if( coder.target( 'MATLAB') ), ctx.q_compress.delete(); end        
            
    case Fopt.Split
        ctx = SplitCurvStructs(ctx);

        % For testing
        sizeSplit = ctx.q_split.size
        ctx.op = Fopt.Finished; % SAUTE L'OPTIMISATION

        % Check of the zspdmode
        zspmodevec = zeros(1, sizeSplit);
        for i = 1:sizeSplit
            Curv = ctx.q_split.get(i);      % Get Curv in the queue
            Curv.Info.zspdmode
            zspmodevec(i) = Curv.Info.zspdmode;
        end

        if( coder.target( 'MATLAB') ), ctx.q_smooth.delete(); end        
    
        DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
        if coder.target('matlab')
            diary off;
        end
    
    case Fopt.Opt
%         [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
%         
%         if optimized
%             ctx.go_next = true;
%             ctx.q_opt.push( opt_curv );
%         end
% 
%         if( quit ), return; end

    case Fopt.Finished
        ctx.op = Fopt.Finished;
        
    otherwise
        DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;
        
end

end