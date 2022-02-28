//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 14:58:55
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &r_0D
//                const ::coder::array<double, 2U> &r4
//                const ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &r_0D, const ::coder::array<double, 2U> &r4,
                      const ::coder::array<double, 2U> &b)
{
    ::coder::array<double, 2U> r;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    if (b.size(1) == 1) {
        if (r_0D.size(1) == 1) {
            i = r4.size(1);
        } else {
            i = r_0D.size(1);
        }
    } else {
        i = b.size(1);
    }
    r.set_size(3, i);
    stride_0_1 = (r4.size(1) != 1);
    stride_1_1 = (r_0D.size(1) != 1);
    stride_2_1 = (b.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (b.size(1) == 1) {
        if (r_0D.size(1) == 1) {
            loop_ub = r4.size(1);
        } else {
            loop_ub = r_0D.size(1);
        }
    } else {
        loop_ub = b.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        __m128d r1;
        __m128d r2;
        __m128d r3;
        r1 = _mm_loadu_pd((const double *)&r4[3 * aux_0_1]);
        r2 = _mm_loadu_pd(&r_0D[3 * aux_1_1]);
        r3 = _mm_loadu_pd((const double *)&b[3 * aux_2_1]);
        _mm_storeu_pd(&r[3 * i1], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
        r[3 * i1 + 2] = r4[3 * aux_0_1 + 2] * r_0D[3 * aux_1_1 + 2] + b[3 * aux_2_1 + 2];
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    r_0D.set_size(3, r.size(1));
    b_loop_ub = r.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        r_0D[3 * i2] = r[3 * i2];
        r_0D[3 * i2 + 1] = r[3 * i2 + 1];
        r_0D[3 * i2 + 2] = r[3 * i2 + 2];
    }
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
