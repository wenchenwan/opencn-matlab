//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstr_v4.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:46:02
//

// Include Files
#include "BuildConstr_v4.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "bspline_base_eval.h"
#include "bsxfun.h"
#include "eml_mtimes_helper.h"
#include "linspace.h"
#include "mtimes.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "repmat.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <algorithm>
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &ramp);

static void d_binary_expand_op(::coder::array<double, 2U> &R3, const ::coder::array<double, 2U> &r,
                               const ::coder::array<double, 2U> &r1);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &ramp
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &ramp)
{
    ::coder::array<double, 1U> b_b;
    int b_loop_ub;
    int b_ramp;
    int c_ramp;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_ramp = ramp.size(0) * ramp.size(1);
    if (b_ramp == 1) {
        c_ramp = b.size(0);
    } else {
        c_ramp = b_ramp;
    }
    b_b.set_size(c_ramp);
    stride_0_0 = (b.size(0) != 1);
    stride_1_0 = (b_ramp != 1);
    if (b_ramp == 1) {
        loop_ub = b.size(0);
    } else {
        loop_ub = b_ramp;
    }
    for (int i{0}; i < loop_ub; i++) {
        b_b[i] = b[i * stride_0_0] * ramp[i * stride_1_0];
    }
    b.set_size(b_b.size(0));
    b_loop_ub = b_b.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b[i1] = b_b[i1];
    }
}

//
// Arguments    : ::coder::array<double, 2U> &R3
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1
// Return Type  : void
//
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
// function [A, b, Aeq, beq ] = BuildConstr_v4(ctx, CurvStructs, amax, v_0, at_0, v_1, at_1, ...
//     BasisVal, BasisValD, u_vec)
//
// Arguments    : const queue_coder *ctx_q_splines
//                bool ctx_cfg_UseDynamicBreakpoints
//                bool ctx_cfg_UseLinearBreakpoints
//                double ctx_cfg_DynamicBreakpointsDistance
//                int ctx_cfg_SplineDegree
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS
//                double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS
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
                    const double ctx_cfg_GaussLegendreW[5],
                    double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS,
                    double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS, int ctx_Bl_ncoeff,
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
    ::coder::array<double, 2U> acc_ramp;
    ::coder::array<double, 2U> b_BasisVal;
    ::coder::array<double, 2U> b_u_vec;
    ::coder::array<double, 2U> b_y;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> c_u_vec;
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1D_sqnorm;
    ::coder::array<double, 2U> r1Dn;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r2Dn;
    ::coder::array<double, 2U> r30;
    ::coder::array<double, 2U> ramp;
    ::coder::array<double, 2U> varargin_3;
    ::coder::array<double, 2U> varargin_4;
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
    ::coder::array<double, 1U> r17;
    ::coder::array<double, 1U> vel_ramp;
    double dv4[6][3];
    double dv9[6][3];
    double b_vel_ramp[7];
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
    double Nc;
    double Nec;
    double Nx;
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
    int M;
    int N;
    int ab_loop_ub;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_loop_ub_tmp;
    int b_unnamed_idx_1;
    int bb_loop_ub;
    int bc_loop_ub;
    int c_input_sizes_idx_0;
    int c_loop_ub;
    int c_unnamed_idx_1;
    int cb_loop_ub;
    int d_input_sizes_idx_0;
    int d_loop_ub;
    int d_unnamed_idx_1;
    int db_loop_ub;
    int dc_loop_ub;
    int e_input_sizes_idx_0;
    int e_loop_ub;
    int e_unnamed_idx_1;
    int eb_loop_ub;
    int f_input_sizes_idx_0;
    int f_unnamed_idx_1;
    int fb_loop_ub;
    int g_input_sizes_idx_0;
    int g_loop_ub;
    int g_scalarLB;
    int g_vectorUB;
    int gb_loop_ub;
    int h_input_sizes_idx_0;
    int hb_loop_ub;
    int i29;
    int i30;
    int i48;
    int i60;
    int i64;
    int i_loop_ub;
    int ib_loop_ub;
    int input_sizes_idx_0;
    int k_loop_ub;
    int kb_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int m_loop_ub;
    int nb_loop_ub;
    int ob_loop_ub;
    int p_loop_ub;
    int pb_loop_ub;
    int qb_loop_ub;
    int r_loop_ub;
    int rb_loop_ub;
    int result;
    int sb_loop_ub;
    int t_loop_ub;
    int ub_loop_ub;
    int unnamed_idx_0;
    int unnamed_idx_1;
    int vb_loop_ub;
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
            // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
            // 'bspline_create:3' nbreak = length(breakpoints);
            // 'bspline_create:4' ncoeff = nbreak + degree - 2;
            Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
            // 'bspline_create:5' h = uint64(0);
            // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c',
            // '$(START_DIR)/src'); 'bspline_create:8' coder.updateBuildInfo('addLinkFlags',
            // LibInfo.gsl.lflags); 'bspline_create:9' coder.cinclude('src/c_spline.h');
            // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
            // degree, breakpoints, int32(nbreak) );
            c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                              breakpoints.size(1));
            // 'bspline_create:11' Bl.ncoeff = ncoeff;
            // 'bspline_create:12' Bl.breakpoints = breakpoints;
            // 'bspline_create:13' Bl.handle = h;
            // 'bspline_create:14' Bl.degree = int32(degree);
            // 'bspline_create:15' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
        }
        // 'BuildConstr_v4:14' [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
        bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
    }
    // 'BuildConstr_v4:18' c_prof_in(mfilename);
    // 'BuildConstr_v4:19' Ncrv   = length(CurvStructs);
    // Bl
    // 'BuildConstr_v4:21' [M, N] = size(BasisVal);
    M = BasisVal.size(0);
    N = BasisVal.size(1);
    // 'BuildConstr_v4:22' Nx  = N * Ncrv;
    Nx = static_cast<double>(BasisVal.size(1)) * static_cast<double>(CurvStructs.size(1));
    // 'BuildConstr_v4:23' Nc  = 7 * M * Ncrv;
    Nc = 7.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size(1));
    // 'BuildConstr_v4:24' Nec = 2 * (Ncrv + 1);
    Nec = 2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0);
    //  M     : number of discretization
    //  N     : number of coefficients
    //  Nx    : number of decision variable
    //  Nc    : number of inequality constraints
    //  Nec   : number of equality constraints
    // 'BuildConstr_v4:31' A      = sparse(Nc,   Nx);
    coder::b_sparse(Nc, Nx, A);
    //  preallocation
    // 'BuildConstr_v4:32' b      = zeros(Nc,   1);
    loop_ub_tmp = static_cast<int>(Nc);
    b.set_size(loop_ub_tmp);
    for (int i1{0}; i1 < loop_ub_tmp; i1++) {
        b[i1] = 0.0;
    }
    int i2;
    //  preallocation
    // 'BuildConstr_v4:33' Aeq    = zeros(Nec, Nx);
    loop_ub = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
    b_loop_ub_tmp = static_cast<int>(Nx);
    i2 = static_cast<int>(Nec);
    Aeq.set_size(i2, b_loop_ub_tmp);
    for (int i3{0}; i3 < b_loop_ub_tmp; i3++) {
        for (int i4{0}; i4 < loop_ub; i4++) {
            Aeq[i4 + Aeq.size(0) * i3] = 0.0;
        }
    }
    int i5;
    //  preallocation
    // 'BuildConstr_v4:34' beq    = zeros(Nec, 1);
    i5 = static_cast<int>(Nec);
    beq.set_size(i5);
    for (int i6{0}; i6 < loop_ub; i6++) {
        beq[i6] = 0.0;
    }
    //  preallocation
    //  A     : Inequality matrix
    //  b     : Inequality vector
    //  Aeq   : Inequality matrix
    //  beq   : Inequality vector
    //  coder.varsize('b', [7*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
    //  coder.varsize('Aeq', [2*(FeedoptLimits.MaxNHorz+1),
    //  FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); coder.varsize('beq',
    //  [2*(FeedoptLimits.MaxNHorz+1), 1], [1,0]); Compute the partial derivatives
    // 'BuildConstr_v4:45' [~, r1D, r2D] = EvalCurvStruct(ctx, CurvStructs(1), u_vec);
    b_u_vec.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1) - 1;
    for (int i7{0}; i7 <= b_loop_ub; i7++) {
        b_u_vec[i7] = u_vec[i7];
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
    // 'BuildConstr_v4:47' vmax = CurvStructs(1).FeedRate;
    // 'BuildConstr_v4:49' r1D_sqnorm    = sum(r1D.^2);
    r.set_size(3, r1D.size(1));
    c_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < c_loop_ub; i8++) {
        double b_varargin_1;
        double c_varargin_1;
        double d_varargin_1;
        b_varargin_1 = r1D[3 * i8];
        r[3 * i8] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = r1D[3 * i8 + 1];
        r[3 * i8 + 1] = std::pow(c_varargin_1, 2.0);
        d_varargin_1 = r1D[3 * i8 + 2];
        r[3 * i8 + 2] = std::pow(d_varargin_1, 2.0);
    }
    coder::sum(r, r1D_sqnorm);
    //  squared norm
    //
    // 'BuildConstr_v4:51' t_0 = r1D(:, 1)/norm(r1D(:, 1));
    //  unit tangent vector @ start
    //
    // 'BuildConstr_v4:54' R1 = bsxfun(@times, r2D(1, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(1,
    // :)' , BasisValD);
    d_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i9{0}; i9 < d_loop_ub; i9++) {
        b_r2D[i9] = r2D[3 * i9];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    e_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        b_r1D[i10] = r1D[3 * i10];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int f_loop_ub;
        R1.set_size(r1.size(0), r1.size(1));
        f_loop_ub = r1.size(1);
        for (int i11{0}; i11 < f_loop_ub; i11++) {
            int h_loop_ub;
            int i13;
            int scalarLB;
            int vectorUB;
            h_loop_ub = r1.size(0);
            scalarLB = (r1.size(0) / 2) << 1;
            vectorUB = scalarLB - 2;
            for (i13 = 0; i13 <= vectorUB; i13 += 2) {
                __m128d r3;
                __m128d r4;
                r3 = _mm_loadu_pd(&r2[i13 + r2.size(0) * i11]);
                r4 = _mm_loadu_pd(&r1[i13 + r1.size(0) * i11]);
                _mm_storeu_pd(&R1[i13 + R1.size(0) * i11],
                              _mm_add_pd(r4, _mm_mul_pd(_mm_set1_pd(0.5), r3)));
            }
            for (i13 = scalarLB; i13 < h_loop_ub; i13++) {
                R1[i13 + R1.size(0) * i11] =
                    r1[i13 + r1.size(0) * i11] + 0.5 * r2[i13 + r2.size(0) * i11];
            }
        }
    } else {
        d_binary_expand_op(R1, r1, r2);
    }
    // 'BuildConstr_v4:55' R2 = bsxfun(@times, r2D(2, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(2,
    // :)' , BasisValD);
    g_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i12{0}; i12 < g_loop_ub; i12++) {
        b_r2D[i12] = r2D[3 * i12 + 1];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    i_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i14{0}; i14 < i_loop_ub; i14++) {
        b_r1D[i14] = r1D[3 * i14 + 1];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int j_loop_ub;
        R2.set_size(r1.size(0), r1.size(1));
        j_loop_ub = r1.size(1);
        for (int i15{0}; i15 < j_loop_ub; i15++) {
            int b_scalarLB;
            int b_vectorUB;
            int i17;
            int l_loop_ub;
            l_loop_ub = r1.size(0);
            b_scalarLB = (r1.size(0) / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (i17 = 0; i17 <= b_vectorUB; i17 += 2) {
                __m128d r5;
                __m128d r6;
                r5 = _mm_loadu_pd(&r2[i17 + r2.size(0) * i15]);
                r6 = _mm_loadu_pd(&r1[i17 + r1.size(0) * i15]);
                _mm_storeu_pd(&R2[i17 + R2.size(0) * i15],
                              _mm_add_pd(r6, _mm_mul_pd(_mm_set1_pd(0.5), r5)));
            }
            for (i17 = b_scalarLB; i17 < l_loop_ub; i17++) {
                R2[i17 + R2.size(0) * i15] =
                    r1[i17 + r1.size(0) * i15] + 0.5 * r2[i17 + r2.size(0) * i15];
            }
        }
    } else {
        d_binary_expand_op(R2, r1, r2);
    }
    // 'BuildConstr_v4:56' R3 = bsxfun(@times, r2D(3, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(3,
    // :)' , BasisValD);
    k_loop_ub = r2D.size(1);
    b_r2D.set_size(r2D.size(1));
    for (int i16{0}; i16 < k_loop_ub; i16++) {
        b_r2D[i16] = r2D[3 * i16 + 2];
    }
    coder::bsxfun(b_r2D, BasisVal, r1);
    m_loop_ub = r1D.size(1);
    b_r1D.set_size(r1D.size(1));
    for (int i18{0}; i18 < m_loop_ub; i18++) {
        b_r1D[i18] = r1D[3 * i18 + 2];
    }
    coder::bsxfun(b_r1D, BasisValD, r2);
    if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
        int n_loop_ub;
        R3.set_size(r1.size(0), r1.size(1));
        n_loop_ub = r1.size(1);
        for (int i19{0}; i19 < n_loop_ub; i19++) {
            int c_scalarLB;
            int c_vectorUB;
            int i20;
            int o_loop_ub;
            o_loop_ub = r1.size(0);
            c_scalarLB = (r1.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (i20 = 0; i20 <= c_vectorUB; i20 += 2) {
                __m128d r7;
                __m128d r8;
                r7 = _mm_loadu_pd(&r2[i20 + r2.size(0) * i19]);
                r8 = _mm_loadu_pd(&r1[i20 + r1.size(0) * i19]);
                _mm_storeu_pd(&R3[i20 + R3.size(0) * i19],
                              _mm_add_pd(r8, _mm_mul_pd(_mm_set1_pd(0.5), r7)));
            }
            for (i20 = c_scalarLB; i20 < o_loop_ub; i20++) {
                R3[i20 + R3.size(0) * i19] =
                    r1[i20 + r1.size(0) * i19] + 0.5 * r2[i20 + r2.size(0) * i19];
            }
        }
    } else {
        d_binary_expand_op(R3, r1, r2);
    }
    //
    // 'BuildConstr_v4:59' A(1:7*M, 1:N)  = [BasisVal;
    // 'BuildConstr_v4:60'     R1;
    // 'BuildConstr_v4:61'     -R1;
    // 'BuildConstr_v4:62'     R2;
    // 'BuildConstr_v4:63'     -R2;
    // 'BuildConstr_v4:64'     R3;
    // 'BuildConstr_v4:65'     -R3];
    varargin_3.set_size(R1.size(0), R1.size(1));
    p_loop_ub = R1.size(1);
    for (int i21{0}; i21 < p_loop_ub; i21++) {
        int d_scalarLB;
        int d_vectorUB;
        int i23;
        int q_loop_ub;
        q_loop_ub = R1.size(0);
        d_scalarLB = (R1.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i23 = 0; i23 <= d_vectorUB; i23 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&R1[i23 + R1.size(0) * i21]);
            _mm_storeu_pd(&varargin_3[i23 + varargin_3.size(0) * i21],
                          _mm_mul_pd(r9, _mm_set1_pd(-1.0)));
        }
        for (i23 = d_scalarLB; i23 < q_loop_ub; i23++) {
            varargin_3[i23 + varargin_3.size(0) * i21] = -R1[i23 + R1.size(0) * i21];
        }
    }
    varargin_5.set_size(R2.size(0), R2.size(1));
    r_loop_ub = R2.size(1);
    for (int i22{0}; i22 < r_loop_ub; i22++) {
        int e_scalarLB;
        int e_vectorUB;
        int i25;
        int s_loop_ub;
        s_loop_ub = R2.size(0);
        e_scalarLB = (R2.size(0) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (i25 = 0; i25 <= e_vectorUB; i25 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&R2[i25 + R2.size(0) * i22]);
            _mm_storeu_pd(&varargin_5[i25 + varargin_5.size(0) * i22],
                          _mm_mul_pd(r10, _mm_set1_pd(-1.0)));
        }
        for (i25 = e_scalarLB; i25 < s_loop_ub; i25++) {
            varargin_5[i25 + varargin_5.size(0) * i22] = -R2[i25 + R2.size(0) * i22];
        }
    }
    varargin_7.set_size(R3.size(0), R3.size(1));
    t_loop_ub = R3.size(1);
    for (int i24{0}; i24 < t_loop_ub; i24++) {
        int f_scalarLB;
        int f_vectorUB;
        int i26;
        int u_loop_ub;
        u_loop_ub = R3.size(0);
        f_scalarLB = (R3.size(0) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (i26 = 0; i26 <= f_vectorUB; i26 += 2) {
            __m128d r11;
            r11 = _mm_loadu_pd(&R3[i26 + R3.size(0) * i24]);
            _mm_storeu_pd(&varargin_7[i26 + varargin_7.size(0) * i24],
                          _mm_mul_pd(r11, _mm_set1_pd(-1.0)));
        }
        for (i26 = f_scalarLB; i26 < u_loop_ub; i26++) {
            varargin_7[i26 + varargin_7.size(0) * i24] = -R3[i26 + R3.size(0) * i24];
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
        int v_loop_ub;
        y.set_size(1, static_cast<int>(b_b - 1.0) + 1);
        v_loop_ub = static_cast<int>(b_b - 1.0);
        for (int i27{0}; i27 <= v_loop_ub; i27++) {
            y[i27] = static_cast<double>(i27) + 1.0;
        }
    }
    if (BasisVal.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        int w_loop_ub;
        b_y.set_size(1, BasisVal.size(1));
        w_loop_ub = BasisVal.size(1) - 1;
        for (int i28{0}; i28 <= w_loop_ub; i28++) {
            b_y[i28] = static_cast<double>(i28) + 1.0;
        }
    }
    h_input_sizes_idx_0 = input_sizes_idx_0;
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_input_sizes_idx_0 = c_input_sizes_idx_0;
    c_input_sizes_idx_0 = d_input_sizes_idx_0;
    d_input_sizes_idx_0 = e_input_sizes_idx_0;
    i29 = h_input_sizes_idx_0 + input_sizes_idx_0;
    i30 = i29 + b_input_sizes_idx_0;
    b_BasisVal.set_size(
        (((i30 + c_input_sizes_idx_0) + d_input_sizes_idx_0) + f_input_sizes_idx_0) +
            g_input_sizes_idx_0,
        result);
    for (int i31{0}; i31 < result; i31++) {
        for (int i33{0}; i33 < h_input_sizes_idx_0; i33++) {
            b_BasisVal[i33 + b_BasisVal.size(0) * i31] = BasisVal[i33 + h_input_sizes_idx_0 * i31];
        }
    }
    for (int i32{0}; i32 < result; i32++) {
        for (int i35{0}; i35 < input_sizes_idx_0; i35++) {
            b_BasisVal[(i35 + h_input_sizes_idx_0) + b_BasisVal.size(0) * i32] =
                R1[i35 + input_sizes_idx_0 * i32];
        }
    }
    for (int i34{0}; i34 < result; i34++) {
        for (int i37{0}; i37 < b_input_sizes_idx_0; i37++) {
            b_BasisVal[((i37 + h_input_sizes_idx_0) + input_sizes_idx_0) +
                       b_BasisVal.size(0) * i34] = varargin_3[i37 + b_input_sizes_idx_0 * i34];
        }
    }
    for (int i36{0}; i36 < result; i36++) {
        for (int i39{0}; i39 < c_input_sizes_idx_0; i39++) {
            b_BasisVal[(((i39 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i36] = R2[i39 + c_input_sizes_idx_0 * i36];
        }
    }
    for (int i38{0}; i38 < result; i38++) {
        for (int i41{0}; i41 < d_input_sizes_idx_0; i41++) {
            b_BasisVal[((((i41 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                        c_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i38] = varargin_5[i41 + d_input_sizes_idx_0 * i38];
        }
    }
    for (int i40{0}; i40 < result; i40++) {
        for (int i43{0}; i43 < f_input_sizes_idx_0; i43++) {
            b_BasisVal[((((i43 + i29) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                        d_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i40] = R3[i43 + f_input_sizes_idx_0 * i40];
        }
    }
    for (int i42{0}; i42 < result; i42++) {
        for (int i44{0}; i44 < g_input_sizes_idx_0; i44++) {
            b_BasisVal[((((i44 + i30) + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                        f_input_sizes_idx_0) +
                       b_BasisVal.size(0) * i42] = varargin_7[i44 + g_input_sizes_idx_0 * i42];
        }
    }
    A->parenAssign(b_BasisVal, y, b_y);
    //
    // 'BuildConstr_v4:67' bC1 = (vmax)^2./r1D_sqnorm';
    x = CurvStructs[0].FeedRate * CurvStructs[0].FeedRate;
    // 'BuildConstr_v4:68' bC2 = amax(1)*ones(M, 1);
    bC2.set_size(BasisVal.size(0));
    x_loop_ub = BasisVal.size(0);
    for (int i45{0}; i45 < x_loop_ub; i45++) {
        bC2[i45] = amax[0];
    }
    // 'BuildConstr_v4:69' bC3 = amax(2)*ones(M, 1);
    bC3.set_size(BasisVal.size(0));
    y_loop_ub = BasisVal.size(0);
    for (int i46{0}; i46 < y_loop_ub; i46++) {
        bC3[i46] = amax[1];
    }
    // 'BuildConstr_v4:70' bC4 = amax(3)*ones(M, 1);
    bC4.set_size(BasisVal.size(0));
    ab_loop_ub = BasisVal.size(0);
    for (int i47{0}; i47 < ab_loop_ub; i47++) {
        bC4[i47] = amax[2];
    }
    //
    // 'BuildConstr_v4:72' b(1:7*M)       = [bC1;
    // 'BuildConstr_v4:73'     bC2;
    // 'BuildConstr_v4:74'     bC2;
    // 'BuildConstr_v4:75'     bC3;
    // 'BuildConstr_v4:76'     bC3;
    // 'BuildConstr_v4:77'     bC4;
    // 'BuildConstr_v4:78'     bC4];
    unnamed_idx_1 = r1D_sqnorm.size(1);
    b_unnamed_idx_1 = BasisVal.size(0);
    c_unnamed_idx_1 = BasisVal.size(0);
    d_unnamed_idx_1 = BasisVal.size(0);
    e_unnamed_idx_1 = BasisVal.size(0);
    f_unnamed_idx_1 = BasisVal.size(0);
    bb_loop_ub = r1D_sqnorm.size(1);
    g_scalarLB = (r1D_sqnorm.size(1) / 2) << 1;
    g_vectorUB = g_scalarLB - 2;
    for (i48 = 0; i48 <= g_vectorUB; i48 += 2) {
        __m128d r12;
        r12 = _mm_loadu_pd(&r1D_sqnorm[i48]);
        _mm_storeu_pd(&b[i48], _mm_div_pd(_mm_set1_pd(x), r12));
    }
    for (i48 = g_scalarLB; i48 < bb_loop_ub; i48++) {
        b[i48] = x / r1D_sqnorm[i48];
    }
    cb_loop_ub = BasisVal.size(0);
    for (int i49{0}; i49 < cb_loop_ub; i49++) {
        b[i49 + unnamed_idx_1] = amax[0];
    }
    db_loop_ub = BasisVal.size(0);
    for (int i50{0}; i50 < db_loop_ub; i50++) {
        b[(i50 + unnamed_idx_1) + b_unnamed_idx_1] = amax[0];
    }
    eb_loop_ub = BasisVal.size(0);
    for (int i51{0}; i51 < eb_loop_ub; i51++) {
        b[((i51 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = amax[1];
    }
    fb_loop_ub = BasisVal.size(0);
    for (int i52{0}; i52 < fb_loop_ub; i52++) {
        b[(((i52 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1] =
            amax[1];
    }
    gb_loop_ub = BasisVal.size(0);
    for (int i53{0}; i53 < gb_loop_ub; i53++) {
        b[((((i53 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
          e_unnamed_idx_1] = amax[2];
    }
    hb_loop_ub = BasisVal.size(0);
    for (int i54{0}; i54 < hb_loop_ub; i54++) {
        b[(((((i54 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
           e_unnamed_idx_1) +
          f_unnamed_idx_1] = amax[2];
    }
    //
    // 'BuildConstr_v4:80' Aeq(1:2, 1:N)   = [BasisVal(1, :);
    // 'BuildConstr_v4:81'     t_0' * [r2D(1, 1)   * BasisVal(1, :)   + 0.5*r1D(1, 1)   *
    // BasisValD(1, :); 'BuildConstr_v4:82'     r2D(2, 1)   * BasisVal(1, :)   + 0.5*r1D(2, 1)   *
    // BasisValD(1, :); 'BuildConstr_v4:83'     r2D(3, 1)   * BasisVal(1, :)   + 0.5*r1D(3, 1)   *
    // BasisValD(1, :)]];
    a = r2D[0];
    b_a = 0.5 * r1D[0];
    c_a = r2D[1];
    d_a = 0.5 * r1D[1];
    e_a = r2D[2];
    f_a = 0.5 * r1D[2];
    if (BasisVal.size(1) == BasisValD.size(1)) {
        __m128d r14;
        double d;
        int jb_loop_ub;
        int lb_loop_ub;
        int mb_loop_ub;
        d = coder::b_norm(*(double(*)[3]) & r1D[0]);
        r14 = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&c_r1D[0], _mm_div_pd(r14, _mm_set1_pd(d)));
        c_r1D[2] = r1D[2] / d;
        jb_loop_ub = BasisVal.size(1);
        lb_loop_ub = BasisVal.size(1);
        mb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i57{0}; i57 < jb_loop_ub; i57++) {
            g_a[3 * i57] =
                a * BasisVal[BasisVal.size(0) * i57] + b_a * BasisValD[BasisValD.size(0) * i57];
        }
        for (int i58{0}; i58 < lb_loop_ub; i58++) {
            g_a[3 * i58 + 1] =
                c_a * BasisVal[BasisVal.size(0) * i58] + d_a * BasisValD[BasisValD.size(0) * i58];
        }
        for (int i59{0}; i59 < mb_loop_ub; i59++) {
            g_a[3 * i59 + 2] =
                e_a * BasisVal[BasisVal.size(0) * i59] + f_a * BasisValD[BasisValD.size(0) * i59];
        }
        coder::internal::blas::mtimes(c_r1D, g_a, r13);
    } else {
        b_binary_expand_op(r13, r1D, a, BasisVal, b_a, BasisValD, c_a, d_a, e_a, f_a);
    }
    ib_loop_ub = BasisVal.size(1);
    for (int i55{0}; i55 < ib_loop_ub; i55++) {
        Aeq[Aeq.size(0) * i55] = BasisVal[BasisVal.size(0) * i55];
    }
    kb_loop_ub = r13.size(1);
    for (int i56{0}; i56 < kb_loop_ub; i56++) {
        Aeq[Aeq.size(0) * i56 + 1] = r13[i56];
    }
    // 'BuildConstr_v4:84' beq(1:2)       = [(v_0(1)^2)/r1D_sqnorm(1);
    // 'BuildConstr_v4:85'     at_0(1)];
    beq[0] = v_0 * v_0 / r1D_sqnorm[0];
    beq[1] = at_0;
    //  This should be the correct behavior for a single segment,
    //  reusing the r1D norm
    // 'BuildConstr_v4:89' r1Dn_sqnorm = r1D_sqnorm;
    // 'BuildConstr_v4:91' for k = 1:Ncrv-1
    i60 = CurvStructs.size(1);
    if (0 <= CurvStructs.size(1) - 2) {
        b_unnamed_idx_1 = bC2.size(0);
        c_unnamed_idx_1 = bC2.size(0);
        d_unnamed_idx_1 = bC3.size(0);
        e_unnamed_idx_1 = bC3.size(0);
        f_unnamed_idx_1 = bC4.size(0);
        nb_loop_ub = bC2.size(0);
        ob_loop_ub = bC2.size(0);
        pb_loop_ub = bC3.size(0);
        qb_loop_ub = bC3.size(0);
        rb_loop_ub = bC4.size(0);
        sb_loop_ub = bC4.size(0);
    }
    for (int b_k{0}; b_k <= i60 - 2; b_k++) {
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
        int bd_loop_ub;
        int c_result;
        int cc_loop_ub;
        int cd_loop_ub;
        int dd_loop_ub;
        int ec_loop_ub;
        int ed_loop_ub;
        int gc_loop_ub;
        int gd_loop_ub;
        int hd_loop_ub;
        int i117;
        int i118;
        int i125;
        int i127;
        int i129;
        int i132;
        int i_input_sizes_idx_0;
        int ic_loop_ub;
        int id_loop_ub;
        int j_input_sizes_idx_0;
        int jd_loop_ub;
        int k_input_sizes_idx_0;
        int kc_loop_ub;
        int l_input_sizes_idx_0;
        int m_input_sizes_idx_0;
        int mc_loop_ub;
        int n_input_sizes_idx_0;
        int o_input_sizes_idx_0;
        int o_scalarLB;
        int o_vectorUB;
        int sc_loop_ub;
        int tb_loop_ub;
        unsigned int u;
        int uc_loop_ub;
        int wb_loop_ub;
        int wc_loop_ub;
        bool c_empty_non_axis_sizes;
        // 'BuildConstr_v4:92' if ctx.cfg.UseDynamicBreakpoints
        if (ctx_cfg_UseDynamicBreakpoints) {
            double varargin_2;
            // 'BuildConstr_v4:93' NBreak = max(4, floor(LengthCurv(ctx, CurvStructs(k+1), 0,
            // 1)/ctx.cfg.DynamicBreakpointsDistance));
            varargin_2 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                    &CurvStructs[b_k + 1]) /
                         ctx_cfg_DynamicBreakpointsDistance;
            // 'BuildConstr_v4:94' if ctx.cfg.UseLinearBreakpoints
            if (ctx_cfg_UseLinearBreakpoints) {
                double b_delta1;
                int i61;
                int i63;
                // 'BuildConstr_v4:95' Bl = bspline_create(ctx.cfg.SplineDegree,
                // linspace(0,1,NBreak));
                i61 = static_cast<int>(std::fmax(4.0, std::floor(varargin_2)));
                breakpoints.set_size(1, i61);
                breakpoints[i61 - 1] = 1.0;
                breakpoints[0] = 0.0;
                b_delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
                i63 = breakpoints.size(1);
                for (int c_k{0}; c_k <= i63 - 3; c_k++) {
                    breakpoints[c_k + 1] = (static_cast<double>(c_k) + 1.0) * b_delta1;
                }
                // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
                // 'bspline_create:3' nbreak = length(breakpoints);
                // 'bspline_create:4' ncoeff = nbreak + degree - 2;
                Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
                // 'bspline_create:5' h = uint64(0);
                // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c',
                // '$(START_DIR)/src'); 'bspline_create:8' coder.updateBuildInfo('addLinkFlags',
                // LibInfo.gsl.lflags); 'bspline_create:9' coder.cinclude('src/c_spline.h');
                // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints',
                // coder.wref(h), degree, breakpoints, int32(nbreak) );
                c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                                                  breakpoints.size(1));
                // 'bspline_create:11' Bl.ncoeff = ncoeff;
                // 'bspline_create:12' Bl.breakpoints = breakpoints;
                // 'bspline_create:13' Bl.handle = h;
                // 'bspline_create:14' Bl.degree = int32(degree);
                // 'bspline_create:15' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
            }
            // 'BuildConstr_v4:98' [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
            bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
        }
        // 'BuildConstr_v4:100' [M, N] = size(BasisVal);
        M = BasisVal.size(0);
        N = BasisVal.size(1);
        // 'BuildConstr_v4:102' [~, r1Dn, r2Dn] = EvalCurvStruct(ctx, CurvStructs(k+1), u_vec);
        c_u_vec.set_size(1, u_vec.size(1));
        tb_loop_ub = u_vec.size(1) - 1;
        for (int i62{0}; i62 <= tb_loop_ub; i62++) {
            c_u_vec[i62] = u_vec[i62];
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
        // 'BuildConstr_v4:103' vmax            = CurvStructs(k+1).FeedRate;
        // 'BuildConstr_v4:104' r1Dn_sqnorm     = sum(r1Dn.^2);
        wb_loop_ub = r1Dn.size(1);
        r.set_size(3, r1Dn.size(1));
        for (int i67{0}; i67 < wb_loop_ub; i67++) {
            double e_varargin_1;
            double f_varargin_1;
            double g_varargin_1;
            e_varargin_1 = r1Dn[3 * i67];
            r[3 * i67] = std::pow(e_varargin_1, 2.0);
            f_varargin_1 = r1Dn[3 * i67 + 1];
            r[3 * i67 + 1] = std::pow(f_varargin_1, 2.0);
            g_varargin_1 = r1Dn[3 * i67 + 2];
            r[3 * i67 + 2] = std::pow(g_varargin_1, 2.0);
        }
        __m128d r16;
        double d3;
        double x_tmp;
        int f_r1D;
        int g_r1D;
        coder::sum(r, r1D_sqnorm);
        //  squared norm
        // 'BuildConstr_v4:105' bC1 = (vmax)^2./r1Dn_sqnorm';
        x_tmp = CurvStructs[b_k + 1].FeedRate;
        b_x = x_tmp * x_tmp;
        // 'BuildConstr_v4:106' t_1 = r1D(:, end)/norm(r1D(:, end));
        f_r1D = r1D.size(1);
        g_r1D = r1D.size(1);
        d3 = coder::b_norm(*(double(*)[3]) & r1D[3 * (g_r1D - 1)]);
        r16 = _mm_loadu_pd(&r1D[3 * (f_r1D - 1)]);
        _mm_storeu_pd(&t_1[0], _mm_div_pd(r16, _mm_set1_pd(d3)));
        t_1[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d3;
        //  unit tangent vector @ end of previous piece
        //
        // 'BuildConstr_v4:108' R1 = bsxfun(@times, r2Dn(1, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(1, :)' , BasisValD);
        cc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i73{0}; i73 < cc_loop_ub; i73++) {
            b_r2Dn[i73] = r2Dn[3 * i73];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        ec_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i74{0}; i74 < ec_loop_ub; i74++) {
            b_r1Dn[i74] = r1Dn[3 * i74];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int fc_loop_ub;
            R1.set_size(r1.size(0), r1.size(1));
            fc_loop_ub = r1.size(1);
            for (int i76{0}; i76 < fc_loop_ub; i76++) {
                int h_scalarLB;
                int h_vectorUB;
                int hc_loop_ub;
                int i78;
                hc_loop_ub = r1.size(0);
                h_scalarLB = (r1.size(0) / 2) << 1;
                h_vectorUB = h_scalarLB - 2;
                for (i78 = 0; i78 <= h_vectorUB; i78 += 2) {
                    __m128d r18;
                    __m128d r19;
                    r18 = _mm_loadu_pd(&r2[i78 + r2.size(0) * i76]);
                    r19 = _mm_loadu_pd(&r1[i78 + r1.size(0) * i76]);
                    _mm_storeu_pd(&R1[i78 + R1.size(0) * i76],
                                  _mm_add_pd(r19, _mm_mul_pd(_mm_set1_pd(0.5), r18)));
                }
                for (i78 = h_scalarLB; i78 < hc_loop_ub; i78++) {
                    R1[i78 + R1.size(0) * i76] =
                        r1[i78 + r1.size(0) * i76] + 0.5 * r2[i78 + r2.size(0) * i76];
                }
            }
        } else {
            d_binary_expand_op(R1, r1, r2);
        }
        // 'BuildConstr_v4:109' R2 = bsxfun(@times, r2Dn(2, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(2, :)' , BasisValD);
        gc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i77{0}; i77 < gc_loop_ub; i77++) {
            b_r2Dn[i77] = r2Dn[3 * i77 + 1];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        ic_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i79{0}; i79 < ic_loop_ub; i79++) {
            b_r1Dn[i79] = r1Dn[3 * i79 + 1];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int jc_loop_ub;
            R2.set_size(r1.size(0), r1.size(1));
            jc_loop_ub = r1.size(1);
            for (int i80{0}; i80 < jc_loop_ub; i80++) {
                int i82;
                int i_scalarLB;
                int i_vectorUB;
                int lc_loop_ub;
                lc_loop_ub = r1.size(0);
                i_scalarLB = (r1.size(0) / 2) << 1;
                i_vectorUB = i_scalarLB - 2;
                for (i82 = 0; i82 <= i_vectorUB; i82 += 2) {
                    __m128d r20;
                    __m128d r21;
                    r20 = _mm_loadu_pd(&r2[i82 + r2.size(0) * i80]);
                    r21 = _mm_loadu_pd(&r1[i82 + r1.size(0) * i80]);
                    _mm_storeu_pd(&R2[i82 + R2.size(0) * i80],
                                  _mm_add_pd(r21, _mm_mul_pd(_mm_set1_pd(0.5), r20)));
                }
                for (i82 = i_scalarLB; i82 < lc_loop_ub; i82++) {
                    R2[i82 + R2.size(0) * i80] =
                        r1[i82 + r1.size(0) * i80] + 0.5 * r2[i82 + r2.size(0) * i80];
                }
            }
        } else {
            d_binary_expand_op(R2, r1, r2);
        }
        // 'BuildConstr_v4:110' R3 = bsxfun(@times, r2Dn(3, :)' , BasisVal) + 0.5*bsxfun(@times,
        // r1Dn(3, :)' , BasisValD);
        kc_loop_ub = r2Dn.size(1);
        b_r2Dn.set_size(r2Dn.size(1));
        for (int i81{0}; i81 < kc_loop_ub; i81++) {
            b_r2Dn[i81] = r2Dn[3 * i81 + 2];
        }
        coder::bsxfun(b_r2Dn, BasisVal, r1);
        mc_loop_ub = r1Dn.size(1);
        b_r1Dn.set_size(r1Dn.size(1));
        for (int i85{0}; i85 < mc_loop_ub; i85++) {
            b_r1Dn[i85] = r1Dn[3 * i85 + 2];
        }
        coder::bsxfun(b_r1Dn, BasisValD, r2);
        if ((r1.size(0) == r2.size(0)) && (r1.size(1) == r2.size(1))) {
            int pc_loop_ub;
            R3.set_size(r1.size(0), r1.size(1));
            pc_loop_ub = r1.size(1);
            for (int i91{0}; i91 < pc_loop_ub; i91++) {
                int i93;
                int j_scalarLB;
                int j_vectorUB;
                int qc_loop_ub;
                qc_loop_ub = r1.size(0);
                j_scalarLB = (r1.size(0) / 2) << 1;
                j_vectorUB = j_scalarLB - 2;
                for (i93 = 0; i93 <= j_vectorUB; i93 += 2) {
                    __m128d r22;
                    __m128d r23;
                    r22 = _mm_loadu_pd(&r2[i93 + r2.size(0) * i91]);
                    r23 = _mm_loadu_pd(&r1[i93 + r1.size(0) * i91]);
                    _mm_storeu_pd(&R3[i93 + R3.size(0) * i91],
                                  _mm_add_pd(r23, _mm_mul_pd(_mm_set1_pd(0.5), r22)));
                }
                for (i93 = j_scalarLB; i93 < qc_loop_ub; i93++) {
                    R3[i93 + R3.size(0) * i91] =
                        r1[i93 + r1.size(0) * i91] + 0.5 * r2[i93 + r2.size(0) * i91];
                }
            }
        } else {
            d_binary_expand_op(R3, r1, r2);
        }
        //
        // 'BuildConstr_v4:112' A(k*7*M+1:(k+1)*7*M, k*N+1:(k+1)*N) = ...
        // 'BuildConstr_v4:113'         [BasisVal;
        // 'BuildConstr_v4:114'         R1;
        // 'BuildConstr_v4:115'         -R1;
        // 'BuildConstr_v4:116'         R2;
        // 'BuildConstr_v4:117'         -R2;
        // 'BuildConstr_v4:118'         R3;
        // 'BuildConstr_v4:119'         -R3];
        varargin_3.set_size(R1.size(0), R1.size(1));
        sc_loop_ub = R1.size(1);
        for (int i95{0}; i95 < sc_loop_ub; i95++) {
            int i97;
            int l_scalarLB;
            int l_vectorUB;
            int tc_loop_ub;
            tc_loop_ub = R1.size(0);
            l_scalarLB = (R1.size(0) / 2) << 1;
            l_vectorUB = l_scalarLB - 2;
            for (i97 = 0; i97 <= l_vectorUB; i97 += 2) {
                __m128d r26;
                r26 = _mm_loadu_pd(&R1[i97 + R1.size(0) * i95]);
                _mm_storeu_pd(&varargin_3[i97 + varargin_3.size(0) * i95],
                              _mm_mul_pd(r26, _mm_set1_pd(-1.0)));
            }
            for (i97 = l_scalarLB; i97 < tc_loop_ub; i97++) {
                varargin_3[i97 + varargin_3.size(0) * i95] = -R1[i97 + R1.size(0) * i95];
            }
        }
        varargin_5.set_size(R2.size(0), R2.size(1));
        uc_loop_ub = R2.size(1);
        for (int i96{0}; i96 < uc_loop_ub; i96++) {
            int i99;
            int m_scalarLB;
            int m_vectorUB;
            int vc_loop_ub;
            vc_loop_ub = R2.size(0);
            m_scalarLB = (R2.size(0) / 2) << 1;
            m_vectorUB = m_scalarLB - 2;
            for (i99 = 0; i99 <= m_vectorUB; i99 += 2) {
                __m128d r27;
                r27 = _mm_loadu_pd(&R2[i99 + R2.size(0) * i96]);
                _mm_storeu_pd(&varargin_5[i99 + varargin_5.size(0) * i96],
                              _mm_mul_pd(r27, _mm_set1_pd(-1.0)));
            }
            for (i99 = m_scalarLB; i99 < vc_loop_ub; i99++) {
                varargin_5[i99 + varargin_5.size(0) * i96] = -R2[i99 + R2.size(0) * i96];
            }
        }
        varargin_7.set_size(R3.size(0), R3.size(1));
        wc_loop_ub = R3.size(1);
        for (int i98{0}; i98 < wc_loop_ub; i98++) {
            int i100;
            int n_scalarLB;
            int n_vectorUB;
            int xc_loop_ub;
            xc_loop_ub = R3.size(0);
            n_scalarLB = (R3.size(0) / 2) << 1;
            n_vectorUB = n_scalarLB - 2;
            for (i100 = 0; i100 <= n_vectorUB; i100 += 2) {
                __m128d r28;
                r28 = _mm_loadu_pd(&R3[i100 + R3.size(0) * i98]);
                _mm_storeu_pd(&varargin_7[i100 + varargin_7.size(0) * i98],
                              _mm_mul_pd(r28, _mm_set1_pd(-1.0)));
            }
            for (i100 = n_scalarLB; i100 < xc_loop_ub; i100++) {
                varargin_7[i100 + varargin_7.size(0) * i98] = -R3[i100 + R3.size(0) * i98];
            }
        }
        if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
            c_result = BasisVal.size(1);
        } else if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            c_result = R1.size(1);
        } else if ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)) {
            c_result = varargin_3.size(1);
        } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
            c_result = R2.size(1);
        } else if ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)) {
            c_result = varargin_5.size(1);
        } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
            c_result = R3.size(1);
        } else if ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)) {
            c_result = varargin_7.size(1);
        } else {
            c_result = BasisVal.size(1);
            if (R1.size(1) > BasisVal.size(1)) {
                c_result = R1.size(1);
            }
            if (varargin_3.size(1) > c_result) {
                c_result = varargin_3.size(1);
            }
            if (R2.size(1) > c_result) {
                c_result = R2.size(1);
            }
            if (varargin_5.size(1) > c_result) {
                c_result = varargin_5.size(1);
            }
            if (R3.size(1) > c_result) {
                c_result = R3.size(1);
            }
            if (varargin_7.size(1) > c_result) {
                c_result = varargin_7.size(1);
            }
        }
        c_empty_non_axis_sizes = (c_result == 0);
        if (c_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            i_input_sizes_idx_0 = BasisVal.size(0);
        } else {
            i_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
            j_input_sizes_idx_0 = R1.size(0);
        } else {
            j_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0))) {
            k_input_sizes_idx_0 = varargin_3.size(0);
        } else {
            k_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
            l_input_sizes_idx_0 = R2.size(0);
        } else {
            l_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0))) {
            m_input_sizes_idx_0 = varargin_5.size(0);
        } else {
            m_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
            n_input_sizes_idx_0 = R3.size(0);
        } else {
            n_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0))) {
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
            int yc_loop_ub;
            yc_loop_ub = static_cast<int>(c_b - n_a);
            y.set_size(1, yc_loop_ub + 1);
            for (int i101{0}; i101 <= yc_loop_ub; i101++) {
                y[i101] = n_a + static_cast<double>(i101);
            }
        }
        o_a = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        d_b = ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1));
        if (d_b < o_a) {
            b_y.set_size(1, 0);
        } else {
            int ad_loop_ub;
            ad_loop_ub = static_cast<int>(d_b - o_a);
            b_y.set_size(1, ad_loop_ub + 1);
            for (int i102{0}; i102 <= ad_loop_ub; i102++) {
                b_y[i102] = o_a + static_cast<double>(i102);
            }
        }
        b_BasisVal.set_size((((((i_input_sizes_idx_0 + j_input_sizes_idx_0) + k_input_sizes_idx_0) +
                               l_input_sizes_idx_0) +
                              m_input_sizes_idx_0) +
                             n_input_sizes_idx_0) +
                                o_input_sizes_idx_0,
                            c_result);
        for (int i103{0}; i103 < c_result; i103++) {
            for (int i105{0}; i105 < i_input_sizes_idx_0; i105++) {
                b_BasisVal[i105 + b_BasisVal.size(0) * i103] =
                    BasisVal[i105 + i_input_sizes_idx_0 * i103];
            }
        }
        for (int i104{0}; i104 < c_result; i104++) {
            for (int i107{0}; i107 < j_input_sizes_idx_0; i107++) {
                b_BasisVal[(i107 + i_input_sizes_idx_0) + b_BasisVal.size(0) * i104] =
                    R1[i107 + j_input_sizes_idx_0 * i104];
            }
        }
        for (int i106{0}; i106 < c_result; i106++) {
            for (int i109{0}; i109 < k_input_sizes_idx_0; i109++) {
                b_BasisVal[((i109 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i106] =
                    varargin_3[i109 + k_input_sizes_idx_0 * i106];
            }
        }
        for (int i108{0}; i108 < c_result; i108++) {
            for (int i111{0}; i111 < l_input_sizes_idx_0; i111++) {
                b_BasisVal[(((i111 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                            k_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i108] = R2[i111 + l_input_sizes_idx_0 * i108];
            }
        }
        for (int i110{0}; i110 < c_result; i110++) {
            for (int i113{0}; i113 < m_input_sizes_idx_0; i113++) {
                b_BasisVal[((((i113 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                             k_input_sizes_idx_0) +
                            l_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i110] =
                    varargin_5[i113 + m_input_sizes_idx_0 * i110];
            }
        }
        for (int i112{0}; i112 < c_result; i112++) {
            for (int i115{0}; i115 < n_input_sizes_idx_0; i115++) {
                b_BasisVal[(((((i115 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                              k_input_sizes_idx_0) +
                             l_input_sizes_idx_0) +
                            m_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i112] = R3[i115 + n_input_sizes_idx_0 * i112];
            }
        }
        for (int i114{0}; i114 < c_result; i114++) {
            for (int i116{0}; i116 < o_input_sizes_idx_0; i116++) {
                b_BasisVal[((((((i116 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                               k_input_sizes_idx_0) +
                              l_input_sizes_idx_0) +
                             m_input_sizes_idx_0) +
                            n_input_sizes_idx_0) +
                           b_BasisVal.size(0) * i114] =
                    varargin_7[i116 + o_input_sizes_idx_0 * i114];
            }
        }
        A->parenAssign(b_BasisVal, y, b_y);
        //
        // 'BuildConstr_v4:121' b(k*7*M+1:(k+1)*7*M) = [bC1;
        // 'BuildConstr_v4:122'         bC2;
        // 'BuildConstr_v4:123'         bC2;
        // 'BuildConstr_v4:124'         bC3;
        // 'BuildConstr_v4:125'         bC3;
        // 'BuildConstr_v4:126'         bC4;
        // 'BuildConstr_v4:127'         bC4];
        d4 = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
        if (d4 > b_tmp * static_cast<double>(BasisVal.size(0))) {
            i117 = 0;
        } else {
            i117 = static_cast<int>(d4) - 1;
        }
        unnamed_idx_1 = r1D_sqnorm.size(1);
        bd_loop_ub = r1D_sqnorm.size(1);
        o_scalarLB = (r1D_sqnorm.size(1) / 2) << 1;
        o_vectorUB = o_scalarLB - 2;
        for (i118 = 0; i118 <= o_vectorUB; i118 += 2) {
            __m128d r29;
            r29 = _mm_loadu_pd(&r1D_sqnorm[i118]);
            _mm_storeu_pd(&b[i117 + i118], _mm_div_pd(_mm_set1_pd(b_x), r29));
        }
        for (i118 = o_scalarLB; i118 < bd_loop_ub; i118++) {
            b[i117 + i118] = b_x / r1D_sqnorm[i118];
        }
        for (int i119{0}; i119 < nb_loop_ub; i119++) {
            b[(i117 + i119) + unnamed_idx_1] = bC2[i119];
        }
        for (int i120{0}; i120 < ob_loop_ub; i120++) {
            b[((i117 + i120) + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i120];
        }
        for (int i121{0}; i121 < pb_loop_ub; i121++) {
            b[(((i117 + i121) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i121];
        }
        for (int i122{0}; i122 < qb_loop_ub; i122++) {
            b[((((i117 + i122) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
              d_unnamed_idx_1] = bC3[i122];
        }
        for (int i123{0}; i123 < rb_loop_ub; i123++) {
            b[(((((i117 + i123) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
               d_unnamed_idx_1) +
              e_unnamed_idx_1] = bC4[i123];
        }
        for (int i124{0}; i124 < sb_loop_ub; i124++) {
            b[((((((i117 + i124) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                d_unnamed_idx_1) +
               e_unnamed_idx_1) +
              f_unnamed_idx_1] = bC4[i124];
        }
        //
        // 'BuildConstr_v4:129' Aeq(2*k+1, (k-1)*N+1:k*N) =  (t_1'*r1D(:, end))^2 * BasisVal(end,
        // :);
        cd_loop_ub = BasisVal.size(1);
        d5 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d5 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i125 = 1;
        } else {
            i125 = static_cast<int>(d5);
        }
        u = static_cast<unsigned int>(b_k + 1) << 1;
        b_t_1 = (t_1[0] * r1D[3 * (r1D.size(1) - 1)] + t_1[1] * r1D[3 * (r1D.size(1) - 1) + 1]) +
                t_1[2] * r1D[3 * (r1D.size(1) - 1) + 2];
        p_a = b_t_1 * b_t_1;
        for (int i126{0}; i126 < cd_loop_ub; i126++) {
            Aeq[static_cast<int>(u) + Aeq.size(0) * ((i125 + i126) - 1)] =
                p_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i126) - 1];
        }
        // 'BuildConstr_v4:130' Aeq(2*k+1, k*N+1:(k+1)*N) = -(t_1'*r1Dn(:, 1))^2  * BasisVal(1, :);
        dd_loop_ub = BasisVal.size(1);
        d6 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d6 > ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i127 = 1;
        } else {
            i127 = static_cast<int>(d6);
        }
        c_t_1 = (t_1[0] * r1Dn[0] + t_1[1] * r1Dn[1]) + t_1[2] * r1Dn[2];
        c = c_t_1 * c_t_1;
        for (int i128{0}; i128 < dd_loop_ub; i128++) {
            Aeq[static_cast<int>(u) + Aeq.size(0) * ((i127 + i128) - 1)] =
                -c * BasisVal[BasisVal.size(0) * i128];
        }
        // 'BuildConstr_v4:132' Aeq(2*k+2, (k-1)*N+1:k*N) =   t_1'*[...
        // 'BuildConstr_v4:133'         r2D(1, end)   * BasisVal(end, :)   + 0.5*r1D(1, end)   *
        // BasisValD(end, :); 'BuildConstr_v4:134'         r2D(2, end)   * BasisVal(end, :)   +
        // 0.5*r1D(2, end)   * BasisValD(end, :); 'BuildConstr_v4:135'         r2D(3, end)   *
        // BasisVal(end, :)   + 0.5*r1D(3, end)   * BasisValD(end, :)];
        q_a = r2D[3 * (r2D.size(1) - 1)];
        r_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
        s_a = r2D[3 * (r2D.size(1) - 1) + 1];
        t_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
        u_a = r2D[3 * (r2D.size(1) - 1) + 2];
        v_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
        ed_loop_ub = BasisVal.size(1);
        d7 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d7 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i129 = 0;
        } else {
            i129 = static_cast<int>(d7) - 1;
        }
        if (BasisVal.size(1) == BasisValD.size(1)) {
            int fd_loop_ub;
            g_a.set_size(3, BasisVal.size(1));
            for (int i130{0}; i130 < ed_loop_ub; i130++) {
                double d8;
                double d9;
                d8 = BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i130) - 1];
                d9 = BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i130) - 1];
                g_a[3 * i130] = q_a * d8 + r_a * d9;
                g_a[3 * i130 + 1] = s_a * d8 + t_a * d9;
                g_a[3 * i130 + 2] = u_a * d8 + v_a * d9;
            }
            coder::internal::blas::mtimes(t_1, g_a, r30);
            fd_loop_ub = r30.size(1);
            for (int i131{0}; i131 < fd_loop_ub; i131++) {
                Aeq[(static_cast<int>(u) + Aeq.size(0) * (i129 + i131)) + 1] = r30[i131];
            }
        } else {
            binary_expand_op(Aeq, static_cast<int>(u + 2U), i129, t_1, q_a, BasisVal, r_a,
                             BasisValD, s_a, t_a, u_a, v_a);
        }
        //
        // 'BuildConstr_v4:137' Aeq(2*k+2, k*N+1:(k+1)*N) = -(t_1'*[...
        // 'BuildConstr_v4:138'         r2Dn(1, 1)   * BasisVal(1, :)   + 0.5*r1Dn(1, 1)   *
        // BasisValD(1, :); 'BuildConstr_v4:139'         r2Dn(2, 1)   * BasisVal(1, :)   +
        // 0.5*r1Dn(2, 1)   * BasisValD(1, :); 'BuildConstr_v4:140'         r2Dn(3, 1)   *
        // BasisVal(1, :)   + 0.5*r1Dn(3, 1)   * BasisValD(1, :)]);
        w_a = r2Dn[0];
        x_a = 0.5 * r1Dn[0];
        y_a = r2Dn[1];
        ab_a = 0.5 * r1Dn[1];
        bb_a = r2Dn[2];
        cb_a = 0.5 * r1Dn[2];
        gd_loop_ub = BasisVal.size(1);
        d10 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
        if (d10 >
            ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1))) {
            i132 = 1;
        } else {
            i132 = static_cast<int>(d10);
        }
        if (BasisVal.size(1) == BasisValD.size(1)) {
            g_a.set_size(3, BasisVal.size(1));
            for (int i133{0}; i133 < gd_loop_ub; i133++) {
                double d11;
                double d12;
                d11 = BasisVal[BasisVal.size(0) * i133];
                d12 = BasisValD[BasisValD.size(0) * i133];
                g_a[3 * i133] = w_a * d11 + x_a * d12;
                g_a[3 * i133 + 1] = y_a * d11 + ab_a * d12;
                g_a[3 * i133 + 2] = bb_a * d11 + cb_a * d12;
            }
            coder::internal::blas::mtimes(t_1, g_a, r13);
        } else {
            binary_expand_op(r13, t_1, w_a, BasisVal, x_a, BasisValD, y_a, ab_a, bb_a, cb_a);
        }
        hd_loop_ub = r13.size(1);
        for (int i134{0}; i134 < hd_loop_ub; i134++) {
            Aeq[(static_cast<int>(u) + Aeq.size(0) * ((i132 + i134) - 1)) + 1] = -r13[i134];
        }
        //
        // 'BuildConstr_v4:142' r1D = r1Dn;
        id_loop_ub = r1Dn.size(1);
        r1D.set_size(3, r1Dn.size(1));
        for (int i135{0}; i135 < id_loop_ub; i135++) {
            r1D[3 * i135] = r1Dn[3 * i135];
            r1D[3 * i135 + 1] = r1Dn[3 * i135 + 1];
            r1D[3 * i135 + 2] = r1Dn[3 * i135 + 2];
        }
        // 'BuildConstr_v4:143' r2D = r2Dn;
        jd_loop_ub = r2Dn.size(1);
        r2D.set_size(3, r2Dn.size(1));
        for (int i136{0}; i136 < jd_loop_ub; i136++) {
            r2D[3 * i136] = r2Dn[3 * i136];
            r2D[3 * i136 + 1] = r2Dn[3 * i136 + 1];
            r2D[3 * i136 + 2] = r2Dn[3 * i136 + 2];
        }
    }
    //
    // 'BuildConstr_v4:146' t_1 = r1D(:, end)/norm(r1D(:, end));
    //  unit tangent vector @ end of previous piece
    //
    // 'BuildConstr_v4:148' Aeq(end-1:end, end-N+1:end)   = [BasisVal(end, :);
    // 'BuildConstr_v4:149'     t_1' * [...
    // 'BuildConstr_v4:150'     r2D(1, end) * BasisVal(end, :) + 0.5*r1D(1, end) * BasisValD(end,
    // :); 'BuildConstr_v4:151'     r2D(2, end) * BasisVal(end, :) + 0.5*r1D(2, end) *
    // BasisValD(end, :); 'BuildConstr_v4:152'     r2D(3, end) * BasisVal(end, :) + 0.5*r1D(3, end)
    // * BasisValD(end, :)]];
    h_a = r2D[3 * (r2D.size(1) - 1)];
    i_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
    j_a = r2D[3 * (r2D.size(1) - 1) + 1];
    k_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
    l_a = r2D[3 * (r2D.size(1) - 1) + 2];
    m_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
    d1 = static_cast<double>(Aeq.size(1) - N) + 1.0;
    if (d1 > Aeq.size(1)) {
        i64 = 0;
    } else {
        i64 = static_cast<int>(d1) - 1;
    }
    unnamed_idx_0 = Aeq.size(0) - 2;
    unnamed_idx_1 = Aeq.size(0) - 1;
    if (BasisVal.size(1) == BasisValD.size(1)) {
        __m128d r15;
        double d2;
        int ac_loop_ub;
        int d_r1D;
        int e_r1D;
        int xb_loop_ub;
        int yb_loop_ub;
        d_r1D = r1D.size(1);
        e_r1D = r1D.size(1);
        d2 = coder::b_norm(*(double(*)[3]) & r1D[3 * (e_r1D - 1)]);
        r15 = _mm_loadu_pd(&r1D[3 * (d_r1D - 1)]);
        _mm_storeu_pd(&c_r1D[0], _mm_div_pd(r15, _mm_set1_pd(d2)));
        c_r1D[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d2;
        xb_loop_ub = BasisVal.size(1);
        yb_loop_ub = BasisVal.size(1);
        ac_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i68{0}; i68 < xb_loop_ub; i68++) {
            g_a[3 * i68] = h_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i68) - 1] +
                           i_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i68) - 1];
        }
        for (int i69{0}; i69 < yb_loop_ub; i69++) {
            g_a[3 * i69 + 1] = j_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i69) - 1] +
                               k_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i69) - 1];
        }
        for (int i70{0}; i70 < ac_loop_ub; i70++) {
            g_a[3 * i70 + 2] = l_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i70) - 1] +
                               m_a * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i70) - 1];
        }
        coder::internal::blas::mtimes(c_r1D, g_a, r13);
    } else {
        binary_expand_op(r13, r1D, h_a, BasisVal, i_a, BasisValD, j_a, k_a, l_a, m_a);
    }
    ub_loop_ub = BasisVal.size(1);
    for (int i65{0}; i65 < ub_loop_ub; i65++) {
        Aeq[unnamed_idx_0 + Aeq.size(0) * (i64 + i65)] =
            BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i65) - 1];
    }
    vb_loop_ub = r13.size(1);
    for (int i66{0}; i66 < vb_loop_ub; i66++) {
        Aeq[unnamed_idx_1 + Aeq.size(0) * (i64 + i66)] = r13[i66];
    }
    int b_beq;
    //
    // 'BuildConstr_v4:154' beq(end-1:end) = [(v_1^2)/r1Dn_sqnorm(end);
    // 'BuildConstr_v4:155'     at_1];
    b_beq = beq.size(0) - 1;
    beq[beq.size(0) - 2] = v_1 * v_1 / r1D_sqnorm[r1D_sqnorm.size(1) - 1];
    beq[b_beq] = at_1;
    // 'BuildConstr_v4:157' c_prof_out(mfilename);
    //  Add a ramp on the acceleration and speed limits
    // 'BuildConstr_v4:161' vel_ramp = linspace(1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M)';
    coder::b_linspace(ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS, static_cast<double>(M), r13);
    vel_ramp.set_size(r13.size(1));
    bc_loop_ub = r13.size(1);
    for (int i71{0}; i71 < bc_loop_ub; i71++) {
        vel_ramp[i71] = r13[i71];
    }
    // 'BuildConstr_v4:162' acc_ramp = repmat(linspace(1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS,
    // M)',1,6);
    coder::b_linspace(ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, static_cast<double>(M), r13);
    r17.set_size(r13.size(1));
    dc_loop_ub = r13.size(1);
    for (int i72{0}; i72 < dc_loop_ub; i72++) {
        r17[i72] = r13[i72];
    }
    acc_ramp.set_size(r17.size(0), 6);
    if (r17.size(0) != 0) {
        int na;
        na = r17.size(0);
        for (int t{0}; t < 6; t++) {
            for (int d_k{0}; d_k < na; d_k++) {
                acc_ramp[d_k + acc_ramp.size(0) * t] = r17[d_k];
            }
        }
    }
    // 'BuildConstr_v4:164' if( Ncrv > 1 )
    if (CurvStructs.size(1) > 1) {
        int b_result;
        int d_input_sizes_idx_1;
        int nc_loop_ub;
        int oc_loop_ub;
        int result_idx_1_tmp;
        signed char b_input_sizes_idx_1;
        signed char c_input_sizes_idx_1;
        signed char input_sizes_idx_1;
        bool b_empty_non_axis_sizes;
        // 'BuildConstr_v4:165' ramp = [ones(M, 7), vel_ramp, acc_ramp, ...
        // 'BuildConstr_v4:166'             repmat([vel_ramp(end), acc_ramp(end,:)], M, Ncrv-2)];
        b_vel_ramp[0] = vel_ramp[vel_ramp.size(0) - 1];
        for (int i75{0}; i75 < 6; i75++) {
            b_vel_ramp[i75 + 1] = acc_ramp[(acc_ramp.size(0) + acc_ramp.size(0) * i75) - 1];
        }
        coder::repmat(b_vel_ramp, static_cast<double>(M),
                      static_cast<double>(CurvStructs.size(1)) - 2.0, varargin_4);
        if (M != 0) {
            b_result = M;
        } else if (vel_ramp.size(0) != 0) {
            b_result = vel_ramp.size(0);
        } else if (acc_ramp.size(0) != 0) {
            b_result = acc_ramp.size(0);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            b_result = varargin_4.size(0);
        } else {
            b_result = 0;
            if (varargin_4.size(0) > 0) {
                b_result = varargin_4.size(0);
            }
        }
        b_empty_non_axis_sizes = (b_result == 0);
        if (b_empty_non_axis_sizes || (M != 0)) {
            input_sizes_idx_1 = 7;
        } else {
            input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || (vel_ramp.size(0) != 0)) {
            b_input_sizes_idx_1 = 1;
        } else {
            b_input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || (acc_ramp.size(0) != 0)) {
            c_input_sizes_idx_1 = 6;
        } else {
            c_input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            d_input_sizes_idx_1 = varargin_4.size(1);
        } else {
            d_input_sizes_idx_1 = 0;
        }
        result_idx_1_tmp = input_sizes_idx_1;
        ramp.set_size(b_result, ((input_sizes_idx_1 + b_input_sizes_idx_1) + c_input_sizes_idx_1) +
                                    d_input_sizes_idx_1);
        for (int i83{0}; i83 < result_idx_1_tmp; i83++) {
            for (int i84{0}; i84 < b_result; i84++) {
                ramp[i84 + ramp.size(0) * i83] = 1.0;
            }
        }
        nc_loop_ub = b_input_sizes_idx_1;
        for (int i86{0}; i86 < nc_loop_ub; i86++) {
            for (int i87{0}; i87 < b_result; i87++) {
                ramp[i87 + ramp.size(0) * input_sizes_idx_1] = vel_ramp[i87];
            }
        }
        oc_loop_ub = c_input_sizes_idx_1;
        for (int i88{0}; i88 < oc_loop_ub; i88++) {
            for (int i90{0}; i90 < b_result; i90++) {
                ramp[i90 + ramp.size(0) * ((i88 + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                    acc_ramp[i90 + acc_ramp.size(0) * i88];
            }
        }
        for (int i89{0}; i89 < d_input_sizes_idx_1; i89++) {
            for (int i92{0}; i92 < b_result; i92++) {
                ramp[i92 + ramp.size(0) * (((i89 + input_sizes_idx_1) + b_input_sizes_idx_1) +
                                           c_input_sizes_idx_1)] = varargin_4[i92 + b_result * i89];
            }
        }
        // 'BuildConstr_v4:167' b  = b .* ramp(:);
        if (b.size(0) == ramp.size(0) * ramp.size(1)) {
            int i94;
            int k_scalarLB;
            int k_vectorUB;
            int rc_loop_ub;
            rc_loop_ub = b.size(0);
            k_scalarLB = (b.size(0) / 2) << 1;
            k_vectorUB = k_scalarLB - 2;
            for (i94 = 0; i94 <= k_vectorUB; i94 += 2) {
                __m128d r24;
                __m128d r25;
                r24 = _mm_loadu_pd(&b[i94]);
                r25 = _mm_loadu_pd(&ramp[i94]);
                _mm_storeu_pd(&b[i94], _mm_mul_pd(r24, r25));
            }
            for (i94 = k_scalarLB; i94 < rc_loop_ub; i94++) {
                b[i94] = b[i94] * ramp[i94];
            }
        } else {
            binary_expand_op(b, ramp);
        }
    }
    //  if( isempty( ctx.at_1 ) )
    //      Aeq = Aeq(1 : end -1, : );
    //      beq = beq( 1 : end -1 );
    //  end
}

} // namespace ocn

//
// File trailer for BuildConstr_v4.cpp
//
// [EOF]
//
