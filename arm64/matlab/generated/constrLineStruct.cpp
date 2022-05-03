//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:06
//

// Include Files
#include "constrLineStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = constrLineStruct( gcodeInfoStruct, R0, R1 )
//
// constrLineStruct : Construct a Curv struct filled with the
//  parameters of a Line.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                      const ::coder::array<double, 1U> &R1, CurvStruct *CStrct)
{
    double dv[3];
    double dv1[3];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrLineStruct:11' coder.inline("never");
    // 'constrLineStruct:13' params = paramsDefaultCurv();
    // 'constrLineStruct:15' gcodeInfoStruct.Type = CurveType.Line;
    gcodeInfoStruct->Type = CurveType_Line;
    // 'constrLineStruct:17' if( coder.target( "MATLAB" ) )
    // 'constrLineStruct:19' else
    // 'constrLineStruct:20' CStrct = constrCurvStruct( gcodeInfoStruct, R0, R1, params.Cprim, ...
    // 'constrLineStruct:21'                            params.delta, params.evec, params.theta, ...
    // 'constrLineStruct:22'                            params.pitch, params.CoeffP5, params.Coeff
    // );
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    b_constrCurvStruct(*gcodeInfoStruct, R0, R1, dv, 0.0, dv1, 0.0, 0.0, CStrct);
}

} // namespace ocn

//
// File trailer for constrLineStruct.cpp
//
// [EOF]
//
