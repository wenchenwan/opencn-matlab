//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: InitFeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
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
#include "sinspace_types11.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void cast(const double t7_CoeffX[4], const double t7_CoeffY[4], const double t7_CoeffZ[4],
                 int t7_Bl_ncoeff, const ::coder::array<double, 2U> &t7_Bl_breakpoints,
                 const uint64m_T t7_Bl_handle, int t7_Bl_degree, const double t7_knots[8],
                 SplineStruct *r);

}

// Function Definitions
//
// Arguments    : const double t7_CoeffX[4]
//                const double t7_CoeffY[4]
//                const double t7_CoeffZ[4]
//                int t7_Bl_ncoeff
//                const ::coder::array<double, 2U> &t7_Bl_breakpoints
//                const uint64m_T t7_Bl_handle
//                int t7_Bl_degree
//                const double t7_knots[8]
//                SplineStruct *r
// Return Type  : void
//
namespace ocn {
static void cast(const double t7_CoeffX[4], const double t7_CoeffY[4], const double t7_CoeffZ[4],
                 int t7_Bl_ncoeff, const ::coder::array<double, 2U> &t7_Bl_breakpoints,
                 const uint64m_T t7_Bl_handle, int t7_Bl_degree, const double t7_knots[8],
                 SplineStruct *r)
{
    int loop_ub;
    r->CoeffX.set_size(1, 4);
    r->CoeffY.set_size(1, 4);
    r->CoeffZ.set_size(1, 4);
    r->CoeffX[0] = t7_CoeffX[0];
    r->CoeffY[0] = t7_CoeffY[0];
    r->CoeffZ[0] = t7_CoeffZ[0];
    r->CoeffX[1] = t7_CoeffX[1];
    r->CoeffY[1] = t7_CoeffY[1];
    r->CoeffZ[1] = t7_CoeffZ[1];
    r->CoeffX[2] = t7_CoeffX[2];
    r->CoeffY[2] = t7_CoeffY[2];
    r->CoeffZ[2] = t7_CoeffZ[2];
    r->CoeffX[3] = t7_CoeffX[3];
    r->CoeffY[3] = t7_CoeffY[3];
    r->CoeffZ[3] = t7_CoeffZ[3];
    r->Bl.ncoeff = t7_Bl_ncoeff;
    r->Bl.breakpoints.set_size(1, t7_Bl_breakpoints.size(1));
    loop_ub = t7_Bl_breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        r->Bl.breakpoints[i] = t7_Bl_breakpoints[i];
    }
    r->Bl.handle = t7_Bl_handle;
    r->Bl.degree = t7_Bl_degree;
    r->knots.set_size(1, 8);
    for (int i1{0}; i1 < 8; i1++) {
        r->knots[i1] = t7_knots[i1];
    }
    r->Lk.set_size(0, 0);
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
    uint64m_T Bl_handle;
    uint64m_T Spline_Bl_handle;
    double Spline_knots[8];
    double Spline_CoeffX[4];
    double Spline_CoeffY[4];
    double Spline_CoeffZ[4];
    double dv[3];
    double dv1[3];
    int Bl_degree;
    int Bl_ncoeff;
    int Spline_Bl_degree;
    int Spline_Bl_ncoeff;
    int g_loop_ub;
    int i_loop_ub;
    int k_loop_ub;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    if (cfg.UseLinearBreakpoints) {
        int b_loop_ub;
        coder::c_linspace(cfg.NBreak, ctx->Bl.breakpoints);
        Bl_ncoeff = (ctx->Bl.breakpoints.size(1) + cfg.SplineDegree) - 2;
        breakpoints.set_size(1, ctx->Bl.breakpoints.size(1));
        b_loop_ub = ctx->Bl.breakpoints.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            breakpoints[i1] = ctx->Bl.breakpoints[i1];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0],
                                          ctx->Bl.breakpoints.size(1));
        Bl_degree = cfg.SplineDegree;
        coder::c_linspace(cfg.NDiscr, ctx->u_vec);
    } else {
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int i2;
        int i6;
        int loop_ub;
        coder::b_linspace(cfg.NBreak, r);
        y.set_size(1, r.size(1));
        loop_ub = r.size(1);
        for (int i{0}; i < loop_ub; i++) {
            y[i] = 3.1415926535897931 * r[i];
        }
        i2 = y.size(1);
        for (int k{0}; k < i2; k++) {
            y[k] = std::cos(y[k]);
        }
        ctx->Bl.breakpoints.set_size(1, y.size(1));
        c_loop_ub = y.size(1);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            ctx->Bl.breakpoints[i3] = y[i3] * 0.5 + 0.5;
        }
        Bl_ncoeff = (ctx->Bl.breakpoints.size(1) + cfg.SplineDegree) - 2;
        breakpoints.set_size(1, ctx->Bl.breakpoints.size(1));
        d_loop_ub = ctx->Bl.breakpoints.size(1);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            breakpoints[i4] = ctx->Bl.breakpoints[i4];
        }
        c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0],
                                          ctx->Bl.breakpoints.size(1));
        Bl_degree = cfg.SplineDegree;
        coder::b_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        e_loop_ub = r.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            y[i5] = 3.1415926535897931 * r[i5];
        }
        i6 = y.size(1);
        for (int b_k{0}; b_k < i6; b_k++) {
            y[b_k] = std::cos(y[b_k]);
        }
        ctx->u_vec.set_size(1, y.size(1));
        f_loop_ub = y.size(1);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            ctx->u_vec[i7] = y[i7] * 0.5 + 0.5;
        }
    }
    bspline_base_eval(Bl_ncoeff, Bl_handle, ctx->u_vec, BasisVal, BasisValD, BasisValDD, a__1,
                      ctx->BasisIntegr);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    ConstrLineStruct(dv, dv1, 1.0, ZSpdMode_NN, &Curv);
    CalcBspline_Lee(cfg.SplineDegree, Spline_CoeffX, Spline_CoeffY, Spline_CoeffZ,
                    &Spline_Bl_ncoeff, Spline_Bl_breakpoints, &Spline_Bl_handle, &Spline_Bl_degree,
                    Spline_knots);
    cast(Spline_CoeffX, Spline_CoeffY, Spline_CoeffZ, Spline_Bl_ncoeff, Spline_Bl_breakpoints,
         Spline_Bl_handle, Spline_Bl_degree, Spline_knots, &Curv.sp);
    Curv.sp.Ltot = 0.0;
    Curv.sp.Lk.set_size(1, 1);
    Curv.sp.Lk[0] = 0.0;
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
    ctx->simplex_calls = 0;
    ctx->forced_stop = 0;
    ctx->programmed_stop = 0;
    ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    g_loop_ub = BasisVal.size(1);
    for (int i8{0}; i8 < g_loop_ub; i8++) {
        int h_loop_ub;
        h_loop_ub = BasisVal.size(0);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            ctx->BasisVal[i9 + ctx->BasisVal.size(0) * i8] = BasisVal[i9 + BasisVal.size(0) * i8];
        }
    }
    ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    i_loop_ub = BasisValD.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        int j_loop_ub;
        j_loop_ub = BasisValD.size(0);
        for (int i11{0}; i11 < j_loop_ub; i11++) {
            ctx->BasisValD[i11 + ctx->BasisValD.size(0) * i10] =
                BasisValD[i11 + BasisValD.size(0) * i10];
        }
    }
    ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
    k_loop_ub = BasisValDD.size(1);
    for (int i12{0}; i12 < k_loop_ub; i12++) {
        int l_loop_ub;
        l_loop_ub = BasisValDD.size(0);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            ctx->BasisValDD[i13 + ctx->BasisValDD.size(0) * i12] =
                BasisValDD[i13 + BasisValDD.size(0) * i12];
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
