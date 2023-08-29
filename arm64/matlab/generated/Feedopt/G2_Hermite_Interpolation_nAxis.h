//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: G2_Hermite_Interpolation_nAxis.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:52:02
//

#ifndef G2_HERMITE_INTERPOLATION_NAXIS_H
#define G2_HERMITE_INTERPOLATION_NAXIS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void G2_Hermite_Interpolation_nAxis(
    const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
    const ::coder::array<double, 1U> &ctx_cfg_D, const ::coder::array<double, 1U> &r0D0_in,
    const ::coder::array<double, 1U> &r0D1_in, const ::coder::array<double, 1U> &r0D2_in,
    const ::coder::array<double, 1U> &r1D0_in, const ::coder::array<double, 1U> &r1D1_in,
    const ::coder::array<double, 1U> &r1D2_in, double p5[6][6], int *status);

}

#endif
//
// File trailer for G2_Hermite_Interpolation_nAxis.h
//
// [EOF]
//
