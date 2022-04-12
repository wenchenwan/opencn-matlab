//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:49:22
//

// Include Files
#include "FeedoptPlan.h"
#include "CalcZeroStartConstraints.h"
#include "CheckCurvStructs.h"
#include "CompressCurvStructs.h"
#include "ConstrLineStruct.h"
#include "ExpandZeroStructs.h"
#include "FeedratePlanning.h"
#include "PrintCurvStruct.h"
#include "SmoothCurvStructs.h"
#include "SplitCurvStructs.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
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
    static const uint64m_T r1{
        {8U, 0U} // chunks
    };
    static const uint64m_T r25{
        {16U, 0U} // chunks
    };
    static const uint64m_T r4{
        {0U, 0U} // chunks
    };
    static const uint64m_T r6{
        {2U, 0U} // chunks
    };
    static const uint64m_T r9{
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
    CurvStruct r13;
    uint64m_T r;
    uint64m_T r10;
    uint64m_T r11;
    uint64m_T r12;
    uint64m_T r14;
    uint64m_T r16;
    uint64m_T r18;
    uint64m_T r19;
    uint64m_T r2;
    uint64m_T r21;
    uint64m_T r22;
    uint64m_T r24;
    uint64m_T r26;
    uint64m_T r27;
    uint64m_T r28;
    uint64m_T r29;
    uint64m_T r3;
    uint64m_T r30;
    uint64m_T r31;
    uint64m_T r32;
    uint64m_T r33;
    uint64m_T r7;
    uint64m_T r8;
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
    int c_status;
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
    // 'FeedoptPlan:9' end_flag = false;
    // 'FeedoptPlan:11' trafo = false;
    //  TRAFO flag disable
    // 'FeedoptPlan:12' HSC = false;
    // 'FeedoptPlan:13' Poff = zeros(3, 1);
    // 'FeedoptPlan:13' Aoff = Poff;
    // 'FeedoptPlan:13' Uoff = Poff;
    // 'FeedoptPlan:13' Doff = 0.0;
    // 'FeedoptPlan:14' A0 = zeros(3,1);
    // 'FeedoptPlan:14' A1 = A0;
    // 'FeedoptPlan:14' U0 = A0 ;
    // 'FeedoptPlan:14' U1 = A0;
    // 'FeedoptPlan:16' opt_struct = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
    // 'FeedoptPlan:17'                                Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
    // 'FeedoptPlan:18'                                U1, 0.2, ZSpdMode.NN);
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
    // 'FeedoptPlan:20' switch ctx.op
    guard1 = false;
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:21' case Fopt.Init
        // 'FeedoptPlan:22' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        break;
    case Fopt_GCode: {
        uint64m_T r17;
        int status;
        // 'FeedoptPlan:23' case Fopt.GCode
        // 'FeedoptPlan:25' status = int32(ReadGCode(ReadGCodeCmd.Load, ctx.cfg.source));
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' if coder.target('mex')
        // 'ReadGCode:86' elseif coder.target('rtw')
        // 'ReadGCode:87' trafo = false;
        //  TRAFO flag disable
        // 'ReadGCode:88' HSC = false;
        // 'ReadGCode:89' Poff = zeros(3, 1);
        // 'ReadGCode:89' Aoff = Poff;
        // 'ReadGCode:89' Uoff = Poff;
        // 'ReadGCode:89' Doff = 0.0;
        // 'ReadGCode:90' A0 = zeros(3,1);
        // 'ReadGCode:90' A1 = A0;
        // 'ReadGCode:90' U0 = A0 ;
        // 'ReadGCode:90' U1 = A0;
        // 'ReadGCode:92' if cmd == ReadGCodeCmd.Load
        // 'ReadGCode:94' CurvStruct = ConstrLineStruct(trafo, HSC, Poff, Aoff, ...
        // 'ReadGCode:95'                                       Uoff, Doff, [1,2,3]', [4,5,6]', ...
        // 'ReadGCode:96'                                       A0, A1, U0, U1, 0.2, ZSpdMode.NN);
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
        ConstrLineStruct(false, false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2,
                         ZSpdMode_NN, &b_CurvStruct);
        // 'ReadGCode:98' status = int32(0);
        // 'ReadGCode:99' status = coder.ceval('c_open_gcode', [filename, 0],
        // coder.ref(CurvStruct));
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = c_open_gcode(&b_cv[0], &b_CurvStruct);
        // 'FeedoptPlan:26' DebugLog(DebugCfg.Validate, 'Reading G-code...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r16.chunks[0U]);
        r17 = r9;
        MultiWordAnd((unsigned int *)&r16.chunks[0U], (unsigned int *)&r9.chunks[0U],
                     (unsigned int *)&r18.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r18.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:27' while status
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
            // 'FeedoptPlan:28' [status, CurvStruct] = ReadGCode(ReadGCodeCmd.Read, '');
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' if coder.target('mex')
            // 'ReadGCode:86' elseif coder.target('rtw')
            // 'ReadGCode:87' trafo = false;
            //  TRAFO flag disable
            // 'ReadGCode:88' HSC = false;
            // 'ReadGCode:89' Poff = zeros(3, 1);
            // 'ReadGCode:89' Aoff = Poff;
            // 'ReadGCode:89' Uoff = Poff;
            // 'ReadGCode:89' Doff = 0.0;
            // 'ReadGCode:90' A0 = zeros(3,1);
            // 'ReadGCode:90' A1 = A0;
            // 'ReadGCode:90' U0 = A0 ;
            // 'ReadGCode:90' U1 = A0;
            // 'ReadGCode:92' if cmd == ReadGCodeCmd.Load
            // 'ReadGCode:100' elseif cmd == ReadGCodeCmd.Read
            // 'ReadGCode:102' CurvStruct = ConstrLineStruct(trafo, HSC, Poff, Aoff, ...
            // 'ReadGCode:103'                                       Uoff, Doff, [1,2,3]', [4,5,6]',
            // ... 'ReadGCode:104'                                       A0, A1, U0, U1, 0.2,
            // ZSpdMode.NN);
            ConstrLineStruct(false, false, dv, dv1, dv2, 0.0, dv3, dv4, dv5, dv6, dv7, dv8, 0.2,
                             ZSpdMode_NN, &b_CurvStruct);
            // 'ReadGCode:105' status = int32(0);
            // 'ReadGCode:106' status = coder.ceval('c_read_and_exec_gcode', '',
            // coder.ref(CurvStruct));
            b_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            status = b_status;
            // 'FeedoptPlan:29' if( CurvStruct.FeedRate == 0 )
            if (b_CurvStruct.FeedRate == 0.0) {
                // 'FeedoptPlan:30' CurvStruct.FeedRate = ctx.cfg.vmax;
                b_CurvStruct.FeedRate = ctx->cfg.vmax;
            }
            // 'FeedoptPlan:32' if status == 1 && CurvStruct.Type ~= 0
            if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Type) != 0)) {
                // 'FeedoptPlan:33' if ( CurvStruct.FeedRate == 0.0 )
                if (b_CurvStruct.FeedRate == 0.0) {
                    //  check for undefined feedrate
                    // 'FeedoptPlan:35' CurvStruct.FeedRate = ctx.cfg.vmax;
                    b_CurvStruct.FeedRate = ctx->cfg.vmax;
                }
                // 'FeedoptPlan:37' ctx.q_gcode.push(CurvStruct);
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:40' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:41' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:42' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:43'                 'ERROR: Optimization failed, Gcode queue is
            // empty\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r24.chunks[0U]);
            MultiWordAnd((unsigned int *)&r24.chunks[0U], (unsigned int *)&r25.chunks[0U],
                         (unsigned int *)&r17.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r17.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("ERROR: Optimization failed, Gcode queue is empty\n");
                fflush(stdout);
            }
        } else {
            // 'FeedoptPlan:46' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:47' if last.zspdmode == ZSpdMode.NN
            if (last.zspdmode == ZSpdMode_NN) {
                // 'FeedoptPlan:48' last.zspdmode = ZSpdMode.NZ;
                last.zspdmode = ZSpdMode_NZ;
            } else if (last.zspdmode == ZSpdMode_ZN) {
                // 'FeedoptPlan:49' elseif last.zspdmode == ZSpdMode.ZN
                // 'FeedoptPlan:50' last.zspdmode = ZSpdMode.ZZ;
                last.zspdmode = ZSpdMode_ZZ;
            }
            // 'FeedoptPlan:52' ctx.q_gcode.set(ctx.q_gcode.size, last);
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:53' ctx.op = Fopt.Check;
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check:
        // 'FeedoptPlan:55' case Fopt.Check
        // 'FeedoptPlan:56' ctx = CheckCurvStructs(ctx);
        CheckCurvStructs(ctx);
        // 'FeedoptPlan:57' ctx.op = Fopt.Compress;
        ctx->op = Fopt_Compress;
        break;
    case Fopt_Compress:
        // 'FeedoptPlan:59' case Fopt.Compress
        // 'FeedoptPlan:60' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            // 'FeedoptPlan:61' ctx = ExpandZeroStructs(ctx);
            ExpandZeroStructs(ctx);
        } else {
            // 'FeedoptPlan:62' else
            // 'FeedoptPlan:63' ctx = CompressCurvStructs(ctx);
            CompressCurvStructs(ctx);
        }
        // 'FeedoptPlan:65' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:66' if( coder.target( 'MATLAB') )
        break;
    case Fopt_Smooth:
        // 'FeedoptPlan:68' case Fopt.Smooth
        // 'FeedoptPlan:69' ctx = SmoothCurvStructs(ctx);
        SmoothCurvStructs(ctx);
        // 'FeedoptPlan:70' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:71' if( coder.target( 'MATLAB') )
        break;
    case Fopt_Split:
        // 'FeedoptPlan:73' case Fopt.Split
        // 'FeedoptPlan:74' ctx = SplitCurvStructs(ctx);
        SplitCurvStructs(ctx);
        // 'FeedoptPlan:76' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:77' if( coder.target( 'MATLAB') )
        // 'FeedoptPlan:79' DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r11.chunks[0U]);
        MultiWordAnd((unsigned int *)&r11.chunks[0U], (unsigned int *)&r9.chunks[0U],
                     (unsigned int *)&r12.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r12.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Feedrate Planning...\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:80' if coder.target('matlab')
        break;
    case Fopt_Opt: {
        // 'FeedoptPlan:84' case Fopt.Opt
        // 'FeedoptPlan:85' if ctx.q_split.isempty
        if (ctx->q_split.isempty()) {
            // 'FeedoptPlan:86' if coder.target('matlab')
            // 'FeedoptPlan:89' DebugLog(DebugCfg.Validate, 'Queue empty...\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r8.chunks[0U]);
            MultiWordAnd((unsigned int *)&r8.chunks[0U], (unsigned int *)&r9.chunks[0U],
                         (unsigned int *)&r10.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r10.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Queue empty...\n");
                fflush(stdout);
            }
            // 'FeedoptPlan:90' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
        } else {
            uint64m_T r5;
            // 'FeedoptPlan:93' ctx.op = Fopt.Opt;
            ctx->op = Fopt_Opt;
            // 'FeedoptPlan:95' if IsEnabledDebugLog(DebugCfg.OptimProgress)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r3.chunks[0U]);
            r5 = r6;
            MultiWordAnd((unsigned int *)&r3.chunks[0U], (unsigned int *)&r6.chunks[0U],
                         (unsigned int *)&r7.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r7.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                unsigned int validatedHoleFilling_f2;
                // 'IsEnabledDebugLog:7' value = true;
                // 'FeedoptPlan:96' fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
                validatedHoleFilling_f2 = ctx->q_split.size();
                printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
                fflush(stdout);
            }
            //  Increment index on q_split
            // 'FeedoptPlan:100' if ctx.go_next
            if (ctx->go_next) {
                // 'FeedoptPlan:101' ctx.k0 = ctx.k0 + 1;
                ctx->k0++;
                // 'FeedoptPlan:102' ctx.n_optimized = ctx.n_optimized + 1;
                ctx->n_optimized++;
            }
            // 'FeedoptPlan:105' if ctx.n_optimized < ctx.q_split.size
            if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
                // 'FeedoptPlan:106' if ctx.try_push_again
                if (ctx->try_push_again) {
                    //  Do nothing, we already have the last one optimized
                    guard1 = true;
                } else if (!ctx->reached_end) {
                    int varargin_2_tmp;
                    // 'FeedoptPlan:108' elseif ~ctx.reached_end
                    // 'FeedoptPlan:109' OptSegment = repmat(ctx.q_split.get(1), 1, ctx.cfg.NHorz);
                    ctx->q_split.get(static_cast<double>(1.0), &r13);
                    varargin_2_tmp = ctx->cfg.NHorz;
                    OptSegment.set_size(1, varargin_2_tmp);
                    for (int i3{0}; i3 < varargin_2_tmp; i3++) {
                        OptSegment[i3] = r13;
                    }
                    // 'FeedoptPlan:111' first = ctx.q_split.get(ctx.k0);
                    ctx->q_split.get(ctx->k0, &b_first);
                    // 'FeedoptPlan:112' if first.zspdmode == ZSpdMode.ZN
                    if (b_first.zspdmode == ZSpdMode_ZN) {
                        // 'FeedoptPlan:113' opt_struct = first;
                        *opt_struct = b_first;
                        // 'FeedoptPlan:114' optimized = true;
                        b_optimized = true;
                        // 'FeedoptPlan:115' [v_0, at_0] = CalcZeroStartConstraints(ctx, first, 1);
                        CalcZeroStartConstraints(
                            &ctx->q_splines, b_first.Type, b_first.P0, b_first.P1,
                            b_first.CorrectedHelixCenter, b_first.evec, b_first.theta,
                            b_first.pitch, b_first.CoeffP5, b_first.sp_index, b_first.UseConstJerk,
                            b_first.ConstJerk, b_first.a_param, b_first.b_param, 1.0, &ctx->v_0,
                            &ctx->at_0);
                        // 'FeedoptPlan:116' ctx.v_0 = v_0;
                        // 'FeedoptPlan:117' ctx.at_0 = at_0;
                        // 'FeedoptPlan:118' ctx.zero_start = true;
                        ctx->zero_start = true;
                    } else {
                        uint64m_T r15;
                        uint64m_T r20;
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
                        // 'FeedoptPlan:123' k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
                        k1temp = (ctx->k0 + ctx->cfg.NHorz) - 1;
                        // 'FeedoptPlan:124' if k1temp > ctx.q_split.size
                        if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                            // 'FeedoptPlan:125' ctx.reached_end = true;
                            ctx->reached_end = true;
                            // 'FeedoptPlan:126' k1 = int32(ctx.q_split.size);
                            k1 = static_cast<int>(ctx->q_split.size());
                        } else {
                            // 'FeedoptPlan:127' else
                            // 'FeedoptPlan:128' k1 = int32(k1temp);
                            k1 = k1temp;
                        }
                        // 'FeedoptPlan:131' ctx.at_1    = 0;
                        ctx->at_1 = 0.0;
                        // 'FeedoptPlan:132' ctx.v_1     = 0;
                        ctx->v_1 = 0.0;
                        // 'FeedoptPlan:134' nopt = 0;
                        nopt = 0U;
                        // 'FeedoptPlan:135' DebugLog(DebugCfg.Global, 'FEEDRATE PLANNING...\n')
                        //  1 -> stdout
                        //  2 -> stderr
                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                        // 'IsEnabledDebugLog:4' value = false;
                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                        Double2MultiWord(DebugConfig, (unsigned int *)&r14.chunks[0U]);
                        r15 = r1;
                        MultiWordAnd((unsigned int *)&r14.chunks[0U],
                                     (unsigned int *)&r1.chunks[0U],
                                     (unsigned int *)&r5.chunks[0U]);
                        if (uMultiWordNe((unsigned int *)&r5.chunks[0U],
                                         (unsigned int *)&r4.chunks[0U])) {
                            // 'IsEnabledDebugLog:7' value = true;
                            // 'DebugLog:6' fprintf(1, varargin{:});
                            printf("FEEDRATE PLANNING...\n");
                            fflush(stdout);
                        }
                        // 'FeedoptPlan:136' kend = ctx.k0;
                        kend = ctx->k0;
                        // 'FeedoptPlan:137' for k = ctx.k0:k1
                        k = ctx->k0;
                        exitg1 = false;
                        while ((!exitg1) && (k <= k1)) {
                            // 'FeedoptPlan:138' NextCurv = ctx.q_split.get(k);
                            ctx->q_split.get(k, &NextCurv);
                            // 'FeedoptPlan:139' if NextCurv.zspdmode == ZSpdMode.NZ
                            if (NextCurv.zspdmode == ZSpdMode_NZ) {
                                //  If we reach an NZ segment, we set the final velocity
                                //  and tangent acceleration constraints to the ones
                                //  specified by the segment, and pretend this is the
                                //  end of all segments
                                // 'FeedoptPlan:144' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // NextCurv, 1);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                    NextCurv.CorrectedHelixCenter, NextCurv.evec, NextCurv.theta,
                                    NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                    NextCurv.UseConstJerk, NextCurv.ConstJerk, NextCurv.a_param,
                                    NextCurv.b_param, 1.0, &v_0, &at_0);
                                // 'FeedoptPlan:145' ctx.at_1 = -at_0;
                                // 'FeedoptPlan:146' ctx.v_1 = v_0;
                                // 'FeedoptPlan:147' ctx.zero_end = true;
                                ctx->zero_end = true;
                                // 'FeedoptPlan:148' ctx.reached_end = true;
                                ctx->reached_end = true;
                                // 'FeedoptPlan:149' kend = k;
                                kend = k;
                                exitg1 = true;
                            } else {
                                if (NextCurv.zspdmode == ZSpdMode_NN) {
                                    uint64m_T r23;
                                    // 'FeedoptPlan:151' elseif NextCurv.zspdmode == ZSpdMode.NN
                                    // 'FeedoptPlan:152' nopt = nopt + 1;
                                    nopt++;
                                    // 'FeedoptPlan:153' OptSegment(nopt) = NextCurv;
                                    OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                    // 'FeedoptPlan:155' if IsEnabledDebugLog(DebugCfg.Global)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    Double2MultiWord(DebugConfig, (unsigned int *)&r22.chunks[0U]);
                                    r23 = r1;
                                    MultiWordAnd((unsigned int *)&r22.chunks[0U],
                                                 (unsigned int *)&r1.chunks[0U],
                                                 (unsigned int *)&r15.chunks[0U]);
                                    r22 = r4;
                                    if (uMultiWordNe((unsigned int *)&r15.chunks[0U],
                                                     (unsigned int *)&r4.chunks[0U])) {
                                        // 'IsEnabledDebugLog:7' value = true;
                                        // 'FeedoptPlan:156' PrintCurvStruct(ctx,
                                        // OptSegment(k-ctx.k0+1))
                                        PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                        ctx->cfg.GaussLegendreW,
                                                        &OptSegment[k - ctx->k0]);
                                    }
                                    // 'FeedoptPlan:158' if k < k1
                                    if (k < k1) {
                                        // 'FeedoptPlan:159' DebugLog(DebugCfg.Global, ...
                                        // 'FeedoptPlan:160'
                                        // '-----------------------------------\n')
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                        // 'IsEnabledDebugLog:4' value = false;
                                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                        Double2MultiWord(DebugConfig,
                                                         (unsigned int *)&r26.chunks[0U]);
                                        r21 = r1;
                                        MultiWordAnd((unsigned int *)&r26.chunks[0U],
                                                     (unsigned int *)&r1.chunks[0U],
                                                     (unsigned int *)&r23.chunks[0U]);
                                        r26 = r4;
                                        if (uMultiWordNe((unsigned int *)&r23.chunks[0U],
                                                         (unsigned int *)&r4.chunks[0U])) {
                                            // 'IsEnabledDebugLog:7' value = true;
                                            // 'DebugLog:6' fprintf(1, varargin{:});
                                            printf("-----------------------------------\n");
                                            fflush(stdout);
                                        }
                                    }
                                } else {
                                    // 'FeedoptPlan:162' else
                                    // 'FeedoptPlan:163' error('Wrong ZspdMode');
                                }
                                k++;
                            }
                        }
                        // 'FeedoptPlan:166' DebugLog(DebugCfg.Global, ...
                        // 'FeedoptPlan:167' '================================================\n')
                        //  1 -> stdout
                        //  2 -> stderr
                        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                        // 'IsEnabledDebugLog:4' value = false;
                        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                        Double2MultiWord(DebugConfig, (unsigned int *)&r19.chunks[0U]);
                        r20 = r1;
                        MultiWordAnd((unsigned int *)&r19.chunks[0U],
                                     (unsigned int *)&r1.chunks[0U],
                                     (unsigned int *)&r21.chunks[0U]);
                        if (uMultiWordNe((unsigned int *)&r21.chunks[0U],
                                         (unsigned int *)&r4.chunks[0U])) {
                            // 'IsEnabledDebugLog:7' value = true;
                            // 'DebugLog:6' fprintf(1, varargin{:});
                            printf("================================================\n");
                            fflush(stdout);
                        }
                        // 'FeedoptPlan:169' Retry = 0;
                        Retry = 0;
                        // 'FeedoptPlan:170' success = false;
                        success = false;
                        // 'FeedoptPlan:171' Coeff = [];
                        Coeff.set_size(0, 0);
                        // 'FeedoptPlan:172' ctx.at_1 = ctx.cfg.at_1;
                        ctx->at_1 = ctx->cfg.at_1;
                        // 'FeedoptPlan:172' ctx.v_1 = ctx.cfg.v_0;
                        ctx->v_1 = ctx->cfg.v_0;
                        // 'FeedoptPlan:173' MAX_RETRY = 100;
                        // 'FeedoptPlan:174' while Retry < MAX_RETRY && ~success
                        while ((Retry < 100) && (!success)) {
                            int d_ctx;
                            // 'FeedoptPlan:176' if ctx.zero_start
                            if (ctx->zero_start) {
                                // 'FeedoptPlan:177' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(ctx.k0 - 1), 0.5^Retry);
                                ctx->q_split.get(ctx->k0 - 1, &r13);
                                CalcZeroStartConstraints(&ctx->q_splines, r13.Type, r13.P0, r13.P1,
                                                         r13.CorrectedHelixCenter, r13.evec,
                                                         r13.theta, r13.pitch, r13.CoeffP5,
                                                         r13.sp_index, r13.UseConstJerk,
                                                         r13.ConstJerk, r13.a_param, r13.b_param,
                                                         std::pow(0.5, static_cast<double>(Retry)),
                                                         &ctx->v_0, &ctx->at_0);
                                // 'FeedoptPlan:178' ctx.v_0 = v_0;
                                // 'FeedoptPlan:179' ctx.at_0 = at_0;
                            }
                            // 'FeedoptPlan:182' if ctx.zero_end
                            if (ctx->zero_end) {
                                // 'FeedoptPlan:183' [v_0, at_0] = CalcZeroStartConstraints(ctx,
                                // ctx.q_split.get(kend), 0.5^Retry);
                                ctx->q_split.get(kend, &r13);
                                CalcZeroStartConstraints(
                                    &ctx->q_splines, r13.Type, r13.P0, r13.P1,
                                    r13.CorrectedHelixCenter, r13.evec, r13.theta, r13.pitch,
                                    r13.CoeffP5, r13.sp_index, r13.UseConstJerk, r13.ConstJerk,
                                    r13.a_param, r13.b_param,
                                    std::pow(0.5, static_cast<double>(Retry)), &ctx->v_1, &b_at_0);
                                // 'FeedoptPlan:184' ctx.at_1 = -at_0;
                                ctx->at_1 = -b_at_0;
                                // 'FeedoptPlan:185' ctx.v_1 = v_0;
                            }
                            // 'FeedoptPlan:188' [ctx, Coeff, ~, success, status, msg] =
                            // FeedratePlanning(ctx, OptSegment, ctx.cfg.amax, ctx.cfg.jmax,...
                            // 'FeedoptPlan:189'                         ctx.BasisVal,
                            // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr,... 'FeedoptPlan:190'
                            // ctx.Bl, ctx.u_vec, min(ctx.cfg.NHorz, nopt));
                            if (ctx->cfg.NHorz > static_cast<int>(nopt)) {
                                d_ctx = static_cast<int>(nopt);
                            } else {
                                d_ctx = ctx->cfg.NHorz;
                            }
                            FeedratePlanning(ctx, OptSegment, ctx->cfg.amax, ctx->cfg.jmax,
                                             ctx->BasisVal, ctx->BasisValD, ctx->BasisValDD,
                                             ctx->BasisIntegr, ctx->Bl.handle, ctx->u_vec, d_ctx,
                                             Coeff, &a__1, &b_success, &c_status);
                            success = b_success;
                            // 'FeedoptPlan:192' if( ~success )
                            if (!b_success) {
                                // 'FeedoptPlan:193' Retry = Retry + 1;
                                Retry++;
                                // 'FeedoptPlan:194' if coder.target('matlab')
                                // 'FeedoptPlan:202' if( ctx.zero_start )
                                if (ctx->zero_start) {
                                    // 'FeedoptPlan:203' DebugLog(DebugCfg.Warning, 'ZeroStart at k
                                    // = %d failed, halving jerk\n', ctx.k0-1);
                                    //  1 -> stdout
                                    //  2 -> stderr
                                    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    Double2MultiWord(DebugConfig, (unsigned int *)&r30.chunks[0U]);
                                    r31 = r25;
                                    MultiWordAnd((unsigned int *)&r30.chunks[0U],
                                                 (unsigned int *)&r25.chunks[0U],
                                                 (unsigned int *)&r32.chunks[0U]);
                                    r30 = r4;
                                    if (uMultiWordNe((unsigned int *)&r32.chunks[0U],
                                                     (unsigned int *)&r4.chunks[0U])) {
                                        // 'IsEnabledDebugLog:7' value = true;
                                        // 'DebugLog:6' fprintf(1, varargin{:});
                                        printf("ZeroStart at k = %d failed, halving jerk\n",
                                               ctx->k0 - 1);
                                        fflush(stdout);
                                    }
                                }
                                // 'FeedoptPlan:206' if( ctx.zero_end )
                                if (ctx->zero_end) {
                                    // 'FeedoptPlan:207' DebugLog(DebugCfg.Warning, 'ZeroEnd at k =
                                    // %d failed, halving jerk\n', kend);
                                    //  1 -> stdout
                                    //  2 -> stderr
                                    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                                    // 'IsEnabledDebugLog:4' value = false;
                                    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                    Double2MultiWord(DebugConfig, (unsigned int *)&r33.chunks[0U]);
                                    MultiWordAnd((unsigned int *)&r33.chunks[0U],
                                                 (unsigned int *)&r25.chunks[0U],
                                                 (unsigned int *)&r31.chunks[0U]);
                                    r33 = r4;
                                    if (uMultiWordNe((unsigned int *)&r31.chunks[0U],
                                                     (unsigned int *)&r4.chunks[0U])) {
                                        // 'IsEnabledDebugLog:7' value = true;
                                        // 'DebugLog:6' fprintf(1, varargin{:});
                                        printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                        fflush(stdout);
                                    }
                                }
                            }
                        }
                        // 'FeedoptPlan:212' if coder.target('matlab')
                        // 'FeedoptPlan:216' ctx.zero_start = false;
                        ctx->zero_start = false;
                        // 'FeedoptPlan:217' ctx.zero_end = false;
                        ctx->zero_end = false;
                        // 'FeedoptPlan:219' ctx.Coeff = Coeff;
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
                        // 'FeedoptPlan:220' if success == 0
                        if (!success) {
                            int i11;
                            // 'FeedoptPlan:221' for nprint = 1:ctx.cfg.NHorz
                            i11 = ctx->cfg.NHorz;
                            if (0 <= i11 - 1) {
                                r27 = r1;
                            }
                            for (int nprint{0}; nprint < i11; nprint++) {
                                // 'FeedoptPlan:222' if IsEnabledDebugLog(DebugCfg.Global)
                                // 'IsEnabledDebugLog:4' value = false;
                                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                                Double2MultiWord(DebugConfig, (unsigned int *)&r28.chunks[0U]);
                                MultiWordAnd((unsigned int *)&r28.chunks[0U],
                                             (unsigned int *)&r1.chunks[0U],
                                             (unsigned int *)&r20.chunks[0U]);
                                r28 = r4;
                                if (uMultiWordNe((unsigned int *)&r20.chunks[0U],
                                                 (unsigned int *)&r4.chunks[0U])) {
                                    // 'IsEnabledDebugLog:7' value = true;
                                    // 'FeedoptPlan:223' PrintCurvStruct(ctx, OptSegment(1));
                                    PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                    ctx->cfg.GaussLegendreW, &OptSegment[0]);
                                }
                            }
                            // 'FeedoptPlan:226' if coder.target('MATLAB')
                            // 'FeedoptPlan:228' else
                            // 'FeedoptPlan:229' DebugLog(DebugCfg.Global, 'OPTIMIZATION
                            // FAILED!\n');
                            //  1 -> stdout
                            //  2 -> stderr
                            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                            // 'IsEnabledDebugLog:4' value = false;
                            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                            Double2MultiWord(DebugConfig, (unsigned int *)&r29.chunks[0U]);
                            MultiWordAnd((unsigned int *)&r29.chunks[0U],
                                         (unsigned int *)&r1.chunks[0U],
                                         (unsigned int *)&r27.chunks[0U]);
                            if (uMultiWordNe((unsigned int *)&r27.chunks[0U],
                                             (unsigned int *)&r4.chunks[0U])) {
                                // 'IsEnabledDebugLog:7' value = true;
                                // 'DebugLog:6' fprintf(1, varargin{:});
                                printf("OPTIMIZATION FAILED!\n");
                                fflush(stdout);
                            }
                            // 'FeedoptPlan:230' ctx.errcode = FeedoptPlanError.OptimizationFailed;
                            ctx->errcode = FeedoptPlanError_OptimizationFailed;
                            // 'FeedoptPlan:232' ctx.op = Fopt.Finished;
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
                    // 'FeedoptPlan:235' else
                    //  If we have reached the end of the optimizing segment, we
                    //  can just copy out the coefficients for the whole horizon
                    // 'FeedoptPlan:238' ctx.Coeff(:, 1:end-1) = ctx.Coeff(:, 2:end);
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
                // 'FeedoptPlan:249' else
                // 'FeedoptPlan:250' ctx.op = Fopt.Finished;
                ctx->op = Fopt_Finished;
            }
        }
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:253' case Fopt.Finished
        // 'FeedoptPlan:254' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:256' otherwise
        // 'FeedoptPlan:257' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:258' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    }
    if (guard1) {
        int loop_ub;
        // 'FeedoptPlan:241' optimized = true;
        b_optimized = true;
        // 'FeedoptPlan:242' opt_struct = ctx.q_split.get(ctx.n_optimized + 1);
        ctx->q_split.get(ctx->n_optimized + 1, opt_struct);
        // 'FeedoptPlan:243' opt_struct.Coeff = ctx.Coeff(:, 1);
        loop_ub = ctx->Coeff.size(0);
        opt_struct->Coeff.set_size(loop_ub);
        for (int i1{0}; i1 < loop_ub; i1++) {
            opt_struct->Coeff[i1] = ctx->Coeff[i1];
        }
        // 'FeedoptPlan:245' if opt_struct.zspdmode == ZSpdMode.NZ
        if (opt_struct->zspdmode == ZSpdMode_NZ) {
            // 'FeedoptPlan:246' ctx.reached_end = false;
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
