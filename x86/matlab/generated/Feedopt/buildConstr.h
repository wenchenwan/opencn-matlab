//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstr.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

#ifndef BUILDCONSTR_H
#define BUILDCONSTR_H

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

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void buildConstr(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                 const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                 const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                 const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                 const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                 int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                 double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS,
                 const Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
                 const double amax[6], double v_0, double at_0, double v_1, double at_1,
                 const ::coder::array<double, 2U> &BasisVal,
                 const ::coder::array<double, 2U> &BasisValD,
                 const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &A,
                 ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq,
                 ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &continuity);

}

#endif
//
// File trailer for buildConstr.h
//
// [EOF]
//
