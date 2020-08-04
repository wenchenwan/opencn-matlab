function BusElem = SimulinkBusCurvStruct()
%#codegen
CoeffP5     = zeros(3, 6);
evec        = zeros(3, 1);
theta       = 0;
pitch       = 0;

CurvStruct  = ConstrLineStruct([1,2,3]', [4,5,6]', 0.7, ZSpdMode.NN);
CurvStruct.Type = CurveType.None;
coder.cstructname(CurvStruct, 'CurvStruct');

BusElem = Simulink.Bus.createObject(CurvStruct);
BusElem.Name = 'CurvStruct';