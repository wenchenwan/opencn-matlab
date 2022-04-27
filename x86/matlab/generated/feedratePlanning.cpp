//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "feedratePlanning.h"
#include "ConstrLineStruct.h"
#include "FeedratePlanning1.h"
#include "PrintCurvStruct.h"
#include "calcZeroStartConstraints.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <stdio.h>

// Function Definitions
//
// function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
//
// Arguments    : FeedoptContext *ctx
//                bool *optimized
//                CurvStruct *opt_struct
//                bool *quit
// Return Type  : void
//
namespace ocn {
void feedratePlanning(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct, bool *quit)
{
    ::coder::array<CurvStruct, 2U> OptSegment;
    ::coder::array<double, 2U> Coeff;
    ::coder::array<double, 2U> c_ctx;
    CurvStruct NextCurv;
    CurvStruct a;
    CurvStruct b_expl_temp;
    CurvStruct b_first;
    CurvStruct expl_temp;
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    double at_0;
    double b_at_0;
    double v_0;
    int a__1;
    int status;
    bool b_optimized;
    bool b_quit;
    bool b_success;
    // 'feedratePlanning:3' trafo = false;
    //  TRAFO flag disable
    // 'feedratePlanning:4' HSC = false;
    // 'feedratePlanning:5' Poff = zeros(3, 1);
    // 'feedratePlanning:5' Aoff = Poff;
    // 'feedratePlanning:5' Uoff = Poff;
    // 'feedratePlanning:5' Doff = 0.0;
    // 'feedratePlanning:6' A0 = zeros(3,1);
    // 'feedratePlanning:6' A1 = A0;
    // 'feedratePlanning:6' U0 = A0 ;
    // 'feedratePlanning:6' U1 = A0;
    // 'feedratePlanning:8' opt_struct = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
    // 'feedratePlanning:9'     Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
    // 'feedratePlanning:10'     U1, 0.2, ZSpdMode.NN);
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
    ConstrLineStruct(false, false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2,
                     ZSpdMode_NN, opt_struct);
    // 'feedratePlanning:12' quit        = false;
    b_quit = false;
    // 'feedratePlanning:13' optimized   = false;
    b_optimized = false;
    // 'feedratePlanning:15' if ctx.q_split.isempty
    if (ctx->q_split.isempty()) {
        // 'feedratePlanning:16' if coder.target('matlab')
        // 'feedratePlanning:19' DebugLog(DebugCfg.Validate, 'Queue empty...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Queue empty...\n");
            fflush(stdout);
        }
        // 'feedratePlanning:20' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        // 'feedratePlanning:21' quit = true;
        b_quit = true;
    } else {
        // 'feedratePlanning:24' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'feedratePlanning:26' if IsEnabledDebugLog(DebugCfg.OptimProgress)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            unsigned int validatedHoleFilling_f2;
            // 'IsEnabledDebugLog:7' value = true;
            // 'feedratePlanning:27' fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
            validatedHoleFilling_f2 = ctx->q_split.size();
            printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
            fflush(stdout);
        }
        //  Increment index on q_split
        // 'feedratePlanning:31' if ctx.go_next
        if (ctx->go_next) {
            // 'feedratePlanning:32' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
            // 'feedratePlanning:33' ctx.n_optimized = ctx.n_optimized + 1;
            ctx->n_optimized++;
        }
        // 'feedratePlanning:36' if ctx.n_optimized < ctx.q_split.size
        if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
            bool guard1{false};
            // 'feedratePlanning:37' if ctx.try_push_again
            guard1 = false;
            if (ctx->try_push_again) {
                //  Do nothing, we already have the last one optimized
                guard1 = true;
            } else if (!ctx->reached_end) {
                int outsize_idx_1_tmp_tmp;
                // 'feedratePlanning:39' elseif ~ctx.reached_end
                // 'feedratePlanning:40' OptSegment = repmat(ctx.q_split.get(1), 1, ctx.cfg.NHorz);
                ctx->q_split.get(static_cast<double>(1.0), &a);
                outsize_idx_1_tmp_tmp = ctx->cfg.NHorz;
                OptSegment.set_size(1, outsize_idx_1_tmp_tmp);
                for (int i1{0}; i1 < outsize_idx_1_tmp_tmp; i1++) {
                    OptSegment[i1] = a;
                }
                // 'feedratePlanning:42' first = ctx.q_split.get(ctx.k0);
                ctx->q_split.get(ctx->k0, &b_first);
                // 'feedratePlanning:43' if first.zspdmode == ZSpdMode.ZN
                if (b_first.zspdmode == ZSpdMode_ZN) {
                    // 'feedratePlanning:44' opt_struct = first;
                    *opt_struct = b_first;
                    // 'feedratePlanning:45' optimized = true;
                    b_optimized = true;
                    // 'feedratePlanning:46' [v_0, at_0] = calcZeroStartConstraints(ctx, first);
                    calcZeroStartConstraints(&ctx->q_splines, ctx->cfg.dt, b_first.Type, b_first.P0,
                                             b_first.P1, b_first.CorrectedHelixCenter, b_first.evec,
                                             b_first.theta, b_first.pitch, b_first.CoeffP5,
                                             b_first.sp_index, b_first.ConstJerk, b_first.a_param,
                                             b_first.b_param, &ctx->v_0, &ctx->at_0);
                    // 'feedratePlanning:47' ctx.v_0 = v_0;
                    // 'feedratePlanning:48' ctx.at_0 = at_0;
                    // 'feedratePlanning:49' ctx.zero_start = true;
                    ctx->zero_start = true;
                    // 'feedratePlanning:50' quit = true;
                    b_quit = true;
                } else {
                    unsigned long u;
                    int Retry;
                    int e_loop_ub;
                    int k;
                    int k1;
                    int k1temp;
                    int kend;
                    unsigned int nopt;
                    bool exitg1;
                    bool success;
                    //  Get final index for the sliding horizon
                    // 'feedratePlanning:55' k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
                    k1temp = (ctx->k0 + outsize_idx_1_tmp_tmp) - 1;
                    // 'feedratePlanning:56' if k1temp > ctx.q_split.size
                    if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                        // 'feedratePlanning:57' ctx.reached_end = true;
                        ctx->reached_end = true;
                        // 'feedratePlanning:58' k1 = int32(ctx.q_split.size);
                        k1 = static_cast<int>(ctx->q_split.size());
                    } else {
                        // 'feedratePlanning:59' else
                        // 'feedratePlanning:60' k1 = int32(k1temp);
                        k1 = k1temp;
                    }
                    // 'feedratePlanning:63' nopt = 0;
                    nopt = 0U;
                    // 'feedratePlanning:64' DebugLog(DebugCfg.Global, 'FEEDRATE PLANNING...\n')
                    //  1 -> stdout
                    //  2 -> stderr
                    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                    // 'IsEnabledDebugLog:4' value = false;
                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                    u = static_cast<unsigned long>(DebugConfig) & 8UL;
                    if (u != 0UL) {
                        // 'IsEnabledDebugLog:7' value = true;
                        // 'DebugLog:6' fprintf(1, varargin{:});
                        printf("FEEDRATE PLANNING...\n");
                        fflush(stdout);
                    }
                    // 'feedratePlanning:65' kend = ctx.k0;
                    kend = ctx->k0;
                    // 'feedratePlanning:66' for k = ctx.k0:k1
                    k = ctx->k0;
                    exitg1 = false;
                    while ((!exitg1) && (k <= k1)) {
                        // 'feedratePlanning:67' NextCurv = ctx.q_split.get(k);
                        ctx->q_split.get(k, &NextCurv);
                        // 'feedratePlanning:68' if NextCurv.zspdmode == ZSpdMode.NZ
                        if (NextCurv.zspdmode == ZSpdMode_NZ) {
                            //  If we reach an NZ segment, we set the final velocity
                            //  and tangent acceleration constraints to the ones
                            //  specified by the segment, and pretend this is the
                            //  end of all segments
                            // 'feedratePlanning:73' [v_0, at_0] = calcZeroStartConstraints(ctx,
                            // NextCurv);
                            calcZeroStartConstraints(
                                &ctx->q_splines, ctx->cfg.dt, NextCurv.Type, NextCurv.P0,
                                NextCurv.P1, NextCurv.CorrectedHelixCenter, NextCurv.evec,
                                NextCurv.theta, NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                NextCurv.ConstJerk, NextCurv.a_param, NextCurv.b_param, &v_0,
                                &at_0);
                            // 'feedratePlanning:74' ctx.at_1 = -at_0;
                            // 'feedratePlanning:75' ctx.v_1 = v_0;
                            // 'feedratePlanning:76' ctx.zero_end = true;
                            ctx->zero_end = true;
                            // 'feedratePlanning:77' ctx.reached_end = true;
                            ctx->reached_end = true;
                            // 'feedratePlanning:78' kend = k;
                            kend = k;
                            exitg1 = true;
                        } else {
                            if (NextCurv.zspdmode == ZSpdMode_NN) {
                                // 'feedratePlanning:80' elseif NextCurv.zspdmode == ZSpdMode.NN
                                // 'feedratePlanning:81' nopt = nopt + 1;
                                nopt++;
                                // 'feedratePlanning:82' OptSegment(nopt) = NextCurv;
                                OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                // 'feedratePlanning:84' if IsEnabledDebugLog(DebugCfg.Global)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                if (u != 0UL) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'feedratePlanning:85' PrintCurvStruct(ctx,
                                    // OptSegment(k-ctx.k0+1))
                                    PrintCurvStruct(
                                        &ctx->q_splines, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                        ctx->cfg.GaussLegendreW, &OptSegment[k - ctx->k0]);
                                }
                                // 'feedratePlanning:87' if k < k1
                                if ((k < k1) && (u != 0UL)) {
                                    // 'feedratePlanning:88' DebugLog(DebugCfg.Global, ...
                                    // 'feedratePlanning:89'
                                    // '-----------------------------------\n')
                                    //  1 -> stdout
                                    //  2 -> stderr
                                    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'DebugLog:6' fprintf(1, varargin{:});
                                    printf("-----------------------------------\n");
                                    fflush(stdout);
                                }
                            } else {
                                // 'feedratePlanning:91' else
                                // 'feedratePlanning:92' error('Wrong ZspdMode');
                            }
                            k++;
                        }
                    }
                    // 'feedratePlanning:95' DebugLog(DebugCfg.Global, ...
                    // 'feedratePlanning:96' '================================================\n')
                    //  1 -> stdout
                    //  2 -> stderr
                    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                    // 'IsEnabledDebugLog:4' value = false;
                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                        // 'IsEnabledDebugLog:7' value = true;
                        // 'DebugLog:6' fprintf(1, varargin{:});
                        printf("================================================\n");
                        fflush(stdout);
                    }
                    // 'feedratePlanning:98' Retry = 0;
                    Retry = 0;
                    // 'feedratePlanning:99' success = false;
                    success = false;
                    // 'feedratePlanning:100' Coeff = [];
                    Coeff.set_size(0, 0);
                    // 'feedratePlanning:101' ctx.at_1 = ctx.cfg.at_1;
                    ctx->at_1 = ctx->cfg.at_1;
                    // 'feedratePlanning:101' ctx.v_1 = ctx.cfg.v_0;
                    ctx->v_1 = ctx->cfg.v_0;
                    // 'feedratePlanning:102' MAX_RETRY = 100;
                    // 'feedratePlanning:103' while Retry < MAX_RETRY && ~success
                    while ((Retry < 100) && (!success)) {
                        int d_ctx;
                        // 'feedratePlanning:105' if ctx.zero_start
                        if (ctx->zero_start) {
                            // 'feedratePlanning:106' [v_0, at_0] = calcZeroStartConstraints( ctx,
                            // ctx.q_split.get( ctx.k0 - 1 ) );
                            ctx->q_split.get(ctx->k0 - 1, &expl_temp);
                            calcZeroStartConstraints(
                                &ctx->q_splines, ctx->cfg.dt, expl_temp.Type, expl_temp.P0,
                                expl_temp.P1, expl_temp.CorrectedHelixCenter, expl_temp.evec,
                                expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                                expl_temp.sp_index, expl_temp.ConstJerk, expl_temp.a_param,
                                expl_temp.b_param, &ctx->v_0, &ctx->at_0);
                            // 'feedratePlanning:107' ctx.v_0 = v_0;
                            // 'feedratePlanning:108' ctx.at_0 = at_0;
                        }
                        // 'feedratePlanning:111' if ctx.zero_end
                        if (ctx->zero_end) {
                            // 'feedratePlanning:112' [v_0, at_0] = calcZeroStartConstraints( ctx,
                            // ctx.q_split.get( kend ) );
                            ctx->q_split.get(kend, &b_expl_temp);
                            expl_temp.P0[0] = b_expl_temp.P0[0];
                            expl_temp.P1[0] = b_expl_temp.P1[0];
                            expl_temp.CorrectedHelixCenter[0] = b_expl_temp.CorrectedHelixCenter[0];
                            expl_temp.evec[0] = b_expl_temp.evec[0];
                            expl_temp.P0[1] = b_expl_temp.P0[1];
                            expl_temp.P1[1] = b_expl_temp.P1[1];
                            expl_temp.CorrectedHelixCenter[1] = b_expl_temp.CorrectedHelixCenter[1];
                            expl_temp.evec[1] = b_expl_temp.evec[1];
                            expl_temp.P0[2] = b_expl_temp.P0[2];
                            expl_temp.P1[2] = b_expl_temp.P1[2];
                            expl_temp.CorrectedHelixCenter[2] = b_expl_temp.CorrectedHelixCenter[2];
                            expl_temp.evec[2] = b_expl_temp.evec[2];
                            for (int i11{0}; i11 < 6; i11++) {
                                expl_temp.CoeffP5[i11][0] = b_expl_temp.CoeffP5[i11][0];
                                expl_temp.CoeffP5[i11][1] = b_expl_temp.CoeffP5[i11][1];
                                expl_temp.CoeffP5[i11][2] = b_expl_temp.CoeffP5[i11][2];
                            }
                            calcZeroStartConstraints(
                                &ctx->q_splines, ctx->cfg.dt, b_expl_temp.Type, expl_temp.P0,
                                expl_temp.P1, expl_temp.CorrectedHelixCenter, expl_temp.evec,
                                b_expl_temp.theta, b_expl_temp.pitch, expl_temp.CoeffP5,
                                b_expl_temp.sp_index, b_expl_temp.ConstJerk, b_expl_temp.a_param,
                                b_expl_temp.b_param, &ctx->v_1, &b_at_0);
                            // 'feedratePlanning:113' ctx.at_1 = -at_0;
                            ctx->at_1 = -b_at_0;
                            // 'feedratePlanning:114' ctx.v_1 = v_0;
                        }
                        // 'feedratePlanning:117' [ctx, Coeff, ~, success, status, msg] =
                        // FeedratePlanning(ctx, OptSegment, ctx.cfg.amax, ctx.cfg.jmax,...
                        // 'feedratePlanning:118'                 ctx.BasisVal, ctx.BasisValD,
                        // ctx.BasisValDD, ctx.BasisIntegr,... 'feedratePlanning:119' ctx.Bl,
                        // ctx.u_vec, min(ctx.cfg.NHorz, nopt));
                        if (ctx->cfg.NHorz > static_cast<int>(nopt)) {
                            d_ctx = static_cast<int>(nopt);
                        } else {
                            d_ctx = ctx->cfg.NHorz;
                        }
                        FeedratePlanning(ctx, OptSegment, ctx->cfg.amax, ctx->cfg.jmax,
                                         ctx->BasisVal, ctx->BasisValD, ctx->BasisValDD,
                                         ctx->BasisIntegr, ctx->Bl.handle, ctx->u_vec, d_ctx, Coeff,
                                         &a__1, &b_success, &status);
                        success = b_success;
                        // 'feedratePlanning:120' if( ~success )
                        if (!b_success) {
                            // 'feedratePlanning:121' Retry = Retry + 1;
                            Retry++;
                            // 'feedratePlanning:122' if coder.target('matlab')
                            // 'feedratePlanning:131' if( ctx.zero_start )
                            if (ctx->zero_start &&
                                ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL)) {
                                // 'feedratePlanning:132' DebugLog(DebugCfg.Warning, 'ZeroStart at k
                                // = %d failed, halving jerk\n', ctx.k0-1);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                // 'IsEnabledDebugLog:7' value = true;
                                // 'DebugLog:6' fprintf(1, varargin{:});
                                printf("ZeroStart at k = %d failed, halving jerk\n", ctx->k0 - 1);
                                fflush(stdout);
                            }
                            // 'feedratePlanning:135' if( ctx.zero_end )
                            if (ctx->zero_end &&
                                ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL)) {
                                // 'feedratePlanning:136' DebugLog(DebugCfg.Warning, 'ZeroEnd at k =
                                // %d failed, halving jerk\n', kend);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                // 'IsEnabledDebugLog:7' value = true;
                                // 'DebugLog:6' fprintf(1, varargin{:});
                                printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                fflush(stdout);
                            }
                        }
                    }
                    // 'feedratePlanning:141' if coder.target('matlab')
                    // 'feedratePlanning:145' ctx.zero_start = false;
                    ctx->zero_start = false;
                    // 'feedratePlanning:146' ctx.zero_end = false;
                    ctx->zero_end = false;
                    // 'feedratePlanning:148' ctx.Coeff = Coeff;
                    ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
                    e_loop_ub = Coeff.size(1);
                    for (int i8{0}; i8 < e_loop_ub; i8++) {
                        int f_loop_ub;
                        f_loop_ub = Coeff.size(0);
                        for (int i9{0}; i9 < f_loop_ub; i9++) {
                            ctx->Coeff[i9 + ctx->Coeff.size(0) * i8] =
                                Coeff[i9 + Coeff.size(0) * i8];
                        }
                    }
                    // 'feedratePlanning:149' if success == 0
                    if (!success) {
                        int i10;
                        // 'feedratePlanning:150' for nprint = 1:ctx.cfg.NHorz
                        i10 = ctx->cfg.NHorz;
                        for (int nprint{0}; nprint < i10; nprint++) {
                            // 'feedratePlanning:151' if IsEnabledDebugLog(DebugCfg.Global)
                            // 'IsEnabledDebugLog:4' value = false;
                            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                            if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                                // 'IsEnabledDebugLog:7' value = true;
                                // 'feedratePlanning:152' PrintCurvStruct(ctx, OptSegment(1));
                                PrintCurvStruct(&ctx->q_splines, ctx->cfg.dt,
                                                ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                                &OptSegment[0]);
                            }
                        }
                        // 'feedratePlanning:155' if coder.target('MATLAB')
                        // 'feedratePlanning:157' else
                        // 'feedratePlanning:158' DebugLog(DebugCfg.Global, 'OPTIMIZATION
                        // FAILED!\n');
                        //  1 -> stdout
                        //  2 -> stderr
                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                        // 'IsEnabledDebugLog:4' value = false;
                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                            // 'IsEnabledDebugLog:7' value = true;
                            // 'DebugLog:6' fprintf(1, varargin{:});
                            printf("OPTIMIZATION FAILED!\n");
                            fflush(stdout);
                        }
                        // 'feedratePlanning:159' ctx.errcode = FeedoptPlanError.OptimizationFailed;
                        ctx->errcode = FeedoptPlanError_OptimizationFailed;
                        // 'feedratePlanning:161' ctx.op = Fopt.Finished;
                        ctx->op = Fopt_Finished;
                        // 'feedratePlanning:162' quit = true;
                        b_quit = true;
                    } else {
                        guard1 = true;
                    }
                }
            } else {
                int b_ctx;
                int b_loop_ub;
                int c_loop_ub;
                int i;
                int i2;
                // 'feedratePlanning:165' else
                //  If we have reached the end of the optimizing segment, we
                //  can just copy out the coefficients for the whole horizon
                // 'feedratePlanning:168' ctx.Coeff(:, 1:end-1) = ctx.Coeff(:, 2:end);
                if (2 > ctx->Coeff.size(1)) {
                    i = 0;
                    i2 = 0;
                } else {
                    i = 1;
                    i2 = ctx->Coeff.size(1);
                }
                b_ctx = ctx->Coeff.size(0) - 1;
                b_loop_ub = i2 - i;
                c_ctx.set_size(b_ctx + 1, b_loop_ub);
                for (int i4{0}; i4 < b_loop_ub; i4++) {
                    for (int i5{0}; i5 <= b_ctx; i5++) {
                        c_ctx[i5 + c_ctx.size(0) * i4] =
                            ctx->Coeff[i5 + ctx->Coeff.size(0) * (i + i4)];
                    }
                }
                c_loop_ub = c_ctx.size(1);
                for (int i6{0}; i6 < c_loop_ub; i6++) {
                    int d_loop_ub;
                    d_loop_ub = c_ctx.size(0);
                    for (int i7{0}; i7 < d_loop_ub; i7++) {
                        ctx->Coeff[i7 + ctx->Coeff.size(0) * i6] = c_ctx[i7 + c_ctx.size(0) * i6];
                    }
                }
                guard1 = true;
            }
            if (guard1) {
                int loop_ub;
                // 'feedratePlanning:171' optimized = true;
                b_optimized = true;
                // 'feedratePlanning:172' opt_struct = ctx.q_split.get(ctx.n_optimized + 1);
                ctx->q_split.get(ctx->n_optimized + 1, opt_struct);
                // 'feedratePlanning:173' opt_struct.Coeff = ctx.Coeff(:, 1);
                loop_ub = ctx->Coeff.size(0);
                opt_struct->Coeff.set_size(loop_ub);
                for (int i3{0}; i3 < loop_ub; i3++) {
                    opt_struct->Coeff[i3] = ctx->Coeff[i3];
                }
                // 'feedratePlanning:175' if opt_struct.zspdmode == ZSpdMode.NZ
                if (opt_struct->zspdmode == ZSpdMode_NZ) {
                    // 'feedratePlanning:176' ctx.reached_end = false;
                    ctx->reached_end = false;
                }
            }
        } else {
            // 'feedratePlanning:179' else
            // 'feedratePlanning:180' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
        }
    }
    *optimized = b_optimized;
    *quit = b_quit;
}

} // namespace ocn

//
// File trailer for feedratePlanning.cpp
//
// [EOF]
//
