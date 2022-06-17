//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

#ifndef MYPOLYVAL_H
#define MYPOLYVAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &y, const ::coder::array<double, 2U> &r1,
                        const ::coder::array<double, 2U> &r2);

void binary_expand_op(::coder::array<double, 2U> &D0, const ::coder::array<double, 2U> &b,
                      const ::coder::array<double, 2U> &b_b);

void binary_expand_op(::coder::array<double, 1U> &D0, double u_vec, const int outsize[2],
                      const ::coder::array<double, 1U> &r);

} // namespace ocn

#endif
//
// File trailer for mypolyval.h
//
// [EOF]
//
