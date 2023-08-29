//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyder.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:52:02
//

// Include Files
#include "mypolyder.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<signed char, 2U> &in3
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<signed char, 2U> &in3)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = in2.size(0);
    if (in3.size(0) == 1) {
        i1 = i;
    } else {
        i1 = in3.size(0);
    }
    in1.set_size(i1, 4);
    stride_0_0 = (i != 1);
    stride_1_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = in3.size(0);
    }
    for (int i2{0}; i2 < 4; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            in1[i3 + in1.size(0) * i2] =
                in2[i3 * stride_0_0 + in2.size(0) * i2] *
                static_cast<double>(in3[i3 * stride_1_0 + in3.size(0) * i2]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<signed char, 2U> &in3
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<signed char, 2U> &in3)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = in2.size(0);
    if (in3.size(0) == 1) {
        i1 = i;
    } else {
        i1 = in3.size(0);
    }
    in1.set_size(i1, 3);
    stride_0_0 = (i != 1);
    stride_1_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = in3.size(0);
    }
    for (int i2{0}; i2 < 3; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            in1[i3 + in1.size(0) * i2] =
                in2[i3 * stride_0_0 + in2.size(0) * i2] *
                static_cast<double>(in3[i3 * stride_1_0 + in3.size(0) * i2]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<signed char, 2U> &in3
// Return Type  : void
//
void c_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<signed char, 2U> &in3)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = in2.size(0);
    if (in3.size(0) == 1) {
        i1 = i;
    } else {
        i1 = in3.size(0);
    }
    in1.set_size(i1, 5);
    stride_0_0 = (i != 1);
    stride_1_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = in3.size(0);
    }
    for (int i2{0}; i2 < 5; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            in1[i3 + in1.size(0) * i2] =
                in2[i3 * stride_0_0 + in2.size(0) * i2] *
                static_cast<double>(in3[i3 * stride_1_0 + in3.size(0) * i2]);
        }
    }
}

} // namespace ocn

//
// File trailer for mypolyder.cpp
//
// [EOF]
//
