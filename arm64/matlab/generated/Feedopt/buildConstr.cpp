//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstr.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "buildConstr.h"
#include "EvalCurvStruct.h"
#include "colon.h"
#include "linspace.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "repmat.h"
#include "vecnorm.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &Acc, const ::coder::array<int, 1U> &r,
                             const ::coder::array<double, 2U> &r2D, int j, int i4,
                             const ::coder::array<double, 2U> &BasisVal,
                             const ::coder::array<double, 1U> &r1,
                             const ::coder::array<double, 2U> &BasisValD);

static void binary_expand_op(::coder::array<double, 2U> &Aeq, const int indAEL[4],
                             const ::coder::array<int, 1U> &r,
                             const ::coder::array<double, 3U> &v2_vec, int k,
                             const ::coder::array<double, 3U> &at_norm,
                             const signed char mask_continuity[4]);

static void binary_expand_op(::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &ramp);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &Acc
//                const ::coder::array<int, 1U> &r
//                const ::coder::array<double, 2U> &r2D
//                int j
//                int i4
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 1U> &r1
//                const ::coder::array<double, 2U> &BasisValD
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &Acc, const ::coder::array<int, 1U> &r,
                             const ::coder::array<double, 2U> &r2D, int j, int i4,
                             const ::coder::array<double, 2U> &BasisVal,
                             const ::coder::array<double, 1U> &r1,
                             const ::coder::array<double, 2U> &BasisValD)
{
    int aux_1_1;
    int aux_3_1;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_3_0;
    int stride_3_1;
    int unnamed_idx_0;
    unnamed_idx_0 = r1.size(0);
    stride_0_0 = (i4 != 1);
    stride_1_0 = (BasisVal.size(0) != 1);
    stride_1_1 = (BasisVal.size(1) != 1);
    stride_2_0 = (unnamed_idx_0 != 1);
    stride_3_0 = (BasisValD.size(0) != 1);
    stride_3_1 = (BasisValD.size(1) != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    if (BasisValD.size(1) == 1) {
        i = 1;
    } else {
        i = BasisValD.size(1);
    }
    if (i == 1) {
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
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        int i2;
        if (BasisValD.size(0) == 1) {
            i2 = unnamed_idx_0;
        } else {
            i2 = BasisValD.size(0);
        }
        if (i2 == 1) {
            if (BasisVal.size(0) == 1) {
                b_loop_ub = i4;
            } else {
                b_loop_ub = BasisVal.size(0);
            }
        } else if (BasisValD.size(0) == 1) {
            b_loop_ub = unnamed_idx_0;
        } else {
            b_loop_ub = BasisValD.size(0);
        }
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            Acc[r[i3] + Acc.size(0) * i1] =
                r2D[j + r2D.size(0) * (i3 * stride_0_0)] *
                    BasisVal[i3 * stride_1_0 + BasisVal.size(0) * aux_1_1] +
                r1[i3 * stride_2_0] * BasisValD[i3 * stride_3_0 + BasisValD.size(0) * aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &Aeq
//                const int indAEL[4]
//                const ::coder::array<int, 1U> &r
//                const ::coder::array<double, 3U> &v2_vec
//                int k
//                const ::coder::array<double, 3U> &at_norm
//                const signed char mask_continuity[4]
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &Aeq, const int indAEL[4],
                             const ::coder::array<int, 1U> &r,
                             const ::coder::array<double, 3U> &v2_vec, int k,
                             const ::coder::array<double, 3U> &at_norm,
                             const signed char mask_continuity[4])
{
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_v2_vec;
    int aux_0_1;
    int aux_1_1;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i4;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    loop_ub = v2_vec.size(1);
    b_loop_ub = at_norm.size(1);
    c_loop_ub = v2_vec.size(1);
    d_loop_ub = at_norm.size(1);
    b_v2_vec.set_size(4, loop_ub);
    for (int i{0}; i < loop_ub; i++) {
        b_v2_vec[4 * i] = v2_vec[2 * i + 2 * v2_vec.size(1) * k];
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b_v2_vec[4 * i1 + 1] = at_norm[2 * i1 + 2 * at_norm.size(1) * k];
    }
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        b_v2_vec[4 * i2 + 2] = v2_vec[(2 * i2 + 2 * v2_vec.size(1) * k) + 1];
    }
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        b_v2_vec[4 * i3 + 3] = at_norm[(2 * i3 + 2 * at_norm.size(1) * k) + 1];
    }
    if (b_v2_vec.size(1) == 1) {
        i4 = r.size(0);
    } else {
        i4 = b_v2_vec.size(1);
    }
    b_Aeq.set_size(4, i4);
    stride_0_1 = (r.size(0) != 1);
    stride_1_1 = (b_v2_vec.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (b_v2_vec.size(1) == 1) {
        e_loop_ub = r.size(0);
    } else {
        e_loop_ub = b_v2_vec.size(1);
    }
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        b_Aeq[4 * i5] = Aeq[(indAEL[0] + Aeq.size(0) * (r[aux_0_1] - 1)) - 1] +
                        b_v2_vec[4 * aux_1_1] * static_cast<double>(mask_continuity[0]);
        b_Aeq[4 * i5 + 1] = Aeq[(indAEL[1] + Aeq.size(0) * (r[aux_0_1] - 1)) - 1] +
                            b_v2_vec[4 * aux_1_1 + 1] * static_cast<double>(mask_continuity[1]);
        b_Aeq[4 * i5 + 2] = Aeq[(indAEL[2] + Aeq.size(0) * (r[aux_0_1] - 1)) - 1] +
                            b_v2_vec[4 * aux_1_1 + 2] * static_cast<double>(mask_continuity[2]);
        b_Aeq[4 * i5 + 3] = Aeq[(indAEL[3] + Aeq.size(0) * (r[aux_0_1] - 1)) - 1] +
                            b_v2_vec[4 * aux_1_1 + 3] * static_cast<double>(mask_continuity[3]);
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    f_loop_ub = b_Aeq.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        Aeq[(indAEL[0] + Aeq.size(0) * (r[i6] - 1)) - 1] = b_Aeq[4 * i6];
        Aeq[(indAEL[1] + Aeq.size(0) * (r[i6] - 1)) - 1] = b_Aeq[4 * i6 + 1];
        Aeq[(indAEL[2] + Aeq.size(0) * (r[i6] - 1)) - 1] = b_Aeq[4 * i6 + 2];
        Aeq[(indAEL[3] + Aeq.size(0) * (r[i6] - 1)) - 1] = b_Aeq[4 * i6 + 3];
    }
}

//
// Arguments    : ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &ramp
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &ramp)
{
    ::coder::array<double, 1U> b_b;
    int b_loop_ub;
    int b_ramp;
    int c_ramp;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_ramp = ramp.size(0) * ramp.size(1);
    if (b_ramp == 1) {
        c_ramp = b.size(0);
    } else {
        c_ramp = b_ramp;
    }
    b_b.set_size(c_ramp);
    stride_0_0 = (b.size(0) != 1);
    stride_1_0 = (b_ramp != 1);
    if (b_ramp == 1) {
        loop_ub = b.size(0);
    } else {
        loop_ub = b_ramp;
    }
    for (int i{0}; i < loop_ub; i++) {
        b_b[i] = b[i * stride_0_0] * ramp[i * stride_1_0];
    }
    b.set_size(b_b.size(0));
    b_loop_ub = b_b.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b[i1] = b_b[i1];
    }
}

//
// function [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, windowCurv, amax, ...
//     v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec )
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
//                double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS
//                double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS
//                const ::coder::array<CurvStruct, 2U> &windowCurv
//                const double amax[6]
//                double v_0
//                double at_0
//                double v_1
//                double at_1
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 2U> &BasisValD
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &b
//                ::coder::array<double, 2U> &Aeq
//                ::coder::array<double, 1U> &beq
//                ::coder::array<double, 2U> &continuity
// Return Type  : void
//
void buildConstr(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                 int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                 const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                 const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                 double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS,
                 const ::coder::array<CurvStruct, 2U> &windowCurv, const double amax[6], double v_0,
                 double at_0, double v_1, double at_1, const ::coder::array<double, 2U> &BasisVal,
                 const ::coder::array<double, 2U> &BasisValD,
                 const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &A,
                 ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq,
                 ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &continuity)
{
    static const signed char mask_continuity[4]{1, 1, -1, -1};
    ::coder::array<double, 3U> at_norm;
    ::coder::array<double, 3U> t_vec;
    ::coder::array<double, 3U> v2_vec;
    ::coder::array<double, 2U> Acc;
    ::coder::array<double, 2U> C;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> acc_ramp;
    ::coder::array<double, 2U> amax_data;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_amax;
    ::coder::array<double, 2U> b_v2_vec;
    ::coder::array<double, 2U> b_vel_ramp;
    ::coder::array<double, 2U> d_varargin_1;
    ::coder::array<double, 2U> normR1D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> ramp;
    ::coder::array<double, 2U> v_max;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 2U> varargin_4;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> vel_ramp;
    ::coder::array<unsigned int, 2U> e_y;
    ::coder::array<int, 2U> indAC_tmp;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 2U> indAT;
    ::coder::array<int, 2U> r1;
    ::coder::array<int, 1U> r4;
    ::coder::array<int, 1U> r5;
    ::coder::array<signed char, 2U> b_varargin_1;
    double b_amax_data[6];
    double dv[6];
    double dv2[6];
    double dv1[3];
    double dv3[3];
    double d_y[2];
    double Nec;
    double Nx;
    int indAEL[4];
    int iv[2];
    int iv1[2];
    int M;
    int N;
    int ab_loop_ub;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_unnamed_idx_1;
    int b_y;
    int bb_loop_ub;
    int c_loop_ub;
    int c_y;
    int cb_loop_ub;
    int e_loop_ub;
    int eb_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int hb_loop_ub;
    int i22;
    int i37;
    int input_sizes_idx_0;
    int j_loop_ub;
    int jb_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int nb_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int pb_loop_ub;
    int q_loop_ub;
    int result;
    int t_loop_ub;
    int tmp_data_idx_1;
    int varargin_1;
    int y;
    int y_loop_ub;
    int y_tmp;
    bool empty_non_axis_sizes;
    // 'buildConstr:5' c_prof_in(mfilename);
    //  Ndim     : number of dimention
    //  NWindow  : number of axes
    // 'buildConstr:8' Ndim        = ctx.cfg.NumberAxis;
    // 'buildConstr:9' Nwindow     = length( windowCurv );
    //  M     : number of discretization
    //  N     : number of coefficients
    //  Nx    : number of decision variable
    //  Nc    : number of inequality constraints
    //  Nec   : number of equality constraints
    // 'buildConstr:16' [ M, N ]    = size( BasisVal );
    N = BasisVal.size(1);
    M = BasisVal.size(0);
    // 'buildConstr:17' Nx          = N * Nwindow;
    Nx = static_cast<double>(BasisVal.size(1)) * static_cast<double>(windowCurv.size(1));
    // 'buildConstr:18' Nc          = ( 2 + 2 * Ndim );
    y_tmp = ctx_cfg_NumberAxis << 1;
    // 'buildConstr:19' Nec         = 2 * ( Nwindow + 1 );
    Nec = 2.0 * (static_cast<double>(windowCurv.size(1)) + 1.0);
    //  A         : Matrix for equality constraints
    //  b         : Vector for equality constraints
    //  Aeq       : Matrix for inequality constraints
    //  beq       : Vector for inequality constraints
    //  amaxTot   : Acceleration max total ( cart + rot )
    //  b_amax    : Vector for maximum acceleration
    // 'buildConstr:27' A           = zeros( Nc * M * Nwindow,  Nx );
    y = static_cast<int>(
        static_cast<double>(static_cast<int>(static_cast<double>(y_tmp + 2) *
                                             static_cast<double>(BasisVal.size(0)))) *
        static_cast<double>(windowCurv.size(1)));
    loop_ub = static_cast<int>(static_cast<double>(BasisVal.size(1)) *
                               static_cast<double>(windowCurv.size(1)));
    A.set_size(y, static_cast<int>(Nx));
    for (int i{0}; i < loop_ub; i++) {
        for (int i1{0}; i1 < y; i1++) {
            A[i1 + A.size(0) * i] = 0.0;
        }
    }
    // 'buildConstr:28' b           = zeros( Nc * M * Nwindow,  1 );
    b_y = static_cast<int>(
        static_cast<double>(static_cast<int>(static_cast<double>(y_tmp + 2) *
                                             static_cast<double>(BasisVal.size(0)))) *
        static_cast<double>(windowCurv.size(1)));
    b.set_size(b_y);
    for (int i2{0}; i2 < b_y; i2++) {
        b[i2] = 0.0;
    }
    int i3;
    // 'buildConstr:29' Aeq         = zeros( Nec, Nx );
    b_loop_ub = static_cast<int>(2.0 * (static_cast<double>(windowCurv.size(1)) + 1.0));
    i3 = static_cast<int>(Nec);
    Aeq.set_size(i3, static_cast<int>(Nx));
    for (int i4{0}; i4 < loop_ub; i4++) {
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            Aeq[i5 + Aeq.size(0) * i4] = 0.0;
        }
    }
    int i6;
    // 'buildConstr:30' beq         = zeros( Nec, 1 );
    i6 = static_cast<int>(Nec);
    beq.set_size(i6);
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        beq[i7] = 0.0;
    }
    // 'buildConstr:31' amaxTot     = amax( ctx.cfg.indTot );
    // 'buildConstr:32' b_amax      = repmat( amaxTot, M, 1 );
    for (int i8{0}; i8 < ctx_cfg_indTot_size; i8++) {
        b_amax_data[i8] = amax[ctx_cfg_indTot_data[i8] - 1];
    }
    amax_data.set(&b_amax_data[0], 1, ctx_cfg_indTot_size);
    varargin_1 = BasisVal.size(0);
    r.set_size(varargin_1, amax_data.size(1));
    if ((varargin_1 != 0) && (amax_data.size(1) != 0)) {
        int na;
        na = amax_data.size(1);
        for (int k{0}; k < na; k++) {
            int i10;
            i10 = varargin_1 - 1;
            for (int t{0}; t <= i10; t++) {
                r[t + r.size(0) * k] = amax_data[k];
            }
        }
    }
    b_amax.set_size(r.size(0), r.size(1));
    c_loop_ub = r.size(1);
    for (int i9{0}; i9 < c_loop_ub; i9++) {
        int d_loop_ub;
        d_loop_ub = r.size(0);
        for (int i11{0}; i11 < d_loop_ub; i11++) {
            b_amax[i11 + b_amax.size(0) * i9] = r[i11 + r.size(0) * i9];
        }
    }
    //  at_norm   : Norm of tangential acceleration vector
    //  t_vec     : Unit vector tangential to the curve
    //  Acc       : Matrix of the acceleration by axis
    //  Aw        : Cell of the matrix of inequality const. by window
    //  bw        : Cell of the vector of inequality const. by window
    //  indAT     : Indexis for at_norm at continuity points
    //  mask_continuity : Mask used in the recursive form the continuity equ.
    // 'buildConstr:41' at_norm     = zeros( 2, N, Nwindow );
    at_norm.set_size(2, BasisVal.size(1), windowCurv.size(1));
    e_loop_ub = windowCurv.size(1);
    for (int i12{0}; i12 < e_loop_ub; i12++) {
        int f_loop_ub;
        f_loop_ub = BasisVal.size(1);
        for (int i13{0}; i13 < f_loop_ub; i13++) {
            at_norm[2 * i13 + 2 * at_norm.size(1) * i12] = 0.0;
            at_norm[(2 * i13 + 2 * at_norm.size(1) * i12) + 1] = 0.0;
        }
    }
    // 'buildConstr:42' t_vec       = zeros( Ndim, 2, Nwindow );
    t_vec.set_size(ctx_cfg_NumberAxis, 2, windowCurv.size(1));
    g_loop_ub = windowCurv.size(1);
    for (int i14{0}; i14 < g_loop_ub; i14++) {
        for (int i15{0}; i15 < 2; i15++) {
            for (int i16{0}; i16 < ctx_cfg_NumberAxis; i16++) {
                t_vec[(i16 + t_vec.size(0) * i15) + t_vec.size(0) * 2 * i14] = 0.0;
            }
        }
    }
    // 'buildConstr:43' v2_vec      = zeros( 2, N, Nwindow );
    v2_vec.set_size(2, BasisVal.size(1), windowCurv.size(1));
    h_loop_ub = windowCurv.size(1);
    for (int i17{0}; i17 < h_loop_ub; i17++) {
        int i_loop_ub;
        i_loop_ub = BasisVal.size(1);
        for (int i18{0}; i18 < i_loop_ub; i18++) {
            v2_vec[2 * i18 + 2 * v2_vec.size(1) * i17] = 0.0;
            v2_vec[(2 * i18 + 2 * v2_vec.size(1) * i17) + 1] = 0.0;
        }
    }
    // 'buildConstr:44' Acc         = zeros( M * Ndim , N );
    c_y = static_cast<int>(static_cast<double>(BasisVal.size(0)) *
                           static_cast<double>(ctx_cfg_NumberAxis));
    Acc.set_size(c_y, BasisVal.size(1));
    j_loop_ub = BasisVal.size(1);
    for (int i19{0}; i19 < j_loop_ub; i19++) {
        for (int i20{0}; i20 < c_y; i20++) {
            Acc[i20 + Acc.size(0) * i19] = 0.0;
        }
    }
    // 'buildConstr:45' indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );
    coder::eml_integer_colon_dispatcher(ctx_cfg_NumberAxis, r1);
    tmp_data_idx_1 = BasisVal.size(0);
    indAT.set_size(2, r1.size(1));
    k_loop_ub = r1.size(1);
    for (int i21{0}; i21 < k_loop_ub; i21++) {
        int indAT_tmp;
        indAT_tmp = r1[i21] - 1;
        indAT[2 * i21] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                          static_cast<double>(BasisVal.size(0))) +
                         1;
        indAT[2 * i21 + 1] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                              static_cast<double>(BasisVal.size(0))) +
                             tmp_data_idx_1;
    }
    // 'buildConstr:46' mask_continuity = [ 1; 1; -1; -1 ];
    // 'buildConstr:48' for k = 1 : Nwindow
    i22 = windowCurv.size(1);
    if (0 <= windowCurv.size(1) - 1) {
        int unnamed_idx_1;
        coder::eml_integer_colon_dispatcher(static_cast<int>(static_cast<double>(y_tmp + 2) *
                                                             static_cast<double>(BasisVal.size(0))),
                                            r1);
        l_loop_ub = r1.size(1);
        unnamed_idx_1 = b_amax.size(0) * b_amax.size(1);
        n_loop_ub = unnamed_idx_1;
    }
    if (0 <= i22 - 1) {
        m_loop_ub = BasisVal.size(1);
        b_unnamed_idx_1 = b_amax.size(0) * b_amax.size(1);
        o_loop_ub = BasisVal.size(1);
    }
    for (int b_k{0}; b_k < i22; b_k++) {
        double c_k;
        double z1_idx_0;
        double z1_idx_1;
        int ac_loop_ub;
        int b_inner;
        int b_nc;
        int bc_loop_ub;
        int c_result;
        int c_unnamed_idx_1;
        int cc_loop_ub;
        int d_k;
        int d_unnamed_idx_1;
        int dc_loop_ub;
        int f_y;
        int ib_loop_ub;
        int inner;
        int kb_loop_ub;
        int nc;
        int ob_loop_ub;
        int qb_loop_ub;
        int r_loop_ub;
        int tb_loop_ub;
        int u_loop_ub;
        int ub_loop_ub;
        int vb_loop_ub;
        int w_loop_ub;
        int wb_loop_ub;
        int xb_loop_ub;
        int yb_loop_ub;
        bool c_empty_non_axis_sizes;
        //  Compute the partial derivatives
        // 'buildConstr:50' [ ~, r1D, r2D, ~ ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
        for (int i23{0}; i23 < 6; i23++) {
            dv[i23] = windowCurv[b_k].R0[i23];
        }
        for (int i24{0}; i24 < 6; i24++) {
            dv2[i24] = windowCurv[b_k].R1[i24];
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
                         a__2);
        //  Tangent unit vector at start and at end
        // 'buildConstr:52' normR1D = vecnorm( r1D );
        coder::vecnorm(r1D, normR1D);
        // 'buildConstr:53' t_vec( : , :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );
        iv[0] = 0;
        iv[1] = r1D.size(1) - 1;
        r_loop_ub = r1D.size(0);
        x.set_size(r1D.size(0), 2);
        iv1[0] = 0;
        iv1[1] = normR1D.size(1) - 1;
        for (int i27{0}; i27 < 2; i27++) {
            for (int i29{0}; i29 < r_loop_ub; i29++) {
                x[i29 + x.size(0) * i27] = r1D[i29 + r1D.size(0) * iv[i27]];
            }
            d_y[i27] = normR1D[iv1[i27]];
        }
        u_loop_ub = x.size(0);
        for (int i31{0}; i31 < 2; i31++) {
            for (int i33{0}; i33 < u_loop_ub; i33++) {
                t_vec[(i33 + t_vec.size(0) * i31) + t_vec.size(0) * 2 * b_k] =
                    x[i33 + x.size(0) * i31] / d_y[i31];
            }
        }
        //  Maximum constraint on the speed
        // 'buildConstr:55' v_max = ( windowCurv( k ).Info.FeedRate ./ normR1D ).^2;
        v_max.set_size(1, normR1D.size(1));
        w_loop_ub = normR1D.size(1);
        for (int i34{0}; i34 < w_loop_ub; i34++) {
            double c_varargin_1;
            c_varargin_1 = windowCurv[b_k].Info.FeedRate / normR1D[i34];
            v_max[i34] = std::pow(c_varargin_1, 2.0);
        }
        // 'buildConstr:57' for j = 1 : Ndim
        if (0 <= ctx_cfg_NumberAxis - 1) {
            if (M < 1) {
                e_y.set_size(1, 0);
            } else {
                int x_loop_ub;
                e_y.set_size(1, M);
                x_loop_ub = M - 1;
                for (int i36{0}; i36 <= x_loop_ub; i36++) {
                    e_y[i36] = i36 + 1U;
                }
            }
            i37 = r1D.size(1);
            y_loop_ub = r1D.size(1);
            ab_loop_ub = e_y.size(1);
            bb_loop_ub = BasisVal.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int g_y;
            int i51;
            int i58;
            //  Compute the acceleration matrix
            // 'buildConstr:58' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            g_y = static_cast<int>((static_cast<double>(j + 1) - 1.0) * static_cast<double>(M)) - 1;
            // 'buildConstr:59' Acc( ind, : ) = r2D( j, : )' .* BasisVal + 0.5 * r1D( j, : )' .*
            // BasisValD;
            r3.set_size(i37);
            for (int i43{0}; i43 < y_loop_ub; i43++) {
                r3[i43] = 0.5 * r1D[j + r1D.size(0) * i43];
            }
            r4.set_size(e_y.size(1));
            for (int i46{0}; i46 < ab_loop_ub; i46++) {
                r4[i46] = static_cast<int>(e_y[i46]) + g_y;
            }
            if (r2D.size(1) == 1) {
                i51 = BasisVal.size(0);
            } else {
                i51 = r2D.size(1);
            }
            if (r3.size(0) == 1) {
                i58 = BasisValD.size(0);
            } else {
                i58 = r3.size(0);
            }
            if ((BasisVal.size(0) == r2D.size(1)) && (r3.size(0) == BasisValD.size(0)) &&
                (i51 == i58) && (BasisVal.size(1) == BasisValD.size(1))) {
                for (int i61{0}; i61 < bb_loop_ub; i61++) {
                    int mb_loop_ub;
                    mb_loop_ub = r2D.size(1);
                    for (int i64{0}; i64 < mb_loop_ub; i64++) {
                        Acc[r4[i64] + Acc.size(0) * i61] =
                            r2D[j + r2D.size(0) * i64] * BasisVal[i64 + BasisVal.size(0) * i61] +
                            r3[i64] * BasisValD[i64 + BasisValD.size(0) * i61];
                    }
                }
            } else {
                binary_expand_op(Acc, r4, r2D, j, r2D.size(1), BasisVal, r3, BasisValD);
            }
        }
        //  Inequality constraints
        // 'buildConstr:63' indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
        f_y = static_cast<int>(
            static_cast<double>(static_cast<int>(((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 static_cast<double>(y_tmp + 2))) *
            static_cast<double>(M));
        indAL.set_size(1, r1.size(1));
        for (int i41{0}; i41 < l_loop_ub; i41++) {
            indAL[i41] = r1[i41] + f_y;
        }
        // 'buildConstr:64' indAC   = int32( 1 : N  ) + ( k - 1 ) * N;
        if (N < 1) {
            e_y.set_size(1, 0);
        } else {
            int gb_loop_ub;
            e_y.set_size(1, N);
            gb_loop_ub = N - 1;
            for (int i50{0}; i50 <= gb_loop_ub; i50++) {
                e_y[i50] = i50 + 1U;
            }
        }
        c_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        indAC_tmp.set_size(1, e_y.size(1));
        ib_loop_ub = e_y.size(1);
        for (int i55{0}; i55 < ib_loop_ub; i55++) {
            indAC_tmp[i55] = static_cast<int>(static_cast<double>(e_y[i55]) + c_k);
        }
        // 'buildConstr:65' A( indAL, indAC )   = [ BasisVal; -BasisVal ; Acc ; -Acc ];
        r4.set_size(indAL.size(1));
        kb_loop_ub = indAL.size(1);
        for (int i62{0}; i62 < kb_loop_ub; i62++) {
            r4[i62] = indAL[i62] - 1;
        }
        r5.set_size(indAC_tmp.size(1));
        ob_loop_ub = indAC_tmp.size(1);
        for (int i65{0}; i65 < ob_loop_ub; i65++) {
            r5[i65] = indAC_tmp[i65] - 1;
        }
        varargin_2.set_size(BasisVal.size(0), BasisVal.size(1));
        for (int i67{0}; i67 < m_loop_ub; i67++) {
            int rb_loop_ub;
            rb_loop_ub = BasisVal.size(0);
            for (int i69{0}; i69 < rb_loop_ub; i69++) {
                varargin_2[i69 + varargin_2.size(0) * i67] =
                    -BasisVal[i69 + BasisVal.size(0) * i67];
            }
        }
        qb_loop_ub = Acc.size(1);
        varargin_4.set_size(Acc.size(0), Acc.size(1));
        for (int i70{0}; i70 < qb_loop_ub; i70++) {
            int sb_loop_ub;
            sb_loop_ub = Acc.size(0);
            for (int i71{0}; i71 < sb_loop_ub; i71++) {
                varargin_4[i71 + varargin_4.size(0) * i70] = -Acc[i71 + Acc.size(0) * i70];
            }
        }
        if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
            c_result = BasisVal.size(1);
        } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
            c_result = varargin_2.size(1);
        } else if ((Acc.size(0) != 0) && (Acc.size(1) != 0)) {
            c_result = Acc.size(1);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            c_result = varargin_4.size(1);
        } else {
            c_result = BasisVal.size(1);
            if (varargin_2.size(1) > BasisVal.size(1)) {
                c_result = varargin_2.size(1);
            }
            if (Acc.size(1) > c_result) {
                c_result = Acc.size(1);
            }
            if (varargin_4.size(1) > c_result) {
                c_result = varargin_4.size(1);
            }
        }
        c_empty_non_axis_sizes = (c_result == 0);
        if (c_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            tb_loop_ub = BasisVal.size(0);
        } else {
            tb_loop_ub = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            ub_loop_ub = varargin_2.size(0);
        } else {
            ub_loop_ub = 0;
        }
        if (c_empty_non_axis_sizes || ((Acc.size(0) != 0) && (Acc.size(1) != 0))) {
            vb_loop_ub = Acc.size(0);
        } else {
            vb_loop_ub = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            wb_loop_ub = varargin_4.size(0);
        } else {
            wb_loop_ub = 0;
        }
        for (int i72{0}; i72 < c_result; i72++) {
            for (int i74{0}; i74 < tb_loop_ub; i74++) {
                A[r4[i74] + A.size(0) * r5[i72]] = BasisVal[i74 + tb_loop_ub * i72];
            }
        }
        for (int i73{0}; i73 < c_result; i73++) {
            for (int i76{0}; i76 < ub_loop_ub; i76++) {
                A[r4[i76 + tb_loop_ub] + A.size(0) * r5[i73]] = varargin_2[i76 + ub_loop_ub * i73];
            }
        }
        for (int i75{0}; i75 < c_result; i75++) {
            for (int i78{0}; i78 < vb_loop_ub; i78++) {
                A[r4[(i78 + tb_loop_ub) + ub_loop_ub] + A.size(0) * r5[i75]] =
                    Acc[i78 + vb_loop_ub * i75];
            }
        }
        for (int i77{0}; i77 < c_result; i77++) {
            for (int i79{0}; i79 < wb_loop_ub; i79++) {
                A[r4[((i79 + tb_loop_ub) + ub_loop_ub) + vb_loop_ub] + A.size(0) * r5[i77]] =
                    varargin_4[i79 + wb_loop_ub * i77];
            }
        }
        // 'buildConstr:66' b( indAL )          = [ v_max'; zeros( size(v_max) )';
        // 'buildConstr:67'                             b_amax( : ); b_amax( : ) ];
        c_unnamed_idx_1 = v_max.size(1);
        d_unnamed_idx_1 = v_max.size(1);
        xb_loop_ub = v_max.size(1);
        for (int i80{0}; i80 < xb_loop_ub; i80++) {
            b[indAL[i80] - 1] = v_max[i80];
        }
        yb_loop_ub = v_max.size(1);
        for (int i81{0}; i81 < yb_loop_ub; i81++) {
            b[indAL[i81 + c_unnamed_idx_1] - 1] = 0.0;
        }
        for (int i82{0}; i82 < b_unnamed_idx_1; i82++) {
            b[indAL[(i82 + c_unnamed_idx_1) + d_unnamed_idx_1] - 1] = b_amax[i82];
        }
        for (int i83{0}; i83 < n_loop_ub; i83++) {
            b[indAL[((i83 + c_unnamed_idx_1) + d_unnamed_idx_1) + b_unnamed_idx_1] - 1] =
                b_amax[i83];
        }
        //  Continuity equations
        // 'buildConstr:70' indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2 ;
        d_k = (b_k << 1) + 1;
        indAEL[0] = d_k;
        indAEL[1] = d_k + 1;
        indAEL[2] = d_k + 2;
        indAEL[3] = d_k + 3;
        //  Line   index
        // 'buildConstr:71' indAEC  = int32( 1 : N ) + ( k - 1 ) * N ;
        //  Column index
        // 'buildConstr:72' at_norm( 1, :, k )   = t_vec( : , 1, k )' * Acc( indAT( 1, : ) , : );
        inner = t_vec.size(0) - 1;
        nc = Acc.size(1) - 1;
        C.set_size(1, Acc.size(1));
        for (int b_j{0}; b_j <= nc; b_j++) {
            C[b_j] = 0.0;
            for (int e_k{0}; e_k <= inner; e_k++) {
                C[b_j] = C[b_j] + t_vec[e_k + t_vec.size(0) * 2 * b_k] *
                                      Acc[(indAT[2 * e_k] + Acc.size(0) * b_j) - 1];
            }
        }
        ac_loop_ub = C.size(1);
        for (int i84{0}; i84 < ac_loop_ub; i84++) {
            at_norm[2 * i84 + 2 * at_norm.size(1) * b_k] = C[i84];
        }
        // 'buildConstr:73' at_norm( 2, :, k )   = t_vec( : , 2, k )' * Acc( indAT( 2, : ) , : );
        b_inner = t_vec.size(0) - 1;
        b_nc = Acc.size(1) - 1;
        C.set_size(1, Acc.size(1));
        for (int c_j{0}; c_j <= b_nc; c_j++) {
            C[c_j] = 0.0;
            for (int f_k{0}; f_k <= b_inner; f_k++) {
                C[c_j] = C[c_j] + t_vec[(f_k + t_vec.size(0)) + t_vec.size(0) * 2 * b_k] *
                                      Acc[(indAT[2 * f_k + 1] + Acc.size(0) * c_j) - 1];
            }
        }
        bc_loop_ub = C.size(1);
        for (int i85{0}; i85 < bc_loop_ub; i85++) {
            at_norm[(2 * i85 + 2 * at_norm.size(1) * b_k) + 1] = C[i85];
        }
        // 'buildConstr:75' v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [ 1; end ], :);
        z1_idx_0 = std::pow(normR1D[0], 2.0);
        z1_idx_1 = std::pow(normR1D[normR1D.size(1) - 1], 2.0);
        iv[1] = BasisVal.size(0) - 1;
        for (int i86{0}; i86 < o_loop_ub; i86++) {
            v2_vec[2 * i86 + 2 * v2_vec.size(1) * b_k] =
                z1_idx_0 * BasisVal[BasisVal.size(0) * i86];
            v2_vec[(2 * i86 + 2 * v2_vec.size(1) * b_k) + 1] =
                z1_idx_1 * BasisVal[iv[1] + BasisVal.size(0) * i86];
        }
        // 'buildConstr:76' continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
        // 'buildConstr:77'                    v2_vec( 2, :, k ); at_norm( 2, :, k ) ];
        // 'buildConstr:78' Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity.*
        // mask_continuity;
        r4.set_size(indAC_tmp.size(1));
        cc_loop_ub = indAC_tmp.size(1);
        for (int i87{0}; i87 < cc_loop_ub; i87++) {
            r4[i87] = indAC_tmp[i87];
        }
        dc_loop_ub = v2_vec.size(1);
        if (r4.size(0) == v2_vec.size(1)) {
            int ec_loop_ub;
            int fc_loop_ub;
            int gc_loop_ub;
            ec_loop_ub = at_norm.size(1);
            b_v2_vec.set_size(4, v2_vec.size(1));
            for (int i88{0}; i88 < dc_loop_ub; i88++) {
                b_v2_vec[4 * i88] = v2_vec[2 * i88 + 2 * v2_vec.size(1) * b_k];
            }
            for (int i89{0}; i89 < ec_loop_ub; i89++) {
                b_v2_vec[4 * i89 + 1] = at_norm[2 * i89 + 2 * at_norm.size(1) * b_k];
            }
            for (int i90{0}; i90 < dc_loop_ub; i90++) {
                b_v2_vec[4 * i90 + 2] = v2_vec[(2 * i90 + 2 * v2_vec.size(1) * b_k) + 1];
            }
            for (int i91{0}; i91 < ec_loop_ub; i91++) {
                b_v2_vec[4 * i91 + 3] = at_norm[(2 * i91 + 2 * at_norm.size(1) * b_k) + 1];
            }
            b_Aeq.set_size(4, r4.size(0));
            fc_loop_ub = r4.size(0);
            for (int i92{0}; i92 < fc_loop_ub; i92++) {
                b_Aeq[4 * i92] = Aeq[(d_k + Aeq.size(0) * (r4[i92] - 1)) - 1] + b_v2_vec[4 * i92];
                b_Aeq[4 * i92 + 1] = Aeq[d_k + Aeq.size(0) * (r4[i92] - 1)] + b_v2_vec[4 * i92 + 1];
                b_Aeq[4 * i92 + 2] =
                    Aeq[(d_k + Aeq.size(0) * (r4[i92] - 1)) + 1] + -b_v2_vec[4 * i92 + 2];
                b_Aeq[4 * i92 + 3] =
                    Aeq[(d_k + Aeq.size(0) * (r4[i92] - 1)) + 2] + -b_v2_vec[4 * i92 + 3];
            }
            gc_loop_ub = b_Aeq.size(1);
            for (int i93{0}; i93 < gc_loop_ub; i93++) {
                Aeq[(d_k + Aeq.size(0) * (r4[i93] - 1)) - 1] = b_Aeq[4 * i93];
                Aeq[d_k + Aeq.size(0) * (r4[i93] - 1)] = b_Aeq[4 * i93 + 1];
                Aeq[(d_k + Aeq.size(0) * (r4[i93] - 1)) + 1] = b_Aeq[4 * i93 + 2];
                Aeq[(d_k + Aeq.size(0) * (r4[i93] - 1)) + 2] = b_Aeq[4 * i93 + 3];
            }
        } else {
            binary_expand_op(Aeq, indAEL, r4, v2_vec, b_k, at_norm, mask_continuity);
        }
    }
    // 'buildConstr:81' beq( [ 1, 2, end-1, end ] ) = [ v_0^2; at_0; v_1^2; at_1 ] .*
    // mask_continuity;
    beq[0] = v_0 * v_0;
    beq[1] = at_0;
    beq[static_cast<int>(Nec) - 2] = -(v_1 * v_1);
    beq[static_cast<int>(Nec) - 1] = -at_1;
    //  Add a ramp on the acceleration and speed limits
    // 'buildConstr:84' vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
    coder::b_linspace(ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    vel_ramp.set_size(r2.size(1));
    p_loop_ub = r2.size(1);
    for (int i25{0}; i25 < p_loop_ub; i25++) {
        vel_ramp[i25] = r2[i25];
    }
    // 'buildConstr:85' acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )',1,
    // Nc -1 );
    coder::b_linspace(ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    r3.set_size(r2.size(1));
    q_loop_ub = r2.size(1);
    for (int i26{0}; i26 < q_loop_ub; i26++) {
        r3[i26] = r2[i26];
    }
    coder::repmat(r3, y_tmp + 1, acc_ramp);
    // 'buildConstr:87' if( Nwindow > 1 )
    if (windowCurv.size(1) > 1) {
        int b_result;
        int c_input_sizes_idx_1;
        int d_input_sizes_idx_1;
        int fb_loop_ub;
        int input_sizes_idx_1;
        int s_loop_ub;
        signed char b_input_sizes_idx_1;
        bool b_empty_non_axis_sizes;
        // 'buildConstr:88' ramp = [ones(M, Nc ), vel_ramp, acc_ramp, ...
        // 'buildConstr:89'             repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)];
        s_loop_ub = acc_ramp.size(1);
        b_vel_ramp.set_size(1, acc_ramp.size(1) + 1);
        b_vel_ramp[0] = vel_ramp[vel_ramp.size(0) - 1];
        for (int i30{0}; i30 < s_loop_ub; i30++) {
            b_vel_ramp[i30 + 1] = acc_ramp[(acc_ramp.size(0) + acc_ramp.size(0) * i30) - 1];
        }
        coder::repmat(b_vel_ramp, static_cast<double>(BasisVal.size(0)),
                      static_cast<double>(windowCurv.size(1)) - 2.0, varargin_4);
        if ((BasisVal.size(0) != 0) && (y_tmp + 2 != 0)) {
            b_result = BasisVal.size(0);
        } else if (vel_ramp.size(0) != 0) {
            b_result = vel_ramp.size(0);
        } else if ((acc_ramp.size(0) != 0) && (acc_ramp.size(1) != 0)) {
            b_result = acc_ramp.size(0);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            b_result = varargin_4.size(0);
        } else {
            b_result = BasisVal.size(0);
            if (acc_ramp.size(0) > BasisVal.size(0)) {
                b_result = acc_ramp.size(0);
            }
            if (varargin_4.size(0) > b_result) {
                b_result = varargin_4.size(0);
            }
        }
        b_empty_non_axis_sizes = (b_result == 0);
        if (b_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (y_tmp + 2 != 0))) {
            input_sizes_idx_1 = y_tmp + 2;
        } else {
            input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || (vel_ramp.size(0) != 0)) {
            b_input_sizes_idx_1 = 1;
        } else {
            b_input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || ((acc_ramp.size(0) != 0) && (acc_ramp.size(1) != 0))) {
            c_input_sizes_idx_1 = acc_ramp.size(1);
        } else {
            c_input_sizes_idx_1 = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            d_input_sizes_idx_1 = varargin_4.size(1);
        } else {
            d_input_sizes_idx_1 = 0;
        }
        ramp.set_size(b_result, ((input_sizes_idx_1 + b_input_sizes_idx_1) + c_input_sizes_idx_1) +
                                    d_input_sizes_idx_1);
        for (int i44{0}; i44 < input_sizes_idx_1; i44++) {
            for (int i47{0}; i47 < b_result; i47++) {
                ramp[i47 + ramp.size(0) * i44] = 1.0;
            }
        }
        fb_loop_ub = b_input_sizes_idx_1;
        for (int i49{0}; i49 < fb_loop_ub; i49++) {
            for (int i53{0}; i53 < b_result; i53++) {
                ramp[i53 + ramp.size(0) * input_sizes_idx_1] = vel_ramp[i53];
            }
        }
        for (int i52{0}; i52 < c_input_sizes_idx_1; i52++) {
            for (int i57{0}; i57 < b_result; i57++) {
                ramp[i57 + ramp.size(0) * ((i52 + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                    acc_ramp[i57 + b_result * i52];
            }
        }
        for (int i56{0}; i56 < d_input_sizes_idx_1; i56++) {
            for (int i59{0}; i59 < b_result; i59++) {
                ramp[i59 + ramp.size(0) * (((i56 + input_sizes_idx_1) + b_input_sizes_idx_1) +
                                           c_input_sizes_idx_1)] = varargin_4[i59 + b_result * i56];
            }
        }
        // 'buildConstr:90' b  = b .* ramp(:);
        if (b.size(0) == ramp.size(0) * ramp.size(1)) {
            int lb_loop_ub;
            lb_loop_ub = b.size(0);
            for (int i63{0}; i63 < lb_loop_ub; i63++) {
                b[i63] = b[i63] * ramp[i63];
            }
        } else {
            binary_expand_op(b, ramp);
        }
    }
    // 'buildConstr:93' A = [ -ones( size( A, 2 ) );      A ];
    b_varargin_1.set_size(A.size(1), A.size(1));
    t_loop_ub = A.size(1);
    for (int i28{0}; i28 < t_loop_ub; i28++) {
        int v_loop_ub;
        v_loop_ub = A.size(1);
        for (int i32{0}; i32 < v_loop_ub; i32++) {
            b_varargin_1[i32 + b_varargin_1.size(0) * i28] = -1;
        }
    }
    if ((b_varargin_1.size(0) != 0) && (b_varargin_1.size(1) != 0)) {
        result = b_varargin_1.size(1);
    } else if ((A.size(0) != 0) && (A.size(1) != 0)) {
        result = A.size(1);
    } else {
        result = b_varargin_1.size(1);
        if (A.size(1) > b_varargin_1.size(1)) {
            result = A.size(1);
        }
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((b_varargin_1.size(0) != 0) && (b_varargin_1.size(1) != 0))) {
        input_sizes_idx_0 = b_varargin_1.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((A.size(0) != 0) && (A.size(1) != 0))) {
        b_input_sizes_idx_0 = A.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    d_varargin_1.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, result);
    for (int i35{0}; i35 < result; i35++) {
        for (int i39{0}; i39 < input_sizes_idx_0; i39++) {
            d_varargin_1[i39 + d_varargin_1.size(0) * i35] = -1.0;
        }
    }
    for (int i38{0}; i38 < result; i38++) {
        for (int i40{0}; i40 < b_input_sizes_idx_0; i40++) {
            d_varargin_1[(i40 + input_sizes_idx_0) + d_varargin_1.size(0) * i38] =
                A[i40 + b_input_sizes_idx_0 * i38];
        }
    }
    A.set_size(d_varargin_1.size(0), d_varargin_1.size(1));
    cb_loop_ub = d_varargin_1.size(1);
    for (int i42{0}; i42 < cb_loop_ub; i42++) {
        int db_loop_ub;
        db_loop_ub = d_varargin_1.size(0);
        for (int i45{0}; i45 < db_loop_ub; i45++) {
            A[i45 + A.size(0) * i42] = d_varargin_1[i45 + d_varargin_1.size(0) * i42];
        }
    }
    // 'buildConstr:94' b = [ zeros( size( A, 2 ), 1 );   b ];
    r3.set_size(b.size(0) + A.size(1));
    eb_loop_ub = A.size(1);
    for (int i48{0}; i48 < eb_loop_ub; i48++) {
        r3[i48] = 0.0;
    }
    hb_loop_ub = b.size(0);
    for (int i54{0}; i54 < hb_loop_ub; i54++) {
        r3[i54 + A.size(1)] = b[i54];
    }
    b.set_size(r3.size(0));
    jb_loop_ub = r3.size(0);
    for (int i60{0}; i60 < jb_loop_ub; i60++) {
        b[i60] = r3[i60];
    }
    //  Continuity equations
    // 'buildConstr:97' continuity = [ v2_vec( 2, : , 1 ); at_norm( 2, :, 1 ) ];
    nb_loop_ub = v2_vec.size(1);
    pb_loop_ub = at_norm.size(1);
    continuity.set_size(2, v2_vec.size(1));
    for (int i66{0}; i66 < nb_loop_ub; i66++) {
        continuity[2 * i66] = v2_vec[2 * i66 + 1];
    }
    for (int i68{0}; i68 < pb_loop_ub; i68++) {
        continuity[2 * i68 + 1] = at_norm[2 * i68 + 1];
    }
    // 'buildConstr:99' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstr.cpp
//
// [EOF]
//
