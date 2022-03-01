//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:00:11
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
void CalcBspline_Lee(int cfg_SplineDegree, const ::coder::array<double, 2U> &points,
                     ::coder::array<double, 2U> &sp3D_CoeffX,
                     ::coder::array<double, 2U> &sp3D_CoeffY,
                     ::coder::array<double, 2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, ::coder::array<double, 2U> &sp3D_knots);

}

#endif
//
// File trailer for CalcBspline_Lee.h
//
// [EOF]
//
