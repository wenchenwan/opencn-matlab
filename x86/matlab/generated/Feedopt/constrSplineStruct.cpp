//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSplineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "constrSplineStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = constrSplineStruct( gcodeInfoStruct, R0, R1, sp_index )
//
// constrSplineStruct : Construct a Curv struct filled with the
//  parameters of a Spline.
//
//  gcodeInfoStruct : struct containing the information from the Gcode
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
                        bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, const double R0[6],
                        const double R1[6], unsigned int sp_index, CurvStruct *CStrct)
{
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    double b_expl_temp[6];
    double expl_temp[6];
    double params_CoeffP5[6];
    double params_Cprim[3];
    double params_evec[3];
    double c_expl_temp;
    double d_expl_temp;
    double e_expl_temp;
    double expl_temp_FeedRate;
    double expl_temp_SpindleSpeed;
    double f_expl_temp;
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
    // 'constrSplineStruct:12' coder.inline("never");
    // 'constrSplineStruct:14' params = paramsDefaultCurv();
    paramsDefaultCurv(
        &expl_temp_Type, &expl_temp_zspdmode, &expl_temp_TRAFO, &expl_temp_HSC, &expl_temp_FeedRate,
        &expl_temp_SpindleSpeed, &expl_temp_gcode_source_line, &expl_temp_G91, &expl_temp_G91_1,
        &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints, &params_spline_Bl_handle,
        &params_spline_Bl_order, params_spline_coeff, params_spline_knots, &params_spline_Ltot,
        params_spline_Lk, expl_temp, b_expl_temp, params_Cprim, &c_expl_temp, params_evec,
        &d_expl_temp, &e_expl_temp, params_CoeffP5, &f_expl_temp);
    //  params{11} = sp_index;
    // 'constrSplineStruct:16' gcodeInfoStruct.Type = CurveType.Spline;
    //  gcodeInfoStruct.sp_index = sp_index;
    // 'constrSplineStruct:19' if( coder.target( "MATLAB" ) )
    // 'constrSplineStruct:23' else
    // 'constrSplineStruct:24' CStrct = constrCurvStruct( gcodeInfoStruct, params.spline, R0, R1,
    // ... 'constrSplineStruct:25'                            params.Cprim, ...
    // 'constrSplineStruct:26'                            params.delta, params.evec, params.theta,
    // ... 'constrSplineStruct:27'                            params.pitch, params.CoeffP5,
    // params.Coeff );
    b_constrCurvStruct(CurveType_Spline, gcodeInfoStruct_zspdmode, gcodeInfoStruct_TRAFO,
                       gcodeInfoStruct_HSC, gcodeInfoStruct_FeedRate, gcodeInfoStruct_SpindleSpeed,
                       gcodeInfoStruct_gcode_source_line, gcodeInfoStruct_G91,
                       gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
                       params_spline_Bl_handle, params_spline_Bl_order, params_spline_coeff,
                       params_spline_knots, params_spline_Ltot, params_spline_Lk, R0, R1,
                       params_Cprim, params_evec, params_CoeffP5, CStrct);
    // 'constrSplineStruct:28' CStrct.sp_index = uint32( sp_index );
    CStrct->sp_index = sp_index;
}

} // namespace ocn

//
// File trailer for constrSplineStruct.cpp
//
// [EOF]
//
