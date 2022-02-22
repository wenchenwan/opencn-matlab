//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 21-Feb-2022 17:59:00
//

// Include Files
#include "FeedoptPlan.h"
#include "CalcZeroStartConstraints.h"
#include "CheckCurvStructs.h"
#include "CompressCurvStructs.h"
#include "ConstrLineStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_initialize.h"
#include "EvalCurvStruct_rtwutil.h"
#include "EvalCurvStruct_types.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types11.h"
#include "EvalCurvStruct_types2.h"
#include "EvalCurvStruct_types3.h"
#include "ExpandZeroStructs.h"
#include "FeedratePlanning_v4.h"
#include "PrintCurvStruct.h"
#include "SmoothCurvStructs.h"
#include "SplitCurvStructs.h"
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
    static const uint64m_T r1{
        {8U, 0U} // chunks
    };
    static const uint64m_T r14{
        {2U, 0U} // chunks
    };
    static const uint64m_T r29{
        {16U, 0U} // chunks
    };
    static const uint64m_T r4{
        {0U, 0U} // chunks
    };
    static const uint64m_T r6{
        {128U, 0U} // chunks
    };
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
    CurvStruct r15;
    uint64m_T r;
    uint64m_T r10;
    uint64m_T r11;
    uint64m_T r12;
    uint64m_T r13;
    uint64m_T r16;
    uint64m_T r18;
    uint64m_T r2;
    uint64m_T r20;
    uint64m_T r21;
    uint64m_T r23;
    uint64m_T r25;
    uint64m_T r26;
    uint64m_T r28;
    uint64m_T r3;
    uint64m_T r30;
    uint64m_T r31;
    uint64m_T r32;
    uint64m_T r33;
    uint64m_T r34;
    uint64m_T r35;
    uint64m_T r36;
    uint64m_T r37;
    uint64m_T r7;
    uint64m_T r8;
    uint64m_T r9;
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    double e_ctx[3];
    double at_0;
    double b_at_0;
    int a__1;
    char b_cv[1025];
    char message[39];
    bool b_optimized;
    bool b_success;
    bool guard1{false};
    if (!isInitialized_EvalCurvStruct) {
        EvalCurvStruct_initialize();
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
    // 'FeedoptPlan:10' trafo = false;
    //  TRAFO flag disable
    // 'FeedoptPlan:11' Poff = zeros(3, 1);
    // 'FeedoptPlan:11' Aoff = Poff;
    // 'FeedoptPlan:11' Uoff = Poff;
    // 'FeedoptPlan:11' Doff = 0.0;
    // 'FeedoptPlan:12' A0 = zeros(3,1);
    // 'FeedoptPlan:12' A1 = A0;
    // 'FeedoptPlan:12' U0 = A0 ;
    // 'FeedoptPlan:12' U1 = A0;
    // 'FeedoptPlan:14' opt_struct = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
    // 'FeedoptPlan:15'                                Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
    // 'FeedoptPlan:16'                                U1, 0.2, ZSpdMode.NN);
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
    ConstrLineStruct(false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2, ZSpdMode_NN,
                     opt_struct);
    // 'FeedoptPlan:18' switch ctx.op
    guard1 = false;
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:19' case Fopt.Init
        // 'FeedoptPlan:20' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        break;
    case Fopt_GCode: {
        uint64m_T r19;
        uint64m_T r22;
        int status;
        // 'FeedoptPlan:21' case Fopt.GCode
        // 'FeedoptPlan:22' status = int32(ReadGCode(ReadGCodeCmd.Load, ctx.cfg.source));
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' if coder.target('mex')
        // 'ReadGCode:89' elseif coder.target('rtw')
        // 'ReadGCode:90' trafo = false;
        //  TRAFO flag disable
        // 'ReadGCode:91' Poff = zeros(3, 1);
        // 'ReadGCode:91' Aoff = Poff;
        // 'ReadGCode:91' Uoff = Poff;
        // 'ReadGCode:91' Doff = 0.0;
        // 'ReadGCode:92' A0 = zeros(3,1);
        // 'ReadGCode:92' A1 = A0;
        // 'ReadGCode:92' U0 = A0 ;
        // 'ReadGCode:92' U1 = A0;
        // 'ReadGCode:94' if cmd == ReadGCodeCmd.Load
        // 'ReadGCode:96' CurvStruct = ConstrLineStruct(trafo, Poff, Aoff, ...
        // 'ReadGCode:97'                                       Uoff, Doff, [1,2,3]', [4,5,6]', ...
        // 'ReadGCode:98'                                       A0, A1, U0, U1, 0.2, ZSpdMode.NN);
        dv[0] = 0.0;
        dv1[0] = 0.0;
        dv2[0] = 0.0;
        dv3[0] = 1.0;
        dv4[0] = 4.0;
        dv5[0] = 0.0;
        dv6[0] = 0.0;
        dv7[0] = 0.0;
        dv8[0] = 0.0;
        dv[1] = 0.0;
        dv1[1] = 0.0;
        dv2[1] = 0.0;
        dv3[1] = 2.0;
        dv4[1] = 5.0;
        dv5[1] = 0.0;
        dv6[1] = 0.0;
        dv7[1] = 0.0;
        dv8[1] = 0.0;
        dv[2] = 0.0;
        dv1[2] = 0.0;
        dv2[2] = 0.0;
        dv3[2] = 3.0;
        dv4[2] = 6.0;
        dv5[2] = 0.0;
        dv6[2] = 0.0;
        dv7[2] = 0.0;
        dv8[2] = 0.0;
        ConstrLineStruct(false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2, ZSpdMode_NN,
                         &b_CurvStruct);
        // 'ReadGCode:100' status = int32(0);
        // 'ReadGCode:101' status = coder.ceval('c_open_gcode', [filename, 0],
        // coder.ref(CurvStruct));
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = c_open_gcode(&b_cv[0], &b_CurvStruct);
        // 'FeedoptPlan:23' DebugLog(DebugCfg.Validate, 'Reading G-code...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r18.chunks[0U]);
        r19 = r6;
        MultiWordAnd((unsigned int *)&r18.chunks[0U], (unsigned int *)&r6.chunks[0U],
                     (unsigned int *)&r20.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r20.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:24' DebugLog(DebugCfg.OptimProgress, 'Reading G-code...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r21.chunks[0U]);
        r22 = r14;
        MultiWordAnd((unsigned int *)&r21.chunks[0U], (unsigned int *)&r14.chunks[0U],
                     (unsigned int *)&r19.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r19.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:25' while status
        if (status != 0) {
            dv[0] = 0.0;
            dv1[0] = 0.0;
            dv2[0] = 0.0;
            dv3[0] = 1.0;
            dv4[0] = 4.0;
            dv5[0] = 0.0;
            dv6[0] = 0.0;
            dv7[0] = 0.0;
            dv8[0] = 0.0;
            dv[1] = 0.0;
            dv1[1] = 0.0;
            dv2[1] = 0.0;
            dv3[1] = 2.0;
            dv4[1] = 5.0;
            dv5[1] = 0.0;
            dv6[1] = 0.0;
            dv7[1] = 0.0;
            dv8[1] = 0.0;
            dv[2] = 0.0;
            dv1[2] = 0.0;
            dv2[2] = 0.0;
            dv3[2] = 3.0;
            dv4[2] = 6.0;
            dv5[2] = 0.0;
            dv6[2] = 0.0;
            dv7[2] = 0.0;
            dv8[2] = 0.0;
        }
        while (status != 0) {
            int b_status;
            // 'FeedoptPlan:26' [status, CurvStruct] = ReadGCode(ReadGCodeCmd.Read, '');
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' if coder.target('mex')
            // 'ReadGCode:89' elseif coder.target('rtw')
            // 'ReadGCode:90' trafo = false;
            //  TRAFO flag disable
            // 'ReadGCode:91' Poff = zeros(3, 1);
            // 'ReadGCode:91' Aoff = Poff;
            // 'ReadGCode:91' Uoff = Poff;
            // 'ReadGCode:91' Doff = 0.0;
            // 'ReadGCode:92' A0 = zeros(3,1);
            // 'ReadGCode:92' A1 = A0;
            // 'ReadGCode:92' U0 = A0 ;
            // 'ReadGCode:92' U1 = A0;
            // 'ReadGCode:94' if cmd == ReadGCodeCmd.Load
            // 'ReadGCode:102' elseif cmd == ReadGCodeCmd.Read
            // 'ReadGCode:104' CurvStruct = ConstrLineStruct(trafo, Poff, Aoff, ...
            // 'ReadGCode:105'                                       Uoff, Doff, [1,2,3]', [4,5,6]',
            // ... 'ReadGCode:106'                                       A0, A1, U0, U1, 0.2,
            // ZSpdMode.NN);
            ConstrLineStruct(false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2,
                             ZSpdMode_NN, &b_CurvStruct);
            // 'ReadGCode:107' status = int32(0);
            // 'ReadGCode:108' status = coder.ceval('c_read_and_exec_gcode', '',
            // coder.ref(CurvStruct));
            b_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            status = b_status;
            // 'FeedoptPlan:27' if status == 1 && CurvStruct.Type ~= 0
            if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Type) != 0)) {
                // 'FeedoptPlan:28' ctx.q_gcode.push(CurvStruct);
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:31' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:32' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:33' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:34'                 'ERROR: Optimization failed, Gcode queue is
            // empty\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r28.chunks[0U]);
            MultiWordAnd((unsigned int *)&r28.chunks[0U], (unsigned int *)&r29.chunks[0U],
                         (unsigned int *)&r22.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r22.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("ERROR: Optimization failed, Gcode queue is empty\n");
                fflush(stdout);
            }
        } else {
            // 'FeedoptPlan:37' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:38' if last.zspdmode == ZSpdMode.NN
            if (last.zspdmode == ZSpdMode_NN) {
                // 'FeedoptPlan:39' last.zspdmode = ZSpdMode.NZ;
                last.zspdmode = ZSpdMode_NZ;
            } else if (last.zspdmode == ZSpdMode_ZN) {
                // 'FeedoptPlan:40' elseif last.zspdmode == ZSpdMode.ZN
                // 'FeedoptPlan:41' last.zspdmode = ZSpdMode.ZZ;
                last.zspdmode = ZSpdMode_ZZ;
            }
            // 'FeedoptPlan:43' ctx.q_gcode.set(ctx.q_gcode.size, last);
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:44' ctx.op = Fopt.Check;
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check:
        // 'FeedoptPlan:46' case Fopt.Check
        // 'FeedoptPlan:47' ctx = CheckCurvStructs(ctx);
        CheckCurvStructs(ctx);
        // 'FeedoptPlan:48' ctx.op = Fopt.Compress;
        ctx->op = Fopt_Compress;
        break;
    case Fopt_Compress:
        // 'FeedoptPlan:50' case Fopt.Compress
        // 'FeedoptPlan:51' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            // 'FeedoptPlan:52' ctx = ExpandZeroStructs(ctx);
            ExpandZeroStructs(ctx);
        } else {
            // 'FeedoptPlan:53' else
            // 'FeedoptPlan:54' ctx = CompressCurvStructs(ctx);
            CompressCurvStructs(ctx);
        }
        // 'FeedoptPlan:56' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        break;
    case Fopt_Smooth:
        // 'FeedoptPlan:58' case Fopt.Smooth
        // 'FeedoptPlan:59' ctx = SmoothCurvStructs(ctx);
        SmoothCurvStructs(ctx);
        // 'FeedoptPlan:60' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        break;
    case Fopt_Split:
        // 'FeedoptPlan:62' case Fopt.Split
        // 'FeedoptPlan:63' ctx = SplitCurvStructs(ctx);
        SplitCurvStructs(ctx);
        // 'FeedoptPlan:64' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:65' DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r9.chunks[0U]);
        MultiWordAnd((unsigned int *)&r9.chunks[0U], (unsigned int *)&r6.chunks[0U],
                     (unsigned int *)&r11.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r11.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Feedrate Planning...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:66' if coder.target('matlab')
        break;
    case Fopt_Opt: {
        // 'FeedoptPlan:70' case Fopt.Opt
        // 'FeedoptPlan:71' if ctx.q_split.isempty
        if (ctx->q_split.isempty()) {
            // 'FeedoptPlan:72' if coder.target('matlab')
            // 'FeedoptPlan:75' DebugLog(DebugCfg.Validate, 'Queue empty...\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r8.chunks[0U]);
            MultiWordAnd((unsigned int *)&r8.chunks[0U], (unsigned int *)&r6.chunks[0U],
                         (unsigned int *)&r10.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r10.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Queue empty...\n");
                fflush(stdout);
            }
            // 'FeedoptPlan:76' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
        } else {
            uint64m_T r5;
            bool guard2{false};
            // 'FeedoptPlan:79' ctx.op = Fopt.Opt;
            ctx->op = Fopt_Opt;
            // 'FeedoptPlan:81' if IsEnabledDebugLog(DebugCfg.Validate) ||
            // IsEnabledDebugLog(DebugCfg.OptimProgress) 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r3.chunks[0U]);
            r5 = r6;
            MultiWordAnd((unsigned int *)&r3.chunks[0U], (unsigned int *)&r6.chunks[0U],
                         (unsigned int *)&r7.chunks[0U]);
            guard2 = false;
            if (uMultiWordNe((unsigned int *)&r7.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                guard2 = true;
            } else {
                // 'IsEnabledDebugLog:4' value = false;
                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                Double2MultiWord(DebugConfig, (unsigned int *)&r12.chunks[0U]);
                r13 = r14;
                MultiWordAnd((unsigned int *)&r12.chunks[0U], (unsigned int *)&r14.chunks[0U],
                             (unsigned int *)&r5.chunks[0U]);
                if (uMultiWordNe((unsigned int *)&r5.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                    // 'IsEnabledDebugLog:7' value = true;
                    guard2 = true;
                }
            }
            if (guard2) {
                unsigned int validatedHoleFilling_f2;
                // 'FeedoptPlan:82' fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
                validatedHoleFilling_f2 = ctx->q_split.size();
                printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
                fflush(stdout);
            }
            // 'FeedoptPlan:85' if ctx.go_next
            if (ctx->go_next) {
                // 'FeedoptPlan:86' ctx.k0 = ctx.k0 + 1;
                ctx->k0++;
                // 'FeedoptPlan:87' ctx.n_optimized = ctx.n_optimized + 1;
                ctx->n_optimized++;
            }
            // 'FeedoptPlan:91' if ctx.n_optimized < ctx.q_split.size
            if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
                // 'FeedoptPlan:92' if ctx.try_push_again
                if (ctx->try_push_again) {
                    //  Do nothing, we already have the last one optimized
                    guard1 = true;
                } else if (!ctx->reached_end) {
                    int varargin_2_tmp;
                    // 'FeedoptPlan:94' elseif ~ctx.reached_end
                    // 'FeedoptPlan:95' OptSegment = repmat(ctx.q_split.get(1), 1, ctx.cfg.NHorz);
                    ctx->q_split.get(static_cast<double>(1.0), &r15);
                    varargin_2_tmp = ctx->cfg.NHorz;
                    OptSegment.set_size(1, varargin_2_tmp);
                    for (int i3{0}; i3 < varargin_2_tmp; i3++) {
                        OptSegment[i3] = r15;
                    }
                    // 'FeedoptPlan:97' first = ctx.q_split.get(ctx.k0);
                    ctx->q_split.get(ctx->k0, &b_first);
                    // 'FeedoptPlan:98' if first.zspdmode == ZSpdMode.ZN
                    if (b_first.zspdmode == ZSpdMode_ZN) {
                        // 'FeedoptPlan:99' opt_struct = first;
                        *opt_struct = b_first;
                        // 'FeedoptPlan:100' optimized = true;
                        b_optimized = true;
                        // 'FeedoptPlan:101' [v_0, at_0] = CalcZeroStartConstraints(ctx, first, 1);
                        CalcZeroStartConstraints(
                            &ctx->q_splines, b_first.Type, b_first.P0, b_first.P1,
                            b_first.CorrectedHelixCenter, b_first.evec, b_first.theta,
                            b_first.pitch, b_first.CoeffP5, b_first.sp_index, b_first.UseConstJerk,
                            b_first.ConstJerk, b_first.a_param, b_first.b_param, 1.0, &ctx->v_0,
                            &ctx->at_0);
                        // 'FeedoptPlan:102' ctx.v_0 = v_0;
                        // 'FeedoptPlan:103' ctx.at_0 = at_0;
                        // 'FeedoptPlan:104' ctx.zero_start = true;
                        ctx->zero_start = true;
                    } else {
                        uint64m_T r17;
                        uint64m_T r24;
                        int Retry;
                        int e_loop_ub;
                        int k;
                        int k1;
                        int k1temp;
                        int kend;
                        unsigned int nopt;
                        bool exitg1;
                        bool success;
                        // 'FeedoptPlan:108' k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
                        k1temp = (ctx->k0 + ctx->cfg.NHorz) - 1;
                        // 'FeedoptPlan:109' if k1temp > ctx.q_split.size
                        if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                            // 'FeedoptPlan:110' ctx.reached_end = true;
                            ctx->reached_end = true;
                            // 'FeedoptPlan:111' k1 = int32(ctx.q_split.size);
                            k1 = static_cast<int>(ctx->q_split.size());
                        } else {
                            // 'FeedoptPlan:112' else
                            // 'FeedoptPlan:113' k1 = int32(k1temp);
                            k1 = k1temp;
                        }
                        // 'FeedoptPlan:116' ctx.at_1 = 0;
                        ctx->at_1 = 0.0;
                        // 'FeedoptPlan:117' ctx.v_1 = 0;
                        ctx->v_1 = 0.0;
                        // 'FeedoptPlan:119' nopt = 0;
                        nopt = 0U;
                        // 'FeedoptPlan:120' DebugLog(DebugCfg.Global, 'FEEDRATE PLANNING...\n')
                        //  1 -> stdout
                        //  2 -> stderr
                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                        // 'IsEnabledDebugLog:4' value = false;
                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                        Double2MultiWord(DebugConfig, (unsigned int *)&r16.chunks[0U]);
                        r17 = r1;
                        MultiWordAnd((unsigned int *)&r16.chunks[0U],
                                     (unsigned int *)&r1.chunks[0U],
                                     (unsigned int *)&r13.chunks[0U]);
                        if (uMultiWordNe((unsigned int *)&r13.chunks[0U],
                                         (unsigned int *)&r4.chunks[0U])) {
                            // 'IsEnabledDebugLog:7' value = true;
                            // 'DebugLog:6' fprintf(1, varargin{:});
                            printf("FEEDRATE PLANNING...\n");
                            fflush(stdout);
                        }
                        // 'FeedoptPlan:121' kend = ctx.k0;
                        kend = ctx->k0;
                        // 'FeedoptPlan:122' for k = ctx.k0:k1
                        k = ctx->k0;
                        exitg1 = false;
                        while ((!exitg1) && (k <= k1)) {
                            // 'FeedoptPlan:123' NextCurv = ctx.q_split.get(k);
                            ctx->q_split.get(k, &NextCurv);
                            // 'FeedoptPlan:124' if NextCurv.zspdmode == ZSpdMode.NZ
                            if (NextCurv.zspdmode == ZSpdMode_NZ) {
                                //  If we reach an NZ segment, we set the final velocity
                                //  and tangent acceleration constraints to the ones
                                //  specified by the segment, and pretend this is the
                                //  end of all segments
                                // 'FeedoptPlan:129' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // NextCurv, 1);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                    NextCurv.CorrectedHelixCenter, NextCurv.evec, NextCurv.theta,
                                    NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                    NextCurv.UseConstJerk, NextCurv.ConstJerk, NextCurv.a_param,
                                    NextCurv.b_param, 1.0, &ctx->v_1, &at_0);
                                // 'FeedoptPlan:130' ctx.at_1 = -at_0;
                                ctx->at_1 = -at_0;
                                // 'FeedoptPlan:131' ctx.v_1 = v_0;
                                // 'FeedoptPlan:132' ctx.zero_end = true;
                                ctx->zero_end = true;
                                // 'FeedoptPlan:133' ctx.reached_end = true;
                                ctx->reached_end = true;
                                // 'FeedoptPlan:134' kend = k;
                                kend = k;
                                exitg1 = true;
                            } else {
                                if (NextCurv.zspdmode == ZSpdMode_NN) {
                                    uint64m_T r27;
                                    // 'FeedoptPlan:136' elseif NextCurv.zspdmode == ZSpdMode.NN
                                    // 'FeedoptPlan:137' nopt = nopt + 1;
                                    nopt++;
                                    // 'FeedoptPlan:138' OptSegment(nopt) = NextCurv;
                                    OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                    // 'FeedoptPlan:140' if IsEnabledDebugLog(DebugCfg.Global)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    Double2MultiWord(DebugConfig, (unsigned int *)&r26.chunks[0U]);
                                    r27 = r1;
                                    MultiWordAnd((unsigned int *)&r26.chunks[0U],
                                                 (unsigned int *)&r1.chunks[0U],
                                                 (unsigned int *)&r17.chunks[0U]);
                                    r26 = r4;
                                    if (uMultiWordNe((unsigned int *)&r17.chunks[0U],
                                                     (unsigned int *)&r4.chunks[0U])) {
                                        // 'IsEnabledDebugLog:7' value = true;
                                        // 'FeedoptPlan:141' PrintCurvStruct(ctx,
                                        // OptSegment(k-ctx.k0+1))
                                        PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                        ctx->cfg.GaussLegendreW,
                                                        &OptSegment[k - ctx->k0]);
                                    }
                                    // 'FeedoptPlan:143' if k < k1
                                    if (k < k1) {
                                        // 'FeedoptPlan:144' DebugLog(DebugCfg.Global, ...
                                        // 'FeedoptPlan:145'
                                        // '-----------------------------------\n')
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                        // 'IsEnabledDebugLog:4' value = false;
                                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                        Double2MultiWord(DebugConfig,
                                                         (unsigned int *)&r30.chunks[0U]);
                                        r25 = r1;
                                        MultiWordAnd((unsigned int *)&r30.chunks[0U],
                                                     (unsigned int *)&r1.chunks[0U],
                                                     (unsigned int *)&r27.chunks[0U]);
                                        r30 = r4;
                                        if (uMultiWordNe((unsigned int *)&r27.chunks[0U],
                                                         (unsigned int *)&r4.chunks[0U])) {
                                            // 'IsEnabledDebugLog:7' value = true;
                                            // 'DebugLog:6' fprintf(1, varargin{:});
                                            printf("-----------------------------------\n");
                                            fflush(stdout);
                                        }
                                    }
                                } else {
                                    // 'FeedoptPlan:147' else
                                    // 'FeedoptPlan:148' error('Wrong ZspdMode');
                                }
                                k++;
                            }
                        }
                        // 'FeedoptPlan:151' DebugLog(DebugCfg.Global, ...
                        // 'FeedoptPlan:152' '================================================\n')
                        //  1 -> stdout
                        //  2 -> stderr
                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                        // 'IsEnabledDebugLog:4' value = false;
                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                        Double2MultiWord(DebugConfig, (unsigned int *)&r23.chunks[0U]);
                        r24 = r1;
                        MultiWordAnd((unsigned int *)&r23.chunks[0U],
                                     (unsigned int *)&r1.chunks[0U],
                                     (unsigned int *)&r25.chunks[0U]);
                        if (uMultiWordNe((unsigned int *)&r25.chunks[0U],
                                         (unsigned int *)&r4.chunks[0U])) {
                            // 'IsEnabledDebugLog:7' value = true;
                            // 'DebugLog:6' fprintf(1, varargin{:});
                            printf("================================================\n");
                            fflush(stdout);
                        }
                        // 'FeedoptPlan:154' Retry = 0;
                        Retry = 0;
                        // 'FeedoptPlan:155' success = false;
                        success = false;
                        // 'FeedoptPlan:156' Coeff = [];
                        Coeff.set_size(0, 0);
                        // 'FeedoptPlan:158' while Retry < 100 && ~success
                        while ((Retry < 100) && (!success)) {
                            int d_ctx;
                            // 'FeedoptPlan:159' [ctx, Coeff, ~, success] = FeedratePlanning_v4(ctx,
                            // OptSegment, ctx.cfg.amax, ctx.cfg.jmax,... 'FeedoptPlan:160'
                            // ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr,...
                            // 'FeedoptPlan:161'                         ctx.Bl, ctx.u_vec,
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
                            // 'FeedoptPlan:163' if success == 0 && ctx.zero_start
                            if ((!b_success) && ctx->zero_start) {
                                // 'FeedoptPlan:164' DebugLog(DebugCfg.Warning, 'ZeroStart at k = %d
                                // failed, halving jerk\n', ctx.k0-1);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                Double2MultiWord(DebugConfig, (unsigned int *)&r32.chunks[0U]);
                                r33 = r29;
                                MultiWordAnd((unsigned int *)&r32.chunks[0U],
                                             (unsigned int *)&r29.chunks[0U],
                                             (unsigned int *)&r35.chunks[0U]);
                                r32 = r4;
                                if (uMultiWordNe((unsigned int *)&r35.chunks[0U],
                                                 (unsigned int *)&r4.chunks[0U])) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'DebugLog:6' fprintf(1, varargin{:});
                                    printf("ZeroStart at k = %d failed, halving jerk\n",
                                           ctx->k0 - 1);
                                    fflush(stdout);
                                }
                                // 'FeedoptPlan:165' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(ctx.k0 - 1), 0.5^Retry);
                                ctx->q_split.get(ctx->k0 - 1, &r15);
                                CalcZeroStartConstraints(&ctx->q_splines, r15.Type, r15.P0, r15.P1,
                                                         r15.CorrectedHelixCenter, r15.evec,
                                                         r15.theta, r15.pitch, r15.CoeffP5,
                                                         r15.sp_index, r15.UseConstJerk,
                                                         r15.ConstJerk, r15.a_param, r15.b_param,
                                                         std::pow(0.5, static_cast<double>(Retry)),
                                                         &ctx->v_0, &ctx->at_0);
                                // 'FeedoptPlan:166' ctx.v_0 = v_0;
                                // 'FeedoptPlan:167' ctx.at_0 = at_0;
                            }
                            // 'FeedoptPlan:170' if success == 0 && ctx.zero_end
                            if ((!b_success) && ctx->zero_end) {
                                // 'FeedoptPlan:171' DebugLog(DebugCfg.Warning, 'ZeroEnd at k = %d
                                // failed, halving jerk\n', kend);
                                //  1 -> stdout
                                //  2 -> stderr
                                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                Double2MultiWord(DebugConfig, (unsigned int *)&r36.chunks[0U]);
                                MultiWordAnd((unsigned int *)&r36.chunks[0U],
                                             (unsigned int *)&r29.chunks[0U],
                                             (unsigned int *)&r33.chunks[0U]);
                                r36 = r4;
                                if (uMultiWordNe((unsigned int *)&r33.chunks[0U],
                                                 (unsigned int *)&r4.chunks[0U])) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'DebugLog:6' fprintf(1, varargin{:});
                                    printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                    fflush(stdout);
                                }
                                // 'FeedoptPlan:172' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(kend), 0.5^Retry);
                                ctx->q_split.get(kend, &r15);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, r15.Type, r15.P0, r15.P1,
                                    r15.CorrectedHelixCenter, r15.evec, r15.theta, r15.pitch,
                                    r15.CoeffP5, r15.sp_index, r15.UseConstJerk, r15.ConstJerk,
                                    r15.a_param, r15.b_param,
                                    std::pow(0.5, static_cast<double>(Retry)), &ctx->v_1, &b_at_0);
                                // 'FeedoptPlan:173' ctx.at_1 = -at_0;
                                ctx->at_1 = -b_at_0;
                                // 'FeedoptPlan:174' ctx.v_1 = v_0;
                            }
                            // 'FeedoptPlan:177' Retry = Retry + 1;
                            Retry++;
                        }
                        // 'FeedoptPlan:180' if coder.target('matlab')
                        // 'FeedoptPlan:184' ctx.zero_start = false;
                        ctx->zero_start = false;
                        // 'FeedoptPlan:185' ctx.zero_end = false;
                        ctx->zero_end = false;
                        // 'FeedoptPlan:187' ctx.Coeff = Coeff;
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
                        // 'FeedoptPlan:188' if success == 0
                        if (!success) {
                            int i11;
                            // 'FeedoptPlan:189' for nprint = 1:ctx.cfg.NHorz
                            i11 = ctx->cfg.NHorz;
                            if (0 <= i11 - 1) {
                                r31 = r1;
                            }
                            for (int nprint{0}; nprint < i11; nprint++) {
                                // 'FeedoptPlan:190' if IsEnabledDebugLog(DebugCfg.Global)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                Double2MultiWord(DebugConfig, (unsigned int *)&r34.chunks[0U]);
                                MultiWordAnd((unsigned int *)&r34.chunks[0U],
                                             (unsigned int *)&r1.chunks[0U],
                                             (unsigned int *)&r24.chunks[0U]);
                                r34 = r4;
                                if (uMultiWordNe((unsigned int *)&r24.chunks[0U],
                                                 (unsigned int *)&r4.chunks[0U])) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'FeedoptPlan:191' PrintCurvStruct(ctx, OptSegment(1));
                                    PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                    ctx->cfg.GaussLegendreW, &OptSegment[0]);
                                }
                            }
                            // 'FeedoptPlan:194' if coder.target('MATLAB')
                            // 'FeedoptPlan:196' else
                            // 'FeedoptPlan:197' DebugLog(DebugCfg.Global, 'OPTIMIZATION
                            // FAILED!\n');
                            //  1 -> stdout
                            //  2 -> stderr
                            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                            // 'IsEnabledDebugLog:4' value = false;
                            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                            Double2MultiWord(DebugConfig, (unsigned int *)&r37.chunks[0U]);
                            MultiWordAnd((unsigned int *)&r37.chunks[0U],
                                         (unsigned int *)&r1.chunks[0U],
                                         (unsigned int *)&r31.chunks[0U]);
                            if (uMultiWordNe((unsigned int *)&r31.chunks[0U],
                                             (unsigned int *)&r4.chunks[0U])) {
                                // 'IsEnabledDebugLog:7' value = true;
                                // 'DebugLog:6' fprintf(1, varargin{:});
                                printf("OPTIMIZATION FAILED!\n");
                                fflush(stdout);
                            }
                            // 'FeedoptPlan:198' ctx.errcode = FeedoptPlanError.OptimizationFailed;
                            ctx->errcode = FeedoptPlanError_OptimizationFailed;
                            // 'FeedoptPlan:200' ctx.op = Fopt.Finished;
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
                    // 'FeedoptPlan:203' else
                    //  If we have reached the end of the optimizing segment, we
                    //  can just copy out the coefficients for the whole horizon
                    // 'FeedoptPlan:206' ctx.Coeff(:, 1:end-1) = ctx.Coeff(:, 2:end);
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
                // 'FeedoptPlan:217' else
                // 'FeedoptPlan:218' ctx.op = Fopt.Finished;
                ctx->op = Fopt_Finished;
            }
        }
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:221' case Fopt.Finished
        // 'FeedoptPlan:222' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:224' otherwise
        // 'FeedoptPlan:225' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
        MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                     (unsigned int *)&r2.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("FEEDOPT: WRONG STATE\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:226' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    }
    if (guard1) {
        int loop_ub;
        // 'FeedoptPlan:209' optimized = true;
        b_optimized = true;
        // 'FeedoptPlan:210' opt_struct = ctx.q_split.get(ctx.n_optimized + 1);
        ctx->q_split.get(ctx->n_optimized + 1, opt_struct);
        // 'FeedoptPlan:211' opt_struct.Coeff = ctx.Coeff(:, 1);
        loop_ub = ctx->Coeff.size(0);
        opt_struct->Coeff.set_size(loop_ub);
        for (int i1{0}; i1 < loop_ub; i1++) {
            opt_struct->Coeff[i1] = ctx->Coeff[i1];
        }
        // 'FeedoptPlan:213' if opt_struct.zspdmode == ZSpdMode.NZ
        if (opt_struct->zspdmode == ZSpdMode_NZ) {
            // 'FeedoptPlan:214' ctx.reached_end = false;
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
