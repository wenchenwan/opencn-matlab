
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "ReadGCode.h"
#include "constrCurvStruct.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "string1.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include "cpp_interp.hpp"
#include <algorithm>
#include <stdio.h>

// Function Definitions
//
// function [ status, CurvStruct, err_msg ] = ReadGCode( cfg, cmd, filename )
//
// ReadGCode : Read the G code contents.
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
//
// Arguments    : const FeedoptConfig cfg
//                ReadGCodeCmd cmd
//                const char filename_data[]
//                const int filename_size[2]
//                ReadGCodeError *status
//                CurvStruct *c_CurvStruct
//                MsgStruct *err_msg
// Return Type  : void
//
namespace ocn {
void ReadGCode(const FeedoptConfig, ReadGCodeCmd cmd, const char filename_data[],
               const int filename_size[2], ReadGCodeError *status, CurvStruct *c_CurvStruct,
               MsgStruct *err_msg)
{
    static const char obj1Value[6]{'[', 'L', 'i', 'n', 'e', ' '};
    coder::rtString obj;
    Axes params_tool_offset;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
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
    int g_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int resCount;
    char tmp_data[1025];
    char st[12];
    char obj2Value_data[11];
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ReadGCodeError b_status;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    //  Wrapper for pulling the next gcode line from the interpreter
    // 'ReadGCode:18' status          = ReadGCodeError.InterpError;
    // 'ReadGCode:19' CurvStruct      = constrCurvStructType;
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
    c_CurvStruct->Info = e_expl_temp.Info;
    c_CurvStruct->tool = e_expl_temp.tool;
    c_CurvStruct->sp = e_expl_temp.sp;
    c_CurvStruct->R0.set_size(e_expl_temp.R0.size[0]);
    loop_ub = e_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        c_CurvStruct->R0[i] = e_expl_temp.R0.data[i];
    }
    c_CurvStruct->R1.set_size(e_expl_temp.R1.size[0]);
    b_loop_ub = e_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        c_CurvStruct->R1[i1] = e_expl_temp.R1.data[i1];
    }
    c_CurvStruct->delta = e_expl_temp.delta;
    c_CurvStruct->CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    c_CurvStruct->evec[0] = e_expl_temp.evec[0];
    c_CurvStruct->CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    c_CurvStruct->evec[1] = e_expl_temp.evec[1];
    c_CurvStruct->CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    c_CurvStruct->evec[2] = e_expl_temp.evec[2];
    c_CurvStruct->theta = e_expl_temp.theta;
    c_CurvStruct->pitch = e_expl_temp.pitch;
    c_CurvStruct->CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    c_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            c_CurvStruct->CoeffP5[i3 + c_CurvStruct->CoeffP5.size(0) * i2] =
                e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    c_CurvStruct->sp_index = e_expl_temp.sp_index;
    c_CurvStruct->i_begin_sp = e_expl_temp.i_begin_sp;
    c_CurvStruct->i_end_sp = e_expl_temp.i_end_sp;
    c_CurvStruct->index_smooth = e_expl_temp.index_smooth;
    c_CurvStruct->UseConstJerk = e_expl_temp.UseConstJerk;
    c_CurvStruct->ConstJerk = e_expl_temp.ConstJerk;
    c_CurvStruct->Coeff.set_size(e_expl_temp.Coeff.size(0));
    e_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        c_CurvStruct->Coeff[i4] = e_expl_temp.Coeff[i4];
    }
    c_CurvStruct->a_param = e_expl_temp.a_param;
    c_CurvStruct->b_param = e_expl_temp.b_param;
    // 'ReadGCode:20' err_msg         = constrMsgStructType;
    std::copy(&cv1[0], &cv1[2048], &err_msg->msg[0]);
    err_msg->size = 2048.0;
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
    // pathRs274Src); 'ReadGCode:80' coder.updateBuildInfo('addSourceFiles','interp_internal.cc',
    // pathRs274Src); 'ReadGCode:81' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc',
    // pathRs274Src); 'ReadGCode:82' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
    // pathRs274Src); 'ReadGCode:83' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
    // pathRs274Src); 'ReadGCode:84' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
    // pathRs274Src); 'ReadGCode:85' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
    // pathRs274Src); 'ReadGCode:86' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
    // pathRs274Src); 'ReadGCode:87' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
    // pathRs274Src); 'ReadGCode:88' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
    // pathRs274Src); 'ReadGCode:89' coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
    // 'ReadGCode:90' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
    // 'ReadGCode:91' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
    // 'ReadGCode:92' coder.updateBuildInfo('addLinkFlags', '-ldl');
    //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    // 'ReadGCode:94' coder.cinclude('cpp_interp.hpp');
    // 'ReadGCode:96' switch cmd
    if (cmd == ReadGCodeCmd_Load) {
        int f_loop_ub;
        // 'ReadGCode:97' case ReadGCodeCmd.Load
        // 'ReadGCode:98' status = coder.ceval( 'cpp_interp_init', [filename 0], coder.ref(err_msg)
        // );
        f_loop_ub = filename_size[1];
        if (f_loop_ub - 1 >= 0) {
            std::copy(&filename_data[0], &filename_data[f_loop_ub], &tmp_data[0]);
        }
        tmp_data[filename_size[1]] = '\x00';
        b_status = cpp_interp_init(&tmp_data[0], err_msg);
    } else {
        bool is_loaded;
        // 'ReadGCode:99' case ReadGCodeCmd.Read
        // 'ReadGCode:100' is_loaded = false;
        // 'ReadGCode:101' is_loaded = coder.ceval( 'cpp_interp_loaded', coder.ref(err_msg) );
        is_loaded = cpp_interp_loaded(err_msg);
        // 'ReadGCode:102' if is_loaded
        if (is_loaded) {
            // 'ReadGCode:103' status  = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ),
            // coder.ref(err_msg) );
            b_status = cpp_interp_read(c_CurvStruct, err_msg);
        } else {
            // 'ReadGCode:104' else
            // 'ReadGCode:105' status  = ReadGCodeError.InterpError;
            b_status = ReadGCodeError_InterpError;
        }
    }
    // 'ReadGCode:110' if(0)
    // 'ReadGCode:115' ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
    // 'ReadGCode:116'     "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    // 'ReadGCode:117'     err_msg.msg( 1 : err_msg.size ), mfilename );
    if (err_msg->size < 1.0) {
        g_loop_ub = 0;
    } else {
        g_loop_ub = static_cast<int>(err_msg->size);
    }
    resCount = sprintf(&st[0], "%d", c_CurvStruct->Info.gcode_source_line);
    if (resCount - 1 >= 0) {
        std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
    }
    obj.Value.size[0] = 1;
    obj.Value.size[1] = (resCount + g_loop_ub) + 8;
    for (int i5{0}; i5 < 6; i5++) {
        obj.Value.data[i5] = obj1Value[i5];
    }
    if (resCount - 1 >= 0) {
        std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[6]);
    }
    obj.Value.data[resCount + 6] = ']';
    obj.Value.data[resCount + 7] = ' ';
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        obj.Value.data[(i6 + resCount) + 8] = err_msg->msg[i6];
    }
    f_ocn_assert(b_status < ReadGCodeError_InterpNotOpen, &obj);
    *status = b_status;
}

//
// function [ status, CurvStruct, err_msg ] = ReadGCode( cfg, cmd, filename )
//
// ReadGCode : Read the G code contents.
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
//
// Arguments    : ReadGCodeError *status
//                CurvStruct *c_CurvStruct
// Return Type  : void
//
void b_ReadGCode(ReadGCodeError *status, CurvStruct *c_CurvStruct)
{
    static const char obj1Value[6]{'[', 'L', 'i', 'n', 'e', ' '};
    coder::rtString obj;
    Axes params_tool_offset;
    MsgStruct err_msg;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
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
    int f_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int resCount;
    char st[12];
    char obj2Value_data[11];
    bool is_loaded;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ReadGCodeError b_status;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    //  Wrapper for pulling the next gcode line from the interpreter
    // 'ReadGCode:18' status          = ReadGCodeError.InterpError;
    // 'ReadGCode:19' CurvStruct      = constrCurvStructType;
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
    c_CurvStruct->Info = e_expl_temp.Info;
    c_CurvStruct->tool = e_expl_temp.tool;
    c_CurvStruct->sp = e_expl_temp.sp;
    c_CurvStruct->R0.set_size(e_expl_temp.R0.size[0]);
    loop_ub = e_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        c_CurvStruct->R0[i] = e_expl_temp.R0.data[i];
    }
    c_CurvStruct->R1.set_size(e_expl_temp.R1.size[0]);
    b_loop_ub = e_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        c_CurvStruct->R1[i1] = e_expl_temp.R1.data[i1];
    }
    c_CurvStruct->delta = e_expl_temp.delta;
    c_CurvStruct->CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    c_CurvStruct->evec[0] = e_expl_temp.evec[0];
    c_CurvStruct->CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    c_CurvStruct->evec[1] = e_expl_temp.evec[1];
    c_CurvStruct->CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    c_CurvStruct->evec[2] = e_expl_temp.evec[2];
    c_CurvStruct->theta = e_expl_temp.theta;
    c_CurvStruct->pitch = e_expl_temp.pitch;
    c_CurvStruct->CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    c_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            c_CurvStruct->CoeffP5[i3 + c_CurvStruct->CoeffP5.size(0) * i2] =
                e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    c_CurvStruct->sp_index = e_expl_temp.sp_index;
    c_CurvStruct->i_begin_sp = e_expl_temp.i_begin_sp;
    c_CurvStruct->i_end_sp = e_expl_temp.i_end_sp;
    c_CurvStruct->index_smooth = e_expl_temp.index_smooth;
    c_CurvStruct->UseConstJerk = e_expl_temp.UseConstJerk;
    c_CurvStruct->ConstJerk = e_expl_temp.ConstJerk;
    c_CurvStruct->Coeff.set_size(e_expl_temp.Coeff.size(0));
    e_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        c_CurvStruct->Coeff[i4] = e_expl_temp.Coeff[i4];
    }
    c_CurvStruct->a_param = e_expl_temp.a_param;
    c_CurvStruct->b_param = e_expl_temp.b_param;
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
    // pathRs274Src); 'ReadGCode:80' coder.updateBuildInfo('addSourceFiles','interp_internal.cc',
    // pathRs274Src); 'ReadGCode:81' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc',
    // pathRs274Src); 'ReadGCode:82' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
    // pathRs274Src); 'ReadGCode:83' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
    // pathRs274Src); 'ReadGCode:84' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
    // pathRs274Src); 'ReadGCode:85' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
    // pathRs274Src); 'ReadGCode:86' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
    // pathRs274Src); 'ReadGCode:87' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
    // pathRs274Src); 'ReadGCode:88' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
    // pathRs274Src); 'ReadGCode:89' coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
    // 'ReadGCode:90' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
    // 'ReadGCode:91' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
    // 'ReadGCode:92' coder.updateBuildInfo('addLinkFlags', '-ldl');
    //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    // 'ReadGCode:94' coder.cinclude('cpp_interp.hpp');
    // 'ReadGCode:96' switch cmd
    // 'ReadGCode:99' case ReadGCodeCmd.Read
    // 'ReadGCode:100' is_loaded = false;
    // 'ReadGCode:101' is_loaded = coder.ceval( 'cpp_interp_loaded', coder.ref(err_msg) );
    is_loaded = cpp_interp_loaded(&err_msg);
    // 'ReadGCode:102' if is_loaded
    if (is_loaded) {
        // 'ReadGCode:103' status  = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ),
        // coder.ref(err_msg) );
        b_status = cpp_interp_read(c_CurvStruct, &err_msg);
    } else {
        // 'ReadGCode:104' else
        // 'ReadGCode:105' status  = ReadGCodeError.InterpError;
        b_status = ReadGCodeError_InterpError;
    }
    // 'ReadGCode:110' if(0)
    // 'ReadGCode:115' ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
    // 'ReadGCode:116'     "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    // 'ReadGCode:117'     err_msg.msg( 1 : err_msg.size ), mfilename );
    if (err_msg.size < 1.0) {
        f_loop_ub = 0;
    } else {
        f_loop_ub = static_cast<int>(err_msg.size);
    }
    resCount = sprintf(&st[0], "%d", c_CurvStruct->Info.gcode_source_line);
    if (resCount - 1 >= 0) {
        std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
    }
    obj.Value.size[0] = 1;
    obj.Value.size[1] = (resCount + f_loop_ub) + 8;
    for (int i5{0}; i5 < 6; i5++) {
        obj.Value.data[i5] = obj1Value[i5];
    }
    if (resCount - 1 >= 0) {
        std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[6]);
    }
    obj.Value.data[resCount + 6] = ']';
    obj.Value.data[resCount + 7] = ' ';
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        obj.Value.data[(i6 + resCount) + 8] = err_msg.msg[i6];
    }
    f_ocn_assert(b_status < ReadGCodeError_InterpNotOpen, &obj);
    *status = b_status;
}

} // namespace ocn

//
// File trailer for ReadGCode.cpp
//
// [EOF]
//
