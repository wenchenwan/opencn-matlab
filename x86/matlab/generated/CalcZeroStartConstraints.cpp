//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcZeroStartConstraints.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:46:02
//

// Include Files
#include "CalcZeroStartConstraints.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// function [v_0, at_0] = CalcZeroStartConstraints(ctx, Curv, JerkScale)
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
    static const char b_message[50]{'C', 'a', 'l', 'c', 'Z', 'e', 'r', 'o', 'S', 't', 'a', 'r', 't',
                                    'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', ':', ' ',
                                    'C', 'a', 'l', 'l', 'e', 'd', ' ', 'o', 'n', ' ', 'n', 'o', 'n',
                                    '-', 'c', 'o', 'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
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
    char message[50];
    // 'CalcZeroStartConstraints:2' c_assert(Curv.UseConstJerk, 'CalcZeroStartConstraints: Called on
    // non-const jerk'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (!Curv_UseConstJerk) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 50; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'CalcZeroStartConstraints:3' jps = Curv.ConstJerk*JerkScale;
    jps = Curv_ConstJerk * JerkScale;
    // 'CalcZeroStartConstraints:4' u = 1;
    // 'CalcZeroStartConstraints:5' t = (6*u/jps)^(1/3);
    t = std::pow(6.0 / jps, 0.33333333333333331);
    // 'CalcZeroStartConstraints:6' d1uk = jps*t.^2/2;
    d1uk = jps * std::pow(t, 2.0) / 2.0;
    // 'CalcZeroStartConstraints:7' d2uk = jps*t;
    b = jps * t;
    // 'CalcZeroStartConstraints:9' [~, r1D, r2D] = EvalCurvStruct(ctx, Curv, u);
    b_EvalCurvStruct(ctx_q_splines, Curv_Type, Curv_P0, Curv_P1, Curv_CorrectedHelixCenter,
                     Curv_evec, Curv_theta, Curv_pitch, Curv_CoeffP5, Curv_sp_index, Curv_a_param,
                     Curv_b_param, a__1, r1D, r2D);
    // 'CalcZeroStartConstraints:11' r2dt = bsxfun(@times, r2D, d1uk.^2) + bsxfun(@times, r1D,
    // d2uk);
    b_b = std::pow(d1uk, 2.0);
    // 'CalcZeroStartConstraints:12' r1dt = bsxfun(@times, r1D, d1uk);
    // 'CalcZeroStartConstraints:14' norm_vt = mysqrt(sum(r1dt.^2, 1));
    // 'mysqrt:3' y = sqrt(x);
    *v_0 = std::sqrt((std::pow(r1D[0] * d1uk, 2.0) + std::pow(r1D[1] * d1uk, 2.0)) +
                     std::pow(r1D[2] * d1uk, 2.0));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'CalcZeroStartConstraints:15' t_end = r1D/MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'CalcZeroStartConstraints:17' v_0 = norm_vt;
    // 'CalcZeroStartConstraints:18' at_0 = norm(r2dt.*t_end);
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
