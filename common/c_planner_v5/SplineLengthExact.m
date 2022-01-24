function L = SplineLengthExact(ctx, Curv, u0, u1, AbsTol, RelTol)
% numerically computes the arc length of a parametric spline
% uses Matlab build-in function based on adaptive quadrature with error
% bounds.
% This function is ONLY for debugging purposes, not intended for code generation !
%
switch nargin   % define standard default parameters
    case 4
        AbsTol = 1e-10;
        RelTol = 1e-6;
    case 5
        RelTol = 1e-6;
    otherwise
end
%            
% get the sp structure
Spline = ctx.q_splines.get(Curv.sp_index);
sp     = Spline.sp;
Knots  = sp.knots(4:end-3);  % eliminate multiplicities at the end points
% for better numerical precision Waypoints are specified
WayPoints = Knots;
WayPoints = WayPoints(WayPoints > u0);
WayPoints = WayPoints(WayPoints < u1);
L     = integral(@(u) Integrand(ctx, Curv, u), u0, u1, ...
                'Waypoints', WayPoints, 'AbsTol', AbsTol, 'RelTol', RelTol);
end

function I = Integrand(ctx, Curv, u)
Spline    = ctx.q_splines.get(Curv.sp_index);
[~, r1D]  = EvalBSplineNoCtx(Spline, u);
I         = MyNorm(r1D);
end
