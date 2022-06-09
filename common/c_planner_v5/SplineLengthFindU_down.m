function u  = SplineLengthFindU_down(ctx, curv, L, u1)
% computes approximately the value of curve parameter u such that the arc 
% length starting from u1 equals L.
% This function takes usage of the precalculated arc lengths between knots.
% The last integration interval is approximated by the trapezoidal rule.
% u1 must satisfy 0 < u1 < 1.
% In the normal case, u must satisfy 0 < u < u1. If L is too large, u is 
% set to -1
% Warning : This function works only for B-spline of degree 3

DEFAULT_TOL_NR  = 1e-6;      % Default tolerance for Newton Raphson
IND_KNOTS_MULT  = 4;         % Index used to remove multiple knots 
%                              (ONLY TRUE FOR CUBIC SPLINE)

% Get the sp structure
spline = ctx.q_spline.get( curv.sp_index );
sp     = spline.sp;

% Eliminate multiplicities at the end points
Knots  = sp.knots( IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
Lk     = sp.Lk;
%
C_ASSERT_MSG = 'u1 must be %s or equal than the first spline knot';
c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater') );
c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
%
k = length(Knots);
%
while u1 < Knots(k)
    k = k - 1;
end
%
% Length to next break point
Lcum = SplineLengthApprox_Interval1(ctx, curv, Knots(k), u1); 
%
k = k - 1;
while Lcum < L
    if k < 1
        u = -1;
        return;
    end    
    Lcum = Lcum + Lk(k);  % Sum up precalculated length between knots
    k = k - 1;
end
% undo last increment
k         = k + 1;
Lcum      = Lcum - Lk(k);
Lremain   = L - Lcum;
%

u1     = Knots(k+1);
% Initial guess for Newton Raphson iteration
uk     = 0.5*(Knots(k) + Knots(k+1));  
% Dummy value to ensure that while loop enters
uk_old = 2;                            

% Iterate until new value of uk is close to old value
while abs(uk - uk_old) > DEFAULT_TOL_NR 
    % Evaluation of function which should become zero
    fk = SplineLengthApprox_Interval1(ctx, curv, uk, u1) - Lremain; 
    [~, r1D]  = EvalBSpline(spline, uk);
    % Evaluation of the derivative of the function which should become zero
    Dfk       = -MyNorm(r1D);   
    %
    uk_old = uk;
    uk     = uk_old - fk/Dfk;  % Newton Raphson update
    if uk > u1
        uk = u1;               % Make sure not to run away
    end
end
%
u  = uk;
