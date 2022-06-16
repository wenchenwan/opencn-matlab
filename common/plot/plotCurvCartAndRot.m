 function plotCurvCartAndRot( cfg, point, figureName, feedrate )
% plotCurvCartAndRot : Plot the cartesian and rotative part of the curve.
if( nargin < 4 ), feedrate = zeros( 1, size( point, 2 )); end

needSubPlot = ( cfg.NRot > 0 && cfg.NCart > 0 );

figure( 'Name', figureName );
if( cfg.NCart > 0 )
    if( needSubPlot ), subplot( 1, 2, 1 ); end
    dataCart = zeros( 3, size( point, 2 ) );
    dataCart( cfg.maskCart( 1 : 3 ), : ) = point( cfg.indCart, : );
    my_plot( dataCart, feedrate, { 'X [mm]', 'Y [mm]', 'Z [mm]' } );
end

if( cfg.NRot > 0 )
    if( needSubPlot ), subplot( 1, 2, 2 ); end
    dataRot = zeros( 3, size( point, 2 ) );
    indRot  = cfg.NCart + 1 : cfg.NumberAxis;
    dataRot( cfg.maskRot( end-2 : end ), : ) = point( indRot, : );
    my_plot( dataRot, feedrate, { 'A [Rad]', 'B [Rad]', 'C [Rad]' } );
end
end

function my_plot( data, feedrate, labels )
    plot3( data( 1, : ), data( 2, : ), data( 3, : ), '-' ); grid on; axis square;
%     scatter3( data( 1, : ), data( 2, : ), data( 3, : ), 1, feedrate, '.' );
    colormap jet
    set(gca, 'Projection','orthographic')
    xlabel( labels{ 1 } ); ylabel( labels{ 2 } ); zlabel( labels{ 3 } );
    colorbar
end