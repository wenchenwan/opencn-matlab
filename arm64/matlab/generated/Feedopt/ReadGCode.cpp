//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
//

// Include Files
#include "ReadGCode.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "cpp_interp.hpp"
#include <algorithm>

// Function Definitions
//
// function [ status, CurvStruct ] = ReadGCode( cmd, filename )
//
// coder.extrinsic('ReadGCode_mex');
//  Wrapper for pulling the next gcode line from the interpreter
//
// Arguments    : ReadGCodeCmd cmd
//                const char filename_data[]
//                const int filename_size[2]
//                int *status
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ReadGCode(ReadGCodeCmd cmd, const char filename_data[], const int filename_size[2],
               int *status, CurvStruct *b_CurvStruct)
{
    Axes params_tool_offset;
    SplineStruct params_spline;
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
    int b_status;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    char tmp_data[1025];
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ReadGCode:6' status      = int32(0);
    // 'ReadGCode:7' CurvStruct  = constrCurvStructType;
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
                       params_R1, params_Cprim, params_evec, params_CoeffP5, b_CurvStruct);
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
    // pathRs274Src); 'ReadGCode:29' coder.updateBuildInfo('addSourceFiles','interp_internal.cc',
    // pathRs274Src); 'ReadGCode:30' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc',
    // pathRs274Src); 'ReadGCode:31' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc',
    // pathRs274Src); 'ReadGCode:32' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc',
    // pathRs274Src); 'ReadGCode:33' coder.updateBuildInfo('addSourceFiles','interp_queue.cc',
    // pathRs274Src); 'ReadGCode:34' coder.updateBuildInfo('addSourceFiles','interp_read.cc',
    // pathRs274Src); 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','interp_remap.cc',
    // pathRs274Src); 'ReadGCode:36' coder.updateBuildInfo('addSourceFiles','interp_setup.cc',
    // pathRs274Src); 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','interp_write.cc',
    // pathRs274Src); 'ReadGCode:38' coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
    // 'ReadGCode:39' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
    // 'ReadGCode:40' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
    // 'ReadGCode:41' coder.updateBuildInfo('addLinkFlags', '-ldl');
    //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    // 'ReadGCode:43' coder.cinclude('cpp_interp.hpp');
    // 'ReadGCode:45' switch cmd
    if (cmd == ReadGCodeCmd_Load) {
        int loop_ub;
        // 'ReadGCode:46' case ReadGCodeCmd.Load
        // 'ReadGCode:47' status = coder.ceval( 'cpp_interp_init', [filename 0] );
        loop_ub = filename_size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&filename_data[0], &filename_data[loop_ub], &tmp_data[0]);
        }
        tmp_data[filename_size[1]] = '\x00';
        b_status = cpp_interp_init(&tmp_data[0]);
    } else {
        int is_loaded;
        // 'ReadGCode:48' case ReadGCodeCmd.Read
        // 'ReadGCode:49' is_loaded = int32(0);
        // 'ReadGCode:50' is_loaded = coder.ceval( 'cpp_interp_loaded' );
        is_loaded = cpp_interp_loaded();
        // 'ReadGCode:51' if is_loaded
        if (is_loaded != 0) {
            // 'ReadGCode:52' status = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ) );
            b_status = cpp_interp_read(b_CurvStruct);
        } else {
            // 'ReadGCode:53' else
            // 'ReadGCode:54' status = int32(0);
            b_status = 0;
        }
    }
    *status = b_status;
}

} // namespace ocn

//
// File trailer for ReadGCode.cpp
//
// [EOF]
//
