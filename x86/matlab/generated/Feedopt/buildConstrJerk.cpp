//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstrJerk.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "buildConstrJerk.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &Jerk, const ::coder::array<int, 1U> &r,
                             const ::coder::array<double, 2U> &r3D, int j, int i6,
                             const ::coder::array<double, 2U> &BasisVal,
                             const ::coder::array<double, 1U> &r1,
                             const ::coder::array<double, 2U> &BasisValD,
                             const ::coder::array<double, 1U> &r2,
                             const ::coder::array<double, 2U> &BasisValDD,
                             const ::coder::array<double, 1U> &r3);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &Jerk
//                const ::coder::array<int, 1U> &r
//                const ::coder::array<double, 2U> &r3D
//                int j
//                int i6
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 1U> &r1
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 1U> &r2
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 1U> &r3
// Return Type  : void
//
namespace ocn {
static void
binary_expand_op(::coder::array<double, 2U> &Jerk, const ::coder::array<int, 1U> &r,
                 const ::coder::array<double, 2U> &r3D, int j, int i6,
                 const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 1U> &r1,
                 const ::coder::array<double, 2U> &BasisValD, const ::coder::array<double, 1U> &r2,
                 const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 1U> &r3)
{
    int aux_1_1;
    int aux_3_1;
    int aux_5_1;
    int b_unnamed_idx_0;
    int c_unnamed_idx_0;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_3_0;
    int stride_3_1;
    int stride_4_0;
    int stride_5_0;
    int stride_5_1;
    int stride_6_0;
    int unnamed_idx_0;
    unnamed_idx_0 = r1.size(0);
    b_unnamed_idx_0 = r2.size(0);
    c_unnamed_idx_0 = r3.size(0);
    stride_0_0 = (i6 != 1);
    stride_1_0 = (BasisVal.size(0) != 1);
    stride_1_1 = (BasisVal.size(1) != 1);
    stride_2_0 = (unnamed_idx_0 != 1);
    stride_3_0 = (BasisValD.size(0) != 1);
    stride_3_1 = (BasisValD.size(1) != 1);
    stride_4_0 = (b_unnamed_idx_0 != 1);
    stride_5_0 = (BasisValDD.size(0) != 1);
    stride_5_1 = (BasisValDD.size(1) != 1);
    stride_6_0 = (c_unnamed_idx_0 != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    aux_5_1 = 0;
    if (BasisValDD.size(1) == 1) {
        i = 1;
    } else {
        i = BasisValDD.size(1);
    }
    if (i == 1) {
        int i1;
        if (BasisValD.size(1) == 1) {
            i1 = 1;
        } else {
            i1 = BasisValD.size(1);
        }
        if (i1 == 1) {
            if (BasisVal.size(1) == 1) {
                loop_ub = 1;
            } else {
                loop_ub = BasisVal.size(1);
            }
        } else if (BasisValD.size(1) == 1) {
            loop_ub = 1;
        } else {
            loop_ub = BasisValD.size(1);
        }
    } else if (BasisValDD.size(1) == 1) {
        loop_ub = 1;
    } else {
        loop_ub = BasisValDD.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int b_loop_ub;
        if (c_unnamed_idx_0 == 1) {
            int i3;
            if (BasisValDD.size(0) == 1) {
                i3 = b_unnamed_idx_0;
            } else {
                i3 = BasisValDD.size(0);
            }
            if (i3 == 1) {
                int i5;
                if (BasisValD.size(0) == 1) {
                    i5 = unnamed_idx_0;
                } else {
                    i5 = BasisValD.size(0);
                }
                if (i5 == 1) {
                    if (BasisVal.size(0) == 1) {
                        b_loop_ub = i6;
                    } else {
                        b_loop_ub = BasisVal.size(0);
                    }
                } else if (BasisValD.size(0) == 1) {
                    b_loop_ub = unnamed_idx_0;
                } else {
                    b_loop_ub = BasisValD.size(0);
                }
            } else if (BasisValDD.size(0) == 1) {
                b_loop_ub = b_unnamed_idx_0;
            } else {
                b_loop_ub = BasisValDD.size(0);
            }
        } else {
            b_loop_ub = c_unnamed_idx_0;
        }
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            Jerk[r[i4] + Jerk.size(0) * i2] =
                ((r3D[j + r3D.size(0) * (i4 * stride_0_0)] *
                      BasisVal[i4 * stride_1_0 + BasisVal.size(0) * aux_1_1] +
                  r1[i4 * stride_2_0] * BasisValD[i4 * stride_3_0 + BasisValD.size(0) * aux_3_1]) +
                 r2[i4 * stride_4_0] * BasisValDD[i4 * stride_5_0 + BasisValDD.size(0) * aux_5_1]) *
                r3[i4 * stride_6_0];
        }
        aux_5_1 += stride_5_1;
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// function [ A, b ] = buildConstrJerk( ctx, windowCurv, coeff, jmax, ...
//                     BasisVal, BasisValD, BasisValDD, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const ::coder::array<CurvStruct, 2U> &windowCurv
//                const ::coder::array<double, 2U> &coeff
//                const double jmax[6]
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &b
// Return Type  : void
//
void buildConstrJerk(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                     int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                     const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                     const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                     const ::coder::array<CurvStruct, 2U> &windowCurv,
                     const ::coder::array<double, 2U> &coeff, const double jmax[6],
                     const ::coder::array<double, 2U> &BasisVal,
                     const ::coder::array<double, 2U> &BasisValD,
                     const ::coder::array<double, 2U> &BasisValDD,
                     const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &A,
                     ::coder::array<double, 1U> &b)
{
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Jerk;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_b;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> c_varargin_2;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r3;
    ::coder::array<unsigned int, 2U> d_y;
    ::coder::array<int, 2U> g_y;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 1U> r4;
    ::coder::array<int, 1U> r8;
    ::coder::array<signed char, 2U> b_varargin_2;
    ::coder::array<signed char, 1U> varargin_2;
    double dv[6];
    double dv2[6];
    double dv1[3];
    double dv3[3];
    int M;
    int N;
    int Nc;
    int b_loop_ub;
    int b_y;
    int c_loop_ub;
    int c_y;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i12;
    int i14;
    int i21;
    int i6;
    int i_loop_ub;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int loop_ub;
    int m_loop_ub;
    int n;
    int result;
    int sizes_idx_1;
    int y;
    signed char b_input_sizes_idx_1;
    bool empty_non_axis_sizes;
    // 'buildConstrJerk:5' c_prof_in(mfilename);
    //  Ndim     : number of dimention
    //  NWindow  : number of axes
    // 'buildConstrJerk:8' Ndim        = ctx.cfg.NumberAxis;
    // 'buildConstrJerk:9' Nwindow     = length( windowCurv );
    //  M     : number of discretization
    //  N     : number of coefficients
    //  Nx    : number of decision variable
    //  Nc    : number of inequality constraints
    // 'buildConstrJerk:15' [ M, N ]    = size( BasisVal );
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    // 'buildConstrJerk:16' Nx          = N * Nwindow;
    // 'buildConstrJerk:17' Nc          = 2 * Ndim;
    Nc = ctx_cfg_NumberAxis << 1;
    //  A         : Matrix for equality constraints
    //  b         : Vector for equality constraints
    //  jmaxTot   : Jerk max total ( cart + rot )
    //  b_jmax    : Vector for maximum jerk
    // 'buildConstrJerk:23' Aj          = zeros( Nc * M * Nwindow,  Nx );
    y = static_cast<int>(static_cast<double>(static_cast<int>(
                             static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)))) *
                         static_cast<double>(windowCurv.size(1)));
    loop_ub = static_cast<int>(static_cast<double>(BasisVal.size(1)) *
                               static_cast<double>(windowCurv.size(1)));
    Aj.set_size(y, static_cast<int>(static_cast<double>(BasisVal.size(1)) *
                                    static_cast<double>(windowCurv.size(1))));
    for (int i{0}; i < loop_ub; i++) {
        for (int i1{0}; i1 < y; i1++) {
            Aj[i1 + Aj.size(0) * i] = 0.0;
        }
    }
    // 'buildConstrJerk:24' bj          = zeros( Nc * M * Nwindow,  1 );
    b_y = static_cast<int>(static_cast<double>(static_cast<int>(
                               static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)))) *
                           static_cast<double>(windowCurv.size(1)));
    bj.set_size(b_y);
    for (int i2{0}; i2 < b_y; i2++) {
        bj[i2] = 0.0;
    }
    // 'buildConstrJerk:25' jmaxTot     = jmax( ctx.cfg.indTot );
    // 'buildConstrJerk:26' b_jmax      = repmat( jmaxTot, M, 1 );
    b_b.set_size(BasisVal.size(0), ctx_cfg_indTot_size);
    if ((BasisVal.size(0) != 0) && (ctx_cfg_indTot_size != 0)) {
        for (int k{0}; k < ctx_cfg_indTot_size; k++) {
            int i3;
            i3 = BasisVal.size(0) - 1;
            for (int t{0}; t <= i3; t++) {
                b_b[t + b_b.size(0) * k] = jmax[ctx_cfg_indTot_data[k] - 1];
            }
        }
    }
    //  Jerk       : Matrix of the jerk by axis
    // 'buildConstrJerk:29' Jerk         = zeros( M * Ndim , N );
    c_y = static_cast<int>(static_cast<double>(BasisVal.size(0)) *
                           static_cast<double>(ctx_cfg_NumberAxis));
    Jerk.set_size(c_y, BasisVal.size(1));
    b_loop_ub = BasisVal.size(1);
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        for (int i5{0}; i5 < c_y; i5++) {
            Jerk[i5 + Jerk.size(0) * i4] = 0.0;
        }
    }
    // 'buildConstrJerk:32' for k = 1 : Nwindow
    i6 = windowCurv.size(1);
    if (0 <= windowCurv.size(1) - 1) {
        int c_b;
        c_b = static_cast<int>(static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)));
        if (c_b < 1) {
            n = 0;
        } else {
            n = c_b;
        }
    }
    for (int b_k{0}; b_k < i6; b_k++) {
        double f_k;
        int b_unnamed_idx_1;
        int c_result;
        int d_scalarLB;
        int d_vectorUB;
        int e_y;
        int i19;
        int i27;
        int j_loop_ub;
        int l_loop_ub;
        int n_loop_ub;
        int p_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        int scalarLB;
        int unnamed_idx_1;
        int vectorUB;
        bool b_empty_non_axis_sizes;
        //  Compute the partial derivatives
        // 'buildConstrJerk:34' [ ~, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec
        // );
        for (int i7{0}; i7 < 6; i7++) {
            dv[i7] = windowCurv[b_k].R0[i7];
        }
        for (int i8{0}; i8 < 6; i8++) {
            dv2[i8] = windowCurv[b_k].R1[i8];
        }
        dv1[0] = windowCurv[b_k].CorrectedHelixCenter[0];
        dv1[1] = windowCurv[b_k].CorrectedHelixCenter[1];
        dv1[2] = windowCurv[b_k].CorrectedHelixCenter[2];
        dv3[0] = windowCurv[b_k].evec[0];
        dv3[1] = windowCurv[b_k].evec[1];
        dv3[2] = windowCurv[b_k].evec[2];
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         windowCurv[b_k].Info.Type, dv, dv2, dv1, dv3, windowCurv[b_k].theta,
                         windowCurv[b_k].pitch, windowCurv[b_k].CoeffP5, windowCurv[b_k].sp_index,
                         windowCurv[b_k].a_param, windowCurv[b_k].b_param, u_vec, a__1, r1D, r2D,
                         r3D);
        // 'buildConstrJerk:36' for j = 1 : Ndim
        if (0 <= ctx_cfg_NumberAxis - 1) {
            if (M < 1) {
                d_y.set_size(1, 0);
            } else {
                int d_loop_ub;
                d_y.set_size(1, M);
                d_loop_ub = M - 1;
                for (int i11{0}; i11 <= d_loop_ub; i11++) {
                    d_y[i11] = i11 + 1U;
                }
            }
            i12 = r2D.size(1);
            e_loop_ub = r2D.size(1);
            i14 = r1D.size(1);
            g_loop_ub = r1D.size(1);
            h_loop_ub = d_y.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int c_scalarLB;
            int c_vectorUB;
            int e_k;
            int f_y;
            int i23;
            int i31;
            int i33;
            int i34;
            int i36;
            int i37;
            int i41;
            int i43;
            int i46;
            int i47;
            int i48;
            int inner;
            int mc;
            int o_loop_ub;
            //  Compute the jerk matrix
            // 'buildConstrJerk:37' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            f_y = static_cast<int>(static_cast<double>(j) * static_cast<double>(M)) - 1;
            // 'buildConstrJerk:38' Jerk( ind, : ) = ( r3D( j, : )' .* BasisVal + 1.5 * r2D( j, : )'
            // ... 'buildConstrJerk:39'                         .* BasisValD + 0.5 * r1D( j, : )' .*
            // BasisValDD ) ... 'buildConstrJerk:40'                         .* sqrt( BasisVal *
            // coeff( :, k ) );
            r.set_size(i12);
            for (int i18{0}; i18 < e_loop_ub; i18++) {
                r[i18] = 1.5 * r2D[j + r2D.size(0) * i18];
            }
            r1.set_size(i14);
            for (int i20{0}; i20 < g_loop_ub; i20++) {
                r1[i20] = 0.5 * r1D[j + r1D.size(0) * i20];
            }
            mc = BasisVal.size(0) - 1;
            inner = BasisVal.size(1);
            r3.set_size(BasisVal.size(0));
            for (int b_i{0}; b_i <= mc; b_i++) {
                r3[b_i] = 0.0;
            }
            for (int d_k{0}; d_k < inner; d_k++) {
                int b_scalarLB;
                int b_vectorUB;
                int c_i;
                b_scalarLB = (BasisVal.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (c_i = 0; c_i <= b_vectorUB; c_i += 2) {
                    __m128d r5;
                    r5 = _mm_loadu_pd(&r3[c_i]);
                    _mm_storeu_pd(
                        &r3[c_i],
                        _mm_add_pd(
                            r5,
                            _mm_mul_pd(_mm_loadu_pd(
                                           (const double *)&BasisVal[c_i + BasisVal.size(0) * d_k]),
                                       _mm_set1_pd(coeff[d_k + coeff.size(0) * b_k]))));
                }
                for (c_i = b_scalarLB; c_i <= mc; c_i++) {
                    r3[c_i] = r3[c_i] + BasisVal[c_i + BasisVal.size(0) * d_k] *
                                            coeff[d_k + coeff.size(0) * b_k];
                }
            }
            i23 = r3.size(0);
            c_scalarLB = (r3.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (e_k = 0; e_k <= c_vectorUB; e_k += 2) {
                __m128d r6;
                r6 = _mm_loadu_pd(&r3[e_k]);
                _mm_storeu_pd(&r3[e_k], _mm_sqrt_pd(r6));
            }
            for (e_k = c_scalarLB; e_k < i23; e_k++) {
                r3[e_k] = std::sqrt(r3[e_k]);
            }
            r4.set_size(d_y.size(1));
            for (int i29{0}; i29 < h_loop_ub; i29++) {
                r4[i29] = static_cast<int>(d_y[i29]) + f_y;
            }
            o_loop_ub = BasisVal.size(1);
            if (r3D.size(1) == 1) {
                i31 = BasisVal.size(0);
            } else {
                i31 = r3D.size(1);
            }
            if (r.size(0) == 1) {
                i33 = BasisValD.size(0);
            } else {
                i33 = r.size(0);
            }
            if (r3D.size(1) == 1) {
                i34 = BasisVal.size(0);
            } else {
                i34 = r3D.size(1);
            }
            if (i34 == 1) {
                if (r.size(0) == 1) {
                    i36 = BasisValD.size(0);
                } else {
                    i36 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i36 = BasisVal.size(0);
            } else {
                i36 = r3D.size(1);
            }
            if (r1.size(0) == 1) {
                i37 = BasisValDD.size(0);
            } else {
                i37 = r1.size(0);
            }
            if (BasisVal.size(1) == 1) {
                i41 = BasisValD.size(1);
            } else {
                i41 = BasisVal.size(1);
            }
            if (r3D.size(1) == 1) {
                i43 = BasisVal.size(0);
            } else {
                i43 = r3D.size(1);
            }
            if (i43 == 1) {
                if (r.size(0) == 1) {
                    i46 = BasisValD.size(0);
                } else {
                    i46 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i46 = BasisVal.size(0);
            } else {
                i46 = r3D.size(1);
            }
            if (r3D.size(1) == 1) {
                i47 = BasisVal.size(0);
            } else {
                i47 = r3D.size(1);
            }
            if (i46 == 1) {
                if (r1.size(0) == 1) {
                    i48 = BasisValDD.size(0);
                } else {
                    i48 = r1.size(0);
                }
            } else if (i47 == 1) {
                if (r.size(0) == 1) {
                    i48 = BasisValD.size(0);
                } else {
                    i48 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i48 = BasisVal.size(0);
            } else {
                i48 = r3D.size(1);
            }
            if ((BasisVal.size(0) == r3D.size(1)) && (r.size(0) == BasisValD.size(0)) &&
                (i31 == i33) && (BasisVal.size(1) == BasisValD.size(1)) &&
                (r1.size(0) == BasisValDD.size(0)) && (i36 == i37) && (i41 == BasisValDD.size(1)) &&
                (i48 == r3.size(0))) {
                for (int i49{0}; i49 < o_loop_ub; i49++) {
                    int t_loop_ub;
                    t_loop_ub = r3D.size(1);
                    for (int i50{0}; i50 < t_loop_ub; i50++) {
                        Jerk[r4[i50] + Jerk.size(0) * i49] =
                            ((r3D[j + r3D.size(0) * i50] * BasisVal[i50 + BasisVal.size(0) * i49] +
                              r[i50] * BasisValD[i50 + BasisValD.size(0) * i49]) +
                             r1[i50] * BasisValDD[i50 + BasisValDD.size(0) * i49]) *
                            r3[i50];
                    }
                }
            } else {
                binary_expand_op(Jerk, r4, r3D, j, r3D.size(1), BasisVal, r, BasisValD, r1,
                                 BasisValDD, r3);
            }
        }
        //  Inequality constraints
        // 'buildConstrJerk:43' indAL   = int32( 1 : Nc * M )   + ( k - 1 ) * Nc * M;
        e_y = static_cast<int>(
            static_cast<double>(static_cast<int>(((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 static_cast<double>(Nc))) *
            static_cast<double>(M));
        g_y.set_size(1, n);
        if (n > 0) {
            int yk;
            g_y[0] = 1;
            yk = 1;
            for (int c_k{2}; c_k <= n; c_k++) {
                yk++;
                g_y[c_k - 1] = yk;
            }
        }
        indAL.set_size(1, g_y.size(1));
        j_loop_ub = g_y.size(1);
        scalarLB = (g_y.size(1) / 4) << 2;
        vectorUB = scalarLB - 4;
        for (i19 = 0; i19 <= vectorUB; i19 += 4) {
            __m128i r2;
            r2 = _mm_loadu_si128((const __m128i *)&g_y[i19]);
            _mm_storeu_si128((__m128i *)&indAL[i19], _mm_add_epi32(r2, _mm_set1_epi32(e_y)));
        }
        for (i19 = scalarLB; i19 < j_loop_ub; i19++) {
            indAL[i19] = g_y[i19] + e_y;
        }
        // 'buildConstrJerk:44' indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
        if (N < 1) {
            d_y.set_size(1, 0);
        } else {
            int k_loop_ub;
            d_y.set_size(1, N);
            k_loop_ub = N - 1;
            for (int i22{0}; i22 <= k_loop_ub; i22++) {
                d_y[i22] = i22 + 1U;
            }
        }
        // 'buildConstrJerk:45' Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
        r4.set_size(indAL.size(1));
        l_loop_ub = indAL.size(1);
        d_scalarLB = (indAL.size(1) / 4) << 2;
        d_vectorUB = d_scalarLB - 4;
        for (i27 = 0; i27 <= d_vectorUB; i27 += 4) {
            __m128i r7;
            r7 = _mm_loadu_si128((const __m128i *)&indAL[i27]);
            _mm_storeu_si128((__m128i *)&r4[i27], _mm_sub_epi32(r7, _mm_set1_epi32(1)));
        }
        for (i27 = d_scalarLB; i27 < l_loop_ub; i27++) {
            r4[i27] = indAL[i27] - 1;
        }
        f_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        r8.set_size(d_y.size(1));
        n_loop_ub = d_y.size(1);
        for (int i30{0}; i30 < n_loop_ub; i30++) {
            r8[i30] = static_cast<int>(static_cast<double>(d_y[i30]) + f_k) - 1;
        }
        p_loop_ub = Jerk.size(1);
        c_varargin_2.set_size(Jerk.size(0), Jerk.size(1));
        for (int i32{0}; i32 < p_loop_ub; i32++) {
            int e_scalarLB;
            int e_vectorUB;
            int i35;
            int q_loop_ub;
            q_loop_ub = Jerk.size(0);
            e_scalarLB = (Jerk.size(0) / 2) << 1;
            e_vectorUB = e_scalarLB - 2;
            for (i35 = 0; i35 <= e_vectorUB; i35 += 2) {
                __m128d r9;
                r9 = _mm_loadu_pd(&Jerk[i35 + Jerk.size(0) * i32]);
                _mm_storeu_pd(&c_varargin_2[i35 + c_varargin_2.size(0) * i32],
                              _mm_mul_pd(r9, _mm_set1_pd(-1.0)));
            }
            for (i35 = e_scalarLB; i35 < q_loop_ub; i35++) {
                c_varargin_2[i35 + c_varargin_2.size(0) * i32] = -Jerk[i35 + Jerk.size(0) * i32];
            }
        }
        if ((Jerk.size(0) != 0) && (Jerk.size(1) != 0)) {
            c_result = Jerk.size(1);
        } else if ((c_varargin_2.size(0) != 0) && (c_varargin_2.size(1) != 0)) {
            c_result = c_varargin_2.size(1);
        } else {
            c_result = Jerk.size(1);
            if (c_varargin_2.size(1) > Jerk.size(1)) {
                c_result = c_varargin_2.size(1);
            }
        }
        b_empty_non_axis_sizes = (c_result == 0);
        if (b_empty_non_axis_sizes || ((Jerk.size(0) != 0) && (Jerk.size(1) != 0))) {
            r_loop_ub = Jerk.size(0);
        } else {
            r_loop_ub = 0;
        }
        if (b_empty_non_axis_sizes ||
            ((c_varargin_2.size(0) != 0) && (c_varargin_2.size(1) != 0))) {
            s_loop_ub = c_varargin_2.size(0);
        } else {
            s_loop_ub = 0;
        }
        for (int i38{0}; i38 < c_result; i38++) {
            for (int i40{0}; i40 < r_loop_ub; i40++) {
                Aj[r4[i40] + Aj.size(0) * r8[i38]] = Jerk[i40 + r_loop_ub * i38];
            }
        }
        for (int i39{0}; i39 < c_result; i39++) {
            for (int i42{0}; i42 < s_loop_ub; i42++) {
                Aj[r4[i42 + r_loop_ub] + Aj.size(0) * r8[i39]] =
                    c_varargin_2[i42 + s_loop_ub * i39];
            }
        }
        // 'buildConstrJerk:46' bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
        unnamed_idx_1 = b_b.size(0) * b_b.size(1);
        b_unnamed_idx_1 = b_b.size(0) * b_b.size(1);
        for (int i44{0}; i44 < unnamed_idx_1; i44++) {
            bj[indAL[i44] - 1] = b_b[i44];
        }
        for (int i45{0}; i45 < b_unnamed_idx_1; i45++) {
            bj[indAL[i45 + unnamed_idx_1] - 1] = b_b[i45];
        }
    }
    //  Slack variables
    // 'buildConstrJerk:50' [ nAL, nAc ] = size( Aj );
    // 'buildConstrJerk:51' A = [ Aj, - ones( nAL, 1 ) ; zeros( 1, nAc ), -1 ];
    varargin_2.set_size(Aj.size(0));
    c_loop_ub = Aj.size(0);
    for (int i9{0}; i9 < c_loop_ub; i9++) {
        varargin_2[i9] = -1;
    }
    if ((Aj.size(0) != 0) && (Aj.size(1) != 0)) {
        result = Aj.size(0);
    } else if (varargin_2.size(0) != 0) {
        result = varargin_2.size(0);
    } else {
        result = Aj.size(0);
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((Aj.size(0) != 0) && (Aj.size(1) != 0))) {
        input_sizes_idx_1 = Aj.size(1);
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_2.size(0) != 0)) {
        b_input_sizes_idx_1 = 1;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    b_result.set_size(result, input_sizes_idx_1 + b_input_sizes_idx_1);
    for (int i10{0}; i10 < input_sizes_idx_1; i10++) {
        for (int i13{0}; i13 < result; i13++) {
            b_result[i13 + b_result.size(0) * i10] = Aj[i13 + result * i10];
        }
    }
    f_loop_ub = b_input_sizes_idx_1;
    for (int i15{0}; i15 < f_loop_ub; i15++) {
        for (int i16{0}; i16 < result; i16++) {
            b_result[i16 + b_result.size(0) * input_sizes_idx_1] = -1.0;
        }
    }
    b_varargin_2.set_size(1, Aj.size(1) + 1);
    i_loop_ub = Aj.size(1);
    for (int i17{0}; i17 < i_loop_ub; i17++) {
        b_varargin_2[i17] = 0;
    }
    b_varargin_2[Aj.size(1)] = -1;
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        sizes_idx_1 = b_result.size(1);
    } else {
        sizes_idx_1 = b_varargin_2.size(1);
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        input_sizes_idx_0 = b_result.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if ((b_result.size(0) != 0) && (b_result.size(1) != 0)) {
        i21 = b_result.size(0);
    } else {
        i21 = 0;
    }
    A.set_size(i21 + 1, sizes_idx_1);
    for (int i24{0}; i24 < sizes_idx_1; i24++) {
        for (int i26{0}; i26 < input_sizes_idx_0; i26++) {
            A[i26 + A.size(0) * i24] = b_result[i26 + input_sizes_idx_0 * i24];
        }
    }
    for (int i25{0}; i25 < sizes_idx_1; i25++) {
        A[input_sizes_idx_0 + A.size(0) * i25] = b_varargin_2[i25];
    }
    // 'buildConstrJerk:53' b = [ bj ; 0 ];
    b.set_size(bj.size(0) + 1);
    m_loop_ub = bj.size(0);
    for (int i28{0}; i28 < m_loop_ub; i28++) {
        b[i28] = bj[i28];
    }
    b[bj.size(0)] = 0.0;
    // 'buildConstrJerk:55' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstrJerk.cpp
//
// [EOF]
//
