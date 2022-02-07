//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: InitFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "InitFeedoptPlan.h"
#include "CalcBspline_Lee.h"
#include "ConstrLineStruct.h"
#include "bspline_base_eval.h"
#include "linspace.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void cast(const double t6_CoeffX[4], const double t6_CoeffY[4], const double t6_CoeffZ[4],
                 int t6_Bl_ncoeff, const ::coder::array<double, 2U> &t6_Bl_breakpoints,
                 unsigned long t6_Bl_handle, int t6_Bl_degree, const double t6_knots[8],
                 ::coder::array<double, 2U> &t7_CoeffX, ::coder::array<double, 2U> &t7_CoeffY,
                 ::coder::array<double, 2U> &t7_CoeffZ, int *t7_Bl_ncoeff,
                 ::coder::array<double, 2U> &t7_Bl_breakpoints, unsigned long *t7_Bl_handle,
                 int *t7_Bl_degree, ::coder::array<double, 2U> &t7_knots);

}

// Function Definitions
//
// Arguments    : const double t6_CoeffX[4]
//                const double t6_CoeffY[4]
//                const double t6_CoeffZ[4]
//                int t6_Bl_ncoeff
//                const ::coder::array<double, 2U> &t6_Bl_breakpoints
//                unsigned long t6_Bl_handle
//                int t6_Bl_degree
//                const double t6_knots[8]
//                ::coder::array<double, 2U> &t7_CoeffX
//                ::coder::array<double, 2U> &t7_CoeffY
//                ::coder::array<double, 2U> &t7_CoeffZ
//                int *t7_Bl_ncoeff
//                ::coder::array<double, 2U> &t7_Bl_breakpoints
//                unsigned long *t7_Bl_handle
//                int *t7_Bl_degree
//                ::coder::array<double, 2U> &t7_knots
// Return Type  : void
//
namespace ocn {
static void cast(const double t6_CoeffX[4], const double t6_CoeffY[4], const double t6_CoeffZ[4],
                 int t6_Bl_ncoeff, const ::coder::array<double, 2U> &t6_Bl_breakpoints,
                 unsigned long t6_Bl_handle, int t6_Bl_degree, const double t6_knots[8],
                 ::coder::array<double, 2U> &t7_CoeffX, ::coder::array<double, 2U> &t7_CoeffY,
                 ::coder::array<double, 2U> &t7_CoeffZ, int *t7_Bl_ncoeff,
                 ::coder::array<double, 2U> &t7_Bl_breakpoints, unsigned long *t7_Bl_handle,
                 int *t7_Bl_degree, ::coder::array<double, 2U> &t7_knots)
{
    int loop_ub;
    t7_CoeffX.set_size(1, 4);
    t7_CoeffY.set_size(1, 4);
    t7_CoeffZ.set_size(1, 4);
    t7_CoeffX[0] = t6_CoeffX[0];
    t7_CoeffY[0] = t6_CoeffY[0];
    t7_CoeffZ[0] = t6_CoeffZ[0];
    t7_CoeffX[1] = t6_CoeffX[1];
    t7_CoeffY[1] = t6_CoeffY[1];
    t7_CoeffZ[1] = t6_CoeffZ[1];
    t7_CoeffX[2] = t6_CoeffX[2];
    t7_CoeffY[2] = t6_CoeffY[2];
    t7_CoeffZ[2] = t6_CoeffZ[2];
    t7_CoeffX[3] = t6_CoeffX[3];
    t7_CoeffY[3] = t6_CoeffY[3];
    t7_CoeffZ[3] = t6_CoeffZ[3];
    t7_Bl_breakpoints.set_size(1, t6_Bl_breakpoints.size(1));
    loop_ub = t6_Bl_breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        t7_Bl_breakpoints[i] = t6_Bl_breakpoints[i];
    }
    t7_knots.set_size(1, 8);
    for (int i1{0}; i1 < 8; i1++) {
        t7_knots[i1] = t6_knots[i1];
    }
    *t7_Bl_ncoeff = t6_Bl_ncoeff;
    *t7_Bl_handle = t6_Bl_handle;
    *t7_Bl_degree = t6_Bl_degree;
}

//
// ctx is the context variable, it should contain:
//  - op: Operation to execute
//  - go_next: Should we optimize the next segment
//  - q_gcode: GCode queue
//  - q_smooth: Queue for smoothed segments
//  - q_split: Queue after splitting
//  - q_opt: Queue after optimization
//
// Arguments    : const FeedoptConfig cfg
//                FeedoptContext *ctx
// Return Type  : void
//
void InitFeedoptPlan(const FeedoptConfig cfg, FeedoptContext *ctx)
{
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> Spline_Bl_breakpoints;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> y;
    CurvStruct Curv;
    double Spline_knots[8];
    double Spline_CoeffX[4];
    double Spline_CoeffY[4];
    double Spline_CoeffZ[4];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    unsigned long Bl_handle;
    unsigned long Spline_Bl_handle;
    int Bl_degree;
    int Bl_ncoeff;
    int Spline_Bl_degree;
    int Spline_Bl_ncoeff;
    int c_scalarLB;
    int c_vectorUB;
    int d_scalarLB;
    int d_vectorUB;
    int e_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i6;
    int i8;
    int i9;
    int j_loop_ub;
    int l_loop_ub;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        int c_loop_ub;
        if (cfg.NBreak < 0) {
            y.set_size(1, 0);
        } else {
            y.set_size(1, cfg.NBreak);
            if (cfg.NBreak >= 1) {
                y[cfg.NBreak - 1] = 1.0;
                if (y.size(1) >= 2) {
                    y[0] = 0.0;
                    if (y.size(1) >= 3) {
                        double delta1;
                        int i2;
                        delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                        i2 = y.size(1);
                        for (int k{0}; k <= i2 - 3; k++) {
                            y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                        }
                    }
                }
            }
        }
        Bl_ncoeff = (y.size(1) + cfg.SplineDegree) - 2;
        ctx->Bl.breakpoints.set_size(1, y.size(1));
        b_loop_ub = y.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            ctx->Bl.breakpoints[i1] = y[i1];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &ctx->Bl.breakpoints[0],
                                          y.size(1));
        ctx->Bl.breakpoints.set_size(1, y.size(1));
        c_loop_ub = y.size(1);
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            ctx->Bl.breakpoints[i4] = y[i4];
        }
        Bl_degree = cfg.SplineDegree;
    } else {
        int b_scalarLB;
        int b_vectorUB;
        int d_loop_ub;
        int f_loop_ub;
        int i;
        int i3;
        int i5;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        coder::b_linspace(cfg.NBreak, r);
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
        i3 = y.size(1);
        for (int b_k{0}; b_k < i3; b_k++) {
            y[b_k] = std::cos(y[b_k]);
        }
        ctx->Bl.breakpoints.set_size(1, y.size(1));
        d_loop_ub = y.size(1);
        b_scalarLB = (y.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i5 = 0; i5 <= b_vectorUB; i5 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&y[i5]);
            r3 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&ctx->Bl.breakpoints[i5], _mm_add_pd(_mm_mul_pd(r2, r3), r3));
        }
        for (i5 = b_scalarLB; i5 < d_loop_ub; i5++) {
            ctx->Bl.breakpoints[i5] = y[i5] * 0.5 + 0.5;
        }
        Bl_ncoeff = (ctx->Bl.breakpoints.size(1) + cfg.SplineDegree) - 2;
        breakpoints.set_size(1, ctx->Bl.breakpoints.size(1));
        f_loop_ub = ctx->Bl.breakpoints.size(1);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            breakpoints[i7] = ctx->Bl.breakpoints[i7];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0],
                                          ctx->Bl.breakpoints.size(1));
        Bl_degree = cfg.SplineDegree;
    }
    coder::b_linspace(cfg.NDiscr, r);
    y.set_size(1, r.size(1));
    e_loop_ub = r.size(1);
    c_scalarLB = (r.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i6 = 0; i6 <= c_vectorUB; i6 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r[i6]);
        _mm_storeu_pd(&y[i6], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r4));
    }
    for (i6 = c_scalarLB; i6 < e_loop_ub; i6++) {
        y[i6] = 3.1415926535897931 * r[i6];
    }
    i8 = y.size(1);
    for (int c_k{0}; c_k < i8; c_k++) {
        y[c_k] = std::cos(y[c_k]);
    }
    ctx->u_vec.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    d_scalarLB = (y.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (i9 = 0; i9 <= d_vectorUB; i9 += 2) {
        __m128d r5;
        __m128d r6;
        r5 = _mm_loadu_pd(&y[i9]);
        r6 = _mm_set1_pd(0.5);
        _mm_storeu_pd(&ctx->u_vec[i9], _mm_add_pd(_mm_mul_pd(r5, r6), r6));
    }
    for (i9 = d_scalarLB; i9 < g_loop_ub; i9++) {
        ctx->u_vec[i9] = y[i9] * 0.5 + 0.5;
    }
    bspline_base_eval(Bl_ncoeff, Bl_handle, ctx->u_vec, BasisVal, BasisValD, BasisValDD, a__1,
                      ctx->BasisIntegr);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv2[0] = 0.0;
    dv3[0] = 0.0;
    dv4[0] = 0.0;
    dv5[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv2[1] = 0.0;
    dv3[1] = 0.0;
    dv4[1] = 0.0;
    dv5[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    dv2[2] = 0.0;
    dv3[2] = 0.0;
    dv4[2] = 0.0;
    dv5[2] = 0.0;
    ConstrLineStruct(false, dv, dv1, dv2, dv3, dv4, dv5, 1.0, ZSpdMode_NN, &Curv);
    CalcBspline_Lee(cfg.SplineDegree, Spline_CoeffX, Spline_CoeffY, Spline_CoeffZ,
                    &Spline_Bl_ncoeff, Spline_Bl_breakpoints, &Spline_Bl_handle, &Spline_Bl_degree,
                    Spline_knots);
    cast(Spline_CoeffX, Spline_CoeffY, Spline_CoeffZ, Spline_Bl_ncoeff, Spline_Bl_breakpoints,
         Spline_Bl_handle, Spline_Bl_degree, Spline_knots, Curv.sp.CoeffX, Curv.sp.CoeffY,
         Curv.sp.CoeffZ, &Curv.sp.Bl.ncoeff, Curv.sp.Bl.breakpoints, &Curv.sp.Bl.handle,
         &Curv.sp.Bl.degree, Curv.sp.knots);
    ctx->op = Fopt_Init;
    ctx->go_next = false;
    ctx->q_gcode.init(&Curv);
    ctx->q_compress.init(&Curv);
    ctx->q_splines.init(&Curv);
    ctx->q_smooth.init(&Curv);
    ctx->q_split.init(&Curv);
    ctx->q_opt.init(&Curv);
    ctx->try_push_again = false;
    ctx->n_optimized = 0;
    ctx->reached_end = false;
    ctx->k0 = 1;
    ctx->v_0 = cfg.v_0;
    ctx->v_1 = cfg.v_1;
    ctx->at_0 = cfg.at_0;
    ctx->at_1 = cfg.at_1;
    ctx->cfg = cfg;
    ctx->Bl.ncoeff = Bl_ncoeff;
    ctx->Bl.handle = Bl_handle;
    ctx->Bl.degree = Bl_degree;
    ctx->errcode = FeedoptPlanError_Success;
    ctx->jmax_increase_count = 0;
    ctx->zero_start = false;
    ctx->zero_end = false;
    ctx->forced_stop = 0;
    ctx->programmed_stop = 0;
    ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    h_loop_ub = BasisVal.size(1);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        int i_loop_ub;
        i_loop_ub = BasisVal.size(0);
        for (int i11{0}; i11 < i_loop_ub; i11++) {
            ctx->BasisVal[i11 + ctx->BasisVal.size(0) * i10] =
                BasisVal[i11 + BasisVal.size(0) * i10];
        }
    }
    ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    j_loop_ub = BasisValD.size(1);
    for (int i12{0}; i12 < j_loop_ub; i12++) {
        int k_loop_ub;
        k_loop_ub = BasisValD.size(0);
        for (int i13{0}; i13 < k_loop_ub; i13++) {
            ctx->BasisValD[i13 + ctx->BasisValD.size(0) * i12] =
                BasisValD[i13 + BasisValD.size(0) * i12];
        }
    }
    ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
    l_loop_ub = BasisValDD.size(1);
    for (int i14{0}; i14 < l_loop_ub; i14++) {
        int m_loop_ub;
        m_loop_ub = BasisValDD.size(0);
        for (int i15{0}; i15 < m_loop_ub; i15++) {
            ctx->BasisValDD[i15 + ctx->BasisValDD.size(0) * i14] =
                BasisValDD[i15 + BasisValDD.size(0) * i14];
        }
    }
    ctx->Coeff.set_size(0, 0);
    ctx->Skipped = 0;
    //  Push the dummy spline curv
    ctx->q_splines.push(&Curv);
}

} // namespace ocn

//
// File trailer for InitFeedoptPlan.cpp
//
// [EOF]
//
