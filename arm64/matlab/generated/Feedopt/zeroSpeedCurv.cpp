
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: zeroSpeedCurv.cpp
//
// MATLAB Coder version            : 5.4
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
    double a_delta;
    double b_ex;
    double b_fmax;
    double b_jps;
    double d_ex;
    double d_k;
    double f_delta;
    double j_delta;
    double k_tmp;
    double v_delta;
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
    int i_loop_ub;
    int iindx;
    int k_loop_ub;
    int last;
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
    if (trueCount <= 2) {
        if (trueCount == 1) {
            b_ex = ctx_cfg_jmax[tmp_data[0] - 1];
        } else {
            double d;
            double d1;
            d = ctx_cfg_jmax[tmp_data[0] - 1];
            d1 = ctx_cfg_jmax[tmp_data[trueCount - 1] - 1];
            if (d > d1) {
                b_ex = d1;
            } else {
                b_ex = d;
            }
        }
    } else {
        double ex;
        ex = ctx_cfg_jmax[tmp_data[0] - 1];
        for (int b_k{2}; b_k <= trueCount; b_k++) {
            double d2;
            d2 = ctx_cfg_jmax[tmp_data[b_k - 1] - 1];
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
    b_jps = b_ex / d_ex;
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:31' searchJps = true;
    // 'zeroSpeedCurv:33' ind = 0;
    // 'zeroSpeedCurv:34' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    uv[0] = 1U;
    searchJps = true;
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double c_jps;
        double e_k;
        double k_max;
        int b_partialTrueCount;
        int bb_loop_ub;
        int c_end;
        int c_partialTrueCount;
        int d_end;
        int d_partialTrueCount;
        int eb_loop_ub;
        int h_k;
        int hi;
        int i29;
        int i30;
        int i34;
        int i35;
        int i36;
        int i37;
        int i38;
        int i39;
        int i40;
        int i41;
        int i42;
        int j_loop_ub;
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
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        e_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (e_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(e_k) + 1);
            c_loop_ub = static_cast<int>(e_k);
            for (int i3{0}; i3 <= c_loop_ub; i3++) {
                k_vec[i3] = i3;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (static_cast<int>(e_k) < e_k) {
                int e_loop_ub;
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(e_k) + 2);
                e_loop_ub = static_cast<int>(e_k);
                for (int i5{0}; i5 <= e_loop_ub; i5++) {
                    k_vec[i5] = i5;
                }
                k_vec[static_cast<int>(e_k) + 1] = e_k;
            }
        } else {
            // 'zeroSpeedCurv:53' else
            // 'zeroSpeedCurv:54' k_vec = 1;
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
        // 'zeroSpeedCurv:75' if( isempty( ratio ) )
        // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //  Inputs :
        //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
        //    k_vec           :  [ 1 x M ] The time vector
        //    isEnd           :  ( Boolean ) Is the end of the Curve.
        //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
        //  Outputs :
        //    u               :  [ N x M ]
        //    ud              :  [ N x M ]
        //    udd             :  [ N x M ]
        //    uddd            :  [ N x M ]
        // 'constJerkU:15' if( coder.target( "MATLAB" ) )
        // 'constJerkU:21' if( isEnd )
        // 'constJerkU:22' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
        k_max = std::pow(6.0 / b_jps, 0.33333333333333331);
        // 'constJerkU:23' k_vec  = k_max - k_vec;
        y.set_size(1, k_vec.size(1));
        j_loop_ub = k_vec.size(1);
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            y[i10] = k_max - k_vec[i10] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
        r.set_size(1, y.size(1));
        l_loop_ub = y.size(1);
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            double c_varargin_1;
            c_varargin_1 = y[i12];
            r[i12] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        m_loop_ub = r.size(1);
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            ud[i13] = b_jps * r[i13] / 2.0;
        }
        // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        n_loop_ub = y.size(1);
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            double d_varargin_1;
            d_varargin_1 = y[i14];
            r[i14] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        p_loop_ub = r.size(1);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            u[i16] = b_jps * r[i16] / 6.0;
        }
        // 'constJerkU:32' if( forceLimits )
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
        // 'constJerkU:37' if( isEnd )
        //  Reverse time ( Backward-like integration )
        // 'constJerkU:38' u    = 1 - u;
        u.set_size(1, u.size(1));
        r_loop_ub = u.size(1);
        for (int i18{0}; i18 < r_loop_ub; i18++) {
            u[i18] = 1.0 - u[i18];
        }
        // 'constJerkU:39' ud   = ud;
        // 'constJerkU:40' udd  = -udd;
        // 'constJerkU:41' uddd = uddd;
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        s_loop_ub = y.size(1);
        for (int i19{0}; i19 < s_loop_ub; i19++) {
            udd_vec[i19] = -(b_jps * y[i19]);
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
            for (int i20{0}; i20 <= t_loop_ub; i20++) {
                int u_loop_ub;
                u_loop_ub = c_r1D.size(0) - 1;
                for (int i21{0}; i21 <= u_loop_ub; i21++) {
                    d_r1D[i21 + d_r1D.size(0) * i20] = c_r1D[i21 + c_r1D.size(0) * i20];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            v_loop_ub = r2D.size(1) - 1;
            for (int i22{0}; i22 <= v_loop_ub; i22++) {
                int w_loop_ub;
                w_loop_ub = r2D.size(0) - 1;
                for (int i23{0}; i23 <= w_loop_ub; i23++) {
                    b_r2D[i23 + b_r2D.size(0) * i22] = r2D[i23 + r2D.size(0) * i22];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            x_loop_ub = r3D.size(1) - 1;
            for (int i24{0}; i24 <= x_loop_ub; i24++) {
                int y_loop_ub;
                y_loop_ub = r3D.size(0) - 1;
                for (int i25{0}; i25 <= y_loop_ub; i25++) {
                    b_r3D[i25 + b_r3D.size(0) * i24] = r3D[i25 + r3D.size(0) * i24];
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
            for (int i26{0}; i26 < ab_loop_ub; i26++) {
                int cb_loop_ub;
                cb_loop_ub = c_r1D.size(0);
                for (int i28{0}; i28 < cb_loop_ub; i28++) {
                    V[i28 + V.size(0) * i26] = c_r1D[i28 + c_r1D.size(0) * i26] * ud[i26];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        bb_loop_ub = ud.size(1);
        for (int i27{0}; i27 < bb_loop_ub; i27++) {
            double e_varargin_1;
            e_varargin_1 = ud[i27];
            r[i27] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i29 = r.size(1);
        } else {
            i29 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i30 = udd_vec.size(1);
        } else {
            i30 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i29 == i30)) {
            int db_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            db_loop_ub = r2D.size(1);
            for (int i31{0}; i31 < db_loop_ub; i31++) {
                int fb_loop_ub;
                fb_loop_ub = r2D.size(0);
                for (int i33{0}; i33 < fb_loop_ub; i33++) {
                    A[i33 + A.size(0) * i31] = r2D[i33 + r2D.size(0) * i31] * r[i31] +
                                               c_r1D[i33 + c_r1D.size(0) * i31] * udd_vec[i31];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        eb_loop_ub = ud.size(1);
        for (int i32{0}; i32 < eb_loop_ub; i32++) {
            double f_varargin_1;
            f_varargin_1 = ud[i32];
            r[i32] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i34 = ud.size(1);
        } else {
            i34 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i35 = r.size(1);
        } else {
            i35 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i36 = ud.size(1);
        } else {
            i36 = r2D.size(1);
        }
        if (i36 == 1) {
            i37 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i37 = ud.size(1);
        } else {
            i37 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i38 = r2D.size(0);
        } else {
            i38 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i39 = r.size(1);
        } else {
            i39 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i40 = ud.size(1);
        } else {
            i40 = r2D.size(1);
        }
        if (i39 == 1) {
            if (i40 == 1) {
                i41 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i41 = ud.size(1);
            } else {
                i41 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i41 = r.size(1);
        } else {
            i41 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i42 = y.size(1);
        } else {
            i42 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i34 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i35 == i37) && (c_r1D.size(1) == y.size(1)) &&
            (i38 == c_r1D.size(0)) && (i41 == i42)) {
            int gb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            gb_loop_ub = r3D.size(1);
            for (int i43{0}; i43 < gb_loop_ub; i43++) {
                int hb_loop_ub;
                hb_loop_ub = r3D.size(0);
                for (int i44{0}; i44 < hb_loop_ub; i44++) {
                    J[i44 + J.size(0) * i43] =
                        (r3D[i44 + r3D.size(0) * i43] * r[i43] +
                         3.0 * r2D[i44 + r2D.size(0) * i43] * ud[i43] * udd_vec[i43]) +
                        c_r1D[i44 + c_r1D.size(0) * i43] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'zeroSpeedCurv:85' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int ib_loop_ub;
            // 'zeroSpeedCurv:87' else
            // 'zeroSpeedCurv:88' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            ib_loop_ub = c_r1D.size(1) - 1;
            for (int i45{0}; i45 <= ib_loop_ub; i45++) {
                int jb_loop_ub;
                jb_loop_ub = c_r1D.size(0) - 1;
                for (int i46{0}; i46 <= jb_loop_ub; i46++) {
                    e_r1D[i46 + e_r1D.size(0) * i45] = c_r1D[i46 + c_r1D.size(0) * i45];
                }
            }
            b_ctx_kin.v_relative(b_r0D, e_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:86' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:91' safetyFactor = 0.5;
        // 'zeroSpeedCurv:92' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:93' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i47{0}; i47 < b_trueCount; i47++) {
            vmax_data[i47] = ctx_cfg_vmax[b_tmp_data[i47] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:94' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int h_i{0}; h_i <= end_tmp; h_i++) {
            if (ctx_cfg_maskTot_data[h_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(h_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i48{0}; i48 < c_trueCount; i48++) {
            amax_data[i48] = ctx_cfg_amax[c_tmp_data[i48] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int i_i{0}; i_i <= end_tmp; i_i++) {
            if (ctx_cfg_maskTot_data[i_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(i_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i49{0}; i49 < d_trueCount; i49++) {
            jmax_data[i49] = ctx_cfg_jmax[d_tmp_data[i49] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:97' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        kb_loop_ub = c_r1D.size(1);
        for (int i50{0}; i50 < kb_loop_ub; i50++) {
            y[i50] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            lb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int f_k{0}; f_k <= hi; f_k++) {
            xv.set_size(outsize_idx_0);
            for (int i51{0}; i51 < lb_loop_ub; i51++) {
                xv[i51] = 0.0;
            }
            for (int g_k{0}; g_k < nx; g_k++) {
                xv[g_k] = c_r1D[(ctx_cfg_indCart[g_k] + c_r1D.size(0) * f_k) - 1];
            }
            y[f_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int mb_loop_ub;
            feed.set_size(1, y.size(1));
            mb_loop_ub = y.size(1);
            for (int i52{0}; i52 < mb_loop_ub; i52++) {
                feed[i52] = y[i52] * ud[i52];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:99' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        nb_loop_ub = feed.size(1);
        for (int i53{0}; i53 < nb_loop_ub; i53++) {
            x[i53] = (feed[i53] > b_fmax);
        }
        b_y = false;
        h_k = 0;
        exitg1 = false;
        while ((!exitg1) && (h_k <= x.size(1) - 1)) {
            if (x[h_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                h_k++;
            }
        }
        if (b_y) {
            int ob_loop_ub;
            // 'zeroSpeedCurv:100' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            ob_loop_ub = feed.size(1);
            for (int i55{0}; i55 < ob_loop_ub; i55++) {
                b_feed[i55] = feed[i55] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:101' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i54;
                i54 = V.size(1);
                for (int i_k{0}; i_k < i54; i_k++) {
                    int i56;
                    i56 = r1.size(0);
                    for (int j_k{0}; j_k < i56; j_k++) {
                        r1[j_k + r1.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int pb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                pb_loop_ub = r1.size(1);
                for (int i57{0}; i57 < pb_loop_ub; i57++) {
                    int qb_loop_ub;
                    qb_loop_ub = r1.size(0);
                    for (int i58{0}; i58 < qb_loop_ub; i58++) {
                        b_x[i58 + b_x.size(0) * i57] =
                            (r1[i58 + r1.size(0) * i57] > vmax_data[i58]);
                    }
                }
            } else {
                e_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
            }
            varargout_1 = false;
            k_k = 0;
            exitg1 = false;
            while ((!exitg1) && (k_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[k_k]) {
                    varargout_1 = true;
                    exitg1 = true;
                } else {
                    k_k++;
                }
            }
            if (varargout_1) {
                // 'zeroSpeedCurv:102' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:103' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r1.size(0) == b_trueCount) {
                    int rb_loop_ub;
                    int vb_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    rb_loop_ub = r1.size(1);
                    for (int i61{0}; i61 < rb_loop_ub; i61++) {
                        int tb_loop_ub;
                        tb_loop_ub = r1.size(0);
                        for (int i63{0}; i63 < tb_loop_ub; i63++) {
                            r2[i63 + r2.size(0) * i61] =
                                r1[i63 + r1.size(0) * i61] - vmax_data[i63];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    vb_loop_ub = r2.size(1);
                    for (int i65{0}; i65 < vb_loop_ub; i65++) {
                        int wb_loop_ub;
                        wb_loop_ub = r2.size(0);
                        for (int i66{0}; i66 < wb_loop_ub; i66++) {
                            r1[i66 + r1.size(0) * i65] = r2[i66 + r2.size(0) * i65];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:104' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i59;
                    i59 = A.size(1);
                    for (int l_k{0}; l_k < i59; l_k++) {
                        int i60;
                        i60 = r1.size(0);
                        for (int m_k{0}; m_k < i60; m_k++) {
                            r1[m_k + r1.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int sb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    sb_loop_ub = r1.size(1);
                    for (int i62{0}; i62 < sb_loop_ub; i62++) {
                        int ub_loop_ub;
                        ub_loop_ub = r1.size(0);
                        for (int i64{0}; i64 < ub_loop_ub; i64++) {
                            b_x[i64 + b_x.size(0) * i62] =
                                (r1[i64 + r1.size(0) * i62] > amax_data[i64]);
                        }
                    }
                } else {
                    e_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
                }
                b_varargout_1 = false;
                n_k = 0;
                exitg1 = false;
                while ((!exitg1) && (n_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[n_k]) {
                        b_varargout_1 = true;
                        exitg1 = true;
                    } else {
                        n_k++;
                    }
                }
                if (b_varargout_1) {
                    // 'zeroSpeedCurv:105' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:106' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r1.size(0) == c_trueCount) {
                        int cc_loop_ub;
                        int xb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        xb_loop_ub = r1.size(1);
                        for (int i69{0}; i69 < xb_loop_ub; i69++) {
                            int ac_loop_ub;
                            ac_loop_ub = r1.size(0);
                            for (int i71{0}; i71 < ac_loop_ub; i71++) {
                                r3[i71 + r3.size(0) * i69] =
                                    r1[i71 + r1.size(0) * i69] - amax_data[i71];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        cc_loop_ub = r3.size(1);
                        for (int i73{0}; i73 < cc_loop_ub; i73++) {
                            int dc_loop_ub;
                            dc_loop_ub = r3.size(0);
                            for (int i74{0}; i74 < dc_loop_ub; i74++) {
                                r1[i74 + r1.size(0) * i73] = r3[i74 + r3.size(0) * i73];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:107' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i67;
                        i67 = J.size(1);
                        for (int o_k{0}; o_k < i67; o_k++) {
                            int i68;
                            i68 = r1.size(0);
                            for (int p_k{0}; p_k < i68; p_k++) {
                                r1[p_k + r1.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int yb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        yb_loop_ub = r1.size(1);
                        for (int i70{0}; i70 < yb_loop_ub; i70++) {
                            int bc_loop_ub;
                            bc_loop_ub = r1.size(0);
                            for (int i72{0}; i72 < bc_loop_ub; i72++) {
                                b_x[i72 + b_x.size(0) * i70] =
                                    (r1[i72 + r1.size(0) * i70] > jmax_data[i72]);
                            }
                        }
                    } else {
                        e_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
                    }
                    c_varargout_1 = false;
                    q_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (q_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[q_k]) {
                            c_varargout_1 = true;
                            exitg1 = true;
                        } else {
                            q_k++;
                        }
                    }
                    if (c_varargout_1) {
                        // 'zeroSpeedCurv:108' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:109' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r1.size(0) == d_trueCount) {
                            int ec_loop_ub;
                            int gc_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            ec_loop_ub = r1.size(1);
                            for (int i75{0}; i75 < ec_loop_ub; i75++) {
                                int fc_loop_ub;
                                fc_loop_ub = r1.size(0);
                                for (int i76{0}; i76 < fc_loop_ub; i76++) {
                                    r4[i76 + r4.size(0) * i75] =
                                        r1[i76 + r1.size(0) * i75] - jmax_data[i76];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            gc_loop_ub = r4.size(1);
                            for (int i77{0}; i77 < gc_loop_ub; i77++) {
                                int hc_loop_ub;
                                hc_loop_ub = r4.size(0);
                                for (int i78{0}; i78 < hc_loop_ub; i78++) {
                                    r1[i78 + r1.size(0) * i77] = r4[i78 + r4.size(0) * i77];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:110' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:111' else
                        // 'zeroSpeedCurv:112' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:40' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    k_tmp = std::pow(6.0 / b_jps, 0.33333333333333331);
    d_k = k_tmp / ctx_cfg_dt;
    // 'zeroSpeedCurv:50' if( k > 0 )
    if (d_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:51' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(d_k) + 1);
        b_loop_ub = static_cast<int>(d_k);
        for (int i2{0}; i2 <= b_loop_ub; i2++) {
            k_vec[i2] = i2;
        }
        // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
        if (static_cast<int>(d_k) < d_k) {
            int d_loop_ub;
            // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(d_k) + 2);
            d_loop_ub = static_cast<int>(d_k);
            for (int i4{0}; i4 <= d_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            k_vec[static_cast<int>(d_k) + 1] = d_k;
        }
    } else {
        // 'zeroSpeedCurv:53' else
        // 'zeroSpeedCurv:54' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    // 'constJerkU:15' if( coder.target( "MATLAB" ) )
    // 'constJerkU:21' if( isEnd )
    // 'constJerkU:22' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    // 'constJerkU:23' k_vec  = k_max - k_vec;
    y.set_size(1, k_vec.size(1));
    f_loop_ub = k_vec.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        y[i6] = k_tmp - k_vec[i6] * ctx_cfg_dt;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        double varargin_1;
        varargin_1 = y[i7];
        r[i7] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    h_loop_ub = r.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        ud[i8] = b_jps * r[i8] / 2.0;
    }
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        double b_varargin_1;
        b_varargin_1 = y[i9];
        r[i9] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    k_loop_ub = r.size(1);
    for (int i11{0}; i11 < k_loop_ub; i11++) {
        u[i11] = b_jps * r[i11] / 6.0;
    }
    // 'constJerkU:32' if( forceLimits )
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
    // 'constJerkU:37' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:38' u    = 1 - u;
    u.set_size(1, u.size(1));
    o_loop_ub = u.size(1);
    for (int i15{0}; i15 < o_loop_ub; i15++) {
        u[i15] = 1.0 - u[i15];
    }
    // 'constJerkU:39' ud   = ud;
    // 'constJerkU:40' udd  = -udd;
    udd.set_size(1, y.size(1));
    q_loop_ub = y.size(1);
    for (int i17{0}; i17 < q_loop_ub; i17++) {
        udd[i17] = -(b_jps * y[i17]);
    }
    // 'constJerkU:41' uddd = uddd;
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
    double a_delta;
    double b_ex;
    double b_fmax;
    double b_jps;
    double d_ex;
    double d_k;
    double f_delta;
    double j_delta;
    double v_delta;
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
    if (trueCount <= 2) {
        if (trueCount == 1) {
            b_ex = ctx_cfg_jmax[tmp_data[0] - 1];
        } else {
            double d;
            double d1;
            d = ctx_cfg_jmax[tmp_data[0] - 1];
            d1 = ctx_cfg_jmax[tmp_data[trueCount - 1] - 1];
            if (d > d1) {
                b_ex = d1;
            } else {
                b_ex = d;
            }
        }
    } else {
        double ex;
        ex = ctx_cfg_jmax[tmp_data[0] - 1];
        for (int b_k{2}; b_k <= trueCount; b_k++) {
            double d2;
            d2 = ctx_cfg_jmax[tmp_data[b_k - 1] - 1];
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
    b_jps = b_ex / d_ex;
    //  searchU   = true;
    // while searchU
    // 'zeroSpeedCurv:31' searchJps = true;
    // 'zeroSpeedCurv:33' ind = 0;
    // 'zeroSpeedCurv:34' while searchJps
    b_fmax = curv->Info.FeedRate * 0.5;
    uv[0] = 1U;
    searchJps = true;
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int c_end;
        int c_partialTrueCount;
        int cb_loop_ub;
        int d_end;
        int d_partialTrueCount;
        int g_loop_ub;
        int h_k;
        int hi;
        int i27;
        int i28;
        int i32;
        int i33;
        int i34;
        int i35;
        int i36;
        int i37;
        int i38;
        int i39;
        int i40;
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
        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        e_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:50' if( k > 0 )
        if (e_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:51' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(e_k) + 1);
            c_loop_ub = static_cast<int>(e_k);
            for (int i3{0}; i3 <= c_loop_ub; i3++) {
                k_vec[i3] = i3;
            }
            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
            if (static_cast<int>(e_k) < e_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(e_k) + 2);
                f_loop_ub = static_cast<int>(e_k);
                for (int i6{0}; i6 <= f_loop_ub; i6++) {
                    k_vec[i6] = i6;
                }
                k_vec[static_cast<int>(e_k) + 1] = e_k;
            }
        } else {
            // 'zeroSpeedCurv:53' else
            // 'zeroSpeedCurv:54' k_vec = 1;
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
        // 'zeroSpeedCurv:75' if( isempty( ratio ) )
        // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        y.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            y[i7] = k_vec[i7] * ctx_cfg_dt;
        }
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //  Inputs :
        //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
        //    k_vec           :  [ 1 x M ] The time vector
        //    isEnd           :  ( Boolean ) Is the end of the Curve.
        //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
        //  Outputs :
        //    u               :  [ N x M ]
        //    ud              :  [ N x M ]
        //    udd             :  [ N x M ]
        //    uddd            :  [ N x M ]
        // 'constJerkU:15' if( coder.target( "MATLAB" ) )
        // 'constJerkU:21' if( isEnd )
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
        r.set_size(1, y.size(1));
        m_loop_ub = y.size(1);
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            double c_varargin_1;
            c_varargin_1 = y[i13];
            r[i13] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r.size(1));
        n_loop_ub = r.size(1);
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            ud[i14] = b_jps * r[i14] / 2.0;
        }
        // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
        r.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            double d_varargin_1;
            d_varargin_1 = y[i15];
            r[i15] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r.size(1));
        p_loop_ub = r.size(1);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            u[i16] = b_jps * r[i16] / 6.0;
        }
        // 'constJerkU:32' if( forceLimits )
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
        // 'constJerkU:37' if( isEnd )
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        q_loop_ub = y.size(1);
        for (int i17{0}; i17 < q_loop_ub; i17++) {
            udd_vec[i17] = b_jps * y[i17];
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
            for (int i18{0}; i18 <= r_loop_ub; i18++) {
                int s_loop_ub;
                s_loop_ub = c_r1D.size(0) - 1;
                for (int i19{0}; i19 <= s_loop_ub; i19++) {
                    d_r1D[i19 + d_r1D.size(0) * i18] = c_r1D[i19 + c_r1D.size(0) * i18];
                }
            }
            b_r2D.set_size(r2D.size(0), r2D.size(1));
            t_loop_ub = r2D.size(1) - 1;
            for (int i20{0}; i20 <= t_loop_ub; i20++) {
                int u_loop_ub;
                u_loop_ub = r2D.size(0) - 1;
                for (int i21{0}; i21 <= u_loop_ub; i21++) {
                    b_r2D[i21 + b_r2D.size(0) * i20] = r2D[i21 + r2D.size(0) * i20];
                }
            }
            b_r3D.set_size(r3D.size(0), r3D.size(1));
            v_loop_ub = r3D.size(1) - 1;
            for (int i22{0}; i22 <= v_loop_ub; i22++) {
                int w_loop_ub;
                w_loop_ub = r3D.size(0) - 1;
                for (int i23{0}; i23 <= w_loop_ub; i23++) {
                    b_r3D[i23 + b_r3D.size(0) * i22] = r3D[i23 + r3D.size(0) * i22];
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
            for (int i24{0}; i24 < x_loop_ub; i24++) {
                int ab_loop_ub;
                ab_loop_ub = c_r1D.size(0);
                for (int i26{0}; i26 < ab_loop_ub; i26++) {
                    V[i26 + V.size(0) * i24] = c_r1D[i26 + c_r1D.size(0) * i24] * ud[i24];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r.set_size(1, ud.size(1));
        y_loop_ub = ud.size(1);
        for (int i25{0}; i25 < y_loop_ub; i25++) {
            double e_varargin_1;
            e_varargin_1 = ud[i25];
            r[i25] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i27 = r.size(1);
        } else {
            i27 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i28 = udd_vec.size(1);
        } else {
            i28 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i27 == i28)) {
            int bb_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            bb_loop_ub = r2D.size(1);
            for (int i29{0}; i29 < bb_loop_ub; i29++) {
                int db_loop_ub;
                db_loop_ub = r2D.size(0);
                for (int i31{0}; i31 < db_loop_ub; i31++) {
                    A[i31 + A.size(0) * i29] = r2D[i31 + r2D.size(0) * i29] * r[i29] +
                                               c_r1D[i31 + c_r1D.size(0) * i29] * udd_vec[i29];
                }
            }
        } else {
            binary_expand_op(A, r2D, r, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r.set_size(1, ud.size(1));
        cb_loop_ub = ud.size(1);
        for (int i30{0}; i30 < cb_loop_ub; i30++) {
            double f_varargin_1;
            f_varargin_1 = ud[i30];
            r[i30] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i32 = ud.size(1);
        } else {
            i32 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i33 = r.size(1);
        } else {
            i33 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i34 = ud.size(1);
        } else {
            i34 = r2D.size(1);
        }
        if (i34 == 1) {
            i35 = udd_vec.size(1);
        } else if (r2D.size(1) == 1) {
            i35 = ud.size(1);
        } else {
            i35 = r2D.size(1);
        }
        if (r3D.size(0) == 1) {
            i36 = r2D.size(0);
        } else {
            i36 = r3D.size(0);
        }
        if (r3D.size(1) == 1) {
            i37 = r.size(1);
        } else {
            i37 = r3D.size(1);
        }
        if (r2D.size(1) == 1) {
            i38 = ud.size(1);
        } else {
            i38 = r2D.size(1);
        }
        if (i37 == 1) {
            if (i38 == 1) {
                i39 = udd_vec.size(1);
            } else if (r2D.size(1) == 1) {
                i39 = ud.size(1);
            } else {
                i39 = r2D.size(1);
            }
        } else if (r3D.size(1) == 1) {
            i39 = r.size(1);
        } else {
            i39 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i40 = y.size(1);
        } else {
            i40 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud.size(1)) && (i32 == udd_vec.size(1)) &&
            (r3D.size(0) == r2D.size(0)) && (i33 == i35) && (c_r1D.size(1) == y.size(1)) &&
            (i36 == c_r1D.size(0)) && (i39 == i40)) {
            int eb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            eb_loop_ub = r3D.size(1);
            for (int i41{0}; i41 < eb_loop_ub; i41++) {
                int fb_loop_ub;
                fb_loop_ub = r3D.size(0);
                for (int i42{0}; i42 < fb_loop_ub; i42++) {
                    J[i42 + J.size(0) * i41] =
                        (r3D[i42 + r3D.size(0) * i41] * r[i41] +
                         3.0 * r2D[i42 + r2D.size(0) * i41] * ud[i41] * udd_vec[i41]) +
                        c_r1D[i42 + c_r1D.size(0) * i41] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r, r2D, ud, udd_vec, c_r1D, b_jps, uv);
        }
        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:83' ctx.kin = ctx.kin.set_tool_length( curv.tool.offset.z );
        b_ctx_kin = *ctx_kin;
        b_ctx_kin.set_tool_length(curv->tool.offset.z);
        // 'zeroSpeedCurv:85' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int gb_loop_ub;
            // 'zeroSpeedCurv:87' else
            // 'zeroSpeedCurv:88' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            gb_loop_ub = c_r1D.size(1) - 1;
            for (int i43{0}; i43 <= gb_loop_ub; i43++) {
                int hb_loop_ub;
                hb_loop_ub = c_r1D.size(0) - 1;
                for (int i44{0}; i44 <= hb_loop_ub; i44++) {
                    e_r1D[i44 + e_r1D.size(0) * i43] = c_r1D[i44 + c_r1D.size(0) * i43];
                }
            }
            b_ctx_kin.v_relative(b_r0D, e_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:86' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:91' safetyFactor = 0.5;
        // 'zeroSpeedCurv:92' fmax =  curv.Info.FeedRate * safetyFactor;
        // 'zeroSpeedCurv:93' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i45{0}; i45 < b_trueCount; i45++) {
            vmax_data[i45] = ctx_cfg_vmax[b_tmp_data[i45] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:94' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int h_i{0}; h_i <= end_tmp; h_i++) {
            if (ctx_cfg_maskTot_data[h_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(h_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i46{0}; i46 < c_trueCount; i46++) {
            amax_data[i46] = ctx_cfg_amax[c_tmp_data[i46] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:95' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int i_i{0}; i_i <= end_tmp; i_i++) {
            if (ctx_cfg_maskTot_data[i_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(i_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i47{0}; i47 < d_trueCount; i47++) {
            jmax_data[i47] = ctx_cfg_jmax[d_tmp_data[i47] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:97' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        ib_loop_ub = c_r1D.size(1);
        for (int i48{0}; i48 < ib_loop_ub; i48++) {
            y[i48] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            jb_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int f_k{0}; f_k <= hi; f_k++) {
            xv.set_size(outsize_idx_0);
            for (int i49{0}; i49 < jb_loop_ub; i49++) {
                xv[i49] = 0.0;
            }
            for (int g_k{0}; g_k < nx; g_k++) {
                xv[g_k] = c_r1D[(ctx_cfg_indCart[g_k] + c_r1D.size(0) * f_k) - 1];
            }
            y[f_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int kb_loop_ub;
            feed.set_size(1, y.size(1));
            kb_loop_ub = y.size(1);
            for (int i50{0}; i50 < kb_loop_ub; i50++) {
                feed[i50] = y[i50] * ud[i50];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:99' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        lb_loop_ub = feed.size(1);
        for (int i51{0}; i51 < lb_loop_ub; i51++) {
            x[i51] = (feed[i51] > b_fmax);
        }
        b_y = false;
        h_k = 0;
        exitg1 = false;
        while ((!exitg1) && (h_k <= x.size(1) - 1)) {
            if (x[h_k]) {
                b_y = true;
                exitg1 = true;
            } else {
                h_k++;
            }
        }
        if (b_y) {
            int mb_loop_ub;
            // 'zeroSpeedCurv:100' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            for (int i53{0}; i53 < mb_loop_ub; i53++) {
                b_feed[i53] = feed[i53] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:101' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i52;
                i52 = V.size(1);
                for (int i_k{0}; i_k < i52; i_k++) {
                    int i54;
                    i54 = r1.size(0);
                    for (int j_k{0}; j_k < i54; j_k++) {
                        r1[j_k + r1.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                nb_loop_ub = r1.size(1);
                for (int i55{0}; i55 < nb_loop_ub; i55++) {
                    int ob_loop_ub;
                    ob_loop_ub = r1.size(0);
                    for (int i56{0}; i56 < ob_loop_ub; i56++) {
                        b_x[i56 + b_x.size(0) * i55] =
                            (r1[i56 + r1.size(0) * i55] > vmax_data[i56]);
                    }
                }
            } else {
                e_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
            }
            varargout_1 = false;
            k_k = 0;
            exitg1 = false;
            while ((!exitg1) && (k_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[k_k]) {
                    varargout_1 = true;
                    exitg1 = true;
                } else {
                    k_k++;
                }
            }
            if (varargout_1) {
                // 'zeroSpeedCurv:102' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:103' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r1.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int tb_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    pb_loop_ub = r1.size(1);
                    for (int i59{0}; i59 < pb_loop_ub; i59++) {
                        int rb_loop_ub;
                        rb_loop_ub = r1.size(0);
                        for (int i61{0}; i61 < rb_loop_ub; i61++) {
                            r2[i61 + r2.size(0) * i59] =
                                r1[i61 + r1.size(0) * i59] - vmax_data[i61];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    tb_loop_ub = r2.size(1);
                    for (int i63{0}; i63 < tb_loop_ub; i63++) {
                        int ub_loop_ub;
                        ub_loop_ub = r2.size(0);
                        for (int i64{0}; i64 < ub_loop_ub; i64++) {
                            r1[i64 + r1.size(0) * i63] = r2[i64 + r2.size(0) * i63];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:104' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i57;
                    i57 = A.size(1);
                    for (int l_k{0}; l_k < i57; l_k++) {
                        int i58;
                        i58 = r1.size(0);
                        for (int m_k{0}; m_k < i58; m_k++) {
                            r1[m_k + r1.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    qb_loop_ub = r1.size(1);
                    for (int i60{0}; i60 < qb_loop_ub; i60++) {
                        int sb_loop_ub;
                        sb_loop_ub = r1.size(0);
                        for (int i62{0}; i62 < sb_loop_ub; i62++) {
                            b_x[i62 + b_x.size(0) * i60] =
                                (r1[i62 + r1.size(0) * i60] > amax_data[i62]);
                        }
                    }
                } else {
                    e_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
                }
                b_varargout_1 = false;
                n_k = 0;
                exitg1 = false;
                while ((!exitg1) && (n_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[n_k]) {
                        b_varargout_1 = true;
                        exitg1 = true;
                    } else {
                        n_k++;
                    }
                }
                if (b_varargout_1) {
                    // 'zeroSpeedCurv:105' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:106' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r1.size(0) == c_trueCount) {
                        int ac_loop_ub;
                        int vb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        vb_loop_ub = r1.size(1);
                        for (int i67{0}; i67 < vb_loop_ub; i67++) {
                            int xb_loop_ub;
                            xb_loop_ub = r1.size(0);
                            for (int i69{0}; i69 < xb_loop_ub; i69++) {
                                r3[i69 + r3.size(0) * i67] =
                                    r1[i69 + r1.size(0) * i67] - amax_data[i69];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        ac_loop_ub = r3.size(1);
                        for (int i71{0}; i71 < ac_loop_ub; i71++) {
                            int bc_loop_ub;
                            bc_loop_ub = r3.size(0);
                            for (int i72{0}; i72 < bc_loop_ub; i72++) {
                                r1[i72 + r1.size(0) * i71] = r3[i72 + r3.size(0) * i71];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:107' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i65;
                        i65 = J.size(1);
                        for (int o_k{0}; o_k < i65; o_k++) {
                            int i66;
                            i66 = r1.size(0);
                            for (int p_k{0}; p_k < i66; p_k++) {
                                r1[p_k + r1.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        wb_loop_ub = r1.size(1);
                        for (int i68{0}; i68 < wb_loop_ub; i68++) {
                            int yb_loop_ub;
                            yb_loop_ub = r1.size(0);
                            for (int i70{0}; i70 < yb_loop_ub; i70++) {
                                b_x[i70 + b_x.size(0) * i68] =
                                    (r1[i70 + r1.size(0) * i68] > jmax_data[i70]);
                            }
                        }
                    } else {
                        e_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
                    }
                    c_varargout_1 = false;
                    q_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (q_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[q_k]) {
                            c_varargout_1 = true;
                            exitg1 = true;
                        } else {
                            q_k++;
                        }
                    }
                    if (c_varargout_1) {
                        // 'zeroSpeedCurv:108' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:109' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r1.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            cc_loop_ub = r1.size(1);
                            for (int i73{0}; i73 < cc_loop_ub; i73++) {
                                int dc_loop_ub;
                                dc_loop_ub = r1.size(0);
                                for (int i74{0}; i74 < dc_loop_ub; i74++) {
                                    r4[i74 + r4.size(0) * i73] =
                                        r1[i74 + r1.size(0) * i73] - jmax_data[i74];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            ec_loop_ub = r4.size(1);
                            for (int i75{0}; i75 < ec_loop_ub; i75++) {
                                int fc_loop_ub;
                                fc_loop_ub = r4.size(0);
                                for (int i76{0}; i76 < fc_loop_ub; i76++) {
                                    r1[i76 + r1.size(0) * i75] = r4[i76 + r4.size(0) * i75];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:110' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:111' else
                        // 'zeroSpeedCurv:112' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:40' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:50' if( k > 0 )
    if (d_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:51' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(d_k) + 1);
        b_loop_ub = static_cast<int>(d_k);
        for (int i2{0}; i2 <= b_loop_ub; i2++) {
            k_vec[i2] = i2;
        }
        // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
        if (static_cast<int>(d_k) < d_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(d_k) + 2);
            e_loop_ub = static_cast<int>(d_k);
            for (int i5{0}; i5 <= e_loop_ub; i5++) {
                k_vec[i5] = i5;
            }
            k_vec[static_cast<int>(d_k) + 1] = d_k;
        }
    } else {
        // 'zeroSpeedCurv:53' else
        // 'zeroSpeedCurv:54' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        y[i4] = k_vec[i4] * ctx_cfg_dt;
    }
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    // 'constJerkU:15' if( coder.target( "MATLAB" ) )
    // 'constJerkU:21' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
    udd.set_size(1, y.size(1));
    h_loop_ub = y.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        udd[i8] = b_jps * y[i8];
    }
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        double varargin_1;
        varargin_1 = y[i9];
        r[i9] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    j_loop_ub = r.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        ud[i10] = b_jps * r[i10] / 2.0;
    }
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    k_loop_ub = y.size(1);
    for (int i11{0}; i11 < k_loop_ub; i11++) {
        double b_varargin_1;
        b_varargin_1 = y[i11];
        r[i11] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    l_loop_ub = r.size(1);
    for (int i12{0}; i12 < l_loop_ub; i12++) {
        u[i12] = b_jps * r[i12] / 6.0;
    }
    // 'constJerkU:32' if( forceLimits )
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
    // 'constJerkU:37' if( isEnd )
    *jps = b_jps;
}

} // namespace ocn

//
// File trailer for zeroSpeedCurv.cpp
//
// [EOF]
//
