//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: kin_J2P_ar_xyzbc.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

#ifndef KIN_J2P_AR_XYZBC_H
#define KIN_J2P_AR_XYZBC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void kin_J2P_ar_xyzbc(const ::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
                      const ::coder::array<double, 1U> &in3, const ::coder::array<double, 1U> &in4,
                      double J2P_ar[5][5]);

}

#endif
//
// File trailer for kin_J2P_ar_xyzbc.h
//
// [EOF]
//
