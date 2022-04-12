//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstrJerkWithSlacks.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:49:22
//

// Include Files
#include "BuildConstrJerkWithSlacks.h"
#include "BuildConstrJerk_v4.h"
#include "EvalCurvStruct.h"
#include "bsxfun.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [A, b] = BuildConstrJerkWithSlacks(ctx, CurvStructs, Coeff, jmax,  ...
//                                      BasisVal, BasisValD, BasisValDD, u_vec)
//
// Arguments    : const queue_coder *ctx_q_splines
//                const ::coder::array<CurvStruct, 2U> &CurvStructs
//                const ::coder::array<double, 2U> &Coeff
//                const double jmax[3]
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 2U> &u_vec
//                coder::sparse *A
//                ::coder::array<double, 1U> &b
// Return Type  : void
//
namespace ocn {
void BuildConstrJerkWithSlacks(const queue_coder *ctx_q_splines,
                               const ::coder::array<CurvStruct, 2U> &CurvStructs,
                               const ::coder::array<double, 2U> &Coeff, const double jmax[3],
                               const ::coder::array<double, 2U> &BasisVal,
                               const ::coder::array<double, 2U> &BasisValD,
                               const ::coder::array<double, 2U> &BasisValDD,
                               const ::coder::array<double, 2U> &u_vec, coder::sparse *A,
                               ::coder::array<double, 1U> &b)
{
    ::coder::array<double, 2U> R1;
    ::coder::array<double, 2U> R2;
    ::coder::array<double, 2U> R3;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> b_R1;
    ::coder::array<double, 2U> b_u_vec;
    ::coder::array<double, 2U> b_y;
    ::coder::array<double, 2U> c_u_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 2U> varargin_4;
    ::coder::array<double, 2U> varargin_6;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> b_r2D;
    ::coder::array<double, 1U> b_r3D;
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> y_tmp;
    double b_b;
    double d;
    int BasisVal_idx_0;
    int M;
    int N;
    int ab_loop_ub;
    int b_BasisVal_idx_0;
    int b_inner;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_mc;
    int bb_loop_ub;
    int c_BasisVal_idx_0;
    int c_input_sizes_idx_0;
    int c_loop_ub;
    int cb_loop_ub;
    int d_BasisVal_idx_0;
    int d_input_sizes_idx_0;
    int d_loop_ub;
    int db_loop_ub;
    int e_input_sizes_idx_0;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int g_loop_ub;
    int h_loop_ub;
    int i13;
    int i14;
    int i2;
    int i20;
    int i21;
    int i32;
    int i52;
    int i6;
    int i7;
    int i_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int mc;
    int n_loop_ub;
    int q_loop_ub;
    int result;
    int s_loop_ub;
    int u_loop_ub;
    int unnamed_idx_0;
    int y_loop_ub;
    bool empty_non_axis_sizes;
    // 'BuildConstrJerkWithSlacks:3' c_prof_block('BuildConstrJerk_v4');
    //  import splines.*
    //
    // 'BuildConstrJerkWithSlacks:6' Ncrv   = length(CurvStructs);
    // 'BuildConstrJerkWithSlacks:7' [M, N] = size(BasisVal);
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    //
    // 'BuildConstrJerkWithSlacks:9' A      = sparse(6*M*Ncrv + 1,   N*Ncrv + 1);
    coder::b_sparse(
        6.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size(1)) +
            1.0,
        static_cast<double>(BasisVal.size(1)) * static_cast<double>(CurvStructs.size(1)) + 1.0, A);
    //  preallocation
    // 'BuildConstrJerkWithSlacks:10' b      = zeros(6*M*Ncrv + 1,   1);
    unnamed_idx_0 = static_cast<int>(6.0 * static_cast<double>(BasisVal.size(0)) *
                                         static_cast<double>(CurvStructs.size(1)) +
                                     1.0);
    b.set_size(unnamed_idx_0);
    for (int i{0}; i < unnamed_idx_0; i++) {
        b[i] = 0.0;
    }
    //  preallocation
    //  coder.varsize('A', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz,
    //  FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); coder.varsize('b',
    //  [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
    //
    //  q_opt  = Function(Bl, Coeff(:, 1));
    //  q_val  = q_opt.fast_eval(u_vec);
    // 'BuildConstrJerkWithSlacks:18' q_val = BasisVal*Coeff(:,1);
    // 'BuildConstrJerkWithSlacks:20' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(1),
    // u_vec);
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i1{0}; i1 <= loop_ub; i1++) {
        b_u_vec[i1] = u_vec[i1];
    }
    b_EvalCurvStruct(ctx_q_splines, &CurvStructs[0], b_u_vec, a__1, r1D, r2D, r3D);
    //
    // 'BuildConstrJerkWithSlacks:22' R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)') +
    // ... 'BuildConstrJerkWithSlacks:23'       1.5*bsxfun(@times, BasisValD , r2D(1, :)') + ...
    // 'BuildConstrJerkWithSlacks:24'       0.5*bsxfun(@times, BasisValDD,r1D(1, :)')) ,
    // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x);
    mc = BasisVal.size(0) - 1;
    inner = BasisVal.size(1);
    y_tmp.set_size(BasisVal.size(0));
    for (int b_i{0}; b_i <= mc; b_i++) {
        y_tmp[b_i] = 0.0;
    }
    for (int k{0}; k < inner; k++) {
        for (int c_i{0}; c_i <= mc; c_i++) {
            y_tmp[c_i] = y_tmp[c_i] + BasisVal[c_i + BasisVal.size(0) * k] * Coeff[k];
        }
    }
    i2 = y_tmp.size(0);
    for (int b_k{0}; b_k < i2; b_k++) {
        y_tmp[b_k] = std::sqrt(y_tmp[b_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    b_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        b_r3D[i3] = r3D[3 * i3];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    c_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        b_r2D[i4] = r2D[3 * i4];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    d_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        b_r1D[i5] = r1D[3 * i5];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    if (r.size(0) == 1) {
        i6 = r1.size(0);
    } else {
        i6 = r.size(0);
    }
    if (r.size(1) == 1) {
        i7 = r1.size(1);
    } else {
        i7 = r.size(1);
    }
    if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i6 == r2.size(0)) &&
        (i7 == r2.size(1))) {
        int e_loop_ub;
        e_loop_ub = r.size(1);
        for (int i8{0}; i8 < e_loop_ub; i8++) {
            int f_loop_ub;
            f_loop_ub = r.size(0);
            for (int i9{0}; i9 < f_loop_ub; i9++) {
                r[i9 + r.size(0) * i8] = (r[i9 + r.size(0) * i8] + 1.5 * r1[i9 + r1.size(0) * i8]) +
                                         0.5 * r2[i9 + r2.size(0) * i8];
            }
        }
        coder::bsxfun(r, y_tmp, R1);
    } else {
        binary_expand_op(R1, r, r1, r2, y_tmp);
    }
    // 'BuildConstrJerkWithSlacks:26' R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)') +
    // ... 'BuildConstrJerkWithSlacks:27'   1.5*bsxfun(@times, BasisValD , r2D(2, :)') + ...
    // 'BuildConstrJerkWithSlacks:28'   0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) , mysqrt(q_val));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    g_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        b_r3D[i10] = r3D[3 * i10 + 1];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    h_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        b_r2D[i11] = r2D[3 * i11 + 1];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    i_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        b_r1D[i12] = r1D[3 * i12 + 1];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    if (r.size(0) == 1) {
        i13 = r1.size(0);
    } else {
        i13 = r.size(0);
    }
    if (r.size(1) == 1) {
        i14 = r1.size(1);
    } else {
        i14 = r.size(1);
    }
    if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i13 == r2.size(0)) &&
        (i14 == r2.size(1))) {
        int j_loop_ub;
        j_loop_ub = r.size(1);
        for (int i15{0}; i15 < j_loop_ub; i15++) {
            int k_loop_ub;
            k_loop_ub = r.size(0);
            for (int i16{0}; i16 < k_loop_ub; i16++) {
                r[i16 + r.size(0) * i15] =
                    (r[i16 + r.size(0) * i15] + 1.5 * r1[i16 + r1.size(0) * i15]) +
                    0.5 * r2[i16 + r2.size(0) * i15];
            }
        }
        coder::bsxfun(r, y_tmp, R2);
    } else {
        binary_expand_op(R2, r, r1, r2, y_tmp);
    }
    // 'BuildConstrJerkWithSlacks:30' R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)') +
    // ... 'BuildConstrJerkWithSlacks:31'   1.5*bsxfun(@times, BasisValD , r2D(3, :)') + ...
    // 'BuildConstrJerkWithSlacks:32'   0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) , mysqrt(q_val));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    l_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i17{0}; i17 < l_loop_ub; i17++) {
        b_r3D[i17] = r3D[3 * i17 + 2];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    m_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i18{0}; i18 < m_loop_ub; i18++) {
        b_r2D[i18] = r2D[3 * i18 + 2];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    n_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i19{0}; i19 < n_loop_ub; i19++) {
        b_r1D[i19] = r1D[3 * i19 + 2];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    if (r.size(0) == 1) {
        i20 = r1.size(0);
    } else {
        i20 = r.size(0);
    }
    if (r.size(1) == 1) {
        i21 = r1.size(1);
    } else {
        i21 = r.size(1);
    }
    if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i20 == r2.size(0)) &&
        (i21 == r2.size(1))) {
        int o_loop_ub;
        o_loop_ub = r.size(1);
        for (int i22{0}; i22 < o_loop_ub; i22++) {
            int p_loop_ub;
            p_loop_ub = r.size(0);
            for (int i23{0}; i23 < p_loop_ub; i23++) {
                r[i23 + r.size(0) * i22] =
                    (r[i23 + r.size(0) * i22] + 1.5 * r1[i23 + r1.size(0) * i22]) +
                    0.5 * r2[i23 + r2.size(0) * i22];
            }
        }
        coder::bsxfun(r, y_tmp, R3);
    } else {
        binary_expand_op(R3, r, r1, r2, y_tmp);
    }
    //  R2 = (BasisVal .* r3D(2, :)' + ...
    //        1.5*BasisValD .* r2D(2, :)' + ...
    //        0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
    //  R3 = (BasisVal .* r3D(3, :)' + ...
    //        1.5*BasisValD .* r2D(3, :)' + ...
    //        0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
    //
    // 'BuildConstrJerkWithSlacks:40' A(1:6*M, 1:N)  = [R1;
    // 'BuildConstrJerkWithSlacks:41'                  -R1;
    // 'BuildConstrJerkWithSlacks:42'                   R2;
    // 'BuildConstrJerkWithSlacks:43'                  -R2;
    // 'BuildConstrJerkWithSlacks:44'                   R3;
    // 'BuildConstrJerkWithSlacks:45'                  -R3];
    varargin_2.set_size(R1.size(0), R1.size(1));
    q_loop_ub = R1.size(1);
    for (int i24{0}; i24 < q_loop_ub; i24++) {
        int r_loop_ub;
        r_loop_ub = R1.size(0);
        for (int i25{0}; i25 < r_loop_ub; i25++) {
            varargin_2[i25 + varargin_2.size(0) * i24] = -R1[i25 + R1.size(0) * i24];
        }
    }
    varargin_4.set_size(R2.size(0), R2.size(1));
    s_loop_ub = R2.size(1);
    for (int i26{0}; i26 < s_loop_ub; i26++) {
        int t_loop_ub;
        t_loop_ub = R2.size(0);
        for (int i27{0}; i27 < t_loop_ub; i27++) {
            varargin_4[i27 + varargin_4.size(0) * i26] = -R2[i27 + R2.size(0) * i26];
        }
    }
    varargin_6.set_size(R3.size(0), R3.size(1));
    u_loop_ub = R3.size(1);
    for (int i28{0}; i28 < u_loop_ub; i28++) {
        int v_loop_ub;
        v_loop_ub = R3.size(0);
        for (int i29{0}; i29 < v_loop_ub; i29++) {
            varargin_6[i29 + varargin_6.size(0) * i28] = -R3[i29 + R3.size(0) * i28];
        }
    }
    if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
        result = R1.size(1);
    } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
        result = varargin_2.size(1);
    } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
        result = R2.size(1);
    } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
        result = varargin_4.size(1);
    } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
        result = R3.size(1);
    } else if ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0)) {
        result = varargin_6.size(1);
    } else {
        result = R1.size(1);
        if (varargin_2.size(1) > R1.size(1)) {
            result = varargin_2.size(1);
        }
        if (R2.size(1) > result) {
            result = R2.size(1);
        }
        if (varargin_4.size(1) > result) {
            result = varargin_4.size(1);
        }
        if (R3.size(1) > result) {
            result = R3.size(1);
        }
        if (varargin_6.size(1) > result) {
            result = varargin_6.size(1);
        }
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
        input_sizes_idx_0 = R1.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
        b_input_sizes_idx_0 = varargin_2.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
        c_input_sizes_idx_0 = R2.size(0);
    } else {
        c_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
        d_input_sizes_idx_0 = varargin_4.size(0);
    } else {
        d_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
        e_input_sizes_idx_0 = R3.size(0);
    } else {
        e_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0))) {
        f_input_sizes_idx_0 = varargin_6.size(0);
    } else {
        f_input_sizes_idx_0 = 0;
    }
    b_b = 6.0 * static_cast<double>(BasisVal.size(0));
    if (b_b < 1.0) {
        y.set_size(1, 0);
    } else {
        int w_loop_ub;
        y.set_size(1, static_cast<int>(b_b - 1.0) + 1);
        w_loop_ub = static_cast<int>(b_b - 1.0);
        for (int i30{0}; i30 <= w_loop_ub; i30++) {
            y[i30] = static_cast<double>(i30) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int x_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        x_loop_ub = BasisVal.size(1) - 1;
        for (int i31{0}; i31 <= x_loop_ub; i31++) {
            b_y[i31] = static_cast<double>(i31) + 1.0;
        }
    }
    g_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    i32 = g_input_sizes_idx_0 + input_sizes_idx_0;
    b_R1.set_size((((i32 + b_input_sizes_idx_0) + c_input_sizes_idx_0) + e_input_sizes_idx_0) +
                      f_input_sizes_idx_0,
                  result);
    for (int i33{0}; i33 < result; i33++) {
        for (int i35{0}; i35 < g_input_sizes_idx_0; i35++) {
            b_R1[i35 + b_R1.size(0) * i33] = R1[i35 + g_input_sizes_idx_0 * i33];
        }
    }
    for (int i34{0}; i34 < result; i34++) {
        for (int i37{0}; i37 < input_sizes_idx_0; i37++) {
            b_R1[(i37 + g_input_sizes_idx_0) + b_R1.size(0) * i34] =
                varargin_2[i37 + input_sizes_idx_0 * i34];
        }
    }
    for (int i36{0}; i36 < result; i36++) {
        for (int i39{0}; i39 < b_input_sizes_idx_0; i39++) {
            b_R1[((i39 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_R1.size(0) * i36] =
                R2[i39 + b_input_sizes_idx_0 * i36];
        }
    }
    for (int i38{0}; i38 < result; i38++) {
        for (int i41{0}; i41 < c_input_sizes_idx_0; i41++) {
            b_R1[(((i41 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                 b_R1.size(0) * i38] = varargin_4[i41 + c_input_sizes_idx_0 * i38];
        }
    }
    for (int i40{0}; i40 < result; i40++) {
        for (int i43{0}; i43 < e_input_sizes_idx_0; i43++) {
            b_R1[((((i43 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                  c_input_sizes_idx_0) +
                 b_R1.size(0) * i40] = R3[i43 + e_input_sizes_idx_0 * i40];
        }
    }
    for (int i42{0}; i42 < result; i42++) {
        for (int i44{0}; i44 < f_input_sizes_idx_0; i44++) {
            b_R1[((((i44 + i32) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                  e_input_sizes_idx_0) +
                 b_R1.size(0) * i42] = varargin_6[i44 + f_input_sizes_idx_0 * i42];
        }
    }
    A->parenAssign(b_R1, y, b_y);
    //
    // 'BuildConstrJerkWithSlacks:47' bC2 = jmax(1)*ones(M, 1);
    // 'BuildConstrJerkWithSlacks:48' bC3 = jmax(2)*ones(M, 1);
    // 'BuildConstrJerkWithSlacks:49' bC4 = jmax(3)*ones(M, 1);
    //
    // 'BuildConstrJerkWithSlacks:51' b(1:6*M)       = [bC2;
    // 'BuildConstrJerkWithSlacks:52'                   bC2;
    // 'BuildConstrJerkWithSlacks:53'                   bC3;
    // 'BuildConstrJerkWithSlacks:54'                   bC3;
    // 'BuildConstrJerkWithSlacks:55'                   bC4;
    // 'BuildConstrJerkWithSlacks:56'                   bC4];
    d = 6.0 * static_cast<double>(BasisVal.size(0));
    BasisVal_idx_0 = BasisVal.size(0);
    b_BasisVal_idx_0 = BasisVal.size(0);
    c_BasisVal_idx_0 = BasisVal.size(0);
    d_BasisVal_idx_0 = BasisVal.size(0);
    r3.set_size(((((BasisVal.size(0) + BasisVal.size(0)) + BasisVal.size(0)) + BasisVal.size(0)) +
                 BasisVal.size(0)) +
                BasisVal.size(0));
    y_loop_ub = BasisVal.size(0);
    for (int i45{0}; i45 < y_loop_ub; i45++) {
        r3[i45] = jmax[0];
    }
    ab_loop_ub = BasisVal.size(0);
    for (int i46{0}; i46 < ab_loop_ub; i46++) {
        r3[i46 + BasisVal_idx_0] = jmax[0];
    }
    bb_loop_ub = BasisVal.size(0);
    for (int i47{0}; i47 < bb_loop_ub; i47++) {
        r3[(i47 + BasisVal_idx_0) + b_BasisVal_idx_0] = jmax[1];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i48{0}; i48 < cb_loop_ub; i48++) {
        r3[((i48 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0] = jmax[1];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i49{0}; i49 < db_loop_ub; i49++) {
        r3[(((i49 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0] =
            jmax[2];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i50{0}; i50 < eb_loop_ub; i50++) {
        r3[((((i50 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0) +
           BasisVal.size(0)] = jmax[2];
    }
    if (1.0 > d) {
        fb_loop_ub = 0;
    } else {
        fb_loop_ub = static_cast<int>(d);
    }
    for (int i51{0}; i51 < fb_loop_ub; i51++) {
        b[i51] = r3[i51];
    }
    //
    // 'BuildConstrJerkWithSlacks:58' for k = 1:Ncrv-1
    i52 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_mc = BasisVal.size(0) - 1;
        b_inner = BasisVal.size(1);
    }
    for (int c_k{0}; c_k <= i52 - 2; c_k++) {
        double a;
        double a_tmp;
        double b_tmp;
        double c_b;
        int ac_loop_ub;
        int b_result;
        int cc_loop_ub;
        int gb_loop_ub;
        int gc_loop_ub;
        int h_input_sizes_idx_0;
        int i55;
        int i59;
        int i60;
        int i66;
        int i67;
        int i73;
        int i74;
        int i97;
        int i98;
        int i_input_sizes_idx_0;
        int ib_loop_ub;
        int j_input_sizes_idx_0;
        int jb_loop_ub;
        int k_input_sizes_idx_0;
        int kb_loop_ub;
        int l_input_sizes_idx_0;
        int m_input_sizes_idx_0;
        int nb_loop_ub;
        int ob_loop_ub;
        int pb_loop_ub;
        int sb_loop_ub;
        int tb_loop_ub;
        int ub_loop_ub;
        int xb_loop_ub;
        bool b_empty_non_axis_sizes;
        // 'BuildConstrJerkWithSlacks:59' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(k+1),
        // u_vec);
        c_u_vec.set_size(1, u_vec.size(1));
        gb_loop_ub = u_vec.size(1) - 1;
        for (int i53{0}; i53 <= gb_loop_ub; i53++) {
            c_u_vec[i53] = u_vec[i53];
        }
        b_EvalCurvStruct(ctx_q_splines, &CurvStructs[c_k + 1], c_u_vec, a__2, r1D, r2D, r3D);
        //
        //      q_opt  = Function(Bl, Coeff(:, k+1));
        //      q_val  = q_opt.fast_eval(u_vec);
        // 'BuildConstrJerkWithSlacks:63' q_val = BasisVal*Coeff(:, k+1);
        //
        // 'BuildConstrJerkWithSlacks:65' R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)')
        // + ... 'BuildConstrJerkWithSlacks:66'           1.5*bsxfun(@times, BasisValD , r2D(1, :)')
        // + ... 'BuildConstrJerkWithSlacks:67'           0.5*bsxfun(@times, BasisValDD,r1D(1, :)'))
        // , mysqrt(q_val)); 'mysqrt:3' y = sqrt(x);
        y_tmp.set_size(BasisVal.size(0));
        for (int d_i{0}; d_i <= b_mc; d_i++) {
            y_tmp[d_i] = 0.0;
        }
        for (int d_k{0}; d_k < b_inner; d_k++) {
            for (int e_i{0}; e_i <= b_mc; e_i++) {
                y_tmp[e_i] = y_tmp[e_i] + BasisVal[e_i + BasisVal.size(0) * d_k] *
                                              Coeff[d_k + Coeff.size(0) * (c_k + 1)];
            }
        }
        i55 = y_tmp.size(0);
        for (int e_k{0}; e_k < i55; e_k++) {
            y_tmp[e_k] = std::sqrt(y_tmp[e_k]);
        }
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        ib_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i56{0}; i56 < ib_loop_ub; i56++) {
            b_r3D[i56] = r3D[3 * i56];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        jb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i57{0}; i57 < jb_loop_ub; i57++) {
            b_r2D[i57] = r2D[3 * i57];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        kb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i58{0}; i58 < kb_loop_ub; i58++) {
            b_r1D[i58] = r1D[3 * i58];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        if (r.size(0) == 1) {
            i59 = r1.size(0);
        } else {
            i59 = r.size(0);
        }
        if (r.size(1) == 1) {
            i60 = r1.size(1);
        } else {
            i60 = r.size(1);
        }
        if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i59 == r2.size(0)) &&
            (i60 == r2.size(1))) {
            int lb_loop_ub;
            lb_loop_ub = r.size(1);
            for (int i61{0}; i61 < lb_loop_ub; i61++) {
                int mb_loop_ub;
                mb_loop_ub = r.size(0);
                for (int i62{0}; i62 < mb_loop_ub; i62++) {
                    r[i62 + r.size(0) * i61] =
                        (r[i62 + r.size(0) * i61] + 1.5 * r1[i62 + r1.size(0) * i61]) +
                        0.5 * r2[i62 + r2.size(0) * i61];
                }
            }
            coder::bsxfun(r, y_tmp, R1);
        } else {
            binary_expand_op(R1, r, r1, r2, y_tmp);
        }
        // 'BuildConstrJerkWithSlacks:69' R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)')
        // + ... 'BuildConstrJerkWithSlacks:70'       1.5*bsxfun(@times, BasisValD , r2D(2, :)') +
        // ... 'BuildConstrJerkWithSlacks:71'       0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) ,
        // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x); 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        nb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i63{0}; i63 < nb_loop_ub; i63++) {
            b_r3D[i63] = r3D[3 * i63 + 1];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        ob_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i64{0}; i64 < ob_loop_ub; i64++) {
            b_r2D[i64] = r2D[3 * i64 + 1];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        pb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i65{0}; i65 < pb_loop_ub; i65++) {
            b_r1D[i65] = r1D[3 * i65 + 1];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        if (r.size(0) == 1) {
            i66 = r1.size(0);
        } else {
            i66 = r.size(0);
        }
        if (r.size(1) == 1) {
            i67 = r1.size(1);
        } else {
            i67 = r.size(1);
        }
        if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i66 == r2.size(0)) &&
            (i67 == r2.size(1))) {
            int qb_loop_ub;
            qb_loop_ub = r.size(1);
            for (int i68{0}; i68 < qb_loop_ub; i68++) {
                int rb_loop_ub;
                rb_loop_ub = r.size(0);
                for (int i69{0}; i69 < rb_loop_ub; i69++) {
                    r[i69 + r.size(0) * i68] =
                        (r[i69 + r.size(0) * i68] + 1.5 * r1[i69 + r1.size(0) * i68]) +
                        0.5 * r2[i69 + r2.size(0) * i68];
                }
            }
            coder::bsxfun(r, y_tmp, R2);
        } else {
            binary_expand_op(R2, r, r1, r2, y_tmp);
        }
        // 'BuildConstrJerkWithSlacks:73' R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)')
        // + ... 'BuildConstrJerkWithSlacks:74'       1.5*bsxfun(@times, BasisValD , r2D(3, :)') +
        // ... 'BuildConstrJerkWithSlacks:75'       0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) ,
        // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x); 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        sb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i70{0}; i70 < sb_loop_ub; i70++) {
            b_r3D[i70] = r3D[3 * i70 + 2];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        tb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i71{0}; i71 < tb_loop_ub; i71++) {
            b_r2D[i71] = r2D[3 * i71 + 2];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        ub_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i72{0}; i72 < ub_loop_ub; i72++) {
            b_r1D[i72] = r1D[3 * i72 + 2];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        if (r.size(0) == 1) {
            i73 = r1.size(0);
        } else {
            i73 = r.size(0);
        }
        if (r.size(1) == 1) {
            i74 = r1.size(1);
        } else {
            i74 = r.size(1);
        }
        if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) && (i73 == r2.size(0)) &&
            (i74 == r2.size(1))) {
            int vb_loop_ub;
            vb_loop_ub = r.size(1);
            for (int i75{0}; i75 < vb_loop_ub; i75++) {
                int wb_loop_ub;
                wb_loop_ub = r.size(0);
                for (int i76{0}; i76 < wb_loop_ub; i76++) {
                    r[i76 + r.size(0) * i75] =
                        (r[i76 + r.size(0) * i75] + 1.5 * r1[i76 + r1.size(0) * i75]) +
                        0.5 * r2[i76 + r2.size(0) * i75];
                }
            }
            coder::bsxfun(r, y_tmp, R3);
        } else {
            binary_expand_op(R3, r, r1, r2, y_tmp);
        }
        //      R2 = (BasisVal .* r3D(2, :)' + ...
        //            1.5*BasisValD .* r2D(2, :)' + ...
        //            0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
        //      R3 = (BasisVal .* r3D(3, :)' + ...
        //            1.5*BasisValD .* r2D(3, :)' + ...
        //            0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
        //
        // 'BuildConstrJerkWithSlacks:83' A(k*6*M+1:(k+1)*6*M, k*N+1:(k+1)*N) = ...
        // 'BuildConstrJerkWithSlacks:84'       [R1;
        // 'BuildConstrJerkWithSlacks:85'       -R1;
        // 'BuildConstrJerkWithSlacks:86'        R2;
        // 'BuildConstrJerkWithSlacks:87'       -R2;
        // 'BuildConstrJerkWithSlacks:88'        R3;
        // 'BuildConstrJerkWithSlacks:89'       -R3];
        varargin_2.set_size(R1.size(0), R1.size(1));
        xb_loop_ub = R1.size(1);
        for (int i77{0}; i77 < xb_loop_ub; i77++) {
            int yb_loop_ub;
            yb_loop_ub = R1.size(0);
            for (int i78{0}; i78 < yb_loop_ub; i78++) {
                varargin_2[i78 + varargin_2.size(0) * i77] = -R1[i78 + R1.size(0) * i77];
            }
        }
        varargin_4.set_size(R2.size(0), R2.size(1));
        ac_loop_ub = R2.size(1);
        for (int i79{0}; i79 < ac_loop_ub; i79++) {
            int bc_loop_ub;
            bc_loop_ub = R2.size(0);
            for (int i80{0}; i80 < bc_loop_ub; i80++) {
                varargin_4[i80 + varargin_4.size(0) * i79] = -R2[i80 + R2.size(0) * i79];
            }
        }
        varargin_6.set_size(R3.size(0), R3.size(1));
        cc_loop_ub = R3.size(1);
        for (int i81{0}; i81 < cc_loop_ub; i81++) {
            int dc_loop_ub;
            dc_loop_ub = R3.size(0);
            for (int i82{0}; i82 < dc_loop_ub; i82++) {
                varargin_6[i82 + varargin_6.size(0) * i81] = -R3[i82 + R3.size(0) * i81];
            }
        }
        if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            b_result = R1.size(1);
        } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
            b_result = varargin_2.size(1);
        } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
            b_result = R2.size(1);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            b_result = varargin_4.size(1);
        } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
            b_result = R3.size(1);
        } else if ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0)) {
            b_result = varargin_6.size(1);
        } else {
            b_result = R1.size(1);
            if (varargin_2.size(1) > R1.size(1)) {
                b_result = varargin_2.size(1);
            }
            if (R2.size(1) > b_result) {
                b_result = R2.size(1);
            }
            if (varargin_4.size(1) > b_result) {
                b_result = varargin_4.size(1);
            }
            if (R3.size(1) > b_result) {
                b_result = R3.size(1);
            }
            if (varargin_6.size(1) > b_result) {
                b_result = varargin_6.size(1);
            }
        }
        b_empty_non_axis_sizes = (b_result == 0);
        if (b_empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
            h_input_sizes_idx_0 = R1.size(0);
        } else {
            h_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            i_input_sizes_idx_0 = varargin_2.size(0);
        } else {
            i_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
            j_input_sizes_idx_0 = R2.size(0);
        } else {
            j_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            k_input_sizes_idx_0 = varargin_4.size(0);
        } else {
            k_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
            l_input_sizes_idx_0 = R3.size(0);
        } else {
            l_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0))) {
            m_input_sizes_idx_0 = varargin_6.size(0);
        } else {
            m_input_sizes_idx_0 = 0;
        }
        a_tmp = (static_cast<double>(c_k) + 1.0) * 6.0 * static_cast<double>(M) + 1.0;
        b_tmp = ((static_cast<double>(c_k) + 1.0) + 1.0) * 6.0 * static_cast<double>(M);
        if (b_tmp < a_tmp) {
            y.set_size(1, 0);
        } else {
            int ec_loop_ub;
            ec_loop_ub = static_cast<int>(b_tmp - a_tmp);
            y.set_size(1, ec_loop_ub + 1);
            for (int i83{0}; i83 <= ec_loop_ub; i83++) {
                y[i83] = a_tmp + static_cast<double>(i83);
            }
        }
        a = (static_cast<double>(c_k) + 1.0) * static_cast<double>(N) + 1.0;
        c_b = ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(N);
        if (c_b < a) {
            b_y.set_size(1, 0);
        } else {
            int fc_loop_ub;
            fc_loop_ub = static_cast<int>(c_b - a);
            b_y.set_size(1, fc_loop_ub + 1);
            for (int i84{0}; i84 <= fc_loop_ub; i84++) {
                b_y[i84] = a + static_cast<double>(i84);
            }
        }
        b_R1.set_size(((((h_input_sizes_idx_0 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                        k_input_sizes_idx_0) +
                       l_input_sizes_idx_0) +
                          m_input_sizes_idx_0,
                      b_result);
        for (int i85{0}; i85 < b_result; i85++) {
            for (int i87{0}; i87 < h_input_sizes_idx_0; i87++) {
                b_R1[i87 + b_R1.size(0) * i85] = R1[i87 + h_input_sizes_idx_0 * i85];
            }
        }
        for (int i86{0}; i86 < b_result; i86++) {
            for (int i89{0}; i89 < i_input_sizes_idx_0; i89++) {
                b_R1[(i89 + h_input_sizes_idx_0) + b_R1.size(0) * i86] =
                    varargin_2[i89 + i_input_sizes_idx_0 * i86];
            }
        }
        for (int i88{0}; i88 < b_result; i88++) {
            for (int i91{0}; i91 < j_input_sizes_idx_0; i91++) {
                b_R1[((i91 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + b_R1.size(0) * i88] =
                    R2[i91 + j_input_sizes_idx_0 * i88];
            }
        }
        for (int i90{0}; i90 < b_result; i90++) {
            for (int i93{0}; i93 < k_input_sizes_idx_0; i93++) {
                b_R1[(((i93 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                     b_R1.size(0) * i90] = varargin_4[i93 + k_input_sizes_idx_0 * i90];
            }
        }
        for (int i92{0}; i92 < b_result; i92++) {
            for (int i95{0}; i95 < l_input_sizes_idx_0; i95++) {
                b_R1[((((i95 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                      k_input_sizes_idx_0) +
                     b_R1.size(0) * i92] = R3[i95 + l_input_sizes_idx_0 * i92];
            }
        }
        for (int i94{0}; i94 < b_result; i94++) {
            for (int i96{0}; i96 < m_input_sizes_idx_0; i96++) {
                b_R1[(((((i96 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                       k_input_sizes_idx_0) +
                      l_input_sizes_idx_0) +
                     b_R1.size(0) * i94] = varargin_6[i96 + m_input_sizes_idx_0 * i94];
            }
        }
        A->parenAssign(b_R1, y, b_y);
        //
        // 'BuildConstrJerkWithSlacks:91' b(k*6*M+1:(k+1)*6*M) = [bC2;
        // 'BuildConstrJerkWithSlacks:92'                             bC2;
        // 'BuildConstrJerkWithSlacks:93'                             bC3;
        // 'BuildConstrJerkWithSlacks:94'                             bC3;
        // 'BuildConstrJerkWithSlacks:95'                             bC4;
        // 'BuildConstrJerkWithSlacks:96'                             bC4];
        if (a_tmp > b_tmp) {
            i97 = -1;
            i98 = 0;
        } else {
            i97 = static_cast<int>(a_tmp) - 2;
            i98 = static_cast<int>(b_tmp);
        }
        gc_loop_ub = (i98 - i97) - 1;
        for (int i99{0}; i99 < gc_loop_ub; i99++) {
            b[(i97 + i99) + 1] = r3[i99];
        }
        //
    }
    // 'BuildConstrJerkWithSlacks:100' A(1:end -1 , end) = -1;
    if (static_cast<double>(A->m) - 1.0 < 1.0) {
        y.set_size(1, 0);
    } else {
        int hb_loop_ub;
        y.set_size(1, static_cast<int>((static_cast<double>(A->m) - 1.0) - 1.0) + 1);
        hb_loop_ub = static_cast<int>((static_cast<double>(A->m) - 1.0) - 1.0);
        for (int i54{0}; i54 <= hb_loop_ub; i54++) {
            y[i54] = static_cast<double>(i54) + 1.0;
        }
    }
    A->parenAssign(y, static_cast<double>(A->n));
    // 'BuildConstrJerkWithSlacks:102' A(end, end) = -1;
    A->parenAssign(static_cast<double>(A->m), static_cast<double>(A->n));
    // 'BuildConstrJerkWithSlacks:102' b(end) = 0;
    b[b.size(0) - 1] = 0.0;
}

} // namespace ocn

//
// File trailer for BuildConstrJerkWithSlacks.cpp
//
// [EOF]
//
