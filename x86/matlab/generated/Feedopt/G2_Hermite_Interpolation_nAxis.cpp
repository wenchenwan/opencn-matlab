//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation_nAxis.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "G2_Hermite_Interpolation_nAxis.h"
#include "CalcAlpha0.h"
#include "Calc_beta0_beta1.h"
#include "CharPolyAlpha1.h"
#include "CoefPolySys.h"
#include "EvalCostIntegral.h"
#include "calc_t_nk_kappa.h"
#include "div.h"
#include "find.h"
#include "minOrMax.h"
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
//                const ::coder::array<double, 1U> &ctx_cfg_D
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
    int ctx_cfg_NumberAxis, const ::coder::array<double, 1U> &ctx_cfg_D,
    const ::coder::array<double, 1U> &r0D0_in, const ::coder::array<double, 1U> &r0D1_in,
    const ::coder::array<double, 1U> &r0D2_in, const ::coder::array<double, 1U> &r1D0_in,
    const ::coder::array<double, 1U> &r1D1_in, const ::coder::array<double, 1U> &r1D2_in,
    double p5[6][5], int *status)
{
    static const double d_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double g_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b_b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char c_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char e_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char f_b[6]{-3, 7, -4, 0, 0, 0};
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> r9;
    ::coder::array<double, 1U> z;
    creal_T b_alpha1_v[9];
    creal_T alpha0_v[3];
    creal_T alpha1_v[3];
    double b_alpha0[6][5];
    double b_r0D0[6][5];
    double b_r1D0[6][5];
    double c_r0D0[6][5];
    double CoefPS[16];
    double dv[10];
    double dv1[10];
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
    double A[2][2];
    double dv2[4];
    double B[2];
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
    // 'G2_Hermite_Interpolation_nAxis:44' D = ctx.cfg.D;
    // 'G2_Hermite_Interpolation_nAxis:46' status = int32(1);
    *status = 1;
    //  default success
    // 'G2_Hermite_Interpolation_nAxis:48' p5 = zeros(5,6);
    std::memset(&p5[0][0], 0, 30U * sizeof(double));
    // 'G2_Hermite_Interpolation_nAxis:50' alpha0 = 0;
    // 'G2_Hermite_Interpolation_nAxis:51' alpha1 = 0;
    //  compute Frenet frame
    // 'G2_Hermite_Interpolation_nAxis:54' [t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
    calc_t_nk_kappa(r0D1, r0D2, t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation_nAxis:55' [t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);
    calc_t_nk_kappa(r1D1, r1D2, t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    // 'G2_Hermite_Interpolation_nAxis:63' CoefPS = CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D);
    CoefPolySys(r0D0, t0, n0, r1D0, t1, n1,
                (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(), CoefPS);
    //
    // 'G2_Hermite_Interpolation_nAxis:65' a1     = CoefPS(1);
    // 'G2_Hermite_Interpolation_nAxis:66' a0     = CoefPS(2);
    // 'G2_Hermite_Interpolation_nAxis:67' b1     = CoefPS(3);
    // 'G2_Hermite_Interpolation_nAxis:68' b0     = CoefPS(4);
    // 'G2_Hermite_Interpolation_nAxis:69' c3     = CoefPS(5);
    // 'G2_Hermite_Interpolation_nAxis:70' c2     = CoefPS(6);
    // 'G2_Hermite_Interpolation_nAxis:71' c1     = CoefPS(7);
    // 'G2_Hermite_Interpolation_nAxis:72' c0     = CoefPS(8);
    // 'G2_Hermite_Interpolation_nAxis:73' d1     = CoefPS(9);
    // 'G2_Hermite_Interpolation_nAxis:74' d0     = CoefPS(10);
    // 'G2_Hermite_Interpolation_nAxis:75' e1     = CoefPS(11);
    // 'G2_Hermite_Interpolation_nAxis:76' e0     = CoefPS(12);
    // 'G2_Hermite_Interpolation_nAxis:77' f3     = CoefPS(13);
    // 'G2_Hermite_Interpolation_nAxis:78' f2     = CoefPS(14);
    // 'G2_Hermite_Interpolation_nAxis:79' f1     = CoefPS(15);
    // 'G2_Hermite_Interpolation_nAxis:80' f0     = CoefPS(16);
    // 'G2_Hermite_Interpolation_nAxis:81' TolZero = 1e-11;
    //
    // 'G2_Hermite_Interpolation_nAxis:83' if (kappa0 == 0) && (kappa1 == 0)
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        double X_idx_0;
        double X_idx_1;
        double a21;
        int r1;
        int r2;
        //  degenerated case where the polynomial system degenerates to a linear one
        // 'G2_Hermite_Interpolation_nAxis:84' M       = [b0, c1;
        // 'G2_Hermite_Interpolation_nAxis:85'                f1, e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:87' B       = [-c0;
        // 'G2_Hermite_Interpolation_nAxis:88'                -f0];
        //
        // 'G2_Hermite_Interpolation_nAxis:90' X       = M \ B;
        A[0][0] = CoefPS[3];
        A[1][0] = CoefPS[6];
        A[0][1] = CoefPS[14];
        A[1][1] = CoefPS[11];
        B[0] = -CoefPS[7];
        B[1] = -CoefPS[15];
        if (std::abs(CoefPS[14]) > std::abs(CoefPS[3])) {
            r1 = 1;
            r2 = 0;
        } else {
            r1 = 0;
            r2 = 1;
        }
        a21 = A[0][r2] / A[0][r1];
        X_idx_1 = (B[r2] - B[r1] * a21) / (A[1][r2] - a21 * A[1][r1]);
        X_idx_0 = (B[r1] - X_idx_1 * A[1][r1]) / A[0][r1];
        //  resolution of linear system
        // 'G2_Hermite_Interpolation_nAxis:91' alpha0  = X(1);
        alpha0 = X_idx_0;
        // 'G2_Hermite_Interpolation_nAxis:92' alpha1  = X(2);
        alpha1 = X_idx_1;
        // 'G2_Hermite_Interpolation_nAxis:94' if ~((alpha0 > 0) && (alpha1 > 0))
        if ((X_idx_0 > 0.0) && (X_idx_1 > 0.0)) {
            // 'G2_Hermite_Interpolation_nAxis:98' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1,
            // ... 'G2_Hermite_Interpolation_nAxis:99'                                       r0D0,
            // t0, n0, ... 'G2_Hermite_Interpolation_nAxis:100' r1D0, t1, n1, D);
            Calc_beta0_beta1(X_idx_0, X_idx_1, r0D0, t0, n0, r1D0, t1, n1,
                             (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(), &a,
                             &b_a);
            guard1 = true;
        }
    } else if (kappa0 == 0.0) {
        int b_partialTrueCount;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        bool unnamed_idx_2;
        // 'G2_Hermite_Interpolation_nAxis:101' elseif kappa0 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:103' Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0
        // + b1*f0 - c1*f1, b0*f0 - c0*f1];
        //
        // 'G2_Hermite_Interpolation_nAxis:105' alpha1_v = c_roots_(Coef);
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
        dv2[0] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
        dv2[1] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
        dv2[2] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
        dv2[3] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
        c_roots(&dv2[0], &alpha1_v[0], 4);
        //  all roots of 3th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:106' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        b_trueCount = 0;
        unnamed_idx_2 = (std::abs(alpha1_v[0].im) < 1.0E-11);
        unnamed_idx_0 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[0].re > 0.0)) {
            b_trueCount = 1;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[1].im) < 1.0E-11);
        unnamed_idx_1 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[1].re > 0.0)) {
            b_trueCount++;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[2].im) < 1.0E-11);
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            b_trueCount++;
        }
        b_partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha1_v[0].re > 0.0)) {
            tmp_data[0] = 1;
            b_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha1_v[1].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 2;
            b_partialTrueCount++;
        }
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 3;
        }
        for (int i7{0}; i7 < b_trueCount; i7++) {
            alpha1_t_data[i7] = alpha1_v[tmp_data[i7] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:108' if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:109' alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
            r3.set_size(b_trueCount);
            for (int i11{0}; i11 < b_trueCount; i11++) {
                r3[i11] = std::pow(alpha1_t_data[i11], 2.0);
            }
            if (r3.size(0) == b_trueCount) {
                double b_CoefPS;
                double d_CoefPS;
                double f_CoefPS;
                double h_CoefPS;
                int h_loop_ub;
                int i27;
                int scalarLB;
                int vectorUB;
                b_CoefPS = CoefPS[9];
                d_CoefPS = CoefPS[11];
                f_CoefPS = CoefPS[15];
                h_CoefPS = CoefPS[14];
                alpha0_t_size = r3.size(0);
                h_loop_ub = r3.size(0);
                scalarLB = (r3.size(0) / 2) << 1;
                vectorUB = scalarLB - 2;
                for (i27 = 0; i27 <= vectorUB; i27 += 2) {
                    __m128d r18;
                    __m128d r21;
                    r18 = _mm_loadu_pd(&r3[i27]);
                    r21 = _mm_loadu_pd(&alpha1_t_data[i27]);
                    _mm_storeu_pd(
                        &alpha0_t_data[i27],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(b_CoefPS), r18),
                                                      _mm_mul_pd(_mm_set1_pd(d_CoefPS), r21)),
                                           _mm_set1_pd(f_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(h_CoefPS)));
                }
                for (i27 = scalarLB; i27 < h_loop_ub; i27++) {
                    alpha0_t_data[i27] =
                        -((b_CoefPS * r3[i27] + d_CoefPS * alpha1_t_data[i27]) + f_CoefPS) /
                        h_CoefPS;
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r3, alpha1_t_data,
                                 &b_trueCount);
            }
        } else {
            int i20;
            int i25;
            int i29;
            // 'G2_Hermite_Interpolation_nAxis:110' else
            // 'G2_Hermite_Interpolation_nAxis:111' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            r3.set_size(b_trueCount);
            for (int i14{0}; i14 < b_trueCount; i14++) {
                r3[i14] = std::pow(alpha1_t_data[i14], 3.0);
            }
            r9.set_size(b_trueCount);
            for (int i17{0}; i17 < b_trueCount; i17++) {
                r9[i17] = std::pow(alpha1_t_data[i17], 2.0);
            }
            if (r3.size(0) == 1) {
                i20 = r9.size(0);
            } else {
                i20 = r3.size(0);
            }
            if (r3.size(0) == 1) {
                i25 = r9.size(0);
            } else {
                i25 = r3.size(0);
            }
            if (i25 == 1) {
                i29 = b_trueCount;
            } else if (r3.size(0) == 1) {
                i29 = r9.size(0);
            } else {
                i29 = r3.size(0);
            }
            if ((r3.size(0) == r9.size(0)) && (i20 == b_trueCount) && (i29 == b_trueCount)) {
                double l_CoefPS;
                double n_CoefPS;
                double p_CoefPS;
                double r_CoefPS;
                double t_CoefPS;
                double w_CoefPS;
                int e_scalarLB;
                int e_vectorUB;
                int i35;
                int j_loop_ub;
                l_CoefPS = CoefPS[4];
                n_CoefPS = CoefPS[5];
                p_CoefPS = CoefPS[6];
                r_CoefPS = CoefPS[7];
                t_CoefPS = CoefPS[2];
                w_CoefPS = CoefPS[3];
                alpha0_t_size = r3.size(0);
                j_loop_ub = r3.size(0);
                e_scalarLB = (r3.size(0) / 2) << 1;
                e_vectorUB = e_scalarLB - 2;
                for (i35 = 0; i35 <= e_vectorUB; i35 += 2) {
                    __m128d r34;
                    __m128d r37;
                    __m128d r39;
                    r34 = _mm_loadu_pd(&r3[i35]);
                    r37 = _mm_loadu_pd(&r9[i35]);
                    r39 = _mm_loadu_pd(&alpha1_t_data[i35]);
                    _mm_storeu_pd(
                        &alpha0_t_data[i35],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(l_CoefPS), r34),
                                                          _mm_mul_pd(_mm_set1_pd(n_CoefPS), r37)),
                                               _mm_mul_pd(_mm_set1_pd(p_CoefPS), r39)),
                                    _mm_set1_pd(r_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t_CoefPS), r39),
                                       _mm_set1_pd(w_CoefPS))));
                }
                for (i35 = e_scalarLB; i35 < j_loop_ub; i35++) {
                    double d3;
                    d3 = alpha1_t_data[i35];
                    alpha0_t_data[i35] =
                        -(((l_CoefPS * r3[i35] + n_CoefPS * r9[i35]) + p_CoefPS * d3) + r_CoefPS) /
                        (t_CoefPS * d3 + w_CoefPS);
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r3, r9, alpha1_t_data,
                                 &b_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:114' Idx       = find(alpha0_t > 0);
        for (int i21{0}; i21 < alpha0_t_size; i21++) {
            b_alpha0_t_data[i21] = (alpha0_t_data[i21] > 0.0);
        }
        coder::c_eml_find(b_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:115' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:116' alpha0_u  = alpha0_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:118' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:119' status = int32(3);
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:124' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:126' CostInt = zeros(size(alpha0_u));
                CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:127' beta0_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:128' beta1_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:130' for k = 1:length(alpha0_u)
                for (int b_k{0}; b_k < Idx_size; b_k++) {
                    int i39;
                    // 'G2_Hermite_Interpolation_nAxis:132' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:133' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:134' r1D0, t1, n1, D);
                    i39 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i39 - 1], alpha1_t_data[i39 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1,
                                     (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(),
                                     &beta0_u_data[b_k], &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation_nAxis:135' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:136' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:137' r1D0, t1, n1, D);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[i39 - 1], beta0_u_data[b_k], alpha1_t_data[i39 - 1],
                        beta1_u_data[b_k], r0D0, t0, n0, r1D0, t1, n1,
                        (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data());
                }
                int alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:141' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)), &ex,
                                         &iindx);
                // 'G2_Hermite_Interpolation_nAxis:142' alpha0   = alpha0_u(Idx);
                alpha0_tmp = Idx_data[iindx - 1] - 1;
                alpha0 = alpha0_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:143' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:144' beta0    = beta0_u(Idx);
                a = beta0_u_data[iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:145' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:147' else
                // 'G2_Hermite_Interpolation_nAxis:149' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:150' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:151' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:152' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:153' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1,
                                 (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(), &a,
                                 &b_a);
            }
            //
            guard1 = true;
        }
    } else if (kappa1 == 0.0) {
        int c_partialTrueCount;
        bool b_unnamed_idx_2;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        // 'G2_Hermite_Interpolation_nAxis:157' elseif kappa1 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:159' Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1
        // - c0*e1 - b0*e0, c1*f0 - c0*e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:161' alpha0_v  = c_roots_(Coef);
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
        dv2[0] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
        dv2[1] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
        dv2[2] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
        dv2[3] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
        c_roots(&dv2[0], &alpha0_v[0], 4);
        //  all roots of 3th degree polynomial in alpha0
        // 'G2_Hermite_Interpolation_nAxis:162' alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) <
        // TolZero) & (real(alpha0_v) >  0)));
        c_trueCount = 0;
        b_unnamed_idx_2 = (std::abs(alpha0_v[0].im) < 1.0E-11);
        unnamed_idx_0 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[0].re > 0.0)) {
            c_trueCount = 1;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[1].im) < 1.0E-11);
        unnamed_idx_1 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[1].re > 0.0)) {
            c_trueCount++;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[2].im) < 1.0E-11);
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            c_trueCount++;
        }
        c_partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha0_v[0].re > 0.0)) {
            tmp_data[0] = 1;
            c_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha0_v[1].re > 0.0)) {
            tmp_data[c_partialTrueCount] = 2;
            c_partialTrueCount++;
        }
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            tmp_data[c_partialTrueCount] = 3;
        }
        for (int i8{0}; i8 < c_trueCount; i8++) {
            alpha0_t_data[i8] = alpha0_v[tmp_data[i8] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:164' if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:165' alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
            r3.set_size(c_trueCount);
            for (int i13{0}; i13 < c_trueCount; i13++) {
                r3[i13] = std::pow(alpha0_t_data[i13], 2.0);
            }
            if (r3.size(0) == c_trueCount) {
                double c_CoefPS;
                double e_CoefPS;
                double g_CoefPS;
                double i_CoefPS;
                int b_scalarLB;
                int b_vectorUB;
                int i28;
                int i_loop_ub;
                c_CoefPS = CoefPS[1];
                e_CoefPS = CoefPS[3];
                g_CoefPS = CoefPS[7];
                i_CoefPS = CoefPS[6];
                alpha1_t_size = r3.size(0);
                i_loop_ub = r3.size(0);
                b_scalarLB = (r3.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (i28 = 0; i28 <= b_vectorUB; i28 += 2) {
                    __m128d r20;
                    __m128d r23;
                    r20 = _mm_loadu_pd(&r3[i28]);
                    r23 = _mm_loadu_pd(&alpha0_t_data[i28]);
                    _mm_storeu_pd(
                        &alpha1_t_data[i28],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(c_CoefPS), r20),
                                                      _mm_mul_pd(_mm_set1_pd(e_CoefPS), r23)),
                                           _mm_set1_pd(g_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(i_CoefPS)));
                }
                for (i28 = b_scalarLB; i28 < i_loop_ub; i28++) {
                    alpha1_t_data[i28] =
                        -((c_CoefPS * r3[i28] + e_CoefPS * alpha0_t_data[i28]) + g_CoefPS) /
                        i_CoefPS;
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r3, alpha0_t_data,
                                   &c_trueCount);
            }
        } else {
            int i22;
            int i26;
            int i30;
            // 'G2_Hermite_Interpolation_nAxis:166' else
            // 'G2_Hermite_Interpolation_nAxis:167' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            r3.set_size(c_trueCount);
            for (int i15{0}; i15 < c_trueCount; i15++) {
                r3[i15] = std::pow(alpha0_t_data[i15], 3.0);
            }
            r9.set_size(c_trueCount);
            for (int i19{0}; i19 < c_trueCount; i19++) {
                r9[i19] = std::pow(alpha0_t_data[i19], 2.0);
            }
            if (r3.size(0) == 1) {
                i22 = r9.size(0);
            } else {
                i22 = r3.size(0);
            }
            if (r3.size(0) == 1) {
                i26 = r9.size(0);
            } else {
                i26 = r3.size(0);
            }
            if (i26 == 1) {
                i30 = c_trueCount;
            } else if (r3.size(0) == 1) {
                i30 = r9.size(0);
            } else {
                i30 = r3.size(0);
            }
            if ((r3.size(0) == r9.size(0)) && (i22 == c_trueCount) && (i30 == c_trueCount)) {
                double m_CoefPS;
                double o_CoefPS;
                double q_CoefPS;
                double s_CoefPS;
                double v_CoefPS;
                double y_CoefPS;
                int f_scalarLB;
                int f_vectorUB;
                int i36;
                int k_loop_ub;
                m_CoefPS = CoefPS[12];
                o_CoefPS = CoefPS[13];
                q_CoefPS = CoefPS[14];
                s_CoefPS = CoefPS[15];
                v_CoefPS = CoefPS[10];
                y_CoefPS = CoefPS[11];
                alpha1_t_size = r3.size(0);
                k_loop_ub = r3.size(0);
                f_scalarLB = (r3.size(0) / 2) << 1;
                f_vectorUB = f_scalarLB - 2;
                for (i36 = 0; i36 <= f_vectorUB; i36 += 2) {
                    __m128d r36;
                    __m128d r38;
                    __m128d r41;
                    r36 = _mm_loadu_pd(&r3[i36]);
                    r38 = _mm_loadu_pd(&r9[i36]);
                    r41 = _mm_loadu_pd(&alpha0_t_data[i36]);
                    _mm_storeu_pd(
                        &alpha1_t_data[i36],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(m_CoefPS), r36),
                                                          _mm_mul_pd(_mm_set1_pd(o_CoefPS), r38)),
                                               _mm_mul_pd(_mm_set1_pd(q_CoefPS), r41)),
                                    _mm_set1_pd(s_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(v_CoefPS), r41),
                                       _mm_set1_pd(y_CoefPS))));
                }
                for (i36 = f_scalarLB; i36 < k_loop_ub; i36++) {
                    double d4;
                    d4 = alpha0_t_data[i36];
                    alpha1_t_data[i36] =
                        -(((m_CoefPS * r3[i36] + o_CoefPS * r9[i36]) + q_CoefPS * d4) + s_CoefPS) /
                        (v_CoefPS * d4 + y_CoefPS);
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r3, r9, alpha0_t_data,
                                   &c_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:170' Idx      = find(alpha1_t > 0);
        for (int i23{0}; i23 < alpha1_t_size; i23++) {
            b_alpha1_t_data[i23] = (alpha1_t_data[i23] > 0.0);
        }
        coder::c_eml_find(b_alpha1_t_data, alpha1_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:171' alpha1_u = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:172' alpha0_u = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:174' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:175' status = int32(4);
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:180' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int b_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:181' CostInt = zeros(size(alpha0_u));
                b_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:182' beta0_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:183' beta1_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:185' for k = 1:length(alpha0_u)
                for (int c_k{0}; c_k < Idx_size; c_k++) {
                    int i40;
                    // 'G2_Hermite_Interpolation_nAxis:186' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:187' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:188' r1D0, t1, n1, D);
                    i40 = Idx_data[c_k];
                    Calc_beta0_beta1(alpha0_t_data[i40 - 1], alpha1_t_data[i40 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1,
                                     (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(),
                                     &beta0_u_data[c_k], &beta1_u_data[c_k]);
                    // 'G2_Hermite_Interpolation_nAxis:189' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:190' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:191' r1D0, t1, n1, D);
                    CostInt_data[c_k] = EvalCostIntegral(
                        alpha0_t_data[i40 - 1], beta0_u_data[c_k], alpha1_t_data[i40 - 1],
                        beta1_u_data[c_k], r0D0, t0, n0, r1D0, t1, n1,
                        (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data());
                }
                int b_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:193' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &b_ex, &b_iindx);
                // 'G2_Hermite_Interpolation_nAxis:194' alpha0   = alpha0_u(Idx);
                b_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                alpha0 = alpha0_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:195' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:196' beta0    = beta0_u(Idx);
                a = beta0_u_data[b_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:197' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:199' else
                // 'G2_Hermite_Interpolation_nAxis:201' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:202' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:203' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:204' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:205' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1,
                                 (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(), &a,
                                 &b_a);
            }
            //
            guard1 = true;
        }
    } else {
        double ab_CoefPS;
        double bb_CoefPS;
        double j_CoefPS;
        double k_CoefPS;
        double u_CoefPS;
        double x_CoefPS;
        int b_t12_size;
        int c_scalarLB;
        int c_vectorUB;
        int d_scalarLB;
        int d_trueCount;
        int d_vectorUB;
        int e_trueCount;
        int f_trueCount;
        int g_loop_ub;
        int g_scalarLB;
        int g_trueCount;
        int g_vectorUB;
        int h_trueCount;
        int i31;
        int i34;
        int i38;
        int i46;
        int i47;
        int i_trueCount;
        int j_trueCount;
        int k_trueCount;
        int l_trueCount;
        int m_trueCount;
        int n_trueCount;
        int o_trueCount;
        int p_trueCount;
        int partialTrueCount;
        int q_trueCount;
        int r_trueCount;
        int s_trueCount;
        int t_trueCount;
        int u_trueCount;
        int v_trueCount;
        int w_trueCount;
        int x_trueCount;
        // 'G2_Hermite_Interpolation_nAxis:209' else
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:211' Coef = CharPolyAlpha1(CoefPS);
        //
        // 'G2_Hermite_Interpolation_nAxis:213' alpha1_v = c_roots_(Coef);
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        CharPolyAlpha1(CoefPS, dv);
        for (int i6{0}; i6 < 10; i6++) {
            dv1[i6] = dv[9 - i6];
        }
        c_roots(&dv1[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:214' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        trueCount = 0;
        partialTrueCount = 0;
        for (int k{0}; k < 9; k++) {
            double d;
            bool b;
            b = (std::abs(b_alpha1_v[k].im) < 1.0E-11);
            d = b_alpha1_v[k].re;
            if (b && (d > 0.0)) {
                trueCount++;
                alpha1_t_data[partialTrueCount] = d;
                partialTrueCount++;
            }
        }
        //  retain only positive real roots
        //  compute corresponding values of alpha0
        // 'G2_Hermite_Interpolation_nAxis:217' alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
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
        r3.set_size(trueCount);
        for (int i12{0}; i12 < trueCount; i12++) {
            r3[i12] = std::pow(alpha1_t_data[i12], 2.0);
        }
        t5_size = r3.size(0);
        g_loop_ub = r3.size(0);
        for (int i18{0}; i18 < g_loop_ub; i18++) {
            t5_data[i18] = r3[i18];
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        j_CoefPS = CoefPS[3];
        k_CoefPS = CoefPS[2];
        c_scalarLB = (trueCount / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i31 = 0; i31 <= c_vectorUB; i31 += 2) {
            __m128d r25;
            r25 = _mm_loadu_pd(&alpha1_t_data[i31]);
            _mm_storeu_pd(&t10_data[i31], _mm_add_pd(_mm_set1_pd(j_CoefPS),
                                                     _mm_mul_pd(r25, _mm_set1_pd(k_CoefPS))));
        }
        for (i31 = c_scalarLB; i31 < trueCount; i31++) {
            t10_data[i31] = j_CoefPS + alpha1_t_data[i31] * k_CoefPS;
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        u_CoefPS = CoefPS[1];
        x_CoefPS = CoefPS[0];
        z.set_size(trueCount);
        d_scalarLB = (trueCount / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i34 = 0; i34 <= d_vectorUB; i34 += 2) {
            __m128d r33;
            r33 = _mm_loadu_pd(&alpha1_t_data[i34]);
            _mm_storeu_pd(&z[i34], _mm_div_pd(_mm_set1_pd(1.0),
                                              _mm_add_pd(_mm_set1_pd(u_CoefPS),
                                                         _mm_mul_pd(_mm_set1_pd(x_CoefPS), r33))));
        }
        for (i34 = d_scalarLB; i34 < trueCount; i34++) {
            z[i34] = 1.0 / (u_CoefPS + x_CoefPS * alpha1_t_data[i34]);
        }
        ab_CoefPS = CoefPS[1];
        bb_CoefPS = CoefPS[0];
        g_scalarLB = (trueCount / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (i38 = 0; i38 <= g_vectorUB; i38 += 2) {
            __m128d r42;
            r42 = _mm_loadu_pd(&alpha1_t_data[i38]);
            _mm_storeu_pd(
                &t11_data[i38],
                _mm_div_pd(_mm_set1_pd(1.0), _mm_add_pd(_mm_set1_pd(ab_CoefPS),
                                                        _mm_mul_pd(_mm_set1_pd(bb_CoefPS), r42))));
        }
        for (i38 = g_scalarLB; i38 < trueCount; i38++) {
            t11_data[i38] = 1.0 / (ab_CoefPS + bb_CoefPS * alpha1_t_data[i38]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        r3.set_size(trueCount);
        for (int i41{0}; i41 < trueCount; i41++) {
            r3[i41] = std::pow(alpha1_t_data[i41], 2.0);
        }
        r9.set_size(trueCount);
        for (int i42{0}; i42 < trueCount; i42++) {
            r9[i42] = std::pow(alpha1_t_data[i42], 3.0);
        }
        if (trueCount == 1) {
            d_trueCount = r3.size(0);
        } else {
            d_trueCount = trueCount;
        }
        if ((trueCount == r3.size(0)) && (d_trueCount == r9.size(0))) {
            double cb_CoefPS;
            double db_CoefPS;
            double eb_CoefPS;
            double fb_CoefPS;
            int h_scalarLB;
            int h_vectorUB;
            int i45;
            cb_CoefPS = CoefPS[7];
            db_CoefPS = CoefPS[6];
            eb_CoefPS = CoefPS[5];
            fb_CoefPS = CoefPS[4];
            t12_size = trueCount;
            h_scalarLB = (trueCount / 2) << 1;
            h_vectorUB = h_scalarLB - 2;
            for (i45 = 0; i45 <= h_vectorUB; i45 += 2) {
                __m128d r43;
                __m128d r44;
                __m128d r45;
                r43 = _mm_loadu_pd(&alpha1_t_data[i45]);
                r44 = _mm_loadu_pd(&r3[i45]);
                r45 = _mm_loadu_pd(&r9[i45]);
                _mm_storeu_pd(
                    &t12_data[i45],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_set1_pd(cb_CoefPS),
                                                     _mm_mul_pd(r43, _mm_set1_pd(db_CoefPS))),
                                          _mm_mul_pd(_mm_set1_pd(eb_CoefPS), r44)),
                               _mm_mul_pd(_mm_set1_pd(fb_CoefPS), r45)));
            }
            for (i45 = h_scalarLB; i45 < trueCount; i45++) {
                t12_data[i45] =
                    ((cb_CoefPS + alpha1_t_data[i45] * db_CoefPS) + eb_CoefPS * r3[i45]) +
                    fb_CoefPS * r9[i45];
            }
        } else {
            binary_expand_op(t12_data, &t12_size, CoefPS, alpha1_t_data, &trueCount, r3, r9);
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        r3.set_size(trueCount);
        for (int i43{0}; i43 < trueCount; i43++) {
            r3[i43] = std::pow(t11_data[i43], 2.0);
        }
        r9.set_size(trueCount);
        for (int i44{0}; i44 < trueCount; i44++) {
            r9[i44] = std::pow(t10_data[i44], 2.0);
        }
        if (trueCount == 1) {
            e_trueCount = t5_size;
            f_trueCount = t12_size;
            g_trueCount = r3.size(0);
            h_trueCount = t5_size;
        } else {
            e_trueCount = trueCount;
            f_trueCount = trueCount;
            g_trueCount = trueCount;
            h_trueCount = trueCount;
        }
        if (h_trueCount == 1) {
            if (trueCount == 1) {
                i_trueCount = t12_size;
            } else {
                i_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            i_trueCount = t5_size;
        } else {
            i_trueCount = trueCount;
        }
        if (trueCount == 1) {
            j_trueCount = r3.size(0);
        } else {
            j_trueCount = trueCount;
        }
        if (j_trueCount == 1) {
            k_trueCount = t12_size;
        } else if (trueCount == 1) {
            k_trueCount = r3.size(0);
        } else {
            k_trueCount = trueCount;
        }
        if (trueCount == 1) {
            l_trueCount = t5_size;
            m_trueCount = z.size(0);
        } else {
            l_trueCount = trueCount;
            m_trueCount = trueCount;
        }
        if (r9.size(0) == 1) {
            i46 = trueCount;
        } else {
            i46 = r9.size(0);
        }
        if (t12_size == 1) {
            if (r9.size(0) == 1) {
                b_t12_size = trueCount;
            } else {
                b_t12_size = r9.size(0);
            }
        } else {
            b_t12_size = t12_size;
        }
        if (trueCount == 1) {
            n_trueCount = t5_size;
        } else {
            n_trueCount = trueCount;
        }
        if (n_trueCount == 1) {
            if (trueCount == 1) {
                o_trueCount = z.size(0);
            } else {
                o_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            o_trueCount = t5_size;
        } else {
            o_trueCount = trueCount;
        }
        if (z.size(0) == 1) {
            if (t12_size == 1) {
                if (r9.size(0) == 1) {
                    i47 = trueCount;
                } else {
                    i47 = r9.size(0);
                }
            } else {
                i47 = t12_size;
            }
        } else {
            i47 = z.size(0);
        }
        if (trueCount == 1) {
            p_trueCount = t5_size;
        } else {
            p_trueCount = trueCount;
        }
        if (p_trueCount == 1) {
            if (trueCount == 1) {
                q_trueCount = t12_size;
            } else {
                q_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            q_trueCount = t5_size;
        } else {
            q_trueCount = trueCount;
        }
        if (trueCount == 1) {
            r_trueCount = r3.size(0);
            s_trueCount = t5_size;
        } else {
            r_trueCount = trueCount;
            s_trueCount = trueCount;
        }
        if (q_trueCount == 1) {
            if (r_trueCount == 1) {
                t_trueCount = t12_size;
            } else if (trueCount == 1) {
                t_trueCount = r3.size(0);
            } else {
                t_trueCount = trueCount;
            }
        } else if (s_trueCount == 1) {
            if (trueCount == 1) {
                t_trueCount = t12_size;
            } else {
                t_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            t_trueCount = t5_size;
        } else {
            t_trueCount = trueCount;
        }
        if (trueCount == 1) {
            u_trueCount = t5_size;
        } else {
            u_trueCount = trueCount;
        }
        if (u_trueCount == 1) {
            if (trueCount == 1) {
                v_trueCount = z.size(0);
            } else {
                v_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            v_trueCount = t5_size;
        } else {
            v_trueCount = trueCount;
        }
        if (trueCount == 1) {
            w_trueCount = t5_size;
        } else {
            w_trueCount = trueCount;
        }
        if (v_trueCount == 1) {
            if (z.size(0) == 1) {
                if (t12_size == 1) {
                    if (r9.size(0) == 1) {
                        x_trueCount = trueCount;
                    } else {
                        x_trueCount = r9.size(0);
                    }
                } else {
                    x_trueCount = t12_size;
                }
            } else {
                x_trueCount = z.size(0);
            }
        } else if (w_trueCount == 1) {
            if (trueCount == 1) {
                x_trueCount = z.size(0);
            } else {
                x_trueCount = trueCount;
            }
        } else if (trueCount == 1) {
            x_trueCount = t5_size;
        } else {
            x_trueCount = trueCount;
        }
        if ((trueCount == t5_size) && (trueCount == t12_size) && (e_trueCount == f_trueCount) &&
            (trueCount == r3.size(0)) && (g_trueCount == t12_size) &&
            (i_trueCount == k_trueCount) && (trueCount == t5_size) && (trueCount == z.size(0)) &&
            (l_trueCount == m_trueCount) && (r9.size(0) == trueCount) && (t12_size == i46) &&
            (z.size(0) == b_t12_size) && (o_trueCount == i47) && (t_trueCount == x_trueCount)) {
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
            int i49;
            int i_scalarLB;
            int i_vectorUB;
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
            alpha0_t_size = trueCount;
            i_scalarLB = (trueCount / 2) << 1;
            i_vectorUB = i_scalarLB - 2;
            for (i49 = 0; i49 <= i_vectorUB; i49 += 2) {
                __m128d r46;
                __m128d r47;
                __m128d r48;
                __m128d r49;
                __m128d r50;
                __m128d r51;
                __m128d r52;
                __m128d r53;
                r46 = _mm_loadu_pd(&alpha1_t_data[i49]);
                r47 = _mm_loadu_pd(&t5_data[i49]);
                r48 = _mm_loadu_pd(&t11_data[i49]);
                r49 = _mm_loadu_pd(&t12_data[i49]);
                r50 = _mm_loadu_pd(&t10_data[i49]);
                r51 = _mm_loadu_pd(&r3[i49]);
                r52 = _mm_loadu_pd(&z[i49]);
                r53 = _mm_loadu_pd(&r9[i49]);
                _mm_storeu_pd(
                    &alpha0_t_data[i49],
                    _mm_div_pd(
                        _mm_mul_pd(
                            _mm_add_pd(
                                _mm_sub_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_set1_pd(gb_CoefPS),
                                                          _mm_mul_pd(r46, _mm_set1_pd(hb_CoefPS))),
                                               _mm_mul_pd(_mm_set1_pd(ib_CoefPS), r47)),
                                    _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jb_CoefPS), r48), r49)),
                                _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(kb_CoefPS), r50), r51),
                                           r49)),
                            _mm_set1_pd(-1.0)),
                        _mm_sub_pd(
                            _mm_sub_pd(
                                _mm_add_pd(_mm_add_pd(_mm_set1_pd(lb_CoefPS),
                                                      _mm_mul_pd(r46, _mm_set1_pd(mb_CoefPS))),
                                           _mm_mul_pd(_mm_set1_pd(nb_CoefPS), r47)),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(ob_CoefPS), r50), r52)),
                            _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(pb_CoefPS), r52),
                                       _mm_sub_pd(r49, _mm_mul_pd(r53, r48))))));
            }
            for (i49 = i_scalarLB; i49 < trueCount; i49++) {
                double d5;
                double d6;
                double d7;
                double d8;
                double d9;
                d5 = alpha1_t_data[i49];
                d6 = t5_data[i49];
                d7 = t11_data[i49];
                d8 = t12_data[i49];
                d9 = t10_data[i49];
                alpha0_t_data[i49] =
                    -((((gb_CoefPS + d5 * hb_CoefPS) + ib_CoefPS * d6) - jb_CoefPS * d7 * d8) +
                      kb_CoefPS * d9 * r3[i49] * d8) /
                    ((((lb_CoefPS + d5 * mb_CoefPS) + nb_CoefPS * d6) - ob_CoefPS * d9 * z[i49]) -
                     pb_CoefPS * z[i49] * (d8 - r9[i49] * d7));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &trueCount,
                             t5_data, &t5_size, t11_data, &trueCount, t12_data, &t12_size, t10_data,
                             &trueCount, r3, z, r9);
        }
        //
        // 'G2_Hermite_Interpolation_nAxis:219' Idx       = find(alpha0_t > 0);
        for (int i48{0}; i48 < alpha0_t_size; i48++) {
            c_alpha0_t_data[i48] = (alpha0_t_data[i48] > 0.0);
        }
        coder::c_eml_find(c_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation_nAxis:220' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:221' alpha0_u  = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:223' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:224' status = int32(5);
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:229' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int c_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation_nAxis:231' CostInt = zeros(size(alpha0_u));
                c_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:232' beta0_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:233' beta1_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:235' for k = 1:length(alpha0_u)
                for (int d_k{0}; d_k < Idx_size; d_k++) {
                    int i50;
                    // 'G2_Hermite_Interpolation_nAxis:237' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:238' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:239' r1D0, t1, n1, D);
                    i50 = Idx_data[d_k];
                    Calc_beta0_beta1(alpha0_t_data[i50 - 1], alpha1_t_data[i50 - 1], r0D0, t0, n0,
                                     r1D0, t1, n1,
                                     (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(),
                                     &beta0_u_data[d_k], &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation_nAxis:240' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:241' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:242' r1D0, t1, n1, D);
                    CostInt_data[d_k] = EvalCostIntegral(
                        alpha0_t_data[i50 - 1], beta0_u_data[d_k], alpha1_t_data[i50 - 1],
                        beta1_u_data[d_k], r0D0, t0, n0, r1D0, t1, n1,
                        (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data());
                }
                int c_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:246' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &c_ex, &c_iindx);
                // 'G2_Hermite_Interpolation_nAxis:247' alpha0   = alpha0_u(Idx);
                c_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                alpha0 = alpha0_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:248' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:249' beta0    = beta0_u(Idx);
                a = beta0_u_data[c_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:250' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:252' else
                // 'G2_Hermite_Interpolation_nAxis:254' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:255' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:256' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:257' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:258' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, r1D0, t1, n1,
                                 (double *)((::coder::array<double, 1U> *)&ctx_cfg_D)->data(), &a,
                                 &b_a);
            }
            guard1 = true;
        }
    }
    if (guard1) {
        __m128d r;
        __m128d r11;
        __m128d r27;
        __m128d r28;
        double a_tmp;
        double b_a_tmp;
        //
        //  Hermite basis
        // 'G2_Hermite_Interpolation_nAxis:265' h00 = [-6,    15,   -10,     0,     0,     1];
        // 'G2_Hermite_Interpolation_nAxis:266' h10 = [-3,     8,    -6,     0,     1,     0];
        // 'G2_Hermite_Interpolation_nAxis:267' h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
        // 'G2_Hermite_Interpolation_nAxis:268' h01 = [6,   -15,     10,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:269' h11 = [-3,    7,     -4,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:270' h21 = [0.5,  -1,    0.5,     0,     0,     0];
        //  evaluate coefficients as sum of basis functions
        // 'G2_Hermite_Interpolation_nAxis:272' p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 +
        // alpha0^2*n0) * h20 + ... 'G2_Hermite_Interpolation_nAxis:273'      r1D0 * h01 + alpha1*t1
        // * h11 + (beta1*t1 + alpha1^2*n1) * h21;
        a_tmp = alpha0 * alpha0;
        b_a_tmp = alpha1 * alpha1;
        r = _mm_set1_pd(alpha0);
        for (int i9{0}; i9 < 6; i9++) {
            __m128d b_r2;
            __m128d r10;
            __m128d r6;
            __m128d r8;
            int i10;
            int i16;
            b_r2 = _mm_loadu_pd(&r0D0[0]);
            i10 = b_b[i9];
            r6 = _mm_set1_pd(static_cast<double>(i10));
            _mm_storeu_pd(&b_r0D0[i9][0], _mm_mul_pd(b_r2, r6));
            r8 = _mm_loadu_pd(&t0[0]);
            i16 = c_b[i9];
            r10 = _mm_set1_pd(static_cast<double>(i16));
            _mm_storeu_pd(&b_alpha0[i9][0], _mm_mul_pd(_mm_mul_pd(r, r8), r10));
            b_r2 = _mm_loadu_pd(&r0D0[2]);
            _mm_storeu_pd(&b_r0D0[i9][2], _mm_mul_pd(b_r2, r6));
            r8 = _mm_loadu_pd(&t0[2]);
            _mm_storeu_pd(&b_alpha0[i9][2], _mm_mul_pd(_mm_mul_pd(r, r8), r10));
            b_r0D0[i9][4] = r0D0[4] * static_cast<double>(i10);
            b_alpha0[i9][4] = alpha0 * t0[4] * static_cast<double>(i16);
        }
        __m128d b_r1;
        __m128d r4;
        __m128d r5;
        __m128d r7;
        b_r1 = _mm_loadu_pd(&t0[0]);
        r4 = _mm_loadu_pd(&n0[0]);
        r5 = _mm_set1_pd(a);
        r7 = _mm_set1_pd(a_tmp);
        _mm_storeu_pd(&c_a[0], _mm_add_pd(_mm_mul_pd(r5, b_r1), _mm_mul_pd(r7, r4)));
        b_r1 = _mm_loadu_pd(&t0[2]);
        r4 = _mm_loadu_pd(&n0[2]);
        _mm_storeu_pd(&c_a[2], _mm_add_pd(_mm_mul_pd(r5, b_r1), _mm_mul_pd(r7, r4)));
        c_a[4] = a * t0[4] + a_tmp * n0[4];
        r11 = _mm_set1_pd(0.0);
        for (int i24{0}; i24 < 6; i24++) {
            __m128d r13;
            __m128d r15;
            __m128d r17;
            __m128d r22;
            __m128d r24;
            __m128d r26;
            double d1;
            int i32;
            r13 = _mm_loadu_pd(&c_a[0]);
            r15 = _mm_loadu_pd(&b_r0D0[i24][0]);
            r17 = _mm_loadu_pd(&b_alpha0[i24][0]);
            d1 = d_b[i24];
            r22 = _mm_set1_pd(d1);
            _mm_storeu_pd(&c_r0D0[i24][0],
                          _mm_add_pd(_mm_add_pd(r15, r17), _mm_add_pd(r11, _mm_mul_pd(r13, r22))));
            r24 = _mm_loadu_pd(&r1D0[0]);
            i32 = e_b[i24];
            r26 = _mm_set1_pd(static_cast<double>(i32));
            _mm_storeu_pd(&b_r1D0[i24][0], _mm_mul_pd(r24, r26));
            r13 = _mm_loadu_pd(&c_a[2]);
            r15 = _mm_loadu_pd(&b_r0D0[i24][2]);
            r17 = _mm_loadu_pd(&b_alpha0[i24][2]);
            _mm_storeu_pd(&c_r0D0[i24][2],
                          _mm_add_pd(_mm_add_pd(r15, r17), _mm_add_pd(r11, _mm_mul_pd(r13, r22))));
            r24 = _mm_loadu_pd(&r1D0[2]);
            _mm_storeu_pd(&b_r1D0[i24][2], _mm_mul_pd(r24, r26));
            c_r0D0[i24][4] = (b_r0D0[i24][4] + b_alpha0[i24][4]) + c_a[4] * d1;
            b_r1D0[i24][4] = r1D0[4] * static_cast<double>(i32);
        }
        __m128d r12;
        __m128d r14;
        __m128d r16;
        __m128d r19;
        r12 = _mm_loadu_pd(&t1[0]);
        r14 = _mm_loadu_pd(&n1[0]);
        r16 = _mm_set1_pd(b_a);
        r19 = _mm_set1_pd(b_a_tmp);
        _mm_storeu_pd(&c_a[0], _mm_add_pd(_mm_mul_pd(r16, r12), _mm_mul_pd(r19, r14)));
        r12 = _mm_loadu_pd(&t1[2]);
        r14 = _mm_loadu_pd(&n1[2]);
        _mm_storeu_pd(&c_a[2], _mm_add_pd(_mm_mul_pd(r16, r12), _mm_mul_pd(r19, r14)));
        c_a[4] = b_a * t1[4] + b_a_tmp * n1[4];
        r27 = _mm_set1_pd(alpha1);
        r28 = _mm_set1_pd(0.0);
        for (int i33{0}; i33 < 6; i33++) {
            __m128d r29;
            __m128d r30;
            __m128d r31;
            __m128d r32;
            __m128d r35;
            __m128d r40;
            double d2;
            int i37;
            r29 = _mm_loadu_pd(&t1[0]);
            r30 = _mm_loadu_pd(&c_r0D0[i33][0]);
            r31 = _mm_loadu_pd(&b_r1D0[i33][0]);
            r32 = _mm_loadu_pd(&c_a[0]);
            i37 = f_b[i33];
            r35 = _mm_set1_pd(static_cast<double>(i37));
            d2 = g_b[i33];
            r40 = _mm_set1_pd(d2);
            _mm_storeu_pd(
                &p5[i33][0],
                _mm_add_pd(_mm_add_pd(_mm_add_pd(r30, r31),
                                      _mm_add_pd(r28, _mm_mul_pd(_mm_mul_pd(r27, r29), r35))),
                           _mm_mul_pd(r32, r40)));
            r29 = _mm_loadu_pd(&t1[2]);
            r30 = _mm_loadu_pd(&c_r0D0[i33][2]);
            r31 = _mm_loadu_pd(&b_r1D0[i33][2]);
            r32 = _mm_loadu_pd(&c_a[2]);
            _mm_storeu_pd(
                &p5[i33][2],
                _mm_add_pd(_mm_add_pd(_mm_add_pd(r30, r31),
                                      _mm_add_pd(r28, _mm_mul_pd(_mm_mul_pd(r27, r29), r35))),
                           _mm_mul_pd(r32, r40)));
            p5[i33][4] =
                ((c_r0D0[i33][4] + b_r1D0[i33][4]) + alpha1 * t1[4] * static_cast<double>(i37)) +
                c_a[4] * d2;
        }
        //  last cross check ...
        // 'G2_Hermite_Interpolation_nAxis:275' p1val = (a1*alpha1+a0)*alpha0^2  +
        // (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
        // 'G2_Hermite_Interpolation_nAxis:276' p2val = (d1*alpha0+d0)*alpha1^2  +
        // (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        // 'G2_Hermite_Interpolation_nAxis:278' if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
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
            // 'G2_Hermite_Interpolation_nAxis:279' status = int32(6);
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
