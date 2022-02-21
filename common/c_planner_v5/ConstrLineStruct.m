function CurvStruct = ConstrLineStruct(trafo, Poff, Aoff, ...
                                       Uoff, Doff, P0, P1, A0, A1, U0, U1,...
                                       FeedRate, ZSpdMode)
%#codegen
CoeffP5     = zeros(3, 6);
evec        = zeros(3, 1);
Cprim       = zeros(3, 1);
delta       = 0.0;
theta       = 0;
pitch       = 0;


CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, trafo, Poff, ...
                                Aoff, Uoff, Doff, P0, P1, A0, A1, U0, U1, ...
                                Cprim, delta, evec, theta, pitch, ...
                                CoeffP5, FeedRate);

coder.cstructname(CurvStruct, 'CurvStruct');
