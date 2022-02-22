//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:18:27
//

// Include Files
#include "minOrMax.h"
#include <cmath>

// Function Definitions
//
// Arguments    : unsigned long x
// Return Type  : unsigned long
//
namespace ocn {
namespace coder {
namespace internal {
unsigned long maximum2(unsigned long x)
{
    double DBLMAXFLINT;
    unsigned long ex;
    bool alarge;
    bool blarge;
    bool p;
    p = false;
    DBLMAXFLINT = std::pow(2.0, 52.0);
    blarge = (1.0 >= DBLMAXFLINT);
    alarge = (x >= static_cast<unsigned long>(std::round(DBLMAXFLINT)));
    if ((!alarge) && blarge) {
        p = true;
    } else if (alarge && blarge) {
        p = (x < 1UL);
    } else if (!alarge) {
        p = (x < 1.0);
    }
    if (p) {
        ex = 1UL;
    } else {
        ex = x;
    }
    return ex;
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
