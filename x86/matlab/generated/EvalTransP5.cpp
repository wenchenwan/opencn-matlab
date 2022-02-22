//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <emmintrin.h>

// Function Definitions
//
// function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                const double u_vec[10]
//                double r_0D[10][3]
//                double r_1D[10][3]
//                double r_2D[10][3]
//                double r_3D[10][3]
// Return Type  : void
//
namespace ocn {
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const double u_vec[10], double r_0D[10][3],
                 double r_1D[10][3], double r_2D[10][3], double r_3D[10][3])
{
    double p5_1D[5][3];
    double p5_2D[4][3];
    double p5_3D[3][3];
    double d;
    double d1;
    double d10;
    double d12;
    double d13;
    double d14;
    double d2;
    double d4;
    double d5;
    double d6;
    double d8;
    double d9;
    // 'EvalTransP5:2' if ~coder.target('MATLAB')
    // 'EvalTransP5:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:4' coder.inline('never')
    // 'EvalTransP5:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:8' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:9' p5_1D = mypolyder(p5);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int k{0}; k < 5; k++) {
        _mm_storeu_pd(&p5_1D[k][0],
                      _mm_mul_pd(_mm_loadu_pd((const double *)&CurvStruct_CoeffP5[k][0]),
                                 _mm_set1_pd(5.0 - static_cast<double>(k))));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    r = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r = _mm_loadu_pd(&p5_1D[1][0]);
    r1 = _mm_set1_pd(3.0);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r = _mm_loadu_pd(&p5_1D[2][0]);
    r2 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r = _mm_loadu_pd(&p5_1D[3][0]);
    r3 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
    p5_2D[3][2] = p5_1D[3][2];
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    r4 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r4, r1));
    p5_3D[0][2] = p5_2D[0][2] * 3.0;
    r4 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r4, r2));
    p5_3D[1][2] = p5_2D[1][2] * 2.0;
    r4 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r4, r3));
    p5_3D[2][2] = p5_2D[2][2];
    //
    // 'EvalTransP5:13' r_0D = mypolyval(p5,    u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    d = CurvStruct_CoeffP5[0][0];
    d1 = CurvStruct_CoeffP5[0][1];
    d2 = CurvStruct_CoeffP5[0][2];
    for (int t{0}; t < 10; t++) {
        r_0D[t][0] = d;
        r_0D[t][1] = d1;
        r_0D[t][2] = d2;
    }
    // 'mypolyval:12' for i=2:nc
    for (int i{0}; i < 5; i++) {
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        for (int b_k{0}; b_k < 10; b_k++) {
            __m128d r5;
            double d3;
            r5 = _mm_loadu_pd(&r_0D[b_k][0]);
            d3 = u_vec[b_k];
            _mm_storeu_pd(&r_0D[b_k][0],
                          _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r5),
                                     _mm_loadu_pd((const double *)&CurvStruct_CoeffP5[i + 1][0])));
            r_0D[b_k][2] = d3 * r_0D[b_k][2] + CurvStruct_CoeffP5[i + 1][2];
        }
    }
    // 'EvalTransP5:14' r_1D = mypolyval(p5_1D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    d4 = p5_1D[0][0];
    d5 = p5_1D[0][1];
    d6 = p5_1D[0][2];
    for (int b_t{0}; b_t < 10; b_t++) {
        r_1D[b_t][0] = d4;
        r_1D[b_t][1] = d5;
        r_1D[b_t][2] = d6;
    }
    // 'mypolyval:12' for i=2:nc
    for (int b_i{0}; b_i < 4; b_i++) {
        __m128d r6;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r6 = _mm_loadu_pd(&p5_1D[b_i + 1][0]);
        for (int c_k{0}; c_k < 10; c_k++) {
            __m128d r7;
            double d7;
            r7 = _mm_loadu_pd(&r_1D[c_k][0]);
            d7 = u_vec[c_k];
            _mm_storeu_pd(&r_1D[c_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d7), r7), r6));
            r_1D[c_k][2] = d7 * r_1D[c_k][2] + p5_1D[b_i + 1][2];
        }
    }
    // 'EvalTransP5:15' r_2D = mypolyval(p5_2D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    d8 = p5_2D[0][0];
    d9 = p5_2D[0][1];
    d10 = p5_2D[0][2];
    for (int c_t{0}; c_t < 10; c_t++) {
        r_2D[c_t][0] = d8;
        r_2D[c_t][1] = d9;
        r_2D[c_t][2] = d10;
    }
    // 'mypolyval:12' for i=2:nc
    for (int c_i{0}; c_i < 3; c_i++) {
        __m128d r8;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r8 = _mm_loadu_pd(&p5_2D[c_i + 1][0]);
        for (int d_k{0}; d_k < 10; d_k++) {
            __m128d r9;
            double d11;
            r9 = _mm_loadu_pd(&r_2D[d_k][0]);
            d11 = u_vec[d_k];
            _mm_storeu_pd(&r_2D[d_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d11), r9), r8));
            r_2D[d_k][2] = d11 * r_2D[d_k][2] + p5_2D[c_i + 1][2];
        }
    }
    // 'EvalTransP5:16' r_3D = mypolyval(p5_3D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    d12 = p5_3D[0][0];
    d13 = p5_3D[0][1];
    d14 = p5_3D[0][2];
    for (int d_t{0}; d_t < 10; d_t++) {
        r_3D[d_t][0] = d12;
        r_3D[d_t][1] = d13;
        r_3D[d_t][2] = d14;
    }
    // 'mypolyval:12' for i=2:nc
    for (int d_i{0}; d_i < 2; d_i++) {
        __m128d r10;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r10 = _mm_loadu_pd(&p5_3D[d_i + 1][0]);
        for (int e_k{0}; e_k < 10; e_k++) {
            __m128d r11;
            double d15;
            r11 = _mm_loadu_pd(&r_3D[e_k][0]);
            d15 = u_vec[e_k];
            _mm_storeu_pd(&r_3D[e_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d15), r11), r10));
            r_3D[e_k][2] = d15 * r_3D[e_k][2] + p5_3D[d_i + 1][2];
        }
    }
}

//
// function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r_0D
//                ::coder::array<double, 2U> &r_1D
//                ::coder::array<double, 2U> &r_2D
//                ::coder::array<double, 2U> &r_3D
// Return Type  : void
//
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const ::coder::array<double, 2U> &u_vec,
                 ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U> &r_1D,
                 ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U> &r_3D)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> r5;
    double p5_1D[5][3];
    double p5_2D[4][3];
    double p5_3D[3][3];
    // 'EvalTransP5:2' if ~coder.target('MATLAB')
    // 'EvalTransP5:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:4' coder.inline('never')
    // 'EvalTransP5:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:8' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:9' p5_1D = mypolyder(p5);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int k{0}; k < 5; k++) {
        _mm_storeu_pd(&p5_1D[k][0],
                      _mm_mul_pd(_mm_loadu_pd((const double *)&CurvStruct_CoeffP5[k][0]),
                                 _mm_set1_pd(5.0 - static_cast<double>(k))));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    r = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r = _mm_loadu_pd(&p5_1D[1][0]);
    r1 = _mm_set1_pd(3.0);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r = _mm_loadu_pd(&p5_1D[2][0]);
    r2 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r = _mm_loadu_pd(&p5_1D[3][0]);
    r3 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
    p5_2D[3][2] = p5_1D[3][2];
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    r4 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r4, r1));
    p5_3D[0][2] = p5_2D[0][2] * 3.0;
    r4 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r4, r2));
    p5_3D[1][2] = p5_2D[1][2] * 2.0;
    r4 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r4, r3));
    p5_3D[2][2] = p5_2D[2][2];
    //
    // 'EvalTransP5:13' r_0D = mypolyval(p5,    u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_0D.set_size(3, u_vec.size(1));
    if (u_vec.size(1) != 0) {
        int i;
        i = u_vec.size(1) - 1;
        for (int t{0}; t <= i; t++) {
            r_0D[3 * t] = CurvStruct_CoeffP5[0][0];
            r_0D[3 * t + 1] = CurvStruct_CoeffP5[0][1];
            r_0D[3 * t + 2] = CurvStruct_CoeffP5[0][2];
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int b_i{0}; b_i < 5; b_i++) {
        int i2;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r5.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int na;
            na = u_vec.size(1);
            for (int b_k{0}; b_k < na; b_k++) {
                r5[3 * b_k] = u_vec[b_k];
                r5[3 * b_k + 1] = u_vec[b_k];
                r5[3 * b_k + 2] = u_vec[b_k];
            }
        }
        b.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i1;
            i1 = u_vec.size(1) - 1;
            for (int b_t{0}; b_t <= i1; b_t++) {
                b[3 * b_t] = CurvStruct_CoeffP5[b_i + 1][0];
                b[3 * b_t + 1] = CurvStruct_CoeffP5[b_i + 1][1];
                b[3 * b_t + 2] = CurvStruct_CoeffP5[b_i + 1][2];
            }
        }
        if (r5.size(1) == 1) {
            i2 = r_0D.size(1);
        } else {
            i2 = r5.size(1);
        }
        if ((r5.size(1) == r_0D.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            r_0D.set_size(3, r5.size(1));
            loop_ub = r5.size(1);
            for (int i4{0}; i4 < loop_ub; i4++) {
                __m128d r6;
                __m128d r7;
                __m128d r8;
                r6 = _mm_loadu_pd(&r5[3 * i4]);
                r7 = _mm_loadu_pd(&r_0D[3 * i4]);
                r8 = _mm_loadu_pd(&b[3 * i4]);
                _mm_storeu_pd(&r_0D[3 * i4], _mm_add_pd(_mm_mul_pd(r6, r7), r8));
                r_0D[3 * i4 + 2] = r5[3 * i4 + 2] * r_0D[3 * i4 + 2] + b[3 * i4 + 2];
            }
        } else {
            binary_expand_op(r_0D, r5, b);
        }
    }
    // 'EvalTransP5:14' r_1D = mypolyval(p5_1D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_1D.set_size(3, u_vec.size(1));
    if (u_vec.size(1) != 0) {
        int i3;
        i3 = u_vec.size(1) - 1;
        for (int c_t{0}; c_t <= i3; c_t++) {
            r_1D[3 * c_t] = p5_1D[0][0];
            r_1D[3 * c_t + 1] = p5_1D[0][1];
            r_1D[3 * c_t + 2] = p5_1D[0][2];
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int c_i{0}; c_i < 4; c_i++) {
        int i6;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r5.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int b_na;
            b_na = u_vec.size(1);
            for (int c_k{0}; c_k < b_na; c_k++) {
                r5[3 * c_k] = u_vec[c_k];
                r5[3 * c_k + 1] = u_vec[c_k];
                r5[3 * c_k + 2] = u_vec[c_k];
            }
        }
        b.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i5;
            i5 = u_vec.size(1) - 1;
            for (int d_t{0}; d_t <= i5; d_t++) {
                b[3 * d_t] = p5_1D[c_i + 1][0];
                b[3 * d_t + 1] = p5_1D[c_i + 1][1];
                b[3 * d_t + 2] = p5_1D[c_i + 1][2];
            }
        }
        if (r5.size(1) == 1) {
            i6 = r_1D.size(1);
        } else {
            i6 = r5.size(1);
        }
        if ((r5.size(1) == r_1D.size(1)) && (i6 == b.size(1))) {
            int b_loop_ub;
            r_1D.set_size(3, r5.size(1));
            b_loop_ub = r5.size(1);
            for (int i8{0}; i8 < b_loop_ub; i8++) {
                __m128d r10;
                __m128d r11;
                __m128d r9;
                r9 = _mm_loadu_pd(&r5[3 * i8]);
                r10 = _mm_loadu_pd(&r_1D[3 * i8]);
                r11 = _mm_loadu_pd(&b[3 * i8]);
                _mm_storeu_pd(&r_1D[3 * i8], _mm_add_pd(_mm_mul_pd(r9, r10), r11));
                r_1D[3 * i8 + 2] = r5[3 * i8 + 2] * r_1D[3 * i8 + 2] + b[3 * i8 + 2];
            }
        } else {
            binary_expand_op(r_1D, r5, b);
        }
    }
    // 'EvalTransP5:15' r_2D = mypolyval(p5_2D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_2D.set_size(3, u_vec.size(1));
    if (u_vec.size(1) != 0) {
        int i7;
        i7 = u_vec.size(1) - 1;
        for (int e_t{0}; e_t <= i7; e_t++) {
            r_2D[3 * e_t] = p5_2D[0][0];
            r_2D[3 * e_t + 1] = p5_2D[0][1];
            r_2D[3 * e_t + 2] = p5_2D[0][2];
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int d_i{0}; d_i < 3; d_i++) {
        int i10;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r5.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int c_na;
            c_na = u_vec.size(1);
            for (int d_k{0}; d_k < c_na; d_k++) {
                r5[3 * d_k] = u_vec[d_k];
                r5[3 * d_k + 1] = u_vec[d_k];
                r5[3 * d_k + 2] = u_vec[d_k];
            }
        }
        b.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i9;
            i9 = u_vec.size(1) - 1;
            for (int f_t{0}; f_t <= i9; f_t++) {
                b[3 * f_t] = p5_2D[d_i + 1][0];
                b[3 * f_t + 1] = p5_2D[d_i + 1][1];
                b[3 * f_t + 2] = p5_2D[d_i + 1][2];
            }
        }
        if (r5.size(1) == 1) {
            i10 = r_2D.size(1);
        } else {
            i10 = r5.size(1);
        }
        if ((r5.size(1) == r_2D.size(1)) && (i10 == b.size(1))) {
            int c_loop_ub;
            r_2D.set_size(3, r5.size(1));
            c_loop_ub = r5.size(1);
            for (int i12{0}; i12 < c_loop_ub; i12++) {
                __m128d r12;
                __m128d r13;
                __m128d r14;
                r12 = _mm_loadu_pd(&r5[3 * i12]);
                r13 = _mm_loadu_pd(&r_2D[3 * i12]);
                r14 = _mm_loadu_pd(&b[3 * i12]);
                _mm_storeu_pd(&r_2D[3 * i12], _mm_add_pd(_mm_mul_pd(r12, r13), r14));
                r_2D[3 * i12 + 2] = r5[3 * i12 + 2] * r_2D[3 * i12 + 2] + b[3 * i12 + 2];
            }
        } else {
            binary_expand_op(r_2D, r5, b);
        }
    }
    // 'EvalTransP5:16' r_3D = mypolyval(p5_3D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_3D.set_size(3, u_vec.size(1));
    if (u_vec.size(1) != 0) {
        int i11;
        i11 = u_vec.size(1) - 1;
        for (int g_t{0}; g_t <= i11; g_t++) {
            r_3D[3 * g_t] = p5_3D[0][0];
            r_3D[3 * g_t + 1] = p5_3D[0][1];
            r_3D[3 * g_t + 2] = p5_3D[0][2];
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int e_i{0}; e_i < 2; e_i++) {
        int i14;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r5.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int d_na;
            d_na = u_vec.size(1);
            for (int e_k{0}; e_k < d_na; e_k++) {
                r5[3 * e_k] = u_vec[e_k];
                r5[3 * e_k + 1] = u_vec[e_k];
                r5[3 * e_k + 2] = u_vec[e_k];
            }
        }
        b.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i13;
            i13 = u_vec.size(1) - 1;
            for (int h_t{0}; h_t <= i13; h_t++) {
                b[3 * h_t] = p5_3D[e_i + 1][0];
                b[3 * h_t + 1] = p5_3D[e_i + 1][1];
                b[3 * h_t + 2] = p5_3D[e_i + 1][2];
            }
        }
        if (r5.size(1) == 1) {
            i14 = r_3D.size(1);
        } else {
            i14 = r5.size(1);
        }
        if ((r5.size(1) == r_3D.size(1)) && (i14 == b.size(1))) {
            int d_loop_ub;
            r_3D.set_size(3, r5.size(1));
            d_loop_ub = r5.size(1);
            for (int i15{0}; i15 < d_loop_ub; i15++) {
                __m128d r15;
                __m128d r16;
                __m128d r17;
                r15 = _mm_loadu_pd(&r5[3 * i15]);
                r16 = _mm_loadu_pd(&r_3D[3 * i15]);
                r17 = _mm_loadu_pd(&b[3 * i15]);
                _mm_storeu_pd(&r_3D[3 * i15], _mm_add_pd(_mm_mul_pd(r15, r16), r17));
                r_3D[3 * i15 + 2] = r5[3 * i15 + 2] * r_3D[3 * i15 + 2] + b[3 * i15 + 2];
            }
        } else {
            binary_expand_op(r_3D, r5, b);
        }
    }
}

//
// function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                double u_vec
//                double r_0D[3]
//                double r_1D[3]
//                double r_2D[3]
//                double r_3D[3]
// Return Type  : void
//
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
                 double r_1D[3], double r_2D[3], double r_3D[3])
{
    __m128d r;
    __m128d r1;
    __m128d r2;
    double p5_1D[5][3];
    double p5_2D[4][3];
    double p5_3D[3][3];
    // 'EvalTransP5:2' if ~coder.target('MATLAB')
    // 'EvalTransP5:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:4' coder.inline('never')
    // 'EvalTransP5:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:8' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:9' p5_1D = mypolyder(p5);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    r = _mm_set1_pd(3.0);
    r1 = _mm_set1_pd(2.0);
    r2 = _mm_set1_pd(1.0);
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    //
    // 'EvalTransP5:13' r_0D = mypolyval(p5,    u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_0D[0] = CurvStruct_CoeffP5[0][0];
    r_0D[1] = CurvStruct_CoeffP5[0][1];
    r_0D[2] = CurvStruct_CoeffP5[0][2];
    // 'mypolyval:12' for i=2:nc
    for (int i{0}; i < 5; i++) {
        __m128d r4;
        _mm_storeu_pd(&p5_1D[i][0],
                      _mm_mul_pd(_mm_loadu_pd((const double *)&CurvStruct_CoeffP5[i][0]),
                                 _mm_set1_pd(5.0 - static_cast<double>(i))));
        p5_1D[i][2] = CurvStruct_CoeffP5[i][2] * (5.0 - static_cast<double>(i));
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r4 = _mm_loadu_pd(&r_0D[0]);
        _mm_storeu_pd(&r_0D[0],
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(u_vec), r4),
                                 _mm_loadu_pd((const double *)&CurvStruct_CoeffP5[i + 1][0])));
        r_0D[2] = u_vec * r_0D[2] + CurvStruct_CoeffP5[i + 1][2];
    }
    __m128d r10;
    __m128d r11;
    __m128d r12;
    __m128d r3;
    __m128d r5;
    __m128d r6;
    __m128d r7;
    __m128d r8;
    __m128d r9;
    r3 = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r3, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r3 = _mm_loadu_pd(&p5_1D[1][0]);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r3, r));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r3 = _mm_loadu_pd(&p5_1D[2][0]);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r3, r1));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r3 = _mm_loadu_pd(&p5_1D[3][0]);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r3, r2));
    p5_2D[3][2] = p5_1D[3][2];
    r5 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r5, r));
    p5_3D[0][2] = p5_2D[0][2] * 3.0;
    r5 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r5, r1));
    p5_3D[1][2] = p5_2D[1][2] * 2.0;
    r5 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r5, r2));
    p5_3D[2][2] = p5_2D[2][2];
    // 'EvalTransP5:14' r_1D = mypolyval(p5_1D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_1D[0] = p5_1D[0][0];
    r_1D[1] = p5_1D[0][1];
    r_1D[2] = p5_1D[0][2];
    // 'mypolyval:12' for i=2:nc
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r6 = _mm_loadu_pd(&r_1D[0]);
    r7 = _mm_loadu_pd(&p5_1D[1][0]);
    r8 = _mm_set1_pd(u_vec);
    _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
    r_1D[2] = u_vec * r_1D[2] + p5_1D[1][2];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r6 = _mm_loadu_pd(&r_1D[0]);
    r7 = _mm_loadu_pd(&p5_1D[2][0]);
    _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
    r_1D[2] = u_vec * r_1D[2] + p5_1D[2][2];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r6 = _mm_loadu_pd(&r_1D[0]);
    r7 = _mm_loadu_pd(&p5_1D[3][0]);
    _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
    r_1D[2] = u_vec * r_1D[2] + p5_1D[3][2];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r6 = _mm_loadu_pd(&r_1D[0]);
    r7 = _mm_loadu_pd(&p5_1D[4][0]);
    _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
    r_1D[2] = u_vec * r_1D[2] + p5_1D[4][2];
    // 'EvalTransP5:15' r_2D = mypolyval(p5_2D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    r_2D[0] = p5_2D[0][0];
    r_2D[1] = p5_2D[0][1];
    r_2D[2] = p5_2D[0][2];
    // 'mypolyval:12' for i=2:nc
    // 'EvalTransP5:16' r_3D = mypolyval(p5_3D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r9 = _mm_loadu_pd(&r_2D[0]);
    r10 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
    r_2D[2] = u_vec * r_2D[2] + p5_2D[1][2];
    r_3D[0] = p5_3D[0][0];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r9 = _mm_loadu_pd(&r_2D[0]);
    r10 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
    r_2D[2] = u_vec * r_2D[2] + p5_2D[2][2];
    r_3D[1] = p5_3D[0][1];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r9 = _mm_loadu_pd(&r_2D[0]);
    r10 = _mm_loadu_pd(&p5_2D[3][0]);
    _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
    r_2D[2] = u_vec * r_2D[2] + p5_1D[3][2];
    r_3D[2] = p5_3D[0][2];
    // 'mypolyval:12' for i=2:nc
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r11 = _mm_loadu_pd(&r_3D[0]);
    r12 = _mm_loadu_pd(&p5_3D[1][0]);
    _mm_storeu_pd(&r_3D[0], _mm_add_pd(_mm_mul_pd(r8, r11), r12));
    r_3D[2] = u_vec * r_3D[2] + p5_3D[1][2];
    // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
    r11 = _mm_loadu_pd(&r_3D[0]);
    r12 = _mm_loadu_pd(&p5_3D[2][0]);
    _mm_storeu_pd(&r_3D[0], _mm_add_pd(_mm_mul_pd(r8, r11), r12));
    r_3D[2] = u_vec * r_3D[2] + p5_2D[2][2];
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
