function CurvStruct = ConstrTransP5Struct(CoeffP5, FeedRate)
P0          = mypolyval(CoeffP5,0);
P1          = mypolyval(CoeffP5,1);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;
CurvStruct  = ConstrCurvStruct(CurveType.TransP5, ZSpdMode.NN, P0, P1, [0,0,0]', evec, theta, pitch, CoeffP5, FeedRate);
