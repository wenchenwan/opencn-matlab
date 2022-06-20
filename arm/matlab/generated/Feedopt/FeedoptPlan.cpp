//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
//

// Include Files
#include "FeedoptPlan.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcTransition.h"
#include "compressCurvStructs_new.h"
#include "constrCurvStruct.h"
#include "feedratePlanning.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "opencn_matlab_types31.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "splitQueue.h"
#include "string1.h"
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
    static const uint64m_T r17{
        {2U, 0U} // chunks
    };
    static const uint64m_T r19{
        {16U, 0U} // chunks
    };
    static const uint64m_T r2{
        {8U, 0U} // chunks
    };
    static const uint64m_T r4{
        {0U, 0U} // chunks
    };
    static const uint64m_T r8{
        {128U, 0U} // chunks
    };
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
    CurvStruct r5;
    b_FeedoptContext b_ctx;
    b_FeedoptContext r;
    uint64m_T params_tmp_spline_Bl_handle;
    uint64m_T r1;
    uint64m_T r10;
    uint64m_T r12;
    uint64m_T r13;
    uint64m_T r15;
    uint64m_T r16;
    uint64m_T r18;
    uint64m_T r20;
    uint64m_T r3;
    uint64m_T r6;
    uint64m_T r9;
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
    TransitionResult c_status;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptPlan:5' c_assert( ctx.errcode == FeedoptPlanError.Success, ...
    // 'FeedoptPlan:6'     'FeedoptPlan: error code was not handled' );
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
        uint64m_T r7;
        int status;
        // 'FeedoptPlan:16' case Fopt.GCode
        // 'FeedoptPlan:17' status = int32( ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source ) );
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' status = int32(0);
        // 'ReadGCode:8' CurvStruct = constrCurvStructType;
        // 'ReadGCode:10' if coder.target('mex')
        // 'ReadGCode:88' elseif coder.target('rtw')
        // 'ReadGCode:90' if cmd == ReadGCodeCmd.Load
        // 'ReadGCode:92' CurvStruct = constrCurvStructType;
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
        // 'ReadGCode:93' status = int32( 0 );
        // 'ReadGCode:94' status = coder.ceval( 'c_open_gcode', [filename, 0], coder.ref( CurvStruct
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
        Double2MultiWord(DebugConfig, (unsigned int *)&r6.chunks[0U]);
        r7 = r8;
        MultiWordAnd((unsigned int *)&r6.chunks[0U], (unsigned int *)&r8.chunks[0U],
                     (unsigned int *)&r9.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r9.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        //
        // 'FeedoptPlan:20' while status
        while (status != 0) {
            int b_status;
            // 'FeedoptPlan:21' [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, '' );
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' status = int32(0);
            // 'ReadGCode:8' CurvStruct = constrCurvStructType;
            // 'ReadGCode:10' if coder.target('mex')
            // 'ReadGCode:88' elseif coder.target('rtw')
            // 'ReadGCode:90' if cmd == ReadGCodeCmd.Load
            // 'ReadGCode:95' elseif cmd == ReadGCodeCmd.Read
            // 'ReadGCode:97' CurvStruct = constrCurvStructType;
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
            // 'ReadGCode:98' status = int32( 0 );
            // 'ReadGCode:99' status = coder.ceval( 'c_read_and_exec_gcode', '', coder.ref(
            // CurvStruct ) );
            b_status = c_read_and_exec_gcode(nullptr, &b_CurvStruct);
            // 'ReadGCode:100' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            // 'ReadGCode:101' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
            b_CurvStruct.R0[3] *= 0.017453292519943295;
            b_CurvStruct.R1[3] *= 0.017453292519943295;
            b_CurvStruct.R0[4] *= 0.017453292519943295;
            b_CurvStruct.R1[4] *= 0.017453292519943295;
            b_CurvStruct.R0[5] *= 0.017453292519943295;
            b_CurvStruct.R1[5] *= 0.017453292519943295;
            status = b_status;
            // 'FeedoptPlan:23' for j = 1 : StructTypeName.NumberAxisMax
            // 'FeedoptPlan:32' if( CurvStruct.Info.FeedRate == 0.0 )
            if (b_CurvStruct.Info.FeedRate == 0.0) {
                // 'FeedoptPlan:33' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                b_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
            }
            // 'FeedoptPlan:35' if( status == 1 && CurvStruct.Info.Type ~= 0 )
            if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Info.Type) != 0)) {
                // 'FeedoptPlan:36' if ( CurvStruct.Info.FeedRate == 0.0 )
                if (b_CurvStruct.Info.FeedRate == 0.0) {
                    //  check for undefined feedrate
                    // 'FeedoptPlan:38' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                    b_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
                }
                //                  PrintCurvStruct( ctx, CurvStruct );
                // 'FeedoptPlan:41' ctx.q_gcode.push( CurvStruct );
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:44' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:45' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:46' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:47'                 'ERROR: Optimization failed, Gcode queue is
            // empty\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r18.chunks[0U]);
            MultiWordAnd((unsigned int *)&r18.chunks[0U], (unsigned int *)&r19.chunks[0U],
                         (unsigned int *)&r7.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r7.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf( 1, varargin{:} );
                printf("ERROR: Optimization failed, Gcode queue is empty\n");
                fflush(stdout);
            }
        } else {
            // 'FeedoptPlan:50' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:51' if last.Info.zspdmode == ZSpdMode.NN
            if (last.Info.zspdmode == ZSpdMode_NN) {
                // 'FeedoptPlan:52' last.Info.zspdmode = ZSpdMode.NZ;
                last.Info.zspdmode = ZSpdMode_NZ;
            } else if (last.Info.zspdmode == ZSpdMode_ZN) {
                // 'FeedoptPlan:53' elseif last.Info.zspdmode == ZSpdMode.ZN
                // 'FeedoptPlan:54' last.Info.zspdmode = ZSpdMode.ZZ;
                last.Info.zspdmode = ZSpdMode_ZZ;
            }
            // 'FeedoptPlan:56' ctx.q_gcode.set( ctx.q_gcode.size, last );
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:58' ctx.op = Fopt.Check;
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check: {
        uint64m_T r11;
        unsigned int N;
        int ab_loop_ub;
        int c_loop_ub;
        int i42;
        int ib_loop_ub;
        int j_loop_ub;
        int r_loop_ub;
        // 'FeedoptPlan:60' case Fopt.Check
        // 'FeedoptPlan:61' ctx     = CheckCurvStructs( ctx );
        r.q_spline = ctx->q_spline;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        c_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= c_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[c_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        j_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i9{0}; i9 < j_loop_ub; i9++) {
            r.cfg.maskCart[i9] = ctx->cfg.maskCart[i9];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        r_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i17{0}; i17 < r_loop_ub; i17++) {
            r.cfg.maskRot[i17] = ctx->cfg.maskRot[i17];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ab_loop_ub = ctx->cfg.indCart.size[0];
        for (int i25{0}; i25 < ab_loop_ub; i25++) {
            r.cfg.indCart[i25] = ctx->cfg.indCart.data[i25];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ib_loop_ub = ctx->cfg.indRot.size[0];
        for (int i33{0}; i33 < ib_loop_ub; i33++) {
            r.cfg.indRot[i33] = ctx->cfg.indRot.data[i33];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.CuspThreshold = ctx->cfg.CuspThreshold;
        // 'CheckCurvStructs:3' N = ctx.q_gcode.size;
        N = ctx->q_gcode.size();
        // 'CheckCurvStructs:5' DebugLog(DebugCfg.Validate, 'Checking for cusps...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r10.chunks[0U]);
        r11 = r8;
        MultiWordAnd((unsigned int *)&r10.chunks[0U], (unsigned int *)&r8.chunks[0U],
                     (unsigned int *)&r12.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r12.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Checking for cusps...\n");
            fflush(stdout);
        }
        // 'CheckCurvStructs:6' DebugLog(DebugCfg.OptimProgress, 'Checking for cusps...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r16.chunks[0U]);
        MultiWordAnd((unsigned int *)&r16.chunks[0U], (unsigned int *)&r17.chunks[0U],
                     (unsigned int *)&r11.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r11.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Checking for cusps...\n");
            fflush(stdout);
        }
        // 'CheckCurvStructs:8' for k = 1:N-1
        i42 = static_cast<int>(N - 1U);
        for (int k{0}; k < i42; k++) {
            double absx;
            double b_n;
            double c;
            double x;
            int i53;
            signed char n;
            // 'CheckCurvStructs:9' Curv1 = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k + 1U, &Curv1);
            // 'CheckCurvStructs:10' Curv2 = ctx.q_gcode.get(k+1);
            ctx->q_gcode.get(k - 4294967294U, &Curv2);
            // 'CheckCurvStructs:12' [~, r0D1] = EvalCurvStruct( ctx, Curv1, 1 );
            b_EvalCurvStruct(&r.q_spline, r.cfg.maskTot.data, r.cfg.maskTot.size, r.cfg.maskCart,
                             r.cfg.maskRot, r.cfg.indCart, r.cfg.indRot, r.cfg.NumberAxis,
                             r.cfg.NCart, r.cfg.NRot, &Curv1, a__1, r0D1);
            // 'CheckCurvStructs:13' [~, r1D1] = EvalCurvStruct( ctx, Curv2, 0 );
            c_EvalCurvStruct(&r.q_spline, r.cfg.maskTot.data, r.cfg.maskTot.size, r.cfg.maskCart,
                             r.cfg.maskRot, r.cfg.indCart, r.cfg.indRot, r.cfg.NumberAxis,
                             r.cfg.NCart, r.cfg.NRot, &Curv2, a__2, r1D1);
            // 'CheckCurvStructs:15' if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
            // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
            c = 0.0;
            i53 = r0D1.size(0);
            if (r0D1.size(0) >= 1) {
                for (int c_k{0}; c_k < i53; c_k++) {
                    c += r0D1[c_k] * r1D1[c_k];
                }
            }
            x = rt_remd(180.0 - r.cfg.CuspThreshold, 360.0);
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
        // 'FeedoptPlan:62' ctx.op  = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        // 'FeedoptPlan:64' case Fopt.Compress
        // 'FeedoptPlan:65' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i3;
            unsigned int u;
            // 'FeedoptPlan:66' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i3 = static_cast<int>(u);
            for (int j{0}; j < i3; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:67' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r5);
                ctx->q_compress.push(&r5);
            }
        } else {
            int bc_loop_ub;
            int ce_loop_ub;
            int db_loop_ub;
            int dd_loop_ub;
            int e_loop_ub;
            int ec_loop_ub;
            int fe_loop_ub;
            int hc_loop_ub;
            int ie_loop_ub;
            int jd_loop_ub;
            int kc_loop_ub;
            int lb_loop_ub;
            int le_loop_ub;
            int m_loop_ub;
            int ob_loop_ub;
            int oe_loop_ub;
            int pd_loop_ub;
            int qc_loop_ub;
            int rb_loop_ub;
            int sd_loop_ub;
            int u_loop_ub;
            int ub_loop_ub;
            int vd_loop_ub;
            int wc_loop_ub;
            int xb_loop_ub;
            int yd_loop_ub;
            // 'FeedoptPlan:69' else
            // 'FeedoptPlan:70' ctx = compressCurvStructs_new(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            e_loop_ub = ctx->BasisVal.size(1);
            for (int i4{0}; i4 < e_loop_ub; i4++) {
                int k_loop_ub;
                k_loop_ub = ctx->BasisVal.size(0);
                for (int i10{0}; i10 < k_loop_ub; i10++) {
                    r.BasisVal[i10 + r.BasisVal.size(0) * i4] =
                        ctx->BasisVal[i10 + ctx->BasisVal.size(0) * i4];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            m_loop_ub = ctx->BasisValD.size(1);
            for (int i12{0}; i12 < m_loop_ub; i12++) {
                int s_loop_ub;
                s_loop_ub = ctx->BasisValD.size(0);
                for (int i18{0}; i18 < s_loop_ub; i18++) {
                    r.BasisValD[i18 + r.BasisValD.size(0) * i12] =
                        ctx->BasisValD[i18 + ctx->BasisValD.size(0) * i12];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            u_loop_ub = ctx->BasisValDD.size(1);
            for (int i20{0}; i20 < u_loop_ub; i20++) {
                int bb_loop_ub;
                bb_loop_ub = ctx->BasisValDD.size(0);
                for (int i26{0}; i26 < bb_loop_ub; i26++) {
                    r.BasisValDD[i26 + r.BasisValDD.size(0) * i20] =
                        ctx->BasisValDD[i26 + ctx->BasisValDD.size(0) * i20];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            db_loop_ub = ctx->BasisValDDD.size(1);
            for (int i28{0}; i28 < db_loop_ub; i28++) {
                int jb_loop_ub;
                jb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i34{0}; i34 < jb_loop_ub; i34++) {
                    r.BasisValDDD[i34 + r.BasisValDDD.size(0) * i28] =
                        ctx->BasisValDDD[i34 + ctx->BasisValDDD.size(0) * i28];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            lb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i36{0}; i36 < lb_loop_ub; i36++) {
                r.BasisIntegr[i36] = ctx->BasisIntegr[i36];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            ob_loop_ub = ctx->u_vec.size(1);
            for (int i39{0}; i39 < ob_loop_ub; i39++) {
                r.u_vec[i39] = ctx->u_vec[i39];
            }
            r.q_spline = ctx->q_spline;
            r.q_gcode = ctx->q_gcode;
            r.q_compress = ctx->q_compress;
            r.q_smooth = ctx->q_smooth;
            r.q_split = ctx->q_split;
            r.q_opt = ctx->q_opt;
            r.op = ctx->op;
            r.go_next = ctx->go_next;
            r.try_push_again = ctx->try_push_again;
            r.n_optimized = ctx->n_optimized;
            r.reached_end = ctx->reached_end;
            r.k0 = ctx->k0;
            r.v_0 = ctx->v_0;
            r.v_1 = ctx->v_1;
            r.at_0 = ctx->at_0;
            r.at_1 = ctx->at_1;
            r.cfg.maskTot.size[0] = 1;
            r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
            rb_loop_ub = ctx->cfg.maskTot.size[1];
            if (0 <= rb_loop_ub - 1) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[rb_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
            ub_loop_ub = ctx->cfg.maskCart.size(1);
            for (int i43{0}; i43 < ub_loop_ub; i43++) {
                r.cfg.maskCart[i43] = ctx->cfg.maskCart[i43];
            }
            r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
            xb_loop_ub = ctx->cfg.maskRot.size(1);
            for (int i46{0}; i46 < xb_loop_ub; i46++) {
                r.cfg.maskRot[i46] = ctx->cfg.maskRot[i46];
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            bc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i49{0}; i49 < bc_loop_ub; i49++) {
                r.cfg.indCart[i49] = ctx->cfg.indCart.data[i49];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            ec_loop_ub = ctx->cfg.indRot.size[0];
            for (int i52{0}; i52 < ec_loop_ub; i52++) {
                r.cfg.indRot[i52] = ctx->cfg.indRot.data[i52];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
            hc_loop_ub = ctx->cfg.kin_params.size(0);
            for (int i56{0}; i56 < hc_loop_ub; i56++) {
                r.cfg.kin_params[i56] = ctx->cfg.kin_params[i56];
            }
            r.cfg.kin_type = ctx->cfg.kin_type;
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i59{0}; i59 < 6; i59++) {
                r.cfg.vmax[i59] = ctx->cfg.vmax[i59];
                r.cfg.amax[i59] = ctx->cfg.amax[i59];
                r.cfg.jmax[i59] = ctx->cfg.jmax[i59];
            }
            r.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
            r.cfg.SplineDegree = ctx->cfg.SplineDegree;
            r.cfg.CutOff = ctx->cfg.CutOff;
            r.cfg.LSplit = ctx->cfg.LSplit;
            r.cfg.LSplitZero = ctx->cfg.LSplitZero;
            r.cfg.LThreshold = ctx->cfg.LThreshold;
            r.cfg.CuspThreshold = ctx->cfg.CuspThreshold;
            r.cfg.v_0 = ctx->cfg.v_0;
            r.cfg.at_0 = ctx->cfg.at_0;
            r.cfg.v_1 = ctx->cfg.v_1;
            r.cfg.at_1 = ctx->cfg.at_1;
            r.cfg.dt = ctx->cfg.dt;
            r.cfg.ZeroStartAccLimit = ctx->cfg.ZeroStartAccLimit;
            r.cfg.ZeroStartJerkLimit = ctx->cfg.ZeroStartJerkLimit;
            r.cfg.ZeroStartVelLimit = ctx->cfg.ZeroStartVelLimit;
            std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &r.cfg.source[0]);
            r.cfg.DebugCutZero = ctx->cfg.DebugCutZero;
            r.cfg.Compressing = ctx->cfg.Compressing;
            r.cfg.ColTolCosSmooth = ctx->cfg.ColTolCosSmooth;
            r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
            for (int e_i{0}; e_i < 5; e_i++) {
                r.cfg.GaussLegendreX[e_i] = ctx->cfg.GaussLegendreX[e_i];
                r.cfg.GaussLegendreW[e_i] = ctx->cfg.GaussLegendreW[e_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i62{0}; i62 < 9; i62++) {
                r.cfg.LogFileName[i62] = ctx->cfg.LogFileName[i62];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            kc_loop_ub = ctx->Coeff.size(1);
            for (int i65{0}; i65 < kc_loop_ub; i65++) {
                int nc_loop_ub;
                nc_loop_ub = ctx->Coeff.size(0);
                for (int i68{0}; i68 < nc_loop_ub; i68++) {
                    r.Coeff[i68 + r.Coeff.size(0) * i65] =
                        ctx->Coeff[i68 + ctx->Coeff.size(0) * i65];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            compressCurvStructs_new(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            qc_loop_ub = r.BasisVal.size(1);
            for (int i71{0}; i71 < qc_loop_ub; i71++) {
                int vc_loop_ub;
                vc_loop_ub = r.BasisVal.size(0);
                for (int i76{0}; i76 < vc_loop_ub; i76++) {
                    ctx->BasisVal[i76 + ctx->BasisVal.size(0) * i71] =
                        r.BasisVal[i76 + r.BasisVal.size(0) * i71];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            wc_loop_ub = r.BasisValD.size(1);
            for (int i77{0}; i77 < wc_loop_ub; i77++) {
                int cd_loop_ub;
                cd_loop_ub = r.BasisValD.size(0);
                for (int i82{0}; i82 < cd_loop_ub; i82++) {
                    ctx->BasisValD[i82 + ctx->BasisValD.size(0) * i77] =
                        r.BasisValD[i82 + r.BasisValD.size(0) * i77];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            dd_loop_ub = r.BasisValDD.size(1);
            for (int i83{0}; i83 < dd_loop_ub; i83++) {
                int id_loop_ub;
                id_loop_ub = r.BasisValDD.size(0);
                for (int i88{0}; i88 < id_loop_ub; i88++) {
                    ctx->BasisValDD[i88 + ctx->BasisValDD.size(0) * i83] =
                        r.BasisValDD[i88 + r.BasisValDD.size(0) * i83];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            jd_loop_ub = r.BasisValDDD.size(1);
            for (int i89{0}; i89 < jd_loop_ub; i89++) {
                int od_loop_ub;
                od_loop_ub = r.BasisValDDD.size(0);
                for (int i94{0}; i94 < od_loop_ub; i94++) {
                    ctx->BasisValDDD[i94 + ctx->BasisValDDD.size(0) * i89] =
                        r.BasisValDDD[i94 + r.BasisValDDD.size(0) * i89];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            pd_loop_ub = r.BasisIntegr.size(0);
            for (int i95{0}; i95 < pd_loop_ub; i95++) {
                ctx->BasisIntegr[i95] = r.BasisIntegr[i95];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            sd_loop_ub = r.u_vec.size(1);
            for (int i98{0}; i98 < sd_loop_ub; i98++) {
                ctx->u_vec[i98] = r.u_vec[i98];
            }
            ctx->q_spline = r.q_spline;
            ctx->q_gcode = r.q_gcode;
            ctx->q_compress = r.q_compress;
            ctx->q_smooth = r.q_smooth;
            ctx->q_split = r.q_split;
            ctx->q_opt = r.q_opt;
            ctx->go_next = r.go_next;
            ctx->try_push_again = r.try_push_again;
            ctx->n_optimized = r.n_optimized;
            ctx->reached_end = r.reached_end;
            ctx->k0 = r.k0;
            ctx->v_0 = r.v_0;
            ctx->v_1 = r.v_1;
            ctx->at_0 = r.at_0;
            ctx->at_1 = r.at_1;
            ctx->cfg.maskTot.size[0] = 1;
            ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
            vd_loop_ub = r.cfg.maskTot.size[1];
            if (0 <= vd_loop_ub - 1) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[vd_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.set_size(1, r.cfg.maskCart.size(1));
            yd_loop_ub = r.cfg.maskCart.size(1);
            for (int i101{0}; i101 < yd_loop_ub; i101++) {
                ctx->cfg.maskCart[i101] = r.cfg.maskCart[i101];
            }
            ctx->cfg.maskRot.set_size(1, r.cfg.maskRot.size(1));
            ce_loop_ub = r.cfg.maskRot.size(1);
            for (int i104{0}; i104 < ce_loop_ub; i104++) {
                ctx->cfg.maskRot[i104] = r.cfg.maskRot[i104];
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            fe_loop_ub = r.cfg.indCart.size(0);
            for (int i107{0}; i107 < fe_loop_ub; i107++) {
                ctx->cfg.indCart.data[i107] = r.cfg.indCart[i107];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            ie_loop_ub = r.cfg.indRot.size(0);
            for (int i110{0}; i110 < ie_loop_ub; i110++) {
                ctx->cfg.indRot.data[i110] = r.cfg.indRot[i110];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.kin_params.set_size(r.cfg.kin_params.size(0));
            le_loop_ub = r.cfg.kin_params.size(0);
            for (int i113{0}; i113 < le_loop_ub; i113++) {
                ctx->cfg.kin_params[i113] = r.cfg.kin_params[i113];
            }
            ctx->cfg.kin_type = r.cfg.kin_type;
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i116{0}; i116 < 6; i116++) {
                ctx->cfg.vmax[i116] = r.cfg.vmax[i116];
                ctx->cfg.amax[i116] = r.cfg.amax[i116];
                ctx->cfg.jmax[i116] = r.cfg.jmax[i116];
            }
            ctx->cfg.LeeSplineDegree = r.cfg.LeeSplineDegree;
            ctx->cfg.SplineDegree = r.cfg.SplineDegree;
            ctx->cfg.CutOff = r.cfg.CutOff;
            ctx->cfg.LSplit = r.cfg.LSplit;
            ctx->cfg.LSplitZero = r.cfg.LSplitZero;
            ctx->cfg.LThreshold = r.cfg.LThreshold;
            ctx->cfg.CuspThreshold = r.cfg.CuspThreshold;
            ctx->cfg.v_0 = r.cfg.v_0;
            ctx->cfg.at_0 = r.cfg.at_0;
            ctx->cfg.v_1 = r.cfg.v_1;
            ctx->cfg.at_1 = r.cfg.at_1;
            ctx->cfg.dt = r.cfg.dt;
            ctx->cfg.ZeroStartAccLimit = r.cfg.ZeroStartAccLimit;
            ctx->cfg.ZeroStartJerkLimit = r.cfg.ZeroStartJerkLimit;
            ctx->cfg.ZeroStartVelLimit = r.cfg.ZeroStartVelLimit;
            std::copy(&r.cfg.source[0], &r.cfg.source[1024], &ctx->cfg.source[0]);
            ctx->cfg.DebugCutZero = r.cfg.DebugCutZero;
            ctx->cfg.Compressing = r.cfg.Compressing;
            ctx->cfg.ColTolCosSmooth = r.cfg.ColTolCosSmooth;
            ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
            for (int h_i{0}; h_i < 5; h_i++) {
                ctx->cfg.GaussLegendreX[h_i] = r.cfg.GaussLegendreX[h_i];
                ctx->cfg.GaussLegendreW[h_i] = r.cfg.GaussLegendreW[h_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i119{0}; i119 < 9; i119++) {
                ctx->cfg.LogFileName[i119] = r.cfg.LogFileName[i119];
            }
            ctx->errcode = r.errcode;
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            oe_loop_ub = r.Coeff.size(1);
            for (int i122{0}; i122 < oe_loop_ub; i122++) {
                int re_loop_ub;
                re_loop_ub = r.Coeff.size(0);
                for (int i125{0}; i125 < re_loop_ub; i125++) {
                    ctx->Coeff[i125 + ctx->Coeff.size(0) * i122] =
                        r.Coeff[i125 + r.Coeff.size(0) * i122];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        //          if( ctx.q_compress.size > 1 )
        //              error( "should be only compressing");
        //          end
        // 'FeedoptPlan:77' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:78' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int cb_loop_ub;
        int d_loop_ub;
        int kb_loop_ub;
        int l_loop_ub;
        int t_loop_ub;
        // 'FeedoptPlan:80' case Fopt.Smooth
        // 'FeedoptPlan:81' ctx = smoothCurvStructs(ctx);
        r.q_spline = ctx->q_spline;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        d_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= d_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[d_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        l_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i11{0}; i11 < l_loop_ub; i11++) {
            r.cfg.maskCart[i11] = ctx->cfg.maskCart[i11];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        t_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i19{0}; i19 < t_loop_ub; i19++) {
            r.cfg.maskRot[i19] = ctx->cfg.maskRot[i19];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        cb_loop_ub = ctx->cfg.indCart.size[0];
        for (int i27{0}; i27 < cb_loop_ub; i27++) {
            r.cfg.indCart[i27] = ctx->cfg.indCart.data[i27];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        kb_loop_ub = ctx->cfg.indRot.size[0];
        for (int i35{0}; i35 < kb_loop_ub; i35++) {
            r.cfg.indRot[i35] = ctx->cfg.indRot.data[i35];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.CutOff = ctx->cfg.CutOff;
        r.cfg.ColTolCosSmooth = ctx->cfg.ColTolCosSmooth;
        for (int b_i{0}; b_i < 5; b_i++) {
            r.cfg.GaussLegendreX[b_i] = ctx->cfg.GaussLegendreX[b_i];
            r.cfg.GaussLegendreW[b_i] = ctx->cfg.GaussLegendreW[b_i];
        }
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        //  Optimal transitions calculation between segments whith G2 continuity
        // 'smoothCurvStructs:5' if ctx.q_compress.isempty()
        if (!ctx->q_compress.isempty()) {
            uint64m_T r14;
            unsigned int Ncrv;
            // 'smoothCurvStructs:7' Ncrv = ctx.q_compress.size;
            Ncrv = ctx->q_compress.size();
            // 'smoothCurvStructs:9' DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r13.chunks[0U]);
            r14 = r8;
            MultiWordAnd((unsigned int *)&r13.chunks[0U], (unsigned int *)&r8.chunks[0U],
                         (unsigned int *)&r15.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r15.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf( 1, varargin{:} );
                printf("Smoothing...\n");
                fflush(stdout);
            }
            // 'smoothCurvStructs:10' DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r20.chunks[0U]);
            MultiWordAnd((unsigned int *)&r20.chunks[0U], (unsigned int *)&r17.chunks[0U],
                         (unsigned int *)&r14.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r14.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf( 1, varargin{:} );
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
                    r.programmed_stop++;
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
                    calcTransition(&r.q_spline, r.cfg.maskTot.data, r.cfg.maskTot.size,
                                   r.cfg.maskCart, r.cfg.maskRot, r.cfg.indCart, r.cfg.indRot,
                                   r.cfg.NumberAxis, r.cfg.NCart, r.cfg.NRot, r.cfg.CutOff,
                                   r.cfg.ColTolCosSmooth, r.cfg.GaussLegendreX,
                                   r.cfg.GaussLegendreW, &curv, &nextCurv, &curvC1, &curvT, &curvC2,
                                   &c_status);
                    // 'smoothCurvStructs:26' if      ( status == TransitionResult.Ok )
                    if (c_status == TransitionResult_Ok) {
                        // 'smoothCurvStructs:27' ctx.q_smooth.push( curvC1 );
                        ctx->q_smooth.push(&curvC1);
                        // 'smoothCurvStructs:28' ctx.q_smooth.push( curvT );
                        ctx->q_smooth.push(&curvT);
                        // 'smoothCurvStructs:29' curv = curvC2;
                        curv = curvC2;
                    } else if (c_status == TransitionResult_Collinear) {
                        // 'smoothCurvStructs:30' elseif  ( status == TransitionResult.Collinear )
                        // 'smoothCurvStructs:31' ctx.q_smooth.push( curv );
                        ctx->q_smooth.push(&curv);
                        // 'smoothCurvStructs:32' curv = nextCurv;
                        curv = nextCurv;
                    } else {
                        // 'smoothCurvStructs:33' else
                        //  If the transition fails, force a zero-stop
                        // 'smoothCurvStructs:34' ctx.forced_stop = ctx.forced_stop + 1;
                        r.forced_stop++;
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
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        // 'FeedoptPlan:82' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:83' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Split: {
        int ad_loop_ub;
        int ae_loop_ub;
        int cc_loop_ub;
        int de_loop_ub;
        int fc_loop_ub;
        int gb_loop_ub;
        int gd_loop_ub;
        int ge_loop_ub;
        int h_loop_ub;
        int ic_loop_ub;
        int je_loop_ub;
        int loop_ub;
        int mb_loop_ub;
        int md_loop_ub;
        int me_loop_ub;
        int oc_loop_ub;
        int p_loop_ub;
        int pb_loop_ub;
        int qd_loop_ub;
        int sb_loop_ub;
        int tc_loop_ub;
        int td_loop_ub;
        int vb_loop_ub;
        int wd_loop_ub;
        int x_loop_ub;
        int yb_loop_ub;
        // 'FeedoptPlan:85' case Fopt.Split
        // 'FeedoptPlan:86' ctx = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        loop_ub = ctx->BasisVal.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            int f_loop_ub;
            f_loop_ub = ctx->BasisVal.size(0);
            for (int i5{0}; i5 < f_loop_ub; i5++) {
                r.BasisVal[i5 + r.BasisVal.size(0) * i1] =
                    ctx->BasisVal[i5 + ctx->BasisVal.size(0) * i1];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        h_loop_ub = ctx->BasisValD.size(1);
        for (int i7{0}; i7 < h_loop_ub; i7++) {
            int n_loop_ub;
            n_loop_ub = ctx->BasisValD.size(0);
            for (int i13{0}; i13 < n_loop_ub; i13++) {
                r.BasisValD[i13 + r.BasisValD.size(0) * i7] =
                    ctx->BasisValD[i13 + ctx->BasisValD.size(0) * i7];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        p_loop_ub = ctx->BasisValDD.size(1);
        for (int i15{0}; i15 < p_loop_ub; i15++) {
            int v_loop_ub;
            v_loop_ub = ctx->BasisValDD.size(0);
            for (int i21{0}; i21 < v_loop_ub; i21++) {
                r.BasisValDD[i21 + r.BasisValDD.size(0) * i15] =
                    ctx->BasisValDD[i21 + ctx->BasisValDD.size(0) * i15];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        x_loop_ub = ctx->BasisValDDD.size(1);
        for (int i23{0}; i23 < x_loop_ub; i23++) {
            int eb_loop_ub;
            eb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i29{0}; i29 < eb_loop_ub; i29++) {
                r.BasisValDDD[i29 + r.BasisValDDD.size(0) * i23] =
                    ctx->BasisValDDD[i29 + ctx->BasisValDDD.size(0) * i23];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        gb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i31{0}; i31 < gb_loop_ub; i31++) {
            r.BasisIntegr[i31] = ctx->BasisIntegr[i31];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        mb_loop_ub = ctx->u_vec.size(1);
        for (int i37{0}; i37 < mb_loop_ub; i37++) {
            r.u_vec[i37] = ctx->u_vec[i37];
        }
        r.q_spline = ctx->q_spline;
        r.q_gcode = ctx->q_gcode;
        r.q_compress = ctx->q_compress;
        r.q_smooth = ctx->q_smooth;
        r.q_split = ctx->q_split;
        r.q_opt = ctx->q_opt;
        r.op = ctx->op;
        r.go_next = ctx->go_next;
        r.try_push_again = ctx->try_push_again;
        r.n_optimized = ctx->n_optimized;
        r.reached_end = ctx->reached_end;
        r.k0 = ctx->k0;
        r.v_0 = ctx->v_0;
        r.v_1 = ctx->v_1;
        r.at_0 = ctx->at_0;
        r.at_1 = ctx->at_1;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        pb_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= pb_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[pb_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        sb_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i40{0}; i40 < sb_loop_ub; i40++) {
            r.cfg.maskCart[i40] = ctx->cfg.maskCart[i40];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        vb_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i44{0}; i44 < vb_loop_ub; i44++) {
            r.cfg.maskRot[i44] = ctx->cfg.maskRot[i44];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        yb_loop_ub = ctx->cfg.indCart.size[0];
        for (int i47{0}; i47 < yb_loop_ub; i47++) {
            r.cfg.indCart[i47] = ctx->cfg.indCart.data[i47];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        cc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i50{0}; i50 < cc_loop_ub; i50++) {
            r.cfg.indRot[i50] = ctx->cfg.indRot.data[i50];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
        fc_loop_ub = ctx->cfg.kin_params.size(0);
        for (int i54{0}; i54 < fc_loop_ub; i54++) {
            r.cfg.kin_params[i54] = ctx->cfg.kin_params[i54];
        }
        r.cfg.kin_type = ctx->cfg.kin_type;
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i57{0}; i57 < 6; i57++) {
            r.cfg.vmax[i57] = ctx->cfg.vmax[i57];
            r.cfg.amax[i57] = ctx->cfg.amax[i57];
            r.cfg.jmax[i57] = ctx->cfg.jmax[i57];
        }
        r.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
        r.cfg.SplineDegree = ctx->cfg.SplineDegree;
        r.cfg.CutOff = ctx->cfg.CutOff;
        r.cfg.LSplit = ctx->cfg.LSplit;
        r.cfg.LSplitZero = ctx->cfg.LSplitZero;
        r.cfg.LThreshold = ctx->cfg.LThreshold;
        r.cfg.CuspThreshold = ctx->cfg.CuspThreshold;
        r.cfg.v_0 = ctx->cfg.v_0;
        r.cfg.at_0 = ctx->cfg.at_0;
        r.cfg.v_1 = ctx->cfg.v_1;
        r.cfg.at_1 = ctx->cfg.at_1;
        r.cfg.dt = ctx->cfg.dt;
        r.cfg.ZeroStartAccLimit = ctx->cfg.ZeroStartAccLimit;
        r.cfg.ZeroStartJerkLimit = ctx->cfg.ZeroStartJerkLimit;
        r.cfg.ZeroStartVelLimit = ctx->cfg.ZeroStartVelLimit;
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &r.cfg.source[0]);
        r.cfg.DebugCutZero = ctx->cfg.DebugCutZero;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.ColTolCosSmooth = ctx->cfg.ColTolCosSmooth;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int c_i{0}; c_i < 5; c_i++) {
            r.cfg.GaussLegendreX[c_i] = ctx->cfg.GaussLegendreX[c_i];
            r.cfg.GaussLegendreW[c_i] = ctx->cfg.GaussLegendreW[c_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i60{0}; i60 < 9; i60++) {
            r.cfg.LogFileName[i60] = ctx->cfg.LogFileName[i60];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        ic_loop_ub = ctx->Coeff.size(1);
        for (int i63{0}; i63 < ic_loop_ub; i63++) {
            int lc_loop_ub;
            lc_loop_ub = ctx->Coeff.size(0);
            for (int i66{0}; i66 < lc_loop_ub; i66++) {
                r.Coeff[i66 + r.Coeff.size(0) * i63] = ctx->Coeff[i66 + ctx->Coeff.size(0) * i63];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        splitQueue(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        oc_loop_ub = r.BasisVal.size(1);
        for (int i69{0}; i69 < oc_loop_ub; i69++) {
            int rc_loop_ub;
            rc_loop_ub = r.BasisVal.size(0);
            for (int i72{0}; i72 < rc_loop_ub; i72++) {
                ctx->BasisVal[i72 + ctx->BasisVal.size(0) * i69] =
                    r.BasisVal[i72 + r.BasisVal.size(0) * i69];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        tc_loop_ub = r.BasisValD.size(1);
        for (int i74{0}; i74 < tc_loop_ub; i74++) {
            int xc_loop_ub;
            xc_loop_ub = r.BasisValD.size(0);
            for (int i78{0}; i78 < xc_loop_ub; i78++) {
                ctx->BasisValD[i78 + ctx->BasisValD.size(0) * i74] =
                    r.BasisValD[i78 + r.BasisValD.size(0) * i74];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        ad_loop_ub = r.BasisValDD.size(1);
        for (int i80{0}; i80 < ad_loop_ub; i80++) {
            int ed_loop_ub;
            ed_loop_ub = r.BasisValDD.size(0);
            for (int i84{0}; i84 < ed_loop_ub; i84++) {
                ctx->BasisValDD[i84 + ctx->BasisValDD.size(0) * i80] =
                    r.BasisValDD[i84 + r.BasisValDD.size(0) * i80];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        gd_loop_ub = r.BasisValDDD.size(1);
        for (int i86{0}; i86 < gd_loop_ub; i86++) {
            int kd_loop_ub;
            kd_loop_ub = r.BasisValDDD.size(0);
            for (int i90{0}; i90 < kd_loop_ub; i90++) {
                ctx->BasisValDDD[i90 + ctx->BasisValDDD.size(0) * i86] =
                    r.BasisValDDD[i90 + r.BasisValDDD.size(0) * i86];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        md_loop_ub = r.BasisIntegr.size(0);
        for (int i92{0}; i92 < md_loop_ub; i92++) {
            ctx->BasisIntegr[i92] = r.BasisIntegr[i92];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        qd_loop_ub = r.u_vec.size(1);
        for (int i96{0}; i96 < qd_loop_ub; i96++) {
            ctx->u_vec[i96] = r.u_vec[i96];
        }
        ctx->q_spline = r.q_spline;
        ctx->q_gcode = r.q_gcode;
        ctx->q_compress = r.q_compress;
        ctx->q_smooth = r.q_smooth;
        ctx->q_split = r.q_split;
        ctx->q_opt = r.q_opt;
        ctx->go_next = r.go_next;
        ctx->try_push_again = r.try_push_again;
        ctx->n_optimized = r.n_optimized;
        ctx->reached_end = r.reached_end;
        ctx->k0 = r.k0;
        ctx->v_0 = r.v_0;
        ctx->v_1 = r.v_1;
        ctx->at_0 = r.at_0;
        ctx->at_1 = r.at_1;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
        td_loop_ub = r.cfg.maskTot.size[1];
        if (0 <= td_loop_ub - 1) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[td_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.set_size(1, r.cfg.maskCart.size(1));
        wd_loop_ub = r.cfg.maskCart.size(1);
        for (int i99{0}; i99 < wd_loop_ub; i99++) {
            ctx->cfg.maskCart[i99] = r.cfg.maskCart[i99];
        }
        ctx->cfg.maskRot.set_size(1, r.cfg.maskRot.size(1));
        ae_loop_ub = r.cfg.maskRot.size(1);
        for (int i102{0}; i102 < ae_loop_ub; i102++) {
            ctx->cfg.maskRot[i102] = r.cfg.maskRot[i102];
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        de_loop_ub = r.cfg.indCart.size(0);
        for (int i105{0}; i105 < de_loop_ub; i105++) {
            ctx->cfg.indCart.data[i105] = r.cfg.indCart[i105];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        ge_loop_ub = r.cfg.indRot.size(0);
        for (int i108{0}; i108 < ge_loop_ub; i108++) {
            ctx->cfg.indRot.data[i108] = r.cfg.indRot[i108];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.kin_params.set_size(r.cfg.kin_params.size(0));
        je_loop_ub = r.cfg.kin_params.size(0);
        for (int i111{0}; i111 < je_loop_ub; i111++) {
            ctx->cfg.kin_params[i111] = r.cfg.kin_params[i111];
        }
        ctx->cfg.kin_type = r.cfg.kin_type;
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i114{0}; i114 < 6; i114++) {
            ctx->cfg.vmax[i114] = r.cfg.vmax[i114];
            ctx->cfg.amax[i114] = r.cfg.amax[i114];
            ctx->cfg.jmax[i114] = r.cfg.jmax[i114];
        }
        ctx->cfg.LeeSplineDegree = r.cfg.LeeSplineDegree;
        ctx->cfg.SplineDegree = r.cfg.SplineDegree;
        ctx->cfg.CutOff = r.cfg.CutOff;
        ctx->cfg.LSplit = r.cfg.LSplit;
        ctx->cfg.LSplitZero = r.cfg.LSplitZero;
        ctx->cfg.LThreshold = r.cfg.LThreshold;
        ctx->cfg.CuspThreshold = r.cfg.CuspThreshold;
        ctx->cfg.v_0 = r.cfg.v_0;
        ctx->cfg.at_0 = r.cfg.at_0;
        ctx->cfg.v_1 = r.cfg.v_1;
        ctx->cfg.at_1 = r.cfg.at_1;
        ctx->cfg.dt = r.cfg.dt;
        ctx->cfg.ZeroStartAccLimit = r.cfg.ZeroStartAccLimit;
        ctx->cfg.ZeroStartJerkLimit = r.cfg.ZeroStartJerkLimit;
        ctx->cfg.ZeroStartVelLimit = r.cfg.ZeroStartVelLimit;
        std::copy(&r.cfg.source[0], &r.cfg.source[1024], &ctx->cfg.source[0]);
        ctx->cfg.DebugCutZero = r.cfg.DebugCutZero;
        ctx->cfg.Compressing = r.cfg.Compressing;
        ctx->cfg.ColTolCosSmooth = r.cfg.ColTolCosSmooth;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int f_i{0}; f_i < 5; f_i++) {
            ctx->cfg.GaussLegendreX[f_i] = r.cfg.GaussLegendreX[f_i];
            ctx->cfg.GaussLegendreW[f_i] = r.cfg.GaussLegendreW[f_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i117{0}; i117 < 9; i117++) {
            ctx->cfg.LogFileName[i117] = r.cfg.LogFileName[i117];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        me_loop_ub = r.Coeff.size(1);
        for (int i120{0}; i120 < me_loop_ub; i120++) {
            int pe_loop_ub;
            pe_loop_ub = r.Coeff.size(0);
            for (int i123{0}; i123 < pe_loop_ub; i123++) {
                ctx->Coeff[i123 + ctx->Coeff.size(0) * i120] =
                    r.Coeff[i123 + r.Coeff.size(0) * i120];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:87' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:88' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
    } break;
    case Fopt_Opt: {
        int ac_loop_ub;
        int b_loop_ub;
        int bd_loop_ub;
        int be_loop_ub;
        int dc_loop_ub;
        int ee_loop_ub;
        int gc_loop_ub;
        int hb_loop_ub;
        int hd_loop_ub;
        int he_loop_ub;
        int i_loop_ub;
        int jc_loop_ub;
        int ke_loop_ub;
        int nb_loop_ub;
        int nd_loop_ub;
        int ne_loop_ub;
        int pc_loop_ub;
        int q_loop_ub;
        int qb_loop_ub;
        int rd_loop_ub;
        int tb_loop_ub;
        int uc_loop_ub;
        int ud_loop_ub;
        int wb_loop_ub;
        int xd_loop_ub;
        int y_loop_ub;
        // 'FeedoptPlan:90' case Fopt.Opt
        // 'FeedoptPlan:91' [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
        b_ctx.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        b_loop_ub = ctx->BasisVal.size(1);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            int g_loop_ub;
            g_loop_ub = ctx->BasisVal.size(0);
            for (int i6{0}; i6 < g_loop_ub; i6++) {
                b_ctx.BasisVal[i6 + b_ctx.BasisVal.size(0) * i2] =
                    ctx->BasisVal[i6 + ctx->BasisVal.size(0) * i2];
            }
        }
        b_ctx.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        i_loop_ub = ctx->BasisValD.size(1);
        for (int i8{0}; i8 < i_loop_ub; i8++) {
            int o_loop_ub;
            o_loop_ub = ctx->BasisValD.size(0);
            for (int i14{0}; i14 < o_loop_ub; i14++) {
                b_ctx.BasisValD[i14 + b_ctx.BasisValD.size(0) * i8] =
                    ctx->BasisValD[i14 + ctx->BasisValD.size(0) * i8];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        q_loop_ub = ctx->BasisValDD.size(1);
        for (int i16{0}; i16 < q_loop_ub; i16++) {
            int w_loop_ub;
            w_loop_ub = ctx->BasisValDD.size(0);
            for (int i22{0}; i22 < w_loop_ub; i22++) {
                b_ctx.BasisValDD[i22 + b_ctx.BasisValDD.size(0) * i16] =
                    ctx->BasisValDD[i22 + ctx->BasisValDD.size(0) * i16];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        y_loop_ub = ctx->BasisValDDD.size(1);
        for (int i24{0}; i24 < y_loop_ub; i24++) {
            int fb_loop_ub;
            fb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i30{0}; i30 < fb_loop_ub; i30++) {
                b_ctx.BasisValDDD[i30 + b_ctx.BasisValDDD.size(0) * i24] =
                    ctx->BasisValDDD[i30 + ctx->BasisValDDD.size(0) * i24];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        hb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i32{0}; i32 < hb_loop_ub; i32++) {
            b_ctx.BasisIntegr[i32] = ctx->BasisIntegr[i32];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        nb_loop_ub = ctx->u_vec.size(1);
        for (int i38{0}; i38 < nb_loop_ub; i38++) {
            b_ctx.u_vec[i38] = ctx->u_vec[i38];
        }
        b_ctx.q_spline = ctx->q_spline;
        b_ctx.q_gcode = ctx->q_gcode;
        b_ctx.q_compress = ctx->q_compress;
        b_ctx.q_smooth = ctx->q_smooth;
        b_ctx.q_split = ctx->q_split;
        b_ctx.q_opt = ctx->q_opt;
        b_ctx.op = ctx->op;
        b_ctx.go_next = ctx->go_next;
        b_ctx.try_push_again = ctx->try_push_again;
        b_ctx.n_optimized = ctx->n_optimized;
        b_ctx.reached_end = ctx->reached_end;
        b_ctx.k0 = ctx->k0;
        b_ctx.v_0 = ctx->v_0;
        b_ctx.v_1 = ctx->v_1;
        b_ctx.at_0 = ctx->at_0;
        b_ctx.at_1 = ctx->at_1;
        b_ctx.cfg.maskTot.size[0] = 1;
        b_ctx.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        qb_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= qb_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[qb_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        tb_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i41{0}; i41 < tb_loop_ub; i41++) {
            b_ctx.cfg.maskCart[i41] = ctx->cfg.maskCart[i41];
        }
        b_ctx.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        wb_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i45{0}; i45 < wb_loop_ub; i45++) {
            b_ctx.cfg.maskRot[i45] = ctx->cfg.maskRot[i45];
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ac_loop_ub = ctx->cfg.indCart.size[0];
        for (int i48{0}; i48 < ac_loop_ub; i48++) {
            b_ctx.cfg.indCart[i48] = ctx->cfg.indCart.data[i48];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        dc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i51{0}; i51 < dc_loop_ub; i51++) {
            b_ctx.cfg.indRot[i51] = ctx->cfg.indRot.data[i51];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
        gc_loop_ub = ctx->cfg.kin_params.size(0);
        for (int i55{0}; i55 < gc_loop_ub; i55++) {
            b_ctx.cfg.kin_params[i55] = ctx->cfg.kin_params[i55];
        }
        b_ctx.cfg.kin_type = ctx->cfg.kin_type;
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        b_ctx.cfg.fmax = ctx->cfg.fmax;
        b_ctx.cfg.smax = ctx->cfg.smax;
        for (int i58{0}; i58 < 6; i58++) {
            b_ctx.cfg.vmax[i58] = ctx->cfg.vmax[i58];
            b_ctx.cfg.amax[i58] = ctx->cfg.amax[i58];
            b_ctx.cfg.jmax[i58] = ctx->cfg.jmax[i58];
        }
        b_ctx.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
        b_ctx.cfg.SplineDegree = ctx->cfg.SplineDegree;
        b_ctx.cfg.CutOff = ctx->cfg.CutOff;
        b_ctx.cfg.LSplit = ctx->cfg.LSplit;
        b_ctx.cfg.LSplitZero = ctx->cfg.LSplitZero;
        b_ctx.cfg.LThreshold = ctx->cfg.LThreshold;
        b_ctx.cfg.CuspThreshold = ctx->cfg.CuspThreshold;
        b_ctx.cfg.v_0 = ctx->cfg.v_0;
        b_ctx.cfg.at_0 = ctx->cfg.at_0;
        b_ctx.cfg.v_1 = ctx->cfg.v_1;
        b_ctx.cfg.at_1 = ctx->cfg.at_1;
        b_ctx.cfg.dt = ctx->cfg.dt;
        b_ctx.cfg.ZeroStartAccLimit = ctx->cfg.ZeroStartAccLimit;
        b_ctx.cfg.ZeroStartJerkLimit = ctx->cfg.ZeroStartJerkLimit;
        b_ctx.cfg.ZeroStartVelLimit = ctx->cfg.ZeroStartVelLimit;
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_ctx.cfg.source[0]);
        b_ctx.cfg.DebugCutZero = ctx->cfg.DebugCutZero;
        b_ctx.cfg.Compressing = ctx->cfg.Compressing;
        b_ctx.cfg.ColTolCosSmooth = ctx->cfg.ColTolCosSmooth;
        b_ctx.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int d_i{0}; d_i < 5; d_i++) {
            b_ctx.cfg.GaussLegendreX[d_i] = ctx->cfg.GaussLegendreX[d_i];
            b_ctx.cfg.GaussLegendreW[d_i] = ctx->cfg.GaussLegendreW[d_i];
        }
        b_ctx.cfg.opt = ctx->cfg.opt;
        for (int i61{0}; i61 < 9; i61++) {
            b_ctx.cfg.LogFileName[i61] = ctx->cfg.LogFileName[i61];
        }
        b_ctx.errcode = ctx->errcode;
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        jc_loop_ub = ctx->Coeff.size(1);
        for (int i64{0}; i64 < jc_loop_ub; i64++) {
            int mc_loop_ub;
            mc_loop_ub = ctx->Coeff.size(0);
            for (int i67{0}; i67 < mc_loop_ub; i67++) {
                b_ctx.Coeff[i67 + b_ctx.Coeff.size(0) * i64] =
                    ctx->Coeff[i67 + ctx->Coeff.size(0) * i64];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        feedratePlanning(&b_ctx, &c_optimized, &opt_curv, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        pc_loop_ub = b_ctx.BasisVal.size(1);
        for (int i70{0}; i70 < pc_loop_ub; i70++) {
            int sc_loop_ub;
            sc_loop_ub = b_ctx.BasisVal.size(0);
            for (int i73{0}; i73 < sc_loop_ub; i73++) {
                ctx->BasisVal[i73 + ctx->BasisVal.size(0) * i70] =
                    b_ctx.BasisVal[i73 + b_ctx.BasisVal.size(0) * i70];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        uc_loop_ub = b_ctx.BasisValD.size(1);
        for (int i75{0}; i75 < uc_loop_ub; i75++) {
            int yc_loop_ub;
            yc_loop_ub = b_ctx.BasisValD.size(0);
            for (int i79{0}; i79 < yc_loop_ub; i79++) {
                ctx->BasisValD[i79 + ctx->BasisValD.size(0) * i75] =
                    b_ctx.BasisValD[i79 + b_ctx.BasisValD.size(0) * i75];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        bd_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i81{0}; i81 < bd_loop_ub; i81++) {
            int fd_loop_ub;
            fd_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i85{0}; i85 < fd_loop_ub; i85++) {
                ctx->BasisValDD[i85 + ctx->BasisValDD.size(0) * i81] =
                    b_ctx.BasisValDD[i85 + b_ctx.BasisValDD.size(0) * i81];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        hd_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i87{0}; i87 < hd_loop_ub; i87++) {
            int ld_loop_ub;
            ld_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i91{0}; i91 < ld_loop_ub; i91++) {
                ctx->BasisValDDD[i91 + ctx->BasisValDDD.size(0) * i87] =
                    b_ctx.BasisValDDD[i91 + b_ctx.BasisValDDD.size(0) * i87];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        nd_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i93{0}; i93 < nd_loop_ub; i93++) {
            ctx->BasisIntegr[i93] = b_ctx.BasisIntegr[i93];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        rd_loop_ub = b_ctx.u_vec.size(1);
        for (int i97{0}; i97 < rd_loop_ub; i97++) {
            ctx->u_vec[i97] = b_ctx.u_vec[i97];
        }
        ctx->q_spline = b_ctx.q_spline;
        ctx->q_gcode = b_ctx.q_gcode;
        ctx->q_compress = b_ctx.q_compress;
        ctx->q_smooth = b_ctx.q_smooth;
        ctx->q_split = b_ctx.q_split;
        ctx->q_opt = b_ctx.q_opt;
        ctx->op = b_ctx.op;
        ctx->go_next = b_ctx.go_next;
        ctx->try_push_again = b_ctx.try_push_again;
        ctx->n_optimized = b_ctx.n_optimized;
        ctx->reached_end = b_ctx.reached_end;
        ctx->k0 = b_ctx.k0;
        ctx->v_0 = b_ctx.v_0;
        ctx->v_1 = b_ctx.v_1;
        ctx->at_0 = b_ctx.at_0;
        ctx->at_1 = b_ctx.at_1;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = b_ctx.cfg.maskTot.size[1];
        ud_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (0 <= ud_loop_ub - 1) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[ud_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.set_size(1, b_ctx.cfg.maskCart.size(1));
        xd_loop_ub = b_ctx.cfg.maskCart.size(1);
        for (int i100{0}; i100 < xd_loop_ub; i100++) {
            ctx->cfg.maskCart[i100] = b_ctx.cfg.maskCart[i100];
        }
        ctx->cfg.maskRot.set_size(1, b_ctx.cfg.maskRot.size(1));
        be_loop_ub = b_ctx.cfg.maskRot.size(1);
        for (int i103{0}; i103 < be_loop_ub; i103++) {
            ctx->cfg.maskRot[i103] = b_ctx.cfg.maskRot[i103];
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        ee_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i106{0}; i106 < ee_loop_ub; i106++) {
            ctx->cfg.indCart.data[i106] = b_ctx.cfg.indCart[i106];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        he_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i109{0}; i109 < he_loop_ub; i109++) {
            ctx->cfg.indRot.data[i109] = b_ctx.cfg.indRot[i109];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.kin_params.set_size(b_ctx.cfg.kin_params.size(0));
        ke_loop_ub = b_ctx.cfg.kin_params.size(0);
        for (int i112{0}; i112 < ke_loop_ub; i112++) {
            ctx->cfg.kin_params[i112] = b_ctx.cfg.kin_params[i112];
        }
        ctx->cfg.kin_type = b_ctx.cfg.kin_type;
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        ctx->cfg.fmax = b_ctx.cfg.fmax;
        ctx->cfg.smax = b_ctx.cfg.smax;
        for (int i115{0}; i115 < 6; i115++) {
            ctx->cfg.vmax[i115] = b_ctx.cfg.vmax[i115];
            ctx->cfg.amax[i115] = b_ctx.cfg.amax[i115];
            ctx->cfg.jmax[i115] = b_ctx.cfg.jmax[i115];
        }
        ctx->cfg.LeeSplineDegree = b_ctx.cfg.LeeSplineDegree;
        ctx->cfg.SplineDegree = b_ctx.cfg.SplineDegree;
        ctx->cfg.CutOff = b_ctx.cfg.CutOff;
        ctx->cfg.LSplit = b_ctx.cfg.LSplit;
        ctx->cfg.LSplitZero = b_ctx.cfg.LSplitZero;
        ctx->cfg.LThreshold = b_ctx.cfg.LThreshold;
        ctx->cfg.CuspThreshold = b_ctx.cfg.CuspThreshold;
        ctx->cfg.v_0 = b_ctx.cfg.v_0;
        ctx->cfg.at_0 = b_ctx.cfg.at_0;
        ctx->cfg.v_1 = b_ctx.cfg.v_1;
        ctx->cfg.at_1 = b_ctx.cfg.at_1;
        ctx->cfg.dt = b_ctx.cfg.dt;
        ctx->cfg.ZeroStartAccLimit = b_ctx.cfg.ZeroStartAccLimit;
        ctx->cfg.ZeroStartJerkLimit = b_ctx.cfg.ZeroStartJerkLimit;
        ctx->cfg.ZeroStartVelLimit = b_ctx.cfg.ZeroStartVelLimit;
        std::copy(&b_ctx.cfg.source[0], &b_ctx.cfg.source[1024], &ctx->cfg.source[0]);
        ctx->cfg.DebugCutZero = b_ctx.cfg.DebugCutZero;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.ColTolCosSmooth = b_ctx.cfg.ColTolCosSmooth;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int g_i{0}; g_i < 5; g_i++) {
            ctx->cfg.GaussLegendreX[g_i] = b_ctx.cfg.GaussLegendreX[g_i];
            ctx->cfg.GaussLegendreW[g_i] = b_ctx.cfg.GaussLegendreW[g_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i118{0}; i118 < 9; i118++) {
            ctx->cfg.LogFileName[i118] = b_ctx.cfg.LogFileName[i118];
        }
        ctx->errcode = b_ctx.errcode;
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        ne_loop_ub = b_ctx.Coeff.size(1);
        for (int i121{0}; i121 < ne_loop_ub; i121++) {
            int qe_loop_ub;
            qe_loop_ub = b_ctx.Coeff.size(0);
            for (int i124{0}; i124 < qe_loop_ub; i124++) {
                ctx->Coeff[i124 + ctx->Coeff.size(0) * i121] =
                    b_ctx.Coeff[i124 + b_ctx.Coeff.size(0) * i121];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        b_optimized = c_optimized;
        // 'FeedoptPlan:92' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:93' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:94' ctx.q_opt.push( opt_curv );
            b_ctx.q_opt.push(&opt_curv);
        }
        // 'FeedoptPlan:97' if( quit )
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:99' case Fopt.Finished
        // 'FeedoptPlan:100' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:102' otherwise
        // 'FeedoptPlan:103' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r1.chunks[0U]);
        MultiWordAnd((unsigned int *)&r1.chunks[0U], (unsigned int *)&r2.chunks[0U],
                     (unsigned int *)&r3.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r3.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("FEEDOPT: WRONG STATE\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:104' ctx.op = Fopt.Finished;
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
