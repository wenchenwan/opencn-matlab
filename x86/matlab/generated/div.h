//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: div.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
//

#ifndef DIV_H
#define DIV_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void binary_expand_op(double alpha0_t_data[], int *alpha0_t_size, const double CoefPS[16],
                      const double alpha1_t_data[], const int *alpha1_t_size,
                      const double t5_data[], const int *t5_size, const double t11_data[],
                      const int *t11_size, const double t12_data[], const int *t12_size,
                      const double t10_data[], const int *t10_size, const double _data[],
                      const int *_size, const double b__data[], const int *b__size);

}

#endif
//
// File trailer for div.h
//
// [EOF]
//
