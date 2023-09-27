//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrGcodeInfoStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

#ifndef CONSTRGCODEINFOSTRUCT_H
#define CONSTRGCODEINFOSTRUCT_H

// Include Files
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrGcodeInfoStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, bool HSC,
                                  bool G91, bool G91_1, double FeedRate, double SpindleSpeed,
                                  int gcode_source_line, GcodeInfoStruct *GCodeInfoStrct);

}

#endif
//
// File trailer for constrGcodeInfoStruct.h
//
// [EOF]
//
