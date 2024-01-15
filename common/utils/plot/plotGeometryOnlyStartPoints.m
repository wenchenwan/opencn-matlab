function [ fig ] = plotGeometryOnlyStartPoints( ctx, q_curv, q_spline, ...
                                                curvName, fig )
% plotGeometryOnlyStartPoints : Plot the geometry of the provided queue,
% only the start points.
% 
% Inputs : 
% ctx       : Context of the test
% q_curv    : Queue of the desired curves to plot
% q_spline  : Queue of the splines
% curvName  : Name of the curves
% fig       : Figure pointer, if provided the curves are just happended to
%             the plot.
%
% Outputs :
% fig       : Pointer on the resulting figure 
%

if( ~(nargin > 4) ) 
    fig = figure(); 
    holdOn = false;
    legendOptions   = { curvName, 'Location', 'best' };
else
    holdOn = true;
    hLegend = findobj(gcf, 'Type', 'Legend');
    legendOptions   = { hLegend(1).String{ : }, curvName, 'Location', 'best' };
end

cfg             = ctx.cfg;
axisNameGen     = {"x", "y", "z", "a", "b", "c"};
axisUnitGen     = {"mm", "mm", "mm", "rad", "rad", "rad"};
axisName        = axisNameGen(1, ctx.cfg.maskTot);
axisUnit        = axisUnitGen(1, ctx.cfg.maskTot);

[ param ]           = load_param();
[ joint, piece, u ] = eval_points( ctx, cfg, q_curv, q_spline, param );

ind3D       = [ 1 9 ];
ind2D       = [ 2 4 ];

if( 0 )
figure( fig );
% 3D plots
subplot( 10, 2, ind3D );

if( holdOn ), hold on; end
ax = plot3( joint( 1, : ), joint( 2, : ), joint( 3, : ), 'k+', 'MarkerSize', 8);
colormap jet;
set(gca, 'Projection','orthographic');
% axis vis3d
% equal
xlabel('x mm');
ylabel('y mm');
zlabel('z mm');
title( "Joint Space" );

legend( legendOptions{ : } );

subplot( 10, 2, 10 + ind3D );
end

if( holdOn ), hold on; end
ax = plot3( piece( 1, : ), piece( 2, : ), piece( 3, : ), 'k+', 'MarkerSize', 8);
colormap jet;
set(gca, 'Projection','orthographic');
% axis vis3d
% equal
xlabel('x mm');
ylabel('y mm');
zlabel('z mm');
title( "Piece Space" );
legend( legendOptions{ : } );

if( 0 )

for j = 1 : 5
    subplot(10, 2, (j - 1) * 4 + ind2D);
    if( holdOn ), hold on; end
    plot( u, joint( j, :  ), 'k+', 'MarkerSize', 8 ); grid on;
    ylabel( axisName{ j } + " " + axisUnitGen{ j } );
    legend( legendOptions{ : } );
end

end

end


function [ param ] = load_param()
    param.Nu    = 1;
end

function [ joint, piece, u ] = eval_points( ctx, cfg, q_curv, q_spline, param )
NCurv   = double( q_curv.size );
NPoints = NCurv * param.Nu;
NDim    = cfg.NumberAxis + 1;

joint   = zeros( NDim, NPoints );
piece   = joint;
u_vec   = 0;
u       = 0 : NCurv - 1;

splineDefault = constrCurvStructType;

for j = 1 : NCurv
    curv    = q_curv.get( j );

    if( curv.Info.Type == CurveType.Spline )
        ptr    = curv.sp_index;
        spline = q_spline.get( ptr );
    else
        spline = splineDefault;
    end

    ind     = [ 1 : param.Nu ] + ( j - 1 ) * param.Nu;
    joint( 1 : end -1, ind ) = EvalCurvStructNoCtx( cfg, curv, spline, u_vec );
    joint( end, ind ) = j;

    ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
        if( ~curv.Info.TRAFO )
            [ piece(  1 : end -1, ind ) ] = ctx.kin.r_relative( joint(  1 : end -1, ind ) );
        else
            piece(  1 : end -1, ind ) = joint(  1 : end -1, ind );
            [ joint(  1 : end -1, ind ) ] = ctx.kin.r_joint( point(  1 : end -1, ind ) );
        end

end
end