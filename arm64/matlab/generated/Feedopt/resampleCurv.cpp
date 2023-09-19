//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
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
    double Tr;
    double d1;
    double d2;
    double d3;
    // 'resampleCurv:20' coder.inline( "never" );
    // 'resampleCurv:22' if coder.target( "MATLAB" )
    // 'resampleCurv:25' else
    //  Check for a zero stop
    // 'resampleCurv:27' if( state.isAStop )
    if (state->isAStop) {
        // 'resampleCurv:28' state = state.decreaseStopCounter();
        // 'ResampleStateClass:58' this.stopCounter    = this.stopCounter -1;
        state->stopCounter--;
        // 'ResampleStateClass:11' int32
        // 'ResampleStateClass:11' stopCounter
        // 'ResampleStateClass:59' if( this.stopCounter <= 0 )
        if (state->stopCounter <= 0) {
            // 'ResampleStateClass:60' this.isAStop        = false;
            state->isAStop = false;
            // 'ResampleStateClass:61' this.go_next        = true;
            state->go_next = true;
            // 'ResampleStateClass:62' this.isOutsideRange = true;
            state->isOutsideRange = true;
        }
    } else {
        double d;
        double u;
        double ud;
        double udd;
        double uddd;
        bool guard1;
        bool guard2;
        //  Compute new u state depending of zspdmode
        // 'resampleCurv:33' if( curv_mode == ZSpdMode.ZN )
        if (curv_mode == ZSpdMode_ZN) {
            double k_vec;
            // 'resampleCurv:34' [ time ] = constJerkTime(constJerk, state.u, false);
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
            // 'resampleCurv:35' isEnd = false;
            // 'resampleCurv:35' forcelimit = false;
            // 'resampleCurv:36' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:37'             forcelimit );
            k_vec = std::pow(state->u * 6.0 / constJerk, 0.33333333333333331) + state->dt;
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
            u = constJerk * std::pow(k_vec, 3.0) / 6.0;
            // 'constJerkU:32' if( forceLimits )
            // 'constJerkU:37' if( isEnd )
        } else if (curv_mode == ZSpdMode_NZ) {
            double b_k_vec;
            double k_vec_tmp;
            // 'resampleCurv:38' elseif( curv_mode == ZSpdMode.NZ )
            // 'resampleCurv:39' [ time ] = constJerkTime(constJerk, state.u, true);
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
            // 'resampleCurv:40' isEnd = true;
            // 'resampleCurv:40' forcelimit = false;
            // 'resampleCurv:41' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:42'             forcelimit );
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
                ((k_vec_tmp - std::pow((1.0 - state->u) * 6.0 / constJerk, 0.33333333333333331)) +
                 state->dt);
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
            u = 1.0 - constJerk * std::pow(b_k_vec, 3.0) / 6.0;
            // 'constJerkU:39' ud   = ud;
            // 'constJerkU:40' udd  = -udd;
            udd = -(constJerk * b_k_vec);
            // 'constJerkU:41' uddd = uddd;
            uddd = constJerk;
        } else {
            double X[4];
            double b_u;
            double b_ud;
            double b_udd;
            double q;
            double u_tmp;
            int loop_ub;
            // 'resampleCurv:43' else
            // 'resampleCurv:44' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
            // 'resampleCurv:90' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
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
            // 'resampleCurv:92' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
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
            // 'resampleCurv:95' u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;
            u_tmp = state->u + b_ud * state->dt;
            b_u = u_tmp + b_udd * (state->dt * state->dt) / 2.0;
            //  Ensure u > uk
            // 'resampleCurv:98' if( u  <= uk )
            if (b_u <= state->u) {
                //  Taylor odre 1. Note since ud > 0
                // 'resampleCurv:100' u = uk + ud * dt;
                b_u = u_tmp;
            }
            u = b_u;
        }
        // 'resampleCurv:46' state.dt = dt;
        state->dt = dt;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
        //  Check the u state validity
        // 'resampleCurv:49' u = check_u_state_validity( u, state );
        // 'resampleCurv:122' assert( u > 0, "U parameter should not be negative during resampling"
        // ); 'resampleCurv:124' u  = state.u + check_minimum_precision( u - state.u );
        d = u - state->u;
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:108' if( isempty( dMin ) )
        // 'resampleCurv:110' if(d < dMin )
        if (d < 2.2204460492503131E-16) {
            // 'resampleCurv:110' d = dMin;
            d = 2.2204460492503131E-16;
        }
        u = state->u + d;
        //  Check if u is outside the range
        // 'resampleCurv:52' if( u > 1 )
        guard1 = false;
        guard2 = false;
        if (u > 1.0) {
            // 'resampleCurv:53' state.isOutsideRange = true;
            state->isOutsideRange = true;
            // 'resampleCurv:54' if( curv_mode == ZSpdMode.NN )
            if (curv_mode == ZSpdMode_NN) {
                double c_d;
                int b_loop_ub;
                int c_loop_ub;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int h_loop_ub;
                int i6;
                int i7;
                //  Numerical integration : Gauss-Legendre
                // 'resampleCurv:56' GL_X   = GaussLegendreX;
                // 'resampleCurv:57' GL_W   = GaussLegendreW;
                //  Linear mapping from[-1, 1] to [state.u, 1]
                // 'resampleCurv:60' uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
                uval.set_size(GaussLegendreX.size(0));
                b_loop_ub = GaussLegendreX.size(0);
                for (int i1{0}; i1 < b_loop_ub; i1++) {
                    uval[i1] =
                        (state->u * (1.0 - GaussLegendreX[i1]) + (GaussLegendreX[i1] + 1.0)) / 2.0;
                }
                // 'resampleCurv:61' Ival  = 1 ./ sqrt( bspline_eval_vec( Bl, coeff', uval ) );
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
                // 'resampleCurv:63' Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
                i7 = x.size(0);
                for (int b_k{0}; b_k < i7; b_k++) {
                    x[b_k] = std::sqrt(x[b_k]);
                }
                c_d = 0.0;
                h_loop_ub = x.size(0);
                for (int i9{0}; i9 < h_loop_ub; i9++) {
                    c_d += 1.0 / x[i9] * GaussLegendreW[i9];
                }
                Tr = c_d * (1.0 - state->u) / 2.0;
                guard2 = true;
            } else if (curv_mode == ZSpdMode_ZN) {
                // 'resampleCurv:64' elseif( curv_mode == ZSpdMode.ZN )
                // 'resampleCurv:65' [ time ] = constJerkTime(constJerk, [state.u, 1], false);
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
                // 'resampleCurv:66' Tr = time(2) - time(1);
                Tr = std::pow(6.0 / constJerk, 0.33333333333333331) -
                     std::pow(state->u * 6.0 / constJerk, 0.33333333333333331);
                guard2 = true;
            } else {
                // 'resampleCurv:67' else
                // 'resampleCurv:68' state = state.startZeroStopTime();
                // 'ResampleStateClass:67' this = this.setZeroStop( this.dt, this.zeroStopTime );
                // 'ResampleStateClass:31' this.dt             = dt;
                // 'ResampleStateClass:7' double
                state->dt = dt;
                // 'ResampleStateClass:7' dt
                // 'ResampleStateClass:32' this.u              = 1;
                // 'ResampleStateClass:3' double
                // 'ResampleStateClass:3' u
                state->u = 1.0;
                // 'ResampleStateClass:33' this.ud             = 0;
                // 'ResampleStateClass:4' double
                // 'ResampleStateClass:4' ud
                state->ud = 0.0;
                // 'ResampleStateClass:34' this.udd            = 0;
                // 'ResampleStateClass:5' double
                // 'ResampleStateClass:5' udd
                state->udd = 0.0;
                // 'ResampleStateClass:35' this.uddd           = 0;
                // 'ResampleStateClass:6' double
                // 'ResampleStateClass:6' uddd
                state->uddd = 0.0;
                // 'ResampleStateClass:36' this.go_next        = false;
                state->go_next = false;
                // 'ResampleStateClass:37' this.isOutsideRange = false;
                state->isOutsideRange = false;
                // 'ResampleStateClass:38' this.isAStop        = true;
                state->isAStop = true;
                // 'ResampleStateClass:39' this.stopCounter    = zeroStopTime;
                state->stopCounter = state->zeroStopTime;
                // 'ResampleStateClass:11' int32
                // 'ResampleStateClass:11' stopCounter
                // 'ResampleStateClass:40' this.zeroStopTime   = zeroStopTime;
                // 'ResampleStateClass:12' int32
                // 'ResampleStateClass:12' zeroStopTime
            }
        } else {
            // 'resampleCurv:73' else
            // 'resampleCurv:74' state.isOutsideRange = false;
            state->isOutsideRange = false;
            // 'resampleCurv:75' state = state.setU( u, ud, udd, uddd );
            state->u = u;
            state->ud = ud;
            state->udd = udd;
            state->uddd = uddd;
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
            double b_d;
            //  Ensure Tr <= dt and Tr >= 0
            // 'resampleCurv:72' state.dt = check_minimum_precision_dt( dt - Tr, dt );
            b_d = dt - Tr;
            //  check_minimum_precision : Avoid effect numerical problem
            // 'resampleCurv:116' if(d <= 0.0 )
            if (b_d <= 0.0) {
                // 'resampleCurv:116' d = 0.0;
                b_d = 0.0;
            }
            // 'resampleCurv:118' if(d > dt )
            if (b_d > dt) {
                // 'resampleCurv:118' d = dt;
                b_d = dt;
            }
            state->dt = b_d;
            // 'ResampleStateClass:7' double
            // 'ResampleStateClass:7' dt
            guard1 = true;
        }
        if (guard1) {
            //  Need to use the next curve structure
            // 'resampleCurv:79' if( u >= 1 )
            if (u >= 1.0) {
                // 'resampleCurv:80' state.go_next = true;
                state->go_next = true;
            } else {
                // 'resampleCurv:81' else
                // 'resampleCurv:82' state.go_next = false;
                state->go_next = false;
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
