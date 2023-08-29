//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: tridiag.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:52:02
//

// Include Files
#include "tridiag.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                int in2
//                const ::coder::array<double, 2U> &in3
//                const ::coder::array<double, 1U> &in4
//                double in5
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &in1, int in2,
                      const ::coder::array<double, 2U> &in3, const ::coder::array<double, 1U> &in4,
                      double in5)
{
    ::coder::array<double, 2U> b_in3;
    double b_in4;
    int b_in1;
    int b_loop_ub;
    int c_in1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    b_in4 = in4[in2 + 1];
    b_in1 = in1.size(1) - 1;
    i = in3.size(1);
    if (b_in1 + 1 == 1) {
        c_in1 = i;
    } else {
        c_in1 = b_in1 + 1;
    }
    b_in3.set_size(1, c_in1);
    stride_0_1 = (i != 1);
    stride_1_1 = (b_in1 + 1 != 1);
    if (b_in1 + 1 == 1) {
        loop_ub = i;
    } else {
        loop_ub = b_in1 + 1;
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_in3[i1] = (in3[(in2 + in3.size(0) * (i1 * stride_0_1)) + 1] -
                     b_in4 * in1[in2 + in1.size(0) * (i1 * stride_1_1)]) /
                    in5;
    }
    b_loop_ub = b_in3.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        in1[(in2 + in1.size(0) * i2) + 1] = b_in3[i2];
    }
}

} // namespace ocn

//
// File trailer for tridiag.cpp
//
// [EOF]
//
