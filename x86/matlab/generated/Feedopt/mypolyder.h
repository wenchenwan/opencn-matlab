//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyder.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

#ifndef MYPOLYDER_H
#define MYPOLYDER_H

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
                        const ::coder::array<signed char, 2U> &in3);

void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<signed char, 2U> &in3);

void c_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<signed char, 2U> &in3);

} // namespace ocn

#endif
//
// File trailer for mypolyder.h
//
// [EOF]
//
