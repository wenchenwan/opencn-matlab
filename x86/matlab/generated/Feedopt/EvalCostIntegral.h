
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCostIntegral.h
//
// MATLAB Coder version            : 5.4
//

#ifndef EVALCOSTINTEGRAL_H
#define EVALCOSTINTEGRAL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
double EvalCostIntegral(double alpha0, double beta0, double alpha1, double beta1,
                        const double in5[6], const double in6[6], const double in7[6],
                        const double in8[6], const double in9[6], const double in10[6],
                        const double in11[6]);

}

#endif
//
// File trailer for EvalCostIntegral.h
//
// [EOF]
//
