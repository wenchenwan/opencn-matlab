
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splineLengthFindU.h
//
// MATLAB Coder version            : 5.4
//

#ifndef SPLINELENGTHFINDU_H
#define SPLINELENGTHFINDU_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
double b_splineLengthFindU(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                           unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                           const ::coder::array<double, 2U> &spline_sp_coeff,
                           const ::coder::array<double, 2U> &spline_sp_knots,
                           const ::coder::array<double, 2U> &spline_sp_Lk, double L, double u0);

double splineLengthFindU(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                         unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                         const ::coder::array<double, 2U> &spline_sp_coeff,
                         const ::coder::array<double, 2U> &spline_sp_knots,
                         const ::coder::array<double, 2U> &spline_sp_Lk, double L, double u0);

} // namespace ocn

#endif
//
// File trailer for splineLengthFindU.h
//
// [EOF]
//
