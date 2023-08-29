//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:52:02
//

// Include Files
#include "compressCurvStructs.h"
#include "CalcBspline_Lee.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "SplineLengthApproxGL_tot.h"
#include "bspline_eval.h"
#include "constrCurvStruct.h"
#include "constrSplineStruct.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void create_spline(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
                          int ctx_cfg_NumberAxis, int ctx_cfg_LeeSplineDegree,
                          double ctx_cfg_GaussLegendreN, const double ctx_cfg_GaussLegendreX[5],
                          const double ctx_cfg_GaussLegendreW[5],
                          const ::coder::array<double, 2U> &batch_pvec,
                          const CurvStruct batch_curvArray[2], unsigned int *spline_index,
                          CurvStruct *curv, CurvStruct *spline);

}

// Function Definitions
//
// function [ curv, spline, spline_index ] = create_spline( ctx, batch, spline_index )
//
// Arguments    : const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_LeeSplineDegree
//                double ctx_cfg_GaussLegendreN
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const ::coder::array<double, 2U> &batch_pvec
//                const CurvStruct batch_curvArray[2]
//                unsigned int *spline_index
//                CurvStruct *curv
//                CurvStruct *spline
// Return Type  : void
//
namespace ocn {
static void create_spline(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
                          int ctx_cfg_NumberAxis, int ctx_cfg_LeeSplineDegree,
                          double ctx_cfg_GaussLegendreN, const double ctx_cfg_GaussLegendreX[5],
                          const double ctx_cfg_GaussLegendreW[5],
                          const ::coder::array<double, 2U> &batch_pvec,
                          const CurvStruct batch_curvArray[2], unsigned int *spline_index,
                          CurvStruct *curv, CurvStruct *spline)
{
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> b_batch_pvec;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1Dnorm;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    Axes params_tool_offset;
    SplineStruct params_spline;
    double dv[6];
    double dv1[6];
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double b[5];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d;
    double d1;
    double d2;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    int csz_idx_1_tmp;
    int d_loop_ub;
    int e_loop_ub;
    int end;
    int i15;
    int i16;
    int i17;
    int i2;
    int i21;
    int i26;
    int i3;
    int i4;
    int i5;
    int i6;
    int i7;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int partialTrueCount;
    int trueCount;
    int unnamed_idx_1;
    signed char tmp_data[6];
    bool b_b;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs:158' spline            = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                      &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                      &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                      &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                      &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                      &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                      &params_tool_backangle, &params_tool_orientation, &params_spline, params_R0,
                      params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp, &c_expl_temp,
                      params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                       params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                       params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                       params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                       params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                       &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                       params_tool_backangle, params_tool_orientation, &params_spline, params_R0,
                       params_R1, params_Cprim, params_evec, params_CoeffP5, spline);
    // 'compressCurvStructs:159' spline.Info.Type  = CurveType.Spline;
    spline->Info.Type = CurveType_Spline;
    // 'compressCurvStructs:160' spline.sp_index   = spline_index;
    spline->sp_index = *spline_index;
    // 'compressCurvStructs:161' spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec(
    // ctx.cfg.maskTot, : ) );
    end = ctx_cfg_maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int i{0}; i <= end; i++) {
        if (ctx_cfg_maskTot_data[i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
            partialTrueCount++;
        }
    }
    loop_ub = batch_pvec.size(1);
    b_batch_pvec.set_size(trueCount, batch_pvec.size(1));
    for (int b_i{0}; b_i < loop_ub; b_i++) {
        for (int i1{0}; i1 < trueCount; i1++) {
            b_batch_pvec[i1 + b_batch_pvec.size(0) * b_i] =
                batch_pvec[(tmp_data[i1] + 6 * b_i) - 1];
        }
    }
    CalcBspline_Lee(ctx_cfg_NumberAxis, ctx_cfg_LeeSplineDegree, b_batch_pvec,
                    &spline->sp.Bl.ncoeff, spline->sp.Bl.breakpoints, &spline->sp.Bl.handle,
                    &spline->sp.Bl.order, spline->sp.coeff, spline->sp.knots, &spline->sp.Ltot,
                    spline->sp.Lk);
    // 'compressCurvStructs:162' [ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx.cfg, spline );
    //  Precomputes approximately the total arc length L as well as the individual
    //  arc lengths between knot points of a parametric spline.
    //  The computation is based on numerical Gauss Legendre integration.
    //  SplineLengthApproxGL_tot should only be called once since the result
    //  of the computation is stored and reused later.
    //  get the sp structure
    //  Spline = ctx.q_spline.get(Curv.sp_index);
    //  sp     = Spline.sp;
    // 'SplineLengthApproxGL_tot:11' sp     = Curv.sp;
    // 'SplineLengthApproxGL_tot:12' Knots  = sp.knots(4:end-3);
    if (spline->sp.knots.size(1) - 3 < 4) {
        i2 = 0;
        i3 = -1;
    } else {
        i2 = 3;
        i3 = spline->sp.knots.size(1) - 4;
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
    i4 = i3 - i2;
    if (i4 < 1) {
        i5 = 0;
    } else {
        i5 = i3 - i2;
    }
    //  lower integration limits
    // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
    if (i4 + 1 < 2) {
        i6 = -1;
        i7 = -1;
    } else {
        i6 = 0;
        i7 = i4;
    }
    //  upper integration limits
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApproxGL_tot:16' GL_N   = cfg.GaussLegendreN;
    // 'SplineLengthApproxGL_tot:17' GL_X   = cfg.GaussLegendreX;
    // 'SplineLengthApproxGL_tot:18' GL_W   = cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [a, b]
    // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b,
    // (1+GL_X)))/2;
    for (int c_i{0}; c_i < 5; c_i++) {
        b[c_i] = 1.0 - ctx_cfg_GaussLegendreX[c_i];
    }
    c.set_size(5, i5);
    if (i5 != 0) {
        int acoef;
        int i8;
        acoef = (i5 != 1);
        i8 = i5 - 1;
        for (int k{0}; k <= i8; k++) {
            int varargin_2;
            varargin_2 = acoef * k;
            for (int b_k{0}; b_k < 5; b_k++) {
                c[b_k + 5 * k] = spline->sp.knots[i2 + varargin_2] * b[b_k];
            }
        }
    }
    for (int d_i{0}; d_i < 5; d_i++) {
        b[d_i] = ctx_cfg_GaussLegendreX[d_i] + 1.0;
    }
    csz_idx_1_tmp = i7 - i6;
    b_c.set_size(5, csz_idx_1_tmp);
    if (csz_idx_1_tmp != 0) {
        int b_acoef;
        int i9;
        b_acoef = (csz_idx_1_tmp != 1);
        i9 = csz_idx_1_tmp - 1;
        for (int c_k{0}; c_k <= i9; c_k++) {
            int i11;
            i11 = (i6 + b_acoef * c_k) + 1;
            for (int d_k{0}; d_k < 5; d_k++) {
                b_c[d_k + 5 * c_k] = spline->sp.knots[i2 + i11] * b[d_k];
            }
        }
    }
    if (c.size(1) == b_c.size(1)) {
        int b_loop_ub;
        Umat.set_size(5, c.size(1));
        b_loop_ub = c.size(1);
        for (int i10{0}; i10 < b_loop_ub; i10++) {
            for (int i12{0}; i12 < 5; i12++) {
                Umat[i12 + 5 * i10] = (c[i12 + 5 * i10] + b_c[i12 + 5 * i10]) / 2.0;
            }
        }
    } else {
        c_binary_expand_op(Umat, c, b_c);
    }
    // 'SplineLengthApproxGL_tot:21' Uvec   = Umat(:)';
    //  all evaluation points as row vector
    // 'SplineLengthApproxGL_tot:23' [~, r1D]  = EvalBSpline(Curv, Uvec);
    //  EvalBSpline
    //
    //  INPUT
    //  spline        : struct : Spline structure
    //  u_vec         :    1xn : Vector for evaluation of the curv
    //
    //  OUTPUT
    //  r0D           :   nDxn : The evaluated B spline at u\_vec points
    //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec points
    //  r2D           :   nDxn : 2nd order parametric derivative for the B spline at u\_vec points
    //  r3D           :   nDxn : 3rd order parametric derivative for the B spline at u\_vec points
    // 'EvalBSpline:14' sp = spline.sp;
    // 'EvalBSpline:15' N  = length( u_vec );
    // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
    // 'EvalBSpline:18' r0D = zeros( M, N );
    unnamed_idx_1 = 5 * Umat.size(1);
    // 'EvalBSpline:18' r1D = r0D;
    r1D.set_size(spline->sp.coeff.size(0), unnamed_idx_1);
    for (int i13{0}; i13 < unnamed_idx_1; i13++) {
        int c_loop_ub;
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i14{0}; i14 < c_loop_ub; i14++) {
            r1D[i14 + r1D.size(0) * i13] = 0.0;
        }
    }
    // 'EvalBSpline:18' r2D = r1D;
    // 'EvalBSpline:18' r3D = r2D;
    // 'EvalBSpline:20' for j = 1 : M
    i15 = spline->sp.coeff.size(0);
    if (spline->sp.coeff.size(0) - 1 >= 0) {
        i16 = 5 * Umat.size(1);
        if (i16 - 1 >= 0) {
            i17 = spline->sp.coeff.size(1);
            d_loop_ub = spline->sp.coeff.size(1);
        }
    }
    for (int j{0}; j < i15; j++) {
        unsigned int b_unnamed_idx_1;
        int f_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        int j_loop_ub;
        int l_loop_ub;
        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
        // u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r1.set_size(1, static_cast<int>(b_unnamed_idx_1));
        f_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i19{0}; i19 < f_loop_ub; i19++) {
            r1[i19] = 0.0;
        }
        // 'bspline_eval_vec:4' xd      = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r2.set_size(1, static_cast<int>(b_unnamed_idx_1));
        h_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i22{0}; i22 < h_loop_ub; i22++) {
            r2[i22] = 0.0;
        }
        // 'bspline_eval_vec:5' xdd     = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r3.set_size(1, static_cast<int>(b_unnamed_idx_1));
        i_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i23{0}; i23 < i_loop_ub; i23++) {
            r3[i23] = 0.0;
        }
        // 'bspline_eval_vec:6' xddd    = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r4.set_size(1, static_cast<int>(b_unnamed_idx_1));
        j_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i27{0}; i27 < j_loop_ub; i27++) {
            r4[i27] = 0.0;
        }
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int i_k{0}; i_k < i16; i_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r1[i_k] = Umat[i_k];
            b_spline.set_size(1, i17);
            for (int i30{0}; i30 < d_loop_ub; i30++) {
                b_spline[i30] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i30];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r1[i_k], &d, &d1, &d2);
            r4[i_k] = d2;
            r3[i_k] = d1;
            r2[i_k] = d;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        l_loop_ub = r2.size(1);
        for (int i29{0}; i29 < l_loop_ub; i29++) {
            r1D[j + r1D.size(0) * i29] = r2[i29];
        }
    }
    // 'SplineLengthApproxGL_tot:24' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    r.set_size(r1D.size(0), r1D.size(1));
    e_loop_ub = r1D.size(1);
    for (int i18{0}; i18 < e_loop_ub; i18++) {
        int g_loop_ub;
        g_loop_ub = r1D.size(0);
        for (int i20{0}; i20 < g_loop_ub; i20++) {
            double varargin_1;
            varargin_1 = r1D[i20 + r1D.size(0) * i18];
            r[i20 + r.size(0) * i18] = std::pow(varargin_1, 2.0);
        }
    }
    coder::sum(r, r1Dnorm);
    // 'mysqrt:3' y = sqrt(x);
    i21 = r1Dnorm.size(1);
    for (int e_k{0}; e_k < i21; e_k++) {
        r1Dnorm[e_k] = std::sqrt(r1Dnorm[e_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApproxGL_tot:25' r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1);
    // 'SplineLengthApproxGL_tot:26' Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
    c.set_size(5, i4);
    if (i4 != 0) {
        int b_bcoef;
        int bcoef;
        int i24;
        bcoef = (i4 != 1);
        i24 = i4 - 1;
        b_bcoef = (static_cast<int>(ctx_cfg_GaussLegendreN) != 1);
        for (int f_k{0}; f_k <= i24; f_k++) {
            int varargin_3;
            varargin_3 = bcoef * f_k;
            for (int h_k{0}; h_k < 5; h_k++) {
                c[h_k + 5 * f_k] =
                    ctx_cfg_GaussLegendreW[h_k] *
                    r1Dnorm[b_bcoef * h_k + static_cast<int>(ctx_cfg_GaussLegendreN) * varargin_3];
            }
        }
    }
    if (c.size(1) == 0) {
        r1.set_size(1, 0);
    } else {
        int i25;
        r1.set_size(1, c.size(1));
        i25 = c.size(1);
        for (int g_k{0}; g_k < i25; g_k++) {
            r1[g_k] = c[5 * g_k];
            r1[g_k] = r1[g_k] + c[5 * g_k + 1];
            r1[g_k] = r1[g_k] + c[5 * g_k + 2];
            r1[g_k] = r1[g_k] + c[5 * g_k + 3];
            r1[g_k] = r1[g_k] + c[5 * g_k + 4];
        }
    }
    if (i7 - i6 == 1) {
        i26 = i5;
    } else {
        i26 = i7 - i6;
    }
    if ((csz_idx_1_tmp == i5) && (r1.size(1) == i26)) {
        int k_loop_ub;
        spline->sp.Lk.set_size(1, r1.size(1));
        k_loop_ub = r1.size(1);
        for (int i28{0}; i28 < k_loop_ub; i28++) {
            spline->sp.Lk[i28] =
                r1[i28] * (spline->sp.knots[((i2 + i6) + i28) + 1] - spline->sp.knots[i2 + i28]) /
                2.0;
        }
    } else {
        binary_expand_op(spline, r1, i2, i6 + 1, i7, i5 - 1);
    }
    //  Gauss Legendre integration
    // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
    spline->sp.Ltot = coder::sum(spline->sp.Lk);
    // 'compressCurvStructs:163' spline.sp.Ltot    = Ltot;
    // 'compressCurvStructs:164' spline.sp.Lk      = Lk;
    // 'compressCurvStructs:166' curv    = constrSplineStruct( batch.curvArray( end ).Info, ...
    // 'compressCurvStructs:167'                               batch.curvArray( end ).Tool, ...
    // 'compressCurvStructs:168'                               batch.pvec( :, 1 ), ...
    // 'compressCurvStructs:169'                               batch.pvec( :,end ), uint32(
    // spline_index ) );
    for (int i31{0}; i31 < 6; i31++) {
        dv[i31] = (*(double(*)[6]) & batch_pvec[0])[i31];
    }
    for (int i32{0}; i32 < 6; i32++) {
        dv1[i32] = (*(double(*)[6]) & batch_pvec[6 * (batch_pvec.size(1) - 1)])[i32];
    }
    constrSplineStruct(batch_curvArray[1].Info.zspdmode, batch_curvArray[1].Info.TRAFO,
                       batch_curvArray[1].Info.HSC, batch_curvArray[1].Info.FeedRate,
                       batch_curvArray[1].Info.SpindleSpeed,
                       batch_curvArray[1].Info.gcode_source_line, batch_curvArray[1].Info.G91,
                       batch_curvArray[1].Info.G91_1, batch_curvArray[1].b_Tool.toolno,
                       batch_curvArray[1].b_Tool.pocketno, &batch_curvArray[1].b_Tool.offset,
                       batch_curvArray[1].b_Tool.diameter, batch_curvArray[1].b_Tool.frontangle,
                       batch_curvArray[1].b_Tool.backangle, batch_curvArray[1].b_Tool.orientation,
                       dv, dv1, *spline_index, curv);
    //  Calculate the ZSpdMode for the spline
    // 'compressCurvStructs:172' first   = batch.curvArray( 1 );
    // 'compressCurvStructs:173' last    = batch.curvArray( end );
    // 'compressCurvStructs:175' if ( ~isAZeroSpeed( first ) ) && ( ~isAZeroSpeed( last ) )
    //  isAZeroSpeed : Return true if the curv is has a zero speed
    //  Input :
    //  curv  : The curve struct
    // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
    b_b = (batch_curvArray[0].Info.zspdmode != ZSpdMode_NN);
    if ((!b_b) && (batch_curvArray[1].Info.zspdmode == ZSpdMode_NN)) {
        //  isAZeroSpeed : Return true if the curv is has a zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
        // 'compressCurvStructs:176' curv.Info.zspdmode = ZSpdMode.NN;
        curv->Info.zspdmode = ZSpdMode_NN;
    } else if ((!b_b) && ((batch_curvArray[1].Info.zspdmode == ZSpdMode_NZ) ||
                          (batch_curvArray[1].Info.zspdmode == ZSpdMode_ZZ))) {
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        // 'isAZeroEnd:7' zeroFlag = true;
        // 'compressCurvStructs:177' elseif ( ~isAZeroSpeed( first ) ) && ( isAZeroEnd( last ) )
        // 'compressCurvStructs:178' curv.Info.zspdmode = ZSpdMode.NZ;
        curv->Info.zspdmode = ZSpdMode_NZ;

        // 'isAZeroEnd:9' zeroFlag = false;
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
    } else if (((batch_curvArray[0].Info.zspdmode == ZSpdMode_ZN) ||
                (batch_curvArray[0].Info.zspdmode == ZSpdMode_ZZ)) &&
               (batch_curvArray[1].Info.zspdmode == ZSpdMode_NN)) {
        // 'isAZeroStart:6' zeroFlag = true;
        //  isAZeroSpeed : Return true if the curv is has a zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
        // 'compressCurvStructs:179' elseif ( isAZeroStart( first ) ) && ( ~isAZeroSpeed( last ) )
        // 'compressCurvStructs:180' curv.Info.zspdmode = ZSpdMode.ZN;
        curv->Info.zspdmode = ZSpdMode_ZN;
    } else {
        // 'isAZeroStart:8' zeroFlag = false;
        // 'compressCurvStructs:181' else
        // 'compressCurvStructs:182' curv.Info.zspdmode = ZSpdMode.ZZ;
        curv->Info.zspdmode = ZSpdMode_ZZ;
    }
    // 'compressCurvStructs:185' spline_index = spline_index + 1;
    (*spline_index)++;
}

//
// function [ ctx ] = compressCurvStructs( ctx )
//
// CompressCurvStructs :
//  - Is feeded by the queue : q_gcode
//  - Check if a compression is possible based on the individual curves
//  length, the cummulative length and the collinearity of two consecutive
//  segment.
//  - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves
//  accordingly.
//  - Create a Bspline based on Lee89.
//  - Fill the queue : q_compress
//
//  Note : If compression is not required call ExpandZeroStructs
//
// Arguments    : const b_FeedoptContext *ctx
// Return Type  : void
//
void compressCurvStructs(const b_FeedoptContext *ctx)
{
    ::coder::array<double, 2U> batch_pvec;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    Axes params_tool_offset;
    CurvStruct batch_curvArray[2];
    CurvStruct C;
    CurvStruct curv;
    CurvStruct curvCompressed;
    CurvStruct prevCurv;
    CurvStruct spline;
    SplineStruct params_spline;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    unsigned int b_spline_index;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    unsigned int spline_index;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs:14' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double batch_size;
        unsigned int Ncrv;
        int i1;
        // 'compressCurvStructs:16' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs:17' Ncrv                = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        // 'compressCurvStructs:18' [ batch ]           = batch_init();
        // 'compressCurvStructs:114' batch = struct( ...
        // 'compressCurvStructs:115'     'pvec',          zeros( StructTypeName.NumberAxisMax, 1
        // ),... 'compressCurvStructs:116'     'curvArray',     repmat( constrCurvStructType, 1, 2
        // ),... 'compressCurvStructs:117'     'spindle_speed', 0,... 'compressCurvStructs:118'
        // 'feedrate',      0,... 'compressCurvStructs:119'     'size',          0 ...
        // 'compressCurvStructs:120'     );
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                          &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                          &params_tool_backangle, &params_tool_orientation, &params_spline,
                          params_R0, params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp,
                          &c_expl_temp, params_CoeffP5, &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
        // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
        // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch,
        // ... 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                           &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                           params_tool_backangle, params_tool_orientation, &params_spline,
                           params_R0, params_R1, params_Cprim, params_evec, params_CoeffP5, &C);
        batch_pvec.set_size(6, 1);
        for (int i{0}; i < 6; i++) {
            batch_pvec[i] = 0.0;
        }
        batch_curvArray[0] = C;
        batch_curvArray[1] = C;
        batch_size = 0.0;
        // 'compressCurvStructs:122' if( ~coder.target( "MATLAB" ) )
        // 'compressCurvStructs:123' coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
        // 'compressCurvStructs:20' DebugLog(DebugCfg.Validate, 'Compressing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'compressCurvStructs:22' if( coder.target( "MATLAB" ) )
        // 'compressCurvStructs:26' for k = 1 : Ncrv
        i1 = static_cast<int>(Ncrv);
        for (int k{0}; k < i1; k++) {
            double b_curv[2][6];
            bool addBatch;
            bool addNewBatch;
            bool closeBatch;
            // 'compressCurvStructs:27' curv = ctx.q_gcode.get( k );
            ctx->q_gcode.get(k + 1U, &curv);
            //  Get next Curve in the queue
            // 'compressCurvStructs:29' [ addBatch, addNewBatch ] = check_add_batch( ctx, curv,
            // batch );
            // -------------------------------------------------------------------------%
            // 'compressCurvStructs:60' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:62' addBatch    = true;
            addBatch = true;
            // 'compressCurvStructs:63' addNewBatch = false;
            addNewBatch = false;
            // 'compressCurvStructs:65' if( curv.Info.Type ~= CurveType.Line )
            if (curv.Info.Type != CurveType_Line) {
                // 'compressCurvStructs:66' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:69' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs:72' if( LengthCurv( ctx, curv, 0, 1 ) >
                // ctx.cfg.LThresholdMax )
            } else if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                  ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  &curv) > ctx->cfg.LThresholdMax) {
                // 'compressCurvStructs:73' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:76' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs:79' if( LengthCurv( ctx, curv, 0, 1 ) <
                // ctx.cfg.LThresholdMin )
            } else if ((LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                   &curv) >= ctx->cfg.LThresholdMin) &&
                       (batch_size > 0.0)) {
                bool collinear;
                // 'compressCurvStructs:83' if( batch.size > 0 )
                // 'compressCurvStructs:84' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    // 'compressCurvStructs:85' prevCurv = batch.curvArray( end );
                    prevCurv = batch_curvArray[1];
                } else {
                    // 'compressCurvStructs:86' else
                    // 'compressCurvStructs:87' prevCurv = batch.curvArray( 1 );
                    prevCurv = batch_curvArray[0];
                }
                // 'compressCurvStructs:89' collinear = curvCollinear( ctx, prevCurv, curv, ...
                // 'compressCurvStructs:90'         ctx.cfg.Compressing.ColTolCosLee );
                // 'curvCollinear:3' [~, V0] = EvalCurvStruct(ctx, Curv1, 1);
                b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &prevCurv, a__1, V0);
                // 'curvCollinear:4' [~, V1] = EvalCurvStruct(ctx, Curv2, 0);
                c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curv, a__2, V1);
                // 'curvCollinear:6' result = collinear(V0, V1, ToleranceCos);
                // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
                if ((coder::b_norm(V0) < 2.2204460492503131E-16) ||
                    (coder::b_norm(V1) < 2.2204460492503131E-16)) {
                    // 'collinear:3' value = true;
                    collinear = true;
                } else {
                    double c;
                    int b_loop_ub;
                    int loop_ub;
                    // 'collinear:6' cos_angle = dot(u,v)/(MyNorm(u)*MyNorm(v));
                    // 'MyNorm:2' coder.inline('always');
                    // 'MyNorm:3' n = mysqrt(sum(x.^2));
                    // 'mysqrt:3' y = sqrt(x);
                    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                    sqrt_calls++;
                    // 'MyNorm:2' coder.inline('always');
                    // 'MyNorm:3' n = mysqrt(sum(x.^2));
                    // 'mysqrt:3' y = sqrt(x);
                    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                    sqrt_calls++;
                    // 'collinear:7' value = cos_angle >= tol_cos;
                    c = 0.0;
                    if (V0.size(0) >= 1) {
                        int ixlast;
                        ixlast = V0.size(0);
                        for (int b_k{0}; b_k < ixlast; b_k++) {
                            c += V0[b_k] * V1[b_k];
                        }
                    }
                    r.set_size(V0.size(0));
                    loop_ub = V0.size(0);
                    for (int i10{0}; i10 < loop_ub; i10++) {
                        double varargin_1;
                        varargin_1 = V0[i10];
                        r[i10] = std::pow(varargin_1, 2.0);
                    }
                    r1.set_size(V1.size(0));
                    b_loop_ub = V1.size(0);
                    for (int i11{0}; i11 < b_loop_ub; i11++) {
                        double b_varargin_1;
                        b_varargin_1 = V1[i11];
                        r1[i11] = std::pow(b_varargin_1, 2.0);
                    }
                    collinear = (c / (std::sqrt(coder::sum(r)) * std::sqrt(coder::sum(r1))) >=
                                 ctx->cfg.Compressing.ColTolCosLee);
                }
                // 'compressCurvStructs:91' if( ~collinear )
                if (!collinear) {
                    // 'compressCurvStructs:92' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:95' addBatch = false;
                    addBatch = false;
                    // 'compressCurvStructs:96' addNewBatch = true;
                    addNewBatch = true;
                }
            } else {
                // 'compressCurvStructs:80' addBatch = true;
            }
            // 'compressCurvStructs:30' [ closeBatch ] = check_close_batch( curv, addBatch );
            // 'compressCurvStructs:103' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:105' closeBatch = false;
            closeBatch = false;
            // 'compressCurvStructs:107' if( ~addBatch )
            if (!addBatch) {
                // 'compressCurvStructs:107' closeBatch = true;
                closeBatch = true;

                // 'compressCurvStructs:109' if( isAZeroEnd( curv ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            } else if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'compressCurvStructs:109' closeBatch = true;
                closeBatch = true;
            } else {
                // 'isAZeroEnd:9' zeroFlag = false;
            }
            // 'compressCurvStructs:32' if( addBatch )
            if (addBatch) {
                // 'compressCurvStructs:33' if( batch.size > 0)
                if (batch_size > 0.0) {
                    int i2;
                    // 'compressCurvStructs:34' [ batch ] = batch_add_curv( batch, curv );
                    // 'compressCurvStructs:150' batch.pvec             = [ batch.pvec, curv.R1 ];
                    i2 = batch_pvec.size(1);
                    batch_pvec.set_size(6, batch_pvec.size(1) + 1);
                    for (int i3{0}; i3 < 6; i3++) {
                        batch_pvec[i3 + 6 * i2] = curv.R1[i3];
                    }
                    // 'compressCurvStructs:151' batch.curvArray( end ) = curv;
                    batch_curvArray[1] = curv;
                    // 'compressCurvStructs:152' batch.spindle_speed    = min( batch.spindle_speed ,
                    // curv.Info.SpindleSpeed ); 'compressCurvStructs:153' batch.feedrate         =
                    // min( batch.feedrate, curv.Info.FeedRate ); 'compressCurvStructs:154'
                    // batch.size             = batch.size + 1;
                    batch_size++;
                } else {
                    // 'compressCurvStructs:35' else
                    // 'compressCurvStructs:36' [ batch ] = batch_reset( ctx, curv );
                    // 'compressCurvStructs:142' batch.pvec            = [curv.R0, curv.R1 ];
                    // 'compressCurvStructs:143' batch.curvArray       = [ curv, curv ];
                    // 'compressCurvStructs:144' batch.spindle_speed   = ctx.cfg.smax;
                    // 'compressCurvStructs:145' batch.feedrate        = ctx.cfg.fmax;
                    // 'compressCurvStructs:146' batch.size            = 1;
                    for (int i4{0}; i4 < 6; i4++) {
                        b_curv[0][i4] = curv.R0[i4];
                        b_curv[1][i4] = curv.R1[i4];
                    }
                    batch_pvec.set_size(6, 2);
                    for (int i6{0}; i6 < 2; i6++) {
                        for (int i7{0}; i7 < 6; i7++) {
                            batch_pvec[i7 + 6 * i6] = b_curv[i6][i7];
                        }
                    }
                    batch_curvArray[0] = curv;
                    batch_curvArray[1] = curv;
                    batch_size = 1.0;
                }
            }
            // 'compressCurvStructs:40' if( closeBatch )
            if (closeBatch) {
                // 'compressCurvStructs:41' [ ctx, batch, spline_index ] = batch_close( ctx, batch,
                // spline_index ); 'compressCurvStructs:128' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    // 'compressCurvStructs:129' [ curvCompressed, spline, spline_index ] = ...
                    // 'compressCurvStructs:130'         create_spline( ctx, batch, spline_index );
                    create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                                  ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                                  ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                                  batch_curvArray, &spline_index, &curvCompressed, &spline);
                    // 'compressCurvStructs:132' ctx.q_compress.push( curvCompressed );
                    ctx->q_compress.push(&curvCompressed);
                    // 'compressCurvStructs:133' ctx.q_spline.push( spline );
                    ctx->q_spline.push(&spline);
                } else if (batch_size > 0.0) {
                    // 'compressCurvStructs:135' elseif( batch.size > 0 )
                    // 'compressCurvStructs:136' ctx.q_compress.push( batch.curvArray( 1 ) );
                    ctx->q_compress.push(&batch_curvArray[0]);
                }
                // 'compressCurvStructs:138' batch.size = 0;
                batch_size = 0.0;
            }
            // 'compressCurvStructs:44' if( addNewBatch )
            if (addNewBatch) {
                // 'compressCurvStructs:45' [ batch ] = batch_reset( ctx, curv );
                // 'compressCurvStructs:142' batch.pvec            = [curv.R0, curv.R1 ];
                // 'compressCurvStructs:143' batch.curvArray       = [ curv, curv ];
                // 'compressCurvStructs:144' batch.spindle_speed   = ctx.cfg.smax;
                // 'compressCurvStructs:145' batch.feedrate        = ctx.cfg.fmax;
                // 'compressCurvStructs:146' batch.size            = 1;
                for (int i5{0}; i5 < 6; i5++) {
                    b_curv[0][i5] = curv.R0[i5];
                    b_curv[1][i5] = curv.R1[i5];
                }
                batch_pvec.set_size(6, 2);
                for (int i8{0}; i8 < 2; i8++) {
                    for (int i9{0}; i9 < 6; i9++) {
                        batch_pvec[i9 + 6 * i8] = b_curv[i8][i9];
                    }
                }
                batch_curvArray[0] = curv;
                batch_curvArray[1] = curv;
                batch_size = 1.0;
            } else if (!addBatch) {
                // 'compressCurvStructs:46' elseif( ~addBatch )
                // 'compressCurvStructs:47' ctx.q_compress.push( curv );
                ctx->q_compress.push(&curv);
            }
        }
        // 'compressCurvStructs:53' [ ctx ] = batch_close( ctx, batch, spline_index );
        // 'compressCurvStructs:128' if( batch.size > 1 )
        if (batch_size > 1.0) {
            // 'compressCurvStructs:129' [ curvCompressed, spline, spline_index ] = ...
            // 'compressCurvStructs:130'         create_spline( ctx, batch, spline_index );
            b_spline_index = spline_index;
            create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                          ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                          ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                          batch_curvArray, &b_spline_index, &curvCompressed, &spline);
            // 'compressCurvStructs:132' ctx.q_compress.push( curvCompressed );
            ctx->q_compress.push(&curvCompressed);
            // 'compressCurvStructs:133' ctx.q_spline.push( spline );
            ctx->q_spline.push(&spline);
        } else if (batch_size > 0.0) {
            // 'compressCurvStructs:135' elseif( batch.size > 0 )
            // 'compressCurvStructs:136' ctx.q_compress.push( batch.curvArray( 1 ) );
            ctx->q_compress.push(&batch_curvArray[0]);
        }
        // 'compressCurvStructs:138' batch.size = 0;
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs.cpp
//
// [EOF]
//
