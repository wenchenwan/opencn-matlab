//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: vecnorm.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "vecnorm.h"
#include "norm.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void vecnorm(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 1U> xv;
    int b_loop_ub;
    int hi;
    int loop_ub;
    int nx;
    int outsize_idx_0;
    y.set_size(1, x.size(1));
    loop_ub = x.size(1);
    for (int i{0}; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    hi = x.size(1);
    if (0 <= x.size(1) - 1) {
        nx = x.size(0);
        outsize_idx_0 = x.size(0);
        b_loop_ub = x.size(0);
    }
    for (int k{0}; k < hi; k++) {
        xv.set_size(outsize_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            xv[i1] = 0.0;
        }
        for (int b_k{0}; b_k < nx; b_k++) {
            xv[b_k] = x[b_k + x.size(0) * k];
        }
        y[k] = b_norm(xv);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for vecnorm.cpp
//
// [EOF]
//
