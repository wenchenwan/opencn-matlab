//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unsafeSxfun.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 13:16:18
//

// Include Files
#include "unsafeSxfun.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &delta_CW
//                const ::coder::array<double, 1U> &r1
//                const ::coder::array<double, 1U> &r2
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 1U> &delta_CW, const ::coder::array<double, 1U> &r1,
                      const ::coder::array<double, 1U> &r2)
{
    ::coder::array<double, 1U> r;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (r2.size(0) == 1) {
        i = r1.size(0);
    } else {
        i = r2.size(0);
    }
    r.set_size(i);
    stride_0_0 = (r1.size(0) != 1);
    stride_1_0 = (r2.size(0) != 1);
    if (r2.size(0) == 1) {
        loop_ub = r1.size(0);
    } else {
        loop_ub = r2.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        r[i1] = r1[i1 * stride_0_0] - r2[i1 * stride_1_0];
    }
    delta_CW.set_size(r.size(0));
    b_loop_ub = r.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        double varargin_1;
        double varargout_1;
        varargin_1 = r[i2];
        if (varargin_1 == 0.0) {
            varargout_1 = 0.0;
        } else {
            varargout_1 = std::fmod(varargin_1, 360.0);
            if (varargout_1 == 0.0) {
                varargout_1 = 0.0;
            } else if (varargin_1 < 0.0) {
                varargout_1 += 360.0;
            }
        }
        delta_CW[i2] = varargout_1;
    }
}

} // namespace ocn

//
// File trailer for unsafeSxfun.cpp
//
// [EOF]
//
