//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
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
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const double ctx_cfg_amax[6]
//                const double ctx_cfg_jmax[6]
//                double ctx_cfg_LSplitZero
//                double ctx_cfg_dt
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
namespace ocn {
void cutZeroEnd(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                const CurvStruct *curv, CurvStruct *curv1, CurvStruct *curv2)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> c_z1;
    ::coder::array<double, 2U> d_z1;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> ud_vec;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> b_V;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> xv;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    double amax_data[6];
    double jmax_data[6];
    double a_delta;
    double b_ex;
    double d_ex;
    double j_delta;
    double jps;
    double u;
    double v_delta;
    unsigned int uv[2];
    int b_iindx;
    int c_iindx;
    int iindx;
    int last;
    int nx;
    int outsize_idx_0;
    int r_loop_ub;
    bool searchJps;
    // 'cutZeroEnd:3' u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
    u = b_cutCurvStructU(
        ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_indCart_data,
        ctx_cfg_indCart_size, ctx_cfg_indRot_data, ctx_cfg_indRot_size, ctx_cfg_indTot_data,
        ctx_cfg_indTot_size, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv->Info.Type,
        curv->R0, curv->R1, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
        curv->CoeffP5, curv->sp_index, curv->a_param, curv->b_param, ctx_cfg_LSplitZero);
    // 'cutZeroEnd:5' if( u >= 1 )
    if (u >= 1.0) {
        // 'cutZeroEnd:6' u = curv.a_param / 2 + curv.b_param;
        u = curv->a_param / 2.0 + curv->b_param;
    }
    // 'cutZeroEnd:8' curv2                   = curv;
    *curv2 = *curv;
    // 'cutZeroEnd:9' curv2.UseConstJerk      = true;
    curv2->UseConstJerk = true;
    // 'cutZeroEnd:10' curv2.b_param           = u;
    curv2->b_param = u;
    // 'cutZeroEnd:11' curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
    curv2->a_param = (curv->a_param + curv->b_param) - u;
    // 'cutZeroEnd:12' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
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
    // 'zeroSpeedCurv:13' uk = 0;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:15' uk = 1 - uk ;
    // 'zeroSpeedCurv:17' [ ~, r1D ] = EvalCurvStruct( ctx, curv, uk );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size, curv->Info.Type,
                     curv->R0, curv->R1, curv->CorrectedHelixCenter, curv->evec, curv->theta,
                     curv->pitch, curv->CoeffP5, curv->sp_index, curv2->a_param, u, a__1, r1D);
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:20' jps = min( ctx.cfg.jmax( ctx.cfg.indTot ) ) / max( abs( r1D ) );
    z1.set_size(r1D.size(0));
    if (r1D.size(0) != 0) {
        int i;
        i = r1D.size(0);
        for (int k{0}; k < i; k++) {
            z1[k] = std::abs(r1D[k]);
        }
    }
    if (ctx_cfg_indTot_size <= 2) {
        if (ctx_cfg_indTot_size == 1) {
            b_ex = ctx_cfg_jmax[ctx_cfg_indTot_data[0] - 1];
        } else {
            double d;
            double d1;
            d = ctx_cfg_jmax[ctx_cfg_indTot_data[0] - 1];
            d1 = ctx_cfg_jmax[ctx_cfg_indTot_data[ctx_cfg_indTot_size - 1] - 1];
            if (d > d1) {
                b_ex = d1;
            } else {
                b_ex = d;
            }
        }
    } else {
        double ex;
        ex = ctx_cfg_jmax[ctx_cfg_indTot_data[0] - 1];
        for (int b_k{2}; b_k <= ctx_cfg_indTot_size; b_k++) {
            double d2;
            d2 = ctx_cfg_jmax[ctx_cfg_indTot_data[b_k - 1] - 1];
            if (ex > d2) {
                ex = d2;
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
            double d3;
            d3 = z1[c_k - 1];
            if (c_ex < d3) {
                c_ex = d3;
            }
        }
        d_ex = c_ex;
    }
    jps = b_ex / d_ex;
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:25' searchJps = true;
    // 'zeroSpeedCurv:27' ind = 0;
    // 'zeroSpeedCurv:28' while searchJps
    for (int i1{0}; i1 < ctx_cfg_indTot_size; i1++) {
        amax_data[i1] = ctx_cfg_amax[ctx_cfg_indTot_data[i1] - 1];
        jmax_data[i1] = ctx_cfg_jmax[ctx_cfg_indTot_data[i1] - 1];
    }
    searchJps = true;
    while (searchJps) {
        double b_jps;
        double d_k;
        double k_tmp;
        int b_end;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
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
        int i14;
        int i15;
        int i19;
        int i20;
        int i21;
        int i22;
        int i23;
        int i24;
        int i25;
        int i26;
        int i27;
        int i4;
        int i6;
        int i7;
        int i9;
        int j_loop_ub;
        int m_loop_ub;
        int q_loop_ub;
        int s_loop_ub;
        int scalarLB;
        int vectorUB;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:29' ind = ind + 1;
        // 'zeroSpeedCurv:30' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:55' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        k_tmp = std::pow(6.0 / jps, 0.33333333333333331);
        d_k = k_tmp / ctx_cfg_dt;
        // 'zeroSpeedCurv:57' if( k > 0 )
        if (d_k > 0.0) {
            // 'zeroSpeedCurv:58' k_vec = 1 : k;
            if (d_k < 1.0) {
                k_vec.set_size(1, 0);
            } else {
                int loop_ub;
                loop_ub = static_cast<int>(std::floor(d_k - 1.0));
                k_vec.set_size(1, loop_ub + 1);
                for (int i2{0}; i2 <= loop_ub; i2++) {
                    k_vec[i2] = static_cast<double>(i2) + 1.0;
                }
            }
            // 'zeroSpeedCurv:59' if( k_vec( end ) < k )
            if (k_vec[k_vec.size(1) - 1] < d_k) {
                int i3;
                // 'zeroSpeedCurv:59' k_vec = [ k_vec, k ];
                i3 = k_vec.size(1);
                k_vec.set_size(k_vec.size(0), k_vec.size(1) + 1);
                k_vec[i3] = d_k;
            }
        } else {
            // 'zeroSpeedCurv:60' else
            // 'zeroSpeedCurv:61' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:31' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:82' if( isempty( ratio ) )
        // 'zeroSpeedCurv:84' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
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
        b_loop_ub = k_vec.size(1);
        scalarLB = (k_vec.size(1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i4 = 0; i4 <= vectorUB; i4 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&k_vec[i4]);
            _mm_storeu_pd(&y[i4],
                          _mm_sub_pd(_mm_set1_pd(k_tmp), _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt))));
        }
        for (i4 = scalarLB; i4 < b_loop_ub; i4++) {
            y[i4] = k_tmp - k_vec[i4] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[0] = 1U;
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r1.set_size(1, y.size(1));
        c_loop_ub = y.size(1);
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            double varargin_1;
            varargin_1 = y[i5];
            r1[i5] = std::pow(varargin_1, 3.0);
        }
        b_u.set_size(1, r1.size(1));
        d_loop_ub = r1.size(1);
        b_scalarLB = (r1.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i6 = 0; i6 <= b_vectorUB; i6 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r1[i6]);
            _mm_storeu_pd(&b_u[i6], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(6.0)));
        }
        for (i6 = b_scalarLB; i6 < d_loop_ub; i6++) {
            b_u[i6] = jps * r1[i6] / 6.0;
        }
        // 'constJerkU:33' u( u > 1 ) = 1;
        end = b_u.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (b_u[b_i] > 1.0) {
                b_u[b_i] = 1.0;
            }
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        b_end = b_u.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (b_u[c_i] < 0.0) {
                b_u[c_i] = 0.0;
            }
        }
        // 'constJerkU:36' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:37' u    = 1 - u;
        b_u.set_size(1, b_u.size(1));
        e_loop_ub = b_u.size(1);
        c_scalarLB = (b_u.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i7 = 0; i7 <= c_vectorUB; i7 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&b_u[i7]);
            _mm_storeu_pd(&b_u[i7], _mm_sub_pd(_mm_set1_pd(1.0), r3));
        }
        for (i7 = c_scalarLB; i7 < e_loop_ub; i7++) {
            b_u[i7] = 1.0 - b_u[i7];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:86' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        r1.set_size(1, y.size(1));
        f_loop_ub = y.size(1);
        for (int i8{0}; i8 < f_loop_ub; i8++) {
            double b_varargin_1;
            b_varargin_1 = y[i8];
            r1[i8] = std::pow(b_varargin_1, 2.0);
        }
        ud_vec.set_size(1, r1.size(1));
        g_loop_ub = r1.size(1);
        d_scalarLB = (r1.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i9 = 0; i9 <= d_vectorUB; i9 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r1[i9]);
            _mm_storeu_pd(&ud_vec[i9],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r4), _mm_set1_pd(2.0)));
        }
        for (i9 = d_scalarLB; i9 < g_loop_ub; i9++) {
            ud_vec[i9] = jps * r1[i9] / 2.0;
        }
        udd_vec.set_size(1, y.size(1));
        h_loop_ub = y.size(1);
        e_scalarLB = (y.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (i10 = 0; i10 <= e_vectorUB; i10 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&y[i10]);
            _mm_storeu_pd(&udd_vec[i10],
                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jps), r5), _mm_set1_pd(-1.0)));
        }
        for (i10 = e_scalarLB; i10 < h_loop_ub; i10++) {
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
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         curv->Info.Type, curv->R0, curv->R1, curv->CorrectedHelixCenter,
                         curv->evec, curv->theta, curv->pitch, curv->CoeffP5, curv->sp_index,
                         curv2->a_param, u, b_u, a__2, b_r1D, r2D, r3D);
        // 'calcRVAJfromU:18' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
        // 'calcRVAJfromU:19'                           udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
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
        if (b_r1D.size(1) == ud_vec.size(1)) {
            int i_loop_ub;
            V.set_size(b_r1D.size(0), b_r1D.size(1));
            i_loop_ub = b_r1D.size(1);
            for (int i11{0}; i11 < i_loop_ub; i11++) {
                int f_scalarLB;
                int f_vectorUB;
                int i13;
                int k_loop_ub;
                k_loop_ub = b_r1D.size(0);
                f_scalarLB = (b_r1D.size(0) / 2) << 1;
                f_vectorUB = f_scalarLB - 2;
                for (i13 = 0; i13 <= f_vectorUB; i13 += 2) {
                    __m128d r6;
                    r6 = _mm_loadu_pd(&b_r1D[i13 + b_r1D.size(0) * i11]);
                    _mm_storeu_pd(&V[i13 + V.size(0) * i11],
                                  _mm_mul_pd(r6, _mm_set1_pd(ud_vec[i11])));
                }
                for (i13 = f_scalarLB; i13 < k_loop_ub; i13++) {
                    V[i13 + V.size(0) * i11] = b_r1D[i13 + b_r1D.size(0) * i11] * ud_vec[i11];
                }
            }
        } else {
            times(V, b_r1D, ud_vec);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r1.set_size(1, ud_vec.size(1));
        j_loop_ub = ud_vec.size(1);
        for (int i12{0}; i12 < j_loop_ub; i12++) {
            double c_varargin_1;
            c_varargin_1 = ud_vec[i12];
            r1[i12] = std::pow(c_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i14 = r1.size(1);
        } else {
            i14 = r2D.size(1);
        }
        if (b_r1D.size(1) == 1) {
            i15 = udd_vec.size(1);
        } else {
            i15 = b_r1D.size(1);
        }
        if ((r2D.size(1) == r1.size(1)) && (b_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == b_r1D.size(0)) && (i14 == i15)) {
            int l_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            l_loop_ub = r2D.size(1);
            for (int i16{0}; i16 < l_loop_ub; i16++) {
                int g_scalarLB;
                int g_vectorUB;
                int i18;
                int n_loop_ub;
                n_loop_ub = r2D.size(0);
                g_scalarLB = (r2D.size(0) / 2) << 1;
                g_vectorUB = g_scalarLB - 2;
                for (i18 = 0; i18 <= g_vectorUB; i18 += 2) {
                    __m128d r7;
                    __m128d r8;
                    r7 = _mm_loadu_pd(&r2D[i18 + r2D.size(0) * i16]);
                    r8 = _mm_loadu_pd(&b_r1D[i18 + b_r1D.size(0) * i16]);
                    _mm_storeu_pd(&A[i18 + A.size(0) * i16],
                                  _mm_add_pd(_mm_mul_pd(r7, _mm_set1_pd(r1[i16])),
                                             _mm_mul_pd(r8, _mm_set1_pd(udd_vec[i16]))));
                }
                for (i18 = g_scalarLB; i18 < n_loop_ub; i18++) {
                    A[i18 + A.size(0) * i16] = r2D[i18 + r2D.size(0) * i16] * r1[i16] +
                                               b_r1D[i18 + b_r1D.size(0) * i16] * udd_vec[i16];
                }
            }
        } else {
            binary_expand_op(A, r2D, r1, b_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r1.set_size(1, ud_vec.size(1));
        m_loop_ub = ud_vec.size(1);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            double d_varargin_1;
            d_varargin_1 = ud_vec[i17];
            r1[i17] = std::pow(d_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i19 = ud_vec.size(1);
        } else {
            i19 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i20 = r1.size(1);
        } else {
            i20 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i21 = ud_vec.size(1);
        } else {
            i21 = r2D.size(1);
        }
        if (i21 == 1) {
            i22 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i22 = ud_vec.size(1);
        } else {
            i22 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i23 = r2D.size(0);
        } else {
            i23 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i24 = r1.size(1);
        } else {
            i24 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i25 = ud_vec.size(1);
        } else {
            i25 = r2D.size(1);
        }
        if (i24 == 1) {
            if (i25 == 1) {
                i26 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i26 = ud_vec.size(1);
            } else {
                i26 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i26 = r1.size(1);
        } else {
            i26 = r3D.size(1);
        }
        if (b_r1D.size(1) == 1) {
            i27 = y.size(1);
        } else {
            i27 = b_r1D.size(1);
        }
        if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud_vec.size(1)) &&
            (i19 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i20 == i22) &&
            (b_r1D.size(1) == y.size(1)) && (i23 == b_r1D.size(0)) && (i26 == i27)) {
            int o_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            o_loop_ub = r3D.size(1);
            for (int i28{0}; i28 < o_loop_ub; i28++) {
                int h_scalarLB;
                int h_vectorUB;
                int i30;
                int p_loop_ub;
                p_loop_ub = r3D.size(0);
                h_scalarLB = (r3D.size(0) / 2) << 1;
                h_vectorUB = h_scalarLB - 2;
                for (i30 = 0; i30 <= h_vectorUB; i30 += 2) {
                    __m128d r10;
                    __m128d r11;
                    __m128d r9;
                    r9 = _mm_loadu_pd(&r3D[i30 + r3D.size(0) * i28]);
                    r10 = _mm_loadu_pd(&r2D[i30 + r2D.size(0) * i28]);
                    r11 = _mm_loadu_pd(&b_r1D[i30 + b_r1D.size(0) * i28]);
                    _mm_storeu_pd(
                        &J[i30 + J.size(0) * i28],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r9, _mm_set1_pd(r1[i28])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r10),
                                                             _mm_set1_pd(ud_vec[i28])),
                                                  _mm_set1_pd(udd_vec[i28]))),
                            _mm_mul_pd(r11, _mm_set1_pd(jps))));
                }
                for (i30 = h_scalarLB; i30 < p_loop_ub; i30++) {
                    J[i30 + J.size(0) * i28] =
                        (r3D[i30 + r3D.size(0) * i28] * r1[i28] +
                         3.0 * r2D[i30 + r2D.size(0) * i28] * ud_vec[i28] * udd_vec[i28]) +
                        b_r1D[i30 + b_r1D.size(0) * i28] * jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r1, r2D, ud_vec, udd_vec, b_r1D, jps, uv);
        }
        // 'zeroSpeedCurv:88' amax =  ctx.cfg.amax( ctx.cfg.indTot )';
        // 'zeroSpeedCurv:89' jmax =  ctx.cfg.jmax( ctx.cfg.indTot )';
        // 'zeroSpeedCurv:91' if( any( vecnorm( V ) > curv.Info.FeedRate ) )
        r1.set_size(1, V.size(1));
        q_loop_ub = V.size(1);
        for (int i29{0}; i29 < q_loop_ub; i29++) {
            r1[i29] = 0.0;
        }
        hi = V.size(1);
        if (0 <= V.size(1) - 1) {
            nx = V.size(0);
            outsize_idx_0 = V.size(0);
            r_loop_ub = V.size(0);
        }
        for (int e_k{0}; e_k < hi; e_k++) {
            xv.set_size(outsize_idx_0);
            for (int i31{0}; i31 < r_loop_ub; i31++) {
                xv[i31] = 0.0;
            }
            for (int f_k{0}; f_k < nx; f_k++) {
                xv[f_k] = V[f_k + V.size(0) * e_k];
            }
            r1[e_k] = coder::b_norm(xv);
        }
        x.set_size(1, r1.size(1));
        s_loop_ub = r1.size(1);
        for (int i32{0}; i32 < s_loop_ub; i32++) {
            x[i32] = (r1[i32] > curv->Info.FeedRate);
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
            int i35;
            int i_scalarLB;
            int i_vectorUB;
            int t_loop_ub;
            int w_loop_ub;
            // 'zeroSpeedCurv:92' [ v_delta, ind ] = max( vecnorm( V ) - curv.Info.FeedRate );
            r1.set_size(1, r1.size(1));
            t_loop_ub = r1.size(1);
            i_scalarLB = (r1.size(1) / 2) << 1;
            i_vectorUB = i_scalarLB - 2;
            for (i35 = 0; i35 <= i_vectorUB; i35 += 2) {
                __m128d r12;
                r12 = _mm_loadu_pd(&r1[i35]);
                _mm_storeu_pd(&r1[i35], _mm_sub_pd(r12, _mm_set1_pd(curv->Info.FeedRate)));
            }
            for (i35 = i_scalarLB; i35 < t_loop_ub; i35++) {
                r1[i35] = r1[i35] - curv->Info.FeedRate;
            }
            coder::internal::maximum(r1, &v_delta, &iindx);
            // 'zeroSpeedCurv:93' jps = jps * ( 1 - ratio * ( 1 - v_delta / vecnorm( V( :, ind ) ) )
            // );
            w_loop_ub = V.size(0);
            b_V.set_size(V.size(0));
            for (int i38{0}; i38 < w_loop_ub; i38++) {
                b_V[i38] = V[i38 + V.size(0) * (iindx - 1)];
            }
            b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / coder::b_norm(b_V)));
        } else {
            int j_k;
            bool c_y;
            b_z1.set_size(A.size(0), A.size(1));
            if ((A.size(0) != 0) && (A.size(1) != 0)) {
                int i33;
                i33 = A.size(1);
                for (int h_k{0}; h_k < i33; h_k++) {
                    int i34;
                    i34 = b_z1.size(0);
                    for (int i_k{0}; i_k < i34; i_k++) {
                        b_z1[i_k + b_z1.size(0) * h_k] = std::abs(A[i_k + A.size(0) * h_k]);
                    }
                }
            }
            if (b_z1.size(0) == ctx_cfg_indTot_size) {
                int u_loop_ub;
                b_x.set_size(b_z1.size(0), b_z1.size(1));
                u_loop_ub = b_z1.size(1);
                for (int i36{0}; i36 < u_loop_ub; i36++) {
                    int v_loop_ub;
                    v_loop_ub = b_z1.size(0);
                    for (int i37{0}; i37 < v_loop_ub; i37++) {
                        b_x[i37 + b_x.size(0) * i36] =
                            (b_z1[i37 + b_z1.size(0) * i36] > amax_data[i37]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, b_z1, amax_data, &ctx_cfg_indTot_size);
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
                // 'zeroSpeedCurv:94' elseif( any( abs( A ) > amax, 'all' ) )
                // 'zeroSpeedCurv:95' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                if (b_z1.size(0) == ctx_cfg_indTot_size) {
                    int cb_loop_ub;
                    int x_loop_ub;
                    c_z1.set_size(b_z1.size(0), b_z1.size(1));
                    x_loop_ub = b_z1.size(1);
                    for (int i41{0}; i41 < x_loop_ub; i41++) {
                        int ab_loop_ub;
                        int i45;
                        int j_scalarLB;
                        int j_vectorUB;
                        ab_loop_ub = b_z1.size(0);
                        j_scalarLB = (b_z1.size(0) / 2) << 1;
                        j_vectorUB = j_scalarLB - 2;
                        for (i45 = 0; i45 <= j_vectorUB; i45 += 2) {
                            __m128d r13;
                            __m128d r14;
                            r13 = _mm_loadu_pd(&b_z1[i45 + b_z1.size(0) * i41]);
                            r14 = _mm_loadu_pd(&amax_data[i45]);
                            _mm_storeu_pd(&c_z1[i45 + c_z1.size(0) * i41], _mm_sub_pd(r13, r14));
                        }
                        for (i45 = j_scalarLB; i45 < ab_loop_ub; i45++) {
                            c_z1[i45 + c_z1.size(0) * i41] =
                                b_z1[i45 + b_z1.size(0) * i41] - amax_data[i45];
                        }
                    }
                    b_z1.set_size(c_z1.size(0), c_z1.size(1));
                    cb_loop_ub = c_z1.size(1);
                    for (int i44{0}; i44 < cb_loop_ub; i44++) {
                        int db_loop_ub;
                        db_loop_ub = c_z1.size(0);
                        for (int i46{0}; i46 < db_loop_ub; i46++) {
                            b_z1[i46 + b_z1.size(0) * i44] = c_z1[i46 + c_z1.size(0) * i44];
                        }
                    }
                    coder::internal::b_maximum(b_z1, &a_delta, &b_iindx);
                } else {
                    binary_expand_op(b_z1, amax_data, &ctx_cfg_indTot_size, &a_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:96' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) ) ) );
                b_jps = jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[b_iindx - 1])));
            } else {
                int m_k;
                bool d_y;
                b_z1.set_size(J.size(0), J.size(1));
                if ((J.size(0) != 0) && (J.size(1) != 0)) {
                    int i39;
                    i39 = J.size(1);
                    for (int k_k{0}; k_k < i39; k_k++) {
                        int i40;
                        i40 = b_z1.size(0);
                        for (int l_k{0}; l_k < i40; l_k++) {
                            b_z1[l_k + b_z1.size(0) * k_k] = std::abs(J[l_k + J.size(0) * k_k]);
                        }
                    }
                }
                if (b_z1.size(0) == ctx_cfg_indTot_size) {
                    int y_loop_ub;
                    b_x.set_size(b_z1.size(0), b_z1.size(1));
                    y_loop_ub = b_z1.size(1);
                    for (int i42{0}; i42 < y_loop_ub; i42++) {
                        int bb_loop_ub;
                        bb_loop_ub = b_z1.size(0);
                        for (int i43{0}; i43 < bb_loop_ub; i43++) {
                            b_x[i43 + b_x.size(0) * i42] =
                                (b_z1[i43 + b_z1.size(0) * i42] > jmax_data[i43]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, b_z1, jmax_data, &ctx_cfg_indTot_size);
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
                    // 'zeroSpeedCurv:97' elseif( any( abs( J ) > jmax, 'all' ) )
                    // 'zeroSpeedCurv:98' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                    if (b_z1.size(0) == ctx_cfg_indTot_size) {
                        int eb_loop_ub;
                        int gb_loop_ub;
                        d_z1.set_size(b_z1.size(0), b_z1.size(1));
                        eb_loop_ub = b_z1.size(1);
                        for (int i47{0}; i47 < eb_loop_ub; i47++) {
                            int fb_loop_ub;
                            int i49;
                            int k_scalarLB;
                            int k_vectorUB;
                            fb_loop_ub = b_z1.size(0);
                            k_scalarLB = (b_z1.size(0) / 2) << 1;
                            k_vectorUB = k_scalarLB - 2;
                            for (i49 = 0; i49 <= k_vectorUB; i49 += 2) {
                                __m128d r15;
                                __m128d r16;
                                r15 = _mm_loadu_pd(&b_z1[i49 + b_z1.size(0) * i47]);
                                r16 = _mm_loadu_pd(&jmax_data[i49]);
                                _mm_storeu_pd(&d_z1[i49 + d_z1.size(0) * i47],
                                              _mm_sub_pd(r15, r16));
                            }
                            for (i49 = k_scalarLB; i49 < fb_loop_ub; i49++) {
                                d_z1[i49 + d_z1.size(0) * i47] =
                                    b_z1[i49 + b_z1.size(0) * i47] - jmax_data[i49];
                            }
                        }
                        b_z1.set_size(d_z1.size(0), d_z1.size(1));
                        gb_loop_ub = d_z1.size(1);
                        for (int i48{0}; i48 < gb_loop_ub; i48++) {
                            int hb_loop_ub;
                            hb_loop_ub = d_z1.size(0);
                            for (int i50{0}; i50 < hb_loop_ub; i50++) {
                                b_z1[i50 + b_z1.size(0) * i48] = d_z1[i50 + d_z1.size(0) * i48];
                            }
                        }
                        coder::internal::b_maximum(b_z1, &j_delta, &c_iindx);
                    } else {
                        binary_expand_op(b_z1, jmax_data, &ctx_cfg_indTot_size, &j_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind ) )
                    // ) );
                    b_jps = jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[c_iindx - 1])));
                } else {
                    // 'zeroSpeedCurv:100' else
                    // 'zeroSpeedCurv:101' searchJps = false;
                    searchJps = false;
                }
            }
        }
        jps = b_jps;
    }
    // 'zeroSpeedCurv:33' jps = jps /2;
    jps /= 2.0;
    // 'zeroSpeedCurv:34' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:55' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    // 'zeroSpeedCurv:57' if( k > 0 )
    // 'zeroSpeedCurv:35' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
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
    //  [ k ]               = computeContinuityMat( ctx, curv, u, ud, udd, isEnd );
    //
    //  if( k > 1 )
    //      u   = u( k );
    //      ud  = ud( k );
    //      udd = udd( k );
    //      break;
    //  else
    //      jps = jps / 2;
    //  end
    //
    //  end
    // 'cutZeroEnd:13' curv2.ConstJerk         = jps;
    curv2->ConstJerk = jps;
    // 'cutZeroEnd:14' curv2.Info.zspdmode     = ZSpdMode.NZ;
    curv2->Info.zspdmode = ZSpdMode_NZ;
    // 'cutZeroEnd:16' curv1                   = curv;
    *curv1 = *curv;
    // 'cutZeroEnd:17' curv1.a_param           = u - curv1.b_param;
    curv1->a_param = u - curv->b_param;
    // 'cutZeroEnd:18' curv1.UseConstJerk      = false;
    curv1->UseConstJerk = false;
    // 'cutZeroEnd:19' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
    curv1->Info.gcode_source_line = curv->Info.gcode_source_line;
    // 'cutZeroEnd:21' if( isAZeroStart( curv ) )
    //  isAZeroStart : Return true if the curv starts with zero speed
    //  curv  : The curve struct
    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
    if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:6' zeroFlag = true;
        // 'cutZeroEnd:22' curv1.Info.zspdmode = ZSpdMode.ZN;
        curv1->Info.zspdmode = ZSpdMode_ZN;
    } else {
        // 'isAZeroStart:8' zeroFlag = false;
        // 'cutZeroEnd:23' else
        // 'cutZeroEnd:24' curv1.Info.zspdmode = ZSpdMode.NN;
        curv1->Info.zspdmode = ZSpdMode_NN;
    }
    // 'cutZeroEnd:27' if( coder.target("MATLAB") )
}

} // namespace ocn

//
// File trailer for cutZeroEnd.cpp
//
// [EOF]
//
