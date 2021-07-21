//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcTransition.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

#ifndef CALCTRANSITION_H
#define CALCTRANSITION_H

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
extern void CalcTransition(const FeedoptContext *ctx, const CurvStruct *CurvStruct1,
                           const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                           CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C,
                           TransitionResult *status);

void b_CalcTransition(const queue_coder *ctx_q_splines, double ctx_cfg_CutOff,
                      double ctx_cfg_CollTolDeg, double ctx_cfg_NGridLengthSpline,
                      const CurvStruct *CurvStruct1, const CurvStruct *CurvStruct2,
                      CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T,
                      CurvStruct *CurvStruct2_C, TransitionResult *status);

} // namespace ocn

#endif
//
// File trailer for CalcTransition.h
//
// [EOF]
//
