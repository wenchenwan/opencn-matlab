//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:52:48
//

// Include Files
#include "ConstrHelixStruct.h"
#include "ConstrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"

// Function Definitions
//
// function CurvStruct = ConstrHelixStruct(trafo, HSC, HSC_cmd, ...
//                       Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, U0, U1, ...
//                       Cprim, delta, evec, theta, pitch, FeedRate, mode)
//
// Arguments    : bool trafo
//                bool HSC
//                const char HSC_cmd[256]
//                const double Poff[3]
//                const double Aoff[3]
//                const double Uoff[3]
//                double Doff
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
//                ZSpdMode mode
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrHelixStruct(bool trafo, bool HSC, const char HSC_cmd[256], const double Poff[3],
                       const double Aoff[3], const double Uoff[3], double Doff, const double P0[3],
                       const double P1[3], const double A0[3], const double A1[3],
                       const double U0[3], const double U1[3], const double Cprim[3], double delta,
                       const double evec[3], double theta, double pitch, double FeedRate,
                       ZSpdMode mode, CurvStruct *b_CurvStruct)
{
    double dv[6][3];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrHelixStruct:5' CoeffP5     = zeros(3, 6);
    // 'ConstrHelixStruct:7' CurvStruct  = ConstrCurvStruct(CurveType.Helix, mode, trafo, HSC,
    // HSC_cmd, ... 'ConstrHelixStruct:8'                                 Poff, Aoff, Uoff, Doff,
    // P0, ... 'ConstrHelixStruct:9'                                 P1, A0, A1, U0, U1, Cprim,
    // delta, evec,... 'ConstrHelixStruct:10'                                 theta, pitch, CoeffP5,
    // FeedRate);
    for (int i{0}; i < 6; i++) {
        dv[i][0] = 0.0;
        dv[i][1] = 0.0;
        dv[i][2] = 0.0;
    }
    ConstrCurvStruct(CurveType_Helix, mode, trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, Doff, P0, P1, A0,
                     A1, U0, U1, Cprim, delta, evec, theta, pitch, dv, FeedRate, b_CurvStruct);
    // 'ConstrHelixStruct:12' coder.cstructname(CurvStruct, 'CurvStruct');
}

} // namespace ocn

//
// File trailer for ConstrHelixStruct.cpp
//
// [EOF]
//
