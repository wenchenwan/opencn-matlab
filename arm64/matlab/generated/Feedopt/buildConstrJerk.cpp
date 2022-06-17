//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstrJerk.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
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
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
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
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &b
// Return Type  : void
//
void buildConstrJerk(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
    const ::coder::array<bool, 2U> &ctx_cfg_maskRot, const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, const Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
    const ::coder::array<double, 2U> &coeff, const double jmax[6],
    const ::coder::array<double, 2U> &BasisVal, const ::coder::array<double, 2U> &BasisValD,
    const ::coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 2U> &u_vec,
    ::coder::array<double, 2U> &A, ::coder::array<double, 1U> &b)
{
    ::coder::array<double, 2U> Aj;
    ::coder::array<double, 2U> Jerk;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_b;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_result;
    ::coder::array<double, 2U> c_varargin_2;
    ::coder::array<double, 2U> r0D;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 1U> bj;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r2;
    ::coder::array<unsigned int, 2U> d_y;
    ::coder::array<int, 2U> g_y;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 1U> r3;
    ::coder::array<int, 1U> r4;
    ::coder::array<signed char, 2U> b_varargin_2;
    ::coder::array<signed char, 1U> varargin_2;
    int M;
    int N;
    int Nc;
    int b_loop_ub;
    int b_y;
    int c_loop_ub;
    int c_y;
    int end;
    int h_loop_ub;
    int i10;
    int i13;
    int i30;
    int i6;
    int i_loop_ub;
    int input_sizes_idx_0;
    int input_sizes_idx_1;
    int k_loop_ub;
    int loop_ub;
    int n;
    int o_loop_ub;
    int p_loop_ub;
    int partialTrueCount;
    int result;
    int sizes_idx_1;
    int trueCount;
    int w_loop_ub;
    int y;
    signed char tmp_data[6];
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
    b_b.set_size(BasisVal.size(0), trueCount);
    if ((BasisVal.size(0) != 0) && (trueCount != 0)) {
        for (int k{0}; k < trueCount; k++) {
            int i3;
            i3 = BasisVal.size(0) - 1;
            for (int t{0}; t <= i3; t++) {
                b_b[t + b_b.size(0) * k] = jmax[tmp_data[k] - 1];
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
        double e_k;
        int b_unnamed_idx_1;
        int c_result;
        int e_y;
        int m_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        int t_loop_ub;
        int unnamed_idx_1;
        int x_loop_ub;
        int y_loop_ub;
        bool b_empty_non_axis_sizes;
        //  Compute the partial derivatives
        // 'buildConstrJerk:34' [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec
        // );
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, &windowCurv[b_k], u_vec, r0D, r1D, r2D, r3D);
        // 'buildConstrJerk:36' if( windowCurv( k ).Info.TRAFO )
        if (windowCurv[b_k].Info.TRAFO) {
            int d_loop_ub;
            int g_loop_ub;
            int l_loop_ub;
            // 'buildConstrJerk:37' [ ~, r1D, r2D, r3D ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
            b_r1D.set_size(r1D.size(0), r1D.size(1));
            d_loop_ub = r1D.size(1) - 1;
            for (int i8{0}; i8 <= d_loop_ub; i8++) {
                int f_loop_ub;
                f_loop_ub = r1D.size(0) - 1;
                for (int i11{0}; i11 <= f_loop_ub; i11++) {
                    b_r1D[i11 + b_r1D.size(0) * i8] = r1D[i11 + r1D.size(0) * i8];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            g_loop_ub = r2D.size(1) - 1;
            for (int i12{0}; i12 <= g_loop_ub; i12++) {
                int j_loop_ub;
                j_loop_ub = r2D.size(0) - 1;
                for (int i14{0}; i14 <= j_loop_ub; i14++) {
                    b_r2D[i14 + b_r2D.size(0) * i12] = r2D[i14 + r2D.size(0) * i12];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            l_loop_ub = r3D.size(1) - 1;
            for (int i15{0}; i15 <= l_loop_ub; i15++) {
                int n_loop_ub;
                n_loop_ub = r3D.size(0) - 1;
                for (int i19{0}; i19 <= n_loop_ub; i19++) {
                    b_r3D[i19 + b_r3D.size(0) * i15] = r3D[i19 + r3D.size(0) * i15];
                }
            }
            ctx_kin->joint(r0D, b_r1D, b_r2D, b_r3D, a__1, r1D, r2D, r3D);
        }
        // 'buildConstrJerk:40' for j = 1 : Ndim
        if (0 <= ctx_cfg_NumberAxis - 1) {
            if (M < 1) {
                d_y.set_size(1, 0);
            } else {
                int e_loop_ub;
                d_y.set_size(1, M);
                e_loop_ub = M - 1;
                for (int i9{0}; i9 <= e_loop_ub; i9++) {
                    d_y[i9] = i9 + 1U;
                }
            }
            i10 = r2D.size(1);
            h_loop_ub = r2D.size(1);
            i13 = r1D.size(1);
            i_loop_ub = r1D.size(1);
            k_loop_ub = d_y.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int f_y;
            int i27;
            int i33;
            int i37;
            int i38;
            int i40;
            int i44;
            int i46;
            int i49;
            int i50;
            int i51;
            int i52;
            int inner;
            int mc;
            int u_loop_ub;
            //  Compute the jerk matrix
            // 'buildConstrJerk:41' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            f_y = static_cast<int>(static_cast<double>(j) * static_cast<double>(M)) - 1;
            // 'buildConstrJerk:42' Jerk( ind, : ) = ( r3D( j, : )' .* BasisVal + 1.5 * r2D( j, : )'
            // ... 'buildConstrJerk:43'                         .* BasisValD + 0.5 * r1D( j, : )' .*
            // BasisValDD ) ... 'buildConstrJerk:44'                         .* sqrt( BasisVal *
            // coeff( :, k ) );
            r.set_size(i10);
            for (int i17{0}; i17 < h_loop_ub; i17++) {
                r[i17] = 1.5 * r2D[j + r2D.size(0) * i17];
            }
            r1.set_size(i13);
            for (int i22{0}; i22 < i_loop_ub; i22++) {
                r1[i22] = 0.5 * r1D[j + r1D.size(0) * i22];
            }
            mc = BasisVal.size(0) - 1;
            inner = BasisVal.size(1);
            r2.set_size(BasisVal.size(0));
            for (int c_i{0}; c_i <= mc; c_i++) {
                r2[c_i] = 0.0;
            }
            for (int d_k{0}; d_k < inner; d_k++) {
                for (int d_i{0}; d_i <= mc; d_i++) {
                    r2[d_i] = r2[d_i] + BasisVal[d_i + BasisVal.size(0) * d_k] *
                                            coeff[d_k + coeff.size(0) * b_k];
                }
            }
            i27 = r2.size(0);
            for (int f_k{0}; f_k < i27; f_k++) {
                r2[f_k] = std::sqrt(r2[f_k]);
            }
            r3.set_size(d_y.size(1));
            for (int i29{0}; i29 < k_loop_ub; i29++) {
                r3[i29] = static_cast<int>(d_y[i29]) + f_y;
            }
            u_loop_ub = BasisVal.size(1);
            if (r3D.size(1) == 1) {
                i33 = BasisVal.size(0);
            } else {
                i33 = r3D.size(1);
            }
            if (r.size(0) == 1) {
                i37 = BasisValD.size(0);
            } else {
                i37 = r.size(0);
            }
            if (r3D.size(1) == 1) {
                i38 = BasisVal.size(0);
            } else {
                i38 = r3D.size(1);
            }
            if (i38 == 1) {
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
            if (r1.size(0) == 1) {
                i44 = BasisValDD.size(0);
            } else {
                i44 = r1.size(0);
            }
            if (BasisVal.size(1) == 1) {
                i46 = BasisValD.size(1);
            } else {
                i46 = BasisVal.size(1);
            }
            if (r3D.size(1) == 1) {
                i49 = BasisVal.size(0);
            } else {
                i49 = r3D.size(1);
            }
            if (i49 == 1) {
                if (r.size(0) == 1) {
                    i50 = BasisValD.size(0);
                } else {
                    i50 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i50 = BasisVal.size(0);
            } else {
                i50 = r3D.size(1);
            }
            if (r3D.size(1) == 1) {
                i51 = BasisVal.size(0);
            } else {
                i51 = r3D.size(1);
            }
            if (i50 == 1) {
                if (r1.size(0) == 1) {
                    i52 = BasisValDD.size(0);
                } else {
                    i52 = r1.size(0);
                }
            } else if (i51 == 1) {
                if (r.size(0) == 1) {
                    i52 = BasisValD.size(0);
                } else {
                    i52 = r.size(0);
                }
            } else if (r3D.size(1) == 1) {
                i52 = BasisVal.size(0);
            } else {
                i52 = r3D.size(1);
            }
            if ((BasisVal.size(0) == r3D.size(1)) && (r.size(0) == BasisValD.size(0)) &&
                (i33 == i37) && (BasisVal.size(1) == BasisValD.size(1)) &&
                (r1.size(0) == BasisValDD.size(0)) && (i40 == i44) && (i46 == BasisValDD.size(1)) &&
                (i52 == r2.size(0))) {
                for (int i53{0}; i53 < u_loop_ub; i53++) {
                    int ab_loop_ub;
                    ab_loop_ub = r3D.size(1);
                    for (int i54{0}; i54 < ab_loop_ub; i54++) {
                        Jerk[r3[i54] + Jerk.size(0) * i53] =
                            ((r3D[j + r3D.size(0) * i54] * BasisVal[i54 + BasisVal.size(0) * i53] +
                              r[i54] * BasisValD[i54 + BasisValD.size(0) * i53]) +
                             r1[i54] * BasisValDD[i54 + BasisValDD.size(0) * i53]) *
                            r2[i54];
                    }
                }
            } else {
                binary_expand_op(Jerk, r3, r3D, j, r3D.size(1), BasisVal, r, BasisValD, r1,
                                 BasisValDD, r2);
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
        m_loop_ub = g_y.size(1);
        for (int i18{0}; i18 < m_loop_ub; i18++) {
            indAL[i18] = g_y[i18] + e_y;
        }
        // 'buildConstrJerk:48' indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
        if (N < 1) {
            d_y.set_size(1, 0);
        } else {
            int q_loop_ub;
            d_y.set_size(1, N);
            q_loop_ub = N - 1;
            for (int i25{0}; i25 <= q_loop_ub; i25++) {
                d_y[i25] = i25 + 1U;
            }
        }
        // 'buildConstrJerk:49' Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
        r3.set_size(indAL.size(1));
        r_loop_ub = indAL.size(1);
        for (int i26{0}; i26 < r_loop_ub; i26++) {
            r3[i26] = indAL[i26] - 1;
        }
        e_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        r4.set_size(d_y.size(1));
        s_loop_ub = d_y.size(1);
        for (int i28{0}; i28 < s_loop_ub; i28++) {
            r4[i28] = static_cast<int>(static_cast<double>(d_y[i28]) + e_k) - 1;
        }
        t_loop_ub = Jerk.size(1);
        c_varargin_2.set_size(Jerk.size(0), Jerk.size(1));
        for (int i31{0}; i31 < t_loop_ub; i31++) {
            int v_loop_ub;
            v_loop_ub = Jerk.size(0);
            for (int i36{0}; i36 < v_loop_ub; i36++) {
                c_varargin_2[i36 + c_varargin_2.size(0) * i31] = -Jerk[i36 + Jerk.size(0) * i31];
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
            x_loop_ub = Jerk.size(0);
        } else {
            x_loop_ub = 0;
        }
        if (b_empty_non_axis_sizes ||
            ((c_varargin_2.size(0) != 0) && (c_varargin_2.size(1) != 0))) {
            y_loop_ub = c_varargin_2.size(0);
        } else {
            y_loop_ub = 0;
        }
        for (int i41{0}; i41 < c_result; i41++) {
            for (int i43{0}; i43 < x_loop_ub; i43++) {
                Aj[r3[i43] + Aj.size(0) * r4[i41]] = Jerk[i43 + x_loop_ub * i41];
            }
        }
        for (int i42{0}; i42 < c_result; i42++) {
            for (int i45{0}; i45 < y_loop_ub; i45++) {
                Aj[r3[i45 + x_loop_ub] + Aj.size(0) * r4[i42]] =
                    c_varargin_2[i45 + y_loop_ub * i42];
            }
        }
        // 'buildConstrJerk:50' bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
        unnamed_idx_1 = b_b.size(0) * b_b.size(1);
        b_unnamed_idx_1 = b_b.size(0) * b_b.size(1);
        for (int i47{0}; i47 < unnamed_idx_1; i47++) {
            bj[indAL[i47] - 1] = b_b[i47];
        }
        for (int i48{0}; i48 < b_unnamed_idx_1; i48++) {
            bj[indAL[i48 + unnamed_idx_1] - 1] = b_b[i48];
        }
    }
    //  Slack variables
    // 'buildConstrJerk:54' [ nAL, nAc ] = size( Aj );
    // 'buildConstrJerk:55' A = [ Aj, - ones( nAL, 1 ) ; zeros( 1, nAc ), -1 ];
    varargin_2.set_size(Aj.size(0));
    c_loop_ub = Aj.size(0);
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        varargin_2[i7] = -1;
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
    for (int i16{0}; i16 < input_sizes_idx_1; i16++) {
        for (int i20{0}; i20 < result; i20++) {
            b_result[i20 + b_result.size(0) * i16] = Aj[i20 + result * i16];
        }
    }
    o_loop_ub = b_input_sizes_idx_1;
    for (int i21{0}; i21 < o_loop_ub; i21++) {
        for (int i23{0}; i23 < result; i23++) {
            b_result[i23 + b_result.size(0) * input_sizes_idx_1] = -1.0;
        }
    }
    b_varargin_2.set_size(1, Aj.size(1) + 1);
    p_loop_ub = Aj.size(1);
    for (int i24{0}; i24 < p_loop_ub; i24++) {
        b_varargin_2[i24] = 0;
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
        i30 = b_result.size(0);
    } else {
        i30 = 0;
    }
    A.set_size(i30 + 1, sizes_idx_1);
    for (int i32{0}; i32 < sizes_idx_1; i32++) {
        for (int i35{0}; i35 < input_sizes_idx_0; i35++) {
            A[i35 + A.size(0) * i32] = b_result[i35 + input_sizes_idx_0 * i32];
        }
    }
    for (int i34{0}; i34 < sizes_idx_1; i34++) {
        A[input_sizes_idx_0 + A.size(0) * i34] = b_varargin_2[i34];
    }
    // 'buildConstrJerk:57' b = [ bj ; 0 ];
    b.set_size(bj.size(0) + 1);
    w_loop_ub = bj.size(0);
    for (int i39{0}; i39 < w_loop_ub; i39++) {
        b[i39] = bj[i39];
    }
    b[bj.size(0)] = 0.0;
    // 'buildConstrJerk:59' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstrJerk.cpp
//
// [EOF]
//
