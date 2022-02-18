function BusElem = SimulinkBusCurvStruct()
%#codegen
CoeffP5     = zeros(3, 6);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;

trafo = false; % TRAFO flag disable 
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

CurvStruct = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
                               Doff, [1,2,3]', [4,5,6]', A0, A1, U0, ...
                               U1, 0.7, ZSpdMode.NN);

CurvStruct.Type = CurveType.None;
coder.cstructname(CurvStruct, 'CurvStruct');

BusElem = Simulink.Bus.createObject(CurvStruct);
BusElem.Name = 'CurvStruct';