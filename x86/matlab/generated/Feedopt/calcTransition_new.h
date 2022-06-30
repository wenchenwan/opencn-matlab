//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition_new.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

#ifndef CALCTRANSITION_NEW_H
#define CALCTRANSITION_NEW_H

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
void calcTransition_new(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                        const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                        const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                        const int ctx_cfg_maskRot_size[2],
                        const ::coder::array<int, 1U> &ctx_cfg_indCart,
                        const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                        int ctx_cfg_NCart, int ctx_cfg_NRot, double ctx_cfg_coeffD,
                        double ctx_cfg_CutOff, const double ctx_cfg_GaussLegendreX[5],
                        const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv1,
                        const CurvStruct *curv2, TransitionResult *status, CurvStruct *curv1C,
                        CurvStruct *curv2C, CurvStruct *curvT);

}

#endif
//
// File trailer for calcTransition_new.h
//
// [EOF]
//
