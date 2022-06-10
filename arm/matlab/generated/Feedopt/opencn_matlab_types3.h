//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types3.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef OPENCN_MATLAB_TYPES3_H
#define OPENCN_MATLAB_TYPES3_H

// Include Files
#include "opencn_matlab_types1.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct BaseSplineStruct {
    int ncoeff;
    ::coder::array<double, 2U> breakpoints;
    uint64m_T handle;
    int order;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types3.h
//
// [EOF]
//
