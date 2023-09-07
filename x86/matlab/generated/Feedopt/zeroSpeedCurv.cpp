//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:21:23
//

// Include Files
#include "zeroSpeedCurv.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void d_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
                               const double in3_data[], const int *in3_size);

static void times(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                  const ::coder::array<double, 2U> &in3);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const double in3_data[]
//                const int *in3_size
// Return Type  : void
//
namespace ocn {
static void d_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
                               const double in3_data[], const int *in3_size)
{
    int b_in3_idx_0;
    int in3_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    in3_idx_0 = *in3_size;
    if (in3_idx_0 == 1) {
        b_in3_idx_0 = in2.size(0);
    } else {
        b_in3_idx_0 = in3_idx_0;
    }
    in1.set_size(b_in3_idx_0, in2.size(1));
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in3_idx_0 != 1);
    loop_ub = in2.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (in3_idx_0 == 1) {
            b_loop_ub = in2.size(0);
        } else {
            b_loop_ub = in3_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            in1[i1 + in1.size(0) * i] =
                (in2[i1 * stride_0_0 + in2.size(0) * i] > in3_data[i1 * stride_1_0]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
static void times(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                  const ::coder::array<double, 2U> &in3)
{
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (in3.size(1) == 1) {
        i = in2.size(1);
    } else {
        i = in3.size(1);
    }
    in1.set_size(1, i);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    if (in3.size(1) == 1) {
        loop_ub = in2.size(1);
    } else {
        loop_ub = in3.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[i1] = in2[i1 * stride_0_1] * in3[i1 * stride_1_1];
    }
}

//
// function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
//
// zeroSpeedCurv : Compute the profile paramater u in case of zero start /
//  stop. This approach assumes a constant pseudo jerk. The resulting profile
//  will respect the velocity, acceleration and jerk constraints.
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//  Outputs :
//    u       : Resulting U for constant jerk
//    jps     : Resulting Pseudo jerk
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
//                const double ctx_cfg_amax[6]
//                const double ctx_cfg_jmax[6]
//                double ctx_cfg_dt
//                Kinematics *ctx_kin
//                const CurvStruct *curv
//                ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &ud
//                ::coder::array<double, 2U> &udd
//                double *jps
// Return Type  : void
//
void b_zeroSpeedCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                     const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6], double ctx_cfg_dt,
                     Kinematics *ctx_kin, const CurvStruct *curv, ::coder::array<double, 2U> &u,
                     ::coder::array<double, 2U> &ud, ::coder::array<double, 2U> &udd, double *jps)
{
    Kinematics b_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r19;
    ::coder::array<double, 2U> r21;
    ::coder::array<double, 2U> r24;
    ::coder::array<double, 2U> r27;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> xv;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    double amax_data[6];
    double ctx_cfg_jmax_data[6];
    double jmax_data[6];
    double vmax_data[6];
    double a_delta;
    double b_fmax;
    double b_jps;
    double b_k;
    double f_delta;
    double j_delta;
    double k_tmp;
    double v_delta;
    int ctx_cfg_jmax_size[2];
    unsigned int uv[2];
    int b_end;
    int b_iindx;
    int b_scalarLB;
    int b_trueCount;
    int b_vectorUB;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int end;
    int end_tmp;
    int f_loop_ub;
    int g_loop_ub;
    int g_scalarLB;
    int g_vectorUB;
    int h_loop_ub;
    int h_scalarLB;
    int h_vectorUB;
    int iindx;
    int j_loop_ub;
    int k_loop_ub;
    int lb_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int q_loop_ub;
    int scalarLB;
    int trueCount;
    int vectorUB;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:15' uk = 1 - uk ;
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    e_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:19' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
    ctx_kin->set_tool_length(curv->tool.offset.z);
    // 'zeroSpeedCurv:21' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:22' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:26' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    z1.set_size(r1D.size(0));
    if (r1D.size(0) != 0) {
        int i1;
        i1 = r1D.size(0);
        for (int k{0}; k < i1; k++) {
            z1[k] = std::abs(r1D[k]);
        }
    }
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i2{0}; i2 < trueCount; i2++) {
        ctx_cfg_jmax_data[i2] = ctx_cfg_jmax[tmp_data[i2] - 1];
    }
    b_jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) /
            coder::internal::maximum(z1);
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:31' searchJps = true;
    // 'zeroSpeedCurv:33' ind = 0;
    // 'zeroSpeedCurv:34' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    searchJps = true;
    while (searchJps) {
        double b_k_tmp;
        double c_jps;
        double c_k;
        int b_partialTrueCount;
        int bb_loop_ub;
        int c_end;
        int c_partialTrueCount;
        int c_scalarLB;
        int c_vectorUB;
        int d_end;
        int d_partialTrueCount;
        int e_scalarLB;
        int e_vectorUB;
        int eb_loop_ub;
        int f_k;
        int f_scalarLB;
        int f_vectorUB;
        int hi;
        int i30;
        int i31;
        int i35;
        int i36;
        int i37;
        int i38;
        int i39;
        int i40;
        int i41;
        int i42;
        int i43;
        int i_loop_ub;
        int i_scalarLB;
        int i_vectorUB;
        int j_scalarLB;
        int j_vectorUB;
        int kb_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int nb_loop_ub;
        int o_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:35' ind = ind + 1;
        // 'zeroSpeedCurv:36' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:50' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        b_k_tmp = std::pow(6.0 / b_jps, 0.33333333333333331);
        c_k = b_k_tmp / ctx_cfg_dt;
        // 'zeroSpeedCurv:52' if( k > 0 )
        if (c_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:53' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(c_k) + 1);
            c_loop_ub = static_cast<int>(c_k);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:54' if( k_vec( end ) < k )
            if (static_cast<int>(c_k) < c_k) {
                int e_loop_ub;
                // 'zeroSpeedCurv:54' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(c_k) + 2);
                e_loop_ub = static_cast<int>(c_k);
                for (int i6{0}; i6 <= e_loop_ub; i6++) {
                    k_vec[i6] = i6;
                }
                k_vec[static_cast<int>(c_k) + 1] = c_k;
            }
        } else {
            // 'zeroSpeedCurv:55' else
            // 'zeroSpeedCurv:56' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:37' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
        c_jps = b_jps;
        //  calc_u : Calcule u for a given pseudo jerk. U is assured to give velocity,
        //  acceleration and jerk below the provided limits.
        //  Inputs :
        //    isEnd : ( Boolean ) is the end of the curve.
        //    searchJps : ( Boolean ) is searching a Jps
        //    jps   : The constant pseudo jerk
        //    ctx   : The context
        //    curv  : The curve
        //    k_vec : The vector of index
        //  Outputs :
        //    searchU : ( Boolean ) is searching a U
        //    jps : The constant pseudo jerk
        //    u : The resulting u
        // 'zeroSpeedCurv:77' if( isempty( ratio ) )
        // 'zeroSpeedCurv:79' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //  Inputs :
        //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
        //    k_vec      :  [ 1 x M ] The time vector
        //    isEnd      :  ( Boolean ) Is the end of the Curve.
        //    a          :  Curve parameter a for affine transforme
        //    b          :  Curve parameter b for affine transforme
        //  Outputs :
        //    u          :  [ N x M ]
        //    ud         :  [ N x M ]
        //    udd        :  [ N x M ]
        //    uddd       :  [ N x M ]
        // 'constJerkU:16' if( coder.target( "MATLAB" ) )
        // 'constJerkU:22' if( isEnd )
        // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
        // 'constJerkU:24' k_vec  = k_max - k_vec;
        y.set_size(1, k_vec.size(1));
        i_loop_ub = k_vec.size(1);
        c_scalarLB = (k_vec.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i10{0}; i10 <= c_vectorUB; i10 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&k_vec[i10]);
            _mm_storeu_pd(
                &y[i10], _mm_sub_pd(_mm_set1_pd(b_k_tmp), _mm_mul_pd(r3, _mm_set1_pd(ctx_cfg_dt))));
        }
        for (int i10{c_scalarLB}; i10 < i_loop_ub; i10++) {
            y[i10] = b_k_tmp - k_vec[i10] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[0] = 1U;
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r1.set_size(1, y.size(1));
        l_loop_ub = y.size(1);
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            double c_varargin_1;
            c_varargin_1 = y[i12];
            r1[i12] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r1.size(1));
        m_loop_ub = r1.size(1);
        e_scalarLB = (r1.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i14{0}; i14 <= e_vectorUB; i14 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r1[i14]);
            _mm_storeu_pd(&ud[i14],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(2.0)));
        }
        for (int i14{e_scalarLB}; i14 < m_loop_ub; i14++) {
            ud[i14] = b_jps * r1[i14] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r1.set_size(1, y.size(1));
        n_loop_ub = y.size(1);
        for (int i15{0}; i15 < n_loop_ub; i15++) {
            double d_varargin_1;
            d_varargin_1 = y[i15];
            r1[i15] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r1.size(1));
        o_loop_ub = r1.size(1);
        f_scalarLB = (r1.size(1) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (int i16{0}; i16 <= f_vectorUB; i16 += 2) {
            __m128d r6;
            r6 = _mm_loadu_pd(&r1[i16]);
            _mm_storeu_pd(&u[i16],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r6), _mm_set1_pd(6.0)));
        }
        for (int i16{f_scalarLB}; i16 < o_loop_ub; i16++) {
            u[i16] = b_jps * r1[i16] / 6.0;
        }
        // 'constJerkU:33' u( u > 1 ) = 1;
        c_end = u.size(1);
        for (int e_i{0}; e_i < c_end; e_i++) {
            if (u[e_i] > 1.0) {
                u[e_i] = 1.0;
            }
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        d_end = u.size(1);
        for (int f_i{0}; f_i < d_end; f_i++) {
            if (u[f_i] < 0.0) {
                u[f_i] = 0.0;
            }
        }
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        u.set_size(1, u.size(1));
        r_loop_ub = u.size(1);
        i_scalarLB = (u.size(1) / 2) << 1;
        i_vectorUB = i_scalarLB - 2;
        for (int i19{0}; i19 <= i_vectorUB; i19 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&u[i19]);
            _mm_storeu_pd(&u[i19], _mm_sub_pd(_mm_set1_pd(1.0), r9));
        }
        for (int i19{i_scalarLB}; i19 < r_loop_ub; i19++) {
            u[i19] = 1.0 - u[i19];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:81' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        s_loop_ub = y.size(1);
        j_scalarLB = (y.size(1) / 2) << 1;
        j_vectorUB = j_scalarLB - 2;
        for (int i20{0}; i20 <= j_vectorUB; i20 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&y[i20]);
            _mm_storeu_pd(&udd_vec[i20],
                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r10), _mm_set1_pd(-1.0)));
        }
        for (int i20{j_scalarLB}; i20 < s_loop_ub; i20++) {
            udd_vec[i20] = -(b_jps * y[i20]);
        }
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ctx     : The context
        //    Curv    : The curve struct
        //    u_vec   : [ 1 x M ] The vector of u
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromU:17' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' ctx.kin = ctx.kin.set_tool_length(curv.tool.offset.z);
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'calcRVAJfromU:21' if( curv.Info.TRAFO )
        if (curv->Info.TRAFO) {
            int t_loop_ub;
            int v_loop_ub;
            int x_loop_ub;
            // 'calcRVAJfromU:22' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            t_loop_ub = c_r1D.size(1) - 1;
            for (int i21{0}; i21 <= t_loop_ub; i21++) {
                int u_loop_ub;
                u_loop_ub = c_r1D.size(0) - 1;
                for (int i22{0}; i22 <= u_loop_ub; i22++) {
                    d_r1D[i22 + d_r1D.size(0) * i21] = c_r1D[i22 + c_r1D.size(0) * i21];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            v_loop_ub = r2D.size(1) - 1;
            for (int i23{0}; i23 <= v_loop_ub; i23++) {
                int w_loop_ub;
                w_loop_ub = r2D.size(0) - 1;
                for (int i24{0}; i24 <= w_loop_ub; i24++) {
                    b_r2D[i24 + b_r2D.size(0) * i23] = r2D[i24 + r2D.size(0) * i23];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            x_loop_ub = r3D.size(1) - 1;
            for (int i25{0}; i25 <= x_loop_ub; i25++) {
                int y_loop_ub;
                y_loop_ub = r3D.size(0) - 1;
                for (int i26{0}; i26 <= y_loop_ub; i26++) {
                    b_r3D[i26 + b_r3D.size(0) * i25] = r3D[i26 + r3D.size(0) * i25];
                }
            }
            b_ctx_kin.joint(b_r0D, d_r1D, b_r2D, b_r3D, a__1, c_r1D, r2D, r3D);
        }
        // 'calcRVAJfromU:25' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
        // 'calcRVAJfromU:26'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
        //    r0D     : [ 1 x M ] The vector of r
        //    r1D     : [ 1 x M ] The vector of first derivative of r
        //    r2D     : [ 1 x M ] The vector of second derivative of r
        //    r3D     : [ 1 x M ] The vector of second derivative of r
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromUWithoutCurv:18' R = r0D;
        // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
        if (c_r1D.size(1) == ud.size(1)) {
            int ab_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            ab_loop_ub = c_r1D.size(1);
            for (int i27{0}; i27 < ab_loop_ub; i27++) {
                int cb_loop_ub;
                int k_scalarLB;
                int k_vectorUB;
                cb_loop_ub = c_r1D.size(0);
                k_scalarLB = (c_r1D.size(0) / 2) << 1;
                k_vectorUB = k_scalarLB - 2;
                for (int i29{0}; i29 <= k_vectorUB; i29 += 2) {
                    __m128d r11;
                    r11 = _mm_loadu_pd(&c_r1D[i29 + c_r1D.size(0) * i27]);
                    _mm_storeu_pd(&V[i29 + V.size(0) * i27], _mm_mul_pd(r11, _mm_set1_pd(ud[i27])));
                }
                for (int i29{k_scalarLB}; i29 < cb_loop_ub; i29++) {
                    V[i29 + V.size(0) * i27] = c_r1D[i29 + c_r1D.size(0) * i27] * ud[i27];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r1.set_size(1, ud.size(1));
        bb_loop_ub = ud.size(1);
        for (int i28{0}; i28 < bb_loop_ub; i28++) {
            double e_varargin_1;
            e_varargin_1 = ud[i28];
            r1[i28] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i30 = r1.size(1);
        } else {
            i30 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i31 = udd_vec.size(1);
        } else {
            i31 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r1.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i30 == i31)) {
            int db_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            db_loop_ub = r2D.size(1);
            for (int i32{0}; i32 < db_loop_ub; i32++) {
                int fb_loop_ub;
                int l_scalarLB;
                int l_vectorUB;
                fb_loop_ub = r2D.size(0);
                l_scalarLB = (r2D.size(0) / 2) << 1;
                l_vectorUB = l_scalarLB - 2;
                for (int i34{0}; i34 <= l_vectorUB; i34 += 2) {
                    __m128d r12;
                    __m128d r13;
                    r12 = _mm_loadu_pd(&r2D[i34 + r2D.size(0) * i32]);
                    r13 = _mm_loadu_pd(&c_r1D[i34 + c_r1D.size(0) * i32]);
                    _mm_storeu_pd(&A[i34 + A.size(0) * i32],
                                  _mm_add_pd(_mm_mul_pd(r12, _mm_set1_pd(r1[i32])),
                                             _mm_mul_pd(r13, _mm_set1_pd(udd_vec[i32]))));
                }
                for (int i34{l_scalarLB}; i34 < fb_loop_ub; i34++) {
                    A[i34 + A.size(0) * i32] = r2D[i34 + r2D.size(0) * i32] * r1[i32] +
                                               c_r1D[i34 + c_r1D.size(0) * i32] * udd_vec[i32];
                }
            }
        } else {
            binary_expand_op(A, r2D, r1, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r1.set_size(1, ud.size(1));
        eb_loop_ub = ud.size(1);
        for (int i33{0}; i33 < eb_loop_ub; i33++) {
            double f_varargin_1;
            f_varargin_1 = ud[i33];
            r1[i33] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i35 = ud.size(1);
        } else {
            i35 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i36 = r1.size(1);
        } else {
            i36 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i37 = ud.size(1);
        } else {
            i37 = r2D.size(1);
        }
        if (i37 == 1) {
            i38 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i38 = ud.size(1);
        } else {
            i38 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i39 = r2D.size(0);
        } else {
            i39 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i40 = r1.size(1);
        } else {
            i40 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i41 = ud.size(1);
        } else {
            i41 = r2D.size(1);
        }
        if (i40 == 1) {
            if (i41 == 1) {
                i42 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i42 = ud.size(1);
            } else {
                i42 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i42 = r1.size(1);
        } else {
            i42 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i43 = y.size(1);
        } else {
            i43 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i35 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i36 == i38) &&
            (c_r1D.size(1) == y.size(1)) && (i39 == c_r1D.size(0)) && (i42 == i43)) {
            int gb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            gb_loop_ub = r3D.size(1);
            for (int i44{0}; i44 < gb_loop_ub; i44++) {
                int hb_loop_ub;
                int m_scalarLB;
                int m_vectorUB;
                hb_loop_ub = r3D.size(0);
                m_scalarLB = (r3D.size(0) / 2) << 1;
                m_vectorUB = m_scalarLB - 2;
                for (int i45{0}; i45 <= m_vectorUB; i45 += 2) {
                    __m128d r14;
                    __m128d r15;
                    __m128d r16;
                    r14 = _mm_loadu_pd(&r3D[i45 + r3D.size(0) * i44]);
                    r15 = _mm_loadu_pd(&r2D[i45 + r2D.size(0) * i44]);
                    r16 = _mm_loadu_pd(&c_r1D[i45 + c_r1D.size(0) * i44]);
                    _mm_storeu_pd(
                        &J[i45 + J.size(0) * i44],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r14, _mm_set1_pd(r1[i44])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r15),
                                                             _mm_set1_pd(ud[i44])),
                                                  _mm_set1_pd(udd_vec[i44]))),
                            _mm_mul_pd(r16, _mm_set1_pd(b_jps))));
                }
                for (int i45{m_scalarLB}; i45 < hb_loop_ub; i45++) {
                    J[i45 + J.size(0) * i44] =
                        (r3D[i45 + r3D.size(0) * i44] * r1[i44] +
                         3.0 * r2D[i45 + r2D.size(0) * i44] * ud[i44] * udd_vec[i44]) +
                        c_r1D[i45 + c_r1D.size(0) * i44] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r1, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:83' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:85' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'zeroSpeedCurv:87' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int ib_loop_ub;
            // 'zeroSpeedCurv:89' else
            // 'zeroSpeedCurv:90' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            ib_loop_ub = c_r1D.size(1) - 1;
            for (int i46{0}; i46 <= ib_loop_ub; i46++) {
                int jb_loop_ub;
                jb_loop_ub = c_r1D.size(0) - 1;
                for (int i47{0}; i47 <= jb_loop_ub; i47++) {
                    e_r1D[i47 + e_r1D.size(0) * i46] = c_r1D[i47 + c_r1D.size(0) * i46];
                }
            }
            b_ctx_kin.v_relative(b_r0D, e_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:88' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:93' safetyFactor = 0.5;
        // 'zeroSpeedCurv:94' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:95' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i48{0}; i48 < b_trueCount; i48++) {
            vmax_data[i48] = ctx_cfg_vmax[b_tmp_data[i48] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:96' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int h_i{0}; h_i <= end_tmp; h_i++) {
            if (ctx_cfg_maskTot_data[h_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(h_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i49{0}; i49 < c_trueCount; i49++) {
            amax_data[i49] = ctx_cfg_amax[c_tmp_data[i49] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:97' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int i_i{0}; i_i <= end_tmp; i_i++) {
            if (ctx_cfg_maskTot_data[i_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(i_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i50{0}; i50 < d_trueCount; i50++) {
            jmax_data[i50] = ctx_cfg_jmax[d_tmp_data[i50] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        kb_loop_ub = c_r1D.size(1);
        for (int i51{0}; i51 < kb_loop_ub; i51++) {
            y[i51] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            lb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int d_k{0}; d_k <= hi; d_k++) {
            xv.set_size(outsize_idx_0);
            for (int i52{0}; i52 < lb_loop_ub; i52++) {
                xv[i52] = 0.0;
            }
            for (int e_k{0}; e_k < nx; e_k++) {
                xv[e_k] = c_r1D[(ctx_cfg_indCart[e_k] + c_r1D.size(0) * d_k) - 1];
            }
            y[d_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int mb_loop_ub;
            int n_scalarLB;
            int n_vectorUB;
            feed.set_size(1, y.size(1));
            mb_loop_ub = y.size(1);
            n_scalarLB = (y.size(1) / 2) << 1;
            n_vectorUB = n_scalarLB - 2;
            for (int i53{0}; i53 <= n_vectorUB; i53 += 2) {
                __m128d r17;
                __m128d r18;
                r17 = _mm_loadu_pd(&y[i53]);
                r18 = _mm_loadu_pd(&ud[i53]);
                _mm_storeu_pd(&feed[i53], _mm_mul_pd(r17, r18));
            }
            for (int i53{n_scalarLB}; i53 < mb_loop_ub; i53++) {
                feed[i53] = y[i53] * ud[i53];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:101' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        nb_loop_ub = feed.size(1);
        for (int i54{0}; i54 < nb_loop_ub; i54++) {
            x[i54] = (feed[i54] > b_fmax);
        }
        b_y = false;
        f_k = 0;
        exitg1 = false;
        while ((!exitg1) && (f_k <= x.size(1) - 1)) {
            if (x[f_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                f_k++;
            }
        }
        if (b_y) {
            int o_scalarLB;
            int o_vectorUB;
            int ob_loop_ub;
            // 'zeroSpeedCurv:102' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            ob_loop_ub = feed.size(1);
            o_scalarLB = (feed.size(1) / 2) << 1;
            o_vectorUB = o_scalarLB - 2;
            for (int i56{0}; i56 <= o_vectorUB; i56 += 2) {
                __m128d r20;
                r20 = _mm_loadu_pd(&feed[i56]);
                _mm_storeu_pd(&b_feed[i56], _mm_sub_pd(r20, _mm_set1_pd(b_fmax)));
            }
            for (int i56{o_scalarLB}; i56 < ob_loop_ub; i56++) {
                b_feed[i56] = feed[i56] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:103' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r19.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i55;
                i55 = V.size(1);
                for (int g_k{0}; g_k < i55; g_k++) {
                    int i57;
                    i57 = r19.size(0);
                    for (int h_k{0}; h_k < i57; h_k++) {
                        r19[h_k + r19.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r19.size(0) == b_trueCount) {
                int pb_loop_ub;
                b_x.set_size(r19.size(0), r19.size(1));
                pb_loop_ub = r19.size(1);
                for (int i58{0}; i58 < pb_loop_ub; i58++) {
                    int qb_loop_ub;
                    qb_loop_ub = r19.size(0);
                    for (int i59{0}; i59 < qb_loop_ub; i59++) {
                        b_x[i59 + b_x.size(0) * i58] =
                            (r19[i59 + r19.size(0) * i58] > vmax_data[i59]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r19, vmax_data, &b_trueCount);
            }
            c_y = false;
            i_k = 0;
            exitg1 = false;
            while ((!exitg1) && (i_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[i_k]) {
                    c_y = true;
                    exitg1 = true;
                } else {
                    i_k++;
                }
            }
            if (c_y) {
                // 'zeroSpeedCurv:104' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:105' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r19.size(0) == b_trueCount) {
                    int rb_loop_ub;
                    int ub_loop_ub;
                    r21.set_size(r19.size(0), r19.size(1));
                    rb_loop_ub = r19.size(1);
                    for (int i61{0}; i61 < rb_loop_ub; i61++) {
                        int p_scalarLB;
                        int p_vectorUB;
                        int tb_loop_ub;
                        tb_loop_ub = r19.size(0);
                        p_scalarLB = (r19.size(0) / 2) << 1;
                        p_vectorUB = p_scalarLB - 2;
                        for (int i66{0}; i66 <= p_vectorUB; i66 += 2) {
                            __m128d r22;
                            __m128d r23;
                            r22 = _mm_loadu_pd(&r19[i66 + r19.size(0) * i61]);
                            r23 = _mm_loadu_pd(&vmax_data[i66]);
                            _mm_storeu_pd(&r21[i66 + r21.size(0) * i61], _mm_sub_pd(r22, r23));
                        }
                        for (int i66{p_scalarLB}; i66 < tb_loop_ub; i66++) {
                            r21[i66 + r21.size(0) * i61] =
                                r19[i66 + r19.size(0) * i61] - vmax_data[i66];
                        }
                    }
                    r19.set_size(r21.size(0), r21.size(1));
                    ub_loop_ub = r21.size(1);
                    for (int i64{0}; i64 < ub_loop_ub; i64++) {
                        int wb_loop_ub;
                        wb_loop_ub = r21.size(0);
                        for (int i67{0}; i67 < wb_loop_ub; i67++) {
                            r19[i67 + r19.size(0) * i64] = r21[i67 + r21.size(0) * i64];
                        }
                    }
                    coder::internal::b_maximum(r19, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r19, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:106' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                r19.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i60;
                    i60 = A.size(1);
                    for (int j_k{0}; j_k < i60; j_k++) {
                        int i62;
                        i62 = r19.size(0);
                        for (int k_k{0}; k_k < i62; k_k++) {
                            r19[k_k + r19.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r19.size(0) == c_trueCount) {
                    int sb_loop_ub;
                    b_x.set_size(r19.size(0), r19.size(1));
                    sb_loop_ub = r19.size(1);
                    for (int i63{0}; i63 < sb_loop_ub; i63++) {
                        int vb_loop_ub;
                        vb_loop_ub = r19.size(0);
                        for (int i65{0}; i65 < vb_loop_ub; i65++) {
                            b_x[i65 + b_x.size(0) * i63] =
                                (r19[i65 + r19.size(0) * i63] > amax_data[i65]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r19, amax_data, &c_trueCount);
                }
                d_y = false;
                l_k = 0;
                exitg1 = false;
                while ((!exitg1) && (l_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[l_k]) {
                        d_y = true;
                        exitg1 = true;
                    } else {
                        l_k++;
                    }
                }
                if (d_y) {
                    // 'zeroSpeedCurv:107' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:108' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r19.size(0) == c_trueCount) {
                        int bc_loop_ub;
                        int xb_loop_ub;
                        r24.set_size(r19.size(0), r19.size(1));
                        xb_loop_ub = r19.size(1);
                        for (int i69{0}; i69 < xb_loop_ub; i69++) {
                            int ac_loop_ub;
                            int q_scalarLB;
                            int q_vectorUB;
                            ac_loop_ub = r19.size(0);
                            q_scalarLB = (r19.size(0) / 2) << 1;
                            q_vectorUB = q_scalarLB - 2;
                            for (int i74{0}; i74 <= q_vectorUB; i74 += 2) {
                                __m128d r25;
                                __m128d r26;
                                r25 = _mm_loadu_pd(&r19[i74 + r19.size(0) * i69]);
                                r26 = _mm_loadu_pd(&amax_data[i74]);
                                _mm_storeu_pd(&r24[i74 + r24.size(0) * i69], _mm_sub_pd(r25, r26));
                            }
                            for (int i74{q_scalarLB}; i74 < ac_loop_ub; i74++) {
                                r24[i74 + r24.size(0) * i69] =
                                    r19[i74 + r19.size(0) * i69] - amax_data[i74];
                            }
                        }
                        r19.set_size(r24.size(0), r24.size(1));
                        bc_loop_ub = r24.size(1);
                        for (int i72{0}; i72 < bc_loop_ub; i72++) {
                            int dc_loop_ub;
                            dc_loop_ub = r24.size(0);
                            for (int i75{0}; i75 < dc_loop_ub; i75++) {
                                r19[i75 + r19.size(0) * i72] = r24[i75 + r24.size(0) * i72];
                            }
                        }
                        coder::internal::b_maximum(r19, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r19, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:109' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    r19.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i68;
                        i68 = J.size(1);
                        for (int m_k{0}; m_k < i68; m_k++) {
                            int i70;
                            i70 = r19.size(0);
                            for (int n_k{0}; n_k < i70; n_k++) {
                                r19[n_k + r19.size(0) * m_k] = std::abs(J[n_k + J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r19.size(0) == d_trueCount) {
                        int yb_loop_ub;
                        b_x.set_size(r19.size(0), r19.size(1));
                        yb_loop_ub = r19.size(1);
                        for (int i71{0}; i71 < yb_loop_ub; i71++) {
                            int cc_loop_ub;
                            cc_loop_ub = r19.size(0);
                            for (int i73{0}; i73 < cc_loop_ub; i73++) {
                                b_x[i73 + b_x.size(0) * i71] =
                                    (r19[i73 + r19.size(0) * i71] > jmax_data[i73]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r19, jmax_data, &d_trueCount);
                    }
                    e_y = false;
                    o_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (o_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[o_k]) {
                            e_y = true;
                            exitg1 = true;
                        } else {
                            o_k++;
                        }
                    }
                    if (e_y) {
                        // 'zeroSpeedCurv:110' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:111' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r19.size(0) == d_trueCount) {
                            int ec_loop_ub;
                            int gc_loop_ub;
                            r27.set_size(r19.size(0), r19.size(1));
                            ec_loop_ub = r19.size(1);
                            for (int i76{0}; i76 < ec_loop_ub; i76++) {
                                int fc_loop_ub;
                                int r_scalarLB;
                                int r_vectorUB;
                                fc_loop_ub = r19.size(0);
                                r_scalarLB = (r19.size(0) / 2) << 1;
                                r_vectorUB = r_scalarLB - 2;
                                for (int i78{0}; i78 <= r_vectorUB; i78 += 2) {
                                    __m128d r28;
                                    __m128d r29;
                                    r28 = _mm_loadu_pd(&r19[i78 + r19.size(0) * i76]);
                                    r29 = _mm_loadu_pd(&jmax_data[i78]);
                                    _mm_storeu_pd(&r27[i78 + r27.size(0) * i76],
                                                  _mm_sub_pd(r28, r29));
                                }
                                for (int i78{r_scalarLB}; i78 < fc_loop_ub; i78++) {
                                    r27[i78 + r27.size(0) * i76] =
                                        r19[i78 + r19.size(0) * i76] - jmax_data[i78];
                                }
                            }
                            r19.set_size(r27.size(0), r27.size(1));
                            gc_loop_ub = r27.size(1);
                            for (int i77{0}; i77 < gc_loop_ub; i77++) {
                                int hc_loop_ub;
                                hc_loop_ub = r27.size(0);
                                for (int i79{0}; i79 < hc_loop_ub; i79++) {
                                    r19[i79 + r19.size(0) * i77] = r27[i79 + r27.size(0) * i77];
                                }
                            }
                            coder::internal::b_maximum(r19, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r19, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:112' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:113' else
                        // 'zeroSpeedCurv:114' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:40' if( coder.target( "MATLAB" ) )
    // 'zeroSpeedCurv:42' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:50' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    k_tmp = std::pow(6.0 / b_jps, 0.33333333333333331);
    b_k = k_tmp / ctx_cfg_dt;
    // 'zeroSpeedCurv:52' if( k > 0 )
    if (b_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:53' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(b_k) + 1);
        b_loop_ub = static_cast<int>(b_k);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:54' if( k_vec( end ) < k )
        if (static_cast<int>(b_k) < b_k) {
            int d_loop_ub;
            // 'zeroSpeedCurv:54' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(b_k) + 2);
            d_loop_ub = static_cast<int>(b_k);
            for (int i5{0}; i5 <= d_loop_ub; i5++) {
                k_vec[i5] = i5;
            }
            k_vec[static_cast<int>(b_k) + 1] = b_k;
        }
    } else {
        // 'zeroSpeedCurv:55' else
        // 'zeroSpeedCurv:56' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:43' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec      :  [ 1 x M ] The time vector
    //    isEnd      :  ( Boolean ) Is the end of the Curve.
    //    a          :  Curve parameter a for affine transforme
    //    b          :  Curve parameter b for affine transforme
    //  Outputs :
    //    u          :  [ N x M ]
    //    ud         :  [ N x M ]
    //    udd        :  [ N x M ]
    //    uddd       :  [ N x M ]
    // 'constJerkU:16' if( coder.target( "MATLAB" ) )
    // 'constJerkU:22' if( isEnd )
    // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    // 'constJerkU:24' k_vec  = k_max - k_vec;
    y.set_size(1, k_vec.size(1));
    f_loop_ub = k_vec.size(1);
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i7{0}; i7 <= vectorUB; i7 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i7]);
        _mm_storeu_pd(&y[i7],
                      _mm_sub_pd(_mm_set1_pd(k_tmp), _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt))));
    }
    for (int i7{scalarLB}; i7 < f_loop_ub; i7++) {
        y[i7] = k_tmp - k_vec[i7] * ctx_cfg_dt;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r1.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    for (int i8{0}; i8 < g_loop_ub; i8++) {
        double varargin_1;
        varargin_1 = y[i8];
        r1[i8] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r1.size(1));
    h_loop_ub = r1.size(1);
    b_scalarLB = (r1.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i9{0}; i9 <= b_vectorUB; i9 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1[i9]);
        _mm_storeu_pd(&ud[i9], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r2), _mm_set1_pd(2.0)));
    }
    for (int i9{b_scalarLB}; i9 < h_loop_ub; i9++) {
        ud[i9] = b_jps * r1[i9] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r1.set_size(1, y.size(1));
    j_loop_ub = y.size(1);
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        double b_varargin_1;
        b_varargin_1 = y[i11];
        r1[i11] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r1.size(1));
    k_loop_ub = r1.size(1);
    d_scalarLB = (r1.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i13{0}; i13 <= d_vectorUB; i13 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r1[i13]);
        _mm_storeu_pd(&u[i13], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(6.0)));
    }
    for (int i13{d_scalarLB}; i13 < k_loop_ub; i13++) {
        u[i13] = b_jps * r1[i13] / 6.0;
    }
    // 'constJerkU:33' u( u > 1 ) = 1;
    end = u.size(1);
    for (int c_i{0}; c_i < end; c_i++) {
        if (u[c_i] > 1.0) {
            u[c_i] = 1.0;
        }
    }
    // 'constJerkU:34' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int d_i{0}; d_i < b_end; d_i++) {
        if (u[d_i] < 0.0) {
            u[d_i] = 0.0;
        }
    }
    // 'constJerkU:36' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:37' u    = 1 - u;
    u.set_size(1, u.size(1));
    p_loop_ub = u.size(1);
    g_scalarLB = (u.size(1) / 2) << 1;
    g_vectorUB = g_scalarLB - 2;
    for (int i17{0}; i17 <= g_vectorUB; i17 += 2) {
        __m128d r7;
        r7 = _mm_loadu_pd(&u[i17]);
        _mm_storeu_pd(&u[i17], _mm_sub_pd(_mm_set1_pd(1.0), r7));
    }
    for (int i17{g_scalarLB}; i17 < p_loop_ub; i17++) {
        u[i17] = 1.0 - u[i17];
    }
    // 'constJerkU:38' ud   = ud;
    // 'constJerkU:39' udd  = -udd;
    udd.set_size(1, y.size(1));
    q_loop_ub = y.size(1);
    h_scalarLB = (y.size(1) / 2) << 1;
    h_vectorUB = h_scalarLB - 2;
    for (int i18{0}; i18 <= h_vectorUB; i18 += 2) {
        __m128d r8;
        r8 = _mm_loadu_pd(&y[i18]);
        _mm_storeu_pd(&udd[i18], _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r8), _mm_set1_pd(-1.0)));
    }
    for (int i18{h_scalarLB}; i18 < q_loop_ub; i18++) {
        udd[i18] = -(b_jps * y[i18]);
    }
    // 'constJerkU:40' uddd = uddd;
    *jps = b_jps;
}

//
// function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
//
// zeroSpeedCurv : Compute the profile paramater u in case of zero start /
//  stop. This approach assumes a constant pseudo jerk. The resulting profile
//  will respect the velocity, acceleration and jerk constraints.
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//  Outputs :
//    u       : Resulting U for constant jerk
//    jps     : Resulting Pseudo jerk
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
//                const double ctx_cfg_amax[6]
//                const double ctx_cfg_jmax[6]
//                double ctx_cfg_dt
//                Kinematics *ctx_kin
//                const CurvStruct *curv
//                ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &ud
//                ::coder::array<double, 2U> &udd
//                double *jps
// Return Type  : void
//
void zeroSpeedCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                   const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                   const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                   const int ctx_cfg_maskRot_size[2],
                   const ::coder::array<int, 1U> &ctx_cfg_indCart,
                   const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                   int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                   const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6], double ctx_cfg_dt,
                   Kinematics *ctx_kin, const CurvStruct *curv, ::coder::array<double, 2U> &u,
                   ::coder::array<double, 2U> &ud, ::coder::array<double, 2U> &udd, double *jps)
{
    Kinematics b_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r17;
    ::coder::array<double, 2U> r19;
    ::coder::array<double, 2U> r22;
    ::coder::array<double, 2U> r25;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> xv;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    double amax_data[6];
    double ctx_cfg_jmax_data[6];
    double jmax_data[6];
    double vmax_data[6];
    double a_delta;
    double b_fmax;
    double b_jps;
    double b_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int ctx_cfg_jmax_size[2];
    unsigned int uv[2];
    int b_end;
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_scalarLB;
    int c_trueCount;
    int c_vectorUB;
    int d_iindx;
    int d_loop_ub;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int end;
    int end_tmp;
    int f_scalarLB;
    int f_vectorUB;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int j_loop_ub;
    int jb_loop_ub;
    int l_loop_ub;
    int n_loop_ub;
    int nx;
    int outsize_idx_0;
    int partialTrueCount;
    int scalarLB;
    int trueCount;
    int vectorUB;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    d_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:19' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
    ctx_kin->set_tool_length(curv->tool.offset.z);
    // 'zeroSpeedCurv:21' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:22' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:26' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    z1.set_size(r1D.size(0));
    if (r1D.size(0) != 0) {
        int i1;
        i1 = r1D.size(0);
        for (int k{0}; k < i1; k++) {
            z1[k] = std::abs(r1D[k]);
        }
    }
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i2{0}; i2 < trueCount; i2++) {
        ctx_cfg_jmax_data[i2] = ctx_cfg_jmax[tmp_data[i2] - 1];
    }
    b_jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) /
            coder::internal::maximum(z1);
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:31' searchJps = true;
    // 'zeroSpeedCurv:33' ind = 0;
    // 'zeroSpeedCurv:34' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    searchJps = true;
    while (searchJps) {
        double c_jps;
        double c_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
        int c_end;
        int c_partialTrueCount;
        int cb_loop_ub;
        int d_end;
        int d_partialTrueCount;
        int e_scalarLB;
        int e_vectorUB;
        int f_k;
        int g_loop_ub;
        int g_scalarLB;
        int g_vectorUB;
        int h_scalarLB;
        int h_vectorUB;
        int hi;
        int i28;
        int i29;
        int i33;
        int i34;
        int i35;
        int i36;
        int i37;
        int i38;
        int i39;
        int i40;
        int i41;
        int ib_loop_ub;
        int k_loop_ub;
        int lb_loop_ub;
        int m_loop_ub;
        int o_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int y_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:35' ind = ind + 1;
        // 'zeroSpeedCurv:36' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:50' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        c_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:52' if( k > 0 )
        if (c_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:53' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(c_k) + 1);
            c_loop_ub = static_cast<int>(c_k);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:54' if( k_vec( end ) < k )
            if (static_cast<int>(c_k) < c_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:54' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(c_k) + 2);
                f_loop_ub = static_cast<int>(c_k);
                for (int i7{0}; i7 <= f_loop_ub; i7++) {
                    k_vec[i7] = i7;
                }
                k_vec[static_cast<int>(c_k) + 1] = c_k;
            }
        } else {
            // 'zeroSpeedCurv:55' else
            // 'zeroSpeedCurv:56' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:37' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
        c_jps = b_jps;
        //  calc_u : Calcule u for a given pseudo jerk. U is assured to give velocity,
        //  acceleration and jerk below the provided limits.
        //  Inputs :
        //    isEnd : ( Boolean ) is the end of the curve.
        //    searchJps : ( Boolean ) is searching a Jps
        //    jps   : The constant pseudo jerk
        //    ctx   : The context
        //    curv  : The curve
        //    k_vec : The vector of index
        //  Outputs :
        //    searchU : ( Boolean ) is searching a U
        //    jps : The constant pseudo jerk
        //    u : The resulting u
        // 'zeroSpeedCurv:77' if( isempty( ratio ) )
        // 'zeroSpeedCurv:79' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
        y.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i8{0}; i8 <= b_vectorUB; i8 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i8]);
            _mm_storeu_pd(&y[i8], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i8{b_scalarLB}; i8 < g_loop_ub; i8++) {
            y[i8] = k_vec[i8] * ctx_cfg_dt;
        }
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //  Inputs :
        //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
        //    k_vec      :  [ 1 x M ] The time vector
        //    isEnd      :  ( Boolean ) Is the end of the Curve.
        //    a          :  Curve parameter a for affine transforme
        //    b          :  Curve parameter b for affine transforme
        //  Outputs :
        //    u          :  [ N x M ]
        //    ud         :  [ N x M ]
        //    udd        :  [ N x M ]
        //    uddd       :  [ N x M ]
        // 'constJerkU:16' if( coder.target( "MATLAB" ) )
        // 'constJerkU:22' if( isEnd )
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[0] = 1U;
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r3.set_size(1, y.size(1));
        k_loop_ub = y.size(1);
        for (int i12{0}; i12 < k_loop_ub; i12++) {
            double b_varargin_1;
            b_varargin_1 = y[i12];
            r3[i12] = std::pow(b_varargin_1, 2.0);
        }
        ud.set_size(1, r3.size(1));
        m_loop_ub = r3.size(1);
        e_scalarLB = (r3.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i14{0}; i14 <= e_vectorUB; i14 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r3[i14]);
            _mm_storeu_pd(&ud[i14],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(2.0)));
        }
        for (int i14{e_scalarLB}; i14 < m_loop_ub; i14++) {
            ud[i14] = b_jps * r3[i14] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r3.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i16{0}; i16 < o_loop_ub; i16++) {
            double d_varargin_1;
            d_varargin_1 = y[i16];
            r3[i16] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r3.size(1));
        p_loop_ub = r3.size(1);
        g_scalarLB = (r3.size(1) / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (int i17{0}; i17 <= g_vectorUB; i17 += 2) {
            __m128d r7;
            r7 = _mm_loadu_pd(&r3[i17]);
            _mm_storeu_pd(&u[i17],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r7), _mm_set1_pd(6.0)));
        }
        for (int i17{g_scalarLB}; i17 < p_loop_ub; i17++) {
            u[i17] = b_jps * r3[i17] / 6.0;
        }
        // 'constJerkU:33' u( u > 1 ) = 1;
        c_end = u.size(1);
        for (int e_i{0}; e_i < c_end; e_i++) {
            if (u[e_i] > 1.0) {
                u[e_i] = 1.0;
            }
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        d_end = u.size(1);
        for (int f_i{0}; f_i < d_end; f_i++) {
            if (u[f_i] < 0.0) {
                u[f_i] = 0.0;
            }
        }
        // 'constJerkU:36' if( isEnd )
        // 'zeroSpeedCurv:81' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        q_loop_ub = y.size(1);
        h_scalarLB = (y.size(1) / 2) << 1;
        h_vectorUB = h_scalarLB - 2;
        for (int i18{0}; i18 <= h_vectorUB; i18 += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&y[i18]);
            _mm_storeu_pd(&udd_vec[i18], _mm_mul_pd(_mm_set1_pd(b_jps), r8));
        }
        for (int i18{h_scalarLB}; i18 < q_loop_ub; i18++) {
            udd_vec[i18] = b_jps * y[i18];
        }
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ctx     : The context
        //    Curv    : The curve struct
        //    u_vec   : [ 1 x M ] The vector of u
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromU:17' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' ctx.kin = ctx.kin.set_tool_length(curv.tool.offset.z);
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'calcRVAJfromU:21' if( curv.Info.TRAFO )
        if (curv->Info.TRAFO) {
            int r_loop_ub;
            int t_loop_ub;
            int v_loop_ub;
            // 'calcRVAJfromU:22' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            r_loop_ub = c_r1D.size(1) - 1;
            for (int i19{0}; i19 <= r_loop_ub; i19++) {
                int s_loop_ub;
                s_loop_ub = c_r1D.size(0) - 1;
                for (int i20{0}; i20 <= s_loop_ub; i20++) {
                    d_r1D[i20 + d_r1D.size(0) * i19] = c_r1D[i20 + c_r1D.size(0) * i19];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            t_loop_ub = r2D.size(1) - 1;
            for (int i21{0}; i21 <= t_loop_ub; i21++) {
                int u_loop_ub;
                u_loop_ub = r2D.size(0) - 1;
                for (int i22{0}; i22 <= u_loop_ub; i22++) {
                    b_r2D[i22 + b_r2D.size(0) * i21] = r2D[i22 + r2D.size(0) * i21];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            v_loop_ub = r3D.size(1) - 1;
            for (int i23{0}; i23 <= v_loop_ub; i23++) {
                int w_loop_ub;
                w_loop_ub = r3D.size(0) - 1;
                for (int i24{0}; i24 <= w_loop_ub; i24++) {
                    b_r3D[i24 + b_r3D.size(0) * i23] = r3D[i24 + r3D.size(0) * i23];
                }
            }
            b_ctx_kin.joint(b_r0D, d_r1D, b_r2D, b_r3D, a__1, c_r1D, r2D, r3D);
        }
        // 'calcRVAJfromU:25' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
        // 'calcRVAJfromU:26'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
        //    r0D     : [ 1 x M ] The vector of r
        //    r1D     : [ 1 x M ] The vector of first derivative of r
        //    r2D     : [ 1 x M ] The vector of second derivative of r
        //    r3D     : [ 1 x M ] The vector of second derivative of r
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromUWithoutCurv:18' R = r0D;
        // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
        if (c_r1D.size(1) == ud.size(1)) {
            int x_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            x_loop_ub = c_r1D.size(1);
            for (int i25{0}; i25 < x_loop_ub; i25++) {
                int ab_loop_ub;
                int i_scalarLB;
                int i_vectorUB;
                ab_loop_ub = c_r1D.size(0);
                i_scalarLB = (c_r1D.size(0) / 2) << 1;
                i_vectorUB = i_scalarLB - 2;
                for (int i27{0}; i27 <= i_vectorUB; i27 += 2) {
                    __m128d r9;
                    r9 = _mm_loadu_pd(&c_r1D[i27 + c_r1D.size(0) * i25]);
                    _mm_storeu_pd(&V[i27 + V.size(0) * i25], _mm_mul_pd(r9, _mm_set1_pd(ud[i25])));
                }
                for (int i27{i_scalarLB}; i27 < ab_loop_ub; i27++) {
                    V[i27 + V.size(0) * i25] = c_r1D[i27 + c_r1D.size(0) * i25] * ud[i25];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r3.set_size(1, ud.size(1));
        y_loop_ub = ud.size(1);
        for (int i26{0}; i26 < y_loop_ub; i26++) {
            double e_varargin_1;
            e_varargin_1 = ud[i26];
            r3[i26] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i28 = r3.size(1);
        } else {
            i28 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i29 = udd_vec.size(1);
        } else {
            i29 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r3.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i28 == i29)) {
            int bb_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            bb_loop_ub = r2D.size(1);
            for (int i30{0}; i30 < bb_loop_ub; i30++) {
                int db_loop_ub;
                int j_scalarLB;
                int j_vectorUB;
                db_loop_ub = r2D.size(0);
                j_scalarLB = (r2D.size(0) / 2) << 1;
                j_vectorUB = j_scalarLB - 2;
                for (int i32{0}; i32 <= j_vectorUB; i32 += 2) {
                    __m128d r10;
                    __m128d r11;
                    r10 = _mm_loadu_pd(&r2D[i32 + r2D.size(0) * i30]);
                    r11 = _mm_loadu_pd(&c_r1D[i32 + c_r1D.size(0) * i30]);
                    _mm_storeu_pd(&A[i32 + A.size(0) * i30],
                                  _mm_add_pd(_mm_mul_pd(r10, _mm_set1_pd(r3[i30])),
                                             _mm_mul_pd(r11, _mm_set1_pd(udd_vec[i30]))));
                }
                for (int i32{j_scalarLB}; i32 < db_loop_ub; i32++) {
                    A[i32 + A.size(0) * i30] = r2D[i32 + r2D.size(0) * i30] * r3[i30] +
                                               c_r1D[i32 + c_r1D.size(0) * i30] * udd_vec[i30];
                }
            }
        } else {
            binary_expand_op(A, r2D, r3, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r3.set_size(1, ud.size(1));
        cb_loop_ub = ud.size(1);
        for (int i31{0}; i31 < cb_loop_ub; i31++) {
            double f_varargin_1;
            f_varargin_1 = ud[i31];
            r3[i31] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i33 = ud.size(1);
        } else {
            i33 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i34 = r3.size(1);
        } else {
            i34 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i35 = ud.size(1);
        } else {
            i35 = r2D.size(1);
        }
        if (i35 == 1) {
            i36 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i36 = ud.size(1);
        } else {
            i36 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i37 = r2D.size(0);
        } else {
            i37 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i38 = r3.size(1);
        } else {
            i38 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i39 = ud.size(1);
        } else {
            i39 = r2D.size(1);
        }
        if (i38 == 1) {
            if (i39 == 1) {
                i40 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i40 = ud.size(1);
            } else {
                i40 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i40 = r3.size(1);
        } else {
            i40 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i41 = y.size(1);
        } else {
            i41 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r3.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i33 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i34 == i36) &&
            (c_r1D.size(1) == y.size(1)) && (i37 == c_r1D.size(0)) && (i40 == i41)) {
            int eb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            eb_loop_ub = r3D.size(1);
            for (int i42{0}; i42 < eb_loop_ub; i42++) {
                int fb_loop_ub;
                int k_scalarLB;
                int k_vectorUB;
                fb_loop_ub = r3D.size(0);
                k_scalarLB = (r3D.size(0) / 2) << 1;
                k_vectorUB = k_scalarLB - 2;
                for (int i43{0}; i43 <= k_vectorUB; i43 += 2) {
                    __m128d r12;
                    __m128d r13;
                    __m128d r14;
                    r12 = _mm_loadu_pd(&r3D[i43 + r3D.size(0) * i42]);
                    r13 = _mm_loadu_pd(&r2D[i43 + r2D.size(0) * i42]);
                    r14 = _mm_loadu_pd(&c_r1D[i43 + c_r1D.size(0) * i42]);
                    _mm_storeu_pd(
                        &J[i43 + J.size(0) * i42],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r12, _mm_set1_pd(r3[i42])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r13),
                                                             _mm_set1_pd(ud[i42])),
                                                  _mm_set1_pd(udd_vec[i42]))),
                            _mm_mul_pd(r14, _mm_set1_pd(b_jps))));
                }
                for (int i43{k_scalarLB}; i43 < fb_loop_ub; i43++) {
                    J[i43 + J.size(0) * i42] =
                        (r3D[i43 + r3D.size(0) * i42] * r3[i42] +
                         3.0 * r2D[i43 + r2D.size(0) * i42] * ud[i42] * udd_vec[i42]) +
                        c_r1D[i43 + c_r1D.size(0) * i42] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r3, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:83' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:85' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'zeroSpeedCurv:87' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int gb_loop_ub;
            // 'zeroSpeedCurv:89' else
            // 'zeroSpeedCurv:90' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            gb_loop_ub = c_r1D.size(1) - 1;
            for (int i44{0}; i44 <= gb_loop_ub; i44++) {
                int hb_loop_ub;
                hb_loop_ub = c_r1D.size(0) - 1;
                for (int i45{0}; i45 <= hb_loop_ub; i45++) {
                    e_r1D[i45 + e_r1D.size(0) * i44] = c_r1D[i45 + c_r1D.size(0) * i44];
                }
            }
            b_ctx_kin.v_relative(b_r0D, e_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:88' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:93' safetyFactor = 0.5;
        // 'zeroSpeedCurv:94' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:95' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i46{0}; i46 < b_trueCount; i46++) {
            vmax_data[i46] = ctx_cfg_vmax[b_tmp_data[i46] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:96' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int h_i{0}; h_i <= end_tmp; h_i++) {
            if (ctx_cfg_maskTot_data[h_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(h_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i47{0}; i47 < c_trueCount; i47++) {
            amax_data[i47] = ctx_cfg_amax[c_tmp_data[i47] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:97' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int i_i{0}; i_i <= end_tmp; i_i++) {
            if (ctx_cfg_maskTot_data[i_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(i_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i48{0}; i48 < d_trueCount; i48++) {
            jmax_data[i48] = ctx_cfg_jmax[d_tmp_data[i48] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        ib_loop_ub = c_r1D.size(1);
        for (int i49{0}; i49 < ib_loop_ub; i49++) {
            y[i49] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            jb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int d_k{0}; d_k <= hi; d_k++) {
            xv.set_size(outsize_idx_0);
            for (int i50{0}; i50 < jb_loop_ub; i50++) {
                xv[i50] = 0.0;
            }
            for (int e_k{0}; e_k < nx; e_k++) {
                xv[e_k] = c_r1D[(ctx_cfg_indCart[e_k] + c_r1D.size(0) * d_k) - 1];
            }
            y[d_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int kb_loop_ub;
            int l_scalarLB;
            int l_vectorUB;
            feed.set_size(1, y.size(1));
            kb_loop_ub = y.size(1);
            l_scalarLB = (y.size(1) / 2) << 1;
            l_vectorUB = l_scalarLB - 2;
            for (int i51{0}; i51 <= l_vectorUB; i51 += 2) {
                __m128d r15;
                __m128d r16;
                r15 = _mm_loadu_pd(&y[i51]);
                r16 = _mm_loadu_pd(&ud[i51]);
                _mm_storeu_pd(&feed[i51], _mm_mul_pd(r15, r16));
            }
            for (int i51{l_scalarLB}; i51 < kb_loop_ub; i51++) {
                feed[i51] = y[i51] * ud[i51];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:101' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        lb_loop_ub = feed.size(1);
        for (int i52{0}; i52 < lb_loop_ub; i52++) {
            x[i52] = (feed[i52] > b_fmax);
        }
        b_y = false;
        f_k = 0;
        exitg1 = false;
        while ((!exitg1) && (f_k <= x.size(1) - 1)) {
            if (x[f_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                f_k++;
            }
        }
        if (b_y) {
            int m_scalarLB;
            int m_vectorUB;
            int mb_loop_ub;
            // 'zeroSpeedCurv:102' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            m_scalarLB = (feed.size(1) / 2) << 1;
            m_vectorUB = m_scalarLB - 2;
            for (int i54{0}; i54 <= m_vectorUB; i54 += 2) {
                __m128d r18;
                r18 = _mm_loadu_pd(&feed[i54]);
                _mm_storeu_pd(&b_feed[i54], _mm_sub_pd(r18, _mm_set1_pd(b_fmax)));
            }
            for (int i54{m_scalarLB}; i54 < mb_loop_ub; i54++) {
                b_feed[i54] = feed[i54] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:103' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r17.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i53;
                i53 = V.size(1);
                for (int g_k{0}; g_k < i53; g_k++) {
                    int i55;
                    i55 = r17.size(0);
                    for (int h_k{0}; h_k < i55; h_k++) {
                        r17[h_k + r17.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r17.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(r17.size(0), r17.size(1));
                nb_loop_ub = r17.size(1);
                for (int i56{0}; i56 < nb_loop_ub; i56++) {
                    int ob_loop_ub;
                    ob_loop_ub = r17.size(0);
                    for (int i57{0}; i57 < ob_loop_ub; i57++) {
                        b_x[i57 + b_x.size(0) * i56] =
                            (r17[i57 + r17.size(0) * i56] > vmax_data[i57]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r17, vmax_data, &b_trueCount);
            }
            c_y = false;
            i_k = 0;
            exitg1 = false;
            while ((!exitg1) && (i_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[i_k]) {
                    c_y = true;
                    exitg1 = true;
                } else {
                    i_k++;
                }
            }
            if (c_y) {
                // 'zeroSpeedCurv:104' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:105' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r17.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int sb_loop_ub;
                    r19.set_size(r17.size(0), r17.size(1));
                    pb_loop_ub = r17.size(1);
                    for (int i59{0}; i59 < pb_loop_ub; i59++) {
                        int n_scalarLB;
                        int n_vectorUB;
                        int rb_loop_ub;
                        rb_loop_ub = r17.size(0);
                        n_scalarLB = (r17.size(0) / 2) << 1;
                        n_vectorUB = n_scalarLB - 2;
                        for (int i64{0}; i64 <= n_vectorUB; i64 += 2) {
                            __m128d r20;
                            __m128d r21;
                            r20 = _mm_loadu_pd(&r17[i64 + r17.size(0) * i59]);
                            r21 = _mm_loadu_pd(&vmax_data[i64]);
                            _mm_storeu_pd(&r19[i64 + r19.size(0) * i59], _mm_sub_pd(r20, r21));
                        }
                        for (int i64{n_scalarLB}; i64 < rb_loop_ub; i64++) {
                            r19[i64 + r19.size(0) * i59] =
                                r17[i64 + r17.size(0) * i59] - vmax_data[i64];
                        }
                    }
                    r17.set_size(r19.size(0), r19.size(1));
                    sb_loop_ub = r19.size(1);
                    for (int i62{0}; i62 < sb_loop_ub; i62++) {
                        int ub_loop_ub;
                        ub_loop_ub = r19.size(0);
                        for (int i65{0}; i65 < ub_loop_ub; i65++) {
                            r17[i65 + r17.size(0) * i62] = r19[i65 + r19.size(0) * i62];
                        }
                    }
                    coder::internal::b_maximum(r17, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r17, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:106' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                r17.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i58;
                    i58 = A.size(1);
                    for (int j_k{0}; j_k < i58; j_k++) {
                        int i60;
                        i60 = r17.size(0);
                        for (int k_k{0}; k_k < i60; k_k++) {
                            r17[k_k + r17.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r17.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(r17.size(0), r17.size(1));
                    qb_loop_ub = r17.size(1);
                    for (int i61{0}; i61 < qb_loop_ub; i61++) {
                        int tb_loop_ub;
                        tb_loop_ub = r17.size(0);
                        for (int i63{0}; i63 < tb_loop_ub; i63++) {
                            b_x[i63 + b_x.size(0) * i61] =
                                (r17[i63 + r17.size(0) * i61] > amax_data[i63]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r17, amax_data, &c_trueCount);
                }
                d_y = false;
                l_k = 0;
                exitg1 = false;
                while ((!exitg1) && (l_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[l_k]) {
                        d_y = true;
                        exitg1 = true;
                    } else {
                        l_k++;
                    }
                }
                if (d_y) {
                    // 'zeroSpeedCurv:107' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:108' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r17.size(0) == c_trueCount) {
                        int vb_loop_ub;
                        int yb_loop_ub;
                        r22.set_size(r17.size(0), r17.size(1));
                        vb_loop_ub = r17.size(1);
                        for (int i67{0}; i67 < vb_loop_ub; i67++) {
                            int o_scalarLB;
                            int o_vectorUB;
                            int xb_loop_ub;
                            xb_loop_ub = r17.size(0);
                            o_scalarLB = (r17.size(0) / 2) << 1;
                            o_vectorUB = o_scalarLB - 2;
                            for (int i72{0}; i72 <= o_vectorUB; i72 += 2) {
                                __m128d r23;
                                __m128d r24;
                                r23 = _mm_loadu_pd(&r17[i72 + r17.size(0) * i67]);
                                r24 = _mm_loadu_pd(&amax_data[i72]);
                                _mm_storeu_pd(&r22[i72 + r22.size(0) * i67], _mm_sub_pd(r23, r24));
                            }
                            for (int i72{o_scalarLB}; i72 < xb_loop_ub; i72++) {
                                r22[i72 + r22.size(0) * i67] =
                                    r17[i72 + r17.size(0) * i67] - amax_data[i72];
                            }
                        }
                        r17.set_size(r22.size(0), r22.size(1));
                        yb_loop_ub = r22.size(1);
                        for (int i70{0}; i70 < yb_loop_ub; i70++) {
                            int bc_loop_ub;
                            bc_loop_ub = r22.size(0);
                            for (int i73{0}; i73 < bc_loop_ub; i73++) {
                                r17[i73 + r17.size(0) * i70] = r22[i73 + r22.size(0) * i70];
                            }
                        }
                        coder::internal::b_maximum(r17, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r17, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:109' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    r17.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i66;
                        i66 = J.size(1);
                        for (int m_k{0}; m_k < i66; m_k++) {
                            int i68;
                            i68 = r17.size(0);
                            for (int n_k{0}; n_k < i68; n_k++) {
                                r17[n_k + r17.size(0) * m_k] = std::abs(J[n_k + J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r17.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(r17.size(0), r17.size(1));
                        wb_loop_ub = r17.size(1);
                        for (int i69{0}; i69 < wb_loop_ub; i69++) {
                            int ac_loop_ub;
                            ac_loop_ub = r17.size(0);
                            for (int i71{0}; i71 < ac_loop_ub; i71++) {
                                b_x[i71 + b_x.size(0) * i69] =
                                    (r17[i71 + r17.size(0) * i69] > jmax_data[i71]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r17, jmax_data, &d_trueCount);
                    }
                    e_y = false;
                    o_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (o_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[o_k]) {
                            e_y = true;
                            exitg1 = true;
                        } else {
                            o_k++;
                        }
                    }
                    if (e_y) {
                        // 'zeroSpeedCurv:110' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:111' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r17.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            r25.set_size(r17.size(0), r17.size(1));
                            cc_loop_ub = r17.size(1);
                            for (int i74{0}; i74 < cc_loop_ub; i74++) {
                                int dc_loop_ub;
                                int p_scalarLB;
                                int p_vectorUB;
                                dc_loop_ub = r17.size(0);
                                p_scalarLB = (r17.size(0) / 2) << 1;
                                p_vectorUB = p_scalarLB - 2;
                                for (int i76{0}; i76 <= p_vectorUB; i76 += 2) {
                                    __m128d r26;
                                    __m128d r27;
                                    r26 = _mm_loadu_pd(&r17[i76 + r17.size(0) * i74]);
                                    r27 = _mm_loadu_pd(&jmax_data[i76]);
                                    _mm_storeu_pd(&r25[i76 + r25.size(0) * i74],
                                                  _mm_sub_pd(r26, r27));
                                }
                                for (int i76{p_scalarLB}; i76 < dc_loop_ub; i76++) {
                                    r25[i76 + r25.size(0) * i74] =
                                        r17[i76 + r17.size(0) * i74] - jmax_data[i76];
                                }
                            }
                            r17.set_size(r25.size(0), r25.size(1));
                            ec_loop_ub = r25.size(1);
                            for (int i75{0}; i75 < ec_loop_ub; i75++) {
                                int fc_loop_ub;
                                fc_loop_ub = r25.size(0);
                                for (int i77{0}; i77 < fc_loop_ub; i77++) {
                                    r17[i77 + r17.size(0) * i75] = r25[i77 + r25.size(0) * i75];
                                }
                            }
                            coder::internal::b_maximum(r17, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r17, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:112' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:113' else
                        // 'zeroSpeedCurv:114' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:40' if( coder.target( "MATLAB" ) )
    // 'zeroSpeedCurv:42' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:50' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    b_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:52' if( k > 0 )
    if (b_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:53' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(b_k) + 1);
        b_loop_ub = static_cast<int>(b_k);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:54' if( k_vec( end ) < k )
        if (static_cast<int>(b_k) < b_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:54' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(b_k) + 2);
            e_loop_ub = static_cast<int>(b_k);
            for (int i6{0}; i6 <= e_loop_ub; i6++) {
                k_vec[i6] = i6;
            }
            k_vec[static_cast<int>(b_k) + 1] = b_k;
        }
    } else {
        // 'zeroSpeedCurv:55' else
        // 'zeroSpeedCurv:56' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:43' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i5{0}; i5 <= vectorUB; i5 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i5]);
        _mm_storeu_pd(&y[i5], _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt)));
    }
    for (int i5{scalarLB}; i5 < d_loop_ub; i5++) {
        y[i5] = k_vec[i5] * ctx_cfg_dt;
    }
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec      :  [ 1 x M ] The time vector
    //    isEnd      :  ( Boolean ) Is the end of the Curve.
    //    a          :  Curve parameter a for affine transforme
    //    b          :  Curve parameter b for affine transforme
    //  Outputs :
    //    u          :  [ N x M ]
    //    ud         :  [ N x M ]
    //    udd        :  [ N x M ]
    //    uddd       :  [ N x M ]
    // 'constJerkU:16' if( coder.target( "MATLAB" ) )
    // 'constJerkU:22' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    udd.set_size(1, y.size(1));
    h_loop_ub = y.size(1);
    c_scalarLB = (y.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i9{0}; i9 <= c_vectorUB; i9 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&y[i9]);
        _mm_storeu_pd(&udd[i9], _mm_mul_pd(_mm_set1_pd(b_jps), r2));
    }
    for (int i9{c_scalarLB}; i9 < h_loop_ub; i9++) {
        udd[i9] = b_jps * y[i9];
    }
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r3.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        double varargin_1;
        varargin_1 = y[i10];
        r3[i10] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r3.size(1));
    j_loop_ub = r3.size(1);
    d_scalarLB = (r3.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i11{0}; i11 <= d_vectorUB; i11 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3[i11]);
        _mm_storeu_pd(&ud[i11], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(2.0)));
    }
    for (int i11{d_scalarLB}; i11 < j_loop_ub; i11++) {
        ud[i11] = b_jps * r3[i11] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r3.set_size(1, y.size(1));
    l_loop_ub = y.size(1);
    for (int i13{0}; i13 < l_loop_ub; i13++) {
        double c_varargin_1;
        c_varargin_1 = y[i13];
        r3[i13] = std::pow(c_varargin_1, 3.0);
    }
    u.set_size(1, r3.size(1));
    n_loop_ub = r3.size(1);
    f_scalarLB = (r3.size(1) / 2) << 1;
    f_vectorUB = f_scalarLB - 2;
    for (int i15{0}; i15 <= f_vectorUB; i15 += 2) {
        __m128d r6;
        r6 = _mm_loadu_pd(&r3[i15]);
        _mm_storeu_pd(&u[i15], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r6), _mm_set1_pd(6.0)));
    }
    for (int i15{f_scalarLB}; i15 < n_loop_ub; i15++) {
        u[i15] = b_jps * r3[i15] / 6.0;
    }
    // 'constJerkU:33' u( u > 1 ) = 1;
    end = u.size(1);
    for (int c_i{0}; c_i < end; c_i++) {
        if (u[c_i] > 1.0) {
            u[c_i] = 1.0;
        }
    }
    // 'constJerkU:34' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int d_i{0}; d_i < b_end; d_i++) {
        if (u[d_i] < 0.0) {
            u[d_i] = 0.0;
        }
    }
    // 'constJerkU:36' if( isEnd )
    *jps = b_jps;
}

} // namespace ocn

//
// File trailer for zeroSpeedCurv.cpp
//
// [EOF]
//
