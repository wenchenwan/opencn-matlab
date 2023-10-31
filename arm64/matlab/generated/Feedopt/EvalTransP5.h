
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.h
//
// MATLAB Coder version            : 5.4
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
                 const ::coder::array<double, 1U> &u_vec, const bool maskTot_data[],
                 const int maskTot_size[2], ::coder::array<double, 2U> &r_0D,
                 ::coder::array<double, 2U> &r_1D, ::coder::array<double, 2U> &r_2D,
                 ::coder::array<double, 2U> &r_3D);

void b_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, double u_vec,
                   const bool maskTot_data[], const int maskTot_size[2], double r_0D_data[],
                   int *r_0D_size, double r_1D_data[], int *r_1D_size, double r_2D_data[],
                   int *r_2D_size, double r_3D_data[], int *r_3D_size);

void c_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                   const ::coder::array<double, 2U> &u_vec, const bool maskTot_data[],
                   const int maskTot_size[2], ::coder::array<double, 2U> &r_0D,
                   ::coder::array<double, 2U> &r_1D, ::coder::array<double, 2U> &r_2D,
                   ::coder::array<double, 2U> &r_3D);

void d_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, const double u_vec[2],
                   const bool maskTot_data[], const int maskTot_size[2], double r_0D_data[],
                   int r_0D_size[2], double r_1D_data[], int r_1D_size[2], double r_2D_data[],
                   int r_2D_size[2], double r_3D_data[], int r_3D_size[2]);

} // namespace ocn

#endif
//
// File trailer for EvalTransP5.h
//
// [EOF]
//
