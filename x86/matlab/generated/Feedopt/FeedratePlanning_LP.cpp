
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "FeedratePlanning_LP.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "buildConstr.h"
#include "buildConstrJerk.h"
#include "c_simplex.h"
#include "calcZeroConstraints.h"
#include "mtimes.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types111.h"
#include "queue_coder.h"
#include "repmat.h"
#include "sparse.h"
#include "sparse1.h"
#include "string1.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
#include <emmintrin.h>

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
                                       bool *success, int *status, coder::rtString *msg);

static void relax_intial_constraints(const ::coder::array<double, 1U> &f,
                                     const ::coder::array<double, 2U> &A,
                                     const ::coder::array<double, 1U> &b,
                                     const ::coder::array<double, 2U> &Aeq,
                                     ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx,
                                     int indCurv, ::coder::array<double, 2U> &Coeff0, bool *success,
                                     int *status, coder::rtString *msg);

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
    // 'FeedratePlanning_LP:126' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:128' if( 0 )
    // 'FeedratePlanning_LP:134' else
    // 'FeedratePlanning_LP:135' Apos = [];
    // 'FeedratePlanning_LP:136' bpos = [];
    //  Slack variables
    // 'FeedratePlanning_LP:140' vecSlack    = zeros( nAL, 1 );
    vecSlack.set_size(A.size(0));
    loop_ub = A.size(0);
    for (int i{0}; i < loop_ub; i++) {
        vecSlack[i] = 0;
    }
    // 'FeedratePlanning_LP:140' vecSlack( indSlack ) = -1;
    r.set_size(1, indSlack.size(1));
    b_loop_ub = indSlack.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r[i1] = static_cast<int>(indSlack[i1]);
    }
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        vecSlack[r[i2] - 1] = -1;
    }
    // 'FeedratePlanning_LP:141' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i3{0}; i3 < b_f; i3++) {
        fSlack[i3] = f[i3];
    }
    fSlack[b_f] = LP_SLACK_PENALTY;
    // 'FeedratePlanning_LP:142' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
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
    // 'FeedratePlanning_LP:143' bSlack      = [ bpos; b ; 0 ];
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
    // 'FeedratePlanning_LP:144' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    // 'FeedratePlanning_LP:145' beqSlack    = beq;
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
//                coder::rtString *msg
// Return Type  : void
//
static void b_relax_intial_constraints(const ::coder::array<double, 1U> &f,
                                       const ::coder::array<double, 2U> &A,
                                       const ::coder::array<double, 1U> &b,
                                       const ::coder::array<double, 2U> &Aeq,
                                       ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx,
                                       int indCurv, ::coder::array<double, 2U> &Coeff0,
                                       bool *success, int *status, coder::rtString *msg)
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
    // 'FeedratePlanning_LP:156' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:157' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:158' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:159' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:160' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:161' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:162' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:163' msg         = "";
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    // 'FeedratePlanning_LP:165' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        // 'FeedratePlanning_LP:166' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:150' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:151' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        b_calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                              ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                              ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                              ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, &b_vNorm,
                              &b_atNorm);
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:168' if(isEnd)
        // 'FeedratePlanning_LP:169' beq( end-1 )    = -vNorm^2;
        beq[beq.size(0) - 2] = -(b_vNorm * b_vNorm);
        // 'FeedratePlanning_LP:170' beq( end )      = atNorm;
        beq[beq.size(0) - 1] = b_atNorm;
        // 'FeedratePlanning_LP:176' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:177'         Aeq, beq, ctx );
        coder::b_sparse(A, &r);
        c_simplex(f, &r, b, Aeq, beq, Coeff0, &b_success, &b_status);
        msg->Value.size[0] = 1;
        msg->Value.size[1] = 0;
        // 'FeedratePlanning_LP:178' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:183' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:184' if(isEnd)
    // 'FeedratePlanning_LP:185' ctx.at_1    = -atNorm;
    ctx->at_1 = -atNorm;
    // 'FeedratePlanning_LP:186' ctx.v_1     = -vNorm;
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
//                coder::rtString *msg
// Return Type  : void
//
static void relax_intial_constraints(const ::coder::array<double, 1U> &f,
                                     const ::coder::array<double, 2U> &A,
                                     const ::coder::array<double, 1U> &b,
                                     const ::coder::array<double, 2U> &Aeq,
                                     ::coder::array<double, 1U> &beq, b_FeedoptContext *ctx,
                                     int indCurv, ::coder::array<double, 2U> &Coeff0, bool *success,
                                     int *status, coder::rtString *msg)
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
    // 'FeedratePlanning_LP:156' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:157' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:158' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:159' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:160' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:161' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:162' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:163' msg         = "";
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    // 'FeedratePlanning_LP:165' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        // 'FeedratePlanning_LP:166' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:150' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:151' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, &b_vNorm,
                            &b_atNorm);
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:168' if(isEnd)
        // 'FeedratePlanning_LP:171' else
        // 'FeedratePlanning_LP:172' beq( 1 )        = vNorm^2;
        beq[0] = b_vNorm * b_vNorm;
        // 'FeedratePlanning_LP:173' beq( 2 )        = atNorm;
        beq[1] = b_atNorm;
        // 'FeedratePlanning_LP:176' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:177'         Aeq, beq, ctx );
        coder::b_sparse(A, &r);
        c_simplex(f, &r, b, Aeq, beq, Coeff0, &b_success, &b_status);
        msg->Value.size[0] = 1;
        msg->Value.size[1] = 0;
        // 'FeedratePlanning_LP:178' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:183' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:184' if(isEnd)
    // 'FeedratePlanning_LP:187' else
    // 'FeedratePlanning_LP:188' ctx.at_0    = atNorm;
    ctx->at_0 = atNorm;
    // 'FeedratePlanning_LP:189' ctx.v_0     = vNorm;
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
//                coder::rtString *msg
// Return Type  : void
//
void FeedratePlanning_LP(b_FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &window,
                         const double amax[6], const double jmax[6],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr,
                         const ::coder::array<double, 2U> &u_vec, double NWindow,
                         ::coder::array<double, 2U> &Coeff, bool *success, int *status,
                         coder::rtString *msg)
{
    Kinematics b_ctx;
    Kinematics c_ctx;
    coder::sparse r12;
    coder::sparse r4;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> ASlack;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> AeqSlack;
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> C;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> D;
    ::coder::array<double, 2U> b_A;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_Aj;
    ::coder::array<double, 2U> b_Coeff0;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 2U> lCurvs;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 1U> bSlack;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_beqSlack;
    ::coder::array<double, 1U> beqSlack;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> c_beqSlack;
    ::coder::array<double, 1U> d_beqSlack;
    ::coder::array<double, 1U> fSlack;
    ::coder::array<double, 1U> r5;
    ::coder::array<double, 1U> t;
    ::coder::array<double, 1U> v;
    ::coder::array<unsigned int, 2U> y;
    ::coder::array<signed char, 2U> varargin_3;
    double X[2];
    int BasisVal_idx_0;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_status;
    int c_input_sizes_idx_1;
    int c_loop_ub;
    int c_result;
    int calclen;
    int calclen_idx_0;
    int d_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int i17;
    int i7;
    int i_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int j_loop_ub;
    int loop_ub;
    int nc;
    int nv;
    int result;
    int scalarLB;
    int sizes_idx_1;
    int vectorUB;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool b_success;
    bool c_success;
    bool d_success;
    bool e_success;
    bool empty_non_axis_sizes;
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
    // 'FeedratePlanning_LP:14' [ D, Dinv ] = compute_scaling_matrix( ctx, CurvArray, N );
    // 'FeedratePlanning_LP:195' N       = length( curvArray );
    // 'FeedratePlanning_LP:197' if( ctx.cfg.opt.USE_LENGTH_SCALING )
    if (ctx->cfg.opt.USE_LENGTH_SCALING) {
        int b_lCurvs;
        int i;
        // 'FeedratePlanning_LP:198' lCurvs  = zeros( NCoeff, N );
        lCurvs.set_size(BasisVal.size(1), loop_ub);
        // 'FeedratePlanning_LP:200' for ind = 1 : N
        i = loop_ub - 1;
        if (loop_ub - 1 >= 0) {
            b_loop_ub = BasisVal.size(1);
        }
        for (int ind{0}; ind <= i; ind++) {
            double b;
            // 'FeedratePlanning_LP:201' lCurvs( :, ind ) = ones( NCoeff, 1 ) * LengthCurv( ctx, ...
            // 'FeedratePlanning_LP:202'                 curvArray( ind ), 0, 1 );
            b = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                           ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                           ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                           ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &window[ind]);
            for (int i2{0}; i2 < b_loop_ub; i2++) {
                lCurvs[i2 + lCurvs.size(0) * ind] = b;
            }
        }
        // 'FeedratePlanning_LP:204' t       = lCurvs( : ).^2;
        b_lCurvs = lCurvs.size(0) * lCurvs.size(1);
        t.set_size(b_lCurvs);
        for (int i4{0}; i4 < b_lCurvs; i4++) {
            double varargin_1;
            varargin_1 = lCurvs[i4];
            t[i4] = std::pow(varargin_1, 2.0);
        }
    } else {
        int unnamed_idx_0;
        // 'FeedratePlanning_LP:205' else
        // 'FeedratePlanning_LP:206' t       = ones( N * NCoeff, 1  );
        unnamed_idx_0 =
            static_cast<int>(static_cast<double>(loop_ub) * static_cast<double>(BasisVal.size(1)));
        t.set_size(unnamed_idx_0);
        for (int i1{0}; i1 < unnamed_idx_0; i1++) {
            t[i1] = 1.0;
        }
    }
    // 'FeedratePlanning_LP:209' D       = diag( 1 ./ t );
    v.set_size(t.size(0));
    c_loop_ub = t.size(0);
    scalarLB = (t.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&t[i3]);
        _mm_storeu_pd(&v[i3], _mm_div_pd(_mm_set1_pd(1.0), r));
    }
    for (int i3{scalarLB}; i3 < c_loop_ub; i3++) {
        v[i3] = 1.0 / t[i3];
    }
    nv = v.size(0);
    D.set_size(v.size(0), v.size(0));
    d_loop_ub = v.size(0);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        int e_loop_ub;
        e_loop_ub = v.size(0);
        for (int i6{0}; i6 < e_loop_ub; i6++) {
            D[i6 + D.size(0) * i5] = 0.0;
        }
    }
    for (int j{0}; j < nv; j++) {
        D[j + D.size(0) * j] = v[j];
    }
    // 'FeedratePlanning_LP:210' Dinv    = diag( t );
    // 'FeedratePlanning_LP:15' DCon        = D( [ 1 : N ], [ 1 : N ] );
    if (BasisVal.size(1) < 1) {
        i7 = 0;
    } else {
        i7 = BasisVal.size(1);
    }
    //  A. Linear objectif
    // 'FeedratePlanning_LP:18' f = -repmat( BasisIntegr, 1, NWindow );
    coder::repmat(BasisIntegr, NWindow, r1);
    f.set_size(r1.size(0), r1.size(1));
    f_loop_ub = r1.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        int b_scalarLB;
        int b_vectorUB;
        int g_loop_ub;
        g_loop_ub = r1.size(0);
        b_scalarLB = (r1.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i9{0}; i9 <= b_vectorUB; i9 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r1[i9 + r1.size(0) * i8]);
            _mm_storeu_pd(&f[i9 + f.size(0) * i8], _mm_mul_pd(r3, _mm_set1_pd(-1.0)));
        }
        for (int i9{b_scalarLB}; i9 < g_loop_ub; i9++) {
            f[i9 + f.size(0) * i8] = -r1[i9 + r1.size(0) * i8];
        }
    }
    // 'FeedratePlanning_LP:19' f = reshape( f( : )'  * D, [], NWindow );
    inner = f.size(0) * f.size(1);
    nc = D.size(1);
    r2.set_size(1, D.size(1));
    for (int b_j{0}; b_j < nc; b_j++) {
        r2[b_j] = 0.0;
        for (int k{0}; k < inner; k++) {
            r2[b_j] = r2[b_j] + f[k] * D[k + D.size(0) * b_j];
        }
    }
    if (static_cast<int>(NWindow) > 0) {
        calclen = r2.size(1) / static_cast<int>(NWindow);
    } else {
        calclen = 0;
    }
    //  B. Constraints : Inequality and Equality
    //  Feedrate and acceleration
    // 'FeedratePlanning_LP:23' [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax,
    // ctx.v_0, ... 'FeedratePlanning_LP:24'     ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD,
    // u_vec);
    b_window.set_size(1, loop_ub);
    for (int i10{0}; i10 < loop_ub; i10++) {
        b_window[i10] = window[i10];
    }
    b_ctx = ctx->kin;
    buildConstr(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS,
                ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS, &b_ctx, b_window, amax, ctx->v_0, ctx->at_0,
                ctx->v_1, ctx->at_1, BasisVal, BasisValD, u_vec, A, b_b, Aeq, beqSlack, continuity);
    // 'FeedratePlanning_LP:27' A           = A * D;
    coder::internal::blas::mtimes(A, D, b_A);
    // 'FeedratePlanning_LP:28' Aeq         = Aeq * D;
    coder::internal::blas::mtimes(Aeq, D, b_Aeq);
    // 'FeedratePlanning_LP:29' continuity  = continuity * DCon;
    // 'FeedratePlanning_LP:31' indSlack =  [];
    // 1 : numel( b );
    // 'FeedratePlanning_LP:33' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    // 'FeedratePlanning_LP:34'     A, b, Aeq, beq, indSlack, LP );
    // 'FeedratePlanning_LP:126' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:128' if( 0 )
    // 'FeedratePlanning_LP:134' else
    // 'FeedratePlanning_LP:135' Apos = [];
    // 'FeedratePlanning_LP:136' bpos = [];
    //  Slack variables
    // 'FeedratePlanning_LP:140' vecSlack    = zeros( nAL, 1 );
    // 'FeedratePlanning_LP:140' vecSlack( indSlack ) = -1;
    // 'FeedratePlanning_LP:141' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    calclen_idx_0 = calclen * static_cast<int>(NWindow);
    fSlack.set_size(calclen_idx_0 + 1);
    for (int i11{0}; i11 < calclen_idx_0; i11++) {
        fSlack[i11] = r2[i11];
    }
    fSlack[calclen_idx_0] = ctx->cfg.opt.SLACK_PENALTY;
    // 'FeedratePlanning_LP:142' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
    if ((b_A.size(0) != 0) && (b_A.size(1) != 0)) {
        result = b_A.size(0);
    } else if (b_A.size(0) != 0) {
        result = b_A.size(0);
    } else {
        result = 0;
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((b_A.size(0) != 0) && (b_A.size(1) != 0))) {
        input_sizes_idx_1 = b_A.size(1);
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (b_A.size(0) != 0)) {
        b_input_sizes_idx_1 = 1;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    b_result.set_size(result, input_sizes_idx_1 + b_input_sizes_idx_1);
    for (int i12{0}; i12 < input_sizes_idx_1; i12++) {
        for (int i13{0}; i13 < result; i13++) {
            b_result[i13 + b_result.size(0) * i12] = b_A[i13 + result * i12];
        }
    }
    h_loop_ub = b_input_sizes_idx_1;
    for (int i14{0}; i14 < h_loop_ub; i14++) {
        for (int i15{0}; i15 < result; i15++) {
            b_result[i15 + b_result.size(0) * input_sizes_idx_1] = 0.0;
        }
    }
    varargin_3.set_size(1, b_A.size(1) + 1);
    i_loop_ub = b_A.size(1);
    for (int i16{0}; i16 < i_loop_ub; i16++) {
        varargin_3[i16] = 0;
    }
    varargin_3[b_A.size(1)] = -1;
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
        i17 = b_result.size(0);
    } else {
        i17 = 0;
    }
    ASlack.set_size(i17 + 1, sizes_idx_1);
    for (int i18{0}; i18 < sizes_idx_1; i18++) {
        for (int i20{0}; i20 < input_sizes_idx_0; i20++) {
            ASlack[i20 + ASlack.size(0) * i18] = b_result[i20 + input_sizes_idx_0 * i18];
        }
    }
    for (int i19{0}; i19 < sizes_idx_1; i19++) {
        ASlack[input_sizes_idx_0 + ASlack.size(0) * i19] = varargin_3[i19];
    }
    // 'FeedratePlanning_LP:143' bSlack      = [ bpos; b ; 0 ];
    if (b_b.size(0) != 0) {
        b_input_sizes_idx_0 = b_b.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    bSlack.set_size(b_input_sizes_idx_0 + 1);
    for (int i21{0}; i21 < b_input_sizes_idx_0; i21++) {
        bSlack[i21] = b_b[i21];
    }
    bSlack[b_input_sizes_idx_0] = 0.0;
    // 'FeedratePlanning_LP:144' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
    if ((b_Aeq.size(0) != 0) && (b_Aeq.size(1) != 0)) {
        c_result = b_Aeq.size(0);
    } else if (b_Aeq.size(0) != 0) {
        c_result = b_Aeq.size(0);
    } else {
        c_result = 0;
    }
    b_empty_non_axis_sizes = (c_result == 0);
    if (b_empty_non_axis_sizes || ((b_Aeq.size(0) != 0) && (b_Aeq.size(1) != 0))) {
        c_input_sizes_idx_1 = b_Aeq.size(1);
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (b_empty_non_axis_sizes || (b_Aeq.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    AeqSlack.set_size(c_result, c_input_sizes_idx_1 + d_input_sizes_idx_1);
    for (int i22{0}; i22 < c_input_sizes_idx_1; i22++) {
        for (int i23{0}; i23 < c_result; i23++) {
            AeqSlack[i23 + AeqSlack.size(0) * i22] = b_Aeq[i23 + c_result * i22];
        }
    }
    j_loop_ub = d_input_sizes_idx_1;
    for (int i24{0}; i24 < j_loop_ub; i24++) {
        for (int i25{0}; i25 < c_result; i25++) {
            AeqSlack[i25 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:145' beqSlack    = beq;
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:38' [ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack,
    // ASlack, bSlack, ... 'FeedratePlanning_LP:39'     AeqSlack, beqSlack, ctx, N, NWindow, "First
    // LP" );
    //  Call the solver
    // -------------------------------------------------------------------------
    //  Functions
    // -------------------------------------------------------------------------
    // 'FeedratePlanning_LP:86' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, ... 'FeedratePlanning_LP:87'     beq, ctx );
    coder::b_sparse(ASlack, &r4);
    c_simplex(fSlack, &r4, bSlack, AeqSlack, beqSlack, Coeff0, &b_success, &b_status);
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    c_success = b_success;
    // 'FeedratePlanning_LP:89' if( ~success && ( ctx.zero_start || ctx.zero_end ) )
    if ((!b_success) && (ctx->zero_start || ctx->zero_end)) {
        double Ntot;
        //  ZN or NZ case :
        //  Optimization failed due with zero end constaints, decrease pseudo jerk
        // 'FeedratePlanning_LP:92' Ntot        = NWindow;
        Ntot = NWindow;
        // 'FeedratePlanning_LP:93' maxIter     = 15;
        // 'FeedratePlanning_LP:95' if( ~success && ctx.zero_start )
        if (ctx->zero_start) {
            int l_loop_ub;
            // 'FeedratePlanning_LP:96' Ntot        = Ntot + 1;
            Ntot = NWindow + 1.0;
            // 'FeedratePlanning_LP:97' indStart    = ctx.k0;
            // 'FeedratePlanning_LP:98' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:99'                 f, A, b, Aeq,
            // beq, ctx, indStart, false, maxIter);
            b_beqSlack.set_size(beqSlack.size(0));
            l_loop_ub = beqSlack.size(0) - 1;
            for (int i27{0}; i27 <= l_loop_ub; i27++) {
                b_beqSlack[i27] = beqSlack[i27];
            }
            relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, b_beqSlack, ctx, ctx->k0,
                                     Coeff0, &c_success, &b_status, msg);
        }
        // 'FeedratePlanning_LP:102' if( ~success && ctx.zero_end )
        if ((!c_success) && ctx->zero_end) {
            int n_loop_ub;
            // 'FeedratePlanning_LP:103' Ntot        = Ntot + 1;
            Ntot++;
            // 'FeedratePlanning_LP:104' indEnd      = ctx.k0 + Ntot -1;
            // 'FeedratePlanning_LP:105' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:106'                 f, A, b, Aeq,
            // beq, ctx, indEnd, true, maxIter);
            c_beqSlack.set_size(beqSlack.size(0));
            n_loop_ub = beqSlack.size(0) - 1;
            for (int i29{0}; i29 <= n_loop_ub; i29++) {
                c_beqSlack[i29] = beqSlack[i29];
            }
            b_relax_intial_constraints(
                fSlack, ASlack, bSlack, AeqSlack, c_beqSlack, ctx,
                static_cast<int>(std::round(static_cast<double>(ctx->k0) + Ntot)) - 1, Coeff0,
                &c_success, &b_status, msg);
        }
    }
    //  Check the status of the optimization
    // 'FeedratePlanning_LP:111' Coeff = [];
    Coeff.set_size(0, 0);
    // 'FeedratePlanning_LP:112' if( success )
    if (c_success) {
        int k_loop_ub;
        int m_loop_ub;
        // 'FeedratePlanning_LP:113' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (Coeff0.size(0) - 1 < 1) {
            k_loop_ub = 0;
        } else {
            k_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, k_loop_ub);
        for (int i26{0}; i26 < k_loop_ub; i26++) {
            b_Coeff0[i26] = Coeff0[i26];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), static_cast<int>(NWindow));
        m_loop_ub = static_cast<int>(NWindow);
        for (int i28{0}; i28 < m_loop_ub; i28++) {
            for (int i30{0}; i30 < BasisVal_idx_0; i30++) {
                Coeff[i30 + Coeff.size(0) * i28] = b_Coeff0[i30 + BasisVal_idx_0 * i28];
            }
        }
        // 'FeedratePlanning_LP:115' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
    } else {
        // 'FeedratePlanning_LP:118' else
        // 'FeedratePlanning_LP:119' msg = optName + " failed...";
        msg->init();
    }
    d_success = c_success;
    // 'FeedratePlanning_LP:41' if( ~success )
    if (c_success) {
        int b_Coeff;
        //  2) Optimization : second LP with jerk constraints and slack
        // 'FeedratePlanning_LP:45' if( ctx.cfg.opt.UseConstraintsOnJerk )
        if (ctx->cfg.opt.UseConstraintsOnJerk) {
            ::coder::array<double, 1U> c_Coeff;
            int b_calclen;
            int c_input_sizes_idx_0;
            int calclen_idx_1;
            int d_input_sizes_idx_0;
            int d_result;
            int p_loop_ub;
            int q_loop_ub;
            int r_loop_ub;
            int unnamed_idx_1;
            bool c_empty_non_axis_sizes;
            // 'FeedratePlanning_LP:46' Coeff       = reshape( D * Coeff( : ), N, [] );
            b_Coeff = Coeff.size(0) * Coeff.size(1);
            c_Coeff = Coeff.reshape(b_Coeff);
            coder::internal::blas::mtimes(D, c_Coeff, r5);
            //  B. Constraints : Inequality and Equality
            //  Feedrate, acceleration and jerk
            // 'FeedratePlanning_LP:49' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax,
            // ... 'FeedratePlanning_LP:50'         BasisVal, BasisValD, BasisValDD, u_vec );
            if (BasisVal.size(1) > 0) {
                b_calclen = r5.size(0) / BasisVal.size(1);
            } else {
                b_calclen = 0;
            }
            BasisVal_idx_0 = BasisVal.size(1);
            b_window.set_size(1, loop_ub);
            for (int i31{0}; i31 < loop_ub; i31++) {
                b_window[i31] = window[i31];
            }
            ::coder::array<double, 2U> r7;
            c_ctx = ctx->kin;
            r7 = r5.reshape(BasisVal_idx_0, b_calclen);
            buildConstrJerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &c_ctx, b_window,
                            r7, jmax, BasisVal, BasisValD, BasisValDD, u_vec, Aj, bj);
            // 'FeedratePlanning_LP:52' Aj   = Aj * D;
            coder::internal::blas::mtimes(Aj, D, b_Aj);
            // 'FeedratePlanning_LP:53' Atot = [ A; Aj ];
            if ((b_A.size(0) != 0) && (b_A.size(1) != 0)) {
                d_result = b_A.size(1);
            } else if ((b_Aj.size(0) != 0) && (b_Aj.size(1) != 0)) {
                d_result = b_Aj.size(1);
            } else {
                d_result = b_A.size(1);
                if (b_Aj.size(1) > b_A.size(1)) {
                    d_result = b_Aj.size(1);
                }
            }
            c_empty_non_axis_sizes = (d_result == 0);
            if (c_empty_non_axis_sizes || ((b_A.size(0) != 0) && (b_A.size(1) != 0))) {
                c_input_sizes_idx_0 = b_A.size(0);
            } else {
                c_input_sizes_idx_0 = 0;
            }
            if (c_empty_non_axis_sizes || ((b_Aj.size(0) != 0) && (b_Aj.size(1) != 0))) {
                d_input_sizes_idx_0 = b_Aj.size(0);
            } else {
                d_input_sizes_idx_0 = 0;
            }
            // 'FeedratePlanning_LP:53' btot = [ b; bj ];
            // 'FeedratePlanning_LP:55' indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];
            if (bj.size(0) < 1) {
                y.set_size(1, 0);
            } else {
                int o_loop_ub;
                y.set_size(1, bj.size(0));
                o_loop_ub = bj.size(0) - 1;
                for (int i36{0}; i36 <= o_loop_ub; i36++) {
                    y[i36] = i36 + 1U;
                }
            }
            varargin_2.set_size(1, y.size(1));
            p_loop_ub = y.size(1);
            for (int i37{0}; i37 < p_loop_ub; i37++) {
                varargin_2[i37] = y[i37] + b_b.size(0);
            }
            // 'FeedratePlanning_LP:57' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack(
            // f, ... 'FeedratePlanning_LP:58'         Atot, btot, Aeq, beq, indSlack, LP );
            calclen_idx_1 = static_cast<int>(NWindow);
            if (varargin_2.size(1) != 0) {
                unnamed_idx_1 = varargin_2.size(1);
            } else {
                unnamed_idx_1 = 0;
            }
            A.set_size(c_input_sizes_idx_0 + d_input_sizes_idx_0, d_result);
            for (int i38{0}; i38 < d_result; i38++) {
                for (int i40{0}; i40 < c_input_sizes_idx_0; i40++) {
                    A[i40 + A.size(0) * i38] = b_A[i40 + c_input_sizes_idx_0 * i38];
                }
            }
            for (int i39{0}; i39 < d_result; i39++) {
                for (int i41{0}; i41 < d_input_sizes_idx_0; i41++) {
                    A[(i41 + c_input_sizes_idx_0) + A.size(0) * i39] =
                        b_Aj[i41 + d_input_sizes_idx_0 * i39];
                }
            }
            c_b.set_size(b_b.size(0) + bj.size(0));
            q_loop_ub = b_b.size(0);
            for (int i42{0}; i42 < q_loop_ub; i42++) {
                c_b[i42] = b_b[i42];
            }
            r_loop_ub = bj.size(0);
            for (int i43{0}; i43 < r_loop_ub; i43++) {
                c_b[i43 + b_b.size(0)] = bj[i43];
            }
            ::coder::array<double, 2U> b_varargin_2;
            ::coder::array<double, 2U> r11;
            r11 = r2.reshape(calclen, calclen_idx_1);
            b_varargin_2 = varargin_2.reshape(1, unnamed_idx_1);
            add_slack(r11, A, c_b, b_Aeq, b_varargin_2, ctx->cfg.opt.SLACK_PENALTY, fSlack, ASlack,
                      bSlack, AeqSlack);
            // 'FeedratePlanning_LP:60' [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack,
            // ASlack, bSlack, ... 'FeedratePlanning_LP:61'         AeqSlack, beqSlack, ctx, N,
            // NWindow, "Second LP" );
            //  Call the solver
            // -------------------------------------------------------------------------
            //  Functions
            // -------------------------------------------------------------------------
            // 'FeedratePlanning_LP:86' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A
            // ), b, Aeq, ... 'FeedratePlanning_LP:87'     beq, ctx );
            coder::b_sparse(ASlack, &r12);
            c_simplex(fSlack, &r12, bSlack, AeqSlack, beqSlack, Coeff0, &e_success, &b_status);
            msg->Value.size[0] = 1;
            msg->Value.size[1] = 0;
            d_success = e_success;
            // 'FeedratePlanning_LP:89' if( ~success && ( ctx.zero_start || ctx.zero_end ) )
            if ((!e_success) && (ctx->zero_start || ctx->zero_end)) {
                double b_Ntot;
                //  ZN or NZ case :
                //  Optimization failed due with zero end constaints, decrease pseudo jerk
                // 'FeedratePlanning_LP:92' Ntot        = NWindow;
                b_Ntot = NWindow;
                // 'FeedratePlanning_LP:93' maxIter     = 15;
                // 'FeedratePlanning_LP:95' if( ~success && ctx.zero_start )
                if (ctx->zero_start) {
                    int t_loop_ub;
                    // 'FeedratePlanning_LP:96' Ntot        = Ntot + 1;
                    b_Ntot = NWindow + 1.0;
                    // 'FeedratePlanning_LP:97' indStart    = ctx.k0;
                    // 'FeedratePlanning_LP:98' [ctx, Coeff0, success, status, msg] =
                    // relax_intial_constraints( ... 'FeedratePlanning_LP:99'                 f, A,
                    // b, Aeq, beq, ctx, indStart, false, maxIter);
                    d_beqSlack.set_size(beqSlack.size(0));
                    t_loop_ub = beqSlack.size(0) - 1;
                    for (int i45{0}; i45 <= t_loop_ub; i45++) {
                        d_beqSlack[i45] = beqSlack[i45];
                    }
                    relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, d_beqSlack, ctx,
                                             ctx->k0, Coeff0, &d_success, &b_status, msg);
                }
                // 'FeedratePlanning_LP:102' if( ~success && ctx.zero_end )
                if ((!d_success) && ctx->zero_end) {
                    // 'FeedratePlanning_LP:103' Ntot        = Ntot + 1;
                    b_Ntot++;
                    // 'FeedratePlanning_LP:104' indEnd      = ctx.k0 + Ntot -1;
                    // 'FeedratePlanning_LP:105' [ctx, Coeff0, success, status, msg] =
                    // relax_intial_constraints( ... 'FeedratePlanning_LP:106'                 f, A,
                    // b, Aeq, beq, ctx, indEnd, true, maxIter);
                    b_relax_intial_constraints(
                        fSlack, ASlack, bSlack, AeqSlack, beqSlack, ctx,
                        static_cast<int>(std::round(static_cast<double>(ctx->k0) + b_Ntot)) - 1,
                        Coeff0, &d_success, &b_status, msg);
                }
            }
            //  Check the status of the optimization
            // 'FeedratePlanning_LP:111' Coeff = [];
            Coeff.set_size(0, 0);
            // 'FeedratePlanning_LP:112' if( success )
            if (d_success) {
                int s_loop_ub;
                int u_loop_ub;
                // 'FeedratePlanning_LP:113' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
                if (Coeff0.size(0) - 1 < 1) {
                    s_loop_ub = 0;
                } else {
                    s_loop_ub = Coeff0.size(0) - 1;
                }
                b_Coeff0.set_size(1, s_loop_ub);
                for (int i44{0}; i44 < s_loop_ub; i44++) {
                    b_Coeff0[i44] = Coeff0[i44];
                }
                BasisVal_idx_0 = BasisVal.size(1);
                Coeff.set_size(BasisVal.size(1), static_cast<int>(NWindow));
                u_loop_ub = static_cast<int>(NWindow);
                for (int i46{0}; i46 < u_loop_ub; i46++) {
                    for (int i47{0}; i47 < BasisVal_idx_0; i47++) {
                        Coeff[i47 + Coeff.size(0) * i46] = b_Coeff0[i47 + BasisVal_idx_0 * i46];
                    }
                }
                // 'FeedratePlanning_LP:115' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
            } else {
                // 'FeedratePlanning_LP:118' else
                // 'FeedratePlanning_LP:119' msg = optName + " failed...";
                msg->b_init();
            }
        }
        // 'FeedratePlanning_LP:64' if( ~success )
        if (d_success) {
            ::coder::array<double, 1U> d_Coeff;
            int c_calclen;
            // 'FeedratePlanning_LP:66' if( ~ctx.zero_start )
            if (!ctx->zero_start) {
                int b_inner;
                int b_nc;
                int c_inner;
                //  Compute the continuity equations
                // 'FeedratePlanning_LP:68' X           = continuity * Coeff( : , 1 );
                b_inner = continuity.size(1);
                b_nc = i7 - 1;
                C.set_size(2, i7);
                for (int c_j{0}; c_j <= b_nc; c_j++) {
                    C[2 * c_j] = 0.0;
                    C[2 * c_j + 1] = 0.0;
                    for (int b_k{0}; b_k < b_inner; b_k++) {
                        __m128d r6;
                        __m128d r9;
                        r6 = _mm_loadu_pd(&continuity[2 * b_k]);
                        r9 = _mm_loadu_pd(&C[2 * c_j]);
                        _mm_storeu_pd(
                            &C[2 * c_j],
                            _mm_add_pd(r9, _mm_mul_pd(r6, _mm_set1_pd(D[b_k + D.size(0) * c_j]))));
                    }
                }
                c_inner = C.size(1);
                X[0] = 0.0;
                X[1] = 0.0;
                for (int c_k{0}; c_k < c_inner; c_k++) {
                    __m128d r10;
                    __m128d r8;
                    r8 = _mm_loadu_pd(&C[2 * c_k]);
                    r10 = _mm_loadu_pd(&X[0]);
                    _mm_storeu_pd(&X[0], _mm_add_pd(r10, _mm_mul_pd(r8, _mm_set1_pd(Coeff[c_k]))));
                }
                // 'FeedratePlanning_LP:69' ctx.v_0     = sqrt( X( 1 ) );
                ctx->v_0 = std::sqrt(X[0]);
                // 'FeedratePlanning_LP:70' ctx.at_0    = X( 2 );
                ctx->at_0 = X[1];
            }
            // 'FeedratePlanning_LP:73' Coeff       = reshape( D * Coeff( : ), N, [] );
            b_Coeff = Coeff.size(0) * Coeff.size(1);
            d_Coeff = Coeff.reshape(b_Coeff);
            coder::internal::blas::mtimes(D, d_Coeff, r5);
            if (BasisVal.size(1) > 0) {
                c_calclen = r5.size(0) / BasisVal.size(1);
            } else {
                c_calclen = 0;
            }
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), c_calclen);
            for (int i32{0}; i32 < c_calclen; i32++) {
                for (int i33{0}; i33 < BasisVal_idx_0; i33++) {
                    Coeff[i33 + Coeff.size(0) * i32] = r5[i33 + BasisVal_idx_0 * i32];
                }
            }
            // 'FeedratePlanning_LP:75' ctx.Coeff   = Coeff;
            BasisVal_idx_0 = BasisVal.size(1);
            ctx->Coeff.set_size(BasisVal.size(1), c_calclen);
            for (int i34{0}; i34 < c_calclen; i34++) {
                for (int i35{0}; i35 < BasisVal_idx_0; i35++) {
                    ctx->Coeff[i35 + ctx->Coeff.size(0) * i34] = r5[i35 + BasisVal_idx_0 * i34];
                }
            }
        }
    }
    *success = d_success;
    *status = b_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_LP.cpp
//
// [EOF]
//
