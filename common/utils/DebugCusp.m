classdef ( Sealed ) DebugCusp < handle
    properties
        q_cusp;
    end

    methods (Access = private)
        function [ obj ] = DebugCusp
            curv = constrCurvStructType;
            obj.q_cusp = queue( [curv; curv] );
        end

        function [] = drawArrow3( obj, arrow )
            hold on;
            quiver3(arrow(1), arrow(2), arrow(3), arrow(4), ...
                arrow(5), arrow(6), 1, 'Color', ...
                [0, 0, 0]);
            hold off;
        end

        function [] = drawCharts( obj, fig, point, arrow, indCart, indRot ...
                )
            nbRot = length(indRot);

            ind = 2 * [ 1 : nbRot] - 1;

            figure( fig );

            subplot( nbRot,2, ind );
            hold on;
            plot3(  point(indCart(1), : ), point(indCart(2), : ), ...
                point(indCart(3), : ), '-b'); grid on;
            obj.drawArrow3( arrow );
            axis equal;

            for j = 1 : nbRot
                subplot( nbRot, 2, 2 * j );
                hold on;
                plot( point( indRot, : ), '-b'); grid on;
                axis equal;
            end

        end

        function [joint, piece, jointd, pieced] = evalCurv( obj, ctx, ...
                curv, u_vec)

            [joint, jointd] = EvalCurvStructNoCtx( ctx.cfg, ...
                curv, constrCurvStructType, u_vec );
            piece   = joint;
            pieced  = jointd;
            ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );

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
    end

    methods
 
        function [ obj ] = reset( obj )
            curv = constrCurvStructType;
            obj.q_cusp.delete;
            obj.q_cusp = queue( [curv; curv] );
        end

        function [ obj ] = print( obj, ctx )
            nbUPoints   = 20;
            nbCusp      = obj.q_cusp.size();
            u_vec       = linspace( 0, 1, nbUPoints );
            joint       = zeros( ctx.cfg.NumberAxis, 2 * nbUPoints );
            piece       = joint;
            jointd      = joint;
            pieced      = joint;

            ind1        = [ 1 : nbUPoints ];
            ind2        = [ 1 : nbUPoints ] + nbUPoints;

            for ind = 1 : nbCusp
                cuspArray   = obj.q_cusp.get(ind);
                curv1       = cuspArray( 1 );
                curv2       = cuspArray( 2 );

                [ joint( : , ind1 ), piece( : , ind1 ), jointd( : , ind1 ),...
                    pieced( : , ind1 ) ] = obj.evalCurv( ctx, curv1, u_vec);

                [ joint( : , ind2 ), piece( : , ind2 ), jointd( : , ind2 ),...
                    pieced( : , ind2 ) ] = obj.evalCurv( ctx, curv2, u_vec);

                fig = figure( 'Name', "Joint Space" );
                arrow = [ joint( ctx.cfg.indCart, ind1(end));
                    jointd( ctx.cfg.indCart, ind1(end)) ];
                obj.drawCharts( fig, joint(:, ind1), arrow, ...
                    ctx.cfg.indCart, ctx.cfg.indRot );

                arrow = [ joint( ctx.cfg.indCart, ind2(1));
                    jointd( ctx.cfg.indCart, ind2(1)) ];
                obj.drawCharts( fig, joint(:, ind2), arrow, ...
                    ctx.cfg.indCart, ctx.cfg.indRot );

                fig = figure( 'Name', "Piece Space" );

                arrow = [ piece( ctx.cfg.indCart, ind1(end));
                    pieced( ctx.cfg.indCart, ind1(end)) ];
                obj.drawCharts( fig, piece(:, ind1), arrow, ...
                    ctx.cfg.indCart, ctx.cfg.indRot );

                arrow = [ piece( ctx.cfg.indCart, ind2(1));
                    pieced( ctx.cfg.indCart, ind2(1)) ];
                obj.drawCharts( fig, piece(:, ind2), arrow, ...
                    ctx.cfg.indCart, ctx.cfg.indRot );

                messagePrompt();
            end

        end

        function [ obj ] = add( obj, curv1, curv2 )
            obj.q_cusp.push( [curv1; curv2] );
        end

    end

    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugCusp;
                localObj.reset();
            end
            singleObj = localObj;
        end
    end
end