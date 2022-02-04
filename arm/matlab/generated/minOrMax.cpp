//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "minOrMax.h"
#include "sinspace_rtwutil.h"
#include "sinspace_types11.h"
#include <cmath>

// Function Declarations
namespace ocn {
static bool uMultiWordLt(const unsigned int u1[], const unsigned int u2[]);

}

// Function Definitions
//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
namespace ocn {
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
