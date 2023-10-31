
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isSameGeometry.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "isSameGeometry.h"
#include "opencn_matlab_types111.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &in1
//                const CurvStruct *in2
//                const CurvStruct *in3
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<bool, 2U> &in1, const CurvStruct *in2, const CurvStruct *in3)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    if (in3->CoeffP5.size(0) == 1) {
        i = in2->CoeffP5.size(0);
    } else {
        i = in3->CoeffP5.size(0);
    }
    if (in3->CoeffP5.size(1) == 1) {
        i1 = in2->CoeffP5.size(1);
    } else {
        i1 = in3->CoeffP5.size(1);
    }
    in1.set_size(i, i1);
    stride_0_0 = (in2->CoeffP5.size(0) != 1);
    stride_0_1 = (in2->CoeffP5.size(1) != 1);
    stride_1_0 = (in3->CoeffP5.size(0) != 1);
    stride_1_1 = (in3->CoeffP5.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in3->CoeffP5.size(1) == 1) {
        loop_ub = in2->CoeffP5.size(1);
    } else {
        loop_ub = in3->CoeffP5.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int b_loop_ub;
        if (in3->CoeffP5.size(0) == 1) {
            b_loop_ub = in2->CoeffP5.size(0);
        } else {
            b_loop_ub = in3->CoeffP5.size(0);
        }
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            in1[i3 + in1.size(0) * i2] =
                (in2->CoeffP5[i3 * stride_0_0 + in2->CoeffP5.size(0) * aux_0_1] !=
                 in3->CoeffP5[i3 * stride_1_0 + in3->CoeffP5.size(0) * aux_1_1]);
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<bool, 1U> &in1
//                const CurvStruct *in2
//                const CurvStruct *in3
// Return Type  : void
//
void c_binary_expand_op(::coder::array<bool, 1U> &in1, const CurvStruct *in2, const CurvStruct *in3)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in3->R1.size(0) == 1) {
        i = in2->R1.size(0);
    } else {
        i = in3->R1.size(0);
    }
    in1.set_size(i);
    stride_0_0 = (in2->R1.size(0) != 1);
    stride_1_0 = (in3->R1.size(0) != 1);
    if (in3->R1.size(0) == 1) {
        loop_ub = in2->R1.size(0);
    } else {
        loop_ub = in3->R1.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[i1] = (in2->R1[i1 * stride_0_0] != in3->R1[i1 * stride_1_0]);
    }
}

//
// Arguments    : ::coder::array<bool, 1U> &in1
//                const CurvStruct *in2
//                const CurvStruct *in3
// Return Type  : void
//
void d_binary_expand_op(::coder::array<bool, 1U> &in1, const CurvStruct *in2, const CurvStruct *in3)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in3->R0.size(0) == 1) {
        i = in2->R0.size(0);
    } else {
        i = in3->R0.size(0);
    }
    in1.set_size(i);
    stride_0_0 = (in2->R0.size(0) != 1);
    stride_1_0 = (in3->R0.size(0) != 1);
    if (in3->R0.size(0) == 1) {
        loop_ub = in2->R0.size(0);
    } else {
        loop_ub = in3->R0.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[i1] = (in2->R0[i1 * stride_0_0] != in3->R0[i1 * stride_1_0]);
    }
}

} // namespace ocn

//
// File trailer for isSameGeometry.cpp
//
// [EOF]
//
