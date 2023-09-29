//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Sep-2023 09:56:15
//

#ifndef CALCTRANSITION_H
#define CALCTRANSITION_H

// Include Files
#include "opencn_matlab_internal_types.h"
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
void calcTransition(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                    const int ctx_cfg_maskRot_size[2],
                    const ::coder::array<int, 1U> &ctx_cfg_indCart,
                    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                    int ctx_cfg_NCart, int ctx_cfg_NRot,
                    const ::coder::array<double, 1U> &ctx_cfg_D, double ctx_cfg_CutOff,
                    double ctx_cfg_Smoothing_ColTolCosSmooth, double ctx_cfg_Smoothing_ColTolSmooth,
                    const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                    const CurvStruct *curv1, const CurvStruct *curv2, TransitionResult *status,
                    CurvStruct *curv1C, CurvStruct *curv2C, CurvStruct *curvT);

void minus(::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
           const ::coder::array<double, 1U> &in3);

} // namespace ocn

#endif
//
// File trailer for calcTransition.h
//
// [EOF]
//
