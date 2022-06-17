//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSpline.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
//

#ifndef EVALBSPLINE_H
#define EVALBSPLINE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalBSpline(unsigned long spline_sp_Bl_handle,
                 const ::coder::array<double, 2U> &spline_sp_coeff, const double u_vec[5],
                 ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D);

void EvalBSpline(unsigned long spline_sp_Bl_handle,
                 const ::coder::array<double, 2U> &spline_sp_coeff,
                 const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                 ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                 ::coder::array<double, 2U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalBSpline.h
//
// [EOF]
//
