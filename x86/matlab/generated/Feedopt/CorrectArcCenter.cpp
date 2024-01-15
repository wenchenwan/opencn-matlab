
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CorrectArcCenter.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "CorrectArcCenter.h"
#include "ocn_assert.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ R, Cprim, delta ] = CorrectArcCenter( P0, P1, C )
//
// CorrectArcCenter : Recompute the correct center of a given arc. This is a
//  required step to minimize rounding errors.
//
//  Inputs :
//  P0    : 2D vector from the origin to the starting point
//  P1    : 2D vector from the origin to the ending point
//  C     : 2D vector from the origin to the center of the arc
//
//  Outputs :
//  R     : Radius of arc
//  Cprim : Corrected Center of the arc
//  delta : Numerical difference between the two centers
//
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
    double P10_idx_0;
    double b_x;
    double c_x;
    double d;
    double x;
    double x_tmp;
    double z1_idx_0;
    // 'CorrectArcCenter:17' P10 = P1 - P0;
    // 'CorrectArcCenter:18' L10 = MyNorm( P10 );
    //  MyNorm : My implementation of the norm computation.
    //
    //  Inputs :
    //    x   : The input vector.
    //
    //  Outputs :
    //    n   : The resulting norm.
    //
    // 'MyNorm:10' coder.inline( 'always' );
    // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
    d = P1[0] - P0[0];
    P10_idx_0 = d;
    z1_idx_0 = std::pow(d, 2.0);
    d = P1[1] - P0[1];
    x_tmp = std::pow(d, 2.0);
    x = z1_idx_0 + x_tmp;
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    ocn_assert(x >= 0.0);
    // 'mysqrt:11' y = sqrt(x);
    L10 = std::sqrt(x);
    //  Compute mean of radii
    // 'CorrectArcCenter:20' R   = ( MyNorm( C - P0 ) + MyNorm( C - P1 ) ) / 2;
    //  MyNorm : My implementation of the norm computation.
    //
    //  Inputs :
    //    x   : The input vector.
    //
    //  Outputs :
    //    n   : The resulting norm.
    //
    // 'MyNorm:10' coder.inline( 'always' );
    // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
    b_x = std::pow(C[0] - P0[0], 2.0) + std::pow(C[1] - P0[1], 2.0);
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    ocn_assert(b_x >= 0.0);
    // 'mysqrt:11' y = sqrt(x);
    //  MyNorm : My implementation of the norm computation.
    //
    //  Inputs :
    //    x   : The input vector.
    //
    //  Outputs :
    //    n   : The resulting norm.
    //
    // 'MyNorm:10' coder.inline( 'always' );
    // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
    c_x = std::pow(C[0] - P1[0], 2.0) + std::pow(C[1] - P1[1], 2.0);
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    ocn_assert(c_x >= 0.0);
    // 'mysqrt:11' y = sqrt(x);
    *R = (std::sqrt(b_x) + std::sqrt(c_x)) / 2.0;
    //  Default tolerance for considering two points as supperposed
    // 'CorrectArcCenter:23' DEFAULT_TOL_DIST = 1e-6;
    // 'CorrectArcCenter:25' if L10 < DEFAULT_TOL_DIST
    if (L10 < 1.0E-6) {
        //  Points are supperposed
        // 'CorrectArcCenter:27' Cprim = C;
        // 'CorrectArcCenter:27' delta = 0;
        *delta = 0.0;
    } else {
        __m128d r;
        double Cprim1_idx_0;
        double Cprim2_idx_0;
        double Cprim2_idx_1;
        double a;
        double b_a;
        double d1;
        double d2;
        double d3;
        double d_x;
        double e_x;
        double f_x;
        // 'CorrectArcCenter:28' else
        // 'CorrectArcCenter:30' ep  = [P10(2); -P10(1)];
        ep[0] = d;
        ep[1] = -P10_idx_0;
        //  Bisecting line (90° rotation)
        // 'CorrectArcCenter:31' ep  = ep / MyNorm(ep);
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        d_x = x_tmp + std::pow(-P10_idx_0, 2.0);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(d_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        r = _mm_loadu_pd(&ep[0]);
        _mm_storeu_pd(&ep[0], _mm_div_pd(r, _mm_set1_pd(std::sqrt(d_x))));
        //  Unit vector on bisecting line
        //  Dealing with limit cases...
        // 'CorrectArcCenter:34' a = R.^2 - ( L10.^2 ) / 4;
        a = *R * *R - L10 * L10 / 4.0;
        // 'CorrectArcCenter:35' if  a <= 0
        if (a <= 0.0) {
            //  Center is aligned with the two points
            // 'CorrectArcCenter:36' d = 0;
            b_a = 0.0;
        } else {
            // 'CorrectArcCenter:37' else
            // 'CorrectArcCenter:38' d = mysqrt(a);
            //  mysqrt : Custom implementation of the sqrt method.
            //
            //  Inputs :
            //    x : Value used for the computation
            //  Outputs :
            //    y : Resulting value
            //
            // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
            // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
            ocn_assert(a >= 0.0);
            // 'mysqrt:11' y = sqrt(x);
            b_a = std::sqrt(a);
        }
        // 'CorrectArcCenter:41' delta = a;
        *delta = a;
        // 'CorrectArcCenter:43' M      = 0.5*(P0+P1);
        //  Midpoint
        // 'CorrectArcCenter:44' Cprim1 = M + d*ep;
        //  Two choices for the center point
        // 'CorrectArcCenter:45' Cprim2 = M - d*ep;
        //  Determine on which side the center point lies
        // 'CorrectArcCenter:48' if MyNorm(C-Cprim1) < MyNorm(C-Cprim2)
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        d1 = 0.5 * (P0[0] + P1[0]);
        d2 = b_a * ep[0];
        d3 = d1 + d2;
        Cprim1_idx_0 = d3;
        Cprim2_idx_0 = d1 - d2;
        z1_idx_0 = std::pow(C[0] - d3, 2.0);
        d1 = 0.5 * (P0[1] + P1[1]);
        d2 = b_a * ep[1];
        d3 = d1 + d2;
        Cprim2_idx_1 = d1 - d2;
        e_x = z1_idx_0 + std::pow(C[1] - d3, 2.0);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(e_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        f_x = std::pow(C[0] - Cprim2_idx_0, 2.0) + std::pow(C[1] - Cprim2_idx_1, 2.0);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(f_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        if (std::sqrt(e_x) < std::sqrt(f_x)) {
            // 'CorrectArcCenter:49' Cprim = Cprim1;
            C[0] = Cprim1_idx_0;
            C[1] = d3;
        } else {
            // 'CorrectArcCenter:50' else
            // 'CorrectArcCenter:51' Cprim = Cprim2;
            C[0] = Cprim2_idx_0;
            C[1] = Cprim2_idx_1;
        }
    }
}

} // namespace ocn

//
// File trailer for CorrectArcCenter.cpp
//
// [EOF]
//
