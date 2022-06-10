//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "G2_Hermite_Interpolation.h"
#include "CalcAlpha0.h"
#include "CalcFrenet.h"
#include "Calc_beta0_beta1.h"
#include "CoefPolySys.h"
#include "EvalCostIntegral.h"
#include "div.h"
#include "find.h"
#include "minOrMax.h"
#include "coder_array.h"
#include "functions.h"
#include <cmath>
#include <cstring>

// Function Declarations
namespace ocn {
static void b_binary_expand_op(double alpha1_t_data[], int *alpha1_t_size, const double CoefPS[16],
                               const ::coder::array<double, 1U> &r, const double alpha0_t_data[],
                               const int *alpha0_t_size);

static void binary_expand_op(double alpha0_t_data[], int *alpha0_t_size, const double CoefPS[16],
                             const ::coder::array<double, 1U> &r, const double alpha1_t_data[],
                             const int *alpha1_t_size);

static void binary_expand_op(double p5_3D[6][3], const ::coder::array<double, 1U> &r0D0,
                             const signed char b[6], double alpha0, const double t0[3],
                             const signed char b_b[6], double a, double b_a, const double n0[3],
                             const double c_b[6], const ::coder::array<double, 1U> &r1D0,
                             const signed char d_b[6], double alpha1, const double t1[3],
                             const signed char e_b[6], double c_a, double d_a, const double n1[3],
                             const double f_b[6]);

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
// Arguments    : double p5_3D[6][3]
//                const ::coder::array<double, 1U> &r0D0
//                const signed char b[6]
//                double alpha0
//                const double t0[3]
//                const signed char b_b[6]
//                double a
//                double b_a
//                const double n0[3]
//                const double c_b[6]
//                const ::coder::array<double, 1U> &r1D0
//                const signed char d_b[6]
//                double alpha1
//                const double t1[3]
//                const signed char e_b[6]
//                double c_a
//                double d_a
//                const double n1[3]
//                const double f_b[6]
// Return Type  : void
//
static void binary_expand_op(double p5_3D[6][3], const ::coder::array<double, 1U> &r0D0,
                             const signed char b[6], double alpha0, const double t0[3],
                             const signed char b_b[6], double a, double b_a, const double n0[3],
                             const double c_b[6], const ::coder::array<double, 1U> &r1D0,
                             const signed char d_b[6], double alpha1, const double t1[3],
                             const signed char e_b[6], double c_a, double d_a, const double n1[3],
                             const double f_b[6])
{
    ::coder::array<double, 2U> b_r0D0;
    ::coder::array<double, 2U> b_r1D0;
    double b_alpha0[6][3];
    double b_alpha1[6][3];
    double e_a[6][3];
    double a_idx_0;
    double a_idx_1;
    double a_idx_2;
    int b_loop_ub;
    int loop_ub;
    int stride_0_0;
    int stride_2_0;
    b_r0D0.set_size(r0D0.size(0), 6);
    loop_ub = r0D0.size(0);
    a_idx_0 = a * t0[0] + b_a * n0[0];
    a_idx_1 = a * t0[1] + b_a * n0[1];
    a_idx_2 = a * t0[2] + b_a * n0[2];
    b_r1D0.set_size(r1D0.size(0), 6);
    b_loop_ub = r1D0.size(0);
    for (int i{0}; i < 6; i++) {
        for (int i1{0}; i1 < loop_ub; i1++) {
            b_r0D0[i1 + b_r0D0.size(0) * i] = r0D0[i1] * static_cast<double>(b[i]);
        }
        int alpha0_tmp;
        alpha0_tmp = b_b[i];
        b_alpha0[i][0] = alpha0 * t0[0] * static_cast<double>(alpha0_tmp);
        b_alpha0[i][1] = alpha0 * t0[1] * static_cast<double>(alpha0_tmp);
        b_alpha0[i][2] = alpha0 * t0[2] * static_cast<double>(alpha0_tmp);
        e_a[i][0] = a_idx_0 * c_b[i];
        e_a[i][1] = a_idx_1 * c_b[i];
        e_a[i][2] = a_idx_2 * c_b[i];
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            b_r1D0[i3 + b_r1D0.size(0) * i] = r1D0[i3] * static_cast<double>(d_b[i]);
        }
        int alpha1_tmp;
        alpha1_tmp = e_b[i];
        b_alpha1[i][0] = alpha1 * t1[0] * static_cast<double>(alpha1_tmp);
        b_alpha1[i][1] = alpha1 * t1[1] * static_cast<double>(alpha1_tmp);
        b_alpha1[i][2] = alpha1 * t1[2] * static_cast<double>(alpha1_tmp);
    }
    a_idx_0 = c_a * t1[0] + d_a * n1[0];
    a_idx_1 = c_a * t1[1] + d_a * n1[1];
    a_idx_2 = c_a * t1[2] + d_a * n1[2];
    stride_0_0 = (b_r0D0.size(0) != 1);
    stride_2_0 = (b_r1D0.size(0) != 1);
    for (int i2{0}; i2 < 6; i2++) {
        p5_3D[i2][0] = ((((b_r0D0[b_r0D0.size(0) * i2] + b_alpha0[i2][0]) + e_a[i2][0]) +
                         b_r1D0[b_r1D0.size(0) * i2]) +
                        b_alpha1[i2][0]) +
                       a_idx_0 * f_b[i2];
        p5_3D[i2][1] =
            ((((b_r0D0[stride_0_0 + b_r0D0.size(0) * i2] + b_alpha0[i2][1]) + e_a[i2][1]) +
              b_r1D0[stride_2_0 + b_r1D0.size(0) * i2]) +
             b_alpha1[i2][1]) +
            a_idx_1 * f_b[i2];
        p5_3D[i2][2] =
            ((((b_r0D0[(stride_0_0 << 1) + b_r0D0.size(0) * i2] + b_alpha0[i2][2]) + e_a[i2][2]) +
              b_r1D0[(stride_2_0 << 1) + b_r1D0.size(0) * i2]) +
             b_alpha1[i2][2]) +
            a_idx_2 * f_b[i2];
    }
}

//
// function [p5_3D, status, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1,
// r1D2)
//
// Arguments    : const ::coder::array<double, 1U> &r0D0
//                const ::coder::array<double, 1U> &r0D1
//                const ::coder::array<double, 1U> &r0D2
//                const ::coder::array<double, 1U> &r1D0
//                const ::coder::array<double, 1U> &r1D1
//                const ::coder::array<double, 1U> &r1D2
//                double p5_3D[6][3]
//                int *status
//                double *alpha0
//                double *alpha1
// Return Type  : void
//
void G2_Hermite_Interpolation(const ::coder::array<double, 1U> &r0D0,
                              const ::coder::array<double, 1U> &r0D1,
                              const ::coder::array<double, 1U> &r0D2,
                              const ::coder::array<double, 1U> &r1D0,
                              const ::coder::array<double, 1U> &r1D1,
                              const ::coder::array<double, 1U> &r1D2, double p5_3D[6][3],
                              int *status, double *alpha0, double *alpha1)
{
    static const double c_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double f_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char b_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char d_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char e_b[6]{-3, 7, -4, 0, 0, 0};
    ::coder::array<double, 2U> b_r1;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 1U> b_r2;
    ::coder::array<double, 1U> r3;
    creal_T b_alpha1_v[9];
    creal_T alpha0_v[3];
    creal_T alpha1_v[3];
    double b_r0D0[6][3];
    double b_r1D0[6][3];
    double c_r0D0[6][3];
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
    double A[2][2];
    double dv[4];
    double n0[3];
    double n1[3];
    double t0[3];
    double t1[3];
    double B[2];
    double a;
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
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int iindx;
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
    // 'G2_Hermite_Interpolation:32' status = int32(1);
    *status = 1;
    //  default success
    // 'G2_Hermite_Interpolation:34' p5_3D = zeros(3,6);
    for (int i{0}; i < 6; i++) {
        p5_3D[i][0] = 0.0;
        p5_3D[i][1] = 0.0;
        p5_3D[i][2] = 0.0;
    }
    // 'G2_Hermite_Interpolation:35' alpha0 = 0;
    *alpha0 = 0.0;
    // 'G2_Hermite_Interpolation:36' alpha1 = 0;
    *alpha1 = 0.0;
    //  compute Frenet frame
    // 'G2_Hermite_Interpolation:39' [t0, n0, kappa0] = CalcFrenet(r0D1(1:3), r0D2(1:3));
    CalcFrenet(*(double(*)[3]) & r0D1[0], *(double(*)[3]) & r0D2[0], t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation:40' [t1, n1, kappa1] = CalcFrenet(r1D1(1:3), r1D2(1:3));
    CalcFrenet(*(double(*)[3]) & r1D1[0], *(double(*)[3]) & r1D2[0], t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    // 'G2_Hermite_Interpolation:48' CoefPS = CoefPolySys(r0D0, t0, n0, kappa0, r1D0, t1, n1,
    // kappa1);
    CoefPolySys(r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, CoefPS);
    //
    // 'G2_Hermite_Interpolation:50' a1     = CoefPS(1);
    // 'G2_Hermite_Interpolation:51' a0     = CoefPS(2);
    // 'G2_Hermite_Interpolation:52' b1     = CoefPS(3);
    // 'G2_Hermite_Interpolation:53' b0     = CoefPS(4);
    // 'G2_Hermite_Interpolation:54' c3     = CoefPS(5);
    // 'G2_Hermite_Interpolation:55' c2     = CoefPS(6);
    // 'G2_Hermite_Interpolation:56' c1     = CoefPS(7);
    // 'G2_Hermite_Interpolation:57' c0     = CoefPS(8);
    // 'G2_Hermite_Interpolation:58' d1     = CoefPS(9);
    // 'G2_Hermite_Interpolation:59' d0     = CoefPS(10);
    // 'G2_Hermite_Interpolation:60' e1     = CoefPS(11);
    // 'G2_Hermite_Interpolation:61' e0     = CoefPS(12);
    // 'G2_Hermite_Interpolation:62' f3     = CoefPS(13);
    // 'G2_Hermite_Interpolation:63' f2     = CoefPS(14);
    // 'G2_Hermite_Interpolation:64' f1     = CoefPS(15);
    // 'G2_Hermite_Interpolation:65' f0     = CoefPS(16);
    // 'G2_Hermite_Interpolation:66' TolZero = 1e-11;
    //
    // 'G2_Hermite_Interpolation:68' if (kappa0 == 0) && (kappa1 == 0)
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        double X_idx_0;
        double X_idx_1;
        double a21;
        int r1;
        int r2;
        //  degenerated case where the polynomial system degenerates to a linear one
        // 'G2_Hermite_Interpolation:69' M       = [b0, c1;
        // 'G2_Hermite_Interpolation:70'                f1, e0];
        //
        // 'G2_Hermite_Interpolation:72' B       = [-c0;
        // 'G2_Hermite_Interpolation:73'                -f0];
        //
        // 'G2_Hermite_Interpolation:75' X       = M \ B;
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
        // 'G2_Hermite_Interpolation:76' alpha0  = X(1);
        *alpha0 = X_idx_0;
        // 'G2_Hermite_Interpolation:77' alpha1  = X(2);
        *alpha1 = X_idx_1;
        // 'G2_Hermite_Interpolation:79' if ~((alpha0 > 0) && (alpha1 > 0))
        if ((X_idx_0 > 0.0) && (X_idx_1 > 0.0)) {
            // 'G2_Hermite_Interpolation:83' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
            // 'G2_Hermite_Interpolation:84'                                       r0D0, t0, n0,
            // kappa0, ... 'G2_Hermite_Interpolation:85'                                       r1D0,
            // t1, n1, kappa1);
            Calc_beta0_beta1(X_idx_0, X_idx_1, r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a,
                             &b_a);
            guard1 = true;
        }
    } else if (kappa0 == 0.0) {
        int partialTrueCount;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        bool unnamed_idx_2;
        // 'G2_Hermite_Interpolation:86' elseif kappa0 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation:89' Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0 + b1*f0
        // - c1*f1, b0*f0 - c0*f1];
        //
        // 'G2_Hermite_Interpolation:91' alpha1_v   = c_roots_(Coef);
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
        // 'G2_Hermite_Interpolation:92' alpha1_t   = real(alpha1_v((abs(imag(alpha1_v)) < TolZero)
        // & (real(alpha1_v) >  0)));
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
        for (int i1{0}; i1 < trueCount; i1++) {
            alpha1_t_data[i1] = alpha1_v[tmp_data[i1] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation:94' if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation:95' alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
            b_r2.set_size(trueCount);
            for (int i3{0}; i3 < trueCount; i3++) {
                b_r2[i3] = std::pow(alpha1_t_data[i3], 2.0);
            }
            if (b_r2.size(0) == trueCount) {
                int c_loop_ub;
                alpha0_t_size = b_r2.size(0);
                c_loop_ub = b_r2.size(0);
                for (int i11{0}; i11 < c_loop_ub; i11++) {
                    alpha0_t_data[i11] =
                        -((CoefPS[9] * b_r2[i11] + CoefPS[11] * alpha1_t_data[i11]) + CoefPS[15]) /
                        CoefPS[14];
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, b_r2, alpha1_t_data,
                                 &trueCount);
            }
        } else {
            int i14;
            int i19;
            int i22;
            // 'G2_Hermite_Interpolation:96' else
            // 'G2_Hermite_Interpolation:97' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            b_r2.set_size(trueCount);
            for (int i5{0}; i5 < trueCount; i5++) {
                b_r2[i5] = std::pow(alpha1_t_data[i5], 3.0);
            }
            r3.set_size(trueCount);
            for (int i9{0}; i9 < trueCount; i9++) {
                r3[i9] = std::pow(alpha1_t_data[i9], 2.0);
            }
            if (b_r2.size(0) == 1) {
                i14 = r3.size(0);
            } else {
                i14 = b_r2.size(0);
            }
            if (b_r2.size(0) == 1) {
                i19 = r3.size(0);
            } else {
                i19 = b_r2.size(0);
            }
            if (i19 == 1) {
                i22 = trueCount;
            } else if (b_r2.size(0) == 1) {
                i22 = r3.size(0);
            } else {
                i22 = b_r2.size(0);
            }
            if ((b_r2.size(0) == r3.size(0)) && (i14 == trueCount) && (i22 == trueCount)) {
                int g_loop_ub;
                alpha0_t_size = b_r2.size(0);
                g_loop_ub = b_r2.size(0);
                for (int i25{0}; i25 < g_loop_ub; i25++) {
                    double d4;
                    d4 = alpha1_t_data[i25];
                    alpha0_t_data[i25] =
                        -(((CoefPS[4] * b_r2[i25] + CoefPS[5] * r3[i25]) + CoefPS[6] * d4) +
                          CoefPS[7]) /
                        (CoefPS[2] * d4 + CoefPS[3]);
                }
            } else {
                binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, b_r2, r3, alpha1_t_data,
                                 &trueCount);
            }
        }
        // 'G2_Hermite_Interpolation:100' Idx       = find(alpha0_t > 0);
        for (int i15{0}; i15 < alpha0_t_size; i15++) {
            b_alpha0_t_data[i15] = (alpha0_t_data[i15] > 0.0);
        }
        coder::b_eml_find(b_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation:101' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation:102' alpha0_u  = alpha0_t(Idx);
        // 'G2_Hermite_Interpolation:104' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation:105' status = int32(3);
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation:110' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int CostInt_size_tmp;
                // 'G2_Hermite_Interpolation:112' CostInt = zeros(size(alpha0_u));
                CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:113' beta0_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:114' beta1_u = zeros(size(alpha0_u));
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:116' for k = 1:length(alpha0_u)
                for (int k{0}; k < Idx_size; k++) {
                    int i28;
                    // 'G2_Hermite_Interpolation:118' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:119'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:120' r1D0, t1, n1,
                    // kappa1);
                    i28 = Idx_data[k];
                    Calc_beta0_beta1(alpha0_t_data[i28 - 1], alpha1_t_data[i28 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[k],
                                     &beta1_u_data[k]);
                    // 'G2_Hermite_Interpolation:121' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:122' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:123' r1D0, t1, n1, kappa1);
                    CostInt_data[k] = EvalCostIntegral(alpha0_t_data[i28 - 1], beta0_u_data[k],
                                                       alpha1_t_data[i28 - 1], beta1_u_data[k],
                                                       r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int b_alpha0_tmp;
                // 'G2_Hermite_Interpolation:127' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)), &ex,
                                         &iindx);
                // 'G2_Hermite_Interpolation:128' alpha0   = alpha0_u(Idx);
                b_alpha0_tmp = Idx_data[iindx - 1] - 1;
                *alpha0 = alpha0_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation:129' alpha1   = alpha1_u(Idx);
                *alpha1 = alpha1_t_data[b_alpha0_tmp];
                // 'G2_Hermite_Interpolation:130' beta0    = beta0_u(Idx);
                a = beta0_u_data[iindx - 1];
                // 'G2_Hermite_Interpolation:131' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation:133' else
                // 'G2_Hermite_Interpolation:135' alpha0   = alpha0_u(1);
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:136' alpha1   = alpha1_u(1);
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:137' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1,
                // ... 'G2_Hermite_Interpolation:138' r0D0, t0, n0, kappa0, ...
                // 'G2_Hermite_Interpolation:139'                                           r1D0,
                // t1, n1, kappa1);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else if (kappa1 == 0.0) {
        int b_partialTrueCount;
        bool b_unnamed_idx_2;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        // 'G2_Hermite_Interpolation:143' elseif kappa1 == 0
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation:146' Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1 -
        // c0*e1 - b0*e0, c1*f0 - c0*e0];
        //
        // 'G2_Hermite_Interpolation:148' alpha0_v  = c_roots_(Coef);
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
        // 'G2_Hermite_Interpolation:149' alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) < TolZero)
        // & (real(alpha0_v) >  0)));
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
        for (int i2{0}; i2 < b_trueCount; i2++) {
            alpha0_t_data[i2] = alpha0_v[tmp_data[i2] - 1].re;
        }
        //  retain only positive real roots
        // 'G2_Hermite_Interpolation:151' if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            // 'G2_Hermite_Interpolation:152' alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
            b_r2.set_size(b_trueCount);
            for (int i4{0}; i4 < b_trueCount; i4++) {
                b_r2[i4] = std::pow(alpha0_t_data[i4], 2.0);
            }
            if (b_r2.size(0) == b_trueCount) {
                int e_loop_ub;
                alpha1_t_size = b_r2.size(0);
                e_loop_ub = b_r2.size(0);
                for (int i13{0}; i13 < e_loop_ub; i13++) {
                    alpha1_t_data[i13] =
                        -((CoefPS[1] * b_r2[i13] + CoefPS[3] * alpha0_t_data[i13]) + CoefPS[7]) /
                        CoefPS[6];
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, b_r2, alpha0_t_data,
                                   &b_trueCount);
            }
        } else {
            int i16;
            int i20;
            int i23;
            // 'G2_Hermite_Interpolation:153' else
            // 'G2_Hermite_Interpolation:154' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            b_r2.set_size(b_trueCount);
            for (int i7{0}; i7 < b_trueCount; i7++) {
                b_r2[i7] = std::pow(alpha0_t_data[i7], 3.0);
            }
            r3.set_size(b_trueCount);
            for (int i10{0}; i10 < b_trueCount; i10++) {
                r3[i10] = std::pow(alpha0_t_data[i10], 2.0);
            }
            if (b_r2.size(0) == 1) {
                i16 = r3.size(0);
            } else {
                i16 = b_r2.size(0);
            }
            if (b_r2.size(0) == 1) {
                i20 = r3.size(0);
            } else {
                i20 = b_r2.size(0);
            }
            if (i20 == 1) {
                i23 = b_trueCount;
            } else if (b_r2.size(0) == 1) {
                i23 = r3.size(0);
            } else {
                i23 = b_r2.size(0);
            }
            if ((b_r2.size(0) == r3.size(0)) && (i16 == b_trueCount) && (i23 == b_trueCount)) {
                int h_loop_ub;
                alpha1_t_size = b_r2.size(0);
                h_loop_ub = b_r2.size(0);
                for (int i27{0}; i27 < h_loop_ub; i27++) {
                    double d6;
                    d6 = alpha0_t_data[i27];
                    alpha1_t_data[i27] =
                        -(((CoefPS[12] * b_r2[i27] + CoefPS[13] * r3[i27]) + CoefPS[14] * d6) +
                          CoefPS[15]) /
                        (CoefPS[10] * d6 + CoefPS[11]);
                }
            } else {
                b_binary_expand_op(alpha1_t_data, &alpha1_t_size, CoefPS, b_r2, r3, alpha0_t_data,
                                   &b_trueCount);
            }
        }
        // 'G2_Hermite_Interpolation:157' Idx      = find(alpha1_t > 0);
        for (int i17{0}; i17 < alpha1_t_size; i17++) {
            b_alpha1_t_data[i17] = (alpha1_t_data[i17] > 0.0);
        }
        coder::b_eml_find(b_alpha1_t_data, alpha1_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation:158' alpha1_u   = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation:159' alpha0_u   = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation:162' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation:163' status = int32(4);
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation:168' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int b_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation:169' CostInt = zeros(size(alpha0_u));
                b_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:170' beta0_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:171' beta1_u = zeros(size(alpha0_u));
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:173' for k = 1:length(alpha0_u)
                for (int b_k{0}; b_k < Idx_size; b_k++) {
                    int i29;
                    // 'G2_Hermite_Interpolation:174' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:175'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:176' r1D0, t1, n1,
                    // kappa1);
                    i29 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i29 - 1], alpha1_t_data[i29 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation:177' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:178' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:179' r1D0, t1, n1, kappa1);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[i29 - 1], beta0_u_data[b_k], alpha1_t_data[i29 - 1],
                        beta1_u_data[b_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int c_alpha0_tmp;
                // 'G2_Hermite_Interpolation:181' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &b_ex, &b_iindx);
                // 'G2_Hermite_Interpolation:182' alpha0   = alpha0_u(Idx);
                c_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation:183' alpha1   = alpha1_u(Idx);
                *alpha1 = alpha1_t_data[c_alpha0_tmp];
                // 'G2_Hermite_Interpolation:184' beta0    = beta0_u(Idx);
                a = beta0_u_data[b_iindx - 1];
                // 'G2_Hermite_Interpolation:185' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation:187' else
                // 'G2_Hermite_Interpolation:189' alpha0   = alpha0_u(1);
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:190' alpha1   = alpha1_u(1);
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:191' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1,
                // ... 'G2_Hermite_Interpolation:192' r0D0, t0, n0, kappa0, ...
                // 'G2_Hermite_Interpolation:193'                                           r1D0,
                // t1, n1, kappa1);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else {
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
        int b_t12_size;
        int c_partialTrueCount;
        int d_trueCount;
        int e_trueCount;
        int f_trueCount;
        int g_trueCount;
        int h_trueCount;
        int i40;
        int i_loop_ub;
        int i_trueCount;
        int j_trueCount;
        int k_trueCount;
        int l_trueCount;
        int m_trueCount;
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
        // 'G2_Hermite_Interpolation:197' else
        //  compute resultant of the polynomial system
        // 'G2_Hermite_Interpolation:200' Coef = CharPolyAlpha1(CoefPS);
        //
        // 'G2_Hermite_Interpolation:202' alpha1_v = c_roots_(Coef);
        // CHARPOLYALPHA1
        //     COEFF_POLY_ALPHA1 = CHARPOLYALPHA1(IN1)
        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:33
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
        // 'CharPolyAlpha1:44' Coeff_Poly_Alpha1 =
        // [CoefPS5_1.^3.*t18+CoefPS5_1.*t2.*t14-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0,CoefPS6_1.*t2.*t14+CoefPS6_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t14.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0,t3.*t15+CoefPS1_1.*t10.*t19+CoefPS5_1.*t2.*t16+CoefPS5_1.*t4.*t14+CoefPS5_1.*t11.*t18.*3.0+CoefPS7_1.*t2.*t14+CoefPS7_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t14.*2.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t10+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0,CoefPS6_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t3.*2.0+CoefPS2_1.*t2.*t15.*3.0+CoefPS2_1.*t10.*t19+CoefPS6_1.*t2.*t16+CoefPS6_1.*t4.*t14+CoefPS8_1.*t2.*t14+CoefPS8_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS7_1.*t18.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t2-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t10-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0,t3.*t17-CoefPS10_1.*CoefPS13_1.*t7+CoefPS10_1.*CoefPS16_1.*t3.*2.0+CoefPS1_1.*t4.*t15.*3.0+CoefPS1_1.*t11.*t19+CoefPS5_1.*t4.*t16+CoefPS5_1.*t2.*t20+CoefPS5_1.*t12.*t18.*3.0+CoefPS7_1.*t2.*t16+CoefPS7_1.*t4.*t14+CoefPS7_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS8_1.*t18.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS12_1.*t2.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t2+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t11+CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0,t5.*t15-CoefPS12_1.*CoefPS13_1.*t7+CoefPS12_1.*CoefPS16_1.*t3.*2.0+CoefPS2_1.*t2.*t17.*3.0+CoefPS2_1.*t11.*t19+CoefPS6_1.*t4.*t16+CoefPS6_1.*t2.*t20+CoefPS6_1.*t12.*t18.*3.0+CoefPS8_1.*t2.*t16+CoefPS8_1.*t4.*t14+CoefPS8_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t16.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS5_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0+CoefPS1_1.*CoefPS10_1.*CoefPS12_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t4-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS10_1.*CoefPS13_1.*t6.*3.0+CoefPS2_1.*CoefPS10_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t2+CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t11+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS3_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0,t3.*t21+CoefPS7_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t5.*2.0-CoefPS13_1.*CoefPS16_1.*t7+CoefPS1_1.*t4.*t17.*3.0+CoefPS1_1.*t12.*t19+CoefPS5_1.*t4.*t20+CoefPS5_1.*t13.*t18.*3.0+CoefPS7_1.*t4.*t16+CoefPS7_1.*t2.*t20+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t16.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS6_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t4+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS13_1.*t8.*3.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS1_1.*CoefPS10_1.*CoefPS16_1.*t4.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS12_1.*CoefPS13_1.*t6.*3.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t12-CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t2+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0,t5.*t17-CoefPS10_1.*CoefPS13_1.*t9+CoefPS10_1.*CoefPS16_1.*t5.*2.0+CoefPS2_1.*t2.*t21.*3.0+CoefPS2_1.*t12.*t19+CoefPS6_1.*t4.*t20+CoefPS6_1.*t13.*t18.*3.0+CoefPS8_1.*t4.*t16+CoefPS8_1.*t2.*t20+CoefPS8_1.*t12.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t20.*2.0+CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t4+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS12_1.*CoefPS13_1.*t8.*3.0+CoefPS1_1.*CoefPS12_1.*CoefPS16_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t4-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t12+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS16_1.*t6.*3.0+CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t2-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0,-CoefPS12_1.*CoefPS13_1.*t9+CoefPS12_1.*CoefPS16_1.*t5.*2.0+CoefPS1_1.*t4.*t21.*3.0+CoefPS1_1.*t13.*t19+CoefPS7_1.*t4.*t20+CoefPS7_1.*t13.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t20.*2.0+CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t13-CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS16_1.*t8.*3.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS4_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0,t5.*t21+CoefPS8_1.^3.*t18-CoefPS13_1.*CoefPS16_1.*t9+CoefPS2_1.*t13.*t19+CoefPS8_1.*t4.*t20-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t13+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1];
        // 'c_roots_:2' if coder.target('rtw')
        // 'c_roots_:3' Y = complex(zeros(numel(coeffs)-1, 1));
        std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
        // 'c_roots_:4' coder.cinclude('functions.h');
        // 'c_roots_:5' coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y),
        // int32(numel(coeffs)));
        d7 = CoefPS[4] * t2;
        d8 = CoefPS[0] * CoefPS[8] * CoefPS[12];
        dv1[0] = (std::pow(CoefPS[4], 3.0) * t18 + d7 * t14) - d8 * t10 * 2.0;
        d9 = CoefPS[0] * CoefPS[1];
        d10 = CoefPS[4] * CoefPS[8];
        d11 = d9 * CoefPS[4];
        d12 = CoefPS[0] * CoefPS[4];
        d13 = d12 * CoefPS[5];
        d14 = CoefPS[5] * t2;
        d15 = CoefPS[1] * CoefPS[8] * CoefPS[12];
        d16 = d10 * CoefPS[10];
        d17 = CoefPS[0] * CoefPS[10] * CoefPS[12];
        dv1[1] =
            (((((d14 * t14 + CoefPS[5] * t10 * t18 * 3.0) + d11 * t14 * 2.0) - d15 * t10 * 2.0) +
              d16 * t2 * 2.0) -
             d17 * t10 * 2.0) -
            d13 * CoefPS[8] * CoefPS[12] * 4.0;
        d18 = CoefPS[0] * CoefPS[2];
        d19 = d18 * CoefPS[4];
        d20 = CoefPS[2] * CoefPS[8];
        d21 = CoefPS[5] * CoefPS[8];
        d22 = d9 * CoefPS[5];
        d23 = d11 * CoefPS[8];
        d24 = CoefPS[1] * CoefPS[4];
        d25 = d12 * CoefPS[6];
        d26 = d24 * CoefPS[5];
        d27 = CoefPS[4] * t4;
        d28 = CoefPS[6] * t2;
        d29 = d20 * CoefPS[9];
        d30 = d21 * CoefPS[10];
        d31 = CoefPS[1] * CoefPS[10] * CoefPS[12];
        d32 = d10 * CoefPS[12];
        d33 = d10 * CoefPS[14];
        d34 = CoefPS[4] * CoefPS[9] * CoefPS[13];
        d35 = CoefPS[0] * CoefPS[12] * CoefPS[14];
        d36 = CoefPS[2] * CoefPS[12];
        d37 = d36 * CoefPS[13];
        dv1[2] = (((((((((((((((((((((t3 * t15 + CoefPS[0] * t10 * t19) + d7 * t16) + d27 * t14) +
                                   CoefPS[4] * t11 * t18 * 3.0) +
                                  d28 * t14) +
                                 CoefPS[6] * t10 * t18 * 3.0) +
                                d22 * t14 * 2.0) -
                               d29 * t2) -
                              d8 * t11 * 2.0) +
                             d30 * t2 * 2.0) -
                            d31 * t10 * 2.0) +
                           d32 * t6) +
                          d33 * t2 * 2.0) -
                         d34 * t2 * 2.0) -
                        d35 * t10 * 2.0) -
                       d37 * t10) +
                      d23 * CoefPS[10] * 4.0) -
                     d19 * CoefPS[8] * CoefPS[13]) +
                    d19 * CoefPS[9] * CoefPS[12] * 3.0) -
                   d25 * CoefPS[8] * CoefPS[12] * 4.0) -
                  d26 * CoefPS[8] * CoefPS[12] * 4.0) -
                 d13 * CoefPS[10] * CoefPS[12] * 4.0;
        d38 = CoefPS[9] * CoefPS[11];
        d39 = CoefPS[1] * t2;
        d40 = CoefPS[4] * CoefPS[10];
        d41 = d18 * CoefPS[5];
        d42 = CoefPS[0] * CoefPS[3];
        d43 = d42 * CoefPS[4];
        d44 = CoefPS[1] * CoefPS[2];
        d45 = d44 * CoefPS[4];
        d46 = CoefPS[4] * CoefPS[5];
        d47 = CoefPS[3] * CoefPS[8];
        d48 = CoefPS[2] * CoefPS[9];
        d49 = CoefPS[6] * CoefPS[8];
        d50 = d9 * CoefPS[2];
        d51 = d50 * CoefPS[8];
        d52 = d9 * CoefPS[6];
        d53 = d22 * CoefPS[8];
        d54 = CoefPS[2] * CoefPS[3];
        d55 = d54 * CoefPS[4];
        d56 = CoefPS[0] * CoefPS[5];
        d57 = d12 * CoefPS[7];
        d58 = d56 * CoefPS[6];
        d59 = d24 * CoefPS[6];
        d60 = CoefPS[2] * CoefPS[4];
        d61 = CoefPS[5] * t4;
        d62 = CoefPS[7] * t2;
        d63 = d47 * CoefPS[9];
        d64 = d20 * CoefPS[11];
        d65 = d48 * CoefPS[10];
        d66 = d49 * CoefPS[10];
        d67 = d21 * CoefPS[12];
        d68 = d40 * CoefPS[12];
        d69 = d21 * CoefPS[14];
        d70 = CoefPS[5] * CoefPS[9] * CoefPS[13];
        d71 = CoefPS[1] * CoefPS[12] * CoefPS[14];
        d72 = d40 * CoefPS[14];
        d73 = CoefPS[4] * CoefPS[11] * CoefPS[13];
        d74 = CoefPS[3] * CoefPS[12];
        d75 = d74 * CoefPS[13];
        dv1[3] = (((((((((((((((((((((((((((((((((((((((((((((std::pow(CoefPS[5], 3.0) * t18 +
                                                              d38 * t3 * 2.0) +
                                                             d39 * t15 * 3.0) +
                                                            CoefPS[1] * t10 * t19) +
                                                           d14 * t16) +
                                                          d61 * t14) +
                                                         d62 * t14) +
                                                        CoefPS[7] * t10 * t18 * 3.0) +
                                                       d11 * t16 * 2.0) +
                                                      d52 * t14 * 2.0) +
                                                     d13 * t19 * 2.0) +
                                                    d46 * CoefPS[6] * t18 * 6.0) -
                                                   d63 * t2) -
                                                  d64 * t2) -
                                                 d65 * t2) -
                                                d15 * t11 * 2.0) +
                                               d16 * t4 * 2.0) -
                                              d17 * t11 * 2.0) +
                                             d66 * t2 * 2.0) +
                                            d67 * t6) +
                                           d68 * t6) +
                                          d69 * t2 * 2.0) -
                                         d70 * t2 * 2.0) -
                                        d71 * t10 * 2.0) +
                                       d72 * t2 * 2.0) -
                                      d73 * t2 * 2.0) -
                                     d75 * t10) -
                                    d51 * CoefPS[9] * 2.0) +
                                   d53 * CoefPS[10] * 4.0) +
                                  d23 * CoefPS[14] * 4.0) -
                                 d11 * CoefPS[9] * CoefPS[13] * 4.0) -
                                d41 * CoefPS[8] * CoefPS[13]) +
                               d41 * CoefPS[9] * CoefPS[12] * 3.0) -
                              d43 * CoefPS[8] * CoefPS[13]) +
                             d43 * CoefPS[9] * CoefPS[12] * 3.0) -
                            d45 * CoefPS[8] * CoefPS[13]) +
                           d45 * CoefPS[9] * CoefPS[12] * 3.0) -
                          d19 * CoefPS[10] * CoefPS[13]) +
                         d19 * CoefPS[11] * CoefPS[12] * 3.0) +
                        d55 * CoefPS[8] * CoefPS[12] * 2.0) -
                       d57 * CoefPS[8] * CoefPS[12] * 4.0) -
                      d58 * CoefPS[8] * CoefPS[12] * 4.0) -
                     d59 * CoefPS[8] * CoefPS[12] * 4.0) -
                    d25 * CoefPS[10] * CoefPS[12] * 4.0) -
                   d26 * CoefPS[10] * CoefPS[12] * 4.0) -
                  d13 * CoefPS[12] * CoefPS[14] * 4.0) -
                 d60 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0;
        d76 = CoefPS[0] * CoefPS[9];
        d77 = CoefPS[1] * CoefPS[9];
        d78 = CoefPS[3] * CoefPS[9];
        d79 = CoefPS[2] * CoefPS[10];
        d80 = d9 * CoefPS[7];
        d81 = CoefPS[0] * t4;
        d82 = CoefPS[6] * t4;
        d83 = d47 * CoefPS[11];
        d84 = d78 * CoefPS[10];
        d85 = d76 * CoefPS[13];
        d86 = d79 * CoefPS[11];
        d87 = d20 * CoefPS[15];
        d88 = d48 * CoefPS[14];
        d89 = CoefPS[9] * CoefPS[12];
        d90 = CoefPS[9] * CoefPS[15];
        d91 = CoefPS[7] * CoefPS[8];
        d92 = d91 * CoefPS[10];
        d93 = d18 * CoefPS[6];
        d94 = d42 * CoefPS[5];
        d95 = d44 * CoefPS[5];
        d96 = CoefPS[1] * CoefPS[3];
        d97 = d96 * CoefPS[4];
        d98 = d9 * CoefPS[3];
        d99 = d98 * CoefPS[8];
        d100 = d54 * CoefPS[5];
        d101 = CoefPS[1] * CoefPS[5];
        d102 = d56 * CoefPS[7];
        d103 = d24 * CoefPS[7];
        d104 = d101 * CoefPS[6];
        d105 = CoefPS[3] * CoefPS[4];
        d106 = CoefPS[6] * CoefPS[9] * CoefPS[13];
        d107 = CoefPS[5] * CoefPS[10];
        d108 = d107 * CoefPS[14];
        d109 = CoefPS[5] * CoefPS[11] * CoefPS[13];
        d110 = CoefPS[4] * CoefPS[12] * CoefPS[14];
        d111 = CoefPS[4] * CoefPS[13] * CoefPS[15];
        d112 = d50 * CoefPS[9];
        d113 = d107 * CoefPS[12];
        d114 = d49 * CoefPS[14];
        dv1[4] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t17 - d89 * t7) + d90 * t3 * 2.0) + d81 * t15 * 3.0) + CoefPS[0] * t11 * t19) + d27 * t16) + d7 * t20) + CoefPS[4] * t12 * t18 * 3.0) + d28 * t16) + d82 * t14) + CoefPS[6] * t11 * t18 * 3.0) + d22 * t16 * 2.0) + d80 * t14 * 2.0) + d25 * t19 * 2.0) + d26 * t19 * 2.0) + d46 * CoefPS[7] * t18 * 6.0) - d29 * t4) - d8 * t12 * 2.0) + d77 * CoefPS[11] * t2 * 6.0) - d83 * t2) - d84 * t2) + d85 * t6) - d86 * t2) + d30 * t4 * 2.0) - d31 * t11 * 2.0) + d32 * t8) - d87 * t2) - d88 * t2) + d92 * t2 * 2.0) + d33 * t4 * 2.0) - d34 * t4 * 2.0) + d49 * CoefPS[12] * t6) - d35 * t11 * 2.0) + d113 * t6) - d37 * t11) + d114 * t2 * 2.0) - d106 * t2 * 2.0) + d108 * t2 * 2.0) - d109 * t2 * 2.0) + d110 * t6) - d111 * t2 * 2.0) - d99 * CoefPS[9] * 2.0) - d51 * CoefPS[11] * 2.0) - d112 * CoefPS[10] * 2.0) + d52 * CoefPS[8] * CoefPS[10] * 4.0) + d53 * CoefPS[14] * 4.0) - d22 * CoefPS[9] * CoefPS[13] * 4.0) + d11 * CoefPS[10] * CoefPS[14] * 4.0) - d11 * CoefPS[11] * CoefPS[13] * 4.0) - d93 * CoefPS[8] * CoefPS[13]) + d93 * CoefPS[9] * CoefPS[12] * 3.0) - d94 * CoefPS[8] * CoefPS[13]) + d94 * CoefPS[9] * CoefPS[12] * 3.0) - d95 * CoefPS[8] * CoefPS[13]) + d95 * CoefPS[9] * CoefPS[12] * 3.0) - d97 * CoefPS[8] * CoefPS[13]) + d97 * CoefPS[9] * CoefPS[12] * 3.0) - d41 * CoefPS[10] * CoefPS[13]) + d41 * CoefPS[11] * CoefPS[12] * 3.0) - d43 * CoefPS[10] * CoefPS[13]) + d43 * CoefPS[11] * CoefPS[12] * 3.0) - d45 * CoefPS[10] * CoefPS[13]) + d45 * CoefPS[11] * CoefPS[12] * 3.0) + d100 * CoefPS[8] * CoefPS[12] * 2.0) + d55 * CoefPS[10] * CoefPS[12] * 2.0) - d102 * CoefPS[8] * CoefPS[12] * 4.0) - d103 * CoefPS[8] * CoefPS[12] * 4.0) - d104 * CoefPS[8] * CoefPS[12] * 4.0) + d19 * CoefPS[12] * CoefPS[15] * 3.0) - d19 * CoefPS[13] * CoefPS[14]) - d57 * CoefPS[10] * CoefPS[12] * 4.0) - d58 * CoefPS[10] * CoefPS[12] * 4.0) - d59 * CoefPS[10] * CoefPS[12] * 4.0) - d25 * CoefPS[12] * CoefPS[14] * 4.0) - d26 * CoefPS[12] * CoefPS[14] * 4.0) - d60 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d105 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0;
        d115 = CoefPS[11] * CoefPS[15];
        d116 = CoefPS[6] * CoefPS[10];
        d117 = CoefPS[3] * CoefPS[10];
        d118 = CoefPS[7] * t4;
        d119 = d77 * CoefPS[13];
        d120 = d117 * CoefPS[11];
        d121 = CoefPS[0] * CoefPS[11];
        d122 = d121 * CoefPS[13];
        d123 = CoefPS[2] * CoefPS[11];
        d124 = d47 * CoefPS[15];
        d125 = d78 * CoefPS[14];
        d126 = d79 * CoefPS[15];
        d127 = d123 * CoefPS[14];
        d128 = CoefPS[7] * CoefPS[9] * CoefPS[13];
        d129 = d116 * CoefPS[14];
        d130 = CoefPS[6] * CoefPS[11] * CoefPS[13];
        d131 = CoefPS[5] * CoefPS[12] * CoefPS[14];
        d132 = CoefPS[5] * CoefPS[13] * CoefPS[15];
        d133 = d18 * CoefPS[7];
        d134 = d42 * CoefPS[6];
        d135 = d44 * CoefPS[6];
        d136 = d96 * CoefPS[5];
        d137 = d54 * CoefPS[6];
        d138 = CoefPS[0] * CoefPS[6] * CoefPS[7];
        d139 = d101 * CoefPS[7];
        d140 = CoefPS[2] * CoefPS[5];
        d141 = d98 * CoefPS[9];
        d142 = d50 * CoefPS[10];
        d143 = d91 * CoefPS[12];
        dv1[5] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t15 - CoefPS[11] * CoefPS[12] * t7) + d115 * t3 * 2.0) + d39 * t17 * 3.0) + CoefPS[1] * t11 * t19) + d61 * t16) + d14 * t20) + CoefPS[5] * t12 * t18 * 3.0) + d62 * t16) + d118 * t14) + CoefPS[7] * t11 * t18 * 3.0) + d11 * t20 * 2.0) + d52 * t16 * 2.0) + d57 * t19 * 2.0) + d58 * t19 * 2.0) + d59 * t19 * 2.0) + CoefPS[4] * CoefPS[6] * CoefPS[7] * t18 * 6.0) + d76 * CoefPS[11] * t4 * 6.0) - d63 * t4) - d64 * t4) - d65 * t4) - d15 * t12 * 2.0) - d17 * t12 * 2.0) + d119 * t6) - d120 * t2) + d66 * t4 * 2.0) + d122 * t6) - d78 * CoefPS[12] * t6 * 3.0) + d77 * CoefPS[15] * t2 * 6.0) + d67 * t8) - d124 * t2) - d125 * t2) + d68 * t8) - d126 * t2) - d127 * t2) + d69 * t4 * 2.0) - d70 * t4 * 2.0) + d143 * t6) - d71 * t11 * 2.0) + d72 * t4 * 2.0) - d73 * t4 * 2.0) + d116 * CoefPS[12] * t6) - d75 * t11) + d91 * CoefPS[14] * t2 * 2.0) - d128 * t2 * 2.0) + d129 * t2 * 2.0) - d130 * t2 * 2.0) + d131 * t6) - d132 * t2 * 2.0) - d99 * CoefPS[11] * 2.0) - d141 * CoefPS[10] * 2.0) - d142 * CoefPS[11] * 2.0) - d51 * CoefPS[15] * 2.0) - d112 * CoefPS[14] * 2.0) + d80 * CoefPS[8] * CoefPS[10] * 4.0) + d18 * CoefPS[3] * CoefPS[9] * CoefPS[13] * 2.0) + d9 * CoefPS[6] * CoefPS[8] * CoefPS[14] * 4.0) - CoefPS[0] * CoefPS[1] * CoefPS[6] * CoefPS[9] * CoefPS[13] * 4.0) + d22 * CoefPS[10] * CoefPS[14] * 4.0) - d22 * CoefPS[11] * CoefPS[13] * 4.0) - d133 * CoefPS[8] * CoefPS[13]) + d133 * CoefPS[9] * CoefPS[12] * 3.0) - d134 * CoefPS[8] * CoefPS[13]) + d134 * CoefPS[9] * CoefPS[12] * 3.0) - d135 * CoefPS[8] * CoefPS[13]) + d135 * CoefPS[9] * CoefPS[12] * 3.0) - d136 * CoefPS[8] * CoefPS[13]) + d136 * CoefPS[9] * CoefPS[12] * 3.0) - d93 * CoefPS[10] * CoefPS[13]) + d93 * CoefPS[11] * CoefPS[12] * 3.0) - d94 * CoefPS[10] * CoefPS[13]) + d94 * CoefPS[11] * CoefPS[12] * 3.0) - d95 * CoefPS[10] * CoefPS[13]) + d95 * CoefPS[11] * CoefPS[12] * 3.0) - d97 * CoefPS[10] * CoefPS[13]) + d97 * CoefPS[11] * CoefPS[12] * 3.0) + d137 * CoefPS[8] * CoefPS[12] * 2.0) + d100 * CoefPS[10] * CoefPS[12] * 2.0) - d11 * CoefPS[13] * CoefPS[15] * 4.0) - d138 * CoefPS[8] * CoefPS[12] * 4.0) - d139 * CoefPS[8] * CoefPS[12] * 4.0) + d41 * CoefPS[12] * CoefPS[15] * 3.0) - d41 * CoefPS[13] * CoefPS[14]) + d43 * CoefPS[12] * CoefPS[15] * 3.0) - d43 * CoefPS[13] * CoefPS[14]) - d102 * CoefPS[10] * CoefPS[12] * 4.0) + d45 * CoefPS[12] * CoefPS[15] * 3.0) - d45 * CoefPS[13] * CoefPS[14]) - d103 * CoefPS[10] * CoefPS[12] * 4.0) - d104 * CoefPS[10] * CoefPS[12] * 4.0) + d55 * CoefPS[12] * CoefPS[14] * 2.0) - d57 * CoefPS[12] * CoefPS[14] * 4.0) - d58 * CoefPS[12] * CoefPS[14] * 4.0) - d59 * CoefPS[12] * CoefPS[14] * 4.0) - d60 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d140 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d105 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0;
        d144 = CoefPS[1] * CoefPS[11];
        d145 = CoefPS[3] * CoefPS[11];
        d146 = CoefPS[7] * CoefPS[10];
        d147 = d144 * CoefPS[13];
        d148 = d117 * CoefPS[15];
        d149 = d145 * CoefPS[14];
        d150 = CoefPS[0] * CoefPS[13] * CoefPS[15];
        d151 = d146 * CoefPS[12];
        d152 = CoefPS[2] * CoefPS[14] * CoefPS[15];
        d153 = d146 * CoefPS[14];
        d154 = CoefPS[7] * CoefPS[11] * CoefPS[13];
        d155 = CoefPS[12] * CoefPS[15];
        d156 = CoefPS[6] * CoefPS[12] * CoefPS[14];
        d157 = CoefPS[6] * CoefPS[13] * CoefPS[15];
        d158 = d98 * CoefPS[10];
        d159 = d42 * CoefPS[7];
        d160 = d44 * CoefPS[7];
        d161 = d96 * CoefPS[6];
        d162 = d54 * CoefPS[7];
        d163 = CoefPS[1] * CoefPS[6] * CoefPS[7];
        d164 = CoefPS[3] * CoefPS[5];
        d165 = CoefPS[0] * CoefPS[2] * CoefPS[3];
        dv1[6] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t21 + std::pow(CoefPS[6], 3.0) * t18) + d38 * t5 * 2.0) - d155 * t7) + d81 * t17 * 3.0) + CoefPS[0] * t12 * t19) + d27 * t20) + CoefPS[4] * t13 * t18 * 3.0) + d82 * t16) + d28 * t20) + d22 * t20 * 2.0) + d80 * t16 * 2.0) + d102 * t19 * 2.0) + d103 * t19 * 2.0) + d104 * t19 * 2.0) + CoefPS[5] * CoefPS[6] * CoefPS[7] * t18 * 6.0) - d8 * t13 * 2.0) - d83 * t4) - d84 * t4) + d85 * t8) - d86 * t4) - d48 * CoefPS[12] * t8 * 3.0) - d31 * t12 * 2.0) + d76 * CoefPS[15] * t4 * 6.0) - d87 * t4) - d88 * t4) + d92 * t4 * 2.0) + d147 * t6) - d145 * CoefPS[12] * t6 * 3.0) + CoefPS[6] * CoefPS[8] * CoefPS[12] * t8) - d35 * t12 * 2.0) + d144 * CoefPS[15] * t2 * 6.0) + d113 * t8) - d37 * t12) - d148 * t2) - d149 * t2) + d114 * t4 * 2.0) - d106 * t4 * 2.0) + d150 * t6) + d108 * t4 * 2.0) - d109 * t4 * 2.0) + d151 * t6) + d110 * t8) - d152 * t2) + d153 * t2 * 2.0) - d154 * t2 * 2.0) - d111 * t4 * 2.0) + d156 * t6) - d157 * t2 * 2.0) - d158 * CoefPS[11] * 2.0) - d99 * CoefPS[15] * 2.0) - d141 * CoefPS[14] * 2.0) - d142 * CoefPS[15] * 2.0) - d50 * CoefPS[11] * CoefPS[14] * 2.0) + d44 * CoefPS[3] * CoefPS[9] * CoefPS[13] * 2.0) + d165 * CoefPS[11] * CoefPS[13] * 2.0) + CoefPS[0] * CoefPS[1] * CoefPS[7] * CoefPS[8] * CoefPS[14] * 4.0) - d80 * CoefPS[9] * CoefPS[13] * 4.0) + d52 * CoefPS[10] * CoefPS[14] * 4.0) - d52 * CoefPS[11] * CoefPS[13] * 4.0) - d159 * CoefPS[8] * CoefPS[13]) + d159 * CoefPS[9] * CoefPS[12] * 3.0) - d160 * CoefPS[8] * CoefPS[13]) + d160 * CoefPS[9] * CoefPS[12] * 3.0) - d161 * CoefPS[8] * CoefPS[13]) + d161 * CoefPS[9] * CoefPS[12] * 3.0) - d133 * CoefPS[10] * CoefPS[13]) + d133 * CoefPS[11] * CoefPS[12] * 3.0) - d134 * CoefPS[10] * CoefPS[13]) + d134 * CoefPS[11] * CoefPS[12] * 3.0) - d135 * CoefPS[10] * CoefPS[13]) + d135 * CoefPS[11] * CoefPS[12] * 3.0) - d136 * CoefPS[10] * CoefPS[13]) + d136 * CoefPS[11] * CoefPS[12] * 3.0) + d162 * CoefPS[8] * CoefPS[12] * 2.0) + d137 * CoefPS[10] * CoefPS[12] * 2.0) - d22 * CoefPS[13] * CoefPS[15] * 4.0) - d163 * CoefPS[8] * CoefPS[12] * 4.0) + d93 * CoefPS[12] * CoefPS[15] * 3.0) - d93 * CoefPS[13] * CoefPS[14]) + d94 * CoefPS[12] * CoefPS[15] * 3.0) - d94 * CoefPS[13] * CoefPS[14]) - d138 * CoefPS[10] * CoefPS[12] * 4.0) + d95 * CoefPS[12] * CoefPS[15] * 3.0) - d95 * CoefPS[13] * CoefPS[14]) + d97 * CoefPS[12] * CoefPS[15] * 3.0) - d97 * CoefPS[13] * CoefPS[14]) - d139 * CoefPS[10] * CoefPS[12] * 4.0) + d100 * CoefPS[12] * CoefPS[14] * 2.0) - d102 * CoefPS[12] * CoefPS[14] * 4.0) - d103 * CoefPS[12] * CoefPS[14] * 4.0) - d104 * CoefPS[12] * CoefPS[14] * 4.0) - d140 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d105 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d164 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0;
        d166 = d96 * CoefPS[7];
        d167 = CoefPS[1] * CoefPS[2] * CoefPS[3];
        d168 = CoefPS[1] * CoefPS[13] * CoefPS[15];
        d169 = CoefPS[3] * CoefPS[14] * CoefPS[15];
        d170 = CoefPS[7] * CoefPS[12] * CoefPS[14];
        d171 = CoefPS[7] * CoefPS[13] * CoefPS[15];
        dv1[7] = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t17 - d89 * t9) + d90 * t5 * 2.0) + d39 * t21 * 3.0) + CoefPS[1] * t12 * t19) + d61 * t20) + CoefPS[5] * t13 * t18 * 3.0) + d118 * t16) + d62 * t20) + CoefPS[7] * t12 * t18 * 3.0) + d52 * t20 * 2.0) + d138 * t19 * 2.0) + d139 * t19 * 2.0) - d15 * t13 * 2.0) - d17 * t13 * 2.0) + d119 * t8) - d120 * t4) + d122 * t8) - d123 * CoefPS[12] * t8 * 3.0) + d121 * CoefPS[15] * t4 * 6.0) - d124 * t4) - d125 * t4) - d126 * t4) - d127 * t4) + d143 * t8) - d71 * t12 * 2.0) + CoefPS[6] * CoefPS[10] * CoefPS[12] * t8) - d75 * t12) + CoefPS[7] * CoefPS[8] * CoefPS[14] * t4 * 2.0) - d128 * t4 * 2.0) + d168 * t6) + d129 * t4 * 2.0) - d130 * t4 * 2.0) - d74 * CoefPS[15] * t6 * 3.0) + d131 * t8) - d169 * t2) - d132 * t4 * 2.0) + d170 * t6) - d171 * t2 * 2.0) - d158 * CoefPS[15] * 2.0) - d98 * CoefPS[11] * CoefPS[14] * 2.0) + d167 * CoefPS[11] * CoefPS[13] * 2.0) - d50 * CoefPS[14] * CoefPS[15] * 2.0) + d80 * CoefPS[10] * CoefPS[14] * 4.0) - d80 * CoefPS[11] * CoefPS[13] * 4.0) - d166 * CoefPS[8] * CoefPS[13]) + d166 * CoefPS[9] * CoefPS[12] * 3.0) + d165 * CoefPS[13] * CoefPS[15] * 2.0) - d159 * CoefPS[10] * CoefPS[13]) + d159 * CoefPS[11] * CoefPS[12] * 3.0) - d160 * CoefPS[10] * CoefPS[13]) + d160 * CoefPS[11] * CoefPS[12] * 3.0) - d161 * CoefPS[10] * CoefPS[13]) + d161 * CoefPS[11] * CoefPS[12] * 3.0) + d162 * CoefPS[10] * CoefPS[12] * 2.0) - d52 * CoefPS[13] * CoefPS[15] * 4.0) + d133 * CoefPS[12] * CoefPS[15] * 3.0) - d133 * CoefPS[13] * CoefPS[14]) + d134 * CoefPS[12] * CoefPS[15] * 3.0) - d134 * CoefPS[13] * CoefPS[14]) + d135 * CoefPS[12] * CoefPS[15] * 3.0) - d135 * CoefPS[13] * CoefPS[14]) + d136 * CoefPS[12] * CoefPS[15] * 3.0) - d136 * CoefPS[13] * CoefPS[14]) - d163 * CoefPS[10] * CoefPS[12] * 4.0) + d137 * CoefPS[12] * CoefPS[14] * 2.0) - d138 * CoefPS[12] * CoefPS[14] * 4.0) - d139 * CoefPS[12] * CoefPS[14] * 4.0) - CoefPS[2] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d164 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0;
        dv1[8] =
            ((((((((((((((((((((((((((((((((((-CoefPS[11] * CoefPS[12] * t9 + d115 * t5 * 2.0) +
                                             d81 * t21 * 3.0) +
                                            CoefPS[0] * t13 * t19) +
                                           d82 * t20) +
                                          CoefPS[6] * t13 * t18 * 3.0) +
                                         d80 * t20 * 2.0) +
                                        d163 * t19 * 2.0) -
                                       d31 * t13 * 2.0) +
                                      d147 * t8) -
                                     d35 * t13 * 2.0) -
                                    d37 * t13) -
                                   d148 * t4) -
                                  d149 * t4) +
                                 d150 * t8) -
                                d36 * CoefPS[15] * t8 * 3.0) +
                               d151 * t8) -
                              d152 * t4) +
                             d153 * t4 * 2.0) -
                            d154 * t4 * 2.0) +
                           d156 * t8) -
                          d157 * t4 * 2.0) -
                         d98 * CoefPS[14] * CoefPS[15] * 2.0) +
                        d167 * CoefPS[13] * CoefPS[15] * 2.0) -
                       d166 * CoefPS[10] * CoefPS[13]) +
                      d166 * CoefPS[11] * CoefPS[12] * 3.0) -
                     d80 * CoefPS[13] * CoefPS[15] * 4.0) +
                    d159 * CoefPS[12] * CoefPS[15] * 3.0) -
                   d159 * CoefPS[13] * CoefPS[14]) +
                  d160 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d160 * CoefPS[13] * CoefPS[14]) +
                d161 * CoefPS[12] * CoefPS[15] * 3.0) -
               d161 * CoefPS[13] * CoefPS[14]) +
              d162 * CoefPS[12] * CoefPS[14] * 2.0) -
             d163 * CoefPS[12] * CoefPS[14] * 4.0) -
            CoefPS[3] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0;
        dv1[9] = (((((((((((t5 * t21 + std::pow(CoefPS[7], 3.0) * t18) - d155 * t9) +
                          CoefPS[1] * t13 * t19) +
                         d118 * t20) -
                        d71 * t13 * 2.0) -
                       d75 * t13) +
                      d168 * t8) -
                     d169 * t4) +
                    d170 * t8) -
                   d171 * t4 * 2.0) +
                  d166 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d166 * CoefPS[13] * CoefPS[14];
        for (int i30{0}; i30 < 10; i30++) {
            dv2[i30] = dv1[9 - i30];
        }
        c_roots(&dv2[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation:203' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) &
        // (real(alpha1_v) >  0)));
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int c_k{0}; c_k < 9; c_k++) {
            double d172;
            bool g_b;
            g_b = (std::abs(b_alpha1_v[c_k].im) < 1.0E-11);
            d172 = b_alpha1_v[c_k].re;
            if (g_b && (d172 > 0.0)) {
                c_trueCount++;
                alpha1_t_data[c_partialTrueCount] = d172;
                c_partialTrueCount++;
            }
        }
        //  retain only positive real roots
        //  compute corresponding values of alpha0
        // 'G2_Hermite_Interpolation:206' alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
        // CALCALPHA0
        //     ALPHA0_S = CALCALPHA0(ALPHA1,IN2)
        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:35
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
        b_r2.set_size(c_trueCount);
        for (int i31{0}; i31 < c_trueCount; i31++) {
            b_r2[i31] = std::pow(alpha1_t_data[i31], 2.0);
        }
        t5_size = b_r2.size(0);
        i_loop_ub = b_r2.size(0);
        for (int i32{0}; i32 < i_loop_ub; i32++) {
            t5_data[i32] = b_r2[i32];
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        for (int i33{0}; i33 < c_trueCount; i33++) {
            t10_data[i33] = CoefPS[3] + alpha1_t_data[i33] * CoefPS[2];
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        for (int i34{0}; i34 < c_trueCount; i34++) {
            t11_data[i34] = 1.0 / (CoefPS[1] + CoefPS[0] * alpha1_t_data[i34]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        b_r2.set_size(c_trueCount);
        for (int i35{0}; i35 < c_trueCount; i35++) {
            b_r2[i35] = std::pow(alpha1_t_data[i35], 2.0);
        }
        r3.set_size(c_trueCount);
        for (int i36{0}; i36 < c_trueCount; i36++) {
            r3[i36] = std::pow(alpha1_t_data[i36], 3.0);
        }
        if (c_trueCount == 1) {
            d_trueCount = b_r2.size(0);
        } else {
            d_trueCount = c_trueCount;
        }
        if ((c_trueCount == b_r2.size(0)) && (d_trueCount == r3.size(0))) {
            t12_size = c_trueCount;
            for (int i37{0}; i37 < c_trueCount; i37++) {
                t12_data[i37] =
                    ((CoefPS[7] + alpha1_t_data[i37] * CoefPS[6]) + CoefPS[5] * b_r2[i37]) +
                    CoefPS[4] * r3[i37];
            }
        } else {
            binary_expand_op(t12_data, &t12_size, CoefPS, alpha1_t_data, &c_trueCount, b_r2, r3);
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        b_r2.set_size(c_trueCount);
        for (int i38{0}; i38 < c_trueCount; i38++) {
            b_r2[i38] = std::pow(t11_data[i38], 2.0);
        }
        r3.set_size(c_trueCount);
        for (int i39{0}; i39 < c_trueCount; i39++) {
            r3[i39] = std::pow(t10_data[i39], 2.0);
        }
        if (c_trueCount == 1) {
            e_trueCount = t5_size;
            f_trueCount = t12_size;
            g_trueCount = b_r2.size(0);
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
            j_trueCount = b_r2.size(0);
        } else {
            j_trueCount = c_trueCount;
        }
        if (j_trueCount == 1) {
            k_trueCount = t12_size;
        } else if (c_trueCount == 1) {
            k_trueCount = b_r2.size(0);
        } else {
            k_trueCount = c_trueCount;
        }
        if (c_trueCount == 1) {
            l_trueCount = t5_size;
        } else {
            l_trueCount = c_trueCount;
        }
        if (r3.size(0) == 1) {
            i40 = c_trueCount;
        } else {
            i40 = r3.size(0);
        }
        if (t12_size == 1) {
            if (r3.size(0) == 1) {
                b_t12_size = c_trueCount;
            } else {
                b_t12_size = r3.size(0);
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
                if (r3.size(0) == 1) {
                    o_trueCount = c_trueCount;
                } else {
                    o_trueCount = r3.size(0);
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
            r_trueCount = b_r2.size(0);
            s_trueCount = t5_size;
        } else {
            r_trueCount = c_trueCount;
            s_trueCount = c_trueCount;
        }
        if (q_trueCount == 1) {
            if (r_trueCount == 1) {
                t_trueCount = t12_size;
            } else if (c_trueCount == 1) {
                t_trueCount = b_r2.size(0);
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
                    if (r3.size(0) == 1) {
                        x_trueCount = c_trueCount;
                    } else {
                        x_trueCount = r3.size(0);
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
            (c_trueCount == b_r2.size(0)) && (g_trueCount == t12_size) &&
            (i_trueCount == k_trueCount) && (c_trueCount == t5_size) &&
            (l_trueCount == c_trueCount) && (r3.size(0) == c_trueCount) && (t12_size == i40) &&
            (c_trueCount == b_t12_size) && (n_trueCount == o_trueCount) &&
            (t_trueCount == x_trueCount)) {
            alpha0_t_size = c_trueCount;
            for (int i41{0}; i41 < c_trueCount; i41++) {
                double d173;
                double d174;
                double d175;
                double d176;
                double d177;
                d173 = alpha1_t_data[i41];
                d174 = t5_data[i41];
                d175 = t11_data[i41];
                d176 = t12_data[i41];
                d177 = t10_data[i41];
                alpha0_t_data[i41] = -((((CoefPS[15] + d173 * CoefPS[11]) + CoefPS[9] * d174) -
                                        CoefPS[13] * d175 * d176) +
                                       CoefPS[12] * d177 * b_r2[i41] * d176) /
                                     ((((CoefPS[14] + d173 * CoefPS[10]) + CoefPS[8] * d174) -
                                       CoefPS[13] * d177 * d175) -
                                      CoefPS[12] * d175 * (d176 - r3[i41] * d175));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &c_trueCount,
                             t5_data, &t5_size, t11_data, &c_trueCount, t12_data, &t12_size,
                             t10_data, &c_trueCount, b_r2, r3);
        }
        //
        // 'G2_Hermite_Interpolation:208' Idx       = find(alpha0_t > 0);
        for (int i42{0}; i42 < alpha0_t_size; i42++) {
            c_alpha0_t_data[i42] = (alpha0_t_data[i42] > 0.0);
        }
        coder::b_eml_find(c_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        // 'G2_Hermite_Interpolation:209' alpha1_u  = alpha1_t(Idx);
        // 'G2_Hermite_Interpolation:210' alpha0_u  = alpha0_t(Idx);
        //
        // 'G2_Hermite_Interpolation:213' if ~(numel(alpha0_u) > 0)
        if (Idx_size <= 0) {
            // 'G2_Hermite_Interpolation:214' status = int32(5);
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            // 'G2_Hermite_Interpolation:219' if length(alpha0_u) > 1
            if (Idx_size > 1) {
                int c_CostInt_size_tmp;
                // 'G2_Hermite_Interpolation:221' CostInt = zeros(size(alpha0_u));
                c_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:222' beta0_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:223' beta1_u = zeros(size(alpha0_u));
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                // 'G2_Hermite_Interpolation:225' for k = 1:length(alpha0_u)
                for (int d_k{0}; d_k < Idx_size; d_k++) {
                    int i43;
                    // 'G2_Hermite_Interpolation:227' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:228'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:229' r1D0, t1, n1,
                    // kappa1);
                    i43 = Idx_data[d_k];
                    Calc_beta0_beta1(alpha0_t_data[i43 - 1], alpha1_t_data[i43 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[d_k],
                                     &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation:230' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:231' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:232' r1D0, t1, n1, kappa1);
                    CostInt_data[d_k] = EvalCostIntegral(
                        alpha0_t_data[i43 - 1], beta0_u_data[d_k], alpha1_t_data[i43 - 1],
                        beta1_u_data[d_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int d_alpha0_tmp;
                // 'G2_Hermite_Interpolation:236' [~, Idx] = min(CostInt);
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &c_ex, &c_iindx);
                // 'G2_Hermite_Interpolation:237' alpha0   = alpha0_u(Idx);
                d_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[d_alpha0_tmp];
                // 'G2_Hermite_Interpolation:238' alpha1   = alpha1_u(Idx);
                *alpha1 = alpha1_t_data[d_alpha0_tmp];
                // 'G2_Hermite_Interpolation:239' beta0    = beta0_u(Idx);
                a = beta0_u_data[c_iindx - 1];
                // 'G2_Hermite_Interpolation:240' beta1    = beta1_u(Idx);
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                // 'G2_Hermite_Interpolation:242' else
                // 'G2_Hermite_Interpolation:244' alpha0   = alpha0_u(1);
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:245' alpha1   = alpha1_u(1);
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                // 'G2_Hermite_Interpolation:246' [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1,
                // ... 'G2_Hermite_Interpolation:247' r0D0, t0, n0, kappa0, ...
                // 'G2_Hermite_Interpolation:248'                                           r1D0,
                // t1, n1, kappa1);
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
            }
            guard1 = true;
        }
    }
    if (guard1) {
        double a_tmp;
        double b_a_tmp;
        double c_a;
        double d_a;
        int b_loop_ub;
        int loop_ub;
        //
        //  Hermite basis
        // 'G2_Hermite_Interpolation:255' h00 = [-6,    15,   -10,     0,     0,     1];
        // 'G2_Hermite_Interpolation:256' h10 = [-3,     8,    -6,     0,     1,     0];
        // 'G2_Hermite_Interpolation:257' h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
        // 'G2_Hermite_Interpolation:258' h01 = [6,   -15,     10,     0,     0,     0];
        // 'G2_Hermite_Interpolation:259' h11 = [-3,    7,     -4,     0,     0,     0];
        // 'G2_Hermite_Interpolation:260' h21 = [0.5,  -1,    0.5,     0,     0,     0];
        //  evaluate coefficients as sum of basis functions
        // 'G2_Hermite_Interpolation:262' p5_3D = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 +
        // kappa0*alpha0^2*n0) * h20 + ... 'G2_Hermite_Interpolation:263'         r1D0 * h01 +
        // alpha1*t1 * h11 + (beta1*t1 + kappa1*alpha1^2*n1) * h21;
        a_tmp = *alpha0 * *alpha0;
        c_a = kappa0 * a_tmp;
        b_a_tmp = *alpha1 * *alpha1;
        d_a = kappa1 * b_a_tmp;
        r.set_size(r0D0.size(0), 6);
        b_r1.set_size(r1D0.size(0), 6);
        loop_ub = r0D0.size(0);
        b_loop_ub = r1D0.size(0);
        for (int i6{0}; i6 < 6; i6++) {
            for (int i8{0}; i8 < loop_ub; i8++) {
                r[i8 + r.size(0) * i6] = r0D0[i8] * static_cast<double>(b[i6]);
            }
            for (int i12{0}; i12 < b_loop_ub; i12++) {
                b_r1[i12 + b_r1.size(0) * i6] = r1D0[i12] * static_cast<double>(d_b[i6]);
            }
        }
        if ((r.size(0) == 3) && (3 == b_r1.size(0))) {
            double a_idx_0;
            double a_idx_1;
            double a_idx_2;
            double d;
            double d2;
            double d3;
            int d_loop_ub;
            int f_loop_ub;
            d_loop_ub = r0D0.size(0);
            a_idx_0 = a * t0[0] + c_a * n0[0];
            a_idx_1 = a * t0[1] + c_a * n0[1];
            a_idx_2 = a * t0[2] + c_a * n0[2];
            f_loop_ub = r1D0.size(0);
            for (int i18{0}; i18 < 6; i18++) {
                for (int i21{0}; i21 < d_loop_ub; i21++) {
                    b_r0D0[i18][i21] = r0D0[i21] * static_cast<double>(b[i18]);
                }
                double d1;
                int alpha0_tmp;
                alpha0_tmp = b_b[i18];
                d1 = c_b[i18];
                c_r0D0[i18][0] =
                    (b_r0D0[i18][0] + *alpha0 * t0[0] * static_cast<double>(alpha0_tmp)) +
                    a_idx_0 * d1;
                c_r0D0[i18][1] =
                    (b_r0D0[i18][1] + *alpha0 * t0[1] * static_cast<double>(alpha0_tmp)) +
                    a_idx_1 * d1;
                c_r0D0[i18][2] =
                    (b_r0D0[i18][2] + *alpha0 * t0[2] * static_cast<double>(alpha0_tmp)) +
                    a_idx_2 * d1;
                for (int i26{0}; i26 < f_loop_ub; i26++) {
                    b_r1D0[i18][i26] = r1D0[i26] * static_cast<double>(d_b[i18]);
                }
            }
            a_idx_0 = b_a * t1[0] + d_a * n1[0];
            a_idx_1 = b_a * t1[1] + d_a * n1[1];
            a_idx_2 = b_a * t1[2] + d_a * n1[2];
            d = t1[0];
            d2 = t1[1];
            d3 = t1[2];
            for (int i24{0}; i24 < 6; i24++) {
                double d5;
                int p5_3D_tmp;
                p5_3D_tmp = e_b[i24];
                d5 = f_b[i24];
                p5_3D[i24][0] = ((c_r0D0[i24][0] + b_r1D0[i24][0]) +
                                 *alpha1 * d * static_cast<double>(p5_3D_tmp)) +
                                a_idx_0 * d5;
                p5_3D[i24][1] = ((c_r0D0[i24][1] + b_r1D0[i24][1]) +
                                 *alpha1 * d2 * static_cast<double>(p5_3D_tmp)) +
                                a_idx_1 * d5;
                p5_3D[i24][2] = ((c_r0D0[i24][2] + b_r1D0[i24][2]) +
                                 *alpha1 * d3 * static_cast<double>(p5_3D_tmp)) +
                                a_idx_2 * d5;
            }
        } else {
            binary_expand_op(p5_3D, r0D0, b, *alpha0, t0, b_b, a, c_a, n0, c_b, r1D0, d_b, *alpha1,
                             t1, e_b, b_a, d_a, n1, f_b);
        }
        //  last cross check ...
        // 'G2_Hermite_Interpolation:265' p1val = (a1*alpha1+a0)*alpha0^2  +  (b1*alpha1+b0)*alpha0
        // +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0; 'G2_Hermite_Interpolation:266' p2val =
        // (d1*alpha0+d0)*alpha1^2  +  (e1*alpha0+e0)*alpha1  +
        // f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        // 'G2_Hermite_Interpolation:269' if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
        if ((std::abs((((((CoefPS[0] * *alpha1 + CoefPS[1]) * a_tmp +
                          (CoefPS[2] * *alpha1 + CoefPS[3]) * *alpha0) +
                         CoefPS[4] * std::pow(*alpha1, 3.0)) +
                        CoefPS[5] * b_a_tmp) +
                       CoefPS[6] * *alpha1) +
                      CoefPS[7]) >= 1.0E-7) ||
            (std::abs((((((CoefPS[8] * *alpha0 + CoefPS[9]) * b_a_tmp +
                          (CoefPS[10] * *alpha0 + CoefPS[11]) * *alpha1) +
                         CoefPS[12] * std::pow(*alpha0, 3.0)) +
                        CoefPS[13] * a_tmp) +
                       CoefPS[14] * *alpha0) +
                      CoefPS[15]) >= 1.0E-7)) {
            // 'G2_Hermite_Interpolation:270' status = int32(6);
            *status = 6;
        }
    }
}

} // namespace ocn

//
// File trailer for G2_Hermite_Interpolation.cpp
//
// [EOF]
//
