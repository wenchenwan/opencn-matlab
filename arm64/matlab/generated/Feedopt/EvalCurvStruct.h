//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:58:50
//

#ifndef EVALCURVSTRUCT_H
#define EVALCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
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

void b_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D);

void c_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D);

void d_EvalCurvStruct(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
                      const bool ctx_cfg_maskCart_data[], const int ctx_cfg_maskCart_size[2],
                      const bool ctx_cfg_maskRot_data[], const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

void e_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D);

void f_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D);

void g_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D);

void h_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D);

void i_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv, double u_vec,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

void j_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D);

void k_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D);

void l_EvalCurvStruct(const FeedoptConfig *ctx_cfg, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStruct.h
//
// [EOF]
//
