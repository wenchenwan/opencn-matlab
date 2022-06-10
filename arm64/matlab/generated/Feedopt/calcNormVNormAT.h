//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcNormVNormAT.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

#ifndef CALCNORMVNORMAT_H
#define CALCNORMVNORMAT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct FeedoptContext;

}

// Function Declarations
namespace ocn {
void binary_expand_op(FeedoptContext *ctx, const ::coder::array<double, 1U> &r2D, double y,
                      const ::coder::array<double, 1U> &r1D, double udd, double n);

}

#endif
//
// File trailer for calcNormVNormAT.h
//
// [EOF]
//
