function CurvStruct = ConstrHelixStruct(P0, P1, Cprim, delta, evec, theta, pitch, FeedRate, ZSpdMode)
%#codegen
CoeffP5     = zeros(3, 6);

CurvStruct  = ConstrCurvStruct(CurveType.Helix, ZSpdMode, P0, P1, Cprim, delta, evec, theta, pitch, CoeffP5, FeedRate);
coder.cstructname(CurvStruct, 'CurvStruct');
