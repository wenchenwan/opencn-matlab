//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unsafeSxfun.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "unsafeSxfun.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &in1
//                const ::coder::array<double, 1U> &in3
//                double in4
//                const ::coder::array<double, 1U> &in5
//                double in6
//                double in7
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in3,
                      double in4, const ::coder::array<double, 1U> &in5, double in6, double in7)
{
    ::coder::array<double, 1U> b_in3;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (in5.size(0) == 1) {
        i = in3.size(0);
    } else {
        i = in5.size(0);
    }
    b_in3.set_size(i);
    stride_0_0 = (in3.size(0) != 1);
    stride_1_0 = (in5.size(0) != 1);
    stride_2_0 = (in5.size(0) != 1);
    if (in5.size(0) == 1) {
        loop_ub = in3.size(0);
    } else {
        loop_ub = in5.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_in3[i1] = (in3[i1 * stride_0_0] * in4 + in5[i1 * stride_1_0] * in6) *
                    (in5[i1 * stride_2_0] / in7);
    }
    in1.set_size(b_in3.size(0));
    b_loop_ub = b_in3.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        double varargin_1;
        varargin_1 = b_in3[i2];
        in1[i2] = std::pow(varargin_1, 2.0);
    }
}

} // namespace ocn

//
// File trailer for unsafeSxfun.cpp
//
// [EOF]
//
