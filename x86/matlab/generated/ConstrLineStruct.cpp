//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

// Include Files
#include "ConstrLineStruct.h"
#include "ConstrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"

// Function Definitions
//
// function CurvStruct = ConstrLineStruct(P0, P1, FeedRate, ZSpdMode)
//
// Arguments    : const double P0[3]
//                const double P1[3]
//                double FeedRate
//                ZSpdMode b_ZSpdMode
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrLineStruct(const double P0[3], const double P1[3], double FeedRate, ZSpdMode b_ZSpdMode,
                      CurvStruct *b_CurvStruct)
{
    double dv2[6][3];
    double dv[3];
    double dv1[3];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrLineStruct:3' coder.inline("never");
    // 'ConstrLineStruct:4' CoeffP5     = zeros(3, 6);
    // 'ConstrLineStruct:5' evec        = zeros(3, 1);
    // 'ConstrLineStruct:6' theta       = 0;
    // 'ConstrLineStruct:7' pitch       = 0;
    // 'ConstrLineStruct:10' CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, P0, P1,
    // [0,0,0]', 0.0, evec, theta, pitch, CoeffP5, FeedRate);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    for (int i{0}; i < 6; i++) {
        dv2[i][0] = 0.0;
        dv2[i][1] = 0.0;
        dv2[i][2] = 0.0;
    }
    ConstrCurvStruct(CurveType_Line, b_ZSpdMode, P0, P1, dv, 0.0, dv1, 0.0, 0.0, dv2, FeedRate,
                     b_CurvStruct);
    // 'ConstrLineStruct:11' coder.cstructname(CurvStruct, 'CurvStruct');
}

} // namespace ocn

//
// File trailer for ConstrLineStruct.cpp
//
// [EOF]
//
