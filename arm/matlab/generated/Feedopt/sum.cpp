//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
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
    int vlen;
    int xsubs_idx_1;
    int ysubs_idx_1;
    vlen = x.size(0);
    if ((x.size(0) == 0) || (x.size(1) == 0)) {
        int loop_ub;
        y.set_size(1, x.size(1));
        loop_ub = x.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            y[i1] = 0.0;
        }
    } else {
        int firstBlockLength;
        int i;
        int lastBlockLength;
        int nblocks;
        y.set_size(1, x.size(1));
        i = x.size(1);
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
        for (int k{0}; k < i; k++) {
            y[k] = x[x.size(0) * k];
            for (int b_k{2}; b_k <= firstBlockLength; b_k++) {
                if (vlen >= 2) {
                    ysubs_idx_1 = k + 1;
                    y[k] = y[k] + x[(b_k + x.size(0) * k) - 1];
                }
            }
            if (2 <= nblocks) {
                xsubs_idx_1 = k + 1;
                ysubs_idx_1 = k + 1;
            }
            for (int ib{2}; ib <= nblocks; ib++) {
                double bsum;
                int hi;
                int offset;
                offset = (ib - 1) << 10;
                bsum = x[offset + x.size(0) * (xsubs_idx_1 - 1)];
                if (ib == nblocks) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (int c_k{2}; c_k <= hi; c_k++) {
                    double b_bsum;
                    b_bsum = bsum;
                    if (vlen >= 2) {
                        b_bsum = bsum + x[((offset + c_k) + x.size(0) * k) - 1];
                    }
                    bsum = b_bsum;
                }
                y[ysubs_idx_1 - 1] = y[ysubs_idx_1 - 1] + bsum;
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
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
//                double y[5]
// Return Type  : void
//
void sum(const ::coder::array<double, 2U> &x, double y[5])
{
    int vlen;
    int xsubs_idx_1;
    short ysubs_idx_1;
    vlen = x.size(0);
    if (x.size(0) == 0) {
        for (int i{0}; i < 5; i++) {
            y[i] = 0.0;
        }
    } else {
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
        for (int k{0}; k < 5; k++) {
            y[k] = x[x.size(0) * k];
            for (int b_k{2}; b_k <= firstBlockLength; b_k++) {
                if (vlen >= 2) {
                    ysubs_idx_1 = static_cast<short>(k + 1);
                    y[k] += x[(b_k + x.size(0) * k) - 1];
                }
            }
            if (2 <= nblocks) {
                xsubs_idx_1 = k + 1;
                ysubs_idx_1 = static_cast<short>(k + 1);
            }
            for (int ib{2}; ib <= nblocks; ib++) {
                double bsum;
                int hi;
                int offset;
                offset = (ib - 1) << 10;
                bsum = x[offset + x.size(0) * (xsubs_idx_1 - 1)];
                if (ib == nblocks) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (int c_k{2}; c_k <= hi; c_k++) {
                    double b_bsum;
                    b_bsum = bsum;
                    if (vlen >= 2) {
                        b_bsum = bsum + x[((offset + c_k) + x.size(0) * k) - 1];
                    }
                    bsum = b_bsum;
                }
                y[ysubs_idx_1 - 1] += bsum;
            }
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
