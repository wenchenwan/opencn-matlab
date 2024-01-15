
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromU.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "calcRVAJfromU.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ R, V, A, J ] = calcRVAJfromU( ctx, curv, u_vec, ud_vec, udd_vec, ...
//                           uddd_vec )
//
// calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
//  jerk for a given set of u variable.
//
//  Inputs :
//    ctx     : The context
//    Curv    : The curve struct
//    u_vec   : [ 1 x M ] The vector of u
//    ud_vec  : [ 1 x M ] The vector of first derivative of u
//    udd_vec : [ 1 x M ] The vector of second derivative of u
//    uddd_vec: [ 1 x M ] The vector of third derivative of u
//
//  Outputs :
//    R       : [ N x M ] pose
//    V       : [ N x M ] velocity
//    A       : [ N x M ] acceleration
//    J       : [ N x M ] jerk
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
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                const ::coder::array<double, 2U> &ud_vec
//                const ::coder::array<double, 2U> &udd_vec
//                const ::coder::array<double, 2U> &uddd_vec
//                ::coder::array<double, 2U> &R
//                ::coder::array<double, 2U> &V
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 2U> &J
// Return Type  : void
//
namespace ocn {
void b_calcRVAJfromU(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, Kinematics *ctx_kin,
                     const CurvStruct *curv, const ::coder::array<double, 2U> &u_vec,
                     const ::coder::array<double, 2U> &ud_vec,
                     const ::coder::array<double, 2U> &udd_vec,
                     const ::coder::array<double, 2U> &uddd_vec, ::coder::array<double, 2U> &R,
                     ::coder::array<double, 2U> &V, ::coder::array<double, 2U> &A,
                     ::coder::array<double, 2U> &J)
{
    ::coder::array<double, 2U> b_R;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    int i11;
    int i12;
    int i16;
    int i17;
    int i18;
    int i19;
    int i20;
    int i21;
    int i22;
    int i23;
    int i24;
    int j_loop_ub;
    int m_loop_ub;
    // 'calcRVAJfromU:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );
    q_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, u_vec, R, r1D, r2D, r3D);
    // 'calcRVAJfromU:24' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv->tool.offset.z);
    // 'calcRVAJfromU:26' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int c_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int loop_ub;
        // 'calcRVAJfromU:27' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
        b_R.set_size(R.size(0), R.size(1));
        loop_ub = R.size(1) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            int b_loop_ub;
            b_loop_ub = R.size(0) - 1;
            for (int i1{0}; i1 <= b_loop_ub; i1++) {
                b_R[i1 + b_R.size(0) * i] = R[i1 + R.size(0) * i];
            }
        }
        b_r1D.set_size(r1D.size(0), r1D.size(1));
        c_loop_ub = r1D.size(1) - 1;
        for (int i2{0}; i2 <= c_loop_ub; i2++) {
            int d_loop_ub;
            d_loop_ub = r1D.size(0) - 1;
            for (int i3{0}; i3 <= d_loop_ub; i3++) {
                b_r1D[i3 + b_r1D.size(0) * i2] = r1D[i3 + r1D.size(0) * i2];
            }
        }
        b_r2D.set_size(r2D.size(0), r2D.size(1));
        e_loop_ub = r2D.size(1) - 1;
        for (int i4{0}; i4 <= e_loop_ub; i4++) {
            int f_loop_ub;
            f_loop_ub = r2D.size(0) - 1;
            for (int i5{0}; i5 <= f_loop_ub; i5++) {
                b_r2D[i5 + b_r2D.size(0) * i4] = r2D[i5 + r2D.size(0) * i4];
            }
        }
        b_r3D.set_size(r3D.size(0), r3D.size(1));
        g_loop_ub = r3D.size(1) - 1;
        for (int i6{0}; i6 <= g_loop_ub; i6++) {
            int h_loop_ub;
            h_loop_ub = r3D.size(0) - 1;
            for (int i7{0}; i7 <= h_loop_ub; i7++) {
                b_r3D[i7 + b_r3D.size(0) * i6] = r3D[i7 + r3D.size(0) * i6];
            }
        }
        ctx_kin->joint(b_R, b_r1D, b_r2D, b_r3D, R, r1D, r2D, r3D);
    }
    // 'calcRVAJfromU:30' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
    // 'calcRVAJfromU:31'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //
    //  Inputs :
    //    ud_vec      : [ 1 x M ] The vector of first derivative of u
    //    udd_vec     : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
    //    r0D         : [ 1 x M ] The vector of r
    //    r1D         : [ 1 x M ] The vector of first derivative of r
    //    r2D         : [ 1 x M ] The vector of second derivative of r
    //    r3D         : [ 1 x M ] The vector of second derivative of r
    //
    //  Outputs :
    //    R           : [ N x M ] pose
    //    V           : [ N x M ] velocity
    //    A           : [ N x M ] acceleration
    //    J           : [ N x M ] jerk
    //
    // 'calcRVAJfromUWithoutCurv:21' R = r0D;
    // 'calcRVAJfromUWithoutCurv:22' V = r1D .* ud_vec;
    if (r1D.size(1) == ud_vec.size(1)) {
        int i_loop_ub;
        V.set_size(r1D.size(0), r1D.size(1));
        i_loop_ub = r1D.size(1);
        for (int i8{0}; i8 < i_loop_ub; i8++) {
            int k_loop_ub;
            int scalarLB;
            int vectorUB;
            k_loop_ub = r1D.size(0);
            scalarLB = (r1D.size(0) / 2) << 1;
            vectorUB = scalarLB - 2;
            for (int i10{0}; i10 <= vectorUB; i10 += 2) {
                __m128d r1;
                r1 = _mm_loadu_pd(&r1D[i10 + r1D.size(0) * i8]);
                _mm_storeu_pd(&V[i10 + V.size(0) * i8], _mm_mul_pd(r1, _mm_set1_pd(ud_vec[i8])));
            }
            for (int i10{scalarLB}; i10 < k_loop_ub; i10++) {
                V[i10 + V.size(0) * i8] = r1D[i10 + r1D.size(0) * i8] * ud_vec[i8];
            }
        }
    } else {
        b_times(V, r1D, ud_vec);
    }
    // 'calcRVAJfromUWithoutCurv:23' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    r.set_size(1, ud_vec.size(1));
    j_loop_ub = ud_vec.size(1);
    for (int i9{0}; i9 < j_loop_ub; i9++) {
        double varargin_1;
        varargin_1 = ud_vec[i9];
        r[i9] = std::pow(varargin_1, 2.0);
    }
    if (r2D.size(1) == 1) {
        i11 = r.size(1);
    } else {
        i11 = r2D.size(1);
    }
    if (r1D.size(1) == 1) {
        i12 = udd_vec.size(1);
    } else {
        i12 = r1D.size(1);
    }
    if ((r2D.size(1) == r.size(1)) && (r1D.size(1) == udd_vec.size(1)) &&
        (r2D.size(0) == r1D.size(0)) && (i11 == i12)) {
        int l_loop_ub;
        A.set_size(r2D.size(0), r2D.size(1));
        l_loop_ub = r2D.size(1);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            int b_scalarLB;
            int b_vectorUB;
            int n_loop_ub;
            n_loop_ub = r2D.size(0);
            b_scalarLB = (r2D.size(0) / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (int i15{0}; i15 <= b_vectorUB; i15 += 2) {
                __m128d r2;
                __m128d r3;
                r2 = _mm_loadu_pd(&r2D[i15 + r2D.size(0) * i13]);
                r3 = _mm_loadu_pd(&r1D[i15 + r1D.size(0) * i13]);
                _mm_storeu_pd(&A[i15 + A.size(0) * i13],
                              _mm_add_pd(_mm_mul_pd(r2, _mm_set1_pd(r[i13])),
                                         _mm_mul_pd(r3, _mm_set1_pd(udd_vec[i13]))));
            }
            for (int i15{b_scalarLB}; i15 < n_loop_ub; i15++) {
                A[i15 + A.size(0) * i13] = r2D[i15 + r2D.size(0) * i13] * r[i13] +
                                           r1D[i15 + r1D.size(0) * i13] * udd_vec[i13];
            }
        }
    } else {
        binary_expand_op(A, r2D, r, r1D, udd_vec);
    }
    // 'calcRVAJfromUWithoutCurv:24' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec;
    r.set_size(1, ud_vec.size(1));
    m_loop_ub = ud_vec.size(1);
    for (int i14{0}; i14 < m_loop_ub; i14++) {
        double b_varargin_1;
        b_varargin_1 = ud_vec[i14];
        r[i14] = std::pow(b_varargin_1, 3.0);
    }
    if (r2D.size(1) == 1) {
        i16 = ud_vec.size(1);
    } else {
        i16 = r2D.size(1);
    }
    if (r3D.size(1) == 1) {
        i17 = r.size(1);
    } else {
        i17 = r3D.size(1);
    }
    if (r2D.size(1) == 1) {
        i18 = ud_vec.size(1);
    } else {
        i18 = r2D.size(1);
    }
    if (i18 == 1) {
        i19 = udd_vec.size(1);
    } else if (r2D.size(1) == 1) {
        i19 = ud_vec.size(1);
    } else {
        i19 = r2D.size(1);
    }
    if (r3D.size(0) == 1) {
        i20 = r2D.size(0);
    } else {
        i20 = r3D.size(0);
    }
    if (r3D.size(1) == 1) {
        i21 = r.size(1);
    } else {
        i21 = r3D.size(1);
    }
    if (r2D.size(1) == 1) {
        i22 = ud_vec.size(1);
    } else {
        i22 = r2D.size(1);
    }
    if (i21 == 1) {
        if (i22 == 1) {
            i23 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i23 = ud_vec.size(1);
        } else {
            i23 = r2D.size(1);
        }
    } else if (r3D.size(1) == 1) {
        i23 = r.size(1);
    } else {
        i23 = r3D.size(1);
    }
    if (r1D.size(1) == 1) {
        i24 = uddd_vec.size(1);
    } else {
        i24 = r1D.size(1);
    }
    if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud_vec.size(1)) && (i16 == udd_vec.size(1)) &&
        (r3D.size(0) == r2D.size(0)) && (i17 == i19) && (r1D.size(1) == uddd_vec.size(1)) &&
        (i20 == r1D.size(0)) && (i23 == i24)) {
        int o_loop_ub;
        J.set_size(r3D.size(0), r3D.size(1));
        o_loop_ub = r3D.size(1);
        for (int i25{0}; i25 < o_loop_ub; i25++) {
            int c_scalarLB;
            int c_vectorUB;
            int p_loop_ub;
            p_loop_ub = r3D.size(0);
            c_scalarLB = (r3D.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (int i26{0}; i26 <= c_vectorUB; i26 += 2) {
                __m128d r4;
                __m128d r5;
                __m128d r6;
                r4 = _mm_loadu_pd(&r3D[i26 + r3D.size(0) * i25]);
                r5 = _mm_loadu_pd(&r2D[i26 + r2D.size(0) * i25]);
                r6 = _mm_loadu_pd(&r1D[i26 + r1D.size(0) * i25]);
                _mm_storeu_pd(
                    &J[i26 + J.size(0) * i25],
                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(r4, _mm_set1_pd(r[i25])),
                                          _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r5),
                                                                _mm_set1_pd(ud_vec[i25])),
                                                     _mm_set1_pd(udd_vec[i25]))),
                               _mm_mul_pd(r6, _mm_set1_pd(uddd_vec[i25]))));
            }
            for (int i26{c_scalarLB}; i26 < p_loop_ub; i26++) {
                J[i26 + J.size(0) * i25] =
                    (r3D[i26 + r3D.size(0) * i25] * r[i25] +
                     3.0 * r2D[i26 + r2D.size(0) * i25] * ud_vec[i25] * udd_vec[i25]) +
                    r1D[i26 + r1D.size(0) * i25] * uddd_vec[i25];
            }
        }
    } else {
        binary_expand_op(J, r3D, r, r2D, ud_vec, udd_vec, r1D, uddd_vec);
    }
}

//
// function [ R, V, A, J ] = calcRVAJfromU( ctx, curv, u_vec, ud_vec, udd_vec, ...
//                           uddd_vec )
//
// calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
//  jerk for a given set of u variable.
//
//  Inputs :
//    ctx     : The context
//    Curv    : The curve struct
//    u_vec   : [ 1 x M ] The vector of u
//    ud_vec  : [ 1 x M ] The vector of first derivative of u
//    udd_vec : [ 1 x M ] The vector of second derivative of u
//    uddd_vec: [ 1 x M ] The vector of third derivative of u
//
//  Outputs :
//    R       : [ N x M ] pose
//    V       : [ N x M ] velocity
//    A       : [ N x M ] acceleration
//    J       : [ N x M ] jerk
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
//                const GcodeInfoStruct curv_Info
//                const Tool *curv_tool
//                const ::coder::array<double, 1U> &curv_R0
//                const ::coder::array<double, 1U> &curv_R1
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                unsigned int curv_sp_index
//                double curv_a_param
//                double curv_b_param
//                const ::coder::array<double, 2U> &u_vec
//                const ::coder::array<double, 2U> &ud_vec
//                const ::coder::array<double, 2U> &udd_vec
//                const ::coder::array<double, 2U> &uddd_vec
//                ::coder::array<double, 2U> &R
//                ::coder::array<double, 2U> &V
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 2U> &J
// Return Type  : void
//
void calcRVAJfromU(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, Kinematics *ctx_kin, const GcodeInfoStruct curv_Info, const Tool *curv_tool,
    const ::coder::array<double, 1U> &curv_R0, const ::coder::array<double, 1U> &curv_R1,
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, const ::coder::array<double, 2U> &u_vec,
    const ::coder::array<double, 2U> &ud_vec, const ::coder::array<double, 2U> &udd_vec,
    const ::coder::array<double, 2U> &uddd_vec, ::coder::array<double, 2U> &R,
    ::coder::array<double, 2U> &V, ::coder::array<double, 2U> &A, ::coder::array<double, 2U> &J)
{
    ::coder::array<double, 2U> b_R;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    int i11;
    int i12;
    int i16;
    int i17;
    int i18;
    int i19;
    int i20;
    int i21;
    int i22;
    int i23;
    int i24;
    int j_loop_ub;
    int m_loop_ub;
    // 'calcRVAJfromU:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );
    h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv_Info, curv_R0, curv_R1,
                     curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch, curv_CoeffP5,
                     curv_sp_index, curv_a_param, curv_b_param, u_vec, R, r1D, r2D, r3D);
    // 'calcRVAJfromU:24' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv_tool->offset.z);
    // 'calcRVAJfromU:26' if( curv.Info.TRAFO )
    if (curv_Info.TRAFO) {
        int c_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int loop_ub;
        // 'calcRVAJfromU:27' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
        b_R.set_size(R.size(0), R.size(1));
        loop_ub = R.size(1) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            int b_loop_ub;
            b_loop_ub = R.size(0) - 1;
            for (int i1{0}; i1 <= b_loop_ub; i1++) {
                b_R[i1 + b_R.size(0) * i] = R[i1 + R.size(0) * i];
            }
        }
        b_r1D.set_size(r1D.size(0), r1D.size(1));
        c_loop_ub = r1D.size(1) - 1;
        for (int i2{0}; i2 <= c_loop_ub; i2++) {
            int d_loop_ub;
            d_loop_ub = r1D.size(0) - 1;
            for (int i3{0}; i3 <= d_loop_ub; i3++) {
                b_r1D[i3 + b_r1D.size(0) * i2] = r1D[i3 + r1D.size(0) * i2];
            }
        }
        b_r2D.set_size(r2D.size(0), r2D.size(1));
        e_loop_ub = r2D.size(1) - 1;
        for (int i4{0}; i4 <= e_loop_ub; i4++) {
            int f_loop_ub;
            f_loop_ub = r2D.size(0) - 1;
            for (int i5{0}; i5 <= f_loop_ub; i5++) {
                b_r2D[i5 + b_r2D.size(0) * i4] = r2D[i5 + r2D.size(0) * i4];
            }
        }
        b_r3D.set_size(r3D.size(0), r3D.size(1));
        g_loop_ub = r3D.size(1) - 1;
        for (int i6{0}; i6 <= g_loop_ub; i6++) {
            int h_loop_ub;
            h_loop_ub = r3D.size(0) - 1;
            for (int i7{0}; i7 <= h_loop_ub; i7++) {
                b_r3D[i7 + b_r3D.size(0) * i6] = r3D[i7 + r3D.size(0) * i6];
            }
        }
        ctx_kin->joint(b_R, b_r1D, b_r2D, b_r3D, R, r1D, r2D, r3D);
    }
    // 'calcRVAJfromU:30' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
    // 'calcRVAJfromU:31'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
    //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
    //  jerk for a given set of u variable.
    //
    //  Inputs :
    //    ud_vec      : [ 1 x M ] The vector of first derivative of u
    //    udd_vec     : [ 1 x M ] The vector of second derivative of ddu
    //    uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
    //    r0D         : [ 1 x M ] The vector of r
    //    r1D         : [ 1 x M ] The vector of first derivative of r
    //    r2D         : [ 1 x M ] The vector of second derivative of r
    //    r3D         : [ 1 x M ] The vector of second derivative of r
    //
    //  Outputs :
    //    R           : [ N x M ] pose
    //    V           : [ N x M ] velocity
    //    A           : [ N x M ] acceleration
    //    J           : [ N x M ] jerk
    //
    // 'calcRVAJfromUWithoutCurv:21' R = r0D;
    // 'calcRVAJfromUWithoutCurv:22' V = r1D .* ud_vec;
    if (r1D.size(1) == ud_vec.size(1)) {
        int i_loop_ub;
        V.set_size(r1D.size(0), r1D.size(1));
        i_loop_ub = r1D.size(1);
        for (int i8{0}; i8 < i_loop_ub; i8++) {
            int k_loop_ub;
            int scalarLB;
            int vectorUB;
            k_loop_ub = r1D.size(0);
            scalarLB = (r1D.size(0) / 2) << 1;
            vectorUB = scalarLB - 2;
            for (int i10{0}; i10 <= vectorUB; i10 += 2) {
                __m128d r1;
                r1 = _mm_loadu_pd(&r1D[i10 + r1D.size(0) * i8]);
                _mm_storeu_pd(&V[i10 + V.size(0) * i8], _mm_mul_pd(r1, _mm_set1_pd(ud_vec[i8])));
            }
            for (int i10{scalarLB}; i10 < k_loop_ub; i10++) {
                V[i10 + V.size(0) * i8] = r1D[i10 + r1D.size(0) * i8] * ud_vec[i8];
            }
        }
    } else {
        b_times(V, r1D, ud_vec);
    }
    // 'calcRVAJfromUWithoutCurv:23' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
    r.set_size(1, ud_vec.size(1));
    j_loop_ub = ud_vec.size(1);
    for (int i9{0}; i9 < j_loop_ub; i9++) {
        double varargin_1;
        varargin_1 = ud_vec[i9];
        r[i9] = std::pow(varargin_1, 2.0);
    }
    if (r2D.size(1) == 1) {
        i11 = r.size(1);
    } else {
        i11 = r2D.size(1);
    }
    if (r1D.size(1) == 1) {
        i12 = udd_vec.size(1);
    } else {
        i12 = r1D.size(1);
    }
    if ((r2D.size(1) == r.size(1)) && (r1D.size(1) == udd_vec.size(1)) &&
        (r2D.size(0) == r1D.size(0)) && (i11 == i12)) {
        int l_loop_ub;
        A.set_size(r2D.size(0), r2D.size(1));
        l_loop_ub = r2D.size(1);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            int b_scalarLB;
            int b_vectorUB;
            int n_loop_ub;
            n_loop_ub = r2D.size(0);
            b_scalarLB = (r2D.size(0) / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (int i15{0}; i15 <= b_vectorUB; i15 += 2) {
                __m128d r2;
                __m128d r3;
                r2 = _mm_loadu_pd(&r2D[i15 + r2D.size(0) * i13]);
                r3 = _mm_loadu_pd(&r1D[i15 + r1D.size(0) * i13]);
                _mm_storeu_pd(&A[i15 + A.size(0) * i13],
                              _mm_add_pd(_mm_mul_pd(r2, _mm_set1_pd(r[i13])),
                                         _mm_mul_pd(r3, _mm_set1_pd(udd_vec[i13]))));
            }
            for (int i15{b_scalarLB}; i15 < n_loop_ub; i15++) {
                A[i15 + A.size(0) * i13] = r2D[i15 + r2D.size(0) * i13] * r[i13] +
                                           r1D[i15 + r1D.size(0) * i13] * udd_vec[i13];
            }
        }
    } else {
        binary_expand_op(A, r2D, r, r1D, udd_vec);
    }
    // 'calcRVAJfromUWithoutCurv:24' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
    // uddd_vec;
    r.set_size(1, ud_vec.size(1));
    m_loop_ub = ud_vec.size(1);
    for (int i14{0}; i14 < m_loop_ub; i14++) {
        double b_varargin_1;
        b_varargin_1 = ud_vec[i14];
        r[i14] = std::pow(b_varargin_1, 3.0);
    }
    if (r2D.size(1) == 1) {
        i16 = ud_vec.size(1);
    } else {
        i16 = r2D.size(1);
    }
    if (r3D.size(1) == 1) {
        i17 = r.size(1);
    } else {
        i17 = r3D.size(1);
    }
    if (r2D.size(1) == 1) {
        i18 = ud_vec.size(1);
    } else {
        i18 = r2D.size(1);
    }
    if (i18 == 1) {
        i19 = udd_vec.size(1);
    } else if (r2D.size(1) == 1) {
        i19 = ud_vec.size(1);
    } else {
        i19 = r2D.size(1);
    }
    if (r3D.size(0) == 1) {
        i20 = r2D.size(0);
    } else {
        i20 = r3D.size(0);
    }
    if (r3D.size(1) == 1) {
        i21 = r.size(1);
    } else {
        i21 = r3D.size(1);
    }
    if (r2D.size(1) == 1) {
        i22 = ud_vec.size(1);
    } else {
        i22 = r2D.size(1);
    }
    if (i21 == 1) {
        if (i22 == 1) {
            i23 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i23 = ud_vec.size(1);
        } else {
            i23 = r2D.size(1);
        }
    } else if (r3D.size(1) == 1) {
        i23 = r.size(1);
    } else {
        i23 = r3D.size(1);
    }
    if (r1D.size(1) == 1) {
        i24 = uddd_vec.size(1);
    } else {
        i24 = r1D.size(1);
    }
    if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud_vec.size(1)) && (i16 == udd_vec.size(1)) &&
        (r3D.size(0) == r2D.size(0)) && (i17 == i19) && (r1D.size(1) == uddd_vec.size(1)) &&
        (i20 == r1D.size(0)) && (i23 == i24)) {
        int o_loop_ub;
        J.set_size(r3D.size(0), r3D.size(1));
        o_loop_ub = r3D.size(1);
        for (int i25{0}; i25 < o_loop_ub; i25++) {
            int c_scalarLB;
            int c_vectorUB;
            int p_loop_ub;
            p_loop_ub = r3D.size(0);
            c_scalarLB = (r3D.size(0) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (int i26{0}; i26 <= c_vectorUB; i26 += 2) {
                __m128d r4;
                __m128d r5;
                __m128d r6;
                r4 = _mm_loadu_pd(&r3D[i26 + r3D.size(0) * i25]);
                r5 = _mm_loadu_pd(&r2D[i26 + r2D.size(0) * i25]);
                r6 = _mm_loadu_pd(&r1D[i26 + r1D.size(0) * i25]);
                _mm_storeu_pd(
                    &J[i26 + J.size(0) * i25],
                    _mm_add_pd(_mm_add_pd(_mm_mul_pd(r4, _mm_set1_pd(r[i25])),
                                          _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r5),
                                                                _mm_set1_pd(ud_vec[i25])),
                                                     _mm_set1_pd(udd_vec[i25]))),
                               _mm_mul_pd(r6, _mm_set1_pd(uddd_vec[i25]))));
            }
            for (int i26{c_scalarLB}; i26 < p_loop_ub; i26++) {
                J[i26 + J.size(0) * i25] =
                    (r3D[i26 + r3D.size(0) * i25] * r[i25] +
                     3.0 * r2D[i26 + r2D.size(0) * i25] * ud_vec[i25] * udd_vec[i25]) +
                    r1D[i26 + r1D.size(0) * i25] * uddd_vec[i25];
            }
        }
    } else {
        binary_expand_op(J, r3D, r, r2D, ud_vec, udd_vec, r1D, uddd_vec);
    }
}

} // namespace ocn

//
// File trailer for calcRVAJfromU.cpp
//
// [EOF]
//
