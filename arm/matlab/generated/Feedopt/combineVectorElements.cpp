//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: combineVectorElements.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "combineVectorElements.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
namespace ocn {
namespace coder {
double combineVectorElements(const ::coder::array<double, 1U> &x)
{
    double y;
    int vlen;
    vlen = x.size(0);
    if (x.size(0) == 0) {
        y = 0.0;
    } else {
        double b_y;
        int firstBlockLength;
        int lastBlockLength;
        int nblocks;
        if (x.size(0) <= 1024) {
            firstBlockLength = x.size(0);
            lastBlockLength = 0;
            nblocks = 1;
        } else {
            firstBlockLength = 1024;
            nblocks = x.size(0) / 1024;
            lastBlockLength = x.size(0) - (nblocks << 10);
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

} // namespace coder
} // namespace ocn

//
// File trailer for combineVectorElements.cpp
//
// [EOF]
//
