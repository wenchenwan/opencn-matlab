//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

#ifndef LENGTHCURV_H
#define LENGTHCURV_H

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
double LengthCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                  const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                  const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                  const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                  const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                  int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv);

}

#endif
//
// File trailer for LengthCurv.h
//
// [EOF]
//
