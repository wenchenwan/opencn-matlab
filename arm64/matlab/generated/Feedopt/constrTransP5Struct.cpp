//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 16:00:50
//

// Include Files
#include "constrTransP5Struct.h"
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
// function CStrct = constrTransP5Struct( gcodeInfoStruct, R0, R1, CoeffP5 )
//
// constrTransP5Struct : Construct a Curv struct filled with the
//  parameters of a hermite polynom used for the transitions.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  CoeffP5   : Coefficient of the 5th order polynom
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
//                const double R0[6]
//                const double R1[6]
//                const double CoeffP5[6][5]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void b_constrTransP5Struct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                           bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                           double gcodeInfoStruct_SpindleSpeed,
                           int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                           bool gcodeInfoStruct_G91_1, const double R0[6], const double R1[6],
                           const double CoeffP5[6][5], CurvStruct *CStrct)
{
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    double b_expl_temp[6];
    double expl_temp[6];
    double f_expl_temp[6];
    double params_Cprim[3];
    double params_evec[3];
    double c_expl_temp;
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double g_expl_temp;
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    int expl_temp_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    bool expl_temp_G91;
    bool expl_temp_G91_1;
    bool expl_temp_HSC;
    bool expl_temp_TRAFO;
    CurveType expl_temp_Type;
    ZSpdMode expl_temp_zspdmode;
    // 'constrTransP5Struct:13' coder.inline( "never" );
    // 'constrTransP5Struct:15' params = paramsDefaultCurv;
    paramsDefaultCurv(
        &expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC, &expl_temp_FeedRate,
        &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line, &expl_temp_G91, &expl_temp_G91_1,
        &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints, &params_spline_Bl_handle,
        &params_spline_Bl_order, params_spline_coeff, params_spline_knots, &params_spline_Ltot,
        params_spline_Lk, expl_temp, b_expl_temp, params_Cprim, &c_expl_temp, params_evec,
        &d_expl_temp, &e_expl_temp, f_expl_temp, &g_expl_temp);
    // 'constrTransP5Struct:17' gcodeInfoStruct.Type = CurveType.TransP5;
    // 'constrTransP5Struct:19' if( coder.target( "MATLAB" ) )
    // 'constrTransP5Struct:22' else
    // 'constrTransP5Struct:23' CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1,
    // ... 'constrTransP5Struct:24'                            params.Cprim, ...
    // 'constrTransP5Struct:25'                            params.delta, params.evec, params.theta,
    // ... 'constrTransP5Struct:26'                            params.pitch, CoeffP5, params.Coeff
    // );
    d_constrCurvStruct(gcodeInfoStruct_zspdmode, gcodeInfoStruct_TRAFO, gcodeInfoStruct_HSC,
                       gcodeInfoStruct_FeedRate, gcodeInfoStruct_SpindleSpeed,
                       gcodeInfoStruct_gcode_source_line, gcodeInfoStruct_G91,
                       gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
                       params_spline_Bl_handle, params_spline_Bl_order, params_spline_coeff,
                       params_spline_knots, params_spline_Ltot, params_spline_Lk, R0, R1,
                       params_Cprim, params_evec, CoeffP5, CStrct);
}

//
// function CStrct = constrTransP5Struct( gcodeInfoStruct, R0, R1, CoeffP5 )
//
// constrTransP5Struct : Construct a Curv struct filled with the
//  parameters of a hermite polynom used for the transitions.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const double R0[6]
//                const double R1[6]
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct, const double R0[6], const double R1[6],
                         const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    double b_expl_temp[6];
    double expl_temp[6];
    double f_expl_temp[6];
    double params_Cprim[3];
    double params_evec[3];
    double c_expl_temp;
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double g_expl_temp;
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    int expl_temp_gcode_source_line;
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
    // 'constrTransP5Struct:13' coder.inline( "never" );
    // 'constrTransP5Struct:15' params = paramsDefaultCurv;
    paramsDefaultCurv(
        &expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC, &expl_temp_FeedRate,
        &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line, &expl_temp_G91, &expl_temp_G91_1,
        &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints, &params_spline_Bl_handle,
        &params_spline_Bl_order, params_spline_coeff, params_spline_knots, &params_spline_Ltot,
        params_spline_Lk, expl_temp, b_expl_temp, params_Cprim, &c_expl_temp, params_evec,
        &d_expl_temp, &e_expl_temp, f_expl_temp, &g_expl_temp);
    // 'constrTransP5Struct:17' gcodeInfoStruct.Type = CurveType.TransP5;
    gcodeInfoStruct->Type = CurveType_TransP5;
    // 'constrTransP5Struct:19' if( coder.target( "MATLAB" ) )
    // 'constrTransP5Struct:22' else
    // 'constrTransP5Struct:23' CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1,
    // ... 'constrTransP5Struct:24'                            params.Cprim, ...
    // 'constrTransP5Struct:25'                            params.delta, params.evec, params.theta,
    // ... 'constrTransP5Struct:26'                            params.pitch, CoeffP5, params.Coeff
    // );
    c_constrCurvStruct(*gcodeInfoStruct, params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
                       params_spline_Bl_handle, params_spline_Bl_order, params_spline_coeff,
                       params_spline_knots, params_spline_Ltot, params_spline_Lk, R0, R1,
                       params_Cprim, params_evec, CoeffP5, CStrct);
}

} // namespace ocn

//
// File trailer for constrTransP5Struct.cpp
//
// [EOF]
//
