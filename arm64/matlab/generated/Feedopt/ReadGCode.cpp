//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

// Include Files
#include "ReadGCode.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"
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
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
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
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    int b_status;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
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
    // 'ReadGCode:7' status = int32(0);
    // 'ReadGCode:8' CurvStruct = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
        &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
        &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
        &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
        &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
        &params_spline_Bl_handle, &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
        &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim, &expl_temp,
        params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode, params_gcodeInfoStruct_TRAFO,
        params_gcodeInfoStruct_HSC, params_gcodeInfoStruct_FeedRate,
        params_gcodeInfoStruct_SpindleSpeed, params_gcodeInfoStruct_gcode_source_line,
        params_gcodeInfoStruct_G91, params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
        params_spline_Bl_breakpoints, params_spline_Bl_handle, params_spline_Bl_order,
        params_spline_coeff, params_spline_knots, params_spline_Ltot, params_spline_Lk, params_R0,
        params_R1, params_Cprim, params_evec, params_CoeffP5, b_CurvStruct);
    // 'ReadGCode:10' if ( coder.target('mex') || coder.target('rtw') )
    // 'ReadGCode:11' coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
    // 'ReadGCode:13' pathRs274Src = '$(START_DIR)/../../rs274ngc/src';
    //      coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
    // 'ReadGCode:15' coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
    // 'ReadGCode:16' coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp',
    // '$(START_DIR)/../common/src'); 'ReadGCode:17'
    // coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src); 'ReadGCode:18'
    // coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc', pathRs274Src);
    // 'ReadGCode:19' coder.updateBuildInfo('addSourceFiles','interp_arc.cc', pathRs274Src);
    // 'ReadGCode:20' coder.updateBuildInfo('addSourceFiles','interp_array.cc', pathRs274Src);
    // 'ReadGCode:21' coder.updateBuildInfo('addSourceFiles','interp_base.cc', pathRs274Src);
    // 'ReadGCode:22' coder.updateBuildInfo('addSourceFiles','interp_check.cc', pathRs274Src);
    // 'ReadGCode:23' coder.updateBuildInfo('addSourceFiles','interp_convert.cc', pathRs274Src);
    // 'ReadGCode:24' coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', pathRs274Src);
    // 'ReadGCode:25' coder.updateBuildInfo('addSourceFiles','interp_execute.cc', pathRs274Src);
    // 'ReadGCode:26' coder.updateBuildInfo('addSourceFiles','interp_find.cc', pathRs274Src);
    // 'ReadGCode:27' coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
    // 'ReadGCode:28' coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
    // 'ReadGCode:29' coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc', pathRs274Src);
    // 'ReadGCode:30' coder.updateBuildInfo('addSourceFiles','interp_o_word.cc', pathRs274Src);
    // 'ReadGCode:31' coder.updateBuildInfo('addSourceFiles','interp_queue.cc', pathRs274Src);
    // 'ReadGCode:32' coder.updateBuildInfo('addSourceFiles','interp_read.cc', pathRs274Src);
    // 'ReadGCode:33' coder.updateBuildInfo('addSourceFiles','interp_remap.cc', pathRs274Src);
    // 'ReadGCode:34' coder.updateBuildInfo('addSourceFiles','interp_setup.cc', pathRs274Src);
    // 'ReadGCode:35' coder.updateBuildInfo('addSourceFiles','interp_write.cc', pathRs274Src);
    // 'ReadGCode:36' coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
    // 'ReadGCode:37' coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
    // 'ReadGCode:38' coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
    // 'ReadGCode:39' coder.updateBuildInfo('addLinkFlags', '-ldl');
    //     coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    // 'ReadGCode:41' coder.cinclude('cpp_interp.hpp');
    // 'ReadGCode:43' switch cmd
    if (cmd == ReadGCodeCmd_Load) {
        int loop_ub;
        // 'ReadGCode:44' case ReadGCodeCmd.Load
        // 'ReadGCode:45' status = coder.ceval( 'cpp_interp_init', [filename 0] );
        loop_ub = filename_size[1];
        if (0 <= loop_ub - 1) {
            std::copy(&filename_data[0], &filename_data[loop_ub], &tmp_data[0]);
        }
        tmp_data[filename_size[1]] = '\x00';
        b_status = cpp_interp_init(&tmp_data[0]);
    } else {
        int is_loaded;
        // 'ReadGCode:46' case ReadGCodeCmd.Read
        // 'ReadGCode:47' is_loaded = int32(0);
        // 'ReadGCode:48' is_loaded = coder.ceval( 'cpp_interp_loaded' );
        is_loaded = cpp_interp_loaded();
        // 'ReadGCode:49' if is_loaded
        if (is_loaded != 0) {
            // 'ReadGCode:50' status = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ) );
            b_status = cpp_interp_read(b_CurvStruct);
            // 'ReadGCode:51' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            // 'ReadGCode:52' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
            b_CurvStruct->R0[3] *= 0.017453292519943295;
            b_CurvStruct->R1[3] *= 0.017453292519943295;
            b_CurvStruct->R0[4] *= 0.017453292519943295;
            b_CurvStruct->R1[4] *= 0.017453292519943295;
            b_CurvStruct->R0[5] *= 0.017453292519943295;
            b_CurvStruct->R1[5] *= 0.017453292519943295;
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
