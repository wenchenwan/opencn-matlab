//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcTransition.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef CALCTRANSITION_H
#define CALCTRANSITION_H

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
extern void CalcTransition(const FeedoptContext *ctx, const CurvStruct *CurvStruct1,
                           const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                           CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C,
                           TransitionResult *status);

void b_CalcTransition(const queue_coder *ctx_q_splines, double ctx_cfg_CutOff,
                      double ctx_cfg_ColTolCos, const double ctx_cfg_GaussLegendreX[5],
                      const double ctx_cfg_GaussLegendreW[5], const CurvStruct *CurvStruct1,
                      const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                      CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C,
                      TransitionResult *status);

} // namespace ocn

#endif
//
// File trailer for CalcTransition.h
//
// [EOF]
//
