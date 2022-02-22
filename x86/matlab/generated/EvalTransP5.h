//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
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
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const double u_vec[10], double r_0D[10][3],
                 double r_1D[10][3], double r_2D[10][3], double r_3D[10][3]);

void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const ::coder::array<double, 2U> &u_vec,
                 ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U> &r_1D,
                 ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U> &r_3D);

void EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
                 double r_1D[3], double r_2D[3], double r_3D[3]);

} // namespace ocn

#endif
//
// File trailer for EvalTransP5.h
//
// [EOF]
//
