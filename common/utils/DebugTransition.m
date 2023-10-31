classdef ( Sealed ) DebugTransition < handle
    properties
        q_transition;
        q_transition_fail;
        nbIsAZeroCurv;
        nbTransitionOK;
        nbTransitionFail;
        nbNoNeedForTransition;
        summary;
        coupleVsRet;
        flagDoPlot;
    end

    methods (Access = private)
        function [ obj ] = DebugTransition
            obj.reset();
        end

        function [joint, piece, jointd, pieced] = evalCurv( obj, ctx, ...
                curv, u_vec)

            [joint, jointd] = EvalCurvStructNoCtx( ctx.cfg, ...
                curv, constrCurvStructType, u_vec );
            piece   = joint;
            pieced  = jointd;
            ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );

            if( ~curv.Info.TRAFO )
                [ piece]    = ctx.kin.r_relative( joint );
                pieced      = ctx.kin.v_relative( joint, jointd );
            else
                [ joint ]   = ctx.kin.r_joint( piece );
                jointd      = ctx.kin.v_joint( piece, pieced );
            end

            pieced = pieced ./ vecnorm(pieced, 2, 1 );
            jointd = jointd ./ vecnorm(jointd, 2, 1 );
        end

        function [] = drawChartsAxis( obj, fig, time, point, color, ...
                indTot, legendCurvs )
            if nargin < 7
                legendCurvs = {};
            end

            axisNameTot = { "X", "Y", "Z", "A", "B", "C" };

            axisName    = axisNameTot( indTot );

            nbAxis = size( point, 1 );

            figure( fig );

            for ind =  1 : nbAxis
                subplot( nbAxis, 1, ind );
                hold on;
                plot( time, point( ind, : ), 'Color', color); grid on;

                ylabel( "" + axisName{ ind } + " axe" );
                if( ~isempty( legendCurvs ) )
                    legend( legendCurvs );
                end
            end
        end

        function [] = drawChartsCart( obj, fig, jointCart, pieceCart, ...
                color, legendCurvs )
            if nargin < 6
                legendCurvs = {};
            end

            figure( fig );

            subplot( 1, 2, 1 );
            hold on;
            plot3( jointCart( 1, : ), jointCart( 2, : ), jointCart( 3, : ), ...
                'Color', color);
            grid on;
            axis equal;
            if( ~isempty( legendCurvs ) )
                legend( legendCurvs );
            end
            xlabel("x [mm]");
            ylabel("y [mm]");
            zlabel("z [mm]");
            title( "X-Y-Z in joint space" );

            subplot( 1, 2, 2 );
            hold on;
            plot3( pieceCart( 1, : ), pieceCart( 2, : ), pieceCart( 3, : ), ...
                'Color', color);
            grid on;
            axis equal;
            if( ~isempty( legendCurvs ) )
                legend( legendCurvs );
            end
            xlabel("x [mm]");
            ylabel("y [mm]");
            zlabel("z [mm]");
            title( "X-Y-Z in piece space" );

        end
    end

    methods
        function [ obj ] = incZeroCurv( obj )
            obj.nbIsAZeroCurv = obj.nbIsAZeroCurv + 1;
        end

        function [ obj ] = incNoNeedForTransition( obj )
            obj.nbNoNeedForTransition = obj.nbNoNeedForTransition + 1;
        end

        function [ list ] = getCurveCoupleList( obj )
            list =  ...
                [ "LineHelix", "HelixLine", "LineSpline", "SplineLine", ...
                "SplineHelix", "HelixSpline", "LineLine", "HelixHelix", ...
                "SplineSpline" ];
        end

        function [ obj ] = reset( obj )
            curv = constrCurvStructType;
            obj.q_transition        = queue( [curv; curv; curv] );
            curveCoupleType         = "LineHelix";
            transitionRet           = 0.0;
            obj.q_transition_fail   = queue( {[curv; curv], ...
                curveCoupleType,  transitionRet });
            obj.nbIsAZeroCurv       = 0;
            obj.nbTransitionOK      = 0;
            obj.nbTransitionFail    = 0;
            obj.nbNoNeedForTransition = 0;
            defaultStat     = struct( "Fail", 0, "Success", 0 );
            listPossibleCurveCouple = obj.getCurveCoupleList();
            obj.summary = struct();
            for l = listPossibleCurveCouple
                obj.summary.(l) = defaultStat;
            end
            obj.coupleVsRet = zeros(length( listPossibleCurveCouple ), 9);

            obj.flagDoPlot = false;
        end

        function [ obj ] = print( obj, ctx )
            nbUPoints    = 20;
            u_vec       = linspace( 0, 1, nbUPoints );
            nbTransition = obj.q_transition.size();
            joint        = zeros( ctx.cfg.NumberAxis, 3 * nbUPoints );
            piece        = joint;
            jointd       = joint;
            pieced       = joint;

            ind1         = [ 1 : nbUPoints ];
            indT         = ind1 + nbUPoints;
            ind2         = indT + nbUPoints;
            myBlue       = [0; 0; 1];
            myRed        = [1; 0; 0];
            curvLegends  = { "Curv1", "Curv2", "CurvT" };

            disp( "****************************************************" );
            disp( "Transition Resulting tests : " );

            total = obj.nbTransitionFail + obj.nbIsAZeroCurv + ...
                obj.nbNoNeedForTransition + obj.nbTransitionOK;
            disp( "No Need for Transition : "   + obj.nbNoNeedForTransition );
            disp( "Is a Zero Curve : "          + obj.nbIsAZeroCurv );
            disp( "Is a Transition OK : "       + obj.nbTransitionOK );
            disp( "Is a Transition Fail : "     + obj.nbTransitionFail );
            disp( "Nb Total Curves : "          + total );

            listPossibleCurveCouple = obj.getCurveCoupleList();
            for l  =listPossibleCurveCouple
                obj.writeSummary( l );
            end

            disp( obj.coupleVsRet );

            if( nbTransition == 0 )
                disp( "No transition to plot..." );
                messagePrompt();
            end

            if( obj.flagDoPlot )
                for ind = 1 : nbTransition

                    disp( "Transition : " + ind + "/" + nbTransition );

                    cuspArray   = obj.q_transition.get( ind );

                    curv1       = cuspArray( 1 );
                    curvT       = cuspArray( 2 );
                    curv2       = cuspArray( 3 );

                    [ joint( : , ind1 ), piece( : , ind1 ), jointd( : , ind1 ),...
                        pieced( : , ind1 ) ] = obj.evalCurv( ctx, curv1, u_vec);

                    [ joint( : , ind2 ), piece( : , ind2 ), jointd( : , ind2 ),...
                        pieced( : , ind2 ) ] = obj.evalCurv( ctx, curv2, u_vec);

                    [ joint( : , indT ), piece( : , indT ), jointd( : , indT ),...
                        pieced( : , indT ) ] = obj.evalCurv( ctx, curvT, u_vec);


                    fig1 = figure( 'Name', "X-Y-Z positions in both Joint and Piece space" );


                    obj.drawChartsCart( fig1, joint( 1 : 3, ind1 ), ...
                        piece( 1 : 3, ind1 ), myBlue );

                    obj.drawChartsCart( fig1, joint( 1 : 3, ind2 ), ...
                        piece( 1 : 3, ind2 ), myBlue );

                    obj.drawChartsCart( fig1, joint( 1 : 3, indT ), ...
                        piece( 1 : 3, indT ), myRed, curvLegends );


                    fig2 = figure( 'Name', "Axis plot in joint space" );

                    obj.drawChartsAxis( fig2, ind1, joint( : , ind1), myBlue, ...
                        ctx.cfg.maskTot );

                    obj.drawChartsAxis( fig2, ind2-2, joint( : , ind2), myBlue, ...
                        ctx.cfg.maskTot );

                    obj.drawChartsAxis( fig2, indT-1, joint( : , indT ), myRed, ...
                        ctx.cfg.maskTot, curvLegends );


                    fig3 = figure( 'Name', "Axis plot in piece space" );

                    obj.drawChartsAxis( fig3, ind1, piece( : , ind1 ), myBlue, ...
                        ctx.cfg.maskTot );

                    obj.drawChartsAxis( fig3, ind2-2, piece( : , ind2 ), myBlue, ...
                        ctx.cfg.maskTot );

                    obj.drawChartsAxis( fig3, indT-1, piece( : , indT ), myRed, ...
                        ctx.cfg.maskTot, curvLegends );


                    messagePrompt();
                    close( [fig1, fig2, fig3] );
                end
            end

            disp( "****************************************************" );

        end

        function writeSummary( obj, str )
            total = obj.summary.(str).Fail + obj.summary.(str).Success;
            msg1 = ": Fail - "      + obj.summary.(str).Fail;
            msg2 = ": Success - "   + obj.summary.(str).Success;
            msg3 = ": Total - "     + total;

            fprintf( 1, "%s\t%s\t%s\t%s\n", str, msg1, msg2, msg3 );
        end

        function [ curveCoupleType ] = getCurvCoupleTypes( obj, curv1, curv2 )
            persistent curveTypeList;

            if( isempty( curveTypeList ) )
                curveTypeList   = { "Line", "Helix", "Spline" };
            end

            curveCoupleType     =  curveTypeList{ curv1.Info.Type } + ...
                curveTypeList{ curv2.Info.Type };
        end

        function [ ind ] = getCurvCoupleTypesInd( obj, curv1, curv2 )
            persistent curveTypeList;

            if( isempty( curveTypeList ) )
                curveTypeList   = obj.getCurveCoupleList;
            end

            curveCoupleType     =  obj.getCurvCoupleTypes( curv1, curv2 );

            ind = find( curveCoupleType == curveTypeList );
        end

        function [ obj ] = addTransition( obj, curv1C, curvT, curv2C )
            curveCoupleType         = obj.getCurvCoupleTypes( curv1C, curv2C );
            obj.q_transition.push( [curv1C; curvT; curv2C] );
            obj.nbTransitionOK  = obj.nbTransitionOK + 1;
            obj.summary.(curveCoupleType).Success = ...
                obj.summary.(curveCoupleType).Success + 1;
        end

        function [ obj ] = addTransitionFail( obj, curv1, curv2, ret )
            curveCoupleType         = obj.getCurvCoupleTypes( curv1, curv2 );
            obj.q_transition_fail.push( { [curv1; curv2], curveCoupleType, ret } );
            ind = obj.getCurvCoupleTypesInd( curv1, curv2 );
            obj.coupleVsRet( ind, ret ) = obj.coupleVsRet( ind, ret ) + 1;
            obj.nbTransitionFail        = obj.nbTransitionFail + 1;
            obj.summary.(curveCoupleType).Fail = ...
                obj.summary.(curveCoupleType).Fail + 1;
        end
    end

    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugTransition;
                localObj.reset();
            end
            singleObj = localObj;
        end
    end
end