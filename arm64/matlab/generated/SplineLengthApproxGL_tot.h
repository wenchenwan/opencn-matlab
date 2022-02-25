//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:29:52
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
// Function Declarations
namespace ocn {
void SplineLengthApproxGL_tot(double ctx_cfg_GaussLegendreN, const double ctx_cfg_GaussLegendreX[5],
                              const double ctx_cfg_GaussLegendreW[5],
                              const ::coder::array<double, 2U> &Curv_sp_CoeffX,
                              const ::coder::array<double, 2U> &Curv_sp_CoeffY,
                              const ::coder::array<double, 2U> &Curv_sp_CoeffZ,
                              unsigned long Curv_sp_Bl_handle,
                              const ::coder::array<double, 2U> &Curv_sp_knots, double *L,
                              ::coder::array<double, 2U> &Lk);

}

#endif
//
// File trailer for SplineLengthApproxGL_tot.h
//
// [EOF]
//
