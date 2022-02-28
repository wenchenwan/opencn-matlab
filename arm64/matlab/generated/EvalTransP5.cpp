//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:02:06
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

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
    double d14;
    double d15;
    double d16;
    double d2;
    double d21;
    double d22;
    double d23;
    double d7;
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
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int c_k{0}; c_k < 3; c_k++) {
        p5_3D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
    }
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
        double d3;
        double d4;
        double d5;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d3 = CurvStruct_CoeffP5[i + 1][0];
        d4 = CurvStruct_CoeffP5[i + 1][1];
        d5 = CurvStruct_CoeffP5[i + 1][2];
        for (int d_k{0}; d_k < 10; d_k++) {
            double d6;
            d6 = u_vec[d_k];
            r_0D[d_k][0] = d6 * r_0D[d_k][0] + d3;
            r_0D[d_k][1] = d6 * r_0D[d_k][1] + d4;
            r_0D[d_k][2] = d6 * r_0D[d_k][2] + d5;
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
    d7 = p5_1D[0][0];
    d8 = p5_1D[0][1];
    d9 = p5_1D[0][2];
    for (int b_t{0}; b_t < 10; b_t++) {
        r_1D[b_t][0] = d7;
        r_1D[b_t][1] = d8;
        r_1D[b_t][2] = d9;
    }
    // 'mypolyval:12' for i=2:nc
    for (int b_i{0}; b_i < 4; b_i++) {
        double d10;
        double d11;
        double d12;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d10 = p5_1D[b_i + 1][0];
        d11 = p5_1D[b_i + 1][1];
        d12 = p5_1D[b_i + 1][2];
        for (int e_k{0}; e_k < 10; e_k++) {
            double d13;
            d13 = u_vec[e_k];
            r_1D[e_k][0] = d13 * r_1D[e_k][0] + d10;
            r_1D[e_k][1] = d13 * r_1D[e_k][1] + d11;
            r_1D[e_k][2] = d13 * r_1D[e_k][2] + d12;
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
    d14 = p5_2D[0][0];
    d15 = p5_2D[0][1];
    d16 = p5_2D[0][2];
    for (int c_t{0}; c_t < 10; c_t++) {
        r_2D[c_t][0] = d14;
        r_2D[c_t][1] = d15;
        r_2D[c_t][2] = d16;
    }
    // 'mypolyval:12' for i=2:nc
    for (int c_i{0}; c_i < 3; c_i++) {
        double d17;
        double d18;
        double d19;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d17 = p5_2D[c_i + 1][0];
        d18 = p5_2D[c_i + 1][1];
        d19 = p5_2D[c_i + 1][2];
        for (int f_k{0}; f_k < 10; f_k++) {
            double d20;
            d20 = u_vec[f_k];
            r_2D[f_k][0] = d20 * r_2D[f_k][0] + d17;
            r_2D[f_k][1] = d20 * r_2D[f_k][1] + d18;
            r_2D[f_k][2] = d20 * r_2D[f_k][2] + d19;
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
    d21 = p5_3D[0][0];
    d22 = p5_3D[0][1];
    d23 = p5_3D[0][2];
    for (int d_t{0}; d_t < 10; d_t++) {
        r_3D[d_t][0] = d21;
        r_3D[d_t][1] = d22;
        r_3D[d_t][2] = d23;
    }
    // 'mypolyval:12' for i=2:nc
    for (int d_i{0}; d_i < 2; d_i++) {
        double d24;
        double d25;
        double d26;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d24 = p5_3D[d_i + 1][0];
        d25 = p5_3D[d_i + 1][1];
        d26 = p5_3D[d_i + 1][2];
        for (int g_k{0}; g_k < 10; g_k++) {
            double d27;
            d27 = u_vec[g_k];
            r_3D[g_k][0] = d27 * r_3D[g_k][0] + d24;
            r_3D[g_k][1] = d27 * r_3D[g_k][1] + d25;
            r_3D[g_k][2] = d27 * r_3D[g_k][2] + d26;
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
    ::coder::array<double, 2U> r;
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
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int c_k{0}; c_k < 3; c_k++) {
        p5_3D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
    }
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
        r.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int na;
            na = u_vec.size(1);
            for (int d_k{0}; d_k < na; d_k++) {
                r[3 * d_k] = u_vec[d_k];
                r[3 * d_k + 1] = u_vec[d_k];
                r[3 * d_k + 2] = u_vec[d_k];
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
        if (r.size(1) == 1) {
            i2 = r_0D.size(1);
        } else {
            i2 = r.size(1);
        }
        if ((r.size(1) == r_0D.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            r_0D.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i4{0}; i4 < loop_ub; i4++) {
                r_0D[3 * i4] = r[3 * i4] * r_0D[3 * i4] + b[3 * i4];
                r_0D[3 * i4 + 1] = r[3 * i4 + 1] * r_0D[3 * i4 + 1] + b[3 * i4 + 1];
                r_0D[3 * i4 + 2] = r[3 * i4 + 2] * r_0D[3 * i4 + 2] + b[3 * i4 + 2];
            }
        } else {
            binary_expand_op(r_0D, r, b);
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
        r.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int b_na;
            b_na = u_vec.size(1);
            for (int e_k{0}; e_k < b_na; e_k++) {
                r[3 * e_k] = u_vec[e_k];
                r[3 * e_k + 1] = u_vec[e_k];
                r[3 * e_k + 2] = u_vec[e_k];
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
        if (r.size(1) == 1) {
            i6 = r_1D.size(1);
        } else {
            i6 = r.size(1);
        }
        if ((r.size(1) == r_1D.size(1)) && (i6 == b.size(1))) {
            int b_loop_ub;
            r_1D.set_size(3, r.size(1));
            b_loop_ub = r.size(1);
            for (int i8{0}; i8 < b_loop_ub; i8++) {
                r_1D[3 * i8] = r[3 * i8] * r_1D[3 * i8] + b[3 * i8];
                r_1D[3 * i8 + 1] = r[3 * i8 + 1] * r_1D[3 * i8 + 1] + b[3 * i8 + 1];
                r_1D[3 * i8 + 2] = r[3 * i8 + 2] * r_1D[3 * i8 + 2] + b[3 * i8 + 2];
            }
        } else {
            binary_expand_op(r_1D, r, b);
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
        r.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int c_na;
            c_na = u_vec.size(1);
            for (int f_k{0}; f_k < c_na; f_k++) {
                r[3 * f_k] = u_vec[f_k];
                r[3 * f_k + 1] = u_vec[f_k];
                r[3 * f_k + 2] = u_vec[f_k];
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
        if (r.size(1) == 1) {
            i10 = r_2D.size(1);
        } else {
            i10 = r.size(1);
        }
        if ((r.size(1) == r_2D.size(1)) && (i10 == b.size(1))) {
            int c_loop_ub;
            r_2D.set_size(3, r.size(1));
            c_loop_ub = r.size(1);
            for (int i12{0}; i12 < c_loop_ub; i12++) {
                r_2D[3 * i12] = r[3 * i12] * r_2D[3 * i12] + b[3 * i12];
                r_2D[3 * i12 + 1] = r[3 * i12 + 1] * r_2D[3 * i12 + 1] + b[3 * i12 + 1];
                r_2D[3 * i12 + 2] = r[3 * i12 + 2] * r_2D[3 * i12 + 2] + b[3 * i12 + 2];
            }
        } else {
            binary_expand_op(r_2D, r, b);
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
        r.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int d_na;
            d_na = u_vec.size(1);
            for (int g_k{0}; g_k < d_na; g_k++) {
                r[3 * g_k] = u_vec[g_k];
                r[3 * g_k + 1] = u_vec[g_k];
                r[3 * g_k + 2] = u_vec[g_k];
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
        if (r.size(1) == 1) {
            i14 = r_3D.size(1);
        } else {
            i14 = r.size(1);
        }
        if ((r.size(1) == r_3D.size(1)) && (i14 == b.size(1))) {
            int d_loop_ub;
            r_3D.set_size(3, r.size(1));
            d_loop_ub = r.size(1);
            for (int i15{0}; i15 < d_loop_ub; i15++) {
                r_3D[3 * i15] = r[3 * i15] * r_3D[3 * i15] + b[3 * i15];
                r_3D[3 * i15 + 1] = r[3 * i15 + 1] * r_3D[3 * i15 + 1] + b[3 * i15 + 1];
                r_3D[3 * i15 + 2] = r[3 * i15 + 2] * r_3D[3 * i15 + 2] + b[3 * i15 + 2];
            }
        } else {
            binary_expand_op(r_3D, r, b);
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
    double p5_1D[5][3];
    double p5_2D[4][3];
    double p5_3D[3][3];
    double d;
    double d1;
    double d10;
    double d11;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
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
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
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
    for (int c_k{0}; c_k < 3; c_k++) {
        p5_3D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        p5_3D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
        r_0D[c_k] = CurvStruct_CoeffP5[0][c_k];
    }
    // 'mypolyval:12' for i=2:nc
    d = r_0D[0];
    d1 = r_0D[1];
    d2 = r_0D[2];
    for (int i{0}; i < 5; i++) {
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d = u_vec * d + CurvStruct_CoeffP5[i + 1][0];
        d1 = u_vec * d1 + CurvStruct_CoeffP5[i + 1][1];
        d2 = u_vec * d2 + CurvStruct_CoeffP5[i + 1][2];
    }
    r_0D[2] = d2;
    r_0D[1] = d1;
    r_0D[0] = d;
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
    // 'mypolyval:12' for i=2:nc
    d3 = p5_1D[0][0];
    d4 = p5_1D[0][1];
    d5 = p5_1D[0][2];
    for (int b_i{0}; b_i < 4; b_i++) {
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d3 = u_vec * d3 + p5_1D[b_i + 1][0];
        d4 = u_vec * d4 + p5_1D[b_i + 1][1];
        d5 = u_vec * d5 + p5_1D[b_i + 1][2];
    }
    r_1D[2] = d5;
    r_1D[1] = d4;
    r_1D[0] = d3;
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
    d6 = p5_2D[0][0];
    d7 = p5_2D[0][1];
    d8 = p5_2D[0][2];
    for (int c_i{0}; c_i < 3; c_i++) {
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d6 = u_vec * d6 + p5_2D[c_i + 1][0];
        d7 = u_vec * d7 + p5_2D[c_i + 1][1];
        d8 = u_vec * d8 + p5_2D[c_i + 1][2];
        r_3D[c_i] = p5_3D[0][c_i];
    }
    r_2D[2] = d8;
    r_2D[1] = d7;
    r_2D[0] = d6;
    // 'mypolyval:12' for i=2:nc
    d9 = r_3D[0];
    d10 = r_3D[1];
    d11 = r_3D[2];
    for (int d_i{0}; d_i < 2; d_i++) {
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d9 = u_vec * d9 + p5_3D[d_i + 1][0];
        d10 = u_vec * d10 + p5_3D[d_i + 1][1];
        d11 = u_vec * d11 + p5_3D[d_i + 1][2];
    }
    r_3D[2] = d11;
    r_3D[1] = d10;
    r_3D[0] = d9;
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
