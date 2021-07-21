//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval_vec.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef BSPLINE_EVAL_VEC_H
#define BSPLINE_EVAL_VEC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void bspline_eval_vec(unsigned long Bl_handle, const double coeffs[4], const double u[2],
                      double x[2]);

void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
                      const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x);

void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
                      const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x,
                      ::coder::array<double, 2U> &xd);

void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
                      const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x,
                      ::coder::array<double, 2U> &xd, ::coder::array<double, 2U> &xdd,
                      ::coder::array<double, 2U> &xddd);

} // namespace ocn

#endif
//
// File trailer for bspline_eval_vec.h
//
// [EOF]
//
