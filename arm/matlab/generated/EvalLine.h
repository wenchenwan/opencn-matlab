//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:48:06
//

#ifndef EVALLINE_H
#define EVALLINE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double u_vec[10],
              double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3]);

void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
              const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
              ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
              ::coder::array<double, 2U> &r3D);

void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], double u_vec,
              double r0D[3], double r1D[3], double r2D[3], double r3D[3]);

} // namespace ocn

#endif
//
// File trailer for EvalLine.h
//
// [EOF]
//
