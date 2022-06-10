//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
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
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "opencn_matlab_types31.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
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
    static const uint64m_T r1{
        {128U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
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
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> r9;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r4;
    ::coder::array<double, 1U> r5;
    CurvStruct curve;
    CurvStruct preCurve;
    CurvStruct spline;
    CurvStruct splineCurve;
    uint64m_T params_spline_Bl_handle;
    uint64m_T r;
    uint64m_T r2;
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
    double params_spline_Ltot;
    int b_bcoef;
    int ctx_idx_0;
    int i38;
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
        Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
        MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                     (unsigned int *)&r2.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U])) {
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
                    r4.set_size(V0.size(0));
                    loop_ub = V0.size(0);
                    for (int i5{0}; i5 < loop_ub; i5++) {
                        double varargin_1;
                        varargin_1 = V0[i5];
                        r4[i5] = std::pow(varargin_1, 2.0);
                    }
                    r5.set_size(V1.size(0));
                    b_loop_ub = V1.size(0);
                    for (int i6{0}; i6 < b_loop_ub; i6++) {
                        double b_varargin_1;
                        b_varargin_1 = V1[i6];
                        r5[i6] = std::pow(b_varargin_1, 2.0);
                    }
                    Collinear = (c / (std::sqrt(coder::combineVectorElements(r4)) *
                                      std::sqrt(coder::combineVectorElements(r5))) >
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
                        int c_loop_ub;
                        int c_pvec;
                        int f_loop_ub;
                        int i11;
                        int i12;
                        int i13;
                        int i14;
                        int i15;
                        int i16;
                        int i18;
                        int i25;
                        int i29;
                        int i32;
                        int i37;
                        int j_loop_ub;
                        unsigned int unnamed_idx_1;
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
                        for (int b_i{0}; b_i < 5; b_i++) {
                            b[b_i] = 1.0 - ctx->cfg.GaussLegendreX[b_i];
                        }
                        b_c.set_size(5, i14);
                        if (i14 != 0) {
                            int acoef;
                            int i17;
                            acoef = (i14 != 1);
                            i17 = i14 - 1;
                            for (int c_k{0}; c_k <= i17; c_k++) {
                                int varargin_2;
                                varargin_2 = acoef * c_k;
                                for (int d_k{0}; d_k < 5; d_k++) {
                                    b_c[d_k + 5 * c_k] =
                                        splineCurve.sp.knots[(i11 + varargin_2) + 1] * b[d_k];
                                }
                            }
                        }
                        for (int c_i{0}; c_i < 5; c_i++) {
                            b[c_i] = ctx->cfg.GaussLegendreX[c_i] + 1.0;
                        }
                        i18 = i16 - i15;
                        c_c.set_size(5, i18);
                        if (i18 != 0) {
                            int b_acoef;
                            int i19;
                            b_acoef = (i18 != 1);
                            i19 = i18 - 1;
                            for (int e_k{0}; e_k <= i19; e_k++) {
                                int i21;
                                i21 = (i15 + b_acoef * e_k) + 1;
                                for (int f_k{0}; f_k < 5; f_k++) {
                                    c_c[f_k + 5 * e_k] =
                                        splineCurve.sp.knots[(i11 + i21) + 1] * b[f_k];
                                }
                            }
                        }
                        if (b_c.size(1) == c_c.size(1)) {
                            int e_loop_ub;
                            Umat.set_size(5, b_c.size(1));
                            e_loop_ub = b_c.size(1);
                            for (int i20{0}; i20 < e_loop_ub; i20++) {
                                for (int i22{0}; i22 < 5; i22++) {
                                    Umat[i22 + 5 * i20] =
                                        (b_c[i22 + 5 * i20] + c_c[i22 + 5 * i20]) / 2.0;
                                }
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
                        for (int i23{0}; i23 < f_loop_ub; i23++) {
                            int g_loop_ub;
                            g_loop_ub = splineCurve.sp.coeff.size(0);
                            for (int i24{0}; i24 < g_loop_ub; i24++) {
                                r1D[i24 + r1D.size(0) * i23] = 0.0;
                            }
                        }
                        // 'EvalBSpline:18' r2D = r1D;
                        // 'EvalBSpline:18' r3D = r2D;
                        // 'EvalBSpline:20' for j = 1 : M
                        i25 = splineCurve.sp.coeff.size(0);
                        for (int j{0}; j < i25; j++) {
                            int h_loop_ub;
                            int i36;
                            int i_loop_ub;
                            int l_loop_ub;
                            int m_loop_ub;
                            int p_loop_ub;
                            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j ,
                            // : ) ] = ... 'EvalBSpline:22' bspline_eval_vec( sp.Bl, sp.coeff( j, :
                            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                            h_loop_ub = 5 * Umat.size(1);
                            r6.set_size(1, 5 * Umat.size(1));
                            for (int i26{0}; i26 < h_loop_ub; i26++) {
                                r6[i26] = 0.0;
                            }
                            // 'bspline_eval_vec:4' xd      = zeros(size(u));
                            i_loop_ub = 5 * Umat.size(1);
                            r8.set_size(1, 5 * Umat.size(1));
                            for (int i28{0}; i28 < i_loop_ub; i28++) {
                                r8[i28] = 0.0;
                            }
                            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                            l_loop_ub = 5 * Umat.size(1);
                            r9.set_size(1, 5 * Umat.size(1));
                            for (int i31{0}; i31 < l_loop_ub; i31++) {
                                r9[i31] = 0.0;
                            }
                            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                            m_loop_ub = 5 * Umat.size(1);
                            r10.set_size(1, 5 * Umat.size(1));
                            for (int i34{0}; i34 < m_loop_ub; i34++) {
                                r10[i34] = 0.0;
                            }
                            // 'bspline_eval_vec:8' for k = 1:length(u)
                            i36 = 5 * Umat.size(1);
                            if (0 <= i36 - 1) {
                                i38 = splineCurve.sp.coeff.size(1);
                                n_loop_ub = splineCurve.sp.coeff.size(1);
                            }
                            for (int k_k{0}; k_k < i36; k_k++) {
                                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl,
                                // coeffs, u(k));
                                r6[k_k] = Umat[k_k];
                                b_splineCurve.set_size(1, i38);
                                for (int i41{0}; i41 < n_loop_ub; i41++) {
                                    b_splineCurve[i41] =
                                        splineCurve.sp
                                            .coeff[j + splineCurve.sp.coeff.size(0) * i41];
                                }
                                bspline_eval(splineCurve.sp.Bl.handle, b_splineCurve, &r6[k_k], &d,
                                             &d1, &d2);
                                r10[k_k] = d2;
                                r9[k_k] = d1;
                                r8[k_k] = d;
                                // 'bspline_eval_vec:10' x(k)    = xk;
                                // 'bspline_eval_vec:11' xd(k)   = xdk;
                                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                                // 'bspline_eval_vec:13' xddd(k) = xdddk;
                            }
                            p_loop_ub = r8.size(1);
                            for (int i40{0}; i40 < p_loop_ub; i40++) {
                                r1D[j + r1D.size(0) * i40] = r8[i40];
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
                        r7.set_size(r1D.size(0), r1D.size(1));
                        j_loop_ub = r1D.size(1);
                        for (int i27{0}; i27 < j_loop_ub; i27++) {
                            int k_loop_ub;
                            k_loop_ub = r1D.size(0);
                            for (int i30{0}; i30 < k_loop_ub; i30++) {
                                double c_varargin_1;
                                c_varargin_1 = r1D[i30 + r1D.size(0) * i27];
                                r7[i30 + r7.size(0) * i27] = std::pow(c_varargin_1, 2.0);
                            }
                        }
                        coder::sum(r7, x);
                        i29 = x.size(1);
                        for (int g_k{0}; g_k < i29; g_k++) {
                            x[g_k] = std::sqrt(x[g_k]);
                        }
                        i32 = (i12 - i11) - 1;
                        b_c.set_size(5, (i12 - i11) - 1);
                        if (i32 != 0) {
                            int bcoef;
                            int i33;
                            bcoef = ((i12 - i11) - 1 != 1);
                            i33 = i32 - 1;
                            if (0 <= b_c.size(1) - 1) {
                                b_bcoef = (static_cast<int>(ctx->cfg.GaussLegendreN) != 1);
                                ctx_idx_0 = static_cast<int>(ctx->cfg.GaussLegendreN);
                            }
                            for (int i_k{0}; i_k <= i33; i_k++) {
                                int varargin_3;
                                varargin_3 = bcoef * i_k;
                                for (int j_k{0}; j_k < 5; j_k++) {
                                    b_c[j_k + 5 * i_k] = ctx->cfg.GaussLegendreW[j_k] *
                                                         x[b_bcoef * j_k + ctx_idx_0 * varargin_3];
                                }
                            }
                        }
                        if (b_c.size(1) == 0) {
                            y.set_size(1, 0);
                        } else {
                            int i35;
                            y.set_size(1, b_c.size(1));
                            i35 = b_c.size(1);
                            for (int h_k{0}; h_k < i35; h_k++) {
                                y[h_k] = b_c[5 * h_k];
                                y[h_k] = y[h_k] + b_c[5 * h_k + 1];
                                y[h_k] = y[h_k] + b_c[5 * h_k + 2];
                                y[h_k] = y[h_k] + b_c[5 * h_k + 3];
                                y[h_k] = y[h_k] + b_c[5 * h_k + 4];
                            }
                        }
                        if (i16 - i15 == 1) {
                            i37 = i14;
                        } else {
                            i37 = i16 - i15;
                        }
                        if ((i18 == i14) && (y.size(1) == i37)) {
                            int o_loop_ub;
                            splineCurve.sp.Lk.set_size(1, y.size(1));
                            o_loop_ub = y.size(1);
                            for (int i39{0}; i39 < o_loop_ub; i39++) {
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
                        for (int i42{0}; i42 < 6; i42++) {
                            dv[i42] = (*(double(*)[6]) & pvec[0])[i42];
                        }
                        for (int i43{0}; i43 < 6; i43++) {
                            dv1[i43] = (*(double(*)[6]) & pvec[6 * (c_pvec - 1)])[i43];
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
