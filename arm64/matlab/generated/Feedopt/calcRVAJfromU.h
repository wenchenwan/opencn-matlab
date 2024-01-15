
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromU.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CALCRVAJFROMU_H
#define CALCRVAJFROMU_H

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

class Kinematics;

struct GcodeInfoStruct;

struct Tool;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void b_calcRVAJfromU(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, Kinematics *ctx_kin,
                     const CurvStruct *curv, const ::coder::array<double, 2U> &u_vec,
                     const ::coder::array<double, 2U> &ud_vec,
                     const ::coder::array<double, 2U> &udd_vec,
                     const ::coder::array<double, 2U> &uddd_vec, ::coder::array<double, 2U> &R,
                     ::coder::array<double, 2U> &V, ::coder::array<double, 2U> &A,
                     ::coder::array<double, 2U> &J);

void calcRVAJfromU(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, Kinematics *ctx_kin, const GcodeInfoStruct curv_Info, const Tool *curv_tool,
    const ::coder::array<double, 1U> &curv_R0, const ::coder::array<double, 1U> &curv_R1,
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, const ::coder::array<double, 2U> &u_vec,
    const ::coder::array<double, 2U> &ud_vec, const ::coder::array<double, 2U> &udd_vec,
    const ::coder::array<double, 2U> &uddd_vec, ::coder::array<double, 2U> &R,
    ::coder::array<double, 2U> &V, ::coder::array<double, 2U> &A, ::coder::array<double, 2U> &J);

} // namespace ocn

#endif
//
// File trailer for calcRVAJfromU.h
//
// [EOF]
//
