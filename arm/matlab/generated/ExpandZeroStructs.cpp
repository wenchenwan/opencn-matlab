//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ExpandZeroStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:28:22
//

// Include Files
#include "ExpandZeroStructs.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <stdio.h>

// Function Definitions
//
// function ctx = ExpandZeroStructs(ctx)
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
    static const uint64m_T r1{
        {1U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    CurvStruct Curv;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct b_CurvStruct2_C;
    uint64m_T r;
    uint64m_T r2;
    // 'ExpandZeroStructs:7' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        unsigned int Ncrv;
        int i;
        // 'ExpandZeroStructs:11' Ncrv = double(ctx.q_gcode.size);
        Ncrv = ctx->q_gcode.size();
        // 'ExpandZeroStructs:12' DebugLog(DebugCfg.Transitions, 'Expanding ...\n');
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
            printf("Expanding ...\n");
            fflush(stdout);
        }
        // 'ExpandZeroStructs:14' for k = 1:Ncrv
        i = static_cast<int>(Ncrv);
        for (int k{0}; k < i; k++) {
            // 'ExpandZeroStructs:15' Curv = ctx.q_gcode.get(k);
            ctx->q_gcode.get(static_cast<double>(k) + 1.0, &Curv);
            // 'ExpandZeroStructs:17' if Curv.zspdmode == ZSpdMode.ZN
            if (Curv.zspdmode == ZSpdMode_ZN) {
                // 'ExpandZeroStructs:18' [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv,
                // k);
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:19' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:20' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_NZ) {
                // 'ExpandZeroStructs:21' elseif Curv.zspdmode == ZSpdMode.NZ
                // 'ExpandZeroStructs:22' [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &Curv,
                           static_cast<double>(k) + 1.0, &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:23' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:24' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                // 'ExpandZeroStructs:25' elseif Curv.zspdmode == ZSpdMode.ZZ
                // 'ExpandZeroStructs:26' [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv,
                // k);
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:27' [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx,
                // CurvStruct2_C, k);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct2_C,
                           static_cast<double>(k) + 1.0, &b_CurvStruct2_C, &CurvStruct3_C);
                // 'ExpandZeroStructs:28' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:29' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&b_CurvStruct2_C);
                // 'ExpandZeroStructs:30' ctx.q_compress.push(CurvStruct3_C);
                ctx->q_compress.push(&CurvStruct3_C);
            } else {
                // 'ExpandZeroStructs:31' else
                // 'ExpandZeroStructs:32' ctx.q_compress.push(Curv);
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
