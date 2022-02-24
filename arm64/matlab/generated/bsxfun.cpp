//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:52:48
//

// Include Files
#include "bsxfun.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &a
//                const ::coder::array<double, 2U> &b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
namespace ocn {
namespace coder {
void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &b,
            ::coder::array<double, 2U> &c)
{
    int b_u0;
    int b_u1;
    int b_y;
    int csz_idx_1;
    int i;
    int u0;
    int u1;
    int y;
    u0 = b.size(1);
    u1 = a.size(1);
    if (u0 <= u1) {
        y = u0;
    } else {
        y = u1;
    }
    if (b.size(1) == 1) {
        csz_idx_1 = a.size(1);
    } else if (a.size(1) == 1) {
        csz_idx_1 = b.size(1);
    } else if (a.size(1) == b.size(1)) {
        csz_idx_1 = a.size(1);
    } else {
        csz_idx_1 = y;
    }
    b_u0 = b.size(1);
    b_u1 = a.size(1);
    if (b_u0 <= b_u1) {
        b_y = b_u0;
    } else {
        b_y = b_u1;
    }
    if (b.size(1) == 1) {
        i = a.size(1);
    } else if (a.size(1) == 1) {
        i = b.size(1);
    } else if (a.size(1) == b.size(1)) {
        i = a.size(1);
    } else {
        i = b_y;
    }
    c.set_size(3, i);
    if (csz_idx_1 != 0) {
        int acoef;
        int bcoef;
        int i1;
        acoef = (a.size(1) != 1);
        bcoef = (b.size(1) != 1);
        i1 = csz_idx_1 - 1;
        for (int k{0}; k <= i1; k++) {
            int varargin_2;
            int varargin_3;
            varargin_2 = acoef * k;
            varargin_3 = bcoef * k;
            c[3 * k] = a[3 * varargin_2] * b[varargin_3];
            c[3 * k + 1] = b[varargin_3] * a[3 * varargin_2 + 1];
            c[3 * k + 2] = b[varargin_3] * a[3 * varargin_2 + 2];
        }
    }
}

//
// Arguments    : const ::coder::array<double, 1U> &a
//                const ::coder::array<double, 2U> &b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
void bsxfun(const ::coder::array<double, 1U> &a, const ::coder::array<double, 2U> &b,
            ::coder::array<double, 2U> &c)
{
    int b_u0;
    int b_u1;
    int b_y;
    int i;
    int i1;
    int u0;
    int u1;
    int y;
    u0 = b.size(0);
    u1 = a.size(0);
    if (u0 <= u1) {
        y = u0;
    } else {
        y = u1;
    }
    if (b.size(0) == 1) {
        i = a.size(0);
    } else if (a.size(0) == 1) {
        i = b.size(0);
    } else if (a.size(0) == b.size(0)) {
        i = a.size(0);
    } else {
        i = y;
    }
    c.set_size(i, b.size(1));
    b_u0 = b.size(0);
    b_u1 = a.size(0);
    if (b_u0 <= b_u1) {
        b_y = b_u0;
    } else {
        b_y = b_u1;
    }
    if (b.size(0) == 1) {
        i1 = a.size(0);
    } else if (a.size(0) == 1) {
        i1 = b.size(0);
    } else if (a.size(0) == b.size(0)) {
        i1 = a.size(0);
    } else {
        i1 = b_y;
    }
    if ((i1 != 0) && (b.size(1) != 0)) {
        int bcoef;
        int i2;
        bcoef = (b.size(1) != 1);
        i2 = b.size(1) - 1;
        for (int k{0}; k <= i2; k++) {
            int acoef;
            int b_bcoef;
            int i3;
            int varargin_3;
            varargin_3 = bcoef * k;
            acoef = (a.size(0) != 1);
            b_bcoef = (b.size(0) != 1);
            i3 = c.size(0) - 1;
            for (int b_k{0}; b_k <= i3; b_k++) {
                c[b_k + c.size(0) * k] = a[acoef * b_k] * b[b_bcoef * b_k + b.size(0) * varargin_3];
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &a
//                const ::coder::array<double, 1U> &b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 1U> &b,
            ::coder::array<double, 2U> &c)
{
    int b_u0;
    int b_u1;
    int b_y;
    int i;
    int i1;
    int u0;
    int u1;
    int y;
    u0 = b.size(0);
    u1 = a.size(0);
    if (u0 <= u1) {
        y = u0;
    } else {
        y = u1;
    }
    if (b.size(0) == 1) {
        i = a.size(0);
    } else if (a.size(0) == 1) {
        i = b.size(0);
    } else if (a.size(0) == b.size(0)) {
        i = a.size(0);
    } else {
        i = y;
    }
    c.set_size(i, a.size(1));
    b_u0 = b.size(0);
    b_u1 = a.size(0);
    if (b_u0 <= b_u1) {
        b_y = b_u0;
    } else {
        b_y = b_u1;
    }
    if (b.size(0) == 1) {
        i1 = a.size(0);
    } else if (a.size(0) == 1) {
        i1 = b.size(0);
    } else if (a.size(0) == b.size(0)) {
        i1 = a.size(0);
    } else {
        i1 = b_y;
    }
    if ((i1 != 0) && (a.size(1) != 0)) {
        int acoef;
        int i2;
        acoef = (a.size(1) != 1);
        i2 = a.size(1) - 1;
        for (int k{0}; k <= i2; k++) {
            int b_acoef;
            int bcoef;
            int i3;
            int varargin_2;
            varargin_2 = acoef * k;
            b_acoef = (a.size(0) != 1);
            bcoef = (b.size(0) != 1);
            i3 = c.size(0) - 1;
            for (int b_k{0}; b_k <= i3; b_k++) {
                c[b_k + c.size(0) * k] = a[b_acoef * b_k + a.size(0) * varargin_2] * b[bcoef * b_k];
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
