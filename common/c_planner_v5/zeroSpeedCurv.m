function [ u, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
% zeroSpeedCurv : Compute the profile paramater u in case of zero start / 
% stop. This approach assume a constant pseudo jerk. The resulting profile
% will respect the velocity, acceleration and jerk constraints.
% Inputs  :
%   ctx     : The context
%   curv    : The Curve Struct
%   isEnd   : ( Boolean ) is the end of a curve 
% Outputs :
%   u       : Resulting U for constant jerk
%   jps     : Resulting Pseudo jerk

uk = 0; if( isEnd ), uk = 1; end

[ ~, r1D ] = EvalCurvStruct( ctx, curv, uk );

% Compute pseudo jerk based on max allowed jerk
jps = min( ctx.cfg.jmax ) / max( abs( r1D ) );

searchU = true; u = 0;

while searchU
 [ searchU, jps, u ] = calcU( isEnd, searchU, jps, ctx, curv );
end

end

function [ searchU, jps, u ] = calcU( isEnd, searchU, jps, ctx, curv )
% calcU : Calcule u for a given pseudo jerk. U is assured to give velocity,
% acceleration and jerk below the provided limits.
% Inputs : 
%   isEnd : ( Boolean ) is the end of the curve.
%   searchU : ( Boolean ) is searching a U
%   jps : The constant pseudo jerk
%   ctx : The context
%   curv : The curve
% Outputs : 
%   searchU : ( Boolean ) is searching a U
%   jps : The constant pseudo jerk
%   u : The resulting u
persistent ratio
if( isempty( ratio ) ), ratio = 0.9; end


[ u, ud, udd, uddd ]  = constJerkU( jps, ctx.cfg.dt, isEnd, curv.a_param, ...
                                                            curv.b_param );

[ ~, V, A, J ] = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );

if( norm( V ) > curv.FeedRate )
    jps = jps * ratio * ( curv.FeedRate / norm( V ) ) ^ ( 1 / 2 );
elseif( max( abs( A ) ) > max( ctx.cfg.amax ) )
    jps = jps * ratio * ( max( abs( A ) ) / max( abs( ctx.cfg.amax ) ) ) ^ ( 1 / 4 );
elseif( max( abs( J ) ) > max( ctx.cfg.jmax ) )
    jps = jps * ratio * ( max( abs( J ) ) / max( abs( ctx.cfg.jmax ) ) ) ^ ( 1 / 6 );
else
    searchU = false;
end

end