function CurvStruct = ConstrTransP5Struct(trafo, HSC, HSC_cmd, Poff, ...
                                          Aoff, Uoff, Doff, avec, uvec,...
                                          CoeffP5, FeedRate)
Type        = CurveType.TransP5;

P0          = mypolyval(CoeffP5,0);
P1          = mypolyval(CoeffP5,1);
A0          = avec(:,1);
A1          = avec(:,end);
U0          = uvec(:,1);
U1          = uvec(:,end);

Cprim       = zeros(3, 1);
delta       = 0.0;
evec        = zeros(3, 1);
theta       = 0.0;
pitch       = 0.0;

CurvStruct  = ConstrCurvStruct(Type, ZSpdMode.NN, trafo, HSC, HSC_cmd, ...
                                   Poff, Aoff, Uoff, Doff, P0, P1, A0, ...
                                   A1, U0, U1, Cprim, delta, evec, theta,... 
                                   pitch, CoeffP5, FeedRate);
