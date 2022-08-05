//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcAlpha0.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "CalcAlpha0.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : double t12_data[]
//                int *t12_size
//                const double CoefPS[16]
//                const double alpha1_t_data[]
//                const int *alpha1_t_size
//                const ::coder::array<double, 1U> &r
//                const ::coder::array<double, 1U> &r1
// Return Type  : void
//
namespace ocn {
void binary_expand_op(double t12_data[], int *t12_size, const double CoefPS[16],
                      const double alpha1_t_data[], const int *alpha1_t_size,
                      const ::coder::array<double, 1U> &r, const ::coder::array<double, 1U> &r1)
{
    double b_CoefPS;
    double c_CoefPS;
    double d_CoefPS;
    double e_CoefPS;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    b_CoefPS = CoefPS[7];
    c_CoefPS = CoefPS[6];
    d_CoefPS = CoefPS[5];
    e_CoefPS = CoefPS[4];
    if (r1.size(0) == 1) {
        if (r.size(0) == 1) {
            *t12_size = *alpha1_t_size;
        } else {
            *t12_size = r.size(0);
        }
    } else {
        *t12_size = r1.size(0);
    }
    stride_0_0 = (*alpha1_t_size != 1);
    stride_1_0 = (r.size(0) != 1);
    stride_2_0 = (r1.size(0) != 1);
    if (r1.size(0) == 1) {
        if (r.size(0) == 1) {
            loop_ub = *alpha1_t_size;
        } else {
            loop_ub = r.size(0);
        }
    } else {
        loop_ub = r1.size(0);
    }
    for (int i{0}; i < loop_ub; i++) {
        t12_data[i] =
            ((b_CoefPS + alpha1_t_data[i * stride_0_0] * c_CoefPS) + d_CoefPS * r[i * stride_1_0]) +
            e_CoefPS * r1[i * stride_2_0];
    }
}

} // namespace ocn

//
// File trailer for CalcAlpha0.cpp
//
// [EOF]
//
