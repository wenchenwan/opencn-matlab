//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
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
#include <emmintrin.h>

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
    double b_alpha0[6][3];
    double b_r0D0[6][3];
    double b_r1D0[6][3];
    double c_r0D0[6][3];
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
    double e_a[3];
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
            double c_CoefPS;
            double e_CoefPS;
            double h_CoefPS;
            double l_CoefPS;
            int i9;
            int scalarLB;
            int vectorUB;
            for (int d_k{0}; d_k < b_trueCount; d_k++) {
                z1_data[d_k] = std::pow(alpha1_t_data[d_k], 2.0);
            }
            c_CoefPS = CoefPS[9];
            e_CoefPS = CoefPS[11];
            h_CoefPS = CoefPS[15];
            l_CoefPS = CoefPS[14];
            alpha0_t_size = b_trueCount;
            scalarLB = (b_trueCount / 2) << 1;
            vectorUB = scalarLB - 2;
            for (i9 = 0; i9 <= vectorUB; i9 += 2) {
                __m128d r10;
                __m128d r8;
                r8 = _mm_loadu_pd(&z1_data[i9]);
                r10 = _mm_loadu_pd(&alpha1_t_data[i9]);
                _mm_storeu_pd(
                    &alpha0_t_data[i9],
                    _mm_div_pd(
                        _mm_mul_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(c_CoefPS), r8),
                                                         _mm_mul_pd(_mm_set1_pd(e_CoefPS), r10)),
                                              _mm_set1_pd(h_CoefPS)),
                                   _mm_set1_pd(-1.0)),
                        _mm_set1_pd(l_CoefPS)));
            }
            for (i9 = scalarLB; i9 < b_trueCount; i9++) {
                alpha0_t_data[i9] =
                    -((c_CoefPS * z1_data[i9] + e_CoefPS * alpha1_t_data[i9]) + h_CoefPS) /
                    l_CoefPS;
            }
        } else {
            double g_CoefPS;
            double k_CoefPS;
            double o_CoefPS;
            double q_CoefPS;
            double s_CoefPS;
            double u_CoefPS;
            int c_scalarLB;
            int c_vectorUB;
            int i12;
            for (int c_k{0}; c_k < b_trueCount; c_k++) {
                z1_data[c_k] = std::pow(alpha1_t_data[c_k], 3.0);
            }
            for (int g_k{0}; g_k < b_trueCount; g_k++) {
                b_z1_data[g_k] = std::pow(alpha1_t_data[g_k], 2.0);
            }
            g_CoefPS = CoefPS[4];
            k_CoefPS = CoefPS[5];
            o_CoefPS = CoefPS[6];
            q_CoefPS = CoefPS[7];
            s_CoefPS = CoefPS[2];
            u_CoefPS = CoefPS[3];
            alpha0_t_size = b_trueCount;
            c_scalarLB = (b_trueCount / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (i12 = 0; i12 <= c_vectorUB; i12 += 2) {
                __m128d r14;
                __m128d r16;
                __m128d r19;
                r14 = _mm_loadu_pd(&z1_data[i12]);
                r16 = _mm_loadu_pd(&b_z1_data[i12]);
                r19 = _mm_loadu_pd(&alpha1_t_data[i12]);
                _mm_storeu_pd(
                    &alpha0_t_data[i12],
                    _mm_div_pd(
                        _mm_mul_pd(
                            _mm_add_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(g_CoefPS), r14),
                                                      _mm_mul_pd(_mm_set1_pd(k_CoefPS), r16)),
                                           _mm_mul_pd(_mm_set1_pd(o_CoefPS), r19)),
                                _mm_set1_pd(q_CoefPS)),
                            _mm_set1_pd(-1.0)),
                        _mm_add_pd(_mm_mul_pd(_mm_set1_pd(s_CoefPS), r19), _mm_set1_pd(u_CoefPS))));
            }
            for (i12 = c_scalarLB; i12 < b_trueCount; i12++) {
                double d2;
                d2 = alpha1_t_data[i12];
                alpha0_t_data[i12] =
                    -(((g_CoefPS * z1_data[i12] + k_CoefPS * b_z1_data[i12]) + o_CoefPS * d2) +
                      q_CoefPS) /
                    (s_CoefPS * d2 + u_CoefPS);
            }
        }
        for (int i14{0}; i14 < alpha0_t_size; i14++) {
            c_alpha0_t_data[i14] = (alpha0_t_data[i14] > 0.0);
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
                    int i18;
                    i18 = Idx_data[i_k];
                    Calc_beta0_beta1(alpha0_t_data[i18 - 1], alpha1_t_data[i18 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[i_k],
                                     &beta1_u_data[i_k]);
                    CostInt_data[i_k] = EvalCostIntegral(
                        alpha0_t_data[i18 - 1], beta0_u_data[i_k], alpha1_t_data[i18 - 1],
                        beta1_u_data[i_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int b_alpha0_tmp;
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &a__1, &b_iindx);
                b_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[b_alpha0_tmp];
                *alpha1 = alpha1_t_data[b_alpha0_tmp];
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
            double d_CoefPS;
            double f_CoefPS;
            double j_CoefPS;
            double n_CoefPS;
            int b_scalarLB;
            int b_vectorUB;
            int i10;
            for (int f_k{0}; f_k < c_trueCount; f_k++) {
                z1_data[f_k] = std::pow(alpha0_t_data[f_k], 2.0);
            }
            d_CoefPS = CoefPS[1];
            f_CoefPS = CoefPS[3];
            j_CoefPS = CoefPS[7];
            n_CoefPS = CoefPS[6];
            alpha1_t_size = c_trueCount;
            b_scalarLB = (c_trueCount / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (i10 = 0; i10 <= b_vectorUB; i10 += 2) {
                __m128d r12;
                __m128d r9;
                r9 = _mm_loadu_pd(&z1_data[i10]);
                r12 = _mm_loadu_pd(&alpha0_t_data[i10]);
                _mm_storeu_pd(
                    &alpha1_t_data[i10],
                    _mm_div_pd(
                        _mm_mul_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(d_CoefPS), r9),
                                                         _mm_mul_pd(_mm_set1_pd(f_CoefPS), r12)),
                                              _mm_set1_pd(j_CoefPS)),
                                   _mm_set1_pd(-1.0)),
                        _mm_set1_pd(n_CoefPS)));
            }
            for (i10 = b_scalarLB; i10 < c_trueCount; i10++) {
                alpha1_t_data[i10] =
                    -((d_CoefPS * z1_data[i10] + f_CoefPS * alpha0_t_data[i10]) + j_CoefPS) /
                    n_CoefPS;
            }
        } else {
            double i_CoefPS;
            double m_CoefPS;
            double p_CoefPS;
            double r_CoefPS;
            double t_CoefPS;
            double v_CoefPS;
            int d_scalarLB;
            int d_vectorUB;
            int i13;
            for (int e_k{0}; e_k < c_trueCount; e_k++) {
                z1_data[e_k] = std::pow(alpha0_t_data[e_k], 3.0);
            }
            for (int h_k{0}; h_k < c_trueCount; h_k++) {
                b_z1_data[h_k] = std::pow(alpha0_t_data[h_k], 2.0);
            }
            i_CoefPS = CoefPS[12];
            m_CoefPS = CoefPS[13];
            p_CoefPS = CoefPS[14];
            r_CoefPS = CoefPS[15];
            t_CoefPS = CoefPS[10];
            v_CoefPS = CoefPS[11];
            alpha1_t_size = c_trueCount;
            d_scalarLB = (c_trueCount / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (i13 = 0; i13 <= d_vectorUB; i13 += 2) {
                __m128d r15;
                __m128d r18;
                __m128d r21;
                r15 = _mm_loadu_pd(&z1_data[i13]);
                r18 = _mm_loadu_pd(&b_z1_data[i13]);
                r21 = _mm_loadu_pd(&alpha0_t_data[i13]);
                _mm_storeu_pd(
                    &alpha1_t_data[i13],
                    _mm_div_pd(
                        _mm_mul_pd(
                            _mm_add_pd(
                                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(i_CoefPS), r15),
                                                      _mm_mul_pd(_mm_set1_pd(m_CoefPS), r18)),
                                           _mm_mul_pd(_mm_set1_pd(p_CoefPS), r21)),
                                _mm_set1_pd(r_CoefPS)),
                            _mm_set1_pd(-1.0)),
                        _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t_CoefPS), r21), _mm_set1_pd(v_CoefPS))));
            }
            for (i13 = d_scalarLB; i13 < c_trueCount; i13++) {
                double d3;
                d3 = alpha0_t_data[i13];
                alpha1_t_data[i13] =
                    -(((i_CoefPS * z1_data[i13] + m_CoefPS * b_z1_data[i13]) + p_CoefPS * d3) +
                      r_CoefPS) /
                    (t_CoefPS * d3 + v_CoefPS);
            }
        }
        for (int i16{0}; i16 < alpha1_t_size; i16++) {
            b_alpha1_t_data[i16] = (alpha1_t_data[i16] > 0.0);
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
                    int i19;
                    i19 = Idx_data[j_k];
                    Calc_beta0_beta1(alpha0_t_data[i19 - 1], alpha1_t_data[i19 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[j_k],
                                     &beta1_u_data[j_k]);
                    CostInt_data[j_k] = EvalCostIntegral(
                        alpha0_t_data[i19 - 1], beta0_u_data[j_k], alpha1_t_data[i19 - 1],
                        beta1_u_data[j_k], r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                }
                int c_alpha0_tmp;
                coder::internal::minimum(CostInt_data,
                                         static_cast<int>(static_cast<signed char>(Idx_size)),
                                         &a__2, &c_iindx);
                c_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                *alpha0 = alpha0_t_data[c_alpha0_tmp];
                *alpha1 = alpha1_t_data[c_alpha0_tmp];
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
                    int i6;
                    i6 = Idx_data[b_k];
                    Calc_beta0_beta1(alpha0_t_data[i6 - 1], alpha1_t_data[i6 - 1], r0D0, t0, n0,
                                     kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[b_k],
                                     &beta1_u_data[b_k]);
                    CostInt_data[b_k] = EvalCostIntegral(
                        alpha0_t_data[i6 - 1], beta0_u_data[b_k], alpha1_t_data[i6 - 1],
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
        __m128d r;
        __m128d r11;
        __m128d r13;
        __m128d r3;
        double a_tmp;
        double b_a_tmp;
        double c_a;
        double d_a;
        //
        //  Hermite basis
        //  evaluate coefficients as sum of basis functions
        a_tmp = std::pow(*alpha0, 2.0);
        c_a = kappa0 * a_tmp;
        b_a_tmp = std::pow(*alpha1, 2.0);
        d_a = kappa1 * b_a_tmp;
        r = _mm_loadu_pd(&t0[0]);
        for (int i4{0}; i4 < 6; i4++) {
            int i5;
            int i7;
            i5 = b_b[i4];
            _mm_storeu_pd(&b_r0D0[i4][0], _mm_mul_pd(_mm_loadu_pd((double *)&r0D0[0]),
                                                     _mm_set1_pd(static_cast<double>(i5))));
            i7 = c_b[i4];
            _mm_storeu_pd(&b_alpha0[i4][0], _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(*alpha0), r),
                                                       _mm_set1_pd(static_cast<double>(i7))));
            b_r0D0[i4][2] = r0D0[2] * static_cast<double>(i5);
            b_alpha0[i4][2] = *alpha0 * t0[2] * static_cast<double>(i7);
        }
        __m128d b_r1;
        __m128d b_r2;
        b_r1 = _mm_loadu_pd(&t0[0]);
        b_r2 = _mm_loadu_pd(&n0[0]);
        _mm_storeu_pd(&e_a[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(a), b_r1),
                                          _mm_mul_pd(_mm_set1_pd(c_a), b_r2)));
        e_a[2] = a * t0[2] + c_a * n0[2];
        r3 = _mm_loadu_pd(&e_a[0]);
        for (int i8{0}; i8 < 6; i8++) {
            __m128d r5;
            __m128d r7;
            double d1;
            int i11;
            r5 = _mm_loadu_pd(&b_r0D0[i8][0]);
            r7 = _mm_loadu_pd(&b_alpha0[i8][0]);
            d1 = d_b[i8];
            _mm_storeu_pd(&c_r0D0[i8][0], _mm_add_pd(_mm_add_pd(r5, r7),
                                                     _mm_add_pd(_mm_set1_pd(0.0),
                                                                _mm_mul_pd(r3, _mm_set1_pd(d1)))));
            i11 = e_b[i8];
            _mm_storeu_pd(&b_r1D0[i8][0], _mm_mul_pd(_mm_loadu_pd((double *)&r1D0[0]),
                                                     _mm_set1_pd(static_cast<double>(i11))));
            c_r0D0[i8][2] = (b_r0D0[i8][2] + b_alpha0[i8][2]) + e_a[2] * d1;
            b_r1D0[i8][2] = r1D0[2] * static_cast<double>(i11);
        }
        __m128d r4;
        __m128d r6;
        r4 = _mm_loadu_pd(&t1[0]);
        r6 = _mm_loadu_pd(&n1[0]);
        _mm_storeu_pd(&e_a[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(b_a), r4),
                                          _mm_mul_pd(_mm_set1_pd(d_a), r6)));
        e_a[2] = b_a * t1[2] + d_a * n1[2];
        r11 = _mm_loadu_pd(&t1[0]);
        r13 = _mm_loadu_pd(&e_a[0]);
        for (int i15{0}; i15 < 6; i15++) {
            __m128d r17;
            __m128d r20;
            double d4;
            int i17;
            r17 = _mm_loadu_pd(&c_r0D0[i15][0]);
            r20 = _mm_loadu_pd(&b_r1D0[i15][0]);
            i17 = f_b[i15];
            d4 = g_b[i15];
            _mm_storeu_pd(
                &p5_3D[i15][0],
                _mm_add_pd(
                    _mm_add_pd(_mm_add_pd(r17, r20),
                               _mm_add_pd(_mm_set1_pd(0.0),
                                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(*alpha1), r11),
                                                     _mm_set1_pd(static_cast<double>(i17))))),
                    _mm_mul_pd(r13, _mm_set1_pd(d4))));
            p5_3D[i15][2] =
                ((c_r0D0[i15][2] + b_r1D0[i15][2]) + *alpha1 * t1[2] * static_cast<double>(i17)) +
                e_a[2] * d4;
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
