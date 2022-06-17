//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

#ifndef SPLINELENGTHAPPROXGL_TOT_H
#define SPLINELENGTHAPPROXGL_TOT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void binary_expand_op(CurvStruct *spline, const ::coder::array<double, 2U> &y, int i4, int i5,
                      int i6, int i7);

void c_binary_expand_op(::coder::array<double, 2U> &Umat, const ::coder::array<double, 2U> &c,
                        const ::coder::array<double, 2U> &b_c);

} // namespace ocn

#endif
//
// File trailer for SplineLengthApproxGL_tot.h
//
// [EOF]
//
