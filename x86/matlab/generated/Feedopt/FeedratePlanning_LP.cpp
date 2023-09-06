//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
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
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void add_slack(const ::coder::array<double, 2U> &f, const ::coder::array<double, 2U> &A,
                      const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                      double LP_SLACK_PENALTY, ::coder::array<double, 1U> &fSlack,
                      ::coder::array<double, 2U> &ASlack, ::coder::array<double, 1U> &bSlack,
                      ::coder::array<double, 2U> &AeqSlack);

static void add_slack(const ::coder::array<double, 2U> &f, const ::coder::array<double, 2U> &A,
                      const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                      const ::coder::array<double, 2U> &indSlack, double LP_SLACK_PENALTY,
                      ::coder::array<double, 1U> &fSlack, ::coder::array<double, 2U> &ASlack,
                      ::coder::array<double, 1U> &bSlack, ::coder::array<double, 2U> &AeqSlack);

static void decrease_constjerk(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                               const int ctx_cfg_maskTot_size[2],
                               const bool ctx_cfg_maskCart_data[],
                               const int ctx_cfg_maskCart_size[2],
                               const bool ctx_cfg_maskRot_data[], const int ctx_cfg_maskRot_size[2],
                               const ::coder::array<int, 1U> &ctx_cfg_indCart,
                               const ::coder::array<int, 1U> &ctx_cfg_indRot,
                               int ctx_cfg_NumberAxis, int ctx_cfg_NCart, int ctx_cfg_NRot,
                               CurvStruct *curv, double *vNorm, double *atNorm);

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
                      double LP_SLACK_PENALTY, ::coder::array<double, 1U> &fSlack,
                      ::coder::array<double, 2U> &ASlack, ::coder::array<double, 1U> &bSlack,
                      ::coder::array<double, 2U> &AeqSlack)
{
    ::coder::array<double, 2U> b_result;
    ::coder::array<signed char, 2U> Apos;
    ::coder::array<signed char, 2U> b_I;
    ::coder::array<signed char, 2U> varargin_3;
    int b_f;
    int b_input_sizes_idx_0;
    int c_input_sizes_idx_1;
    int c_loop_ub;
    int c_result;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i13;
    int i2;
    int i_loop_ub;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int loop_ub;
    int result;
    int sizes_idx_1;
    int t;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'FeedratePlanning_LP:134' [ nAL, nAc ] = size( A );
    //  Add condition of positivity on coeffs the 2 first and the two last are
    //  nto
    // 'FeedratePlanning_LP:138' Apos = zeros( nAc -4 , nAc + 1 );
    Apos.set_size(A.size(1) - 4, A.size(1) + 1);
    loop_ub = A.size(1) + 1;
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = A.size(1) - 4;
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            Apos[i1 + Apos.size(0) * i] = 0;
        }
    }
    // 'FeedratePlanning_LP:138' bpos = -1E-3 * ones( nAc -4 , 1);
    // 'FeedratePlanning_LP:139' Apos( : , 3 : end-3  ) = -eye( nAc -4  );
    if (A.size(1) - 2 < 3) {
        i2 = 0;
    } else {
        i2 = 2;
    }
    if (A.size(1) - 4 < 0) {
        t = 0;
    } else {
        t = A.size(1) - 4;
    }
    b_I.set_size(t, t);
    for (int i3{0}; i3 < t; i3++) {
        for (int i4{0}; i4 < t; i4++) {
            b_I[i4 + b_I.size(0) * i3] = 0;
        }
    }
    if (t > 0) {
        for (int k{0}; k < t; k++) {
            b_I[k + b_I.size(0) * k] = 1;
        }
    }
    c_loop_ub = b_I.size(1);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        int d_loop_ub;
        d_loop_ub = b_I.size(0);
        for (int i6{0}; i6 < d_loop_ub; i6++) {
            Apos[i6 + Apos.size(0) * (i2 + i5)] =
                static_cast<signed char>(-b_I[i6 + b_I.size(0) * i5]);
        }
    }
    //  Slack variables
    // 'FeedratePlanning_LP:142' vecSlack    = zeros( nAL, 1 );
    // 'FeedratePlanning_LP:142' vecSlack( indSlack ) = -1;
    // 'FeedratePlanning_LP:143' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i7{0}; i7 < b_f; i7++) {
        fSlack[i7] = f[i7];
    }
    fSlack[b_f] = LP_SLACK_PENALTY;
    // 'FeedratePlanning_LP:144' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
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
    for (int i8{0}; i8 < input_sizes_idx_1; i8++) {
        for (int i9{0}; i9 < result; i9++) {
            b_result[i9 + b_result.size(0) * i8] = A[i9 + result * i8];
        }
    }
    e_loop_ub = b_input_sizes_idx_1;
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        for (int i11{0}; i11 < result; i11++) {
            b_result[i11 + b_result.size(0) * input_sizes_idx_1] = 0.0;
        }
    }
    varargin_3.set_size(1, A.size(1) + 1);
    f_loop_ub = A.size(1);
    for (int i12{0}; i12 < f_loop_ub; i12++) {
        varargin_3[i12] = 0;
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
        i13 = b_result.size(0);
    } else {
        i13 = 0;
    }
    ASlack.set_size((input_sizes_idx_0 + i13) + 1, sizes_idx_1);
    for (int i14{0}; i14 < sizes_idx_1; i14++) {
        for (int i16{0}; i16 < input_sizes_idx_0; i16++) {
            ASlack[i16 + ASlack.size(0) * i14] = Apos[i16 + input_sizes_idx_0 * i14];
        }
    }
    for (int i15{0}; i15 < sizes_idx_1; i15++) {
        for (int i18{0}; i18 < b_input_sizes_idx_0; i18++) {
            ASlack[(i18 + input_sizes_idx_0) + ASlack.size(0) * i15] =
                b_result[i18 + b_input_sizes_idx_0 * i15];
        }
    }
    for (int i17{0}; i17 < sizes_idx_1; i17++) {
        ASlack[(input_sizes_idx_0 + b_input_sizes_idx_0) + ASlack.size(0) * i17] = varargin_3[i17];
    }
    // 'FeedratePlanning_LP:145' bSlack      = [ bpos; b ; 0 ];
    bSlack.set_size((b.size(0) + A.size(1)) - 3);
    g_loop_ub = A.size(1) - 4;
    for (int i19{0}; i19 < g_loop_ub; i19++) {
        bSlack[i19] = -0.001;
    }
    h_loop_ub = b.size(0);
    for (int i20{0}; i20 < h_loop_ub; i20++) {
        bSlack[(i20 + A.size(1)) - 4] = b[i20];
    }
    bSlack[(b.size(0) + A.size(1)) - 4] = 0.0;
    // 'FeedratePlanning_LP:146' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    for (int i21{0}; i21 < c_input_sizes_idx_1; i21++) {
        for (int i22{0}; i22 < c_result; i22++) {
            AeqSlack[i22 + AeqSlack.size(0) * i21] = Aeq[i22 + c_result * i21];
        }
    }
    i_loop_ub = d_input_sizes_idx_1;
    for (int i23{0}; i23 < i_loop_ub; i23++) {
        for (int i24{0}; i24 < c_result; i24++) {
            AeqSlack[i24 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:147' beqSlack    = beq;
}

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
static void add_slack(const ::coder::array<double, 2U> &f, const ::coder::array<double, 2U> &A,
                      const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
                      const ::coder::array<double, 2U> &indSlack, double LP_SLACK_PENALTY,
                      ::coder::array<double, 1U> &fSlack, ::coder::array<double, 2U> &ASlack,
                      ::coder::array<double, 1U> &bSlack, ::coder::array<double, 2U> &AeqSlack)
{
    ::coder::array<double, 2U> b_result;
    ::coder::array<int, 2U> r;
    ::coder::array<signed char, 2U> Apos;
    ::coder::array<signed char, 2U> b_I;
    ::coder::array<signed char, 2U> varargin_3;
    ::coder::array<signed char, 1U> vecSlack;
    int b_f;
    int b_input_sizes_idx_0;
    int c_input_sizes_idx_1;
    int c_loop_ub;
    int c_result;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i16;
    int i2;
    int i_loop_ub;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int result;
    int sizes_idx_1;
    int t;
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'FeedratePlanning_LP:134' [ nAL, nAc ] = size( A );
    //  Add condition of positivity on coeffs the 2 first and the two last are
    //  nto
    // 'FeedratePlanning_LP:138' Apos = zeros( nAc -4 , nAc + 1 );
    Apos.set_size(A.size(1) - 4, A.size(1) + 1);
    loop_ub = A.size(1) + 1;
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = A.size(1) - 4;
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            Apos[i1 + Apos.size(0) * i] = 0;
        }
    }
    // 'FeedratePlanning_LP:138' bpos = -1E-3 * ones( nAc -4 , 1);
    // 'FeedratePlanning_LP:139' Apos( : , 3 : end-3  ) = -eye( nAc -4  );
    if (A.size(1) - 2 < 3) {
        i2 = 0;
    } else {
        i2 = 2;
    }
    if (A.size(1) - 4 < 0) {
        t = 0;
    } else {
        t = A.size(1) - 4;
    }
    b_I.set_size(t, t);
    for (int i3{0}; i3 < t; i3++) {
        for (int i4{0}; i4 < t; i4++) {
            b_I[i4 + b_I.size(0) * i3] = 0;
        }
    }
    if (t > 0) {
        for (int k{0}; k < t; k++) {
            b_I[k + b_I.size(0) * k] = 1;
        }
    }
    c_loop_ub = b_I.size(1);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        int d_loop_ub;
        d_loop_ub = b_I.size(0);
        for (int i6{0}; i6 < d_loop_ub; i6++) {
            Apos[i6 + Apos.size(0) * (i2 + i5)] =
                static_cast<signed char>(-b_I[i6 + b_I.size(0) * i5]);
        }
    }
    //  Slack variables
    // 'FeedratePlanning_LP:142' vecSlack    = zeros( nAL, 1 );
    vecSlack.set_size(A.size(0));
    e_loop_ub = A.size(0);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        vecSlack[i7] = 0;
    }
    // 'FeedratePlanning_LP:142' vecSlack( indSlack ) = -1;
    r.set_size(1, indSlack.size(1));
    f_loop_ub = indSlack.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        r[i8] = static_cast<int>(indSlack[i8]);
    }
    g_loop_ub = r.size(1);
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        vecSlack[r[i9] - 1] = -1;
    }
    // 'FeedratePlanning_LP:143' fSlack      = [ f( : ); LP.SLACK_PENALTY ];
    b_f = f.size(0) * f.size(1);
    fSlack.set_size(b_f + 1);
    for (int i10{0}; i10 < b_f; i10++) {
        fSlack[i10] = f[i10];
    }
    fSlack[b_f] = LP_SLACK_PENALTY;
    // 'FeedratePlanning_LP:144' ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
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
    for (int i11{0}; i11 < input_sizes_idx_1; i11++) {
        for (int i12{0}; i12 < result; i12++) {
            b_result[i12 + b_result.size(0) * i11] = A[i12 + result * i11];
        }
    }
    h_loop_ub = b_input_sizes_idx_1;
    for (int i13{0}; i13 < h_loop_ub; i13++) {
        for (int i14{0}; i14 < result; i14++) {
            b_result[i14 + b_result.size(0) * input_sizes_idx_1] = vecSlack[i14];
        }
    }
    varargin_3.set_size(1, A.size(1) + 1);
    i_loop_ub = A.size(1);
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        varargin_3[i15] = 0;
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
        i16 = b_result.size(0);
    } else {
        i16 = 0;
    }
    ASlack.set_size((input_sizes_idx_0 + i16) + 1, sizes_idx_1);
    for (int i17{0}; i17 < sizes_idx_1; i17++) {
        for (int i19{0}; i19 < input_sizes_idx_0; i19++) {
            ASlack[i19 + ASlack.size(0) * i17] = Apos[i19 + input_sizes_idx_0 * i17];
        }
    }
    for (int i18{0}; i18 < sizes_idx_1; i18++) {
        for (int i21{0}; i21 < b_input_sizes_idx_0; i21++) {
            ASlack[(i21 + input_sizes_idx_0) + ASlack.size(0) * i18] =
                b_result[i21 + b_input_sizes_idx_0 * i18];
        }
    }
    for (int i20{0}; i20 < sizes_idx_1; i20++) {
        ASlack[(input_sizes_idx_0 + b_input_sizes_idx_0) + ASlack.size(0) * i20] = varargin_3[i20];
    }
    // 'FeedratePlanning_LP:145' bSlack      = [ bpos; b ; 0 ];
    bSlack.set_size((b.size(0) + A.size(1)) - 3);
    j_loop_ub = A.size(1) - 4;
    for (int i22{0}; i22 < j_loop_ub; i22++) {
        bSlack[i22] = -0.001;
    }
    k_loop_ub = b.size(0);
    for (int i23{0}; i23 < k_loop_ub; i23++) {
        bSlack[(i23 + A.size(1)) - 4] = b[i23];
    }
    bSlack[(b.size(0) + A.size(1)) - 4] = 0.0;
    // 'FeedratePlanning_LP:146' AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    for (int i24{0}; i24 < c_input_sizes_idx_1; i24++) {
        for (int i25{0}; i25 < c_result; i25++) {
            AeqSlack[i25 + AeqSlack.size(0) * i24] = Aeq[i25 + c_result * i24];
        }
    }
    l_loop_ub = d_input_sizes_idx_1;
    for (int i26{0}; i26 < l_loop_ub; i26++) {
        for (int i27{0}; i27 < c_result; i27++) {
            AeqSlack[i27 + AeqSlack.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    // 'FeedratePlanning_LP:147' beqSlack    = beq;
}

//
// function [ curv, vNorm, atNorm ] = decrease_constjerk( ctx, curv, isEnd )
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
//                CurvStruct *curv
//                double *vNorm
//                double *atNorm
// Return Type  : void
//
static void decrease_constjerk(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                               const int ctx_cfg_maskTot_size[2],
                               const bool ctx_cfg_maskCart_data[],
                               const int ctx_cfg_maskCart_size[2],
                               const bool ctx_cfg_maskRot_data[], const int ctx_cfg_maskRot_size[2],
                               const ::coder::array<int, 1U> &ctx_cfg_indCart,
                               const ::coder::array<int, 1U> &ctx_cfg_indRot,
                               int ctx_cfg_NumberAxis, int ctx_cfg_NCart, int ctx_cfg_NRot,
                               CurvStruct *curv, double *vNorm, double *atNorm)
{
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double b_unnamed_idx_0;
    double k_vec;
    double n;
    double pseudoJerk;
    double u;
    double ud;
    double udd;
    double unnamed_idx_0;
    double y;
    int b_loop_ub;
    int i2;
    int loop_ub;
    // 'FeedratePlanning_LP:152' curv.ConstJerk = curv.ConstJerk / 2;
    curv->ConstJerk /= 2.0;
    // 'FeedratePlanning_LP:153' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
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
    pseudoJerk = curv->ConstJerk;
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
    k_vec = std::pow(6.0 / pseudoJerk, 0.33333333333333331);
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    ud = pseudoJerk * (k_vec * k_vec) / 2.0;
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    u = pseudoJerk * std::pow(k_vec, 3.0) / 6.0;
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
    udd = -(pseudoJerk * k_vec);
    // 'constJerkU:40' uddd = uddd;
    // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
    j_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, 1.0 - b_unnamed_idx_0, r0D, r1D, r2D, r3D);
    // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd,
    // r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
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
        varargin_1 = r1D[i] * ud;
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
            c_varargin_1 = (r2D[i3] * y + r1D[i3] * udd) * (r1D[i3] / n);
            r[i3] = std::pow(c_varargin_1, 2.0);
        }
    } else {
        binary_expand_op(r, r2D, y, r1D, udd, n);
    }
    *atNorm = std::sqrt(coder::sum(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
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
    coder::sparse r1;
    coder::sparse r2;
    coder::sparse r3;
    coder::sparse r4;
    coder::sparse r7;
    coder::sparse r8;
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
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 1U> bSlack;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> beqSlack;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> fSlack;
    ::coder::array<unsigned int, 2U> y;
    CurvStruct b_first;
    CurvStruct last;
    double X[2];
    double b_atNorm;
    double b_vNorm;
    double c_atNorm;
    double c_vNorm;
    double e_atNorm;
    double e_vNorm;
    double f_atNorm;
    double f_vNorm;
    int BasisVal_idx_0;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_status;
    int c_status;
    int d_status;
    int e_status;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int j_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int result;
    int unnamed_idx_1;
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
        int scalarLB;
        int vectorUB;
        c_loop_ub = b.size(0);
        scalarLB = (b.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i2{0}; i2 <= vectorUB; i2 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&b[i2 + b.size(0) * i1]);
            _mm_storeu_pd(&f[i2 + f.size(0) * i1], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
        }
        for (int i2{scalarLB}; i2 < c_loop_ub; i2++) {
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
    add_slack(f, A, b_b, Aeq, ctx->cfg.opt.SLACK_PENALTY, fSlack, ASlack, bSlack, AeqSlack);
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:29' [ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack,
    // ASlack, bSlack, ... 'FeedratePlanning_LP:30'     AeqSlack, beqSlack, ctx, ...
    // 'FeedratePlanning_LP:31'     N, NWindow, "First LP" );
    //  Call the solver
    // -------------------------------------------------------------------------
    //  Functions
    // -------------------------------------------------------------------------
    // 'FeedratePlanning_LP:72' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, ... 'FeedratePlanning_LP:73'     beq, ctx );
    coder::b_sparse(ASlack, &r1);
    c_simplex(fSlack, &r1, bSlack, AeqSlack, beqSlack, Coeff0, &b_success, &b_status);
    c_success = b_success;
    //  If optimization failed due with zero end constaints, decrease pseudo jerk
    // 'FeedratePlanning_LP:75' if( ~success && ( ctx.zero_end || ctx.zero_start ) )
    if ((!b_success) && (ctx->zero_end || ctx->zero_start)) {
        // 'FeedratePlanning_LP:76' if( ctx.zero_end )
        if (ctx->zero_end) {
            double atNorm;
            double vNorm;
            int count;
            //  Read last curve ( NZ )
            // 'FeedratePlanning_LP:78' last    = ctx.q_split.get( ctx.k0 + NWindow );
            ctx->q_split.get(static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow)),
                             &last);
            // 'FeedratePlanning_LP:79' count   = 0;
            count = 0;
            // 'FeedratePlanning_LP:79' iterMax = 15;
            // 'FeedratePlanning_LP:80' atNorm  = -ctx.at_1;
            atNorm = -ctx->at_1;
            // 'FeedratePlanning_LP:81' vNorm   = -ctx.v_1;
            vNorm = -ctx->v_1;
            // 'FeedratePlanning_LP:83' while( ~success && count < iterMax )
            while ((!c_success) && (count < 15)) {
                // 'FeedratePlanning_LP:84' [ last, vNorm , atNorm ] = decrease_constjerk( ctx,
                // last, true );
                decrease_constjerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, &last, &b_vNorm, &b_atNorm);
                vNorm = b_vNorm;
                atNorm = b_atNorm;
                // 'FeedratePlanning_LP:85' beq( end-1 )   = -vNorm^2;
                beqSlack[beqSlack.size(0) - 2] = -(b_vNorm * b_vNorm);
                // 'FeedratePlanning_LP:86' beq( end )     = atNorm;
                beqSlack[beqSlack.size(0) - 1] = b_atNorm;
                // 'FeedratePlanning_LP:87' [ Coeff0, success, status, msg ] = c_simplex( f, sparse(
                // A ), b, ... 'FeedratePlanning_LP:88'                 Aeq, beq, ctx );
                coder::b_sparse(ASlack, &r2);
                c_simplex(fSlack, &r2, bSlack, AeqSlack, beqSlack, Coeff0, &c_success, &c_status);
                // 'FeedratePlanning_LP:89' count = count + 1;
                count++;
            }
            //  Set back the change into the queue
            // 'FeedratePlanning_LP:92' ctx.q_split.set( ctx.k0 + NWindow, last );
            ctx->q_split.set(static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow)),
                             &last);
            // 'FeedratePlanning_LP:93' ctx.at_1    = -atNorm;
            ctx->at_1 = -atNorm;
            // 'FeedratePlanning_LP:94' ctx.v_1     = -vNorm;
            ctx->v_1 = -vNorm;
        } else {
            double atNorm;
            double vNorm;
            int count;
            // 'FeedratePlanning_LP:95' else
            //  Read first curve ( ZN )
            // 'FeedratePlanning_LP:97' first   = ctx.q_split.get( ctx.k0 );
            ctx->q_split.get(ctx->k0, &b_first);
            // 'FeedratePlanning_LP:98' count   = 0;
            count = 0;
            // 'FeedratePlanning_LP:98' iterMax = 15;
            // 'FeedratePlanning_LP:99' atNorm  = ctx.at_0;
            atNorm = ctx->at_0;
            // 'FeedratePlanning_LP:100' vNorm   = ctx.v_0;
            vNorm = ctx->v_0;
            // 'FeedratePlanning_LP:101' while( ~success && count < iterMax )
            while ((!c_success) && (count < 15)) {
                // 'FeedratePlanning_LP:102' [ first, vNorm , atNorm ] = decrease_constjerk( ctx,
                // first, false ); 'FeedratePlanning_LP:152' curv.ConstJerk = curv.ConstJerk / 2;
                b_first.ConstJerk /= 2.0;
                // 'FeedratePlanning_LP:153' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv,
                // isEnd );
                calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                    ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                    ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                    ctx->cfg.NRot, &b_first, &c_vNorm, &c_atNorm);
                vNorm = c_vNorm;
                atNorm = c_atNorm;
                // 'FeedratePlanning_LP:103' beq( 1 )   = vNorm^2;
                beqSlack[0] = c_vNorm * c_vNorm;
                // 'FeedratePlanning_LP:104' beq( 2 )   = atNorm;
                beqSlack[1] = c_atNorm;
                // 'FeedratePlanning_LP:105' [ Coeff0, success, status, msg ] = c_simplex( f,
                // sparse( A ), b, ... 'FeedratePlanning_LP:106'                 Aeq, beq, ctx );
                coder::b_sparse(ASlack, &r3);
                c_simplex(fSlack, &r3, bSlack, AeqSlack, beqSlack, Coeff0, &c_success, &d_status);
                // 'FeedratePlanning_LP:107' count = count + 1;
                count++;
            }
            //  Set back the change into the queue
            // 'FeedratePlanning_LP:110' ctx.q_split.set( ctx.k0, first );
            ctx->q_split.set(ctx->k0, &b_first);
            // 'FeedratePlanning_LP:111' ctx.at_0    = atNorm;
            ctx->at_0 = atNorm;
            // 'FeedratePlanning_LP:112' ctx.v_0     = vNorm;
            ctx->v_0 = vNorm;
        }
    }
    //  Check the status of the optimization
    // 'FeedratePlanning_LP:118' if( ~success )
    if (c_success) {
        int d_loop_ub;
        // 'FeedratePlanning_LP:123' else
        // 'FeedratePlanning_LP:124' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (Coeff0.size(0) - 1 < 1) {
            d_loop_ub = 0;
        } else {
            d_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, d_loop_ub);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_Coeff0[i4] = Coeff0[i4];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        b_Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i5{0}; i5 < loop_ub_tmp; i5++) {
            for (int i7{0}; i7 < BasisVal_idx_0; i7++) {
                b_Coeff[i7 + b_Coeff.size(0) * i5] = b_Coeff0[i7 + BasisVal_idx_0 * i5];
            }
        }
        // 'FeedratePlanning_LP:125' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
    } else {
        // 'FeedratePlanning_LP:119' Coeff = [];
        // 'FeedratePlanning_LP:120' if( coder.target( "MATLAB" ) )
        // 'FeedratePlanning_LP:121' error( optName + " failed...");
    }
    //  2) Optimization : second LP with jerk constraints and slack
    // 'FeedratePlanning_LP:35' if( true )
    //  B. Constraints : Inequality and Equality
    //  Feedrate, acceleration and jerk
    // 'FeedratePlanning_LP:38' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
    // 'FeedratePlanning_LP:39'         BasisVal, BasisValD, BasisValDD, u_vec );
    b_window.set_size(1, loop_ub);
    for (int i6{0}; i6 < loop_ub; i6++) {
        b_window[i6] = window[i6];
    }
    c_ctx = ctx->kin;
    buildConstrJerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                    ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                    ctx->cfg.NCart, ctx->cfg.NRot, &c_ctx, b_window, b_Coeff, jmax, BasisVal,
                    BasisValD, BasisValDD, u_vec, Aj, bj);
    // 'FeedratePlanning_LP:41' Atot = [ A; Aj ];
    if ((A.size(0) != 0) && (A.size(1) != 0)) {
        result = A.size(1);
    } else if ((Aj.size(0) != 0) && (Aj.size(1) != 0)) {
        result = Aj.size(1);
    } else {
        result = A.size(1);
        if (Aj.size(1) > A.size(1)) {
            result = Aj.size(1);
        }
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
        input_sizes_idx_0 = A.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((Aj.size(0) != 0) && (Aj.size(1) != 0))) {
        b_input_sizes_idx_0 = Aj.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    // 'FeedratePlanning_LP:41' btot = [ b; bj ];
    // 'FeedratePlanning_LP:43' indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];
    if (bj.size(0) < 1) {
        y.set_size(1, 0);
    } else {
        int e_loop_ub;
        y.set_size(1, bj.size(0));
        e_loop_ub = bj.size(0) - 1;
        for (int i8{0}; i8 <= e_loop_ub; i8++) {
            y[i8] = i8 + 1U;
        }
    }
    varargin_2.set_size(1, y.size(1));
    f_loop_ub = y.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        varargin_2[i9] = y[i9] + b_b.size(0);
    }
    // 'FeedratePlanning_LP:45' [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    // 'FeedratePlanning_LP:46'         Atot, btot, Aeq, beq, indSlack, LP );
    if (varargin_2.size(1) != 0) {
        unnamed_idx_1 = varargin_2.size(1);
    } else {
        unnamed_idx_1 = 0;
    }
    b_A.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, result);
    for (int i10{0}; i10 < result; i10++) {
        for (int i12{0}; i12 < input_sizes_idx_0; i12++) {
            b_A[i12 + b_A.size(0) * i10] = A[i12 + input_sizes_idx_0 * i10];
        }
    }
    for (int i11{0}; i11 < result; i11++) {
        for (int i13{0}; i13 < b_input_sizes_idx_0; i13++) {
            b_A[(i13 + input_sizes_idx_0) + b_A.size(0) * i11] =
                Aj[i13 + b_input_sizes_idx_0 * i11];
        }
    }
    c_b.set_size(b_b.size(0) + bj.size(0));
    g_loop_ub = b_b.size(0);
    for (int i14{0}; i14 < g_loop_ub; i14++) {
        c_b[i14] = b_b[i14];
    }
    h_loop_ub = bj.size(0);
    for (int i15{0}; i15 < h_loop_ub; i15++) {
        c_b[i15 + b_b.size(0)] = bj[i15];
    }
    ::coder::array<double, 2U> b_varargin_2;
    b_varargin_2 = varargin_2.reshape(1, unnamed_idx_1);
    add_slack(f, b_A, c_b, Aeq, b_varargin_2, ctx->cfg.opt.SLACK_PENALTY, fSlack, ASlack, bSlack,
              AeqSlack);
    // 'FeedratePlanning_LP:48' [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack, ASlack,
    // bSlack, ... 'FeedratePlanning_LP:49'         AeqSlack, beqSlack, ctx, ...
    // 'FeedratePlanning_LP:50'         N, NWindow, "Second LP" );
    //  Call the solver
    // -------------------------------------------------------------------------
    //  Functions
    // -------------------------------------------------------------------------
    // 'FeedratePlanning_LP:72' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, ... 'FeedratePlanning_LP:73'     beq, ctx );
    coder::b_sparse(ASlack, &r4);
    c_simplex(fSlack, &r4, bSlack, AeqSlack, beqSlack, Coeff0, &d_success, &e_status);
    e_success = d_success;
    //  If optimization failed due with zero end constaints, decrease pseudo jerk
    // 'FeedratePlanning_LP:75' if( ~success && ( ctx.zero_end || ctx.zero_start ) )
    if ((!d_success) && (ctx->zero_end || ctx->zero_start)) {
        // 'FeedratePlanning_LP:76' if( ctx.zero_end )
        if (ctx->zero_end) {
            double d_atNorm;
            double d_vNorm;
            int b_count;
            //  Read last curve ( NZ )
            // 'FeedratePlanning_LP:78' last    = ctx.q_split.get( ctx.k0 + NWindow );
            ctx->q_split.get(static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow)),
                             &last);
            // 'FeedratePlanning_LP:79' count   = 0;
            b_count = 0;
            // 'FeedratePlanning_LP:79' iterMax = 15;
            // 'FeedratePlanning_LP:80' atNorm  = -ctx.at_1;
            d_atNorm = -ctx->at_1;
            // 'FeedratePlanning_LP:81' vNorm   = -ctx.v_1;
            d_vNorm = -ctx->v_1;
            // 'FeedratePlanning_LP:83' while( ~success && count < iterMax )
            while ((!e_success) && (b_count < 15)) {
                // 'FeedratePlanning_LP:84' [ last, vNorm , atNorm ] = decrease_constjerk( ctx,
                // last, true );
                decrease_constjerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, &last, &e_vNorm, &e_atNorm);
                d_vNorm = e_vNorm;
                d_atNorm = e_atNorm;
                // 'FeedratePlanning_LP:85' beq( end-1 )   = -vNorm^2;
                beqSlack[beqSlack.size(0) - 2] = -(e_vNorm * e_vNorm);
                // 'FeedratePlanning_LP:86' beq( end )     = atNorm;
                beqSlack[beqSlack.size(0) - 1] = e_atNorm;
                // 'FeedratePlanning_LP:87' [ Coeff0, success, status, msg ] = c_simplex( f, sparse(
                // A ), b, ... 'FeedratePlanning_LP:88'                 Aeq, beq, ctx );
                coder::b_sparse(ASlack, &r7);
                c_simplex(fSlack, &r7, bSlack, AeqSlack, beqSlack, Coeff0, &e_success, &e_status);
                // 'FeedratePlanning_LP:89' count = count + 1;
                b_count++;
            }
            //  Set back the change into the queue
            // 'FeedratePlanning_LP:92' ctx.q_split.set( ctx.k0 + NWindow, last );
            ctx->q_split.set(static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow)),
                             &last);
            // 'FeedratePlanning_LP:93' ctx.at_1    = -atNorm;
            ctx->at_1 = -d_atNorm;
            // 'FeedratePlanning_LP:94' ctx.v_1     = -vNorm;
            ctx->v_1 = -d_vNorm;
        } else {
            double d_atNorm;
            double d_vNorm;
            int b_count;
            // 'FeedratePlanning_LP:95' else
            //  Read first curve ( ZN )
            // 'FeedratePlanning_LP:97' first   = ctx.q_split.get( ctx.k0 );
            ctx->q_split.get(ctx->k0, &b_first);
            // 'FeedratePlanning_LP:98' count   = 0;
            b_count = 0;
            // 'FeedratePlanning_LP:98' iterMax = 15;
            // 'FeedratePlanning_LP:99' atNorm  = ctx.at_0;
            d_atNorm = ctx->at_0;
            // 'FeedratePlanning_LP:100' vNorm   = ctx.v_0;
            d_vNorm = ctx->v_0;
            // 'FeedratePlanning_LP:101' while( ~success && count < iterMax )
            while ((!e_success) && (b_count < 15)) {
                // 'FeedratePlanning_LP:102' [ first, vNorm , atNorm ] = decrease_constjerk( ctx,
                // first, false ); 'FeedratePlanning_LP:152' curv.ConstJerk = curv.ConstJerk / 2;
                b_first.ConstJerk /= 2.0;
                // 'FeedratePlanning_LP:153' [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv,
                // isEnd );
                calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                    ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                    ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                    ctx->cfg.NRot, &b_first, &f_vNorm, &f_atNorm);
                d_vNorm = f_vNorm;
                d_atNorm = f_atNorm;
                // 'FeedratePlanning_LP:103' beq( 1 )   = vNorm^2;
                beqSlack[0] = f_vNorm * f_vNorm;
                // 'FeedratePlanning_LP:104' beq( 2 )   = atNorm;
                beqSlack[1] = f_atNorm;
                // 'FeedratePlanning_LP:105' [ Coeff0, success, status, msg ] = c_simplex( f,
                // sparse( A ), b, ... 'FeedratePlanning_LP:106'                 Aeq, beq, ctx );
                coder::b_sparse(ASlack, &r8);
                c_simplex(fSlack, &r8, bSlack, AeqSlack, beqSlack, Coeff0, &e_success, &e_status);
                // 'FeedratePlanning_LP:107' count = count + 1;
                b_count++;
            }
            //  Set back the change into the queue
            // 'FeedratePlanning_LP:110' ctx.q_split.set( ctx.k0, first );
            ctx->q_split.set(ctx->k0, &b_first);
            // 'FeedratePlanning_LP:111' ctx.at_0    = atNorm;
            ctx->at_0 = d_atNorm;
            // 'FeedratePlanning_LP:112' ctx.v_0     = vNorm;
            ctx->v_0 = d_vNorm;
        }
    }
    //  Check the status of the optimization
    // 'FeedratePlanning_LP:118' if( ~success )
    if (e_success) {
        int i_loop_ub;
        // 'FeedratePlanning_LP:123' else
        // 'FeedratePlanning_LP:124' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (Coeff0.size(0) - 1 < 1) {
            i_loop_ub = 0;
        } else {
            i_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, i_loop_ub);
        for (int i16{0}; i16 < i_loop_ub; i16++) {
            b_Coeff0[i16] = Coeff0[i16];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i17{0}; i17 < loop_ub_tmp; i17++) {
            for (int i18{0}; i18 < BasisVal_idx_0; i18++) {
                Coeff[i18 + Coeff.size(0) * i17] = b_Coeff0[i18 + BasisVal_idx_0 * i17];
            }
        }
        // 'FeedratePlanning_LP:125' if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
    } else {
        // 'FeedratePlanning_LP:119' Coeff = [];
        // 'FeedratePlanning_LP:120' if( coder.target( "MATLAB" ) )
        // 'FeedratePlanning_LP:121' error( optName + " failed...");
    }
    //  Compute the continuity equations
    // 'FeedratePlanning_LP:54' X  = continuity * Coeff( : , 1 );
    inner = continuity.size(1);
    X[0] = 0.0;
    X[1] = 0.0;
    for (int b_k{0}; b_k < inner; b_k++) {
        __m128d r5;
        __m128d r6;
        r5 = _mm_loadu_pd(&continuity[2 * b_k]);
        r6 = _mm_loadu_pd(&X[0]);
        _mm_storeu_pd(&X[0], _mm_add_pd(r6, _mm_mul_pd(r5, _mm_set1_pd(Coeff[b_k]))));
    }
    // 'FeedratePlanning_LP:56' if( ~ctx.zero_start )
    if (!ctx->zero_start) {
        // 'FeedratePlanning_LP:57' ctx.v_0     = sqrt( X( 1 ) );
        ctx->v_0 = std::sqrt(X[0]);
        // 'FeedratePlanning_LP:58' ctx.at_0    = X( 2 );
        ctx->at_0 = X[1];
    }
    // 'FeedratePlanning_LP:61' ctx.Coeff   = Coeff;
    ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
    j_loop_ub = Coeff.size(1);
    for (int i19{0}; i19 < j_loop_ub; i19++) {
        int k_loop_ub;
        k_loop_ub = Coeff.size(0);
        for (int i20{0}; i20 < k_loop_ub; i20++) {
            ctx->Coeff[i20 + ctx->Coeff.size(0) * i19] = Coeff[i20 + Coeff.size(0) * i19];
        }
    }
    *success = true;
    *status = e_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_LP.cpp
//
// [EOF]
//
