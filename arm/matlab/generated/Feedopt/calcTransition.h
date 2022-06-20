//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
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
                    const int ctx_cfg_maskTot_size[2],
                    const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                    const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                    const ::coder::array<int, 1U> &ctx_cfg_indCart,
                    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                    int ctx_cfg_NCart, int ctx_cfg_NRot, double ctx_cfg_CutOff,
                    double ctx_cfg_ColTolCosSmooth, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *CurvStruct1,
                    const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                    CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C, TransitionResult *status);

}

#endif
//
// File trailer for calcTransition.h
//
// [EOF]
//
