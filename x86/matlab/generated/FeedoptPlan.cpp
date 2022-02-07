//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "FeedoptPlan.h"
#include "CalcZeroStartConstraints.h"
#include "CheckCurvStructs.h"
#include "CompressCurvStructs.h"
#include "ConstrLineStruct.h"
#include "DebugLog.h"
#include "ExpandZeroStructs.h"
#include "FeedratePlanning_v4.h"
#include "PrintCurvStruct.h"
#include "ReadGCode.h"
#include "SmoothCurvStructs.h"
#include "SplitCurvStructs.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// See InitFeedoptPlan for information about the context variable ctx
//
// Arguments    : FeedoptContext *ctx
//                bool *optimized
//                CurvStruct *opt_struct
// Return Type  : void
//
namespace ocn {
void FeedoptPlan(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct)
{
    ::coder::array<CurvStruct, 2U> OptSegment;
    ::coder::array<double, 2U> Coeff;
    ::coder::array<double, 2U> c_ctx;
    CurvStruct NextCurv;
    CurvStruct a;
    CurvStruct b_CurvStruct;
    CurvStruct b_expl_temp;
    CurvStruct b_first;
    CurvStruct expl_temp;
    CurvStruct last;
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double e_ctx[3];
    double at_0;
    double b_at_0;
    int a__1;
    bool b_optimized;
    bool b_success;
    bool guard1{false};
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    c_c_assert(ctx->errcode == FeedoptPlanError_Success);
    b_optimized = false;
    //  opt_struct = struct('Coeff', zeros(ctx.cfg.MaxNCoeff, 1),...
    //      'CurvStruct', ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN));
    //  coder.cstructname(opt_struct, 'OptCurvStruct');
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
    ConstrLineStruct(false, dv, dv1, dv2, dv3, dv4, dv5, 0.2, ZSpdMode_NN, opt_struct);
    guard1 = false;
    switch (ctx->op) {
    case Fopt_Init:
        ctx->op = Fopt_GCode;
        //          coder.varsize('OptSegment', [1, FeedoptLimits.MaxNHorz], [0, 0]);
        //          coder.varsize('Coeff', [FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz],
        //          [1,1]);
        //  fprintf('Starting optimization with NHorz = %d\n', ctx.cfg.NHorz);
        //
        break;
    case Fopt_GCode: {
        int status;
        status = ReadGCode(ctx->cfg.source);
        f_DebugLog();
        if (status != 0) {
            dv[0] = 1.0;
            dv1[0] = 4.0;
            dv2[0] = 0.0;
            dv3[0] = 0.0;
            dv4[0] = 0.0;
            dv5[0] = 0.0;
            dv[1] = 2.0;
            dv1[1] = 5.0;
            dv2[1] = 0.0;
            dv3[1] = 0.0;
            dv4[1] = 0.0;
            dv5[1] = 0.0;
            dv[2] = 3.0;
            dv1[2] = 6.0;
            dv2[2] = 0.0;
            dv3[2] = 0.0;
            dv4[2] = 0.0;
            dv5[2] = 0.0;
        }
        while (status != 0) {
            int b_status;
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            ConstrLineStruct(false, dv, dv1, dv2, dv3, dv4, dv5, 0.2, ZSpdMode_NN, &b_CurvStruct);
            b_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            status = b_status;
            if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Type) != 0)) {
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        if (ctx->q_gcode.isempty()) {
            ctx->op = Fopt_Finished;
            g_DebugLog();
        } else {
            ctx->q_gcode.rget(&last);
            if (last.zspdmode == ZSpdMode_NN) {
                last.zspdmode = ZSpdMode_NZ;
            } else if (last.zspdmode == ZSpdMode_ZN) {
                last.zspdmode = ZSpdMode_ZZ;
            }
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check:
        CheckCurvStructs(ctx);
        ctx->op = Fopt_Compress;
        break;
    case Fopt_Compress:
        if (ctx->cfg.Compressing.Skip) {
            ExpandZeroStructs(ctx);
        } else {
            CompressCurvStructs(ctx);
        }
        ctx->op = Fopt_Smooth;
        break;
    case Fopt_Smooth:
        SmoothCurvStructs(ctx);
        ctx->op = Fopt_Split;
        break;
    case Fopt_Split:
        SplitCurvStructs(ctx);
        ctx->op = Fopt_Opt;
        m_DebugLog();
        break;
    case Fopt_Opt: {
        if (ctx->q_split.isempty()) {
            n_DebugLog();
            ctx->op = Fopt_Finished;
        } else {
            ctx->op = Fopt_Opt;
            if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
                unsigned int validatedHoleFilling_f2;
                validatedHoleFilling_f2 = ctx->q_split.size();
                printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
                fflush(stdout);
            }
            if (ctx->go_next) {
                ctx->k0++;
                ctx->n_optimized++;
            }
            if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
                if (ctx->try_push_again) {
                    //  Do nothing, we already have the last one optimized
                    guard1 = true;
                } else if (!ctx->reached_end) {
                    int outsize_idx_1_tmp_tmp;
                    ctx->q_split.get(static_cast<double>(1.0), &a);
                    outsize_idx_1_tmp_tmp = ctx->cfg.NHorz;
                    OptSegment.set_size(1, outsize_idx_1_tmp_tmp);
                    for (int i2{0}; i2 < outsize_idx_1_tmp_tmp; i2++) {
                        OptSegment[i2] = a;
                    }
                    ctx->q_split.get(ctx->k0, &b_first);
                    if (b_first.zspdmode == ZSpdMode_ZN) {
                        *opt_struct = b_first;
                        b_optimized = true;
                        CalcZeroStartConstraints(
                            &ctx->q_splines, b_first.Type, b_first.P0, b_first.P1,
                            b_first.CorrectedHelixCenter, b_first.evec, b_first.theta,
                            b_first.pitch, b_first.CoeffP5, b_first.sp_index, b_first.UseConstJerk,
                            b_first.ConstJerk, b_first.a_param, b_first.b_param, 1.0, &ctx->v_0,
                            &ctx->at_0);
                        ctx->zero_start = true;
                    } else {
                        int Retry;
                        int e_loop_ub;
                        int k;
                        int k1;
                        int k1temp;
                        int kend;
                        unsigned int nopt;
                        bool exitg1;
                        bool success;
                        k1temp = (ctx->k0 + outsize_idx_1_tmp_tmp) - 1;
                        if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                            ctx->reached_end = true;
                            k1 = static_cast<int>(ctx->q_split.size());
                        } else {
                            k1 = k1temp;
                        }
                        ctx->at_1 = 0.0;
                        ctx->v_1 = 0.0;
                        nopt = 0U;
                        o_DebugLog();
                        kend = ctx->k0;
                        k = ctx->k0;
                        exitg1 = false;
                        while ((!exitg1) && (k <= k1)) {
                            ctx->q_split.get(k, &NextCurv);
                            if (NextCurv.zspdmode == ZSpdMode_NZ) {
                                //  If we reach an NZ segment, we set the final velocity
                                //  and tangent acceleration constraints to the ones
                                //  specified by the segment, and pretend this is the
                                //  end of all segments
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                    NextCurv.CorrectedHelixCenter, NextCurv.evec, NextCurv.theta,
                                    NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                    NextCurv.UseConstJerk, NextCurv.ConstJerk, NextCurv.a_param,
                                    NextCurv.b_param, 1.0, &ctx->v_1, &at_0);
                                ctx->at_1 = -at_0;
                                ctx->zero_end = true;
                                ctx->reached_end = true;
                                kend = k;
                                exitg1 = true;
                            } else {
                                if (NextCurv.zspdmode == ZSpdMode_NN) {
                                    nopt++;
                                    OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                                        b_PrintCurvStruct(&ctx->q_splines,
                                                          ctx->cfg.NGridLengthSpline,
                                                          &OptSegment[k - ctx->k0]);
                                    }
                                    if (k < k1) {
                                        p_DebugLog();
                                    }
                                }
                                k++;
                            }
                        }
                        q_DebugLog();
                        Retry = 0;
                        success = false;
                        Coeff.set_size(0, 0);
                        while ((Retry < 100) && (!success)) {
                            int d_ctx;
                            if (ctx->cfg.NHorz > static_cast<int>(nopt)) {
                                d_ctx = static_cast<int>(nopt);
                            } else {
                                d_ctx = ctx->cfg.NHorz;
                            }
                            e_ctx[0] = ctx->cfg.jmax[0];
                            e_ctx[1] = ctx->cfg.jmax[1];
                            e_ctx[2] = ctx->cfg.jmax[2];
                            FeedratePlanning_v4(ctx, OptSegment, ctx->cfg.amax, e_ctx,
                                                ctx->BasisVal, ctx->BasisValD, ctx->BasisValDD,
                                                ctx->BasisIntegr, ctx->Bl.handle, ctx->u_vec, d_ctx,
                                                Coeff, &a__1, &b_success);
                            success = b_success;
                            if ((!b_success) && ctx->zero_start) {
                                DebugLog(ctx->k0 - 1);
                                ctx->q_split.get(ctx->k0 - 1, &expl_temp);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, expl_temp.Type, expl_temp.P0, expl_temp.P1,
                                    expl_temp.CorrectedHelixCenter, expl_temp.evec, expl_temp.theta,
                                    expl_temp.pitch, expl_temp.CoeffP5, expl_temp.sp_index,
                                    expl_temp.UseConstJerk, expl_temp.ConstJerk, expl_temp.a_param,
                                    expl_temp.b_param, std::pow(0.5, static_cast<double>(Retry)),
                                    &ctx->v_0, &ctx->at_0);
                            }
                            if ((!b_success) && ctx->zero_end) {
                                b_DebugLog(kend);
                                ctx->q_split.get(kend, &b_expl_temp);
                                expl_temp.P0[0] = b_expl_temp.P0[0];
                                expl_temp.P1[0] = b_expl_temp.P1[0];
                                expl_temp.CorrectedHelixCenter[0] =
                                    b_expl_temp.CorrectedHelixCenter[0];
                                expl_temp.evec[0] = b_expl_temp.evec[0];
                                expl_temp.P0[1] = b_expl_temp.P0[1];
                                expl_temp.P1[1] = b_expl_temp.P1[1];
                                expl_temp.CorrectedHelixCenter[1] =
                                    b_expl_temp.CorrectedHelixCenter[1];
                                expl_temp.evec[1] = b_expl_temp.evec[1];
                                expl_temp.P0[2] = b_expl_temp.P0[2];
                                expl_temp.P1[2] = b_expl_temp.P1[2];
                                expl_temp.CorrectedHelixCenter[2] =
                                    b_expl_temp.CorrectedHelixCenter[2];
                                expl_temp.evec[2] = b_expl_temp.evec[2];
                                for (int i11{0}; i11 < 6; i11++) {
                                    expl_temp.CoeffP5[i11][0] = b_expl_temp.CoeffP5[i11][0];
                                    expl_temp.CoeffP5[i11][1] = b_expl_temp.CoeffP5[i11][1];
                                    expl_temp.CoeffP5[i11][2] = b_expl_temp.CoeffP5[i11][2];
                                }
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, b_expl_temp.Type, expl_temp.P0, expl_temp.P1,
                                    expl_temp.CorrectedHelixCenter, expl_temp.evec,
                                    b_expl_temp.theta, b_expl_temp.pitch, expl_temp.CoeffP5,
                                    b_expl_temp.sp_index, b_expl_temp.UseConstJerk,
                                    b_expl_temp.ConstJerk, b_expl_temp.a_param, b_expl_temp.b_param,
                                    std::pow(0.5, static_cast<double>(Retry)), &ctx->v_1, &b_at_0);
                                ctx->at_1 = -b_at_0;
                            }
                            Retry++;
                        }
                        ctx->zero_start = false;
                        ctx->zero_end = false;
                        ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
                        e_loop_ub = Coeff.size(1);
                        for (int i8{0}; i8 < e_loop_ub; i8++) {
                            int f_loop_ub;
                            f_loop_ub = Coeff.size(0);
                            for (int i10{0}; i10 < f_loop_ub; i10++) {
                                ctx->Coeff[i10 + ctx->Coeff.size(0) * i8] =
                                    Coeff[i10 + Coeff.size(0) * i8];
                            }
                        }
                        if (!success) {
                            int i9;
                            i9 = ctx->cfg.NHorz;
                            for (int nprint{0}; nprint < i9; nprint++) {
                                if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                                    b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                                      &OptSegment[0]);
                                }
                            }
                            w_DebugLog();
                            ctx->errcode = FeedoptPlanError_OptimizationFailed;
                            ctx->op = Fopt_Finished;
                        } else {
                            guard1 = true;
                        }
                    }
                } else {
                    int b_ctx;
                    int b_loop_ub;
                    int c_loop_ub;
                    int i1;
                    int i3;
                    //  If we have reached the end of the optimizing segment, we
                    //  can just copy out the coefficients for the whole horizon
                    if (2 > ctx->Coeff.size(1)) {
                        i1 = 0;
                        i3 = 0;
                    } else {
                        i1 = 1;
                        i3 = ctx->Coeff.size(1);
                    }
                    b_ctx = ctx->Coeff.size(0) - 1;
                    b_loop_ub = i3 - i1;
                    c_ctx.set_size(b_ctx + 1, b_loop_ub);
                    for (int i4{0}; i4 < b_loop_ub; i4++) {
                        for (int i5{0}; i5 <= b_ctx; i5++) {
                            c_ctx[i5 + c_ctx.size(0) * i4] =
                                ctx->Coeff[i5 + ctx->Coeff.size(0) * (i1 + i4)];
                        }
                    }
                    c_loop_ub = c_ctx.size(1);
                    for (int i6{0}; i6 < c_loop_ub; i6++) {
                        int d_loop_ub;
                        d_loop_ub = c_ctx.size(0);
                        for (int i7{0}; i7 < d_loop_ub; i7++) {
                            ctx->Coeff[i7 + ctx->Coeff.size(0) * i6] =
                                c_ctx[i7 + c_ctx.size(0) * i6];
                        }
                    }
                    guard1 = true;
                }
            } else {
                ctx->op = Fopt_Finished;
            }
        }
    } break;
    case Fopt_Finished:
        ctx->op = Fopt_Finished;
        break;
    default:
        x_DebugLog();
        ctx->op = Fopt_Finished;
        break;
    }
    if (guard1) {
        int loop_ub;
        b_optimized = true;
        ctx->q_split.get(ctx->n_optimized + 1, opt_struct);
        loop_ub = ctx->Coeff.size(0);
        opt_struct->Coeff.set_size(loop_ub);
        for (int i{0}; i < loop_ub; i++) {
            opt_struct->Coeff[i] = ctx->Coeff[i];
        }
        if (opt_struct->zspdmode == ZSpdMode_NZ) {
            ctx->reached_end = false;
        }
    }
    *optimized = b_optimized;
}

} // namespace ocn

//
// File trailer for FeedoptPlan.cpp
//
// [EOF]
//
