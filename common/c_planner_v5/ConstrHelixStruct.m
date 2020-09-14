function CurvStruct = ConstrHelixStruct(P0, P1, evec, theta, pitch, FeedRate, ZSpdMode)
%#codegen
CoeffP5     = zeros(3, 6);

CurvStruct  = ConstrCurvStruct(CurveType.Helix, ZSpdMode, P0, P1, evec, theta, pitch, CoeffP5, FeedRate);
CurvStruct.cottheta2 = cot(theta/2);
coder.cstructname(CurvStruct, 'CurvStruct');
