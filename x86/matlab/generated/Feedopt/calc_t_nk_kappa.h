//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calc_t_nk_kappa.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

#ifndef CALC_T_NK_KAPPA_H
#define CALC_T_NK_KAPPA_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void calc_t_nk_kappa(const double rD1[5], const double rD2[5], double t[5], double nk[5],
                     double *kappa);

void calc_t_nk_kappa(const ::coder::array<double, 1U> &rD1, const ::coder::array<double, 1U> &rD2,
                     ::coder::array<double, 1U> &t, ::coder::array<double, 1U> &nk, double *kappa);

} // namespace ocn

#endif
//
// File trailer for calc_t_nk_kappa.h
//
// [EOF]
//
