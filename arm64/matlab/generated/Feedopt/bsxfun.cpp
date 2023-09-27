//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "bsxfun.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &a
//                const double b[5]
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
namespace ocn {
namespace coder {
void bsxfun(const ::coder::array<double, 2U> &a, const double b[5], ::coder::array<double, 2U> &c)
{
    c.set_size(5, a.size(1));
    if (a.size(1) != 0) {
        int acoef;
        int i;
        acoef = (a.size(1) != 1);
        i = a.size(1) - 1;
        for (int k{0}; k <= i; k++) {
            int varargin_2;
            varargin_2 = acoef * k;
            for (int b_k{0}; b_k < 5; b_k++) {
                c[b_k + 5 * k] = a[varargin_2] * b[b_k];
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
