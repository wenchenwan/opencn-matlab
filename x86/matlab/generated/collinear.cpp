//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: collinear.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "collinear.h"
#include "sinspace_data.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double u[3]
//                const double v[3]
//                double tol_cos
// Return Type  : bool
//
namespace ocn {
bool collinear(const double u[3], const double v[3], double tol_cos)
{
    double absxk;
    double scale;
    double t;
    double y;
    bool value;
    scale = 3.3121686421112381E-170;
    absxk = std::abs(u[0]);
    if (absxk > 3.3121686421112381E-170) {
        y = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        y = t * t;
    }
    absxk = std::abs(u[1]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    absxk = std::abs(u[2]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    y = scale * std::sqrt(y);
    if (y < 2.2204460492503131E-16) {
        value = true;
    } else {
        double b_absxk;
        double b_scale;
        double b_t;
        double b_y;
        b_scale = 3.3121686421112381E-170;
        b_absxk = std::abs(v[0]);
        if (b_absxk > 3.3121686421112381E-170) {
            b_y = 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / 3.3121686421112381E-170;
            b_y = b_t * b_t;
        }
        b_absxk = std::abs(v[1]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            b_y = b_y * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            b_y += b_t * b_t;
        }
        b_absxk = std::abs(v[2]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            b_y = b_y * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            b_y += b_t * b_t;
        }
        b_y = b_scale * std::sqrt(b_y);
        if (b_y < 2.2204460492503131E-16) {
            value = true;
        } else {
            sqrt_calls++;
            sqrt_calls++;
            value =
                (((u[0] * v[0] + u[1] * v[1]) + u[2] * v[2]) /
                     (std::sqrt((std::pow(u[0], 2.0) + std::pow(u[1], 2.0)) + std::pow(u[2], 2.0)) *
                      std::sqrt((std::pow(v[0], 2.0) + std::pow(v[1], 2.0)) +
                                std::pow(v[2], 2.0))) >
                 tol_cos);
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
