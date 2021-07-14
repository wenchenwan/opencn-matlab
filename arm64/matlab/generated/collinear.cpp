//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: collinear.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "collinear.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double u[3]
//                const double v[3]
//                double tol_angle_d
// Return Type  : bool
//
namespace ocn {
bool collinear(const double u[3], const double v[3], double tol_angle_d)
{
    double absxk;
    double d;
    double scale;
    double t;
    bool value;
    scale = 3.3121686421112381E-170;
    absxk = std::abs(u[0]);
    if (absxk > 3.3121686421112381E-170) {
        d = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        d = t * t;
    }
    absxk = std::abs(u[1]);
    if (absxk > scale) {
        t = scale / absxk;
        d = d * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        d += t * t;
    }
    absxk = std::abs(u[2]);
    if (absxk > scale) {
        t = scale / absxk;
        d = d * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        d += t * t;
    }
    d = scale * std::sqrt(d);
    if (d < 2.2204460492503131E-16) {
        value = true;
    } else {
        double b_absxk;
        double b_scale;
        double b_t;
        double d1;
        b_scale = 3.3121686421112381E-170;
        b_absxk = std::abs(v[0]);
        if (b_absxk > 3.3121686421112381E-170) {
            d1 = 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / 3.3121686421112381E-170;
            d1 = b_t * b_t;
        }
        b_absxk = std::abs(v[1]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            d1 = d1 * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            d1 += b_t * b_t;
        }
        b_absxk = std::abs(v[2]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            d1 = d1 * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            d1 += b_t * b_t;
        }
        d1 = b_scale * std::sqrt(d1);
        if (d1 < 2.2204460492503131E-16) {
            value = true;
        } else {
            value = (std::abs(57.295779513082323 *
                              std::acos(((u[0] * v[0] + u[1] * v[1]) + u[2] * v[2]) / (d * d1))) <
                     std::abs(tol_angle_d));
        }
    }
    return value;
}

} // namespace ocn

//
// File trailer for collinear.cpp
//
// [EOF]
//
