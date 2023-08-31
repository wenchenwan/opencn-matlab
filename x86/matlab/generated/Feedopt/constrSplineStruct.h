//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSplineStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:10:03
//

#ifndef CONSTRSPLINESTRUCT_H
#define CONSTRSPLINESTRUCT_H

// Include Files
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void constrSplineStruct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                        bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                        double gcodeInfoStruct_SpindleSpeed, int gcodeInfoStruct_gcode_source_line,
                        bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, int tool_toolno,
                        int tool_pocketno, const Axes *tool_offset, double tool_diameter,
                        double tool_frontangle, double tool_backangle, int tool_orientation,
                        const double R0[6], const double R1[6], unsigned int sp_index,
                        CurvStruct *CStrct);

}

#endif
//
// File trailer for constrSplineStruct.h
//
// [EOF]
//
