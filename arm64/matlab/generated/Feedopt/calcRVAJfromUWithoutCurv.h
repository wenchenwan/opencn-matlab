//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromUWithoutCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

#ifndef CALCRVAJFROMUWITHOUTCURV_H
#define CALCRVAJFROMUWITHOUTCURV_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_times(::coder::array<double, 2U> &V, const ::coder::array<double, 2U> &r1D,
             const ::coder::array<double, 2U> &ud);

void binary_expand_op(::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &r2D,
                      const ::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r1D,
                      const ::coder::array<double, 2U> &udd_vec);

void binary_expand_op(::coder::array<double, 2U> &J, const ::coder::array<double, 2U> &r3D,
                      const ::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r2D,
                      const ::coder::array<double, 2U> &ud,
                      const ::coder::array<double, 2U> &udd_vec,
                      const ::coder::array<double, 2U> &r1D, double jps, const unsigned int r1[2]);

} // namespace ocn

#endif
//
// File trailer for calcRVAJfromUWithoutCurv.h
//
// [EOF]
//
