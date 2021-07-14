//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

#ifndef MINORMAX_H
#define MINORMAX_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
namespace coder {
namespace internal {
unsigned long maximum2(unsigned long x);

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
