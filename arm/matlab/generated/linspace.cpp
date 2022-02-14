//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "linspace.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_linspace(int n, ::coder::array<double, 2U> &y)
{
    if (n < 0) {
        y.set_size(1, 0);
    } else {
        y.set_size(1, n);
        if (n >= 1) {
            y[n - 1] = 0.0;
            if (y.size(1) >= 2) {
                y[0] = -1.0;
                if (y.size(1) >= 3) {
                    double delta1;
                    int i;
                    delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                    i = y.size(1);
                    for (int k{0}; k <= i - 3; k++) {
                        y[k + 1] = (static_cast<double>(k) + 1.0) * delta1 + -1.0;
                    }
                }
            }
        }
    }
}

//
// Arguments    : int n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void c_linspace(int n, ::coder::array<double, 2U> &y)
{
    if (n < 0) {
        y.set_size(1, 0);
    } else {
        y.set_size(1, n);
        if (n >= 1) {
            y[n - 1] = 1.0;
            if (y.size(1) >= 2) {
                y[0] = 0.0;
                if (y.size(1) >= 3) {
                    double delta1;
                    int i;
                    delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                    i = y.size(1);
                    for (int k{0}; k <= i - 3; k++) {
                        y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                    }
                }
            }
        }
    }
}

//
// Arguments    : double d1
//                double d2
//                double n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void linspace(double d1, double d2, double n, ::coder::array<double, 2U> &y)
{
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    if (n < 0.0) {
        y.set_size(1, 0);
    } else {
        double d;
        d = std::floor(n);
        y.set_size(1, static_cast<int>(d));
        if (static_cast<int>(d) >= 1) {
            int y_tmp;
            y_tmp = static_cast<int>(d) - 1;
            y[static_cast<int>(d) - 1] = d2;
            if (y.size(1) >= 2) {
                y[0] = d1;
                if (y.size(1) >= 3) {
                    if ((d1 == -d2) && (static_cast<int>(d) > 2)) {
                        double d2scaled;
                        d2scaled = d2 / (static_cast<double>(static_cast<int>(d)) - 1.0);
                        for (int k{2}; k <= y_tmp; k++) {
                            y[k - 1] = static_cast<double>(((k << 1) - static_cast<int>(d)) - 1) *
                                       d2scaled;
                        }
                        if ((static_cast<int>(d) & 1) == 1) {
                            y[static_cast<int>(d) >> 1] = 0.0;
                        }
                    } else if (((d1 < 0.0) != (d2 < 0.0)) &&
                               ((std::abs(d1) > 8.9884656743115785E+307) ||
                                (std::abs(d2) > 8.9884656743115785E+307))) {
                        double delta1;
                        double delta2;
                        int i1;
                        delta1 = d1 / (static_cast<double>(y.size(1)) - 1.0);
                        delta2 = d2 / (static_cast<double>(y.size(1)) - 1.0);
                        i1 = y.size(1);
                        for (int c_k{0}; c_k <= i1 - 3; c_k++) {
                            y[c_k + 1] = (d1 + delta2 * (static_cast<double>(c_k) + 1.0)) -
                                         delta1 * (static_cast<double>(c_k) + 1.0);
                        }
                    } else {
                        double delta1;
                        int i;
                        delta1 = (d2 - d1) / (static_cast<double>(y.size(1)) - 1.0);
                        i = y.size(1);
                        for (int b_k{0}; b_k <= i - 3; b_k++) {
                            y[b_k + 1] = d1 + (static_cast<double>(b_k) + 1.0) * delta1;
                        }
                    }
                }
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for linspace.cpp
//
// [EOF]
//
