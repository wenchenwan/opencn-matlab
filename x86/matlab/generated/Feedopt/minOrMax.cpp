//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "minOrMax.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &z1
//                const double amax_data[]
//                const int *ctx_cfg_indTot_size
//                double *a_delta
//                int *iindx
// Return Type  : void
//
namespace ocn {
void binary_expand_op(const ::coder::array<double, 2U> &z1, const double amax_data[],
                      const int *ctx_cfg_indTot_size, double *a_delta, int *iindx)
{
    ::coder::array<double, 2U> b_z1;
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
    b_z1.set_size(b_ctx_cfg_indTot_idx_0, z1.size(1));
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
            b_z1[i1 + b_z1.size(0) * i] =
                z1[i1 * stride_0_0 + z1.size(0) * i] - amax_data[i1 * stride_1_0];
        }
    }
    coder::internal::b_maximum(b_z1, a_delta, iindx);
}

//
// Arguments    : const ::coder::array<double, 2U> &r1
//                const double amax_data[]
//                const FeedoptContext *ctx
//                double *a_delta
//                int *iindx
// Return Type  : void
//
void binary_expand_op(const ::coder::array<double, 2U> &r1, const double amax_data[],
                      const FeedoptContext *ctx, double *a_delta, int *iindx)
{
    ::coder::array<double, 2U> r;
    int b_ctx_idx_0;
    int ctx_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    ctx_idx_0 = ctx->cfg.indTot.size[0];
    if (ctx_idx_0 == 1) {
        b_ctx_idx_0 = r1.size(0);
    } else {
        b_ctx_idx_0 = ctx_idx_0;
    }
    r.set_size(b_ctx_idx_0, r1.size(1));
    stride_0_0 = (r1.size(0) != 1);
    stride_1_0 = (ctx_idx_0 != 1);
    loop_ub = r1.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (ctx_idx_0 == 1) {
            b_loop_ub = r1.size(0);
        } else {
            b_loop_ub = ctx_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r[i1 + r.size(0) * i] =
                r1[i1 * stride_0_0 + r1.size(0) * i] - amax_data[i1 * stride_1_0];
        }
    }
    coder::internal::b_maximum(r, a_delta, iindx);
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double *ex
//                int *idx
// Return Type  : void
//
namespace coder {
namespace internal {
void b_maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx)
{
    int last;
    last = x.size(0) * x.size(1);
    if (x.size(0) * x.size(1) <= 2) {
        if (x.size(0) * x.size(1) == 1) {
            *ex = x[0];
            *idx = 1;
        } else if (x[0] < x[x.size(0) * x.size(1) - 1]) {
            *ex = x[x.size(0) * x.size(1) - 1];
            *idx = x.size(0) * x.size(1);
        } else {
            *ex = x[0];
            *idx = 1;
        }
    } else {
        double b_ex;
        b_ex = x[0];
        *idx = 1;
        for (int k{2}; k <= last; k++) {
            if (b_ex < x[k - 1]) {
                b_ex = x[k - 1];
                *idx = k;
            }
        }
        *ex = b_ex;
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double *ex
//                int *idx
// Return Type  : void
//
void maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx)
{
    int last;
    last = x.size(1);
    if (x.size(1) <= 2) {
        if (x.size(1) == 1) {
            *ex = x[0];
            *idx = 1;
        } else if (x[0] < x[x.size(1) - 1]) {
            *ex = x[x.size(1) - 1];
            *idx = x.size(1);
        } else {
            *ex = x[0];
            *idx = 1;
        }
    } else {
        double b_ex;
        b_ex = x[0];
        *idx = 1;
        for (int k{2}; k <= last; k++) {
            double d;
            d = x[k - 1];
            if (b_ex < d) {
                b_ex = d;
                *idx = k;
            }
        }
        *ex = b_ex;
    }
}

//
// Arguments    : const double x_data[]
//                int x_size
//                double *ex
//                int *idx
// Return Type  : void
//
void minimum(const double x_data[], int x_size, double *ex, int *idx)
{
    if (x_size <= 2) {
        if (x_size == 1) {
            *ex = x_data[0];
            *idx = 1;
        } else {
            double d;
            d = x_data[x_size - 1];
            if (x_data[0] > d) {
                *ex = d;
                *idx = x_size;
            } else {
                *ex = x_data[0];
                *idx = 1;
            }
        }
    } else {
        double b_ex;
        b_ex = x_data[0];
        *idx = 1;
        for (int k{2}; k <= x_size; k++) {
            double d1;
            d1 = x_data[k - 1];
            if (b_ex > d1) {
                b_ex = d1;
                *idx = k;
            }
        }
        *ex = b_ex;
    }
}

} // namespace internal
} // namespace coder
} // namespace ocn

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
