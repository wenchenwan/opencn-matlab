//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
//

// Include Files
#include "constrCurvStructType.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types31.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"

// Function Definitions
//
// function [ C ] = constrCurvStructType( ~ )
//
// constrCurvStructType : Constructs a constrCurvStruct with default values.
//
// Arguments    : double a__1
//                CurvStruct *C
// Return Type  : void
//
namespace ocn {
void constrCurvStructType(double, CurvStruct *C)
{
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    uint64m_T params_spline_Bl_handle;
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
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:5' [ params ] = paramsDefaultCurv( StructTypeName.MEX );
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
        params_R1, params_Cprim, params_evec, params_CoeffP5, C);
}

} // namespace ocn

//
// File trailer for constrCurvStructType.cpp
//
// [EOF]
//
