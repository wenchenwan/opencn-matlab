//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrGcodeInfoStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:10
//

#ifndef CONSTRGCODEINFOSTRUCT_H
#define CONSTRGCODEINFOSTRUCT_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrGcodeInfoStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, bool HSC,
                                  bool FeedRate, bool SpindleSpeed, double gcode_source_line,
                                  double G91, unsigned long G91_1, GcodeInfoStruct *GCodeInfoStrct);

}

#endif
//
// File trailer for constrGcodeInfoStruct.h
//
// [EOF]
//
