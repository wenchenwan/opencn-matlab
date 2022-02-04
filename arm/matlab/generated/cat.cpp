//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cat.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "cat.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &r0D
//                const double CurvStruct_P1[3]
//                const ::coder::array<double, 2U> &u_vec
//                const double CurvStruct_P0[3]
//                const ::coder::array<double, 2U> &b_tmp
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &r0D, const double CurvStruct_P1[3],
                      const ::coder::array<double, 2U> &u_vec, const double CurvStruct_P0[3],
                      const ::coder::array<double, 2U> &b_tmp)
{
    ::coder::array<double, 2U> e_CurvStruct_P1;
    ::coder::array<double, 2U> f_CurvStruct_P1;
    ::coder::array<double, 2U> g_CurvStruct_P1;
    double b_CurvStruct_P0;
    double b_CurvStruct_P1;
    double c_CurvStruct_P0;
    double c_CurvStruct_P1;
    double d_CurvStruct_P0;
    double d_CurvStruct_P1;
    int b_loop_ub;
    int b_stride_0_1;
    int b_stride_1_1;
    int c_loop_ub;
    int c_stride_0_1;
    int c_stride_1_1;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i;
    int i2;
    int i4;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    b_CurvStruct_P1 = CurvStruct_P1[0];
    b_CurvStruct_P0 = CurvStruct_P0[0];
    c_CurvStruct_P1 = CurvStruct_P1[1];
    c_CurvStruct_P0 = CurvStruct_P0[1];
    d_CurvStruct_P1 = CurvStruct_P1[2];
    d_CurvStruct_P0 = CurvStruct_P0[2];
    if (b_tmp.size(1) == 1) {
        i = u_vec.size(1);
    } else {
        i = b_tmp.size(1);
    }
    e_CurvStruct_P1.set_size(1, i);
    stride_0_1 = (u_vec.size(1) != 1);
    stride_1_1 = (b_tmp.size(1) != 1);
    if (b_tmp.size(1) == 1) {
        loop_ub = u_vec.size(1);
    } else {
        loop_ub = b_tmp.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        e_CurvStruct_P1[i1] =
            b_CurvStruct_P1 * u_vec[i1 * stride_0_1] + b_CurvStruct_P0 * b_tmp[i1 * stride_1_1];
    }
    if (b_tmp.size(1) == 1) {
        i2 = u_vec.size(1);
    } else {
        i2 = b_tmp.size(1);
    }
    f_CurvStruct_P1.set_size(1, i2);
    b_stride_0_1 = (u_vec.size(1) != 1);
    b_stride_1_1 = (b_tmp.size(1) != 1);
    if (b_tmp.size(1) == 1) {
        b_loop_ub = u_vec.size(1);
    } else {
        b_loop_ub = b_tmp.size(1);
    }
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        f_CurvStruct_P1[i3] =
            c_CurvStruct_P1 * u_vec[i3 * b_stride_0_1] + c_CurvStruct_P0 * b_tmp[i3 * b_stride_1_1];
    }
    if (b_tmp.size(1) == 1) {
        i4 = u_vec.size(1);
    } else {
        i4 = b_tmp.size(1);
    }
    g_CurvStruct_P1.set_size(1, i4);
    c_stride_0_1 = (u_vec.size(1) != 1);
    c_stride_1_1 = (b_tmp.size(1) != 1);
    if (b_tmp.size(1) == 1) {
        c_loop_ub = u_vec.size(1);
    } else {
        c_loop_ub = b_tmp.size(1);
    }
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        g_CurvStruct_P1[i5] =
            d_CurvStruct_P1 * u_vec[i5 * c_stride_0_1] + d_CurvStruct_P0 * b_tmp[i5 * c_stride_1_1];
    }
    r0D.set_size(3, e_CurvStruct_P1.size(1));
    d_loop_ub = e_CurvStruct_P1.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        r0D[3 * i6] = e_CurvStruct_P1[i6];
    }
    e_loop_ub = f_CurvStruct_P1.size(1);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        r0D[3 * i7 + 1] = f_CurvStruct_P1[i7];
    }
    f_loop_ub = g_CurvStruct_P1.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        r0D[3 * i8 + 2] = g_CurvStruct_P1[i8];
    }
}

} // namespace ocn

//
// File trailer for cat.cpp
//
// [EOF]
//
