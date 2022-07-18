//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: tridiag.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:58:50
//

// Include Files
#include "tridiag.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &c
//                int i
//                const ::coder::array<double, 2U> &B
//                const ::coder::array<double, 1U> &v_l
//                double w
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &c, int i, const ::coder::array<double, 2U> &B,
                      const ::coder::array<double, 1U> &v_l, double w)
{
    ::coder::array<double, 2U> b_B;
    double b_v_l;
    int b_c;
    int b_i;
    int b_loop_ub;
    int c_c;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    b_v_l = v_l[i + 1];
    b_c = c.size(1) - 1;
    b_i = B.size(1);
    if (b_c + 1 == 1) {
        c_c = b_i;
    } else {
        c_c = b_c + 1;
    }
    b_B.set_size(1, c_c);
    stride_0_1 = (b_i != 1);
    stride_1_1 = (b_c + 1 != 1);
    if (b_c + 1 == 1) {
        loop_ub = b_i;
    } else {
        loop_ub = b_c + 1;
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_B[i1] = (B[(i + B.size(0) * (i1 * stride_0_1)) + 1] -
                   b_v_l * c[i + c.size(0) * (i1 * stride_1_1)]) /
                  w;
    }
    b_loop_ub = b_B.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        c[(i + c.size(0) * i2) + 1] = b_B[i2];
    }
}

} // namespace ocn

//
// File trailer for tridiag.cpp
//
// [EOF]
//
