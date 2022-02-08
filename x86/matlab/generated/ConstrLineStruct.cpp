//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "ConstrLineStruct.h"
#include "ConstrCurvStruct.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

// Function Definitions
//
// Arguments    : bool trafo
//                const double P0[3]
//                const double P1[3]
//                const double A0[3]
//                const double A1[3]
//                const double U0[3]
//                const double U1[3]
//                double FeedRate
//                ZSpdMode b_ZSpdMode
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrLineStruct(bool trafo, const double P0[3], const double P1[3], const double A0[3],
                      const double A1[3], const double U0[3], const double U1[3], double FeedRate,
                      ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct)
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
    ConstrCurvStruct(CurveType_Line, b_ZSpdMode, trafo, P0, P1, A0, A1, U0, U1, dv, 0.0, dv1, 0.0,
                     0.0, dv2, FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrLineStruct.cpp
//
// [EOF]
//
