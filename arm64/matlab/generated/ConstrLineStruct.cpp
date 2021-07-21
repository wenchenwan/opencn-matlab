//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "ConstrLineStruct.h"
#include "ConstrCurvStruct.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"

// Function Definitions
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
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
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
}

} // namespace ocn

//
// File trailer for ConstrLineStruct.cpp
//
// [EOF]
//
