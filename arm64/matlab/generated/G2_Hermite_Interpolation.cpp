//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "G2_Hermite_Interpolation.h"
#include "CalcAlpha0.h"
#include "CalcFrenet.h"
#include "Calc_beta0_beta1.h"
#include "CharPolyAlpha1.h"
#include "CoefPolySys.h"
#include "EvalCostIntegral.h"
#include "c_roots_.h"
#include "find.h"
#include "minOrMax.h"
#include <cmath>
#include <cstring>

// Function Definitions
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
    static const double d_b[6]{-0.5, 1.5, -1.5, 0.5, 0.0, 0.0};
    static const double g_b[6]{0.5, -1.0, 0.5, 0.0, 0.0, 0.0};
    static const signed char b_b[6]{-6, 15, -10, 0, 0, 1};
    static const signed char c_b[6]{-3, 8, -6, 0, 1, 0};
    static const signed char e_b[6]{6, -15, 10, 0, 0, 0};
    static const signed char f_b[6]{-3, 7, -4, 0, 0, 0};
    creal_T alpha1_v[9];
    creal_T alpha0_v[3];
    creal_T b_alpha1_v[3];
    double b_r0D0[6][3];
    double b_r1D0[6][3];
    double CoefPS[16];
    double dv[10];
    double CostInt_data[9];
    double alpha0_t_data[9];
    double alpha1_t_data[9];
    double b_z1_data[9];
    double beta0_u_data[9];
    double beta1_u_data[9];
    double z1_data[9];
    double A[2][2];
    double b_CoefPS[4];
    double n0[3];
    double n1[3];
    double t0[3];
    double t1[3];
    double B[2];
    double a;
    double a__1;
    double a__2;
    double a__3;
    double b_a;
    double kappa0;
    double kappa1;
    int Idx_data[9];
    int Idx_size;
    int alpha0_t_size;
    int b_iindx;
    int c_iindx;
    int iindx;
    signed char tmp_data[3];
    bool b_alpha0_t_data[9];
    bool b_alpha1_t_data[3];
    bool c_alpha0_t_data[3];
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
    //
    //  [p5_3D, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2)
    //
    //  Compute an optimal trajectory in R^3, connecting the point r0 to r1 with
    //  C^2 smoothness while minimizing the integral of the norm of the third
    //  derivative.
    *status = 1;
    //  default success
    for (int i{0}; i < 6; i++) {
        p5_3D[i][0] = 0.0;
        p5_3D[i][1] = 0.0;
        p5_3D[i][2] = 0.0;
    }
    *alpha0 = 0.0;
    *alpha1 = 0.0;
    //  compute Frenet frame
    CalcFrenet(r0D1, r0D2, t0, n0, &kappa0);
    CalcFrenet(r1D1, r1D2, t1, n1, &kappa1);
    //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
    //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
    //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
    //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
    //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
    //
    //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
    CoefPolySys(r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, CoefPS);
    //
    //
    guard1 = false;
    if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
        double X_idx_0;
        double X_idx_1;
        double a21;
        int r1;
        int r2;
        //  degenerated case where the polynomial system degenerates to a linear one
        //
        //
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
        *alpha0 = X_idx_0;
        *alpha1 = X_idx_1;
        if ((X_idx_0 > 0.0) && (X_idx_1 > 0.0)) {
            Calc_beta0_beta1(X_idx_0, X_idx_1, r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a,
                             &b_a);
            guard1 = true;
        }
    } else if (kappa0 == 0.0) {
        int b_partialTrueCount;
        int b_trueCount;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        bool unnamed_idx_2;
        //  compute resultant of the polynomial system
        //
        b_CoefPS[0] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
        b_CoefPS[1] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
        b_CoefPS[2] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
        b_CoefPS[3] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
        b_c_roots_(b_CoefPS, b_alpha1_v);
        //  all roots of 3th degree polynomial in alpha1
        b_trueCount = 0;
        unnamed_idx_2 = (std::abs(b_alpha1_v[0].im) < 1.0E-11);
        unnamed_idx_0 = unnamed_idx_2;
        if (unnamed_idx_2 && (b_alpha1_v[0].re > 0.0)) {
            b_trueCount = 1;
        }
        unnamed_idx_2 = (std::abs(b_alpha1_v[1].im) < 1.0E-11);
        unnamed_idx_1 = unnamed_idx_2;
        if (unnamed_idx_2 && (b_alpha1_v[1].re > 0.0)) {
            b_trueCount++;
        }
        unnamed_idx_2 = (std::abs(b_alpha1_v[2].im) < 1.0E-11);
        if (unnamed_idx_2 && (b_alpha1_v[2].re > 0.0)) {
            b_trueCount++;
        }
        b_partialTrueCount = 0;
        if (unnamed_idx_0 && (b_alpha1_v[0].re > 0.0)) {
            tmp_data[0] = 1;
            b_partialTrueCount = 1;
        }
        if (unnamed_idx_1 && (b_alpha1_v[1].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 2;
            b_partialTrueCount++;
        }
        if (unnamed_idx_2 && (b_alpha1_v[2].re > 0.0)) {
            tmp_data[b_partialTrueCount] = 3;
        }
        for (int i2{0}; i2 < b_trueCount; i2++) {
            alpha1_t_data[i2] = b_alpha1_v[tmp_data[i2] - 1].re;
        }
        //  retain only positive real roots
        if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
            for (int d_k{0}; d_k < b_trueCount; d_k++) {
                z1_data[d_k] = std::pow(alpha1_t_data[d_k], 2.0);
            }
            alpha0_t_size = b_trueCount;
            for (int i5{0}; i5 < b_trueCount; i5++) {
                alpha0_t_data[i5] =
                    -((CoefPS[9] * z1_data[i5] + CoefPS[11] * alpha1_t_data[i5]) + CoefPS[15]) /
                    CoefPS[14];
            }
        } else {
            for (int c_k{0}; c_k < b_trueCount; c_k++) {
                z1_data[c_k] = std::pow(alpha1_t_data[c_k], 3.0);
            }
            for (int g_k{0}; g_k < b_trueCount; g_k++) {
                b_z1_data[g_k] = std::pow(alpha1_t_data[g_k], 2.0);
            }
            alpha0_t_size = b_trueCount;
            for (int i7{0}; i7 < b_trueCount; i7++) {
                double d7;
                d7 = alpha1_t_data[i7];
                alpha0_t_data[i7] =
                    -(((CoefPS[4] * z1_data[i7] + CoefPS[5] * b_z1_data[i7]) + CoefPS[6] * d7) +
                      CoefPS[7]) /
                    (CoefPS[2] * d7 + CoefPS[3]);
            }
        }
        for (int i9{0}; i9 < alpha0_t_size; i9++) {
            c_alpha0_t_data[i9] = (alpha0_t_data[i9] > 0.0);
        }
        coder::c_eml_find(c_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        if (Idx_size <= 0) {
            *status = 3;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            if (Idx_size > 1) {
                int b_CostInt_size_tmp;
                b_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= b_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, b_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                for (int i_k{0}; i_k < Idx_size; i_k++) {
                    int i13;
                    i13 = Idx_data[i_k];
                    Calc_beta0_beta1(alpha0_t_data[i13 - 1], alpha1_t_data[i13 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[i_k],
                                     &beta1_u_data[i_k]);
                    CostInt_data[i_k] = EvalCostIntegral(
                        alpha0_t_data[i13 - 1], beta0_u_data[i_k], alpha1_t_data[i13 - 1],
                        beta1_u_data[i_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int c_alpha0_tmp;
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &a__1, &b_iindx);
                c_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[c_alpha0_tmp];
                *alpha1 = alpha1_t_data[c_alpha0_tmp];
                a = beta0_u_data[b_iindx - 1];
                b_a = beta1_u_data[b_iindx - 1];
            } else {
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else if (kappa1 == 0.0) {
        int alpha1_t_size;
        int c_partialTrueCount;
        int c_trueCount;
        bool b_unnamed_idx_2;
        bool unnamed_idx_0;
        bool unnamed_idx_1;
        //  compute resultant of the polynomial system
        //
        b_CoefPS[0] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
        b_CoefPS[1] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
        b_CoefPS[2] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
        b_CoefPS[3] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
        b_c_roots_(b_CoefPS, alpha0_v);
        //  all roots of 3th degree polynomial in alpha0
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
        for (int i3{0}; i3 < c_trueCount; i3++) {
            alpha0_t_data[i3] = alpha0_v[tmp_data[i3] - 1].re;
        }
        //  retain only positive real roots
        if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
            for (int f_k{0}; f_k < c_trueCount; f_k++) {
                z1_data[f_k] = std::pow(alpha0_t_data[f_k], 2.0);
            }
            alpha1_t_size = c_trueCount;
            for (int i6{0}; i6 < c_trueCount; i6++) {
                alpha1_t_data[i6] =
                    -((CoefPS[1] * z1_data[i6] + CoefPS[3] * alpha0_t_data[i6]) + CoefPS[7]) /
                    CoefPS[6];
            }
        } else {
            for (int e_k{0}; e_k < c_trueCount; e_k++) {
                z1_data[e_k] = std::pow(alpha0_t_data[e_k], 3.0);
            }
            for (int h_k{0}; h_k < c_trueCount; h_k++) {
                b_z1_data[h_k] = std::pow(alpha0_t_data[h_k], 2.0);
            }
            alpha1_t_size = c_trueCount;
            for (int i8{0}; i8 < c_trueCount; i8++) {
                double d9;
                d9 = alpha0_t_data[i8];
                alpha1_t_data[i8] =
                    -(((CoefPS[12] * z1_data[i8] + CoefPS[13] * b_z1_data[i8]) + CoefPS[14] * d9) +
                      CoefPS[15]) /
                    (CoefPS[10] * d9 + CoefPS[11]);
            }
        }
        for (int i10{0}; i10 < alpha1_t_size; i10++) {
            b_alpha1_t_data[i10] = (alpha1_t_data[i10] > 0.0);
        }
        coder::c_eml_find(b_alpha1_t_data, alpha1_t_size, Idx_data, &Idx_size);
        //
        if (Idx_size <= 0) {
            *status = 4;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            if (Idx_size > 1) {
                int c_CostInt_size_tmp;
                c_CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= c_CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, c_CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                for (int j_k{0}; j_k < Idx_size; j_k++) {
                    int i14;
                    i14 = Idx_data[j_k];
                    Calc_beta0_beta1(alpha0_t_data[i14 - 1], alpha1_t_data[i14 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[j_k],
                                     &beta1_u_data[j_k]);
                    CostInt_data[j_k] = EvalCostIntegral(
                        alpha0_t_data[i14 - 1], beta0_u_data[j_k], alpha1_t_data[i14 - 1],
                        beta1_u_data[j_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int d_alpha0_tmp;
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &a__2, &c_iindx);
                d_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[d_alpha0_tmp];
                *alpha1 = alpha1_t_data[d_alpha0_tmp];
                a = beta0_u_data[c_iindx - 1];
                b_a = beta1_u_data[c_iindx - 1];
            } else {
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                 r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
            }
            //
            guard1 = true;
        }
    } else {
        int partialTrueCount;
        int trueCount;
        //  compute resultant of the polynomial system
        //
        CharPolyAlpha1(CoefPS, dv);
        c_c_roots_(dv, alpha1_v);
        //  all roots of 9th degree polynomial in alpha1
        trueCount = 0;
        partialTrueCount = 0;
        for (int k{0}; k < 9; k++) {
            double d;
            bool b;
            b = (std::abs(alpha1_v[k].im) < 1.0E-11);
            d = alpha1_v[k].re;
            if (b && (d > 0.0)) {
                trueCount++;
                alpha1_t_data[partialTrueCount] = d;
                partialTrueCount++;
            }
        }
        //  retain only positive real roots
        //  compute corresponding values of alpha0
        CalcAlpha0(alpha1_t_data, trueCount, CoefPS, alpha0_t_data, &alpha0_t_size);
        //
        for (int i1{0}; i1 < alpha0_t_size; i1++) {
            b_alpha0_t_data[i1] = (alpha0_t_data[i1] > 0.0);
        }
        coder::c_eml_find(b_alpha0_t_data, alpha0_t_size, Idx_data, &Idx_size);
        //
        if (Idx_size <= 0) {
            *status = 5;
        } else {
            // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
            if (Idx_size > 1) {
                int CostInt_size_tmp;
                CostInt_size_tmp = static_cast<signed char>(Idx_size);
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&CostInt_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta0_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                if (0 <= CostInt_size_tmp - 1) {
                    std::memset(&beta1_u_data[0], 0, CostInt_size_tmp * sizeof(double));
                }
                //  preallocating
                for (int b_k{0}; b_k < Idx_size; b_k++) {
                    int i4;
                    i4 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i4 - 1], alpha1_t_data[i4 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[i4 - 1], beta0_u_data[b_k], alpha1_t_data[i4 - 1],
                        beta1_u_data[b_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int alpha0_tmp;
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &a__3, &iindx);
                alpha0_tmp = Idx_data[iindx - 1] - 1;
                *alpha0 = alpha0_t_data[alpha0_tmp];
                *alpha1 = alpha1_t_data[alpha0_tmp];
                a = beta0_u_data[iindx - 1];
                b_a = beta1_u_data[iindx - 1];
            } else {
                *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                *alpha1 = alpha1_t_data[Idx_data[0] - 1];
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
        double d1;
        double d10;
        double d11;
        double d13;
        double d14;
        double d15;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d8;
        double d_a;
        //
        //  Hermite basis
        //  evaluate coefficients as sum of basis functions
        a_tmp = std::pow(*alpha0, 2.0);
        c_a = kappa0 * a_tmp;
        b_a_tmp = std::pow(*alpha1, 2.0);
        d_a = kappa1 * b_a_tmp;
        a_idx_0 = a * t0[0] + c_a * n0[0];
        a_idx_1 = a * t0[1] + c_a * n0[1];
        a_idx_2 = a * t0[2] + c_a * n0[2];
        d1 = r0D0[0];
        d2 = r0D0[1];
        d3 = r0D0[2];
        d4 = t0[0];
        d5 = t0[1];
        d6 = t0[2];
        d8 = r1D0[0];
        d10 = r1D0[1];
        d11 = r1D0[2];
        for (int i11{0}; i11 < 6; i11++) {
            double d12;
            int b_alpha0_tmp;
            int r0D0_tmp;
            int r1D0_tmp;
            r0D0_tmp = b_b[i11];
            b_alpha0_tmp = c_b[i11];
            d12 = d_b[i11];
            b_r0D0[i11][0] = (d1 * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d4 * static_cast<double>(b_alpha0_tmp)) +
                             a_idx_0 * d12;
            r1D0_tmp = e_b[i11];
            b_r1D0[i11][0] = d8 * static_cast<double>(r1D0_tmp);
            b_r0D0[i11][1] = (d2 * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d5 * static_cast<double>(b_alpha0_tmp)) +
                             a_idx_1 * d12;
            b_r1D0[i11][1] = d10 * static_cast<double>(r1D0_tmp);
            b_r0D0[i11][2] = (d3 * static_cast<double>(r0D0_tmp) +
                              *alpha0 * d6 * static_cast<double>(b_alpha0_tmp)) +
                             a_idx_2 * d12;
            b_r1D0[i11][2] = d11 * static_cast<double>(r1D0_tmp);
        }
        a_idx_0 = b_a * t1[0] + d_a * n1[0];
        a_idx_1 = b_a * t1[1] + d_a * n1[1];
        a_idx_2 = b_a * t1[2] + d_a * n1[2];
        d13 = t1[0];
        d14 = t1[1];
        d15 = t1[2];
        for (int i12{0}; i12 < 6; i12++) {
            double d16;
            int p5_3D_tmp;
            p5_3D_tmp = f_b[i12];
            d16 = g_b[i12];
            p5_3D[i12][0] = ((b_r0D0[i12][0] + b_r1D0[i12][0]) +
                             *alpha1 * d13 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_0 * d16;
            p5_3D[i12][1] = ((b_r0D0[i12][1] + b_r1D0[i12][1]) +
                             *alpha1 * d14 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_1 * d16;
            p5_3D[i12][2] = ((b_r0D0[i12][2] + b_r1D0[i12][2]) +
                             *alpha1 * d15 * static_cast<double>(p5_3D_tmp)) +
                            a_idx_2 * d16;
        }
        //  last cross check ...
        //
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
