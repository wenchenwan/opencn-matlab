function [ ret, ctx ] = loadCtx( filename )
ret = 1;

data = load( filename );

ctx = data.ctxMat;

% Create ctx object based on saved strcutures
ctx.q_compress  = load_queue( data.compressArray );
ctx.q_gcode     = load_queue( data.gcodeArray );
ctx.q_smooth    = load_queue( data.smoothArray );
ctx.q_split     = load_queue( data.splitArray );
ctx.q_opt       = load_queue( data.optArray );
ctx.q_spline    = load_q_spline( data.splineArray );
ctx.Bl          = bspline_create( ctx.Bl.order, ctx.Bl.breakpoints );
ctx.op          = Fopt( ctx.op );
ctx.errcode     = FeedoptPlanError( ctx.errcode );
ctx.kin         = Kinematics( ctx.cfg.kin_type, ctx.cfg.kin_params );

ret = 0;

end

%-------------------------------------------------------------------------
%   Functions
%-------------------------------------------------------------------------

function [ q_load ] = load_queue( curvArray )
N      = numel( curvArray );
q_load = queue( constrCurvStructType );

for j = 1 : N
    q_load.push( curvArray( j ) );
end

end


function [ q_spline ] = load_q_spline( splineArray )
NSpline     = numel( splineArray );
q_spline    = queue( constrCurvStructType );

for j = 1 : NSpline
    arr              = splineArray( j );
    spline            = constrCurvStructType;
    spline.Info.Type  = CurveType.Spline;
    Bl                = bspline_create( arr.sp.order, arr.sp.breakpoints );
    spline.sp         = constrSpline( arr.sp.coeff, arr.sp.knots, Bl );
    spline.sp.Lk      = arr.Lk;
    spline.sp.Ltot    = arr.Ltot;
    
    q_spline.push( spline );
end
end