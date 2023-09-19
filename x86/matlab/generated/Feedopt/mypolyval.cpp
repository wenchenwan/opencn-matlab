//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    b_in2.set_size(i, 9);
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_2_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            loop_ub = in2.size(0);
        } else {
            loop_ub = in1.size(0);
        }
    } else {
        loop_ub = in3.size(0);
    }
    for (int i1{0}; i1 < 9; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            b_in2[i2 + b_in2.size(0) * i1] =
                in2[i2 * stride_0_0 + in2.size(0) * i1] * in1[i2 * stride_1_0 + in1.size(0) * i1] +
                in3[i2 * stride_2_0 + in3.size(0) * i1];
        }
    }
    in1.set_size(b_in2.size(0), 9);
    b_loop_ub = b_in2.size(0);
    for (int i3{0}; i3 < 9; i3++) {
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            in1[i4 + in1.size(0) * i3] = b_in2[i4 + b_in2.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            i1 = in2.size(1);
        } else {
            i1 = in1.size(1);
        }
    } else {
        i1 = in3.size(1);
    }
    b_in2.set_size(i, i1);
    stride_0_0 = (in2.size(0) != 1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_1_1 = (in1.size(1) != 1);
    stride_2_0 = (in3.size(0) != 1);
    stride_2_1 = (in3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            loop_ub = in2.size(1);
        } else {
            loop_ub = in1.size(1);
        }
    } else {
        loop_ub = in3.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int c_loop_ub;
        if (in3.size(0) == 1) {
            if (in1.size(0) == 1) {
                c_loop_ub = in2.size(0);
            } else {
                c_loop_ub = in1.size(0);
            }
        } else {
            c_loop_ub = in3.size(0);
        }
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            b_in2[i4 + b_in2.size(0) * i2] = in2[i4 * stride_0_0 + in2.size(0) * aux_0_1] *
                                                 in1[i4 * stride_1_0 + in1.size(0) * aux_1_1] +
                                             in3[i4 * stride_2_0 + in3.size(0) * aux_2_1];
        }
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    in1.set_size(b_in2.size(0), b_in2.size(1));
    b_loop_ub = b_in2.size(1);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = b_in2.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i3] = b_in2[i5 + b_in2.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 1U> &in1
//                double in2
//                const int in3[2]
//                const ::coder::array<double, 1U> &in4
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 1U> &in1, double in2, const int in3[2],
                      const ::coder::array<double, 1U> &in4)
{
    ::coder::array<double, 1U> b_in2;
    int b_loop_ub;
    int i;
    int in3_idx_0;
    int loop_ub;
    int stride_1_0;
    int stride_2_0;
    in3_idx_0 = in3[0];
    if (in4.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in3_idx_0;
        } else {
            i = in1.size(0);
        }
    } else {
        i = in4.size(0);
    }
    b_in2.set_size(i);
    stride_1_0 = (in1.size(0) != 1);
    stride_2_0 = (in4.size(0) != 1);
    if (in4.size(0) == 1) {
        if (in1.size(0) == 1) {
            loop_ub = in3_idx_0;
        } else {
            loop_ub = in1.size(0);
        }
    } else {
        loop_ub = in4.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_in2[i1] = in2 * in1[i1 * stride_1_0] + in4[i1 * stride_2_0];
    }
    in1.set_size(b_in2.size(0));
    b_loop_ub = b_in2.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        in1[i2] = b_in2[i2];
    }
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
