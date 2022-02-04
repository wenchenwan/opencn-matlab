//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_base_eval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

#ifndef BSPLINE_BASE_EVAL_H
#define BSPLINE_BASE_EVAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle,
                       const ::coder::array<double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal,
                       ::coder::array<double, 2U> &BasisValD,
                       ::coder::array<double, 2U> &BasisValDD,
                       ::coder::array<double, 2U> &BasisValDDD,
                       ::coder::array<double, 1U> &BasisIntegr);

void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle,
                       const ::coder::array<double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal,
                       ::coder::array<double, 2U> &BasisValD);

} // namespace ocn

#endif
//
// File trailer for bspline_base_eval.h
//
// [EOF]
//
