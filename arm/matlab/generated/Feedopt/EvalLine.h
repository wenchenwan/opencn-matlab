//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
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
              const ::coder::array<double, 2U> &u_vec, const int ind_data[], int ind_size,
              ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
              ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);

void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
              const int ind_data[], int ind_size, double r0D_data[], int *r0D_size,
              double r1D_data[], int *r1D_size, double r2D_data[], int *r2D_size, double r3D_data[],
              int *r3D_size);

} // namespace ocn

#endif
//
// File trailer for EvalLine.h
//
// [EOF]
//
