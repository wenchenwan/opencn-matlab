//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

#ifndef G2_HERMITE_INTERPOLATION_H
#define G2_HERMITE_INTERPOLATION_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void G2_Hermite_Interpolation(const ::coder::array<double, 1U> &r0D0,
                              const ::coder::array<double, 1U> &r0D1,
                              const ::coder::array<double, 1U> &r0D2,
                              const ::coder::array<double, 1U> &r1D0,
                              const ::coder::array<double, 1U> &r1D1,
                              const ::coder::array<double, 1U> &r1D2, double p5_3D[6][3],
                              int *status, double *alpha0, double *alpha1);

}

#endif
//
// File trailer for G2_Hermite_Interpolation.h
//
// [EOF]
//
