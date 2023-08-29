//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSplineStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

// Include Files
#include "constrSplineStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"

// Function Definitions
//
// function CStrct = constrSplineStruct( gcodeInfoStruct, tool, R0, R1, ...
//                                     sp_index )
//
// constrSplineStruct : Construct a Curv struct filled with the
//  parameters of a Spline.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the spline P0
//  R1        : Ending pose of the spline P0
//  sp_index  : Index of the refrence spline
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : ZSpdMode gcodeInfoStruct_zspdmode
//                bool gcodeInfoStruct_TRAFO
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
//                unsigned int sp_index
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrSplineStruct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                        bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                        double gcodeInfoStruct_SpindleSpeed, int gcodeInfoStruct_gcode_source_line,
                        bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, int tool_toolno,
                        int tool_pocketno, const Axes *tool_offset, double tool_diameter,
                        double tool_frontangle, double tool_backangle, int tool_orientation,
                        const double R0[6], const double R1[6], unsigned int sp_index,
                        CurvStruct *CStrct)
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
    // 'constrSplineStruct:14' coder.inline("never");
    // 'constrSplineStruct:16' params = paramsDefaultCurv();
    paramsDefaultCurv(&expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC,
                      &expl_temp_FeedRate, &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line,
                      &expl_temp_G91, &expl_temp_G91_1, &expl_temp.toolno, &expl_temp.pocketno,
                      &expl_temp.offset, &expl_temp.diameter, &expl_temp.frontangle,
                      &expl_temp.backangle, &expl_temp.orientation, &params_spline, b_expl_temp,
                      c_expl_temp, params_Cprim, &d_expl_temp, params_evec, &e_expl_temp,
                      &f_expl_temp, params_CoeffP5, &g_expl_temp);
    //  params{11} = sp_index;
    // 'constrSplineStruct:18' gcodeInfoStruct.Type = CurveType.Spline;
    //  gcodeInfoStruct.sp_index = sp_index;
    // 'constrSplineStruct:21' if( coder.target( "MATLAB" ) )
    // 'constrSplineStruct:25' else
    // 'constrSplineStruct:26' CStrct = constrCurvStruct( gcodeInfoStruct, tool, params.spline, R0,
    // ... 'constrSplineStruct:27'                            R1, params.Cprim, params.delta,
    // params.evec, ... 'constrSplineStruct:28'                            params.theta,
    // params.pitch, params.CoeffP5, ... 'constrSplineStruct:29' params.Coeff );
    b_constrCurvStruct(CurveType_Spline, gcodeInfoStruct_zspdmode, gcodeInfoStruct_TRAFO,
                       gcodeInfoStruct_HSC, gcodeInfoStruct_FeedRate, gcodeInfoStruct_SpindleSpeed,
                       gcodeInfoStruct_gcode_source_line, gcodeInfoStruct_G91,
                       gcodeInfoStruct_G91_1, tool_toolno, tool_pocketno, tool_offset,
                       tool_diameter, tool_frontangle, tool_backangle, tool_orientation,
                       &params_spline, R0, R1, params_Cprim, params_evec, params_CoeffP5, CStrct);
    // 'constrSplineStruct:30' CStrct.sp_index = uint32( sp_index );
    CStrct->sp_index = sp_index;
}

} // namespace ocn

//
// File trailer for constrSplineStruct.cpp
//
// [EOF]
//
