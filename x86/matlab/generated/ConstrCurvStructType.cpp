//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:51:03
//

// Include Files
#include "ConstrCurvStructType.h"
#include "ConstrLineStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"

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
    // 'ConstrCurvStructType:2' trafo       = false;
    // 'ConstrCurvStructType:3' HSC         = false;
    // 'ConstrCurvStructType:4' HSC_cmd = char(zeros(1,256));
    // 'ConstrCurvStructType:5' Poff        = zeros(3,1);
    // 'ConstrCurvStructType:6' Aoff        = zeros(3,1);
    // 'ConstrCurvStructType:7' Uoff        = zeros(3,1);
    // 'ConstrCurvStructType:8' Doff        = 0.0;
    // 'ConstrCurvStructType:9' P0          = zeros(3,1);
    // 'ConstrCurvStructType:10' P1          = zeros(3,1);
    // 'ConstrCurvStructType:11' A0          = zeros(3,1);
    // 'ConstrCurvStructType:12' A1          = zeros(3,1);
    // 'ConstrCurvStructType:13' U0          = zeros(3,1);
    // 'ConstrCurvStructType:14' U1          = zeros(3,1);
    // 'ConstrCurvStructType:15' FeedRate    = 0.2;
    // 'ConstrCurvStructType:17' C = ConstrLineStruct(trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, Doff,
    // P0, P1, A0, A1, ... 'ConstrCurvStructType:18'                             U0, U1, FeedRate,
    // ZSpdMode.NN);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    b_ConstrLineStruct(dv, dv1, 0.2, C);
}

} // namespace ocn

//
// File trailer for ConstrCurvStructType.cpp
//
// [EOF]
//
