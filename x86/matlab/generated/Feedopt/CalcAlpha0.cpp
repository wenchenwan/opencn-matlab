//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcAlpha0.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

// Include Files
#include "CalcAlpha0.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const double in3_data[]
//                const int *in3_size
//                const ::coder::array<double, 1U> &in4
//                const ::coder::array<double, 1U> &in5
// Return Type  : void
//
namespace ocn {
void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                      const double in3_data[], const int *in3_size,
                      const ::coder::array<double, 1U> &in4, const ::coder::array<double, 1U> &in5)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    b_in2 = in2[7];
    c_in2 = in2[6];
    d_in2 = in2[5];
    e_in2 = in2[4];
    if (in5.size(0) == 1) {
        if (in4.size(0) == 1) {
            *in1_size = *in3_size;
        } else {
            *in1_size = in4.size(0);
        }
    } else {
        *in1_size = in5.size(0);
    }
    stride_0_0 = (*in3_size != 1);
    stride_1_0 = (in4.size(0) != 1);
    stride_2_0 = (in5.size(0) != 1);
    if (in5.size(0) == 1) {
        if (in4.size(0) == 1) {
            loop_ub = *in3_size;
        } else {
            loop_ub = in4.size(0);
        }
    } else {
        loop_ub = in5.size(0);
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = ((b_in2 + in3_data[i * stride_0_0] * c_in2) + d_in2 * in4[i * stride_1_0]) +
                      e_in2 * in5[i * stride_2_0];
    }
}

} // namespace ocn

//
// File trailer for CalcAlpha0.cpp
//
// [EOF]
//
