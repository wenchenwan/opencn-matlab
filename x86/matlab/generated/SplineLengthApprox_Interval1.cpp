//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApprox_Interval1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "SplineLengthApprox_Interval1.h"
#include "EvalBSplineNoCtx.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// computes approximately the arc length L with integration bounds u1 and u2.
//  IMPORTANT : u1 and u2 should lie in the same knot interval.
//  The computation is based on numerical Gauss Legendre integration
//
//  get the spline
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                int Curv_sp_index
//                double u0
//                double u1
// Return Type  : double
//
namespace ocn {
double SplineLengthApprox_Interval1(const queue_coder *ctx_q_splines,
                                    const double ctx_cfg_GaussLegendreX[5],
                                    const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index,
                                    double u0, double u1)
{
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    CurvStruct expl_temp;
    double a__1[5][3];
    double r1D[5][3];
    double b_u0[5];
    double r1Dnorm[5];
    double b_r1Dnorm;
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    //  get Gauss-Legendre knots and weights
    //  apply linear map from[-1, 1] to [u0, u1]
    //
    r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
    r1 = _mm_set1_pd(1.0);
    r2 = _mm_set1_pd(u0);
    r3 = _mm_set1_pd(u1);
    r4 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&b_u0[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                                  _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                       r4));
    r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
    _mm_storeu_pd(&b_u0[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                                  _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                       r4));
    b_u0[4] =
        (u0 * (1.0 - ctx_cfg_GaussLegendreX[4]) + u1 * (ctx_cfg_GaussLegendreX[4] + 1.0)) / 2.0;
    EvalBSplineNoCtx(expl_temp.sp.CoeffX, expl_temp.sp.CoeffY, expl_temp.sp.CoeffZ,
                     expl_temp.sp.Bl.handle, b_u0, a__1, r1D);
    for (int k{0}; k < 5; k++) {
        r1Dnorm[k] = std::pow(r1D[k][0], 2.0);
        r1Dnorm[k] += std::pow(r1D[k][1], 2.0);
        r1Dnorm[k] += std::pow(r1D[k][2], 2.0);
    }
    sqrt_calls++;
    b_r1Dnorm = 0.0;
    for (int b_k{0}; b_k < 5; b_k++) {
        double d;
        d = std::sqrt(r1Dnorm[b_k]);
        r1Dnorm[b_k] = d;
        b_r1Dnorm += d * ctx_cfg_GaussLegendreW[b_k];
    }
    return b_r1Dnorm * (u1 - u0) / 2.0;
    //  Gauss Legendre integration
    //  to satisfy Matlab Coder
}

} // namespace ocn

//
// File trailer for SplineLengthApprox_Interval1.cpp
//
// [EOF]
//
