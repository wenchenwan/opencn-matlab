//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Calc_beta0_beta1.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:29:52
//

#ifndef CALC_BETA0_BETA1_H
#define CALC_BETA0_BETA1_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[3], const double in4[3],
                      const double in5[3], double kappa0, const double in7[3], const double in8[3],
                      const double in9[3], double kappa1, double *beta0, double *beta1);

}

#endif
//
// File trailer for Calc_beta0_beta1.h
//
// [EOF]
//
