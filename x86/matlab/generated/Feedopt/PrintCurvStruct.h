//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

#ifndef PRINTCURVSTRUCT_H
#define PRINTCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types3.h"
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
void PrintCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                     int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                     const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                     const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                     const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                     CurveType S_Info_Type, ZSpdMode S_Info_zspdmode, double S_Info_FeedRate,
                     const double S_R0[6], const double S_R1[6],
                     const double S_CorrectedHelixCenter[3], const double S_evec[3], double S_theta,
                     double S_pitch, const ::coder::array<double, 2U> &S_CoeffP5,
                     unsigned int S_sp_index, bool S_UseConstJerk, double S_ConstJerk,
                     double S_a_param, double S_b_param);

}

#endif
//
// File trailer for PrintCurvStruct.h
//
// [EOF]
//
