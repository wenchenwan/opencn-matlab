
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
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                             const ::coder::array<double, 1U> &in3, const double in4_data[],
                             const int *in4_size);

static void e_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
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
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const ::coder::array<double, 1U> &in3
//                const double in4_data[]
//                const int *in4_size
// Return Type  : void
//
static void e_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
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
// function [ p5, status, alpha0, alpha1 ] = G2_Hermite_Interpolation_nAxis( ...
//     ctx, r0D0_in, r0D1_in, r0D2_in, r1D0_in, r1D1_in, r1D2_in )
//
// G2_Hermite_Interpolation_nAxis :
//
//  Inputs :
//    ctx     : Context used in the computational chain
//    r0D0_in : Left curve end position vector
//    r0D1_in : Left curve end velocity vector
//    r0D2_in : Left curve end acceleration vector
//    r1D0_in : Right curve start position vector
//    r1D1_in : Right curve start velocity vector
//    r1D2_in : Right curve start acceleration vector
//
//  Outputs :
//    p5      : Resulting polynom (5th order) coefficients for the transition
//    status  : Computation status index
//    alpha0  : Alpha0 vector (see publication)
//    alpha1  : Alpha1 vector (see publication)
//
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
    static const double f_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b_b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char c_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char e_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char g_b[6]{-3, 7, -4, 0, 0, 0};
    ::coder::array<double, 1U> r10;
    ::coder::array<double, 1U> r13;
    ::coder::array<double, 1U> z;
    ::coder::array<int, 1U> k_i;
    ::coder::array<int, 1U> r23;
    ::coder::array<bool, 1U> c_alpha0_t_data;
    ::coder::array<bool, 1U> c_alpha1_t_data;
    ::coder::array<bool, 1U> d_alpha0_t_data;
    ::coder::array<bool, 1U> d_alpha1_t_data;
    ::coder::array<bool, 1U> f_alpha0_t_data;
    ::coder::array<bool, 1U> g_alpha0_t_data;
    creal_T b_alpha1_v[9];
    double b_alpha0[6][6];
    double b_r0D0[6][6];
    double b_r1D0[6][6];
    double c_r0D0[6][6];
    double CoefPS[16];
    double CostInt_data[9];
    double alpha0_t_data[9];
    double alpha1_t_data[9];
    double beta0_u_data[9];
    double beta1_u_data[9];
    double t10_data[9];
    double t11_data[9];
    double t12_data[9];
    double t5_data[9];
    double D[6];
    double c_a[6];
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
    // 'G2_Hermite_Interpolation_nAxis:50' N_AXES_MAX = 6;
    //  Function are calculated for 5 axis
    // 'G2_Hermite_Interpolation_nAxis:53' r0D0 = zeros(N_AXES_MAX, 1);
    // 'G2_Hermite_Interpolation_nAxis:53' r0D1 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:53' r0D2 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:53' r1D0 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:54' r1D1 = r0D0;
    // 'G2_Hermite_Interpolation_nAxis:54' r1D2 = r0D0;
    for (int i{0}; i < 6; i++) {
        r0D0[i] = 0.0;
        r0D1[i] = 0.0;
        r0D2[i] = 0.0;
        r1D0[i] = 0.0;
        r1D1[i] = 0.0;
        r1D2[i] = 0.0;
    }
    //  Place input vector in : Set padding on vector
    // 'G2_Hermite_Interpolation_nAxis:57' r0D0( ctx.cfg.maskTot ) = r0D0_in;
    end = ctx_cfg_maskTot_size[1];
    partialTrueCount = 0;
    for (int b_i{0}; b_i < end; b_i++) {
        if (ctx_cfg_maskTot_data[b_i]) {
            r0D0[b_i] = r0D0_in[partialTrueCount];
            partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:58' r0D1( ctx.cfg.maskTot ) = r0D1_in;
    b_end = ctx_cfg_maskTot_size[1];
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i < b_end; c_i++) {
        if (ctx_cfg_maskTot_data[c_i]) {
            r0D1[c_i] = r0D1_in[b_partialTrueCount];
            b_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:59' r0D2( ctx.cfg.maskTot ) = r0D2_in;
    c_end = ctx_cfg_maskTot_size[1];
    c_partialTrueCount = 0;
    for (int d_i{0}; d_i < c_end; d_i++) {
        if (ctx_cfg_maskTot_data[d_i]) {
            r0D2[d_i] = r0D2_in[c_partialTrueCount];
            c_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:60' r1D0( ctx.cfg.maskTot ) = r1D0_in;
    d_end = ctx_cfg_maskTot_size[1];
    d_partialTrueCount = 0;
    for (int e_i{0}; e_i < d_end; e_i++) {
        if (ctx_cfg_maskTot_data[e_i]) {
            r1D0[e_i] = r1D0_in[d_partialTrueCount];
            d_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:61' r1D1( ctx.cfg.maskTot ) = r1D1_in;
    e_end = ctx_cfg_maskTot_size[1];
    e_partialTrueCount = 0;
    for (int f_i{0}; f_i < e_end; f_i++) {
        if (ctx_cfg_maskTot_data[f_i]) {
            r1D1[f_i] = r1D1_in[e_partialTrueCount];
            e_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:62' r1D2( ctx.cfg.maskTot ) = r1D2_in;
    f_end = ctx_cfg_maskTot_size[1];
    f_partialTrueCount = 0;
    for (int g_i{0}; g_i < f_end; g_i++) {
        if (ctx_cfg_maskTot_data[g_i]) {
            r1D2[g_i] = r1D2_in[f_partialTrueCount];
            f_partialTrueCount++;
        }
    }
    // 'G2_Hermite_Interpolation_nAxis:64' D = zeros( N_AXES_MAX,1);
    for (int h_i{0}; h_i < 6; h_i++) {
        D[h_i] = 0.0;
    }
    // 'G2_Hermite_Interpolation_nAxis:65' D(ctx.cfg.maskTot) = ctx.cfg.D;
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
    // 'G2_Hermite_Interpolation_nAxis:67' status = int32(1);
    *status = 1;
    //  default success
    // 'G2_Hermite_Interpolation_nAxis:69' p5 = zeros(N_AXES_MAX,6);
    std::memset(&p5[0][0], 0, 36U * sizeof(double));
    // 'G2_Hermite_Interpolation_nAxis:71' alpha0 = 0;
    // 'G2_Hermite_Interpolation_nAxis:72' alpha1 = 0;
    //  compute Frenet frame
    // 'G2_Hermite_Interpolation_nAxis:75' [t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
    calc_t_nk_kappa(r0D1, r0D2, t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation_nAxis:76' [t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);
    calc_t_nk_kappa(r1D1, r1D2, t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    // 'G2_Hermite_Interpolation_nAxis:84' CoefPS = CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D);
    CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D, CoefPS);
    //
    // 'G2_Hermite_Interpolation_nAxis:86' a1     = CoefPS(1);
    // 'G2_Hermite_Interpolation_nAxis:87' a0     = CoefPS(2);
    // 'G2_Hermite_Interpolation_nAxis:88' b1     = CoefPS(3);
    // 'G2_Hermite_Interpolation_nAxis:89' b0     = CoefPS(4);
    // 'G2_Hermite_Interpolation_nAxis:90' c3     = CoefPS(5);
    // 'G2_Hermite_Interpolation_nAxis:91' c2     = CoefPS(6);
    // 'G2_Hermite_Interpolation_nAxis:92' c1     = CoefPS(7);
    // 'G2_Hermite_Interpolation_nAxis:93' c0     = CoefPS(8);
    // 'G2_Hermite_Interpolation_nAxis:94' d1     = CoefPS(9);
    // 'G2_Hermite_Interpolation_nAxis:95' d0     = CoefPS(10);
    // 'G2_Hermite_Interpolation_nAxis:96' e1     = CoefPS(11);
    // 'G2_Hermite_Interpolation_nAxis:97' e0     = CoefPS(12);
    // 'G2_Hermite_Interpolation_nAxis:98' f3     = CoefPS(13);
    // 'G2_Hermite_Interpolation_nAxis:99' f2     = CoefPS(14);
    // 'G2_Hermite_Interpolation_nAxis:100' f1     = CoefPS(15);
    // 'G2_Hermite_Interpolation_nAxis:101' f0     = CoefPS(16);
    // 'G2_Hermite_Interpolation_nAxis:102' TolZero = 1e-11;
    //
    // 'G2_Hermite_Interpolation_nAxis:104' if (kappa0 == 0) && (kappa1 == 0)
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        double b_CoefPS[2][2];
        double X[2];
        double c_CoefPS[2];
        //  degenerated case where the polynomial system degenerates to a linear one
        // 'G2_Hermite_Interpolation_nAxis:105' M       = [b0, c1;
        // 'G2_Hermite_Interpolation_nAxis:106'                f1, e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:108' B       = [-c0;
        // 'G2_Hermite_Interpolation_nAxis:109'                -f0];
        //
        // 'G2_Hermite_Interpolation_nAxis:111' X       = M \ B;
        b_CoefPS[0][0] = CoefPS[3];
        b_CoefPS[1][0] = CoefPS[6];
        b_CoefPS[0][1] = CoefPS[14];
        b_CoefPS[1][1] = CoefPS[11];
        c_CoefPS[0] = -CoefPS[7];
        c_CoefPS[1] = -CoefPS[15];
        coder::mldivide(b_CoefPS, c_CoefPS, X);
        //  resolution of linear system
        // 'G2_Hermite_Interpolation_nAxis:112' alpha0  = X(1);
        alpha0 = X[0];
        // 'G2_Hermite_Interpolation_nAxis:113' alpha1  = X(2);
        alpha1 = X[1];
        // 'G2_Hermite_Interpolation_nAxis:115' if ~((alpha0 > 0) && (alpha1 > 0))
        if ((X[0] > 0.0) && (X[1] > 0.0)) {
            // 'G2_Hermite_Interpolation_nAxis:119' [beta0, beta1] = Calc_beta0_beta1(alpha0,
            // alpha1, ... 'G2_Hermite_Interpolation_nAxis:120' r0D0, t0, n0, ...
            // 'G2_Hermite_Interpolation_nAxis:121'                                       r1D0, t1,
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
        // 'G2_Hermite_Interpolation_nAxis:122' elseif kappa0 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:124' Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0
        // + b1*f0 - c1*f1, b0*f0 - c0*f1];
        //
        // 'G2_Hermite_Interpolation_nAxis:126' alpha1_v = c_roots_(Coef);
        //  c_roots_ : Compute the square root
        //
        //  Inputs :
        //  coeffs        : Coefficient of the optimization
        //
        //  Outputs :
        //  Y             : Result for the square root
        // 'c_roots_:10' if coder.target('rtw')
        // 'c_roots_:11' Y = complex(zeros(numel(coeffs)-1, 1));
        alpha1_v[0].re = 0.0;
        alpha1_v[0].im = 0.0;
        alpha1_v[1].re = 0.0;
        alpha1_v[1].im = 0.0;
        alpha1_v[2].re = 0.0;
        alpha1_v[2].im = 0.0;
        // 'c_roots_:12' coder.cinclude('functions.h');
        // 'c_roots_:13' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        dv2[0] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
        dv2[1] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
        dv2[2] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
        dv2[3] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
        c_roots(&dv2[0], &alpha1_v[0], 4);
        //  all roots of 3th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:127' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
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
        for (int i3{0}; i3 < c_trueCount; i3++) {
            alpha1_t_data[i3] = alpha1_v[b_tmp_data[i3] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:129' if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:130' alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
            r10.set_size(c_trueCount);
            for (int i6{0}; i6 < c_trueCount; i6++) {
                r10[i6] = std::pow(alpha1_t_data[i6], 2.0);
            }
            if (r10.size(0) == c_trueCount) {
                double d_CoefPS;
                double f_CoefPS;
                double h_CoefPS;
                double j_CoefPS;
                int b_loop_ub;
                int scalarLB;
                int vectorUB;
                d_CoefPS = CoefPS[9];
                f_CoefPS = CoefPS[11];
                h_CoefPS = CoefPS[15];
                j_CoefPS = CoefPS[14];
                alpha0_t_size = r10.size(0);
                b_loop_ub = r10.size(0);
                scalarLB = (r10.size(0) / 2) << 1;
                vectorUB = scalarLB - 2;
                for (int i22{0}; i22 <= vectorUB; i22 += 2) {
                    __m128d r24;
                    __m128d r26;
                    r24 = _mm_loadu_pd(&(r10.data())[0]);
                    r26 = _mm_loadu_pd(&alpha1_t_data[0]);
                    _mm_storeu_pd(
                        &alpha0_t_data[0],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(d_CoefPS), r24),
                                                      _mm_mul_pd(_mm_set1_pd(f_CoefPS), r26)),
                                           _mm_set1_pd(h_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(j_CoefPS)));
                }
                for (int i22{scalarLB}; i22 < b_loop_ub; i22++) {
                    alpha0_t_data[i22] =
                        -((d_CoefPS * r10[i22] + f_CoefPS * alpha1_t_data[i22]) + h_CoefPS) /
                        j_CoefPS;
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r10, alpha1_t_data,
                                 &c_trueCount);
            }
        } else {
            int i16;
            int i20;
            int i24;
            // 'G2_Hermite_Interpolation_nAxis:131' else
            // 'G2_Hermite_Interpolation_nAxis:132' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            r10.set_size(c_trueCount);
            for (int i9{0}; i9 < c_trueCount; i9++) {
                r10[i9] = std::pow(alpha1_t_data[i9], 3.0);
            }
            r13.set_size(c_trueCount);
            for (int i13{0}; i13 < c_trueCount; i13++) {
                r13[i13] = std::pow(alpha1_t_data[i13], 2.0);
            }
            if (r10.size(0) == 1) {
                i16 = r13.size(0);
            } else {
                i16 = r10.size(0);
            }
            if (r10.size(0) == 1) {
                i20 = r13.size(0);
            } else {
                i20 = r10.size(0);
            }
            if (i20 == 1) {
                i24 = c_trueCount;
            } else if (r10.size(0) == 1) {
                i24 = r13.size(0);
            } else {
                i24 = r10.size(0);
            }
            if ((r10.size(0) == r13.size(0)) && (i16 == c_trueCount) && (i24 == c_trueCount)) {
                double n_CoefPS;
                double p_CoefPS;
                double r_CoefPS;
                double t_CoefPS;
                double v_CoefPS;
                double x_CoefPS;
                int c_scalarLB;
                int d_vectorUB;
                int f_loop_ub;
                n_CoefPS = CoefPS[4];
                p_CoefPS = CoefPS[5];
                r_CoefPS = CoefPS[6];
                t_CoefPS = CoefPS[7];
                v_CoefPS = CoefPS[2];
                x_CoefPS = CoefPS[3];
                alpha0_t_size = r10.size(0);
                f_loop_ub = r10.size(0);
                c_scalarLB = (r10.size(0) / 2) << 1;
                d_vectorUB = c_scalarLB - 2;
                for (int i31{0}; i31 <= d_vectorUB; i31 += 2) {
                    __m128d r29;
                    __m128d r32;
                    __m128d r34;
                    r29 = _mm_loadu_pd(&(r10.data())[0]);
                    r32 = _mm_loadu_pd(&(r13.data())[0]);
                    r34 = _mm_loadu_pd(&alpha1_t_data[0]);
                    _mm_storeu_pd(
                        &alpha0_t_data[0],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(n_CoefPS), r29),
                                                          _mm_mul_pd(_mm_set1_pd(p_CoefPS), r32)),
                                               _mm_mul_pd(_mm_set1_pd(r_CoefPS), r34)),
                                    _mm_set1_pd(t_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(v_CoefPS), r34),
                                       _mm_set1_pd(x_CoefPS))));
                }
                for (int i31{c_scalarLB}; i31 < f_loop_ub; i31++) {
                    double d1;
                    d1 = alpha1_t_data[i31];
                    alpha0_t_data[i31] =
                        -(((n_CoefPS * r10[i31] + p_CoefPS * r13[i31]) + r_CoefPS * d1) +
                          t_CoefPS) /
                        (v_CoefPS * d1 + x_CoefPS);
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, r10, r13, alpha1_t_data,
                                 &c_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:135' Idx       = find(alpha0_t > 0);
        for (int i18{0}; i18 < alpha0_t_size; i18++) {
            b_alpha0_t_data[i18] = (alpha0_t_data[i18] > 0.0);
        }
        c_alpha0_t_data.set(&b_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(c_alpha0_t_data, r23);
        k_i.set_size(r23.size(0));
        d_loop_ub = r23.size(0);
        for (int i26{0}; i26 < d_loop_ub; i26++) {
            k_i[i26] = r23[i26];
        }
        for (int i28{0}; i28 < alpha0_t_size; i28++) {
            b_alpha0_t_data[i28] = (alpha0_t_data[i28] > 0.0);
        }
        d_alpha0_t_data.set(&b_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(d_alpha0_t_data, r23);
        // 'G2_Hermite_Interpolation_nAxis:136' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:137' alpha0_u  = alpha0_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:139' if ~(numel(alpha0_u) > 0)
        if (r23.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:140' status = int32(3);
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:145' if length(alpha0_u) > 1
            if (r23.size(0) > 1) {
                int CostInt_size;
                int h_loop_ub;
                int i37;
                int j_loop_ub;
                int l_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:147' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r23.size(0));
                h_loop_ub = static_cast<signed char>(r23.size(0));
                if (h_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, h_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:148' beta0_u = zeros(size(alpha0_u));
                j_loop_ub = static_cast<signed char>(r23.size(0));
                if (j_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, j_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:149' beta1_u = zeros(size(alpha0_u));
                l_loop_ub = static_cast<signed char>(r23.size(0));
                if (l_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, l_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:151' for k = 1:length(alpha0_u)
                i37 = k_i.size(0);
                for (int b_k{0}; b_k < i37; b_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:153' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:154' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:155' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r23[b_k] - 1], alpha1_t_data[r23[b_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation_nAxis:156' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:157' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:158' r1D0, t1, n1, D);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[r23[b_k] - 1], beta0_u_data[b_k], alpha1_t_data[r23[b_k] - 1],
                        beta1_u_data[b_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:162' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &ex, &iindx);
                // 'G2_Hermite_Interpolation_nAxis:163' alpha0   = alpha0_u(Idx);
                alpha0_tmp = r23[iindx - 1] - 1;
                alpha0 = alpha0_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:164' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:165' beta0    = beta0_u(Idx);
                a = beta0_u_data[iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:166' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:168' else
                // 'G2_Hermite_Interpolation_nAxis:170' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:171' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:172' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:173' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:174' r1D0, t1, n1, D);
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
        // 'G2_Hermite_Interpolation_nAxis:178' elseif kappa1 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:180' Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1
        // - c0*e1 - b0*e0, c1*f0 - c0*e0];
        //
        // 'G2_Hermite_Interpolation_nAxis:182' alpha0_v  = c_roots_(Coef);
        //  c_roots_ : Compute the square root
        //
        //  Inputs :
        //  coeffs        : Coefficient of the optimization
        //
        //  Outputs :
        //  Y             : Result for the square root
        // 'c_roots_:10' if coder.target('rtw')
        // 'c_roots_:11' Y = complex(zeros(numel(coeffs)-1, 1));
        alpha0_v[0].re = 0.0;
        alpha0_v[0].im = 0.0;
        alpha0_v[1].re = 0.0;
        alpha0_v[1].im = 0.0;
        alpha0_v[2].re = 0.0;
        alpha0_v[2].im = 0.0;
        // 'c_roots_:12' coder.cinclude('functions.h');
        // 'c_roots_:13' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        dv2[0] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
        dv2[1] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
        dv2[2] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
        dv2[3] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
        c_roots(&dv2[0], &alpha0_v[0], 4);
        //  all roots of 3th degree polynomial in alpha0
        // 'G2_Hermite_Interpolation_nAxis:183' alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) <
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
        for (int i5{0}; i5 < d_trueCount; i5++) {
            alpha0_t_data[i5] = alpha0_v[b_tmp_data[i5] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation_nAxis:185' if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation_nAxis:186' alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
            r10.set_size(d_trueCount);
            for (int i8{0}; i8 < d_trueCount; i8++) {
                r10[i8] = std::pow(alpha0_t_data[i8], 2.0);
            }
            if (r10.size(0) == d_trueCount) {
                double e_CoefPS;
                double g_CoefPS;
                double i_CoefPS;
                double k_CoefPS;
                int b_scalarLB;
                int b_vectorUB;
                int c_loop_ub;
                e_CoefPS = CoefPS[1];
                g_CoefPS = CoefPS[3];
                i_CoefPS = CoefPS[7];
                k_CoefPS = CoefPS[6];
                alpha1_t_size = r10.size(0);
                c_loop_ub = r10.size(0);
                b_scalarLB = (r10.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (int i23{0}; i23 <= b_vectorUB; i23 += 2) {
                    __m128d r25;
                    __m128d r27;
                    r25 = _mm_loadu_pd(&(r10.data())[0]);
                    r27 = _mm_loadu_pd(&alpha0_t_data[0]);
                    _mm_storeu_pd(
                        &alpha1_t_data[0],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(e_CoefPS), r25),
                                                      _mm_mul_pd(_mm_set1_pd(g_CoefPS), r27)),
                                           _mm_set1_pd(i_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_set1_pd(k_CoefPS)));
                }
                for (int i23{b_scalarLB}; i23 < c_loop_ub; i23++) {
                    alpha1_t_data[i23] =
                        -((e_CoefPS * r10[i23] + g_CoefPS * alpha0_t_data[i23]) + i_CoefPS) /
                        k_CoefPS;
                }
            } else {
                e_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r10, alpha0_t_data,
                                   &d_trueCount);
            }
        } else {
            int i17;
            int i21;
            int i25;
            // 'G2_Hermite_Interpolation_nAxis:187' else
            // 'G2_Hermite_Interpolation_nAxis:188' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            r10.set_size(d_trueCount);
            for (int i11{0}; i11 < d_trueCount; i11++) {
                r10[i11] = std::pow(alpha0_t_data[i11], 3.0);
            }
            r13.set_size(d_trueCount);
            for (int i14{0}; i14 < d_trueCount; i14++) {
                r13[i14] = std::pow(alpha0_t_data[i14], 2.0);
            }
            if (r10.size(0) == 1) {
                i17 = r13.size(0);
            } else {
                i17 = r10.size(0);
            }
            if (r10.size(0) == 1) {
                i21 = r13.size(0);
            } else {
                i21 = r10.size(0);
            }
            if (i21 == 1) {
                i25 = d_trueCount;
            } else if (r10.size(0) == 1) {
                i25 = r13.size(0);
            } else {
                i25 = r10.size(0);
            }
            if ((r10.size(0) == r13.size(0)) && (i17 == d_trueCount) && (i25 == d_trueCount)) {
                double o_CoefPS;
                double q_CoefPS;
                double s_CoefPS;
                double u_CoefPS;
                double w_CoefPS;
                double y_CoefPS;
                int d_scalarLB;
                int f_vectorUB;
                int g_loop_ub;
                o_CoefPS = CoefPS[12];
                q_CoefPS = CoefPS[13];
                s_CoefPS = CoefPS[14];
                u_CoefPS = CoefPS[15];
                w_CoefPS = CoefPS[10];
                y_CoefPS = CoefPS[11];
                alpha1_t_size = r10.size(0);
                g_loop_ub = r10.size(0);
                d_scalarLB = (r10.size(0) / 2) << 1;
                f_vectorUB = d_scalarLB - 2;
                for (int i33{0}; i33 <= f_vectorUB; i33 += 2) {
                    __m128d r31;
                    __m128d r33;
                    __m128d r35;
                    r31 = _mm_loadu_pd(&(r10.data())[0]);
                    r33 = _mm_loadu_pd(&(r13.data())[0]);
                    r35 = _mm_loadu_pd(&alpha0_t_data[0]);
                    _mm_storeu_pd(
                        &alpha1_t_data[0],
                        _mm_div_pd(
                            _mm_mul_pd(
                                _mm_add_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(o_CoefPS), r31),
                                                          _mm_mul_pd(_mm_set1_pd(q_CoefPS), r33)),
                                               _mm_mul_pd(_mm_set1_pd(s_CoefPS), r35)),
                                    _mm_set1_pd(u_CoefPS)),
                                _mm_set1_pd(-1.0)),
                            _mm_add_pd(_mm_mul_pd(_mm_set1_pd(w_CoefPS), r35),
                                       _mm_set1_pd(y_CoefPS))));
                }
                for (int i33{d_scalarLB}; i33 < g_loop_ub; i33++) {
                    double d2;
                    d2 = alpha0_t_data[i33];
                    alpha1_t_data[i33] =
                        -(((o_CoefPS * r10[i33] + q_CoefPS * r13[i33]) + s_CoefPS * d2) +
                          u_CoefPS) /
                        (w_CoefPS * d2 + y_CoefPS);
                }
            } else {
                e_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, r10, r13, alpha0_t_data,
                                   &d_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation_nAxis:191' Idx      = find(alpha1_t > 0);
        for (int i19{0}; i19 < alpha1_t_size; i19++) {
            b_alpha1_t_data[i19] = (alpha1_t_data[i19] > 0.0);
        }
        c_alpha1_t_data.set(&b_alpha1_t_data[0], alpha1_t_size);
        coder::c_eml_find(c_alpha1_t_data, r23);
        k_i.set_size(r23.size(0));
        e_loop_ub = r23.size(0);
        for (int i27{0}; i27 < e_loop_ub; i27++) {
            k_i[i27] = r23[i27];
        }
        for (int i29{0}; i29 < alpha1_t_size; i29++) {
            b_alpha1_t_data[i29] = (alpha1_t_data[i29] > 0.0);
        }
        d_alpha1_t_data.set(&b_alpha1_t_data[0], alpha1_t_size);
        coder::c_eml_find(d_alpha1_t_data, r23);
        // 'G2_Hermite_Interpolation_nAxis:192' alpha1_u = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:193' alpha0_u = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:195' if ~(numel(alpha0_u) > 0)
        if (r23.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:196' status = int32(4);
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:201' if length(alpha0_u) > 1
            if (r23.size(0) > 1) {
                int CostInt_size;
                int i38;
                int i_loop_ub;
                int k_loop_ub;
                int m_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:202' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r23.size(0));
                i_loop_ub = static_cast<signed char>(r23.size(0));
                if (i_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, i_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:203' beta0_u = zeros(size(alpha0_u));
                k_loop_ub = static_cast<signed char>(r23.size(0));
                if (k_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, k_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:204' beta1_u = zeros(size(alpha0_u));
                m_loop_ub = static_cast<signed char>(r23.size(0));
                if (m_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, m_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:206' for k = 1:length(alpha0_u)
                i38 = k_i.size(0);
                for (int c_k{0}; c_k < i38; c_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:207' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:208' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:209' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r23[c_k] - 1], alpha1_t_data[r23[c_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[c_k],
                                     &beta1_u_data[c_k]);
                    // 'G2_Hermite_Interpolation_nAxis:210' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:211' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:212' r1D0, t1, n1, D);
                    CostInt_data[c_k] = EvalCostIntegral(
                        alpha0_t_data[r23[c_k] - 1], beta0_u_data[c_k], alpha1_t_data[r23[c_k] - 1],
                        beta1_u_data[c_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int b_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:214' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &b_ex, &b_iindx);
                // 'G2_Hermite_Interpolation_nAxis:215' alpha0   = alpha0_u(Idx);
                b_alpha0_tmp = r23[b_iindx - 1] - 1;
                alpha0 = alpha0_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:216' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:217' beta0    = beta0_u(Idx);
                a = beta0_u_data[b_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:218' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:220' else
                // 'G2_Hermite_Interpolation_nAxis:222' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:223' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:224' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:225' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:226' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[k_i[0] - 1], alpha1_t_data[k_i[0] - 1], r0D0, t0, n0,
                                 r1D0, t1, n1, D, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else {
        double dv[10];
        double dv1[10];
        double ab_CoefPS;
        double bb_CoefPS;
        double cb_CoefPS;
        double db_CoefPS;
        double l_CoefPS;
        double m_CoefPS;
        int b_t12_size;
        int c_vectorUB;
        int e_trueCount;
        int e_vectorUB;
        int f_trueCount;
        int g_trueCount;
        int g_vectorUB;
        int h_partialTrueCount;
        int h_trueCount;
        int i42;
        int i43;
        int i_trueCount;
        int j_trueCount;
        int k_trueCount;
        int l_trueCount;
        int loop_ub;
        int m_trueCount;
        int n_loop_ub;
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
        int y_trueCount;
        // 'G2_Hermite_Interpolation_nAxis:230' else
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation_nAxis:232' Coef = CharPolyAlpha1(CoefPS);
        //
        // 'G2_Hermite_Interpolation_nAxis:234' alpha1_v = c_roots_(Coef);
        //  c_roots_ : Compute the square root
        //
        //  Inputs :
        //  coeffs        : Coefficient of the optimization
        //
        //  Outputs :
        //  Y             : Result for the square root
        // 'c_roots_:10' if coder.target('rtw')
        // 'c_roots_:11' Y = complex(zeros(numel(coeffs)-1, 1));
        std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
        // 'c_roots_:12' coder.cinclude('functions.h');
        // 'c_roots_:13' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        CharPolyAlpha1(CoefPS, dv);
        for (int i1{0}; i1 < 10; i1++) {
            dv1[i1] = dv[9 - i1];
        }
        c_roots(&dv1[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation_nAxis:235' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) <
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
        // 'G2_Hermite_Interpolation_nAxis:238' alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
        // CalcAlpha0
        //     ALPHA0_S = CalcAlpha0(ALPHA1,IN2)
        //     This function was generated by the Symbolic Math Toolbox version 9.1.
        //     11-Oct-2023 13:05:42
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
        r10.set_size(b_trueCount);
        for (int i10{0}; i10 < b_trueCount; i10++) {
            r10[i10] = std::pow(alpha1_t_data[i10], 2.0);
        }
        t5_size = r10.size(0);
        loop_ub = r10.size(0);
        for (int i15{0}; i15 < loop_ub; i15++) {
            t5_data[i15] = r10[i15];
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        l_CoefPS = CoefPS[3];
        m_CoefPS = CoefPS[2];
        scalarLB_tmp = (b_trueCount / 2) << 1;
        c_vectorUB = scalarLB_tmp - 2;
        for (int i30{0}; i30 <= c_vectorUB; i30 += 2) {
            __m128d r28;
            r28 = _mm_loadu_pd(&alpha1_t_data[i30]);
            _mm_storeu_pd(&t10_data[i30], _mm_add_pd(_mm_set1_pd(l_CoefPS),
                                                     _mm_mul_pd(r28, _mm_set1_pd(m_CoefPS))));
        }
        for (int i30{scalarLB_tmp}; i30 < b_trueCount; i30++) {
            t10_data[i30] = l_CoefPS + alpha1_t_data[i30] * m_CoefPS;
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        ab_CoefPS = CoefPS[1];
        bb_CoefPS = CoefPS[0];
        z.set_size(b_trueCount);
        e_vectorUB = scalarLB_tmp - 2;
        for (int i32{0}; i32 <= e_vectorUB; i32 += 2) {
            __m128d r30;
            r30 = _mm_loadu_pd(&alpha1_t_data[i32]);
            _mm_storeu_pd(&z[i32], _mm_div_pd(_mm_set1_pd(1.0),
                                              _mm_add_pd(_mm_set1_pd(ab_CoefPS),
                                                         _mm_mul_pd(_mm_set1_pd(bb_CoefPS), r30))));
        }
        for (int i32{scalarLB_tmp}; i32 < b_trueCount; i32++) {
            z[i32] = 1.0 / (ab_CoefPS + bb_CoefPS * alpha1_t_data[i32]);
        }
        cb_CoefPS = CoefPS[1];
        db_CoefPS = CoefPS[0];
        g_vectorUB = scalarLB_tmp - 2;
        for (int i34{0}; i34 <= g_vectorUB; i34 += 2) {
            __m128d r36;
            r36 = _mm_loadu_pd(&alpha1_t_data[i34]);
            _mm_storeu_pd(
                &t11_data[i34],
                _mm_div_pd(_mm_set1_pd(1.0), _mm_add_pd(_mm_set1_pd(cb_CoefPS),
                                                        _mm_mul_pd(_mm_set1_pd(db_CoefPS), r36))));
        }
        for (int i34{scalarLB_tmp}; i34 < b_trueCount; i34++) {
            t11_data[i34] = 1.0 / (cb_CoefPS + db_CoefPS * alpha1_t_data[i34]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        r10.set_size(b_trueCount);
        for (int i35{0}; i35 < b_trueCount; i35++) {
            r10[i35] = std::pow(alpha1_t_data[i35], 2.0);
        }
        r13.set_size(b_trueCount);
        for (int i36{0}; i36 < b_trueCount; i36++) {
            r13[i36] = std::pow(alpha1_t_data[i36], 3.0);
        }
        if (b_trueCount == 1) {
            e_trueCount = r10.size(0);
        } else {
            e_trueCount = b_trueCount;
        }
        if ((b_trueCount == r10.size(0)) && (e_trueCount == r13.size(0))) {
            double eb_CoefPS;
            double fb_CoefPS;
            double gb_CoefPS;
            double hb_CoefPS;
            int h_vectorUB;
            eb_CoefPS = CoefPS[7];
            fb_CoefPS = CoefPS[6];
            gb_CoefPS = CoefPS[5];
            hb_CoefPS = CoefPS[4];
            t12_size = b_trueCount;
            h_vectorUB = scalarLB_tmp - 2;
            for (int i41{0}; i41 <= h_vectorUB; i41 += 2) {
                __m128d r37;
                __m128d r38;
                __m128d r39;
                r37 = _mm_loadu_pd(&alpha1_t_data[i41]);
                r38 = _mm_loadu_pd(&r10[i41]);
                r39 = _mm_loadu_pd(&r13[i41]);
                _mm_storeu_pd(
                    &t12_data[i41],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_set1_pd(eb_CoefPS),
                                                     _mm_mul_pd(r37, _mm_set1_pd(fb_CoefPS))),
                                          _mm_mul_pd(_mm_set1_pd(gb_CoefPS), r38)),
                               _mm_mul_pd(_mm_set1_pd(hb_CoefPS), r39)));
            }
            for (int i41{scalarLB_tmp}; i41 < b_trueCount; i41++) {
                t12_data[i41] =
                    ((eb_CoefPS + alpha1_t_data[i41] * fb_CoefPS) + gb_CoefPS * r10[i41]) +
                    hb_CoefPS * r13[i41];
            }
        } else {
            binary_expand_op(t12_data, &t12_size, CoefPS, alpha1_t_data, &b_trueCount, r10, r13);
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        r10.set_size(b_trueCount);
        for (int i39{0}; i39 < b_trueCount; i39++) {
            r10[i39] = std::pow(t11_data[i39], 2.0);
        }
        r13.set_size(b_trueCount);
        for (int i40{0}; i40 < b_trueCount; i40++) {
            r13[i40] = std::pow(t10_data[i40], 2.0);
        }
        if (b_trueCount == 1) {
            f_trueCount = t5_size;
            g_trueCount = t12_size;
            h_trueCount = r10.size(0);
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
            k_trueCount = r10.size(0);
        } else {
            k_trueCount = b_trueCount;
        }
        if (k_trueCount == 1) {
            l_trueCount = t12_size;
        } else if (b_trueCount == 1) {
            l_trueCount = r10.size(0);
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
        if (r13.size(0) == 1) {
            i42 = b_trueCount;
        } else {
            i42 = r13.size(0);
        }
        if (t12_size == 1) {
            if (r13.size(0) == 1) {
                b_t12_size = b_trueCount;
            } else {
                b_t12_size = r13.size(0);
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
                if (r13.size(0) == 1) {
                    i43 = b_trueCount;
                } else {
                    i43 = r13.size(0);
                }
            } else {
                i43 = t12_size;
            }
        } else {
            i43 = z.size(0);
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
            s_trueCount = r10.size(0);
            t_trueCount = t5_size;
        } else {
            s_trueCount = b_trueCount;
            t_trueCount = b_trueCount;
        }
        if (r_trueCount == 1) {
            if (s_trueCount == 1) {
                u_trueCount = t12_size;
            } else if (b_trueCount == 1) {
                u_trueCount = r10.size(0);
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
                    if (r13.size(0) == 1) {
                        y_trueCount = b_trueCount;
                    } else {
                        y_trueCount = r13.size(0);
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
            (b_trueCount == r10.size(0)) && (h_trueCount == t12_size) &&
            (j_trueCount == l_trueCount) && (b_trueCount == t5_size) &&
            (b_trueCount == z.size(0)) && (m_trueCount == n_trueCount) &&
            (r13.size(0) == b_trueCount) && (t12_size == i42) && (z.size(0) == b_t12_size) &&
            (p_trueCount == i43) && (u_trueCount == y_trueCount)) {
            double ib_CoefPS;
            double jb_CoefPS;
            double kb_CoefPS;
            double lb_CoefPS;
            double mb_CoefPS;
            double nb_CoefPS;
            double ob_CoefPS;
            double pb_CoefPS;
            double qb_CoefPS;
            double rb_CoefPS;
            int i_vectorUB;
            ib_CoefPS = CoefPS[15];
            jb_CoefPS = CoefPS[11];
            kb_CoefPS = CoefPS[9];
            lb_CoefPS = CoefPS[13];
            mb_CoefPS = CoefPS[12];
            nb_CoefPS = CoefPS[14];
            ob_CoefPS = CoefPS[10];
            pb_CoefPS = CoefPS[8];
            qb_CoefPS = CoefPS[13];
            rb_CoefPS = CoefPS[12];
            alpha0_t_size = b_trueCount;
            i_vectorUB = scalarLB_tmp - 2;
            for (int i46{0}; i46 <= i_vectorUB; i46 += 2) {
                __m128d r40;
                __m128d r41;
                __m128d r42;
                __m128d r43;
                __m128d r44;
                __m128d r45;
                __m128d r46;
                __m128d r47;
                r40 = _mm_loadu_pd(&alpha1_t_data[i46]);
                r41 = _mm_loadu_pd(&t5_data[i46]);
                r42 = _mm_loadu_pd(&t11_data[i46]);
                r43 = _mm_loadu_pd(&t12_data[i46]);
                r44 = _mm_loadu_pd(&t10_data[i46]);
                r45 = _mm_loadu_pd(&r10[i46]);
                r46 = _mm_loadu_pd(&z[i46]);
                r47 = _mm_loadu_pd(&r13[i46]);
                _mm_storeu_pd(
                    &alpha0_t_data[i46],
                    _mm_div_pd(
                        _mm_mul_pd(
                            _mm_add_pd(
                                _mm_sub_pd(
                                    _mm_add_pd(_mm_add_pd(_mm_set1_pd(ib_CoefPS),
                                                          _mm_mul_pd(r40, _mm_set1_pd(jb_CoefPS))),
                                               _mm_mul_pd(_mm_set1_pd(kb_CoefPS), r41)),
                                    _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(lb_CoefPS), r42), r43)),
                                _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(mb_CoefPS), r44), r45),
                                           r43)),
                            _mm_set1_pd(-1.0)),
                        _mm_sub_pd(
                            _mm_sub_pd(
                                _mm_add_pd(_mm_add_pd(_mm_set1_pd(nb_CoefPS),
                                                      _mm_mul_pd(r40, _mm_set1_pd(ob_CoefPS))),
                                           _mm_mul_pd(_mm_set1_pd(pb_CoefPS), r41)),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(qb_CoefPS), r44), r46)),
                            _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(rb_CoefPS), r46),
                                       _mm_sub_pd(r43, _mm_mul_pd(r47, r42))))));
            }
            for (int i46{scalarLB_tmp}; i46 < b_trueCount; i46++) {
                double d3;
                double d4;
                double d5;
                double d6;
                double d7;
                d3 = alpha1_t_data[i46];
                d4 = t5_data[i46];
                d5 = t11_data[i46];
                d6 = t12_data[i46];
                d7 = t10_data[i46];
                alpha0_t_data[i46] =
                    -((((ib_CoefPS + d3 * jb_CoefPS) + kb_CoefPS * d4) - lb_CoefPS * d5 * d6) +
                      mb_CoefPS * d7 * r10[i46] * d6) /
                    ((((nb_CoefPS + d3 * ob_CoefPS) + pb_CoefPS * d4) - qb_CoefPS * d7 * z[i46]) -
                     rb_CoefPS * z[i46] * (d6 - r13[i46] * d5));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &b_trueCount,
                             t5_data, &t5_size, t11_data, &b_trueCount, t12_data, &t12_size,
                             t10_data, &b_trueCount, r10, z, r13);
        }
        //
        // 'G2_Hermite_Interpolation_nAxis:240' Idx       = find(alpha0_t > 0);
        for (int i44{0}; i44 < alpha0_t_size; i44++) {
            e_alpha0_t_data[i44] = (alpha0_t_data[i44] > 0.0);
        }
        f_alpha0_t_data.set(&e_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(f_alpha0_t_data, r23);
        k_i.set_size(r23.size(0));
        n_loop_ub = r23.size(0);
        for (int i45{0}; i45 < n_loop_ub; i45++) {
            k_i[i45] = r23[i45];
        }
        for (int i47{0}; i47 < alpha0_t_size; i47++) {
            e_alpha0_t_data[i47] = (alpha0_t_data[i47] > 0.0);
        }
        g_alpha0_t_data.set(&e_alpha0_t_data[0], alpha0_t_size);
        coder::c_eml_find(g_alpha0_t_data, r23);
        // 'G2_Hermite_Interpolation_nAxis:241' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation_nAxis:242' alpha0_u  = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation_nAxis:244' if ~(numel(alpha0_u) > 0)
        if (r23.size(0) <= 0) {
            // 'G2_Hermite_Interpolation_nAxis:245' status = int32(5);
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation_nAxis:250' if length(alpha0_u) > 1
            if (r23.size(0) > 1) {
                int CostInt_size;
                int i48;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;
                // 'G2_Hermite_Interpolation_nAxis:252' CostInt = zeros(size(alpha0_u));
                CostInt_size = static_cast<signed char>(r23.size(0));
                o_loop_ub = static_cast<signed char>(r23.size(0));
                if (o_loop_ub - 1 >= 0) {
                    std::memset(&CostInt_data[0], 0, o_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:253' beta0_u = zeros(size(alpha0_u));
                p_loop_ub = static_cast<signed char>(r23.size(0));
                if (p_loop_ub - 1 >= 0) {
                    std::memset(&beta0_u_data[0], 0, p_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:254' beta1_u = zeros(size(alpha0_u));
                q_loop_ub = static_cast<signed char>(r23.size(0));
                if (q_loop_ub - 1 >= 0) {
                    std::memset(&beta1_u_data[0], 0, q_loop_ub * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation_nAxis:256' for k = 1:length(alpha0_u)
                i48 = k_i.size(0);
                for (int d_k{0}; d_k < i48; d_k++) {
                    // 'G2_Hermite_Interpolation_nAxis:258' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:259' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:260' r1D0, t1, n1, D);
                    Calc_beta0_beta1(alpha0_t_data[r23[d_k] - 1], alpha1_t_data[r23[d_k] - 1], r0D0,
                                     t0, n0, r1D0, t1, n1, D, &beta0_u_data[d_k],
                                     &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation_nAxis:261' CostInt(k)     =
                    // EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                    // 'G2_Hermite_Interpolation_nAxis:262' r0D0, t0, n0, ...
                    // 'G2_Hermite_Interpolation_nAxis:263' r1D0, t1, n1, D);
                    CostInt_data[d_k] = EvalCostIntegral(
                        alpha0_t_data[r23[d_k] - 1], beta0_u_data[d_k], alpha1_t_data[r23[d_k] - 1],
                        beta1_u_data[d_k], r0D0, t0, n0, r1D0, t1, n1, D);
                }
                int c_alpha0_tmp;
                // 'G2_Hermite_Interpolation_nAxis:267' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data, CostInt_size, &c_ex, &c_iindx);
                // 'G2_Hermite_Interpolation_nAxis:268' alpha0   = alpha0_u(Idx);
                c_alpha0_tmp = r23[c_iindx - 1] - 1;
                alpha0 = alpha0_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:269' alpha1   = alpha1_u(Idx);
                alpha1 = alpha1_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation_nAxis:270' beta0    = beta0_u(Idx);
                a = beta0_u_data[c_iindx - 1];
                // 'G2_Hermite_Interpolation_nAxis:271' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation_nAxis:273' else
                // 'G2_Hermite_Interpolation_nAxis:275' alpha0   = alpha0_u(1);
                alpha0 = alpha0_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:276' alpha1   = alpha1_u(1);
                alpha1 = alpha1_t_data[r23[0] - 1];
                // 'G2_Hermite_Interpolation_nAxis:277' [beta0, beta1] = Calc_beta0_beta1(alpha0,
                // alpha1, ... 'G2_Hermite_Interpolation_nAxis:278' r0D0, t0, n0, ...
                // 'G2_Hermite_Interpolation_nAxis:279' r1D0, t1, n1, D);
                Calc_beta0_beta1(alpha0_t_data[k_i[0] - 1], alpha1_t_data[k_i[0] - 1], r0D0, t0, n0,
                                 r1D0, t1, n1, D, &a, &b_a);
            }
            guard1 = true;
        }
    }
    if (guard1) {
        __m128d r;
        __m128d r2;
        __m128d r7;
        __m128d r9;
        double a_tmp;
        double b_a_tmp;
        //
        //  Hermite basis
        // 'G2_Hermite_Interpolation_nAxis:286' h00 = [-6,    15,   -10,     0,     0,     1];
        // 'G2_Hermite_Interpolation_nAxis:287' h10 = [-3,     8,    -6,     0,     1,     0];
        // 'G2_Hermite_Interpolation_nAxis:288' h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
        // 'G2_Hermite_Interpolation_nAxis:289' h01 = [6,   -15,     10,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:290' h11 = [-3,    7,     -4,     0,     0,     0];
        // 'G2_Hermite_Interpolation_nAxis:291' h21 = [0.5,  -1,    0.5,     0,     0,     0];
        //  evaluate coefficients as sum of basis functions
        // 'G2_Hermite_Interpolation_nAxis:293' p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 +
        // alpha0^2*n0) * h20 + ... 'G2_Hermite_Interpolation_nAxis:294'      r1D0 * h01 + alpha1*t1
        // * h11 + (beta1*t1 + alpha1^2*n1) * h21;
        a_tmp = alpha0 * alpha0;
        b_a_tmp = alpha1 * alpha1;
        r = _mm_set1_pd(alpha0);
        for (int i2{0}; i2 < 6; i2++) {
            __m128d r1;
            __m128d r3;
            __m128d r4;
            __m128d r6;
            r1 = _mm_loadu_pd(&r0D0[0]);
            r3 = _mm_set1_pd(static_cast<double>(b_b[i2]));
            _mm_storeu_pd(&b_r0D0[i2][0], _mm_mul_pd(r1, r3));
            r4 = _mm_loadu_pd(&t0[0]);
            r6 = _mm_set1_pd(static_cast<double>(c_b[i2]));
            _mm_storeu_pd(&b_alpha0[i2][0], _mm_mul_pd(_mm_mul_pd(r, r4), r6));
            r1 = _mm_loadu_pd(&r0D0[2]);
            _mm_storeu_pd(&b_r0D0[i2][2], _mm_mul_pd(r1, r3));
            r4 = _mm_loadu_pd(&t0[2]);
            _mm_storeu_pd(&b_alpha0[i2][2], _mm_mul_pd(_mm_mul_pd(r, r4), r6));
            r1 = _mm_loadu_pd(&r0D0[4]);
            _mm_storeu_pd(&b_r0D0[i2][4], _mm_mul_pd(r1, r3));
            r4 = _mm_loadu_pd(&t0[4]);
            _mm_storeu_pd(&b_alpha0[i2][4], _mm_mul_pd(_mm_mul_pd(r, r4), r6));
            c_a[i2] = a * t0[i2] + a_tmp * n0[i2];
        }
        r2 = _mm_set1_pd(0.0);
        for (int i4{0}; i4 < 6; i4++) {
            __m128d r11;
            __m128d r12;
            __m128d r15;
            __m128d r18;
            __m128d r5;
            __m128d r8;
            r5 = _mm_loadu_pd(&c_a[0]);
            r8 = _mm_loadu_pd(&b_r0D0[i4][0]);
            r11 = _mm_loadu_pd(&b_alpha0[i4][0]);
            r12 = _mm_set1_pd(d_b[i4]);
            _mm_storeu_pd(&c_r0D0[i4][0],
                          _mm_add_pd(_mm_add_pd(r8, r11), _mm_add_pd(r2, _mm_mul_pd(r5, r12))));
            r15 = _mm_loadu_pd(&r1D0[0]);
            r18 = _mm_set1_pd(static_cast<double>(e_b[i4]));
            _mm_storeu_pd(&b_r1D0[i4][0], _mm_mul_pd(r15, r18));
            r5 = _mm_loadu_pd(&c_a[2]);
            r8 = _mm_loadu_pd(&b_r0D0[i4][2]);
            r11 = _mm_loadu_pd(&b_alpha0[i4][2]);
            _mm_storeu_pd(&c_r0D0[i4][2],
                          _mm_add_pd(_mm_add_pd(r8, r11), _mm_add_pd(r2, _mm_mul_pd(r5, r12))));
            r15 = _mm_loadu_pd(&r1D0[2]);
            _mm_storeu_pd(&b_r1D0[i4][2], _mm_mul_pd(r15, r18));
            r5 = _mm_loadu_pd(&c_a[4]);
            r8 = _mm_loadu_pd(&b_r0D0[i4][4]);
            r11 = _mm_loadu_pd(&b_alpha0[i4][4]);
            _mm_storeu_pd(&c_r0D0[i4][4],
                          _mm_add_pd(_mm_add_pd(r8, r11), _mm_add_pd(r2, _mm_mul_pd(r5, r12))));
            r15 = _mm_loadu_pd(&r1D0[4]);
            _mm_storeu_pd(&b_r1D0[i4][4], _mm_mul_pd(r15, r18));
        }
        r7 = _mm_set1_pd(alpha1);
        r9 = _mm_set1_pd(0.0);
        for (int i7{0}; i7 < 6; i7++) {
            __m128d r14;
            __m128d r17;
            __m128d r20;
            __m128d r22;
            c_a[i7] = b_a * t1[i7] + b_a_tmp * n1[i7];
            r14 = _mm_loadu_pd(&t1[0]);
            r17 = _mm_loadu_pd(&c_r0D0[i7][0]);
            r20 = _mm_loadu_pd(&b_r1D0[i7][0]);
            r22 = _mm_set1_pd(static_cast<double>(g_b[i7]));
            _mm_storeu_pd(&b_r0D0[i7][0],
                          _mm_add_pd(_mm_add_pd(r17, r20),
                                     _mm_add_pd(r9, _mm_mul_pd(_mm_mul_pd(r7, r14), r22))));
            r14 = _mm_loadu_pd(&t1[2]);
            r17 = _mm_loadu_pd(&c_r0D0[i7][2]);
            r20 = _mm_loadu_pd(&b_r1D0[i7][2]);
            _mm_storeu_pd(&b_r0D0[i7][2],
                          _mm_add_pd(_mm_add_pd(r17, r20),
                                     _mm_add_pd(r9, _mm_mul_pd(_mm_mul_pd(r7, r14), r22))));
            r14 = _mm_loadu_pd(&t1[4]);
            r17 = _mm_loadu_pd(&c_r0D0[i7][4]);
            r20 = _mm_loadu_pd(&b_r1D0[i7][4]);
            _mm_storeu_pd(&b_r0D0[i7][4],
                          _mm_add_pd(_mm_add_pd(r17, r20),
                                     _mm_add_pd(r9, _mm_mul_pd(_mm_mul_pd(r7, r14), r22))));
        }
        for (int i12{0}; i12 < 6; i12++) {
            __m128d r16;
            __m128d r19;
            __m128d r21;
            r16 = _mm_loadu_pd(&c_a[0]);
            r19 = _mm_loadu_pd(&b_r0D0[i12][0]);
            r21 = _mm_set1_pd(f_b[i12]);
            _mm_storeu_pd(&p5[i12][0], _mm_add_pd(r19, _mm_mul_pd(r16, r21)));
            r16 = _mm_loadu_pd(&c_a[2]);
            r19 = _mm_loadu_pd(&b_r0D0[i12][2]);
            _mm_storeu_pd(&p5[i12][2], _mm_add_pd(r19, _mm_mul_pd(r16, r21)));
            r16 = _mm_loadu_pd(&c_a[4]);
            r19 = _mm_loadu_pd(&b_r0D0[i12][4]);
            _mm_storeu_pd(&p5[i12][4], _mm_add_pd(r19, _mm_mul_pd(r16, r21)));
        }
        //  last cross check ...
        // 'G2_Hermite_Interpolation_nAxis:296' p1val = (a1*alpha1+a0)*alpha0^2  +
        // (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
        // 'G2_Hermite_Interpolation_nAxis:297' p2val = (d1*alpha0+d0)*alpha1^2  +
        // (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        // 'G2_Hermite_Interpolation_nAxis:299' if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
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
            // 'G2_Hermite_Interpolation_nAxis:300' status = int32(6);
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
