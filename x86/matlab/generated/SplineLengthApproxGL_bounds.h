//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_bounds.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:00:11
//

#ifndef SPLINELENGTHAPPROXGL_BOUNDS_H
#define SPLINELENGTHAPPROXGL_BOUNDS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

}

// Function Declarations
namespace ocn {
double SplineLengthApproxGL_bounds(const queue_coder *ctx_q_splines,
                                   const double ctx_cfg_GaussLegendreX[5],
                                   const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index,
                                   double u1, double u2);

}

#endif
//
// File trailer for SplineLengthApproxGL_bounds.h
//
// [EOF]
//
