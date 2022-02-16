//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: norm.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

// Include Files
#include "norm.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double x[3]
// Return Type  : double
//
namespace ocn {
namespace coder {
double b_norm(const double x[3])
{
    double absxk;
    double scale;
    double t;
    double y;
    scale = 3.3121686421112381E-170;
    absxk = std::abs(x[0]);
    if (absxk > 3.3121686421112381E-170) {
        y = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        y = t * t;
    }
    absxk = std::abs(x[1]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    absxk = std::abs(x[2]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    return scale * std::sqrt(y);
}

} // namespace coder
} // namespace ocn

//
// File trailer for norm.cpp
//
// [EOF]
//
