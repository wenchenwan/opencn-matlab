//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_rtwutil.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "sinspace_rtwutil.h"
#include <cmath>
#include <cstring>
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
// Return Type  : double
//
double uMultiWord2Double(const unsigned int u1[])
{
    double y;
    int b_exp;
    y = 0.0;
    b_exp = 0;
    for (int i{0}; i < 2; i++) {
        y += std::ldexp(static_cast<double>(u1[i]), b_exp);
        b_exp += 32;
    }
    return y;
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
//                unsigned int n2
//                unsigned int y[]
// Return Type  : void
//
void uMultiWordShl(const unsigned int u1[], unsigned int n2, unsigned int y[])
{
    int i;
    int nb;
    int nc;
    unsigned int u1i;
    unsigned int ys;
    nb = static_cast<int>(n2) / 32;
    if ((u1[1] & 2147483648U) != 0U) {
        ys = MAX_uint32_T;
    } else {
        ys = 0U;
    }
    if (nb > 2) {
        nc = 2;
    } else {
        nc = nb;
    }
    u1i = 0U;
    if (0 <= nc - 1) {
        std::memset(&y[0], 0, nc * sizeof(unsigned int));
    }
    for (i = 0; i < nc; i++) {
    }
    if (nb < 2) {
        int nc1;
        unsigned int nl;
        nl = n2 - nb * 32U;
        nc1 = nb + 2;
        if (nb + 2 > 2) {
            nc1 = 2;
        }
        nc1 -= i;
        if (nl > 0U) {
            for (int i1{0}; i1 < nc1; i1++) {
                unsigned int yi;
                yi = u1i >> (32U - nl);
                u1i = u1[i1];
                y[i] = yi | u1i << nl;
                i++;
            }
            if (i < 2) {
                y[i] = u1i >> (32U - nl) | ys << nl;
                i++;
            }
        } else {
            for (int i1{0}; i1 < nc1; i1++) {
                y[i] = u1[i1];
                i++;
            }
        }
    }
    while (i < 2) {
        y[i] = ys;
        i++;
    }
}

} // namespace ocn

//
// File trailer for sinspace_rtwutil.cpp
//
// [EOF]
//
