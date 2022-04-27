//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_simplex.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

#ifndef C_SIMPLEX_H
#define C_SIMPLEX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
namespace coder {
class sparse;

}
} // namespace ocn

// Function Declarations
namespace ocn {
void c_simplex(const ::coder::array<double, 2U> &f, const coder::sparse *A,
               const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
               const ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &C, bool *success,
               int *status);

}

#endif
//
// File trailer for c_simplex.h
//
// [EOF]
//
