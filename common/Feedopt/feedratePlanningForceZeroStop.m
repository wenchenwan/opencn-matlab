function [ ctx, window, NWindow ] = feedratePlanningForceZeroStop( ctx, window, NWindow )
% NN case :
% Optimization failed due to small coefficient, so force a stop

curvQueue       = ctx.q_split;
ctx.zero_forced = true;
ocn_assert( ctx.k0 > 1, "Should not be called one the first set of curves", ...
    mfilename );

curv0           = window( 1 );
curv1           = window( NWindow );
ind1            = ctx.k0 + NWindow;

msg = "Curve should be a Zero Stop";
ocn_assert( ~isAZeroStart( curv0 ), msg, mfilename );
ocn_assert( ~isAZeroEnd( curv1 ),   msg, mfilename );
curv1.Info.zspdmode = ZSpdMode.NZ;

[ ~, curv1NN, curv1NZ ]     = cutZeroEnd( ctx,  curv1 );
ctx.zero_forced_buffer( 1 ) = curv1NZ;
curvQueue.set( ind1, curv1NN );

ind2            = ind1 + 1;
if( ind2 <= curvQueue.size() )
    curv2       = ctx.q_split.get( ind2 );
    curv2.Info.zspdmode = ZSpdMode.ZN;
    [ ~, curv2ZN, curv2NN ]     = cutZeroStart( ctx, curv2 );
    ctx.zero_forced_buffer( 2 ) = curv2ZN;
    curvQueue.set( ind2, curv2NN );
else
    % Empty curve
    ctx.zero_forced_buffer( 2 ) = constrCurvStructType;
end

% Get window of interest in from a given queue
[ window, NWindow ] = feedratePlanningGetwindow( ctx.k0, NWindow, curvQueue );

window  = [ window, ctx.zero_forced_buffer( 1 ) ];
NWindow = NWindow + 1;

% Prepare the boundaries conditions of the problem
[ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
    ctx, window, NWindow );

ctx.q_split = curvQueue;
end