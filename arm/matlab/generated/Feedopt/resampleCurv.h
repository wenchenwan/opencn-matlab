//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

#ifndef RESAMPLECURV_H
#define RESAMPLECURV_H

// Include Files
#include "opencn_matlab_types31.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class ResampleStateClass;

struct uint64m_T;

} // namespace ocn

// Function Declarations
namespace ocn {
void resampleCurv(ResampleStateClass *state, const uint64m_T Bl_handle, ZSpdMode curv_mode,
                  const ::coder::array<double, 1U> &coeff, double constJerk, double dt);

}

#endif
//
// File trailer for resampleCurv.h
//
// [EOF]
//
