//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isSameGeometry.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
//

// Include Files
#include "isSameGeometry.h"
#include "opencn_matlab_types1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &in1
//                const CurvStruct *in2
//                const CurvStruct *in3
// Return Type  : void
//
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &in1, const CurvStruct *in2, const CurvStruct *in3)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in3->CoeffP5.size(0) == 1) {
        i = in2->CoeffP5.size(0);
    } else {
        i = in3->CoeffP5.size(0);
    }
    in1.set_size(i, 6);
    stride_0_0 = (in2->CoeffP5.size(0) != 1);
    stride_1_0 = (in3->CoeffP5.size(0) != 1);
    if (in3->CoeffP5.size(0) == 1) {
        loop_ub = in2->CoeffP5.size(0);
    } else {
        loop_ub = in3->CoeffP5.size(0);
    }
    for (int i1{0}; i1 < 6; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            in1[i2 + in1.size(0) * i1] =
                (in2->CoeffP5[i2 * stride_0_0 + in2->CoeffP5.size(0) * i1] !=
                 in3->CoeffP5[i2 * stride_1_0 + in3->CoeffP5.size(0) * i1]);
        }
    }
}

} // namespace ocn

//
// File trailer for isSameGeometry.cpp
//
// [EOF]
//
