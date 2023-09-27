//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstrJerk.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

#ifndef BUILDCONSTRJERK_H
#define BUILDCONSTRJERK_H

// Include Files
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

class Kinematics;

} // namespace ocn

// Function Declarations
namespace ocn {
void buildConstrJerk(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
    const ::coder::array<double, 2U> &coeff, const double jmax[6],
    const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 2U> &BasisValD,
    const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 2U> &u_vec,
    ::coder::array<double, 2U> &Aj, ::coder::array<double, 1U> &bj);

}

#endif
//
// File trailer for buildConstrJerk.h
//
// [EOF]
//
