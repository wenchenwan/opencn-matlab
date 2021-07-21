//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitSpline.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef SPLITSPLINE_H
#define SPLITSPLINE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct FeedoptContext;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void SplitSpline(const FeedoptContext *ctx, CurvStruct *Curv);

}

#endif
//
// File trailer for SplitSpline.h
//
// [EOF]
//
