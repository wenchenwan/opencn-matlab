//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

#ifndef PRINTCURVSTRUCT_H
#define PRINTCURVSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

}

// Function Declarations
namespace ocn {
extern void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S);

void b_PrintCurvStruct(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                       const double ctx_cfg_GaussLegendreW[5], const CurvStruct *S);

} // namespace ocn

#endif
//
// File trailer for PrintCurvStruct.h
//
// [EOF]
//
