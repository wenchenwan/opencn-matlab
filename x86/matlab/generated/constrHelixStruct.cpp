//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:10
//

// Include Files
#include "constrHelixStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// function [ CStrct ] = constrHelixStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                                          delta, evec, theta, pitch )
//
// constrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis ( x, y, z ) with a circular
//  motion in the perpendicular plan ( XY, ZX, YZ ).
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  Cprim     : Corrected center of the helix
//  rotation  : Number of rotation to realize (positive ; Clockwise |
//              negative ; Counterclockwise | zero ; pure translation)
//  evec      : Unit vector orthogonal to the planned of the projected circle
//  theta     : The rotation angle of the skrew motion
//  pitch     : Travelled distance along the skrew axis
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                       const ::coder::array<double, 1U> &R1, const double Cprim[3], double delta,
                       const double evec[3], double theta, double pitch, CurvStruct *CStrct)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrHelixStruct:20' coder.inline( "never" );
    // 'constrHelixStruct:22' gcodeInfoStruct.Type = CurveType.Helix;
    gcodeInfoStruct->Type = CurveType_Helix;
    // 'constrHelixStruct:24' CoeffP5 = zeros( 1, 6 );
    // 'constrHelixStruct:25' Coeff   = zeros( 1, 1 );
    // 'constrHelixStruct:27' CStrct = constrCurvStruct( gcodeInfoStruct, R0, R1, Cprim, delta,
    // evec, ... 'constrHelixStruct:28'                            theta, pitch, CoeffP5, Coeff );
    b_constrCurvStruct(*gcodeInfoStruct, R0, R1, Cprim, delta, evec, theta, pitch, CStrct);
}

} // namespace ocn

//
// File trailer for constrHelixStruct.cpp
//
// [EOF]
//
