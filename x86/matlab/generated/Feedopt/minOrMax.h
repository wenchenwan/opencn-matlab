//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
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
void binary_expand_op(const ::coder::array<double, 2U> &r1, const double vmax_data[],
                      const int *vmax_size, double *v_delta, int *iindx);

namespace coder {
namespace internal {
void b_maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

double maximum(const ::coder::array<double, 1U> &x);

void maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx);

void minimum(const double x_data[], int x_size, double *ex, int *idx);

double minimum(const double x_data[], const int x_size[2]);

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
