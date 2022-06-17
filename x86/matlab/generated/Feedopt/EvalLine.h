//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
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
void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6],
              const ::coder::array<double, 2U> &u_vec, const ::coder::array<bool, 2U> &mask,
              ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
              ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);

void b_EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
                const ::coder::array<bool, 2U> &mask, ::coder::array<double, 1U> &r0D,
                ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                ::coder::array<double, 1U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalLine.h
//
// [EOF]
//
