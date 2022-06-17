//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs_new.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
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
namespace ocn {
void compressCurvStructs_new(const b_FeedoptContext *ctx)
{
    static const uint64m_T r1{
        {128U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> b_batch_pvec;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> batch_pvec;
    ::coder::array<double, 2U> c_c;
    ::coder::array<double, 2U> params_tmp_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_tmp_spline_Lk;
    ::coder::array<double, 2U> params_tmp_spline_coeff;
    ::coder::array<double, 2U> params_tmp_spline_knots;
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
    CurvStruct C_tmp;
    CurvStruct batch_curvArray_idx_0;
    CurvStruct curv;
    CurvStruct curvCompressed;
    CurvStruct prevCurv;
    CurvStruct spline;
    uint64m_T params_tmp_spline_Bl_handle;
    uint64m_T r;
    uint64m_T r2;
    double dv[6];
    double dv1[6];
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double b[5];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d;
    double d1;
    double d2;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_spline_Ltot;
    int b_bcoef;
    int ctx_idx_0;
    int i36;
    int m_loop_ub;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_spline_Bl_ncoeff;
    int params_tmp_spline_Bl_order;
    signed char tmp_data[6];
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    CurveType params_tmp_gcodeInfoStruct_Type;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs_new:14' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        CurvStruct batch_curvArray_idx_1;
        double batch_size;
        unsigned int Ncrv;
        int i1;
        unsigned int spline_index;
        // 'compressCurvStructs_new:16' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs_new:17' Ncrv                = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        // 'compressCurvStructs_new:18' [ batch ]           = batch_init();
        // 'compressCurvStructs_new:96' batch = struct( ...
        // 'compressCurvStructs_new:97'     'pvec',          zeros( StructTypeName.NumberAxisMax, 1
        // ),... 'compressCurvStructs_new:98'     'curvArray',     repmat( constrCurvStructType, 1,
        // 2 ),... 'compressCurvStructs_new:99'     'spindle_speed', 0,...
        // 'compressCurvStructs_new:100'     'feedrate',      0,...
        // 'compressCurvStructs_new:101'     'size',          0 ...
        // 'compressCurvStructs_new:102'     );
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(
            &params_tmp_gcodeInfoStruct_Type, &params_tmp_gcodeInfoStruct_zspdmode,
            &params_tmp_gcodeInfoStruct_TRAFO, &params_tmp_gcodeInfoStruct_HSC,
            &params_tmp_gcodeInfoStruct_FeedRate, &params_tmp_gcodeInfoStruct_SpindleSpeed,
            &params_tmp_gcodeInfoStruct_gcode_source_line, &params_tmp_gcodeInfoStruct_G91,
            &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_spline_Bl_ncoeff,
            params_tmp_spline_Bl_breakpoints, &params_tmp_spline_Bl_handle,
            &params_tmp_spline_Bl_order, params_tmp_spline_coeff, params_tmp_spline_knots,
            &params_tmp_spline_Ltot, params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1,
            params_tmp_Cprim, &expl_temp, params_tmp_evec, &b_expl_temp, &c_expl_temp,
            params_tmp_CoeffP5, &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline,
        // ... 'constrCurvStructType:14'         params.R0, params.R1, ... 'constrCurvStructType:15'
        // params.Cprim, params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
        // params.pitch, params.CoeffP5, params.Coeff );
        b_constrCurvStruct(
            params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
            params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
            params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
            params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
            params_tmp_gcodeInfoStruct_G91_1, params_tmp_spline_Bl_ncoeff,
            params_tmp_spline_Bl_breakpoints, params_tmp_spline_Bl_handle,
            params_tmp_spline_Bl_order, params_tmp_spline_coeff, params_tmp_spline_knots,
            params_tmp_spline_Ltot, params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1,
            params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &C_tmp);
        batch_pvec.set_size(6, 1);
        for (int i{0}; i < 6; i++) {
            batch_pvec[i] = 0.0;
        }
        batch_curvArray_idx_0 = C_tmp;
        batch_curvArray_idx_1 = C_tmp;
        batch_size = 0.0;
        // 'compressCurvStructs_new:104' if( ~coder.target( "MATLAB" ) )
        // 'compressCurvStructs_new:105' coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
        // 'compressCurvStructs_new:20' DebugLog(DebugCfg.Validate, 'Compressing...\n');
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
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'compressCurvStructs_new:22' for k = 1 : Ncrv
        i1 = static_cast<int>(Ncrv);
        for (int k{0}; k < i1; k++) {
            bool addBatch;
            bool closeBatch;
            // 'compressCurvStructs_new:23' curv = ctx.q_gcode.get( k );
            ctx->q_gcode.get(k + 1U, &curv);
            //  Get next Curve in the queue
            // 'compressCurvStructs_new:25' [ addBatch ]    = check_add_batch( ctx, curv, batch );
            // 'compressCurvStructs_new:58' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs_new:60' addBatch = true;
            addBatch = true;
            // 'compressCurvStructs_new:62' if( curv.Info.Type ~= CurveType.Line )
            if (curv.Info.Type != CurveType_Line) {
                // 'compressCurvStructs_new:63' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs_new:67' if( LengthCurv( ctx, curv, 0, 1 ) >
                // ctx.cfg.LThreshold )
            } else if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  curv.Info, curv.R0, curv.R1, curv.CorrectedHelixCenter, curv.evec,
                                  curv.theta, curv.pitch, curv.CoeffP5, curv.sp_index, curv.a_param,
                                  curv.b_param) > ctx->cfg.LThreshold) {
                // 'compressCurvStructs_new:68' addBatch = false;
                addBatch = false;

                // 'compressCurvStructs_new:71' if( batch.size > 0 )
            } else if (batch_size > 0.0) {
                bool collinear;
                // 'compressCurvStructs_new:72' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    // 'compressCurvStructs_new:73' prevCurv = batch.curvArray( end );
                    prevCurv = batch_curvArray_idx_1;
                } else {
                    // 'compressCurvStructs_new:74' else
                    // 'compressCurvStructs_new:75' prevCurv = batch.curvArray( 1 );
                    prevCurv = batch_curvArray_idx_0;
                }
                // 'compressCurvStructs_new:77' collinear = curvCollinear( ctx, prevCurv, curv, ...
                // 'compressCurvStructs_new:78'         ctx.cfg.Compressing.ColTolCosLee );
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
                    collinear = (c / (std::sqrt(coder::combineVectorElements(r4)) *
                                      std::sqrt(coder::combineVectorElements(r5))) >
                                 ctx->cfg.Compressing.ColTolCosLee);
                }
                // 'compressCurvStructs_new:79' if( ~collinear )
                if (!collinear) {
                    // 'compressCurvStructs_new:79' addBatch = false;
                    addBatch = false;
                }
            }
            // 'compressCurvStructs_new:26' [ closeBatch ]  = check_close_batch( curv, addBatch );
            // 'compressCurvStructs_new:85' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs_new:87' closeBatch = false;
            closeBatch = false;
            // 'compressCurvStructs_new:89' if( ~addBatch )
            if (!addBatch) {
                // 'compressCurvStructs_new:89' closeBatch = true;
                closeBatch = true;

                // 'compressCurvStructs_new:91' if( isAZeroEnd( curv ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            } else if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'compressCurvStructs_new:91' closeBatch = true;
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
                    // 'compressCurvStructs_new:118' batch.pvec             = [ batch.pvec, curv.R1
                    // ];
                    i2 = batch_pvec.size(1);
                    batch_pvec.set_size(6, batch_pvec.size(1) + 1);
                    for (int i3{0}; i3 < 6; i3++) {
                        batch_pvec[i3 + 6 * i2] = curv.R1[i3];
                    }
                    // 'compressCurvStructs_new:119' batch.curvArray( end ) = curv;
                    batch_curvArray_idx_1 = curv;
                    // 'compressCurvStructs_new:120' batch.spindle_speed    = min(
                    // batch.spindle_speed , curv.Info.SpindleSpeed ); 'compressCurvStructs_new:121'
                    // batch.feedrate         = min( batch.feedrate, curv.Info.FeedRate );
                    // 'compressCurvStructs_new:122' batch.size             = batch.size + 1;
                    batch_size++;
                } else {
                    // 'compressCurvStructs_new:31' else
                    // 'compressCurvStructs_new:32' [ batch ] = batch_reset( ctx, curv );
                    // 'compressCurvStructs_new:110' batch.pvec            = curv.R0;
                    // 'compressCurvStructs_new:111' batch.curvArray       = [ curv, curv ];
                    // 'compressCurvStructs_new:112' batch.spindle_speed   = ctx.cfg.smax;
                    // 'compressCurvStructs_new:113' batch.feedrate        = ctx.cfg.fmax;
                    // 'compressCurvStructs_new:114' batch.size            = 1;
                    batch_pvec.set_size(6, 1);
                    for (int i4{0}; i4 < 6; i4++) {
                        batch_pvec[i4] = curv.R0[i4];
                    }
                    batch_curvArray_idx_0 = curv;
                    batch_curvArray_idx_1 = curv;
                    batch_size = 1.0;
                }
            }
            // 'compressCurvStructs_new:36' if( closeBatch )
            if (closeBatch) {
                // 'compressCurvStructs_new:37' if( batch.size > 1 )
                if (batch_size > 1.0) {
                    int c_batch_pvec;
                    int c_loop_ub;
                    int e_loop_ub;
                    int end;
                    int i10;
                    int i11;
                    int i12;
                    int i13;
                    int i14;
                    int i16;
                    int i23;
                    int i27;
                    int i30;
                    int i35;
                    int i9;
                    int i_loop_ub;
                    int partialTrueCount;
                    int trueCount;
                    unsigned int unnamed_idx_1;
                    bool b_b;
                    // 'compressCurvStructs_new:38' [ curvCompressed, spline, spline_index ] = ...
                    // 'compressCurvStructs_new:39'             create_spline( ctx, batch,
                    // spline_index ); 'compressCurvStructs_new:126' spline            =
                    // constrCurvStructType;
                    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                    // 'constrCurvStructType:4' if( nargin > 0 )
                    // 'constrCurvStructType:6' else
                    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                    // 'constrCurvStructType:12' else
                    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                    // params.spline, ... 'constrCurvStructType:14'         params.R0, params.R1,
                    // ... 'constrCurvStructType:15'         params.Cprim, params.delta,
                    // params.evec, params.theta, ... 'constrCurvStructType:16' params.pitch,
                    // params.CoeffP5, params.Coeff );
                    spline = C_tmp;
                    // 'compressCurvStructs_new:127' spline.Info.Type  = CurveType.Spline;
                    spline.Info.Type = CurveType_Spline;
                    // 'compressCurvStructs_new:128' spline.sp_index   = spline_index;
                    spline.sp_index = spline_index;
                    // 'compressCurvStructs_new:129' spline.sp         = CalcBspline_Lee( ctx.cfg,
                    // batch.pvec( ctx.cfg.maskTot, : ) );
                    end = ctx->cfg.maskTot.size[1] - 1;
                    trueCount = 0;
                    for (int b_i{0}; b_i <= end; b_i++) {
                        if (ctx->cfg.maskTot.data[b_i]) {
                            trueCount++;
                        }
                    }
                    partialTrueCount = 0;
                    for (int c_i{0}; c_i <= end; c_i++) {
                        if (ctx->cfg.maskTot.data[c_i]) {
                            tmp_data[partialTrueCount] = static_cast<signed char>(c_i + 1);
                            partialTrueCount++;
                        }
                    }
                    c_loop_ub = batch_pvec.size(1);
                    b_batch_pvec.set_size(trueCount, batch_pvec.size(1));
                    for (int i7{0}; i7 < c_loop_ub; i7++) {
                        for (int i8{0}; i8 < trueCount; i8++) {
                            b_batch_pvec[i8 + b_batch_pvec.size(0) * i7] =
                                batch_pvec[(tmp_data[i8] + 6 * i7) - 1];
                        }
                    }
                    CalcBspline_Lee(ctx->cfg.NumberAxis, ctx->cfg.LeeSplineDegree, b_batch_pvec,
                                    &spline.sp.Bl.ncoeff, spline.sp.Bl.breakpoints,
                                    &spline.sp.Bl.handle, &spline.sp.Bl.order, spline.sp.coeff,
                                    spline.sp.knots, &spline.sp.Ltot, spline.sp.Lk);
                    // 'compressCurvStructs_new:130' [ Ltot, Lk ]      = SplineLengthApproxGL_tot(
                    // ctx, spline );
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
                    if (4 > spline.sp.knots.size(1) - 3) {
                        i9 = -1;
                        i10 = -1;
                    } else {
                        i9 = 2;
                        i10 = spline.sp.knots.size(1) - 4;
                    }
                    //  eliminate multiplicities at the end points
                    // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
                    i11 = i10 - i9;
                    if (1 > i11 - 1) {
                        i12 = 0;
                    } else {
                        i12 = (i10 - i9) - 1;
                    }
                    //  lower integration limits
                    // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
                    if (2 > i11) {
                        i13 = -1;
                        i14 = -1;
                    } else {
                        i13 = 0;
                        i14 = (i10 - i9) - 1;
                    }
                    //  upper integration limits
                    //  get Gauss-Legendre knots and weights
                    // 'SplineLengthApproxGL_tot:16' GL_N   = ctx.cfg.GaussLegendreN;
                    // 'SplineLengthApproxGL_tot:17' GL_X   = ctx.cfg.GaussLegendreX;
                    // 'SplineLengthApproxGL_tot:18' GL_W   = ctx.cfg.GaussLegendreW;
                    //  apply linear map from[-1, 1] to [a, b]
                    // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) +
                    // bsxfun(@times, b, (1+GL_X)))/2;
                    for (int d_i{0}; d_i < 5; d_i++) {
                        b[d_i] = 1.0 - ctx->cfg.GaussLegendreX[d_i];
                    }
                    b_c.set_size(5, i12);
                    if (i12 != 0) {
                        int acoef;
                        int i15;
                        acoef = (i12 != 1);
                        i15 = i12 - 1;
                        for (int c_k{0}; c_k <= i15; c_k++) {
                            int varargin_2;
                            varargin_2 = acoef * c_k;
                            for (int d_k{0}; d_k < 5; d_k++) {
                                b_c[d_k + 5 * c_k] =
                                    spline.sp.knots[(i9 + varargin_2) + 1] * b[d_k];
                            }
                        }
                    }
                    for (int e_i{0}; e_i < 5; e_i++) {
                        b[e_i] = ctx->cfg.GaussLegendreX[e_i] + 1.0;
                    }
                    i16 = i14 - i13;
                    c_c.set_size(5, i16);
                    if (i16 != 0) {
                        int b_acoef;
                        int i17;
                        b_acoef = (i16 != 1);
                        i17 = i16 - 1;
                        for (int e_k{0}; e_k <= i17; e_k++) {
                            int i19;
                            i19 = (i13 + b_acoef * e_k) + 1;
                            for (int f_k{0}; f_k < 5; f_k++) {
                                c_c[f_k + 5 * e_k] = spline.sp.knots[(i9 + i19) + 1] * b[f_k];
                            }
                        }
                    }
                    if (b_c.size(1) == c_c.size(1)) {
                        int d_loop_ub;
                        Umat.set_size(5, b_c.size(1));
                        d_loop_ub = b_c.size(1);
                        for (int i18{0}; i18 < d_loop_ub; i18++) {
                            for (int i20{0}; i20 < 5; i20++) {
                                Umat[i20 + 5 * i18] =
                                    (b_c[i20 + 5 * i18] + c_c[i20 + 5 * i18]) / 2.0;
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
                    //  r1D           :   nDxn : 1rst order parametric derivative for the B spline
                    //  at u\_vec points r2D           :   nDxn : 2nd order parametric derivative
                    //  for the B spline at u\_vec points r3D           :   nDxn : 3rd order
                    //  parametric derivative for the B spline at u\_vec points
                    // 'EvalBSpline:14' sp = spline.sp;
                    // 'EvalBSpline:15' N  = length( u_vec );
                    // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
                    // 'EvalBSpline:18' r0D = zeros( M, N );
                    unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
                    // 'EvalBSpline:18' r1D = r0D;
                    r1D.set_size(spline.sp.coeff.size(0), static_cast<int>(unnamed_idx_1));
                    e_loop_ub = static_cast<int>(unnamed_idx_1);
                    for (int i21{0}; i21 < e_loop_ub; i21++) {
                        int f_loop_ub;
                        f_loop_ub = spline.sp.coeff.size(0);
                        for (int i22{0}; i22 < f_loop_ub; i22++) {
                            r1D[i22 + r1D.size(0) * i21] = 0.0;
                        }
                    }
                    // 'EvalBSpline:18' r2D = r1D;
                    // 'EvalBSpline:18' r3D = r2D;
                    // 'EvalBSpline:20' for j = 1 : M
                    i23 = spline.sp.coeff.size(0);
                    for (int j{0}; j < i23; j++) {
                        int g_loop_ub;
                        int h_loop_ub;
                        int i34;
                        int k_loop_ub;
                        int l_loop_ub;
                        int o_loop_ub;
                        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : )
                        // ] = ... 'EvalBSpline:22'                             bspline_eval_vec(
                        // sp.Bl, sp.coeff( j, : ), u_vec ); 'bspline_eval_vec:3' x       =
                        // zeros(size(u));
                        g_loop_ub = 5 * Umat.size(1);
                        r6.set_size(1, 5 * Umat.size(1));
                        for (int i24{0}; i24 < g_loop_ub; i24++) {
                            r6[i24] = 0.0;
                        }
                        // 'bspline_eval_vec:4' xd      = zeros(size(u));
                        h_loop_ub = 5 * Umat.size(1);
                        r8.set_size(1, 5 * Umat.size(1));
                        for (int i26{0}; i26 < h_loop_ub; i26++) {
                            r8[i26] = 0.0;
                        }
                        // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                        k_loop_ub = 5 * Umat.size(1);
                        r9.set_size(1, 5 * Umat.size(1));
                        for (int i29{0}; i29 < k_loop_ub; i29++) {
                            r9[i29] = 0.0;
                        }
                        // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                        l_loop_ub = 5 * Umat.size(1);
                        r10.set_size(1, 5 * Umat.size(1));
                        for (int i32{0}; i32 < l_loop_ub; i32++) {
                            r10[i32] = 0.0;
                        }
                        // 'bspline_eval_vec:8' for k = 1:length(u)
                        i34 = 5 * Umat.size(1);
                        if (0 <= i34 - 1) {
                            i36 = spline.sp.coeff.size(1);
                            m_loop_ub = spline.sp.coeff.size(1);
                        }
                        for (int k_k{0}; k_k < i34; k_k++) {
                            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl,
                            // coeffs, u(k));
                            r6[k_k] = Umat[k_k];
                            b_spline.set_size(1, i36);
                            for (int i39{0}; i39 < m_loop_ub; i39++) {
                                b_spline[i39] = spline.sp.coeff[j + spline.sp.coeff.size(0) * i39];
                            }
                            bspline_eval(spline.sp.Bl.handle, b_spline, &r6[k_k], &d, &d1, &d2);
                            r10[k_k] = d2;
                            r9[k_k] = d1;
                            r8[k_k] = d;
                            // 'bspline_eval_vec:10' x(k)    = xk;
                            // 'bspline_eval_vec:11' xd(k)   = xdk;
                            // 'bspline_eval_vec:12' xdd(k)  = xddk;
                            // 'bspline_eval_vec:13' xddd(k) = xdddk;
                        }
                        o_loop_ub = r8.size(1);
                        for (int i38{0}; i38 < o_loop_ub; i38++) {
                            r1D[j + r1D.size(0) * i38] = r8[i38];
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
                    i_loop_ub = r1D.size(1);
                    for (int i25{0}; i25 < i_loop_ub; i25++) {
                        int j_loop_ub;
                        j_loop_ub = r1D.size(0);
                        for (int i28{0}; i28 < j_loop_ub; i28++) {
                            double c_varargin_1;
                            c_varargin_1 = r1D[i28 + r1D.size(0) * i25];
                            r7[i28 + r7.size(0) * i25] = std::pow(c_varargin_1, 2.0);
                        }
                    }
                    coder::sum(r7, x);
                    i27 = x.size(1);
                    for (int g_k{0}; g_k < i27; g_k++) {
                        x[g_k] = std::sqrt(x[g_k]);
                    }
                    i30 = (i10 - i9) - 1;
                    b_c.set_size(5, (i10 - i9) - 1);
                    if (i30 != 0) {
                        int bcoef;
                        int i31;
                        bcoef = ((i10 - i9) - 1 != 1);
                        i31 = i30 - 1;
                        if (0 <= b_c.size(1) - 1) {
                            b_bcoef = (static_cast<int>(ctx->cfg.GaussLegendreN) != 1);
                            ctx_idx_0 = static_cast<int>(ctx->cfg.GaussLegendreN);
                        }
                        for (int i_k{0}; i_k <= i31; i_k++) {
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
                        int i33;
                        y.set_size(1, b_c.size(1));
                        i33 = b_c.size(1);
                        for (int h_k{0}; h_k < i33; h_k++) {
                            y[h_k] = b_c[5 * h_k];
                            y[h_k] = y[h_k] + b_c[5 * h_k + 1];
                            y[h_k] = y[h_k] + b_c[5 * h_k + 2];
                            y[h_k] = y[h_k] + b_c[5 * h_k + 3];
                            y[h_k] = y[h_k] + b_c[5 * h_k + 4];
                        }
                    }
                    if (i14 - i13 == 1) {
                        i35 = i12;
                    } else {
                        i35 = i14 - i13;
                    }
                    if ((i16 == i12) && (y.size(1) == i35)) {
                        int n_loop_ub;
                        spline.sp.Lk.set_size(1, y.size(1));
                        n_loop_ub = y.size(1);
                        for (int i37{0}; i37 < n_loop_ub; i37++) {
                            spline.sp.Lk[i37] = y[i37] *
                                                (spline.sp.knots[((i9 + i13) + i37) + 2] -
                                                 spline.sp.knots[(i9 + i37) + 1]) /
                                                2.0;
                        }
                    } else {
                        binary_expand_op(&spline, y, i9 + 1, i13 + 1, i14, i12 - 1);
                    }
                    //  Gauss Legendre integration
                    // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
                    spline.sp.Ltot = coder::sum(spline.sp.Lk);
                    // 'compressCurvStructs_new:131' spline.sp.Ltot    = Ltot;
                    // 'compressCurvStructs_new:132' spline.sp.Lk      = Lk;
                    // 'compressCurvStructs_new:134' curv    = constrSplineStruct( batch.curvArray(
                    // end ).Info, batch.pvec( :, 1 ), ... 'compressCurvStructs_new:135' batch.pvec(
                    // :,end ), uint32( spline_index ) );
                    c_batch_pvec = batch_pvec.size(1);
                    for (int i40{0}; i40 < 6; i40++) {
                        dv[i40] = (*(double(*)[6]) & batch_pvec[0])[i40];
                    }
                    for (int i41{0}; i41 < 6; i41++) {
                        dv1[i41] = (*(double(*)[6]) & batch_pvec[6 * (c_batch_pvec - 1)])[i41];
                    }
                    constrSplineStruct(
                        batch_curvArray_idx_1.Info.zspdmode, batch_curvArray_idx_1.Info.TRAFO,
                        batch_curvArray_idx_1.Info.HSC, batch_curvArray_idx_1.Info.FeedRate,
                        batch_curvArray_idx_1.Info.SpindleSpeed,
                        batch_curvArray_idx_1.Info.gcode_source_line,
                        batch_curvArray_idx_1.Info.G91, batch_curvArray_idx_1.Info.G91_1, dv, dv1,
                        spline_index, &curvCompressed);
                    //  Calculate the ZSpdMode for the spline
                    // 'compressCurvStructs_new:138' first   = batch.curvArray( 1 );
                    // 'compressCurvStructs_new:139' last    = batch.curvArray( end );
                    // 'compressCurvStructs_new:141' if ( ~isAZeroSpeed( first ) ) && (
                    // ~isAZeroSpeed( last ) )
                    //  isAZeroSpeed : Return true if the curv is has a zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
                    b_b = (batch_curvArray_idx_0.Info.zspdmode != ZSpdMode_NN);
                    if ((!b_b) && (!(batch_curvArray_idx_1.Info.zspdmode != ZSpdMode_NN))) {
                        //  isAZeroSpeed : Return true if the curv is has a zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
                        // 'compressCurvStructs_new:142' curv.Info.zspdmode = ZSpdMode.NN;
                        curvCompressed.Info.zspdmode = ZSpdMode_NN;
                    } else if ((!b_b) && ((batch_curvArray_idx_1.Info.zspdmode == ZSpdMode_NZ) ||
                                          (batch_curvArray_idx_1.Info.zspdmode == ZSpdMode_ZZ))) {
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'compressCurvStructs_new:143' elseif ( ~isAZeroSpeed( first ) ) && (
                        // isAZeroEnd( last ) ) 'compressCurvStructs_new:144' curv.Info.zspdmode =
                        // ZSpdMode.NZ;
                        curvCompressed.Info.zspdmode = ZSpdMode_NZ;

                        // 'isAZeroEnd:9' zeroFlag = false;
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  curv  : The curve struct
                        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    } else if (((batch_curvArray_idx_0.Info.zspdmode == ZSpdMode_ZN) ||
                                (batch_curvArray_idx_0.Info.zspdmode == ZSpdMode_ZZ)) &&
                               (!(batch_curvArray_idx_1.Info.zspdmode != ZSpdMode_NN))) {
                        // 'isAZeroStart:6' zeroFlag = true;
                        //  isAZeroSpeed : Return true if the curv is has a zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroSpeed:5' speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
                        // 'compressCurvStructs_new:145' elseif ( isAZeroStart( first ) ) && (
                        // ~isAZeroSpeed( last ) ) 'compressCurvStructs_new:146' curv.Info.zspdmode
                        // = ZSpdMode.ZN;
                        curvCompressed.Info.zspdmode = ZSpdMode_ZN;
                    } else {
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'compressCurvStructs_new:147' else
                        // 'compressCurvStructs_new:148' curv.Info.zspdmode = ZSpdMode.ZZ;
                        curvCompressed.Info.zspdmode = ZSpdMode_ZZ;
                    }
                    // 'compressCurvStructs_new:151' spline_index = spline_index + 1;
                    spline_index++;
                    // 'compressCurvStructs_new:41' ctx.q_compress.push( curvCompressed );
                    ctx->q_compress.push(&curvCompressed);
                    // 'compressCurvStructs_new:42' ctx.q_spline.push( spline );
                    ctx->q_spline.push(&spline);
                } else if (batch_size > 0.0) {
                    // 'compressCurvStructs_new:44' elseif( batch.size > 0 )
                    // 'compressCurvStructs_new:45' ctx.q_compress.push( batch.curvArray( 1 ) );
                    ctx->q_compress.push(&batch_curvArray_idx_0);
                }
                // 'compressCurvStructs_new:47' batch.size = 0;
                batch_size = 0.0;
            }
            // 'compressCurvStructs_new:50' if( ~addBatch )
            if (!addBatch) {
                // 'compressCurvStructs_new:51' ctx.q_compress.push( curv );
                ctx->q_compress.push(&curv);
            }
        }
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs_new.cpp
//
// [EOF]
//
