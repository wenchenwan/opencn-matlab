//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef PRINTCURVSTRUCT_H
#define PRINTCURVSTRUCT_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include "sinspace_types.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S);

void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                       const CurvStruct *S);

} // namespace ocn

#endif
//
// File trailer for PrintCurvStruct.h
//
// [EOF]
//
