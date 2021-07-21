//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrBSplineStruct.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

#ifndef CONSTRBSPLINESTRUCT_H
#define CONSTRBSPLINESTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void ConstrBSplineStruct(const ::coder::array<double, 2U> &pvec, double FeedRate,
                         CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrBSplineStruct.h
//
// [EOF]
//
