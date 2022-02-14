//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_v4.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "FeedratePlanning_v4.h"
#include "BuildConstrJerk_v4.h"
#include "BuildConstr_v4.h"
#include "CalcVAJ_v5.h"
#include "DebugLog.h"
#include "EvalCurvStruct.h"
#include "PrintCurvStruct.h"
#include "c_simplex.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
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
    coder::sparse Atot;
    ::coder::array<CurvStruct, 2U> b_CurvStructs0;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> Coeff2;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_BasisVal;
    ::coder::array<double, 2U> b_BasisValD;
    ::coder::array<double, 2U> c_b;
    ::coder::array<double, 2U> d_b;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 1U> b_Coeff2;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_jerk;
    ::coder::array<double, 1U> beq;
    double a_0[3];
    double a__2[3];
    double r1D[3];
    double v_0;
    int b_NCoeff;
    int b_loop_ub;
    int b_status;
    int beq_idx_0;
    int d_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int loop_ub;
    int status;
    bool b_success;
    bool c_success;
    bool d_success;
    if (1 > N_Hor) {
        loop_ub = 0;
    } else {
        loop_ub = N_Hor;
    }
    w_DebugLog();
    x_DebugLog();
    w_DebugLog();
    DebugLog(ctx->v_0);
    b_DebugLog(ctx->at_0);
    c_DebugLog(ctx->v_1);
    d_DebugLog(ctx->at_1);
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        for (int k{0}; k < loop_ub; k++) {
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                              &CurvStructs0[k]);
        }
    }
    w_DebugLog();
    w_DebugLog();
    //
    //  FIRST setup of Linear Program (LP) WITHOUT jerk constraint
    b.set_size(BasisIntegr.size(0), loop_ub);
    if ((BasisIntegr.size(0) != 0) && (loop_ub != 0)) {
        int i;
        i = loop_ub - 1;
        for (int t{0}; t <= i; t++) {
            int na;
            na = BasisIntegr.size(0);
            for (int b_k{0}; b_k < na; b_k++) {
                b[b_k + b.size(0) * t] = BasisIntegr[b_k];
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
    //  maximize integral of q
    //  equality constraints
    //  to satisfy the coder
    //  -----------
    b_CurvStructs0.set_size(1, loop_ub);
    for (int i3{0}; i3 < loop_ub; i3++) {
        b_CurvStructs0[i3] = CurvStructs0[i3];
    }
    b_BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
    d_loop_ub = BasisVal.size(1) - 1;
    for (int i4{0}; i4 <= d_loop_ub; i4++) {
        int e_loop_ub;
        e_loop_ub = BasisVal.size(0) - 1;
        for (int i5{0}; i5 <= e_loop_ub; i5++) {
            b_BasisVal[i5 + b_BasisVal.size(0) * i4] = BasisVal[i5 + BasisVal.size(0) * i4];
        }
    }
    b_BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
    f_loop_ub = BasisValD.size(1) - 1;
    for (int i6{0}; i6 <= f_loop_ub; i6++) {
        int g_loop_ub;
        g_loop_ub = BasisValD.size(0) - 1;
        for (int i7{0}; i7 <= g_loop_ub; i7++) {
            b_BasisValD[i7 + b_BasisValD.size(0) * i6] = BasisValD[i7 + BasisValD.size(0) * i6];
        }
    }
    int b_idx_0;
    BuildConstr_v4(&ctx->q_splines, ctx->cfg.UseDynamicBreakpoints, ctx->cfg.UseLinearBreakpoints,
                   ctx->cfg.DynamicBreakpointsDistance, ctx->cfg.SplineDegree,
                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, ctx->Bl.ncoeff, ctx->Bl.handle,
                   b_CurvStructs0, amax, ctx->v_0, ctx->at_0, ctx->v_1, ctx->at_1, b_BasisVal,
                   b_BasisValD, u_vec, &A, b_b, Aeq, beq);
    b_idx_0 = b_b.size(0);
    beq_idx_0 = beq.size(0);
    c_b.set_size(b_idx_0, 1);
    h_loop_ub = b_idx_0 - 1;
    for (int i8{0}; i8 <= h_loop_ub; i8++) {
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
    if (!b_success) {
        Coeff.set_size(0, 0);
        b_NCoeff = 0;
    } else {
        int i9;
        int max_increase;
        y_DebugLog();
        i9 = BasisVal.size(1);
        for (int c_k{0}; c_k < i9; c_k++) {
            e_DebugLog(Coeff0[c_k]);
        }
        ab_DebugLog();
        //  SECOND setup of Linear Program (LP) WITH jerk constraint
        c_success = false;
        max_increase = 20;
        Coeff2.set_size(BasisVal.size(1), loop_ub);
        for (int i10{0}; i10 < loop_ub; i10++) {
            int i_loop_ub;
            i_loop_ub = BasisVal.size(1);
            for (int i11{0}; i11 < i_loop_ub; i11++) {
                Coeff2[i11 + Coeff2.size(0) * i10] = 0.0;
            }
        }
        //  satisfy the coder
        while ((!c_success) && (max_increase > 0)) {
            int N_idx_0;
            int b_input_sizes_idx_0;
            int c_input_sizes_idx_0;
            int cnfixeddim;
            int cnnz;
            int cnvardim;
            int i19;
            int input_sizes_idx_0;
            int numalloc;
            int nzCount;
            bool allEmpty;
            bool b_isAcceptableEmpty_tmp;
            bool emptyflag_idx_0;
            bool emptyflag_idx_1;
            bool isAcceptableEmpty_tmp;
            N_idx_0 = BasisVal.size(1);
            b_CurvStructs0.set_size(1, loop_ub);
            for (int i12{0}; i12 < loop_ub; i12++) {
                b_CurvStructs0[i12] = CurvStructs0[i12];
            }
            ::coder::array<double, 2U> b_Coeff0;
            b_Coeff0 = Coeff0.reshape(N_idx_0, loop_ub);
            BuildConstrJerk_v4(&ctx->q_splines, b_CurvStructs0, b_Coeff0, jmax, BasisVal, BasisValD,
                               BasisValDD, u_vec, &A_jerk, b_jerk);
            //
            cnfixeddim = A.n;
            if ((A.m == 0) || (A.n == 0)) {
                isAcceptableEmpty_tmp = true;
            } else {
                isAcceptableEmpty_tmp = false;
            }
            if ((A_jerk.m == 0) || (A_jerk.n == 0)) {
                b_isAcceptableEmpty_tmp = true;
            } else {
                b_isAcceptableEmpty_tmp = false;
            }
            allEmpty = (isAcceptableEmpty_tmp && b_isAcceptableEmpty_tmp);
            if ((!b_isAcceptableEmpty_tmp) && isAcceptableEmpty_tmp) {
                cnfixeddim = A_jerk.n;
            }
            cnnz = 0;
            cnvardim = 0;
            if (allEmpty || (!isAcceptableEmpty_tmp)) {
                cnnz = A.colidx[A.colidx.size(0) - 1] - 1;
                cnvardim = A.m;
            }
            if (allEmpty || (!b_isAcceptableEmpty_tmp)) {
                cnnz = (cnnz + A_jerk.colidx[A_jerk.colidx.size(0) - 1]) - 1;
                cnvardim += A_jerk.m;
            }
            Atot.m = cnvardim;
            Atot.n = cnfixeddim;
            if (cnnz >= 1) {
                numalloc = cnnz;
            } else {
                numalloc = 1;
            }
            Atot.d.set_size(numalloc);
            for (int i16{0}; i16 < numalloc; i16++) {
                Atot.d[i16] = 0.0;
            }
            Atot.maxnz = numalloc;
            Atot.colidx.set_size(cnfixeddim + 1);
            Atot.colidx[0] = 1;
            Atot.rowidx.set_size(numalloc);
            for (int i18{0}; i18 < numalloc; i18++) {
                Atot.rowidx[i18] = 0;
            }
            for (int c{0}; c < cnfixeddim; c++) {
                Atot.colidx[c + 1] = 1;
            }
            i19 = Atot.colidx.size(0);
            for (int b_c{0}; b_c <= i19 - 2; b_c++) {
                Atot.colidx[b_c] = 1;
            }
            Atot.colidx[Atot.colidx.size(0) - 1] = 1;
            nzCount = -1;
            if ((A.m == 0) || (A.n == 0)) {
                emptyflag_idx_0 = true;
            } else {
                emptyflag_idx_0 = false;
            }
            if ((A_jerk.m == 0) || (A_jerk.n == 0)) {
                emptyflag_idx_1 = true;
            } else {
                emptyflag_idx_1 = false;
            }
            for (int ccol{0}; ccol < cnfixeddim; ccol++) {
                int crowoffs;
                int kpend;
                int kpstart;
                crowoffs = 0;
                if (!emptyflag_idx_0) {
                    int kpend_tmp;
                    kpstart = A.colidx[ccol];
                    kpend_tmp = A.colidx[ccol + 1];
                    kpend = kpend_tmp - 1;
                    for (int kp{kpstart}; kp <= kpend; kp++) {
                        int i20;
                        i20 = ((nzCount + kp) - kpstart) + 1;
                        Atot.rowidx[i20] = A.rowidx[kp - 1];
                        Atot.d[i20] = A.d[kp - 1];
                    }
                    nzCount = (nzCount + kpend_tmp) - A.colidx[ccol];
                    crowoffs = A.m;
                }
                if (!emptyflag_idx_1) {
                    int b_kpend_tmp;
                    kpstart = A_jerk.colidx[ccol];
                    b_kpend_tmp = A_jerk.colidx[ccol + 1];
                    kpend = b_kpend_tmp - 1;
                    for (int b_kp{kpstart}; b_kp <= kpend; b_kp++) {
                        int i21;
                        i21 = ((nzCount + b_kp) - kpstart) + 1;
                        Atot.rowidx[i21] = A_jerk.rowidx[b_kp - 1] + crowoffs;
                        Atot.d[i21] = A_jerk.d[b_kp - 1];
                    }
                    nzCount = (nzCount + b_kpend_tmp) - A_jerk.colidx[ccol];
                }
                Atot.colidx[ccol + 1] = nzCount + 2;
            }
            //
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
            if (b_b.size(0) != 0) {
                c_input_sizes_idx_0 = b_b.size(0);
            } else {
                c_input_sizes_idx_0 = 0;
            }
            beq_idx_0 = beq.size(0);
            d_b.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, 1);
            for (int i22{0}; i22 < input_sizes_idx_0; i22++) {
                d_b[i22] = b_b[i22];
            }
            for (int i23{0}; i23 < b_input_sizes_idx_0; i23++) {
                d_b[i23 + c_input_sizes_idx_0] = b_jerk[i23];
            }
            ::coder::array<double, 2U> c_beq;
            c_beq = beq.reshape(beq_idx_0, 1);
            c_simplex(f, &Atot, d_b, Aeq, c_beq, Coeff2, &d_success, &b_status);
            c_success = d_success;
            if (!d_success) {
                __m128d r1;
                //          amax = amax*1.1;
                ctx->jmax_increase_count++;
                r1 = _mm_loadu_pd(&jmax[0]);
                _mm_storeu_pd(&jmax[0], _mm_mul_pd(r1, _mm_set1_pd(2.0)));
                jmax[2] *= 2.0;
                //  TODO: valeur à ajuster, avant: 1.1...
                DebugLog(jmax[0], jmax[1], jmax[2]);
                max_increase--;
            }
        }
        if (!c_success) {
            Coeff.set_size(0, 0);
            b_NCoeff = 0;
        } else {
            int BasisVal_idx_0;
            int i13;
            int j_loop_ub;
            //
            //  tic
            //  Coeff1 = linprog(f, Atot, btot, Aeq, beq, [], [], options);
            //  toc
            //
            bb_DebugLog();
            i13 = BasisVal.size(1);
            for (int d_k{0}; d_k < i13; d_k++) {
                e_DebugLog(Coeff2[d_k]);
            }
            ab_DebugLog();
            //
            j_loop_ub = BasisVal.size(1);
            b_Coeff2.set_size(BasisVal.size(1));
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                b_Coeff2[i14] = Coeff2[i14];
            }
            double n;
            CalcVAJ_v5(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].zspdmode,
                       CurvStructs0[0].P0, CurvStructs0[0].P1, CurvStructs0[0].CorrectedHelixCenter,
                       CurvStructs0[0].evec, CurvStructs0[0].theta, CurvStructs0[0].pitch,
                       CurvStructs0[0].CoeffP5, CurvStructs0[0].sp_index, CurvStructs0[0].ConstJerk,
                       CurvStructs0[0].a_param, CurvStructs0[0].b_param, Bl_handle, b_Coeff2, &v_0,
                       a_0);
            c_EvalCurvStruct(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].P0,
                             CurvStructs0[0].P1, CurvStructs0[0].CorrectedHelixCenter,
                             CurvStructs0[0].evec, CurvStructs0[0].theta, CurvStructs0[0].pitch,
                             CurvStructs0[0].CoeffP5, CurvStructs0[0].sp_index,
                             CurvStructs0[0].a_param, CurvStructs0[0].b_param, a__2, r1D);
            n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
            sqrt_calls++;
            //  unit tangential vector
            ctx->at_0 = (a_0[0] * (r1D[0] / n) + a_0[1] * (r1D[1] / n)) + a_0[2] * (r1D[2] / n);
            //  tangential acceleration at the end of first piece in horizon
            ctx->v_0 = v_0;
            //  Coeff = Coeff3(:, 1);
            //  Coeff = zeros(FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz);
            //  coder.varsize('Coeff', [Inf, Inf], [1,1]);
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), loop_ub);
            for (int i15{0}; i15 < loop_ub; i15++) {
                for (int i17{0}; i17 < BasisVal_idx_0; i17++) {
                    Coeff[i17 + Coeff.size(0) * i15] = Coeff2[i17 + BasisVal_idx_0 * i15];
                }
            }
            b_NCoeff = BasisVal.size(1);
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
