//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:58:50
//

// Include Files
#include "zeroSpeedCurv.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &z1,
                               const double jmax_data[], const int *jmax_size);

static void times(::coder::array<double, 2U> &feed, const ::coder::array<double, 2U> &y,
                  const ::coder::array<double, 2U> &ud);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<bool, 2U> &x
//                const ::coder::array<double, 2U> &z1
//                const double jmax_data[]
//                const int *jmax_size
// Return Type  : void
//
namespace ocn {
static void d_binary_expand_op(::coder::array<bool, 2U> &x, const ::coder::array<double, 2U> &z1,
                               const double jmax_data[], const int *jmax_size)
{
    int b_jmax_idx_0;
    int jmax_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    jmax_idx_0 = *jmax_size;
    if (jmax_idx_0 == 1) {
        b_jmax_idx_0 = z1.size(0);
    } else {
        b_jmax_idx_0 = jmax_idx_0;
    }
    x.set_size(b_jmax_idx_0, z1.size(1));
    stride_0_0 = (z1.size(0) != 1);
    stride_1_0 = (jmax_idx_0 != 1);
    loop_ub = z1.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (jmax_idx_0 == 1) {
            b_loop_ub = z1.size(0);
        } else {
            b_loop_ub = jmax_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            x[i1 + x.size(0) * i] =
                (z1[i1 * stride_0_0 + z1.size(0) * i] > jmax_data[i1 * stride_1_0]);
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &feed
//                const ::coder::array<double, 2U> &y
//                const ::coder::array<double, 2U> &ud
// Return Type  : void
//
static void times(::coder::array<double, 2U> &feed, const ::coder::array<double, 2U> &y,
                  const ::coder::array<double, 2U> &ud)
{
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (ud.size(1) == 1) {
        i = y.size(1);
    } else {
        i = ud.size(1);
    }
    feed.set_size(1, i);
    stride_0_1 = (y.size(1) != 1);
    stride_1_1 = (ud.size(1) != 1);
    if (ud.size(1) == 1) {
        loop_ub = y.size(1);
    } else {
        loop_ub = ud.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        feed[i1] = y[i1 * stride_0_1] * ud[i1 * stride_1_1];
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
//                const Kinematics *ctx_kin
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
                     const Kinematics *ctx_kin, const CurvStruct *curv,
                     ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &ud,
                     ::coder::array<double, 2U> &udd, double *jps)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> c_z1;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> d_z1;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> e_z1;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
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
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_loop_ub;
    int d_trueCount;
    int e_loop_ub;
    int end;
    int end_tmp;
    int f_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int jb_loop_ub;
    int m_loop_ub;
    int nx;
    int o_loop_ub;
    int outsize_idx_0;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:15' uk = 1 - uk ;
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
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
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i2{0}; i2 < trueCount; i2++) {
        ctx_cfg_jmax_data[i2] = ctx_cfg_jmax[tmp_data[i2] - 1];
    }
    b_jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) /
            coder::internal::maximum(z1);
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:29' searchJps = true;
    // 'zeroSpeedCurv:31' ind = 0;
    // 'zeroSpeedCurv:32' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    searchJps = true;
    while (searchJps) {
        double b_k_tmp;
        double c_jps;
        double c_k;
        int b_partialTrueCount;
        int c_end;
        int c_partialTrueCount;
        int cb_loop_ub;
        int d_end;
        int d_partialTrueCount;
        int f_k;
        int g_loop_ub;
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
        int ib_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int lb_loop_ub;
        int n_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int y_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        b_k_tmp = std::pow(6.0 / b_jps, 0.33333333333333331);
        c_k = b_k_tmp / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (c_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            c_loop_ub = static_cast<int>(std::floor(c_k));
            k_vec.set_size(1, c_loop_ub + 1);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (c_loop_ub < c_k) {
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, c_loop_ub + 2);
                for (int i6{0}; i6 <= c_loop_ub; i6++) {
                    k_vec[i6] = i6;
                }
                k_vec[c_loop_ub + 1] = c_k;
            }
        } else {
            // 'zeroSpeedCurv:53' else
            // 'zeroSpeedCurv:54' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:35' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        g_loop_ub = k_vec.size(1);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            y[i10] = b_k_tmp - k_vec[i10] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[0] = 1U;
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r.set_size(1, y.size(1));
        j_loop_ub = y.size(1);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            double c_varargin_1;
            c_varargin_1 = y[i13];
            r[i13] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        k_loop_ub = r.size(1);
        for (int i14{0}; i14 < k_loop_ub; i14++) {
            ud[i14] = b_jps * r[i14] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        l_loop_ub = y.size(1);
        for (int i15{0}; i15 < l_loop_ub; i15++) {
            double d_varargin_1;
            d_varargin_1 = y[i15];
            r[i15] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        n_loop_ub = r.size(1);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            u[i17] = b_jps * r[i17] / 6.0;
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
        p_loop_ub = u.size(1);
        for (int i19{0}; i19 < p_loop_ub; i19++) {
            u[i19] = 1.0 - u[i19];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        q_loop_ub = y.size(1);
        for (int i20{0}; i20 < q_loop_ub; i20++) {
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
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
        if (curv->Info.TRAFO) {
            int r_loop_ub;
            int t_loop_ub;
            int v_loop_ub;
            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            r_loop_ub = c_r1D.size(1) - 1;
            for (int i21{0}; i21 <= r_loop_ub; i21++) {
                int s_loop_ub;
                s_loop_ub = c_r1D.size(0) - 1;
                for (int i22{0}; i22 <= s_loop_ub; i22++) {
                    d_r1D[i22 + d_r1D.size(0) * i21] = c_r1D[i22 + c_r1D.size(0) * i21];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            t_loop_ub = r2D.size(1) - 1;
            for (int i23{0}; i23 <= t_loop_ub; i23++) {
                int u_loop_ub;
                u_loop_ub = r2D.size(0) - 1;
                for (int i24{0}; i24 <= u_loop_ub; i24++) {
                    b_r2D[i24 + b_r2D.size(0) * i23] = r2D[i24 + r2D.size(0) * i23];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            v_loop_ub = r3D.size(1) - 1;
            for (int i25{0}; i25 <= v_loop_ub; i25++) {
                int w_loop_ub;
                w_loop_ub = r3D.size(0) - 1;
                for (int i26{0}; i26 <= w_loop_ub; i26++) {
                    b_r3D[i26 + b_r3D.size(0) * i25] = r3D[i26 + r3D.size(0) * i25];
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
            int x_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            x_loop_ub = c_r1D.size(1);
            for (int i27{0}; i27 < x_loop_ub; i27++) {
                int ab_loop_ub;
                ab_loop_ub = c_r1D.size(0);
                for (int i29{0}; i29 < ab_loop_ub; i29++) {
                    V[i29 + V.size(0) * i27] = c_r1D[i29 + c_r1D.size(0) * i27] * ud[i27];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        y_loop_ub = ud.size(1);
        for (int i28{0}; i28 < y_loop_ub; i28++) {
            double e_varargin_1;
            e_varargin_1 = ud[i28];
            r[i28] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i30 = r.size(1);
        } else {
            i30 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i31 = udd_vec.size(1);
        } else {
            i31 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i30 == i31)) {
            int bb_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            bb_loop_ub = r2D.size(1);
            for (int i32{0}; i32 < bb_loop_ub; i32++) {
                int db_loop_ub;
                db_loop_ub = r2D.size(0);
                for (int i34{0}; i34 < db_loop_ub; i34++) {
                    A[i34 + A.size(0) * i32] = r2D[i34 + r2D.size(0) * i32] * r[i32] +
                                               c_r1D[i34 + c_r1D.size(0) * i32] * udd_vec[i32];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        cb_loop_ub = ud.size(1);
        for (int i33{0}; i33 < cb_loop_ub; i33++) {
            double f_varargin_1;
            f_varargin_1 = ud[i33];
            r[i33] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i35 = ud.size(1);
        } else {
            i35 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i36 = r.size(1);
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
            i40 = r.size(1);
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
            i42 = r.size(1);
        } else {
            i42 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i43 = y.size(1);
        } else {
            i43 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i35 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i36 == i38) && (c_r1D.size(1) == y.size(1)) &&
            (i39 == c_r1D.size(0)) && (i42 == i43)) {
            int eb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            eb_loop_ub = r3D.size(1);
            for (int i44{0}; i44 < eb_loop_ub; i44++) {
                int fb_loop_ub;
                fb_loop_ub = r3D.size(0);
                for (int i45{0}; i45 < fb_loop_ub; i45++) {
                    J[i45 + J.size(0) * i44] =
                        (r3D[i45 + r3D.size(0) * i44] * r[i44] +
                         3.0 * r2D[i45 + r2D.size(0) * i44] * ud[i44] * udd_vec[i44]) +
                        c_r1D[i45 + c_r1D.size(0) * i44] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int gb_loop_ub;
            // 'zeroSpeedCurv:85' else
            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            gb_loop_ub = c_r1D.size(1) - 1;
            for (int i46{0}; i46 <= gb_loop_ub; i46++) {
                int hb_loop_ub;
                hb_loop_ub = c_r1D.size(0) - 1;
                for (int i47{0}; i47 <= hb_loop_ub; i47++) {
                    e_r1D[i47 + e_r1D.size(0) * i46] = c_r1D[i47 + c_r1D.size(0) * i46];
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
        // 'zeroSpeedCurv:92' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
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
        // 'zeroSpeedCurv:93' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
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
        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        ib_loop_ub = c_r1D.size(1);
        for (int i51{0}; i51 < ib_loop_ub; i51++) {
            y[i51] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (0 <= c_r1D.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            jb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int d_k{0}; d_k <= hi; d_k++) {
            xv.set_size(outsize_idx_0);
            for (int i52{0}; i52 < jb_loop_ub; i52++) {
                xv[i52] = 0.0;
            }
            for (int e_k{0}; e_k < nx; e_k++) {
                xv[e_k] = c_r1D[(ctx_cfg_indCart[e_k] + c_r1D.size(0) * d_k) - 1];
            }
            y[d_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int kb_loop_ub;
            feed.set_size(1, y.size(1));
            kb_loop_ub = y.size(1);
            for (int i53{0}; i53 < kb_loop_ub; i53++) {
                feed[i53] = y[i53] * ud[i53];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        lb_loop_ub = feed.size(1);
        for (int i54{0}; i54 < lb_loop_ub; i54++) {
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
            int mb_loop_ub;
            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            for (int i56{0}; i56 < mb_loop_ub; i56++) {
                b_feed[i56] = feed[i56] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            b_z1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i55;
                i55 = V.size(1);
                for (int g_k{0}; g_k < i55; g_k++) {
                    int i57;
                    i57 = b_z1.size(0);
                    for (int h_k{0}; h_k < i57; h_k++) {
                        b_z1[h_k + b_z1.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (b_z1.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(b_z1.size(0), b_z1.size(1));
                nb_loop_ub = b_z1.size(1);
                for (int i58{0}; i58 < nb_loop_ub; i58++) {
                    int ob_loop_ub;
                    ob_loop_ub = b_z1.size(0);
                    for (int i59{0}; i59 < ob_loop_ub; i59++) {
                        b_x[i59 + b_x.size(0) * i58] =
                            (b_z1[i59 + b_z1.size(0) * i58] > vmax_data[i59]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, b_z1, vmax_data, &b_trueCount);
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
                if (b_z1.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int tb_loop_ub;
                    c_z1.set_size(b_z1.size(0), b_z1.size(1));
                    pb_loop_ub = b_z1.size(1);
                    for (int i62{0}; i62 < pb_loop_ub; i62++) {
                        int rb_loop_ub;
                        rb_loop_ub = b_z1.size(0);
                        for (int i64{0}; i64 < rb_loop_ub; i64++) {
                            c_z1[i64 + c_z1.size(0) * i62] =
                                b_z1[i64 + b_z1.size(0) * i62] - vmax_data[i64];
                        }
                    }
                    b_z1.set_size(c_z1.size(0), c_z1.size(1));
                    tb_loop_ub = c_z1.size(1);
                    for (int i66{0}; i66 < tb_loop_ub; i66++) {
                        int ub_loop_ub;
                        ub_loop_ub = c_z1.size(0);
                        for (int i67{0}; i67 < ub_loop_ub; i67++) {
                            b_z1[i67 + b_z1.size(0) * i66] = c_z1[i67 + c_z1.size(0) * i66];
                        }
                    }
                    coder::internal::b_maximum(b_z1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(b_z1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                b_z1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i60;
                    i60 = A.size(1);
                    for (int j_k{0}; j_k < i60; j_k++) {
                        int i61;
                        i61 = b_z1.size(0);
                        for (int k_k{0}; k_k < i61; k_k++) {
                            b_z1[k_k + b_z1.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (b_z1.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(b_z1.size(0), b_z1.size(1));
                    qb_loop_ub = b_z1.size(1);
                    for (int i63{0}; i63 < qb_loop_ub; i63++) {
                        int sb_loop_ub;
                        sb_loop_ub = b_z1.size(0);
                        for (int i65{0}; i65 < sb_loop_ub; i65++) {
                            b_x[i65 + b_x.size(0) * i63] =
                                (b_z1[i65 + b_z1.size(0) * i63] > amax_data[i65]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, b_z1, amax_data, &c_trueCount);
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
                    if (b_z1.size(0) == c_trueCount) {
                        int ac_loop_ub;
                        int vb_loop_ub;
                        d_z1.set_size(b_z1.size(0), b_z1.size(1));
                        vb_loop_ub = b_z1.size(1);
                        for (int i70{0}; i70 < vb_loop_ub; i70++) {
                            int xb_loop_ub;
                            xb_loop_ub = b_z1.size(0);
                            for (int i72{0}; i72 < xb_loop_ub; i72++) {
                                d_z1[i72 + d_z1.size(0) * i70] =
                                    b_z1[i72 + b_z1.size(0) * i70] - amax_data[i72];
                            }
                        }
                        b_z1.set_size(d_z1.size(0), d_z1.size(1));
                        ac_loop_ub = d_z1.size(1);
                        for (int i74{0}; i74 < ac_loop_ub; i74++) {
                            int bc_loop_ub;
                            bc_loop_ub = d_z1.size(0);
                            for (int i75{0}; i75 < bc_loop_ub; i75++) {
                                b_z1[i75 + b_z1.size(0) * i74] = d_z1[i75 + d_z1.size(0) * i74];
                            }
                        }
                        coder::internal::b_maximum(b_z1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(b_z1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    b_z1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i68;
                        i68 = J.size(1);
                        for (int m_k{0}; m_k < i68; m_k++) {
                            int i69;
                            i69 = b_z1.size(0);
                            for (int n_k{0}; n_k < i69; n_k++) {
                                b_z1[n_k + b_z1.size(0) * m_k] = std::abs(J[n_k + J.size(0) * m_k]);
                            }
                        }
                    }
                    if (b_z1.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(b_z1.size(0), b_z1.size(1));
                        wb_loop_ub = b_z1.size(1);
                        for (int i71{0}; i71 < wb_loop_ub; i71++) {
                            int yb_loop_ub;
                            yb_loop_ub = b_z1.size(0);
                            for (int i73{0}; i73 < yb_loop_ub; i73++) {
                                b_x[i73 + b_x.size(0) * i71] =
                                    (b_z1[i73 + b_z1.size(0) * i71] > jmax_data[i73]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, b_z1, jmax_data, &d_trueCount);
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
                        if (b_z1.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            e_z1.set_size(b_z1.size(0), b_z1.size(1));
                            cc_loop_ub = b_z1.size(1);
                            for (int i76{0}; i76 < cc_loop_ub; i76++) {
                                int dc_loop_ub;
                                dc_loop_ub = b_z1.size(0);
                                for (int i77{0}; i77 < dc_loop_ub; i77++) {
                                    e_z1[i77 + e_z1.size(0) * i76] =
                                        b_z1[i77 + b_z1.size(0) * i76] - jmax_data[i77];
                                }
                            }
                            b_z1.set_size(e_z1.size(0), e_z1.size(1));
                            ec_loop_ub = e_z1.size(1);
                            for (int i78{0}; i78 < ec_loop_ub; i78++) {
                                int fc_loop_ub;
                                fc_loop_ub = e_z1.size(0);
                                for (int i79{0}; i79 < fc_loop_ub; i79++) {
                                    b_z1[i79 + b_z1.size(0) * i78] = e_z1[i79 + e_z1.size(0) * i78];
                                }
                            }
                            coder::internal::b_maximum(b_z1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(b_z1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:109' else
                        // 'zeroSpeedCurv:110' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:38' if( coder.target( "MATLAB" ) )
    // 'zeroSpeedCurv:40' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    k_tmp = std::pow(6.0 / b_jps, 0.33333333333333331);
    b_k = k_tmp / ctx_cfg_dt;
    // 'zeroSpeedCurv:50' if( k > 0 )
    if (b_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:51' k_vec = 0 : k;
        b_loop_ub = static_cast<int>(std::floor(b_k));
        k_vec.set_size(1, b_loop_ub + 1);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
        if (b_loop_ub < b_k) {
            // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
            k_vec.set_size(1, b_loop_ub + 2);
            for (int i5{0}; i5 <= b_loop_ub; i5++) {
                k_vec[i5] = i5;
            }
            k_vec[b_loop_ub + 1] = b_k;
        }
    } else {
        // 'zeroSpeedCurv:53' else
        // 'zeroSpeedCurv:54' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
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
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i7{0}; i7 < d_loop_ub; i7++) {
        y[i7] = k_tmp - k_vec[i7] * ctx_cfg_dt;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    e_loop_ub = y.size(1);
    for (int i8{0}; i8 < e_loop_ub; i8++) {
        double varargin_1;
        varargin_1 = y[i8];
        r[i8] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    f_loop_ub = r.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        ud[i9] = b_jps * r[i9] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    h_loop_ub = y.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        double b_varargin_1;
        b_varargin_1 = y[i11];
        r[i11] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    i_loop_ub = r.size(1);
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        u[i12] = b_jps * r[i12] / 6.0;
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
    m_loop_ub = u.size(1);
    for (int i16{0}; i16 < m_loop_ub; i16++) {
        u[i16] = 1.0 - u[i16];
    }
    // 'constJerkU:38' ud   = ud;
    // 'constJerkU:39' udd  = -udd;
    udd.set_size(1, y.size(1));
    o_loop_ub = y.size(1);
    for (int i18{0}; i18 < o_loop_ub; i18++) {
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
//                const Kinematics *ctx_kin
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
                   const Kinematics *ctx_kin, const CurvStruct *curv, ::coder::array<double, 2U> &u,
                   ::coder::array<double, 2U> &ud, ::coder::array<double, 2U> &udd, double *jps)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> c_z1;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> d_z1;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> e_z1;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
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
    double b_ex;
    double b_fmax;
    double b_jps;
    double c_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int ctx_cfg_jmax_size[2];
    unsigned int uv[2];
    int b_end;
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_loop_ub;
    int d_trueCount;
    int end;
    int end_tmp;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int hb_loop_ub;
    int i_loop_ub;
    int iindx;
    int j_loop_ub;
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
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
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
            double d;
            d = z1[b_k - 1];
            if (ex < d) {
                ex = d;
            }
        }
        b_ex = ex;
    }
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i2{0}; i2 < trueCount; i2++) {
        ctx_cfg_jmax_data[i2] = ctx_cfg_jmax[tmp_data[i2] - 1];
    }
    b_jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) / b_ex;
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:29' searchJps = true;
    // 'zeroSpeedCurv:31' ind = 0;
    // 'zeroSpeedCurv:32' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    searchJps = true;
    while (searchJps) {
        double c_jps;
        double d_k;
        int ab_loop_ub;
        int b_partialTrueCount;
        int c_end;
        int c_partialTrueCount;
        int d_end;
        int d_partialTrueCount;
        int e_loop_ub;
        int g_k;
        int gb_loop_ub;
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
        int jb_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int w_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (d_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            c_loop_ub = static_cast<int>(std::floor(d_k));
            k_vec.set_size(1, c_loop_ub + 1);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (c_loop_ub < d_k) {
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, c_loop_ub + 2);
                for (int i7{0}; i7 <= c_loop_ub; i7++) {
                    k_vec[i7] = i7;
                }
                k_vec[c_loop_ub + 1] = d_k;
            }
        } else {
            // 'zeroSpeedCurv:53' else
            // 'zeroSpeedCurv:54' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:35' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:75' if( isempty( ratio ) )
        // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
        y.set_size(1, k_vec.size(1));
        e_loop_ub = k_vec.size(1);
        for (int i8{0}; i8 < e_loop_ub; i8++) {
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
        r.set_size(1, y.size(1));
        k_loop_ub = y.size(1);
        for (int i14{0}; i14 < k_loop_ub; i14++) {
            double c_varargin_1;
            c_varargin_1 = y[i14];
            r[i14] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        l_loop_ub = r.size(1);
        for (int i15{0}; i15 < l_loop_ub; i15++) {
            ud[i15] = b_jps * r[i15] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        m_loop_ub = y.size(1);
        for (int i16{0}; i16 < m_loop_ub; i16++) {
            double d_varargin_1;
            d_varargin_1 = y[i16];
            r[i16] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        n_loop_ub = r.size(1);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            u[i17] = b_jps * r[i17] / 6.0;
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
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i18{0}; i18 < o_loop_ub; i18++) {
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
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
        if (curv->Info.TRAFO) {
            int p_loop_ub;
            int r_loop_ub;
            int t_loop_ub;
            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            p_loop_ub = c_r1D.size(1) - 1;
            for (int i19{0}; i19 <= p_loop_ub; i19++) {
                int q_loop_ub;
                q_loop_ub = c_r1D.size(0) - 1;
                for (int i20{0}; i20 <= q_loop_ub; i20++) {
                    d_r1D[i20 + d_r1D.size(0) * i19] = c_r1D[i20 + c_r1D.size(0) * i19];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            r_loop_ub = r2D.size(1) - 1;
            for (int i21{0}; i21 <= r_loop_ub; i21++) {
                int s_loop_ub;
                s_loop_ub = r2D.size(0) - 1;
                for (int i22{0}; i22 <= s_loop_ub; i22++) {
                    b_r2D[i22 + b_r2D.size(0) * i21] = r2D[i22 + r2D.size(0) * i21];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            t_loop_ub = r3D.size(1) - 1;
            for (int i23{0}; i23 <= t_loop_ub; i23++) {
                int u_loop_ub;
                u_loop_ub = r3D.size(0) - 1;
                for (int i24{0}; i24 <= u_loop_ub; i24++) {
                    b_r3D[i24 + b_r3D.size(0) * i23] = r3D[i24 + r3D.size(0) * i23];
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
            int v_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            v_loop_ub = c_r1D.size(1);
            for (int i25{0}; i25 < v_loop_ub; i25++) {
                int x_loop_ub;
                x_loop_ub = c_r1D.size(0);
                for (int i27{0}; i27 < x_loop_ub; i27++) {
                    V[i27 + V.size(0) * i25] = c_r1D[i27 + c_r1D.size(0) * i25] * ud[i25];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        w_loop_ub = ud.size(1);
        for (int i26{0}; i26 < w_loop_ub; i26++) {
            double e_varargin_1;
            e_varargin_1 = ud[i26];
            r[i26] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i28 = r.size(1);
        } else {
            i28 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i29 = udd_vec.size(1);
        } else {
            i29 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i28 == i29)) {
            int y_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            y_loop_ub = r2D.size(1);
            for (int i30{0}; i30 < y_loop_ub; i30++) {
                int bb_loop_ub;
                bb_loop_ub = r2D.size(0);
                for (int i32{0}; i32 < bb_loop_ub; i32++) {
                    A[i32 + A.size(0) * i30] = r2D[i32 + r2D.size(0) * i30] * r[i30] +
                                               c_r1D[i32 + c_r1D.size(0) * i30] * udd_vec[i30];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        ab_loop_ub = ud.size(1);
        for (int i31{0}; i31 < ab_loop_ub; i31++) {
            double f_varargin_1;
            f_varargin_1 = ud[i31];
            r[i31] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i33 = ud.size(1);
        } else {
            i33 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i34 = r.size(1);
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
            i38 = r.size(1);
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
            i40 = r.size(1);
        } else {
            i40 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i41 = y.size(1);
        } else {
            i41 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i33 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i34 == i36) && (c_r1D.size(1) == y.size(1)) &&
            (i37 == c_r1D.size(0)) && (i40 == i41)) {
            int cb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            cb_loop_ub = r3D.size(1);
            for (int i42{0}; i42 < cb_loop_ub; i42++) {
                int db_loop_ub;
                db_loop_ub = r3D.size(0);
                for (int i43{0}; i43 < db_loop_ub; i43++) {
                    J[i43 + J.size(0) * i42] =
                        (r3D[i43 + r3D.size(0) * i42] * r[i42] +
                         3.0 * r2D[i43 + r2D.size(0) * i42] * ud[i42] * udd_vec[i42]) +
                        c_r1D[i43 + c_r1D.size(0) * i42] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int eb_loop_ub;
            // 'zeroSpeedCurv:85' else
            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            eb_loop_ub = c_r1D.size(1) - 1;
            for (int i44{0}; i44 <= eb_loop_ub; i44++) {
                int fb_loop_ub;
                fb_loop_ub = c_r1D.size(0) - 1;
                for (int i45{0}; i45 <= fb_loop_ub; i45++) {
                    e_r1D[i45 + e_r1D.size(0) * i44] = c_r1D[i45 + c_r1D.size(0) * i44];
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
        // 'zeroSpeedCurv:92' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
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
        // 'zeroSpeedCurv:93' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
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
        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        gb_loop_ub = c_r1D.size(1);
        for (int i49{0}; i49 < gb_loop_ub; i49++) {
            y[i49] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (0 <= c_r1D.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            hb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int e_k{0}; e_k <= hi; e_k++) {
            xv.set_size(outsize_idx_0);
            for (int i50{0}; i50 < hb_loop_ub; i50++) {
                xv[i50] = 0.0;
            }
            for (int f_k{0}; f_k < nx; f_k++) {
                xv[f_k] = c_r1D[(ctx_cfg_indCart[f_k] + c_r1D.size(0) * e_k) - 1];
            }
            y[e_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int ib_loop_ub;
            feed.set_size(1, y.size(1));
            ib_loop_ub = y.size(1);
            for (int i51{0}; i51 < ib_loop_ub; i51++) {
                feed[i51] = y[i51] * ud[i51];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        jb_loop_ub = feed.size(1);
        for (int i52{0}; i52 < jb_loop_ub; i52++) {
            x[i52] = (feed[i52] > b_fmax);
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
            int kb_loop_ub;
            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            kb_loop_ub = feed.size(1);
            for (int i54{0}; i54 < kb_loop_ub; i54++) {
                b_feed[i54] = feed[i54] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool c_y;
            b_z1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i53;
                i53 = V.size(1);
                for (int h_k{0}; h_k < i53; h_k++) {
                    int i55;
                    i55 = b_z1.size(0);
                    for (int i_k{0}; i_k < i55; i_k++) {
                        b_z1[i_k + b_z1.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (b_z1.size(0) == b_trueCount) {
                int lb_loop_ub;
                b_x.set_size(b_z1.size(0), b_z1.size(1));
                lb_loop_ub = b_z1.size(1);
                for (int i56{0}; i56 < lb_loop_ub; i56++) {
                    int mb_loop_ub;
                    mb_loop_ub = b_z1.size(0);
                    for (int i57{0}; i57 < mb_loop_ub; i57++) {
                        b_x[i57 + b_x.size(0) * i56] =
                            (b_z1[i57 + b_z1.size(0) * i56] > vmax_data[i57]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, b_z1, vmax_data, &b_trueCount);
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
                if (b_z1.size(0) == b_trueCount) {
                    int nb_loop_ub;
                    int rb_loop_ub;
                    c_z1.set_size(b_z1.size(0), b_z1.size(1));
                    nb_loop_ub = b_z1.size(1);
                    for (int i60{0}; i60 < nb_loop_ub; i60++) {
                        int pb_loop_ub;
                        pb_loop_ub = b_z1.size(0);
                        for (int i62{0}; i62 < pb_loop_ub; i62++) {
                            c_z1[i62 + c_z1.size(0) * i60] =
                                b_z1[i62 + b_z1.size(0) * i60] - vmax_data[i62];
                        }
                    }
                    b_z1.set_size(c_z1.size(0), c_z1.size(1));
                    rb_loop_ub = c_z1.size(1);
                    for (int i64{0}; i64 < rb_loop_ub; i64++) {
                        int sb_loop_ub;
                        sb_loop_ub = c_z1.size(0);
                        for (int i65{0}; i65 < sb_loop_ub; i65++) {
                            b_z1[i65 + b_z1.size(0) * i64] = c_z1[i65 + c_z1.size(0) * i64];
                        }
                    }
                    coder::internal::b_maximum(b_z1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(b_z1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool d_y;
                b_z1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i58;
                    i58 = A.size(1);
                    for (int k_k{0}; k_k < i58; k_k++) {
                        int i59;
                        i59 = b_z1.size(0);
                        for (int l_k{0}; l_k < i59; l_k++) {
                            b_z1[l_k + b_z1.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (b_z1.size(0) == c_trueCount) {
                    int ob_loop_ub;
                    b_x.set_size(b_z1.size(0), b_z1.size(1));
                    ob_loop_ub = b_z1.size(1);
                    for (int i61{0}; i61 < ob_loop_ub; i61++) {
                        int qb_loop_ub;
                        qb_loop_ub = b_z1.size(0);
                        for (int i63{0}; i63 < qb_loop_ub; i63++) {
                            b_x[i63 + b_x.size(0) * i61] =
                                (b_z1[i63 + b_z1.size(0) * i61] > amax_data[i63]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, b_z1, amax_data, &c_trueCount);
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
                    if (b_z1.size(0) == c_trueCount) {
                        int tb_loop_ub;
                        int xb_loop_ub;
                        d_z1.set_size(b_z1.size(0), b_z1.size(1));
                        tb_loop_ub = b_z1.size(1);
                        for (int i68{0}; i68 < tb_loop_ub; i68++) {
                            int vb_loop_ub;
                            vb_loop_ub = b_z1.size(0);
                            for (int i70{0}; i70 < vb_loop_ub; i70++) {
                                d_z1[i70 + d_z1.size(0) * i68] =
                                    b_z1[i70 + b_z1.size(0) * i68] - amax_data[i70];
                            }
                        }
                        b_z1.set_size(d_z1.size(0), d_z1.size(1));
                        xb_loop_ub = d_z1.size(1);
                        for (int i72{0}; i72 < xb_loop_ub; i72++) {
                            int yb_loop_ub;
                            yb_loop_ub = d_z1.size(0);
                            for (int i73{0}; i73 < yb_loop_ub; i73++) {
                                b_z1[i73 + b_z1.size(0) * i72] = d_z1[i73 + d_z1.size(0) * i72];
                            }
                        }
                        coder::internal::b_maximum(b_z1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(b_z1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool e_y;
                    b_z1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i66;
                        i66 = J.size(1);
                        for (int n_k{0}; n_k < i66; n_k++) {
                            int i67;
                            i67 = b_z1.size(0);
                            for (int o_k{0}; o_k < i67; o_k++) {
                                b_z1[o_k + b_z1.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (b_z1.size(0) == d_trueCount) {
                        int ub_loop_ub;
                        b_x.set_size(b_z1.size(0), b_z1.size(1));
                        ub_loop_ub = b_z1.size(1);
                        for (int i69{0}; i69 < ub_loop_ub; i69++) {
                            int wb_loop_ub;
                            wb_loop_ub = b_z1.size(0);
                            for (int i71{0}; i71 < wb_loop_ub; i71++) {
                                b_x[i71 + b_x.size(0) * i69] =
                                    (b_z1[i71 + b_z1.size(0) * i69] > jmax_data[i71]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, b_z1, jmax_data, &d_trueCount);
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
                        if (b_z1.size(0) == d_trueCount) {
                            int ac_loop_ub;
                            int cc_loop_ub;
                            e_z1.set_size(b_z1.size(0), b_z1.size(1));
                            ac_loop_ub = b_z1.size(1);
                            for (int i74{0}; i74 < ac_loop_ub; i74++) {
                                int bc_loop_ub;
                                bc_loop_ub = b_z1.size(0);
                                for (int i75{0}; i75 < bc_loop_ub; i75++) {
                                    e_z1[i75 + e_z1.size(0) * i74] =
                                        b_z1[i75 + b_z1.size(0) * i74] - jmax_data[i75];
                                }
                            }
                            b_z1.set_size(e_z1.size(0), e_z1.size(1));
                            cc_loop_ub = e_z1.size(1);
                            for (int i76{0}; i76 < cc_loop_ub; i76++) {
                                int dc_loop_ub;
                                dc_loop_ub = e_z1.size(0);
                                for (int i77{0}; i77 < dc_loop_ub; i77++) {
                                    b_z1[i77 + b_z1.size(0) * i76] = e_z1[i77 + e_z1.size(0) * i76];
                                }
                            }
                            coder::internal::b_maximum(b_z1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(b_z1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:109' else
                        // 'zeroSpeedCurv:110' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:38' if( coder.target( "MATLAB" ) )
    // 'zeroSpeedCurv:40' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    c_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:50' if( k > 0 )
    if (c_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:51' k_vec = 0 : k;
        b_loop_ub = static_cast<int>(std::floor(c_k));
        k_vec.set_size(1, b_loop_ub + 1);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
        if (b_loop_ub < c_k) {
            // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
            k_vec.set_size(1, b_loop_ub + 2);
            for (int i6{0}; i6 <= b_loop_ub; i6++) {
                k_vec[i6] = i6;
            }
            k_vec[b_loop_ub + 1] = c_k;
        }
    } else {
        // 'zeroSpeedCurv:53' else
        // 'zeroSpeedCurv:54' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd );
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
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
    f_loop_ub = y.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        udd[i9] = b_jps * y[i9];
    }
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        double varargin_1;
        varargin_1 = y[i10];
        r[i10] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    h_loop_ub = r.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        ud[i11] = b_jps * r[i11] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        double b_varargin_1;
        b_varargin_1 = y[i12];
        r[i12] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    j_loop_ub = r.size(1);
    for (int i13{0}; i13 < j_loop_ub; i13++) {
        u[i13] = b_jps * r[i13] / 6.0;
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
