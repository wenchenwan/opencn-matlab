//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &y
//                const ::coder::array<double, 2U> &r1
//                const ::coder::array<double, 2U> &r2
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &y, const ::coder::array<double, 2U> &r1,
                        const ::coder::array<double, 2U> &r2)
{
    ::coder::array<double, 2U> r;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (r2.size(0) == 1) {
        if (y.size(0) == 1) {
            i = r1.size(0);
        } else {
            i = y.size(0);
        }
    } else {
        i = r2.size(0);
    }
    r.set_size(i, 9);
    stride_0_0 = (r1.size(0) != 1);
    stride_1_0 = (y.size(0) != 1);
    stride_2_0 = (r2.size(0) != 1);
    if (r2.size(0) == 1) {
        if (y.size(0) == 1) {
            loop_ub = r1.size(0);
        } else {
            loop_ub = y.size(0);
        }
    } else {
        loop_ub = r2.size(0);
    }
    for (int i1{0}; i1 < 9; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            r[i2 + r.size(0) * i1] =
                r1[i2 * stride_0_0 + r1.size(0) * i1] * y[i2 * stride_1_0 + y.size(0) * i1] +
                r2[i2 * stride_2_0 + r2.size(0) * i1];
        }
    }
    y.set_size(r.size(0), 9);
    b_loop_ub = r.size(0);
    for (int i3{0}; i3 < 9; i3++) {
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            y[i4 + y.size(0) * i3] = r[i4 + r.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &D0
//                const ::coder::array<double, 2U> &b
//                const ::coder::array<double, 2U> &b_b
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &D0, const ::coder::array<double, 2U> &b,
                      const ::coder::array<double, 2U> &b_b)
{
    ::coder::array<double, 2U> c_b;
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
    if (b_b.size(0) == 1) {
        if (D0.size(0) == 1) {
            i = b.size(0);
        } else {
            i = D0.size(0);
        }
    } else {
        i = b_b.size(0);
    }
    if (b_b.size(1) == 1) {
        if (D0.size(1) == 1) {
            i1 = b.size(1);
        } else {
            i1 = D0.size(1);
        }
    } else {
        i1 = b_b.size(1);
    }
    c_b.set_size(i, i1);
    stride_0_0 = (b.size(0) != 1);
    stride_0_1 = (b.size(1) != 1);
    stride_1_0 = (D0.size(0) != 1);
    stride_1_1 = (D0.size(1) != 1);
    stride_2_0 = (b_b.size(0) != 1);
    stride_2_1 = (b_b.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (b_b.size(1) == 1) {
        if (D0.size(1) == 1) {
            loop_ub = b.size(1);
        } else {
            loop_ub = D0.size(1);
        }
    } else {
        loop_ub = b_b.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int c_loop_ub;
        if (b_b.size(0) == 1) {
            if (D0.size(0) == 1) {
                c_loop_ub = b.size(0);
            } else {
                c_loop_ub = D0.size(0);
            }
        } else {
            c_loop_ub = b_b.size(0);
        }
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            c_b[i4 + c_b.size(0) * i2] = b[i4 * stride_0_0 + b.size(0) * aux_0_1] *
                                             D0[i4 * stride_1_0 + D0.size(0) * aux_1_1] +
                                         b_b[i4 * stride_2_0 + b_b.size(0) * aux_2_1];
        }
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    D0.set_size(c_b.size(0), c_b.size(1));
    b_loop_ub = c_b.size(1);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = c_b.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            D0[i5 + D0.size(0) * i3] = c_b[i5 + c_b.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 1U> &D0
//                double u_vec
//                const int outsize[2]
//                const ::coder::array<double, 1U> &r
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 1U> &D0, double u_vec, const int outsize[2],
                      const ::coder::array<double, 1U> &r)
{
    ::coder::array<double, 1U> b_u_vec;
    int b_loop_ub;
    int i;
    int loop_ub;
    int outsize_idx_0;
    int stride_1_0;
    int stride_2_0;
    outsize_idx_0 = outsize[0];
    if (r.size(0) == 1) {
        if (D0.size(0) == 1) {
            i = outsize_idx_0;
        } else {
            i = D0.size(0);
        }
    } else {
        i = r.size(0);
    }
    b_u_vec.set_size(i);
    stride_1_0 = (D0.size(0) != 1);
    stride_2_0 = (r.size(0) != 1);
    if (r.size(0) == 1) {
        if (D0.size(0) == 1) {
            loop_ub = outsize_idx_0;
        } else {
            loop_ub = D0.size(0);
        }
    } else {
        loop_ub = r.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_u_vec[i1] = u_vec * D0[i1 * stride_1_0] + r[i1 * stride_2_0];
    }
    D0.set_size(b_u_vec.size(0));
    b_loop_ub = b_u_vec.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        D0[i2] = b_u_vec[i2];
    }
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
