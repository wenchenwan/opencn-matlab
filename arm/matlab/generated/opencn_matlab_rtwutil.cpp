//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_rtwutil.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 10:58:42
//

// Include Files
#include "opencn_matlab_rtwutil.h"
#include <cmath>
#include <math.h>

// Function Definitions
//
// Arguments    : double u1
//                unsigned int y[]
// Return Type  : void
//
namespace ocn {
void Double2MultiWord(double u1, unsigned int y[])
{
    double b_y0;
    double b_yn;
    int cb;
    int currExp;
    int i;
    int msl;
    int prevExp;
    bool isNegative;
    isNegative = (u1 < 0.0);
    b_yn = frexp(u1, &currExp);
    if (currExp <= 0) {
        msl = -1;
    } else {
        msl = (currExp - 1) / 32;
    }
    cb = 1;
    for (i = msl + 1; i < 2; i++) {
        y[i] = 0U;
    }
    if (isNegative) {
        b_y0 = -b_yn;
    } else {
        b_y0 = b_yn;
    }
    prevExp = 32 * msl;
    for (i = msl; i >= 0; i--) {
        double yd;
        b_y0 = std::ldexp(b_y0, currExp - prevExp);
        yd = std::floor(b_y0);
        b_y0 -= yd;
        if (i < 2) {
            y[i] = static_cast<unsigned int>(yd);
        }
        currExp = prevExp;
        prevExp -= 32;
    }
    if (isNegative) {
        for (i = 0; i < 2; i++) {
            unsigned int u1i;
            unsigned int yi;
            u1i = ~y[i];
            yi = u1i + cb;
            y[i] = yi;
            cb = (yi < u1i);
        }
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordAdd(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    int carry{0};
    for (int i{0}; i < 2; i++) {
        unsigned int u1i;
        unsigned int yi;
        u1i = u1[i];
        yi = (u1i + u2[i]) + carry;
        y[i] = yi;
        if (static_cast<unsigned int>(carry) != 0U) {
            carry = (yi <= u1i);
        } else {
            carry = (yi < u1i);
        }
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordAnd(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    for (int i{0}; i < 2; i++) {
        y[i] = u1[i] & u2[i];
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordSub(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    int borrow{0};
    for (int i{0}; i < 2; i++) {
        unsigned int u1i;
        unsigned int yi;
        u1i = u1[i];
        yi = (u1i - u2[i]) - borrow;
        y[i] = yi;
        if (static_cast<unsigned int>(borrow) != 0U) {
            borrow = (yi >= u1i);
        } else {
            borrow = (yi > u1i);
        }
    }
}

//
// Arguments    : int u
//                unsigned int y[]
// Return Type  : void
//
void sLong2MultiWord(int u, unsigned int y[])
{
    y[0] = static_cast<unsigned int>(u);
    if (u < 0) {
        y[1] = MAX_uint32_T;
    } else {
        y[1] = 0U;
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : int
//
int uMultiWordCmp(const unsigned int u1[], const unsigned int u2[])
{
    int cmp;
    int i;
    cmp = 0;
    i = 2;
    while ((cmp == 0) && (i > 0)) {
        unsigned int u1i;
        unsigned int u2i;
        i--;
        u1i = u1[i];
        u2i = u2[i];
        if (u1i != u2i) {
            if (u1i > u2i) {
                cmp = 1;
            } else {
                cmp = -1;
            }
        }
    }
    return cmp;
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
bool uMultiWordGe(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) >= 0;
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
bool uMultiWordNe(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) != 0;
}

} // namespace ocn

//
// File trailer for opencn_matlab_rtwutil.cpp
//
// [EOF]
//
