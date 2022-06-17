//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calc_t_nk_kappa.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

// Include Files
#include "calc_t_nk_kappa.h"
#include "opencn_matlab_data.h"
#include <cmath>

// Function Definitions
//
// function [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
//
// Arguments    : const double rD1[5]
//                const double rD2[5]
//                double t[5]
//                double nk[5]
//                double *kappa
// Return Type  : void
//
namespace ocn {
void calc_t_nk_kappa(const double rD1[5], const double rD2[5], double t[5], double nk[5],
                     double *kappa)
{
    double z1[5];
    double a;
    double a_tmp;
    double b_rD2;
    double norm_rD1;
    double norm_rD2;
    double num;
    //  computes the local Frenet frame (t, n, b) of a curve in R^n
    //  [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'calc_t_nk_kappa:5' norm_rD1 = MyNorm(rD1);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    for (int k{0}; k < 5; k++) {
        z1[k] = std::pow(rD1[k], 2.0);
    }
    // 'mysqrt:3' y = sqrt(x);
    norm_rD1 = std::sqrt((((z1[0] + z1[1]) + z1[2]) + z1[3]) + z1[4]);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:6' norm_rD2 = MyNorm(rD2);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:8' t = rD1 / norm_rD1;
    //  tangential unit vector
    //
    // 'calc_t_nk_kappa:10' nk     = (rD2 - rD2'*rD1/(norm_rD1*norm_rD1)*rD1)/(norm_rD1*norm_rD1);
    b_rD2 = 0.0;
    for (int b_k{0}; b_k < 5; b_k++) {
        double d;
        double d1;
        d = rD2[b_k];
        z1[b_k] = std::pow(d, 2.0);
        d1 = rD1[b_k];
        t[b_k] = d1 / norm_rD1;
        b_rD2 += d * d1;
    }
    norm_rD2 = std::sqrt((((z1[0] + z1[1]) + z1[2]) + z1[3]) + z1[4]);
    a_tmp = norm_rD1 * norm_rD1;
    a = b_rD2 / a_tmp;
    for (int i{0}; i < 5; i++) {
        nk[i] = (rD2[i] - a * rD1[i]) / a_tmp;
    }
    //  normal unit vector
    //
    // 'calc_t_nk_kappa:12' num = norm_rD2*norm_rD2*norm_rD1*norm_rD1 - (rD2'*rD1)*(rD2'*rD1);
    num = norm_rD2 * norm_rD2 * norm_rD1 * norm_rD1 - b_rD2 * b_rD2;
    // 'calc_t_nk_kappa:13' if num < 0
    if (num < 0.0) {
        // 'calc_t_nk_kappa:14' num = 0;
        num = 0.0;
    }
    // 'calc_t_nk_kappa:17' kappa = sqrt(num)...
    // 'calc_t_nk_kappa:18'         /(norm_rD1*norm_rD1*norm_rD1);
    *kappa = std::sqrt(num) / (a_tmp * norm_rD1);
    //  curvature
}

} // namespace ocn

//
// File trailer for calc_t_nk_kappa.cpp
//
// [EOF]
//
