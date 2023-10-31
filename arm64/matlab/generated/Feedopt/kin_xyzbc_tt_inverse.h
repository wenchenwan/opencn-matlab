
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: kin_xyzbc_tt_inverse.h
//
// MATLAB Coder version            : 5.4
//

#ifndef KIN_XYZBC_TT_INVERSE_H
#define KIN_XYZBC_TT_INVERSE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void kin_xyzbc_tt_inverse(const ::coder::array<double, 1U> &in1,
                          const ::coder::array<double, 1U> &in2, double joint[5]);

}

#endif
//
// File trailer for kin_xyzbc_tt_inverse.h
//
// [EOF]
//
