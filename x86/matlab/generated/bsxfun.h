//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef BSXFUN_H
#define BSXFUN_H

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
void bsxfun(const ::coder::array<double, 1U> &a, const ::coder::array<double, 2U> &b,
            ::coder::array<double, 2U> &c);

void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 1U> &b,
            ::coder::array<double, 2U> &c);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for bsxfun.h
//
// [EOF]
//
