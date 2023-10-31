
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroStart.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CUTZEROSTART_H
#define CUTZEROSTART_H

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

class Kinematics;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void cutZeroStart(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                  const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                  const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                  const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                  const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                  int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                  const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                  double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                  const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                  const Kinematics *ctx_kin, const CurvStruct *curv, double *ret, CurvStruct *curv1,
                  CurvStruct *curv2);

}

#endif
//
// File trailer for cutZeroStart.h
//
// [EOF]
//
