//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:52:02
//

// Include Files
#include "resampleCurv.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types3.h"
#include "c_spline.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [ state, ud, udd, uddd ] = resampleCurv(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, curv_a, curv_b, GaussLegendreX, GaussLegendreW )
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
//  Bl                : Structure for the spline object used during the optimization
//  curv_mode         : Zero speed mode for the curve
//  coeff             : The resulting coeff of the optimization
//  useConstJerk      : ( Boolean ) Use a constant jerk for u
//  constJerk         : The actual value of the const jerk
//  dt                : Sampling time
//  curv_a            : Curve parameter a for affine transform
//  curv_b            : Curve parameter b for affine transform
//  GaussLegendreX    : Nodes used for the gauss-legendre integration
//  GaussLegendreW    : Weights used for the gauss-legendre integration
//
//  Outputs :
//  state         : Updated input state
//  ud            : Derivative of u
//  udd           : Second derivative of u
//  uddd          : Third derivatibe of u
//
// Arguments    : ResampleStateClass *state
//                unsigned long Bl_handle
//                ZSpdMode curv_mode
//                const ::coder::array<double, 1U> &coeff
//                double constJerk
//                double dt
//                const ::coder::array<double, 1U> &GaussLegendreX
//                const ::coder::array<double, 1U> &GaussLegendreW
// Return Type  : void
//
namespace ocn {
void resampleCurv(ResampleStateClass *state, unsigned long Bl_handle, ZSpdMode curv_mode,
                  const ::coder::array<double, 1U> &coeff, double constJerk, double dt,
                  const ::coder::array<double, 1U> &GaussLegendreX,
                  const ::coder::array<double, 1U> &GaussLegendreW)
{
    ::coder::array<double, 2U> b_coeff;
    ::coder::array<double, 2U> coeffs;
    ::coder::array<double, 1U> uval;
    ::coder::array<double, 1U> x;
    ::coder::array<double, 1U> xd;
    ::coder::array<double, 1U> xdd;
    ::coder::array<double, 1U> xddd;
    double b_u;
    double d1;
    double d2;
    double d3;
    double ud;
    double udd;
    double xdddk;
    double xddk;
    double xdk;
    double xk;
    // 'resampleCurv:29' coder.inline( "never" );
    // 'resampleCurv:31' if coder.target( "MATLAB" )
    // 'resampleCurv:34' else
    // 'resampleCurv:36' if      ( curv_mode == ZSpdMode.ZN )
    if (curv_mode == ZSpdMode_ZN) {
        double c_unnamed_idx_0;
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
        udd = constJerk * state->dt;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        ud = constJerk * (state->dt * state->dt) / 2.0;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u_tmp = constJerk * std::pow(state->dt, 3.0) / 6.0;
        // 'constJerkU:33' u( u > 1 ) = 1;
        unnamed_idx_0 = u_tmp;
        if (u_tmp > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        c_unnamed_idx_0 = unnamed_idx_0;
        if (unnamed_idx_0 < 0.0) {
            c_unnamed_idx_0 = 0.0;
        }
        // 'constJerkU:36' if( isEnd )
        b_u = c_unnamed_idx_0;
        // 'resampleCurv:39' if( u == 1 )
        if (c_unnamed_idx_0 == 1.0) {
            // 'resampleCurv:40' u = constJerk .* state.dt .^3 / 6;
            b_u = u_tmp;
        }
        // 'resampleCurv:42' state.dt = state.dt + dt;
        state->dt += dt;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
    } else if (curv_mode == ZSpdMode_NZ) {
        double b_unnamed_idx_0;
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
        ud = constJerk * (k_vec * k_vec) / 2.0;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u = constJerk * std::pow(k_vec, 3.0) / 6.0;
        // 'constJerkU:33' u( u > 1 ) = 1;
        b_unnamed_idx_0 = u;
        if (u > 1.0) {
            b_unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        d_unnamed_idx_0 = b_unnamed_idx_0;
        if (b_unnamed_idx_0 < 0.0) {
            d_unnamed_idx_0 = 0.0;
        }
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        udd = -(constJerk * k_vec);
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
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
    } else {
        double X[4];
        double b_u_tmp;
        double b_ud;
        double b_udd;
        double d_u;
        double q;
        int loop_ub;
        // 'resampleCurv:52' else
        // 'resampleCurv:53' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
        // 'resampleCurv:99' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
        coeffs.set_size(1, coeff.size(0));
        loop_ub = coeff.size(0);
        for (int i{0}; i < loop_ub; i++) {
            coeffs[i] = coeff[i];
        }
        q = state->u;
        //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
        // 'bspline_eval:3' X = zeros(1, 4);
        // 'bspline_eval:4' if( ~isreal(x) )
        // 'bspline_eval:8' if coder.target('matlab')
        // 'bspline_eval:15' if coder.target('rtw') || coder.target('mex')
        // 'bspline_eval:16' if x < 0
        if (state->u < 0.0) {
            // 'bspline_eval:17' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", state->u);
            fflush(stdout);
            // 'bspline_eval:18' x = 0;
            q = 0.0;
        } else if (state->u > 1.0) {
            // 'bspline_eval:19' elseif x > 1
            // 'bspline_eval:20' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
            printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", state->u);
            fflush(stdout);
            // 'bspline_eval:21' x = 1;
            q = 1.0;
        }
        // 'bspline_eval:23' my_path = StructTypeName.WDIR + "/src";
        // 'bspline_eval:24' coder.updateBuildInfo('addIncludePaths',my_path);
        // 'bspline_eval:25' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        // 'bspline_eval:26' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        // 'bspline_eval:27' coder.cinclude('c_spline.h');
        // 'bspline_eval:29' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
        // coder.rref(coeffs),... 'bspline_eval:30'                     x, coder.wref(X));
        c_bspline_eval(&Bl_handle, &coeffs[0], q, &X[0]);
        // 'bspline_eval:31' x       = X(1);
        // 'bspline_eval:32' xd      = X(2);
        // 'bspline_eval:33' xdd     = X(3);
        // 'bspline_eval:34' xddd    = X(4);
        // 'resampleCurv:101' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
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
        b_ud = std::sqrt(X[0]);
        // 'calcUfromQ:12' udd     = qd / 2;
        b_udd = X[1] / 2.0;
        // 'calcUfromQ:13' uddd    = qdd / 2 .* ud;
        ud = b_ud;
        udd = b_udd;
        //  Taylor odre 2
        // 'resampleCurv:104' u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;
        b_u_tmp = state->u + b_ud * state->dt;
        d_u = b_u_tmp + b_udd * (state->dt * state->dt) / 2.0;
        //  Ensure u > uk
        // 'resampleCurv:107' if( u  <= uk )
        if (d_u <= state->u) {
            //  Taylor odre 1. Note since ud > 0
            // 'resampleCurv:109' u = uk + ud * dt;
            d_u = b_u_tmp;
        }
        b_u = d_u;
        // 'resampleCurv:54' state.dt = dt;
        state->dt = dt;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
    }
    // 'resampleCurv:57' if( state.u > 0 )
    if (state->u > 0.0) {
        double du;
        double du_min;
        // 'resampleCurv:58' du      = u - state.u;
        du = b_u - state->u;
        // 'resampleCurv:59' du_min  = check_minimum_precision( du );
        du_min = du;
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:118' if( isempty( dMin ) )
        // 'resampleCurv:120' if(d < dMin )
        if (du < 2.2204460492503131E-16) {
            // 'resampleCurv:121' d = dMin;
            du_min = 2.2204460492503131E-16;
        }
        // 'resampleCurv:60' if( du_min > du )
        if (du_min > du) {
            // 'resampleCurv:60' u = state.u + du_min - du;
            b_u = (state->u + du_min) - du;
        }
    }
    // 'resampleCurv:63' if( u > 1 )
    if (b_u > 1.0) {
        double Tr;
        double d;
        // 'resampleCurv:64' if      ( curv_mode == ZSpdMode.NN )
        if (curv_mode == ZSpdMode_NN) {
            double c_u[2];
            double b_d;
            int b_loop_ub;
            int c_loop_ub;
            int d_loop_ub;
            int e_loop_ub;
            int f_loop_ub;
            int g_loop_ub;
            int i7;
            int i8;
            int i_loop_ub;
            // 'resampleCurv:65' [ q ]     = bspline_eval_vec( Bl, coeff', [ state.u, 1 ] );
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
                xk = c_u[k];
                b_coeff.set_size(1, coeff.size(0));
                for (int i1{0}; i1 < b_loop_ub; i1++) {
                    b_coeff[i1] = coeff[i1];
                }
                bspline_eval(Bl_handle, b_coeff, &xk, &xdk, &xddk, &xdddk);
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            //  Numerical integration : Gauss-Legendre
            // 'resampleCurv:67' GL_X   = GaussLegendreX;
            // 'resampleCurv:68' GL_W   = GaussLegendreW;
            //  Linear map from[-1, 1] to [state.u, 1]
            // 'resampleCurv:71' uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
            uval.set_size(GaussLegendreX.size(0));
            c_loop_ub = GaussLegendreX.size(0);
            for (int i2{0}; i2 < c_loop_ub; i2++) {
                uval[i2] =
                    (state->u * (1.0 - GaussLegendreX[i2]) + (GaussLegendreX[i2] + 1.0)) / 2.0;
            }
            // 'resampleCurv:72' Ival  = 1 ./ sqrt( bspline_eval_vec( Bl, coeff', uval ) );
            // 'bspline_eval_vec:3' x       = zeros(size(u));
            x.set_size(uval.size(0));
            d_loop_ub = uval.size(0);
            for (int i3{0}; i3 < d_loop_ub; i3++) {
                x[i3] = 0.0;
            }
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            xd.set_size(uval.size(0));
            e_loop_ub = uval.size(0);
            for (int i4{0}; i4 < e_loop_ub; i4++) {
                xd[i4] = 0.0;
            }
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            xdd.set_size(uval.size(0));
            f_loop_ub = uval.size(0);
            for (int i5{0}; i5 < f_loop_ub; i5++) {
                xdd[i5] = 0.0;
            }
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            xddd.set_size(uval.size(0));
            g_loop_ub = uval.size(0);
            for (int i6{0}; i6 < g_loop_ub; i6++) {
                xddd[i6] = 0.0;
            }
            // 'bspline_eval_vec:8' for k = 1:length(u)
            i7 = uval.size(0);
            for (int b_k{0}; b_k < i7; b_k++) {
                int h_loop_ub;
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                x[b_k] = uval[b_k];
                h_loop_ub = coeff.size(0);
                b_coeff.set_size(1, coeff.size(0));
                for (int i9{0}; i9 < h_loop_ub; i9++) {
                    b_coeff[i9] = coeff[i9];
                }
                bspline_eval(Bl_handle, b_coeff, &x[b_k], &d1, &d2, &d3);
                xddd[b_k] = d3;
                xdd[b_k] = d2;
                xd[b_k] = d1;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            //  Gauss Legendre integration
            // 'resampleCurv:74' Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
            i8 = x.size(0);
            for (int c_k{0}; c_k < i8; c_k++) {
                x[c_k] = std::sqrt(x[c_k]);
            }
            b_d = 0.0;
            i_loop_ub = x.size(0);
            for (int i10{0}; i10 < i_loop_ub; i10++) {
                b_d += 1.0 / x[i10] * GaussLegendreW[i10];
            }
            Tr = b_d * (1.0 - state->u) / 2.0;
        } else {
            // 'resampleCurv:75' else
            // 'resampleCurv:76' Tuk = ( 6 * state.u / constJerk )^( 1 / 3 );
            // 'resampleCurv:77' T1  = ( 6 / constJerk )^( 1 / 3 );
            // 'resampleCurv:78' Tr  = T1 - Tuk;
            Tr = std::pow(6.0 / constJerk, 0.33333333333333331) -
                 std::pow(6.0 * state->u / constJerk, 0.33333333333333331);
        }
        //  Ensure Tr <= dt
        // 'resampleCurv:81' state.dt = check_minimum_precision_dt( dt - Tr, dt );
        d = dt - Tr;
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:128' if(d <= 0.0 )
        if (d <= 0.0) {
            // 'resampleCurv:129' d = 0.0;
            d = 0.0;
        }
        // 'resampleCurv:132' if(d > dt )
        if (d > dt) {
            // 'resampleCurv:133' d = dt;
            d = dt;
        }
        state->dt = d;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
        // 'resampleCurv:82' state.isOutsideRange = true;
        state->isOutsideRange = true;
    } else {
        // 'resampleCurv:83' else
        // 'resampleCurv:84' state.u     = u;
        state->u = b_u;
        // 'ResampleStateClass:3' double
        // 'ResampleStateClass:3' u
        // 'resampleCurv:85' state.ud    = ud;
        state->ud = ud;
        // 'ResampleStateClass:4' double
        // 'ResampleStateClass:4' ud
        // 'resampleCurv:86' state.udd   = udd;
        state->udd = udd;
        // 'ResampleStateClass:5' double
        // 'ResampleStateClass:5' udd
    }
    // 'resampleCurv:89' if( u >= 1 )
    if (b_u >= 1.0) {
        // 'resampleCurv:90' state.go_next = true;
        state->go_next = true;
    } else {
        // 'resampleCurv:91' else
        // 'resampleCurv:92' state.go_next = false;
        state->go_next = false;
    }
}

} // namespace ocn

//
// File trailer for resampleCurv.cpp
//
// [EOF]
//
