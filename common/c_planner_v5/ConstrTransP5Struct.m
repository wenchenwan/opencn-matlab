function CurvStruct = ConstrTransP5Struct(trafo, avec, uvec, CoeffP5, FeedRate)
P0          = mypolyval(CoeffP5,0);
P1          = mypolyval(CoeffP5,1);
A0          = avec(:,1);
A1          = avec(:,end);
U0          = uvec(:,1);
U1          = uvec(:,end);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;
CurvStruct  = ConstrCurvStruct(CurveType.TransP5, ZSpdMode.NN, trafo, P0, ...
                                P1, A0, A1, U0, U1, [0,0,0]', 0.0, evec, ...
                                theta, pitch, CoeffP5, FeedRate);
