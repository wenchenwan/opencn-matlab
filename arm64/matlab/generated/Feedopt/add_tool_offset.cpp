//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: add_tool_offset.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

// Include Files
#include "add_tool_offset.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// Arguments    : CurvStruct *in1
//                const FeedoptContext *in2
//                double in3
//                double in4
//                double in5
// Return Type  : void
//
namespace ocn {
void binary_expand_op(CurvStruct *in1, const FeedoptContext *in2, double in3, double in4,
                      double in5)
{
    double b_in3[3];
    double in1_data[3];
    int in1_size;
    int loop_ub;
    int stride_0_0;
    b_in3[0] = in3;
    b_in3[1] = in4;
    b_in3[2] = in5;
    in1_size = in2->cfg.indCart.size[0];
    stride_0_0 = (in2->cfg.indCart.size[0] != 1);
    loop_ub = in2->cfg.indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = in1->R0[in2->cfg.indCart.data[i * stride_0_0] - 1] + b_in3[i];
    }
    for (int i1{0}; i1 < in1_size; i1++) {
        in1->R0[in2->cfg.indCart.data[i1] - 1] = in1_data[i1];
    }
}

//
// Arguments    : CurvStruct *in1
//                const FeedoptContext *in2
//                const double in3[3]
// Return Type  : void
//
void binary_expand_op(CurvStruct *in1, const FeedoptContext *in2, const double in3[3])
{
    double in1_data[3];
    int in1_size;
    int loop_ub;
    int stride_0_0;
    in1_size = in2->cfg.indCart.size[0];
    stride_0_0 = (in2->cfg.indCart.size[0] != 1);
    loop_ub = in2->cfg.indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = in1->R1[in2->cfg.indCart.data[i * stride_0_0] - 1] + in3[i];
    }
    for (int i1{0}; i1 < in1_size; i1++) {
        in1->R1[in2->cfg.indCart.data[i1] - 1] = in1_data[i1];
    }
}

} // namespace ocn

//
// File trailer for add_tool_offset.cpp
//
// [EOF]
//
