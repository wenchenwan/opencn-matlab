//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:10:03
//

// Include Files
#include "FeedoptPlan.h"
#include "Kinematics.h"
#include "add_tool_offset.h"
#include "checkParametrisation.h"
#include "checkZSpdmode.h"
#include "compressCurvStructs.h"
#include "constrCurvStruct.h"
#include "feedratePlanning.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "smoothCurvStructs.h"
#include "splitQueue.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include "cpp_interp.hpp"
#include <algorithm>
#include <emmintrin.h>
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
    Axes params_tmp_tool_offset;
    CurvStruct b_CurvStruct;
    CurvStruct curv1;
    CurvStruct last;
    CurvStruct opt_struct_tmp;
    CurvStruct r1;
    SplineStruct params_tmp_spline;
    b_FeedoptContext b_ctx;
    b_FeedoptContext r;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double off[3];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_tool_backangle;
    double params_tmp_tool_diameter;
    double params_tmp_tool_frontangle;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_tool_orientation;
    int params_tmp_tool_pocketno;
    int params_tmp_tool_toolno;
    char b_cv[1025];
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
    if (ctx->errcode != FeedoptPlanError_Success) {
        char message[39];
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
        &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_tool_toolno, &params_tmp_tool_pocketno,
        &params_tmp_tool_offset, &params_tmp_tool_diameter, &params_tmp_tool_frontangle,
        &params_tmp_tool_backangle, &params_tmp_tool_orientation, &params_tmp_spline, params_tmp_R0,
        params_tmp_R1, params_tmp_Cprim, &expl_temp, params_tmp_evec, &b_expl_temp, &c_expl_temp,
        params_tmp_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
        params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
        params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
        params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
        params_tmp_gcodeInfoStruct_G91_1, params_tmp_tool_toolno, params_tmp_tool_pocketno,
        &params_tmp_tool_offset, params_tmp_tool_diameter, params_tmp_tool_frontangle,
        params_tmp_tool_backangle, params_tmp_tool_orientation, &params_tmp_spline, params_tmp_R0,
        params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &opt_struct_tmp);
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
        // 'ReadGCode:6' status      = int32(0);
        // 'ReadGCode:7' CurvStruct  = constrCurvStructType;
        // 'ReadGCode:9' if ( coder.target('mex') || coder.target('rtw') )
        // 'ReadGCode:10' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
        // 'ReadGCode:12' my_path = StructTypeName.WDIR + "/src";
        // 'ReadGCode:13' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'ReadGCode:15' pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
        //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
        // 'ReadGCode:17' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
        // 'ReadGCode:18' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path);
        // 'ReadGCode:19' coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
        // 'ReadGCode:20' coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc',
        // pathRs274Src); 'ReadGCode:21' coder.updateBuildInfo('addSourceFiles','interp_arc.cc',
        // pathRs274Src); 'ReadGCode:22' coder.updateBuildInfo('addSourceFiles','interp_array.cc',
        // pathRs274Src); 'ReadGCode:23' coder.updateBuildInfo('addSourceFiles','interp_base.cc',
        // pathRs274Src); 'ReadGCode:24' coder.updateBuildInfo('addSourceFiles','interp_check.cc',
        // pathRs274Src); 'ReadGCode:25' coder.updateBuildInfo('addSourceFiles','interp_convert.cc',
        // pathRs274Src); 'ReadGCode:26' coder.updateBuildInfo('addSourceFiles','interp_cycles.cc',
        // pathRs274Src); 'ReadGCode:27' coder.updateBuildInfo('addSourceFiles','interp_execute.cc',
        // pathRs274Src); 'ReadGCode:28' coder.updateBuildInfo('addSourceFiles','interp_find.cc',
        // pathRs274Src); 'ReadGCode:29'
        // coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
        // 'ReadGCode:30' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
        // 'ReadGCode:31' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
        // pathRs274Src); 'ReadGCode:32' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
        // pathRs274Src); 'ReadGCode:33' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
        // pathRs274Src); 'ReadGCode:34' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
        // pathRs274Src); 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
        // pathRs274Src); 'ReadGCode:36' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
        // pathRs274Src); 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
        // pathRs274Src); 'ReadGCode:38' coder.updateBuildInfo('addSourceFiles','ocn.cc',
        // pathRs274Src); 'ReadGCode:39' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc',
        // pathRs274Src); 'ReadGCode:40' coder.updateBuildInfo('addSourceFiles','inifile.cc',
        // pathRs274Src); 'ReadGCode:41' coder.updateBuildInfo('addLinkFlags', '-ldl');
        //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
        // 'ReadGCode:43' coder.cinclude('cpp_interp.hpp');
        // 'ReadGCode:45' switch cmd
        // 'ReadGCode:46' case ReadGCodeCmd.Load
        // 'ReadGCode:47' status = coder.ceval( 'cpp_interp_init', [filename 0] );
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
            __m128d r2;
            __m128d r3;
            __m128d r4;
            double prev_tool_offset_x;
            double prev_tool_offset_y;
            double prev_tool_offset_z;
            int b_status;
            int is_loaded;
            // 'FeedoptPlan:21' [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, ...
            // 'FeedoptPlan:22'                 ctx.cfg.source );
            //  coder.extrinsic('ReadGCode_mex');
            //  Wrapper for pulling the next gcode line from the interpreter
            // 'ReadGCode:6' status      = int32(0);
            // 'ReadGCode:7' CurvStruct  = constrCurvStructType;
            //  constrCurvStructType : Constructs a constrCurvStruct with default values.
            // 'constrCurvStructType:4' if( nargin > 0 )
            // 'constrCurvStructType:6' else
            // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
            // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
            // 'constrCurvStructType:12' else
            // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool,
            // ... 'constrCurvStructType:14'         params.spline, params.R0, params.R1,
            // params.Cprim, ... 'constrCurvStructType:15'         params.delta, params.evec,
            // params.theta, params.pitch, ... 'constrCurvStructType:16'         params.CoeffP5,
            // params.Coeff );
            b_CurvStruct = opt_struct_tmp;
            // 'ReadGCode:9' if ( coder.target('mex') || coder.target('rtw') )
            // 'ReadGCode:10' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
            // 'ReadGCode:12' my_path = StructTypeName.WDIR + "/src";
            // 'ReadGCode:13' coder.updateBuildInfo('addIncludePaths',my_path);
            // 'ReadGCode:15' pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
            //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
            // 'ReadGCode:17' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
            // 'ReadGCode:18' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path);
            // 'ReadGCode:19' coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
            // 'ReadGCode:20' coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc',
            // pathRs274Src); 'ReadGCode:21' coder.updateBuildInfo('addSourceFiles','interp_arc.cc',
            // pathRs274Src); 'ReadGCode:22'
            // coder.updateBuildInfo('addSourceFiles','interp_array.cc', pathRs274Src);
            // 'ReadGCode:23' coder.updateBuildInfo('addSourceFiles','interp_base.cc',
            // pathRs274Src); 'ReadGCode:24'
            // coder.updateBuildInfo('addSourceFiles','interp_check.cc', pathRs274Src);
            // 'ReadGCode:25' coder.updateBuildInfo('addSourceFiles','interp_convert.cc',
            // pathRs274Src); 'ReadGCode:26'
            // coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', pathRs274Src);
            // 'ReadGCode:27' coder.updateBuildInfo('addSourceFiles','interp_execute.cc',
            // pathRs274Src); 'ReadGCode:28'
            // coder.updateBuildInfo('addSourceFiles','interp_find.cc', pathRs274Src);
            // 'ReadGCode:29' coder.updateBuildInfo('addSourceFiles','interp_internal.cc',
            // pathRs274Src); 'ReadGCode:30'
            // coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
            // 'ReadGCode:31' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
            // pathRs274Src); 'ReadGCode:32'
            // coder.updateBuildInfo('addSourceFiles','interp_o_word.cc', pathRs274Src);
            // 'ReadGCode:33' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
            // pathRs274Src); 'ReadGCode:34'
            // coder.updateBuildInfo('addSourceFiles','interp_read.cc', pathRs274Src);
            // 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
            // pathRs274Src); 'ReadGCode:36'
            // coder.updateBuildInfo('addSourceFiles','interp_setup.cc', pathRs274Src);
            // 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
            // pathRs274Src); 'ReadGCode:38' coder.updateBuildInfo('addSourceFiles','ocn.cc',
            // pathRs274Src); 'ReadGCode:39'
            // coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
            // 'ReadGCode:40' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
            // 'ReadGCode:41' coder.updateBuildInfo('addLinkFlags', '-ldl');
            //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
            // 'ReadGCode:43' coder.cinclude('cpp_interp.hpp');
            // 'ReadGCode:45' switch cmd
            // 'ReadGCode:48' case ReadGCodeCmd.Read
            // 'ReadGCode:49' is_loaded = int32(0);
            // 'ReadGCode:50' is_loaded = coder.ceval( 'cpp_interp_loaded' );
            is_loaded = cpp_interp_loaded();
            // 'ReadGCode:51' if is_loaded
            if (is_loaded != 0) {
                // 'ReadGCode:52' status = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct )
                // );
                b_status = cpp_interp_read(&b_CurvStruct);
            } else {
                // 'ReadGCode:53' else
                // 'ReadGCode:54' status = int32(0);
                b_status = 0;
            }
            status = b_status;
            // 'FeedoptPlan:23' if( ctx.q_gcode.isempty )
            if (ctx->q_gcode.isempty()) {
                // 'FeedoptPlan:24' prev_tool = constrToolStructType;
                prev_tool_offset_x = 0.0;
                prev_tool_offset_y = 0.0;
                prev_tool_offset_z = 0.0;
            } else {
                bool isEqual;
                // 'FeedoptPlan:25' else
                // 'FeedoptPlan:26' prev_tool = ctx.q_gcode.rget(1).tool;
                ctx->q_gcode.rget(&r1);
                prev_tool_offset_x = r1.tool.offset.x;
                prev_tool_offset_y = r1.tool.offset.y;
                prev_tool_offset_z = r1.tool.offset.z;
                // 'FeedoptPlan:28' if( ~toolIsEqual(prev_tool, CurvStruct.tool ) )
                //  Check the tools are equals
                // 'toolIsEqual:3' isEqual = false;
                isEqual = false;
                // 'toolIsEqual:5' if( tool1.toolno        ~= tool2.toolno )
                if ((r1.tool.toolno == b_CurvStruct.tool.toolno) &&
                    (r1.tool.pocketno == b_CurvStruct.tool.pocketno) &&
                    (r1.tool.diameter == b_CurvStruct.tool.diameter) &&
                    (r1.tool.frontangle == b_CurvStruct.tool.frontangle) &&
                    (r1.tool.backangle == b_CurvStruct.tool.backangle) &&
                    (r1.tool.orientation == b_CurvStruct.tool.orientation) &&
                    (r1.tool.offset.x == b_CurvStruct.tool.offset.x) &&
                    (r1.tool.offset.y == b_CurvStruct.tool.offset.y) &&
                    (r1.tool.offset.z == b_CurvStruct.tool.offset.z) &&
                    (r1.tool.offset.a == b_CurvStruct.tool.offset.a) &&
                    (r1.tool.offset.b == b_CurvStruct.tool.offset.b) &&
                    (r1.tool.offset.c == b_CurvStruct.tool.offset.c) &&
                    (r1.tool.offset.u == b_CurvStruct.tool.offset.u) &&
                    (r1.tool.offset.v == b_CurvStruct.tool.offset.v) &&
                    (r1.tool.offset.w == b_CurvStruct.tool.offset.w)) {
                    // 'toolIsEqual:6' if( tool1.pocketno      ~= tool2.pocketno )
                    // 'toolIsEqual:7' if( tool1.diameter      ~= tool2.diameter )
                    // 'toolIsEqual:8' if( tool1.frontangle    ~= tool2.frontangle )
                    // 'toolIsEqual:9' if( tool1.backangle     ~= tool2.backangle )
                    // 'toolIsEqual:10' if( tool1.orientation   ~= tool2.orientation )
                    // 'toolIsEqual:11' if( tool1.offset.x      ~= tool2.offset.x )
                    // 'toolIsEqual:12' if( tool1.offset.y      ~= tool2.offset.y )
                    // 'toolIsEqual:13' if( tool1.offset.z      ~= tool2.offset.z )
                    // 'toolIsEqual:14' if( tool1.offset.a      ~= tool2.offset.a )
                    // 'toolIsEqual:15' if( tool1.offset.b      ~= tool2.offset.b )
                    // 'toolIsEqual:16' if( tool1.offset.c      ~= tool2.offset.c )
                    // 'toolIsEqual:17' if( tool1.offset.u      ~= tool2.offset.u )
                    // 'toolIsEqual:18' if( tool1.offset.v      ~= tool2.offset.v )
                    // 'toolIsEqual:19' if( tool1.offset.w      ~= tool2.offset.w )
                    // 'toolIsEqual:21' isEqual = true;
                    isEqual = true;
                }
                if (!isEqual) {
                    // 'FeedoptPlan:29' curv1 = ctx.q_gcode.rget(1);
                    ctx->q_gcode.rget(&curv1);
                    // 'FeedoptPlan:30' if( isAZeroStart(curv1) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((curv1.Info.zspdmode == ZSpdMode_ZN) ||
                        (curv1.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:6' zeroFlag = true;
                        // 'FeedoptPlan:31' curv1.Info.zspdmode = ZSpdMode.ZZ;
                        curv1.Info.zspdmode = ZSpdMode_ZZ;
                    } else {
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'FeedoptPlan:32' else
                        // 'FeedoptPlan:33' curv1.Info.zspdmode = ZSpdMode.NZ;
                        curv1.Info.zspdmode = ZSpdMode_NZ;
                    }
                    // 'FeedoptPlan:36' ctx.q_gcode.set(ctx.q_gcode.size, curv1);
                    ctx->q_gcode.set(ctx->q_gcode.size(), &curv1);
                    // 'FeedoptPlan:38' if( isAZeroEnd(CurvStruct) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((b_CurvStruct.Info.zspdmode == ZSpdMode_NZ) ||
                        (b_CurvStruct.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'FeedoptPlan:39' CurvStruct.Info.zspdmode = ZSpdMode.ZZ;
                        b_CurvStruct.Info.zspdmode = ZSpdMode_ZZ;
                    } else {
                        // 'isAZeroEnd:9' zeroFlag = false;
                        // 'FeedoptPlan:40' else
                        // 'FeedoptPlan:41' CurvStruct.Info.zspdmode = ZSpdMode.ZN;
                        b_CurvStruct.Info.zspdmode = ZSpdMode_ZN;
                    }
                }
            }
            // 'FeedoptPlan:46' [CurvStruct] = add_tool_offset( CurvStruct, ctx.cfg.indCart,
            // prev_tool );
            //  Add the tool offset to the curve structure.
            // 'add_tool_offset:4' if( ~CurvStruct.Info.TRAFO )
            if (!b_CurvStruct.Info.TRAFO) {
                double CurvStruct_data[3];
                int CurvStruct_size;
                // 'add_tool_offset:5' prev_off = [prev_tool.offset.x,prev_tool.offset.y,
                // prev_tool.offset.z]; 'add_tool_offset:6' off = [CurvStruct.tool.offset.x, ...
                // 'add_tool_offset:7'            CurvStruct.tool.offset.y, ...
                // 'add_tool_offset:8'            CurvStruct.tool.offset.z];
                off[0] = b_CurvStruct.tool.offset.x;
                off[1] = b_CurvStruct.tool.offset.y;
                off[2] = b_CurvStruct.tool.offset.z;
                // 'add_tool_offset:9' CurvStruct.R0( indCart ) = ...
                // 'add_tool_offset:10'         CurvStruct.R0( indCart ) + prev_off( : );
                if (ctx->cfg.indCart.size[0] == 3) {
                    double b_prev_tool_offset_x[3];
                    int fe_loop_ub;
                    b_prev_tool_offset_x[0] = prev_tool_offset_x;
                    b_prev_tool_offset_x[1] = prev_tool_offset_y;
                    b_prev_tool_offset_x[2] = prev_tool_offset_z;
                    CurvStruct_size = ctx->cfg.indCart.size[0];
                    fe_loop_ub = ctx->cfg.indCart.size[0];
                    for (int i103{0}; i103 < fe_loop_ub; i103++) {
                        CurvStruct_data[i103] = b_CurvStruct.R0[ctx->cfg.indCart.data[i103] - 1] +
                                                b_prev_tool_offset_x[i103];
                    }
                    for (int i110{0}; i110 < CurvStruct_size; i110++) {
                        b_CurvStruct.R0[ctx->cfg.indCart.data[i110] - 1] = CurvStruct_data[i110];
                    }
                } else {
                    binary_expand_op(&b_CurvStruct, ctx, prev_tool_offset_x, prev_tool_offset_y,
                                     prev_tool_offset_z);
                }
                // 'add_tool_offset:11' CurvStruct.R1( indCart ) = ...
                // 'add_tool_offset:12'         CurvStruct.R1( indCart ) + off( : );
                if (ctx->cfg.indCart.size[0] == 3) {
                    int je_loop_ub;
                    CurvStruct_size = ctx->cfg.indCart.size[0];
                    je_loop_ub = ctx->cfg.indCart.size[0];
                    for (int i107{0}; i107 < je_loop_ub; i107++) {
                        CurvStruct_data[i107] =
                            b_CurvStruct.R1[ctx->cfg.indCart.data[i107] - 1] + off[i107];
                    }
                    for (int i112{0}; i112 < CurvStruct_size; i112++) {
                        b_CurvStruct.R1[ctx->cfg.indCart.data[i112] - 1] = CurvStruct_data[i112];
                    }
                } else {
                    binary_expand_op(&b_CurvStruct, ctx, off);
                }
                // 'add_tool_offset:13' if ( CurvStruct.Info.Type == CurveType.Helix )
                if (b_CurvStruct.Info.Type == CurveType_Helix) {
                    __m128d r5;
                    __m128d r6;
                    // 'add_tool_offset:14' CurvStruct.CorrectedHelixCenter =
                    // CurvStruct.CorrectedHelixCenter + off( : );
                    r5 = _mm_loadu_pd(&b_CurvStruct.CorrectedHelixCenter[0]);
                    r6 = _mm_loadu_pd(&off[0]);
                    _mm_storeu_pd(&b_CurvStruct.CorrectedHelixCenter[0], _mm_add_pd(r5, r6));
                    b_CurvStruct.CorrectedHelixCenter[2] += off[2];
                }
            }
            // 'FeedoptPlan:48' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            // 'FeedoptPlan:49' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
            r2 = _mm_loadu_pd(&b_CurvStruct.R0[3]);
            r3 = _mm_set1_pd(0.017453292519943295);
            _mm_storeu_pd(&b_CurvStruct.R0[3], _mm_mul_pd(r3, r2));
            r4 = _mm_loadu_pd(&b_CurvStruct.R1[3]);
            _mm_storeu_pd(&b_CurvStruct.R1[3], _mm_mul_pd(r3, r4));
            b_CurvStruct.R0[5] *= 0.017453292519943295;
            b_CurvStruct.R1[5] *= 0.017453292519943295;
            // 'FeedoptPlan:51' for j = 1 : StructTypeName.NumberAxisMax
            // 'FeedoptPlan:60' if( CurvStruct.Info.FeedRate == 0.0 )
            if (b_CurvStruct.Info.FeedRate == 0.0) {
                // 'FeedoptPlan:61' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                b_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
            }
            // 'FeedoptPlan:63' if( status == 1 && CurvStruct.Info.Type ~= CurveType.None )
            if ((b_status == 1) && (b_CurvStruct.Info.Type != CurveType_None)) {
                // 'FeedoptPlan:64' if ( CurvStruct.Info.FeedRate == 0.0 )
                if (b_CurvStruct.Info.FeedRate == 0.0) {
                    //  check for undefined feedrate
                    // 'FeedoptPlan:66' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                    b_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
                }
                // 'FeedoptPlan:68' ctx.q_gcode.push( CurvStruct );
                ctx->q_gcode.push(&b_CurvStruct);
            }
        }
        // 'FeedoptPlan:71' if ctx.q_gcode.isempty()
        if (ctx->q_gcode.isempty()) {
            // 'FeedoptPlan:72' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
            // 'FeedoptPlan:73' DebugLog(DebugCfg.Warning, ...
            // 'FeedoptPlan:74'                 'ERROR: Optimization failed, Gcode queue is
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
            // 'FeedoptPlan:77' last = ctx.q_gcode.rget(1);
            ctx->q_gcode.rget(&last);
            // 'FeedoptPlan:78' if( isAZeroStart(last) )
            //  isAZeroStart : Return true if the curv starts with zero speed
            //  curv  : The curve struct
            // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
            // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
            if ((last.Info.zspdmode == ZSpdMode_ZN) || (last.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroStart:6' zeroFlag = true;
                // 'FeedoptPlan:79' last.Info.zspdmode = ZSpdMode.ZZ;
                last.Info.zspdmode = ZSpdMode_ZZ;
            } else {
                // 'isAZeroStart:8' zeroFlag = false;
                // 'FeedoptPlan:80' else
                // 'FeedoptPlan:81' last.Info.zspdmode = ZSpdMode.NZ;
                last.Info.zspdmode = ZSpdMode_NZ;
            }
            // 'FeedoptPlan:83' ctx.q_gcode.set( ctx.q_gcode.size, last );
            ctx->q_gcode.set(ctx->q_gcode.size(), &last);
            // 'FeedoptPlan:85' assert( checkZSpdmode( ctx.q_gcode ), "ERROR : " + mfilename ...
            // 'FeedoptPlan:86'             + ".m : Check zspdmode failed " );
            checkZSpdmode(&ctx->q_gcode);
            checkParametrisation(&ctx->q_gcode);
            ctx->op = Fopt_Check;
        }
    } break;
    case Fopt_Check:
        // 'FeedoptPlan:92' case Fopt.Check
        // 'FeedoptPlan:93' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    case Fopt_Compress: {
        // 'FeedoptPlan:106' case Fopt.Compress
        // 'FeedoptPlan:107' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i2;
            unsigned int u;
            // 'FeedoptPlan:108' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i2 = static_cast<int>(u);
            for (int j{0}; j < i2; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:109' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r1);
                ctx->q_compress.push(&r1);
            }
        } else {
            int af_loop_ub;
            int bc_loop_ub;
            int cb_loop_ub;
            int d_loop_ub;
            int de_loop_ub;
            int ed_loop_ub;
            int ef_loop_ub;
            int fc_loop_ub;
            int if_loop_ub;
            int jc_loop_ub;
            int kb_loop_ub;
            int l_loop_ub;
            int md_loop_ub;
            int mf_loop_ub;
            int nc_loop_ub;
            int ne_loop_ub;
            int ob_loop_ub;
            int qf_loop_ub;
            int rc_loop_ub;
            int re_loop_ub;
            int sb_loop_ub;
            int t_loop_ub;
            int ud_loop_ub;
            int uf_loop_ub;
            int vc_loop_ub;
            int ve_loop_ub;
            int wb_loop_ub;
            int yf_loop_ub;
            // 'FeedoptPlan:111' else
            // 'FeedoptPlan:112' ctx = compressCurvStructs(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            d_loop_ub = ctx->BasisVal.size(1);
            for (int i5{0}; i5 < d_loop_ub; i5++) {
                int k_loop_ub;
                k_loop_ub = ctx->BasisVal.size(0);
                for (int i12{0}; i12 < k_loop_ub; i12++) {
                    r.BasisVal[i12 + r.BasisVal.size(0) * i5] =
                        ctx->BasisVal[i12 + ctx->BasisVal.size(0) * i5];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            l_loop_ub = ctx->BasisValD.size(1);
            for (int i13{0}; i13 < l_loop_ub; i13++) {
                int s_loop_ub;
                s_loop_ub = ctx->BasisValD.size(0);
                for (int i20{0}; i20 < s_loop_ub; i20++) {
                    r.BasisValD[i20 + r.BasisValD.size(0) * i13] =
                        ctx->BasisValD[i20 + ctx->BasisValD.size(0) * i13];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            t_loop_ub = ctx->BasisValDD.size(1);
            for (int i21{0}; i21 < t_loop_ub; i21++) {
                int bb_loop_ub;
                bb_loop_ub = ctx->BasisValDD.size(0);
                for (int i28{0}; i28 < bb_loop_ub; i28++) {
                    r.BasisValDD[i28 + r.BasisValDD.size(0) * i21] =
                        ctx->BasisValDD[i28 + ctx->BasisValDD.size(0) * i21];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            cb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i29{0}; i29 < cb_loop_ub; i29++) {
                int jb_loop_ub;
                jb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i36{0}; i36 < jb_loop_ub; i36++) {
                    r.BasisValDDD[i36 + r.BasisValDDD.size(0) * i29] =
                        ctx->BasisValDDD[i36 + ctx->BasisValDDD.size(0) * i29];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            kb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i37{0}; i37 < kb_loop_ub; i37++) {
                r.BasisIntegr[i37] = ctx->BasisIntegr[i37];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            ob_loop_ub = ctx->u_vec.size(1);
            for (int i41{0}; i41 < ob_loop_ub; i41++) {
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
            sb_loop_ub = ctx->cfg.maskTot.size[1];
            if (sb_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[sb_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            wb_loop_ub = ctx->cfg.maskCart.size[1];
            if (wb_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[wb_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            bc_loop_ub = ctx->cfg.maskRot.size[1];
            if (bc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[bc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            fc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i45{0}; i45 < fc_loop_ub; i45++) {
                r.cfg.indCart[i45] = ctx->cfg.indCart.data[i45];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            jc_loop_ub = ctx->cfg.indRot.size[0];
            for (int i49{0}; i49 < jc_loop_ub; i49++) {
                r.cfg.indRot[i49] = ctx->cfg.indRot.data[i49];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            nc_loop_ub = ctx->cfg.D.size[0];
            for (int i53{0}; i53 < nc_loop_ub; i53++) {
                r.cfg.D[i53] = ctx->cfg.D.data[i53];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            rc_loop_ub = ctx->cfg.kin_params.size[0];
            if (rc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[rc_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i57{0}; i57 < 5; i57++) {
                r.cfg.kin_type[i57] = ctx->cfg.kin_type[i57];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i61{0}; i61 < 6; i61++) {
                r.cfg.vmax[i61] = ctx->cfg.vmax[i61];
                r.cfg.amax[i61] = ctx->cfg.amax[i61];
                r.cfg.jmax[i61] = ctx->cfg.jmax[i61];
            }
            r.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
            r.cfg.SplineDegree = ctx->cfg.SplineDegree;
            r.cfg.CutOff = ctx->cfg.CutOff;
            r.cfg.LSplit = ctx->cfg.LSplit;
            r.cfg.LSplitZero = ctx->cfg.LSplitZero;
            r.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
            r.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
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
            r.cfg.Cusp = ctx->cfg.Cusp;
            r.cfg.Compressing = ctx->cfg.Compressing;
            r.cfg.Smoothing = ctx->cfg.Smoothing;
            r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
            for (int e_i{0}; e_i < 5; e_i++) {
                r.cfg.GaussLegendreX[e_i] = ctx->cfg.GaussLegendreX[e_i];
                r.cfg.GaussLegendreW[e_i] = ctx->cfg.GaussLegendreW[e_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i65{0}; i65 < 9; i65++) {
                r.cfg.LogFileName[i65] = ctx->cfg.LogFileName[i65];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            vc_loop_ub = ctx->Coeff.size(1);
            for (int i69{0}; i69 < vc_loop_ub; i69++) {
                int ad_loop_ub;
                ad_loop_ub = ctx->Coeff.size(0);
                for (int i73{0}; i73 < ad_loop_ub; i73++) {
                    r.Coeff[i73 + r.Coeff.size(0) * i69] =
                        ctx->Coeff[i73 + ctx->Coeff.size(0) * i69];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            ed_loop_ub = r.BasisVal.size(1);
            for (int i77{0}; i77 < ed_loop_ub; i77++) {
                int ld_loop_ub;
                ld_loop_ub = r.BasisVal.size(0);
                for (int i84{0}; i84 < ld_loop_ub; i84++) {
                    ctx->BasisVal[i84 + ctx->BasisVal.size(0) * i77] =
                        r.BasisVal[i84 + r.BasisVal.size(0) * i77];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            md_loop_ub = r.BasisValD.size(1);
            for (int i85{0}; i85 < md_loop_ub; i85++) {
                int td_loop_ub;
                td_loop_ub = r.BasisValD.size(0);
                for (int i92{0}; i92 < td_loop_ub; i92++) {
                    ctx->BasisValD[i92 + ctx->BasisValD.size(0) * i85] =
                        r.BasisValD[i92 + r.BasisValD.size(0) * i85];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            ud_loop_ub = r.BasisValDD.size(1);
            for (int i93{0}; i93 < ud_loop_ub; i93++) {
                int ce_loop_ub;
                ce_loop_ub = r.BasisValDD.size(0);
                for (int i100{0}; i100 < ce_loop_ub; i100++) {
                    ctx->BasisValDD[i100 + ctx->BasisValDD.size(0) * i93] =
                        r.BasisValDD[i100 + r.BasisValDD.size(0) * i93];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            de_loop_ub = r.BasisValDDD.size(1);
            for (int i101{0}; i101 < de_loop_ub; i101++) {
                int me_loop_ub;
                me_loop_ub = r.BasisValDDD.size(0);
                for (int i111{0}; i111 < me_loop_ub; i111++) {
                    ctx->BasisValDDD[i111 + ctx->BasisValDDD.size(0) * i101] =
                        r.BasisValDDD[i111 + r.BasisValDDD.size(0) * i101];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            ne_loop_ub = r.BasisIntegr.size(0);
            for (int i113{0}; i113 < ne_loop_ub; i113++) {
                ctx->BasisIntegr[i113] = r.BasisIntegr[i113];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            re_loop_ub = r.u_vec.size(1);
            for (int i117{0}; i117 < re_loop_ub; i117++) {
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
            ve_loop_ub = r.cfg.maskTot.size[1];
            if (ve_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ve_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            af_loop_ub = r.cfg.maskCart.size[1];
            if (af_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[af_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            ef_loop_ub = r.cfg.maskRot.size[1];
            if (ef_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[ef_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            if_loop_ub = r.cfg.indCart.size(0);
            for (int i121{0}; i121 < if_loop_ub; i121++) {
                ctx->cfg.indCart.data[i121] = r.cfg.indCart[i121];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            mf_loop_ub = r.cfg.indRot.size(0);
            for (int i125{0}; i125 < mf_loop_ub; i125++) {
                ctx->cfg.indRot.data[i125] = r.cfg.indRot[i125];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            qf_loop_ub = r.cfg.D.size(0);
            for (int i129{0}; i129 < qf_loop_ub; i129++) {
                ctx->cfg.D.data[i129] = r.cfg.D[i129];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            uf_loop_ub = r.cfg.kin_params.size[0];
            if (uf_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[uf_loop_ub],
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
            ctx->cfg.LThresholdMax = r.cfg.LThresholdMax;
            ctx->cfg.LThresholdMin = r.cfg.LThresholdMin;
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
            ctx->cfg.Cusp = r.cfg.Cusp;
            ctx->cfg.Compressing = r.cfg.Compressing;
            ctx->cfg.Smoothing = r.cfg.Smoothing;
            ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
            for (int i_i{0}; i_i < 5; i_i++) {
                ctx->cfg.GaussLegendreX[i_i] = r.cfg.GaussLegendreX[i_i];
                ctx->cfg.GaussLegendreW[i_i] = r.cfg.GaussLegendreW[i_i];
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
            yf_loop_ub = r.Coeff.size(1);
            for (int i145{0}; i145 < yf_loop_ub; i145++) {
                int dg_loop_ub;
                dg_loop_ub = r.Coeff.size(0);
                for (int i149{0}; i149 < dg_loop_ub; i149++) {
                    ctx->Coeff[i149 + ctx->Coeff.size(0) * i145] =
                        r.Coeff[i149 + r.Coeff.size(0) * i145];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        // 'FeedoptPlan:115' assert( checkZSpdmode( ctx.q_compress ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:116'             + ".m : compress zspdmode failed " );
        checkZSpdmode(&ctx->q_compress);
        checkParametrisation(&ctx->q_compress);
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:121' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int ae_loop_ub;
        int b_loop_ub;
        int bf_loop_ub;
        int cd_loop_ub;
        int dc_loop_ub;
        int ff_loop_ub;
        int hb_loop_ub;
        int hc_loop_ub;
        int i_loop_ub;
        int jd_loop_ub;
        int jf_loop_ub;
        int ke_loop_ub;
        int lc_loop_ub;
        int mb_loop_ub;
        int nf_loop_ub;
        int pc_loop_ub;
        int pe_loop_ub;
        int q_loop_ub;
        int qb_loop_ub;
        int rd_loop_ub;
        int rf_loop_ub;
        int se_loop_ub;
        int tc_loop_ub;
        int ub_loop_ub;
        int vf_loop_ub;
        int we_loop_ub;
        int y_loop_ub;
        int yb_loop_ub;
        // 'FeedoptPlan:123' case Fopt.Smooth
        //          histogramLength( ctx, ctx.q_compress, "Compressing" );
        // 'FeedoptPlan:126' ctx = smoothCurvStructs(ctx);
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        b_loop_ub = ctx->BasisVal.size(1);
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            int f_loop_ub;
            f_loop_ub = ctx->BasisVal.size(0);
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                r.BasisVal[i7 + r.BasisVal.size(0) * i3] =
                    ctx->BasisVal[i7 + ctx->BasisVal.size(0) * i3];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        i_loop_ub = ctx->BasisValD.size(1);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            int n_loop_ub;
            n_loop_ub = ctx->BasisValD.size(0);
            for (int i15{0}; i15 < n_loop_ub; i15++) {
                r.BasisValD[i15 + r.BasisValD.size(0) * i10] =
                    ctx->BasisValD[i15 + ctx->BasisValD.size(0) * i10];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        q_loop_ub = ctx->BasisValDD.size(1);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            int v_loop_ub;
            v_loop_ub = ctx->BasisValDD.size(0);
            for (int i23{0}; i23 < v_loop_ub; i23++) {
                r.BasisValDD[i23 + r.BasisValDD.size(0) * i18] =
                    ctx->BasisValDD[i23 + ctx->BasisValDD.size(0) * i18];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        y_loop_ub = ctx->BasisValDDD.size(1);
        for (int i26{0}; i26 < y_loop_ub; i26++) {
            int eb_loop_ub;
            eb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i31{0}; i31 < eb_loop_ub; i31++) {
                r.BasisValDDD[i31 + r.BasisValDDD.size(0) * i26] =
                    ctx->BasisValDDD[i31 + ctx->BasisValDDD.size(0) * i26];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        hb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i34{0}; i34 < hb_loop_ub; i34++) {
            r.BasisIntegr[i34] = ctx->BasisIntegr[i34];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        mb_loop_ub = ctx->u_vec.size(1);
        for (int i39{0}; i39 < mb_loop_ub; i39++) {
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
        qb_loop_ub = ctx->cfg.maskTot.size[1];
        if (qb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[qb_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        ub_loop_ub = ctx->cfg.maskCart.size[1];
        if (ub_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[ub_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        yb_loop_ub = ctx->cfg.maskRot.size[1];
        if (yb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[yb_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        dc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i43{0}; i43 < dc_loop_ub; i43++) {
            r.cfg.indCart[i43] = ctx->cfg.indCart.data[i43];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        hc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i47{0}; i47 < hc_loop_ub; i47++) {
            r.cfg.indRot[i47] = ctx->cfg.indRot.data[i47];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        lc_loop_ub = ctx->cfg.D.size[0];
        for (int i51{0}; i51 < lc_loop_ub; i51++) {
            r.cfg.D[i51] = ctx->cfg.D.data[i51];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        pc_loop_ub = ctx->cfg.kin_params.size[0];
        if (pc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[pc_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i55{0}; i55 < 5; i55++) {
            r.cfg.kin_type[i55] = ctx->cfg.kin_type[i55];
        }
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
        r.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
        r.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
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
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int c_i{0}; c_i < 5; c_i++) {
            r.cfg.GaussLegendreX[c_i] = ctx->cfg.GaussLegendreX[c_i];
            r.cfg.GaussLegendreW[c_i] = ctx->cfg.GaussLegendreW[c_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i63{0}; i63 < 9; i63++) {
            r.cfg.LogFileName[i63] = ctx->cfg.LogFileName[i63];
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
        for (int i67{0}; i67 < tc_loop_ub; i67++) {
            int xc_loop_ub;
            xc_loop_ub = ctx->Coeff.size(0);
            for (int i71{0}; i71 < xc_loop_ub; i71++) {
                r.Coeff[i71 + r.Coeff.size(0) * i67] = ctx->Coeff[i71 + ctx->Coeff.size(0) * i67];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        smoothCurvStructs(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        cd_loop_ub = r.BasisVal.size(1);
        for (int i75{0}; i75 < cd_loop_ub; i75++) {
            int gd_loop_ub;
            gd_loop_ub = r.BasisVal.size(0);
            for (int i79{0}; i79 < gd_loop_ub; i79++) {
                ctx->BasisVal[i79 + ctx->BasisVal.size(0) * i75] =
                    r.BasisVal[i79 + r.BasisVal.size(0) * i75];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        jd_loop_ub = r.BasisValD.size(1);
        for (int i82{0}; i82 < jd_loop_ub; i82++) {
            int od_loop_ub;
            od_loop_ub = r.BasisValD.size(0);
            for (int i87{0}; i87 < od_loop_ub; i87++) {
                ctx->BasisValD[i87 + ctx->BasisValD.size(0) * i82] =
                    r.BasisValD[i87 + r.BasisValD.size(0) * i82];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        rd_loop_ub = r.BasisValDD.size(1);
        for (int i90{0}; i90 < rd_loop_ub; i90++) {
            int wd_loop_ub;
            wd_loop_ub = r.BasisValDD.size(0);
            for (int i95{0}; i95 < wd_loop_ub; i95++) {
                ctx->BasisValDD[i95 + ctx->BasisValDD.size(0) * i90] =
                    r.BasisValDD[i95 + r.BasisValDD.size(0) * i90];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        ae_loop_ub = r.BasisValDDD.size(1);
        for (int i98{0}; i98 < ae_loop_ub; i98++) {
            int ge_loop_ub;
            ge_loop_ub = r.BasisValDDD.size(0);
            for (int i104{0}; i104 < ge_loop_ub; i104++) {
                ctx->BasisValDDD[i104 + ctx->BasisValDDD.size(0) * i98] =
                    r.BasisValDDD[i104 + r.BasisValDDD.size(0) * i98];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        ke_loop_ub = r.BasisIntegr.size(0);
        for (int i108{0}; i108 < ke_loop_ub; i108++) {
            ctx->BasisIntegr[i108] = r.BasisIntegr[i108];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        pe_loop_ub = r.u_vec.size(1);
        for (int i115{0}; i115 < pe_loop_ub; i115++) {
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
        se_loop_ub = r.cfg.maskTot.size[1];
        if (se_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[se_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        we_loop_ub = r.cfg.maskCart.size[1];
        if (we_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[we_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        bf_loop_ub = r.cfg.maskRot.size[1];
        if (bf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[bf_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        ff_loop_ub = r.cfg.indCart.size(0);
        for (int i118{0}; i118 < ff_loop_ub; i118++) {
            ctx->cfg.indCart.data[i118] = r.cfg.indCart[i118];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        jf_loop_ub = r.cfg.indRot.size(0);
        for (int i122{0}; i122 < jf_loop_ub; i122++) {
            ctx->cfg.indRot.data[i122] = r.cfg.indRot[i122];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        nf_loop_ub = r.cfg.D.size(0);
        for (int i126{0}; i126 < nf_loop_ub; i126++) {
            ctx->cfg.D.data[i126] = r.cfg.D[i126];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        rf_loop_ub = r.cfg.kin_params.size[0];
        if (rf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[rf_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i130{0}; i130 < 5; i130++) {
            ctx->cfg.kin_type[i130] = r.cfg.kin_type[i130];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i134{0}; i134 < 6; i134++) {
            ctx->cfg.vmax[i134] = r.cfg.vmax[i134];
            ctx->cfg.amax[i134] = r.cfg.amax[i134];
            ctx->cfg.jmax[i134] = r.cfg.jmax[i134];
        }
        ctx->cfg.LeeSplineDegree = r.cfg.LeeSplineDegree;
        ctx->cfg.SplineDegree = r.cfg.SplineDegree;
        ctx->cfg.CutOff = r.cfg.CutOff;
        ctx->cfg.LSplit = r.cfg.LSplit;
        ctx->cfg.LSplitZero = r.cfg.LSplitZero;
        ctx->cfg.LThresholdMax = r.cfg.LThresholdMax;
        ctx->cfg.LThresholdMin = r.cfg.LThresholdMin;
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
        ctx->cfg.Cusp = r.cfg.Cusp;
        ctx->cfg.Compressing = r.cfg.Compressing;
        ctx->cfg.Smoothing = r.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int f_i{0}; f_i < 5; f_i++) {
            ctx->cfg.GaussLegendreX[f_i] = r.cfg.GaussLegendreX[f_i];
            ctx->cfg.GaussLegendreW[f_i] = r.cfg.GaussLegendreW[f_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i138{0}; i138 < 9; i138++) {
            ctx->cfg.LogFileName[i138] = r.cfg.LogFileName[i138];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        vf_loop_ub = r.Coeff.size(1);
        for (int i142{0}; i142 < vf_loop_ub; i142++) {
            int ag_loop_ub;
            ag_loop_ub = r.Coeff.size(0);
            for (int i146{0}; i146 < ag_loop_ub; i146++) {
                ctx->Coeff[i146 + ctx->Coeff.size(0) * i142] =
                    r.Coeff[i146 + r.Coeff.size(0) * i142];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:127' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:129' assert( checkZSpdmode( ctx.q_smooth ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:130'             + ".m : smooth zspdmode failed " );
        checkZSpdmode(&r.q_smooth);
        checkParametrisation(&r.q_smooth);
    } break;
    case Fopt_Split: {
        int ab_loop_ub;
        int ac_loop_ub;
        int be_loop_ub;
        int c_loop_ub;
        int cf_loop_ub;
        int dd_loop_ub;
        int ec_loop_ub;
        int gf_loop_ub;
        int ib_loop_ub;
        int ic_loop_ub;
        int j_loop_ub;
        int kd_loop_ub;
        int kf_loop_ub;
        int le_loop_ub;
        int mc_loop_ub;
        int nb_loop_ub;
        int of_loop_ub;
        int qc_loop_ub;
        int qe_loop_ub;
        int r_loop_ub;
        int rb_loop_ub;
        int sd_loop_ub;
        int sf_loop_ub;
        int te_loop_ub;
        int uc_loop_ub;
        int vb_loop_ub;
        int wf_loop_ub;
        int xe_loop_ub;
        // 'FeedoptPlan:136' case Fopt.Split
        //          histogramLength( ctx, ctx.q_smooth, "Smoothing" );
        // 'FeedoptPlan:139' ctx = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        c_loop_ub = ctx->BasisVal.size(1);
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            int g_loop_ub;
            g_loop_ub = ctx->BasisVal.size(0);
            for (int i8{0}; i8 < g_loop_ub; i8++) {
                r.BasisVal[i8 + r.BasisVal.size(0) * i4] =
                    ctx->BasisVal[i8 + ctx->BasisVal.size(0) * i4];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        j_loop_ub = ctx->BasisValD.size(1);
        for (int i11{0}; i11 < j_loop_ub; i11++) {
            int o_loop_ub;
            o_loop_ub = ctx->BasisValD.size(0);
            for (int i16{0}; i16 < o_loop_ub; i16++) {
                r.BasisValD[i16 + r.BasisValD.size(0) * i11] =
                    ctx->BasisValD[i16 + ctx->BasisValD.size(0) * i11];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        r_loop_ub = ctx->BasisValDD.size(1);
        for (int i19{0}; i19 < r_loop_ub; i19++) {
            int w_loop_ub;
            w_loop_ub = ctx->BasisValDD.size(0);
            for (int i24{0}; i24 < w_loop_ub; i24++) {
                r.BasisValDD[i24 + r.BasisValDD.size(0) * i19] =
                    ctx->BasisValDD[i24 + ctx->BasisValDD.size(0) * i19];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        ab_loop_ub = ctx->BasisValDDD.size(1);
        for (int i27{0}; i27 < ab_loop_ub; i27++) {
            int fb_loop_ub;
            fb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i32{0}; i32 < fb_loop_ub; i32++) {
                r.BasisValDDD[i32 + r.BasisValDDD.size(0) * i27] =
                    ctx->BasisValDDD[i32 + ctx->BasisValDDD.size(0) * i27];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        ib_loop_ub = ctx->BasisIntegr.size(0);
        for (int i35{0}; i35 < ib_loop_ub; i35++) {
            r.BasisIntegr[i35] = ctx->BasisIntegr[i35];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        nb_loop_ub = ctx->u_vec.size(1);
        for (int i40{0}; i40 < nb_loop_ub; i40++) {
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
        rb_loop_ub = ctx->cfg.maskTot.size[1];
        if (rb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[rb_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        vb_loop_ub = ctx->cfg.maskCart.size[1];
        if (vb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[vb_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        ac_loop_ub = ctx->cfg.maskRot.size[1];
        if (ac_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[ac_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ec_loop_ub = ctx->cfg.indCart.size[0];
        for (int i44{0}; i44 < ec_loop_ub; i44++) {
            r.cfg.indCart[i44] = ctx->cfg.indCart.data[i44];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ic_loop_ub = ctx->cfg.indRot.size[0];
        for (int i48{0}; i48 < ic_loop_ub; i48++) {
            r.cfg.indRot[i48] = ctx->cfg.indRot.data[i48];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        mc_loop_ub = ctx->cfg.D.size[0];
        for (int i52{0}; i52 < mc_loop_ub; i52++) {
            r.cfg.D[i52] = ctx->cfg.D.data[i52];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        qc_loop_ub = ctx->cfg.kin_params.size[0];
        if (qc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[qc_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i56{0}; i56 < 5; i56++) {
            r.cfg.kin_type[i56] = ctx->cfg.kin_type[i56];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i60{0}; i60 < 6; i60++) {
            r.cfg.vmax[i60] = ctx->cfg.vmax[i60];
            r.cfg.amax[i60] = ctx->cfg.amax[i60];
            r.cfg.jmax[i60] = ctx->cfg.jmax[i60];
        }
        r.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
        r.cfg.SplineDegree = ctx->cfg.SplineDegree;
        r.cfg.CutOff = ctx->cfg.CutOff;
        r.cfg.LSplit = ctx->cfg.LSplit;
        r.cfg.LSplitZero = ctx->cfg.LSplitZero;
        r.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
        r.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
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
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int d_i{0}; d_i < 5; d_i++) {
            r.cfg.GaussLegendreX[d_i] = ctx->cfg.GaussLegendreX[d_i];
            r.cfg.GaussLegendreW[d_i] = ctx->cfg.GaussLegendreW[d_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i64{0}; i64 < 9; i64++) {
            r.cfg.LogFileName[i64] = ctx->cfg.LogFileName[i64];
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
        for (int i68{0}; i68 < uc_loop_ub; i68++) {
            int yc_loop_ub;
            yc_loop_ub = ctx->Coeff.size(0);
            for (int i72{0}; i72 < yc_loop_ub; i72++) {
                r.Coeff[i72 + r.Coeff.size(0) * i68] = ctx->Coeff[i72 + ctx->Coeff.size(0) * i68];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        splitQueue(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        dd_loop_ub = r.BasisVal.size(1);
        for (int i76{0}; i76 < dd_loop_ub; i76++) {
            int hd_loop_ub;
            hd_loop_ub = r.BasisVal.size(0);
            for (int i80{0}; i80 < hd_loop_ub; i80++) {
                ctx->BasisVal[i80 + ctx->BasisVal.size(0) * i76] =
                    r.BasisVal[i80 + r.BasisVal.size(0) * i76];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        kd_loop_ub = r.BasisValD.size(1);
        for (int i83{0}; i83 < kd_loop_ub; i83++) {
            int pd_loop_ub;
            pd_loop_ub = r.BasisValD.size(0);
            for (int i88{0}; i88 < pd_loop_ub; i88++) {
                ctx->BasisValD[i88 + ctx->BasisValD.size(0) * i83] =
                    r.BasisValD[i88 + r.BasisValD.size(0) * i83];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        sd_loop_ub = r.BasisValDD.size(1);
        for (int i91{0}; i91 < sd_loop_ub; i91++) {
            int xd_loop_ub;
            xd_loop_ub = r.BasisValDD.size(0);
            for (int i96{0}; i96 < xd_loop_ub; i96++) {
                ctx->BasisValDD[i96 + ctx->BasisValDD.size(0) * i91] =
                    r.BasisValDD[i96 + r.BasisValDD.size(0) * i91];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        be_loop_ub = r.BasisValDDD.size(1);
        for (int i99{0}; i99 < be_loop_ub; i99++) {
            int he_loop_ub;
            he_loop_ub = r.BasisValDDD.size(0);
            for (int i105{0}; i105 < he_loop_ub; i105++) {
                ctx->BasisValDDD[i105 + ctx->BasisValDDD.size(0) * i99] =
                    r.BasisValDDD[i105 + r.BasisValDDD.size(0) * i99];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        le_loop_ub = r.BasisIntegr.size(0);
        for (int i109{0}; i109 < le_loop_ub; i109++) {
            ctx->BasisIntegr[i109] = r.BasisIntegr[i109];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        qe_loop_ub = r.u_vec.size(1);
        for (int i116{0}; i116 < qe_loop_ub; i116++) {
            ctx->u_vec[i116] = r.u_vec[i116];
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
        te_loop_ub = r.cfg.maskTot.size[1];
        if (te_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[te_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        xe_loop_ub = r.cfg.maskCart.size[1];
        if (xe_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[xe_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        cf_loop_ub = r.cfg.maskRot.size[1];
        if (cf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[cf_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        gf_loop_ub = r.cfg.indCart.size(0);
        for (int i119{0}; i119 < gf_loop_ub; i119++) {
            ctx->cfg.indCart.data[i119] = r.cfg.indCart[i119];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        kf_loop_ub = r.cfg.indRot.size(0);
        for (int i123{0}; i123 < kf_loop_ub; i123++) {
            ctx->cfg.indRot.data[i123] = r.cfg.indRot[i123];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        of_loop_ub = r.cfg.D.size(0);
        for (int i127{0}; i127 < of_loop_ub; i127++) {
            ctx->cfg.D.data[i127] = r.cfg.D[i127];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        sf_loop_ub = r.cfg.kin_params.size[0];
        if (sf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[sf_loop_ub],
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
        ctx->cfg.LThresholdMax = r.cfg.LThresholdMax;
        ctx->cfg.LThresholdMin = r.cfg.LThresholdMin;
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
        ctx->cfg.Cusp = r.cfg.Cusp;
        ctx->cfg.Compressing = r.cfg.Compressing;
        ctx->cfg.Smoothing = r.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int g_i{0}; g_i < 5; g_i++) {
            ctx->cfg.GaussLegendreX[g_i] = r.cfg.GaussLegendreX[g_i];
            ctx->cfg.GaussLegendreW[g_i] = r.cfg.GaussLegendreW[g_i];
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
        wf_loop_ub = r.Coeff.size(1);
        for (int i143{0}; i143 < wf_loop_ub; i143++) {
            int bg_loop_ub;
            bg_loop_ub = r.Coeff.size(0);
            for (int i147{0}; i147 < bg_loop_ub; i147++) {
                ctx->Coeff[i147 + ctx->Coeff.size(0) * i143] =
                    r.Coeff[i147 + r.Coeff.size(0) * i143];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:141' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:143' assert( checkZSpdmode( ctx.q_split ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:144'             + ".m : splitted zspdmode failed " );
        checkZSpdmode(&r.q_split);
        checkParametrisation(&r.q_smooth);
    } break;
    case Fopt_Opt: {
        int bd_loop_ub;
        int cc_loop_ub;
        int df_loop_ub;
        int gb_loop_ub;
        int gc_loop_ub;
        int h_loop_ub;
        int hf_loop_ub;
        int id_loop_ub;
        int ie_loop_ub;
        int kc_loop_ub;
        int lb_loop_ub;
        int lf_loop_ub;
        int loop_ub;
        int oc_loop_ub;
        int oe_loop_ub;
        int p_loop_ub;
        int pb_loop_ub;
        int pf_loop_ub;
        int qd_loop_ub;
        int sc_loop_ub;
        int tb_loop_ub;
        int tf_loop_ub;
        int ue_loop_ub;
        int x_loop_ub;
        int xb_loop_ub;
        int xf_loop_ub;
        int yd_loop_ub;
        int ye_loop_ub;
        // 'FeedoptPlan:151' case Fopt.Opt
        // 'FeedoptPlan:152' [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        b_ctx.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        loop_ub = ctx->BasisVal.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            int e_loop_ub;
            e_loop_ub = ctx->BasisVal.size(0);
            for (int i6{0}; i6 < e_loop_ub; i6++) {
                b_ctx.BasisVal[i6 + b_ctx.BasisVal.size(0) * i1] =
                    ctx->BasisVal[i6 + ctx->BasisVal.size(0) * i1];
            }
        }
        b_ctx.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        h_loop_ub = ctx->BasisValD.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            int m_loop_ub;
            m_loop_ub = ctx->BasisValD.size(0);
            for (int i14{0}; i14 < m_loop_ub; i14++) {
                b_ctx.BasisValD[i14 + b_ctx.BasisValD.size(0) * i9] =
                    ctx->BasisValD[i14 + ctx->BasisValD.size(0) * i9];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        p_loop_ub = ctx->BasisValDD.size(1);
        for (int i17{0}; i17 < p_loop_ub; i17++) {
            int u_loop_ub;
            u_loop_ub = ctx->BasisValDD.size(0);
            for (int i22{0}; i22 < u_loop_ub; i22++) {
                b_ctx.BasisValDD[i22 + b_ctx.BasisValDD.size(0) * i17] =
                    ctx->BasisValDD[i22 + ctx->BasisValDD.size(0) * i17];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        x_loop_ub = ctx->BasisValDDD.size(1);
        for (int i25{0}; i25 < x_loop_ub; i25++) {
            int db_loop_ub;
            db_loop_ub = ctx->BasisValDDD.size(0);
            for (int i30{0}; i30 < db_loop_ub; i30++) {
                b_ctx.BasisValDDD[i30 + b_ctx.BasisValDDD.size(0) * i25] =
                    ctx->BasisValDDD[i30 + ctx->BasisValDDD.size(0) * i25];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        gb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i33{0}; i33 < gb_loop_ub; i33++) {
            b_ctx.BasisIntegr[i33] = ctx->BasisIntegr[i33];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        lb_loop_ub = ctx->u_vec.size(1);
        for (int i38{0}; i38 < lb_loop_ub; i38++) {
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
        pb_loop_ub = ctx->cfg.maskTot.size[1];
        if (pb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[pb_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        tb_loop_ub = ctx->cfg.maskCart.size[1];
        if (tb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[tb_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        xb_loop_ub = ctx->cfg.maskRot.size[1];
        if (xb_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[xb_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        cc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i42{0}; i42 < cc_loop_ub; i42++) {
            b_ctx.cfg.indCart[i42] = ctx->cfg.indCart.data[i42];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        gc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i46{0}; i46 < gc_loop_ub; i46++) {
            b_ctx.cfg.indRot[i46] = ctx->cfg.indRot.data[i46];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.D.set_size(ctx->cfg.D.size[0]);
        kc_loop_ub = ctx->cfg.D.size[0];
        for (int i50{0}; i50 < kc_loop_ub; i50++) {
            b_ctx.cfg.D[i50] = ctx->cfg.D.data[i50];
        }
        b_ctx.cfg.coeffD = ctx->cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        oc_loop_ub = ctx->cfg.kin_params.size[0];
        if (oc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[oc_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i54{0}; i54 < 5; i54++) {
            b_ctx.cfg.kin_type[i54] = ctx->cfg.kin_type[i54];
        }
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
        b_ctx.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
        b_ctx.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
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
        b_ctx.cfg.Cusp = ctx->cfg.Cusp;
        b_ctx.cfg.Compressing = ctx->cfg.Compressing;
        b_ctx.cfg.Smoothing = ctx->cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int b_i{0}; b_i < 5; b_i++) {
            b_ctx.cfg.GaussLegendreX[b_i] = ctx->cfg.GaussLegendreX[b_i];
            b_ctx.cfg.GaussLegendreW[b_i] = ctx->cfg.GaussLegendreW[b_i];
        }
        b_ctx.cfg.opt = ctx->cfg.opt;
        for (int i62{0}; i62 < 9; i62++) {
            b_ctx.cfg.LogFileName[i62] = ctx->cfg.LogFileName[i62];
        }
        b_ctx.errcode = ctx->errcode;
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        sc_loop_ub = ctx->Coeff.size(1);
        for (int i66{0}; i66 < sc_loop_ub; i66++) {
            int wc_loop_ub;
            wc_loop_ub = ctx->Coeff.size(0);
            for (int i70{0}; i70 < wc_loop_ub; i70++) {
                b_ctx.Coeff[i70 + b_ctx.Coeff.size(0) * i66] =
                    ctx->Coeff[i70 + ctx->Coeff.size(0) * i66];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        feedratePlanning(&b_ctx, &c_optimized, opt_struct, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        bd_loop_ub = b_ctx.BasisVal.size(1);
        for (int i74{0}; i74 < bd_loop_ub; i74++) {
            int fd_loop_ub;
            fd_loop_ub = b_ctx.BasisVal.size(0);
            for (int i78{0}; i78 < fd_loop_ub; i78++) {
                ctx->BasisVal[i78 + ctx->BasisVal.size(0) * i74] =
                    b_ctx.BasisVal[i78 + b_ctx.BasisVal.size(0) * i74];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        id_loop_ub = b_ctx.BasisValD.size(1);
        for (int i81{0}; i81 < id_loop_ub; i81++) {
            int nd_loop_ub;
            nd_loop_ub = b_ctx.BasisValD.size(0);
            for (int i86{0}; i86 < nd_loop_ub; i86++) {
                ctx->BasisValD[i86 + ctx->BasisValD.size(0) * i81] =
                    b_ctx.BasisValD[i86 + b_ctx.BasisValD.size(0) * i81];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        qd_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i89{0}; i89 < qd_loop_ub; i89++) {
            int vd_loop_ub;
            vd_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i94{0}; i94 < vd_loop_ub; i94++) {
                ctx->BasisValDD[i94 + ctx->BasisValDD.size(0) * i89] =
                    b_ctx.BasisValDD[i94 + b_ctx.BasisValDD.size(0) * i89];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        yd_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i97{0}; i97 < yd_loop_ub; i97++) {
            int ee_loop_ub;
            ee_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i102{0}; i102 < ee_loop_ub; i102++) {
                ctx->BasisValDDD[i102 + ctx->BasisValDDD.size(0) * i97] =
                    b_ctx.BasisValDDD[i102 + b_ctx.BasisValDDD.size(0) * i97];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        ie_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i106{0}; i106 < ie_loop_ub; i106++) {
            ctx->BasisIntegr[i106] = b_ctx.BasisIntegr[i106];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        oe_loop_ub = b_ctx.u_vec.size(1);
        for (int i114{0}; i114 < oe_loop_ub; i114++) {
            ctx->u_vec[i114] = b_ctx.u_vec[i114];
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
        ue_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (ue_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[ue_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        ye_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (ye_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[ye_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        df_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (df_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[df_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        hf_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i120{0}; i120 < hf_loop_ub; i120++) {
            ctx->cfg.indCart.data[i120] = b_ctx.cfg.indCart[i120];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        lf_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i124{0}; i124 < lf_loop_ub; i124++) {
            ctx->cfg.indRot.data[i124] = b_ctx.cfg.indRot[i124];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        pf_loop_ub = b_ctx.cfg.D.size(0);
        for (int i128{0}; i128 < pf_loop_ub; i128++) {
            ctx->cfg.D.data[i128] = b_ctx.cfg.D[i128];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        tf_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (tf_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[tf_loop_ub],
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
        ctx->cfg.LThresholdMax = b_ctx.cfg.LThresholdMax;
        ctx->cfg.LThresholdMin = b_ctx.cfg.LThresholdMin;
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
        ctx->cfg.Cusp = b_ctx.cfg.Cusp;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int h_i{0}; h_i < 5; h_i++) {
            ctx->cfg.GaussLegendreX[h_i] = b_ctx.cfg.GaussLegendreX[h_i];
            ctx->cfg.GaussLegendreW[h_i] = b_ctx.cfg.GaussLegendreW[h_i];
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
        xf_loop_ub = b_ctx.Coeff.size(1);
        for (int i144{0}; i144 < xf_loop_ub; i144++) {
            int cg_loop_ub;
            cg_loop_ub = b_ctx.Coeff.size(0);
            for (int i148{0}; i148 < cg_loop_ub; i148++) {
                ctx->Coeff[i148 + ctx->Coeff.size(0) * i144] =
                    b_ctx.Coeff[i148 + b_ctx.Coeff.size(0) * i144];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        b_optimized = c_optimized;
        // 'FeedoptPlan:153' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:154' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:155' ctx.q_opt.push( opt_struct );
            b_ctx.q_opt.push(opt_struct);
        }
        // 'FeedoptPlan:158' if( quit )
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:160' case Fopt.Finished
        // 'FeedoptPlan:161' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:163' otherwise
        // 'FeedoptPlan:164' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:165' ctx.op = Fopt.Finished;
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
