//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CorrectArcCenter.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:06
//

// Include Files
#include "CorrectArcCenter.h"
#include "opencn_matlab_data.h"
#include <cmath>

// Function Definitions
//
// function [R, Cprim, delta] = CorrectArcCenter(P0, P1, C)
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
    double L10;
    double L10_tmp;
    double P10_idx_0;
    double d;
    double z1_idx_0;
    // 'CorrectArcCenter:14' P10 = P1 - P0;
    // 'CorrectArcCenter:15' L10 = MyNorm( P10 );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    //  Compute mean of radii
    // 'CorrectArcCenter:17' R   = ( MyNorm( C - P0 ) + MyNorm( C - P1 ) ) / 2;
    d = P1[0] - P0[0];
    P10_idx_0 = d;
    z1_idx_0 = std::pow(d, 2.0);
    d = P1[1] - P0[1];
    L10_tmp = std::pow(d, 2.0);
    L10 = std::sqrt(z1_idx_0 + L10_tmp);
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
    *R = (std::sqrt(std::pow(C[0] - P0[0], 2.0) + std::pow(C[1] - P0[1], 2.0)) +
          std::sqrt(std::pow(C[0] - P1[0], 2.0) + std::pow(C[1] - P1[1], 2.0))) /
         2.0;
    //  Default tolerance for considering two points as supperposed
    // 'CorrectArcCenter:20' DEFAULT_TOL_DIST = 1e-6;
    // 'CorrectArcCenter:22' if L10 < DEFAULT_TOL_DIST
    if (L10 < 1.0E-6) {
        //  Points are supperposed
        // 'CorrectArcCenter:24' Cprim = C;
        // 'CorrectArcCenter:24' delta = 0;
        *delta = 0.0;
    } else {
        double Cprim1_idx_0;
        double Cprim2_idx_0;
        double a;
        double b_a;
        double b_z1_idx_0;
        double d1;
        double d2;
        double d3;
        double d4;
        double n;
        // 'CorrectArcCenter:25' else
        // 'CorrectArcCenter:27' ep  = [P10(2); -P10(1)];
        //  Bisecting line (90° rotation)
        // 'CorrectArcCenter:28' ep  = ep / MyNorm(ep);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        n = std::sqrt(L10_tmp + std::pow(-P10_idx_0, 2.0));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        //  Unit vector on bisecting line
        //  Dealing with limit cases...
        // 'CorrectArcCenter:31' a = R.^2 - ( L10.^2 ) / 4;
        a = std::pow(*R, 2.0) - std::pow(L10, 2.0) / 4.0;
        // 'CorrectArcCenter:32' if  a <= 0
        if (a <= 0.0) {
            //  Center is aligned with the two points
            // 'CorrectArcCenter:33' d = 0;
            b_a = 0.0;
        } else {
            // 'CorrectArcCenter:34' else
            // 'CorrectArcCenter:35' d = mysqrt(a);
            // 'mysqrt:3' y = sqrt(x);
            b_a = std::sqrt(a);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
        }
        // 'CorrectArcCenter:38' delta = a;
        *delta = a;
        // 'CorrectArcCenter:40' M      = 0.5*(P0+P1);
        //  Midpoint
        // 'CorrectArcCenter:41' Cprim1 = M + d*ep;
        //  Two choices for the center point
        // 'CorrectArcCenter:42' Cprim2 = M - d*ep;
        //  Determine on which side the center point lies
        // 'CorrectArcCenter:45' if MyNorm(C-Cprim1) < MyNorm(C-Cprim2)
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        d1 = 0.5 * (P0[0] + P1[0]);
        d2 = b_a * (d / n);
        d3 = d1 + d2;
        Cprim1_idx_0 = d3;
        d4 = d1 - d2;
        Cprim2_idx_0 = d4;
        z1_idx_0 = std::pow(C[0] - d3, 2.0);
        b_z1_idx_0 = std::pow(C[0] - d4, 2.0);
        d1 = 0.5 * (P0[1] + P1[1]);
        d2 = b_a * (-P10_idx_0 / n);
        d3 = d1 + d2;
        d4 = d1 - d2;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        if (std::sqrt(z1_idx_0 + std::pow(C[1] - d3, 2.0)) <
            std::sqrt(b_z1_idx_0 + std::pow(C[1] - d4, 2.0))) {
            // 'CorrectArcCenter:46' Cprim = Cprim1;
            C[0] = Cprim1_idx_0;
            C[1] = d3;
        } else {
            // 'CorrectArcCenter:47' else
            // 'CorrectArcCenter:48' Cprim = Cprim2;
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
