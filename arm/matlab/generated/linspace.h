//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
//

#ifndef LINSPACE_H
#define LINSPACE_H

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
void b_linspace(int n, ::coder::array<double, 2U> &y);

void c_linspace(int n, ::coder::array<double, 2U> &y);

extern void linspace(double d1, double d2, double n, ::coder::array<double, 2U> &y);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for linspace.h
//
// [EOF]
//
