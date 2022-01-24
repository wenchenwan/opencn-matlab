function u  = SplineLengthFindU_down(ctx, Curv, L, u1)
% computes approximately the value of curve parameter u such that the arc 
% length starting from u1 equals L.
% This function takes usage of the precalculated arc lengths between knots.
% The last integration interval is approximated by the trapezoidal rule.
% u1 must satisfy 0 < u1 < 1.
% In the normal case, u must satisfy 0 < u < u1. If L is too large, u is set to -1

%
% get the sp structure
Spline = ctx.q_splines.get(Curv.sp_index);
sp     = Spline.sp;
Knots  = sp.knots(4:end-3);  % eliminate multiplicities at the end points
Lk     = sp.Lk;
%
c_assert(u1 >= Knots(1),   'u1 must be greater or equal than the first spline knot');
c_assert(u1 <= Knots(end), 'u1 must be smaller or equal than the last spline knot');
%
k = length(Knots);
%
while u1 < Knots(k)
    k = k - 1;
end
%
Lcum = SplineLengthApprox_Interval1(ctx, Curv, Knots(k), u1); % length to next break point
%
k = k - 1;
while Lcum < L
    if k < 1
        u = -1;
        return;
    end    
    Lcum = Lcum + Lk(k);  % sum up precalculated length between knots
    k = k - 1;
end
% undo last increment
k         = k + 1;
Lcum      = Lcum - Lk(k);
Lremain   = L - Lcum;
%

u1     = Knots(k+1);
uk     = 0.5*(Knots(k) + Knots(k+1));  % initial guess for Newton Raphson iteration
tol    = 1e-6;                         % tolerance for Newton Raphson
uk_old = 2;                            % dummy value to ensure that while loop enters

while abs(uk - uk_old) > tol  % Iterate until new value of uk is close to old value
    fk = SplineLengthApprox_Interval1(ctx, Curv, uk, u1) - Lremain; % evaluation of function which should become zero
    [~, r1D]  = EvalBSplineNoCtx(Spline, uk);
    Dfk       = -MyNorm(r1D);   % evaluation of the derivative of the function which should become zero
    %
    uk_old = uk;
    uk     = uk_old - fk/Dfk;  % Newton Raphson update
    if uk > u1
        uk = u1;               % make sure not to run away
    end
end
%
u  = uk;
