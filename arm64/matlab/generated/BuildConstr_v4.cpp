//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstr_v4.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:27:55
//

// Include Files
#include "BuildConstr_v4.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "bspline_base_eval.h"
#include "bsxfun.h"
#include "eml_mtimes_helper.h"
#include "mtimes.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void d_binary_expand_op(::coder::array<double, 2U> &R3, const ::coder::array<double, 2U> &r,
                               const ::coder::array<double, 2U> &r1);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &R3
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1
// Return Type  : void
//
namespace ocn {
static void d_binary_expand_op(::coder::array<double, 2U> &R3, const ::coder::array<double, 2U> &r,
                               const ::coder::array<double, 2U> &r1)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    if (r1.size(0) == 1) {
        i = r.size(0);
    } else {
        i = r1.size(0);
    }
    if (r1.size(1) == 1) {
        i1 = r.size(1);
    } else {
        i1 = r1.size(1);
    }
    R3.set_size(i, i1);
    stride_0_0 = (r.size(0) != 1);
    stride_0_1 = (r.size(1) != 1);
    stride_1_0 = (r1.size(0) != 1);
    stride_1_1 = (r1.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (r1.size(1) == 1) {
        loop_ub = r.size(1);
    } else {
        loop_ub = r1.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int b_loop_ub;
        if (r1.size(0) == 1) {
            b_loop_ub = r.size(0);
        } else {
            b_loop_ub = r1.size(0);
        }
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            R3[i3 + R3.size(0) * i2] = r[i3 * stride_0_0 + r.size(0) * aux_0_1] +
                                       0.5 * r1[i3 * stride_1_0 + r1.size(0) * aux_1_1];
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// function [A, b, Aeq, beq] = BuildConstr_v4(ctx, CurvStructs, amax, v_0, at_0, v_1, at_1, ...
//     BasisVal, BasisValD, u_vec)
//
// Arguments    : const queue_coder *ctx_q_splines
//                bool ctx_cfg_UseDynamicBreakpoints
//                bool ctx_cfg_UseLinearBreakpoints
//                double ctx_cfg_DynamicBreakpointsDistance
//                int ctx_cfg_SplineDegree
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
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
void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
                    bool ctx_cfg_UseLinearBreakpoints, double ctx_cfg_DynamicBreakpointsDistance,
                    int ctx_cfg_SplineDegree, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], int ctx_Bl_ncoeff,
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
    double dv4[6][3];
    double dv9[6][3];
    double c_r1D[3];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    double t_1[3];
    double a;
    double b_a;
    double b_b;
    double c_a;
    double d1;
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
    int d_unnamed_idx_1;
    int db_loop_ub;
    int e_input_sizes_idx_0;
    int e_unnamed_idx_1;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int f_loop_ub;
    int f_unnamed_idx_1;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int gb_loop_ub;
    int h_input_sizes_idx_0;
    int h_loop_ub;
    int hb_loop_ub;
    int i27;
    int i28;
    int i58;
    int i62;
    int input_sizes_idx_0;
    int j_loop_ub;
    int jb_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int mb_loop_ub;
    int nb_loop_ub;
    int o_loop_ub;
    int ob_loop_ub;
    int pb_loop_ub;
    int q_loop_ub;
    int qb_loop_ub;
    int result;
    int s_loop_ub;
    int sb_loop_ub;
    int tb_loop_ub;
    int unnamed_idx_0;
    int unnamed_idx_1;
    int vb_loop_ub;
    int w_loop_ub;
    int x_loop_ub;
    int y_loop_ub;
    bool empty_non_axis_sizes;
    // 'BuildConstr_v4:4' DebugLog(DebugCfg.Global, 'BuildConstr_v4 with Ncrv = %d, amax = [%f, %f,
    // %f], v_0 = %f, at_0 = %f, v_1 = %f, at_1 = %f\n', ... 'BuildConstr_v4:5'
    // int32(numel(CurvStructs)), amax(1), amax(2), amax(3), v_0, at_0, v_1, at_1);
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("BuildConstr_v4 with Ncrv = %d, amax = [%f, %f, %f], v_0 = %f, at_0 = %f, v_1 = %f, "
               "at_1 = %f\n",
               CurvStructs.size(1), amax[0], amax[1], amax[2], v_0, at_0, v_1, at_1);
        fflush(stdout);
    }
    // 'BuildConstr_v4:7' Bl = ctx.Bl;
    Bl_ncoeff = ctx_Bl_ncoeff;
    Bl_handle = ctx_Bl_handle;
    // 'BuildConstr_v4:8' if ctx.cfg.UseDynamicBreakpoints
    if (ctx_cfg_UseDynamicBreakpoints) {
        double varargin_1;
        // 'BuildConstr_v4:9' NBreak = max(floor(LengthCurv(ctx, CurvStructs(1), 0,
        // 1)/ctx.cfg.DynamicBreakpointsDistance), 4);
        varargin_1 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                &CurvStructs[0]) /
                     ctx_cfg_DynamicBreakpointsDistance;
        // 'BuildConstr_v4:10' if ctx.cfg.UseLinearBreakpoints
        if (ctx_cfg_UseLinearBreakpoints) {
            double delta1;
            int i;
            // 'BuildConstr_v4:11' Bl = bspline_create(ctx.cfg.SplineDegree, linspace(0,1,NBreak));
            breakpoints.set_size(1, static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)));
            breakpoints[static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)) - 1] = 1.0;
            breakpoints[0] = 0.0;
            delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
            i = breakpoints.size(1);
            for (int k{0}; k <= i - 3; k++) {
                breakpoints[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
            }
            // 'bspline_create:2' nbreak = length(breakpoints);
            // 'bspline_create:3' ncoeff = nbreak + degree - 2;
            Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
            // 'bspline_create:5' h = uint64(0);
            // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
            // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c',
            // '$(START_DIR)/src'); 'bspline_create:9' coder.updateBuildInfo('addLinkFlags',
            // LibInfo.gsl.lflags); 'bspline_create:10' coder.cinclude('src/c_spline.h');
            // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
            // degree, breakpoints, int32(nbreak));
            c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                              breakpoints.size(1));
            // 'bspline_create:12' Bl.ncoeff = ncoeff;
            // 'bspline_create:13' Bl.breakpoints = breakpoints;
            // 'bspline_create:14' Bl.handle = h;
            // 'bspline_create:15' Bl.degree = int32(degree);
            // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
        }
        // 'BuildConstr_v4:14' [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
        bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
    }
    // 'BuildConstr_v4:18' c_prof_in(mfilename);
    // 'BuildConstr_v4:19' Ncrv   = length(CurvStructs);
    // 'BuildConstr_v4:20' [M, N] = size(BasisVal);
    N = BasisVal.size(1);
    //
    // 'BuildConstr_v4:22' A      = sparse(7*M*Ncrv,   N*Ncrv);
    coder::b_sparse(
        7.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size(1)),
        static_cast<double>(BasisVal.size(1)) * static_cast<double>(CurvStructs.size(1)), A);
    //  preallocation
    // 'BuildConstr_v4:23' b      = zeros(7*M*Ncrv,   1);
    unnamed_idx_0 = static_cast<int>(7.0 * static_cast<double>(BasisVal.size(0)) *
                                     static_cast<double>(CurvStructs.size(1)));
    b.set_size(unnamed_idx_0);
    for (int i1{0}; i1 < unnamed_idx_0; i1++) {
        b[i1] = 0.0;
    }
    //  preallocation
    // 'BuildConstr_v4:24' Aeq    = zeros(2*(Ncrv+1), N*Ncrv);
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
    // 'BuildConstr_v4:25' beq    = zeros(2*(Ncrv+1), 1);
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
    // 'BuildConstr_v4:32' [~, r1D, r2D] = EvalCurvStruct(ctx, CurvStructs(1), u_vec);
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i5{0}; i5 <= loop_ub; i5++) {
        b_u_vec[i5] = u_vec[i5];
    }
    dv[0] = CurvStructs[0].P0[0];
    dv[1] = CurvStructs[0].P0[1];
    dv[2] = CurvStructs[0].P0[2];
    dv1[0] = CurvStructs[0].P1[0];
    dv1[1] = CurvStructs[0].P1[1];
    dv1[2] = CurvStructs[0].P1[2];
    dv2[0] = CurvStructs[0].CorrectedHelixCenter[0];
    dv2[1] = CurvStructs[0].CorrectedHelixCenter[1];
    dv2[2] = CurvStructs[0].CorrectedHelixCenter[2];
    dv3[0] = CurvStructs[0].evec[0];
    dv3[1] = CurvStructs[0].evec[1];
    dv3[2] = CurvStructs[0].evec[2];
    std::copy(&CurvStructs[0].CoeffP5[0][0], &CurvStructs[0].CoeffP5[0][0] + 18U, &dv4[0][0]);
    b_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, dv, dv1, dv2, dv3, CurvStructs[0].theta,
                     CurvStructs[0].pitch, dv4, CurvStructs[0].sp_index, CurvStructs[0].a_param,
                     CurvStructs[0].b_param, b_u_vec, a__1, r1D, r2D);
    // 'BuildConstr_v4:33' vmax          = CurvStructs(1).FeedRate;
    // 'BuildConstr_v4:34' r1D_sqnorm    = sum(r1D.^2);
    r.set_size(3, r1D.size(1));
    b_loop_ub = r1D.size(1);
    for (int i6{0}; i6 < b_loop_ub; i6++) {
        double b_varargin_1;
        double c_varargin_1;
        double d_varargin_1;
        b_varargin_1 = r1D[3 * i6];
        r[3 * i6] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = r1D[3 * i6 + 1];
        r[3 * i6 + 1] = std::pow(c_varargin_1, 2.0);
        d_varargin_1 = r1D[3 * i6 + 2];
        r[3 * i6 + 2] = std::pow(d_varargin_1, 2.0);
    }
    coder::sum(r, r1D_sqnorm);
    //  squared norm
    //
    // 'BuildConstr_v4:36' t_0 = r1D(:, 1)/norm(r1D(:, 1));
    //  unit tangent vector @ start
    //
    // 'BuildConstr_v4:39' R1 = bsxfun(@times, r2D(1, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(1,
    // :)' , BasisValD);
    c_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        b_r2D[i7] = r2D[3 * i7];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    d_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        b_r1D[i8] = r1D[3 * i8];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int e_loop_ub;
        R1.set_size(r1.size(0), r1.size(1));
        e_loop_ub = r1.size(1);
        for (int i9{0}; i9 < e_loop_ub; i9++) {
            int g_loop_ub;
            g_loop_ub = r1.size(0);
            for (int i11{0}; i11 < g_loop_ub; i11++) {
                R1[i11 + R1.size(0) * i9] =
                    r1[i11 + r1.size(0) * i9] + 0.5 * r2[i11 + r2.size(0) * i9];
            }
        }
    } else {
        d_binary_expand_op(R1, r1, r2);
    }
    // 'BuildConstr_v4:40' R2 = bsxfun(@times, r2D(2, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(2,
    // :)' , BasisValD);
    f_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i10{0}; i10 < f_loop_ub; i10++) {
        b_r2D[i10] = r2D[3 * i10 + 1];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    h_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        b_r1D[i12] = r1D[3 * i12 + 1];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int i_loop_ub;
        R2.set_size(r1.size(0), r1.size(1));
        i_loop_ub = r1.size(1);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            int k_loop_ub;
            k_loop_ub = r1.size(0);
            for (int i15{0}; i15 < k_loop_ub; i15++) {
                R2[i15 + R2.size(0) * i13] =
                    r1[i15 + r1.size(0) * i13] + 0.5 * r2[i15 + r2.size(0) * i13];
            }
        }
    } else {
        d_binary_expand_op(R2, r1, r2);
    }
    // 'BuildConstr_v4:41' R3 = bsxfun(@times, r2D(3, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(3,
    // :)' , BasisValD);
    j_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i14{0}; i14 < j_loop_ub; i14++) {
        b_r2D[i14] = r2D[3 * i14 + 2];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    l_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i16{0}; i16 < l_loop_ub; i16++) {
        b_r1D[i16] = r1D[3 * i16 + 2];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int m_loop_ub;
        R3.set_size(r1.size(0), r1.size(1));
        m_loop_ub = r1.size(1);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            int n_loop_ub;
            n_loop_ub = r1.size(0);
            for (int i18{0}; i18 < n_loop_ub; i18++) {
                R3[i18 + R3.size(0) * i17] =
                    r1[i18 + r1.size(0) * i17] + 0.5 * r2[i18 + r2.size(0) * i17];
            }
        }
    } else {
        d_binary_expand_op(R3, r1, r2);
    }
    //
    // 'BuildConstr_v4:44' A(1:7*M, 1:N)  = [BasisVal;
    // 'BuildConstr_v4:45'     R1;
    // 'BuildConstr_v4:46'     -R1;
    // 'BuildConstr_v4:47'     R2;
    // 'BuildConstr_v4:48'     -R2;
    // 'BuildConstr_v4:49'     R3;
    // 'BuildConstr_v4:50'     -R3];
    varargin_3.set_size(R1.size(0), R1.size(1));
    o_loop_ub = R1.size(1);
    for (int i19{0}; i19 < o_loop_ub; i19++) {
        int p_loop_ub;
        p_loop_ub = R1.size(0);
        for (int i20{0}; i20 < p_loop_ub; i20++) {
            varargin_3[i20 + varargin_3.size(0) * i19] = -R1[i20 + R1.size(0) * i19];
        }
    }
    varargin_5.set_size(R2.size(0), R2.size(1));
    q_loop_ub = R2.size(1);
    for (int i21{0}; i21 < q_loop_ub; i21++) {
        int r_loop_ub;
        r_loop_ub = R2.size(0);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            varargin_5[i22 + varargin_5.size(0) * i21] = -R2[i22 + R2.size(0) * i21];
        }
    }
    varargin_7.set_size(R3.size(0), R3.size(1));
    s_loop_ub = R3.size(1);
    for (int i23{0}; i23 < s_loop_ub; i23++) {
        int t_loop_ub;
        t_loop_ub = R3.size(0);
        for (int i24{0}; i24 < t_loop_ub; i24++) {
            varargin_7[i24 + varargin_7.size(0) * i23] = -R3[i24 + R3.size(0) * i23];
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
        int u_loop_ub;
        y.set_size(1, static_cast<int>(b_b - 1.0) + 1);
        u_loop_ub = static_cast<int>(b_b - 1.0);
        for (int i25{0}; i25 <= u_loop_ub; i25++) {
            y[i25] = static_cast<double>(i25) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int v_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        v_loop_ub = BasisVal.size(1) - 1;
        for (int i26{0}; i26 <= v_loop_ub; i26++) {
            b_y[i26] = static_cast<double>(i26) + 1.0;
        }
    }
    h_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    d_input_sizes_idx_0 = e_input_sizes_idx_0;
    i27 = h_input_sizes_idx_0 + input_sizes_idx_0;
    i28 = i27 + b_input_sizes_idx_0;
    b_BasisVal.set_size(
        (((i28 + c_input_sizes_idx_0) + d_input_sizes_idx_0) + f_input_sizes_idx_0) +
            g_input_sizes_idx_0,
        result);
    for (int i29{0}; i29 < result; i29++) {
        for (int i31{0}; i31 < h_input_sizes_idx_0; i31++) {
            b_BasisVal[i31 + b_BasisVal.size(0) * i29] = BasisVal[i31 + h_input_sizes_idx_0 * i29];
        }
    }
    for (int i30{0}; i30 < result; i30++) {
        for (int i33{0}; i33 < input_sizes_idx_0; i33++) {
            b_BasisVal[(i33 + h_input_sizes_idx_0) + b_BasisVal.size(0) * i30] =
                R1[i33 + input_sizes_idx_0 * i30];
        }
    }
    for (int i32{0}; i32 < result; i32++) {
        for (int i35{0}; i35 < b_input_sizes_idx_0; i35++) {
            b_BasisVal[((i35 + h_input_sizes_idx_0) + input_sizes_idx_0) +
                       b_BasisVal.size(0) * i32] = varargin_3[i35 + b_input_sizes_idx_0 * i32];
        }
    }
    for (int i34{0}; i34 < result; i34++) {
        for (int i37{0}; i37 < c_input_sizes_idx_0; i37++) {
            b_BasisVal[(((i37 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i34] = R2[i37 + c_input_sizes_idx_0 * i34];
        }
    }
    for (int i36{0}; i36 < result; i36++) {
        for (int i39{0}; i39 < d_input_sizes_idx_0; i39++) {
            b_BasisVal[((((i39 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                        c_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i36] = varargin_5[i39 + d_input_sizes_idx_0 * i36];
        }
    }
    for (int i38{0}; i38 < result; i38++) {
        for (int i41{0}; i41 < f_input_sizes_idx_0; i41++) {
            b_BasisVal[((((i41 + i27) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                        d_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i38] = R3[i41 + f_input_sizes_idx_0 * i38];
        }
    }
    for (int i40{0}; i40 < result; i40++) {
        for (int i42{0}; i42 < g_input_sizes_idx_0; i42++) {
            b_BasisVal[((((i42 + i28) + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                        f_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i40] = varargin_7[i42 + g_input_sizes_idx_0 * i40];
        }
    }
    A->parenAssign(b_BasisVal, y, b_y);
    //
    // 'BuildConstr_v4:52' bC1 = (vmax)^2./r1D_sqnorm';
    x = CurvStructs[0].FeedRate * CurvStructs[0].FeedRate;
    // 'BuildConstr_v4:53' bC2 = amax(1)*ones(M, 1);
    bC2.set_size(BasisVal.size(0));
    w_loop_ub = BasisVal.size(0);
    for (int i43{0}; i43 < w_loop_ub; i43++) {
        bC2[i43] = amax[0];
    }
    // 'BuildConstr_v4:54' bC3 = amax(2)*ones(M, 1);
    bC3.set_size(BasisVal.size(0));
    x_loop_ub = BasisVal.size(0);
    for (int i44{0}; i44 < x_loop_ub; i44++) {
        bC3[i44] = amax[1];
    }
    // 'BuildConstr_v4:55' bC4 = amax(3)*ones(M, 1);
    bC4.set_size(BasisVal.size(0));
    y_loop_ub = BasisVal.size(0);
    for (int i45{0}; i45 < y_loop_ub; i45++) {
        bC4[i45] = amax[2];
    }
    //
    // 'BuildConstr_v4:57' b(1:7*M)       = [bC1;
    // 'BuildConstr_v4:58'     bC2;
    // 'BuildConstr_v4:59'     bC2;
    // 'BuildConstr_v4:60'     bC3;
    // 'BuildConstr_v4:61'     bC3;
    // 'BuildConstr_v4:62'     bC4;
    // 'BuildConstr_v4:63'     bC4];
    unnamed_idx_1 = r1D_sqnorm.size(1);
    b_unnamed_idx_1 = BasisVal.size(0);
    c_unnamed_idx_1 = BasisVal.size(0);
    d_unnamed_idx_1 = BasisVal.size(0);
    e_unnamed_idx_1 = BasisVal.size(0);
    f_unnamed_idx_1 = BasisVal.size(0);
    ab_loop_ub = r1D_sqnorm.size(1);
    for (int i46{0}; i46 < ab_loop_ub; i46++) {
        b[i46] = x / r1D_sqnorm[i46];
    }
    bb_loop_ub = BasisVal.size(0);
    for (int i47{0}; i47 < bb_loop_ub; i47++) {
        b[i47 + unnamed_idx_1] = amax[0];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i48{0}; i48 < cb_loop_ub; i48++) {
        b[(i48 + unnamed_idx_1) + b_unnamed_idx_1] = amax[0];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i49{0}; i49 < db_loop_ub; i49++) {
        b[((i49 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = amax[1];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i50{0}; i50 < eb_loop_ub; i50++) {
        b[(((i50 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1] =
            amax[1];
    }
    fb_loop_ub = BasisVal.size(0);
    for (int i51{0}; i51 < fb_loop_ub; i51++) {
        b[((((i51 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
          e_unnamed_idx_1] = amax[2];
    }
    gb_loop_ub = BasisVal.size(0);
    for (int i52{0}; i52 < gb_loop_ub; i52++) {
        b[(((((i52 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
           e_unnamed_idx_1) +
          f_unnamed_idx_1] = amax[2];
    }
    //
    // 'BuildConstr_v4:65' Aeq(1:2, 1:N)   = [BasisVal(1, :);
    // 'BuildConstr_v4:66'     t_0' * [r2D(1, 1)   * BasisVal(1, :)   + 0.5*r1D(1, 1)   *
    // BasisValD(1, :); 'BuildConstr_v4:67'     r2D(2, 1)   * BasisVal(1, :)   + 0.5*r1D(2, 1)   *
    // BasisValD(1, :); 'BuildConstr_v4:68'     r2D(3, 1)   * BasisVal(1, :)   + 0.5*r1D(3, 1)   *
    // BasisValD(1, :)]];
    a = r2D[0];
    b_a = 0.5 * r1D[0];
    c_a = r2D[1];
    d_a = 0.5 * r1D[1];
    e_a = r2D[2];
    f_a = 0.5 * r1D[2];
    if (BasisVal.size(1) == BasisValD.size(1)) {
        double d;
        int ib_loop_ub;
        int kb_loop_ub;
        int lb_loop_ub;
        d = coder::b_norm(*(double(*)[3]) & r1D[0]);
        c_r1D[0] = r1D[0] / d;
        c_r1D[1] = r1D[1] / d;
        c_r1D[2] = r1D[2] / d;
        ib_loop_ub = BasisVal.size(1);
        kb_loop_ub = BasisVal.size(1);
        lb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i55{0}; i55 < ib_loop_ub; i55++) {
            g_a[3 * i55] =
                a * BasisVal[BasisVal.size(0) * i55] + b_a * BasisValD[BasisValD.size(0) * i55];
        }
        for (int i56{0}; i56 < kb_loop_ub; i56++) {
            g_a[3 * i56 + 1] =
                c_a * BasisVal[BasisVal.size(0) * i56] + d_a * BasisValD[BasisValD.size(0) * i56];
        }
        for (int i57{0}; i57 < lb_loop_ub; i57++) {
            g_a[3 * i57 + 2] =
                e_a * BasisVal[BasisVal.size(0) * i57] + f_a * BasisValD[BasisValD.size(0) * i57];
        }
        coder::internal::blas::mtimes(c_r1D, g_a, r3);
    } else {
        b_binary_expand_op(r3, r1D, a, BasisVal, b_a, BasisValD, c_a, d_a, e_a, f_a);
    }
    hb_loop_ub = BasisVal.size(1);
    for (int i53{0}; i53 < hb_loop_ub; i53++) {
        Aeq[Aeq.size(0) * i53] = BasisVal[BasisVal.size(0) * i53];
    }
    jb_loop_ub = r3.size(1);
    for (int i54{0}; i54 < jb_loop_ub; i54++) {
        Aeq[Aeq.size(0) * i54 + 1] = r3[i54];
    }
    // 'BuildConstr_v4:69' beq(1:2)       = [(v_0(1)^2)/r1D_sqnorm(1);
    // 'BuildConstr_v4:70'     at_0(1)];
    beq[0] = v_0 * v_0 / r1D_sqnorm[0];
    beq[1] = at_0;
    //  This should be the correct behavior for a single segment,
    //  reusing the r1D norm
    // 'BuildConstr_v4:74' r1Dn_sqnorm = r1D_sqnorm;
    // 'BuildConstr_v4:76' for k = 1:Ncrv-1
    i58 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_unnamed_idx_1 = bC2.size(0);
        c_unnamed_idx_1 = bC2.size(0);
        d_unnamed_idx_1 = bC3.size(0);
        e_unnamed_idx_1 = bC3.size(0);
        f_unnamed_idx_1 = bC4.size(0);
        mb_loop_ub = bC2.size(0);
        nb_loop_ub = bC2.size(0);
        ob_loop_ub = bC3.size(0);
        pb_loop_ub = bC3.size(0);
        qb_loop_ub = bC4.size(0);
        sb_loop_ub = bC4.size(0);
    }
    for (int b_k{0}; b_k <= i58 - 2; b_k++) {
        double a_tmp;
        double ab_a;
        double b_t_1;
        double b_tmp;
        double b_x;
        double bb_a;
        double c;
        double c_b;
        double c_t_1;
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
        int ac_loop_ub;
        int ad_loop_ub;
        int b_result;
        int bc_loop_ub;
        int bd_loop_ub;
        int cd_loop_ub;
        int dc_loop_ub;
        int dd_loop_ub;
        int fc_loop_ub;
        int hc_loop_ub;
        int i103;
        int i111;
        int i113;
        int i115;
        int i118;
        int i_input_sizes_idx_0;
        int j_input_sizes_idx_0;
        int jc_loop_ub;
        int k_input_sizes_idx_0;
        int l_input_sizes_idx_0;
        int m_input_sizes_idx_0;
        int mc_loop_ub;
        int n_input_sizes_idx_0;
        int o_input_sizes_idx_0;
        int oc_loop_ub;
        int qc_loop_ub;
        int rb_loop_ub;
        unsigned int u;
        int ub_loop_ub;
        int uc_loop_ub;
        int vc_loop_ub;
        int wc_loop_ub;
        int xc_loop_ub;
        bool b_empty_non_axis_sizes;
        // 'BuildConstr_v4:77' if ctx.cfg.UseDynamicBreakpoints
        if (ctx_cfg_UseDynamicBreakpoints) {
            double varargin_2;
            // 'BuildConstr_v4:78' NBreak = max(4, floor(LengthCurv(ctx, CurvStructs(k+1), 0,
            // 1)/ctx.cfg.DynamicBreakpointsDistance));
            varargin_2 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                    &CurvStructs[b_k + 1]) /
                         ctx_cfg_DynamicBreakpointsDistance;
            // 'BuildConstr_v4:79' if ctx.cfg.UseLinearBreakpoints
            if (ctx_cfg_UseLinearBreakpoints) {
                double b_delta1;
                int i59;
                int i61;
                // 'BuildConstr_v4:80' Bl = bspline_create(ctx.cfg.SplineDegree,
                // linspace(0,1,NBreak));
                i59 = static_cast<int>(std::fmax(4.0, std::floor(varargin_2)));
                breakpoints.set_size(1, i59);
                breakpoints[i59 - 1] = 1.0;
                breakpoints[0] = 0.0;
                b_delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
                i61 = breakpoints.size(1);
                for (int c_k{0}; c_k <= i61 - 3; c_k++) {
                    breakpoints[c_k + 1] = (static_cast<double>(c_k) + 1.0) * b_delta1;
                }
                // 'bspline_create:2' nbreak = length(breakpoints);
                // 'bspline_create:3' ncoeff = nbreak + degree - 2;
                Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
                // 'bspline_create:5' h = uint64(0);
                // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
                // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c',
                // '$(START_DIR)/src'); 'bspline_create:9' coder.updateBuildInfo('addLinkFlags',
                // LibInfo.gsl.lflags); 'bspline_create:10' coder.cinclude('src/c_spline.h');
                // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints',
                // coder.wref(h), degree, breakpoints, int32(nbreak));
                c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                                  breakpoints.size(1));
                // 'bspline_create:12' Bl.ncoeff = ncoeff;
                // 'bspline_create:13' Bl.breakpoints = breakpoints;
                // 'bspline_create:14' Bl.handle = h;
                // 'bspline_create:15' Bl.degree = int32(degree);
                // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
            }
            // 'BuildConstr_v4:83' [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
            bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
        }
        // 'BuildConstr_v4:85' [M, N] = size(BasisVal);
        N = BasisVal.size(1);
        // 'BuildConstr_v4:87' [~, r1Dn, r2Dn] = EvalCurvStruct(ctx, CurvStructs(k+1), u_vec);
        c_u_vec.set_size(1, u_vec.size(1));
        rb_loop_ub = u_vec.size(1) - 1;
        for (int i60{0}; i60 <= rb_loop_ub; i60++) {
            c_u_vec[i60] = u_vec[i60];
        }
        dv5[0] = CurvStructs[b_k + 1].P0[0];
        dv5[1] = CurvStructs[b_k + 1].P0[1];
        dv5[2] = CurvStructs[b_k + 1].P0[2];
        dv6[0] = CurvStructs[b_k + 1].P1[0];
        dv6[1] = CurvStructs[b_k + 1].P1[1];
        dv6[2] = CurvStructs[b_k + 1].P1[2];
        dv7[0] = CurvStructs[b_k + 1].CorrectedHelixCenter[0];
        dv7[1] = CurvStructs[b_k + 1].CorrectedHelixCenter[1];
        dv7[2] = CurvStructs[b_k + 1].CorrectedHelixCenter[2];
        dv8[0] = CurvStructs[b_k + 1].evec[0];
        dv8[1] = CurvStructs[b_k + 1].evec[1];
        dv8[2] = CurvStructs[b_k + 1].evec[2];
        std::copy(&CurvStructs[b_k + 1].CoeffP5[0][0], &CurvStructs[b_k + 1].CoeffP5[0][0] + 18U,
                  &dv9[0][0]);
        b_EvalCurvStruct(ctx_q_splines, CurvStructs[b_k + 1].Type, dv5, dv6, dv7, dv8,
                         CurvStructs[b_k + 1].theta, CurvStructs[b_k + 1].pitch, dv9,
                         CurvStructs[b_k + 1].sp_index, CurvStructs[b_k + 1].a_param,
                         CurvStructs[b_k + 1].b_param, c_u_vec, a__2, r1Dn, r2Dn);
        // 'BuildConstr_v4:88' vmax            = CurvStructs(k+1).FeedRate;
        // 'BuildConstr_v4:89' r1Dn_sqnorm     = sum(r1Dn.^2);
        ub_loop_ub = r1Dn.size(1);
        r.set_size(3, r1Dn.size(1));
        for (int i65{0}; i65 < ub_loop_ub; i65++) {
            double e_varargin_1;
            double f_varargin_1;
            double g_varargin_1;
            e_varargin_1 = r1Dn[3 * i65];
            r[3 * i65] = std::pow(e_varargin_1, 2.0);
            f_varargin_1 = r1Dn[3 * i65 + 1];
            r[3 * i65 + 1] = std::pow(f_varargin_1, 2.0);
            g_varargin_1 = r1Dn[3 * i65 + 2];
            r[3 * i65 + 2] = std::pow(g_varargin_1, 2.0);
        }
        double d3;
        double x_tmp;
        int e_r1D;
        coder::sum(r, r1D_sqnorm);
        //  squared norm
        // 'BuildConstr_v4:90' bC1 = (vmax)^2./r1Dn_sqnorm';
        x_tmp = CurvStructs[b_k + 1].FeedRate;
        b_x = x_tmp * x_tmp;
        // 'BuildConstr_v4:91' t_1 = r1D(:, end)/norm(r1D(:, end));
        e_r1D = r1D.size(1);
        d3 = coder::b_norm(*(double(*)[3]) & r1D[3 * (e_r1D - 1)]);
        t_1[0] = r1D[3 * (r1D.size(1) - 1)] / d3;
        t_1[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d3;
        t_1[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d3;
        //  unit tangent vector @ end of previous piece
        //
        // 'BuildConstr_v4:93' R1 = bsxfun(@times, r2Dn(1, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(1, :)' , BasisValD);
        ac_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i69{0}; i69 < ac_loop_ub; i69++) {
            b_r2Dn[i69] = r2Dn[3 * i69];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        bc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i70{0}; i70 < bc_loop_ub; i70++) {
            b_r1Dn[i70] = r1Dn[3 * i70];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int cc_loop_ub;
            R1.set_size(r1.size(0), r1.size(1));
            cc_loop_ub = r1.size(1);
            for (int i71{0}; i71 < cc_loop_ub; i71++) {
                int ec_loop_ub;
                ec_loop_ub = r1.size(0);
                for (int i73{0}; i73 < ec_loop_ub; i73++) {
                    R1[i73 + R1.size(0) * i71] =
                        r1[i73 + r1.size(0) * i71] + 0.5 * r2[i73 + r2.size(0) * i71];
                }
            }
        } else {
            d_binary_expand_op(R1, r1, r2);
        }
        // 'BuildConstr_v4:94' R2 = bsxfun(@times, r2Dn(2, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(2, :)' , BasisValD);
        dc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i72{0}; i72 < dc_loop_ub; i72++) {
            b_r2Dn[i72] = r2Dn[3 * i72 + 1];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        fc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i74{0}; i74 < fc_loop_ub; i74++) {
            b_r1Dn[i74] = r1Dn[3 * i74 + 1];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int gc_loop_ub;
            R2.set_size(r1.size(0), r1.size(1));
            gc_loop_ub = r1.size(1);
            for (int i75{0}; i75 < gc_loop_ub; i75++) {
                int ic_loop_ub;
                ic_loop_ub = r1.size(0);
                for (int i77{0}; i77 < ic_loop_ub; i77++) {
                    R2[i77 + R2.size(0) * i75] =
                        r1[i77 + r1.size(0) * i75] + 0.5 * r2[i77 + r2.size(0) * i75];
                }
            }
        } else {
            d_binary_expand_op(R2, r1, r2);
        }
        // 'BuildConstr_v4:95' R3 = bsxfun(@times, r2Dn(3, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(3, :)' , BasisValD);
        hc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i76{0}; i76 < hc_loop_ub; i76++) {
            b_r2Dn[i76] = r2Dn[3 * i76 + 2];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        jc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i78{0}; i78 < jc_loop_ub; i78++) {
            b_r1Dn[i78] = r1Dn[3 * i78 + 2];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int kc_loop_ub;
            R3.set_size(r1.size(0), r1.size(1));
            kc_loop_ub = r1.size(1);
            for (int i79{0}; i79 < kc_loop_ub; i79++) {
                int lc_loop_ub;
                lc_loop_ub = r1.size(0);
                for (int i80{0}; i80 < lc_loop_ub; i80++) {
                    R3[i80 + R3.size(0) * i79] =
                        r1[i80 + r1.size(0) * i79] + 0.5 * r2[i80 + r2.size(0) * i79];
                }
            }
        } else {
            d_binary_expand_op(R3, r1, r2);
        }
        //
        // 'BuildConstr_v4:97' A(k*7*M+1:(k+1)*7*M, k*N+1:(k+1)*N) = ...
        // 'BuildConstr_v4:98'         [BasisVal;
        // 'BuildConstr_v4:99'         R1;
        // 'BuildConstr_v4:100'         -R1;
        // 'BuildConstr_v4:101'         R2;
        // 'BuildConstr_v4:102'         -R2;
        // 'BuildConstr_v4:103'         R3;
        // 'BuildConstr_v4:104'         -R3];
        varargin_3.set_size(R1.size(0), R1.size(1));
        mc_loop_ub = R1.size(1);
        for (int i81{0}; i81 < mc_loop_ub; i81++) {
            int nc_loop_ub;
            nc_loop_ub = R1.size(0);
            for (int i82{0}; i82 < nc_loop_ub; i82++) {
                varargin_3[i82 + varargin_3.size(0) * i81] = -R1[i82 + R1.size(0) * i81];
            }
        }
        varargin_5.set_size(R2.size(0), R2.size(1));
        oc_loop_ub = R2.size(1);
        for (int i83{0}; i83 < oc_loop_ub; i83++) {
            int pc_loop_ub;
            pc_loop_ub = R2.size(0);
            for (int i84{0}; i84 < pc_loop_ub; i84++) {
                varargin_5[i84 + varargin_5.size(0) * i83] = -R2[i84 + R2.size(0) * i83];
            }
        }
        varargin_7.set_size(R3.size(0), R3.size(1));
        qc_loop_ub = R3.size(1);
        for (int i85{0}; i85 < qc_loop_ub; i85++) {
            int rc_loop_ub;
            rc_loop_ub = R3.size(0);
            for (int i86{0}; i86 < rc_loop_ub; i86++) {
                varargin_7[i86 + varargin_7.size(0) * i85] = -R3[i86 + R3.size(0) * i85];
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
        a_tmp = (static_cast<double>(b_k) + 1.0) * 7.0;
        n_a = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
        b_tmp = ((static_cast<double>(b_k) + 1.0) + 1.0) * 7.0;
        c_b = b_tmp * static_cast<double>(BasisVal.size(0));
        if (c_b < n_a) {
            y.set_size(1, 0);
        } else {
            int sc_loop_ub;
            sc_loop_ub = static_cast<int>(c_b - n_a);
            y.set_size(1, sc_loop_ub + 1);
            for (int i87{0}; i87 <= sc_loop_ub; i87++) {
                y[i87] = n_a + static_cast<double>(i87);
            }
        }
        o_a = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        d_b = ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1));
        if (d_b < o_a) {
            b_y.set_size(1, 0);
        } else {
            int tc_loop_ub;
            tc_loop_ub = static_cast<int>(d_b - o_a);
            b_y.set_size(1, tc_loop_ub + 1);
            for (int i88{0}; i88 <= tc_loop_ub; i88++) {
                b_y[i88] = o_a + static_cast<double>(i88);
            }
        }
        b_BasisVal.set_size((((((i_input_sizes_idx_0 + j_input_sizes_idx_0) + k_input_sizes_idx_0) +
                               l_input_sizes_idx_0) +
                              m_input_sizes_idx_0) +
                             n_input_sizes_idx_0) +
                                o_input_sizes_idx_0,
                            b_result);
        for (int i89{0}; i89 < b_result; i89++) {
            for (int i91{0}; i91 < i_input_sizes_idx_0; i91++) {
                b_BasisVal[i91 + b_BasisVal.size(0) * i89] =
                    BasisVal[i91 + i_input_sizes_idx_0 * i89];
            }
        }
        for (int i90{0}; i90 < b_result; i90++) {
            for (int i93{0}; i93 < j_input_sizes_idx_0; i93++) {
                b_BasisVal[(i93 + i_input_sizes_idx_0) + b_BasisVal.size(0) * i90] =
                    R1[i93 + j_input_sizes_idx_0 * i90];
            }
        }
        for (int i92{0}; i92 < b_result; i92++) {
            for (int i95{0}; i95 < k_input_sizes_idx_0; i95++) {
                b_BasisVal[((i95 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i92] = varargin_3[i95 + k_input_sizes_idx_0 * i92];
            }
        }
        for (int i94{0}; i94 < b_result; i94++) {
            for (int i97{0}; i97 < l_input_sizes_idx_0; i97++) {
                b_BasisVal[(((i97 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                            k_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i94] = R2[i97 + l_input_sizes_idx_0 * i94];
            }
        }
        for (int i96{0}; i96 < b_result; i96++) {
            for (int i99{0}; i99 < m_input_sizes_idx_0; i99++) {
                b_BasisVal[((((i99 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                             k_input_sizes_idx_0) +
                            l_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i96] = varargin_5[i99 + m_input_sizes_idx_0 * i96];
            }
        }
        for (int i98{0}; i98 < b_result; i98++) {
            for (int i101{0}; i101 < n_input_sizes_idx_0; i101++) {
                b_BasisVal[(((((i101 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                              k_input_sizes_idx_0) +
                             l_input_sizes_idx_0) +
                            m_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i98] = R3[i101 + n_input_sizes_idx_0 * i98];
            }
        }
        for (int i100{0}; i100 < b_result; i100++) {
            for (int i102{0}; i102 < o_input_sizes_idx_0; i102++) {
                b_BasisVal[((((((i102 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                               k_input_sizes_idx_0) +
                              l_input_sizes_idx_0) +
                             m_input_sizes_idx_0) +
                            n_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i100] =
                    varargin_7[i102 + o_input_sizes_idx_0 * i100];
            }
        }
        A->parenAssign(b_BasisVal, y, b_y);
        //
        // 'BuildConstr_v4:106' b(k*7*M+1:(k+1)*7*M) = [bC1;
        // 'BuildConstr_v4:107'         bC2;
        // 'BuildConstr_v4:108'         bC2;
        // 'BuildConstr_v4:109'         bC3;
        // 'BuildConstr_v4:110'         bC3;
        // 'BuildConstr_v4:111'         bC4;
        // 'BuildConstr_v4:112'         bC4];
        d4 = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
        if (d4 > b_tmp * static_cast<double>(BasisVal.size(0))) {
            i103 = 0;
        } else {
            i103 = static_cast<int>(d4) - 1;
        }
        unnamed_idx_1 = r1D_sqnorm.size(1);
        uc_loop_ub = r1D_sqnorm.size(1);
        for (int i104{0}; i104 < uc_loop_ub; i104++) {
            b[i103 + i104] = b_x / r1D_sqnorm[i104];
        }
        for (int i105{0}; i105 < mb_loop_ub; i105++) {
            b[(i103 + i105) + unnamed_idx_1] = bC2[i105];
        }
        for (int i106{0}; i106 < nb_loop_ub; i106++) {
            b[((i103 + i106) + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i106];
        }
        for (int i107{0}; i107 < ob_loop_ub; i107++) {
            b[(((i103 + i107) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i107];
        }
        for (int i108{0}; i108 < pb_loop_ub; i108++) {
            b[((((i103 + i108) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
              d_unnamed_idx_1] = bC3[i108];
        }
        for (int i109{0}; i109 < qb_loop_ub; i109++) {
            b[(((((i103 + i109) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
               d_unnamed_idx_1) +
              e_unnamed_idx_1] = bC4[i109];
        }
        for (int i110{0}; i110 < sb_loop_ub; i110++) {
            b[((((((i103 + i110) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                d_unnamed_idx_1) +
               e_unnamed_idx_1) +
              f_unnamed_idx_1] = bC4[i110];
        }
        //
        // 'BuildConstr_v4:114' Aeq(2*k+1, (k-1)*N+1:k*N) =  (t_1'*r1D(:, end))^2 * BasisVal(end,
        // :);
        vc_loop_ub = BasisVal.size(1);
        d5 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d5 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i111 = 1;
        } else {
            i111 = static_cast<int>(d5);
        }
        u = static_cast<unsigned int>(b_k + 1) << 1;
        b_t_1 = (t_1[0] * r1D[3 * (r1D.size(1) - 1)] + t_1[1] * r1D[3 * (r1D.size(1) - 1) + 1]) +
                t_1[2] * r1D[3 * (r1D.size(1) - 1) + 2];
        p_a = b_t_1 * b_t_1;
        for (int i112{0}; i112 < vc_loop_ub; i112++) {
            Aeq[static_cast<int>(u) + Aeq.size(0) * ((i111 + i112) - 1)] =
                p_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i112) - 1];
        }
        // 'BuildConstr_v4:115' Aeq(2*k+1, k*N+1:(k+1)*N) = -(t_1'*r1Dn(:, 1))^2  * BasisVal(1, :);
        wc_loop_ub = BasisVal.size(1);
        d6 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d6 > ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i113 = 1;
        } else {
            i113 = static_cast<int>(d6);
        }
        c_t_1 = (t_1[0] * r1Dn[0] + t_1[1] * r1Dn[1]) + t_1[2] * r1Dn[2];
        c = c_t_1 * c_t_1;
        for (int i114{0}; i114 < wc_loop_ub; i114++) {
            Aeq[static_cast<int>(u) + Aeq.size(0) * ((i113 + i114) - 1)] =
                -c * BasisVal[BasisVal.size(0) * i114];
        }
        // 'BuildConstr_v4:117' Aeq(2*k+2, (k-1)*N+1:k*N) =   t_1'*[...
        // 'BuildConstr_v4:118'         r2D(1, end)   * BasisVal(end, :)   + 0.5*r1D(1, end)   *
        // BasisValD(end, :); 'BuildConstr_v4:119'         r2D(2, end)   * BasisVal(end, :)   +
        // 0.5*r1D(2, end)   * BasisValD(end, :); 'BuildConstr_v4:120'         r2D(3, end)   *
        // BasisVal(end, :)   + 0.5*r1D(3, end)   * BasisValD(end, :)];
        q_a = r2D[3 * (r2D.size(1) - 1)];
        r_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
        s_a = r2D[3 * (r2D.size(1) - 1) + 1];
        t_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
        u_a = r2D[3 * (r2D.size(1) - 1) + 2];
        v_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
        xc_loop_ub = BasisVal.size(1);
        d7 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d7 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i115 = 0;
        } else {
            i115 = static_cast<int>(d7) - 1;
        }
        if (BasisVal.size(1) == BasisValD.size(1)) {
            int yc_loop_ub;
            g_a.set_size(3, BasisVal.size(1));
            for (int i116{0}; i116 < xc_loop_ub; i116++) {
                double d8;
                double d9;
                d8 = BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i116) - 1];
                d9 = BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i116) - 1];
                g_a[3 * i116] = q_a * d8 + r_a * d9;
                g_a[3 * i116 + 1] = s_a * d8 + t_a * d9;
                g_a[3 * i116 + 2] = u_a * d8 + v_a * d9;
            }
            coder::internal::blas::mtimes(t_1, g_a, r4);
            yc_loop_ub = r4.size(1);
            for (int i117{0}; i117 < yc_loop_ub; i117++) {
                Aeq[(static_cast<int>(u) + Aeq.size(0) * (i115 + i117)) + 1] = r4[i117];
            }
        } else {
            binary_expand_op(Aeq, static_cast<int>(u + 2U), i115, t_1, q_a, BasisVal, r_a,
                             BasisValD, s_a, t_a, u_a, v_a);
        }
        //
        // 'BuildConstr_v4:122' Aeq(2*k+2, k*N+1:(k+1)*N) = -(t_1'*[...
        // 'BuildConstr_v4:123'         r2Dn(1, 1)   * BasisVal(1, :)   + 0.5*r1Dn(1, 1)   *
        // BasisValD(1, :); 'BuildConstr_v4:124'         r2Dn(2, 1)   * BasisVal(1, :)   +
        // 0.5*r1Dn(2, 1)   * BasisValD(1, :); 'BuildConstr_v4:125'         r2Dn(3, 1)   *
        // BasisVal(1, :)   + 0.5*r1Dn(3, 1)   * BasisValD(1, :)]);
        w_a = r2Dn[0];
        x_a = 0.5 * r1Dn[0];
        y_a = r2Dn[1];
        ab_a = 0.5 * r1Dn[1];
        bb_a = r2Dn[2];
        cb_a = 0.5 * r1Dn[2];
        ad_loop_ub = BasisVal.size(1);
        d10 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d10 >
            ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i118 = 1;
        } else {
            i118 = static_cast<int>(d10);
        }
        if (BasisVal.size(1) == BasisValD.size(1)) {
            g_a.set_size(3, BasisVal.size(1));
            for (int i119{0}; i119 < ad_loop_ub; i119++) {
                double d11;
                double d12;
                d11 = BasisVal[BasisVal.size(0) * i119];
                d12 = BasisValD[BasisValD.size(0) * i119];
                g_a[3 * i119] = w_a * d11 + x_a * d12;
                g_a[3 * i119 + 1] = y_a * d11 + ab_a * d12;
                g_a[3 * i119 + 2] = bb_a * d11 + cb_a * d12;
            }
            coder::internal::blas::mtimes(t_1, g_a, r3);
        } else {
            binary_expand_op(r3, t_1, w_a, BasisVal, x_a, BasisValD, y_a, ab_a, bb_a, cb_a);
        }
        bd_loop_ub = r3.size(1);
        for (int i120{0}; i120 < bd_loop_ub; i120++) {
            Aeq[(static_cast<int>(u) + Aeq.size(0) * ((i118 + i120) - 1)) + 1] = -r3[i120];
        }
        //
        // 'BuildConstr_v4:127' r1D = r1Dn;
        cd_loop_ub = r1Dn.size(1);
        r1D.set_size(3, r1Dn.size(1));
        for (int i121{0}; i121 < cd_loop_ub; i121++) {
            r1D[3 * i121] = r1Dn[3 * i121];
            r1D[3 * i121 + 1] = r1Dn[3 * i121 + 1];
            r1D[3 * i121 + 2] = r1Dn[3 * i121 + 2];
        }
        // 'BuildConstr_v4:128' r2D = r2Dn;
        dd_loop_ub = r2Dn.size(1);
        r2D.set_size(3, r2Dn.size(1));
        for (int i122{0}; i122 < dd_loop_ub; i122++) {
            r2D[3 * i122] = r2Dn[3 * i122];
            r2D[3 * i122 + 1] = r2Dn[3 * i122 + 1];
            r2D[3 * i122 + 2] = r2Dn[3 * i122 + 2];
        }
    }
    //
    // 'BuildConstr_v4:131' t_1 = r1D(:, end)/norm(r1D(:, end));
    //  unit tangent vector @ end of previous piece
    //
    // 'BuildConstr_v4:133' Aeq(end-1:end, end-N+1:end)   = [BasisVal(end, :);
    // 'BuildConstr_v4:134'     t_1' * [...
    // 'BuildConstr_v4:135'     r2D(1, end) * BasisVal(end, :) + 0.5*r1D(1, end) * BasisValD(end,
    // :); 'BuildConstr_v4:136'     r2D(2, end) * BasisVal(end, :) + 0.5*r1D(2, end) *
    // BasisValD(end, :); 'BuildConstr_v4:137'     r2D(3, end) * BasisVal(end, :) + 0.5*r1D(3, end)
    // * BasisValD(end, :)]];
    h_a = r2D[3 * (r2D.size(1) - 1)];
    i_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
    j_a = r2D[3 * (r2D.size(1) - 1) + 1];
    k_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
    l_a = r2D[3 * (r2D.size(1) - 1) + 2];
    m_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
    d1 = static_cast<double>(Aeq.size(1) - N) + 1.0;
    if (d1 > Aeq.size(1)) {
        i62 = 0;
    } else {
        i62 = static_cast<int>(d1) - 1;
    }
    b_unnamed_idx_0 = Aeq.size(0) - 2;
    unnamed_idx_1 = Aeq.size(0) - 1;
    if (BasisVal.size(1) == BasisValD.size(1)) {
        double d2;
        int d_r1D;
        int wb_loop_ub;
        int xb_loop_ub;
        int yb_loop_ub;
        d_r1D = r1D.size(1);
        d2 = coder::b_norm(*(double(*)[3]) & r1D[3 * (d_r1D - 1)]);
        c_r1D[0] = r1D[3 * (r1D.size(1) - 1)] / d2;
        c_r1D[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d2;
        c_r1D[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d2;
        wb_loop_ub = BasisVal.size(1);
        xb_loop_ub = BasisVal.size(1);
        yb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i66{0}; i66 < wb_loop_ub; i66++) {
            g_a[3 * i66] = h_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i66) - 1] +
                           i_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i66) - 1];
        }
        for (int i67{0}; i67 < xb_loop_ub; i67++) {
            g_a[3 * i67 + 1] = j_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i67) - 1] +
                               k_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i67) - 1];
        }
        for (int i68{0}; i68 < yb_loop_ub; i68++) {
            g_a[3 * i68 + 2] = l_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i68) - 1] +
                               m_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i68) - 1];
        }
        coder::internal::blas::mtimes(c_r1D, g_a, r3);
    } else {
        binary_expand_op(r3, r1D, h_a, BasisVal, i_a, BasisValD, j_a, k_a, l_a, m_a);
    }
    tb_loop_ub = BasisVal.size(1);
    for (int i63{0}; i63 < tb_loop_ub; i63++) {
        Aeq[b_unnamed_idx_0 + Aeq.size(0) * (i62 + i63)] =
            BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i63) - 1];
    }
    vb_loop_ub = r3.size(1);
    for (int i64{0}; i64 < vb_loop_ub; i64++) {
        Aeq[unnamed_idx_1 + Aeq.size(0) * (i62 + i64)] = r3[i64];
    }
    int b_beq;
    //
    // 'BuildConstr_v4:139' beq(end-1:end) = [(v_1^2)/r1Dn_sqnorm(end);
    // 'BuildConstr_v4:140'     at_1];
    b_beq = beq.size(0) - 1;
    beq[beq.size(0) - 2] = v_1 * v_1 / r1D_sqnorm[r1D_sqnorm.size(1) - 1];
    beq[b_beq] = at_1;
    // 'BuildConstr_v4:141' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for BuildConstr_v4.cpp
//
// [EOF]
//
