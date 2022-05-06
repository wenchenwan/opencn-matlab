//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 06-May-2022 16:41:55
//

// Include Files
#include "constrLineStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = constrLineStruct( gcodeInfoStruct, R0, R1 )
//
// constrLineStruct : Construct a Curv struct filled with the
//  parameters of a Line.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the line P0
//  R1        : Ending pose of the line P0
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const double R0[6]
//                const double R1[6]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const double R0[6], const double R1[6],
                      CurvStruct *CStrct)
{
    SplineStruct expl_temp;
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
    double params_spline_Ltot;
    unsigned long expl_temp_gcode_source_line;
    unsigned long params_spline_Bl_handle;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    bool expl_temp_G91;
    bool expl_temp_G91_1;
    bool expl_temp_HSC;
    bool expl_temp_TRAFO;
    CurveType expl_temp_Type;
    ZSpdMode expl_temp_zspdmode;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrLineStruct:11' coder.inline("never");
    // 'constrLineStruct:13' params = paramsDefaultCurv();
    paramsDefaultCurv(&expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC,
                      &expl_temp_FeedRate, &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line,
                      &expl_temp_G91, &expl_temp_G91_1, &params_spline_Bl_ncoeff,
                      expl_temp.Bl.breakpoints, &params_spline_Bl_handle, &params_spline_Bl_order,
                      expl_temp.coeff, expl_temp.knots, &params_spline_Ltot, expl_temp.Lk,
                      b_expl_temp, c_expl_temp, params_Cprim, &d_expl_temp, params_evec,
                      &e_expl_temp, &f_expl_temp, params_CoeffP5, &g_expl_temp);
    // 'constrLineStruct:15' gcodeInfoStruct.Type = CurveType.Line;
    gcodeInfoStruct->Type = CurveType_Line;
    // 'constrLineStruct:17' if( coder.target( "MATLAB" ) )
    // 'constrLineStruct:20' else
    // 'constrLineStruct:21' CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1, ...
    // 'constrLineStruct:22'                            params.Cprim, ...
    // 'constrLineStruct:23'                            params.delta, params.evec, params.theta, ...
    // 'constrLineStruct:24'                            params.pitch, params.CoeffP5, params.Coeff
    // );
    expl_temp.Ltot = params_spline_Ltot;
    expl_temp.Bl.ncoeff = params_spline_Bl_ncoeff;
    expl_temp.Bl.handle = params_spline_Bl_handle;
    expl_temp.Bl.order = params_spline_Bl_order;
    c_constrCurvStruct(*gcodeInfoStruct, &expl_temp, R0, R1, params_Cprim, 0.0, params_evec, 0.0,
                       0.0, params_CoeffP5, CStrct);
}

} // namespace ocn

//
// File trailer for constrLineStruct.cpp
//
// [EOF]
//
