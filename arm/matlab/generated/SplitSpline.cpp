//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitSpline.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "SplitSpline.h"
#include "SplineLengthFindU_up.h"
#include "queue_coder.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"

// Function Definitions
//
// Arguments    : const FeedoptContext *ctx
//                CurvStruct *Curv
// Return Type  : void
//
namespace ocn {
void SplitSpline(const FeedoptContext *ctx, CurvStruct *Curv)
{
    CurvStruct b_ctx;
    double ux_tilda;
    ctx->q_splines.get(Curv->sp_index, &b_ctx);
    ux_tilda =
        SplineLengthFindU_up(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                             Curv->sp_index, ctx->cfg.LSplit, Curv->b_param);
    if (ux_tilda != -1.0) {
        //  if spline is not too short
        Curv->a_param = ux_tilda - Curv->b_param;
    }
    ctx->q_split.push(Curv);
}

} // namespace ocn

//
// File trailer for SplitSpline.cpp
//
// [EOF]
//
