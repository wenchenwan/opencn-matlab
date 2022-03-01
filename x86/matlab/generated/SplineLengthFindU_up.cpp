//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthFindU_up.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:00:11
//

// Include Files
#include "SplineLengthFindU_up.h"
#include "EvalBSplineNoCtx.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function u  = SplineLengthFindU_up(ctx, Curv, L, u1)
//
// computes approximately the value of curve parameter u such that the arc
//  length starting from u1 equals L.
//  This function takes usage of the precalculated arc lengths between knots.
//  The last integration interval is approximated by the trapezoidal rule.
//  u1 must satisfy 0 < u1 < 1.
//  In the normal case, u must satisfy u1 < u < 1. If L is too large, u is
//  set to -1
//  Warning : This function works only for B-spline of degree 3
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                int Curv_sp_index
//                double L
//                double u1
// Return Type  : double
//
namespace ocn {
double SplineLengthFindU_up(const queue_coder *ctx_q_splines,
                            const double ctx_cfg_GaussLegendreX[5],
                            const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index, double L,
                            double u1)
{
    __m128d r1;
    __m128d r4;
    CurvStruct b_expl_temp;
    CurvStruct d_expl_temp;
    CurvStruct expl_temp;
    double a__1[5][3];
    double r1D[5][3];
    double b_u0[5];
    double b_u1[5];
    double r1Dnorm[5];
    double b_a__1[3];
    double b_r1D[3];
    double Lcum;
    double b_r1Dnorm;
    double u;
    int exitg1;
    int i;
    int i1;
    int i4;
    int k;
    char message[54];
    // 'SplineLengthFindU_up:11' DEFAULT_TOL_NR  = 1e-6;
    //  Default tolerance for Newton Raphson
    // 'SplineLengthFindU_up:12' IND_KNOTS_MULT  = 4;
    //  Index used to remove multiple knots
    //                               (ONLY TRUE FOR CUBIC SPLINE)
    //  Get the sp structure
    // 'SplineLengthFindU_up:16' Spline = ctx.q_splines.get(Curv.sp_index);
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    // 'SplineLengthFindU_up:17' sp     = Spline.sp;
    //  Eliminate multiplicities at the end points
    // 'SplineLengthFindU_up:20' Knots  = sp.knots( IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = -1;
        i1 = -1;
    } else {
        i = 2;
        i1 = expl_temp.sp.knots.size(1) - 4;
    }
    // 'SplineLengthFindU_up:21' N      = length(Knots);
    // 'SplineLengthFindU_up:22' Lk     = sp.Lk;
    //
    // 'SplineLengthFindU_up:24' C_ASSERT_MSG = 'u1 must be %s or equal than the first spline knot';
    // 'SplineLengthFindU_up:25' c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater') );
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
    if (u1 < expl_temp.sp.knots[i + 1]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i2{0}; i2 < 54; i2++) {
            message[i2] = cv1[i2];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'SplineLengthFindU_up:26' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
    if (u1 > expl_temp.sp.knots[i1]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i3{0}; i3 < 54; i3++) {
            message[i3] = cv2[i3];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    //
    // 'SplineLengthFindU_up:28' k = 1;
    k = 1;
    //
    // 'SplineLengthFindU_up:30' while u1 > Knots(k)
    do {
        exitg1 = 0;
        i4 = i + k;
        if (u1 > expl_temp.sp.knots[i4]) {
            // 'SplineLengthFindU_up:31' k = k + 1;
            k++;
        } else {
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    __m128d r;
    __m128d r2;
    __m128d r3;
    double c_expl_temp;
    //
    //  Length to next break point
    // 'SplineLengthFindU_up:35' Lcum = SplineLengthApprox_Interval1(ctx, Curv, u1, Knots(k));
    //  computes approximately the arc length L with integration bounds u1 and u2.
    //  IMPORTANT : u1 and u2 should lie in the same knot interval.
    //  The computation is based on numerical Gauss Legendre integration
    //
    //  get the spline
    // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_splines.get(Curv.sp_index);
    ctx_q_splines->get(Curv_sp_index, &b_expl_temp);
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
    // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [u0, u1]
    // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
    //
    // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline, uvec);
    c_expl_temp = expl_temp.sp.knots[i4];
    r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
    r1 = _mm_set1_pd(1.0);
    r2 = _mm_set1_pd(u1);
    r3 = _mm_set1_pd(c_expl_temp);
    r4 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&b_u1[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                                  _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                       r4));
    r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
    _mm_storeu_pd(&b_u1[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                                  _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                       r4));
    b_u1[4] =
        (u1 * (1.0 - ctx_cfg_GaussLegendreX[4]) + c_expl_temp * (ctx_cfg_GaussLegendreX[4] + 1.0)) /
        2.0;
    EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY, b_expl_temp.sp.CoeffZ,
                     b_expl_temp.sp.Bl.handle, b_u1, a__1, r1D);
    // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    for (int b_k{0}; b_k < 5; b_k++) {
        r1Dnorm[b_k] = std::pow(r1D[b_k][0], 2.0);
        r1Dnorm[b_k] += std::pow(r1D[b_k][1], 2.0);
        r1Dnorm[b_k] += std::pow(r1D[b_k][2], 2.0);
    }
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
    b_r1Dnorm = 0.0;
    for (int c_k{0}; c_k < 5; c_k++) {
        double d;
        d = std::sqrt(r1Dnorm[c_k]);
        r1Dnorm[c_k] = d;
        b_r1Dnorm += d * ctx_cfg_GaussLegendreW[c_k];
    }
    Lcum = b_r1Dnorm * (expl_temp.sp.knots[i4] - u1) / 2.0;
    //  Gauss Legendre integration
    // 'SplineLengthApprox_Interval1:17' L = L(1);
    //  to satisfy Matlab Coder
    //
    // 'SplineLengthFindU_up:37' while Lcum < L
    do {
        exitg1 = 0;
        if (Lcum < L) {
            // 'SplineLengthFindU_up:38' if k > N-1
            if (k > (i1 - i) - 1) {
                // 'SplineLengthFindU_up:39' u = -1;
                u = -1.0;
                exitg1 = 1;
            } else {
                // 'SplineLengthFindU_up:42' Lcum = Lcum + Lk(k);
                Lcum += expl_temp.sp.Lk[k - 1];
                //  Sum up precalculated length between knots
                // 'SplineLengthFindU_up:43' k = k + 1;
                k++;
            }
        } else {
            double Lremain;
            double u0;
            double uk;
            double uk_old;
            int u0_tmp_tmp;
            //  undo last increment
            // 'SplineLengthFindU_up:46' k         = k - 1;
            // 'SplineLengthFindU_up:47' Lcum      = Lcum - Lk(k);
            Lcum -= expl_temp.sp.Lk[k - 2];
            // 'SplineLengthFindU_up:48' Lremain   = L - Lcum;
            Lremain = L - Lcum;
            //
            // 'SplineLengthFindU_up:50' u0     = Knots(k);
            u0_tmp_tmp = i + k;
            u0 = expl_temp.sp.knots[u0_tmp_tmp - 1];
            //  Initial guess for Newton Raphson iteration
            // 'SplineLengthFindU_up:52' uk     = 0.5*(Knots(k) + Knots(k+1));
            uk = 0.5 * (expl_temp.sp.knots[u0_tmp_tmp - 1] + expl_temp.sp.knots[u0_tmp_tmp]);
            //  Dummy value to ensure that while loop enters
            // 'SplineLengthFindU_up:54' uk_old = 2;
            //  Iterate until new value of uk is close to old value
            // 'SplineLengthFindU_up:57' while abs(uk - uk_old) > DEFAULT_TOL_NR
            uk_old = 2.0;
            while (std::abs(uk - uk_old) > 1.0E-6) {
                double c_r1Dnorm;
                int b_loop_ub;
                int c_loop_ub;
                int loop_ub;
                //  Evaluation of function which should become zero
                // 'SplineLengthFindU_up:59' fk = SplineLengthApprox_Interval1(ctx, Curv, u0, uk) -
                // Lremain;
                //  computes approximately the arc length L with integration bounds u1 and u2.
                //  IMPORTANT : u1 and u2 should lie in the same knot interval.
                //  The computation is based on numerical Gauss Legendre integration
                //
                //  get the spline
                // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_splines.get(Curv.sp_index);
                ctx_q_splines->get(Curv_sp_index, &d_expl_temp);
                b_expl_temp.sp.CoeffX.set_size(1, d_expl_temp.sp.CoeffX.size(1));
                loop_ub = d_expl_temp.sp.CoeffX.size(1);
                for (int i5{0}; i5 < loop_ub; i5++) {
                    b_expl_temp.sp.CoeffX[i5] = d_expl_temp.sp.CoeffX[i5];
                }
                b_expl_temp.sp.CoeffY.set_size(1, d_expl_temp.sp.CoeffY.size(1));
                b_loop_ub = d_expl_temp.sp.CoeffY.size(1);
                for (int i6{0}; i6 < b_loop_ub; i6++) {
                    b_expl_temp.sp.CoeffY[i6] = d_expl_temp.sp.CoeffY[i6];
                }
                b_expl_temp.sp.CoeffZ.set_size(1, d_expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = d_expl_temp.sp.CoeffZ.size(1);
                for (int i7{0}; i7 < c_loop_ub; i7++) {
                    b_expl_temp.sp.CoeffZ[i7] = d_expl_temp.sp.CoeffZ[i7];
                }
                __m128d r5;
                __m128d r6;
                __m128d r7;
                //  get Gauss-Legendre knots and weights
                // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
                // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
                //  apply linear map from[-1, 1] to [u0, u1]
                // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
                //
                // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline, uvec);
                r5 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
                r6 = _mm_set1_pd(u0);
                r7 = _mm_set1_pd(uk);
                _mm_storeu_pd(&b_u0[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r6, _mm_sub_pd(r1, r5)),
                                                              _mm_mul_pd(r7, _mm_add_pd(r5, r1))),
                                                   r4));
                r5 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
                _mm_storeu_pd(&b_u0[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r6, _mm_sub_pd(r1, r5)),
                                                              _mm_mul_pd(r7, _mm_add_pd(r5, r1))),
                                                   r4));
                b_u0[4] = (u0 * (1.0 - ctx_cfg_GaussLegendreX[4]) +
                           uk * (ctx_cfg_GaussLegendreX[4] + 1.0)) /
                          2.0;
                EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY,
                                 b_expl_temp.sp.CoeffZ, d_expl_temp.sp.Bl.handle, b_u0, a__1, r1D);
                // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                for (int d_k{0}; d_k < 5; d_k++) {
                    r1Dnorm[d_k] = std::pow(r1D[d_k][0], 2.0);
                    r1Dnorm[d_k] += std::pow(r1D[d_k][1], 2.0);
                    r1Dnorm[d_k] += std::pow(r1D[d_k][2], 2.0);
                }
                __m128d r8;
                // 'mysqrt:3' y = sqrt(x);
                r8 = _mm_loadu_pd(&r1Dnorm[0]);
                _mm_storeu_pd(&r1Dnorm[0], _mm_sqrt_pd(r8));
                r8 = _mm_loadu_pd(&r1Dnorm[2]);
                _mm_storeu_pd(&r1Dnorm[2], _mm_sqrt_pd(r8));
                r1Dnorm[4] = std::sqrt(r1Dnorm[4]);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
                //  Gauss Legendre integration
                // 'SplineLengthApprox_Interval1:17' L = L(1);
                //  to satisfy Matlab Coder
                // 'SplineLengthFindU_up:60' [~, r1D]  = EvalBSplineNoCtx(Spline, uk);
                EvalBSplineNoCtx(expl_temp.sp.CoeffX, expl_temp.sp.CoeffY, expl_temp.sp.CoeffZ,
                                 expl_temp.sp.Bl.handle, uk, b_a__1, b_r1D);
                //  Evaluation of the derivative of the function which should become zero
                // 'SplineLengthFindU_up:62' Dfk       = MyNorm(r1D);
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                //
                // 'SplineLengthFindU_up:64' uk_old = uk;
                uk_old = uk;
                // 'SplineLengthFindU_up:65' uk     = uk_old - fk/Dfk;
                c_r1Dnorm = 0.0;
                for (int i8{0}; i8 < 5; i8++) {
                    c_r1Dnorm += r1Dnorm[i8] * ctx_cfg_GaussLegendreW[i8];
                }
                uk -= (c_r1Dnorm * (uk - u0) / 2.0 - Lremain) /
                      std::sqrt((std::pow(b_r1D[0], 2.0) + std::pow(b_r1D[1], 2.0)) +
                                std::pow(b_r1D[2], 2.0));
                //  Newton Raphson update
                // 'SplineLengthFindU_up:66' if uk < u0
                if (uk < u0) {
                    // 'SplineLengthFindU_up:67' uk = u0;
                    uk = u0;
                    //  make sure not to run away
                }
            }
            //
            // 'SplineLengthFindU_up:71' u  = uk;
            u = uk;
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    return u;
}

} // namespace ocn

//
// File trailer for SplineLengthFindU_up.cpp
//
// [EOF]
//
