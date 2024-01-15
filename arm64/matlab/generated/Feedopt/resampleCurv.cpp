
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
#include "ocn_assert.h"
#include "ocn_print1.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types11.h"
#include "string1.h"
#include "c_spline.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <stdio.h>

// Function Definitions
//
// function [ state ] = resampleCurv(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint )
//
// resampleCurv : Resampling step.
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
//  state             : Updated input state.
//
// Arguments    : ResampleStateClass *state
//                unsigned long Bl_handle
//                ZSpdMode curv_mode
//                const ::coder::array<double, 1U> &coeff
//                double constJerk
//                double dt
//                const ::coder::array<double, 1U> &GaussLegendreX
//                const ::coder::array<double, 1U> &GaussLegendreW
//                bool enablePrint
// Return Type  : void
//
namespace ocn {
void resampleCurv(ResampleStateClass *state, unsigned long Bl_handle, ZSpdMode curv_mode,
                  const ::coder::array<double, 1U> &coeff, double constJerk, double dt,
                  const ::coder::array<double, 1U> &GaussLegendreX,
                  const ::coder::array<double, 1U> &GaussLegendreW, bool enablePrint)
{
    coder::rtString obj;
    ::coder::array<double, 2U> b_coeff;
    ::coder::array<double, 2U> coeffs;
    ::coder::array<double, 1U> uval;
    ::coder::array<double, 1U> x;
    ::coder::array<double, 1U> xd;
    ::coder::array<double, 1U> xdd;
    ::coder::array<double, 1U> xddd;
    ::coder::array<bool, 1U> b_x;
    double Tr;
    double b_d;
    double d1;
    double d2;
    int exponent;
    char st[24];
    char obj2Value_data[23];
    // 'resampleCurv:21' coder.inline( "never" );
    // 'resampleCurv:23' if( coder.target( "MATLAB" ) )
    // 'resampleCurv:27' if coder.target( "MATLAB" )
    // 'resampleCurv:30' else
    //  Check for a zero stop
    // 'resampleCurv:32' if( state.isAStop )
    if (state->isAStop) {
        // 'resampleCurv:33' state = state.decreaseStopCounter();
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
        double u;
        double ud;
        double udd;
        double uddd;
        bool guard1;
        bool guard2;
        //  Compute new u state depending of zspdmode
        // 'resampleCurv:38' if( curv_mode == ZSpdMode.ZN )
        if (curv_mode == ZSpdMode_ZN) {
            double k_vec;
            // 'resampleCurv:39' [ time ] = constJerkTime(constJerk, state.u, false);
            //  constJerkTime : Compute the time vector for a given u vector based on a
            //                  constant jerk velocity profile.
            //
            //  Inputs :
            //    pseudoJerk  : Constant jerk value
            //    u_vec       : U vector
            //    isEnd       : Is the end of a curv
            //
            //  Outputs :
            //    k_vec       : Time vector
            //
            // 'constJerkTime:13' if( coder.target( "MATLAB" ) )
            // 'constJerkTime:19' if( isEnd )
            // 'constJerkTime:23' k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );
            // 'constJerkTime:25' if( isEnd )
            // 'resampleCurv:40' isEnd = false;
            // 'resampleCurv:40' forcelimit = false;
            // 'resampleCurv:41' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:42'             forcelimit );
            k_vec = std::pow(state->u * 6.0 / constJerk, 0.33333333333333331) + state->dt;
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
            uddd = constJerk;
            // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
            udd = constJerk * k_vec;
            // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
            ud = constJerk * (k_vec * k_vec) / 2.0;
            // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
            u = constJerk * std::pow(k_vec, 3.0) / 6.0;
            // 'constJerkU:35' if( forceLimits )
            // 'constJerkU:40' if( isEnd )
        } else if (curv_mode == ZSpdMode_NZ) {
            double b_k_vec;
            double k_vec_tmp;
            // 'resampleCurv:43' elseif( curv_mode == ZSpdMode.NZ )
            // 'resampleCurv:44' [ time ] = constJerkTime(constJerk, state.u, true);
            //  constJerkTime : Compute the time vector for a given u vector based on a
            //                  constant jerk velocity profile.
            //
            //  Inputs :
            //    pseudoJerk  : Constant jerk value
            //    u_vec       : U vector
            //    isEnd       : Is the end of a curv
            //
            //  Outputs :
            //    k_vec       : Time vector
            //
            // 'constJerkTime:13' if( coder.target( "MATLAB" ) )
            // 'constJerkTime:19' if( isEnd )
            // 'constJerkTime:20' u_vec = 1 - u_vec;
            // 'constJerkTime:23' k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );
            // 'constJerkTime:25' if( isEnd )
            // 'constJerkTime:26' k_max   = ( 6 / pseudoJerk )^( 1 / 3 );
            // 'constJerkTime:27' k_vec   = k_max - k_vec;
            // 'resampleCurv:45' isEnd = true;
            // 'resampleCurv:45' forcelimit = false;
            // 'resampleCurv:46' [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt,
            // isEnd, ... 'resampleCurv:47'             forcelimit );
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
            // 'constJerkU:26' k_vec  = k_max - k_vec;
            k_vec_tmp = std::pow(6.0 / constJerk, 0.33333333333333331);
            b_k_vec =
                k_vec_tmp -
                ((k_vec_tmp - std::pow((1.0 - state->u) * 6.0 / constJerk, 0.33333333333333331)) +
                 state->dt);
            //  Compute u and its derivatives based on constant jerk
            // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
            // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
            // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
            ud = constJerk * (b_k_vec * b_k_vec) / 2.0;
            // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
            // 'constJerkU:35' if( forceLimits )
            // 'constJerkU:40' if( isEnd )
            //  Reverse time ( Backward-like integration )
            // 'constJerkU:41' u    = 1 - u;
            u = 1.0 - constJerk * std::pow(b_k_vec, 3.0) / 6.0;
            // 'constJerkU:42' ud   = ud;
            // 'constJerkU:43' udd  = -udd;
            udd = -(constJerk * b_k_vec);
            // 'constJerkU:44' uddd = uddd;
            uddd = constJerk;
        } else {
            double X[4];
            double b_u;
            double q;
            double q_tmp;
            int loop_ub;
            // 'resampleCurv:48' else
            // 'resampleCurv:49' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt,
            // enablePrint ); 'resampleCurv:134' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
            coeffs.set_size(1, coeff.size(0));
            loop_ub = coeff.size(0);
            for (int i{0}; i < loop_ub; i++) {
                coeffs[i] = coeff[i];
            }
            q_tmp = state->u;
            q = q_tmp;
            //  bspline_eval  : Eval Bspline bases for a given set of points and
            //  coefficients
            //
            //  Inputs :
            //  Bl            : BSpline bases
            //  coeffs        : Coefficients used during the evaluation
            //  x             : Given set of points
            //
            //  Outputs:
            //  x             : Evaluated points
            //  xd            : Evaluated points derivative
            //  xdd           : Evaluated points 2nd derivative
            //  xddd          : Evaluated points 3rd derivative
            // 'bspline_eval:15' enablePrint = true;
            // 'bspline_eval:16' X = zeros(1, 4);
            // 'bspline_eval:17' ocn_assert( isreal( x ), "x should be real", mfilename );
            // 'bspline_eval:19' if coder.target( "MATLAB" )
            // 'bspline_eval:22' else
            // 'bspline_eval:23' if ( x < 0 )
            if (state->u < 0.0) {
                int obj2Value_size_idx_1;
                // 'bspline_eval:24' ocn_print( enablePrint, ...
                // 'bspline_eval:25'                 "ERROR: C_BSPLINE_EVAL: X < 0 (" + x + ")",
                // mfilename );
                if (state->u == 0.0) {
                    obj2Value_size_idx_1 = 1;
                    obj2Value_data[0] = '0';
                } else {
                    int resCount;
                    resCount = sprintf(&st[0], "%.16g", state->u);
                    obj2Value_size_idx_1 = resCount;
                    if (resCount - 1 >= 0) {
                        std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
                    }
                }
                obj.Value.size[0] = 1;
                obj.Value.size[1] = obj2Value_size_idx_1 + 31;
                for (int i1{0}; i1 < 30; i1++) {
                    obj.Value.data[i1] = cv2[i1];
                }
                if (obj2Value_size_idx_1 - 1 >= 0) {
                    std::copy(&obj2Value_data[0], &obj2Value_data[obj2Value_size_idx_1],
                              &obj.Value.data[30]);
                }
                obj.Value.data[obj2Value_size_idx_1 + 30] = ')';
                ocn_print(&obj);
                // 'bspline_eval:26' x = 0;
                q = 0.0;
            } else if (state->u > 1.0) {
                int obj2Value_size_idx_1;
                // 'bspline_eval:27' elseif ( x > 1 )
                // 'bspline_eval:28' ocn_print( enablePrint, ...
                // 'bspline_eval:29'                 "ERROR: C_BSPLINE_EVAL: X > 1 (" + x + ")",
                // mfilename );
                if (state->u == 0.0) {
                    obj2Value_size_idx_1 = 1;
                    obj2Value_data[0] = '0';
                } else {
                    int b_resCount;
                    b_resCount = sprintf(&st[0], "%.16g", state->u);
                    obj2Value_size_idx_1 = b_resCount;
                    if (b_resCount - 1 >= 0) {
                        std::copy(&st[0], &st[b_resCount], &obj2Value_data[0]);
                    }
                }
                obj.Value.size[0] = 1;
                obj.Value.size[1] = obj2Value_size_idx_1 + 31;
                for (int i2{0}; i2 < 30; i2++) {
                    obj.Value.data[i2] = cv3[i2];
                }
                if (obj2Value_size_idx_1 - 1 >= 0) {
                    std::copy(&obj2Value_data[0], &obj2Value_data[obj2Value_size_idx_1],
                              &obj.Value.data[30]);
                }
                obj.Value.data[obj2Value_size_idx_1 + 30] = ')';
                ocn_print(&obj);
                // 'bspline_eval:30' x = 1;
                q = 1.0;
            }
            // 'bspline_eval:32' my_path = StructTypeName.WDIR + "/src";
            // 'bspline_eval:33' coder.updateBuildInfo('addIncludePaths',my_path);
            // 'bspline_eval:34' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
            // 'bspline_eval:35' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
            // 'bspline_eval:36' coder.cinclude('c_spline.h');
            // 'bspline_eval:38' coder.ceval( 'c_bspline_eval', coder.rref(Bl.handle), ...
            // 'bspline_eval:39'             coder.rref(coeffs), x, coder.wref(X));
            c_bspline_eval(&Bl_handle, &coeffs[0], q, &X[0]);
            // 'bspline_eval:40' x       = X(1);
            // 'bspline_eval:41' xd      = X(2);
            // 'bspline_eval:42' xdd     = X(3);
            // 'bspline_eval:43' xddd    = X(4);
            // 'resampleCurv:136' if( q < 0 )
            if (X[0] < 0.0) {
                //  Non-positive function, it is better to go out
                // 'resampleCurv:138' u = uk;
                b_u = q_tmp;
                // 'resampleCurv:138' ud = 0;
                ud = 0.0;
                // 'resampleCurv:138' udd = 0;
                udd = 0.0;
                // 'resampleCurv:138' uddd = 0;
                uddd = 0.0;
                // 'resampleCurv:139' ocn_print( enablePrint, "Q should not be negative", mfilename
                // );
                b_ocn_print(enablePrint);
                // 'resampleCurv:141' if( coder.target( "MATLAB" ) )
            } else {
                double b_ud;
                double b_udd;
                double u_tmp;
                // 'resampleCurv:147' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
                //  calcQfromU : Compute q( u ) based on u and its derivatives.
                //
                //  Inputs :
                //  q     : [ N x M ] q( u )
                //  qd    : [ N x M ] First derivative of q
                //  qdd   : [ N x M ] Second derivative of q
                //
                //  Outputs :
                //  ud    : [ N x M ] First derivative of u
                //  udd   : [ N x M ] Second derivative of u
                //  uddd  : [ N x M ] Third derivative of u
                //
                // 'calcUfromQ:14' ud      = mysqrt( q );
                //  mysqrt : Custom implementation of the sqrt method.
                //
                //  Inputs :
                //    x : Value used for the computation
                //  Outputs :
                //    y : Resulting value
                //
                // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
                ocn_assert(X[0] >= 0.0);
                // 'mysqrt:11' y = sqrt(x);
                b_ud = std::sqrt(X[0]);
                // 'calcUfromQ:15' udd     = qd / 2;
                b_udd = X[1] / 2.0;
                // 'calcUfromQ:16' uddd    = qdd / 2 .* ud;
                uddd = X[2] / 2.0 * b_ud;
                ud = b_ud;
                udd = b_udd;
                //  Taylor odre 2
                // 'resampleCurv:150' u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;
                u_tmp = state->u + b_ud * state->dt;
                b_u = u_tmp + b_udd * (state->dt * state->dt) / 2.0;
                // + ( uddd * dt ^ 3 ) / 6;
                //  Ensure u > uk
                // 'resampleCurv:153' if( u  <= uk )
                if (b_u <= state->u) {
                    //  Taylor odre 1. Note since ud > 0
                    // 'resampleCurv:155' u = uk + ud * dt;
                    b_u = u_tmp;
                }
            }
            u = b_u;
        }
        // 'resampleCurv:51' state.dt = dt;
        state->dt = dt;
        // 'ResampleStateClass:7' double
        // 'ResampleStateClass:7' dt
        // 'resampleCurv:53' u = check_u_state_validity( u, state, enablePrint );
        // 'resampleCurv:204' if( isnan( u ) )
        // 'resampleCurv:213' if( ~isreal( u ) )
        // 'resampleCurv:222' if( u < 0 )
        if (u < 0.0) {
            // 'resampleCurv:223' ocn_print( enablePrint, ...
            // 'resampleCurv:224'         "U parameter should not be negative during resampling",
            // mfilename );
            c_ocn_print(enablePrint);
            // 'resampleCurv:225' if( coder.target( "MATLAB" ) )
        }
        // 'resampleCurv:230' if( ~( u > state.u ) )
        if (u <= state->u) {
            // 'resampleCurv:231' ocn_print( enablePrint, ...
            // 'resampleCurv:232'         "U parameter is too close from the previous one during
            // resampling", ... 'resampleCurv:233'         mfilename );
            d_ocn_print(enablePrint);
            // 'resampleCurv:235' if( coder.target( "MATLAB" ) )
        }
        //  ocn_assert( u > 0, "U parameter should not be negative during resampling", mfilename);
        // 'resampleCurv:241' u  = check_minimum_precision( state.u, u );
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:162' if( ~( d_up > d_low ) )
        if (u <= state->u) {
            double absx;
            double r;
            // 'resampleCurv:163' d_up = d_up + eps( d_up );
            absx = std::abs(u);
            if (absx <= 2.2250738585072014E-308) {
                r = 4.94065645841247E-324;
            } else {
                frexp(absx, &exponent);
                r = std::ldexp(1.0, exponent - 53);
            }
            u += r;
        }
        //  Check if u is outside the range
        // 'resampleCurv:56' if( u > 1 )
        guard1 = false;
        guard2 = false;
        if (u > 1.0) {
            // 'resampleCurv:57' state.isOutsideRange = true;
            state->isOutsideRange = true;
            // 'resampleCurv:58' if( curv_mode == ZSpdMode.NN )
            if (curv_mode == ZSpdMode_NN) {
                double TrVec[4];
                double d3;
                int b_loop_ub;
                int c_loop_ub;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int h_loop_ub;
                int i11;
                int i8;
                int i_loop_ub;
                // 'resampleCurv:59' TrVec   = zeros( 1, 4 );
                TrVec[0] = 0.0;
                //  Numerical integration : Gauss-Legendre
                // 'resampleCurv:61' GL_X   = GaussLegendreX;
                // 'resampleCurv:62' GL_W   = GaussLegendreW;
                //  Linear mapping from[-1, 1] to [state.u, 1]
                // 'resampleCurv:65' uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
                uval.set_size(GaussLegendreX.size(0));
                b_loop_ub = GaussLegendreX.size(0);
                for (int i3{0}; i3 < b_loop_ub; i3++) {
                    uval[i3] =
                        (state->u * (1.0 - GaussLegendreX[i3]) + (GaussLegendreX[i3] + 1.0)) / 2.0;
                }
                // 'resampleCurv:66' Ival  = 1 ./ mysqrt( bspline_eval_vec( Bl, coeff', uval ) );
                //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
                //
                //  Inputs    :
                //  Bl            : BSpline bases
                //  coeffs        : BSpline coefficients
                //  uVec          : U vector of points to evaluate
                //
                //  Outputs   :
                //  x             : Evaluation of the BSpline
                //  xd            : Evaluation of the first derivative of the BSpline
                //  xdd           : Evaluation of the second derivative of the BSpline
                //  xddd          : Evaluation of the third derivative of the BSpline
                //
                // 'bspline_eval_vec:15' x       = zeros(size(uVec));
                x.set_size(uval.size(0));
                c_loop_ub = uval.size(0);
                for (int i4{0}; i4 < c_loop_ub; i4++) {
                    x[i4] = 0.0;
                }
                // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
                xd.set_size(uval.size(0));
                d_loop_ub = uval.size(0);
                for (int i5{0}; i5 < d_loop_ub; i5++) {
                    xd[i5] = 0.0;
                }
                // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
                xdd.set_size(uval.size(0));
                e_loop_ub = uval.size(0);
                for (int i6{0}; i6 < e_loop_ub; i6++) {
                    xdd[i6] = 0.0;
                }
                // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
                xddd.set_size(uval.size(0));
                f_loop_ub = uval.size(0);
                for (int i7{0}; i7 < f_loop_ub; i7++) {
                    xddd[i7] = 0.0;
                }
                // 'bspline_eval_vec:20' for k = 1:length(uVec)
                i8 = uval.size(0);
                for (int k{0}; k < i8; k++) {
                    int g_loop_ub;
                    // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs,
                    // uVec( k ) );
                    x[k] = uval[k];
                    g_loop_ub = coeff.size(0);
                    b_coeff.set_size(1, coeff.size(0));
                    for (int i9{0}; i9 < g_loop_ub; i9++) {
                        b_coeff[i9] = coeff[i9];
                    }
                    bspline_eval(Bl_handle, b_coeff, &x[k], &b_d, &d1, &d2);
                    xddd[k] = d2;
                    xdd[k] = d1;
                    xd[k] = b_d;
                    // 'bspline_eval_vec:22' x(k)    = xk;
                    // 'bspline_eval_vec:23' xd(k)   = xdk;
                    // 'bspline_eval_vec:24' xdd(k)  = xddk;
                    // 'bspline_eval_vec:25' xddd(k) = xdddk;
                }
                //  mysqrt : Custom implementation of the sqrt method.
                //
                //  Inputs :
                //    x : Value used for the computation
                //  Outputs :
                //    y : Resulting value
                //
                // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
                b_x.set_size(x.size(0));
                h_loop_ub = x.size(0);
                for (int i10{0}; i10 < h_loop_ub; i10++) {
                    b_x[i10] = (x[i10] >= 0.0);
                }
                e_ocn_assert(b_x);
                // 'mysqrt:11' y = sqrt(x);
                //  Gauss Legendre integration
                // 'resampleCurv:68' Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
                i11 = x.size(0);
                for (int b_k{0}; b_k < i11; b_k++) {
                    x[b_k] = std::sqrt(x[b_k]);
                }
                d3 = 0.0;
                i_loop_ub = x.size(0);
                for (int i12{0}; i12 < i_loop_ub; i12++) {
                    d3 += 1.0 / x[i12] * GaussLegendreW[i12];
                }
                Tr = d3 * (1.0 - state->u) / 2.0;
                // 'resampleCurv:70' if( ~isreal( Tr ) || isnan( Tr ) )
                // 'resampleCurv:74' if( Tr >= dt )
                if (Tr >= dt) {
                    double Delta;
                    double a;
                    double b_state;
                    double d4;
                    double ex;
                    double yVec_idx_0;
                    double yVec_idx_1;
                    double yVec_idx_2;
                    int iindx;
                    // 'resampleCurv:75' a = udd/2;
                    a = udd / 2.0;
                    // 'resampleCurv:75' b = ud;
                    // 'resampleCurv:75' c = state.u -1;
                    // 'resampleCurv:77' Delta   = b^2 - 4 * a * c;
                    Delta = ud * ud - 4.0 * a * (state->u - 1.0);
                    // 'resampleCurv:79' if( Delta <= 0)
                    if (Delta <= 0.0) {
                        // 'resampleCurv:80' TrVec( 2 )  = -c / b;
                        TrVec[1] = -(state->u - 1.0) / ud;
                        // 'resampleCurv:81' TrVec( 3 )  = -b / a;
                        TrVec[2] = -ud / a;
                    } else if (ud > 0.0) {
                        double b_TrVec_tmp;
                        // 'resampleCurv:82' elseif( b > 0 )
                        // 'resampleCurv:83' TrVec( 2 )  = 2 *  c / ( -b - mysqrt(Delta) );
                        //  mysqrt : Custom implementation of the sqrt method.
                        //
                        //  Inputs :
                        //    x : Value used for the computation
                        //  Outputs :
                        //    y : Resulting value
                        //
                        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(Delta >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
                        b_TrVec_tmp = -ud - std::sqrt(Delta);
                        TrVec[1] = 2.0 * (state->u - 1.0) / b_TrVec_tmp;
                        // 'resampleCurv:84' TrVec( 3 )  = (-b - mysqrt(Delta) ) / ( 2 *  a );
                        //  mysqrt : Custom implementation of the sqrt method.
                        //
                        //  Inputs :
                        //    x : Value used for the computation
                        //  Outputs :
                        //    y : Resulting value
                        //
                        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(Delta >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
                        TrVec[2] = b_TrVec_tmp / (2.0 * a);
                    } else {
                        double TrVec_tmp;
                        // 'resampleCurv:85' else
                        // 'resampleCurv:86' TrVec( 2 )  = (-b + mysqrt(Delta) ) / ( 2 *  a );
                        //  mysqrt : Custom implementation of the sqrt method.
                        //
                        //  Inputs :
                        //    x : Value used for the computation
                        //  Outputs :
                        //    y : Resulting value
                        //
                        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(Delta >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
                        TrVec_tmp = -ud + std::sqrt(Delta);
                        TrVec[1] = TrVec_tmp / (2.0 * a);
                        // 'resampleCurv:87' TrVec( 3 )  = 2 *  c / ( -b + mysqrt(Delta) );
                        //  mysqrt : Custom implementation of the sqrt method.
                        //
                        //  Inputs :
                        //    x : Value used for the computation
                        //  Outputs :
                        //    y : Resulting value
                        //
                        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(Delta >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
                        TrVec[2] = 2.0 * (state->u - 1.0) / TrVec_tmp;
                    }
                    // 'resampleCurv:90' TrVec( 4 )  = -c / b;
                    TrVec[3] = -(state->u - 1.0) / ud;
                    //  Check validity
                    // 'resampleCurv:93' TrVec( isnan( TrVec ) )     = dt;
                    // 'resampleCurv:94' TrVec( ~isreal( TrVec ) )   = dt;
                    // 'resampleCurv:95' TrVec( ~( TrVec >= 0 ) )    = dt;
                    // 'resampleCurv:96' TrVec( ~( TrVec <= dt ) )   = dt;
                    // 'resampleCurv:98' yVec            = abs( a * TrVec.^2 + b * TrVec + c );
                    b_state = state->u - 1.0;
                    d4 = 0.0;
                    if (dt < 0.0) {
                        d4 = dt;
                        TrVec[0] = dt;
                    }
                    yVec_idx_0 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + b_state);
                    d4 = TrVec[1];
                    if (TrVec[1] < 0.0) {
                        d4 = dt;
                        TrVec[1] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[1] = dt;
                    }
                    yVec_idx_1 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + b_state);
                    d4 = TrVec[2];
                    if (TrVec[2] < 0.0) {
                        d4 = dt;
                        TrVec[2] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[2] = dt;
                    }
                    yVec_idx_2 = std::abs((a * std::pow(d4, 2.0) + ud * d4) + b_state);
                    d4 = TrVec[3];
                    if (TrVec[3] < 0.0) {
                        d4 = dt;
                        TrVec[3] = dt;
                    }
                    if (d4 > dt) {
                        d4 = dt;
                        TrVec[3] = dt;
                    }
                    // 'resampleCurv:99' [ ~, ind ]      = min( yVec );
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
                    if (ex > std::abs((a * std::pow(d4, 2.0) + ud * d4) + b_state)) {
                        iindx = 2;
                    }
                    // 'resampleCurv:100' Tr              = TrVec( ind );
                    Tr = TrVec[iindx + 1];
                }
                guard2 = true;
            } else if (curv_mode == ZSpdMode_ZN) {
                // 'resampleCurv:103' elseif( curv_mode == ZSpdMode.ZN )
                // 'resampleCurv:104' [ time ] = constJerkTime(constJerk, [state.u, 1], false);
                //  constJerkTime : Compute the time vector for a given u vector based on a
                //                  constant jerk velocity profile.
                //
                //  Inputs :
                //    pseudoJerk  : Constant jerk value
                //    u_vec       : U vector
                //    isEnd       : Is the end of a curv
                //
                //  Outputs :
                //    k_vec       : Time vector
                //
                // 'constJerkTime:13' if( coder.target( "MATLAB" ) )
                // 'constJerkTime:19' if( isEnd )
                // 'constJerkTime:23' k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );
                // 'constJerkTime:25' if( isEnd )
                // 'resampleCurv:105' Tr = time(2) - time(1);
                Tr = std::pow(6.0 / constJerk, 0.33333333333333331) -
                     std::pow(state->u * 6.0 / constJerk, 0.33333333333333331);
                guard2 = true;
            } else {
                // 'resampleCurv:106' else
                // 'resampleCurv:107' state = state.startZeroStopTime();
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
            // 'resampleCurv:117' else
            // 'resampleCurv:118' state.isOutsideRange = false;
            state->isOutsideRange = false;
            // 'resampleCurv:119' state = state.setU( u, ud, udd, uddd );
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
            double d;
            //  Ensure Tr <= dt and Tr >= 0 and real
            // 'resampleCurv:111' state.dt = check_minimum_precision_dt( dt - Tr, dt, enablePrint );
            d = dt - Tr;
            //  check_minimum_precision : Avoid effect numerical problem
            // 'resampleCurv:170' if( isnan( d ) )
            // 'resampleCurv:178' if( ~isreal( d ) )
            // 'resampleCurv:186' if( d <= 0.0 )
            if (d <= 0.0) {
                // 'resampleCurv:187' d = 0.0;
                d = 0.0;
                // 'resampleCurv:188' ocn_print( enablePrint, "Tr should be positive", mfilename );
                e_ocn_print(enablePrint);
                // 'resampleCurv:189' if( coder.target( "MATLAB" ) )
            }
            //  if( d > dt )
            //      d = dt;
            //      disp("Tr should not be larger than Ts", mfilename);
            //      if( coder.target( "MATLAB" ) )
            //          DebugResampling.getInstance().increaseTTooLargeCounter();
            //      end
            //  end
            state->dt = d;
            // 'ResampleStateClass:7' double
            // 'ResampleStateClass:7' dt
            // 'resampleCurv:113' if( coder.target( "MATLAB" ) )
            guard1 = true;
        }
        if (guard1) {
            //  Need to use the next curve structure
            // 'resampleCurv:123' if( u >= 1 )
            if (u >= 1.0) {
                // 'resampleCurv:124' state.go_next = true;
                state->go_next = true;
            } else {
                // 'resampleCurv:125' else
                // 'resampleCurv:126' state.go_next = false;
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
