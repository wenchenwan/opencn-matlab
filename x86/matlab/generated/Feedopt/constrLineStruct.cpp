//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:21:23
//

// Include Files
#include "constrLineStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"

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
//                const double R0[6]
//                const double R1[6]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0[6],
                      const double R1[6], CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
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
    int expl_temp_gcode_source_line;
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
    c_constrCurvStruct(*gcodeInfoStruct, tool, &params_spline, R0, R1, params_Cprim, 0.0,
                       params_evec, 0.0, 0.0, params_CoeffP5, CStrct);
}

} // namespace ocn

//
// File trailer for constrLineStruct.cpp
//
// [EOF]
//
