//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

// Include Files
#include "FeedoptPlan.h"
#include "CheckCurvStructs.h"
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
                // 'FeedoptPlan:26' prev_tool = ctx.q_gcode.rget(1).Tool;
                ctx->q_gcode.rget(&r1);
                prev_tool_offset_x = r1.b_Tool.offset.x;
                prev_tool_offset_y = r1.b_Tool.offset.y;
                prev_tool_offset_z = r1.b_Tool.offset.z;
                // 'FeedoptPlan:28' if( ~toolIsEqual(prev_tool, CurvStruct.Tool ) )
                //  Check the tools are equals
                // 'toolIsEqual:3' isEqual = false;
                isEqual = false;
                // 'toolIsEqual:5' if( tool1.toolno        ~= tool2.toolno )
                if ((r1.b_Tool.toolno == b_CurvStruct.b_Tool.toolno) &&
                    (r1.b_Tool.pocketno == b_CurvStruct.b_Tool.pocketno) &&
                    (r1.b_Tool.diameter == b_CurvStruct.b_Tool.diameter) &&
                    (r1.b_Tool.frontangle == b_CurvStruct.b_Tool.frontangle) &&
                    (r1.b_Tool.backangle == b_CurvStruct.b_Tool.backangle) &&
                    (r1.b_Tool.orientation == b_CurvStruct.b_Tool.orientation) &&
                    (r1.b_Tool.offset.x == b_CurvStruct.b_Tool.offset.x) &&
                    (r1.b_Tool.offset.y == b_CurvStruct.b_Tool.offset.y) &&
                    (r1.b_Tool.offset.z == b_CurvStruct.b_Tool.offset.z) &&
                    (r1.b_Tool.offset.a == b_CurvStruct.b_Tool.offset.a) &&
                    (r1.b_Tool.offset.b == b_CurvStruct.b_Tool.offset.b) &&
                    (r1.b_Tool.offset.c == b_CurvStruct.b_Tool.offset.c) &&
                    (r1.b_Tool.offset.u == b_CurvStruct.b_Tool.offset.u) &&
                    (r1.b_Tool.offset.v == b_CurvStruct.b_Tool.offset.v) &&
                    (r1.b_Tool.offset.w == b_CurvStruct.b_Tool.offset.w)) {
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
                double off[3];
                int CurvStruct_size;
                // 'add_tool_offset:5' prev_off = [prev_tool.offset.x,prev_tool.offset.y,
                // prev_tool.offset.z]; 'add_tool_offset:6' off = [CurvStruct.Tool.offset.x, ...
                // 'add_tool_offset:7'            CurvStruct.Tool.offset.y, ...
                // 'add_tool_offset:8'            CurvStruct.Tool.offset.z];
                off[0] = b_CurvStruct.b_Tool.offset.x;
                off[1] = b_CurvStruct.b_Tool.offset.y;
                off[2] = b_CurvStruct.b_Tool.offset.z;
                // 'add_tool_offset:9' CurvStruct.R0( indCart ) = ...
                // 'add_tool_offset:10'         CurvStruct.R0( indCart ) + prev_off( : );
                if (ctx->cfg.indCart.size[0] == 3) {
                    double b_prev_tool_offset_x[3];
                    int ff_loop_ub;
                    b_prev_tool_offset_x[0] = prev_tool_offset_x;
                    b_prev_tool_offset_x[1] = prev_tool_offset_y;
                    b_prev_tool_offset_x[2] = prev_tool_offset_z;
                    CurvStruct_size = ctx->cfg.indCart.size[0];
                    ff_loop_ub = ctx->cfg.indCart.size[0];
                    for (int i127{0}; i127 < ff_loop_ub; i127++) {
                        CurvStruct_data[i127] = b_CurvStruct.R0[ctx->cfg.indCart.data[i127] - 1] +
                                                b_prev_tool_offset_x[i127];
                    }
                    for (int i135{0}; i135 < CurvStruct_size; i135++) {
                        b_CurvStruct.R0[ctx->cfg.indCart.data[i135] - 1] = CurvStruct_data[i135];
                    }
                } else {
                    binary_expand_op(&b_CurvStruct, ctx, prev_tool_offset_x, prev_tool_offset_y,
                                     prev_tool_offset_z);
                }
                // 'add_tool_offset:11' CurvStruct.R1( indCart ) = ...
                // 'add_tool_offset:12'         CurvStruct.R1( indCart ) + off( : );
                if (ctx->cfg.indCart.size[0] == 3) {
                    int kf_loop_ub;
                    CurvStruct_size = ctx->cfg.indCart.size[0];
                    kf_loop_ub = ctx->cfg.indCart.size[0];
                    for (int i132{0}; i132 < kf_loop_ub; i132++) {
                        CurvStruct_data[i132] =
                            b_CurvStruct.R1[ctx->cfg.indCart.data[i132] - 1] + off[i132];
                    }
                    for (int i137{0}; i137 < CurvStruct_size; i137++) {
                        b_CurvStruct.R1[ctx->cfg.indCart.data[i137] - 1] = CurvStruct_data[i137];
                    }
                } else {
                    binary_expand_op(&b_CurvStruct, ctx, off);
                }
                // 'add_tool_offset:13' if ( CurvStruct.Info.Type == CurveType.Helix )
                if (b_CurvStruct.Info.Type == CurveType_Helix) {
                    // 'add_tool_offset:14' CurvStruct.CorrectedHelixCenter =
                    // CurvStruct.CorrectedHelixCenter + off( : );
                    b_CurvStruct.CorrectedHelixCenter[0] += b_CurvStruct.b_Tool.offset.x;
                    b_CurvStruct.CorrectedHelixCenter[1] += b_CurvStruct.b_Tool.offset.y;
                    b_CurvStruct.CorrectedHelixCenter[2] += b_CurvStruct.b_Tool.offset.z;
                }
            }
            // 'FeedoptPlan:48' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            // 'FeedoptPlan:49' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
            b_CurvStruct.R0[3] *= 0.017453292519943295;
            b_CurvStruct.R1[3] *= 0.017453292519943295;
            b_CurvStruct.R0[4] *= 0.017453292519943295;
            b_CurvStruct.R1[4] *= 0.017453292519943295;
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
    case Fopt_Check: {
        // 'FeedoptPlan:92' case Fopt.Check
        //          [ ctx.q_gcode ] = checkTrafo( ctx, ctx.q_gcode );
        //          histogramLength( ctx, ctx.q_gcode, "Gcode");
        // 'FeedoptPlan:95' if ~ctx.cfg.Cusp.Skip
        if (!ctx->cfg.Cusp.Skip) {
            int ab_loop_ub;
            int ae_loop_ub;
            int bg_loop_ub;
            int bh_loop_ub;
            int ec_loop_ub;
            int ed_loop_ub;
            int f_loop_ub;
            int gf_loop_ub;
            int gg_loop_ub;
            int gh_loop_ub;
            int jc_loop_ub;
            int jd_loop_ub;
            int kb_loop_ub;
            int ke_loop_ub;
            int lg_loop_ub;
            int lh_loop_ub;
            int oc_loop_ub;
            int p_loop_ub;
            int pd_loop_ub;
            int qf_loop_ub;
            int qg_loop_ub;
            int tb_loop_ub;
            int tc_loop_ub;
            int ue_loop_ub;
            int vf_loop_ub;
            int vg_loop_ub;
            int yb_loop_ub;
            int yc_loop_ub;
            // 'FeedoptPlan:96' ctx     = CheckCurvStructs( ctx );
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            f_loop_ub = ctx->BasisVal.size(1);
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                int m_loop_ub;
                m_loop_ub = ctx->BasisVal.size(0);
                for (int i14{0}; i14 < m_loop_ub; i14++) {
                    r.BasisVal[i14 + r.BasisVal.size(0) * i7] =
                        ctx->BasisVal[i14 + ctx->BasisVal.size(0) * i7];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            p_loop_ub = ctx->BasisValD.size(1);
            for (int i17{0}; i17 < p_loop_ub; i17++) {
                int w_loop_ub;
                w_loop_ub = ctx->BasisValD.size(0);
                for (int i24{0}; i24 < w_loop_ub; i24++) {
                    r.BasisValD[i24 + r.BasisValD.size(0) * i17] =
                        ctx->BasisValD[i24 + ctx->BasisValD.size(0) * i17];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            ab_loop_ub = ctx->BasisValDD.size(1);
            for (int i27{0}; i27 < ab_loop_ub; i27++) {
                int hb_loop_ub;
                hb_loop_ub = ctx->BasisValDD.size(0);
                for (int i34{0}; i34 < hb_loop_ub; i34++) {
                    r.BasisValDD[i34 + r.BasisValDD.size(0) * i27] =
                        ctx->BasisValDD[i34 + ctx->BasisValDD.size(0) * i27];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            kb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i37{0}; i37 < kb_loop_ub; i37++) {
                int rb_loop_ub;
                rb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i44{0}; i44 < rb_loop_ub; i44++) {
                    r.BasisValDDD[i44 + r.BasisValDDD.size(0) * i37] =
                        ctx->BasisValDDD[i44 + ctx->BasisValDDD.size(0) * i37];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            tb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i46{0}; i46 < tb_loop_ub; i46++) {
                r.BasisIntegr[i46] = ctx->BasisIntegr[i46];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            yb_loop_ub = ctx->u_vec.size(1);
            for (int i51{0}; i51 < yb_loop_ub; i51++) {
                r.u_vec[i51] = ctx->u_vec[i51];
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
            ec_loop_ub = ctx->cfg.maskTot.size[1];
            if (ec_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ec_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            jc_loop_ub = ctx->cfg.maskCart.size[1];
            if (jc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[jc_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            oc_loop_ub = ctx->cfg.maskRot.size[1];
            if (oc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[oc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            tc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i56{0}; i56 < tc_loop_ub; i56++) {
                r.cfg.indCart[i56] = ctx->cfg.indCart.data[i56];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            yc_loop_ub = ctx->cfg.indRot.size[0];
            for (int i61{0}; i61 < yc_loop_ub; i61++) {
                r.cfg.indRot[i61] = ctx->cfg.indRot.data[i61];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            ed_loop_ub = ctx->cfg.D.size[0];
            for (int i66{0}; i66 < ed_loop_ub; i66++) {
                r.cfg.D[i66] = ctx->cfg.D.data[i66];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            jd_loop_ub = ctx->cfg.kin_params.size[0];
            if (jd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[jd_loop_ub],
                          &r.cfg.kin_params.data[0]);
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
            for (int i76{0}; i76 < 6; i76++) {
                r.cfg.vmax[i76] = ctx->cfg.vmax[i76];
                r.cfg.amax[i76] = ctx->cfg.amax[i76];
                r.cfg.jmax[i76] = ctx->cfg.jmax[i76];
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
            for (int f_i{0}; f_i < 5; f_i++) {
                r.cfg.GaussLegendreX[f_i] = ctx->cfg.GaussLegendreX[f_i];
                r.cfg.GaussLegendreW[f_i] = ctx->cfg.GaussLegendreW[f_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i81{0}; i81 < 9; i81++) {
                r.cfg.LogFileName[i81] = ctx->cfg.LogFileName[i81];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            pd_loop_ub = ctx->Coeff.size(1);
            for (int i87{0}; i87 < pd_loop_ub; i87++) {
                int td_loop_ub;
                td_loop_ub = ctx->Coeff.size(0);
                for (int i91{0}; i91 < td_loop_ub; i91++) {
                    r.Coeff[i91 + r.Coeff.size(0) * i87] =
                        ctx->Coeff[i91 + ctx->Coeff.size(0) * i87];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            CheckCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            ae_loop_ub = r.BasisVal.size(1);
            for (int i97{0}; i97 < ae_loop_ub; i97++) {
                int he_loop_ub;
                he_loop_ub = r.BasisVal.size(0);
                for (int i104{0}; i104 < he_loop_ub; i104++) {
                    ctx->BasisVal[i104 + ctx->BasisVal.size(0) * i97] =
                        r.BasisVal[i104 + r.BasisVal.size(0) * i97];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            ke_loop_ub = r.BasisValD.size(1);
            for (int i107{0}; i107 < ke_loop_ub; i107++) {
                int re_loop_ub;
                re_loop_ub = r.BasisValD.size(0);
                for (int i114{0}; i114 < re_loop_ub; i114++) {
                    ctx->BasisValD[i114 + ctx->BasisValD.size(0) * i107] =
                        r.BasisValD[i114 + r.BasisValD.size(0) * i107];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            ue_loop_ub = r.BasisValDD.size(1);
            for (int i117{0}; i117 < ue_loop_ub; i117++) {
                int cf_loop_ub;
                cf_loop_ub = r.BasisValDD.size(0);
                for (int i124{0}; i124 < cf_loop_ub; i124++) {
                    ctx->BasisValDD[i124 + ctx->BasisValDD.size(0) * i117] =
                        r.BasisValDD[i124 + r.BasisValDD.size(0) * i117];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            gf_loop_ub = r.BasisValDDD.size(1);
            for (int i128{0}; i128 < gf_loop_ub; i128++) {
                int of_loop_ub;
                of_loop_ub = r.BasisValDDD.size(0);
                for (int i138{0}; i138 < of_loop_ub; i138++) {
                    ctx->BasisValDDD[i138 + ctx->BasisValDDD.size(0) * i128] =
                        r.BasisValDDD[i138 + r.BasisValDDD.size(0) * i128];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            qf_loop_ub = r.BasisIntegr.size(0);
            for (int i140{0}; i140 < qf_loop_ub; i140++) {
                ctx->BasisIntegr[i140] = r.BasisIntegr[i140];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            vf_loop_ub = r.u_vec.size(1);
            for (int i145{0}; i145 < vf_loop_ub; i145++) {
                ctx->u_vec[i145] = r.u_vec[i145];
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
            bg_loop_ub = r.cfg.maskTot.size[1];
            if (bg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[bg_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            gg_loop_ub = r.cfg.maskCart.size[1];
            if (gg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[gg_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            lg_loop_ub = r.cfg.maskRot.size[1];
            if (lg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[lg_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            qg_loop_ub = r.cfg.indCart.size(0);
            for (int i150{0}; i150 < qg_loop_ub; i150++) {
                ctx->cfg.indCart.data[i150] = r.cfg.indCart[i150];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            vg_loop_ub = r.cfg.indRot.size(0);
            for (int i155{0}; i155 < vg_loop_ub; i155++) {
                ctx->cfg.indRot.data[i155] = r.cfg.indRot[i155];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            bh_loop_ub = r.cfg.D.size(0);
            for (int i160{0}; i160 < bh_loop_ub; i160++) {
                ctx->cfg.D.data[i160] = r.cfg.D[i160];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            gh_loop_ub = r.cfg.kin_params.size[0];
            if (gh_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[gh_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i165{0}; i165 < 5; i165++) {
                ctx->cfg.kin_type[i165] = r.cfg.kin_type[i165];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i170{0}; i170 < 6; i170++) {
                ctx->cfg.vmax[i170] = r.cfg.vmax[i170];
                ctx->cfg.amax[i170] = r.cfg.amax[i170];
                ctx->cfg.jmax[i170] = r.cfg.jmax[i170];
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
            for (int k_i{0}; k_i < 5; k_i++) {
                ctx->cfg.GaussLegendreX[k_i] = r.cfg.GaussLegendreX[k_i];
                ctx->cfg.GaussLegendreW[k_i] = r.cfg.GaussLegendreW[k_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i175{0}; i175 < 9; i175++) {
                ctx->cfg.LogFileName[i175] = r.cfg.LogFileName[i175];
            }
            ctx->errcode = r.errcode;
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            lh_loop_ub = r.Coeff.size(1);
            for (int i180{0}; i180 < lh_loop_ub; i180++) {
                int qh_loop_ub;
                qh_loop_ub = r.Coeff.size(0);
                for (int i185{0}; i185 < qh_loop_ub; i185++) {
                    ctx->Coeff[i185 + ctx->Coeff.size(0) * i180] =
                        r.Coeff[i185 + r.Coeff.size(0) * i180];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        // 'FeedoptPlan:98' assert( checkZSpdmode( ctx.q_gcode ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:99'             + ".m : Check zspdmode failed " );
        checkZSpdmode(&ctx->q_gcode);
        checkParametrisation(&ctx->q_gcode);
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        // 'FeedoptPlan:105' case Fopt.Compress
        // 'FeedoptPlan:106' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i2;
            unsigned int u;
            // 'FeedoptPlan:107' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i2 = static_cast<int>(u);
            for (int j{0}; j < i2; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:108' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r1);
                ctx->q_compress.push(&r1);
            }
        } else {
            int ag_loop_ub;
            int ah_loop_ub;
            int d_loop_ub;
            int dc_loop_ub;
            int dd_loop_ub;
            int df_loop_ub;
            int fg_loop_ub;
            int fh_loop_ub;
            int ib_loop_ub;
            int ic_loop_ub;
            int id_loop_ub;
            int ie_loop_ub;
            int kg_loop_ub;
            int kh_loop_ub;
            int n_loop_ub;
            int nc_loop_ub;
            int nd_loop_ub;
            int pf_loop_ub;
            int pg_loop_ub;
            int sb_loop_ub;
            int sc_loop_ub;
            int se_loop_ub;
            int uf_loop_ub;
            int ug_loop_ub;
            int x_loop_ub;
            int xb_loop_ub;
            int xc_loop_ub;
            int xd_loop_ub;
            // 'FeedoptPlan:110' else
            // 'FeedoptPlan:111' ctx = compressCurvStructs(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            d_loop_ub = ctx->BasisVal.size(1);
            for (int i5{0}; i5 < d_loop_ub; i5++) {
                int l_loop_ub;
                l_loop_ub = ctx->BasisVal.size(0);
                for (int i13{0}; i13 < l_loop_ub; i13++) {
                    r.BasisVal[i13 + r.BasisVal.size(0) * i5] =
                        ctx->BasisVal[i13 + ctx->BasisVal.size(0) * i5];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            n_loop_ub = ctx->BasisValD.size(1);
            for (int i15{0}; i15 < n_loop_ub; i15++) {
                int v_loop_ub;
                v_loop_ub = ctx->BasisValD.size(0);
                for (int i23{0}; i23 < v_loop_ub; i23++) {
                    r.BasisValD[i23 + r.BasisValD.size(0) * i15] =
                        ctx->BasisValD[i23 + ctx->BasisValD.size(0) * i15];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            x_loop_ub = ctx->BasisValDD.size(1);
            for (int i25{0}; i25 < x_loop_ub; i25++) {
                int gb_loop_ub;
                gb_loop_ub = ctx->BasisValDD.size(0);
                for (int i33{0}; i33 < gb_loop_ub; i33++) {
                    r.BasisValDD[i33 + r.BasisValDD.size(0) * i25] =
                        ctx->BasisValDD[i33 + ctx->BasisValDD.size(0) * i25];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            ib_loop_ub = ctx->BasisValDDD.size(1);
            for (int i35{0}; i35 < ib_loop_ub; i35++) {
                int qb_loop_ub;
                qb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i43{0}; i43 < qb_loop_ub; i43++) {
                    r.BasisValDDD[i43 + r.BasisValDDD.size(0) * i35] =
                        ctx->BasisValDDD[i43 + ctx->BasisValDDD.size(0) * i35];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            sb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i45{0}; i45 < sb_loop_ub; i45++) {
                r.BasisIntegr[i45] = ctx->BasisIntegr[i45];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            xb_loop_ub = ctx->u_vec.size(1);
            for (int i50{0}; i50 < xb_loop_ub; i50++) {
                r.u_vec[i50] = ctx->u_vec[i50];
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
            dc_loop_ub = ctx->cfg.maskTot.size[1];
            if (dc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[dc_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            ic_loop_ub = ctx->cfg.maskCart.size[1];
            if (ic_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[ic_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            nc_loop_ub = ctx->cfg.maskRot.size[1];
            if (nc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[nc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            sc_loop_ub = ctx->cfg.indCart.size[0];
            for (int i55{0}; i55 < sc_loop_ub; i55++) {
                r.cfg.indCart[i55] = ctx->cfg.indCart.data[i55];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            xc_loop_ub = ctx->cfg.indRot.size[0];
            for (int i60{0}; i60 < xc_loop_ub; i60++) {
                r.cfg.indRot[i60] = ctx->cfg.indRot.data[i60];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            dd_loop_ub = ctx->cfg.D.size[0];
            for (int i65{0}; i65 < dd_loop_ub; i65++) {
                r.cfg.D[i65] = ctx->cfg.D.data[i65];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            id_loop_ub = ctx->cfg.kin_params.size[0];
            if (id_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[id_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i70{0}; i70 < 5; i70++) {
                r.cfg.kin_type[i70] = ctx->cfg.kin_type[i70];
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
            for (int i80{0}; i80 < 9; i80++) {
                r.cfg.LogFileName[i80] = ctx->cfg.LogFileName[i80];
            }
            r.errcode = ctx->errcode;
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            nd_loop_ub = ctx->Coeff.size(1);
            for (int i85{0}; i85 < nd_loop_ub; i85++) {
                int sd_loop_ub;
                sd_loop_ub = ctx->Coeff.size(0);
                for (int i90{0}; i90 < sd_loop_ub; i90++) {
                    r.Coeff[i90 + r.Coeff.size(0) * i85] =
                        ctx->Coeff[i90 + ctx->Coeff.size(0) * i85];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            xd_loop_ub = r.BasisVal.size(1);
            for (int i95{0}; i95 < xd_loop_ub; i95++) {
                int ge_loop_ub;
                ge_loop_ub = r.BasisVal.size(0);
                for (int i103{0}; i103 < ge_loop_ub; i103++) {
                    ctx->BasisVal[i103 + ctx->BasisVal.size(0) * i95] =
                        r.BasisVal[i103 + r.BasisVal.size(0) * i95];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            ie_loop_ub = r.BasisValD.size(1);
            for (int i105{0}; i105 < ie_loop_ub; i105++) {
                int qe_loop_ub;
                qe_loop_ub = r.BasisValD.size(0);
                for (int i113{0}; i113 < qe_loop_ub; i113++) {
                    ctx->BasisValD[i113 + ctx->BasisValD.size(0) * i105] =
                        r.BasisValD[i113 + r.BasisValD.size(0) * i105];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            se_loop_ub = r.BasisValDD.size(1);
            for (int i115{0}; i115 < se_loop_ub; i115++) {
                int bf_loop_ub;
                bf_loop_ub = r.BasisValDD.size(0);
                for (int i123{0}; i123 < bf_loop_ub; i123++) {
                    ctx->BasisValDD[i123 + ctx->BasisValDD.size(0) * i115] =
                        r.BasisValDD[i123 + r.BasisValDD.size(0) * i115];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            df_loop_ub = r.BasisValDDD.size(1);
            for (int i125{0}; i125 < df_loop_ub; i125++) {
                int nf_loop_ub;
                nf_loop_ub = r.BasisValDDD.size(0);
                for (int i136{0}; i136 < nf_loop_ub; i136++) {
                    ctx->BasisValDDD[i136 + ctx->BasisValDDD.size(0) * i125] =
                        r.BasisValDDD[i136 + r.BasisValDDD.size(0) * i125];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            pf_loop_ub = r.BasisIntegr.size(0);
            for (int i139{0}; i139 < pf_loop_ub; i139++) {
                ctx->BasisIntegr[i139] = r.BasisIntegr[i139];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            uf_loop_ub = r.u_vec.size(1);
            for (int i144{0}; i144 < uf_loop_ub; i144++) {
                ctx->u_vec[i144] = r.u_vec[i144];
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
            ag_loop_ub = r.cfg.maskTot.size[1];
            if (ag_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ag_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            fg_loop_ub = r.cfg.maskCart.size[1];
            if (fg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[fg_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            kg_loop_ub = r.cfg.maskRot.size[1];
            if (kg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[kg_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            pg_loop_ub = r.cfg.indCart.size(0);
            for (int i149{0}; i149 < pg_loop_ub; i149++) {
                ctx->cfg.indCart.data[i149] = r.cfg.indCart[i149];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            ug_loop_ub = r.cfg.indRot.size(0);
            for (int i154{0}; i154 < ug_loop_ub; i154++) {
                ctx->cfg.indRot.data[i154] = r.cfg.indRot[i154];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            ah_loop_ub = r.cfg.D.size(0);
            for (int i159{0}; i159 < ah_loop_ub; i159++) {
                ctx->cfg.D.data[i159] = r.cfg.D[i159];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            fh_loop_ub = r.cfg.kin_params.size[0];
            if (fh_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[fh_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i164{0}; i164 < 5; i164++) {
                ctx->cfg.kin_type[i164] = r.cfg.kin_type[i164];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i169{0}; i169 < 6; i169++) {
                ctx->cfg.vmax[i169] = r.cfg.vmax[i169];
                ctx->cfg.amax[i169] = r.cfg.amax[i169];
                ctx->cfg.jmax[i169] = r.cfg.jmax[i169];
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
            for (int j_i{0}; j_i < 5; j_i++) {
                ctx->cfg.GaussLegendreX[j_i] = r.cfg.GaussLegendreX[j_i];
                ctx->cfg.GaussLegendreW[j_i] = r.cfg.GaussLegendreW[j_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i174{0}; i174 < 9; i174++) {
                ctx->cfg.LogFileName[i174] = r.cfg.LogFileName[i174];
            }
            ctx->errcode = r.errcode;
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            kh_loop_ub = r.Coeff.size(1);
            for (int i179{0}; i179 < kh_loop_ub; i179++) {
                int ph_loop_ub;
                ph_loop_ub = r.Coeff.size(0);
                for (int i184{0}; i184 < ph_loop_ub; i184++) {
                    ctx->Coeff[i184 + ctx->Coeff.size(0) * i179] =
                        r.Coeff[i184 + r.Coeff.size(0) * i179];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
        }
        // 'FeedoptPlan:114' assert( checkZSpdmode( ctx.q_compress ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:115'             + ".m : compress zspdmode failed " );
        checkZSpdmode(&ctx->q_compress);
        checkParametrisation(&ctx->q_compress);
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:120' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int b_loop_ub;
        int bc_loop_ub;
        int bd_loop_ub;
        int cg_loop_ub;
        int ch_loop_ub;
        int eb_loop_ub;
        int ee_loop_ub;
        int gc_loop_ub;
        int gd_loop_ub;
        int hg_loop_ub;
        int hh_loop_ub;
        int j_loop_ub;
        int lc_loop_ub;
        int ld_loop_ub;
        int lf_loop_ub;
        int mg_loop_ub;
        int ob_loop_ub;
        int oe_loop_ub;
        int qc_loop_ub;
        int rg_loop_ub;
        int sf_loop_ub;
        int t_loop_ub;
        int vb_loop_ub;
        int vc_loop_ub;
        int vd_loop_ub;
        int wf_loop_ub;
        int wg_loop_ub;
        int ye_loop_ub;
        // 'FeedoptPlan:122' case Fopt.Smooth
        //          histogramLength( ctx, ctx.q_compress, "Compressing" );
        // 'FeedoptPlan:125' ctx = smoothCurvStructs(ctx);
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        b_loop_ub = ctx->BasisVal.size(1);
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            int g_loop_ub;
            g_loop_ub = ctx->BasisVal.size(0);
            for (int i8{0}; i8 < g_loop_ub; i8++) {
                r.BasisVal[i8 + r.BasisVal.size(0) * i3] =
                    ctx->BasisVal[i8 + ctx->BasisVal.size(0) * i3];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        j_loop_ub = ctx->BasisValD.size(1);
        for (int i11{0}; i11 < j_loop_ub; i11++) {
            int q_loop_ub;
            q_loop_ub = ctx->BasisValD.size(0);
            for (int i18{0}; i18 < q_loop_ub; i18++) {
                r.BasisValD[i18 + r.BasisValD.size(0) * i11] =
                    ctx->BasisValD[i18 + ctx->BasisValD.size(0) * i11];
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
        eb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i31{0}; i31 < eb_loop_ub; i31++) {
            int lb_loop_ub;
            lb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i38{0}; i38 < lb_loop_ub; i38++) {
                r.BasisValDDD[i38 + r.BasisValDDD.size(0) * i31] =
                    ctx->BasisValDDD[i38 + ctx->BasisValDDD.size(0) * i31];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        ob_loop_ub = ctx->BasisIntegr.size(0);
        for (int i41{0}; i41 < ob_loop_ub; i41++) {
            r.BasisIntegr[i41] = ctx->BasisIntegr[i41];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        vb_loop_ub = ctx->u_vec.size(1);
        for (int i48{0}; i48 < vb_loop_ub; i48++) {
            r.u_vec[i48] = ctx->u_vec[i48];
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
        bc_loop_ub = ctx->cfg.maskTot.size[1];
        if (bc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[bc_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        gc_loop_ub = ctx->cfg.maskCart.size[1];
        if (gc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[gc_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        lc_loop_ub = ctx->cfg.maskRot.size[1];
        if (lc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[lc_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        qc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i53{0}; i53 < qc_loop_ub; i53++) {
            r.cfg.indCart[i53] = ctx->cfg.indCart.data[i53];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        vc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i58{0}; i58 < vc_loop_ub; i58++) {
            r.cfg.indRot[i58] = ctx->cfg.indRot.data[i58];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        bd_loop_ub = ctx->cfg.D.size[0];
        for (int i63{0}; i63 < bd_loop_ub; i63++) {
            r.cfg.D[i63] = ctx->cfg.D.data[i63];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        gd_loop_ub = ctx->cfg.kin_params.size[0];
        if (gd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[gd_loop_ub],
                      &r.cfg.kin_params.data[0]);
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
        for (int i78{0}; i78 < 9; i78++) {
            r.cfg.LogFileName[i78] = ctx->cfg.LogFileName[i78];
        }
        r.errcode = ctx->errcode;
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        ld_loop_ub = ctx->Coeff.size(1);
        for (int i83{0}; i83 < ld_loop_ub; i83++) {
            int qd_loop_ub;
            qd_loop_ub = ctx->Coeff.size(0);
            for (int i88{0}; i88 < qd_loop_ub; i88++) {
                r.Coeff[i88 + r.Coeff.size(0) * i83] = ctx->Coeff[i88 + ctx->Coeff.size(0) * i83];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        smoothCurvStructs(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        vd_loop_ub = r.BasisVal.size(1);
        for (int i93{0}; i93 < vd_loop_ub; i93++) {
            int be_loop_ub;
            be_loop_ub = r.BasisVal.size(0);
            for (int i98{0}; i98 < be_loop_ub; i98++) {
                ctx->BasisVal[i98 + ctx->BasisVal.size(0) * i93] =
                    r.BasisVal[i98 + r.BasisVal.size(0) * i93];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        ee_loop_ub = r.BasisValD.size(1);
        for (int i101{0}; i101 < ee_loop_ub; i101++) {
            int le_loop_ub;
            le_loop_ub = r.BasisValD.size(0);
            for (int i108{0}; i108 < le_loop_ub; i108++) {
                ctx->BasisValD[i108 + ctx->BasisValD.size(0) * i101] =
                    r.BasisValD[i108 + r.BasisValD.size(0) * i101];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        oe_loop_ub = r.BasisValDD.size(1);
        for (int i111{0}; i111 < oe_loop_ub; i111++) {
            int ve_loop_ub;
            ve_loop_ub = r.BasisValDD.size(0);
            for (int i118{0}; i118 < ve_loop_ub; i118++) {
                ctx->BasisValDD[i118 + ctx->BasisValDD.size(0) * i111] =
                    r.BasisValDD[i118 + r.BasisValDD.size(0) * i111];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        ye_loop_ub = r.BasisValDDD.size(1);
        for (int i121{0}; i121 < ye_loop_ub; i121++) {
            int hf_loop_ub;
            hf_loop_ub = r.BasisValDDD.size(0);
            for (int i129{0}; i129 < hf_loop_ub; i129++) {
                ctx->BasisValDDD[i129 + ctx->BasisValDDD.size(0) * i121] =
                    r.BasisValDDD[i129 + r.BasisValDDD.size(0) * i121];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        lf_loop_ub = r.BasisIntegr.size(0);
        for (int i133{0}; i133 < lf_loop_ub; i133++) {
            ctx->BasisIntegr[i133] = r.BasisIntegr[i133];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        sf_loop_ub = r.u_vec.size(1);
        for (int i142{0}; i142 < sf_loop_ub; i142++) {
            ctx->u_vec[i142] = r.u_vec[i142];
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
        wf_loop_ub = r.cfg.maskTot.size[1];
        if (wf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[wf_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        cg_loop_ub = r.cfg.maskCart.size[1];
        if (cg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[cg_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        hg_loop_ub = r.cfg.maskRot.size[1];
        if (hg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[hg_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        mg_loop_ub = r.cfg.indCart.size(0);
        for (int i146{0}; i146 < mg_loop_ub; i146++) {
            ctx->cfg.indCart.data[i146] = r.cfg.indCart[i146];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        rg_loop_ub = r.cfg.indRot.size(0);
        for (int i151{0}; i151 < rg_loop_ub; i151++) {
            ctx->cfg.indRot.data[i151] = r.cfg.indRot[i151];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        wg_loop_ub = r.cfg.D.size(0);
        for (int i156{0}; i156 < wg_loop_ub; i156++) {
            ctx->cfg.D.data[i156] = r.cfg.D[i156];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        ch_loop_ub = r.cfg.kin_params.size[0];
        if (ch_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[ch_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i161{0}; i161 < 5; i161++) {
            ctx->cfg.kin_type[i161] = r.cfg.kin_type[i161];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i166{0}; i166 < 6; i166++) {
            ctx->cfg.vmax[i166] = r.cfg.vmax[i166];
            ctx->cfg.amax[i166] = r.cfg.amax[i166];
            ctx->cfg.jmax[i166] = r.cfg.jmax[i166];
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
        for (int i171{0}; i171 < 9; i171++) {
            ctx->cfg.LogFileName[i171] = r.cfg.LogFileName[i171];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        hh_loop_ub = r.Coeff.size(1);
        for (int i176{0}; i176 < hh_loop_ub; i176++) {
            int mh_loop_ub;
            mh_loop_ub = r.Coeff.size(0);
            for (int i181{0}; i181 < mh_loop_ub; i181++) {
                ctx->Coeff[i181 + ctx->Coeff.size(0) * i176] =
                    r.Coeff[i181 + r.Coeff.size(0) * i176];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:126' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:128' assert( checkZSpdmode( ctx.q_smooth ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:129'             + ".m : smooth zspdmode failed " );
        checkZSpdmode(&r.q_smooth);
        checkParametrisation(&r.q_smooth);
    } break;
    case Fopt_Split: {
        int af_loop_ub;
        int c_loop_ub;
        int cc_loop_ub;
        int cd_loop_ub;
        int dg_loop_ub;
        int dh_loop_ub;
        int fb_loop_ub;
        int fe_loop_ub;
        int hc_loop_ub;
        int hd_loop_ub;
        int ig_loop_ub;
        int ih_loop_ub;
        int k_loop_ub;
        int mc_loop_ub;
        int md_loop_ub;
        int mf_loop_ub;
        int ng_loop_ub;
        int pb_loop_ub;
        int pe_loop_ub;
        int rc_loop_ub;
        int sg_loop_ub;
        int tf_loop_ub;
        int u_loop_ub;
        int wb_loop_ub;
        int wc_loop_ub;
        int wd_loop_ub;
        int xf_loop_ub;
        int xg_loop_ub;
        // 'FeedoptPlan:135' case Fopt.Split
        //          histogramLength( ctx, ctx.q_smooth, "Smoothing" );
        // 'FeedoptPlan:138' ctx = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        c_loop_ub = ctx->BasisVal.size(1);
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            int h_loop_ub;
            h_loop_ub = ctx->BasisVal.size(0);
            for (int i9{0}; i9 < h_loop_ub; i9++) {
                r.BasisVal[i9 + r.BasisVal.size(0) * i4] =
                    ctx->BasisVal[i9 + ctx->BasisVal.size(0) * i4];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        k_loop_ub = ctx->BasisValD.size(1);
        for (int i12{0}; i12 < k_loop_ub; i12++) {
            int r_loop_ub;
            r_loop_ub = ctx->BasisValD.size(0);
            for (int i19{0}; i19 < r_loop_ub; i19++) {
                r.BasisValD[i19 + r.BasisValD.size(0) * i12] =
                    ctx->BasisValD[i19 + ctx->BasisValD.size(0) * i12];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        u_loop_ub = ctx->BasisValDD.size(1);
        for (int i22{0}; i22 < u_loop_ub; i22++) {
            int cb_loop_ub;
            cb_loop_ub = ctx->BasisValDD.size(0);
            for (int i29{0}; i29 < cb_loop_ub; i29++) {
                r.BasisValDD[i29 + r.BasisValDD.size(0) * i22] =
                    ctx->BasisValDD[i29 + ctx->BasisValDD.size(0) * i22];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        fb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i32{0}; i32 < fb_loop_ub; i32++) {
            int mb_loop_ub;
            mb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i39{0}; i39 < mb_loop_ub; i39++) {
                r.BasisValDDD[i39 + r.BasisValDDD.size(0) * i32] =
                    ctx->BasisValDDD[i39 + ctx->BasisValDDD.size(0) * i32];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        pb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i42{0}; i42 < pb_loop_ub; i42++) {
            r.BasisIntegr[i42] = ctx->BasisIntegr[i42];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        wb_loop_ub = ctx->u_vec.size(1);
        for (int i49{0}; i49 < wb_loop_ub; i49++) {
            r.u_vec[i49] = ctx->u_vec[i49];
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
        cc_loop_ub = ctx->cfg.maskTot.size[1];
        if (cc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[cc_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        hc_loop_ub = ctx->cfg.maskCart.size[1];
        if (hc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[hc_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        mc_loop_ub = ctx->cfg.maskRot.size[1];
        if (mc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[mc_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        rc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i54{0}; i54 < rc_loop_ub; i54++) {
            r.cfg.indCart[i54] = ctx->cfg.indCart.data[i54];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        wc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i59{0}; i59 < wc_loop_ub; i59++) {
            r.cfg.indRot[i59] = ctx->cfg.indRot.data[i59];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        cd_loop_ub = ctx->cfg.D.size[0];
        for (int i64{0}; i64 < cd_loop_ub; i64++) {
            r.cfg.D[i64] = ctx->cfg.D.data[i64];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        hd_loop_ub = ctx->cfg.kin_params.size[0];
        if (hd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[hd_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i69{0}; i69 < 5; i69++) {
            r.cfg.kin_type[i69] = ctx->cfg.kin_type[i69];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i74{0}; i74 < 6; i74++) {
            r.cfg.vmax[i74] = ctx->cfg.vmax[i74];
            r.cfg.amax[i74] = ctx->cfg.amax[i74];
            r.cfg.jmax[i74] = ctx->cfg.jmax[i74];
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
        md_loop_ub = ctx->Coeff.size(1);
        for (int i84{0}; i84 < md_loop_ub; i84++) {
            int rd_loop_ub;
            rd_loop_ub = ctx->Coeff.size(0);
            for (int i89{0}; i89 < rd_loop_ub; i89++) {
                r.Coeff[i89 + r.Coeff.size(0) * i84] = ctx->Coeff[i89 + ctx->Coeff.size(0) * i84];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        splitQueue(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        wd_loop_ub = r.BasisVal.size(1);
        for (int i94{0}; i94 < wd_loop_ub; i94++) {
            int ce_loop_ub;
            ce_loop_ub = r.BasisVal.size(0);
            for (int i99{0}; i99 < ce_loop_ub; i99++) {
                ctx->BasisVal[i99 + ctx->BasisVal.size(0) * i94] =
                    r.BasisVal[i99 + r.BasisVal.size(0) * i94];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        fe_loop_ub = r.BasisValD.size(1);
        for (int i102{0}; i102 < fe_loop_ub; i102++) {
            int me_loop_ub;
            me_loop_ub = r.BasisValD.size(0);
            for (int i109{0}; i109 < me_loop_ub; i109++) {
                ctx->BasisValD[i109 + ctx->BasisValD.size(0) * i102] =
                    r.BasisValD[i109 + r.BasisValD.size(0) * i102];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        pe_loop_ub = r.BasisValDD.size(1);
        for (int i112{0}; i112 < pe_loop_ub; i112++) {
            int we_loop_ub;
            we_loop_ub = r.BasisValDD.size(0);
            for (int i119{0}; i119 < we_loop_ub; i119++) {
                ctx->BasisValDD[i119 + ctx->BasisValDD.size(0) * i112] =
                    r.BasisValDD[i119 + r.BasisValDD.size(0) * i112];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        af_loop_ub = r.BasisValDDD.size(1);
        for (int i122{0}; i122 < af_loop_ub; i122++) {
            int if_loop_ub;
            if_loop_ub = r.BasisValDDD.size(0);
            for (int i130{0}; i130 < if_loop_ub; i130++) {
                ctx->BasisValDDD[i130 + ctx->BasisValDDD.size(0) * i122] =
                    r.BasisValDDD[i130 + r.BasisValDDD.size(0) * i122];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        mf_loop_ub = r.BasisIntegr.size(0);
        for (int i134{0}; i134 < mf_loop_ub; i134++) {
            ctx->BasisIntegr[i134] = r.BasisIntegr[i134];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        tf_loop_ub = r.u_vec.size(1);
        for (int i143{0}; i143 < tf_loop_ub; i143++) {
            ctx->u_vec[i143] = r.u_vec[i143];
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
        xf_loop_ub = r.cfg.maskTot.size[1];
        if (xf_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[xf_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        dg_loop_ub = r.cfg.maskCart.size[1];
        if (dg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[dg_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        ig_loop_ub = r.cfg.maskRot.size[1];
        if (ig_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[ig_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        ng_loop_ub = r.cfg.indCart.size(0);
        for (int i147{0}; i147 < ng_loop_ub; i147++) {
            ctx->cfg.indCart.data[i147] = r.cfg.indCart[i147];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        sg_loop_ub = r.cfg.indRot.size(0);
        for (int i152{0}; i152 < sg_loop_ub; i152++) {
            ctx->cfg.indRot.data[i152] = r.cfg.indRot[i152];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        xg_loop_ub = r.cfg.D.size(0);
        for (int i157{0}; i157 < xg_loop_ub; i157++) {
            ctx->cfg.D.data[i157] = r.cfg.D[i157];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        dh_loop_ub = r.cfg.kin_params.size[0];
        if (dh_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[dh_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i162{0}; i162 < 5; i162++) {
            ctx->cfg.kin_type[i162] = r.cfg.kin_type[i162];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i167{0}; i167 < 6; i167++) {
            ctx->cfg.vmax[i167] = r.cfg.vmax[i167];
            ctx->cfg.amax[i167] = r.cfg.amax[i167];
            ctx->cfg.jmax[i167] = r.cfg.jmax[i167];
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
        for (int h_i{0}; h_i < 5; h_i++) {
            ctx->cfg.GaussLegendreX[h_i] = r.cfg.GaussLegendreX[h_i];
            ctx->cfg.GaussLegendreW[h_i] = r.cfg.GaussLegendreW[h_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i172{0}; i172 < 9; i172++) {
            ctx->cfg.LogFileName[i172] = r.cfg.LogFileName[i172];
        }
        ctx->errcode = r.errcode;
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        ih_loop_ub = r.Coeff.size(1);
        for (int i177{0}; i177 < ih_loop_ub; i177++) {
            int nh_loop_ub;
            nh_loop_ub = r.Coeff.size(0);
            for (int i182{0}; i182 < nh_loop_ub; i182++) {
                ctx->Coeff[i182 + ctx->Coeff.size(0) * i177] =
                    r.Coeff[i182 + r.Coeff.size(0) * i177];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        // 'FeedoptPlan:140' ctx.op = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:142' assert( checkZSpdmode( ctx.q_split ), "ERROR : " + mfilename ...
        // 'FeedoptPlan:143'             + ".m : splitted zspdmode failed " );
        checkZSpdmode(&r.q_split);
        checkParametrisation(&r.q_smooth);
    } break;
    case Fopt_Opt: {
        int ac_loop_ub;
        int ad_loop_ub;
        int db_loop_ub;
        int de_loop_ub;
        int eg_loop_ub;
        int eh_loop_ub;
        int fc_loop_ub;
        int fd_loop_ub;
        int i_loop_ub;
        int jf_loop_ub;
        int jg_loop_ub;
        int jh_loop_ub;
        int kc_loop_ub;
        int kd_loop_ub;
        int loop_ub;
        int nb_loop_ub;
        int ne_loop_ub;
        int og_loop_ub;
        int pc_loop_ub;
        int rf_loop_ub;
        int s_loop_ub;
        int tg_loop_ub;
        int ub_loop_ub;
        int uc_loop_ub;
        int ud_loop_ub;
        int xe_loop_ub;
        int yf_loop_ub;
        int yg_loop_ub;
        // 'FeedoptPlan:150' case Fopt.Opt
        // 'FeedoptPlan:151' [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
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
        i_loop_ub = ctx->BasisValD.size(1);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            int o_loop_ub;
            o_loop_ub = ctx->BasisValD.size(0);
            for (int i16{0}; i16 < o_loop_ub; i16++) {
                b_ctx.BasisValD[i16 + b_ctx.BasisValD.size(0) * i10] =
                    ctx->BasisValD[i16 + ctx->BasisValD.size(0) * i10];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        s_loop_ub = ctx->BasisValDD.size(1);
        for (int i20{0}; i20 < s_loop_ub; i20++) {
            int y_loop_ub;
            y_loop_ub = ctx->BasisValDD.size(0);
            for (int i26{0}; i26 < y_loop_ub; i26++) {
                b_ctx.BasisValDD[i26 + b_ctx.BasisValDD.size(0) * i20] =
                    ctx->BasisValDD[i26 + ctx->BasisValDD.size(0) * i20];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        db_loop_ub = ctx->BasisValDDD.size(1);
        for (int i30{0}; i30 < db_loop_ub; i30++) {
            int jb_loop_ub;
            jb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i36{0}; i36 < jb_loop_ub; i36++) {
                b_ctx.BasisValDDD[i36 + b_ctx.BasisValDDD.size(0) * i30] =
                    ctx->BasisValDDD[i36 + ctx->BasisValDDD.size(0) * i30];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        nb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i40{0}; i40 < nb_loop_ub; i40++) {
            b_ctx.BasisIntegr[i40] = ctx->BasisIntegr[i40];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        ub_loop_ub = ctx->u_vec.size(1);
        for (int i47{0}; i47 < ub_loop_ub; i47++) {
            b_ctx.u_vec[i47] = ctx->u_vec[i47];
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
        ac_loop_ub = ctx->cfg.maskTot.size[1];
        if (ac_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ac_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        fc_loop_ub = ctx->cfg.maskCart.size[1];
        if (fc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[fc_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        kc_loop_ub = ctx->cfg.maskRot.size[1];
        if (kc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[kc_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        pc_loop_ub = ctx->cfg.indCart.size[0];
        for (int i52{0}; i52 < pc_loop_ub; i52++) {
            b_ctx.cfg.indCart[i52] = ctx->cfg.indCart.data[i52];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        uc_loop_ub = ctx->cfg.indRot.size[0];
        for (int i57{0}; i57 < uc_loop_ub; i57++) {
            b_ctx.cfg.indRot[i57] = ctx->cfg.indRot.data[i57];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.D.set_size(ctx->cfg.D.size[0]);
        ad_loop_ub = ctx->cfg.D.size[0];
        for (int i62{0}; i62 < ad_loop_ub; i62++) {
            b_ctx.cfg.D[i62] = ctx->cfg.D.data[i62];
        }
        b_ctx.cfg.coeffD = ctx->cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        fd_loop_ub = ctx->cfg.kin_params.size[0];
        if (fd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[fd_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i67{0}; i67 < 5; i67++) {
            b_ctx.cfg.kin_type[i67] = ctx->cfg.kin_type[i67];
        }
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        b_ctx.cfg.fmax = ctx->cfg.fmax;
        b_ctx.cfg.smax = ctx->cfg.smax;
        for (int i72{0}; i72 < 6; i72++) {
            b_ctx.cfg.vmax[i72] = ctx->cfg.vmax[i72];
            b_ctx.cfg.amax[i72] = ctx->cfg.amax[i72];
            b_ctx.cfg.jmax[i72] = ctx->cfg.jmax[i72];
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
        for (int i77{0}; i77 < 9; i77++) {
            b_ctx.cfg.LogFileName[i77] = ctx->cfg.LogFileName[i77];
        }
        b_ctx.errcode = ctx->errcode;
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        kd_loop_ub = ctx->Coeff.size(1);
        for (int i82{0}; i82 < kd_loop_ub; i82++) {
            int od_loop_ub;
            od_loop_ub = ctx->Coeff.size(0);
            for (int i86{0}; i86 < od_loop_ub; i86++) {
                b_ctx.Coeff[i86 + b_ctx.Coeff.size(0) * i82] =
                    ctx->Coeff[i86 + ctx->Coeff.size(0) * i82];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        feedratePlanning(&b_ctx, &c_optimized, opt_struct, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        ud_loop_ub = b_ctx.BasisVal.size(1);
        for (int i92{0}; i92 < ud_loop_ub; i92++) {
            int yd_loop_ub;
            yd_loop_ub = b_ctx.BasisVal.size(0);
            for (int i96{0}; i96 < yd_loop_ub; i96++) {
                ctx->BasisVal[i96 + ctx->BasisVal.size(0) * i92] =
                    b_ctx.BasisVal[i96 + b_ctx.BasisVal.size(0) * i92];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        de_loop_ub = b_ctx.BasisValD.size(1);
        for (int i100{0}; i100 < de_loop_ub; i100++) {
            int je_loop_ub;
            je_loop_ub = b_ctx.BasisValD.size(0);
            for (int i106{0}; i106 < je_loop_ub; i106++) {
                ctx->BasisValD[i106 + ctx->BasisValD.size(0) * i100] =
                    b_ctx.BasisValD[i106 + b_ctx.BasisValD.size(0) * i100];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        ne_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i110{0}; i110 < ne_loop_ub; i110++) {
            int te_loop_ub;
            te_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i116{0}; i116 < te_loop_ub; i116++) {
                ctx->BasisValDD[i116 + ctx->BasisValDD.size(0) * i110] =
                    b_ctx.BasisValDD[i116 + b_ctx.BasisValDD.size(0) * i110];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        xe_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i120{0}; i120 < xe_loop_ub; i120++) {
            int ef_loop_ub;
            ef_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i126{0}; i126 < ef_loop_ub; i126++) {
                ctx->BasisValDDD[i126 + ctx->BasisValDDD.size(0) * i120] =
                    b_ctx.BasisValDDD[i126 + b_ctx.BasisValDDD.size(0) * i120];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        jf_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i131{0}; i131 < jf_loop_ub; i131++) {
            ctx->BasisIntegr[i131] = b_ctx.BasisIntegr[i131];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        rf_loop_ub = b_ctx.u_vec.size(1);
        for (int i141{0}; i141 < rf_loop_ub; i141++) {
            ctx->u_vec[i141] = b_ctx.u_vec[i141];
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
        yf_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (yf_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[yf_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        eg_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (eg_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[eg_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        jg_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (jg_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[jg_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        og_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i148{0}; i148 < og_loop_ub; i148++) {
            ctx->cfg.indCart.data[i148] = b_ctx.cfg.indCart[i148];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        tg_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i153{0}; i153 < tg_loop_ub; i153++) {
            ctx->cfg.indRot.data[i153] = b_ctx.cfg.indRot[i153];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        yg_loop_ub = b_ctx.cfg.D.size(0);
        for (int i158{0}; i158 < yg_loop_ub; i158++) {
            ctx->cfg.D.data[i158] = b_ctx.cfg.D[i158];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        eh_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (eh_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[eh_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i163{0}; i163 < 5; i163++) {
            ctx->cfg.kin_type[i163] = b_ctx.cfg.kin_type[i163];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        ctx->cfg.fmax = b_ctx.cfg.fmax;
        ctx->cfg.smax = b_ctx.cfg.smax;
        for (int i168{0}; i168 < 6; i168++) {
            ctx->cfg.vmax[i168] = b_ctx.cfg.vmax[i168];
            ctx->cfg.amax[i168] = b_ctx.cfg.amax[i168];
            ctx->cfg.jmax[i168] = b_ctx.cfg.jmax[i168];
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
        for (int i_i{0}; i_i < 5; i_i++) {
            ctx->cfg.GaussLegendreX[i_i] = b_ctx.cfg.GaussLegendreX[i_i];
            ctx->cfg.GaussLegendreW[i_i] = b_ctx.cfg.GaussLegendreW[i_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i173{0}; i173 < 9; i173++) {
            ctx->cfg.LogFileName[i173] = b_ctx.cfg.LogFileName[i173];
        }
        ctx->errcode = b_ctx.errcode;
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        jh_loop_ub = b_ctx.Coeff.size(1);
        for (int i178{0}; i178 < jh_loop_ub; i178++) {
            int oh_loop_ub;
            oh_loop_ub = b_ctx.Coeff.size(0);
            for (int i183{0}; i183 < oh_loop_ub; i183++) {
                ctx->Coeff[i183 + ctx->Coeff.size(0) * i178] =
                    b_ctx.Coeff[i183 + b_ctx.Coeff.size(0) * i178];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        b_optimized = c_optimized;
        // 'FeedoptPlan:152' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:153' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:154' ctx.q_opt.push( opt_struct );
            b_ctx.q_opt.push(opt_struct);
        }
        // 'FeedoptPlan:157' if( quit )
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:159' case Fopt.Finished
        // 'FeedoptPlan:160' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:162' otherwise
        // 'FeedoptPlan:163' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:164' ctx.op = Fopt.Finished;
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
