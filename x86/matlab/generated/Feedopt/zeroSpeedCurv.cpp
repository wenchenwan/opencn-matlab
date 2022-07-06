//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

// Include Files
#include "zeroSpeedCurv.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &x
//                const ::coder::array<double, 2U> &r
//                const double jmax_data[]
//                const int *jmax_size
// Return Type  : void
//
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &r,
                        const double jmax_data[], const int *jmax_size)
{
    int b_jmax_idx_0;
    int jmax_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    jmax_idx_0 = *jmax_size;
    if (jmax_idx_0 == 1) {
        b_jmax_idx_0 = r.size(0);
    } else {
        b_jmax_idx_0 = jmax_idx_0;
    }
    x.set_size(b_jmax_idx_0, r.size(1));
    stride_0_0 = (r.size(0) != 1);
    stride_1_0 = (jmax_idx_0 != 1);
    loop_ub = r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (jmax_idx_0 == 1) {
            b_loop_ub = r.size(0);
        } else {
            b_loop_ub = jmax_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            x[i1 + x.size(0) * i] =
                (r[i1 * stride_0_0 + r.size(0) * i] > jmax_data[i1 * stride_1_0]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &feed
//                const ::coder::array<double, 2U> &y
//                const ::coder::array<double, 2U> &ud
// Return Type  : void
//
void times(::coder::array<double, 2U> &feed, const ::coder::array<double, 2U> &y,
           const ::coder::array<double, 2U> &ud)
{
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (ud.size(1) == 1) {
        i = y.size(1);
    } else {
        i = ud.size(1);
    }
    feed.set_size(1, i);
    stride_0_1 = (y.size(1) != 1);
    stride_1_1 = (ud.size(1) != 1);
    if (ud.size(1) == 1) {
        loop_ub = y.size(1);
    } else {
        loop_ub = ud.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        feed[i1] = y[i1 * stride_0_1] * ud[i1 * stride_1_1];
    }
}

} // namespace ocn

//
// File trailer for zeroSpeedCurv.cpp
//
// [EOF]
//
