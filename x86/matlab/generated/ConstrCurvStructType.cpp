//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "ConstrCurvStructType.h"
#include "ConstrLineStruct.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

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
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv2[0] = 0.0;
    dv3[0] = 0.0;
    dv4[0] = 0.0;
    dv5[0] = 0.0;
    dv6[0] = 0.0;
    dv7[0] = 0.0;
    dv8[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv2[1] = 0.0;
    dv3[1] = 0.0;
    dv4[1] = 0.0;
    dv5[1] = 0.0;
    dv6[1] = 0.0;
    dv7[1] = 0.0;
    dv8[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    dv2[2] = 0.0;
    dv3[2] = 0.0;
    dv4[2] = 0.0;
    dv5[2] = 0.0;
    dv6[2] = 0.0;
    dv7[2] = 0.0;
    dv8[2] = 0.0;
    ConstrLineStruct(false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2, ZSpdMode_NN, C);
}

} // namespace ocn

//
// File trailer for ConstrCurvStructType.cpp
//
// [EOF]
//
