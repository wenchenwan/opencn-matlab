//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct_types3.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 21-Feb-2022 17:59:00
//

#ifndef EVALCURVSTRUCT_TYPES3_H
#define EVALCURVSTRUCT_TYPES3_H

// Include Files
#include "EvalCurvStruct_types11.h"
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
    uint64m_T handle;
    int degree;
};

} // namespace ocn

#endif
//
// File trailer for EvalCurvStruct_types3.h
//
// [EOF]
//
