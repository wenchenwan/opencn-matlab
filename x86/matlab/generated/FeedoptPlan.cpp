//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

// Include Files
#include "FeedoptPlan.h"
#include "CalcZeroStartConstraints.h"
#include "CheckCurvStructs.h"
#include "CompressCurvStructs.h"
#include "ConstrLineStruct.h"
#include "ExpandZeroStructs.h"
#include "FeedratePlanning_v4.h"
#include "PrintCurvStruct.h"
#include "SmoothCurvStructs.h"
#include "SplitCurvStructs.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
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
    static const char b_message[39]{'F', 'e', 'e', 'd', 'o', 'p', 't', 'P', 'l', 'a',
                                    'n', ':', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'c',
                                    'o', 'd', 'e', ' ', 'w', 'a', 's', ' ', 'n', 'o',
                                    't', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'd'};
    ::coder::array<CurvStruct, 2U> OptSegment;
    ::coder::array<double, 2U> Coeff;
    ::coder::array<double, 2U> c_ctx;
    CurvStruct NextCurv;
    CurvStruct b_CurvStruct;
    CurvStruct b_first;
    CurvStruct last;
    CurvStruct r;
    double dv[3];
    double dv1[3];
    double e_ctx[3];
    double at_0;
    double b_at_0;
    int a__1;
    char b_cv[1025];
    char message[39];
    bool b_optimized;
    bool b_success;
    bool guard1{false};
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptPlan:5' c_assert(ctx.errcode == FeedoptPlanError.Success, 'FeedoptPlan: error code
    // was not handled'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (!(ctx->errcode == FeedoptPlanError_Success)) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 39; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'FeedoptPlan:8' optimized = false;
    b_optimized = false;
    //  opt_struct = struct('Coeff', zeros(ctx.cfg.MaxNCoeff, 1),...
    //      'CurvStruct', ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN));
    //  coder.cstructname(opt_struct, 'OptCurvStruct');
    // 'FeedoptPlan:14' opt_struct = ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, opt_struct);
    // 'FeedoptPlan:16' switch ctx.op
    guard1 = false;
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:17' case Fopt.Init
        // 'FeedoptPlan:18' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        //          coder.varsize('OptSegment', [1, FeedoptLimits.MaxNHorz], [0, 0]);
        //          coder.varsize('Coeff', [FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz],
        //          [1,1]);
        //  fprintf('Starting optimization with NHorz = %d\n', ctx.cfg.NHorz);
        //
        break;
    case Fopt_GCode: {
        int status;
        // 'FeedoptPlan:25' case Fopt.GCode
        // 'FeedoptPlan:26' status = int32(ReadGCode(ReadGCodeCmd.Load, ctx.cfg.source));
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' if coder.target('mex')
        // 'ReadGCode:80' elseif coder.target('rtw')
        // 'ReadGCode:81' if cmd == ReadGCodeCmd.Load
        // 'ReadGCode:82' CurvStruct = ConstrLineStruct([1,2,3]', [4,5,6]', 0.2, ZSpdMode.NN);
        dv[0] = 1.0;
        dv1[0] = 4.0;
        dv[1] = 2.0;
        dv1[1] = 5.0;
        dv[2] = 3.0;
        dv1[2] = 6.0;
        ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, &b_CurvStruct);
        // 'ReadGCode:83' status = int32(0);
        // 'ReadGCode:84' status = coder.ceval('c_open_gcode', [filename, 0],
        // coder.ref(CurvStruct));
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = c_open_gcode(&b_cv[0], &b_CurvStruct);
        // 'FeedoptPlan:27' DebugLog(DebugCfg.Validate, 'Reading G-code...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:28' DebugLog(DebugCfg.OptimProgress, 'Reading G-code...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:29' while status
        if (status != 0) {
            dv[0] = 1.0;
            dv1[0] = 4.0;
            dv[1] = 2.0;
            dv1[1] = 5.0;
            dv[2] = 3.0;
            dv1[2] = 6.0;
        }
        while (status != 0) {
            int b_status;
            // 'FeedoptPlan:30' [status, CurvStruct] = ReadGCode(ReadGCodeCmd.Read, '');
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' if coder.target('mex')
            // 'ReadGCode:80' elseif coder.target('rtw')
            // 'ReadGCode:81' if cmd == ReadGCodeCmd.Load
            // 'ReadGCode:85' elseif cmd == ReadGCodeCmd.Read
            // 'ReadGCode:86' CurvStruct = ConstrLineStruct([1,2,3]', [4,5,6]', 0.2, ZSpdMode.NN);
            ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, &b_CurvStruct);
            // 'ReadGCode:87' status = int32(0);
            // 'ReadGCode:88' status = coder.ceval('c_read_and_exec_gcode', '',
            // coder.ref(CurvStruct));
            b_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            status = b_status;
            // 'FeedoptPlan:31' if status == 1 && CurvStruct.Type ~= 0
            if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Type) != 0)) {
                // 'FeedoptPlan:32' ctx.q_gcode.push(CurvStruct);
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:35' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:36' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:37' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:38'                 'ERROR: Optimization failed, Gcode queue is
            // empty\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("ERROR: Optimization failed, Gcode queue is empty\n");
                fflush(stdout);
            }
        } else {
            // 'FeedoptPlan:41' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:42' if last.zspdmode == ZSpdMode.NN
            if (last.zspdmode == ZSpdMode_NN) {
                // 'FeedoptPlan:43' last.zspdmode = ZSpdMode.NZ;
                last.zspdmode = ZSpdMode_NZ;
            } else if (last.zspdmode == ZSpdMode_ZN) {
                // 'FeedoptPlan:44' elseif last.zspdmode == ZSpdMode.ZN
                // 'FeedoptPlan:45' last.zspdmode = ZSpdMode.ZZ;
                last.zspdmode = ZSpdMode_ZZ;
            }
            // 'FeedoptPlan:47' ctx.q_gcode.set(ctx.q_gcode.size, last);
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:48' ctx.op = Fopt.Check;
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check:
        // 'FeedoptPlan:50' case Fopt.Check
        // 'FeedoptPlan:51' ctx = CheckCurvStructs(ctx);
        CheckCurvStructs(ctx);
        // 'FeedoptPlan:52' ctx.op = Fopt.Compress;
        ctx->op = Fopt_Compress;
        break;
    case Fopt_Compress:
        // 'FeedoptPlan:54' case Fopt.Compress
        // 'FeedoptPlan:55' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            // 'FeedoptPlan:56' ctx = ExpandZeroStructs(ctx);
            ExpandZeroStructs(ctx);
        } else {
            // 'FeedoptPlan:57' else
            // 'FeedoptPlan:58' ctx = CompressCurvStructs(ctx);
            CompressCurvStructs(ctx);
        }
        // 'FeedoptPlan:60' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        break;
    case Fopt_Smooth:
        // 'FeedoptPlan:62' case Fopt.Smooth
        // 'FeedoptPlan:63' ctx = SmoothCurvStructs(ctx);
        SmoothCurvStructs(ctx);
        // 'FeedoptPlan:64' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        break;
    case Fopt_Split:
        // 'FeedoptPlan:66' case Fopt.Split
        // 'FeedoptPlan:67' ctx = SplitCurvStructs(ctx);
        SplitCurvStructs(ctx);
        // 'FeedoptPlan:68' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:69' DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Feedrate Planning...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:70' if coder.target('matlab')
        break;
    case Fopt_Opt: {
        // 'FeedoptPlan:74' case Fopt.Opt
        // 'FeedoptPlan:75' if ctx.q_split.isempty
        if (ctx->q_split.isempty()) {
            // 'FeedoptPlan:76' if coder.target('matlab')
            // 'FeedoptPlan:79' DebugLog(DebugCfg.Validate, 'Queue empty...\n');
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
            // 'FeedoptPlan:80' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
        } else {
            // 'FeedoptPlan:83' ctx.op = Fopt.Opt;
            ctx->op = Fopt_Opt;
            // 'FeedoptPlan:85' if IsEnabledDebugLog(DebugCfg.Validate) ||
            // IsEnabledDebugLog(DebugCfg.OptimProgress) 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) ||
                ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL)) {
                unsigned int validatedHoleFilling_f2;
                // 'IsEnabledDebugLog:7' value = true;
                // 'IsEnabledDebugLog:7' value = true;
                // 'FeedoptPlan:86' fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
                validatedHoleFilling_f2 = ctx->q_split.size();
                printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
                fflush(stdout);
            } else {
                // 'IsEnabledDebugLog:4' value = false;
                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            }
            // 'FeedoptPlan:89' if ctx.go_next
            if (ctx->go_next) {
                // 'FeedoptPlan:90' ctx.k0 = ctx.k0 + 1;
                ctx->k0++;
                // 'FeedoptPlan:91' ctx.n_optimized = ctx.n_optimized + 1;
                ctx->n_optimized++;
            }
            // 'FeedoptPlan:95' if ctx.n_optimized < ctx.q_split.size
            if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
                // 'FeedoptPlan:96' if ctx.try_push_again
                if (ctx->try_push_again) {
                    //  Do nothing, we already have the last one optimized
                    guard1 = true;
                } else if (!ctx->reached_end) {
                    int varargin_2_tmp;
                    // 'FeedoptPlan:98' elseif ~ctx.reached_end
                    // 'FeedoptPlan:99' OptSegment = repmat(ctx.q_split.get(1), 1, ctx.cfg.NHorz);
                    ctx->q_split.get(static_cast<double>(1.0), &r);
                    varargin_2_tmp = ctx->cfg.NHorz;
                    OptSegment.set_size(1, varargin_2_tmp);
                    for (int i3{0}; i3 < varargin_2_tmp; i3++) {
                        OptSegment[i3] = r;
                    }
                    // 'FeedoptPlan:101' first = ctx.q_split.get(ctx.k0);
                    ctx->q_split.get(ctx->k0, &b_first);
                    // 'FeedoptPlan:102' if first.zspdmode == ZSpdMode.ZN
                    if (b_first.zspdmode == ZSpdMode_ZN) {
                        // 'FeedoptPlan:103' opt_struct = first;
                        *opt_struct = b_first;
                        // 'FeedoptPlan:104' optimized = true;
                        b_optimized = true;
                        // 'FeedoptPlan:105' [v_0, at_0] = CalcZeroStartConstraints(ctx, first, 1);
                        CalcZeroStartConstraints(
                            &ctx->q_splines, b_first.Type, b_first.P0, b_first.P1,
                            b_first.CorrectedHelixCenter, b_first.evec, b_first.theta,
                            b_first.pitch, b_first.CoeffP5, b_first.sp_index, b_first.UseConstJerk,
                            b_first.ConstJerk, b_first.a_param, b_first.b_param, 1.0, &ctx->v_0,
                            &ctx->at_0);
                        // 'FeedoptPlan:106' ctx.v_0 = v_0;
                        // 'FeedoptPlan:107' ctx.at_0 = at_0;
                        // 'FeedoptPlan:108' ctx.zero_start = true;
                        ctx->zero_start = true;
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
                        // 'FeedoptPlan:112' k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
                        k1temp = (ctx->k0 + ctx->cfg.NHorz) - 1;
                        // 'FeedoptPlan:113' if k1temp > ctx.q_split.size
                        if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                            // 'FeedoptPlan:114' ctx.reached_end = true;
                            ctx->reached_end = true;
                            // 'FeedoptPlan:115' k1 = int32(ctx.q_split.size);
                            k1 = static_cast<int>(ctx->q_split.size());
                        } else {
                            // 'FeedoptPlan:116' else
                            // 'FeedoptPlan:117' k1 = int32(k1temp);
                            k1 = k1temp;
                        }
                        // 'FeedoptPlan:120' ctx.at_1 = 0;
                        ctx->at_1 = 0.0;
                        // 'FeedoptPlan:121' ctx.v_1 = 0;
                        ctx->v_1 = 0.0;
                        // 'FeedoptPlan:123' nopt = 0;
                        nopt = 0U;
                        // 'FeedoptPlan:124' DebugLog(DebugCfg.Global, 'FEEDRATE PLANNING...\n')
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
                        // 'FeedoptPlan:125' kend = ctx.k0;
                        kend = ctx->k0;
                        // 'FeedoptPlan:126' for k = ctx.k0:k1
                        k = ctx->k0;
                        exitg1 = false;
                        while ((!exitg1) && (k <= k1)) {
                            // 'FeedoptPlan:127' NextCurv = ctx.q_split.get(k);
                            ctx->q_split.get(k, &NextCurv);
                            // 'FeedoptPlan:128' if NextCurv.zspdmode == ZSpdMode.NZ
                            if (NextCurv.zspdmode == ZSpdMode_NZ) {
                                //  If we reach an NZ segment, we set the final velocity
                                //  and tangent acceleration constraints to the ones
                                //  specified by the segment, and pretend this is the
                                //  end of all segments
                                // 'FeedoptPlan:133' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // NextCurv, 1);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                    NextCurv.CorrectedHelixCenter, NextCurv.evec, NextCurv.theta,
                                    NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                    NextCurv.UseConstJerk, NextCurv.ConstJerk, NextCurv.a_param,
                                    NextCurv.b_param, 1.0, &ctx->v_1, &at_0);
                                // 'FeedoptPlan:134' ctx.at_1 = -at_0;
                                ctx->at_1 = -at_0;
                                // 'FeedoptPlan:135' ctx.v_1 = v_0;
                                // 'FeedoptPlan:136' ctx.zero_end = true;
                                ctx->zero_end = true;
                                // 'FeedoptPlan:137' ctx.reached_end = true;
                                ctx->reached_end = true;
                                // 'FeedoptPlan:138' kend = k;
                                kend = k;
                                exitg1 = true;
                            } else {
                                if (NextCurv.zspdmode == ZSpdMode_NN) {
                                    // 'FeedoptPlan:140' elseif NextCurv.zspdmode == ZSpdMode.NN
                                    // 'FeedoptPlan:141' nopt = nopt + 1;
                                    nopt++;
                                    // 'FeedoptPlan:142' OptSegment(nopt) = NextCurv;
                                    OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                    // 'FeedoptPlan:144' if IsEnabledDebugLog(DebugCfg.Global)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    if (u != 0UL) {
                                        // 'IsEnabledDebugLog:7' value = true;
                                        // 'FeedoptPlan:145' PrintCurvStruct(ctx,
                                        // OptSegment(k-ctx.k0+1))
                                        PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                        ctx->cfg.GaussLegendreW,
                                                        &OptSegment[k - ctx->k0]);
                                    }
                                    // 'FeedoptPlan:147' if k < k1
                                    if ((k < k1) && (u != 0UL)) {
                                        // 'FeedoptPlan:148' DebugLog(DebugCfg.Global, ...
                                        // 'FeedoptPlan:149'
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
                                    // 'FeedoptPlan:151' else
                                    // 'FeedoptPlan:152' error('Wrong ZspdMode');
                                }
                                k++;
                            }
                        }
                        // 'FeedoptPlan:155' DebugLog(DebugCfg.Global, ...
                        // 'FeedoptPlan:156' '================================================\n')
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
                        // 'FeedoptPlan:158' Retry = 0;
                        Retry = 0;
                        // 'FeedoptPlan:159' success = false;
                        success = false;
                        // 'FeedoptPlan:160' Coeff = [];
                        Coeff.set_size(0, 0);
                        // 'FeedoptPlan:162' while Retry < 100 && ~success
                        while ((Retry < 100) && (!success)) {
                            int d_ctx;
                            // 'FeedoptPlan:163' [ctx, Coeff, ~, success] = FeedratePlanning_v4(ctx,
                            // OptSegment, ctx.cfg.amax, ctx.cfg.jmax,... 'FeedoptPlan:164'
                            // ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr,...
                            // 'FeedoptPlan:165'                         ctx.Bl, ctx.u_vec,
                            // min(ctx.cfg.NHorz, nopt));
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
                            // 'FeedoptPlan:167' if success == 0 && ctx.zero_start
                            if ((!b_success) && ctx->zero_start) {
                                // 'FeedoptPlan:168' DebugLog(DebugCfg.Warning, 'ZeroStart at k = %d
                                // failed, halving jerk\n', ctx.k0-1);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'DebugLog:6' fprintf(1, varargin{:});
                                    printf("ZeroStart at k = %d failed, halving jerk\n",
                                           ctx->k0 - 1);
                                    fflush(stdout);
                                }
                                // 'FeedoptPlan:169' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(ctx.k0 - 1), 0.5^Retry);
                                ctx->q_split.get(ctx->k0 - 1, &r);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, r.Type, r.P0, r.P1, r.CorrectedHelixCenter,
                                    r.evec, r.theta, r.pitch, r.CoeffP5, r.sp_index, r.UseConstJerk,
                                    r.ConstJerk, r.a_param, r.b_param,
                                    std::pow(0.5, static_cast<double>(Retry)), &ctx->v_0,
                                    &ctx->at_0);
                                // 'FeedoptPlan:170' ctx.v_0 = v_0;
                                // 'FeedoptPlan:171' ctx.at_0 = at_0;
                            }
                            // 'FeedoptPlan:174' if success == 0 && ctx.zero_end
                            if ((!b_success) && ctx->zero_end) {
                                // 'FeedoptPlan:175' DebugLog(DebugCfg.Warning, 'ZeroEnd at k = %d
                                // failed, halving jerk\n', kend);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'DebugLog:6' fprintf(1, varargin{:});
                                    printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                    fflush(stdout);
                                }
                                // 'FeedoptPlan:176' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(kend), 0.5^Retry);
                                ctx->q_split.get(kend, &r);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, r.Type, r.P0, r.P1, r.CorrectedHelixCenter,
                                    r.evec, r.theta, r.pitch, r.CoeffP5, r.sp_index, r.UseConstJerk,
                                    r.ConstJerk, r.a_param, r.b_param,
                                    std::pow(0.5, static_cast<double>(Retry)), &ctx->v_1, &b_at_0);
                                // 'FeedoptPlan:177' ctx.at_1 = -at_0;
                                ctx->at_1 = -b_at_0;
                                // 'FeedoptPlan:178' ctx.v_1 = v_0;
                            }
                            // 'FeedoptPlan:181' Retry = Retry + 1;
                            Retry++;
                        }
                        // 'FeedoptPlan:184' if coder.target('matlab')
                        // 'FeedoptPlan:188' ctx.zero_start = false;
                        ctx->zero_start = false;
                        // 'FeedoptPlan:189' ctx.zero_end = false;
                        ctx->zero_end = false;
                        // 'FeedoptPlan:191' ctx.Coeff = Coeff;
                        ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
                        e_loop_ub = Coeff.size(1);
                        for (int i9{0}; i9 < e_loop_ub; i9++) {
                            int f_loop_ub;
                            f_loop_ub = Coeff.size(0);
                            for (int i10{0}; i10 < f_loop_ub; i10++) {
                                ctx->Coeff[i10 + ctx->Coeff.size(0) * i9] =
                                    Coeff[i10 + Coeff.size(0) * i9];
                            }
                        }
                        // 'FeedoptPlan:192' if success == 0
                        if (!success) {
                            int i11;
                            // 'FeedoptPlan:193' for nprint = 1:ctx.cfg.NHorz
                            i11 = ctx->cfg.NHorz;
                            for (int nprint{0}; nprint < i11; nprint++) {
                                // 'FeedoptPlan:194' if IsEnabledDebugLog(DebugCfg.Global)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'FeedoptPlan:195' PrintCurvStruct(ctx, OptSegment(1));
                                    PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                    ctx->cfg.GaussLegendreW, &OptSegment[0]);
                                }
                            }
                            // 'FeedoptPlan:198' if coder.target('MATLAB')
                            // 'FeedoptPlan:200' else
                            // 'FeedoptPlan:201' DebugLog(DebugCfg.Global, 'OPTIMIZATION
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
                            // 'FeedoptPlan:202' ctx.errcode = FeedoptPlanError.OptimizationFailed;
                            ctx->errcode = FeedoptPlanError_OptimizationFailed;
                            // 'FeedoptPlan:204' ctx.op = Fopt.Finished;
                            ctx->op = Fopt_Finished;
                        } else {
                            guard1 = true;
                        }
                    }
                } else {
                    int b_ctx;
                    int b_loop_ub;
                    int c_loop_ub;
                    int i2;
                    int i4;
                    // 'FeedoptPlan:207' else
                    //  If we have reached the end of the optimizing segment, we
                    //  can just copy out the coefficients for the whole horizon
                    // 'FeedoptPlan:210' ctx.Coeff(:, 1:end-1) = ctx.Coeff(:, 2:end);
                    if (2 > ctx->Coeff.size(1)) {
                        i2 = 0;
                        i4 = 0;
                    } else {
                        i2 = 1;
                        i4 = ctx->Coeff.size(1);
                    }
                    b_ctx = ctx->Coeff.size(0) - 1;
                    b_loop_ub = i4 - i2;
                    c_ctx.set_size(b_ctx + 1, b_loop_ub);
                    for (int i5{0}; i5 < b_loop_ub; i5++) {
                        for (int i6{0}; i6 <= b_ctx; i6++) {
                            c_ctx[i6 + c_ctx.size(0) * i5] =
                                ctx->Coeff[i6 + ctx->Coeff.size(0) * (i2 + i5)];
                        }
                    }
                    c_loop_ub = c_ctx.size(1);
                    for (int i7{0}; i7 < c_loop_ub; i7++) {
                        int d_loop_ub;
                        d_loop_ub = c_ctx.size(0);
                        for (int i8{0}; i8 < d_loop_ub; i8++) {
                            ctx->Coeff[i8 + ctx->Coeff.size(0) * i7] =
                                c_ctx[i8 + c_ctx.size(0) * i7];
                        }
                    }
                    guard1 = true;
                }
            } else {
                // 'FeedoptPlan:221' else
                // 'FeedoptPlan:222' ctx.op = Fopt.Finished;
                ctx->op = Fopt_Finished;
            }
        }
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:225' case Fopt.Finished
        // 'FeedoptPlan:226' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:228' otherwise
        // 'FeedoptPlan:229' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("FEEDOPT: WRONG STATE\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:230' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    }
    if (guard1) {
        int loop_ub;
        // 'FeedoptPlan:213' optimized = true;
        b_optimized = true;
        // 'FeedoptPlan:214' opt_struct = ctx.q_split.get(ctx.n_optimized + 1);
        ctx->q_split.get(ctx->n_optimized + 1, opt_struct);
        // 'FeedoptPlan:215' opt_struct.Coeff = ctx.Coeff(:, 1);
        loop_ub = ctx->Coeff.size(0);
        opt_struct->Coeff.set_size(loop_ub);
        for (int i1{0}; i1 < loop_ub; i1++) {
            opt_struct->Coeff[i1] = ctx->Coeff[i1];
        }
        // 'FeedoptPlan:217' if opt_struct.zspdmode == ZSpdMode.NZ
        if (opt_struct->zspdmode == ZSpdMode_NZ) {
            // 'FeedoptPlan:218' ctx.reached_end = false;
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
