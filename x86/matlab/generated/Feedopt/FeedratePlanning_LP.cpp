//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
//

// Include Files
#include "FeedratePlanning_LP.h"
#include "Kinematics.h"
#include "buildConstr.h"
#include "buildConstrJerk.h"
#include "c_simplex.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
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
namespace ocn {
void FeedratePlanning_LP(b_FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &window,
                         const double amax[6], const double jmax[6],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr,
                         const ::coder::array<double, 2U> &u_vec, double NWindow,
                         ::coder::array<double, 2U> &Coeff, bool *success, int *status)
{
    coder::sparse r1;
    coder::sparse r2;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> Coeff2;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_Coeff0;
    ::coder::array<double, 2U> b_Coeff2;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> d_result;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> beq;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> c_f;
    ::coder::array<signed char, 2U> b_varargin_2;
    ::coder::array<signed char, 1U> varargin_2;
    double X[2];
    double f_tmp;
    int b_f;
    int b_loop_ub;
    int b_status;
    int c_input_sizes_idx_1;
    int c_result;
    int c_status;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
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
    bool empty_non_axis_sizes;
    //  M     : number of discretization
    //  N     : number of coefficients
    // 'FeedratePlanning_LP:9' [ M, N ]    = size( BasisVal );
    // 'FeedratePlanning_LP:10' LP          = ctx.cfg.opt;
    //  Load parameters of the LP
    // 'FeedratePlanning_LP:11' CurvArray   = window( 1 : NWindow );
    if (1.0 > NWindow) {
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
        int i2;
        int scalarLB;
        int vectorUB;
        c_loop_ub = b.size(0);
        scalarLB = (b.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i2 = 0; i2 <= vectorUB; i2 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&b[i2 + b.size(0) * i1]);
            _mm_storeu_pd(&f[i2 + f.size(0) * i1], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
        }
        for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
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
    buildConstr(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart,
                ctx->cfg.maskRot, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS,
                ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS, &ctx->kin, b_window, amax, ctx->v_0, ctx->at_0,
                ctx->v_1, ctx->at_1, BasisVal, BasisValD, u_vec, A, b_b, Aeq, beq, continuity);
    //  Slack variables
    // 'FeedratePlanning_LP:24' fSlack = [ f( : ); LP.SLACK_PENALTY ];
    // 'FeedratePlanning_LP:25' [ nAL, nAc ] = size( A );
    // 'FeedratePlanning_LP:26' ASlack = [ A, - ones( nAL, 1 ) ; zeros( 1, nAc ), -1 ];
    varargin_2.set_size(A.size(0));
    d_loop_ub = A.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        varargin_2[i4] = -1;
    }
    if ((A.size(0) != 0) && (A.size(1) != 0)) {
        result = A.size(0);
    } else if (varargin_2.size(0) != 0) {
        result = varargin_2.size(0);
    } else {
        result = A.size(0);
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
        input_sizes_idx_1 = A.size(1);
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_2.size(0) != 0)) {
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
    e_loop_ub = b_input_sizes_idx_1;
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        for (int i8{0}; i8 < result; i8++) {
            b_result[i8 + b_result.size(0) * input_sizes_idx_1] = -1.0;
        }
    }
    b_varargin_2.set_size(1, A.size(1) + 1);
    f_loop_ub = A.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        b_varargin_2[i9] = 0;
    }
    b_varargin_2[A.size(1)] = -1;
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = b_varargin_2.size(1);
    }
    // 'FeedratePlanning_LP:27' bSlack = [ b ; 0 ];
    // 'FeedratePlanning_LP:28' AeqSlack   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
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
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:31' [ Coeff0, success, status, msg ] = c_simplex( fSlack, sparse( ASlack
    // ), ... 'FeedratePlanning_LP:32'     bSlack, AeqSlack, beq, ctx );
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        input_sizes_idx_0 = b_result.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    d_result.set_size(input_sizes_idx_0 + 1, sizes_idx_1);
    for (int i10{0}; i10 < sizes_idx_1; i10++) {
        for (int i12{0}; i12 < input_sizes_idx_0; i12++) {
            d_result[i12 + d_result.size(0) * i10] = b_result[i12 + input_sizes_idx_0 * i10];
        }
    }
    for (int i11{0}; i11 < sizes_idx_1; i11++) {
        d_result[input_sizes_idx_0 + d_result.size(0) * i11] = b_varargin_2[i11];
    }
    b_f = f.size(0) * f.size(1);
    c_f.set_size(b_f + 1);
    for (int i13{0}; i13 < b_f; i13++) {
        c_f[i13] = f[i13];
    }
    f_tmp = ctx->cfg.opt.SLACK_PENALTY;
    c_f[b_f] = f_tmp;
    c_b.set_size(b_b.size(0) + 1);
    g_loop_ub = b_b.size(0);
    for (int i14{0}; i14 < g_loop_ub; i14++) {
        c_b[i14] = b_b[i14];
    }
    c_b[b_b.size(0)] = 0.0;
    b_Aeq.set_size(c_result, c_input_sizes_idx_1 + d_input_sizes_idx_1);
    for (int i15{0}; i15 < c_input_sizes_idx_1; i15++) {
        for (int i16{0}; i16 < c_result; i16++) {
            b_Aeq[i16 + b_Aeq.size(0) * i15] = Aeq[i16 + c_result * i15];
        }
    }
    h_loop_ub = d_input_sizes_idx_1;
    for (int i17{0}; i17 < h_loop_ub; i17++) {
        for (int i18{0}; i18 < c_result; i18++) {
            b_Aeq[i18 + b_Aeq.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    coder::b_sparse(d_result, &r1);
    c_simplex(c_f, &r1, c_b, b_Aeq, beq, Coeff0, &b_success, &b_status);
    c_success = b_success;
    // 'FeedratePlanning_LP:35' if( ~success )
    if (b_success) {
        int BasisVal_idx_0;
        int b_input_sizes_idx_0;
        int c_input_sizes_idx_0;
        int e_input_sizes_idx_1;
        int e_result;
        int f_result;
        int g_input_sizes_idx_1;
        int g_result;
        int i_loop_ub;
        int inner;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int p_loop_ub;
        signed char f_input_sizes_idx_1;
        signed char h_input_sizes_idx_1;
        bool c_empty_non_axis_sizes;
        bool d_empty_non_axis_sizes;
        bool e_empty_non_axis_sizes;
        // 'FeedratePlanning_LP:41' else
        // 'FeedratePlanning_LP:42' Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
        if (1 > Coeff0.size(0) - 1) {
            i_loop_ub = 0;
        } else {
            i_loop_ub = Coeff0.size(0) - 1;
        }
        b_Coeff0.set_size(1, i_loop_ub);
        for (int i19{0}; i19 < i_loop_ub; i19++) {
            b_Coeff0[i19] = Coeff0[i19];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i20{0}; i20 < loop_ub_tmp; i20++) {
            for (int i21{0}; i21 < BasisVal_idx_0; i21++) {
                Coeff[i21 + Coeff.size(0) * i20] = b_Coeff0[i21 + BasisVal_idx_0 * i20];
            }
        }
        //  2) Optimization : second LP with jerk constraints and slack
        //  % A. Linear objectif
        // 'FeedratePlanning_LP:48' ftot = [ f( : ); LP.SLACK_PENALTY ];
        //  B. Constraints : Inequality and Equality
        //  Feedrate, acceleration and jerk
        // 'FeedratePlanning_LP:52' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
        // 'FeedratePlanning_LP:53'     BasisVal, BasisValD, BasisValDD, u_vec );
        b_Coeff0.set_size(1, i_loop_ub);
        for (int i22{0}; i22 < i_loop_ub; i22++) {
            b_Coeff0[i22] = Coeff0[i22];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        b_window.set_size(1, loop_ub);
        for (int i23{0}; i23 < loop_ub; i23++) {
            b_window[i23] = window[i23];
        }
        ::coder::array<double, 2U> c_Coeff0;
        c_Coeff0 = b_Coeff0.reshape(BasisVal_idx_0, loop_ub_tmp);
        buildConstrJerk(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                        ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart, ctx->cfg.indRot,
                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &ctx->kin, b_window,
                        c_Coeff0, jmax, BasisVal, BasisValD, BasisValDD, u_vec, Aj, bj);
        // 'FeedratePlanning_LP:55' Atot    = [ A, -ones( size( A, 1), 1 ) ;
        // 'FeedratePlanning_LP:56'     Aj ];
        varargin_2.set_size(A.size(0));
        j_loop_ub = A.size(0);
        for (int i24{0}; i24 < j_loop_ub; i24++) {
            varargin_2[i24] = -1;
        }
        if ((A.size(0) != 0) && (A.size(1) != 0)) {
            e_result = A.size(0);
        } else if (varargin_2.size(0) != 0) {
            e_result = varargin_2.size(0);
        } else {
            e_result = A.size(0);
        }
        c_empty_non_axis_sizes = (e_result == 0);
        if (c_empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
            e_input_sizes_idx_1 = A.size(1);
        } else {
            e_input_sizes_idx_1 = 0;
        }
        if (c_empty_non_axis_sizes || (varargin_2.size(0) != 0)) {
            f_input_sizes_idx_1 = 1;
        } else {
            f_input_sizes_idx_1 = 0;
        }
        b_result.set_size(e_result, e_input_sizes_idx_1 + f_input_sizes_idx_1);
        for (int i25{0}; i25 < e_input_sizes_idx_1; i25++) {
            for (int i26{0}; i26 < e_result; i26++) {
                b_result[i26 + b_result.size(0) * i25] = A[i26 + e_result * i25];
            }
        }
        k_loop_ub = f_input_sizes_idx_1;
        for (int i27{0}; i27 < k_loop_ub; i27++) {
            for (int i28{0}; i28 < e_result; i28++) {
                b_result[i28 + b_result.size(0) * e_input_sizes_idx_1] = -1.0;
            }
        }
        if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
            f_result = b_result.size(1);
        } else if ((Aj.size(0) != 0) && (Aj.size(1) != 0)) {
            f_result = Aj.size(1);
        } else {
            f_result = b_result.size(1);
            if (Aj.size(1) > b_result.size(1)) {
                f_result = Aj.size(1);
            }
        }
        d_empty_non_axis_sizes = (f_result == 0);
        if (d_empty_non_axis_sizes || ((b_result.size(0) != 0) && (b_result.size(1) != 0))) {
            b_input_sizes_idx_0 = b_result.size(0);
        } else {
            b_input_sizes_idx_0 = 0;
        }
        if (d_empty_non_axis_sizes || ((Aj.size(0) != 0) && (Aj.size(1) != 0))) {
            c_input_sizes_idx_0 = Aj.size(0);
        } else {
            c_input_sizes_idx_0 = 0;
        }
        // 'FeedratePlanning_LP:57' btot    = [ b; bj ];
        // 'FeedratePlanning_LP:59' AEtot   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
        if ((Aeq.size(0) != 0) && (Aeq.size(1) != 0)) {
            g_result = Aeq.size(0);
        } else if (Aeq.size(0) != 0) {
            g_result = Aeq.size(0);
        } else {
            g_result = 0;
        }
        e_empty_non_axis_sizes = (g_result == 0);
        if (e_empty_non_axis_sizes || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
            g_input_sizes_idx_1 = Aeq.size(1);
        } else {
            g_input_sizes_idx_1 = 0;
        }
        if (e_empty_non_axis_sizes || (Aeq.size(0) != 0)) {
            h_input_sizes_idx_1 = 1;
        } else {
            h_input_sizes_idx_1 = 0;
        }
        // 'FeedratePlanning_LP:61' [ Coeff2, success, status, msg ] = c_simplex( ftot, sparse( Atot
        // ), btot, ... 'FeedratePlanning_LP:62'     AEtot, beq, ctx );
        d_result.set_size(b_input_sizes_idx_0 + c_input_sizes_idx_0, f_result);
        for (int i29{0}; i29 < f_result; i29++) {
            for (int i31{0}; i31 < b_input_sizes_idx_0; i31++) {
                d_result[i31 + d_result.size(0) * i29] = b_result[i31 + b_input_sizes_idx_0 * i29];
            }
        }
        for (int i30{0}; i30 < f_result; i30++) {
            for (int i32{0}; i32 < c_input_sizes_idx_0; i32++) {
                d_result[(i32 + b_input_sizes_idx_0) + d_result.size(0) * i30] =
                    Aj[i32 + c_input_sizes_idx_0 * i30];
            }
        }
        b_f = f.size(0) * f.size(1);
        c_f.set_size(b_f + 1);
        for (int i33{0}; i33 < b_f; i33++) {
            c_f[i33] = f[i33];
        }
        c_f[b_f] = f_tmp;
        c_b.set_size(b_b.size(0) + bj.size(0));
        l_loop_ub = b_b.size(0);
        for (int i34{0}; i34 < l_loop_ub; i34++) {
            c_b[i34] = b_b[i34];
        }
        m_loop_ub = bj.size(0);
        for (int i35{0}; i35 < m_loop_ub; i35++) {
            c_b[i35 + b_b.size(0)] = bj[i35];
        }
        b_Aeq.set_size(g_result, g_input_sizes_idx_1 + h_input_sizes_idx_1);
        for (int i36{0}; i36 < g_input_sizes_idx_1; i36++) {
            for (int i37{0}; i37 < g_result; i37++) {
                b_Aeq[i37 + b_Aeq.size(0) * i36] = Aeq[i37 + g_result * i36];
            }
        }
        n_loop_ub = h_input_sizes_idx_1;
        for (int i38{0}; i38 < n_loop_ub; i38++) {
            for (int i39{0}; i39 < g_result; i39++) {
                b_Aeq[i39 + b_Aeq.size(0) * g_input_sizes_idx_1] = 0.0;
            }
        }
        coder::b_sparse(d_result, &r2);
        c_simplex(c_f, &r2, c_b, b_Aeq, beq, Coeff2, &d_success, &c_status);
        c_success = d_success;
        // 'FeedratePlanning_LP:65' if( ~success )
        if (d_success) {
            int o_loop_ub;
            // 'FeedratePlanning_LP:68' else
            // 'FeedratePlanning_LP:69' Coeff   = reshape( Coeff2( 1 : end -1 ), N, NWindow );
            if (1 > Coeff2.size(0) - 1) {
                o_loop_ub = 0;
            } else {
                o_loop_ub = Coeff2.size(0) - 1;
            }
            b_Coeff2.set_size(1, o_loop_ub);
            for (int i40{0}; i40 < o_loop_ub; i40++) {
                b_Coeff2[i40] = Coeff2[i40];
            }
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
            for (int i41{0}; i41 < loop_ub_tmp; i41++) {
                for (int i42{0}; i42 < BasisVal_idx_0; i42++) {
                    Coeff[i42 + Coeff.size(0) * i41] = b_Coeff2[i42 + BasisVal_idx_0 * i41];
                }
            }
            // 'FeedratePlanning_LP:70' if( coder.target( "MATLAB" ) )
        } else {
            //  The optimization successed
            // 'FeedratePlanning_LP:66' if( coder.target( "MATLAB" ) )
            // 'FeedratePlanning_LP:67' error( "Second LP failed..." );
        }
        //  Compute the continuity equations
        // 'FeedratePlanning_LP:74' X           = continuity * Coeff( : , 1 );
        inner = continuity.size(1);
        X[0] = 0.0;
        X[1] = 0.0;
        for (int b_k{0}; b_k < inner; b_k++) {
            __m128d r3;
            __m128d r4;
            r3 = _mm_loadu_pd(&continuity[2 * b_k]);
            r4 = _mm_loadu_pd(&X[0]);
            _mm_storeu_pd(&X[0], _mm_add_pd(r4, _mm_mul_pd(r3, _mm_set1_pd(Coeff[b_k]))));
        }
        // 'FeedratePlanning_LP:75' ctx.v_0     = sqrt( X( 1, : ) );
        ctx->v_0 = std::sqrt(X[0]);
        // 'FeedratePlanning_LP:76' ctx.at_0    = X( 2, : );
        ctx->at_0 = X[1];
        // 'FeedratePlanning_LP:77' ctx.Coeff   = Coeff;
        ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
        p_loop_ub = Coeff.size(1);
        for (int i43{0}; i43 < p_loop_ub; i43++) {
            int q_loop_ub;
            q_loop_ub = Coeff.size(0);
            for (int i44{0}; i44 < q_loop_ub; i44++) {
                ctx->Coeff[i44 + ctx->Coeff.size(0) * i43] = Coeff[i44 + Coeff.size(0) * i43];
            }
        }
    } else {
        // 'FeedratePlanning_LP:36' Coeff = [];
        // 'FeedratePlanning_LP:37' NCoeff = int32(0);
        // 'FeedratePlanning_LP:38' if( coder.target( "MATLAB" ) )
        // 'FeedratePlanning_LP:39' error("First LP failed...");
    }
    *success = c_success;
    *status = c_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_LP.cpp
//
// [EOF]
//
