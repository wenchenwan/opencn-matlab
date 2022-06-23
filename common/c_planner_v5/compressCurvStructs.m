function [ ctx ] = compressCurvStructs_new( ctx )
% CompressCurvStructs :
% - Is feeded by the queue : q_gcode
% - Check if a compression is possible based on the individual curves
% length, the cummulative length and the collinearity of two consecutive
% segment.
% - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves
% accordingly.
% - Create a Bspline based on Lee89.
% - Fill the queue : q_compress
%
% Note : If compression is not required call ExpandZeroStructs

if ctx.q_gcode.isempty(), return; end

spline_index        = ctx.q_spline.size() + 1;  % New index in q_spline
Ncrv                = ctx.q_gcode.size;         % Number of curve in queue
[ batch ]           = batch_init();

DebugLog(DebugCfg.Validate, 'Compressing...\n');

for k = 1 : Ncrv
    curv = ctx.q_gcode.get( k ); % Get next Curve in the queue

    [ addBatch, addBatchNew ] = check_add_batch( ctx, curv, batch );
    [ closeBatch ] = check_close_batch( curv, addBatch );

    if( addBatch )
        if( batch.size > 0)
            [ batch ] = batch_add_curv( batch, curv );
        else
            [ batch ] = batch_reset( ctx, curv );
        end
    end

    if( closeBatch )
        [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index );
    end

    if( addBatchNew )
        [ batch ] = batch_reset( ctx, curv );
    elseif( ~addBatch )
        ctx.q_compress.push( curv );
    end


end

[ ctx ] = batch_close( ctx, batch, spline_index );

end

%-------------------------------------------------------------------------%

function [ addBatch, addBatchNew ] = check_add_batch( ctx, curv, batch )
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

addBatch    = true;
addBatchNew = false;

if( curv.Info.Type ~= CurveType.Line )
    addBatch = false;
    return;
end

if( LengthCurv( ctx, curv, 0, 1 ) >  ctx.cfg.LThreshold )
    addBatch = false; return;
end

if( batch.size > 0 )
    if( batch.size > 1 )
        prevCurv = batch.curvArray( end );
    else
        prevCurv = batch.curvArray( 1 );
    end
    collinear = curvCollinear( ctx, prevCurv, curv, ...
        ctx.cfg.Compressing.ColTolCosLee );
    if( ~collinear ), addBatch = false; addBatchNew = true; return; end
end

end

function [ closeBatch ] = check_close_batch( curv, addBatch )
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

closeBatch = false;

if( ~addBatch ), closeBatch = true; return; end

if( isAZeroEnd( curv ) ), closeBatch = true; return; end

end

function [ batch ] = batch_init()
batch = struct( ...
    'pvec',          zeros( StructTypeName.NumberAxisMax, 1 ),...
    'curvArray',     repmat( constrCurvStructType, 1, 2 ),...
    'spindle_speed', 0,...
    'feedrate',      0,...
    'size',          0 ...
    );

if( ~coder.target( "MATLAB" ) )
    coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
end
end

function [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index )
if( batch.size > 1 )
    [ curvCompressed, spline, spline_index ] = ...
        create_spline( ctx, batch, spline_index );

    ctx.q_compress.push( curvCompressed );
    ctx.q_spline.push( spline );

elseif( batch.size > 0 )
    ctx.q_compress.push( batch.curvArray( 1 ) );
end
batch.size = 0;
end

function [ batch ] = batch_reset( ctx, curv )
batch.pvec            = curv.R0;
batch.curvArray       = [ curv, curv ];
batch.spindle_speed   = ctx.cfg.smax;
batch.feedrate        = ctx.cfg.fmax;
batch.size            = 1;
end

function [ batch ] = batch_add_curv( batch, curv )
batch.pvec             = [ batch.pvec, curv.R1 ];
batch.curvArray( end ) = curv;
batch.spindle_speed    = min( batch.spindle_speed , curv.Info.SpindleSpeed );
batch.feedrate         = min( batch.feedrate, curv.Info.FeedRate );
batch.size             = batch.size + 1;
end

function [ curv, spline, spline_index ] = create_spline( ctx, batch, spline_index )
spline            = constrCurvStructType;
spline.Info.Type  = CurveType.Spline;
spline.sp_index   = spline_index;
spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec( ctx.cfg.maskTot, : ) );
[ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx, spline );
spline.sp.Ltot    = Ltot;
spline.sp.Lk      = Lk;

curv    = constrSplineStruct( batch.curvArray( end ).Info, batch.pvec( :, 1 ), ...
    batch.pvec( :,end ), uint32( spline_index ) );

% Calculate the ZSpdMode for the spline
first   = batch.curvArray( 1 );
last    = batch.curvArray( end );

if ( ~isAZeroSpeed( first ) ) && ( ~isAZeroSpeed( last ) )
    curv.Info.zspdmode = ZSpdMode.NN;
elseif ( ~isAZeroSpeed( first ) ) && ( isAZeroEnd( last ) )
    curv.Info.zspdmode = ZSpdMode.NZ;
elseif ( isAZeroStart( first ) ) && ( ~isAZeroSpeed( last ) )
    curv.Info.zspdmode = ZSpdMode.ZN;
else
    curv.Info.zspdmode = ZSpdMode.ZZ;
end

spline_index = spline_index + 1;
end