//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:28:22
//

#ifndef BSPLINE_EVAL_H
#define BSPLINE_EVAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct uint64m_T;

}

// Function Declarations
namespace ocn {
void bspline_eval(const uint64m_T Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd, double *xddd);

void bspline_eval(const uint64m_T Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd);

} // namespace ocn

#endif
//
// File trailer for bspline_eval.h
//
// [EOF]
//
