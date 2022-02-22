//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: InitFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "InitFeedoptPlan.h"
#include "ConstrLineStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_initialize.h"
#include "EvalCurvStruct_types.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types2.h"
#include "EvalCurvStruct_types3.h"
#include "linspace.h"
#include "queue_coder.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function ctx = InitFeedoptPlan(cfg)
//
// Arguments    : const FeedoptConfig cfg
//                FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void InitFeedoptPlan(const FeedoptConfig cfg, FeedoptContext *ctx)
{
    static const signed char bx[4]{0, 0, 1, 0};
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> y;
    CurvStruct Curv;
    double A[4][4];
    double b_BasisVal[4][2];
    double dv9[8];
    double B[4];
    double BasisValDD0[4];
    double BasisValDD1[4];
    double X[4];
    double coef[4];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    double b_breakpoints[2];
    double u[2];
    double d;
    double d1;
    unsigned long Bl_handle;
    unsigned long b_Bl_handle;
    int Bl_degree;
    int Bl_ncoeff;
    int l_loop_ub;
    int n_loop_ub;
    int p_loop_ub;
    signed char ipiv[4];
    if (!isInitialized_EvalCurvStruct) {
        EvalCurvStruct_initialize();
    }
    // 'InitFeedoptPlan:3' coder.inline("never");
    //  ctx is the context variable, it should contain:
    //  - op: Operation to execute
    //  - go_next: Should we optimize the next segment
    //  - q_gcode: GCode queue
    //  - q_smooth: Queue for smoothed segments
    //  - q_split: Queue after splitting
    //  - q_opt: Queue after optimization
    // 'InitFeedoptPlan:12' if cfg.UseLinearBreakpoints
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        // 'InitFeedoptPlan:13' Bl = bspline_create(cfg.SplineDegree, linspace(0, 1, cfg.NBreak));
        coder::b_linspace(cfg.NBreak, ctx->Bl.breakpoints);
        // 'bspline_create:2' nbreak = length(breakpoints);
        // 'bspline_create:3' ncoeff = nbreak + degree - 2;
        Bl_ncoeff = (ctx->Bl.breakpoints.size(1) + cfg.SplineDegree) - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_create:9' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_create:10' coder.cinclude('src/c_spline.h');
        // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak));
        breakpoints.set_size(1, ctx->Bl.breakpoints.size(1));
        b_loop_ub = ctx->Bl.breakpoints.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            breakpoints[i1] = ctx->Bl.breakpoints[i1];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0],
                                          ctx->Bl.breakpoints.size(1));
        // 'bspline_create:12' Bl.ncoeff = ncoeff;
        // 'bspline_create:13' Bl.breakpoints = breakpoints;
        // 'bspline_create:14' Bl.handle = h;
        // 'bspline_create:15' Bl.degree = int32(degree);
        Bl_degree = cfg.SplineDegree;
        // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
        // 'InitFeedoptPlan:14' u_vec = linspace(0, 1, cfg.NDiscr);
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
        int e_loop_ub;
        int i;
        int i11;
        int i12;
        int i13;
        int i2;
        int i3;
        int j_loop_ub;
        int k_loop_ub;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        // 'InitFeedoptPlan:15' else
        // 'InitFeedoptPlan:16' Bl = bspline_create(cfg.SplineDegree, sinspace(0, 1, cfg.NBreak));
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
        // 'bspline_create:2' nbreak = length(breakpoints);
        // 'bspline_create:3' ncoeff = nbreak + degree - 2;
        Bl_ncoeff = (x.size(1) + cfg.SplineDegree) - 2;
        // 'bspline_create:5' h = uint64(0);
        // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_create:9' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_create:10' coder.cinclude('src/c_spline.h');
        // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h),
        // degree, breakpoints, int32(nbreak));
        ctx->Bl.breakpoints.set_size(1, x.size(1));
        d_loop_ub = x.size(1);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            ctx->Bl.breakpoints[i4] = x[i4];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &ctx->Bl.breakpoints[0],
                                          x.size(1));
        // 'bspline_create:12' Bl.ncoeff = ncoeff;
        // 'bspline_create:13' Bl.breakpoints = breakpoints;
        ctx->Bl.breakpoints.set_size(1, x.size(1));
        e_loop_ub = x.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            ctx->Bl.breakpoints[i5] = x[i5];
        }
        // 'bspline_create:14' Bl.handle = h;
        // 'bspline_create:15' Bl.degree = int32(degree);
        Bl_degree = cfg.SplineDegree;
        // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
        // 'InitFeedoptPlan:17' u_vec = sinspace(0, 1, cfg.NDiscr);
        // 'sinspace:2' t = linspace(-1,0,N);
        // 'sinspace:3' if coder.target('rtw')
        // 'sinspace:4' coder.varsize('x', [1, Inf], [0, 1]);
        // 'sinspace:6' x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
        coder::c_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        j_loop_ub = r.size(1);
        c_scalarLB = (r.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i11 = 0; i11 <= c_vectorUB; i11 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r[i11]);
            _mm_storeu_pd(&y[i11], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r4));
        }
        for (i11 = c_scalarLB; i11 < j_loop_ub; i11++) {
            y[i11] = 3.1415926535897931 * r[i11];
        }
        i12 = y.size(1);
        for (int b_k{0}; b_k < i12; b_k++) {
            y[b_k] = std::cos(y[b_k]);
        }
        ctx->u_vec.set_size(1, y.size(1));
        k_loop_ub = y.size(1);
        d_scalarLB = (y.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i13 = 0; i13 <= d_vectorUB; i13 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&y[i13]);
            r6 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&ctx->u_vec[i13], _mm_add_pd(_mm_mul_pd(r5, r6), r6));
        }
        for (i13 = d_scalarLB; i13 < k_loop_ub; i13++) {
            ctx->u_vec[i13] = y[i13] * 0.5 + 0.5;
        }
    }
    // 'InitFeedoptPlan:21' if ~coder.target('matlab')
    // 'InitFeedoptPlan:22' coder.varsize('BasisVal', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:23' coder.varsize('BasisValD', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:24' coder.varsize('BasisValDD', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:25' coder.varsize('BasisIntegr', [Inf, 1], [1 0]);
    // 'InitFeedoptPlan:27' [BasisVal, BasisValD, BasisValDD, ~, BasisIntegr] =
    // bspline_base_eval(Bl, u_vec); 'bspline_base_eval:2' if coder.target('rtw') ||
    // coder.target('mex')
    //  n, bspline_n
    // 'bspline_base_eval:4' samples = int32(numel(xvec));
    // 'bspline_base_eval:5' BasisVal = zeros(samples, Bl.ncoeff);
    BasisVal.set_size(ctx->u_vec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:6' BasisValD = BasisVal;
    BasisValD.set_size(ctx->u_vec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:7' BasisValDD = BasisVal;
    BasisValDD.set_size(ctx->u_vec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:8' BasisValDDD = BasisVal;
    a__1.set_size(ctx->u_vec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:9' BasisIntegr = BasisVal(1, :)';
    ctx->BasisIntegr.set_size(Bl_ncoeff);
    for (int i6{0}; i6 < Bl_ncoeff; i6++) {
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        f_loop_ub = ctx->u_vec.size(1);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            BasisVal[i7 + BasisVal.size(0) * i6] = 0.0;
        }
        g_loop_ub = ctx->u_vec.size(1);
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            BasisValD[i8 + BasisValD.size(0) * i6] = 0.0;
        }
        h_loop_ub = ctx->u_vec.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            BasisValDD[i9 + BasisValDD.size(0) * i6] = 0.0;
        }
        i_loop_ub = ctx->u_vec.size(1);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            a__1[i10 + a__1.size(0) * i6] = 0.0;
        }
        ctx->BasisIntegr[i6] = 0.0;
    }
    __m128d r7;
    __m128d r8;
    double z1_tmp;
    // 'bspline_base_eval:11' coder.updateBuildInfo('addSourceFiles','c_spline.c',
    // '$(START_DIR)/src'); 'bspline_base_eval:12' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.gsl.lflags); 'bspline_base_eval:13' coder.cinclude('src/c_spline.h');
    // 'bspline_base_eval:14' coder.ceval('c_bspline_base_eval', coder.rref(Bl.handle), samples,
    // coder.rref(xvec), ..., 'bspline_base_eval:15'             coder.ref(BasisVal),
    // coder.ref(BasisValD), coder.ref(BasisValDD),coder.ref(BasisValDDD),... 'bspline_base_eval:16'
    // coder.ref(BasisIntegr));
    c_bspline_base_eval(&Bl_handle, ctx->u_vec.size(1), &ctx->u_vec[0], &BasisVal[0], &BasisValD[0],
                        &BasisValDD[0], &a__1[0], &(ctx->BasisIntegr.data())[0]);
    // ,
    // 'InitFeedoptPlan:29' Coeff = zeros(0, 0);
    // 'InitFeedoptPlan:31' trafo = false;
    //  TRAFO flag disable
    // 'InitFeedoptPlan:32' Poff = zeros(3, 1);
    // 'InitFeedoptPlan:32' Aoff = Poff;
    // 'InitFeedoptPlan:32' Uoff = Poff;
    // 'InitFeedoptPlan:32' Doff = 0.0;
    // 'InitFeedoptPlan:33' A0 = zeros(3,1);
    // 'InitFeedoptPlan:33' A1 = A0;
    // 'InitFeedoptPlan:33' U0 = A0 ;
    // 'InitFeedoptPlan:33' U1 = A0;
    // 'InitFeedoptPlan:35' Curv = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
    // 'InitFeedoptPlan:36'                             Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
    // 'InitFeedoptPlan:37'                             U1, 1, ZSpdMode.NN);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv2[0] = 0.0;
    dv3[0] = 0.0;
    dv4[0] = 0.0;
    dv5[0] = 0.0;
    dv6[0] = 0.0;
    dv7[0] = 0.0;
    dv8[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv2[1] = 0.0;
    dv3[1] = 0.0;
    dv4[1] = 0.0;
    dv5[1] = 0.0;
    dv6[1] = 0.0;
    dv7[1] = 0.0;
    dv8[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    dv2[2] = 0.0;
    dv3[2] = 0.0;
    dv4[2] = 0.0;
    dv5[2] = 0.0;
    dv6[2] = 0.0;
    dv7[2] = 0.0;
    dv8[2] = 0.0;
    ConstrLineStruct(false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 1.0, ZSpdMode_NN,
                     &Curv);
    // 'InitFeedoptPlan:39' Spline = CalcBspline_Lee(cfg, [[0,0,0]', [1,1,1]']);
    // 'CalcBspline_Lee:3' [~, N] = size(points);
    //  number of points in 3D space
    // 'CalcBspline_Lee:4' du     = sum((diff(points.').^2).');
    z1_tmp = std::pow(1.0, 2.0);
    // 'CalcBspline_Lee:5' u      = cumsum([0,du.^(1/4)]);
    u[0] = 0.0;
    u[1] = std::pow((z1_tmp + z1_tmp) + z1_tmp, 0.25);
    // 'CalcBspline_Lee:6' u      = u / u(end);
    //  normalize knots to interval [0...1]
    // 'CalcBspline_Lee:7' knots  = [zeros(1, 3), u, ones(1, 3)];
    // 'CalcBspline_Lee:9' Bl = bspline_create(cfg.SplineDegree, u);
    // 'bspline_create:2' nbreak = length(breakpoints);
    // 'bspline_create:3' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:10' coder.cinclude('src/c_spline.h');
    // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak));
    r7 = _mm_loadu_pd(&u[0]);
    r8 = _mm_div_pd(r7, _mm_set1_pd(u[1]));
    _mm_storeu_pd(&u[0], r8);
    _mm_storeu_pd(&b_breakpoints[0], r8);
    c_bspline_create_with_breakpoints(&b_Bl_handle, cfg.SplineDegree, &b_breakpoints[0], 2);
    // 'bspline_create:12' Bl.ncoeff = ncoeff;
    // 'bspline_create:13' Bl.breakpoints = breakpoints;
    Curv.sp.Bl.breakpoints.set_size(1, 2);
    Curv.sp.Bl.breakpoints[0] = u[0];
    Curv.sp.Bl.breakpoints[1] = u[1];
    // 'bspline_create:14' Bl.handle = h;
    // 'bspline_create:15' Bl.degree = int32(degree);
    // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
    // 'CalcBspline_Lee:11' BasisVal    = zeros(N, N+2);
    //  preallocation
    // 'CalcBspline_Lee:12' BasisValDD0 = zeros(1, N+2);
    //  preallocation
    // 'CalcBspline_Lee:13' BasisValDD1 = zeros(1, N+2);
    //  preallocation
    //
    // 'CalcBspline_Lee:15' for k = 1:N+2
    d = u[0];
    d1 = u[1];
    for (int c_k{0}; c_k < 4; c_k++) {
        double x_idx_0;
        double xk;
        //  evaluate basis functions at the knots
        // 'CalcBspline_Lee:16' coef           = zeros(1, N+2);
        coef[0] = 0.0;
        coef[1] = 0.0;
        coef[2] = 0.0;
        coef[3] = 0.0;
        // 'CalcBspline_Lee:17' coef(:, k)     = 1;
        coef[c_k] = 1.0;
        //      sp             = spmak(knots, coef);
        //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
        // 'CalcBspline_Lee:20' BasisVal(:, k) = bspline_eval_vec(Bl, coef, u);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        xk = d;
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if coder.target('matlab')
        // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:8' if x < 0
        if (d < 0.0) {
            // 'bspline_eval:9' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", d);
            fflush(stdout);
            // 'bspline_eval:10' x = 0;
            xk = 0.0;
        } else if (d > 1.0) {
            // 'bspline_eval:11' elseif x > 1
            // 'bspline_eval:12' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", d);
            fflush(stdout);
            // 'bspline_eval:13' x = 1;
            xk = 1.0;
        }
        // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_eval:17' coder.cinclude('src/c_spline.h');
        // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:19'             x, coder.wref(X));
        c_bspline_eval(&b_Bl_handle, &coef[0], xk, &X[0]);
        // 'bspline_eval:20' x = X(1);
        x_idx_0 = X[0];
        // 'bspline_eval:21' xd = X(2);
        // 'bspline_eval:22' xdd = X(3);
        // 'bspline_eval:23' xddd = X(4);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        xk = d1;
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if coder.target('matlab')
        // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:8' if x < 0
        if (d1 < 0.0) {
            // 'bspline_eval:9' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", d1);
            fflush(stdout);
            // 'bspline_eval:10' x = 0;
            xk = 0.0;
        } else if (d1 > 1.0) {
            // 'bspline_eval:11' elseif x > 1
            // 'bspline_eval:12' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", d1);
            fflush(stdout);
            // 'bspline_eval:13' x = 1;
            xk = 1.0;
        }
        // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_eval:17' coder.cinclude('src/c_spline.h');
        // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:19'             x, coder.wref(X));
        c_bspline_eval(&b_Bl_handle, &coef[0], xk, &X[0]);
        // 'bspline_eval:20' x = X(1);
        // 'bspline_eval:21' xd = X(2);
        // 'bspline_eval:22' xdd = X(3);
        // 'bspline_eval:23' xddd = X(4);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        b_BasisVal[c_k][0] = x_idx_0;
        b_BasisVal[c_k][1] = X[0];
        //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions
        //      @u=0,1
        // 'CalcBspline_Lee:24' [~, ~, BasisValDD0(k)] = bspline_eval(Bl, coef, 0);
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if coder.target('matlab')
        // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:8' if x < 0
        // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_eval:17' coder.cinclude('src/c_spline.h');
        // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:19'             x, coder.wref(X));
        c_bspline_eval(&b_Bl_handle, &coef[0], 0.0, &X[0]);
        // 'bspline_eval:20' x = X(1);
        // 'bspline_eval:21' xd = X(2);
        // 'bspline_eval:22' xdd = X(3);
        BasisValDD0[c_k] = X[2];
        // 'bspline_eval:23' xddd = X(4);
        // 'CalcBspline_Lee:25' [~, ~, BasisValDD1(k)] = bspline_eval(Bl, coef, 1);
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if coder.target('matlab')
        // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:8' if x < 0
        // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_eval:17' coder.cinclude('src/c_spline.h');
        // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:19'             x, coder.wref(X));
        c_bspline_eval(&b_Bl_handle, &coef[0], 1.0, &X[0]);
        // 'bspline_eval:20' x = X(1);
        // 'bspline_eval:21' xd = X(2);
        // 'bspline_eval:22' xdd = X(3);
        BasisValDD1[c_k] = X[2];
        // 'bspline_eval:23' xddd = X(4);
        //      BasisValDD0(k) = spval(sp2D, 0);
        //      BasisValDD1(k) = spval(sp2D, 1);
    }
    //
    // 'CalcBspline_Lee:30' A = [BasisValDD0; BasisVal; BasisValDD1];
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    // 'CalcBspline_Lee:37' bx = [0; points(1, :)'; 0];
    // 'CalcBspline_Lee:38' by = [0; points(2, :)'; 0];
    // 'CalcBspline_Lee:39' bz = [0; points(3, :)'; 0];
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    // 'CalcBspline_Lee:46' cx = A\bx;
    for (int b_i{0}; b_i < 4; b_i++) {
        A[b_i][0] = BasisValDD0[b_i];
        A[b_i][1] = b_BasisVal[b_i][0];
        A[b_i][2] = b_BasisVal[b_i][1];
        A[b_i][3] = BasisValDD1[b_i];
        B[b_i] = bx[b_i];
        ipiv[b_i] = static_cast<signed char>(b_i + 1);
    }
    for (int j{0}; j < 3; j++) {
        double smax;
        int a;
        int b_tmp;
        int jA;
        int jp1j;
        int mmj_tmp;
        int n;
        signed char i16;
        mmj_tmp = 2 - j;
        b_tmp = j * 5;
        jp1j = b_tmp + 2;
        n = 4 - j;
        a = 0;
        smax = std::abs((&A[0][0])[b_tmp]);
        for (int f_k{2}; f_k <= n; f_k++) {
            double s;
            s = std::abs((&A[0][0])[(b_tmp + f_k) - 1]);
            if (s > smax) {
                a = f_k - 1;
                smax = s;
            }
        }
        if ((&A[0][0])[b_tmp + a] != 0.0) {
            int i15;
            if (a != 0) {
                double temp;
                int ipiv_tmp;
                ipiv_tmp = j + a;
                ipiv[j] = static_cast<signed char>(ipiv_tmp + 1);
                temp = (&A[0][0])[j];
                (&A[0][0])[j] = (&A[0][0])[ipiv_tmp];
                (&A[0][0])[ipiv_tmp] = temp;
                temp = (&A[0][0])[j + 4];
                (&A[0][0])[j + 4] = (&A[0][0])[ipiv_tmp + 4];
                (&A[0][0])[ipiv_tmp + 4] = temp;
                temp = (&A[0][0])[j + 8];
                (&A[0][0])[j + 8] = (&A[0][0])[ipiv_tmp + 8];
                (&A[0][0])[ipiv_tmp + 8] = temp;
                temp = (&A[0][0])[j + 12];
                (&A[0][0])[j + 12] = (&A[0][0])[ipiv_tmp + 12];
                (&A[0][0])[ipiv_tmp + 12] = temp;
            }
            i15 = (b_tmp - j) + 4;
            for (int e_i{jp1j}; e_i <= i15; e_i++) {
                (&A[0][0])[e_i - 1] /= (&A[0][0])[b_tmp];
            }
        }
        jA = b_tmp;
        for (int b_j{0}; b_j <= mmj_tmp; b_j++) {
            double yjy_tmp;
            yjy_tmp = (&A[0][0])[(b_tmp + (b_j << 2)) + 4];
            if (yjy_tmp != 0.0) {
                int i17;
                int i18;
                i17 = jA + 6;
                i18 = (jA - j) + 8;
                for (int ijA{i17}; ijA <= i18; ijA++) {
                    (&A[0][0])[ijA - 1] += (&A[0][0])[((b_tmp + ijA) - jA) - 5] * -yjy_tmp;
                }
            }
            jA += 4;
        }
        i16 = ipiv[j];
        if (i16 != j + 1) {
            int b_temp;
            b_temp = static_cast<int>(B[j]);
            B[j] = B[i16 - 1];
            B[i16 - 1] = b_temp;
        }
    }
    for (int d_k{0}; d_k < 4; d_k++) {
        int kAcol;
        kAcol = d_k << 2;
        if (B[d_k] != 0.0) {
            int i14;
            i14 = d_k + 2;
            for (int c_i{i14}; c_i < 5; c_i++) {
                B[c_i - 1] -= B[d_k] * (&A[0][0])[(c_i + kAcol) - 1];
            }
        }
    }
    for (int e_k{3}; e_k >= 0; e_k--) {
        double d2;
        int b_kAcol;
        b_kAcol = e_k << 2;
        d2 = B[e_k];
        if (d2 != 0.0) {
            d2 /= (&A[0][0])[e_k + b_kAcol];
            B[e_k] = d2;
            for (int d_i{0}; d_i < e_k; d_i++) {
                B[d_i] -= B[e_k] * (&A[0][0])[d_i + b_kAcol];
            }
        }
    }
    //  solve sparse banded linear system
    // 'CalcBspline_Lee:47' cy = A\by;
    //  solve sparse banded linear system
    // 'CalcBspline_Lee:48' cz = A\bz;
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    // 'CalcBspline_Lee:55' sp3D.CoeffX = cx.';
    // 'CalcBspline_Lee:56' sp3D.CoeffY = cy.';
    // 'CalcBspline_Lee:57' sp3D.CoeffZ = cz.';
    // 'CalcBspline_Lee:58' sp3D.Bl = Bl;
    // 'CalcBspline_Lee:59' sp3D.knots = knots;
    // 'InitFeedoptPlan:40' Curv.sp = Spline;
    Curv.sp.CoeffX.set_size(1, 4);
    Curv.sp.CoeffY.set_size(1, 4);
    Curv.sp.CoeffZ.set_size(1, 4);
    Curv.sp.CoeffX[0] = B[0];
    Curv.sp.CoeffY[0] = B[0];
    Curv.sp.CoeffZ[0] = B[0];
    Curv.sp.CoeffX[1] = B[1];
    Curv.sp.CoeffY[1] = B[1];
    Curv.sp.CoeffZ[1] = B[1];
    Curv.sp.CoeffX[2] = B[2];
    Curv.sp.CoeffY[2] = B[2];
    Curv.sp.CoeffZ[2] = B[2];
    Curv.sp.CoeffX[3] = B[3];
    Curv.sp.CoeffY[3] = B[3];
    Curv.sp.CoeffZ[3] = B[3];
    Curv.sp.Bl.ncoeff = cfg.SplineDegree;
    Curv.sp.Bl.handle = b_Bl_handle;
    Curv.sp.Bl.degree = cfg.SplineDegree;
    dv9[0] = 0.0;
    dv9[1] = 0.0;
    dv9[2] = 0.0;
    dv9[3] = u[0];
    dv9[4] = u[1];
    dv9[5] = 1.0;
    dv9[6] = 1.0;
    dv9[7] = 1.0;
    Curv.sp.knots.set_size(1, 8);
    for (int i19{0}; i19 < 8; i19++) {
        Curv.sp.knots[i19] = dv9[i19];
    }
    // 'InitFeedoptPlan:41' Curv.sp.Ltot = 0;
    Curv.sp.Ltot = 0.0;
    // 'InitFeedoptPlan:42' Curv.sp.Lk = 0;
    Curv.sp.Lk.set_size(1, 1);
    Curv.sp.Lk[0] = 0.0;
    // 'InitFeedoptPlan:44' ctx.op = Fopt.Init;
    ctx->op = Fopt_Init;
    // 'InitFeedoptPlan:45' ctx.go_next = false;
    ctx->go_next = false;
    // 'InitFeedoptPlan:46' ctx.q_gcode = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_gcode.init(&Curv);
    // 'InitFeedoptPlan:47' ctx.q_compress = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_compress.init(&Curv);
    // 'InitFeedoptPlan:48' ctx.q_splines = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_splines.init(&Curv);
    // 'InitFeedoptPlan:49' ctx.q_smooth = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_smooth.init(&Curv);
    // 'InitFeedoptPlan:50' ctx.q_split = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_split.init(&Curv);
    // 'InitFeedoptPlan:51' ctx.q_opt = queue(Curv);
    // 'queue:2' q = queue_coder(value_type);
    ctx->q_opt.init(&Curv);
    // 'InitFeedoptPlan:52' ctx.try_push_again = false;
    ctx->try_push_again = false;
    // 'InitFeedoptPlan:53' ctx.n_optimized = int32(0);
    ctx->n_optimized = 0;
    // 'InitFeedoptPlan:54' ctx.reached_end = false;
    ctx->reached_end = false;
    // 'InitFeedoptPlan:55' ctx.k0 = int32(1);
    ctx->k0 = 1;
    // 'InitFeedoptPlan:56' ctx.v_0 = cfg.v_0;
    ctx->v_0 = cfg.v_0;
    // 'InitFeedoptPlan:57' ctx.v_1 = cfg.v_1;
    ctx->v_1 = cfg.v_1;
    // 'InitFeedoptPlan:58' ctx.at_0 = cfg.at_0;
    ctx->at_0 = cfg.at_0;
    // 'InitFeedoptPlan:59' ctx.at_1 = cfg.at_1;
    ctx->at_1 = cfg.at_1;
    // 'InitFeedoptPlan:60' ctx.cfg = cfg;
    ctx->cfg = cfg;
    // 'InitFeedoptPlan:61' ctx.Bl = Bl;
    ctx->Bl.ncoeff = Bl_ncoeff;
    ctx->Bl.handle = Bl_handle;
    ctx->Bl.degree = Bl_degree;
    // 'InitFeedoptPlan:62' ctx.u_vec = u_vec;
    // 'InitFeedoptPlan:63' ctx.errcode = FeedoptPlanError.Success;
    ctx->errcode = FeedoptPlanError_Success;
    // 'InitFeedoptPlan:64' ctx.jmax_increase_count = int32(0);
    ctx->jmax_increase_count = 0;
    // 'InitFeedoptPlan:65' ctx.zero_start = false;
    ctx->zero_start = false;
    // 'InitFeedoptPlan:66' ctx.zero_end = false;
    ctx->zero_end = false;
    // 'InitFeedoptPlan:67' ctx.simplex_calls = int32(0);
    ctx->simplex_calls = 0;
    // 'InitFeedoptPlan:69' ctx.forced_stop = int32(0);
    ctx->forced_stop = 0;
    // 'InitFeedoptPlan:70' ctx.programmed_stop = int32(0);
    ctx->programmed_stop = 0;
    // 'InitFeedoptPlan:73' if ~coder.target('matlab')
    // 'InitFeedoptPlan:74' coder.varsize('ctx.BasisVal', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:75' coder.varsize('ctx.BasisValD', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:76' coder.varsize('ctx.BasisValDD', [Inf, Inf], [1, 1]);
    // 'InitFeedoptPlan:77' coder.varsize('ctx.BasisIntegr', [Inf, 1], [1 0]);
    // 'InitFeedoptPlan:78' coder.varsize('ctx.u_vec', [1, Inf], [0, 1]);
    // 'InitFeedoptPlan:79' coder.varsize('ctx.Coeff', [Inf, Inf], [1 1]);
    // 'InitFeedoptPlan:80' coder.varsize('ctx.Bl.breakpoints', [1, Inf], [0, 1]);
    // 'InitFeedoptPlan:83' ctx.BasisVal = BasisVal;
    ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    l_loop_ub = BasisVal.size(1);
    for (int i20{0}; i20 < l_loop_ub; i20++) {
        int m_loop_ub;
        m_loop_ub = BasisVal.size(0);
        for (int i21{0}; i21 < m_loop_ub; i21++) {
            ctx->BasisVal[i21 + ctx->BasisVal.size(0) * i20] =
                BasisVal[i21 + BasisVal.size(0) * i20];
        }
    }
    // 'InitFeedoptPlan:84' ctx.BasisValD = BasisValD;
    ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    n_loop_ub = BasisValD.size(1);
    for (int i22{0}; i22 < n_loop_ub; i22++) {
        int o_loop_ub;
        o_loop_ub = BasisValD.size(0);
        for (int i23{0}; i23 < o_loop_ub; i23++) {
            ctx->BasisValD[i23 + ctx->BasisValD.size(0) * i22] =
                BasisValD[i23 + BasisValD.size(0) * i22];
        }
    }
    // 'InitFeedoptPlan:85' ctx.BasisValDD = BasisValDD;
    ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
    p_loop_ub = BasisValDD.size(1);
    for (int i24{0}; i24 < p_loop_ub; i24++) {
        int q_loop_ub;
        q_loop_ub = BasisValDD.size(0);
        for (int i25{0}; i25 < q_loop_ub; i25++) {
            ctx->BasisValDD[i25 + ctx->BasisValDD.size(0) * i24] =
                BasisValDD[i25 + BasisValDD.size(0) * i24];
        }
    }
    // 'InitFeedoptPlan:86' ctx.BasisIntegr = BasisIntegr;
    // 'InitFeedoptPlan:88' ctx.Coeff = Coeff;
    ctx->Coeff.set_size(0, 0);
    // 'InitFeedoptPlan:89' ctx.Skipped = int32(0);
    ctx->Skipped = 0;
    // 'InitFeedoptPlan:90' coder.cstructname(ctx, 'FeedoptContext');
    //  Push the dummy spline curv
    // 'InitFeedoptPlan:93' ctx.q_splines.push(Curv);
    ctx->q_splines.push(&Curv);
}

} // namespace ocn

//
// File trailer for InitFeedoptPlan.cpp
//
// [EOF]
//
