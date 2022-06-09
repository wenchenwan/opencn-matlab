function [ u ]  = splineLengthFindU( ctx, curv, L, u1, isEnd )
% Computes approximately the value of curve parameter u such that the arc 
% length starting from u1 equals L.
% This function takes usage of the precalculated arc lengths between knots.
% The last integration interval is approximated by the trapezoidal rule.
% u1 must satisfy 0 < u1 < 1.
% In the normal case, u must satisfy 0 < u < u1. If L is too large, u is 
% set to -1
% Warning : This function works only for B-spline of degree 3

% Get the sp structure
spline = ctx.q_spline.get( curv.sp_index );
sp     = spline.sp;

DEFAULT_TOL_NR  = 1e-6;         % Default tolerance for Newton Raphson
IND_KNOTS_MULT  = sp.Bl.order;  % Index used to remove multiple knots 
%                              (ONLY TRUE FOR CUBIC SPLINE)

% Eliminate multiplicities at the end points
Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk     = sp.Lk;
KMax   = length( Lk );

if( isEnd )
    u1 = 1 - u1;
end

%
C_ASSERT_MSG = 'u1 must be %s or equal than the first spline knot';
c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater') );
c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
%
k_vec = find( Knots < u1 );
if( isempty( k_vec ) )
    k = 1; 
else
    k = k_vec( end );
end

if( isEnd )
    L  = sum( Lk( k : end ) ) - L;
    if( L < 0 ), u = 1; return; end
else
    if( L > sum( Lk( k : end ) ) ), u = 1; return; end
end

%
% Length to next break point
Lcum = Lk( k ) - SplineLengthApprox_Interval1( ctx, curv, Knots( k ), u1 ); 
%
while ( Lcum < L ) && ( k < KMax )
    k = k + 1;
    Lcum = Lcum + Lk( k );  % Sum up precalculated length between knots
end

% undo last increment
k         = k - 1;
Lcum      = Lcum - Lk( k );
Lremain   = L - Lcum;
%

u1     = Knots( k+1 );
% Initial guess for Newton Raphson iteration
uk     = 0.5 * ( Knots( k ) + Knots( k + 1 ) );  
% Dummy value to ensure that while loop enters
uk_old = 2;                            

% Iterate until new value of uk is close to old value
while abs( uk - uk_old ) > DEFAULT_TOL_NR 
    % Evaluation of function which should become zero
    fk = SplineLengthApprox_Interval1( ctx, curv, uk, u1 ) - Lremain; 
    [ ~, r1D ]  = EvalBSpline( spline, uk );
    % Evaluation of the derivative of the function which should become zero
    Dfk    = -MyNorm(r1D);   
    %
    uk_old = uk;
    uk     = uk_old - fk / Dfk;  % Newton Raphson update
    if uk > u1
        uk = u1;               % Make sure not to run away
    end
end
%
u  = uk;
