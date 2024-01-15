
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.h
//
// MATLAB Coder version            : 5.4
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
void b_mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &C);

void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
            ::coder::array<double, 2U> &C);

void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B, double C[2]);

void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B,
            ::coder::array<double, 1U> &C);

} // namespace blas
} // namespace internal
} // namespace coder
} // namespace ocn

#endif
//
// File trailer for mtimes.h
//
// [EOF]
//
