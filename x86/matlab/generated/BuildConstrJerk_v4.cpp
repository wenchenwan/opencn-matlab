//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstrJerk_v4.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "BuildConstrJerk_v4.h"
#include "EvalCurvStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_types1.h"
#include "bsxfun.h"
#include "queue_coder.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &R3, const ::coder::array<double, 2U> &r1,
                             const ::coder::array<double, 2U> &r2,
                             const ::coder::array<double, 2U> &r3,
                             const ::coder::array<double, 1U> &y_tmp);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &R3
//                const ::coder::array<double, 2U> &r1
//                const ::coder::array<double, 2U> &r2
//                const ::coder::array<double, 2U> &r3
//                const ::coder::array<double, 1U> &y_tmp
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &R3, const ::coder::array<double, 2U> &r1,
                             const ::coder::array<double, 2U> &r2,
                             const ::coder::array<double, 2U> &r3,
                             const ::coder::array<double, 1U> &y_tmp)
{
    ::coder::array<double, 2U> r;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    if (r3.size(0) == 1) {
        if (r2.size(0) == 1) {
            i = r1.size(0);
        } else {
            i = r2.size(0);
        }
    } else {
        i = r3.size(0);
    }
    if (r3.size(1) == 1) {
        if (r2.size(1) == 1) {
            i1 = r1.size(1);
        } else {
            i1 = r2.size(1);
        }
    } else {
        i1 = r3.size(1);
    }
    r.set_size(i, i1);
    stride_0_0 = (r1.size(0) != 1);
    stride_0_1 = (r1.size(1) != 1);
    stride_1_0 = (r2.size(0) != 1);
    stride_1_1 = (r2.size(1) != 1);
    stride_2_0 = (r3.size(0) != 1);
    stride_2_1 = (r3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (r3.size(1) == 1) {
        if (r2.size(1) == 1) {
            loop_ub = r1.size(1);
        } else {
            loop_ub = r2.size(1);
        }
    } else {
        loop_ub = r3.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int b_loop_ub;
        if (r3.size(0) == 1) {
            if (r2.size(0) == 1) {
                b_loop_ub = r1.size(0);
            } else {
                b_loop_ub = r2.size(0);
            }
        } else {
            b_loop_ub = r3.size(0);
        }
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            r[i3 + r.size(0) * i2] = (r1[i3 * stride_0_0 + r1.size(0) * aux_0_1] +
                                      1.5 * r2[i3 * stride_1_0 + r2.size(0) * aux_1_1]) +
                                     0.5 * r3[i3 * stride_2_0 + r3.size(0) * aux_2_1];
        }
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    coder::bsxfun(r, y_tmp, R3);
}

//
// function [A, b] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff, jmax,  ...
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
void BuildConstrJerk_v4(const queue_coder *ctx_q_splines,
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
    ::coder::array<double, 2U> b_varargin_2;
    ::coder::array<double, 2U> b_y;
    ::coder::array<double, 2U> c_u_vec;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> varargin_4;
    ::coder::array<double, 2U> varargin_6;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> b_r2D;
    ::coder::array<double, 1U> b_r3D;
    ::coder::array<double, 1U> r17;
    ::coder::array<double, 1U> y_tmp;
    double b_b;
    double d;
    double varargin_2;
    int BasisVal_idx_0;
    int M;
    int N;
    int ab_loop_ub;
    int b_BasisVal_idx_0;
    int b_inner;
    int b_input_sizes_idx_0;
    int b_k;
    int b_loop_ub;
    int b_mc;
    int b_scalarLB;
    int b_vectorUB;
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
    int e_loop_ub;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int gb_loop_ub;
    int h_loop_ub;
    int i14;
    int i15;
    int i21;
    int i22;
    int i3;
    int i33;
    int i53;
    int i7;
    int i8;
    int i_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int j_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int mc;
    int n_loop_ub;
    int o_loop_ub;
    int r_loop_ub;
    int result;
    int t_loop_ub;
    int unnamed_idx_0;
    int v_loop_ub;
    bool empty_non_axis_sizes;
    // 'BuildConstrJerk_v4:3' c_prof_block('BuildConstrJerk_v4');
    //  import splines.*
    //
    // 'BuildConstrJerk_v4:6' Ncrv   = length(CurvStructs);
    // 'BuildConstrJerk_v4:7' [M, N] = size(BasisVal);
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    //
    // 'BuildConstrJerk_v4:9' A      = sparse(6*M*Ncrv,   N*Ncrv);
    varargin_2 = static_cast<double>(BasisVal.size(1)) * static_cast<double>(CurvStructs.size(1));
    A->m = static_cast<int>(6.0 * static_cast<double>(BasisVal.size(0)) *
                            static_cast<double>(CurvStructs.size(1)));
    A->n = static_cast<int>(varargin_2);
    A->d.set_size(1);
    A->d[0] = 0.0;
    loop_ub = static_cast<int>(varargin_2) + 1;
    A->colidx.set_size(static_cast<int>(static_cast<double>(BasisVal.size(1)) *
                                        static_cast<double>(CurvStructs.size(1))) +
                       1);
    for (int i{0}; i < loop_ub; i++) {
        A->colidx[i] = 1;
    }
    A->rowidx.set_size(1);
    A->rowidx[0] = 1;
    A->maxnz = 1;
    //  preallocation
    // 'BuildConstrJerk_v4:10' b      = zeros(6*M*Ncrv,   1);
    unnamed_idx_0 = static_cast<int>(6.0 * static_cast<double>(BasisVal.size(0)) *
                                     static_cast<double>(CurvStructs.size(1)));
    b.set_size(unnamed_idx_0);
    for (int i1{0}; i1 < unnamed_idx_0; i1++) {
        b[i1] = 0.0;
    }
    //  preallocation
    //  coder.varsize('A', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz,
    //  FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); coder.varsize('b',
    //  [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
    //
    //  q_opt  = Function(Bl, Coeff(:, 1));
    //  q_val  = q_opt.fast_eval(u_vec);
    // 'BuildConstrJerk_v4:18' q_val = BasisVal*Coeff(:,1);
    // 'BuildConstrJerk_v4:20' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(1), u_vec);
    b_u_vec.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1) - 1;
    for (int i2{0}; i2 <= b_loop_ub; i2++) {
        b_u_vec[i2] = u_vec[i2];
    }
    b_EvalCurvStruct(ctx_q_splines, &CurvStructs[0], b_u_vec, a__1, r1D, r2D, r3D);
    //
    // 'BuildConstrJerk_v4:22' R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)') + ...
    // 'BuildConstrJerk_v4:23'       1.5*bsxfun(@times, BasisValD , r2D(1, :)') + ...
    // 'BuildConstrJerk_v4:24'       0.5*bsxfun(@times, BasisValDD,r1D(1, :)')) , mysqrt(q_val));
    // 'mysqrt:3' y = sqrt(x);
    mc = BasisVal.size(0) - 1;
    inner = BasisVal.size(1);
    y_tmp.set_size(BasisVal.size(0));
    for (int b_i{0}; b_i <= mc; b_i++) {
        y_tmp[b_i] = 0.0;
    }
    for (int k{0}; k < inner; k++) {
        int c_i;
        int scalarLB;
        int vectorUB;
        scalarLB = ((mc + 1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (c_i = 0; c_i <= vectorUB; c_i += 2) {
            __m128d r;
            r = _mm_loadu_pd(&y_tmp[c_i]);
            _mm_storeu_pd(
                &y_tmp[c_i],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(
                                             (const double *)&BasisVal[c_i + BasisVal.size(0) * k]),
                                         _mm_set1_pd(Coeff[k]))));
        }
        for (c_i = scalarLB; c_i <= mc; c_i++) {
            y_tmp[c_i] = y_tmp[c_i] + BasisVal[c_i + BasisVal.size(0) * k] * Coeff[k];
        }
    }
    i3 = y_tmp.size(0);
    b_scalarLB = (y_tmp.size(0) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (b_k = 0; b_k <= b_vectorUB; b_k += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&y_tmp[b_k]);
        _mm_storeu_pd(&y_tmp[b_k], _mm_sqrt_pd(r1));
    }
    for (b_k = b_scalarLB; b_k < i3; b_k++) {
        y_tmp[b_k] = std::sqrt(y_tmp[b_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    c_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        b_r3D[i4] = r3D[3 * i4];
    }
    coder::bsxfun(BasisVal, b_r3D, r2);
    d_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        b_r2D[i5] = r2D[3 * i5];
    }
    coder::bsxfun(BasisValD, b_r2D, r3);
    e_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        b_r1D[i6] = r1D[3 * i6];
    }
    coder::bsxfun(BasisValDD, b_r1D, r4);
    if (r2.size(0) == 1) {
        i7 = r3.size(0);
    } else {
        i7 = r2.size(0);
    }
    if (r2.size(1) == 1) {
        i8 = r3.size(1);
    } else {
        i8 = r2.size(1);
    }
    if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i7 == r4.size(0)) &&
        (i8 == r4.size(1))) {
        int f_loop_ub;
        f_loop_ub = r2.size(1);
        for (int i9{0}; i9 < f_loop_ub; i9++) {
            int c_scalarLB;
            int c_vectorUB;
            int g_loop_ub;
            int i10;
            g_loop_ub = r2.size(0);
            c_scalarLB = (r2.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (i10 = 0; i10 <= c_vectorUB; i10 += 2) {
                __m128d r5;
                __m128d r6;
                __m128d r7;
                r5 = _mm_loadu_pd(&r3[i10 + r3.size(0) * i9]);
                r6 = _mm_loadu_pd(&r2[i10 + r2.size(0) * i9]);
                r7 = _mm_loadu_pd(&r4[i10 + r4.size(0) * i9]);
                _mm_storeu_pd(&r2[i10 + r2.size(0) * i9],
                              _mm_add_pd(_mm_add_pd(r6, _mm_mul_pd(_mm_set1_pd(1.5), r5)),
                                         _mm_mul_pd(_mm_set1_pd(0.5), r7)));
            }
            for (i10 = c_scalarLB; i10 < g_loop_ub; i10++) {
                r2[i10 + r2.size(0) * i9] =
                    (r2[i10 + r2.size(0) * i9] + 1.5 * r3[i10 + r3.size(0) * i9]) +
                    0.5 * r4[i10 + r4.size(0) * i9];
            }
        }
        coder::bsxfun(r2, y_tmp, R1);
    } else {
        binary_expand_op(R1, r2, r3, r4, y_tmp);
    }
    // 'BuildConstrJerk_v4:26' R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)') + ...
    // 'BuildConstrJerk_v4:27'   1.5*bsxfun(@times, BasisValD , r2D(2, :)') + ...
    // 'BuildConstrJerk_v4:28'   0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) , mysqrt(q_val));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    h_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        b_r3D[i11] = r3D[3 * i11 + 1];
    }
    coder::bsxfun(BasisVal, b_r3D, r2);
    i_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        b_r2D[i12] = r2D[3 * i12 + 1];
    }
    coder::bsxfun(BasisValD, b_r2D, r3);
    j_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i13{0}; i13 < j_loop_ub; i13++) {
        b_r1D[i13] = r1D[3 * i13 + 1];
    }
    coder::bsxfun(BasisValDD, b_r1D, r4);
    if (r2.size(0) == 1) {
        i14 = r3.size(0);
    } else {
        i14 = r2.size(0);
    }
    if (r2.size(1) == 1) {
        i15 = r3.size(1);
    } else {
        i15 = r2.size(1);
    }
    if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i14 == r4.size(0)) &&
        (i15 == r4.size(1))) {
        int k_loop_ub;
        k_loop_ub = r2.size(1);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            int d_scalarLB;
            int d_vectorUB;
            int i17;
            int l_loop_ub;
            l_loop_ub = r2.size(0);
            d_scalarLB = (r2.size(0) / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (i17 = 0; i17 <= d_vectorUB; i17 += 2) {
                __m128d r10;
                __m128d r8;
                __m128d r9;
                r8 = _mm_loadu_pd(&r3[i17 + r3.size(0) * i16]);
                r9 = _mm_loadu_pd(&r2[i17 + r2.size(0) * i16]);
                r10 = _mm_loadu_pd(&r4[i17 + r4.size(0) * i16]);
                _mm_storeu_pd(&r2[i17 + r2.size(0) * i16],
                              _mm_add_pd(_mm_add_pd(r9, _mm_mul_pd(_mm_set1_pd(1.5), r8)),
                                         _mm_mul_pd(_mm_set1_pd(0.5), r10)));
            }
            for (i17 = d_scalarLB; i17 < l_loop_ub; i17++) {
                r2[i17 + r2.size(0) * i16] =
                    (r2[i17 + r2.size(0) * i16] + 1.5 * r3[i17 + r3.size(0) * i16]) +
                    0.5 * r4[i17 + r4.size(0) * i16];
            }
        }
        coder::bsxfun(r2, y_tmp, R2);
    } else {
        binary_expand_op(R2, r2, r3, r4, y_tmp);
    }
    // 'BuildConstrJerk_v4:30' R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)') + ...
    // 'BuildConstrJerk_v4:31'   1.5*bsxfun(@times, BasisValD , r2D(3, :)') + ...
    // 'BuildConstrJerk_v4:32'   0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) , mysqrt(q_val));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    m_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i18{0}; i18 < m_loop_ub; i18++) {
        b_r3D[i18] = r3D[3 * i18 + 2];
    }
    coder::bsxfun(BasisVal, b_r3D, r2);
    n_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i19{0}; i19 < n_loop_ub; i19++) {
        b_r2D[i19] = r2D[3 * i19 + 2];
    }
    coder::bsxfun(BasisValD, b_r2D, r3);
    o_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i20{0}; i20 < o_loop_ub; i20++) {
        b_r1D[i20] = r1D[3 * i20 + 2];
    }
    coder::bsxfun(BasisValDD, b_r1D, r4);
    if (r2.size(0) == 1) {
        i21 = r3.size(0);
    } else {
        i21 = r2.size(0);
    }
    if (r2.size(1) == 1) {
        i22 = r3.size(1);
    } else {
        i22 = r2.size(1);
    }
    if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i21 == r4.size(0)) &&
        (i22 == r4.size(1))) {
        int p_loop_ub;
        p_loop_ub = r2.size(1);
        for (int i23{0}; i23 < p_loop_ub; i23++) {
            int e_scalarLB;
            int e_vectorUB;
            int i24;
            int q_loop_ub;
            q_loop_ub = r2.size(0);
            e_scalarLB = (r2.size(0) / 2) << 1;
            e_vectorUB = e_scalarLB - 2;
            for (i24 = 0; i24 <= e_vectorUB; i24 += 2) {
                __m128d r11;
                __m128d r12;
                __m128d r13;
                r11 = _mm_loadu_pd(&r3[i24 + r3.size(0) * i23]);
                r12 = _mm_loadu_pd(&r2[i24 + r2.size(0) * i23]);
                r13 = _mm_loadu_pd(&r4[i24 + r4.size(0) * i23]);
                _mm_storeu_pd(&r2[i24 + r2.size(0) * i23],
                              _mm_add_pd(_mm_add_pd(r12, _mm_mul_pd(_mm_set1_pd(1.5), r11)),
                                         _mm_mul_pd(_mm_set1_pd(0.5), r13)));
            }
            for (i24 = e_scalarLB; i24 < q_loop_ub; i24++) {
                r2[i24 + r2.size(0) * i23] =
                    (r2[i24 + r2.size(0) * i23] + 1.5 * r3[i24 + r3.size(0) * i23]) +
                    0.5 * r4[i24 + r4.size(0) * i23];
            }
        }
        coder::bsxfun(r2, y_tmp, R3);
    } else {
        binary_expand_op(R3, r2, r3, r4, y_tmp);
    }
    //  R2 = (BasisVal .* r3D(2, :)' + ...
    //        1.5*BasisValD .* r2D(2, :)' + ...
    //        0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
    //  R3 = (BasisVal .* r3D(3, :)' + ...
    //        1.5*BasisValD .* r2D(3, :)' + ...
    //        0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
    //
    // 'BuildConstrJerk_v4:40' A(1:6*M, 1:N)  = [R1;
    // 'BuildConstrJerk_v4:41'                  -R1;
    // 'BuildConstrJerk_v4:42'                   R2;
    // 'BuildConstrJerk_v4:43'                  -R2;
    // 'BuildConstrJerk_v4:44'                   R3;
    // 'BuildConstrJerk_v4:45'                  -R3];
    b_varargin_2.set_size(R1.size(0), R1.size(1));
    r_loop_ub = R1.size(1);
    for (int i25{0}; i25 < r_loop_ub; i25++) {
        int f_scalarLB;
        int f_vectorUB;
        int i27;
        int s_loop_ub;
        s_loop_ub = R1.size(0);
        f_scalarLB = (R1.size(0) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (i27 = 0; i27 <= f_vectorUB; i27 += 2) {
            __m128d r14;
            r14 = _mm_loadu_pd(&R1[i27 + R1.size(0) * i25]);
            _mm_storeu_pd(&b_varargin_2[i27 + b_varargin_2.size(0) * i25],
                          _mm_mul_pd(r14, _mm_set1_pd(-1.0)));
        }
        for (i27 = f_scalarLB; i27 < s_loop_ub; i27++) {
            b_varargin_2[i27 + b_varargin_2.size(0) * i25] = -R1[i27 + R1.size(0) * i25];
        }
    }
    varargin_4.set_size(R2.size(0), R2.size(1));
    t_loop_ub = R2.size(1);
    for (int i26{0}; i26 < t_loop_ub; i26++) {
        int g_scalarLB;
        int g_vectorUB;
        int i29;
        int u_loop_ub;
        u_loop_ub = R2.size(0);
        g_scalarLB = (R2.size(0) / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (i29 = 0; i29 <= g_vectorUB; i29 += 2) {
            __m128d r15;
            r15 = _mm_loadu_pd(&R2[i29 + R2.size(0) * i26]);
            _mm_storeu_pd(&varargin_4[i29 + varargin_4.size(0) * i26],
                          _mm_mul_pd(r15, _mm_set1_pd(-1.0)));
        }
        for (i29 = g_scalarLB; i29 < u_loop_ub; i29++) {
            varargin_4[i29 + varargin_4.size(0) * i26] = -R2[i29 + R2.size(0) * i26];
        }
    }
    varargin_6.set_size(R3.size(0), R3.size(1));
    v_loop_ub = R3.size(1);
    for (int i28{0}; i28 < v_loop_ub; i28++) {
        int h_scalarLB;
        int h_vectorUB;
        int i30;
        int w_loop_ub;
        w_loop_ub = R3.size(0);
        h_scalarLB = (R3.size(0) / 2) << 1;
        h_vectorUB = h_scalarLB - 2;
        for (i30 = 0; i30 <= h_vectorUB; i30 += 2) {
            __m128d r16;
            r16 = _mm_loadu_pd(&R3[i30 + R3.size(0) * i28]);
            _mm_storeu_pd(&varargin_6[i30 + varargin_6.size(0) * i28],
                          _mm_mul_pd(r16, _mm_set1_pd(-1.0)));
        }
        for (i30 = h_scalarLB; i30 < w_loop_ub; i30++) {
            varargin_6[i30 + varargin_6.size(0) * i28] = -R3[i30 + R3.size(0) * i28];
        }
    }
    if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
        result = R1.size(1);
    } else if ((b_varargin_2.size(0) != 0) && (b_varargin_2.size(1) != 0)) {
        result = b_varargin_2.size(1);
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
        if (b_varargin_2.size(1) > R1.size(1)) {
            result = b_varargin_2.size(1);
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
    if (empty_non_axis_sizes || ((b_varargin_2.size(0) != 0) && (b_varargin_2.size(1) != 0))) {
        b_input_sizes_idx_0 = b_varargin_2.size(0);
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
        int x_loop_ub;
        y.set_size(1, static_cast<int>(b_b - 1.0) + 1);
        x_loop_ub = static_cast<int>(b_b - 1.0);
        for (int i31{0}; i31 <= x_loop_ub; i31++) {
            y[i31] = static_cast<double>(i31) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int y_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        y_loop_ub = BasisVal.size(1) - 1;
        for (int i32{0}; i32 <= y_loop_ub; i32++) {
            b_y[i32] = static_cast<double>(i32) + 1.0;
        }
    }
    g_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    i33 = g_input_sizes_idx_0 + input_sizes_idx_0;
    b_R1.set_size((((i33 + b_input_sizes_idx_0) + c_input_sizes_idx_0) + e_input_sizes_idx_0) +
                      f_input_sizes_idx_0,
                  result);
    for (int i34{0}; i34 < result; i34++) {
        for (int i36{0}; i36 < g_input_sizes_idx_0; i36++) {
            b_R1[i36 + b_R1.size(0) * i34] = R1[i36 + g_input_sizes_idx_0 * i34];
        }
    }
    for (int i35{0}; i35 < result; i35++) {
        for (int i38{0}; i38 < input_sizes_idx_0; i38++) {
            b_R1[(i38 + g_input_sizes_idx_0) + b_R1.size(0) * i35] =
                b_varargin_2[i38 + input_sizes_idx_0 * i35];
        }
    }
    for (int i37{0}; i37 < result; i37++) {
        for (int i40{0}; i40 < b_input_sizes_idx_0; i40++) {
            b_R1[((i40 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_R1.size(0) * i37] =
                R2[i40 + b_input_sizes_idx_0 * i37];
        }
    }
    for (int i39{0}; i39 < result; i39++) {
        for (int i42{0}; i42 < c_input_sizes_idx_0; i42++) {
            b_R1[(((i42 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                 b_R1.size(0) * i39] = varargin_4[i42 + c_input_sizes_idx_0 * i39];
        }
    }
    for (int i41{0}; i41 < result; i41++) {
        for (int i44{0}; i44 < e_input_sizes_idx_0; i44++) {
            b_R1[((((i44 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                  c_input_sizes_idx_0) +
                 b_R1.size(0) * i41] = R3[i44 + e_input_sizes_idx_0 * i41];
        }
    }
    for (int i43{0}; i43 < result; i43++) {
        for (int i45{0}; i45 < f_input_sizes_idx_0; i45++) {
            b_R1[((((i45 + i33) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                  e_input_sizes_idx_0) +
                 b_R1.size(0) * i43] = varargin_6[i45 + f_input_sizes_idx_0 * i43];
        }
    }
    A->parenAssign(b_R1, y, b_y);
    //
    // 'BuildConstrJerk_v4:47' bC2 = jmax(1)*ones(M, 1);
    // 'BuildConstrJerk_v4:48' bC3 = jmax(2)*ones(M, 1);
    // 'BuildConstrJerk_v4:49' bC4 = jmax(3)*ones(M, 1);
    //
    // 'BuildConstrJerk_v4:51' b(1:6*M)       = [bC2;
    // 'BuildConstrJerk_v4:52'                   bC2;
    // 'BuildConstrJerk_v4:53'                   bC3;
    // 'BuildConstrJerk_v4:54'                   bC3;
    // 'BuildConstrJerk_v4:55'                   bC4;
    // 'BuildConstrJerk_v4:56'                   bC4];
    d = 6.0 * static_cast<double>(BasisVal.size(0));
    BasisVal_idx_0 = BasisVal.size(0);
    b_BasisVal_idx_0 = BasisVal.size(0);
    c_BasisVal_idx_0 = BasisVal.size(0);
    d_BasisVal_idx_0 = BasisVal.size(0);
    r17.set_size(((((BasisVal.size(0) + BasisVal.size(0)) + BasisVal.size(0)) + BasisVal.size(0)) +
                  BasisVal.size(0)) +
                 BasisVal.size(0));
    ab_loop_ub = BasisVal.size(0);
    for (int i46{0}; i46 < ab_loop_ub; i46++) {
        r17[i46] = jmax[0];
    }
    bb_loop_ub = BasisVal.size(0);
    for (int i47{0}; i47 < bb_loop_ub; i47++) {
        r17[i47 + BasisVal_idx_0] = jmax[0];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i48{0}; i48 < cb_loop_ub; i48++) {
        r17[(i48 + BasisVal_idx_0) + b_BasisVal_idx_0] = jmax[1];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i49{0}; i49 < db_loop_ub; i49++) {
        r17[((i49 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0] = jmax[1];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i50{0}; i50 < eb_loop_ub; i50++) {
        r17[(((i50 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0] =
            jmax[2];
    }
    fb_loop_ub = BasisVal.size(0);
    for (int i51{0}; i51 < fb_loop_ub; i51++) {
        r17[((((i51 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0) +
            BasisVal.size(0)] = jmax[2];
    }
    if (1.0 > d) {
        gb_loop_ub = 0;
    } else {
        gb_loop_ub = static_cast<int>(d);
    }
    for (int i52{0}; i52 < gb_loop_ub; i52++) {
        b[i52] = r17[i52];
    }
    //
    // 'BuildConstrJerk_v4:58' for k = 1:Ncrv-1
    i53 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_mc = BasisVal.size(0) - 1;
        b_inner = BasisVal.size(1);
    }
    for (int c_k{0}; c_k <= i53 - 2; c_k++) {
        double a;
        double a_tmp;
        double b_tmp;
        double c_b;
        int ac_loop_ub;
        int b_result;
        int cc_loop_ub;
        int e_k;
        int gc_loop_ub;
        int h_input_sizes_idx_0;
        int hb_loop_ub;
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
        int j_scalarLB;
        int j_vectorUB;
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
        // 'BuildConstrJerk_v4:59' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(k+1),
        // u_vec);
        c_u_vec.set_size(1, u_vec.size(1));
        hb_loop_ub = u_vec.size(1) - 1;
        for (int i54{0}; i54 <= hb_loop_ub; i54++) {
            c_u_vec[i54] = u_vec[i54];
        }
        b_EvalCurvStruct(ctx_q_splines, &CurvStructs[c_k + 1], c_u_vec, a__2, r1D, r2D, r3D);
        //
        //      q_opt  = Function(Bl, Coeff(:, k+1));
        //      q_val  = q_opt.fast_eval(u_vec);
        // 'BuildConstrJerk_v4:63' q_val = BasisVal*Coeff(:, k+1);
        //
        // 'BuildConstrJerk_v4:65' R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)') + ...
        // 'BuildConstrJerk_v4:66'           1.5*bsxfun(@times, BasisValD , r2D(1, :)') + ...
        // 'BuildConstrJerk_v4:67'           0.5*bsxfun(@times, BasisValDD,r1D(1, :)')) ,
        // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x);
        y_tmp.set_size(BasisVal.size(0));
        for (int d_i{0}; d_i <= b_mc; d_i++) {
            y_tmp[d_i] = 0.0;
        }
        for (int d_k{0}; d_k < b_inner; d_k++) {
            int e_i;
            int i_scalarLB;
            int i_vectorUB;
            i_scalarLB = ((b_mc + 1) / 2) << 1;
            i_vectorUB = i_scalarLB - 2;
            for (e_i = 0; e_i <= i_vectorUB; e_i += 2) {
                __m128d r18;
                r18 = _mm_loadu_pd(&y_tmp[e_i]);
                _mm_storeu_pd(
                    &y_tmp[e_i],
                    _mm_add_pd(
                        r18, _mm_mul_pd(_mm_loadu_pd((
                                            const double *)&BasisVal[e_i + BasisVal.size(0) * d_k]),
                                        _mm_set1_pd(Coeff[d_k + Coeff.size(0) * (c_k + 1)]))));
            }
            for (e_i = i_scalarLB; e_i <= b_mc; e_i++) {
                y_tmp[e_i] = y_tmp[e_i] + BasisVal[e_i + BasisVal.size(0) * d_k] *
                                              Coeff[d_k + Coeff.size(0) * (c_k + 1)];
            }
        }
        i55 = y_tmp.size(0);
        j_scalarLB = (y_tmp.size(0) / 2) << 1;
        j_vectorUB = j_scalarLB - 2;
        for (e_k = 0; e_k <= j_vectorUB; e_k += 2) {
            __m128d r19;
            r19 = _mm_loadu_pd(&y_tmp[e_k]);
            _mm_storeu_pd(&y_tmp[e_k], _mm_sqrt_pd(r19));
        }
        for (e_k = j_scalarLB; e_k < i55; e_k++) {
            y_tmp[e_k] = std::sqrt(y_tmp[e_k]);
        }
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        ib_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i56{0}; i56 < ib_loop_ub; i56++) {
            b_r3D[i56] = r3D[3 * i56];
        }
        coder::bsxfun(BasisVal, b_r3D, r2);
        jb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i57{0}; i57 < jb_loop_ub; i57++) {
            b_r2D[i57] = r2D[3 * i57];
        }
        coder::bsxfun(BasisValD, b_r2D, r3);
        kb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i58{0}; i58 < kb_loop_ub; i58++) {
            b_r1D[i58] = r1D[3 * i58];
        }
        coder::bsxfun(BasisValDD, b_r1D, r4);
        if (r2.size(0) == 1) {
            i59 = r3.size(0);
        } else {
            i59 = r2.size(0);
        }
        if (r2.size(1) == 1) {
            i60 = r3.size(1);
        } else {
            i60 = r2.size(1);
        }
        if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i59 == r4.size(0)) &&
            (i60 == r4.size(1))) {
            int lb_loop_ub;
            lb_loop_ub = r2.size(1);
            for (int i61{0}; i61 < lb_loop_ub; i61++) {
                int i62;
                int k_scalarLB;
                int k_vectorUB;
                int mb_loop_ub;
                mb_loop_ub = r2.size(0);
                k_scalarLB = (r2.size(0) / 2) << 1;
                k_vectorUB = k_scalarLB - 2;
                for (i62 = 0; i62 <= k_vectorUB; i62 += 2) {
                    __m128d r20;
                    __m128d r21;
                    __m128d r22;
                    r20 = _mm_loadu_pd(&r3[i62 + r3.size(0) * i61]);
                    r21 = _mm_loadu_pd(&r2[i62 + r2.size(0) * i61]);
                    r22 = _mm_loadu_pd(&r4[i62 + r4.size(0) * i61]);
                    _mm_storeu_pd(&r2[i62 + r2.size(0) * i61],
                                  _mm_add_pd(_mm_add_pd(r21, _mm_mul_pd(_mm_set1_pd(1.5), r20)),
                                             _mm_mul_pd(_mm_set1_pd(0.5), r22)));
                }
                for (i62 = k_scalarLB; i62 < mb_loop_ub; i62++) {
                    r2[i62 + r2.size(0) * i61] =
                        (r2[i62 + r2.size(0) * i61] + 1.5 * r3[i62 + r3.size(0) * i61]) +
                        0.5 * r4[i62 + r4.size(0) * i61];
                }
            }
            coder::bsxfun(r2, y_tmp, R1);
        } else {
            binary_expand_op(R1, r2, r3, r4, y_tmp);
        }
        // 'BuildConstrJerk_v4:69' R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)') + ...
        // 'BuildConstrJerk_v4:70'       1.5*bsxfun(@times, BasisValD , r2D(2, :)') + ...
        // 'BuildConstrJerk_v4:71'       0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) ,
        // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x); 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        nb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i63{0}; i63 < nb_loop_ub; i63++) {
            b_r3D[i63] = r3D[3 * i63 + 1];
        }
        coder::bsxfun(BasisVal, b_r3D, r2);
        ob_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i64{0}; i64 < ob_loop_ub; i64++) {
            b_r2D[i64] = r2D[3 * i64 + 1];
        }
        coder::bsxfun(BasisValD, b_r2D, r3);
        pb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i65{0}; i65 < pb_loop_ub; i65++) {
            b_r1D[i65] = r1D[3 * i65 + 1];
        }
        coder::bsxfun(BasisValDD, b_r1D, r4);
        if (r2.size(0) == 1) {
            i66 = r3.size(0);
        } else {
            i66 = r2.size(0);
        }
        if (r2.size(1) == 1) {
            i67 = r3.size(1);
        } else {
            i67 = r2.size(1);
        }
        if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i66 == r4.size(0)) &&
            (i67 == r4.size(1))) {
            int qb_loop_ub;
            qb_loop_ub = r2.size(1);
            for (int i68{0}; i68 < qb_loop_ub; i68++) {
                int i69;
                int l_scalarLB;
                int l_vectorUB;
                int rb_loop_ub;
                rb_loop_ub = r2.size(0);
                l_scalarLB = (r2.size(0) / 2) << 1;
                l_vectorUB = l_scalarLB - 2;
                for (i69 = 0; i69 <= l_vectorUB; i69 += 2) {
                    __m128d r23;
                    __m128d r24;
                    __m128d r25;
                    r23 = _mm_loadu_pd(&r3[i69 + r3.size(0) * i68]);
                    r24 = _mm_loadu_pd(&r2[i69 + r2.size(0) * i68]);
                    r25 = _mm_loadu_pd(&r4[i69 + r4.size(0) * i68]);
                    _mm_storeu_pd(&r2[i69 + r2.size(0) * i68],
                                  _mm_add_pd(_mm_add_pd(r24, _mm_mul_pd(_mm_set1_pd(1.5), r23)),
                                             _mm_mul_pd(_mm_set1_pd(0.5), r25)));
                }
                for (i69 = l_scalarLB; i69 < rb_loop_ub; i69++) {
                    r2[i69 + r2.size(0) * i68] =
                        (r2[i69 + r2.size(0) * i68] + 1.5 * r3[i69 + r3.size(0) * i68]) +
                        0.5 * r4[i69 + r4.size(0) * i68];
                }
            }
            coder::bsxfun(r2, y_tmp, R2);
        } else {
            binary_expand_op(R2, r2, r3, r4, y_tmp);
        }
        // 'BuildConstrJerk_v4:73' R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)') + ...
        // 'BuildConstrJerk_v4:74'       1.5*bsxfun(@times, BasisValD , r2D(3, :)') + ...
        // 'BuildConstrJerk_v4:75'       0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) ,
        // mysqrt(q_val)); 'mysqrt:3' y = sqrt(x); 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        sb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i70{0}; i70 < sb_loop_ub; i70++) {
            b_r3D[i70] = r3D[3 * i70 + 2];
        }
        coder::bsxfun(BasisVal, b_r3D, r2);
        tb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i71{0}; i71 < tb_loop_ub; i71++) {
            b_r2D[i71] = r2D[3 * i71 + 2];
        }
        coder::bsxfun(BasisValD, b_r2D, r3);
        ub_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i72{0}; i72 < ub_loop_ub; i72++) {
            b_r1D[i72] = r1D[3 * i72 + 2];
        }
        coder::bsxfun(BasisValDD, b_r1D, r4);
        if (r2.size(0) == 1) {
            i73 = r3.size(0);
        } else {
            i73 = r2.size(0);
        }
        if (r2.size(1) == 1) {
            i74 = r3.size(1);
        } else {
            i74 = r2.size(1);
        }
        if ((r2.size(0) == r3.size(0)) && (r2.size(1) == r3.size(1)) && (i73 == r4.size(0)) &&
            (i74 == r4.size(1))) {
            int vb_loop_ub;
            vb_loop_ub = r2.size(1);
            for (int i75{0}; i75 < vb_loop_ub; i75++) {
                int i76;
                int m_scalarLB;
                int m_vectorUB;
                int wb_loop_ub;
                wb_loop_ub = r2.size(0);
                m_scalarLB = (r2.size(0) / 2) << 1;
                m_vectorUB = m_scalarLB - 2;
                for (i76 = 0; i76 <= m_vectorUB; i76 += 2) {
                    __m128d r26;
                    __m128d r27;
                    __m128d r28;
                    r26 = _mm_loadu_pd(&r3[i76 + r3.size(0) * i75]);
                    r27 = _mm_loadu_pd(&r2[i76 + r2.size(0) * i75]);
                    r28 = _mm_loadu_pd(&r4[i76 + r4.size(0) * i75]);
                    _mm_storeu_pd(&r2[i76 + r2.size(0) * i75],
                                  _mm_add_pd(_mm_add_pd(r27, _mm_mul_pd(_mm_set1_pd(1.5), r26)),
                                             _mm_mul_pd(_mm_set1_pd(0.5), r28)));
                }
                for (i76 = m_scalarLB; i76 < wb_loop_ub; i76++) {
                    r2[i76 + r2.size(0) * i75] =
                        (r2[i76 + r2.size(0) * i75] + 1.5 * r3[i76 + r3.size(0) * i75]) +
                        0.5 * r4[i76 + r4.size(0) * i75];
                }
            }
            coder::bsxfun(r2, y_tmp, R3);
        } else {
            binary_expand_op(R3, r2, r3, r4, y_tmp);
        }
        //      R2 = (BasisVal .* r3D(2, :)' + ...
        //            1.5*BasisValD .* r2D(2, :)' + ...
        //            0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
        //      R3 = (BasisVal .* r3D(3, :)' + ...
        //            1.5*BasisValD .* r2D(3, :)' + ...
        //            0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
        //
        // 'BuildConstrJerk_v4:83' A(k*6*M+1:(k+1)*6*M, k*N+1:(k+1)*N) = ...
        // 'BuildConstrJerk_v4:84'       [R1;
        // 'BuildConstrJerk_v4:85'       -R1;
        // 'BuildConstrJerk_v4:86'        R2;
        // 'BuildConstrJerk_v4:87'       -R2;
        // 'BuildConstrJerk_v4:88'        R3;
        // 'BuildConstrJerk_v4:89'       -R3];
        b_varargin_2.set_size(R1.size(0), R1.size(1));
        xb_loop_ub = R1.size(1);
        for (int i77{0}; i77 < xb_loop_ub; i77++) {
            int i79;
            int n_scalarLB;
            int n_vectorUB;
            int yb_loop_ub;
            yb_loop_ub = R1.size(0);
            n_scalarLB = (R1.size(0) / 2) << 1;
            n_vectorUB = n_scalarLB - 2;
            for (i79 = 0; i79 <= n_vectorUB; i79 += 2) {
                __m128d r29;
                r29 = _mm_loadu_pd(&R1[i79 + R1.size(0) * i77]);
                _mm_storeu_pd(&b_varargin_2[i79 + b_varargin_2.size(0) * i77],
                              _mm_mul_pd(r29, _mm_set1_pd(-1.0)));
            }
            for (i79 = n_scalarLB; i79 < yb_loop_ub; i79++) {
                b_varargin_2[i79 + b_varargin_2.size(0) * i77] = -R1[i79 + R1.size(0) * i77];
            }
        }
        varargin_4.set_size(R2.size(0), R2.size(1));
        ac_loop_ub = R2.size(1);
        for (int i78{0}; i78 < ac_loop_ub; i78++) {
            int bc_loop_ub;
            int i81;
            int o_scalarLB;
            int o_vectorUB;
            bc_loop_ub = R2.size(0);
            o_scalarLB = (R2.size(0) / 2) << 1;
            o_vectorUB = o_scalarLB - 2;
            for (i81 = 0; i81 <= o_vectorUB; i81 += 2) {
                __m128d r30;
                r30 = _mm_loadu_pd(&R2[i81 + R2.size(0) * i78]);
                _mm_storeu_pd(&varargin_4[i81 + varargin_4.size(0) * i78],
                              _mm_mul_pd(r30, _mm_set1_pd(-1.0)));
            }
            for (i81 = o_scalarLB; i81 < bc_loop_ub; i81++) {
                varargin_4[i81 + varargin_4.size(0) * i78] = -R2[i81 + R2.size(0) * i78];
            }
        }
        varargin_6.set_size(R3.size(0), R3.size(1));
        cc_loop_ub = R3.size(1);
        for (int i80{0}; i80 < cc_loop_ub; i80++) {
            int dc_loop_ub;
            int i82;
            int p_scalarLB;
            int p_vectorUB;
            dc_loop_ub = R3.size(0);
            p_scalarLB = (R3.size(0) / 2) << 1;
            p_vectorUB = p_scalarLB - 2;
            for (i82 = 0; i82 <= p_vectorUB; i82 += 2) {
                __m128d r31;
                r31 = _mm_loadu_pd(&R3[i82 + R3.size(0) * i80]);
                _mm_storeu_pd(&varargin_6[i82 + varargin_6.size(0) * i80],
                              _mm_mul_pd(r31, _mm_set1_pd(-1.0)));
            }
            for (i82 = p_scalarLB; i82 < dc_loop_ub; i82++) {
                varargin_6[i82 + varargin_6.size(0) * i80] = -R3[i82 + R3.size(0) * i80];
            }
        }
        if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            b_result = R1.size(1);
        } else if ((b_varargin_2.size(0) != 0) && (b_varargin_2.size(1) != 0)) {
            b_result = b_varargin_2.size(1);
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
            if (b_varargin_2.size(1) > R1.size(1)) {
                b_result = b_varargin_2.size(1);
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
        if (b_empty_non_axis_sizes ||
            ((b_varargin_2.size(0) != 0) && (b_varargin_2.size(1) != 0))) {
            i_input_sizes_idx_0 = b_varargin_2.size(0);
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
                    b_varargin_2[i89 + i_input_sizes_idx_0 * i86];
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
        // 'BuildConstrJerk_v4:91' b(k*6*M+1:(k+1)*6*M) = [bC2;
        // 'BuildConstrJerk_v4:92'                             bC2;
        // 'BuildConstrJerk_v4:93'                             bC3;
        // 'BuildConstrJerk_v4:94'                             bC3;
        // 'BuildConstrJerk_v4:95'                             bC4;
        // 'BuildConstrJerk_v4:96'                             bC4];
        if (a_tmp > b_tmp) {
            i97 = -1;
            i98 = 0;
        } else {
            i97 = static_cast<int>(a_tmp) - 2;
            i98 = static_cast<int>(b_tmp);
        }
        gc_loop_ub = (i98 - i97) - 1;
        for (int i99{0}; i99 < gc_loop_ub; i99++) {
            b[(i97 + i99) + 1] = r17[i99];
        }
        //
    }
}

} // namespace ocn

//
// File trailer for BuildConstrJerk_v4.cpp
//
// [EOF]
//
