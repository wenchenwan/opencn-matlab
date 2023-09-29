
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation_nAxis.cpp
//
// MATLAB Coder version            : 5.4
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
#include "mldivide.h"
#include "coder_array.h"
#include "functions.h"
#include <cmath>
#include <cstring>

// Function Declarations
namespace ocn {
static void b_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                               const ::coder::array<double, 1U> &in3, const double in4_data[],
                               const int *in4_size);

static void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                             const ::coder::array<double, 1U> &in3, const double in4_data[],
                             const int *in4_size);

} // namespace ocn

// Function Definitions
//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const ::coder::array<double, 1U> &in3
//                const double in4_data[]
//                const int *in4_size
// Return Type  : void
//
namespace ocn {
static void b_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                               const ::coder::array<double, 1U> &in3, const double in4_data[],
                               const int *in4_size)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_in2 = in2[1];
    c_in2 = in2[3];
    d_in2 = in2[7];
    e_in2 = in2[6];
    if (*in4_size == 1) {
        *in1_size = in3.size(0);
    } else {
        *in1_size = *in4_size;
    }
    stride_0_0 = (in3.size(0) != 1);
    stride_1_0 = (*in4_size != 1);
    if (*in4_size == 1) {
        loop_ub = in3.size(0);
    } else {
        loop_ub = *in4_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] =
            -((b_in2 * in3[i * stride_0_0] + c_in2 * in4_data[i * stride_1_0]) + d_in2) / e_in2;
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const ::coder::array<double, 1U> &in3
//                const double in4_data[]
//                const int *in4_size
// Return Type  : void
//
static void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                             const ::coder::array<double, 1U> &in3, const double in4_data[],
                             const int *in4_size)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_in2 = in2[9];
    c_in2 = in2[11];
    d_in2 = in2[15];
    e_in2 = in2[14];
    if (*in4_size == 1) {
        *in1_size = in3.size(0);
    } else {
        *in1_size = *in4_size;
    }
    stride_0_0 = (in3.size(0) != 1);
    stride_1_0 = (*in4_size != 1);
    if (*in4_size == 1) {
        loop_ub = in3.size(0);
    } else {
        loop_ub = *in4_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] =
            -((b_in2 * in3[i * stride_0_0] + c_in2 * in4_data[i * stride_1_0]) + d_in2) / e_in2;
    }
}

//
// function [p5, status, alpha0, alpha1] = G2_Hermite_Interpolation_nAxis(ctx, r0D0_in, r0D1_in,
// r0D2_in, r1D0_in, r1D1_in, r1D2_in)
//
// Arguments    : const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<double, 1U> &ctx_cfg_D
//                const ::coder::array<double, 1U> &r0D0_in
//                const ::coder::array<double, 1U> &r0D1_in
//                const ::coder::array<double, 1U> &r0D2_in
//                const ::coder::array<double, 1U> &r1D0_in
//                const ::coder::array<double, 1U> &r1D1_in
//                const ::coder::array<double, 1U> &r1D2_in
//                double p5[6][6]
//                int *status
// Return Type  : void
//
void G2_Hermite_Interpolation_nAxis(
    const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
    const ::coder::array<double, 1U> &ctx_cfg_D, const ::coder::array<double, 1U> &r0D0_in,
    const ::coder::array<double, 1U> &r0D1_in, const ::coder::array<double, 1U> &r0D2_in,
    const ::coder::array<double, 1U> &r1D0_in, const ::coder::array<double, 1U> &r1D1_in,
    const ::coder::array<double, 1U> &r1D2_in, double p5[6][6], int *status)
{
    static const double d_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double g_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b_b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char c_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char e_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char f_b[6]{-3, 7, -4, 0, 0, 0};
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> z;
    ::coder::array<int, 1U> k_i;
    ::coder::array<int, 1U> r2;
    ::coder::array<bool, 1U> c_alpha0_t_data;
    ::coder::array<bool, 1U> c_alpha1_t_data;
    ::coder::array<bool, 1U> d_alpha0_t_data;
    ::coder::array<bool, 1U> d_alpha1_t_data;
    ::coder::array<bool, 1U> f_alpha0_t_data;
    ::coder::array<bool, 1U> g_alpha0_t_data;
    creal_T b_alpha1_v[9];
    double CoefPS[16];
    double CostInt_data[9];
    double alpha0_t_data[9];
    double alpha1_t_data[9];
    double beta0_u_data[9];
    double beta1_u_data[9];
    double t12_data[9];
    double D[6];
    double n0[6];
    double n1[6];
    double r0D0[6];
    double r0D1[6];
    double r0D2[6];
    double r1D0[6];
    double r1D1[6];
    double r1D2[6];
    double t0[6];
    double t1[6];
    double a;
    double alpha0;
    double alpha1;
    double b_a;
    double b_ex;
    double c_ex;
    double ex;
    double kappa0;
    double kappa1;
    int alpha0_t_size;
    int alpha1_t_size;
    int b_end;
    int b_iindx;
    int b_partialTrueCount;
    int b_trueCount;
    int c_end;
    int c_iindx;
    int c_partialTrueCount;
    int c_trueCount;
    int d_end;
    int d_partialTrueCount;
    int d_trueCount;
    int e_end;
    int e_partialTrueCount;
    int end;
    int f_end;
    int f_partialTrueCount;
    int g_end;
    int g_partialTrueCount;
    int iindx;
    int partialTrueCount;
    int t12_size;
    int t5_size;
    int trueCount;
    signed char tmp_data[6];
    signed char b_tmp_data[3];
    bool e_alpha0_t_data[9];
    bool b_alpha0_t_data[3];
    bool b_alpha1_t_data[3];
    bool guard1;
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
    // 'G2_Hermite_Interpolation_nAxis:32' N_AXES_MAX = 6;
    //  Function are calculated for 5 axis
    // 'G2_Hermite_Interpolation_nAxis:35' r0D0 = zeros(N_AXES_MAX, 1);
    // 'G2_Hermite_Interpolation_nAxis:35' r0D1 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:35' r0D2 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:35' r1D0 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:36' r1D1 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:36' r1D2 = r0D0;
    for (int i{0}; i < 6; i++) {
        r0D0[i] = 0.0;
        r0D1[i] = 0.0;
        r0D2[i] = 0.0;
        r1D0[i] = 0.0;
        r1D1[i] = 0.0;
        r1D2[i] = 0.0;
    }
    //  Place input vector in : Set padding on vector
    // 'G2_Hermite_Interpolation_nAxis:39' r0D0(ctx.cfg.maskTot) = r0D0_in;
    end = ctx_cfg_maskTot_size[1];
    partialTrueCount = 0;
    for (int b_i{0}; b_i < end; b_i++) {
        if (ctx_cfg_maskTot_data[b_i]) {
            r0D0[b_i] = r0D0_in[partialTrueCount];
            partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:40' r0D1(ctx.cfg.maskTot) = r0D1_in;
    b_end = ctx_cfg_maskTot_size[1];
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i < b_end; c_i++) {
        if (ctx_cfg_maskTot_data[c_i]) {
            r0D1[c_i] = r0D1_in[b_partialTrueCount];
            b_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:41' r0D2(ctx.cfg.maskTot) = r0D2_in;
    c_end = ctx_cfg_maskTot_size[1];
    c_partialTrueCount = 0;
    for (int d_i{0}; d_i < c_end; d_i++) {
        if (ctx_cfg_maskTot_data[d_i]) {
            r0D2[d_i] = r0D2_in[c_partialTrueCount];
            c_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:42' r1D0(ctx.cfg.maskTot) = r1D0_in;
    d_end = ctx_cfg_maskTot_size[1];
    d_partialTrueCount = 0;
    for (int e_i{0}; e_i < d_end; e_i++) {
        if (ctx_cfg_maskTot_data[e_i]) {
            r1D0[e_i] = r1D0_in[d_partialTrueCount];
            d_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:43' r1D1(ctx.cfg.maskTot) = r1D1_in;
    e_end = ctx_cfg_maskTot_size[1];
    e_partialTrueCount = 0;
    for (int f_i{0}; f_i < e_end; f_i++) {
        if (ctx_cfg_maskTot_data[f_i]) {
            r1D1[f_i] = r1D1_in[e_partialTrueCount];
            e_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:44' r1D2(ctx.cfg.maskTot) = r1D2_in;
    f_end = ctx_cfg_maskTot_size[1];
    f_partialTrueCount = 0;
    for (int g_i{0}; g_i < f_end; g_i++) {
        if (ctx_cfg_maskTot_data[g_i]) {
            r1D2[g_i] = r1D2_in[f_partialTrueCount];
            f_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:46' D = zeros( N_AXES_MAX,1);
    for (int h_i{0}; h_i < 6; h_i++) {
        D[h_i] = 0.0;
    }
    // 'G2_Hermite_Interpolation_nAxis:47' D(ctx.cfg.maskTot) = ctx.cfg.D;
    g_end = ctx_cfg_maskTot_size[1] - 1;
    trueCount = 0;
    g_partialTrueCount = 0;
    for (int i_i{0}; i_i <= g_end; i_i++) {
        if (ctx_cfg_maskTot_data[i_i]) {
            trueCount++;
            tmp_data[g_partialTrueCount] = static_cast<signed char>(i_i + 1);
            g_partialTrueCount++;
        }
    }
    for (int j_i{0}; j_i < trueCount; j_i++) {
        D[tmp_data[j_i] - 1] = ctx_cfg_D[j_i];
    }
    // 'G2_Hermite_Interpolation_nAxis:49' status = int32(1);
    *status = 1;
    //  default success
    // 'G2_Hermite_Interpolation_nAxis:51' p5 = zeros(N_AXES_MAX,6);
    std::memset(&p5[0][0], 0, 36U * sizeof(double));
    // 'G2_Hermite_Interpolation_nAxis:53' alpha0 = 0;
    // 'G2_Hermite_Interpolation_nAxis:54' alpha1 = 0;
    //  compute Frenet frame
    // 'G2_Hermite_Interpolation_nAxis:57' [t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
    calc_t_nk_kappa(r0D1, r0D2, t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation_nAxis:58' [t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);
    calc_t_nk_kappa(r1D1, r1D2, t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    // 'G2_Hermite_Interpolation_nAxis:66' CoefPS = CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D);
    CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D, CoefPS);
    //
    // 'G2_Hermite_Interpolation_nAxis:68' a1     = CoefPS(1);
    // 'G2_Hermite_Interpolation_nAxis:69' a0     = CoefPS(2);
    // 'G2_Hermite_Interpolation_nAxis:70' b1     = CoefPS(3);
    // 'G2_Hermite_Interpolation_nAxis:71' b0     = CoefPS(4);
    // 'G2_Hermite_Interpolation_nAxis:72' c3     = CoefPS(5);
    // 'G2_Hermite_Interpolation_nAxis:73' c2     = CoefPS(6);
    // 'G2_Hermite_Interpolation_nAxis:74' c1     = CoefPS(7);
    // 'G2_Hermite_Interpolation_nAxis:75' c0     = CoefPS(8);
    // 'G2_Hermite_Interpolation_nAxis:76' d1     = CoefPS(9);
    // 'G2_Hermite_Interpolation_nAxis:77' d0     = CoefPS(10);
    // 'G2_Hermite_Interpolation_nAxis:78' e1     = CoefPS(11);
    // 'G2_Hermite_Interpolation_nAxis:79' e0     = CoefPS(12);
    // 'G2_Hermite_Interpolation_nAxis:80' f3     = CoefPS(13);
    // 'G2_Hermite_Interpolation_nAxis:81' f2     = CoefPS(14);
    // 'G2_Hermite_Interpolation_nAxis:82' f1     = CoefPS(15);
    // 'G2_Hermite_Interpolation_nAxis:83' f0     = CoefPS(16);
    // 'G2_Hermite_Interpolation_nAxis:84' TolZero = 1e-11;
    //
    // 'G2_Hermite_Interpolation_nAxis:86' if (kappa0 == 0) && (kappa1 == 0)
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        double b_CoefPS[2][2];
        double X[2];
        double c_CoefPS[2];
        //  degenerated case where the polynomial system degenerates to a linear one
        // 'G2_Hermite_Interpolation_nAxis:87' M       = [b0, c1;
        // 'G2_Hermite_Interpolation_nAxis:88'                f1, e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:90' B       = [-c0;
        // 'G2_Hermite_Interpolation_nAxis:91'                -f0];
        //
        // 'G2_Hermite_Interpolation_nAxis:93' X       = M \ B;
        b_CoefPS[0][0] = CoefPS[3];
        b_CoefPS[1][0] = CoefPS[6];
        b_CoefPS[0][1] = CoefPS[14];
        b_CoefPS[1][1] = CoefPS[11];
        c_CoefPS[0] = -CoefPS[7];
        c_CoefPS[1] = -CoefPS[15];
        coder::mldivide(b_CoefPS, c_CoefPS, X);
        //  resolution of linear system
        // 'G2_Hermite_Interpolation_nAxis:94' alpha0  = X(1);
        alpha0 = X[0];
        // 'G2_Hermite_Interpolation_nAxis:95' alpha1  = X(2);
        alpha1 = X[1];
        // 'G2_Hermite_Interpolation_nAxis:97' if ~((alpha0 > 0) && (alpha1 > 0))
        if ((X[0] > 0.0) && (X[1] > 0.0)) {
            // 'G2_Hermite_Interpolation_nAxis:101' [beta0, beta1] = Calc_beta0_beta1(alpha0,
            // alpha1, ... 'G2_Hermite_Interpolation_nAxis:102' r0D0, t0, n0, ...
            // 'G2_Hermite_Interpolation_nAxis:103'                                       r1D0, t1,
            // n1, D);
            Calc_beta0_beta1(X[0], X[1], r0D0, t0, n0, r1D0, t1, n1, D, &a, &b_a);
            guard1 = true;
        }
    } else if (kappa0 == 0.0) {
        creal_T alpha1_v[3];
        double dv2[4];
        int d_loop_ub;
        int i_partialTrueCount;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        bool unnamed_idx_2;
        // 'G2_Hermite_Interpolation_nAxis:104' elseif kappa0 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:106' Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0
        // + b1*f0 - c1*f1, b0*f0 - c0*f1];
        //
        // 'G2_Hermite_Interpolation_nAxis:108' alpha1_v = c_roots_(Coef);
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
        // 'G2_Hermite_Interpolation_nAxis:109' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        c_trueCount = 0;
        unnamed_idx_2 = (std::abs(alpha1_v[0].im) < 1.0E-11);
        unnamed_idx_0 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[0].re > 0.0)) {
            c_trueCount = 1;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[1].im) < 1.0E-11);
        unnamed_idx_1 = unnamed_idx_2;
        if (unnamed_idx_2 && (alpha1_v[1].re > 0.0)) {
            c_trueCount++;
        }
        unnamed_idx_2 = (std::abs(alpha1_v[2].im) < 1.0E-11);
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            c_trueCount++;
        }
        i_partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha1_v[0].re > 0.0)) {
            b_tmp_data[0] = 1;
            i_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha1_v[1].re > 0.0)) {
            b_tmp_data[i_partialTrueCount] = 2;
            i_partialTrueCount++;
        }
        if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
            b_tmp_data[i_partialTrueCount] = 3;
        }
        for (int i2{0}; i2 < c_trueCount; i2++) {
            alpha1_t_data[i2] = alpha1_v[b_tmp_data[i2] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:111' if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:112' alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
            r.set_size(c_trueCount);
            for (int i8{0}; i8 < c_trueCount; i8++) {
                r[i8] = std::pow(alpha1_t_data[i8], 2.0);
            }
            if (r.size(0) == c_trueCount) {
                int loop_ub;
                alpha0_t_size = r.size(0);
                loop_ub = r.size(0);
                for (int i18{0}; i18 < loop_ub; i18++) {
                    alpha0_t_data[i18] =
                        -((CoefPS[9] * r[i18] + CoefPS[11] * alpha1_t_data[i18]) + CoefPS[15]) /
                        CoefPS[14];
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r, alpha1_t_data,
                                 &c_trueCount);
            }
        } else {
            int i22;
            int i26;
            int i28;
            // 'G2_Hermite_Interpolation_nAxis:113' else
            // 'G2_Hermite_Interpolation_nAxis:114' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            r.set_size(c_trueCount);
            for (int i10{0}; i10 < c_trueCount; i10++) {
                r[i10] = std::pow(alpha1_t_data[i10], 3.0);
            }
            r1.set_size(c_trueCount);
            for (int i14{0}; i14 < c_trueCount; i14++) {
                r1[i14] = std::pow(alpha1_t_data[i14], 2.0);
            }
            if (r.size(0) == 1) {
                i22 = r1.size(0);
            } else {
                i22 = r.size(0);
            }
            if (r.size(0) == 1) {
                i26 = r1.size(0);
            } else {
                i26 = r.size(0);
            }
            if (i26 == 1) {
                i28 = c_trueCount;
            } else if (r.size(0) == 1) {
                i28 = r1.size(0);
            } else {
                i28 = r.size(0);
            }
            if ((r.size(0) == r1.size(0)) && (i22 == c_trueCount) && (i28 == c_trueCount)) {
                int f_loop_ub;
                alpha0_t_size = r.size(0);
                f_loop_ub = r.size(0);
                for (int i36{0}; i36 < f_loop_ub; i36++) {
                    double d1;
                    d1 = alpha1_t_data[i36];
                    alpha0_t_data[i36] =
                        -(((CoefPS[4] * r[i36] + CoefPS[5] * r1[i36]) + CoefPS[6] * d1) +
                          CoefPS[7]) /
                        (CoefPS[2] * d1 + CoefPS[3]);
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r, r1, alpha1_t_data,
                                 &c_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:117' Idx       = find(alpha0_t > 0);
        for (int i24{0}; i24 < alpha0_t_size; i24++) {
            b_alpha0_t_data[i24] = (alpha0_t_data[i24] > 0.0);
        }
        c_alpha0_t_data.set(&b_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(c_alpha0_t_data, r2);
        k_i.set_size(r2.size(0));
        d_loop_ub = r2.size(0);
        for (int i30{0}; i30 < d_loop_ub; i30++) {
            k_i[i30] = r2[i30];
        }
        for (int i33{0}; i33 < alpha0_t_size; i33++) {
            b_alpha0_t_data[i33] = (alpha0_t_data[i33] > 0.0);
        }
        d_alpha0_t_data.set(&b_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(d_alpha0_t_data, r2);
        // 'G2_Hermite_Interpolation_nAxis:118' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:119' alpha0_u  = alpha0_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:121' if ~(numel(alpha0_u) > 0)
        if (r2.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:122' status = int32(3);
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:127' if length(alpha0_u) > 1
            if (r2.size(0) > 1) {
                int CostInt_size;
                int h_loop_ub;
                int i44;
                int j_loop_ub;
                int l_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:129' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r2.size(0));
                h_loop_ub = static_cast<signed char>(r2.size(0));
                if (h_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, h_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:130' beta0_u = zeros(size(alpha0_u));
                j_loop_ub = static_cast<signed char>(r2.size(0));
                if (j_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, j_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:131' beta1_u = zeros(size(alpha0_u));
                l_loop_ub = static_cast<signed char>(r2.size(0));
                if (l_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, l_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:133' for k = 1:length(alpha0_u)
                i44 = k_i.size(0);
                for (int b_k{0}; b_k < i44; b_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:135' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:136' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:137' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r2[b_k] - 1], alpha1_t_data[r2[b_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation_nAxis:138' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:139' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:140' r1D0, t1, n1, D);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[r2[b_k] - 1], beta0_u_data[b_k], alpha1_t_data[r2[b_k] - 1],
                        beta1_u_data[b_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:144' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &ex, &iindx);
                // 'G2_Hermite_Interpolation_nAxis:145' alpha0   = alpha0_u(Idx);
                alpha0_tmp = r2[iindx - 1] - 1;
                alpha0 = alpha0_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:146' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:147' beta0    = beta0_u(Idx);
                a = beta0_u_data[iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:148' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:150' else
                // 'G2_Hermite_Interpolation_nAxis:152' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:153' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:154' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:155' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:156' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[k_i[0] - 1], alpha1_t_data[k_i[0] - 1], r0D0, t0, n0,
                                 r1D0, t1, n1, D, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else if (kappa1 == 0.0) {
        creal_T alpha0_v[3];
        double dv2[4];
        int e_loop_ub;
        int j_partialTrueCount;
        bool b_unnamed_idx_2;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        // 'G2_Hermite_Interpolation_nAxis:160' elseif kappa1 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:162' Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1
        // - c0*e1 - b0*e0, c1*f0 - c0*e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:164' alpha0_v  = c_roots_(Coef);
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
        // 'G2_Hermite_Interpolation_nAxis:165' alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) <
        // TolZero) & (real(alpha0_v) >  0)));
        d_trueCount = 0;
        b_unnamed_idx_2 = (std::abs(alpha0_v[0].im) < 1.0E-11);
        unnamed_idx_0 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[0].re > 0.0)) {
            d_trueCount = 1;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[1].im) < 1.0E-11);
        unnamed_idx_1 = b_unnamed_idx_2;
        if (b_unnamed_idx_2 && (alpha0_v[1].re > 0.0)) {
            d_trueCount++;
        }
        b_unnamed_idx_2 = (std::abs(alpha0_v[2].im) < 1.0E-11);
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            d_trueCount++;
        }
        j_partialTrueCount = 0;
        if (unnamed_idx_0 && (alpha0_v[0].re > 0.0)) {
            b_tmp_data[0] = 1;
            j_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (alpha0_v[1].re > 0.0)) {
            b_tmp_data[j_partialTrueCount] = 2;
            j_partialTrueCount++;
        }
        if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
            b_tmp_data[j_partialTrueCount] = 3;
        }
        for (int i4{0}; i4 < d_trueCount; i4++) {
            alpha0_t_data[i4] = alpha0_v[b_tmp_data[i4] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:167' if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:168' alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
            r.set_size(d_trueCount);
            for (int i9{0}; i9 < d_trueCount; i9++) {
                r[i9] = std::pow(alpha0_t_data[i9], 2.0);
            }
            if (r.size(0) == d_trueCount) {
                int c_loop_ub;
                alpha1_t_size = r.size(0);
                c_loop_ub = r.size(0);
                for (int i21{0}; i21 < c_loop_ub; i21++) {
                    alpha1_t_data[i21] =
                        -((CoefPS[1] * r[i21] + CoefPS[3] * alpha0_t_data[i21]) + CoefPS[7]) /
                        CoefPS[6];
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r, alpha0_t_data,
                                   &d_trueCount);
            }
        } else {
            int i23;
            int i27;
            int i29;
            // 'G2_Hermite_Interpolation_nAxis:169' else
            // 'G2_Hermite_Interpolation_nAxis:170' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            r.set_size(d_trueCount);
            for (int i13{0}; i13 < d_trueCount; i13++) {
                r[i13] = std::pow(alpha0_t_data[i13], 3.0);
            }
            r1.set_size(d_trueCount);
            for (int i17{0}; i17 < d_trueCount; i17++) {
                r1[i17] = std::pow(alpha0_t_data[i17], 2.0);
            }
            if (r.size(0) == 1) {
                i23 = r1.size(0);
            } else {
                i23 = r.size(0);
            }
            if (r.size(0) == 1) {
                i27 = r1.size(0);
            } else {
                i27 = r.size(0);
            }
            if (i27 == 1) {
                i29 = d_trueCount;
            } else if (r.size(0) == 1) {
                i29 = r1.size(0);
            } else {
                i29 = r.size(0);
            }
            if ((r.size(0) == r1.size(0)) && (i23 == d_trueCount) && (i29 == d_trueCount)) {
                int g_loop_ub;
                alpha1_t_size = r.size(0);
                g_loop_ub = r.size(0);
                for (int i37{0}; i37 < g_loop_ub; i37++) {
                    double d2;
                    d2 = alpha0_t_data[i37];
                    alpha1_t_data[i37] =
                        -(((CoefPS[12] * r[i37] + CoefPS[13] * r1[i37]) + CoefPS[14] * d2) +
                          CoefPS[15]) /
                        (CoefPS[10] * d2 + CoefPS[11]);
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r, r1, alpha0_t_data,
                                   &d_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:173' Idx      = find(alpha1_t > 0);
        for (int i25{0}; i25 < alpha1_t_size; i25++) {
            b_alpha1_t_data[i25] = (alpha1_t_data[i25] > 0.0);
        }
        c_alpha1_t_data.set(&b_alpha1_t_data[0], alpha1_t_size);
        coder::c_eml_find(c_alpha1_t_data, r2);
        k_i.set_size(r2.size(0));
        e_loop_ub = r2.size(0);
        for (int i32{0}; i32 < e_loop_ub; i32++) {
            k_i[i32] = r2[i32];
        }
        for (int i34{0}; i34 < alpha1_t_size; i34++) {
            b_alpha1_t_data[i34] = (alpha1_t_data[i34] > 0.0);
        }
        d_alpha1_t_data.set(&b_alpha1_t_data[0], alpha1_t_size);
        coder::c_eml_find(d_alpha1_t_data, r2);
        // 'G2_Hermite_Interpolation_nAxis:174' alpha1_u = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:175' alpha0_u = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:177' if ~(numel(alpha0_u) > 0)
        if (r2.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:178' status = int32(4);
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:183' if length(alpha0_u) > 1
            if (r2.size(0) > 1) {
                int CostInt_size;
                int i45;
                int i_loop_ub;
                int k_loop_ub;
                int m_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:184' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r2.size(0));
                i_loop_ub = static_cast<signed char>(r2.size(0));
                if (i_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, i_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:185' beta0_u = zeros(size(alpha0_u));
                k_loop_ub = static_cast<signed char>(r2.size(0));
                if (k_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, k_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:186' beta1_u = zeros(size(alpha0_u));
                m_loop_ub = static_cast<signed char>(r2.size(0));
                if (m_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, m_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:188' for k = 1:length(alpha0_u)
                i45 = k_i.size(0);
                for (int c_k{0}; c_k < i45; c_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:189' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:190' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:191' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r2[c_k] - 1], alpha1_t_data[r2[c_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[c_k],
                                     &beta1_u_data[c_k]);
                    // 'G2_Hermite_Interpolation_nAxis:192' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:193' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:194' r1D0, t1, n1, D);
                    CostInt_data[c_k] = EvalCostIntegral(
                        alpha0_t_data[r2[c_k] - 1], beta0_u_data[c_k], alpha1_t_data[r2[c_k] - 1],
                        beta1_u_data[c_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int b_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:196' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &b_ex, &b_iindx);
                // 'G2_Hermite_Interpolation_nAxis:197' alpha0   = alpha0_u(Idx);
                b_alpha0_tmp = r2[b_iindx - 1] - 1;
                alpha0 = alpha0_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:198' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:199' beta0    = beta0_u(Idx);
                a = beta0_u_data[b_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:200' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:202' else
                // 'G2_Hermite_Interpolation_nAxis:204' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:205' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:206' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:207' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:208' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[k_i[0] - 1], alpha1_t_data[k_i[0] - 1], r0D0, t0, n0,
                                 r1D0, t1, n1, D, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else {
        double dv[10];
        double dv1[10];
        double t10_data[9];
        double t11_data[9];
        double t5_data[9];
        int b_loop_ub;
        int b_t12_size;
        int e_trueCount;
        int f_trueCount;
        int g_trueCount;
        int h_partialTrueCount;
        int h_trueCount;
        int i46;
        int i47;
        int i_trueCount;
        int j_trueCount;
        int k_trueCount;
        int l_trueCount;
        int m_trueCount;
        int n_loop_ub;
        int n_trueCount;
        int o_trueCount;
        int p_trueCount;
        int q_trueCount;
        int r_trueCount;
        int s_trueCount;
        int t_trueCount;
        int u_trueCount;
        int v_trueCount;
        int w_trueCount;
        int x_trueCount;
        int y_trueCount;
        // 'G2_Hermite_Interpolation_nAxis:212' else
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:214' Coef = CharPolyAlpha1(CoefPS);
        //
        // 'G2_Hermite_Interpolation_nAxis:216' alpha1_v = c_roots_(Coef);
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        CharPolyAlpha1(CoefPS, dv);
        for (int i1{0}; i1 < 10; i1++) {
            dv1[i1] = dv[9 - i1];
        }
        c_roots(&dv1[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:217' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
        // TolZero) & (real(alpha1_v) >  0)));
        b_trueCount = 0;
        h_partialTrueCount = 0;
        for (int k{0}; k < 9; k++) {
            double d;
            bool b;
            b = (std::abs(b_alpha1_v[k].im) < 1.0E-11);
            d = b_alpha1_v[k].re;
            if (b && (d > 0.0)) {
                b_trueCount++;
                alpha1_t_data[h_partialTrueCount] = d;
                h_partialTrueCount++;
            }
        }
        //  retain only positive real roots
        //  compute corresponding values of alpha0
        // 'G2_Hermite_Interpolation_nAxis:220' alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
        // CalcAlpha0
        //     ALPHA0_S = CalcAlpha0(ALPHA1,IN2)
        //     This function was generated by the Symbolic Math Toolbox version 9.0.
        //     02-Nov-2022 16:01:04
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
        r.set_size(b_trueCount);
        for (int i12{0}; i12 < b_trueCount; i12++) {
            r[i12] = std::pow(alpha1_t_data[i12], 2.0);
        }
        t5_size = r.size(0);
        b_loop_ub = r.size(0);
        for (int i20{0}; i20 < b_loop_ub; i20++) {
            t5_data[i20] = r[i20];
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        for (int i31{0}; i31 < b_trueCount; i31++) {
            t10_data[i31] = CoefPS[3] + alpha1_t_data[i31] * CoefPS[2];
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        z.set_size(b_trueCount);
        for (int i35{0}; i35 < b_trueCount; i35++) {
            z[i35] = 1.0 / (CoefPS[1] + CoefPS[0] * alpha1_t_data[i35]);
        }
        for (int i38{0}; i38 < b_trueCount; i38++) {
            t11_data[i38] = 1.0 / (CoefPS[1] + CoefPS[0] * alpha1_t_data[i38]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        r.set_size(b_trueCount);
        for (int i39{0}; i39 < b_trueCount; i39++) {
            r[i39] = std::pow(alpha1_t_data[i39], 2.0);
        }
        r1.set_size(b_trueCount);
        for (int i40{0}; i40 < b_trueCount; i40++) {
            r1[i40] = std::pow(alpha1_t_data[i40], 3.0);
        }
        if (b_trueCount == 1) {
            e_trueCount = r.size(0);
        } else {
            e_trueCount = b_trueCount;
        }
        if ((b_trueCount == r.size(0)) && (e_trueCount == r1.size(0))) {
            t12_size = b_trueCount;
            for (int i41{0}; i41 < b_trueCount; i41++) {
                t12_data[i41] =
                    ((CoefPS[7] + alpha1_t_data[i41] * CoefPS[6]) + CoefPS[5] * r[i41]) +
                    CoefPS[4] * r1[i41];
            }
        } else {
            binary_expand_op(t12_data, &t12_size, CoefPS, alpha1_t_data, &b_trueCount, r, r1);
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        r.set_size(b_trueCount);
        for (int i42{0}; i42 < b_trueCount; i42++) {
            r[i42] = std::pow(t11_data[i42], 2.0);
        }
        r1.set_size(b_trueCount);
        for (int i43{0}; i43 < b_trueCount; i43++) {
            r1[i43] = std::pow(t10_data[i43], 2.0);
        }
        if (b_trueCount == 1) {
            f_trueCount = t5_size;
            g_trueCount = t12_size;
            h_trueCount = r.size(0);
            i_trueCount = t5_size;
        } else {
            f_trueCount = b_trueCount;
            g_trueCount = b_trueCount;
            h_trueCount = b_trueCount;
            i_trueCount = b_trueCount;
        }
        if (i_trueCount == 1) {
            if (b_trueCount == 1) {
                j_trueCount = t12_size;
            } else {
                j_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            j_trueCount = t5_size;
        } else {
            j_trueCount = b_trueCount;
        }
        if (b_trueCount == 1) {
            k_trueCount = r.size(0);
        } else {
            k_trueCount = b_trueCount;
        }
        if (k_trueCount == 1) {
            l_trueCount = t12_size;
        } else if (b_trueCount == 1) {
            l_trueCount = r.size(0);
        } else {
            l_trueCount = b_trueCount;
        }
        if (b_trueCount == 1) {
            m_trueCount = t5_size;
            n_trueCount = z.size(0);
        } else {
            m_trueCount = b_trueCount;
            n_trueCount = b_trueCount;
        }
        if (r1.size(0) == 1) {
            i46 = b_trueCount;
        } else {
            i46 = r1.size(0);
        }
        if (t12_size == 1) {
            if (r1.size(0) == 1) {
                b_t12_size = b_trueCount;
            } else {
                b_t12_size = r1.size(0);
            }
        } else {
            b_t12_size = t12_size;
        }
        if (b_trueCount == 1) {
            o_trueCount = t5_size;
        } else {
            o_trueCount = b_trueCount;
        }
        if (o_trueCount == 1) {
            if (b_trueCount == 1) {
                p_trueCount = z.size(0);
            } else {
                p_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            p_trueCount = t5_size;
        } else {
            p_trueCount = b_trueCount;
        }
        if (z.size(0) == 1) {
            if (t12_size == 1) {
                if (r1.size(0) == 1) {
                    i47 = b_trueCount;
                } else {
                    i47 = r1.size(0);
                }
            } else {
                i47 = t12_size;
            }
        } else {
            i47 = z.size(0);
        }
        if (b_trueCount == 1) {
            q_trueCount = t5_size;
        } else {
            q_trueCount = b_trueCount;
        }
        if (q_trueCount == 1) {
            if (b_trueCount == 1) {
                r_trueCount = t12_size;
            } else {
                r_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            r_trueCount = t5_size;
        } else {
            r_trueCount = b_trueCount;
        }
        if (b_trueCount == 1) {
            s_trueCount = r.size(0);
            t_trueCount = t5_size;
        } else {
            s_trueCount = b_trueCount;
            t_trueCount = b_trueCount;
        }
        if (r_trueCount == 1) {
            if (s_trueCount == 1) {
                u_trueCount = t12_size;
            } else if (b_trueCount == 1) {
                u_trueCount = r.size(0);
            } else {
                u_trueCount = b_trueCount;
            }
        } else if (t_trueCount == 1) {
            if (b_trueCount == 1) {
                u_trueCount = t12_size;
            } else {
                u_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            u_trueCount = t5_size;
        } else {
            u_trueCount = b_trueCount;
        }
        if (b_trueCount == 1) {
            v_trueCount = t5_size;
        } else {
            v_trueCount = b_trueCount;
        }
        if (v_trueCount == 1) {
            if (b_trueCount == 1) {
                w_trueCount = z.size(0);
            } else {
                w_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            w_trueCount = t5_size;
        } else {
            w_trueCount = b_trueCount;
        }
        if (b_trueCount == 1) {
            x_trueCount = t5_size;
        } else {
            x_trueCount = b_trueCount;
        }
        if (w_trueCount == 1) {
            if (z.size(0) == 1) {
                if (t12_size == 1) {
                    if (r1.size(0) == 1) {
                        y_trueCount = b_trueCount;
                    } else {
                        y_trueCount = r1.size(0);
                    }
                } else {
                    y_trueCount = t12_size;
                }
            } else {
                y_trueCount = z.size(0);
            }
        } else if (x_trueCount == 1) {
            if (b_trueCount == 1) {
                y_trueCount = z.size(0);
            } else {
                y_trueCount = b_trueCount;
            }
        } else if (b_trueCount == 1) {
            y_trueCount = t5_size;
        } else {
            y_trueCount = b_trueCount;
        }
        if ((b_trueCount == t5_size) && (b_trueCount == t12_size) && (f_trueCount == g_trueCount) &&
            (b_trueCount == r.size(0)) && (h_trueCount == t12_size) &&
            (j_trueCount == l_trueCount) && (b_trueCount == t5_size) &&
            (b_trueCount == z.size(0)) && (m_trueCount == n_trueCount) &&
            (r1.size(0) == b_trueCount) && (t12_size == i46) && (z.size(0) == b_t12_size) &&
            (p_trueCount == i47) && (u_trueCount == y_trueCount)) {
            alpha0_t_size = b_trueCount;
            for (int i48{0}; i48 < b_trueCount; i48++) {
                double d3;
                double d4;
                double d5;
                double d6;
                double d7;
                d3 = alpha1_t_data[i48];
                d4 = t5_data[i48];
                d5 = t11_data[i48];
                d6 = t12_data[i48];
                d7 = t10_data[i48];
                alpha0_t_data[i48] =
                    -((((CoefPS[15] + d3 * CoefPS[11]) + CoefPS[9] * d4) - CoefPS[13] * d5 * d6) +
                      CoefPS[12] * d7 * r[i48] * d6) /
                    ((((CoefPS[14] + d3 * CoefPS[10]) + CoefPS[8] * d4) -
                      CoefPS[13] * d7 * z[i48]) -
                     CoefPS[12] * z[i48] * (d6 - r1[i48] * d5));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &b_trueCount,
                             t5_data, &t5_size, t11_data, &b_trueCount, t12_data, &t12_size,
                             t10_data, &b_trueCount, r, z, r1);
        }
        //
        // 'G2_Hermite_Interpolation_nAxis:222' Idx       = find(alpha0_t > 0);
        for (int i49{0}; i49 < alpha0_t_size; i49++) {
            e_alpha0_t_data[i49] = (alpha0_t_data[i49] > 0.0);
        }
        f_alpha0_t_data.set(&e_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(f_alpha0_t_data, r2);
        k_i.set_size(r2.size(0));
        n_loop_ub = r2.size(0);
        for (int i50{0}; i50 < n_loop_ub; i50++) {
            k_i[i50] = r2[i50];
        }
        for (int i51{0}; i51 < alpha0_t_size; i51++) {
            e_alpha0_t_data[i51] = (alpha0_t_data[i51] > 0.0);
        }
        g_alpha0_t_data.set(&e_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(g_alpha0_t_data, r2);
        // 'G2_Hermite_Interpolation_nAxis:223' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:224' alpha0_u  = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:226' if ~(numel(alpha0_u) > 0)
        if (r2.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:227' status = int32(5);
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:232' if length(alpha0_u) > 1
            if (r2.size(0) > 1) {
                int CostInt_size;
                int i52;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:234' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r2.size(0));
                o_loop_ub = static_cast<signed char>(r2.size(0));
                if (o_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, o_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:235' beta0_u = zeros(size(alpha0_u));
                p_loop_ub = static_cast<signed char>(r2.size(0));
                if (p_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, p_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:236' beta1_u = zeros(size(alpha0_u));
                q_loop_ub = static_cast<signed char>(r2.size(0));
                if (q_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, q_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:238' for k = 1:length(alpha0_u)
                i52 = k_i.size(0);
                for (int d_k{0}; d_k < i52; d_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:240' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:241' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:242' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r2[d_k] - 1], alpha1_t_data[r2[d_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[d_k],
                                     &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation_nAxis:243' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:244' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:245' r1D0, t1, n1, D);
                    CostInt_data[d_k] = EvalCostIntegral(
                        alpha0_t_data[r2[d_k] - 1], beta0_u_data[d_k], alpha1_t_data[r2[d_k] - 1],
                        beta1_u_data[d_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int c_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:249' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &c_ex, &c_iindx);
                // 'G2_Hermite_Interpolation_nAxis:250' alpha0   = alpha0_u(Idx);
                c_alpha0_tmp = r2[c_iindx - 1] - 1;
                alpha0 = alpha0_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:251' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:252' beta0    = beta0_u(Idx);
                a = beta0_u_data[c_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:253' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:255' else
                // 'G2_Hermite_Interpolation_nAxis:257' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:258' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r2[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:259' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:260' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:261' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[k_i[0] - 1], alpha1_t_data[k_i[0] - 1], r0D0, t0, n0,
                                 r1D0, t1, n1, D, &a, &b_a);
            }
            guard1 = true;
        }
    }
    if (guard1) {
        double b_alpha0[6][6];
        double b_r0D0[6][6];
        double b_r1D0[6][6];
        double c_r0D0[6][6];
        double c_a[6];
        double a_tmp;
        double b_a_tmp;
        //
        //  Hermite basis
        // 'G2_Hermite_Interpolation_nAxis:268' h00 = [-6,    15,   -10,     0,     0,     1];
        // 'G2_Hermite_Interpolation_nAxis:269' h10 = [-3,     8,    -6,     0,     1,     0];
        // 'G2_Hermite_Interpolation_nAxis:270' h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
        // 'G2_Hermite_Interpolation_nAxis:271' h01 = [6,   -15,     10,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:272' h11 = [-3,    7,     -4,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:273' h21 = [0.5,  -1,    0.5,     0,     0,     0];
        //  evaluate coefficients as sum of basis functions
        // 'G2_Hermite_Interpolation_nAxis:275' p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 +
        // alpha0^2*n0) * h20 + ... 'G2_Hermite_Interpolation_nAxis:276'      r1D0 * h01 + alpha1*t1
        // * h11 + (beta1*t1 + alpha1^2*n1) * h21;
        a_tmp = alpha0 * alpha0;
        b_a_tmp = alpha1 * alpha1;
        for (int i3{0}; i3 < 6; i3++) {
            for (int i5{0}; i5 < 6; i5++) {
                b_r0D0[i3][i5] = r0D0[i5] * static_cast<double>(b_b[i3]);
                b_alpha0[i3][i5] = alpha0 * t0[i5] * static_cast<double>(c_b[i3]);
            }
            c_a[i3] = a * t0[i3] + a_tmp * n0[i3];
        }
        for (int i6{0}; i6 < 6; i6++) {
            for (int i7{0}; i7 < 6; i7++) {
                c_r0D0[i6][i7] = (b_r0D0[i6][i7] + b_alpha0[i6][i7]) + c_a[i7] * d_b[i6];
                b_r1D0[i6][i7] = r1D0[i7] * static_cast<double>(e_b[i6]);
            }
        }
        for (int i11{0}; i11 < 6; i11++) {
            c_a[i11] = b_a * t1[i11] + b_a_tmp * n1[i11];
            for (int i16{0}; i16 < 6; i16++) {
                b_r0D0[i11][i16] = (c_r0D0[i11][i16] + b_r1D0[i11][i16]) +
                                   alpha1 * t1[i16] * static_cast<double>(f_b[i11]);
            }
        }
        for (int i15{0}; i15 < 6; i15++) {
            for (int i19{0}; i19 < 6; i19++) {
                p5[i15][i19] = b_r0D0[i15][i19] + c_a[i19] * g_b[i15];
            }
        }
        //  last cross check ...
        // 'G2_Hermite_Interpolation_nAxis:278' p1val = (a1*alpha1+a0)*alpha0^2  +
        // (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
        // 'G2_Hermite_Interpolation_nAxis:279' p2val = (d1*alpha0+d0)*alpha1^2  +
        // (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        // 'G2_Hermite_Interpolation_nAxis:281' if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
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
            // 'G2_Hermite_Interpolation_nAxis:282' status = int32(6);
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
