//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef MINORMAX_H
#define MINORMAX_H

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
void binary_expand_op(const ::coder::array<double, 2U> &z1, const double amax_data[],
                      const int *ctx_cfg_indTot_size, double *a_delta, int *iindx);

void binary_expand_op(const ::coder::array<double, 2U> &r1, const double amax_data[],
                      const FeedoptContext *ctx, double *a_delta, int *iindx);

namespace coder {
namespace internal {
void b_maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

void maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

void minimum(const double x_data[], int x_size, double *ex, int *idx);

} // namespace internal
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for minOrMax.h
//
// [EOF]
//
