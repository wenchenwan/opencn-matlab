//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

#ifndef EVALCURVSTRUCT_H
#define EVALCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
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
extern void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *curv,
                           const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                           ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                           ::coder::array<double, 2U> &r3D);

void EvalCurvStruct_init();

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D);

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D);

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D);

void b_EvalCurvStruct(int ctx_cfg_NumberAxis, int ctx_cfg_NCart, int ctx_cfg_NRot,
                      const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                      double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                      ::coder::array<double, 1U> &r3D);

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param,
                      const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D);

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, double u_vec,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

void c_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D);

void c_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D);

void c_EvalCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStruct.h
//
// [EOF]
//
