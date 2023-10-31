
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "resampleCurv.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types11.h"
#include "c_spline.h"
#include "coder_array.h"
#include <cmath>
#include <math.h>
#include <stdio.h>

// Function Definitions
//
// function [ state ] = resampleCurv(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, GaussLegendreX, GaussLegendreW )
//
// resampleCurv :
//
//  Inputs :
//
//  state             : Structure containing the current state
//  Bl                : Structure for the spline object used during the optimization
//  curv_mode         : Zero speed mode for the curve
//  coeff             : The resulting coeff of the optimization
//  useConstJerk      : ( Boolean ) Use a constant jerk for u
//  constJerk         : The actual value of the const jerk
//  dt                : Sampling time
//  GaussLegendreX    : Nodes used for the gauss-legendre integration
//  GaussLegendreW    : Weights used for the gauss-legendre integration
//
//  Outputs :
//  state         : Updated input state
//
// Arguments    : ResampleStateClass *b_state
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
void resampleCurv(ResampleStateClass *b_state, unsigned long Bl_handle, ZSpdMode curv_mode,
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
    double Tr;
    double d1;
    double d2;
    double d3;
    int exponent;
    // 'resampleCurv:20' coder.inline( "never" );
    // 'resampleCurv:22' if( coder.target( "MATLAB" ) )
    // 'resampleCurv:26' if coder.target( "MATLAB" )
    // 'resampleCurv:29' else
    //  Check for a zero stop
    // 'resampleCurv:31' if( state.isAStop )
    if (b_state->isAStop) {
        // 'resampleCurv:32' state = state.decreaseStopCounter();
        // 'ResampleStateClass:58' this.stopCounter    = this.stopCounter -1;
        b_state->stopCounter--;
        // 'ResampleStateClass:11' int32
        // 'ResampleStateClass:11' stopCounter
        // 'ResampleStateClass:59' if( this.stopCounter <= 0 )
        if (b_state->stopCounter <= 0) {
            // 'ResampleStateClass:60' this.isAStop        = false;
            b_state->isAStop = false;
            // 'ResampleStateClass:61' this.go_next        = true;
            b_state->go_next = true;
            // 'ResampleStateClass:62' this.isOutsideRange = true;
            b_state->isOutsideRange = true;
        }
    } else {
        double b_u;
        double ud;
        double udd;
        double uddd;
        bool guard1;
        bool guard2;
        //  Compute new u state depending of zspdmode
        // 'resampleCurv:37' if( curv_mode == ZSpdMode.ZN )
        if (curv_mode == ZSpdMode_ZN) {
            double k_vec;
            // 'resampleCurv:38' [ time ] = constJerkTime(constJerk, state.u, false);
            //  constJerkN : Compute k
            //  Inputs :
            //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
            //    u_vec      :  [ 1 x M ] The u vector
            //    isEnd      :  ( Boolean ) Is the end of the Curve
            //  Outputs :
            //    k_vec      :  [ 1 x M ] The time vector
            // 'constJerkTime:10' if( coder.target( "MATLAB" ) )
            // 'constJerkTime:16' if( isEnd )
            // 'constJerkTime:20' k_vec = (u_vec * 6 / pseudoJerk).^(1/3);
            // 'constJerkTime:22' if( isEnd )
            // 'resampleCurv:39' isEnd = false;
            // 'resampleCurv:39' forcelimit = false;
            // 'resampleCurv:40' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:41'             forcelimit );
            k_vec = std::pow(b_state->u * 6.0 / constJerk, 0.33333333333333331) + b_state->dt;
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
            uddd = constJerk;
            // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
            udd = constJerk * k_vec;
            // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
            ud = constJerk * (k_vec * k_vec) / 2.0;
            // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
            b_u = constJerk * std::pow(k_vec, 3.0) / 6.0;
            // 'constJerkU:32' if( forceLimits )
            // 'constJerkU:37' if( isEnd )
        } else if (curv_mode == ZSpdMode_NZ) {
            double b_k_vec;
            double k_vec_tmp;
            // 'resampleCurv:42' elseif( curv_mode == ZSpdMode.NZ )
            // 'resampleCurv:43' [ time ] = constJerkTime(constJerk, state.u, true);
            //  constJerkN : Compute k
            //  Inputs :
            //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
            //    u_vec      :  [ 1 x M ] The u vector
            //    isEnd      :  ( Boolean ) Is the end of the Curve
            //  Outputs :
            //    k_vec      :  [ 1 x M ] The time vector
            // 'constJerkTime:10' if( coder.target( "MATLAB" ) )
            // 'constJerkTime:16' if( isEnd )
            // 'constJerkTime:17' u_vec = 1 - u_vec;
            // 'constJerkTime:20' k_vec = (u_vec * 6 / pseudoJerk).^(1/3);
            // 'constJerkTime:22' if( isEnd )
            // 'constJerkTime:23' k_max   = ( 6 / pseudoJerk )^( 1 / 3 );
            // 'constJerkTime:24' k_vec   = k_max - k_vec;
            // 'resampleCurv:44' isEnd = true;
            // 'resampleCurv:44' forcelimit = false;
            // 'resampleCurv:45' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:46'             forcelimit );
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
            // 'constJerkU:23' k_vec  = k_max - k_vec;
            k_vec_tmp = std::pow(6.0 / constJerk, 0.33333333333333331);
            b_k_vec =
                k_vec_tmp -
                ((k_vec_tmp - std::pow((1.0 - b_state->u) * 6.0 / constJerk, 0.33333333333333331)) +
                 b_state->dt);
            //  Compute u and its derivatives based on constant jerk
            // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
            // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
            // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
            ud = constJerk * (b_k_vec * b_k_vec) / 2.0;
            // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
            // 'constJerkU:32' if( forceLimits )
            // 'constJerkU:37' if( isEnd )
            //  Reverse time ( Backward-like integration )
            // 'constJerkU:38' u    = 1 - u;
            b_u = 1.0 - constJerk * std::pow(b_k_vec, 3.0) / 6.0;
            // 'constJerkU:39' ud   = ud;
            // 'constJerkU:40' udd  = -udd;
            udd = -(constJerk * b_k_vec);
            // 'constJerkU:41' uddd = uddd;
            uddd = constJerk;
        } else {
            double X[4];
            double q;
            double q_tmp;
            double u;
            int loop_ub;
            // 'resampleCurv:47' else
            // 'resampleCurv:48' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
            // 'resampleCurv:128' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
            coeffs.set_size(1, coeff.size(0));
            loop_ub = coeff.size(0);
            for (int i{0}; i < loop_ub; i++) {
                coeffs[i] = coeff[i];
            }
            q_tmp = b_state->u;
            q = q_tmp;
            //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
            // 'bspline_eval:3' X = zeros(1, 4);
            // 'bspline_eval:5' ocn_assert( isreal(x), "x should be real", mfilename );
            // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
            // 'bspline_eval:8' if x < 0
            if (b_state->u < 0.0) {
                // 'bspline_eval:9' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
                printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", b_state->u);
                fflush(stdout);
                // 'bspline_eval:10' x = 0;
                q = 0.0;
            } else if (b_state->u > 1.0) {
                // 'bspline_eval:11' elseif x > 1
                // 'bspline_eval:12' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
                printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", b_state->u);
                fflush(stdout);
                // 'bspline_eval:13' x = 1;
                q = 1.0;
            }
            // 'bspline_eval:15' my_path = StructTypeName.WDIR + "/src";
            // 'bspline_eval:16' coder.updateBuildInfo('addIncludePaths',my_path);
            // 'bspline_eval:17' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
            // 'bspline_eval:18' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
            // 'bspline_eval:19' coder.cinclude('c_spline.h');
            // 'bspline_eval:21' coder.ceval('c_bspline_eval', coder.rref(Bl.handle),
            // coder.rref(coeffs),... 'bspline_eval:22'                     x, coder.wref(X));
            c_bspline_eval(&Bl_handle, &coeffs[0], q, &X[0]);
            // 'bspline_eval:23' x       = X(1);
            // 'bspline_eval:24' xd      = X(2);
            // 'bspline_eval:25' xdd     = X(3);
            // 'bspline_eval:26' xddd    = X(4);
            // 'resampleCurv:130' if( q < 0 )
            if (X[0] < 0.0) {
                //  Non-positive function, it is better to go out
                // 'resampleCurv:132' u = uk;
                u = q_tmp;
                // 'resampleCurv:132' ud = 0;
                ud = 0.0;
                // 'resampleCurv:132' udd = 0;
                udd = 0.0;
                // 'resampleCurv:132' uddd = 0;
                uddd = 0.0;
                // 'resampleCurv:133' if( coder.target( "MATLAB" ) )
            } else {
                double b_ud;
                double b_udd;
                double u_tmp;
                // 'resampleCurv:140' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
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
                uddd = X[2] / 2.0 * b_ud;
                ud = b_ud;
                udd = b_udd;
                //  Taylor odre 2
                // 'resampleCurv:143' u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;
                u_tmp = b_state->u + b_ud * b_state->dt;
                u = u_tmp + b_udd * (b_state->dt * b_state->dt) / 2.0;
                // + ( uddd * dt ^ 3 ) / 6;
                //  Ensure u > uk
                // 'resampleCurv:146' if( u  <= uk )
                if (u <= b_state->u) {
                    //  Taylor odre 1. Note since ud > 0
                    // 'resampleCurv:148' u = uk + ud * dt;
                    u = u_tmp;
                }
            }
            b_u = u;
        }
        // 'resampleCurv:50' state.dt = dt;
        b_state->dt = dt;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
        // 'resampleCurv:52' u = check_u_state_validity( u, state );
        // 'resampleCurv:197' if( isnan( u ) )
        // 'resampleCurv:205' if( ~isreal( u ) )
        // 'resampleCurv:213' if( u < 0 )
        // 'resampleCurv:220' if( ~( u > state.u ) )
        //  ocn_assert( u > 0, "U parameter should not be negative during resampling", mfilename);
        // 'resampleCurv:228' u  = check_minimum_precision( state.u, u );
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:155' if( ~( d_up > d_low ) )
        if (b_u <= b_state->u) {
            double absx;
            double r;
            // 'resampleCurv:156' d_up = d_up + eps( d_up );
            absx = std::abs(b_u);
            if (absx <= 2.2250738585072014E-308) {
                r = 4.94065645841247E-324;
            } else {
                frexp(absx, &exponent);
                r = std::ldexp(1.0, exponent - 53);
            }
            b_u += r;
        }
        //  Check if u is outside the range
        // 'resampleCurv:55' if( u > 1 )
        guard1 = false;
        guard2 = false;
        if (b_u > 1.0) {
            // 'resampleCurv:56' state.isOutsideRange = true;
            b_state->isOutsideRange = true;
            // 'resampleCurv:57' if( curv_mode == ZSpdMode.NN )
            if (curv_mode == ZSpdMode_NN) {
                double TrVec[4];
                double b_d;
                int b_loop_ub;
                int c_loop_ub;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int h_loop_ub;
                int i6;
                int i7;
                // 'resampleCurv:58' TrVec   = zeros( 1, 4 );
                TrVec[0] = 0.0;
                //  Numerical integration : Gauss-Legendre
                // 'resampleCurv:60' GL_X   = GaussLegendreX;
                // 'resampleCurv:61' GL_W   = GaussLegendreW;
                //  Linear mapping from[-1, 1] to [state.u, 1]
                // 'resampleCurv:64' uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
                uval.set_size(GaussLegendreX.size(0));
                b_loop_ub = GaussLegendreX.size(0);
                for (int i1{0}; i1 < b_loop_ub; i1++) {
                    uval[i1] =
                        (b_state->u * (1.0 - GaussLegendreX[i1]) + (GaussLegendreX[i1] + 1.0)) /
                        2.0;
                }
                // 'resampleCurv:65' Ival  = 1 ./ sqrt( bspline_eval_vec( Bl, coeff', uval ) );
                // 'bspline_eval_vec:3' x       = zeros(size(u));
                x.set_size(uval.size(0));
                c_loop_ub = uval.size(0);
                for (int i2{0}; i2 < c_loop_ub; i2++) {
                    x[i2] = 0.0;
                }
                // 'bspline_eval_vec:4' xd      = zeros(size(u));
                xd.set_size(uval.size(0));
                d_loop_ub = uval.size(0);
                for (int i3{0}; i3 < d_loop_ub; i3++) {
                    xd[i3] = 0.0;
                }
                // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                xdd.set_size(uval.size(0));
                e_loop_ub = uval.size(0);
                for (int i4{0}; i4 < e_loop_ub; i4++) {
                    xdd[i4] = 0.0;
                }
                // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                xddd.set_size(uval.size(0));
                f_loop_ub = uval.size(0);
                for (int i5{0}; i5 < f_loop_ub; i5++) {
                    xddd[i5] = 0.0;
                }
                // 'bspline_eval_vec:8' for k = 1:length(u)
                i6 = uval.size(0);
                for (int k{0}; k < i6; k++) {
                    int g_loop_ub;
                    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                    x[k] = uval[k];
                    g_loop_ub = coeff.size(0);
                    b_coeff.set_size(1, coeff.size(0));
                    for (int i8{0}; i8 < g_loop_ub; i8++) {
                        b_coeff[i8] = coeff[i8];
                    }
                    bspline_eval(Bl_handle, b_coeff, &x[k], &d1, &d2, &d3);
                    xddd[k] = d3;
                    xdd[k] = d2;
                    xd[k] = d1;
                    // 'bspline_eval_vec:10' x(k)    = xk;
                    // 'bspline_eval_vec:11' xd(k)   = xdk;
                    // 'bspline_eval_vec:12' xdd(k)  = xddk;
                    // 'bspline_eval_vec:13' xddd(k) = xdddk;
                }
                //  Gauss Legendre integration
                // 'resampleCurv:67' Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
                i7 = x.size(0);
                for (int b_k{0}; b_k < i7; b_k++) {
                    x[b_k] = std::sqrt(x[b_k]);
                }
                b_d = 0.0;
                h_loop_ub = x.size(0);
                for (int i9{0}; i9 < h_loop_ub; i9++) {
                    b_d += 1.0 / x[i9] * GaussLegendreW[i9];
                }
                Tr = b_d * (1.0 - b_state->u) / 2.0;
                // 'resampleCurv:69' if( ~isreal( Tr ) || isnan( Tr ) )
                // 'resampleCurv:73' if( Tr >= dt )
                if (Tr >= dt) {
                    double Delta;
                    double a;
                    double c_state;
                    double d4;
                    double ex;
                    double yVec_idx_0;
                    double yVec_idx_1;
                    double yVec_idx_2;
                    int iindx;
                    // 'resampleCurv:74' a = udd/2;
                    a = udd / 2.0;
                    // 'resampleCurv:74' b = ud;
                    // 'resampleCurv:74' c = state.u -1;
                    // 'resampleCurv:76' Delta   = b^2 - 4 * a * c;
                    Delta = ud * ud - 4.0 * a * (b_state->u - 1.0);
                    // 'resampleCurv:78' if( Delta <= 0)
                    if (Delta <= 0.0) {
                        // 'resampleCurv:79' TrVec( 2 )  = -c / b;
                        TrVec[1] = -(b_state->u - 1.0) / ud;
                        // 'resampleCurv:80' TrVec( 3 )  = -b / a;
                        TrVec[2] = -ud / a;
                    } else if (ud > 0.0) {
                        double b_TrVec_tmp;
                        // 'resampleCurv:81' elseif( b > 0 )
                        // 'resampleCurv:82' TrVec( 2 )  = 2 *  c / ( -b - sqrt(Delta) );
                        b_TrVec_tmp = -ud - std::sqrt(Delta);
                        TrVec[1] = 2.0 * (b_state->u - 1.0) / b_TrVec_tmp;
                        // 'resampleCurv:83' TrVec( 3 )  = (-b - sqrt(Delta) ) / ( 2 *  a );
                        TrVec[2] = b_TrVec_tmp / (2.0 * a);
                    } else {
                        double TrVec_tmp;
                        // 'resampleCurv:84' else
                        // 'resampleCurv:85' TrVec( 2 )  = (-b + sqrt(Delta) ) / ( 2 *  a );
                        TrVec_tmp = -ud + std::sqrt(Delta);
                        TrVec[1] = TrVec_tmp / (2.0 * a);
                        // 'resampleCurv:86' TrVec( 3 )  = 2 *  c / ( -b + sqrt(Delta) );
                        TrVec[2] = 2.0 * (b_state->u - 1.0) / TrVec_tmp;
                    }
                    // 'resampleCurv:89' TrVec( 4 )  = -c / b;
                    TrVec[3] = -(b_state->u - 1.0) / ud;
                    //  Check validity
                    // 'resampleCurv:92' TrVec( isnan( TrVec ) )     = dt;
                    // 'resampleCurv:93' TrVec( ~isreal( TrVec ) )   = dt;
                    // 'resampleCurv:94' TrVec( ~( TrVec >= 0 ) )    = dt;
                    // 'resampleCurv:95' TrVec( ~( TrVec <= dt ) )   = dt;
                    // 'resampleCurv:97' yVec            = abs( a * TrVec.^2 + b * TrVec + c );
                    c_state = b_state->u - 1.0;
                    d4 = 0.0;
                    if (dt < 0.0) {
                        d4 = dt;
                        TrVec[0] = dt;
                    }
                    yVec_idx_0 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + c_state);
                    d4 = TrVec[1];
                    if (TrVec[1] < 0.0) {
                        d4 = dt;
                        TrVec[1] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[1] = dt;
                    }
                    yVec_idx_1 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + c_state);
                    d4 = TrVec[2];
                    if (TrVec[2] < 0.0) {
                        d4 = dt;
                        TrVec[2] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[2] = dt;
                    }
                    yVec_idx_2 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + c_state);
                    d4 = TrVec[3];
                    if (TrVec[3] < 0.0) {
                        d4 = dt;
                        TrVec[3] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[3] = dt;
                    }
                    // 'resampleCurv:98' [ ~, ind ]      = min( yVec );
                    ex = yVec_idx_0;
                    iindx = -1;
                    if (yVec_idx_0 > yVec_idx_1) {
                        ex = yVec_idx_1;
                        iindx = 0;
                    }
                    if (ex > yVec_idx_2) {
                        ex = yVec_idx_2;
                        iindx = 1;
                    }
                    if (ex > std::abs((a * std::pow(d4, 2.0) + ud * d4) + c_state)) {
                        iindx = 2;
                    }
                    // 'resampleCurv:99' Tr              = TrVec( ind );
                    Tr = TrVec[iindx + 1];
                }
                guard2 = true;
            } else if (curv_mode == ZSpdMode_ZN) {
                // 'resampleCurv:102' elseif( curv_mode == ZSpdMode.ZN )
                // 'resampleCurv:103' [ time ] = constJerkTime(constJerk, [state.u, 1], false);
                //  constJerkN : Compute k
                //  Inputs :
                //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
                //    u_vec      :  [ 1 x M ] The u vector
                //    isEnd      :  ( Boolean ) Is the end of the Curve
                //  Outputs :
                //    k_vec      :  [ 1 x M ] The time vector
                // 'constJerkTime:10' if( coder.target( "MATLAB" ) )
                // 'constJerkTime:16' if( isEnd )
                // 'constJerkTime:20' k_vec = (u_vec * 6 / pseudoJerk).^(1/3);
                // 'constJerkTime:22' if( isEnd )
                // 'resampleCurv:104' Tr = time(2) - time(1);
                Tr = std::pow(6.0 / constJerk, 0.33333333333333331) -
                     std::pow(b_state->u * 6.0 / constJerk, 0.33333333333333331);
                guard2 = true;
            } else {
                // 'resampleCurv:105' else
                // 'resampleCurv:106' state = state.startZeroStopTime();
                // 'ResampleStateClass:67' this = this.setZeroStop( this.dt, this.zeroStopTime );
                // 'ResampleStateClass:31' this.dt             = dt;
                // 'ResampleStateClass:7' double
                b_state->dt = dt;
                // 'ResampleStateClass:7' dt
                // 'ResampleStateClass:32' this.u              = 1;
                // 'ResampleStateClass:3' double
                // 'ResampleStateClass:3' u
                b_state->u = 1.0;
                // 'ResampleStateClass:33' this.ud             = 0;
                // 'ResampleStateClass:4' double
                // 'ResampleStateClass:4' ud
                b_state->ud = 0.0;
                // 'ResampleStateClass:34' this.udd            = 0;
                // 'ResampleStateClass:5' double
                // 'ResampleStateClass:5' udd
                b_state->udd = 0.0;
                // 'ResampleStateClass:35' this.uddd           = 0;
                // 'ResampleStateClass:6' double
                // 'ResampleStateClass:6' uddd
                b_state->uddd = 0.0;
                // 'ResampleStateClass:36' this.go_next        = false;
                b_state->go_next = false;
                // 'ResampleStateClass:37' this.isOutsideRange = false;
                b_state->isOutsideRange = false;
                // 'ResampleStateClass:38' this.isAStop        = true;
                b_state->isAStop = true;
                // 'ResampleStateClass:39' this.stopCounter    = zeroStopTime;
                b_state->stopCounter = b_state->zeroStopTime;
                // 'ResampleStateClass:11' int32
                // 'ResampleStateClass:11' stopCounter
                // 'ResampleStateClass:40' this.zeroStopTime   = zeroStopTime;
                // 'ResampleStateClass:12' int32
                // 'ResampleStateClass:12' zeroStopTime
            }
        } else {
            // 'resampleCurv:111' else
            // 'resampleCurv:112' state.isOutsideRange = false;
            b_state->isOutsideRange = false;
            // 'resampleCurv:113' state = state.setU( u, ud, udd, uddd );
            b_state->u = b_u;
            b_state->ud = ud;
            b_state->udd = udd;
            b_state->uddd = uddd;
            // 'ResampleStateClass:44' this.u      = u;
            // 'ResampleStateClass:3' double
            // 'ResampleStateClass:3' u
            // 'ResampleStateClass:45' this.ud     = ud;
            // 'ResampleStateClass:4' double
            // 'ResampleStateClass:4' ud
            // 'ResampleStateClass:46' this.udd    = udd;
            // 'ResampleStateClass:5' double
            // 'ResampleStateClass:5' udd
            // 'ResampleStateClass:47' this.uddd   = uddd;
            // 'ResampleStateClass:6' double
            // 'ResampleStateClass:6' uddd
            guard1 = true;
        }
        if (guard2) {
            double d;
            //  Ensure Tr <= dt and Tr >= 0 and real
            // 'resampleCurv:110' state.dt = check_minimum_precision_dt( dt - Tr, dt );
            d = dt - Tr;
            //  check_minimum_precision : Avoid effect numerical problem
            // 'resampleCurv:163' if( isnan( d ) )
            // 'resampleCurv:171' if( ~isreal( d ) )
            // 'resampleCurv:179' if( d <= 0.0 )
            if (d <= 0.0) {
                // 'resampleCurv:180' d = 0.0;
                d = 0.0;
                // 'resampleCurv:181' if( coder.target( "MATLAB" ) )
            }
            //  if( d > dt )
            //      d = dt;
            //      disp("Tr should not be larger than Ts", mfilename);
            //      if( coder.target( "MATLAB" ) )
            //          DebugResampling.getInstance().increaseTTooLargeCounter();
            //      end
            //  end
            b_state->dt = d;
            // 'ResampleStateClass:7' double
            // 'ResampleStateClass:7' dt
            guard1 = true;
        }
        if (guard1) {
            //  Need to use the next curve structure
            // 'resampleCurv:117' if( u >= 1 )
            if (b_u >= 1.0) {
                // 'resampleCurv:118' state.go_next = true;
                b_state->go_next = true;
            } else {
                // 'resampleCurv:119' else
                // 'resampleCurv:120' state.go_next = false;
                b_state->go_next = false;
            }
        }
    }
}

} // namespace ocn

//
// File trailer for resampleCurv.cpp
//
// [EOF]
//
