//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "FeedratePlanning_LP.h"
#include "buildConstr.h"
#include "buildConstrJerk.h"
#include "find.h"
#include "linspace.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "queue_coder.h"
#include "sparse.h"
#include "sparse1.h"
#include "string1.h"
#include "coder_array.h"
#include "cpp_simplex.hpp"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [ctx, Coeff, success, status, msg] = ...
//     FeedratePlanning_LP( ctx, window, amax, jmax, BasisVal, ...
//     BasisValD, BasisValDD, BasisIntegr, u_vec, NWindow )
//
// 0) Initialization of the problem
//
// Arguments    : FeedoptContext *ctx
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
void FeedratePlanning_LP(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &window,
                         const double amax[6], const double jmax[6],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr,
                         const ::coder::array<double, 2U> &u_vec, double NWindow,
                         ::coder::array<double, 2U> &Coeff, bool *success, int *status)
{
    static const char obj1Value[8]{'s', 'l', 'a', 'c', 'k', ' ', ':', ' '};
    coder::rtString b_obj;
    coder::sparse Atot;
    coder::sparse c_r1;
    coder::sparse r;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> Coeff2;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_Coeff2;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> c_Coeff0;
    ::coder::array<double, 2U> continuity;
    ::coder::array<double, 2U> e_result;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 1U> Avs;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> beq;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> c_f;
    ::coder::array<int, 1U> Ais;
    ::coder::array<int, 1U> Ajs;
    ::coder::array<int, 1U> ii;
    ::coder::array<int, 1U> jj;
    double X_idx_0;
    double X_idx_1;
    int Asize[2];
    int Csize[2];
    int beqsize[2];
    int bsize[2];
    int fsize[2];
    int BasisVal_idx_0;
    int b_f;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_n;
    int b_status;
    int c_input_sizes_idx_1;
    int c_result;
    int c_status;
    int d_loop_ub;
    int d_result;
    int f_loop_ub;
    int g_loop_ub;
    int i31;
    int i8;
    int i_loop_ub;
    int inner;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int m_loop_ub;
    int n;
    int n_loop_ub;
    int o_loop_ub;
    int q_loop_ub;
    int result;
    char varargin_1_data[32];
    char st[24];
    char obj2Value_data[23];
    signed char b_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    bool b_empty_non_axis_sizes;
    bool b_success;
    bool c_empty_non_axis_sizes;
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
    buildConstr(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS, ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS, b_window,
                amax, ctx->v_0, ctx->at_0, ctx->v_1, ctx->at_1, BasisVal, BasisValD, u_vec, A, b_b,
                Aeq, beq, continuity);
    //  C. Solve the optimization problem
    // 'FeedratePlanning_LP:24' [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b,
    // Aeq, beq, ctx ); 'c_simplex:2' msg = ""; 'c_simplex:3' if coder.target('rtw') ||
    // coder.target('mex') 'c_simplex:4' c_prof_in(mfilename); 'c_simplex:5' c_prof_in('join_A');
    // 'c_simplex:6' Atot = [A; Aeq];
    coder::b_sparse(A, &r);
    r.vertcat(Aeq, &Atot);
    // 'c_simplex:7' c_prof_out('join_A');
    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    // 'c_simplex:9' [NCoeff, NHorz] = size(f);
    // 'c_simplex:10' C = zeros(NCoeff, NHorz);
    Coeff0.set_size(f.size(0), f.size(1));
    d_loop_ub = f.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        int e_loop_ub;
        e_loop_ub = f.size(0);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            Coeff0[i5 + Coeff0.size(0) * i4] = 0.0;
        }
    }
    // 'c_simplex:11' coder.varsize('C', [Inf, Inf], [1,1]);
    // 'c_simplex:13' [Aisd, Ajsd, Avs] = find(Atot);
    coder::c_eml_find(&Atot, ii, jj, Avs);
    // 'c_simplex:14' Ais = int32(Aisd)-1;
    Ais.set_size(ii.size(0));
    f_loop_ub = ii.size(0);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        Ais[i6] = ii[i6] - 1;
    }
    // 'c_simplex:15' Ajs = int32(Ajsd)-1;
    Ajs.set_size(jj.size(0));
    g_loop_ub = jj.size(0);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        Ajs[i7] = jj[i7] - 1;
    }
    // 'c_simplex:17' coder.varsize('Avs', [Inf, 1], [1, 0]);
    // 'c_simplex:18' coder.varsize('Ais', [Inf, 1], [1, 0]);
    // 'c_simplex:19' coder.varsize('Ajs', [Inf, 1], [1, 0]);
    // 'c_simplex:21' fsize = int32(size(f));
    fsize[0] = f.size(0);
    fsize[1] = f.size(1);
    // 'c_simplex:22' Asize = int32(size(Atot));
    Asize[0] = Atot.m;
    Asize[1] = Atot.n;
    // 'c_simplex:23' An = int32(nnz(Avs));
    n = 0;
    i8 = Avs.size(0);
    for (int b_k{0}; b_k < i8; b_k++) {
        if (Avs[b_k] != 0.0) {
            n++;
        }
    }
    // 'c_simplex:24' bsize = int32(size(b));
    bsize[0] = b_b.size(0);
    bsize[1] = 1;
    // 'c_simplex:25' beqsize = int32(size(beq));
    beqsize[0] = beq.size(0);
    beqsize[1] = 1;
    // 'c_simplex:26' Csize = int32(size(C));
    Csize[0] = f.size(0);
    Csize[1] = f.size(1);
    // 'c_simplex:27' success = int32(0);
    // 'c_simplex:28' status = int32(0);
    // 'c_simplex:29' coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp',
    // '$(START_DIR)/src/'); 'c_simplex:30' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.clp.lflags); 'c_simplex:31' coder.cinclude('cpp_simplex.hpp'); 'c_simplex:32' status
    // = coder.ceval('simplex_solve', coder.rref(f), fsize,... 'c_simplex:33' coder.rref(Avs),
    // coder.rref(Ais), coder.rref(Ajs), Asize, An,... 'c_simplex:34'         coder.rref(b), bsize,
    // coder.rref(beq),beqsize,... 'c_simplex:35'         coder.ref(C), Csize);
    b_status = simplex_solve(&f[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0], &(Ajs.data())[0],
                             &Asize[0], n, &(b_b.data())[0], &bsize[0], &(beq.data())[0],
                             &beqsize[0], &Coeff0[0], &Csize[0]);
    //          C = solution.solution;
    // 'c_simplex:37' success = status == 0;
    //  Status :
    //        0 : Primal Dual Optimality
    //        1 : Primal Infeasible
    //        2 : Dual Infeasible
    //        3 : Max iteration reached
    //        4 : isAbandoned
    // 'c_simplex:44' c_prof_out(mfilename);
    // 'FeedratePlanning_LP:26' if( ~success )
    if (b_status != 0) {
        double X_idx_1_tmp;
        double Y_idx_1;
        double a21;
        double a21_tmp;
        double b_a21;
        int b_Coeff0;
        int b_r1;
        int b_r2;
        int h_loop_ub;
        int r1;
        int r2;
        // 'FeedratePlanning_LP:27' Coeff0 = zeros( size( A, 2),  1);
        Coeff0.set_size(A.size(1), 1);
        h_loop_ub = A.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            Coeff0[i9] = 0.0;
        }
        // 'FeedratePlanning_LP:28' M = Aeq( 1 : 2, 1 : 2 );
        // 'FeedratePlanning_LP:29' m = beq( 1 : 2 );
        // 'FeedratePlanning_LP:30' Coeff0( 1 : 2 ) = M \ m;
        if (std::abs(Aeq[1]) > std::abs(Aeq[0])) {
            r1 = 1;
            r2 = 0;
        } else {
            r1 = 0;
            r2 = 1;
        }
        a21_tmp = Aeq[r1 % 2 + Aeq.size(0) * (r1 / 2)];
        a21 = Aeq[r2 % 2 + Aeq.size(0) * (r2 / 2)] / a21_tmp;
        X_idx_1_tmp = Aeq[(r1 + 2) % 2 + Aeq.size(0) * ((r1 + 2) / 2)];
        X_idx_1 = (beq[r2] - beq[r1] * a21) /
                  (Aeq[(r2 + 2) % 2 + Aeq.size(0) * ((r2 + 2) / 2)] - a21 * X_idx_1_tmp);
        Coeff0[0] = (beq[r1] - X_idx_1 * X_idx_1_tmp) / a21_tmp;
        Coeff0[1] = X_idx_1;
        // 'FeedratePlanning_LP:31' M1 = Aeq( end- 1:end, end- 1:end);
        // 'FeedratePlanning_LP:32' m1 = beq( end-1 : end );
        // 'FeedratePlanning_LP:33' Coeff0( end-1 :end ) = M1 \ m1;
        if (std::abs(Aeq[(Aeq.size(0) + Aeq.size(0) * (Aeq.size(1) - 2)) - 1]) >
            std::abs(Aeq[(Aeq.size(0) + Aeq.size(0) * (Aeq.size(1) - 2)) - 2])) {
            b_r1 = 0;
            b_r2 = -1;
        } else {
            b_r1 = -1;
            b_r2 = 0;
        }
        b_a21 = Aeq[((b_r2 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) - 2)) - 1] /
                Aeq[((b_r1 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) - 2)) - 1];
        Y_idx_1 = (beq[(b_r2 + beq.size(0)) - 1] - beq[(b_r1 + beq.size(0)) - 1] * b_a21) /
                  (Aeq[((b_r2 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) + -1)) - 1] -
                   b_a21 * Aeq[((b_r1 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) + -1)) - 1]);
        b_Coeff0 = Coeff0.size(0) - 1;
        Coeff0[Coeff0.size(0) - 2] =
            (beq[(b_r1 + beq.size(0)) - 1] -
             Y_idx_1 * Aeq[((b_r1 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) + -1)) - 1]) /
            Aeq[((b_r1 + Aeq.size(0)) + Aeq.size(0) * (Aeq.size(1) - 2)) - 1];
        Coeff0[b_Coeff0] = Y_idx_1;
        // 'FeedratePlanning_LP:34' CoeffInt = linspace( Coeff0(2), Coeff0(3), size( A, 2) -2 );
        coder::linspace(Coeff0[1], Coeff0[2], static_cast<double>(A.size(1)) - 2.0, c_Coeff0);
        // 'FeedratePlanning_LP:35' Coeff0( 3 :end -2 ) = CoeffInt( 2 : end -1 );
        // 'FeedratePlanning_LP:36' resIneq = A* Coeff0 -b;
        // 'FeedratePlanning_LP:37' errIneq = find( resIneq >= 0 );
        // 'FeedratePlanning_LP:38' error("First LP failed...");
    } else {
        // 'FeedratePlanning_LP:39' else
        // 'FeedratePlanning_LP:40' Coeff  = reshape( Coeff0, N, NWindow );
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i10{0}; i10 < loop_ub_tmp; i10++) {
            for (int i11{0}; i11 < BasisVal_idx_0; i11++) {
                Coeff[i11 + Coeff.size(0) * i10] = Coeff0[i11 + BasisVal_idx_0 * i10];
            }
        }
    }
    //  2) Optimization : second LP with jerk constraints and slack
    //  % A. Linear objectif
    // 'FeedratePlanning_LP:46' ftot = [ f( : ); LP.SLACK_PENALTY ];
    //  B. Constraints : Inequality and Equality
    //  Feedrate, acceleration and jerk
    // 'FeedratePlanning_LP:50' [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
    // 'FeedratePlanning_LP:51'     BasisVal, BasisValD, BasisValDD, u_vec );
    b_window.set_size(1, loop_ub);
    for (int i12{0}; i12 < loop_ub; i12++) {
        b_window[i12] = window[i12];
    }
    buildConstrJerk(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                    ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                    ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                    b_window, Coeff, jmax, BasisVal, BasisValD, BasisValDD, u_vec, Aj, bj);
    // 'FeedratePlanning_LP:53' Atot    = [ A, zeros( size( A, 1), 1 ) ;
    // 'FeedratePlanning_LP:54'     Aj ];
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
    for (int i13{0}; i13 < input_sizes_idx_1; i13++) {
        for (int i14{0}; i14 < result; i14++) {
            b_result[i14 + b_result.size(0) * i13] = A[i14 + result * i13];
        }
    }
    i_loop_ub = b_input_sizes_idx_1;
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        for (int i16{0}; i16 < result; i16++) {
            b_result[i16 + b_result.size(0) * input_sizes_idx_1] = 0.0;
        }
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        c_result = b_result.size(1);
    } else if ((Aj.size(0) != 0) && (Aj.size(1) != 0)) {
        c_result = Aj.size(1);
    } else {
        c_result = b_result.size(1);
        if (Aj.size(1) > b_result.size(1)) {
            c_result = Aj.size(1);
        }
    }
    b_empty_non_axis_sizes = (c_result == 0);
    if (b_empty_non_axis_sizes || ((b_result.size(0) != 0) && (b_result.size(1) != 0))) {
        input_sizes_idx_0 = b_result.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (b_empty_non_axis_sizes || ((Aj.size(0) != 0) && (Aj.size(1) != 0))) {
        b_input_sizes_idx_0 = Aj.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    // 'FeedratePlanning_LP:55' btot    = [ b; bj ];
    // 'FeedratePlanning_LP:57' AEtot   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
    if ((Aeq.size(0) != 0) && (Aeq.size(1) != 0)) {
        d_result = Aeq.size(0);
    } else if (Aeq.size(0) != 0) {
        d_result = Aeq.size(0);
    } else {
        d_result = 0;
    }
    c_empty_non_axis_sizes = (d_result == 0);
    if (c_empty_non_axis_sizes || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
        c_input_sizes_idx_1 = Aeq.size(1);
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (c_empty_non_axis_sizes || (Aeq.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    // 'FeedratePlanning_LP:59' [ Coeff2, success, status, msg ] = c_simplex( ftot, sparse( Atot ),
    // btot, ... 'FeedratePlanning_LP:60'     AEtot, beq, ctx );
    b_f = f.size(0) * f.size(1);
    c_f.set_size(b_f + 1);
    for (int i17{0}; i17 < b_f; i17++) {
        c_f[i17] = f[i17];
    }
    c_f[b_f] = ctx->cfg.opt.SLACK_PENALTY;
    e_result.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, c_result);
    for (int i18{0}; i18 < c_result; i18++) {
        for (int i20{0}; i20 < input_sizes_idx_0; i20++) {
            e_result[i20 + e_result.size(0) * i18] = b_result[i20 + input_sizes_idx_0 * i18];
        }
    }
    for (int i19{0}; i19 < c_result; i19++) {
        for (int i21{0}; i21 < b_input_sizes_idx_0; i21++) {
            e_result[(i21 + input_sizes_idx_0) + e_result.size(0) * i19] =
                Aj[i21 + b_input_sizes_idx_0 * i19];
        }
    }
    c_b.set_size(b_b.size(0) + bj.size(0));
    j_loop_ub = b_b.size(0);
    for (int i22{0}; i22 < j_loop_ub; i22++) {
        c_b[i22] = b_b[i22];
    }
    k_loop_ub = bj.size(0);
    for (int i23{0}; i23 < k_loop_ub; i23++) {
        c_b[i23 + b_b.size(0)] = bj[i23];
    }
    // 'c_simplex:2' msg = "";
    // 'c_simplex:3' if coder.target('rtw') || coder.target('mex')
    // 'c_simplex:4' c_prof_in(mfilename);
    // 'c_simplex:5' c_prof_in('join_A');
    // 'c_simplex:6' Atot = [A; Aeq];
    b_Aeq.set_size(d_result, c_input_sizes_idx_1 + d_input_sizes_idx_1);
    for (int i24{0}; i24 < c_input_sizes_idx_1; i24++) {
        for (int i25{0}; i25 < d_result; i25++) {
            b_Aeq[i25 + b_Aeq.size(0) * i24] = Aeq[i25 + d_result * i24];
        }
    }
    l_loop_ub = d_input_sizes_idx_1;
    for (int i26{0}; i26 < l_loop_ub; i26++) {
        for (int i27{0}; i27 < d_result; i27++) {
            b_Aeq[i27 + b_Aeq.size(0) * c_input_sizes_idx_1] = 0.0;
        }
    }
    coder::b_sparse(e_result, &c_r1);
    c_r1.vertcat(b_Aeq, &Atot);
    // 'c_simplex:7' c_prof_out('join_A');
    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    // 'c_simplex:9' [NCoeff, NHorz] = size(f);
    // 'c_simplex:10' C = zeros(NCoeff, NHorz);
    Coeff2.set_size(c_f.size(0), 1);
    m_loop_ub = c_f.size(0);
    for (int i28{0}; i28 < m_loop_ub; i28++) {
        Coeff2[i28] = 0.0;
    }
    // 'c_simplex:11' coder.varsize('C', [Inf, Inf], [1,1]);
    // 'c_simplex:13' [Aisd, Ajsd, Avs] = find(Atot);
    coder::c_eml_find(&Atot, ii, jj, Avs);
    // 'c_simplex:14' Ais = int32(Aisd)-1;
    Ais.set_size(ii.size(0));
    n_loop_ub = ii.size(0);
    for (int i29{0}; i29 < n_loop_ub; i29++) {
        Ais[i29] = ii[i29] - 1;
    }
    // 'c_simplex:15' Ajs = int32(Ajsd)-1;
    Ajs.set_size(jj.size(0));
    o_loop_ub = jj.size(0);
    for (int i30{0}; i30 < o_loop_ub; i30++) {
        Ajs[i30] = jj[i30] - 1;
    }
    // 'c_simplex:17' coder.varsize('Avs', [Inf, 1], [1, 0]);
    // 'c_simplex:18' coder.varsize('Ais', [Inf, 1], [1, 0]);
    // 'c_simplex:19' coder.varsize('Ajs', [Inf, 1], [1, 0]);
    // 'c_simplex:21' fsize = int32(size(f));
    fsize[0] = c_f.size(0);
    fsize[1] = 1;
    // 'c_simplex:22' Asize = int32(size(Atot));
    Asize[0] = Atot.m;
    Asize[1] = Atot.n;
    // 'c_simplex:23' An = int32(nnz(Avs));
    b_n = 0;
    i31 = Avs.size(0);
    for (int c_k{0}; c_k < i31; c_k++) {
        if (Avs[c_k] != 0.0) {
            b_n++;
        }
    }
    // 'c_simplex:24' bsize = int32(size(b));
    bsize[0] = c_b.size(0);
    bsize[1] = 1;
    // 'c_simplex:25' beqsize = int32(size(beq));
    beqsize[0] = beq.size(0);
    beqsize[1] = 1;
    // 'c_simplex:26' Csize = int32(size(C));
    Csize[0] = c_f.size(0);
    Csize[1] = 1;
    // 'c_simplex:27' success = int32(0);
    // 'c_simplex:28' status = int32(0);
    // 'c_simplex:29' coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp',
    // '$(START_DIR)/src/'); 'c_simplex:30' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.clp.lflags); 'c_simplex:31' coder.cinclude('cpp_simplex.hpp'); 'c_simplex:32' status
    // = coder.ceval('simplex_solve', coder.rref(f), fsize,... 'c_simplex:33' coder.rref(Avs),
    // coder.rref(Ais), coder.rref(Ajs), Asize, An,... 'c_simplex:34'         coder.rref(b), bsize,
    // coder.rref(beq),beqsize,... 'c_simplex:35'         coder.ref(C), Csize);
    c_status = simplex_solve(&(c_f.data())[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0],
                             &(Ajs.data())[0], &Asize[0], b_n, &(c_b.data())[0], &bsize[0],
                             &(beq.data())[0], &beqsize[0], &Coeff2[0], &Csize[0]);
    //          C = solution.solution;
    // 'c_simplex:37' success = status == 0;
    b_success = (c_status == 0);
    //  Status :
    //        0 : Primal Dual Optimality
    //        1 : Primal Infeasible
    //        2 : Dual Infeasible
    //        3 : Max iteration reached
    //        4 : isAbandoned
    // 'c_simplex:44' c_prof_out(mfilename);
    // 'FeedratePlanning_LP:63' if( ~success )
    if (b_success) {
        double obj;
        int obj2Value_size_idx_1;
        int p_loop_ub;
        int s_loop_ub;
        // 'FeedratePlanning_LP:65' else
        // 'FeedratePlanning_LP:66' Coeff   = reshape( Coeff2( 1 : end -1 ), N, NWindow );
        if (1 > Coeff2.size(0) - 1) {
            p_loop_ub = 0;
        } else {
            p_loop_ub = Coeff2.size(0) - 1;
        }
        b_Coeff2.set_size(1, p_loop_ub);
        for (int i32{0}; i32 < p_loop_ub; i32++) {
            b_Coeff2[i32] = Coeff2[i32];
        }
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), loop_ub_tmp);
        for (int i33{0}; i33 < loop_ub_tmp; i33++) {
            for (int i34{0}; i34 < BasisVal_idx_0; i34++) {
                Coeff[i34 + Coeff.size(0) * i33] = b_Coeff2[i34 + BasisVal_idx_0 * i33];
            }
        }
        // 'FeedratePlanning_LP:67' disp( "slack : " + Coeff2(end) );
        obj = std::round(Coeff2[Coeff2.size(0) - 1]);
        if (obj == 0.0) {
            obj2Value_size_idx_1 = 1;
            obj2Value_data[0] = '0';
        } else {
            int resCount;
            resCount = sprintf(&st[0], "%.16g", obj);
            obj2Value_size_idx_1 = resCount;
            if (0 <= resCount - 1) {
                std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
            }
        }
        for (int i36{0}; i36 < 8; i36++) {
            b_obj.Value.data[i36] = obj1Value[i36];
        }
        if (0 <= obj2Value_size_idx_1 - 1) {
            std::copy(&obj2Value_data[0], &obj2Value_data[obj2Value_size_idx_1],
                      &b_obj.Value.data[8]);
        }
        s_loop_ub = obj2Value_size_idx_1 + 8;
        if (0 <= s_loop_ub - 1) {
            std::copy(&b_obj.Value.data[0], &b_obj.Value.data[s_loop_ub], &varargin_1_data[0]);
        }
        varargin_1_data[obj2Value_size_idx_1 + 8] = '\x00';
        printf("%s\n", &varargin_1_data[0]);
        fflush(stdout);
    } else {
        //  The optimization successed
        // 'FeedratePlanning_LP:64' error( "Second LP failed..." );
    }
    //  Compute the continuity equations
    // 'FeedratePlanning_LP:71' X           = continuity * Coeff( : , 1 );
    inner = continuity.size(1);
    X_idx_0 = 0.0;
    X_idx_1 = 0.0;
    for (int d_k{0}; d_k < inner; d_k++) {
        X_idx_0 += continuity[2 * d_k] * Coeff[d_k];
        X_idx_1 += continuity[2 * d_k + 1] * Coeff[d_k];
    }
    // 'FeedratePlanning_LP:72' ctx.v_0     = sqrt( X( 1, : ) );
    ctx->v_0 = std::sqrt(X_idx_0);
    // 'FeedratePlanning_LP:73' ctx.at_0    = X( 2, : );
    ctx->at_0 = X_idx_1;
    // 'FeedratePlanning_LP:74' ctx.Coeff   = Coeff;
    ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
    q_loop_ub = Coeff.size(1);
    for (int i35{0}; i35 < q_loop_ub; i35++) {
        int r_loop_ub;
        r_loop_ub = Coeff.size(0);
        for (int i37{0}; i37 < r_loop_ub; i37++) {
            ctx->Coeff[i37 + ctx->Coeff.size(0) * i35] = Coeff[i37 + Coeff.size(0) * i35];
        }
    }
    *success = b_success;
    *status = c_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_LP.cpp
//
// [EOF]
//
