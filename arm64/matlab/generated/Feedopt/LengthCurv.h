//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
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

struct GcodeInfoStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                  const int ctx_cfg_maskTot_size[2],
                  const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                  const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                  const ::coder::array<int, 1U> &ctx_cfg_indCart,
                  const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                  int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const GcodeInfoStruct curv_Info,
                  const double curv_R0[6], const double curv_R1[6],
                  const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                  double curv_theta, double curv_pitch,
                  const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                  double curv_a_param, double curv_b_param);

}

#endif
//
// File trailer for LengthCurv.h
//
// [EOF]
//
