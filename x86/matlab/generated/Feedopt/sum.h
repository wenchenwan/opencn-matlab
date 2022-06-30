//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

#ifndef SUM_H
#define SUM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
namespace coder {
void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

double sum(const ::coder::array<double, 2U> &x);

void sum(const ::coder::array<double, 2U> &x, double y[5]);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for sum.h
//
// [EOF]
//
