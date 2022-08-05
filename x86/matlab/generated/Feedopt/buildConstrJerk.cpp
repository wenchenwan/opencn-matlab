//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstrJerk.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "buildConstrJerk.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void
binary_expand_op(::coder::array<double, 2U> &Jerk, const ::coder::array<int, 1U> &r,
                 const ::coder::array<double, 2U> &r3D, int j, int i6,
                 const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 1U> &r1,
                 const ::coder::array<double, 2U> &BasisValD, const ::coder::array<double, 1U> &r2,
                 const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 1U> &y);

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
//                const ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace ocn {
static void
binary_expand_op(::coder::array<double, 2U> &Jerk, const ::coder::array<int, 1U> &r,
                 const ::coder::array<double, 2U> &r3D, int j, int i6,
                 const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 1U> &r1,
                 const ::coder::array<double, 2U> &BasisValD, const ::coder::array<double, 1U> &r2,
                 const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 1U> &y)
{
    int aux_1_1;
    int aux_3_1;
    int aux_5_1;
    int b_unnamed_idx_0;
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
    int y_idx_0;
    unnamed_idx_0 = r1.size(0);
    b_unnamed_idx_0 = r2.size(0);
    y_idx_0 = y.size(0);
    stride_0_0 = (i6 != 1);
    stride_1_0 = (BasisVal.size(0) != 1);
    stride_1_1 = (BasisVal.size(1) != 1);
    stride_2_0 = (unnamed_idx_0 != 1);
    stride_3_0 = (BasisValD.size(0) != 1);
    stride_3_1 = (BasisValD.size(1) != 1);
    stride_4_0 = (b_unnamed_idx_0 != 1);
    stride_5_0 = (BasisValDD.size(0) != 1);
    stride_5_1 = (BasisValDD.size(1) != 1);
    stride_6_0 = (y_idx_0 != 1);
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
        if (y_idx_0 == 1) {
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
            b_loop_ub = y_idx_0;
        }
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            Jerk[r[i4] + Jerk.size(0) * i2] =
                ((r3D[j + r3D.size(0) * (i4 * stride_0_0)] *
                      BasisVal[i4 * stride_1_0 + BasisVal.size(0) * aux_1_1] +
                  r1[i4 * stride_2_0] * BasisValD[i4 * stride_3_0 + BasisValD.size(0) * aux_3_1]) +
                 r2[i4 * stride_4_0] * BasisValDD[i4 * stride_5_0 + BasisValDD.size(0) * aux_5_1]) *
                y[i4 * stride_6_0];
        }
        aux_5_1 += stride_5_1;
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// function [ Aj, bj ] = buildConstrJerk( ctx, windowCurv, coeff, jmax, ...
//                     BasisVal, BasisValD, BasisValDD, u_vec )
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
//                const Kinematics *ctx_kin
//                const ::coder::array<CurvStruct, 2U> &windowCurv
//                const ::coder::array<double, 2U> &coeff
//                const double jmax[6]
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &BasisValDD
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &Aj
//                ::coder::array<double, 1U> &bj
// Return Type  : void
//
void buildConstrJerk(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, const Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
    const ::coder::array<double, 2U> &coeff, const double jmax[6],
    const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 2U> &BasisValD,
    const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 2U> &u_vec,
    ::coder::array<double, 2U> &Aj, ::coder::array<double, 1U> &bj)
{
    ::coder::array<double, 2U> Jerk;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> r0D;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 1U> h_y;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<unsigned int, 2U> d_y;
    ::coder::array<int, 2U> g_y;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 1U> r3;
    ::coder::array<int, 1U> r7;
    int M;
    int N;
    int Nc;
    int b_loop_ub;
    int b_y;
    int c_y;
    int end;
    int g_loop_ub;
    int h_loop_ub;
    int i12;
    int i6;
    int i9;
    int j_loop_ub;
    int loop_ub;
    int n;
    int partialTrueCount;
    int trueCount;
    int y;
    signed char tmp_data[6];
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
    // 'buildConstrJerk:25' jmaxTot     = jmax( ctx.cfg.maskTot );
    // 'buildConstrJerk:26' b_jmax      = repmat( jmaxTot, M, 1 );
    end = ctx_cfg_maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end; b_i++) {
        if (ctx_cfg_maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    b.set_size(BasisVal.size(0), trueCount);
    if ((BasisVal.size(0) != 0) && (trueCount != 0)) {
        for (int k{0}; k < trueCount; k++) {
            int i3;
            i3 = BasisVal.size(0) - 1;
            for (int t{0}; t <= i3; t++) {
                b[t + b.size(0) * k] = jmax[tmp_data[k] - 1];
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
        int b_b;
        b_b = static_cast<int>(static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)));
        if (b_b < 1) {
            n = 0;
        } else {
            n = b_b;
        }
    }
    for (int b_k{0}; b_k < i6; b_k++) {
        double f_k;
        int b_unnamed_idx_1;
        int d_scalarLB;
        int d_vectorUB;
        int e_y;
        int i17;
        int i21;
        int l_loop_ub;
        int o_loop_ub;
        int p_loop_ub;
        int r_loop_ub;
        int result;
        int scalarLB;
        int t_loop_ub;
        int u_loop_ub;
        int unnamed_idx_1;
        int vectorUB;
        bool empty_non_axis_sizes;
        //  Compute the partial derivatives
        // 'buildConstrJerk:34' [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec
        // );
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, &windowCurv[b_k], u_vec, r0D, r1D, r2D, r3D);
        // 'buildConstrJerk:36' if( windowCurv( k ).Info.TRAFO )
        if (windowCurv[b_k].Info.TRAFO) {
            int c_loop_ub;
            int f_loop_ub;
            int k_loop_ub;
            // 'buildConstrJerk:37' [ ~, r1D, r2D, r3D ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
            b_r1D.set_size(r1D.size(0), r1D.size(1));
            c_loop_ub = r1D.size(1) - 1;
            for (int i7{0}; i7 <= c_loop_ub; i7++) {
                int e_loop_ub;
                e_loop_ub = r1D.size(0) - 1;
                for (int i10{0}; i10 <= e_loop_ub; i10++) {
                    b_r1D[i10 + b_r1D.size(0) * i7] = r1D[i10 + r1D.size(0) * i7];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            f_loop_ub = r2D.size(1) - 1;
            for (int i11{0}; i11 <= f_loop_ub; i11++) {
                int i_loop_ub;
                i_loop_ub = r2D.size(0) - 1;
                for (int i13{0}; i13 <= i_loop_ub; i13++) {
                    b_r2D[i13 + b_r2D.size(0) * i11] = r2D[i13 + r2D.size(0) * i11];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            k_loop_ub = r3D.size(1) - 1;
            for (int i14{0}; i14 <= k_loop_ub; i14++) {
                int m_loop_ub;
                m_loop_ub = r3D.size(0) - 1;
                for (int i16{0}; i16 <= m_loop_ub; i16++) {
                    b_r3D[i16 + b_r3D.size(0) * i14] = r3D[i16 + r3D.size(0) * i14];
                }
            }
            ctx_kin->joint(r0D, b_r1D, b_r2D, b_r3D, a__1, r1D, r2D, r3D);
        }
        // 'buildConstrJerk:40' for j = 1 : Ndim
        if (0 <= ctx_cfg_NumberAxis - 1) {
            if (M < 1) {
                d_y.set_size(1, 0);
            } else {
                int d_loop_ub;
                d_y.set_size(1, M);
                d_loop_ub = M - 1;
                for (int i8{0}; i8 <= d_loop_ub; i8++) {
                    d_y[i8] = i8 + 1U;
                }
            }
            i9 = r2D.size(1);
            g_loop_ub = r2D.size(1);
            i12 = r1D.size(1);
            h_loop_ub = r1D.size(1);
            j_loop_ub = d_y.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int c_scalarLB;
            int c_vectorUB;
            int e_k;
            int f_y;
            int i20;
            int i24;
            int i26;
            int i27;
            int i29;
            int i30;
            int i34;
            int i36;
            int i39;
            int i40;
            int i41;
            int inner;
            int mc;
            int q_loop_ub;
            //  Compute the jerk matrix
            // 'buildConstrJerk:41' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            f_y = static_cast<int>(static_cast<double>(j) * static_cast<double>(M)) - 1;
            // 'buildConstrJerk:42' Jerk( ind, : ) = ( r3D( j, : ).' .* BasisVal + 1.5 * r2D( j, :
            // ).' ... 'buildConstrJerk:43'                         .* BasisValD + 0.5 * r1D( j, :
            // ).' .* BasisValDD ) ... 'buildConstrJerk:44'                         .* sqrt(
            // BasisVal * coeff( :, k ) );
            r.set_size(i9);
            for (int i15{0}; i15 < g_loop_ub; i15++) {
                r[i15] = 1.5 * r2D[j + r2D.size(0) * i15];
            }
            r1.set_size(i12);
            for (int i18{0}; i18 < h_loop_ub; i18++) {
                r1[i18] = 0.5 * r1D[j + r1D.size(0) * i18];
            }
            mc = BasisVal.size(0) - 1;
            inner = BasisVal.size(1);
            h_y.set_size(BasisVal.size(0));
            for (int c_i{0}; c_i <= mc; c_i++) {
                h_y[c_i] = 0.0;
            }
            for (int d_k{0}; d_k < inner; d_k++) {
                int b_scalarLB;
                int b_vectorUB;
                int d_i;
                b_scalarLB = (BasisVal.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (d_i = 0; d_i <= b_vectorUB; d_i += 2) {
                    __m128d r4;
                    r4 = _mm_loadu_pd(&h_y[d_i]);
                    _mm_storeu_pd(
                        &h_y[d_i],
                        _mm_add_pd(
                            r4,
                            _mm_mul_pd(_mm_loadu_pd(
                                           (const double *)&BasisVal[d_i + BasisVal.size(0) * d_k]),
                                       _mm_set1_pd(coeff[d_k + coeff.size(0) * b_k]))));
                }
                for (d_i = b_scalarLB; d_i <= mc; d_i++) {
                    h_y[d_i] = h_y[d_i] + BasisVal[d_i + BasisVal.size(0) * d_k] *
                                              coeff[d_k + coeff.size(0) * b_k];
                }
            }
            i20 = h_y.size(0);
            c_scalarLB = (h_y.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (e_k = 0; e_k <= c_vectorUB; e_k += 2) {
                __m128d r5;
                r5 = _mm_loadu_pd(&h_y[e_k]);
                _mm_storeu_pd(&h_y[e_k], _mm_sqrt_pd(r5));
            }
            for (e_k = c_scalarLB; e_k < i20; e_k++) {
                h_y[e_k] = std::sqrt(h_y[e_k]);
            }
            r3.set_size(d_y.size(1));
            for (int i22{0}; i22 < j_loop_ub; i22++) {
                r3[i22] = static_cast<int>(d_y[i22]) + f_y;
            }
            q_loop_ub = BasisVal.size(1);
            if (r3D.size(1) == 1) {
                i24 = BasisVal.size(0);
            } else {
                i24 = r3D.size(1);
            }
            if (r.size(0) == 1) {
                i26 = BasisValD.size(0);
            } else {
                i26 = r.size(0);
            }
            if (r3D.size(1) == 1) {
                i27 = BasisVal.size(0);
            } else {
                i27 = r3D.size(1);
            }
            if (i27 == 1) {
                if (r.size(0) == 1) {
                    i29 = BasisValD.size(0);
                } else {
                    i29 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i29 = BasisVal.size(0);
            } else {
                i29 = r3D.size(1);
            }
            if (r1.size(0) == 1) {
                i30 = BasisValDD.size(0);
            } else {
                i30 = r1.size(0);
            }
            if (BasisVal.size(1) == 1) {
                i34 = BasisValD.size(1);
            } else {
                i34 = BasisVal.size(1);
            }
            if (r3D.size(1) == 1) {
                i36 = BasisVal.size(0);
            } else {
                i36 = r3D.size(1);
            }
            if (i36 == 1) {
                if (r.size(0) == 1) {
                    i39 = BasisValD.size(0);
                } else {
                    i39 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i39 = BasisVal.size(0);
            } else {
                i39 = r3D.size(1);
            }
            if (r3D.size(1) == 1) {
                i40 = BasisVal.size(0);
            } else {
                i40 = r3D.size(1);
            }
            if (i39 == 1) {
                if (r1.size(0) == 1) {
                    i41 = BasisValDD.size(0);
                } else {
                    i41 = r1.size(0);
                }
            } else if (i40 == 1) {
                if (r.size(0) == 1) {
                    i41 = BasisValD.size(0);
                } else {
                    i41 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i41 = BasisVal.size(0);
            } else {
                i41 = r3D.size(1);
            }
            if ((BasisVal.size(0) == r3D.size(1)) && (r.size(0) == BasisValD.size(0)) &&
                (i24 == i26) && (BasisVal.size(1) == BasisValD.size(1)) &&
                (r1.size(0) == BasisValDD.size(0)) && (i29 == i30) && (i34 == BasisValDD.size(1)) &&
                (i41 == h_y.size(0))) {
                for (int i42{0}; i42 < q_loop_ub; i42++) {
                    int v_loop_ub;
                    v_loop_ub = r3D.size(1);
                    for (int i43{0}; i43 < v_loop_ub; i43++) {
                        Jerk[r3[i43] + Jerk.size(0) * i42] =
                            ((r3D[j + r3D.size(0) * i43] * BasisVal[i43 + BasisVal.size(0) * i42] +
                              r[i43] * BasisValD[i43 + BasisValD.size(0) * i42]) +
                             r1[i43] * BasisValDD[i43 + BasisValDD.size(0) * i42]) *
                            h_y[i43];
                    }
                }
            } else {
                binary_expand_op(Jerk, r3, r3D, j, r3D.size(1), BasisVal, r, BasisValD, r1,
                                 BasisValDD, h_y);
            }
        }
        //  Inequality constraints
        // 'buildConstrJerk:47' indAL   = int32( 1 : Nc * M )   + ( k - 1 ) * Nc * M;
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
        l_loop_ub = g_y.size(1);
        scalarLB = (g_y.size(1) / 4) << 2;
        vectorUB = scalarLB - 4;
        for (i17 = 0; i17 <= vectorUB; i17 += 4) {
            __m128i r2;
            r2 = _mm_loadu_si128((const __m128i *)&g_y[i17]);
            _mm_storeu_si128((__m128i *)&indAL[i17], _mm_add_epi32(r2, _mm_set1_epi32(e_y)));
        }
        for (i17 = scalarLB; i17 < l_loop_ub; i17++) {
            indAL[i17] = g_y[i17] + e_y;
        }
        // 'buildConstrJerk:48' indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
        if (N < 1) {
            d_y.set_size(1, 0);
        } else {
            int n_loop_ub;
            d_y.set_size(1, N);
            n_loop_ub = N - 1;
            for (int i19{0}; i19 <= n_loop_ub; i19++) {
                d_y[i19] = i19 + 1U;
            }
        }
        // 'buildConstrJerk:49' Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
        r3.set_size(indAL.size(1));
        o_loop_ub = indAL.size(1);
        d_scalarLB = (indAL.size(1) / 4) << 2;
        d_vectorUB = d_scalarLB - 4;
        for (i21 = 0; i21 <= d_vectorUB; i21 += 4) {
            __m128i r6;
            r6 = _mm_loadu_si128((const __m128i *)&indAL[i21]);
            _mm_storeu_si128((__m128i *)&r3[i21], _mm_sub_epi32(r6, _mm_set1_epi32(1)));
        }
        for (i21 = d_scalarLB; i21 < o_loop_ub; i21++) {
            r3[i21] = indAL[i21] - 1;
        }
        f_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        r7.set_size(d_y.size(1));
        p_loop_ub = d_y.size(1);
        for (int i23{0}; i23 < p_loop_ub; i23++) {
            r7[i23] = static_cast<int>(static_cast<double>(d_y[i23]) + f_k) - 1;
        }
        r_loop_ub = Jerk.size(1);
        varargin_2.set_size(Jerk.size(0), Jerk.size(1));
        for (int i25{0}; i25 < r_loop_ub; i25++) {
            int e_scalarLB;
            int e_vectorUB;
            int i28;
            int s_loop_ub;
            s_loop_ub = Jerk.size(0);
            e_scalarLB = (Jerk.size(0) / 2) << 1;
            e_vectorUB = e_scalarLB - 2;
            for (i28 = 0; i28 <= e_vectorUB; i28 += 2) {
                __m128d r8;
                r8 = _mm_loadu_pd(&Jerk[i28 + Jerk.size(0) * i25]);
                _mm_storeu_pd(&varargin_2[i28 + varargin_2.size(0) * i25],
                              _mm_mul_pd(r8, _mm_set1_pd(-1.0)));
            }
            for (i28 = e_scalarLB; i28 < s_loop_ub; i28++) {
                varargin_2[i28 + varargin_2.size(0) * i25] = -Jerk[i28 + Jerk.size(0) * i25];
            }
        }
        if ((Jerk.size(0) != 0) && (Jerk.size(1) != 0)) {
            result = Jerk.size(1);
        } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
            result = varargin_2.size(1);
        } else {
            result = Jerk.size(1);
            if (varargin_2.size(1) > Jerk.size(1)) {
                result = varargin_2.size(1);
            }
        }
        empty_non_axis_sizes = (result == 0);
        if (empty_non_axis_sizes || ((Jerk.size(0) != 0) && (Jerk.size(1) != 0))) {
            t_loop_ub = Jerk.size(0);
        } else {
            t_loop_ub = 0;
        }
        if (empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            u_loop_ub = varargin_2.size(0);
        } else {
            u_loop_ub = 0;
        }
        for (int i31{0}; i31 < result; i31++) {
            for (int i33{0}; i33 < t_loop_ub; i33++) {
                Aj[r3[i33] + Aj.size(0) * r7[i31]] = Jerk[i33 + t_loop_ub * i31];
            }
        }
        for (int i32{0}; i32 < result; i32++) {
            for (int i35{0}; i35 < u_loop_ub; i35++) {
                Aj[r3[i35 + t_loop_ub] + Aj.size(0) * r7[i32]] = varargin_2[i35 + u_loop_ub * i32];
            }
        }
        // 'buildConstrJerk:50' bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
        unnamed_idx_1 = b.size(0) * b.size(1);
        b_unnamed_idx_1 = b.size(0) * b.size(1);
        for (int i37{0}; i37 < unnamed_idx_1; i37++) {
            bj[indAL[i37] - 1] = b[i37];
        }
        for (int i38{0}; i38 < b_unnamed_idx_1; i38++) {
            bj[indAL[i38 + unnamed_idx_1] - 1] = b[i38];
        }
    }
    // 'buildConstrJerk:53' checkValidity( Aj, bj );
    // 'buildConstrJerk:55' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstrJerk.cpp
//
// [EOF]
//
