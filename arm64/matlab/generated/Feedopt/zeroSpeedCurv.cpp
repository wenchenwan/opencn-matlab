//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
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

// Function Declarations
namespace ocn {
static void e_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
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
static void e_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
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
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> xv;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    double ctx_cfg_jmax_data[6];
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
    int d_trueCount;
    int end;
    int end_tmp;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int iindx;
    int j_loop_ub;
    int k_loop_ub;
    int lb_loop_ub;
    int nx;
    int o_loop_ub;
    int outsize_idx_0;
    int partialTrueCount;
    int q_loop_ub;
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
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double b_k_tmp;
        double c_jps;
        double c_k;
        int b_partialTrueCount;
        int bb_loop_ub;
        int c_end;
        int c_partialTrueCount;
        int d_end;
        int d_partialTrueCount;
        int eb_loop_ub;
        int f_k;
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
        int kb_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int nb_loop_ub;
        int p_loop_ub;
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
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            y[i10] = b_k_tmp - k_vec[i10] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[0] = 1U;
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        r.set_size(1, y.size(1));
        l_loop_ub = y.size(1);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            double c_varargin_1;
            c_varargin_1 = y[i13];
            r[i13] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        m_loop_ub = r.size(1);
        for (int i14{0}; i14 < m_loop_ub; i14++) {
            ud[i14] = b_jps * r[i14] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        n_loop_ub = y.size(1);
        for (int i15{0}; i15 < n_loop_ub; i15++) {
            double d_varargin_1;
            d_varargin_1 = y[i15];
            r[i15] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        p_loop_ub = r.size(1);
        for (int i17{0}; i17 < p_loop_ub; i17++) {
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
        r_loop_ub = u.size(1);
        for (int i19{0}; i19 < r_loop_ub; i19++) {
            u[i19] = 1.0 - u[i19];
        }
        // 'constJerkU:38' ud   = ud;
        // 'constJerkU:39' udd  = -udd;
        // 'constJerkU:40' uddd = uddd;
        // 'zeroSpeedCurv:81' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        s_loop_ub = y.size(1);
        for (int i20{0}; i20 < s_loop_ub; i20++) {
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
                cb_loop_ub = c_r1D.size(0);
                for (int i29{0}; i29 < cb_loop_ub; i29++) {
                    V[i29 + V.size(0) * i27] = c_r1D[i29 + c_r1D.size(0) * i27] * ud[i27];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        bb_loop_ub = ud.size(1);
        for (int i28{0}; i28 < bb_loop_ub; i28++) {
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
            int db_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            db_loop_ub = r2D.size(1);
            for (int i32{0}; i32 < db_loop_ub; i32++) {
                int fb_loop_ub;
                fb_loop_ub = r2D.size(0);
                for (int i34{0}; i34 < fb_loop_ub; i34++) {
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
        eb_loop_ub = ud.size(1);
        for (int i33{0}; i33 < eb_loop_ub; i33++) {
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
            int gb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            gb_loop_ub = r3D.size(1);
            for (int i44{0}; i44 < gb_loop_ub; i44++) {
                int hb_loop_ub;
                hb_loop_ub = r3D.size(0);
                for (int i45{0}; i45 < hb_loop_ub; i45++) {
                    J[i45 + J.size(0) * i44] =
                        (r3D[i45 + r3D.size(0) * i44] * r[i44] +
                         3.0 * r2D[i45 + r2D.size(0) * i44] * ud[i44] * udd_vec[i44]) +
                        c_r1D[i45 + c_r1D.size(0) * i44] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
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
            feed.set_size(1, y.size(1));
            mb_loop_ub = y.size(1);
            for (int i53{0}; i53 < mb_loop_ub; i53++) {
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
            int ob_loop_ub;
            // 'zeroSpeedCurv:102' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            ob_loop_ub = feed.size(1);
            for (int i56{0}; i56 < ob_loop_ub; i56++) {
                b_feed[i56] = feed[i56] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:103' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i55;
                i55 = V.size(1);
                for (int g_k{0}; g_k < i55; g_k++) {
                    int i57;
                    i57 = r1.size(0);
                    for (int h_k{0}; h_k < i57; h_k++) {
                        r1[h_k + r1.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int pb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                pb_loop_ub = r1.size(1);
                for (int i58{0}; i58 < pb_loop_ub; i58++) {
                    int qb_loop_ub;
                    qb_loop_ub = r1.size(0);
                    for (int i59{0}; i59 < qb_loop_ub; i59++) {
                        b_x[i59 + b_x.size(0) * i58] =
                            (r1[i59 + r1.size(0) * i58] > vmax_data[i59]);
                    }
                }
            } else {
                e_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
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
                if (r1.size(0) == b_trueCount) {
                    int rb_loop_ub;
                    int ub_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    rb_loop_ub = r1.size(1);
                    for (int i61{0}; i61 < rb_loop_ub; i61++) {
                        int tb_loop_ub;
                        tb_loop_ub = r1.size(0);
                        for (int i64{0}; i64 < tb_loop_ub; i64++) {
                            r2[i64 + r2.size(0) * i61] =
                                r1[i64 + r1.size(0) * i61] - vmax_data[i64];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    ub_loop_ub = r2.size(1);
                    for (int i65{0}; i65 < ub_loop_ub; i65++) {
                        int wb_loop_ub;
                        wb_loop_ub = r2.size(0);
                        for (int i67{0}; i67 < wb_loop_ub; i67++) {
                            r1[i67 + r1.size(0) * i65] = r2[i67 + r2.size(0) * i65];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:106' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i60;
                    i60 = A.size(1);
                    for (int j_k{0}; j_k < i60; j_k++) {
                        int i62;
                        i62 = r1.size(0);
                        for (int k_k{0}; k_k < i62; k_k++) {
                            r1[k_k + r1.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int sb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    sb_loop_ub = r1.size(1);
                    for (int i63{0}; i63 < sb_loop_ub; i63++) {
                        int vb_loop_ub;
                        vb_loop_ub = r1.size(0);
                        for (int i66{0}; i66 < vb_loop_ub; i66++) {
                            b_x[i66 + b_x.size(0) * i63] =
                                (r1[i66 + r1.size(0) * i63] > amax_data[i66]);
                        }
                    }
                } else {
                    e_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
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
                    if (r1.size(0) == c_trueCount) {
                        int bc_loop_ub;
                        int xb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        xb_loop_ub = r1.size(1);
                        for (int i69{0}; i69 < xb_loop_ub; i69++) {
                            int ac_loop_ub;
                            ac_loop_ub = r1.size(0);
                            for (int i72{0}; i72 < ac_loop_ub; i72++) {
                                r3[i72 + r3.size(0) * i69] =
                                    r1[i72 + r1.size(0) * i69] - amax_data[i72];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        bc_loop_ub = r3.size(1);
                        for (int i73{0}; i73 < bc_loop_ub; i73++) {
                            int dc_loop_ub;
                            dc_loop_ub = r3.size(0);
                            for (int i75{0}; i75 < dc_loop_ub; i75++) {
                                r1[i75 + r1.size(0) * i73] = r3[i75 + r3.size(0) * i73];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:109' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i68;
                        i68 = J.size(1);
                        for (int m_k{0}; m_k < i68; m_k++) {
                            int i70;
                            i70 = r1.size(0);
                            for (int n_k{0}; n_k < i70; n_k++) {
                                r1[n_k + r1.size(0) * m_k] = std::abs(J[n_k + J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int yb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        yb_loop_ub = r1.size(1);
                        for (int i71{0}; i71 < yb_loop_ub; i71++) {
                            int cc_loop_ub;
                            cc_loop_ub = r1.size(0);
                            for (int i74{0}; i74 < cc_loop_ub; i74++) {
                                b_x[i74 + b_x.size(0) * i71] =
                                    (r1[i74 + r1.size(0) * i71] > jmax_data[i74]);
                            }
                        }
                    } else {
                        e_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
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
                        if (r1.size(0) == d_trueCount) {
                            int ec_loop_ub;
                            int gc_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            ec_loop_ub = r1.size(1);
                            for (int i76{0}; i76 < ec_loop_ub; i76++) {
                                int fc_loop_ub;
                                fc_loop_ub = r1.size(0);
                                for (int i77{0}; i77 < fc_loop_ub; i77++) {
                                    r4[i77 + r4.size(0) * i76] =
                                        r1[i77 + r1.size(0) * i76] - jmax_data[i77];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            gc_loop_ub = r4.size(1);
                            for (int i78{0}; i78 < gc_loop_ub; i78++) {
                                int hc_loop_ub;
                                hc_loop_ub = r4.size(0);
                                for (int i79{0}; i79 < hc_loop_ub; i79++) {
                                    r1[i79 + r1.size(0) * i78] = r4[i79 + r4.size(0) * i78];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    for (int i7{0}; i7 < f_loop_ub; i7++) {
        y[i7] = k_tmp - k_vec[i7] * ctx_cfg_dt;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    for (int i8{0}; i8 < g_loop_ub; i8++) {
        double varargin_1;
        varargin_1 = y[i8];
        r[i8] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    h_loop_ub = r.size(1);
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        ud[i9] = b_jps * r[i9] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    j_loop_ub = y.size(1);
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        double b_varargin_1;
        b_varargin_1 = y[i11];
        r[i11] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    k_loop_ub = r.size(1);
    for (int i12{0}; i12 < k_loop_ub; i12++) {
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
    o_loop_ub = u.size(1);
    for (int i16{0}; i16 < o_loop_ub; i16++) {
        u[i16] = 1.0 - u[i16];
    }
    // 'constJerkU:38' ud   = ud;
    // 'constJerkU:39' udd  = -udd;
    udd.set_size(1, y.size(1));
    q_loop_ub = y.size(1);
    for (int i18{0}; i18 < q_loop_ub; i18++) {
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
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> xv;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    double ctx_cfg_jmax_data[6];
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
    int c_trueCount;
    int d_iindx;
    int d_loop_ub;
    int d_trueCount;
    int end;
    int end_tmp;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int j_loop_ub;
    int jb_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
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
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
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
        int lb_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
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
        for (int i8{0}; i8 < g_loop_ub; i8++) {
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
        m_loop_ub = y.size(1);
        for (int i14{0}; i14 < m_loop_ub; i14++) {
            double c_varargin_1;
            c_varargin_1 = y[i14];
            r[i14] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        n_loop_ub = r.size(1);
        for (int i15{0}; i15 < n_loop_ub; i15++) {
            ud[i15] = b_jps * r[i15] / 2.0;
        }
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i16{0}; i16 < o_loop_ub; i16++) {
            double d_varargin_1;
            d_varargin_1 = y[i16];
            r[i16] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        p_loop_ub = r.size(1);
        for (int i17{0}; i17 < p_loop_ub; i17++) {
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
        // 'zeroSpeedCurv:81' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        q_loop_ub = y.size(1);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
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
                ab_loop_ub = c_r1D.size(0);
                for (int i27{0}; i27 < ab_loop_ub; i27++) {
                    V[i27 + V.size(0) * i25] = c_r1D[i27 + c_r1D.size(0) * i25] * ud[i25];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        y_loop_ub = ud.size(1);
        for (int i26{0}; i26 < y_loop_ub; i26++) {
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
            int bb_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            bb_loop_ub = r2D.size(1);
            for (int i30{0}; i30 < bb_loop_ub; i30++) {
                int db_loop_ub;
                db_loop_ub = r2D.size(0);
                for (int i32{0}; i32 < db_loop_ub; i32++) {
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
        cb_loop_ub = ud.size(1);
        for (int i31{0}; i31 < cb_loop_ub; i31++) {
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
            int eb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            eb_loop_ub = r3D.size(1);
            for (int i42{0}; i42 < eb_loop_ub; i42++) {
                int fb_loop_ub;
                fb_loop_ub = r3D.size(0);
                for (int i43{0}; i43 < fb_loop_ub; i43++) {
                    J[i43 + J.size(0) * i42] =
                        (r3D[i43 + r3D.size(0) * i42] * r[i42] +
                         3.0 * r2D[i43 + r2D.size(0) * i42] * ud[i42] * udd_vec[i42]) +
                        c_r1D[i43 + c_r1D.size(0) * i42] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
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
            feed.set_size(1, y.size(1));
            kb_loop_ub = y.size(1);
            for (int i51{0}; i51 < kb_loop_ub; i51++) {
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
            int mb_loop_ub;
            // 'zeroSpeedCurv:102' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            for (int i54{0}; i54 < mb_loop_ub; i54++) {
                b_feed[i54] = feed[i54] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:103' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int i_k;
            bool c_y;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i53;
                i53 = V.size(1);
                for (int g_k{0}; g_k < i53; g_k++) {
                    int i55;
                    i55 = r1.size(0);
                    for (int h_k{0}; h_k < i55; h_k++) {
                        r1[h_k + r1.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                nb_loop_ub = r1.size(1);
                for (int i56{0}; i56 < nb_loop_ub; i56++) {
                    int ob_loop_ub;
                    ob_loop_ub = r1.size(0);
                    for (int i57{0}; i57 < ob_loop_ub; i57++) {
                        b_x[i57 + b_x.size(0) * i56] =
                            (r1[i57 + r1.size(0) * i56] > vmax_data[i57]);
                    }
                }
            } else {
                e_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
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
                if (r1.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int sb_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    pb_loop_ub = r1.size(1);
                    for (int i59{0}; i59 < pb_loop_ub; i59++) {
                        int rb_loop_ub;
                        rb_loop_ub = r1.size(0);
                        for (int i62{0}; i62 < rb_loop_ub; i62++) {
                            r2[i62 + r2.size(0) * i59] =
                                r1[i62 + r1.size(0) * i59] - vmax_data[i62];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    sb_loop_ub = r2.size(1);
                    for (int i63{0}; i63 < sb_loop_ub; i63++) {
                        int ub_loop_ub;
                        ub_loop_ub = r2.size(0);
                        for (int i65{0}; i65 < ub_loop_ub; i65++) {
                            r1[i65 + r1.size(0) * i63] = r2[i65 + r2.size(0) * i63];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:106' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int l_k;
                bool d_y;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i58;
                    i58 = A.size(1);
                    for (int j_k{0}; j_k < i58; j_k++) {
                        int i60;
                        i60 = r1.size(0);
                        for (int k_k{0}; k_k < i60; k_k++) {
                            r1[k_k + r1.size(0) * j_k] = std::abs(A[k_k + A.size(0) * j_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    qb_loop_ub = r1.size(1);
                    for (int i61{0}; i61 < qb_loop_ub; i61++) {
                        int tb_loop_ub;
                        tb_loop_ub = r1.size(0);
                        for (int i64{0}; i64 < tb_loop_ub; i64++) {
                            b_x[i64 + b_x.size(0) * i61] =
                                (r1[i64 + r1.size(0) * i61] > amax_data[i64]);
                        }
                    }
                } else {
                    e_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
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
                    if (r1.size(0) == c_trueCount) {
                        int vb_loop_ub;
                        int yb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        vb_loop_ub = r1.size(1);
                        for (int i67{0}; i67 < vb_loop_ub; i67++) {
                            int xb_loop_ub;
                            xb_loop_ub = r1.size(0);
                            for (int i70{0}; i70 < xb_loop_ub; i70++) {
                                r3[i70 + r3.size(0) * i67] =
                                    r1[i70 + r1.size(0) * i67] - amax_data[i70];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        yb_loop_ub = r3.size(1);
                        for (int i71{0}; i71 < yb_loop_ub; i71++) {
                            int bc_loop_ub;
                            bc_loop_ub = r3.size(0);
                            for (int i73{0}; i73 < bc_loop_ub; i73++) {
                                r1[i73 + r1.size(0) * i71] = r3[i73 + r3.size(0) * i71];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:109' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int o_k;
                    bool e_y;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i66;
                        i66 = J.size(1);
                        for (int m_k{0}; m_k < i66; m_k++) {
                            int i68;
                            i68 = r1.size(0);
                            for (int n_k{0}; n_k < i68; n_k++) {
                                r1[n_k + r1.size(0) * m_k] = std::abs(J[n_k + J.size(0) * m_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        wb_loop_ub = r1.size(1);
                        for (int i69{0}; i69 < wb_loop_ub; i69++) {
                            int ac_loop_ub;
                            ac_loop_ub = r1.size(0);
                            for (int i72{0}; i72 < ac_loop_ub; i72++) {
                                b_x[i72 + b_x.size(0) * i69] =
                                    (r1[i72 + r1.size(0) * i69] > jmax_data[i72]);
                            }
                        }
                    } else {
                        e_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
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
                        if (r1.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            cc_loop_ub = r1.size(1);
                            for (int i74{0}; i74 < cc_loop_ub; i74++) {
                                int dc_loop_ub;
                                dc_loop_ub = r1.size(0);
                                for (int i75{0}; i75 < dc_loop_ub; i75++) {
                                    r4[i75 + r4.size(0) * i74] =
                                        r1[i75 + r1.size(0) * i74] - jmax_data[i75];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            ec_loop_ub = r4.size(1);
                            for (int i76{0}; i76 < ec_loop_ub; i76++) {
                                int fc_loop_ub;
                                fc_loop_ub = r4.size(0);
                                for (int i77{0}; i77 < fc_loop_ub; i77++) {
                                    r1[i77 + r1.size(0) * i76] = r4[i77 + r4.size(0) * i76];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    h_loop_ub = y.size(1);
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        udd[i9] = b_jps * y[i9];
    }
    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        double varargin_1;
        varargin_1 = y[i10];
        r[i10] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    j_loop_ub = r.size(1);
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        ud[i11] = b_jps * r[i11] / 2.0;
    }
    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    k_loop_ub = y.size(1);
    for (int i12{0}; i12 < k_loop_ub; i12++) {
        double b_varargin_1;
        b_varargin_1 = y[i12];
        r[i12] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    l_loop_ub = r.size(1);
    for (int i13{0}; i13 < l_loop_ub; i13++) {
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
