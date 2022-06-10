//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
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
void cutZeroEnd(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                const CurvStruct *curv, CurvStruct *curv1, CurvStruct *curv2);

}

#endif
//
// File trailer for cutZeroEnd.h
//
// [EOF]
//
