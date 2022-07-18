//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

#ifndef BSPLINE_EVAL_H
#define BSPLINE_EVAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd, double *xddd);

}

#endif
//
// File trailer for bspline_eval.h
//
// [EOF]
//
