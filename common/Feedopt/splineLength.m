function [ L ] = splineLength( cfg, spline, u1, u2 )
% splineLength : Compute the spline length between u1 and u2.
%
% Inputs : 
% cfg       : The configuration structure 
% spline    : The spline
% u1        : The starting u
% u2        : The endind u
%
% Outputs :
% L         : The resulting length of the spline
%
sp = spline.sp;
IND_KNOTS_MULT  = sp.Bl.order;  % Index used to remove multiple knots
% Eliminate multiplicities at the end points
Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk     = sp.Lk;

ocn_assert( u2 > u1,          'u2 must be greater than u1', mfilename);
ocn_assert( u1 >= Knots(1),   'u1 must be greater or equal than the first spline knot', mfilename);
ocn_assert( u2 <= Knots(end), 'u2 must be smaller or equal than the last spline knot', mfilename);

kStartVec  = find( Knots <= u1, 1, "last" );
kEndVec    = find( Knots >= u2, 1, "first" );
kStart     = kStartVec( 1 );
kEnd       = kEndVec( 1 );

if( Knots( kStart ) < u1 )
    LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u1, false );
else
    LStart = 0;
end


if( Knots( kEnd ) > u2 )
    LEnd = splineLengthApprox_Interval( cfg, spline, u2, Knots( kEnd ), false );
else
    LEnd = 0;
end

L = sum( Lk( kStart : ( kEnd -1 ) ) ) - LStart - LEnd;
end
