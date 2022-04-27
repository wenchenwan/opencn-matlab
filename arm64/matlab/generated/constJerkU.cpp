//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constJerkU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

// Include Files
#include "constJerkU.h"
#include <cmath>

// Function Definitions
//
// function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, a, b )
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
//                double a
//                double b
//                double *u
//                double *ud
//                double *udd
//                double *uddd
// Return Type  : void
//
namespace ocn {
void constJerkU(double pseudoJerk, double k_vec, bool isEnd, double a, double b, double *u,
                double *ud, double *udd, double *uddd)
{
    // 'constJerkU:16' if( coder.target( "MATLAB" ) )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:23' uddd    = pseudoJerk .* ones( size( k_vec ) );
    *uddd = pseudoJerk;
    // 'constJerkU:24' udd     = pseudoJerk .* k_vec;
    *udd = pseudoJerk * k_vec;
    // 'constJerkU:25' ud      = pseudoJerk .* k_vec .^2 / 2;
    *ud = pseudoJerk * std::pow(k_vec, 2.0) / 2.0;
    // 'constJerkU:26' u       = pseudoJerk .* k_vec .^3 / 6;
    *u = pseudoJerk * std::pow(k_vec, 3.0) / 6.0;
    // 'constJerkU:28' if( isEnd )
    if (isEnd) {
        //  Reverse time ( Backward integration )
        // 'constJerkU:29' u    = 1 - u;
        *u = 1.0 - *u;
        // 'constJerkU:30' ud   = -ud;
        *ud = -*ud;
        // 'constJerkU:31' udd  = -udd;
        *udd = -*udd;
        // 'constJerkU:32' uddd = -uddd;
        *uddd = -pseudoJerk;
    }
    // 'constJerkU:35' u    = ( u - b ) / a;
    *u = (*u - b) / a;
    // 'constJerkU:36' ud   = ud / a;
    *ud /= a;
    // 'constJerkU:37' udd  = udd / a;
    *udd /= a;
    // 'constJerkU:38' uddd = uddd / a;
    *uddd /= a;
}

} // namespace ocn

//
// File trailer for constJerkU.cpp
//
// [EOF]
//
