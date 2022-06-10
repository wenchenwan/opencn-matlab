//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_internal_types.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef OPENCN_MATLAB_INTERNAL_TYPES_H
#define OPENCN_MATLAB_INTERNAL_TYPES_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct emxArray_char_T_1x31 {
    char data[31];
    int size[2];
};

enum TransitionResult : int
{
    TransitionResult_Ok = 0, // Default value
    TransitionResult_Collinear,
    TransitionResult_NoSolution
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_internal_types.h
//
// [EOF]
//
