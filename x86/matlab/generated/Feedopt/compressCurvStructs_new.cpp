//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs_new.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:55:52
//

// Include Files
#include "compressCurvStructs_new.h"
#include "CalcBspline_Lee.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "SplineLengthApproxGL_tot.h"
#include "bspline_eval.h"
#include "combineVectorElements.h"
#include "constrCurvStruct.h"
#include "constrSplineStruct.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
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
    __m128d r;
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> b_batch_pvec;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1Dnorm;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> r9;
    ::coder::array<double, 2U> y;
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
    double d2;
    double d3;
    double d4;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    int b_bcoef;
    int c_batch_pvec;
    int c_k;
    int c_loop_ub;
    int csz_idx_1;
    int csz_idx_1_tmp;
    int ctx_cfg_GaussLegendreN_idx_0;
    int e_loop_ub;
    int end;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i13;
    int i14;
    int i15;
    int i2;
    int i20;
    int i27;
    int i3;
    int i4;
    int i5;
    int i6;
    int i7;
    int i_loop_ub;
    int j_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    int partialTrueCount;
    int scalarLB;
    int trueCount;
    unsigned int unnamed_idx_1;
    int vectorUB;
    signed char tmp_data[6];
    bool b_b;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs_new:139' spline            = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
        &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
        &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
        &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
        &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
        &params_spline_Bl_handle, &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
        &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim, &expl_temp,
        params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode, params_gcodeInfoStruct_TRAFO,
        params_gcodeInfoStruct_HSC, params_gcodeInfoStruct_FeedRate,
        params_gcodeInfoStruct_SpindleSpeed, params_gcodeInfoStruct_gcode_source_line,
        params_gcodeInfoStruct_G91, params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
        params_spline_Bl_breakpoints, params_spline_Bl_handle, params_spline_Bl_order,
        params_spline_coeff, params_spline_knots, params_spline_Ltot, params_spline_Lk, params_R0,
        params_R1, params_Cprim, params_evec, params_CoeffP5, spline);
    // 'compressCurvStructs_new:140' spline.Info.Type  = CurveType.Spline;
    spline->Info.Type = CurveType_Spline;
    // 'compressCurvStructs_new:141' spline.sp_index   = spline_index;
    spline->sp_index = *spline_index;
    // 'compressCurvStructs_new:142' spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec(
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
    // 'compressCurvStructs_new:143' [ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx, spline );
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
    if (4 > spline->sp.knots.size(1) - 3) {
        i2 = -1;
        i3 = -1;
    } else {
        i2 = 2;
        i3 = spline->sp.knots.size(1) - 4;
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
    i4 = i3 - i2;
    if (1 > i4 - 1) {
        i5 = 0;
    } else {
        i5 = (i3 - i2) - 1;
    }
    //  lower integration limits
    // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
    if (2 > i4) {
        i6 = -1;
        i7 = -1;
    } else {
        i6 = 0;
        i7 = (i3 - i2) - 1;
    }
    //  upper integration limits
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApproxGL_tot:16' GL_N   = ctx.cfg.GaussLegendreN;
    // 'SplineLengthApproxGL_tot:17' GL_X   = ctx.cfg.GaussLegendreX;
    // 'SplineLengthApproxGL_tot:18' GL_W   = ctx.cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [a, b]
    // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b,
    // (1+GL_X)))/2;
    r = _mm_set1_pd(1.0);
    _mm_storeu_pd(&b[0], _mm_sub_pd(r, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0])));
    _mm_storeu_pd(&b[2], _mm_sub_pd(r, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2])));
    b[4] = 1.0 - ctx_cfg_GaussLegendreX[4];
    c.set_size(5, i5);
    if (i5 != 0) {
        int acoef;
        int i8;
        acoef = (i5 != 1);
        i8 = i5 - 1;
        for (int k{0}; k <= i8; k++) {
            __m128d r1;
            __m128d r2;
            double d;
            r1 = _mm_loadu_pd(&b[0]);
            d = spline->sp.knots[(i2 + acoef * k) + 1];
            r2 = _mm_set1_pd(d);
            _mm_storeu_pd(&c[5 * k], _mm_mul_pd(r2, r1));
            r1 = _mm_loadu_pd(&b[2]);
            _mm_storeu_pd(&c[5 * k + 2], _mm_mul_pd(r2, r1));
            c[5 * k + 4] = d * b[4];
        }
    }
    _mm_storeu_pd(&b[0], _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]), r));
    _mm_storeu_pd(&b[2], _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]), r));
    b[4] = ctx_cfg_GaussLegendreX[4] + 1.0;
    csz_idx_1_tmp = i7 - i6;
    b_c.set_size(5, csz_idx_1_tmp);
    if (csz_idx_1_tmp != 0) {
        int b_acoef;
        int i9;
        b_acoef = (csz_idx_1_tmp != 1);
        i9 = csz_idx_1_tmp - 1;
        for (int b_k{0}; b_k <= i9; b_k++) {
            __m128d r3;
            __m128d r5;
            double d1;
            r3 = _mm_loadu_pd(&b[0]);
            d1 = spline->sp.knots[((i2 + i6) + b_acoef * b_k) + 2];
            r5 = _mm_set1_pd(d1);
            _mm_storeu_pd(&b_c[5 * b_k], _mm_mul_pd(r5, r3));
            r3 = _mm_loadu_pd(&b[2]);
            _mm_storeu_pd(&b_c[5 * b_k + 2], _mm_mul_pd(r5, r3));
            b_c[5 * b_k + 4] = d1 * b[4];
        }
    }
    if (c.size(1) == b_c.size(1)) {
        int b_loop_ub;
        Umat.set_size(5, c.size(1));
        b_loop_ub = c.size(1);
        for (int i10{0}; i10 < b_loop_ub; i10++) {
            __m128d r4;
            __m128d r6;
            __m128d r7;
            r4 = _mm_loadu_pd(&c[5 * i10]);
            r6 = _mm_loadu_pd(&b_c[5 * i10]);
            r7 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&Umat[5 * i10], _mm_div_pd(_mm_add_pd(r4, r6), r7));
            r4 = _mm_loadu_pd(&c[5 * i10 + 2]);
            r6 = _mm_loadu_pd(&b_c[5 * i10 + 2]);
            _mm_storeu_pd(&Umat[5 * i10 + 2], _mm_div_pd(_mm_add_pd(r4, r6), r7));
            Umat[5 * i10 + 4] = (c[5 * i10 + 4] + b_c[5 * i10 + 4]) / 2.0;
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
    unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
    // 'EvalBSpline:18' r1D = r0D;
    r1D.set_size(spline->sp.coeff.size(0), static_cast<int>(unnamed_idx_1));
    c_loop_ub = static_cast<int>(unnamed_idx_1);
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        int d_loop_ub;
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i12{0}; i12 < d_loop_ub; i12++) {
            r1D[i12 + r1D.size(0) * i11] = 0.0;
        }
    }
    // 'EvalBSpline:18' r2D = r1D;
    // 'EvalBSpline:18' r3D = r2D;
    // 'EvalBSpline:20' for j = 1 : M
    i13 = spline->sp.coeff.size(0);
    if (0 <= i13 - 1) {
        e_loop_ub = 5 * Umat.size(1);
        f_loop_ub = 5 * Umat.size(1);
        g_loop_ub = 5 * Umat.size(1);
        h_loop_ub = 5 * Umat.size(1);
        i14 = 5 * Umat.size(1);
        if (0 <= i14 - 1) {
            i15 = spline->sp.coeff.size(1);
            j_loop_ub = spline->sp.coeff.size(1);
        }
    }
    for (int j{0}; j < i13; j++) {
        int l_loop_ub;
        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
        // u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
        y.set_size(1, 5 * Umat.size(1));
        for (int i16{0}; i16 < e_loop_ub; i16++) {
            y[i16] = 0.0;
        }
        // 'bspline_eval_vec:4' xd      = zeros(size(u));
        r9.set_size(1, 5 * Umat.size(1));
        for (int i19{0}; i19 < f_loop_ub; i19++) {
            r9[i19] = 0.0;
        }
        // 'bspline_eval_vec:5' xdd     = zeros(size(u));
        r10.set_size(1, 5 * Umat.size(1));
        for (int i21{0}; i21 < g_loop_ub; i21++) {
            r10[i21] = 0.0;
        }
        // 'bspline_eval_vec:6' xddd    = zeros(size(u));
        r12.set_size(1, 5 * Umat.size(1));
        for (int i22{0}; i22 < h_loop_ub; i22++) {
            r12[i22] = 0.0;
        }
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int d_k{0}; d_k < i14; d_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            y[d_k] = Umat[d_k];
            b_spline.set_size(1, i15);
            for (int i25{0}; i25 < j_loop_ub; i25++) {
                b_spline[i25] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i25];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &y[d_k], &d2, &d3, &d4);
            r12[d_k] = d4;
            r10[d_k] = d3;
            r9[d_k] = d2;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        l_loop_ub = r9.size(1);
        for (int i23{0}; i23 < l_loop_ub; i23++) {
            r1D[j + r1D.size(0) * i23] = r9[i23];
        }
    }
    // 'SplineLengthApproxGL_tot:24' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    r8.set_size(r1D.size(0), r1D.size(1));
    i_loop_ub = r1D.size(1);
    for (int i17{0}; i17 < i_loop_ub; i17++) {
        int k_loop_ub;
        k_loop_ub = r1D.size(0);
        for (int i18{0}; i18 < k_loop_ub; i18++) {
            double varargin_1;
            varargin_1 = r1D[i18 + r1D.size(0) * i17];
            r8[i18 + r8.size(0) * i17] = std::pow(varargin_1, 2.0);
        }
    }
    coder::sum(r8, r1Dnorm);
    // 'mysqrt:3' y = sqrt(x);
    i20 = r1Dnorm.size(1);
    scalarLB = (r1Dnorm.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (c_k = 0; c_k <= vectorUB; c_k += 2) {
        __m128d r11;
        r11 = _mm_loadu_pd(&r1Dnorm[c_k]);
        _mm_storeu_pd(&r1Dnorm[c_k], _mm_sqrt_pd(r11));
    }
    for (c_k = scalarLB; c_k < i20; c_k++) {
        r1Dnorm[c_k] = std::sqrt(r1Dnorm[c_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApproxGL_tot:25' r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1);
    // 'SplineLengthApproxGL_tot:26' Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
    csz_idx_1 = (i3 - i2) - 1;
    c.set_size(5, (i3 - i2) - 1);
    if (csz_idx_1 != 0) {
        int bcoef;
        int i24;
        bcoef = ((i3 - i2) - 1 != 1);
        i24 = csz_idx_1 - 1;
        if (0 <= c.size(1) - 1) {
            b_bcoef = (static_cast<int>(ctx_cfg_GaussLegendreN) != 1);
            ctx_cfg_GaussLegendreN_idx_0 = static_cast<int>(ctx_cfg_GaussLegendreN);
        }
        for (int f_k{0}; f_k <= i24; f_k++) {
            int varargin_3;
            varargin_3 = bcoef * f_k;
            for (int g_k{0}; g_k < 5; g_k++) {
                c[g_k + 5 * f_k] =
                    ctx_cfg_GaussLegendreW[g_k] *
                    r1Dnorm[b_bcoef * g_k + ctx_cfg_GaussLegendreN_idx_0 * varargin_3];
            }
        }
    }
    if (c.size(1) == 0) {
        y.set_size(1, 0);
    } else {
        int i26;
        y.set_size(1, c.size(1));
        i26 = c.size(1);
        for (int e_k{0}; e_k < i26; e_k++) {
            y[e_k] = c[5 * e_k];
            y[e_k] = y[e_k] + c[5 * e_k + 1];
            y[e_k] = y[e_k] + c[5 * e_k + 2];
            y[e_k] = y[e_k] + c[5 * e_k + 3];
            y[e_k] = y[e_k] + c[5 * e_k + 4];
        }
    }
    if (i7 - i6 == 1) {
        i27 = i5;
    } else {
        i27 = i7 - i6;
    }
    if ((csz_idx_1_tmp == i5) && (y.size(1) == i27)) {
        int b_scalarLB;
        int b_vectorUB;
        int i28;
        int m_loop_ub;
        spline->sp.Lk.set_size(1, y.size(1));
        m_loop_ub = y.size(1);
        b_scalarLB = (y.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i28 = 0; i28 <= b_vectorUB; i28 += 2) {
            __m128d r13;
            __m128d r14;
            __m128d r15;
            r13 = _mm_loadu_pd(&spline->sp.knots[((i2 + i6) + i28) + 2]);
            r14 = _mm_loadu_pd(&spline->sp.knots[(i2 + i28) + 1]);
            r15 = _mm_loadu_pd(&y[i28]);
            _mm_storeu_pd(&spline->sp.Lk[i28],
                          _mm_div_pd(_mm_mul_pd(r15, _mm_sub_pd(r13, r14)), _mm_set1_pd(2.0)));
        }
        for (i28 = b_scalarLB; i28 < m_loop_ub; i28++) {
            spline->sp.Lk[i28] =
                y[i28] *
                (spline->sp.knots[((i2 + i6) + i28) + 2] - spline->sp.knots[(i2 + i28) + 1]) / 2.0;
        }
    } else {
        binary_expand_op(spline, y, i2 + 1, i6 + 1, i7, i5 - 1);
    }
    //  Gauss Legendre integration
    // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
    spline->sp.Ltot = coder::sum(spline->sp.Lk);
    // 'compressCurvStructs_new:144' spline.sp.Ltot    = Ltot;
    // 'compressCurvStructs_new:145' spline.sp.Lk      = Lk;
    // 'compressCurvStructs_new:147' curv    = constrSplineStruct( batch.curvArray( end ).Info,
    // batch.pvec( :, 1 ), ... 'compressCurvStructs_new:148'     batch.pvec( :,end ), uint32(
    // spline_index ) );
    c_batch_pvec = batch_pvec.size(1);
    for (int i29{0}; i29 < 6; i29++) {
        dv[i29] = (*(double(*)[6]) & batch_pvec[0])[i29];
    }
    for (int i30{0}; i30 < 6; i30++) {
        dv1[i30] = (*(double(*)[6]) & batch_pvec[6 * (c_batch_pvec - 1)])[i30];
    }
    constrSplineStruct(batch_curvArray[1].Info.zspdmode, batch_curvArray[1].Info.TRAFO,
                       batch_curvArray[1].Info.HSC, batch_curvArray[1].Info.FeedRate,
                       batch_curvArray[1].Info.SpindleSpeed,
                       batch_curvArray[1].Info.gcode_source_line, batch_curvArray[1].Info.G91,
                       batch_curvArray[1].Info.G91_1, dv, dv1, *spline_index, curv);
    //  Calculate the ZSpdMode for the spline
    // 'compressCurvStructs_new:151' first   = batch.curvArray( 1 );
    // 'compressCurvStructs_new:152' last    = batch.curvArray( end );
    // 'compressCurvStructs_new:154' if ( ~isAZeroSpeed( first ) ) && ( ~isAZeroSpeed( last ) )
    //  isAZeroSpeed : Return true if the curv is has a zero speed
    //  Input :
    //  curv  : The curve struct
    // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
    b_b = (batch_curvArray[0].Info.zspdmode != ZSpdMode_NN);
    if ((!b_b) && (!(batch_curvArray[1].Info.zspdmode != ZSpdMode_NN))) {
        //  isAZeroSpeed : Return true if the curv is has a zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
        // 'compressCurvStructs_new:155' curv.Info.zspdmode = ZSpdMode.NN;
        curv->Info.zspdmode = ZSpdMode_NN;
    } else if ((!b_b) && ((batch_curvArray[1].Info.zspdmode == ZSpdMode_NZ) ||
                          (batch_curvArray[1].Info.zspdmode == ZSpdMode_ZZ))) {
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        // 'isAZeroEnd:7' zeroFlag = true;
        // 'compressCurvStructs_new:156' elseif ( ~isAZeroSpeed( first ) ) && ( isAZeroEnd( last ) )
        // 'compressCurvStructs_new:157' curv.Info.zspdmode = ZSpdMode.NZ;
        curv->Info.zspdmode = ZSpdMode_NZ;

        // 'isAZeroEnd:9' zeroFlag = false;
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
    } else if (((batch_curvArray[0].Info.zspdmode == ZSpdMode_ZN) ||
                (batch_curvArray[0].Info.zspdmode == ZSpdMode_ZZ)) &&
               (!(batch_curvArray[1].Info.zspdmode != ZSpdMode_NN))) {
        // 'isAZeroStart:6' zeroFlag = true;
        //  isAZeroSpeed : Return true if the curv is has a zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
        // 'compressCurvStructs_new:158' elseif ( isAZeroStart( first ) ) && ( ~isAZeroSpeed( last )
        // ) 'compressCurvStructs_new:159' curv.Info.zspdmode = ZSpdMode.ZN;
        curv->Info.zspdmode = ZSpdMode_ZN;
    } else {
        // 'isAZeroStart:8' zeroFlag = false;
        // 'compressCurvStructs_new:160' else
        // 'compressCurvStructs_new:161' curv.Info.zspdmode = ZSpdMode.ZZ;
        curv->Info.zspdmode = ZSpdMode_ZZ;
    }
    // 'compressCurvStructs_new:164' spline_index = spline_index + 1;
    (*spline_index)++;
}

//
// function [ ctx ] = compressCurvStructs_new( ctx )
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
void compressCurvStructs_new(const b_FeedoptContext *ctx)
{
    ::coder::array<double, 2U> batch_pvec;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    CurvStruct batch_curvArray[2];
    CurvStruct C;
    CurvStruct curv;
    CurvStruct curvCompressed;
    CurvStruct prevCurv;
    CurvStruct spline;
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
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    unsigned int b_spline_index;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    unsigned int spline_index;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs_new:14' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double batch_size;
        unsigned int Ncrv;
        int i1;
        // 'compressCurvStructs_new:16' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs_new:17' Ncrv                = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        // 'compressCurvStructs_new:18' [ batch ]           = batch_init();
        // 'compressCurvStructs_new:95' batch = struct( ...
        // 'compressCurvStructs_new:96'     'pvec',          zeros( StructTypeName.NumberAxisMax, 1
        // ),... 'compressCurvStructs_new:97'     'curvArray',     repmat( constrCurvStructType, 1,
        // 2 ),... 'compressCurvStructs_new:98'     'spindle_speed', 0,...
        // 'compressCurvStructs_new:99'     'feedrate',      0,...
        // 'compressCurvStructs_new:100'     'size',          0 ...
        // 'compressCurvStructs_new:101'     );
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff,
                          params_spline_Bl_breakpoints, &params_spline_Bl_handle,
                          &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                          &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                          &expl_temp, params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5,
                          &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline,
        // ... 'constrCurvStructType:14'         params.R0, params.R1, ... 'constrCurvStructType:15'
        // params.Cprim, params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
        // params.pitch, params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
                           params_spline_Bl_breakpoints, params_spline_Bl_handle,
                           params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                           params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                           params_evec, params_CoeffP5, &C);
        batch_pvec.set_size(6, 1);
        for (int i{0}; i < 6; i++) {
            batch_pvec[i] = 0.0;
        }
        batch_curvArray[0] = C;
        batch_curvArray[1] = C;
        batch_size = 0.0;
        // 'compressCurvStructs_new:103' if( ~coder.target( "MATLAB" ) )
        // 'compressCurvStructs_new:104' coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
        // 'compressCurvStructs_new:20' DebugLog(DebugCfg.Validate, 'Compressing...\n');
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
        // 'compressCurvStructs_new:22' for k = 1 : Ncrv
        i1 = static_cast<int>(Ncrv);
        for (int k{0}; k < i1; k++) {
            bool addBatch;
            bool addBatchNew;
            bool closeBatch;
            // 'compressCurvStructs_new:23' curv = ctx.q_gcode.get( k );
            ctx->q_gcode.get(k + 1U, &curv);
            //  Get next Curve in the queue
            // 'compressCurvStructs_new:25' [ addBatch, addBatchNew ] = check_add_batch( ctx, curv,
            // batch );
            // -------------------------------------------------------------------------%
            // 'compressCurvStructs_new:56' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs_new:58' addBatch    = true;
            addBatch = true;
            // 'compressCurvStructs_new:59' addBatchNew = false;
            addBatchNew = false;
            // 'compressCurvStructs_new:61' if( curv.Info.Type ~= CurveType.Line )
            if (curv.Info.Type != CurveType_Line) {
                // 'compressCurvStructs_new:62' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs_new:66' if( LengthCurv( ctx, curv, 0, 1 ) >
                // ctx.cfg.LThreshold )
            } else if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  curv.Info, curv.R0, curv.R1, curv.CorrectedHelixCenter, curv.evec,
                                  curv.theta, curv.pitch, curv.CoeffP5, curv.sp_index, curv.a_param,
                                  curv.b_param) > ctx->cfg.LThreshold) {
                // 'compressCurvStructs_new:67' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs_new:70' if( batch.size > 0 )
            } else if (batch_size > 0.0) {
                bool collinear;
                // 'compressCurvStructs_new:71' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    // 'compressCurvStructs_new:72' prevCurv = batch.curvArray( end );
                    prevCurv = batch_curvArray[1];
                } else {
                    // 'compressCurvStructs_new:73' else
                    // 'compressCurvStructs_new:74' prevCurv = batch.curvArray( 1 );
                    prevCurv = batch_curvArray[0];
                }
                // 'compressCurvStructs_new:76' collinear = curvCollinear( ctx, prevCurv, curv, ...
                // 'compressCurvStructs_new:77'         ctx.cfg.Compressing.ColTolCosLee );
                // 'curvCollinear:3' [~, V0] = EvalCurvStruct(ctx, Curv1, 1);
                b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &prevCurv, a__1, V0);
                // 'curvCollinear:4' [~, V1] = EvalCurvStruct(ctx, Curv2, 0);
                c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
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
                    // 'collinear:7' value = cos_angle > tol_cos;
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
                    for (int i6{0}; i6 < loop_ub; i6++) {
                        double varargin_1;
                        varargin_1 = V0[i6];
                        r[i6] = std::pow(varargin_1, 2.0);
                    }
                    r1.set_size(V1.size(0));
                    b_loop_ub = V1.size(0);
                    for (int i7{0}; i7 < b_loop_ub; i7++) {
                        double b_varargin_1;
                        b_varargin_1 = V1[i7];
                        r1[i7] = std::pow(b_varargin_1, 2.0);
                    }
                    collinear = (c / (std::sqrt(coder::combineVectorElements(r)) *
                                      std::sqrt(coder::combineVectorElements(r1))) >
                                 ctx->cfg.Compressing.ColTolCosLee);
                }
                // 'compressCurvStructs_new:78' if( ~collinear )
                if (!collinear) {
                    // 'compressCurvStructs_new:78' addBatch = false;
                    addBatch = false;
                    // 'compressCurvStructs_new:78' addBatchNew = true;
                    addBatchNew = true;
                }
            }
            // 'compressCurvStructs_new:26' [ closeBatch ] = check_close_batch( curv, addBatch );
            // 'compressCurvStructs_new:84' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs_new:86' closeBatch = false;
            closeBatch = false;
            // 'compressCurvStructs_new:88' if( ~addBatch )
            if (!addBatch) {
                // 'compressCurvStructs_new:88' closeBatch = true;
                closeBatch = true;

                // 'compressCurvStructs_new:90' if( isAZeroEnd( curv ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            } else if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'compressCurvStructs_new:90' closeBatch = true;
                closeBatch = true;
            } else {
                // 'isAZeroEnd:9' zeroFlag = false;
            }
            // 'compressCurvStructs_new:28' if( addBatch )
            if (addBatch) {
                // 'compressCurvStructs_new:29' if( batch.size > 0)
                if (batch_size > 0.0) {
                    int i2;
                    // 'compressCurvStructs_new:30' [ batch ] = batch_add_curv( batch, curv );
                    // 'compressCurvStructs_new:131' batch.pvec             = [ batch.pvec, curv.R1
                    // ];
                    i2 = batch_pvec.size(1);
                    batch_pvec.set_size(6, batch_pvec.size(1) + 1);
                    for (int i3{0}; i3 < 6; i3++) {
                        batch_pvec[i3 + 6 * i2] = curv.R1[i3];
                    }
                    // 'compressCurvStructs_new:132' batch.curvArray( end ) = curv;
                    batch_curvArray[1] = curv;
                    // 'compressCurvStructs_new:133' batch.spindle_speed    = min(
                    // batch.spindle_speed , curv.Info.SpindleSpeed ); 'compressCurvStructs_new:134'
                    // batch.feedrate         = min( batch.feedrate, curv.Info.FeedRate );
                    // 'compressCurvStructs_new:135' batch.size             = batch.size + 1;
                    batch_size++;
                } else {
                    // 'compressCurvStructs_new:31' else
                    // 'compressCurvStructs_new:32' [ batch ] = batch_reset( ctx, curv );
                    // 'compressCurvStructs_new:123' batch.pvec            = curv.R0;
                    // 'compressCurvStructs_new:124' batch.curvArray       = [ curv, curv ];
                    // 'compressCurvStructs_new:125' batch.spindle_speed   = ctx.cfg.smax;
                    // 'compressCurvStructs_new:126' batch.feedrate        = ctx.cfg.fmax;
                    // 'compressCurvStructs_new:127' batch.size            = 1;
                    batch_pvec.set_size(6, 1);
                    for (int i4{0}; i4 < 6; i4++) {
                        batch_pvec[i4] = curv.R0[i4];
                    }
                    batch_curvArray[0] = curv;
                    batch_curvArray[1] = curv;
                    batch_size = 1.0;
                }
            }
            // 'compressCurvStructs_new:36' if( closeBatch )
            if (closeBatch) {
                // 'compressCurvStructs_new:37' [ ctx, batch, spline_index ] = batch_close( ctx,
                // batch, spline_index ); 'compressCurvStructs_new:109' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    // 'compressCurvStructs_new:110' [ curvCompressed, spline, spline_index ] = ...
                    // 'compressCurvStructs_new:111'         create_spline( ctx, batch, spline_index
                    // );
                    create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                                  ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                                  ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                                  batch_curvArray, &spline_index, &curvCompressed, &spline);
                    // 'compressCurvStructs_new:113' ctx.q_compress.push( curvCompressed );
                    ctx->q_compress.push(&curvCompressed);
                    // 'compressCurvStructs_new:114' ctx.q_spline.push( spline );
                    ctx->q_spline.push(&spline);
                } else if (batch_size > 0.0) {
                    // 'compressCurvStructs_new:116' elseif( batch.size > 0 )
                    // 'compressCurvStructs_new:117' ctx.q_compress.push( batch.curvArray( 1 ) );
                    ctx->q_compress.push(&batch_curvArray[0]);
                }
                // 'compressCurvStructs_new:119' batch.size = 0;
                batch_size = 0.0;
            }
            // 'compressCurvStructs_new:40' if( addBatchNew )
            if (addBatchNew) {
                // 'compressCurvStructs_new:41' [ batch ] = batch_reset( ctx, curv );
                // 'compressCurvStructs_new:123' batch.pvec            = curv.R0;
                // 'compressCurvStructs_new:124' batch.curvArray       = [ curv, curv ];
                // 'compressCurvStructs_new:125' batch.spindle_speed   = ctx.cfg.smax;
                // 'compressCurvStructs_new:126' batch.feedrate        = ctx.cfg.fmax;
                // 'compressCurvStructs_new:127' batch.size            = 1;
                batch_pvec.set_size(6, 1);
                for (int i5{0}; i5 < 6; i5++) {
                    batch_pvec[i5] = curv.R0[i5];
                }
                batch_curvArray[0] = curv;
                batch_curvArray[1] = curv;
                batch_size = 1.0;
            } else if (!addBatch) {
                // 'compressCurvStructs_new:42' elseif( ~addBatch )
                // 'compressCurvStructs_new:43' ctx.q_compress.push( curv );
                ctx->q_compress.push(&curv);
            }
        }
        // 'compressCurvStructs_new:49' [ ctx ] = batch_close( ctx, batch, spline_index );
        // 'compressCurvStructs_new:109' if( batch.size > 1 )
        if (batch_size > 1.0) {
            // 'compressCurvStructs_new:110' [ curvCompressed, spline, spline_index ] = ...
            // 'compressCurvStructs_new:111'         create_spline( ctx, batch, spline_index );
            b_spline_index = spline_index;
            create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                          ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                          ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                          batch_curvArray, &b_spline_index, &curvCompressed, &spline);
            // 'compressCurvStructs_new:113' ctx.q_compress.push( curvCompressed );
            ctx->q_compress.push(&curvCompressed);
            // 'compressCurvStructs_new:114' ctx.q_spline.push( spline );
            ctx->q_spline.push(&spline);
        } else if (batch_size > 0.0) {
            // 'compressCurvStructs_new:116' elseif( batch.size > 0 )
            // 'compressCurvStructs_new:117' ctx.q_compress.push( batch.curvArray( 1 ) );
            ctx->q_compress.push(&batch_curvArray[0]);
        }
        // 'compressCurvStructs_new:119' batch.size = 0;
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs_new.cpp
//
// [EOF]
//
