//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyder.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 13-Jul-2022 14:15:57
//

// Include Files
#include "mypolyder.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &p5_2D
//                const ::coder::array<double, 2U> &p5_1D
//                const ::coder::array<signed char, 2U> &b
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &p5_2D, const ::coder::array<double, 2U> &p5_1D,
                        const ::coder::array<signed char, 2U> &b)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = p5_1D.size(0);
    if (b.size(0) == 1) {
        i1 = i;
    } else {
        i1 = b.size(0);
    }
    p5_2D.set_size(i1, 4);
    stride_0_0 = (i != 1);
    stride_1_0 = (b.size(0) != 1);
    if (b.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = b.size(0);
    }
    for (int i2{0}; i2 < 4; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            p5_2D[i3 + p5_2D.size(0) * i2] =
                p5_1D[i3 * stride_0_0 + p5_1D.size(0) * i2] *
                static_cast<double>(b[i3 * stride_1_0 + b.size(0) * i2]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &p5_3D
//                const ::coder::array<double, 2U> &p5_2D
//                const ::coder::array<signed char, 2U> &b
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &p5_3D, const ::coder::array<double, 2U> &p5_2D,
                      const ::coder::array<signed char, 2U> &b)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = p5_2D.size(0);
    if (b.size(0) == 1) {
        i1 = i;
    } else {
        i1 = b.size(0);
    }
    p5_3D.set_size(i1, 3);
    stride_0_0 = (i != 1);
    stride_1_0 = (b.size(0) != 1);
    if (b.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = b.size(0);
    }
    for (int i2{0}; i2 < 3; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            p5_3D[i3 + p5_3D.size(0) * i2] =
                p5_2D[i3 * stride_0_0 + p5_2D.size(0) * i2] *
                static_cast<double>(b[i3 * stride_1_0 + b.size(0) * i2]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &p5_1D
//                const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                const ::coder::array<signed char, 2U> &b
// Return Type  : void
//
void c_binary_expand_op(::coder::array<double, 2U> &p5_1D,
                        const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                        const ::coder::array<signed char, 2U> &b)
{
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    i = CurvStruct_CoeffP5.size(0);
    if (b.size(0) == 1) {
        i1 = i;
    } else {
        i1 = b.size(0);
    }
    p5_1D.set_size(i1, 5);
    stride_0_0 = (i != 1);
    stride_1_0 = (b.size(0) != 1);
    if (b.size(0) == 1) {
        loop_ub = i;
    } else {
        loop_ub = b.size(0);
    }
    for (int i2{0}; i2 < 5; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            p5_1D[i3 + p5_1D.size(0) * i2] =
                CurvStruct_CoeffP5[i3 * stride_0_0 + CurvStruct_CoeffP5.size(0) * i2] *
                static_cast<double>(b[i3 * stride_1_0 + b.size(0) * i2]);
        }
    }
}

} // namespace ocn

//
// File trailer for mypolyder.cpp
//
// [EOF]
//
