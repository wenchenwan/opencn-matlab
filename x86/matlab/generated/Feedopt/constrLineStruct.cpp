
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constrLineStruct.h"
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
// function CStrct = constrLineStruct( gcodeInfoStruct, tool, R0, R1 )
//
// constrLineStruct : Construct a Curv struct filled with the
//  parameters of a Line.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the line P0
//  R1        : Ending pose of the line P0
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const Tool *tool
//                const double R0_data[]
//                const int R0_size[1]
//                const double R1_data[]
//                const int R1_size[1]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0_data[],
                      const int R0_size[1], const double R1_data[], const int R1_size[1],
                      CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
    b_CurvStruct h_expl_temp;
    double b_expl_temp[6];
    double c_expl_temp[6];
    double params_CoeffP5[6];
    double params_Cprim[3];
    double params_evec[3];
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double f_expl_temp;
    double g_expl_temp;
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
    // 'constrLineStruct:12' coder.inline("never");
    // 'constrLineStruct:14' params = paramsDefaultCurv();
    paramsDefaultCurv(&expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC,
                      &expl_temp_FeedRate, &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line,
                      &expl_temp_G91, &expl_temp_G91_1, &expl_temp.toolno, &expl_temp.pocketno,
                      &expl_temp.offset, &expl_temp.diameter, &expl_temp.frontangle,
                      &expl_temp.backangle, &expl_temp.orientation, &params_spline, b_expl_temp,
                      c_expl_temp, params_Cprim, &d_expl_temp, params_evec, &e_expl_temp,
                      &f_expl_temp, params_CoeffP5, &g_expl_temp);
    // 'constrLineStruct:16' gcodeInfoStruct.Type = CurveType.Line;
    gcodeInfoStruct->Type = CurveType_Line;
    // 'constrLineStruct:18' if( coder.target( "MATLAB" ) )
    // 'constrLineStruct:21' else
    // 'constrLineStruct:22' CStrct = constrCurvStruct( gcodeInfoStruct, tool, params.spline, R0,
    // ... 'constrLineStruct:23'                            R1, params.Cprim,params.delta,
    // params.evec, ... 'constrLineStruct:24'                            params.theta, params.pitch,
    // params.CoeffP5, ... 'constrLineStruct:25'                            params.Coeff );
    c_constrCurvStruct(*gcodeInfoStruct, tool, &params_spline, R0_data, R0_size[0], R1_data,
                       R1_size[0], params_Cprim, 0.0, params_evec, 0.0, 0.0, params_CoeffP5,
                       &h_expl_temp);
    CStrct->Info = h_expl_temp.Info;
    CStrct->tool = h_expl_temp.tool;
    CStrct->sp = h_expl_temp.sp;
    CStrct->R0.set_size(h_expl_temp.R0.size[0]);
    loop_ub = h_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = h_expl_temp.R0.data[i];
    }
    CStrct->R1.set_size(h_expl_temp.R1.size[0]);
    b_loop_ub = h_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = h_expl_temp.R1.data[i1];
    }
    CStrct->delta = h_expl_temp.delta;
    CStrct->CorrectedHelixCenter[0] = h_expl_temp.CorrectedHelixCenter[0];
    CStrct->evec[0] = h_expl_temp.evec[0];
    CStrct->CorrectedHelixCenter[1] = h_expl_temp.CorrectedHelixCenter[1];
    CStrct->evec[1] = h_expl_temp.evec[1];
    CStrct->CorrectedHelixCenter[2] = h_expl_temp.CorrectedHelixCenter[2];
    CStrct->evec[2] = h_expl_temp.evec[2];
    CStrct->theta = h_expl_temp.theta;
    CStrct->pitch = h_expl_temp.pitch;
    CStrct->CoeffP5.set_size(h_expl_temp.CoeffP5.size(0), h_expl_temp.CoeffP5.size(1));
    c_loop_ub = h_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = h_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] =
                h_expl_temp.CoeffP5[i3 + h_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = h_expl_temp.sp_index;
    CStrct->i_begin_sp = h_expl_temp.i_begin_sp;
    CStrct->i_end_sp = h_expl_temp.i_end_sp;
    CStrct->index_smooth = h_expl_temp.index_smooth;
    CStrct->UseConstJerk = h_expl_temp.UseConstJerk;
    CStrct->ConstJerk = h_expl_temp.ConstJerk;
    CStrct->Coeff.set_size(h_expl_temp.Coeff.size(0));
    e_loop_ub = h_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->Coeff[i4] = h_expl_temp.Coeff[i4];
    }
    CStrct->a_param = h_expl_temp.a_param;
    CStrct->b_param = h_expl_temp.b_param;
}

} // namespace ocn

//
// File trailer for constrLineStruct.cpp
//
// [EOF]
//
