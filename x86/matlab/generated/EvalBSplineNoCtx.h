//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSplineNoCtx.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

#ifndef EVALBSPLINENOCTX_H
#define EVALBSPLINENOCTX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
                      double r1D[3], double r2D[3], double r3D[3]);

void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, const ::coder::array<double, 2U> &uvec,
                      ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D);

void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
                      double r1D[3]);

void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, const double uvec[5], double r0D[5][3],
                      double r1D[5][3]);

} // namespace ocn

#endif
//
// File trailer for EvalBSplineNoCtx.h
//
// [EOF]
//
