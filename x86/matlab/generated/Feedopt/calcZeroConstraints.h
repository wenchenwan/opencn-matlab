//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcZeroConstraints.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

#ifndef CALCZEROCONSTRAINTS_H
#define CALCZEROCONSTRAINTS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
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
void calcZeroConstraints(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                         const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                         const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                         const int ctx_cfg_maskRot_size[2],
                         const ::coder::array<int, 1U> &ctx_cfg_indCart,
                         const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                         int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv, double *vNorm,
                         double *atNorm);

}

#endif
//
// File trailer for calcZeroConstraints.h
//
// [EOF]
//
