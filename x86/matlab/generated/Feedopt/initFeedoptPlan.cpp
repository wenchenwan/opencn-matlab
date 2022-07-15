//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: initFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 13-Jul-2022 14:15:57
//

// Include Files
#include "initFeedoptPlan.h"
#include "Kinematics.h"
#include "constrBaseSpline.h"
#include "constrCurvStruct.h"
#include "linspace.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function ctx = initFeedoptPlan( cfg )
//
// ctx is the context variable, it should contain:
//  - op: Operation to execute
//  - go_next:    Should we optimize the next segment
//  - q_gcode:    GCode queue
//  - q_smooth:   Queue for smoothed segments
//  - q_split:    Queue after splitting
//  - q_opt:      Queue after optimization
//
// Arguments    : const FeedoptConfig cfg
//                FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void initFeedoptPlan(const FeedoptConfig cfg, FeedoptContext *ctx)
{
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> BasisValDDD;
    ::coder::array<double, 2U> b_breakpoints;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> y;
    CurvStruct Curv;
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
    unsigned long b_h;
    unsigned long h;
    unsigned long params_spline_Bl_handle;
    int j_loop_ub;
    int l_loop_ub;
    int loop_ub_tmp;
    int n_loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    int q_loop_ub;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'initFeedoptPlan:10' coder.inline("never");
    //  if coder.target( 'MEX' )
    //      coder.extrinsic( 'queue' );
    //  end
    // 'initFeedoptPlan:16' if cfg.UseLinearBreakpoints
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        // 'initFeedoptPlan:17' Bl      = bspline_create( cfg.SplineDegree, linspace( 0, 1, ...
        // 'initFeedoptPlan:18'                                   cfg.NBreak ) );
        coder::b_linspace(cfg.NBreak, breakpoints);
        // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
        // 'bspline_create:3' nbreak = length(breakpoints);
        // 'bspline_create:4' ncoeff = nbreak + degree - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_create:8' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_create:9' coder.cinclude('src/c_spline.h');
        // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak) );
        b_breakpoints.set_size(1, breakpoints.size(1));
        b_loop_ub = breakpoints.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            b_breakpoints[i1] = breakpoints[i1];
        }
        c_bspline_create_with_breakpoints(&h, cfg.SplineDegree, &b_breakpoints[0],
                                          breakpoints.size(1));
        // 'bspline_create:11' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((breakpoints.size(1) + cfg.SplineDegree) - 2, breakpoints, h,
                         cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:19' u_vec   = linspace( 0, 1, cfg.NDiscr );
        coder::b_linspace(cfg.NDiscr, ctx->u_vec);
    } else {
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i;
        int i11;
        int i14;
        int i17;
        int i2;
        int i3;
        int i_loop_ub;
        int loop_ub;
        int o_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'initFeedoptPlan:20' else
        // 'initFeedoptPlan:21' Bl      = bspline_create( cfg.SplineDegree, sinspace( 0, 1, ...
        // 'initFeedoptPlan:22'                                   cfg.NBreak ) );
        // 'sinspace:2' t = linspace(-1,0,N);
        // 'sinspace:3' if coder.target('rtw')
        // 'sinspace:4' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:6' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
        coder::c_linspace(cfg.NBreak, r);
        y.set_size(1, r.size(1));
        loop_ub = r.size(1);
        scalarLB = (r.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i = 0; i <= vectorUB; i += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r[i]);
            _mm_storeu_pd(&y[i], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r1));
        }
        for (i = scalarLB; i < loop_ub; i++) {
            y[i] = 3.1415926535897931 * r[i];
        }
        i2 = y.size(1);
        for (int k{0}; k < i2; k++) {
            y[k] = std::cos(y[k]);
        }
        x.set_size(1, y.size(1));
        c_loop_ub = y.size(1);
        b_scalarLB = (y.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i3 = 0; i3 <= b_vectorUB; i3 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&y[i3]);
            r3 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&x[i3], _mm_add_pd(_mm_mul_pd(r2, r3), r3));
        }
        for (i3 = b_scalarLB; i3 < c_loop_ub; i3++) {
            x[i3] = y[i3] * 0.5 + 0.5;
        }
        // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
        // 'bspline_create:3' nbreak = length(breakpoints);
        // 'bspline_create:4' ncoeff = nbreak + degree - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_create:8' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_create:9' coder.cinclude('src/c_spline.h');
        // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak) );
        breakpoints.set_size(1, x.size(1));
        d_loop_ub = x.size(1);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            breakpoints[i4] = x[i4];
        }
        c_bspline_create_with_breakpoints(&b_h, cfg.SplineDegree, &breakpoints[0], x.size(1));
        // 'bspline_create:11' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((x.size(1) + cfg.SplineDegree) - 2, x, b_h, cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:23' u_vec   = sinspace( 0, 1, cfg.NDiscr );
        // 'sinspace:2' t = linspace(-1,0,N);
        // 'sinspace:3' if coder.target('rtw')
        // 'sinspace:4' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:6' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
        coder::c_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        i_loop_ub = r.size(1);
        c_scalarLB = (r.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i11 = 0; i11 <= c_vectorUB; i11 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r[i11]);
            _mm_storeu_pd(&y[i11], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r4));
        }
        for (i11 = c_scalarLB; i11 < i_loop_ub; i11++) {
            y[i11] = 3.1415926535897931 * r[i11];
        }
        i14 = y.size(1);
        for (int b_k{0}; b_k < i14; b_k++) {
            y[b_k] = std::cos(y[b_k]);
        }
        ctx->u_vec.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        d_scalarLB = (y.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i17 = 0; i17 <= d_vectorUB; i17 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&y[i17]);
            r6 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&ctx->u_vec[i17], _mm_add_pd(_mm_mul_pd(r5, r6), r6));
        }
        for (i17 = d_scalarLB; i17 < o_loop_ub; i17++) {
            ctx->u_vec[i17] = y[i17] * 0.5 + 0.5;
        }
    }
    // 'initFeedoptPlan:26' [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
    // 'initFeedoptPlan:27'                                     bspline_base_eval( Bl , u_vec );
    // 'bspline_base_eval:2' if coder.target('rtw') || coder.target('mex')
    //  n, bspline_n
    // 'bspline_base_eval:4' samples = int32(numel(xvec));
    // 'bspline_base_eval:5' BasisVal = zeros(samples, Bl.ncoeff);
    loop_ub_tmp = ctx->Bl.ncoeff;
    BasisVal.set_size(ctx->u_vec.size(1), loop_ub_tmp);
    // 'bspline_base_eval:6' BasisValD = BasisVal;
    BasisValD.set_size(ctx->u_vec.size(1), loop_ub_tmp);
    // 'bspline_base_eval:7' BasisValDD = BasisVal;
    BasisValDD.set_size(ctx->u_vec.size(1), loop_ub_tmp);
    // 'bspline_base_eval:8' BasisValDDD = BasisVal;
    BasisValDDD.set_size(ctx->u_vec.size(1), loop_ub_tmp);
    // 'bspline_base_eval:9' BasisIntegr = BasisVal(1, :)';
    ctx->BasisIntegr.set_size(loop_ub_tmp);
    for (int i5{0}; i5 < loop_ub_tmp; i5++) {
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        e_loop_ub = ctx->u_vec.size(1);
        for (int i6{0}; i6 < e_loop_ub; i6++) {
            BasisVal[i6 + BasisVal.size(0) * i5] = 0.0;
        }
        f_loop_ub = ctx->u_vec.size(1);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            BasisValD[i7 + BasisValD.size(0) * i5] = 0.0;
        }
        g_loop_ub = ctx->u_vec.size(1);
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            BasisValDD[i8 + BasisValDD.size(0) * i5] = 0.0;
        }
        h_loop_ub = ctx->u_vec.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            BasisValDDD[i9 + BasisValDDD.size(0) * i5] = 0.0;
        }
        ctx->BasisIntegr[i5] = 0.0;
    }
    // 'bspline_base_eval:11' coder.updateBuildInfo('addSourceFiles','c_spline.c',
    // '$(START_DIR)/src'); 'bspline_base_eval:12' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.gsl.lflags); 'bspline_base_eval:13' coder.cinclude('src/c_spline.h');
    // 'bspline_base_eval:14' coder.ceval('c_bspline_base_eval', coder.rref(Bl.handle), samples,
    // coder.rref(xvec), ..., 'bspline_base_eval:15'             coder.ref(BasisVal),
    // coder.ref(BasisValD), coder.ref(BasisValDD),coder.ref(BasisValDDD),... 'bspline_base_eval:16'
    // coder.ref(BasisIntegr));
    c_bspline_base_eval(&ctx->Bl.handle, ctx->u_vec.size(1), &ctx->u_vec[0], &BasisVal[0],
                        &BasisValD[0], &BasisValDD[0], &BasisValDDD[0],
                        &(ctx->BasisIntegr.data())[0]);
    // ,
    // 'initFeedoptPlan:29' ctx.BasisVal    = BasisVal;
    ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    j_loop_ub = BasisVal.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        int k_loop_ub;
        k_loop_ub = BasisVal.size(0);
        for (int i12{0}; i12 < k_loop_ub; i12++) {
            ctx->BasisVal[i12 + ctx->BasisVal.size(0) * i10] =
                BasisVal[i12 + BasisVal.size(0) * i10];
        }
    }
    // 'initFeedoptPlan:30' ctx.BasisValD   = BasisValD;
    ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    l_loop_ub = BasisValD.size(1);
    for (int i13{0}; i13 < l_loop_ub; i13++) {
        int m_loop_ub;
        m_loop_ub = BasisValD.size(0);
        for (int i15{0}; i15 < m_loop_ub; i15++) {
            ctx->BasisValD[i15 + ctx->BasisValD.size(0) * i13] =
                BasisValD[i15 + BasisValD.size(0) * i13];
        }
    }
    // 'initFeedoptPlan:31' ctx.BasisValDD  = BasisValDD;
    ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
    n_loop_ub = BasisValDD.size(1);
    for (int i16{0}; i16 < n_loop_ub; i16++) {
        int p_loop_ub;
        p_loop_ub = BasisValDD.size(0);
        for (int i18{0}; i18 < p_loop_ub; i18++) {
            ctx->BasisValDD[i18 + ctx->BasisValDD.size(0) * i16] =
                BasisValDD[i18 + BasisValDD.size(0) * i16];
        }
    }
    // 'initFeedoptPlan:32' ctx.BasisValDDD = BasisValDDD;
    ctx->BasisValDDD.set_size(BasisValDDD.size(0), BasisValDDD.size(1));
    q_loop_ub = BasisValDDD.size(1);
    for (int i19{0}; i19 < q_loop_ub; i19++) {
        int r_loop_ub;
        r_loop_ub = BasisValDDD.size(0);
        for (int i20{0}; i20 < r_loop_ub; i20++) {
            ctx->BasisValDDD[i20 + ctx->BasisValDDD.size(0) * i19] =
                BasisValDDD[i20 + BasisValDDD.size(0) * i19];
        }
    }
    // 'initFeedoptPlan:33' ctx.BasisIntegr = BasisIntegr;
    // 'initFeedoptPlan:34' ctx.Bl          = Bl;
    // 'initFeedoptPlan:35' ctx.u_vec       = u_vec;
    // 'initFeedoptPlan:37' Curv            = constrCurvStructType();
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
        params_R1, params_Cprim, params_evec, params_CoeffP5, &Curv);
    // 'initFeedoptPlan:38' ctx.q_spline    = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_spline.init(&Curv);
    // 'initFeedoptPlan:39' ctx.q_gcode     = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_gcode.init(&Curv);
    // 'initFeedoptPlan:40' ctx.q_compress  = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_compress.init(&Curv);
    // 'initFeedoptPlan:41' ctx.q_smooth    = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_smooth.init(&Curv);
    // 'initFeedoptPlan:42' ctx.q_split     = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_split.init(&Curv);
    // 'initFeedoptPlan:43' ctx.q_opt       = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_opt.init(&Curv);
    //
    // 'initFeedoptPlan:45' ctx.op              = Fopt.Init;
    ctx->op = Fopt_Init;
    // 'initFeedoptPlan:46' ctx.go_next         = false;
    ctx->go_next = false;
    // 'initFeedoptPlan:47' ctx.try_push_again  = false;
    ctx->try_push_again = false;
    // 'initFeedoptPlan:48' ctx.n_optimized     = int32(0);
    ctx->n_optimized = 0;
    // 'initFeedoptPlan:49' ctx.reached_end     = false;
    ctx->reached_end = false;
    // 'initFeedoptPlan:50' ctx.k0              = int32(1);
    ctx->k0 = 1;
    // 'initFeedoptPlan:51' ctx.v_0             = cfg.v_0;
    ctx->v_0 = cfg.v_0;
    // 'initFeedoptPlan:52' ctx.v_1             = cfg.v_1;
    ctx->v_1 = cfg.v_1;
    // 'initFeedoptPlan:53' ctx.at_0            = cfg.at_0;
    ctx->at_0 = cfg.at_0;
    // 'initFeedoptPlan:54' ctx.at_1            = cfg.at_1;
    ctx->at_1 = cfg.at_1;
    // 'initFeedoptPlan:55' ctx.cfg             = cfg;
    ctx->cfg = cfg;
    // 'initFeedoptPlan:56' ctx.errcode         = FeedoptPlanError.Success;
    ctx->errcode = FeedoptPlanError_Success;
    // 'initFeedoptPlan:57' ctx.jmax_increase_count = int32(0);
    ctx->jmax_increase_count = 0;
    // 'initFeedoptPlan:58' ctx.zero_start          = false;
    ctx->zero_start = false;
    // 'initFeedoptPlan:59' ctx.zero_end            = false;
    ctx->zero_end = false;
    // 'initFeedoptPlan:60' ctx.simplex_calls       = int32(0);
    ctx->simplex_calls = 0;
    // 'initFeedoptPlan:62' ctx.forced_stop     = int32(0);
    ctx->forced_stop = 0;
    // 'initFeedoptPlan:63' ctx.programmed_stop = int32(0);
    ctx->programmed_stop = 0;
    // 'initFeedoptPlan:65' ctx.Coeff   = zeros( 1, 1 );
    ctx->Coeff.set_size(1, 1);
    ctx->Coeff[0] = 0.0;
    // 'initFeedoptPlan:66' ctx.Skipped = int32(0);
    ctx->Skipped = 0;
    // 'initFeedoptPlan:67' ctx.kin     = Kinematics( cfg.kin_type, cfg.kin_params );
    ctx->kin.init(cfg.kin_type, cfg.kin_params.data, cfg.kin_params.size[0]);
    // 'initFeedoptPlan:69' Curv.Info.Type = CurveType.Spline;
    Curv.Info.Type = CurveType_Spline;
    // 'initFeedoptPlan:70' Curv.sp.Bl     = Bl;
    Curv.sp.Bl = ctx->Bl;
    // 'initFeedoptPlan:72' if ~coder.target('matlab')
    // 'initFeedoptPlan:74' coder.varsize( 'ctx.cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:75' coder.varsize( 'ctx.cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:76' coder.varsize( 'ctx.cfg.maskTot',   StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:77' coder.varsize( 'ctx.cfg.maskCart',  StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:78' coder.varsize( 'ctx.cfg.maskRot',   StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:79' coder.varsize( 'ctx.cfg.D',         StructTypeName.dimD{ : } );
    // 'initFeedoptPlan:80' coder.varsize( 'ctx.cfg.kin_params',StructTypeName.dimKinParams{ : } );
    // 'initFeedoptPlan:81' coder.varsize('ctx.BasisVal',       StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:82' coder.varsize('ctx.BasisValD',      StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:83' coder.varsize('ctx.BasisValDD',     StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:84' coder.varsize('ctx.BasisIntegr',    StructTypeName.dimBasisInt{ : } );
    // 'initFeedoptPlan:85' coder.varsize('ctx.u_vec',          StructTypeName.dimCtxUvec{ : } );
    // 'initFeedoptPlan:86' coder.varsize('ctx.Bl.breakpoints', StructTypeName.dimCtxBlBreaks{ : }
    // ); 'initFeedoptPlan:87' coder.varsize('ctx.Coeff',          StructTypeName.dimCtxCoeff{ : }
    // ); 'initFeedoptPlan:88' coder.cstructname(ctx, StructTypeName.FeedoptCtx );
    // 'initFeedoptPlan:91' ctx.q_spline.push( Curv );
    ctx->q_spline.push(&Curv);
}

} // namespace ocn

//
// File trailer for initFeedoptPlan.cpp
//
// [EOF]
//
