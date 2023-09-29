//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Sep-2023 09:56:15
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
// Function Declarations
namespace ocn {
void binary_expand_op(const ::coder::array<double, 2U> &in1, const double in2_data[],
                      const int *in2_size, double *out1, int *out2);

namespace coder {
namespace internal {
void b_maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

void maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

void minimum(const double x_data[], int x_size, double *ex, int *idx);

void minimum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &ex);

} // namespace internal
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for minOrMax.h
//
// [EOF]
//
