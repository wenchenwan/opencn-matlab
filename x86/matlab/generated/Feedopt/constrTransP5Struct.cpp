//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
//

// Include Files
#include "constrTransP5Struct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"

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
//                const double R0[6]
//                const double R1[6]
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
                           double tool_backangle, int tool_orientation, const double R0[6],
                           const double R1[6], const double CoeffP5[6][6], CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
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
    int expl_temp_gcode_source_line;
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
    d_constrCurvStruct(gcodeInfoStruct_TRAFO, gcodeInfoStruct_HSC, gcodeInfoStruct_FeedRate,
                       gcodeInfoStruct_SpindleSpeed, gcodeInfoStruct_gcode_source_line,
                       gcodeInfoStruct_G91, gcodeInfoStruct_G91_1, tool_toolno, tool_pocketno,
                       tool_offset, tool_diameter, tool_frontangle, tool_backangle,
                       tool_orientation, &params_spline, R0, R1, params_Cprim, params_evec, CoeffP5,
                       CStrct);
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
//                const double R0[6]
//                const double R1[6]
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0[6],
                         const double R1[6], const ::coder::array<double, 2U> &CoeffP5,
                         CurvStruct *CStrct)
{
    SplineStruct params_spline;
    Tool expl_temp;
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
    c_constrCurvStruct(*gcodeInfoStruct, tool, &params_spline, R0, R1, params_Cprim, params_evec,
                       CoeffP5, CStrct);
}

} // namespace ocn

//
// File trailer for constrTransP5Struct.cpp
//
// [EOF]
//
