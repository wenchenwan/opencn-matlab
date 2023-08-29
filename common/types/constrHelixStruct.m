function [ CStrct ] = constrHelixStruct( gcodeInfoStruct, tool, R0, R1, ...
                                        Cprim, delta, evec, theta, pitch )
%#codegen
% constrHelixStructFromArcFeed : Construct a Curv struct filled with the
% parameters of a helix. The resulting helix is the combination of a linear 
% motion along one of the three reference axis ( x, y, z ) with a circular
% motion in the perpendicular plan ( XY, ZX, YZ ).
%
% gcodeInfoStruct : struct containing the information from the Gcode
% tool      : Struct containing the information of the tool
% R0        : Starting pose of the helix P0
% R1        : Ending pose of the helix P0
% Cprim     : Corrected center of the helix
% rotation  : Number of rotation to realize (positive ; Clockwise |
%             negative ; Counterclockwise | zero ; pure translation)
% evec      : Unit vector orthogonal to the planned of the projected circle 
% theta     : The rotation angle of the skrew motion
% pitch     : Travelled distance along the skrew axis
%
% CStrct    : The resulting CurvStruct
coder.inline( "never" );

gcodeInfoStruct.Type = CurveType.Helix;

spline  = constrSplineType();
CoeffP5 = zeros( 1, 6 );
Coeff   = zeros( 1, 1 );

CStrct = constrCurvStruct( gcodeInfoStruct, tool, spline, R0, R1, Cprim, ...
                            delta,evec, theta, pitch, CoeffP5, Coeff );
end