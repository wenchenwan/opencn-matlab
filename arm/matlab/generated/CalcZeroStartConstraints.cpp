//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcZeroStartConstraints.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CalcZeroStartConstraints.h"
#include "EvalCurvStruct.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types2.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType Curv_Type
//                const double Curv_P0[3]
//                const double Curv_P1[3]
//                const double Curv_CorrectedHelixCenter[3]
//                const double Curv_evec[3]
//                double Curv_theta
//                double Curv_pitch
//                const double Curv_CoeffP5[6][3]
//                int Curv_sp_index
//                bool Curv_UseConstJerk
//                double Curv_ConstJerk
//                double Curv_a_param
//                double Curv_b_param
//                double JerkScale
//                double *v_0
//                double *at_0
// Return Type  : void
//
namespace ocn {
void CalcZeroStartConstraints(const queue_coder *ctx_q_splines, CurveType Curv_Type,
                              const double Curv_P0[3], const double Curv_P1[3],
                              const double Curv_CorrectedHelixCenter[3], const double Curv_evec[3],
                              double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
                              int Curv_sp_index, bool Curv_UseConstJerk, double Curv_ConstJerk,
                              double Curv_a_param, double Curv_b_param, double JerkScale,
                              double *v_0, double *at_0)
{
    double a__1[3];
    double r1D[3];
    double r2D[3];
    double absxk;
    double b;
    double b_b;
    double b_t;
    double d1uk;
    double jps;
    double n;
    double scale;
    double t;
    e_c_assert(Curv_UseConstJerk);
    jps = Curv_ConstJerk * JerkScale;
    t = std::pow(6.0 / jps, 0.33333333333333331);
    d1uk = jps * std::pow(t, 2.0) / 2.0;
    b = jps * t;
    b_EvalCurvStruct(ctx_q_splines, Curv_Type, Curv_P0, Curv_P1, Curv_CorrectedHelixCenter,
                     Curv_evec, Curv_theta, Curv_pitch, Curv_CoeffP5, Curv_sp_index, Curv_a_param,
                     Curv_b_param, a__1, r1D, r2D);
    b_b = std::pow(d1uk, 2.0);
    *v_0 = std::sqrt((std::pow(r1D[0] * d1uk, 2.0) + std::pow(r1D[1] * d1uk, 2.0)) +
                     std::pow(r1D[2] * d1uk, 2.0));
    sqrt_calls++;
    n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
    sqrt_calls++;
    scale = 3.3121686421112381E-170;
    absxk = std::abs((r2D[0] * b_b + r1D[0] * b) * (r1D[0] / n));
    if (absxk > 3.3121686421112381E-170) {
        *at_0 = 1.0;
        scale = absxk;
    } else {
        b_t = absxk / 3.3121686421112381E-170;
        *at_0 = b_t * b_t;
    }
    absxk = std::abs((r2D[1] * b_b + r1D[1] * b) * (r1D[1] / n));
    if (absxk > scale) {
        b_t = scale / absxk;
        *at_0 = *at_0 * b_t * b_t + 1.0;
        scale = absxk;
    } else {
        b_t = absxk / scale;
        *at_0 += b_t * b_t;
    }
    absxk = std::abs((r2D[2] * b_b + r1D[2] * b) * (r1D[2] / n));
    if (absxk > scale) {
        b_t = scale / absxk;
        *at_0 = *at_0 * b_t * b_t + 1.0;
        scale = absxk;
    } else {
        b_t = absxk / scale;
        *at_0 += b_t * b_t;
    }
    *at_0 = scale * std::sqrt(*at_0);
}

} // namespace ocn

//
// File trailer for CalcZeroStartConstraints.cpp
//
// [EOF]
//
