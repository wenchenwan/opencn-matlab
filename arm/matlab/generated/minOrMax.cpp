//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
//

// Include Files
#include "minOrMax.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types11.h"
#include <cmath>

// Function Declarations
namespace ocn {
static double uMultiWord2Double(const unsigned int u1[]);

static bool uMultiWordLt(const unsigned int u1[], const unsigned int u2[]);

} // namespace ocn

// Function Definitions
//
// Arguments    : const unsigned int u1[]
// Return Type  : double
//
namespace ocn {
static double uMultiWord2Double(const unsigned int u1[])
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
// Return Type  : bool
//
static bool uMultiWordLt(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) < 0;
}

//
// Arguments    : const uint64m_T x
// Return Type  : uint64m_T
//
namespace coder {
namespace internal {
uint64m_T maximum2(const uint64m_T x)
{
    static const uint64m_T r1{
        {1U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    double DBLMAXFLINT;
    bool alarge;
    bool blarge;
    bool p;
    p = false;
    DBLMAXFLINT = std::pow(2.0, 52.0);
    blarge = (1.0 >= DBLMAXFLINT);
    Double2MultiWord(std::round(DBLMAXFLINT), (unsigned int *)&r.chunks[0U]);
    alarge = uMultiWordGe((unsigned int *)&x.chunks[0U], (unsigned int *)&r.chunks[0U]);
    if ((!alarge) && blarge) {
        p = true;
    } else if (alarge && blarge) {
        p = uMultiWordLt((unsigned int *)&x.chunks[0U], (unsigned int *)&r1.chunks[0U]);
    } else if (!alarge) {
        p = (uMultiWord2Double((unsigned int *)&x.chunks[0U]) < 1.0);
    }
    if (p) {
        r2 = r1;
    } else {
        r2 = x;
    }
    return r2;
}

//
// Arguments    : const double x_data[]
//                int x_size
//                double *ex
//                int *idx
// Return Type  : void
//
void minimum(const double x_data[], int x_size, double *ex, int *idx)
{
    if (x_size <= 2) {
        double d;
        d = x_data[x_size - 1];
        if (x_data[0] > d) {
            *ex = d;
            *idx = x_size;
        } else {
            *ex = x_data[0];
            *idx = 1;
        }
    } else {
        double b_ex;
        b_ex = x_data[0];
        *idx = 1;
        for (int k{2}; k <= x_size; k++) {
            double d1;
            d1 = x_data[k - 1];
            if (b_ex > d1) {
                b_ex = d1;
                *idx = k;
            }
        }
        *ex = b_ex;
    }
}

} // namespace internal
} // namespace coder
} // namespace ocn

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
