//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildConstr.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

// Include Files
#include "buildConstr.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "colon.h"
#include "linspace.h"
#include "minOrMax.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "repmat.h"
#include "vecnorm.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void b_binary_expand_op(::coder::array<double, 3U> &Acc, const ::coder::array<int, 1U> &r,
                               const ::coder::array<double, 2U> &r2D_a, int j, int i4,
                               const ::coder::array<double, 2U> &BasisVal,
                               const ::coder::array<double, 1U> &r1,
                               const ::coder::array<double, 2U> &BasisValD);

static void binary_expand_op(::coder::array<double, 2U> &v_max, const double ctx_cfg_vmax[6],
                             const signed char _data[], const int _size[2],
                             const ::coder::array<double, 2U> &r1D_a);

static void binary_expand_op(::coder::array<double, 3U> &Acc, const ::coder::array<int, 1U> &r,
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
// Arguments    : ::coder::array<double, 3U> &Acc
//                const ::coder::array<int, 1U> &r
//                const ::coder::array<double, 2U> &r2D_a
//                int j
//                int i4
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 1U> &r1
//                const ::coder::array<double, 2U> &BasisValD
// Return Type  : void
//
namespace ocn {
static void b_binary_expand_op(::coder::array<double, 3U> &Acc, const ::coder::array<int, 1U> &r,
                               const ::coder::array<double, 2U> &r2D_a, int j, int i4,
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
            Acc[(r[i3] + Acc.size(0) * i1) - 1] =
                r2D_a[j + r2D_a.size(0) * (i3 * stride_0_0)] *
                    BasisVal[i3 * stride_1_0 + BasisVal.size(0) * aux_1_1] +
                r1[i3 * stride_2_0] * BasisValD[i3 * stride_3_0 + BasisValD.size(0) * aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &v_max
//                const double ctx_cfg_vmax[6]
//                const signed char _data[]
//                const int _size[2]
//                const ::coder::array<double, 2U> &r1D_a
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &v_max, const double ctx_cfg_vmax[6],
                             const signed char _data[], const int _size[2],
                             const ::coder::array<double, 2U> &r1D_a)
{
    ::coder::array<double, 2U> b_ctx_cfg_vmax;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int unnamed_idx_0;
    unnamed_idx_0 = _size[1];
    if (r1D_a.size(0) == 1) {
        i = unnamed_idx_0;
    } else {
        i = r1D_a.size(0);
    }
    b_ctx_cfg_vmax.set_size(i, r1D_a.size(1));
    stride_0_0 = (unnamed_idx_0 != 1);
    stride_1_0 = (r1D_a.size(0) != 1);
    loop_ub = r1D_a.size(1);
    for (int i1{0}; i1 < loop_ub; i1++) {
        int c_loop_ub;
        if (r1D_a.size(0) == 1) {
            c_loop_ub = unnamed_idx_0;
        } else {
            c_loop_ub = r1D_a.size(0);
        }
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_ctx_cfg_vmax[i3 + b_ctx_cfg_vmax.size(0) * i1] =
                ctx_cfg_vmax[_data[i3 * stride_0_0] - 1] /
                r1D_a[i3 * stride_1_0 + r1D_a.size(0) * i1];
        }
    }
    b_loop_ub = b_ctx_cfg_vmax.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = b_ctx_cfg_vmax.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            double varargin_1;
            varargin_1 = b_ctx_cfg_vmax[i4 + b_ctx_cfg_vmax.size(0) * i2];
            v_max[i4 + v_max.size(0) * i2] = std::pow(varargin_1, 2.0);
        }
    }
}

//
// Arguments    : ::coder::array<double, 3U> &Acc
//                const ::coder::array<int, 1U> &r
//                const ::coder::array<double, 2U> &r2D
//                int j
//                int i4
//                const ::coder::array<double, 2U> &BasisVal
//                const ::coder::array<double, 1U> &r1
//                const ::coder::array<double, 2U> &BasisValD
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 3U> &Acc, const ::coder::array<int, 1U> &r,
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
            Acc[((r[i3] + Acc.size(0) * i1) + Acc.size(0) * Acc.size(1)) - 1] =
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
//                const Kinematics *ctx_kin
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
                 const Kinematics *ctx_kin, const ::coder::array<CurvStruct, 2U> &windowCurv,
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
    ::coder::array<double, 2U> amax_data;
    ::coder::array<double, 2U> b_Acc;
    ::coder::array<double, 2U> b_Aeq;
    ::coder::array<double, 2U> b_amax;
    ::coder::array<double, 2U> b_b;
    ::coder::array<double, 2U> b_ctx_cfg_vmax;
    ::coder::array<double, 2U> b_r1D_r;
    ::coder::array<double, 2U> b_v2_vec;
    ::coder::array<double, 2U> b_vel_ramp;
    ::coder::array<double, 2U> c_varargin_1;
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
    ::coder::array<int, 1U> r10;
    ::coder::array<int, 1U> r8;
    ::coder::array<signed char, 2U> b_varargin_1;
    double b_amax_data[6];
    double d_y[2];
    double Nec;
    double Nx;
    int indAEL[4];
    int b_iv[2];
    int iv1[2];
    int tmp_size[2];
    int M;
    int N;
    int ac_loop_ub;
    int b_input_sizes_idx_0;
    int b_loop_ub;
    int b_unnamed_idx_1;
    int b_y;
    int c_input_sizes_idx_0;
    int c_loop_ub;
    int c_y;
    int cb_loop_ub;
    int e_loop_ub;
    int end;
    int end_tmp;
    int g_loop_ub;
    int h_loop_ub;
    int i24;
    int i66;
    int i68;
    int ib_loop_ub;
    int input_sizes_idx_0;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int mb_loop_ub;
    int n_loop_ub;
    int nc_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int partialTrueCount;
    int pb_loop_ub;
    int q_loop_ub;
    int qb_loop_ub;
    int r_loop_ub;
    int result;
    int scalarLB;
    int tb_loop_ub;
    int tmp_data_idx_1;
    int trueCount;
    int ub_loop_ub;
    int varargin_1;
    int vb_loop_ub;
    int vectorUB;
    int wb_loop_ub;
    int x_loop_ub;
    int xb_loop_ub;
    int y;
    int y_tmp;
    int yb_loop_ub;
    signed char b_tmp_data[6];
    signed char tmp_data[6];
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
        b_amax_data[i8] = amax[tmp_data[i8] - 1];
    }
    amax_data.set(&b_amax_data[0], 1, trueCount);
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
    // 'buildConstr:44' Acc         = zeros( M * Ndim , N, 2 );
    c_y = static_cast<int>(static_cast<double>(BasisVal.size(0)) *
                           static_cast<double>(ctx_cfg_NumberAxis));
    Acc.set_size(c_y, BasisVal.size(1), 2);
    j_loop_ub = BasisVal.size(1);
    for (int i19{0}; i19 < 2; i19++) {
        for (int i20{0}; i20 < j_loop_ub; i20++) {
            for (int i21{0}; i21 < c_y; i21++) {
                Acc[(i21 + Acc.size(0) * i20) + Acc.size(0) * Acc.size(1) * i19] = 0.0;
            }
        }
    }
    // 'buildConstr:45' indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );
    coder::eml_integer_colon_dispatcher(ctx_cfg_NumberAxis, r1);
    tmp_data_idx_1 = BasisVal.size(0);
    indAT.set_size(2, r1.size(1));
    k_loop_ub = r1.size(1);
    for (int i22{0}; i22 < k_loop_ub; i22++) {
        int indAT_tmp;
        indAT_tmp = r1[i22] - 1;
        indAT[2 * i22] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                          static_cast<double>(BasisVal.size(0))) +
                         1;
        indAT[2 * i22 + 1] = static_cast<int>(static_cast<double>(indAT_tmp) *
                                              static_cast<double>(BasisVal.size(0))) +
                             tmp_data_idx_1;
    }
    // 'buildConstr:46' mask_continuity = [ 1; 1; -1; -1 ];
    // 'buildConstr:47' v_max       = zeros( Ndim + 1, M );
    v_max.set_size(ctx_cfg_NumberAxis + 1, BasisVal.size(0));
    l_loop_ub = BasisVal.size(0);
    for (int i23{0}; i23 < l_loop_ub; i23++) {
        int m_loop_ub;
        m_loop_ub = ctx_cfg_NumberAxis + 1;
        for (int i25{0}; i25 < m_loop_ub; i25++) {
            v_max[i25 + v_max.size(0) * i23] = 0.0;
        }
    }
    // 'buildConstr:49' for k = 1 : Nwindow
    i24 = windowCurv.size(1);
    if (0 <= windowCurv.size(1) - 1) {
        int unnamed_idx_1;
        end = ctx_cfg_maskTot_size[1] - 1;
        coder::eml_integer_colon_dispatcher(static_cast<int>(static_cast<double>(y_tmp + 2) *
                                                             static_cast<double>(BasisVal.size(0))),
                                            r1);
        n_loop_ub = r1.size(1);
        unnamed_idx_1 = b_amax.size(0) * b_amax.size(1);
        o_loop_ub = unnamed_idx_1;
        p_loop_ub = indAT.size(1);
        q_loop_ub = indAT.size(1);
    }
    if (0 <= i24 - 1) {
        tmp_size[0] = 1;
        scalarLB = (n_loop_ub / 4) << 2;
        vectorUB = scalarLB - 4;
        b_unnamed_idx_1 = b_amax.size(0) * b_amax.size(1);
    }
    for (int b_k{0}; b_k < i24; b_k++) {
        double c_k;
        double z1_idx_0;
        double z1_idx_1;
        int ab_loop_ub;
        int ad_loop_ub;
        int b_inner;
        int b_nc;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_trueCount;
        int b_v_max;
        int b_vectorUB;
        int c_result;
        int c_unnamed_idx_1;
        int cc_loop_ub;
        int d_input_sizes_idx_0;
        int d_scalarLB;
        int d_unnamed_idx_1;
        int d_vectorUB;
        int db_loop_ub;
        int dc_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int f_y;
        int fc_loop_ub;
        int hb_loop_ub;
        int hc_loop_ub;
        int i69;
        int i81;
        int i84;
        int ic_loop_ub;
        int inner;
        int kc_loop_ub;
        int lc_loop_ub;
        int mc_loop_ub;
        int nc;
        int ob_loop_ub;
        int oc_loop_ub;
        int pc_loop_ub;
        int qc_loop_ub;
        int rc_loop_ub;
        int sc_loop_ub;
        int tc_loop_ub;
        int uc_loop_ub;
        int vc_loop_ub;
        int wc_loop_ub;
        int xc_loop_ub;
        int yc_loop_ub;
        bool c_empty_non_axis_sizes;
        bool guard1{false};
        //  Compute the partial derivatives
        // 'buildConstr:51' [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, &windowCurv[b_k], u_vec, r0D, r1D, r2D, r3D);
        // 'buildConstr:53' if( windowCurv( k ).Info.TRAFO )
        if (windowCurv[b_k].Info.TRAFO) {
            int s_loop_ub;
            // 'buildConstr:54' [ ~, r1D_a, r2D_a ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
            ctx_kin->joint(r0D, r1D, r2D, a__1, r1D_a, r2D_a);
            // 'buildConstr:55' r1D_r    = r1D;
            r1D_r.set_size(r1D.size(0), r1D.size(1));
            s_loop_ub = r1D.size(1);
            for (int i27{0}; i27 < s_loop_ub; i27++) {
                int u_loop_ub;
                u_loop_ub = r1D.size(0);
                for (int i29{0}; i29 < u_loop_ub; i29++) {
                    r1D_r[i29 + r1D_r.size(0) * i27] = r1D[i29 + r1D.size(0) * i27];
                }
            }
        } else {
            int t_loop_ub;
            int w_loop_ub;
            // 'buildConstr:56' else
            // 'buildConstr:57' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            ctx_kin->v_relative(r0D, r1D, r1D_r);
            // 'buildConstr:58' r1D_a    = r1D;
            r1D_a.set_size(r1D.size(0), r1D.size(1));
            t_loop_ub = r1D.size(1);
            for (int i28{0}; i28 < t_loop_ub; i28++) {
                int v_loop_ub;
                v_loop_ub = r1D.size(0);
                for (int i30{0}; i30 < v_loop_ub; i30++) {
                    r1D_a[i30 + r1D_a.size(0) * i28] = r1D[i30 + r1D.size(0) * i28];
                }
            }
            // 'buildConstr:59' r2D_a    = r2D;
            w_loop_ub = r2D.size(1);
            r2D_a.set_size(r2D.size(0), r2D.size(1));
            for (int i32{0}; i32 < w_loop_ub; i32++) {
                int y_loop_ub;
                y_loop_ub = r2D.size(0);
                for (int i33{0}; i33 < y_loop_ub; i33++) {
                    r2D_a[i33 + r2D_a.size(0) * i32] = r2D[i33 + r2D.size(0) * i32];
                }
            }
        }
        //  Tangent unit vector at start and at end
        // 'buildConstr:63' normR1D = vecnorm( r1D );
        coder::vecnorm(r1D, normR1D);
        // 'buildConstr:64' t_vec( : , :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );
        b_iv[0] = 0;
        b_iv[1] = r1D.size(1) - 1;
        ab_loop_ub = r1D.size(0);
        x.set_size(r1D.size(0), 2);
        iv1[0] = 0;
        iv1[1] = normR1D.size(1) - 1;
        for (int i34{0}; i34 < 2; i34++) {
            for (int i36{0}; i36 < ab_loop_ub; i36++) {
                x[i36 + x.size(0) * i34] = r1D[i36 + r1D.size(0) * b_iv[i34]];
            }
            d_y[i34] = normR1D[iv1[i34]];
        }
        db_loop_ub = x.size(0);
        b_scalarLB = (db_loop_ub / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i39{0}; i39 < 2; i39++) {
            int i40;
            for (i40 = 0; i40 <= b_vectorUB; i40 += 2) {
                __m128d r4;
                r4 = _mm_loadu_pd(&x[i40 + x.size(0) * i39]);
                _mm_storeu_pd(&t_vec[(i40 + t_vec.size(0) * i39) + t_vec.size(0) * 2 * b_k],
                              _mm_div_pd(r4, _mm_set1_pd(d_y[i39])));
            }
            for (i40 = b_scalarLB; i40 < db_loop_ub; i40++) {
                t_vec[(i40 + t_vec.size(0) * i39) + t_vec.size(0) * 2 * b_k] =
                    x[i40 + x.size(0) * i39] / d_y[i39];
            }
        }
        // 'buildConstr:66' v_max( 1 : Ndim, : ) = ( ctx.cfg.vmax( ctx.cfg.maskTot ).'./ r1D_a ).^2;
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
            int gb_loop_ub;
            b_ctx_cfg_vmax.set_size(b_trueCount, r1D_a.size(1));
            fb_loop_ub = r1D_a.size(1);
            for (int i42{0}; i42 < fb_loop_ub; i42++) {
                for (int i45{0}; i45 < b_trueCount; i45++) {
                    b_ctx_cfg_vmax[i45 + b_ctx_cfg_vmax.size(0) * i42] =
                        ctx_cfg_vmax[b_tmp_data[i45] - 1] / r1D_a[i45 + r1D_a.size(0) * i42];
                }
            }
            gb_loop_ub = b_ctx_cfg_vmax.size(1);
            for (int i47{0}; i47 < gb_loop_ub; i47++) {
                int jb_loop_ub;
                jb_loop_ub = b_ctx_cfg_vmax.size(0);
                for (int i50{0}; i50 < jb_loop_ub; i50++) {
                    double d_varargin_1;
                    d_varargin_1 = b_ctx_cfg_vmax[i50 + b_ctx_cfg_vmax.size(0) * i47];
                    v_max[i50 + v_max.size(0) * i47] = std::pow(d_varargin_1, 2.0);
                }
            }
        } else {
            binary_expand_op(v_max, ctx_cfg_vmax, b_tmp_data, tmp_size, r1D_a);
        }
        //  Maximum constraint on the speed
        // 'buildConstr:69' v_max( end, : ) = ( windowCurv( k ).Info.FeedRate ./ ...
        // 'buildConstr:70'         vecnorm( r1D_r( ctx.cfg.indCart, : ) ) ).^2;
        hb_loop_ub = r1D_r.size(1);
        b_r1D_r.set_size(ctx_cfg_indCart.size(0), r1D_r.size(1));
        for (int i49{0}; i49 < hb_loop_ub; i49++) {
            int lb_loop_ub;
            lb_loop_ub = ctx_cfg_indCart.size(0);
            for (int i53{0}; i53 < lb_loop_ub; i53++) {
                b_r1D_r[i53 + b_r1D_r.size(0) * i49] =
                    r1D_r[(ctx_cfg_indCart[i53] + r1D_r.size(0) * i49) - 1];
            }
        }
        coder::vecnorm(b_r1D_r, r2);
        b_v_max = v_max.size(0) - 1;
        ob_loop_ub = r2.size(1);
        for (int i57{0}; i57 < ob_loop_ub; i57++) {
            double e_varargin_1;
            e_varargin_1 = windowCurv[b_k].Info.FeedRate / r2[i57];
            v_max[b_v_max + v_max.size(0) * i57] = std::pow(e_varargin_1, 2.0);
        }
        // 'buildConstr:72' f_max = min( v_max, [], 1 );
        coder::internal::minimum(v_max, f_max);
        // 'buildConstr:74' for j = 1 : Ndim
        if (0 <= ctx_cfg_NumberAxis - 1) {
            if (M < 1) {
                e_y.set_size(1, 0);
            } else {
                int sb_loop_ub;
                e_y.set_size(1, M);
                sb_loop_ub = M - 1;
                for (int i65{0}; i65 <= sb_loop_ub; i65++) {
                    e_y[i65] = i65 + 1U;
                }
            }
            i66 = r1D_a.size(1);
            tb_loop_ub = r1D_a.size(1);
            vb_loop_ub = e_y.size(1);
            i68 = r1D.size(1);
            xb_loop_ub = r1D.size(1);
            yb_loop_ub = BasisVal.size(1);
            ac_loop_ub = BasisVal.size(1);
        }
        for (int j{0}; j < ctx_cfg_NumberAxis; j++) {
            int g_y;
            int i74;
            int i76;
            int i82;
            int i83;
            //  Compute the acceleration matrix
            // 'buildConstr:75' ind = int32( 1 : M ) + ( j - 1 ) * M ;
            g_y = static_cast<int>((static_cast<double>(j + 1) - 1.0) * static_cast<double>(M));
            // 'buildConstr:76' Acc( ind, :, 1 ) = r2D_a( j, : )' .* BasisVal + 0.5 * r1D_a( j, : )'
            // .* BasisValD;
            r3.set_size(i66);
            for (int i71{0}; i71 < tb_loop_ub; i71++) {
                r3[i71] = 0.5 * r1D_a[j + r1D_a.size(0) * i71];
            }
            r8.set_size(e_y.size(1));
            for (int i73{0}; i73 < vb_loop_ub; i73++) {
                r8[i73] = static_cast<int>(e_y[i73]) + g_y;
            }
            if (r2D_a.size(1) == 1) {
                i74 = BasisVal.size(0);
            } else {
                i74 = r2D_a.size(1);
            }
            if (r3.size(0) == 1) {
                i76 = BasisValD.size(0);
            } else {
                i76 = r3.size(0);
            }
            if ((BasisVal.size(0) == r2D_a.size(1)) && (r3.size(0) == BasisValD.size(0)) &&
                (i74 == i76) && (BasisVal.size(1) == BasisValD.size(1))) {
                for (int i78{0}; i78 < yb_loop_ub; i78++) {
                    int ec_loop_ub;
                    ec_loop_ub = r2D_a.size(1);
                    for (int i79{0}; i79 < ec_loop_ub; i79++) {
                        Acc[(r8[i79] + Acc.size(0) * i78) - 1] =
                            r2D_a[j + r2D_a.size(0) * i79] *
                                BasisVal[i79 + BasisVal.size(0) * i78] +
                            r3[i79] * BasisValD[i79 + BasisValD.size(0) * i78];
                    }
                }
            } else {
                b_binary_expand_op(Acc, r8, r2D_a, j, r2D_a.size(1), BasisVal, r3, BasisValD);
            }
            // 'buildConstr:77' Acc( ind, :, 2 ) = r2D( j, : )'   .* BasisVal + 0.5 * r1D( j, : )'
            // .* BasisValD;
            r3.set_size(i68);
            for (int i80{0}; i80 < xb_loop_ub; i80++) {
                r3[i80] = 0.5 * r1D[j + r1D.size(0) * i80];
            }
            if (r2D.size(1) == 1) {
                i82 = BasisVal.size(0);
            } else {
                i82 = r2D.size(1);
            }
            if (r3.size(0) == 1) {
                i83 = BasisValD.size(0);
            } else {
                i83 = r3.size(0);
            }
            if ((BasisVal.size(0) == r2D.size(1)) && (r3.size(0) == BasisValD.size(0)) &&
                (i82 == i83) && (BasisVal.size(1) == BasisValD.size(1))) {
                for (int i85{0}; i85 < ac_loop_ub; i85++) {
                    int gc_loop_ub;
                    gc_loop_ub = r2D.size(1);
                    for (int i86{0}; i86 < gc_loop_ub; i86++) {
                        Acc[((r8[i86] + Acc.size(0) * i85) + Acc.size(0) * Acc.size(1)) - 1] =
                            r2D[j + r2D.size(0) * i86] * BasisVal[i86 + BasisVal.size(0) * i85] +
                            r3[i86] * BasisValD[i86 + BasisValD.size(0) * i85];
                    }
                }
            } else {
                binary_expand_op(Acc, r8, r2D, j, r2D.size(1), BasisVal, r3, BasisValD);
            }
        }
        //  Inequality constraints
        // 'buildConstr:81' indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
        f_y = static_cast<int>(
            static_cast<double>(static_cast<int>(((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 static_cast<double>(y_tmp + 2))) *
            static_cast<double>(M));
        indAL.set_size(1, r1.size(1));
        for (i69 = 0; i69 <= vectorUB; i69 += 4) {
            __m128i r7;
            r7 = _mm_loadu_si128((const __m128i *)&r1[i69]);
            _mm_storeu_si128((__m128i *)&indAL[i69], _mm_add_epi32(r7, _mm_set1_epi32(f_y)));
        }
        for (i69 = scalarLB; i69 < n_loop_ub; i69++) {
            indAL[i69] = r1[i69] + f_y;
        }
        // 'buildConstr:82' indAC   = int32( 1 : N  ) + ( k - 1 ) * N;
        if (N < 1) {
            e_y.set_size(1, 0);
        } else {
            int bc_loop_ub;
            e_y.set_size(1, N);
            bc_loop_ub = N - 1;
            for (int i75{0}; i75 <= bc_loop_ub; i75++) {
                e_y[i75] = i75 + 1U;
            }
        }
        c_k = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(N);
        indAC_tmp.set_size(1, e_y.size(1));
        cc_loop_ub = e_y.size(1);
        for (int i77{0}; i77 < cc_loop_ub; i77++) {
            indAC_tmp[i77] = static_cast<int>(static_cast<double>(e_y[i77]) + c_k);
        }
        // 'buildConstr:83' A( indAL, indAC )   = [ BasisVal; -BasisVal ; Acc( :, :, 1) ; -Acc( :,
        // :, 1) ];
        r8.set_size(indAL.size(1));
        dc_loop_ub = indAL.size(1);
        d_scalarLB = (indAL.size(1) / 4) << 2;
        d_vectorUB = d_scalarLB - 4;
        for (i81 = 0; i81 <= d_vectorUB; i81 += 4) {
            __m128i r9;
            r9 = _mm_loadu_si128((const __m128i *)&indAL[i81]);
            _mm_storeu_si128((__m128i *)&r8[i81], _mm_sub_epi32(r9, _mm_set1_epi32(1)));
        }
        for (i81 = d_scalarLB; i81 < dc_loop_ub; i81++) {
            r8[i81] = indAL[i81] - 1;
        }
        r10.set_size(indAC_tmp.size(1));
        fc_loop_ub = indAC_tmp.size(1);
        e_scalarLB = (indAC_tmp.size(1) / 4) << 2;
        e_vectorUB = e_scalarLB - 4;
        for (i84 = 0; i84 <= e_vectorUB; i84 += 4) {
            __m128i r11;
            r11 = _mm_loadu_si128((const __m128i *)&indAC_tmp[i84]);
            _mm_storeu_si128((__m128i *)&r10[i84], _mm_sub_epi32(r11, _mm_set1_epi32(1)));
        }
        for (i84 = e_scalarLB; i84 < fc_loop_ub; i84++) {
            r10[i84] = indAC_tmp[i84] - 1;
        }
        hc_loop_ub = BasisVal.size(1);
        varargin_2.set_size(BasisVal.size(0), BasisVal.size(1));
        for (int i87{0}; i87 < hc_loop_ub; i87++) {
            int f_scalarLB;
            int f_vectorUB;
            int i89;
            int jc_loop_ub;
            jc_loop_ub = BasisVal.size(0);
            f_scalarLB = (BasisVal.size(0) / 2) << 1;
            f_vectorUB = f_scalarLB - 2;
            for (i89 = 0; i89 <= f_vectorUB; i89 += 2) {
                _mm_storeu_pd(
                    &varargin_2[i89 + varargin_2.size(0) * i87],
                    _mm_mul_pd(
                        _mm_loadu_pd((const double *)&BasisVal[i89 + BasisVal.size(0) * i87]),
                        _mm_set1_pd(-1.0)));
            }
            for (i89 = f_scalarLB; i89 < jc_loop_ub; i89++) {
                varargin_2[i89 + varargin_2.size(0) * i87] =
                    -BasisVal[i89 + BasisVal.size(0) * i87];
            }
        }
        ic_loop_ub = Acc.size(0);
        kc_loop_ub = Acc.size(1);
        varargin_4.set_size(Acc.size(0), Acc.size(1));
        for (int i88{0}; i88 < kc_loop_ub; i88++) {
            int g_scalarLB;
            int g_vectorUB;
            int i90;
            g_scalarLB = (ic_loop_ub / 2) << 1;
            g_vectorUB = g_scalarLB - 2;
            for (i90 = 0; i90 <= g_vectorUB; i90 += 2) {
                __m128d r12;
                r12 = _mm_loadu_pd(&Acc[i90 + Acc.size(0) * i88]);
                _mm_storeu_pd(&varargin_4[i90 + varargin_4.size(0) * i88],
                              _mm_mul_pd(r12, _mm_set1_pd(-1.0)));
            }
            for (i90 = g_scalarLB; i90 < ic_loop_ub; i90++) {
                varargin_4[i90 + varargin_4.size(0) * i88] = -Acc[i90 + Acc.size(0) * i88];
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
            lc_loop_ub = BasisVal.size(0);
        } else {
            lc_loop_ub = 0;
        }
        if (c_empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            mc_loop_ub = varargin_2.size(0);
        } else {
            mc_loop_ub = 0;
        }
        guard1 = false;
        if (c_empty_non_axis_sizes) {
            guard1 = true;
        } else {
            nc_loop_ub = Acc.size(0);
            if ((Acc.size(0) != 0) && (Acc.size(1) != 0)) {
                guard1 = true;
            } else {
                c_input_sizes_idx_0 = 0;
            }
        }
        if (guard1) {
            nc_loop_ub = Acc.size(0);
            c_input_sizes_idx_0 = Acc.size(0);
        }
        if (c_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            d_input_sizes_idx_0 = varargin_4.size(0);
        } else {
            d_input_sizes_idx_0 = 0;
        }
        oc_loop_ub = Acc.size(1);
        b_Acc.set_size(nc_loop_ub, Acc.size(1));
        for (int i91{0}; i91 < oc_loop_ub; i91++) {
            for (int i93{0}; i93 < nc_loop_ub; i93++) {
                b_Acc[i93 + b_Acc.size(0) * i91] = Acc[i93 + Acc.size(0) * i91];
            }
        }
        for (int i92{0}; i92 < c_result; i92++) {
            for (int i95{0}; i95 < lc_loop_ub; i95++) {
                A[r8[i95] + A.size(0) * r10[i92]] = BasisVal[i95 + lc_loop_ub * i92];
            }
        }
        for (int i94{0}; i94 < c_result; i94++) {
            for (int i97{0}; i97 < mc_loop_ub; i97++) {
                A[r8[i97 + lc_loop_ub] + A.size(0) * r10[i94]] = varargin_2[i97 + mc_loop_ub * i94];
            }
        }
        for (int i96{0}; i96 < c_result; i96++) {
            for (int i99{0}; i99 < c_input_sizes_idx_0; i99++) {
                A[r8[(i99 + lc_loop_ub) + mc_loop_ub] + A.size(0) * r10[i96]] =
                    b_Acc[i99 + c_input_sizes_idx_0 * i96];
            }
        }
        for (int i98{0}; i98 < c_result; i98++) {
            for (int i100{0}; i100 < d_input_sizes_idx_0; i100++) {
                A[r8[((i100 + lc_loop_ub) + mc_loop_ub) + c_input_sizes_idx_0] +
                  A.size(0) * r10[i98]] = varargin_4[i100 + d_input_sizes_idx_0 * i98];
            }
        }
        // 'buildConstr:84' b( indAL )          = [ f_max'; zeros( size(f_max) )';
        // 'buildConstr:85'                             b_amax( : ); b_amax( : ) ];
        c_unnamed_idx_1 = f_max.size(1);
        d_unnamed_idx_1 = f_max.size(1);
        pc_loop_ub = f_max.size(1);
        for (int i101{0}; i101 < pc_loop_ub; i101++) {
            b[indAL[i101] - 1] = f_max[i101];
        }
        qc_loop_ub = f_max.size(1);
        for (int i102{0}; i102 < qc_loop_ub; i102++) {
            b[indAL[i102 + c_unnamed_idx_1] - 1] = 0.0;
        }
        for (int i103{0}; i103 < b_unnamed_idx_1; i103++) {
            b[indAL[(i103 + c_unnamed_idx_1) + d_unnamed_idx_1] - 1] = b_amax[i103];
        }
        for (int i104{0}; i104 < o_loop_ub; i104++) {
            b[indAL[((i104 + c_unnamed_idx_1) + d_unnamed_idx_1) + b_unnamed_idx_1] - 1] =
                b_amax[i104];
        }
        //  Continuity equations
        // 'buildConstr:88' indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2 ;
        _mm_storeu_si128((__m128i *)&indAEL[0],
                         _mm_add_epi32(_mm_add_epi32(_mm_set1_epi32(0),
                                                     _mm_loadu_si128((const __m128i *)&iv[0])),
                                       _mm_set1_epi32((b_k << 1) + 1)));
        //  Line   index
        // 'buildConstr:89' indAEC  = int32( 1 : N ) + ( k - 1 ) * N ;
        //  Column index
        // 'buildConstr:90' at_norm( 1, :, k )   = t_vec( : , 1, k )' * Acc( indAT( 1, : ) , :, 2 );
        rc_loop_ub = Acc.size(1);
        b_b.set_size(p_loop_ub, Acc.size(1));
        for (int i105{0}; i105 < rc_loop_ub; i105++) {
            for (int i106{0}; i106 < p_loop_ub; i106++) {
                b_b[i106 + b_b.size(0) * i105] =
                    Acc[((indAT[2 * i106] + Acc.size(0) * i105) + Acc.size(0) * Acc.size(1)) - 1];
            }
        }
        sc_loop_ub = t_vec.size(0);
        b_t_vec.set_size(t_vec.size(0));
        for (int i107{0}; i107 < sc_loop_ub; i107++) {
            b_t_vec[i107] = t_vec[i107 + t_vec.size(0) * 2 * b_k];
        }
        inner = b_t_vec.size(0);
        nc = b_b.size(1);
        r2.set_size(1, b_b.size(1));
        for (int b_j{0}; b_j < nc; b_j++) {
            r2[b_j] = 0.0;
            for (int d_k{0}; d_k < inner; d_k++) {
                r2[b_j] = r2[b_j] + b_t_vec[d_k] * b_b[d_k + b_b.size(0) * b_j];
            }
        }
        tc_loop_ub = r2.size(1);
        for (int i108{0}; i108 < tc_loop_ub; i108++) {
            at_norm[2 * i108 + 2 * at_norm.size(1) * b_k] = r2[i108];
        }
        // 'buildConstr:91' at_norm( 2, :, k )   = t_vec( : , 2, k )' * Acc( indAT( 2, : ) , :, 2 );
        uc_loop_ub = Acc.size(1);
        b_b.set_size(q_loop_ub, Acc.size(1));
        for (int i109{0}; i109 < uc_loop_ub; i109++) {
            for (int i110{0}; i110 < q_loop_ub; i110++) {
                b_b[i110 + b_b.size(0) * i109] =
                    Acc[((indAT[2 * i110 + 1] + Acc.size(0) * i109) + Acc.size(0) * Acc.size(1)) -
                        1];
            }
        }
        vc_loop_ub = t_vec.size(0);
        b_t_vec.set_size(t_vec.size(0));
        for (int i111{0}; i111 < vc_loop_ub; i111++) {
            b_t_vec[i111] = t_vec[(i111 + t_vec.size(0)) + t_vec.size(0) * 2 * b_k];
        }
        b_inner = b_t_vec.size(0);
        b_nc = b_b.size(1);
        r2.set_size(1, b_b.size(1));
        for (int c_j{0}; c_j < b_nc; c_j++) {
            r2[c_j] = 0.0;
            for (int e_k{0}; e_k < b_inner; e_k++) {
                r2[c_j] = r2[c_j] + b_t_vec[e_k] * b_b[e_k + b_b.size(0) * c_j];
            }
        }
        wc_loop_ub = r2.size(1);
        for (int i112{0}; i112 < wc_loop_ub; i112++) {
            at_norm[(2 * i112 + 2 * at_norm.size(1) * b_k) + 1] = r2[i112];
        }
        // 'buildConstr:93' v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [ 1; end ], :);
        z1_idx_0 = std::pow(normR1D[0], 2.0);
        z1_idx_1 = std::pow(normR1D[normR1D.size(1) - 1], 2.0);
        b_iv[1] = BasisVal.size(0) - 1;
        xc_loop_ub = BasisVal.size(1);
        for (int i113{0}; i113 < xc_loop_ub; i113++) {
            v2_vec[2 * i113 + 2 * v2_vec.size(1) * b_k] =
                z1_idx_0 * BasisVal[BasisVal.size(0) * i113];
            v2_vec[(2 * i113 + 2 * v2_vec.size(1) * b_k) + 1] =
                z1_idx_1 * BasisVal[b_iv[1] + BasisVal.size(0) * i113];
        }
        // 'buildConstr:94' continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
        // 'buildConstr:95'                    v2_vec( 2, :, k ); at_norm( 2, :, k ) ];
        // 'buildConstr:96' Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity.*
        // mask_continuity;
        r8.set_size(indAC_tmp.size(1));
        yc_loop_ub = indAC_tmp.size(1);
        for (int i114{0}; i114 < yc_loop_ub; i114++) {
            r8[i114] = indAC_tmp[i114];
        }
        ad_loop_ub = v2_vec.size(1);
        if (r8.size(0) == v2_vec.size(1)) {
            int bd_loop_ub;
            int cd_loop_ub;
            int dd_loop_ub;
            bd_loop_ub = at_norm.size(1);
            b_v2_vec.set_size(4, v2_vec.size(1));
            for (int i115{0}; i115 < ad_loop_ub; i115++) {
                b_v2_vec[4 * i115] = v2_vec[2 * i115 + 2 * v2_vec.size(1) * b_k];
            }
            for (int i116{0}; i116 < bd_loop_ub; i116++) {
                b_v2_vec[4 * i116 + 1] = at_norm[2 * i116 + 2 * at_norm.size(1) * b_k];
            }
            for (int i117{0}; i117 < ad_loop_ub; i117++) {
                b_v2_vec[4 * i117 + 2] = v2_vec[(2 * i117 + 2 * v2_vec.size(1) * b_k) + 1];
            }
            for (int i118{0}; i118 < bd_loop_ub; i118++) {
                b_v2_vec[4 * i118 + 3] = at_norm[(2 * i118 + 2 * at_norm.size(1) * b_k) + 1];
            }
            b_Aeq.set_size(4, r8.size(0));
            cd_loop_ub = r8.size(0);
            for (int i119{0}; i119 < cd_loop_ub; i119++) {
                b_Aeq[4 * i119] =
                    Aeq[(indAEL[0] + Aeq.size(0) * (r8[i119] - 1)) - 1] + b_v2_vec[4 * i119];
                b_Aeq[4 * i119 + 1] =
                    Aeq[(indAEL[1] + Aeq.size(0) * (r8[i119] - 1)) - 1] + b_v2_vec[4 * i119 + 1];
                b_Aeq[4 * i119 + 2] =
                    Aeq[(indAEL[2] + Aeq.size(0) * (r8[i119] - 1)) - 1] + -b_v2_vec[4 * i119 + 2];
                b_Aeq[4 * i119 + 3] =
                    Aeq[(indAEL[3] + Aeq.size(0) * (r8[i119] - 1)) - 1] + -b_v2_vec[4 * i119 + 3];
            }
            dd_loop_ub = b_Aeq.size(1);
            for (int i120{0}; i120 < dd_loop_ub; i120++) {
                Aeq[(indAEL[0] + Aeq.size(0) * (r8[i120] - 1)) - 1] = b_Aeq[4 * i120];
                Aeq[(indAEL[1] + Aeq.size(0) * (r8[i120] - 1)) - 1] = b_Aeq[4 * i120 + 1];
                Aeq[(indAEL[2] + Aeq.size(0) * (r8[i120] - 1)) - 1] = b_Aeq[4 * i120 + 2];
                Aeq[(indAEL[3] + Aeq.size(0) * (r8[i120] - 1)) - 1] = b_Aeq[4 * i120 + 3];
            }
        } else {
            binary_expand_op(Aeq, indAEL, r8, v2_vec, b_k, at_norm, mask_continuity);
        }
    }
    // 'buildConstr:99' beq( [ 1, 2, end-1, end ] ) = [ v_0^2; at_0; v_1^2; at_1 ] .*
    // mask_continuity;
    beq[0] = v_0 * v_0;
    beq[1] = at_0;
    beq[static_cast<int>(Nec) - 2] = -(v_1 * v_1);
    beq[static_cast<int>(Nec) - 1] = -at_1;
    //  Add a ramp on the acceleration and speed limits
    // 'buildConstr:102' vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
    coder::b_linspace(ctx_cfg_opt_VEL_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    vel_ramp.set_size(r2.size(1));
    r_loop_ub = r2.size(1);
    for (int i26{0}; i26 < r_loop_ub; i26++) {
        vel_ramp[i26] = r2[i26];
    }
    // 'buildConstr:103' acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )',1,
    // Nc -1 );
    coder::b_linspace(ctx_cfg_opt_ACC_RAMP_OVER_WINDOWS, static_cast<double>(BasisVal.size(0)), r2);
    r3.set_size(r2.size(1));
    x_loop_ub = r2.size(1);
    for (int i31{0}; i31 < x_loop_ub; i31++) {
        r3[i31] = r2[i31];
    }
    coder::repmat(r3, y_tmp + 1, acc_ramp);
    // 'buildConstr:105' if( Nwindow > 1 )
    if (windowCurv.size(1) > 1) {
        int b_result;
        int bb_loop_ub;
        int c_input_sizes_idx_1;
        int d_input_sizes_idx_1;
        int input_sizes_idx_1;
        int nb_loop_ub;
        signed char b_input_sizes_idx_1;
        bool b_empty_non_axis_sizes;
        // 'buildConstr:106' ramp = [ones(M, Nc ), vel_ramp, acc_ramp, ...
        // 'buildConstr:107'             repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)];
        bb_loop_ub = acc_ramp.size(1);
        b_vel_ramp.set_size(1, acc_ramp.size(1) + 1);
        b_vel_ramp[0] = vel_ramp[vel_ramp.size(0) - 1];
        for (int i37{0}; i37 < bb_loop_ub; i37++) {
            b_vel_ramp[i37 + 1] = acc_ramp[(acc_ramp.size(0) + acc_ramp.size(0) * i37) - 1];
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
        for (int i51{0}; i51 < input_sizes_idx_1; i51++) {
            for (int i54{0}; i54 < b_result; i54++) {
                ramp[i54 + ramp.size(0) * i51] = 1.0;
            }
        }
        nb_loop_ub = b_input_sizes_idx_1;
        for (int i56{0}; i56 < nb_loop_ub; i56++) {
            for (int i59{0}; i59 < b_result; i59++) {
                ramp[i59 + ramp.size(0) * input_sizes_idx_1] = vel_ramp[i59];
            }
        }
        for (int i58{0}; i58 < c_input_sizes_idx_1; i58++) {
            for (int i62{0}; i62 < b_result; i62++) {
                ramp[i62 + ramp.size(0) * ((i58 + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                    acc_ramp[i62 + b_result * i58];
            }
        }
        for (int i61{0}; i61 < d_input_sizes_idx_1; i61++) {
            for (int i63{0}; i63 < b_result; i63++) {
                ramp[i63 + ramp.size(0) * (((i61 + input_sizes_idx_1) + b_input_sizes_idx_1) +
                                           c_input_sizes_idx_1)] = varargin_4[i63 + b_result * i61];
            }
        }
        // 'buildConstr:108' b  = b .* ramp(:);
        if (b.size(0) == ramp.size(0) * ramp.size(1)) {
            int c_scalarLB;
            int c_vectorUB;
            int i67;
            int rb_loop_ub;
            rb_loop_ub = b.size(0);
            c_scalarLB = (b.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (i67 = 0; i67 <= c_vectorUB; i67 += 2) {
                __m128d r5;
                __m128d r6;
                r5 = _mm_loadu_pd(&b[i67]);
                r6 = _mm_loadu_pd(&ramp[i67]);
                _mm_storeu_pd(&b[i67], _mm_mul_pd(r5, r6));
            }
            for (i67 = c_scalarLB; i67 < rb_loop_ub; i67++) {
                b[i67] = b[i67] * ramp[i67];
            }
        } else {
            binary_expand_op(b, ramp);
        }
    }
    // 'buildConstr:111' A = [ -ones( size( A, 2 ) );      A ];
    b_varargin_1.set_size(A.size(1), A.size(1));
    cb_loop_ub = A.size(1);
    for (int i35{0}; i35 < cb_loop_ub; i35++) {
        int eb_loop_ub;
        eb_loop_ub = A.size(1);
        for (int i38{0}; i38 < eb_loop_ub; i38++) {
            b_varargin_1[i38 + b_varargin_1.size(0) * i35] = -1;
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
    c_varargin_1.set_size(input_sizes_idx_0 + b_input_sizes_idx_0, result);
    for (int i41{0}; i41 < result; i41++) {
        for (int i44{0}; i44 < input_sizes_idx_0; i44++) {
            c_varargin_1[i44 + c_varargin_1.size(0) * i41] = -1.0;
        }
    }
    for (int i43{0}; i43 < result; i43++) {
        for (int i46{0}; i46 < b_input_sizes_idx_0; i46++) {
            c_varargin_1[(i46 + input_sizes_idx_0) + c_varargin_1.size(0) * i43] =
                A[i46 + b_input_sizes_idx_0 * i43];
        }
    }
    A.set_size(c_varargin_1.size(0), c_varargin_1.size(1));
    ib_loop_ub = c_varargin_1.size(1);
    for (int i48{0}; i48 < ib_loop_ub; i48++) {
        int kb_loop_ub;
        kb_loop_ub = c_varargin_1.size(0);
        for (int i52{0}; i52 < kb_loop_ub; i52++) {
            A[i52 + A.size(0) * i48] = c_varargin_1[i52 + c_varargin_1.size(0) * i48];
        }
    }
    // 'buildConstr:112' b = [ zeros( size( A, 2 ), 1 );   b ];
    r3.set_size(b.size(0) + A.size(1));
    mb_loop_ub = A.size(1);
    for (int i55{0}; i55 < mb_loop_ub; i55++) {
        r3[i55] = 0.0;
    }
    pb_loop_ub = b.size(0);
    for (int i60{0}; i60 < pb_loop_ub; i60++) {
        r3[i60 + A.size(1)] = b[i60];
    }
    b.set_size(r3.size(0));
    qb_loop_ub = r3.size(0);
    for (int i64{0}; i64 < qb_loop_ub; i64++) {
        b[i64] = r3[i64];
    }
    //  Continuity equations
    // 'buildConstr:115' continuity = [ v2_vec( 2, : , 1 ); at_norm( 2, :, 1 ) ];
    ub_loop_ub = v2_vec.size(1);
    wb_loop_ub = at_norm.size(1);
    continuity.set_size(2, v2_vec.size(1));
    for (int i70{0}; i70 < ub_loop_ub; i70++) {
        continuity[2 * i70] = v2_vec[2 * i70 + 1];
    }
    for (int i72{0}; i72 < wb_loop_ub; i72++) {
        continuity[2 * i72 + 1] = at_norm[2 * i72 + 1];
    }
    // 'buildConstr:117' c_prof_out(mfilename);
}

} // namespace ocn

//
// File trailer for buildConstr.cpp
//
// [EOF]
//
