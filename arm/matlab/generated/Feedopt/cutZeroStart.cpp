//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroStart.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
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
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types31.h"
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
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
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
    int cb_loop_ub;
    int d_iindx;
    int d_trueCount;
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
    b_fmax = curv1->Info.FeedRate * 0.5;
    uv[0] = 1U;
    searchJps = true;
    while (searchJps) {
        double b_jps;
        double c_k;
        int b_end;
        int b_partialTrueCount;
        int bb_loop_ub;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int e_loop_ub;
        int eb_loop_ub;
        int end;
        int f_k;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int hi;
        int i24;
        int i25;
        int i29;
        int i30;
        int i31;
        int i32;
        int i33;
        int i34;
        int i35;
        int i36;
        int i37;
        int i_loop_ub;
        int j_loop_ub;
        int r_loop_ub;
        int u_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:33' ind = ind + 1;
        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        c_k = std::pow(6.0 / jps, 0.33333333333333331) / ctx_cfg_dt;
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
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
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
        if (c_r1D.size(1) == ud.size(1)) {
            int q_loop_ub;
            V.set_size(c_r1D.size(0), c_r1D.size(1));
            q_loop_ub = c_r1D.size(1);
            for (int i21{0}; i21 < q_loop_ub; i21++) {
                int s_loop_ub;
                s_loop_ub = c_r1D.size(0);
                for (int i23{0}; i23 < s_loop_ub; i23++) {
                    V[i23 + V.size(0) * i21] = c_r1D[i23 + c_r1D.size(0) * i21] * ud[i21];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        r_loop_ub = ud.size(1);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            double c_varargin_1;
            c_varargin_1 = ud[i22];
            r[i22] = std::pow(c_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i24 = r.size(1);
        } else {
            i24 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i25 = udd_vec.size(1);
        } else {
            i25 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i24 == i25)) {
            int t_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            t_loop_ub = r2D.size(1);
            for (int i26{0}; i26 < t_loop_ub; i26++) {
                int v_loop_ub;
                v_loop_ub = r2D.size(0);
                for (int i28{0}; i28 < v_loop_ub; i28++) {
                    A[i28 + A.size(0) * i26] = r2D[i28 + r2D.size(0) * i26] * r[i26] +
                                               c_r1D[i28 + c_r1D.size(0) * i26] * udd_vec[i26];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        u_loop_ub = ud.size(1);
        for (int i27{0}; i27 < u_loop_ub; i27++) {
            double d_varargin_1;
            d_varargin_1 = ud[i27];
            r[i27] = std::pow(d_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i29 = ud.size(1);
        } else {
            i29 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i30 = r.size(1);
        } else {
            i30 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i31 = ud.size(1);
        } else {
            i31 = r2D.size(1);
        }
        if (i31 == 1) {
            i32 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i32 = ud.size(1);
        } else {
            i32 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i33 = r2D.size(0);
        } else {
            i33 = r3D.size(0);
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
        if (i34 == 1) {
            if (i35 == 1) {
                i36 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i36 = ud.size(1);
            } else {
                i36 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i36 = r.size(1);
        } else {
            i36 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i37 = y.size(1);
        } else {
            i37 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i29 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i30 == i32) && (c_r1D.size(1) == y.size(1)) &&
            (i33 == c_r1D.size(0)) && (i36 == i37)) {
            int w_loop_ub;
            c_J.set_size(r3D.size(0), r3D.size(1));
            w_loop_ub = r3D.size(1);
            for (int i38{0}; i38 < w_loop_ub; i38++) {
                int x_loop_ub;
                x_loop_ub = r3D.size(0);
                for (int i39{0}; i39 < x_loop_ub; i39++) {
                    c_J[i39 + c_J.size(0) * i38] =
                        (r3D[i39 + r3D.size(0) * i38] * r[i38] +
                         3.0 * r2D[i39 + r2D.size(0) * i38] * ud[i38] * udd_vec[i38]) +
                        c_r1D[i39 + c_r1D.size(0) * i38] * jps;
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
        if (!curv1->Info.TRAFO) {
            int y_loop_ub;
            // 'zeroSpeedCurv:85' else
            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            y_loop_ub = c_r1D.size(1) - 1;
            for (int i40{0}; i40 <= y_loop_ub; i40++) {
                int ab_loop_ub;
                ab_loop_ub = c_r1D.size(0) - 1;
                for (int i41{0}; i41 <= ab_loop_ub; i41++) {
                    e_r1D[i41 + e_r1D.size(0) * i40] = c_r1D[i41 + c_r1D.size(0) * i40];
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
        for (int i42{0}; i42 < b_trueCount; i42++) {
            vmax_data[i42] = ctx_cfg_vmax[b_tmp_data[i42] - 1] * 0.5;
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
        for (int i43{0}; i43 < c_trueCount; i43++) {
            amax_data[i43] = ctx_cfg_amax[c_tmp_data[i43] - 1] * 0.5;
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
        for (int i44{0}; i44 < d_trueCount; i44++) {
            jmax_data[i44] = ctx_cfg_jmax[d_tmp_data[i44] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        bb_loop_ub = c_r1D.size(1);
        for (int i45{0}; i45 < bb_loop_ub; i45++) {
            y[i45] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (0 <= c_r1D.size(1) - 1) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            cb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int d_k{0}; d_k <= hi; d_k++) {
            xv.set_size(outsize_idx_0);
            for (int i46{0}; i46 < cb_loop_ub; i46++) {
                xv[i46] = 0.0;
            }
            for (int e_k{0}; e_k < nx; e_k++) {
                xv[e_k] = c_r1D[(ctx_cfg_indCart[e_k] + c_r1D.size(0) * d_k) - 1];
            }
            y[d_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int db_loop_ub;
            feed.set_size(1, y.size(1));
            db_loop_ub = y.size(1);
            for (int i47{0}; i47 < db_loop_ub; i47++) {
                feed[i47] = y[i47] * ud[i47];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        eb_loop_ub = feed.size(1);
        for (int i48{0}; i48 < eb_loop_ub; i48++) {
            x[i48] = (feed[i48] > b_fmax);
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
            int fb_loop_ub;
            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            fb_loop_ub = feed.size(1);
            for (int i50{0}; i50 < fb_loop_ub; i50++) {
                b_feed[i50] = feed[i50] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i49;
                i49 = V.size(1);
                for (int g_k{0}; g_k < i49; g_k++) {
                    int i51;
                    i51 = r1.size(0);
                    for (int h_k{0}; h_k < i51; h_k++) {
                        r1[h_k + r1.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int gb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                gb_loop_ub = r1.size(1);
                for (int i52{0}; i52 < gb_loop_ub; i52++) {
                    int hb_loop_ub;
                    hb_loop_ub = r1.size(0);
                    for (int i53{0}; i53 < hb_loop_ub; i53++) {
                        b_x[i53 + b_x.size(0) * i52] =
                            (r1[i53 + r1.size(0) * i52] > vmax_data[i53]);
                    }
                }
            } else {
                d_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
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
                if (r1.size(0) == b_trueCount) {
                    int ib_loop_ub;
                    int mb_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    ib_loop_ub = r1.size(1);
                    for (int i56{0}; i56 < ib_loop_ub; i56++) {
                        int kb_loop_ub;
                        kb_loop_ub = r1.size(0);
                        for (int i58{0}; i58 < kb_loop_ub; i58++) {
                            r2[i58 + r2.size(0) * i56] =
                                r1[i58 + r1.size(0) * i56] - vmax_data[i58];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    mb_loop_ub = r2.size(1);
                    for (int i60{0}; i60 < mb_loop_ub; i60++) {
                        int nb_loop_ub;
                        nb_loop_ub = r2.size(0);
                        for (int i61{0}; i61 < nb_loop_ub; i61++) {
                            r1[i61 + r1.size(0) * i60] = r2[i61 + r2.size(0) * i60];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i54;
                    i54 = A.size(1);
                    for (int j_k{0}; j_k < i54; j_k++) {
                        int i55;
                        i55 = r1.size(0);
                        for (int k_k{0}; k_k < i55; k_k++) {
                            r1[k_k + r1.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int jb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    jb_loop_ub = r1.size(1);
                    for (int i57{0}; i57 < jb_loop_ub; i57++) {
                        int lb_loop_ub;
                        lb_loop_ub = r1.size(0);
                        for (int i59{0}; i59 < lb_loop_ub; i59++) {
                            b_x[i59 + b_x.size(0) * i57] =
                                (r1[i59 + r1.size(0) * i57] > amax_data[i59]);
                        }
                    }
                } else {
                    d_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
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
                    if (r1.size(0) == c_trueCount) {
                        int ob_loop_ub;
                        int sb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        ob_loop_ub = r1.size(1);
                        for (int i64{0}; i64 < ob_loop_ub; i64++) {
                            int qb_loop_ub;
                            qb_loop_ub = r1.size(0);
                            for (int i66{0}; i66 < qb_loop_ub; i66++) {
                                r3[i66 + r3.size(0) * i64] =
                                    r1[i66 + r1.size(0) * i64] - amax_data[i66];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        sb_loop_ub = r3.size(1);
                        for (int i68{0}; i68 < sb_loop_ub; i68++) {
                            int tb_loop_ub;
                            tb_loop_ub = r3.size(0);
                            for (int i69{0}; i69 < tb_loop_ub; i69++) {
                                r1[i69 + r1.size(0) * i68] = r3[i69 + r3.size(0) * i68];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    b_jps = jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    r1.set_size(c_J.size(0), c_J.size(1));
                    if ((c_J.size(0) != 0) && (c_J.size(1) != 0)) {
                        int i62;
                        i62 = c_J.size(1);
                        for (int m_k{0}; m_k < i62; m_k++) {
                            int i63;
                            i63 = r1.size(0);
                            for (int n_k{0}; n_k < i63; n_k++) {
                                r1[n_k + r1.size(0) * m_k] = std::abs(c_J[n_k + c_J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int pb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        pb_loop_ub = r1.size(1);
                        for (int i65{0}; i65 < pb_loop_ub; i65++) {
                            int rb_loop_ub;
                            rb_loop_ub = r1.size(0);
                            for (int i67{0}; i67 < rb_loop_ub; i67++) {
                                b_x[i67 + b_x.size(0) * i65] =
                                    (r1[i67 + r1.size(0) * i65] > jmax_data[i67]);
                            }
                        }
                    } else {
                        d_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
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
                        if (r1.size(0) == d_trueCount) {
                            int ub_loop_ub;
                            int wb_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            ub_loop_ub = r1.size(1);
                            for (int i70{0}; i70 < ub_loop_ub; i70++) {
                                int vb_loop_ub;
                                vb_loop_ub = r1.size(0);
                                for (int i71{0}; i71 < vb_loop_ub; i71++) {
                                    r4[i71 + r4.size(0) * i70] =
                                        r1[i71 + r1.size(0) * i70] - jmax_data[i71];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            wb_loop_ub = r4.size(1);
                            for (int i72{0}; i72 < wb_loop_ub; i72++) {
                                int xb_loop_ub;
                                xb_loop_ub = r4.size(0);
                                for (int i73{0}; i73 < xb_loop_ub; i73++) {
                                    r1[i73 + r1.size(0) * i72] = r4[i73 + r4.size(0) * i72];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
