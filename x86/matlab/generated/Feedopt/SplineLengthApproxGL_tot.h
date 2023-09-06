//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
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
void binary_expand_op(CurvStruct *in1, const ::coder::array<double, 2U> &in2, int in3, int in7,
                      int in8, int in11);

void c_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3);

} // namespace ocn

#endif
//
// File trailer for SplineLengthApproxGL_tot.h
//
// [EOF]
//
