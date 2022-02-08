//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_types3.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

#ifndef SINSPACE_TYPES3_H
#define SINSPACE_TYPES3_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct SplineBase {
    int ncoeff;
    ::coder::array<double, 2U> breakpoints;
    unsigned long handle;
    int degree;
};

} // namespace ocn

#endif
//
// File trailer for sinspace_types3.h
//
// [EOF]
//
