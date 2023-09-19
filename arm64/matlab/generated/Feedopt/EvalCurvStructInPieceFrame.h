//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructInPieceFrame.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

#ifndef EVALCURVSTRUCTINPIECEFRAME_H
#define EVALCURVSTRUCTINPIECEFRAME_H

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

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void EvalCurvStructInPieceFrame(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, GcodeInfoStruct curv_Info, const double curv_R0[6], const double curv_R1[6],
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D);

void b_EvalCurvStructInPieceFrame(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, CurvStruct *curv, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStructInPieceFrame.h
//
// [EOF]
//
