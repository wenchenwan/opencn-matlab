//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "cutCurvStructU.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ curv1, curv2 ] = cutZeroEnd( ctx, curv )
//
// cutZeroEnd : Cut the end of the given to handle the zero speed.
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
//                double ctx_cfg_LSplitZero
//                double ctx_cfg_dt
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const Kinematics *ctx_kin
//                const CurvStruct *curv
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
namespace ocn {
void cutZeroEnd(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                const Kinematics *ctx_kin, const CurvStruct *curv, CurvStruct *curv1,
                CurvStruct *curv2)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r14;
    ::coder::array<double, 2U> r16;
    ::coder::array<double, 2U> r19;
    ::coder::array<double, 2U> r22;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> ud;
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
    double jmax_data[6];
    double vmax_data[6];
    double a_delta;
    double b_ex;
    double b_fmax;
    double d;
    double d_ex;
    double f_delta;
    double j_delta;
    double jps;
    double u;
    double v_delta;
    unsigned int uv[2];
    int b_iindx;
    int b_trueCount;
    int bb_loop_ub;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_trueCount;
    int end_tmp;
    int iindx;
    int last;
    int nx;
    int outsize_idx_0;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'cutZeroEnd:3' u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
    u = b_cutCurvStructU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX,
                         ctx_cfg_GaussLegendreW, curv, ctx_cfg_LSplitZero);
    // 'cutZeroEnd:5' if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
    d = curv->b_param + curv->a_param;
    if ((u >= d) || (u <= curv->b_param)) {
        // 'cutZeroEnd:6' u = curv.a_param / 2 + curv.b_param;
        u = curv->a_param / 2.0 + curv->b_param;
    }
    // 'cutZeroEnd:9' curv2                   = curv;
    *curv2 = *curv;
    // 'cutZeroEnd:10' curv2.UseConstJerk      = true;
    curv2->UseConstJerk = true;
    // 'cutZeroEnd:11' curv2.b_param           = u;
    curv2->b_param = u;
    // 'cutZeroEnd:12' curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
    curv2->a_param = d - u;
    // 'cutZeroEnd:13' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
    //  zeroSpeedCurv : Compute the profile paramater u in case of zero start /
    //  stop. This approach assumes a constant pseudo jerk. The resulting profile
    //  will respect the velocity, acceleration and jerk constraints.
    //  Inputs  :
    //    ctx     : The context
    //    curv    : The Curve Struct
    //    isEnd   : ( Boolean ) is the end of a curve
    //  Outputs :
    //    u       : Resulting U for constant jerk
    //    jps     : Resulting Pseudo jerk
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:15' uk = 1 - uk ;
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv2, r0D, r1D);
    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
    if (curv2->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:20' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:24' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    if (trueCount <= 2) {
        if (trueCount == 1) {
            b_ex = ctx_cfg_jmax[tmp_data[0] - 1];
        } else {
            double d1;
            double d2;
            d1 = ctx_cfg_jmax[tmp_data[0] - 1];
            d2 = ctx_cfg_jmax[tmp_data[trueCount - 1] - 1];
            if (d1 > d2) {
                b_ex = d2;
            } else {
                b_ex = d1;
            }
        }
    } else {
        double ex;
        ex = ctx_cfg_jmax[tmp_data[0] - 1];
        for (int b_k{2}; b_k <= trueCount; b_k++) {
            double d3;
            d3 = ctx_cfg_jmax[tmp_data[b_k - 1] - 1];
            if (ex > d3) {
                ex = d3;
            }
        }
        b_ex = ex;
    }
    last = z1.size(0);
    if (z1.size(0) <= 2) {
        if (z1.size(0) == 1) {
            d_ex = z1[0];
        } else if (z1[0] < z1[z1.size(0) - 1]) {
            d_ex = z1[z1.size(0) - 1];
        } else {
            d_ex = z1[0];
        }
    } else {
        double c_ex;
        c_ex = z1[0];
        for (int c_k{2}; c_k <= last; c_k++) {
            double d4;
            d4 = z1[c_k - 1];
            if (c_ex < d4) {
                c_ex = d4;
            }
        }
        d_ex = c_ex;
    }
    jps = b_ex / d_ex;
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:29' searchJps = true;
    // 'zeroSpeedCurv:31' ind = 0;
    // 'zeroSpeedCurv:32' while searchJps
    b_fmax = curv2->Info.FeedRate * 0.5;
    uv[0] = 1U;
    searchJps = true;
    while (searchJps) {
        double b_jps;
        double d_k;
        double k_tmp;
        int ab_loop_ub;
        int b_end;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_partialTrueCount;
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        int d_partialTrueCount;
        int d_scalarLB;
        int d_vectorUB;
        int db_loop_ub;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int end;
        int f_loop_ub;
        int g_k;
        int g_loop_ub;
        int h_loop_ub;
        int hi;
        int i10;
        int i20;
        int i21;
        int i25;
        int i26;
        int i27;
        int i28;
        int i29;
        int i30;
        int i31;
        int i32;
        int i33;
        int i4;
        int i6;
        int i8;
        int i9;
        int i_loop_ub;
        int q_loop_ub;
        int scalarLB;
        int t_loop_ub;
        int vectorUB;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        k_tmp = std::pow(6.0 / jps, 0.33333333333333331);
        d_k = k_tmp / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (d_k > 0.0) {
            int b_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            b_loop_ub = static_cast<int>(std::floor(d_k));
            k_vec.set_size(1, b_loop_ub + 1);
            for (int i2{0}; i2 <= b_loop_ub; i2++) {
                k_vec[i2] = i2;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (b_loop_ub < d_k) {
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, b_loop_ub + 2);
                for (int i3{0}; i3 <= b_loop_ub; i3++) {
                    k_vec[i3] = i3;
                }
                k_vec[b_loop_ub + 1] = d_k;
            }
        } else {
            // 'zeroSpeedCurv:53' else
            // 'zeroSpeedCurv:54' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:35' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
        b_jps = jps;
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
        // 'zeroSpeedCurv:75' if( isempty( ratio ) )
        // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
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
        c_loop_ub = k_vec.size(1);
        scalarLB = (k_vec.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i4 = 0; i4 <= vectorUB; i4 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&k_vec[i4]);
            _mm_storeu_pd(&y[i4],
                          _mm_sub_pd(_mm_set1_pd(k_tmp), _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt))));
        }
        for (i4 = scalarLB; i4 < c_loop_ub; i4++) {
            y[i4] = k_tmp - k_vec[i4] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r1.set_size(1, y.size(1));
        d_loop_ub = y.size(1);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            double varargin_1;
            varargin_1 = y[i5];
            r1[i5] = std::pow(varargin_1, 2.0);
        }
        ud.set_size(1, r1.size(1));
        e_loop_ub = r1.size(1);
        b_scalarLB = (r1.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i6 = 0; i6 <= b_vectorUB; i6 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r1[i6]);
            _mm_storeu_pd(&ud[i6], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
        }
        for (i6 = b_scalarLB; i6 < e_loop_ub; i6++) {
            ud[i6] = jps * r1[i6] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r1.set_size(1, y.size(1));
        f_loop_ub = y.size(1);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            double b_varargin_1;
            b_varargin_1 = y[i7];
            r1[i7] = std::pow(b_varargin_1, 3.0);
        }
        b_u.set_size(1, r1.size(1));
        g_loop_ub = r1.size(1);
        c_scalarLB = (r1.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i8 = 0; i8 <= c_vectorUB; i8 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r1[i8]);
            _mm_storeu_pd(&b_u[i8], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r3), _mm_set1_pd(6.0)));
        }
        for (i8 = c_scalarLB; i8 < g_loop_ub; i8++) {
            b_u[i8] = jps * r1[i8] / 6.0;
        }
        // 'constJerkU:33' u( u > 1 ) = 1;
        end = b_u.size(1);
        for (int c_i{0}; c_i < end; c_i++) {
            if (b_u[c_i] > 1.0) {
                b_u[c_i] = 1.0;
            }
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        b_end = b_u.size(1);
        for (int d_i{0}; d_i < b_end; d_i++) {
            if (b_u[d_i] < 0.0) {
                b_u[d_i] = 0.0;
            }
        }
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        b_u.set_size(1, b_u.size(1));
        h_loop_ub = b_u.size(1);
        d_scalarLB = (b_u.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i9 = 0; i9 <= d_vectorUB; i9 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&b_u[i9]);
            _mm_storeu_pd(&b_u[i9], _mm_sub_pd(_mm_set1_pd(1.0), r4));
        }
        for (i9 = d_scalarLB; i9 < h_loop_ub; i9++) {
            b_u[i9] = 1.0 - b_u[i9];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        i_loop_ub = y.size(1);
        e_scalarLB = (y.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (i10 = 0; i10 <= e_vectorUB; i10 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&y[i10]);
            _mm_storeu_pd(&udd_vec[i10],
                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jps), r5), _mm_set1_pd(-1.0)));
        }
        for (i10 = e_scalarLB; i10 < i_loop_ub; i10++) {
            udd_vec[i10] = -(jps * y[i10]);
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
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2, b_u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
        if (curv2->Info.TRAFO) {
            int j_loop_ub;
            int l_loop_ub;
            int n_loop_ub;
            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            j_loop_ub = c_r1D.size(1) - 1;
            for (int i11{0}; i11 <= j_loop_ub; i11++) {
                int k_loop_ub;
                k_loop_ub = c_r1D.size(0) - 1;
                for (int i12{0}; i12 <= k_loop_ub; i12++) {
                    d_r1D[i12 + d_r1D.size(0) * i11] = c_r1D[i12 + c_r1D.size(0) * i11];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            l_loop_ub = r2D.size(1) - 1;
            for (int i13{0}; i13 <= l_loop_ub; i13++) {
                int m_loop_ub;
                m_loop_ub = r2D.size(0) - 1;
                for (int i14{0}; i14 <= m_loop_ub; i14++) {
                    b_r2D[i14 + b_r2D.size(0) * i13] = r2D[i14 + r2D.size(0) * i13];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            n_loop_ub = r3D.size(1) - 1;
            for (int i15{0}; i15 <= n_loop_ub; i15++) {
                int o_loop_ub;
                o_loop_ub = r3D.size(0) - 1;
                for (int i16{0}; i16 <= o_loop_ub; i16++) {
                    b_r3D[i16 + b_r3D.size(0) * i15] = r3D[i16 + r3D.size(0) * i15];
                }
            }
            ctx_kin->joint(b_r0D, d_r1D, b_r2D, b_r3D, a__1, c_r1D, r2D, r3D);
        }
        // 'calcRVAJfromU:23' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
        // 'calcRVAJfromU:24'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
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
            int p_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            p_loop_ub = c_r1D.size(1);
            for (int i17{0}; i17 < p_loop_ub; i17++) {
                int f_scalarLB;
                int f_vectorUB;
                int i19;
                int r_loop_ub;
                r_loop_ub = c_r1D.size(0);
                f_scalarLB = (c_r1D.size(0) / 2) << 1;
                f_vectorUB = f_scalarLB - 2;
                for (i19 = 0; i19 <= f_vectorUB; i19 += 2) {
                    __m128d r6;
                    r6 = _mm_loadu_pd(&c_r1D[i19 + c_r1D.size(0) * i17]);
                    _mm_storeu_pd(&V[i19 + V.size(0) * i17], _mm_mul_pd(r6, _mm_set1_pd(ud[i17])));
                }
                for (i19 = f_scalarLB; i19 < r_loop_ub; i19++) {
                    V[i19 + V.size(0) * i17] = c_r1D[i19 + c_r1D.size(0) * i17] * ud[i17];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r1.set_size(1, ud.size(1));
        q_loop_ub = ud.size(1);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            double c_varargin_1;
            c_varargin_1 = ud[i18];
            r1[i18] = std::pow(c_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i20 = r1.size(1);
        } else {
            i20 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i21 = udd_vec.size(1);
        } else {
            i21 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r1.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i20 == i21)) {
            int s_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            s_loop_ub = r2D.size(1);
            for (int i22{0}; i22 < s_loop_ub; i22++) {
                int g_scalarLB;
                int g_vectorUB;
                int i24;
                int u_loop_ub;
                u_loop_ub = r2D.size(0);
                g_scalarLB = (r2D.size(0) / 2) << 1;
                g_vectorUB = g_scalarLB - 2;
                for (i24 = 0; i24 <= g_vectorUB; i24 += 2) {
                    __m128d r7;
                    __m128d r8;
                    r7 = _mm_loadu_pd(&r2D[i24 + r2D.size(0) * i22]);
                    r8 = _mm_loadu_pd(&c_r1D[i24 + c_r1D.size(0) * i22]);
                    _mm_storeu_pd(&A[i24 + A.size(0) * i22],
                                  _mm_add_pd(_mm_mul_pd(r7, _mm_set1_pd(r1[i22])),
                                             _mm_mul_pd(r8, _mm_set1_pd(udd_vec[i22]))));
                }
                for (i24 = g_scalarLB; i24 < u_loop_ub; i24++) {
                    A[i24 + A.size(0) * i22] = r2D[i24 + r2D.size(0) * i22] * r1[i22] +
                                               c_r1D[i24 + c_r1D.size(0) * i22] * udd_vec[i22];
                }
            }
        } else {
            binary_expand_op(A, r2D, r1, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r1.set_size(1, ud.size(1));
        t_loop_ub = ud.size(1);
        for (int i23{0}; i23 < t_loop_ub; i23++) {
            double d_varargin_1;
            d_varargin_1 = ud[i23];
            r1[i23] = std::pow(d_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i25 = ud.size(1);
        } else {
            i25 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i26 = r1.size(1);
        } else {
            i26 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i27 = ud.size(1);
        } else {
            i27 = r2D.size(1);
        }
        if (i27 == 1) {
            i28 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i28 = ud.size(1);
        } else {
            i28 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i29 = r2D.size(0);
        } else {
            i29 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i30 = r1.size(1);
        } else {
            i30 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i31 = ud.size(1);
        } else {
            i31 = r2D.size(1);
        }
        if (i30 == 1) {
            if (i31 == 1) {
                i32 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i32 = ud.size(1);
            } else {
                i32 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i32 = r1.size(1);
        } else {
            i32 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i33 = y.size(1);
        } else {
            i33 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i25 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i26 == i28) &&
            (c_r1D.size(1) == y.size(1)) && (i29 == c_r1D.size(0)) && (i32 == i33)) {
            int v_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            v_loop_ub = r3D.size(1);
            for (int i34{0}; i34 < v_loop_ub; i34++) {
                int h_scalarLB;
                int h_vectorUB;
                int i35;
                int w_loop_ub;
                w_loop_ub = r3D.size(0);
                h_scalarLB = (r3D.size(0) / 2) << 1;
                h_vectorUB = h_scalarLB - 2;
                for (i35 = 0; i35 <= h_vectorUB; i35 += 2) {
                    __m128d r10;
                    __m128d r11;
                    __m128d r9;
                    r9 = _mm_loadu_pd(&r3D[i35 + r3D.size(0) * i34]);
                    r10 = _mm_loadu_pd(&r2D[i35 + r2D.size(0) * i34]);
                    r11 = _mm_loadu_pd(&c_r1D[i35 + c_r1D.size(0) * i34]);
                    _mm_storeu_pd(
                        &J[i35 + J.size(0) * i34],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r9, _mm_set1_pd(r1[i34])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r10),
                                                             _mm_set1_pd(ud[i34])),
                                                  _mm_set1_pd(udd_vec[i34]))),
                            _mm_mul_pd(r11, _mm_set1_pd(jps))));
                }
                for (i35 = h_scalarLB; i35 < w_loop_ub; i35++) {
                    J[i35 + J.size(0) * i34] =
                        (r3D[i35 + r3D.size(0) * i34] * r1[i34] +
                         3.0 * r2D[i35 + r2D.size(0) * i34] * ud[i34] * udd_vec[i34]) +
                        c_r1D[i35 + c_r1D.size(0) * i34] * jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r1, r2D, ud, udd_vec, c_r1D, jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2, b_u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
        if (!curv2->Info.TRAFO) {
            int x_loop_ub;
            // 'zeroSpeedCurv:85' else
            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            x_loop_ub = c_r1D.size(1) - 1;
            for (int i36{0}; i36 <= x_loop_ub; i36++) {
                int y_loop_ub;
                y_loop_ub = c_r1D.size(0) - 1;
                for (int i37{0}; i37 <= y_loop_ub; i37++) {
                    e_r1D[i37 + e_r1D.size(0) * i36] = c_r1D[i37 + c_r1D.size(0) * i36];
                }
            }
            ctx_kin->v_relative(b_r0D, e_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:84' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:89' safetyFactor = 0.5;
        // 'zeroSpeedCurv:90' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:91' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int e_i{0}; e_i <= end_tmp; e_i++) {
            if (ctx_cfg_maskTot_data[e_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(e_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i38{0}; i38 < b_trueCount; i38++) {
            vmax_data[i38] = ctx_cfg_vmax[b_tmp_data[i38] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:92' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int f_i{0}; f_i <= end_tmp; f_i++) {
            if (ctx_cfg_maskTot_data[f_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(f_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i39{0}; i39 < c_trueCount; i39++) {
            amax_data[i39] = ctx_cfg_amax[c_tmp_data[i39] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:93' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(g_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i40{0}; i40 < d_trueCount; i40++) {
            jmax_data[i40] = ctx_cfg_jmax[d_tmp_data[i40] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        ab_loop_ub = c_r1D.size(1);
        for (int i41{0}; i41 < ab_loop_ub; i41++) {
            y[i41] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (0 <= c_r1D.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            bb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int e_k{0}; e_k <= hi; e_k++) {
            xv.set_size(outsize_idx_0);
            for (int i42{0}; i42 < bb_loop_ub; i42++) {
                xv[i42] = 0.0;
            }
            for (int f_k{0}; f_k < nx; f_k++) {
                xv[f_k] = c_r1D[(ctx_cfg_indCart[f_k] + c_r1D.size(0) * e_k) - 1];
            }
            y[e_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int cb_loop_ub;
            int i43;
            int i_scalarLB;
            int i_vectorUB;
            feed.set_size(1, y.size(1));
            cb_loop_ub = y.size(1);
            i_scalarLB = (y.size(1) / 2) << 1;
            i_vectorUB = i_scalarLB - 2;
            for (i43 = 0; i43 <= i_vectorUB; i43 += 2) {
                __m128d r12;
                __m128d r13;
                r12 = _mm_loadu_pd(&y[i43]);
                r13 = _mm_loadu_pd(&ud[i43]);
                _mm_storeu_pd(&feed[i43], _mm_mul_pd(r12, r13));
            }
            for (i43 = i_scalarLB; i43 < cb_loop_ub; i43++) {
                feed[i43] = y[i43] * ud[i43];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        db_loop_ub = feed.size(1);
        for (int i44{0}; i44 < db_loop_ub; i44++) {
            x[i44] = (feed[i44] > b_fmax);
        }
        b_y = false;
        g_k = 0;
        exitg1 = false;
        while ((!exitg1) && (g_k <= x.size(1) - 1)) {
            if (x[g_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                g_k++;
            }
        }
        if (b_y) {
            int eb_loop_ub;
            int i47;
            int j_scalarLB;
            int j_vectorUB;
            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            eb_loop_ub = feed.size(1);
            j_scalarLB = (feed.size(1) / 2) << 1;
            j_vectorUB = j_scalarLB - 2;
            for (i47 = 0; i47 <= j_vectorUB; i47 += 2) {
                __m128d r15;
                r15 = _mm_loadu_pd(&feed[i47]);
                _mm_storeu_pd(&b_feed[i47], _mm_sub_pd(r15, _mm_set1_pd(b_fmax)));
            }
            for (i47 = j_scalarLB; i47 < eb_loop_ub; i47++) {
                b_feed[i47] = feed[i47] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool c_y;
            r14.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i45;
                i45 = V.size(1);
                for (int h_k{0}; h_k < i45; h_k++) {
                    int i46;
                    i46 = r14.size(0);
                    for (int i_k{0}; i_k < i46; i_k++) {
                        r14[i_k + r14.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (r14.size(0) == b_trueCount) {
                int fb_loop_ub;
                b_x.set_size(r14.size(0), r14.size(1));
                fb_loop_ub = r14.size(1);
                for (int i48{0}; i48 < fb_loop_ub; i48++) {
                    int gb_loop_ub;
                    gb_loop_ub = r14.size(0);
                    for (int i49{0}; i49 < gb_loop_ub; i49++) {
                        b_x[i49 + b_x.size(0) * i48] =
                            (r14[i49 + r14.size(0) * i48] > vmax_data[i49]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r14, vmax_data, &b_trueCount);
            }
            c_y = false;
            j_k = 0;
            exitg1 = false;
            while ((!exitg1) && (j_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[j_k]) {
                    c_y = true;
                    exitg1 = true;
                } else {
                    j_k++;
                }
            }
            if (c_y) {
                // 'zeroSpeedCurv:100' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:101' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r14.size(0) == b_trueCount) {
                    int hb_loop_ub;
                    int lb_loop_ub;
                    r16.set_size(r14.size(0), r14.size(1));
                    hb_loop_ub = r14.size(1);
                    for (int i52{0}; i52 < hb_loop_ub; i52++) {
                        int i56;
                        int jb_loop_ub;
                        int k_scalarLB;
                        int k_vectorUB;
                        jb_loop_ub = r14.size(0);
                        k_scalarLB = (r14.size(0) / 2) << 1;
                        k_vectorUB = k_scalarLB - 2;
                        for (i56 = 0; i56 <= k_vectorUB; i56 += 2) {
                            __m128d r17;
                            __m128d r18;
                            r17 = _mm_loadu_pd(&r14[i56 + r14.size(0) * i52]);
                            r18 = _mm_loadu_pd(&vmax_data[i56]);
                            _mm_storeu_pd(&r16[i56 + r16.size(0) * i52], _mm_sub_pd(r17, r18));
                        }
                        for (i56 = k_scalarLB; i56 < jb_loop_ub; i56++) {
                            r16[i56 + r16.size(0) * i52] =
                                r14[i56 + r14.size(0) * i52] - vmax_data[i56];
                        }
                    }
                    r14.set_size(r16.size(0), r16.size(1));
                    lb_loop_ub = r16.size(1);
                    for (int i55{0}; i55 < lb_loop_ub; i55++) {
                        int mb_loop_ub;
                        mb_loop_ub = r16.size(0);
                        for (int i57{0}; i57 < mb_loop_ub; i57++) {
                            r14[i57 + r14.size(0) * i55] = r16[i57 + r16.size(0) * i55];
                        }
                    }
                    coder::internal::b_maximum(r14, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r14, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool d_y;
                r14.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i50;
                    i50 = A.size(1);
                    for (int k_k{0}; k_k < i50; k_k++) {
                        int i51;
                        i51 = r14.size(0);
                        for (int l_k{0}; l_k < i51; l_k++) {
                            r14[l_k + r14.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (r14.size(0) == c_trueCount) {
                    int ib_loop_ub;
                    b_x.set_size(r14.size(0), r14.size(1));
                    ib_loop_ub = r14.size(1);
                    for (int i53{0}; i53 < ib_loop_ub; i53++) {
                        int kb_loop_ub;
                        kb_loop_ub = r14.size(0);
                        for (int i54{0}; i54 < kb_loop_ub; i54++) {
                            b_x[i54 + b_x.size(0) * i53] =
                                (r14[i54 + r14.size(0) * i53] > amax_data[i54]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r14, amax_data, &c_trueCount);
                }
                d_y = false;
                m_k = 0;
                exitg1 = false;
                while ((!exitg1) && (m_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[m_k]) {
                        d_y = true;
                        exitg1 = true;
                    } else {
                        m_k++;
                    }
                }
                if (d_y) {
                    // 'zeroSpeedCurv:103' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:104' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r14.size(0) == c_trueCount) {
                        int nb_loop_ub;
                        int rb_loop_ub;
                        r19.set_size(r14.size(0), r14.size(1));
                        nb_loop_ub = r14.size(1);
                        for (int i60{0}; i60 < nb_loop_ub; i60++) {
                            int i64;
                            int l_scalarLB;
                            int l_vectorUB;
                            int pb_loop_ub;
                            pb_loop_ub = r14.size(0);
                            l_scalarLB = (r14.size(0) / 2) << 1;
                            l_vectorUB = l_scalarLB - 2;
                            for (i64 = 0; i64 <= l_vectorUB; i64 += 2) {
                                __m128d r20;
                                __m128d r21;
                                r20 = _mm_loadu_pd(&r14[i64 + r14.size(0) * i60]);
                                r21 = _mm_loadu_pd(&amax_data[i64]);
                                _mm_storeu_pd(&r19[i64 + r19.size(0) * i60], _mm_sub_pd(r20, r21));
                            }
                            for (i64 = l_scalarLB; i64 < pb_loop_ub; i64++) {
                                r19[i64 + r19.size(0) * i60] =
                                    r14[i64 + r14.size(0) * i60] - amax_data[i64];
                            }
                        }
                        r14.set_size(r19.size(0), r19.size(1));
                        rb_loop_ub = r19.size(1);
                        for (int i63{0}; i63 < rb_loop_ub; i63++) {
                            int sb_loop_ub;
                            sb_loop_ub = r19.size(0);
                            for (int i65{0}; i65 < sb_loop_ub; i65++) {
                                r14[i65 + r14.size(0) * i63] = r19[i65 + r19.size(0) * i63];
                            }
                        }
                        coder::internal::b_maximum(r14, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r14, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    b_jps = jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool e_y;
                    r14.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i58;
                        i58 = J.size(1);
                        for (int n_k{0}; n_k < i58; n_k++) {
                            int i59;
                            i59 = r14.size(0);
                            for (int o_k{0}; o_k < i59; o_k++) {
                                r14[o_k + r14.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (r14.size(0) == d_trueCount) {
                        int ob_loop_ub;
                        b_x.set_size(r14.size(0), r14.size(1));
                        ob_loop_ub = r14.size(1);
                        for (int i61{0}; i61 < ob_loop_ub; i61++) {
                            int qb_loop_ub;
                            qb_loop_ub = r14.size(0);
                            for (int i62{0}; i62 < qb_loop_ub; i62++) {
                                b_x[i62 + b_x.size(0) * i61] =
                                    (r14[i62 + r14.size(0) * i61] > jmax_data[i62]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r14, jmax_data, &d_trueCount);
                    }
                    e_y = false;
                    p_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (p_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[p_k]) {
                            e_y = true;
                            exitg1 = true;
                        } else {
                            p_k++;
                        }
                    }
                    if (e_y) {
                        // 'zeroSpeedCurv:106' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:107' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r14.size(0) == d_trueCount) {
                            int tb_loop_ub;
                            int vb_loop_ub;
                            r22.set_size(r14.size(0), r14.size(1));
                            tb_loop_ub = r14.size(1);
                            for (int i66{0}; i66 < tb_loop_ub; i66++) {
                                int i68;
                                int m_scalarLB;
                                int m_vectorUB;
                                int ub_loop_ub;
                                ub_loop_ub = r14.size(0);
                                m_scalarLB = (r14.size(0) / 2) << 1;
                                m_vectorUB = m_scalarLB - 2;
                                for (i68 = 0; i68 <= m_vectorUB; i68 += 2) {
                                    __m128d r23;
                                    __m128d r24;
                                    r23 = _mm_loadu_pd(&r14[i68 + r14.size(0) * i66]);
                                    r24 = _mm_loadu_pd(&jmax_data[i68]);
                                    _mm_storeu_pd(&r22[i68 + r22.size(0) * i66],
                                                  _mm_sub_pd(r23, r24));
                                }
                                for (i68 = m_scalarLB; i68 < ub_loop_ub; i68++) {
                                    r22[i68 + r22.size(0) * i66] =
                                        r14[i68 + r14.size(0) * i66] - jmax_data[i68];
                                }
                            }
                            r14.set_size(r22.size(0), r22.size(1));
                            vb_loop_ub = r22.size(1);
                            for (int i67{0}; i67 < vb_loop_ub; i67++) {
                                int wb_loop_ub;
                                wb_loop_ub = r22.size(0);
                                for (int i69{0}; i69 < wb_loop_ub; i69++) {
                                    r14[i69 + r14.size(0) * i67] = r22[i69 + r22.size(0) * i67];
                                }
                            }
                            coder::internal::b_maximum(r14, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r14, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        b_jps = jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:109' else
                        // 'zeroSpeedCurv:110' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        jps = b_jps;
    }
    // 'zeroSpeedCurv:38' if( coder.target( "MATLAB" ) )
    // 'zeroSpeedCurv:40' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    // 'zeroSpeedCurv:50' if( k > 0 )
    // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
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
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    // 'constJerkU:33' u( u > 1 ) = 1;
    // 'constJerkU:34' u( u < 0 ) = 0;
    // 'constJerkU:36' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:37' u    = 1 - u;
    // 'constJerkU:38' ud   = ud;
    // 'constJerkU:39' udd  = -udd;
    // 'constJerkU:40' uddd = uddd;
    // 'cutZeroEnd:14' curv2.ConstJerk         = jps;
    curv2->ConstJerk = jps;
    // 'cutZeroEnd:15' curv2.Info.zspdmode     = ZSpdMode.NZ;
    curv2->Info.zspdmode = ZSpdMode_NZ;
    // 'cutZeroEnd:17' curv1                   = curv;
    *curv1 = *curv;
    // 'cutZeroEnd:18' curv1.a_param           = u - curv1.b_param;
    curv1->a_param = u - curv->b_param;
    // 'cutZeroEnd:19' curv1.UseConstJerk      = false;
    curv1->UseConstJerk = false;
    // 'cutZeroEnd:20' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
    curv1->Info.gcode_source_line = curv->Info.gcode_source_line;
    // 'cutZeroEnd:22' if( isAZeroStart( curv ) )
    //  isAZeroStart : Return true if the curv starts with zero speed
    //  curv  : The curve struct
    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
    if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:6' zeroFlag = true;
        // 'cutZeroEnd:23' curv1.Info.zspdmode = ZSpdMode.ZN;
        curv1->Info.zspdmode = ZSpdMode_ZN;
    } else {
        // 'isAZeroStart:8' zeroFlag = false;
        // 'cutZeroEnd:24' else
        // 'cutZeroEnd:25' curv1.Info.zspdmode = ZSpdMode.NN;
        curv1->Info.zspdmode = ZSpdMode_NN;
    }
    // 'cutZeroEnd:28' if( coder.target("MATLAB") )
}

} // namespace ocn

//
// File trailer for cutZeroEnd.cpp
//
// [EOF]
//
