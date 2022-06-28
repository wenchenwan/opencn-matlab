//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

#ifndef ZEROSPEEDCURV_H
#define ZEROSPEEDCURV_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &r,
                        const double jmax_data[], const int *jmax_size);

void times(::coder::array<double, 2U> &feed, const ::coder::array<double, 2U> &y,
           const ::coder::array<double, 2U> &ud);

} // namespace ocn

#endif
//
// File trailer for zeroSpeedCurv.h
//
// [EOF]
//
