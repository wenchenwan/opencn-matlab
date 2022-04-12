//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:46:02
//

// Include Files
#include "FeedratePlanning.h"
#include "BuildConstrJerkWithSlacks.h"
#include "BuildConstrJerk_v4.h"
#include "BuildConstr_v4.h"
#include "EvalCurvStruct.h"
#include "bspline_eval.h"
#include "c_simplex.h"
#include "find.h"
#include "locBsearch.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sparse1.h"
#include "coder_array.h"
#include "cpp_simplex.hpp"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function [ctx, Coeff, NCoeff, success, status, msg] = ...
//     FeedratePlanning( ctx, CurvStructsArray, amax, jmax, BasisVal, ...
//     BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor)
//
// FeedratePlanning :
//
//  Inputs
//  ctx               : The context
//  CurvStructsArray  : Array of structures
//  amax              : Acceleration maximum
//  jmax              : Jerk maximum
//  BasisVal          : Functions basis evaluated
//  BasisValD         : 1st derivative
//  BasisValDD        : 2nd derivative
//  BasisIntegr       : Integral
//  Bl                : B-spline
//  u_vec             : Knot vector
//  N_Hor             : Number of windows (horizon)
//
//  Outputs
//  ctx               : See before
//  Coeff             : Result of the optimization
//  NCoeff            : Number of coefficients
//  success           : Result of the optimization
//                    0 : Fails of the optimization
//                    1 : Success of the optimization
//  status            : returned structure by the optimizer
//  msg               : Message on the optimiztion process
//
// Arguments    : FeedoptContext *ctx
//                const ::coder::array<CurvStruct, 2U> &CurvStructsArray
//                const double amax[3]
//                const double jmax[3]
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
//                int *status
// Return Type  : void
//
namespace ocn {
void FeedratePlanning(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &CurvStructsArray,
                      const double amax[3], const double jmax[3],
                      const ::coder::array<double, 2U> &BasisVal,
                      const ::coder::array<double, 2U> &BasisValD,
                      const ::coder::array<double, 2U> &BasisValDD,
                      const ::coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle,
                      const ::coder::array<double, 2U> &u_vec, int N_Hor,
                      ::coder::array<double, 2U> &Coeff, int *NCoeff, bool *success, int *status)
{
    coder::sparse A;
    coder::sparse A_jerk;
    coder::sparse Atot;
    coder::sparse b_A;
    coder::sparse b_Atot;
    coder::sparse r3;
    coder::sparse r5;
    ::coder::array<CurvStruct, 2U> b_CurvStructsArray;
    ::coder::array<double, 2U> Aeq;
    ::coder::array<double, 2U> Coeff0;
    ::coder::array<double, 2U> Coeff2;
    ::coder::array<double, 2U> Coeff3;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_BasisVal;
    ::coder::array<double, 2U> b_BasisValD;
    ::coder::array<double, 2U> b_Coeff;
    ::coder::array<double, 2U> b_Coeff3;
    ::coder::array<double, 2U> f;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 1U> Avs;
    ::coder::array<double, 1U> b_b;
    ::coder::array<double, 1U> b_jerk;
    ::coder::array<double, 1U> beq;
    ::coder::array<double, 1U> btot;
    ::coder::array<double, 1U> c_b;
    ::coder::array<double, 1U> ftot;
    ::coder::array<unsigned int, 2U> b_y;
    ::coder::array<unsigned int, 2U> y;
    ::coder::array<int, 1U> Ais;
    ::coder::array<int, 1U> Ajs;
    ::coder::array<int, 1U> ii;
    ::coder::array<int, 1U> jj;
    double a__1[3];
    double a__2[3];
    double c[3];
    double d_b[3];
    double jmaxNew[3];
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double qD_val;
    double q_val;
    double v3;
    int Asize[2];
    int Csize[2];
    int beqsize[2];
    int bsize[2];
    int fsize[2];
    int BasisVal_idx_0;
    int b_NCoeff;
    int b_loop_ub;
    int b_status;
    int c_status;
    int d_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int m_tmp;
    int vidx;
    char st[12];
    bool b_success;
    bool c_success;
    bool d_success;
    bool found;
    // 'FeedratePlanning:29' [ctx, Coeff, NCoeff, success, status, msg] = ...
    // 'FeedratePlanning:30'     FeedratePlanning_LP( ctx, CurvStructsArray, amax, jmax, BasisVal,
    // ... 'FeedratePlanning:31'     BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor);
    //  FeedratePlanning_LP : Perform the feedrate planning based on the LP
    //  formulation. A two stage scheme is performed (with and without jerk
    //  constraints).
    //
    //  Inputs
    //  ctx               : The context
    //  CurvStructsArray  : Array of structures
    //  amax              : Acceleration maximum
    //  jmax              : Jerk maximum
    //  BasisVal          : Functions basis evaluated
    //  BasisValD         : 1st derivative
    //  BasisValDD        : 2nd derivative
    //  BasisIntegr       : Integral
    //  Bl                : B-spline
    //  u_vec             : Knot vector
    //  N_Hor             : Number of windows (horizon)
    //
    //  Outputs
    //  ctx               : See before
    //  Coeff             : Result of the optimization
    //  NCoeff            : Number of coefficients
    //  success           : Result of the optimization
    //                    0 : Fails of the optimization
    //                    1 : Success of the optimization
    //  status            : returned structure by the optimizer
    //  msg               : Message on the optimiztion process
    //  0) Initialization of the problem
    // 'FeedratePlanning_LP:33' LP = ctx.cfg.opt;
    //  Load parameters of the LP
    // 'FeedratePlanning_LP:35' [~, NCoeff0] = size( BasisVal );
    //  Extract size of the problem
    // 'FeedratePlanning_LP:37' CurvStructs = CurvStructsArray( 1 : N_Hor );
    if (1 > N_Hor) {
        loop_ub = 0;
    } else {
        loop_ub = N_Hor;
    }
    //  Extract window of interest
    // 'FeedratePlanning_LP:39' f = -repmat( BasisIntegr, 1, N_Hor );
    b.set_size(BasisIntegr.size(0), N_Hor);
    if ((BasisIntegr.size(0) != 0) && (N_Hor != 0)) {
        int i;
        i = N_Hor - 1;
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
    //  Linear pernalty
    //  1) Optimization : first LP
    //  Constraints
    //  [A, b, Aeq, beq] = BuildConstr(ctx, CurvStructs, amax, ctx.v_0, ...
    //                              ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, ...
    //                              BasisValD, u_vec);
    //  A = sparse( A );
    // b = full( b ); beq = full( beq ); %Aeq = full( Aeq );
    // 'FeedratePlanning_LP:51' [A, b, Aeq, beq ] = BuildConstr_v4(ctx, CurvStructs, amax, ctx.v_0,
    // ... 'FeedratePlanning_LP:52'     ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, ...
    // 'FeedratePlanning_LP:53'     BasisValD, u_vec);
    b_CurvStructsArray.set_size(1, loop_ub);
    for (int i3{0}; i3 < loop_ub; i3++) {
        b_CurvStructsArray[i3] = CurvStructsArray[i3];
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
    BuildConstr_v4(&ctx->q_splines, ctx->cfg.UseDynamicBreakpoints, ctx->cfg.UseLinearBreakpoints,
                   ctx->cfg.DynamicBreakpointsDistance, ctx->cfg.SplineDegree,
                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                   ctx->cfg.opt.ACC_RAMP_OVER_WINDOWS, ctx->cfg.opt.VEL_RAMP_OVER_WINDOWS,
                   ctx->Bl.ncoeff, ctx->Bl.handle, b_CurvStructsArray, amax, ctx->v_0, ctx->at_0,
                   ctx->v_1, ctx->at_1, b_BasisVal, b_BasisValD, u_vec, &A, b_b, Aeq, beq);
    // 'FeedratePlanning_LP:55' A = [-1 * eye( size(A,2) ); A];
    m_tmp = A.n;
    b.set_size(A.n, A.n);
    for (int i8{0}; i8 < m_tmp; i8++) {
        for (int i9{0}; i9 < m_tmp; i9++) {
            b[i9 + b.size(0) * i8] = 0.0;
        }
    }
    if (A.n > 0) {
        for (int b_k{0}; b_k < m_tmp; b_k++) {
            b[b_k + b.size(0) * b_k] = 1.0;
        }
    }
    r1.set_size(b.size(0), b.size(1));
    h_loop_ub = b.size(1);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        int b_scalarLB;
        int b_vectorUB;
        int i11;
        int i_loop_ub;
        i_loop_ub = b.size(0);
        b_scalarLB = (b.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i11 = 0; i11 <= b_vectorUB; i11 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&b[i11 + b.size(0) * i10]);
            _mm_storeu_pd(&r1[i11 + r1.size(0) * i10], _mm_mul_pd(r2, _mm_set1_pd(-1.0)));
        }
        for (i11 = b_scalarLB; i11 < i_loop_ub; i11++) {
            r1[i11 + r1.size(0) * i10] = -b[i11 + b.size(0) * i10];
        }
    }
    A.vertcat(r1, &b_A);
    // 'FeedratePlanning_LP:56' b = [zeros( size(A,2), 1 ) ; b];
    c_b.set_size(b_A.n + b_b.size(0));
    j_loop_ub = b_A.n;
    for (int i12{0}; i12 < j_loop_ub; i12++) {
        c_b[i12] = 0.0;
    }
    k_loop_ub = b_b.size(0);
    for (int i13{0}; i13 < k_loop_ub; i13++) {
        c_b[i13 + b_A.n] = b_b[i13];
    }
    // 'FeedratePlanning_LP:58' [Coeff0, success, status, msg] = c_simplex(f, A, b, Aeq, beq, ctx);
    c_simplex(f, &b_A, c_b, Aeq, beq, Coeff0, &b_success, &b_status);
    //  if( ~success ) % Return if optimization fails
    //      printMSG( "\t First LP | "); ctx.at_1 = [];
    //      Coeff = []; NCoeff = int32(0); return;
    //  end
    // 'FeedratePlanning_LP:65' Coeff1  = reshape(Coeff0, NCoeff0, N_Hor);
    //  2) Optimization : second LP
    // 'FeedratePlanning_LP:69' [A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff1,...
    // 'FeedratePlanning_LP:70'                    jmax, BasisVal, BasisValD, BasisValDD, u_vec);
    BasisVal_idx_0 = BasisVal.size(1);
    b_CurvStructsArray.set_size(1, loop_ub);
    for (int i14{0}; i14 < loop_ub; i14++) {
        b_CurvStructsArray[i14] = CurvStructsArray[i14];
    }
    ::coder::array<double, 2U> b_Coeff0;
    b_Coeff0 = Coeff0.reshape(BasisVal_idx_0, N_Hor);
    BuildConstrJerk_v4(&ctx->q_splines, b_CurvStructsArray, b_Coeff0, jmax, BasisVal, BasisValD,
                       BasisValDD, u_vec, &A_jerk, b_jerk);
    // 'FeedratePlanning_LP:72' Atot = [A; A_jerk];
    // 'FeedratePlanning_LP:72' btot = [b; b_jerk];
    // 'FeedratePlanning_LP:74' [Coeff2, success, status, msg] = c_simplex(f, Atot, btot, ...
    // 'FeedratePlanning_LP:75'                                  Aeq, beq, ctx);
    b_b.set_size(c_b.size(0) + b_jerk.size(0));
    l_loop_ub = c_b.size(0);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        b_b[i15] = c_b[i15];
    }
    m_loop_ub = b_jerk.size(0);
    for (int i16{0}; i16 < m_loop_ub; i16++) {
        b_b[i16 + c_b.size(0)] = b_jerk[i16];
    }
    b_A.vertcat(&A_jerk, &r3);
    c_simplex(f, &r3, b_b, Aeq, beq, Coeff2, &c_success, &c_status);
    d_success = c_success;
    // 'FeedratePlanning_LP:77' if( ~success )
    if (!c_success) {
        // 'FeedratePlanning_LP:78' printMSG( "\t Second LP | k : " + ctx.k0 );
        sprintf(&st[0], "%d", ctx->k0);
        // 'FeedratePlanning_LP:80' if( LP.USE_SLACK_ON_JERK )
        if (ctx->cfg.opt.USE_SLACK_ON_JERK) {
            int ab_loop_ub;
            int b_f;
            int bb_loop_ub;
            int cb_loop_ub;
            int e_scalarLB;
            int e_vectorUB;
            int f_scalarLB;
            int f_vectorUB;
            int i43;
            int i44;
            int i45;
            int input_sizes_idx_1;
            int n;
            int n_loop_ub;
            int result;
            int rhsIter_col;
            int rhsIter_idx;
            int rhsIter_row;
            int sm;
            int sn;
            int t_loop_ub;
            int u_loop_ub;
            int v_loop_ub;
            int x_loop_ub;
            int y_loop_ub;
            signed char b_input_sizes_idx_1;
            bool empty_non_axis_sizes;
            //  Create jerk constraints
            // 'FeedratePlanning_LP:83' [A_jerk, b_jerk] = BuildConstrJerkWithSlacks( ctx,
            // CurvStructs,... 'FeedratePlanning_LP:84'             Coeff1, jmax, BasisVal,
            // BasisValD, BasisValDD, u_vec ... 'FeedratePlanning_LP:85'             );
            BasisVal_idx_0 = BasisVal.size(1);
            b_CurvStructsArray.set_size(1, loop_ub);
            for (int i19{0}; i19 < loop_ub; i19++) {
                b_CurvStructsArray[i19] = CurvStructsArray[i19];
            }
            ::coder::array<double, 2U> c_Coeff0;
            c_Coeff0 = Coeff0.reshape(BasisVal_idx_0, N_Hor);
            BuildConstrJerkWithSlacks(&ctx->q_splines, b_CurvStructsArray, c_Coeff0, jmax, BasisVal,
                                      BasisValD, BasisValDD, u_vec, &A_jerk, b_jerk);
            // 'FeedratePlanning_LP:87' Aeq_tot = [Aeq zeros(size(Aeq,1),1)];
            if ((Aeq.size(0) != 0) && (Aeq.size(1) != 0)) {
                result = Aeq.size(0);
            } else if (Aeq.size(0) != 0) {
                result = Aeq.size(0);
            } else {
                result = 0;
            }
            empty_non_axis_sizes = (result == 0);
            if (empty_non_axis_sizes || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
                input_sizes_idx_1 = Aeq.size(1);
            } else {
                input_sizes_idx_1 = 0;
            }
            if (empty_non_axis_sizes || (Aeq.size(0) != 0)) {
                b_input_sizes_idx_1 = 1;
            } else {
                b_input_sizes_idx_1 = 0;
            }
            // 'FeedratePlanning_LP:89' Atot = [zeros(size(A,1), size(A_jerk,2)); A_jerk];
            r1.set_size(b_A.m, A_jerk.n);
            n_loop_ub = A_jerk.n;
            for (int i23{0}; i23 < n_loop_ub; i23++) {
                int o_loop_ub;
                o_loop_ub = b_A.m;
                for (int i24{0}; i24 < o_loop_ub; i24++) {
                    r1[i24 + r1.size(0) * i23] = 0.0;
                }
            }
            A_jerk.vertcat(r1, &Atot);
            // 'FeedratePlanning_LP:91' Atot(1 : size(A,1), 1 : size(A,2)) = A;
            if (b_A.m < 1) {
                y.set_size(1, 0);
            } else {
                int p_loop_ub;
                y.set_size(1, b_A.m);
                p_loop_ub = b_A.m - 1;
                for (int i25{0}; i25 <= p_loop_ub; i25++) {
                    y[i25] = i25 + 1U;
                }
            }
            if (b_A.n < 1) {
                b_y.set_size(1, 0);
            } else {
                int r_loop_ub;
                b_y.set_size(1, b_A.n);
                r_loop_ub = b_A.n - 1;
                for (int i27{0}; i27 <= r_loop_ub; i27++) {
                    b_y[i27] = i27 + 1U;
                }
            }
            sm = y.size(1);
            sn = b_y.size(1);
            rhsIter_idx = 1;
            rhsIter_col = 1;
            rhsIter_row = 1;
            for (int cidx{0}; cidx < sn; cidx++) {
                int nt;
                nt = static_cast<int>(b_y[cidx]);
                for (int ridx{0}; ridx < sm; ridx++) {
                    double rhsv;
                    double thisv;
                    int b_nt;
                    int b_rhsIter_col;
                    int b_rhsIter_row;
                    int iter_idx;
                    b_nt = static_cast<int>(y[ridx]);
                    coder::sparse_locBsearch(Atot.rowidx, b_nt, Atot.colidx[nt - 1],
                                             Atot.colidx[nt], &vidx, &found);
                    if (found) {
                        thisv = Atot.d[vidx - 1];
                    } else {
                        thisv = 0.0;
                    }
                    iter_idx = rhsIter_idx;
                    if ((rhsIter_idx < b_A.colidx[rhsIter_col]) &&
                        (rhsIter_idx <= b_A.colidx[b_A.colidx.size(0) - 1] - 1) &&
                        (rhsIter_row == b_A.rowidx[rhsIter_idx - 1])) {
                        rhsv = b_A.d[rhsIter_idx - 1];
                        iter_idx = rhsIter_idx + 1;
                    } else {
                        rhsv = 0.0;
                    }
                    b_rhsIter_col = rhsIter_col;
                    b_rhsIter_row = rhsIter_row + 1;
                    if (rhsIter_row + 1 > b_A.m) {
                        b_rhsIter_col = rhsIter_col + 1;
                        b_rhsIter_row = 1;
                    }
                    rhsIter_idx = iter_idx;
                    rhsIter_col = b_rhsIter_col;
                    rhsIter_row = b_rhsIter_row;
                    if ((thisv != 0.0) || (rhsv != 0.0)) {
                        if ((thisv != 0.0) && (rhsv != 0.0)) {
                            Atot.d[vidx - 1] = rhsv;
                        } else if (thisv == 0.0) {
                            int d_k;
                            int d_scalarLB;
                            int d_vectorUB;
                            int i36;
                            int i38;
                            if (Atot.colidx[Atot.colidx.size(0) - 1] - 1 == Atot.maxnz) {
                                coder::sparse::b_realloc(
                                    &Atot, Atot.colidx[Atot.colidx.size(0) - 1] + 9, vidx, vidx + 1,
                                    Atot.colidx[Atot.colidx.size(0) - 1] - 1);
                                Atot.rowidx[vidx] = b_nt;
                                Atot.d[vidx] = rhsv;
                            } else {
                                int b_nelem;
                                b_nelem = (Atot.colidx[Atot.colidx.size(0) - 1] - vidx) - 1;
                                if (b_nelem > 0) {
                                    std::memmove((void *)&Atot.rowidx[vidx + 1],
                                                 (void *)&Atot.rowidx[vidx],
                                                 (unsigned int)((size_t)b_nelem * sizeof(int)));
                                    std::memmove((void *)&Atot.d[vidx + 1], (void *)&Atot.d[vidx],
                                                 (unsigned int)((size_t)b_nelem * sizeof(double)));
                                }
                                Atot.d[vidx] = rhsv;
                                Atot.rowidx[vidx] = b_nt;
                            }
                            i36 = nt + 1;
                            i38 = Atot.n + 1;
                            d_scalarLB = (((((Atot.n - nt) + 1) / 4) << 2) + nt) + 1;
                            d_vectorUB = d_scalarLB - 4;
                            for (d_k = i36; d_k <= d_vectorUB; d_k += 4) {
                                __m128i r9;
                                r9 = _mm_loadu_si128((const __m128i *)&Atot.colidx[d_k - 1]);
                                _mm_storeu_si128((__m128i *)&Atot.colidx[d_k - 1],
                                                 _mm_add_epi32(r9, _mm_set1_epi32(1)));
                            }
                            for (d_k = d_scalarLB; d_k <= i38; d_k++) {
                                Atot.colidx[d_k - 1] = Atot.colidx[d_k - 1] + 1;
                            }
                        } else {
                            int c_k;
                            int c_scalarLB;
                            int c_vectorUB;
                            int i34;
                            int i35;
                            int nelem;
                            nelem = (Atot.colidx[Atot.colidx.size(0) - 1] - vidx) - 1;
                            if (nelem > 0) {
                                std::memmove((void *)&Atot.rowidx[vidx - 1],
                                             (void *)&Atot.rowidx[vidx],
                                             (unsigned int)((size_t)nelem * sizeof(int)));
                                std::memmove((void *)&Atot.d[vidx - 1], (void *)&Atot.d[vidx],
                                             (unsigned int)((size_t)nelem * sizeof(double)));
                            }
                            i34 = nt + 1;
                            i35 = Atot.n + 1;
                            c_scalarLB = (((((Atot.n - nt) + 1) / 4) << 2) + nt) + 1;
                            c_vectorUB = c_scalarLB - 4;
                            for (c_k = i34; c_k <= c_vectorUB; c_k += 4) {
                                __m128i r8;
                                r8 = _mm_loadu_si128((const __m128i *)&Atot.colidx[c_k - 1]);
                                _mm_storeu_si128((__m128i *)&Atot.colidx[c_k - 1],
                                                 _mm_sub_epi32(r8, _mm_set1_epi32(1)));
                            }
                            for (c_k = c_scalarLB; c_k <= i35; c_k++) {
                                Atot.colidx[c_k - 1] = Atot.colidx[c_k - 1] - 1;
                            }
                        }
                    }
                }
            }
            // 'FeedratePlanning_LP:93' btot = [zeros(size(b)); b_jerk];
            btot.set_size(c_b.size(0) + b_jerk.size(0));
            t_loop_ub = c_b.size(0);
            for (int i29{0}; i29 < t_loop_ub; i29++) {
                btot[i29] = 0.0;
            }
            u_loop_ub = b_jerk.size(0);
            for (int i30{0}; i30 < u_loop_ub; i30++) {
                btot[i30 + c_b.size(0)] = b_jerk[i30];
            }
            // 'FeedratePlanning_LP:95' btot(1 : size(b,1)) = b;
            if (1 > c_b.size(0)) {
                v_loop_ub = 0;
            } else {
                v_loop_ub = c_b.size(0);
            }
            for (int i31{0}; i31 < v_loop_ub; i31++) {
                btot[i31] = c_b[i31];
            }
            // 'FeedratePlanning_LP:97' ftot = [f(:) ; LP.SLACK_PENALTY];
            b_f = f.size(0) * f.size(1);
            ftot.set_size(b_f + 1);
            for (int i33{0}; i33 < b_f; i33++) {
                ftot[i33] = f[i33];
            }
            ftot[b_f] = ctx->cfg.opt.SLACK_PENALTY;
            // 'FeedratePlanning_LP:99' [Coeff3, success, status, msg ] = c_simplex(ftot, Atot,
            // btot, ... 'FeedratePlanning_LP:100'             Aeq_tot, beq, ctx); 'c_simplex:2' msg
            // = ""; 'c_simplex:3' if coder.target('rtw') || coder.target('mex') 'c_simplex:4'
            // c_prof_in(mfilename); 'c_simplex:5' c_prof_in('join_A'); 'c_simplex:6' Atot = [A;
            // Aeq];
            b_Aeq.set_size(result, input_sizes_idx_1 + b_input_sizes_idx_1);
            for (int i37{0}; i37 < input_sizes_idx_1; i37++) {
                for (int i39{0}; i39 < result; i39++) {
                    b_Aeq[i39 + b_Aeq.size(0) * i37] = Aeq[i39 + result * i37];
                }
            }
            x_loop_ub = b_input_sizes_idx_1;
            for (int i40{0}; i40 < x_loop_ub; i40++) {
                for (int i41{0}; i41 < result; i41++) {
                    b_Aeq[i41 + b_Aeq.size(0) * input_sizes_idx_1] = 0.0;
                }
            }
            Atot.b_vertcat(b_Aeq, &b_Atot);
            // 'c_simplex:7' c_prof_out('join_A');
            //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
            // 'c_simplex:9' [NCoeff, NHorz] = size(f);
            // 'c_simplex:10' C = zeros(NCoeff, NHorz);
            Coeff3.set_size(ftot.size(0), 1);
            y_loop_ub = ftot.size(0);
            for (int i42{0}; i42 < y_loop_ub; i42++) {
                Coeff3[i42] = 0.0;
            }
            // 'c_simplex:11' coder.varsize('C', [Inf, Inf], [1,1]);
            // 'c_simplex:13' [Aisd, Ajsd, Avs] = find(Atot);
            coder::d_eml_find(&b_Atot, ii, jj, Avs);
            // 'c_simplex:14' Ais = int32(Aisd)-1;
            Ais.set_size(ii.size(0));
            ab_loop_ub = ii.size(0);
            e_scalarLB = (ii.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (i43 = 0; i43 <= e_vectorUB; i43 += 4) {
                __m128i r10;
                r10 = _mm_loadu_si128((const __m128i *)&ii[i43]);
                _mm_storeu_si128((__m128i *)&Ais[i43], _mm_sub_epi32(r10, _mm_set1_epi32(1)));
            }
            for (i43 = e_scalarLB; i43 < ab_loop_ub; i43++) {
                Ais[i43] = ii[i43] - 1;
            }
            // 'c_simplex:15' Ajs = int32(Ajsd)-1;
            Ajs.set_size(jj.size(0));
            bb_loop_ub = jj.size(0);
            f_scalarLB = (jj.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (i44 = 0; i44 <= f_vectorUB; i44 += 4) {
                __m128i r11;
                r11 = _mm_loadu_si128((const __m128i *)&jj[i44]);
                _mm_storeu_si128((__m128i *)&Ajs[i44], _mm_sub_epi32(r11, _mm_set1_epi32(1)));
            }
            for (i44 = f_scalarLB; i44 < bb_loop_ub; i44++) {
                Ajs[i44] = jj[i44] - 1;
            }
            // 'c_simplex:17' coder.varsize('Avs', [Inf, 1], [1, 0]);
            // 'c_simplex:18' coder.varsize('Ais', [Inf, 1], [1, 0]);
            // 'c_simplex:19' coder.varsize('Ajs', [Inf, 1], [1, 0]);
            // 'c_simplex:21' fsize = int32(size(f));
            fsize[0] = ftot.size(0);
            fsize[1] = 1;
            // 'c_simplex:22' Asize = int32(size(Atot));
            Asize[0] = b_Atot.m;
            Asize[1] = b_Atot.n;
            // 'c_simplex:23' An = int32(nnz(Avs));
            n = 0;
            i45 = Avs.size(0);
            for (int e_k{0}; e_k < i45; e_k++) {
                if (Avs[e_k] != 0.0) {
                    n++;
                }
            }
            int d_status;
            // 'c_simplex:24' bsize = int32(size(b));
            bsize[0] = btot.size(0);
            bsize[1] = 1;
            // 'c_simplex:25' beqsize = int32(size(beq));
            beqsize[0] = beq.size(0);
            beqsize[1] = 1;
            // 'c_simplex:26' Csize = int32(size(C));
            Csize[0] = ftot.size(0);
            Csize[1] = 1;
            // 'c_simplex:27' success = int32(0);
            // 'c_simplex:28' status = int32(0);
            // 'c_simplex:29' coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp',
            // '$(START_DIR)/src/'); 'c_simplex:30' coder.updateBuildInfo('addLinkFlags',
            // LibInfo.clp.lflags); 'c_simplex:31' coder.cinclude('cpp_simplex.hpp'); 'c_simplex:32'
            // status = coder.ceval('simplex_solve', coder.rref(f), fsize,... 'c_simplex:33'
            // coder.rref(Avs), coder.rref(Ais), coder.rref(Ajs), Asize, An,... 'c_simplex:34'
            // coder.rref(b), bsize, coder.rref(beq),beqsize,... 'c_simplex:35' coder.ref(C),
            // Csize);
            d_status =
                simplex_solve(&(ftot.data())[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0],
                              &(Ajs.data())[0], &Asize[0], n, &(btot.data())[0], &bsize[0],
                              &(beq.data())[0], &beqsize[0], &Coeff3[0], &Csize[0]);
            //          C = solution.solution;
            // 'c_simplex:37' success = status == 0;
            d_success = (d_status == 0);
            //  Status :
            //        0 : Primal Dual Optimality
            //        1 : Primal Infeasible
            //        2 : Dual Infeasible
            //        3 : Max iteration reached
            //        4 : isAbandoned
            // 'c_simplex:44' c_prof_out(mfilename);
            c_status = d_status;
            // 'FeedratePlanning_LP:102' jerkRatio = (jmax + Coeff3(end)) ./ jmax;
            // 'FeedratePlanning_LP:104' printSecondLPMsg( jerkRatio, msg, success, ...
            // 'FeedratePlanning_LP:105'             LP.USE_SLACK_ON_JERK );
            // 'FeedratePlanning_LP:107' Coeff4 = Coeff3(1:end-1);
            if (1 > Coeff3.size(0) - 1) {
                cb_loop_ub = 0;
            } else {
                cb_loop_ub = Coeff3.size(0) - 1;
            }
            // 'FeedratePlanning_LP:109' Coeff  = reshape(Coeff4, NCoeff0, N_Hor);
            b_Coeff3.set_size(1, cb_loop_ub);
            for (int i46{0}; i46 < cb_loop_ub; i46++) {
                b_Coeff3[i46] = Coeff3[i46];
            }
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), N_Hor);
            for (int i47{0}; i47 < N_Hor; i47++) {
                for (int i48{0}; i48 < BasisVal_idx_0; i48++) {
                    Coeff[i48 + Coeff.size(0) * i47] = b_Coeff3[i48 + BasisVal_idx_0 * i47];
                }
            }
        } else {
            int max_increase;
            // 'FeedratePlanning_LP:110' else
            // 'FeedratePlanning_LP:111' max_increase = 5;
            max_increase = 5;
            // 'FeedratePlanning_LP:111' success = false;
            d_success = false;
            // 'FeedratePlanning_LP:113' jmaxNew = jmax;
            jmaxNew[0] = jmax[0];
            jmaxNew[1] = jmax[1];
            jmaxNew[2] = jmax[2];
            // 'FeedratePlanning_LP:115' while ~success && max_increase > 0
            while ((!d_success) && (max_increase > 0)) {
                __m128d r4;
                int q_loop_ub;
                int s_loop_ub;
                // 'FeedratePlanning_LP:116' jmaxNew = jmaxNew * 2;
                r4 = _mm_loadu_pd(&jmaxNew[0]);
                _mm_storeu_pd(&jmaxNew[0], _mm_mul_pd(r4, _mm_set1_pd(2.0)));
                jmaxNew[2] *= 2.0;
                // 'FeedratePlanning_LP:118' jerkRatio = jmaxNew ./ jmax;
                //  Create jerk constraints
                // 'FeedratePlanning_LP:121' [A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs,
                // Coeff1,... 'FeedratePlanning_LP:122'                 jmaxNew, BasisVal,
                // BasisValD, BasisValDD, u_vec);
                BasisVal_idx_0 = BasisVal.size(1);
                b_CurvStructsArray.set_size(1, loop_ub);
                for (int i22{0}; i22 < loop_ub; i22++) {
                    b_CurvStructsArray[i22] = CurvStructsArray[i22];
                }
                ::coder::array<double, 2U> d_Coeff0;
                d_Coeff0 = Coeff0.reshape(BasisVal_idx_0, N_Hor);
                BuildConstrJerk_v4(&ctx->q_splines, b_CurvStructsArray, d_Coeff0, jmaxNew, BasisVal,
                                   BasisValD, BasisValDD, u_vec, &A_jerk, b_jerk);
                // 'FeedratePlanning_LP:124' Atot = [A; A_jerk];
                // 'FeedratePlanning_LP:124' btot = [b; b_jerk];
                // 'FeedratePlanning_LP:127' [Coeff2, success, status, msg] = c_simplex(f, Atot,
                // btot, ... 'FeedratePlanning_LP:128'                 Aeq, beq, ctx);
                b_b.set_size(c_b.size(0) + b_jerk.size(0));
                q_loop_ub = c_b.size(0);
                for (int i26{0}; i26 < q_loop_ub; i26++) {
                    b_b[i26] = c_b[i26];
                }
                s_loop_ub = b_jerk.size(0);
                for (int i28{0}; i28 < s_loop_ub; i28++) {
                    b_b[i28 + c_b.size(0)] = b_jerk[i28];
                }
                b_A.vertcat(&A_jerk, &r5);
                c_simplex(f, &r5, b_b, Aeq, beq, Coeff2, &d_success, &c_status);
                // 'FeedratePlanning_LP:130' printSecondLPMsg( jerkRatio, msg, success, ...
                // 'FeedratePlanning_LP:131'                 LP.USE_SLACK_ON_JERK );
                // 'FeedratePlanning_LP:133' max_increase = max_increase - 1;
                max_increase--;
                // 'FeedratePlanning_LP:135' ctx.jmax_increase_count = ctx.jmax_increase_count + 1;
                ctx->jmax_increase_count++;
            }
            // 'FeedratePlanning_LP:139' Coeff  = reshape(Coeff2, NCoeff0, N_Hor);
            BasisVal_idx_0 = BasisVal.size(1);
            Coeff.set_size(BasisVal.size(1), N_Hor);
            for (int i20{0}; i20 < N_Hor; i20++) {
                for (int i21{0}; i21 < BasisVal_idx_0; i21++) {
                    Coeff[i21 + Coeff.size(0) * i20] = Coeff2[i21 + BasisVal_idx_0 * i20];
                }
            }
        }
    } else {
        // 'FeedratePlanning_LP:141' else
        // 'FeedratePlanning_LP:142' Coeff  = reshape(Coeff2, NCoeff0, N_Hor);
        BasisVal_idx_0 = BasisVal.size(1);
        Coeff.set_size(BasisVal.size(1), N_Hor);
        for (int i17{0}; i17 < N_Hor; i17++) {
            for (int i18{0}; i18 < BasisVal_idx_0; i18++) {
                Coeff[i18 + Coeff.size(0) * i17] = Coeff2[i18 + BasisVal_idx_0 * i17];
            }
        }
    }
    //  Return if optimization fails
    // 'FeedratePlanning_LP:146' if( ~success )
    if (!d_success) {
        // 'FeedratePlanning_LP:147' printMSG(  "\t ERROR OPTMIZATION FAILED\n" );
        // 'FeedratePlanning_LP:148' Coeff = [];
        Coeff.set_size(0, 0);
        // 'FeedratePlanning_LP:148' NCoeff = int32(0);
        b_NCoeff = 0;
    } else {
        __m128d r6;
        __m128d r7;
        double n_tmp;
        double y_tmp;
        // 'FeedratePlanning_LP:151' [v_0, a_0]  = CalcVAJ_v5(ctx, CurvStructs(1), Bl, Coeff(:, 1),
        // {1});
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
        c_EvalCurvStruct(&ctx->q_splines, CurvStructsArray[0].Type, CurvStructsArray[0].P0,
                         CurvStructsArray[0].P1, CurvStructsArray[0].CorrectedHelixCenter,
                         CurvStructsArray[0].evec, CurvStructsArray[0].theta,
                         CurvStructsArray[0].pitch, CurvStructsArray[0].CoeffP5,
                         CurvStructsArray[0].sp_index, CurvStructsArray[0].a_param,
                         CurvStructsArray[0].b_param, a__1, r1D, r2D, r3D);
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
        if (CurvStructsArray[0].zspdmode == ZSpdMode_ZN) {
            double a;
            double b_t;
            // 'CalcVAJ_v5:40' t = (6*u_vec(iu)/CurvStructs.ConstJerk)^(1/3);
            b_t = std::pow(6.0 / CurvStructsArray[0].ConstJerk, 0.33333333333333331);
            // 'CalcVAJ_v5:41' q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
            a = CurvStructsArray[0].ConstJerk * (b_t * b_t) / 2.0;
            q_val = a * a;
            // 'CalcVAJ_v5:42' qD_val(iu) = 2*CurvStructs.ConstJerk*t;
            qD_val = 2.0 * CurvStructsArray[0].ConstJerk * b_t;
            // 'CalcVAJ_v5:43' qDD_val(iu) = 4/t^2;
        } else if (CurvStructsArray[0].zspdmode == ZSpdMode_NZ) {
            double b_a;
            double b_t;
            // 'CalcVAJ_v5:44' elseif CurvStructs.zspdmode==ZSpdMode.NZ
            // 'CalcVAJ_v5:45' t = (6*(1-u_vec(iu))/CurvStructs.ConstJerk)^(1/3);
            b_t = std::pow(0.0 / CurvStructsArray[0].ConstJerk, 0.33333333333333331);
            // 'CalcVAJ_v5:46' q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
            b_a = CurvStructsArray[0].ConstJerk * (b_t * b_t) / 2.0;
            q_val = b_a * b_a;
            // 'CalcVAJ_v5:47' qD_val(iu) = -2*CurvStructs.ConstJerk*t;
            qD_val = -2.0 * CurvStructsArray[0].ConstJerk * b_t;
            // 'CalcVAJ_v5:48' qDD_val(iu) = 4/t^2;
        } else if (!(CurvStructsArray[0].zspdmode == ZSpdMode_ZZ)) {
            int w_loop_ub;
            // 'CalcVAJ_v5:51' else
            //  ZSpdMode.NN
            // 'CalcVAJ_v5:52' [v1, v2, v3] = bspline_eval(Bl, Coeff(:, k)', u_vec(iu));
            q_val = 1.0;
            w_loop_ub = Coeff.size(0);
            b_Coeff.set_size(1, Coeff.size(0));
            for (int i32{0}; i32 < w_loop_ub; i32++) {
                b_Coeff[i32] = Coeff[i32];
            }
            bspline_eval(Bl_handle, b_Coeff, &q_val, &qD_val, &v3);
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
        // 'CalcVAJ_v5:66' tmp2 = bsxfun(@times, r2D, q_val') + 0.5*bsxfun(@times, r1D, qD_val');
        r6 = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&d_b[0], _mm_mul_pd(r6, _mm_set1_pd(qD_val)));
        r7 = _mm_loadu_pd(&r2D[0]);
        _mm_storeu_pd(&c[0], _mm_mul_pd(r7, _mm_set1_pd(q_val)));
        d_b[2] = r1D[2] * qD_val;
        // 'CalcVAJ_v5:67' tmp3 = bsxfun(@times, r3D, (q_val.^(3/2))') + ...
        // 'CalcVAJ_v5:68'             1.5*bsxfun(@times, r2D, bsxfun(@times,
        // qD_val',mysqrt(q_val)')) + ... 'CalcVAJ_v5:69'             0.5*bsxfun(@times, r1D,
        // bsxfun(@times, qDD_val',mysqrt(q_val)')); 'mysqrt:3' y = sqrt(x); 'mysqrt:4' sqrt_calls =
        // sqrt_calls + 1;
        sqrt_calls++;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'CalcVAJ_v5:71' v_norm = tmp1;
        // 'CalcVAJ_v5:72' a = tmp2;
        // zeros(3, size(tmp2, 2));
        // 'CalcVAJ_v5:73' j = tmp3;
        // 'FeedratePlanning_LP:152' [~, r1D]    = EvalCurvStruct(ctx, CurvStructs(1), 1);
        b_EvalCurvStruct(&ctx->q_splines, &CurvStructsArray[0], a__2, r1D);
        // 'FeedratePlanning_LP:153' t_end       = r1D / MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        n_tmp = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        //  unit tangential vector
        //  tangential acceleration at the end of first piece in horizon
        // 'FeedratePlanning_LP:155' at_0        = a_0'*t_end;
        ctx->at_0 =
            ((c[0] + 0.5 * d_b[0]) * (r1D[0] / n_tmp) + (c[1] + 0.5 * d_b[1]) * (r1D[1] / n_tmp)) +
            (r2D[2] * q_val + 0.5 * d_b[2]) * (r1D[2] / n_tmp);
        // 'FeedratePlanning_LP:156' ctx.v_0     = v_0;
        ctx->v_0 = std::sqrt(y_tmp) * std::sqrt(q_val);
        // 'FeedratePlanning_LP:157' ctx.at_0    = at_0;
        // 'FeedratePlanning_LP:158' NCoeff      = int32( NCoeff0 );
        b_NCoeff = BasisVal.size(1);
    }
    *NCoeff = b_NCoeff;
    *success = d_success;
    *status = c_status;
}

} // namespace ocn

//
// File trailer for FeedratePlanning.cpp
//
// [EOF]
//
