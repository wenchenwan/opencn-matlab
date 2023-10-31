
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyder.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "mypolyder.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<int, 2U> &in3
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<int, 2U> &in3)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int i1;
    int i2;
    int i3;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    i = in2.size(0);
    i1 = in2.size(1) - 1;
    if (in3.size(0) == 1) {
        i2 = i;
    } else {
        i2 = in3.size(0);
    }
    if (in3.size(1) == 1) {
        i3 = i1;
    } else {
        i3 = in3.size(1);
    }
    in1.set_size(i2, i3);
    stride_0_0 = (i != 1);
    stride_0_1 = (i1 != 1);
    stride_1_0 = (in3.size(0) != 1);
    stride_1_1 = (in3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in3.size(1) == 1) {
        loop_ub = i1;
    } else {
        loop_ub = in3.size(1);
    }
    for (int i4{0}; i4 < loop_ub; i4++) {
        int b_loop_ub;
        if (in3.size(0) == 1) {
            b_loop_ub = i;
        } else {
            b_loop_ub = in3.size(0);
        }
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i4] =
                in2[i5 * stride_0_0 + in2.size(0) * aux_0_1] *
                static_cast<double>(in3[i5 * stride_1_0 + in3.size(0) * aux_1_1]);
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
void g_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int i1;
    int i2;
    int i3;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    i = in2.size(0);
    i1 = in2.size(1) - 1;
    if (in3.size(0) == 1) {
        i2 = i;
    } else {
        i2 = in3.size(0);
    }
    if (in3.size(1) == 1) {
        i3 = i1;
    } else {
        i3 = in3.size(1);
    }
    in1.set_size(i2, i3);
    stride_0_0 = (i != 1);
    stride_0_1 = (i1 != 1);
    stride_1_0 = (in3.size(0) != 1);
    stride_1_1 = (in3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in3.size(1) == 1) {
        loop_ub = i1;
    } else {
        loop_ub = in3.size(1);
    }
    for (int i4{0}; i4 < loop_ub; i4++) {
        int b_loop_ub;
        if (in3.size(0) == 1) {
            b_loop_ub = i;
        } else {
            b_loop_ub = in3.size(0);
        }
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i4] = in2[i5 * stride_0_0 + in2.size(0) * aux_0_1] *
                                         in3[i5 * stride_1_0 + in3.size(0) * aux_1_1];
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

} // namespace ocn

//
// File trailer for mypolyder.cpp
//
// [EOF]
//
