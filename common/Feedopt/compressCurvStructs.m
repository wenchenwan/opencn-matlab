function [ ctx ] = compressCurvStructs( ctx )
% CompressCurvStructs :
% - Is feeded by the queue : q_gcode
% - Check if a compression is possible based on the individual curves
% length, the cummulative length and the collinearity of two consecutive
% segment.
% - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves
% accordingly.
% - Create a Bspline based on ( Lee Algorithm : Lee89 ).
% - Fill the queue : q_compress
%
% Note : If compression is not required call ExpandZeroStructs
%
% Inputs :
%   ctx     : The context of the computational chain
%
% Outputs :
%   ctx     : The context of the computatinal chain
%

if ctx.q_gcode.isempty(), return; end

spline_index        = ctx.q_spline.size() + 1;  % New index in q_spline
Ncrv                = ctx.q_gcode.size;         % Number of curve in queue
[ batch ]           = batch_init();

DebugLog( DebugCfg.Validate, 'Compressing...\n' );

ctx.k0 = int32( 1 );

for k = 1 : Ncrv

    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + Ncrv, mfilename );
    curv = ctx.q_gcode.get( k ); % Get next Curve in the queue

    [ addBatch ]    = check_add_batch( ctx, curv );
    [ closeBatch ]  = check_close_batch( ctx, batch, curv, addBatch);

    if( closeBatch )
        [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index );
    end

    if( addBatch )
        [ batch ] = batch_add_curv( batch, curv );
    else
        ctx.q_compress.push( curv );
    end
    ctx.k0 = ctx.k0 + 1;
end

[ ctx ] = batch_close( ctx, batch, spline_index );

end

%-------------------------------------------------------------------------%

function [ addBatch ] = check_add_batch( ctx, curv )
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

addBatch    = true;

% Cond 1. Keep only line segments
if( curv.Info.Type ~= CurveType.Line )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.NotALineInc;
    end
    addBatch = false; return;
end
% Cond 2. Remove to large segment
if( LengthCurv( ctx, curv, 0, 1 ) >  ctx.cfg.LThresholdMax )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.TooLargeInc;
    end
    addBatch = false; return;
end

end

function [ closeBatch ] = check_close_batch( ctx, batch, curv, addBatch )
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

closeBatch = false;

if( batch.size == 0 ), return; end

% Cond 1. Curv not in the batch
if( ~addBatch ) 
    closeBatch = true;
end

% Cond 2. Curv require a stop
if( isAZeroStart( curv ) )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.IsAZeroStartInc;
    end
    closeBatch = true;
end

% Cond 3. Machine parameters are not the same
if( ~isSameMachiningParameters( batch.lastCurv, curv ) )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.NotSameMachineParamsInc;
    end

    closeBatch = true;
end    

% Cond 4. If to small don't test the collinearity
if( LengthCurv( ctx, curv, 0, 1 ) <=  ctx.cfg.LThresholdMin )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.IsReallySmallInc;
    end
    return; 
end

% Cond 5. If not collinear lines, create a new batch
collinear = curvCollinear( ctx, batch.lastCurv, curv, ...
    ctx.cfg.Compressing.ColTolCosLee );
if( ~collinear )
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.NotCollinearInc;
    end
    closeBatch = true;
end

end

function [ batch ] = batch_init()
batch = struct( ...
    'pvec',          zeros( StructTypeName.NumberAxisMax, 1 ),...
    'lastCurv',      constrCurvStructType,...
    'size',          0, ...
    'zspdmode',      ZSpdMode.NN ...
    );

if( ~coder.target( "MATLAB" ) )
    coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
end
end

function [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index )

if( batch.size == 0 )
    batch = batch_init();
    return
end

if( batch.size > 1 )
    [ curvCompressed, spline, spline_index ] = ...
        create_spline( ctx, batch, spline_index );
    
    ctx.q_compress.push( curvCompressed );
    ctx.q_spline.push( spline );

%     [r, rd, rdd, rddd ] = EvalCurvStruct( ctx, curvCompressed, [0, 1]);
    
    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.addSplineBatch( curvCompressed, batch );
        DebugCompressing.getInstance.printSplineBatch( ctx, curvCompressed, batch );
    end

else
    ctx.q_compress.push( batch.lastCurv );
end

if( coder.target( "MATLAB" ) )
    DebugCompressing.getInstance.addBatch( batch.size, batch.zspdmode );
end

batch = batch_init();
end

function [ batch ] = batch_add_curv( batch, curv )

if( batch.size == 0 )
    batch.pvec      = [ curv.R0, curv.R1 ];
    batch.lastCurv  = curv;
    batch.size      = 1;
    batch.zspdmode  = curv.Info.zspdmode;
else
    batch.pvec      = [ batch.pvec, curv.R1 ];
    batch.lastCurv  = curv;
    batch.size      = batch.size + 1;
    if( isAZeroEnd( curv ) )
        if( isAZeroStart( batch.zspdmode ) )
            batch.zspdmode = ZSpdMode.ZZ;
        else
            batch.zspdmode = ZSpdMode.NZ;
        end
    end
end

end

function [ curv, spline, spline_index ] = create_spline( ctx, batch, spline_index )

batch.lastCurv.Info.zspdmode = batch.zspdmode;

curv    = constrSplineStruct( ...
                              batch.lastCurv.Info, ...
                              batch.lastCurv.tool, ...
                              batch.pvec( :, 1 ), ...
                              batch.pvec( :,end ), ...
                              uint32( spline_index ) );

spline            = curv;
spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec( ctx.cfg.maskTot, : ) );
[ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx.cfg, spline );
spline.sp.Ltot    = Ltot;
spline.sp.Lk      = Lk;
spline_index      = spline_index + 1;
end
