//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStructType.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "ConstrCurvStructType.h"
#include "ConstrLineStruct.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"

// Function Definitions
//
// Arguments    : CurvStruct *C
// Return Type  : void
//
namespace ocn {
void ConstrCurvStructType(CurvStruct *C)
{
    double dv[3];
    double dv1[3];
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
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
