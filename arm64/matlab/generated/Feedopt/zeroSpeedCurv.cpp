
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
#include "calcRVAJfromU.h"
#include "constJerkU.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>

// Variable Definitions
namespace ocn {
static bool ratio_not_empty;

}

// Function Declarations
namespace ocn {
static void f_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
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
static void f_binary_expand_op(::coder::array<bool, 2U> &in1, const ::coder::array<double, 2U> &in2,
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
//
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//
//  Outputs :
//    u       : Resulting U for constant jerk
//    ud      : First derivative of u
//    udd     : Second derivative of u
//    jps     : Resulting Pseudo jerk
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
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> uddd;
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
    double b_jps;
    double d_ex;
    double d_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_loop_ub;
    int d_trueCount;
    int end_tmp;
    int iindx;
    int k_loop_ub;
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
    // 'zeroSpeedCurv:17' uk = 1;
    // 'zeroSpeedCurv:19' if( isEnd )
    // 'zeroSpeedCurv:19' uk = 1 - uk ;
    // 'zeroSpeedCurv:21' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    r_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:23' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv->tool.offset.z);
    // 'zeroSpeedCurv:25' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:26' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:30' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    // 'zeroSpeedCurv:35' searchJps = true;
    searchJps = true;
    // 'zeroSpeedCurv:37' ind = 0;
    // 'zeroSpeedCurv:38' while searchJps
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double b_fmax;
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int g_loop_ub;
        int h_k;
        int hi;
        int j_loop_ub;
        int m_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:39' ind = ind + 1;
        // 'zeroSpeedCurv:40' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        e_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:54' if( k > 0 )
        if (e_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:55' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(e_k) + 1);
            c_loop_ub = static_cast<int>(e_k);
            for (int i3{0}; i3 <= c_loop_ub; i3++) {
                k_vec[i3] = i3;
            }
            // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
            if (static_cast<int>(e_k) < e_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(e_k) + 2);
                f_loop_ub = static_cast<int>(e_k);
                for (int i6{0}; i6 <= f_loop_ub; i6++) {
                    k_vec[i6] = i6;
                }
                k_vec[static_cast<int>(e_k) + 1] = e_k;
            }
        } else {
            // 'zeroSpeedCurv:57' else
            // 'zeroSpeedCurv:58' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:41' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:79' if( isempty( ratio ) )
        // 'zeroSpeedCurv:81' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        k_vec.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            k_vec[i7] = k_vec[i7] * ctx_cfg_dt;
        }
        b_constJerkU(b_jps, k_vec, u, ud, udd, uddd);
        // 'zeroSpeedCurv:83' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        b_ctx_kin = *ctx_kin;
        calcRVAJfromU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                      ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                      ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                      ctx_cfg_NCart, ctx_cfg_NRot, &b_ctx_kin, curv->Info, &curv->tool, curv->R0,
                      curv->R1, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      curv->CoeffP5, curv->sp_index, curv->a_param, curv->b_param, u, ud, udd, uddd,
                      a__1, V, A, J);
        // 'zeroSpeedCurv:85' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:87' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
        c_ctx_kin = *ctx_kin;
        c_ctx_kin.set_tool_length(-curv->tool.offset.z);
        // 'zeroSpeedCurv:89' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int h_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            h_loop_ub = c_r1D.size(1) - 1;
            for (int i8{0}; i8 <= h_loop_ub; i8++) {
                int i_loop_ub;
                i_loop_ub = c_r1D.size(0) - 1;
                for (int i9{0}; i9 <= i_loop_ub; i9++) {
                    d_r1D[i9 + d_r1D.size(0) * i8] = c_r1D[i9 + c_r1D.size(0) * i8];
                }
            }
            c_ctx_kin.v_relative(b_r0D, d_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:90' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:95' safetyFactor = 0.5;
        // 'zeroSpeedCurv:96' fmax =  curv.Info.FeedRate * safetyFactor;
        b_fmax = curv->Info.FeedRate * 0.5;
        // 'zeroSpeedCurv:97' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int c_i{0}; c_i <= end_tmp; c_i++) {
            if (ctx_cfg_maskTot_data[c_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i10{0}; i10 < b_trueCount; i10++) {
            vmax_data[i10] = ctx_cfg_vmax[b_tmp_data[i10] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:98' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int d_i{0}; d_i <= end_tmp; d_i++) {
            if (ctx_cfg_maskTot_data[d_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i11{0}; i11 < c_trueCount; i11++) {
            amax_data[i11] = ctx_cfg_amax[c_tmp_data[i11] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int e_i{0}; e_i <= end_tmp; e_i++) {
            if (ctx_cfg_maskTot_data[e_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(e_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i12{0}; i12 < d_trueCount; i12++) {
            jmax_data[i12] = ctx_cfg_jmax[d_tmp_data[i12] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:101' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        j_loop_ub = c_r1D.size(1);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            y[i13] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            k_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int f_k{0}; f_k <= hi; f_k++) {
            xv.set_size(outsize_idx_0);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                xv[i14] = 0.0;
            }
            for (int g_k{0}; g_k < nx; g_k++) {
                xv[g_k] = c_r1D[(ctx_cfg_indCart[g_k] + c_r1D.size(0) * f_k) - 1];
            }
            y[f_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int l_loop_ub;
            feed.set_size(1, y.size(1));
            l_loop_ub = y.size(1);
            for (int i15{0}; i15 < l_loop_ub; i15++) {
                feed[i15] = y[i15] * ud[i15];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:103' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        m_loop_ub = feed.size(1);
        for (int i16{0}; i16 < m_loop_ub; i16++) {
            x[i16] = (feed[i16] > b_fmax);
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
            int n_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            n_loop_ub = feed.size(1);
            for (int i18{0}; i18 < n_loop_ub; i18++) {
                b_feed[i18] = feed[i18] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i17;
                i17 = V.size(1);
                for (int i_k{0}; i_k < i17; i_k++) {
                    int i19;
                    i19 = r.size(0);
                    for (int j_k{0}; j_k < i19; j_k++) {
                        r[j_k + r.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r.size(0) == b_trueCount) {
                int o_loop_ub;
                b_x.set_size(r.size(0), r.size(1));
                o_loop_ub = r.size(1);
                for (int i20{0}; i20 < o_loop_ub; i20++) {
                    int p_loop_ub;
                    p_loop_ub = r.size(0);
                    for (int i21{0}; i21 < p_loop_ub; i21++) {
                        b_x[i21 + b_x.size(0) * i20] = (r[i21 + r.size(0) * i20] > vmax_data[i21]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r, vmax_data, &b_trueCount);
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
                // 'zeroSpeedCurv:106' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:107' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r.size(0) == b_trueCount) {
                    int q_loop_ub;
                    int u_loop_ub;
                    r1.set_size(r.size(0), r.size(1));
                    q_loop_ub = r.size(1);
                    for (int i24{0}; i24 < q_loop_ub; i24++) {
                        int s_loop_ub;
                        s_loop_ub = r.size(0);
                        for (int i26{0}; i26 < s_loop_ub; i26++) {
                            r1[i26 + r1.size(0) * i24] = r[i26 + r.size(0) * i24] - vmax_data[i26];
                        }
                    }
                    r.set_size(r1.size(0), r1.size(1));
                    u_loop_ub = r1.size(1);
                    for (int i28{0}; i28 < u_loop_ub; i28++) {
                        int v_loop_ub;
                        v_loop_ub = r1.size(0);
                        for (int i29{0}; i29 < v_loop_ub; i29++) {
                            r[i29 + r.size(0) * i28] = r1[i29 + r1.size(0) * i28];
                        }
                    }
                    coder::internal::b_maximum(r, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i22;
                    i22 = A.size(1);
                    for (int l_k{0}; l_k < i22; l_k++) {
                        int i23;
                        i23 = r.size(0);
                        for (int m_k{0}; m_k < i23; m_k++) {
                            r[m_k + r.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r.size(0) == c_trueCount) {
                    int r_loop_ub;
                    b_x.set_size(r.size(0), r.size(1));
                    r_loop_ub = r.size(1);
                    for (int i25{0}; i25 < r_loop_ub; i25++) {
                        int t_loop_ub;
                        t_loop_ub = r.size(0);
                        for (int i27{0}; i27 < t_loop_ub; i27++) {
                            b_x[i27 + b_x.size(0) * i25] =
                                (r[i27 + r.size(0) * i25] > amax_data[i27]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r, amax_data, &c_trueCount);
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
                    // 'zeroSpeedCurv:109' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:110' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r.size(0) == c_trueCount) {
                        int bb_loop_ub;
                        int w_loop_ub;
                        r2.set_size(r.size(0), r.size(1));
                        w_loop_ub = r.size(1);
                        for (int i32{0}; i32 < w_loop_ub; i32++) {
                            int y_loop_ub;
                            y_loop_ub = r.size(0);
                            for (int i34{0}; i34 < y_loop_ub; i34++) {
                                r2[i34 + r2.size(0) * i32] =
                                    r[i34 + r.size(0) * i32] - amax_data[i34];
                            }
                        }
                        r.set_size(r2.size(0), r2.size(1));
                        bb_loop_ub = r2.size(1);
                        for (int i36{0}; i36 < bb_loop_ub; i36++) {
                            int cb_loop_ub;
                            cb_loop_ub = r2.size(0);
                            for (int i37{0}; i37 < cb_loop_ub; i37++) {
                                r[i37 + r.size(0) * i36] = r2[i37 + r2.size(0) * i36];
                            }
                        }
                        coder::internal::b_maximum(r, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i30;
                        i30 = J.size(1);
                        for (int o_k{0}; o_k < i30; o_k++) {
                            int i31;
                            i31 = r.size(0);
                            for (int p_k{0}; p_k < i31; p_k++) {
                                r[p_k + r.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r.size(0) == d_trueCount) {
                        int x_loop_ub;
                        b_x.set_size(r.size(0), r.size(1));
                        x_loop_ub = r.size(1);
                        for (int i33{0}; i33 < x_loop_ub; i33++) {
                            int ab_loop_ub;
                            ab_loop_ub = r.size(0);
                            for (int i35{0}; i35 < ab_loop_ub; i35++) {
                                b_x[i35 + b_x.size(0) * i33] =
                                    (r[i35 + r.size(0) * i33] > jmax_data[i35]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r, jmax_data, &d_trueCount);
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
                        // 'zeroSpeedCurv:112' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:113' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r.size(0) == d_trueCount) {
                            int db_loop_ub;
                            int fb_loop_ub;
                            r3.set_size(r.size(0), r.size(1));
                            db_loop_ub = r.size(1);
                            for (int i38{0}; i38 < db_loop_ub; i38++) {
                                int eb_loop_ub;
                                eb_loop_ub = r.size(0);
                                for (int i39{0}; i39 < eb_loop_ub; i39++) {
                                    r3[i39 + r3.size(0) * i38] =
                                        r[i39 + r.size(0) * i38] - jmax_data[i39];
                                }
                            }
                            r.set_size(r3.size(0), r3.size(1));
                            fb_loop_ub = r3.size(1);
                            for (int i40{0}; i40 < fb_loop_ub; i40++) {
                                int gb_loop_ub;
                                gb_loop_ub = r3.size(0);
                                for (int i41{0}; i41 < gb_loop_ub; i41++) {
                                    r[i41 + r.size(0) * i40] = r3[i41 + r3.size(0) * i40];
                                }
                            }
                            coder::internal::b_maximum(r, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:114' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:115' else
                        // 'zeroSpeedCurv:116' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:44' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:54' if( k > 0 )
    if (d_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:55' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(d_k) + 1);
        b_loop_ub = static_cast<int>(d_k);
        for (int i2{0}; i2 <= b_loop_ub; i2++) {
            k_vec[i2] = i2;
        }
        // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
        if (static_cast<int>(d_k) < d_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(d_k) + 2);
            e_loop_ub = static_cast<int>(d_k);
            for (int i5{0}; i5 <= e_loop_ub; i5++) {
                k_vec[i5] = i5;
            }
            k_vec[static_cast<int>(d_k) + 1] = d_k;
        }
    } else {
        // 'zeroSpeedCurv:57' else
        // 'zeroSpeedCurv:58' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:45' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    k_vec.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        k_vec[i4] = k_vec[i4] * ctx_cfg_dt;
    }
    constJerkU(b_jps, k_vec, u, ud, udd);
    *jps = b_jps;
}

//
// function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
//
// zeroSpeedCurv : Compute the profile paramater u in case of zero start /
//  stop. This approach assumes a constant pseudo jerk. The resulting profile
//  will respect the velocity, acceleration and jerk constraints.
//
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//
//  Outputs :
//    u       : Resulting U for constant jerk
//    ud      : First derivative of u
//    udd     : Second derivative of u
//    jps     : Resulting Pseudo jerk
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
void c_zeroSpeedCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
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
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> uddd;
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
    double b_jps;
    double d_ex;
    double d_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_loop_ub;
    int d_trueCount;
    int end_tmp;
    int iindx;
    int k_loop_ub;
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
    // 'zeroSpeedCurv:17' uk = 1;
    // 'zeroSpeedCurv:19' if( isEnd )
    // 'zeroSpeedCurv:19' uk = 1 - uk ;
    // 'zeroSpeedCurv:21' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    r_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:23' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv->tool.offset.z);
    // 'zeroSpeedCurv:25' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:26' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:30' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    // 'zeroSpeedCurv:35' searchJps = true;
    searchJps = true;
    // 'zeroSpeedCurv:37' ind = 0;
    // 'zeroSpeedCurv:38' while searchJps
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double b_fmax;
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int g_loop_ub;
        int h_k;
        int hi;
        int j_loop_ub;
        int m_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:39' ind = ind + 1;
        // 'zeroSpeedCurv:40' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        e_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:54' if( k > 0 )
        if (e_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:55' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(e_k) + 1);
            c_loop_ub = static_cast<int>(e_k);
            for (int i3{0}; i3 <= c_loop_ub; i3++) {
                k_vec[i3] = i3;
            }
            // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
            if (static_cast<int>(e_k) < e_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(e_k) + 2);
                f_loop_ub = static_cast<int>(e_k);
                for (int i6{0}; i6 <= f_loop_ub; i6++) {
                    k_vec[i6] = i6;
                }
                k_vec[static_cast<int>(e_k) + 1] = e_k;
            }
        } else {
            // 'zeroSpeedCurv:57' else
            // 'zeroSpeedCurv:58' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:41' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:79' if( isempty( ratio ) )
        if (!ratio_not_empty) {
            // 'zeroSpeedCurv:79' ratio = 0.9;
            ratio_not_empty = true;
        }
        // 'zeroSpeedCurv:81' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        k_vec.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            k_vec[i7] = k_vec[i7] * ctx_cfg_dt;
        }
        b_constJerkU(b_jps, k_vec, u, ud, udd, uddd);
        // 'zeroSpeedCurv:83' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        b_ctx_kin = *ctx_kin;
        b_calcRVAJfromU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, &b_ctx_kin, curv, u, ud, udd, uddd, a__1, V, A,
                        J);
        // 'zeroSpeedCurv:85' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        o_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:87' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
        c_ctx_kin = *ctx_kin;
        c_ctx_kin.set_tool_length(-curv->tool.offset.z);
        // 'zeroSpeedCurv:89' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int h_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            h_loop_ub = c_r1D.size(1) - 1;
            for (int i8{0}; i8 <= h_loop_ub; i8++) {
                int i_loop_ub;
                i_loop_ub = c_r1D.size(0) - 1;
                for (int i9{0}; i9 <= i_loop_ub; i9++) {
                    d_r1D[i9 + d_r1D.size(0) * i8] = c_r1D[i9 + c_r1D.size(0) * i8];
                }
            }
            c_ctx_kin.v_relative(b_r0D, d_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:90' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:95' safetyFactor = 0.5;
        // 'zeroSpeedCurv:96' fmax =  curv.Info.FeedRate * safetyFactor;
        b_fmax = curv->Info.FeedRate * 0.5;
        // 'zeroSpeedCurv:97' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int c_i{0}; c_i <= end_tmp; c_i++) {
            if (ctx_cfg_maskTot_data[c_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i10{0}; i10 < b_trueCount; i10++) {
            vmax_data[i10] = ctx_cfg_vmax[b_tmp_data[i10] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:98' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int d_i{0}; d_i <= end_tmp; d_i++) {
            if (ctx_cfg_maskTot_data[d_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i11{0}; i11 < c_trueCount; i11++) {
            amax_data[i11] = ctx_cfg_amax[c_tmp_data[i11] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int e_i{0}; e_i <= end_tmp; e_i++) {
            if (ctx_cfg_maskTot_data[e_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(e_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i12{0}; i12 < d_trueCount; i12++) {
            jmax_data[i12] = ctx_cfg_jmax[d_tmp_data[i12] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:101' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        j_loop_ub = c_r1D.size(1);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            y[i13] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            k_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int f_k{0}; f_k <= hi; f_k++) {
            xv.set_size(outsize_idx_0);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                xv[i14] = 0.0;
            }
            for (int g_k{0}; g_k < nx; g_k++) {
                xv[g_k] = c_r1D[(ctx_cfg_indCart[g_k] + c_r1D.size(0) * f_k) - 1];
            }
            y[f_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int l_loop_ub;
            feed.set_size(1, y.size(1));
            l_loop_ub = y.size(1);
            for (int i15{0}; i15 < l_loop_ub; i15++) {
                feed[i15] = y[i15] * ud[i15];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:103' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        m_loop_ub = feed.size(1);
        for (int i16{0}; i16 < m_loop_ub; i16++) {
            x[i16] = (feed[i16] > b_fmax);
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
            int n_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            n_loop_ub = feed.size(1);
            for (int i18{0}; i18 < n_loop_ub; i18++) {
                b_feed[i18] = feed[i18] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i17;
                i17 = V.size(1);
                for (int i_k{0}; i_k < i17; i_k++) {
                    int i19;
                    i19 = r.size(0);
                    for (int j_k{0}; j_k < i19; j_k++) {
                        r[j_k + r.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r.size(0) == b_trueCount) {
                int o_loop_ub;
                b_x.set_size(r.size(0), r.size(1));
                o_loop_ub = r.size(1);
                for (int i20{0}; i20 < o_loop_ub; i20++) {
                    int p_loop_ub;
                    p_loop_ub = r.size(0);
                    for (int i21{0}; i21 < p_loop_ub; i21++) {
                        b_x[i21 + b_x.size(0) * i20] = (r[i21 + r.size(0) * i20] > vmax_data[i21]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r, vmax_data, &b_trueCount);
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
                // 'zeroSpeedCurv:106' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:107' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r.size(0) == b_trueCount) {
                    int q_loop_ub;
                    int u_loop_ub;
                    r1.set_size(r.size(0), r.size(1));
                    q_loop_ub = r.size(1);
                    for (int i24{0}; i24 < q_loop_ub; i24++) {
                        int s_loop_ub;
                        s_loop_ub = r.size(0);
                        for (int i26{0}; i26 < s_loop_ub; i26++) {
                            r1[i26 + r1.size(0) * i24] = r[i26 + r.size(0) * i24] - vmax_data[i26];
                        }
                    }
                    r.set_size(r1.size(0), r1.size(1));
                    u_loop_ub = r1.size(1);
                    for (int i28{0}; i28 < u_loop_ub; i28++) {
                        int v_loop_ub;
                        v_loop_ub = r1.size(0);
                        for (int i29{0}; i29 < v_loop_ub; i29++) {
                            r[i29 + r.size(0) * i28] = r1[i29 + r1.size(0) * i28];
                        }
                    }
                    coder::internal::b_maximum(r, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i22;
                    i22 = A.size(1);
                    for (int l_k{0}; l_k < i22; l_k++) {
                        int i23;
                        i23 = r.size(0);
                        for (int m_k{0}; m_k < i23; m_k++) {
                            r[m_k + r.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r.size(0) == c_trueCount) {
                    int r_loop_ub;
                    b_x.set_size(r.size(0), r.size(1));
                    r_loop_ub = r.size(1);
                    for (int i25{0}; i25 < r_loop_ub; i25++) {
                        int t_loop_ub;
                        t_loop_ub = r.size(0);
                        for (int i27{0}; i27 < t_loop_ub; i27++) {
                            b_x[i27 + b_x.size(0) * i25] =
                                (r[i27 + r.size(0) * i25] > amax_data[i27]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r, amax_data, &c_trueCount);
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
                    // 'zeroSpeedCurv:109' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:110' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r.size(0) == c_trueCount) {
                        int bb_loop_ub;
                        int w_loop_ub;
                        r2.set_size(r.size(0), r.size(1));
                        w_loop_ub = r.size(1);
                        for (int i32{0}; i32 < w_loop_ub; i32++) {
                            int y_loop_ub;
                            y_loop_ub = r.size(0);
                            for (int i34{0}; i34 < y_loop_ub; i34++) {
                                r2[i34 + r2.size(0) * i32] =
                                    r[i34 + r.size(0) * i32] - amax_data[i34];
                            }
                        }
                        r.set_size(r2.size(0), r2.size(1));
                        bb_loop_ub = r2.size(1);
                        for (int i36{0}; i36 < bb_loop_ub; i36++) {
                            int cb_loop_ub;
                            cb_loop_ub = r2.size(0);
                            for (int i37{0}; i37 < cb_loop_ub; i37++) {
                                r[i37 + r.size(0) * i36] = r2[i37 + r2.size(0) * i36];
                            }
                        }
                        coder::internal::b_maximum(r, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i30;
                        i30 = J.size(1);
                        for (int o_k{0}; o_k < i30; o_k++) {
                            int i31;
                            i31 = r.size(0);
                            for (int p_k{0}; p_k < i31; p_k++) {
                                r[p_k + r.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r.size(0) == d_trueCount) {
                        int x_loop_ub;
                        b_x.set_size(r.size(0), r.size(1));
                        x_loop_ub = r.size(1);
                        for (int i33{0}; i33 < x_loop_ub; i33++) {
                            int ab_loop_ub;
                            ab_loop_ub = r.size(0);
                            for (int i35{0}; i35 < ab_loop_ub; i35++) {
                                b_x[i35 + b_x.size(0) * i33] =
                                    (r[i35 + r.size(0) * i33] > jmax_data[i35]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r, jmax_data, &d_trueCount);
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
                        // 'zeroSpeedCurv:112' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:113' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r.size(0) == d_trueCount) {
                            int db_loop_ub;
                            int fb_loop_ub;
                            r3.set_size(r.size(0), r.size(1));
                            db_loop_ub = r.size(1);
                            for (int i38{0}; i38 < db_loop_ub; i38++) {
                                int eb_loop_ub;
                                eb_loop_ub = r.size(0);
                                for (int i39{0}; i39 < eb_loop_ub; i39++) {
                                    r3[i39 + r3.size(0) * i38] =
                                        r[i39 + r.size(0) * i38] - jmax_data[i39];
                                }
                            }
                            r.set_size(r3.size(0), r3.size(1));
                            fb_loop_ub = r3.size(1);
                            for (int i40{0}; i40 < fb_loop_ub; i40++) {
                                int gb_loop_ub;
                                gb_loop_ub = r3.size(0);
                                for (int i41{0}; i41 < gb_loop_ub; i41++) {
                                    r[i41 + r.size(0) * i40] = r3[i41 + r3.size(0) * i40];
                                }
                            }
                            coder::internal::b_maximum(r, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:114' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:115' else
                        // 'zeroSpeedCurv:116' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:44' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:54' if( k > 0 )
    if (d_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:55' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(d_k) + 1);
        b_loop_ub = static_cast<int>(d_k);
        for (int i2{0}; i2 <= b_loop_ub; i2++) {
            k_vec[i2] = i2;
        }
        // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
        if (static_cast<int>(d_k) < d_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(d_k) + 2);
            e_loop_ub = static_cast<int>(d_k);
            for (int i5{0}; i5 <= e_loop_ub; i5++) {
                k_vec[i5] = i5;
            }
            k_vec[static_cast<int>(d_k) + 1] = d_k;
        }
    } else {
        // 'zeroSpeedCurv:57' else
        // 'zeroSpeedCurv:58' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:45' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    k_vec.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        k_vec[i4] = k_vec[i4] * ctx_cfg_dt;
    }
    constJerkU(b_jps, k_vec, u, ud, udd);
    *jps = b_jps;
}

//
// function [ searchJps, jps, u, ud, udd ] = calc_u( isEnd, searchJps, jps, ctx, ...
//     curv, k_vec  )
//
// calc_u : Calcule u for a given pseudo jerk. U is assured to give velocity,
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
//
// Arguments    : void
// Return Type  : void
//
void calc_u_init()
{
    // 'zeroSpeedCurv:79' ratio = 0.9;
    ratio_not_empty = true;
}

//
// function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
//
// zeroSpeedCurv : Compute the profile paramater u in case of zero start /
//  stop. This approach assumes a constant pseudo jerk. The resulting profile
//  will respect the velocity, acceleration and jerk constraints.
//
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//
//  Outputs :
//    u       : Resulting U for constant jerk
//    ud      : First derivative of u
//    udd     : Second derivative of u
//    jps     : Resulting Pseudo jerk
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
void d_zeroSpeedCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
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
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> uddd;
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
    double b_ex;
    double b_jps;
    double c_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int ctx_cfg_jmax_size[2];
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
    int l_loop_ub;
    int last;
    int n_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:17' uk = 1;
    // 'zeroSpeedCurv:19' if( isEnd )
    // 'zeroSpeedCurv:21' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    n_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:23' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv->tool.offset.z);
    // 'zeroSpeedCurv:25' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:26' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:30' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    // 'zeroSpeedCurv:35' searchJps = true;
    searchJps = true;
    // 'zeroSpeedCurv:37' ind = 0;
    // 'zeroSpeedCurv:38' while searchJps
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double b_fmax;
        double c_jps;
        double d_k;
        int b_partialTrueCount;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int g_k;
        int g_loop_ub;
        int hi;
        int o_loop_ub;
        int r_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:39' ind = ind + 1;
        // 'zeroSpeedCurv:40' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:54' if( k > 0 )
        if (d_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:55' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(d_k) + 1);
            c_loop_ub = static_cast<int>(d_k);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
            if (static_cast<int>(d_k) < d_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(d_k) + 2);
                f_loop_ub = static_cast<int>(d_k);
                for (int i7{0}; i7 <= f_loop_ub; i7++) {
                    k_vec[i7] = i7;
                }
                k_vec[static_cast<int>(d_k) + 1] = d_k;
            }
        } else {
            // 'zeroSpeedCurv:57' else
            // 'zeroSpeedCurv:58' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:41' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:79' if( isempty( ratio ) )
        if (!ratio_not_empty) {
            // 'zeroSpeedCurv:79' ratio = 0.9;
            ratio_not_empty = true;
        }
        // 'zeroSpeedCurv:81' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        k_vec.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            k_vec[i8] = k_vec[i8] * ctx_cfg_dt;
        }
        constJerkU(b_jps, k_vec, u, ud, udd, uddd);
        // 'zeroSpeedCurv:83' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        b_ctx_kin = *ctx_kin;
        b_calcRVAJfromU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, &b_ctx_kin, curv, u, ud, udd, uddd, a__1, V, A,
                        J);
        // 'zeroSpeedCurv:85' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        o_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:87' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
        c_ctx_kin = *ctx_kin;
        c_ctx_kin.set_tool_length(-curv->tool.offset.z);
        // 'zeroSpeedCurv:89' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int k_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            k_loop_ub = c_r1D.size(1) - 1;
            for (int i12{0}; i12 <= k_loop_ub; i12++) {
                int m_loop_ub;
                m_loop_ub = c_r1D.size(0) - 1;
                for (int i14{0}; i14 <= m_loop_ub; i14++) {
                    d_r1D[i14 + d_r1D.size(0) * i12] = c_r1D[i14 + c_r1D.size(0) * i12];
                }
            }
            c_ctx_kin.v_relative(b_r0D, d_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:90' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:95' safetyFactor = 0.5;
        // 'zeroSpeedCurv:96' fmax =  curv.Info.FeedRate * safetyFactor;
        b_fmax = curv->Info.FeedRate * 0.5;
        // 'zeroSpeedCurv:97' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int c_i{0}; c_i <= end_tmp; c_i++) {
            if (ctx_cfg_maskTot_data[c_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i16{0}; i16 < b_trueCount; i16++) {
            vmax_data[i16] = ctx_cfg_vmax[b_tmp_data[i16] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:98' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int e_i{0}; e_i <= end_tmp; e_i++) {
            if (ctx_cfg_maskTot_data[e_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(e_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i17{0}; i17 < c_trueCount; i17++) {
            amax_data[i17] = ctx_cfg_amax[c_tmp_data[i17] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(g_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i18{0}; i18 < d_trueCount; i18++) {
            jmax_data[i18] = ctx_cfg_jmax[d_tmp_data[i18] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:101' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        o_loop_ub = c_r1D.size(1);
        for (int i19{0}; i19 < o_loop_ub; i19++) {
            y[i19] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            p_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int e_k{0}; e_k <= hi; e_k++) {
            xv.set_size(outsize_idx_0);
            for (int i20{0}; i20 < p_loop_ub; i20++) {
                xv[i20] = 0.0;
            }
            for (int f_k{0}; f_k < nx; f_k++) {
                xv[f_k] = c_r1D[(ctx_cfg_indCart[f_k] + c_r1D.size(0) * e_k) - 1];
            }
            y[e_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int q_loop_ub;
            feed.set_size(1, y.size(1));
            q_loop_ub = y.size(1);
            for (int i21{0}; i21 < q_loop_ub; i21++) {
                feed[i21] = y[i21] * ud[i21];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:103' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        r_loop_ub = feed.size(1);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            x[i22] = (feed[i22] > b_fmax);
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
            int s_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            s_loop_ub = feed.size(1);
            for (int i24{0}; i24 < s_loop_ub; i24++) {
                b_feed[i24] = feed[i24] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool varargout_1;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i23;
                i23 = V.size(1);
                for (int h_k{0}; h_k < i23; h_k++) {
                    int i25;
                    i25 = r1.size(0);
                    for (int i_k{0}; i_k < i25; i_k++) {
                        r1[i_k + r1.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int t_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                t_loop_ub = r1.size(1);
                for (int i26{0}; i26 < t_loop_ub; i26++) {
                    int u_loop_ub;
                    u_loop_ub = r1.size(0);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        b_x[i27 + b_x.size(0) * i26] =
                            (r1[i27 + r1.size(0) * i26] > vmax_data[i27]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
            }
            varargout_1 = false;
            j_k = 0;
            exitg1 = false;
            while ((!exitg1) && (j_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[j_k]) {
                    varargout_1 = true;
                    exitg1 = true;
                } else {
                    j_k++;
                }
            }
            if (varargout_1) {
                // 'zeroSpeedCurv:106' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:107' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r1.size(0) == b_trueCount) {
                    int ab_loop_ub;
                    int v_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    v_loop_ub = r1.size(1);
                    for (int i30{0}; i30 < v_loop_ub; i30++) {
                        int x_loop_ub;
                        x_loop_ub = r1.size(0);
                        for (int i32{0}; i32 < x_loop_ub; i32++) {
                            r2[i32 + r2.size(0) * i30] =
                                r1[i32 + r1.size(0) * i30] - vmax_data[i32];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    ab_loop_ub = r2.size(1);
                    for (int i34{0}; i34 < ab_loop_ub; i34++) {
                        int bb_loop_ub;
                        bb_loop_ub = r2.size(0);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            r1[i35 + r1.size(0) * i34] = r2[i35 + r2.size(0) * i34];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool b_varargout_1;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i28;
                    i28 = A.size(1);
                    for (int k_k{0}; k_k < i28; k_k++) {
                        int i29;
                        i29 = r1.size(0);
                        for (int l_k{0}; l_k < i29; l_k++) {
                            r1[l_k + r1.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int w_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    w_loop_ub = r1.size(1);
                    for (int i31{0}; i31 < w_loop_ub; i31++) {
                        int y_loop_ub;
                        y_loop_ub = r1.size(0);
                        for (int i33{0}; i33 < y_loop_ub; i33++) {
                            b_x[i33 + b_x.size(0) * i31] =
                                (r1[i33 + r1.size(0) * i31] > amax_data[i33]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
                }
                b_varargout_1 = false;
                m_k = 0;
                exitg1 = false;
                while ((!exitg1) && (m_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[m_k]) {
                        b_varargout_1 = true;
                        exitg1 = true;
                    } else {
                        m_k++;
                    }
                }
                if (b_varargout_1) {
                    // 'zeroSpeedCurv:109' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:110' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r1.size(0) == c_trueCount) {
                        int cb_loop_ub;
                        int gb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        cb_loop_ub = r1.size(1);
                        for (int i38{0}; i38 < cb_loop_ub; i38++) {
                            int eb_loop_ub;
                            eb_loop_ub = r1.size(0);
                            for (int i40{0}; i40 < eb_loop_ub; i40++) {
                                r3[i40 + r3.size(0) * i38] =
                                    r1[i40 + r1.size(0) * i38] - amax_data[i40];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        gb_loop_ub = r3.size(1);
                        for (int i42{0}; i42 < gb_loop_ub; i42++) {
                            int hb_loop_ub;
                            hb_loop_ub = r3.size(0);
                            for (int i43{0}; i43 < hb_loop_ub; i43++) {
                                r1[i43 + r1.size(0) * i42] = r3[i43 + r3.size(0) * i42];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool c_varargout_1;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i36;
                        i36 = J.size(1);
                        for (int n_k{0}; n_k < i36; n_k++) {
                            int i37;
                            i37 = r1.size(0);
                            for (int o_k{0}; o_k < i37; o_k++) {
                                r1[o_k + r1.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int db_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        db_loop_ub = r1.size(1);
                        for (int i39{0}; i39 < db_loop_ub; i39++) {
                            int fb_loop_ub;
                            fb_loop_ub = r1.size(0);
                            for (int i41{0}; i41 < fb_loop_ub; i41++) {
                                b_x[i41 + b_x.size(0) * i39] =
                                    (r1[i41 + r1.size(0) * i39] > jmax_data[i41]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
                    }
                    c_varargout_1 = false;
                    p_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (p_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[p_k]) {
                            c_varargout_1 = true;
                            exitg1 = true;
                        } else {
                            p_k++;
                        }
                    }
                    if (c_varargout_1) {
                        // 'zeroSpeedCurv:112' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:113' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r1.size(0) == d_trueCount) {
                            int ib_loop_ub;
                            int kb_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            ib_loop_ub = r1.size(1);
                            for (int i44{0}; i44 < ib_loop_ub; i44++) {
                                int jb_loop_ub;
                                jb_loop_ub = r1.size(0);
                                for (int i45{0}; i45 < jb_loop_ub; i45++) {
                                    r4[i45 + r4.size(0) * i44] =
                                        r1[i45 + r1.size(0) * i44] - jmax_data[i45];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            kb_loop_ub = r4.size(1);
                            for (int i46{0}; i46 < kb_loop_ub; i46++) {
                                int lb_loop_ub;
                                lb_loop_ub = r4.size(0);
                                for (int i47{0}; i47 < lb_loop_ub; i47++) {
                                    r1[i47 + r1.size(0) * i46] = r4[i47 + r4.size(0) * i46];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:114' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:115' else
                        // 'zeroSpeedCurv:116' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:44' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    c_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:54' if( k > 0 )
    if (c_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:55' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(c_k) + 1);
        b_loop_ub = static_cast<int>(c_k);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
        if (static_cast<int>(c_k) < c_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(c_k) + 2);
            e_loop_ub = static_cast<int>(c_k);
            for (int i6{0}; i6 <= e_loop_ub; i6++) {
                k_vec[i6] = i6;
            }
            k_vec[static_cast<int>(c_k) + 1] = c_k;
        }
    } else {
        // 'zeroSpeedCurv:57' else
        // 'zeroSpeedCurv:58' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:45' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        y[i5] = k_vec[i5] * ctx_cfg_dt;
    }
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The constant Jerk value
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    //
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    udd.set_size(1, y.size(1));
    h_loop_ub = y.size(1);
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        udd[i9] = b_jps * y[i9];
    }
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
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
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    l_loop_ub = y.size(1);
    for (int i13{0}; i13 < l_loop_ub; i13++) {
        double b_varargin_1;
        b_varargin_1 = y[i13];
        r[i13] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    n_loop_ub = r.size(1);
    for (int i15{0}; i15 < n_loop_ub; i15++) {
        u[i15] = b_jps * r[i15] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int d_i{0}; d_i < end; d_i++) {
        if (u[d_i] > 1.0) {
            u[d_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int f_i{0}; f_i < b_end; f_i++) {
        if (u[f_i] < 0.0) {
            u[f_i] = 0.0;
        }
    }
    // 'constJerkU:40' if( isEnd )
    *jps = b_jps;
}

//
// Arguments    : void
// Return Type  : void
//
void ratio_not_empty_init()
{
    ratio_not_empty = false;
}

//
// function [ u, ud, udd, jps ] = zeroSpeedCurv( ctx, curv, isEnd )
//
// zeroSpeedCurv : Compute the profile paramater u in case of zero start /
//  stop. This approach assumes a constant pseudo jerk. The resulting profile
//  will respect the velocity, acceleration and jerk constraints.
//
//  Inputs  :
//    ctx     : The context
//    curv    : The Curve Struct
//    isEnd   : ( Boolean ) is the end of a curve
//
//  Outputs :
//    u       : Resulting U for constant jerk
//    ud      : First derivative of u
//    udd     : Second derivative of u
//    jps     : Resulting Pseudo jerk
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
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> uddd;
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
    double b_ex;
    double b_jps;
    double c_k;
    double f_delta;
    double j_delta;
    double v_delta;
    int ctx_cfg_jmax_size[2];
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
    int last;
    int m_loop_ub;
    int n_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:17' uk = 1;
    // 'zeroSpeedCurv:19' if( isEnd )
    // 'zeroSpeedCurv:21' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
    n_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D);
    // 'zeroSpeedCurv:23' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
    ctx_kin->set_tool_length(-curv->tool.offset.z);
    // 'zeroSpeedCurv:25' if( curv.Info.TRAFO )
    if (curv->Info.TRAFO) {
        int loop_ub;
        // 'zeroSpeedCurv:26' r1D = ctx.kin.v_joint( r0D, r1D );
        b_r1D.set_size(r1D.size(0));
        loop_ub = r1D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r1D[i] = r1D[i];
        }
        ctx_kin->v_joint(r0D, b_r1D, r1D);
    }
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:30' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
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
    // 'zeroSpeedCurv:35' searchJps = true;
    searchJps = true;
    // 'zeroSpeedCurv:37' ind = 0;
    // 'zeroSpeedCurv:38' while searchJps
    while (searchJps) {
        double amax_data[6];
        double jmax_data[6];
        double vmax_data[6];
        double b_fmax;
        double c_jps;
        double d_k;
        int b_partialTrueCount;
        int c_partialTrueCount;
        int d_partialTrueCount;
        int g_k;
        int g_loop_ub;
        int hi;
        int o_loop_ub;
        int r_loop_ub;
        bool b_y;
        bool exitg1;
        // 'zeroSpeedCurv:39' ind = ind + 1;
        // 'zeroSpeedCurv:40' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
        //  compute_k : Compute the vector of time steps required by the paramter u to
        //  go from 0 to 1.
        // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
        d_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
        // 'zeroSpeedCurv:54' if( k > 0 )
        if (d_k > 0.0) {
            int c_loop_ub;
            // 'zeroSpeedCurv:55' k_vec = 0 : k;
            k_vec.set_size(1, static_cast<int>(d_k) + 1);
            c_loop_ub = static_cast<int>(d_k);
            for (int i4{0}; i4 <= c_loop_ub; i4++) {
                k_vec[i4] = i4;
            }
            // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
            if (static_cast<int>(d_k) < d_k) {
                int f_loop_ub;
                // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
                k_vec.set_size(1, static_cast<int>(d_k) + 2);
                f_loop_ub = static_cast<int>(d_k);
                for (int i7{0}; i7 <= f_loop_ub; i7++) {
                    k_vec[i7] = i7;
                }
                k_vec[static_cast<int>(d_k) + 1] = d_k;
            }
        } else {
            // 'zeroSpeedCurv:57' else
            // 'zeroSpeedCurv:58' k_vec = 1;
            k_vec.set_size(1, 1);
            k_vec[0] = 1.0;
        }
        // 'zeroSpeedCurv:41' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv, k_vec );
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
        // 'zeroSpeedCurv:79' if( isempty( ratio ) )
        // 'zeroSpeedCurv:81' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd,
        // true );
        k_vec.set_size(1, k_vec.size(1));
        g_loop_ub = k_vec.size(1);
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            k_vec[i8] = k_vec[i8] * ctx_cfg_dt;
        }
        constJerkU(b_jps, k_vec, u, ud, udd, uddd);
        // 'zeroSpeedCurv:83' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        b_ctx_kin = *ctx_kin;
        calcRVAJfromU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                      ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                      ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                      ctx_cfg_NCart, ctx_cfg_NRot, &b_ctx_kin, curv->Info, &curv->tool, curv->R0,
                      curv->R1, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      curv->CoeffP5, curv->sp_index, curv->a_param, curv->b_param, u, ud, udd, uddd,
                      a__1, V, A, J);
        // 'zeroSpeedCurv:85' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, u, b_r0D, c_r1D);
        // 'zeroSpeedCurv:87' ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );
        c_ctx_kin = *ctx_kin;
        c_ctx_kin.set_tool_length(-curv->tool.offset.z);
        // 'zeroSpeedCurv:89' if( curv.Info.TRAFO )
        if (!curv->Info.TRAFO) {
            int k_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            k_loop_ub = c_r1D.size(1) - 1;
            for (int i12{0}; i12 <= k_loop_ub; i12++) {
                int l_loop_ub;
                l_loop_ub = c_r1D.size(0) - 1;
                for (int i13{0}; i13 <= l_loop_ub; i13++) {
                    d_r1D[i13 + d_r1D.size(0) * i12] = c_r1D[i13 + c_r1D.size(0) * i12];
                }
            }
            c_ctx_kin.v_relative(b_r0D, d_r1D, c_r1D);
        } else {
            // 'zeroSpeedCurv:90' r1D_r     = r1D;
        }
        // 'zeroSpeedCurv:95' safetyFactor = 0.5;
        // 'zeroSpeedCurv:96' fmax =  curv.Info.FeedRate * safetyFactor;
        b_fmax = curv->Info.FeedRate * 0.5;
        // 'zeroSpeedCurv:97' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
        b_trueCount = 0;
        b_partialTrueCount = 0;
        for (int c_i{0}; c_i <= end_tmp; c_i++) {
            if (ctx_cfg_maskTot_data[c_i]) {
                b_trueCount++;
                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                b_partialTrueCount++;
            }
        }
        for (int i15{0}; i15 < b_trueCount; i15++) {
            vmax_data[i15] = ctx_cfg_vmax[b_tmp_data[i15] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:98' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
        c_trueCount = 0;
        c_partialTrueCount = 0;
        for (int d_i{0}; d_i <= end_tmp; d_i++) {
            if (ctx_cfg_maskTot_data[d_i]) {
                c_trueCount++;
                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
                c_partialTrueCount++;
            }
        }
        for (int i17{0}; i17 < c_trueCount; i17++) {
            amax_data[i17] = ctx_cfg_amax[c_tmp_data[i17] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:99' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
        d_trueCount = 0;
        d_partialTrueCount = 0;
        for (int g_i{0}; g_i <= end_tmp; g_i++) {
            if (ctx_cfg_maskTot_data[g_i]) {
                d_trueCount++;
                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(g_i + 1);
                d_partialTrueCount++;
            }
        }
        for (int i18{0}; i18 < d_trueCount; i18++) {
            jmax_data[i18] = ctx_cfg_jmax[d_tmp_data[i18] - 1] * 0.5;
        }
        // 'zeroSpeedCurv:101' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
        y.set_size(1, c_r1D.size(1));
        o_loop_ub = c_r1D.size(1);
        for (int i19{0}; i19 < o_loop_ub; i19++) {
            y[i19] = 0.0;
        }
        hi = c_r1D.size(1) - 1;
        if (c_r1D.size(1) - 1 >= 0) {
            nx = ctx_cfg_indCart.size(0);
            outsize_idx_0 = static_cast<signed char>(ctx_cfg_indCart.size(0));
            p_loop_ub = static_cast<signed char>(ctx_cfg_indCart.size(0));
        }
        for (int e_k{0}; e_k <= hi; e_k++) {
            xv.set_size(outsize_idx_0);
            for (int i20{0}; i20 < p_loop_ub; i20++) {
                xv[i20] = 0.0;
            }
            for (int f_k{0}; f_k < nx; f_k++) {
                xv[f_k] = c_r1D[(ctx_cfg_indCart[f_k] + c_r1D.size(0) * e_k) - 1];
            }
            y[e_k] = coder::b_norm(xv);
        }
        if (y.size(1) == ud.size(1)) {
            int q_loop_ub;
            feed.set_size(1, y.size(1));
            q_loop_ub = y.size(1);
            for (int i21{0}; i21 < q_loop_ub; i21++) {
                feed[i21] = y[i21] * ud[i21];
            }
        } else {
            times(feed, y, ud);
        }
        // 'zeroSpeedCurv:103' if( any( feed > fmax ) )
        x.set_size(1, feed.size(1));
        r_loop_ub = feed.size(1);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            x[i22] = (feed[i22] > b_fmax);
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
            int s_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            s_loop_ub = feed.size(1);
            for (int i24{0}; i24 < s_loop_ub; i24++) {
                b_feed[i24] = feed[i24] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool varargout_1;
            r1.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i23;
                i23 = V.size(1);
                for (int h_k{0}; h_k < i23; h_k++) {
                    int i25;
                    i25 = r1.size(0);
                    for (int i_k{0}; i_k < i25; i_k++) {
                        r1[i_k + r1.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (r1.size(0) == b_trueCount) {
                int t_loop_ub;
                b_x.set_size(r1.size(0), r1.size(1));
                t_loop_ub = r1.size(1);
                for (int i26{0}; i26 < t_loop_ub; i26++) {
                    int u_loop_ub;
                    u_loop_ub = r1.size(0);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        b_x[i27 + b_x.size(0) * i26] =
                            (r1[i27 + r1.size(0) * i26] > vmax_data[i27]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r1, vmax_data, &b_trueCount);
            }
            varargout_1 = false;
            j_k = 0;
            exitg1 = false;
            while ((!exitg1) && (j_k <= b_x.size(0) * b_x.size(1) - 1)) {
                if (b_x[j_k]) {
                    varargout_1 = true;
                    exitg1 = true;
                } else {
                    j_k++;
                }
            }
            if (varargout_1) {
                // 'zeroSpeedCurv:106' elseif( any( abs( V ) > vmax, 'all' ) )
                // 'zeroSpeedCurv:107' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                if (r1.size(0) == b_trueCount) {
                    int ab_loop_ub;
                    int v_loop_ub;
                    r2.set_size(r1.size(0), r1.size(1));
                    v_loop_ub = r1.size(1);
                    for (int i30{0}; i30 < v_loop_ub; i30++) {
                        int x_loop_ub;
                        x_loop_ub = r1.size(0);
                        for (int i32{0}; i32 < x_loop_ub; i32++) {
                            r2[i32 + r2.size(0) * i30] =
                                r1[i32 + r1.size(0) * i30] - vmax_data[i32];
                        }
                    }
                    r1.set_size(r2.size(0), r2.size(1));
                    ab_loop_ub = r2.size(1);
                    for (int i34{0}; i34 < ab_loop_ub; i34++) {
                        int bb_loop_ub;
                        bb_loop_ub = r2.size(0);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            r1[i35 + r1.size(0) * i34] = r2[i35 + r2.size(0) * i34];
                        }
                    }
                    coder::internal::b_maximum(r1, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r1, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool b_varargout_1;
                r1.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i28;
                    i28 = A.size(1);
                    for (int k_k{0}; k_k < i28; k_k++) {
                        int i29;
                        i29 = r1.size(0);
                        for (int l_k{0}; l_k < i29; l_k++) {
                            r1[l_k + r1.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (r1.size(0) == c_trueCount) {
                    int w_loop_ub;
                    b_x.set_size(r1.size(0), r1.size(1));
                    w_loop_ub = r1.size(1);
                    for (int i31{0}; i31 < w_loop_ub; i31++) {
                        int y_loop_ub;
                        y_loop_ub = r1.size(0);
                        for (int i33{0}; i33 < y_loop_ub; i33++) {
                            b_x[i33 + b_x.size(0) * i31] =
                                (r1[i33 + r1.size(0) * i31] > amax_data[i33]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r1, amax_data, &c_trueCount);
                }
                b_varargout_1 = false;
                m_k = 0;
                exitg1 = false;
                while ((!exitg1) && (m_k <= b_x.size(0) * b_x.size(1) - 1)) {
                    if (b_x[m_k]) {
                        b_varargout_1 = true;
                        exitg1 = true;
                    } else {
                        m_k++;
                    }
                }
                if (b_varargout_1) {
                    // 'zeroSpeedCurv:109' elseif( any( abs( A ) > amax, 'all' ) )
                    // 'zeroSpeedCurv:110' [ a_delta, ind ] = max( abs( A ) - amax, [], 'all' );
                    if (r1.size(0) == c_trueCount) {
                        int cb_loop_ub;
                        int gb_loop_ub;
                        r3.set_size(r1.size(0), r1.size(1));
                        cb_loop_ub = r1.size(1);
                        for (int i38{0}; i38 < cb_loop_ub; i38++) {
                            int eb_loop_ub;
                            eb_loop_ub = r1.size(0);
                            for (int i40{0}; i40 < eb_loop_ub; i40++) {
                                r3[i40 + r3.size(0) * i38] =
                                    r1[i40 + r1.size(0) * i38] - amax_data[i40];
                            }
                        }
                        r1.set_size(r3.size(0), r3.size(1));
                        gb_loop_ub = r3.size(1);
                        for (int i42{0}; i42 < gb_loop_ub; i42++) {
                            int hb_loop_ub;
                            hb_loop_ub = r3.size(0);
                            for (int i43{0}; i43 < hb_loop_ub; i43++) {
                                r1[i43 + r1.size(0) * i42] = r3[i43 + r3.size(0) * i42];
                            }
                        }
                        coder::internal::b_maximum(r1, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r1, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool c_varargout_1;
                    r1.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i36;
                        i36 = J.size(1);
                        for (int n_k{0}; n_k < i36; n_k++) {
                            int i37;
                            i37 = r1.size(0);
                            for (int o_k{0}; o_k < i37; o_k++) {
                                r1[o_k + r1.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (r1.size(0) == d_trueCount) {
                        int db_loop_ub;
                        b_x.set_size(r1.size(0), r1.size(1));
                        db_loop_ub = r1.size(1);
                        for (int i39{0}; i39 < db_loop_ub; i39++) {
                            int fb_loop_ub;
                            fb_loop_ub = r1.size(0);
                            for (int i41{0}; i41 < fb_loop_ub; i41++) {
                                b_x[i41 + b_x.size(0) * i39] =
                                    (r1[i41 + r1.size(0) * i39] > jmax_data[i41]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r1, jmax_data, &d_trueCount);
                    }
                    c_varargout_1 = false;
                    p_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (p_k <= b_x.size(0) * b_x.size(1) - 1)) {
                        if (b_x[p_k]) {
                            c_varargout_1 = true;
                            exitg1 = true;
                        } else {
                            p_k++;
                        }
                    }
                    if (c_varargout_1) {
                        // 'zeroSpeedCurv:112' elseif( any( abs( J ) > jmax, 'all' ) )
                        // 'zeroSpeedCurv:113' [ j_delta, ind ] = max( abs( J ) - jmax, [], 'all' );
                        if (r1.size(0) == d_trueCount) {
                            int ib_loop_ub;
                            int kb_loop_ub;
                            r4.set_size(r1.size(0), r1.size(1));
                            ib_loop_ub = r1.size(1);
                            for (int i44{0}; i44 < ib_loop_ub; i44++) {
                                int jb_loop_ub;
                                jb_loop_ub = r1.size(0);
                                for (int i45{0}; i45 < jb_loop_ub; i45++) {
                                    r4[i45 + r4.size(0) * i44] =
                                        r1[i45 + r1.size(0) * i44] - jmax_data[i45];
                                }
                            }
                            r1.set_size(r4.size(0), r4.size(1));
                            kb_loop_ub = r4.size(1);
                            for (int i46{0}; i46 < kb_loop_ub; i46++) {
                                int lb_loop_ub;
                                lb_loop_ub = r4.size(0);
                                for (int i47{0}; i47 < lb_loop_ub; i47++) {
                                    r1[i47 + r1.size(0) * i46] = r4[i47 + r4.size(0) * i46];
                                }
                            }
                            coder::internal::b_maximum(r1, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r1, jmax_data, &d_trueCount, &j_delta, &d_iindx);
                        }
                        // 'zeroSpeedCurv:114' jps = jps * ( 1 - ratio * ( 1 - j_delta / abs( J( ind
                        // ) ) ) );
                        c_jps = b_jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
                    } else {
                        // 'zeroSpeedCurv:115' else
                        // 'zeroSpeedCurv:116' searchJps = false;
                        searchJps = false;
                    }
                }
            }
        }
        b_jps = c_jps;
    }
    // 'zeroSpeedCurv:44' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
    //  compute_k : Compute the vector of time steps required by the paramter u to
    //  go from 0 to 1.
    // 'zeroSpeedCurv:52' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
    c_k = std::pow(6.0 / b_jps, 0.33333333333333331) / ctx_cfg_dt;
    // 'zeroSpeedCurv:54' if( k > 0 )
    if (c_k > 0.0) {
        int b_loop_ub;
        // 'zeroSpeedCurv:55' k_vec = 0 : k;
        k_vec.set_size(1, static_cast<int>(c_k) + 1);
        b_loop_ub = static_cast<int>(c_k);
        for (int i3{0}; i3 <= b_loop_ub; i3++) {
            k_vec[i3] = i3;
        }
        // 'zeroSpeedCurv:56' if( k_vec( end ) < k )
        if (static_cast<int>(c_k) < c_k) {
            int e_loop_ub;
            // 'zeroSpeedCurv:56' k_vec = [ k_vec, k ];
            k_vec.set_size(1, static_cast<int>(c_k) + 2);
            e_loop_ub = static_cast<int>(c_k);
            for (int i6{0}; i6 <= e_loop_ub; i6++) {
                k_vec[i6] = i6;
            }
            k_vec[static_cast<int>(c_k) + 1] = c_k;
        }
    } else {
        // 'zeroSpeedCurv:57' else
        // 'zeroSpeedCurv:58' k_vec = 1;
        k_vec.set_size(1, 1);
        k_vec[0] = 1.0;
    }
    // 'zeroSpeedCurv:45' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd, true);
    y.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        y[i5] = k_vec[i5] * ctx_cfg_dt;
    }
    //  constJerkU : Compute u and its derivative based on the pseudo jerk
    //  approximation.
    //
    //  Inputs :
    //    pseudoJerk      :  [ N x 1 ] The constant Jerk value
    //    k_vec           :  [ 1 x M ] The time vector
    //    isEnd           :  ( Boolean ) Is the end of the Curve.
    //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
    //
    //  Outputs :
    //    u               :  [ N x M ]
    //    ud              :  [ N x M ]
    //    udd             :  [ N x M ]
    //    uddd            :  [ N x M ]
    //
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    udd.set_size(1, y.size(1));
    h_loop_ub = y.size(1);
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        udd[i9] = b_jps * y[i9];
    }
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
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
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, y.size(1));
    m_loop_ub = y.size(1);
    for (int i14{0}; i14 < m_loop_ub; i14++) {
        double b_varargin_1;
        b_varargin_1 = y[i14];
        r[i14] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    n_loop_ub = r.size(1);
    for (int i16{0}; i16 < n_loop_ub; i16++) {
        u[i16] = b_jps * r[i16] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int e_i{0}; e_i < end; e_i++) {
        if (u[e_i] > 1.0) {
            u[e_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int f_i{0}; f_i < b_end; f_i++) {
        if (u[f_i] < 0.0) {
            u[f_i] = 0.0;
        }
    }
    // 'constJerkU:40' if( isEnd )
    *jps = b_jps;
}

} // namespace ocn

//
// File trailer for zeroSpeedCurv.cpp
//
// [EOF]
//
