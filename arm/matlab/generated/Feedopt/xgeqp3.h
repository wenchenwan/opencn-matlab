//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef XGEQP3_H
#define XGEQP3_H

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
namespace internal {
namespace lapack {
void xgeqp3(::coder::array<double, 2U> &A, ::coder::array<double, 1U> &tau,
            ::coder::array<int, 2U> &jpvt);

}
} // namespace internal
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for xgeqp3.h
//
// [EOF]
//
