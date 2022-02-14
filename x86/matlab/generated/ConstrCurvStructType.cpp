//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

// Include Files
#include "ConstrCurvStructType.h"
#include "ConstrLineStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"

// Function Definitions
//
// function C = ConstrCurvStructType
//
// Arguments    : CurvStruct *C
// Return Type  : void
//
namespace ocn {
void ConstrCurvStructType(CurvStruct *C)
{
    double dv[3];
    double dv1[3];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrCurvStructType:2' C = ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, C);
}

} // namespace ocn

//
// File trailer for ConstrCurvStructType.cpp
//
// [EOF]
//
