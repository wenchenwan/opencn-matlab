//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSplineNoCtx.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
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

}

#endif
//
// File trailer for EvalBSplineNoCtx.h
//
// [EOF]
//
