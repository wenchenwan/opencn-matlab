//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroStart.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "cutZeroStart.h"
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

// Function Definitions
//
// function [ curv1, curv2 ] = cutZeroStart( ctx, curv )
//
// cutZeroStart : Cut the start of the given to handle the zero speed.
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
void cutZeroStart(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
    const ::coder::array<bool, 2U> &ctx_cfg_maskRot, const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, const double ctx_cfg_vmax[6], const double ctx_cfg_amax[6],
    const double ctx_cfg_jmax[6], double ctx_cfg_LSplitZero, double ctx_cfg_dt,
    const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
    const Kinematics *ctx_kin, const CurvStruct *curv, CurvStruct *curv1, CurvStruct *curv2)
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
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D_a;
    ::coder::array<double, 2U> r1D_r;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
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
    int end_tmp;
    int hb_loop_ub;
    int iindx;
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
    // 'cutZeroStart:3' u  = cutCurvStructU( ctx, curv, 0, ctx.cfg.LSplitZero, false );
    u = cutCurvStructU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                       ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                       ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                       curv, ctx_cfg_LSplitZero);
    // 'cutZeroStart:5' if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
    d = curv->b_param + curv->a_param;
    if ((u >= d) || (u <= curv->b_param)) {
        // 'cutZeroStart:6' u = curv.a_param / 2 + curv.b_param;
        u = curv->a_param / 2.0 + curv->b_param;
    }
    // 'cutZeroStart:9' curv1               = curv;
    *curv1 = *curv;
    // 'cutZeroStart:10' curv1.a_param       = u -curv1.b_param;
    curv1->a_param = u - curv1->b_param;
    // 'cutZeroStart:11' curv1.UseConstJerk  = true;
    curv1->UseConstJerk = true;
    // 'cutZeroStart:12' [ ~, ~, ~, jps ]    = zeroSpeedCurv( ctx, curv1, false );
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
    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv1, r0D, r1D);
    b_r1D.set_size(r1D.size(0));
    loop_ub = r1D.size(0);
    for (int i{0}; i < loop_ub; i++) {
        b_r1D[i] = r1D[i];
    }
    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
    if (curv1->Info.TRAFO) {
        int b_loop_ub;
        int c_loop_ub;
        // 'zeroSpeedCurv:20' r1D = ctx.kin.v_joint( r0D, r1D );
        //              if( coder.target( 'MATLAB' ) )
        // 'Kinematics:128' N   = size( r_r, 2 );
        // 'Kinematics:129' v_a = zeros( size( v_r ) );
        b_r1D.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            b_r1D[i1] = 0.0;
        }
        // 'Kinematics:131' for j = 1 : N
        // 'Kinematics:132' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        kin_J_ar_xyzbc(r0D, ctx_kin->parameters, J);
        // 'Kinematics:133' v_a( :, j ) = J * v_r( :, j );
        for (int i3{0}; i3 < 5; i3++) {
            double d1;
            d1 = 0.0;
            for (int i6{0}; i6 < 5; i6++) {
                d1 += J[i6][i3] * r1D[i6];
            }
            b_J[i3] = d1;
        }
        c_loop_ub = r1D.size(0);
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            b_r1D[i5] = b_J[i5];
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
    ctx_cfg_jmax_size[0] = 1;
    ctx_cfg_jmax_size[1] = trueCount;
    for (int i4{0}; i4 < trueCount; i4++) {
        ctx_cfg_jmax_data[i4] = ctx_cfg_jmax[tmp_data[i4] - 1];
    }
    jps = coder::internal::minimum(ctx_cfg_jmax_data, ctx_cfg_jmax_size) /
          coder::internal::maximum(z1);
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:29' searchJps = true;
    // 'zeroSpeedCurv:31' ind = 0;
    // 'zeroSpeedCurv:32' while searchJps
    b_fmax = curv1->Info.FeedRate * 0.5;
    searchJps = true;
    while (searchJps) {
        double b_jps;
        double b_k;
        int b_end;
        int b_partialTrueCount;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int e_k;
        int e_loop_ub;
        int end;
        int f_loop_ub;
        int g_loop_ub;
        int gb_loop_ub;
        int h_loop_ub;
        int hi;
        int i22;
        int i23;
        int i27;
        int i28;
        int i29;
        int i30;
        int i31;
        int i32;
        int i33;
        int i34;
        int i35;
        int i_loop_ub;
        int j_loop_ub;
        int kb_loop_ub;
        int q_loop_ub;
        int s_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        b_k = std::pow(6.0 / jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (b_k > 0.0) {
            int d_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            d_loop_ub = static_cast<int>(std::floor(b_k));
            k_vec.set_size(1, d_loop_ub + 1);
            for (int i7{0}; i7 <= d_loop_ub; i7++) {
                k_vec[i7] = i7;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (d_loop_ub < b_k) {
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, d_loop_ub + 2);
                for (int i8{0}; i8 <= d_loop_ub; i8++) {
                    k_vec[i8] = i8;
                }
                k_vec[d_loop_ub + 1] = b_k;
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
        y.set_size(1, k_vec.size(1));
        e_loop_ub = k_vec.size(1);
        for (int i9{0}; i9 < e_loop_ub; i9++) {
            y[i9] = k_vec[i9] * ctx_cfg_dt;
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
        f_loop_ub = y.size(1);
        for (int i10{0}; i10 < f_loop_ub; i10++) {
            double varargin_1;
            varargin_1 = y[i10];
            r[i10] = std::pow(varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        g_loop_ub = r.size(1);
        for (int i11{0}; i11 < g_loop_ub; i11++) {
            ud[i11] = jps * r[i11] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        h_loop_ub = y.size(1);
        for (int i12{0}; i12 < h_loop_ub; i12++) {
            double b_varargin_1;
            b_varargin_1 = y[i12];
            r[i12] = std::pow(b_varargin_1, 3.0);
        }
        b_u.set_size(1, r.size(1));
        i_loop_ub = r.size(1);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            b_u[i13] = jps * r[i13] / 6.0;
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
        // 'zeroSpeedCurv:79' [ ~, ~, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        j_loop_ub = y.size(1);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            udd_vec[i14] = jps * y[i14];
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
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1, b_u, b_r0D, c_r1D, r2D, r3D);
        // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
        if (curv1->Info.TRAFO) {
            int k_loop_ub;
            int m_loop_ub;
            int o_loop_ub;
            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            k_loop_ub = c_r1D.size(1) - 1;
            for (int i15{0}; i15 <= k_loop_ub; i15++) {
                int l_loop_ub;
                l_loop_ub = c_r1D.size(0) - 1;
                for (int i16{0}; i16 <= l_loop_ub; i16++) {
                    d_r1D[i16 + d_r1D.size(0) * i15] = c_r1D[i16 + c_r1D.size(0) * i15];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            m_loop_ub = r2D.size(1) - 1;
            for (int i17{0}; i17 <= m_loop_ub; i17++) {
                int n_loop_ub;
                n_loop_ub = r2D.size(0) - 1;
                for (int i18{0}; i18 <= n_loop_ub; i18++) {
                    b_r2D[i18 + b_r2D.size(0) * i17] = r2D[i18 + r2D.size(0) * i17];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            o_loop_ub = r3D.size(1) - 1;
            for (int i19{0}; i19 <= o_loop_ub; i19++) {
                int p_loop_ub;
                p_loop_ub = r3D.size(0) - 1;
                for (int i20{0}; i20 <= p_loop_ub; i20++) {
                    b_r3D[i20 + b_r3D.size(0) * i19] = r3D[i20 + r3D.size(0) * i19];
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
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        q_loop_ub = ud.size(1);
        for (int i21{0}; i21 < q_loop_ub; i21++) {
            double c_varargin_1;
            c_varargin_1 = ud[i21];
            r[i21] = std::pow(c_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i22 = r.size(1);
        } else {
            i22 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i23 = udd_vec.size(1);
        } else {
            i23 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i22 == i23)) {
            int r_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            r_loop_ub = r2D.size(1);
            for (int i24{0}; i24 < r_loop_ub; i24++) {
                int t_loop_ub;
                t_loop_ub = r2D.size(0);
                for (int i26{0}; i26 < t_loop_ub; i26++) {
                    A[i26 + A.size(0) * i24] = r2D[i26 + r2D.size(0) * i24] * r[i24] +
                                               c_r1D[i26 + c_r1D.size(0) * i24] * udd_vec[i24];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        s_loop_ub = ud.size(1);
        for (int i25{0}; i25 < s_loop_ub; i25++) {
            double d_varargin_1;
            d_varargin_1 = ud[i25];
            r[i25] = std::pow(d_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i27 = ud.size(1);
        } else {
            i27 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i28 = r.size(1);
        } else {
            i28 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i29 = ud.size(1);
        } else {
            i29 = r2D.size(1);
        }
        if (i29 == 1) {
            i30 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i30 = ud.size(1);
        } else {
            i30 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i31 = r2D.size(0);
        } else {
            i31 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i32 = r.size(1);
        } else {
            i32 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i33 = ud.size(1);
        } else {
            i33 = r2D.size(1);
        }
        if (i32 == 1) {
            if (i33 == 1) {
                i34 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i34 = ud.size(1);
            } else {
                i34 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i34 = r.size(1);
        } else {
            i34 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i35 = y.size(1);
        } else {
            i35 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i27 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i28 == i30) && (c_r1D.size(1) == y.size(1)) &&
            (i31 == c_r1D.size(0)) && (i34 == i35)) {
            int u_loop_ub;
            c_J.set_size(r3D.size(0), r3D.size(1));
            u_loop_ub = r3D.size(1);
            for (int i36{0}; i36 < u_loop_ub; i36++) {
                int v_loop_ub;
                v_loop_ub = r3D.size(0);
                for (int i37{0}; i37 < v_loop_ub; i37++) {
                    c_J[i37 + c_J.size(0) * i36] =
                        (r3D[i37 + r3D.size(0) * i36] * r[i36] +
                         3.0 * r2D[i37 + r2D.size(0) * i36] * ud[i36] * udd_vec[i36]) +
                        c_r1D[i37 + c_r1D.size(0) * i36] * jps;
                }
            }
        } else {
            binary_expand_op(c_J, r3D, r, r2D, ud, udd_vec, c_r1D, jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        h_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1, b_u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
        if (curv1->Info.TRAFO) {
            int cb_loop_ub;
            int i41;
            int x_loop_ub;
            // 'zeroSpeedCurv:84' [ r1D_a ] = ctx.kin.v_joint( r0D, r1D );
            //              if( coder.target( 'MATLAB' ) )
            // 'Kinematics:128' N   = size( r_r, 2 );
            // 'Kinematics:129' v_a = zeros( size( v_r ) );
            uv[0] = static_cast<unsigned int>(c_r1D.size(0));
            r1D_a.set_size(c_r1D.size(0), c_r1D.size(1));
            x_loop_ub = c_r1D.size(1);
            for (int i39{0}; i39 < x_loop_ub; i39++) {
                int ab_loop_ub;
                ab_loop_ub = static_cast<int>(uv[0]);
                for (int i42{0}; i42 < ab_loop_ub; i42++) {
                    r1D_a[i42 + r1D_a.size(0) * i39] = 0.0;
                }
            }
            // 'Kinematics:131' for j = 1 : N
            i41 = b_r0D.size(1);
            for (int j{0}; j < i41; j++) {
                int bb_loop_ub;
                int eb_loop_ub;
                int fb_loop_ub;
                // 'Kinematics:132' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                bb_loop_ub = b_r0D.size(0);
                r0D.set_size(b_r0D.size(0));
                for (int i44{0}; i44 < bb_loop_ub; i44++) {
                    r0D[i44] = b_r0D[i44 + b_r0D.size(0) * j];
                }
                kin_J_ar_xyzbc(r0D, ctx_kin->parameters, J);
                // 'Kinematics:133' v_a( :, j ) = J * v_r( :, j );
                eb_loop_ub = c_r1D.size(0);
                r1D.set_size(c_r1D.size(0));
                for (int i47{0}; i47 < eb_loop_ub; i47++) {
                    r1D[i47] = c_r1D[i47 + c_r1D.size(0) * j];
                }
                for (int i49{0}; i49 < 5; i49++) {
                    double d2;
                    d2 = 0.0;
                    for (int i51{0}; i51 < 5; i51++) {
                        d2 += J[i51][i49] * r1D[i51];
                    }
                    b_J[i49] = d2;
                }
                fb_loop_ub = r1D_a.size(0);
                for (int i50{0}; i50 < fb_loop_ub; i50++) {
                    r1D_a[i50 + r1D_a.size(0) * j] = b_J[i50];
                }
            }
            //              end
            // 'zeroSpeedCurv:85' r1D_r     = r1D;
            r1D_r.set_size(c_r1D.size(0), c_r1D.size(1));
            cb_loop_ub = c_r1D.size(1);
            for (int i45{0}; i45 < cb_loop_ub; i45++) {
                int db_loop_ub;
                db_loop_ub = c_r1D.size(0);
                for (int i46{0}; i46 < db_loop_ub; i46++) {
                    r1D_r[i46 + r1D_r.size(0) * i45] = c_r1D[i46 + c_r1D.size(0) * i45];
                }
            }
        } else {
            int w_loop_ub;
            // 'zeroSpeedCurv:86' else
            // 'zeroSpeedCurv:87' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            ctx_kin->v_relative(b_r0D, c_r1D, r1D_r);
            // 'zeroSpeedCurv:88' r1D_a     = r1D;
            r1D_a.set_size(c_r1D.size(0), c_r1D.size(1));
            w_loop_ub = c_r1D.size(1);
            for (int i38{0}; i38 < w_loop_ub; i38++) {
                int y_loop_ub;
                y_loop_ub = c_r1D.size(0);
                for (int i40{0}; i40 < y_loop_ub; i40++) {
                    r1D_a[i40 + r1D_a.size(0) * i38] = c_r1D[i40 + c_r1D.size(0) * i38];
                }
            }
        }
        // 'zeroSpeedCurv:91' safetyFactor = 0.5;
        // 'zeroSpeedCurv:92' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:93' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
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
        // 'zeroSpeedCurv:94' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int f_i{0}; f_i <= end_tmp; f_i++) {
            if (ctx_cfg_maskTot_data[f_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(f_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i48{0}; i48 < c_trueCount; i48++) {
            amax_data[i48] = ctx_cfg_amax[c_tmp_data[i48] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(g_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i52{0}; i52 < d_trueCount; i52++) {
            jmax_data[i52] = ctx_cfg_jmax[d_tmp_data[i52] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:97' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, r1D_r.size(1));
        gb_loop_ub = r1D_r.size(1);
        for (int i53{0}; i53 < gb_loop_ub; i53++) {
            y[i53] = 0.0;
        }
        hi = r1D_r.size(1) - 1;
        if (0 <= r1D_r.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            hb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int c_k{0}; c_k <= hi; c_k++) {
            xv.set_size(outsize_idx_0);
            for (int i54{0}; i54 < hb_loop_ub; i54++) {
                xv[i54] = 0.0;
            }
            for (int d_k{0}; d_k < nx; d_k++) {
                xv[d_k] = r1D_r[(ctx_cfg_indCart[d_k] + r1D_r.size(0) * c_k) - 1];
            }
            y[c_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int ib_loop_ub;
            feed.set_size(1, y.size(1));
            ib_loop_ub = y.size(1);
            for (int i55{0}; i55 < ib_loop_ub; i55++) {
                feed[i55] = y[i55] * ud[i55];
            }
        } else {
            b_times(feed, y, ud);
        }
        // 'zeroSpeedCurv:98' V     = r1D_a .* ud;
        if (r1D_a.size(1) == ud.size(1)) {
            int jb_loop_ub;
            V.set_size(r1D_a.size(0), r1D_a.size(1));
            jb_loop_ub = r1D_a.size(1);
            for (int i56{0}; i56 < jb_loop_ub; i56++) {
                int lb_loop_ub;
                lb_loop_ub = r1D_a.size(0);
                for (int i58{0}; i58 < lb_loop_ub; i58++) {
                    V[i58 + V.size(0) * i56] = r1D_a[i58 + r1D_a.size(0) * i56] * ud[i56];
                }
            }
        } else {
            times(V, r1D_a, ud);
        }
        // 'zeroSpeedCurv:100' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        kb_loop_ub = feed.size(1);
        for (int i57{0}; i57 < kb_loop_ub; i57++) {
            x[i57] = (feed[i57] > b_fmax);
        }
        b_y = false;
        e_k = 0;
        exitg1 = false;
        while ((!exitg1) && (e_k <= x.size(1) - 1)) {
            if (x[e_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                e_k++;
            }
        }
        if (b_y) {
            int mb_loop_ub;
            // 'zeroSpeedCurv:101' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            for (int i60{0}; i60 < mb_loop_ub; i60++) {
                b_feed[i60] = feed[i60] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int h_k;
            bool c_y;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i59;
                i59 = V.size(1);
                for (int f_k{0}; f_k < i59; f_k++) {
                    int i61;
                    i61 = r1.size(0);
                    for (int g_k{0}; g_k < i61; g_k++) {
                        r1[g_k + r1.size(0) * f_k] = std::abs(V[g_k + V.size(0) * f_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                nb_loop_ub = r1.size(1);
                for (int i62{0}; i62 < nb_loop_ub; i62++) {
                    int ob_loop_ub;
                    ob_loop_ub = r1.size(0);
                    for (int i63{0}; i63 < ob_loop_ub; i63++) {
                        b_x[i63 + b_x.size(0) * i62] =
                            (r1[i63 + r1.size(0) * i62] > vmax_data[i63]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
            }
            c_y = false;
            h_k = 0;
            exitg1 = false;
            while ((!exitg1) && (h_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[h_k]) {
                    c_y = true;
                    exitg1 = true;
                } else {
                    h_k++;
                }
            }
            if (c_y) {
                // 'zeroSpeedCurv:103' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:104' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r1.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int tb_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    pb_loop_ub = r1.size(1);
                    for (int i66{0}; i66 < pb_loop_ub; i66++) {
                        int rb_loop_ub;
                        rb_loop_ub = r1.size(0);
                        for (int i68{0}; i68 < rb_loop_ub; i68++) {
                            r2[i68 + r2.size(0) * i66] =
                                r1[i68 + r1.size(0) * i66] - vmax_data[i68];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    tb_loop_ub = r2.size(1);
                    for (int i70{0}; i70 < tb_loop_ub; i70++) {
                        int ub_loop_ub;
                        ub_loop_ub = r2.size(0);
                        for (int i71{0}; i71 < ub_loop_ub; i71++) {
                            r1[i71 + r1.size(0) * i70] = r2[i71 + r2.size(0) * i70];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int k_k;
                bool d_y;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i64;
                    i64 = A.size(1);
                    for (int i_k{0}; i_k < i64; i_k++) {
                        int i65;
                        i65 = r1.size(0);
                        for (int j_k{0}; j_k < i65; j_k++) {
                            r1[j_k + r1.size(0) * i_k] = std::abs(A[j_k + A.size(0) * i_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    qb_loop_ub = r1.size(1);
                    for (int i67{0}; i67 < qb_loop_ub; i67++) {
                        int sb_loop_ub;
                        sb_loop_ub = r1.size(0);
                        for (int i69{0}; i69 < sb_loop_ub; i69++) {
                            b_x[i69 + b_x.size(0) * i67] =
                                (r1[i69 + r1.size(0) * i67] > amax_data[i69]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
                }
                d_y = false;
                k_k = 0;
                exitg1 = false;
                while ((!exitg1) && (k_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[k_k]) {
                        d_y = true;
                        exitg1 = true;
                    } else {
                        k_k++;
                    }
                }
                if (d_y) {
                    // 'zeroSpeedCurv:106' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:107' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r1.size(0) == c_trueCount) {
                        int ac_loop_ub;
                        int vb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        vb_loop_ub = r1.size(1);
                        for (int i74{0}; i74 < vb_loop_ub; i74++) {
                            int xb_loop_ub;
                            xb_loop_ub = r1.size(0);
                            for (int i76{0}; i76 < xb_loop_ub; i76++) {
                                r3[i76 + r3.size(0) * i74] =
                                    r1[i76 + r1.size(0) * i74] - amax_data[i76];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        ac_loop_ub = r3.size(1);
                        for (int i78{0}; i78 < ac_loop_ub; i78++) {
                            int bc_loop_ub;
                            bc_loop_ub = r3.size(0);
                            for (int i79{0}; i79 < bc_loop_ub; i79++) {
                                r1[i79 + r1.size(0) * i78] = r3[i79 + r3.size(0) * i78];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    b_jps = jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int n_k;
                    bool e_y;
                    r1.set_size(c_J.size(0), c_J.size(1));
                    if ((c_J.size(0) != 0) && (c_J.size(1) != 0)) {
                        int i72;
                        i72 = c_J.size(1);
                        for (int l_k{0}; l_k < i72; l_k++) {
                            int i73;
                            i73 = r1.size(0);
                            for (int m_k{0}; m_k < i73; m_k++) {
                                r1[m_k + r1.size(0) * l_k] = std::abs(c_J[m_k + c_J.size(0) * l_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        wb_loop_ub = r1.size(1);
                        for (int i75{0}; i75 < wb_loop_ub; i75++) {
                            int yb_loop_ub;
                            yb_loop_ub = r1.size(0);
                            for (int i77{0}; i77 < yb_loop_ub; i77++) {
                                b_x[i77 + b_x.size(0) * i75] =
                                    (r1[i77 + r1.size(0) * i75] > jmax_data[i77]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
                    }
                    e_y = false;
                    n_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (n_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[n_k]) {
                            e_y = true;
                            exitg1 = true;
                        } else {
                            n_k++;
                        }
                    }
                    if (e_y) {
                        // 'zeroSpeedCurv:109' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:110' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r1.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            cc_loop_ub = r1.size(1);
                            for (int i80{0}; i80 < cc_loop_ub; i80++) {
                                int dc_loop_ub;
                                dc_loop_ub = r1.size(0);
                                for (int i81{0}; i81 < dc_loop_ub; i81++) {
                                    r4[i81 + r4.size(0) * i80] =
                                        r1[i81 + r1.size(0) * i80] - jmax_data[i81];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            ec_loop_ub = r4.size(1);
                            for (int i82{0}; i82 < ec_loop_ub; i82++) {
                                int fc_loop_ub;
                                fc_loop_ub = r4.size(0);
                                for (int i83{0}; i83 < fc_loop_ub; i83++) {
                                    r1[i83 + r1.size(0) * i82] = r4[i83 + r4.size(0) * i82];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        b_jps = jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(c_J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:112' else
                        // 'zeroSpeedCurv:113' searchJps = false;
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
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    // 'constJerkU:33' u( u > 1 ) = 1;
    // 'constJerkU:34' u( u < 0 ) = 0;
    // 'constJerkU:36' if( isEnd )
    // 'cutZeroStart:13' curv1.ConstJerk     = jps;
    curv1->ConstJerk = jps;
    // 'cutZeroStart:14' curv1.Info.zspdmode = ZSpdMode.ZN;
    curv1->Info.zspdmode = ZSpdMode_ZN;
    // 'cutZeroStart:15' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
    curv1->Info.gcode_source_line = curv->Info.gcode_source_line;
    // 'cutZeroStart:17' curv2               = curv;
    *curv2 = *curv;
    // 'cutZeroStart:18' curv2.UseConstJerk  = false;
    curv2->UseConstJerk = false;
    // 'cutZeroStart:19' curv2.b_param       = u;
    curv2->b_param = u;
    // 'cutZeroStart:20' curv2.a_param       = curv.a_param  + curv.b_param - curv2.b_param;
    curv2->a_param = d - u;
    // 'cutZeroStart:22' if( isAZeroEnd( curv ) )
    //  isAZeroEnd : Return true if the curv ends with zero speed
    //  Input :
    //  curv  : The curve struct
    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
    if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroEnd:7' zeroFlag = true;
        // 'cutZeroStart:23' curv2.Info.zspdmode = ZSpdMode.NZ;
        curv2->Info.zspdmode = ZSpdMode_NZ;
    } else {
        // 'isAZeroEnd:9' zeroFlag = false;
        // 'cutZeroStart:24' else
        // 'cutZeroStart:25' curv2.Info.zspdmode = ZSpdMode.NN;
        curv2->Info.zspdmode = ZSpdMode_NN;
    }
    // 'cutZeroStart:28' if( coder.target("MATLAB") )
}

} // namespace ocn

//
// File trailer for cutZeroStart.cpp
//
// [EOF]
//
