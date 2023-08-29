//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: initFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:40:50
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
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "c_spline.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
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
    ::coder::array<double, 2U> b_breakpoints;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> y;
    Axes params_tool_offset;
    CurvStruct Curv;
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
    int d_loop_ub;
    int f_loop_ub;
    int i_loop_ub;
    int k_loop_ub;
    int loop_ub_tmp;
    int o_loop_ub;
    int p_loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int t_loop_ub;
    int u_loop_ub;
    int v_loop_ub;
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
    // 'initFeedoptPlan:12' if cfg.UseLinearBreakpoints
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        // 'initFeedoptPlan:13' Bl      = bspline_create( cfg.SplineDegree, linspace( 0, 1, ...
        // 'initFeedoptPlan:14'                                   cfg.NBreak ) );
        coder::b_linspace(cfg.NBreak, breakpoints);
        // 'bspline_create:2' if  coder.target('rtw') || coder.target('mex')
        // 'bspline_create:3' nbreak = length(breakpoints);
        // 'bspline_create:4' ncoeff = nbreak + degree - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:6' my_path = StructTypeName.WDIR + "/src";
        // 'bspline_create:7' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        // 'bspline_create:10' coder.cinclude('c_spline.h');
        // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak) );
        b_breakpoints.set_size(1, breakpoints.size(1));
        b_loop_ub = breakpoints.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            b_breakpoints[i1] = breakpoints[i1];
        }
        unsigned long h;
        c_bspline_create_with_breakpoints(&h, cfg.SplineDegree, &b_breakpoints[0],
                                          breakpoints.size(1));
        // 'bspline_create:12' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((breakpoints.size(1) + cfg.SplineDegree) - 2, breakpoints, h,
                         cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:15' u_vec   = linspace( 0, 1, cfg.NDiscr );
        coder::b_linspace(cfg.NDiscr, ctx->u_vec);
    } else {
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_scalarLB;
        int d_vectorUB;
        int g_loop_ub;
        int i15;
        int i2;
        int loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'initFeedoptPlan:16' else
        // 'initFeedoptPlan:17' Bl      = bspline_create( cfg.SplineDegree, sinspace( 0, 1, ...
        // 'initFeedoptPlan:18'                                   cfg.NBreak ) );
        // 'sinspace:2' t = linspace(-1,0,N);
        // 'sinspace:3' if coder.target('rtw')
        // 'sinspace:4' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:6' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
        coder::c_linspace(cfg.NBreak, r);
        y.set_size(1, r.size(1));
        loop_ub = r.size(1);
        scalarLB = (r.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i{0}; i <= vectorUB; i += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r[i]);
            _mm_storeu_pd(&y[i], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r1));
        }
        for (int i{scalarLB}; i < loop_ub; i++) {
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
        for (int i3{0}; i3 <= b_vectorUB; i3 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&y[i3]);
            r3 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&x[i3], _mm_add_pd(_mm_mul_pd(r2, r3), r3));
        }
        for (int i3{b_scalarLB}; i3 < c_loop_ub; i3++) {
            x[i3] = y[i3] * 0.5 + 0.5;
        }
        // 'bspline_create:2' if  coder.target('rtw') || coder.target('mex')
        // 'bspline_create:3' nbreak = length(breakpoints);
        // 'bspline_create:4' ncoeff = nbreak + degree - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:6' my_path = StructTypeName.WDIR + "/src";
        // 'bspline_create:7' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        // 'bspline_create:10' coder.cinclude('c_spline.h');
        // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak) );
        breakpoints.set_size(1, x.size(1));
        g_loop_ub = x.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            breakpoints[i7] = x[i7];
        }
        unsigned long b_h;
        c_bspline_create_with_breakpoints(&b_h, cfg.SplineDegree, &breakpoints[0], x.size(1));
        // 'bspline_create:12' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((x.size(1) + cfg.SplineDegree) - 2, x, b_h, cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:19' u_vec   = sinspace( 0, 1, cfg.NDiscr );
        // 'sinspace:2' t = linspace(-1,0,N);
        // 'sinspace:3' if coder.target('rtw')
        // 'sinspace:4' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:6' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
        coder::c_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        m_loop_ub = r.size(1);
        c_scalarLB = (r.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i14{0}; i14 <= c_vectorUB; i14 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r[i14]);
            _mm_storeu_pd(&y[i14], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r4));
        }
        for (int i14{c_scalarLB}; i14 < m_loop_ub; i14++) {
            y[i14] = 3.1415926535897931 * r[i14];
        }
        i15 = y.size(1);
        for (int b_k{0}; b_k < i15; b_k++) {
            y[b_k] = std::cos(y[b_k]);
        }
        ctx->u_vec.set_size(1, y.size(1));
        n_loop_ub = y.size(1);
        d_scalarLB = (y.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (int i16{0}; i16 <= d_vectorUB; i16 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&y[i16]);
            r6 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&ctx->u_vec[i16], _mm_add_pd(_mm_mul_pd(r5, r6), r6));
        }
        for (int i16{d_scalarLB}; i16 < n_loop_ub; i16++) {
            ctx->u_vec[i16] = y[i16] * 0.5 + 0.5;
        }
    }
    // 'initFeedoptPlan:22' [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
    // 'initFeedoptPlan:23'                                     bspline_base_eval( Bl , u_vec );
    // 'bspline_base_eval:4' if coder.target('rtw') || coder.target('mex')
    //  n, bspline_n
    // 'bspline_base_eval:6' samples     = int32(numel(xvec));
    // 'bspline_base_eval:7' BasisVal    = zeros(samples, Bl.ncoeff);
    ctx->BasisVal.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    d_loop_ub = ctx->Bl.ncoeff;
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        int e_loop_ub;
        e_loop_ub = ctx->u_vec.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            ctx->BasisVal[i5 + ctx->BasisVal.size(0) * i4] = 0.0;
        }
    }
    // 'bspline_base_eval:8' BasisValD   = BasisVal;
    ctx->BasisValD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    f_loop_ub = ctx->Bl.ncoeff;
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = ctx->u_vec.size(1);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            ctx->BasisValD[i8 + ctx->BasisValD.size(0) * i6] = 0.0;
        }
    }
    // 'bspline_base_eval:9' BasisValDD  = BasisVal;
    ctx->BasisValDD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    i_loop_ub = ctx->Bl.ncoeff;
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        int j_loop_ub;
        j_loop_ub = ctx->u_vec.size(1);
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            ctx->BasisValDD[i10 + ctx->BasisValDD.size(0) * i9] = 0.0;
        }
    }
    // 'bspline_base_eval:10' BasisValDDD = BasisVal;
    ctx->BasisValDDD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    k_loop_ub = ctx->Bl.ncoeff;
    for (int i11{0}; i11 < k_loop_ub; i11++) {
        int l_loop_ub;
        l_loop_ub = ctx->u_vec.size(1);
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            ctx->BasisValDDD[i12 + ctx->BasisValDDD.size(0) * i11] = 0.0;
        }
    }
    // 'bspline_base_eval:11' BasisIntegr = BasisVal(1, :)';
    loop_ub_tmp = ctx->Bl.ncoeff;
    ctx->BasisIntegr.set_size(ctx->Bl.ncoeff);
    for (int i13{0}; i13 < loop_ub_tmp; i13++) {
        ctx->BasisIntegr[i13] = 0.0;
    }
    // 'bspline_base_eval:13' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_base_eval:14' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_base_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_base_eval:16' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags );
    // 'bspline_base_eval:17' coder.cinclude('c_spline.h');
    // 'bspline_base_eval:18' coder.ceval( 'c_bspline_base_eval', coder.rref( Bl.handle ), samples,
    // ... 'bspline_base_eval:19'                      coder.rref( xvec ), coder.ref( BasisVal ),
    // ... 'bspline_base_eval:20'                      coder.ref( BasisValD ), coder.ref( BasisValDD
    // ), ... 'bspline_base_eval:21'                      coder.ref( BasisValDDD ), coder.ref(
    // BasisIntegr ) );
    c_bspline_base_eval(&ctx->Bl.handle, ctx->u_vec.size(1), &ctx->u_vec[0], &ctx->BasisVal[0],
                        &ctx->BasisValD[0], &ctx->BasisValDD[0], &ctx->BasisValDDD[0],
                        &(ctx->BasisIntegr.data())[0]);
    // 'initFeedoptPlan:25' ctx.BasisVal    = BasisVal;
    // 'initFeedoptPlan:26' ctx.BasisValD   = BasisValD;
    // 'initFeedoptPlan:27' ctx.BasisValDD  = BasisValDD;
    // 'initFeedoptPlan:28' ctx.BasisValDDD = BasisValDDD;
    // 'initFeedoptPlan:29' ctx.BasisIntegr = BasisIntegr;
    // 'initFeedoptPlan:30' ctx.Bl          = Bl;
    // 'initFeedoptPlan:31' ctx.u_vec       = u_vec;
    // 'initFeedoptPlan:33' Curv            = constrCurvStructType();
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
                       params_R1, params_Cprim, params_evec, params_CoeffP5, &Curv);
    // 'initFeedoptPlan:34' ctx.q_spline    = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_spline.init(&Curv);
    // 'initFeedoptPlan:35' ctx.q_gcode     = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_gcode.init(&Curv);
    // 'initFeedoptPlan:36' ctx.q_compress  = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_compress.init(&Curv);
    // 'initFeedoptPlan:37' ctx.q_smooth    = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_smooth.init(&Curv);
    // 'initFeedoptPlan:38' ctx.q_split     = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_split.init(&Curv);
    // 'initFeedoptPlan:39' ctx.q_opt       = queue( Curv );
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_opt.init(&Curv);
    //
    // 'initFeedoptPlan:41' ctx.op              = Fopt.Init;
    ctx->op = Fopt_Init;
    // 'initFeedoptPlan:42' ctx.go_next         = false;
    ctx->go_next = false;
    // 'initFeedoptPlan:43' ctx.try_push_again  = false;
    ctx->try_push_again = false;
    // 'initFeedoptPlan:44' ctx.n_optimized     = int32(0);
    ctx->n_optimized = 0;
    // 'initFeedoptPlan:45' ctx.reached_end     = false;
    ctx->reached_end = false;
    // 'initFeedoptPlan:46' ctx.k0              = int32(1);
    ctx->k0 = 1;
    // 'initFeedoptPlan:47' ctx.v_0             = cfg.v_0;
    ctx->v_0 = cfg.v_0;
    // 'initFeedoptPlan:48' ctx.v_1             = cfg.v_1;
    ctx->v_1 = cfg.v_1;
    // 'initFeedoptPlan:49' ctx.at_0            = cfg.at_0;
    ctx->at_0 = cfg.at_0;
    // 'initFeedoptPlan:50' ctx.at_1            = cfg.at_1;
    ctx->at_1 = cfg.at_1;
    // 'initFeedoptPlan:51' ctx.cfg             = cfg;
    ctx->cfg.maskTot.size[0] = 1;
    ctx->cfg.maskTot.size[1] = cfg.maskTot.size[1];
    o_loop_ub = cfg.maskTot.size[1];
    if (o_loop_ub - 1 >= 0) {
        std::copy(&cfg.maskTot.data[0], &cfg.maskTot.data[o_loop_ub], &ctx->cfg.maskTot.data[0]);
    }
    ctx->cfg.maskCart.size[0] = 1;
    ctx->cfg.maskCart.size[1] = cfg.maskCart.size[1];
    p_loop_ub = cfg.maskCart.size[1];
    if (p_loop_ub - 1 >= 0) {
        std::copy(&cfg.maskCart.data[0], &cfg.maskCart.data[p_loop_ub], &ctx->cfg.maskCart.data[0]);
    }
    ctx->cfg.maskRot.size[0] = 1;
    ctx->cfg.maskRot.size[1] = cfg.maskRot.size[1];
    q_loop_ub = cfg.maskRot.size[1];
    if (q_loop_ub - 1 >= 0) {
        std::copy(&cfg.maskRot.data[0], &cfg.maskRot.data[q_loop_ub], &ctx->cfg.maskRot.data[0]);
    }
    ctx->cfg.indCart.size[0] = cfg.indCart.size[0];
    r_loop_ub = cfg.indCart.size[0];
    if (r_loop_ub - 1 >= 0) {
        std::copy(&cfg.indCart.data[0], &cfg.indCart.data[r_loop_ub], &ctx->cfg.indCart.data[0]);
    }
    ctx->cfg.indRot.size[0] = cfg.indRot.size[0];
    s_loop_ub = cfg.indRot.size[0];
    if (s_loop_ub - 1 >= 0) {
        std::copy(&cfg.indRot.data[0], &cfg.indRot.data[s_loop_ub], &ctx->cfg.indRot.data[0]);
    }
    ctx->cfg.NumberAxis = cfg.NumberAxis;
    ctx->cfg.NCart = cfg.NCart;
    ctx->cfg.NRot = cfg.NRot;
    ctx->cfg.D.size[0] = cfg.D.size[0];
    t_loop_ub = cfg.D.size[0];
    if (t_loop_ub - 1 >= 0) {
        std::copy(&cfg.D.data[0], &cfg.D.data[t_loop_ub], &ctx->cfg.D.data[0]);
    }
    ctx->cfg.coeffD = cfg.coeffD;
    ctx->cfg.kin_params.size[0] = cfg.kin_params.size[0];
    u_loop_ub = cfg.kin_params.size[0];
    if (u_loop_ub - 1 >= 0) {
        std::copy(&cfg.kin_params.data[0], &cfg.kin_params.data[u_loop_ub],
                  &ctx->cfg.kin_params.data[0]);
    }
    for (int i17{0}; i17 < 5; i17++) {
        ctx->cfg.kin_type[i17] = cfg.kin_type[i17];
    }
    ctx->cfg.NDiscr = cfg.NDiscr;
    ctx->cfg.NBreak = cfg.NBreak;
    ctx->cfg.UseDynamicBreakpoints = cfg.UseDynamicBreakpoints;
    ctx->cfg.UseLinearBreakpoints = cfg.UseLinearBreakpoints;
    ctx->cfg.DynamicBreakpointsDistance = cfg.DynamicBreakpointsDistance;
    ctx->cfg.NHorz = cfg.NHorz;
    ctx->cfg.fmax = cfg.fmax;
    ctx->cfg.smax = cfg.smax;
    for (int i18{0}; i18 < 6; i18++) {
        ctx->cfg.vmax[i18] = cfg.vmax[i18];
        ctx->cfg.amax[i18] = cfg.amax[i18];
        ctx->cfg.jmax[i18] = cfg.jmax[i18];
    }
    ctx->cfg.LeeSplineDegree = cfg.LeeSplineDegree;
    ctx->cfg.SplineDegree = cfg.SplineDegree;
    ctx->cfg.CutOff = cfg.CutOff;
    ctx->cfg.LSplit = cfg.LSplit;
    ctx->cfg.LSplitZero = cfg.LSplitZero;
    ctx->cfg.LThresholdMax = cfg.LThresholdMax;
    ctx->cfg.LThresholdMin = cfg.LThresholdMin;
    ctx->cfg.v_0 = cfg.v_0;
    ctx->cfg.at_0 = cfg.at_0;
    ctx->cfg.v_1 = cfg.v_1;
    ctx->cfg.at_1 = cfg.at_1;
    ctx->cfg.dt = cfg.dt;
    ctx->cfg.ZeroStartAccLimit = cfg.ZeroStartAccLimit;
    ctx->cfg.ZeroStartJerkLimit = cfg.ZeroStartJerkLimit;
    ctx->cfg.ZeroStartVelLimit = cfg.ZeroStartVelLimit;
    ctx->cfg.source.set_size(1, cfg.source.size[1]);
    v_loop_ub = cfg.source.size[1];
    for (int i19{0}; i19 < v_loop_ub; i19++) {
        ctx->cfg.source[i19] = cfg.source.data[i19];
    }
    ctx->cfg.DebugCutZero = cfg.DebugCutZero;
    ctx->cfg.Cusp = cfg.Cusp;
    ctx->cfg.Compressing = cfg.Compressing;
    ctx->cfg.Smoothing = cfg.Smoothing;
    ctx->cfg.GaussLegendreN = cfg.GaussLegendreN;
    for (int b_i{0}; b_i < 5; b_i++) {
        ctx->cfg.GaussLegendreX[b_i] = cfg.GaussLegendreX[b_i];
        ctx->cfg.GaussLegendreW[b_i] = cfg.GaussLegendreW[b_i];
    }
    ctx->cfg.opt = cfg.opt;
    for (int i20{0}; i20 < 9; i20++) {
        ctx->cfg.LogFileName[i20] = cfg.LogFileName[i20];
    }
    // 'initFeedoptPlan:52' ctx.errcode         = FeedoptPlanError.Success;
    ctx->errcode = FeedoptPlanError_Success;
    // 'initFeedoptPlan:53' ctx.jmax_increase_count = int32(0);
    ctx->jmax_increase_count = 0;
    // 'initFeedoptPlan:54' ctx.zero_start          = false;
    ctx->zero_start = false;
    // 'initFeedoptPlan:55' ctx.zero_end            = false;
    ctx->zero_end = false;
    // 'initFeedoptPlan:56' ctx.simplex_calls       = int32(0);
    ctx->simplex_calls = 0;
    // 'initFeedoptPlan:58' ctx.forced_stop     = int32(0);
    ctx->forced_stop = 0;
    // 'initFeedoptPlan:59' ctx.programmed_stop = int32(0);
    ctx->programmed_stop = 0;
    // 'initFeedoptPlan:61' ctx.Coeff   = zeros( 1, 1 );
    ctx->Coeff.set_size(1, 1);
    ctx->Coeff[0] = 0.0;
    // 'initFeedoptPlan:62' ctx.Skipped = int32(0);
    ctx->Skipped = 0;
    // 'initFeedoptPlan:63' ctx.kin     = Kinematics( cfg.kin_type, cfg.kin_params );
    ctx->kin.init(cfg.kin_type, cfg.kin_params.data, cfg.kin_params.size[0]);
    // 'initFeedoptPlan:65' Curv.Info.Type = CurveType.Spline;
    Curv.Info.Type = CurveType_Spline;
    // 'initFeedoptPlan:66' Curv.sp.Bl     = Bl;
    Curv.sp.Bl = ctx->Bl;
    // 'initFeedoptPlan:68' if ~coder.target('matlab')
    // 'initFeedoptPlan:70' coder.varsize( 'ctx.cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:71' coder.varsize( 'ctx.cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:72' coder.varsize( 'ctx.cfg.maskTot',   StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:73' coder.varsize( 'ctx.cfg.maskCart',  StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:74' coder.varsize( 'ctx.cfg.maskRot',   StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:75' coder.varsize( 'ctx.cfg.D',         StructTypeName.dimD{ : } );
    // 'initFeedoptPlan:76' coder.varsize( 'ctx.cfg.kin_params',StructTypeName.dimKinParams{ : } );
    // 'initFeedoptPlan:77' coder.varsize('ctx.BasisVal',       StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:78' coder.varsize('ctx.BasisValD',      StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:79' coder.varsize('ctx.BasisValDD',     StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:80' coder.varsize('ctx.BasisIntegr',    StructTypeName.dimBasisInt{ : } );
    // 'initFeedoptPlan:81' coder.varsize('ctx.u_vec',          StructTypeName.dimCtxUvec{ : } );
    // 'initFeedoptPlan:82' coder.varsize('ctx.Bl.breakpoints', StructTypeName.dimCtxBlBreaks{ : }
    // ); 'initFeedoptPlan:83' coder.varsize('ctx.Coeff',          StructTypeName.dimCtxCoeff{ : }
    // ); 'initFeedoptPlan:84' coder.cstructname(ctx, StructTypeName.FeedoptCtx );
    // 'initFeedoptPlan:87' ctx.q_spline.push( Curv );
    ctx->q_spline.push(&Curv);
}

} // namespace ocn

//
// File trailer for initFeedoptPlan.cpp
//
// [EOF]
//
