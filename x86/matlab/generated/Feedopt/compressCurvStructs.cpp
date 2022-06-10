//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "compressCurvStructs.h"
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

// Function Definitions
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
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void compressCurvStructs(const FeedoptContext *ctx)
{
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> b_pvec;
    ::coder::array<double, 2U> b_splineCurve;
    ::coder::array<double, 2U> c_c;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> pvec;
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r14;
    ::coder::array<double, 2U> r15;
    ::coder::array<double, 2U> r17;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    CurvStruct curve;
    CurvStruct preCurve;
    CurvStruct spline;
    CurvStruct splineCurve;
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
    int ctx_idx_0;
    int i34;
    int n_loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs:14' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double CumulatedLength;
        unsigned int Ncrv;
        int i1;
        unsigned int spline_index;
        ZSpdMode zspdmodevec_idx_0;
        ZSpdMode zspdmodevec_idx_1;
        // 'compressCurvStructs:16' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs:17' Length_Threshold    = ctx.cfg.LThreshold;
        //  in [mm]
        // 'compressCurvStructs:18' Ncrv    = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        //  Vector for the speed mode of the first and the last segment of the spline
        // 'compressCurvStructs:21' zspdmodevec = [ ZSpdMode.NN, ZSpdMode.NN ];
        zspdmodevec_idx_0 = ZSpdMode_NN;
        zspdmodevec_idx_1 = ZSpdMode_NN;
        // 'compressCurvStructs:23' CumulatedLength = 0;
        CumulatedLength = 0.0;
        //  Accumulator for the length
        // 'compressCurvStructs:24' spindle_speed   = 75000;
        //  in [rpm]
        // 'compressCurvStructs:26' DebugLog(DebugCfg.Validate, 'Compressing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Compressing...\n");
            fflush(stdout);
        }
        //  Satisfy coder
        // 'compressCurvStructs:29' if ( ~ coder.target( 'MATLAB' ) )
        // 'compressCurvStructs:30' pvec    = zeros( 6, 1 );
        pvec.set_size(6, 1);
        for (int i{0}; i < 6; i++) {
            pvec[i] = 0.0;
        }
        // 'compressCurvStructs:31' coder.varsize( 'pvec', [ 6, Inf ], [0, 1] );
        // 'compressCurvStructs:34' for k = 1 : Ncrv
        i1 = static_cast<int>(Ncrv);
        for (int k{0}; k < i1; k++) {
            bool Collinear;
            // 'compressCurvStructs:35' curve = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k + 1U, &curve);
            //  Get next Curv in the queue
            //  If the next curve segment is too long for compressing or it is not an NN,
            //  we need to stop growing the compressing list and create the spline
            // 'compressCurvStructs:39' if k > 1
            if (k + 1U > 1U) {
                //  Check colinearity with previous segment
                // 'compressCurvStructs:40' preCurve    = ctx.q_gcode.get( k-1 );
                ctx->q_gcode.get(static_cast<unsigned int>(k), &preCurve);
                // 'compressCurvStructs:41' Collinear   = curvCollinear(ctx, preCurve, curve, ...
                // 'compressCurvStructs:42'             ctx.cfg.Compressing.ColTolCosLee);
                // 'curvCollinear:3' [~, V0] = EvalCurvStruct(ctx, Curv1, 1);
                b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                 ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                                 ctx->cfg.indRot.data, ctx->cfg.indRot.size[0],
                                 ctx->cfg.indTot.data, ctx->cfg.indTot.size[0], preCurve.Info.Type,
                                 preCurve.R0, preCurve.R1, preCurve.CorrectedHelixCenter,
                                 preCurve.evec, preCurve.theta, preCurve.pitch, preCurve.CoeffP5,
                                 preCurve.sp_index, preCurve.a_param, preCurve.b_param, a__1, V0);
                // 'curvCollinear:4' [~, V1] = EvalCurvStruct(ctx, Curv2, 0);
                c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                 ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                                 ctx->cfg.indRot.data, ctx->cfg.indRot.size[0],
                                 ctx->cfg.indTot.data, ctx->cfg.indTot.size[0], curve.Info.Type,
                                 curve.R0, curve.R1, curve.CorrectedHelixCenter, curve.evec,
                                 curve.theta, curve.pitch, curve.CoeffP5, curve.sp_index,
                                 curve.a_param, curve.b_param, a__2, V1);
                // 'curvCollinear:6' result = collinear(V0, V1, ToleranceCos);
                // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
                if ((coder::b_norm(V0) < 2.2204460492503131E-16) ||
                    (coder::b_norm(V1) < 2.2204460492503131E-16)) {
                    // 'collinear:3' value = true;
                    Collinear = true;
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
                    for (int i5{0}; i5 < loop_ub; i5++) {
                        double varargin_1;
                        varargin_1 = V0[i5];
                        r[i5] = std::pow(varargin_1, 2.0);
                    }
                    r1.set_size(V1.size(0));
                    b_loop_ub = V1.size(0);
                    for (int i6{0}; i6 < b_loop_ub; i6++) {
                        double b_varargin_1;
                        b_varargin_1 = V1[i6];
                        r1[i6] = std::pow(b_varargin_1, 2.0);
                    }
                    Collinear = (c / (std::sqrt(coder::combineVectorElements(r)) *
                                      std::sqrt(coder::combineVectorElements(r1))) >
                                 ctx->cfg.Compressing.ColTolCosLee);
                }
            } else {
                // 'compressCurvStructs:43' else
                //  Set default value for the c code generation
                // 'compressCurvStructs:44' preCurve    = curve;
                preCurve = curve;
                // 'compressCurvStructs:45' Collinear   = false;
                Collinear = false;
            }
            //  A new spline is created if one of the following conditions is met :
            //   - The length of the current curve is too long for the compressing
            //   - One of the boundaries speed is zero
            //  No more segment is added to the list of compressing curves
            // 'compressCurvStructs:52' if ( curve.Info.Type ~= CurveType.Line )        || ... % Not
            // a Line 'compressCurvStructs:53'             ( curve.Info.zspdmode == ZSpdMode.NZ ) ||
            // ... % Zero stop 'compressCurvStructs:54'             ( (k ~= 1)  && ~Collinear ) ||
            // ... % Not collinear and not 1rst segment 'compressCurvStructs:55'             ( (k ==
            // Ncrv) && (CumulatedLength ~= 0) )    || ... % Last segment and on-going compression
            // 'compressCurvStructs:56'             ( LengthCurv(ctx, curve, 0, 1) >=
            // Length_Threshold )
            if ((curve.Info.Type != CurveType_Line) || (curve.Info.zspdmode == ZSpdMode_NZ) ||
                ((k + 1U != 1U) && (!Collinear)) ||
                ((k + 1U == Ncrv) && (CumulatedLength != 0.0)) ||
                (LengthCurv(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                            ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                            ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                            ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, CurveType_Line,
                            curve.R0, curve.R1, curve.CorrectedHelixCenter, curve.evec, curve.theta,
                            curve.pitch, curve.CoeffP5, curve.sp_index, curve.a_param,
                            curve.b_param) >= ctx->cfg.LThreshold)) {
                //  % Not a Line
                //  % Zero stop
                //  % Not collinear and not 1rst segment
                //  % Last segment and on-going compression
                //  Too long segment
                //  In this case add the last segment
                // 'compressCurvStructs:59' if ( ( isAZeroEnd( curve ) ) || ... % Zero stop OR Last
                // segment 'compressCurvStructs:60'                 ( k == Ncrv ) ) && (
                // CumulatedLength ~= 0 )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if (((curve.Info.zspdmode == ZSpdMode_NZ) || (curve.Info.zspdmode == ZSpdMode_ZZ) ||
                     (k + 1U == Ncrv)) &&
                    (CumulatedLength != 0.0)) {
                    int i7;
                    // 'isAZeroEnd:7' zeroFlag = true;
                    //  % Zero stop OR Last segment
                    //  AND on-going compression
                    // 'compressCurvStructs:61' pvec = [ pvec curve.R1 ];
                    i7 = pvec.size(1);
                    pvec.set_size(6, pvec.size(1) + 1);
                    for (int i8{0}; i8 < 6; i8++) {
                        pvec[i8 + 6 * i7] = curve.R1[i8];
                    }
                    // 'compressCurvStructs:62' zspdmodevec( end ) =  curve.Info.zspdmode;
                    zspdmodevec_idx_1 = curve.Info.zspdmode;
                    // 'compressCurvStructs:63' spindle_speed = min( spindle_speed,
                    // curve.Info.SpindleSpeed );
                } else {
                    // 'isAZeroEnd:9' zeroFlag = false;
                }
                //  If the cumulated length is zero, no compressing is on-going.
                //  The segment is treated individually
                // 'compressCurvStructs:69' if ( CumulatedLength == 0 )
                if (CumulatedLength == 0.0) {
                    // 'compressCurvStructs:70' ctx.q_compress.push( curve );
                    ctx->q_compress.push(&curve);
                    //  If there was an on-going compression
                } else {
                    // 'compressCurvStructs:73' else
                    //  We have more than 2 points, thus constructing a spline
                    //  is warranted
                    // 'compressCurvStructs:76' if ( size( pvec, 2 ) > 2 )
                    if (pvec.size(1) > 2) {
                        __m128d r2;
                        __m128d r3;
                        __m128d r4;
                        int c_loop_ub;
                        int c_pvec;
                        int e_k;
                        int f_loop_ub;
                        int i11;
                        int i12;
                        int i13;
                        int i14;
                        int i15;
                        int i16;
                        int i18;
                        int i23;
                        int i27;
                        int i30;
                        int i36;
                        int j_loop_ub;
                        int scalarLB;
                        unsigned int unnamed_idx_1;
                        int vectorUB;
                        // 'compressCurvStructs:77' splineCurve             = constrCurvStructType;
                        //  constrCurvStructType : Constructs a constrCurvStruct with default
                        //  values.
                        // 'constrCurvStructType:4' if( nargin > 0 )
                        // 'constrCurvStructType:6' else
                        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                        paramsDefaultCurv(
                            &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                            &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                            &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                            &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                            &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff,
                            params_spline_Bl_breakpoints, &params_spline_Bl_handle,
                            &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                            &params_spline_Ltot, params_spline_Lk, params_R0, params_R1,
                            params_Cprim, &expl_temp, params_evec, &b_expl_temp, &c_expl_temp,
                            params_CoeffP5, &d_expl_temp);
                        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                        // 'constrCurvStructType:12' else
                        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                        // params.spline, ... 'constrCurvStructType:14'         params.R0,
                        // params.R1, ... 'constrCurvStructType:15'         params.Cprim,
                        // params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
                        // params.pitch, params.CoeffP5, params.Coeff );
                        b_constrCurvStruct(
                            params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                            params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                            params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                            params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                            params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
                            params_spline_Bl_breakpoints, params_spline_Bl_handle,
                            params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                            params_spline_Ltot, params_spline_Lk, params_R0, params_R1,
                            params_Cprim, params_evec, params_CoeffP5, &splineCurve);
                        // 'compressCurvStructs:78' splineCurve.Info.Type   = CurveType.Spline;
                        splineCurve.Info.Type = CurveType_Spline;
                        // 'compressCurvStructs:79' splineCurve.sp_index    = spline_index;
                        splineCurve.sp_index = spline_index;
                        // 'compressCurvStructs:80' splineCurve.sp          = CalcBspline_Lee(
                        // ctx.cfg, pvec( ctx.cfg.indTot, : ) );
                        c_loop_ub = pvec.size(1);
                        b_pvec.set_size(ctx->cfg.indTot.size[0], pvec.size(1));
                        for (int i9{0}; i9 < c_loop_ub; i9++) {
                            int d_loop_ub;
                            d_loop_ub = ctx->cfg.indTot.size[0];
                            for (int i10{0}; i10 < d_loop_ub; i10++) {
                                b_pvec[i10 + b_pvec.size(0) * i9] =
                                    pvec[(ctx->cfg.indTot.data[i10] + 6 * i9) - 1];
                            }
                        }
                        CalcBspline_Lee(ctx->cfg.NumberAxis, ctx->cfg.LeeSplineDegree, b_pvec,
                                        &splineCurve.sp.Bl.ncoeff, splineCurve.sp.Bl.breakpoints,
                                        &splineCurve.sp.Bl.handle, &splineCurve.sp.Bl.order,
                                        splineCurve.sp.coeff, splineCurve.sp.knots,
                                        &splineCurve.sp.Ltot, splineCurve.sp.Lk);
                        // 'compressCurvStructs:81' [Ltot, Lk]              =
                        // SplineLengthApproxGL_tot( ctx, splineCurve );
                        //  Precomputes approximately the total arc length L as well as the
                        //  individual arc lengths between knot points of a parametric spline. The
                        //  computation is based on numerical Gauss Legendre integration.
                        //  SplineLengthApproxGL_tot should only be called once since the result
                        //  of the computation is stored and reused later.
                        //  get the sp structure
                        //  Spline = ctx.q_spline.get(Curv.sp_index);
                        //  sp     = Spline.sp;
                        // 'SplineLengthApproxGL_tot:11' sp     = Curv.sp;
                        // 'SplineLengthApproxGL_tot:12' Knots  = sp.knots(4:end-3);
                        if (4 > splineCurve.sp.knots.size(1) - 3) {
                            i11 = -1;
                            i12 = -1;
                        } else {
                            i11 = 2;
                            i12 = splineCurve.sp.knots.size(1) - 4;
                        }
                        //  eliminate multiplicities at the end points
                        // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
                        i13 = i12 - i11;
                        if (1 > i13 - 1) {
                            i14 = 0;
                        } else {
                            i14 = (i12 - i11) - 1;
                        }
                        //  lower integration limits
                        // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
                        if (2 > i13) {
                            i15 = -1;
                            i16 = -1;
                        } else {
                            i15 = 0;
                            i16 = (i12 - i11) - 1;
                        }
                        //  upper integration limits
                        //  get Gauss-Legendre knots and weights
                        // 'SplineLengthApproxGL_tot:16' GL_N   = ctx.cfg.GaussLegendreN;
                        // 'SplineLengthApproxGL_tot:17' GL_X   = ctx.cfg.GaussLegendreX;
                        // 'SplineLengthApproxGL_tot:18' GL_W   = ctx.cfg.GaussLegendreW;
                        //  apply linear map from[-1, 1] to [a, b]
                        // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) +
                        // bsxfun(@times, b, (1+GL_X)))/2;
                        r2 = _mm_loadu_pd((const double *)&ctx->cfg.GaussLegendreX[0]);
                        r3 = _mm_set1_pd(1.0);
                        _mm_storeu_pd(&b[0], _mm_sub_pd(r3, r2));
                        r2 = _mm_loadu_pd((const double *)&ctx->cfg.GaussLegendreX[2]);
                        _mm_storeu_pd(&b[2], _mm_sub_pd(r3, r2));
                        b[4] = 1.0 - ctx->cfg.GaussLegendreX[4];
                        b_c.set_size(5, i14);
                        if (i14 != 0) {
                            int acoef;
                            int i17;
                            acoef = (i14 != 1);
                            i17 = i14 - 1;
                            for (int c_k{0}; c_k <= i17; c_k++) {
                                __m128d r5;
                                __m128d r6;
                                double d;
                                r5 = _mm_loadu_pd(&b[0]);
                                d = splineCurve.sp.knots[(i11 + acoef * c_k) + 1];
                                r6 = _mm_set1_pd(d);
                                _mm_storeu_pd(&b_c[5 * c_k], _mm_mul_pd(r6, r5));
                                r5 = _mm_loadu_pd(&b[2]);
                                _mm_storeu_pd(&b_c[5 * c_k + 2], _mm_mul_pd(r6, r5));
                                b_c[5 * c_k + 4] = d * b[4];
                            }
                        }
                        r4 = _mm_loadu_pd((const double *)&ctx->cfg.GaussLegendreX[0]);
                        _mm_storeu_pd(&b[0], _mm_add_pd(r4, r3));
                        r4 = _mm_loadu_pd((const double *)&ctx->cfg.GaussLegendreX[2]);
                        _mm_storeu_pd(&b[2], _mm_add_pd(r4, r3));
                        b[4] = ctx->cfg.GaussLegendreX[4] + 1.0;
                        i18 = i16 - i15;
                        c_c.set_size(5, i18);
                        if (i18 != 0) {
                            int b_acoef;
                            int i19;
                            b_acoef = (i18 != 1);
                            i19 = i18 - 1;
                            for (int d_k{0}; d_k <= i19; d_k++) {
                                __m128d r7;
                                __m128d r9;
                                double d1;
                                r7 = _mm_loadu_pd(&b[0]);
                                d1 = splineCurve.sp.knots[((i11 + i15) + b_acoef * d_k) + 2];
                                r9 = _mm_set1_pd(d1);
                                _mm_storeu_pd(&c_c[5 * d_k], _mm_mul_pd(r9, r7));
                                r7 = _mm_loadu_pd(&b[2]);
                                _mm_storeu_pd(&c_c[5 * d_k + 2], _mm_mul_pd(r9, r7));
                                c_c[5 * d_k + 4] = d1 * b[4];
                            }
                        }
                        if (b_c.size(1) == c_c.size(1)) {
                            int e_loop_ub;
                            Umat.set_size(5, b_c.size(1));
                            e_loop_ub = b_c.size(1);
                            for (int i20{0}; i20 < e_loop_ub; i20++) {
                                __m128d r10;
                                __m128d r11;
                                __m128d r8;
                                r8 = _mm_loadu_pd(&b_c[5 * i20]);
                                r10 = _mm_loadu_pd(&c_c[5 * i20]);
                                r11 = _mm_set1_pd(2.0);
                                _mm_storeu_pd(&Umat[5 * i20], _mm_div_pd(_mm_add_pd(r8, r10), r11));
                                r8 = _mm_loadu_pd(&b_c[5 * i20 + 2]);
                                r10 = _mm_loadu_pd(&c_c[5 * i20 + 2]);
                                _mm_storeu_pd(&Umat[5 * i20 + 2],
                                              _mm_div_pd(_mm_add_pd(r8, r10), r11));
                                Umat[5 * i20 + 4] = (b_c[5 * i20 + 4] + c_c[5 * i20 + 4]) / 2.0;
                            }
                        } else {
                            c_binary_expand_op(Umat, b_c, c_c);
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
                        //  r1D           :   nDxn : 1rst order parametric derivative for the B
                        //  spline at u\_vec points r2D           :   nDxn : 2nd order parametric
                        //  derivative for the B spline at u\_vec points r3D           :   nDxn :
                        //  3rd order parametric derivative for the B spline at u\_vec points
                        // 'EvalBSpline:14' sp = spline.sp;
                        // 'EvalBSpline:15' N  = length( u_vec );
                        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
                        // 'EvalBSpline:18' r0D = zeros( M, N );
                        unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
                        // 'EvalBSpline:18' r1D = r0D;
                        r1D.set_size(splineCurve.sp.coeff.size(0), static_cast<int>(unnamed_idx_1));
                        f_loop_ub = static_cast<int>(unnamed_idx_1);
                        for (int i21{0}; i21 < f_loop_ub; i21++) {
                            int g_loop_ub;
                            g_loop_ub = splineCurve.sp.coeff.size(0);
                            for (int i22{0}; i22 < g_loop_ub; i22++) {
                                r1D[i22 + r1D.size(0) * i21] = 0.0;
                            }
                        }
                        // 'EvalBSpline:18' r2D = r1D;
                        // 'EvalBSpline:18' r3D = r2D;
                        // 'EvalBSpline:20' for j = 1 : M
                        i23 = splineCurve.sp.coeff.size(0);
                        for (int j{0}; j < i23; j++) {
                            int h_loop_ub;
                            int i32;
                            int i_loop_ub;
                            int l_loop_ub;
                            int m_loop_ub;
                            int o_loop_ub;
                            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j ,
                            // : ) ] = ... 'EvalBSpline:22' bspline_eval_vec( sp.Bl, sp.coeff( j, :
                            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                            h_loop_ub = 5 * Umat.size(1);
                            r12.set_size(1, 5 * Umat.size(1));
                            for (int i24{0}; i24 < h_loop_ub; i24++) {
                                r12[i24] = 0.0;
                            }
                            // 'bspline_eval_vec:4' xd      = zeros(size(u));
                            i_loop_ub = 5 * Umat.size(1);
                            r14.set_size(1, 5 * Umat.size(1));
                            for (int i26{0}; i26 < i_loop_ub; i26++) {
                                r14[i26] = 0.0;
                            }
                            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                            l_loop_ub = 5 * Umat.size(1);
                            r15.set_size(1, 5 * Umat.size(1));
                            for (int i29{0}; i29 < l_loop_ub; i29++) {
                                r15[i29] = 0.0;
                            }
                            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                            m_loop_ub = 5 * Umat.size(1);
                            r17.set_size(1, 5 * Umat.size(1));
                            for (int i31{0}; i31 < m_loop_ub; i31++) {
                                r17[i31] = 0.0;
                            }
                            // 'bspline_eval_vec:8' for k = 1:length(u)
                            i32 = 5 * Umat.size(1);
                            if (0 <= i32 - 1) {
                                i34 = splineCurve.sp.coeff.size(1);
                                n_loop_ub = splineCurve.sp.coeff.size(1);
                            }
                            for (int f_k{0}; f_k < i32; f_k++) {
                                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl,
                                // coeffs, u(k));
                                r12[f_k] = Umat[f_k];
                                b_splineCurve.set_size(1, i34);
                                for (int i38{0}; i38 < n_loop_ub; i38++) {
                                    b_splineCurve[i38] =
                                        splineCurve.sp
                                            .coeff[j + splineCurve.sp.coeff.size(0) * i38];
                                }
                                bspline_eval(splineCurve.sp.Bl.handle, b_splineCurve, &r12[f_k],
                                             &d2, &d3, &d4);
                                r17[f_k] = d4;
                                r15[f_k] = d3;
                                r14[f_k] = d2;
                                // 'bspline_eval_vec:10' x(k)    = xk;
                                // 'bspline_eval_vec:11' xd(k)   = xdk;
                                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                                // 'bspline_eval_vec:13' xddd(k) = xdddk;
                            }
                            o_loop_ub = r14.size(1);
                            for (int i37{0}; i37 < o_loop_ub; i37++) {
                                r1D[j + r1D.size(0) * i37] = r14[i37];
                            }
                        }
                        // 'SplineLengthApproxGL_tot:24' r1Dnorm   = MyNorm(r1D);
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'SplineLengthApproxGL_tot:25' r1DnormM  = reshape(r1Dnorm, GL_N,
                        // length(Knots)-1); 'SplineLengthApproxGL_tot:26' Lk        =
                        // sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
                        r13.set_size(r1D.size(0), r1D.size(1));
                        j_loop_ub = r1D.size(1);
                        for (int i25{0}; i25 < j_loop_ub; i25++) {
                            int k_loop_ub;
                            k_loop_ub = r1D.size(0);
                            for (int i28{0}; i28 < k_loop_ub; i28++) {
                                double c_varargin_1;
                                c_varargin_1 = r1D[i28 + r1D.size(0) * i25];
                                r13[i28 + r13.size(0) * i25] = std::pow(c_varargin_1, 2.0);
                            }
                        }
                        coder::sum(r13, x);
                        i27 = x.size(1);
                        scalarLB = (x.size(1) / 2) << 1;
                        vectorUB = scalarLB - 2;
                        for (e_k = 0; e_k <= vectorUB; e_k += 2) {
                            __m128d r16;
                            r16 = _mm_loadu_pd(&x[e_k]);
                            _mm_storeu_pd(&x[e_k], _mm_sqrt_pd(r16));
                        }
                        for (e_k = scalarLB; e_k < i27; e_k++) {
                            x[e_k] = std::sqrt(x[e_k]);
                        }
                        i30 = (i12 - i11) - 1;
                        b_c.set_size(5, (i12 - i11) - 1);
                        if (i30 != 0) {
                            int bcoef;
                            int i33;
                            bcoef = ((i12 - i11) - 1 != 1);
                            i33 = i30 - 1;
                            if (0 <= b_c.size(1) - 1) {
                                b_bcoef = (static_cast<int>(ctx->cfg.GaussLegendreN) != 1);
                                ctx_idx_0 = static_cast<int>(ctx->cfg.GaussLegendreN);
                            }
                            for (int h_k{0}; h_k <= i33; h_k++) {
                                int varargin_3;
                                varargin_3 = bcoef * h_k;
                                for (int i_k{0}; i_k < 5; i_k++) {
                                    b_c[i_k + 5 * h_k] = ctx->cfg.GaussLegendreW[i_k] *
                                                         x[b_bcoef * i_k + ctx_idx_0 * varargin_3];
                                }
                            }
                        }
                        if (b_c.size(1) == 0) {
                            y.set_size(1, 0);
                        } else {
                            int i35;
                            y.set_size(1, b_c.size(1));
                            i35 = b_c.size(1);
                            for (int g_k{0}; g_k < i35; g_k++) {
                                y[g_k] = b_c[5 * g_k];
                                y[g_k] = y[g_k] + b_c[5 * g_k + 1];
                                y[g_k] = y[g_k] + b_c[5 * g_k + 2];
                                y[g_k] = y[g_k] + b_c[5 * g_k + 3];
                                y[g_k] = y[g_k] + b_c[5 * g_k + 4];
                            }
                        }
                        if (i16 - i15 == 1) {
                            i36 = i14;
                        } else {
                            i36 = i16 - i15;
                        }
                        if ((i18 == i14) && (y.size(1) == i36)) {
                            int b_scalarLB;
                            int b_vectorUB;
                            int i39;
                            int p_loop_ub;
                            splineCurve.sp.Lk.set_size(1, y.size(1));
                            p_loop_ub = y.size(1);
                            b_scalarLB = (y.size(1) / 2) << 1;
                            b_vectorUB = b_scalarLB - 2;
                            for (i39 = 0; i39 <= b_vectorUB; i39 += 2) {
                                __m128d r18;
                                __m128d r19;
                                __m128d r20;
                                r18 = _mm_loadu_pd(&splineCurve.sp.knots[((i11 + i15) + i39) + 2]);
                                r19 = _mm_loadu_pd(&splineCurve.sp.knots[(i11 + i39) + 1]);
                                r20 = _mm_loadu_pd(&y[i39]);
                                _mm_storeu_pd(&splineCurve.sp.Lk[i39],
                                              _mm_div_pd(_mm_mul_pd(r20, _mm_sub_pd(r18, r19)),
                                                         _mm_set1_pd(2.0)));
                            }
                            for (i39 = b_scalarLB; i39 < p_loop_ub; i39++) {
                                splineCurve.sp.Lk[i39] =
                                    y[i39] *
                                    (splineCurve.sp.knots[((i11 + i15) + i39) + 2] -
                                     splineCurve.sp.knots[(i11 + i39) + 1]) /
                                    2.0;
                            }
                        } else {
                            binary_expand_op(&splineCurve, y, i11 + 1, i15 + 1, i16, i14 - 1);
                        }
                        //  Gauss Legendre integration
                        // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
                        splineCurve.sp.Ltot = coder::sum(splineCurve.sp.Lk);
                        // 'compressCurvStructs:82' splineCurve.sp.Ltot     = Ltot;
                        // 'compressCurvStructs:83' splineCurve.sp.Lk       = Lk;
                        // 'compressCurvStructs:85' spline = constrSplineStruct( curve.Info,
                        // pvec(:,1), ... 'compressCurvStructs:86'                     pvec(:,end),
                        // uint32( spline_index ) );
                        c_pvec = pvec.size(1);
                        for (int i40{0}; i40 < 6; i40++) {
                            dv[i40] = (*(double(*)[6]) & pvec[0])[i40];
                        }
                        for (int i41{0}; i41 < 6; i41++) {
                            dv1[i41] = (*(double(*)[6]) & pvec[6 * (c_pvec - 1)])[i41];
                        }
                        constrSplineStruct(curve.Info.zspdmode, curve.Info.TRAFO, curve.Info.HSC,
                                           curve.Info.FeedRate, curve.Info.SpindleSpeed,
                                           curve.Info.gcode_source_line, curve.Info.G91,
                                           curve.Info.G91_1, dv, dv1, spline_index, &spline);
                        //  Calculate the ZSpdMode for the spline
                        // 'compressCurvStructs:89' first   = zspdmodevec( 1 );
                        // 'compressCurvStructs:90' last    = zspdmodevec( end );
                        // 'compressCurvStructs:92' if ( first == ZSpdMode.NN ) && ( last ==
                        // ZSpdMode.NN )
                        if ((zspdmodevec_idx_0 == ZSpdMode_NN) &&
                            (zspdmodevec_idx_1 == ZSpdMode_NN)) {
                            // 'compressCurvStructs:93' spline.Info.zspdmode = ZSpdMode.NN;
                            spline.Info.zspdmode = ZSpdMode_NN;
                        } else if ((zspdmodevec_idx_0 == ZSpdMode_NN) &&
                                   (zspdmodevec_idx_1 == ZSpdMode_NZ)) {
                            // 'compressCurvStructs:94' elseif  ( first == ZSpdMode.NN ) && ( last
                            // == ZSpdMode.NZ ) 'compressCurvStructs:95' spline.Info.zspdmode =
                            // ZSpdMode.NZ;
                            spline.Info.zspdmode = ZSpdMode_NZ;
                        } else if ((zspdmodevec_idx_0 == ZSpdMode_ZN) &&
                                   (zspdmodevec_idx_1 == ZSpdMode_NN)) {
                            // 'compressCurvStructs:96' elseif  ( first == ZSpdMode.ZN ) && ( last
                            // == ZSpdMode.NN ) 'compressCurvStructs:97' spline.Info.zspdmode =
                            // ZSpdMode.ZN;
                            spline.Info.zspdmode = ZSpdMode_ZN;
                        } else if ((zspdmodevec_idx_0 == ZSpdMode_ZN) &&
                                   (zspdmodevec_idx_1 == ZSpdMode_NZ)) {
                            // 'compressCurvStructs:98' elseif ( first == ZSpdMode.ZN ) && ( last ==
                            // ZSpdMode.NZ ) 'compressCurvStructs:99' spline.Info.zspdmode =
                            // ZSpdMode.ZZ;
                            spline.Info.zspdmode = ZSpdMode_ZZ;
                        } else {
                            // 'compressCurvStructs:100' else
                            // 'compressCurvStructs:101' fprintf('ERROR IN ZSPDMODE');
                            printf("ERROR IN ZSPDMODE");
                            fflush(stdout);
                        }
                        // 'compressCurvStructs:104' ctx.q_spline.push( splineCurve );
                        ctx->q_spline.push(&splineCurve);
                        // 'compressCurvStructs:105' ctx.q_compress.push( spline );
                        ctx->q_compress.push(&spline);
                        // 'compressCurvStructs:107' spline_index = spline_index + 1;
                        spline_index++;
                        //  With only two points, construct a line
                    } else {
                        // 'compressCurvStructs:110' else
                        // 'compressCurvStructs:111' ctx.q_compress.push( preCurve );
                        ctx->q_compress.push(&preCurve);
                        //  push segment to q_compress
                        // 'compressCurvStructs:112' ctx.q_compress.push( curve );
                        ctx->q_compress.push(&curve);
                        //  push segment to q_compress
                    }
                    // 'compressCurvStructs:114' CumulatedLength = 0;
                    CumulatedLength = 0.0;
                }
                //  In the general case with an elligible segment, add it to the
                //  compression list
            } else {
                int i3;
                // 'compressCurvStructs:118' else
                // 'compressCurvStructs:119' if CumulatedLength == 0
                if (CumulatedLength == 0.0) {
                    // 'compressCurvStructs:120' pvec    = curve.R0;
                    pvec.set_size(6, 1);
                    for (int i2{0}; i2 < 6; i2++) {
                        pvec[i2] = curve.R0[i2];
                    }
                    // 'compressCurvStructs:121' spindle_speed   = curve.Info.SpindleSpeed;
                    // 'compressCurvStructs:122' zspdmodevec( 1 )= curve.Info.zspdmode;
                    zspdmodevec_idx_0 = curve.Info.zspdmode;
                }
                // 'compressCurvStructs:125' CumulatedLength = CumulatedLength + LengthCurv( ctx,
                // curve, 0, 1 );
                CumulatedLength += LengthCurv(
                    &ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                    ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                    ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                    ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, CurveType_Line, curve.R0,
                    curve.R1, curve.CorrectedHelixCenter, curve.evec, curve.theta, curve.pitch,
                    curve.CoeffP5, curve.sp_index, curve.a_param, curve.b_param);
                // 'compressCurvStructs:126' pvec    = [pvec curve.R1];
                i3 = pvec.size(1);
                pvec.set_size(6, pvec.size(1) + 1);
                for (int i4{0}; i4 < 6; i4++) {
                    pvec[i4 + 6 * i3] = curve.R1[i4];
                }
                // 'compressCurvStructs:127' zspdmodevec( end ) = curve.Info.zspdmode;
                zspdmodevec_idx_1 = curve.Info.zspdmode;
                // 'compressCurvStructs:128' spindle_speed = min( spindle_speed,
                // curve.Info.SpindleSpeed );
            }
        }
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs.cpp
//
// [EOF]
//
