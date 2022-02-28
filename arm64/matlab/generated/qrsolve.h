//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qrsolve.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:02:06
//

#ifndef QRSOLVE_H
#define QRSOLVE_H

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
void qrsolve(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B,
             ::coder::array<double, 1U> &Y);

}
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for qrsolve.h
//
// [EOF]
//
