//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "colon.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double a
//                double d
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_eml_float_colon(double a, double d, ::coder::array<double, 2U> &y)
{
    double apnd;
    double b1;
    double cdiff;
    double ndbl;
    int n;
    ndbl = std::floor((0.0 - a) / d + 0.5);
    apnd = a + ndbl * d;
    if (d > 0.0) {
        cdiff = apnd;
    } else {
        cdiff = 0.0 - apnd;
    }
    if (std::abs(cdiff) < 4.4408920985006262E-16 * std::fmax(std::abs(a), 0.0)) {
        ndbl++;
        b1 = 0.0;
    } else if (cdiff > 0.0) {
        b1 = a + (ndbl - 1.0) * d;
    } else {
        ndbl++;
        b1 = apnd;
    }
    if (ndbl >= 0.0) {
        n = static_cast<int>(ndbl);
    } else {
        n = 0;
    }
    y.set_size(1, n);
    if (n > 0) {
        y[0] = a;
        if (n > 1) {
            double kd;
            int nm1d2;
            y[n - 1] = b1;
            nm1d2 = (n - 1) / 2;
            for (int k{0}; k <= nm1d2 - 2; k++) {
                kd = (static_cast<double>(k) + 1.0) * d;
                y[k + 1] = a + kd;
                y[(n - k) - 2] = b1 - kd;
            }
            if (nm1d2 << 1 == n - 1) {
                y[nm1d2] = (a + b1) / 2.0;
            } else {
                kd = static_cast<double>(nm1d2) * d;
                y[nm1d2] = a + kd;
                y[nm1d2 + 1] = b1 - kd;
            }
        }
    }
}

//
// Arguments    : double d
//                double b
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void eml_float_colon(double d, double b, ::coder::array<double, 2U> &y)
{
    double apnd;
    double b1;
    double cdiff;
    double ndbl;
    int n;
    ndbl = std::floor(b / d + 0.5);
    apnd = ndbl * d;
    if (d > 0.0) {
        cdiff = apnd - b;
    } else {
        cdiff = b - apnd;
    }
    if (std::abs(cdiff) < 4.4408920985006262E-16 * std::fmax(0.0, std::abs(b))) {
        ndbl++;
        b1 = b;
    } else if (cdiff > 0.0) {
        b1 = (ndbl - 1.0) * d;
    } else {
        ndbl++;
        b1 = apnd;
    }
    if (ndbl >= 0.0) {
        n = static_cast<int>(ndbl);
    } else {
        n = 0;
    }
    y.set_size(1, n);
    if (n > 0) {
        y[0] = 0.0;
        if (n > 1) {
            double kd;
            int nm1d2;
            y[n - 1] = b1;
            nm1d2 = (n - 1) / 2;
            for (int k{0}; k <= nm1d2 - 2; k++) {
                kd = (static_cast<double>(k) + 1.0) * d;
                y[k + 1] = kd;
                y[(n - k) - 2] = b1 - kd;
            }
            if (nm1d2 << 1 == n - 1) {
                y[nm1d2] = b1 / 2.0;
            } else {
                kd = static_cast<double>(nm1d2) * d;
                y[nm1d2] = kd;
                y[nm1d2 + 1] = b1 - kd;
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for colon.cpp
//
// [EOF]
//
