//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:27:55
//

// Include Files
#include "G2_Hermite_Interpolation.h"
#include "CalcFrenet.h"
#include "Calc_beta0_beta1.h"
#include "CoefPolySys.h"
#include "EvalCostIntegral.h"
#include "div.h"
#include "find.h"
#include "minOrMax.h"
#include "functions.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// function [p5_3D, status, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1,
// r1D2)
//
// Arguments    : const double r0D0[3]
//                const double r0D1[3]
//                const double r0D2[3]
//                const double r1D0[3]
//                const double r1D1[3]
//                const double r1D2[3]
//                double p5_3D[6][3]
//                int *status
//                double *alpha0
//                double *alpha1
// Return Type  : void
//
namespace ocn {
void G2_Hermite_Interpolation(const double r0D0[3], const double r0D1[3], const double r0D2[3],
                              const double r1D0[3], const double r1D1[3], const double r1D2[3],
                              double p5_3D[6][3], int *status, double *alpha0, double *alpha1)
{
    static const double c_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double f_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char b_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char d_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char e_b[6]{-3, 7, -4, 0, 0, 0};
    creal_T b_alpha1_v[9];
    creal_T alpha0_v[3];
    creal_T alpha1_v[3];
    double b_r0D0[6][3];
    double b_r1D0[6][3];
    double CoefPS[16];
    double dv1[10];
    double dv2[10];
    double CostInt_data[9];
    double alpha0_t_data[9];
    double alpha1_t_data[9];
    double b_tmp_data[9];
    double beta0_u_data[9];
    double beta1_u_data[9];
    double c_tmp_data[9];
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
    int b_iindx;
    int c_iindx;
    int c_trueCount;
    int iindx;
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
    // 'G2_Hermite_Interpolation:39' [t0, n0, kappa0] = CalcFrenet(r0D1, r0D2);
    CalcFrenet(r0D1, r0D2, t0, n0, &kappa0);
    // 'G2_Hermite_Interpolation:40' [t1, n1, kappa1] = CalcFrenet(r1D1, r1D2);
    CalcFrenet(r1D1, r1D2, t1, n1, &kappa1);
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
        int trueCount;
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
            for (int i3{0}; i3 < trueCount; i3++) {
                b_tmp_data[i3] = std::pow(alpha1_t_data[i3], 2.0);
            }
            alpha0_t_size = trueCount;
            for (int i8{0}; i8 < trueCount; i8++) {
                alpha0_t_data[i8] =
                    -((CoefPS[9] * b_tmp_data[i8] + CoefPS[11] * alpha1_t_data[i8]) + CoefPS[15]) /
                    CoefPS[14];
            }
        } else {
            // 'G2_Hermite_Interpolation:96' else
            // 'G2_Hermite_Interpolation:97' alpha0_t =
            // -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
            for (int i5{0}; i5 < trueCount; i5++) {
                b_tmp_data[i5] = std::pow(alpha1_t_data[i5], 3.0);
            }
            for (int i7{0}; i7 < trueCount; i7++) {
                c_tmp_data[i7] = std::pow(alpha1_t_data[i7], 2.0);
            }
            alpha0_t_size = trueCount;
            for (int i11{0}; i11 < trueCount; i11++) {
                double d7;
                d7 = alpha1_t_data[i11];
                alpha0_t_data[i11] =
                    -(((CoefPS[4] * b_tmp_data[i11] + CoefPS[5] * c_tmp_data[i11]) +
                       CoefPS[6] * d7) +
                      CoefPS[7]) /
                    (CoefPS[2] * d7 + CoefPS[3]);
            }
        }
        // 'G2_Hermite_Interpolation:100' Idx       = find(alpha0_t > 0);
        for (int i13{0}; i13 < alpha0_t_size; i13++) {
            b_alpha0_t_data[i13] = (alpha0_t_data[i13] > 0.0);
        }
        coder::c_eml_find(b_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
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
                    int i17;
                    // 'G2_Hermite_Interpolation:118' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:119'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:120' r1D0, t1, n1,
                    // kappa1);
                    i17 = Idx_data[k];
                    Calc_beta0_beta1(alpha0_t_data[i17 - 1], alpha1_t_data[i17 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[k],
                                     &beta1_u_data[k]);
                    // 'G2_Hermite_Interpolation:121' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:122' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:123' r1D0, t1, n1, kappa1);
                    CostInt_data[k] = EvalCostIntegral(alpha0_t_data[i17 - 1], beta0_u_data[k],
                                                       alpha1_t_data[i17 - 1], beta1_u_data[k],
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
        int alpha1_t_size;
        int b_partialTrueCount;
        int b_trueCount;
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
            for (int i4{0}; i4 < b_trueCount; i4++) {
                b_tmp_data[i4] = std::pow(alpha0_t_data[i4], 2.0);
            }
            alpha1_t_size = b_trueCount;
            for (int i10{0}; i10 < b_trueCount; i10++) {
                alpha1_t_data[i10] =
                    -((CoefPS[1] * b_tmp_data[i10] + CoefPS[3] * alpha0_t_data[i10]) + CoefPS[7]) /
                    CoefPS[6];
            }
        } else {
            // 'G2_Hermite_Interpolation:153' else
            // 'G2_Hermite_Interpolation:154' alpha1_t =
            // -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
            for (int i6{0}; i6 < b_trueCount; i6++) {
                b_tmp_data[i6] = std::pow(alpha0_t_data[i6], 3.0);
            }
            for (int i9{0}; i9 < b_trueCount; i9++) {
                c_tmp_data[i9] = std::pow(alpha0_t_data[i9], 2.0);
            }
            alpha1_t_size = b_trueCount;
            for (int i12{0}; i12 < b_trueCount; i12++) {
                double d9;
                d9 = alpha0_t_data[i12];
                alpha1_t_data[i12] =
                    -(((CoefPS[12] * b_tmp_data[i12] + CoefPS[13] * c_tmp_data[i12]) +
                       CoefPS[14] * d9) +
                      CoefPS[15]) /
                    (CoefPS[10] * d9 + CoefPS[11]);
            }
        }
        // 'G2_Hermite_Interpolation:157' Idx      = find(alpha1_t > 0);
        for (int i14{0}; i14 < alpha1_t_size; i14++) {
            b_alpha1_t_data[i14] = (alpha1_t_data[i14] > 0.0);
        }
        coder::c_eml_find(b_alpha1_t_data, alpha1_t_size, Idx_data, &Idx_size);
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
                    int i18;
                    // 'G2_Hermite_Interpolation:174' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:175'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:176' r1D0, t1, n1,
                    // kappa1);
                    i18 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i18 - 1], alpha1_t_data[i18 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    // 'G2_Hermite_Interpolation:177' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:178' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:179' r1D0, t1, n1, kappa1);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[i18 - 1], beta0_u_data[b_k], alpha1_t_data[i18 - 1],
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
        double d174;
        double d175;
        double d176;
        double d177;
        double d178;
        double d179;
        double d18;
        double d180;
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
        int c_partialTrueCount;
        int d_trueCount;
        int e_trueCount;
        int f_trueCount;
        int g_trueCount;
        int h_trueCount;
        int i_trueCount;
        int t12_size;
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
        d16 = CoefPS[4] * t2;
        d17 = CoefPS[0] * CoefPS[8] * CoefPS[12];
        dv1[0] = (std::pow(CoefPS[4], 3.0) * t18 + d16 * t14) - d17 * t10 * 2.0;
        d18 = CoefPS[0] * CoefPS[1];
        d19 = CoefPS[4] * CoefPS[8];
        d20 = d18 * CoefPS[4];
        d21 = CoefPS[0] * CoefPS[4];
        d22 = d21 * CoefPS[5];
        d23 = CoefPS[5] * t2;
        d24 = CoefPS[1] * CoefPS[8] * CoefPS[12];
        d25 = d19 * CoefPS[10];
        d26 = CoefPS[0] * CoefPS[10] * CoefPS[12];
        dv1[1] =
            (((((d23 * t14 + CoefPS[5] * t10 * t18 * 3.0) + d20 * t14 * 2.0) - d24 * t10 * 2.0) +
              d25 * t2 * 2.0) -
             d26 * t10 * 2.0) -
            d22 * CoefPS[8] * CoefPS[12] * 4.0;
        d27 = CoefPS[0] * CoefPS[2];
        d28 = d27 * CoefPS[4];
        d29 = CoefPS[2] * CoefPS[8];
        d30 = CoefPS[5] * CoefPS[8];
        d31 = d18 * CoefPS[5];
        d32 = d20 * CoefPS[8];
        d33 = CoefPS[1] * CoefPS[4];
        d34 = d21 * CoefPS[6];
        d35 = d33 * CoefPS[5];
        d36 = CoefPS[4] * t4;
        d37 = CoefPS[6] * t2;
        d38 = d29 * CoefPS[9];
        d39 = d30 * CoefPS[10];
        d40 = CoefPS[1] * CoefPS[10] * CoefPS[12];
        d41 = d19 * CoefPS[12];
        d42 = d19 * CoefPS[14];
        d43 = CoefPS[4] * CoefPS[9] * CoefPS[13];
        d44 = CoefPS[0] * CoefPS[12] * CoefPS[14];
        d45 = CoefPS[2] * CoefPS[12];
        d46 = d45 * CoefPS[13];
        dv1[2] = (((((((((((((((((((((t3 * t15 + CoefPS[0] * t10 * t19) + d16 * t16) + d36 * t14) +
                                   CoefPS[4] * t11 * t18 * 3.0) +
                                  d37 * t14) +
                                 CoefPS[6] * t10 * t18 * 3.0) +
                                d31 * t14 * 2.0) -
                               d38 * t2) -
                              d17 * t11 * 2.0) +
                             d39 * t2 * 2.0) -
                            d40 * t10 * 2.0) +
                           d41 * t6) +
                          d42 * t2 * 2.0) -
                         d43 * t2 * 2.0) -
                        d44 * t10 * 2.0) -
                       d46 * t10) +
                      d32 * CoefPS[10] * 4.0) -
                     d28 * CoefPS[8] * CoefPS[13]) +
                    d28 * CoefPS[9] * CoefPS[12] * 3.0) -
                   d34 * CoefPS[8] * CoefPS[12] * 4.0) -
                  d35 * CoefPS[8] * CoefPS[12] * 4.0) -
                 d22 * CoefPS[10] * CoefPS[12] * 4.0;
        d47 = CoefPS[9] * CoefPS[11];
        d48 = CoefPS[1] * t2;
        d49 = CoefPS[4] * CoefPS[10];
        d50 = d27 * CoefPS[5];
        d51 = CoefPS[0] * CoefPS[3];
        d52 = d51 * CoefPS[4];
        d53 = CoefPS[1] * CoefPS[2];
        d54 = d53 * CoefPS[4];
        d55 = CoefPS[4] * CoefPS[5];
        d56 = CoefPS[3] * CoefPS[8];
        d57 = CoefPS[2] * CoefPS[9];
        d58 = CoefPS[6] * CoefPS[8];
        d59 = d18 * CoefPS[2];
        d60 = d59 * CoefPS[8];
        d61 = d18 * CoefPS[6];
        d62 = d31 * CoefPS[8];
        d63 = CoefPS[2] * CoefPS[3];
        d64 = d63 * CoefPS[4];
        d65 = CoefPS[0] * CoefPS[5];
        d66 = d21 * CoefPS[7];
        d67 = d65 * CoefPS[6];
        d68 = d33 * CoefPS[6];
        d69 = CoefPS[2] * CoefPS[4];
        d70 = CoefPS[5] * t4;
        d71 = CoefPS[7] * t2;
        d72 = d56 * CoefPS[9];
        d73 = d29 * CoefPS[11];
        d74 = d57 * CoefPS[10];
        d75 = d58 * CoefPS[10];
        d76 = d30 * CoefPS[12];
        d77 = d49 * CoefPS[12];
        d78 = d30 * CoefPS[14];
        d79 = CoefPS[5] * CoefPS[9] * CoefPS[13];
        d80 = CoefPS[1] * CoefPS[12] * CoefPS[14];
        d81 = d49 * CoefPS[14];
        d82 = CoefPS[4] * CoefPS[11] * CoefPS[13];
        d83 = CoefPS[3] * CoefPS[12];
        d84 = d83 * CoefPS[13];
        dv1[3] = (((((((((((((((((((((((((((((((((((((((((((((std::pow(CoefPS[5], 3.0) * t18 +
                                                              d47 * t3 * 2.0) +
                                                             d48 * t15 * 3.0) +
                                                            CoefPS[1] * t10 * t19) +
                                                           d23 * t16) +
                                                          d70 * t14) +
                                                         d71 * t14) +
                                                        CoefPS[7] * t10 * t18 * 3.0) +
                                                       d20 * t16 * 2.0) +
                                                      d61 * t14 * 2.0) +
                                                     d22 * t19 * 2.0) +
                                                    d55 * CoefPS[6] * t18 * 6.0) -
                                                   d72 * t2) -
                                                  d73 * t2) -
                                                 d74 * t2) -
                                                d24 * t11 * 2.0) +
                                               d25 * t4 * 2.0) -
                                              d26 * t11 * 2.0) +
                                             d75 * t2 * 2.0) +
                                            d76 * t6) +
                                           d77 * t6) +
                                          d78 * t2 * 2.0) -
                                         d79 * t2 * 2.0) -
                                        d80 * t10 * 2.0) +
                                       d81 * t2 * 2.0) -
                                      d82 * t2 * 2.0) -
                                     d84 * t10) -
                                    d60 * CoefPS[9] * 2.0) +
                                   d62 * CoefPS[10] * 4.0) +
                                  d32 * CoefPS[14] * 4.0) -
                                 d20 * CoefPS[9] * CoefPS[13] * 4.0) -
                                d50 * CoefPS[8] * CoefPS[13]) +
                               d50 * CoefPS[9] * CoefPS[12] * 3.0) -
                              d52 * CoefPS[8] * CoefPS[13]) +
                             d52 * CoefPS[9] * CoefPS[12] * 3.0) -
                            d54 * CoefPS[8] * CoefPS[13]) +
                           d54 * CoefPS[9] * CoefPS[12] * 3.0) -
                          d28 * CoefPS[10] * CoefPS[13]) +
                         d28 * CoefPS[11] * CoefPS[12] * 3.0) +
                        d64 * CoefPS[8] * CoefPS[12] * 2.0) -
                       d66 * CoefPS[8] * CoefPS[12] * 4.0) -
                      d67 * CoefPS[8] * CoefPS[12] * 4.0) -
                     d68 * CoefPS[8] * CoefPS[12] * 4.0) -
                    d34 * CoefPS[10] * CoefPS[12] * 4.0) -
                   d35 * CoefPS[10] * CoefPS[12] * 4.0) -
                  d22 * CoefPS[12] * CoefPS[14] * 4.0) -
                 d69 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0;
        d85 = CoefPS[0] * CoefPS[9];
        d86 = CoefPS[1] * CoefPS[9];
        d87 = CoefPS[3] * CoefPS[9];
        d88 = CoefPS[2] * CoefPS[10];
        d89 = d18 * CoefPS[7];
        d90 = CoefPS[0] * t4;
        d91 = CoefPS[6] * t4;
        d92 = d56 * CoefPS[11];
        d93 = d87 * CoefPS[10];
        d94 = d85 * CoefPS[13];
        d95 = d88 * CoefPS[11];
        d96 = d29 * CoefPS[15];
        d97 = d57 * CoefPS[14];
        d98 = CoefPS[9] * CoefPS[12];
        d99 = CoefPS[9] * CoefPS[15];
        d100 = CoefPS[7] * CoefPS[8];
        d101 = d100 * CoefPS[10];
        d102 = d27 * CoefPS[6];
        d103 = d51 * CoefPS[5];
        d104 = d53 * CoefPS[5];
        d105 = CoefPS[1] * CoefPS[3];
        d106 = d105 * CoefPS[4];
        d107 = d18 * CoefPS[3];
        d108 = d107 * CoefPS[8];
        d109 = d63 * CoefPS[5];
        d110 = CoefPS[1] * CoefPS[5];
        d111 = d65 * CoefPS[7];
        d112 = d33 * CoefPS[7];
        d113 = d110 * CoefPS[6];
        d114 = CoefPS[3] * CoefPS[4];
        d115 = CoefPS[6] * CoefPS[9] * CoefPS[13];
        d116 = CoefPS[5] * CoefPS[10];
        d117 = d116 * CoefPS[14];
        d118 = CoefPS[5] * CoefPS[11] * CoefPS[13];
        d119 = CoefPS[4] * CoefPS[12] * CoefPS[14];
        d120 = CoefPS[4] * CoefPS[13] * CoefPS[15];
        d121 = d59 * CoefPS[9];
        d122 = d116 * CoefPS[12];
        d123 = d58 * CoefPS[14];
        dv1[4] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t17 - d98 * t7) + d99 * t3 * 2.0) + d90 * t15 * 3.0) + CoefPS[0] * t11 * t19) + d36 * t16) + d16 * t20) + CoefPS[4] * t12 * t18 * 3.0) + d37 * t16) + d91 * t14) + CoefPS[6] * t11 * t18 * 3.0) + d31 * t16 * 2.0) + d89 * t14 * 2.0) + d34 * t19 * 2.0) + d35 * t19 * 2.0) + d55 * CoefPS[7] * t18 * 6.0) - d38 * t4) - d17 * t12 * 2.0) + d86 * CoefPS[11] * t2 * 6.0) - d92 * t2) - d93 * t2) + d94 * t6) - d95 * t2) + d39 * t4 * 2.0) - d40 * t11 * 2.0) + d41 * t8) - d96 * t2) - d97 * t2) + d101 * t2 * 2.0) + d42 * t4 * 2.0) - d43 * t4 * 2.0) + d58 * CoefPS[12] * t6) - d44 * t11 * 2.0) + d122 * t6) - d46 * t11) + d123 * t2 * 2.0) - d115 * t2 * 2.0) + d117 * t2 * 2.0) - d118 * t2 * 2.0) + d119 * t6) - d120 * t2 * 2.0) - d108 * CoefPS[9] * 2.0) - d60 * CoefPS[11] * 2.0) - d121 * CoefPS[10] * 2.0) + d61 * CoefPS[8] * CoefPS[10] * 4.0) + d62 * CoefPS[14] * 4.0) - d31 * CoefPS[9] * CoefPS[13] * 4.0) + d20 * CoefPS[10] * CoefPS[14] * 4.0) - d20 * CoefPS[11] * CoefPS[13] * 4.0) - d102 * CoefPS[8] * CoefPS[13]) + d102 * CoefPS[9] * CoefPS[12] * 3.0) - d103 * CoefPS[8] * CoefPS[13]) + d103 * CoefPS[9] * CoefPS[12] * 3.0) - d104 * CoefPS[8] * CoefPS[13]) + d104 * CoefPS[9] * CoefPS[12] * 3.0) - d106 * CoefPS[8] * CoefPS[13]) + d106 * CoefPS[9] * CoefPS[12] * 3.0) - d50 * CoefPS[10] * CoefPS[13]) + d50 * CoefPS[11] * CoefPS[12] * 3.0) - d52 * CoefPS[10] * CoefPS[13]) + d52 * CoefPS[11] * CoefPS[12] * 3.0) - d54 * CoefPS[10] * CoefPS[13]) + d54 * CoefPS[11] * CoefPS[12] * 3.0) + d109 * CoefPS[8] * CoefPS[12] * 2.0) + d64 * CoefPS[10] * CoefPS[12] * 2.0) - d111 * CoefPS[8] * CoefPS[12] * 4.0) - d112 * CoefPS[8] * CoefPS[12] * 4.0) - d113 * CoefPS[8] * CoefPS[12] * 4.0) + d28 * CoefPS[12] * CoefPS[15] * 3.0) - d28 * CoefPS[13] * CoefPS[14]) - d66 * CoefPS[10] * CoefPS[12] * 4.0) - d67 * CoefPS[10] * CoefPS[12] * 4.0) - d68 * CoefPS[10] * CoefPS[12] * 4.0) - d34 * CoefPS[12] * CoefPS[14] * 4.0) - d35 * CoefPS[12] * CoefPS[14] * 4.0) - d69 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d114 * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0;
        d124 = CoefPS[11] * CoefPS[15];
        d125 = CoefPS[6] * CoefPS[10];
        d126 = CoefPS[3] * CoefPS[10];
        d127 = CoefPS[7] * t4;
        d128 = d86 * CoefPS[13];
        d129 = d126 * CoefPS[11];
        d130 = CoefPS[0] * CoefPS[11];
        d131 = d130 * CoefPS[13];
        d132 = CoefPS[2] * CoefPS[11];
        d133 = d56 * CoefPS[15];
        d134 = d87 * CoefPS[14];
        d135 = d88 * CoefPS[15];
        d136 = d132 * CoefPS[14];
        d137 = CoefPS[7] * CoefPS[9] * CoefPS[13];
        d138 = d125 * CoefPS[14];
        d139 = CoefPS[6] * CoefPS[11] * CoefPS[13];
        d140 = CoefPS[5] * CoefPS[12] * CoefPS[14];
        d141 = CoefPS[5] * CoefPS[13] * CoefPS[15];
        d142 = d27 * CoefPS[7];
        d143 = d51 * CoefPS[6];
        d144 = d53 * CoefPS[6];
        d145 = d105 * CoefPS[5];
        d146 = d63 * CoefPS[6];
        d147 = CoefPS[0] * CoefPS[6] * CoefPS[7];
        d148 = d110 * CoefPS[7];
        d149 = CoefPS[2] * CoefPS[5];
        d150 = d107 * CoefPS[9];
        d151 = d59 * CoefPS[10];
        d152 = d100 * CoefPS[12];
        dv1[5] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t15 - CoefPS[11] * CoefPS[12] * t7) + d124 * t3 * 2.0) + d48 * t17 * 3.0) + CoefPS[1] * t11 * t19) + d70 * t16) + d23 * t20) + CoefPS[5] * t12 * t18 * 3.0) + d71 * t16) + d127 * t14) + CoefPS[7] * t11 * t18 * 3.0) + d20 * t20 * 2.0) + d61 * t16 * 2.0) + d66 * t19 * 2.0) + d67 * t19 * 2.0) + d68 * t19 * 2.0) + CoefPS[4] * CoefPS[6] * CoefPS[7] * t18 * 6.0) + d85 * CoefPS[11] * t4 * 6.0) - d72 * t4) - d73 * t4) - d74 * t4) - d24 * t12 * 2.0) - d26 * t12 * 2.0) + d128 * t6) - d129 * t2) + d75 * t4 * 2.0) + d131 * t6) - d87 * CoefPS[12] * t6 * 3.0) + d86 * CoefPS[15] * t2 * 6.0) + d76 * t8) - d133 * t2) - d134 * t2) + d77 * t8) - d135 * t2) - d136 * t2) + d78 * t4 * 2.0) - d79 * t4 * 2.0) + d152 * t6) - d80 * t11 * 2.0) + d81 * t4 * 2.0) - d82 * t4 * 2.0) + d125 * CoefPS[12] * t6) - d84 * t11) + d100 * CoefPS[14] * t2 * 2.0) - d137 * t2 * 2.0) + d138 * t2 * 2.0) - d139 * t2 * 2.0) + d140 * t6) - d141 * t2 * 2.0) - d108 * CoefPS[11] * 2.0) - d150 * CoefPS[10] * 2.0) - d151 * CoefPS[11] * 2.0) - d60 * CoefPS[15] * 2.0) - d121 * CoefPS[14] * 2.0) + d89 * CoefPS[8] * CoefPS[10] * 4.0) + d27 * CoefPS[3] * CoefPS[9] * CoefPS[13] * 2.0) + d18 * CoefPS[6] * CoefPS[8] * CoefPS[14] * 4.0) - CoefPS[0] * CoefPS[1] * CoefPS[6] * CoefPS[9] * CoefPS[13] * 4.0) + d31 * CoefPS[10] * CoefPS[14] * 4.0) - d31 * CoefPS[11] * CoefPS[13] * 4.0) - d142 * CoefPS[8] * CoefPS[13]) + d142 * CoefPS[9] * CoefPS[12] * 3.0) - d143 * CoefPS[8] * CoefPS[13]) + d143 * CoefPS[9] * CoefPS[12] * 3.0) - d144 * CoefPS[8] * CoefPS[13]) + d144 * CoefPS[9] * CoefPS[12] * 3.0) - d145 * CoefPS[8] * CoefPS[13]) + d145 * CoefPS[9] * CoefPS[12] * 3.0) - d102 * CoefPS[10] * CoefPS[13]) + d102 * CoefPS[11] * CoefPS[12] * 3.0) - d103 * CoefPS[10] * CoefPS[13]) + d103 * CoefPS[11] * CoefPS[12] * 3.0) - d104 * CoefPS[10] * CoefPS[13]) + d104 * CoefPS[11] * CoefPS[12] * 3.0) - d106 * CoefPS[10] * CoefPS[13]) + d106 * CoefPS[11] * CoefPS[12] * 3.0) + d146 * CoefPS[8] * CoefPS[12] * 2.0) + d109 * CoefPS[10] * CoefPS[12] * 2.0) - d20 * CoefPS[13] * CoefPS[15] * 4.0) - d147 * CoefPS[8] * CoefPS[12] * 4.0) - d148 * CoefPS[8] * CoefPS[12] * 4.0) + d50 * CoefPS[12] * CoefPS[15] * 3.0) - d50 * CoefPS[13] * CoefPS[14]) + d52 * CoefPS[12] * CoefPS[15] * 3.0) - d52 * CoefPS[13] * CoefPS[14]) - d111 * CoefPS[10] * CoefPS[12] * 4.0) + d54 * CoefPS[12] * CoefPS[15] * 3.0) - d54 * CoefPS[13] * CoefPS[14]) - d112 * CoefPS[10] * CoefPS[12] * 4.0) - d113 * CoefPS[10] * CoefPS[12] * 4.0) + d64 * CoefPS[12] * CoefPS[14] * 2.0) - d66 * CoefPS[12] * CoefPS[14] * 4.0) - d67 * CoefPS[12] * CoefPS[14] * 4.0) - d68 * CoefPS[12] * CoefPS[14] * 4.0) - d69 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d149 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d114 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0;
        d153 = CoefPS[1] * CoefPS[11];
        d154 = CoefPS[3] * CoefPS[11];
        d155 = CoefPS[7] * CoefPS[10];
        d156 = d153 * CoefPS[13];
        d157 = d126 * CoefPS[15];
        d158 = d154 * CoefPS[14];
        d159 = CoefPS[0] * CoefPS[13] * CoefPS[15];
        d160 = d155 * CoefPS[12];
        d161 = CoefPS[2] * CoefPS[14] * CoefPS[15];
        d162 = d155 * CoefPS[14];
        d163 = CoefPS[7] * CoefPS[11] * CoefPS[13];
        d164 = CoefPS[12] * CoefPS[15];
        d165 = CoefPS[6] * CoefPS[12] * CoefPS[14];
        d166 = CoefPS[6] * CoefPS[13] * CoefPS[15];
        d167 = d107 * CoefPS[10];
        d168 = d51 * CoefPS[7];
        d169 = d53 * CoefPS[7];
        d170 = d105 * CoefPS[6];
        d171 = d63 * CoefPS[7];
        d172 = CoefPS[1] * CoefPS[6] * CoefPS[7];
        d173 = CoefPS[3] * CoefPS[5];
        d174 = CoefPS[0] * CoefPS[2] * CoefPS[3];
        dv1[6] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t21 + std::pow(CoefPS[6], 3.0) * t18) + d47 * t5 * 2.0) - d164 * t7) + d90 * t17 * 3.0) + CoefPS[0] * t12 * t19) + d36 * t20) + CoefPS[4] * t13 * t18 * 3.0) + d91 * t16) + d37 * t20) + d31 * t20 * 2.0) + d89 * t16 * 2.0) + d111 * t19 * 2.0) + d112 * t19 * 2.0) + d113 * t19 * 2.0) + CoefPS[5] * CoefPS[6] * CoefPS[7] * t18 * 6.0) - d17 * t13 * 2.0) - d92 * t4) - d93 * t4) + d94 * t8) - d95 * t4) - d57 * CoefPS[12] * t8 * 3.0) - d40 * t12 * 2.0) + d85 * CoefPS[15] * t4 * 6.0) - d96 * t4) - d97 * t4) + d101 * t4 * 2.0) + d156 * t6) - d154 * CoefPS[12] * t6 * 3.0) + CoefPS[6] * CoefPS[8] * CoefPS[12] * t8) - d44 * t12 * 2.0) + d153 * CoefPS[15] * t2 * 6.0) + d122 * t8) - d46 * t12) - d157 * t2) - d158 * t2) + d123 * t4 * 2.0) - d115 * t4 * 2.0) + d159 * t6) + d117 * t4 * 2.0) - d118 * t4 * 2.0) + d160 * t6) + d119 * t8) - d161 * t2) + d162 * t2 * 2.0) - d163 * t2 * 2.0) - d120 * t4 * 2.0) + d165 * t6) - d166 * t2 * 2.0) - d167 * CoefPS[11] * 2.0) - d108 * CoefPS[15] * 2.0) - d150 * CoefPS[14] * 2.0) - d151 * CoefPS[15] * 2.0) - d59 * CoefPS[11] * CoefPS[14] * 2.0) + d53 * CoefPS[3] * CoefPS[9] * CoefPS[13] * 2.0) + d174 * CoefPS[11] * CoefPS[13] * 2.0) + CoefPS[0] * CoefPS[1] * CoefPS[7] * CoefPS[8] * CoefPS[14] * 4.0) - d89 * CoefPS[9] * CoefPS[13] * 4.0) + d61 * CoefPS[10] * CoefPS[14] * 4.0) - d61 * CoefPS[11] * CoefPS[13] * 4.0) - d168 * CoefPS[8] * CoefPS[13]) + d168 * CoefPS[9] * CoefPS[12] * 3.0) - d169 * CoefPS[8] * CoefPS[13]) + d169 * CoefPS[9] * CoefPS[12] * 3.0) - d170 * CoefPS[8] * CoefPS[13]) + d170 * CoefPS[9] * CoefPS[12] * 3.0) - d142 * CoefPS[10] * CoefPS[13]) + d142 * CoefPS[11] * CoefPS[12] * 3.0) - d143 * CoefPS[10] * CoefPS[13]) + d143 * CoefPS[11] * CoefPS[12] * 3.0) - d144 * CoefPS[10] * CoefPS[13]) + d144 * CoefPS[11] * CoefPS[12] * 3.0) - d145 * CoefPS[10] * CoefPS[13]) + d145 * CoefPS[11] * CoefPS[12] * 3.0) + d171 * CoefPS[8] * CoefPS[12] * 2.0) + d146 * CoefPS[10] * CoefPS[12] * 2.0) - d31 * CoefPS[13] * CoefPS[15] * 4.0) - d172 * CoefPS[8] * CoefPS[12] * 4.0) + d102 * CoefPS[12] * CoefPS[15] * 3.0) - d102 * CoefPS[13] * CoefPS[14]) + d103 * CoefPS[12] * CoefPS[15] * 3.0) - d103 * CoefPS[13] * CoefPS[14]) - d147 * CoefPS[10] * CoefPS[12] * 4.0) + d104 * CoefPS[12] * CoefPS[15] * 3.0) - d104 * CoefPS[13] * CoefPS[14]) + d106 * CoefPS[12] * CoefPS[15] * 3.0) - d106 * CoefPS[13] * CoefPS[14]) - d148 * CoefPS[10] * CoefPS[12] * 4.0) + d109 * CoefPS[12] * CoefPS[14] * 2.0) - d111 * CoefPS[12] * CoefPS[14] * 4.0) - d112 * CoefPS[12] * CoefPS[14] * 4.0) - d113 * CoefPS[12] * CoefPS[14] * 4.0) - d149 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d114 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d173 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0;
        d175 = d105 * CoefPS[7];
        d176 = CoefPS[1] * CoefPS[2] * CoefPS[3];
        d177 = CoefPS[1] * CoefPS[13] * CoefPS[15];
        d178 = CoefPS[3] * CoefPS[14] * CoefPS[15];
        d179 = CoefPS[7] * CoefPS[12] * CoefPS[14];
        d180 = CoefPS[7] * CoefPS[13] * CoefPS[15];
        dv1[7] = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t17 - d98 * t9) + d99 * t5 * 2.0) + d48 * t21 * 3.0) + CoefPS[1] * t12 * t19) + d70 * t20) + CoefPS[5] * t13 * t18 * 3.0) + d127 * t16) + d71 * t20) + CoefPS[7] * t12 * t18 * 3.0) + d61 * t20 * 2.0) + d147 * t19 * 2.0) + d148 * t19 * 2.0) - d24 * t13 * 2.0) - d26 * t13 * 2.0) + d128 * t8) - d129 * t4) + d131 * t8) - d132 * CoefPS[12] * t8 * 3.0) + d130 * CoefPS[15] * t4 * 6.0) - d133 * t4) - d134 * t4) - d135 * t4) - d136 * t4) + d152 * t8) - d80 * t12 * 2.0) + CoefPS[6] * CoefPS[10] * CoefPS[12] * t8) - d84 * t12) + CoefPS[7] * CoefPS[8] * CoefPS[14] * t4 * 2.0) - d137 * t4 * 2.0) + d177 * t6) + d138 * t4 * 2.0) - d139 * t4 * 2.0) - d83 * CoefPS[15] * t6 * 3.0) + d140 * t8) - d178 * t2) - d141 * t4 * 2.0) + d179 * t6) - d180 * t2 * 2.0) - d167 * CoefPS[15] * 2.0) - d107 * CoefPS[11] * CoefPS[14] * 2.0) + d176 * CoefPS[11] * CoefPS[13] * 2.0) - d59 * CoefPS[14] * CoefPS[15] * 2.0) + d89 * CoefPS[10] * CoefPS[14] * 4.0) - d89 * CoefPS[11] * CoefPS[13] * 4.0) - d175 * CoefPS[8] * CoefPS[13]) + d175 * CoefPS[9] * CoefPS[12] * 3.0) + d174 * CoefPS[13] * CoefPS[15] * 2.0) - d168 * CoefPS[10] * CoefPS[13]) + d168 * CoefPS[11] * CoefPS[12] * 3.0) - d169 * CoefPS[10] * CoefPS[13]) + d169 * CoefPS[11] * CoefPS[12] * 3.0) - d170 * CoefPS[10] * CoefPS[13]) + d170 * CoefPS[11] * CoefPS[12] * 3.0) + d171 * CoefPS[10] * CoefPS[12] * 2.0) - d61 * CoefPS[13] * CoefPS[15] * 4.0) + d142 * CoefPS[12] * CoefPS[15] * 3.0) - d142 * CoefPS[13] * CoefPS[14]) + d143 * CoefPS[12] * CoefPS[15] * 3.0) - d143 * CoefPS[13] * CoefPS[14]) + d144 * CoefPS[12] * CoefPS[15] * 3.0) - d144 * CoefPS[13] * CoefPS[14]) + d145 * CoefPS[12] * CoefPS[15] * 3.0) - d145 * CoefPS[13] * CoefPS[14]) - d172 * CoefPS[10] * CoefPS[12] * 4.0) + d146 * CoefPS[12] * CoefPS[14] * 2.0) - d147 * CoefPS[12] * CoefPS[14] * 4.0) - d148 * CoefPS[12] * CoefPS[14] * 4.0) - CoefPS[2] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d173 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0;
        dv1[8] =
            ((((((((((((((((((((((((((((((((((-CoefPS[11] * CoefPS[12] * t9 + d124 * t5 * 2.0) +
                                             d90 * t21 * 3.0) +
                                            CoefPS[0] * t13 * t19) +
                                           d91 * t20) +
                                          CoefPS[6] * t13 * t18 * 3.0) +
                                         d89 * t20 * 2.0) +
                                        d172 * t19 * 2.0) -
                                       d40 * t13 * 2.0) +
                                      d156 * t8) -
                                     d44 * t13 * 2.0) -
                                    d46 * t13) -
                                   d157 * t4) -
                                  d158 * t4) +
                                 d159 * t8) -
                                d45 * CoefPS[15] * t8 * 3.0) +
                               d160 * t8) -
                              d161 * t4) +
                             d162 * t4 * 2.0) -
                            d163 * t4 * 2.0) +
                           d165 * t8) -
                          d166 * t4 * 2.0) -
                         d107 * CoefPS[14] * CoefPS[15] * 2.0) +
                        d176 * CoefPS[13] * CoefPS[15] * 2.0) -
                       d175 * CoefPS[10] * CoefPS[13]) +
                      d175 * CoefPS[11] * CoefPS[12] * 3.0) -
                     d89 * CoefPS[13] * CoefPS[15] * 4.0) +
                    d168 * CoefPS[12] * CoefPS[15] * 3.0) -
                   d168 * CoefPS[13] * CoefPS[14]) +
                  d169 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d169 * CoefPS[13] * CoefPS[14]) +
                d170 * CoefPS[12] * CoefPS[15] * 3.0) -
               d170 * CoefPS[13] * CoefPS[14]) +
              d171 * CoefPS[12] * CoefPS[14] * 2.0) -
             d172 * CoefPS[12] * CoefPS[14] * 4.0) -
            CoefPS[3] * CoefPS[6] * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0;
        dv1[9] = (((((((((((t5 * t21 + std::pow(CoefPS[7], 3.0) * t18) - d164 * t9) +
                          CoefPS[1] * t13 * t19) +
                         d127 * t20) -
                        d80 * t13 * 2.0) -
                       d84 * t13) +
                      d177 * t8) -
                     d178 * t4) +
                    d179 * t8) -
                   d180 * t4 * 2.0) +
                  d175 * CoefPS[12] * CoefPS[15] * 3.0) -
                 d175 * CoefPS[13] * CoefPS[14];
        for (int i19{0}; i19 < 10; i19++) {
            dv2[i19] = dv1[9 - i19];
        }
        c_roots(&dv2[0], &b_alpha1_v[0], 10);
        //  all roots of 9th degree polynomial in alpha1
        // 'G2_Hermite_Interpolation:203' alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) &
        // (real(alpha1_v) >  0)));
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int c_k{0}; c_k < 9; c_k++) {
            double d181;
            bool g_b;
            g_b = (std::abs(b_alpha1_v[c_k].im) < 1.0E-11);
            d181 = b_alpha1_v[c_k].re;
            if (g_b && (d181 > 0.0)) {
                c_trueCount++;
                alpha1_t_data[c_partialTrueCount] = d181;
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
        for (int i20{0}; i20 < c_trueCount; i20++) {
            t5_data[i20] = std::pow(alpha1_t_data[i20], 2.0);
        }
        // 'CalcAlpha0:28' t6 = alpha1.^3;
        // 'CalcAlpha0:29' t7 = c2.*t5;
        // 'CalcAlpha0:30' t8 = c3.*t6;
        // 'CalcAlpha0:31' t9 = a0+t2;
        // 'CalcAlpha0:32' t10 = b0+t3;
        for (int i21{0}; i21 < c_trueCount; i21++) {
            t10_data[i21] = CoefPS[3] + alpha1_t_data[i21] * CoefPS[2];
        }
        // 'CalcAlpha0:33' t11 = 1.0./t9;
        for (int i22{0}; i22 < c_trueCount; i22++) {
            t11_data[i22] = 1.0 / (CoefPS[1] + CoefPS[0] * alpha1_t_data[i22]);
        }
        // 'CalcAlpha0:34' t12 = c0+t4+t7+t8;
        for (int i23{0}; i23 < c_trueCount; i23++) {
            b_tmp_data[i23] = std::pow(alpha1_t_data[i23], 3.0);
        }
        for (int i24{0}; i24 < c_trueCount; i24++) {
            t12_data[i24] =
                ((CoefPS[7] + alpha1_t_data[i24] * CoefPS[6]) + CoefPS[5] * t5_data[i24]) +
                CoefPS[4] * b_tmp_data[i24];
        }
        // 'CalcAlpha0:35' alpha0_s =
        // -(f0+alpha1.*e0+d0.*t5-f2.*t11.*t12+f3.*t10.*t11.^2.*t12)./(f1+alpha1.*e1+d1.*t5-f2.*t10.*t11-f3.*t11.*(t12-t10.^2.*t11));
        for (int i25{0}; i25 < c_trueCount; i25++) {
            b_tmp_data[i25] = std::pow(t11_data[i25], 2.0);
        }
        for (int i26{0}; i26 < c_trueCount; i26++) {
            c_tmp_data[i26] = std::pow(t10_data[i26], 2.0);
        }
        if (c_trueCount == 1) {
            d_trueCount = c_trueCount;
            e_trueCount = c_trueCount;
            f_trueCount = c_trueCount;
        } else {
            d_trueCount = c_trueCount;
            e_trueCount = c_trueCount;
            f_trueCount = c_trueCount;
        }
        t12_size = c_trueCount;
        if (c_trueCount == 1) {
            g_trueCount = c_trueCount;
        } else {
            g_trueCount = c_trueCount;
        }
        h_trueCount = c_trueCount;
        i_trueCount = c_trueCount;
        if ((c_trueCount == d_trueCount) && (e_trueCount == f_trueCount) &&
            (c_trueCount == t12_size) && (c_trueCount == g_trueCount) &&
            (h_trueCount == i_trueCount)) {
            alpha0_t_size = c_trueCount;
            for (int i27{0}; i27 < c_trueCount; i27++) {
                double d182;
                double d183;
                double d184;
                double d185;
                double d186;
                d182 = alpha1_t_data[i27];
                d183 = t5_data[i27];
                d184 = t11_data[i27];
                d185 = t12_data[i27];
                d186 = t10_data[i27];
                alpha0_t_data[i27] = -((((CoefPS[15] + d182 * CoefPS[11]) + CoefPS[9] * d183) -
                                        CoefPS[13] * d184 * d185) +
                                       CoefPS[12] * d186 * b_tmp_data[i27] * d185) /
                                     ((((CoefPS[14] + d182 * CoefPS[10]) + CoefPS[8] * d183) -
                                       CoefPS[13] * d186 * d184) -
                                      CoefPS[12] * d184 * (d185 - c_tmp_data[i27] * d184));
            }
        } else {
            binary_expand_op(alpha0_t_data, &alpha0_t_size, CoefPS, alpha1_t_data, &c_trueCount,
                             t5_data, &c_trueCount, t11_data, &c_trueCount, t12_data, &c_trueCount,
                             t10_data, &c_trueCount, b_tmp_data, &c_trueCount, c_tmp_data,
                             &c_trueCount);
        }
        //
        // 'G2_Hermite_Interpolation:208' Idx       = find(alpha0_t > 0);
        for (int i28{0}; i28 < alpha0_t_size; i28++) {
            c_alpha0_t_data[i28] = (alpha0_t_data[i28] > 0.0);
        }
        coder::c_eml_find(c_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
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
                    int i29;
                    // 'G2_Hermite_Interpolation:227' [beta0_u(k), beta1_u(k)] =
                    // Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ... 'G2_Hermite_Interpolation:228'
                    // r0D0, t0, n0, kappa0, ... 'G2_Hermite_Interpolation:229' r1D0, t1, n1,
                    // kappa1);
                    i29 = Idx_data[d_k];
                    Calc_beta0_beta1(alpha0_t_data[i29 - 1], alpha1_t_data[i29 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[d_k],
                                     &beta1_u_data[d_k]);
                    // 'G2_Hermite_Interpolation:230' CostInt(k)     = EvalCostIntegral(alpha0_u(k),
                    // beta0_u(k), alpha1_u(k), beta1_u(k), ... 'G2_Hermite_Interpolation:231' r0D0,
                    // t0, n0, kappa0, ... 'G2_Hermite_Interpolation:232' r1D0, t1, n1, kappa1);
                    CostInt_data[d_k] = EvalCostIntegral(
                        alpha0_t_data[i29 - 1], beta0_u_data[d_k], alpha1_t_data[i29 - 1],
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
        double a_idx_0;
        double a_idx_1;
        double a_idx_2;
        double a_tmp;
        double b_a_tmp;
        double c_a;
        double d;
        double d1;
        double d10;
        double d12;
        double d13;
        double d14;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d8;
        double d_a;
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
        a_idx_0 = a * t0[0] + c_a * n0[0];
        a_idx_1 = a * t0[1] + c_a * n0[1];
        a_idx_2 = a * t0[2] + c_a * n0[2];
        d = r0D0[0];
        d1 = r0D0[1];
        d2 = r0D0[2];
        d3 = t0[0];
        d4 = t0[1];
        d5 = t0[2];
        d6 = r1D0[0];
        d8 = r1D0[1];
        d10 = r1D0[2];
        for (int i15{0}; i15 < 6; i15++) {
            double d11;
            int alpha0_tmp;
            int r0D0_tmp;
            int r1D0_tmp;
            r0D0_tmp = b[i15];
            alpha0_tmp = b_b[i15];
            d11 = c_b[i15];
            b_r0D0[i15][0] = (d * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d3 * static_cast<double>(alpha0_tmp)) +
                             a_idx_0 * d11;
            r1D0_tmp = d_b[i15];
            b_r1D0[i15][0] = d6 * static_cast<double>(r1D0_tmp);
            b_r0D0[i15][1] = (d1 * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d4 * static_cast<double>(alpha0_tmp)) +
                             a_idx_1 * d11;
            b_r1D0[i15][1] = d8 * static_cast<double>(r1D0_tmp);
            b_r0D0[i15][2] = (d2 * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d5 * static_cast<double>(alpha0_tmp)) +
                             a_idx_2 * d11;
            b_r1D0[i15][2] = d10 * static_cast<double>(r1D0_tmp);
        }
        a_idx_0 = b_a * t1[0] + d_a * n1[0];
        a_idx_1 = b_a * t1[1] + d_a * n1[1];
        a_idx_2 = b_a * t1[2] + d_a * n1[2];
        d12 = t1[0];
        d13 = t1[1];
        d14 = t1[2];
        for (int i16{0}; i16 < 6; i16++) {
            double d15;
            int p5_3D_tmp;
            p5_3D_tmp = e_b[i16];
            d15 = f_b[i16];
            p5_3D[i16][0] = ((b_r0D0[i16][0] + b_r1D0[i16][0]) +
                             *alpha1 * d12 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_0 * d15;
            p5_3D[i16][1] = ((b_r0D0[i16][1] + b_r1D0[i16][1]) +
                             *alpha1 * d13 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_1 * d15;
            p5_3D[i16][2] = ((b_r0D0[i16][2] + b_r1D0[i16][2]) +
                             *alpha1 * d14 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_2 * d15;
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
