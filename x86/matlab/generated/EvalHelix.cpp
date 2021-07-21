//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "EvalHelix.h"
#include "c_assert.h"
#include "sinspace_data.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double u_vec[10]
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
namespace ocn {
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch, const double u_vec[10],
               double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
{
    __m128d r;
    double cphiTCP0[10][3];
    double cphiTEcrCP0[10][3];
    double sphiTCP0[10][3];
    double sphiTEcrCP0[10][3];
    double CP0[3];
    double EcrCP0[3];
    double P0P1[3];
    double y[3];
    ZoneScopedN("EvalHelix");
    //
    //
    r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
    _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
    P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
    for (int i{0}; i < 10; i++) {
        r0D[i][0] = 0.0;
        r1D[i][0] = 0.0;
        r2D[i][0] = 0.0;
        r3D[i][0] = 0.0;
        r0D[i][1] = 0.0;
        r1D[i][1] = 0.0;
        r2D[i][1] = 0.0;
        r3D[i][1] = 0.0;
        r0D[i][2] = 0.0;
        r1D[i][2] = 0.0;
        r2D[i][2] = 0.0;
        r3D[i][2] = 0.0;
    }
    sqrt_calls++;
    if (c_assert(
            std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - P0P1[1] * CurvStruct_evec[2], 2.0) +
                       std::pow(P0P1[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - P0P1[0] * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r6;
        __m128d r7;
        double a;
        double a_tmp;
        double b_a_tmp;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        r1 = _mm_loadu_pd((double *)&CurvStruct_CorrectedHelixCenter[0]);
        _mm_storeu_pd(&CP0[0], _mm_sub_pd(r, r1));
        CP0[2] = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
        EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
        EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
        cos_calls++;
        sin_calls++;
        //
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        r2 = _mm_loadu_pd(&CP0[0]);
        r3 = _mm_loadu_pd(&EcrCP0[0]);
        for (int k{0}; k < 10; k++) {
            __m128d r10;
            __m128d r4;
            __m128d r5;
            __m128d r8;
            double d;
            double d1;
            double d2;
            double d3;
            double d5;
            d = CurvStruct_theta * u_vec[k];
            d1 = std::cos(d);
            d2 = std::sin(d);
            r4 = _mm_set1_pd(d1);
            r5 = _mm_mul_pd(r2, r4);
            _mm_storeu_pd(&cphiTCP0[k][0], r5);
            r8 = _mm_set1_pd(d2);
            _mm_storeu_pd(&sphiTCP0[k][0], _mm_mul_pd(r2, r8));
            _mm_storeu_pd(&cphiTEcrCP0[k][0], _mm_mul_pd(r3, r4));
            r10 = _mm_mul_pd(r3, r8);
            _mm_storeu_pd(&sphiTEcrCP0[k][0], r10);
            _mm_storeu_pd(
                &r0D[k][0],
                _mm_add_pd(
                    r1, _mm_add_pd(
                            _mm_add_pd(r5, r10),
                            _mm_add_pd(
                                _mm_set1_pd(0.0),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                                      _mm_loadu_pd((double *)&CurvStruct_evec[0])),
                                           _mm_set1_pd(d))))));
            d3 = CP0[2] * d1;
            cphiTCP0[k][2] = d3;
            sphiTCP0[k][2] = CP0[2] * d2;
            cphiTEcrCP0[k][2] = EcrCP0[2] * d1;
            d5 = EcrCP0[2] * d2;
            sphiTEcrCP0[k][2] = d5;
            r0D[k][2] =
                CurvStruct_CorrectedHelixCenter[2] + ((d3 + d5) + a * CurvStruct_evec[2] * d);
        }
        double b_a;
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        _mm_storeu_pd(&y[0],
                      _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((double *)&CurvStruct_evec[0])));
        y[2] = b_a * CurvStruct_evec[2];
        a_tmp = std::pow(CurvStruct_theta, 2.0);
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        r6 = _mm_loadu_pd(&y[0]);
        r7 = _mm_set1_pd(b_a_tmp);
        for (int b_k{0}; b_k < 10; b_k++) {
            __m128d r11;
            __m128d r12;
            __m128d r13;
            __m128d r9;
            double d4;
            double d6;
            r9 = _mm_loadu_pd(&sphiTCP0[b_k][0]);
            r11 = _mm_loadu_pd(&cphiTEcrCP0[b_k][0]);
            _mm_storeu_pd(&r1D[b_k][0],
                          _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r9),
                                                _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r11)),
                                     r6));
            r12 = _mm_loadu_pd(&cphiTCP0[b_k][0]);
            r13 = _mm_loadu_pd(&sphiTEcrCP0[b_k][0]);
            _mm_storeu_pd(&r2D[b_k][0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                                                   _mm_mul_pd(_mm_set1_pd(a_tmp), r13)));
            _mm_storeu_pd(&r3D[b_k][0], _mm_sub_pd(_mm_mul_pd(r7, r9), _mm_mul_pd(r7, r11)));
            d4 = sphiTCP0[b_k][2];
            d6 = cphiTEcrCP0[b_k][2];
            r1D[b_k][2] = (-CurvStruct_theta * d4 + CurvStruct_theta * d6) + y[2];
            r2D[b_k][2] = -a_tmp * cphiTCP0[b_k][2] - a_tmp * sphiTEcrCP0[b_k][2];
            r3D[b_k][2] = b_a_tmp * d4 - b_a_tmp * d6;
        }
    }
}

//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch,
               const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
               ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
               ::coder::array<double, 2U> &r3D)
{
    __m128d r;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> c_a;
    ::coder::array<double, 2U> cphi;
    ::coder::array<double, 2U> cphiTCP0;
    ::coder::array<double, 2U> cphiTEcrCP0;
    ::coder::array<double, 2U> phi_vec;
    ::coder::array<double, 2U> sphi;
    ::coder::array<double, 2U> sphiTCP0;
    ::coder::array<double, 2U> sphiTEcrCP0;
    double CP0[3];
    double EcrCP0[3];
    double P0P1[3];
    double y[3];
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    ZoneScopedN("EvalHelix");
    //
    //
    r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
    _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
    P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
    r0D.set_size(3, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        r0D[3 * i] = 0.0;
        r0D[3 * i + 1] = 0.0;
        r0D[3 * i + 2] = 0.0;
    }
    r1D.set_size(3, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r1D[3 * i1] = 0.0;
        r1D[3 * i1 + 1] = 0.0;
        r1D[3 * i1 + 2] = 0.0;
    }
    r2D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r2D[3 * i2] = 0.0;
        r2D[3 * i2 + 1] = 0.0;
        r2D[3 * i2 + 2] = 0.0;
    }
    r3D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r3D[3 * i3] = 0.0;
        r3D[3 * i3 + 1] = 0.0;
        r3D[3 * i3 + 2] = 0.0;
    }
    sqrt_calls++;
    if (c_assert(
            std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - P0P1[1] * CurvStruct_evec[2], 2.0) +
                       std::pow(P0P1[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - P0P1[0] * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        __m128d r1;
        double a;
        double a_tmp;
        double b_a;
        double b_a_tmp;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i4;
        int i6;
        int i8;
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int scalarLB;
        int vectorUB;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        r1 = _mm_loadu_pd((double *)&CurvStruct_CorrectedHelixCenter[0]);
        _mm_storeu_pd(&CP0[0], _mm_sub_pd(r, r1));
        CP0[2] = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        phi_vec.set_size(1, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        scalarLB = (u_vec.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i4 = 0; i4 <= vectorUB; i4 += 2) {
            _mm_storeu_pd(&phi_vec[i4], _mm_mul_pd(_mm_set1_pd(CurvStruct_theta),
                                                   _mm_loadu_pd((double *)&u_vec[i4])));
        }
        for (i4 = scalarLB; i4 < e_loop_ub; i4++) {
            phi_vec[i4] = CurvStruct_theta * u_vec[i4];
        }
        EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
        EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
        EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
        cphi.set_size(1, phi_vec.size(1));
        f_loop_ub = phi_vec.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            cphi[i5] = phi_vec[i5];
        }
        i6 = phi_vec.size(1);
        for (int k{0}; k < i6; k++) {
            cphi[k] = std::cos(cphi[k]);
        }
        cos_calls++;
        sphi.set_size(1, phi_vec.size(1));
        g_loop_ub = phi_vec.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            sphi[i7] = phi_vec[i7];
        }
        i8 = phi_vec.size(1);
        for (int b_k{0}; b_k < i8; b_k++) {
            sphi[b_k] = std::sin(sphi[b_k]);
        }
        sin_calls++;
        //
        cphiTCP0.set_size(3, cphi.size(1));
        h_loop_ub = cphi.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            __m128d r2;
            r2 = _mm_loadu_pd(&CP0[0]);
            _mm_storeu_pd(&cphiTCP0[3 * i9], _mm_mul_pd(r2, _mm_set1_pd(cphi[i9])));
            cphiTCP0[3 * i9 + 2] = CP0[2] * cphi[i9];
        }
        sphiTCP0.set_size(3, sphi.size(1));
        i_loop_ub = sphi.size(1);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            __m128d r3;
            r3 = _mm_loadu_pd(&CP0[0]);
            _mm_storeu_pd(&sphiTCP0[3 * i10], _mm_mul_pd(r3, _mm_set1_pd(sphi[i10])));
            sphiTCP0[3 * i10 + 2] = CP0[2] * sphi[i10];
        }
        cphiTEcrCP0.set_size(3, cphi.size(1));
        j_loop_ub = cphi.size(1);
        for (int i11{0}; i11 < j_loop_ub; i11++) {
            __m128d r4;
            r4 = _mm_loadu_pd(&EcrCP0[0]);
            _mm_storeu_pd(&cphiTEcrCP0[3 * i11], _mm_mul_pd(r4, _mm_set1_pd(cphi[i11])));
            cphiTEcrCP0[3 * i11 + 2] = EcrCP0[2] * cphi[i11];
        }
        sphiTEcrCP0.set_size(3, sphi.size(1));
        k_loop_ub = sphi.size(1);
        for (int i12{0}; i12 < k_loop_ub; i12++) {
            __m128d r5;
            r5 = _mm_loadu_pd(&EcrCP0[0]);
            _mm_storeu_pd(&sphiTEcrCP0[3 * i12], _mm_mul_pd(r5, _mm_set1_pd(sphi[i12])));
            sphiTEcrCP0[3 * i12 + 2] = EcrCP0[2] * sphi[i12];
        }
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        b.set_size(3, phi_vec.size(1));
        l_loop_ub = phi_vec.size(1);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            __m128d r6;
            __m128d r7;
            r6 = _mm_loadu_pd(&cphiTCP0[3 * i13]);
            r7 = _mm_loadu_pd(&sphiTEcrCP0[3 * i13]);
            _mm_storeu_pd(
                &b[3 * i13],
                _mm_add_pd(
                    _mm_add_pd(r6, r7),
                    _mm_add_pd(_mm_set1_pd(0.0),
                               _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                                     _mm_loadu_pd((double *)&CurvStruct_evec[0])),
                                          _mm_set1_pd(phi_vec[i13])))));
            b[3 * i13 + 2] = (cphiTCP0[3 * i13 + 2] + sphiTEcrCP0[3 * i13 + 2]) +
                             a * CurvStruct_evec[2] * phi_vec[i13];
        }
        r0D.set_size(3, b.size(1));
        if (b.size(1) != 0) {
            int bcoef;
            int i14;
            bcoef = (b.size(1) != 1);
            i14 = b.size(1) - 1;
            for (int c_k{0}; c_k <= i14; c_k++) {
                __m128d r8;
                int varargin_3;
                varargin_3 = bcoef * c_k;
                r8 = _mm_loadu_pd(&b[3 * varargin_3]);
                _mm_storeu_pd(&r0D[3 * c_k], _mm_add_pd(r1, r8));
                r0D[3 * c_k + 2] = CurvStruct_CorrectedHelixCenter[2] + b[3 * varargin_3 + 2];
            }
        }
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        _mm_storeu_pd(&y[0],
                      _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((double *)&CurvStruct_evec[0])));
        y[2] = b_a * CurvStruct_evec[2];
        c_a.set_size(3, sphiTCP0.size(1));
        m_loop_ub = sphiTCP0.size(1);
        for (int i15{0}; i15 < m_loop_ub; i15++) {
            __m128d r10;
            __m128d r9;
            r9 = _mm_loadu_pd(&sphiTCP0[3 * i15]);
            r10 = _mm_loadu_pd(&cphiTEcrCP0[3 * i15]);
            _mm_storeu_pd(&c_a[3 * i15],
                          _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r9),
                                     _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r10)));
            c_a[3 * i15 + 2] = -CurvStruct_theta * sphiTCP0[3 * i15 + 2] +
                               CurvStruct_theta * cphiTEcrCP0[3 * i15 + 2];
        }
        r1D.set_size(3, c_a.size(1));
        if (c_a.size(1) != 0) {
            int acoef;
            int i16;
            acoef = (c_a.size(1) != 1);
            i16 = c_a.size(1) - 1;
            for (int d_k{0}; d_k <= i16; d_k++) {
                __m128d r11;
                __m128d r13;
                int varargin_2;
                varargin_2 = acoef * d_k;
                r11 = _mm_loadu_pd(&c_a[3 * varargin_2]);
                r13 = _mm_loadu_pd(&y[0]);
                _mm_storeu_pd(&r1D[3 * d_k], _mm_add_pd(r11, r13));
                r1D[3 * d_k + 2] = c_a[3 * varargin_2 + 2] + y[2];
            }
        }
        a_tmp = std::pow(CurvStruct_theta, 2.0);
        r2D.set_size(3, cphiTCP0.size(1));
        n_loop_ub = cphiTCP0.size(1);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            __m128d r12;
            __m128d r14;
            r12 = _mm_loadu_pd(&cphiTCP0[3 * i17]);
            r14 = _mm_loadu_pd(&sphiTEcrCP0[3 * i17]);
            _mm_storeu_pd(&r2D[3 * i17], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                                                    _mm_mul_pd(_mm_set1_pd(a_tmp), r14)));
            r2D[3 * i17 + 2] = -a_tmp * cphiTCP0[3 * i17 + 2] - a_tmp * sphiTEcrCP0[3 * i17 + 2];
        }
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        r3D.set_size(3, sphiTCP0.size(1));
        o_loop_ub = sphiTCP0.size(1);
        for (int i18{0}; i18 < o_loop_ub; i18++) {
            __m128d r15;
            __m128d r16;
            __m128d r17;
            r15 = _mm_loadu_pd(&sphiTCP0[3 * i18]);
            r16 = _mm_loadu_pd(&cphiTEcrCP0[3 * i18]);
            r17 = _mm_set1_pd(b_a_tmp);
            _mm_storeu_pd(&r3D[3 * i18], _mm_sub_pd(_mm_mul_pd(r17, r15), _mm_mul_pd(r17, r16)));
            r3D[3 * i18 + 2] = b_a_tmp * sphiTCP0[3 * i18 + 2] - b_a_tmp * cphiTEcrCP0[3 * i18 + 2];
        }
    }
}

//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                double u_vec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch, double u_vec, double r0D[3],
               double r1D[3], double r2D[3], double r3D[3])
{
    __m128d r;
    __m128d r1;
    double CP0[3];
    double EcrCP0[3];
    double P0P1[3];
    double cphiTCP0[3];
    double sphiTCP0[3];
    ZoneScopedN("EvalHelix");
    //
    //
    r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
    _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
    r1 = _mm_set1_pd(0.0);
    _mm_storeu_pd(&r0D[0], r1);
    _mm_storeu_pd(&r1D[0], r1);
    _mm_storeu_pd(&r2D[0], r1);
    _mm_storeu_pd(&r3D[0], r1);
    P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    r3D[2] = 0.0;
    sqrt_calls++;
    if (c_assert(
            std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - P0P1[1] * CurvStruct_evec[2], 2.0) +
                       std::pow(P0P1[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - P0P1[0] * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        __m128d r10;
        __m128d r11;
        __m128d r12;
        __m128d r2;
        __m128d r3;
        __m128d r4;
        __m128d r5;
        __m128d r6;
        __m128d r7;
        __m128d r8;
        __m128d r9;
        double a;
        double a_tmp;
        double b_a;
        double b_a_tmp;
        double cphi;
        double d;
        double d1;
        double d2;
        double phi_vec;
        double sphi;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        phi_vec = CurvStruct_theta * u_vec;
        cphi = std::cos(phi_vec);
        cos_calls++;
        sphi = std::sin(phi_vec);
        sin_calls++;
        //
        r2 = _mm_loadu_pd((double *)&CurvStruct_CorrectedHelixCenter[0]);
        r3 = _mm_sub_pd(r, r2);
        _mm_storeu_pd(&CP0[0], r3);
        r4 = _mm_set1_pd(cphi);
        _mm_storeu_pd(&cphiTCP0[0], _mm_mul_pd(r3, r4));
        r5 = _mm_set1_pd(sphi);
        _mm_storeu_pd(&sphiTCP0[0], _mm_mul_pd(r3, r5));
        d = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        cphiTCP0[2] = d * cphi;
        sphiTCP0[2] = d * sphi;
        EcrCP0[0] = CurvStruct_evec[1] * d - CP0[1] * CurvStruct_evec[2];
        EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * d;
        EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        a_tmp = std::pow(CurvStruct_theta, 2.0);
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        r6 = _mm_loadu_pd(&EcrCP0[0]);
        r7 = _mm_mul_pd(r6, r4);
        r8 = _mm_mul_pd(r6, r5);
        r9 = _mm_loadu_pd(&cphiTCP0[0]);
        r10 = _mm_loadu_pd((double *)&CurvStruct_evec[0]);
        _mm_storeu_pd(&r0D[0], _mm_add_pd(r2, _mm_add_pd(_mm_add_pd(r9, r8),
                                                         _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a), r10),
                                                                    _mm_set1_pd(phi_vec)))));
        r11 = _mm_loadu_pd(&sphiTCP0[0]);
        _mm_storeu_pd(&r1D[0],
                      _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r11),
                                            _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r7)),
                                 _mm_mul_pd(_mm_set1_pd(b_a), r10)));
        _mm_storeu_pd(&r2D[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r9),
                                          _mm_mul_pd(_mm_set1_pd(a_tmp), r8)));
        r12 = _mm_set1_pd(b_a_tmp);
        _mm_storeu_pd(&r3D[0], _mm_sub_pd(_mm_mul_pd(r12, r11), _mm_mul_pd(r12, r7)));
        d1 = EcrCP0[2] * cphi;
        d2 = EcrCP0[2] * sphi;
        r0D[2] = CurvStruct_CorrectedHelixCenter[2] +
                 ((cphiTCP0[2] + d2) + a * CurvStruct_evec[2] * phi_vec);
        r1D[2] =
            (-CurvStruct_theta * sphiTCP0[2] + CurvStruct_theta * d1) + b_a * CurvStruct_evec[2];
        r2D[2] = -a_tmp * cphiTCP0[2] - a_tmp * d2;
        r3D[2] = b_a_tmp * sphiTCP0[2] - b_a_tmp * d1;
    }
}

} // namespace ocn

//
// File trailer for EvalHelix.cpp
//
// [EOF]
//
