//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

#ifndef PRINTCURVSTRUCT_H
#define PRINTCURVSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void PrintCurvStruct(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], const CurvStruct *S);

}

#endif
//
// File trailer for PrintCurvStruct.h
//
// [EOF]
//
