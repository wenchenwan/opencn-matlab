function L = SplineLength(sp, u0, u1)
% computes numerically the arc length of a parametric spline / RHG
sp1D = fnder(sp, 1); % derivative
fh   = @(u) mysqrt(sum(spval(sp1D, u).^2)); % function handle to norm of parametric derivative
% for better numerical precision Waypoints are specified
WayPoints = sp1D.knots;
WayPoints = WayPoints(WayPoints > u0);
WayPoints = WayPoints(WayPoints < u1);
L     = integral(fh, u0, u1, 'Waypoints', WayPoints);
