//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

// Include Files
#include "resampleCurv.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types31.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [ state, ud, udd, uddd ] = resampleCurv(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, ...
//     curv_a, curv_b)
//
// resampleCurv :
//
//  Inputs :
//
//  state         : Structure about the current state
//            u :       curv parameter [0,1]
//            go_next : {0 : stay at on the same curve, 1 : move to the next}
//            dt :      time step used for the discretization
//            isOutsideRange : {true : if u is out of range}
//  Bl            : Structure for the spline object used during the optimization
//  curv_mode     : Zero speed mode for the curve
//  coeff         : The resulting coeff of the optimization
//  useConstJerk  : ( Boolean ) Use a constant jerk for u
//  constJerk     : The actual value of the const jerk
//  dt            : Sampling time
//  curv_a        :  Curve parameter a for affine transform
//  curv_b        :  Curve parameter b for affine transform
//
//  Outputs :
//  state         : Updated input state
//  ud            : Derivative of u
//  udd           : Second derivative of u
//  uddd          : Third derivatibe of u
//
// Arguments    : ResampleStateClass *state
//                const uint64m_T Bl_handle
//                ZSpdMode curv_mode
//                const ::coder::array<double, 1U> &coeff
//                double constJerk
//                double dt
// Return Type  : void
//
namespace ocn {
void resampleCurv(ResampleStateClass *state, const uint64m_T Bl_handle, ZSpdMode curv_mode,
                  const ::coder::array<double, 1U> &coeff, double constJerk, double dt)
{
    ::coder::array<double, 2U> b_coeff;
    ::coder::array<double, 2U> coeffs;
    double X[4];
    double q_data[4];
    double c_u[2];
    double x[2];
    double b_u;
    double du;
    double du_min;
    double ud;
    double xdddk;
    double xddk;
    double xdk;
    // 'resampleCurv:28' coder.inline( "never" );
    // 'resampleCurv:30' if false && coder.target( "MATLAB" )
    // 'resampleCurv:34' else
    // 'resampleCurv:36' if      ( curv_mode == ZSpdMode.ZN )
    if (curv_mode == ZSpdMode_ZN) {
        double b_unnamed_idx_0;
        double u_tmp;
        double unnamed_idx_0;
        // 'resampleCurv:37' [ u, ud, udd, uddd ] = constJerkU( constJerk, state.dt, false );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
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
        // 'constJerkU:16' if( coder.target( "MATLAB" ) )
        // 'constJerkU:22' if( isEnd )
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        ud = constJerk * std::pow(state->dt, 2.0) / 2.0;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u_tmp = constJerk * std::pow(state->dt, 3.0) / 6.0;
        // 'constJerkU:33' u( u > 1 ) = 1;
        unnamed_idx_0 = u_tmp;
        if (u_tmp > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        b_unnamed_idx_0 = unnamed_idx_0;
        if (unnamed_idx_0 < 0.0) {
            b_unnamed_idx_0 = 0.0;
        }
        // 'constJerkU:36' if( isEnd )
        b_u = b_unnamed_idx_0;
        // 'resampleCurv:39' if( u == 1 )
        if (b_unnamed_idx_0 == 1.0) {
            // 'resampleCurv:40' u = constJerk .* state.dt .^3 / 6;
            b_u = u_tmp;
        }
        // 'resampleCurv:42' state.dt = state.dt + dt;
        state->dt += dt;
        // 'ResampleStateClass:6' double
        // 'ResampleStateClass:6' dt
    } else if (curv_mode == ZSpdMode_NZ) {
        double c_unnamed_idx_0;
        double d_unnamed_idx_0;
        double k_vec;
        double u;
        // 'resampleCurv:44' elseif  ( curv_mode == ZSpdMode.NZ )
        // 'resampleCurv:45' [ u, ud, udd, uddd ] = constJerkU( constJerk, state.dt, true );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
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
        // 'constJerkU:16' if( coder.target( "MATLAB" ) )
        // 'constJerkU:22' if( isEnd )
        // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
        // 'constJerkU:24' k_vec  = k_max - k_vec;
        k_vec = std::pow(6.0 / constJerk, 0.33333333333333331) - state->dt;
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        ud = constJerk * std::pow(k_vec, 2.0) / 2.0;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u = constJerk * std::pow(k_vec, 3.0) / 6.0;
        // 'constJerkU:33' u( u > 1 ) = 1;
        c_unnamed_idx_0 = u;
        if (u > 1.0) {
            c_unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        d_unnamed_idx_0 = c_unnamed_idx_0;
        if (c_unnamed_idx_0 < 0.0) {
            d_unnamed_idx_0 = 0.0;
        }
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        b_u = 1.0 - d_unnamed_idx_0;
        // 'resampleCurv:47' if( u == 1 )
        if (1.0 - d_unnamed_idx_0 == 1.0) {
            // 'resampleCurv:48' k_max  = ( 6 / constJerk )^( 1 / 3 );
            // 'resampleCurv:49' u = 1 - constJerk .* ( k_max - state.dt ) .^3 / 6;
            b_u = 1.0 -
                  constJerk *
                      std::pow(std::pow(6.0 / constJerk, 0.33333333333333331) - state->dt, 3.0) /
                      6.0;
        }
        // 'resampleCurv:51' state.dt = state.dt + dt;
        state->dt += dt;
        // 'ResampleStateClass:6' double
        // 'ResampleStateClass:6' dt
    } else {
        double q;
        double ud_tmp;
        int loop_ub;
        // 'resampleCurv:52' else
        // 'resampleCurv:53' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
        // 'resampleCurv:93' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
        coeffs.set_size(1, coeff.size(0));
        loop_ub = coeff.size(0);
        for (int i{0}; i < loop_ub; i++) {
            coeffs[i] = coeff[i];
        }
        q = state->u;
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if coder.target('matlab')
        // 'bspline_eval:11' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:12' if x < 0
        if (state->u < 0.0) {
            // 'bspline_eval:13' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", state->u);
            fflush(stdout);
            // 'bspline_eval:14' x = 0;
            q = 0.0;
        } else if (state->u > 1.0) {
            // 'bspline_eval:15' elseif x > 1
            // 'bspline_eval:16' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", state->u);
            fflush(stdout);
            // 'bspline_eval:17' x = 1;
            q = 1.0;
        }
        // 'bspline_eval:19' coder.updateBuildInfo('addSourceFiles','c_spline.c',
        // '$(START_DIR)/src'); 'bspline_eval:20' coder.updateBuildInfo('addLinkFlags',
        // LibInfo.gsl.lflags); 'bspline_eval:21' coder.cinclude('src/c_spline.h');
        // 'bspline_eval:22' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:23'                     x, coder.wref(X));
        c_bspline_eval(&Bl_handle, &coeffs[0], q, &X[0]);
        // 'bspline_eval:24' x       = X(1);
        // 'bspline_eval:25' xd      = X(2);
        // 'bspline_eval:26' xdd     = X(3);
        // 'bspline_eval:27' xddd    = X(4);
        // 'resampleCurv:95' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
        //  calcQfromU : Compute q( u ) based on u and its derivatives.
        //  Inputs :
        //  q     : [ N x M ] q( u )
        //  qd    : [ N x M ] First derivative of q
        //  qdd   : [ N x M ] Second derivative of q
        //  Outputs :
        //  ud    : [ N x M ] First derivative of u
        //  udd   : [ N x M ] Second derivative of u
        //  uddd  : [ N x M ] Third derivative of u
        // 'calcUfromQ:11' ud      = sqrt( q );
        ud_tmp = std::sqrt(X[0]);
        ud = ud_tmp;
        // 'calcUfromQ:12' udd     = qd / 2;
        // 'calcUfromQ:13' uddd    = qdd / 2 .* ud;
        // 'resampleCurv:97' u = uk + mysqrt( q ) * dt + ( qd * dt ^ 2 ) / 4;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        b_u = (state->u + ud_tmp * state->dt) + X[1] * (state->dt * state->dt) / 4.0;
        // 'resampleCurv:54' state.dt = dt;
        state->dt = dt;
        // 'ResampleStateClass:6' double
        // 'ResampleStateClass:6' dt
    }
    // 'resampleCurv:57' du      = u - state.u;
    du = b_u - state->u;
    // 'resampleCurv:58' du_min  = check_minimum_precision( du );
    du_min = du;
    //  check_minimum_precision : Avoid effect numerical problem
    // 'resampleCurv:102' MIN_PRES = eps;
    // 'resampleCurv:103' if(d < MIN_PRES)
    if (du < 2.2204460492503131E-16) {
        // 'resampleCurv:103' d = MIN_PRES;
        du_min = 2.2204460492503131E-16;
    }
    // 'resampleCurv:59' if( du_min > du )
    if (du_min > du) {
        // 'resampleCurv:59' u = state.u + du_min - du;
        b_u = (state->u + du_min) - du;
    }
    // 'resampleCurv:61' if( u > 1 )
    if (b_u > 1.0) {
        double d;
        int q_size_idx_0;
        int q_size_idx_1;
        // 'resampleCurv:62' if      ( curv_mode == ZSpdMode.NN )
        if (curv_mode == ZSpdMode_NN) {
            int b_loop_ub;
            // 'resampleCurv:63' [ q ]     = bspline_eval_vec( Bl, coeff', [ state.u, 1 ] );
            c_u[0] = state->u;
            c_u[1] = 1.0;
            // 'bspline_eval_vec:3' x       = zeros(size(u));
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            // 'bspline_eval_vec:8' for k = 1:length(u)
            b_loop_ub = coeff.size(0);
            for (int k{0}; k < 2; k++) {
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                x[k] = c_u[k];
                b_coeff.set_size(1, coeff.size(0));
                for (int i1{0}; i1 < b_loop_ub; i1++) {
                    b_coeff[i1] = coeff[i1];
                }
                bspline_eval(Bl_handle, b_coeff, &x[k], &xdk, &xddk, &xdddk);
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            q_size_idx_0 = 1;
            q_size_idx_1 = 2;
            q_data[0] = x[0];
            q_data[1] = x[1];
        } else {
            double b_k_vec;
            bool isEnd;
            // 'resampleCurv:64' else
            // 'resampleCurv:65' if  ( curv_mode == ZSpdMode.NZ )
            if (curv_mode == ZSpdMode_NZ) {
                // 'resampleCurv:66' isEnd = true;
                isEnd = true;
            } else {
                // 'resampleCurv:67' else
                // 'resampleCurv:68' isEnd = false;
                isEnd = false;
            }
            // 'resampleCurv:70' k_max  = ( 6 / constJerk )^( 1 / 3 );
            b_k_vec = std::pow(6.0 / constJerk, 0.33333333333333331);
            // 'resampleCurv:71' [ ~, u1d, ~, ~ ] = constJerkU( constJerk, k_max, isEnd );
            //  constJerkU : Compute u and its derivative based on the pseudo jerk
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
            // 'constJerkU:16' if( coder.target( "MATLAB" ) )
            // 'constJerkU:22' if( isEnd )
            if (isEnd) {
                // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
                // 'constJerkU:24' k_vec  = k_max - k_vec;
                b_k_vec = 0.0;
            }
            //  Compute u and its derivatives based on constant jerk
            // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
            // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
            // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
            // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
            // 'constJerkU:33' u( u > 1 ) = 1;
            // 'constJerkU:34' u( u < 0 ) = 0;
            // 'constJerkU:36' if( isEnd )
            // 'resampleCurv:72' q = [ state.ud; u1d ] .^2;
            q_size_idx_0 = 2;
            q_size_idx_1 = 1;
            q_data[0] = std::pow(state->ud, 2.0);
            q_data[1] = std::pow(constJerk * std::pow(b_k_vec, 2.0) / 2.0, 2.0);
        }
        // 'resampleCurv:75' Tr       = 2 * ( 1 - state.u ) / ( sqrt( q( end ) ) + sqrt( q( 1 ) ) );
        // 'resampleCurv:76' state.dt = check_minimum_precision( dt - Tr );
        d = dt - 2.0 * (1.0 - state->u) /
                     (std::sqrt(q_data[q_size_idx_0 * q_size_idx_1 - 1]) + std::sqrt(q_data[0]));
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:102' MIN_PRES = eps;
        // 'resampleCurv:103' if(d < MIN_PRES)
        if (d < 2.2204460492503131E-16) {
            // 'resampleCurv:103' d = MIN_PRES;
            d = 2.2204460492503131E-16;
        }
        state->dt = d;
        // 'ResampleStateClass:6' double
        // 'ResampleStateClass:6' dt
        // 'resampleCurv:77' state.isOutsideRange = true;
        state->isOutsideRange = true;
    } else {
        // 'resampleCurv:78' else
        // 'resampleCurv:79' state.u     = u;
        state->u = b_u;
        // 'ResampleStateClass:3' double
        // 'ResampleStateClass:3' u
        // 'resampleCurv:80' state.ud    = ud;
        state->ud = ud;
        // 'ResampleStateClass:4' double
        // 'ResampleStateClass:4' ud
    }
    // 'resampleCurv:83' if( u >= 1 )
    if (b_u >= 1.0) {
        // 'resampleCurv:84' state.go_next = true;
        state->go_next = true;
    } else {
        // 'resampleCurv:85' else
        // 'resampleCurv:86' state.go_next = false;
        state->go_next = false;
    }
}

} // namespace ocn

//
// File trailer for resampleCurv.cpp
//
// [EOF]
//
