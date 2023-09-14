//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
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
void b_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3);

void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3);

void binary_expand_op(::coder::array<double, 1U> &in1, double in2, const int in3[2],
                      const ::coder::array<double, 1U> &in4);

} // namespace ocn

#endif
//
// File trailer for mypolyval.h
//
// [EOF]
//
