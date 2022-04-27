//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef CUTZEROEND_H
#define CUTZEROEND_H

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
void cutZeroEnd(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
                const double ctx_cfg_jmax[3], double ctx_cfg_dt, const CurvStruct *b_CurvStruct,
                CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);

}

#endif
//
// File trailer for cutZeroEnd.h
//
// [EOF]
//
