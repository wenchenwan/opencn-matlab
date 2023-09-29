function [ u ]  = splineLengthFindU( cfg, spline, L, u0, isEnd )
% Computes approximately the value of curve parameter u such that the arc
% length starting from u1 equals L.
% This function takes usage of the precalculated arc lengths between knots.
% The last integration interval is approximated by the trapezoidal rule.
% u1 must satisfy 0 < u1 < 1.
% In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
% set to -1.
% The parameter isEnd is used to start inverse the problem, the length is
% estimated starting from u quals to 1 to 0. It's used to cut a specific
% length at the beginning of the curv.

ITER_MAX    = 1000;
DEFAULT_TOL = 1E-7;

% Get the sp structure
sp     = spline.sp;

IND_KNOTS_MULT  = sp.Bl.order;  % Index used to remove multiple knots
% Eliminate multiplicities at the end points
Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk     = sp.Lk;
kMax   = numel( Lk );

if( isEnd )
    u0      = 1 - u0;
    Knots   = flip( 1 - Knots );
    Lk      = flip( Lk );
end

C_ASSERT_MSG = 'u0 must be %s or equal than the first spline knot';
ocn_assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater'), mfilename );
ocn_assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller'), mfilename );

kStartVec = find( Knots <= u0, 1, "last" );
kStart    = kStartVec( 1 );

if( Knots( kStart ) < u0 )
    LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u0, isEnd );
else
    LStart = 0;
end

LEnd = cumsum( Lk( kStart : kMax) ) - LStart;

LkEndVec = find( LEnd >= L, 1, "first" );
if( isempty( LkEndVec ) ) 
    u = -1;   return; 
else
    LkEnd    = LkEndVec( 1 );
    if( LkEnd > 1 )
        LDiff = L - LEnd( LkEnd - 1 );
    else
        LDiff = L + LStart;
    end
end

kEnd = LkEnd + kStart;

uLeft       = Knots( kEnd -1 );
uRight      = Knots( kEnd );

[ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff, ITER_MAX, DEFAULT_TOL, isEnd );

ocn_assert(~(u < 0), "Fails to compute length", mfilename);

if( isEnd && u >= 0 )
    u = 1 -u;
end

end

%-------------------------------------------------------------------------%
% Functions
%-------------------------------------------------------------------------%

function [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff, iterMax, tol, isEnd )
count   = 0;
uStart  = uLeft;
fk      = tol * 1.1;

uMiddle = ( uLeft + uRight ) / 2;

while( count < iterMax && abs( fk ) > tol )
    uMiddle = ( uLeft + uRight ) / 2;

    fk  = splineLengthApprox_Interval( cfg, spline, uStart, uMiddle, isEnd ) - LDiff;

    if( fk > 0 )
        uRight = uMiddle;
    else
        uLeft  = uMiddle;
    end
    count = count + 1;
end

if( count >= iterMax )
    u = -1; 
else
    u = uMiddle;
end

end