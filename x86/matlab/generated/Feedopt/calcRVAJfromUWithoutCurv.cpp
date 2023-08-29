//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromUWithoutCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

// Include Files
#include "calcRVAJfromUWithoutCurv.h"
#include "coder_array.h"
#include <emmintrin.h>

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
        int scalarLB;
        int vectorUB;
        b_loop_ub = in2.size(0);
        scalarLB = (b_loop_ub / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i2{0}; i2 <= vectorUB; i2 += 2) {
            __m128d r;
            r = _mm_loadu_pd((const double *)&in2[i2 + in2.size(0) * aux_0_1]);
            _mm_storeu_pd(&in1[i2 + in1.size(0) * i1], _mm_mul_pd(r, _mm_set1_pd(in3[aux_1_1])));
        }
        for (int i2{scalarLB}; i2 < b_loop_ub; i2++) {
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
//                double in8
//                const unsigned int in9[2]
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3, const ::coder::array<double, 2U> &in4,
                      const ::coder::array<double, 2U> &in5, const ::coder::array<double, 2U> &in6,
                      const ::coder::array<double, 2U> &in7, double in8, const unsigned int in9[2])
{
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int aux_3_1;
    int aux_4_1;
    int aux_5_1;
    int b_unnamed_idx_1;
    int c_unnamed_idx_1;
    int d_unnamed_idx_1;
    int i;
    int i1;
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
    int unnamed_idx_1;
    unnamed_idx_1 = static_cast<int>(in9[1]);
    if (in7.size(0) == 1) {
        if (in4.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in4.size(0);
        }
    } else {
        i = in7.size(0);
    }
    if (unnamed_idx_1 == 1) {
        b_unnamed_idx_1 = in7.size(1);
    } else {
        b_unnamed_idx_1 = unnamed_idx_1;
    }
    if (in6.size(1) == 1) {
        if (in5.size(1) == 1) {
            i1 = in4.size(1);
        } else {
            i1 = in5.size(1);
        }
    } else {
        i1 = in6.size(1);
    }
    if (b_unnamed_idx_1 == 1) {
        if (i1 == 1) {
            if (in3.size(1) == 1) {
                c_unnamed_idx_1 = in2.size(1);
            } else {
                c_unnamed_idx_1 = in3.size(1);
            }
        } else if (in6.size(1) == 1) {
            if (in5.size(1) == 1) {
                c_unnamed_idx_1 = in4.size(1);
            } else {
                c_unnamed_idx_1 = in5.size(1);
            }
        } else {
            c_unnamed_idx_1 = in6.size(1);
        }
    } else if (unnamed_idx_1 == 1) {
        c_unnamed_idx_1 = in7.size(1);
    } else {
        c_unnamed_idx_1 = unnamed_idx_1;
    }
    in1.set_size(i, c_unnamed_idx_1);
    stride_0_0 = (in2.size(0) != 1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    stride_2_0 = (in4.size(0) != 1);
    stride_2_1 = (in4.size(1) != 1);
    stride_3_1 = (in5.size(1) != 1);
    stride_4_1 = (in6.size(1) != 1);
    stride_5_0 = (in7.size(0) != 1);
    stride_5_1 = (in7.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    aux_3_1 = 0;
    aux_4_1 = 0;
    aux_5_1 = 0;
    if (unnamed_idx_1 == 1) {
        d_unnamed_idx_1 = in7.size(1);
    } else {
        d_unnamed_idx_1 = unnamed_idx_1;
    }
    if (d_unnamed_idx_1 == 1) {
        int i2;
        if (in6.size(1) == 1) {
            if (in5.size(1) == 1) {
                i2 = in4.size(1);
            } else {
                i2 = in5.size(1);
            }
        } else {
            i2 = in6.size(1);
        }
        if (i2 == 1) {
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
    } else if (unnamed_idx_1 == 1) {
        loop_ub = in7.size(1);
    } else {
        loop_ub = unnamed_idx_1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
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
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            in1[i4 + in1.size(0) * i3] =
                (in2[i4 * stride_0_0 + in2.size(0) * aux_0_1] * in3[aux_1_1] +
                 3.0 * in4[i4 * stride_2_0 + in4.size(0) * aux_2_1] * in5[aux_3_1] * in6[aux_4_1]) +
                in7[i4 * stride_5_0 + in7.size(0) * aux_5_1] * in8;
        }
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
