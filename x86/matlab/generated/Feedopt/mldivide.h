//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

#ifndef MLDIVIDE_H
#define MLDIVIDE_H

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
void mldivide(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &Y);

void mldivide(const double A[2][2], const double B[2], double Y[2]);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for mldivide.h
//
// [EOF]
//
