//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: diag.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "diag.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &v
//                ::coder::array<double, 1U> &d
// Return Type  : void
//
namespace ocn {
namespace coder {
void diag(const ::coder::array<double, 2U> &v, ::coder::array<double, 1U> &d)
{
    if (v.size(0) < 1) {
        d.set_size(0);
    } else {
        int b_i;
        int dlen;
        int i;
        if (v.size(0) > 1) {
            int u0;
            int u1;
            u0 = v.size(0) - 1;
            u1 = v.size(1);
            if (u0 <= u1) {
                dlen = u0;
            } else {
                dlen = u1;
            }
            i = 1;
        } else {
            dlen = 0;
            i = 0;
        }
        d.set_size(dlen);
        b_i = dlen - 1;
        for (int k{0}; k <= b_i; k++) {
            d[k] = v[(i + k) + v.size(0) * k];
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for diag.cpp
//
// [EOF]
//
