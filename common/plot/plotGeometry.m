function plotGeometry( ctx, cfg, q_curv, q_spline )
% plotGeometry : Plot the geometric path of a given queue.
% cfg       : The configuration structure
% q_curv    : The queue that contains the curves
% q_spline  : The queue that contains the spline
[ param ] = load_param();
[ point ] = eval_points( ctx, cfg, q_curv, q_spline, param );
plotCurvCartAndRot( cfg, point, 'Geometry curve' );

end


function [ param ] = load_param()
    param.Nu    = 1000;
end

function [ point ] = eval_points( ctx, cfg, q_curv, q_spline, param )
NCurv   = double( q_curv.size );
NPoints = NCurv * param.Nu;
NDim    = cfg.NumberAxis;

point   = zeros( NDim, NPoints );
u_vec  = linspace( 0, 1, param.Nu );

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
    point( :, ind ) = EvalCurvStructNoCtx( cfg, curv, spline, u_vec );

    if( curv.Info.TRAFO )
        [ point( :, ind ) ] = ctx.kin.r_joint( point( :, ind ) );
    end

end
end