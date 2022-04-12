//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

#ifndef MTIMES_H
#define MTIMES_H

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
namespace blas {
void mtimes(const double A[3], const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C);

}
} // namespace internal
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for mtimes.h
//
// [EOF]
//
