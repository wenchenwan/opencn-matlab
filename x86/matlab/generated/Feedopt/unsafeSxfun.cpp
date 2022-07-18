//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unsafeSxfun.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "unsafeSxfun.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &r
//                const ::coder::array<double, 1U> &r2D
//                double y
//                const ::coder::array<double, 1U> &r1D
//                double udd
//                double n
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 1U> &r, const ::coder::array<double, 1U> &r2D,
                      double y, const ::coder::array<double, 1U> &r1D, double udd, double n)
{
    ::coder::array<double, 1U> b_r2D;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (r1D.size(0) == 1) {
        i = r2D.size(0);
    } else {
        i = r1D.size(0);
    }
    b_r2D.set_size(i);
    stride_0_0 = (r2D.size(0) != 1);
    stride_1_0 = (r1D.size(0) != 1);
    stride_2_0 = (r1D.size(0) != 1);
    if (r1D.size(0) == 1) {
        loop_ub = r2D.size(0);
    } else {
        loop_ub = r1D.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_r2D[i1] =
            (r2D[i1 * stride_0_0] * y + r1D[i1 * stride_1_0] * udd) * (r1D[i1 * stride_2_0] / n);
    }
    r.set_size(b_r2D.size(0));
    b_loop_ub = b_r2D.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        double varargin_1;
        varargin_1 = b_r2D[i2];
        r[i2] = std::pow(varargin_1, 2.0);
    }
}

} // namespace ocn

//
// File trailer for unsafeSxfun.cpp
//
// [EOF]
//
