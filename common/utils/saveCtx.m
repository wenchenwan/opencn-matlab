function [ ret ] = saveCtx( ctx, fileName )
%saveQueue : Save the curves in a given queue
ret = 1;

[ gcodeArray ]      = copy_queue( ctx.q_gcode );
[ compressArray ]   = copy_queue( ctx.q_compress );
[ smoothArray ]     = copy_queue( ctx.q_smooth );
[ splitArray ]      = copy_queue( ctx.q_split );
[ optArray ]        = copy_queue( ctx.q_opt );

q_spline    = ctx.q_spline;
NSpline     = q_spline.size;
sp          = constr_sp( [], [], [], [] );
splineMat   = constr_spline( sp, 0.0, 0.0 );
splineArray = repmat( splineMat, NSpline, 1);

% Loop over spline array
for j = 1 : NSpline
    spline = q_spline.get(j).sp;
    sp = constr_sp( spline.knots, spline.coeff, spline.Bl.breakpoints, ...
                      spline.Bl.order );
    splineArray( j ) = constr_spline( sp, spline.Ltot, spline.Lk );
end

[ ctxMat ] = constr_ctx( ctx );

save( fileName, "ctxMat", "splineArray", "gcodeArray", "compressArray", ...
                "smoothArray", "splitArray", "optArray" );
% success
ret = 0;

end
%-------------------------------------------------------------------------
%   Functions
%-------------------------------------------------------------------------

function [ curvArray ] = copy_queue( queue )
% Loop over curve arrays
N         = queue.size;
curvArray = repmat( constrCurvStructType, N, 1);
for j = 1 : N
    curvArray( j ) = queue.get( j );
end

end

function [ sp ] = constr_sp( knots, coeff, breakpoints, order )
sp = struct( "knots", knots, ...
    "coeff", coeff, ...
    "breakpoints", breakpoints, ...
    "order", order ...
    );
end

function [ splineMat ] = constr_spline( sp, Ltot, Lk )
splineMat = struct( "sp", sp, ...
    "Ltot", Ltot, ...
    "Lk", Lk);
end

function [ ctxMat ] = constr_ctx( ctx )

fields = fieldnames( ctx );

for f = fields.'
    if( isenum( ctx.( f{:} ) ) )
        ctxMat.( f{:} ) = double( ctx.( f{:} ) );
    elseif( isobject( ctx.( f{:} ) ) )
        ctxMat.( f{:} ) = -1;
    else
        ctxMat.( f{:} ) = ctx.( f{:} );
    end
end

end