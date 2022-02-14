//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
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
// Type Declarations
namespace ocn {
struct uint64m_T;

}

// Function Declarations
namespace ocn {
void CalcBspline_Lee(int cfg_SplineDegree, double sp3D_CoeffX[4], double sp3D_CoeffY[4],
                     double sp3D_CoeffZ[4], int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, uint64m_T *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, double sp3D_knots[8]);

void CalcBspline_Lee(int cfg_SplineDegree, const ::coder::array<double, 2U> &points,
                     ::coder::array<double, 2U> &sp3D_CoeffX,
                     ::coder::array<double, 2U> &sp3D_CoeffY,
                     ::coder::array<double, 2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, uint64m_T *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, ::coder::array<double, 2U> &sp3D_knots);

} // namespace ocn

#endif
//
// File trailer for CalcBspline_Lee.h
//
// [EOF]
//
