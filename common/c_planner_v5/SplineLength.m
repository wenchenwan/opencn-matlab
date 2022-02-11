function L = SplineLength(sp, u0, u1)
% Computes numerically the arc length of a parametric spline
sp1D = fnder(sp, 1); % Derivative
% Function handle to norm of parametric derivative
fh   = @(u) mysqrt(sum(spval(sp1D, u).^2)); 
% For better numerical precision Waypoints are specified
WayPoints = sp1D.knots;
WayPoints = WayPoints(WayPoints > u0);
WayPoints = WayPoints(WayPoints < u1);
L     = integral(fh, u0, u1, 'Waypoints', WayPoints);
