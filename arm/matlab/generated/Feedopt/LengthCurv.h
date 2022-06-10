//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef LENGTHCURV_H
#define LENGTHCURV_H

// Include Files
#include "opencn_matlab_types31.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

}

// Function Declarations
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                  int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                  const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                  const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                  const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                  CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
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
