//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcAlpha0.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

#ifndef CALCALPHA0_H
#define CALCALPHA0_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void binary_expand_op(double t12_data[], int *t12_size, const double CoefPS[16],
                      const double alpha1_t_data[], const int *alpha1_t_size,
                      const ::coder::array<double, 1U> &r, const ::coder::array<double, 1U> &r1);

}

#endif
//
// File trailer for CalcAlpha0.h
//
// [EOF]
//
