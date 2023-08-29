//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutCurvStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

#ifndef CUTCURVSTRUCT_H
#define CUTCURVSTRUCT_H

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
void b_cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L,
                     double *ret, CurvStruct *curv1, CurvStruct *curv2);

void cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                   const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                   const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                   const int ctx_cfg_maskRot_size[2],
                   const ::coder::array<int, 1U> &ctx_cfg_indCart,
                   const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                   int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                   const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L,
                   double *ret, CurvStruct *curv1, CurvStruct *curv2);

} // namespace ocn

#endif
//
// File trailer for cutCurvStruct.h
//
// [EOF]
//
