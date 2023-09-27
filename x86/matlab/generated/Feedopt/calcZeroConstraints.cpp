//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcZeroConstraints.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

// Include Files
#include "calcZeroConstraints.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
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
//  Inputs :
//  ctx   : The context
//  Curv  : The curve
//  isEnd : (boolean) Is the end of the curve
//  Outputs :
//  v_0   : Norm of the velocity
//  at_0  : Norm of the tangential acceleration
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
    // 'calcZeroConstraints:12' jps = curv.ConstJerk;
    // 'calcZeroConstraints:14' if( isEnd )
    // 'calcZeroConstraints:15' k  = 0;
    // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    // 'constJerkU:15' if( coder.target( "MATLAB" ) )
    // 'constJerkU:21' if( isEnd )
    // 'constJerkU:22' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_max = std::pow(6.0 / curv->ConstJerk, 0.33333333333333331);
    // 'constJerkU:23' k_vec  = k_max - k_vec;
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    u = curv->ConstJerk * std::pow(k_max, 3.0) / 6.0;
    // 'constJerkU:32' if( forceLimits )
    // 'constJerkU:33' u( u > 1 ) = 1;
    unnamed_idx_0 = u;
    if (u > 1.0) {
        unnamed_idx_0 = 1.0;
    }
    // 'constJerkU:34' u( u < 0 ) = 0;
    b_unnamed_idx_0 = unnamed_idx_0;
    if (unnamed_idx_0 < 0.0) {
        b_unnamed_idx_0 = 0.0;
    }
    // 'constJerkU:37' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:38' u    = 1 - u;
    // 'constJerkU:39' ud   = ud;
    // 'constJerkU:40' udd  = -udd;
    // 'constJerkU:41' uddd = uddd;
    // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
    j_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, 1.0 - b_unnamed_idx_0, r0D, r1D, r2D, r3D);
    // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd,
    // r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
    ud_vec = curv->ConstJerk * (k_max * k_max) / 2.0;
    udd_vec = -(curv->ConstJerk * k_max);
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //  Inputs :
    //    ud_vec  : [ 1 x M ] The vector of first derivative of u
    //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
    //    r0D     : [ 1 x M ] The vector of r
    //    r1D     : [ 1 x M ] The vector of first derivative of r
    //    r2D     : [ 1 x M ] The vector of second derivative of r
    //    r3D     : [ 1 x M ] The vector of second derivative of r
    //  Outputs :
    //    R   : [ N x M ] pose
    //    V   : [ N x M ] velocity
    //    A   : [ N x M ] acceleration
    //    J   : [ N x M ] jerk
    // 'calcRVAJfromUWithoutCurv:18' R = r0D;
    // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
    // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    y = ud_vec * ud_vec;
    // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
    //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
    //  acceleration.
    //  Inputs :
    //  V     : The velovity vector
    //  A     : The acceleration vector
    //  r1D   : The partial derivative of R
    //  Outputs :
    //  vNorm   : Norm of the velocity
    //  atNorm  : Norm of the tangential acceleration
    // 'calcNormVNormAT:12' vNorm   = MyNorm( V );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        double varargin_1;
        varargin_1 = r1D[i] * ud_vec;
        r[i] = std::pow(varargin_1, 2.0);
    }
    *vNorm = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(r1D.size(0));
    b_loop_ub = r1D.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double b_varargin_1;
        b_varargin_1 = r1D[i1];
        r[i1] = std::pow(b_varargin_1, 2.0);
    }
    n = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcNormVNormAT:14' atNorm  = MyNorm( A.*t );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
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
    *atNorm = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
}

//
// function [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd )
//
// calcZeroConstraints : Compute the velocity and acceleration
//  required for the continuity at zero start.
//  Inputs :
//  ctx   : The context
//  Curv  : The curve
//  isEnd : (boolean) Is the end of the curve
//  Outputs :
//  v_0   : Norm of the velocity
//  at_0  : Norm of the tangential acceleration
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
    // 'calcZeroConstraints:12' jps = curv.ConstJerk;
    // 'calcZeroConstraints:14' if( isEnd )
    // 'calcZeroConstraints:16' else
    // 'calcZeroConstraints:17' k   = ( 6 / jps )^( 1 / 3 );
    k_vec = std::pow(6.0 / curv->ConstJerk, 0.33333333333333331);
    // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    // 'constJerkU:15' if( coder.target( "MATLAB" ) )
    // 'constJerkU:21' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    u = curv->ConstJerk * std::pow(k_vec, 3.0) / 6.0;
    // 'constJerkU:32' if( forceLimits )
    // 'constJerkU:33' u( u > 1 ) = 1;
    unnamed_idx_0 = u;
    if (u > 1.0) {
        unnamed_idx_0 = 1.0;
    }
    // 'constJerkU:34' u( u < 0 ) = 0;
    b_unnamed_idx_0 = unnamed_idx_0;
    if (unnamed_idx_0 < 0.0) {
        b_unnamed_idx_0 = 0.0;
    }
    // 'constJerkU:37' if( isEnd )
    // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
    j_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, b_unnamed_idx_0, r0D, r1D, r2D, r3D);
    // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd,
    // r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
    ud_vec = curv->ConstJerk * (k_vec * k_vec) / 2.0;
    udd_vec = curv->ConstJerk * k_vec;
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //  Inputs :
    //    ud_vec  : [ 1 x M ] The vector of first derivative of u
    //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
    //    r0D     : [ 1 x M ] The vector of r
    //    r1D     : [ 1 x M ] The vector of first derivative of r
    //    r2D     : [ 1 x M ] The vector of second derivative of r
    //    r3D     : [ 1 x M ] The vector of second derivative of r
    //  Outputs :
    //    R   : [ N x M ] pose
    //    V   : [ N x M ] velocity
    //    A   : [ N x M ] acceleration
    //    J   : [ N x M ] jerk
    // 'calcRVAJfromUWithoutCurv:18' R = r0D;
    // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
    // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    y = ud_vec * ud_vec;
    // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
    //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
    //  acceleration.
    //  Inputs :
    //  V     : The velovity vector
    //  A     : The acceleration vector
    //  r1D   : The partial derivative of R
    //  Outputs :
    //  vNorm   : Norm of the velocity
    //  atNorm  : Norm of the tangential acceleration
    // 'calcNormVNormAT:12' vNorm   = MyNorm( V );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        double varargin_1;
        varargin_1 = r1D[i] * ud_vec;
        r[i] = std::pow(varargin_1, 2.0);
    }
    *vNorm = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(r1D.size(0));
    b_loop_ub = r1D.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double b_varargin_1;
        b_varargin_1 = r1D[i1];
        r[i1] = std::pow(b_varargin_1, 2.0);
    }
    n = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcNormVNormAT:14' atNorm  = MyNorm( A.*t );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
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
    *atNorm = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
}

} // namespace ocn

//
// File trailer for calcZeroConstraints.cpp
//
// [EOF]
//
