//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstrJerk_v4.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "BuildConstrJerk_v4.h"
#include "EvalCurvStruct.h"
#include "bsxfun.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
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
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
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
    double varargin_2;
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
    int e_loop_ub;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int f_loop_ub;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int gb_loop_ub;
    int h_loop_ub;
    int i27;
    int i3;
    int i47;
    int i_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int j_loop_ub;
    int k_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int mc;
    int n_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int r_loop_ub;
    int result;
    int t_loop_ub;
    int unnamed_idx_0;
    int v_loop_ub;
    bool empty_non_axis_sizes;
    //  import splines.*
    //
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    //
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
    b_u_vec.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1) - 1;
    for (int i2{0}; i2 <= b_loop_ub; i2++) {
        b_u_vec[i2] = u_vec[i2];
    }
    b_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                     CurvStructs[0].CorrectedHelixCenter, CurvStructs[0].evec, CurvStructs[0].theta,
                     CurvStructs[0].pitch, CurvStructs[0].CoeffP5, CurvStructs[0].sp_index,
                     CurvStructs[0].a_param, CurvStructs[0].b_param, b_u_vec, a__1, r1D, r2D, r3D);
    //
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
    i3 = y_tmp.size(0);
    for (int b_k{0}; b_k < i3; b_k++) {
        y_tmp[b_k] = std::sqrt(y_tmp[b_k]);
    }
    sqrt_calls++;
    c_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        b_r3D[i4] = r3D[3 * i4];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    d_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        b_r2D[i5] = r2D[3 * i5];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    e_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        b_r1D[i6] = r1D[3 * i6];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    f_loop_ub = r.size(1);
    for (int i7{0}; i7 < f_loop_ub; i7++) {
        int g_loop_ub;
        g_loop_ub = r.size(0);
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            r[i8 + r.size(0) * i7] = (r[i8 + r.size(0) * i7] + 1.5 * r1[i8 + r1.size(0) * i7]) +
                                     0.5 * r2[i8 + r2.size(0) * i7];
        }
    }
    coder::bsxfun(r, y_tmp, R1);
    sqrt_calls++;
    h_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        b_r3D[i9] = r3D[3 * i9 + 1];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    i_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        b_r2D[i10] = r2D[3 * i10 + 1];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    j_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        b_r1D[i11] = r1D[3 * i11 + 1];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    k_loop_ub = r.size(1);
    for (int i12{0}; i12 < k_loop_ub; i12++) {
        int l_loop_ub;
        l_loop_ub = r.size(0);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            r[i13 + r.size(0) * i12] =
                (r[i13 + r.size(0) * i12] + 1.5 * r1[i13 + r1.size(0) * i12]) +
                0.5 * r2[i13 + r2.size(0) * i12];
        }
    }
    coder::bsxfun(r, y_tmp, R2);
    sqrt_calls++;
    m_loop_ub = r3D.size(1);
    b_r3D.set_size(r3D.size(1));
    for (int i14{0}; i14 < m_loop_ub; i14++) {
        b_r3D[i14] = r3D[3 * i14 + 2];
    }
    coder::bsxfun(BasisVal, b_r3D, r);
    n_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i15{0}; i15 < n_loop_ub; i15++) {
        b_r2D[i15] = r2D[3 * i15 + 2];
    }
    coder::bsxfun(BasisValD, b_r2D, r1);
    o_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i16{0}; i16 < o_loop_ub; i16++) {
        b_r1D[i16] = r1D[3 * i16 + 2];
    }
    coder::bsxfun(BasisValDD, b_r1D, r2);
    p_loop_ub = r.size(1);
    for (int i17{0}; i17 < p_loop_ub; i17++) {
        int q_loop_ub;
        q_loop_ub = r.size(0);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            r[i18 + r.size(0) * i17] =
                (r[i18 + r.size(0) * i17] + 1.5 * r1[i18 + r1.size(0) * i17]) +
                0.5 * r2[i18 + r2.size(0) * i17];
        }
    }
    coder::bsxfun(r, y_tmp, R3);
    //  R2 = (BasisVal .* r3D(2, :)' + ...
    //        1.5*BasisValD .* r2D(2, :)' + ...
    //        0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
    //  R3 = (BasisVal .* r3D(3, :)' + ...
    //        1.5*BasisValD .* r2D(3, :)' + ...
    //        0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
    //
    b_varargin_2.set_size(R1.size(0), R1.size(1));
    r_loop_ub = R1.size(1);
    for (int i19{0}; i19 < r_loop_ub; i19++) {
        int s_loop_ub;
        s_loop_ub = R1.size(0);
        for (int i20{0}; i20 < s_loop_ub; i20++) {
            b_varargin_2[i20 + b_varargin_2.size(0) * i19] = -R1[i20 + R1.size(0) * i19];
        }
    }
    varargin_4.set_size(R2.size(0), R2.size(1));
    t_loop_ub = R2.size(1);
    for (int i21{0}; i21 < t_loop_ub; i21++) {
        int u_loop_ub;
        u_loop_ub = R2.size(0);
        for (int i22{0}; i22 < u_loop_ub; i22++) {
            varargin_4[i22 + varargin_4.size(0) * i21] = -R2[i22 + R2.size(0) * i21];
        }
    }
    varargin_6.set_size(R3.size(0), R3.size(1));
    v_loop_ub = R3.size(1);
    for (int i23{0}; i23 < v_loop_ub; i23++) {
        int w_loop_ub;
        w_loop_ub = R3.size(0);
        for (int i24{0}; i24 < w_loop_ub; i24++) {
            varargin_6[i24 + varargin_6.size(0) * i23] = -R3[i24 + R3.size(0) * i23];
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
        for (int i25{0}; i25 <= x_loop_ub; i25++) {
            y[i25] = static_cast<double>(i25) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int y_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        y_loop_ub = BasisVal.size(1) - 1;
        for (int i26{0}; i26 <= y_loop_ub; i26++) {
            b_y[i26] = static_cast<double>(i26) + 1.0;
        }
    }
    g_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    i27 = g_input_sizes_idx_0 + input_sizes_idx_0;
    b_R1.set_size((((i27 + b_input_sizes_idx_0) + c_input_sizes_idx_0) + e_input_sizes_idx_0) +
                      f_input_sizes_idx_0,
                  result);
    for (int i28{0}; i28 < result; i28++) {
        for (int i30{0}; i30 < g_input_sizes_idx_0; i30++) {
            b_R1[i30 + b_R1.size(0) * i28] = R1[i30 + g_input_sizes_idx_0 * i28];
        }
    }
    for (int i29{0}; i29 < result; i29++) {
        for (int i32{0}; i32 < input_sizes_idx_0; i32++) {
            b_R1[(i32 + g_input_sizes_idx_0) + b_R1.size(0) * i29] =
                b_varargin_2[i32 + input_sizes_idx_0 * i29];
        }
    }
    for (int i31{0}; i31 < result; i31++) {
        for (int i34{0}; i34 < b_input_sizes_idx_0; i34++) {
            b_R1[((i34 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_R1.size(0) * i31] =
                R2[i34 + b_input_sizes_idx_0 * i31];
        }
    }
    for (int i33{0}; i33 < result; i33++) {
        for (int i36{0}; i36 < c_input_sizes_idx_0; i36++) {
            b_R1[(((i36 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                 b_R1.size(0) * i33] = varargin_4[i36 + c_input_sizes_idx_0 * i33];
        }
    }
    for (int i35{0}; i35 < result; i35++) {
        for (int i38{0}; i38 < e_input_sizes_idx_0; i38++) {
            b_R1[((((i38 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                  c_input_sizes_idx_0) +
                 b_R1.size(0) * i35] = R3[i38 + e_input_sizes_idx_0 * i35];
        }
    }
    for (int i37{0}; i37 < result; i37++) {
        for (int i39{0}; i39 < f_input_sizes_idx_0; i39++) {
            b_R1[((((i39 + i27) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                  e_input_sizes_idx_0) +
                 b_R1.size(0) * i37] = varargin_6[i39 + f_input_sizes_idx_0 * i37];
        }
    }
    A->parenAssign(b_R1, y, b_y);
    //
    //
    d = 6.0 * static_cast<double>(BasisVal.size(0));
    BasisVal_idx_0 = BasisVal.size(0);
    b_BasisVal_idx_0 = BasisVal.size(0);
    c_BasisVal_idx_0 = BasisVal.size(0);
    d_BasisVal_idx_0 = BasisVal.size(0);
    r3.set_size(((((BasisVal.size(0) + BasisVal.size(0)) + BasisVal.size(0)) + BasisVal.size(0)) +
                 BasisVal.size(0)) +
                BasisVal.size(0));
    ab_loop_ub = BasisVal.size(0);
    for (int i40{0}; i40 < ab_loop_ub; i40++) {
        r3[i40] = jmax[0];
    }
    bb_loop_ub = BasisVal.size(0);
    for (int i41{0}; i41 < bb_loop_ub; i41++) {
        r3[i41 + BasisVal_idx_0] = jmax[0];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i42{0}; i42 < cb_loop_ub; i42++) {
        r3[(i42 + BasisVal_idx_0) + b_BasisVal_idx_0] = jmax[1];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i43{0}; i43 < db_loop_ub; i43++) {
        r3[((i43 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0] = jmax[1];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i44{0}; i44 < eb_loop_ub; i44++) {
        r3[(((i44 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0] =
            jmax[2];
    }
    fb_loop_ub = BasisVal.size(0);
    for (int i45{0}; i45 < fb_loop_ub; i45++) {
        r3[((((i45 + BasisVal_idx_0) + b_BasisVal_idx_0) + c_BasisVal_idx_0) + d_BasisVal_idx_0) +
           BasisVal.size(0)] = jmax[2];
    }
    if (1.0 > d) {
        gb_loop_ub = 0;
    } else {
        gb_loop_ub = static_cast<int>(d);
    }
    for (int i46{0}; i46 < gb_loop_ub; i46++) {
        b[i46] = r3[i46];
    }
    //
    i47 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_mc = BasisVal.size(0) - 1;
        b_inner = BasisVal.size(1);
    }
    for (int c_k{0}; c_k <= i47 - 2; c_k++) {
        double a;
        double a_tmp;
        double b_tmp;
        double c_b;
        int ac_loop_ub;
        int b_result;
        int cc_loop_ub;
        int gc_loop_ub;
        int h_input_sizes_idx_0;
        int hb_loop_ub;
        int i49;
        int i85;
        int i86;
        int i_input_sizes_idx_0;
        int ib_loop_ub;
        int j_input_sizes_idx_0;
        int jb_loop_ub;
        int k_input_sizes_idx_0;
        int kb_loop_ub;
        int l_input_sizes_idx_0;
        int lb_loop_ub;
        int m_input_sizes_idx_0;
        int nb_loop_ub;
        int ob_loop_ub;
        int pb_loop_ub;
        int qb_loop_ub;
        int sb_loop_ub;
        int tb_loop_ub;
        int ub_loop_ub;
        int vb_loop_ub;
        int xb_loop_ub;
        bool b_empty_non_axis_sizes;
        c_u_vec.set_size(1, u_vec.size(1));
        hb_loop_ub = u_vec.size(1) - 1;
        for (int i48{0}; i48 <= hb_loop_ub; i48++) {
            c_u_vec[i48] = u_vec[i48];
        }
        b_EvalCurvStruct(ctx_q_splines, CurvStructs[c_k + 1].Type, CurvStructs[c_k + 1].P0,
                         CurvStructs[c_k + 1].P1, CurvStructs[c_k + 1].CorrectedHelixCenter,
                         CurvStructs[c_k + 1].evec, CurvStructs[c_k + 1].theta,
                         CurvStructs[c_k + 1].pitch, CurvStructs[c_k + 1].CoeffP5,
                         CurvStructs[c_k + 1].sp_index, CurvStructs[c_k + 1].a_param,
                         CurvStructs[c_k + 1].b_param, c_u_vec, a__2, r1D, r2D, r3D);
        //
        //      q_opt  = Function(Bl, Coeff(:, k+1));
        //      q_val  = q_opt.fast_eval(u_vec);
        //
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
        i49 = y_tmp.size(0);
        for (int e_k{0}; e_k < i49; e_k++) {
            y_tmp[e_k] = std::sqrt(y_tmp[e_k]);
        }
        sqrt_calls++;
        ib_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i50{0}; i50 < ib_loop_ub; i50++) {
            b_r3D[i50] = r3D[3 * i50];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        jb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i51{0}; i51 < jb_loop_ub; i51++) {
            b_r2D[i51] = r2D[3 * i51];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        kb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i52{0}; i52 < kb_loop_ub; i52++) {
            b_r1D[i52] = r1D[3 * i52];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        lb_loop_ub = r.size(1);
        for (int i53{0}; i53 < lb_loop_ub; i53++) {
            int mb_loop_ub;
            mb_loop_ub = r.size(0);
            for (int i54{0}; i54 < mb_loop_ub; i54++) {
                r[i54 + r.size(0) * i53] =
                    (r[i54 + r.size(0) * i53] + 1.5 * r1[i54 + r1.size(0) * i53]) +
                    0.5 * r2[i54 + r2.size(0) * i53];
            }
        }
        coder::bsxfun(r, y_tmp, R1);
        sqrt_calls++;
        nb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i55{0}; i55 < nb_loop_ub; i55++) {
            b_r3D[i55] = r3D[3 * i55 + 1];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        ob_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i56{0}; i56 < ob_loop_ub; i56++) {
            b_r2D[i56] = r2D[3 * i56 + 1];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        pb_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i57{0}; i57 < pb_loop_ub; i57++) {
            b_r1D[i57] = r1D[3 * i57 + 1];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        qb_loop_ub = r.size(1);
        for (int i58{0}; i58 < qb_loop_ub; i58++) {
            int rb_loop_ub;
            rb_loop_ub = r.size(0);
            for (int i59{0}; i59 < rb_loop_ub; i59++) {
                r[i59 + r.size(0) * i58] =
                    (r[i59 + r.size(0) * i58] + 1.5 * r1[i59 + r1.size(0) * i58]) +
                    0.5 * r2[i59 + r2.size(0) * i58];
            }
        }
        coder::bsxfun(r, y_tmp, R2);
        sqrt_calls++;
        sb_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i60{0}; i60 < sb_loop_ub; i60++) {
            b_r3D[i60] = r3D[3 * i60 + 2];
        }
        coder::bsxfun(BasisVal, b_r3D, r);
        tb_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i61{0}; i61 < tb_loop_ub; i61++) {
            b_r2D[i61] = r2D[3 * i61 + 2];
        }
        coder::bsxfun(BasisValD, b_r2D, r1);
        ub_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i62{0}; i62 < ub_loop_ub; i62++) {
            b_r1D[i62] = r1D[3 * i62 + 2];
        }
        coder::bsxfun(BasisValDD, b_r1D, r2);
        vb_loop_ub = r.size(1);
        for (int i63{0}; i63 < vb_loop_ub; i63++) {
            int wb_loop_ub;
            wb_loop_ub = r.size(0);
            for (int i64{0}; i64 < wb_loop_ub; i64++) {
                r[i64 + r.size(0) * i63] =
                    (r[i64 + r.size(0) * i63] + 1.5 * r1[i64 + r1.size(0) * i63]) +
                    0.5 * r2[i64 + r2.size(0) * i63];
            }
        }
        coder::bsxfun(r, y_tmp, R3);
        //      R2 = (BasisVal .* r3D(2, :)' + ...
        //            1.5*BasisValD .* r2D(2, :)' + ...
        //            0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
        //      R3 = (BasisVal .* r3D(3, :)' + ...
        //            1.5*BasisValD .* r2D(3, :)' + ...
        //            0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
        //
        b_varargin_2.set_size(R1.size(0), R1.size(1));
        xb_loop_ub = R1.size(1);
        for (int i65{0}; i65 < xb_loop_ub; i65++) {
            int yb_loop_ub;
            yb_loop_ub = R1.size(0);
            for (int i66{0}; i66 < yb_loop_ub; i66++) {
                b_varargin_2[i66 + b_varargin_2.size(0) * i65] = -R1[i66 + R1.size(0) * i65];
            }
        }
        varargin_4.set_size(R2.size(0), R2.size(1));
        ac_loop_ub = R2.size(1);
        for (int i67{0}; i67 < ac_loop_ub; i67++) {
            int bc_loop_ub;
            bc_loop_ub = R2.size(0);
            for (int i68{0}; i68 < bc_loop_ub; i68++) {
                varargin_4[i68 + varargin_4.size(0) * i67] = -R2[i68 + R2.size(0) * i67];
            }
        }
        varargin_6.set_size(R3.size(0), R3.size(1));
        cc_loop_ub = R3.size(1);
        for (int i69{0}; i69 < cc_loop_ub; i69++) {
            int dc_loop_ub;
            dc_loop_ub = R3.size(0);
            for (int i70{0}; i70 < dc_loop_ub; i70++) {
                varargin_6[i70 + varargin_6.size(0) * i69] = -R3[i70 + R3.size(0) * i69];
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
            for (int i71{0}; i71 <= ec_loop_ub; i71++) {
                y[i71] = a_tmp + static_cast<double>(i71);
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
            for (int i72{0}; i72 <= fc_loop_ub; i72++) {
                b_y[i72] = a + static_cast<double>(i72);
            }
        }
        b_R1.set_size(((((h_input_sizes_idx_0 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                        k_input_sizes_idx_0) +
                       l_input_sizes_idx_0) +
                          m_input_sizes_idx_0,
                      b_result);
        for (int i73{0}; i73 < b_result; i73++) {
            for (int i75{0}; i75 < h_input_sizes_idx_0; i75++) {
                b_R1[i75 + b_R1.size(0) * i73] = R1[i75 + h_input_sizes_idx_0 * i73];
            }
        }
        for (int i74{0}; i74 < b_result; i74++) {
            for (int i77{0}; i77 < i_input_sizes_idx_0; i77++) {
                b_R1[(i77 + h_input_sizes_idx_0) + b_R1.size(0) * i74] =
                    b_varargin_2[i77 + i_input_sizes_idx_0 * i74];
            }
        }
        for (int i76{0}; i76 < b_result; i76++) {
            for (int i79{0}; i79 < j_input_sizes_idx_0; i79++) {
                b_R1[((i79 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + b_R1.size(0) * i76] =
                    R2[i79 + j_input_sizes_idx_0 * i76];
            }
        }
        for (int i78{0}; i78 < b_result; i78++) {
            for (int i81{0}; i81 < k_input_sizes_idx_0; i81++) {
                b_R1[(((i81 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                     b_R1.size(0) * i78] = varargin_4[i81 + k_input_sizes_idx_0 * i78];
            }
        }
        for (int i80{0}; i80 < b_result; i80++) {
            for (int i83{0}; i83 < l_input_sizes_idx_0; i83++) {
                b_R1[((((i83 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                      k_input_sizes_idx_0) +
                     b_R1.size(0) * i80] = R3[i83 + l_input_sizes_idx_0 * i80];
            }
        }
        for (int i82{0}; i82 < b_result; i82++) {
            for (int i84{0}; i84 < m_input_sizes_idx_0; i84++) {
                b_R1[(((((i84 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                       k_input_sizes_idx_0) +
                      l_input_sizes_idx_0) +
                     b_R1.size(0) * i82] = varargin_6[i84 + m_input_sizes_idx_0 * i82];
            }
        }
        A->parenAssign(b_R1, y, b_y);
        //
        if (a_tmp > b_tmp) {
            i85 = -1;
            i86 = 0;
        } else {
            i85 = static_cast<int>(a_tmp) - 2;
            i86 = static_cast<int>(b_tmp);
        }
        gc_loop_ub = (i86 - i85) - 1;
        for (int i87{0}; i87 < gc_loop_ub; i87++) {
            b[(i85 + i87) + 1] = r3[i87];
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
