//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "ConstrHelixStruct.h"
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
void ConstrHelixStruct(bool trafo, const double P0[3], const double P1[3], const double A0[3],
                       const double A1[3], const double U0[3], const double U1[3],
                       const double Cprim[3], double delta, const double evec[3], double theta,
                       double pitch, double FeedRate, ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct)
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
    ConstrCurvStruct(CurveType_Helix, b_ZSpdMode, trafo, P0, P1, A0, A1, U0, U1, Cprim, delta, evec,
                     theta, pitch, dv, FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrHelixStruct.cpp
//
// [EOF]
//
