//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 16:00:50
//

// Include Files
#include "SplineLengthApproxGL_tot.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : CurvStruct *spline
//                const ::coder::array<double, 2U> &y
//                int i4
//                int i5
//                int i6
//                int i7
// Return Type  : void
//
namespace ocn {
void binary_expand_op(CurvStruct *spline, const ::coder::array<double, 2U> &y, int i4, int i5,
                      int i6, int i7)
{
    int i;
    int i1;
    int i2;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    if (i7 + 1 == 1) {
        i = (i6 - i5) + 1;
    } else {
        i = i7 + 1;
    }
    if (i == 1) {
        i1 = y.size(1);
    } else if (i7 + 1 == 1) {
        i1 = (i6 - i5) + 1;
    } else {
        i1 = i7 + 1;
    }
    spline->sp.Lk.set_size(1, i1);
    stride_0_1 = (y.size(1) != 1);
    stride_1_1 = ((i6 - i5) + 1 != 1);
    stride_2_1 = (i7 + 1 != 1);
    if (i7 + 1 == 1) {
        i2 = (i6 - i5) + 1;
    } else {
        i2 = i7 + 1;
    }
    if (i2 == 1) {
        loop_ub = y.size(1);
    } else if (i7 + 1 == 1) {
        loop_ub = (i6 - i5) + 1;
    } else {
        loop_ub = i7 + 1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        spline->sp.Lk[i3] = y[i3 * stride_0_1] *
                            (spline->sp.knots[(i4 + i5) + i3 * stride_1_1] -
                             spline->sp.knots[i4 + i3 * stride_2_1]) /
                            2.0;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &Umat
//                const ::coder::array<double, 2U> &c
//                const ::coder::array<double, 2U> &b_c
// Return Type  : void
//
void c_binary_expand_op(::coder::array<double, 2U> &Umat, const ::coder::array<double, 2U> &c,
                        const ::coder::array<double, 2U> &b_c)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (b_c.size(1) == 1) {
        i = c.size(1);
    } else {
        i = b_c.size(1);
    }
    Umat.set_size(5, i);
    stride_0_1 = (c.size(1) != 1);
    stride_1_1 = (b_c.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (b_c.size(1) == 1) {
        loop_ub = c.size(1);
    } else {
        loop_ub = b_c.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        for (int i2{0}; i2 < 5; i2++) {
            Umat[i2 + 5 * i1] = (c[i2 + 5 * aux_0_1] + b_c[i2 + 5 * aux_1_1]) / 2.0;
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

} // namespace ocn

//
// File trailer for SplineLengthApproxGL_tot.cpp
//
// [EOF]
//
