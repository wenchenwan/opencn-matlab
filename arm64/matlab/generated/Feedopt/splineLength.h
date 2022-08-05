//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splineLength.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

#ifndef SPLINELENGTH_H
#define SPLINELENGTH_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
double splineLength(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                    unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                    const ::coder::array<double, 2U> &spline_sp_coeff,
                    const ::coder::array<double, 2U> &spline_sp_knots,
                    const ::coder::array<double, 2U> &spline_sp_Lk, double u1, double u2);

}

#endif
//
// File trailer for splineLength.h
//
// [EOF]
//
