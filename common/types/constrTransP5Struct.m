function CStrct = constrTransP5Struct( gcodeInfoStruct, R0, R1, CoeffP5 )
%#codegen
% constrTransP5Struct : Construct a Curv struct filled with the
% parameters of a hermite polynom used for the transitions.
%
% gcodeInfoStruct : struct containing the information from the Gcode
% R0        : Starting pose of the helix P0
% R1        : Ending pose of the helix P0
% CoeffP5   : Coefficient of the 5th order polynom
%
% CStrct    : The resulting CurvStruct

coder.inline( "never" );

params = paramsDefaultCurv;

gcodeInfoStruct.Type = CurveType.TransP5;

if( coder.target( "MATLAB" ) )
    CStrct = constrCurvStruct( gcodeInfoStruct, params{ 2 },  R0, R1, ...
        params{ 5 : end -2 }, CoeffP5, params{ end } );
else
    CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1, ...
                           params.Cprim, ...
                           params.delta, params.evec, params.theta, ...
                           params.pitch, CoeffP5, params.Coeff );
end

end
