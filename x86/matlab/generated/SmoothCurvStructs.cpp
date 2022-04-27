//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SmoothCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "SmoothCurvStructs.h"
#include "CalcTransition.h"
#include "cutZeroEnd.h"
#include "cutZeroStart.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <stdio.h>

// Function Definitions
//
// function ctx = SmoothCurvStructs(ctx)
//
// Optimal transitions calculation between segments whith G2 continuity
//
// Arguments    : FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void SmoothCurvStructs(FeedoptContext *ctx)
{
    static const char d_message[28]{'S', 'i', 'n', 'g', 'l', 'e', ' ', 'C', 'u', 'r',
                                    'v', 'S', 't', 'r', 'u', 'c', 't', ' ', 'w', 'a',
                                    's', ' ', 'n', 'o', 't', ' ', 'Z', 'Z'};
    static const char b_message[27]{'C', 'o', 'm', 'p', 'r', 'e', 's', 's', 'i',
                                    'n', 'g', ' ', 'q', 'u', 'e', 'u', 'e', ' ',
                                    'i', 's', ' ', 'e', 'm', 'p', 't', 'y', '!'};
    CurvStruct CurvStruct1;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct CurvStruct_T;
    CurvStruct NextCurv;
    CurvStruct b_CurvStruct2_C;
    CurvStruct b_ctx;
    char c_message[28];
    char message[27];
    TransitionResult status;
    // 'SmoothCurvStructs:4' if ctx.q_compress.isempty()
    if (!ctx->q_compress.isempty()) {
        unsigned int Ncrv;
        unsigned int k;
        // 'SmoothCurvStructs:8' if coder.target('rtw')
        // 'SmoothCurvStructs:9' NextCurv = ctx.q_compress.get(1);
        ctx->q_compress.get(static_cast<double>(1.0), &b_ctx);
        //  to satisfy the coder
        // 'SmoothCurvStructs:11' Ncrv = ctx.q_compress.size;
        Ncrv = ctx->q_compress.size();
        // 'SmoothCurvStructs:13' DebugLog(DebugCfg.Validate, 'Smoothing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'SmoothCurvStructs:14' DebugLog(DebugCfg.OptimProgress, 'Smoothing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'SmoothCurvStructs:16' k = 1;
        k = 1U;
        // 'SmoothCurvStructs:18' if Ncrv > 1
        if (Ncrv > 1U) {
            // 'SmoothCurvStructs:19' CurvStruct1 = ctx.q_compress.get(k);
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            //  get current curv in q_compress
            // 'SmoothCurvStructs:20' while k < Ncrv
            while (k < Ncrv) {
                // 'SmoothCurvStructs:21' NextCurv = ctx.q_compress.get(k+1);
                ctx->q_compress.get(static_cast<double>(k) + 1.0, &NextCurv);
                //  get next curv in q_compress
                //  Check neither of the two curves has a zero speed.
                // 'SmoothCurvStructs:23' if CurvStruct1.zspdmode == ZSpdMode.NN ...
                // 'SmoothCurvStructs:24'            && NextCurv.zspdmode == ZSpdMode.NN
                if ((CurvStruct1.zspdmode == ZSpdMode_NN) && (NextCurv.zspdmode == ZSpdMode_NN)) {
                    // 'SmoothCurvStructs:25' [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status] =
                    // ... 'SmoothCurvStructs:26'                 CalcTransition(ctx, CurvStruct1,
                    // NextCurv);
                    b_CalcTransition(&ctx->q_splines, ctx->cfg.CutOff, ctx->cfg.dt,
                                     ctx->cfg.ColTolCos, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &CurvStruct1, &NextCurv,
                                     &CurvStruct1_C, &CurvStruct_T, &CurvStruct2_C, &status);
                    // 'SmoothCurvStructs:28' if status == TransitionResult.Ok
                    if (status == TransitionResult_Ok) {
                        // 'SmoothCurvStructs:29' ctx.q_smooth.push(CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct1_C);
                        // 'SmoothCurvStructs:30' ctx.q_smooth.push(CurvStruct_T);
                        ctx->q_smooth.push(&CurvStruct_T);
                        // 'SmoothCurvStructs:31' CurvStruct1 = CurvStruct2_C;
                        CurvStruct1 = CurvStruct2_C;
                    } else if (status == TransitionResult_Collinear) {
                        // 'SmoothCurvStructs:32' elseif status == TransitionResult.Collinear
                        // 'SmoothCurvStructs:33' ctx.q_smooth.push(CurvStruct1);
                        ctx->q_smooth.push(&CurvStruct1);
                        // 'SmoothCurvStructs:34' CurvStruct1 = NextCurv;
                        CurvStruct1 = NextCurv;
                    } else {
                        // 'SmoothCurvStructs:35' else
                        // 'SmoothCurvStructs:36' CurvStruct1.zspdmode = ZSpdMode.NZ;
                        CurvStruct1.zspdmode = ZSpdMode_NZ;
                        // 'SmoothCurvStructs:37' NextCurv.zspdmode = ZSpdMode.ZN;
                        NextCurv.zspdmode = ZSpdMode_ZN;
                        // 'SmoothCurvStructs:38' CurvStruct2 = NextCurv;
                        //                  SaveTransition;
                        //                  If the transition fails, force a zero-stop
                        // 'SmoothCurvStructs:41' [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd(ctx,
                        // CurvStruct1);
                        cutZeroEnd(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                   &CurvStruct1, &CurvStruct1_C, &CurvStruct2_C);
                        // 'SmoothCurvStructs:42' [CurvStruct3_C, CurvStruct4_C] = cutZeroStart(ctx,
                        // NextCurv);
                        cutZeroStart(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                     &NextCurv, &CurvStruct3_C, &CurvStruct1);
                        // 'SmoothCurvStructs:43' ctx.q_smooth.push(CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct1_C);
                        // 'SmoothCurvStructs:44' ctx.q_smooth.push(CurvStruct2_C);
                        ctx->q_smooth.push(&CurvStruct2_C);
                        // 'SmoothCurvStructs:45' ctx.q_smooth.push(CurvStruct3_C);
                        ctx->q_smooth.push(&CurvStruct3_C);
                        // 'SmoothCurvStructs:46' CurvStruct1 = CurvStruct4_C;
                        // 'SmoothCurvStructs:48' ctx.forced_stop = ctx.forced_stop + 1;
                        ctx->forced_stop++;
                    }
                    // 'SmoothCurvStructs:50' k = k + 1;
                    k++;
                } else {
                    // 'SmoothCurvStructs:51' else
                    // 'SmoothCurvStructs:53' if (CurvStruct1.zspdmode == ZSpdMode.NZ ||
                    // CurvStruct1.zspdmode == ZSpdMode.ZZ) ... 'SmoothCurvStructs:54' &&
                    // (NextCurv.zspdmode == ZSpdMode.ZN || NextCurv.zspdmode == ZSpdMode.ZZ)
                    if (((CurvStruct1.zspdmode == ZSpdMode_NZ) ||
                         (CurvStruct1.zspdmode == ZSpdMode_ZZ)) &&
                        ((NextCurv.zspdmode == ZSpdMode_ZN) ||
                         (NextCurv.zspdmode == ZSpdMode_ZZ))) {
                        // 'SmoothCurvStructs:55' ctx.programmed_stop = ctx.programmed_stop + 1;
                        ctx->programmed_stop++;
                    }
                    // 'SmoothCurvStructs:58' ctx.q_smooth.push(CurvStruct1);
                    ctx->q_smooth.push(&CurvStruct1);
                    // 'SmoothCurvStructs:59' CurvStruct1 = NextCurv;
                    CurvStruct1 = NextCurv;
                    // 'SmoothCurvStructs:60' k = k + 1;
                    k++;
                }
            }
            // 'SmoothCurvStructs:64' ctx.q_smooth.push(CurvStruct1);
            ctx->q_smooth.push(&CurvStruct1);
        } else if (static_cast<int>(Ncrv) == 1) {
            // 'SmoothCurvStructs:67' elseif Ncrv==1
            // 'SmoothCurvStructs:68' CurvStruct1 = ctx.q_compress.get(1);
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            // 'SmoothCurvStructs:69' if CurvStruct1.zspdmode == ZSpdMode.ZZ
            if (CurvStruct1.zspdmode == ZSpdMode_ZZ) {
                // 'SmoothCurvStructs:70' [CurvStruct1_C, CurvStruct2_C] = cutZeroStart(ctx,
                // CurvStruct1);
                cutZeroStart(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                             &CurvStruct1, &CurvStruct1_C, &CurvStruct2_C);
                // 'SmoothCurvStructs:71' [CurvStruct2_C, CurvStruct3_C] = cutZeroEnd(ctx,
                // CurvStruct2_C);
                cutZeroEnd(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                           &CurvStruct2_C, &b_CurvStruct2_C, &CurvStruct3_C);
                // 'SmoothCurvStructs:72' ctx.q_smooth.push(CurvStruct1_C);
                ctx->q_smooth.push(&CurvStruct1_C);
                // 'SmoothCurvStructs:73' ctx.q_smooth.push(CurvStruct2_C);
                ctx->q_smooth.push(&b_CurvStruct2_C);
                // 'SmoothCurvStructs:74' ctx.q_smooth.push(CurvStruct3_C);
                ctx->q_smooth.push(&CurvStruct3_C);
            } else {
                // 'SmoothCurvStructs:75' else
                // 'SmoothCurvStructs:76' c_assert(false, 'Single CurvStruct was not ZZ');
                // 'c_assert:2' if coder.target('rtw')
                // 'c_assert:3' if ~condition
                // 'c_assert:4' coder.ceval('c_assert_', message);
                for (int i1{0}; i1 < 28; i1++) {
                    c_message[i1] = d_message[i1];
                }
                c_assert_(&c_message[0]);
                // 'c_assert:6' value = condition;
            }
        } else {
            // 'SmoothCurvStructs:78' else
            // 'SmoothCurvStructs:79' c_assert(false, 'Compressing queue is empty!');
            // 'c_assert:2' if coder.target('rtw')
            // 'c_assert:3' if ~condition
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i{0}; i < 27; i++) {
                message[i] = b_message[i];
            }
            c_assert_(&message[0]);
            // 'c_assert:6' value = condition;
        }
    }
}

} // namespace ocn

//
// File trailer for SmoothCurvStructs.cpp
//
// [EOF]
//
