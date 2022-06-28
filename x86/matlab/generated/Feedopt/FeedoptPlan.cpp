//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "FeedoptPlan.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
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
#include "smoothCurvStructs.h"
#include "splitQueue.h"
#include "coder_array.h"
#include "cpp_interp.hpp"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <emmintrin.h>
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
    CurvStruct last;
    CurvStruct opt_curv;
    CurvStruct opt_struct_tmp;
    CurvStruct r1;
    b_FeedoptContext b_ctx;
    b_FeedoptContext r;
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
        int status;
        // 'FeedoptPlan:16' case Fopt.GCode
        // 'FeedoptPlan:17' status = int32( ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source ) );
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:7' status = int32(0);
        // 'ReadGCode:8' CurvStruct = constrCurvStructType;
        // 'ReadGCode:10' if ( coder.target('mex') || coder.target('rtw') )
        // 'ReadGCode:11' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
        // 'ReadGCode:13' pathRs274Src = '$(START_DIR)/../../rs274ngc/src';
        //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
        // 'ReadGCode:15' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
        // 'ReadGCode:16' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp',
        // '$(START_DIR)/../common/src'); 'ReadGCode:17'
        // coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src); 'ReadGCode:18'
        // coder.updateBuildInfo('addSourceFiles','interp_arc.cc', pathRs274Src); 'ReadGCode:19'
        // coder.updateBuildInfo('addSourceFiles','interp_array.cc', pathRs274Src); 'ReadGCode:20'
        // coder.updateBuildInfo('addSourceFiles','interp_base.cc', pathRs274Src); 'ReadGCode:21'
        // coder.updateBuildInfo('addSourceFiles','interp_check.cc', pathRs274Src); 'ReadGCode:22'
        // coder.updateBuildInfo('addSourceFiles','interp_convert.cc', pathRs274Src); 'ReadGCode:23'
        // coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', pathRs274Src); 'ReadGCode:24'
        // coder.updateBuildInfo('addSourceFiles','interp_execute.cc', pathRs274Src); 'ReadGCode:25'
        // coder.updateBuildInfo('addSourceFiles','interp_find.cc', pathRs274Src); 'ReadGCode:26'
        // coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
        // 'ReadGCode:27' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
        // 'ReadGCode:28' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
        // pathRs274Src); 'ReadGCode:29' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
        // pathRs274Src); 'ReadGCode:30' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
        // pathRs274Src); 'ReadGCode:31' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
        // pathRs274Src); 'ReadGCode:32' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
        // pathRs274Src); 'ReadGCode:33' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
        // pathRs274Src); 'ReadGCode:34' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
        // pathRs274Src); 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','ocn.cc',
        // pathRs274Src); 'ReadGCode:36' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc',
        // pathRs274Src); 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','inifile.cc',
        // pathRs274Src); 'ReadGCode:38' coder.updateBuildInfo('addLinkFlags', '-ldl');
        //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
        // 'ReadGCode:40' coder.cinclude('cpp_interp.hpp');
        // 'ReadGCode:42' switch cmd
        // 'ReadGCode:43' case ReadGCodeCmd.Load
        // 'ReadGCode:44' status = coder.ceval( 'cpp_interp_init', [filename 0] );
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = cpp_interp_init(&b_cv[0]);
        // 'FeedoptPlan:18' DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        //
        // 'FeedoptPlan:20' while status
        while (status != 0) {
            int b_status;
            int is_loaded;
            // 'FeedoptPlan:21' [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, '' );
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:7' status = int32(0);
            // 'ReadGCode:8' CurvStruct = constrCurvStructType;
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
            // 'ReadGCode:10' if ( coder.target('mex') || coder.target('rtw') )
            // 'ReadGCode:11' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
            // 'ReadGCode:13' pathRs274Src = '$(START_DIR)/../../rs274ngc/src';
            //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
            // 'ReadGCode:15' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
            // 'ReadGCode:16' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp',
            // '$(START_DIR)/../common/src'); 'ReadGCode:17'
            // coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src); 'ReadGCode:18'
            // coder.updateBuildInfo('addSourceFiles','interp_arc.cc', pathRs274Src); 'ReadGCode:19'
            // coder.updateBuildInfo('addSourceFiles','interp_array.cc', pathRs274Src);
            // 'ReadGCode:20' coder.updateBuildInfo('addSourceFiles','interp_base.cc',
            // pathRs274Src); 'ReadGCode:21'
            // coder.updateBuildInfo('addSourceFiles','interp_check.cc', pathRs274Src);
            // 'ReadGCode:22' coder.updateBuildInfo('addSourceFiles','interp_convert.cc',
            // pathRs274Src); 'ReadGCode:23'
            // coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', pathRs274Src);
            // 'ReadGCode:24' coder.updateBuildInfo('addSourceFiles','interp_execute.cc',
            // pathRs274Src); 'ReadGCode:25'
            // coder.updateBuildInfo('addSourceFiles','interp_find.cc', pathRs274Src);
            // 'ReadGCode:26' coder.updateBuildInfo('addSourceFiles','interp_internal.cc',
            // pathRs274Src); 'ReadGCode:27'
            // coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
            // 'ReadGCode:28' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
            // pathRs274Src); 'ReadGCode:29'
            // coder.updateBuildInfo('addSourceFiles','interp_o_word.cc', pathRs274Src);
            // 'ReadGCode:30' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
            // pathRs274Src); 'ReadGCode:31'
            // coder.updateBuildInfo('addSourceFiles','interp_read.cc', pathRs274Src);
            // 'ReadGCode:32' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
            // pathRs274Src); 'ReadGCode:33'
            // coder.updateBuildInfo('addSourceFiles','interp_setup.cc', pathRs274Src);
            // 'ReadGCode:34' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
            // pathRs274Src); 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','ocn.cc',
            // pathRs274Src); 'ReadGCode:36'
            // coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
            // 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
            // 'ReadGCode:38' coder.updateBuildInfo('addLinkFlags', '-ldl');
            //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
            // 'ReadGCode:40' coder.cinclude('cpp_interp.hpp');
            // 'ReadGCode:42' switch cmd
            // 'ReadGCode:45' case ReadGCodeCmd.Read
            // 'ReadGCode:46' is_loaded = int32(0);
            // 'ReadGCode:47' is_loaded = coder.ceval( 'cpp_interp_loaded' );
            is_loaded = cpp_interp_loaded();
            // 'ReadGCode:48' if is_loaded
            if (is_loaded != 0) {
                __m128d r2;
                __m128d r3;
                __m128d r4;
                // 'ReadGCode:49' status = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct )
                // );
                b_status = cpp_interp_read(&b_CurvStruct);
                // 'ReadGCode:50' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
                // 'ReadGCode:51' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
                r2 = _mm_loadu_pd(&b_CurvStruct.R0[3]);
                r3 = _mm_set1_pd(0.017453292519943295);
                _mm_storeu_pd(&b_CurvStruct.R0[3], _mm_mul_pd(r3, r2));
                r4 = _mm_loadu_pd(&b_CurvStruct.R1[3]);
                _mm_storeu_pd(&b_CurvStruct.R1[3], _mm_mul_pd(r3, r4));
                b_CurvStruct.R0[5] *= 0.017453292519943295;
                b_CurvStruct.R1[5] *= 0.017453292519943295;
            } else {
                // 'ReadGCode:52' else
                // 'ReadGCode:53' status = int32(0);
                b_status = 0;
            }
            status = b_status;
            // 'FeedoptPlan:23' for j = 1 : StructTypeName.NumberAxisMax
            // 'FeedoptPlan:32' if( CurvStruct.Info.FeedRate == 0.0 )
            if (b_CurvStruct.Info.FeedRate == 0.0) {
                // 'FeedoptPlan:33' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                b_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
            }
            // 'FeedoptPlan:35' if( status == 1 && CurvStruct.Info.Type ~= CurveType.None )
            if ((b_status == 1) && (b_CurvStruct.Info.Type != CurveType_None)) {
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
            if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
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
        unsigned int N;
        int d_loop_ub;
        int fb_loop_ub;
        int i46;
        int m_loop_ub;
        int ob_loop_ub;
        int v_loop_ub;
        // 'FeedoptPlan:60' case Fopt.Check
        //          [ ctx.q_gcode ] = checkTrafo( ctx, ctx.q_gcode );
        // 'FeedoptPlan:62' ctx     = CheckCurvStructs( ctx );
        r.q_spline = ctx->q_spline;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        d_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= d_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[d_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        m_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            r.cfg.maskCart[i13] = ctx->cfg.maskCart[i13];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        v_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i22{0}; i22 < v_loop_ub; i22++) {
            r.cfg.maskRot[i22] = ctx->cfg.maskRot[i22];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        fb_loop_ub = ctx->cfg.indCart.size[0];
        for (int i31{0}; i31 < fb_loop_ub; i31++) {
            r.cfg.indCart[i31] = ctx->cfg.indCart.data[i31];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ob_loop_ub = ctx->cfg.indRot.size[0];
        for (int i40{0}; i40 < ob_loop_ub; i40++) {
            r.cfg.indRot[i40] = ctx->cfg.indRot.data[i40];
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
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
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
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Checking for cusps...\n");
            fflush(stdout);
        }
        // 'CheckCurvStructs:8' for k = 1 : N-1
        i46 = static_cast<int>(N - 1U);
        for (int k{0}; k < i46; k++) {
            double absx;
            double b_n;
            double c;
            double x;
            int i66;
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
            c = 0.0;
            i66 = r0D1.size(0);
            if (r0D1.size(0) >= 1) {
                for (int b_k{0}; b_k < i66; b_k++) {
                    c += r0D1[b_k] * r1D1[b_k];
                }
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
        // 'FeedoptPlan:63' ctx.op  = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        // 'FeedoptPlan:65' case Fopt.Compress
        // 'FeedoptPlan:66' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i4;
            unsigned int u;
            // 'FeedoptPlan:67' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i4 = static_cast<int>(u);
            for (int j{0}; j < i4; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:68' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r1);
                ctx->q_compress.push(&r1);
            }
        } else {
            int cc_loop_ub;
            int df_loop_ub;
            int e_loop_ub;
            int ee_loop_ub;
            int fd_loop_ub;
            int gb_loop_ub;
            int gc_loop_ub;
            int hf_loop_ub;
            int kc_loop_ub;
            int lf_loop_ub;
            int me_loop_ub;
            int n_loop_ub;
            int nd_loop_ub;
            int oc_loop_ub;
            int pb_loop_ub;
            int pf_loop_ub;
            int qe_loop_ub;
            int sc_loop_ub;
            int tb_loop_ub;
            int tf_loop_ub;
            int ue_loop_ub;
            int vd_loop_ub;
            int w_loop_ub;
            int wc_loop_ub;
            int xb_loop_ub;
            int ye_loop_ub;
            // 'FeedoptPlan:70' else
            // 'FeedoptPlan:71' ctx = compressCurvStructs(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            e_loop_ub = ctx->BasisVal.size(1);
            for (int i5{0}; i5 < e_loop_ub; i5++) {
                int l_loop_ub;
                l_loop_ub = ctx->BasisVal.size(0);
                for (int i12{0}; i12 < l_loop_ub; i12++) {
                    r.BasisVal[i12 + r.BasisVal.size(0) * i5] =
                        ctx->BasisVal[i12 + ctx->BasisVal.size(0) * i5];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            n_loop_ub = ctx->BasisValD.size(1);
            for (int i14{0}; i14 < n_loop_ub; i14++) {
                int u_loop_ub;
                u_loop_ub = ctx->BasisValD.size(0);
                for (int i21{0}; i21 < u_loop_ub; i21++) {
                    r.BasisValD[i21 + r.BasisValD.size(0) * i14] =
                        ctx->BasisValD[i21 + ctx->BasisValD.size(0) * i14];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            w_loop_ub = ctx->BasisValDD.size(1);
            for (int i23{0}; i23 < w_loop_ub; i23++) {
                int eb_loop_ub;
                eb_loop_ub = ctx->BasisValDD.size(0);
                for (int i30{0}; i30 < eb_loop_ub; i30++) {
                    r.BasisValDD[i30 + r.BasisValDD.size(0) * i23] =
                        ctx->BasisValDD[i30 + ctx->BasisValDD.size(0) * i23];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            gb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i32{0}; i32 < gb_loop_ub; i32++) {
                int nb_loop_ub;
                nb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i39{0}; i39 < nb_loop_ub; i39++) {
                    r.BasisValDDD[i39 + r.BasisValDDD.size(0) * i32] =
                        ctx->BasisValDDD[i39 + ctx->BasisValDDD.size(0) * i32];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            pb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i41{0}; i41 < pb_loop_ub; i41++) {
                r.BasisIntegr[i41] = ctx->BasisIntegr[i41];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            tb_loop_ub = ctx->u_vec.size(1);
            for (int i45{0}; i45 < tb_loop_ub; i45++) {
                r.u_vec[i45] = ctx->u_vec[i45];
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
            xb_loop_ub = ctx->cfg.maskTot.size[1];
            if (0 <= xb_loop_ub - 1) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[xb_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
            cc_loop_ub = ctx->cfg.maskCart.size(1);
            for (int i50{0}; i50 < cc_loop_ub; i50++) {
                r.cfg.maskCart[i50] = ctx->cfg.maskCart[i50];
            }
            r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
            gc_loop_ub = ctx->cfg.maskRot.size(1);
            for (int i54{0}; i54 < gc_loop_ub; i54++) {
                r.cfg.maskRot[i54] = ctx->cfg.maskRot[i54];
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            kc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i58{0}; i58 < kc_loop_ub; i58++) {
                r.cfg.indCart[i58] = ctx->cfg.indCart.data[i58];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            oc_loop_ub = ctx->cfg.indRot.size[0];
            for (int i62{0}; i62 < oc_loop_ub; i62++) {
                r.cfg.indRot[i62] = ctx->cfg.indRot.data[i62];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
            sc_loop_ub = ctx->cfg.kin_params.size(0);
            for (int i70{0}; i70 < sc_loop_ub; i70++) {
                r.cfg.kin_params[i70] = ctx->cfg.kin_params[i70];
            }
            for (int i71{0}; i71 < 5; i71++) {
                r.cfg.kin_type[i71] = ctx->cfg.kin_type[i71];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i75{0}; i75 < 6; i75++) {
                r.cfg.vmax[i75] = ctx->cfg.vmax[i75];
                r.cfg.amax[i75] = ctx->cfg.amax[i75];
                r.cfg.jmax[i75] = ctx->cfg.jmax[i75];
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
            r.cfg.Smoothing = ctx->cfg.Smoothing;
            r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
            for (int e_i{0}; e_i < 5; e_i++) {
                r.cfg.GaussLegendreX[e_i] = ctx->cfg.GaussLegendreX[e_i];
                r.cfg.GaussLegendreW[e_i] = ctx->cfg.GaussLegendreW[e_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i79{0}; i79 < 9; i79++) {
                r.cfg.LogFileName[i79] = ctx->cfg.LogFileName[i79];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            wc_loop_ub = ctx->Coeff.size(1);
            for (int i83{0}; i83 < wc_loop_ub; i83++) {
                int bd_loop_ub;
                bd_loop_ub = ctx->Coeff.size(0);
                for (int i87{0}; i87 < bd_loop_ub; i87++) {
                    r.Coeff[i87 + r.Coeff.size(0) * i83] =
                        ctx->Coeff[i87 + ctx->Coeff.size(0) * i83];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            fd_loop_ub = r.BasisVal.size(1);
            for (int i91{0}; i91 < fd_loop_ub; i91++) {
                int md_loop_ub;
                md_loop_ub = r.BasisVal.size(0);
                for (int i98{0}; i98 < md_loop_ub; i98++) {
                    ctx->BasisVal[i98 + ctx->BasisVal.size(0) * i91] =
                        r.BasisVal[i98 + r.BasisVal.size(0) * i91];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            nd_loop_ub = r.BasisValD.size(1);
            for (int i99{0}; i99 < nd_loop_ub; i99++) {
                int ud_loop_ub;
                ud_loop_ub = r.BasisValD.size(0);
                for (int i106{0}; i106 < ud_loop_ub; i106++) {
                    ctx->BasisValD[i106 + ctx->BasisValD.size(0) * i99] =
                        r.BasisValD[i106 + r.BasisValD.size(0) * i99];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            vd_loop_ub = r.BasisValDD.size(1);
            for (int i107{0}; i107 < vd_loop_ub; i107++) {
                int de_loop_ub;
                de_loop_ub = r.BasisValDD.size(0);
                for (int i114{0}; i114 < de_loop_ub; i114++) {
                    ctx->BasisValDD[i114 + ctx->BasisValDD.size(0) * i107] =
                        r.BasisValDD[i114 + r.BasisValDD.size(0) * i107];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            ee_loop_ub = r.BasisValDDD.size(1);
            for (int i115{0}; i115 < ee_loop_ub; i115++) {
                int le_loop_ub;
                le_loop_ub = r.BasisValDDD.size(0);
                for (int i122{0}; i122 < le_loop_ub; i122++) {
                    ctx->BasisValDDD[i122 + ctx->BasisValDDD.size(0) * i115] =
                        r.BasisValDDD[i122 + r.BasisValDDD.size(0) * i115];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            me_loop_ub = r.BasisIntegr.size(0);
            for (int i123{0}; i123 < me_loop_ub; i123++) {
                ctx->BasisIntegr[i123] = r.BasisIntegr[i123];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            qe_loop_ub = r.u_vec.size(1);
            for (int i127{0}; i127 < qe_loop_ub; i127++) {
                ctx->u_vec[i127] = r.u_vec[i127];
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
            ue_loop_ub = r.cfg.maskTot.size[1];
            if (0 <= ue_loop_ub - 1) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ue_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.set_size(1, r.cfg.maskCart.size(1));
            ye_loop_ub = r.cfg.maskCart.size(1);
            for (int i131{0}; i131 < ye_loop_ub; i131++) {
                ctx->cfg.maskCart[i131] = r.cfg.maskCart[i131];
            }
            ctx->cfg.maskRot.set_size(1, r.cfg.maskRot.size(1));
            df_loop_ub = r.cfg.maskRot.size(1);
            for (int i135{0}; i135 < df_loop_ub; i135++) {
                ctx->cfg.maskRot[i135] = r.cfg.maskRot[i135];
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            hf_loop_ub = r.cfg.indCart.size(0);
            for (int i139{0}; i139 < hf_loop_ub; i139++) {
                ctx->cfg.indCart.data[i139] = r.cfg.indCart[i139];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            lf_loop_ub = r.cfg.indRot.size(0);
            for (int i143{0}; i143 < lf_loop_ub; i143++) {
                ctx->cfg.indRot.data[i143] = r.cfg.indRot[i143];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.kin_params.set_size(r.cfg.kin_params.size(0));
            pf_loop_ub = r.cfg.kin_params.size(0);
            for (int i149{0}; i149 < pf_loop_ub; i149++) {
                ctx->cfg.kin_params[i149] = r.cfg.kin_params[i149];
            }
            for (int i151{0}; i151 < 5; i151++) {
                ctx->cfg.kin_type[i151] = r.cfg.kin_type[i151];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i155{0}; i155 < 6; i155++) {
                ctx->cfg.vmax[i155] = r.cfg.vmax[i155];
                ctx->cfg.amax[i155] = r.cfg.amax[i155];
                ctx->cfg.jmax[i155] = r.cfg.jmax[i155];
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
            ctx->cfg.Smoothing = r.cfg.Smoothing;
            ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
            for (int i_i{0}; i_i < 5; i_i++) {
                ctx->cfg.GaussLegendreX[i_i] = r.cfg.GaussLegendreX[i_i];
                ctx->cfg.GaussLegendreW[i_i] = r.cfg.GaussLegendreW[i_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i159{0}; i159 < 9; i159++) {
                ctx->cfg.LogFileName[i159] = r.cfg.LogFileName[i159];
            }
            ctx->errcode = r.errcode;
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            tf_loop_ub = r.Coeff.size(1);
            for (int i163{0}; i163 < tf_loop_ub; i163++) {
                int xf_loop_ub;
                xf_loop_ub = r.Coeff.size(0);
                for (int i167{0}; i167 < xf_loop_ub; i167++) {
                    ctx->Coeff[i167 + ctx->Coeff.size(0) * i163] =
                        r.Coeff[i167 + r.Coeff.size(0) * i163];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        //          if( ctx.q_compress.size > 1 )
        //              error( "should be only compressing");
        //          end
        // 'FeedoptPlan:78' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:79' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int ae_loop_ub;
        int af_loop_ub;
        int bb_loop_ub;
        int cd_loop_ub;
        int dc_loop_ub;
        int ef_loop_ub;
        int hc_loop_ub;
        int i_loop_ub;
        int ie_loop_ub;
        int if_loop_ub;
        int jd_loop_ub;
        int kb_loop_ub;
        int lc_loop_ub;
        int loop_ub;
        int mf_loop_ub;
        int ne_loop_ub;
        int pc_loop_ub;
        int qb_loop_ub;
        int qf_loop_ub;
        int r_loop_ub;
        int rd_loop_ub;
        int re_loop_ub;
        int tc_loop_ub;
        int ub_loop_ub;
        int ve_loop_ub;
        int yb_loop_ub;
        // 'FeedoptPlan:81' case Fopt.Smooth
        // 'FeedoptPlan:82' ctx = smoothCurvStructs(ctx);
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        loop_ub = ctx->BasisVal.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            int f_loop_ub;
            f_loop_ub = ctx->BasisVal.size(0);
            for (int i6{0}; i6 < f_loop_ub; i6++) {
                r.BasisVal[i6 + r.BasisVal.size(0) * i1] =
                    ctx->BasisVal[i6 + ctx->BasisVal.size(0) * i1];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        i_loop_ub = ctx->BasisValD.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            int o_loop_ub;
            o_loop_ub = ctx->BasisValD.size(0);
            for (int i15{0}; i15 < o_loop_ub; i15++) {
                r.BasisValD[i15 + r.BasisValD.size(0) * i9] =
                    ctx->BasisValD[i15 + ctx->BasisValD.size(0) * i9];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        r_loop_ub = ctx->BasisValDD.size(1);
        for (int i18{0}; i18 < r_loop_ub; i18++) {
            int x_loop_ub;
            x_loop_ub = ctx->BasisValDD.size(0);
            for (int i24{0}; i24 < x_loop_ub; i24++) {
                r.BasisValDD[i24 + r.BasisValDD.size(0) * i18] =
                    ctx->BasisValDD[i24 + ctx->BasisValDD.size(0) * i18];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        bb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i27{0}; i27 < bb_loop_ub; i27++) {
            int hb_loop_ub;
            hb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i33{0}; i33 < hb_loop_ub; i33++) {
                r.BasisValDDD[i33 + r.BasisValDDD.size(0) * i27] =
                    ctx->BasisValDDD[i33 + ctx->BasisValDDD.size(0) * i27];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        kb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i36{0}; i36 < kb_loop_ub; i36++) {
            r.BasisIntegr[i36] = ctx->BasisIntegr[i36];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        qb_loop_ub = ctx->u_vec.size(1);
        for (int i42{0}; i42 < qb_loop_ub; i42++) {
            r.u_vec[i42] = ctx->u_vec[i42];
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
        ub_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= ub_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ub_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        yb_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i47{0}; i47 < yb_loop_ub; i47++) {
            r.cfg.maskCart[i47] = ctx->cfg.maskCart[i47];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        dc_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i51{0}; i51 < dc_loop_ub; i51++) {
            r.cfg.maskRot[i51] = ctx->cfg.maskRot[i51];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        hc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i55{0}; i55 < hc_loop_ub; i55++) {
            r.cfg.indCart[i55] = ctx->cfg.indCart.data[i55];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        lc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i59{0}; i59 < lc_loop_ub; i59++) {
            r.cfg.indRot[i59] = ctx->cfg.indRot.data[i59];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
        pc_loop_ub = ctx->cfg.kin_params.size(0);
        for (int i63{0}; i63 < pc_loop_ub; i63++) {
            r.cfg.kin_params[i63] = ctx->cfg.kin_params[i63];
        }
        for (int i67{0}; i67 < 5; i67++) {
            r.cfg.kin_type[i67] = ctx->cfg.kin_type[i67];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i72{0}; i72 < 6; i72++) {
            r.cfg.vmax[i72] = ctx->cfg.vmax[i72];
            r.cfg.amax[i72] = ctx->cfg.amax[i72];
            r.cfg.jmax[i72] = ctx->cfg.jmax[i72];
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
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int b_i{0}; b_i < 5; b_i++) {
            r.cfg.GaussLegendreX[b_i] = ctx->cfg.GaussLegendreX[b_i];
            r.cfg.GaussLegendreW[b_i] = ctx->cfg.GaussLegendreW[b_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i76{0}; i76 < 9; i76++) {
            r.cfg.LogFileName[i76] = ctx->cfg.LogFileName[i76];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        tc_loop_ub = ctx->Coeff.size(1);
        for (int i80{0}; i80 < tc_loop_ub; i80++) {
            int xc_loop_ub;
            xc_loop_ub = ctx->Coeff.size(0);
            for (int i84{0}; i84 < xc_loop_ub; i84++) {
                r.Coeff[i84 + r.Coeff.size(0) * i80] = ctx->Coeff[i84 + ctx->Coeff.size(0) * i80];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        smoothCurvStructs(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        cd_loop_ub = r.BasisVal.size(1);
        for (int i88{0}; i88 < cd_loop_ub; i88++) {
            int gd_loop_ub;
            gd_loop_ub = r.BasisVal.size(0);
            for (int i92{0}; i92 < gd_loop_ub; i92++) {
                ctx->BasisVal[i92 + ctx->BasisVal.size(0) * i88] =
                    r.BasisVal[i92 + r.BasisVal.size(0) * i88];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        jd_loop_ub = r.BasisValD.size(1);
        for (int i95{0}; i95 < jd_loop_ub; i95++) {
            int od_loop_ub;
            od_loop_ub = r.BasisValD.size(0);
            for (int i100{0}; i100 < od_loop_ub; i100++) {
                ctx->BasisValD[i100 + ctx->BasisValD.size(0) * i95] =
                    r.BasisValD[i100 + r.BasisValD.size(0) * i95];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        rd_loop_ub = r.BasisValDD.size(1);
        for (int i103{0}; i103 < rd_loop_ub; i103++) {
            int wd_loop_ub;
            wd_loop_ub = r.BasisValDD.size(0);
            for (int i108{0}; i108 < wd_loop_ub; i108++) {
                ctx->BasisValDD[i108 + ctx->BasisValDD.size(0) * i103] =
                    r.BasisValDD[i108 + r.BasisValDD.size(0) * i103];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        ae_loop_ub = r.BasisValDDD.size(1);
        for (int i111{0}; i111 < ae_loop_ub; i111++) {
            int fe_loop_ub;
            fe_loop_ub = r.BasisValDDD.size(0);
            for (int i116{0}; i116 < fe_loop_ub; i116++) {
                ctx->BasisValDDD[i116 + ctx->BasisValDDD.size(0) * i111] =
                    r.BasisValDDD[i116 + r.BasisValDDD.size(0) * i111];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        ie_loop_ub = r.BasisIntegr.size(0);
        for (int i119{0}; i119 < ie_loop_ub; i119++) {
            ctx->BasisIntegr[i119] = r.BasisIntegr[i119];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        ne_loop_ub = r.u_vec.size(1);
        for (int i124{0}; i124 < ne_loop_ub; i124++) {
            ctx->u_vec[i124] = r.u_vec[i124];
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
        re_loop_ub = r.cfg.maskTot.size[1];
        if (0 <= re_loop_ub - 1) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[re_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.set_size(1, r.cfg.maskCart.size(1));
        ve_loop_ub = r.cfg.maskCart.size(1);
        for (int i128{0}; i128 < ve_loop_ub; i128++) {
            ctx->cfg.maskCart[i128] = r.cfg.maskCart[i128];
        }
        ctx->cfg.maskRot.set_size(1, r.cfg.maskRot.size(1));
        af_loop_ub = r.cfg.maskRot.size(1);
        for (int i132{0}; i132 < af_loop_ub; i132++) {
            ctx->cfg.maskRot[i132] = r.cfg.maskRot[i132];
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        ef_loop_ub = r.cfg.indCart.size(0);
        for (int i136{0}; i136 < ef_loop_ub; i136++) {
            ctx->cfg.indCart.data[i136] = r.cfg.indCart[i136];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        if_loop_ub = r.cfg.indRot.size(0);
        for (int i140{0}; i140 < if_loop_ub; i140++) {
            ctx->cfg.indRot.data[i140] = r.cfg.indRot[i140];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.kin_params.set_size(r.cfg.kin_params.size(0));
        mf_loop_ub = r.cfg.kin_params.size(0);
        for (int i144{0}; i144 < mf_loop_ub; i144++) {
            ctx->cfg.kin_params[i144] = r.cfg.kin_params[i144];
        }
        for (int i147{0}; i147 < 5; i147++) {
            ctx->cfg.kin_type[i147] = r.cfg.kin_type[i147];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i152{0}; i152 < 6; i152++) {
            ctx->cfg.vmax[i152] = r.cfg.vmax[i152];
            ctx->cfg.amax[i152] = r.cfg.amax[i152];
            ctx->cfg.jmax[i152] = r.cfg.jmax[i152];
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
        ctx->cfg.Smoothing = r.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int f_i{0}; f_i < 5; f_i++) {
            ctx->cfg.GaussLegendreX[f_i] = r.cfg.GaussLegendreX[f_i];
            ctx->cfg.GaussLegendreW[f_i] = r.cfg.GaussLegendreW[f_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i156{0}; i156 < 9; i156++) {
            ctx->cfg.LogFileName[i156] = r.cfg.LogFileName[i156];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        qf_loop_ub = r.Coeff.size(1);
        for (int i160{0}; i160 < qf_loop_ub; i160++) {
            int uf_loop_ub;
            uf_loop_ub = r.Coeff.size(0);
            for (int i164{0}; i164 < uf_loop_ub; i164++) {
                ctx->Coeff[i164 + ctx->Coeff.size(0) * i160] =
                    r.Coeff[i164 + r.Coeff.size(0) * i160];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:83' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:84' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Split: {
        int ac_loop_ub;
        int b_loop_ub;
        int be_loop_ub;
        int bf_loop_ub;
        int cb_loop_ub;
        int dd_loop_ub;
        int ec_loop_ub;
        int ff_loop_ub;
        int ic_loop_ub;
        int j_loop_ub;
        int je_loop_ub;
        int jf_loop_ub;
        int kd_loop_ub;
        int lb_loop_ub;
        int mc_loop_ub;
        int nf_loop_ub;
        int oe_loop_ub;
        int qc_loop_ub;
        int rb_loop_ub;
        int rf_loop_ub;
        int s_loop_ub;
        int sd_loop_ub;
        int se_loop_ub;
        int uc_loop_ub;
        int vb_loop_ub;
        int we_loop_ub;
        // 'FeedoptPlan:86' case Fopt.Split
        // 'FeedoptPlan:87' ctx = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        b_loop_ub = ctx->BasisVal.size(1);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            int g_loop_ub;
            g_loop_ub = ctx->BasisVal.size(0);
            for (int i7{0}; i7 < g_loop_ub; i7++) {
                r.BasisVal[i7 + r.BasisVal.size(0) * i2] =
                    ctx->BasisVal[i7 + ctx->BasisVal.size(0) * i2];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        j_loop_ub = ctx->BasisValD.size(1);
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            int p_loop_ub;
            p_loop_ub = ctx->BasisValD.size(0);
            for (int i16{0}; i16 < p_loop_ub; i16++) {
                r.BasisValD[i16 + r.BasisValD.size(0) * i10] =
                    ctx->BasisValD[i16 + ctx->BasisValD.size(0) * i10];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        s_loop_ub = ctx->BasisValDD.size(1);
        for (int i19{0}; i19 < s_loop_ub; i19++) {
            int y_loop_ub;
            y_loop_ub = ctx->BasisValDD.size(0);
            for (int i25{0}; i25 < y_loop_ub; i25++) {
                r.BasisValDD[i25 + r.BasisValDD.size(0) * i19] =
                    ctx->BasisValDD[i25 + ctx->BasisValDD.size(0) * i19];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        cb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i28{0}; i28 < cb_loop_ub; i28++) {
            int ib_loop_ub;
            ib_loop_ub = ctx->BasisValDDD.size(0);
            for (int i34{0}; i34 < ib_loop_ub; i34++) {
                r.BasisValDDD[i34 + r.BasisValDDD.size(0) * i28] =
                    ctx->BasisValDDD[i34 + ctx->BasisValDDD.size(0) * i28];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        lb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i37{0}; i37 < lb_loop_ub; i37++) {
            r.BasisIntegr[i37] = ctx->BasisIntegr[i37];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        rb_loop_ub = ctx->u_vec.size(1);
        for (int i43{0}; i43 < rb_loop_ub; i43++) {
            r.u_vec[i43] = ctx->u_vec[i43];
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
        vb_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= vb_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[vb_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        ac_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i48{0}; i48 < ac_loop_ub; i48++) {
            r.cfg.maskCart[i48] = ctx->cfg.maskCart[i48];
        }
        r.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        ec_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i52{0}; i52 < ec_loop_ub; i52++) {
            r.cfg.maskRot[i52] = ctx->cfg.maskRot[i52];
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ic_loop_ub = ctx->cfg.indCart.size[0];
        for (int i56{0}; i56 < ic_loop_ub; i56++) {
            r.cfg.indCart[i56] = ctx->cfg.indCart.data[i56];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        mc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i60{0}; i60 < mc_loop_ub; i60++) {
            r.cfg.indRot[i60] = ctx->cfg.indRot.data[i60];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
        qc_loop_ub = ctx->cfg.kin_params.size(0);
        for (int i64{0}; i64 < qc_loop_ub; i64++) {
            r.cfg.kin_params[i64] = ctx->cfg.kin_params[i64];
        }
        for (int i68{0}; i68 < 5; i68++) {
            r.cfg.kin_type[i68] = ctx->cfg.kin_type[i68];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i73{0}; i73 < 6; i73++) {
            r.cfg.vmax[i73] = ctx->cfg.vmax[i73];
            r.cfg.amax[i73] = ctx->cfg.amax[i73];
            r.cfg.jmax[i73] = ctx->cfg.jmax[i73];
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
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int c_i{0}; c_i < 5; c_i++) {
            r.cfg.GaussLegendreX[c_i] = ctx->cfg.GaussLegendreX[c_i];
            r.cfg.GaussLegendreW[c_i] = ctx->cfg.GaussLegendreW[c_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i77{0}; i77 < 9; i77++) {
            r.cfg.LogFileName[i77] = ctx->cfg.LogFileName[i77];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        uc_loop_ub = ctx->Coeff.size(1);
        for (int i81{0}; i81 < uc_loop_ub; i81++) {
            int yc_loop_ub;
            yc_loop_ub = ctx->Coeff.size(0);
            for (int i85{0}; i85 < yc_loop_ub; i85++) {
                r.Coeff[i85 + r.Coeff.size(0) * i81] = ctx->Coeff[i85 + ctx->Coeff.size(0) * i81];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        splitQueue(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        dd_loop_ub = r.BasisVal.size(1);
        for (int i89{0}; i89 < dd_loop_ub; i89++) {
            int hd_loop_ub;
            hd_loop_ub = r.BasisVal.size(0);
            for (int i93{0}; i93 < hd_loop_ub; i93++) {
                ctx->BasisVal[i93 + ctx->BasisVal.size(0) * i89] =
                    r.BasisVal[i93 + r.BasisVal.size(0) * i89];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        kd_loop_ub = r.BasisValD.size(1);
        for (int i96{0}; i96 < kd_loop_ub; i96++) {
            int pd_loop_ub;
            pd_loop_ub = r.BasisValD.size(0);
            for (int i101{0}; i101 < pd_loop_ub; i101++) {
                ctx->BasisValD[i101 + ctx->BasisValD.size(0) * i96] =
                    r.BasisValD[i101 + r.BasisValD.size(0) * i96];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        sd_loop_ub = r.BasisValDD.size(1);
        for (int i104{0}; i104 < sd_loop_ub; i104++) {
            int xd_loop_ub;
            xd_loop_ub = r.BasisValDD.size(0);
            for (int i109{0}; i109 < xd_loop_ub; i109++) {
                ctx->BasisValDD[i109 + ctx->BasisValDD.size(0) * i104] =
                    r.BasisValDD[i109 + r.BasisValDD.size(0) * i104];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        be_loop_ub = r.BasisValDDD.size(1);
        for (int i112{0}; i112 < be_loop_ub; i112++) {
            int ge_loop_ub;
            ge_loop_ub = r.BasisValDDD.size(0);
            for (int i117{0}; i117 < ge_loop_ub; i117++) {
                ctx->BasisValDDD[i117 + ctx->BasisValDDD.size(0) * i112] =
                    r.BasisValDDD[i117 + r.BasisValDDD.size(0) * i112];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        je_loop_ub = r.BasisIntegr.size(0);
        for (int i120{0}; i120 < je_loop_ub; i120++) {
            ctx->BasisIntegr[i120] = r.BasisIntegr[i120];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        oe_loop_ub = r.u_vec.size(1);
        for (int i125{0}; i125 < oe_loop_ub; i125++) {
            ctx->u_vec[i125] = r.u_vec[i125];
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
        se_loop_ub = r.cfg.maskTot.size[1];
        if (0 <= se_loop_ub - 1) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[se_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.set_size(1, r.cfg.maskCart.size(1));
        we_loop_ub = r.cfg.maskCart.size(1);
        for (int i129{0}; i129 < we_loop_ub; i129++) {
            ctx->cfg.maskCart[i129] = r.cfg.maskCart[i129];
        }
        ctx->cfg.maskRot.set_size(1, r.cfg.maskRot.size(1));
        bf_loop_ub = r.cfg.maskRot.size(1);
        for (int i133{0}; i133 < bf_loop_ub; i133++) {
            ctx->cfg.maskRot[i133] = r.cfg.maskRot[i133];
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        ff_loop_ub = r.cfg.indCart.size(0);
        for (int i137{0}; i137 < ff_loop_ub; i137++) {
            ctx->cfg.indCart.data[i137] = r.cfg.indCart[i137];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        jf_loop_ub = r.cfg.indRot.size(0);
        for (int i141{0}; i141 < jf_loop_ub; i141++) {
            ctx->cfg.indRot.data[i141] = r.cfg.indRot[i141];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.kin_params.set_size(r.cfg.kin_params.size(0));
        nf_loop_ub = r.cfg.kin_params.size(0);
        for (int i145{0}; i145 < nf_loop_ub; i145++) {
            ctx->cfg.kin_params[i145] = r.cfg.kin_params[i145];
        }
        for (int i148{0}; i148 < 5; i148++) {
            ctx->cfg.kin_type[i148] = r.cfg.kin_type[i148];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i153{0}; i153 < 6; i153++) {
            ctx->cfg.vmax[i153] = r.cfg.vmax[i153];
            ctx->cfg.amax[i153] = r.cfg.amax[i153];
            ctx->cfg.jmax[i153] = r.cfg.jmax[i153];
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
        ctx->cfg.Smoothing = r.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int g_i{0}; g_i < 5; g_i++) {
            ctx->cfg.GaussLegendreX[g_i] = r.cfg.GaussLegendreX[g_i];
            ctx->cfg.GaussLegendreW[g_i] = r.cfg.GaussLegendreW[g_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i157{0}; i157 < 9; i157++) {
            ctx->cfg.LogFileName[i157] = r.cfg.LogFileName[i157];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        rf_loop_ub = r.Coeff.size(1);
        for (int i161{0}; i161 < rf_loop_ub; i161++) {
            int vf_loop_ub;
            vf_loop_ub = r.Coeff.size(0);
            for (int i165{0}; i165 < vf_loop_ub; i165++) {
                ctx->Coeff[i165 + ctx->Coeff.size(0) * i161] =
                    r.Coeff[i165 + r.Coeff.size(0) * i161];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:88' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:89' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
    } break;
    case Fopt_Opt: {
        int bc_loop_ub;
        int c_loop_ub;
        int ce_loop_ub;
        int cf_loop_ub;
        int db_loop_ub;
        int ed_loop_ub;
        int fc_loop_ub;
        int gf_loop_ub;
        int jc_loop_ub;
        int k_loop_ub;
        int ke_loop_ub;
        int kf_loop_ub;
        int ld_loop_ub;
        int mb_loop_ub;
        int nc_loop_ub;
        int of_loop_ub;
        int pe_loop_ub;
        int rc_loop_ub;
        int sb_loop_ub;
        int sf_loop_ub;
        int t_loop_ub;
        int td_loop_ub;
        int te_loop_ub;
        int vc_loop_ub;
        int wb_loop_ub;
        int xe_loop_ub;
        // 'FeedoptPlan:91' case Fopt.Opt
        // 'FeedoptPlan:92' [ ctx, optimized, opt_curv, quit ] = feedratePlanning( ctx );
        b_ctx.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        c_loop_ub = ctx->BasisVal.size(1);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            int h_loop_ub;
            h_loop_ub = ctx->BasisVal.size(0);
            for (int i8{0}; i8 < h_loop_ub; i8++) {
                b_ctx.BasisVal[i8 + b_ctx.BasisVal.size(0) * i3] =
                    ctx->BasisVal[i8 + ctx->BasisVal.size(0) * i3];
            }
        }
        b_ctx.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        k_loop_ub = ctx->BasisValD.size(1);
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            int q_loop_ub;
            q_loop_ub = ctx->BasisValD.size(0);
            for (int i17{0}; i17 < q_loop_ub; i17++) {
                b_ctx.BasisValD[i17 + b_ctx.BasisValD.size(0) * i11] =
                    ctx->BasisValD[i17 + ctx->BasisValD.size(0) * i11];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        t_loop_ub = ctx->BasisValDD.size(1);
        for (int i20{0}; i20 < t_loop_ub; i20++) {
            int ab_loop_ub;
            ab_loop_ub = ctx->BasisValDD.size(0);
            for (int i26{0}; i26 < ab_loop_ub; i26++) {
                b_ctx.BasisValDD[i26 + b_ctx.BasisValDD.size(0) * i20] =
                    ctx->BasisValDD[i26 + ctx->BasisValDD.size(0) * i20];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        db_loop_ub = ctx->BasisValDDD.size(1);
        for (int i29{0}; i29 < db_loop_ub; i29++) {
            int jb_loop_ub;
            jb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i35{0}; i35 < jb_loop_ub; i35++) {
                b_ctx.BasisValDDD[i35 + b_ctx.BasisValDDD.size(0) * i29] =
                    ctx->BasisValDDD[i35 + ctx->BasisValDDD.size(0) * i29];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        mb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i38{0}; i38 < mb_loop_ub; i38++) {
            b_ctx.BasisIntegr[i38] = ctx->BasisIntegr[i38];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        sb_loop_ub = ctx->u_vec.size(1);
        for (int i44{0}; i44 < sb_loop_ub; i44++) {
            b_ctx.u_vec[i44] = ctx->u_vec[i44];
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
        wb_loop_ub = ctx->cfg.maskTot.size[1];
        if (0 <= wb_loop_ub - 1) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[wb_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.set_size(1, ctx->cfg.maskCart.size(1));
        bc_loop_ub = ctx->cfg.maskCart.size(1);
        for (int i49{0}; i49 < bc_loop_ub; i49++) {
            b_ctx.cfg.maskCart[i49] = ctx->cfg.maskCart[i49];
        }
        b_ctx.cfg.maskRot.set_size(1, ctx->cfg.maskRot.size(1));
        fc_loop_ub = ctx->cfg.maskRot.size(1);
        for (int i53{0}; i53 < fc_loop_ub; i53++) {
            b_ctx.cfg.maskRot[i53] = ctx->cfg.maskRot[i53];
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        jc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i57{0}; i57 < jc_loop_ub; i57++) {
            b_ctx.cfg.indCart[i57] = ctx->cfg.indCart.data[i57];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        nc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i61{0}; i61 < nc_loop_ub; i61++) {
            b_ctx.cfg.indRot[i61] = ctx->cfg.indRot.data[i61];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.kin_params.set_size(ctx->cfg.kin_params.size(0));
        rc_loop_ub = ctx->cfg.kin_params.size(0);
        for (int i65{0}; i65 < rc_loop_ub; i65++) {
            b_ctx.cfg.kin_params[i65] = ctx->cfg.kin_params[i65];
        }
        for (int i69{0}; i69 < 5; i69++) {
            b_ctx.cfg.kin_type[i69] = ctx->cfg.kin_type[i69];
        }
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        b_ctx.cfg.fmax = ctx->cfg.fmax;
        b_ctx.cfg.smax = ctx->cfg.smax;
        for (int i74{0}; i74 < 6; i74++) {
            b_ctx.cfg.vmax[i74] = ctx->cfg.vmax[i74];
            b_ctx.cfg.amax[i74] = ctx->cfg.amax[i74];
            b_ctx.cfg.jmax[i74] = ctx->cfg.jmax[i74];
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
        b_ctx.cfg.Smoothing = ctx->cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int d_i{0}; d_i < 5; d_i++) {
            b_ctx.cfg.GaussLegendreX[d_i] = ctx->cfg.GaussLegendreX[d_i];
            b_ctx.cfg.GaussLegendreW[d_i] = ctx->cfg.GaussLegendreW[d_i];
        }
        b_ctx.cfg.opt = ctx->cfg.opt;
        for (int i78{0}; i78 < 9; i78++) {
            b_ctx.cfg.LogFileName[i78] = ctx->cfg.LogFileName[i78];
        }
        b_ctx.errcode = ctx->errcode;
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        vc_loop_ub = ctx->Coeff.size(1);
        for (int i82{0}; i82 < vc_loop_ub; i82++) {
            int ad_loop_ub;
            ad_loop_ub = ctx->Coeff.size(0);
            for (int i86{0}; i86 < ad_loop_ub; i86++) {
                b_ctx.Coeff[i86 + b_ctx.Coeff.size(0) * i82] =
                    ctx->Coeff[i86 + ctx->Coeff.size(0) * i82];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        feedratePlanning(&b_ctx, &c_optimized, &opt_curv, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        ed_loop_ub = b_ctx.BasisVal.size(1);
        for (int i90{0}; i90 < ed_loop_ub; i90++) {
            int id_loop_ub;
            id_loop_ub = b_ctx.BasisVal.size(0);
            for (int i94{0}; i94 < id_loop_ub; i94++) {
                ctx->BasisVal[i94 + ctx->BasisVal.size(0) * i90] =
                    b_ctx.BasisVal[i94 + b_ctx.BasisVal.size(0) * i90];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        ld_loop_ub = b_ctx.BasisValD.size(1);
        for (int i97{0}; i97 < ld_loop_ub; i97++) {
            int qd_loop_ub;
            qd_loop_ub = b_ctx.BasisValD.size(0);
            for (int i102{0}; i102 < qd_loop_ub; i102++) {
                ctx->BasisValD[i102 + ctx->BasisValD.size(0) * i97] =
                    b_ctx.BasisValD[i102 + b_ctx.BasisValD.size(0) * i97];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        td_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i105{0}; i105 < td_loop_ub; i105++) {
            int yd_loop_ub;
            yd_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i110{0}; i110 < yd_loop_ub; i110++) {
                ctx->BasisValDD[i110 + ctx->BasisValDD.size(0) * i105] =
                    b_ctx.BasisValDD[i110 + b_ctx.BasisValDD.size(0) * i105];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        ce_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i113{0}; i113 < ce_loop_ub; i113++) {
            int he_loop_ub;
            he_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i118{0}; i118 < he_loop_ub; i118++) {
                ctx->BasisValDDD[i118 + ctx->BasisValDDD.size(0) * i113] =
                    b_ctx.BasisValDDD[i118 + b_ctx.BasisValDDD.size(0) * i113];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        ke_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i121{0}; i121 < ke_loop_ub; i121++) {
            ctx->BasisIntegr[i121] = b_ctx.BasisIntegr[i121];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        pe_loop_ub = b_ctx.u_vec.size(1);
        for (int i126{0}; i126 < pe_loop_ub; i126++) {
            ctx->u_vec[i126] = b_ctx.u_vec[i126];
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
        te_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (0 <= te_loop_ub - 1) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[te_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.set_size(1, b_ctx.cfg.maskCart.size(1));
        xe_loop_ub = b_ctx.cfg.maskCart.size(1);
        for (int i130{0}; i130 < xe_loop_ub; i130++) {
            ctx->cfg.maskCart[i130] = b_ctx.cfg.maskCart[i130];
        }
        ctx->cfg.maskRot.set_size(1, b_ctx.cfg.maskRot.size(1));
        cf_loop_ub = b_ctx.cfg.maskRot.size(1);
        for (int i134{0}; i134 < cf_loop_ub; i134++) {
            ctx->cfg.maskRot[i134] = b_ctx.cfg.maskRot[i134];
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        gf_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i138{0}; i138 < gf_loop_ub; i138++) {
            ctx->cfg.indCart.data[i138] = b_ctx.cfg.indCart[i138];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        kf_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i142{0}; i142 < kf_loop_ub; i142++) {
            ctx->cfg.indRot.data[i142] = b_ctx.cfg.indRot[i142];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.kin_params.set_size(b_ctx.cfg.kin_params.size(0));
        of_loop_ub = b_ctx.cfg.kin_params.size(0);
        for (int i146{0}; i146 < of_loop_ub; i146++) {
            ctx->cfg.kin_params[i146] = b_ctx.cfg.kin_params[i146];
        }
        for (int i150{0}; i150 < 5; i150++) {
            ctx->cfg.kin_type[i150] = b_ctx.cfg.kin_type[i150];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        ctx->cfg.fmax = b_ctx.cfg.fmax;
        ctx->cfg.smax = b_ctx.cfg.smax;
        for (int i154{0}; i154 < 6; i154++) {
            ctx->cfg.vmax[i154] = b_ctx.cfg.vmax[i154];
            ctx->cfg.amax[i154] = b_ctx.cfg.amax[i154];
            ctx->cfg.jmax[i154] = b_ctx.cfg.jmax[i154];
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
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int h_i{0}; h_i < 5; h_i++) {
            ctx->cfg.GaussLegendreX[h_i] = b_ctx.cfg.GaussLegendreX[h_i];
            ctx->cfg.GaussLegendreW[h_i] = b_ctx.cfg.GaussLegendreW[h_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i158{0}; i158 < 9; i158++) {
            ctx->cfg.LogFileName[i158] = b_ctx.cfg.LogFileName[i158];
        }
        ctx->errcode = b_ctx.errcode;
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        sf_loop_ub = b_ctx.Coeff.size(1);
        for (int i162{0}; i162 < sf_loop_ub; i162++) {
            int wf_loop_ub;
            wf_loop_ub = b_ctx.Coeff.size(0);
            for (int i166{0}; i166 < wf_loop_ub; i166++) {
                ctx->Coeff[i166 + ctx->Coeff.size(0) * i162] =
                    b_ctx.Coeff[i166 + b_ctx.Coeff.size(0) * i162];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        b_optimized = c_optimized;
        // 'FeedoptPlan:93' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:94' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:95' ctx.q_opt.push( opt_curv );
            b_ctx.q_opt.push(&opt_curv);
        }
        // 'FeedoptPlan:98' if( quit )
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:100' case Fopt.Finished
        // 'FeedoptPlan:101' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:103' otherwise
        // 'FeedoptPlan:104' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("FEEDOPT: WRONG STATE\n");
            fflush(stdout);
        }
        // 'FeedoptPlan:105' ctx.op = Fopt.Finished;
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
