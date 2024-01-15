
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptPlan.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "FeedoptPlan.h"
#include "CheckCurvStructs.h"
#include "Kinematics.h"
#include "ReadGCode.h"
#include "add_tool_offset.h"
#include "checkGeometry.h"
#include "checkParametrisationQueue.h"
#include "checkZSpdmode.h"
#include "compressCurvStructs.h"
#include "constrCurvStruct.h"
#include "feedratePlanning.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "smoothCurvStructs.h"
#include "splitQueue.h"
#include "string1.h"
#include "toolIsEqual.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include "cpp_interp.hpp"
#include <algorithm>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function [ ctx, optimized, opt_struct ] = FeedoptPlan( ctx )
//
// FeedoptPlan : Feedrate optimisation Finite State Machine (FSM).
//
//  Inputs :
//  ctx        : The context of the computational chain
//
//  Outputs :
//  ctx        : The context of the computational chain
//  optimized  : Bolean value used to say if the curve has been optimized
//  opt_struct : Optimized structure
//
//
// Arguments    : FeedoptContext *ctx
//                bool *optimized
//                CurvStruct *opt_struct
// Return Type  : void
//
namespace ocn {
void FeedoptPlan(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct)
{
    static const char c_obj2Value[34]{' ', '-', ' ', 'C', 'h', 'e', 'c', 'k', ' ', 'p', 'a', 'r',
                                      'a', 'm', 'e', 't', 'r', 'i', 's', 'a', 't', 'i', 'o', 'n',
                                      ' ', 'f', 'a', 'i', 'l', 'e', 'd', '.', '.', '.'};
    static const char b_obj2Value[27]{' ', '-', ' ', 'C', 'h', 'e', 'c', 'k', ' ',
                                      'z', 's', 'p', 'd', 'm', 'o', 'd', 'e', ' ',
                                      'f', 'a', 'i', 'l', 'e', 'd', '.', '.', '.'};
    static const char obj2Value[27]{' ', '-', ' ', 'C', 'h', 'e', 'c', 'k', ' ',
                                    'g', 'e', 'o', 'm', 'e', 't', 'r', 'y', ' ',
                                    'f', 'a', 'i', 'l', 'e', 'd', '.', '.', '.'};
    static const char obj1Value[6]{'[', 'L', 'i', 'n', 'e', ' '};
    coder::rtString b_obj;
    coder::rtString c_obj;
    coder::rtString d_obj;
    coder::rtString obj;
    coder::rtString r3;
    Axes params_tool_offset;
    CurvStruct c_CurvStruct;
    CurvStruct curv1;
    CurvStruct last;
    CurvStruct r2;
    MsgStruct err_msg;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
    b_FeedoptContext b_ctx;
    b_FeedoptContext r;
    b_FeedoptContext r1;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double off[3];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    char tmp_data[1025];
    char obj2Value_data[11];
    bool b_optimized;
    bool c_optimized;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    bool quit;
    CurveType params_gcodeInfoStruct_Type;
    ReadGCodeError status;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptPlan:13' optimized = false;
    b_optimized = false;
    // 'FeedoptPlan:15' opt_struct = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                      &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                      &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                      &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                      &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                      &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                      &params_tool_backangle, &params_tool_orientation, &params_spline, params_R0,
                      params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp, &c_expl_temp,
                      params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                       params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                       params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                       params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                       params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                       &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                       params_tool_backangle, params_tool_orientation, &params_spline, params_R0,
                       params_R1, params_Cprim, params_evec, params_CoeffP5, &e_expl_temp);
    opt_struct->Info = e_expl_temp.Info;
    opt_struct->tool = e_expl_temp.tool;
    opt_struct->sp = e_expl_temp.sp;
    opt_struct->R0.set_size(e_expl_temp.R0.size[0]);
    loop_ub = e_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        opt_struct->R0[i] = e_expl_temp.R0.data[i];
    }
    opt_struct->R1.set_size(e_expl_temp.R1.size[0]);
    b_loop_ub = e_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        opt_struct->R1[i1] = e_expl_temp.R1.data[i1];
    }
    opt_struct->delta = e_expl_temp.delta;
    opt_struct->CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    opt_struct->evec[0] = e_expl_temp.evec[0];
    opt_struct->CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    opt_struct->evec[1] = e_expl_temp.evec[1];
    opt_struct->CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    opt_struct->evec[2] = e_expl_temp.evec[2];
    opt_struct->theta = e_expl_temp.theta;
    opt_struct->pitch = e_expl_temp.pitch;
    opt_struct->CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    c_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            opt_struct->CoeffP5[i3 + opt_struct->CoeffP5.size(0) * i2] =
                e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    opt_struct->sp_index = e_expl_temp.sp_index;
    opt_struct->i_begin_sp = e_expl_temp.i_begin_sp;
    opt_struct->i_end_sp = e_expl_temp.i_end_sp;
    opt_struct->index_smooth = e_expl_temp.index_smooth;
    opt_struct->UseConstJerk = e_expl_temp.UseConstJerk;
    opt_struct->ConstJerk = e_expl_temp.ConstJerk;
    opt_struct->Coeff.set_size(e_expl_temp.Coeff.size(0));
    e_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        opt_struct->Coeff[i4] = e_expl_temp.Coeff[i4];
    }
    opt_struct->a_param = e_expl_temp.a_param;
    opt_struct->b_param = e_expl_temp.b_param;
    //  See InitFeedoptPlan for information about the context variable ctx
    // 'FeedoptPlan:18' ocn_assert( ctx.errcode == FeedoptPlanError.NoError, ...
    // 'FeedoptPlan:19'     "FeedoptPlan: error code was not handled...", mfilename );
    g_ocn_assert(ctx->errcode == FeedoptPlanError_NoError);
    // 'FeedoptPlan:21' switch ctx.op
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:22' case Fopt.Init
        // 'FeedoptPlan:23' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        //
        break;
    case Fopt_GCode: {
        int obj2Value_size[2];
        int ao_loop_ub;
        int bl_loop_ub;
        int bp_loop_ub;
        int cp_loop_ub;
        int el_loop_ub;
        int eo_loop_ub;
        int fi_loop_ub;
        int ii_loop_ub;
        int il_loop_ub;
        int io_loop_ub;
        int ke_loop_ub;
        int kk_loop_ub;
        int km_loop_ub;
        int li_loop_ub;
        int mk_loop_ub;
        int mn_loop_ub;
        int nn_loop_ub;
        int no_loop_ub;
        int oi_loop_ub;
        int on_loop_ub;
        int oo_loop_ub;
        int po_loop_ub;
        int qo_loop_ub;
        int ro_loop_ub;
        int si_loop_ub;
        int sk_loop_ub;
        int sn_loop_ub;
        int td_loop_ub;
        int ue_loop_ub;
        int uo_loop_ub;
        int vh_loop_ub;
        int vo_loop_ub;
        int wl_loop_ub;
        int wm_loop_ub;
        int wn_loop_ub;
        int yk_loop_ub;
        bool exitg1;
        bool i_isValid;
        bool j_isValid;
        bool zeroFlag;
        // 'FeedoptPlan:25' case Fopt.GCode
        // 'FeedoptPlan:26' ctx.k0      = int32( 1 );
        ctx->k0 = 1;
        // 'FeedoptPlan:27' status      = ReadGCode( ctx.cfg, ReadGCodeCmd.Load, ctx.cfg.source );
        //  ReadGCode : Read the G code contents.
        //
        //  Inputs :
        //    cfg :           The configuration structure.
        //    cmd :           The command operation.
        //    filename :      The G code filename.
        //
        //  Outputs :
        //    status :        The current status of the reading operation
        //    CurvStruct :    The curve structure
        //    err_msg :       The error message
        //
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:18' status          = ReadGCodeError.InterpError;
        // 'ReadGCode:19' CurvStruct      = constrCurvStructType;
        // 'ReadGCode:20' err_msg         = constrMsgStructType;
        std::copy(&cv1[0], &cv1[2048], &err_msg.msg[0]);
        err_msg.size = 2048.0;
        // 'ReadGCode:22' if coder.target('matlab')
        // 'ReadGCode:60' else
        // 'ReadGCode:61' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
        // 'ReadGCode:63' my_path = StructTypeName.WDIR + "/src";
        // 'ReadGCode:64' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'ReadGCode:66' pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
        //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
        // 'ReadGCode:68' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
        // 'ReadGCode:69' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path);
        // 'ReadGCode:70' coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
        // 'ReadGCode:71' coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc',
        // pathRs274Src); 'ReadGCode:72' coder.updateBuildInfo('addSourceFiles','interp_arc.cc',
        // pathRs274Src); 'ReadGCode:73' coder.updateBuildInfo('addSourceFiles','interp_array.cc',
        // pathRs274Src); 'ReadGCode:74' coder.updateBuildInfo('addSourceFiles','interp_base.cc',
        // pathRs274Src); 'ReadGCode:75' coder.updateBuildInfo('addSourceFiles','interp_check.cc',
        // pathRs274Src); 'ReadGCode:76' coder.updateBuildInfo('addSourceFiles','interp_convert.cc',
        // pathRs274Src); 'ReadGCode:77' coder.updateBuildInfo('addSourceFiles','interp_cycles.cc',
        // pathRs274Src); 'ReadGCode:78' coder.updateBuildInfo('addSourceFiles','interp_execute.cc',
        // pathRs274Src); 'ReadGCode:79' coder.updateBuildInfo('addSourceFiles','interp_find.cc',
        // pathRs274Src); 'ReadGCode:80'
        // coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
        // 'ReadGCode:81' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
        // 'ReadGCode:82' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
        // pathRs274Src); 'ReadGCode:83' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
        // pathRs274Src); 'ReadGCode:84' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
        // pathRs274Src); 'ReadGCode:85' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
        // pathRs274Src); 'ReadGCode:86' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
        // pathRs274Src); 'ReadGCode:87' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
        // pathRs274Src); 'ReadGCode:88' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
        // pathRs274Src); 'ReadGCode:89' coder.updateBuildInfo('addSourceFiles','ocn.cc',
        // pathRs274Src); 'ReadGCode:90' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc',
        // pathRs274Src); 'ReadGCode:91' coder.updateBuildInfo('addSourceFiles','inifile.cc',
        // pathRs274Src); 'ReadGCode:92' coder.updateBuildInfo('addLinkFlags', '-ldl');
        //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
        // 'ReadGCode:94' coder.cinclude('cpp_interp.hpp');
        // 'ReadGCode:96' switch cmd
        // 'ReadGCode:97' case ReadGCodeCmd.Load
        // 'ReadGCode:98' status = coder.ceval( 'cpp_interp_init', [filename 0], coder.ref(err_msg)
        // );
        td_loop_ub = ctx->cfg.source.size[1];
        if (td_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[td_loop_ub], &tmp_data[0]);
        }
        tmp_data[ctx->cfg.source.size[1]] = '\x00';
        status = cpp_interp_init(&tmp_data[0], &err_msg);
        // 'ReadGCode:110' if(0)
        // 'ReadGCode:115' ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
        // 'ReadGCode:116'     "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
        // 'ReadGCode:117'     err_msg.msg( 1 : err_msg.size ), mfilename );
        if (err_msg.size < 1.0) {
            ke_loop_ub = 0;
        } else {
            ke_loop_ub = static_cast<int>(err_msg.size);
        }
        coder::rtString::convertToString(obj2Value_data, obj2Value_size);
        obj.Value.size[0] = 1;
        obj.Value.size[1] = (obj2Value_size[1] + ke_loop_ub) + 8;
        for (int i95{0}; i95 < 6; i95++) {
            obj.Value.data[i95] = obj1Value[i95];
        }
        ue_loop_ub = obj2Value_size[1];
        if (ue_loop_ub - 1 >= 0) {
            std::copy(&obj2Value_data[0], &obj2Value_data[ue_loop_ub], &obj.Value.data[6]);
        }
        obj.Value.data[obj2Value_size[1] + 6] = ']';
        obj.Value.data[obj2Value_size[1] + 7] = ' ';
        for (int i103{0}; i103 < ke_loop_ub; i103++) {
            obj.Value.data[(i103 + obj2Value_size[1]) + 8] = err_msg.msg[i103];
        }
        f_ocn_assert(status < ReadGCodeError_InterpNotOpen, &obj);
        // 'FeedoptPlan:28' CurvStruct  = opt_struct;
        c_CurvStruct = *opt_struct;
        // 'FeedoptPlan:29' CurvStruct.Info.Type = CurveType.None;
        c_CurvStruct.Info.Type = CurveType_None;
        // 'FeedoptPlan:30' DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
        //  DebugLog : Print msg in log pipe.
        //
        //  Inputs :
        //  cfg       : The configuration structure
        //  varargin  : Variable types of arguments (a.k.a print msg)
        //
        // 'DebugLog:9' if IsEnabledDebugLog( cfg )
        //  IsEnableDebugLog : Is the Debug log enable
        //
        //  Inputs :
        //    cfg : Configuration structure
        //
        //  Outputs :
        //  Value : Boolean Value. TRUE means the debug log is enable.
        //
        // 'IsEnabledDebugLog:13' value = false;
        // 'IsEnabledDebugLog:15' if bitget( DebugConfig, int32( cfg ) )
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:16' value = true;
            //    Output
            //    stdout : 1
            //    stderr : 2
            // 'DebugLog:13' output  = 1;
            // 'DebugLog:14' fprintf( output, varargin{ : } );
            printf("Reading G-code...\n");
            fflush(stdout);
        }
        //
        // 'FeedoptPlan:32' while status < ReadGCodeError.InterpNotOpen
        exitg1 = false;
        while ((!exitg1) && (status < ReadGCodeError_InterpNotOpen)) {
            // 'FeedoptPlan:33' if( CurvStruct.Info.Type ~= CurveType.None )
            if (c_CurvStruct.Info.Type != CurveType_None) {
                // 'FeedoptPlan:34' ctx.q_gcode.push( CurvStruct );
                ctx->q_gcode.push(&c_CurvStruct);
                // 'FeedoptPlan:35' ctx.k0 = ctx.k0 + 1;
                ctx->k0++;
            }
            // 'FeedoptPlan:38' if( status == ReadGCodeError.InterpExit )
            if (status == ReadGCodeError_InterpExit) {
                exitg1 = true;
            } else {
                // 'FeedoptPlan:42' [ status, CurvStruct ] = ReadGCode( ctx.cfg, ReadGCodeCmd.Read,
                // ... 'FeedoptPlan:43'                 ctx.cfg.source );
                b_ReadGCode(&status, &c_CurvStruct);
                // 'FeedoptPlan:45' if( CurvStruct.Info.Type ~= CurveType.None )
                if (c_CurvStruct.Info.Type != CurveType_None) {
                    __m128d r4;
                    __m128d r5;
                    __m128d r6;
                    double prev_tool_offset_x;
                    double prev_tool_offset_y;
                    double prev_tool_offset_z;
                    // 'FeedoptPlan:46' if( ctx.q_gcode.isempty )
                    if (ctx->q_gcode.isempty()) {
                        // 'FeedoptPlan:47' prev_tool = constrToolStructType;
                        prev_tool_offset_x = 0.0;
                        prev_tool_offset_y = 0.0;
                        prev_tool_offset_z = 0.0;
                    } else {
                        // 'FeedoptPlan:48' else
                        // 'FeedoptPlan:49' prev_tool = ctx.q_gcode.rget(1).tool;
                        ctx->q_gcode.rget(&r2);
                        prev_tool_offset_x = r2.tool.offset.x;
                        prev_tool_offset_y = r2.tool.offset.y;
                        prev_tool_offset_z = r2.tool.offset.z;
                        // 'FeedoptPlan:51' if( ~toolIsEqual(prev_tool, CurvStruct.tool ) )
                        if (!toolIsEqual(r2.tool.toolno, r2.tool.pocketno, r2.tool.offset.x,
                                         r2.tool.offset.y, r2.tool.offset.z, r2.tool.offset.a,
                                         r2.tool.offset.b, r2.tool.offset.c, r2.tool.offset.u,
                                         r2.tool.offset.v, r2.tool.offset.w, r2.tool.diameter,
                                         r2.tool.frontangle, r2.tool.backangle, r2.tool.orientation,
                                         c_CurvStruct.tool.toolno, c_CurvStruct.tool.pocketno,
                                         &c_CurvStruct.tool.offset, c_CurvStruct.tool.diameter,
                                         c_CurvStruct.tool.frontangle, c_CurvStruct.tool.backangle,
                                         c_CurvStruct.tool.orientation)) {
                            bool b_zeroFlag;
                            bool c_zeroFlag;
                            // 'FeedoptPlan:52' curv1 = ctx.q_gcode.rget(1);
                            ctx->q_gcode.rget(&curv1);
                            // 'FeedoptPlan:53' if( isAZeroStart(curv1) )
                            //  isAZeroStart : Return true if the curv starts with zero speed
                            //
                            //  Inputs :
                            //  curv / Info / ZSpdMode : A structure containning the information of
                            //  the curv zero speed.
                            //
                            //  Outputs :
                            //  zeroflag : Boolean value. TRUE means zero structure with a zero
                            //  speed.
                            //
                            // 'isAZeroStart:11' zeroFlag = false;
                            b_zeroFlag = false;
                            // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                            //  getZspdmode: Get the current zero speed mode
                            //
                            //  Inputs :
                            //    speed    : structure with zspdmode for the speed
                            //
                            //  Outputs :
                            //    zspdmode : Zero speed mode
                            //    error    : Error bolean value. TRUE if no zspdmode has been found.
                            //
                            // 'getZspdmode:13' error = false;
                            // 'getZspdmode:15' if( isenum( speed ) )
                            // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                            // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                            // 'isAZeroStart:15' if( error )
                            // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                            // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                            if ((curv1.Info.zspdmode == ZSpdMode_ZN) ||
                                (curv1.Info.zspdmode == ZSpdMode_ZZ)) {
                                // 'isAZeroStart:19' zeroFlag = true;
                                b_zeroFlag = true;
                            }
                            if (b_zeroFlag) {
                                // 'FeedoptPlan:54' curv1.Info.zspdmode = ZSpdMode.ZZ;
                                curv1.Info.zspdmode = ZSpdMode_ZZ;
                            } else {
                                // 'FeedoptPlan:55' else
                                // 'FeedoptPlan:56' curv1.Info.zspdmode = ZSpdMode.NZ;
                                curv1.Info.zspdmode = ZSpdMode_NZ;
                            }
                            // 'FeedoptPlan:59' ctx.q_gcode.set(ctx.q_gcode.size, curv1);
                            ctx->q_gcode.set(ctx->q_gcode.size(), &curv1);
                            // 'FeedoptPlan:61' if( isAZeroEnd(CurvStruct) )
                            //  isAZeroEnd : Return true if the curv ends with zero speed
                            //
                            //  Inputs :
                            //  curv / Info / ZSpdMode : A structure containning the information of
                            //  the curv zero speed.
                            //
                            //  Outputs :
                            //  zeroFlag : Boolean value. TRUE mean zero flag
                            // 'isAZeroEnd:10' zeroFlag = false;
                            c_zeroFlag = false;
                            // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
                            //  getZspdmode: Get the current zero speed mode
                            //
                            //  Inputs :
                            //    speed    : structure with zspdmode for the speed
                            //
                            //  Outputs :
                            //    zspdmode : Zero speed mode
                            //    error    : Error bolean value. TRUE if no zspdmode has been found.
                            //
                            // 'getZspdmode:13' error = false;
                            // 'getZspdmode:15' if( isenum( speed ) )
                            // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                            // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                            // 'isAZeroEnd:14' if( error )
                            // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
                            // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
                            if ((c_CurvStruct.Info.zspdmode == ZSpdMode_NZ) ||
                                (c_CurvStruct.Info.zspdmode == ZSpdMode_ZZ)) {
                                // 'isAZeroEnd:18' zeroFlag = true;
                                c_zeroFlag = true;
                            }
                            if (c_zeroFlag) {
                                // 'FeedoptPlan:62' CurvStruct.Info.zspdmode = ZSpdMode.ZZ;
                                c_CurvStruct.Info.zspdmode = ZSpdMode_ZZ;
                            } else {
                                // 'FeedoptPlan:63' else
                                // 'FeedoptPlan:64' CurvStruct.Info.zspdmode = ZSpdMode.ZN;
                                c_CurvStruct.Info.zspdmode = ZSpdMode_ZN;
                            }
                        }
                    }
                    // 'FeedoptPlan:69' [CurvStruct] = add_tool_offset( CurvStruct, ...
                    // 'FeedoptPlan:70'                     ctx.cfg.indCart, prev_tool );
                    //  add_tool_offset : Add the tool offset to the curve structure.
                    //
                    //  Inputs :
                    //  CurvStruct    : Curv structure
                    //  indCart       : Index carthesien
                    //  prev_tool     : Previous tool
                    //
                    //  Outputs:
                    //  CurvStruct    : Curv structure
                    // 'add_tool_offset:13' if( ~CurvStruct.Info.TRAFO )
                    if (!c_CurvStruct.Info.TRAFO) {
                        double CurvStruct_data[3];
                        int CurvStruct_size;
                        // 'add_tool_offset:14' prev_off = [prev_tool.offset.x,prev_tool.offset.y,
                        // prev_tool.offset.z]; 'add_tool_offset:15' off =
                        // [CurvStruct.tool.offset.x, ... 'add_tool_offset:16'
                        // CurvStruct.tool.offset.y, ... 'add_tool_offset:17'
                        // CurvStruct.tool.offset.z];
                        off[0] = c_CurvStruct.tool.offset.x;
                        off[1] = c_CurvStruct.tool.offset.y;
                        off[2] = c_CurvStruct.tool.offset.z;
                        // 'add_tool_offset:18' CurvStruct.R0( indCart ) = ...
                        // 'add_tool_offset:19'         CurvStruct.R0( indCart ) + prev_off( : );
                        if (ctx->cfg.indCart.size[0] == 3) {
                            double b_prev_tool_offset_x[3];
                            int di_loop_ub;
                            b_prev_tool_offset_x[0] = prev_tool_offset_x;
                            b_prev_tool_offset_x[1] = prev_tool_offset_y;
                            b_prev_tool_offset_x[2] = prev_tool_offset_z;
                            CurvStruct_size = ctx->cfg.indCart.size[0];
                            di_loop_ub = ctx->cfg.indCart.size[0];
                            for (int i188{0}; i188 < di_loop_ub; i188++) {
                                CurvStruct_data[i188] =
                                    c_CurvStruct.R0[ctx->cfg.indCart.data[i188] - 1] +
                                    b_prev_tool_offset_x[i188];
                            }
                            for (int i193{0}; i193 < CurvStruct_size; i193++) {
                                c_CurvStruct.R0[ctx->cfg.indCart.data[i193] - 1] =
                                    CurvStruct_data[i193];
                            }
                        } else {
                            binary_expand_op(&c_CurvStruct, ctx, prev_tool_offset_x,
                                             prev_tool_offset_y, prev_tool_offset_z);
                        }
                        // 'add_tool_offset:20' CurvStruct.R1( indCart ) = ...
                        // 'add_tool_offset:21'         CurvStruct.R1( indCart ) + off( : );
                        if (ctx->cfg.indCart.size[0] == 3) {
                            int gi_loop_ub;
                            CurvStruct_size = ctx->cfg.indCart.size[0];
                            gi_loop_ub = ctx->cfg.indCart.size[0];
                            for (int i191{0}; i191 < gi_loop_ub; i191++) {
                                CurvStruct_data[i191] =
                                    c_CurvStruct.R1[ctx->cfg.indCart.data[i191] - 1] + off[i191];
                            }
                            for (int i194{0}; i194 < CurvStruct_size; i194++) {
                                c_CurvStruct.R1[ctx->cfg.indCart.data[i194] - 1] =
                                    CurvStruct_data[i194];
                            }
                        } else {
                            binary_expand_op(&c_CurvStruct, ctx, off);
                        }
                        // 'add_tool_offset:22' if ( CurvStruct.Info.Type == CurveType.Helix )
                        if (c_CurvStruct.Info.Type == CurveType_Helix) {
                            __m128d r7;
                            __m128d r8;
                            // 'add_tool_offset:23' CurvStruct.CorrectedHelixCenter =
                            // CurvStruct.CorrectedHelixCenter + off( : );
                            r7 = _mm_loadu_pd(&c_CurvStruct.CorrectedHelixCenter[0]);
                            r8 = _mm_loadu_pd(&off[0]);
                            _mm_storeu_pd(&c_CurvStruct.CorrectedHelixCenter[0],
                                          _mm_add_pd(r7, r8));
                            c_CurvStruct.CorrectedHelixCenter[2] += off[2];
                        }
                    }
                    //  Convert degree to rad
                    // 'FeedoptPlan:72' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end )
                    // );
                    r4 = _mm_loadu_pd(&c_CurvStruct.R0[3]);
                    r5 = _mm_set1_pd(0.017453292519943295);
                    _mm_storeu_pd(&c_CurvStruct.R0[3], _mm_mul_pd(r5, r4));
                    c_CurvStruct.R0[5] = 0.017453292519943295 * c_CurvStruct.R0[5];
                    // 'FeedoptPlan:73' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end )
                    // );
                    r6 = _mm_loadu_pd(&c_CurvStruct.R1[3]);
                    _mm_storeu_pd(&c_CurvStruct.R1[3], _mm_mul_pd(r5, r6));
                    c_CurvStruct.R1[5] = 0.017453292519943295 * c_CurvStruct.R1[5];
                    // 'FeedoptPlan:75' for j = 1 : StructTypeName.NumberAxisMax
                    // 'FeedoptPlan:84' ocn_assert( CurvStruct.Info.FeedRate > 0.0, ...
                    // 'FeedoptPlan:85'                     "Feedrate is not valide...", mfilename
                    // );
                    h_ocn_assert(c_CurvStruct.Info.FeedRate > 0.0);
                }
            }
        }
        //  Error if gcode queue is empty
        // 'FeedoptPlan:90' ocn_assert( ~ctx.q_gcode.isempty(), "Gcode queue is empty", mfilename );
        i_ocn_assert(!ctx->q_gcode.isempty());
        // 'FeedoptPlan:92' last = ctx.q_gcode.rget(1);
        ctx->q_gcode.rget(&last);
        // 'FeedoptPlan:93' if( isAZeroStart(last) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //
        //  Inputs :
        //  curv / Info / ZSpdMode : A structure containning the information of the
        //  curv zero speed.
        //
        //  Outputs :
        //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
        //
        // 'isAZeroStart:11' zeroFlag = false;
        zeroFlag = false;
        // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
        //  getZspdmode: Get the current zero speed mode
        //
        //  Inputs :
        //    speed    : structure with zspdmode for the speed
        //
        //  Outputs :
        //    zspdmode : Zero speed mode
        //    error    : Error bolean value. TRUE if no zspdmode has been found.
        //
        // 'getZspdmode:13' error = false;
        // 'getZspdmode:15' if( isenum( speed ) )
        // 'getZspdmode:17' elseif( isfield( speed, "Info") )
        // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
        // 'isAZeroStart:15' if( error )
        // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
        if ((last.Info.zspdmode == ZSpdMode_ZN) || (last.Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:19' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'FeedoptPlan:94' last.Info.zspdmode = ZSpdMode.ZZ;
            last.Info.zspdmode = ZSpdMode_ZZ;
        } else {
            // 'FeedoptPlan:95' else
            // 'FeedoptPlan:96' last.Info.zspdmode = ZSpdMode.NZ;
            last.Info.zspdmode = ZSpdMode_NZ;
        }
        // 'FeedoptPlan:98' ctx.q_gcode.set( ctx.q_gcode.size, last );
        ctx->q_gcode.set(ctx->q_gcode.size(), &last);
        // 'FeedoptPlan:100' ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        vh_loop_ub = ctx->BasisVal.size(1);
        for (int i182{0}; i182 < vh_loop_ub; i182++) {
            int ci_loop_ub;
            ci_loop_ub = ctx->BasisVal.size(0);
            for (int i187{0}; i187 < ci_loop_ub; i187++) {
                r.BasisVal[i187 + r.BasisVal.size(0) * i182] =
                    ctx->BasisVal[i187 + ctx->BasisVal.size(0) * i182];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        fi_loop_ub = ctx->BasisValD.size(1);
        for (int i190{0}; i190 < fi_loop_ub; i190++) {
            int hi_loop_ub;
            hi_loop_ub = ctx->BasisValD.size(0);
            for (int i195{0}; i195 < hi_loop_ub; i195++) {
                r.BasisValD[i195 + r.BasisValD.size(0) * i190] =
                    ctx->BasisValD[i195 + ctx->BasisValD.size(0) * i190];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        ii_loop_ub = ctx->BasisValDD.size(1);
        for (int i196{0}; i196 < ii_loop_ub; i196++) {
            int ki_loop_ub;
            ki_loop_ub = ctx->BasisValDD.size(0);
            for (int i197{0}; i197 < ki_loop_ub; i197++) {
                r.BasisValDD[i197 + r.BasisValDD.size(0) * i196] =
                    ctx->BasisValDD[i197 + ctx->BasisValDD.size(0) * i196];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        li_loop_ub = ctx->BasisValDDD.size(1);
        for (int i199{0}; i199 < li_loop_ub; i199++) {
            int ni_loop_ub;
            ni_loop_ub = ctx->BasisValDDD.size(0);
            for (int i200{0}; i200 < ni_loop_ub; i200++) {
                r.BasisValDDD[i200 + r.BasisValDDD.size(0) * i199] =
                    ctx->BasisValDDD[i200 + ctx->BasisValDDD.size(0) * i199];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        oi_loop_ub = ctx->BasisIntegr.size(0);
        for (int i201{0}; i201 < oi_loop_ub; i201++) {
            r.BasisIntegr[i201] = ctx->BasisIntegr[i201];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        si_loop_ub = ctx->u_vec.size(1);
        for (int i206{0}; i206 < si_loop_ub; i206++) {
            r.u_vec[i206] = ctx->u_vec[i206];
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
        r.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        kk_loop_ub = ctx->cfg.maskTot.size[1];
        if (kk_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[kk_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        mk_loop_ub = ctx->cfg.maskCart.size[1];
        if (mk_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[mk_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        sk_loop_ub = ctx->cfg.maskRot.size[1];
        if (sk_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[sk_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        yk_loop_ub = ctx->cfg.indCart.size[0];
        for (int i243{0}; i243 < yk_loop_ub; i243++) {
            r.cfg.indCart[i243] = ctx->cfg.indCart.data[i243];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        bl_loop_ub = ctx->cfg.indRot.size[0];
        for (int i245{0}; i245 < bl_loop_ub; i245++) {
            r.cfg.indRot[i245] = ctx->cfg.indRot.data[i245];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        el_loop_ub = ctx->cfg.D.size[0];
        for (int i251{0}; i251 < el_loop_ub; i251++) {
            r.cfg.D[i251] = ctx->cfg.D.data[i251];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        il_loop_ub = ctx->cfg.kin_params.size[0];
        if (il_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[il_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i253{0}; i253 < 8; i253++) {
            r.cfg.kin_type[i253] = ctx->cfg.kin_type[i253];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        r.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        for (int i258{0}; i258 < 6; i258++) {
            r.cfg.vmax[i258] = ctx->cfg.vmax[i258];
            r.cfg.amax[i258] = ctx->cfg.amax[i258];
            r.cfg.jmax[i258] = ctx->cfg.jmax[i258];
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
        r.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        r.cfg.source.size[0] = 1;
        r.cfg.source.size[1] = ctx->cfg.source.size[1];
        wl_loop_ub = ctx->cfg.source.size[1];
        if (wl_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[wl_loop_ub],
                      &r.cfg.source.data[0]);
        }
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int n_i{0}; n_i < 5; n_i++) {
            r.cfg.GaussLegendreX[n_i] = ctx->cfg.GaussLegendreX[n_i];
            r.cfg.GaussLegendreW[n_i] = ctx->cfg.GaussLegendreW[n_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i279{0}; i279 < 9; i279++) {
            r.cfg.LogFileName[i279] = ctx->cfg.LogFileName[i279];
        }
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.zero_forced = ctx->zero_forced;
        r.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        r.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        km_loop_ub = ctx->Coeff.size(1);
        for (int i280{0}; i280 < km_loop_ub; i280++) {
            int mm_loop_ub;
            mm_loop_ub = ctx->Coeff.size(0);
            for (int i283{0}; i283 < mm_loop_ub; i283++) {
                r.Coeff[i283 + r.Coeff.size(0) * i280] =
                    ctx->Coeff[i283 + ctx->Coeff.size(0) * i280];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        r.errmsg = ctx->errmsg;
        r.errcode = ctx->errcode;
        // 'FeedoptPlan:172' msg = string( op );
        // 'FeedoptPlan:173' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:174'     msg + " - Check geometry failed...", mfilename );
        r3.init(ctx->op);
        b_obj.Value.size[0] = 1;
        b_obj.Value.size[1] = r3.Value.size[1] + 27;
        wm_loop_ub = r3.Value.size[1];
        if (wm_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[wm_loop_ub], &b_obj.Value.data[0]);
        }
        for (int i297{0}; i297 < 27; i297++) {
            b_obj.Value.data[i297 + r3.Value.size[1]] = obj2Value[i297];
        }
        j_ocn_assert(checkGeometry(&ctx->q_gcode), &b_obj);
        // 'FeedoptPlan:176' [ isValid, ctx ] = checkZSpdmode( ctx, queue );
        i_isValid = checkZSpdmode(&r, &ctx->q_gcode);
        // 'FeedoptPlan:177' ocn_assert( isValid, ...
        // 'FeedoptPlan:178'     msg + " - Check zspdmode failed...", mfilename );
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r3.Value.size[1] + 27;
        mn_loop_ub = r3.Value.size[1];
        if (mn_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[mn_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i309{0}; i309 < 27; i309++) {
            c_obj.Value.data[i309 + r3.Value.size[1]] = b_obj2Value[i309];
        }
        j_ocn_assert(i_isValid, &c_obj);
        // 'FeedoptPlan:180' isValid = checkParametrisationQueue( queue );
        j_isValid = checkParametrisationQueue(&ctx->q_gcode);
        // 'FeedoptPlan:181' ocn_assert( isValid, ...
        // 'FeedoptPlan:182'     msg + " - Check parametrisation failed...", mfilename );
        d_obj.Value.size[0] = 1;
        d_obj.Value.size[1] = r3.Value.size[1] + 34;
        nn_loop_ub = r3.Value.size[1];
        if (nn_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[nn_loop_ub], &d_obj.Value.data[0]);
        }
        for (int i310{0}; i310 < 34; i310++) {
            d_obj.Value.data[i310 + r3.Value.size[1]] = c_obj2Value[i310];
        }
        j_ocn_assert(j_isValid, &d_obj);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        on_loop_ub = r.BasisVal.size(1);
        for (int i311{0}; i311 < on_loop_ub; i311++) {
            int rn_loop_ub;
            rn_loop_ub = r.BasisVal.size(0);
            for (int i312{0}; i312 < rn_loop_ub; i312++) {
                ctx->BasisVal[i312 + ctx->BasisVal.size(0) * i311] =
                    r.BasisVal[i312 + r.BasisVal.size(0) * i311];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        sn_loop_ub = r.BasisValD.size(1);
        for (int i313{0}; i313 < sn_loop_ub; i313++) {
            int un_loop_ub;
            un_loop_ub = r.BasisValD.size(0);
            for (int i314{0}; i314 < un_loop_ub; i314++) {
                ctx->BasisValD[i314 + ctx->BasisValD.size(0) * i313] =
                    r.BasisValD[i314 + r.BasisValD.size(0) * i313];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        wn_loop_ub = r.BasisValDD.size(1);
        for (int i315{0}; i315 < wn_loop_ub; i315++) {
            int xn_loop_ub;
            xn_loop_ub = r.BasisValDD.size(0);
            for (int i316{0}; i316 < xn_loop_ub; i316++) {
                ctx->BasisValDD[i316 + ctx->BasisValDD.size(0) * i315] =
                    r.BasisValDD[i316 + r.BasisValDD.size(0) * i315];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        ao_loop_ub = r.BasisValDDD.size(1);
        for (int i317{0}; i317 < ao_loop_ub; i317++) {
            int co_loop_ub;
            co_loop_ub = r.BasisValDDD.size(0);
            for (int i318{0}; i318 < co_loop_ub; i318++) {
                ctx->BasisValDDD[i318 + ctx->BasisValDDD.size(0) * i317] =
                    r.BasisValDDD[i318 + r.BasisValDDD.size(0) * i317];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        eo_loop_ub = r.BasisIntegr.size(0);
        for (int i320{0}; i320 < eo_loop_ub; i320++) {
            ctx->BasisIntegr[i320] = r.BasisIntegr[i320];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        io_loop_ub = r.u_vec.size(1);
        for (int i324{0}; i324 < io_loop_ub; i324++) {
            ctx->u_vec[i324] = r.u_vec[i324];
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
        ctx->cfg.ENABLE_PRINT_MSG = r.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
        no_loop_ub = r.cfg.maskTot.size[1];
        if (no_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[no_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        oo_loop_ub = r.cfg.maskCart.size[1];
        if (oo_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[oo_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        po_loop_ub = r.cfg.maskRot.size[1];
        if (po_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[po_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        qo_loop_ub = r.cfg.indCart.size(0);
        for (int i331{0}; i331 < qo_loop_ub; i331++) {
            ctx->cfg.indCart.data[i331] = r.cfg.indCart[i331];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        ro_loop_ub = r.cfg.indRot.size(0);
        for (int i332{0}; i332 < ro_loop_ub; i332++) {
            ctx->cfg.indRot.data[i332] = r.cfg.indRot[i332];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        uo_loop_ub = r.cfg.D.size(0);
        for (int i333{0}; i333 < uo_loop_ub; i333++) {
            ctx->cfg.D.data[i333] = r.cfg.D[i333];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        vo_loop_ub = r.cfg.kin_params.size[0];
        if (vo_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[vo_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i336{0}; i336 < 8; i336++) {
            ctx->cfg.kin_type[i336] = r.cfg.kin_type[i336];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = r.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = r.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        for (int i338{0}; i338 < 6; i338++) {
            ctx->cfg.vmax[i338] = r.cfg.vmax[i338];
            ctx->cfg.amax[i338] = r.cfg.amax[i338];
            ctx->cfg.jmax[i338] = r.cfg.jmax[i338];
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
        ctx->cfg.DefaultZeroStopCount = r.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = r.cfg.source.size[1];
        bp_loop_ub = r.cfg.source.size[1];
        if (bp_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.source.data[0], &r.cfg.source.data[bp_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = r.cfg.Cusp;
        ctx->cfg.Compressing = r.cfg.Compressing;
        ctx->cfg.Smoothing = r.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int s_i{0}; s_i < 5; s_i++) {
            ctx->cfg.GaussLegendreX[s_i] = r.cfg.GaussLegendreX[s_i];
            ctx->cfg.GaussLegendreW[s_i] = r.cfg.GaussLegendreW[s_i];
        }
        ctx->cfg.opt = r.cfg.opt;
        for (int i342{0}; i342 < 9; i342++) {
            ctx->cfg.LogFileName[i342] = r.cfg.LogFileName[i342];
        }
        ctx->jmax_increase_count = r.jmax_increase_count;
        ctx->zero_start = r.zero_start;
        ctx->zero_end = r.zero_end;
        ctx->zero_forced = r.zero_forced;
        ctx->zero_forced_buffer[0] = r.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = r.zero_forced_buffer[1];
        ctx->simplex_calls = r.simplex_calls;
        ctx->forced_stop = r.forced_stop;
        ctx->programmed_stop = r.programmed_stop;
        ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        cp_loop_ub = r.Coeff.size(1);
        for (int i343{0}; i343 < cp_loop_ub; i343++) {
            int dp_loop_ub;
            dp_loop_ub = r.Coeff.size(0);
            for (int i344{0}; i344 < dp_loop_ub; i344++) {
                ctx->Coeff[i344 + ctx->Coeff.size(0) * i343] =
                    r.Coeff[i344 + r.Coeff.size(0) * i343];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        ctx->errmsg = r.errmsg;
        ctx->errcode = r.errcode;
        // 'FeedoptPlan:102' ctx.op = Fopt.Check;
        ctx->op = Fopt_Check;
    } break;
    case Fopt_Check: {
        int al_loop_ub;
        int bn_loop_ub;
        int cl_loop_ub;
        int dd_loop_ub;
        int ff_loop_ub;
        int fj_loop_ub;
        int fl_loop_ub;
        int ge_loop_ub;
        int hb_loop_ub;
        int hl_loop_ub;
        int i_loop_ub;
        int im_loop_ub;
        int jd_loop_ub;
        int jg_loop_ub;
        int ji_loop_ub;
        int kc_loop_ub;
        int kl_loop_ub;
        int mf_loop_ub;
        int nl_loop_ub;
        int oj_loop_ub;
        int pe_loop_ub;
        int pi_loop_ub;
        int qd_loop_ub;
        int qh_loop_ub;
        int ri_loop_ub;
        int t_loop_ub;
        int tl_loop_ub;
        int uc_loop_ub;
        int vb_loop_ub;
        int we_loop_ub;
        int xi_loop_ub;
        int xj_loop_ub;
        int yd_loop_ub;
        bool c_isValid;
        bool isValid;
        // 'FeedoptPlan:104' case Fopt.Check
        // 'FeedoptPlan:105' if ~ctx.cfg.Cusp.Skip
        if (!ctx->cfg.Cusp.Skip) {
            int cd_loop_ub;
            int ch_loop_ub;
            int ef_loop_ub;
            int fb_loop_ub;
            int fe_loop_ub;
            int fg_loop_ub;
            int fk_loop_ub;
            int gj_loop_ub;
            int h_loop_ub;
            int ic_loop_ub;
            int id_loop_ub;
            int lf_loop_ub;
            int mh_loop_ub;
            int nk_loop_ub;
            int oe_loop_ub;
            int ol_loop_ub;
            int pd_loop_ub;
            int qg_loop_ub;
            int qj_loop_ub;
            int r_loop_ub;
            int sc_loop_ub;
            int tb_loop_ub;
            int tk_loop_ub;
            int ve_loop_ub;
            int vi_loop_ub;
            int wf_loop_ub;
            int wh_loop_ub;
            int xd_loop_ub;
            int xl_loop_ub;
            int yj_loop_ub;
            // 'FeedoptPlan:106' ctx     = CheckCurvStructs( ctx );
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            h_loop_ub = ctx->BasisVal.size(1);
            for (int i8{0}; i8 < h_loop_ub; i8++) {
                int p_loop_ub;
                p_loop_ub = ctx->BasisVal.size(0);
                for (int i16{0}; i16 < p_loop_ub; i16++) {
                    r.BasisVal[i16 + r.BasisVal.size(0) * i8] =
                        ctx->BasisVal[i16 + ctx->BasisVal.size(0) * i8];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            r_loop_ub = ctx->BasisValD.size(1);
            for (int i18{0}; i18 < r_loop_ub; i18++) {
                int db_loop_ub;
                db_loop_ub = ctx->BasisValD.size(0);
                for (int i29{0}; i29 < db_loop_ub; i29++) {
                    r.BasisValD[i29 + r.BasisValD.size(0) * i18] =
                        ctx->BasisValD[i29 + ctx->BasisValD.size(0) * i18];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            fb_loop_ub = ctx->BasisValDD.size(1);
            for (int i31{0}; i31 < fb_loop_ub; i31++) {
                int rb_loop_ub;
                rb_loop_ub = ctx->BasisValDD.size(0);
                for (int i43{0}; i43 < rb_loop_ub; i43++) {
                    r.BasisValDD[i43 + r.BasisValDD.size(0) * i31] =
                        ctx->BasisValDD[i43 + ctx->BasisValDD.size(0) * i31];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            tb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i45{0}; i45 < tb_loop_ub; i45++) {
                int gc_loop_ub;
                gc_loop_ub = ctx->BasisValDDD.size(0);
                for (int i57{0}; i57 < gc_loop_ub; i57++) {
                    r.BasisValDDD[i57 + r.BasisValDDD.size(0) * i45] =
                        ctx->BasisValDDD[i57 + ctx->BasisValDDD.size(0) * i45];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            ic_loop_ub = ctx->BasisIntegr.size(0);
            for (int i59{0}; i59 < ic_loop_ub; i59++) {
                r.BasisIntegr[i59] = ctx->BasisIntegr[i59];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            sc_loop_ub = ctx->u_vec.size(1);
            for (int i69{0}; i69 < sc_loop_ub; i69++) {
                r.u_vec[i69] = ctx->u_vec[i69];
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
            r.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
            r.cfg.maskTot.size[0] = 1;
            r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
            cd_loop_ub = ctx->cfg.maskTot.size[1];
            if (cd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[cd_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            id_loop_ub = ctx->cfg.maskCart.size[1];
            if (id_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[id_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            pd_loop_ub = ctx->cfg.maskRot.size[1];
            if (pd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[pd_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            xd_loop_ub = ctx->cfg.indCart.size[0];
            for (int i78{0}; i78 < xd_loop_ub; i78++) {
                r.cfg.indCart[i78] = ctx->cfg.indCart.data[i78];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            fe_loop_ub = ctx->cfg.indRot.size[0];
            for (int i84{0}; i84 < fe_loop_ub; i84++) {
                r.cfg.indRot[i84] = ctx->cfg.indRot.data[i84];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            oe_loop_ub = ctx->cfg.D.size[0];
            for (int i92{0}; i92 < oe_loop_ub; i92++) {
                r.cfg.D[i92] = ctx->cfg.D.data[i92];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            ve_loop_ub = ctx->cfg.kin_params.size[0];
            if (ve_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[ve_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i100{0}; i100 < 8; i100++) {
                r.cfg.kin_type[i100] = ctx->cfg.kin_type[i100];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
            r.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            for (int i108{0}; i108 < 6; i108++) {
                r.cfg.vmax[i108] = ctx->cfg.vmax[i108];
                r.cfg.amax[i108] = ctx->cfg.amax[i108];
                r.cfg.jmax[i108] = ctx->cfg.jmax[i108];
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
            r.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
            r.cfg.source.size[0] = 1;
            r.cfg.source.size[1] = ctx->cfg.source.size[1];
            ef_loop_ub = ctx->cfg.source.size[1];
            if (ef_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[ef_loop_ub],
                          &r.cfg.source.data[0]);
            }
            r.cfg.Cusp = ctx->cfg.Cusp;
            r.cfg.Compressing = ctx->cfg.Compressing;
            r.cfg.Smoothing = ctx->cfg.Smoothing;
            r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
            for (int d_i{0}; d_i < 5; d_i++) {
                r.cfg.GaussLegendreX[d_i] = ctx->cfg.GaussLegendreX[d_i];
                r.cfg.GaussLegendreW[d_i] = ctx->cfg.GaussLegendreW[d_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i115{0}; i115 < 9; i115++) {
                r.cfg.LogFileName[i115] = ctx->cfg.LogFileName[i115];
            }
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.zero_forced = ctx->zero_forced;
            r.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
            r.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            lf_loop_ub = ctx->Coeff.size(1);
            for (int i122{0}; i122 < lf_loop_ub; i122++) {
                int rf_loop_ub;
                rf_loop_ub = ctx->Coeff.size(0);
                for (int i128{0}; i128 < rf_loop_ub; i128++) {
                    r.Coeff[i128 + r.Coeff.size(0) * i122] =
                        ctx->Coeff[i128 + ctx->Coeff.size(0) * i122];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            r.errmsg = ctx->errmsg;
            r.errcode = ctx->errcode;
            CheckCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            wf_loop_ub = r.BasisVal.size(1);
            for (int i133{0}; i133 < wf_loop_ub; i133++) {
                int dg_loop_ub;
                dg_loop_ub = r.BasisVal.size(0);
                for (int i139{0}; i139 < dg_loop_ub; i139++) {
                    ctx->BasisVal[i139 + ctx->BasisVal.size(0) * i133] =
                        r.BasisVal[i139 + r.BasisVal.size(0) * i133];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            fg_loop_ub = r.BasisValD.size(1);
            for (int i141{0}; i141 < fg_loop_ub; i141++) {
                int og_loop_ub;
                og_loop_ub = r.BasisValD.size(0);
                for (int i150{0}; i150 < og_loop_ub; i150++) {
                    ctx->BasisValD[i150 + ctx->BasisValD.size(0) * i141] =
                        r.BasisValD[i150 + r.BasisValD.size(0) * i141];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            qg_loop_ub = r.BasisValDD.size(1);
            for (int i152{0}; i152 < qg_loop_ub; i152++) {
                int ah_loop_ub;
                ah_loop_ub = r.BasisValDD.size(0);
                for (int i160{0}; i160 < ah_loop_ub; i160++) {
                    ctx->BasisValDD[i160 + ctx->BasisValDD.size(0) * i152] =
                        r.BasisValDD[i160 + r.BasisValDD.size(0) * i152];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            ch_loop_ub = r.BasisValDDD.size(1);
            for (int i162{0}; i162 < ch_loop_ub; i162++) {
                int kh_loop_ub;
                kh_loop_ub = r.BasisValDDD.size(0);
                for (int i171{0}; i171 < kh_loop_ub; i171++) {
                    ctx->BasisValDDD[i171 + ctx->BasisValDDD.size(0) * i162] =
                        r.BasisValDDD[i171 + r.BasisValDDD.size(0) * i162];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            mh_loop_ub = r.BasisIntegr.size(0);
            for (int i173{0}; i173 < mh_loop_ub; i173++) {
                ctx->BasisIntegr[i173] = r.BasisIntegr[i173];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            wh_loop_ub = r.u_vec.size(1);
            for (int i183{0}; i183 < wh_loop_ub; i183++) {
                ctx->u_vec[i183] = r.u_vec[i183];
            }
            ctx->q_spline = r.q_spline;
            ctx->q_gcode = r.q_gcode;
            ctx->q_compress = r.q_compress;
            ctx->q_smooth = r.q_smooth;
            ctx->q_split = r.q_split;
            ctx->q_opt = r.q_opt;
            ctx->op = r.op;
            ctx->go_next = r.go_next;
            ctx->try_push_again = r.try_push_again;
            ctx->n_optimized = r.n_optimized;
            ctx->reached_end = r.reached_end;
            ctx->k0 = r.k0;
            ctx->v_0 = r.v_0;
            ctx->v_1 = r.v_1;
            ctx->at_0 = r.at_0;
            ctx->at_1 = r.at_1;
            ctx->cfg.ENABLE_PRINT_MSG = r.cfg.ENABLE_PRINT_MSG;
            ctx->cfg.maskTot.size[0] = 1;
            ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
            vi_loop_ub = r.cfg.maskTot.size[1];
            if (vi_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[vi_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            gj_loop_ub = r.cfg.maskCart.size[1];
            if (gj_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[gj_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            qj_loop_ub = r.cfg.maskRot.size[1];
            if (qj_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[qj_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            yj_loop_ub = r.cfg.indCart.size(0);
            for (int i222{0}; i222 < yj_loop_ub; i222++) {
                ctx->cfg.indCart.data[i222] = r.cfg.indCart[i222];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            fk_loop_ub = r.cfg.indRot.size(0);
            for (int i228{0}; i228 < fk_loop_ub; i228++) {
                ctx->cfg.indRot.data[i228] = r.cfg.indRot[i228];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            nk_loop_ub = r.cfg.D.size(0);
            for (int i234{0}; i234 < nk_loop_ub; i234++) {
                ctx->cfg.D.data[i234] = r.cfg.D[i234];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            tk_loop_ub = r.cfg.kin_params.size[0];
            if (tk_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[tk_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i239{0}; i239 < 8; i239++) {
                ctx->cfg.kin_type[i239] = r.cfg.kin_type[i239];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.SplitSpecialSpline = r.cfg.SplitSpecialSpline;
            ctx->cfg.ReleaseMemoryOfTheQueues = r.cfg.ReleaseMemoryOfTheQueues;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            for (int i246{0}; i246 < 6; i246++) {
                ctx->cfg.vmax[i246] = r.cfg.vmax[i246];
                ctx->cfg.amax[i246] = r.cfg.amax[i246];
                ctx->cfg.jmax[i246] = r.cfg.jmax[i246];
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
            ctx->cfg.DefaultZeroStopCount = r.cfg.DefaultZeroStopCount;
            ctx->cfg.source.size[0] = 1;
            ctx->cfg.source.size[1] = r.cfg.source.size[1];
            ol_loop_ub = r.cfg.source.size[1];
            if (ol_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.source.data[0], &r.cfg.source.data[ol_loop_ub],
                          &ctx->cfg.source.data[0]);
            }
            ctx->cfg.Cusp = r.cfg.Cusp;
            ctx->cfg.Compressing = r.cfg.Compressing;
            ctx->cfg.Smoothing = r.cfg.Smoothing;
            ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
            for (int i_i{0}; i_i < 5; i_i++) {
                ctx->cfg.GaussLegendreX[i_i] = r.cfg.GaussLegendreX[i_i];
                ctx->cfg.GaussLegendreW[i_i] = r.cfg.GaussLegendreW[i_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i261{0}; i261 < 9; i261++) {
                ctx->cfg.LogFileName[i261] = r.cfg.LogFileName[i261];
            }
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->zero_forced = r.zero_forced;
            ctx->zero_forced_buffer[0] = r.zero_forced_buffer[0];
            ctx->zero_forced_buffer[1] = r.zero_forced_buffer[1];
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            xl_loop_ub = r.Coeff.size(1);
            for (int i268{0}; i268 < xl_loop_ub; i268++) {
                int dm_loop_ub;
                dm_loop_ub = r.Coeff.size(0);
                for (int i274{0}; i274 < dm_loop_ub; i274++) {
                    ctx->Coeff[i274 + ctx->Coeff.size(0) * i268] =
                        r.Coeff[i274 + r.Coeff.size(0) * i268];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
            ctx->errmsg = r.errmsg;
            ctx->errcode = r.errcode;
        }
        // 'FeedoptPlan:109' ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        r1.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        i_loop_ub = ctx->BasisVal.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            int q_loop_ub;
            q_loop_ub = ctx->BasisVal.size(0);
            for (int i17{0}; i17 < q_loop_ub; i17++) {
                r1.BasisVal[i17 + r1.BasisVal.size(0) * i9] =
                    ctx->BasisVal[i17 + ctx->BasisVal.size(0) * i9];
            }
        }
        r1.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        t_loop_ub = ctx->BasisValD.size(1);
        for (int i20{0}; i20 < t_loop_ub; i20++) {
            int eb_loop_ub;
            eb_loop_ub = ctx->BasisValD.size(0);
            for (int i30{0}; i30 < eb_loop_ub; i30++) {
                r1.BasisValD[i30 + r1.BasisValD.size(0) * i20] =
                    ctx->BasisValD[i30 + ctx->BasisValD.size(0) * i20];
            }
        }
        r1.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        hb_loop_ub = ctx->BasisValDD.size(1);
        for (int i33{0}; i33 < hb_loop_ub; i33++) {
            int sb_loop_ub;
            sb_loop_ub = ctx->BasisValDD.size(0);
            for (int i44{0}; i44 < sb_loop_ub; i44++) {
                r1.BasisValDD[i44 + r1.BasisValDD.size(0) * i33] =
                    ctx->BasisValDD[i44 + ctx->BasisValDD.size(0) * i33];
            }
        }
        r1.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        vb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i47{0}; i47 < vb_loop_ub; i47++) {
            int hc_loop_ub;
            hc_loop_ub = ctx->BasisValDDD.size(0);
            for (int i58{0}; i58 < hc_loop_ub; i58++) {
                r1.BasisValDDD[i58 + r1.BasisValDDD.size(0) * i47] =
                    ctx->BasisValDDD[i58 + ctx->BasisValDDD.size(0) * i47];
            }
        }
        r1.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        kc_loop_ub = ctx->BasisIntegr.size(0);
        for (int i61{0}; i61 < kc_loop_ub; i61++) {
            r1.BasisIntegr[i61] = ctx->BasisIntegr[i61];
        }
        r1.Bl = ctx->Bl;
        r1.u_vec.set_size(1, ctx->u_vec.size(1));
        uc_loop_ub = ctx->u_vec.size(1);
        for (int i71{0}; i71 < uc_loop_ub; i71++) {
            r1.u_vec[i71] = ctx->u_vec[i71];
        }
        r1.q_spline = ctx->q_spline;
        r1.q_gcode = ctx->q_gcode;
        r1.q_compress = ctx->q_compress;
        r1.q_smooth = ctx->q_smooth;
        r1.q_split = ctx->q_split;
        r1.q_opt = ctx->q_opt;
        r1.op = ctx->op;
        r1.go_next = ctx->go_next;
        r1.try_push_again = ctx->try_push_again;
        r1.n_optimized = ctx->n_optimized;
        r1.reached_end = ctx->reached_end;
        r1.k0 = ctx->k0;
        r1.v_0 = ctx->v_0;
        r1.v_1 = ctx->v_1;
        r1.at_0 = ctx->at_0;
        r1.at_1 = ctx->at_1;
        r1.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        r1.cfg.maskTot.size[0] = 1;
        r1.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        dd_loop_ub = ctx->cfg.maskTot.size[1];
        if (dd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[dd_loop_ub],
                      &r1.cfg.maskTot.data[0]);
        }
        r1.cfg.maskCart.size[0] = 1;
        r1.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        jd_loop_ub = ctx->cfg.maskCart.size[1];
        if (jd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[jd_loop_ub],
                      &r1.cfg.maskCart.data[0]);
        }
        r1.cfg.maskRot.size[0] = 1;
        r1.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        qd_loop_ub = ctx->cfg.maskRot.size[1];
        if (qd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[qd_loop_ub],
                      &r1.cfg.maskRot.data[0]);
        }
        r1.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        yd_loop_ub = ctx->cfg.indCart.size[0];
        for (int i79{0}; i79 < yd_loop_ub; i79++) {
            r1.cfg.indCart[i79] = ctx->cfg.indCart.data[i79];
        }
        r1.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ge_loop_ub = ctx->cfg.indRot.size[0];
        for (int i85{0}; i85 < ge_loop_ub; i85++) {
            r1.cfg.indRot[i85] = ctx->cfg.indRot.data[i85];
        }
        r1.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r1.cfg.NCart = ctx->cfg.NCart;
        r1.cfg.NRot = ctx->cfg.NRot;
        r1.cfg.D.set_size(ctx->cfg.D.size[0]);
        pe_loop_ub = ctx->cfg.D.size[0];
        for (int i93{0}; i93 < pe_loop_ub; i93++) {
            r1.cfg.D[i93] = ctx->cfg.D.data[i93];
        }
        r1.cfg.coeffD = ctx->cfg.coeffD;
        r1.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        we_loop_ub = ctx->cfg.kin_params.size[0];
        if (we_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[we_loop_ub],
                      &r1.cfg.kin_params.data[0]);
        }
        for (int i101{0}; i101 < 8; i101++) {
            r1.cfg.kin_type[i101] = ctx->cfg.kin_type[i101];
        }
        r1.cfg.NDiscr = ctx->cfg.NDiscr;
        r1.cfg.NBreak = ctx->cfg.NBreak;
        r1.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        r1.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        r1.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r1.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r1.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r1.cfg.NHorz = ctx->cfg.NHorz;
        for (int i109{0}; i109 < 6; i109++) {
            r1.cfg.vmax[i109] = ctx->cfg.vmax[i109];
            r1.cfg.amax[i109] = ctx->cfg.amax[i109];
            r1.cfg.jmax[i109] = ctx->cfg.jmax[i109];
        }
        r1.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
        r1.cfg.SplineDegree = ctx->cfg.SplineDegree;
        r1.cfg.CutOff = ctx->cfg.CutOff;
        r1.cfg.LSplit = ctx->cfg.LSplit;
        r1.cfg.LSplitZero = ctx->cfg.LSplitZero;
        r1.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
        r1.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
        r1.cfg.v_0 = ctx->cfg.v_0;
        r1.cfg.at_0 = ctx->cfg.at_0;
        r1.cfg.v_1 = ctx->cfg.v_1;
        r1.cfg.at_1 = ctx->cfg.at_1;
        r1.cfg.dt = ctx->cfg.dt;
        r1.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        r1.cfg.source.size[0] = 1;
        r1.cfg.source.size[1] = ctx->cfg.source.size[1];
        ff_loop_ub = ctx->cfg.source.size[1];
        if (ff_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[ff_loop_ub],
                      &r1.cfg.source.data[0]);
        }
        r1.cfg.Cusp = ctx->cfg.Cusp;
        r1.cfg.Compressing = ctx->cfg.Compressing;
        r1.cfg.Smoothing = ctx->cfg.Smoothing;
        r1.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int e_i{0}; e_i < 5; e_i++) {
            r1.cfg.GaussLegendreX[e_i] = ctx->cfg.GaussLegendreX[e_i];
            r1.cfg.GaussLegendreW[e_i] = ctx->cfg.GaussLegendreW[e_i];
        }
        r1.cfg.opt = ctx->cfg.opt;
        for (int i116{0}; i116 < 9; i116++) {
            r1.cfg.LogFileName[i116] = ctx->cfg.LogFileName[i116];
        }
        r1.jmax_increase_count = ctx->jmax_increase_count;
        r1.zero_start = ctx->zero_start;
        r1.zero_end = ctx->zero_end;
        r1.zero_forced = ctx->zero_forced;
        r1.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        r1.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        r1.simplex_calls = ctx->simplex_calls;
        r1.forced_stop = ctx->forced_stop;
        r1.programmed_stop = ctx->programmed_stop;
        r1.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        mf_loop_ub = ctx->Coeff.size(1);
        for (int i123{0}; i123 < mf_loop_ub; i123++) {
            int sf_loop_ub;
            sf_loop_ub = ctx->Coeff.size(0);
            for (int i129{0}; i129 < sf_loop_ub; i129++) {
                r1.Coeff[i129 + r1.Coeff.size(0) * i123] =
                    ctx->Coeff[i129 + ctx->Coeff.size(0) * i123];
            }
        }
        r1.Skipped = ctx->Skipped;
        r1.kin = ctx->kin;
        r1.errmsg = ctx->errmsg;
        r1.errcode = ctx->errcode;
        // 'FeedoptPlan:172' msg = string( op );
        // 'FeedoptPlan:173' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:174'     msg + " - Check geometry failed...", mfilename );
        r3.init(ctx->op);
        obj.Value.size[0] = 1;
        obj.Value.size[1] = r3.Value.size[1] + 27;
        jg_loop_ub = r3.Value.size[1];
        if (jg_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[jg_loop_ub], &obj.Value.data[0]);
        }
        for (int i149{0}; i149 < 27; i149++) {
            obj.Value.data[i149 + r3.Value.size[1]] = obj2Value[i149];
        }
        j_ocn_assert(checkGeometry(&ctx->q_gcode), &obj);
        // 'FeedoptPlan:176' [ isValid, ctx ] = checkZSpdmode( ctx, queue );
        isValid = checkZSpdmode(&r1, &ctx->q_gcode);
        // 'FeedoptPlan:177' ocn_assert( isValid, ...
        // 'FeedoptPlan:178'     msg + " - Check zspdmode failed...", mfilename );
        b_obj.Value.size[0] = 1;
        b_obj.Value.size[1] = r3.Value.size[1] + 27;
        qh_loop_ub = r3.Value.size[1];
        if (qh_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[qh_loop_ub], &b_obj.Value.data[0]);
        }
        for (int i181{0}; i181 < 27; i181++) {
            b_obj.Value.data[i181 + r3.Value.size[1]] = b_obj2Value[i181];
        }
        j_ocn_assert(isValid, &b_obj);
        // 'FeedoptPlan:180' isValid = checkParametrisationQueue( queue );
        c_isValid = checkParametrisationQueue(&ctx->q_gcode);
        // 'FeedoptPlan:181' ocn_assert( isValid, ...
        // 'FeedoptPlan:182'     msg + " - Check parametrisation failed...", mfilename );
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r3.Value.size[1] + 34;
        ji_loop_ub = r3.Value.size[1];
        if (ji_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[ji_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i198{0}; i198 < 34; i198++) {
            c_obj.Value.data[i198 + r3.Value.size[1]] = c_obj2Value[i198];
        }
        j_ocn_assert(c_isValid, &c_obj);
        ctx->BasisVal.set_size(r1.BasisVal.size(0), r1.BasisVal.size(1));
        pi_loop_ub = r1.BasisVal.size(1);
        for (int i202{0}; i202 < pi_loop_ub; i202++) {
            int qi_loop_ub;
            qi_loop_ub = r1.BasisVal.size(0);
            for (int i204{0}; i204 < qi_loop_ub; i204++) {
                ctx->BasisVal[i204 + ctx->BasisVal.size(0) * i202] =
                    r1.BasisVal[i204 + r1.BasisVal.size(0) * i202];
            }
        }
        ctx->BasisValD.set_size(r1.BasisValD.size(0), r1.BasisValD.size(1));
        ri_loop_ub = r1.BasisValD.size(1);
        for (int i205{0}; i205 < ri_loop_ub; i205++) {
            int ui_loop_ub;
            ui_loop_ub = r1.BasisValD.size(0);
            for (int i208{0}; i208 < ui_loop_ub; i208++) {
                ctx->BasisValD[i208 + ctx->BasisValD.size(0) * i205] =
                    r1.BasisValD[i208 + r1.BasisValD.size(0) * i205];
            }
        }
        ctx->BasisValDD.set_size(r1.BasisValDD.size(0), r1.BasisValDD.size(1));
        xi_loop_ub = r1.BasisValDD.size(1);
        for (int i209{0}; i209 < xi_loop_ub; i209++) {
            int ej_loop_ub;
            ej_loop_ub = r1.BasisValDD.size(0);
            for (int i212{0}; i212 < ej_loop_ub; i212++) {
                ctx->BasisValDD[i212 + ctx->BasisValDD.size(0) * i209] =
                    r1.BasisValDD[i212 + r1.BasisValDD.size(0) * i209];
            }
        }
        ctx->BasisValDDD.set_size(r1.BasisValDDD.size(0), r1.BasisValDDD.size(1));
        fj_loop_ub = r1.BasisValDDD.size(1);
        for (int i213{0}; i213 < fj_loop_ub; i213++) {
            int nj_loop_ub;
            nj_loop_ub = r1.BasisValDDD.size(0);
            for (int i216{0}; i216 < nj_loop_ub; i216++) {
                ctx->BasisValDDD[i216 + ctx->BasisValDDD.size(0) * i213] =
                    r1.BasisValDDD[i216 + r1.BasisValDDD.size(0) * i213];
            }
        }
        ctx->BasisIntegr.set_size(r1.BasisIntegr.size(0));
        oj_loop_ub = r1.BasisIntegr.size(0);
        for (int i217{0}; i217 < oj_loop_ub; i217++) {
            ctx->BasisIntegr[i217] = r1.BasisIntegr[i217];
        }
        ctx->Bl = r1.Bl;
        ctx->u_vec.set_size(1, r1.u_vec.size(1));
        xj_loop_ub = r1.u_vec.size(1);
        for (int i221{0}; i221 < xj_loop_ub; i221++) {
            ctx->u_vec[i221] = r1.u_vec[i221];
        }
        ctx->q_spline = r1.q_spline;
        ctx->q_gcode = r1.q_gcode;
        ctx->q_compress = r1.q_compress;
        ctx->q_smooth = r1.q_smooth;
        ctx->q_split = r1.q_split;
        ctx->q_opt = r1.q_opt;
        ctx->go_next = r1.go_next;
        ctx->try_push_again = r1.try_push_again;
        ctx->n_optimized = r1.n_optimized;
        ctx->reached_end = r1.reached_end;
        ctx->k0 = r1.k0;
        ctx->v_0 = r1.v_0;
        ctx->v_1 = r1.v_1;
        ctx->at_0 = r1.at_0;
        ctx->at_1 = r1.at_1;
        ctx->cfg.ENABLE_PRINT_MSG = r1.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = r1.cfg.maskTot.size[1];
        al_loop_ub = r1.cfg.maskTot.size[1];
        if (al_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskTot.data[0], &r1.cfg.maskTot.data[al_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r1.cfg.maskCart.size[1];
        cl_loop_ub = r1.cfg.maskCart.size[1];
        if (cl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskCart.data[0], &r1.cfg.maskCart.data[cl_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r1.cfg.maskRot.size[1];
        fl_loop_ub = r1.cfg.maskRot.size[1];
        if (fl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskRot.data[0], &r1.cfg.maskRot.data[fl_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r1.cfg.indCart.size(0);
        hl_loop_ub = r1.cfg.indCart.size(0);
        for (int i252{0}; i252 < hl_loop_ub; i252++) {
            ctx->cfg.indCart.data[i252] = r1.cfg.indCart[i252];
        }
        ctx->cfg.indRot.size[0] = r1.cfg.indRot.size(0);
        kl_loop_ub = r1.cfg.indRot.size(0);
        for (int i254{0}; i254 < kl_loop_ub; i254++) {
            ctx->cfg.indRot.data[i254] = r1.cfg.indRot[i254];
        }
        ctx->cfg.NumberAxis = r1.cfg.NumberAxis;
        ctx->cfg.NCart = r1.cfg.NCart;
        ctx->cfg.NRot = r1.cfg.NRot;
        ctx->cfg.D.size[0] = r1.cfg.D.size(0);
        nl_loop_ub = r1.cfg.D.size(0);
        for (int i257{0}; i257 < nl_loop_ub; i257++) {
            ctx->cfg.D.data[i257] = r1.cfg.D[i257];
        }
        ctx->cfg.coeffD = r1.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r1.cfg.kin_params.size[0];
        tl_loop_ub = r1.cfg.kin_params.size[0];
        if (tl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.kin_params.data[0], &r1.cfg.kin_params.data[tl_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i260{0}; i260 < 8; i260++) {
            ctx->cfg.kin_type[i260] = r1.cfg.kin_type[i260];
        }
        ctx->cfg.NDiscr = r1.cfg.NDiscr;
        ctx->cfg.NBreak = r1.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = r1.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = r1.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = r1.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r1.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r1.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r1.cfg.NHorz;
        for (int i267{0}; i267 < 6; i267++) {
            ctx->cfg.vmax[i267] = r1.cfg.vmax[i267];
            ctx->cfg.amax[i267] = r1.cfg.amax[i267];
            ctx->cfg.jmax[i267] = r1.cfg.jmax[i267];
        }
        ctx->cfg.LeeSplineDegree = r1.cfg.LeeSplineDegree;
        ctx->cfg.SplineDegree = r1.cfg.SplineDegree;
        ctx->cfg.CutOff = r1.cfg.CutOff;
        ctx->cfg.LSplit = r1.cfg.LSplit;
        ctx->cfg.LSplitZero = r1.cfg.LSplitZero;
        ctx->cfg.LThresholdMax = r1.cfg.LThresholdMax;
        ctx->cfg.LThresholdMin = r1.cfg.LThresholdMin;
        ctx->cfg.v_0 = r1.cfg.v_0;
        ctx->cfg.at_0 = r1.cfg.at_0;
        ctx->cfg.v_1 = r1.cfg.v_1;
        ctx->cfg.at_1 = r1.cfg.at_1;
        ctx->cfg.dt = r1.cfg.dt;
        ctx->cfg.DefaultZeroStopCount = r1.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = r1.cfg.source.size[1];
        im_loop_ub = r1.cfg.source.size[1];
        if (im_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.source.data[0], &r1.cfg.source.data[im_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = r1.cfg.Cusp;
        ctx->cfg.Compressing = r1.cfg.Compressing;
        ctx->cfg.Smoothing = r1.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r1.cfg.GaussLegendreN;
        for (int o_i{0}; o_i < 5; o_i++) {
            ctx->cfg.GaussLegendreX[o_i] = r1.cfg.GaussLegendreX[o_i];
            ctx->cfg.GaussLegendreW[o_i] = r1.cfg.GaussLegendreW[o_i];
        }
        ctx->cfg.opt = r1.cfg.opt;
        for (int i281{0}; i281 < 9; i281++) {
            ctx->cfg.LogFileName[i281] = r1.cfg.LogFileName[i281];
        }
        ctx->jmax_increase_count = r1.jmax_increase_count;
        ctx->zero_start = r1.zero_start;
        ctx->zero_end = r1.zero_end;
        ctx->zero_forced = r1.zero_forced;
        ctx->zero_forced_buffer[0] = r1.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = r1.zero_forced_buffer[1];
        ctx->simplex_calls = r1.simplex_calls;
        ctx->forced_stop = r1.forced_stop;
        ctx->programmed_stop = r1.programmed_stop;
        ctx->Coeff.set_size(r1.Coeff.size(0), r1.Coeff.size(1));
        bn_loop_ub = r1.Coeff.size(1);
        for (int i298{0}; i298 < bn_loop_ub; i298++) {
            int en_loop_ub;
            en_loop_ub = r1.Coeff.size(0);
            for (int i301{0}; i301 < en_loop_ub; i301++) {
                ctx->Coeff[i301 + ctx->Coeff.size(0) * i298] =
                    r1.Coeff[i301 + r1.Coeff.size(0) * i298];
            }
        }
        ctx->Skipped = r1.Skipped;
        ctx->kin = r1.kin;
        ctx->errmsg = r1.errmsg;
        ctx->errcode = r1.errcode;
        // 'FeedoptPlan:111' ctx.op  = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        int ai_loop_ub;
        int ak_loop_ub;
        int be_loop_ub;
        int bf_loop_ub;
        int cc_loop_ub;
        int cj_loop_ub;
        int dl_loop_ub;
        int gl_loop_ub;
        int ie_loop_ub;
        int if_loop_ub;
        int ik_loop_ub;
        int in_loop_ub;
        int jl_loop_ub;
        int jm_loop_ub;
        int kj_loop_ub;
        int ld_loop_ub;
        int ll_loop_ub;
        int mi_loop_ub;
        int ml_loop_ub;
        int nb_loop_ub;
        int ne_loop_ub;
        int oc_loop_ub;
        int rj_loop_ub;
        int sd_loop_ub;
        int ti_loop_ub;
        int ul_loop_ub;
        int vf_loop_ub;
        int vl_loop_ub;
        int wc_loop_ub;
        int xg_loop_ub;
        int y_loop_ub;
        int yc_loop_ub;
        int ye_loop_ub;
        bool b_isValid;
        bool d_isValid;
        // 'FeedoptPlan:113' case Fopt.Compress
        // 'FeedoptPlan:114' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i7;
            unsigned int u;
            // 'FeedoptPlan:115' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i7 = static_cast<int>(u);
            for (int j{0}; j < i7; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:117' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r2);
                ctx->q_compress.push(&r2);
            }
        } else {
            int ae_loop_ub;
            int ag_loop_ub;
            int am_loop_ub;
            int ck_loop_ub;
            int ed_loop_ub;
            int gf_loop_ub;
            int gh_loop_ub;
            int he_loop_ub;
            int hk_loop_ub;
            int ib_loop_ub;
            int j_loop_ub;
            int jj_loop_ub;
            int kd_loop_ub;
            int kg_loop_ub;
            int lc_loop_ub;
            int nf_loop_ub;
            int pk_loop_ub;
            int qe_loop_ub;
            int ql_loop_ub;
            int rd_loop_ub;
            int rh_loop_ub;
            int tj_loop_ub;
            int u_loop_ub;
            int ug_loop_ub;
            int vc_loop_ub;
            int vk_loop_ub;
            int wb_loop_ub;
            int xe_loop_ub;
            int yh_loop_ub;
            int yi_loop_ub;
            // 'FeedoptPlan:119' else
            // 'FeedoptPlan:120' ctx = compressCurvStructs(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            j_loop_ub = ctx->BasisVal.size(1);
            for (int i10{0}; i10 < j_loop_ub; i10++) {
                int s_loop_ub;
                s_loop_ub = ctx->BasisVal.size(0);
                for (int i19{0}; i19 < s_loop_ub; i19++) {
                    r.BasisVal[i19 + r.BasisVal.size(0) * i10] =
                        ctx->BasisVal[i19 + ctx->BasisVal.size(0) * i10];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            u_loop_ub = ctx->BasisValD.size(1);
            for (int i21{0}; i21 < u_loop_ub; i21++) {
                int gb_loop_ub;
                gb_loop_ub = ctx->BasisValD.size(0);
                for (int i32{0}; i32 < gb_loop_ub; i32++) {
                    r.BasisValD[i32 + r.BasisValD.size(0) * i21] =
                        ctx->BasisValD[i32 + ctx->BasisValD.size(0) * i21];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            ib_loop_ub = ctx->BasisValDD.size(1);
            for (int i34{0}; i34 < ib_loop_ub; i34++) {
                int ub_loop_ub;
                ub_loop_ub = ctx->BasisValDD.size(0);
                for (int i46{0}; i46 < ub_loop_ub; i46++) {
                    r.BasisValDD[i46 + r.BasisValDD.size(0) * i34] =
                        ctx->BasisValDD[i46 + ctx->BasisValDD.size(0) * i34];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            wb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i48{0}; i48 < wb_loop_ub; i48++) {
                int jc_loop_ub;
                jc_loop_ub = ctx->BasisValDDD.size(0);
                for (int i60{0}; i60 < jc_loop_ub; i60++) {
                    r.BasisValDDD[i60 + r.BasisValDDD.size(0) * i48] =
                        ctx->BasisValDDD[i60 + ctx->BasisValDDD.size(0) * i48];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            lc_loop_ub = ctx->BasisIntegr.size(0);
            for (int i62{0}; i62 < lc_loop_ub; i62++) {
                r.BasisIntegr[i62] = ctx->BasisIntegr[i62];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            vc_loop_ub = ctx->u_vec.size(1);
            for (int i72{0}; i72 < vc_loop_ub; i72++) {
                r.u_vec[i72] = ctx->u_vec[i72];
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
            r.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
            r.cfg.maskTot.size[0] = 1;
            r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
            ed_loop_ub = ctx->cfg.maskTot.size[1];
            if (ed_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ed_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            kd_loop_ub = ctx->cfg.maskCart.size[1];
            if (kd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[kd_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            rd_loop_ub = ctx->cfg.maskRot.size[1];
            if (rd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[rd_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            ae_loop_ub = ctx->cfg.indCart.size[0];
            for (int i80{0}; i80 < ae_loop_ub; i80++) {
                r.cfg.indCart[i80] = ctx->cfg.indCart.data[i80];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            he_loop_ub = ctx->cfg.indRot.size[0];
            for (int i86{0}; i86 < he_loop_ub; i86++) {
                r.cfg.indRot[i86] = ctx->cfg.indRot.data[i86];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            qe_loop_ub = ctx->cfg.D.size[0];
            for (int i94{0}; i94 < qe_loop_ub; i94++) {
                r.cfg.D[i94] = ctx->cfg.D.data[i94];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            xe_loop_ub = ctx->cfg.kin_params.size[0];
            if (xe_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[xe_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i102{0}; i102 < 8; i102++) {
                r.cfg.kin_type[i102] = ctx->cfg.kin_type[i102];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
            r.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            for (int i110{0}; i110 < 6; i110++) {
                r.cfg.vmax[i110] = ctx->cfg.vmax[i110];
                r.cfg.amax[i110] = ctx->cfg.amax[i110];
                r.cfg.jmax[i110] = ctx->cfg.jmax[i110];
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
            r.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
            r.cfg.source.size[0] = 1;
            r.cfg.source.size[1] = ctx->cfg.source.size[1];
            gf_loop_ub = ctx->cfg.source.size[1];
            if (gf_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[gf_loop_ub],
                          &r.cfg.source.data[0]);
            }
            r.cfg.Cusp = ctx->cfg.Cusp;
            r.cfg.Compressing = ctx->cfg.Compressing;
            r.cfg.Smoothing = ctx->cfg.Smoothing;
            r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
            for (int f_i{0}; f_i < 5; f_i++) {
                r.cfg.GaussLegendreX[f_i] = ctx->cfg.GaussLegendreX[f_i];
                r.cfg.GaussLegendreW[f_i] = ctx->cfg.GaussLegendreW[f_i];
            }
            r.cfg.opt = ctx->cfg.opt;
            for (int i117{0}; i117 < 9; i117++) {
                r.cfg.LogFileName[i117] = ctx->cfg.LogFileName[i117];
            }
            r.jmax_increase_count = ctx->jmax_increase_count;
            r.zero_start = ctx->zero_start;
            r.zero_end = ctx->zero_end;
            r.zero_forced = ctx->zero_forced;
            r.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
            r.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
            r.simplex_calls = ctx->simplex_calls;
            r.forced_stop = ctx->forced_stop;
            r.programmed_stop = ctx->programmed_stop;
            r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
            nf_loop_ub = ctx->Coeff.size(1);
            for (int i124{0}; i124 < nf_loop_ub; i124++) {
                int tf_loop_ub;
                tf_loop_ub = ctx->Coeff.size(0);
                for (int i130{0}; i130 < tf_loop_ub; i130++) {
                    r.Coeff[i130 + r.Coeff.size(0) * i124] =
                        ctx->Coeff[i130 + ctx->Coeff.size(0) * i124];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            r.errmsg = ctx->errmsg;
            r.errcode = ctx->errcode;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            ag_loop_ub = r.BasisVal.size(1);
            for (int i136{0}; i136 < ag_loop_ub; i136++) {
                int gg_loop_ub;
                gg_loop_ub = r.BasisVal.size(0);
                for (int i142{0}; i142 < gg_loop_ub; i142++) {
                    ctx->BasisVal[i142 + ctx->BasisVal.size(0) * i136] =
                        r.BasisVal[i142 + r.BasisVal.size(0) * i136];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            kg_loop_ub = r.BasisValD.size(1);
            for (int i145{0}; i145 < kg_loop_ub; i145++) {
                int rg_loop_ub;
                rg_loop_ub = r.BasisValD.size(0);
                for (int i153{0}; i153 < rg_loop_ub; i153++) {
                    ctx->BasisValD[i153 + ctx->BasisValD.size(0) * i145] =
                        r.BasisValD[i153 + r.BasisValD.size(0) * i145];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            ug_loop_ub = r.BasisValDD.size(1);
            for (int i156{0}; i156 < ug_loop_ub; i156++) {
                int dh_loop_ub;
                dh_loop_ub = r.BasisValDD.size(0);
                for (int i163{0}; i163 < dh_loop_ub; i163++) {
                    ctx->BasisValDD[i163 + ctx->BasisValDD.size(0) * i156] =
                        r.BasisValDD[i163 + r.BasisValDD.size(0) * i156];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            gh_loop_ub = r.BasisValDDD.size(1);
            for (int i167{0}; i167 < gh_loop_ub; i167++) {
                int nh_loop_ub;
                nh_loop_ub = r.BasisValDDD.size(0);
                for (int i174{0}; i174 < nh_loop_ub; i174++) {
                    ctx->BasisValDDD[i174 + ctx->BasisValDDD.size(0) * i167] =
                        r.BasisValDDD[i174 + r.BasisValDDD.size(0) * i167];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            rh_loop_ub = r.BasisIntegr.size(0);
            for (int i177{0}; i177 < rh_loop_ub; i177++) {
                ctx->BasisIntegr[i177] = r.BasisIntegr[i177];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            yh_loop_ub = r.u_vec.size(1);
            for (int i185{0}; i185 < yh_loop_ub; i185++) {
                ctx->u_vec[i185] = r.u_vec[i185];
            }
            ctx->q_spline = r.q_spline;
            ctx->q_gcode = r.q_gcode;
            ctx->q_compress = r.q_compress;
            ctx->q_smooth = r.q_smooth;
            ctx->q_split = r.q_split;
            ctx->q_opt = r.q_opt;
            ctx->op = r.op;
            ctx->go_next = r.go_next;
            ctx->try_push_again = r.try_push_again;
            ctx->n_optimized = r.n_optimized;
            ctx->reached_end = r.reached_end;
            ctx->k0 = r.k0;
            ctx->v_0 = r.v_0;
            ctx->v_1 = r.v_1;
            ctx->at_0 = r.at_0;
            ctx->at_1 = r.at_1;
            ctx->cfg.ENABLE_PRINT_MSG = r.cfg.ENABLE_PRINT_MSG;
            ctx->cfg.maskTot.size[0] = 1;
            ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
            yi_loop_ub = r.cfg.maskTot.size[1];
            if (yi_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[yi_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            jj_loop_ub = r.cfg.maskCart.size[1];
            if (jj_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[jj_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            tj_loop_ub = r.cfg.maskRot.size[1];
            if (tj_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[tj_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            ck_loop_ub = r.cfg.indCart.size(0);
            for (int i225{0}; i225 < ck_loop_ub; i225++) {
                ctx->cfg.indCart.data[i225] = r.cfg.indCart[i225];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            hk_loop_ub = r.cfg.indRot.size(0);
            for (int i230{0}; i230 < hk_loop_ub; i230++) {
                ctx->cfg.indRot.data[i230] = r.cfg.indRot[i230];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            pk_loop_ub = r.cfg.D.size(0);
            for (int i236{0}; i236 < pk_loop_ub; i236++) {
                ctx->cfg.D.data[i236] = r.cfg.D[i236];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            vk_loop_ub = r.cfg.kin_params.size[0];
            if (vk_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[vk_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i241{0}; i241 < 8; i241++) {
                ctx->cfg.kin_type[i241] = r.cfg.kin_type[i241];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.SplitSpecialSpline = r.cfg.SplitSpecialSpline;
            ctx->cfg.ReleaseMemoryOfTheQueues = r.cfg.ReleaseMemoryOfTheQueues;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            for (int i248{0}; i248 < 6; i248++) {
                ctx->cfg.vmax[i248] = r.cfg.vmax[i248];
                ctx->cfg.amax[i248] = r.cfg.amax[i248];
                ctx->cfg.jmax[i248] = r.cfg.jmax[i248];
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
            ctx->cfg.DefaultZeroStopCount = r.cfg.DefaultZeroStopCount;
            ctx->cfg.source.size[0] = 1;
            ctx->cfg.source.size[1] = r.cfg.source.size[1];
            ql_loop_ub = r.cfg.source.size[1];
            if (ql_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.source.data[0], &r.cfg.source.data[ql_loop_ub],
                          &ctx->cfg.source.data[0]);
            }
            ctx->cfg.Cusp = r.cfg.Cusp;
            ctx->cfg.Compressing = r.cfg.Compressing;
            ctx->cfg.Smoothing = r.cfg.Smoothing;
            ctx->cfg.GaussLegendreN = r.cfg.GaussLegendreN;
            for (int k_i{0}; k_i < 5; k_i++) {
                ctx->cfg.GaussLegendreX[k_i] = r.cfg.GaussLegendreX[k_i];
                ctx->cfg.GaussLegendreW[k_i] = r.cfg.GaussLegendreW[k_i];
            }
            ctx->cfg.opt = r.cfg.opt;
            for (int i263{0}; i263 < 9; i263++) {
                ctx->cfg.LogFileName[i263] = r.cfg.LogFileName[i263];
            }
            ctx->jmax_increase_count = r.jmax_increase_count;
            ctx->zero_start = r.zero_start;
            ctx->zero_end = r.zero_end;
            ctx->zero_forced = r.zero_forced;
            ctx->zero_forced_buffer[0] = r.zero_forced_buffer[0];
            ctx->zero_forced_buffer[1] = r.zero_forced_buffer[1];
            ctx->simplex_calls = r.simplex_calls;
            ctx->forced_stop = r.forced_stop;
            ctx->programmed_stop = r.programmed_stop;
            ctx->Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
            am_loop_ub = r.Coeff.size(1);
            for (int i271{0}; i271 < am_loop_ub; i271++) {
                int fm_loop_ub;
                fm_loop_ub = r.Coeff.size(0);
                for (int i276{0}; i276 < fm_loop_ub; i276++) {
                    ctx->Coeff[i276 + ctx->Coeff.size(0) * i271] =
                        r.Coeff[i276 + r.Coeff.size(0) * i271];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
            ctx->errmsg = r.errmsg;
            ctx->errcode = r.errcode;
        }
        // 'FeedoptPlan:123' ctx = assert_queue( ctx, ctx.op, ctx.q_compress );
        r1.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        y_loop_ub = ctx->BasisVal.size(1);
        for (int i25{0}; i25 < y_loop_ub; i25++) {
            int jb_loop_ub;
            jb_loop_ub = ctx->BasisVal.size(0);
            for (int i35{0}; i35 < jb_loop_ub; i35++) {
                r1.BasisVal[i35 + r1.BasisVal.size(0) * i25] =
                    ctx->BasisVal[i35 + ctx->BasisVal.size(0) * i25];
            }
        }
        r1.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        nb_loop_ub = ctx->BasisValD.size(1);
        for (int i39{0}; i39 < nb_loop_ub; i39++) {
            int xb_loop_ub;
            xb_loop_ub = ctx->BasisValD.size(0);
            for (int i49{0}; i49 < xb_loop_ub; i49++) {
                r1.BasisValD[i49 + r1.BasisValD.size(0) * i39] =
                    ctx->BasisValD[i49 + ctx->BasisValD.size(0) * i39];
            }
        }
        r1.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        cc_loop_ub = ctx->BasisValDD.size(1);
        for (int i53{0}; i53 < cc_loop_ub; i53++) {
            int mc_loop_ub;
            mc_loop_ub = ctx->BasisValDD.size(0);
            for (int i63{0}; i63 < mc_loop_ub; i63++) {
                r1.BasisValDD[i63 + r1.BasisValDD.size(0) * i53] =
                    ctx->BasisValDD[i63 + ctx->BasisValDD.size(0) * i53];
            }
        }
        r1.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        oc_loop_ub = ctx->BasisValDDD.size(1);
        for (int i65{0}; i65 < oc_loop_ub; i65++) {
            int tc_loop_ub;
            tc_loop_ub = ctx->BasisValDDD.size(0);
            for (int i70{0}; i70 < tc_loop_ub; i70++) {
                r1.BasisValDDD[i70 + r1.BasisValDDD.size(0) * i65] =
                    ctx->BasisValDDD[i70 + ctx->BasisValDDD.size(0) * i65];
            }
        }
        r1.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        wc_loop_ub = ctx->BasisIntegr.size(0);
        for (int i73{0}; i73 < wc_loop_ub; i73++) {
            r1.BasisIntegr[i73] = ctx->BasisIntegr[i73];
        }
        r1.Bl = ctx->Bl;
        r1.u_vec.set_size(1, ctx->u_vec.size(1));
        yc_loop_ub = ctx->u_vec.size(1);
        for (int i75{0}; i75 < yc_loop_ub; i75++) {
            r1.u_vec[i75] = ctx->u_vec[i75];
        }
        r1.q_spline = ctx->q_spline;
        r1.q_gcode = ctx->q_gcode;
        r1.q_compress = ctx->q_compress;
        r1.q_smooth = ctx->q_smooth;
        r1.q_split = ctx->q_split;
        r1.q_opt = ctx->q_opt;
        r1.op = ctx->op;
        r1.go_next = ctx->go_next;
        r1.try_push_again = ctx->try_push_again;
        r1.n_optimized = ctx->n_optimized;
        r1.reached_end = ctx->reached_end;
        r1.k0 = ctx->k0;
        r1.v_0 = ctx->v_0;
        r1.v_1 = ctx->v_1;
        r1.at_0 = ctx->at_0;
        r1.at_1 = ctx->at_1;
        r1.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        r1.cfg.maskTot.size[0] = 1;
        r1.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        ld_loop_ub = ctx->cfg.maskTot.size[1];
        if (ld_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ld_loop_ub],
                      &r1.cfg.maskTot.data[0]);
        }
        r1.cfg.maskCart.size[0] = 1;
        r1.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        sd_loop_ub = ctx->cfg.maskCart.size[1];
        if (sd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[sd_loop_ub],
                      &r1.cfg.maskCart.data[0]);
        }
        r1.cfg.maskRot.size[0] = 1;
        r1.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        be_loop_ub = ctx->cfg.maskRot.size[1];
        if (be_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[be_loop_ub],
                      &r1.cfg.maskRot.data[0]);
        }
        r1.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ie_loop_ub = ctx->cfg.indCart.size[0];
        for (int i87{0}; i87 < ie_loop_ub; i87++) {
            r1.cfg.indCart[i87] = ctx->cfg.indCart.data[i87];
        }
        r1.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ne_loop_ub = ctx->cfg.indRot.size[0];
        for (int i91{0}; i91 < ne_loop_ub; i91++) {
            r1.cfg.indRot[i91] = ctx->cfg.indRot.data[i91];
        }
        r1.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r1.cfg.NCart = ctx->cfg.NCart;
        r1.cfg.NRot = ctx->cfg.NRot;
        r1.cfg.D.set_size(ctx->cfg.D.size[0]);
        ye_loop_ub = ctx->cfg.D.size[0];
        for (int i99{0}; i99 < ye_loop_ub; i99++) {
            r1.cfg.D[i99] = ctx->cfg.D.data[i99];
        }
        r1.cfg.coeffD = ctx->cfg.coeffD;
        r1.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        bf_loop_ub = ctx->cfg.kin_params.size[0];
        if (bf_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[bf_loop_ub],
                      &r1.cfg.kin_params.data[0]);
        }
        for (int i105{0}; i105 < 8; i105++) {
            r1.cfg.kin_type[i105] = ctx->cfg.kin_type[i105];
        }
        r1.cfg.NDiscr = ctx->cfg.NDiscr;
        r1.cfg.NBreak = ctx->cfg.NBreak;
        r1.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        r1.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        r1.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r1.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r1.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r1.cfg.NHorz = ctx->cfg.NHorz;
        for (int i112{0}; i112 < 6; i112++) {
            r1.cfg.vmax[i112] = ctx->cfg.vmax[i112];
            r1.cfg.amax[i112] = ctx->cfg.amax[i112];
            r1.cfg.jmax[i112] = ctx->cfg.jmax[i112];
        }
        r1.cfg.LeeSplineDegree = ctx->cfg.LeeSplineDegree;
        r1.cfg.SplineDegree = ctx->cfg.SplineDegree;
        r1.cfg.CutOff = ctx->cfg.CutOff;
        r1.cfg.LSplit = ctx->cfg.LSplit;
        r1.cfg.LSplitZero = ctx->cfg.LSplitZero;
        r1.cfg.LThresholdMax = ctx->cfg.LThresholdMax;
        r1.cfg.LThresholdMin = ctx->cfg.LThresholdMin;
        r1.cfg.v_0 = ctx->cfg.v_0;
        r1.cfg.at_0 = ctx->cfg.at_0;
        r1.cfg.v_1 = ctx->cfg.v_1;
        r1.cfg.at_1 = ctx->cfg.at_1;
        r1.cfg.dt = ctx->cfg.dt;
        r1.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        r1.cfg.source.size[0] = 1;
        r1.cfg.source.size[1] = ctx->cfg.source.size[1];
        if_loop_ub = ctx->cfg.source.size[1];
        if (if_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[if_loop_ub],
                      &r1.cfg.source.data[0]);
        }
        r1.cfg.Cusp = ctx->cfg.Cusp;
        r1.cfg.Compressing = ctx->cfg.Compressing;
        r1.cfg.Smoothing = ctx->cfg.Smoothing;
        r1.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int h_i{0}; h_i < 5; h_i++) {
            r1.cfg.GaussLegendreX[h_i] = ctx->cfg.GaussLegendreX[h_i];
            r1.cfg.GaussLegendreW[h_i] = ctx->cfg.GaussLegendreW[h_i];
        }
        r1.cfg.opt = ctx->cfg.opt;
        for (int i119{0}; i119 < 9; i119++) {
            r1.cfg.LogFileName[i119] = ctx->cfg.LogFileName[i119];
        }
        r1.jmax_increase_count = ctx->jmax_increase_count;
        r1.zero_start = ctx->zero_start;
        r1.zero_end = ctx->zero_end;
        r1.zero_forced = ctx->zero_forced;
        r1.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        r1.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        r1.simplex_calls = ctx->simplex_calls;
        r1.forced_stop = ctx->forced_stop;
        r1.programmed_stop = ctx->programmed_stop;
        r1.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        vf_loop_ub = ctx->Coeff.size(1);
        for (int i132{0}; i132 < vf_loop_ub; i132++) {
            int xf_loop_ub;
            xf_loop_ub = ctx->Coeff.size(0);
            for (int i134{0}; i134 < xf_loop_ub; i134++) {
                r1.Coeff[i134 + r1.Coeff.size(0) * i132] =
                    ctx->Coeff[i134 + ctx->Coeff.size(0) * i132];
            }
        }
        r1.Skipped = ctx->Skipped;
        r1.kin = ctx->kin;
        r1.errmsg = ctx->errmsg;
        r1.errcode = ctx->errcode;
        // 'FeedoptPlan:172' msg = string( op );
        // 'FeedoptPlan:173' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:174'     msg + " - Check geometry failed...", mfilename );
        r3.init(ctx->op);
        obj.Value.size[0] = 1;
        obj.Value.size[1] = r3.Value.size[1] + 27;
        xg_loop_ub = r3.Value.size[1];
        if (xg_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[xg_loop_ub], &obj.Value.data[0]);
        }
        for (int i164{0}; i164 < 27; i164++) {
            obj.Value.data[i164 + r3.Value.size[1]] = obj2Value[i164];
        }
        j_ocn_assert(checkGeometry(&ctx->q_compress), &obj);
        // 'FeedoptPlan:176' [ isValid, ctx ] = checkZSpdmode( ctx, queue );
        b_isValid = checkZSpdmode(&r1, &ctx->q_compress);
        // 'FeedoptPlan:177' ocn_assert( isValid, ...
        // 'FeedoptPlan:178'     msg + " - Check zspdmode failed...", mfilename );
        b_obj.Value.size[0] = 1;
        b_obj.Value.size[1] = r3.Value.size[1] + 27;
        ai_loop_ub = r3.Value.size[1];
        if (ai_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[ai_loop_ub], &b_obj.Value.data[0]);
        }
        for (int i192{0}; i192 < 27; i192++) {
            b_obj.Value.data[i192 + r3.Value.size[1]] = b_obj2Value[i192];
        }
        j_ocn_assert(b_isValid, &b_obj);
        // 'FeedoptPlan:180' isValid = checkParametrisationQueue( queue );
        d_isValid = checkParametrisationQueue(&ctx->q_compress);
        // 'FeedoptPlan:181' ocn_assert( isValid, ...
        // 'FeedoptPlan:182'     msg + " - Check parametrisation failed...", mfilename );
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r3.Value.size[1] + 34;
        mi_loop_ub = r3.Value.size[1];
        if (mi_loop_ub - 1 >= 0) {
            std::copy(&r3.Value.data[0], &r3.Value.data[mi_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i203{0}; i203 < 34; i203++) {
            c_obj.Value.data[i203 + r3.Value.size[1]] = c_obj2Value[i203];
        }
        j_ocn_assert(d_isValid, &c_obj);
        ctx->BasisVal.set_size(r1.BasisVal.size(0), r1.BasisVal.size(1));
        ti_loop_ub = r1.BasisVal.size(1);
        for (int i207{0}; i207 < ti_loop_ub; i207++) {
            int aj_loop_ub;
            aj_loop_ub = r1.BasisVal.size(0);
            for (int i210{0}; i210 < aj_loop_ub; i210++) {
                ctx->BasisVal[i210 + ctx->BasisVal.size(0) * i207] =
                    r1.BasisVal[i210 + r1.BasisVal.size(0) * i207];
            }
        }
        ctx->BasisValD.set_size(r1.BasisValD.size(0), r1.BasisValD.size(1));
        cj_loop_ub = r1.BasisValD.size(1);
        for (int i211{0}; i211 < cj_loop_ub; i211++) {
            int hj_loop_ub;
            hj_loop_ub = r1.BasisValD.size(0);
            for (int i214{0}; i214 < hj_loop_ub; i214++) {
                ctx->BasisValD[i214 + ctx->BasisValD.size(0) * i211] =
                    r1.BasisValD[i214 + r1.BasisValD.size(0) * i211];
            }
        }
        ctx->BasisValDD.set_size(r1.BasisValDD.size(0), r1.BasisValDD.size(1));
        kj_loop_ub = r1.BasisValDD.size(1);
        for (int i215{0}; i215 < kj_loop_ub; i215++) {
            int pj_loop_ub;
            pj_loop_ub = r1.BasisValDD.size(0);
            for (int i218{0}; i218 < pj_loop_ub; i218++) {
                ctx->BasisValDD[i218 + ctx->BasisValDD.size(0) * i215] =
                    r1.BasisValDD[i218 + r1.BasisValDD.size(0) * i215];
            }
        }
        ctx->BasisValDDD.set_size(r1.BasisValDDD.size(0), r1.BasisValDDD.size(1));
        rj_loop_ub = r1.BasisValDDD.size(1);
        for (int i219{0}; i219 < rj_loop_ub; i219++) {
            int wj_loop_ub;
            wj_loop_ub = r1.BasisValDDD.size(0);
            for (int i220{0}; i220 < wj_loop_ub; i220++) {
                ctx->BasisValDDD[i220 + ctx->BasisValDDD.size(0) * i219] =
                    r1.BasisValDDD[i220 + r1.BasisValDDD.size(0) * i219];
            }
        }
        ctx->BasisIntegr.set_size(r1.BasisIntegr.size(0));
        ak_loop_ub = r1.BasisIntegr.size(0);
        for (int i223{0}; i223 < ak_loop_ub; i223++) {
            ctx->BasisIntegr[i223] = r1.BasisIntegr[i223];
        }
        ctx->Bl = r1.Bl;
        ctx->u_vec.set_size(1, r1.u_vec.size(1));
        ik_loop_ub = r1.u_vec.size(1);
        for (int i231{0}; i231 < ik_loop_ub; i231++) {
            ctx->u_vec[i231] = r1.u_vec[i231];
        }
        ctx->q_spline = r1.q_spline;
        ctx->q_gcode = r1.q_gcode;
        ctx->q_compress = r1.q_compress;
        ctx->q_smooth = r1.q_smooth;
        ctx->q_split = r1.q_split;
        ctx->q_opt = r1.q_opt;
        ctx->go_next = r1.go_next;
        ctx->try_push_again = r1.try_push_again;
        ctx->n_optimized = r1.n_optimized;
        ctx->reached_end = r1.reached_end;
        ctx->k0 = r1.k0;
        ctx->v_0 = r1.v_0;
        ctx->v_1 = r1.v_1;
        ctx->at_0 = r1.at_0;
        ctx->at_1 = r1.at_1;
        ctx->cfg.ENABLE_PRINT_MSG = r1.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = r1.cfg.maskTot.size[1];
        dl_loop_ub = r1.cfg.maskTot.size[1];
        if (dl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskTot.data[0], &r1.cfg.maskTot.data[dl_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r1.cfg.maskCart.size[1];
        gl_loop_ub = r1.cfg.maskCart.size[1];
        if (gl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskCart.data[0], &r1.cfg.maskCart.data[gl_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r1.cfg.maskRot.size[1];
        jl_loop_ub = r1.cfg.maskRot.size[1];
        if (jl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.maskRot.data[0], &r1.cfg.maskRot.data[jl_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r1.cfg.indCart.size(0);
        ll_loop_ub = r1.cfg.indCart.size(0);
        for (int i255{0}; i255 < ll_loop_ub; i255++) {
            ctx->cfg.indCart.data[i255] = r1.cfg.indCart[i255];
        }
        ctx->cfg.indRot.size[0] = r1.cfg.indRot.size(0);
        ml_loop_ub = r1.cfg.indRot.size(0);
        for (int i256{0}; i256 < ml_loop_ub; i256++) {
            ctx->cfg.indRot.data[i256] = r1.cfg.indRot[i256];
        }
        ctx->cfg.NumberAxis = r1.cfg.NumberAxis;
        ctx->cfg.NCart = r1.cfg.NCart;
        ctx->cfg.NRot = r1.cfg.NRot;
        ctx->cfg.D.size[0] = r1.cfg.D.size(0);
        ul_loop_ub = r1.cfg.D.size(0);
        for (int i259{0}; i259 < ul_loop_ub; i259++) {
            ctx->cfg.D.data[i259] = r1.cfg.D[i259];
        }
        ctx->cfg.coeffD = r1.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r1.cfg.kin_params.size[0];
        vl_loop_ub = r1.cfg.kin_params.size[0];
        if (vl_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.kin_params.data[0], &r1.cfg.kin_params.data[vl_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i266{0}; i266 < 8; i266++) {
            ctx->cfg.kin_type[i266] = r1.cfg.kin_type[i266];
        }
        ctx->cfg.NDiscr = r1.cfg.NDiscr;
        ctx->cfg.NBreak = r1.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = r1.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = r1.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = r1.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r1.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r1.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r1.cfg.NHorz;
        for (int i269{0}; i269 < 6; i269++) {
            ctx->cfg.vmax[i269] = r1.cfg.vmax[i269];
            ctx->cfg.amax[i269] = r1.cfg.amax[i269];
            ctx->cfg.jmax[i269] = r1.cfg.jmax[i269];
        }
        ctx->cfg.LeeSplineDegree = r1.cfg.LeeSplineDegree;
        ctx->cfg.SplineDegree = r1.cfg.SplineDegree;
        ctx->cfg.CutOff = r1.cfg.CutOff;
        ctx->cfg.LSplit = r1.cfg.LSplit;
        ctx->cfg.LSplitZero = r1.cfg.LSplitZero;
        ctx->cfg.LThresholdMax = r1.cfg.LThresholdMax;
        ctx->cfg.LThresholdMin = r1.cfg.LThresholdMin;
        ctx->cfg.v_0 = r1.cfg.v_0;
        ctx->cfg.at_0 = r1.cfg.at_0;
        ctx->cfg.v_1 = r1.cfg.v_1;
        ctx->cfg.at_1 = r1.cfg.at_1;
        ctx->cfg.dt = r1.cfg.dt;
        ctx->cfg.DefaultZeroStopCount = r1.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = r1.cfg.source.size[1];
        jm_loop_ub = r1.cfg.source.size[1];
        if (jm_loop_ub - 1 >= 0) {
            std::copy(&r1.cfg.source.data[0], &r1.cfg.source.data[jm_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = r1.cfg.Cusp;
        ctx->cfg.Compressing = r1.cfg.Compressing;
        ctx->cfg.Smoothing = r1.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = r1.cfg.GaussLegendreN;
        for (int p_i{0}; p_i < 5; p_i++) {
            ctx->cfg.GaussLegendreX[p_i] = r1.cfg.GaussLegendreX[p_i];
            ctx->cfg.GaussLegendreW[p_i] = r1.cfg.GaussLegendreW[p_i];
        }
        ctx->cfg.opt = r1.cfg.opt;
        for (int i288{0}; i288 < 9; i288++) {
            ctx->cfg.LogFileName[i288] = r1.cfg.LogFileName[i288];
        }
        ctx->jmax_increase_count = r1.jmax_increase_count;
        ctx->zero_start = r1.zero_start;
        ctx->zero_end = r1.zero_end;
        ctx->zero_forced = r1.zero_forced;
        ctx->zero_forced_buffer[0] = r1.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = r1.zero_forced_buffer[1];
        ctx->simplex_calls = r1.simplex_calls;
        ctx->forced_stop = r1.forced_stop;
        ctx->programmed_stop = r1.programmed_stop;
        ctx->Coeff.set_size(r1.Coeff.size(0), r1.Coeff.size(1));
        in_loop_ub = r1.Coeff.size(1);
        for (int i305{0}; i305 < in_loop_ub; i305++) {
            int jn_loop_ub;
            jn_loop_ub = r1.Coeff.size(0);
            for (int i306{0}; i306 < jn_loop_ub; i306++) {
                ctx->Coeff[i306 + ctx->Coeff.size(0) * i305] =
                    r1.Coeff[i306 + r1.Coeff.size(0) * i305];
            }
        }
        ctx->Skipped = r1.Skipped;
        ctx->kin = r1.kin;
        ctx->errmsg = r1.errmsg;
        ctx->errcode = r1.errcode;
        // 'FeedoptPlan:125' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:126' if( ctx.cfg.ReleaseMemoryOfTheQueues )
        if (r1.cfg.ReleaseMemoryOfTheQueues) {
            // 'FeedoptPlan:126' ctx.q_gcode.delete();
            r1.q_gcode.queue_coder_delete();
        }
    } break;
    case Fopt_Smooth: {
        int ab_loop_ub;
        int ad_loop_ub;
        int bk_loop_ub;
        int ce_loop_ub;
        int cf_loop_ub;
        int dc_loop_ub;
        int do_loop_ub;
        int eh_loop_ub;
        int f_loop_ub;
        int fn_loop_ub;
        int gd_loop_ub;
        int gk_loop_ub;
        int go_loop_ub;
        int hg_loop_ub;
        int ij_loop_ub;
        int jf_loop_ub;
        int jo_loop_ub;
        int kn_loop_ub;
        int le_loop_ub;
        int lm_loop_ub;
        int lo_loop_ub;
        int m_loop_ub;
        int nd_loop_ub;
        int ob_loop_ub;
        int oh_loop_ub;
        int ok_loop_ub;
        int pl_loop_ub;
        int pm_loop_ub;
        int pn_loop_ub;
        int qc_loop_ub;
        int se_loop_ub;
        int sg_loop_ub;
        int sj_loop_ub;
        int so_loop_ub;
        int tm_loop_ub;
        int tn_loop_ub;
        int ud_loop_ub;
        int uk_loop_ub;
        int wi_loop_ub;
        int wo_loop_ub;
        int xh_loop_ub;
        int yf_loop_ub;
        int yl_loop_ub;
        int ym_loop_ub;
        int yn_loop_ub;
        // 'FeedoptPlan:128' case Fopt.Smooth
        // 'FeedoptPlan:129' ctx = smoothCurvStructs(ctx);
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        f_loop_ub = ctx->BasisVal.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            int k_loop_ub;
            k_loop_ub = ctx->BasisVal.size(0);
            for (int i11{0}; i11 < k_loop_ub; i11++) {
                r.BasisVal[i11 + r.BasisVal.size(0) * i5] =
                    ctx->BasisVal[i11 + ctx->BasisVal.size(0) * i5];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        m_loop_ub = ctx->BasisValD.size(1);
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            int v_loop_ub;
            v_loop_ub = ctx->BasisValD.size(0);
            for (int i22{0}; i22 < v_loop_ub; i22++) {
                r.BasisValD[i22 + r.BasisValD.size(0) * i13] =
                    ctx->BasisValD[i22 + ctx->BasisValD.size(0) * i13];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        ab_loop_ub = ctx->BasisValDD.size(1);
        for (int i26{0}; i26 < ab_loop_ub; i26++) {
            int kb_loop_ub;
            kb_loop_ub = ctx->BasisValDD.size(0);
            for (int i36{0}; i36 < kb_loop_ub; i36++) {
                r.BasisValDD[i36 + r.BasisValDD.size(0) * i26] =
                    ctx->BasisValDD[i36 + ctx->BasisValDD.size(0) * i26];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        ob_loop_ub = ctx->BasisValDDD.size(1);
        for (int i40{0}; i40 < ob_loop_ub; i40++) {
            int yb_loop_ub;
            yb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i50{0}; i50 < yb_loop_ub; i50++) {
                r.BasisValDDD[i50 + r.BasisValDDD.size(0) * i40] =
                    ctx->BasisValDDD[i50 + ctx->BasisValDDD.size(0) * i40];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        dc_loop_ub = ctx->BasisIntegr.size(0);
        for (int i54{0}; i54 < dc_loop_ub; i54++) {
            r.BasisIntegr[i54] = ctx->BasisIntegr[i54];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        qc_loop_ub = ctx->u_vec.size(1);
        for (int i67{0}; i67 < qc_loop_ub; i67++) {
            r.u_vec[i67] = ctx->u_vec[i67];
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
        r.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        ad_loop_ub = ctx->cfg.maskTot.size[1];
        if (ad_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[ad_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        gd_loop_ub = ctx->cfg.maskCart.size[1];
        if (gd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[gd_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        nd_loop_ub = ctx->cfg.maskRot.size[1];
        if (nd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[nd_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ud_loop_ub = ctx->cfg.indCart.size[0];
        for (int i76{0}; i76 < ud_loop_ub; i76++) {
            r.cfg.indCart[i76] = ctx->cfg.indCart.data[i76];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        ce_loop_ub = ctx->cfg.indRot.size[0];
        for (int i81{0}; i81 < ce_loop_ub; i81++) {
            r.cfg.indRot[i81] = ctx->cfg.indRot.data[i81];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        le_loop_ub = ctx->cfg.D.size[0];
        for (int i89{0}; i89 < le_loop_ub; i89++) {
            r.cfg.D[i89] = ctx->cfg.D.data[i89];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        se_loop_ub = ctx->cfg.kin_params.size[0];
        if (se_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[se_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i97{0}; i97 < 8; i97++) {
            r.cfg.kin_type[i97] = ctx->cfg.kin_type[i97];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        r.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        for (int i106{0}; i106 < 6; i106++) {
            r.cfg.vmax[i106] = ctx->cfg.vmax[i106];
            r.cfg.amax[i106] = ctx->cfg.amax[i106];
            r.cfg.jmax[i106] = ctx->cfg.jmax[i106];
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
        r.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        r.cfg.source.size[0] = 1;
        r.cfg.source.size[1] = ctx->cfg.source.size[1];
        cf_loop_ub = ctx->cfg.source.size[1];
        if (cf_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[cf_loop_ub],
                      &r.cfg.source.data[0]);
        }
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int b_i{0}; b_i < 5; b_i++) {
            r.cfg.GaussLegendreX[b_i] = ctx->cfg.GaussLegendreX[b_i];
            r.cfg.GaussLegendreW[b_i] = ctx->cfg.GaussLegendreW[b_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i113{0}; i113 < 9; i113++) {
            r.cfg.LogFileName[i113] = ctx->cfg.LogFileName[i113];
        }
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.zero_forced = ctx->zero_forced;
        r.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        r.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        jf_loop_ub = ctx->Coeff.size(1);
        for (int i120{0}; i120 < jf_loop_ub; i120++) {
            int of_loop_ub;
            of_loop_ub = ctx->Coeff.size(0);
            for (int i125{0}; i125 < of_loop_ub; i125++) {
                r.Coeff[i125 + r.Coeff.size(0) * i120] =
                    ctx->Coeff[i125 + ctx->Coeff.size(0) * i120];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        r.errmsg = ctx->errmsg;
        r.errcode = ctx->errcode;
        smoothCurvStructs(&r);
        // 'FeedoptPlan:130' ctx.op = Fopt.Split;
        // 'FeedoptPlan:132' ctx = assert_queue( ctx, ctx.op, ctx.q_smooth );
        b_ctx.BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        yf_loop_ub = r.BasisVal.size(1);
        for (int i135{0}; i135 < yf_loop_ub; i135++) {
            int eg_loop_ub;
            eg_loop_ub = r.BasisVal.size(0);
            for (int i140{0}; i140 < eg_loop_ub; i140++) {
                b_ctx.BasisVal[i140 + b_ctx.BasisVal.size(0) * i135] =
                    r.BasisVal[i140 + r.BasisVal.size(0) * i135];
            }
        }
        b_ctx.BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        hg_loop_ub = r.BasisValD.size(1);
        for (int i143{0}; i143 < hg_loop_ub; i143++) {
            int pg_loop_ub;
            pg_loop_ub = r.BasisValD.size(0);
            for (int i151{0}; i151 < pg_loop_ub; i151++) {
                b_ctx.BasisValD[i151 + b_ctx.BasisValD.size(0) * i143] =
                    r.BasisValD[i151 + r.BasisValD.size(0) * i143];
            }
        }
        b_ctx.BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        sg_loop_ub = r.BasisValDD.size(1);
        for (int i154{0}; i154 < sg_loop_ub; i154++) {
            int bh_loop_ub;
            bh_loop_ub = r.BasisValDD.size(0);
            for (int i161{0}; i161 < bh_loop_ub; i161++) {
                b_ctx.BasisValDD[i161 + b_ctx.BasisValDD.size(0) * i154] =
                    r.BasisValDD[i161 + r.BasisValDD.size(0) * i154];
            }
        }
        b_ctx.BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        eh_loop_ub = r.BasisValDDD.size(1);
        for (int i165{0}; i165 < eh_loop_ub; i165++) {
            int lh_loop_ub;
            lh_loop_ub = r.BasisValDDD.size(0);
            for (int i172{0}; i172 < lh_loop_ub; i172++) {
                b_ctx.BasisValDDD[i172 + b_ctx.BasisValDDD.size(0) * i165] =
                    r.BasisValDDD[i172 + r.BasisValDDD.size(0) * i165];
            }
        }
        b_ctx.BasisIntegr.set_size(r.BasisIntegr.size(0));
        oh_loop_ub = r.BasisIntegr.size(0);
        for (int i175{0}; i175 < oh_loop_ub; i175++) {
            b_ctx.BasisIntegr[i175] = r.BasisIntegr[i175];
        }
        b_ctx.Bl = r.Bl;
        b_ctx.u_vec.set_size(1, r.u_vec.size(1));
        xh_loop_ub = r.u_vec.size(1);
        for (int i184{0}; i184 < xh_loop_ub; i184++) {
            b_ctx.u_vec[i184] = r.u_vec[i184];
        }
        b_ctx.q_spline = r.q_spline;
        b_ctx.q_gcode = r.q_gcode;
        b_ctx.q_compress = r.q_compress;
        b_ctx.q_smooth = r.q_smooth;
        b_ctx.q_split = r.q_split;
        b_ctx.q_opt = r.q_opt;
        b_ctx.op = Fopt_Split;
        b_ctx.go_next = r.go_next;
        b_ctx.try_push_again = r.try_push_again;
        b_ctx.n_optimized = r.n_optimized;
        b_ctx.reached_end = r.reached_end;
        b_ctx.k0 = r.k0;
        b_ctx.v_0 = r.v_0;
        b_ctx.v_1 = r.v_1;
        b_ctx.at_0 = r.at_0;
        b_ctx.at_1 = r.at_1;
        b_ctx.cfg.ENABLE_PRINT_MSG = r.cfg.ENABLE_PRINT_MSG;
        b_ctx.cfg.maskTot.size[0] = 1;
        b_ctx.cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
        wi_loop_ub = r.cfg.maskTot.size[1];
        if (wi_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[wi_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        ij_loop_ub = r.cfg.maskCart.size[1];
        if (ij_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[ij_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        sj_loop_ub = r.cfg.maskRot.size[1];
        if (sj_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[sj_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(r.cfg.indCart.size(0));
        bk_loop_ub = r.cfg.indCart.size(0);
        for (int i224{0}; i224 < bk_loop_ub; i224++) {
            b_ctx.cfg.indCart[i224] = r.cfg.indCart[i224];
        }
        b_ctx.cfg.indRot.set_size(r.cfg.indRot.size(0));
        gk_loop_ub = r.cfg.indRot.size(0);
        for (int i229{0}; i229 < gk_loop_ub; i229++) {
            b_ctx.cfg.indRot[i229] = r.cfg.indRot[i229];
        }
        b_ctx.cfg.NumberAxis = r.cfg.NumberAxis;
        b_ctx.cfg.NCart = r.cfg.NCart;
        b_ctx.cfg.NRot = r.cfg.NRot;
        b_ctx.cfg.D.set_size(r.cfg.D.size(0));
        ok_loop_ub = r.cfg.D.size(0);
        for (int i235{0}; i235 < ok_loop_ub; i235++) {
            b_ctx.cfg.D[i235] = r.cfg.D[i235];
        }
        b_ctx.cfg.coeffD = r.cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        uk_loop_ub = r.cfg.kin_params.size[0];
        if (uk_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[uk_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i240{0}; i240 < 8; i240++) {
            b_ctx.cfg.kin_type[i240] = r.cfg.kin_type[i240];
        }
        b_ctx.cfg.NDiscr = r.cfg.NDiscr;
        b_ctx.cfg.NBreak = r.cfg.NBreak;
        b_ctx.cfg.SplitSpecialSpline = r.cfg.SplitSpecialSpline;
        b_ctx.cfg.ReleaseMemoryOfTheQueues = r.cfg.ReleaseMemoryOfTheQueues;
        b_ctx.cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = r.cfg.NHorz;
        for (int i247{0}; i247 < 6; i247++) {
            b_ctx.cfg.vmax[i247] = r.cfg.vmax[i247];
            b_ctx.cfg.amax[i247] = r.cfg.amax[i247];
            b_ctx.cfg.jmax[i247] = r.cfg.jmax[i247];
        }
        b_ctx.cfg.LeeSplineDegree = r.cfg.LeeSplineDegree;
        b_ctx.cfg.SplineDegree = r.cfg.SplineDegree;
        b_ctx.cfg.CutOff = r.cfg.CutOff;
        b_ctx.cfg.LSplit = r.cfg.LSplit;
        b_ctx.cfg.LSplitZero = r.cfg.LSplitZero;
        b_ctx.cfg.LThresholdMax = r.cfg.LThresholdMax;
        b_ctx.cfg.LThresholdMin = r.cfg.LThresholdMin;
        b_ctx.cfg.v_0 = r.cfg.v_0;
        b_ctx.cfg.at_0 = r.cfg.at_0;
        b_ctx.cfg.v_1 = r.cfg.v_1;
        b_ctx.cfg.at_1 = r.cfg.at_1;
        b_ctx.cfg.dt = r.cfg.dt;
        b_ctx.cfg.DefaultZeroStopCount = r.cfg.DefaultZeroStopCount;
        b_ctx.cfg.source.size[0] = 1;
        b_ctx.cfg.source.size[1] = r.cfg.source.size[1];
        pl_loop_ub = r.cfg.source.size[1];
        if (pl_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.source.data[0], &r.cfg.source.data[pl_loop_ub],
                      &b_ctx.cfg.source.data[0]);
        }
        b_ctx.cfg.Cusp = r.cfg.Cusp;
        b_ctx.cfg.Compressing = r.cfg.Compressing;
        b_ctx.cfg.Smoothing = r.cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int j_i{0}; j_i < 5; j_i++) {
            b_ctx.cfg.GaussLegendreX[j_i] = r.cfg.GaussLegendreX[j_i];
            b_ctx.cfg.GaussLegendreW[j_i] = r.cfg.GaussLegendreW[j_i];
        }
        b_ctx.cfg.opt = r.cfg.opt;
        for (int i262{0}; i262 < 9; i262++) {
            b_ctx.cfg.LogFileName[i262] = r.cfg.LogFileName[i262];
        }
        b_ctx.jmax_increase_count = r.jmax_increase_count;
        b_ctx.zero_start = r.zero_start;
        b_ctx.zero_end = r.zero_end;
        b_ctx.zero_forced = r.zero_forced;
        b_ctx.zero_forced_buffer[0] = r.zero_forced_buffer[0];
        b_ctx.zero_forced_buffer[1] = r.zero_forced_buffer[1];
        b_ctx.simplex_calls = r.simplex_calls;
        b_ctx.forced_stop = r.forced_stop;
        b_ctx.programmed_stop = r.programmed_stop;
        b_ctx.Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        yl_loop_ub = r.Coeff.size(1);
        for (int i270{0}; i270 < yl_loop_ub; i270++) {
            int em_loop_ub;
            em_loop_ub = r.Coeff.size(0);
            for (int i275{0}; i275 < em_loop_ub; i275++) {
                b_ctx.Coeff[i275 + b_ctx.Coeff.size(0) * i270] =
                    r.Coeff[i275 + r.Coeff.size(0) * i270];
            }
        }
        bool e_isValid;
        bool g_isValid;
        b_ctx.Skipped = r.Skipped;
        b_ctx.kin = r.kin;
        b_ctx.errmsg = r.errmsg;
        b_ctx.errcode = r.errcode;
        // 'FeedoptPlan:172' msg = string( op );
        // 'FeedoptPlan:173' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:174'     msg + " - Check geometry failed...", mfilename );
        x_ocn_assert(checkGeometry(&r.q_smooth));
        // 'FeedoptPlan:176' [ isValid, ctx ] = checkZSpdmode( ctx, queue );
        e_isValid = checkZSpdmode(&b_ctx, &r.q_smooth);
        // 'FeedoptPlan:177' ocn_assert( isValid, ...
        // 'FeedoptPlan:178'     msg + " - Check zspdmode failed...", mfilename );
        y_ocn_assert(e_isValid);
        // 'FeedoptPlan:180' isValid = checkParametrisationQueue( queue );
        g_isValid = checkParametrisationQueue(&r.q_smooth);
        // 'FeedoptPlan:181' ocn_assert( isValid, ...
        // 'FeedoptPlan:182'     msg + " - Check parametrisation failed...", mfilename );
        ab_ocn_assert(g_isValid);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        lm_loop_ub = b_ctx.BasisVal.size(1);
        for (int i282{0}; i282 < lm_loop_ub; i282++) {
            int om_loop_ub;
            om_loop_ub = b_ctx.BasisVal.size(0);
            for (int i285{0}; i285 < om_loop_ub; i285++) {
                ctx->BasisVal[i285 + ctx->BasisVal.size(0) * i282] =
                    b_ctx.BasisVal[i285 + b_ctx.BasisVal.size(0) * i282];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        pm_loop_ub = b_ctx.BasisValD.size(1);
        for (int i286{0}; i286 < pm_loop_ub; i286++) {
            int sm_loop_ub;
            sm_loop_ub = b_ctx.BasisValD.size(0);
            for (int i290{0}; i290 < sm_loop_ub; i290++) {
                ctx->BasisValD[i290 + ctx->BasisValD.size(0) * i286] =
                    b_ctx.BasisValD[i290 + b_ctx.BasisValD.size(0) * i286];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        tm_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i291{0}; i291 < tm_loop_ub; i291++) {
            int xm_loop_ub;
            xm_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i294{0}; i294 < xm_loop_ub; i294++) {
                ctx->BasisValDD[i294 + ctx->BasisValDD.size(0) * i291] =
                    b_ctx.BasisValDD[i294 + b_ctx.BasisValDD.size(0) * i291];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        ym_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i295{0}; i295 < ym_loop_ub; i295++) {
            int dn_loop_ub;
            dn_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i300{0}; i300 < dn_loop_ub; i300++) {
                ctx->BasisValDDD[i300 + ctx->BasisValDDD.size(0) * i295] =
                    b_ctx.BasisValDDD[i300 + b_ctx.BasisValDDD.size(0) * i295];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        fn_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i302{0}; i302 < fn_loop_ub; i302++) {
            ctx->BasisIntegr[i302] = b_ctx.BasisIntegr[i302];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        kn_loop_ub = b_ctx.u_vec.size(1);
        for (int i307{0}; i307 < kn_loop_ub; i307++) {
            ctx->u_vec[i307] = b_ctx.u_vec[i307];
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
        ctx->cfg.ENABLE_PRINT_MSG = b_ctx.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = b_ctx.cfg.maskTot.size[1];
        pn_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (pn_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[pn_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        tn_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (tn_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[tn_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        yn_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (yn_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[yn_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        do_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i319{0}; i319 < do_loop_ub; i319++) {
            ctx->cfg.indCart.data[i319] = b_ctx.cfg.indCart[i319];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        go_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i322{0}; i322 < go_loop_ub; i322++) {
            ctx->cfg.indRot.data[i322] = b_ctx.cfg.indRot[i322];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        jo_loop_ub = b_ctx.cfg.D.size(0);
        for (int i325{0}; i325 < jo_loop_ub; i325++) {
            ctx->cfg.D.data[i325] = b_ctx.cfg.D[i325];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        lo_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (lo_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[lo_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i327{0}; i327 < 8; i327++) {
            ctx->cfg.kin_type[i327] = b_ctx.cfg.kin_type[i327];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = b_ctx.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = b_ctx.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        for (int i329{0}; i329 < 6; i329++) {
            ctx->cfg.vmax[i329] = b_ctx.cfg.vmax[i329];
            ctx->cfg.amax[i329] = b_ctx.cfg.amax[i329];
            ctx->cfg.jmax[i329] = b_ctx.cfg.jmax[i329];
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
        ctx->cfg.DefaultZeroStopCount = b_ctx.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = b_ctx.cfg.source.size[1];
        so_loop_ub = b_ctx.cfg.source.size[1];
        if (so_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.source.data[0], &b_ctx.cfg.source.data[so_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = b_ctx.cfg.Cusp;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int q_i{0}; q_i < 5; q_i++) {
            ctx->cfg.GaussLegendreX[q_i] = b_ctx.cfg.GaussLegendreX[q_i];
            ctx->cfg.GaussLegendreW[q_i] = b_ctx.cfg.GaussLegendreW[q_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i334{0}; i334 < 9; i334++) {
            ctx->cfg.LogFileName[i334] = b_ctx.cfg.LogFileName[i334];
        }
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->zero_forced = b_ctx.zero_forced;
        ctx->zero_forced_buffer[0] = b_ctx.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = b_ctx.zero_forced_buffer[1];
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        wo_loop_ub = b_ctx.Coeff.size(1);
        for (int i337{0}; i337 < wo_loop_ub; i337++) {
            int yo_loop_ub;
            yo_loop_ub = b_ctx.Coeff.size(0);
            for (int i340{0}; i340 < yo_loop_ub; i340++) {
                ctx->Coeff[i340 + ctx->Coeff.size(0) * i337] =
                    b_ctx.Coeff[i340 + b_ctx.Coeff.size(0) * i337];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        ctx->errmsg = b_ctx.errmsg;
        ctx->errcode = b_ctx.errcode;
        // 'FeedoptPlan:134' if( ctx.cfg.ReleaseMemoryOfTheQueues )
        if (b_ctx.cfg.ReleaseMemoryOfTheQueues) {
            // 'FeedoptPlan:134' ctx.q_compress.delete();
            b_ctx.q_compress.queue_coder_delete();
        }
    } break;
    case Fopt_Split: {
        int bb_loop_ub;
        int bd_loop_ub;
        int bg_loop_ub;
        int bi_loop_ub;
        int bj_loop_ub;
        int bm_loop_ub;
        int bo_loop_ub;
        int cn_loop_ub;
        int de_loop_ub;
        int df_loop_ub;
        int dk_loop_ub;
        int ec_loop_ub;
        int fo_loop_ub;
        int g_loop_ub;
        int hd_loop_ub;
        int hh_loop_ub;
        int hn_loop_ub;
        int ho_loop_ub;
        int jk_loop_ub;
        int kf_loop_ub;
        int ko_loop_ub;
        int lg_loop_ub;
        int lj_loop_ub;
        int ln_loop_ub;
        int me_loop_ub;
        int mo_loop_ub;
        int n_loop_ub;
        int nm_loop_ub;
        int od_loop_ub;
        int pb_loop_ub;
        int qk_loop_ub;
        int qn_loop_ub;
        int rc_loop_ub;
        int rl_loop_ub;
        int rm_loop_ub;
        int sh_loop_ub;
        int te_loop_ub;
        int to_loop_ub;
        int uj_loop_ub;
        int vd_loop_ub;
        int vg_loop_ub;
        int vm_loop_ub;
        int vn_loop_ub;
        int wk_loop_ub;
        int xo_loop_ub;
        // 'FeedoptPlan:136' case Fopt.Split
        // 'FeedoptPlan:137' ctx     = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        g_loop_ub = ctx->BasisVal.size(1);
        for (int i6{0}; i6 < g_loop_ub; i6++) {
            int l_loop_ub;
            l_loop_ub = ctx->BasisVal.size(0);
            for (int i12{0}; i12 < l_loop_ub; i12++) {
                r.BasisVal[i12 + r.BasisVal.size(0) * i6] =
                    ctx->BasisVal[i12 + ctx->BasisVal.size(0) * i6];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        n_loop_ub = ctx->BasisValD.size(1);
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            int w_loop_ub;
            w_loop_ub = ctx->BasisValD.size(0);
            for (int i23{0}; i23 < w_loop_ub; i23++) {
                r.BasisValD[i23 + r.BasisValD.size(0) * i14] =
                    ctx->BasisValD[i23 + ctx->BasisValD.size(0) * i14];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        bb_loop_ub = ctx->BasisValDD.size(1);
        for (int i27{0}; i27 < bb_loop_ub; i27++) {
            int lb_loop_ub;
            lb_loop_ub = ctx->BasisValDD.size(0);
            for (int i37{0}; i37 < lb_loop_ub; i37++) {
                r.BasisValDD[i37 + r.BasisValDD.size(0) * i27] =
                    ctx->BasisValDD[i37 + ctx->BasisValDD.size(0) * i27];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        pb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i41{0}; i41 < pb_loop_ub; i41++) {
            int ac_loop_ub;
            ac_loop_ub = ctx->BasisValDDD.size(0);
            for (int i51{0}; i51 < ac_loop_ub; i51++) {
                r.BasisValDDD[i51 + r.BasisValDDD.size(0) * i41] =
                    ctx->BasisValDDD[i51 + ctx->BasisValDDD.size(0) * i41];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        ec_loop_ub = ctx->BasisIntegr.size(0);
        for (int i55{0}; i55 < ec_loop_ub; i55++) {
            r.BasisIntegr[i55] = ctx->BasisIntegr[i55];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        rc_loop_ub = ctx->u_vec.size(1);
        for (int i68{0}; i68 < rc_loop_ub; i68++) {
            r.u_vec[i68] = ctx->u_vec[i68];
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
        r.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        r.cfg.maskTot.size[0] = 1;
        r.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        bd_loop_ub = ctx->cfg.maskTot.size[1];
        if (bd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[bd_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        hd_loop_ub = ctx->cfg.maskCart.size[1];
        if (hd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[hd_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        od_loop_ub = ctx->cfg.maskRot.size[1];
        if (od_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[od_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        vd_loop_ub = ctx->cfg.indCart.size[0];
        for (int i77{0}; i77 < vd_loop_ub; i77++) {
            r.cfg.indCart[i77] = ctx->cfg.indCart.data[i77];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        de_loop_ub = ctx->cfg.indRot.size[0];
        for (int i82{0}; i82 < de_loop_ub; i82++) {
            r.cfg.indRot[i82] = ctx->cfg.indRot.data[i82];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        me_loop_ub = ctx->cfg.D.size[0];
        for (int i90{0}; i90 < me_loop_ub; i90++) {
            r.cfg.D[i90] = ctx->cfg.D.data[i90];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        te_loop_ub = ctx->cfg.kin_params.size[0];
        if (te_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[te_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i98{0}; i98 < 8; i98++) {
            r.cfg.kin_type[i98] = ctx->cfg.kin_type[i98];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        r.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        for (int i107{0}; i107 < 6; i107++) {
            r.cfg.vmax[i107] = ctx->cfg.vmax[i107];
            r.cfg.amax[i107] = ctx->cfg.amax[i107];
            r.cfg.jmax[i107] = ctx->cfg.jmax[i107];
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
        r.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        r.cfg.source.size[0] = 1;
        r.cfg.source.size[1] = ctx->cfg.source.size[1];
        df_loop_ub = ctx->cfg.source.size[1];
        if (df_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[df_loop_ub],
                      &r.cfg.source.data[0]);
        }
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int c_i{0}; c_i < 5; c_i++) {
            r.cfg.GaussLegendreX[c_i] = ctx->cfg.GaussLegendreX[c_i];
            r.cfg.GaussLegendreW[c_i] = ctx->cfg.GaussLegendreW[c_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i114{0}; i114 < 9; i114++) {
            r.cfg.LogFileName[i114] = ctx->cfg.LogFileName[i114];
        }
        r.jmax_increase_count = ctx->jmax_increase_count;
        r.zero_start = ctx->zero_start;
        r.zero_end = ctx->zero_end;
        r.zero_forced = ctx->zero_forced;
        r.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        r.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        r.simplex_calls = ctx->simplex_calls;
        r.forced_stop = ctx->forced_stop;
        r.programmed_stop = ctx->programmed_stop;
        r.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        kf_loop_ub = ctx->Coeff.size(1);
        for (int i121{0}; i121 < kf_loop_ub; i121++) {
            int pf_loop_ub;
            pf_loop_ub = ctx->Coeff.size(0);
            for (int i126{0}; i126 < pf_loop_ub; i126++) {
                r.Coeff[i126 + r.Coeff.size(0) * i121] =
                    ctx->Coeff[i126 + ctx->Coeff.size(0) * i121];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        r.errmsg = ctx->errmsg;
        r.errcode = ctx->errcode;
        splitQueue(&r);
        // 'FeedoptPlan:138' ctx.op  = Fopt.Opt;
        // 'FeedoptPlan:140' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:144' ctx = assert_queue( ctx, ctx.op, ctx.q_split );
        b_ctx.BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        bg_loop_ub = r.BasisVal.size(1);
        for (int i137{0}; i137 < bg_loop_ub; i137++) {
            int ig_loop_ub;
            ig_loop_ub = r.BasisVal.size(0);
            for (int i144{0}; i144 < ig_loop_ub; i144++) {
                b_ctx.BasisVal[i144 + b_ctx.BasisVal.size(0) * i137] =
                    r.BasisVal[i144 + r.BasisVal.size(0) * i137];
            }
        }
        b_ctx.BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        lg_loop_ub = r.BasisValD.size(1);
        for (int i146{0}; i146 < lg_loop_ub; i146++) {
            int tg_loop_ub;
            tg_loop_ub = r.BasisValD.size(0);
            for (int i155{0}; i155 < tg_loop_ub; i155++) {
                b_ctx.BasisValD[i155 + b_ctx.BasisValD.size(0) * i146] =
                    r.BasisValD[i155 + r.BasisValD.size(0) * i146];
            }
        }
        b_ctx.BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        vg_loop_ub = r.BasisValDD.size(1);
        for (int i157{0}; i157 < vg_loop_ub; i157++) {
            int fh_loop_ub;
            fh_loop_ub = r.BasisValDD.size(0);
            for (int i166{0}; i166 < fh_loop_ub; i166++) {
                b_ctx.BasisValDD[i166 + b_ctx.BasisValDD.size(0) * i157] =
                    r.BasisValDD[i166 + r.BasisValDD.size(0) * i157];
            }
        }
        b_ctx.BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        hh_loop_ub = r.BasisValDDD.size(1);
        for (int i168{0}; i168 < hh_loop_ub; i168++) {
            int ph_loop_ub;
            ph_loop_ub = r.BasisValDDD.size(0);
            for (int i176{0}; i176 < ph_loop_ub; i176++) {
                b_ctx.BasisValDDD[i176 + b_ctx.BasisValDDD.size(0) * i168] =
                    r.BasisValDDD[i176 + r.BasisValDDD.size(0) * i168];
            }
        }
        b_ctx.BasisIntegr.set_size(r.BasisIntegr.size(0));
        sh_loop_ub = r.BasisIntegr.size(0);
        for (int i178{0}; i178 < sh_loop_ub; i178++) {
            b_ctx.BasisIntegr[i178] = r.BasisIntegr[i178];
        }
        b_ctx.Bl = r.Bl;
        b_ctx.u_vec.set_size(1, r.u_vec.size(1));
        bi_loop_ub = r.u_vec.size(1);
        for (int i186{0}; i186 < bi_loop_ub; i186++) {
            b_ctx.u_vec[i186] = r.u_vec[i186];
        }
        b_ctx.q_spline = r.q_spline;
        b_ctx.q_gcode = r.q_gcode;
        b_ctx.q_compress = r.q_compress;
        b_ctx.q_smooth = r.q_smooth;
        b_ctx.q_split = r.q_split;
        b_ctx.q_opt = r.q_opt;
        b_ctx.op = Fopt_Opt;
        b_ctx.go_next = r.go_next;
        b_ctx.try_push_again = r.try_push_again;
        b_ctx.n_optimized = r.n_optimized;
        b_ctx.reached_end = r.reached_end;
        b_ctx.k0 = r.k0;
        b_ctx.v_0 = r.v_0;
        b_ctx.v_1 = r.v_1;
        b_ctx.at_0 = r.at_0;
        b_ctx.at_1 = r.at_1;
        b_ctx.cfg.ENABLE_PRINT_MSG = r.cfg.ENABLE_PRINT_MSG;
        b_ctx.cfg.maskTot.size[0] = 1;
        b_ctx.cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
        bj_loop_ub = r.cfg.maskTot.size[1];
        if (bj_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[bj_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        lj_loop_ub = r.cfg.maskCart.size[1];
        if (lj_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[lj_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        uj_loop_ub = r.cfg.maskRot.size[1];
        if (uj_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[uj_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(r.cfg.indCart.size(0));
        dk_loop_ub = r.cfg.indCart.size(0);
        for (int i226{0}; i226 < dk_loop_ub; i226++) {
            b_ctx.cfg.indCart[i226] = r.cfg.indCart[i226];
        }
        b_ctx.cfg.indRot.set_size(r.cfg.indRot.size(0));
        jk_loop_ub = r.cfg.indRot.size(0);
        for (int i232{0}; i232 < jk_loop_ub; i232++) {
            b_ctx.cfg.indRot[i232] = r.cfg.indRot[i232];
        }
        b_ctx.cfg.NumberAxis = r.cfg.NumberAxis;
        b_ctx.cfg.NCart = r.cfg.NCart;
        b_ctx.cfg.NRot = r.cfg.NRot;
        b_ctx.cfg.D.set_size(r.cfg.D.size(0));
        qk_loop_ub = r.cfg.D.size(0);
        for (int i237{0}; i237 < qk_loop_ub; i237++) {
            b_ctx.cfg.D[i237] = r.cfg.D[i237];
        }
        b_ctx.cfg.coeffD = r.cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        wk_loop_ub = r.cfg.kin_params.size[0];
        if (wk_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[wk_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i242{0}; i242 < 8; i242++) {
            b_ctx.cfg.kin_type[i242] = r.cfg.kin_type[i242];
        }
        b_ctx.cfg.NDiscr = r.cfg.NDiscr;
        b_ctx.cfg.NBreak = r.cfg.NBreak;
        b_ctx.cfg.SplitSpecialSpline = r.cfg.SplitSpecialSpline;
        b_ctx.cfg.ReleaseMemoryOfTheQueues = r.cfg.ReleaseMemoryOfTheQueues;
        b_ctx.cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = r.cfg.NHorz;
        for (int i249{0}; i249 < 6; i249++) {
            b_ctx.cfg.vmax[i249] = r.cfg.vmax[i249];
            b_ctx.cfg.amax[i249] = r.cfg.amax[i249];
            b_ctx.cfg.jmax[i249] = r.cfg.jmax[i249];
        }
        b_ctx.cfg.LeeSplineDegree = r.cfg.LeeSplineDegree;
        b_ctx.cfg.SplineDegree = r.cfg.SplineDegree;
        b_ctx.cfg.CutOff = r.cfg.CutOff;
        b_ctx.cfg.LSplit = r.cfg.LSplit;
        b_ctx.cfg.LSplitZero = r.cfg.LSplitZero;
        b_ctx.cfg.LThresholdMax = r.cfg.LThresholdMax;
        b_ctx.cfg.LThresholdMin = r.cfg.LThresholdMin;
        b_ctx.cfg.v_0 = r.cfg.v_0;
        b_ctx.cfg.at_0 = r.cfg.at_0;
        b_ctx.cfg.v_1 = r.cfg.v_1;
        b_ctx.cfg.at_1 = r.cfg.at_1;
        b_ctx.cfg.dt = r.cfg.dt;
        b_ctx.cfg.DefaultZeroStopCount = r.cfg.DefaultZeroStopCount;
        b_ctx.cfg.source.size[0] = 1;
        b_ctx.cfg.source.size[1] = r.cfg.source.size[1];
        rl_loop_ub = r.cfg.source.size[1];
        if (rl_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.source.data[0], &r.cfg.source.data[rl_loop_ub],
                      &b_ctx.cfg.source.data[0]);
        }
        b_ctx.cfg.Cusp = r.cfg.Cusp;
        b_ctx.cfg.Compressing = r.cfg.Compressing;
        b_ctx.cfg.Smoothing = r.cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = r.cfg.GaussLegendreN;
        for (int l_i{0}; l_i < 5; l_i++) {
            b_ctx.cfg.GaussLegendreX[l_i] = r.cfg.GaussLegendreX[l_i];
            b_ctx.cfg.GaussLegendreW[l_i] = r.cfg.GaussLegendreW[l_i];
        }
        b_ctx.cfg.opt = r.cfg.opt;
        for (int i264{0}; i264 < 9; i264++) {
            b_ctx.cfg.LogFileName[i264] = r.cfg.LogFileName[i264];
        }
        b_ctx.jmax_increase_count = r.jmax_increase_count;
        b_ctx.zero_start = r.zero_start;
        b_ctx.zero_end = r.zero_end;
        b_ctx.zero_forced = r.zero_forced;
        b_ctx.zero_forced_buffer[0] = r.zero_forced_buffer[0];
        b_ctx.zero_forced_buffer[1] = r.zero_forced_buffer[1];
        b_ctx.simplex_calls = r.simplex_calls;
        b_ctx.forced_stop = r.forced_stop;
        b_ctx.programmed_stop = r.programmed_stop;
        b_ctx.Coeff.set_size(r.Coeff.size(0), r.Coeff.size(1));
        bm_loop_ub = r.Coeff.size(1);
        for (int i272{0}; i272 < bm_loop_ub; i272++) {
            int gm_loop_ub;
            gm_loop_ub = r.Coeff.size(0);
            for (int i277{0}; i277 < gm_loop_ub; i277++) {
                b_ctx.Coeff[i277 + b_ctx.Coeff.size(0) * i272] =
                    r.Coeff[i277 + r.Coeff.size(0) * i272];
            }
        }
        bool f_isValid;
        bool h_isValid;
        b_ctx.Skipped = r.Skipped;
        b_ctx.kin = r.kin;
        b_ctx.errmsg = r.errmsg;
        b_ctx.errcode = r.errcode;
        // 'FeedoptPlan:172' msg = string( op );
        // 'FeedoptPlan:173' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:174'     msg + " - Check geometry failed...", mfilename );
        kb_ocn_assert(checkGeometry(&r.q_split));
        // 'FeedoptPlan:176' [ isValid, ctx ] = checkZSpdmode( ctx, queue );
        f_isValid = checkZSpdmode(&b_ctx, &r.q_split);
        // 'FeedoptPlan:177' ocn_assert( isValid, ...
        // 'FeedoptPlan:178'     msg + " - Check zspdmode failed...", mfilename );
        lb_ocn_assert(f_isValid);
        // 'FeedoptPlan:180' isValid = checkParametrisationQueue( queue );
        h_isValid = checkParametrisationQueue(&r.q_split);
        // 'FeedoptPlan:181' ocn_assert( isValid, ...
        // 'FeedoptPlan:182'     msg + " - Check parametrisation failed...", mfilename );
        mb_ocn_assert(h_isValid);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        nm_loop_ub = b_ctx.BasisVal.size(1);
        for (int i284{0}; i284 < nm_loop_ub; i284++) {
            int qm_loop_ub;
            qm_loop_ub = b_ctx.BasisVal.size(0);
            for (int i287{0}; i287 < qm_loop_ub; i287++) {
                ctx->BasisVal[i287 + ctx->BasisVal.size(0) * i284] =
                    b_ctx.BasisVal[i287 + b_ctx.BasisVal.size(0) * i284];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        rm_loop_ub = b_ctx.BasisValD.size(1);
        for (int i289{0}; i289 < rm_loop_ub; i289++) {
            int um_loop_ub;
            um_loop_ub = b_ctx.BasisValD.size(0);
            for (int i292{0}; i292 < um_loop_ub; i292++) {
                ctx->BasisValD[i292 + ctx->BasisValD.size(0) * i289] =
                    b_ctx.BasisValD[i292 + b_ctx.BasisValD.size(0) * i289];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        vm_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i293{0}; i293 < vm_loop_ub; i293++) {
            int an_loop_ub;
            an_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i296{0}; i296 < an_loop_ub; i296++) {
                ctx->BasisValDD[i296 + ctx->BasisValDD.size(0) * i293] =
                    b_ctx.BasisValDD[i296 + b_ctx.BasisValDD.size(0) * i293];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        cn_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i299{0}; i299 < cn_loop_ub; i299++) {
            int gn_loop_ub;
            gn_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i303{0}; i303 < gn_loop_ub; i303++) {
                ctx->BasisValDDD[i303 + ctx->BasisValDDD.size(0) * i299] =
                    b_ctx.BasisValDDD[i303 + b_ctx.BasisValDDD.size(0) * i299];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        hn_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i304{0}; i304 < hn_loop_ub; i304++) {
            ctx->BasisIntegr[i304] = b_ctx.BasisIntegr[i304];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        ln_loop_ub = b_ctx.u_vec.size(1);
        for (int i308{0}; i308 < ln_loop_ub; i308++) {
            ctx->u_vec[i308] = b_ctx.u_vec[i308];
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
        ctx->cfg.ENABLE_PRINT_MSG = b_ctx.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = b_ctx.cfg.maskTot.size[1];
        qn_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (qn_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[qn_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        vn_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (vn_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[vn_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        bo_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (bo_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[bo_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        fo_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i321{0}; i321 < fo_loop_ub; i321++) {
            ctx->cfg.indCart.data[i321] = b_ctx.cfg.indCart[i321];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        ho_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i323{0}; i323 < ho_loop_ub; i323++) {
            ctx->cfg.indRot.data[i323] = b_ctx.cfg.indRot[i323];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        ko_loop_ub = b_ctx.cfg.D.size(0);
        for (int i326{0}; i326 < ko_loop_ub; i326++) {
            ctx->cfg.D.data[i326] = b_ctx.cfg.D[i326];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        mo_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (mo_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[mo_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i328{0}; i328 < 8; i328++) {
            ctx->cfg.kin_type[i328] = b_ctx.cfg.kin_type[i328];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = b_ctx.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = b_ctx.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        for (int i330{0}; i330 < 6; i330++) {
            ctx->cfg.vmax[i330] = b_ctx.cfg.vmax[i330];
            ctx->cfg.amax[i330] = b_ctx.cfg.amax[i330];
            ctx->cfg.jmax[i330] = b_ctx.cfg.jmax[i330];
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
        ctx->cfg.DefaultZeroStopCount = b_ctx.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = b_ctx.cfg.source.size[1];
        to_loop_ub = b_ctx.cfg.source.size[1];
        if (to_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.source.data[0], &b_ctx.cfg.source.data[to_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = b_ctx.cfg.Cusp;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int r_i{0}; r_i < 5; r_i++) {
            ctx->cfg.GaussLegendreX[r_i] = b_ctx.cfg.GaussLegendreX[r_i];
            ctx->cfg.GaussLegendreW[r_i] = b_ctx.cfg.GaussLegendreW[r_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i335{0}; i335 < 9; i335++) {
            ctx->cfg.LogFileName[i335] = b_ctx.cfg.LogFileName[i335];
        }
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->zero_forced = b_ctx.zero_forced;
        ctx->zero_forced_buffer[0] = b_ctx.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = b_ctx.zero_forced_buffer[1];
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        xo_loop_ub = b_ctx.Coeff.size(1);
        for (int i339{0}; i339 < xo_loop_ub; i339++) {
            int ap_loop_ub;
            ap_loop_ub = b_ctx.Coeff.size(0);
            for (int i341{0}; i341 < ap_loop_ub; i341++) {
                ctx->Coeff[i341 + ctx->Coeff.size(0) * i339] =
                    b_ctx.Coeff[i341 + b_ctx.Coeff.size(0) * i339];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        ctx->errmsg = b_ctx.errmsg;
        ctx->errcode = b_ctx.errcode;
        //          histogramLength( ctx, ctx.q_split, "Splitting" );
        // 'FeedoptPlan:147' if( ctx.cfg.ReleaseMemoryOfTheQueues )
        if (b_ctx.cfg.ReleaseMemoryOfTheQueues) {
            // 'FeedoptPlan:147' ctx.q_smooth.delete();
            b_ctx.q_smooth.queue_coder_delete();
        }
    } break;
    case Fopt_Opt: {
        int af_loop_ub;
        int cb_loop_ub;
        int cg_loop_ub;
        int cm_loop_ub;
        int dj_loop_ub;
        int ee_loop_ub;
        int ei_loop_ub;
        int ek_loop_ub;
        int fc_loop_ub;
        int fd_loop_ub;
        int hf_loop_ub;
        int je_loop_ub;
        int jh_loop_ub;
        int lk_loop_ub;
        int md_loop_ub;
        int mj_loop_ub;
        int ng_loop_ub;
        int o_loop_ub;
        int pc_loop_ub;
        int qb_loop_ub;
        int qf_loop_ub;
        int re_loop_ub;
        int rk_loop_ub;
        int sl_loop_ub;
        int uh_loop_ub;
        int vj_loop_ub;
        int wd_loop_ub;
        int xc_loop_ub;
        int xk_loop_ub;
        int yg_loop_ub;
        // 'FeedoptPlan:149' case Fopt.Opt
        // 'FeedoptPlan:150' if( ctx.q_opt.size() == 0 )
        if (ctx->q_opt.size() == 0U) {
            // 'FeedoptPlan:150' ctx.k0 = int32( 1 );
            ctx->k0 = 1;
        }
        //          ctx.op = Fopt.Finished; return;
        // 'FeedoptPlan:152' [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        b_ctx.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        o_loop_ub = ctx->BasisVal.size(1);
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            int x_loop_ub;
            x_loop_ub = ctx->BasisVal.size(0);
            for (int i24{0}; i24 < x_loop_ub; i24++) {
                b_ctx.BasisVal[i24 + b_ctx.BasisVal.size(0) * i15] =
                    ctx->BasisVal[i24 + ctx->BasisVal.size(0) * i15];
            }
        }
        b_ctx.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        cb_loop_ub = ctx->BasisValD.size(1);
        for (int i28{0}; i28 < cb_loop_ub; i28++) {
            int mb_loop_ub;
            mb_loop_ub = ctx->BasisValD.size(0);
            for (int i38{0}; i38 < mb_loop_ub; i38++) {
                b_ctx.BasisValD[i38 + b_ctx.BasisValD.size(0) * i28] =
                    ctx->BasisValD[i38 + ctx->BasisValD.size(0) * i28];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        qb_loop_ub = ctx->BasisValDD.size(1);
        for (int i42{0}; i42 < qb_loop_ub; i42++) {
            int bc_loop_ub;
            bc_loop_ub = ctx->BasisValDD.size(0);
            for (int i52{0}; i52 < bc_loop_ub; i52++) {
                b_ctx.BasisValDD[i52 + b_ctx.BasisValDD.size(0) * i42] =
                    ctx->BasisValDD[i52 + ctx->BasisValDD.size(0) * i42];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        fc_loop_ub = ctx->BasisValDDD.size(1);
        for (int i56{0}; i56 < fc_loop_ub; i56++) {
            int nc_loop_ub;
            nc_loop_ub = ctx->BasisValDDD.size(0);
            for (int i64{0}; i64 < nc_loop_ub; i64++) {
                b_ctx.BasisValDDD[i64 + b_ctx.BasisValDDD.size(0) * i56] =
                    ctx->BasisValDDD[i64 + ctx->BasisValDDD.size(0) * i56];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        pc_loop_ub = ctx->BasisIntegr.size(0);
        for (int i66{0}; i66 < pc_loop_ub; i66++) {
            b_ctx.BasisIntegr[i66] = ctx->BasisIntegr[i66];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        xc_loop_ub = ctx->u_vec.size(1);
        for (int i74{0}; i74 < xc_loop_ub; i74++) {
            b_ctx.u_vec[i74] = ctx->u_vec[i74];
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
        b_ctx.cfg.ENABLE_PRINT_MSG = ctx->cfg.ENABLE_PRINT_MSG;
        b_ctx.cfg.maskTot.size[0] = 1;
        b_ctx.cfg.maskTot.size[1] = ctx->cfg.maskTot.size[1];
        fd_loop_ub = ctx->cfg.maskTot.size[1];
        if (fd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[fd_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        md_loop_ub = ctx->cfg.maskCart.size[1];
        if (md_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[md_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        wd_loop_ub = ctx->cfg.maskRot.size[1];
        if (wd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[wd_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ee_loop_ub = ctx->cfg.indCart.size[0];
        for (int i83{0}; i83 < ee_loop_ub; i83++) {
            b_ctx.cfg.indCart[i83] = ctx->cfg.indCart.data[i83];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        je_loop_ub = ctx->cfg.indRot.size[0];
        for (int i88{0}; i88 < je_loop_ub; i88++) {
            b_ctx.cfg.indRot[i88] = ctx->cfg.indRot.data[i88];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.D.set_size(ctx->cfg.D.size[0]);
        re_loop_ub = ctx->cfg.D.size[0];
        for (int i96{0}; i96 < re_loop_ub; i96++) {
            b_ctx.cfg.D[i96] = ctx->cfg.D.data[i96];
        }
        b_ctx.cfg.coeffD = ctx->cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        af_loop_ub = ctx->cfg.kin_params.size[0];
        if (af_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[af_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i104{0}; i104 < 8; i104++) {
            b_ctx.cfg.kin_type[i104] = ctx->cfg.kin_type[i104];
        }
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.SplitSpecialSpline = ctx->cfg.SplitSpecialSpline;
        b_ctx.cfg.ReleaseMemoryOfTheQueues = ctx->cfg.ReleaseMemoryOfTheQueues;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        for (int i111{0}; i111 < 6; i111++) {
            b_ctx.cfg.vmax[i111] = ctx->cfg.vmax[i111];
            b_ctx.cfg.amax[i111] = ctx->cfg.amax[i111];
            b_ctx.cfg.jmax[i111] = ctx->cfg.jmax[i111];
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
        b_ctx.cfg.DefaultZeroStopCount = ctx->cfg.DefaultZeroStopCount;
        b_ctx.cfg.source.size[0] = 1;
        b_ctx.cfg.source.size[1] = ctx->cfg.source.size[1];
        hf_loop_ub = ctx->cfg.source.size[1];
        if (hf_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.source.data[0], &ctx->cfg.source.data[hf_loop_ub],
                      &b_ctx.cfg.source.data[0]);
        }
        b_ctx.cfg.Cusp = ctx->cfg.Cusp;
        b_ctx.cfg.Compressing = ctx->cfg.Compressing;
        b_ctx.cfg.Smoothing = ctx->cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int g_i{0}; g_i < 5; g_i++) {
            b_ctx.cfg.GaussLegendreX[g_i] = ctx->cfg.GaussLegendreX[g_i];
            b_ctx.cfg.GaussLegendreW[g_i] = ctx->cfg.GaussLegendreW[g_i];
        }
        b_ctx.cfg.opt = ctx->cfg.opt;
        for (int i118{0}; i118 < 9; i118++) {
            b_ctx.cfg.LogFileName[i118] = ctx->cfg.LogFileName[i118];
        }
        b_ctx.jmax_increase_count = ctx->jmax_increase_count;
        b_ctx.zero_start = ctx->zero_start;
        b_ctx.zero_end = ctx->zero_end;
        b_ctx.zero_forced = ctx->zero_forced;
        b_ctx.zero_forced_buffer[0] = ctx->zero_forced_buffer[0];
        b_ctx.zero_forced_buffer[1] = ctx->zero_forced_buffer[1];
        b_ctx.simplex_calls = ctx->simplex_calls;
        b_ctx.forced_stop = ctx->forced_stop;
        b_ctx.programmed_stop = ctx->programmed_stop;
        b_ctx.Coeff.set_size(ctx->Coeff.size(0), ctx->Coeff.size(1));
        qf_loop_ub = ctx->Coeff.size(1);
        for (int i127{0}; i127 < qf_loop_ub; i127++) {
            int uf_loop_ub;
            uf_loop_ub = ctx->Coeff.size(0);
            for (int i131{0}; i131 < uf_loop_ub; i131++) {
                b_ctx.Coeff[i131 + b_ctx.Coeff.size(0) * i127] =
                    ctx->Coeff[i131 + ctx->Coeff.size(0) * i127];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        b_ctx.errmsg = ctx->errmsg;
        b_ctx.errcode = ctx->errcode;
        feedratePlanning(&b_ctx, &c_optimized, opt_struct, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        cg_loop_ub = b_ctx.BasisVal.size(1);
        for (int i138{0}; i138 < cg_loop_ub; i138++) {
            int mg_loop_ub;
            mg_loop_ub = b_ctx.BasisVal.size(0);
            for (int i147{0}; i147 < mg_loop_ub; i147++) {
                ctx->BasisVal[i147 + ctx->BasisVal.size(0) * i138] =
                    b_ctx.BasisVal[i147 + b_ctx.BasisVal.size(0) * i138];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        ng_loop_ub = b_ctx.BasisValD.size(1);
        for (int i148{0}; i148 < ng_loop_ub; i148++) {
            int wg_loop_ub;
            wg_loop_ub = b_ctx.BasisValD.size(0);
            for (int i158{0}; i158 < wg_loop_ub; i158++) {
                ctx->BasisValD[i158 + ctx->BasisValD.size(0) * i148] =
                    b_ctx.BasisValD[i158 + b_ctx.BasisValD.size(0) * i148];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        yg_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i159{0}; i159 < yg_loop_ub; i159++) {
            int ih_loop_ub;
            ih_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i169{0}; i169 < ih_loop_ub; i169++) {
                ctx->BasisValDD[i169 + ctx->BasisValDD.size(0) * i159] =
                    b_ctx.BasisValDD[i169 + b_ctx.BasisValDD.size(0) * i159];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        jh_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i170{0}; i170 < jh_loop_ub; i170++) {
            int th_loop_ub;
            th_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i179{0}; i179 < th_loop_ub; i179++) {
                ctx->BasisValDDD[i179 + ctx->BasisValDDD.size(0) * i170] =
                    b_ctx.BasisValDDD[i179 + b_ctx.BasisValDDD.size(0) * i170];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        uh_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i180{0}; i180 < uh_loop_ub; i180++) {
            ctx->BasisIntegr[i180] = b_ctx.BasisIntegr[i180];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        ei_loop_ub = b_ctx.u_vec.size(1);
        for (int i189{0}; i189 < ei_loop_ub; i189++) {
            ctx->u_vec[i189] = b_ctx.u_vec[i189];
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
        ctx->cfg.ENABLE_PRINT_MSG = b_ctx.cfg.ENABLE_PRINT_MSG;
        ctx->cfg.maskTot.size[0] = 1;
        ctx->cfg.maskTot.size[1] = b_ctx.cfg.maskTot.size[1];
        dj_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (dj_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[dj_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        mj_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (mj_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[mj_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        vj_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (vj_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[vj_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        ek_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i227{0}; i227 < ek_loop_ub; i227++) {
            ctx->cfg.indCart.data[i227] = b_ctx.cfg.indCart[i227];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        lk_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i233{0}; i233 < lk_loop_ub; i233++) {
            ctx->cfg.indRot.data[i233] = b_ctx.cfg.indRot[i233];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        rk_loop_ub = b_ctx.cfg.D.size(0);
        for (int i238{0}; i238 < rk_loop_ub; i238++) {
            ctx->cfg.D.data[i238] = b_ctx.cfg.D[i238];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        xk_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (xk_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[xk_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i244{0}; i244 < 8; i244++) {
            ctx->cfg.kin_type[i244] = b_ctx.cfg.kin_type[i244];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.SplitSpecialSpline = b_ctx.cfg.SplitSpecialSpline;
        ctx->cfg.ReleaseMemoryOfTheQueues = b_ctx.cfg.ReleaseMemoryOfTheQueues;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        for (int i250{0}; i250 < 6; i250++) {
            ctx->cfg.vmax[i250] = b_ctx.cfg.vmax[i250];
            ctx->cfg.amax[i250] = b_ctx.cfg.amax[i250];
            ctx->cfg.jmax[i250] = b_ctx.cfg.jmax[i250];
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
        ctx->cfg.DefaultZeroStopCount = b_ctx.cfg.DefaultZeroStopCount;
        ctx->cfg.source.size[0] = 1;
        ctx->cfg.source.size[1] = b_ctx.cfg.source.size[1];
        sl_loop_ub = b_ctx.cfg.source.size[1];
        if (sl_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.source.data[0], &b_ctx.cfg.source.data[sl_loop_ub],
                      &ctx->cfg.source.data[0]);
        }
        ctx->cfg.Cusp = b_ctx.cfg.Cusp;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int m_i{0}; m_i < 5; m_i++) {
            ctx->cfg.GaussLegendreX[m_i] = b_ctx.cfg.GaussLegendreX[m_i];
            ctx->cfg.GaussLegendreW[m_i] = b_ctx.cfg.GaussLegendreW[m_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i265{0}; i265 < 9; i265++) {
            ctx->cfg.LogFileName[i265] = b_ctx.cfg.LogFileName[i265];
        }
        ctx->jmax_increase_count = b_ctx.jmax_increase_count;
        ctx->zero_start = b_ctx.zero_start;
        ctx->zero_end = b_ctx.zero_end;
        ctx->zero_forced = b_ctx.zero_forced;
        ctx->zero_forced_buffer[0] = b_ctx.zero_forced_buffer[0];
        ctx->zero_forced_buffer[1] = b_ctx.zero_forced_buffer[1];
        ctx->simplex_calls = b_ctx.simplex_calls;
        ctx->forced_stop = b_ctx.forced_stop;
        ctx->programmed_stop = b_ctx.programmed_stop;
        ctx->Coeff.set_size(b_ctx.Coeff.size(0), b_ctx.Coeff.size(1));
        cm_loop_ub = b_ctx.Coeff.size(1);
        for (int i273{0}; i273 < cm_loop_ub; i273++) {
            int hm_loop_ub;
            hm_loop_ub = b_ctx.Coeff.size(0);
            for (int i278{0}; i278 < hm_loop_ub; i278++) {
                ctx->Coeff[i278 + ctx->Coeff.size(0) * i273] =
                    b_ctx.Coeff[i278 + b_ctx.Coeff.size(0) * i273];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        ctx->errmsg = b_ctx.errmsg;
        ctx->errcode = b_ctx.errcode;
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
        //  DebugLog : Print msg in log pipe.
        //
        //  Inputs :
        //  cfg       : The configuration structure
        //  varargin  : Variable types of arguments (a.k.a print msg)
        //
        // 'DebugLog:9' if IsEnabledDebugLog( cfg )
        //  IsEnableDebugLog : Is the Debug log enable
        //
        //  Inputs :
        //    cfg : Configuration structure
        //
        //  Outputs :
        //  Value : Boolean Value. TRUE means the debug log is enable.
        //
        // 'IsEnabledDebugLog:13' value = false;
        // 'IsEnabledDebugLog:15' if bitget( DebugConfig, int32( cfg ) )
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            // 'IsEnabledDebugLog:16' value = true;
            //    Output
            //    stdout : 1
            //    stderr : 2
            // 'DebugLog:13' output  = 1;
            // 'DebugLog:14' fprintf( output, varargin{ : } );
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
