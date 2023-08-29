//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:29:37
//

// Include Files
#include "SplineLengthApproxGL_tot.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : CurvStruct *in1
//                const ::coder::array<double, 2U> &in2
//                int in3
//                int in7
//                int in8
//                int in11
// Return Type  : void
//
namespace ocn {
void binary_expand_op(CurvStruct *in1, const ::coder::array<double, 2U> &in2, int in3, int in7,
                      int in8, int in11)
{
    int b_in11;
    int c_in11;
    int d_in11;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    if (in11 + 1 == 1) {
        b_in11 = (in8 - in7) + 1;
    } else {
        b_in11 = in11 + 1;
    }
    if (b_in11 == 1) {
        c_in11 = in2.size(1);
    } else if (in11 + 1 == 1) {
        c_in11 = (in8 - in7) + 1;
    } else {
        c_in11 = in11 + 1;
    }
    in1->sp.Lk.set_size(1, c_in11);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = ((in8 - in7) + 1 != 1);
    stride_2_1 = (in11 + 1 != 1);
    if (in11 + 1 == 1) {
        d_in11 = (in8 - in7) + 1;
    } else {
        d_in11 = in11 + 1;
    }
    if (d_in11 == 1) {
        loop_ub = in2.size(1);
    } else if (in11 + 1 == 1) {
        loop_ub = (in8 - in7) + 1;
    } else {
        loop_ub = in11 + 1;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1->sp.Lk[i] =
            in2[i * stride_0_1] *
            (in1->sp.knots[(in3 + in7) + i * stride_1_1] - in1->sp.knots[in3 + i * stride_2_1]) /
            2.0;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
void c_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
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
    in1.set_size(5, i);
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
        __m128d r;
        __m128d r1;
        __m128d r2;
        r = _mm_loadu_pd((const double *)&in2[5 * aux_0_1]);
        r1 = _mm_loadu_pd((const double *)&in3[5 * aux_1_1]);
        r2 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&in1[5 * i1], _mm_div_pd(_mm_add_pd(r, r1), r2));
        r = _mm_loadu_pd((const double *)&in2[5 * aux_0_1 + 2]);
        r1 = _mm_loadu_pd((const double *)&in3[5 * aux_1_1 + 2]);
        _mm_storeu_pd(&in1[5 * i1 + 2], _mm_div_pd(_mm_add_pd(r, r1), r2));
        in1[5 * i1 + 4] = (in2[5 * aux_0_1 + 4] + in3[5 * aux_1_1 + 4]) / 2.0;
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
