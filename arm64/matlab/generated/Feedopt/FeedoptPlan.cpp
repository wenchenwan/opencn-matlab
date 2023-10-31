
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
#include "add_tool_offset.h"
#include "checkGeometry.h"
#include "checkParametrisation.h"
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
#include <stdio.h>

// Function Definitions
//
// function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
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
    coder::rtString e_obj;
    coder::rtString obj;
    coder::rtString r1;
    Axes params_tmp_tool_offset;
    CurvStruct c_CurvStruct;
    CurvStruct curv1;
    CurvStruct last;
    CurvStruct r2;
    MsgStruct err_msg;
    SplineStruct params_tmp_spline;
    b_CurvStruct e_expl_temp;
    b_CurvStruct expl_temp_tmp;
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
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int loop_ub;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_tool_orientation;
    int params_tmp_tool_pocketno;
    int params_tmp_tool_toolno;
    char b_cv[1025];
    char st[12];
    char b_obj2Value_data[11];
    char obj2Value_data[11];
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
    // 'FeedoptPlan:4' optimized = false;
    b_optimized = false;
    // 'FeedoptPlan:6' opt_struct = constrCurvStructType;
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
        params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &expl_temp_tmp);
    e_expl_temp = expl_temp_tmp;
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
    // 'FeedoptPlan:9' ocn_assert( ctx.errcode == FeedoptPlanError.NoError, ...
    // 'FeedoptPlan:10'     "FeedoptPlan: error code was not handled...", mfilename );
    d_ocn_assert(ctx->errcode == FeedoptPlanError_NoError);
    // 'FeedoptPlan:12' switch ctx.op
    switch (ctx->op) {
    case Fopt_Init:
        // 'FeedoptPlan:13' case Fopt.Init
        // 'FeedoptPlan:14' ctx.op = Fopt.GCode;
        ctx->op = Fopt_GCode;
        //
        break;
    case Fopt_GCode: {
        int be_loop_ub;
        int cf_loop_ub;
        int me_loop_ub;
        int resCount;
        bool exitg1;
        bool zeroFlag;
        ReadGCodeError status;
        // 'FeedoptPlan:16' case Fopt.GCode
        // 'FeedoptPlan:17' ctx.k0      = int32(1);
        ctx->k0 = 1;
        // 'FeedoptPlan:18' status      = ReadGCode( ReadGCodeCmd.Load, ctx.cfg.source );
        //  coder.extrinsic('ReadGCode_mex');
        //  Wrapper for pulling the next gcode line from the interpreter
        // 'ReadGCode:6' status          = ReadGCodeError.InterpError;
        // 'ReadGCode:7' CurvStruct      = constrCurvStructType;
        // 'ReadGCode:8' err_msg         = constrMsgStructType;
        std::copy(&cv[0], &cv[2048], &err_msg.msg[0]);
        err_msg.size = 2048.0;
        // 'ReadGCode:10' if coder.target('matlab')
        // 'ReadGCode:43' else
        // 'ReadGCode:44' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
        // 'ReadGCode:46' my_path = StructTypeName.WDIR + "/src";
        // 'ReadGCode:47' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'ReadGCode:49' pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
        //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
        // 'ReadGCode:51' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
        // 'ReadGCode:52' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path);
        // 'ReadGCode:53' coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
        // 'ReadGCode:54' coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc',
        // pathRs274Src); 'ReadGCode:55' coder.updateBuildInfo('addSourceFiles','interp_arc.cc',
        // pathRs274Src); 'ReadGCode:56' coder.updateBuildInfo('addSourceFiles','interp_array.cc',
        // pathRs274Src); 'ReadGCode:57' coder.updateBuildInfo('addSourceFiles','interp_base.cc',
        // pathRs274Src); 'ReadGCode:58' coder.updateBuildInfo('addSourceFiles','interp_check.cc',
        // pathRs274Src); 'ReadGCode:59' coder.updateBuildInfo('addSourceFiles','interp_convert.cc',
        // pathRs274Src); 'ReadGCode:60' coder.updateBuildInfo('addSourceFiles','interp_cycles.cc',
        // pathRs274Src); 'ReadGCode:61' coder.updateBuildInfo('addSourceFiles','interp_execute.cc',
        // pathRs274Src); 'ReadGCode:62' coder.updateBuildInfo('addSourceFiles','interp_find.cc',
        // pathRs274Src); 'ReadGCode:63'
        // coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
        // 'ReadGCode:64' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
        // 'ReadGCode:65' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
        // pathRs274Src); 'ReadGCode:66' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
        // pathRs274Src); 'ReadGCode:67' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
        // pathRs274Src); 'ReadGCode:68' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
        // pathRs274Src); 'ReadGCode:69' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
        // pathRs274Src); 'ReadGCode:70' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
        // pathRs274Src); 'ReadGCode:71' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
        // pathRs274Src); 'ReadGCode:72' coder.updateBuildInfo('addSourceFiles','ocn.cc',
        // pathRs274Src); 'ReadGCode:73' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc',
        // pathRs274Src); 'ReadGCode:74' coder.updateBuildInfo('addSourceFiles','inifile.cc',
        // pathRs274Src); 'ReadGCode:75' coder.updateBuildInfo('addLinkFlags', '-ldl');
        //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
        // 'ReadGCode:77' coder.cinclude('cpp_interp.hpp');
        // 'ReadGCode:79' switch cmd
        // 'ReadGCode:80' case ReadGCodeCmd.Load
        // 'ReadGCode:81' status = coder.ceval( 'cpp_interp_init', [filename 0], coder.ref(err_msg)
        // );
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_cv[0]);
        b_cv[1024] = '\x00';
        status = cpp_interp_init(&b_cv[0], &err_msg);
        // 'ReadGCode:93' if(0)
        // 'ReadGCode:98' ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
        // 'ReadGCode:99'     "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
        // 'ReadGCode:100'     err_msg.msg, mfilename );
        resCount = sprintf(&st[0], "%d", 0);
        if (resCount - 1 >= 0) {
            std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
        }
        obj.Value.size[0] = 1;
        obj.Value.size[1] = resCount + 2056;
        for (int i64{0}; i64 < 6; i64++) {
            obj.Value.data[i64] = obj1Value[i64];
        }
        if (resCount - 1 >= 0) {
            std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[6]);
        }
        obj.Value.data[resCount + 6] = ']';
        obj.Value.data[resCount + 7] = ' ';
        std::copy(&err_msg.msg[0], &err_msg.msg[2048], &obj.Value.data[resCount + 8]);
        c_ocn_assert(status < ReadGCodeError_InterpNotOpen, &obj);
        // 'FeedoptPlan:19' CurvStruct  = opt_struct;
        c_CurvStruct = *opt_struct;
        // 'FeedoptPlan:20' CurvStruct.Info.Type = CurveType.None;
        c_CurvStruct.Info.Type = CurveType_None;
        // 'FeedoptPlan:21' DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );
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
        // 'FeedoptPlan:23' while status < ReadGCodeError.InterpNotOpen
        exitg1 = false;
        while ((!exitg1) && (status < ReadGCodeError_InterpNotOpen)) {
            // 'FeedoptPlan:24' if( CurvStruct.Info.Type ~= CurveType.None )
            if (c_CurvStruct.Info.Type != CurveType_None) {
                // 'FeedoptPlan:25' ctx.q_gcode.push( CurvStruct );
                ctx->q_gcode.push(&c_CurvStruct);
                // 'FeedoptPlan:26' ctx.k0 = ctx.k0 + 1;
                ctx->k0++;
            }
            // 'FeedoptPlan:29' if( status == ReadGCodeError.InterpExit )
            if (status == ReadGCodeError_InterpExit) {
                exitg1 = true;
            } else {
                int ae_loop_ub;
                int b_resCount;
                int ee_loop_ub;
                int ke_loop_ub;
                int kf_loop_ub;
                int kg_loop_ub;
                int vd_loop_ub;
                int wd_loop_ub;
                int xd_loop_ub;
                bool is_loaded;
                ReadGCodeError b_status;
                // 'FeedoptPlan:33' [ status, CurvStruct ] = ReadGCode( ReadGCodeCmd.Read, ...
                // 'FeedoptPlan:34'                 ctx.cfg.source );
                //  coder.extrinsic('ReadGCode_mex');
                //  Wrapper for pulling the next gcode line from the interpreter
                // 'ReadGCode:6' status          = ReadGCodeError.InterpError;
                // 'ReadGCode:7' CurvStruct      = constrCurvStructType;
                //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                // 'constrCurvStructType:4' if( nargin > 0 )
                // 'constrCurvStructType:6' else
                // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                // 'constrCurvStructType:12' else
                // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                // params.tool, ... 'constrCurvStructType:14'         params.spline, params.R0,
                // params.R1, params.Cprim, ... 'constrCurvStructType:15'         params.delta,
                // params.evec, params.theta, params.pitch, ... 'constrCurvStructType:16'
                // params.CoeffP5, params.Coeff );
                e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                vd_loop_ub = expl_temp_tmp.R0.size[0];
                if (vd_loop_ub - 1 >= 0) {
                    std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[vd_loop_ub],
                              &e_expl_temp.R0.data[0]);
                }
                e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                wd_loop_ub = expl_temp_tmp.R1.size[0];
                if (wd_loop_ub - 1 >= 0) {
                    std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[wd_loop_ub],
                              &e_expl_temp.R1.data[0]);
                }
                e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                             expl_temp_tmp.CoeffP5.size(1));
                xd_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                for (int i91{0}; i91 < xd_loop_ub; i91++) {
                    int yd_loop_ub;
                    yd_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                    for (int i94{0}; i94 < yd_loop_ub; i94++) {
                        e_expl_temp.CoeffP5[i94 + e_expl_temp.CoeffP5.size(0) * i91] =
                            expl_temp_tmp.CoeffP5[i94 + expl_temp_tmp.CoeffP5.size(0) * i91];
                    }
                }
                e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                ae_loop_ub = expl_temp_tmp.Coeff.size(0);
                for (int i95{0}; i95 < ae_loop_ub; i95++) {
                    e_expl_temp.Coeff[i95] = expl_temp_tmp.Coeff[i95];
                }
                c_CurvStruct.Info = expl_temp_tmp.Info;
                c_CurvStruct.tool = expl_temp_tmp.tool;
                c_CurvStruct.sp = expl_temp_tmp.sp;
                c_CurvStruct.R0.set_size(e_expl_temp.R0.size[0]);
                ee_loop_ub = e_expl_temp.R0.size[0];
                for (int i99{0}; i99 < ee_loop_ub; i99++) {
                    c_CurvStruct.R0[i99] = e_expl_temp.R0.data[i99];
                }
                c_CurvStruct.R1.set_size(e_expl_temp.R1.size[0]);
                ke_loop_ub = e_expl_temp.R1.size[0];
                for (int i105{0}; i105 < ke_loop_ub; i105++) {
                    c_CurvStruct.R1[i105] = e_expl_temp.R1.data[i105];
                }
                c_CurvStruct.delta = expl_temp_tmp.delta;
                c_CurvStruct.CorrectedHelixCenter[0] = expl_temp_tmp.CorrectedHelixCenter[0];
                c_CurvStruct.evec[0] = expl_temp_tmp.evec[0];
                c_CurvStruct.CorrectedHelixCenter[1] = expl_temp_tmp.CorrectedHelixCenter[1];
                c_CurvStruct.evec[1] = expl_temp_tmp.evec[1];
                c_CurvStruct.CorrectedHelixCenter[2] = expl_temp_tmp.CorrectedHelixCenter[2];
                c_CurvStruct.evec[2] = expl_temp_tmp.evec[2];
                c_CurvStruct.theta = expl_temp_tmp.theta;
                c_CurvStruct.pitch = expl_temp_tmp.pitch;
                c_CurvStruct.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0),
                                              e_expl_temp.CoeffP5.size(1));
                kf_loop_ub = e_expl_temp.CoeffP5.size(1);
                for (int i130{0}; i130 < kf_loop_ub; i130++) {
                    int sf_loop_ub;
                    sf_loop_ub = e_expl_temp.CoeffP5.size(0);
                    for (int i138{0}; i138 < sf_loop_ub; i138++) {
                        c_CurvStruct.CoeffP5[i138 + c_CurvStruct.CoeffP5.size(0) * i130] =
                            e_expl_temp.CoeffP5[i138 + e_expl_temp.CoeffP5.size(0) * i130];
                    }
                }
                c_CurvStruct.sp_index = expl_temp_tmp.sp_index;
                c_CurvStruct.i_begin_sp = expl_temp_tmp.i_begin_sp;
                c_CurvStruct.i_end_sp = expl_temp_tmp.i_end_sp;
                c_CurvStruct.index_smooth = expl_temp_tmp.index_smooth;
                c_CurvStruct.UseConstJerk = expl_temp_tmp.UseConstJerk;
                c_CurvStruct.ConstJerk = expl_temp_tmp.ConstJerk;
                c_CurvStruct.Coeff.set_size(e_expl_temp.Coeff.size(0));
                kg_loop_ub = e_expl_temp.Coeff.size(0);
                for (int i155{0}; i155 < kg_loop_ub; i155++) {
                    c_CurvStruct.Coeff[i155] = e_expl_temp.Coeff[i155];
                }
                c_CurvStruct.a_param = expl_temp_tmp.a_param;
                c_CurvStruct.b_param = expl_temp_tmp.b_param;
                // 'ReadGCode:8' err_msg         = constrMsgStructType;
                std::copy(&cv[0], &cv[2048], &err_msg.msg[0]);
                err_msg.size = 2048.0;
                // 'ReadGCode:10' if coder.target('matlab')
                // 'ReadGCode:43' else
                // 'ReadGCode:44' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
                // 'ReadGCode:46' my_path = StructTypeName.WDIR + "/src";
                // 'ReadGCode:47' coder.updateBuildInfo('addIncludePaths',my_path);
                // 'ReadGCode:49' pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
                //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
                // 'ReadGCode:51' coder.updateBuildInfo('addCompileFlags',
                // '-fdiagnostics-color=always') 'ReadGCode:52'
                // coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path); 'ReadGCode:53'
                // coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
                // 'ReadGCode:54' coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc',
                // pathRs274Src); 'ReadGCode:55'
                // coder.updateBuildInfo('addSourceFiles','interp_arc.cc', pathRs274Src);
                // 'ReadGCode:56' coder.updateBuildInfo('addSourceFiles','interp_array.cc',
                // pathRs274Src); 'ReadGCode:57'
                // coder.updateBuildInfo('addSourceFiles','interp_base.cc', pathRs274Src);
                // 'ReadGCode:58' coder.updateBuildInfo('addSourceFiles','interp_check.cc',
                // pathRs274Src); 'ReadGCode:59'
                // coder.updateBuildInfo('addSourceFiles','interp_convert.cc', pathRs274Src);
                // 'ReadGCode:60' coder.updateBuildInfo('addSourceFiles','interp_cycles.cc',
                // pathRs274Src); 'ReadGCode:61'
                // coder.updateBuildInfo('addSourceFiles','interp_execute.cc', pathRs274Src);
                // 'ReadGCode:62' coder.updateBuildInfo('addSourceFiles','interp_find.cc',
                // pathRs274Src); 'ReadGCode:63'
                // coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
                // 'ReadGCode:64' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc',
                // pathRs274Src); 'ReadGCode:65'
                // coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc', pathRs274Src);
                // 'ReadGCode:66' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
                // pathRs274Src); 'ReadGCode:67'
                // coder.updateBuildInfo('addSourceFiles','interp_queue.cc', pathRs274Src);
                // 'ReadGCode:68' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
                // pathRs274Src); 'ReadGCode:69'
                // coder.updateBuildInfo('addSourceFiles','interp_remap.cc', pathRs274Src);
                // 'ReadGCode:70' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
                // pathRs274Src); 'ReadGCode:71'
                // coder.updateBuildInfo('addSourceFiles','interp_write.cc', pathRs274Src);
                // 'ReadGCode:72' coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
                // 'ReadGCode:73' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc',
                // pathRs274Src); 'ReadGCode:74'
                // coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
                // 'ReadGCode:75' coder.updateBuildInfo('addLinkFlags', '-ldl');
                //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
                // 'ReadGCode:77' coder.cinclude('cpp_interp.hpp');
                // 'ReadGCode:79' switch cmd
                // 'ReadGCode:82' case ReadGCodeCmd.Read
                // 'ReadGCode:83' is_loaded = false;
                // 'ReadGCode:84' is_loaded = coder.ceval( 'cpp_interp_loaded', coder.ref(err_msg)
                // );
                is_loaded = cpp_interp_loaded(&err_msg);
                // 'ReadGCode:85' if is_loaded
                if (is_loaded) {
                    // 'ReadGCode:86' status  = coder.ceval( 'cpp_interp_read', coder.ref(
                    // CurvStruct ), coder.ref(err_msg) );
                    b_status = cpp_interp_read(&c_CurvStruct, &err_msg);
                } else {
                    // 'ReadGCode:87' else
                    // 'ReadGCode:88' status  = ReadGCodeError.InterpError;
                    b_status = ReadGCodeError_InterpError;
                }
                // 'ReadGCode:93' if(0)
                // 'ReadGCode:98' ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
                // 'ReadGCode:99'     "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
                // 'ReadGCode:100'     err_msg.msg, mfilename );
                b_resCount = sprintf(&st[0], "%d", c_CurvStruct.Info.gcode_source_line);
                if (b_resCount - 1 >= 0) {
                    std::copy(&st[0], &st[b_resCount], &b_obj2Value_data[0]);
                }
                b_obj.Value.size[0] = 1;
                b_obj.Value.size[1] = b_resCount + 2056;
                for (int i184{0}; i184 < 6; i184++) {
                    b_obj.Value.data[i184] = obj1Value[i184];
                }
                if (b_resCount - 1 >= 0) {
                    std::copy(&b_obj2Value_data[0], &b_obj2Value_data[b_resCount],
                              &b_obj.Value.data[6]);
                }
                b_obj.Value.data[b_resCount + 6] = ']';
                b_obj.Value.data[b_resCount + 7] = ' ';
                std::copy(&err_msg.msg[0], &err_msg.msg[2048], &b_obj.Value.data[b_resCount + 8]);
                c_ocn_assert(b_status < ReadGCodeError_InterpNotOpen, &b_obj);
                status = b_status;
                // 'FeedoptPlan:36' if( CurvStruct.Info.Type ~= CurveType.None )
                if (c_CurvStruct.Info.Type != CurveType_None) {
                    double prev_tool_offset_x;
                    double prev_tool_offset_y;
                    double prev_tool_offset_z;
                    // 'FeedoptPlan:37' if( ctx.q_gcode.isempty )
                    if (ctx->q_gcode.isempty()) {
                        // 'FeedoptPlan:38' prev_tool = constrToolStructType;
                        prev_tool_offset_x = 0.0;
                        prev_tool_offset_y = 0.0;
                        prev_tool_offset_z = 0.0;
                    } else {
                        // 'FeedoptPlan:39' else
                        // 'FeedoptPlan:40' prev_tool = ctx.q_gcode.rget(1).tool;
                        ctx->q_gcode.rget(&r2);
                        prev_tool_offset_x = r2.tool.offset.x;
                        prev_tool_offset_y = r2.tool.offset.y;
                        prev_tool_offset_z = r2.tool.offset.z;
                        // 'FeedoptPlan:42' if( ~toolIsEqual(prev_tool, CurvStruct.tool ) )
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
                            // 'FeedoptPlan:43' curv1 = ctx.q_gcode.rget(1);
                            ctx->q_gcode.rget(&curv1);
                            // 'FeedoptPlan:44' if( isAZeroStart(curv1) )
                            //  isAZeroStart : Return true if the curv starts with zero speed
                            //  Input :
                            //  curv / Info / ZSpdMode : A structure containning the information of
                            //  the curv zero speed.
                            // 'isAZeroStart:6' zeroFlag = false;
                            b_zeroFlag = false;
                            // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                            //  Get the zspdmode enum from either a curvStruct, infoStruct or
                            //  zspdMode.
                            // 'getZspdmode:3' error = false;
                            // 'getZspdmode:5' if( isenum( speed ) )
                            // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                            // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                            // 'isAZeroStart:10' if( error )
                            // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                            // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                            if ((curv1.Info.zspdmode == ZSpdMode_ZN) ||
                                (curv1.Info.zspdmode == ZSpdMode_ZZ)) {
                                // 'isAZeroStart:14' zeroFlag = true;
                                b_zeroFlag = true;
                            }
                            if (b_zeroFlag) {
                                // 'FeedoptPlan:45' curv1.Info.zspdmode = ZSpdMode.ZZ;
                                curv1.Info.zspdmode = ZSpdMode_ZZ;
                            } else {
                                // 'FeedoptPlan:46' else
                                // 'FeedoptPlan:47' curv1.Info.zspdmode = ZSpdMode.NZ;
                                curv1.Info.zspdmode = ZSpdMode_NZ;
                            }
                            // 'FeedoptPlan:50' ctx.q_gcode.set(ctx.q_gcode.size, curv1);
                            ctx->q_gcode.set(ctx->q_gcode.size(), &curv1);
                            // 'FeedoptPlan:52' if( isAZeroEnd(CurvStruct) )
                            //  isAZeroEnd : Return true if the curv ends with zero speed
                            //  Input :
                            //  curv / Info / ZSpdMode : A structure containning the information of
                            //  the curv zero speed.
                            // 'isAZeroEnd:6' zeroFlag = false;
                            c_zeroFlag = false;
                            // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                            //  Get the zspdmode enum from either a curvStruct, infoStruct or
                            //  zspdMode.
                            // 'getZspdmode:3' error = false;
                            // 'getZspdmode:5' if( isenum( speed ) )
                            // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                            // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                            // 'isAZeroEnd:10' if( error )
                            // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                            // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                            if ((c_CurvStruct.Info.zspdmode == ZSpdMode_NZ) ||
                                (c_CurvStruct.Info.zspdmode == ZSpdMode_ZZ)) {
                                // 'isAZeroEnd:14' zeroFlag = true;
                                c_zeroFlag = true;
                            }
                            if (c_zeroFlag) {
                                // 'FeedoptPlan:53' CurvStruct.Info.zspdmode = ZSpdMode.ZZ;
                                c_CurvStruct.Info.zspdmode = ZSpdMode_ZZ;
                            } else {
                                // 'FeedoptPlan:54' else
                                // 'FeedoptPlan:55' CurvStruct.Info.zspdmode = ZSpdMode.ZN;
                                c_CurvStruct.Info.zspdmode = ZSpdMode_ZN;
                            }
                        }
                    }
                    // 'FeedoptPlan:60' [CurvStruct] = add_tool_offset( CurvStruct, ctx.cfg.indCart,
                    // prev_tool );
                    //  Add the tool offset to the curve structure.
                    // 'add_tool_offset:4' if( ~CurvStruct.Info.TRAFO )
                    if (!c_CurvStruct.Info.TRAFO) {
                        double CurvStruct_data[3];
                        double off[3];
                        int CurvStruct_size;
                        // 'add_tool_offset:5' prev_off = [prev_tool.offset.x,prev_tool.offset.y,
                        // prev_tool.offset.z]; 'add_tool_offset:6' off = [CurvStruct.tool.offset.x,
                        // ... 'add_tool_offset:7'            CurvStruct.tool.offset.y, ...
                        // 'add_tool_offset:8'            CurvStruct.tool.offset.z];
                        off[0] = c_CurvStruct.tool.offset.x;
                        off[1] = c_CurvStruct.tool.offset.y;
                        off[2] = c_CurvStruct.tool.offset.z;
                        // 'add_tool_offset:9' CurvStruct.R0( indCart ) = ...
                        // 'add_tool_offset:10'         CurvStruct.R0( indCart ) + prev_off( : );
                        if (ctx->cfg.indCart.size[0] == 3) {
                            double b_prev_tool_offset_x[3];
                            int ei_loop_ub;
                            b_prev_tool_offset_x[0] = prev_tool_offset_x;
                            b_prev_tool_offset_x[1] = prev_tool_offset_y;
                            b_prev_tool_offset_x[2] = prev_tool_offset_z;
                            CurvStruct_size = ctx->cfg.indCart.size[0];
                            ei_loop_ub = ctx->cfg.indCart.size[0];
                            for (int i195{0}; i195 < ei_loop_ub; i195++) {
                                CurvStruct_data[i195] =
                                    c_CurvStruct.R0[ctx->cfg.indCart.data[i195] - 1] +
                                    b_prev_tool_offset_x[i195];
                            }
                            for (int i197{0}; i197 < CurvStruct_size; i197++) {
                                c_CurvStruct.R0[ctx->cfg.indCart.data[i197] - 1] =
                                    CurvStruct_data[i197];
                            }
                        } else {
                            binary_expand_op(&c_CurvStruct, ctx, prev_tool_offset_x,
                                             prev_tool_offset_y, prev_tool_offset_z);
                        }
                        // 'add_tool_offset:11' CurvStruct.R1( indCart ) = ...
                        // 'add_tool_offset:12'         CurvStruct.R1( indCart ) + off( : );
                        if (ctx->cfg.indCart.size[0] == 3) {
                            int fi_loop_ub;
                            CurvStruct_size = ctx->cfg.indCart.size[0];
                            fi_loop_ub = ctx->cfg.indCart.size[0];
                            for (int i196{0}; i196 < fi_loop_ub; i196++) {
                                CurvStruct_data[i196] =
                                    c_CurvStruct.R1[ctx->cfg.indCart.data[i196] - 1] + off[i196];
                            }
                            for (int i198{0}; i198 < CurvStruct_size; i198++) {
                                c_CurvStruct.R1[ctx->cfg.indCart.data[i198] - 1] =
                                    CurvStruct_data[i198];
                            }
                        } else {
                            binary_expand_op(&c_CurvStruct, ctx, off);
                        }
                        // 'add_tool_offset:13' if ( CurvStruct.Info.Type == CurveType.Helix )
                        if (c_CurvStruct.Info.Type == CurveType_Helix) {
                            // 'add_tool_offset:14' CurvStruct.CorrectedHelixCenter =
                            // CurvStruct.CorrectedHelixCenter + off( : );
                            c_CurvStruct.CorrectedHelixCenter[0] += c_CurvStruct.tool.offset.x;
                            c_CurvStruct.CorrectedHelixCenter[1] += c_CurvStruct.tool.offset.y;
                            c_CurvStruct.CorrectedHelixCenter[2] += c_CurvStruct.tool.offset.z;
                        }
                    }
                    // 'FeedoptPlan:62' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end )
                    // );
                    c_CurvStruct.R0[3] = 0.017453292519943295 * c_CurvStruct.R0[3];
                    c_CurvStruct.R0[4] = 0.017453292519943295 * c_CurvStruct.R0[4];
                    c_CurvStruct.R0[5] = 0.017453292519943295 * c_CurvStruct.R0[5];
                    // 'FeedoptPlan:63' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end )
                    // );
                    c_CurvStruct.R1[3] = 0.017453292519943295 * c_CurvStruct.R1[3];
                    c_CurvStruct.R1[4] = 0.017453292519943295 * c_CurvStruct.R1[4];
                    c_CurvStruct.R1[5] = 0.017453292519943295 * c_CurvStruct.R1[5];
                    // 'FeedoptPlan:65' for j = 1 : StructTypeName.NumberAxisMax
                    // 'FeedoptPlan:74' if( CurvStruct.Info.FeedRate == 0.0 )
                    if (c_CurvStruct.Info.FeedRate == 0.0) {
                        // 'FeedoptPlan:75' CurvStruct.Info.FeedRate = ctx.cfg.fmax;
                        c_CurvStruct.Info.FeedRate = ctx->cfg.fmax;
                    }
                }
            }
        }
        //  Error if gcode queue is empty
        // 'FeedoptPlan:80' ocn_assert( ~ctx.q_gcode.isempty(), "Gcode queue is empty", mfilename );
        e_ocn_assert(!ctx->q_gcode.isempty());
        // 'FeedoptPlan:82' last = ctx.q_gcode.rget(1);
        ctx->q_gcode.rget(&last);
        // 'FeedoptPlan:83' if( isAZeroStart(last) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  Input :
        //  curv / Info / ZSpdMode : A structure containning the information of the
        //  curv zero speed.
        // 'isAZeroStart:6' zeroFlag = false;
        zeroFlag = false;
        // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
        //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
        // 'getZspdmode:3' error = false;
        // 'getZspdmode:5' if( isenum( speed ) )
        // 'getZspdmode:7' elseif( isfield( speed, "Info") )
        // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
        // 'isAZeroStart:10' if( error )
        // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
        if ((last.Info.zspdmode == ZSpdMode_ZN) || (last.Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:14' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'FeedoptPlan:84' last.Info.zspdmode = ZSpdMode.ZZ;
            last.Info.zspdmode = ZSpdMode_ZZ;
        } else {
            // 'FeedoptPlan:85' else
            // 'FeedoptPlan:86' last.Info.zspdmode = ZSpdMode.NZ;
            last.Info.zspdmode = ZSpdMode_NZ;
        }
        // 'FeedoptPlan:88' ctx.q_gcode.set( ctx.q_gcode.size, last );
        ctx->q_gcode.set(ctx->q_gcode.size(), &last);
        // 'FeedoptPlan:90' assert_queue( ctx.op, ctx.q_gcode );
        // 'FeedoptPlan:161' msg = string( op );
        // 'FeedoptPlan:162' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:163'     msg + " - Check geometry failed...", mfilename );
        r1.init(ctx->op);
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r1.Value.size[1] + 27;
        be_loop_ub = r1.Value.size[1];
        if (be_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[be_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i96{0}; i96 < 27; i96++) {
            c_obj.Value.data[i96 + r1.Value.size[1]] = obj2Value[i96];
        }
        f_ocn_assert(checkGeometry(&ctx->q_gcode), &c_obj);
        // 'FeedoptPlan:164' ocn_assert( checkZSpdmode( queue ), ...
        // 'FeedoptPlan:165'     msg + " - Check zspdmode failed...", mfilename );
        d_obj.Value.size[0] = 1;
        d_obj.Value.size[1] = r1.Value.size[1] + 27;
        me_loop_ub = r1.Value.size[1];
        if (me_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[me_loop_ub], &d_obj.Value.data[0]);
        }
        for (int i109{0}; i109 < 27; i109++) {
            d_obj.Value.data[i109 + r1.Value.size[1]] = b_obj2Value[i109];
        }
        f_ocn_assert(checkZSpdmode(&ctx->q_gcode), &d_obj);
        // 'FeedoptPlan:166' ocn_assert( checkParametrisation( queue ), ...
        // 'FeedoptPlan:167'     msg + " - Check parametrisation failed...", mfilename );
        e_obj.Value.size[0] = 1;
        e_obj.Value.size[1] = r1.Value.size[1] + 34;
        cf_loop_ub = r1.Value.size[1];
        if (cf_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[cf_loop_ub], &e_obj.Value.data[0]);
        }
        for (int i129{0}; i129 < 34; i129++) {
            e_obj.Value.data[i129 + r1.Value.size[1]] = c_obj2Value[i129];
        }
        f_ocn_assert(checkParametrisation(&ctx->q_gcode), &e_obj);
        // 'FeedoptPlan:92' ctx.op = Fopt.Check;
        ctx->op = Fopt_Check;
    } break;
    case Fopt_Check: {
        int jc_loop_ub;
        int v_loop_ub;
        int wb_loop_ub;
        // 'FeedoptPlan:94' case Fopt.Check
        // 'FeedoptPlan:95' if ~ctx.cfg.Cusp.Skip
        if (!ctx->cfg.Cusp.Skip) {
            int af_loop_ub;
            int bb_loop_ub;
            int bh_loop_ub;
            int bi_loop_ub;
            int dd_loop_ub;
            int fc_loop_ub;
            int fe_loop_ub;
            int gh_loop_ub;
            int h_loop_ub;
            int id_loop_ub;
            int ig_loop_ub;
            int ii_loop_ub;
            int lh_loop_ub;
            int mb_loop_ub;
            int mf_loop_ub;
            int nc_loop_ub;
            int nd_loop_ub;
            int p_loop_ub;
            int qg_loop_ub;
            int qh_loop_ub;
            int re_loop_ub;
            int sc_loop_ub;
            int sd_loop_ub;
            int vg_loop_ub;
            int vh_loop_ub;
            int xb_loop_ub;
            int xc_loop_ub;
            int xf_loop_ub;
            // 'FeedoptPlan:96' ctx     = CheckCurvStructs( ctx );
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            h_loop_ub = ctx->BasisVal.size(1);
            for (int i8{0}; i8 < h_loop_ub; i8++) {
                int o_loop_ub;
                o_loop_ub = ctx->BasisVal.size(0);
                for (int i15{0}; i15 < o_loop_ub; i15++) {
                    r.BasisVal[i15 + r.BasisVal.size(0) * i8] =
                        ctx->BasisVal[i15 + ctx->BasisVal.size(0) * i8];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            p_loop_ub = ctx->BasisValD.size(1);
            for (int i16{0}; i16 < p_loop_ub; i16++) {
                int ab_loop_ub;
                ab_loop_ub = ctx->BasisValD.size(0);
                for (int i25{0}; i25 < ab_loop_ub; i25++) {
                    r.BasisValD[i25 + r.BasisValD.size(0) * i16] =
                        ctx->BasisValD[i25 + ctx->BasisValD.size(0) * i16];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            bb_loop_ub = ctx->BasisValDD.size(1);
            for (int i27{0}; i27 < bb_loop_ub; i27++) {
                int kb_loop_ub;
                kb_loop_ub = ctx->BasisValDD.size(0);
                for (int i36{0}; i36 < kb_loop_ub; i36++) {
                    r.BasisValDD[i36 + r.BasisValDD.size(0) * i27] =
                        ctx->BasisValDD[i36 + ctx->BasisValDD.size(0) * i27];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            mb_loop_ub = ctx->BasisValDDD.size(1);
            for (int i37{0}; i37 < mb_loop_ub; i37++) {
                int vb_loop_ub;
                vb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i47{0}; i47 < vb_loop_ub; i47++) {
                    r.BasisValDDD[i47 + r.BasisValDDD.size(0) * i37] =
                        ctx->BasisValDDD[i47 + ctx->BasisValDDD.size(0) * i37];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            xb_loop_ub = ctx->BasisIntegr.size(0);
            for (int i48{0}; i48 < xb_loop_ub; i48++) {
                r.BasisIntegr[i48] = ctx->BasisIntegr[i48];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            fc_loop_ub = ctx->u_vec.size(1);
            for (int i56{0}; i56 < fc_loop_ub; i56++) {
                r.u_vec[i56] = ctx->u_vec[i56];
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
            nc_loop_ub = ctx->cfg.maskTot.size[1];
            if (nc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[nc_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            sc_loop_ub = ctx->cfg.maskCart.size[1];
            if (sc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[sc_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            xc_loop_ub = ctx->cfg.maskRot.size[1];
            if (xc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[xc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            dd_loop_ub = ctx->cfg.indCart.size[0];
            for (int i65{0}; i65 < dd_loop_ub; i65++) {
                r.cfg.indCart[i65] = ctx->cfg.indCart.data[i65];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            id_loop_ub = ctx->cfg.indRot.size[0];
            for (int i70{0}; i70 < id_loop_ub; i70++) {
                r.cfg.indRot[i70] = ctx->cfg.indRot.data[i70];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            nd_loop_ub = ctx->cfg.D.size[0];
            for (int i75{0}; i75 < nd_loop_ub; i75++) {
                r.cfg.D[i75] = ctx->cfg.D.data[i75];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            sd_loop_ub = ctx->cfg.kin_params.size[0];
            if (sd_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[sd_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i80{0}; i80 < 8; i80++) {
                r.cfg.kin_type[i80] = ctx->cfg.kin_type[i80];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i85{0}; i85 < 6; i85++) {
                r.cfg.vmax[i85] = ctx->cfg.vmax[i85];
                r.cfg.amax[i85] = ctx->cfg.amax[i85];
                r.cfg.jmax[i85] = ctx->cfg.jmax[i85];
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
            for (int i90{0}; i90 < 9; i90++) {
                r.cfg.LogFileName[i90] = ctx->cfg.LogFileName[i90];
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
            fe_loop_ub = ctx->Coeff.size(1);
            for (int i100{0}; i100 < fe_loop_ub; i100++) {
                int le_loop_ub;
                le_loop_ub = ctx->Coeff.size(0);
                for (int i106{0}; i106 < le_loop_ub; i106++) {
                    r.Coeff[i106 + r.Coeff.size(0) * i100] =
                        ctx->Coeff[i106 + ctx->Coeff.size(0) * i100];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            r.errmsg = ctx->errmsg;
            r.errcode = ctx->errcode;
            CheckCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            re_loop_ub = r.BasisVal.size(1);
            for (int i112{0}; i112 < re_loop_ub; i112++) {
                int ye_loop_ub;
                ye_loop_ub = r.BasisVal.size(0);
                for (int i119{0}; i119 < ye_loop_ub; i119++) {
                    ctx->BasisVal[i119 + ctx->BasisVal.size(0) * i112] =
                        r.BasisVal[i119 + r.BasisVal.size(0) * i112];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            af_loop_ub = r.BasisValD.size(1);
            for (int i120{0}; i120 < af_loop_ub; i120++) {
                int lf_loop_ub;
                lf_loop_ub = r.BasisValD.size(0);
                for (int i131{0}; i131 < lf_loop_ub; i131++) {
                    ctx->BasisValD[i131 + ctx->BasisValD.size(0) * i120] =
                        r.BasisValD[i131 + r.BasisValD.size(0) * i120];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            mf_loop_ub = r.BasisValDD.size(1);
            for (int i132{0}; i132 < mf_loop_ub; i132++) {
                int wf_loop_ub;
                wf_loop_ub = r.BasisValDD.size(0);
                for (int i142{0}; i142 < wf_loop_ub; i142++) {
                    ctx->BasisValDD[i142 + ctx->BasisValDD.size(0) * i132] =
                        r.BasisValDD[i142 + r.BasisValDD.size(0) * i132];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            xf_loop_ub = r.BasisValDDD.size(1);
            for (int i143{0}; i143 < xf_loop_ub; i143++) {
                int hg_loop_ub;
                hg_loop_ub = r.BasisValDDD.size(0);
                for (int i152{0}; i152 < hg_loop_ub; i152++) {
                    ctx->BasisValDDD[i152 + ctx->BasisValDDD.size(0) * i143] =
                        r.BasisValDDD[i152 + r.BasisValDDD.size(0) * i143];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            ig_loop_ub = r.BasisIntegr.size(0);
            for (int i153{0}; i153 < ig_loop_ub; i153++) {
                ctx->BasisIntegr[i153] = r.BasisIntegr[i153];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            qg_loop_ub = r.u_vec.size(1);
            for (int i161{0}; i161 < qg_loop_ub; i161++) {
                ctx->u_vec[i161] = r.u_vec[i161];
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
            ctx->cfg.maskTot.size[0] = 1;
            ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
            vg_loop_ub = r.cfg.maskTot.size[1];
            if (vg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[vg_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            bh_loop_ub = r.cfg.maskCart.size[1];
            if (bh_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[bh_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            gh_loop_ub = r.cfg.maskRot.size[1];
            if (gh_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[gh_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            lh_loop_ub = r.cfg.indCart.size(0);
            for (int i166{0}; i166 < lh_loop_ub; i166++) {
                ctx->cfg.indCart.data[i166] = r.cfg.indCart[i166];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            qh_loop_ub = r.cfg.indRot.size(0);
            for (int i171{0}; i171 < qh_loop_ub; i171++) {
                ctx->cfg.indRot.data[i171] = r.cfg.indRot[i171];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            vh_loop_ub = r.cfg.D.size(0);
            for (int i176{0}; i176 < vh_loop_ub; i176++) {
                ctx->cfg.D.data[i176] = r.cfg.D[i176];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            bi_loop_ub = r.cfg.kin_params.size[0];
            if (bi_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[bi_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i181{0}; i181 < 8; i181++) {
                ctx->cfg.kin_type[i181] = r.cfg.kin_type[i181];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i187{0}; i187 < 6; i187++) {
                ctx->cfg.vmax[i187] = r.cfg.vmax[i187];
                ctx->cfg.amax[i187] = r.cfg.amax[i187];
                ctx->cfg.jmax[i187] = r.cfg.jmax[i187];
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
            for (int i192{0}; i192 < 9; i192++) {
                ctx->cfg.LogFileName[i192] = r.cfg.LogFileName[i192];
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
            ii_loop_ub = r.Coeff.size(1);
            for (int i201{0}; i201 < ii_loop_ub; i201++) {
                int ni_loop_ub;
                ni_loop_ub = r.Coeff.size(0);
                for (int i206{0}; i206 < ni_loop_ub; i206++) {
                    ctx->Coeff[i206 + ctx->Coeff.size(0) * i201] =
                        r.Coeff[i206 + r.Coeff.size(0) * i201];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
            ctx->errmsg = r.errmsg;
            ctx->errcode = r.errcode;
        }
        // 'FeedoptPlan:99' assert_queue( ctx.op, ctx.q_gcode );
        // 'FeedoptPlan:161' msg = string( op );
        // 'FeedoptPlan:162' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:163'     msg + " - Check geometry failed...", mfilename );
        r1.init(ctx->op);
        obj.Value.size[0] = 1;
        obj.Value.size[1] = r1.Value.size[1] + 27;
        v_loop_ub = r1.Value.size[1];
        if (v_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[v_loop_ub], &obj.Value.data[0]);
        }
        for (int i26{0}; i26 < 27; i26++) {
            obj.Value.data[i26 + r1.Value.size[1]] = obj2Value[i26];
        }
        f_ocn_assert(checkGeometry(&ctx->q_gcode), &obj);
        // 'FeedoptPlan:164' ocn_assert( checkZSpdmode( queue ), ...
        // 'FeedoptPlan:165'     msg + " - Check zspdmode failed...", mfilename );
        b_obj.Value.size[0] = 1;
        b_obj.Value.size[1] = r1.Value.size[1] + 27;
        wb_loop_ub = r1.Value.size[1];
        if (wb_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[wb_loop_ub], &b_obj.Value.data[0]);
        }
        for (int i52{0}; i52 < 27; i52++) {
            b_obj.Value.data[i52 + r1.Value.size[1]] = b_obj2Value[i52];
        }
        f_ocn_assert(checkZSpdmode(&ctx->q_gcode), &b_obj);
        // 'FeedoptPlan:166' ocn_assert( checkParametrisation( queue ), ...
        // 'FeedoptPlan:167'     msg + " - Check parametrisation failed...", mfilename );
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r1.Value.size[1] + 34;
        jc_loop_ub = r1.Value.size[1];
        if (jc_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[jc_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i60{0}; i60 < 34; i60++) {
            c_obj.Value.data[i60 + r1.Value.size[1]] = c_obj2Value[i60];
        }
        f_ocn_assert(checkParametrisation(&ctx->q_gcode), &c_obj);
        // 'FeedoptPlan:101' ctx.op  = Fopt.Compress;
        ctx->op = Fopt_Compress;
    } break;
    case Fopt_Compress: {
        int gc_loop_ub;
        int kc_loop_ub;
        int lb_loop_ub;
        // 'FeedoptPlan:103' case Fopt.Compress
        // 'FeedoptPlan:104' if ctx.cfg.Compressing.Skip
        if (ctx->cfg.Compressing.Skip) {
            int i7;
            unsigned int u;
            // 'FeedoptPlan:105' for j = 1 : ctx.q_gcode.size
            u = ctx->q_gcode.size();
            i7 = static_cast<int>(u);
            for (int j{0}; j < i7; j++) {
                //  Copy queue GCode in queue Compress
                // 'FeedoptPlan:106' ctx.q_compress.push( ctx.q_gcode.get( j ) );
                ctx->q_gcode.get(j + 1U, &r2);
                ctx->q_compress.push(&r2);
            }
        } else {
            int ac_loop_ub;
            int ag_loop_ub;
            int ch_loop_ub;
            int ci_loop_ub;
            int db_loop_ub;
            int df_loop_ub;
            int ed_loop_ub;
            int ge_loop_ub;
            int hc_loop_ub;
            int hh_loop_ub;
            int i_loop_ub;
            int jd_loop_ub;
            int lg_loop_ub;
            int li_loop_ub;
            int mh_loop_ub;
            int ob_loop_ub;
            int oc_loop_ub;
            int od_loop_ub;
            int of_loop_ub;
            int r_loop_ub;
            int rg_loop_ub;
            int rh_loop_ub;
            int se_loop_ub;
            int tc_loop_ub;
            int td_loop_ub;
            int wg_loop_ub;
            int wh_loop_ub;
            int yc_loop_ub;
            // 'FeedoptPlan:108' else
            // 'FeedoptPlan:109' ctx = compressCurvStructs(ctx);
            r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
            i_loop_ub = ctx->BasisVal.size(1);
            for (int i9{0}; i9 < i_loop_ub; i9++) {
                int q_loop_ub;
                q_loop_ub = ctx->BasisVal.size(0);
                for (int i17{0}; i17 < q_loop_ub; i17++) {
                    r.BasisVal[i17 + r.BasisVal.size(0) * i9] =
                        ctx->BasisVal[i17 + ctx->BasisVal.size(0) * i9];
                }
            }
            r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
            r_loop_ub = ctx->BasisValD.size(1);
            for (int i18{0}; i18 < r_loop_ub; i18++) {
                int cb_loop_ub;
                cb_loop_ub = ctx->BasisValD.size(0);
                for (int i28{0}; i28 < cb_loop_ub; i28++) {
                    r.BasisValD[i28 + r.BasisValD.size(0) * i18] =
                        ctx->BasisValD[i28 + ctx->BasisValD.size(0) * i18];
                }
            }
            r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
            db_loop_ub = ctx->BasisValDD.size(1);
            for (int i29{0}; i29 < db_loop_ub; i29++) {
                int nb_loop_ub;
                nb_loop_ub = ctx->BasisValDD.size(0);
                for (int i38{0}; i38 < nb_loop_ub; i38++) {
                    r.BasisValDD[i38 + r.BasisValDD.size(0) * i29] =
                        ctx->BasisValDD[i38 + ctx->BasisValDD.size(0) * i29];
                }
            }
            r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
            ob_loop_ub = ctx->BasisValDDD.size(1);
            for (int i39{0}; i39 < ob_loop_ub; i39++) {
                int yb_loop_ub;
                yb_loop_ub = ctx->BasisValDDD.size(0);
                for (int i49{0}; i49 < yb_loop_ub; i49++) {
                    r.BasisValDDD[i49 + r.BasisValDDD.size(0) * i39] =
                        ctx->BasisValDDD[i49 + ctx->BasisValDDD.size(0) * i39];
                }
            }
            r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
            ac_loop_ub = ctx->BasisIntegr.size(0);
            for (int i50{0}; i50 < ac_loop_ub; i50++) {
                r.BasisIntegr[i50] = ctx->BasisIntegr[i50];
            }
            r.Bl = ctx->Bl;
            r.u_vec.set_size(1, ctx->u_vec.size(1));
            hc_loop_ub = ctx->u_vec.size(1);
            for (int i57{0}; i57 < hc_loop_ub; i57++) {
                r.u_vec[i57] = ctx->u_vec[i57];
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
            oc_loop_ub = ctx->cfg.maskTot.size[1];
            if (oc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[oc_loop_ub],
                          &r.cfg.maskTot.data[0]);
            }
            r.cfg.maskCart.size[0] = 1;
            r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
            tc_loop_ub = ctx->cfg.maskCart.size[1];
            if (tc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[tc_loop_ub],
                          &r.cfg.maskCart.data[0]);
            }
            r.cfg.maskRot.size[0] = 1;
            r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
            yc_loop_ub = ctx->cfg.maskRot.size[1];
            if (yc_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[yc_loop_ub],
                          &r.cfg.maskRot.data[0]);
            }
            r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
            ed_loop_ub = ctx->cfg.indCart.size[0];
            for (int i66{0}; i66 < ed_loop_ub; i66++) {
                r.cfg.indCart[i66] = ctx->cfg.indCart.data[i66];
            }
            r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
            jd_loop_ub = ctx->cfg.indRot.size[0];
            for (int i71{0}; i71 < jd_loop_ub; i71++) {
                r.cfg.indRot[i71] = ctx->cfg.indRot.data[i71];
            }
            r.cfg.NumberAxis = ctx->cfg.NumberAxis;
            r.cfg.NCart = ctx->cfg.NCart;
            r.cfg.NRot = ctx->cfg.NRot;
            r.cfg.D.set_size(ctx->cfg.D.size[0]);
            od_loop_ub = ctx->cfg.D.size[0];
            for (int i76{0}; i76 < od_loop_ub; i76++) {
                r.cfg.D[i76] = ctx->cfg.D.data[i76];
            }
            r.cfg.coeffD = ctx->cfg.coeffD;
            r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
            td_loop_ub = ctx->cfg.kin_params.size[0];
            if (td_loop_ub - 1 >= 0) {
                std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[td_loop_ub],
                          &r.cfg.kin_params.data[0]);
            }
            for (int i81{0}; i81 < 8; i81++) {
                r.cfg.kin_type[i81] = ctx->cfg.kin_type[i81];
            }
            r.cfg.NDiscr = ctx->cfg.NDiscr;
            r.cfg.NBreak = ctx->cfg.NBreak;
            r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
            r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
            r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
            r.cfg.NHorz = ctx->cfg.NHorz;
            r.cfg.fmax = ctx->cfg.fmax;
            r.cfg.smax = ctx->cfg.smax;
            for (int i86{0}; i86 < 6; i86++) {
                r.cfg.vmax[i86] = ctx->cfg.vmax[i86];
                r.cfg.amax[i86] = ctx->cfg.amax[i86];
                r.cfg.jmax[i86] = ctx->cfg.jmax[i86];
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
            for (int i92{0}; i92 < 9; i92++) {
                r.cfg.LogFileName[i92] = ctx->cfg.LogFileName[i92];
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
            ge_loop_ub = ctx->Coeff.size(1);
            for (int i101{0}; i101 < ge_loop_ub; i101++) {
                int ne_loop_ub;
                ne_loop_ub = ctx->Coeff.size(0);
                for (int i107{0}; i107 < ne_loop_ub; i107++) {
                    r.Coeff[i107 + r.Coeff.size(0) * i101] =
                        ctx->Coeff[i107 + ctx->Coeff.size(0) * i101];
                }
            }
            r.Skipped = ctx->Skipped;
            r.kin = ctx->kin;
            r.errmsg = ctx->errmsg;
            r.errcode = ctx->errcode;
            compressCurvStructs(&r);
            ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
            se_loop_ub = r.BasisVal.size(1);
            for (int i113{0}; i113 < se_loop_ub; i113++) {
                int bf_loop_ub;
                bf_loop_ub = r.BasisVal.size(0);
                for (int i121{0}; i121 < bf_loop_ub; i121++) {
                    ctx->BasisVal[i121 + ctx->BasisVal.size(0) * i113] =
                        r.BasisVal[i121 + r.BasisVal.size(0) * i113];
                }
            }
            ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
            df_loop_ub = r.BasisValD.size(1);
            for (int i122{0}; i122 < df_loop_ub; i122++) {
                int nf_loop_ub;
                nf_loop_ub = r.BasisValD.size(0);
                for (int i133{0}; i133 < nf_loop_ub; i133++) {
                    ctx->BasisValD[i133 + ctx->BasisValD.size(0) * i122] =
                        r.BasisValD[i133 + r.BasisValD.size(0) * i122];
                }
            }
            ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
            of_loop_ub = r.BasisValDD.size(1);
            for (int i134{0}; i134 < of_loop_ub; i134++) {
                int yf_loop_ub;
                yf_loop_ub = r.BasisValDD.size(0);
                for (int i144{0}; i144 < yf_loop_ub; i144++) {
                    ctx->BasisValDD[i144 + ctx->BasisValDD.size(0) * i134] =
                        r.BasisValDD[i144 + r.BasisValDD.size(0) * i134];
                }
            }
            ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
            ag_loop_ub = r.BasisValDDD.size(1);
            for (int i145{0}; i145 < ag_loop_ub; i145++) {
                int jg_loop_ub;
                jg_loop_ub = r.BasisValDDD.size(0);
                for (int i154{0}; i154 < jg_loop_ub; i154++) {
                    ctx->BasisValDDD[i154 + ctx->BasisValDDD.size(0) * i145] =
                        r.BasisValDDD[i154 + r.BasisValDDD.size(0) * i145];
                }
            }
            ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
            lg_loop_ub = r.BasisIntegr.size(0);
            for (int i156{0}; i156 < lg_loop_ub; i156++) {
                ctx->BasisIntegr[i156] = r.BasisIntegr[i156];
            }
            ctx->Bl = r.Bl;
            ctx->u_vec.set_size(1, r.u_vec.size(1));
            rg_loop_ub = r.u_vec.size(1);
            for (int i162{0}; i162 < rg_loop_ub; i162++) {
                ctx->u_vec[i162] = r.u_vec[i162];
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
            ctx->cfg.maskTot.size[0] = 1;
            ctx->cfg.maskTot.size[1] = r.cfg.maskTot.size[1];
            wg_loop_ub = r.cfg.maskTot.size[1];
            if (wg_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[wg_loop_ub],
                          &ctx->cfg.maskTot.data[0]);
            }
            ctx->cfg.maskCart.size[0] = 1;
            ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
            ch_loop_ub = r.cfg.maskCart.size[1];
            if (ch_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[ch_loop_ub],
                          &ctx->cfg.maskCart.data[0]);
            }
            ctx->cfg.maskRot.size[0] = 1;
            ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
            hh_loop_ub = r.cfg.maskRot.size[1];
            if (hh_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[hh_loop_ub],
                          &ctx->cfg.maskRot.data[0]);
            }
            ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
            mh_loop_ub = r.cfg.indCart.size(0);
            for (int i167{0}; i167 < mh_loop_ub; i167++) {
                ctx->cfg.indCart.data[i167] = r.cfg.indCart[i167];
            }
            ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
            rh_loop_ub = r.cfg.indRot.size(0);
            for (int i172{0}; i172 < rh_loop_ub; i172++) {
                ctx->cfg.indRot.data[i172] = r.cfg.indRot[i172];
            }
            ctx->cfg.NumberAxis = r.cfg.NumberAxis;
            ctx->cfg.NCart = r.cfg.NCart;
            ctx->cfg.NRot = r.cfg.NRot;
            ctx->cfg.D.size[0] = r.cfg.D.size(0);
            wh_loop_ub = r.cfg.D.size(0);
            for (int i177{0}; i177 < wh_loop_ub; i177++) {
                ctx->cfg.D.data[i177] = r.cfg.D[i177];
            }
            ctx->cfg.coeffD = r.cfg.coeffD;
            ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
            ci_loop_ub = r.cfg.kin_params.size[0];
            if (ci_loop_ub - 1 >= 0) {
                std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[ci_loop_ub],
                          &ctx->cfg.kin_params.data[0]);
            }
            for (int i182{0}; i182 < 8; i182++) {
                ctx->cfg.kin_type[i182] = r.cfg.kin_type[i182];
            }
            ctx->cfg.NDiscr = r.cfg.NDiscr;
            ctx->cfg.NBreak = r.cfg.NBreak;
            ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
            ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
            ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
            ctx->cfg.NHorz = r.cfg.NHorz;
            ctx->cfg.fmax = r.cfg.fmax;
            ctx->cfg.smax = r.cfg.smax;
            for (int i188{0}; i188 < 6; i188++) {
                ctx->cfg.vmax[i188] = r.cfg.vmax[i188];
                ctx->cfg.amax[i188] = r.cfg.amax[i188];
                ctx->cfg.jmax[i188] = r.cfg.jmax[i188];
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
            for (int i193{0}; i193 < 9; i193++) {
                ctx->cfg.LogFileName[i193] = r.cfg.LogFileName[i193];
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
            li_loop_ub = r.Coeff.size(1);
            for (int i204{0}; i204 < li_loop_ub; i204++) {
                int oi_loop_ub;
                oi_loop_ub = r.Coeff.size(0);
                for (int i207{0}; i207 < oi_loop_ub; i207++) {
                    ctx->Coeff[i207 + ctx->Coeff.size(0) * i204] =
                        r.Coeff[i207 + r.Coeff.size(0) * i204];
                }
            }
            ctx->Skipped = r.Skipped;
            ctx->kin = r.kin;
            ctx->errmsg = r.errmsg;
            ctx->errcode = r.errcode;
        }
        // 'FeedoptPlan:112' assert_queue( ctx.op, ctx.q_compress );
        // 'FeedoptPlan:161' msg = string( op );
        // 'FeedoptPlan:162' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:163'     msg + " - Check geometry failed...", mfilename );
        r1.init(ctx->op);
        obj.Value.size[0] = 1;
        obj.Value.size[1] = r1.Value.size[1] + 27;
        lb_loop_ub = r1.Value.size[1];
        if (lb_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[lb_loop_ub], &obj.Value.data[0]);
        }
        for (int i40{0}; i40 < 27; i40++) {
            obj.Value.data[i40 + r1.Value.size[1]] = obj2Value[i40];
        }
        f_ocn_assert(checkGeometry(&ctx->q_compress), &obj);
        // 'FeedoptPlan:164' ocn_assert( checkZSpdmode( queue ), ...
        // 'FeedoptPlan:165'     msg + " - Check zspdmode failed...", mfilename );
        b_obj.Value.size[0] = 1;
        b_obj.Value.size[1] = r1.Value.size[1] + 27;
        gc_loop_ub = r1.Value.size[1];
        if (gc_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[gc_loop_ub], &b_obj.Value.data[0]);
        }
        for (int i58{0}; i58 < 27; i58++) {
            b_obj.Value.data[i58 + r1.Value.size[1]] = b_obj2Value[i58];
        }
        f_ocn_assert(checkZSpdmode(&ctx->q_compress), &b_obj);
        // 'FeedoptPlan:166' ocn_assert( checkParametrisation( queue ), ...
        // 'FeedoptPlan:167'     msg + " - Check parametrisation failed...", mfilename );
        c_obj.Value.size[0] = 1;
        c_obj.Value.size[1] = r1.Value.size[1] + 34;
        kc_loop_ub = r1.Value.size[1];
        if (kc_loop_ub - 1 >= 0) {
            std::copy(&r1.Value.data[0], &r1.Value.data[kc_loop_ub], &c_obj.Value.data[0]);
        }
        for (int i61{0}; i61 < 34; i61++) {
            c_obj.Value.data[i61 + r1.Value.size[1]] = c_obj2Value[i61];
        }
        f_ocn_assert(checkParametrisation(&ctx->q_compress), &c_obj);
        // 'FeedoptPlan:114' ctx.op = Fopt.Smooth;
        ctx->op = Fopt_Smooth;
        // 'FeedoptPlan:115' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Smooth: {
        int ad_loop_ub;
        int ce_loop_ub;
        int dc_loop_ub;
        int dh_loop_ub;
        int eg_loop_ub;
        int f_loop_ub;
        int fd_loop_ub;
        int gi_loop_ub;
        int hb_loop_ub;
        int hf_loop_ub;
        int ih_loop_ub;
        int l_loop_ub;
        int lc_loop_ub;
        int ld_loop_ub;
        int nh_loop_ub;
        int og_loop_ub;
        int pe_loop_ub;
        int qc_loop_ub;
        int qd_loop_ub;
        int sb_loop_ub;
        int tf_loop_ub;
        int tg_loop_ub;
        int th_loop_ub;
        int vc_loop_ub;
        int ve_loop_ub;
        int w_loop_ub;
        int xg_loop_ub;
        int xh_loop_ub;
        // 'FeedoptPlan:117' case Fopt.Smooth
        // 'FeedoptPlan:118' ctx = smoothCurvStructs(ctx);
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        f_loop_ub = ctx->BasisVal.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            int j_loop_ub;
            j_loop_ub = ctx->BasisVal.size(0);
            for (int i10{0}; i10 < j_loop_ub; i10++) {
                r.BasisVal[i10 + r.BasisVal.size(0) * i5] =
                    ctx->BasisVal[i10 + ctx->BasisVal.size(0) * i5];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        l_loop_ub = ctx->BasisValD.size(1);
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            int s_loop_ub;
            s_loop_ub = ctx->BasisValD.size(0);
            for (int i19{0}; i19 < s_loop_ub; i19++) {
                r.BasisValD[i19 + r.BasisValD.size(0) * i12] =
                    ctx->BasisValD[i19 + ctx->BasisValD.size(0) * i12];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        w_loop_ub = ctx->BasisValDD.size(1);
        for (int i22{0}; i22 < w_loop_ub; i22++) {
            int eb_loop_ub;
            eb_loop_ub = ctx->BasisValDD.size(0);
            for (int i30{0}; i30 < eb_loop_ub; i30++) {
                r.BasisValDD[i30 + r.BasisValDD.size(0) * i22] =
                    ctx->BasisValDD[i30 + ctx->BasisValDD.size(0) * i22];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        hb_loop_ub = ctx->BasisValDDD.size(1);
        for (int i33{0}; i33 < hb_loop_ub; i33++) {
            int pb_loop_ub;
            pb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i41{0}; i41 < pb_loop_ub; i41++) {
                r.BasisValDDD[i41 + r.BasisValDDD.size(0) * i33] =
                    ctx->BasisValDDD[i41 + ctx->BasisValDDD.size(0) * i33];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        sb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i44{0}; i44 < sb_loop_ub; i44++) {
            r.BasisIntegr[i44] = ctx->BasisIntegr[i44];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        dc_loop_ub = ctx->u_vec.size(1);
        for (int i54{0}; i54 < dc_loop_ub; i54++) {
            r.u_vec[i54] = ctx->u_vec[i54];
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
        lc_loop_ub = ctx->cfg.maskTot.size[1];
        if (lc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[lc_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        qc_loop_ub = ctx->cfg.maskCart.size[1];
        if (qc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[qc_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        vc_loop_ub = ctx->cfg.maskRot.size[1];
        if (vc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[vc_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        ad_loop_ub = ctx->cfg.indCart.size[0];
        for (int i62{0}; i62 < ad_loop_ub; i62++) {
            r.cfg.indCart[i62] = ctx->cfg.indCart.data[i62];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        fd_loop_ub = ctx->cfg.indRot.size[0];
        for (int i67{0}; i67 < fd_loop_ub; i67++) {
            r.cfg.indRot[i67] = ctx->cfg.indRot.data[i67];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        ld_loop_ub = ctx->cfg.D.size[0];
        for (int i73{0}; i73 < ld_loop_ub; i73++) {
            r.cfg.D[i73] = ctx->cfg.D.data[i73];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        qd_loop_ub = ctx->cfg.kin_params.size[0];
        if (qd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[qd_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i78{0}; i78 < 8; i78++) {
            r.cfg.kin_type[i78] = ctx->cfg.kin_type[i78];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i83{0}; i83 < 6; i83++) {
            r.cfg.vmax[i83] = ctx->cfg.vmax[i83];
            r.cfg.amax[i83] = ctx->cfg.amax[i83];
            r.cfg.jmax[i83] = ctx->cfg.jmax[i83];
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
        r.cfg.ZeroStartAccLimit = ctx->cfg.ZeroStartAccLimit;
        r.cfg.ZeroStartJerkLimit = ctx->cfg.ZeroStartJerkLimit;
        r.cfg.ZeroStartVelLimit = ctx->cfg.ZeroStartVelLimit;
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &r.cfg.source[0]);
        r.cfg.DebugCutZero = ctx->cfg.DebugCutZero;
        r.cfg.Cusp = ctx->cfg.Cusp;
        r.cfg.Compressing = ctx->cfg.Compressing;
        r.cfg.Smoothing = ctx->cfg.Smoothing;
        r.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int b_i{0}; b_i < 5; b_i++) {
            r.cfg.GaussLegendreX[b_i] = ctx->cfg.GaussLegendreX[b_i];
            r.cfg.GaussLegendreW[b_i] = ctx->cfg.GaussLegendreW[b_i];
        }
        r.cfg.opt = ctx->cfg.opt;
        for (int i88{0}; i88 < 9; i88++) {
            r.cfg.LogFileName[i88] = ctx->cfg.LogFileName[i88];
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
        ce_loop_ub = ctx->Coeff.size(1);
        for (int i97{0}; i97 < ce_loop_ub; i97++) {
            int he_loop_ub;
            he_loop_ub = ctx->Coeff.size(0);
            for (int i102{0}; i102 < he_loop_ub; i102++) {
                r.Coeff[i102 + r.Coeff.size(0) * i97] = ctx->Coeff[i102 + ctx->Coeff.size(0) * i97];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        r.errmsg = ctx->errmsg;
        r.errcode = ctx->errcode;
        smoothCurvStructs(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        pe_loop_ub = r.BasisVal.size(1);
        for (int i110{0}; i110 < pe_loop_ub; i110++) {
            int te_loop_ub;
            te_loop_ub = r.BasisVal.size(0);
            for (int i114{0}; i114 < te_loop_ub; i114++) {
                ctx->BasisVal[i114 + ctx->BasisVal.size(0) * i110] =
                    r.BasisVal[i114 + r.BasisVal.size(0) * i110];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        ve_loop_ub = r.BasisValD.size(1);
        for (int i116{0}; i116 < ve_loop_ub; i116++) {
            int ef_loop_ub;
            ef_loop_ub = r.BasisValD.size(0);
            for (int i123{0}; i123 < ef_loop_ub; i123++) {
                ctx->BasisValD[i123 + ctx->BasisValD.size(0) * i116] =
                    r.BasisValD[i123 + r.BasisValD.size(0) * i116];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        hf_loop_ub = r.BasisValDD.size(1);
        for (int i126{0}; i126 < hf_loop_ub; i126++) {
            int pf_loop_ub;
            pf_loop_ub = r.BasisValDD.size(0);
            for (int i135{0}; i135 < pf_loop_ub; i135++) {
                ctx->BasisValDD[i135 + ctx->BasisValDD.size(0) * i126] =
                    r.BasisValDD[i135 + r.BasisValDD.size(0) * i126];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        tf_loop_ub = r.BasisValDDD.size(1);
        for (int i139{0}; i139 < tf_loop_ub; i139++) {
            int bg_loop_ub;
            bg_loop_ub = r.BasisValDDD.size(0);
            for (int i146{0}; i146 < bg_loop_ub; i146++) {
                ctx->BasisValDDD[i146 + ctx->BasisValDDD.size(0) * i139] =
                    r.BasisValDDD[i146 + r.BasisValDDD.size(0) * i139];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        eg_loop_ub = r.BasisIntegr.size(0);
        for (int i149{0}; i149 < eg_loop_ub; i149++) {
            ctx->BasisIntegr[i149] = r.BasisIntegr[i149];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        og_loop_ub = r.u_vec.size(1);
        for (int i159{0}; i159 < og_loop_ub; i159++) {
            ctx->u_vec[i159] = r.u_vec[i159];
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
        tg_loop_ub = r.cfg.maskTot.size[1];
        if (tg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[tg_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        xg_loop_ub = r.cfg.maskCart.size[1];
        if (xg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[xg_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        dh_loop_ub = r.cfg.maskRot.size[1];
        if (dh_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[dh_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        ih_loop_ub = r.cfg.indCart.size(0);
        for (int i164{0}; i164 < ih_loop_ub; i164++) {
            ctx->cfg.indCart.data[i164] = r.cfg.indCart[i164];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        nh_loop_ub = r.cfg.indRot.size(0);
        for (int i168{0}; i168 < nh_loop_ub; i168++) {
            ctx->cfg.indRot.data[i168] = r.cfg.indRot[i168];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        th_loop_ub = r.cfg.D.size(0);
        for (int i174{0}; i174 < th_loop_ub; i174++) {
            ctx->cfg.D.data[i174] = r.cfg.D[i174];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        xh_loop_ub = r.cfg.kin_params.size[0];
        if (xh_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[xh_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i179{0}; i179 < 8; i179++) {
            ctx->cfg.kin_type[i179] = r.cfg.kin_type[i179];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i185{0}; i185 < 6; i185++) {
            ctx->cfg.vmax[i185] = r.cfg.vmax[i185];
            ctx->cfg.amax[i185] = r.cfg.amax[i185];
            ctx->cfg.jmax[i185] = r.cfg.jmax[i185];
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
        for (int i190{0}; i190 < 9; i190++) {
            ctx->cfg.LogFileName[i190] = r.cfg.LogFileName[i190];
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
        gi_loop_ub = r.Coeff.size(1);
        for (int i199{0}; i199 < gi_loop_ub; i199++) {
            int ji_loop_ub;
            ji_loop_ub = r.Coeff.size(0);
            for (int i202{0}; i202 < ji_loop_ub; i202++) {
                ctx->Coeff[i202 + ctx->Coeff.size(0) * i199] =
                    r.Coeff[i202 + r.Coeff.size(0) * i199];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        ctx->errmsg = r.errmsg;
        ctx->errcode = r.errcode;
        // 'FeedoptPlan:119' ctx.op = Fopt.Split;
        ctx->op = Fopt_Split;
        // 'FeedoptPlan:121' assert_queue( ctx.op, ctx.q_smooth );
        // 'FeedoptPlan:161' msg = string( op );
        // 'FeedoptPlan:162' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:163'     msg + " - Check geometry failed...", mfilename );
        p_ocn_assert(checkGeometry(&r.q_smooth));
        // 'FeedoptPlan:164' ocn_assert( checkZSpdmode( queue ), ...
        // 'FeedoptPlan:165'     msg + " - Check zspdmode failed...", mfilename );
        q_ocn_assert(checkZSpdmode(&r.q_smooth));
        // 'FeedoptPlan:166' ocn_assert( checkParametrisation( queue ), ...
        // 'FeedoptPlan:167'     msg + " - Check parametrisation failed...", mfilename );
        r_ocn_assert(checkParametrisation(&r.q_smooth));
        // 'FeedoptPlan:123' if( coder.target( 'MATLAB') )
    } break;
    case Fopt_Split: {
        int bd_loop_ub;
        int de_loop_ub;
        int ec_loop_ub;
        int eh_loop_ub;
        int fg_loop_ub;
        int g_loop_ub;
        int gd_loop_ub;
        int hi_loop_ub;
        int ib_loop_ub;
        int if_loop_ub;
        int jh_loop_ub;
        int m_loop_ub;
        int mc_loop_ub;
        int md_loop_ub;
        int oh_loop_ub;
        int pg_loop_ub;
        int qe_loop_ub;
        int rc_loop_ub;
        int rd_loop_ub;
        int tb_loop_ub;
        int uf_loop_ub;
        int ug_loop_ub;
        int uh_loop_ub;
        int wc_loop_ub;
        int we_loop_ub;
        int x_loop_ub;
        int yg_loop_ub;
        int yh_loop_ub;
        // 'FeedoptPlan:125' case Fopt.Split
        // 'FeedoptPlan:126' ctx     = splitQueue( ctx );
        r.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        g_loop_ub = ctx->BasisVal.size(1);
        for (int i6{0}; i6 < g_loop_ub; i6++) {
            int k_loop_ub;
            k_loop_ub = ctx->BasisVal.size(0);
            for (int i11{0}; i11 < k_loop_ub; i11++) {
                r.BasisVal[i11 + r.BasisVal.size(0) * i6] =
                    ctx->BasisVal[i11 + ctx->BasisVal.size(0) * i6];
            }
        }
        r.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        m_loop_ub = ctx->BasisValD.size(1);
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            int t_loop_ub;
            t_loop_ub = ctx->BasisValD.size(0);
            for (int i20{0}; i20 < t_loop_ub; i20++) {
                r.BasisValD[i20 + r.BasisValD.size(0) * i13] =
                    ctx->BasisValD[i20 + ctx->BasisValD.size(0) * i13];
            }
        }
        r.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        x_loop_ub = ctx->BasisValDD.size(1);
        for (int i23{0}; i23 < x_loop_ub; i23++) {
            int fb_loop_ub;
            fb_loop_ub = ctx->BasisValDD.size(0);
            for (int i31{0}; i31 < fb_loop_ub; i31++) {
                r.BasisValDD[i31 + r.BasisValDD.size(0) * i23] =
                    ctx->BasisValDD[i31 + ctx->BasisValDD.size(0) * i23];
            }
        }
        r.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        ib_loop_ub = ctx->BasisValDDD.size(1);
        for (int i34{0}; i34 < ib_loop_ub; i34++) {
            int qb_loop_ub;
            qb_loop_ub = ctx->BasisValDDD.size(0);
            for (int i42{0}; i42 < qb_loop_ub; i42++) {
                r.BasisValDDD[i42 + r.BasisValDDD.size(0) * i34] =
                    ctx->BasisValDDD[i42 + ctx->BasisValDDD.size(0) * i34];
            }
        }
        r.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        tb_loop_ub = ctx->BasisIntegr.size(0);
        for (int i45{0}; i45 < tb_loop_ub; i45++) {
            r.BasisIntegr[i45] = ctx->BasisIntegr[i45];
        }
        r.Bl = ctx->Bl;
        r.u_vec.set_size(1, ctx->u_vec.size(1));
        ec_loop_ub = ctx->u_vec.size(1);
        for (int i55{0}; i55 < ec_loop_ub; i55++) {
            r.u_vec[i55] = ctx->u_vec[i55];
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
        mc_loop_ub = ctx->cfg.maskTot.size[1];
        if (mc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[mc_loop_ub],
                      &r.cfg.maskTot.data[0]);
        }
        r.cfg.maskCart.size[0] = 1;
        r.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        rc_loop_ub = ctx->cfg.maskCart.size[1];
        if (rc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[rc_loop_ub],
                      &r.cfg.maskCart.data[0]);
        }
        r.cfg.maskRot.size[0] = 1;
        r.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        wc_loop_ub = ctx->cfg.maskRot.size[1];
        if (wc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[wc_loop_ub],
                      &r.cfg.maskRot.data[0]);
        }
        r.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        bd_loop_ub = ctx->cfg.indCart.size[0];
        for (int i63{0}; i63 < bd_loop_ub; i63++) {
            r.cfg.indCart[i63] = ctx->cfg.indCart.data[i63];
        }
        r.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        gd_loop_ub = ctx->cfg.indRot.size[0];
        for (int i68{0}; i68 < gd_loop_ub; i68++) {
            r.cfg.indRot[i68] = ctx->cfg.indRot.data[i68];
        }
        r.cfg.NumberAxis = ctx->cfg.NumberAxis;
        r.cfg.NCart = ctx->cfg.NCart;
        r.cfg.NRot = ctx->cfg.NRot;
        r.cfg.D.set_size(ctx->cfg.D.size[0]);
        md_loop_ub = ctx->cfg.D.size[0];
        for (int i74{0}; i74 < md_loop_ub; i74++) {
            r.cfg.D[i74] = ctx->cfg.D.data[i74];
        }
        r.cfg.coeffD = ctx->cfg.coeffD;
        r.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        rd_loop_ub = ctx->cfg.kin_params.size[0];
        if (rd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[rd_loop_ub],
                      &r.cfg.kin_params.data[0]);
        }
        for (int i79{0}; i79 < 8; i79++) {
            r.cfg.kin_type[i79] = ctx->cfg.kin_type[i79];
        }
        r.cfg.NDiscr = ctx->cfg.NDiscr;
        r.cfg.NBreak = ctx->cfg.NBreak;
        r.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        r.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        r.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        r.cfg.NHorz = ctx->cfg.NHorz;
        r.cfg.fmax = ctx->cfg.fmax;
        r.cfg.smax = ctx->cfg.smax;
        for (int i84{0}; i84 < 6; i84++) {
            r.cfg.vmax[i84] = ctx->cfg.vmax[i84];
            r.cfg.amax[i84] = ctx->cfg.amax[i84];
            r.cfg.jmax[i84] = ctx->cfg.jmax[i84];
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
        for (int i89{0}; i89 < 9; i89++) {
            r.cfg.LogFileName[i89] = ctx->cfg.LogFileName[i89];
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
        de_loop_ub = ctx->Coeff.size(1);
        for (int i98{0}; i98 < de_loop_ub; i98++) {
            int ie_loop_ub;
            ie_loop_ub = ctx->Coeff.size(0);
            for (int i103{0}; i103 < ie_loop_ub; i103++) {
                r.Coeff[i103 + r.Coeff.size(0) * i98] = ctx->Coeff[i103 + ctx->Coeff.size(0) * i98];
            }
        }
        r.Skipped = ctx->Skipped;
        r.kin = ctx->kin;
        r.errmsg = ctx->errmsg;
        r.errcode = ctx->errcode;
        splitQueue(&r);
        ctx->BasisVal.set_size(r.BasisVal.size(0), r.BasisVal.size(1));
        qe_loop_ub = r.BasisVal.size(1);
        for (int i111{0}; i111 < qe_loop_ub; i111++) {
            int ue_loop_ub;
            ue_loop_ub = r.BasisVal.size(0);
            for (int i115{0}; i115 < ue_loop_ub; i115++) {
                ctx->BasisVal[i115 + ctx->BasisVal.size(0) * i111] =
                    r.BasisVal[i115 + r.BasisVal.size(0) * i111];
            }
        }
        ctx->BasisValD.set_size(r.BasisValD.size(0), r.BasisValD.size(1));
        we_loop_ub = r.BasisValD.size(1);
        for (int i117{0}; i117 < we_loop_ub; i117++) {
            int ff_loop_ub;
            ff_loop_ub = r.BasisValD.size(0);
            for (int i124{0}; i124 < ff_loop_ub; i124++) {
                ctx->BasisValD[i124 + ctx->BasisValD.size(0) * i117] =
                    r.BasisValD[i124 + r.BasisValD.size(0) * i117];
            }
        }
        ctx->BasisValDD.set_size(r.BasisValDD.size(0), r.BasisValDD.size(1));
        if_loop_ub = r.BasisValDD.size(1);
        for (int i127{0}; i127 < if_loop_ub; i127++) {
            int qf_loop_ub;
            qf_loop_ub = r.BasisValDD.size(0);
            for (int i136{0}; i136 < qf_loop_ub; i136++) {
                ctx->BasisValDD[i136 + ctx->BasisValDD.size(0) * i127] =
                    r.BasisValDD[i136 + r.BasisValDD.size(0) * i127];
            }
        }
        ctx->BasisValDDD.set_size(r.BasisValDDD.size(0), r.BasisValDDD.size(1));
        uf_loop_ub = r.BasisValDDD.size(1);
        for (int i140{0}; i140 < uf_loop_ub; i140++) {
            int cg_loop_ub;
            cg_loop_ub = r.BasisValDDD.size(0);
            for (int i147{0}; i147 < cg_loop_ub; i147++) {
                ctx->BasisValDDD[i147 + ctx->BasisValDDD.size(0) * i140] =
                    r.BasisValDDD[i147 + r.BasisValDDD.size(0) * i140];
            }
        }
        ctx->BasisIntegr.set_size(r.BasisIntegr.size(0));
        fg_loop_ub = r.BasisIntegr.size(0);
        for (int i150{0}; i150 < fg_loop_ub; i150++) {
            ctx->BasisIntegr[i150] = r.BasisIntegr[i150];
        }
        ctx->Bl = r.Bl;
        ctx->u_vec.set_size(1, r.u_vec.size(1));
        pg_loop_ub = r.u_vec.size(1);
        for (int i160{0}; i160 < pg_loop_ub; i160++) {
            ctx->u_vec[i160] = r.u_vec[i160];
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
        ug_loop_ub = r.cfg.maskTot.size[1];
        if (ug_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskTot.data[0], &r.cfg.maskTot.data[ug_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = r.cfg.maskCart.size[1];
        yg_loop_ub = r.cfg.maskCart.size[1];
        if (yg_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskCart.data[0], &r.cfg.maskCart.data[yg_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = r.cfg.maskRot.size[1];
        eh_loop_ub = r.cfg.maskRot.size[1];
        if (eh_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.maskRot.data[0], &r.cfg.maskRot.data[eh_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = r.cfg.indCart.size(0);
        jh_loop_ub = r.cfg.indCart.size(0);
        for (int i165{0}; i165 < jh_loop_ub; i165++) {
            ctx->cfg.indCart.data[i165] = r.cfg.indCart[i165];
        }
        ctx->cfg.indRot.size[0] = r.cfg.indRot.size(0);
        oh_loop_ub = r.cfg.indRot.size(0);
        for (int i169{0}; i169 < oh_loop_ub; i169++) {
            ctx->cfg.indRot.data[i169] = r.cfg.indRot[i169];
        }
        ctx->cfg.NumberAxis = r.cfg.NumberAxis;
        ctx->cfg.NCart = r.cfg.NCart;
        ctx->cfg.NRot = r.cfg.NRot;
        ctx->cfg.D.size[0] = r.cfg.D.size(0);
        uh_loop_ub = r.cfg.D.size(0);
        for (int i175{0}; i175 < uh_loop_ub; i175++) {
            ctx->cfg.D.data[i175] = r.cfg.D[i175];
        }
        ctx->cfg.coeffD = r.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = r.cfg.kin_params.size[0];
        yh_loop_ub = r.cfg.kin_params.size[0];
        if (yh_loop_ub - 1 >= 0) {
            std::copy(&r.cfg.kin_params.data[0], &r.cfg.kin_params.data[yh_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i180{0}; i180 < 8; i180++) {
            ctx->cfg.kin_type[i180] = r.cfg.kin_type[i180];
        }
        ctx->cfg.NDiscr = r.cfg.NDiscr;
        ctx->cfg.NBreak = r.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = r.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = r.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = r.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = r.cfg.NHorz;
        ctx->cfg.fmax = r.cfg.fmax;
        ctx->cfg.smax = r.cfg.smax;
        for (int i186{0}; i186 < 6; i186++) {
            ctx->cfg.vmax[i186] = r.cfg.vmax[i186];
            ctx->cfg.amax[i186] = r.cfg.amax[i186];
            ctx->cfg.jmax[i186] = r.cfg.jmax[i186];
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
        for (int i191{0}; i191 < 9; i191++) {
            ctx->cfg.LogFileName[i191] = r.cfg.LogFileName[i191];
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
        hi_loop_ub = r.Coeff.size(1);
        for (int i200{0}; i200 < hi_loop_ub; i200++) {
            int ki_loop_ub;
            ki_loop_ub = r.Coeff.size(0);
            for (int i203{0}; i203 < ki_loop_ub; i203++) {
                ctx->Coeff[i203 + ctx->Coeff.size(0) * i200] =
                    r.Coeff[i203 + r.Coeff.size(0) * i200];
            }
        }
        ctx->Skipped = r.Skipped;
        ctx->kin = r.kin;
        ctx->errmsg = r.errmsg;
        ctx->errcode = r.errcode;
        // 'FeedoptPlan:127' ctx.op  = Fopt.Opt;
        ctx->op = Fopt_Opt;
        // 'FeedoptPlan:129' if( coder.target( 'MATLAB' ) )
        // 'FeedoptPlan:133' assert_queue( ctx.op, ctx.q_split );
        // 'FeedoptPlan:161' msg = string( op );
        // 'FeedoptPlan:162' ocn_assert( checkGeometry( queue ), ...
        // 'FeedoptPlan:163'     msg + " - Check geometry failed...", mfilename );
        cb_ocn_assert(checkGeometry(&r.q_split));
        // 'FeedoptPlan:164' ocn_assert( checkZSpdmode( queue ), ...
        // 'FeedoptPlan:165'     msg + " - Check zspdmode failed...", mfilename );
        db_ocn_assert(checkZSpdmode(&r.q_split));
        // 'FeedoptPlan:166' ocn_assert( checkParametrisation( queue ), ...
        // 'FeedoptPlan:167'     msg + " - Check parametrisation failed...", mfilename );
        eb_ocn_assert(checkParametrisation(&r.q_split));
        //          histogramLength( ctx, ctx.q_split, "Splitting" );
        // 'FeedoptPlan:136' if( coder.target( 'MATLAB' ) )
    } break;
    case Fopt_Opt: {
        int ah_loop_ub;
        int ai_loop_ub;
        int cc_loop_ub;
        int cd_loop_ub;
        int di_loop_ub;
        int fh_loop_ub;
        int gg_loop_ub;
        int hd_loop_ub;
        int ic_loop_ub;
        int jb_loop_ub;
        int je_loop_ub;
        int jf_loop_ub;
        int kd_loop_ub;
        int kh_loop_ub;
        int mi_loop_ub;
        int n_loop_ub;
        int ng_loop_ub;
        int pc_loop_ub;
        int pd_loop_ub;
        int ph_loop_ub;
        int sg_loop_ub;
        int sh_loop_ub;
        int ub_loop_ub;
        int uc_loop_ub;
        int ud_loop_ub;
        int vf_loop_ub;
        int xe_loop_ub;
        int y_loop_ub;
        // 'FeedoptPlan:138' case Fopt.Opt
        // 'FeedoptPlan:139' if( ctx.q_opt.size() == 0 )
        if (ctx->q_opt.size() == 0U) {
            // 'FeedoptPlan:139' ctx.k0 = int32( 1 );
            ctx->k0 = 1;
        }
        //          ctx.op = Fopt.Finished; return;
        // 'FeedoptPlan:141' [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        b_ctx.BasisVal.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
        n_loop_ub = ctx->BasisVal.size(1);
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            int u_loop_ub;
            u_loop_ub = ctx->BasisVal.size(0);
            for (int i21{0}; i21 < u_loop_ub; i21++) {
                b_ctx.BasisVal[i21 + b_ctx.BasisVal.size(0) * i14] =
                    ctx->BasisVal[i21 + ctx->BasisVal.size(0) * i14];
            }
        }
        b_ctx.BasisValD.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
        y_loop_ub = ctx->BasisValD.size(1);
        for (int i24{0}; i24 < y_loop_ub; i24++) {
            int gb_loop_ub;
            gb_loop_ub = ctx->BasisValD.size(0);
            for (int i32{0}; i32 < gb_loop_ub; i32++) {
                b_ctx.BasisValD[i32 + b_ctx.BasisValD.size(0) * i24] =
                    ctx->BasisValD[i32 + ctx->BasisValD.size(0) * i24];
            }
        }
        b_ctx.BasisValDD.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
        jb_loop_ub = ctx->BasisValDD.size(1);
        for (int i35{0}; i35 < jb_loop_ub; i35++) {
            int rb_loop_ub;
            rb_loop_ub = ctx->BasisValDD.size(0);
            for (int i43{0}; i43 < rb_loop_ub; i43++) {
                b_ctx.BasisValDD[i43 + b_ctx.BasisValDD.size(0) * i35] =
                    ctx->BasisValDD[i43 + ctx->BasisValDD.size(0) * i35];
            }
        }
        b_ctx.BasisValDDD.set_size(ctx->BasisValDDD.size(0), ctx->BasisValDDD.size(1));
        ub_loop_ub = ctx->BasisValDDD.size(1);
        for (int i46{0}; i46 < ub_loop_ub; i46++) {
            int bc_loop_ub;
            bc_loop_ub = ctx->BasisValDDD.size(0);
            for (int i51{0}; i51 < bc_loop_ub; i51++) {
                b_ctx.BasisValDDD[i51 + b_ctx.BasisValDDD.size(0) * i46] =
                    ctx->BasisValDDD[i51 + ctx->BasisValDDD.size(0) * i46];
            }
        }
        b_ctx.BasisIntegr.set_size(ctx->BasisIntegr.size(0));
        cc_loop_ub = ctx->BasisIntegr.size(0);
        for (int i53{0}; i53 < cc_loop_ub; i53++) {
            b_ctx.BasisIntegr[i53] = ctx->BasisIntegr[i53];
        }
        b_ctx.Bl = ctx->Bl;
        b_ctx.u_vec.set_size(1, ctx->u_vec.size(1));
        ic_loop_ub = ctx->u_vec.size(1);
        for (int i59{0}; i59 < ic_loop_ub; i59++) {
            b_ctx.u_vec[i59] = ctx->u_vec[i59];
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
        pc_loop_ub = ctx->cfg.maskTot.size[1];
        if (pc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskTot.data[0], &ctx->cfg.maskTot.data[pc_loop_ub],
                      &b_ctx.cfg.maskTot.data[0]);
        }
        b_ctx.cfg.maskCart.size[0] = 1;
        b_ctx.cfg.maskCart.size[1] = ctx->cfg.maskCart.size[1];
        uc_loop_ub = ctx->cfg.maskCart.size[1];
        if (uc_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskCart.data[0], &ctx->cfg.maskCart.data[uc_loop_ub],
                      &b_ctx.cfg.maskCart.data[0]);
        }
        b_ctx.cfg.maskRot.size[0] = 1;
        b_ctx.cfg.maskRot.size[1] = ctx->cfg.maskRot.size[1];
        cd_loop_ub = ctx->cfg.maskRot.size[1];
        if (cd_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.maskRot.data[0], &ctx->cfg.maskRot.data[cd_loop_ub],
                      &b_ctx.cfg.maskRot.data[0]);
        }
        b_ctx.cfg.indCart.set_size(ctx->cfg.indCart.size[0]);
        hd_loop_ub = ctx->cfg.indCart.size[0];
        for (int i69{0}; i69 < hd_loop_ub; i69++) {
            b_ctx.cfg.indCart[i69] = ctx->cfg.indCart.data[i69];
        }
        b_ctx.cfg.indRot.set_size(ctx->cfg.indRot.size[0]);
        kd_loop_ub = ctx->cfg.indRot.size[0];
        for (int i72{0}; i72 < kd_loop_ub; i72++) {
            b_ctx.cfg.indRot[i72] = ctx->cfg.indRot.data[i72];
        }
        b_ctx.cfg.NumberAxis = ctx->cfg.NumberAxis;
        b_ctx.cfg.NCart = ctx->cfg.NCart;
        b_ctx.cfg.NRot = ctx->cfg.NRot;
        b_ctx.cfg.D.set_size(ctx->cfg.D.size[0]);
        pd_loop_ub = ctx->cfg.D.size[0];
        for (int i77{0}; i77 < pd_loop_ub; i77++) {
            b_ctx.cfg.D[i77] = ctx->cfg.D.data[i77];
        }
        b_ctx.cfg.coeffD = ctx->cfg.coeffD;
        b_ctx.cfg.kin_params.size[0] = ctx->cfg.kin_params.size[0];
        ud_loop_ub = ctx->cfg.kin_params.size[0];
        if (ud_loop_ub - 1 >= 0) {
            std::copy(&ctx->cfg.kin_params.data[0], &ctx->cfg.kin_params.data[ud_loop_ub],
                      &b_ctx.cfg.kin_params.data[0]);
        }
        for (int i82{0}; i82 < 8; i82++) {
            b_ctx.cfg.kin_type[i82] = ctx->cfg.kin_type[i82];
        }
        b_ctx.cfg.NDiscr = ctx->cfg.NDiscr;
        b_ctx.cfg.NBreak = ctx->cfg.NBreak;
        b_ctx.cfg.UseDynamicBreakpoints = ctx->cfg.UseDynamicBreakpoints;
        b_ctx.cfg.UseLinearBreakpoints = ctx->cfg.UseLinearBreakpoints;
        b_ctx.cfg.DynamicBreakpointsDistance = ctx->cfg.DynamicBreakpointsDistance;
        b_ctx.cfg.NHorz = ctx->cfg.NHorz;
        b_ctx.cfg.fmax = ctx->cfg.fmax;
        b_ctx.cfg.smax = ctx->cfg.smax;
        for (int i87{0}; i87 < 6; i87++) {
            b_ctx.cfg.vmax[i87] = ctx->cfg.vmax[i87];
            b_ctx.cfg.amax[i87] = ctx->cfg.amax[i87];
            b_ctx.cfg.jmax[i87] = ctx->cfg.jmax[i87];
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
        b_ctx.cfg.ZeroStartAccLimit = ctx->cfg.ZeroStartAccLimit;
        b_ctx.cfg.ZeroStartJerkLimit = ctx->cfg.ZeroStartJerkLimit;
        b_ctx.cfg.ZeroStartVelLimit = ctx->cfg.ZeroStartVelLimit;
        std::copy(&ctx->cfg.source[0], &ctx->cfg.source[1024], &b_ctx.cfg.source[0]);
        b_ctx.cfg.DebugCutZero = ctx->cfg.DebugCutZero;
        b_ctx.cfg.Cusp = ctx->cfg.Cusp;
        b_ctx.cfg.Compressing = ctx->cfg.Compressing;
        b_ctx.cfg.Smoothing = ctx->cfg.Smoothing;
        b_ctx.cfg.GaussLegendreN = ctx->cfg.GaussLegendreN;
        for (int f_i{0}; f_i < 5; f_i++) {
            b_ctx.cfg.GaussLegendreX[f_i] = ctx->cfg.GaussLegendreX[f_i];
            b_ctx.cfg.GaussLegendreW[f_i] = ctx->cfg.GaussLegendreW[f_i];
        }
        b_ctx.cfg.opt = ctx->cfg.opt;
        for (int i93{0}; i93 < 9; i93++) {
            b_ctx.cfg.LogFileName[i93] = ctx->cfg.LogFileName[i93];
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
        je_loop_ub = ctx->Coeff.size(1);
        for (int i104{0}; i104 < je_loop_ub; i104++) {
            int oe_loop_ub;
            oe_loop_ub = ctx->Coeff.size(0);
            for (int i108{0}; i108 < oe_loop_ub; i108++) {
                b_ctx.Coeff[i108 + b_ctx.Coeff.size(0) * i104] =
                    ctx->Coeff[i108 + ctx->Coeff.size(0) * i104];
            }
        }
        b_ctx.Skipped = ctx->Skipped;
        b_ctx.kin = ctx->kin;
        b_ctx.errmsg = ctx->errmsg;
        b_ctx.errcode = ctx->errcode;
        feedratePlanning(&b_ctx, &c_optimized, opt_struct, &quit);
        ctx->BasisVal.set_size(b_ctx.BasisVal.size(0), b_ctx.BasisVal.size(1));
        xe_loop_ub = b_ctx.BasisVal.size(1);
        for (int i118{0}; i118 < xe_loop_ub; i118++) {
            int gf_loop_ub;
            gf_loop_ub = b_ctx.BasisVal.size(0);
            for (int i125{0}; i125 < gf_loop_ub; i125++) {
                ctx->BasisVal[i125 + ctx->BasisVal.size(0) * i118] =
                    b_ctx.BasisVal[i125 + b_ctx.BasisVal.size(0) * i118];
            }
        }
        ctx->BasisValD.set_size(b_ctx.BasisValD.size(0), b_ctx.BasisValD.size(1));
        jf_loop_ub = b_ctx.BasisValD.size(1);
        for (int i128{0}; i128 < jf_loop_ub; i128++) {
            int rf_loop_ub;
            rf_loop_ub = b_ctx.BasisValD.size(0);
            for (int i137{0}; i137 < rf_loop_ub; i137++) {
                ctx->BasisValD[i137 + ctx->BasisValD.size(0) * i128] =
                    b_ctx.BasisValD[i137 + b_ctx.BasisValD.size(0) * i128];
            }
        }
        ctx->BasisValDD.set_size(b_ctx.BasisValDD.size(0), b_ctx.BasisValDD.size(1));
        vf_loop_ub = b_ctx.BasisValDD.size(1);
        for (int i141{0}; i141 < vf_loop_ub; i141++) {
            int dg_loop_ub;
            dg_loop_ub = b_ctx.BasisValDD.size(0);
            for (int i148{0}; i148 < dg_loop_ub; i148++) {
                ctx->BasisValDD[i148 + ctx->BasisValDD.size(0) * i141] =
                    b_ctx.BasisValDD[i148 + b_ctx.BasisValDD.size(0) * i141];
            }
        }
        ctx->BasisValDDD.set_size(b_ctx.BasisValDDD.size(0), b_ctx.BasisValDDD.size(1));
        gg_loop_ub = b_ctx.BasisValDDD.size(1);
        for (int i151{0}; i151 < gg_loop_ub; i151++) {
            int mg_loop_ub;
            mg_loop_ub = b_ctx.BasisValDDD.size(0);
            for (int i157{0}; i157 < mg_loop_ub; i157++) {
                ctx->BasisValDDD[i157 + ctx->BasisValDDD.size(0) * i151] =
                    b_ctx.BasisValDDD[i157 + b_ctx.BasisValDDD.size(0) * i151];
            }
        }
        ctx->BasisIntegr.set_size(b_ctx.BasisIntegr.size(0));
        ng_loop_ub = b_ctx.BasisIntegr.size(0);
        for (int i158{0}; i158 < ng_loop_ub; i158++) {
            ctx->BasisIntegr[i158] = b_ctx.BasisIntegr[i158];
        }
        ctx->Bl = b_ctx.Bl;
        ctx->u_vec.set_size(1, b_ctx.u_vec.size(1));
        sg_loop_ub = b_ctx.u_vec.size(1);
        for (int i163{0}; i163 < sg_loop_ub; i163++) {
            ctx->u_vec[i163] = b_ctx.u_vec[i163];
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
        ah_loop_ub = b_ctx.cfg.maskTot.size[1];
        if (ah_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskTot.data[0], &b_ctx.cfg.maskTot.data[ah_loop_ub],
                      &ctx->cfg.maskTot.data[0]);
        }
        ctx->cfg.maskCart.size[0] = 1;
        ctx->cfg.maskCart.size[1] = b_ctx.cfg.maskCart.size[1];
        fh_loop_ub = b_ctx.cfg.maskCart.size[1];
        if (fh_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskCart.data[0], &b_ctx.cfg.maskCart.data[fh_loop_ub],
                      &ctx->cfg.maskCart.data[0]);
        }
        ctx->cfg.maskRot.size[0] = 1;
        ctx->cfg.maskRot.size[1] = b_ctx.cfg.maskRot.size[1];
        kh_loop_ub = b_ctx.cfg.maskRot.size[1];
        if (kh_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.maskRot.data[0], &b_ctx.cfg.maskRot.data[kh_loop_ub],
                      &ctx->cfg.maskRot.data[0]);
        }
        ctx->cfg.indCart.size[0] = b_ctx.cfg.indCart.size(0);
        ph_loop_ub = b_ctx.cfg.indCart.size(0);
        for (int i170{0}; i170 < ph_loop_ub; i170++) {
            ctx->cfg.indCart.data[i170] = b_ctx.cfg.indCart[i170];
        }
        ctx->cfg.indRot.size[0] = b_ctx.cfg.indRot.size(0);
        sh_loop_ub = b_ctx.cfg.indRot.size(0);
        for (int i173{0}; i173 < sh_loop_ub; i173++) {
            ctx->cfg.indRot.data[i173] = b_ctx.cfg.indRot[i173];
        }
        ctx->cfg.NumberAxis = b_ctx.cfg.NumberAxis;
        ctx->cfg.NCart = b_ctx.cfg.NCart;
        ctx->cfg.NRot = b_ctx.cfg.NRot;
        ctx->cfg.D.size[0] = b_ctx.cfg.D.size(0);
        ai_loop_ub = b_ctx.cfg.D.size(0);
        for (int i178{0}; i178 < ai_loop_ub; i178++) {
            ctx->cfg.D.data[i178] = b_ctx.cfg.D[i178];
        }
        ctx->cfg.coeffD = b_ctx.cfg.coeffD;
        ctx->cfg.kin_params.size[0] = b_ctx.cfg.kin_params.size[0];
        di_loop_ub = b_ctx.cfg.kin_params.size[0];
        if (di_loop_ub - 1 >= 0) {
            std::copy(&b_ctx.cfg.kin_params.data[0], &b_ctx.cfg.kin_params.data[di_loop_ub],
                      &ctx->cfg.kin_params.data[0]);
        }
        for (int i183{0}; i183 < 8; i183++) {
            ctx->cfg.kin_type[i183] = b_ctx.cfg.kin_type[i183];
        }
        ctx->cfg.NDiscr = b_ctx.cfg.NDiscr;
        ctx->cfg.NBreak = b_ctx.cfg.NBreak;
        ctx->cfg.UseDynamicBreakpoints = b_ctx.cfg.UseDynamicBreakpoints;
        ctx->cfg.UseLinearBreakpoints = b_ctx.cfg.UseLinearBreakpoints;
        ctx->cfg.DynamicBreakpointsDistance = b_ctx.cfg.DynamicBreakpointsDistance;
        ctx->cfg.NHorz = b_ctx.cfg.NHorz;
        ctx->cfg.fmax = b_ctx.cfg.fmax;
        ctx->cfg.smax = b_ctx.cfg.smax;
        for (int i189{0}; i189 < 6; i189++) {
            ctx->cfg.vmax[i189] = b_ctx.cfg.vmax[i189];
            ctx->cfg.amax[i189] = b_ctx.cfg.amax[i189];
            ctx->cfg.jmax[i189] = b_ctx.cfg.jmax[i189];
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
        ctx->cfg.ZeroStartAccLimit = b_ctx.cfg.ZeroStartAccLimit;
        ctx->cfg.ZeroStartJerkLimit = b_ctx.cfg.ZeroStartJerkLimit;
        ctx->cfg.ZeroStartVelLimit = b_ctx.cfg.ZeroStartVelLimit;
        std::copy(&b_ctx.cfg.source[0], &b_ctx.cfg.source[1024], &ctx->cfg.source[0]);
        ctx->cfg.DebugCutZero = b_ctx.cfg.DebugCutZero;
        ctx->cfg.Cusp = b_ctx.cfg.Cusp;
        ctx->cfg.Compressing = b_ctx.cfg.Compressing;
        ctx->cfg.Smoothing = b_ctx.cfg.Smoothing;
        ctx->cfg.GaussLegendreN = b_ctx.cfg.GaussLegendreN;
        for (int k_i{0}; k_i < 5; k_i++) {
            ctx->cfg.GaussLegendreX[k_i] = b_ctx.cfg.GaussLegendreX[k_i];
            ctx->cfg.GaussLegendreW[k_i] = b_ctx.cfg.GaussLegendreW[k_i];
        }
        ctx->cfg.opt = b_ctx.cfg.opt;
        for (int i194{0}; i194 < 9; i194++) {
            ctx->cfg.LogFileName[i194] = b_ctx.cfg.LogFileName[i194];
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
        mi_loop_ub = b_ctx.Coeff.size(1);
        for (int i205{0}; i205 < mi_loop_ub; i205++) {
            int pi_loop_ub;
            pi_loop_ub = b_ctx.Coeff.size(0);
            for (int i208{0}; i208 < pi_loop_ub; i208++) {
                ctx->Coeff[i208 + ctx->Coeff.size(0) * i205] =
                    b_ctx.Coeff[i208 + b_ctx.Coeff.size(0) * i205];
            }
        }
        ctx->Skipped = b_ctx.Skipped;
        ctx->kin = b_ctx.kin;
        ctx->errmsg = b_ctx.errmsg;
        ctx->errcode = b_ctx.errcode;
        b_optimized = c_optimized;
        // 'FeedoptPlan:142' if optimized
        if (c_optimized) {
            // 'FeedoptPlan:143' ctx.go_next = true;
            ctx->go_next = true;
            // 'FeedoptPlan:144' ctx.q_opt.push( opt_struct );
            b_ctx.q_opt.push(opt_struct);
        }
        // 'FeedoptPlan:147' if( quit )
    } break;
    case Fopt_Finished:
        // 'FeedoptPlan:149' case Fopt.Finished
        // 'FeedoptPlan:150' ctx.op = Fopt.Finished;
        ctx->op = Fopt_Finished;
        break;
    default:
        // 'FeedoptPlan:152' otherwise
        // 'FeedoptPlan:153' DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
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
        // 'FeedoptPlan:154' ctx.op = Fopt.Finished;
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
