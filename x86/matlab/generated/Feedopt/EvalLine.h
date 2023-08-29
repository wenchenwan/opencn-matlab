//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:40:50
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
              const ::coder::array<double, 2U> &u_vec, const bool mask_data[],
              const int mask_size[2], ::coder::array<double, 2U> &r0D,
              ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
              ::coder::array<double, 2U> &r3D);

void b_EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
                const bool mask_data[], const int mask_size[2], double r0D_data[], int *r0D_size,
                double r1D_data[], int *r1D_size, ::coder::array<double, 1U> &r2D,
                ::coder::array<double, 1U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalLine.h
//
// [EOF]
//
