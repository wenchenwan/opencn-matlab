//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cosd.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:27:31
//

// Include Files
#include "cosd.h"
#include <cfloat>
#include <cmath>

// Function Declarations
namespace ocn {
static double rt_remd(double u0, double u1);

}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace ocn {
static double rt_remd(double u0, double u1)
{
    double y;
    if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
        double q;
        q = std::abs(u0 / u1);
        if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
            y = 0.0;
        } else {
            y = std::fmod(u0, u1);
        }
    } else {
        y = std::fmod(u0, u1);
    }
    return y;
}

//
// Arguments    : double *x
// Return Type  : void
//
namespace coder {
void b_cosd(double *x)
{
    double absx;
    double b_x;
    signed char n;
    b_x = rt_remd(*x, 360.0);
    absx = std::abs(b_x);
    if (absx > 180.0) {
        if (b_x > 0.0) {
            b_x -= 360.0;
        } else {
            b_x += 360.0;
        }
        absx = std::abs(b_x);
    }
    if (absx <= 45.0) {
        b_x *= 0.017453292519943295;
        n = 0;
    } else if (absx <= 135.0) {
        if (b_x > 0.0) {
            b_x = 0.017453292519943295 * (b_x - 90.0);
            n = 1;
        } else {
            b_x = 0.017453292519943295 * (b_x + 90.0);
            n = -1;
        }
    } else if (b_x > 0.0) {
        b_x = 0.017453292519943295 * (b_x - 180.0);
        n = 2;
    } else {
        b_x = 0.017453292519943295 * (b_x + 180.0);
        n = -2;
    }
    if (n == 0) {
        *x = std::cos(b_x);
    } else if (n == 1) {
        *x = -std::sin(b_x);
    } else if (n == -1) {
        *x = std::sin(b_x);
    } else {
        *x = -std::cos(b_x);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for cosd.cpp
//
// [EOF]
//
