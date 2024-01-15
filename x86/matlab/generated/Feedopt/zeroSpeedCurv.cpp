
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
#include <emmintrin.h>

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
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r9;
    ::coder::array<double, 2U> uddd;
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
    int scalarLB;
    int trueCount;
    int vectorUB;
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
        double b_fmax;
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
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
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i7{0}; i7 <= b_vectorUB; i7 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i7]);
            _mm_storeu_pd(&k_vec[i7], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i7{b_scalarLB}; i7 < g_loop_ub; i7++) {
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
            int c_scalarLB;
            int c_vectorUB;
            int l_loop_ub;
            feed.set_size(1, y.size(1));
            l_loop_ub = y.size(1);
            c_scalarLB = (y.size(1) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (int i15{0}; i15 <= c_vectorUB; i15 += 2) {
                __m128d r2;
                __m128d r3;
                r2 = _mm_loadu_pd(&y[i15]);
                r3 = _mm_loadu_pd(&ud[i15]);
                _mm_storeu_pd(&feed[i15], _mm_mul_pd(r2, r3));
            }
            for (int i15{c_scalarLB}; i15 < l_loop_ub; i15++) {
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
            int d_scalarLB;
            int d_vectorUB;
            int n_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            n_loop_ub = feed.size(1);
            d_scalarLB = (feed.size(1) / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (int i19{0}; i19 <= d_vectorUB; i19 += 2) {
                __m128d r5;
                r5 = _mm_loadu_pd(&feed[i19]);
                _mm_storeu_pd(&b_feed[i19], _mm_sub_pd(r5, _mm_set1_pd(b_fmax)));
            }
            for (int i19{d_scalarLB}; i19 < n_loop_ub; i19++) {
                b_feed[i19] = feed[i19] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r4.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i17;
                i17 = V.size(1);
                for (int i_k{0}; i_k < i17; i_k++) {
                    int i18;
                    i18 = r4.size(0);
                    for (int j_k{0}; j_k < i18; j_k++) {
                        r4[j_k + r4.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r4.size(0) == b_trueCount) {
                int o_loop_ub;
                b_x.set_size(r4.size(0), r4.size(1));
                o_loop_ub = r4.size(1);
                for (int i20{0}; i20 < o_loop_ub; i20++) {
                    int p_loop_ub;
                    p_loop_ub = r4.size(0);
                    for (int i21{0}; i21 < p_loop_ub; i21++) {
                        b_x[i21 + b_x.size(0) * i20] =
                            (r4[i21 + r4.size(0) * i20] > vmax_data[i21]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r4, vmax_data, &b_trueCount);
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
                if (r4.size(0) == b_trueCount) {
                    int q_loop_ub;
                    int u_loop_ub;
                    r6.set_size(r4.size(0), r4.size(1));
                    q_loop_ub = r4.size(1);
                    for (int i24{0}; i24 < q_loop_ub; i24++) {
                        int e_scalarLB;
                        int e_vectorUB;
                        int s_loop_ub;
                        s_loop_ub = r4.size(0);
                        e_scalarLB = (r4.size(0) / 2) << 1;
                        e_vectorUB = e_scalarLB - 2;
                        for (int i28{0}; i28 <= e_vectorUB; i28 += 2) {
                            __m128d r7;
                            __m128d r8;
                            r7 = _mm_loadu_pd(&r4[i28 + r4.size(0) * i24]);
                            r8 = _mm_loadu_pd(&vmax_data[i28]);
                            _mm_storeu_pd(&r6[i28 + r6.size(0) * i24], _mm_sub_pd(r7, r8));
                        }
                        for (int i28{e_scalarLB}; i28 < s_loop_ub; i28++) {
                            r6[i28 + r6.size(0) * i24] =
                                r4[i28 + r4.size(0) * i24] - vmax_data[i28];
                        }
                    }
                    r4.set_size(r6.size(0), r6.size(1));
                    u_loop_ub = r6.size(1);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        int v_loop_ub;
                        v_loop_ub = r6.size(0);
                        for (int i29{0}; i29 < v_loop_ub; i29++) {
                            r4[i29 + r4.size(0) * i27] = r6[i29 + r6.size(0) * i27];
                        }
                    }
                    coder::internal::b_maximum(r4, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r4, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r4.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i22;
                    i22 = A.size(1);
                    for (int l_k{0}; l_k < i22; l_k++) {
                        int i23;
                        i23 = r4.size(0);
                        for (int m_k{0}; m_k < i23; m_k++) {
                            r4[m_k + r4.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r4.size(0) == c_trueCount) {
                    int r_loop_ub;
                    b_x.set_size(r4.size(0), r4.size(1));
                    r_loop_ub = r4.size(1);
                    for (int i25{0}; i25 < r_loop_ub; i25++) {
                        int t_loop_ub;
                        t_loop_ub = r4.size(0);
                        for (int i26{0}; i26 < t_loop_ub; i26++) {
                            b_x[i26 + b_x.size(0) * i25] =
                                (r4[i26 + r4.size(0) * i25] > amax_data[i26]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r4, amax_data, &c_trueCount);
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
                    if (r4.size(0) == c_trueCount) {
                        int bb_loop_ub;
                        int w_loop_ub;
                        r9.set_size(r4.size(0), r4.size(1));
                        w_loop_ub = r4.size(1);
                        for (int i32{0}; i32 < w_loop_ub; i32++) {
                            int f_scalarLB;
                            int f_vectorUB;
                            int y_loop_ub;
                            y_loop_ub = r4.size(0);
                            f_scalarLB = (r4.size(0) / 2) << 1;
                            f_vectorUB = f_scalarLB - 2;
                            for (int i36{0}; i36 <= f_vectorUB; i36 += 2) {
                                __m128d r10;
                                __m128d r11;
                                r10 = _mm_loadu_pd(&r4[i36 + r4.size(0) * i32]);
                                r11 = _mm_loadu_pd(&amax_data[i36]);
                                _mm_storeu_pd(&r9[i36 + r9.size(0) * i32], _mm_sub_pd(r10, r11));
                            }
                            for (int i36{f_scalarLB}; i36 < y_loop_ub; i36++) {
                                r9[i36 + r9.size(0) * i32] =
                                    r4[i36 + r4.size(0) * i32] - amax_data[i36];
                            }
                        }
                        r4.set_size(r9.size(0), r9.size(1));
                        bb_loop_ub = r9.size(1);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            int cb_loop_ub;
                            cb_loop_ub = r9.size(0);
                            for (int i37{0}; i37 < cb_loop_ub; i37++) {
                                r4[i37 + r4.size(0) * i35] = r9[i37 + r9.size(0) * i35];
                            }
                        }
                        coder::internal::b_maximum(r4, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r4, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r4.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i30;
                        i30 = J.size(1);
                        for (int o_k{0}; o_k < i30; o_k++) {
                            int i31;
                            i31 = r4.size(0);
                            for (int p_k{0}; p_k < i31; p_k++) {
                                r4[p_k + r4.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r4.size(0) == d_trueCount) {
                        int x_loop_ub;
                        b_x.set_size(r4.size(0), r4.size(1));
                        x_loop_ub = r4.size(1);
                        for (int i33{0}; i33 < x_loop_ub; i33++) {
                            int ab_loop_ub;
                            ab_loop_ub = r4.size(0);
                            for (int i34{0}; i34 < ab_loop_ub; i34++) {
                                b_x[i34 + b_x.size(0) * i33] =
                                    (r4[i34 + r4.size(0) * i33] > jmax_data[i34]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r4, jmax_data, &d_trueCount);
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
                        if (r4.size(0) == d_trueCount) {
                            int db_loop_ub;
                            int fb_loop_ub;
                            r12.set_size(r4.size(0), r4.size(1));
                            db_loop_ub = r4.size(1);
                            for (int i38{0}; i38 < db_loop_ub; i38++) {
                                int eb_loop_ub;
                                int g_scalarLB;
                                int g_vectorUB;
                                eb_loop_ub = r4.size(0);
                                g_scalarLB = (r4.size(0) / 2) << 1;
                                g_vectorUB = g_scalarLB - 2;
                                for (int i40{0}; i40 <= g_vectorUB; i40 += 2) {
                                    __m128d r13;
                                    __m128d r14;
                                    r13 = _mm_loadu_pd(&r4[i40 + r4.size(0) * i38]);
                                    r14 = _mm_loadu_pd(&jmax_data[i40]);
                                    _mm_storeu_pd(&r12[i40 + r12.size(0) * i38],
                                                  _mm_sub_pd(r13, r14));
                                }
                                for (int i40{g_scalarLB}; i40 < eb_loop_ub; i40++) {
                                    r12[i40 + r12.size(0) * i38] =
                                        r4[i40 + r4.size(0) * i38] - jmax_data[i40];
                                }
                            }
                            r4.set_size(r12.size(0), r12.size(1));
                            fb_loop_ub = r12.size(1);
                            for (int i39{0}; i39 < fb_loop_ub; i39++) {
                                int gb_loop_ub;
                                gb_loop_ub = r12.size(0);
                                for (int i41{0}; i41 < gb_loop_ub; i41++) {
                                    r4[i41 + r4.size(0) * i39] = r12[i41 + r12.size(0) * i39];
                                }
                            }
                            coder::internal::b_maximum(r4, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r4, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i4{0}; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i4]);
        _mm_storeu_pd(&k_vec[i4], _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt)));
    }
    for (int i4{scalarLB}; i4 < d_loop_ub; i4++) {
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
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r9;
    ::coder::array<double, 2U> uddd;
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
    int scalarLB;
    int trueCount;
    int vectorUB;
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
        double b_fmax;
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
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
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i7{0}; i7 <= b_vectorUB; i7 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i7]);
            _mm_storeu_pd(&k_vec[i7], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i7{b_scalarLB}; i7 < g_loop_ub; i7++) {
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
            int c_scalarLB;
            int c_vectorUB;
            int l_loop_ub;
            feed.set_size(1, y.size(1));
            l_loop_ub = y.size(1);
            c_scalarLB = (y.size(1) / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (int i15{0}; i15 <= c_vectorUB; i15 += 2) {
                __m128d r2;
                __m128d r3;
                r2 = _mm_loadu_pd(&y[i15]);
                r3 = _mm_loadu_pd(&ud[i15]);
                _mm_storeu_pd(&feed[i15], _mm_mul_pd(r2, r3));
            }
            for (int i15{c_scalarLB}; i15 < l_loop_ub; i15++) {
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
            int d_scalarLB;
            int d_vectorUB;
            int n_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            n_loop_ub = feed.size(1);
            d_scalarLB = (feed.size(1) / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (int i19{0}; i19 <= d_vectorUB; i19 += 2) {
                __m128d r5;
                r5 = _mm_loadu_pd(&feed[i19]);
                _mm_storeu_pd(&b_feed[i19], _mm_sub_pd(r5, _mm_set1_pd(b_fmax)));
            }
            for (int i19{d_scalarLB}; i19 < n_loop_ub; i19++) {
                b_feed[i19] = feed[i19] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r4.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i17;
                i17 = V.size(1);
                for (int i_k{0}; i_k < i17; i_k++) {
                    int i18;
                    i18 = r4.size(0);
                    for (int j_k{0}; j_k < i18; j_k++) {
                        r4[j_k + r4.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r4.size(0) == b_trueCount) {
                int o_loop_ub;
                b_x.set_size(r4.size(0), r4.size(1));
                o_loop_ub = r4.size(1);
                for (int i20{0}; i20 < o_loop_ub; i20++) {
                    int p_loop_ub;
                    p_loop_ub = r4.size(0);
                    for (int i21{0}; i21 < p_loop_ub; i21++) {
                        b_x[i21 + b_x.size(0) * i20] =
                            (r4[i21 + r4.size(0) * i20] > vmax_data[i21]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r4, vmax_data, &b_trueCount);
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
                if (r4.size(0) == b_trueCount) {
                    int q_loop_ub;
                    int u_loop_ub;
                    r6.set_size(r4.size(0), r4.size(1));
                    q_loop_ub = r4.size(1);
                    for (int i24{0}; i24 < q_loop_ub; i24++) {
                        int e_scalarLB;
                        int e_vectorUB;
                        int s_loop_ub;
                        s_loop_ub = r4.size(0);
                        e_scalarLB = (r4.size(0) / 2) << 1;
                        e_vectorUB = e_scalarLB - 2;
                        for (int i28{0}; i28 <= e_vectorUB; i28 += 2) {
                            __m128d r7;
                            __m128d r8;
                            r7 = _mm_loadu_pd(&r4[i28 + r4.size(0) * i24]);
                            r8 = _mm_loadu_pd(&vmax_data[i28]);
                            _mm_storeu_pd(&r6[i28 + r6.size(0) * i24], _mm_sub_pd(r7, r8));
                        }
                        for (int i28{e_scalarLB}; i28 < s_loop_ub; i28++) {
                            r6[i28 + r6.size(0) * i24] =
                                r4[i28 + r4.size(0) * i24] - vmax_data[i28];
                        }
                    }
                    r4.set_size(r6.size(0), r6.size(1));
                    u_loop_ub = r6.size(1);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        int v_loop_ub;
                        v_loop_ub = r6.size(0);
                        for (int i29{0}; i29 < v_loop_ub; i29++) {
                            r4[i29 + r4.size(0) * i27] = r6[i29 + r6.size(0) * i27];
                        }
                    }
                    coder::internal::b_maximum(r4, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r4, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r4.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i22;
                    i22 = A.size(1);
                    for (int l_k{0}; l_k < i22; l_k++) {
                        int i23;
                        i23 = r4.size(0);
                        for (int m_k{0}; m_k < i23; m_k++) {
                            r4[m_k + r4.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r4.size(0) == c_trueCount) {
                    int r_loop_ub;
                    b_x.set_size(r4.size(0), r4.size(1));
                    r_loop_ub = r4.size(1);
                    for (int i25{0}; i25 < r_loop_ub; i25++) {
                        int t_loop_ub;
                        t_loop_ub = r4.size(0);
                        for (int i26{0}; i26 < t_loop_ub; i26++) {
                            b_x[i26 + b_x.size(0) * i25] =
                                (r4[i26 + r4.size(0) * i25] > amax_data[i26]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r4, amax_data, &c_trueCount);
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
                    if (r4.size(0) == c_trueCount) {
                        int bb_loop_ub;
                        int w_loop_ub;
                        r9.set_size(r4.size(0), r4.size(1));
                        w_loop_ub = r4.size(1);
                        for (int i32{0}; i32 < w_loop_ub; i32++) {
                            int f_scalarLB;
                            int f_vectorUB;
                            int y_loop_ub;
                            y_loop_ub = r4.size(0);
                            f_scalarLB = (r4.size(0) / 2) << 1;
                            f_vectorUB = f_scalarLB - 2;
                            for (int i36{0}; i36 <= f_vectorUB; i36 += 2) {
                                __m128d r10;
                                __m128d r11;
                                r10 = _mm_loadu_pd(&r4[i36 + r4.size(0) * i32]);
                                r11 = _mm_loadu_pd(&amax_data[i36]);
                                _mm_storeu_pd(&r9[i36 + r9.size(0) * i32], _mm_sub_pd(r10, r11));
                            }
                            for (int i36{f_scalarLB}; i36 < y_loop_ub; i36++) {
                                r9[i36 + r9.size(0) * i32] =
                                    r4[i36 + r4.size(0) * i32] - amax_data[i36];
                            }
                        }
                        r4.set_size(r9.size(0), r9.size(1));
                        bb_loop_ub = r9.size(1);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            int cb_loop_ub;
                            cb_loop_ub = r9.size(0);
                            for (int i37{0}; i37 < cb_loop_ub; i37++) {
                                r4[i37 + r4.size(0) * i35] = r9[i37 + r9.size(0) * i35];
                            }
                        }
                        coder::internal::b_maximum(r4, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r4, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r4.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i30;
                        i30 = J.size(1);
                        for (int o_k{0}; o_k < i30; o_k++) {
                            int i31;
                            i31 = r4.size(0);
                            for (int p_k{0}; p_k < i31; p_k++) {
                                r4[p_k + r4.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r4.size(0) == d_trueCount) {
                        int x_loop_ub;
                        b_x.set_size(r4.size(0), r4.size(1));
                        x_loop_ub = r4.size(1);
                        for (int i33{0}; i33 < x_loop_ub; i33++) {
                            int ab_loop_ub;
                            ab_loop_ub = r4.size(0);
                            for (int i34{0}; i34 < ab_loop_ub; i34++) {
                                b_x[i34 + b_x.size(0) * i33] =
                                    (r4[i34 + r4.size(0) * i33] > jmax_data[i34]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r4, jmax_data, &d_trueCount);
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
                        if (r4.size(0) == d_trueCount) {
                            int db_loop_ub;
                            int fb_loop_ub;
                            r12.set_size(r4.size(0), r4.size(1));
                            db_loop_ub = r4.size(1);
                            for (int i38{0}; i38 < db_loop_ub; i38++) {
                                int eb_loop_ub;
                                int g_scalarLB;
                                int g_vectorUB;
                                eb_loop_ub = r4.size(0);
                                g_scalarLB = (r4.size(0) / 2) << 1;
                                g_vectorUB = g_scalarLB - 2;
                                for (int i40{0}; i40 <= g_vectorUB; i40 += 2) {
                                    __m128d r13;
                                    __m128d r14;
                                    r13 = _mm_loadu_pd(&r4[i40 + r4.size(0) * i38]);
                                    r14 = _mm_loadu_pd(&jmax_data[i40]);
                                    _mm_storeu_pd(&r12[i40 + r12.size(0) * i38],
                                                  _mm_sub_pd(r13, r14));
                                }
                                for (int i40{g_scalarLB}; i40 < eb_loop_ub; i40++) {
                                    r12[i40 + r12.size(0) * i38] =
                                        r4[i40 + r4.size(0) * i38] - jmax_data[i40];
                                }
                            }
                            r4.set_size(r12.size(0), r12.size(1));
                            fb_loop_ub = r12.size(1);
                            for (int i39{0}; i39 < fb_loop_ub; i39++) {
                                int gb_loop_ub;
                                gb_loop_ub = r12.size(0);
                                for (int i41{0}; i41 < gb_loop_ub; i41++) {
                                    r4[i41 + r4.size(0) * i39] = r12[i41 + r12.size(0) * i39];
                                }
                            }
                            coder::internal::b_maximum(r4, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r4, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i4{0}; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i4]);
        _mm_storeu_pd(&k_vec[i4], _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt)));
    }
    for (int i4{scalarLB}; i4 < d_loop_ub; i4++) {
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
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r16;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> uddd;
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
    int c_scalarLB;
    int c_trueCount;
    int c_vectorUB;
    int d_iindx;
    int d_loop_ub;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int e_scalarLB;
    int e_vectorUB;
    int end;
    int end_tmp;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int k_loop_ub;
    int last;
    int m_loop_ub;
    int n_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int scalarLB;
    int trueCount;
    int vectorUB;
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
        double b_fmax;
        double c_jps;
        double d_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
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
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i8{0}; i8 <= b_vectorUB; i8 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i8]);
            _mm_storeu_pd(&k_vec[i8], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i8{b_scalarLB}; i8 < g_loop_ub; i8++) {
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
            int j_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            j_loop_ub = c_r1D.size(1) - 1;
            for (int i11{0}; i11 <= j_loop_ub; i11++) {
                int l_loop_ub;
                l_loop_ub = c_r1D.size(0) - 1;
                for (int i13{0}; i13 <= l_loop_ub; i13++) {
                    d_r1D[i13 + d_r1D.size(0) * i11] = c_r1D[i13 + c_r1D.size(0) * i11];
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
        for (int i14{0}; i14 < b_trueCount; i14++) {
            vmax_data[i14] = ctx_cfg_vmax[b_tmp_data[i14] - 1] * 0.5;
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
        for (int i16{0}; i16 < c_trueCount; i16++) {
            amax_data[i16] = ctx_cfg_amax[c_tmp_data[i16] - 1] * 0.5;
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
            int f_scalarLB;
            int f_vectorUB;
            int q_loop_ub;
            feed.set_size(1, y.size(1));
            q_loop_ub = y.size(1);
            f_scalarLB = (y.size(1) / 2) << 1;
            f_vectorUB = f_scalarLB - 2;
            for (int i21{0}; i21 <= f_vectorUB; i21 += 2) {
                __m128d r6;
                __m128d r7;
                r6 = _mm_loadu_pd(&y[i21]);
                r7 = _mm_loadu_pd(&ud[i21]);
                _mm_storeu_pd(&feed[i21], _mm_mul_pd(r6, r7));
            }
            for (int i21{f_scalarLB}; i21 < q_loop_ub; i21++) {
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
            int g_scalarLB;
            int g_vectorUB;
            int s_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            s_loop_ub = feed.size(1);
            g_scalarLB = (feed.size(1) / 2) << 1;
            g_vectorUB = g_scalarLB - 2;
            for (int i25{0}; i25 <= g_vectorUB; i25 += 2) {
                __m128d r9;
                r9 = _mm_loadu_pd(&feed[i25]);
                _mm_storeu_pd(&b_feed[i25], _mm_sub_pd(r9, _mm_set1_pd(b_fmax)));
            }
            for (int i25{g_scalarLB}; i25 < s_loop_ub; i25++) {
                b_feed[i25] = feed[i25] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool varargout_1;
            r8.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i23;
                i23 = V.size(1);
                for (int h_k{0}; h_k < i23; h_k++) {
                    int i24;
                    i24 = r8.size(0);
                    for (int i_k{0}; i_k < i24; i_k++) {
                        r8[i_k + r8.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (r8.size(0) == b_trueCount) {
                int t_loop_ub;
                b_x.set_size(r8.size(0), r8.size(1));
                t_loop_ub = r8.size(1);
                for (int i26{0}; i26 < t_loop_ub; i26++) {
                    int u_loop_ub;
                    u_loop_ub = r8.size(0);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        b_x[i27 + b_x.size(0) * i26] =
                            (r8[i27 + r8.size(0) * i26] > vmax_data[i27]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r8, vmax_data, &b_trueCount);
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
                if (r8.size(0) == b_trueCount) {
                    int ab_loop_ub;
                    int v_loop_ub;
                    r10.set_size(r8.size(0), r8.size(1));
                    v_loop_ub = r8.size(1);
                    for (int i30{0}; i30 < v_loop_ub; i30++) {
                        int h_scalarLB;
                        int h_vectorUB;
                        int x_loop_ub;
                        x_loop_ub = r8.size(0);
                        h_scalarLB = (r8.size(0) / 2) << 1;
                        h_vectorUB = h_scalarLB - 2;
                        for (int i34{0}; i34 <= h_vectorUB; i34 += 2) {
                            __m128d r11;
                            __m128d r12;
                            r11 = _mm_loadu_pd(&r8[i34 + r8.size(0) * i30]);
                            r12 = _mm_loadu_pd(&vmax_data[i34]);
                            _mm_storeu_pd(&r10[i34 + r10.size(0) * i30], _mm_sub_pd(r11, r12));
                        }
                        for (int i34{h_scalarLB}; i34 < x_loop_ub; i34++) {
                            r10[i34 + r10.size(0) * i30] =
                                r8[i34 + r8.size(0) * i30] - vmax_data[i34];
                        }
                    }
                    r8.set_size(r10.size(0), r10.size(1));
                    ab_loop_ub = r10.size(1);
                    for (int i33{0}; i33 < ab_loop_ub; i33++) {
                        int bb_loop_ub;
                        bb_loop_ub = r10.size(0);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            r8[i35 + r8.size(0) * i33] = r10[i35 + r10.size(0) * i33];
                        }
                    }
                    coder::internal::b_maximum(r8, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r8, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool b_varargout_1;
                r8.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i28;
                    i28 = A.size(1);
                    for (int k_k{0}; k_k < i28; k_k++) {
                        int i29;
                        i29 = r8.size(0);
                        for (int l_k{0}; l_k < i29; l_k++) {
                            r8[l_k + r8.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (r8.size(0) == c_trueCount) {
                    int w_loop_ub;
                    b_x.set_size(r8.size(0), r8.size(1));
                    w_loop_ub = r8.size(1);
                    for (int i31{0}; i31 < w_loop_ub; i31++) {
                        int y_loop_ub;
                        y_loop_ub = r8.size(0);
                        for (int i32{0}; i32 < y_loop_ub; i32++) {
                            b_x[i32 + b_x.size(0) * i31] =
                                (r8[i32 + r8.size(0) * i31] > amax_data[i32]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r8, amax_data, &c_trueCount);
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
                    if (r8.size(0) == c_trueCount) {
                        int cb_loop_ub;
                        int gb_loop_ub;
                        r13.set_size(r8.size(0), r8.size(1));
                        cb_loop_ub = r8.size(1);
                        for (int i38{0}; i38 < cb_loop_ub; i38++) {
                            int eb_loop_ub;
                            int i_scalarLB;
                            int i_vectorUB;
                            eb_loop_ub = r8.size(0);
                            i_scalarLB = (r8.size(0) / 2) << 1;
                            i_vectorUB = i_scalarLB - 2;
                            for (int i42{0}; i42 <= i_vectorUB; i42 += 2) {
                                __m128d r14;
                                __m128d r15;
                                r14 = _mm_loadu_pd(&r8[i42 + r8.size(0) * i38]);
                                r15 = _mm_loadu_pd(&amax_data[i42]);
                                _mm_storeu_pd(&r13[i42 + r13.size(0) * i38], _mm_sub_pd(r14, r15));
                            }
                            for (int i42{i_scalarLB}; i42 < eb_loop_ub; i42++) {
                                r13[i42 + r13.size(0) * i38] =
                                    r8[i42 + r8.size(0) * i38] - amax_data[i42];
                            }
                        }
                        r8.set_size(r13.size(0), r13.size(1));
                        gb_loop_ub = r13.size(1);
                        for (int i41{0}; i41 < gb_loop_ub; i41++) {
                            int hb_loop_ub;
                            hb_loop_ub = r13.size(0);
                            for (int i43{0}; i43 < hb_loop_ub; i43++) {
                                r8[i43 + r8.size(0) * i41] = r13[i43 + r13.size(0) * i41];
                            }
                        }
                        coder::internal::b_maximum(r8, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r8, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool c_varargout_1;
                    r8.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i36;
                        i36 = J.size(1);
                        for (int n_k{0}; n_k < i36; n_k++) {
                            int i37;
                            i37 = r8.size(0);
                            for (int o_k{0}; o_k < i37; o_k++) {
                                r8[o_k + r8.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (r8.size(0) == d_trueCount) {
                        int db_loop_ub;
                        b_x.set_size(r8.size(0), r8.size(1));
                        db_loop_ub = r8.size(1);
                        for (int i39{0}; i39 < db_loop_ub; i39++) {
                            int fb_loop_ub;
                            fb_loop_ub = r8.size(0);
                            for (int i40{0}; i40 < fb_loop_ub; i40++) {
                                b_x[i40 + b_x.size(0) * i39] =
                                    (r8[i40 + r8.size(0) * i39] > jmax_data[i40]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r8, jmax_data, &d_trueCount);
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
                        if (r8.size(0) == d_trueCount) {
                            int ib_loop_ub;
                            int kb_loop_ub;
                            r16.set_size(r8.size(0), r8.size(1));
                            ib_loop_ub = r8.size(1);
                            for (int i44{0}; i44 < ib_loop_ub; i44++) {
                                int j_scalarLB;
                                int j_vectorUB;
                                int jb_loop_ub;
                                jb_loop_ub = r8.size(0);
                                j_scalarLB = (r8.size(0) / 2) << 1;
                                j_vectorUB = j_scalarLB - 2;
                                for (int i46{0}; i46 <= j_vectorUB; i46 += 2) {
                                    __m128d r17;
                                    __m128d r18;
                                    r17 = _mm_loadu_pd(&r8[i46 + r8.size(0) * i44]);
                                    r18 = _mm_loadu_pd(&jmax_data[i46]);
                                    _mm_storeu_pd(&r16[i46 + r16.size(0) * i44],
                                                  _mm_sub_pd(r17, r18));
                                }
                                for (int i46{j_scalarLB}; i46 < jb_loop_ub; i46++) {
                                    r16[i46 + r16.size(0) * i44] =
                                        r8[i46 + r8.size(0) * i44] - jmax_data[i46];
                                }
                            }
                            r8.set_size(r16.size(0), r16.size(1));
                            kb_loop_ub = r16.size(1);
                            for (int i45{0}; i45 < kb_loop_ub; i45++) {
                                int lb_loop_ub;
                                lb_loop_ub = r16.size(0);
                                for (int i47{0}; i47 < lb_loop_ub; i47++) {
                                    r8[i47 + r8.size(0) * i45] = r16[i47 + r16.size(0) * i45];
                                }
                            }
                            coder::internal::b_maximum(r8, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r8, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    r3.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        double varargin_1;
        varargin_1 = y[i10];
        r3[i10] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r3.size(1));
    k_loop_ub = r3.size(1);
    d_scalarLB = (r3.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i12{0}; i12 <= d_vectorUB; i12 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3[i12]);
        _mm_storeu_pd(&ud[i12], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(2.0)));
    }
    for (int i12{d_scalarLB}; i12 < k_loop_ub; i12++) {
        ud[i12] = b_jps * r3[i12] / 2.0;
    }
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r3.set_size(1, y.size(1));
    m_loop_ub = y.size(1);
    for (int i15{0}; i15 < m_loop_ub; i15++) {
        double b_varargin_1;
        b_varargin_1 = y[i15];
        r3[i15] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r3.size(1));
    n_loop_ub = r3.size(1);
    e_scalarLB = (r3.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (int i17{0}; i17 <= e_vectorUB; i17 += 2) {
        __m128d r5;
        r5 = _mm_loadu_pd(&r3[i17]);
        _mm_storeu_pd(&u[i17], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(6.0)));
    }
    for (int i17{e_scalarLB}; i17 < n_loop_ub; i17++) {
        u[i17] = b_jps * r3[i17] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int f_i{0}; f_i < end; f_i++) {
        if (u[f_i] > 1.0) {
            u[f_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int g_i{0}; g_i < b_end; g_i++) {
        if (u[g_i] < 0.0) {
            u[g_i] = 0.0;
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
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r16;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> uddd;
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
    int c_scalarLB;
    int c_trueCount;
    int c_vectorUB;
    int d_iindx;
    int d_loop_ub;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int e_scalarLB;
    int e_vectorUB;
    int end;
    int end_tmp;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int k_loop_ub;
    int last;
    int m_loop_ub;
    int n_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int scalarLB;
    int trueCount;
    int vectorUB;
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
        double b_fmax;
        double c_jps;
        double d_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
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
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i8{0}; i8 <= b_vectorUB; i8 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i8]);
            _mm_storeu_pd(&k_vec[i8], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i8{b_scalarLB}; i8 < g_loop_ub; i8++) {
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
            int j_loop_ub;
            // 'zeroSpeedCurv:91' else
            // 'zeroSpeedCurv:92' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
            j_loop_ub = c_r1D.size(1) - 1;
            for (int i11{0}; i11 <= j_loop_ub; i11++) {
                int l_loop_ub;
                l_loop_ub = c_r1D.size(0) - 1;
                for (int i12{0}; i12 <= l_loop_ub; i12++) {
                    d_r1D[i12 + d_r1D.size(0) * i11] = c_r1D[i12 + c_r1D.size(0) * i11];
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
        for (int i14{0}; i14 < b_trueCount; i14++) {
            vmax_data[i14] = ctx_cfg_vmax[b_tmp_data[i14] - 1] * 0.5;
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
        for (int i16{0}; i16 < c_trueCount; i16++) {
            amax_data[i16] = ctx_cfg_amax[c_tmp_data[i16] - 1] * 0.5;
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
            int f_scalarLB;
            int f_vectorUB;
            int q_loop_ub;
            feed.set_size(1, y.size(1));
            q_loop_ub = y.size(1);
            f_scalarLB = (y.size(1) / 2) << 1;
            f_vectorUB = f_scalarLB - 2;
            for (int i21{0}; i21 <= f_vectorUB; i21 += 2) {
                __m128d r6;
                __m128d r7;
                r6 = _mm_loadu_pd(&y[i21]);
                r7 = _mm_loadu_pd(&ud[i21]);
                _mm_storeu_pd(&feed[i21], _mm_mul_pd(r6, r7));
            }
            for (int i21{f_scalarLB}; i21 < q_loop_ub; i21++) {
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
            int g_scalarLB;
            int g_vectorUB;
            int s_loop_ub;
            // 'zeroSpeedCurv:104' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            s_loop_ub = feed.size(1);
            g_scalarLB = (feed.size(1) / 2) << 1;
            g_vectorUB = g_scalarLB - 2;
            for (int i25{0}; i25 <= g_vectorUB; i25 += 2) {
                __m128d r9;
                r9 = _mm_loadu_pd(&feed[i25]);
                _mm_storeu_pd(&b_feed[i25], _mm_sub_pd(r9, _mm_set1_pd(b_fmax)));
            }
            for (int i25{g_scalarLB}; i25 < s_loop_ub; i25++) {
                b_feed[i25] = feed[i25] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int j_k;
            bool varargout_1;
            r8.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i23;
                i23 = V.size(1);
                for (int h_k{0}; h_k < i23; h_k++) {
                    int i24;
                    i24 = r8.size(0);
                    for (int i_k{0}; i_k < i24; i_k++) {
                        r8[i_k + r8.size(0) * h_k] = std::abs(V[i_k + V.size(0) * h_k]);
                    }
                }
            }
            if (r8.size(0) == b_trueCount) {
                int t_loop_ub;
                b_x.set_size(r8.size(0), r8.size(1));
                t_loop_ub = r8.size(1);
                for (int i26{0}; i26 < t_loop_ub; i26++) {
                    int u_loop_ub;
                    u_loop_ub = r8.size(0);
                    for (int i27{0}; i27 < u_loop_ub; i27++) {
                        b_x[i27 + b_x.size(0) * i26] =
                            (r8[i27 + r8.size(0) * i26] > vmax_data[i27]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r8, vmax_data, &b_trueCount);
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
                if (r8.size(0) == b_trueCount) {
                    int ab_loop_ub;
                    int v_loop_ub;
                    r10.set_size(r8.size(0), r8.size(1));
                    v_loop_ub = r8.size(1);
                    for (int i30{0}; i30 < v_loop_ub; i30++) {
                        int h_scalarLB;
                        int h_vectorUB;
                        int x_loop_ub;
                        x_loop_ub = r8.size(0);
                        h_scalarLB = (r8.size(0) / 2) << 1;
                        h_vectorUB = h_scalarLB - 2;
                        for (int i34{0}; i34 <= h_vectorUB; i34 += 2) {
                            __m128d r11;
                            __m128d r12;
                            r11 = _mm_loadu_pd(&r8[i34 + r8.size(0) * i30]);
                            r12 = _mm_loadu_pd(&vmax_data[i34]);
                            _mm_storeu_pd(&r10[i34 + r10.size(0) * i30], _mm_sub_pd(r11, r12));
                        }
                        for (int i34{h_scalarLB}; i34 < x_loop_ub; i34++) {
                            r10[i34 + r10.size(0) * i30] =
                                r8[i34 + r8.size(0) * i30] - vmax_data[i34];
                        }
                    }
                    r8.set_size(r10.size(0), r10.size(1));
                    ab_loop_ub = r10.size(1);
                    for (int i33{0}; i33 < ab_loop_ub; i33++) {
                        int bb_loop_ub;
                        bb_loop_ub = r10.size(0);
                        for (int i35{0}; i35 < bb_loop_ub; i35++) {
                            r8[i35 + r8.size(0) * i33] = r10[i35 + r10.size(0) * i33];
                        }
                    }
                    coder::internal::b_maximum(r8, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r8, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int m_k;
                bool b_varargout_1;
                r8.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i28;
                    i28 = A.size(1);
                    for (int k_k{0}; k_k < i28; k_k++) {
                        int i29;
                        i29 = r8.size(0);
                        for (int l_k{0}; l_k < i29; l_k++) {
                            r8[l_k + r8.size(0) * k_k] = std::abs(A[l_k + A.size(0) * k_k]);
                        }
                    }
                }
                if (r8.size(0) == c_trueCount) {
                    int w_loop_ub;
                    b_x.set_size(r8.size(0), r8.size(1));
                    w_loop_ub = r8.size(1);
                    for (int i31{0}; i31 < w_loop_ub; i31++) {
                        int y_loop_ub;
                        y_loop_ub = r8.size(0);
                        for (int i32{0}; i32 < y_loop_ub; i32++) {
                            b_x[i32 + b_x.size(0) * i31] =
                                (r8[i32 + r8.size(0) * i31] > amax_data[i32]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r8, amax_data, &c_trueCount);
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
                    if (r8.size(0) == c_trueCount) {
                        int cb_loop_ub;
                        int gb_loop_ub;
                        r13.set_size(r8.size(0), r8.size(1));
                        cb_loop_ub = r8.size(1);
                        for (int i38{0}; i38 < cb_loop_ub; i38++) {
                            int eb_loop_ub;
                            int i_scalarLB;
                            int i_vectorUB;
                            eb_loop_ub = r8.size(0);
                            i_scalarLB = (r8.size(0) / 2) << 1;
                            i_vectorUB = i_scalarLB - 2;
                            for (int i42{0}; i42 <= i_vectorUB; i42 += 2) {
                                __m128d r14;
                                __m128d r15;
                                r14 = _mm_loadu_pd(&r8[i42 + r8.size(0) * i38]);
                                r15 = _mm_loadu_pd(&amax_data[i42]);
                                _mm_storeu_pd(&r13[i42 + r13.size(0) * i38], _mm_sub_pd(r14, r15));
                            }
                            for (int i42{i_scalarLB}; i42 < eb_loop_ub; i42++) {
                                r13[i42 + r13.size(0) * i38] =
                                    r8[i42 + r8.size(0) * i38] - amax_data[i42];
                            }
                        }
                        r8.set_size(r13.size(0), r13.size(1));
                        gb_loop_ub = r13.size(1);
                        for (int i41{0}; i41 < gb_loop_ub; i41++) {
                            int hb_loop_ub;
                            hb_loop_ub = r13.size(0);
                            for (int i43{0}; i43 < hb_loop_ub; i43++) {
                                r8[i43 + r8.size(0) * i41] = r13[i43 + r13.size(0) * i41];
                            }
                        }
                        coder::internal::b_maximum(r8, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r8, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:111' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int p_k;
                    bool c_varargout_1;
                    r8.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i36;
                        i36 = J.size(1);
                        for (int n_k{0}; n_k < i36; n_k++) {
                            int i37;
                            i37 = r8.size(0);
                            for (int o_k{0}; o_k < i37; o_k++) {
                                r8[o_k + r8.size(0) * n_k] = std::abs(J[o_k + J.size(0) * n_k]);
                            }
                        }
                    }
                    if (r8.size(0) == d_trueCount) {
                        int db_loop_ub;
                        b_x.set_size(r8.size(0), r8.size(1));
                        db_loop_ub = r8.size(1);
                        for (int i39{0}; i39 < db_loop_ub; i39++) {
                            int fb_loop_ub;
                            fb_loop_ub = r8.size(0);
                            for (int i40{0}; i40 < fb_loop_ub; i40++) {
                                b_x[i40 + b_x.size(0) * i39] =
                                    (r8[i40 + r8.size(0) * i39] > jmax_data[i40]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r8, jmax_data, &d_trueCount);
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
                        if (r8.size(0) == d_trueCount) {
                            int ib_loop_ub;
                            int kb_loop_ub;
                            r16.set_size(r8.size(0), r8.size(1));
                            ib_loop_ub = r8.size(1);
                            for (int i44{0}; i44 < ib_loop_ub; i44++) {
                                int j_scalarLB;
                                int j_vectorUB;
                                int jb_loop_ub;
                                jb_loop_ub = r8.size(0);
                                j_scalarLB = (r8.size(0) / 2) << 1;
                                j_vectorUB = j_scalarLB - 2;
                                for (int i46{0}; i46 <= j_vectorUB; i46 += 2) {
                                    __m128d r17;
                                    __m128d r18;
                                    r17 = _mm_loadu_pd(&r8[i46 + r8.size(0) * i44]);
                                    r18 = _mm_loadu_pd(&jmax_data[i46]);
                                    _mm_storeu_pd(&r16[i46 + r16.size(0) * i44],
                                                  _mm_sub_pd(r17, r18));
                                }
                                for (int i46{j_scalarLB}; i46 < jb_loop_ub; i46++) {
                                    r16[i46 + r16.size(0) * i44] =
                                        r8[i46 + r8.size(0) * i44] - jmax_data[i46];
                                }
                            }
                            r8.set_size(r16.size(0), r16.size(1));
                            kb_loop_ub = r16.size(1);
                            for (int i45{0}; i45 < kb_loop_ub; i45++) {
                                int lb_loop_ub;
                                lb_loop_ub = r16.size(0);
                                for (int i47{0}; i47 < lb_loop_ub; i47++) {
                                    r8[i47 + r8.size(0) * i45] = r16[i47 + r16.size(0) * i45];
                                }
                            }
                            coder::internal::b_maximum(r8, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r8, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    r3.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        double varargin_1;
        varargin_1 = y[i10];
        r3[i10] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r3.size(1));
    k_loop_ub = r3.size(1);
    d_scalarLB = (r3.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i13{0}; i13 <= d_vectorUB; i13 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3[i13]);
        _mm_storeu_pd(&ud[i13], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(2.0)));
    }
    for (int i13{d_scalarLB}; i13 < k_loop_ub; i13++) {
        ud[i13] = b_jps * r3[i13] / 2.0;
    }
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r3.set_size(1, y.size(1));
    m_loop_ub = y.size(1);
    for (int i15{0}; i15 < m_loop_ub; i15++) {
        double b_varargin_1;
        b_varargin_1 = y[i15];
        r3[i15] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r3.size(1));
    n_loop_ub = r3.size(1);
    e_scalarLB = (r3.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (int i17{0}; i17 <= e_vectorUB; i17 += 2) {
        __m128d r5;
        r5 = _mm_loadu_pd(&r3[i17]);
        _mm_storeu_pd(&u[i17], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(6.0)));
    }
    for (int i17{e_scalarLB}; i17 < n_loop_ub; i17++) {
        u[i17] = b_jps * r3[i17] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int f_i{0}; f_i < end; f_i++) {
        if (u[f_i] > 1.0) {
            u[f_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int g_i{0}; g_i < b_end; g_i++) {
        if (u[g_i] < 0.0) {
            u[g_i] = 0.0;
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
