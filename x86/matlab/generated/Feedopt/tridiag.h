//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: tridiag.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

#ifndef TRIDIAG_H
#define TRIDIAG_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &c, int i, const ::coder::array<double, 2U> &B,
                      const ::coder::array<double, 1U> &v_l, double w);

}

#endif
//
// File trailer for tridiag.h
//
// [EOF]
//
