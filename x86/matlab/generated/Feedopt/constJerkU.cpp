//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constJerkU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "constJerkU.h"
#include <cmath>

// Function Definitions
//
// function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd )
//
// constJerkU : Compute u and its derivative based on the pseudo jerk
//  approximation.
//  Inputs :
//    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
//    k_vec      :  [ 1 x M ] The time vector
//    isEnd      :  ( Boolean ) Is the end of the Curve.
//    a          :  Curve parameter a for affine transforme
//    b          :  Curve parameter b for affine transforme
//  Outputs :
//    u          :  [ N x M ]
//    ud         :  [ N x M ]
//    udd        :  [ N x M ]
//    uddd       :  [ N x M ]
//
// Arguments    : double pseudoJerk
//                double k_vec
//                bool isEnd
//                double *u
//                double *ud
//                double *udd
//                double *uddd
// Return Type  : void
//
namespace ocn {
void constJerkU(double pseudoJerk, double k_vec, bool isEnd, double *u, double *ud, double *udd,
                double *uddd)
{
    double b_unnamed_idx_0;
    double unnamed_idx_0;
    // 'constJerkU:16' if( coder.target( "MATLAB" ) )
    // 'constJerkU:22' if( isEnd )
    if (isEnd) {
        // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
        // 'constJerkU:24' k_vec  = k_max - k_vec;
        k_vec = std::pow(6.0 / pseudoJerk, 0.33333333333333331) - k_vec;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    *uddd = pseudoJerk;
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    *udd = pseudoJerk * k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    *ud = pseudoJerk * std::pow(k_vec, 2.0) / 2.0;
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    *u = pseudoJerk * std::pow(k_vec, 3.0) / 6.0;
    // 'constJerkU:33' u( u > 1 ) = 1;
    unnamed_idx_0 = *u;
    if (*u > 1.0) {
        unnamed_idx_0 = 1.0;
    }
    // 'constJerkU:34' u( u < 0 ) = 0;
    b_unnamed_idx_0 = unnamed_idx_0;
    if (unnamed_idx_0 < 0.0) {
        b_unnamed_idx_0 = 0.0;
    }
    *u = b_unnamed_idx_0;
    // 'constJerkU:36' if( isEnd )
    if (isEnd) {
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        *u = 1.0 - b_unnamed_idx_0;
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        *udd = -*udd;
        // 'constJerkU:40' uddd = uddd;
    }
}

} // namespace ocn

//
// File trailer for constJerkU.cpp
//
// [EOF]
//
