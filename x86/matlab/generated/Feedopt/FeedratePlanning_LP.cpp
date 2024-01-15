
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
#include "ocn_assert.h"
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
static void add_slack(bool opt_FORCE_POSITIV_COEFFS, const ::coder::array<double, 2U> &f,
                      const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &b,
                      const ::coder::array<double, 2U> &Aeq,
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
// function [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( opt, ...
//     f, A, b, Aeq, beq, indSlack, LP )
//
// Arguments    : bool opt_FORCE_POSITIV_COEFFS
//                const ::coder::array<double, 2U> &f
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
static void add_slack(bool opt_FORCE_POSITIV_COEFFS, const ::coder::array<double, 2U> &f,
                      const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &b,
                      const ::coder::array<double, 2U> &Aeq,
                      const ::coder::array<double, 2U> &indSlack, double LP_SLACK_PENALTY,
                      ::coder::array<double, 1U> &fSlack, ::coder::array<double, 2U> &ASlack,
                      ::coder::array<double, 1U> &bSlack, ::coder::array<double, 2U> &AeqSlack)
{
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 1U> bpos;
    ::coder::array<int, 2U> r;
    ::coder::array<signed char, 2U> Apos;
    ::coder::array<signed char, 2U> b_I;
    ::coder::array<signed char, 2U> varargin_3;
    ::coder::array<signed char, 1U> vecSlack;
    int b_f;
    int b_input_sizes_idx_0;
    int c_input_sizes_idx_1;
    int c_result;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i17;
    int i_loop_ub;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int m_loop_ub;
    int result;
    int sizes_idx_1;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'FeedratePlanning_LP:148' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:150' if( opt.FORCE_POSITIV_COEFFS )
    if (opt_FORCE_POSITIV_COEFFS) {
        int c_loop_ub;
        int g_loop_ub;
        int i4;
        int loop_ub;
        int t;
        //  Add condition of positivity on coeffs expected for the 2 first ones and the 2 lasts ones
        // 'FeedratePlanning_LP:153' Apos = zeros( nAc-4 , nAc + 1 );
        Apos.set_size(A.size(1) - 4, A.size(1) + 1);
        loop_ub = A.size(1) + 1;
        for (int i{0}; i < loop_ub; i++) {
            int b_loop_ub;
            b_loop_ub = A.size(1) - 4;
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                Apos[i1 + Apos.size(0) * i] = 0;
            }
        }
        // 'FeedratePlanning_LP:153' bpos = -1e-4 * ones( nAc-4 , 1);
        bpos.set_size(A.size(1) - 4);
        c_loop_ub = A.size(1) - 4;
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            bpos[i2] = -0.0001;
        }
        // 'FeedratePlanning_LP:154' Apos( : , 3 : end -3   ) = -eye( nAc-4  );
        if (A.size(1) - 2 < 3) {
            i4 = 0;
        } else {
            i4 = 2;
        }
        if (A.size(1) - 4 < 0) {
            t = 0;
        } else {
            t = A.size(1) - 4;
        }
        b_I.set_size(t, t);
        for (int i7{0}; i7 < t; i7++) {
            for (int i8{0}; i8 < t; i8++) {
                b_I[i8 + b_I.size(0) * i7] = 0;
            }
        }
        if (t > 0) {
            for (int k{0}; k < t; k++) {
                b_I[k + b_I.size(0) * k] = 1;
            }
        }
        g_loop_ub = b_I.size(1);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            int h_loop_ub;
            h_loop_ub = b_I.size(0);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                Apos[i11 + Apos.size(0) * (i4 + i10)] =
                    static_cast<signed char>(-b_I[i11 + b_I.size(0) * i10]);
            }
        }
    } else {
        // 'FeedratePlanning_LP:155' else
        // 'FeedratePlanning_LP:156' Apos = [];
        Apos.set_size(0, 0);
        // 'FeedratePlanning_LP:157' bpos = [];
        bpos.set_size(0);
    }
    //  Slack variables
    // 'FeedratePlanning_LP:161' vecSlack    = zeros( nAL, 1 );
    vecSlack.set_size(A.size(0));
    d_loop_ub = A.size(0);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        vecSlack[i3] = 0;
    }
    // 'FeedratePlanning_LP:161' vecSlack( indSlack ) = -1;
    r.set_size(1, indSlack.size(1));
    e_loop_ub = indSlack.size(1);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        r[i5] = static_cast<int>(indSlack[i5]);
    }
    f_loop_ub = r.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        vecSlack[r[i6] - 1] = -1;
    }
    // 'FeedratePlanning_LP:162' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i9{0}; i9 < b_f; i9++) {
        fSlack[i9] = f[i9];
    }
    fSlack[b_f] = LP_SLACK_PENALTY;
    // 'FeedratePlanning_LP:163' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
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
    for (int i12{0}; i12 < input_sizes_idx_1; i12++) {
        for (int i13{0}; i13 < result; i13++) {
            b_result[i13 + b_result.size(0) * i12] = A[i13 + result * i12];
        }
    }
    i_loop_ub = b_input_sizes_idx_1;
    for (int i14{0}; i14 < i_loop_ub; i14++) {
        for (int i15{0}; i15 < result; i15++) {
            b_result[i15 + b_result.size(0) * input_sizes_idx_1] = vecSlack[i15];
        }
    }
    varargin_3.set_size(1, A.size(1) + 1);
    j_loop_ub = A.size(1);
    for (int i16{0}; i16 < j_loop_ub; i16++) {
        varargin_3[i16] = 0;
    }
    varargin_3[A.size(1)] = -1;
    if ((Apos.size(0) != 0) && (Apos.size(1) != 0)) {
        sizes_idx_1 = Apos.size(1);
    } else if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = varargin_3.size(1);
    }
    if ((Apos.size(0) != 0) && (Apos.size(1) != 0)) {
        input_sizes_idx_0 = Apos.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        b_input_sizes_idx_0 = b_result.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        i17 = b_result.size(0);
    } else {
        i17 = 0;
    }
    ASlack.set_size((input_sizes_idx_0 + i17) + 1, sizes_idx_1);
    for (int i18{0}; i18 < sizes_idx_1; i18++) {
        for (int i20{0}; i20 < input_sizes_idx_0; i20++) {
            ASlack[i20 + ASlack.size(0) * i18] = Apos[i20 + input_sizes_idx_0 * i18];
        }
    }
    for (int i19{0}; i19 < sizes_idx_1; i19++) {
        for (int i22{0}; i22 < b_input_sizes_idx_0; i22++) {
            ASlack[(i22 + input_sizes_idx_0) + ASlack.size(0) * i19] =
                b_result[i22 + b_input_sizes_idx_0 * i19];
        }
    }
    for (int i21{0}; i21 < sizes_idx_1; i21++) {
        ASlack[(input_sizes_idx_0 + b_input_sizes_idx_0) + ASlack.size(0) * i21] = varargin_3[i21];
    }
    // 'FeedratePlanning_LP:164' bSlack      = [ bpos; b ; 0 ];
    bSlack.set_size((bpos.size(0) + b.size(0)) + 1);
    k_loop_ub = bpos.size(0);
    for (int i23{0}; i23 < k_loop_ub; i23++) {
        bSlack[i23] = -0.0001;
    }
    l_loop_ub = b.size(0);
    for (int i24{0}; i24 < l_loop_ub; i24++) {
        bSlack[i24 + bpos.size(0)] = b[i24];
    }
    bSlack[bpos.size(0) + b.size(0)] = 0.0;
    // 'FeedratePlanning_LP:165' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    for (int i25{0}; i25 < c_input_sizes_idx_1; i25++) {
        for (int i26{0}; i26 < c_result; i26++) {
            AeqSlack[i26 + AeqSlack.size(0) * i25] = Aeq[i26 + c_result * i25];
        }
    }
    m_loop_ub = d_input_sizes_idx_1;
    for (int i27{0}; i27 < m_loop_ub; i27++) {
        for (int i28{0}; i28 < c_result; i28++) {
            AeqSlack[i28 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:166' beqSlack    = beq;
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
    // 'FeedratePlanning_LP:177' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:178' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:179' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:180' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:181' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:182' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:183' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:184' msg         = "";
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    // 'FeedratePlanning_LP:186' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        // 'FeedratePlanning_LP:187' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:171' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:172' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        b_calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                              ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                              ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                              ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, &b_vNorm,
                              &b_atNorm);
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:189' if(isEnd)
        // 'FeedratePlanning_LP:190' beq( end-1 )    = -vNorm^2;
        beq[beq.size(0) - 2] = -(b_vNorm * b_vNorm);
        // 'FeedratePlanning_LP:191' beq( end )      = atNorm;
        beq[beq.size(0) - 1] = b_atNorm;
        // 'FeedratePlanning_LP:197' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:198'         Aeq, beq, ctx );
        coder::b_sparse(A, &r);
        c_simplex(f, &r, b, Aeq, beq, Coeff0, &b_success, &b_status);
        msg->Value.size[0] = 1;
        msg->Value.size[1] = 0;
        // 'FeedratePlanning_LP:199' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:204' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:205' if(isEnd)
    // 'FeedratePlanning_LP:206' ctx.at_1    = -atNorm;
    ctx->at_1 = -atNorm;
    // 'FeedratePlanning_LP:207' ctx.v_1     = -vNorm;
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
    // 'FeedratePlanning_LP:177' success     = false;
    b_success = false;
    // 'FeedratePlanning_LP:178' count       = 0;
    count = 0;
    // 'FeedratePlanning_LP:179' curv        = ctx.q_split.get( indCurv );
    ctx->q_split.get(indCurv, &curv);
    // 'FeedratePlanning_LP:180' atNorm      = 0;
    atNorm = 0.0;
    // 'FeedratePlanning_LP:181' vNorm       = 0;
    vNorm = 0.0;
    // 'FeedratePlanning_LP:182' status      = int32( 0 );
    b_status = 0;
    // 'FeedratePlanning_LP:183' Coeff0      = zeros( size( f ) );
    Coeff0.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i{0}; i < loop_ub; i++) {
        Coeff0[i] = 0.0;
    }
    // 'FeedratePlanning_LP:184' msg         = "";
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    // 'FeedratePlanning_LP:186' while( ~success && count < maxIter )
    while ((!b_success) && (count < 15)) {
        // 'FeedratePlanning_LP:187' [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd
        // ); 'FeedratePlanning_LP:171' curv.ConstJerk = curv.ConstJerk / 8;
        curv.ConstJerk /= 8.0;
        // 'FeedratePlanning_LP:172' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, &b_vNorm,
                            &b_atNorm);
        vNorm = b_vNorm;
        atNorm = b_atNorm;
        // 'FeedratePlanning_LP:189' if(isEnd)
        // 'FeedratePlanning_LP:192' else
        // 'FeedratePlanning_LP:193' beq( 1 )        = vNorm^2;
        beq[0] = b_vNorm * b_vNorm;
        // 'FeedratePlanning_LP:194' beq( 2 )        = atNorm;
        beq[1] = b_atNorm;
        // 'FeedratePlanning_LP:197' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ),
        // b, ... 'FeedratePlanning_LP:198'         Aeq, beq, ctx );
        coder::b_sparse(A, &r);
        c_simplex(f, &r, b, Aeq, beq, Coeff0, &b_success, &b_status);
        msg->Value.size[0] = 1;
        msg->Value.size[1] = 0;
        // 'FeedratePlanning_LP:199' count = count + 1;
        count++;
    }
    //  Set back the change into the queue
    // 'FeedratePlanning_LP:204' ctx.q_split.set( indCurv, curv );
    ctx->q_split.set(indCurv, &curv);
    // 'FeedratePlanning_LP:205' if(isEnd)
    // 'FeedratePlanning_LP:208' else
    // 'FeedratePlanning_LP:209' ctx.at_0    = atNorm;
    ctx->at_0 = atNorm;
    // 'FeedratePlanning_LP:210' ctx.v_0     = vNorm;
    ctx->v_0 = vNorm;
    *success = b_success;
    *status = b_status;
}

//
// function [ ctx, Coeff, success, status, msg ] = ...
//     FeedratePlanning_LP( ctx, window, amax, jmax, BasisVal, ...
//     BasisValD, BasisValDD, BasisIntegr, u_vec, NWindow )
//
// FeedratePlanning_LP : Implement and solve the LP optimization scheme
//
//  Inputs :
//    ctx         : The context of the computational chain
//    window      : Window of curves
//    amax        : Acceleration maximum
//    jmax        : Jerk maximum
//    BasisVal    : BSpline evalueted on a set given points
//    BasisValD   : BSpline derivative evaluated on a set given points
//    BasisValDD  : BSpline second derivative evaluated on a set given points
//    BasisIntegr : BSpline integral evaluated on a set given points
//    u_vec       : Vector of u values
//    NWindow     : Number of curves in the window
//
//  Outputs :
//    ctx         : The context of the computational chain
//    Coeff       : Vector of coefficients
//    success     : Boolean value, TRUE means the optimization succeeded
//    status      : Status code return from the optimization
//    msg         : Msg returned from the optimization
//
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
    coder::sparse r5;
    coder::sparse r9;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> ASlack;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> AeqSlack;
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> D;
    ::coder::array<double, 2U> b_A;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_Aj;
    ::coder::array<double, 2U> b_Coeff0;
    ::coder::array<double, 2U> b_D;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 2U> lCurvs;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 1U> bSlack;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_beqSlack;
    ::coder::array<double, 1U> beqSlack;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> bpos;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> c_beqSlack;
    ::coder::array<double, 1U> c_f;
    ::coder::array<double, 1U> d_beqSlack;
    ::coder::array<double, 1U> e_Coeff;
    ::coder::array<double, 1U> fSlack;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> t;
    ::coder::array<unsigned int, 2U> y;
    ::coder::array<signed char, 2U> Apos;
    ::coder::array<signed char, 2U> b_I;
    ::coder::array<signed char, 2U> varargin_3;
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
    int g_loop_ub;
    int h_loop_ub;
    int i24;
    int inner;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int loop_ub;
    int nc;
    int nv;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int result;
    int s_loop_ub;
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
    //  0) Initialization of the problem
    //  M     : number of discretization
    //  N     : number of coefficients
    // 'FeedratePlanning_LP:31' [ M, N ]    = size( BasisVal );
    // 'FeedratePlanning_LP:32' LP          = ctx.cfg.opt;
    //  Load parameters of the LP
    // 'FeedratePlanning_LP:33' CurvArray   = window( 1 : NWindow );
    if (NWindow < 1.0) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(NWindow);
    }
    //  Extract window of interest
    //  1) Optimization : first LP
    // 'FeedratePlanning_LP:36' [ D, Dinv ] = compute_scaling_matrix( ctx, CurvArray, N );
    // 'FeedratePlanning_LP:216' N       = length( curvArray );
    // 'FeedratePlanning_LP:218' if( ctx.cfg.opt.USE_LENGTH_SCALING )
    if (ctx->cfg.opt.USE_LENGTH_SCALING) {
        int b_lCurvs;
        int i;
        // 'FeedratePlanning_LP:219' lCurvs  = zeros( NCoeff, N );
        lCurvs.set_size(BasisVal.size(1), loop_ub);
        // 'FeedratePlanning_LP:221' for ind = 1 : N
        i = loop_ub - 1;
        if (loop_ub - 1 >= 0) {
            b_loop_ub = BasisVal.size(1);
        }
        for (int ind{0}; ind <= i; ind++) {
            double b;
            // 'FeedratePlanning_LP:222' lCurvs( :, ind ) = ones( NCoeff, 1 ) * LengthCurv( ctx, ...
            // 'FeedratePlanning_LP:223'                 curvArray( ind ), 0, 1 );
            b = b_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                             ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                             ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                             ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                             ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &window[ind]);
            for (int i2{0}; i2 < b_loop_ub; i2++) {
                lCurvs[i2 + lCurvs.size(0) * ind] = b;
            }
        }
        // 'FeedratePlanning_LP:225' t       = lCurvs( : ).^2;
        b_lCurvs = lCurvs.size(0) * lCurvs.size(1);
        t.set_size(b_lCurvs);
        for (int i4{0}; i4 < b_lCurvs; i4++) {
            double varargin_1;
            varargin_1 = lCurvs[i4];
            t[i4] = std::pow(varargin_1, 2.0);
        }
    } else {
        int unnamed_idx_0;
        // 'FeedratePlanning_LP:226' else
        // 'FeedratePlanning_LP:227' t       = ones( N * NCoeff, 1  );
        unnamed_idx_0 =
            static_cast<int>(static_cast<double>(loop_ub) * static_cast<double>(BasisVal.size(1)));
        t.set_size(unnamed_idx_0);
        for (int i1{0}; i1 < unnamed_idx_0; i1++) {
            t[i1] = 1.0;
        }
    }
    // 'FeedratePlanning_LP:230' D       = diag( 1 ./ t );
    r.set_size(t.size(0));
    c_loop_ub = t.size(0);
    scalarLB = (t.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&t[i3]);
        _mm_storeu_pd(&r[i3], _mm_div_pd(_mm_set1_pd(1.0), r1));
    }
    for (int i3{scalarLB}; i3 < c_loop_ub; i3++) {
        r[i3] = 1.0 / t[i3];
    }
    nv = r.size(0);
    D.set_size(r.size(0), r.size(0));
    d_loop_ub = r.size(0);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        int e_loop_ub;
        e_loop_ub = r.size(0);
        for (int i6{0}; i6 < e_loop_ub; i6++) {
            D[i6 + D.size(0) * i5] = 0.0;
        }
    }
    for (int j{0}; j < nv; j++) {
        D[j + D.size(0) * j] = r[j];
    }
    // 'FeedratePlanning_LP:231' Dinv    = diag( t );
    // 'FeedratePlanning_LP:37' DCon        = D( [ 1 : N ], [ 1 : N ] );
    if (BasisVal.size(1) < 1) {
        f_loop_ub = 0;
        g_loop_ub = 0;
    } else {
        f_loop_ub = BasisVal.size(1);
        g_loop_ub = BasisVal.size(1);
    }
    //  A. Linear objectif
    // 'FeedratePlanning_LP:40' f = -repmat( BasisIntegr, 1, NWindow );
    coder::repmat(BasisIntegr, NWindow, r2);
    f.set_size(r2.size(0), r2.size(1));
    h_loop_ub = r2.size(1);
    for (int i7{0}; i7 < h_loop_ub; i7++) {
        int b_scalarLB;
        int b_vectorUB;
        int i_loop_ub;
        i_loop_ub = r2.size(0);
        b_scalarLB = (r2.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i8{0}; i8 <= b_vectorUB; i8 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r2[i8 + r2.size(0) * i7]);
            _mm_storeu_pd(&f[i8 + f.size(0) * i7], _mm_mul_pd(r3, _mm_set1_pd(-1.0)));
        }
        for (int i8{b_scalarLB}; i8 < i_loop_ub; i8++) {
            f[i8 + f.size(0) * i7] = -r2[i8 + r2.size(0) * i7];
        }
    }
    int b_f;
    // 'FeedratePlanning_LP:41' f = reshape( f( : )'  * D, [], NWindow );
    b_f = f.size(0) * f.size(1);
    c_f = f.reshape(b_f);
    inner = c_f.size(0);
    nc = D.size(1);
    r4.set_size(1, D.size(1));
    for (int b_j{0}; b_j < nc; b_j++) {
        r4[b_j] = 0.0;
        for (int k{0}; k < inner; k++) {
            r4[b_j] = r4[b_j] + c_f[k] * D[k + D.size(0) * b_j];
        }
    }
    if (static_cast<int>(NWindow) > 0) {
        calclen = r4.size(1) / static_cast<int>(NWindow);
    } else {
        calclen = 0;
    }
    //  B. Constraints : Inequality and Equality
    //  Feedrate and acceleration
    // 'FeedratePlanning_LP:45' [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax,
    // ctx.v_0, ... 'FeedratePlanning_LP:46'     ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD,
    // u_vec);
    b_window.set_size(1, loop_ub);
    for (int i9{0}; i9 < loop_ub; i9++) {
        b_window[i9] = window[i9];
    }
    b_ctx = ctx->kin;
    buildConstr(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS,
                ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS, &b_ctx, b_window, amax, ctx->v_0, ctx->at_0,
                ctx->v_1, ctx->at_1, BasisVal, BasisValD, u_vec, A, b_b, Aeq, beqSlack, continuity);
    // 'FeedratePlanning_LP:49' A           = A * D;
    coder::internal::blas::mtimes(A, D, b_A);
    // 'FeedratePlanning_LP:50' Aeq         = Aeq * D;
    coder::internal::blas::mtimes(Aeq, D, b_Aeq);
    // 'FeedratePlanning_LP:51' continuity  = continuity * DCon;
    // 'FeedratePlanning_LP:53' indSlack =  [];
    // 1 : numel( b );
    // 'FeedratePlanning_LP:55' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack(
    // ctx.cfg.opt, f, ... 'FeedratePlanning_LP:56'     A, b, Aeq, beq, indSlack, LP );
    // 'FeedratePlanning_LP:148' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:150' if( opt.FORCE_POSITIV_COEFFS )
    if (ctx->cfg.opt.FORCE_POSITIV_COEFFS) {
        int b_t;
        int i14;
        int j_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        //  Add condition of positivity on coeffs expected for the 2 first ones and the 2 lasts ones
        // 'FeedratePlanning_LP:153' Apos = zeros( nAc-4 , nAc + 1 );
        Apos.set_size(b_A.size(1) - 4, b_A.size(1) + 1);
        j_loop_ub = b_A.size(1) + 1;
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            int k_loop_ub;
            k_loop_ub = b_A.size(1) - 4;
            for (int i11{0}; i11 < k_loop_ub; i11++) {
                Apos[i11 + Apos.size(0) * i10] = 0;
            }
        }
        // 'FeedratePlanning_LP:153' bpos = -1e-4 * ones( nAc-4 , 1);
        bpos.set_size(b_A.size(1) - 4);
        l_loop_ub = b_A.size(1) - 4;
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            bpos[i12] = -0.0001;
        }
        // 'FeedratePlanning_LP:154' Apos( : , 3 : end -3   ) = -eye( nAc-4  );
        if (b_A.size(1) - 2 < 3) {
            i14 = 0;
        } else {
            i14 = 2;
        }
        if (b_A.size(1) - 4 < 0) {
            b_t = 0;
        } else {
            b_t = b_A.size(1) - 4;
        }
        b_I.set_size(b_t, b_t);
        for (int i15{0}; i15 < b_t; i15++) {
            for (int i16{0}; i16 < b_t; i16++) {
                b_I[i16 + b_I.size(0) * i15] = 0;
            }
        }
        if (b_t > 0) {
            for (int b_k{0}; b_k < b_t; b_k++) {
                b_I[b_k + b_I.size(0) * b_k] = 1;
            }
        }
        m_loop_ub = b_I.size(1);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            int n_loop_ub;
            n_loop_ub = b_I.size(0);
            for (int i19{0}; i19 < n_loop_ub; i19++) {
                Apos[i19 + Apos.size(0) * (i14 + i17)] =
                    static_cast<signed char>(-b_I[i19 + b_I.size(0) * i17]);
            }
        }
    } else {
        // 'FeedratePlanning_LP:155' else
        // 'FeedratePlanning_LP:156' Apos = [];
        Apos.set_size(0, 0);
        // 'FeedratePlanning_LP:157' bpos = [];
        bpos.set_size(0);
    }
    //  Slack variables
    // 'FeedratePlanning_LP:161' vecSlack    = zeros( nAL, 1 );
    // 'FeedratePlanning_LP:161' vecSlack( indSlack ) = -1;
    // 'FeedratePlanning_LP:162' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    calclen_idx_0 = calclen * static_cast<int>(NWindow);
    fSlack.set_size(calclen_idx_0 + 1);
    for (int i13{0}; i13 < calclen_idx_0; i13++) {
        fSlack[i13] = r4[i13];
    }
    fSlack[calclen_idx_0] = ctx->cfg.opt.SLACK_PENALTY;
    // 'FeedratePlanning_LP:163' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
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
    for (int i18{0}; i18 < input_sizes_idx_1; i18++) {
        for (int i20{0}; i20 < result; i20++) {
            b_result[i20 + b_result.size(0) * i18] = b_A[i20 + result * i18];
        }
    }
    o_loop_ub = b_input_sizes_idx_1;
    for (int i21{0}; i21 < o_loop_ub; i21++) {
        for (int i22{0}; i22 < result; i22++) {
            b_result[i22 + b_result.size(0) * input_sizes_idx_1] = 0.0;
        }
    }
    varargin_3.set_size(1, b_A.size(1) + 1);
    p_loop_ub = b_A.size(1);
    for (int i23{0}; i23 < p_loop_ub; i23++) {
        varargin_3[i23] = 0;
    }
    varargin_3[b_A.size(1)] = -1;
    if ((Apos.size(0) != 0) && (Apos.size(1) != 0)) {
        sizes_idx_1 = Apos.size(1);
    } else if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = varargin_3.size(1);
    }
    if ((Apos.size(0) != 0) && (Apos.size(1) != 0)) {
        input_sizes_idx_0 = Apos.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        b_input_sizes_idx_0 = b_result.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        i24 = b_result.size(0);
    } else {
        i24 = 0;
    }
    ASlack.set_size((input_sizes_idx_0 + i24) + 1, sizes_idx_1);
    for (int i25{0}; i25 < sizes_idx_1; i25++) {
        for (int i27{0}; i27 < input_sizes_idx_0; i27++) {
            ASlack[i27 + ASlack.size(0) * i25] = Apos[i27 + input_sizes_idx_0 * i25];
        }
    }
    for (int i26{0}; i26 < sizes_idx_1; i26++) {
        for (int i29{0}; i29 < b_input_sizes_idx_0; i29++) {
            ASlack[(i29 + input_sizes_idx_0) + ASlack.size(0) * i26] =
                b_result[i29 + b_input_sizes_idx_0 * i26];
        }
    }
    for (int i28{0}; i28 < sizes_idx_1; i28++) {
        ASlack[(input_sizes_idx_0 + b_input_sizes_idx_0) + ASlack.size(0) * i28] = varargin_3[i28];
    }
    // 'FeedratePlanning_LP:164' bSlack      = [ bpos; b ; 0 ];
    bSlack.set_size((bpos.size(0) + b_b.size(0)) + 1);
    q_loop_ub = bpos.size(0);
    for (int i30{0}; i30 < q_loop_ub; i30++) {
        bSlack[i30] = -0.0001;
    }
    r_loop_ub = b_b.size(0);
    for (int i31{0}; i31 < r_loop_ub; i31++) {
        bSlack[i31 + bpos.size(0)] = b_b[i31];
    }
    bSlack[bpos.size(0) + b_b.size(0)] = 0.0;
    // 'FeedratePlanning_LP:165' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    for (int i32{0}; i32 < c_input_sizes_idx_1; i32++) {
        for (int i33{0}; i33 < c_result; i33++) {
            AeqSlack[i33 + AeqSlack.size(0) * i32] = b_Aeq[i33 + c_result * i32];
        }
    }
    s_loop_ub = d_input_sizes_idx_1;
    for (int i34{0}; i34 < s_loop_ub; i34++) {
        for (int i35{0}; i35 < c_result; i35++) {
            AeqSlack[i35 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:166' beqSlack    = beq;
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:60' [ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack,
    // ASlack, bSlack, ... 'FeedratePlanning_LP:61'     AeqSlack, beqSlack, ctx, N, NWindow, "First
    // LP" );
    //  Call the solver
    // -------------------------------------------------------------------------
    //  Functions
    // -------------------------------------------------------------------------
    // 'FeedratePlanning_LP:108' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, ... 'FeedratePlanning_LP:109'     beq, ctx );
    coder::b_sparse(ASlack, &r5);
    c_simplex(fSlack, &r5, bSlack, AeqSlack, beqSlack, Coeff0, &b_success, &b_status);
    msg->Value.size[0] = 1;
    msg->Value.size[1] = 0;
    c_success = b_success;
    // 'FeedratePlanning_LP:111' if( ~success && ( ctx.zero_start || ctx.zero_end ) )
    if ((!b_success) && (ctx->zero_start || ctx->zero_end)) {
        double Ntot;
        //  ZN or NZ case :
        //  Optimization failed due with zero end constaints, decrease pseudo jerk
        // 'FeedratePlanning_LP:114' Ntot        = NWindow;
        Ntot = NWindow;
        // 'FeedratePlanning_LP:115' maxIter     = 15;
        // 'FeedratePlanning_LP:117' if( ~success && ctx.zero_start )
        if (ctx->zero_start) {
            int u_loop_ub;
            // 'FeedratePlanning_LP:118' Ntot        = Ntot + 1;
            Ntot = NWindow + 1.0;
            // 'FeedratePlanning_LP:119' indStart    = ctx.k0;
            // 'FeedratePlanning_LP:120' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:121'                 f, A, b, Aeq,
            // beq, ctx, indStart, false, maxIter);
            b_beqSlack.set_size(beqSlack.size(0));
            u_loop_ub = beqSlack.size(0) - 1;
            for (int i37{0}; i37 <= u_loop_ub; i37++) {
                b_beqSlack[i37] = beqSlack[i37];
            }
            relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, b_beqSlack, ctx, ctx->k0,
                                     Coeff0, &c_success, &b_status, msg);
        }
        // 'FeedratePlanning_LP:124' if( ~success && ctx.zero_end )
        if ((!c_success) && ctx->zero_end) {
            int w_loop_ub;
            // 'FeedratePlanning_LP:125' Ntot        = Ntot + 1;
            Ntot++;
            // 'FeedratePlanning_LP:126' indEnd      = ctx.k0 + Ntot -1;
            // 'FeedratePlanning_LP:127' [ctx, Coeff0, success, status, msg] =
            // relax_intial_constraints( ... 'FeedratePlanning_LP:128'                 f, A, b, Aeq,
            // beq, ctx, indEnd, true, maxIter);
            c_beqSlack.set_size(beqSlack.size(0));
            w_loop_ub = beqSlack.size(0) - 1;
            for (int i39{0}; i39 <= w_loop_ub; i39++) {
                c_beqSlack[i39] = beqSlack[i39];
            }
            b_relax_intial_constraints(
                fSlack, ASlack, bSlack, AeqSlack, c_beqSlack, ctx,
                static_cast<int>(std::round(static_cast<double>(ctx->k0) + Ntot)) - 1, Coeff0,
                &c_success, &b_status, msg);
        }
    }
    //  Check the status of the optimization
    // 'FeedratePlanning_LP:133' Coeff = [];
    Coeff.set_size(0, 0);
    // 'FeedratePlanning_LP:134' if( success )
    if (c_success) {
        int t_loop_ub;
        int v_loop_ub;
        // 'FeedratePlanning_LP:135' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (Coeff0.size(0) - 1 < 1) {
            t_loop_ub = 0;
        } else {
            t_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, t_loop_ub);
        for (int i36{0}; i36 < t_loop_ub; i36++) {
            b_Coeff0[i36] = Coeff0[i36];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), static_cast<int>(NWindow));
        v_loop_ub = static_cast<int>(NWindow);
        for (int i38{0}; i38 < v_loop_ub; i38++) {
            for (int i40{0}; i40 < BasisVal_idx_0; i40++) {
                Coeff[i40 + Coeff.size(0) * i38] = b_Coeff0[i40 + BasisVal_idx_0 * i38];
            }
        }
        // 'FeedratePlanning_LP:137' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
    } else {
        // 'FeedratePlanning_LP:140' else
        // 'FeedratePlanning_LP:141' msg = optName + " failed...";
        msg->init();
    }
    d_success = c_success;
    // 'FeedratePlanning_LP:63' if( ~success )
    if (c_success) {
        int b_Coeff;
        //  2) Optimization : second LP with jerk constraints and slack
        // 'FeedratePlanning_LP:67' if( ctx.cfg.opt.USE_JERK_CONSTRAINTS )
        if (ctx->cfg.opt.USE_JERK_CONSTRAINTS) {
            ::coder::array<double, 1U> c_Coeff;
            int ab_loop_ub;
            int b_calclen;
            int bb_loop_ub;
            int c_input_sizes_idx_0;
            int calclen_idx_1;
            int cb_loop_ub;
            int d_input_sizes_idx_0;
            int d_result;
            int unnamed_idx_1;
            bool c_empty_non_axis_sizes;
            // 'FeedratePlanning_LP:68' Coeff       = reshape( D * Coeff( : ), N, [] );
            b_Coeff = Coeff.size(0) * Coeff.size(1);
            c_Coeff = Coeff.reshape(b_Coeff);
            coder::internal::blas::mtimes(D, c_Coeff, r);
            //  B. Constraints : Inequality and Equality
            //  Feedrate, acceleration and jerk
            // 'FeedratePlanning_LP:71' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax,
            // ... 'FeedratePlanning_LP:72'         BasisVal, BasisValD, BasisValDD, u_vec );
            if (BasisVal.size(1) > 0) {
                b_calclen = r.size(0) / BasisVal.size(1);
            } else {
                b_calclen = 0;
            }
            BasisVal_idx_0 = BasisVal.size(1);
            b_window.set_size(1, loop_ub);
            for (int i44{0}; i44 < loop_ub; i44++) {
                b_window[i44] = window[i44];
            }
            ::coder::array<double, 2U> r7;
            c_ctx = ctx->kin;
            r7 = r.reshape(BasisVal_idx_0, b_calclen);
            buildConstrJerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &c_ctx, b_window,
                            r7, jmax, BasisVal, BasisValD, BasisValDD, u_vec, Aj, bj);
            // 'FeedratePlanning_LP:74' Aj   = Aj * D;
            coder::internal::blas::mtimes(Aj, D, b_Aj);
            // 'FeedratePlanning_LP:75' Atot = [ A; Aj ];
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
            // 'FeedratePlanning_LP:75' btot = [ b; bj ];
            // 'FeedratePlanning_LP:77' indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];
            if (bj.size(0) < 1) {
                y.set_size(1, 0);
            } else {
                int y_loop_ub;
                y.set_size(1, bj.size(0));
                y_loop_ub = bj.size(0) - 1;
                for (int i49{0}; i49 <= y_loop_ub; i49++) {
                    y[i49] = i49 + 1U;
                }
            }
            varargin_2.set_size(1, y.size(1));
            ab_loop_ub = y.size(1);
            for (int i50{0}; i50 < ab_loop_ub; i50++) {
                varargin_2[i50] = y[i50] + b_b.size(0);
            }
            // 'FeedratePlanning_LP:79' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack(
            // ctx.cfg.opt, ... 'FeedratePlanning_LP:80'         f, Atot, btot, Aeq, beq, indSlack,
            // LP );
            calclen_idx_1 = static_cast<int>(NWindow);
            if (varargin_2.size(1) != 0) {
                unnamed_idx_1 = varargin_2.size(1);
            } else {
                unnamed_idx_1 = 0;
            }
            A.set_size(c_input_sizes_idx_0 + d_input_sizes_idx_0, d_result);
            for (int i51{0}; i51 < d_result; i51++) {
                for (int i53{0}; i53 < c_input_sizes_idx_0; i53++) {
                    A[i53 + A.size(0) * i51] = b_A[i53 + c_input_sizes_idx_0 * i51];
                }
            }
            for (int i52{0}; i52 < d_result; i52++) {
                for (int i54{0}; i54 < d_input_sizes_idx_0; i54++) {
                    A[(i54 + c_input_sizes_idx_0) + A.size(0) * i52] =
                        b_Aj[i54 + d_input_sizes_idx_0 * i52];
                }
            }
            c_b.set_size(b_b.size(0) + bj.size(0));
            bb_loop_ub = b_b.size(0);
            for (int i55{0}; i55 < bb_loop_ub; i55++) {
                c_b[i55] = b_b[i55];
            }
            cb_loop_ub = bj.size(0);
            for (int i56{0}; i56 < cb_loop_ub; i56++) {
                c_b[i56 + b_b.size(0)] = bj[i56];
            }
            ::coder::array<double, 2U> b_varargin_2;
            ::coder::array<double, 2U> r8;
            r8 = r4.reshape(calclen, calclen_idx_1);
            b_varargin_2 = varargin_2.reshape(1, unnamed_idx_1);
            add_slack(ctx->cfg.opt.FORCE_POSITIV_COEFFS, r8, A, c_b, b_Aeq, b_varargin_2,
                      ctx->cfg.opt.SLACK_PENALTY, fSlack, ASlack, bSlack, AeqSlack);
            // 'FeedratePlanning_LP:82' [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack,
            // ASlack, bSlack, ... 'FeedratePlanning_LP:83'         AeqSlack, beqSlack, ctx, N,
            // NWindow, "Second LP" );
            //  Call the solver
            // -------------------------------------------------------------------------
            //  Functions
            // -------------------------------------------------------------------------
            // 'FeedratePlanning_LP:108' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A
            // ), b, Aeq, ... 'FeedratePlanning_LP:109'     beq, ctx );
            coder::b_sparse(ASlack, &r9);
            c_simplex(fSlack, &r9, bSlack, AeqSlack, beqSlack, Coeff0, &e_success, &b_status);
            msg->Value.size[0] = 1;
            msg->Value.size[1] = 0;
            d_success = e_success;
            // 'FeedratePlanning_LP:111' if( ~success && ( ctx.zero_start || ctx.zero_end ) )
            if ((!e_success) && (ctx->zero_start || ctx->zero_end)) {
                double b_Ntot;
                //  ZN or NZ case :
                //  Optimization failed due with zero end constaints, decrease pseudo jerk
                // 'FeedratePlanning_LP:114' Ntot        = NWindow;
                b_Ntot = NWindow;
                // 'FeedratePlanning_LP:115' maxIter     = 15;
                // 'FeedratePlanning_LP:117' if( ~success && ctx.zero_start )
                if (ctx->zero_start) {
                    int eb_loop_ub;
                    // 'FeedratePlanning_LP:118' Ntot        = Ntot + 1;
                    b_Ntot = NWindow + 1.0;
                    // 'FeedratePlanning_LP:119' indStart    = ctx.k0;
                    // 'FeedratePlanning_LP:120' [ctx, Coeff0, success, status, msg] =
                    // relax_intial_constraints( ... 'FeedratePlanning_LP:121'                 f, A,
                    // b, Aeq, beq, ctx, indStart, false, maxIter);
                    d_beqSlack.set_size(beqSlack.size(0));
                    eb_loop_ub = beqSlack.size(0) - 1;
                    for (int i58{0}; i58 <= eb_loop_ub; i58++) {
                        d_beqSlack[i58] = beqSlack[i58];
                    }
                    relax_intial_constraints(fSlack, ASlack, bSlack, AeqSlack, d_beqSlack, ctx,
                                             ctx->k0, Coeff0, &d_success, &b_status, msg);
                }
                // 'FeedratePlanning_LP:124' if( ~success && ctx.zero_end )
                if ((!d_success) && ctx->zero_end) {
                    // 'FeedratePlanning_LP:125' Ntot        = Ntot + 1;
                    b_Ntot++;
                    // 'FeedratePlanning_LP:126' indEnd      = ctx.k0 + Ntot -1;
                    // 'FeedratePlanning_LP:127' [ctx, Coeff0, success, status, msg] =
                    // relax_intial_constraints( ... 'FeedratePlanning_LP:128'                 f, A,
                    // b, Aeq, beq, ctx, indEnd, true, maxIter);
                    b_relax_intial_constraints(
                        fSlack, ASlack, bSlack, AeqSlack, beqSlack, ctx,
                        static_cast<int>(std::round(static_cast<double>(ctx->k0) + b_Ntot)) - 1,
                        Coeff0, &d_success, &b_status, msg);
                }
            }
            //  Check the status of the optimization
            // 'FeedratePlanning_LP:133' Coeff = [];
            Coeff.set_size(0, 0);
            // 'FeedratePlanning_LP:134' if( success )
            if (d_success) {
                int db_loop_ub;
                int fb_loop_ub;
                // 'FeedratePlanning_LP:135' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
                if (Coeff0.size(0) - 1 < 1) {
                    db_loop_ub = 0;
                } else {
                    db_loop_ub = Coeff0.size(0) - 1;
                }
                b_Coeff0.set_size(1, db_loop_ub);
                for (int i57{0}; i57 < db_loop_ub; i57++) {
                    b_Coeff0[i57] = Coeff0[i57];
                }
                BasisVal_idx_0 = BasisVal.size(1);
                Coeff.set_size(BasisVal.size(1), static_cast<int>(NWindow));
                fb_loop_ub = static_cast<int>(NWindow);
                for (int i59{0}; i59 < fb_loop_ub; i59++) {
                    for (int i60{0}; i60 < BasisVal_idx_0; i60++) {
                        Coeff[i60 + Coeff.size(0) * i59] = b_Coeff0[i60 + BasisVal_idx_0 * i59];
                    }
                }
                // 'FeedratePlanning_LP:137' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
            } else {
                // 'FeedratePlanning_LP:140' else
                // 'FeedratePlanning_LP:141' msg = optName + " failed...";
                msg->b_init();
            }
        }
        // 'FeedratePlanning_LP:86' if( ~success )
        if (d_success) {
            ::coder::array<double, 1U> d_Coeff;
            int c_calclen;
            // 'FeedratePlanning_LP:88' if( ~ctx.zero_start )
            if (!ctx->zero_start) {
                int x_loop_ub;
                //  Compute the continuity equations
                // 'FeedratePlanning_LP:90' X           = continuity * Coeff( : , 1 );
                b_D.set_size(f_loop_ub, g_loop_ub);
                for (int i41{0}; i41 < g_loop_ub; i41++) {
                    for (int i42{0}; i42 < f_loop_ub; i42++) {
                        b_D[i42 + b_D.size(0) * i41] = D[i42 + D.size(0) * i41];
                    }
                }
                x_loop_ub = Coeff.size(0);
                e_Coeff.set_size(Coeff.size(0));
                for (int i43{0}; i43 < x_loop_ub; i43++) {
                    e_Coeff[i43] = Coeff[i43];
                }
                double X[2];
                coder::internal::blas::b_mtimes(continuity, b_D, r6);
                coder::internal::blas::mtimes(r6, e_Coeff, X);
                // 'FeedratePlanning_LP:91' ctx.v_0     = mysqrt( X( 1 ) );
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
                ctx->v_0 = std::sqrt(X[0]);
                // 'FeedratePlanning_LP:92' ctx.at_0    = X( 2 );
                ctx->at_0 = X[1];
            }
            // 'FeedratePlanning_LP:95' Coeff       = reshape( D * Coeff( : ), N, [] );
            b_Coeff = Coeff.size(0) * Coeff.size(1);
            d_Coeff = Coeff.reshape(b_Coeff);
            coder::internal::blas::mtimes(D, d_Coeff, r);
            if (BasisVal.size(1) > 0) {
                c_calclen = r.size(0) / BasisVal.size(1);
            } else {
                c_calclen = 0;
            }
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), c_calclen);
            for (int i45{0}; i45 < c_calclen; i45++) {
                for (int i46{0}; i46 < BasisVal_idx_0; i46++) {
                    Coeff[i46 + Coeff.size(0) * i45] = r[i46 + BasisVal_idx_0 * i45];
                }
            }
            // 'FeedratePlanning_LP:97' ctx.Coeff   = Coeff;
            BasisVal_idx_0 = BasisVal.size(1);
            ctx->Coeff.set_size(BasisVal.size(1), c_calclen);
            for (int i47{0}; i47 < c_calclen; i47++) {
                for (int i48{0}; i48 < BasisVal_idx_0; i48++) {
                    ctx->Coeff[i48 + ctx->Coeff.size(0) * i47] = r[i48 + BasisVal_idx_0 * i47];
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
