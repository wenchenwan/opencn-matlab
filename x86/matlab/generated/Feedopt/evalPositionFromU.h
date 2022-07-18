//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalPositionFromU.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

#ifndef EVALPOSITIONFROMU_H
#define EVALPOSITIONFROMU_H

// Include Files
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void evalPositionFromU(const FeedoptConfig cfg, const CurvStruct *curv,
                              const CurvStruct *spline, double u, ::coder::array<double, 1U> &r0D);

}

#endif
//
// File trailer for evalPositionFromU.h
//
// [EOF]
//
