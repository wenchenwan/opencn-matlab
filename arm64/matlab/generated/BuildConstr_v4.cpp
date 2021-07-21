//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstr_v4.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "BuildConstr_v4.h"
#include "DebugLog.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "bspline_base_eval.h"
#include "bsxfun.h"
#include "mtimes.h"
#include "norm.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const queue_coder *ctx_q_splines
//                bool ctx_cfg_UseDynamicBreakpoints
//                bool ctx_cfg_UseLinearBreakpoints
//                double ctx_cfg_DynamicBreakpointsDistance
//                int ctx_cfg_SplineDegree
//                double ctx_cfg_NGridLengthSpline
//                int ctx_Bl_ncoeff
//                unsigned long ctx_Bl_handle
//                const ::coder::array<CurvStruct, 2U> &CurvStructs
//                const double amax[3]
//                double v_0
//                double at_0
//                double v_1
//                double at_1
//                ::coder::array<double, 2U> &BasisVal
//                ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &u_vec
//                coder::sparse *A
//                ::coder::array<double, 1U> &b
//                ::coder::array<double, 2U> &Aeq
//                ::coder::array<double, 1U> &beq
// Return Type  : void
//
namespace ocn {
void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
                    bool ctx_cfg_UseLinearBreakpoints, double ctx_cfg_DynamicBreakpointsDistance,
                    int ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff,
                    unsigned long ctx_Bl_handle, const ::coder::array<CurvStruct, 2U> &CurvStructs,
                    const double amax[3], double v_0, double at_0, double v_1, double at_1,
                    ::coder::array<double, 2U> &BasisVal, ::coder::array<double, 2U> &BasisValD,
                    const ::coder::array<double, 2U> &u_vec, coder::sparse *A,
                    ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq,
                    ::coder::array<double, 1U> &beq)
{
    ::coder::array<double, 2U> R1;
    ::coder::array<double, 2U> R2;
    ::coder::array<double, 2U> R3;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> b_BasisVal;
    ::coder::array<double, 2U> b_u_vec;
    ::coder::array<double, 2U> b_y;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> c_u_vec;
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1D_sqnorm;
    ::coder::array<double, 2U> r1Dn;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r2Dn;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> varargin_3;
    ::coder::array<double, 2U> varargin_5;
    ::coder::array<double, 2U> varargin_7;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> bC2;
    ::coder::array<double, 1U> bC3;
    ::coder::array<double, 1U> bC4;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> b_r1Dn;
    ::coder::array<double, 1U> b_r2D;
    ::coder::array<double, 1U> b_r2Dn;
    double c_r1D[3];
    double t_1[3];
    double a;
    double b_a;
    double b_b;
    double c_a;
    double d1;
    double d2;
    double d_a;
    double e_a;
    double f_a;
    double h_a;
    double i_a;
    double j_a;
    double k_a;
    double l_a;
    double m_a;
    double x;
    unsigned long Bl_handle;
    int Bl_ncoeff;
    int N;
    int ab_loop_ub;
    int ac_loop_ub;
    int b_N;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_unnamed_idx_0;
    int b_unnamed_idx_1;
    int bb_loop_ub;
    int c_input_sizes_idx_0;
    int c_loop_ub;
    int c_unnamed_idx_1;
    int cb_loop_ub;
    int d_input_sizes_idx_0;
    int d_loop_ub;
    int d_r1D;
    int d_unnamed_idx_1;
    int db_loop_ub;
    int e_input_sizes_idx_0;
    int e_loop_ub;
    int e_unnamed_idx_1;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int f_unnamed_idx_1;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int g_loop_ub;
    int gb_loop_ub;
    int h_input_sizes_idx_0;
    int h_loop_ub;
    int hb_loop_ub;
    int i26;
    int i27;
    int i57;
    int i61;
    int i_loop_ub;
    int ib_loop_ub;
    int input_sizes_idx_0;
    int jb_loop_ub;
    int k_loop_ub;
    int kb_loop_ub;
    int l_loop_ub;
    int lb_loop_ub;
    int loop_ub;
    int mb_loop_ub;
    int n_loop_ub;
    int ob_loop_ub;
    int p_loop_ub;
    int pb_loop_ub;
    int qb_loop_ub;
    int r_loop_ub;
    int rb_loop_ub;
    int result;
    int sb_loop_ub;
    int tb_loop_ub;
    int ub_loop_ub;
    int unnamed_idx_0;
    int unnamed_idx_1;
    int v_loop_ub;
    int w_loop_ub;
    int x_loop_ub;
    int xb_loop_ub;
    int y_loop_ub;
    bool empty_non_axis_sizes;
    DebugLog(CurvStructs.size(1), amax[0], amax[1], amax[2], v_0, at_0, v_1, at_1);
    Bl_ncoeff = ctx_Bl_ncoeff;
    Bl_handle = ctx_Bl_handle;
    if (ctx_cfg_UseDynamicBreakpoints) {
        double varargin_1;
        varargin_1 =
            LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[0].Type,
                       CurvStructs[0].P0, CurvStructs[0].P1, CurvStructs[0].CorrectedHelixCenter,
                       CurvStructs[0].evec, CurvStructs[0].theta, CurvStructs[0].pitch,
                       CurvStructs[0].CoeffP5, CurvStructs[0].sp_index, CurvStructs[0].a_param,
                       CurvStructs[0].b_param) /
            ctx_cfg_DynamicBreakpointsDistance;
        if (ctx_cfg_UseLinearBreakpoints) {
            double delta1;
            int i;
            breakpoints.set_size(1, static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)));
            breakpoints[static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)) - 1] = 1.0;
            breakpoints[0] = 0.0;
            delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
            i = breakpoints.size(1);
            for (int k{0}; k <= i - 3; k++) {
                breakpoints[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
            }
            Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
            c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                              breakpoints.size(1));
        }
        bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
    }
    N = BasisVal.size(1);
    //
    coder::b_sparse(
        7.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size(1)),
        static_cast<double>(BasisVal.size(1)) * static_cast<double>(CurvStructs.size(1)), A);
    //  preallocation
    unnamed_idx_0 = static_cast<int>(7.0 * static_cast<double>(BasisVal.size(0)) *
                                     static_cast<double>(CurvStructs.size(1)));
    b.set_size(unnamed_idx_0);
    for (int i1{0}; i1 < unnamed_idx_0; i1++) {
        b[i1] = 0.0;
    }
    //  preallocation
    b_unnamed_idx_0 = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
    unnamed_idx_1 = static_cast<int>(static_cast<double>(BasisVal.size(1)) *
                                     static_cast<double>(CurvStructs.size(1)));
    Aeq.set_size(b_unnamed_idx_0, unnamed_idx_1);
    for (int i2{0}; i2 < unnamed_idx_1; i2++) {
        for (int i3{0}; i3 < b_unnamed_idx_0; i3++) {
            Aeq[i3 + Aeq.size(0) * i2] = 0.0;
        }
    }
    //  preallocation
    unnamed_idx_0 = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
    beq.set_size(unnamed_idx_0);
    for (int i4{0}; i4 < unnamed_idx_0; i4++) {
        beq[i4] = 0.0;
    }
    //  preallocation
    //  coder.varsize('b', [7*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
    //  coder.varsize('Aeq', [2*(FeedoptLimits.MaxNHorz+1),
    //  FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); coder.varsize('beq',
    //  [2*(FeedoptLimits.MaxNHorz+1), 1], [1,0]);
    //
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i5{0}; i5 <= loop_ub; i5++) {
        b_u_vec[i5] = u_vec[i5];
    }
    b_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                     CurvStructs[0].CorrectedHelixCenter, CurvStructs[0].evec, CurvStructs[0].theta,
                     CurvStructs[0].pitch, CurvStructs[0].CoeffP5, CurvStructs[0].sp_index,
                     CurvStructs[0].a_param, CurvStructs[0].b_param, b_u_vec, a__1, r1D, r2D);
    r.set_size(3, r1D.size(1));
    b_N = r1D.size(1);
    for (int b_k{0}; b_k < b_N; b_k++) {
        r[3 * b_k] = std::pow(r1D[3 * b_k], 2.0);
        r[3 * b_k + 1] = std::pow(r1D[3 * b_k + 1], 2.0);
        r[3 * b_k + 2] = std::pow(r1D[3 * b_k + 2], 2.0);
    }
    coder::sum(r, r1D_sqnorm);
    //  squared norm
    //
    //  unit tangent vector @ start
    //
    //
    b_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i6{0}; i6 < b_loop_ub; i6++) {
        b_r2D[i6] = r2D[3 * i6];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    c_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        b_r1D[i7] = r1D[3 * i7];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    R1.set_size(r1.size(0), r1.size(1));
    d_loop_ub = r1.size(1);
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        int f_loop_ub;
        f_loop_ub = r1.size(0);
        for (int i9{0}; i9 < f_loop_ub; i9++) {
            R1[i9 + R1.size(0) * i8] = r1[i9 + r1.size(0) * i8] + 0.5 * r2[i9 + r2.size(0) * i8];
        }
    }
    e_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        b_r2D[i10] = r2D[3 * i10 + 1];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    g_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i11{0}; i11 < g_loop_ub; i11++) {
        b_r1D[i11] = r1D[3 * i11 + 1];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    R2.set_size(r1.size(0), r1.size(1));
    h_loop_ub = r1.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int j_loop_ub;
        j_loop_ub = r1.size(0);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            R2[i13 + R2.size(0) * i12] =
                r1[i13 + r1.size(0) * i12] + 0.5 * r2[i13 + r2.size(0) * i12];
        }
    }
    i_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i14{0}; i14 < i_loop_ub; i14++) {
        b_r2D[i14] = r2D[3 * i14 + 2];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    k_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i15{0}; i15 < k_loop_ub; i15++) {
        b_r1D[i15] = r1D[3 * i15 + 2];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    R3.set_size(r1.size(0), r1.size(1));
    l_loop_ub = r1.size(1);
    for (int i16{0}; i16 < l_loop_ub; i16++) {
        int m_loop_ub;
        m_loop_ub = r1.size(0);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            R3[i17 + R3.size(0) * i16] =
                r1[i17 + r1.size(0) * i16] + 0.5 * r2[i17 + r2.size(0) * i16];
        }
    }
    //
    varargin_3.set_size(R1.size(0), R1.size(1));
    n_loop_ub = R1.size(1);
    for (int i18{0}; i18 < n_loop_ub; i18++) {
        int o_loop_ub;
        o_loop_ub = R1.size(0);
        for (int i19{0}; i19 < o_loop_ub; i19++) {
            varargin_3[i19 + varargin_3.size(0) * i18] = -R1[i19 + R1.size(0) * i18];
        }
    }
    varargin_5.set_size(R2.size(0), R2.size(1));
    p_loop_ub = R2.size(1);
    for (int i20{0}; i20 < p_loop_ub; i20++) {
        int q_loop_ub;
        q_loop_ub = R2.size(0);
        for (int i21{0}; i21 < q_loop_ub; i21++) {
            varargin_5[i21 + varargin_5.size(0) * i20] = -R2[i21 + R2.size(0) * i20];
        }
    }
    varargin_7.set_size(R3.size(0), R3.size(1));
    r_loop_ub = R3.size(1);
    for (int i22{0}; i22 < r_loop_ub; i22++) {
        int s_loop_ub;
        s_loop_ub = R3.size(0);
        for (int i23{0}; i23 < s_loop_ub; i23++) {
            varargin_7[i23 + varargin_7.size(0) * i22] = -R3[i23 + R3.size(0) * i22];
        }
    }
    if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
        result = BasisVal.size(1);
    } else if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
        result = R1.size(1);
    } else if ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)) {
        result = varargin_3.size(1);
    } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
        result = R2.size(1);
    } else if ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)) {
        result = varargin_5.size(1);
    } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
        result = R3.size(1);
    } else if ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)) {
        result = varargin_7.size(1);
    } else {
        result = BasisVal.size(1);
        if (R1.size(1) > BasisVal.size(1)) {
            result = R1.size(1);
        }
        if (varargin_3.size(1) > result) {
            result = varargin_3.size(1);
        }
        if (R2.size(1) > result) {
            result = R2.size(1);
        }
        if (varargin_5.size(1) > result) {
            result = varargin_5.size(1);
        }
        if (R3.size(1) > result) {
            result = R3.size(1);
        }
        if (varargin_7.size(1) > result) {
            result = varargin_7.size(1);
        }
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
        input_sizes_idx_0 = BasisVal.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
        b_input_sizes_idx_0 = R1.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0))) {
        c_input_sizes_idx_0 = varargin_3.size(0);
    } else {
        c_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
        d_input_sizes_idx_0 = R2.size(0);
    } else {
        d_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0))) {
        e_input_sizes_idx_0 = varargin_5.size(0);
    } else {
        e_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
        f_input_sizes_idx_0 = R3.size(0);
    } else {
        f_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0))) {
        g_input_sizes_idx_0 = varargin_7.size(0);
    } else {
        g_input_sizes_idx_0 = 0;
    }
    b_b = 7.0 * static_cast<double>(BasisVal.size(0));
    if (b_b < 1.0) {
        y.set_size(1, 0);
    } else {
        int t_loop_ub;
        y.set_size(1, static_cast<int>(b_b - 1.0) + 1);
        t_loop_ub = static_cast<int>(b_b - 1.0);
        for (int i24{0}; i24 <= t_loop_ub; i24++) {
            y[i24] = static_cast<double>(i24) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int u_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        u_loop_ub = BasisVal.size(1) - 1;
        for (int i25{0}; i25 <= u_loop_ub; i25++) {
            b_y[i25] = static_cast<double>(i25) + 1.0;
        }
    }
    h_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    d_input_sizes_idx_0 = e_input_sizes_idx_0;
    i26 = h_input_sizes_idx_0 + input_sizes_idx_0;
    i27 = i26 + b_input_sizes_idx_0;
    b_BasisVal.set_size(
        (((i27 + c_input_sizes_idx_0) + d_input_sizes_idx_0) + f_input_sizes_idx_0) +
            g_input_sizes_idx_0,
        result);
    for (int i28{0}; i28 < result; i28++) {
        for (int i30{0}; i30 < h_input_sizes_idx_0; i30++) {
            b_BasisVal[i30 + b_BasisVal.size(0) * i28] = BasisVal[i30 + h_input_sizes_idx_0 * i28];
        }
    }
    for (int i29{0}; i29 < result; i29++) {
        for (int i32{0}; i32 < input_sizes_idx_0; i32++) {
            b_BasisVal[(i32 + h_input_sizes_idx_0) + b_BasisVal.size(0) * i29] =
                R1[i32 + input_sizes_idx_0 * i29];
        }
    }
    for (int i31{0}; i31 < result; i31++) {
        for (int i34{0}; i34 < b_input_sizes_idx_0; i34++) {
            b_BasisVal[((i34 + h_input_sizes_idx_0) + input_sizes_idx_0) +
                       b_BasisVal.size(0) * i31] = varargin_3[i34 + b_input_sizes_idx_0 * i31];
        }
    }
    for (int i33{0}; i33 < result; i33++) {
        for (int i36{0}; i36 < c_input_sizes_idx_0; i36++) {
            b_BasisVal[(((i36 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i33] = R2[i36 + c_input_sizes_idx_0 * i33];
        }
    }
    for (int i35{0}; i35 < result; i35++) {
        for (int i38{0}; i38 < d_input_sizes_idx_0; i38++) {
            b_BasisVal[((((i38 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                        c_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i35] = varargin_5[i38 + d_input_sizes_idx_0 * i35];
        }
    }
    for (int i37{0}; i37 < result; i37++) {
        for (int i40{0}; i40 < f_input_sizes_idx_0; i40++) {
            b_BasisVal[((((i40 + i26) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                        d_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i37] = R3[i40 + f_input_sizes_idx_0 * i37];
        }
    }
    for (int i39{0}; i39 < result; i39++) {
        for (int i41{0}; i41 < g_input_sizes_idx_0; i41++) {
            b_BasisVal[((((i41 + i27) + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                        f_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i39] = varargin_7[i41 + g_input_sizes_idx_0 * i39];
        }
    }
    A->parenAssign(b_BasisVal, y, b_y);
    //
    x = std::pow(CurvStructs[0].FeedRate, 2.0);
    bC2.set_size(BasisVal.size(0));
    v_loop_ub = BasisVal.size(0);
    for (int i42{0}; i42 < v_loop_ub; i42++) {
        bC2[i42] = amax[0];
    }
    bC3.set_size(BasisVal.size(0));
    w_loop_ub = BasisVal.size(0);
    for (int i43{0}; i43 < w_loop_ub; i43++) {
        bC3[i43] = amax[1];
    }
    bC4.set_size(BasisVal.size(0));
    x_loop_ub = BasisVal.size(0);
    for (int i44{0}; i44 < x_loop_ub; i44++) {
        bC4[i44] = amax[2];
    }
    //
    unnamed_idx_1 = r1D_sqnorm.size(1);
    b_unnamed_idx_1 = BasisVal.size(0);
    c_unnamed_idx_1 = BasisVal.size(0);
    d_unnamed_idx_1 = BasisVal.size(0);
    e_unnamed_idx_1 = BasisVal.size(0);
    f_unnamed_idx_1 = BasisVal.size(0);
    y_loop_ub = r1D_sqnorm.size(1);
    for (int i45{0}; i45 < y_loop_ub; i45++) {
        b[i45] = x / r1D_sqnorm[i45];
    }
    ab_loop_ub = BasisVal.size(0);
    for (int i46{0}; i46 < ab_loop_ub; i46++) {
        b[i46 + unnamed_idx_1] = amax[0];
    }
    bb_loop_ub = BasisVal.size(0);
    for (int i47{0}; i47 < bb_loop_ub; i47++) {
        b[(i47 + unnamed_idx_1) + b_unnamed_idx_1] = amax[0];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i48{0}; i48 < cb_loop_ub; i48++) {
        b[((i48 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = amax[1];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i49{0}; i49 < db_loop_ub; i49++) {
        b[(((i49 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1] =
            amax[1];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i50{0}; i50 < eb_loop_ub; i50++) {
        b[((((i50 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
          e_unnamed_idx_1] = amax[2];
    }
    fb_loop_ub = BasisVal.size(0);
    for (int i51{0}; i51 < fb_loop_ub; i51++) {
        b[(((((i51 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
           e_unnamed_idx_1) +
          f_unnamed_idx_1] = amax[2];
    }
    double d;
    //
    a = r2D[0];
    b_a = 0.5 * r1D[0];
    c_a = r2D[1];
    d_a = 0.5 * r1D[1];
    e_a = r2D[2];
    f_a = 0.5 * r1D[2];
    d = coder::b_norm(*(double(*)[3]) & r1D[0]);
    c_r1D[0] = r1D[0] / d;
    c_r1D[1] = r1D[1] / d;
    c_r1D[2] = r1D[2] / d;
    gb_loop_ub = BasisVal.size(1);
    hb_loop_ub = BasisVal.size(1);
    ib_loop_ub = BasisVal.size(1);
    g_a.set_size(3, BasisVal.size(1));
    for (int i52{0}; i52 < gb_loop_ub; i52++) {
        g_a[3 * i52] =
            a * BasisVal[BasisVal.size(0) * i52] + b_a * BasisValD[BasisValD.size(0) * i52];
    }
    for (int i53{0}; i53 < hb_loop_ub; i53++) {
        g_a[3 * i53 + 1] =
            c_a * BasisVal[BasisVal.size(0) * i53] + d_a * BasisValD[BasisValD.size(0) * i53];
    }
    for (int i54{0}; i54 < ib_loop_ub; i54++) {
        g_a[3 * i54 + 2] =
            e_a * BasisVal[BasisVal.size(0) * i54] + f_a * BasisValD[BasisValD.size(0) * i54];
    }
    coder::internal::blas::mtimes(c_r1D, g_a, r3);
    jb_loop_ub = BasisVal.size(1);
    for (int i55{0}; i55 < jb_loop_ub; i55++) {
        Aeq[Aeq.size(0) * i55] = BasisVal[BasisVal.size(0) * i55];
    }
    kb_loop_ub = r3.size(1);
    for (int i56{0}; i56 < kb_loop_ub; i56++) {
        Aeq[Aeq.size(0) * i56 + 1] = r3[i56];
    }
    beq[0] = std::pow(v_0, 2.0) / r1D_sqnorm[0];
    beq[1] = at_0;
    //  This should be the correct behavior for a single segment,
    //  reusing the r1D norm
    i57 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_unnamed_idx_1 = bC2.size(0);
        c_unnamed_idx_1 = bC2.size(0);
        d_unnamed_idx_1 = bC3.size(0);
        e_unnamed_idx_1 = bC3.size(0);
        f_unnamed_idx_1 = bC4.size(0);
        lb_loop_ub = bC2.size(0);
        mb_loop_ub = bC2.size(0);
        ob_loop_ub = bC3.size(0);
        pb_loop_ub = bC3.size(0);
        qb_loop_ub = bC4.size(0);
        rb_loop_ub = bC4.size(0);
    }
    for (int c_k{0}; c_k <= i57 - 2; c_k++) {
        double a_tmp;
        double ab_a;
        double b_tmp;
        double b_x;
        double bb_a;
        double c;
        double c_b;
        double cb_a;
        double d10;
        double d4;
        double d5;
        double d6;
        double d7;
        double d_b;
        double n_a;
        double o_a;
        double p_a;
        double q_a;
        double r_a;
        double s_a;
        double t_a;
        double u_a;
        double v_a;
        double w_a;
        double x_a;
        double y_a;
        int ad_loop_ub;
        int b_result;
        int bc_loop_ub;
        int bd_loop_ub;
        int c_N;
        int dc_loop_ub;
        int ec_loop_ub;
        int fc_loop_ub;
        int hc_loop_ub;
        int i101;
        int i109;
        int i110;
        int i112;
        int i114;
        int i117;
        int i_input_sizes_idx_0;
        int ic_loop_ub;
        int j_input_sizes_idx_0;
        int k_input_sizes_idx_0;
        int kc_loop_ub;
        int l_input_sizes_idx_0;
        int m_input_sizes_idx_0;
        int mc_loop_ub;
        int n_input_sizes_idx_0;
        int nb_loop_ub;
        int o_input_sizes_idx_0;
        int oc_loop_ub;
        int sc_loop_ub;
        int tc_loop_ub;
        int uc_loop_ub;
        int vb_loop_ub;
        int vc_loop_ub;
        int wb_loop_ub;
        int wc_loop_ub;
        int xc_loop_ub;
        int yb_loop_ub;
        int yc_loop_ub;
        bool b_empty_non_axis_sizes;
        if (ctx_cfg_UseDynamicBreakpoints) {
            double varargin_2;
            varargin_2 =
                LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[c_k + 1].Type,
                           CurvStructs[c_k + 1].P0, CurvStructs[c_k + 1].P1,
                           CurvStructs[c_k + 1].CorrectedHelixCenter, CurvStructs[c_k + 1].evec,
                           CurvStructs[c_k + 1].theta, CurvStructs[c_k + 1].pitch,
                           CurvStructs[c_k + 1].CoeffP5, CurvStructs[c_k + 1].sp_index,
                           CurvStructs[c_k + 1].a_param, CurvStructs[c_k + 1].b_param) /
                ctx_cfg_DynamicBreakpointsDistance;
            if (ctx_cfg_UseLinearBreakpoints) {
                double b_delta1;
                int i58;
                int i60;
                i58 = static_cast<int>(std::fmax(4.0, std::floor(varargin_2)));
                breakpoints.set_size(1, i58);
                breakpoints[i58 - 1] = 1.0;
                breakpoints[0] = 0.0;
                b_delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
                i60 = breakpoints.size(1);
                for (int d_k{0}; d_k <= i60 - 3; d_k++) {
                    breakpoints[d_k + 1] = (static_cast<double>(d_k) + 1.0) * b_delta1;
                }
                Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
                c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                                  breakpoints.size(1));
            }
            bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
        }
        N = BasisVal.size(1);
        c_u_vec.set_size(1, u_vec.size(1));
        nb_loop_ub = u_vec.size(1) - 1;
        for (int i59{0}; i59 <= nb_loop_ub; i59++) {
            c_u_vec[i59] = u_vec[i59];
        }
        b_EvalCurvStruct(ctx_q_splines, CurvStructs[c_k + 1].Type, CurvStructs[c_k + 1].P0,
                         CurvStructs[c_k + 1].P1, CurvStructs[c_k + 1].CorrectedHelixCenter,
                         CurvStructs[c_k + 1].evec, CurvStructs[c_k + 1].theta,
                         CurvStructs[c_k + 1].pitch, CurvStructs[c_k + 1].CoeffP5,
                         CurvStructs[c_k + 1].sp_index, CurvStructs[c_k + 1].a_param,
                         CurvStructs[c_k + 1].b_param, c_u_vec, a__2, r1Dn, r2Dn);
        r4.set_size(3, r1Dn.size(1));
        c_N = r1Dn.size(1);
        for (int e_k{0}; e_k < c_N; e_k++) {
            r4[3 * e_k] = std::pow(r1Dn[3 * e_k], 2.0);
            r4[3 * e_k + 1] = std::pow(r1Dn[3 * e_k + 1], 2.0);
            r4[3 * e_k + 2] = std::pow(r1Dn[3 * e_k + 2], 2.0);
        }
        double d3;
        int e_r1D;
        coder::sum(r4, r1D_sqnorm);
        //  squared norm
        b_x = std::pow(CurvStructs[c_k + 1].FeedRate, 2.0);
        e_r1D = r1D.size(1);
        d3 = coder::b_norm(*(double(*)[3]) & r1D[3 * (e_r1D - 1)]);
        t_1[0] = r1D[3 * (r1D.size(1) - 1)] / d3;
        t_1[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d3;
        t_1[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d3;
        //  unit tangent vector @ end of previous piece
        //
        vb_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i63{0}; i63 < vb_loop_ub; i63++) {
            b_r2Dn[i63] = r2Dn[3 * i63];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        wb_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i66{0}; i66 < wb_loop_ub; i66++) {
            b_r1Dn[i66] = r1Dn[3 * i66];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        R1.set_size(r1.size(0), r1.size(1));
        yb_loop_ub = r1.size(1);
        for (int i68{0}; i68 < yb_loop_ub; i68++) {
            int cc_loop_ub;
            cc_loop_ub = r1.size(0);
            for (int i70{0}; i70 < cc_loop_ub; i70++) {
                R1[i70 + R1.size(0) * i68] =
                    r1[i70 + r1.size(0) * i68] + 0.5 * r2[i70 + r2.size(0) * i68];
            }
        }
        bc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i71{0}; i71 < bc_loop_ub; i71++) {
            b_r2Dn[i71] = r2Dn[3 * i71 + 1];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        dc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i72{0}; i72 < dc_loop_ub; i72++) {
            b_r1Dn[i72] = r1Dn[3 * i72 + 1];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        R2.set_size(r1.size(0), r1.size(1));
        ec_loop_ub = r1.size(1);
        for (int i73{0}; i73 < ec_loop_ub; i73++) {
            int gc_loop_ub;
            gc_loop_ub = r1.size(0);
            for (int i74{0}; i74 < gc_loop_ub; i74++) {
                R2[i74 + R2.size(0) * i73] =
                    r1[i74 + r1.size(0) * i73] + 0.5 * r2[i74 + r2.size(0) * i73];
            }
        }
        fc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i75{0}; i75 < fc_loop_ub; i75++) {
            b_r2Dn[i75] = r2Dn[3 * i75 + 2];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        hc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i76{0}; i76 < hc_loop_ub; i76++) {
            b_r1Dn[i76] = r1Dn[3 * i76 + 2];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        R3.set_size(r1.size(0), r1.size(1));
        ic_loop_ub = r1.size(1);
        for (int i77{0}; i77 < ic_loop_ub; i77++) {
            int jc_loop_ub;
            jc_loop_ub = r1.size(0);
            for (int i78{0}; i78 < jc_loop_ub; i78++) {
                R3[i78 + R3.size(0) * i77] =
                    r1[i78 + r1.size(0) * i77] + 0.5 * r2[i78 + r2.size(0) * i77];
            }
        }
        //
        varargin_3.set_size(R1.size(0), R1.size(1));
        kc_loop_ub = R1.size(1);
        for (int i79{0}; i79 < kc_loop_ub; i79++) {
            int lc_loop_ub;
            lc_loop_ub = R1.size(0);
            for (int i80{0}; i80 < lc_loop_ub; i80++) {
                varargin_3[i80 + varargin_3.size(0) * i79] = -R1[i80 + R1.size(0) * i79];
            }
        }
        varargin_5.set_size(R2.size(0), R2.size(1));
        mc_loop_ub = R2.size(1);
        for (int i81{0}; i81 < mc_loop_ub; i81++) {
            int nc_loop_ub;
            nc_loop_ub = R2.size(0);
            for (int i82{0}; i82 < nc_loop_ub; i82++) {
                varargin_5[i82 + varargin_5.size(0) * i81] = -R2[i82 + R2.size(0) * i81];
            }
        }
        varargin_7.set_size(R3.size(0), R3.size(1));
        oc_loop_ub = R3.size(1);
        for (int i83{0}; i83 < oc_loop_ub; i83++) {
            int pc_loop_ub;
            pc_loop_ub = R3.size(0);
            for (int i84{0}; i84 < pc_loop_ub; i84++) {
                varargin_7[i84 + varargin_7.size(0) * i83] = -R3[i84 + R3.size(0) * i83];
            }
        }
        if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
            b_result = BasisVal.size(1);
        } else if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            b_result = R1.size(1);
        } else if ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)) {
            b_result = varargin_3.size(1);
        } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
            b_result = R2.size(1);
        } else if ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)) {
            b_result = varargin_5.size(1);
        } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
            b_result = R3.size(1);
        } else if ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)) {
            b_result = varargin_7.size(1);
        } else {
            b_result = BasisVal.size(1);
            if (R1.size(1) > BasisVal.size(1)) {
                b_result = R1.size(1);
            }
            if (varargin_3.size(1) > b_result) {
                b_result = varargin_3.size(1);
            }
            if (R2.size(1) > b_result) {
                b_result = R2.size(1);
            }
            if (varargin_5.size(1) > b_result) {
                b_result = varargin_5.size(1);
            }
            if (R3.size(1) > b_result) {
                b_result = R3.size(1);
            }
            if (varargin_7.size(1) > b_result) {
                b_result = varargin_7.size(1);
            }
        }
        b_empty_non_axis_sizes = (b_result == 0);
        if (b_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            i_input_sizes_idx_0 = BasisVal.size(0);
        } else {
            i_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
            j_input_sizes_idx_0 = R1.size(0);
        } else {
            j_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0))) {
            k_input_sizes_idx_0 = varargin_3.size(0);
        } else {
            k_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
            l_input_sizes_idx_0 = R2.size(0);
        } else {
            l_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0))) {
            m_input_sizes_idx_0 = varargin_5.size(0);
        } else {
            m_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
            n_input_sizes_idx_0 = R3.size(0);
        } else {
            n_input_sizes_idx_0 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0))) {
            o_input_sizes_idx_0 = varargin_7.size(0);
        } else {
            o_input_sizes_idx_0 = 0;
        }
        a_tmp = (static_cast<double>(c_k) + 1.0) * 7.0;
        n_a = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
        b_tmp = ((static_cast<double>(c_k) + 1.0) + 1.0) * 7.0;
        c_b = b_tmp * static_cast<double>(BasisVal.size(0));
        if (c_b < n_a) {
            y.set_size(1, 0);
        } else {
            int qc_loop_ub;
            qc_loop_ub = static_cast<int>(c_b - n_a);
            y.set_size(1, qc_loop_ub + 1);
            for (int i85{0}; i85 <= qc_loop_ub; i85++) {
                y[i85] = n_a + static_cast<double>(i85);
            }
        }
        o_a = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        d_b = ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1));
        if (d_b < o_a) {
            b_y.set_size(1, 0);
        } else {
            int rc_loop_ub;
            rc_loop_ub = static_cast<int>(d_b - o_a);
            b_y.set_size(1, rc_loop_ub + 1);
            for (int i86{0}; i86 <= rc_loop_ub; i86++) {
                b_y[i86] = o_a + static_cast<double>(i86);
            }
        }
        b_BasisVal.set_size((((((i_input_sizes_idx_0 + j_input_sizes_idx_0) + k_input_sizes_idx_0) +
                               l_input_sizes_idx_0) +
                              m_input_sizes_idx_0) +
                             n_input_sizes_idx_0) +
                                o_input_sizes_idx_0,
                            b_result);
        for (int i87{0}; i87 < b_result; i87++) {
            for (int i89{0}; i89 < i_input_sizes_idx_0; i89++) {
                b_BasisVal[i89 + b_BasisVal.size(0) * i87] =
                    BasisVal[i89 + i_input_sizes_idx_0 * i87];
            }
        }
        for (int i88{0}; i88 < b_result; i88++) {
            for (int i91{0}; i91 < j_input_sizes_idx_0; i91++) {
                b_BasisVal[(i91 + i_input_sizes_idx_0) + b_BasisVal.size(0) * i88] =
                    R1[i91 + j_input_sizes_idx_0 * i88];
            }
        }
        for (int i90{0}; i90 < b_result; i90++) {
            for (int i93{0}; i93 < k_input_sizes_idx_0; i93++) {
                b_BasisVal[((i93 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i90] = varargin_3[i93 + k_input_sizes_idx_0 * i90];
            }
        }
        for (int i92{0}; i92 < b_result; i92++) {
            for (int i95{0}; i95 < l_input_sizes_idx_0; i95++) {
                b_BasisVal[(((i95 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                            k_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i92] = R2[i95 + l_input_sizes_idx_0 * i92];
            }
        }
        for (int i94{0}; i94 < b_result; i94++) {
            for (int i97{0}; i97 < m_input_sizes_idx_0; i97++) {
                b_BasisVal[((((i97 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                             k_input_sizes_idx_0) +
                            l_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i94] = varargin_5[i97 + m_input_sizes_idx_0 * i94];
            }
        }
        for (int i96{0}; i96 < b_result; i96++) {
            for (int i99{0}; i99 < n_input_sizes_idx_0; i99++) {
                b_BasisVal[(((((i99 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                              k_input_sizes_idx_0) +
                             l_input_sizes_idx_0) +
                            m_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i96] = R3[i99 + n_input_sizes_idx_0 * i96];
            }
        }
        for (int i98{0}; i98 < b_result; i98++) {
            for (int i100{0}; i100 < o_input_sizes_idx_0; i100++) {
                b_BasisVal[((((((i100 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                               k_input_sizes_idx_0) +
                              l_input_sizes_idx_0) +
                             m_input_sizes_idx_0) +
                            n_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i98] = varargin_7[i100 + o_input_sizes_idx_0 * i98];
            }
        }
        A->parenAssign(b_BasisVal, y, b_y);
        //
        d4 = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
        if (d4 > b_tmp * static_cast<double>(BasisVal.size(0))) {
            i101 = 0;
        } else {
            i101 = static_cast<int>(d4) - 1;
        }
        unnamed_idx_1 = r1D_sqnorm.size(1);
        sc_loop_ub = r1D_sqnorm.size(1);
        for (int i102{0}; i102 < sc_loop_ub; i102++) {
            b[i101 + i102] = b_x / r1D_sqnorm[i102];
        }
        for (int i103{0}; i103 < lb_loop_ub; i103++) {
            b[(i101 + i103) + unnamed_idx_1] = bC2[i103];
        }
        for (int i104{0}; i104 < mb_loop_ub; i104++) {
            b[((i101 + i104) + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i104];
        }
        for (int i105{0}; i105 < ob_loop_ub; i105++) {
            b[(((i101 + i105) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i105];
        }
        for (int i106{0}; i106 < pb_loop_ub; i106++) {
            b[((((i101 + i106) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
              d_unnamed_idx_1] = bC3[i106];
        }
        for (int i107{0}; i107 < qb_loop_ub; i107++) {
            b[(((((i101 + i107) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
               d_unnamed_idx_1) +
              e_unnamed_idx_1] = bC4[i107];
        }
        for (int i108{0}; i108 < rb_loop_ub; i108++) {
            b[((((((i101 + i108) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                d_unnamed_idx_1) +
               e_unnamed_idx_1) +
              f_unnamed_idx_1] = bC4[i108];
        }
        //
        tc_loop_ub = BasisVal.size(1);
        d5 = ((static_cast<double>(c_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d5 > (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i109 = 1;
        } else {
            i109 = static_cast<int>(d5);
        }
        i110 = static_cast<int>(static_cast<unsigned int>(c_k + 1) << 1);
        p_a = std::pow(
            (t_1[0] * r1D[3 * (r1D.size(1) - 1)] + t_1[1] * r1D[3 * (r1D.size(1) - 1) + 1]) +
                t_1[2] * r1D[3 * (r1D.size(1) - 1) + 2],
            2.0);
        for (int i111{0}; i111 < tc_loop_ub; i111++) {
            Aeq[i110 + Aeq.size(0) * ((i109 + i111) - 1)] =
                p_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i111) - 1];
        }
        uc_loop_ub = BasisVal.size(1);
        d6 = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d6 > ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i112 = 1;
        } else {
            i112 = static_cast<int>(d6);
        }
        c = std::pow((t_1[0] * r1Dn[0] + t_1[1] * r1Dn[1]) + t_1[2] * r1Dn[2], 2.0);
        for (int i113{0}; i113 < uc_loop_ub; i113++) {
            Aeq[i110 + Aeq.size(0) * ((i112 + i113) - 1)] = -c * BasisVal[BasisVal.size(0) * i113];
        }
        q_a = r2D[3 * (r2D.size(1) - 1)];
        r_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
        s_a = r2D[3 * (r2D.size(1) - 1) + 1];
        t_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
        u_a = r2D[3 * (r2D.size(1) - 1) + 2];
        v_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
        vc_loop_ub = BasisVal.size(1);
        d7 = ((static_cast<double>(c_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d7 > (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i114 = 1;
        } else {
            i114 = static_cast<int>(d7);
        }
        g_a.set_size(3, BasisVal.size(1));
        for (int i115{0}; i115 < vc_loop_ub; i115++) {
            double d8;
            double d9;
            d8 = BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i115) - 1];
            d9 = BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i115) - 1];
            g_a[3 * i115] = q_a * d8 + r_a * d9;
            g_a[3 * i115 + 1] = s_a * d8 + t_a * d9;
            g_a[3 * i115 + 2] = u_a * d8 + v_a * d9;
        }
        coder::internal::blas::mtimes(t_1, g_a, r3);
        wc_loop_ub = r3.size(1);
        for (int i116{0}; i116 < wc_loop_ub; i116++) {
            Aeq[(i110 + Aeq.size(0) * ((i114 + i116) - 1)) + 1] = r3[i116];
        }
        //
        w_a = r2Dn[0];
        x_a = 0.5 * r1Dn[0];
        y_a = r2Dn[1];
        ab_a = 0.5 * r1Dn[1];
        bb_a = r2Dn[2];
        cb_a = 0.5 * r1Dn[2];
        xc_loop_ub = BasisVal.size(1);
        d10 = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d10 >
            ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i117 = 1;
        } else {
            i117 = static_cast<int>(d10);
        }
        g_a.set_size(3, BasisVal.size(1));
        for (int i118{0}; i118 < xc_loop_ub; i118++) {
            double d11;
            double d12;
            d11 = BasisVal[BasisVal.size(0) * i118];
            d12 = BasisValD[BasisValD.size(0) * i118];
            g_a[3 * i118] = w_a * d11 + x_a * d12;
            g_a[3 * i118 + 1] = y_a * d11 + ab_a * d12;
            g_a[3 * i118 + 2] = bb_a * d11 + cb_a * d12;
        }
        coder::internal::blas::mtimes(t_1, g_a, r3);
        yc_loop_ub = r3.size(1);
        for (int i119{0}; i119 < yc_loop_ub; i119++) {
            Aeq[(i110 + Aeq.size(0) * ((i117 + i119) - 1)) + 1] = -r3[i119];
        }
        //
        r1D.set_size(3, r1Dn.size(1));
        ad_loop_ub = r1Dn.size(1);
        for (int i120{0}; i120 < ad_loop_ub; i120++) {
            r1D[3 * i120] = r1Dn[3 * i120];
            r1D[3 * i120 + 1] = r1Dn[3 * i120 + 1];
            r1D[3 * i120 + 2] = r1Dn[3 * i120 + 2];
        }
        bd_loop_ub = r2Dn.size(1);
        r2D.set_size(3, r2Dn.size(1));
        for (int i121{0}; i121 < bd_loop_ub; i121++) {
            r2D[3 * i121] = r2Dn[3 * i121];
            r2D[3 * i121 + 1] = r2Dn[3 * i121 + 1];
            r2D[3 * i121 + 2] = r2Dn[3 * i121 + 2];
        }
    }
    //
    //  unit tangent vector @ end of previous piece
    //
    h_a = r2D[3 * (r2D.size(1) - 1)];
    i_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
    j_a = r2D[3 * (r2D.size(1) - 1) + 1];
    k_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
    l_a = r2D[3 * (r2D.size(1) - 1) + 2];
    m_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
    d1 = static_cast<double>(Aeq.size(1) - N) + 1.0;
    if (d1 > Aeq.size(1)) {
        i61 = 0;
    } else {
        i61 = static_cast<int>(d1) - 1;
    }
    b_unnamed_idx_0 = Aeq.size(0) - 2;
    unnamed_idx_1 = Aeq.size(0) - 1;
    d_r1D = r1D.size(1);
    d2 = coder::b_norm(*(double(*)[3]) & r1D[3 * (d_r1D - 1)]);
    c_r1D[0] = r1D[3 * (r1D.size(1) - 1)] / d2;
    c_r1D[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d2;
    c_r1D[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d2;
    sb_loop_ub = BasisVal.size(1);
    tb_loop_ub = BasisVal.size(1);
    ub_loop_ub = BasisVal.size(1);
    g_a.set_size(3, BasisVal.size(1));
    for (int i62{0}; i62 < sb_loop_ub; i62++) {
        g_a[3 * i62] = h_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i62) - 1] +
                       i_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i62) - 1];
    }
    for (int i64{0}; i64 < tb_loop_ub; i64++) {
        g_a[3 * i64 + 1] = j_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i64) - 1] +
                           k_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i64) - 1];
    }
    for (int i65{0}; i65 < ub_loop_ub; i65++) {
        g_a[3 * i65 + 2] = l_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i65) - 1] +
                           m_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i65) - 1];
    }
    coder::internal::blas::mtimes(c_r1D, g_a, r3);
    xb_loop_ub = BasisVal.size(1);
    for (int i67{0}; i67 < xb_loop_ub; i67++) {
        Aeq[b_unnamed_idx_0 + Aeq.size(0) * (i61 + i67)] =
            BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i67) - 1];
    }
    ac_loop_ub = r3.size(1);
    for (int i69{0}; i69 < ac_loop_ub; i69++) {
        Aeq[unnamed_idx_1 + Aeq.size(0) * (i61 + i69)] = r3[i69];
    }
    int b_beq;
    //
    b_beq = beq.size(0) - 1;
    beq[beq.size(0) - 2] = std::pow(v_1, 2.0) / r1D_sqnorm[r1D_sqnorm.size(1) - 1];
    beq[b_beq] = at_1;
}

} // namespace ocn

//
// File trailer for BuildConstr_v4.cpp
//
// [EOF]
//
