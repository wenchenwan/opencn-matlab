
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcZeroConstraints.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "calcZeroConstraints.h"
#include "EvalCurvStruct.h"
#include "ocn_assert.h"
#include "opencn_matlab_types111.h"
#include "queue_coder.h"
#include "sum.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd )
//
// calcZeroConstraints : Compute the velocity and acceleration
//  required for the continuity at zero start.
//
//  Inputs :
//  ctx       : The context
//  Curv      : The curve
//  isEnd     : (boolean) Is the end of the curve
//
//  Outputs :
//  vNorm     : Norm of the velocity
//  atNorm    : Norm of the tangential acceleration
//
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                double *vNorm
//                double *atNorm
// Return Type  : void
//
namespace ocn {
void b_calcZeroConstraints(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                           const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                           const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                           const int ctx_cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &ctx_cfg_indCart,
                           const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                           int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                           double *vNorm, double *atNorm)
{
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double b_unnamed_idx_0;
    double c_x;
    double k_max;
    double n;
    double u;
    double ud_vec;
    double udd_vec;
    double unnamed_idx_0;
    double y;
    int b_loop_ub;
    int i2;
    int loop_ub;
    // 'calcZeroConstraints:15' jps = curv.ConstJerk;
    // 'calcZeroConstraints:17' if( isEnd )
    // 'calcZeroConstraints:18' k  = 0;
    // 'calcZeroConstraints:23' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The constant Jerk value
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    //
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    // 'constJerkU:25' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_max = std::pow(6.0 / curv->ConstJerk, 0.33333333333333331);
    // 'constJerkU:26' k_vec  = k_max - k_vec;
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    u = curv->ConstJerk * std::pow(k_max, 3.0) / 6.0;
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    unnamed_idx_0 = u;
    if (u > 1.0) {
        unnamed_idx_0 = 1.0;
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_unnamed_idx_0 = unnamed_idx_0;
    if (unnamed_idx_0 < 0.0) {
        b_unnamed_idx_0 = 0.0;
    }
    // 'constJerkU:40' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:41' u    = 1 - u;
    // 'constJerkU:42' ud   = ud;
    // 'constJerkU:43' udd  = -udd;
    // 'constJerkU:44' uddd = uddd;
    // 'calcZeroConstraints:25' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
    k_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, 1.0 - b_unnamed_idx_0, r0D, r1D, r2D, r3D);
    // 'calcZeroConstraints:27' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd,
    // r0D, ... 'calcZeroConstraints:28'                           r1D, r2D, r3D );
    ud_vec = curv->ConstJerk * (k_max * k_max) / 2.0;
    udd_vec = -(curv->ConstJerk * k_max);
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //
    //  Inputs :
    //    ud_vec      : [ 1 x M ] The vector of first derivative of u
    //    udd_vec     : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
    //    r0D         : [ 1 x M ] The vector of r
    //    r1D         : [ 1 x M ] The vector of first derivative of r
    //    r2D         : [ 1 x M ] The vector of second derivative of r
    //    r3D         : [ 1 x M ] The vector of second derivative of r
    //
    //  Outputs :
    //    R           : [ N x M ] pose
    //    V           : [ N x M ] velocity
    //    A           : [ N x M ] acceleration
    //    J           : [ N x M ] jerk
    //
    // 'calcRVAJfromUWithoutCurv:21' R = r0D;
    // 'calcRVAJfromUWithoutCurv:22' V = r1D .* ud_vec;
    // 'calcRVAJfromUWithoutCurv:23' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    y = ud_vec * ud_vec;
    // 'calcRVAJfromUWithoutCurv:24' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec; 'calcZeroConstraints:30' [ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
    //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
    //  acceleration.
    //
    //  Inputs :
    //  V         : The velovity vector
    //  A         : The acceleration vector
    //  r1D       : The partial derivative of R
    //
    //  Outputs :
    //  vNorm     : Norm of the velocity
    //  atNorm    : Norm of the tangential acceleration
    //
    // 'calcNormVNormAT:15' vNorm   = MyNorm( V );
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
    r.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        double varargin_1;
        varargin_1 = r1D[i] * ud_vec;
        r[i] = std::pow(varargin_1, 2.0);
    }
    double x;
    x = coder::sum(r);
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
    *vNorm = std::sqrt(x);
    // 'calcNormVNormAT:16' t       = r1D / MyNorm( r1D );
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
    r.set_size(r1D.size(0));
    b_loop_ub = r1D.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double b_varargin_1;
        b_varargin_1 = r1D[i1];
        r[i1] = std::pow(b_varargin_1, 2.0);
    }
    double b_x;
    b_x = coder::sum(r);
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
    n = std::sqrt(b_x);
    // 'calcNormVNormAT:17' atNorm  = MyNorm( A.*t );
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
    if (r2D.size(0) == 1) {
        i2 = r1D.size(0);
    } else {
        i2 = r2D.size(0);
    }
    if ((r2D.size(0) == r1D.size(0)) && (i2 == r1D.size(0))) {
        int c_loop_ub;
        r.set_size(r2D.size(0));
        c_loop_ub = r2D.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            double c_varargin_1;
            c_varargin_1 = (r2D[i3] * y + r1D[i3] * udd_vec) * (r1D[i3] / n);
            r[i3] = std::pow(c_varargin_1, 2.0);
        }
    } else {
        binary_expand_op(r, r2D, y, r1D, udd_vec, n);
    }
    c_x = coder::sum(r);
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
    *atNorm = std::sqrt(c_x);
}

//
// function [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd )
//
// calcZeroConstraints : Compute the velocity and acceleration
//  required for the continuity at zero start.
//
//  Inputs :
//  ctx       : The context
//  Curv      : The curve
//  isEnd     : (boolean) Is the end of the curve
//
//  Outputs :
//  vNorm     : Norm of the velocity
//  atNorm    : Norm of the tangential acceleration
//
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                double *vNorm
//                double *atNorm
// Return Type  : void
//
void calcZeroConstraints(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                         const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                         const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                         const int ctx_cfg_maskRot_size[2],
                         const ::coder::array<int, 1U> &ctx_cfg_indCart,
                         const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                         int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv, double *vNorm,
                         double *atNorm)
{
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double b_unnamed_idx_0;
    double c_x;
    double k_vec;
    double n;
    double u;
    double ud_vec;
    double udd_vec;
    double unnamed_idx_0;
    double y;
    int b_loop_ub;
    int i2;
    int loop_ub;
    // 'calcZeroConstraints:15' jps = curv.ConstJerk;
    // 'calcZeroConstraints:17' if( isEnd )
    // 'calcZeroConstraints:19' else
    // 'calcZeroConstraints:20' k   = ( 6 / jps )^( 1 / 3 );
    k_vec = std::pow(6.0 / curv->ConstJerk, 0.33333333333333331);
    // 'calcZeroConstraints:23' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The constant Jerk value
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    //
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    u = curv->ConstJerk * std::pow(k_vec, 3.0) / 6.0;
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    unnamed_idx_0 = u;
    if (u > 1.0) {
        unnamed_idx_0 = 1.0;
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_unnamed_idx_0 = unnamed_idx_0;
    if (unnamed_idx_0 < 0.0) {
        b_unnamed_idx_0 = 0.0;
    }
    // 'constJerkU:40' if( isEnd )
    // 'calcZeroConstraints:25' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
    k_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, b_unnamed_idx_0, r0D, r1D, r2D, r3D);
    // 'calcZeroConstraints:27' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd,
    // r0D, ... 'calcZeroConstraints:28'                           r1D, r2D, r3D );
    ud_vec = curv->ConstJerk * (k_vec * k_vec) / 2.0;
    udd_vec = curv->ConstJerk * k_vec;
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //
    //  Inputs :
    //    ud_vec      : [ 1 x M ] The vector of first derivative of u
    //    udd_vec     : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
    //    r0D         : [ 1 x M ] The vector of r
    //    r1D         : [ 1 x M ] The vector of first derivative of r
    //    r2D         : [ 1 x M ] The vector of second derivative of r
    //    r3D         : [ 1 x M ] The vector of second derivative of r
    //
    //  Outputs :
    //    R           : [ N x M ] pose
    //    V           : [ N x M ] velocity
    //    A           : [ N x M ] acceleration
    //    J           : [ N x M ] jerk
    //
    // 'calcRVAJfromUWithoutCurv:21' R = r0D;
    // 'calcRVAJfromUWithoutCurv:22' V = r1D .* ud_vec;
    // 'calcRVAJfromUWithoutCurv:23' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    y = ud_vec * ud_vec;
    // 'calcRVAJfromUWithoutCurv:24' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec; 'calcZeroConstraints:30' [ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
    //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
    //  acceleration.
    //
    //  Inputs :
    //  V         : The velovity vector
    //  A         : The acceleration vector
    //  r1D       : The partial derivative of R
    //
    //  Outputs :
    //  vNorm     : Norm of the velocity
    //  atNorm    : Norm of the tangential acceleration
    //
    // 'calcNormVNormAT:15' vNorm   = MyNorm( V );
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
    r.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        double varargin_1;
        varargin_1 = r1D[i] * ud_vec;
        r[i] = std::pow(varargin_1, 2.0);
    }
    double x;
    x = coder::sum(r);
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
    *vNorm = std::sqrt(x);
    // 'calcNormVNormAT:16' t       = r1D / MyNorm( r1D );
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
    r.set_size(r1D.size(0));
    b_loop_ub = r1D.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double b_varargin_1;
        b_varargin_1 = r1D[i1];
        r[i1] = std::pow(b_varargin_1, 2.0);
    }
    double b_x;
    b_x = coder::sum(r);
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
    n = std::sqrt(b_x);
    // 'calcNormVNormAT:17' atNorm  = MyNorm( A.*t );
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
    if (r2D.size(0) == 1) {
        i2 = r1D.size(0);
    } else {
        i2 = r2D.size(0);
    }
    if ((r2D.size(0) == r1D.size(0)) && (i2 == r1D.size(0))) {
        int c_loop_ub;
        r.set_size(r2D.size(0));
        c_loop_ub = r2D.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            double c_varargin_1;
            c_varargin_1 = (r2D[i3] * y + r1D[i3] * udd_vec) * (r1D[i3] / n);
            r[i3] = std::pow(c_varargin_1, 2.0);
        }
    } else {
        binary_expand_op(r, r2D, y, r1D, udd_vec, n);
    }
    c_x = coder::sum(r);
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
    *atNorm = std::sqrt(c_x);
}

} // namespace ocn

//
// File trailer for calcZeroConstraints.cpp
//
// [EOF]
//
