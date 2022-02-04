function CurvStruct = ConstrLineStruct(P0, P1, FeedRate, ZSpdMode)
%#codegen
coder.inline("never");
CoeffP5     = zeros(3, 6);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;


CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, P0, P1, [0,0,0]', 0.0, evec, theta, pitch, CoeffP5, FeedRate);
coder.cstructname(CurvStruct, 'CurvStruct');
