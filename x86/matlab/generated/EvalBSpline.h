//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSpline.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

#ifndef EVALBSPLINE_H
#define EVALBSPLINE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
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
void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index, const double uvec[10],
                 double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3]);

void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index,
                 const ::coder::array<double, 2U> &uvec, ::coder::array<double, 2U> &r0D,
                 ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                 ::coder::array<double, 2U> &r3D);

void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index, double uvec,
                 double r0D[3], double r1D[3], double r2D[3], double r3D[3]);

} // namespace ocn

#endif
//
// File trailer for EvalBSpline.h
//
// [EOF]
//
