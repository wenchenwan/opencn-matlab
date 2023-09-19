//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstr.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

// Include Files
#include "buildConstr.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "colon.h"
#include "linspace.h"
#include "minOrMax.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "repmat.h"
#include "vecnorm.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void b_binary_expand_op(::coder::array<double, 3U> &in1, const ::coder::array<int, 1U> &in2,
                               const ::coder::array<double, 2U> &in3, int in4, int in5,
                               const ::coder::array<double, 2U> &in6,
                               const ::coder::array<double, 1U> &in7,
                               const ::coder::array<double, 2U> &in8);

static void binary_expand_op(::coder::array<double, 2U> &in1, const double in4[6],
                             const signed char in5_data[], const int in5_size[2],
                             const ::coder::array<double, 2U> &in6);

static void binary_expand_op(::coder::array<double, 3U> &in1, const ::coder::array<int, 1U> &in2,
                             const ::coder::array<double, 2U> &in3, int in4, int in5,
                             const ::coder::array<double, 2U> &in6,
                             const ::coder::array<double, 1U> &in7,
                             const ::coder::array<double, 2U> &in8);

static void binary_expand_op(::coder::array<double, 2U> &in1, const int in2[4],
                             const ::coder::array<int, 1U> &in3,
                             const ::coder::array<double, 3U> &in4, int in5,
                             const ::coder::array<double, 3U> &in6, const signed char in7[4]);

static void binary_expand_op(::coder::array<double, 1U> &in1,
                             const ::coder::array<double, 2U> &in2);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 3U> &in1
//                const ::coder::array<int, 1U> &in2
//                const ::coder::array<double, 2U> &in3
//                int in4
//                int in5
//                const ::coder::array<double, 2U> &in6
//                const ::coder::array<double, 1U> &in7
//                const ::coder::array<double, 2U> &in8
// Return Type  : void
//
namespace ocn {
static void b_binary_expand_op(::coder::array<double, 3U> &in1, const ::coder::array<int, 1U> &in2,
                               const ::coder::array<double, 2U> &in3, int in4, int in5,
                               const ::coder::array<double, 2U> &in6,
                               const ::coder::array<double, 1U> &in7,
                               const ::coder::array<double, 2U> &in8)
{
    int aux_1_1;
    int aux_3_1;
    int i;
    int in7_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_3_0;
    int stride_3_1;
    in7_idx_0 = in7.size(0);
    stride_0_0 = (in5 != 1);
    stride_1_0 = (in6.size(0) != 1);
    stride_1_1 = (in6.size(1) != 1);
    stride_2_0 = (in7_idx_0 != 1);
    stride_3_0 = (in8.size(0) != 1);
    stride_3_1 = (in8.size(1) != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    if (in8.size(1) == 1) {
        i = 1;
    } else {
        i = in8.size(1);
    }
    if (i == 1) {
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
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        int i2;
        if (in8.size(0) == 1) {
            i2 = in7_idx_0;
        } else {
            i2 = in8.size(0);
        }
        if (i2 == 1) {
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
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            in1[(in2[i3] + in1.size(0) * i1) - 1] =
                in3[in4 + in3.size(0) * (i3 * stride_0_0)] *
                    in6[i3 * stride_1_0 + in6.size(0) * aux_1_1] +
                in7[i3 * stride_2_0] * in8[i3 * stride_3_0 + in8.size(0) * aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const double in4[6]
//                const signed char in5_data[]
//                const int in5_size[2]
//                const ::coder::array<double, 2U> &in6
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, const double in4[6],
                             const signed char in5_data[], const int in5_size[2],
                             const ::coder::array<double, 2U> &in6)
{
    ::coder::array<double, 2U> b_in4;
    int b_loop_ub;
    int i;
    int in5_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    in5_idx_0 = in5_size[1];
    if (in6.size(0) == 1) {
        i = in5_idx_0;
    } else {
        i = in6.size(0);
    }
    b_in4.set_size(i, in6.size(1));
    stride_0_0 = (in5_idx_0 != 1);
    stride_1_0 = (in6.size(0) != 1);
    loop_ub = in6.size(1);
    for (int i1{0}; i1 < loop_ub; i1++) {
        int c_loop_ub;
        if (in6.size(0) == 1) {
            c_loop_ub = in5_idx_0;
        } else {
            c_loop_ub = in6.size(0);
        }
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_in4[i3 + b_in4.size(0) * i1] =
                in4[in5_data[i3 * stride_0_0] - 1] / in6[i3 * stride_1_0 + in6.size(0) * i1];
        }
    }
    b_loop_ub = b_in4.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = b_in4.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            double varargin_1;
            varargin_1 = b_in4[i4 + b_in4.size(0) * i2];
            in1[i4 + in1.size(0) * i2] = std::pow(varargin_1, 2.0);
        }
    }
}

//
// Arguments    : ::coder::array<double, 3U> &in1
//                const ::coder::array<int, 1U> &in2
//                const ::coder::array<double, 2U> &in3
//                int in4
//                int in5
//                const ::coder::array<double, 2U> &in6
//                const ::coder::array<double, 1U> &in7
//                const ::coder::array<double, 2U> &in8
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 3U> &in1, const ::coder::array<int, 1U> &in2,
                             const ::coder::array<double, 2U> &in3, int in4, int in5,
                             const ::coder::array<double, 2U> &in6,
                             const ::coder::array<double, 1U> &in7,
                             const ::coder::array<double, 2U> &in8)
{
    int aux_1_1;
    int aux_3_1;
    int i;
    int in7_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_3_0;
    int stride_3_1;
    in7_idx_0 = in7.size(0);
    stride_0_0 = (in5 != 1);
    stride_1_0 = (in6.size(0) != 1);
    stride_1_1 = (in6.size(1) != 1);
    stride_2_0 = (in7_idx_0 != 1);
    stride_3_0 = (in8.size(0) != 1);
    stride_3_1 = (in8.size(1) != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    if (in8.size(1) == 1) {
        i = 1;
    } else {
        i = in8.size(1);
    }
    if (i == 1) {
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
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        int i2;
        if (in8.size(0) == 1) {
            i2 = in7_idx_0;
        } else {
            i2 = in8.size(0);
        }
        if (i2 == 1) {
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
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            in1[((in2[i3] + in1.size(0) * i1) + in1.size(0) * in1.size(1)) - 1] =
                in3[in4 + in3.size(0) * (i3 * stride_0_0)] *
                    in6[i3 * stride_1_0 + in6.size(0) * aux_1_1] +
                in7[i3 * stride_2_0] * in8[i3 * stride_3_0 + in8.size(0) * aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const int in2[4]
//                const ::coder::array<int, 1U> &in3
//                const ::coder::array<double, 3U> &in4
//                int in5
//                const ::coder::array<double, 3U> &in6
//                const signed char in7[4]
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, const int in2[4],
                             const ::coder::array<int, 1U> &in3,
                             const ::coder::array<double, 3U> &in4, int in5,
                             const ::coder::array<double, 3U> &in6, const signed char in7[4])
{
    ::coder::array<double, 2U> b_in1;
    ::coder::array<double, 2U> b_in4;
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
    loop_ub = in4.size(1);
    b_loop_ub = in6.size(1);
    c_loop_ub = in4.size(1);
    d_loop_ub = in6.size(1);
    b_in4.set_size(4, loop_ub);
    for (int i{0}; i < loop_ub; i++) {
        b_in4[4 * i] = in4[2 * i + 2 * in4.size(1) * in5];
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b_in4[4 * i1 + 1] = in6[2 * i1 + 2 * in6.size(1) * in5];
    }
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        b_in4[4 * i2 + 2] = in4[(2 * i2 + 2 * in4.size(1) * in5) + 1];
    }
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        b_in4[4 * i3 + 3] = in6[(2 * i3 + 2 * in6.size(1) * in5) + 1];
    }
    if (b_in4.size(1) == 1) {
        i4 = in3.size(0);
    } else {
        i4 = b_in4.size(1);
    }
    b_in1.set_size(4, i4);
    stride_0_1 = (in3.size(0) != 1);
    stride_1_1 = (b_in4.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (b_in4.size(1) == 1) {
        e_loop_ub = in3.size(0);
    } else {
        e_loop_ub = b_in4.size(1);
    }
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        b_in1[4 * i5] = in1[(in2[0] + in1.size(0) * (in3[aux_0_1] - 1)) - 1] +
                        b_in4[4 * aux_1_1] * static_cast<double>(in7[0]);
        b_in1[4 * i5 + 1] = in1[(in2[1] + in1.size(0) * (in3[aux_0_1] - 1)) - 1] +
                            b_in4[4 * aux_1_1 + 1] * static_cast<double>(in7[1]);
        b_in1[4 * i5 + 2] = in1[(in2[2] + in1.size(0) * (in3[aux_0_1] - 1)) - 1] +
                            b_in4[4 * aux_1_1 + 2] * static_cast<double>(in7[2]);
        b_in1[4 * i5 + 3] = in1[(in2[3] + in1.size(0) * (in3[aux_0_1] - 1)) - 1] +
                            b_in4[4 * aux_1_1 + 3] * static_cast<double>(in7[3]);
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    f_loop_ub = b_in1.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        in1[(in2[0] + in1.size(0) * (in3[i6] - 1)) - 1] = b_in1[4 * i6];
        in1[(in2[1] + in1.size(0) * (in3[i6] - 1)) - 1] = b_in1[4 * i6 + 1];
        in1[(in2[2] + in1.size(0) * (in3[i6] - 1)) - 1] = b_in1[4 * i6 + 2];
        in1[(in2[3] + in1.size(0) * (in3[i6] - 1)) - 1] = b_in1[4 * i6 + 3];
    }
}

//
// Arguments    : ::coder::array<double, 1U> &in1
//                const ::coder::array<double, 2U> &in2
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 1U> &in1, const ::coder::array<double, 2U> &in2)
{
    ::coder::array<double, 1U> b_in1;
    int b_in2;
    int b_loop_ub;
    int c_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_in2 = in2.size(0) * in2.size(1);
    if (b_in2 == 1) {
        c_in2 = in1.size(0);
    } else {
        c_in2 = b_in2;
    }
    b_in1.set_size(c_in2);
    stride_0_0 = (in1.size(0) != 1);
    stride_1_0 = (b_in2 != 1);
    if (b_in2 == 1) {
        loop_ub = in1.size(0);
    } else {
        loop_ub = b_in2;
    }
    for (int i{0}; i < loop_ub; i++) {
        b_in1[i] = in1[i * stride_0_0] * in2[i * stride_1_0];
    }
    in1.set_size(b_in1.size(0));
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        in1[i1] = b_in1[i1];
    }
}

//
// function [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, windowCurv, amax, ...
//     v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec )
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
//                const double ctx_cfg_vmax[6]
//                double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS
//                double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS
//                Kinematics *ctx_kin
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
void buildConstr(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                 const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                 const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                 const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                 const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                 int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                 double ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, double ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS,
                 Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
                 const double amax[6], double v_0, double at_0, double v_1, double at_1,
                 const ::coder::array<double, 2U> &BasisVal,
                 const ::coder::array<double, 2U> &BasisValD,
                 const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &A,
                 ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq,
                 ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &continuity)
{
    static const signed char mask_continuity[4]{1, 1, -1, -1};
    ::coder::array<double, 3U> Acc;
    ::coder::array<double, 3U> at_norm;
    ::coder::array<double, 3U> t_vec;
    ::coder::array<double, 3U> v2_vec;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> acc_ramp;
    ::coder::array<double, 2U> b_Acc;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_amax_data;
    ::coder::array<double, 2U> b_b;
    ::coder::array<double, 2U> b_ctx_cfg_vmax;
    ::coder::array<double, 2U> b_r1D_r;
    ::coder::array<double, 2U> b_v2_vec;
    ::coder::array<double, 2U> b_vel_ramp;
    ::coder::array<double, 2U> f_max;
    ::coder::array<double, 2U> normR1D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r0D;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1D_a;
    ::coder::array<double, 2U> r1D_r;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r2D_a;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> ramp;
    ::coder::array<double, 2U> v_max;
    ::coder::array<double, 2U> varargin_2;
    ::coder::array<double, 2U> varargin_4;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> b_t_vec;
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> vel_ramp;
    ::coder::array<unsigned int, 2U> e_y;
    ::coder::array<int, 2U> indAC_tmp;
    ::coder::array<int, 2U> indAL;
    ::coder::array<int, 2U> indAT;
    ::coder::array<int, 2U> r1;
    ::coder::array<int, 1U> r4;
    ::coder::array<int, 1U> r5;
    double amax_data[6];
    double Nec;
    double Nx;
    int iv[2];
    int iv1[2];
    int tmp_size[2];
    int M;
    int N;
    int b_loop_ub;
    int b_unnamed_idx_1;
    int b_y;
    int c_loop_ub;
    int c_y;
    int cb_loop_ub;
    int db_loop_ub;
    int e_loop_ub;
    int end;
    int end_tmp;
    int f_loop_ub;
    int fc_loop_ub;
    int h_loop_ub;
    int i22;
    int i56;
    int i57;
    int i_loop_ub;
    int input_sizes_idx_0;
    int j_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int ob_loop_ub;
    int p_loop_ub;
    int partialTrueCount;
    int pb_loop_ub;
    int q_loop_ub;
    int qb_loop_ub;
    int r_loop_ub;
    int rb_loop_ub;
    int sb_loop_ub;
    int tmp_data_idx_1;
    int trueCount;
    int v_loop_ub;
    int varargin_1;
    int y;
    int y_tmp;
    signed char b_tmp_data[6];
    signed char tmp_data[6];
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
    // 'buildConstr:31' amaxTot     = amax( ctx.cfg.maskTot );
    // 'buildConstr:32' b_amax      = repmat( amaxTot, M, 1 );
    end_tmp = ctx_cfg_maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end_tmp; b_i++) {
        if (ctx_cfg_maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    for (int i8{0}; i8 < trueCount; i8++) {
        amax_data[i8] = amax[tmp_data[i8] - 1];
    }
    b_amax_data.set(&amax_data[0], 1, trueCount);
    varargin_1 = BasisVal.size(0);
    r.set_size(varargin_1, b_amax_data.size(1));
    if ((varargin_1 != 0) && (b_amax_data.size(1) != 0)) {
        int i9;
        int na;
        na = b_amax_data.size(1);
        i9 = varargin_1 - 1;
        for (int k{0}; k < na; k++) {
            for (int t{0}; t <= i9; t++) {
                r[t + r.size(0) * k] = b_amax_data[k];
            }
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
    c_loop_ub = windowCurv.size(1);
    for (int i10{0}; i10 < c_loop_ub; i10++) {
        int d_loop_ub;
        d_loop_ub = BasisVal.size(1);
        for (int i11{0}; i11 < d_loop_ub; i11++) {
            at_norm[2 * i11 + 2 * at_norm.size(1) * i10] = 0.0;
            at_norm[(2 * i11 + 2 * at_norm.size(1) * i10) + 1] = 0.0;
        }
    }
    // 'buildConstr:42' t_vec       = zeros( Ndim, 2, Nwindow );
    t_vec.set_size(ctx_cfg_NumberAxis, 2, windowCurv.size(1));
    e_loop_ub = windowCurv.size(1);
    for (int i12{0}; i12 < e_loop_ub; i12++) {
        for (int i13{0}; i13 < 2; i13++) {
            for (int i14{0}; i14 < ctx_cfg_NumberAxis; i14++) {
                t_vec[(i14 + t_vec.size(0) * i13) + t_vec.size(0) * 2 * i12] = 0.0;
            }
        }
    }
    // 'buildConstr:43' v2_vec      = zeros( 2, N, Nwindow );
    v2_vec.set_size(2, BasisVal.size(1), windowCurv.size(1));
    f_loop_ub = windowCurv.size(1);
    for (int i15{0}; i15 < f_loop_ub; i15++) {
        int g_loop_ub;
        g_loop_ub = BasisVal.size(1);
        for (int i16{0}; i16 < g_loop_ub; i16++) {
            v2_vec[2 * i16 + 2 * v2_vec.size(1) * i15] = 0.0;
            v2_vec[(2 * i16 + 2 * v2_vec.size(1) * i15) + 1] = 0.0;
        }
    }
    // 'buildConstr:44' Acc         = zeros( M * Ndim , N, 2 );
    c_y = static_cast<int>(static_cast<double>(BasisVal.size(0)) *
                           static_cast<double>(ctx_cfg_NumberAxis));
    Acc.set_size(c_y, BasisVal.size(1), 2);
    h_loop_ub = BasisVal.size(1);
    for (int i17{0}; i17 < 2; i17++) {
        for (int i18{0}; i18 < h_loop_ub; i18++) {
            for (int i19{0}; i19 < c_y; i19++) {
                Acc[(i19 + Acc.size(0) * i18) + Acc.size(0) * Acc.size(1) * i17] = 0.0;
            }
        }
    }
    // 'buildConstr:45' indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );
    coder::eml_integer_colon_dispatcher(ctx_cfg_NumberAxis, r1);
    tmp_data_idx_1 = BasisVal.size(0);
    indAT.set_size(2, r1.size(1));
    i_loop_ub = r1.size(1);
    for (int i20{0}; i20 < i_loop_ub; i20++) {
        int indAT_tmp;
        indAT_tmp = r1[i20] - 1;
        indAT[2 * i20] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                          static_cast<double>(BasisVal.size(0))) +
                         1;
        indAT[2 * i20 + 1] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                              static_cast<double>(BasisVal.size(0))) +
                             tmp_data_idx_1;
    }
    // 'buildConstr:46' mask_continuity = [ 1; 1; -1; -1 ];
    // 'buildConstr:47' v_max       = zeros( Ndim + 1, M );
    v_max.set_size(ctx_cfg_NumberAxis + 1, BasisVal.size(0));
    j_loop_ub = BasisVal.size(0);
    for (int i21{0}; i21 < j_loop_ub; i21++) {
        int k_loop_ub;
        k_loop_ub = ctx_cfg_NumberAxis + 1;
        for (int i23{0}; i23 < k_loop_ub; i23++) {
            v_max[i23 + v_max.size(0) * i21] = 0.0;
        }
    }
    // 'buildConstr:49' for k = 1 : Nwindow
    i22 = windowCurv.size(1);
    if (windowCurv.size(1) - 1 >= 0) {
        int unnamed_idx_1;
        end = ctx_cfg_maskTot_size[1] - 1;
        coder::eml_integer_colon_dispatcher(static_cast<int>(static_cast<double>(y_tmp + 2) *
                                                             static_cast<double>(BasisVal.size(0))),
                                            r1);
        l_loop_ub = r1.size(1);
        unnamed_idx_1 = r.size(0) * r.size(1);
        m_loop_ub = unnamed_idx_1;
        n_loop_ub = indAT.size(1);
        p_loop_ub = indAT.size(1);
    }
    if (i22 - 1 >= 0) {
        tmp_size[0] = 1;
        o_loop_ub = BasisVal.size(1);
        b_unnamed_idx_1 = r.size(0) * r.size(1);
        q_loop_ub = BasisVal.size(1);
    }
    for (int b_k{0}; b_k < i22; b_k++) {
        double d_y[2];
        double c_k;
        double z1_idx_0;
        double z1_idx_1;
        int indAEL[4];
        int ab_loop_ub;
        int b_inner;
        int b_input_sizes_idx_0;
        int b_nc;
        int b_partialTrueCount;
        int b_result;
        int b_trueCount;
        int b_v_max;
        int bc_loop_ub;
        int c_unnamed_idx_1;
        int d_k;
        int d_unnamed_idx_1;
        int dc_loop_ub;
        int eb_loop_ub;
        int ec_loop_ub;
        int f_y;
        int gb_loop_ub;
        int gc_loop_ub;
        int hc_loop_ub;
        int ic_loop_ub;
        int inner;
        int jc_loop_ub;
        int kc_loop_ub;
        int lb_loop_ub;
        int lc_loop_ub;
        int mc_loop_ub;
        int nc;
        int nc_loop_ub;
        int oc_loop_ub;
        int pc_loop_ub;
        int qc_loop_ub;
        int ub_loop_ub;
        int vb_loop_ub;
        int xb_loop_ub;
        int yb_loop_ub;
        bool b_empty_non_axis_sizes;
        bool guard1;
        //  Compute the partial derivatives
        // 'buildConstr:51' [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, &windowCurv[b_k], u_vec, r0D, r1D, r2D, r3D);
        // 'buildConstr:52' ctx.kin = ctx.kin.set_tool_length(windowCurv( k ).tool.offset.z);
        ctx_kin->set_tool_length(windowCurv[b_k].tool.offset.z);
        // 'buildConstr:54' if( windowCurv( k ).Info.TRAFO )
        if (windowCurv[b_k].Info.TRAFO) {
            int s_loop_ub;
            // 'buildConstr:55' [ ~, r1D_a, r2D_a ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
            ctx_kin->joint(r0D, r1D, r2D, a__1, r1D_a, r2D_a);
            // 'buildConstr:56' r1D_r    = r1D;
            r1D_r.set_size(r1D.size(0), r1D.size(1));
            s_loop_ub = r1D.size(1);
            for (int i25{0}; i25 < s_loop_ub; i25++) {
                int u_loop_ub;
                u_loop_ub = r1D.size(0);
                for (int i27{0}; i27 < u_loop_ub; i27++) {
                    r1D_r[i27 + r1D_r.size(0) * i25] = r1D[i27 + r1D.size(0) * i25];
                }
            }
        } else {
            int t_loop_ub;
            int x_loop_ub;
            // 'buildConstr:57' else
            // 'buildConstr:58' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            ctx_kin->v_relative(r0D, r1D, r1D_r);
            // 'buildConstr:59' r1D_a    = r1D;
            r1D_a.set_size(r1D.size(0), r1D.size(1));
            t_loop_ub = r1D.size(1);
            for (int i26{0}; i26 < t_loop_ub; i26++) {
                int w_loop_ub;
                w_loop_ub = r1D.size(0);
                for (int i29{0}; i29 < w_loop_ub; i29++) {
                    r1D_a[i29 + r1D_a.size(0) * i26] = r1D[i29 + r1D.size(0) * i26];
                }
            }
            // 'buildConstr:60' r2D_a    = r2D;
            x_loop_ub = r2D.size(1);
            r2D_a.set_size(r2D.size(0), r2D.size(1));
            for (int i30{0}; i30 < x_loop_ub; i30++) {
                int y_loop_ub;
                y_loop_ub = r2D.size(0);
                for (int i31{0}; i31 < y_loop_ub; i31++) {
                    r2D_a[i31 + r2D_a.size(0) * i30] = r2D[i31 + r2D.size(0) * i30];
                }
            }
        }
        //  Tangent unit vector at start and at end
        // 'buildConstr:64' normR1D = vecnorm( r1D );
        coder::vecnorm(r1D, normR1D);
        // 'buildConstr:65' t_vec( : , :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );
        iv[0] = 0;
        iv[1] = r1D.size(1) - 1;
        ab_loop_ub = r1D.size(0);
        x.set_size(r1D.size(0), 2);
        iv1[0] = 0;
        iv1[1] = normR1D.size(1) - 1;
        for (int i33{0}; i33 < 2; i33++) {
            for (int i35{0}; i35 < ab_loop_ub; i35++) {
                x[i35 + x.size(0) * i33] = r1D[i35 + r1D.size(0) * iv[i33]];
            }
            d_y[i33] = normR1D[iv1[i33]];
        }
        eb_loop_ub = x.size(0);
        for (int i37{0}; i37 < 2; i37++) {
            for (int i38{0}; i38 < eb_loop_ub; i38++) {
                t_vec[(i38 + t_vec.size(0) * i37) + t_vec.size(0) * 2 * b_k] =
                    x[i38 + x.size(0) * i37] / d_y[i37];
            }
        }
        // 'buildConstr:67' v_max( 1 : Ndim, : ) = ( ctx.cfg.vmax( ctx.cfg.maskTot ).'./ r1D_a ).^2;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int c_i{0}; c_i <= end; c_i++) {
            if (ctx_cfg_maskTot_data[c_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                b_partialTrueCount++;
            }
        }
        tmp_size[1] = b_trueCount;
        if (r1D_a.size(0) == b_trueCount) {
            int fb_loop_ub;
            int hb_loop_ub;
            b_ctx_cfg_vmax.set_size(b_trueCount, r1D_a.size(1));
            fb_loop_ub = r1D_a.size(1);
            for (int i39{0}; i39 < fb_loop_ub; i39++) {
                for (int i40{0}; i40 < b_trueCount; i40++) {
                    b_ctx_cfg_vmax[i40 + b_ctx_cfg_vmax.size(0) * i39] =
                        ctx_cfg_vmax[b_tmp_data[i40] - 1] / r1D_a[i40 + r1D_a.size(0) * i39];
                }
            }
            hb_loop_ub = b_ctx_cfg_vmax.size(1);
            for (int i41{0}; i41 < hb_loop_ub; i41++) {
                int ib_loop_ub;
                ib_loop_ub = b_ctx_cfg_vmax.size(0);
                for (int i44{0}; i44 < ib_loop_ub; i44++) {
                    double b_varargin_1;
                    b_varargin_1 = b_ctx_cfg_vmax[i44 + b_ctx_cfg_vmax.size(0) * i41];
                    v_max[i44 + v_max.size(0) * i41] = std::pow(b_varargin_1, 2.0);
                }
            }
        } else {
            binary_expand_op(v_max, ctx_cfg_vmax, b_tmp_data, tmp_size, r1D_a);
        }
        //  Maximum constraint on the speed
        // 'buildConstr:70' v_max( end, : ) = ( windowCurv( k ).Info.FeedRate ./ ...
        // 'buildConstr:71'         vecnorm( r1D_r( ctx.cfg.indCart, : ) ) ).^2;
        gb_loop_ub = r1D_r.size(1);
        b_r1D_r.set_size(ctx_cfg_indCart.size(0), r1D_r.size(1));
        for (int i42{0}; i42 < gb_loop_ub; i42++) {
            int jb_loop_ub;
            jb_loop_ub = ctx_cfg_indCart.size(0);
            for (int i46{0}; i46 < jb_loop_ub; i46++) {
                b_r1D_r[i46 + b_r1D_r.size(0) * i42] =
                    r1D_r[(ctx_cfg_indCart[i46] + r1D_r.size(0) * i42) - 1];
            }
        }
        coder::vecnorm(b_r1D_r, r2);
        b_v_max = v_max.size(0) - 1;
        lb_loop_ub = r2.size(1);
        for (int i48{0}; i48 < lb_loop_ub; i48++) {
            double c_varargin_1;
            c_varargin_1 = windowCurv[b_k].Info.FeedRate / r2[i48];
            v_max[b_v_max + v_max.size(0) * i48] = std::pow(c_varargin_1, 2.0);
        }
        // 'buildConstr:73' f_max = min( v_max, [], 1 );
        coder::internal::minimum(v_max, f_max);
        // 'buildConstr:75' for j = 1 : Ndim
        if (ctx_cfg_NumberAxis - 1 >= 0) {
            if (M < 1) {
                e_y.set_size(1, 0);
            } else {
                int nb_loop_ub;
                e_y.set_size(1, M);
                nb_loop_ub = M - 1;
                for (int i55{0}; i55 <= nb_loop_ub; i55++) {
                    e_y[i55] = i55 + 1U;
                }
            }
            i56 = r1D_a.size(1);
            ob_loop_ub = r1D_a.size(1);
            pb_loop_ub = e_y.size(1);
            i57 = r1D.size(1);
            qb_loop_ub = r1D.size(1);
            rb_loop_ub = BasisVal.size(1);
            sb_loop_ub = BasisVal.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int g_y;
            int i62;
            int i64;
            int i70;
            int i72;
            //  Compute the acceleration matrix
            // 'buildConstr:76' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            g_y = static_cast<int>((static_cast<double>(j + 1) - 1.0) * static_cast<double>(M));
            // 'buildConstr:77' Acc( ind, :, 1 ) = r2D_a( j, : )' .* BasisVal + 0.5 * r1D_a( j, : )'
            // .* BasisValD;
            r3.set_size(i56);
            for (int i59{0}; i59 < ob_loop_ub; i59++) {
                r3[i59] = 0.5 * r1D_a[j + r1D_a.size(0) * i59];
            }
            r4.set_size(e_y.size(1));
            for (int i60{0}; i60 < pb_loop_ub; i60++) {
                r4[i60] = static_cast<int>(e_y[i60]) + g_y;
            }
            if (r2D_a.size(1) == 1) {
                i62 = BasisVal.size(0);
            } else {
                i62 = r2D_a.size(1);
            }
            if (r3.size(0) == 1) {
                i64 = BasisValD.size(0);
            } else {
                i64 = r3.size(0);
            }
            if ((BasisVal.size(0) == r2D_a.size(1)) && (r3.size(0) == BasisValD.size(0)) &&
                (i62 == i64) && (BasisVal.size(1) == BasisValD.size(1))) {
                for (int i65{0}; i65 < rb_loop_ub; i65++) {
                    int wb_loop_ub;
                    wb_loop_ub = r2D_a.size(1);
                    for (int i67{0}; i67 < wb_loop_ub; i67++) {
                        Acc[(r4[i67] + Acc.size(0) * i65) - 1] =
                            r2D_a[j + r2D_a.size(0) * i67] *
                                BasisVal[i67 + BasisVal.size(0) * i65] +
                            r3[i67] * BasisValD[i67 + BasisValD.size(0) * i65];
                    }
                }
            } else {
                b_binary_expand_op(Acc, r4, r2D_a, j, r2D_a.size(1), BasisVal, r3, BasisValD);
            }
            // 'buildConstr:78' Acc( ind, :, 2 ) = r2D( j, : )'   .* BasisVal + 0.5 * r1D( j, : )'
            // .* BasisValD;
            r3.set_size(i57);
            for (int i68{0}; i68 < qb_loop_ub; i68++) {
                r3[i68] = 0.5 * r1D[j + r1D.size(0) * i68];
            }
            if (r2D.size(1) == 1) {
                i70 = BasisVal.size(0);
            } else {
                i70 = r2D.size(1);
            }
            if (r3.size(0) == 1) {
                i72 = BasisValD.size(0);
            } else {
                i72 = r3.size(0);
            }
            if ((BasisVal.size(0) == r2D.size(1)) && (r3.size(0) == BasisValD.size(0)) &&
                (i70 == i72) && (BasisVal.size(1) == BasisValD.size(1))) {
                for (int i75{0}; i75 < sb_loop_ub; i75++) {
                    int cc_loop_ub;
                    cc_loop_ub = r2D.size(1);
                    for (int i77{0}; i77 < cc_loop_ub; i77++) {
                        Acc[((r4[i77] + Acc.size(0) * i75) + Acc.size(0) * Acc.size(1)) - 1] =
                            r2D[j + r2D.size(0) * i77] * BasisVal[i77 + BasisVal.size(0) * i75] +
                            r3[i77] * BasisValD[i77 + BasisValD.size(0) * i75];
                    }
                }
            } else {
                binary_expand_op(Acc, r4, r2D, j, r2D.size(1), BasisVal, r3, BasisValD);
            }
        }
        //  Inequality constraints
        // 'buildConstr:82' indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
        f_y = static_cast<int>(
            static_cast<double>(static_cast<int>(((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 static_cast<double>(y_tmp + 2))) *
            static_cast<double>(M));
        indAL.set_size(1, r1.size(1));
        for (int i58{0}; i58 < l_loop_ub; i58++) {
            indAL[i58] = r1[i58] + f_y;
        }
        // 'buildConstr:83' indAC   = int32( 1 : N  ) + ( k - 1 ) * N;
        if (N < 1) {
            e_y.set_size(1, 0);
        } else {
            int tb_loop_ub;
            e_y.set_size(1, N);
            tb_loop_ub = N - 1;
            for (int i61{0}; i61 <= tb_loop_ub; i61++) {
                e_y[i61] = i61 + 1U;
            }
        }
        c_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        indAC_tmp.set_size(1, e_y.size(1));
        ub_loop_ub = e_y.size(1);
        for (int i63{0}; i63 < ub_loop_ub; i63++) {
            indAC_tmp[i63] = static_cast<int>(static_cast<double>(e_y[i63]) + c_k);
        }
        // 'buildConstr:84' A( indAL, indAC )   = [ BasisVal; -BasisVal ; Acc( :, :, 1) ; -Acc( :,
        // :, 1) ];
        r4.set_size(indAL.size(1));
        vb_loop_ub = indAL.size(1);
        for (int i66{0}; i66 < vb_loop_ub; i66++) {
            r4[i66] = indAL[i66] - 1;
        }
        r5.set_size(indAC_tmp.size(1));
        xb_loop_ub = indAC_tmp.size(1);
        for (int i69{0}; i69 < xb_loop_ub; i69++) {
            r5[i69] = indAC_tmp[i69] - 1;
        }
        varargin_2.set_size(BasisVal.size(0), BasisVal.size(1));
        for (int i71{0}; i71 < o_loop_ub; i71++) {
            int ac_loop_ub;
            ac_loop_ub = BasisVal.size(0);
            for (int i73{0}; i73 < ac_loop_ub; i73++) {
                varargin_2[i73 + varargin_2.size(0) * i71] =
                    -BasisVal[i73 + BasisVal.size(0) * i71];
            }
        }
        yb_loop_ub = Acc.size(0);
        bc_loop_ub = Acc.size(1);
        varargin_4.set_size(Acc.size(0), Acc.size(1));
        for (int i74{0}; i74 < bc_loop_ub; i74++) {
            for (int i76{0}; i76 < yb_loop_ub; i76++) {
                varargin_4[i76 + varargin_4.size(0) * i74] = -Acc[i76 + Acc.size(0) * i74];
            }
        }
        if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
            b_result = BasisVal.size(1);
        } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
            b_result = varargin_2.size(1);
        } else if ((Acc.size(0) != 0) && (Acc.size(1) != 0)) {
            b_result = Acc.size(1);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            b_result = varargin_4.size(1);
        } else {
            b_result = BasisVal.size(1);
            if (varargin_2.size(1) > BasisVal.size(1)) {
                b_result = varargin_2.size(1);
            }
            if (Acc.size(1) > b_result) {
                b_result = Acc.size(1);
            }
            if (varargin_4.size(1) > b_result) {
                b_result = varargin_4.size(1);
            }
        }
        b_empty_non_axis_sizes = (b_result == 0);
        if (b_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            dc_loop_ub = BasisVal.size(0);
        } else {
            dc_loop_ub = 0;
        }
        if (b_empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            ec_loop_ub = varargin_2.size(0);
        } else {
            ec_loop_ub = 0;
        }
        guard1 = false;
        if (b_empty_non_axis_sizes) {
            guard1 = true;
        } else {
            fc_loop_ub = Acc.size(0);
            if ((Acc.size(0) != 0) && (Acc.size(1) != 0)) {
                guard1 = true;
            } else {
                input_sizes_idx_0 = 0;
            }
        }
        if (guard1) {
            fc_loop_ub = Acc.size(0);
            input_sizes_idx_0 = Acc.size(0);
        }
        if (b_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            b_input_sizes_idx_0 = varargin_4.size(0);
        } else {
            b_input_sizes_idx_0 = 0;
        }
        gc_loop_ub = Acc.size(1);
        b_Acc.set_size(fc_loop_ub, Acc.size(1));
        for (int i78{0}; i78 < gc_loop_ub; i78++) {
            for (int i80{0}; i80 < fc_loop_ub; i80++) {
                b_Acc[i80 + b_Acc.size(0) * i78] = Acc[i80 + Acc.size(0) * i78];
            }
        }
        for (int i79{0}; i79 < b_result; i79++) {
            for (int i82{0}; i82 < dc_loop_ub; i82++) {
                A[r4[i82] + A.size(0) * r5[i79]] = BasisVal[i82 + dc_loop_ub * i79];
            }
        }
        for (int i81{0}; i81 < b_result; i81++) {
            for (int i84{0}; i84 < ec_loop_ub; i84++) {
                A[r4[i84 + dc_loop_ub] + A.size(0) * r5[i81]] = varargin_2[i84 + ec_loop_ub * i81];
            }
        }
        for (int i83{0}; i83 < b_result; i83++) {
            for (int i86{0}; i86 < input_sizes_idx_0; i86++) {
                A[r4[(i86 + dc_loop_ub) + ec_loop_ub] + A.size(0) * r5[i83]] =
                    b_Acc[i86 + input_sizes_idx_0 * i83];
            }
        }
        for (int i85{0}; i85 < b_result; i85++) {
            for (int i87{0}; i87 < b_input_sizes_idx_0; i87++) {
                A[r4[((i87 + dc_loop_ub) + ec_loop_ub) + input_sizes_idx_0] + A.size(0) * r5[i85]] =
                    varargin_4[i87 + b_input_sizes_idx_0 * i85];
            }
        }
        // 'buildConstr:85' b( indAL )          = [ f_max'; zeros( size(f_max) )';
        // 'buildConstr:86'                             b_amax( : ); b_amax( : ) ];
        c_unnamed_idx_1 = f_max.size(1);
        d_unnamed_idx_1 = f_max.size(1);
        hc_loop_ub = f_max.size(1);
        for (int i88{0}; i88 < hc_loop_ub; i88++) {
            b[indAL[i88] - 1] = f_max[i88];
        }
        ic_loop_ub = f_max.size(1);
        for (int i89{0}; i89 < ic_loop_ub; i89++) {
            b[indAL[i89 + c_unnamed_idx_1] - 1] = 0.0;
        }
        for (int i90{0}; i90 < b_unnamed_idx_1; i90++) {
            b[indAL[(i90 + c_unnamed_idx_1) + d_unnamed_idx_1] - 1] = r[i90];
        }
        for (int i91{0}; i91 < m_loop_ub; i91++) {
            b[indAL[((i91 + c_unnamed_idx_1) + d_unnamed_idx_1) + b_unnamed_idx_1] - 1] = r[i91];
        }
        //  Continuity equations
        // 'buildConstr:89' indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2 ;
        d_k = (b_k << 1) + 1;
        indAEL[0] = d_k;
        indAEL[1] = d_k + 1;
        indAEL[2] = d_k + 2;
        indAEL[3] = d_k + 3;
        //  Line   index
        // 'buildConstr:90' indAEC  = int32( 1 : N ) + ( k - 1 ) * N ;
        //  Column index
        // 'buildConstr:91' at_norm( 1, :, k )   = t_vec( : , 1, k )' * Acc( indAT( 1, : ) , :, 2 );
        jc_loop_ub = Acc.size(1);
        b_b.set_size(n_loop_ub, Acc.size(1));
        for (int i92{0}; i92 < jc_loop_ub; i92++) {
            for (int i93{0}; i93 < n_loop_ub; i93++) {
                b_b[i93 + b_b.size(0) * i92] =
                    Acc[((indAT[2 * i93] + Acc.size(0) * i92) + Acc.size(0) * Acc.size(1)) - 1];
            }
        }
        kc_loop_ub = t_vec.size(0);
        b_t_vec.set_size(t_vec.size(0));
        for (int i94{0}; i94 < kc_loop_ub; i94++) {
            b_t_vec[i94] = t_vec[i94 + t_vec.size(0) * 2 * b_k];
        }
        inner = b_t_vec.size(0);
        nc = b_b.size(1);
        r2.set_size(1, b_b.size(1));
        for (int b_j{0}; b_j < nc; b_j++) {
            r2[b_j] = 0.0;
            for (int e_k{0}; e_k < inner; e_k++) {
                r2[b_j] = r2[b_j] + b_t_vec[e_k] * b_b[e_k + b_b.size(0) * b_j];
            }
        }
        lc_loop_ub = r2.size(1);
        for (int i95{0}; i95 < lc_loop_ub; i95++) {
            at_norm[2 * i95 + 2 * at_norm.size(1) * b_k] = r2[i95];
        }
        // 'buildConstr:92' at_norm( 2, :, k )   = t_vec( : , 2, k )' * Acc( indAT( 2, : ) , :, 2 );
        mc_loop_ub = Acc.size(1);
        b_b.set_size(p_loop_ub, Acc.size(1));
        for (int i96{0}; i96 < mc_loop_ub; i96++) {
            for (int i97{0}; i97 < p_loop_ub; i97++) {
                b_b[i97 + b_b.size(0) * i96] =
                    Acc[((indAT[2 * i97 + 1] + Acc.size(0) * i96) + Acc.size(0) * Acc.size(1)) - 1];
            }
        }
        nc_loop_ub = t_vec.size(0);
        b_t_vec.set_size(t_vec.size(0));
        for (int i98{0}; i98 < nc_loop_ub; i98++) {
            b_t_vec[i98] = t_vec[(i98 + t_vec.size(0)) + t_vec.size(0) * 2 * b_k];
        }
        b_inner = b_t_vec.size(0);
        b_nc = b_b.size(1);
        r2.set_size(1, b_b.size(1));
        for (int c_j{0}; c_j < b_nc; c_j++) {
            r2[c_j] = 0.0;
            for (int f_k{0}; f_k < b_inner; f_k++) {
                r2[c_j] = r2[c_j] + b_t_vec[f_k] * b_b[f_k + b_b.size(0) * c_j];
            }
        }
        oc_loop_ub = r2.size(1);
        for (int i99{0}; i99 < oc_loop_ub; i99++) {
            at_norm[(2 * i99 + 2 * at_norm.size(1) * b_k) + 1] = r2[i99];
        }
        // 'buildConstr:94' v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [ 1; end ], :);
        z1_idx_0 = std::pow(normR1D[0], 2.0);
        z1_idx_1 = std::pow(normR1D[normR1D.size(1) - 1], 2.0);
        iv[1] = BasisVal.size(0) - 1;
        for (int i100{0}; i100 < q_loop_ub; i100++) {
            v2_vec[2 * i100 + 2 * v2_vec.size(1) * b_k] =
                z1_idx_0 * BasisVal[BasisVal.size(0) * i100];
            v2_vec[(2 * i100 + 2 * v2_vec.size(1) * b_k) + 1] =
                z1_idx_1 * BasisVal[iv[1] + BasisVal.size(0) * i100];
        }
        // 'buildConstr:95' continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
        // 'buildConstr:96'                    v2_vec( 2, :, k ); at_norm( 2, :, k ) ];
        // 'buildConstr:97' Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity.*
        // mask_continuity;
        r4.set_size(indAC_tmp.size(1));
        pc_loop_ub = indAC_tmp.size(1);
        for (int i101{0}; i101 < pc_loop_ub; i101++) {
            r4[i101] = indAC_tmp[i101];
        }
        qc_loop_ub = v2_vec.size(1);
        if (r4.size(0) == v2_vec.size(1)) {
            int rc_loop_ub;
            int sc_loop_ub;
            int tc_loop_ub;
            rc_loop_ub = at_norm.size(1);
            b_v2_vec.set_size(4, v2_vec.size(1));
            for (int i102{0}; i102 < qc_loop_ub; i102++) {
                b_v2_vec[4 * i102] = v2_vec[2 * i102 + 2 * v2_vec.size(1) * b_k];
            }
            for (int i103{0}; i103 < rc_loop_ub; i103++) {
                b_v2_vec[4 * i103 + 1] = at_norm[2 * i103 + 2 * at_norm.size(1) * b_k];
            }
            for (int i104{0}; i104 < qc_loop_ub; i104++) {
                b_v2_vec[4 * i104 + 2] = v2_vec[(2 * i104 + 2 * v2_vec.size(1) * b_k) + 1];
            }
            for (int i105{0}; i105 < rc_loop_ub; i105++) {
                b_v2_vec[4 * i105 + 3] = at_norm[(2 * i105 + 2 * at_norm.size(1) * b_k) + 1];
            }
            b_Aeq.set_size(4, r4.size(0));
            sc_loop_ub = r4.size(0);
            for (int i106{0}; i106 < sc_loop_ub; i106++) {
                b_Aeq[4 * i106] =
                    Aeq[(d_k + Aeq.size(0) * (r4[i106] - 1)) - 1] + b_v2_vec[4 * i106];
                b_Aeq[4 * i106 + 1] =
                    Aeq[d_k + Aeq.size(0) * (r4[i106] - 1)] + b_v2_vec[4 * i106 + 1];
                b_Aeq[4 * i106 + 2] =
                    Aeq[(d_k + Aeq.size(0) * (r4[i106] - 1)) + 1] + -b_v2_vec[4 * i106 + 2];
                b_Aeq[4 * i106 + 3] =
                    Aeq[(d_k + Aeq.size(0) * (r4[i106] - 1)) + 2] + -b_v2_vec[4 * i106 + 3];
            }
            tc_loop_ub = b_Aeq.size(1);
            for (int i107{0}; i107 < tc_loop_ub; i107++) {
                Aeq[(d_k + Aeq.size(0) * (r4[i107] - 1)) - 1] = b_Aeq[4 * i107];
                Aeq[d_k + Aeq.size(0) * (r4[i107] - 1)] = b_Aeq[4 * i107 + 1];
                Aeq[(d_k + Aeq.size(0) * (r4[i107] - 1)) + 1] = b_Aeq[4 * i107 + 2];
                Aeq[(d_k + Aeq.size(0) * (r4[i107] - 1)) + 2] = b_Aeq[4 * i107 + 3];
            }
        } else {
            binary_expand_op(Aeq, indAEL, r4, v2_vec, b_k, at_norm, mask_continuity);
        }
    }
    // 'buildConstr:100' beq( [ 1, 2, end-1, end ] ) = [ v_0^2; at_0; v_1^2; at_1 ] .*
    // mask_continuity;
    beq[0] = v_0 * v_0;
    beq[1] = at_0;
    beq[static_cast<int>(Nec) - 2] = -(v_1 * v_1);
    beq[static_cast<int>(Nec) - 1] = -at_1;
    //  Add a ramp on the acceleration and speed limits
    // 'buildConstr:103' vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
    coder::b_linspace(ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    vel_ramp.set_size(r2.size(1));
    r_loop_ub = r2.size(1);
    for (int i24{0}; i24 < r_loop_ub; i24++) {
        vel_ramp[i24] = r2[i24];
    }
    // 'buildConstr:104' acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )',1,
    // Nc -1 );
    coder::b_linspace(ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    r3.set_size(r2.size(1));
    v_loop_ub = r2.size(1);
    for (int i28{0}; i28 < v_loop_ub; i28++) {
        r3[i28] = r2[i28];
    }
    coder::repmat(r3, y_tmp + 1, acc_ramp);
    // 'buildConstr:106' if( Nwindow > 1 )
    if (windowCurv.size(1) > 1) {
        int bb_loop_ub;
        int c_input_sizes_idx_1;
        int d_input_sizes_idx_1;
        int input_sizes_idx_1;
        int kb_loop_ub;
        int result;
        signed char b_input_sizes_idx_1;
        bool empty_non_axis_sizes;
        // 'buildConstr:107' ramp = [ones(M, Nc ), vel_ramp, acc_ramp, ...
        // 'buildConstr:108'             repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)];
        bb_loop_ub = acc_ramp.size(1);
        b_vel_ramp.set_size(1, acc_ramp.size(1) + 1);
        b_vel_ramp[0] = vel_ramp[vel_ramp.size(0) - 1];
        for (int i32{0}; i32 < bb_loop_ub; i32++) {
            b_vel_ramp[i32 + 1] = acc_ramp[(acc_ramp.size(0) + acc_ramp.size(0) * i32) - 1];
        }
        coder::repmat(b_vel_ramp, static_cast<double>(BasisVal.size(0)),
                      static_cast<double>(windowCurv.size(1)) - 2.0, varargin_4);
        if ((BasisVal.size(0) != 0) && (y_tmp + 2 != 0)) {
            result = BasisVal.size(0);
        } else if (vel_ramp.size(0) != 0) {
            result = vel_ramp.size(0);
        } else if ((acc_ramp.size(0) != 0) && (acc_ramp.size(1) != 0)) {
            result = acc_ramp.size(0);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            result = varargin_4.size(0);
        } else {
            result = BasisVal.size(0);
            if (acc_ramp.size(0) > BasisVal.size(0)) {
                result = acc_ramp.size(0);
            }
            if (varargin_4.size(0) > result) {
                result = varargin_4.size(0);
            }
        }
        empty_non_axis_sizes = (result == 0);
        if (empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (y_tmp + 2 != 0))) {
            input_sizes_idx_1 = y_tmp + 2;
        } else {
            input_sizes_idx_1 = 0;
        }
        if (empty_non_axis_sizes || (vel_ramp.size(0) != 0)) {
            b_input_sizes_idx_1 = 1;
        } else {
            b_input_sizes_idx_1 = 0;
        }
        if (empty_non_axis_sizes || ((acc_ramp.size(0) != 0) && (acc_ramp.size(1) != 0))) {
            c_input_sizes_idx_1 = acc_ramp.size(1);
        } else {
            c_input_sizes_idx_1 = 0;
        }
        if (empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            d_input_sizes_idx_1 = varargin_4.size(1);
        } else {
            d_input_sizes_idx_1 = 0;
        }
        ramp.set_size(result, ((input_sizes_idx_1 + b_input_sizes_idx_1) + c_input_sizes_idx_1) +
                                  d_input_sizes_idx_1);
        for (int i43{0}; i43 < input_sizes_idx_1; i43++) {
            for (int i45{0}; i45 < result; i45++) {
                ramp[i45 + ramp.size(0) * i43] = 1.0;
            }
        }
        kb_loop_ub = b_input_sizes_idx_1;
        for (int i47{0}; i47 < kb_loop_ub; i47++) {
            for (int i50{0}; i50 < result; i50++) {
                ramp[i50 + ramp.size(0) * input_sizes_idx_1] = vel_ramp[i50];
            }
        }
        for (int i49{0}; i49 < c_input_sizes_idx_1; i49++) {
            for (int i52{0}; i52 < result; i52++) {
                ramp[i52 + ramp.size(0) * ((i49 + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                    acc_ramp[i52 + result * i49];
            }
        }
        for (int i51{0}; i51 < d_input_sizes_idx_1; i51++) {
            for (int i53{0}; i53 < result; i53++) {
                ramp[i53 + ramp.size(0) * (((i51 + input_sizes_idx_1) + b_input_sizes_idx_1) +
                                           c_input_sizes_idx_1)] = varargin_4[i53 + result * i51];
            }
        }
        // 'buildConstr:109' b  = b .* ramp(:);
        if (b.size(0) == ramp.size(0) * ramp.size(1)) {
            int mb_loop_ub;
            mb_loop_ub = b.size(0);
            for (int i54{0}; i54 < mb_loop_ub; i54++) {
                b[i54] = b[i54] * ramp[i54];
            }
        } else {
            binary_expand_op(b, ramp);
        }
    }
    //  Continuity equations
    // 'buildConstr:113' continuity = [ v2_vec( 2, : , 1 ); at_norm( 2, :, 1 ) ];
    cb_loop_ub = v2_vec.size(1);
    db_loop_ub = at_norm.size(1);
    continuity.set_size(2, v2_vec.size(1));
    for (int i34{0}; i34 < cb_loop_ub; i34++) {
        continuity[2 * i34] = v2_vec[2 * i34 + 1];
    }
    for (int i36{0}; i36 < db_loop_ub; i36++) {
        continuity[2 * i36 + 1] = at_norm[2 * i36 + 1];
    }
    // 'buildConstr:115' checkValidity( A, b, Aeq, beq, continuity );
    // 'buildConstr:123' assert( ~any( isnan( A ) , 'all' ),          mfilename + " Error : A has
    // NaN"); 'buildConstr:124' assert( ~any( isnan( b ) , 'all' ),          mfilename + " Error : b
    // has NaN"); 'buildConstr:125' assert( ~any( find( b < 0 ) , 'all' ),       mfilename + " Error
    // : b should be positive"); 'buildConstr:126' assert( ~any( isnan( Aeq ) , 'all' ), mfilename +
    // " Error : Aeq has NaN"); 'buildConstr:127' assert( ~any( isnan( beq ) , 'all' ), mfilename +
    // " Error : beq has NaN"); 'buildConstr:128' assert( ~any( isnan( continuity ) , 'all' ),
    // mfilename + " Error : continuity has NaN"); 'buildConstr:117' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstr.cpp
//
// [EOF]
//
