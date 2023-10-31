function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
%#codegen

optimized = false;

opt_struct = constrCurvStructType;

% See InitFeedoptPlan for information about the context variable ctx
ocn_assert( ctx.errcode == FeedoptPlanError.NoError, ...
    "FeedoptPlan: error code was not handled...", mfilename );

switch ctx.op
    case Fopt.Init
        ctx.op = Fopt.GCode;
        %
    case Fopt.GCode
        ctx.k0      = int32(1);
        status      = ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source );
        CurvStruct  = opt_struct;
        CurvStruct.Info.Type = CurveType.None;
        DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
        %
        while status < ReadGCodeError.InterpNotOpen
            if( CurvStruct.Info.Type ~= CurveType.None )
                ctx.q_gcode.push( CurvStruct );
                ctx.k0 = ctx.k0 + 1;
            end

            if( status == ReadGCodeError.InterpExit )
                break;
            end

            [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, ...
                ctx.cfg.source );

            if( CurvStruct.Info.Type ~= CurveType.None )
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
            end
        end
        % Error if gcode queue is empty
        ocn_assert( ~ctx.q_gcode.isempty(), "Gcode queue is empty", mfilename );

        last = ctx.q_gcode.rget(1);
        if( isAZeroStart(last) )
            last.Info.zspdmode = ZSpdMode.ZZ;
        else
            last.Info.zspdmode = ZSpdMode.NZ;
        end
        ctx.q_gcode.set( ctx.q_gcode.size, last );

        assert_queue( ctx.op, ctx.q_gcode );

        ctx.op = Fopt.Check;

    case Fopt.Check
        if ~ctx.cfg.Cusp.Skip
            ctx     = CheckCurvStructs( ctx );
        end

        assert_queue( ctx.op, ctx.q_gcode );

        ctx.op  = Fopt.Compress;

    case Fopt.Compress
        if ctx.cfg.Compressing.Skip
            for j = 1 : ctx.q_gcode.size % Copy queue GCode in queue Compress
                ctx.q_compress.push( ctx.q_gcode.get( j ) );
            end
        else
            ctx = compressCurvStructs(ctx);
        end

        assert_queue( ctx.op, ctx.q_compress );

        ctx.op = Fopt.Smooth;
        if( coder.target( 'MATLAB') ), ctx.q_gcode.delete(); end

    case Fopt.Smooth
        ctx = smoothCurvStructs(ctx);
        ctx.op = Fopt.Split;

        assert_queue( ctx.op, ctx.q_smooth );

        if( coder.target( 'MATLAB') ), ctx.q_compress.delete(); end

    case Fopt.Split
        ctx     = splitQueue( ctx );
        ctx.op  = Fopt.Opt;

        if( coder.target( 'MATLAB' ) )
            DebugOptimization.getInstance.reset;
        end

        assert_queue( ctx.op, ctx.q_split );

        %         histogramLength( ctx, ctx.q_split, "Splitting" );
        if( coder.target( 'MATLAB' ) ), ctx.q_smooth.delete(); end

    case Fopt.Opt
        if( ctx.q_opt.size() == 0 ), ctx.k0 = int32( 1 ); end
        %         ctx.op = Fopt.Finished; return;
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

function assert_queue(op, queue)
msg = string( op );
ocn_assert( checkGeometry( queue ), ...
    msg + " - Check geometry failed...", mfilename );
ocn_assert( checkZSpdmode( queue ), ...
    msg + " - Check zspdmode failed...", mfilename );
ocn_assert( checkParametrisation( queue ), ...
    msg + " - Check parametrisation failed...", mfilename );
end