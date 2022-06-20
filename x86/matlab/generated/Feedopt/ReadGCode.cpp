//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:55:52
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
#include <algorithm>
#include <emmintrin.h>

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
    double e_expl_temp;
    double expl_temp;
    double f_expl_temp;
    double g_expl_temp;
    double h_expl_temp;
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
    // 'ReadGCode:10' if coder.target('mex')
    // 'ReadGCode:88' elseif coder.target('rtw')
    // 'ReadGCode:90' if cmd == ReadGCodeCmd.Load
    if (cmd == ReadGCodeCmd_Load) {
        int loop_ub;
        // 'ReadGCode:92' CurvStruct = constrCurvStructType;
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff,
                          params_spline_Bl_breakpoints, &params_spline_Bl_handle,
                          &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                          &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                          &expl_temp, params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5,
                          &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline,
        // ... 'constrCurvStructType:14'         params.R0, params.R1, ... 'constrCurvStructType:15'
        // params.Cprim, params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
        // params.pitch, params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
                           params_spline_Bl_breakpoints, params_spline_Bl_handle,
                           params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                           params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                           params_evec, params_CoeffP5, b_CurvStruct);
        // 'ReadGCode:93' status = int32( 0 );
        // 'ReadGCode:94' status = coder.ceval( 'c_open_gcode', [filename, 0], coder.ref( CurvStruct
        // ) );
        loop_ub = filename_size[1];
        if (0 <= loop_ub - 1) {
            std::copy(&filename_data[0], &filename_data[loop_ub], &tmp_data[0]);
        }
        tmp_data[filename_size[1]] = '\x00';
        b_status = c_open_gcode(&tmp_data[0], b_CurvStruct);
    } else {
        __m128d r;
        __m128d r1;
        __m128d r2;
        // 'ReadGCode:95' elseif cmd == ReadGCodeCmd.Read
        // 'ReadGCode:97' CurvStruct = constrCurvStructType;
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff,
                          params_spline_Bl_breakpoints, &params_spline_Bl_handle,
                          &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                          &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                          &e_expl_temp, params_evec, &f_expl_temp, &g_expl_temp, params_CoeffP5,
                          &h_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline,
        // ... 'constrCurvStructType:14'         params.R0, params.R1, ... 'constrCurvStructType:15'
        // params.Cprim, params.delta, params.evec, params.theta, ... 'constrCurvStructType:16'
        // params.pitch, params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
                           params_spline_Bl_breakpoints, params_spline_Bl_handle,
                           params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                           params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim,
                           params_evec, params_CoeffP5, b_CurvStruct);
        // 'ReadGCode:98' status = int32( 0 );
        // 'ReadGCode:99' status = coder.ceval( 'c_read_and_exec_gcode', '', coder.ref( CurvStruct )
        // );
        b_status = c_read_and_exec_gcode(nullptr, b_CurvStruct);
        // 'ReadGCode:100' CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
        // 'ReadGCode:101' CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
        r = _mm_loadu_pd(&b_CurvStruct->R0[3]);
        r1 = _mm_set1_pd(0.017453292519943295);
        _mm_storeu_pd(&b_CurvStruct->R0[3], _mm_mul_pd(r1, r));
        r2 = _mm_loadu_pd(&b_CurvStruct->R1[3]);
        _mm_storeu_pd(&b_CurvStruct->R1[3], _mm_mul_pd(r1, r2));
        b_CurvStruct->R0[5] *= 0.017453292519943295;
        b_CurvStruct->R1[5] *= 0.017453292519943295;
    }
    *status = b_status;
}

} // namespace ocn

//
// File trailer for ReadGCode.cpp
//
// [EOF]
//
