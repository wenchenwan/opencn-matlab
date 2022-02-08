//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: diff.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "diff.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void diff(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
{
    int dimSize;
    dimSize = x.size(1);
    if (x.size(1) == 0) {
        y.set_size(1, 0);
    } else {
        int b_y;
        int u0;
        u0 = x.size(1) - 1;
        if (u0 <= 1) {
            b_y = u0;
        } else {
            b_y = 1;
        }
        if (b_y < 1) {
            y.set_size(1, 0);
        } else {
            y.set_size(1, x.size(1) - 1);
            if (x.size(1) - 1 != 0) {
                double work_data;
                work_data = x[0];
                for (int m{2}; m <= dimSize; m++) {
                    double d;
                    double tmp1;
                    tmp1 = x[m - 1];
                    d = tmp1;
                    tmp1 -= work_data;
                    work_data = d;
                    y[m - 2] = tmp1;
                }
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for diff.cpp
//
// [EOF]
//
