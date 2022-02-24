//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcFrenet.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:51:03
//

// Include Files
#include "CalcFrenet.h"
#include "opencn_matlab_data.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [t, n, kappa] = CalcFrenet(rD1, rD2)
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
    double b[3];
    double n_tmp;
    //  computes the local Frenet frame (t, n, b) of a curve in R^3
    //  [t, n, b, kappa] = CalcFrenet(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'CalcFrenet:5' t = rD1 / MyNorm(rD1);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    n_tmp = std::sqrt((std::pow(rD1[0], 2.0) + std::pow(rD1[1], 2.0)) + std::pow(rD1[2], 2.0));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    //  tangential unit vector
    //
    // 'CalcFrenet:7' if  abs(abs(t'*rD2) - MyNorm(rD2)) > eps
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    t[0] = rD1[0] / n_tmp;
    t[1] = rD1[1] / n_tmp;
    t[2] = rD1[2] / n_tmp;
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    if (std::abs(std::abs((t[0] * rD2[0] + t[1] * rD2[1]) + t[2] * rD2[2]) -
                 std::sqrt((std::pow(rD2[0], 2.0) + std::pow(rD2[1], 2.0)) +
                           std::pow(rD2[2], 2.0))) > 2.2204460492503131E-16) {
        __m128d r;
        double b_b_tmp;
        double b_n_tmp;
        double b_tmp;
        double c_b_tmp;
        //  regular case
        // 'CalcFrenet:8' b     = cross(rD1, rD2);
        b_tmp = rD1[1] * rD2[2] - rD2[1] * rD1[2];
        b[0] = b_tmp;
        b_b_tmp = rD2[0] * rD1[2] - rD1[0] * rD2[2];
        b[1] = b_b_tmp;
        c_b_tmp = rD1[0] * rD2[1] - rD2[0] * rD1[1];
        b[2] = c_b_tmp;
        // 'CalcFrenet:9' b     = b / MyNorm(b);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        b_n_tmp =
            std::sqrt((std::pow(b_tmp, 2.0) + std::pow(b_b_tmp, 2.0)) + std::pow(c_b_tmp, 2.0));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        r = _mm_loadu_pd(&b[0]);
        _mm_storeu_pd(&b[0], _mm_div_pd(r, _mm_set1_pd(b_n_tmp)));
        b[2] /= b_n_tmp;
        //  binormal unit vector
        // 'CalcFrenet:10' n     = cross(b, t);
        n[0] = b[1] * t[2] - t[1] * b[2];
        n[1] = t[0] * b[2] - b[0] * t[2];
        n[2] = b[0] * t[1] - t[0] * b[1];
        //  normal unit vector
        // 'CalcFrenet:11' kappa = MyNorm(cross(rD1, rD2)) / MyNorm(rD1)^3;
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        *kappa = b_n_tmp / std::pow(n_tmp, 3.0);
        //  curvature
    } else {
        // 'CalcFrenet:12' else
        //  special case if rD2 = 0
        // 'CalcFrenet:13' n     = zeros(3,1);
        n[0] = 0.0;
        n[1] = 0.0;
        n[2] = 0.0;
        //  normal unit vector not defined
        // 'CalcFrenet:14' kappa = 0;
        *kappa = 0.0;
    }
}

} // namespace ocn

//
// File trailer for CalcFrenet.cpp
//
// [EOF]
//
