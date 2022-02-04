//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "sinspace.h"
#include "linspace.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double x0
//                double x1
//                int N
//                ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace ocn {
void sinspace(double x0, double x1, int N, ::coder::array<double, 2U> &x)
{
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> y;
    double b;
    int b_loop_ub;
    int i1;
    int loop_ub;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    coder::b_linspace(N, r);
    y.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        y[i] = 3.1415926535897931 * r[i];
    }
    i1 = y.size(1);
    for (int k{0}; k < i1; k++) {
        y[k] = std::cos(y[k]);
    }
    b = x1 - x0;
    x.set_size(1, y.size(1));
    b_loop_ub = y.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        x[i2] = (y[i2] * 0.5 + 0.5) * b + x0;
    }
}

} // namespace ocn

//
// File trailer for sinspace.cpp
//
// [EOF]
//
