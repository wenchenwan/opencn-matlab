//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_v4.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "FeedratePlanning_v4.h"
#include "BuildConstrJerk_v4.h"
#include "BuildConstr_v4.h"
#include "EvalCurvStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_types.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types2.h"
#include "EvalCurvStruct_types3.h"
#include "PrintCurvStruct.h"
#include "bspline_eval.h"
#include "c_simplex.h"
#include "queue_coder.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function [ctx, Coeff, NCoeff, success, status] = FeedratePlanning_v4(ctx, CurvStructs0, amax,
// jmax, ...
//                                      BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec,
//                                      N_Hor)
//
//
// Arguments    : FeedoptContext *ctx
//                const ::coder::array<CurvStruct, 2U> &CurvStructs0
//                const double amax[3]
//                double jmax[3]
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 1U> &BasisIntegr
//                unsigned long Bl_handle
//                const ::coder::array<double, 2U> &u_vec
//                int N_Hor
//                ::coder::array<double, 2U> &Coeff
//                int *NCoeff
//                bool *success
// Return Type  : void
//
namespace ocn {
void FeedratePlanning_v4(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &CurvStructs0,
                         const double amax[3], double jmax[3],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle,
                         const ::coder::array<double, 2U> &u_vec, int N_Hor,
                         ::coder::array<double, 2U> &Coeff, int *NCoeff, bool *success)
{
    coder::sparse A;
    coder::sparse A_jerk;
    coder::sparse r1;
    ::coder::array<CurvStruct, 2U> b_CurvStructs0;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> Coeff2;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_BasisVal;
    ::coder::array<double, 2U> b_BasisValD;
    ::coder::array<double, 2U> b_Coeff2;
    ::coder::array<double, 2U> c_b;
    ::coder::array<double, 2U> d_b;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_jerk;
    ::coder::array<double, 1U> beq;
    double a__1[3];
    double a__2[3];
    double c[3];
    double e_b[3];
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double qD_val;
    double q_val;
    double v3;
    unsigned long u;
    int N;
    int b_NCoeff;
    int b_status;
    int beq_idx_0;
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int loop_ub;
    int status;
    int varargin_2;
    bool b_success;
    bool c_success;
    bool d_success;
    // 'FeedratePlanning_v4:6' c_prof_in(mfilename);
    // 'FeedratePlanning_v4:7' CurvStructs = CurvStructs0(1:N_Hor);
    if (1 > N_Hor) {
        varargin_2 = 0;
    } else {
        varargin_2 = N_Hor;
    }
    // 'FeedratePlanning_v4:8' if ~coder.target('MATLAB')
    // 'FeedratePlanning_v4:9' coder.varsize('CurvStructs', [1, Inf], [0,1]);
    // 'FeedratePlanning_v4:11' Ncrv   = length(CurvStructs);
    // 'FeedratePlanning_v4:12' [~, N] = size(BasisVal);
    N = BasisVal.size(1);
    // 'FeedratePlanning_v4:14' DebugLog(DebugCfg.FeedratePlanning,
    // '===============================\n')
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    u = static_cast<unsigned long>(DebugConfig) & 4UL;
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("===============================\n");
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:15' DebugLog(DebugCfg.FeedratePlanning, '====== FEEDRATE PLANNING
    // ======\n')
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("====== FEEDRATE PLANNING ======\n");
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:16' DebugLog(DebugCfg.FeedratePlanning,
    // '===============================\n')
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("===============================\n");
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:18' DebugLog(DebugCfg.FeedratePlanning, 'v_0  = %f\n', ctx.v_0)
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("v_0  = %f\n", ctx->v_0);
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:19' DebugLog(DebugCfg.FeedratePlanning, 'at_0 = %f\n', ctx.at_0)
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("at_0 = %f\n", ctx->at_0);
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:21' DebugLog(DebugCfg.FeedratePlanning, 'v_1  = %f\n', ctx.v_1)
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("v_1  = %f\n", ctx->v_1);
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:22' DebugLog(DebugCfg.FeedratePlanning, 'at_1 = %f\n', ctx.at_1)
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("at_1 = %f\n", ctx->at_1);
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:24' if IsEnabledDebugLog(DebugCfg.FeedratePlanning)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'FeedratePlanning_v4:25' for k = 1:Ncrv
        for (int k{0}; k < varargin_2; k++) {
            // 'FeedratePlanning_v4:26' PrintCurvStruct(ctx, CurvStructs(k));
            PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                            &CurvStructs0[k]);
        }
    }
    // 'FeedratePlanning_v4:30' DebugLog(DebugCfg.FeedratePlanning,
    // '===============================\n')
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("===============================\n");
        fflush(stdout);
    }
    // 'FeedratePlanning_v4:31' DebugLog(DebugCfg.FeedratePlanning,
    // '===============================\n')
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("===============================\n");
        fflush(stdout);
    }
    //
    //  FIRST setup of Linear Program (LP) WITHOUT jerk constraint
    // 'FeedratePlanning_v4:35' f       = -repmat(BasisIntegr, 1, Ncrv);
    b.set_size(BasisIntegr.size(0), varargin_2);
    if ((BasisIntegr.size(0) != 0) && (varargin_2 != 0)) {
        int i;
        i = varargin_2 - 1;
        for (int t{0}; t <= i; t++) {
            int na;
            na = BasisIntegr.size(0);
            for (int b_k{0}; b_k < na; b_k++) {
                b[b_k + b.size(0) * t] = BasisIntegr[b_k];
            }
        }
    }
    f.set_size(b.size(0), b.size(1));
    loop_ub = b.size(1);
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        int i2;
        int scalarLB;
        int vectorUB;
        b_loop_ub = b.size(0);
        scalarLB = (b.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i2 = 0; i2 <= vectorUB; i2 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&b[i2 + b.size(0) * i1]);
            _mm_storeu_pd(&f[i2 + f.size(0) * i1], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
        }
        for (i2 = scalarLB; i2 < b_loop_ub; i2++) {
            f[i2 + f.size(0) * i1] = -b[i2 + b.size(0) * i1];
        }
    }
    //  maximize integral of q
    //  equality constraints
    // 'FeedratePlanning_v4:37' success = false;
    // 'FeedratePlanning_v4:38' max_increase = 5;
    //  to satisfy the coder
    // 'FeedratePlanning_v4:41' if coder.target('rtw') || coder.target('mex')
    // 'FeedratePlanning_v4:42' coder_A = 0;
    // 'FeedratePlanning_v4:43' coder.varsize('coder_A', [Inf Inf], [1, 1]);
    // 'FeedratePlanning_v4:44' A = sparse(coder_A);
    // 'FeedratePlanning_v4:45' Aeq = coder_A;
    // 'FeedratePlanning_v4:47' coder_b = 0;
    // 'FeedratePlanning_v4:48' coder.varsize('coder_b', [1, Inf], [0, 1]);
    // 'FeedratePlanning_v4:49' b = coder_b;
    // 'FeedratePlanning_v4:50' beq = coder_b;
    // 'FeedratePlanning_v4:51' Coeff0 = zeros(N, Ncrv);
    //  -----------
    // 'FeedratePlanning_v4:56' [A, b, Aeq, beq] = BuildConstr_v4(ctx, CurvStructs, amax, ctx.v_0,
    // ctx.at_0, ctx.v_1, ctx.at_1, ... 'FeedratePlanning_v4:57' BasisVal, BasisValD, u_vec);
    b_CurvStructs0.set_size(1, varargin_2);
    for (int i3{0}; i3 < varargin_2; i3++) {
        b_CurvStructs0[i3] = CurvStructs0[i3];
    }
    b_BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    c_loop_ub = BasisVal.size(1) - 1;
    for (int i4{0}; i4 <= c_loop_ub; i4++) {
        int d_loop_ub;
        d_loop_ub = BasisVal.size(0) - 1;
        for (int i5{0}; i5 <= d_loop_ub; i5++) {
            b_BasisVal[i5 + b_BasisVal.size(0) * i4] = BasisVal[i5 + BasisVal.size(0) * i4];
        }
    }
    b_BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    e_loop_ub = BasisValD.size(1) - 1;
    for (int i6{0}; i6 <= e_loop_ub; i6++) {
        int f_loop_ub;
        f_loop_ub = BasisValD.size(0) - 1;
        for (int i7{0}; i7 <= f_loop_ub; i7++) {
            b_BasisValD[i7 + b_BasisValD.size(0) * i6] = BasisValD[i7 + BasisValD.size(0) * i6];
        }
    }
    int b_idx_0;
    BuildConstr_v4(&ctx->q_splines, ctx->cfg.UseDynamicBreakpoints, ctx->cfg.UseLinearBreakpoints,
                   ctx->cfg.DynamicBreakpointsDistance, ctx->cfg.SplineDegree,
                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, ctx->Bl.ncoeff, ctx->Bl.handle,
                   b_CurvStructs0, amax, ctx->v_0, ctx->at_0, ctx->v_1, ctx->at_1, b_BasisVal,
                   b_BasisValD, u_vec, &A, b_b, Aeq, beq);
    // 'FeedratePlanning_v4:59' if ~coder.target('MATLAB')
    // 'FeedratePlanning_v4:60' coder.varsize('f', [Inf, Inf], [1, 1]);
    // 'FeedratePlanning_v4:62' [Coeff0, success, status] = c_simplex(f, A, b, Aeq, beq);
    b_idx_0 = b_b.size(0);
    beq_idx_0 = beq.size(0);
    c_b.set_size(b_idx_0, 1);
    g_loop_ub = b_idx_0 - 1;
    for (int i8{0}; i8 <= g_loop_ub; i8++) {
        c_b[i8] = b_b[i8];
    }
    ::coder::array<double, 2U> b_beq;
    b_beq = beq.reshape(beq_idx_0, 1);
    c_simplex(f, &A, c_b, Aeq, b_beq, Coeff0, &b_success, &status);
    c_success = b_success;
    //
    //  tic
    //  Coeff1 = linprog(f, A, b, Aeq, beq, [], [], options);
    //  toc Coeff(:, end-N_Hor+2:end) = C(:, 2:end);
    //
    // 'FeedratePlanning_v4:70' if ~success
    if (!b_success) {
        // 'FeedratePlanning_v4:71' Coeff = [];
        Coeff.set_size(0, 0);
        // 'FeedratePlanning_v4:72' NCoeff = int32(0);
        b_NCoeff = 0;
    } else {
        unsigned long u1;
        int i9;
        int max_increase;
        // 'FeedratePlanning_v4:75' Coeff1  = reshape(Coeff0, N, Ncrv);
        // 'FeedratePlanning_v4:76' DebugLog(DebugCfg.Global, 'Coeff1 = ');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        u1 = static_cast<unsigned long>(DebugConfig) & 8UL;
        if (u1 != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Coeff1 = ");
            fflush(stdout);
        }
        // 'FeedratePlanning_v4:77' for k = 1:N
        i9 = BasisVal.size(1);
        for (int c_k{0}; c_k < i9; c_k++) {
            // 'FeedratePlanning_v4:78' DebugLog(DebugCfg.Global, '%.4f ', Coeff1(k, 1));
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("%.4f ", Coeff0[c_k]);
                fflush(stdout);
            }
        }
        // 'FeedratePlanning_v4:80' DebugLog(DebugCfg.Global, '\n')
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if (u1 != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("\n");
            fflush(stdout);
        }
        //  SECOND setup of Linear Program (LP) WITH jerk constraint
        // 'FeedratePlanning_v4:83' success = false;
        c_success = false;
        // 'FeedratePlanning_v4:84' max_increase = 20;
        max_increase = 20;
        // 'FeedratePlanning_v4:86' Coeff2 = zeros(N, Ncrv);
        Coeff2.set_size(BasisVal.size(1), varargin_2);
        for (int i10{0}; i10 < varargin_2; i10++) {
            int h_loop_ub;
            h_loop_ub = BasisVal.size(1);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                Coeff2[i11 + Coeff2.size(0) * i10] = 0.0;
            }
        }
        //  satisfy the coder
        // 'FeedratePlanning_v4:87' while ~success && max_increase > 0
        while ((!c_success) && (max_increase > 0)) {
            int b_input_sizes_idx_0;
            int c_input_sizes_idx_0;
            int input_sizes_idx_0;
            // 'FeedratePlanning_v4:88' [A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs,
            // Coeff1, jmax,  ... 'FeedratePlanning_v4:89' BasisVal, BasisValD, BasisValDD, u_vec);
            b_CurvStructs0.set_size(1, varargin_2);
            for (int i12{0}; i12 < varargin_2; i12++) {
                b_CurvStructs0[i12] = CurvStructs0[i12];
            }
            ::coder::array<double, 2U> b_Coeff0;
            b_Coeff0 = Coeff0.reshape(N, varargin_2);
            BuildConstrJerk_v4(&ctx->q_splines, b_CurvStructs0, b_Coeff0, jmax, BasisVal, BasisValD,
                               BasisValDD, u_vec, &A_jerk, b_jerk);
            //
            // 'FeedratePlanning_v4:92' Atot = [A;
            // 'FeedratePlanning_v4:93'             A_jerk];
            //
            // 'FeedratePlanning_v4:95' btot = [b;
            // 'FeedratePlanning_v4:96'             b_jerk];
            if (b_b.size(0) != 0) {
                input_sizes_idx_0 = b_b.size(0);
            } else {
                input_sizes_idx_0 = 0;
            }
            if (b_jerk.size(0) != 0) {
                b_input_sizes_idx_0 = b_jerk.size(0);
            } else {
                b_input_sizes_idx_0 = 0;
            }
            // 'FeedratePlanning_v4:99' [Coeff2, success, status] = c_simplex(f, Atot, btot, Aeq,
            // beq);
            if (b_b.size(0) != 0) {
                c_input_sizes_idx_0 = b_b.size(0);
            } else {
                c_input_sizes_idx_0 = 0;
            }
            beq_idx_0 = beq.size(0);
            d_b.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, 1);
            for (int i14{0}; i14 < input_sizes_idx_0; i14++) {
                d_b[i14] = b_b[i14];
            }
            for (int i15{0}; i15 < b_input_sizes_idx_0; i15++) {
                d_b[i15 + c_input_sizes_idx_0] = b_jerk[i15];
            }
            ::coder::array<double, 2U> c_beq;
            A.vertcat(&A_jerk, &r1);
            c_beq = beq.reshape(beq_idx_0, 1);
            c_simplex(f, &r1, d_b, Aeq, c_beq, Coeff2, &d_success, &b_status);
            c_success = d_success;
            // 'FeedratePlanning_v4:100' if ~success
            if (!d_success) {
                __m128d r2;
                //          amax = amax*1.1;
                // 'FeedratePlanning_v4:102' ctx.jmax_increase_count = ctx.jmax_increase_count + 1;
                ctx->jmax_increase_count++;
                // 'FeedratePlanning_v4:103' jmax = jmax*2;
                r2 = _mm_loadu_pd(&jmax[0]);
                _mm_storeu_pd(&jmax[0], _mm_mul_pd(r2, _mm_set1_pd(2.0)));
                jmax[2] *= 2.0;
                //  TODO: valeur à ajuster, avant: 1.1...
                // 'FeedratePlanning_v4:104' DebugLog(DebugCfg.Warning, ...
                // 'FeedratePlanning_v4:105'             'WARNING: (Jerk) Increasing jmax to
                // [%f,%f,%f]\n', jmax(1), jmax(2), jmax(3));
                //  1 -> stdout
                //  2 -> stderr
                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                // 'IsEnabledDebugLog:4' value = false;
                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
                    // 'IsEnabledDebugLog:7' value = true;
                    // 'DebugLog:6' fprintf(1, varargin{:});
                    printf("WARNING: (Jerk) Increasing jmax to [%f,%f,%f]\n", jmax[0], jmax[1],
                           jmax[2]);
                    fflush(stdout);
                }
                // 'FeedratePlanning_v4:106' max_increase = max_increase - 1;
                max_increase--;
            }
        }
        // 'FeedratePlanning_v4:111' if ~success
        if (!c_success) {
            // 'FeedratePlanning_v4:112' Coeff = [];
            Coeff.set_size(0, 0);
            // 'FeedratePlanning_v4:113' NCoeff = int32(0);
            b_NCoeff = 0;
        } else {
            __m128d r3;
            __m128d r4;
            double n_tmp;
            double y_tmp;
            int BasisVal_idx_0;
            int i13;
            //
            //  tic
            //  Coeff1 = linprog(f, Atot, btot, Aeq, beq, [], [], options);
            //  toc
            //
            // 'FeedratePlanning_v4:121' Coeff3 = reshape(Coeff2, N, Ncrv);
            // 'FeedratePlanning_v4:122' DebugLog(DebugCfg.Global, 'Coeff3 = ');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Coeff3 = ");
                fflush(stdout);
            }
            // 'FeedratePlanning_v4:123' for k = 1:N
            i13 = BasisVal.size(1);
            for (int d_k{0}; d_k < i13; d_k++) {
                // 'FeedratePlanning_v4:124' DebugLog(DebugCfg.Global, '%.4f ', Coeff3(k, 1));
                //  1 -> stdout
                //  2 -> stderr
                // 'DebugLog:5' if IsEnabledDebugLog(cfg)
                // 'IsEnabledDebugLog:4' value = false;
                // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
                if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                    // 'IsEnabledDebugLog:7' value = true;
                    // 'DebugLog:6' fprintf(1, varargin{:});
                    printf("%.4f ", Coeff2[d_k]);
                    fflush(stdout);
                }
            }
            // 'FeedratePlanning_v4:126' DebugLog(DebugCfg.Global, '\n')
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("\n");
                fflush(stdout);
            }
            //
            // 'FeedratePlanning_v4:128' [v_0, a_0]  = CalcVAJ_v5(ctx, CurvStructs(1), Bl, Coeff3(:,
            // 1), {1});
            //
            //  import splines.*
            //
            //  Ntot = 0;
            //  for k = 1:Ncrv
            //      Ntot = Ntot + size(u_cell{k}, 2);
            //  end
            // 'CalcVAJ_v5:10' v_norm    = zeros(1, 1);
            // 'CalcVAJ_v5:11' a         = zeros(3, 1);
            // 'CalcVAJ_v5:12' j         = zeros(3, 1);
            //  v_norm = [];
            //  a = [];
            //  j = [];
            // 'CalcVAJ_v5:18' index = 1;
            //
            // 'CalcVAJ_v5:21' for k = 1:1
            //      qSpl = Function(Bl, Coeff(:, k));
            // 'CalcVAJ_v5:23' u_vec = u_cell{k};
            //
            // 'CalcVAJ_v5:25' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(k), u_vec);
            c_EvalCurvStruct(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].P0,
                             CurvStructs0[0].P1, CurvStructs0[0].CorrectedHelixCenter,
                             CurvStructs0[0].evec, CurvStructs0[0].theta, CurvStructs0[0].pitch,
                             CurvStructs0[0].CoeffP5, CurvStructs0[0].sp_index,
                             CurvStructs0[0].a_param, CurvStructs0[0].b_param, a__1, r1D, r2D, r3D);
            // 'CalcVAJ_v5:26' r1D_norm             = mysqrt(sum(r1D.^2));
            y_tmp = (std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0);
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            //  norm
            //
            //      q_val   = qSpl.fast_eval(u_vec);
            //      qD_val  = qSpl.derivative.fast_eval(u_vec);
            //      qDD_val = qSpl.derivative(2).fast_eval(u_vec);
            // 'CalcVAJ_v5:32' q_val = zeros(size(u_vec));
            // 'CalcVAJ_v5:33' qD_val = zeros(size(u_vec));
            // 'CalcVAJ_v5:34' qDD_val = zeros(size(u_vec));
            //  TODO: Optimize this with a single call to eval, and maybe a basis
            //  precompute?
            // 'CalcVAJ_v5:38' for iu = 1:numel(u_vec)
            // 'CalcVAJ_v5:39' if CurvStructs.zspdmode==ZSpdMode.ZN
            if (CurvStructs0[0].zspdmode == ZSpdMode_ZN) {
                double a;
                double b_t;
                // 'CalcVAJ_v5:40' t = (6*u_vec(iu)/CurvStructs.ConstJerk)^(1/3);
                b_t = std::pow(6.0 / CurvStructs0[0].ConstJerk, 0.33333333333333331);
                // 'CalcVAJ_v5:41' q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
                a = CurvStructs0[0].ConstJerk * (b_t * b_t) / 2.0;
                q_val = a * a;
                // 'CalcVAJ_v5:42' qD_val(iu) = 2*CurvStructs.ConstJerk*t;
                qD_val = 2.0 * CurvStructs0[0].ConstJerk * b_t;
                // 'CalcVAJ_v5:43' qDD_val(iu) = 4/t^2;
            } else if (CurvStructs0[0].zspdmode == ZSpdMode_NZ) {
                double b_a;
                double b_t;
                // 'CalcVAJ_v5:44' elseif CurvStructs.zspdmode==ZSpdMode.NZ
                // 'CalcVAJ_v5:45' t = (6*(1-u_vec(iu))/CurvStructs.ConstJerk)^(1/3);
                b_t = std::pow(0.0 / CurvStructs0[0].ConstJerk, 0.33333333333333331);
                // 'CalcVAJ_v5:46' q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
                b_a = CurvStructs0[0].ConstJerk * (b_t * b_t) / 2.0;
                q_val = b_a * b_a;
                // 'CalcVAJ_v5:47' qD_val(iu) = -2*CurvStructs.ConstJerk*t;
                qD_val = -2.0 * CurvStructs0[0].ConstJerk * b_t;
                // 'CalcVAJ_v5:48' qDD_val(iu) = 4/t^2;
            } else if (!(CurvStructs0[0].zspdmode == ZSpdMode_ZZ)) {
                int i_loop_ub;
                // 'CalcVAJ_v5:51' else
                //  ZSpdMode.NN
                // 'CalcVAJ_v5:52' [v1, v2, v3] = bspline_eval(Bl, Coeff(:, k)', u_vec(iu));
                q_val = 1.0;
                i_loop_ub = BasisVal.size(1);
                b_Coeff2.set_size(1, BasisVal.size(1));
                for (int i16{0}; i16 < i_loop_ub; i16++) {
                    b_Coeff2[i16] = Coeff2[i16];
                }
                bspline_eval(Bl_handle, b_Coeff2, &q_val, &qD_val, &v3);
                // 'CalcVAJ_v5:53' q_val(iu) = v1;
                // 'CalcVAJ_v5:54' qD_val(iu) = v2;
                // 'CalcVAJ_v5:55' qDD_val(iu) = v3;
            } else {
                // 'CalcVAJ_v5:49' elseif CurvStructs.zspdmode==ZSpdMode.ZZ
                // 'CalcVAJ_v5:50' error('Should not get here');
            }
            // 'CalcVAJ_v5:61' q_val = q_val';
            // 'CalcVAJ_v5:62' qD_val = qD_val';
            // 'CalcVAJ_v5:63' qDD_val = qDD_val';
            // 'CalcVAJ_v5:65' tmp1 = bsxfun(@times, r1D_norm, mysqrt(q_val'));
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'CalcVAJ_v5:66' tmp2 = bsxfun(@times, r2D, q_val') + 0.5*bsxfun(@times, r1D,
            // qD_val');
            r3 = _mm_loadu_pd(&r1D[0]);
            _mm_storeu_pd(&e_b[0], _mm_mul_pd(r3, _mm_set1_pd(qD_val)));
            r4 = _mm_loadu_pd(&r2D[0]);
            _mm_storeu_pd(&c[0], _mm_mul_pd(r4, _mm_set1_pd(q_val)));
            e_b[2] = r1D[2] * qD_val;
            // 'CalcVAJ_v5:67' tmp3 = bsxfun(@times, r3D, (q_val.^(3/2))') + ...
            // 'CalcVAJ_v5:68'             1.5*bsxfun(@times, r2D, bsxfun(@times,
            // qD_val',mysqrt(q_val)')) + ... 'CalcVAJ_v5:69'             0.5*bsxfun(@times, r1D,
            // bsxfun(@times, qDD_val',mysqrt(q_val)')); 'mysqrt:3' y = sqrt(x); 'mysqrt:4'
            // sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'CalcVAJ_v5:71' v_norm = tmp1;
            // 'CalcVAJ_v5:72' a = tmp2;
            // zeros(3, size(tmp2, 2));
            // 'CalcVAJ_v5:73' j = tmp3;
            // 'FeedratePlanning_v4:129' [~, r1D]         = EvalCurvStruct(ctx, CurvStructs(1), 1);
            b_EvalCurvStruct(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].P0,
                             CurvStructs0[0].P1, CurvStructs0[0].CorrectedHelixCenter,
                             CurvStructs0[0].evec, CurvStructs0[0].theta, CurvStructs0[0].pitch,
                             CurvStructs0[0].CoeffP5, CurvStructs0[0].sp_index,
                             CurvStructs0[0].a_param, CurvStructs0[0].b_param, a__2, r1D);
            // 'FeedratePlanning_v4:130' t_end            = r1D/MyNorm(r1D);
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            // 'mysqrt:3' y = sqrt(x);
            n_tmp =
                std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            //  unit tangential vector
            // 'FeedratePlanning_v4:131' at_0 = a_0'*t_end;
            ctx->at_0 = ((c[0] + 0.5 * e_b[0]) * (r1D[0] / n_tmp) +
                         (c[1] + 0.5 * e_b[1]) * (r1D[1] / n_tmp)) +
                        (r2D[2] * q_val + 0.5 * e_b[2]) * (r1D[2] / n_tmp);
            //  tangential acceleration at the end of first piece in horizon
            // 'FeedratePlanning_v4:132' ctx.v_0 = v_0;
            ctx->v_0 = std::sqrt(y_tmp) * std::sqrt(q_val);
            // 'FeedratePlanning_v4:133' ctx.at_0 = at_0;
            //  Coeff = Coeff3(:, 1);
            //  Coeff = zeros(FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz);
            //  coder.varsize('Coeff', [Inf, Inf], [1,1]);
            // 'FeedratePlanning_v4:137' Coeff = Coeff3;
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), varargin_2);
            for (int i17{0}; i17 < varargin_2; i17++) {
                for (int i18{0}; i18 < BasisVal_idx_0; i18++) {
                    Coeff[i18 + Coeff.size(0) * i17] = Coeff2[i18 + BasisVal_idx_0 * i17];
                }
            }
            // 'FeedratePlanning_v4:138' NCoeff = int32(N);
            b_NCoeff = BasisVal.size(1);
            // 'FeedratePlanning_v4:139' c_prof_out(mfilename);
        }
    }
    *NCoeff = b_NCoeff;
    *success = c_success;
}

} // namespace ocn

//
// File trailer for FeedratePlanning_v4.cpp
//
// [EOF]
//
