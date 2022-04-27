//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

#ifndef RESAMPLECURV_H
#define RESAMPLECURV_H

// Include Files
#include "ResampleStateClass.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void resampleCurv(ResampleStateClass *state, const SplineBase *Bl, ZSpdMode curv_mode,
                         const ::coder::array<double, 1U> &coeff, double constJerk, double dt,
                         double curv_a, double curv_b, double *ud, double *udd, double *uddd);

}

#endif
//
// File trailer for resampleCurv.h
//
// [EOF]
//
