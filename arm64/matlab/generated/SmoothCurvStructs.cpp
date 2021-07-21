//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SmoothCurvStructs.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "SmoothCurvStructs.h"
#include "CalcTransition.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "DebugLog.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types.h"

// Function Definitions
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
    if (!ctx->q_compress.isempty()) {
        unsigned int Ncrv;
        unsigned int k;
        ctx->q_compress.get(static_cast<double>(1.0), &b_ctx);
        //  to satisfy the coder
        Ncrv = ctx->q_compress.size();
        k_DebugLog();
        k = 1U;
        if (Ncrv > 1U) {
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            while (k < Ncrv) {
                ctx->q_compress.get(static_cast<double>(k) + 1.0, &NextCurv);
                if ((CurvStruct1.zspdmode == ZSpdMode_NN) && (NextCurv.zspdmode == ZSpdMode_NN)) {
                    b_CalcTransition(&ctx->q_splines, ctx->cfg.CutOff, ctx->cfg.CollTolDeg,
                                     ctx->cfg.NGridLengthSpline, &CurvStruct1, &NextCurv,
                                     &CurvStruct1_C, &CurvStruct_T, &CurvStruct2_C, &status);
                    if (status == TransitionResult_Ok) {
                        ctx->q_smooth.push(&CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct_T);
                        CurvStruct1 = CurvStruct2_C;
                    } else if (status == TransitionResult_Collinear) {
                        ctx->q_smooth.push(&CurvStruct1);
                        CurvStruct1 = NextCurv;
                    } else {
                        CurvStruct1.zspdmode = ZSpdMode_NZ;
                        NextCurv.zspdmode = ZSpdMode_ZN;
                        //                  SaveTransition;
                        //                  If the transition fails, force a zero-stop
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.NGridLengthSpline, &CurvStruct1, static_cast<double>(k),
                                   &CurvStruct1_C, &CurvStruct2_C);
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &NextCurv,
                                     static_cast<double>(k), &CurvStruct3_C, &CurvStruct1);
                        ctx->q_smooth.push(&CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct2_C);
                        ctx->q_smooth.push(&CurvStruct3_C);
                        ctx->forced_stop++;
                    }
                    k++;
                } else {
                    if (((CurvStruct1.zspdmode == ZSpdMode_NZ) ||
                         (CurvStruct1.zspdmode == ZSpdMode_ZZ)) &&
                        ((NextCurv.zspdmode == ZSpdMode_ZN) ||
                         (NextCurv.zspdmode == ZSpdMode_ZZ))) {
                        ctx->programmed_stop++;
                    }
                    ctx->q_smooth.push(&CurvStruct1);
                    CurvStruct1 = NextCurv;
                    k++;
                }
            }
            ctx->q_smooth.push(&CurvStruct1);
        } else if (static_cast<int>(Ncrv) == 1) {
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            if (CurvStruct1.zspdmode == ZSpdMode_ZZ) {
                b_CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                               ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                               ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                               ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &CurvStruct1,
                               &CurvStruct1_C, &CurvStruct2_C);
                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                           ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                           ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                           ctx->cfg.NGridLengthSpline, &CurvStruct2_C, &b_CurvStruct2_C,
                           &CurvStruct3_C);
                ctx->q_smooth.push(&CurvStruct1_C);
                ctx->q_smooth.push(&b_CurvStruct2_C);
                ctx->q_smooth.push(&CurvStruct3_C);
            } else {
                for (int i1{0}; i1 < 28; i1++) {
                    c_message[i1] = d_message[i1];
                }
                c_assert_(&c_message[0]);
            }
        } else {
            for (int i{0}; i < 27; i++) {
                message[i] = b_message[i];
            }
            c_assert_(&message[0]);
        }
    }
}

} // namespace ocn

//
// File trailer for SmoothCurvStructs.cpp
//
// [EOF]
//
