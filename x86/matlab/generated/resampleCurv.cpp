//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "resampleCurv.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "constJerkU.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [ state, ud, udd, uddd ] = resampleCurv(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, ...
//     curv_a, curv_b)
//
// resampleCurvDebug :
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
//                const SplineBase *Bl
//                ZSpdMode curv_mode
//                const ::coder::array<double, 1U> &coeff
//                double constJerk
//                double dt
//                double curv_a
//                double curv_b
//                double *ud
//                double *udd
//                double *uddd
// Return Type  : void
//
namespace ocn {
void resampleCurv(ResampleStateClass *state, const SplineBase *Bl, ZSpdMode curv_mode,
                  const ::coder::array<double, 1U> &coeff, double constJerk, double dt,
                  double curv_a, double curv_b, double *ud, double *udd, double *uddd)
{
    ::coder::array<double, 2U> b_coeff;
    double b_q[2];
    double b_u[2];
    double du;
    double du_min;
    double q;
    double qd;
    double qdd;
    double u;
    double xdddk;
    double xddk;
    double xdk;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'resampleCurv:29' coder.inline( "never" );
    // 'resampleCurv:31' if coder.target( "MATLAB" )
    // 'resampleCurv:35' else
    // 'resampleCurv:37' if      ( curv_mode == ZSpdMode.ZN )
    if (curv_mode == ZSpdMode_ZN) {
        // 'resampleCurv:38' [ u, ud, udd, uddd ] = constJerkU( constJerk, dt, false, ...
        // 'resampleCurv:39'             curv_a, curv_b );
        constJerkU(constJerk, dt, false, curv_a, curv_b, &u, ud, udd, uddd);
    } else if (curv_mode == ZSpdMode_NZ) {
        // 'resampleCurv:40' elseif  ( curv_mode == ZSpdMode.NZ )
        // 'resampleCurv:41' T = dt - min( state.dt, dt );
        // 'resampleCurv:42' [ u, ud, udd, uddd ] = constJerkU( constJerk, T, true, ...
        // 'resampleCurv:43'             curv_a, curv_b );
        constJerkU(constJerk, dt - std::fmin(state->dt, dt), true, curv_a, curv_b, &u, ud, udd,
                   uddd);
    } else {
        int loop_ub;
        // 'resampleCurv:44' else
        // 'resampleCurv:45' [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
        // 'resampleCurv:71' [ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );
        q = state->u;
        b_coeff.set_size(1, coeff.size(0));
        loop_ub = coeff.size(0);
        for (int i{0}; i < loop_ub; i++) {
            b_coeff[i] = coeff[i];
        }
        double ud_tmp;
        bspline_eval(Bl->handle, b_coeff, &q, &qd, &qdd);
        // 'resampleCurv:73' [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
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
        ud_tmp = std::sqrt(q);
        // 'calcUfromQ:12' udd     = qd / 2;
        *udd = qd / 2.0;
        // 'calcUfromQ:13' uddd    = qdd / 2 .* ud;
        *uddd = qdd / 2.0 * ud_tmp;
        *ud = ud_tmp;
        // 'resampleCurv:75' u = uk + mysqrt( q ) * dt + (qd * dt ^ 2 ) / 4;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        u = (state->u + ud_tmp * state->dt) + qd * (state->dt * state->dt) / 4.0;
    }
    // 'resampleCurv:48' du      = u - state.u;
    du = u - state->u;
    // 'resampleCurv:49' du_min  = check_minimum_precision( du );
    du_min = du;
    //  check_minimum_precision : Avoid effect numerical problem
    // 'resampleCurv:80' MIN_PRES = eps;
    // 'resampleCurv:81' if(d < MIN_PRES)
    if (du < 2.2204460492503131E-16) {
        // 'resampleCurv:81' d = MIN_PRES;
        du_min = 2.2204460492503131E-16;
    }
    // 'resampleCurv:50' if( du_min > du )
    if (du_min > du) {
        // 'resampleCurv:50' u = state.u + du_min;
        u = state->u + du_min;
    }
    // 'resampleCurv:52' if( u > 1 )
    if (u > 1.0) {
        double d;
        int b_loop_ub;
        // 'resampleCurv:53' [ q ]    = bspline_eval_vec( Bl, coeff', [ state.u, 1 ] );
        b_u[0] = state->u;
        b_u[1] = 1.0;
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        b_loop_ub = coeff.size(0);
        for (int k{0}; k < 2; k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            b_q[k] = b_u[k];
            b_coeff.set_size(1, coeff.size(0));
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                b_coeff[i1] = coeff[i1];
            }
            bspline_eval(Bl->handle, b_coeff, &b_q[k], &xdk, &xddk, &xdddk);
            // 'bspline_eval_vec:10' x(k) = xk;
            // 'bspline_eval_vec:11' xd(k) = xdk;
            // 'bspline_eval_vec:12' xdd(k) = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        // 'resampleCurv:54' Tr       = 2 * ( 1 - state.u ) / ( sqrt( q( end ) ) + sqrt( q( 1 ) ) );
        // 'resampleCurv:55' state.dt = check_minimum_precision( state.dt - Tr );
        d = state->dt - 2.0 * (1.0 - state->u) / (std::sqrt(b_q[1]) + std::sqrt(b_q[0]));
        //  check_minimum_precision : Avoid effect numerical problem
        // 'resampleCurv:80' MIN_PRES = eps;
        // 'resampleCurv:81' if(d < MIN_PRES)
        if (d < 2.2204460492503131E-16) {
            // 'resampleCurv:81' d = MIN_PRES;
            d = 2.2204460492503131E-16;
        }
        state->dt = d;
        // 'ResampleStateClass:5' double
        // 'ResampleStateClass:5' dt
        // 'resampleCurv:56' state.isOutsideRange = true;
        state->isOutsideRange = true;
    }
    // 'resampleCurv:59' state.u = u;
    state->u = u;
    // 'ResampleStateClass:3' double
    // 'ResampleStateClass:3' u
    // 'resampleCurv:61' if( state.u >= 1 )
    if (u >= 1.0) {
        // 'resampleCurv:62' state.go_next = true;
        state->go_next = true;
    } else {
        // 'resampleCurv:63' else
        // 'resampleCurv:64' state.go_next = false;
        state->go_next = false;
    }
}

} // namespace ocn

//
// File trailer for resampleCurv.cpp
//
// [EOF]
//
