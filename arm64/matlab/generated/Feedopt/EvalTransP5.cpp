//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyder.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Definitions
//
// function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec, nAxis)
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                const ::coder::array<double, 2U> &u_vec
//                int nAxis
//                ::coder::array<double, 2U> &r_0D
//                ::coder::array<double, 2U> &r_1D
//                ::coder::array<double, 2U> &r_2D
//                ::coder::array<double, 2U> &r_3D
// Return Type  : void
//
namespace ocn {
void EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                 const ::coder::array<double, 2U> &u_vec, int nAxis,
                 ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U> &r_1D,
                 ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U> &r_3D)
{
    ::coder::array<double, 2U> D0;
    ::coder::array<double, 2U> D1;
    ::coder::array<double, 2U> D2;
    ::coder::array<double, 2U> D3;
    ::coder::array<double, 2U> d_b;
    ::coder::array<double, 2U> e_b;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> p5_2D;
    ::coder::array<double, 2U> p5_3D;
    ::coder::array<signed char, 2U> b;
    ::coder::array<signed char, 2U> b_b;
    ::coder::array<signed char, 2U> c_b;
    int i_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int m_loop_ub;
    int o_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
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
    b.set_size(CurvStruct_CoeffP5.size(0), 5);
    if (CurvStruct_CoeffP5.size(0) != 0) {
        int i;
        i = CurvStruct_CoeffP5.size(0) - 1;
        for (int k{0}; k < 5; k++) {
            for (int t{0}; t <= i; t++) {
                b[t + b.size(0) * k] = static_cast<signed char>(5 - k);
            }
        }
    }
    if (CurvStruct_CoeffP5.size(0) == b.size(0)) {
        int loop_ub;
        loop_ub = CurvStruct_CoeffP5.size(0);
        p5_1D.set_size(CurvStruct_CoeffP5.size(0), 5);
        for (int i1{0}; i1 < 5; i1++) {
            for (int i2{0}; i2 < loop_ub; i2++) {
                p5_1D[i2 + p5_1D.size(0) * i1] =
                    CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1] *
                    static_cast<double>(b[i2 + b.size(0) * i1]);
            }
        }
    } else {
        c_binary_expand_op(p5_1D, CurvStruct_CoeffP5, b);
    }
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    b_b.set_size(p5_1D.size(0), 4);
    if (p5_1D.size(0) != 0) {
        int i3;
        i3 = p5_1D.size(0) - 1;
        for (int b_k{0}; b_k < 4; b_k++) {
            for (int b_t{0}; b_t <= i3; b_t++) {
                b_b[b_t + b_b.size(0) * b_k] = static_cast<signed char>(4 - b_k);
            }
        }
    }
    if (p5_1D.size(0) == b_b.size(0)) {
        int b_loop_ub;
        b_loop_ub = p5_1D.size(0);
        p5_2D.set_size(p5_1D.size(0), 4);
        for (int i4{0}; i4 < 4; i4++) {
            for (int i5{0}; i5 < b_loop_ub; i5++) {
                p5_2D[i5 + p5_2D.size(0) * i4] = p5_1D[i5 + p5_1D.size(0) * i4] *
                                                 static_cast<double>(b_b[i5 + b_b.size(0) * i4]);
            }
        }
    } else {
        b_binary_expand_op(p5_2D, p5_1D, b_b);
    }
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    c_b.set_size(p5_2D.size(0), 3);
    if (p5_2D.size(0) != 0) {
        int i6;
        i6 = p5_2D.size(0) - 1;
        for (int c_k{0}; c_k < 3; c_k++) {
            for (int c_t{0}; c_t <= i6; c_t++) {
                c_b[c_t + c_b.size(0) * c_k] = static_cast<signed char>(3 - c_k);
            }
        }
    }
    if (p5_2D.size(0) == c_b.size(0)) {
        int c_loop_ub;
        c_loop_ub = p5_2D.size(0);
        p5_3D.set_size(p5_2D.size(0), 3);
        for (int i7{0}; i7 < 3; i7++) {
            for (int i8{0}; i8 < c_loop_ub; i8++) {
                p5_3D[i8 + p5_3D.size(0) * i7] = p5_2D[i8 + p5_2D.size(0) * i7] *
                                                 static_cast<double>(c_b[i8 + c_b.size(0) * i7]);
            }
        }
    } else {
        binary_expand_op(p5_3D, p5_2D, c_b);
    }
    //
    // 'EvalTransP5:13' D0 = mypolyval(p5,    u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D0.set_size(CurvStruct_CoeffP5.size(0), u_vec.size(1));
    if ((CurvStruct_CoeffP5.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i9;
        i9 = u_vec.size(1) - 1;
        for (int d_t{0}; d_t <= i9; d_t++) {
            int na;
            na = CurvStruct_CoeffP5.size(0) - 1;
            for (int d_k{0}; d_k <= na; d_k++) {
                D0[d_k + D0.size(0) * d_t] = CurvStruct_CoeffP5[d_k];
            }
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int b_i{0}; b_i < 5; b_i++) {
        int i12;
        int i13;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d_b.set_size(CurvStruct_CoeffP5.size(0), u_vec.size(1));
        if ((CurvStruct_CoeffP5.size(0) != 0) && (u_vec.size(1) != 0)) {
            int b_na;
            b_na = u_vec.size(1);
            for (int e_k{0}; e_k < b_na; e_k++) {
                int i11;
                i11 = CurvStruct_CoeffP5.size(0) - 1;
                for (int f_t{0}; f_t <= i11; f_t++) {
                    d_b[f_t + d_b.size(0) * e_k] = u_vec[e_k];
                }
            }
        }
        e_b.set_size(CurvStruct_CoeffP5.size(0), u_vec.size(1));
        if ((CurvStruct_CoeffP5.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i10;
            i10 = u_vec.size(1) - 1;
            for (int e_t{0}; e_t <= i10; e_t++) {
                int c_na;
                c_na = CurvStruct_CoeffP5.size(0) - 1;
                for (int f_k{0}; f_k <= c_na; f_k++) {
                    e_b[f_k + e_b.size(0) * e_t] =
                        CurvStruct_CoeffP5[f_k + CurvStruct_CoeffP5.size(0) * (b_i + 1)];
                }
            }
        }
        if (d_b.size(0) == 1) {
            i12 = D0.size(0);
        } else {
            i12 = d_b.size(0);
        }
        if (d_b.size(1) == 1) {
            i13 = D0.size(1);
        } else {
            i13 = d_b.size(1);
        }
        if ((d_b.size(0) == D0.size(0)) && (d_b.size(1) == D0.size(1)) && (i12 == e_b.size(0)) &&
            (i13 == e_b.size(1))) {
            int d_loop_ub;
            D0.set_size(d_b.size(0), d_b.size(1));
            d_loop_ub = d_b.size(1);
            for (int i15{0}; i15 < d_loop_ub; i15++) {
                int e_loop_ub;
                e_loop_ub = d_b.size(0);
                for (int i16{0}; i16 < e_loop_ub; i16++) {
                    D0[i16 + D0.size(0) * i15] =
                        d_b[i16 + d_b.size(0) * i15] * D0[i16 + D0.size(0) * i15] +
                        e_b[i16 + e_b.size(0) * i15];
                }
            }
        } else {
            binary_expand_op(D0, d_b, e_b);
        }
    }
    // 'EvalTransP5:14' D1 = mypolyval(p5_1D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D1.set_size(p5_1D.size(0), u_vec.size(1));
    if ((p5_1D.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i14;
        i14 = u_vec.size(1) - 1;
        for (int g_t{0}; g_t <= i14; g_t++) {
            int d_na;
            d_na = p5_1D.size(0) - 1;
            for (int g_k{0}; g_k <= d_na; g_k++) {
                D1[g_k + D1.size(0) * g_t] = p5_1D[g_k];
            }
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int c_i{0}; c_i < 4; c_i++) {
        int i19;
        int i20;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d_b.set_size(p5_1D.size(0), u_vec.size(1));
        if ((p5_1D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int e_na;
            e_na = u_vec.size(1);
            for (int h_k{0}; h_k < e_na; h_k++) {
                int i18;
                i18 = p5_1D.size(0) - 1;
                for (int i_t{0}; i_t <= i18; i_t++) {
                    d_b[i_t + d_b.size(0) * h_k] = u_vec[h_k];
                }
            }
        }
        e_b.set_size(p5_1D.size(0), u_vec.size(1));
        if ((p5_1D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i17;
            i17 = u_vec.size(1) - 1;
            for (int h_t{0}; h_t <= i17; h_t++) {
                int f_na;
                f_na = p5_1D.size(0) - 1;
                for (int i_k{0}; i_k <= f_na; i_k++) {
                    e_b[i_k + e_b.size(0) * h_t] = p5_1D[i_k + p5_1D.size(0) * (c_i + 1)];
                }
            }
        }
        if (d_b.size(0) == 1) {
            i19 = D1.size(0);
        } else {
            i19 = d_b.size(0);
        }
        if (d_b.size(1) == 1) {
            i20 = D1.size(1);
        } else {
            i20 = d_b.size(1);
        }
        if ((d_b.size(0) == D1.size(0)) && (d_b.size(1) == D1.size(1)) && (i19 == e_b.size(0)) &&
            (i20 == e_b.size(1))) {
            int f_loop_ub;
            D1.set_size(d_b.size(0), d_b.size(1));
            f_loop_ub = d_b.size(1);
            for (int i22{0}; i22 < f_loop_ub; i22++) {
                int g_loop_ub;
                g_loop_ub = d_b.size(0);
                for (int i23{0}; i23 < g_loop_ub; i23++) {
                    D1[i23 + D1.size(0) * i22] =
                        d_b[i23 + d_b.size(0) * i22] * D1[i23 + D1.size(0) * i22] +
                        e_b[i23 + e_b.size(0) * i22];
                }
            }
        } else {
            binary_expand_op(D1, d_b, e_b);
        }
    }
    // 'EvalTransP5:15' D2 = mypolyval(p5_2D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D2.set_size(p5_2D.size(0), u_vec.size(1));
    if ((p5_2D.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i21;
        i21 = u_vec.size(1) - 1;
        for (int j_t{0}; j_t <= i21; j_t++) {
            int g_na;
            g_na = p5_2D.size(0) - 1;
            for (int j_k{0}; j_k <= g_na; j_k++) {
                D2[j_k + D2.size(0) * j_t] = p5_2D[j_k];
            }
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int d_i{0}; d_i < 3; d_i++) {
        int i26;
        int i27;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d_b.set_size(p5_2D.size(0), u_vec.size(1));
        if ((p5_2D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int h_na;
            h_na = u_vec.size(1);
            for (int k_k{0}; k_k < h_na; k_k++) {
                int i25;
                i25 = p5_2D.size(0) - 1;
                for (int l_t{0}; l_t <= i25; l_t++) {
                    d_b[l_t + d_b.size(0) * k_k] = u_vec[k_k];
                }
            }
        }
        e_b.set_size(p5_2D.size(0), u_vec.size(1));
        if ((p5_2D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i24;
            i24 = u_vec.size(1) - 1;
            for (int k_t{0}; k_t <= i24; k_t++) {
                int i_na;
                i_na = p5_2D.size(0) - 1;
                for (int l_k{0}; l_k <= i_na; l_k++) {
                    e_b[l_k + e_b.size(0) * k_t] = p5_2D[l_k + p5_2D.size(0) * (d_i + 1)];
                }
            }
        }
        if (d_b.size(0) == 1) {
            i26 = D2.size(0);
        } else {
            i26 = d_b.size(0);
        }
        if (d_b.size(1) == 1) {
            i27 = D2.size(1);
        } else {
            i27 = d_b.size(1);
        }
        if ((d_b.size(0) == D2.size(0)) && (d_b.size(1) == D2.size(1)) && (i26 == e_b.size(0)) &&
            (i27 == e_b.size(1))) {
            int h_loop_ub;
            D2.set_size(d_b.size(0), d_b.size(1));
            h_loop_ub = d_b.size(1);
            for (int i29{0}; i29 < h_loop_ub; i29++) {
                int j_loop_ub;
                j_loop_ub = d_b.size(0);
                for (int i30{0}; i30 < j_loop_ub; i30++) {
                    D2[i30 + D2.size(0) * i29] =
                        d_b[i30 + d_b.size(0) * i29] * D2[i30 + D2.size(0) * i29] +
                        e_b[i30 + e_b.size(0) * i29];
                }
            }
        } else {
            binary_expand_op(D2, d_b, e_b);
        }
    }
    // 'EvalTransP5:16' D3 = mypolyval(p5_3D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D3.set_size(p5_3D.size(0), u_vec.size(1));
    if ((p5_3D.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i28;
        i28 = u_vec.size(1) - 1;
        for (int m_t{0}; m_t <= i28; m_t++) {
            int j_na;
            j_na = p5_3D.size(0) - 1;
            for (int m_k{0}; m_k <= j_na; m_k++) {
                D3[m_k + D3.size(0) * m_t] = p5_3D[m_k];
            }
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int e_i{0}; e_i < 2; e_i++) {
        int i35;
        int i36;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        d_b.set_size(p5_3D.size(0), u_vec.size(1));
        if ((p5_3D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int k_na;
            k_na = u_vec.size(1);
            for (int n_k{0}; n_k < k_na; n_k++) {
                int i33;
                i33 = p5_3D.size(0) - 1;
                for (int o_t{0}; o_t <= i33; o_t++) {
                    d_b[o_t + d_b.size(0) * n_k] = u_vec[n_k];
                }
            }
        }
        e_b.set_size(p5_3D.size(0), u_vec.size(1));
        if ((p5_3D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i32;
            i32 = u_vec.size(1) - 1;
            for (int n_t{0}; n_t <= i32; n_t++) {
                int l_na;
                l_na = p5_3D.size(0) - 1;
                for (int o_k{0}; o_k <= l_na; o_k++) {
                    e_b[o_k + e_b.size(0) * n_t] = p5_3D[o_k + p5_3D.size(0) * (e_i + 1)];
                }
            }
        }
        if (d_b.size(0) == 1) {
            i35 = D3.size(0);
        } else {
            i35 = d_b.size(0);
        }
        if (d_b.size(1) == 1) {
            i36 = D3.size(1);
        } else {
            i36 = d_b.size(1);
        }
        if ((d_b.size(0) == D3.size(0)) && (d_b.size(1) == D3.size(1)) && (i35 == e_b.size(0)) &&
            (i36 == e_b.size(1))) {
            int n_loop_ub;
            D3.set_size(d_b.size(0), d_b.size(1));
            n_loop_ub = d_b.size(1);
            for (int i39{0}; i39 < n_loop_ub; i39++) {
                int p_loop_ub;
                p_loop_ub = d_b.size(0);
                for (int i40{0}; i40 < p_loop_ub; i40++) {
                    D3[i40 + D3.size(0) * i39] =
                        d_b[i40 + d_b.size(0) * i39] * D3[i40 + D3.size(0) * i39] +
                        e_b[i40 + e_b.size(0) * i39];
                }
            }
        } else {
            binary_expand_op(D3, d_b, e_b);
        }
    }
    // 'EvalTransP5:18' r_0D = D0(1:nAxis, :);
    if (1 > nAxis) {
        i_loop_ub = 0;
    } else {
        i_loop_ub = nAxis;
    }
    k_loop_ub = D0.size(1);
    r_0D.set_size(i_loop_ub, D0.size(1));
    for (int i31{0}; i31 < k_loop_ub; i31++) {
        for (int i34{0}; i34 < i_loop_ub; i34++) {
            r_0D[i34 + r_0D.size(0) * i31] = D0[i34 + D0.size(0) * i31];
        }
    }
    // 'EvalTransP5:19' r_1D = D1(1:nAxis, :);
    if (1 > nAxis) {
        l_loop_ub = 0;
    } else {
        l_loop_ub = nAxis;
    }
    m_loop_ub = D1.size(1);
    r_1D.set_size(l_loop_ub, D1.size(1));
    for (int i37{0}; i37 < m_loop_ub; i37++) {
        for (int i38{0}; i38 < l_loop_ub; i38++) {
            r_1D[i38 + r_1D.size(0) * i37] = D1[i38 + D1.size(0) * i37];
        }
    }
    // 'EvalTransP5:20' r_2D = D2(1:nAxis, :);
    if (1 > nAxis) {
        o_loop_ub = 0;
    } else {
        o_loop_ub = nAxis;
    }
    q_loop_ub = D2.size(1);
    r_2D.set_size(o_loop_ub, D2.size(1));
    for (int i41{0}; i41 < q_loop_ub; i41++) {
        for (int i42{0}; i42 < o_loop_ub; i42++) {
            r_2D[i42 + r_2D.size(0) * i41] = D2[i42 + D2.size(0) * i41];
        }
    }
    // 'EvalTransP5:21' r_3D = D3(1:nAxis, :);
    if (1 > nAxis) {
        r_loop_ub = 0;
    } else {
        r_loop_ub = nAxis;
    }
    s_loop_ub = D3.size(1);
    r_3D.set_size(r_loop_ub, D3.size(1));
    for (int i43{0}; i43 < s_loop_ub; i43++) {
        for (int i44{0}; i44 < r_loop_ub; i44++) {
            r_3D[i44 + r_3D.size(0) * i43] = D3[i44 + D3.size(0) * i43];
        }
    }
}

//
// function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec, nAxis)
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                double u_vec
//                int nAxis
//                ::coder::array<double, 1U> &r_0D
//                ::coder::array<double, 1U> &r_1D
//                ::coder::array<double, 1U> &r_2D
//                ::coder::array<double, 1U> &r_3D
// Return Type  : void
//
void EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, double u_vec, int nAxis,
                 ::coder::array<double, 1U> &r_0D, ::coder::array<double, 1U> &r_1D,
                 ::coder::array<double, 1U> &r_2D, ::coder::array<double, 1U> &r_3D)
{
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> p5_2D;
    ::coder::array<double, 2U> p5_3D;
    ::coder::array<double, 1U> D0;
    ::coder::array<double, 1U> D1;
    ::coder::array<double, 1U> D2;
    ::coder::array<double, 1U> D3;
    ::coder::array<double, 1U> r;
    ::coder::array<signed char, 2U> b;
    ::coder::array<signed char, 2U> b_b;
    ::coder::array<signed char, 2U> c_b;
    int b_outsize[2];
    int c_outsize[2];
    int d_outsize[2];
    int outsize[2];
    int d_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int j_loop_ub;
    int l_loop_ub;
    int m_loop_ub;
    int n_loop_ub;
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
    b.set_size(CurvStruct_CoeffP5.size(0), 5);
    if (CurvStruct_CoeffP5.size(0) != 0) {
        int i;
        i = CurvStruct_CoeffP5.size(0) - 1;
        for (int k{0}; k < 5; k++) {
            for (int t{0}; t <= i; t++) {
                b[t + b.size(0) * k] = static_cast<signed char>(5 - k);
            }
        }
    }
    if (CurvStruct_CoeffP5.size(0) == b.size(0)) {
        int loop_ub;
        loop_ub = CurvStruct_CoeffP5.size(0);
        p5_1D.set_size(CurvStruct_CoeffP5.size(0), 5);
        for (int i1{0}; i1 < 5; i1++) {
            for (int i2{0}; i2 < loop_ub; i2++) {
                p5_1D[i2 + p5_1D.size(0) * i1] =
                    CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1] *
                    static_cast<double>(b[i2 + b.size(0) * i1]);
            }
        }
    } else {
        c_binary_expand_op(p5_1D, CurvStruct_CoeffP5, b);
    }
    // 'EvalTransP5:10' p5_2D = mypolyder(p5_1D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    b_b.set_size(p5_1D.size(0), 4);
    if (p5_1D.size(0) != 0) {
        int i3;
        i3 = p5_1D.size(0) - 1;
        for (int b_k{0}; b_k < 4; b_k++) {
            for (int b_t{0}; b_t <= i3; b_t++) {
                b_b[b_t + b_b.size(0) * b_k] = static_cast<signed char>(4 - b_k);
            }
        }
    }
    if (p5_1D.size(0) == b_b.size(0)) {
        int b_loop_ub;
        b_loop_ub = p5_1D.size(0);
        p5_2D.set_size(p5_1D.size(0), 4);
        for (int i4{0}; i4 < 4; i4++) {
            for (int i5{0}; i5 < b_loop_ub; i5++) {
                p5_2D[i5 + p5_2D.size(0) * i4] = p5_1D[i5 + p5_1D.size(0) * i4] *
                                                 static_cast<double>(b_b[i5 + b_b.size(0) * i4]);
            }
        }
    } else {
        b_binary_expand_op(p5_2D, p5_1D, b_b);
    }
    // 'EvalTransP5:11' p5_3D = mypolyder(p5_2D);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    c_b.set_size(p5_2D.size(0), 3);
    if (p5_2D.size(0) != 0) {
        int i6;
        i6 = p5_2D.size(0) - 1;
        for (int c_k{0}; c_k < 3; c_k++) {
            for (int c_t{0}; c_t <= i6; c_t++) {
                c_b[c_t + c_b.size(0) * c_k] = static_cast<signed char>(3 - c_k);
            }
        }
    }
    if (p5_2D.size(0) == c_b.size(0)) {
        int c_loop_ub;
        c_loop_ub = p5_2D.size(0);
        p5_3D.set_size(p5_2D.size(0), 3);
        for (int i7{0}; i7 < 3; i7++) {
            for (int i8{0}; i8 < c_loop_ub; i8++) {
                p5_3D[i8 + p5_3D.size(0) * i7] = p5_2D[i8 + p5_2D.size(0) * i7] *
                                                 static_cast<double>(c_b[i8 + c_b.size(0) * i7]);
            }
        }
    } else {
        binary_expand_op(p5_3D, p5_2D, c_b);
    }
    //
    // 'EvalTransP5:13' D0 = mypolyval(p5,    u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D3.set_size(CurvStruct_CoeffP5.size(0));
    if (CurvStruct_CoeffP5.size(0) != 0) {
        int i9;
        i9 = CurvStruct_CoeffP5.size(0) - 1;
        for (int d_k{0}; d_k <= i9; d_k++) {
            D3[d_k] = CurvStruct_CoeffP5[d_k];
        }
    }
    D0.set_size(D3.size(0));
    d_loop_ub = D3.size(0);
    for (int i10{0}; i10 < d_loop_ub; i10++) {
        D0[i10] = D3[i10];
    }
    // 'mypolyval:12' for i=2:nc
    outsize[0] = CurvStruct_CoeffP5.size(0);
    for (int b_i{0}; b_i < 5; b_i++) {
        int e_loop_ub;
        int i12;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r.set_size(CurvStruct_CoeffP5.size(0));
        if (CurvStruct_CoeffP5.size(0) != 0) {
            int i11;
            i11 = CurvStruct_CoeffP5.size(0) - 1;
            for (int e_k{0}; e_k <= i11; e_k++) {
                r[e_k] = CurvStruct_CoeffP5[e_k + CurvStruct_CoeffP5.size(0) * (b_i + 1)];
            }
        }
        e_loop_ub = D0.size(0);
        if (CurvStruct_CoeffP5.size(0) == 1) {
            i12 = D0.size(0);
        } else {
            i12 = CurvStruct_CoeffP5.size(0);
        }
        if ((CurvStruct_CoeffP5.size(0) == D0.size(0)) && (i12 == r.size(0))) {
            for (int i13{0}; i13 < e_loop_ub; i13++) {
                D0[i13] = u_vec * D0[i13] + r[i13];
            }
        } else {
            binary_expand_op(D0, u_vec, outsize, r);
        }
    }
    // 'EvalTransP5:14' D1 = mypolyval(p5_1D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D3.set_size(p5_1D.size(0));
    if (p5_1D.size(0) != 0) {
        int i14;
        i14 = p5_1D.size(0) - 1;
        for (int f_k{0}; f_k <= i14; f_k++) {
            D3[f_k] = p5_1D[f_k];
        }
    }
    D1.set_size(D3.size(0));
    f_loop_ub = D3.size(0);
    for (int i15{0}; i15 < f_loop_ub; i15++) {
        D1[i15] = D3[i15];
    }
    // 'mypolyval:12' for i=2:nc
    b_outsize[0] = p5_1D.size(0);
    for (int c_i{0}; c_i < 4; c_i++) {
        int g_loop_ub;
        int i17;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r.set_size(p5_1D.size(0));
        if (p5_1D.size(0) != 0) {
            int i16;
            i16 = p5_1D.size(0) - 1;
            for (int g_k{0}; g_k <= i16; g_k++) {
                r[g_k] = p5_1D[g_k + p5_1D.size(0) * (c_i + 1)];
            }
        }
        g_loop_ub = D1.size(0);
        if (p5_1D.size(0) == 1) {
            i17 = D1.size(0);
        } else {
            i17 = p5_1D.size(0);
        }
        if ((p5_1D.size(0) == D1.size(0)) && (i17 == r.size(0))) {
            for (int i18{0}; i18 < g_loop_ub; i18++) {
                D1[i18] = u_vec * D1[i18] + r[i18];
            }
        } else {
            binary_expand_op(D1, u_vec, b_outsize, r);
        }
    }
    // 'EvalTransP5:15' D2 = mypolyval(p5_2D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D3.set_size(p5_2D.size(0));
    if (p5_2D.size(0) != 0) {
        int i19;
        i19 = p5_2D.size(0) - 1;
        for (int h_k{0}; h_k <= i19; h_k++) {
            D3[h_k] = p5_2D[h_k];
        }
    }
    D2.set_size(D3.size(0));
    h_loop_ub = D3.size(0);
    for (int i20{0}; i20 < h_loop_ub; i20++) {
        D2[i20] = D3[i20];
    }
    // 'mypolyval:12' for i=2:nc
    c_outsize[0] = p5_2D.size(0);
    for (int d_i{0}; d_i < 3; d_i++) {
        int i22;
        int i_loop_ub;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r.set_size(p5_2D.size(0));
        if (p5_2D.size(0) != 0) {
            int i21;
            i21 = p5_2D.size(0) - 1;
            for (int i_k{0}; i_k <= i21; i_k++) {
                r[i_k] = p5_2D[i_k + p5_2D.size(0) * (d_i + 1)];
            }
        }
        i_loop_ub = D2.size(0);
        if (p5_2D.size(0) == 1) {
            i22 = D2.size(0);
        } else {
            i22 = p5_2D.size(0);
        }
        if ((p5_2D.size(0) == D2.size(0)) && (i22 == r.size(0))) {
            for (int i23{0}; i23 < i_loop_ub; i23++) {
                D2[i23] = u_vec * D2[i23] + r[i23];
            }
        } else {
            binary_expand_op(D2, u_vec, c_outsize, r);
        }
    }
    // 'EvalTransP5:16' D3 = mypolyval(p5_3D, u_vec);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    D3.set_size(p5_3D.size(0));
    if (p5_3D.size(0) != 0) {
        int i24;
        i24 = p5_3D.size(0) - 1;
        for (int j_k{0}; j_k <= i24; j_k++) {
            D3[j_k] = p5_3D[j_k];
        }
    }
    // 'mypolyval:12' for i=2:nc
    d_outsize[0] = p5_3D.size(0);
    for (int e_i{0}; e_i < 2; e_i++) {
        int i27;
        int k_loop_ub;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r.set_size(p5_3D.size(0));
        if (p5_3D.size(0) != 0) {
            int i25;
            i25 = p5_3D.size(0) - 1;
            for (int k_k{0}; k_k <= i25; k_k++) {
                r[k_k] = p5_3D[k_k + p5_3D.size(0) * (e_i + 1)];
            }
        }
        k_loop_ub = D3.size(0);
        if (p5_3D.size(0) == 1) {
            i27 = D3.size(0);
        } else {
            i27 = p5_3D.size(0);
        }
        if ((p5_3D.size(0) == D3.size(0)) && (i27 == r.size(0))) {
            for (int i28{0}; i28 < k_loop_ub; i28++) {
                D3[i28] = u_vec * D3[i28] + r[i28];
            }
        } else {
            binary_expand_op(D3, u_vec, d_outsize, r);
        }
    }
    // 'EvalTransP5:18' r_0D = D0(1:nAxis, :);
    if (1 > nAxis) {
        j_loop_ub = 0;
    } else {
        j_loop_ub = nAxis;
    }
    r_0D.set_size(j_loop_ub);
    for (int i26{0}; i26 < j_loop_ub; i26++) {
        r_0D[i26] = D0[i26];
    }
    // 'EvalTransP5:19' r_1D = D1(1:nAxis, :);
    if (1 > nAxis) {
        l_loop_ub = 0;
    } else {
        l_loop_ub = nAxis;
    }
    r_1D.set_size(l_loop_ub);
    for (int i29{0}; i29 < l_loop_ub; i29++) {
        r_1D[i29] = D1[i29];
    }
    // 'EvalTransP5:20' r_2D = D2(1:nAxis, :);
    if (1 > nAxis) {
        m_loop_ub = 0;
    } else {
        m_loop_ub = nAxis;
    }
    r_2D.set_size(m_loop_ub);
    for (int i30{0}; i30 < m_loop_ub; i30++) {
        r_2D[i30] = D2[i30];
    }
    // 'EvalTransP5:21' r_3D = D3(1:nAxis, :);
    if (1 > nAxis) {
        n_loop_ub = 0;
    } else {
        n_loop_ub = nAxis;
    }
    r_3D.set_size(n_loop_ub);
    for (int i31{0}; i31 < n_loop_ub; i31++) {
        r_3D[i31] = D3[i31];
    }
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
