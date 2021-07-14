//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
namespace ocn {
namespace coder {
double sum(const ::coder::array<double, 2U> &x)
{
    double y;
    int vlen;
    vlen = x.size(1);
    if (x.size(1) == 0) {
        y = 0.0;
    } else {
        double b_y;
        int firstBlockLength;
        int lastBlockLength;
        int nblocks;
        if (x.size(1) <= 1024) {
            firstBlockLength = x.size(1);
            lastBlockLength = 0;
            nblocks = 1;
        } else {
            firstBlockLength = 1024;
            nblocks = x.size(1) / 1024;
            lastBlockLength = x.size(1) - (nblocks << 10);
            if (lastBlockLength > 0) {
                nblocks++;
            } else {
                lastBlockLength = 1024;
            }
        }
        b_y = x[0];
        for (int k{2}; k <= firstBlockLength; k++) {
            double c_y;
            c_y = b_y;
            if (vlen >= 2) {
                c_y = b_y + x[k - 1];
            }
            b_y = c_y;
        }
        for (int ib{2}; ib <= nblocks; ib++) {
            double bsum;
            int hi;
            int offset;
            offset = (ib - 1) << 10;
            bsum = x[offset];
            if (ib == nblocks) {
                hi = lastBlockLength;
            } else {
                hi = 1024;
            }
            for (int b_k{2}; b_k <= hi; b_k++) {
                double b_bsum;
                b_bsum = bsum;
                if (vlen >= 2) {
                    b_bsum = bsum + x[(offset + b_k) - 1];
                }
                bsum = b_bsum;
            }
            b_y += bsum;
        }
        y = b_y;
    }
    return y;
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
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
