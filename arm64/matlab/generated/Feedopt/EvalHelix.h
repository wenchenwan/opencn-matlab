//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

#ifndef EVALHELIX_H
#define EVALHELIX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               const ::coder::array<double, 2U> &u_vec, const ::coder::array<bool, 2U> &maskCart,
               ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
               ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);

void b_EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
                 const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
                 double u_vec, const ::coder::array<bool, 2U> &maskCart, double r0D[3],
                 double r1D[3], double r2D[3], double r3D[3]);

} // namespace ocn

#endif
//
// File trailer for EvalHelix.h
//
// [EOF]
//
