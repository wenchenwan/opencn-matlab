//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStruct.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "ConstrHelixStruct.h"
#include "ConstrCurvStruct.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"

// Function Definitions
//
// Arguments    : const double P0[3]
//                const double P1[3]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                double FeedRate
//                ZSpdMode b_ZSpdMode
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrHelixStruct(const double P0[3], const double P1[3], const double Cprim[3], double delta,
                       const double evec[3], double theta, double pitch, double FeedRate,
                       ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct)
{
    double dv[6][3];
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    for (int i{0}; i < 6; i++) {
        dv[i][0] = 0.0;
        dv[i][1] = 0.0;
        dv[i][2] = 0.0;
    }
    ConstrCurvStruct(CurveType_Helix, b_ZSpdMode, P0, P1, Cprim, delta, evec, theta, pitch, dv,
                     FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrHelixStruct.cpp
//
// [EOF]
//
