//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
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
// Type Declarations
namespace ocn {
struct FeedoptContext;

}

// Function Declarations
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &z1,
                        const double jmax_data[], const int *ctx_cfg_indTot_size);

void e_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &r,
                        const double jmax_data[], const FeedoptContext *ctx);

} // namespace ocn

#endif
//
// File trailer for zeroSpeedCurv.h
//
// [EOF]
//
