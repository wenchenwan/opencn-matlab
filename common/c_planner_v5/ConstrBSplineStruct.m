function CurvStruct = ConstrBSplineStruct(pvec, zspdmode, FeedRate)

P0          = pvec (:, 1);
P1          = pvec (:, end);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;

CoeffP5     = zeros(3, 6);

CurvStruct  = ConstrCurvStruct(CurveType.Spline, zspdmode, P0, P1, evec, theta, pitch, CoeffP5, FeedRate);
