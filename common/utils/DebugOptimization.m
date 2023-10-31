 classdef ( Sealed ) DebugOptimization < handle
    properties
        DO_PLOT;
        MODE_AUTO;
        NB_SPLINE_POINTS;
        counter;
        results;
    end

    methods (Access = private)
        function [ obj ] = DebugOptimization
            obj.reset();
        end
        function [ result ] = constrResult( ~, coeff, spline_disc, ...
                spline_eval, curve_array, u_struct, vspline_disc, ...
                vspline_eval, feedrate )
            result = struct( "Coeff", coeff, "SplineDisc", spline_disc, ...
                "SplineEval", spline_eval, "CurveArray", curve_array, ...
                "UStruct", u_struct, "VSplineDisc", vspline_disc, ...
                "VSplineEval", vspline_eval, "FeedRate", feedrate );
        end
        function [ result ] = constrUstruct( ~, uCoeffM, uDiscM, ...
                uEvalM )
            result = struct( "uCoeff", uCoeffM, "uDisc", uDiscM, ...
                "uEval", uEvalM );
        end
        
    end

    methods
        function [ curveCoupleType ] = getCurvCoupleTypes( ~, curv )
            persistent curveTypeList;

            if( isempty( curveTypeList ) )
                curveTypeList   = { "Line", "Helix", "Spline", "TransP5" };
            end
            
            NbCurves        = length( curv );
            curveCoupleType = cell( [NbCurves, 0] );

            for j = 1 : NbCurves
                curveCoupleType{ j } = curveTypeList{ curv( j ).Info.Type };
            end
        
        end

        function [ obj ] = reset( obj )
            obj.DO_PLOT             = false;
            obj.MODE_AUTO           = true;
            obj.NB_SPLINE_POINTS    = 60;
            obj.counter             = 0;
            uStruct                 = obj.constrUstruct( [], [], [] );
            result      = obj.constrResult( [], [], [], [], uStruct, [], ...
                [], [] );
            obj.results = queue( result );
        end

        function [ obj ] = print( obj )
            disp( "****************************************************" );
            disp( "Optimization : " );
            disp( "Nb Optimization : " + obj.counter );
                
            if obj.DO_PLOT
                figureName = "Results from optimization";
                for j = 1 : obj.counter
                    result      = obj.results.get( j );
                    nbCurvs     = length( result.CurveArray );

%                     if( j <= 305 || j > 310  )
%                         continue;
%                     end
                    if( figflag( figureName ) )
                        figure( fig );
                    else
                        fig = figure( 'Name', figureName );
                    end
                    
                    subplot( 2, 1, 1 ); hold off;
                    if( 1 )
                        for ind = 1 : nbCurvs
                            semilogy( result.UStruct.uEval( :, ind ), ...
                                result.SplineEval( :, ind ), '-b' ); hold on; grid on;
                            semilogy( result.UStruct.uCoeff( :, ind ), ...
                                result.Coeff( : , ind), 's','MarkerSize',10,...
                            'MarkerEdgeColor','red',...
                            'MarkerFaceColor', [1 .6 .6] );
                            semilogy( result.UStruct.uDisc( :, ind ), ...
                                result.SplineDisc( : , ind ), 'k+' );
                        end
                    else
                        for ind = 1 : nbCurvs
                            plot( result.UStruct.uEval( :, ind ), ...
                                result.SplineEval( :, ind ), '-b' ); hold on; grid on;
                            plot( result.UStruct.uCoeff( :, ind ), ...
                                result.Coeff( : , ind), 's','MarkerSize',10,...
                                'MarkerEdgeColor','red',...
                                'MarkerFaceColor', [1 .6 .6] );
                            plot( result.UStruct.uDisc( :, ind ), ...
                                result.SplineDisc( : , ind ), 'k+' );
                        end
                    end
                    
                    curveTypes = obj.getCurvCoupleTypes( result.CurveArray );

                    vlines = xline( [ 0 : size( result.Coeff, 2 )-1 ], ...
                     '-', curveTypes );
                    yline( 0, '-k', 'LineWidth', 2 );
                    
                    set( vlines, 'LabelOrientation', 'horizontal' );
                    legend( [  "Spline Eval", "Coeff", "Spline Discretization", [] ] );
                    title( "Results from optimization " + j + "/" + obj.counter);
                    xlabel( "U [-]" );
                    ylabel( "Base spline coefficients [-]" );
                    
                    subplot( 2, 1, 2 ); hold off;
                    if( 0 )
                        for ind = 1 : nbCurvs
                            x = result.UStruct.uEval( :, ind );
                            y = result.VSplineEval( :,  ind );
                            semilogy( x, y, '-b' ); hold on; grid on;
                            x = result.UStruct.uDisc( :, ind );
                            y = result.VSplineDisc( :,  ind );
                            semilogy( x, y, 'k+' );
                            y = ones( size( x ) ) * result.FeedRate( ind );
                            semilogy( x, y, 'r-', 'LineWidth', 2 );
                        end                        
                    else
                        for ind = 1 : nbCurvs
                            x = result.UStruct.uEval( :, ind );
                            y = result.VSplineEval( :,  ind );
                            plot( x, y, '-b' ); hold on; grid on;
                            x = result.UStruct.uDisc( :, ind );
                            y = result.VSplineDisc( :,  ind );
                            plot( x, y, 'k+' );
                            y = ones( size( x ) ) * result.FeedRate( ind );
                            plot( x, y, 'r-', 'LineWidth', 2 );
                        end
                    end

                    vlines = xline( [ 0 : size( result.Coeff, 2 )-1 ], ...
                     '-', curveTypes );
                    yline( 0, '-k', 'LineWidth', 2 );
                    
                    set( vlines, 'LabelOrientation', 'horizontal' );
                    legend( [  "Spline Eval", "Spline Discretization", ...
                               "Feedrate", [] ] );
                    xlabel( "U [-]" );
                    ylabel( "Velocity norm in joint space [mm/s]" );
                    
                    if( obj.MODE_AUTO )
                        pause( 5e-2 );
                    else
                        messagePrompt();
                    end
                end
            end

            disp( "****************************************************" );
        end
        
        function [ obj ] = add_result( obj, ctx, Bl, BasisVal, curvArray, Coeff )
            obj.counter     = obj.counter + 1;
            nbCurvs         = length( curvArray );
            spline_eval     = zeros( obj.NB_SPLINE_POINTS   , nbCurvs);
            CoeffM          = reshape( Coeff, [], nbCurvs );
            spline_disc     = BasisVal * CoeffM;
            
            nbDisc          = size( spline_disc, 1 );
            nbCoeff         = size( CoeffM, 1 );

            uDisc           = linspace( 0, 1, nbDisc );
            uDisc           = uDisc( 1 : end );
            
            uCoeff          = linspace( 0, 1, nbCoeff );
            uCoeff          = uCoeff( 1 : end );

            uvec            = linspace( 0, 1, obj.NB_SPLINE_POINTS );
            uvec            = uvec( 1 : end );

            offsetCurv      = [ 0 : ( nbCurvs-1 ) ];
            uEvalM          = repmat( uvec', 1,  nbCurvs )  + offsetCurv;
            uDiscM          = repmat( uDisc', 1, nbCurvs )  + offsetCurv;
            uCoeffM         = repmat( uCoeff', 1, nbCurvs ) + offsetCurv;
            vspline_eval    = zeros( obj.NB_SPLINE_POINTS, nbCurvs );
            vspline_disc    = zeros( nbDisc, nbCurvs );
            feedrate        = zeros( 0, nbCurvs );

            U               = obj.constrUstruct( uCoeffM, uDiscM, uEvalM );
                       
            for j = 1 : nbCurvs
                feedrate( j ) = curvArray( j ).Info.FeedRate;

                [~, r1D]    = EvalCurvStructInPieceFrame( ctx, ...
                    curvArray( j ), uvec );

                spline_eval( : , j ) = bspline_eval_vec( Bl, ...
                    CoeffM( :, j )', uvec' )';

                vSpline5D   = r1D .* sqrt( spline_eval( : , j ) )';

                vspline_eval( :, j ) = vecnorm( ...
                    vSpline5D( ctx.cfg.indCart, :  ) )';

                [~, r1D]    = EvalCurvStructInPieceFrame( ctx, ...
                    curvArray( j ), uDiscM( :, 1 )' );

                vSpline5D = r1D .* sqrt( spline_disc( : , j ) )';

                vspline_disc( :, j ) = vecnorm( ...
                    vSpline5D( ctx.cfg.indCart, :  ) )';

            end
            
            result      = obj.constrResult( CoeffM, spline_disc, ...
                spline_eval, curvArray, U, vspline_disc, vspline_eval, ...
                feedrate );
            

            obj.results.push( result );
        end
    end

    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugOptimization;
            end
            singleObj = localObj;
        end
    end
end