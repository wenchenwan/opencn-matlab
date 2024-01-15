
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: initFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.4
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
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
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
// function [ ctx ] = initFeedoptPlan( cfg )
//
// initFeedoptPlan : Initialize the context of the computational chain.
//
//  Inputs :
//    cfg : The configuration structure
//
//  Outputs :
//    ctx : The context structure of the computational chain
//
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
    b_CurvStruct e_expl_temp;
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
    int s_loop_ub;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'initFeedoptPlan:11' coder.inline("never");
    // 'initFeedoptPlan:13' if cfg.UseLinearBreakpoints
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        // 'initFeedoptPlan:14' Bl      = bspline_create( cfg.SplineDegree, linspace( 0, 1, ...
        // 'initFeedoptPlan:15'                                   cfg.NBreak ) );
        coder::b_linspace(cfg.NBreak, breakpoints);
        //  bspline_create : Create the BSpline basis functions
        //
        //  Inputs :
        //  degree        : BSpline degree
        //  breakpoints   : Vector of breakpoints
        //
        //  Outputs :
        //  Bl            : Bspline basis
        // 'bspline_create:10' if  coder.target( "MATLAB" )
        // 'bspline_create:12' else
        // 'bspline_create:13' nbreak  = length(breakpoints);
        // 'bspline_create:14' ncoeff  = nbreak + degree - 2;
        // 'bspline_create:15' h       = uint64(0);
        // 'bspline_create:16' my_path = StructTypeName.WDIR + "/src";
        // 'bspline_create:17' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'bspline_create:18' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        // 'bspline_create:19' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        // 'bspline_create:20' coder.cinclude('c_spline.h');
        // 'bspline_create:21' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), ...
        // 'bspline_create:22'         degree, breakpoints, int32(nbreak) );
        b_breakpoints.set_size(1, breakpoints.size(1));
        b_loop_ub = breakpoints.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            b_breakpoints[i1] = breakpoints[i1];
        }
        unsigned long h;
        c_bspline_create_with_breakpoints(&h, cfg.SplineDegree, &b_breakpoints[0],
                                          breakpoints.size(1));
        // 'bspline_create:23' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((breakpoints.size(1) + cfg.SplineDegree) - 2, breakpoints, h,
                         cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:16' u_vec   = linspace( 0, 1, cfg.NDiscr );
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
        // 'initFeedoptPlan:17' else
        // 'initFeedoptPlan:18' Bl      = bspline_create( cfg.SplineDegree, sinspace( 0, 1, ...
        // 'initFeedoptPlan:19'                                   cfg.NBreak ) );
        //  sinspace : Other type of noead distribution for a BSpline based on a
        //  sinus-like distribution (more points at start and end of the curve).
        //
        //  Note : I don't know this code (HGS).
        //
        //  Inputs :
        //    x0  :
        //    x1  :
        //    N   :
        //
        //  Outputs :
        //    x   : Resulting points
        //
        // 'sinspace:16' t = linspace(-1,0,N);
        // 'sinspace:17' if coder.target('rtw')
        // 'sinspace:18' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:20' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
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
        //  bspline_create : Create the BSpline basis functions
        //
        //  Inputs :
        //  degree        : BSpline degree
        //  breakpoints   : Vector of breakpoints
        //
        //  Outputs :
        //  Bl            : Bspline basis
        // 'bspline_create:10' if  coder.target( "MATLAB" )
        // 'bspline_create:12' else
        // 'bspline_create:13' nbreak  = length(breakpoints);
        // 'bspline_create:14' ncoeff  = nbreak + degree - 2;
        // 'bspline_create:15' h       = uint64(0);
        // 'bspline_create:16' my_path = StructTypeName.WDIR + "/src";
        // 'bspline_create:17' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'bspline_create:18' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        // 'bspline_create:19' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        // 'bspline_create:20' coder.cinclude('c_spline.h');
        // 'bspline_create:21' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), ...
        // 'bspline_create:22'         degree, breakpoints, int32(nbreak) );
        breakpoints.set_size(1, x.size(1));
        g_loop_ub = x.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            breakpoints[i7] = x[i7];
        }
        unsigned long b_h;
        c_bspline_create_with_breakpoints(&b_h, cfg.SplineDegree, &breakpoints[0], x.size(1));
        // 'bspline_create:23' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
        constrBaseSpline((x.size(1) + cfg.SplineDegree) - 2, x, b_h, cfg.SplineDegree, &ctx->Bl);
        // 'initFeedoptPlan:20' u_vec   = sinspace( 0, 1, cfg.NDiscr );
        //  sinspace : Other type of noead distribution for a BSpline based on a
        //  sinus-like distribution (more points at start and end of the curve).
        //
        //  Note : I don't know this code (HGS).
        //
        //  Inputs :
        //    x0  :
        //    x1  :
        //    N   :
        //
        //  Outputs :
        //    x   : Resulting points
        //
        // 'sinspace:16' t = linspace(-1,0,N);
        // 'sinspace:17' if coder.target('rtw')
        // 'sinspace:18' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:20' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
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
    // 'initFeedoptPlan:24' [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
    // 'initFeedoptPlan:25'                                     bspline_base_eval( Bl , u_vec );
    //  bspline_base_eval : Eval Bspline bases for a given set of points.
    //
    //  Inputs :
    //  Bl            : BSpline bases
    //  xvec          : Given set of points
    //
    //  Outputs:
    //  BasisVal      : Basis of B-Spline
    //  BasisValD     : Basis of derivative of B-Spline
    //  BasisValDD    : Basis of 2nd derivative of B-Spline
    //  BasisValDDD   : Basis of 3rd derivative of B-Spline
    //  BasisIntegr   : Basis of Intregation of B-Spline
    // 'bspline_base_eval:15' if coder.target( "MATLAB" )
    // 'bspline_base_eval:18' else
    // 'bspline_base_eval:19' samples     = int32( numel( xvec ) );
    // 'bspline_base_eval:20' BasisVal    = zeros( samples, Bl.ncoeff );
    ctx->BasisVal.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    d_loop_ub = ctx->Bl.ncoeff;
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        int e_loop_ub;
        e_loop_ub = ctx->u_vec.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            ctx->BasisVal[i5 + ctx->BasisVal.size(0) * i4] = 0.0;
        }
    }
    // 'bspline_base_eval:21' BasisValD   = BasisVal;
    ctx->BasisValD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    f_loop_ub = ctx->Bl.ncoeff;
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = ctx->u_vec.size(1);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            ctx->BasisValD[i8 + ctx->BasisValD.size(0) * i6] = 0.0;
        }
    }
    // 'bspline_base_eval:22' BasisValDD  = BasisVal;
    ctx->BasisValDD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    i_loop_ub = ctx->Bl.ncoeff;
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        int j_loop_ub;
        j_loop_ub = ctx->u_vec.size(1);
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            ctx->BasisValDD[i10 + ctx->BasisValDD.size(0) * i9] = 0.0;
        }
    }
    // 'bspline_base_eval:23' BasisValDDD = BasisVal;
    ctx->BasisValDDD.set_size(ctx->u_vec.size(1), ctx->Bl.ncoeff);
    k_loop_ub = ctx->Bl.ncoeff;
    for (int i11{0}; i11 < k_loop_ub; i11++) {
        int l_loop_ub;
        l_loop_ub = ctx->u_vec.size(1);
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            ctx->BasisValDDD[i12 + ctx->BasisValDDD.size(0) * i11] = 0.0;
        }
    }
    // 'bspline_base_eval:24' BasisIntegr = BasisVal( 1, : )';
    loop_ub_tmp = ctx->Bl.ncoeff;
    ctx->BasisIntegr.set_size(ctx->Bl.ncoeff);
    for (int i13{0}; i13 < loop_ub_tmp; i13++) {
        ctx->BasisIntegr[i13] = 0.0;
    }
    // 'bspline_base_eval:26' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_base_eval:27' coder.updateBuildInfo( 'addIncludePaths',my_path );
    // 'bspline_base_eval:28' coder.updateBuildInfo( 'addSourceFiles','c_spline.c', my_path );
    // 'bspline_base_eval:29' coder.updateBuildInfo( 'addLinkFlags', LibInfo.gsl.lflags );
    // 'bspline_base_eval:30' coder.cinclude( 'c_spline.h' );
    // 'bspline_base_eval:31' coder.ceval( 'c_bspline_base_eval', coder.rref( Bl.handle ), samples,
    // ... 'bspline_base_eval:32'             coder.rref( xvec ), coder.ref( BasisVal ), ...
    // 'bspline_base_eval:33'             coder.ref( BasisValD ), coder.ref( BasisValDD ), ...
    // 'bspline_base_eval:34'             coder.ref( BasisValDDD ), coder.ref( BasisIntegr ) );
    c_bspline_base_eval(&ctx->Bl.handle, ctx->u_vec.size(1), &ctx->u_vec[0], &ctx->BasisVal[0],
                        &ctx->BasisValD[0], &ctx->BasisValDD[0], &ctx->BasisValDDD[0],
                        &(ctx->BasisIntegr.data())[0]);
    // 'initFeedoptPlan:27' ctx.BasisVal            = BasisVal;
    // 'initFeedoptPlan:28' ctx.BasisValD           = BasisValD;
    // 'initFeedoptPlan:29' ctx.BasisValDD          = BasisValDD;
    // 'initFeedoptPlan:30' ctx.BasisValDDD         = BasisValDDD;
    // 'initFeedoptPlan:31' ctx.BasisIntegr         = BasisIntegr;
    // 'initFeedoptPlan:32' ctx.Bl                  = Bl;
    // 'initFeedoptPlan:33' ctx.u_vec               = u_vec;
    //  Initialize the different queue used in the computational chain
    // 'initFeedoptPlan:36' Curv                    = constrCurvStructType;
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
                       params_R1, params_Cprim, params_evec, params_CoeffP5, &e_expl_temp);
    Curv.Info = e_expl_temp.Info;
    Curv.tool = e_expl_temp.tool;
    Curv.sp = e_expl_temp.sp;
    Curv.R0.set_size(e_expl_temp.R0.size[0]);
    o_loop_ub = e_expl_temp.R0.size[0];
    for (int i17{0}; i17 < o_loop_ub; i17++) {
        Curv.R0[i17] = e_expl_temp.R0.data[i17];
    }
    Curv.R1.set_size(e_expl_temp.R1.size[0]);
    p_loop_ub = e_expl_temp.R1.size[0];
    for (int i18{0}; i18 < p_loop_ub; i18++) {
        Curv.R1[i18] = e_expl_temp.R1.data[i18];
    }
    Curv.delta = e_expl_temp.delta;
    Curv.CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    Curv.evec[0] = e_expl_temp.evec[0];
    Curv.CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    Curv.evec[1] = e_expl_temp.evec[1];
    Curv.CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    Curv.evec[2] = e_expl_temp.evec[2];
    Curv.theta = e_expl_temp.theta;
    Curv.pitch = e_expl_temp.pitch;
    Curv.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    q_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i19{0}; i19 < q_loop_ub; i19++) {
        int r_loop_ub;
        r_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i20{0}; i20 < r_loop_ub; i20++) {
            Curv.CoeffP5[i20 + Curv.CoeffP5.size(0) * i19] =
                e_expl_temp.CoeffP5[i20 + e_expl_temp.CoeffP5.size(0) * i19];
        }
    }
    Curv.sp_index = e_expl_temp.sp_index;
    Curv.i_begin_sp = e_expl_temp.i_begin_sp;
    Curv.i_end_sp = e_expl_temp.i_end_sp;
    Curv.index_smooth = e_expl_temp.index_smooth;
    Curv.UseConstJerk = e_expl_temp.UseConstJerk;
    Curv.ConstJerk = e_expl_temp.ConstJerk;
    Curv.Coeff.set_size(e_expl_temp.Coeff.size(0));
    s_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i21{0}; i21 < s_loop_ub; i21++) {
        Curv.Coeff[i21] = e_expl_temp.Coeff[i21];
    }
    Curv.a_param = e_expl_temp.a_param;
    Curv.b_param = e_expl_temp.b_param;
    // 'initFeedoptPlan:37' ctx.q_spline            = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_spline.init(&Curv);
    // 'initFeedoptPlan:38' ctx.q_gcode             = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_gcode.init(&Curv);
    // 'initFeedoptPlan:39' ctx.q_compress          = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_compress.init(&Curv);
    // 'initFeedoptPlan:40' ctx.q_smooth            = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_smooth.init(&Curv);
    // 'initFeedoptPlan:41' ctx.q_split             = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_split.init(&Curv);
    // 'initFeedoptPlan:42' ctx.q_opt               = queue( Curv );
    //  queue : Create and return a queue of the provided input type
    //
    //  Inputs :
    //   value_type   : A value type that the queue should contains
    //  Outputs :
    //    q           : A queue of the instance passed as input
    //
    // 'queue:9' q = queue_coder(value_type);
    ctx->q_opt.init(&Curv);
    //  Current operation
    // 'initFeedoptPlan:45' ctx.op                  = Fopt.Init;
    ctx->op = Fopt_Init;
    //  Go to the next queue
    // 'initFeedoptPlan:47' ctx.go_next             = false;
    ctx->go_next = false;
    //  Try to push again. HGS : Probably not used anymore
    // 'initFeedoptPlan:49' ctx.try_push_again      = false;
    ctx->try_push_again = false;
    //  Number of optimized queue
    // 'initFeedoptPlan:51' ctx.n_optimized         = int32( 0 );
    ctx->n_optimized = 0;
    //  Reach the last optimized queue
    // 'initFeedoptPlan:53' ctx.reached_end         = false;
    ctx->reached_end = false;
    //  Index of the element of the current queue
    // 'initFeedoptPlan:55' ctx.k0                  = int32( 1 );
    ctx->k0 = 1;
    //  Velocity at start of next queue window
    // 'initFeedoptPlan:57' ctx.v_0                 = cfg.v_0;
    ctx->v_0 = cfg.v_0;
    //  Velocity at end of next queue window
    // 'initFeedoptPlan:59' ctx.v_1                 = cfg.v_1;
    ctx->v_1 = cfg.v_1;
    //  Tangential acceleration at start of next queue window
    // 'initFeedoptPlan:61' ctx.at_0                = cfg.at_0;
    ctx->at_0 = cfg.at_0;
    //  Tangential acceleration at end of next queue window
    // 'initFeedoptPlan:63' ctx.at_1                = cfg.at_1;
    ctx->at_1 = cfg.at_1;
    //  Configuration structure with all the parameters
    // 'initFeedoptPlan:65' ctx.cfg                 = cfg;
    ctx->cfg = cfg;
    //  Number of time the maximum jerk increase
    // 'initFeedoptPlan:67' ctx.jmax_increase_count = int32(0);
    ctx->jmax_increase_count = 0;
    //  The current curv is a zero start
    // 'initFeedoptPlan:69' ctx.zero_start          = false;
    ctx->zero_start = false;
    //  The current curv is a zero end
    // 'initFeedoptPlan:71' ctx.zero_end            = false;
    ctx->zero_end = false;
    //  A zero curv has been forced, because the optimization fails
    // 'initFeedoptPlan:73' ctx.zero_forced         = false;
    ctx->zero_forced = false;
    //  A buffer to store the left and right curves use when the optimization
    //  fails
    // 'initFeedoptPlan:76' ctx.zero_forced_buffer  = [ Curv, Curv ];
    ctx->zero_forced_buffer[0] = Curv;
    ctx->zero_forced_buffer[1] = Curv;
    //  The number of time the simplex algorithm has been called. HGS : Probably
    //  not used anymore
    // 'initFeedoptPlan:79' ctx.simplex_calls       = int32(0);
    ctx->simplex_calls = 0;
    //  HGS : Don't know why this parameter is used for
    // 'initFeedoptPlan:82' ctx.forced_stop         = int32(0);
    ctx->forced_stop = 0;
    //  Counter of programmed stop during the whole computational chain
    // 'initFeedoptPlan:84' ctx.programmed_stop     = int32(0);
    ctx->programmed_stop = 0;
    //  Coeff of resulting from the optimization
    // 'initFeedoptPlan:86' ctx.Coeff               = zeros( 1, 1 );
    ctx->Coeff.set_size(1, 1);
    ctx->Coeff[0] = 0.0;
    //  HGS : Don't know what this parameter is used for
    // 'initFeedoptPlan:88' ctx.Skipped             = int32(0);
    ctx->Skipped = 0;
    //  Kinematic class used to interact with the different kinematics
    // 'initFeedoptPlan:90' ctx.kin                 = Kinematics( cfg.kin_type, cfg.kin_params );
    ctx->kin.init(cfg.kin_type, cfg.kin_params.data, cfg.kin_params.size[0]);
    // 'initFeedoptPlan:92' Curv.Info.Type          = CurveType.Spline;
    Curv.Info.Type = CurveType_Spline;
    // 'initFeedoptPlan:93' Curv.sp.Bl              = Bl;
    Curv.sp.Bl = ctx->Bl;
    //  Error message structure
    // 'initFeedoptPlan:95' ctx.errmsg              = constrMsgStructType;
    std::copy(&cv1[0], &cv1[2048], &ctx->errmsg.msg[0]);
    ctx->errmsg.size = 2048.0;
    //  Error code (a.k.a. Operation index when the error has been raised)
    // 'initFeedoptPlan:97' ctx.errcode             = FeedoptPlanError.NoError;
    ctx->errcode = FeedoptPlanError_NoError;
    // 'initFeedoptPlan:99' if ~coder.target('matlab')
    // 'initFeedoptPlan:100' coder.varsize( 'ctx.cfg.indCart',       StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:101' coder.varsize( 'ctx.cfg.indRot',        StructTypeName.dimInd{ : } );
    // 'initFeedoptPlan:102' coder.varsize( 'ctx.cfg.maskTot',       StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:103' coder.varsize( 'ctx.cfg.maskCart',      StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:104' coder.varsize( 'ctx.cfg.maskRot',       StructTypeName.dimMask{ : } );
    // 'initFeedoptPlan:105' coder.varsize( 'ctx.cfg.D',             StructTypeName.dimD{ : } );
    // 'initFeedoptPlan:106' coder.varsize( 'ctx.cfg.source',        StructTypeName.dimFileName{ : }
    // ); 'initFeedoptPlan:107' coder.varsize( 'ctx.cfg.kin_params',    StructTypeName.dimKinParams{
    // : } ); 'initFeedoptPlan:108' coder.cstructname( ctx.cfg, StructTypeName.FeedoptCfg );
    // 'initFeedoptPlan:109' coder.varsize( 'ctx.BasisVal',          StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:110' coder.varsize( 'ctx.BasisValD',         StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:111' coder.varsize( 'ctx.BasisValDD',        StructTypeName.dimBasis{ : } );
    // 'initFeedoptPlan:112' coder.varsize( 'ctx.BasisIntegr',       StructTypeName.dimBasisInt{ : }
    // ); 'initFeedoptPlan:113' coder.varsize( 'ctx.u_vec',             StructTypeName.dimCtxUvec{ :
    // } ); 'initFeedoptPlan:114' coder.varsize( 'ctx.Bl.breakpoints',
    // StructTypeName.dimCtxBlBreaks{ : } ); 'initFeedoptPlan:115' coder.varsize( 'ctx.Coeff',
    // StructTypeName.dimCtxCoeff{ : } ); 'initFeedoptPlan:116' coder.cstructname(ctx,
    // StructTypeName.FeedoptCtx );
    //  Queue of BSpline
    // 'initFeedoptPlan:119' ctx.q_spline.push( Curv );
    ctx->q_spline.push(&Curv);
}

} // namespace ocn

//
// File trailer for initFeedoptPlan.cpp
//
// [EOF]
//
