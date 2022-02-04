//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcFrenet.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CalcFrenet.h"
#include "sinspace_data.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double rD1[3]
//                const double rD2[3]
//                double t[3]
//                double n[3]
//                double *kappa
// Return Type  : void
//
namespace ocn {
void CalcFrenet(const double rD1[3], const double rD2[3], double t[3], double n[3], double *kappa)
{
    double n_tmp;
    //  computes the local Frenet frame (t, n, b) of a curve in R^3
    //  [t, n, b, kappa] = CalcFrenet(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    n_tmp = std::sqrt((std::pow(rD1[0], 2.0) + std::pow(rD1[1], 2.0)) + std::pow(rD1[2], 2.0));
    sqrt_calls++;
    //  tangential unit vector
    //
    t[0] = rD1[0] / n_tmp;
    t[1] = rD1[1] / n_tmp;
    t[2] = rD1[2] / n_tmp;
    sqrt_calls++;
    if (std::abs(std::abs((t[0] * rD2[0] + t[1] * rD2[1]) + t[2] * rD2[2]) -
                 std::sqrt((std::pow(rD2[0], 2.0) + std::pow(rD2[1], 2.0)) +
                           std::pow(rD2[2], 2.0))) > 2.2204460492503131E-16) {
        double b_idx_0;
        double b_idx_0_tmp;
        double b_idx_1;
        double b_idx_1_tmp;
        double b_idx_2;
        double b_idx_2_tmp;
        double b_n_tmp;
        //  regular case
        b_idx_0_tmp = rD1[1] * rD2[2] - rD2[1] * rD1[2];
        b_idx_1_tmp = rD2[0] * rD1[2] - rD1[0] * rD2[2];
        b_idx_2_tmp = rD1[0] * rD2[1] - rD2[0] * rD1[1];
        b_n_tmp = std::sqrt((std::pow(b_idx_0_tmp, 2.0) + std::pow(b_idx_1_tmp, 2.0)) +
                            std::pow(b_idx_2_tmp, 2.0));
        sqrt_calls++;
        b_idx_0 = b_idx_0_tmp / b_n_tmp;
        b_idx_1 = b_idx_1_tmp / b_n_tmp;
        b_idx_2 = b_idx_2_tmp / b_n_tmp;
        //  binormal unit vector
        n[0] = b_idx_1 * t[2] - t[1] * b_idx_2;
        n[1] = t[0] * b_idx_2 - b_idx_0 * t[2];
        n[2] = b_idx_0 * t[1] - t[0] * b_idx_1;
        //  normal unit vector
        sqrt_calls++;
        sqrt_calls++;
        *kappa = b_n_tmp / std::pow(n_tmp, 3.0);
        //  curvature
    } else {
        //  special case if rD2 = 0
        n[0] = 0.0;
        n[1] = 0.0;
        n[2] = 0.0;
        //  normal unit vector not defined
        *kappa = 0.0;
    }
}

} // namespace ocn

//
// File trailer for CalcFrenet.cpp
//
// [EOF]
//
