//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ExpandZeroStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "ExpandZeroStructs.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "DebugLog.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

// Function Definitions
//
// We replace each sequence of small g-code segments with a B-Spline
//  of degree 3
//  A special queue is dedicated to the splines, ctx.q_splines
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void ExpandZeroStructs(const FeedoptContext *ctx)
{
    CurvStruct Curv;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct b_CurvStruct2_C;
    if (!ctx->q_gcode.isempty()) {
        unsigned int Ncrv;
        int i;
        Ncrv = ctx->q_gcode.size();
        k_DebugLog();
        i = static_cast<int>(Ncrv);
        for (int k{0}; k < i; k++) {
            ctx->q_gcode.get(static_cast<double>(k) + 1.0, &Curv);
            if (Curv.zspdmode == ZSpdMode_ZN) {
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_NZ) {
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &Curv,
                           static_cast<double>(k) + 1.0, &CurvStruct1_C, &CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct2_C,
                           static_cast<double>(k) + 1.0, &b_CurvStruct2_C, &CurvStruct3_C);
                ctx->q_compress.push(&CurvStruct1_C);
                ctx->q_compress.push(&b_CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct3_C);
            } else {
                ctx->q_compress.push(&Curv);
            }
        }
    }
}

} // namespace ocn

//
// File trailer for ExpandZeroStructs.cpp
//
// [EOF]
//
