
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStructType.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constrCurvStructType.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

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
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
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
    C->Info = e_expl_temp.Info;
    C->tool = e_expl_temp.tool;
    C->sp = e_expl_temp.sp;
    C->R0.set_size(e_expl_temp.R0.size[0]);
    loop_ub = e_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        C->R0[i] = e_expl_temp.R0.data[i];
    }
    C->R1.set_size(e_expl_temp.R1.size[0]);
    b_loop_ub = e_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        C->R1[i1] = e_expl_temp.R1.data[i1];
    }
    C->delta = e_expl_temp.delta;
    C->CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    C->evec[0] = e_expl_temp.evec[0];
    C->CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    C->evec[1] = e_expl_temp.evec[1];
    C->CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    C->evec[2] = e_expl_temp.evec[2];
    C->theta = e_expl_temp.theta;
    C->pitch = e_expl_temp.pitch;
    C->CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    c_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            C->CoeffP5[i3 + C->CoeffP5.size(0) * i2] =
                e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    C->sp_index = e_expl_temp.sp_index;
    C->i_begin_sp = e_expl_temp.i_begin_sp;
    C->i_end_sp = e_expl_temp.i_end_sp;
    C->index_smooth = e_expl_temp.index_smooth;
    C->UseConstJerk = e_expl_temp.UseConstJerk;
    C->ConstJerk = e_expl_temp.ConstJerk;
    C->Coeff.set_size(e_expl_temp.Coeff.size(0));
    e_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        C->Coeff[i4] = e_expl_temp.Coeff[i4];
    }
    C->a_param = e_expl_temp.a_param;
    C->b_param = e_expl_temp.b_param;
}

} // namespace ocn

//
// File trailer for constrCurvStructType.cpp
//
// [EOF]
//
