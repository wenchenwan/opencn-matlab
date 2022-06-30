//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "cutCurvStructU.h"
#include "kin_J_ar_xyzbc.h"
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
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> c_J;
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
    double J[5][5];
    double amax_data[6];
    double ctx_cfg_jmax_data[6];
    double jmax_data[6];
    double vmax_data[6];
    double b_J[5];
    double a_delta;
    double b_ex;
    double b_fmax;
    double d;
    double f_delta;
    double j_delta;
    double jps;
    double u;
    double v_delta;
    int ctx_cfg_jmax_size[2];
    unsigned int uv[2];
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_trueCount;
    int db_loop_ub;
    int end_tmp;
    int iindx;
    int last;
    int loop_ub;
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
    b_r1D.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        b_r1D[i] = r1D[i];
    }
    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
    if (curv2->Info.TRAFO) {
        int b_loop_ub;
        int c_loop_ub;
        // 'zeroSpeedCurv:20' r1D = ctx.kin.v_joint( r0D, r1D );
        //              if( coder.target( 'MATLAB' ) )
        // 'Kinematics:119' N   = size( r_r, 2 );
        // 'Kinematics:120' v_a = zeros( size( v_r ) );
        b_r1D.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            b_r1D[i1] = 0.0;
        }
        // 'Kinematics:122' for j = 1 : N
        // 'Kinematics:123' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        kin_J_ar_xyzbc(r0D, ctx_kin->parameters, J);
        // 'Kinematics:124' v_a( :, j ) = J * v_r( :, j );
        for (int i3{0}; i3 < 5; i3++) {
            double d1;
            d1 = 0.0;
            for (int i5{0}; i5 < 5; i5++) {
                d1 += J[i5][i3] * r1D[i5];
            }
            b_J[i3] = d1;
        }
        c_loop_ub = r1D.size(0);
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            b_r1D[i4] = b_J[i4];
        }
        //              end
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
    z1.set_size(b_r1D.size(0));
    if (b_r1D.size(0) != 0) {
        int i2;
        i2 = b_r1D.size(0);
        for (int k{0}; k < i2; k++) {
            z1[k] = std::abs(b_r1D[k]);
        }
    }
    last = z1.size(0);
    if (z1.size(0) <= 2) {
        if (z1.size(0) == 1) {
            b_ex = z1[0];
        } else if (z1[0] < z1[z1.size(0) - 1]) {
            b_ex = z1[z1.size(0) - 1];
        } else {
            b_ex = z1[0];
        }
    } else {
        double ex;
        ex = z1[0];
        for (int b_k{2}; b_k <= last; b_k++) {
            double d2;
            d2 = z1[b_k - 1];
            if (ex < d2) {
                ex = d2;
            }
        }
        b_ex = ex;
    }
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i6{0}; i6 < trueCount; i6++) {
        ctx_cfg_jmax_data[i6] = ctx_cfg_jmax[tmp_data[i6] - 1];
    }
    jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) / b_ex;
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
        double c_k;
        double k_tmp;
        int b_end;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
        int c_partialTrueCount;
        int c_scalarLB;
        int c_vectorUB;
        int cb_loop_ub;
        int d_partialTrueCount;
        int d_scalarLB;
        int d_vectorUB;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int end;
        int f_k;
        int f_loop_ub;
        int fb_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int hi;
        int i11;
        int i13;
        int i14;
        int i15;
        int i25;
        int i26;
        int i30;
        int i31;
        int i32;
        int i33;
        int i34;
        int i35;
        int i36;
        int i37;
        int i38;
        int i9;
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int s_loop_ub;
        int scalarLB;
        int v_loop_ub;
        int vectorUB;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        k_tmp = std::pow(6.0 / jps, 0.33333333333333331);
        c_k = k_tmp / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (c_k > 0.0) {
            int d_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            d_loop_ub = static_cast<int>(std::floor(c_k));
            k_vec.set_size(1, d_loop_ub + 1);
            for (int i7{0}; i7 <= d_loop_ub; i7++) {
                k_vec[i7] = i7;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (d_loop_ub < c_k) {
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, d_loop_ub + 2);
                for (int i8{0}; i8 <= d_loop_ub; i8++) {
                    k_vec[i8] = i8;
                }
                k_vec[d_loop_ub + 1] = c_k;
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
        e_loop_ub = k_vec.size(1);
        scalarLB = (k_vec.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i9 = 0; i9 <= vectorUB; i9 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&k_vec[i9]);
            _mm_storeu_pd(&y[i9],
                          _mm_sub_pd(_mm_set1_pd(k_tmp), _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt))));
        }
        for (i9 = scalarLB; i9 < e_loop_ub; i9++) {
            y[i9] = k_tmp - k_vec[i9] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r1.set_size(1, y.size(1));
        f_loop_ub = y.size(1);
        for (int i10{0}; i10 < f_loop_ub; i10++) {
            double varargin_1;
            varargin_1 = y[i10];
            r1[i10] = std::pow(varargin_1, 2.0);
        }
        ud.set_size(1, r1.size(1));
        g_loop_ub = r1.size(1);
        b_scalarLB = (r1.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i11 = 0; i11 <= b_vectorUB; i11 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r1[i11]);
            _mm_storeu_pd(&ud[i11], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
        }
        for (i11 = b_scalarLB; i11 < g_loop_ub; i11++) {
            ud[i11] = jps * r1[i11] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r1.set_size(1, y.size(1));
        h_loop_ub = y.size(1);
        for (int i12{0}; i12 < h_loop_ub; i12++) {
            double b_varargin_1;
            b_varargin_1 = y[i12];
            r1[i12] = std::pow(b_varargin_1, 3.0);
        }
        b_u.set_size(1, r1.size(1));
        i_loop_ub = r1.size(1);
        c_scalarLB = (r1.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i13 = 0; i13 <= c_vectorUB; i13 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r1[i13]);
            _mm_storeu_pd(&b_u[i13],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r3), _mm_set1_pd(6.0)));
        }
        for (i13 = c_scalarLB; i13 < i_loop_ub; i13++) {
            b_u[i13] = jps * r1[i13] / 6.0;
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
        j_loop_ub = b_u.size(1);
        d_scalarLB = (b_u.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i14 = 0; i14 <= d_vectorUB; i14 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&b_u[i14]);
            _mm_storeu_pd(&b_u[i14], _mm_sub_pd(_mm_set1_pd(1.0), r4));
        }
        for (i14 = d_scalarLB; i14 < j_loop_ub; i14++) {
            b_u[i14] = 1.0 - b_u[i14];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        k_loop_ub = y.size(1);
        e_scalarLB = (y.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (i15 = 0; i15 <= e_vectorUB; i15 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&y[i15]);
            _mm_storeu_pd(&udd_vec[i15],
                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jps), r5), _mm_set1_pd(-1.0)));
        }
        for (i15 = e_scalarLB; i15 < k_loop_ub; i15++) {
            udd_vec[i15] = -(jps * y[i15]);
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
            int l_loop_ub;
            int n_loop_ub;
            int p_loop_ub;
            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            l_loop_ub = c_r1D.size(1) - 1;
            for (int i16{0}; i16 <= l_loop_ub; i16++) {
                int m_loop_ub;
                m_loop_ub = c_r1D.size(0) - 1;
                for (int i17{0}; i17 <= m_loop_ub; i17++) {
                    d_r1D[i17 + d_r1D.size(0) * i16] = c_r1D[i17 + c_r1D.size(0) * i16];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            n_loop_ub = r2D.size(1) - 1;
            for (int i18{0}; i18 <= n_loop_ub; i18++) {
                int o_loop_ub;
                o_loop_ub = r2D.size(0) - 1;
                for (int i19{0}; i19 <= o_loop_ub; i19++) {
                    b_r2D[i19 + b_r2D.size(0) * i18] = r2D[i19 + r2D.size(0) * i18];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            p_loop_ub = r3D.size(1) - 1;
            for (int i20{0}; i20 <= p_loop_ub; i20++) {
                int q_loop_ub;
                q_loop_ub = r3D.size(0) - 1;
                for (int i21{0}; i21 <= q_loop_ub; i21++) {
                    b_r3D[i21 + b_r3D.size(0) * i20] = r3D[i21 + r3D.size(0) * i20];
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
            int r_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            r_loop_ub = c_r1D.size(1);
            for (int i22{0}; i22 < r_loop_ub; i22++) {
                int f_scalarLB;
                int f_vectorUB;
                int i24;
                int t_loop_ub;
                t_loop_ub = c_r1D.size(0);
                f_scalarLB = (c_r1D.size(0) / 2) << 1;
                f_vectorUB = f_scalarLB - 2;
                for (i24 = 0; i24 <= f_vectorUB; i24 += 2) {
                    __m128d r6;
                    r6 = _mm_loadu_pd(&c_r1D[i24 + c_r1D.size(0) * i22]);
                    _mm_storeu_pd(&V[i24 + V.size(0) * i22], _mm_mul_pd(r6, _mm_set1_pd(ud[i22])));
                }
                for (i24 = f_scalarLB; i24 < t_loop_ub; i24++) {
                    V[i24 + V.size(0) * i22] = c_r1D[i24 + c_r1D.size(0) * i22] * ud[i22];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r1.set_size(1, ud.size(1));
        s_loop_ub = ud.size(1);
        for (int i23{0}; i23 < s_loop_ub; i23++) {
            double c_varargin_1;
            c_varargin_1 = ud[i23];
            r1[i23] = std::pow(c_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i25 = r1.size(1);
        } else {
            i25 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i26 = udd_vec.size(1);
        } else {
            i26 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r1.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i25 == i26)) {
            int u_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            u_loop_ub = r2D.size(1);
            for (int i27{0}; i27 < u_loop_ub; i27++) {
                int g_scalarLB;
                int g_vectorUB;
                int i29;
                int w_loop_ub;
                w_loop_ub = r2D.size(0);
                g_scalarLB = (r2D.size(0) / 2) << 1;
                g_vectorUB = g_scalarLB - 2;
                for (i29 = 0; i29 <= g_vectorUB; i29 += 2) {
                    __m128d r7;
                    __m128d r8;
                    r7 = _mm_loadu_pd(&r2D[i29 + r2D.size(0) * i27]);
                    r8 = _mm_loadu_pd(&c_r1D[i29 + c_r1D.size(0) * i27]);
                    _mm_storeu_pd(&A[i29 + A.size(0) * i27],
                                  _mm_add_pd(_mm_mul_pd(r7, _mm_set1_pd(r1[i27])),
                                             _mm_mul_pd(r8, _mm_set1_pd(udd_vec[i27]))));
                }
                for (i29 = g_scalarLB; i29 < w_loop_ub; i29++) {
                    A[i29 + A.size(0) * i27] = r2D[i29 + r2D.size(0) * i27] * r1[i27] +
                                               c_r1D[i29 + c_r1D.size(0) * i27] * udd_vec[i27];
                }
            }
        } else {
            binary_expand_op(A, r2D, r1, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r1.set_size(1, ud.size(1));
        v_loop_ub = ud.size(1);
        for (int i28{0}; i28 < v_loop_ub; i28++) {
            double d_varargin_1;
            d_varargin_1 = ud[i28];
            r1[i28] = std::pow(d_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i30 = ud.size(1);
        } else {
            i30 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i31 = r1.size(1);
        } else {
            i31 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i32 = ud.size(1);
        } else {
            i32 = r2D.size(1);
        }
        if (i32 == 1) {
            i33 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i33 = ud.size(1);
        } else {
            i33 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i34 = r2D.size(0);
        } else {
            i34 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i35 = r1.size(1);
        } else {
            i35 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i36 = ud.size(1);
        } else {
            i36 = r2D.size(1);
        }
        if (i35 == 1) {
            if (i36 == 1) {
                i37 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i37 = ud.size(1);
            } else {
                i37 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i37 = r1.size(1);
        } else {
            i37 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i38 = y.size(1);
        } else {
            i38 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i30 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i31 == i33) &&
            (c_r1D.size(1) == y.size(1)) && (i34 == c_r1D.size(0)) && (i37 == i38)) {
            int x_loop_ub;
            c_J.set_size(r3D.size(0), r3D.size(1));
            x_loop_ub = r3D.size(1);
            for (int i39{0}; i39 < x_loop_ub; i39++) {
                int h_scalarLB;
                int h_vectorUB;
                int i40;
                int y_loop_ub;
                y_loop_ub = r3D.size(0);
                h_scalarLB = (r3D.size(0) / 2) << 1;
                h_vectorUB = h_scalarLB - 2;
                for (i40 = 0; i40 <= h_vectorUB; i40 += 2) {
                    __m128d r10;
                    __m128d r11;
                    __m128d r9;
                    r9 = _mm_loadu_pd(&r3D[i40 + r3D.size(0) * i39]);
                    r10 = _mm_loadu_pd(&r2D[i40 + r2D.size(0) * i39]);
                    r11 = _mm_loadu_pd(&c_r1D[i40 + c_r1D.size(0) * i39]);
                    _mm_storeu_pd(
                        &c_J[i40 + c_J.size(0) * i39],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r9, _mm_set1_pd(r1[i39])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r10),
                                                             _mm_set1_pd(ud[i39])),
                                                  _mm_set1_pd(udd_vec[i39]))),
                            _mm_mul_pd(r11, _mm_set1_pd(jps))));
                }
                for (i40 = h_scalarLB; i40 < y_loop_ub; i40++) {
                    c_J[i40 + c_J.size(0) * i39] =
                        (r3D[i40 + r3D.size(0) * i39] * r1[i39] +
                         3.0 * r2D[i40 + r2D.size(0) * i39] * ud[i39] * udd_vec[i39]) +
                        c_r1D[i40 + c_r1D.size(0) * i39] * jps;
                }
            }
        } else {
            binary_expand_op(c_J, r3D, r1, r2D, ud, udd_vec, c_r1D, jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2, b_u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
        if (!curv2->Info.TRAFO) {
            int ab_loop_ub;
            // 'zeroSpeedCurv:85' else
            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            ab_loop_ub = c_r1D.size(1) - 1;
            for (int i41{0}; i41 <= ab_loop_ub; i41++) {
                int bb_loop_ub;
                bb_loop_ub = c_r1D.size(0) - 1;
                for (int i42{0}; i42 <= bb_loop_ub; i42++) {
                    e_r1D[i42 + e_r1D.size(0) * i41] = c_r1D[i42 + c_r1D.size(0) * i41];
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
        for (int i43{0}; i43 < b_trueCount; i43++) {
            vmax_data[i43] = ctx_cfg_vmax[b_tmp_data[i43] - 1] * 0.5;
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
        for (int i44{0}; i44 < c_trueCount; i44++) {
            amax_data[i44] = ctx_cfg_amax[c_tmp_data[i44] - 1] * 0.5;
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
        for (int i45{0}; i45 < d_trueCount; i45++) {
            jmax_data[i45] = ctx_cfg_jmax[d_tmp_data[i45] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        cb_loop_ub = c_r1D.size(1);
        for (int i46{0}; i46 < cb_loop_ub; i46++) {
            y[i46] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (0 <= c_r1D.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            db_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int d_k{0}; d_k <= hi; d_k++) {
            xv.set_size(outsize_idx_0);
            for (int i47{0}; i47 < db_loop_ub; i47++) {
                xv[i47] = 0.0;
            }
            for (int e_k{0}; e_k < nx; e_k++) {
                xv[e_k] = c_r1D[(ctx_cfg_indCart[e_k] + c_r1D.size(0) * d_k) - 1];
            }
            y[d_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int eb_loop_ub;
            int i48;
            int i_scalarLB;
            int i_vectorUB;
            feed.set_size(1, y.size(1));
            eb_loop_ub = y.size(1);
            i_scalarLB = (y.size(1) / 2) << 1;
            i_vectorUB = i_scalarLB - 2;
            for (i48 = 0; i48 <= i_vectorUB; i48 += 2) {
                __m128d r12;
                __m128d r13;
                r12 = _mm_loadu_pd(&y[i48]);
                r13 = _mm_loadu_pd(&ud[i48]);
                _mm_storeu_pd(&feed[i48], _mm_mul_pd(r12, r13));
            }
            for (i48 = i_scalarLB; i48 < eb_loop_ub; i48++) {
                feed[i48] = y[i48] * ud[i48];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        fb_loop_ub = feed.size(1);
        for (int i49{0}; i49 < fb_loop_ub; i49++) {
            x[i49] = (feed[i49] > b_fmax);
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
            int gb_loop_ub;
            int i52;
            int j_scalarLB;
            int j_vectorUB;
            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            gb_loop_ub = feed.size(1);
            j_scalarLB = (feed.size(1) / 2) << 1;
            j_vectorUB = j_scalarLB - 2;
            for (i52 = 0; i52 <= j_vectorUB; i52 += 2) {
                __m128d r15;
                r15 = _mm_loadu_pd(&feed[i52]);
                _mm_storeu_pd(&b_feed[i52], _mm_sub_pd(r15, _mm_set1_pd(b_fmax)));
            }
            for (i52 = j_scalarLB; i52 < gb_loop_ub; i52++) {
                b_feed[i52] = feed[i52] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r14.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i50;
                i50 = V.size(1);
                for (int g_k{0}; g_k < i50; g_k++) {
                    int i51;
                    i51 = r14.size(0);
                    for (int h_k{0}; h_k < i51; h_k++) {
                        r14[h_k + r14.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r14.size(0) == b_trueCount) {
                int hb_loop_ub;
                b_x.set_size(r14.size(0), r14.size(1));
                hb_loop_ub = r14.size(1);
                for (int i53{0}; i53 < hb_loop_ub; i53++) {
                    int ib_loop_ub;
                    ib_loop_ub = r14.size(0);
                    for (int i54{0}; i54 < ib_loop_ub; i54++) {
                        b_x[i54 + b_x.size(0) * i53] =
                            (r14[i54 + r14.size(0) * i53] > vmax_data[i54]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r14, vmax_data, &b_trueCount);
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
                // 'zeroSpeedCurv:100' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:101' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r14.size(0) == b_trueCount) {
                    int jb_loop_ub;
                    int nb_loop_ub;
                    r16.set_size(r14.size(0), r14.size(1));
                    jb_loop_ub = r14.size(1);
                    for (int i57{0}; i57 < jb_loop_ub; i57++) {
                        int i61;
                        int k_scalarLB;
                        int k_vectorUB;
                        int lb_loop_ub;
                        lb_loop_ub = r14.size(0);
                        k_scalarLB = (r14.size(0) / 2) << 1;
                        k_vectorUB = k_scalarLB - 2;
                        for (i61 = 0; i61 <= k_vectorUB; i61 += 2) {
                            __m128d r17;
                            __m128d r18;
                            r17 = _mm_loadu_pd(&r14[i61 + r14.size(0) * i57]);
                            r18 = _mm_loadu_pd(&vmax_data[i61]);
                            _mm_storeu_pd(&r16[i61 + r16.size(0) * i57], _mm_sub_pd(r17, r18));
                        }
                        for (i61 = k_scalarLB; i61 < lb_loop_ub; i61++) {
                            r16[i61 + r16.size(0) * i57] =
                                r14[i61 + r14.size(0) * i57] - vmax_data[i61];
                        }
                    }
                    r14.set_size(r16.size(0), r16.size(1));
                    nb_loop_ub = r16.size(1);
                    for (int i60{0}; i60 < nb_loop_ub; i60++) {
                        int ob_loop_ub;
                        ob_loop_ub = r16.size(0);
                        for (int i62{0}; i62 < ob_loop_ub; i62++) {
                            r14[i62 + r14.size(0) * i60] = r16[i62 + r16.size(0) * i60];
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
                int l_k;
                bool d_y;
                r14.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i55;
                    i55 = A.size(1);
                    for (int j_k{0}; j_k < i55; j_k++) {
                        int i56;
                        i56 = r14.size(0);
                        for (int k_k{0}; k_k < i56; k_k++) {
                            r14[k_k + r14.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r14.size(0) == c_trueCount) {
                    int kb_loop_ub;
                    b_x.set_size(r14.size(0), r14.size(1));
                    kb_loop_ub = r14.size(1);
                    for (int i58{0}; i58 < kb_loop_ub; i58++) {
                        int mb_loop_ub;
                        mb_loop_ub = r14.size(0);
                        for (int i59{0}; i59 < mb_loop_ub; i59++) {
                            b_x[i59 + b_x.size(0) * i58] =
                                (r14[i59 + r14.size(0) * i58] > amax_data[i59]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r14, amax_data, &c_trueCount);
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
                    // 'zeroSpeedCurv:103' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:104' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r14.size(0) == c_trueCount) {
                        int pb_loop_ub;
                        int tb_loop_ub;
                        r19.set_size(r14.size(0), r14.size(1));
                        pb_loop_ub = r14.size(1);
                        for (int i65{0}; i65 < pb_loop_ub; i65++) {
                            int i69;
                            int l_scalarLB;
                            int l_vectorUB;
                            int rb_loop_ub;
                            rb_loop_ub = r14.size(0);
                            l_scalarLB = (r14.size(0) / 2) << 1;
                            l_vectorUB = l_scalarLB - 2;
                            for (i69 = 0; i69 <= l_vectorUB; i69 += 2) {
                                __m128d r20;
                                __m128d r21;
                                r20 = _mm_loadu_pd(&r14[i69 + r14.size(0) * i65]);
                                r21 = _mm_loadu_pd(&amax_data[i69]);
                                _mm_storeu_pd(&r19[i69 + r19.size(0) * i65], _mm_sub_pd(r20, r21));
                            }
                            for (i69 = l_scalarLB; i69 < rb_loop_ub; i69++) {
                                r19[i69 + r19.size(0) * i65] =
                                    r14[i69 + r14.size(0) * i65] - amax_data[i69];
                            }
                        }
                        r14.set_size(r19.size(0), r19.size(1));
                        tb_loop_ub = r19.size(1);
                        for (int i68{0}; i68 < tb_loop_ub; i68++) {
                            int ub_loop_ub;
                            ub_loop_ub = r19.size(0);
                            for (int i70{0}; i70 < ub_loop_ub; i70++) {
                                r14[i70 + r14.size(0) * i68] = r19[i70 + r19.size(0) * i68];
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
                    int o_k;
                    bool e_y;
                    r14.set_size(c_J.size(0), c_J.size(1));
                    if ((c_J.size(0) != 0) && (c_J.size(1) != 0)) {
                        int i63;
                        i63 = c_J.size(1);
                        for (int m_k{0}; m_k < i63; m_k++) {
                            int i64;
                            i64 = r14.size(0);
                            for (int n_k{0}; n_k < i64; n_k++) {
                                r14[n_k + r14.size(0) * m_k] =
                                    std::abs(c_J[n_k + c_J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r14.size(0) == d_trueCount) {
                        int qb_loop_ub;
                        b_x.set_size(r14.size(0), r14.size(1));
                        qb_loop_ub = r14.size(1);
                        for (int i66{0}; i66 < qb_loop_ub; i66++) {
                            int sb_loop_ub;
                            sb_loop_ub = r14.size(0);
                            for (int i67{0}; i67 < sb_loop_ub; i67++) {
                                b_x[i67 + b_x.size(0) * i66] =
                                    (r14[i67 + r14.size(0) * i66] > jmax_data[i67]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r14, jmax_data, &d_trueCount);
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
                        // 'zeroSpeedCurv:106' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:107' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r14.size(0) == d_trueCount) {
                            int vb_loop_ub;
                            int xb_loop_ub;
                            r22.set_size(r14.size(0), r14.size(1));
                            vb_loop_ub = r14.size(1);
                            for (int i71{0}; i71 < vb_loop_ub; i71++) {
                                int i73;
                                int m_scalarLB;
                                int m_vectorUB;
                                int wb_loop_ub;
                                wb_loop_ub = r14.size(0);
                                m_scalarLB = (r14.size(0) / 2) << 1;
                                m_vectorUB = m_scalarLB - 2;
                                for (i73 = 0; i73 <= m_vectorUB; i73 += 2) {
                                    __m128d r23;
                                    __m128d r24;
                                    r23 = _mm_loadu_pd(&r14[i73 + r14.size(0) * i71]);
                                    r24 = _mm_loadu_pd(&jmax_data[i73]);
                                    _mm_storeu_pd(&r22[i73 + r22.size(0) * i71],
                                                  _mm_sub_pd(r23, r24));
                                }
                                for (i73 = m_scalarLB; i73 < wb_loop_ub; i73++) {
                                    r22[i73 + r22.size(0) * i71] =
                                        r14[i73 + r14.size(0) * i71] - jmax_data[i73];
                                }
                            }
                            r14.set_size(r22.size(0), r22.size(1));
                            xb_loop_ub = r22.size(1);
                            for (int i72{0}; i72 < xb_loop_ub; i72++) {
                                int yb_loop_ub;
                                yb_loop_ub = r22.size(0);
                                for (int i74{0}; i74 < yb_loop_ub; i74++) {
                                    r14[i74 + r14.size(0) * i72] = r22[i74 + r22.size(0) * i72];
                                }
                            }
                            coder::internal::b_maximum(r14, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r14, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        b_jps = jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(c_J[d_iindx - 1])));
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
