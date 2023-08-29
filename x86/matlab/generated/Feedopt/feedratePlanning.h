//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

#ifndef FEEDRATEPLANNING_H
#define FEEDRATEPLANNING_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct b_FeedoptContext;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void feedratePlanning(b_FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct, bool *quit);

void feedratePlanning_init();

} // namespace ocn

#endif
//
// File trailer for feedratePlanning.h
//
// [EOF]
//
