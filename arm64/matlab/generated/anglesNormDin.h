//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: anglesNormDin.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:53
//

#ifndef ANGLESNORMDIN_H
#define ANGLESNORMDIN_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void anglesNormDin(const ::coder::array<double, 1U> &A0_deg,
                          const ::coder::array<double, 1U> &A1_deg,
                          const ::coder::array<int, 1U> &A1_mode, bool G90,
                          ::coder::array<double, 1U> &angles_deg);

}

#endif
//
// File trailer for anglesNormDin.h
//
// [EOF]
//
