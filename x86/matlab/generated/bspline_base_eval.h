//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_base_eval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:46:02
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
                       ::coder::array<double, 2U> &BasisValD);

}

#endif
//
// File trailer for bspline_base_eval.h
//
// [EOF]
//
