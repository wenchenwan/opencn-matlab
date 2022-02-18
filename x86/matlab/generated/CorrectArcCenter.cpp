//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CorrectArcCenter.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "CorrectArcCenter.h"
#include "sinspace_data.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// CorrectArcCenter : Recompute the correct center of a given arc. This is a
//  required step to minimize rounding errors.
//
//  P0    : 2D vector from the origin to the starting point
//  P1    : 2D vector from the origin to the ending point
//  C     : 2D vector from the origin to the center of the arc
//
//  R     : Radius of arc
//  Cprim : Corrected Center of the arc
//  delta : Numerical difference between the two centers
//
// Arguments    : const double P0[2]
//                const double P1[2]
//                double C[2]
//                double *R
//                double *delta
// Return Type  : void
//
namespace ocn {
void CorrectArcCenter(const double P0[2], const double P1[2], double C[2], double *R, double *delta)
{
    double ep[2];
    double L10;
    double L10_tmp;
    double P10_idx_0;
    double d;
    double z1_idx_0;
    sqrt_calls++;
    //  Compute mean of radii
    d = P1[0] - P0[0];
    P10_idx_0 = d;
    z1_idx_0 = std::pow(d, 2.0);
    d = P1[1] - P0[1];
    L10_tmp = std::pow(d, 2.0);
    L10 = std::sqrt(z1_idx_0 + L10_tmp);
    sqrt_calls++;
    sqrt_calls++;
    *R = (std::sqrt(std::pow(C[0] - P0[0], 2.0) + std::pow(C[1] - P0[1], 2.0)) +
          std::sqrt(std::pow(C[0] - P1[0], 2.0) + std::pow(C[1] - P1[1], 2.0))) /
         2.0;
    //  Default tolerance for considering two points as supperposed
    if (L10 < 1.0E-6) {
        //  Points are supperposed
        *delta = 0.0;
    } else {
        __m128d r;
        double Cprim1_idx_0;
        double Cprim2_idx_0;
        double a;
        double b_a;
        double b_z1_idx_0;
        double d1;
        double d2;
        double d3;
        double d4;
        ep[0] = d;
        ep[1] = -P10_idx_0;
        //  Bisecting line (90° rotation)
        sqrt_calls++;
        r = _mm_loadu_pd(&ep[0]);
        _mm_storeu_pd(&ep[0],
                      _mm_div_pd(r, _mm_set1_pd(std::sqrt(L10_tmp + std::pow(-P10_idx_0, 2.0)))));
        //  Unit vector on bisecting line
        //  Dealing with limit cases...
        a = std::pow(*R, 2.0) - std::pow(L10, 2.0) / 4.0;
        if (a <= 0.0) {
            //  Center is aligned with the two points
            b_a = 0.0;
        } else {
            b_a = std::sqrt(a);
            sqrt_calls++;
        }
        *delta = a;
        //  Midpoint
        //  Two choices for the center point
        //  Determine on which side the center point lies
        sqrt_calls++;
        d1 = 0.5 * (P0[0] + P1[0]);
        d2 = b_a * ep[0];
        d3 = d1 + d2;
        Cprim1_idx_0 = d3;
        d4 = d1 - d2;
        Cprim2_idx_0 = d4;
        z1_idx_0 = std::pow(C[0] - d3, 2.0);
        b_z1_idx_0 = std::pow(C[0] - d4, 2.0);
        d1 = 0.5 * (P0[1] + P1[1]);
        d2 = b_a * ep[1];
        d3 = d1 + d2;
        d4 = d1 - d2;
        sqrt_calls++;
        if (std::sqrt(z1_idx_0 + std::pow(C[1] - d3, 2.0)) <
            std::sqrt(b_z1_idx_0 + std::pow(C[1] - d4, 2.0))) {
            C[0] = Cprim1_idx_0;
            C[1] = d3;
        } else {
            C[0] = Cprim2_idx_0;
            C[1] = d4;
        }
    }
}

} // namespace ocn

//
// File trailer for CorrectArcCenter.cpp
//
// [EOF]
//
