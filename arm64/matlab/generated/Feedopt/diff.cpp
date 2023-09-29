
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: diff.cpp
//
// MATLAB Coder version            : 5.4
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
    int b_y;
    int dimSize;
    int u0;
    dimSize = x.size(0);
    u0 = x.size(0) - 1;
    if (u0 <= 1) {
        b_y = u0;
    } else {
        b_y = 1;
    }
    if (b_y < 1) {
        y.set_size(0, x.size(1));
    } else {
        y.set_size(x.size(0) - 1, x.size(1));
        if ((x.size(0) - 1 != 0) && (x.size(1) != 0)) {
            int iyStart;
            int nHigh;
            nHigh = x.size(1);
            iyStart = 0;
            for (int r{0}; r < nHigh; r++) {
                double work_data;
                int ixLead;
                ixLead = r * dimSize + 1;
                work_data = x[r * dimSize];
                for (int m{2}; m <= dimSize; m++) {
                    double d;
                    double tmp1;
                    tmp1 = x[(ixLead + m) - 2];
                    d = tmp1;
                    tmp1 -= work_data;
                    work_data = d;
                    y[(iyStart + m) - 2] = tmp1;
                }
                iyStart = (iyStart + dimSize) - 1;
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
