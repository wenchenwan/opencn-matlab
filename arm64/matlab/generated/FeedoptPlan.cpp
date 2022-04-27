//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

// Include Files
#include "FeedoptPlan.h"
#include "CompressCurvStructs.h"
#include "ConstrLineStruct.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "SmoothCurvStructs.h"
#include "SplineLengthFindU_up.h"
#include "cutZeroEnd.h"
#include "cutZeroStart.h"
#include "feedratePlanning.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <stdio.h>

// Function Declarations
namespace ocn {
static double rt_remd(double u0, double u1);

}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace ocn {
static double rt_remd(double u0, double u1)
{
    double y;
    if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
        double q;
        q = std::abs(u0 / u1);
        if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
            y = 0.0;
        } else {
            y = std::fmod(u0, u1);
        }
    } else {
        y = std::fmod(u0, u1);
    }
    return y;
}

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
void FeedoptPlan(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct)
{
    static const char b_message[39]{'F', 'e', 'e', 'd', 'o', 'p', 't', 'P', 'l', 'a',
                                    'n', ':', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'c',
                                    'o', 'd', 'e', ' ', 'w', 'a', 's', ' ', 'n', 'o',
                                    't', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'd'};
    CurvStruct Curv;
    CurvStruct Curv1;
    CurvStruct Curv2;
    CurvStruct CurvStrct;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct b_CurvStruct;
    CurvStruct b_CurvStruct2_C;
    CurvStruct b_ctx;
    CurvStruct last;
    CurvStruct opt_curv;
    double a__1[3];
    double a__2[3];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    double dv7[3];
    double dv8[3];
    double r0D1[3];
    double r1D1[3];
    char b_cv[1025];
    char message[39];
    bool b_optimized;
    bool c_optimized;
    bool quit;
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
    //  end_flag = false;
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
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:21' case Fopt.Init
        // 'FeedoptPlan:22' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        break;
    case Fopt_GCode: {
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
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
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
            if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
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
    case Fopt_Check: {
        unsigned int N;
        int i1;
        // 'FeedoptPlan:55' case Fopt.Check
        // 'FeedoptPlan:56' ctx = CheckCurvStructs(ctx);
        // 'CheckCurvStructs:3' N = ctx.q_gcode.size;
        N = ctx->q_gcode.size();
        // 'CheckCurvStructs:5' DebugLog(DebugCfg.Validate, 'Checking for cusps...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Checking for cusps...\n");
            fflush(stdout);
        }
        // 'CheckCurvStructs:6' DebugLog(DebugCfg.OptimProgress, 'Checking for cusps...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Checking for cusps...\n");
            fflush(stdout);
        }
        // 'CheckCurvStructs:8' for k = 1:N-1
        i1 = static_cast<int>(N - 1U);
        for (int k{0}; k < i1; k++) {
            double absx;
            double b_n;
            double x;
            signed char n;
            // 'CheckCurvStructs:9' Curv1 = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k + 1U, &Curv1);
            // 'CheckCurvStructs:10' Curv2 = ctx.q_gcode.get(k+1);
            ctx->q_gcode.get(k - 4294967294U, &Curv2);
            // 'CheckCurvStructs:12' [~, r0D1] = EvalCurvStruct(ctx, Curv1, 1);
            c_EvalCurvStruct(&ctx->q_splines, Curv1.Type, Curv1.P0, Curv1.P1,
                             Curv1.CorrectedHelixCenter, Curv1.evec, Curv1.theta, Curv1.pitch,
                             Curv1.CoeffP5, Curv1.sp_index, Curv1.a_param, Curv1.b_param, a__1,
                             r0D1);
            // 'CheckCurvStructs:13' [~, r1D1] = EvalCurvStruct(ctx, Curv2, 0);
            b_EvalCurvStruct(&ctx->q_splines, Curv2.Type, Curv2.P0, Curv2.P1,
                             Curv2.CorrectedHelixCenter, Curv2.evec, Curv2.theta, Curv2.pitch,
                             Curv2.CoeffP5, Curv2.sp_index, Curv2.a_param, Curv2.b_param, a__2,
                             r1D1);
            // 'CheckCurvStructs:15' if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
            // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
            x = rt_remd(180.0 - ctx->cfg.CuspThreshold, 360.0);
            absx = std::abs(x);
            if (absx > 180.0) {
                if (x > 0.0) {
                    x -= 360.0;
                } else {
                    x += 360.0;
                }
                absx = std::abs(x);
            }
            if (absx <= 45.0) {
                x *= 0.017453292519943295;
                n = 0;
            } else if (absx <= 135.0) {
                if (x > 0.0) {
                    x = 0.017453292519943295 * (x - 90.0);
                    n = 1;
                } else {
                    x = 0.017453292519943295 * (x + 90.0);
                    n = -1;
                }
            } else if (x > 0.0) {
                x = 0.017453292519943295 * (x - 180.0);
                n = 2;
            } else {
                x = 0.017453292519943295 * (x + 180.0);
                n = -2;
            }
            if (n == 0) {
                b_n = std::cos(x);
            } else if (n == 1) {
                b_n = -std::sin(x);
            } else if (n == -1) {
                b_n = std::sin(x);
            } else {
                b_n = -std::cos(x);
            }
            if (((r0D1[0] * r1D1[0] + r0D1[1] * r1D1[1]) + r0D1[2] * r1D1[2]) /
                    (coder::b_norm(r0D1) * coder::b_norm(r1D1)) <
                b_n) {
                // 'CheckCurvStructs:16' switch Curv1.zspdmode
                switch (Curv1.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:17' case ZSpdMode.NN
                    // 'CheckCurvStructs:18' Curv1.zspdmode = ZSpdMode.NZ;
                    Curv1.zspdmode = ZSpdMode_NZ;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:19' case ZSpdMode.ZN
                    // 'CheckCurvStructs:20' Curv1.zspdmode = ZSpdMode.ZZ;
                    Curv1.zspdmode = ZSpdMode_ZZ;
                    break;
                case ZSpdMode_NZ:
                    // 'CheckCurvStructs:21' case ZSpdMode.NZ
                    //  Nothing to do
                    break;
                default:
                    // 'CheckCurvStructs:23' case ZSpdMode.ZZ
                    //  Nothing to do
                    break;
                }
                // 'CheckCurvStructs:27' switch Curv2.zspdmode
                switch (Curv2.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:28' case ZSpdMode.NN
                    // 'CheckCurvStructs:29' Curv2.zspdmode = ZSpdMode.ZN;
                    Curv2.zspdmode = ZSpdMode_ZN;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:30' case ZSpdMode.ZN
                    //  Nothing to do
                    break;
                case ZSpdMode_NZ:
                    // 'CheckCurvStructs:32' case ZSpdMode.NZ
                    // 'CheckCurvStructs:33' Curv2.zspdmode = ZSpdMode.ZZ;
                    Curv2.zspdmode = ZSpdMode_ZZ;
                    break;
                default:
                    // 'CheckCurvStructs:34' case ZSpdMode.ZZ
                    //  Nothing to do
                    break;
                }
                // 'CheckCurvStructs:38' ctx.q_gcode.set(k,   Curv1);
                ctx->q_gcode.set(k + 1U, &Curv1);
                // 'CheckCurvStructs:39' ctx.q_gcode.set(k+1, Curv2);
                ctx->q_gcode.set(k - 4294967294U, &Curv2);
            }
        }
        // 'FeedoptPlan:57' ctx.op = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        // 'FeedoptPlan:59' case Fopt.Compress
        // 'FeedoptPlan:60' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            // 'FeedoptPlan:61' ctx = ExpandZeroStructs(ctx);
            //  ExpandZeroStructs :
            //  - Is feeded by the queue : q_gcode
            //  - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves if
            //  they contain a zero speed.
            //  - Fill the queue : q_compress
            //
            //  Note : No compression is performed
            // 'ExpandZeroStructs:10' if ctx.q_gcode.isempty()
            if (!ctx->q_gcode.isempty()) {
                unsigned int Ncrv;
                int i3;
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
                i3 = static_cast<int>(Ncrv);
                for (int c_k{0}; c_k < i3; c_k++) {
                    // 'ExpandZeroStructs:18' Curv = ctx.q_gcode.get(k);
                    ctx->q_gcode.get(static_cast<double>(c_k) + 1.0, &Curv);
                    // 'ExpandZeroStructs:20' if Curv.zspdmode == ZSpdMode.ZN
                    if (Curv.zspdmode == ZSpdMode_ZN) {
                        // 'ExpandZeroStructs:21' [CurvStruct1_C, CurvStruct2_C] = cutZeroStart(
                        // ctx, Curv );
                        cutZeroStart(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                     &Curv, &CurvStruct1_C, &CurvStruct2_C);
                        // 'ExpandZeroStructs:22' ctx.q_compress.push(CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        // 'ExpandZeroStructs:23' ctx.q_compress.push(CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_NZ) {
                        // 'ExpandZeroStructs:24' elseif Curv.zspdmode == ZSpdMode.NZ
                        // 'ExpandZeroStructs:25' [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd( ctx,
                        // Curv );
                        cutZeroEnd(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                   &Curv, &CurvStruct1_C, &CurvStruct2_C);
                        // 'ExpandZeroStructs:26' ctx.q_compress.push(CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        // 'ExpandZeroStructs:27' ctx.q_compress.push(CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                        // 'ExpandZeroStructs:28' elseif Curv.zspdmode == ZSpdMode.ZZ
                        // 'ExpandZeroStructs:29' [CurvStruct1_C, CurvStruct2_C] = cutZeroStart(
                        // ctx, Curv );
                        cutZeroStart(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                     &Curv, &CurvStruct1_C, &CurvStruct2_C);
                        // 'ExpandZeroStructs:30' [CurvStruct2_C, CurvStruct3_C] = cutZeroEnd( ctx,
                        // CurvStruct2_C );
                        cutZeroEnd(&ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                   &CurvStruct2_C, &b_CurvStruct2_C, &CurvStruct3_C);
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
        } else {
            // 'FeedoptPlan:62' else
            // 'FeedoptPlan:63' ctx = CompressCurvStructs(ctx);
            CompressCurvStructs(ctx);
        }
        // 'FeedoptPlan:65' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:66' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth:
        // 'FeedoptPlan:68' case Fopt.Smooth
        // 'FeedoptPlan:69' ctx = SmoothCurvStructs(ctx);
        SmoothCurvStructs(ctx);
        // 'FeedoptPlan:70' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:71' if( coder.target( 'MATLAB') )
        break;
    case Fopt_Split: {
        // 'FeedoptPlan:73' case Fopt.Split
        // 'FeedoptPlan:74' ctx = SplitCurvStructs(ctx);
        // 'SplitCurvStructs:3' if ctx.q_smooth.isempty()
        if (!ctx->q_smooth.isempty()) {
            unsigned int b_N;
            int i2;
            // 'SplitCurvStructs:7' N = ctx.q_smooth.size;
            b_N = ctx->q_smooth.size();
            // 'SplitCurvStructs:9' DebugLog(DebugCfg.Validate, 'Splitting...\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Splitting...\n");
                fflush(stdout);
            }
            // 'SplitCurvStructs:10' DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Splitting...\n");
                fflush(stdout);
            }
            // 'SplitCurvStructs:12' for k = 1:N
            i2 = static_cast<int>(b_N);
            for (int b_k{0}; b_k < i2; b_k++) {
                // 'SplitCurvStructs:13' ctx = SplitCurvStruct(ctx, ctx.q_smooth.get(k));
                ctx->q_smooth.get(b_k + 1U, &CurvStrct);
                //  coder.varsize('CrvStructs', [1, 100], [0, 1]);
                //
                // 'SplitCurvStruct:4' Type  = CurvStrct.Type;
                // 'SplitCurvStruct:6' if Type~=CurveType.TransP5 && CurvStrct.UseConstJerk == 0
                if ((CurvStrct.Type != CurveType_TransP5) && (!CurvStrct.UseConstJerk)) {
                    // 'SplitCurvStruct:8' if Type==CurveType.Line || Type==CurveType.Helix
                    if ((CurvStrct.Type == CurveType_Line) || (CurvStrct.Type == CurveType_Helix)) {
                        double L;
                        double a;
                        double b;
                        // 'SplitCurvStruct:9' ctx = SplitLineHelix(ctx, CurvStrct);
                        // 'SplitLineHelix:3' a=Curv.a_param;
                        a = CurvStrct.a_param;
                        // 'SplitLineHelix:4' b=Curv.b_param;
                        b = CurvStrct.b_param;
                        // 'SplitLineHelix:6' L=LengthCurv(ctx, Curv, 0, 1);
                        L = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, CurvStrct.Type, CurvStrct.P0,
                                       CurvStrct.P1, CurvStrct.CorrectedHelixCenter, CurvStrct.evec,
                                       CurvStrct.theta, CurvStrct.pitch, CurvStrct.CoeffP5,
                                       CurvStrct.sp_index, CurvStrct.a_param, CurvStrct.b_param);
                        // 'SplitLineHelix:7' L_split=ctx.cfg.LSplit;
                        // 'SplitLineHelix:9' if L<2*L_split
                        if (L < 2.0 * ctx->cfg.LSplit) {
                            // 'SplitLineHelix:10' ctx.q_split.push(Curv);
                            ctx->q_split.push(&CurvStrct);
                        } else {
                            double L_split;
                            double c_N;
                            int i4;
                            // 'SplitLineHelix:14' N = ceil(L/L_split);
                            c_N = std::ceil(L / ctx->cfg.LSplit);
                            // 'SplitLineHelix:16' L_split = L/N;
                            L_split = L / c_N;
                            // 'SplitLineHelix:18' for k = 1:N
                            i4 = static_cast<int>(c_N);
                            for (int d_k{0}; d_k < i4; d_k++) {
                                double u_tilda_0;
                                double u_tilda_0_tmp;
                                // 'SplitLineHelix:20' u_0 = (k-1)*(L_split/L);
                                // 'SplitLineHelix:21' u_1 = k*(L_split/L);
                                // 'SplitLineHelix:23' u_tilda_0 = a*u_0+b;
                                u_tilda_0_tmp = L_split / L;
                                u_tilda_0 =
                                    a * (((static_cast<double>(d_k) + 1.0) - 1.0) * u_tilda_0_tmp) +
                                    b;
                                // 'SplitLineHelix:24' u_tilda_1 = a*u_1+b;
                                // 'SplitLineHelix:26' Curv.a_param = u_tilda_1 - u_tilda_0;
                                CurvStrct.a_param =
                                    (a * ((static_cast<double>(d_k) + 1.0) * u_tilda_0_tmp) + b) -
                                    u_tilda_0;
                                // 'SplitLineHelix:27' Curv.b_param = u_tilda_0;
                                CurvStrct.b_param = u_tilda_0;
                                // 'SplitLineHelix:29' ctx.q_split.push(Curv);
                                ctx->q_split.push(&CurvStrct);
                            }
                        }
                    } else {
                        double ux_tilda;
                        // 'SplitCurvStruct:10' else
                        // 'SplitCurvStruct:11' ctx = SplitSpline(ctx, CurvStrct);
                        // 'SplitSpline:4' Spline=ctx.q_splines.get(Curv.sp_index);
                        ctx->q_splines.get(CurvStrct.sp_index, &b_ctx);
                        // 'SplitSpline:5' sp = Spline.sp;
                        // 'SplitSpline:7' L_split=ctx.cfg.LSplit;
                        // 'SplitSpline:9' a=Curv.a_param;
                        // 'SplitSpline:10' b=Curv.b_param;
                        // 'SplitSpline:11' u0_tilda = a*0+b;
                        // 'SplitSpline:12' u1_tilda = a*1+b;
                        // 'SplitSpline:14' ux_tilda  = SplineLengthFindU_up(ctx, Curv, L_split,
                        // u0_tilda);
                        ux_tilda = SplineLengthFindU_up(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                        ctx->cfg.GaussLegendreW, CurvStrct.sp_index,
                                                        ctx->cfg.LSplit, CurvStrct.b_param);
                        // 'SplitSpline:16' if ux_tilda ~= -1
                        if (ux_tilda != -1.0) {
                            //  if spline is not too short
                            // 'SplitSpline:17' Curv.a_param = ux_tilda - u0_tilda;
                            CurvStrct.a_param = ux_tilda - CurvStrct.b_param;
                        }
                        // 'SplitSpline:19' ctx.q_split.push(Curv);
                        ctx->q_split.push(&CurvStrct);
                    }
                } else {
                    // 'SplitCurvStruct:14' else
                    // 'SplitCurvStruct:15' ctx.q_split.push(CurvStrct);
                    ctx->q_split.push(&CurvStrct);
                }
            }
        }
        // 'FeedoptPlan:76' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:77' if( coder.target( 'MATLAB') )
        // 'FeedoptPlan:79' DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
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
        // 'FeedoptPlan:80' if coder.target('matlab')
    } break;
    case Fopt_Opt:
        // 'FeedoptPlan:84' case Fopt.Opt
        // 'FeedoptPlan:85' [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
        feedratePlanning(ctx, &c_optimized, &opt_curv, &quit);
        b_optimized = c_optimized;
        // 'FeedoptPlan:87' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:88' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:89' ctx.q_opt.push( opt_curv );
            ctx->q_opt.push(&opt_curv);
        }
        // 'FeedoptPlan:92' if( quit )
        break;
    case Fopt_Finished:
        // 'FeedoptPlan:94' case Fopt.Finished
        // 'FeedoptPlan:95' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:97' otherwise
        // 'FeedoptPlan:98' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:99' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    }
    *optimized = b_optimized;
}

} // namespace ocn

//
// File trailer for FeedoptPlan.cpp
//
// [EOF]
//
