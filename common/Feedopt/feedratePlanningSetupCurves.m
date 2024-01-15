function [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
    ctx, window, NWindow ) 
%#codegen
%feedratePlanningSetupCurves : Setup the windows of curves used in the
% optimization problem.
%
% Inputs / Outputs : 
%
%   ctx     :   The context structure
%   window  :   The window of curves
%   NWindow :   The number of curves in the window
%

% Get first and last curves
first = window( 1 );
last  = window( NWindow );

% Handle the zero speed at start
if ( isAZeroStart( first ) )
    ctx.zero_start  = true;
    window          = window( 2 : end );
    NWindow         = NWindow -1;
else
    ctx.zero_start  = false;
end

% Handle the zero speed at end
if( isAZeroEnd( last ) )
    ctx.zero_end    = true;
    NWindow         = NWindow -1;
    window          = window( 1 : end-1 );
else
    ctx.zero_end    = false;
end

% Compute the boundary conditions (v_norm + at_norm)
if( ctx.zero_start )
    [ v_0, at_0 ]   = calcZeroConstraints( ctx, first, false );
    ctx.v_0         = v_0;
    ctx.at_0        = at_0;
end

if( ctx.zero_end )
    [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true );
    ctx.v_1         = -v_1;
    ctx.at_1        = -at_1;
else
    ctx.v_1         = -ctx.cfg.v_1;
    ctx.at_1        = -ctx.cfg.at_1;
end


end
