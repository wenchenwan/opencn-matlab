//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

#ifndef CALCTRANSITION_H
#define CALCTRANSITION_H

// Include Files
#include "opencn_matlab_internal_types.h"
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
void calcTransition(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                    int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                    const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                    const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size, double ctx_cfg_CutOff,
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
