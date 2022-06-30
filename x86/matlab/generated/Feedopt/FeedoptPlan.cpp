//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
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
#include "splitCurvStruct.h"
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
    CurvStruct e_k;
    CurvStruct last;
    CurvStruct opt_curv;
    CurvStruct opt_struct_tmp;
    CurvStruct r1;
    CurvStruct r5;
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
        int db_loop_ub;
        int i44;
        int mb_loop_ub;
        int pb_loop_ub;
        int q_loop_ub;
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
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        q_loop_ub = ctx->cfg.maskCart.size[1];
        if (0 <= q_loop_ub - 1) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[q_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        db_loop_ub = ctx->cfg.maskRot.size[1];
        if (0 <= db_loop_ub - 1) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[db_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        mb_loop_ub = ctx->cfg.indCart.size[0];
        for (int i36{0}; i36 < mb_loop_ub; i36++) {
            r.cfg.indCart[i36] = ctx->cfg.indCart.data[i36];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        pb_loop_ub = ctx->cfg.indRot.size[0];
        for (int i39{0}; i39 < pb_loop_ub; i39++) {
            r.cfg.indRot[i39] = ctx->cfg.indRot.data[i39];
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
        i44 = static_cast<int>(N - 1U);
        for (int k{0}; k < i44; k++) {
            double absx;
            double b_n;
            double c;
            double x;
            int i49;
            signed char n;
            // 'CheckCurvStructs:9' Curv1 = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k + 1U, &Curv1);
            // 'CheckCurvStructs:10' Curv2 = ctx.q_gcode.get(k+1);
            ctx->q_gcode.get(k - 4294967294U, &Curv2);
            // 'CheckCurvStructs:12' [~, r0D1] = EvalCurvStruct( ctx, Curv1, 1 );
            b_EvalCurvStruct(&r.q_spline, r.cfg.maskTot.data, r.cfg.maskTot.size,
                             r.cfg.maskCart.data, r.cfg.maskCart.size, r.cfg.maskRot.data,
                             r.cfg.maskRot.size, r.cfg.indCart, r.cfg.indRot, r.cfg.NumberAxis,
                             r.cfg.NCart, r.cfg.NRot, &Curv1, a__1, r0D1);
            // 'CheckCurvStructs:13' [~, r1D1] = EvalCurvStruct( ctx, Curv2, 0 );
            c_EvalCurvStruct(&r.q_spline, r.cfg.maskTot.data, r.cfg.maskTot.size,
                             r.cfg.maskCart.data, r.cfg.maskCart.size, r.cfg.maskRot.data,
                             r.cfg.maskRot.size, r.cfg.indCart, r.cfg.indRot, r.cfg.NumberAxis,
                             r.cfg.NCart, r.cfg.NRot, &Curv2, a__2, r1D1);
            // 'CheckCurvStructs:15' if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
            // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
            c = 0.0;
            i49 = r0D1.size(0);
            if (r0D1.size(0) >= 1) {
                for (int b_k{0}; b_k < i49; b_k++) {
                    c += r0D1[b_k] * r1D1[b_k];
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
            int ae_loop_ub;
            int bd_loop_ub;
            int cc_loop_ub;
            int cg_loop_ub;
            int df_loop_ub;
            int e_loop_ub;
            int fb_loop_ub;
            int gc_loop_ub;
            int hf_loop_ub;
            int ie_loop_ub;
            int jd_loop_ub;
            int kc_loop_ub;
            int lf_loop_ub;
            int m_loop_ub;
            int ob_loop_ub;
            int oc_loop_ub;
            int pf_loop_ub;
            int qe_loop_ub;
            int rd_loop_ub;
            int sc_loop_ub;
            int tb_loop_ub;
            int tf_loop_ub;
            int ue_loop_ub;
            int v_loop_ub;
            int wc_loop_ub;
            int xb_loop_ub;
            int xf_loop_ub;
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
            m_loop_ub = ctx->BasisValD.size(1);
            for (int i13{0}; i13 < m_loop_ub; i13++) {
                int u_loop_ub;
                u_loop_ub = ctx->BasisValD.size(0);
                for (int i20{0}; i20 < u_loop_ub; i20++) {
                    r.BasisValD[i20 + r.BasisValD.size(0) * i13] =
                        ctx->BasisValD[i20 + ctx->BasisValD.size(0) * i13];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            v_loop_ub = ctx->BasisValDD.size(1);
            for (int i21{0}; i21 < v_loop_ub; i21++) {
                int eb_loop_ub;
                eb_loop_ub = ctx->BasisValDD.size(0);
                for (int i28{0}; i28 < eb_loop_ub; i28++) {
                    r.BasisValDD[i28 + r.BasisValDD.size(0) * i21] =
                        ctx->BasisValDD[i28 + ctx->BasisValDD.size(0) * i21];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            fb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i29{0}; i29 < fb_loop_ub; i29++) {
                int nb_loop_ub;
                nb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i37{0}; i37 < nb_loop_ub; i37++) {
                    r.BasisValDDD[i37 + r.BasisValDDD.size(0) * i29] =
                        ctx->BasisValDDD[i37 + ctx->BasisValDDD.size(0) * i29];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            ob_loop_ub = ctx->BasisIntegr.size(0);
            for (int i38{0}; i38 < ob_loop_ub; i38++) {
                r.BasisIntegr[i38] = ctx->BasisIntegr[i38];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            tb_loop_ub = ctx->u_vec.size(1);
            for (int i43{0}; i43 < tb_loop_ub; i43++) {
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
            xb_loop_ub = ctx->cfg.maskTot.size[1];
            if (0 <= xb_loop_ub - 1) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[xb_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            cc_loop_ub = ctx->cfg.maskCart.size[1];
            if (0 <= cc_loop_ub - 1) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[cc_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            gc_loop_ub = ctx->cfg.maskRot.size[1];
            if (0 <= gc_loop_ub - 1) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[gc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            kc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i48{0}; i48 < kc_loop_ub; i48++) {
                r.cfg.indCart[i48] = ctx->cfg.indCart.data[i48];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            oc_loop_ub = ctx->cfg.indRot.size[0];
            for (int i53{0}; i53 < oc_loop_ub; i53++) {
                r.cfg.indRot[i53] = ctx->cfg.indRot.data[i53];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            sc_loop_ub = ctx->cfg.D.size[0];
            for (int i57{0}; i57 < sc_loop_ub; i57++) {
                r.cfg.D[i57] = ctx->cfg.D.data[i57];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            wc_loop_ub = ctx->cfg.kin_params.size[0];
            if (0 <= wc_loop_ub - 1) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[wc_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i61{0}; i61 < 5; i61++) {
                r.cfg.kin_type[i61] = ctx->cfg.kin_type[i61];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i65{0}; i65 < 6; i65++) {
                r.cfg.vmax[i65] = ctx->cfg.vmax[i65];
                r.cfg.amax[i65] = ctx->cfg.amax[i65];
                r.cfg.jmax[i65] = ctx->cfg.jmax[i65];
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
            for (int i69{0}; i69 < 9; i69++) {
                r.cfg.LogFileName[i69] = ctx->cfg.LogFileName[i69];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            bd_loop_ub = ctx->Coeff.size(1);
            for (int i73{0}; i73 < bd_loop_ub; i73++) {
                int fd_loop_ub;
                fd_loop_ub = ctx->Coeff.size(0);
                for (int i77{0}; i77 < fd_loop_ub; i77++) {
                    r.Coeff[i77 + r.Coeff.size(0) * i73] =
                        ctx->Coeff[i77 + ctx->Coeff.size(0) * i73];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            jd_loop_ub = r.BasisVal.size(1);
            for (int i81{0}; i81 < jd_loop_ub; i81++) {
                int pd_loop_ub;
                pd_loop_ub = r.BasisVal.size(0);
                for (int i87{0}; i87 < pd_loop_ub; i87++) {
                    ctx->BasisVal[i87 + ctx->BasisVal.size(0) * i81] =
                        r.BasisVal[i87 + r.BasisVal.size(0) * i81];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            rd_loop_ub = r.BasisValD.size(1);
            for (int i89{0}; i89 < rd_loop_ub; i89++) {
                int xd_loop_ub;
                xd_loop_ub = r.BasisValD.size(0);
                for (int i95{0}; i95 < xd_loop_ub; i95++) {
                    ctx->BasisValD[i95 + ctx->BasisValD.size(0) * i89] =
                        r.BasisValD[i95 + r.BasisValD.size(0) * i89];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            ae_loop_ub = r.BasisValDD.size(1);
            for (int i97{0}; i97 < ae_loop_ub; i97++) {
                int ge_loop_ub;
                ge_loop_ub = r.BasisValDD.size(0);
                for (int i103{0}; i103 < ge_loop_ub; i103++) {
                    ctx->BasisValDD[i103 + ctx->BasisValDD.size(0) * i97] =
                        r.BasisValDD[i103 + r.BasisValDD.size(0) * i97];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            ie_loop_ub = r.BasisValDDD.size(1);
            for (int i105{0}; i105 < ie_loop_ub; i105++) {
                int oe_loop_ub;
                oe_loop_ub = r.BasisValDDD.size(0);
                for (int i111{0}; i111 < oe_loop_ub; i111++) {
                    ctx->BasisValDDD[i111 + ctx->BasisValDDD.size(0) * i105] =
                        r.BasisValDDD[i111 + r.BasisValDDD.size(0) * i105];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            qe_loop_ub = r.BasisIntegr.size(0);
            for (int i114{0}; i114 < qe_loop_ub; i114++) {
                ctx->BasisIntegr[i114] = r.BasisIntegr[i114];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            ue_loop_ub = r.u_vec.size(1);
            for (int i118{0}; i118 < ue_loop_ub; i118++) {
                ctx->u_vec[i118] = r.u_vec[i118];
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
            ye_loop_ub = r.cfg.maskTot.size[1];
            if (0 <= ye_loop_ub - 1) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ye_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            df_loop_ub = r.cfg.maskCart.size[1];
            if (0 <= df_loop_ub - 1) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[df_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            hf_loop_ub = r.cfg.maskRot.size[1];
            if (0 <= hf_loop_ub - 1) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[hf_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            lf_loop_ub = r.cfg.indCart.size(0);
            for (int i122{0}; i122 < lf_loop_ub; i122++) {
                ctx->cfg.indCart.data[i122] = r.cfg.indCart[i122];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            pf_loop_ub = r.cfg.indRot.size(0);
            for (int i126{0}; i126 < pf_loop_ub; i126++) {
                ctx->cfg.indRot.data[i126] = r.cfg.indRot[i126];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            tf_loop_ub = r.cfg.D.size(0);
            for (int i130{0}; i130 < tf_loop_ub; i130++) {
                ctx->cfg.D.data[i130] = r.cfg.D[i130];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            xf_loop_ub = r.cfg.kin_params.size[0];
            if (0 <= xf_loop_ub - 1) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[xf_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i134{0}; i134 < 5; i134++) {
                ctx->cfg.kin_type[i134] = r.cfg.kin_type[i134];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i138{0}; i138 < 6; i138++) {
                ctx->cfg.vmax[i138] = r.cfg.vmax[i138];
                ctx->cfg.amax[i138] = r.cfg.amax[i138];
                ctx->cfg.jmax[i138] = r.cfg.jmax[i138];
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
            for (int i142{0}; i142 < 9; i142++) {
                ctx->cfg.LogFileName[i142] = r.cfg.LogFileName[i142];
            }
            ctx->errcode = r.errcode;
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            cg_loop_ub = r.Coeff.size(1);
            for (int i146{0}; i146 < cg_loop_ub; i146++) {
                int gg_loop_ub;
                gg_loop_ub = r.Coeff.size(0);
                for (int i150{0}; i150 < gg_loop_ub; i150++) {
                    ctx->Coeff[i150 + ctx->Coeff.size(0) * i146] =
                        r.Coeff[i150 + r.Coeff.size(0) * i146];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        // 'FeedoptPlan:73' ctx.q_compress.size
        ctx->q_compress.b_size();
        //          if( ctx.q_compress.size > 1 )
        //              error( "should be only compressing");
        //          end
        // 'FeedoptPlan:78' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:79' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int ab_loop_ub;
        int af_loop_ub;
        int dc_loop_ub;
        int de_loop_ub;
        int ef_loop_ub;
        int gd_loop_ub;
        int hc_loop_ub;
        int i_loop_ub;
        int if_loop_ub;
        int jb_loop_ub;
        int lc_loop_ub;
        int le_loop_ub;
        int loop_ub;
        int md_loop_ub;
        int mf_loop_ub;
        int pc_loop_ub;
        int qb_loop_ub;
        int qf_loop_ub;
        int r_loop_ub;
        int re_loop_ub;
        int tc_loop_ub;
        int ub_loop_ub;
        int ud_loop_ub;
        int uf_loop_ub;
        int ve_loop_ub;
        int xc_loop_ub;
        int yb_loop_ub;
        int yf_loop_ub;
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
            int n_loop_ub;
            n_loop_ub = ctx->BasisValD.size(0);
            for (int i14{0}; i14 < n_loop_ub; i14++) {
                r.BasisValD[i14 + r.BasisValD.size(0) * i9] =
                    ctx->BasisValD[i14 + ctx->BasisValD.size(0) * i9];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        r_loop_ub = ctx->BasisValDD.size(1);
        for (int i17{0}; i17 < r_loop_ub; i17++) {
            int w_loop_ub;
            w_loop_ub = ctx->BasisValDD.size(0);
            for (int i22{0}; i22 < w_loop_ub; i22++) {
                r.BasisValDD[i22 + r.BasisValDD.size(0) * i17] =
                    ctx->BasisValDD[i22 + ctx->BasisValDD.size(0) * i17];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        ab_loop_ub = ctx->BasisValDDD.size(1);
        for (int i25{0}; i25 < ab_loop_ub; i25++) {
            int gb_loop_ub;
            gb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i30{0}; i30 < gb_loop_ub; i30++) {
                r.BasisValDDD[i30 + r.BasisValDDD.size(0) * i25] =
                    ctx->BasisValDDD[i30 + ctx->BasisValDDD.size(0) * i25];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        jb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i33{0}; i33 < jb_loop_ub; i33++) {
            r.BasisIntegr[i33] = ctx->BasisIntegr[i33];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        qb_loop_ub = ctx->u_vec.size(1);
        for (int i40{0}; i40 < qb_loop_ub; i40++) {
            r.u_vec[i40] = ctx->u_vec[i40];
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
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        yb_loop_ub = ctx->cfg.maskCart.size[1];
        if (0 <= yb_loop_ub - 1) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[yb_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        dc_loop_ub = ctx->cfg.maskRot.size[1];
        if (0 <= dc_loop_ub - 1) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[dc_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        hc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i45{0}; i45 < hc_loop_ub; i45++) {
            r.cfg.indCart[i45] = ctx->cfg.indCart.data[i45];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        lc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i50{0}; i50 < lc_loop_ub; i50++) {
            r.cfg.indRot[i50] = ctx->cfg.indRot.data[i50];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        pc_loop_ub = ctx->cfg.D.size[0];
        for (int i54{0}; i54 < pc_loop_ub; i54++) {
            r.cfg.D[i54] = ctx->cfg.D.data[i54];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        tc_loop_ub = ctx->cfg.kin_params.size[0];
        if (0 <= tc_loop_ub - 1) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[tc_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i58{0}; i58 < 5; i58++) {
            r.cfg.kin_type[i58] = ctx->cfg.kin_type[i58];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i62{0}; i62 < 6; i62++) {
            r.cfg.vmax[i62] = ctx->cfg.vmax[i62];
            r.cfg.amax[i62] = ctx->cfg.amax[i62];
            r.cfg.jmax[i62] = ctx->cfg.jmax[i62];
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
        for (int i66{0}; i66 < 9; i66++) {
            r.cfg.LogFileName[i66] = ctx->cfg.LogFileName[i66];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        xc_loop_ub = ctx->Coeff.size(1);
        for (int i70{0}; i70 < xc_loop_ub; i70++) {
            int cd_loop_ub;
            cd_loop_ub = ctx->Coeff.size(0);
            for (int i74{0}; i74 < cd_loop_ub; i74++) {
                r.Coeff[i74 + r.Coeff.size(0) * i70] = ctx->Coeff[i74 + ctx->Coeff.size(0) * i70];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        smoothCurvStructs(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        gd_loop_ub = r.BasisVal.size(1);
        for (int i78{0}; i78 < gd_loop_ub; i78++) {
            int kd_loop_ub;
            kd_loop_ub = r.BasisVal.size(0);
            for (int i82{0}; i82 < kd_loop_ub; i82++) {
                ctx->BasisVal[i82 + ctx->BasisVal.size(0) * i78] =
                    r.BasisVal[i82 + r.BasisVal.size(0) * i78];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        md_loop_ub = r.BasisValD.size(1);
        for (int i84{0}; i84 < md_loop_ub; i84++) {
            int sd_loop_ub;
            sd_loop_ub = r.BasisValD.size(0);
            for (int i90{0}; i90 < sd_loop_ub; i90++) {
                ctx->BasisValD[i90 + ctx->BasisValD.size(0) * i84] =
                    r.BasisValD[i90 + r.BasisValD.size(0) * i84];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        ud_loop_ub = r.BasisValDD.size(1);
        for (int i92{0}; i92 < ud_loop_ub; i92++) {
            int be_loop_ub;
            be_loop_ub = r.BasisValDD.size(0);
            for (int i98{0}; i98 < be_loop_ub; i98++) {
                ctx->BasisValDD[i98 + ctx->BasisValDD.size(0) * i92] =
                    r.BasisValDD[i98 + r.BasisValDD.size(0) * i92];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        de_loop_ub = r.BasisValDDD.size(1);
        for (int i100{0}; i100 < de_loop_ub; i100++) {
            int je_loop_ub;
            je_loop_ub = r.BasisValDDD.size(0);
            for (int i106{0}; i106 < je_loop_ub; i106++) {
                ctx->BasisValDDD[i106 + ctx->BasisValDDD.size(0) * i100] =
                    r.BasisValDDD[i106 + r.BasisValDDD.size(0) * i100];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        le_loop_ub = r.BasisIntegr.size(0);
        for (int i108{0}; i108 < le_loop_ub; i108++) {
            ctx->BasisIntegr[i108] = r.BasisIntegr[i108];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        re_loop_ub = r.u_vec.size(1);
        for (int i115{0}; i115 < re_loop_ub; i115++) {
            ctx->u_vec[i115] = r.u_vec[i115];
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
        ve_loop_ub = r.cfg.maskTot.size[1];
        if (0 <= ve_loop_ub - 1) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ve_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        af_loop_ub = r.cfg.maskCart.size[1];
        if (0 <= af_loop_ub - 1) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[af_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        ef_loop_ub = r.cfg.maskRot.size[1];
        if (0 <= ef_loop_ub - 1) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[ef_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        if_loop_ub = r.cfg.indCart.size(0);
        for (int i119{0}; i119 < if_loop_ub; i119++) {
            ctx->cfg.indCart.data[i119] = r.cfg.indCart[i119];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        mf_loop_ub = r.cfg.indRot.size(0);
        for (int i123{0}; i123 < mf_loop_ub; i123++) {
            ctx->cfg.indRot.data[i123] = r.cfg.indRot[i123];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        qf_loop_ub = r.cfg.D.size(0);
        for (int i127{0}; i127 < qf_loop_ub; i127++) {
            ctx->cfg.D.data[i127] = r.cfg.D[i127];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        uf_loop_ub = r.cfg.kin_params.size[0];
        if (0 <= uf_loop_ub - 1) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[uf_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i131{0}; i131 < 5; i131++) {
            ctx->cfg.kin_type[i131] = r.cfg.kin_type[i131];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i135{0}; i135 < 6; i135++) {
            ctx->cfg.vmax[i135] = r.cfg.vmax[i135];
            ctx->cfg.amax[i135] = r.cfg.amax[i135];
            ctx->cfg.jmax[i135] = r.cfg.jmax[i135];
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
        for (int i139{0}; i139 < 9; i139++) {
            ctx->cfg.LogFileName[i139] = r.cfg.LogFileName[i139];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        yf_loop_ub = r.Coeff.size(1);
        for (int i143{0}; i143 < yf_loop_ub; i143++) {
            int dg_loop_ub;
            dg_loop_ub = r.Coeff.size(0);
            for (int i147{0}; i147 < dg_loop_ub; i147++) {
                ctx->Coeff[i147 + ctx->Coeff.size(0) * i143] =
                    r.Coeff[i147 + r.Coeff.size(0) * i143];
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
        int bb_loop_ub;
        int bg_loop_ub;
        int cf_loop_ub;
        int ec_loop_ub;
        int gf_loop_ub;
        int he_loop_ub;
        int ic_loop_ub;
        int id_loop_ub;
        int j_loop_ub;
        int kb_loop_ub;
        int kf_loop_ub;
        int mc_loop_ub;
        int of_loop_ub;
        int pe_loop_ub;
        int qc_loop_ub;
        int qd_loop_ub;
        int rb_loop_ub;
        int s_loop_ub;
        int sf_loop_ub;
        int te_loop_ub;
        int uc_loop_ub;
        int vb_loop_ub;
        int wf_loop_ub;
        int xe_loop_ub;
        int yc_loop_ub;
        int yd_loop_ub;
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
            int o_loop_ub;
            o_loop_ub = ctx->BasisValD.size(0);
            for (int i15{0}; i15 < o_loop_ub; i15++) {
                r.BasisValD[i15 + r.BasisValD.size(0) * i10] =
                    ctx->BasisValD[i15 + ctx->BasisValD.size(0) * i10];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        s_loop_ub = ctx->BasisValDD.size(1);
        for (int i18{0}; i18 < s_loop_ub; i18++) {
            int x_loop_ub;
            x_loop_ub = ctx->BasisValDD.size(0);
            for (int i23{0}; i23 < x_loop_ub; i23++) {
                r.BasisValDD[i23 + r.BasisValDD.size(0) * i18] =
                    ctx->BasisValDD[i23 + ctx->BasisValDD.size(0) * i18];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        bb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i26{0}; i26 < bb_loop_ub; i26++) {
            int hb_loop_ub;
            hb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i31{0}; i31 < hb_loop_ub; i31++) {
                r.BasisValDDD[i31 + r.BasisValDDD.size(0) * i26] =
                    ctx->BasisValDDD[i31 + ctx->BasisValDDD.size(0) * i26];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        kb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i34{0}; i34 < kb_loop_ub; i34++) {
            r.BasisIntegr[i34] = ctx->BasisIntegr[i34];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        rb_loop_ub = ctx->u_vec.size(1);
        for (int i41{0}; i41 < rb_loop_ub; i41++) {
            r.u_vec[i41] = ctx->u_vec[i41];
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
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        ac_loop_ub = ctx->cfg.maskCart.size[1];
        if (0 <= ac_loop_ub - 1) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[ac_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        ec_loop_ub = ctx->cfg.maskRot.size[1];
        if (0 <= ec_loop_ub - 1) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[ec_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ic_loop_ub = ctx->cfg.indCart.size[0];
        for (int i46{0}; i46 < ic_loop_ub; i46++) {
            r.cfg.indCart[i46] = ctx->cfg.indCart.data[i46];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        mc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i51{0}; i51 < mc_loop_ub; i51++) {
            r.cfg.indRot[i51] = ctx->cfg.indRot.data[i51];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        qc_loop_ub = ctx->cfg.D.size[0];
        for (int i55{0}; i55 < qc_loop_ub; i55++) {
            r.cfg.D[i55] = ctx->cfg.D.data[i55];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        uc_loop_ub = ctx->cfg.kin_params.size[0];
        if (0 <= uc_loop_ub - 1) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[uc_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i59{0}; i59 < 5; i59++) {
            r.cfg.kin_type[i59] = ctx->cfg.kin_type[i59];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i63{0}; i63 < 6; i63++) {
            r.cfg.vmax[i63] = ctx->cfg.vmax[i63];
            r.cfg.amax[i63] = ctx->cfg.amax[i63];
            r.cfg.jmax[i63] = ctx->cfg.jmax[i63];
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
        for (int i67{0}; i67 < 9; i67++) {
            r.cfg.LogFileName[i67] = ctx->cfg.LogFileName[i67];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        yc_loop_ub = ctx->Coeff.size(1);
        for (int i71{0}; i71 < yc_loop_ub; i71++) {
            int dd_loop_ub;
            dd_loop_ub = ctx->Coeff.size(0);
            for (int i75{0}; i75 < dd_loop_ub; i75++) {
                r.Coeff[i75 + r.Coeff.size(0) * i71] = ctx->Coeff[i75 + ctx->Coeff.size(0) * i71];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        // 'splitQueue:3' if ctx.q_smooth.isempty()
        if (!ctx->q_smooth.isempty()) {
            unsigned int b_N;
            unsigned int c_N;
            int i113;
            // 'splitQueue:5' DebugLog( DebugCfg.Validate,        'Splitting...\n' );
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf( 1, varargin{:} );
                printf("Splitting...\n");
                fflush(stdout);
            }
            // 'splitQueue:6' DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf( 1, varargin{:} );
                printf("Splitting...\n");
                fflush(stdout);
            }
            // 'splitQueue:9' N = ctx.q_smooth.size;
            b_N = ctx->q_smooth.size();
            // 'splitQueue:11' for k = 1 : N
            i113 = static_cast<int>(b_N);
            for (int c_k{0}; c_k < i113; c_k++) {
                // 'splitQueue:12' ctx = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
                r.q_smooth.get(c_k + 1U, &r1);
                splitCurvStruct(&r, &r1);
            }
            // 'splitQueue:15' checkZSpdmode( ctx.q_split );
            // 'splitQueue:20' N = queue.size;
            c_N = r.q_split.size();
            // 'splitQueue:22' curv = queue.get( 1 );
            r.q_split.get(&r5);
            // 'splitQueue:24' for k = 2 : N
            for (unsigned int d_k{2U}; d_k <= c_N; d_k++) {
                // 'splitQueue:25' curvNext = queue.get( k );
                r.q_split.get(d_k, &e_k);
                // 'splitQueue:27' if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
                // 'splitQueue:28'        ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
                // 'splitQueue:32' curv = curvNext;
            }
        }
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        id_loop_ub = r.BasisVal.size(1);
        for (int i80{0}; i80 < id_loop_ub; i80++) {
            int od_loop_ub;
            od_loop_ub = r.BasisVal.size(0);
            for (int i86{0}; i86 < od_loop_ub; i86++) {
                ctx->BasisVal[i86 + ctx->BasisVal.size(0) * i80] =
                    r.BasisVal[i86 + r.BasisVal.size(0) * i80];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        qd_loop_ub = r.BasisValD.size(1);
        for (int i88{0}; i88 < qd_loop_ub; i88++) {
            int wd_loop_ub;
            wd_loop_ub = r.BasisValD.size(0);
            for (int i94{0}; i94 < wd_loop_ub; i94++) {
                ctx->BasisValD[i94 + ctx->BasisValD.size(0) * i88] =
                    r.BasisValD[i94 + r.BasisValD.size(0) * i88];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        yd_loop_ub = r.BasisValDD.size(1);
        for (int i96{0}; i96 < yd_loop_ub; i96++) {
            int fe_loop_ub;
            fe_loop_ub = r.BasisValDD.size(0);
            for (int i102{0}; i102 < fe_loop_ub; i102++) {
                ctx->BasisValDD[i102 + ctx->BasisValDD.size(0) * i96] =
                    r.BasisValDD[i102 + r.BasisValDD.size(0) * i96];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        he_loop_ub = r.BasisValDDD.size(1);
        for (int i104{0}; i104 < he_loop_ub; i104++) {
            int ne_loop_ub;
            ne_loop_ub = r.BasisValDDD.size(0);
            for (int i110{0}; i110 < ne_loop_ub; i110++) {
                ctx->BasisValDDD[i110 + ctx->BasisValDDD.size(0) * i104] =
                    r.BasisValDDD[i110 + r.BasisValDDD.size(0) * i104];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        pe_loop_ub = r.BasisIntegr.size(0);
        for (int i112{0}; i112 < pe_loop_ub; i112++) {
            ctx->BasisIntegr[i112] = r.BasisIntegr[i112];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        te_loop_ub = r.u_vec.size(1);
        for (int i117{0}; i117 < te_loop_ub; i117++) {
            ctx->u_vec[i117] = r.u_vec[i117];
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
        xe_loop_ub = r.cfg.maskTot.size[1];
        if (0 <= xe_loop_ub - 1) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[xe_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        cf_loop_ub = r.cfg.maskCart.size[1];
        if (0 <= cf_loop_ub - 1) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[cf_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        gf_loop_ub = r.cfg.maskRot.size[1];
        if (0 <= gf_loop_ub - 1) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[gf_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        kf_loop_ub = r.cfg.indCart.size(0);
        for (int i121{0}; i121 < kf_loop_ub; i121++) {
            ctx->cfg.indCart.data[i121] = r.cfg.indCart[i121];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        of_loop_ub = r.cfg.indRot.size(0);
        for (int i125{0}; i125 < of_loop_ub; i125++) {
            ctx->cfg.indRot.data[i125] = r.cfg.indRot[i125];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        sf_loop_ub = r.cfg.D.size(0);
        for (int i129{0}; i129 < sf_loop_ub; i129++) {
            ctx->cfg.D.data[i129] = r.cfg.D[i129];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        wf_loop_ub = r.cfg.kin_params.size[0];
        if (0 <= wf_loop_ub - 1) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[wf_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i133{0}; i133 < 5; i133++) {
            ctx->cfg.kin_type[i133] = r.cfg.kin_type[i133];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i137{0}; i137 < 6; i137++) {
            ctx->cfg.vmax[i137] = r.cfg.vmax[i137];
            ctx->cfg.amax[i137] = r.cfg.amax[i137];
            ctx->cfg.jmax[i137] = r.cfg.jmax[i137];
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
        for (int h_i{0}; h_i < 5; h_i++) {
            ctx->cfg.GaussLegendreX[h_i] = r.cfg.GaussLegendreX[h_i];
            ctx->cfg.GaussLegendreW[h_i] = r.cfg.GaussLegendreW[h_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i141{0}; i141 < 9; i141++) {
            ctx->cfg.LogFileName[i141] = r.cfg.LogFileName[i141];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        bg_loop_ub = r.Coeff.size(1);
        for (int i145{0}; i145 < bg_loop_ub; i145++) {
            int fg_loop_ub;
            fg_loop_ub = r.Coeff.size(0);
            for (int i149{0}; i149 < fg_loop_ub; i149++) {
                ctx->Coeff[i149 + ctx->Coeff.size(0) * i145] =
                    r.Coeff[i149 + r.Coeff.size(0) * i145];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:88' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:89' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
    } break;
    case Fopt_Opt: {
        int ad_loop_ub;
        int ag_loop_ub;
        int bc_loop_ub;
        int bf_loop_ub;
        int c_loop_ub;
        int cb_loop_ub;
        int ee_loop_ub;
        int fc_loop_ub;
        int ff_loop_ub;
        int hd_loop_ub;
        int jc_loop_ub;
        int jf_loop_ub;
        int k_loop_ub;
        int lb_loop_ub;
        int me_loop_ub;
        int nc_loop_ub;
        int nd_loop_ub;
        int nf_loop_ub;
        int rc_loop_ub;
        int rf_loop_ub;
        int sb_loop_ub;
        int se_loop_ub;
        int t_loop_ub;
        int vc_loop_ub;
        int vd_loop_ub;
        int vf_loop_ub;
        int wb_loop_ub;
        int we_loop_ub;
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
            int p_loop_ub;
            p_loop_ub = ctx->BasisValD.size(0);
            for (int i16{0}; i16 < p_loop_ub; i16++) {
                b_ctx.BasisValD[i16 + b_ctx.BasisValD.size(0) * i11] =
                    ctx->BasisValD[i16 + ctx->BasisValD.size(0) * i11];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        t_loop_ub = ctx->BasisValDD.size(1);
        for (int i19{0}; i19 < t_loop_ub; i19++) {
            int y_loop_ub;
            y_loop_ub = ctx->BasisValDD.size(0);
            for (int i24{0}; i24 < y_loop_ub; i24++) {
                b_ctx.BasisValDD[i24 + b_ctx.BasisValDD.size(0) * i19] =
                    ctx->BasisValDD[i24 + ctx->BasisValDD.size(0) * i19];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        cb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i27{0}; i27 < cb_loop_ub; i27++) {
            int ib_loop_ub;
            ib_loop_ub = ctx->BasisValDDD.size(0);
            for (int i32{0}; i32 < ib_loop_ub; i32++) {
                b_ctx.BasisValDDD[i32 + b_ctx.BasisValDDD.size(0) * i27] =
                    ctx->BasisValDDD[i32 + ctx->BasisValDDD.size(0) * i27];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        lb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i35{0}; i35 < lb_loop_ub; i35++) {
            b_ctx.BasisIntegr[i35] = ctx->BasisIntegr[i35];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        sb_loop_ub = ctx->u_vec.size(1);
        for (int i42{0}; i42 < sb_loop_ub; i42++) {
            b_ctx.u_vec[i42] = ctx->u_vec[i42];
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
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        bc_loop_ub = ctx->cfg.maskCart.size[1];
        if (0 <= bc_loop_ub - 1) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[bc_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        fc_loop_ub = ctx->cfg.maskRot.size[1];
        if (0 <= fc_loop_ub - 1) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[fc_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        jc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i47{0}; i47 < jc_loop_ub; i47++) {
            b_ctx.cfg.indCart[i47] = ctx->cfg.indCart.data[i47];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        nc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i52{0}; i52 < nc_loop_ub; i52++) {
            b_ctx.cfg.indRot[i52] = ctx->cfg.indRot.data[i52];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.D.set_size(ctx->cfg.D.size[0]);
        rc_loop_ub = ctx->cfg.D.size[0];
        for (int i56{0}; i56 < rc_loop_ub; i56++) {
            b_ctx.cfg.D[i56] = ctx->cfg.D.data[i56];
        }
        b_ctx.cfg.coeffD = ctx->cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        vc_loop_ub = ctx->cfg.kin_params.size[0];
        if (0 <= vc_loop_ub - 1) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[vc_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i60{0}; i60 < 5; i60++) {
            b_ctx.cfg.kin_type[i60] = ctx->cfg.kin_type[i60];
        }
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        b_ctx.cfg.fmax = ctx->cfg.fmax;
        b_ctx.cfg.smax = ctx->cfg.smax;
        for (int i64{0}; i64 < 6; i64++) {
            b_ctx.cfg.vmax[i64] = ctx->cfg.vmax[i64];
            b_ctx.cfg.amax[i64] = ctx->cfg.amax[i64];
            b_ctx.cfg.jmax[i64] = ctx->cfg.jmax[i64];
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
        for (int i68{0}; i68 < 9; i68++) {
            b_ctx.cfg.LogFileName[i68] = ctx->cfg.LogFileName[i68];
        }
        b_ctx.errcode = ctx->errcode;
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        ad_loop_ub = ctx->Coeff.size(1);
        for (int i72{0}; i72 < ad_loop_ub; i72++) {
            int ed_loop_ub;
            ed_loop_ub = ctx->Coeff.size(0);
            for (int i76{0}; i76 < ed_loop_ub; i76++) {
                b_ctx.Coeff[i76 + b_ctx.Coeff.size(0) * i72] =
                    ctx->Coeff[i76 + ctx->Coeff.size(0) * i72];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        feedratePlanning(&b_ctx, &c_optimized, &opt_curv, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        hd_loop_ub = b_ctx.BasisVal.size(1);
        for (int i79{0}; i79 < hd_loop_ub; i79++) {
            int ld_loop_ub;
            ld_loop_ub = b_ctx.BasisVal.size(0);
            for (int i83{0}; i83 < ld_loop_ub; i83++) {
                ctx->BasisVal[i83 + ctx->BasisVal.size(0) * i79] =
                    b_ctx.BasisVal[i83 + b_ctx.BasisVal.size(0) * i79];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        nd_loop_ub = b_ctx.BasisValD.size(1);
        for (int i85{0}; i85 < nd_loop_ub; i85++) {
            int td_loop_ub;
            td_loop_ub = b_ctx.BasisValD.size(0);
            for (int i91{0}; i91 < td_loop_ub; i91++) {
                ctx->BasisValD[i91 + ctx->BasisValD.size(0) * i85] =
                    b_ctx.BasisValD[i91 + b_ctx.BasisValD.size(0) * i85];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        vd_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i93{0}; i93 < vd_loop_ub; i93++) {
            int ce_loop_ub;
            ce_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i99{0}; i99 < ce_loop_ub; i99++) {
                ctx->BasisValDD[i99 + ctx->BasisValDD.size(0) * i93] =
                    b_ctx.BasisValDD[i99 + b_ctx.BasisValDD.size(0) * i93];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        ee_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i101{0}; i101 < ee_loop_ub; i101++) {
            int ke_loop_ub;
            ke_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i107{0}; i107 < ke_loop_ub; i107++) {
                ctx->BasisValDDD[i107 + ctx->BasisValDDD.size(0) * i101] =
                    b_ctx.BasisValDDD[i107 + b_ctx.BasisValDDD.size(0) * i101];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        me_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i109{0}; i109 < me_loop_ub; i109++) {
            ctx->BasisIntegr[i109] = b_ctx.BasisIntegr[i109];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        se_loop_ub = b_ctx.u_vec.size(1);
        for (int i116{0}; i116 < se_loop_ub; i116++) {
            ctx->u_vec[i116] = b_ctx.u_vec[i116];
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
        we_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (0 <= we_loop_ub - 1) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[we_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        bf_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (0 <= bf_loop_ub - 1) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[bf_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        ff_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (0 <= ff_loop_ub - 1) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[ff_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        jf_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i120{0}; i120 < jf_loop_ub; i120++) {
            ctx->cfg.indCart.data[i120] = b_ctx.cfg.indCart[i120];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        nf_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i124{0}; i124 < nf_loop_ub; i124++) {
            ctx->cfg.indRot.data[i124] = b_ctx.cfg.indRot[i124];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        rf_loop_ub = b_ctx.cfg.D.size(0);
        for (int i128{0}; i128 < rf_loop_ub; i128++) {
            ctx->cfg.D.data[i128] = b_ctx.cfg.D[i128];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        vf_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (0 <= vf_loop_ub - 1) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[vf_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i132{0}; i132 < 5; i132++) {
            ctx->cfg.kin_type[i132] = b_ctx.cfg.kin_type[i132];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        ctx->cfg.fmax = b_ctx.cfg.fmax;
        ctx->cfg.smax = b_ctx.cfg.smax;
        for (int i136{0}; i136 < 6; i136++) {
            ctx->cfg.vmax[i136] = b_ctx.cfg.vmax[i136];
            ctx->cfg.amax[i136] = b_ctx.cfg.amax[i136];
            ctx->cfg.jmax[i136] = b_ctx.cfg.jmax[i136];
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
        for (int g_i{0}; g_i < 5; g_i++) {
            ctx->cfg.GaussLegendreX[g_i] = b_ctx.cfg.GaussLegendreX[g_i];
            ctx->cfg.GaussLegendreW[g_i] = b_ctx.cfg.GaussLegendreW[g_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i140{0}; i140 < 9; i140++) {
            ctx->cfg.LogFileName[i140] = b_ctx.cfg.LogFileName[i140];
        }
        ctx->errcode = b_ctx.errcode;
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        ag_loop_ub = b_ctx.Coeff.size(1);
        for (int i144{0}; i144 < ag_loop_ub; i144++) {
            int eg_loop_ub;
            eg_loop_ub = b_ctx.Coeff.size(0);
            for (int i148{0}; i148 < eg_loop_ub; i148++) {
                ctx->Coeff[i148 + ctx->Coeff.size(0) * i144] =
                    b_ctx.Coeff[i148 + b_ctx.Coeff.size(0) * i144];
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
