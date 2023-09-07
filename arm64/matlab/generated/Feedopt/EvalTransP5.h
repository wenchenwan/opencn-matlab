//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:04:28
//

#ifndef EVALTRANSP5_H
#define EVALTRANSP5_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                 const ::coder::array<double, 2U> &u_vec, int nAxis,
                 ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U> &r_1D,
                 ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U> &r_3D);

void EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, double u_vec, int nAxis,
                 ::coder::array<double, 1U> &r_0D, ::coder::array<double, 1U> &r_1D,
                 ::coder::array<double, 1U> &r_2D, ::coder::array<double, 1U> &r_3D);

} // namespace ocn

#endif
//
// File trailer for EvalTransP5.h
//
// [EOF]
//
