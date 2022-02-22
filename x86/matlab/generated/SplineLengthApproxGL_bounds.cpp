//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_bounds.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
//

// Include Files
#include "SplineLengthApproxGL_bounds.h"
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
// function L  = SplineLengthApproxGL_bounds(ctx, Curv, u1, u2)
//
// computes approximately the arc length L with arbitrary integration bounds u1 and u2.
//  The computation is based on numerical Gauss Legendre integration.
//  This function takes usage of the precalculated arc lengths between knots.
//
//  get the sp structure
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                int Curv_sp_index
//                double u1
//                double u2
// Return Type  : double
//
namespace ocn {
double SplineLengthApproxGL_bounds(const queue_coder *ctx_q_splines,
                                   const double ctx_cfg_GaussLegendreX[5],
                                   const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index,
                                   double u1, double u2)
{
    static const char e_message[53]{
        'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a', 'l', 'l', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'l', 'a', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    static const char b_message[26]{'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b',
                                    'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
                                    ' ', 't', 'h', 'a', 'n', ' ', 'u', '1'};
    CurvStruct b_expl_temp;
    CurvStruct d_expl_temp;
    CurvStruct expl_temp;
    double a__1[5][3];
    double r1D[5][3];
    double b_u1[5];
    double e_expl_temp[5];
    double r1Dnorm[5];
    double L;
    int exitg1;
    int i;
    int i1;
    int i5;
    int k;
    char c_message[54];
    char d_message[53];
    char message[26];
    // 'SplineLengthApproxGL_bounds:7' Spline = ctx.q_splines.get(Curv.sp_index);
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    // 'SplineLengthApproxGL_bounds:8' sp     = Spline.sp;
    // 'SplineLengthApproxGL_bounds:9' Knots  = sp.knots(4:end-3);
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = -1;
        i1 = 3;
    } else {
        i = 2;
        i1 = expl_temp.sp.knots.size(1);
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_bounds:10' Lk     = sp.Lk;
    //
    // 'SplineLengthApproxGL_bounds:12' c_assert(u2 > u1,          'u2 must be greater than u1');
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
    if (u2 <= u1) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i2{0}; i2 < 26; i2++) {
            message[i2] = b_message[i2];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'SplineLengthApproxGL_bounds:13' c_assert(u1 >= Knots(1),   'u1 must be greater or equal than
    // the first spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u1 < expl_temp.sp.knots[i + 1]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i3{0}; i3 < 54; i3++) {
            c_message[i3] = cv1[i3];
        }
        c_assert_(&c_message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'SplineLengthApproxGL_bounds:14' c_assert(u2 <= Knots(end), 'u2 must be smaller or equal than
    // the last spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u2 > expl_temp.sp.knots[i1 - 4]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i4{0}; i4 < 53; i4++) {
            d_message[i4] = e_message[i4];
        }
        c_assert_(&d_message[0]);
    }
    // 'c_assert:6' value = condition;
    //
    // 'SplineLengthApproxGL_bounds:16' k = 1;
    k = 1;
    //
    // 'SplineLengthApproxGL_bounds:18' while u1 > Knots(k)
    do {
        exitg1 = 0;
        i5 = i + k;
        if (u1 > expl_temp.sp.knots[i5]) {
            // 'SplineLengthApproxGL_bounds:19' k = k + 1;
            k++;
        } else {
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    //
    // 'SplineLengthApproxGL_bounds:22' if u2 < Knots(k)
    if (u2 < expl_temp.sp.knots[i5]) {
        __m128d r;
        __m128d r1;
        __m128d r3;
        __m128d r5;
        __m128d r7;
        double b_r1Dnorm;
        // 'SplineLengthApproxGL_bounds:23' L = SplineLengthApprox_Interval1(ctx, Curv, u1, u2);
        //  computes approximately the arc length L with integration bounds u1 and u2.
        //  IMPORTANT : u1 and u2 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  get the spline
        // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_splines.get(Curv.sp_index);
        ctx_q_splines->get(Curv_sp_index, &expl_temp);
        //  get Gauss-Legendre knots and weights
        // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
        // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
        //
        // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline, uvec);
        r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
        r1 = _mm_set1_pd(1.0);
        r3 = _mm_set1_pd(u1);
        r5 = _mm_set1_pd(u2);
        r7 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&b_u1[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r1, r)),
                                                      _mm_mul_pd(r5, _mm_add_pd(r, r1))),
                                           r7));
        r = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&b_u1[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r1, r)),
                                                      _mm_mul_pd(r5, _mm_add_pd(r, r1))),
                                           r7));
        b_u1[4] =
            (u1 * (1.0 - ctx_cfg_GaussLegendreX[4]) + u2 * (ctx_cfg_GaussLegendreX[4] + 1.0)) / 2.0;
        EvalBSplineNoCtx(expl_temp.sp.CoeffX, expl_temp.sp.CoeffY, expl_temp.sp.CoeffZ,
                         expl_temp.sp.Bl.handle, b_u1, a__1, r1D);
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
        for (int d_k{0}; d_k < 5; d_k++) {
            double d;
            d = std::sqrt(r1Dnorm[d_k]);
            r1Dnorm[d_k] = d;
            b_r1Dnorm += d * ctx_cfg_GaussLegendreW[d_k];
        }
        L = b_r1Dnorm * (u2 - u1) / 2.0;
        //  Gauss Legendre integration
        // 'SplineLengthApprox_Interval1:17' L = L(1);
        //  to satisfy Matlab Coder
        //  u1 and u2 in the same break interval
    } else {
        __m128d r2;
        __m128d r4;
        __m128d r6;
        __m128d r8;
        __m128d r9;
        double c_expl_temp;
        double c_r1Dnorm;
        double d_r1Dnorm;
        double expl_temp_tmp;
        int b_loop_ub;
        int c_loop_ub;
        int loop_ub;
        // 'SplineLengthApproxGL_bounds:24' else
        // 'SplineLengthApproxGL_bounds:25' L = SplineLengthApprox_Interval1(ctx, Curv, u1,
        // Knots(k));
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
        expl_temp_tmp = expl_temp.sp.knots[i5];
        r2 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
        r4 = _mm_set1_pd(1.0);
        r6 = _mm_set1_pd(u1);
        r8 = _mm_set1_pd(expl_temp_tmp);
        r9 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&b_u1[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r6, _mm_sub_pd(r4, r2)),
                                                      _mm_mul_pd(r8, _mm_add_pd(r2, r4))),
                                           r9));
        r2 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&b_u1[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r6, _mm_sub_pd(r4, r2)),
                                                      _mm_mul_pd(r8, _mm_add_pd(r2, r4))),
                                           r9));
        b_u1[4] = (u1 * (1.0 - ctx_cfg_GaussLegendreX[4]) +
                   expl_temp_tmp * (ctx_cfg_GaussLegendreX[4] + 1.0)) /
                  2.0;
        EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY, b_expl_temp.sp.CoeffZ,
                         b_expl_temp.sp.Bl.handle, b_u1, a__1, r1D);
        // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        for (int c_k{0}; c_k < 5; c_k++) {
            r1Dnorm[c_k] = std::pow(r1D[c_k][0], 2.0);
            r1Dnorm[c_k] += std::pow(r1D[c_k][1], 2.0);
            r1Dnorm[c_k] += std::pow(r1D[c_k][2], 2.0);
        }
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
        c_r1Dnorm = 0.0;
        for (int e_k{0}; e_k < 5; e_k++) {
            double d1;
            d1 = std::sqrt(r1Dnorm[e_k]);
            r1Dnorm[e_k] = d1;
            c_r1Dnorm += d1 * ctx_cfg_GaussLegendreW[e_k];
        }
        L = c_r1Dnorm * (expl_temp_tmp - u1) / 2.0;
        //  Gauss Legendre integration
        // 'SplineLengthApprox_Interval1:17' L = L(1);
        //  to satisfy Matlab Coder
        //  remaining length to next break point
        // 'SplineLengthApproxGL_bounds:26' while u2 > Knots(k)
        do {
            exitg1 = 0;
            c_expl_temp = expl_temp.sp.knots[i + k];
            if (u2 > c_expl_temp) {
                // 'SplineLengthApproxGL_bounds:27' L = L + Lk(k);
                L += expl_temp.sp.Lk[k - 1];
                //  sum up precalculated length between knots
                // 'SplineLengthApproxGL_bounds:28' k = k + 1;
                k++;
            } else {
                exitg1 = 1;
            }
        } while (exitg1 == 0);
        // 'SplineLengthApproxGL_bounds:30' L = L + SplineLengthApprox_Interval1(ctx, Curv,
        // Knots(k), u2);
        //  computes approximately the arc length L with integration bounds u1 and u2.
        //  IMPORTANT : u1 and u2 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  get the spline
        // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_splines.get(Curv.sp_index);
        ctx_q_splines->get(Curv_sp_index, &d_expl_temp);
        b_expl_temp.sp.CoeffX.set_size(1, d_expl_temp.sp.CoeffX.size(1));
        loop_ub = d_expl_temp.sp.CoeffX.size(1);
        for (int i6{0}; i6 < loop_ub; i6++) {
            b_expl_temp.sp.CoeffX[i6] = d_expl_temp.sp.CoeffX[i6];
        }
        b_expl_temp.sp.CoeffY.set_size(1, d_expl_temp.sp.CoeffY.size(1));
        b_loop_ub = d_expl_temp.sp.CoeffY.size(1);
        for (int i7{0}; i7 < b_loop_ub; i7++) {
            b_expl_temp.sp.CoeffY[i7] = d_expl_temp.sp.CoeffY[i7];
        }
        b_expl_temp.sp.CoeffZ.set_size(1, d_expl_temp.sp.CoeffZ.size(1));
        c_loop_ub = d_expl_temp.sp.CoeffZ.size(1);
        for (int i8{0}; i8 < c_loop_ub; i8++) {
            b_expl_temp.sp.CoeffZ[i8] = d_expl_temp.sp.CoeffZ[i8];
        }
        __m128d r10;
        __m128d r11;
        __m128d r12;
        //  get Gauss-Legendre knots and weights
        // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
        // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
        //
        // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline, uvec);
        r10 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]);
        r11 = _mm_set1_pd(c_expl_temp);
        r12 = _mm_set1_pd(u2);
        _mm_storeu_pd(&e_expl_temp[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r11, _mm_sub_pd(r4, r10)),
                                                             _mm_mul_pd(r12, _mm_add_pd(r10, r4))),
                                                  r9));
        r10 = _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&e_expl_temp[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r11, _mm_sub_pd(r4, r10)),
                                                             _mm_mul_pd(r12, _mm_add_pd(r10, r4))),
                                                  r9));
        e_expl_temp[4] = (c_expl_temp * (1.0 - ctx_cfg_GaussLegendreX[4]) +
                          u2 * (ctx_cfg_GaussLegendreX[4] + 1.0)) /
                         2.0;
        EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY, b_expl_temp.sp.CoeffZ,
                         d_expl_temp.sp.Bl.handle, e_expl_temp, a__1, r1D);
        // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        for (int f_k{0}; f_k < 5; f_k++) {
            r1Dnorm[f_k] = std::pow(r1D[f_k][0], 2.0);
            r1Dnorm[f_k] += std::pow(r1D[f_k][1], 2.0);
            r1Dnorm[f_k] += std::pow(r1D[f_k][2], 2.0);
        }
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
        //  Gauss Legendre integration
        // 'SplineLengthApprox_Interval1:17' L = L(1);
        //  to satisfy Matlab Coder
        d_r1Dnorm = 0.0;
        for (int g_k{0}; g_k < 5; g_k++) {
            double d2;
            d2 = std::sqrt(r1Dnorm[g_k]);
            r1Dnorm[g_k] = d2;
            d_r1Dnorm += d2 * ctx_cfg_GaussLegendreW[g_k];
        }
        L += d_r1Dnorm * (u2 - c_expl_temp) / 2.0;
        //  remaining length to u2
    }
    return L;
}

} // namespace ocn

//
// File trailer for SplineLengthApproxGL_bounds.cpp
//
// [EOF]
//
