function CurvStruct = ConstrBSplineStruct(trafo, HSC, Poff, ...
                                          Aoff, Uoff, Doff, pvec, avec,...
                                          uvec, zspdmode, FeedRate)

P0          = pvec (:, 1);
P1          = pvec (:, end);
A0          = avec (:, 1);
A1          = avec (:, end);
U0          = uvec (:, 1);
U1          = uvec (:, end);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;

c_assert(size(pvec,2) > 2, 'Not enough points');

CoeffP5     = zeros(3, 6);

CurvStruct  = ConstrCurvStruct(CurveType.Spline, zspdmode, trafo, HSC,...
                                Poff, Aoff, Uoff, Doff, P0, P1, ...
                                A0, A1, U0, U1, [0,0,0]', 0.0, evec, ...
                                theta, pitch, CoeffP5, FeedRate);
