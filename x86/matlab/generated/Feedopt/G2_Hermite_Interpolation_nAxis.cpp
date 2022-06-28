//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation_nAxis.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "G2_Hermite_Interpolation_nAxis.h"
#include "CalcAlpha0.h"
#include "Calc_beta0_beta1.h"
#include "CoefPolySys.h"
#include "EvalCostIntegral.h"
#include "calc_t_nk_kappa.h"
#include "div.h"
#include "find.h"
#include "minOrMax.h"
#include "mldivide.h"
#include "coder_array.h"
#include "functions.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void b_binary_expand_op(double alpha1_t_data[], int *alpha1_t_size, const double CoefPS[16],
                               const ::coder::array<double, 1U> &r, const double alpha0_t_data[],
                               const int *alpha0_t_size);

static void binary_expand_op(double alpha0_t_data[], int *alpha0_t_size, const double CoefPS[16],
                             const ::coder::array<double, 1U> &r, const double alpha1_t_data[],
                             const int *alpha1_t_size);

} // namespace ocn

// Function Definitions
//
// Arguments    : double alpha1_t_data[]
//                int *alpha1_t_size
//                const double CoefPS[16]
//                const ::coder::array<double, 1U> &r
//                const double alpha0_t_data[]
//                const int *alpha0_t_size
// Return Type  : void
//
namespace ocn {
static void b_binary_expand_op(double alpha1_t_data[], int *alpha1_t_size, const double CoefPS[16],
                               const ::coder::array<double, 1U> &r, const double alpha0_t_data[],
                               const int *alpha0_t_size)
{
    double b_CoefPS;
    double c_CoefPS;
    double d_CoefPS;
    double e_CoefPS;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_CoefPS = CoefPS[1];
    c_CoefPS = CoefPS[3];
    d_CoefPS = CoefPS[7];
    e_CoefPS = CoefPS[6];
    if (*alpha0_t_size == 1) {
        *alpha1_t_size = r.size(0);
    } else {
        *alpha1_t_size = *alpha0_t_size;
    }
    stride_0_0 = (r.size(0) != 1);
    stride_1_0 = (*alpha0_t_size != 1);
    if (*alpha0_t_size == 1) {
        loop_ub = r.size(0);
    } else {
        loop_ub = *alpha0_t_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        alpha1_t_data[i] =
            -((b_CoefPS * r[i * stride_0_0] + c_CoefPS * alpha0_t_data[i * stride_1_0]) +
              d_CoefPS) /
            e_CoefPS;
    }
}

//
// Arguments    : double alpha0_t_data[]
//                int *alpha0_t_size
//                const double CoefPS[16]
//                const ::coder::array<double, 1U> &r
//                const double alpha1_t_data[]
//                const int *alpha1_t_size
// Return Type  : void
//
static void binary_expand_op(double alpha0_t_data[], int *alpha0_t_size, const double CoefPS[16],
                             const ::coder::array<double, 1U> &r, const double alpha1_t_data[],
                             const int *alpha1_t_size)
{
    double b_CoefPS;
    double c_CoefPS;
    double d_CoefPS;
    double e_CoefPS;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_CoefPS = CoefPS[9];
    c_CoefPS = CoefPS[11];
    d_CoefPS = CoefPS[15];
    e_CoefPS = CoefPS[14];
    if (*alpha1_t_size == 1) {
        *alpha0_t_size = r.size(0);
    } else {
        *alpha0_t_size = *alpha1_t_size;
    }
    stride_0_0 = (r.size(0) != 1);
    stride_1_0 = (*alpha1_t_size != 1);
    if (*alpha1_t_size == 1) {
        loop_ub = r.size(0);
    } else {
        loop_ub = *alpha1_t_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        alpha0_t_data[i] =
            -((b_CoefPS * r[i * stride_0_0] + c_CoefPS * alpha1_t_data[i * stride_1_0]) +
              d_CoefPS) /
            e_CoefPS;
    }
}

//
// function [p5, status, alpha0, alpha1] = G2_Hermite_Interpolation_nAxis(ctx, r0D0_in, r0D1_in,
// r0D2_in, r1D0_in, r1D1_in, r1D2_in)
//
// Function are calculated for 5 axis
//
// Arguments    : int ctx_cfg_NumberAxis
//                const ::coder::array<double, 1U> &r0D0_in
//                const ::coder::array<double, 1U> &r0D1_in
//                const ::coder::array<double, 1U> &r0D2_in
//                const ::coder::array<double, 1U> &r1D0_in
//                const ::coder::array<double, 1U> &r1D1_in
//                const ::coder::array<double, 1U> &r1D2_in
//                double p5[6][5]
//                int *status
// Return Type  : void
//
void G2_Hermite_Interpolation_nAxis(
    int ctx_cfg_NumberAxis, const ::coder::array<double, 1U> &r0D0_in,
    const ::coder::array<double, 1U> &r0D1_in, const ::coder::array<double, 1U> &r0D2_in,
    const ::coder::array<double, 1U> &r1D0_in, const ::coder::array<double, 1U> &r1D1_in,
    const ::coder::array<double, 1U> &r1D2_in, double p5[6][5], int *status)
{
    static const double c_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double f_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char b_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char d_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char e_b[6]{-3, 7, -4, 0, 0, 0};
    ::coder::array<double, 1U> r11;
    ::coder::array<double, 1U> r9;
    creal_T b_alpha1_v[9];
    creal_T alpha0_v[3];
    creal_T alpha1_v[3];
    double b_alpha0[6][5];
    double b_r0D0[6][5];
    double b_r1D0[6][5];
    double c_r0D0[6][5];
    double CoefPS[16];
    double dv1[10];
    double dv2[10];
    double CostInt_data[9];
    double alpha0_t_data[9];
    double alpha1_t_data[9];
    double beta0_u_data[9];
    double beta1_u_data[9];
    double t10_data[9];
    double t11_data[9];
    double t12_data[9];
    double t5_data[9];
    double c_a[5];
    double n0[5];
    double n1[5];
    double r0D0[5];
    double r0D1[5];
    double r0D2[5];
    double r1D0[5];
    double r1D1[5];
    double r1D2[5];
    double t0[5];
    double t1[5];
    double b_CoefPS[2][2];
    double dv[4];
    double X[2];
    double c_CoefPS[2];
    double a;
    double alpha0;
    double alpha1;
    double b_a;
    double b_ex;
    double c_ex;
    double ex;
    double kappa0;
    double kappa1;
    int Idx_data[9];
    int Idx_size;
    int alpha0_t_size;
    int alpha1_t_size;
    int b_iindx;
    int b_loop_ub;
    int b_trueCount;
    int c_iindx;
    int c_loop_ub;
    int c_trueCount;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int iindx;
    int loop_ub;
    int t12_size;
    int t5_size;
    int trueCount;
    signed char tmp_data[3];
    bool c_alpha0_t_data[9];
    bool b_alpha0_t_data[3];
    bool b_alpha1_t_data[3];
    bool guard1{false};
    //
    //      This file is part of the Optimal G^2 Hermite Interpolation Software.
    //
    //      Copyright (C) 2017-2019 Raoul Herzog, Philippe Blanc
    //                              mecatronYx group at HEIG-VD
    //                              University of Applied Sciences Western Switzerland
    //                              CH-1401 Yverdon-les-Bains
    //                              All rights reserved.
    //
    //      This is free software; you can redistribute it and/or
    //      modify it under the terms of the GNU Lesser General Public
    //      License as published by the Free Software Foundation; either
    //      version 3 of the License, or (at your option) any later version.
    //
    //      This software is distributed in the hope that it will be useful,
    //      but WITHOUT ANY WARRANTY; without even the implied warranty of
    //      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    //      Lesser General Public License for more details.
    //
    //      You should have received a copy of the GNU Lesser General Public
    //      License along with this software; if not, write to the Free Software
    //      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
    //
    //  [p5_3D, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2)
    //
    //  Compute an optimal trajectory in R^3, connecting the point r0 to r1 with
    //  C^2 smoothness while minimizing the integral of the norm of the third
    //  derivative.
    // 'G2_Hermite_Interpolation_nAxis:33' r0D0 = zeros(5, 1);
    // 'G2_Hermite_Interpolation_nAxis:33' r0D1 = zeros(5, 1);
    // 'G2_Hermite_Interpolation_nAxis:33' r0D2 = zeros(5, 1);
    // 'G2_Hermite_Interpolation_nAxis:34' r1D0 = zeros(5, 1);
    // 'G2_Hermite_Interpolation_nAxis:34' r1D1 = zeros(5, 1);
    // 'G2_Hermite_Interpolation_nAxis:34' r1D2 = zeros(5, 1);
    for (int i{0}; i < 5; i++) {
        r0D0[i] = 0.0;
        r0D1[i] = 0.0;
        r0D2[i] = 0.0;
        r1D0[i] = 0.0;
        r1D1[i] = 0.0;
        r1D2[i] = 0.0;
    }
    //  Place input vector in
    // 'G2_Hermite_Interpolation_nAxis:37' r0D0(1:ctx.cfg.NumberAxis) = r0D0_in;
    if (1 > ctx_cfg_NumberAxis) {
        loop_ub = 0;
    } else {
        loop_ub = ctx_cfg_NumberAxis;
    }
    for (int b_i{0}; b_i < loop_ub; b_i++) {
        r0D0[b_i] = r0D0_in[b_i];
    }
    // 'G2_Hermite_Interpolation_nAxis:38' r0D1(1:ctx.cfg.NumberAxis) = r0D1_in;
    if (1 > ctx_cfg_NumberAxis) {
        b_loop_ub = 0;
    } else {
        b_loop_ub = ctx_cfg_NumberAxis;
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r0D1[i1] = r0D1_in[i1];
    }
    // 'G2_Hermite_Interpolation_nAxis:39' r0D2(1:ctx.cfg.NumberAxis) = r0D2_in;
    if (1 > ctx_cfg_NumberAxis) {
        c_loop_ub = 0;
    } else {
        c_loop_ub = ctx_cfg_NumberAxis;
    }
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D2[i2] = r0D2_in[i2];
    }
    // 'G2_Hermite_Interpolation_nAxis:40' r1D0(1:ctx.cfg.NumberAxis) = r1D0_in;
    if (1 > ctx_cfg_NumberAxis) {
        d_loop_ub = 0;
    } else {
        d_loop_ub = ctx_cfg_NumberAxis;
    }
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D0[i3] = r1D0_in[i3];
    }
    // 'G2_Hermite_Interpolation_nAxis:41' r1D1(1:ctx.cfg.NumberAxis) = r1D1_in;
    if (1 > ctx_cfg_NumberAxis) {
        e_loop_ub = 0;
    } else {
        e_loop_ub = ctx_cfg_NumberAxis;
    }
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r1D1[i4] = r1D1_in[i4];
    }
    // 'G2_Hermite_Interpolation_nAxis:42' r1D2(1:ctx.cfg.NumberAxis) = r1D2_in;
    if (1 > ctx_cfg_NumberAxis) {
        f_loop_ub = 0;
    } else {
        f_loop_ub = ctx_cfg_NumberAxis;
    }
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r1D2[i5] = r1D2_in[i5];
    }
    // 'G2_Hermite_Interpolation_nAxis:44' nAxis = 5;
    // 'G2_Hermite_Interpolation_nAxis:45' D = ones(nAxis, 1);
    // 'G2_Hermite_Interpolation_nAxis:47' status = int32(1);
    *status = 1;
    //  default success
    // 'G2_Hermite_Interpolation_nAxis:49' p5 = zeros(nAxis,6);
    std::memset(&p5[0][0], 0, 30U * sizeof(double));
    // 'G2_Hermite_Interpolation_nAxis:51' alpha0 = 0;
    // 'G2_Hermite_Interpolation_nAxis:52' alpha1 = 0;
    //  compute Frenet frame
    // 'G2_Hermite_Interpolation_nAxis:55' [t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
    calc_t_nk_kappa(r0D1, r0D2, t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation_nAxis:56' [t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);
    calc_t_nk_kappa(r1D1, r1D2, t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    // 'G2_Hermite_Interpolation_nAxis:64' CoefPS = CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D);
    CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, CoefPS);
    //
    // 'G2_Hermite_Interpolation_nAxis:66' a1     = CoefPS(1);
    // 'G2_Hermite_Interpolation_nAxis:67' a0     = CoefPS(2);
    // 'G2_Hermite_Interpolation_nAxis:68' b1     = CoefPS(3);
    // 'G2_Hermite_Interpolation_nAxis:69' b0     = CoefPS(4);
    // 'G2_Hermite_Interpolation_nAxis:70' c3     = CoefPS(5);
    // 'G2_Hermite_Interpolation_nAxis:71' c2     = CoefPS(6);
    // 'G2_Hermite_Interpolation_nAxis:72' c1     = CoefPS(7);
    // 'G2_Hermite_Interpolation_nAxis:73' c0     = CoefPS(8);
    // 'G2_Hermite_Interpolation_nAxis:74' d1     = CoefPS(9);
    // 'G2_Hermite_Interpolation_nAxis:75' d0     = CoefPS(10);
    // 'G2_Hermite_Interpolation_nAxis:76' e1     = CoefPS(11);
    // 'G2_Hermite_Interpolation_nAxis:77' e0     = CoefPS(12);
    // 'G2_Hermite_Interpolation_nAxis:78' f3     = CoefPS(13);
    // 'G2_Hermite_Interpolation_nAxis:79' f2     = CoefPS(14);
    // 'G2_Hermite_Interpolation_nAxis:80' f1     = CoefPS(15);
    // 'G2_Hermite_Interpolation_nAxis:81' f0     = CoefPS(16);
    // 'G2_Hermite_Interpolation_nAxis:82' TolZero = 1e-11;
    //
    // 'G2_Hermite_Interpolation_nAxis:84' if (kappa0 == 0) && (kappa1 == 0)
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        //  degenerated case where the polynomial system degenerates to a linear one
        // 'G2_Hermite_Interpolation_nAxis:85' M       = [b0, c1;
        // 'G2_Hermite_Interpolation_nAxis:86'                f1, e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:88' B       = [-c0;
        // 'G2_Hermite_Interpolation_nAxis:89'                -f0];
        //
        // 'G2_Hermite_Interpolation_nAxis:91' X       = M \ B;
        b_CoefPS[0][0] = CoefPS[3];
        b_CoefPS[1][0] = CoefPS[6];
        b_CoefPS[0][1] = CoefPS[14];
        b_CoefPS[1][1] = CoefPS[11];
        c_CoefPS[0] = -CoefPS[7];
        c_CoefPS[1] = -CoefPS[15];
        coder::mldivide(b_CoefPS, c_CoefPS, X);
        //  resolution of linear system
        // 'G2_Hermite_Interpolation_nAxis:92' alpha0  = X(1);
        alpha0 = X[0];
        // 'G2_Hermite_Interpolation_nAxis:93' alpha1  = X(2);
        alpha1 = X[1];
        // 'G2_Hermite_Interpolation_nAxis:95' if ~((alpha0 > 0) && (alpha1 > 0))
        if ((X[0] > 0.0) && (X[1] > 0.0)) {
            // 'G2_Hermite_Interpolation_nAxis:99' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1,
            // ... 'G2_Hermite_Interpolation_nAxis:100'                                       r0D0,
            // t0, n0, ... 'G2_Hermite_Interpolation_nAxis:101' r1D0, t1, n1, D);
            Calc_beta0_beta1(X[0], X[1], r0D0, t0, n0, r1D0, t1, n1, &a, &b_a);
            guard1 = true;
        }
    } else if (kappa0 == 0.0) {
        int partialTrueCount;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        bool unnamed_idx_2;
        // 'G2_Hermite_Interpolation_nAxis:102' elseif kappa0 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:104' Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0
        // + b1*f0 - c1*f1, b0*f0 - c0*f1];
        //
        // 'G2_Hermite_Interpolation_nAxis:106' alpha1_v = c_roots_(Coef);
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        alpha1_v[0].re = 0.0;
        alpha1_v[0].im = 0.0;
        alpha1_v[1].re = 0.0;
        alpha1_v[1].im = 0.0;
        alpha1_v[2].re = 0.0;
        alpha1_v[2].im = 0.0;
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        dv[0] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
        dv[1] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
        dv[2] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
        dv[3] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
        c_roots(&dv[0], &alpha1_v[0], 4);
        //  all roots of 3th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:107' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        trueCount = 0;
        unnamed_idx_2 = (std::abs(alpha1_v[0].im) < 1.0E-11);
        unnamed_idx_0 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[0].re > 0.0)) {
            trueCount = 1;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[1].im) < 1.0E-11);
        unnamed_idx_1 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[1].re > 0.0)) {
            trueCount++;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[2].im) < 1.0E-11);
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            trueCount++;
        }
        partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha1_v[0].re > 0.0)) {
            tmp_data[0] = 1;
            partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha1_v[1].re > 0.0)) {
            tmp_data[partialTrueCount] = 2;
            partialTrueCount++;
        }
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            tmp_data[partialTrueCount] = 3;
        }
        for (int i7{0}; i7 < trueCount; i7++) {
            alpha1_t_data[i7] = alpha1_v[tmp_data[i7] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:109' if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:110' alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
            r9.set_size(trueCount);
            for (int i11{0}; i11 < trueCount; i11++) {
                r9[i11] = std::pow(alpha1_t_data[i11], 2.0);
            }
            if (r9.size(0) == trueCount) {
                double d_CoefPS;
                double f_CoefPS;
                double h_CoefPS;
                double j_CoefPS;
                int g_loop_ub;
                int i24;
                int scalarLB;
                int vectorUB;
                d_CoefPS = CoefPS[9];
                f_CoefPS = CoefPS[11];
                h_CoefPS = CoefPS[15];
                j_CoefPS = CoefPS[14];
                alpha0_t_size = r9.size(0);
                g_loop_ub = r9.size(0);
                scalarLB = (r9.size(0) / 2) << 1;
                vectorUB = scalarLB - 2;
                for (i24 = 0; i24 <= vectorUB; i24 += 2) {
                    __m128d r22;
                    __m128d r25;
                    r22 = _mm_loadu_pd(&r9[i24]);
                    r25 = _mm_loadu_pd(&alpha1_t_data[i24]);
                    _mm_storeu_pd(
                        &alpha0_t_data[i24],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(d_CoefPS), r22),
                                                      _mm_mul_pd(_mm_set1_pd(f_CoefPS), r25)),
                                           _mm_set1_pd(h_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(j_CoefPS)));
                }
                for (i24 = scalarLB; i24 < g_loop_ub; i24++) {
                    alpha0_t_data[i24] =
                        -((d_CoefPS * r9[i24] + f_CoefPS * alpha1_t_data[i24]) + h_CoefPS) /
                        j_CoefPS;
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r9, alpha1_t_data,
                                 &trueCount);
            }
        } else {
            int i18;
            int i22;
            int i27;
            // 'G2_Hermite_Interpolation_nAxis:111' else
            // 'G2_Hermite_Interpolation_nAxis:112' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            r9.set_size(trueCount);
            for (int i13{0}; i13 < trueCount; i13++) {
                r9[i13] = std::pow(alpha1_t_data[i13], 3.0);
            }
            r11.set_size(trueCount);
            for (int i16{0}; i16 < trueCount; i16++) {
                r11[i16] = std::pow(alpha1_t_data[i16], 2.0);
            }
            if (r9.size(0) == 1) {
                i18 = r11.size(0);
            } else {
                i18 = r9.size(0);
            }
            if (r9.size(0) == 1) {
                i22 = r11.size(0);
            } else {
                i22 = r9.size(0);
            }
            if (i22 == 1) {
                i27 = trueCount;
            } else if (r9.size(0) == 1) {
                i27 = r11.size(0);
            } else {
                i27 = r9.size(0);
            }
            if ((r9.size(0) == r11.size(0)) && (i18 == trueCount) && (i27 == trueCount)) {
                double l_CoefPS;
                double n_CoefPS;
                double p_CoefPS;
                double r_CoefPS;
                double t_CoefPS;
                double v_CoefPS;
                int c_scalarLB;
                int c_vectorUB;
                int i31;
                int i_loop_ub;
                l_CoefPS = CoefPS[4];
                n_CoefPS = CoefPS[5];
                p_CoefPS = CoefPS[6];
                r_CoefPS = CoefPS[7];
                t_CoefPS = CoefPS[2];
                v_CoefPS = CoefPS[3];
                alpha0_t_size = r9.size(0);
                i_loop_ub = r9.size(0);
                c_scalarLB = (r9.size(0) / 2) << 1;
                c_vectorUB = c_scalarLB - 2;
                for (i31 = 0; i31 <= c_vectorUB; i31 += 2) {
                    __m128d r34;
                    __m128d r36;
                    __m128d r38;
                    r34 = _mm_loadu_pd(&r9[i31]);
                    r36 = _mm_loadu_pd(&r11[i31]);
                    r38 = _mm_loadu_pd(&alpha1_t_data[i31]);
                    _mm_storeu_pd(
                        &alpha0_t_data[i31],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(l_CoefPS), r34),
                                                          _mm_mul_pd(_mm_set1_pd(n_CoefPS), r36)),
                                               _mm_mul_pd(_mm_set1_pd(p_CoefPS), r38)),
                                    _mm_set1_pd(r_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t_CoefPS), r38),
                                       _mm_set1_pd(v_CoefPS))));
                }
                for (i31 = c_scalarLB; i31 < i_loop_ub; i31++) {
                    double d2;
                    d2 = alpha1_t_data[i31];
                    alpha0_t_data[i31] =
                        -(((l_CoefPS * r9[i31] + n_CoefPS * r11[i31]) + p_CoefPS * d2) + r_CoefPS) /
                        (t_CoefPS * d2 + v_CoefPS);
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r9, r11, alpha1_t_data,
                                 &trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:115' Idx       = find(alpha0_t > 0);
        for (int i19{0}; i19 < alpha0_t_size; i19++) {
            b_alpha0_t_data[i19] = (alpha0_t_data[i19] > 0.0);
        }
        coder::c_eml_find(b_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:116' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:117' alpha0_u  = alpha0_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:119' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:120' status = int32(3);
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:125' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:127' CostInt = zeros(size(alpha0_u));
                CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:128' beta0_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:129' beta1_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:131' for k = 1:length(alpha0_u)
                for (int k{0}; k < Idx_size; k++) {
                    int i33;
                    // 'G2_Hermite_Interpolation_nAxis:133' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:134' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:135' r1D0, t1, n1, D);
                    i33 = Idx_data[k];
                    Calc_beta0_beta1(alpha0_t_data[i33 - 1], alpha1_t_data[i33 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1, &beta0_u_data[k], &beta1_u_data[k]);
                    // 'G2_Hermite_Interpolation_nAxis:136' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:137' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:138' r1D0, t1, n1, D);
                    CostInt_data[k] = EvalCostIntegral(alpha0_t_data[i33 - 1], beta0_u_data[k],
                                                       alpha1_t_data[i33 - 1], beta1_u_data[k],
                                                       r0D0, t0, n0, r1D0, t1, n1);
                }
                int alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:142' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)), &ex,
                                         &iindx);
                // 'G2_Hermite_Interpolation_nAxis:143' alpha0   = alpha0_u(Idx);
                alpha0_tmp = Idx_data[iindx - 1] - 1;
                alpha0 = alpha0_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:144' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:145' beta0    = beta0_u(Idx);
                a = beta0_u_data[iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:146' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:148' else
                // 'G2_Hermite_Interpolation_nAxis:150' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:151' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:152' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:153' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:154' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else if (kappa1 == 0.0) {
        int b_partialTrueCount;
        bool b_unnamed_idx_2;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        // 'G2_Hermite_Interpolation_nAxis:158' elseif kappa1 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:160' Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1
        // - c0*e1 - b0*e0, c1*f0 - c0*e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:162' alpha0_v  = c_roots_(Coef);
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        alpha0_v[0].re = 0.0;
        alpha0_v[0].im = 0.0;
        alpha0_v[1].re = 0.0;
        alpha0_v[1].im = 0.0;
        alpha0_v[2].re = 0.0;
        alpha0_v[2].im = 0.0;
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        dv[0] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
        dv[1] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
        dv[2] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
        dv[3] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
        c_roots(&dv[0], &alpha0_v[0], 4);
        //  all roots of 3th degree polynomial in alpha0
        // 'G2_Hermite_Interpolation_nAxis:163' alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) <
        // TolZero) & (real(alpha0_v) >  0)));
        b_trueCount = 0;
        b_unnamed_idx_2 = (std::abs(alpha0_v[0].im) < 1.0E-11);
        unnamed_idx_0 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[0].re > 0.0)) {
            b_trueCount = 1;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[1].im) < 1.0E-11);
        unnamed_idx_1 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[1].re > 0.0)) {
            b_trueCount++;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[2].im) < 1.0E-11);
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            b_trueCount++;
        }
        b_partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha0_v[0].re > 0.0)) {
            tmp_data[0] = 1;
            b_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha0_v[1].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 2;
            b_partialTrueCount++;
        }
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 3;
        }
        for (int i9{0}; i9 < b_trueCount; i9++) {
            alpha0_t_data[i9] = alpha0_v[tmp_data[i9] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:165' if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:166' alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
            r9.set_size(b_trueCount);
            for (int i12{0}; i12 < b_trueCount; i12++) {
                r9[i12] = std::pow(alpha0_t_data[i12], 2.0);
            }
            if (r9.size(0) == b_trueCount) {
                double e_CoefPS;
                double g_CoefPS;
                double i_CoefPS;
                double k_CoefPS;
                int b_scalarLB;
                int b_vectorUB;
                int h_loop_ub;
                int i26;
                e_CoefPS = CoefPS[1];
                g_CoefPS = CoefPS[3];
                i_CoefPS = CoefPS[7];
                k_CoefPS = CoefPS[6];
                alpha1_t_size = r9.size(0);
                h_loop_ub = r9.size(0);
                b_scalarLB = (r9.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (i26 = 0; i26 <= b_vectorUB; i26 += 2) {
                    __m128d r24;
                    __m128d r27;
                    r24 = _mm_loadu_pd(&r9[i26]);
                    r27 = _mm_loadu_pd(&alpha0_t_data[i26]);
                    _mm_storeu_pd(
                        &alpha1_t_data[i26],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(e_CoefPS), r24),
                                                      _mm_mul_pd(_mm_set1_pd(g_CoefPS), r27)),
                                           _mm_set1_pd(i_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(k_CoefPS)));
                }
                for (i26 = b_scalarLB; i26 < h_loop_ub; i26++) {
                    alpha1_t_data[i26] =
                        -((e_CoefPS * r9[i26] + g_CoefPS * alpha0_t_data[i26]) + i_CoefPS) /
                        k_CoefPS;
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r9, alpha0_t_data,
                                   &b_trueCount);
            }
        } else {
            int i20;
            int i23;
            int i28;
            // 'G2_Hermite_Interpolation_nAxis:167' else
            // 'G2_Hermite_Interpolation_nAxis:168' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            r9.set_size(b_trueCount);
            for (int i14{0}; i14 < b_trueCount; i14++) {
                r9[i14] = std::pow(alpha0_t_data[i14], 3.0);
            }
            r11.set_size(b_trueCount);
            for (int i17{0}; i17 < b_trueCount; i17++) {
                r11[i17] = std::pow(alpha0_t_data[i17], 2.0);
            }
            if (r9.size(0) == 1) {
                i20 = r11.size(0);
            } else {
                i20 = r9.size(0);
            }
            if (r9.size(0) == 1) {
                i23 = r11.size(0);
            } else {
                i23 = r9.size(0);
            }
            if (i23 == 1) {
                i28 = b_trueCount;
            } else if (r9.size(0) == 1) {
                i28 = r11.size(0);
            } else {
                i28 = r9.size(0);
            }
            if ((r9.size(0) == r11.size(0)) && (i20 == b_trueCount) && (i28 == b_trueCount)) {
                double m_CoefPS;
                double o_CoefPS;
                double q_CoefPS;
                double s_CoefPS;
                double u_CoefPS;
                double w_CoefPS;
                int d_scalarLB;
                int d_vectorUB;
                int i32;
                int j_loop_ub;
                m_CoefPS = CoefPS[12];
                o_CoefPS = CoefPS[13];
                q_CoefPS = CoefPS[14];
                s_CoefPS = CoefPS[15];
                u_CoefPS = CoefPS[10];
                w_CoefPS = CoefPS[11];
                alpha1_t_size = r9.size(0);
                j_loop_ub = r9.size(0);
                d_scalarLB = (r9.size(0) / 2) << 1;
                d_vectorUB = d_scalarLB - 2;
                for (i32 = 0; i32 <= d_vectorUB; i32 += 2) {
                    __m128d r35;
                    __m128d r37;
                    __m128d r39;
                    r35 = _mm_loadu_pd(&r9[i32]);
                    r37 = _mm_loadu_pd(&r11[i32]);
                    r39 = _mm_loadu_pd(&alpha0_t_data[i32]);
                    _mm_storeu_pd(
                        &alpha1_t_data[i32],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(m_CoefPS), r35),
                                                          _mm_mul_pd(_mm_set1_pd(o_CoefPS), r37)),
                                               _mm_mul_pd(_mm_set1_pd(q_CoefPS), r39)),
                                    _mm_set1_pd(s_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(u_CoefPS), r39),
                                       _mm_set1_pd(w_CoefPS))));
                }
                for (i32 = d_scalarLB; i32 < j_loop_ub; i32++) {
                    double d3;
                    d3 = alpha0_t_data[i32];
                    alpha1_t_data[i32] =
                        -(((m_CoefPS * r9[i32] + o_CoefPS * r11[i32]) + q_CoefPS * d3) + s_CoefPS) /
                        (u_CoefPS * d3 + w_CoefPS);
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r9, r11, alpha0_t_data,
                                   &b_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:171' Idx      = find(alpha1_t > 0);
        for (int i21{0}; i21 < alpha1_t_size; i21++) {
            b_alpha1_t_data[i21] = (alpha1_t_data[i21] > 0.0);
        }
        coder::c_eml_find(b_alpha1_t_data, alpha1_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:172' alpha1_u = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:173' alpha0_u = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:175' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:176' status = int32(4);
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:181' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int b_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:182' CostInt = zeros(size(alpha0_u));
                b_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:183' beta0_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:184' beta1_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:186' for k = 1:length(alpha0_u)
                for (int b_k{0}; b_k < Idx_size; b_k++) {
                    int i34;
                    // 'G2_Hermite_Interpolation_nAxis:187' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:188' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:189' r1D0, t1, n1, D);
                    i34 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i34 - 1], alpha1_t_data[i34 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1, &beta0_u_data[b_k], &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation_nAxis:190' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:191' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:192' r1D0, t1, n1, D);
                    CostInt_data[b_k] = EvalCostIntegral(alpha0_t_data[i34 - 1], beta0_u_data[b_k],
                                                         alpha1_t_data[i34 - 1], beta1_u_data[b_k],
                                                         r0D0, t0, n0, r1D0, t1, n1);
                }
                int b_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:194' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &b_ex, &b_iindx);
                // 'G2_Hermite_Interpolation_nAxis:195' alpha0   = alpha0_u(Idx);
                b_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                alpha0 = alpha0_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:196' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:197' beta0    = beta0_u(Idx);
                a = beta0_u_data[b_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:198' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:200' else
                // 'G2_Hermite_Interpolation_nAxis:202' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:203' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:204' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:205' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:206' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else {
        double ab_CoefPS;
        double bb_CoefPS;
        double d10;
        double d100;
        double d101;
        double d102;
        double d103;
        double d104;
        double d105;
        double d106;
        double d107;
        double d108;
        double d109;
        double d11;
        double d110;
        double d111;
        double d112;
        double d113;
        double d114;
        double d115;
        double d116;
        double d117;
        double d118;
        double d119;
        double d12;
        double d120;
        double d121;
        double d122;
        double d123;
        double d124;
        double d125;
        double d126;
        double d127;
        double d128;
        double d129;
        double d13;
        double d130;
        double d131;
        double d132;
        double d133;
        double d134;
        double d135;
        double d136;
        double d137;
        double d138;
        double d139;
        double d14;
        double d140;
        double d141;
        double d142;
        double d143;
        double d144;
        double d145;
        double d146;
        double d147;
        double d148;
        double d149;
        double d15;
        double d150;
        double d151;
        double d152;
        double d153;
        double d154;
        double d155;
        double d156;
        double d157;
        double d158;
        double d159;
        double d16;
        double d160;
        double d161;
        double d162;
        double d163;
        double d164;
        double d165;
        double d166;
        double d167;
        double d168;
        double d169;
        double d17;
        double d170;
        double d171;
        double d172;
        double d173;
        double d18;
        double d19;
        double d20;
        double d21;
        double d22;
        double d23;
        double d24;
        double d25;
        double d26;
        double d27;
        double d28;
        double d29;
        double d30;
        double d31;
        double d32;
        double d33;
        double d34;
        double d35;
        double d36;
        double d37;
        double d38;
        double d39;
        double d4;
        double d40;
        double d41;
        double d42;
        double d43;
        double d44;
        double d45;
        double d46;
        double d47;
        double d48;
        double d49;
        double d5;
        double d50;
        double d51;
        double d52;
        double d53;
        double d54;
        double d55;
        double d56;
        double d57;
        double d58;
        double d59;
        double d6;
        double d60;
        double d61;
        double d62;
        double d63;
        double d64;
        double d65;
        double d66;
        double d67;
        double d68;
        double d69;
        double d7;
        double d70;
        double d71;
        double d72;
        double d73;
        double d74;
        double d75;
        double d76;
        double d77;
        double d78;
        double d79;
        double d8;
        double d80;
        double d81;
        double d82;
        double d83;
        double d84;
        double d85;
        double d86;
        double d87;
        double d88;
        double d89;
        double d9;
        double d90;
        double d91;
        double d92;
        double d93;
        double d94;
        double d95;
        double d96;
        double d97;
        double d98;
        double d99;
        double t10;
        double t11;
        double t12;
        double t13;
        double t14;
        double t15;
        double t16;
        double t17;
        double t18;
        double t19;
        double t2;
        double t20;
        double t21;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;
        double x_CoefPS;
        double y_CoefPS;
        int b_t12_size;
        int c_partialTrueCount;
        int d_trueCount;
        int e_trueCount;
        int e_vectorUB;
        int f_trueCount;
        int f_vectorUB;
        int g_trueCount;
        int h_trueCount;
        int i38;
        int i39;
        int i45;
        int i_trueCount;
        int j_trueCount;
        int k_loop_ub;
        int k_trueCount;
        int l_trueCount;
        int m_trueCount;
        int n_trueCount;
        int o_trueCount;
        int p_trueCount;
        int q_trueCount;
        int r_trueCount;
        int s_trueCount;
        int scalarLB_tmp;
        int t_trueCount;
        int u_trueCount;
        int v_trueCount;
        int w_trueCount;
        int x_trueCount;
        // 'G2_Hermite_Interpolation_nAxis:210' else
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:212' Coef = CharPolyAlpha1(CoefPS);
        //
        // 'G2_Hermite_Interpolation_nAxis:214' alpha1_v = c_roots_(Coef);
        // CharPolyAlpha1
        //     Coeff_Poly_Alpha1 = CharPolyAlpha1(IN1)
        //     This function was generated by the Symbolic Math Toolbox version 9.0.
        //     10-Jun-2022 12:36:46
        // 'CharPolyAlpha1:8' CoefPS1_1 = in1(1);
        // 'CharPolyAlpha1:9' CoefPS2_1 = in1(2);
        // 'CharPolyAlpha1:10' CoefPS3_1 = in1(3);
        // 'CharPolyAlpha1:11' CoefPS4_1 = in1(4);
        // 'CharPolyAlpha1:12' CoefPS5_1 = in1(5);
        // 'CharPolyAlpha1:13' CoefPS6_1 = in1(6);
        // 'CharPolyAlpha1:14' CoefPS7_1 = in1(7);
        // 'CharPolyAlpha1:15' CoefPS8_1 = in1(8);
        // 'CharPolyAlpha1:16' CoefPS9_1 = in1(9);
        // 'CharPolyAlpha1:17' CoefPS10_1 = in1(10);
        // 'CharPolyAlpha1:18' CoefPS11_1 = in1(11);
        // 'CharPolyAlpha1:19' CoefPS12_1 = in1(12);
        // 'CharPolyAlpha1:20' CoefPS13_1 = in1(13);
        // 'CharPolyAlpha1:21' CoefPS14_1 = in1(14);
        // 'CharPolyAlpha1:22' CoefPS15_1 = in1(15);
        // 'CharPolyAlpha1:23' CoefPS16_1 = in1(16);
        // 'CharPolyAlpha1:24' t2 = CoefPS1_1.^2;
        t2 = std::pow(CoefPS[0], 2.0);
        // 'CharPolyAlpha1:25' t3 = CoefPS1_1.^3;
        t3 = std::pow(CoefPS[0], 3.0);
        // 'CharPolyAlpha1:26' t4 = CoefPS2_1.^2;
        t4 = std::pow(CoefPS[1], 2.0);
        // 'CharPolyAlpha1:27' t5 = CoefPS2_1.^3;
        t5 = std::pow(CoefPS[1], 3.0);
        // 'CharPolyAlpha1:28' t6 = CoefPS3_1.^2;
        t6 = std::pow(CoefPS[2], 2.0);
        // 'CharPolyAlpha1:29' t7 = CoefPS3_1.^3;
        t7 = std::pow(CoefPS[2], 3.0);
        // 'CharPolyAlpha1:30' t8 = CoefPS4_1.^2;
        t8 = std::pow(CoefPS[3], 2.0);
        // 'CharPolyAlpha1:31' t9 = CoefPS4_1.^3;
        t9 = std::pow(CoefPS[3], 3.0);
        // 'CharPolyAlpha1:32' t10 = CoefPS5_1.^2;
        t10 = std::pow(CoefPS[4], 2.0);
        // 'CharPolyAlpha1:33' t11 = CoefPS6_1.^2;
        t11 = std::pow(CoefPS[5], 2.0);
        // 'CharPolyAlpha1:34' t12 = CoefPS7_1.^2;
        t12 = std::pow(CoefPS[6], 2.0);
        // 'CharPolyAlpha1:35' t13 = CoefPS8_1.^2;
        t13 = std::pow(CoefPS[7], 2.0);
        // 'CharPolyAlpha1:36' t14 = CoefPS9_1.^2;
        t14 = std::pow(CoefPS[8], 2.0);
        // 'CharPolyAlpha1:37' t15 = CoefPS10_1.^2;
        t15 = std::pow(CoefPS[9], 2.0);
        // 'CharPolyAlpha1:38' t16 = CoefPS11_1.^2;
        t16 = std::pow(CoefPS[10], 2.0);
        // 'CharPolyAlpha1:39' t17 = CoefPS12_1.^2;
        t17 = std::pow(CoefPS[11], 2.0);
        // 'CharPolyAlpha1:40' t18 = CoefPS13_1.^2;
        t18 = std::pow(CoefPS[12], 2.0);
        // 'CharPolyAlpha1:41' t19 = CoefPS14_1.^2;
        t19 = std::pow(CoefPS[13], 2.0);
        // 'CharPolyAlpha1:42' t20 = CoefPS15_1.^2;
        t20 = std::pow(CoefPS[14], 2.0);
        // 'CharPolyAlpha1:43' t21 = CoefPS16_1.^2;
        t21 = std::pow(CoefPS[15], 2.0);
        // 'CharPolyAlpha1:44' et1 =
        // CoefPS6_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t3.*2.0+CoefPS2_1.*t2.*t15.*3.0+CoefPS2_1.*t10.*t19+CoefPS6_1.*t2.*t16+CoefPS6_1.*t4.*t14+CoefPS8_1.*t2.*t14+CoefPS8_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS7_1.*t18.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t2-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t10-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1;
        // 'CharPolyAlpha1:45' et2 =
        // CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:46' et3 =
        // t3.*t17-CoefPS10_1.*CoefPS13_1.*t7+CoefPS10_1.*CoefPS16_1.*t3.*2.0+CoefPS1_1.*t4.*t15.*3.0+CoefPS1_1.*t11.*t19+CoefPS5_1.*t4.*t16+CoefPS5_1.*t2.*t20+CoefPS5_1.*t12.*t18.*3.0+CoefPS7_1.*t2.*t16+CoefPS7_1.*t4.*t14+CoefPS7_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS8_1.*t18.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS12_1.*t2.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t2+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t11;
        // 'CharPolyAlpha1:47' et4 =
        // CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1;
        // 'CharPolyAlpha1:48' et5 =
        // CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:49' et6 =
        // t5.*t15-CoefPS12_1.*CoefPS13_1.*t7+CoefPS12_1.*CoefPS16_1.*t3.*2.0+CoefPS2_1.*t2.*t17.*3.0+CoefPS2_1.*t11.*t19+CoefPS6_1.*t4.*t16+CoefPS6_1.*t2.*t20+CoefPS6_1.*t12.*t18.*3.0+CoefPS8_1.*t2.*t16+CoefPS8_1.*t4.*t14+CoefPS8_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t16.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS5_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0+CoefPS1_1.*CoefPS10_1.*CoefPS12_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t4-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS10_1.*CoefPS13_1.*t6.*3.0+CoefPS2_1.*CoefPS10_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t2;
        // 'CharPolyAlpha1:50' et7 =
        // CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t11+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1;
        // 'CharPolyAlpha1:51' et8 =
        // CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0;
        // 'CharPolyAlpha1:52' et9 =
        // CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*-4.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS3_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:53' et10 =
        // t3.*t21+CoefPS7_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t5.*2.0-CoefPS13_1.*CoefPS16_1.*t7+CoefPS1_1.*t4.*t17.*3.0+CoefPS1_1.*t12.*t19+CoefPS5_1.*t4.*t20+CoefPS5_1.*t13.*t18.*3.0+CoefPS7_1.*t4.*t16+CoefPS7_1.*t2.*t20+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t16.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS6_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t4+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS13_1.*t8.*3.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS1_1.*CoefPS10_1.*CoefPS16_1.*t4.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS12_1.*CoefPS13_1.*t6.*3.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t12;
        // 'CharPolyAlpha1:54' et11 =
        // -CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t2+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0;
        // 'CharPolyAlpha1:55' et12 =
        // -CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0;
        // 'CharPolyAlpha1:56' et13 =
        // CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:57' et14 =
        // t5.*t17-CoefPS10_1.*CoefPS13_1.*t9+CoefPS10_1.*CoefPS16_1.*t5.*2.0+CoefPS2_1.*t2.*t21.*3.0+CoefPS2_1.*t12.*t19+CoefPS6_1.*t4.*t20+CoefPS6_1.*t13.*t18.*3.0+CoefPS8_1.*t4.*t16+CoefPS8_1.*t2.*t20+CoefPS8_1.*t12.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t20.*2.0+CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t4+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS12_1.*CoefPS13_1.*t8.*3.0+CoefPS1_1.*CoefPS12_1.*CoefPS16_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t4-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t12+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS16_1.*t6.*3.0;
        // 'CharPolyAlpha1:58' et15 =
        // CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t2-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0;
        // 'CharPolyAlpha1:59' et16 =
        // -CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:60' et17 =
        // -CoefPS12_1.*CoefPS13_1.*t9+CoefPS12_1.*CoefPS16_1.*t5.*2.0+CoefPS1_1.*t4.*t21.*3.0+CoefPS1_1.*t13.*t19+CoefPS7_1.*t4.*t20+CoefPS7_1.*t13.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t20.*2.0+CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t13-CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS16_1.*t8.*3.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1;
        // 'CharPolyAlpha1:61' et18 =
        // CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS4_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0;
        // 'CharPolyAlpha1:62' mt1 =
        // [CoefPS5_1.^3.*t18+CoefPS5_1.*t2.*t14-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0,CoefPS6_1.*t2.*t14+CoefPS6_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t14.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0];
        // 'CharPolyAlpha1:63' mt2 =
        // [t3.*t15+CoefPS1_1.*t10.*t19+CoefPS5_1.*t2.*t16+CoefPS5_1.*t4.*t14+CoefPS5_1.*t11.*t18.*3.0+CoefPS7_1.*t2.*t14+CoefPS7_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t14.*2.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t10+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0,et1+et2,et3+et4+et5,et6+et7+et8+et9,et10+et11+et12+et13,et14+et15+et16,et17+et18];
        // 'CharPolyAlpha1:64' mt3 =
        // [t5.*t21+CoefPS8_1.^3.*t18-CoefPS13_1.*CoefPS16_1.*t9+CoefPS2_1.*t13.*t19+CoefPS8_1.*t4.*t20-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t13+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1];
        // 'CharPolyAlpha1:65' Coeff_Poly_Alpha1 = [mt1,mt2,mt3];
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        d4 = CoefPS[4] * t2;
        d5 = CoefPS[0] * CoefPS[8] * CoefPS[12];
        dv1[0] = (std::pow(CoefPS[4], 3.0) * t18 + d4 * t14) - d5 * t10 * 2.0;
        d6 = CoefPS[0] * CoefPS[1];
        d7 = CoefPS[4] * CoefPS[8];
        d8 = d6 * CoefPS[4];
        d9 = CoefPS[0] * CoefPS[4];
        d10 = d9 * CoefPS[5];
        d11 = CoefPS[5] * t2;
        d12 = CoefPS[1] * CoefPS[8] * CoefPS[12];
        d13 = d7 * CoefPS[10];
        d14 = CoefPS[0] * CoefPS[10] * CoefPS[12];
        dv1[1] =
            (((((d11 * t14 + CoefPS[5] * t10 * t18 * 3.0) + d8 * t14 * 2.0) - d12 * t10 * 2.0) +
              d13 * t2 * 2.0) -
             d14 * t10 * 2.0) -
            d10 * CoefPS[8] * CoefPS[12] * 4.0;
        d15 = CoefPS[0] * CoefPS[2];
        d16 = d15 * CoefPS[4];
        d17 = CoefPS[2] * CoefPS[8];
        d18 = CoefPS[5] * CoefPS[8];
        d19 = d6 * CoefPS[5];
        d20 = d8 * CoefPS[8];
        d21 = CoefPS[1] * CoefPS[4];
        d22 = d9 * CoefPS[6];
        d23 = d21 * CoefPS[5];
        d24 = CoefPS[4] * t4;
        d25 = CoefPS[6] * t2;
        d26 = d17 * CoefPS[9];
        d27 = d18 * CoefPS[10];
        d28 = CoefPS[1] * CoefPS[10] * CoefPS[12];
        d29 = d7 * CoefPS[12];
        d30 = d7 * CoefPS[14];
        d31 = CoefPS[4] * CoefPS[9] * CoefPS[13];
        d32 = CoefPS[0] * CoefPS[12] * CoefPS[14];
        d33 = CoefPS[2] * CoefPS[12];
        d34 = d33 * CoefPS[13];
        dv1[2] = (((((((((((((((((((((t3 * t15 + CoefPS[0] * t10 * t19) + d4 * t16) + d24 * t14) +
                                   CoefPS[4] * t11 * t18 * 3.0) +
                                  d25 * t14) +
                                 CoefPS[6] * t10 * t18 * 3.0) +
                                d19 * t14 * 2.0) -
                               d26 * t2) -
                              d5 * t11 * 2.0) +
                             d27 * t2 * 2.0) -
                            d28 * t10 * 2.0) +
                           d29 * t6) +
                          d30 * t2 * 2.0) -
                         d31 * t2 * 2.0) -
                        d32 * t10 * 2.0) -
                       d34 * t10) +
                      d20 * CoefPS[10] * 4.0) -
                     d16 * CoefPS[8] * CoefPS[13]) +
                    d16 * CoefPS[9] * CoefPS[12] * 3.0) -
                   d22 * CoefPS[8] * CoefPS[12] * 4.0) -
                  d23 * CoefPS[8] * CoefPS[12] * 4.0) -
                 d10 * CoefPS[10] * CoefPS[12] * 4.0;
        d35 = CoefPS[4] * CoefPS[10];
        d36 = d15 * CoefPS[5];
        d37 = CoefPS[0] * CoefPS[3];
        d38 = d37 * CoefPS[4];
        d39 = CoefPS[1] * CoefPS[2];
        d40 = d39 * CoefPS[4];
        d41 = CoefPS[4] * CoefPS[5];
        d42 = CoefPS[3] * CoefPS[8];
        d43 = CoefPS[2] * CoefPS[9];
        d44 = CoefPS[6] * CoefPS[8];
        d45 = d6 * CoefPS[2];
        d46 = d45 * CoefPS[8];
        d47 = d6 * CoefPS[6];
        d48 = d19 * CoefPS[8];
        d49 = CoefPS[2] * CoefPS[3];
        d50 = d49 * CoefPS[4];
        d51 = CoefPS[0] * CoefPS[5];
        d52 = d9 * CoefPS[7];
        d53 = d51 * CoefPS[6];
        d54 = d21 * CoefPS[6];
        d55 = CoefPS[2] * CoefPS[4];
        d56 = CoefPS[1] * t2;
        d57 = CoefPS[5] * t4;
        d58 = CoefPS[7] * t2;
        d59 = d42 * CoefPS[9];
        d60 = d17 * CoefPS[11];
        d61 = d43 * CoefPS[10];
        d62 = d44 * CoefPS[10];
        d63 = d18 * CoefPS[12];
        d64 = d35 * CoefPS[12];
        d65 = d18 * CoefPS[14];
        d66 = CoefPS[5] * CoefPS[9] * CoefPS[13];
        d67 = CoefPS[1] * CoefPS[12] * CoefPS[14];
        d68 = d35 * CoefPS[14];
        d69 = CoefPS[4] * CoefPS[11] * CoefPS[13];
        d70 = CoefPS[3] * CoefPS[12];
        d71 = d70 * CoefPS[13];
        d72 = CoefPS[9] * CoefPS[11];
        dv1[3] = (((((((((((((((((((((((((((((((std::pow(CoefPS[5], 3.0) * t18 + d72 * t3 * 2.0) +
                                               d56 * t15 * 3.0) +
                                              CoefPS[1] * t10 * t19) +
                                             d11 * t16) +
                                            d57 * t14) +
                                           d58 * t14) +
                                          CoefPS[7] * t10 * t18 * 3.0) +
                                         d8 * t16 * 2.0) +
                                        d47 * t14 * 2.0) +
                                       d10 * t19 * 2.0) +
                                      d41 * CoefPS[6] * t18 * 6.0) -
                                     d59 * t2) -
                                    d60 * t2) -
                                   d61 * t2) -
                                  d12 * t11 * 2.0) +
                                 d13 * t4 * 2.0) -
                                d14 * t11 * 2.0) +
                               d62 * t2 * 2.0) +
                              d63 * t6) +
                             d64 * t6) +
                            d65 * t2 * 2.0) -
                           d66 * t2 * 2.0) -
                          d67 * t10 * 2.0) +
                         d68 * t2 * 2.0) -
                        d69 * t2 * 2.0) -
                       d71 * t10) -
                      d46 * CoefPS[9] * 2.0) +
                     d48 * CoefPS[10] * 4.0) +
                    d20 * CoefPS[14] * 4.0) -
                   d8 * CoefPS[9] * CoefPS[13] * 4.0) -
                  d36 * CoefPS[8] * CoefPS[13]) +
                 ((((((((((((((d36 * CoefPS[9] * CoefPS[12] * 3.0 - d38 * CoefPS[8] * CoefPS[13]) +
                              d38 * CoefPS[9] * CoefPS[12] * 3.0) -
                             d40 * CoefPS[8] * CoefPS[13]) +
                            d40 * CoefPS[9] * CoefPS[12] * 3.0) -
                           d16 * CoefPS[10] * CoefPS[13]) +
                          d16 * CoefPS[11] * CoefPS[12] * 3.0) +
                         d50 * CoefPS[8] * CoefPS[12] * 2.0) -
                        d52 * CoefPS[8] * CoefPS[12] * 4.0) -
                       d53 * CoefPS[8] * CoefPS[12] * 4.0) -
                      d54 * CoefPS[8] * CoefPS[12] * 4.0) -
                     d22 * CoefPS[10] * CoefPS[12] * 4.0) -
                    d23 * CoefPS[10] * CoefPS[12] * 4.0) -
                   d10 * CoefPS[12] * CoefPS[14] * 4.0) -
                  d55 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0);
        d73 = CoefPS[5] * CoefPS[10];
        d74 = d15 * CoefPS[6];
        d75 = d37 * CoefPS[5];
        d76 = d39 * CoefPS[5];
        d77 = CoefPS[1] * CoefPS[3];
        d78 = d77 * CoefPS[4];
        d79 = CoefPS[0] * CoefPS[9];
        d80 = CoefPS[1] * CoefPS[9];
        d81 = CoefPS[3] * CoefPS[9];
        d82 = CoefPS[2] * CoefPS[10];
        d83 = CoefPS[7] * CoefPS[8];
        d84 = d6 * CoefPS[3];
        d85 = d84 * CoefPS[8];
        d86 = d45 * CoefPS[9];
        d87 = d6 * CoefPS[7];
        d88 = d47 * CoefPS[8];
        d89 = d49 * CoefPS[5];
        d90 = CoefPS[1] * CoefPS[5];
        d91 = d51 * CoefPS[7];
        d92 = d21 * CoefPS[7];
        d93 = d90 * CoefPS[6];
        d94 = CoefPS[3] * CoefPS[4];
        d95 = CoefPS[0] * t4;
        d96 = CoefPS[6] * t4;
        d97 = d42 * CoefPS[11];
        d98 = d81 * CoefPS[10];
        d99 = d79 * CoefPS[13];
        d100 = d82 * CoefPS[11];
        d101 = d17 * CoefPS[15];
        d102 = d43 * CoefPS[14];
        d103 = d83 * CoefPS[10];
        d104 = d44 * CoefPS[12];
        d105 = d73 * CoefPS[12];
        d106 = d44 * CoefPS[14];
        d107 = CoefPS[6] * CoefPS[9] * CoefPS[13];
        d108 = d73 * CoefPS[14];
        d109 = CoefPS[5] * CoefPS[11] * CoefPS[13];
        d110 = CoefPS[4] * CoefPS[12] * CoefPS[14];
        d111 = CoefPS[4] * CoefPS[13] * CoefPS[15];
        d112 = CoefPS[9] * CoefPS[12];
        d113 = CoefPS[9] * CoefPS[15];
        dv1[4] = (((((((((((((((((((((((((((((((((((t3 * t17 - d112 * t7) + d113 * t3 * 2.0) +
                                                  d95 * t15 * 3.0) +
                                                 CoefPS[0] * t11 * t19) +
                                                d24 * t16) +
                                               d4 * t20) +
                                              CoefPS[4] * t12 * t18 * 3.0) +
                                             d25 * t16) +
                                            d96 * t14) +
                                           CoefPS[6] * t11 * t18 * 3.0) +
                                          d19 * t16 * 2.0) +
                                         d87 * t14 * 2.0) +
                                        d22 * t19 * 2.0) +
                                       d23 * t19 * 2.0) +
                                      d41 * CoefPS[7] * t18 * 6.0) -
                                     d26 * t4) -
                                    d5 * t12 * 2.0) +
                                   d80 * CoefPS[11] * t2 * 6.0) -
                                  d97 * t2) -
                                 d98 * t2) +
                                d99 * t6) -
                               d100 * t2) +
                              d27 * t4 * 2.0) -
                             d28 * t11 * 2.0) +
                            d29 * t8) -
                           d101 * t2) -
                          d102 * t2) +
                         d103 * t2 * 2.0) +
                        d30 * t4 * 2.0) -
                       d31 * t4 * 2.0) +
                      d104 * t6) -
                     d32 * t11 * 2.0) +
                    d105 * t6) -
                   d34 * t11) +
                  ((((((((((((((((((((((((((d106 * t2 * 2.0 - d107 * t2 * 2.0) + d108 * t2 * 2.0) -
                                          d109 * t2 * 2.0) +
                                         d110 * t6) -
                                        d111 * t2 * 2.0) -
                                       d85 * CoefPS[9] * 2.0) -
                                      d46 * CoefPS[11] * 2.0) -
                                     d86 * CoefPS[10] * 2.0) +
                                    d88 * CoefPS[10] * 4.0) +
                                   d48 * CoefPS[14] * 4.0) -
                                  d19 * CoefPS[9] * CoefPS[13] * 4.0) +
                                 d8 * CoefPS[10] * CoefPS[14] * 4.0) -
                                d8 * CoefPS[11] * CoefPS[13] * 4.0) -
                               d74 * CoefPS[8] * CoefPS[13]) +
                              d74 * CoefPS[9] * CoefPS[12] * 3.0) -
                             d75 * CoefPS[8] * CoefPS[13]) +
                            d75 * CoefPS[9] * CoefPS[12] * 3.0) -
                           d76 * CoefPS[8] * CoefPS[13]) +
                          d76 * CoefPS[9] * CoefPS[12] * 3.0) -
                         d78 * CoefPS[8] * CoefPS[13]) +
                        d78 * CoefPS[9] * CoefPS[12] * 3.0) -
                       d36 * CoefPS[10] * CoefPS[13]) +
                      d36 * CoefPS[11] * CoefPS[12] * 3.0) -
                     d38 * CoefPS[10] * CoefPS[13]) +
                    d38 * CoefPS[11] * CoefPS[12] * 3.0) -
                   d40 * CoefPS[10] * CoefPS[13])) +
                 ((((((((((((((d40 * CoefPS[11] * CoefPS[12] * 3.0 +
                               d89 * CoefPS[8] * CoefPS[12] * 2.0) +
                              d50 * CoefPS[10] * CoefPS[12] * 2.0) -
                             d91 * CoefPS[8] * CoefPS[12] * 4.0) -
                            d92 * CoefPS[8] * CoefPS[12] * 4.0) -
                           d93 * CoefPS[8] * CoefPS[12] * 4.0) +
                          d16 * CoefPS[12] * CoefPS[15] * 3.0) -
                         d16 * CoefPS[13] * CoefPS[14]) -
                        d52 * CoefPS[10] * CoefPS[12] * 4.0) -
                       d53 * CoefPS[10] * CoefPS[12] * 4.0) -
                      d54 * CoefPS[10] * CoefPS[12] * 4.0) -
                     d22 * CoefPS[12] * CoefPS[14] * 4.0) -
                    d23 * CoefPS[12] * CoefPS[14] * 4.0) -
                   d55 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) -
                  d94 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0);
        d114 = CoefPS[6] * CoefPS[10];
        d115 = d15 * CoefPS[7];
        d116 = d37 * CoefPS[6];
        d117 = d39 * CoefPS[6];
        d118 = d77 * CoefPS[5];
        d119 = d84 * CoefPS[9];
        d120 = d45 * CoefPS[10];
        d121 = d15 * CoefPS[3];
        d122 = d87 * CoefPS[8];
        d123 = d49 * CoefPS[6];
        d124 = CoefPS[0] * CoefPS[6] * CoefPS[7];
        d125 = d90 * CoefPS[7];
        d126 = CoefPS[2] * CoefPS[5];
        d127 = CoefPS[7] * t4;
        d128 = d80 * CoefPS[13];
        d129 = CoefPS[3] * CoefPS[10];
        d130 = d129 * CoefPS[11];
        d131 = CoefPS[0] * CoefPS[11];
        d132 = d131 * CoefPS[13];
        d133 = CoefPS[2] * CoefPS[11];
        d134 = d42 * CoefPS[15];
        d135 = d81 * CoefPS[14];
        d136 = d82 * CoefPS[15];
        d137 = d133 * CoefPS[14];
        d138 = d83 * CoefPS[12];
        d139 = d114 * CoefPS[12];
        d140 = d83 * CoefPS[14];
        d141 = CoefPS[7] * CoefPS[9] * CoefPS[13];
        d142 = d114 * CoefPS[14];
        d143 = CoefPS[6] * CoefPS[11] * CoefPS[13];
        d144 = CoefPS[5] * CoefPS[12] * CoefPS[14];
        d145 = CoefPS[5] * CoefPS[13] * CoefPS[15];
        d146 = CoefPS[11] * CoefPS[15];
        dv1[5] =
            ((((((((((((((((((((((((((((((((((((t5 * t15 - CoefPS[11] * CoefPS[12] * t7) +
                                               d146 * t3 * 2.0) +
                                              d56 * t17 * 3.0) +
                                             CoefPS[1] * t11 * t19) +
                                            d57 * t16) +
                                           d11 * t20) +
                                          CoefPS[5] * t12 * t18 * 3.0) +
                                         d58 * t16) +
                                        d127 * t14) +
                                       CoefPS[7] * t11 * t18 * 3.0) +
                                      d8 * t20 * 2.0) +
                                     d47 * t16 * 2.0) +
                                    d52 * t19 * 2.0) +
                                   d53 * t19 * 2.0) +
                                  d54 * t19 * 2.0) +
                                 CoefPS[4] * CoefPS[6] * CoefPS[7] * t18 * 6.0) +
                                d79 * CoefPS[11] * t4 * 6.0) -
                               d59 * t4) -
                              d60 * t4) -
                             d61 * t4) -
                            d12 * t12 * 2.0) -
                           d14 * t12 * 2.0) +
                          d128 * t6) -
                         d130 * t2) +
                        d62 * t4 * 2.0) +
                       d132 * t6) -
                      d81 * CoefPS[12] * t6 * 3.0) +
                     d80 * CoefPS[15] * t2 * 6.0) +
                    d63 * t8) -
                   d134 * t2) -
                  d135 * t2) +
                 d64 * t8) -
                d136 * t2) -
               d137 * t2) +
              (((((((((((((((((((((((((((d65 * t4 * 2.0 - d66 * t4 * 2.0) + d138 * t6) -
                                       d67 * t11 * 2.0) +
                                      d68 * t4 * 2.0) -
                                     d69 * t4 * 2.0) +
                                    d139 * t6) -
                                   d71 * t11) +
                                  d140 * t2 * 2.0) -
                                 d141 * t2 * 2.0) +
                                d142 * t2 * 2.0) -
                               d143 * t2 * 2.0) +
                              d144 * t6) -
                             d145 * t2 * 2.0) -
                            d85 * CoefPS[11] * 2.0) -
                           d119 * CoefPS[10] * 2.0) -
                          d120 * CoefPS[11] * 2.0) -
                         d46 * CoefPS[15] * 2.0) -
                        d86 * CoefPS[14] * 2.0) +
                       d122 * CoefPS[10] * 4.0) +
                      d121 * CoefPS[9] * CoefPS[13] * 2.0) +
                     d88 * CoefPS[14] * 4.0) -
                    d47 * CoefPS[9] * CoefPS[13] * 4.0) +
                   d19 * CoefPS[10] * CoefPS[14] * 4.0) -
                  d19 * CoefPS[11] * CoefPS[13] * 4.0) -
                 d115 * CoefPS[8] * CoefPS[13]) +
                d115 * CoefPS[9] * CoefPS[12] * 3.0) -
               d116 * CoefPS[8] * CoefPS[13])) +
             (((((((((((((((((((((((((d116 * CoefPS[9] * CoefPS[12] * 3.0 -
                                      d117 * CoefPS[8] * CoefPS[13]) +
                                     d117 * CoefPS[9] * CoefPS[12] * 3.0) -
                                    d118 * CoefPS[8] * CoefPS[13]) +
                                   d118 * CoefPS[9] * CoefPS[12] * 3.0) -
                                  d74 * CoefPS[10] * CoefPS[13]) +
                                 d74 * CoefPS[11] * CoefPS[12] * 3.0) -
                                d75 * CoefPS[10] * CoefPS[13]) +
                               d75 * CoefPS[11] * CoefPS[12] * 3.0) -
                              d76 * CoefPS[10] * CoefPS[13]) +
                             d76 * CoefPS[11] * CoefPS[12] * 3.0) -
                            d78 * CoefPS[10] * CoefPS[13]) +
                           d78 * CoefPS[11] * CoefPS[12] * 3.0) +
                          d123 * CoefPS[8] * CoefPS[12] * 2.0) +
                         d89 * CoefPS[10] * CoefPS[12] * 2.0) -
                        d8 * CoefPS[13] * CoefPS[15] * 4.0) -
                       d124 * CoefPS[8] * CoefPS[12] * 4.0) -
                      d125 * CoefPS[8] * CoefPS[12] * 4.0) +
                     d36 * CoefPS[12] * CoefPS[15] * 3.0) -
                    d36 * CoefPS[13] * CoefPS[14]) +
                   d38 * CoefPS[12] * CoefPS[15] * 3.0) -
                  d38 * CoefPS[13] * CoefPS[14]) -
                 d91 * CoefPS[10] * CoefPS[12] * 4.0) +
                d40 * CoefPS[12] * CoefPS[15] * 3.0) -
               d40 * CoefPS[13] * CoefPS[14]) -
              d92 * CoefPS[10] * CoefPS[12] * 4.0)) +
            (((((((d93 * CoefPS[10] * CoefPS[12] * -4.0 + d50 * CoefPS[12] * CoefPS[14] * 2.0) -
                  d52 * CoefPS[12] * CoefPS[14] * 4.0) -
                 d53 * CoefPS[12] * CoefPS[14] * 4.0) -
                d54 * CoefPS[12] * CoefPS[14] * 4.0) -
               d55 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) -
              d126 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) -
             d94 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0);
        d147 = CoefPS[1] * CoefPS[11];
        d148 = CoefPS[3] * CoefPS[11];
        d149 = CoefPS[7] * CoefPS[10];
        d150 = d37 * CoefPS[7];
        d151 = d77 * CoefPS[6];
        d152 = d84 * CoefPS[10];
        d153 = d39 * CoefPS[3];
        d154 = d39 * CoefPS[7];
        d155 = d49 * CoefPS[7];
        d156 = -CoefPS[1] * CoefPS[2];
        d157 = CoefPS[1] * CoefPS[6] * CoefPS[7];
        d158 = CoefPS[3] * CoefPS[5];
        d159 = d147 * CoefPS[13];
        d160 = d148 * CoefPS[14];
        d161 = CoefPS[0] * CoefPS[13] * CoefPS[15];
        d162 = d149 * CoefPS[12];
        d163 = CoefPS[2] * CoefPS[14] * CoefPS[15];
        d164 = d149 * CoefPS[14];
        d165 = CoefPS[7] * CoefPS[11] * CoefPS[13];
        d166 = CoefPS[6] * CoefPS[12] * CoefPS[14];
        d167 = CoefPS[6] * CoefPS[13] * CoefPS[15];
        d168 = CoefPS[12] * CoefPS[15];
        dv1[6] =
            (((((((((((((((((((((((((((((((((((t3 * t21 + std::pow(CoefPS[6], 3.0) * t18) +
                                              d72 * t5 * 2.0) -
                                             d168 * t7) +
                                            d95 * t17 * 3.0) +
                                           CoefPS[0] * t12 * t19) +
                                          d24 * t20) +
                                         CoefPS[4] * t13 * t18 * 3.0) +
                                        d96 * t16) +
                                       d25 * t20) +
                                      d19 * t20 * 2.0) +
                                     d87 * t16 * 2.0) +
                                    d91 * t19 * 2.0) +
                                   d92 * t19 * 2.0) +
                                  d93 * t19 * 2.0) +
                                 CoefPS[5] * CoefPS[6] * CoefPS[7] * t18 * 6.0) -
                                d5 * t13 * 2.0) -
                               d97 * t4) -
                              d98 * t4) +
                             d99 * t8) -
                            d100 * t4) -
                           d43 * CoefPS[12] * t8 * 3.0) -
                          d28 * t12 * 2.0) +
                         d79 * CoefPS[15] * t4 * 6.0) -
                        d101 * t4) -
                       d102 * t4) +
                      d103 * t4 * 2.0) +
                     d159 * t6) -
                    d148 * CoefPS[12] * t6 * 3.0) +
                   d104 * t8) -
                  d32 * t12 * 2.0) +
                 d147 * CoefPS[15] * t2 * 6.0) +
                d105 * t8) -
               d34 * t12) +
              (((((((((((((((((((((((((((-CoefPS[3] * CoefPS[10] * CoefPS[15] * t2 - d160 * t2) +
                                        d106 * t4 * 2.0) -
                                       d107 * t4 * 2.0) +
                                      d161 * t6) +
                                     d108 * t4 * 2.0) -
                                    d109 * t4 * 2.0) +
                                   d162 * t6) +
                                  d110 * t8) -
                                 d163 * t2) +
                                d164 * t2 * 2.0) -
                               d165 * t2 * 2.0) -
                              d111 * t4 * 2.0) +
                             d166 * t6) -
                            d167 * t2 * 2.0) -
                           d152 * CoefPS[11] * 2.0) -
                          d85 * CoefPS[15] * 2.0) -
                         d119 * CoefPS[14] * 2.0) -
                        d120 * CoefPS[15] * 2.0) -
                       d45 * CoefPS[11] * CoefPS[14] * 2.0) +
                      d153 * CoefPS[9] * CoefPS[13] * 2.0) +
                     d121 * CoefPS[11] * CoefPS[13] * 2.0) +
                    d122 * CoefPS[14] * 4.0) -
                   d87 * CoefPS[9] * CoefPS[13] * 4.0) +
                  d47 * CoefPS[10] * CoefPS[14] * 4.0) -
                 d47 * CoefPS[11] * CoefPS[13] * 4.0) -
                d150 * CoefPS[8] * CoefPS[13]) +
               d150 * CoefPS[9] * CoefPS[12] * 3.0)) +
             (((((((((((((((((((((((((d156 * CoefPS[7] * CoefPS[8] * CoefPS[13] +
                                      d154 * CoefPS[9] * CoefPS[12] * 3.0) -
                                     d151 * CoefPS[8] * CoefPS[13]) +
                                    d151 * CoefPS[9] * CoefPS[12] * 3.0) -
                                   d115 * CoefPS[10] * CoefPS[13]) +
                                  d115 * CoefPS[11] * CoefPS[12] * 3.0) -
                                 d116 * CoefPS[10] * CoefPS[13]) +
                                d116 * CoefPS[11] * CoefPS[12] * 3.0) -
                               d117 * CoefPS[10] * CoefPS[13]) +
                              d117 * CoefPS[11] * CoefPS[12] * 3.0) -
                             d118 * CoefPS[10] * CoefPS[13]) +
                            d118 * CoefPS[11] * CoefPS[12] * 3.0) +
                           d155 * CoefPS[8] * CoefPS[12] * 2.0) +
                          d123 * CoefPS[10] * CoefPS[12] * 2.0) -
                         d19 * CoefPS[13] * CoefPS[15] * 4.0) -
                        d157 * CoefPS[8] * CoefPS[12] * 4.0) +
                       d74 * CoefPS[12] * CoefPS[15] * 3.0) -
                      d74 * CoefPS[13] * CoefPS[14]) +
                     d75 * CoefPS[12] * CoefPS[15] * 3.0) -
                    d75 * CoefPS[13] * CoefPS[14]) -
                   d124 * CoefPS[10] * CoefPS[12] * 4.0) +
                  d76 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d76 * CoefPS[13] * CoefPS[14]) +
                d78 * CoefPS[12] * CoefPS[15] * 3.0) -
               d78 * CoefPS[13] * CoefPS[14]) -
              d125 * CoefPS[10] * CoefPS[12] * 4.0)) +
            ((((((d89 * CoefPS[12] * CoefPS[14] * 2.0 - d91 * CoefPS[12] * CoefPS[14] * 4.0) -
                 d92 * CoefPS[12] * CoefPS[14] * 4.0) -
                d93 * CoefPS[12] * CoefPS[14] * 4.0) -
               d126 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) -
              d94 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) -
             d158 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0);
        d169 = d77 * CoefPS[7];
        d170 = CoefPS[1] * CoefPS[13] * CoefPS[15];
        d171 = CoefPS[3] * CoefPS[14] * CoefPS[15];
        d172 = CoefPS[7] * CoefPS[12] * CoefPS[14];
        d173 = CoefPS[7] * CoefPS[13] * CoefPS[15];
        dv1[7] = ((((((((((((((((((((((((((((((((((t5 * t17 - d112 * t9) + d113 * t5 * 2.0) +
                                                 d56 * t21 * 3.0) +
                                                CoefPS[1] * t12 * t19) +
                                               d57 * t20) +
                                              CoefPS[5] * t13 * t18 * 3.0) +
                                             d127 * t16) +
                                            d58 * t20) +
                                           CoefPS[7] * t12 * t18 * 3.0) +
                                          d47 * t20 * 2.0) +
                                         d124 * t19 * 2.0) +
                                        d125 * t19 * 2.0) -
                                       d12 * t13 * 2.0) -
                                      d14 * t13 * 2.0) +
                                     d128 * t8) -
                                    d130 * t4) +
                                   d132 * t8) -
                                  d133 * CoefPS[12] * t8 * 3.0) +
                                 d131 * CoefPS[15] * t4 * 6.0) -
                                d134 * t4) -
                               d135 * t4) -
                              d136 * t4) -
                             d137 * t4) +
                            d138 * t8) -
                           d67 * t12 * 2.0) +
                          d139 * t8) -
                         d71 * t12) +
                        d140 * t4 * 2.0) -
                       d141 * t4 * 2.0) +
                      d170 * t6) +
                     d142 * t4 * 2.0) -
                    d143 * t4 * 2.0) -
                   d70 * CoefPS[15] * t6 * 3.0) +
                  ((((((((((((((((((((((((((d144 * t8 - d171 * t2) - d145 * t4 * 2.0) + d172 * t6) -
                                         d173 * t2 * 2.0) -
                                        d152 * CoefPS[15] * 2.0) -
                                       d84 * CoefPS[11] * CoefPS[14] * 2.0) +
                                      d153 * CoefPS[11] * CoefPS[13] * 2.0) -
                                     d45 * CoefPS[14] * CoefPS[15] * 2.0) +
                                    d87 * CoefPS[10] * CoefPS[14] * 4.0) -
                                   d87 * CoefPS[11] * CoefPS[13] * 4.0) -
                                  d169 * CoefPS[8] * CoefPS[13]) +
                                 d169 * CoefPS[9] * CoefPS[12] * 3.0) +
                                d121 * CoefPS[13] * CoefPS[15] * 2.0) -
                               d150 * CoefPS[10] * CoefPS[13]) +
                              d150 * CoefPS[11] * CoefPS[12] * 3.0) -
                             d154 * CoefPS[10] * CoefPS[13]) +
                            d154 * CoefPS[11] * CoefPS[12] * 3.0) -
                           d151 * CoefPS[10] * CoefPS[13]) +
                          d151 * CoefPS[11] * CoefPS[12] * 3.0) +
                         d155 * CoefPS[10] * CoefPS[12] * 2.0) -
                        d47 * CoefPS[13] * CoefPS[15] * 4.0) +
                       d115 * CoefPS[12] * CoefPS[15] * 3.0) -
                      d115 * CoefPS[13] * CoefPS[14]) +
                     d116 * CoefPS[12] * CoefPS[15] * 3.0) -
                    d116 * CoefPS[13] * CoefPS[14]) +
                   d117 * CoefPS[12] * CoefPS[15] * 3.0)) +
                 ((((((((d156 * CoefPS[6] * CoefPS[13] * CoefPS[14] +
                         d118 * CoefPS[12] * CoefPS[15] * 3.0) -
                        d118 * CoefPS[13] * CoefPS[14]) -
                       d157 * CoefPS[10] * CoefPS[12] * 4.0) +
                      d123 * CoefPS[12] * CoefPS[14] * 2.0) -
                     d124 * CoefPS[12] * CoefPS[14] * 4.0) -
                    d125 * CoefPS[12] * CoefPS[14] * 4.0) -
                   CoefPS[2] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) -
                  d158 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0);
        dv1[8] = ((((((((((((((((((((((((((((((-CoefPS[11] * CoefPS[12] * t9 + d146 * t5 * 2.0) +
                                              d95 * t21 * 3.0) +
                                             CoefPS[0] * t13 * t19) +
                                            d96 * t20) +
                                           CoefPS[6] * t13 * t18 * 3.0) +
                                          d87 * t20 * 2.0) +
                                         d157 * t19 * 2.0) -
                                        d28 * t13 * 2.0) +
                                       d159 * t8) -
                                      d32 * t13 * 2.0) -
                                     d34 * t13) -
                                    d129 * CoefPS[15] * t4) -
                                   d160 * t4) +
                                  d161 * t8) -
                                 d33 * CoefPS[15] * t8 * 3.0) +
                                d162 * t8) -
                               d163 * t4) +
                              d164 * t4 * 2.0) -
                             d165 * t4 * 2.0) +
                            d166 * t8) -
                           d167 * t4 * 2.0) -
                          d84 * CoefPS[14] * CoefPS[15] * 2.0) +
                         d153 * CoefPS[13] * CoefPS[15] * 2.0) -
                        d169 * CoefPS[10] * CoefPS[13]) +
                       d169 * CoefPS[11] * CoefPS[12] * 3.0) -
                      d87 * CoefPS[13] * CoefPS[15] * 4.0) +
                     d150 * CoefPS[12] * CoefPS[15] * 3.0) -
                    d150 * CoefPS[13] * CoefPS[14]) +
                   d154 * CoefPS[12] * CoefPS[15] * 3.0) -
                  d154 * CoefPS[13] * CoefPS[14]) +
                 ((((d151 * CoefPS[12] * CoefPS[15] * 3.0 - d151 * CoefPS[13] * CoefPS[14]) +
                    d155 * CoefPS[12] * CoefPS[14] * 2.0) -
                   d157 * CoefPS[12] * CoefPS[14] * 4.0) -
                  CoefPS[3] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0);
        dv1[9] = (((((((((((t5 * t21 + std::pow(CoefPS[7], 3.0) * t18) - d168 * t9) +
                          CoefPS[1] * t13 * t19) +
                         d127 * t20) -
                        d67 * t13 * 2.0) -
                       d71 * t13) +
                      d170 * t8) -
                     d171 * t4) +
                    d172 * t8) -
                   d173 * t4 * 2.0) +
                  d169 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d169 * CoefPS[13] * CoefPS[14];
        for (int i35{0}; i35 < 10; i35++) {
            dv2[i35] = dv1[9 - i35];
        }
        c_roots(&dv2[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:215' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int c_k{0}; c_k < 9; c_k++) {
            double d174;
            bool g_b;
            g_b = (std::abs(b_alpha1_v[c_k].im) < 1.0E-11);
            d174 = b_alpha1_v[c_k].re;
            if (g_b && (d174 > 0.0)) {
                c_trueCount++;
                alpha1_t_data[c_partialTrueCount] = d174;
                c_partialTrueCount++;
            }
        }
        //  retain only positive real roots
        //  compute corresponding values of alpha0
        // 'G2_Hermite_Interpolation_nAxis:218' alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
        // CalcAlpha0
        //     ALPHA0_S = CalcAlpha0(ALPHA1,IN2)
        //     This function was generated by the Symbolic Math Toolbox version 9.0.
        //     10-Jun-2022 12:36:50
        // 'CalcAlpha0:8' a0 = in2(:,2);
        // 'CalcAlpha0:9' a1 = in2(:,1);
        // 'CalcAlpha0:10' b0 = in2(:,4);
        // 'CalcAlpha0:11' b1 = in2(:,3);
        // 'CalcAlpha0:12' c0 = in2(:,8);
        // 'CalcAlpha0:13' c1 = in2(:,7);
        // 'CalcAlpha0:14' c2 = in2(:,6);
        // 'CalcAlpha0:15' c3 = in2(:,5);
        // 'CalcAlpha0:16' d0 = in2(:,10);
        // 'CalcAlpha0:17' d1 = in2(:,9);
        // 'CalcAlpha0:18' e0 = in2(:,12);
        // 'CalcAlpha0:19' e1 = in2(:,11);
        // 'CalcAlpha0:20' f0 = in2(:,16);
        // 'CalcAlpha0:21' f1 = in2(:,15);
        // 'CalcAlpha0:22' f2 = in2(:,14);
        // 'CalcAlpha0:23' f3 = in2(:,13);
        // 'CalcAlpha0:24' t2 = a1.*alpha1;
        // 'CalcAlpha0:25' t3 = alpha1.*b1;
        // 'CalcAlpha0:26' t4 = alpha1.*c1;
        // 'CalcAlpha0:27' t5 = alpha1.^2;
        r9.set_size(c_trueCount);
        for (int i36{0}; i36 < c_trueCount; i36++) {
            r9[i36] = std::pow(alpha1_t_data[i36], 2.0);
        }
        t5_size = r9.size(0);
        k_loop_ub = r9.size(0);
        for (int i37{0}; i37 < k_loop_ub; i37++) {
            t5_data[i37] = r9[i37];
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        x_CoefPS = CoefPS[3];
        y_CoefPS = CoefPS[2];
        scalarLB_tmp = (c_trueCount / 2) << 1;
        e_vectorUB = scalarLB_tmp - 2;
        for (i38 = 0; i38 <= e_vectorUB; i38 += 2) {
            __m128d r40;
            r40 = _mm_loadu_pd(&alpha1_t_data[i38]);
            _mm_storeu_pd(&t10_data[i38], _mm_add_pd(_mm_set1_pd(x_CoefPS),
                                                     _mm_mul_pd(r40, _mm_set1_pd(y_CoefPS))));
        }
        for (i38 = scalarLB_tmp; i38 < c_trueCount; i38++) {
            t10_data[i38] = x_CoefPS + alpha1_t_data[i38] * y_CoefPS;
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        ab_CoefPS = CoefPS[1];
        bb_CoefPS = CoefPS[0];
        f_vectorUB = scalarLB_tmp - 2;
        for (i39 = 0; i39 <= f_vectorUB; i39 += 2) {
            __m128d r41;
            r41 = _mm_loadu_pd(&alpha1_t_data[i39]);
            _mm_storeu_pd(
                &t11_data[i39],
                _mm_div_pd(_mm_set1_pd(1.0), _mm_add_pd(_mm_set1_pd(ab_CoefPS),
                                                        _mm_mul_pd(_mm_set1_pd(bb_CoefPS), r41))));
        }
        for (i39 = scalarLB_tmp; i39 < c_trueCount; i39++) {
            t11_data[i39] = 1.0 / (ab_CoefPS + bb_CoefPS * alpha1_t_data[i39]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        r9.set_size(c_trueCount);
        for (int i40{0}; i40 < c_trueCount; i40++) {
            r9[i40] = std::pow(alpha1_t_data[i40], 2.0);
        }
        r11.set_size(c_trueCount);
        for (int i41{0}; i41 < c_trueCount; i41++) {
            r11[i41] = std::pow(alpha1_t_data[i41], 3.0);
        }
        if (c_trueCount == 1) {
            d_trueCount = r9.size(0);
        } else {
            d_trueCount = c_trueCount;
        }
        if ((c_trueCount == r9.size(0)) && (d_trueCount == r11.size(0))) {
            double cb_CoefPS;
            double db_CoefPS;
            double eb_CoefPS;
            double fb_CoefPS;
            int g_vectorUB;
            int i43;
            cb_CoefPS = CoefPS[7];
            db_CoefPS = CoefPS[6];
            eb_CoefPS = CoefPS[5];
            fb_CoefPS = CoefPS[4];
            t12_size = c_trueCount;
            g_vectorUB = scalarLB_tmp - 2;
            for (i43 = 0; i43 <= g_vectorUB; i43 += 2) {
                __m128d r42;
                __m128d r43;
                __m128d r44;
                r42 = _mm_loadu_pd(&alpha1_t_data[i43]);
                r43 = _mm_loadu_pd(&r9[i43]);
                r44 = _mm_loadu_pd(&r11[i43]);
                _mm_storeu_pd(
                    &t12_data[i43],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_set1_pd(cb_CoefPS),
                                                     _mm_mul_pd(r42, _mm_set1_pd(db_CoefPS))),
                                          _mm_mul_pd(_mm_set1_pd(eb_CoefPS), r43)),
                               _mm_mul_pd(_mm_set1_pd(fb_CoefPS), r44)));
            }
            for (i43 = scalarLB_tmp; i43 < c_trueCount; i43++) {
                t12_data[i43] =
                    ((cb_CoefPS + alpha1_t_data[i43] * db_CoefPS) + eb_CoefPS * r9[i43]) +
                    fb_CoefPS * r11[i43];
            }
        } else {
            binary_expand_op(t12_data, &t12_size, CoefPS, alpha1_t_data, &c_trueCount, r9, r11);
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        r9.set_size(c_trueCount);
        for (int i42{0}; i42 < c_trueCount; i42++) {
            r9[i42] = std::pow(t11_data[i42], 2.0);
        }
        r11.set_size(c_trueCount);
        for (int i44{0}; i44 < c_trueCount; i44++) {
            r11[i44] = std::pow(t10_data[i44], 2.0);
        }
        if (c_trueCount == 1) {
            e_trueCount = t5_size;
            f_trueCount = t12_size;
            g_trueCount = r9.size(0);
            h_trueCount = t5_size;
        } else {
            e_trueCount = c_trueCount;
            f_trueCount = c_trueCount;
            g_trueCount = c_trueCount;
            h_trueCount = c_trueCount;
        }
        if (h_trueCount == 1) {
            if (c_trueCount == 1) {
                i_trueCount = t12_size;
            } else {
                i_trueCount = c_trueCount;
            }
        } else if (c_trueCount == 1) {
            i_trueCount = t5_size;
        } else {
            i_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            j_trueCount = r9.size(0);
        } else {
            j_trueCount = c_trueCount;
        }
        if (j_trueCount == 1) {
            k_trueCount = t12_size;
        } else if (c_trueCount == 1) {
            k_trueCount = r9.size(0);
        } else {
            k_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            l_trueCount = t5_size;
        } else {
            l_trueCount = c_trueCount;
        }
        if (r11.size(0) == 1) {
            i45 = c_trueCount;
        } else {
            i45 = r11.size(0);
        }
        if (t12_size == 1) {
            if (r11.size(0) == 1) {
                b_t12_size = c_trueCount;
            } else {
                b_t12_size = r11.size(0);
            }
        } else {
            b_t12_size = t12_size;
        }
        if (c_trueCount == 1) {
            m_trueCount = t5_size;
        } else {
            m_trueCount = c_trueCount;
        }
        if (m_trueCount == 1) {
            n_trueCount = c_trueCount;
        } else if (c_trueCount == 1) {
            n_trueCount = t5_size;
        } else {
            n_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            if (t12_size == 1) {
                if (r11.size(0) == 1) {
                    o_trueCount = c_trueCount;
                } else {
                    o_trueCount = r11.size(0);
                }
            } else {
                o_trueCount = t12_size;
            }
            p_trueCount = t5_size;
        } else {
            o_trueCount = c_trueCount;
            p_trueCount = c_trueCount;
        }
        if (p_trueCount == 1) {
            if (c_trueCount == 1) {
                q_trueCount = t12_size;
            } else {
                q_trueCount = c_trueCount;
            }
        } else if (c_trueCount == 1) {
            q_trueCount = t5_size;
        } else {
            q_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            r_trueCount = r9.size(0);
            s_trueCount = t5_size;
        } else {
            r_trueCount = c_trueCount;
            s_trueCount = c_trueCount;
        }
        if (q_trueCount == 1) {
            if (r_trueCount == 1) {
                t_trueCount = t12_size;
            } else if (c_trueCount == 1) {
                t_trueCount = r9.size(0);
            } else {
                t_trueCount = c_trueCount;
            }
        } else if (s_trueCount == 1) {
            if (c_trueCount == 1) {
                t_trueCount = t12_size;
            } else {
                t_trueCount = c_trueCount;
            }
        } else if (c_trueCount == 1) {
            t_trueCount = t5_size;
        } else {
            t_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            u_trueCount = t5_size;
        } else {
            u_trueCount = c_trueCount;
        }
        if (u_trueCount == 1) {
            v_trueCount = c_trueCount;
        } else if (c_trueCount == 1) {
            v_trueCount = t5_size;
        } else {
            v_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            w_trueCount = t5_size;
        } else {
            w_trueCount = c_trueCount;
        }
        if (v_trueCount == 1) {
            if (c_trueCount == 1) {
                if (t12_size == 1) {
                    if (r11.size(0) == 1) {
                        x_trueCount = c_trueCount;
                    } else {
                        x_trueCount = r11.size(0);
                    }
                } else {
                    x_trueCount = t12_size;
                }
            } else {
                x_trueCount = c_trueCount;
            }
        } else if (w_trueCount == 1) {
            x_trueCount = c_trueCount;
        } else if (c_trueCount == 1) {
            x_trueCount = t5_size;
        } else {
            x_trueCount = c_trueCount;
        }
        if ((c_trueCount == t5_size) && (c_trueCount == t12_size) && (e_trueCount == f_trueCount) &&
            (c_trueCount == r9.size(0)) && (g_trueCount == t12_size) &&
            (i_trueCount == k_trueCount) && (c_trueCount == t5_size) &&
            (l_trueCount == c_trueCount) && (r11.size(0) == c_trueCount) && (t12_size == i45) &&
            (c_trueCount == b_t12_size) && (n_trueCount == o_trueCount) &&
            (t_trueCount == x_trueCount)) {
            double gb_CoefPS;
            double hb_CoefPS;
            double ib_CoefPS;
            double jb_CoefPS;
            double kb_CoefPS;
            double lb_CoefPS;
            double mb_CoefPS;
            double nb_CoefPS;
            double ob_CoefPS;
            double pb_CoefPS;
            int h_vectorUB;
            int i47;
            gb_CoefPS = CoefPS[15];
            hb_CoefPS = CoefPS[11];
            ib_CoefPS = CoefPS[9];
            jb_CoefPS = CoefPS[13];
            kb_CoefPS = CoefPS[12];
            lb_CoefPS = CoefPS[14];
            mb_CoefPS = CoefPS[10];
            nb_CoefPS = CoefPS[8];
            ob_CoefPS = CoefPS[13];
            pb_CoefPS = CoefPS[12];
            alpha0_t_size = c_trueCount;
            h_vectorUB = scalarLB_tmp - 2;
            for (i47 = 0; i47 <= h_vectorUB; i47 += 2) {
                __m128d r45;
                __m128d r46;
                __m128d r47;
                __m128d r48;
                __m128d r49;
                __m128d r50;
                __m128d r51;
                r45 = _mm_loadu_pd(&alpha1_t_data[i47]);
                r46 = _mm_loadu_pd(&t5_data[i47]);
                r47 = _mm_loadu_pd(&t11_data[i47]);
                r48 = _mm_loadu_pd(&t12_data[i47]);
                r49 = _mm_loadu_pd(&t10_data[i47]);
                r50 = _mm_loadu_pd(&r9[i47]);
                r51 = _mm_loadu_pd(&r11[i47]);
                _mm_storeu_pd(
                    &alpha0_t_data[i47],
                    _mm_div_pd(
                        _mm_mul_pd(
                            _mm_add_pd(
                                _mm_sub_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_set1_pd(gb_CoefPS),
                                                          _mm_mul_pd(r45, _mm_set1_pd(hb_CoefPS))),
                                               _mm_mul_pd(_mm_set1_pd(ib_CoefPS), r46)),
                                    _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jb_CoefPS), r47), r48)),
                                _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(kb_CoefPS), r49), r50),
                                           r48)),
                            _mm_set1_pd(-1.0)),
                        _mm_sub_pd(
                            _mm_sub_pd(
                                _mm_add_pd(_mm_add_pd(_mm_set1_pd(lb_CoefPS),
                                                      _mm_mul_pd(r45, _mm_set1_pd(mb_CoefPS))),
                                           _mm_mul_pd(_mm_set1_pd(nb_CoefPS), r46)),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(ob_CoefPS), r49), r47)),
                            _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(pb_CoefPS), r47),
                                       _mm_sub_pd(r48, _mm_mul_pd(r51, r47))))));
            }
            for (i47 = scalarLB_tmp; i47 < c_trueCount; i47++) {
                double d175;
                double d176;
                double d177;
                double d178;
                double d179;
                d175 = alpha1_t_data[i47];
                d176 = t5_data[i47];
                d177 = t11_data[i47];
                d178 = t12_data[i47];
                d179 = t10_data[i47];
                alpha0_t_data[i47] = -((((gb_CoefPS + d175 * hb_CoefPS) + ib_CoefPS * d176) -
                                        jb_CoefPS * d177 * d178) +
                                       kb_CoefPS * d179 * r9[i47] * d178) /
                                     ((((lb_CoefPS + d175 * mb_CoefPS) + nb_CoefPS * d176) -
                                       ob_CoefPS * d179 * d177) -
                                      pb_CoefPS * d177 * (d178 - r11[i47] * d177));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &c_trueCount,
                             t5_data, &t5_size, t11_data, &c_trueCount, t12_data, &t12_size,
                             t10_data, &c_trueCount, r9, r11);
        }
        //
        // 'G2_Hermite_Interpolation_nAxis:220' Idx       = find(alpha0_t > 0);
        for (int i46{0}; i46 < alpha0_t_size; i46++) {
            c_alpha0_t_data[i46] = (alpha0_t_data[i46] > 0.0);
        }
        coder::c_eml_find(c_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:221' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:222' alpha0_u  = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:224' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:225' status = int32(5);
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:230' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int c_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:232' CostInt = zeros(size(alpha0_u));
                c_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:233' beta0_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:234' beta1_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:236' for k = 1:length(alpha0_u)
                for (int d_k{0}; d_k < Idx_size; d_k++) {
                    int i48;
                    // 'G2_Hermite_Interpolation_nAxis:238' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:239' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:240' r1D0, t1, n1, D);
                    i48 = Idx_data[d_k];
                    Calc_beta0_beta1(alpha0_t_data[i48 - 1], alpha1_t_data[i48 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1, &beta0_u_data[d_k], &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation_nAxis:241' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:242' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:243' r1D0, t1, n1, D);
                    CostInt_data[d_k] = EvalCostIntegral(alpha0_t_data[i48 - 1], beta0_u_data[d_k],
                                                         alpha1_t_data[i48 - 1], beta1_u_data[d_k],
                                                         r0D0, t0, n0, r1D0, t1, n1);
                }
                int c_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:247' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &c_ex, &c_iindx);
                // 'G2_Hermite_Interpolation_nAxis:248' alpha0   = alpha0_u(Idx);
                c_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                alpha0 = alpha0_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:249' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:250' beta0    = beta0_u(Idx);
                a = beta0_u_data[c_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:251' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:253' else
                // 'G2_Hermite_Interpolation_nAxis:255' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:256' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:257' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:258' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:259' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1, &a, &b_a);
            }
            guard1 = true;
        }
    }
    if (guard1) {
        __m128d r;
        __m128d r10;
        __m128d r23;
        __m128d r26;
        double a_tmp;
        double b_a_tmp;
        //
        //  Hermite basis
        // 'G2_Hermite_Interpolation_nAxis:266' h00 = [-6,    15,   -10,     0,     0,     1];
        // 'G2_Hermite_Interpolation_nAxis:267' h10 = [-3,     8,    -6,     0,     1,     0];
        // 'G2_Hermite_Interpolation_nAxis:268' h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
        // 'G2_Hermite_Interpolation_nAxis:269' h01 = [6,   -15,     10,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:270' h11 = [-3,    7,     -4,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:271' h21 = [0.5,  -1,    0.5,     0,     0,     0];
        //  evaluate coefficients as sum of basis functions
        // 'G2_Hermite_Interpolation_nAxis:273' p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 +
        // alpha0^2*n0) * h20 + ... 'G2_Hermite_Interpolation_nAxis:274'      r1D0 * h01 + alpha1*t1
        // * h11 + (beta1*t1 + alpha1^2*n1) * h21;
        a_tmp = alpha0 * alpha0;
        b_a_tmp = alpha1 * alpha1;
        r = _mm_set1_pd(alpha0);
        for (int i6{0}; i6 < 6; i6++) {
            __m128d r2;
            __m128d r5;
            __m128d r7;
            __m128d r8;
            int i10;
            int i8;
            r2 = _mm_loadu_pd(&r0D0[0]);
            i8 = b[i6];
            r5 = _mm_set1_pd(static_cast<double>(i8));
            _mm_storeu_pd(&b_r0D0[i6][0], _mm_mul_pd(r2, r5));
            r7 = _mm_loadu_pd(&t0[0]);
            i10 = b_b[i6];
            r8 = _mm_set1_pd(static_cast<double>(i10));
            _mm_storeu_pd(&b_alpha0[i6][0], _mm_mul_pd(_mm_mul_pd(r, r7), r8));
            r2 = _mm_loadu_pd(&r0D0[2]);
            _mm_storeu_pd(&b_r0D0[i6][2], _mm_mul_pd(r2, r5));
            r7 = _mm_loadu_pd(&t0[2]);
            _mm_storeu_pd(&b_alpha0[i6][2], _mm_mul_pd(_mm_mul_pd(r, r7), r8));
            b_r0D0[i6][4] = r0D0[4] * static_cast<double>(i8);
            b_alpha0[i6][4] = alpha0 * t0[4] * static_cast<double>(i10);
        }
        __m128d r1;
        __m128d r3;
        __m128d r4;
        __m128d r6;
        r1 = _mm_loadu_pd(&t0[0]);
        r3 = _mm_loadu_pd(&n0[0]);
        r4 = _mm_set1_pd(a);
        r6 = _mm_set1_pd(a_tmp);
        _mm_storeu_pd(&c_a[0], _mm_add_pd(_mm_mul_pd(r4, r1), _mm_mul_pd(r6, r3)));
        r1 = _mm_loadu_pd(&t0[2]);
        r3 = _mm_loadu_pd(&n0[2]);
        _mm_storeu_pd(&c_a[2], _mm_add_pd(_mm_mul_pd(r4, r1), _mm_mul_pd(r6, r3)));
        c_a[4] = a * t0[4] + a_tmp * n0[4];
        r10 = _mm_set1_pd(0.0);
        for (int i15{0}; i15 < 6; i15++) {
            __m128d r13;
            __m128d r15;
            __m128d r17;
            __m128d r19;
            __m128d r20;
            __m128d r21;
            double d;
            int i25;
            r13 = _mm_loadu_pd(&c_a[0]);
            r15 = _mm_loadu_pd(&b_r0D0[i15][0]);
            r17 = _mm_loadu_pd(&b_alpha0[i15][0]);
            d = c_b[i15];
            r19 = _mm_set1_pd(d);
            _mm_storeu_pd(&c_r0D0[i15][0],
                          _mm_add_pd(_mm_add_pd(r15, r17), _mm_add_pd(r10, _mm_mul_pd(r13, r19))));
            r20 = _mm_loadu_pd(&r1D0[0]);
            i25 = d_b[i15];
            r21 = _mm_set1_pd(static_cast<double>(i25));
            _mm_storeu_pd(&b_r1D0[i15][0], _mm_mul_pd(r20, r21));
            r13 = _mm_loadu_pd(&c_a[2]);
            r15 = _mm_loadu_pd(&b_r0D0[i15][2]);
            r17 = _mm_loadu_pd(&b_alpha0[i15][2]);
            _mm_storeu_pd(&c_r0D0[i15][2],
                          _mm_add_pd(_mm_add_pd(r15, r17), _mm_add_pd(r10, _mm_mul_pd(r13, r19))));
            r20 = _mm_loadu_pd(&r1D0[2]);
            _mm_storeu_pd(&b_r1D0[i15][2], _mm_mul_pd(r20, r21));
            c_r0D0[i15][4] = (b_r0D0[i15][4] + b_alpha0[i15][4]) + c_a[4] * d;
            b_r1D0[i15][4] = r1D0[4] * static_cast<double>(i25);
        }
        __m128d r12;
        __m128d r14;
        __m128d r16;
        __m128d r18;
        r12 = _mm_loadu_pd(&t1[0]);
        r14 = _mm_loadu_pd(&n1[0]);
        r16 = _mm_set1_pd(b_a);
        r18 = _mm_set1_pd(b_a_tmp);
        _mm_storeu_pd(&c_a[0], _mm_add_pd(_mm_mul_pd(r16, r12), _mm_mul_pd(r18, r14)));
        r12 = _mm_loadu_pd(&t1[2]);
        r14 = _mm_loadu_pd(&n1[2]);
        _mm_storeu_pd(&c_a[2], _mm_add_pd(_mm_mul_pd(r16, r12), _mm_mul_pd(r18, r14)));
        c_a[4] = b_a * t1[4] + b_a_tmp * n1[4];
        r23 = _mm_set1_pd(alpha1);
        r26 = _mm_set1_pd(0.0);
        for (int i29{0}; i29 < 6; i29++) {
            __m128d r28;
            __m128d r29;
            __m128d r30;
            __m128d r31;
            __m128d r32;
            __m128d r33;
            double d1;
            int i30;
            r28 = _mm_loadu_pd(&t1[0]);
            r29 = _mm_loadu_pd(&c_r0D0[i29][0]);
            r30 = _mm_loadu_pd(&b_r1D0[i29][0]);
            r31 = _mm_loadu_pd(&c_a[0]);
            i30 = e_b[i29];
            r32 = _mm_set1_pd(static_cast<double>(i30));
            d1 = f_b[i29];
            r33 = _mm_set1_pd(d1);
            _mm_storeu_pd(
                &p5[i29][0],
                _mm_add_pd(_mm_add_pd(_mm_add_pd(r29, r30),
                                      _mm_add_pd(r26, _mm_mul_pd(_mm_mul_pd(r23, r28), r32))),
                           _mm_mul_pd(r31, r33)));
            r28 = _mm_loadu_pd(&t1[2]);
            r29 = _mm_loadu_pd(&c_r0D0[i29][2]);
            r30 = _mm_loadu_pd(&b_r1D0[i29][2]);
            r31 = _mm_loadu_pd(&c_a[2]);
            _mm_storeu_pd(
                &p5[i29][2],
                _mm_add_pd(_mm_add_pd(_mm_add_pd(r29, r30),
                                      _mm_add_pd(r26, _mm_mul_pd(_mm_mul_pd(r23, r28), r32))),
                           _mm_mul_pd(r31, r33)));
            p5[i29][4] =
                ((c_r0D0[i29][4] + b_r1D0[i29][4]) + alpha1 * t1[4] * static_cast<double>(i30)) +
                c_a[4] * d1;
        }
        //  last cross check ...
        // 'G2_Hermite_Interpolation_nAxis:276' p1val = (a1*alpha1+a0)*alpha0^2  +
        // (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
        // 'G2_Hermite_Interpolation_nAxis:277' p2val = (d1*alpha0+d0)*alpha1^2  +
        // (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        // 'G2_Hermite_Interpolation_nAxis:279' if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
        if ((std::abs((((((CoefPS[0] * alpha1 + CoefPS[1]) * a_tmp +
                          (CoefPS[2] * alpha1 + CoefPS[3]) * alpha0) +
                         CoefPS[4] * std::pow(alpha1, 3.0)) +
                        CoefPS[5] * b_a_tmp) +
                       CoefPS[6] * alpha1) +
                      CoefPS[7]) >= 1.0E-7) ||
            (std::abs((((((CoefPS[8] * alpha0 + CoefPS[9]) * b_a_tmp +
                          (CoefPS[10] * alpha0 + CoefPS[11]) * alpha1) +
                         CoefPS[12] * std::pow(alpha0, 3.0)) +
                        CoefPS[13] * a_tmp) +
                       CoefPS[14] * alpha0) +
                      CoefPS[15]) >= 1.0E-7)) {
            // 'G2_Hermite_Interpolation_nAxis:280' status = int32(6);
            *status = 6;
        }
    }
}

} // namespace ocn

//
// File trailer for G2_Hermite_Interpolation_nAxis.cpp
//
// [EOF]
//
