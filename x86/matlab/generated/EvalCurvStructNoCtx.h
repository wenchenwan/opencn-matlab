//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef EVALCURVSTRUCTNOCTX_H
#define EVALCURVSTRUCTNOCTX_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalCurvStructNoCtx(CurveType CurvStruct_Type, const double CurvStruct_P0[3],
                         const double CurvStruct_P1[3],
                         const double CurvStruct_CorrectedHelixCenter[3],
                         const double CurvStruct_evec[3], double CurvStruct_theta,
                         double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                         double CurvStruct_a_param, double CurvStruct_b_param,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                         unsigned long CurvSpline_sp_Bl_handle, double u_vec, double r0D[3]);

}

#endif
//
// File trailer for EvalCurvStructNoCtx.h
//
// [EOF]
//
