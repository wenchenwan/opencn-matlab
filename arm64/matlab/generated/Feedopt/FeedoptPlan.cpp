//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "FeedoptPlan.h"
#include "EvalCurvStruct.h"
#include "calcTransition.h"
#include "compressCurvStructs.h"
#include "constrCurvStruct.h"
#include "feedratePlanning.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "splitQueue.h"
#include "coder_array.h"
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
    ::coder::array<double, 2U> params_tmp_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_tmp_spline_Lk;
    ::coder::array<double, 2U> params_tmp_spline_coeff;
    ::coder::array<double, 2U> params_tmp_spline_knots;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r1D1;
    CurvStruct Curv1;
    CurvStruct Curv2;
    CurvStruct b_CurvStruct;
    CurvStruct curv;
    CurvStruct curvC1;
    CurvStruct curvC2;
    CurvStruct curvT;
    CurvStruct last;
    CurvStruct nextCurv;
    CurvStruct opt_curv;
    CurvStruct opt_struct_tmp;
    CurvStruct r;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_spline_Ltot;
    unsigned long params_tmp_spline_Bl_handle;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_spline_Bl_ncoeff;
    int params_tmp_spline_Bl_order;
    char b_cv[1025];
    char message[39];
    bool b_optimized;
    bool c_optimized;
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    bool quit;
    CurveType params_tmp_gcodeInfoStruct_Type;
    TransitionResult b_status;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptPlan:5' c_assert( ctx.errcode == FeedoptPlanError.Success, ...
    // 'FeedoptPlan:6'                                 'FeedoptPlan: error code was not handled' );
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
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
    // 'FeedoptPlan:10' opt_struct = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_tmp_gcodeInfoStruct_Type, &params_tmp_gcodeInfoStruct_zspdmode,
        &params_tmp_gcodeInfoStruct_TRAFO, &params_tmp_gcodeInfoStruct_HSC,
        &params_tmp_gcodeInfoStruct_FeedRate, &params_tmp_gcodeInfoStruct_SpindleSpeed,
        &params_tmp_gcodeInfoStruct_gcode_source_line, &params_tmp_gcodeInfoStruct_G91,
        &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_spline_Bl_ncoeff,
        params_tmp_spline_Bl_breakpoints, &params_tmp_spline_Bl_handle, &params_tmp_spline_Bl_order,
        params_tmp_spline_coeff, params_tmp_spline_knots, &params_tmp_spline_Ltot,
        params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1, params_tmp_Cprim, &expl_temp,
        params_tmp_evec, &b_expl_temp, &c_expl_temp, params_tmp_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
                       params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
                       params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
                       params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
                       params_tmp_gcodeInfoStruct_G91_1, params_tmp_spline_Bl_ncoeff,
                       params_tmp_spline_Bl_breakpoints, params_tmp_spline_Bl_handle,
                       params_tmp_spline_Bl_order, params_tmp_spline_coeff, params_tmp_spline_knots,
                       params_tmp_spline_Ltot, params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1,
                       params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &opt_struct_tmp);
    *opt_struct = opt_struct_tmp;
    // 'FeedoptPlan:12' switch ctx.op
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:13' case Fopt.Init
        // 'FeedoptPlan:14' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        //
        break;
    case Fopt_GCode: {
        int status;
        // 'FeedoptPlan:16' case Fopt.GCode
        // 'FeedoptPlan:17' status = int32( ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source ) );
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' status = int32(0);
        // 'ReadGCode:8' CurvStruct = constrCurvStructType;
        // 'ReadGCode:10' if coder.target('mex')
        // 'ReadGCode:86' elseif coder.target('rtw')
        // 'ReadGCode:88' if cmd == ReadGCodeCmd.Load
        // 'ReadGCode:90' CurvStruct = constrCurvStructType;
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline,
        // ... 'constrCurvStructType:14'         params.R0, params.R1, ... 'constrCurvStructType:15'
        // params.Cprim, params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
        // params.pitch, params.CoeffP5, params.Coeff );
        b_CurvStruct = opt_struct_tmp;
        // 'ReadGCode:91' status = int32( 0 );
        // 'ReadGCode:92' status = coder.ceval( 'c_open_gcode', [filename, 0], coder.ref( CurvStruct
        // ) );
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = c_open_gcode(&b_cv[0], &b_CurvStruct);
        // 'FeedoptPlan:18' DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
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
        //
        // 'FeedoptPlan:20' while status
        while (status != 0) {
            int c_status;
            // 'FeedoptPlan:21' [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, '' );
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' status = int32(0);
            // 'ReadGCode:8' CurvStruct = constrCurvStructType;
            // 'ReadGCode:10' if coder.target('mex')
            // 'ReadGCode:86' elseif coder.target('rtw')
            // 'ReadGCode:88' if cmd == ReadGCodeCmd.Load
            // 'ReadGCode:93' elseif cmd == ReadGCodeCmd.Read
            // 'ReadGCode:95' CurvStruct = constrCurvStructType;
            //  constrCurvStructType : Constructs a constrCurvStruct with default values.
            // 'constrCurvStructType:4' if( nargin > 0 )
            // 'constrCurvStructType:6' else
            // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
            // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
            // 'constrCurvStructType:12' else
            // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
            // params.spline, ... 'constrCurvStructType:14'         params.R0, params.R1, ...
            // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec,
            // params.theta, ... 'constrCurvStructType:16'         params.pitch, params.CoeffP5,
            // params.Coeff );
            b_CurvStruct = opt_struct_tmp;
            // 'ReadGCode:96' status = int32( 0 );
            // 'ReadGCode:97' status = coder.ceval( 'c_read_and_exec_gcode', '', coder.ref(
            // CurvStruct ) );
            c_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            // 'ReadGCode:100' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            // 'ReadGCode:101' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
            b_CurvStruct.R0[3] *= 0.017453292519943295;
            b_CurvStruct.R1[3] *= 0.017453292519943295;
            b_CurvStruct.R0[4] *= 0.017453292519943295;
            b_CurvStruct.R1[4] *= 0.017453292519943295;
            b_CurvStruct.R0[5] *= 0.017453292519943295;
            b_CurvStruct.R1[5] *= 0.017453292519943295;
            status = c_status;
            // 'FeedoptPlan:22' if( CurvStruct.Info.FeedRate == 0 )
            if (b_CurvStruct.Info.FeedRate == 0.0) {
                // 'FeedoptPlan:23' CurvStruct.Info.FeedRate = ctx.cfg.vmax;
                b_CurvStruct.Info.FeedRate = ctx->cfg.vmax;
            }
            // 'FeedoptPlan:25' if( status == 1 && CurvStruct.Info.Type ~= 0 )
            if ((c_status == 1) && (static_cast<int>(b_CurvStruct.Info.Type) != 0)) {
                // 'FeedoptPlan:26' if ( CurvStruct.Info.FeedRate == 0.0 )
                if (b_CurvStruct.Info.FeedRate == 0.0) {
                    //  check for undefined feedrate
                    // 'FeedoptPlan:28' CurvStruct.Info.FeedRate = ctx.cfg.vmax;
                    b_CurvStruct.Info.FeedRate = ctx->cfg.vmax;
                }
                //                  PrintCurvStruct( ctx, CurvStruct );
                // 'FeedoptPlan:31' ctx.q_gcode.push( CurvStruct );
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:34' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:35' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:36' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:37'                 'ERROR: Optimization failed, Gcode queue is
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
            // 'FeedoptPlan:40' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:41' if last.Info.zspdmode == ZSpdMode.NN
            if (last.Info.zspdmode == ZSpdMode_NN) {
                // 'FeedoptPlan:42' last.Info.zspdmode = ZSpdMode.NZ;
                last.Info.zspdmode = ZSpdMode_NZ;
            } else if (last.Info.zspdmode == ZSpdMode_ZN) {
                // 'FeedoptPlan:43' elseif last.Info.zspdmode == ZSpdMode.ZN
                // 'FeedoptPlan:44' last.Info.zspdmode = ZSpdMode.ZZ;
                last.Info.zspdmode = ZSpdMode_ZZ;
            }
            // 'FeedoptPlan:46' ctx.q_gcode.set( ctx.q_gcode.size, last );
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:48' ctx.op = Fopt.Check;
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check: {
        unsigned int N;
        int i2;
        // 'FeedoptPlan:50' case Fopt.Check
        // 'FeedoptPlan:51' ctx     = CheckCurvStructs( ctx );
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
        i2 = static_cast<int>(N - 1U);
        for (int k{0}; k < i2; k++) {
            double absx;
            double b_n;
            double c;
            double x;
            int i3;
            signed char n;
            // 'CheckCurvStructs:9' Curv1 = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k + 1U, &Curv1);
            // 'CheckCurvStructs:10' Curv2 = ctx.q_gcode.get(k+1);
            ctx->q_gcode.get(k - 4294967294U, &Curv2);
            // 'CheckCurvStructs:12' [~, r0D1] = EvalCurvStruct(ctx, Curv1, 1);
            b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                             ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                             ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                             Curv1.Info.Type, Curv1.R0, Curv1.R1, Curv1.CorrectedHelixCenter,
                             Curv1.evec, Curv1.theta, Curv1.pitch, Curv1.CoeffP5, Curv1.sp_index,
                             Curv1.a_param, Curv1.b_param, a__1, r0D1);
            // 'CheckCurvStructs:13' [~, r1D1] = EvalCurvStruct(ctx, Curv2, 0);
            c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                             ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                             ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                             Curv2.Info.Type, Curv2.R0, Curv2.R1, Curv2.CorrectedHelixCenter,
                             Curv2.evec, Curv2.theta, Curv2.pitch, Curv2.CoeffP5, Curv2.sp_index,
                             Curv2.a_param, Curv2.b_param, a__2, r1D1);
            // 'CheckCurvStructs:15' if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
            // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
            c = 0.0;
            i3 = r0D1.size(0);
            if (r0D1.size(0) >= 1) {
                for (int c_k{0}; c_k < i3; c_k++) {
                    c += r0D1[c_k] * r1D1[c_k];
                }
            }
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
            if (c / (coder::b_norm(r0D1) * coder::b_norm(r1D1)) < b_n) {
                // 'CheckCurvStructs:16' switch Curv1.Info.zspdmode
                switch (Curv1.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:17' case ZSpdMode.NN
                    // 'CheckCurvStructs:18' Curv1.Info.zspdmode = ZSpdMode.NZ;
                    Curv1.Info.zspdmode = ZSpdMode_NZ;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:19' case ZSpdMode.ZN
                    // 'CheckCurvStructs:20' Curv1.Info.zspdmode = ZSpdMode.ZZ;
                    Curv1.Info.zspdmode = ZSpdMode_ZZ;
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
                // 'CheckCurvStructs:27' switch Curv2.Info.zspdmode
                switch (Curv2.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:28' case ZSpdMode.NN
                    // 'CheckCurvStructs:29' Curv2.Info.zspdmode = ZSpdMode.ZN;
                    Curv2.Info.zspdmode = ZSpdMode_ZN;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:30' case ZSpdMode.ZN
                    //  Nothing to do
                    break;
                case ZSpdMode_NZ:
                    // 'CheckCurvStructs:32' case ZSpdMode.NZ
                    // 'CheckCurvStructs:33' Curv2.Info.zspdmode = ZSpdMode.ZZ;
                    Curv2.Info.zspdmode = ZSpdMode_ZZ;
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
        // 'FeedoptPlan:52' ctx.op  = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        // 'FeedoptPlan:54' case Fopt.Compress
        // 'FeedoptPlan:55' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i1;
            unsigned int u;
            // 'FeedoptPlan:56' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i1 = static_cast<int>(u);
            for (int j{0}; j < i1; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:57' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r);
                ctx->q_compress.push(&r);
            }
        } else {
            // 'FeedoptPlan:59' else
            // 'FeedoptPlan:60' ctx = compressCurvStructs(ctx);
            compressCurvStructs(ctx);
        }
        // 'FeedoptPlan:63' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:64' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        // 'FeedoptPlan:66' case Fopt.Smooth
        // 'FeedoptPlan:67' ctx = smoothCurvStructs(ctx);
        //  Optimal transitions calculation between segments whith G2 continuity
        // 'smoothCurvStructs:5' if ctx.q_compress.isempty()
        if (!ctx->q_compress.isempty()) {
            unsigned int Ncrv;
            // 'smoothCurvStructs:7' Ncrv = ctx.q_compress.size;
            Ncrv = ctx->q_compress.size();
            // 'smoothCurvStructs:9' DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
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
            // 'smoothCurvStructs:10' DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );
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
            // 'smoothCurvStructs:13' curv = ctx.q_compress.get( 1 );
            ctx->q_compress.get(&curv);
            // 'smoothCurvStructs:14' for k = 2 : Ncrv
            for (unsigned int b_k{2U}; b_k <= Ncrv; b_k++) {
                // 'smoothCurvStructs:15' nextCurv = ctx.q_compress.get( k );
                ctx->q_compress.get(b_k, &nextCurv);
                //  Check neither of the two curves has a zero speed.
                // 'smoothCurvStructs:17' if( isAZeroEnd( curv ) || isAZeroStart( nextCurv ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ) ||
                    ((nextCurv.Info.zspdmode == ZSpdMode_ZN) ||
                     (nextCurv.Info.zspdmode == ZSpdMode_ZZ))) {
                    // 'isAZeroEnd:7' zeroFlag = true;
                    // 'isAZeroStart:6' zeroFlag = true;
                    // 'smoothCurvStructs:18' ctx.programmed_stop = ctx.programmed_stop + 1;
                    ctx->programmed_stop++;
                    // 'smoothCurvStructs:19' ctx.q_smooth.push( curv );
                    ctx->q_smooth.push(&curv);
                    // 'smoothCurvStructs:20' curv = nextCurv;
                    curv = nextCurv;
                } else {
                    // 'isAZeroEnd:9' zeroFlag = false;
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    // 'isAZeroStart:8' zeroFlag = false;
                    // 'smoothCurvStructs:21' else
                    //  Computes transition
                    // 'smoothCurvStructs:23' [ curvC1, curvT, curvC2, status ] = ...
                    // 'smoothCurvStructs:24'         calcTransition( ctx, curv, nextCurv );
                    calcTransition(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                                   ctx->cfg.indRot.data, ctx->cfg.indRot.size[0],
                                   ctx->cfg.indTot.data, ctx->cfg.indTot.size[0], ctx->cfg.CutOff,
                                   ctx->cfg.ColTolCosSmooth, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &curv, &nextCurv, &curvC1, &curvT,
                                   &curvC2, &b_status);
                    // 'smoothCurvStructs:26' if      ( status == TransitionResult.Ok )
                    if (b_status == TransitionResult_Ok) {
                        // 'smoothCurvStructs:27' ctx.q_smooth.push( curvC1 );
                        ctx->q_smooth.push(&curvC1);
                        // 'smoothCurvStructs:28' ctx.q_smooth.push( curvT );
                        ctx->q_smooth.push(&curvT);
                        // 'smoothCurvStructs:29' curv = curvC2;
                        curv = curvC2;
                    } else if (b_status == TransitionResult_Collinear) {
                        // 'smoothCurvStructs:30' elseif  ( status == TransitionResult.Collinear )
                        // 'smoothCurvStructs:31' ctx.q_smooth.push( curv );
                        ctx->q_smooth.push(&curv);
                        // 'smoothCurvStructs:32' curv = nextCurv;
                        curv = nextCurv;
                    } else {
                        // 'smoothCurvStructs:33' else
                        //  If the transition fails, force a zero-stop
                        // 'smoothCurvStructs:34' ctx.forced_stop = ctx.forced_stop + 1;
                        ctx->forced_stop++;
                        // 'smoothCurvStructs:35' curv.Info.zspdmode      = ZSpdMode.NZ;
                        curv.Info.zspdmode = ZSpdMode_NZ;
                        // 'smoothCurvStructs:36' nextCurv.Info.zspdmode  = ZSpdMode.ZN;
                        nextCurv.Info.zspdmode = ZSpdMode_ZN;
                        // 'smoothCurvStructs:37' ctx.q_smooth.push( curv );
                        ctx->q_smooth.push(&curv);
                        // 'smoothCurvStructs:38' curv = nextCurv;
                        curv = nextCurv;
                    }
                }
            }
            // 'smoothCurvStructs:43' ctx.q_smooth.push( curv );
            ctx->q_smooth.push(&curv);
        }
        // 'FeedoptPlan:68' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:69' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Split:
        // 'FeedoptPlan:71' case Fopt.Split
        // 'FeedoptPlan:72' ctx = splitQueue( ctx );
        splitQueue(ctx);
        // 'FeedoptPlan:73' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:75' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:77' DebugLog(DebugCfg.Validate, 'Feedrate Planning...\n');
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
        // 'FeedoptPlan:78' if coder.target('matlab')
        break;
    case Fopt_Opt:
        // 'FeedoptPlan:82' case Fopt.Opt
        //          ctx.op = Fopt.Finished;
        //          return;
        // 'FeedoptPlan:85' [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
        feedratePlanning(ctx, &c_optimized, &opt_curv, &quit);
        b_optimized = c_optimized;
        // 'FeedoptPlan:86' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:87' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:88' ctx.q_opt.push( opt_curv );
            ctx->q_opt.push(&opt_curv);
        }
        // 'FeedoptPlan:91' if( quit )
        break;
    case Fopt_Finished:
        // 'FeedoptPlan:93' case Fopt.Finished
        // 'FeedoptPlan:94' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:96' otherwise
        // 'FeedoptPlan:97' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:98' ctx.op = Fopt.Finished;
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
