//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ExpandZeroStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

// Include Files
#include "ExpandZeroStructs.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <stdio.h>

// Function Definitions
//
// function ctx = ExpandZeroStructs(ctx)
//
// ExpandZeroStructs :
//  - Is feeded by the queue : q_gcode
//  - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves if
//  they contain a zero speed.
//  - Fill the queue : q_compress
//
//  Note : No compression is performed
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
    // 'ExpandZeroStructs:10' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        unsigned int Ncrv;
        int i;
        // 'ExpandZeroStructs:14' Ncrv = double(ctx.q_gcode.size);
        Ncrv = ctx->q_gcode.size();
        // 'ExpandZeroStructs:15' DebugLog(DebugCfg.Transitions, 'Expanding ...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Expanding ...\n");
            fflush(stdout);
        }
        // 'ExpandZeroStructs:17' for k = 1:Ncrv
        i = static_cast<int>(Ncrv);
        for (int k{0}; k < i; k++) {
            // 'ExpandZeroStructs:18' Curv = ctx.q_gcode.get(k);
            ctx->q_gcode.get(static_cast<double>(k) + 1.0, &Curv);
            // 'ExpandZeroStructs:20' if Curv.zspdmode == ZSpdMode.ZN
            if (Curv.zspdmode == ZSpdMode_ZN) {
                // 'ExpandZeroStructs:21' [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv,
                // k);
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:22' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:23' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_NZ) {
                // 'ExpandZeroStructs:24' elseif Curv.zspdmode == ZSpdMode.NZ
                // 'ExpandZeroStructs:25' [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &Curv,
                           static_cast<double>(k) + 1.0, &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:26' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:27' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&CurvStruct2_C);
            } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                // 'ExpandZeroStructs:28' elseif Curv.zspdmode == ZSpdMode.ZZ
                // 'ExpandZeroStructs:29' [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv,
                // k);
                CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                             ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                             ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                             ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                             ctx->cfg.GaussLegendreW, &Curv, static_cast<double>(k) + 1.0,
                             &CurvStruct1_C, &CurvStruct2_C);
                // 'ExpandZeroStructs:30' [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx,
                // CurvStruct2_C, k);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct2_C,
                           static_cast<double>(k) + 1.0, &b_CurvStruct2_C, &CurvStruct3_C);
                // 'ExpandZeroStructs:31' ctx.q_compress.push(CurvStruct1_C);
                ctx->q_compress.push(&CurvStruct1_C);
                // 'ExpandZeroStructs:32' ctx.q_compress.push(CurvStruct2_C);
                ctx->q_compress.push(&b_CurvStruct2_C);
                // 'ExpandZeroStructs:33' ctx.q_compress.push(CurvStruct3_C);
                ctx->q_compress.push(&CurvStruct3_C);
            } else {
                // 'ExpandZeroStructs:34' else
                // 'ExpandZeroStructs:35' ctx.q_compress.push(Curv);
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
