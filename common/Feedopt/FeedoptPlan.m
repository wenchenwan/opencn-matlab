function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
%#codegen
% See InitFeedoptPlan for information about the context variable ctx

c_assert( ctx.errcode == FeedoptPlanError.Success, ...
    'FeedoptPlan: error code was not handled' );

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
            [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, ...
                ctx.cfg.source );
            if( ctx.q_gcode.isempty )
                prev_tool = constrToolStructType;
            else
                prev_tool = ctx.q_gcode.rget(1).tool;
                
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

            [CurvStruct] = add_tool_offset( CurvStruct, ctx.cfg.indCart, prev_tool );
            
            CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );

            for j = 1 : StructTypeName.NumberAxisMax
                if isnan( CurvStruct.R0( j ) )
                    CurvStruct.R0( j ) = 0 ;
                end
                if isnan( CurvStruct.R1( j ) )
                    CurvStruct.R1( j ) = 0;
                end
            end

            if( CurvStruct.Info.FeedRate == 0.0 )
                CurvStruct.Info.FeedRate = ctx.cfg.fmax;
            end
            if( status == 1 && CurvStruct.Info.Type ~= CurveType.None )
                if ( CurvStruct.Info.FeedRate == 0.0 )
                    % check for undefined feedrate
                    CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                end
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
        if( isAZeroStart(last) )
            last.Info.zspdmode = ZSpdMode.ZZ;
        else
            last.Info.zspdmode = ZSpdMode.NZ;
        end
        ctx.q_gcode.set( ctx.q_gcode.size, last );

        assert( checkZSpdmode( ctx.q_gcode ), "ERROR : " + mfilename ...
            + ".m : Check zspdmode failed " );
        assert( checkParametrisation( ctx.q_gcode ), "ERROR : " + mfilename ...
            + ".m : Check parametrisation failed " );

        ctx.op = Fopt.Check;

    case Fopt.Check
        ctx.op = Fopt.Finished; return;
%         [ ctx.q_gcode ] = checkTrafo( ctx, ctx.q_gcode );
%         histogramLength( ctx, ctx.q_gcode, "Gcode");
        if ~ctx.cfg.Cusp.Skip
            ctx     = CheckCurvStructs( ctx );
        end
        assert( checkZSpdmode( ctx.q_gcode ), "ERROR : " + mfilename ...
            + ".m : Check zspdmode failed " );
        assert( checkParametrisation( ctx.q_gcode ), "ERROR : " + mfilename ...
            + ".m : Check parametrisation failed " );

        ctx.op  = Fopt.Compress;

    case Fopt.Compress
        if ctx.cfg.Compressing.Skip
            for j = 1 : ctx.q_gcode.size % Copy queue GCode in queue Compress
                ctx.q_compress.push( ctx.q_gcode.get( j ) );
            end
        else
            ctx = compressCurvStructs(ctx);
        end

        assert( checkZSpdmode( ctx.q_compress ), "ERROR : " + mfilename ...
            + ".m : compress zspdmode failed " );
        assert( checkParametrisation( ctx.q_compress ), "ERROR : " + mfilename ...
            + ".m : Check parametrisation failed " );

        ctx.op = Fopt.Smooth;
        if( coder.target( 'MATLAB') ), ctx.q_gcode.delete(); end

    case Fopt.Smooth
%         histogramLength( ctx, ctx.q_compress, "Compressing" );

        ctx = smoothCurvStructs(ctx);
        ctx.op = Fopt.Split;

        assert( checkZSpdmode( ctx.q_smooth ), "ERROR : " + mfilename ...
            + ".m : smooth zspdmode failed " );
        assert( checkParametrisation( ctx.q_smooth ), "ERROR : " + mfilename ...
            + ".m : Check parametrisation failed " );

        if( coder.target( 'MATLAB') ), ctx.q_compress.delete(); end

    case Fopt.Split
%         histogramLength( ctx, ctx.q_smooth, "Smoothing" );

        ctx = splitQueue( ctx );

        ctx.op = Fopt.Opt;

        assert( checkZSpdmode( ctx.q_split ), "ERROR : " + mfilename ...
            + ".m : splitted zspdmode failed " );
        assert( checkParametrisation( ctx.q_smooth ), "ERROR : " + mfilename ...
            + ".m : Check parametrisation failed " );

%         histogramLength( ctx, ctx.q_split, "Splitting" );        
        if( coder.target( 'MATLAB' ) ), ctx.q_smooth.delete(); end

    case Fopt.Opt
        [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        if optimized
            ctx.go_next = true;
            ctx.q_opt.push( opt_struct );
        end

        if( quit ), return; end

    case Fopt.Finished
        ctx.op = Fopt.Finished;

    otherwise
        DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;

end

end