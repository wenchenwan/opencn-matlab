//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 15:12:00
//

// Include Files
#include "linspace.h"
#include "coder_array.h"

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
void linspace(int n, ::coder::array<double, 2U> &y)
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

} // namespace coder
} // namespace ocn

//
// File trailer for linspace.cpp
//
// [EOF]
//
