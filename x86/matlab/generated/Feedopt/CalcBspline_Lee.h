//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:10:03
//

#ifndef CALCBSPLINE_LEE_H
#define CALCBSPLINE_LEE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void CalcBspline_Lee(int cfg_NumberAxis, int cfg_LeeSplineDegree,
                     const ::coder::array<double, 2U> &points, int *spnD_Bl_ncoeff,
                     ::coder::array<double, 2U> &spnD_Bl_breakpoints, unsigned long *spnD_Bl_handle,
                     int *spnD_Bl_order, ::coder::array<double, 2U> &spnD_coeff,
                     ::coder::array<double, 2U> &spnD_knots, double *spnD_Ltot,
                     ::coder::array<double, 2U> &spnD_Lk);

}

#endif
//
// File trailer for CalcBspline_Lee.h
//
// [EOF]
//
