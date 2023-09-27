//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:27:31
//

// Include Files
#include "mldivide.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double A[2][2]
//                const double B[2]
//                double Y[2]
// Return Type  : void
//
namespace ocn {
namespace coder {
void mldivide(const double A[2][2], const double B[2], double Y[2])
{
    double a21;
    int r1;
    int r2;
    if (std::abs(A[0][1]) > std::abs(A[0][0])) {
        r1 = 1;
        r2 = 0;
    } else {
        r1 = 0;
        r2 = 1;
    }
    a21 = A[0][r2] / A[0][r1];
    Y[1] = (B[r2] - B[r1] * a21) / (A[1][r2] - a21 * A[1][r1]);
    Y[0] = (B[r1] - Y[1] * A[1][r1]) / A[0][r1];
}

} // namespace coder
} // namespace ocn

//
// File trailer for mldivide.cpp
//
// [EOF]
//
