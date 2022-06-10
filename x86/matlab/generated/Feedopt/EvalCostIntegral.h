//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCostIntegral.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

#ifndef EVALCOSTINTEGRAL_H
#define EVALCOSTINTEGRAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
double EvalCostIntegral(double alpha0, double beta0, double alpha1, double beta1,
                        const ::coder::array<double, 1U> &in5, const double in6[3],
                        const double in7[3], double kappa0, const ::coder::array<double, 1U> &in9,
                        const double in10[3], const double in11[3], double kappa1);

}

#endif
//
// File trailer for EvalCostIntegral.h
//
// [EOF]
//
