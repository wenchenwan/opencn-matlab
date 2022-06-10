//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "zeroSpeedCurv.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &x
//                const ::coder::array<double, 2U> &z1
//                const double jmax_data[]
//                const int *ctx_cfg_indTot_size
// Return Type  : void
//
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &z1,
                        const double jmax_data[], const int *ctx_cfg_indTot_size)
{
    int b_ctx_cfg_indTot_idx_0;
    int ctx_cfg_indTot_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    ctx_cfg_indTot_idx_0 = *ctx_cfg_indTot_size;
    if (ctx_cfg_indTot_idx_0 == 1) {
        b_ctx_cfg_indTot_idx_0 = z1.size(0);
    } else {
        b_ctx_cfg_indTot_idx_0 = ctx_cfg_indTot_idx_0;
    }
    x.set_size(b_ctx_cfg_indTot_idx_0, z1.size(1));
    stride_0_0 = (z1.size(0) != 1);
    stride_1_0 = (ctx_cfg_indTot_idx_0 != 1);
    loop_ub = z1.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (ctx_cfg_indTot_idx_0 == 1) {
            b_loop_ub = z1.size(0);
        } else {
            b_loop_ub = ctx_cfg_indTot_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            x[i1 + x.size(0) * i] =
                (z1[i1 * stride_0_0 + z1.size(0) * i] > jmax_data[i1 * stride_1_0]);
        }
    }
}

//
// Arguments    : ::coder::array<bool, 2U> &x
//                const ::coder::array<double, 2U> &r
//                const double jmax_data[]
//                const FeedoptContext *ctx
// Return Type  : void
//
void e_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &r,
                        const double jmax_data[], const FeedoptContext *ctx)
{
    int b_ctx_idx_0;
    int ctx_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    ctx_idx_0 = ctx->cfg.indTot.size[0];
    if (ctx_idx_0 == 1) {
        b_ctx_idx_0 = r.size(0);
    } else {
        b_ctx_idx_0 = ctx_idx_0;
    }
    x.set_size(b_ctx_idx_0, r.size(1));
    stride_0_0 = (r.size(0) != 1);
    stride_1_0 = (ctx_idx_0 != 1);
    loop_ub = r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (ctx_idx_0 == 1) {
            b_loop_ub = r.size(0);
        } else {
            b_loop_ub = ctx_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            x[i1 + x.size(0) * i] =
                (r[i1 * stride_0_0 + r.size(0) * i] > jmax_data[i1 * stride_1_0]);
        }
    }
}

} // namespace ocn

//
// File trailer for zeroSpeedCurv.cpp
//
// [EOF]
//
