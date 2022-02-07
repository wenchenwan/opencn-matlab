//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef SPLITCURVSTRUCT_H
#define SPLITCURVSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct FeedoptContext;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void SplitCurvStruct(const FeedoptContext *ctx, const CurvStruct *CurvStrct);

}

#endif
//
// File trailer for SplitCurvStruct.h
//
// [EOF]
//
