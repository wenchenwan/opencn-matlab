//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
//

// Include Files
#include "FeedratePlanning_LP.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "buildConstr.h"
#include "buildConstrJerk.h"
#include "c_simplex.h"
#include "calcZeroConstraints.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void add_slack(const ::coder::array<double, 2U> &f, const ::coder::array<double, 2U> &A,
                      const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                      const ::coder::array<double, 2U> &indSlack, double LP_SLACK_PENALTY,
                      ::coder::array<double, 1U> &fSlack, ::coder::array<double, 2U> &ASlack,
                      ::coder::array<double, 1U> &bSlack, ::coder::array<double, 2U> &AeqSlack);

static void b_relax_intial_constraints(const ::coder::array<double, 1U> &f,
                                       const ::coder::array<double, 2U> &A,
                                       const ::coder::array<double, 1U> &b,
                                       const ::coder::array<double, 2U> &Aeq,
                                       ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx,
                                       int indCurv, ::coder::array<double, 2U> &Coeff0,
                                       bool *success, int *status);

static void
relax_intial_constraints(const ::coder::array<double, 1U> &f, const ::coder::array<double, 2U> &A,
                         const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                         ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx, int indCurv,
                         ::coder::array<double, 2U> &Coeff0, bool *success, int *status);

} // namespace ocn

// Function Definitions
//
// function [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
//     A, b, Aeq, beq, indSlack, LP )
//
// Arguments    : const ::coder::array<double, 2U> &f
//                const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &Aeq
//                const ::coder::array<double, 2U> &indSlack
//                double LP_SLACK_PENALTY
//                ::coder::array<double, 1U> &fSlack
//                ::coder::array<double, 2U> &ASlack
//                ::coder::array<double, 1U> &bSlack
//                ::coder::array<double, 2U> &AeqSlack
// Return Type  : void
//
namespace ocn {
static void add_slack(const ::coder::array<double, 2U> &f, const ::coder::array<double, 2U> &A,
                      const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                      const ::coder::array<double, 2U> &indSlack, double LP_SLACK_PENALTY,
                      ::coder::array<double, 1U> &fSlack, ::coder::array<double, 2U> &ASlack,
                      ::coder::array<double, 1U> &bSlack, ::coder::array<double, 2U> &AeqSlack)
{
    ::coder::array<double, 2U> b_result;
    ::coder::array<int, 2U> r;
    ::coder::array<signed char, 2U> varargin_3;
    ::coder::array<signed char, 1U> vecSlack;
    int b_f;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int c_input_sizes_idx_1;
    int c_loop_ub;
    int c_result;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i9;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int loop_ub;
    int result;
    int sizes_idx_1;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'FeedratePlanning_LP:124' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:126' if(0)
    // 'FeedratePlanning_LP:131' else
    // 'FeedratePlanning_LP:132' Apos = [];
    // 'FeedratePlanning_LP:133' bpos = [];
    //  Slack variables
    // 'FeedratePlanning_LP:137' vecSlack    = zeros( nAL, 1 );
    vecSlack.set_size(A.size(0));
    loop_ub = A.size(0);
    for (int i{0}; i < loop_ub; i++) {
        vecSlack[i] = 0;
    }
    // 'FeedratePlanning_LP:137' vecSlack( indSlack ) = -1;
    r.set_size(1, indSlack.size(1));
    b_loop_ub = indSlack.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r[i1] = static_cast<int>(indSlack[i1]);
    }
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        vecSlack[r[i2] - 1] = -1;
    }
    // 'FeedratePlanning_LP:138' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i3{0}; i3 < b_f; i3++) {
        fSlack[i3] = f[i3];
    }
    fSlack[b_f] = LP_SLACK_PENALTY;
    // 'FeedratePlanning_LP:139' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
    if ((A.size(0) != 0) && (A.size(1) != 0)) {
        result = A.size(0);
    } else if (vecSlack.size(0) != 0) {
        result = vecSlack.size(0);
    } else {
        result = A.size(0);
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
        input_sizes_idx_1 = A.size(1);
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (vecSlack.size(0) != 0)) {
        b_input_sizes_idx_1 = 1;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    b_result.set_size(result, input_sizes_idx_1 + b_input_sizes_idx_1);
    for (int i4{0}; i4 < input_sizes_idx_1; i4++) {
        for (int i5{0}; i5 < result; i5++) {
            b_result[i5 + b_result.size(0) * i4] = A[i5 + result * i4];
        }
    }
    d_loop_ub = b_input_sizes_idx_1;
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        for (int i7{0}; i7 < result; i7++) {
            b_result[i7 + b_result.size(0) * input_sizes_idx_1] = vecSlack[i7];
        }
    }
    varargin_3.set_size(1, A.size(1) + 1);
    e_loop_ub = A.size(1);
    for (int i8{0}; i8 < e_loop_ub; i8++) {
        varargin_3[i8] = 0;
    }
    varargin_3[A.size(1)] = -1;
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = varargin_3.size(1);
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        input_sizes_idx_0 = b_result.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        i9 = b_result.size(0);
    } else {
        i9 = 0;
    }
    ASlack.set_size(i9 + 1, sizes_idx_1);
    for (int i10{0}; i10 < sizes_idx_1; i10++) {
        for (int i12{0}; i12 < input_sizes_idx_0; i12++) {
            ASlack[i12 + ASlack.size(0) * i10] = b_result[i12 + input_sizes_idx_0 * i10];
        }
    }
    for (int i11{0}; i11 < sizes_idx_1; i11++) {
        ASlack[input_sizes_idx_0 + ASlack.size(0) * i11] = varargin_3[i11];
    }
    // 'FeedratePlanning_LP:140' bSlack      = [ bpos; b ; 0 ];
    if (b.size(0) != 0) {
        b_input_sizes_idx_0 = b.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    bSlack.set_size(b_input_sizes_idx_0 + 1);
    for (int i13{0}; i13 < b_input_sizes_idx_0; i13++) {
        bSlack[i13] = b[i13];
    }
    bSlack[b_input_sizes_idx_0] = 0.0;
    // 'FeedratePlanning_LP:141' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
    if ((Aeq.size(0) != 0) && (Aeq.size(1) != 0)) {
        c_result = Aeq.size(0);
    } else if (Aeq.size(0) != 0) {
        c_result = Aeq.size(0);
    } else {
        c_result = 0;
    }
    b_empty_non_axis_sizes = (c_result == 0);
    if (b_empty_non_axis_sizes || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
        c_input_sizes_idx_1 = Aeq.size(1);
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (b_empty_non_axis_sizes || (Aeq.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    AeqSlack.set_size(c_result, c_input_sizes_idx_1 + d_input_sizes_idx_1);
    for (int i14{0}; i14 < c_input_sizes_idx_1; i14++) {
        for (int i15{0}; i15 < c_result; i15++) {
            AeqSlack[i15 + AeqSlack.size(0) * i14] = Aeq[i15 + c_result * i14];
        }
    }
    f_loop_ub = d_input_sizes_idx_1;
    for (int i16{0}; i16 < f_loop_ub; i16++) {
        for (int i17{0}; i17 < c_result; i17++) {
            AeqSlack[i17 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:142' beqSlack    = beq;
}

//
// function [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
//     f, A, b, Aeq, beq, ctx, indCurv, isEnd, maxIter)
//
// Arguments    : const ::coder::array<double, 1U> &f
//                const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &Aeq
//                ::coder::array<double, 1U> &beq
//                b_FeedoptContext *ctx
//                int indCurv
//                ::coder::array<double, 2U> &Coeff0
//                bool *success
//                int *status
// Return Type  : void
//
static void b_relax_intial_constraints(const ::coder::array<double, 1U> &f,
                                       const ::coder::array<double, 2U> &A,
                                       const ::coder::array<double, 1U> &b,
                                       const ::coder::array<double, 2U> &Aeq,
                                       ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx,
                                       int indCurv, ::coder::array<double, 2U> &Coeff0,
                                       bool *success, int *status)
{
    coder::sparse r1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    CurvStruct curv;
    double atNorm;
    double vNorm;
    int b_status;
    int count;
    int loop_ub;
    bool b_success;
    // 'FeedratePlanning_LP:153' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:154' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:155' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:156' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:157' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:158' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:159' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:160' msg         = "";
    // 'FeedratePlanning_LP:162' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        double b_atNorm;
        double b_unnamed_idx_0;
        double b_vNorm;
        double k_vec;
        double n;
        double u;
        double ud;
        double udd;
        double unnamed_idx_0;
        double y;
        int b_loop_ub;
        int c_loop_ub;
        int i3;
        // 'FeedratePlanning_LP:163' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:147' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:148' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        //  calcZeroConstraints : Compute the velocity and acceleration
        //  required for the continuity at zero start.
        //  Inputs :
        //  ctx   : The context
        //  Curv  : The curve
        //  isEnd : (boolean) Is the end of the curve
        //  Outputs :
        //  v_0   : Norm of the velocity
        //  at_0  : Norm of the tangential acceleration
        // 'calcZeroConstraints:12' jps = curv.ConstJerk;
        // 'calcZeroConstraints:14' if( isEnd )
        // 'calcZeroConstraints:15' k  = 0;
        // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd );
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
        k_vec = std::pow(6.0 / curv.ConstJerk, 0.33333333333333331);
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        ud = curv.ConstJerk * (k_vec * k_vec) / 2.0;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u = curv.ConstJerk * std::pow(k_vec, 3.0) / 6.0;
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
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        udd = -(curv.ConstJerk * k_vec);
        // 'constJerkU:40' uddd = uddd;
        // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
        j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                         ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv,
                         1.0 - b_unnamed_idx_0, r0D, r1D, r2D, r3D);
        // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd,
        // uddd, r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
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
        y = ud * ud;
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]       = calcNormVNormAT( V, A,
        // r1D );
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
        b_loop_ub = r1D.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            double varargin_1;
            varargin_1 = r1D[i1] * ud;
            r[i1] = std::pow(varargin_1, 2.0);
        }
        b_vNorm = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        c_loop_ub = r1D.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            double b_varargin_1;
            b_varargin_1 = r1D[i2];
            r[i2] = std::pow(b_varargin_1, 2.0);
        }
        n = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:14' atNorm  = MyNorm( A.*t );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        if (r2D.size(0) == 1) {
            i3 = r1D.size(0);
        } else {
            i3 = r2D.size(0);
        }
        if ((r2D.size(0) == r1D.size(0)) && (i3 == r1D.size(0))) {
            int d_loop_ub;
            r.set_size(r2D.size(0));
            d_loop_ub = r2D.size(0);
            for (int i4{0}; i4 < d_loop_ub; i4++) {
                double c_varargin_1;
                c_varargin_1 = (r2D[i4] * y + r1D[i4] * udd) * (r1D[i4] / n);
                r[i4] = std::pow(c_varargin_1, 2.0);
            }
        } else {
            binary_expand_op(r, r2D, y, r1D, udd, n);
        }
        b_atNorm = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:165' if(isEnd)
        // 'FeedratePlanning_LP:166' beq( end-1 )    = -vNorm^2;
        beq[beq.size(0) - 2] = -(b_vNorm * b_vNorm);
        // 'FeedratePlanning_LP:167' beq( end )      = atNorm;
        beq[beq.size(0) - 1] = b_atNorm;
        // 'FeedratePlanning_LP:173' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:174'             Aeq, beq, ctx );
        coder::b_sparse(A, &r1);
        c_simplex(f, &r1, b, Aeq, beq, Coeff0, &b_success, &b_status);
        // 'FeedratePlanning_LP:175' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:180' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:181' if(isEnd)
    // 'FeedratePlanning_LP:182' ctx.at_1    = -atNorm;
    ctx->at_1 = -atNorm;
    // 'FeedratePlanning_LP:183' ctx.v_1     = -vNorm;
    ctx->v_1 = -vNorm;
    *success = b_success;
    *status = b_status;
}

//
// function [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
//     f, A, b, Aeq, beq, ctx, indCurv, isEnd, maxIter)
//
// Arguments    : const ::coder::array<double, 1U> &f
//                const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &Aeq
//                ::coder::array<double, 1U> &beq
//                b_FeedoptContext *ctx
//                int indCurv
//                ::coder::array<double, 2U> &Coeff0
//                bool *success
//                int *status
// Return Type  : void
//
static void
relax_intial_constraints(const ::coder::array<double, 1U> &f, const ::coder::array<double, 2U> &A,
                         const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                         ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx, int indCurv,
                         ::coder::array<double, 2U> &Coeff0, bool *success, int *status)
{
    coder::sparse r;
    CurvStruct curv;
    double atNorm;
    double b_atNorm;
    double b_vNorm;
    double vNorm;
    int b_status;
    int count;
    int loop_ub;
    bool b_success;
    // 'FeedratePlanning_LP:153' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:154' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:155' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:156' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:157' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:158' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:159' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:160' msg         = "";
    // 'FeedratePlanning_LP:162' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        // 'FeedratePlanning_LP:163' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:147' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:148' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, &b_vNorm,
                            &b_atNorm);
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:165' if(isEnd)
        // 'FeedratePlanning_LP:168' else
        // 'FeedratePlanning_LP:169' beq( 1 )        = vNorm^2;
        beq[0] = b_vNorm * b_vNorm;
        // 'FeedratePlanning_LP:170' beq( 2 )        = atNorm;
        beq[1] = b_atNorm;
        // 'FeedratePlanning_LP:173' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:174'             Aeq, beq, ctx );
        coder::b_sparse(A, &r);
        c_simplex(f, &r, b, Aeq, beq, Coeff0, &b_success, &b_status);
        // 'FeedratePlanning_LP:175' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:180' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:181' if(isEnd)
    // 'FeedratePlanning_LP:184' else
    // 'FeedratePlanning_LP:185' ctx.at_0    = atNorm;
    ctx->at_0 = atNorm;
    // 'FeedratePlanning_LP:186' ctx.v_0     = vNorm;
    ctx->v_0 = vNorm;
    *success = b_success;
    *status = b_status;
}

//
// function [ctx, Coeff, success, status, msg] = ...
//     FeedratePlanning_LP( ctx, window, amax, jmax, BasisVal, ...
//     BasisValD, BasisValDD, BasisIntegr, u_vec, NWindow )
//
// 0) Initialization of the problem
//
// Arguments    : b_FeedoptContext *ctx
//                const ::coder::array<CurvStruct, 2U> &window
//                const double amax[6]
//                const double jmax[6]
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 1U> &BasisIntegr
//                const ::coder::array<double, 2U> &u_vec
//                double NWindow
//                ::coder::array<double, 2U> &Coeff
//                bool *success
//                int *status
// Return Type  : void
//
void FeedratePlanning_LP(b_FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &window,
                         const double amax[6], const double jmax[6],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr,
                         const ::coder::array<double, 2U> &u_vec, double NWindow,
                         ::coder::array<double, 2U> &Coeff, bool *success, int *status)
{
    Kinematics b_ctx;
    Kinematics c_ctx;
    coder::sparse r;
    coder::sparse r1;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> ASlack;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> AeqSlack;
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_A;
    ::coder::array<double, 2U> b_Coeff;
    ::coder::array<double, 2U> b_Coeff0;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 1U> bSlack;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_beqSlack;
    ::coder::array<double, 1U> beqSlack;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> c_beqSlack;
    ::coder::array<double, 1U> d_beqSlack;
    ::coder::array<double, 1U> e_beqSlack;
    ::coder::array<double, 1U> fSlack;
    ::coder::array<double, 1U> f_beqSlack;
    ::coder::array<unsigned int, 2U> y;
    ::coder::array<signed char, 2U> varargin_3;
    int BasisVal_idx_0;
    int b_f;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_status;
    int c_input_sizes_idx_1;
    int c_result;
    int c_status;
    int d_loop_ub;
    int d_status;
    int e_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int i10;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int loop_ub;
    int loop_ub_tmp;
    int result;
    int sizes_idx_1;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool b_success;
    bool c_success;
    bool d_success;
    bool e_success;
    bool empty_non_axis_sizes;
    bool f_success;
    bool g_success;
    //  M     : number of discretization
    //  N     : number of coefficients
    // 'FeedratePlanning_LP:9' [ M, N ]    = size( BasisVal );
    // 'FeedratePlanning_LP:10' LP          = ctx.cfg.opt;
    //  Load parameters of the LP
    // 'FeedratePlanning_LP:11' CurvArray   = window( 1 : NWindow );
    if (NWindow < 1.0) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(NWindow);
    }
    //  Extract window of interest
    //  1) Optimization : first LP
    //  A. Linear objectif
    // 'FeedratePlanning_LP:16' f = -repmat( BasisIntegr, 1, NWindow );
    loop_ub_tmp = static_cast<int>(NWindow);
    b.set_size(BasisIntegr.size(0), loop_ub_tmp);
    if ((BasisIntegr.size(0) != 0) && (static_cast<int>(NWindow) != 0)) {
        int i;
        i = static_cast<int>(NWindow) - 1;
        for (int t{0}; t <= i; t++) {
            int na;
            na = BasisIntegr.size(0);
            for (int k{0}; k < na; k++) {
                b[k + b.size(0) * t] = BasisIntegr[k];
            }
        }
    }
    f.set_size(b.size(0), b.size(1));
    b_loop_ub = b.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int c_loop_ub;
        c_loop_ub = b.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            f[i2 + f.size(0) * i1] = -b[i2 + b.size(0) * i1];
        }
    }
    //  B. Constraints : Inequality and Equality
    //  Feedrate and acceleration
    // 'FeedratePlanning_LP:20' [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax,
    // ctx.v_0, ... 'FeedratePlanning_LP:21'     ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD,
    // u_vec);
    b_window.set_size(1, loop_ub);
    for (int i3{0}; i3 < loop_ub; i3++) {
        b_window[i3] = window[i3];
    }
    b_ctx = ctx->kin;
    buildConstr(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS,
                ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS, &b_ctx, b_window, amax, ctx->v_0, ctx->at_0,
                ctx->v_1, ctx->at_1, BasisVal, BasisValD, u_vec, A, b_b, Aeq, beqSlack, continuity);
    // 'FeedratePlanning_LP:23' indSlack =  [];
    // 1 : numel( b );
    // 'FeedratePlanning_LP:25' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    // 'FeedratePlanning_LP:26'     A, b, Aeq, beq, indSlack, LP );
    // 'FeedratePlanning_LP:124' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:126' if(0)
    // 'FeedratePlanning_LP:131' else
    // 'FeedratePlanning_LP:132' Apos = [];
    // 'FeedratePlanning_LP:133' bpos = [];
    //  Slack variables
    // 'FeedratePlanning_LP:137' vecSlack    = zeros( nAL, 1 );
    // 'FeedratePlanning_LP:137' vecSlack( indSlack ) = -1;
    // 'FeedratePlanning_LP:138' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i4{0}; i4 < b_f; i4++) {
        fSlack[i4] = f[i4];
    }
    fSlack[b_f] = ctx->cfg.opt.SLACK_PENALTY;
    // 'FeedratePlanning_LP:139' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
    if ((A.size(0) != 0) && (A.size(1) != 0)) {
        result = A.size(0);
    } else if (A.size(0) != 0) {
        result = A.size(0);
    } else {
        result = 0;
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
        input_sizes_idx_1 = A.size(1);
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (A.size(0) != 0)) {
        b_input_sizes_idx_1 = 1;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    b_result.set_size(result, input_sizes_idx_1 + b_input_sizes_idx_1);
    for (int i5{0}; i5 < input_sizes_idx_1; i5++) {
        for (int i6{0}; i6 < result; i6++) {
            b_result[i6 + b_result.size(0) * i5] = A[i6 + result * i5];
        }
    }
    d_loop_ub = b_input_sizes_idx_1;
    for (int i7{0}; i7 < d_loop_ub; i7++) {
        for (int i8{0}; i8 < result; i8++) {
            b_result[i8 + b_result.size(0) * input_sizes_idx_1] = 0.0;
        }
    }
    varargin_3.set_size(1, A.size(1) + 1);
    e_loop_ub = A.size(1);
    for (int i9{0}; i9 < e_loop_ub; i9++) {
        varargin_3[i9] = 0;
    }
    varargin_3[A.size(1)] = -1;
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = varargin_3.size(1);
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        input_sizes_idx_0 = b_result.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        i10 = b_result.size(0);
    } else {
        i10 = 0;
    }
    ASlack.set_size(i10 + 1, sizes_idx_1);
    for (int i11{0}; i11 < sizes_idx_1; i11++) {
        for (int i13{0}; i13 < input_sizes_idx_0; i13++) {
            ASlack[i13 + ASlack.size(0) * i11] = b_result[i13 + input_sizes_idx_0 * i11];
        }
    }
    for (int i12{0}; i12 < sizes_idx_1; i12++) {
        ASlack[input_sizes_idx_0 + ASlack.size(0) * i12] = varargin_3[i12];
    }
    // 'FeedratePlanning_LP:140' bSlack      = [ bpos; b ; 0 ];
    if (b_b.size(0) != 0) {
        b_input_sizes_idx_0 = b_b.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    bSlack.set_size(b_input_sizes_idx_0 + 1);
    for (int i14{0}; i14 < b_input_sizes_idx_0; i14++) {
        bSlack[i14] = b_b[i14];
    }
    bSlack[b_input_sizes_idx_0] = 0.0;
    // 'FeedratePlanning_LP:141' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
    if ((Aeq.size(0) != 0) && (Aeq.size(1) != 0)) {
        c_result = Aeq.size(0);
    } else if (Aeq.size(0) != 0) {
        c_result = Aeq.size(0);
    } else {
        c_result = 0;
    }
    b_empty_non_axis_sizes = (c_result == 0);
    if (b_empty_non_axis_sizes || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
        c_input_sizes_idx_1 = Aeq.size(1);
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (b_empty_non_axis_sizes || (Aeq.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    AeqSlack.set_size(c_result, c_input_sizes_idx_1 + d_input_sizes_idx_1);
    for (int i15{0}; i15 < c_input_sizes_idx_1; i15++) {
        for (int i16{0}; i16 < c_result; i16++) {
            AeqSlack[i16 + AeqSlack.size(0) * i15] = Aeq[i16 + c_result * i15];
        }
    }
    f_loop_ub = d_input_sizes_idx_1;
    for (int i17{0}; i17 < f_loop_ub; i17++) {
        for (int i18{0}; i18 < c_result; i18++) {
            AeqSlack[i18 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:142' beqSlack    = beq;
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:29' [ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack,
    // ASlack, bSlack, ... 'FeedratePlanning_LP:30'     AeqSlack, beqSlack, ctx, ...
    // 'FeedratePlanning_LP:31'     N, NWindow, "First LP" );
    //  Call the solver
    // -------------------------------------------------------------------------
    //  Functions
    // -------------------------------------------------------------------------
    // 'FeedratePlanning_LP:71' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, ... 'FeedratePlanning_LP:72'     beq, ctx );
    coder::b_sparse(ASlack, &r);
    c_simplex(fSlack, &r, bSlack, AeqSlack, beqSlack, Coeff0, &b_success, &b_status);
    c_success = b_success;
    //  If optimization failed due with zero end constaints, decrease pseudo jerk
    // 'FeedratePlanning_LP:74' if( ~success && ( ctx.zero_end || ctx.zero_start ) )
    if ((!b_success) && (ctx->zero_end || ctx->zero_start)) {
        double Ntot;
        int indEnd;
        // 'FeedratePlanning_LP:75' Ntot        = NWindow;
        Ntot = NWindow;
        // 'FeedratePlanning_LP:76' maxIter     = 15;
        // 'FeedratePlanning_LP:77' indStart    = ctx.k0;
        // 'FeedratePlanning_LP:78' indEnd      = ctx.k0;
        indEnd = ctx->k0;
        // 'FeedratePlanning_LP:80' if(ctx.zero_start)
        if (ctx->zero_start) {
            // 'FeedratePlanning_LP:81' Ntot        = Ntot + 1;
            Ntot = NWindow + 1.0;
        }
        // 'FeedratePlanning_LP:84' if(ctx.zero_end)
        if (ctx->zero_end) {
            // 'FeedratePlanning_LP:85' Ntot        = Ntot + 1;
            Ntot++;
            // 'FeedratePlanning_LP:86' indEnd      = ctx.k0 + Ntot -1;
            indEnd = static_cast<int>(std::round(static_cast<double>(ctx->k0) + Ntot)) - 1;
        }
        // 'FeedratePlanning_LP:89' if( ctx.zero_start && ctx.zero_end )
        if (ctx->zero_start && ctx->zero_end) {
            int l_loop_ub;
            int m_loop_ub;
            // 'FeedratePlanning_LP:90' beq( end-1 )    = -ctx.cfg.v_1^2;
            beqSlack[beqSlack.size(0) - 2] = -(ctx->cfg.v_1 * ctx->cfg.v_1);
            // 'FeedratePlanning_LP:91' beq( end )      = -ctx.cfg.at_1;
            beqSlack[beqSlack.size(0) - 1] = -ctx->cfg.at_1;
            // 'FeedratePlanning_LP:92' [ctx,Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:93'                         f, A,
            // b, Aeq, beq, ctx, indStart, false, maxIter);
            d_beqSlack.set_size(beqSlack.size(0));
            l_loop_ub = beqSlack.size(0) - 1;
            for (int i27{0}; i27 <= l_loop_ub; i27++) {
                d_beqSlack[i27] = beqSlack[i27];
            }
            relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, d_beqSlack, ctx, ctx->k0,
                                     Coeff0, &d_success, &c_status);
            // 'FeedratePlanning_LP:94' beq( 1 )        = ctx.v_0^2;
            beqSlack[0] = ctx->v_0 * ctx->v_0;
            // 'FeedratePlanning_LP:95' beq( 2 )        = ctx.at_0;
            beqSlack[1] = ctx->at_0;
            // 'FeedratePlanning_LP:96' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:97'                         f, A,
            // b, Aeq, beq, ctx, indEnd, true, maxIter);
            e_beqSlack.set_size(beqSlack.size(0));
            m_loop_ub = beqSlack.size(0) - 1;
            for (int i28{0}; i28 <= m_loop_ub; i28++) {
                e_beqSlack[i28] = beqSlack[i28];
            }
            b_relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, e_beqSlack, ctx, indEnd,
                                       Coeff0, &c_success, &b_status);
        } else if (ctx->zero_start && (!ctx->zero_end)) {
            int j_loop_ub;
            // 'FeedratePlanning_LP:98' elseif( ctx.zero_start && ~ctx.zero_end )
            // 'FeedratePlanning_LP:99' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:100'                         f, A,
            // b, Aeq, beq, ctx, indStart, false, maxIter);
            c_beqSlack.set_size(beqSlack.size(0));
            j_loop_ub = beqSlack.size(0) - 1;
            for (int i25{0}; i25 <= j_loop_ub; i25++) {
                c_beqSlack[i25] = beqSlack[i25];
            }
            relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, c_beqSlack, ctx, ctx->k0,
                                     Coeff0, &c_success, &b_status);
        } else {
            int i_loop_ub;
            // 'FeedratePlanning_LP:101' else
            // 'FeedratePlanning_LP:102' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:103'                         f, A,
            // b, Aeq, beq, ctx, indEnd, true, maxIter);
            b_beqSlack.set_size(beqSlack.size(0));
            i_loop_ub = beqSlack.size(0) - 1;
            for (int i24{0}; i24 <= i_loop_ub; i24++) {
                b_beqSlack[i24] = beqSlack[i24];
            }
            b_relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, b_beqSlack, ctx, indEnd,
                                       Coeff0, &c_success, &b_status);
        }
    }
    //  Check the status of the optimization
    // 'FeedratePlanning_LP:108' if( ~success )
    if (c_success) {
        int g_loop_ub;
        // 'FeedratePlanning_LP:113' else
        // 'FeedratePlanning_LP:114' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (Coeff0.size(0) - 1 < 1) {
            g_loop_ub = 0;
        } else {
            g_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, g_loop_ub);
        for (int i19{0}; i19 < g_loop_ub; i19++) {
            b_Coeff0[i19] = Coeff0[i19];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i20{0}; i20 < loop_ub_tmp; i20++) {
            for (int i22{0}; i22 < BasisVal_idx_0; i22++) {
                Coeff[i22 + Coeff.size(0) * i20] = b_Coeff0[i22 + BasisVal_idx_0 * i20];
            }
        }
        // 'FeedratePlanning_LP:115' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
    } else {
        // 'FeedratePlanning_LP:109' Coeff = [];
        // 'FeedratePlanning_LP:110' if( coder.target( "MATLAB" ) )
        // 'FeedratePlanning_LP:111' error( optName + " failed...");
    }
    //  2) Optimization : second LP with jerk constraints and slack
    // 'FeedratePlanning_LP:35' if( ctx.cfg.opt.UseConstraintsOnJerk )
    if (ctx->cfg.opt.UseConstraintsOnJerk) {
        int c_input_sizes_idx_0;
        int d_input_sizes_idx_0;
        int d_result;
        int o_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int s_loop_ub;
        int unnamed_idx_1;
        bool c_empty_non_axis_sizes;
        //  B. Constraints : Inequality and Equality
        //  Feedrate, acceleration and jerk
        // 'FeedratePlanning_LP:38' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
        // 'FeedratePlanning_LP:39'         BasisVal, BasisValD, BasisValDD, u_vec );
        b_window.set_size(1, loop_ub);
        for (int i21{0}; i21 < loop_ub; i21++) {
            b_window[i21] = window[i21];
        }
        c_ctx = ctx->kin;
        buildConstrJerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                        ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                        ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &c_ctx, b_window, Coeff,
                        jmax, BasisVal, BasisValD, BasisValDD, u_vec, Aj, bj);
        // 'FeedratePlanning_LP:41' Atot = [ A; Aj ];
        if ((A.size(0) != 0) && (A.size(1) != 0)) {
            d_result = A.size(1);
        } else if ((Aj.size(0) != 0) && (Aj.size(1) != 0)) {
            d_result = Aj.size(1);
        } else {
            d_result = A.size(1);
            if (Aj.size(1) > A.size(1)) {
                d_result = Aj.size(1);
            }
        }
        c_empty_non_axis_sizes = (d_result == 0);
        if (c_empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
            c_input_sizes_idx_0 = A.size(0);
        } else {
            c_input_sizes_idx_0 = 0;
        }
        if (c_empty_non_axis_sizes || ((Aj.size(0) != 0) && (Aj.size(1) != 0))) {
            d_input_sizes_idx_0 = Aj.size(0);
        } else {
            d_input_sizes_idx_0 = 0;
        }
        // 'FeedratePlanning_LP:41' btot = [ b; bj ];
        // 'FeedratePlanning_LP:43' indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];
        if (bj.size(0) < 1) {
            y.set_size(1, 0);
        } else {
            int n_loop_ub;
            y.set_size(1, bj.size(0));
            n_loop_ub = bj.size(0) - 1;
            for (int i29{0}; i29 <= n_loop_ub; i29++) {
                y[i29] = i29 + 1U;
            }
        }
        varargin_2.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i30{0}; i30 < o_loop_ub; i30++) {
            varargin_2[i30] = y[i30] + b_b.size(0);
        }
        // 'FeedratePlanning_LP:45' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f,
        // ... 'FeedratePlanning_LP:46'         Atot, btot, Aeq, beq, indSlack, LP );
        if (varargin_2.size(1) != 0) {
            unnamed_idx_1 = varargin_2.size(1);
        } else {
            unnamed_idx_1 = 0;
        }
        b_A.set_size(c_input_sizes_idx_0 + d_input_sizes_idx_0, d_result);
        for (int i31{0}; i31 < d_result; i31++) {
            for (int i33{0}; i33 < c_input_sizes_idx_0; i33++) {
                b_A[i33 + b_A.size(0) * i31] = A[i33 + c_input_sizes_idx_0 * i31];
            }
        }
        for (int i32{0}; i32 < d_result; i32++) {
            for (int i34{0}; i34 < d_input_sizes_idx_0; i34++) {
                b_A[(i34 + c_input_sizes_idx_0) + b_A.size(0) * i32] =
                    Aj[i34 + d_input_sizes_idx_0 * i32];
            }
        }
        c_b.set_size(b_b.size(0) + bj.size(0));
        p_loop_ub = b_b.size(0);
        for (int i35{0}; i35 < p_loop_ub; i35++) {
            c_b[i35] = b_b[i35];
        }
        q_loop_ub = bj.size(0);
        for (int i36{0}; i36 < q_loop_ub; i36++) {
            c_b[i36 + b_b.size(0)] = bj[i36];
        }
        ::coder::array<double, 2U> b_varargin_2;
        b_varargin_2 = varargin_2.reshape(1, unnamed_idx_1);
        add_slack(f, b_A, c_b, Aeq, b_varargin_2, ctx->cfg.opt.SLACK_PENALTY, fSlack, ASlack,
                  bSlack, AeqSlack);
        // 'FeedratePlanning_LP:48' [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack, ASlack,
        // bSlack, ... 'FeedratePlanning_LP:49'         AeqSlack, beqSlack, ctx, ...
        // 'FeedratePlanning_LP:50'         N, NWindow, "Second LP" );
        //  Call the solver
        // -------------------------------------------------------------------------
        //  Functions
        // -------------------------------------------------------------------------
        // 'FeedratePlanning_LP:71' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
        // Aeq, ... 'FeedratePlanning_LP:72'     beq, ctx );
        coder::b_sparse(ASlack, &r1);
        c_simplex(fSlack, &r1, bSlack, AeqSlack, beqSlack, Coeff0, &e_success, &b_status);
        f_success = e_success;
        //  If optimization failed due with zero end constaints, decrease pseudo jerk
        // 'FeedratePlanning_LP:74' if( ~success && ( ctx.zero_end || ctx.zero_start ) )
        if ((!e_success) && (ctx->zero_end || ctx->zero_start)) {
            double b_Ntot;
            int b_indEnd;
            // 'FeedratePlanning_LP:75' Ntot        = NWindow;
            b_Ntot = NWindow;
            // 'FeedratePlanning_LP:76' maxIter     = 15;
            // 'FeedratePlanning_LP:77' indStart    = ctx.k0;
            // 'FeedratePlanning_LP:78' indEnd      = ctx.k0;
            b_indEnd = ctx->k0;
            // 'FeedratePlanning_LP:80' if(ctx.zero_start)
            if (ctx->zero_start) {
                // 'FeedratePlanning_LP:81' Ntot        = Ntot + 1;
                b_Ntot = NWindow + 1.0;
            }
            // 'FeedratePlanning_LP:84' if(ctx.zero_end)
            if (ctx->zero_end) {
                // 'FeedratePlanning_LP:85' Ntot        = Ntot + 1;
                b_Ntot++;
                // 'FeedratePlanning_LP:86' indEnd      = ctx.k0 + Ntot -1;
                b_indEnd = static_cast<int>(std::round(static_cast<double>(ctx->k0) + b_Ntot)) - 1;
            }
            // 'FeedratePlanning_LP:89' if( ctx.zero_start && ctx.zero_end )
            if (ctx->zero_start && ctx->zero_end) {
                int u_loop_ub;
                // 'FeedratePlanning_LP:90' beq( end-1 )    = -ctx.cfg.v_1^2;
                beqSlack[beqSlack.size(0) - 2] = -(ctx->cfg.v_1 * ctx->cfg.v_1);
                // 'FeedratePlanning_LP:91' beq( end )      = -ctx.cfg.at_1;
                beqSlack[beqSlack.size(0) - 1] = -ctx->cfg.at_1;
                // 'FeedratePlanning_LP:92' [ctx,Coeff0, success, status, msg] =
                // relax_intial_constraints( ... 'FeedratePlanning_LP:93'                         f,
                // A, b, Aeq, beq, ctx, indStart, false, maxIter);
                f_beqSlack.set_size(beqSlack.size(0));
                u_loop_ub = beqSlack.size(0) - 1;
                for (int i42{0}; i42 <= u_loop_ub; i42++) {
                    f_beqSlack[i42] = beqSlack[i42];
                }
                relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, f_beqSlack, ctx, ctx->k0,
                                         Coeff0, &g_success, &d_status);
                // 'FeedratePlanning_LP:94' beq( 1 )        = ctx.v_0^2;
                beqSlack[0] = ctx->v_0 * ctx->v_0;
                // 'FeedratePlanning_LP:95' beq( 2 )        = ctx.at_0;
                beqSlack[1] = ctx->at_0;
                // 'FeedratePlanning_LP:96' [ctx, Coeff0, success, status, msg] =
                // relax_intial_constraints( ... 'FeedratePlanning_LP:97'                         f,
                // A, b, Aeq, beq, ctx, indEnd, true, maxIter);
                b_relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, beqSlack, ctx,
                                           b_indEnd, Coeff0, &f_success, &b_status);
            } else if (ctx->zero_start && (!ctx->zero_end)) {
                // 'FeedratePlanning_LP:98' elseif( ctx.zero_start && ~ctx.zero_end )
                // 'FeedratePlanning_LP:99' [ctx, Coeff0, success, status, msg] =
                // relax_intial_constraints( ... 'FeedratePlanning_LP:100' f, A, b, Aeq, beq, ctx,
                // indStart, false, maxIter);
                relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, beqSlack, ctx, ctx->k0,
                                         Coeff0, &f_success, &b_status);
            } else {
                // 'FeedratePlanning_LP:101' else
                // 'FeedratePlanning_LP:102' [ctx, Coeff0, success, status, msg] =
                // relax_intial_constraints( ... 'FeedratePlanning_LP:103' f, A, b, Aeq, beq, ctx,
                // indEnd, true, maxIter);
                b_relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, beqSlack, ctx,
                                           b_indEnd, Coeff0, &f_success, &b_status);
            }
        }
        //  Check the status of the optimization
        // 'FeedratePlanning_LP:108' if( ~success )
        if (f_success) {
            int r_loop_ub;
            // 'FeedratePlanning_LP:113' else
            // 'FeedratePlanning_LP:114' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
            if (Coeff0.size(0) - 1 < 1) {
                r_loop_ub = 0;
            } else {
                r_loop_ub = Coeff0.size(0) - 1;
            }
            b_Coeff0.set_size(1, r_loop_ub);
            for (int i38{0}; i38 < r_loop_ub; i38++) {
                b_Coeff0[i38] = Coeff0[i38];
            }
            BasisVal_idx_0 = BasisVal.size(1);
            b_Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
            for (int i40{0}; i40 < loop_ub_tmp; i40++) {
                for (int i41{0}; i41 < BasisVal_idx_0; i41++) {
                    b_Coeff[i41 + b_Coeff.size(0) * i40] = b_Coeff0[i41 + BasisVal_idx_0 * i40];
                }
            }
            // 'FeedratePlanning_LP:115' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
        } else {
            // 'FeedratePlanning_LP:109' Coeff = [];
            // 'FeedratePlanning_LP:110' if( coder.target( "MATLAB" ) )
            // 'FeedratePlanning_LP:111' error( optName + " failed...");
        }
        Coeff.set_size(b_Coeff.size(0), b_Coeff.size(1));
        s_loop_ub = b_Coeff.size(1);
        for (int i37{0}; i37 < s_loop_ub; i37++) {
            int t_loop_ub;
            t_loop_ub = b_Coeff.size(0);
            for (int i39{0}; i39 < t_loop_ub; i39++) {
                Coeff[i39 + Coeff.size(0) * i37] = b_Coeff[i39 + b_Coeff.size(0) * i37];
            }
        }
    }
    // 'FeedratePlanning_LP:53' if( ~ctx.zero_start )
    if (!ctx->zero_start) {
        double X_idx_0;
        double X_idx_1;
        int inner;
        //  Compute the continuity equations
        // 'FeedratePlanning_LP:55' X           = continuity * Coeff( : , 1 );
        inner = continuity.size(1);
        X_idx_0 = 0.0;
        X_idx_1 = 0.0;
        for (int b_k{0}; b_k < inner; b_k++) {
            X_idx_0 += continuity[2 * b_k] * Coeff[b_k];
            X_idx_1 += continuity[2 * b_k + 1] * Coeff[b_k];
        }
        // 'FeedratePlanning_LP:56' ctx.v_0     = sqrt( X( 1 ) );
        ctx->v_0 = std::sqrt(X_idx_0);
        // 'FeedratePlanning_LP:57' ctx.at_0    = X( 2 );
        ctx->at_0 = X_idx_1;
    }
    // 'FeedratePlanning_LP:60' ctx.Coeff   = Coeff;
    ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
    h_loop_ub = Coeff.size(1);
    for (int i23{0}; i23 < h_loop_ub; i23++) {
        int k_loop_ub;
        k_loop_ub = Coeff.size(0);
        for (int i26{0}; i26 < k_loop_ub; i26++) {
            ctx->Coeff[i26 + ctx->Coeff.size(0) * i23] = Coeff[i26 + Coeff.size(0) * i23];
        }
    }
    *success = true;
    *status = b_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_LP.cpp
//
// [EOF]
//
