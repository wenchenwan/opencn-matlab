//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: paramsDefaultCurv.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

#ifndef PARAMSDEFAULTCURV_H
#define PARAMSDEFAULTCURV_H

// Include Files
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct SplineStruct;

}

// Function Declarations
namespace ocn {
void paramsDefaultCurv(
    CurveType *params_gcodeInfoStruct_Type, ZSpdMode *params_gcodeInfoStruct_zspdmode,
    bool *params_gcodeInfoStruct_TRAFO, bool *params_gcodeInfoStruct_HSC,
    double *params_gcodeInfoStruct_FeedRate, double *params_gcodeInfoStruct_SpindleSpeed,
    int *params_gcodeInfoStruct_gcode_source_line, bool *params_gcodeInfoStruct_G91,
    bool *params_gcodeInfoStruct_G91_1, int *params_tool_toolno, int *params_tool_pocketno,
    Axes *params_tool_offset, double *params_tool_diameter, double *params_tool_frontangle,
    double *params_tool_backangle, int *params_tool_orientation, SplineStruct *params_spline,
    double params_R0[6], double params_R1[6], double params_Cprim[3], double *params_delta,
    double params_evec[3], double *params_theta, double *params_pitch, double params_CoeffP5[6],
    double *params_Coeff);

}

#endif
//
// File trailer for paramsDefaultCurv.h
//
// [EOF]
//
