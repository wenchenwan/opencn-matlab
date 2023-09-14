//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: add_tool_offset.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
//

#ifndef ADD_TOOL_OFFSET_H
#define ADD_TOOL_OFFSET_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

struct FeedoptContext;

} // namespace ocn

// Function Declarations
namespace ocn {
void binary_expand_op(CurvStruct *in1, const FeedoptContext *in2, double in3, double in4,
                      double in5);

void binary_expand_op(CurvStruct *in1, const FeedoptContext *in2, const double in3[3]);

} // namespace ocn

#endif
//
// File trailer for add_tool_offset.h
//
// [EOF]
//
