function CurvStruct = ConstrLineStruct(trafo, P0, P1, A0, A1, U0, U1, FeedRate, ZSpdMode)
%#codegen
CoeffP5     = zeros(3, 6);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;


CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, trafo, P0, P1, ...
                A0, A1, U0, U1, [0,0,0]', 0.0, evec, theta, pitch, ...
                CoeffP5, FeedRate);
coder.cstructname(CurvStruct, 'CurvStruct');
