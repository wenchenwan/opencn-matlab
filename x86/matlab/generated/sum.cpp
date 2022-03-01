//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:00:11
//

// Include Files
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(1, 0);
    } else {
        int i;
        y.set_size(1, x.size(1));
        i = x.size(1);
        for (int k{0}; k < i; k++) {
            y[k] = x[3 * k];
            y[k] = y[k] + x[3 * k + 1];
            y[k] = y[k] + x[3 * k + 2];
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for sum.cpp
//
// [EOF]
//
