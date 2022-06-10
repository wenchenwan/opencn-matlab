//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyder.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
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
void b_binary_expand_op(::coder::array<double, 2U> &p5_2D, const ::coder::array<double, 2U> &p5_1D,
                        const ::coder::array<signed char, 2U> &b);

void binary_expand_op(::coder::array<double, 2U> &p5_3D, const ::coder::array<double, 2U> &p5_2D,
                      const ::coder::array<signed char, 2U> &b);

void c_binary_expand_op(::coder::array<double, 2U> &p5_1D,
                        const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                        const ::coder::array<signed char, 2U> &b);

} // namespace ocn

#endif
//
// File trailer for mypolyder.h
//
// [EOF]
//
