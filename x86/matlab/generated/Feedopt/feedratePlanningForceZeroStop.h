
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanningForceZeroStop.h
//
// MATLAB Coder version            : 5.4
//

#ifndef FEEDRATEPLANNINGFORCEZEROSTOP_H
#define FEEDRATEPLANNINGFORCEZEROSTOP_H

// Include Files
#include "opencn_matlab_types111.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct b_FeedoptContext;

}

// Function Declarations
namespace ocn {
void feedratePlanningForceZeroStop(b_FeedoptContext *ctx, ::coder::array<CurvStruct, 2U> &window,
                                   double *NWindow);

}

#endif
//
// File trailer for feedratePlanningForceZeroStop.h
//
// [EOF]
//
