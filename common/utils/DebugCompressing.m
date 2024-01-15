classdef ( Sealed ) DebugCompressing < handle
    % DebugCompressing : Singleton class type used to debug the compressing.
    %
    % Functionalities : 
    %   + Keep track of the following : 
    %         - counter on the number of not collinear line segements
    %         - counter on the number of too Large line segments
    %         - counter on the number of not a line curve type
    %         - counter on the number of is a zero start (ZN / ZZ)
    %         - counter on the number of is not the same machine Parameters
    %         - counter on the number of really small lines
    %   + Options 
    %         - flagDoPlot :
    %           Enable the plot of each compressing result 
    %
    properties
        NotCollinear;           
        TooLarge;         
        NotALine;
        IsAZeroStart;
        NotSameMachineParams;
        IsReallySmall;
        batchLength;
        batchZspdmode;
        listSplineBatch;
        flagDoPlot;
    end

    methods (Access = private)
        function [ obj ] = DebugCompressing
            obj.reset();
        end

        function [ joint, piece, kJoint, kPiece ] = evalCurv( ~, ctx, ...
                curv, u_vec)

            [joint, jointD, jointDD] = EvalCurvStruct( ctx, curv, u_vec );
            
            ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );

            if( ~curv.Info.TRAFO )
                [ piece]    = ctx.kin.r_relative( joint );
                [ pieceD ]  = ctx.kin.v_relative( joint, jointD );
                [ pieceDD ] = ctx.kin.a_relative( joint, jointD, jointDD );
            else
                piece = joint; pieceD = jointD; pieceDD = jointDD;
                [ joint ]   = ctx.kin.r_joint( piece );
                [ jointD ]  = ctx.kin.v_joint( piece, pieceD );
                [ jointDD ] = ctx.kin.a_joint( piece, pieceD, pieceDD );
            end
            [ ~, ~, kJoint ] = calc_t_nk_kappa( jointD, jointDD );
            [ ~, ~, kPiece ] = calc_t_nk_kappa( pieceD, pieceDD );

        end
    end

    methods
        function [ obj ] = reset( obj )
            obj.flagDoPlot              = false;
            obj.NotCollinear            = 0;
            obj.TooLarge                = 0;
            obj.NotALine                = 0;
            obj.IsAZeroStart            = 0;
            obj.NotSameMachineParams    = 0;
            obj.IsReallySmall           = 0;
            obj.batchLength             = [];
            obj.batchZspdmode           = [];

            if( ~isempty( obj.listSplineBatch ) )
                obj.listSplineBatch.delete();
            end

            bSpline             = constrBaseSplineType;
            obj.listSplineBatch = queue( obj.constrInterpSplineBatch( bSpline, [] ) );
        end

        function [ obj ] = print( obj )
            disp( "****************************************************" );
            disp( "Compressing Resulting tests : " );
            disp( "Nb Splines : "           + length( obj.batchLength ) );
            disp( "Nb curves compressed : " + sum( obj.batchLength ) );
            disp( "Not collinear : "        + obj.NotCollinear );
            disp( "Too large : "            + obj.TooLarge );
            disp( "Not alined : "           + obj.NotALine );
            disp( "Is a zero start : "      + obj.IsAZeroStart );
            disp( "Not Same Machine Parameters : "  ...
                + obj.NotSameMachineParams );
            disp( "Is a Really Small Line : "  + obj.IsReallySmall );
            disp( "****************************************************" );

            if( obj.flagDoPlot )
                figure('Name','Distrubution of the number of curves');
                histogram(gca, obj.batchLength);
                figure('Name','Distrubution of the different zero speeds');
                c = categorical(obj.batchZspdmode, [ZSpdMode.NN, ZSpdMode.ZN, ...
                    ZSpdMode.NZ, ZSpdMode.ZZ ] , {'NN', 'ZN', 'NZ', 'ZZ'});
                histogram(gca, c);
                messagePrompt();

            end

        end

        function [ interpStruc ] = constrInterpSplineBatch( ~, bSpline, ...
                batch )
            interpStruc = struct( "spline", bSpline, "batch", batch );
        end

        function [  ] = NotCollinearInc( obj )
            obj.NotCollinear = obj.NotCollinear + 1;
        end

        function [  ] = TooLargeInc( obj )
            obj.TooLarge = obj.TooLarge + 1;
        end

        function [  ] = NotALineInc( obj )
            obj.NotALine = obj.NotALine + 1;
        end

        function [ ] = IsAZeroStartInc( obj )
            obj.IsAZeroStart = obj.IsAZeroStart + 1;
        end

        function [ ] = NotSameMachineParamsInc( obj )
            obj.NotSameMachineParams = obj.NotSameMachineParams + 1;
        end

        function [] = IsReallySmallInc( obj )
            obj.IsReallySmall = obj.IsReallySmall + 1;
        end

        function [] = addBatch( obj, length, zspdmode )
            obj.batchLength( end +1 )   = length;
            obj.batchZspdmode( end + 1 )= zspdmode;
        end

        function [  ] = addSplineBatch( obj, spline, batch )
            interpSplineBatch = obj.constrInterpSplineBatch( spline, batch );
            obj.listSplineBatch.push( interpSplineBatch );
        end

        function [  ] = myPlot( ~, fig, sPointVec, pointVec, sLine, line, ...
                sSpline, spline, kappa, indCart, maskTot, figName )
            
            figure( fig );

            nbAxis = size( line, 1 );
            axisNamesTot    = [ "x", "y", "z", "a", "b", "c" ];
            axisNames       = axisNamesTot( maskTot );
            legendNames     = [ " : Spline", " : Line", " : Point" ];

            subplot( 5, 2, [ 1 7 ] );  % 3D Plot
            
            plot3( spline( indCart( 1 ), : ), spline( indCart( 2 ), : ), ...
                spline( indCart( 3 ), : ) ); hold on; grid on;
            plot3( line( indCart( 1 ), : ), line( indCart( 2 ), : ), ...
                line( indCart( 3 ), : ) );
            plot3( pointVec( indCart( 1 ), : ), pointVec( indCart( 2 ), : ), ...
                pointVec( indCart( 3 ), : ), 's','MarkerSize',10,...
                'MarkerEdgeColor', 'red', 'MarkerFaceColor', [1 .6 .6] );
            legend( legendNames );
            xlabel( "x [mm]" ); ylabel( "y [mm]" ); zlabel( "z [mm]" );
            axis square;

            for k = 1 : length( sPointVec )
                text( pointVec( 1, k ), pointVec( 2, k ), pointVec( 3, k ), ...
                    num2str( k ), 'HorizontalAlignment', 'center' );
            end

            title( figName );
            for j = 1 : nbAxis
                subplot( 5, 2, j * 2 ); % Axis Plot
                plot( sSpline, spline( j , : ) ); hold on; grid on;
                plot( sLine, line( j , : ) );
                plot( sPointVec, pointVec( j , : ), 's','MarkerSize',10,...
                            'MarkerEdgeColor','red',...
                            'MarkerFaceColor', [1 .6 .6] );
                
                for k = 1 : length( sPointVec )
                    text( sPointVec( k ), pointVec( j, k ), num2str( k ), ...
                        'HorizontalAlignment', 'center' );
                end
                
                legend( axisNames( j ) + legendNames  );
                ylabel( axisNames( j ) );
            end
            xlabel( "U vector" );

            subplot( 5, 2, 9 ); % Curvature   
            plot( sSpline, kappa ); grid on; hold on;

            indKappa = zeros( size( sPointVec ) );

            for j = 1 : length( sPointVec )
                indKappa( j ) = find( sSpline ==  sPointVec( j ), 1 );
            end
            
            plot( sPointVec, kappa( indKappa ), 's','MarkerSize',10,...
                            'MarkerEdgeColor','red',...
                            'MarkerFaceColor', [1 .6 .6] );

             for j = 1 : length( sPointVec )
                text( sPointVec( j ) , kappa( indKappa( j ) ), ...
                    num2str( j ), 'HorizontalAlignment', 'center' );
             end

            legend( [ "Curvature", "Point" ] );
            xlabel( "U vector" );
            ylabel( "Curvature" );

            fontsize( fig, 12, "points" );
        end

        function [  ] = printSplineBatch( obj, ctx, spline, batch )
            if( false || obj.flagDoPlot )

                bspline         = ctx.q_spline.get( spline.sp_index );
                breakpoints     = bspline.sp.Bl.breakpoints;
                nbPointU        = 10;
                nbBatch         = batch.size;

                infoStruct      = batch.lastCurv.Info;
                toolStruct      = batch.lastCurv.tool;

                uVec            = linspace( 0, 1, nbPointU + 1 );
                svec            = zeros( 1, nbPointU  * nbBatch + 1 );
                ASpline         = diff( breakpoints );
                BSpline         = breakpoints( 1 : end -1 );
                Uvec            = repmat( uVec, length(ASpline), 1 ) ...
                    .* ASpline' + BSpline';
                sPointVec       =  0 : nbBatch;
                pointJointVec   = zeros( ctx.cfg.NumberAxis, nbBatch + 1 );
                pointPieceVec   = pointJointVec;
                uVecSpline      = [ 0, reshape( Uvec( : , 2 : end )', 1, [] ) ];


                splineJoint     = zeros( ctx.cfg.NumberAxis, length( svec ) );
                linesJoint      = splineJoint;
                linesPiece      = splineJoint;

                splineJointKappa = svec;
                splinePieceKappa = svec;

                ind             = [ 1 : nbPointU + 1 ];



                for j = 1 : nbBatch
                    if( nbBatch == 1 )
                        infoStruct.zspmode = batch.zspdmode;
                    elseif( j == 1 &&  isAZeroStart( batch.zspdmode ) )
                        infoStruct.zspmode = ZSpdMode.ZN;
                    elseif( j == nbBatch &&  isAZeroEnd( batch.zspdmode ) )
                        infoStruct.zspmode = ZSpdMode.NZ;
                    else
                        infoStruct.zspmode = ZSpdMode.NN;
                    end

                    R0 = batch.pvec( :, j );
                    R1 = batch.pvec( :, j + 1 );
                    line = constrLineStruct( infoStruct, toolStruct, R0, R1 );

                    [ linesJoint( :, ind ), linesPiece( :, ind ) ]  = ...
                        obj.evalCurv( ctx, line, uVec );

                    pointJointVec( :, j ) = linesJoint( :, ind( 1 ) );
                    pointPieceVec( :, j ) = linesPiece( :, ind( 1 ) );

                    svec( ind )                 = svec( ind ) + uVec;
                    svec( ind( end )  : end )   = svec( ind( end ) );
                    ind = ind + nbPointU;
                end
                pointJointVec( :, end ) = linesJoint( :, end );
                pointPieceVec( :, end ) = linesPiece( :, end );

                [ splineJoint, splinePiece, splineJointKappa, ...
                    splinePieceKappa ] = obj.evalCurv( ctx, spline, uVecSpline );

                figName = "Joint Space";
                fig(1) = figure( 'Name', figName );
                obj.myPlot( fig(1), sPointVec, pointJointVec, svec, linesJoint, svec, ...
                    splineJoint, splineJointKappa, ctx.cfg.indCart, ...
                    ctx.cfg.maskTot, figName );

                figName = "Piece Space";
                fig(2) = figure( 'Name', figName );
                obj.myPlot( fig(2), sPointVec, pointPieceVec, svec, linesPiece, svec, ...
                    splinePiece, splinePieceKappa, ctx.cfg.indCart, ...
                    ctx.cfg.maskTot, figName );

                messagePrompt();
                close( fig );
            end
        end

    end

    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugCompressing;
            end
            singleObj = localObj;
        end
    end
end
