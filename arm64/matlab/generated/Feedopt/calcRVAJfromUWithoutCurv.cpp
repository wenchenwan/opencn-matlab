
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromUWithoutCurv.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "calcRVAJfromUWithoutCurv.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
namespace ocn {
void b_times(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
             const ::coder::array<double, 2U> &in3)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (in3.size(1) == 1) {
        i = in2.size(1);
    } else {
        i = in3.size(1);
    }
    in1.set_size(in2.size(0), i);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in3.size(1) == 1) {
        loop_ub = in2.size(1);
    } else {
        loop_ub = in3.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        b_loop_ub = in2.size(0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            in1[i2 + in1.size(0) * i1] = in2[i2 + in2.size(0) * aux_0_1] * in3[aux_1_1];
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
//                const ::coder::array<double, 2U> &in4
//                const ::coder::array<double, 2U> &in5
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3, const ::coder::array<double, 2U> &in4,
                      const ::coder::array<double, 2U> &in5)
{
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int aux_3_1;
    int i;
    int i1;
    int i2;
    int i3;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    int stride_3_1;
    if (in4.size(0) == 1) {
        i = in2.size(0);
    } else {
        i = in4.size(0);
    }
    if (in5.size(1) == 1) {
        i1 = in4.size(1);
    } else {
        i1 = in5.size(1);
    }
    if (i1 == 1) {
        if (in3.size(1) == 1) {
            i2 = in2.size(1);
        } else {
            i2 = in3.size(1);
        }
    } else if (in5.size(1) == 1) {
        i2 = in4.size(1);
    } else {
        i2 = in5.size(1);
    }
    in1.set_size(i, i2);
    stride_0_0 = (in2.size(0) != 1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    stride_2_0 = (in4.size(0) != 1);
    stride_2_1 = (in4.size(1) != 1);
    stride_3_1 = (in5.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    aux_3_1 = 0;
    if (in5.size(1) == 1) {
        i3 = in4.size(1);
    } else {
        i3 = in5.size(1);
    }
    if (i3 == 1) {
        if (in3.size(1) == 1) {
            loop_ub = in2.size(1);
        } else {
            loop_ub = in3.size(1);
        }
    } else if (in5.size(1) == 1) {
        loop_ub = in4.size(1);
    } else {
        loop_ub = in5.size(1);
    }
    for (int i4{0}; i4 < loop_ub; i4++) {
        int b_loop_ub;
        if (in4.size(0) == 1) {
            b_loop_ub = in2.size(0);
        } else {
            b_loop_ub = in4.size(0);
        }
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i4] =
                in2[i5 * stride_0_0 + in2.size(0) * aux_0_1] * in3[aux_1_1] +
                in4[i5 * stride_2_0 + in4.size(0) * aux_2_1] * in5[aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
//                const ::coder::array<double, 2U> &in4
//                const ::coder::array<double, 2U> &in5
//                const ::coder::array<double, 2U> &in6
//                const ::coder::array<double, 2U> &in7
//                const ::coder::array<double, 2U> &in8
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3, const ::coder::array<double, 2U> &in4,
                      const ::coder::array<double, 2U> &in5, const ::coder::array<double, 2U> &in6,
                      const ::coder::array<double, 2U> &in7, const ::coder::array<double, 2U> &in8)
{
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int aux_3_1;
    int aux_4_1;
    int aux_5_1;
    int aux_6_1;
    int i;
    int i1;
    int i2;
    int i3;
    int i4;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    int stride_3_1;
    int stride_4_1;
    int stride_5_0;
    int stride_5_1;
    int stride_6_1;
    if (in7.size(0) == 1) {
        if (in4.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in4.size(0);
        }
    } else {
        i = in7.size(0);
    }
    if (in8.size(1) == 1) {
        i1 = in7.size(1);
    } else {
        i1 = in8.size(1);
    }
    if (in6.size(1) == 1) {
        if (in5.size(1) == 1) {
            i2 = in4.size(1);
        } else {
            i2 = in5.size(1);
        }
    } else {
        i2 = in6.size(1);
    }
    if (i1 == 1) {
        if (i2 == 1) {
            if (in3.size(1) == 1) {
                i3 = in2.size(1);
            } else {
                i3 = in3.size(1);
            }
        } else if (in6.size(1) == 1) {
            if (in5.size(1) == 1) {
                i3 = in4.size(1);
            } else {
                i3 = in5.size(1);
            }
        } else {
            i3 = in6.size(1);
        }
    } else if (in8.size(1) == 1) {
        i3 = in7.size(1);
    } else {
        i3 = in8.size(1);
    }
    in1.set_size(i, i3);
    stride_0_0 = (in2.size(0) != 1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    stride_2_0 = (in4.size(0) != 1);
    stride_2_1 = (in4.size(1) != 1);
    stride_3_1 = (in5.size(1) != 1);
    stride_4_1 = (in6.size(1) != 1);
    stride_5_0 = (in7.size(0) != 1);
    stride_5_1 = (in7.size(1) != 1);
    stride_6_1 = (in8.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    aux_3_1 = 0;
    aux_4_1 = 0;
    aux_5_1 = 0;
    aux_6_1 = 0;
    if (in8.size(1) == 1) {
        i4 = in7.size(1);
    } else {
        i4 = in8.size(1);
    }
    if (i4 == 1) {
        int i5;
        if (in6.size(1) == 1) {
            if (in5.size(1) == 1) {
                i5 = in4.size(1);
            } else {
                i5 = in5.size(1);
            }
        } else {
            i5 = in6.size(1);
        }
        if (i5 == 1) {
            if (in3.size(1) == 1) {
                loop_ub = in2.size(1);
            } else {
                loop_ub = in3.size(1);
            }
        } else if (in6.size(1) == 1) {
            if (in5.size(1) == 1) {
                loop_ub = in4.size(1);
            } else {
                loop_ub = in5.size(1);
            }
        } else {
            loop_ub = in6.size(1);
        }
    } else if (in8.size(1) == 1) {
        loop_ub = in7.size(1);
    } else {
        loop_ub = in8.size(1);
    }
    for (int i6{0}; i6 < loop_ub; i6++) {
        int b_loop_ub;
        if (in7.size(0) == 1) {
            if (in4.size(0) == 1) {
                b_loop_ub = in2.size(0);
            } else {
                b_loop_ub = in4.size(0);
            }
        } else {
            b_loop_ub = in7.size(0);
        }
        for (int i7{0}; i7 < b_loop_ub; i7++) {
            in1[i7 + in1.size(0) * i6] =
                (in2[i7 * stride_0_0 + in2.size(0) * aux_0_1] * in3[aux_1_1] +
                 3.0 * in4[i7 * stride_2_0 + in4.size(0) * aux_2_1] * in5[aux_3_1] * in6[aux_4_1]) +
                in7[i7 * stride_5_0 + in7.size(0) * aux_5_1] * in8[aux_6_1];
        }
        aux_6_1 += stride_6_1;
        aux_5_1 += stride_5_1;
        aux_4_1 += stride_4_1;
        aux_3_1 += stride_3_1;
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

} // namespace ocn

//
// File trailer for calcRVAJfromUWithoutCurv.cpp
//
// [EOF]
//
