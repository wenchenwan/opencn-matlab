
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constrTransP5Struct.h"
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
// function CStrct = constrTransP5Struct( gcodeInfoStruct, tool, R0, R1, ...
//                                       CoeffP5 )
//
// constrTransP5Struct : Construct a Curv struct filled with the
//  parameters of a hermite polynom used for the transitions.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : bool gcodeInfoStruct_TRAFO
//                bool gcodeInfoStruct_HSC
//                double gcodeInfoStruct_FeedRate
//                double gcodeInfoStruct_SpindleSpeed
//                int gcodeInfoStruct_gcode_source_line
//                bool gcodeInfoStruct_G91
//                bool gcodeInfoStruct_G91_1
//                int tool_toolno
//                int tool_pocketno
//                const Axes *tool_offset
//                double tool_diameter
//                double tool_frontangle
//                double tool_backangle
//                int tool_orientation
//                const double R0_data[]
//                int R0_size
//                const double R1_data[]
//                int R1_size
//                const double CoeffP5[6][6]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void b_constrTransP5Struct(bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                           double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                           int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                           bool gcodeInfoStruct_G91_1, int tool_toolno, int tool_pocketno,
                           const Axes *tool_offset, double tool_diameter, double tool_frontangle,
                           double tool_backangle, int tool_orientation, const double R0_data[],
                           int R0_size, const double R1_data[], int R1_size,
                           const double CoeffP5[6][6], CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
    b_CurvStruct i_expl_temp;
    double b_expl_temp[6];
    double c_expl_temp[6];
    double g_expl_temp[6];
    double params_Cprim[3];
    double params_evec[3];
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double f_expl_temp;
    double h_expl_temp;
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int expl_temp_gcode_source_line;
    int loop_ub;
    bool expl_temp_G91;
    bool expl_temp_G91_1;
    bool expl_temp_HSC;
    bool expl_temp_TRAFO;
    CurveType expl_temp_Type;
    ZSpdMode expl_temp_zspdmode;
    // 'constrTransP5Struct:15' coder.inline( "never" );
    // 'constrTransP5Struct:17' params = paramsDefaultCurv;
    paramsDefaultCurv(&expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC,
                      &expl_temp_FeedRate, &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line,
                      &expl_temp_G91, &expl_temp_G91_1, &expl_temp.toolno, &expl_temp.pocketno,
                      &expl_temp.offset, &expl_temp.diameter, &expl_temp.frontangle,
                      &expl_temp.backangle, &expl_temp.orientation, &params_spline, b_expl_temp,
                      c_expl_temp, params_Cprim, &d_expl_temp, params_evec, &e_expl_temp,
                      &f_expl_temp, g_expl_temp, &h_expl_temp);
    // 'constrTransP5Struct:19' gcodeInfoStruct.Type = CurveType.TransP5;
    // 'constrTransP5Struct:20' gcodeInfoStruct.zspdmode = ZSpdMode.NN;
    // 'constrTransP5Struct:22' if( coder.target( "MATLAB" ) )
    // 'constrTransP5Struct:26' else
    // 'constrTransP5Struct:27' CStrct = constrCurvStruct( gcodeInfoStruct, tool, params.spline, R0,
    // ... 'constrTransP5Struct:28'                             R1, params.Cprim, params.delta,
    // params.evec, ... 'constrTransP5Struct:29'                             params.theta,
    // params.pitch, CoeffP5, ... 'constrTransP5Struct:30'                             params.Coeff
    // );
    f_constrCurvStruct(gcodeInfoStruct_TRAFO, gcodeInfoStruct_HSC, gcodeInfoStruct_FeedRate,
                       gcodeInfoStruct_SpindleSpeed, gcodeInfoStruct_gcode_source_line,
                       gcodeInfoStruct_G91, gcodeInfoStruct_G91_1, tool_toolno, tool_pocketno,
                       tool_offset, tool_diameter, tool_frontangle, tool_backangle,
                       tool_orientation, &params_spline, R0_data, R0_size, R1_data, R1_size,
                       params_Cprim, params_evec, CoeffP5, &i_expl_temp);
    CStrct->Info = i_expl_temp.Info;
    CStrct->tool = i_expl_temp.tool;
    CStrct->sp = i_expl_temp.sp;
    CStrct->R0.set_size(i_expl_temp.R0.size[0]);
    loop_ub = i_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = i_expl_temp.R0.data[i];
    }
    CStrct->R1.set_size(i_expl_temp.R1.size[0]);
    b_loop_ub = i_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = i_expl_temp.R1.data[i1];
    }
    CStrct->delta = i_expl_temp.delta;
    CStrct->CorrectedHelixCenter[0] = i_expl_temp.CorrectedHelixCenter[0];
    CStrct->evec[0] = i_expl_temp.evec[0];
    CStrct->CorrectedHelixCenter[1] = i_expl_temp.CorrectedHelixCenter[1];
    CStrct->evec[1] = i_expl_temp.evec[1];
    CStrct->CorrectedHelixCenter[2] = i_expl_temp.CorrectedHelixCenter[2];
    CStrct->evec[2] = i_expl_temp.evec[2];
    CStrct->theta = i_expl_temp.theta;
    CStrct->pitch = i_expl_temp.pitch;
    CStrct->CoeffP5.set_size(i_expl_temp.CoeffP5.size(0), i_expl_temp.CoeffP5.size(1));
    c_loop_ub = i_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = i_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] =
                i_expl_temp.CoeffP5[i3 + i_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = i_expl_temp.sp_index;
    CStrct->i_begin_sp = i_expl_temp.i_begin_sp;
    CStrct->i_end_sp = i_expl_temp.i_end_sp;
    CStrct->index_smooth = i_expl_temp.index_smooth;
    CStrct->UseConstJerk = i_expl_temp.UseConstJerk;
    CStrct->ConstJerk = i_expl_temp.ConstJerk;
    CStrct->Coeff.set_size(i_expl_temp.Coeff.size(0));
    e_loop_ub = i_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->Coeff[i4] = i_expl_temp.Coeff[i4];
    }
    CStrct->a_param = i_expl_temp.a_param;
    CStrct->b_param = i_expl_temp.b_param;
}

//
// function CStrct = constrTransP5Struct( gcodeInfoStruct, tool, R0, R1, ...
//                                       CoeffP5 )
//
// constrTransP5Struct : Construct a Curv struct filled with the
//  parameters of a hermite polynom used for the transitions.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const Tool *tool
//                const double R0_data[]
//                const int R0_size[1]
//                const double R1_data[]
//                const int R1_size[1]
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0_data[],
                         const int R0_size[1], const double R1_data[], const int R1_size[1],
                         const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
    b_CurvStruct i_expl_temp;
    double b_expl_temp[6];
    double c_expl_temp[6];
    double g_expl_temp[6];
    double params_Cprim[3];
    double params_evec[3];
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double f_expl_temp;
    double h_expl_temp;
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int expl_temp_gcode_source_line;
    int loop_ub;
    bool expl_temp_G91;
    bool expl_temp_G91_1;
    bool expl_temp_HSC;
    bool expl_temp_TRAFO;
    CurveType expl_temp_Type;
    ZSpdMode expl_temp_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrTransP5Struct:15' coder.inline( "never" );
    // 'constrTransP5Struct:17' params = paramsDefaultCurv;
    paramsDefaultCurv(&expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC,
                      &expl_temp_FeedRate, &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line,
                      &expl_temp_G91, &expl_temp_G91_1, &expl_temp.toolno, &expl_temp.pocketno,
                      &expl_temp.offset, &expl_temp.diameter, &expl_temp.frontangle,
                      &expl_temp.backangle, &expl_temp.orientation, &params_spline, b_expl_temp,
                      c_expl_temp, params_Cprim, &d_expl_temp, params_evec, &e_expl_temp,
                      &f_expl_temp, g_expl_temp, &h_expl_temp);
    // 'constrTransP5Struct:19' gcodeInfoStruct.Type = CurveType.TransP5;
    gcodeInfoStruct->Type = CurveType_TransP5;
    // 'constrTransP5Struct:20' gcodeInfoStruct.zspdmode = ZSpdMode.NN;
    gcodeInfoStruct->zspdmode = ZSpdMode_NN;
    // 'constrTransP5Struct:22' if( coder.target( "MATLAB" ) )
    // 'constrTransP5Struct:26' else
    // 'constrTransP5Struct:27' CStrct = constrCurvStruct( gcodeInfoStruct, tool, params.spline, R0,
    // ... 'constrTransP5Struct:28'                             R1, params.Cprim, params.delta,
    // params.evec, ... 'constrTransP5Struct:29'                             params.theta,
    // params.pitch, CoeffP5, ... 'constrTransP5Struct:30'                             params.Coeff
    // );
    c_constrCurvStruct(*gcodeInfoStruct, tool, &params_spline, R0_data, R0_size[0], R1_data,
                       R1_size[0], params_Cprim, params_evec, CoeffP5, &i_expl_temp);
    CStrct->Info = i_expl_temp.Info;
    CStrct->tool = i_expl_temp.tool;
    CStrct->sp = i_expl_temp.sp;
    CStrct->R0.set_size(i_expl_temp.R0.size[0]);
    loop_ub = i_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = i_expl_temp.R0.data[i];
    }
    CStrct->R1.set_size(i_expl_temp.R1.size[0]);
    b_loop_ub = i_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = i_expl_temp.R1.data[i1];
    }
    CStrct->delta = i_expl_temp.delta;
    CStrct->CorrectedHelixCenter[0] = i_expl_temp.CorrectedHelixCenter[0];
    CStrct->evec[0] = i_expl_temp.evec[0];
    CStrct->CorrectedHelixCenter[1] = i_expl_temp.CorrectedHelixCenter[1];
    CStrct->evec[1] = i_expl_temp.evec[1];
    CStrct->CorrectedHelixCenter[2] = i_expl_temp.CorrectedHelixCenter[2];
    CStrct->evec[2] = i_expl_temp.evec[2];
    CStrct->theta = i_expl_temp.theta;
    CStrct->pitch = i_expl_temp.pitch;
    CStrct->CoeffP5.set_size(i_expl_temp.CoeffP5.size(0), i_expl_temp.CoeffP5.size(1));
    c_loop_ub = i_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = i_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] =
                i_expl_temp.CoeffP5[i3 + i_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = i_expl_temp.sp_index;
    CStrct->i_begin_sp = i_expl_temp.i_begin_sp;
    CStrct->i_end_sp = i_expl_temp.i_end_sp;
    CStrct->index_smooth = i_expl_temp.index_smooth;
    CStrct->UseConstJerk = i_expl_temp.UseConstJerk;
    CStrct->ConstJerk = i_expl_temp.ConstJerk;
    CStrct->Coeff.set_size(i_expl_temp.Coeff.size(0));
    e_loop_ub = i_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->Coeff[i4] = i_expl_temp.Coeff[i4];
    }
    CStrct->a_param = i_expl_temp.a_param;
    CStrct->b_param = i_expl_temp.b_param;
}

} // namespace ocn

//
// File trailer for constrTransP5Struct.cpp
//
// [EOF]
//
