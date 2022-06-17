function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
% zeroSpeedCurv : Compute the profile paramater u in case of zero start /
% stop. This approach assumes a constant pseudo jerk. The resulting profile
% will respect the velocity, acceleration and jerk constraints.
% Inputs  :
%   ctx     : The context
%   curv    : The Curve Struct
%   isEnd   : ( Boolean ) is the end of a curve
% Outputs :
%   u       : Resulting U for constant jerk
%   jps     : Resulting Pseudo jerk

uk = 1;

if( isEnd ), uk = 1 - uk ;  end

[ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );

if( curv.Info.TRAFO )
    r1D = ctx.kin.v_joint( r0D, r1D );
end

% Compute pseudo jerk based on max allowed jerk
jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
    
% searchU   = true;

%while searchU
searchJps = true;

ind = 0;
while searchJps
    ind = ind + 1;
    [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
    [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
end

if( coder.target( "MATLAB" ) ), disp( ind ); end

[ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
[ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );

end

function [ k_vec ] = compute_k( jps, dt, uk )
% compute_k : Compute the vector of time steps required by the paramter u to
% go from 0 to 1.
k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;

if( k > 0 )
    k_vec = 0 : k;
    if( k_vec( end ) < k ), k_vec = [ k_vec, k ]; end
else
    k_vec = 1;
end

end

function [ searchJps, jps, u, ud, udd ] = calc_u( isEnd, searchJps, jps, ctx, ...
    curv, k_vec  )
% calc_u : Calcule u for a given pseudo jerk. U is assured to give velocity,
% acceleration and jerk below the provided limits.
% Inputs :
%   isEnd : ( Boolean ) is the end of the curve.
%   searchJps : ( Boolean ) is searching a Jps
%   jps   : The constant pseudo jerk
%   ctx   : The context
%   curv  : The curve
%   k_vec : The vector of index
% Outputs :
%   searchU : ( Boolean ) is searching a U
%   jps : The constant pseudo jerk
%   u : The resulting u
persistent ratio
if( isempty( ratio ) ), ratio = 0.9; end

[ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );

[ ~, ~, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );

[ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );

if( curv.Info.TRAFO )
    [ r1D_a ] = ctx.kin.v_joint( r0D, r1D );
    r1D_r     = r1D;
else
    [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
    r1D_a     = r1D;
end

safetyFactor = 0.5;
fmax =  curv.Info.FeedRate * safetyFactor;
vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;

feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
V     = r1D_a .* ud;

if( any( feed > fmax ) )
    [ f_delta, ind ] = max( feed - fmax );
    jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
elseif( any( abs( V ) > vmax, 'all' ) )
    [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) ) );
elseif( any( abs( A ) > amax, 'all' ) )
    [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) ) ) );
elseif( any( abs( J ) > jmax, 'all' ) )
    [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
    jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind ) ) ) );
else
    searchJps = false;
end
end