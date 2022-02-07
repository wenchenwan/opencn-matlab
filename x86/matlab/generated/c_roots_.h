//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_roots_.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef C_ROOTS__H
#define C_ROOTS__H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_c_roots_(const double coeffs[4], creal_T Y[3]);

void c_c_roots_(const double coeffs[10], creal_T Y[9]);

extern void c_roots_(const double coeffs_data[], const int coeffs_size[2], creal_T Y_data[],
                     int Y_size[1]);

} // namespace ocn

#endif
//
// File trailer for c_roots_.h
//
// [EOF]
//
