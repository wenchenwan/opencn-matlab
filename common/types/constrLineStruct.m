function CStrct = constrLineStruct( gcodeInfoStruct, tool, R0, R1 )
%#codegen
% constrLineStruct : Construct a Curv struct filled with the
% parameters of a Line.
%
% gcodeInfoStruct : struct containing the information from the Gcode
% tool      : Struct containing the information of the tool
% R0        : Starting pose of the line P0
% R1        : Ending pose of the line P0
%
% CStrct    : The resulting CurvStruct
coder.inline("never");

params = paramsDefaultCurv();

gcodeInfoStruct.Type = CurveType.Line;

if( coder.target( "MATLAB" ) )
    CStrct = constrCurvStruct( gcodeInfoStruct, tool, params{ 3 }, R0, ...
                               R1, params{ 6 : end } );
else
    CStrct = constrCurvStruct( gcodeInfoStruct, tool, params.spline, R0, ...
                           R1, params.Cprim,params.delta, params.evec, ...
                           params.theta, params.pitch, params.CoeffP5, ...
                           params.Coeff );
end