function [ u ]  = splineLengthFindU( cfg, spline, L, u1, isEnd )
% Computes approximately the value of curve parameter u such that the arc 
% length starting from u1 equals L.
% This function takes usage of the precalculated arc lengths between knots.
% The last integration interval is approximated by the trapezoidal rule.
% u1 must satisfy 0 < u1 < 1.
% In the normal case, u must satisfy 0 < u < u1. If L is too large, u is 
% set to -1
% Warning : This function works only for B-spline of degree 3

% Get the sp structure
sp     = spline.sp;

DEFAULT_TOL_NR  = 1e-12;         % Default tolerance for Newton Raphson
IND_KNOTS_MULT  = sp.Bl.order;  % Index used to remove multiple knots
% Eliminate multiplicities at the end points
Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk     = sp.Lk;
kMax   = numel( Lk );

if( isEnd )
    u1      = 1 - u1;
    Knots   = flip( 1 - Knots );
    Lk      = flip( Lk );
end

C_ASSERT_MSG = 'u1 must be %s or equal than the first spline knot';
c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater') );
c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );

kStartVec = find( Knots <= u1, 1, "last" );
kStart    = kStartVec( 1 );

if( Knots( kStart ) < u1 )
    LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u1, isEnd );
else
    LStart = 0;
end

LEnd = cumsum( Lk( kStart : kMax ) ) - LStart;

kEndVec = find( LEnd >= L, 1, "first" );
if( isempty( kEndVec ) ), u = 1;   return; end
kEnd    = kEndVec( 1 );
kEnd = kEnd + kStart;

uLeft       = u1;
uRight      = Knots( kEnd );
uRightOld   = uLeft;

while( abs( uRightOld - uRight ) > DEFAULT_TOL_NR )
    % Evaluation of function which should become zero
    fk  = splineLengthApprox_Interval( cfg, spline, uLeft, uRight, isEnd ) - L;
    [ ~, r1D ] = EvalBSpline( spline, uRight );
    Dfk = MyNorm( r1D );
    uRightOld = uRight;
    uRight    = uRight - fk / Dfk;
    if( uRight > Knots( kEnd ) ),    uRight = Knots( kEnd );    end
    if( uRight < Knots( kStart ) ), uRight = Knots( kStart );   end
end

u = uRight;

if( isEnd )
    u = 1 -u;
end

end
