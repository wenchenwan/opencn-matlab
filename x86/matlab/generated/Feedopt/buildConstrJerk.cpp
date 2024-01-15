
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstrJerk.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "buildConstrJerk.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "ocn_assert.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void
binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<int, 1U> &in2,
                 const ::coder::array<double, 2U> &in3, int in4, int in5,
                 const ::coder::array<double, 2U> &in6, const ::coder::array<double, 1U> &in7,
                 const ::coder::array<double, 2U> &in8, const ::coder::array<double, 1U> &in9,
                 const ::coder::array<double, 2U> &in10, const ::coder::array<double, 1U> &in11);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<int, 1U> &in2
//                const ::coder::array<double, 2U> &in3
//                int in4
//                int in5
//                const ::coder::array<double, 2U> &in6
//                const ::coder::array<double, 1U> &in7
//                const ::coder::array<double, 2U> &in8
//                const ::coder::array<double, 1U> &in9
//                const ::coder::array<double, 2U> &in10
//                const ::coder::array<double, 1U> &in11
// Return Type  : void
//
namespace ocn {
static void
binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<int, 1U> &in2,
                 const ::coder::array<double, 2U> &in3, int in4, int in5,
                 const ::coder::array<double, 2U> &in6, const ::coder::array<double, 1U> &in7,
                 const ::coder::array<double, 2U> &in8, const ::coder::array<double, 1U> &in9,
                 const ::coder::array<double, 2U> &in10, const ::coder::array<double, 1U> &in11)
{
    int aux_1_1;
    int aux_3_1;
    int aux_5_1;
    int i;
    int in11_idx_0;
    int in7_idx_0;
    int in9_idx_0;
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
    in7_idx_0 = in7.size(0);
    in9_idx_0 = in9.size(0);
    in11_idx_0 = in11.size(0);
    stride_0_0 = (in5 != 1);
    stride_1_0 = (in6.size(0) != 1);
    stride_1_1 = (in6.size(1) != 1);
    stride_2_0 = (in7_idx_0 != 1);
    stride_3_0 = (in8.size(0) != 1);
    stride_3_1 = (in8.size(1) != 1);
    stride_4_0 = (in9_idx_0 != 1);
    stride_5_0 = (in10.size(0) != 1);
    stride_5_1 = (in10.size(1) != 1);
    stride_6_0 = (in11_idx_0 != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    aux_5_1 = 0;
    if (in10.size(1) == 1) {
        i = 1;
    } else {
        i = in10.size(1);
    }
    if (i == 1) {
        int i1;
        if (in8.size(1) == 1) {
            i1 = 1;
        } else {
            i1 = in8.size(1);
        }
        if (i1 == 1) {
            if (in6.size(1) == 1) {
                loop_ub = 1;
            } else {
                loop_ub = in6.size(1);
            }
        } else if (in8.size(1) == 1) {
            loop_ub = 1;
        } else {
            loop_ub = in8.size(1);
        }
    } else if (in10.size(1) == 1) {
        loop_ub = 1;
    } else {
        loop_ub = in10.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int b_loop_ub;
        if (in11_idx_0 == 1) {
            int i3;
            if (in10.size(0) == 1) {
                i3 = in9_idx_0;
            } else {
                i3 = in10.size(0);
            }
            if (i3 == 1) {
                int i5;
                if (in8.size(0) == 1) {
                    i5 = in7_idx_0;
                } else {
                    i5 = in8.size(0);
                }
                if (i5 == 1) {
                    if (in6.size(0) == 1) {
                        b_loop_ub = in5;
                    } else {
                        b_loop_ub = in6.size(0);
                    }
                } else if (in8.size(0) == 1) {
                    b_loop_ub = in7_idx_0;
                } else {
                    b_loop_ub = in8.size(0);
                }
            } else if (in10.size(0) == 1) {
                b_loop_ub = in9_idx_0;
            } else {
                b_loop_ub = in10.size(0);
            }
        } else {
            b_loop_ub = in11_idx_0;
        }
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            in1[in2[i4] + in1.size(0) * i2] =
                ((in3[in4 + in3.size(0) * (i4 * stride_0_0)] *
                      in6[i4 * stride_1_0 + in6.size(0) * aux_1_1] +
                  in7[i4 * stride_2_0] * in8[i4 * stride_3_0 + in8.size(0) * aux_3_1]) +
                 in9[i4 * stride_4_0] * in10[i4 * stride_5_0 + in10.size(0) * aux_5_1]) *
                in11[i4 * stride_6_0];
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
// buildConstrJerk : Build jerk constraints
//
//  Inputs :
//  ctx           : Matlab Context
//  windowCurv    : Curv window
//  coeff         : Coefficient of the optimization
//  jmax          : Maximum jerk
//  BasisVal      : BSpline evaluated at u_vec points
//  BasisValD     : BSpline derivative evaluated at u_vec points
//  BasisValDD    : BSpline second derivative evaluated at u_vec points
//  u_vec         : Vector of u values
//  Outputs :
//
//  Aj            : Matrix of inequality constraints for the jerk
//  bj            : vector of inequality limits for the jerk
//
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
//                Kinematics *ctx_kin
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
    int ctx_cfg_NRot, Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
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
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r3;
    ::coder::array<unsigned int, 2U> d_y;
    ::coder::array<int, 2U> g_y;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 1U> r4;
    ::coder::array<int, 1U> r7;
    ::coder::array<bool, 1U> r8;
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
    // 'buildConstrJerk:21' c_prof_in(mfilename);
    //  Ndim     : number of dimention
    //  NWindow  : number of axes
    // 'buildConstrJerk:24' Ndim        = ctx.cfg.NumberAxis;
    // 'buildConstrJerk:25' Nwindow     = length( windowCurv );
    //  M     : number of discretization
    //  N     : number of coefficients
    //  Nx    : number of decision variable
    //  Nc    : number of inequality constraints
    // 'buildConstrJerk:31' [ M, N ]    = size( BasisVal );
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    // 'buildConstrJerk:32' Nx          = N * Nwindow;
    // 'buildConstrJerk:33' Nc          = 2 * Ndim;
    Nc = ctx_cfg_NumberAxis << 1;
    //  A         : Matrix for equality constraints
    //  b         : Vector for equality constraints
    //  jmaxTot   : Jerk max total ( cart + rot )
    //  b_jmax    : Vector for maximum jerk
    // 'buildConstrJerk:39' Aj          = zeros( Nc * M * Nwindow,  Nx );
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
    // 'buildConstrJerk:40' bj          = zeros( Nc * M * Nwindow,  1 );
    b_y = static_cast<int>(static_cast<double>(static_cast<int>(
                               static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)))) *
                           static_cast<double>(windowCurv.size(1)));
    bj.set_size(b_y);
    for (int i2{0}; i2 < b_y; i2++) {
        bj[i2] = 0.0;
    }
    // 'buildConstrJerk:41' jmaxTot     = jmax( ctx.cfg.maskTot );
    // 'buildConstrJerk:42' b_jmax      = repmat( jmaxTot, M, 1 );
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
        int i3;
        i3 = BasisVal.size(0) - 1;
        for (int k{0}; k < trueCount; k++) {
            for (int t{0}; t <= i3; t++) {
                b[t + b.size(0) * k] = jmax[tmp_data[k] - 1];
            }
        }
    }
    //  Jerk       : Matrix of the jerk by axis
    // 'buildConstrJerk:45' Jerk         = zeros( M * Ndim , N );
    c_y = static_cast<int>(static_cast<double>(BasisVal.size(0)) *
                           static_cast<double>(ctx_cfg_NumberAxis));
    Jerk.set_size(c_y, BasisVal.size(1));
    b_loop_ub = BasisVal.size(1);
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        for (int i5{0}; i5 < c_y; i5++) {
            Jerk[i5 + Jerk.size(0) * i4] = 0.0;
        }
    }
    // 'buildConstrJerk:48' for k = 1 : Nwindow
    i6 = windowCurv.size(1);
    if (windowCurv.size(1) - 1 >= 0) {
        int b_b;
        b_b = static_cast<int>(static_cast<double>(Nc) * static_cast<double>(BasisVal.size(0)));
        if (b_b < 1) {
            n = 0;
        } else {
            n = b_b;
        }
    }
    for (int b_k{0}; b_k < i6; b_k++) {
        double e_k;
        int b_unnamed_idx_1;
        int c_scalarLB;
        int c_vectorUB;
        int e_y;
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
        // 'buildConstrJerk:50' [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec
        // );
        q_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, &windowCurv[b_k], u_vec, r0D, r1D, r2D, r3D);
        // 'buildConstrJerk:52' ctx.kin = ctx.kin.set_tool_length( -windowCurv( k ).tool.offset.z );
        ctx_kin->set_tool_length(-windowCurv[b_k].tool.offset.z);
        // 'buildConstrJerk:54' if( windowCurv( k ).Info.TRAFO )
        if (windowCurv[b_k].Info.TRAFO) {
            int c_loop_ub;
            int f_loop_ub;
            int k_loop_ub;
            // 'buildConstrJerk:55' [ ~, r1D, r2D, r3D ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
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
        // 'buildConstrJerk:58' for j = 1 : Ndim
        if (ctx_cfg_NumberAxis - 1 >= 0) {
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
            int d_scalarLB;
            int d_vectorUB;
            int f_y;
            int i24;
            int i28;
            int i31;
            int i33;
            int i36;
            int i37;
            int i38;
            int i39;
            int i40;
            int i41;
            int i42;
            int inner;
            int mc;
            int q_loop_ub;
            int v_loop_ub;
            //  Compute the jerk matrix
            // 'buildConstrJerk:59' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            f_y = static_cast<int>(static_cast<double>(j) * static_cast<double>(M)) - 1;
            // 'buildConstrJerk:60' Jerk( ind, : ) = ( r3D( j, : ).' .* BasisVal + 1.5 * r2D( j, :
            // ).' ... 'buildConstrJerk:61'                         .* BasisValD + 0.5 * r1D( j, :
            // ).' .* BasisValDD ) ... 'buildConstrJerk:62'                         .* mysqrt(
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
            r3.set_size(BasisVal.size(0));
            for (int c_i{0}; c_i <= mc; c_i++) {
                r3[c_i] = 0.0;
            }
            for (int d_k{0}; d_k < inner; d_k++) {
                int b_scalarLB;
                int b_vectorUB;
                b_scalarLB = (BasisVal.size(0) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (int d_i{0}; d_i <= b_vectorUB; d_i += 2) {
                    __m128d r5;
                    r5 = _mm_loadu_pd(&r3[d_i]);
                    _mm_storeu_pd(
                        &r3[d_i],
                        _mm_add_pd(
                            r5,
                            _mm_mul_pd(_mm_loadu_pd(
                                           (const double *)&BasisVal[d_i + BasisVal.size(0) * d_k]),
                                       _mm_set1_pd(coeff[d_k + coeff.size(0) * b_k]))));
                }
                for (int d_i{b_scalarLB}; d_i <= mc; d_i++) {
                    r3[d_i] = r3[d_i] + BasisVal[d_i + BasisVal.size(0) * d_k] *
                                            coeff[d_k + coeff.size(0) * b_k];
                }
            }
            //  mysqrt : Custom implementation of the sqrt method.
            //
            //  Inputs :
            //    x : Value used for the computation
            //  Outputs :
            //    y : Resulting value
            //
            // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
            // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
            r8.set_size(r3.size(0));
            q_loop_ub = r3.size(0);
            for (int i22{0}; i22 < q_loop_ub; i22++) {
                r8[i22] = (r3[i22] >= 0.0);
            }
            e_ocn_assert(r8);
            // 'mysqrt:11' y = sqrt(x);
            i24 = r3.size(0);
            d_scalarLB = (r3.size(0) / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (int f_k{0}; f_k <= d_vectorUB; f_k += 2) {
                __m128d r9;
                r9 = _mm_loadu_pd(&r3[f_k]);
                _mm_storeu_pd(&r3[f_k], _mm_sqrt_pd(r9));
            }
            for (int f_k{d_scalarLB}; f_k < i24; f_k++) {
                r3[f_k] = std::sqrt(r3[f_k]);
            }
            r4.set_size(d_y.size(1));
            for (int i26{0}; i26 < j_loop_ub; i26++) {
                r4[i26] = static_cast<int>(d_y[i26]) + f_y;
            }
            v_loop_ub = BasisVal.size(1);
            if (r3D.size(1) == 1) {
                i28 = BasisVal.size(0);
            } else {
                i28 = r3D.size(1);
            }
            if (r.size(0) == 1) {
                i31 = BasisValD.size(0);
            } else {
                i31 = r.size(0);
            }
            if (r3D.size(1) == 1) {
                i33 = BasisVal.size(0);
            } else {
                i33 = r3D.size(1);
            }
            if (i33 == 1) {
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
                i38 = BasisValD.size(1);
            } else {
                i38 = BasisVal.size(1);
            }
            if (r3D.size(1) == 1) {
                i39 = BasisVal.size(0);
            } else {
                i39 = r3D.size(1);
            }
            if (i39 == 1) {
                if (r.size(0) == 1) {
                    i40 = BasisValD.size(0);
                } else {
                    i40 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i40 = BasisVal.size(0);
            } else {
                i40 = r3D.size(1);
            }
            if (r3D.size(1) == 1) {
                i41 = BasisVal.size(0);
            } else {
                i41 = r3D.size(1);
            }
            if (i40 == 1) {
                if (r1.size(0) == 1) {
                    i42 = BasisValDD.size(0);
                } else {
                    i42 = r1.size(0);
                }
            } else if (i41 == 1) {
                if (r.size(0) == 1) {
                    i42 = BasisValD.size(0);
                } else {
                    i42 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i42 = BasisVal.size(0);
            } else {
                i42 = r3D.size(1);
            }
            if ((BasisVal.size(0) == r3D.size(1)) && (r.size(0) == BasisValD.size(0)) &&
                (i28 == i31) && (BasisVal.size(1) == BasisValD.size(1)) &&
                (r1.size(0) == BasisValDD.size(0)) && (i36 == i37) && (i38 == BasisValDD.size(1)) &&
                (i42 == r3.size(0))) {
                for (int i43{0}; i43 < v_loop_ub; i43++) {
                    int w_loop_ub;
                    w_loop_ub = r3D.size(1);
                    for (int i44{0}; i44 < w_loop_ub; i44++) {
                        Jerk[r4[i44] + Jerk.size(0) * i43] =
                            ((r3D[j + r3D.size(0) * i44] * BasisVal[i44 + BasisVal.size(0) * i43] +
                              r[i44] * BasisValD[i44 + BasisValD.size(0) * i43]) +
                             r1[i44] * BasisValDD[i44 + BasisValDD.size(0) * i43]) *
                            r3[i44];
                    }
                }
            } else {
                binary_expand_op(Jerk, r4, r3D, j, r3D.size(1), BasisVal, r, BasisValD, r1,
                                 BasisValDD, r3);
            }
        }
        //  Inequality constraints
        // 'buildConstrJerk:65' indAL   = int32( 1 : Nc * M )   + ( k - 1 ) * Nc * M;
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
        for (int i17{0}; i17 <= vectorUB; i17 += 4) {
            __m128i r2;
            r2 = _mm_loadu_si128((const __m128i *)&g_y[i17]);
            _mm_storeu_si128((__m128i *)&indAL[i17], _mm_add_epi32(r2, _mm_set1_epi32(e_y)));
        }
        for (int i17{scalarLB}; i17 < l_loop_ub; i17++) {
            indAL[i17] = g_y[i17] + e_y;
        }
        // 'buildConstrJerk:66' indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
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
        // 'buildConstrJerk:67' Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
        r4.set_size(indAL.size(1));
        o_loop_ub = indAL.size(1);
        c_scalarLB = (indAL.size(1) / 4) << 2;
        c_vectorUB = c_scalarLB - 4;
        for (int i20{0}; i20 <= c_vectorUB; i20 += 4) {
            __m128i r6;
            r6 = _mm_loadu_si128((const __m128i *)&indAL[i20]);
            _mm_storeu_si128((__m128i *)&r4[i20], _mm_sub_epi32(r6, _mm_set1_epi32(1)));
        }
        for (int i20{c_scalarLB}; i20 < o_loop_ub; i20++) {
            r4[i20] = indAL[i20] - 1;
        }
        e_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        r7.set_size(d_y.size(1));
        p_loop_ub = d_y.size(1);
        for (int i21{0}; i21 < p_loop_ub; i21++) {
            r7[i21] = static_cast<int>(static_cast<double>(d_y[i21]) + e_k) - 1;
        }
        r_loop_ub = Jerk.size(1);
        varargin_2.set_size(Jerk.size(0), Jerk.size(1));
        for (int i23{0}; i23 < r_loop_ub; i23++) {
            int e_scalarLB;
            int e_vectorUB;
            int s_loop_ub;
            s_loop_ub = Jerk.size(0);
            e_scalarLB = (Jerk.size(0) / 2) << 1;
            e_vectorUB = e_scalarLB - 2;
            for (int i25{0}; i25 <= e_vectorUB; i25 += 2) {
                __m128d r10;
                r10 = _mm_loadu_pd(&Jerk[i25 + Jerk.size(0) * i23]);
                _mm_storeu_pd(&varargin_2[i25 + varargin_2.size(0) * i23],
                              _mm_mul_pd(r10, _mm_set1_pd(-1.0)));
            }
            for (int i25{e_scalarLB}; i25 < s_loop_ub; i25++) {
                varargin_2[i25 + varargin_2.size(0) * i23] = -Jerk[i25 + Jerk.size(0) * i23];
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
        for (int i27{0}; i27 < result; i27++) {
            for (int i30{0}; i30 < t_loop_ub; i30++) {
                Aj[r4[i30] + Aj.size(0) * r7[i27]] = Jerk[i30 + t_loop_ub * i27];
            }
        }
        for (int i29{0}; i29 < result; i29++) {
            for (int i32{0}; i32 < u_loop_ub; i32++) {
                Aj[r4[i32 + t_loop_ub] + Aj.size(0) * r7[i29]] = varargin_2[i32 + u_loop_ub * i29];
            }
        }
        // 'buildConstrJerk:68' bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
        unnamed_idx_1 = b.size(0) * b.size(1);
        b_unnamed_idx_1 = b.size(0) * b.size(1);
        for (int i34{0}; i34 < unnamed_idx_1; i34++) {
            bj[indAL[i34] - 1] = b[i34];
        }
        for (int i35{0}; i35 < b_unnamed_idx_1; i35++) {
            bj[indAL[i35 + unnamed_idx_1] - 1] = b[i35];
        }
    }
    // 'buildConstrJerk:71' checkValidity( Aj, bj );
    // 'buildConstrJerk:79' ocn_assert( ~any( isnan( A ) , 'all' ), "A has NaN", mfilename );
    // 'buildConstrJerk:80' ocn_assert( ~any( isnan( b ) , 'all' ), "b has NaN", mfilename );
    // 'buildConstrJerk:73' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstrJerk.cpp
//
// [EOF]
//
