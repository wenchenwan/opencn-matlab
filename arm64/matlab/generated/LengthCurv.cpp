//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "LengthCurv.h"
#include "EvalCurvStruct.h"
#include "SplineLengthApprox.h"
#include "TransP5LengthApprox.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                CurveType Curv_Type
//                const double Curv_P0[3]
//                const double Curv_P1[3]
//                const double Curv_CorrectedHelixCenter[3]
//                const double Curv_evec[3]
//                double Curv_theta
//                double Curv_pitch
//                const double Curv_CoeffP5[6][3]
//                int Curv_sp_index
//                double Curv_a_param
//                double Curv_b_param
// Return Type  : double
//
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                  CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3],
                  const double Curv_CorrectedHelixCenter[3], const double Curv_evec[3],
                  double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
                  int Curv_sp_index, double Curv_a_param, double Curv_b_param)
{
    static const char b_message[29]{'B', 'A', 'D', ' ', 'C', 'U', 'R', 'V', 'E', ' ',
                                    'T', 'Y', 'P', 'E', ' ', 'I', 'N', ' ', 'L', 'E',
                                    'N', 'G', 'T', 'H', ' ', 'C', 'U', 'R', 'V'};
    double a__1[3];
    double a__2[3];
    double a__3[3];
    double r1D[3];
    double L;
    char message[29];
    if ((Curv_Type == CurveType_Helix) || (Curv_Type == CurveType_Line)) {
        b_EvalCurvStruct(Curv_Type, Curv_P0, Curv_P1, Curv_CorrectedHelixCenter, Curv_evec,
                         Curv_theta, Curv_pitch, Curv_a_param, Curv_b_param, a__1, r1D, a__2, a__3);
        L = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
        sqrt_calls++;
    } else if (Curv_Type == CurveType_Spline) {
        L = SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, Curv_sp_index,
                               Curv_b_param, Curv_a_param + Curv_b_param);
    } else if (Curv_Type == CurveType_TransP5) {
        L = TransP5LengthApprox(Curv_CoeffP5);
    } else {
        for (int i{0}; i < 29; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
        L = 0.0;
    }
    return L;
}

} // namespace ocn

//
// File trailer for LengthCurv.cpp
//
// [EOF]
//
