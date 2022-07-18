function CStrct = constrSplineStruct( gcodeInfoStruct, R0, R1, sp_index )
%#codegen
% constrSplineStruct : Construct a Curv struct filled with the
% parameters of a Spline.
%
% gcodeInfoStruct : struct containing the information from the Gcode
% R0        : Starting pose of the spline P0
% R1        : Ending pose of the spline P0
% sp_index  : Index of the refrence spline
%
% CStrct    : The resulting CurvStruct
coder.inline("never");

params = paramsDefaultCurv();
% params{11} = sp_index;
gcodeInfoStruct.Type = CurveType.Spline;
% gcodeInfoStruct.sp_index = sp_index;

if( coder.target( "MATLAB" ) )
    CStrct = constrCurvStruct( gcodeInfoStruct, params{ 2 }, R0, R1, ...
                               params{ 5 : end } );
    CStrct.sp_index = sp_index;
else
    CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1, ...
                           params.Cprim, ...
                           params.delta, params.evec, params.theta, ...
                           params.pitch, params.CoeffP5, params.Coeff );
    CStrct.sp_index = uint32( sp_index );
end