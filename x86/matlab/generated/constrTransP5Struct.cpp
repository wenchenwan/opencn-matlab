//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:10
//

// Include Files
#include "constrTransP5Struct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = constrTransP5Struct( gcodeInfoStruct, R0, R1, CoeffP5 )
//
// constrTransP5Struct : Construct a Curv struct filled with the
//  parameters of a hermite polynom used for the transitions.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                         const ::coder::array<double, 1U> &R1,
                         const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrTransP5Struct:13' coder.inline( "never" );
    // 'constrTransP5Struct:15' params = paramsDefaultCurv;
    // 'constrTransP5Struct:17' gcodeInfoStruct.Type = CurveType.TransP5;
    gcodeInfoStruct->Type = CurveType_TransP5;
    // 'constrTransP5Struct:19' if( coder.target( "MATLAB" ) )
    // 'constrTransP5Struct:22' else
    // 'constrTransP5Struct:23' CStrct = constrCurvStruct( gcodeInfoStruct, R0, R1, params.Cprim,
    // ... 'constrTransP5Struct:24'                            params.delta, params.evec,
    // params.theta, ... 'constrTransP5Struct:25'                            params.pitch, CoeffP5,
    // params.Coeff );
    b_constrCurvStruct(*gcodeInfoStruct, R0, R1, CoeffP5, CStrct);
}

} // namespace ocn

//
// File trailer for constrTransP5Struct.cpp
//
// [EOF]
//
