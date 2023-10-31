
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
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

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
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r19;
    ::coder::array<double, 2U> r21;
    ::coder::array<double, 2U> r24;
    ::coder::array<double, 2U> r27;
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
    double jmax_data[6];
    double vmax_data[6];
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
    int b_scalarLB;
    int b_trueCount;
    int b_vectorUB;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int end;
    int end_tmp;
    int f_loop_ub;
    int g_loop_ub;
    int g_scalarLB;
    int g_vectorUB;
    int h_loop_ub;
    int h_scalarLB;
    int h_vectorUB;
    int iindx;
    int j_loop_ub;
    int k_loop_ub;
    int last;
    int lb_loop_ub;
    int nx;
    int outsize_idx_0;
    int p_loop_ub;
    int partialTrueCount;
    int q_loop_ub;
    int scalarLB;
    int trueCount;
    int vectorUB;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool searchJps;
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
    // 'zeroSpeedCurv:15' uk = 1 - uk ;
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
        double c_jps;
        double e_k;
        double k_max;
        int b_partialTrueCount;
        int bb_loop_ub;
        int c_end;
        int c_partialTrueCount;
        int c_scalarLB;
        int c_vectorUB;
        int d_end;
        int d_partialTrueCount;
        int e_scalarLB;
        int e_vectorUB;
        int eb_loop_ub;
        int f_scalarLB;
        int f_vectorUB;
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
        int i_loop_ub;
        int i_scalarLB;
        int i_vectorUB;
        int j_scalarLB;
        int j_vectorUB;
        int kb_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int nb_loop_ub;
        int o_loop_ub;
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
        i_loop_ub = k_vec.size(1);
        c_scalarLB = (k_vec.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i9{0}; i9 <= c_vectorUB; i9 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&k_vec[i9]);
            _mm_storeu_pd(&y[i9],
                          _mm_sub_pd(_mm_set1_pd(k_max), _mm_mul_pd(r3, _mm_set1_pd(ctx_cfg_dt))));
        }
        for (int i9{c_scalarLB}; i9 < i_loop_ub; i9++) {
            y[i9] = k_max - k_vec[i9] * ctx_cfg_dt;
        }
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
        uv[1] = static_cast<unsigned int>(y.size(1));
        // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
        // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
        r1.set_size(1, y.size(1));
        l_loop_ub = y.size(1);
        for (int i11{0}; i11 < l_loop_ub; i11++) {
            double c_varargin_1;
            c_varargin_1 = y[i11];
            r1[i11] = std::pow(c_varargin_1, 2.0);
        }
        ud.set_size(1, r1.size(1));
        m_loop_ub = r1.size(1);
        e_scalarLB = (r1.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i13{0}; i13 <= e_vectorUB; i13 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r1[i13]);
            _mm_storeu_pd(&ud[i13],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(2.0)));
        }
        for (int i13{e_scalarLB}; i13 < m_loop_ub; i13++) {
            ud[i13] = b_jps * r1[i13] / 2.0;
        }
        // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
        r1.set_size(1, y.size(1));
        n_loop_ub = y.size(1);
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            double d_varargin_1;
            d_varargin_1 = y[i14];
            r1[i14] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r1.size(1));
        o_loop_ub = r1.size(1);
        f_scalarLB = (r1.size(1) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (int i15{0}; i15 <= f_vectorUB; i15 += 2) {
            __m128d r6;
            r6 = _mm_loadu_pd(&r1[i15]);
            _mm_storeu_pd(&u[i15],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r6), _mm_set1_pd(6.0)));
        }
        for (int i15{f_scalarLB}; i15 < o_loop_ub; i15++) {
            u[i15] = b_jps * r1[i15] / 6.0;
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
        i_scalarLB = (u.size(1) / 2) << 1;
        i_vectorUB = i_scalarLB - 2;
        for (int i18{0}; i18 <= i_vectorUB; i18 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&u[i18]);
            _mm_storeu_pd(&u[i18], _mm_sub_pd(_mm_set1_pd(1.0), r9));
        }
        for (int i18{i_scalarLB}; i18 < r_loop_ub; i18++) {
            u[i18] = 1.0 - u[i18];
        }
        // 'constJerkU:39' ud   = ud;
        // 'constJerkU:40' udd  = -udd;
        // 'constJerkU:41' uddd = uddd;
        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        udd_vec.set_size(1, y.size(1));
        s_loop_ub = y.size(1);
        j_scalarLB = (y.size(1) / 2) << 1;
        j_vectorUB = j_scalarLB - 2;
        for (int i19{0}; i19 <= j_vectorUB; i19 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&y[i19]);
            _mm_storeu_pd(&udd_vec[i19],
                          _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r10), _mm_set1_pd(-1.0)));
        }
        for (int i19{j_scalarLB}; i19 < s_loop_ub; i19++) {
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
                int k_scalarLB;
                int k_vectorUB;
                cb_loop_ub = c_r1D.size(0);
                k_scalarLB = (c_r1D.size(0) / 2) << 1;
                k_vectorUB = k_scalarLB - 2;
                for (int i28{0}; i28 <= k_vectorUB; i28 += 2) {
                    __m128d r11;
                    r11 = _mm_loadu_pd(&c_r1D[i28 + c_r1D.size(0) * i26]);
                    _mm_storeu_pd(&V[i28 + V.size(0) * i26], _mm_mul_pd(r11, _mm_set1_pd(ud[i26])));
                }
                for (int i28{k_scalarLB}; i28 < cb_loop_ub; i28++) {
                    V[i28 + V.size(0) * i26] = c_r1D[i28 + c_r1D.size(0) * i26] * ud[i26];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r1.set_size(1, ud.size(1));
        bb_loop_ub = ud.size(1);
        for (int i27{0}; i27 < bb_loop_ub; i27++) {
            double e_varargin_1;
            e_varargin_1 = ud[i27];
            r1[i27] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i29 = r1.size(1);
        } else {
            i29 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i30 = udd_vec.size(1);
        } else {
            i30 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r1.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i29 == i30)) {
            int db_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            db_loop_ub = r2D.size(1);
            for (int i31{0}; i31 < db_loop_ub; i31++) {
                int fb_loop_ub;
                int l_scalarLB;
                int l_vectorUB;
                fb_loop_ub = r2D.size(0);
                l_scalarLB = (r2D.size(0) / 2) << 1;
                l_vectorUB = l_scalarLB - 2;
                for (int i33{0}; i33 <= l_vectorUB; i33 += 2) {
                    __m128d r12;
                    __m128d r13;
                    r12 = _mm_loadu_pd(&r2D[i33 + r2D.size(0) * i31]);
                    r13 = _mm_loadu_pd(&c_r1D[i33 + c_r1D.size(0) * i31]);
                    _mm_storeu_pd(&A[i33 + A.size(0) * i31],
                                  _mm_add_pd(_mm_mul_pd(r12, _mm_set1_pd(r1[i31])),
                                             _mm_mul_pd(r13, _mm_set1_pd(udd_vec[i31]))));
                }
                for (int i33{l_scalarLB}; i33 < fb_loop_ub; i33++) {
                    A[i33 + A.size(0) * i31] = r2D[i33 + r2D.size(0) * i31] * r1[i31] +
                                               c_r1D[i33 + c_r1D.size(0) * i31] * udd_vec[i31];
                }
            }
        } else {
            binary_expand_op(A, r2D, r1, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r1.set_size(1, ud.size(1));
        eb_loop_ub = ud.size(1);
        for (int i32{0}; i32 < eb_loop_ub; i32++) {
            double f_varargin_1;
            f_varargin_1 = ud[i32];
            r1[i32] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i34 = ud.size(1);
        } else {
            i34 = r2D.size(1);
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
            i39 = r1.size(1);
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
            i41 = r1.size(1);
        } else {
            i41 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i42 = y.size(1);
        } else {
            i42 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i34 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i35 == i37) &&
            (c_r1D.size(1) == y.size(1)) && (i38 == c_r1D.size(0)) && (i41 == i42)) {
            int gb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            gb_loop_ub = r3D.size(1);
            for (int i43{0}; i43 < gb_loop_ub; i43++) {
                int hb_loop_ub;
                int m_scalarLB;
                int m_vectorUB;
                hb_loop_ub = r3D.size(0);
                m_scalarLB = (r3D.size(0) / 2) << 1;
                m_vectorUB = m_scalarLB - 2;
                for (int i44{0}; i44 <= m_vectorUB; i44 += 2) {
                    __m128d r14;
                    __m128d r15;
                    __m128d r16;
                    r14 = _mm_loadu_pd(&r3D[i44 + r3D.size(0) * i43]);
                    r15 = _mm_loadu_pd(&r2D[i44 + r2D.size(0) * i43]);
                    r16 = _mm_loadu_pd(&c_r1D[i44 + c_r1D.size(0) * i43]);
                    _mm_storeu_pd(
                        &J[i44 + J.size(0) * i43],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r14, _mm_set1_pd(r1[i43])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r15),
                                                             _mm_set1_pd(ud[i43])),
                                                  _mm_set1_pd(udd_vec[i43]))),
                            _mm_mul_pd(r16, _mm_set1_pd(b_jps))));
                }
                for (int i44{m_scalarLB}; i44 < hb_loop_ub; i44++) {
                    J[i44 + J.size(0) * i43] =
                        (r3D[i44 + r3D.size(0) * i43] * r1[i43] +
                         3.0 * r2D[i44 + r2D.size(0) * i43] * ud[i43] * udd_vec[i43]) +
                        c_r1D[i44 + c_r1D.size(0) * i43] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r1, r2D, ud, udd_vec, c_r1D, b_jps, uv);
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
            int n_scalarLB;
            int n_vectorUB;
            feed.set_size(1, y.size(1));
            mb_loop_ub = y.size(1);
            n_scalarLB = (y.size(1) / 2) << 1;
            n_vectorUB = n_scalarLB - 2;
            for (int i52{0}; i52 <= n_vectorUB; i52 += 2) {
                __m128d r17;
                __m128d r18;
                r17 = _mm_loadu_pd(&y[i52]);
                r18 = _mm_loadu_pd(&ud[i52]);
                _mm_storeu_pd(&feed[i52], _mm_mul_pd(r17, r18));
            }
            for (int i52{n_scalarLB}; i52 < mb_loop_ub; i52++) {
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
            int o_scalarLB;
            int o_vectorUB;
            int ob_loop_ub;
            // 'zeroSpeedCurv:100' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            ob_loop_ub = feed.size(1);
            o_scalarLB = (feed.size(1) / 2) << 1;
            o_vectorUB = o_scalarLB - 2;
            for (int i56{0}; i56 <= o_vectorUB; i56 += 2) {
                __m128d r20;
                r20 = _mm_loadu_pd(&feed[i56]);
                _mm_storeu_pd(&b_feed[i56], _mm_sub_pd(r20, _mm_set1_pd(b_fmax)));
            }
            for (int i56{o_scalarLB}; i56 < ob_loop_ub; i56++) {
                b_feed[i56] = feed[i56] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:101' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r19.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i54;
                i54 = V.size(1);
                for (int i_k{0}; i_k < i54; i_k++) {
                    int i55;
                    i55 = r19.size(0);
                    for (int j_k{0}; j_k < i55; j_k++) {
                        r19[j_k + r19.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r19.size(0) == b_trueCount) {
                int pb_loop_ub;
                b_x.set_size(r19.size(0), r19.size(1));
                pb_loop_ub = r19.size(1);
                for (int i57{0}; i57 < pb_loop_ub; i57++) {
                    int qb_loop_ub;
                    qb_loop_ub = r19.size(0);
                    for (int i58{0}; i58 < qb_loop_ub; i58++) {
                        b_x[i58 + b_x.size(0) * i57] =
                            (r19[i58 + r19.size(0) * i57] > vmax_data[i58]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r19, vmax_data, &b_trueCount);
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
                if (r19.size(0) == b_trueCount) {
                    int rb_loop_ub;
                    int vb_loop_ub;
                    r21.set_size(r19.size(0), r19.size(1));
                    rb_loop_ub = r19.size(1);
                    for (int i61{0}; i61 < rb_loop_ub; i61++) {
                        int p_scalarLB;
                        int p_vectorUB;
                        int tb_loop_ub;
                        tb_loop_ub = r19.size(0);
                        p_scalarLB = (r19.size(0) / 2) << 1;
                        p_vectorUB = p_scalarLB - 2;
                        for (int i65{0}; i65 <= p_vectorUB; i65 += 2) {
                            __m128d r22;
                            __m128d r23;
                            r22 = _mm_loadu_pd(&r19[i65 + r19.size(0) * i61]);
                            r23 = _mm_loadu_pd(&vmax_data[i65]);
                            _mm_storeu_pd(&r21[i65 + r21.size(0) * i61], _mm_sub_pd(r22, r23));
                        }
                        for (int i65{p_scalarLB}; i65 < tb_loop_ub; i65++) {
                            r21[i65 + r21.size(0) * i61] =
                                r19[i65 + r19.size(0) * i61] - vmax_data[i65];
                        }
                    }
                    r19.set_size(r21.size(0), r21.size(1));
                    vb_loop_ub = r21.size(1);
                    for (int i64{0}; i64 < vb_loop_ub; i64++) {
                        int wb_loop_ub;
                        wb_loop_ub = r21.size(0);
                        for (int i66{0}; i66 < wb_loop_ub; i66++) {
                            r19[i66 + r19.size(0) * i64] = r21[i66 + r21.size(0) * i64];
                        }
                    }
                    coder::internal::b_maximum(r19, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r19, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:104' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r19.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i59;
                    i59 = A.size(1);
                    for (int l_k{0}; l_k < i59; l_k++) {
                        int i60;
                        i60 = r19.size(0);
                        for (int m_k{0}; m_k < i60; m_k++) {
                            r19[m_k + r19.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r19.size(0) == c_trueCount) {
                    int sb_loop_ub;
                    b_x.set_size(r19.size(0), r19.size(1));
                    sb_loop_ub = r19.size(1);
                    for (int i62{0}; i62 < sb_loop_ub; i62++) {
                        int ub_loop_ub;
                        ub_loop_ub = r19.size(0);
                        for (int i63{0}; i63 < ub_loop_ub; i63++) {
                            b_x[i63 + b_x.size(0) * i62] =
                                (r19[i63 + r19.size(0) * i62] > amax_data[i63]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r19, amax_data, &c_trueCount);
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
                    if (r19.size(0) == c_trueCount) {
                        int cc_loop_ub;
                        int xb_loop_ub;
                        r24.set_size(r19.size(0), r19.size(1));
                        xb_loop_ub = r19.size(1);
                        for (int i69{0}; i69 < xb_loop_ub; i69++) {
                            int ac_loop_ub;
                            int q_scalarLB;
                            int q_vectorUB;
                            ac_loop_ub = r19.size(0);
                            q_scalarLB = (r19.size(0) / 2) << 1;
                            q_vectorUB = q_scalarLB - 2;
                            for (int i73{0}; i73 <= q_vectorUB; i73 += 2) {
                                __m128d r25;
                                __m128d r26;
                                r25 = _mm_loadu_pd(&r19[i73 + r19.size(0) * i69]);
                                r26 = _mm_loadu_pd(&amax_data[i73]);
                                _mm_storeu_pd(&r24[i73 + r24.size(0) * i69], _mm_sub_pd(r25, r26));
                            }
                            for (int i73{q_scalarLB}; i73 < ac_loop_ub; i73++) {
                                r24[i73 + r24.size(0) * i69] =
                                    r19[i73 + r19.size(0) * i69] - amax_data[i73];
                            }
                        }
                        r19.set_size(r24.size(0), r24.size(1));
                        cc_loop_ub = r24.size(1);
                        for (int i72{0}; i72 < cc_loop_ub; i72++) {
                            int dc_loop_ub;
                            dc_loop_ub = r24.size(0);
                            for (int i74{0}; i74 < dc_loop_ub; i74++) {
                                r19[i74 + r19.size(0) * i72] = r24[i74 + r24.size(0) * i72];
                            }
                        }
                        coder::internal::b_maximum(r19, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r19, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:107' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r19.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i67;
                        i67 = J.size(1);
                        for (int o_k{0}; o_k < i67; o_k++) {
                            int i68;
                            i68 = r19.size(0);
                            for (int p_k{0}; p_k < i68; p_k++) {
                                r19[p_k + r19.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r19.size(0) == d_trueCount) {
                        int yb_loop_ub;
                        b_x.set_size(r19.size(0), r19.size(1));
                        yb_loop_ub = r19.size(1);
                        for (int i70{0}; i70 < yb_loop_ub; i70++) {
                            int bc_loop_ub;
                            bc_loop_ub = r19.size(0);
                            for (int i71{0}; i71 < bc_loop_ub; i71++) {
                                b_x[i71 + b_x.size(0) * i70] =
                                    (r19[i71 + r19.size(0) * i70] > jmax_data[i71]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r19, jmax_data, &d_trueCount);
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
                        if (r19.size(0) == d_trueCount) {
                            int ec_loop_ub;
                            int gc_loop_ub;
                            r27.set_size(r19.size(0), r19.size(1));
                            ec_loop_ub = r19.size(1);
                            for (int i75{0}; i75 < ec_loop_ub; i75++) {
                                int fc_loop_ub;
                                int r_scalarLB;
                                int r_vectorUB;
                                fc_loop_ub = r19.size(0);
                                r_scalarLB = (r19.size(0) / 2) << 1;
                                r_vectorUB = r_scalarLB - 2;
                                for (int i77{0}; i77 <= r_vectorUB; i77 += 2) {
                                    __m128d r28;
                                    __m128d r29;
                                    r28 = _mm_loadu_pd(&r19[i77 + r19.size(0) * i75]);
                                    r29 = _mm_loadu_pd(&jmax_data[i77]);
                                    _mm_storeu_pd(&r27[i77 + r27.size(0) * i75],
                                                  _mm_sub_pd(r28, r29));
                                }
                                for (int i77{r_scalarLB}; i77 < fc_loop_ub; i77++) {
                                    r27[i77 + r27.size(0) * i75] =
                                        r19[i77 + r19.size(0) * i75] - jmax_data[i77];
                                }
                            }
                            r19.set_size(r27.size(0), r27.size(1));
                            gc_loop_ub = r27.size(1);
                            for (int i76{0}; i76 < gc_loop_ub; i76++) {
                                int hc_loop_ub;
                                hc_loop_ub = r27.size(0);
                                for (int i78{0}; i78 < hc_loop_ub; i78++) {
                                    r19[i78 + r19.size(0) * i76] = r27[i78 + r27.size(0) * i76];
                                }
                            }
                            coder::internal::b_maximum(r19, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r19, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i6{0}; i6 <= vectorUB; i6 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i6]);
        _mm_storeu_pd(&y[i6],
                      _mm_sub_pd(_mm_set1_pd(k_tmp), _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt))));
    }
    for (int i6{scalarLB}; i6 < f_loop_ub; i6++) {
        y[i6] = k_tmp - k_vec[i6] * ctx_cfg_dt;
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:27' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:28' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    r1.set_size(1, y.size(1));
    g_loop_ub = y.size(1);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        double varargin_1;
        varargin_1 = y[i7];
        r1[i7] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r1.size(1));
    h_loop_ub = r1.size(1);
    b_scalarLB = (r1.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i8{0}; i8 <= b_vectorUB; i8 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1[i8]);
        _mm_storeu_pd(&ud[i8], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r2), _mm_set1_pd(2.0)));
    }
    for (int i8{b_scalarLB}; i8 < h_loop_ub; i8++) {
        ud[i8] = b_jps * r1[i8] / 2.0;
    }
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    r1.set_size(1, y.size(1));
    j_loop_ub = y.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        double b_varargin_1;
        b_varargin_1 = y[i10];
        r1[i10] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r1.size(1));
    k_loop_ub = r1.size(1);
    d_scalarLB = (r1.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i12{0}; i12 <= d_vectorUB; i12 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r1[i12]);
        _mm_storeu_pd(&u[i12], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(6.0)));
    }
    for (int i12{d_scalarLB}; i12 < k_loop_ub; i12++) {
        u[i12] = b_jps * r1[i12] / 6.0;
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
    p_loop_ub = u.size(1);
    g_scalarLB = (u.size(1) / 2) << 1;
    g_vectorUB = g_scalarLB - 2;
    for (int i16{0}; i16 <= g_vectorUB; i16 += 2) {
        __m128d r7;
        r7 = _mm_loadu_pd(&u[i16]);
        _mm_storeu_pd(&u[i16], _mm_sub_pd(_mm_set1_pd(1.0), r7));
    }
    for (int i16{g_scalarLB}; i16 < p_loop_ub; i16++) {
        u[i16] = 1.0 - u[i16];
    }
    // 'constJerkU:39' ud   = ud;
    // 'constJerkU:40' udd  = -udd;
    udd.set_size(1, y.size(1));
    q_loop_ub = y.size(1);
    h_scalarLB = (y.size(1) / 2) << 1;
    h_vectorUB = h_scalarLB - 2;
    for (int i17{0}; i17 <= h_vectorUB; i17 += 2) {
        __m128d r8;
        r8 = _mm_loadu_pd(&y[i17]);
        _mm_storeu_pd(&udd[i17], _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r8), _mm_set1_pd(-1.0)));
    }
    for (int i17{h_scalarLB}; i17 < q_loop_ub; i17++) {
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
    ::coder::array<double, 2U> r17;
    ::coder::array<double, 2U> r19;
    ::coder::array<double, 2U> r22;
    ::coder::array<double, 2U> r25;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
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
    double jmax_data[6];
    double vmax_data[6];
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
    int c_scalarLB;
    int c_trueCount;
    int c_vectorUB;
    int d_iindx;
    int d_loop_ub;
    int d_scalarLB;
    int d_trueCount;
    int d_vectorUB;
    int end;
    int end_tmp;
    int f_scalarLB;
    int f_vectorUB;
    int h_loop_ub;
    int i_loop_ub;
    int iindx;
    int j_loop_ub;
    int jb_loop_ub;
    int l_loop_ub;
    int last;
    int n_loop_ub;
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
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' if( isEnd )
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
        double c_jps;
        double e_k;
        int b_partialTrueCount;
        int b_scalarLB;
        int b_vectorUB;
        int c_end;
        int c_partialTrueCount;
        int cb_loop_ub;
        int d_end;
        int d_partialTrueCount;
        int e_scalarLB;
        int e_vectorUB;
        int g_loop_ub;
        int g_scalarLB;
        int g_vectorUB;
        int h_k;
        int h_scalarLB;
        int h_vectorUB;
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
        int k_loop_ub;
        int lb_loop_ub;
        int m_loop_ub;
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
        b_scalarLB = (k_vec.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i7{0}; i7 <= b_vectorUB; i7 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&k_vec[i7]);
            _mm_storeu_pd(&y[i7], _mm_mul_pd(r1, _mm_set1_pd(ctx_cfg_dt)));
        }
        for (int i7{b_scalarLB}; i7 < g_loop_ub; i7++) {
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
        r3.set_size(1, y.size(1));
        k_loop_ub = y.size(1);
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            double b_varargin_1;
            b_varargin_1 = y[i11];
            r3[i11] = std::pow(b_varargin_1, 2.0);
        }
        ud.set_size(1, r3.size(1));
        m_loop_ub = r3.size(1);
        e_scalarLB = (r3.size(1) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i13{0}; i13 <= e_vectorUB; i13 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r3[i13]);
            _mm_storeu_pd(&ud[i13],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r5), _mm_set1_pd(2.0)));
        }
        for (int i13{e_scalarLB}; i13 < m_loop_ub; i13++) {
            ud[i13] = b_jps * r3[i13] / 2.0;
        }
        // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
        r3.set_size(1, y.size(1));
        o_loop_ub = y.size(1);
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            double d_varargin_1;
            d_varargin_1 = y[i15];
            r3[i15] = std::pow(d_varargin_1, 3.0);
        }
        u.set_size(1, r3.size(1));
        p_loop_ub = r3.size(1);
        g_scalarLB = (r3.size(1) / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (int i16{0}; i16 <= g_vectorUB; i16 += 2) {
            __m128d r7;
            r7 = _mm_loadu_pd(&r3[i16]);
            _mm_storeu_pd(&u[i16],
                          _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r7), _mm_set1_pd(6.0)));
        }
        for (int i16{g_scalarLB}; i16 < p_loop_ub; i16++) {
            u[i16] = b_jps * r3[i16] / 6.0;
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
        h_scalarLB = (y.size(1) / 2) << 1;
        h_vectorUB = h_scalarLB - 2;
        for (int i17{0}; i17 <= h_vectorUB; i17 += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&y[i17]);
            _mm_storeu_pd(&udd_vec[i17], _mm_mul_pd(_mm_set1_pd(b_jps), r8));
        }
        for (int i17{h_scalarLB}; i17 < q_loop_ub; i17++) {
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
                int i_scalarLB;
                int i_vectorUB;
                ab_loop_ub = c_r1D.size(0);
                i_scalarLB = (c_r1D.size(0) / 2) << 1;
                i_vectorUB = i_scalarLB - 2;
                for (int i26{0}; i26 <= i_vectorUB; i26 += 2) {
                    __m128d r9;
                    r9 = _mm_loadu_pd(&c_r1D[i26 + c_r1D.size(0) * i24]);
                    _mm_storeu_pd(&V[i26 + V.size(0) * i24], _mm_mul_pd(r9, _mm_set1_pd(ud[i24])));
                }
                for (int i26{i_scalarLB}; i26 < ab_loop_ub; i26++) {
                    V[i26 + V.size(0) * i24] = c_r1D[i26 + c_r1D.size(0) * i24] * ud[i24];
                }
            }
        } else {
            b_times(V, c_r1D, ud);
        }
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        r3.set_size(1, ud.size(1));
        y_loop_ub = ud.size(1);
        for (int i25{0}; i25 < y_loop_ub; i25++) {
            double e_varargin_1;
            e_varargin_1 = ud[i25];
            r3[i25] = std::pow(e_varargin_1, 2.0);
        }
        if (r2D.size(1) == 1) {
            i27 = r3.size(1);
        } else {
            i27 = r2D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i28 = udd_vec.size(1);
        } else {
            i28 = c_r1D.size(1);
        }
        if ((r2D.size(1) == r3.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
            (r2D.size(0) == c_r1D.size(0)) && (i27 == i28)) {
            int bb_loop_ub;
            A.set_size(r2D.size(0), r2D.size(1));
            bb_loop_ub = r2D.size(1);
            for (int i29{0}; i29 < bb_loop_ub; i29++) {
                int db_loop_ub;
                int j_scalarLB;
                int j_vectorUB;
                db_loop_ub = r2D.size(0);
                j_scalarLB = (r2D.size(0) / 2) << 1;
                j_vectorUB = j_scalarLB - 2;
                for (int i31{0}; i31 <= j_vectorUB; i31 += 2) {
                    __m128d r10;
                    __m128d r11;
                    r10 = _mm_loadu_pd(&r2D[i31 + r2D.size(0) * i29]);
                    r11 = _mm_loadu_pd(&c_r1D[i31 + c_r1D.size(0) * i29]);
                    _mm_storeu_pd(&A[i31 + A.size(0) * i29],
                                  _mm_add_pd(_mm_mul_pd(r10, _mm_set1_pd(r3[i29])),
                                             _mm_mul_pd(r11, _mm_set1_pd(udd_vec[i29]))));
                }
                for (int i31{j_scalarLB}; i31 < db_loop_ub; i31++) {
                    A[i31 + A.size(0) * i29] = r2D[i31 + r2D.size(0) * i29] * r3[i29] +
                                               c_r1D[i31 + c_r1D.size(0) * i29] * udd_vec[i29];
                }
            }
        } else {
            binary_expand_op(A, r2D, r3, c_r1D, udd_vec);
        }
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec;
        r3.set_size(1, ud.size(1));
        cb_loop_ub = ud.size(1);
        for (int i30{0}; i30 < cb_loop_ub; i30++) {
            double f_varargin_1;
            f_varargin_1 = ud[i30];
            r3[i30] = std::pow(f_varargin_1, 3.0);
        }
        if (r2D.size(1) == 1) {
            i32 = ud.size(1);
        } else {
            i32 = r2D.size(1);
        }
        if (r3D.size(1) == 1) {
            i33 = r3.size(1);
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
            i37 = r3.size(1);
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
            i39 = r3.size(1);
        } else {
            i39 = r3D.size(1);
        }
        if (c_r1D.size(1) == 1) {
            i40 = y.size(1);
        } else {
            i40 = c_r1D.size(1);
        }
        if ((r3D.size(1) == r3.size(1)) && (r2D.size(1) == ud.size(1)) &&
            (i32 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i33 == i35) &&
            (c_r1D.size(1) == y.size(1)) && (i36 == c_r1D.size(0)) && (i39 == i40)) {
            int eb_loop_ub;
            J.set_size(r3D.size(0), r3D.size(1));
            eb_loop_ub = r3D.size(1);
            for (int i41{0}; i41 < eb_loop_ub; i41++) {
                int fb_loop_ub;
                int k_scalarLB;
                int k_vectorUB;
                fb_loop_ub = r3D.size(0);
                k_scalarLB = (r3D.size(0) / 2) << 1;
                k_vectorUB = k_scalarLB - 2;
                for (int i42{0}; i42 <= k_vectorUB; i42 += 2) {
                    __m128d r12;
                    __m128d r13;
                    __m128d r14;
                    r12 = _mm_loadu_pd(&r3D[i42 + r3D.size(0) * i41]);
                    r13 = _mm_loadu_pd(&r2D[i42 + r2D.size(0) * i41]);
                    r14 = _mm_loadu_pd(&c_r1D[i42 + c_r1D.size(0) * i41]);
                    _mm_storeu_pd(
                        &J[i42 + J.size(0) * i41],
                        _mm_add_pd(
                            _mm_add_pd(_mm_mul_pd(r12, _mm_set1_pd(r3[i41])),
                                       _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r13),
                                                             _mm_set1_pd(ud[i41])),
                                                  _mm_set1_pd(udd_vec[i41]))),
                            _mm_mul_pd(r14, _mm_set1_pd(b_jps))));
                }
                for (int i42{k_scalarLB}; i42 < fb_loop_ub; i42++) {
                    J[i42 + J.size(0) * i41] =
                        (r3D[i42 + r3D.size(0) * i41] * r3[i41] +
                         3.0 * r2D[i42 + r2D.size(0) * i41] * ud[i41] * udd_vec[i41]) +
                        c_r1D[i42 + c_r1D.size(0) * i41] * b_jps;
                }
            }
        } else {
            binary_expand_op(J, r3D, r3, r2D, ud, udd_vec, c_r1D, b_jps, uv);
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
            int l_scalarLB;
            int l_vectorUB;
            feed.set_size(1, y.size(1));
            kb_loop_ub = y.size(1);
            l_scalarLB = (y.size(1) / 2) << 1;
            l_vectorUB = l_scalarLB - 2;
            for (int i50{0}; i50 <= l_vectorUB; i50 += 2) {
                __m128d r15;
                __m128d r16;
                r15 = _mm_loadu_pd(&y[i50]);
                r16 = _mm_loadu_pd(&ud[i50]);
                _mm_storeu_pd(&feed[i50], _mm_mul_pd(r15, r16));
            }
            for (int i50{l_scalarLB}; i50 < kb_loop_ub; i50++) {
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
            int m_scalarLB;
            int m_vectorUB;
            int mb_loop_ub;
            // 'zeroSpeedCurv:100' [ f_delta, ind ] = max( feed - fmax );
            b_feed.set_size(1, feed.size(1));
            mb_loop_ub = feed.size(1);
            m_scalarLB = (feed.size(1) / 2) << 1;
            m_vectorUB = m_scalarLB - 2;
            for (int i54{0}; i54 <= m_vectorUB; i54 += 2) {
                __m128d r18;
                r18 = _mm_loadu_pd(&feed[i54]);
                _mm_storeu_pd(&b_feed[i54], _mm_sub_pd(r18, _mm_set1_pd(b_fmax)));
            }
            for (int i54{m_scalarLB}; i54 < mb_loop_ub; i54++) {
                b_feed[i54] = feed[i54] - b_fmax;
            }
            coder::internal::maximum(b_feed, &f_delta, &iindx);
            // 'zeroSpeedCurv:101' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
            c_jps = b_jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
        } else {
            int k_k;
            bool varargout_1;
            r17.set_size(V.size(0), V.size(1));
            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                int i52;
                i52 = V.size(1);
                for (int i_k{0}; i_k < i52; i_k++) {
                    int i53;
                    i53 = r17.size(0);
                    for (int j_k{0}; j_k < i53; j_k++) {
                        r17[j_k + r17.size(0) * i_k] = std::abs(V[j_k + V.size(0) * i_k]);
                    }
                }
            }
            if (r17.size(0) == b_trueCount) {
                int nb_loop_ub;
                b_x.set_size(r17.size(0), r17.size(1));
                nb_loop_ub = r17.size(1);
                for (int i55{0}; i55 < nb_loop_ub; i55++) {
                    int ob_loop_ub;
                    ob_loop_ub = r17.size(0);
                    for (int i56{0}; i56 < ob_loop_ub; i56++) {
                        b_x[i56 + b_x.size(0) * i55] =
                            (r17[i56 + r17.size(0) * i55] > vmax_data[i56]);
                    }
                }
            } else {
                f_binary_expand_op(b_x, r17, vmax_data, &b_trueCount);
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
                if (r17.size(0) == b_trueCount) {
                    int pb_loop_ub;
                    int tb_loop_ub;
                    r19.set_size(r17.size(0), r17.size(1));
                    pb_loop_ub = r17.size(1);
                    for (int i59{0}; i59 < pb_loop_ub; i59++) {
                        int n_scalarLB;
                        int n_vectorUB;
                        int rb_loop_ub;
                        rb_loop_ub = r17.size(0);
                        n_scalarLB = (r17.size(0) / 2) << 1;
                        n_vectorUB = n_scalarLB - 2;
                        for (int i63{0}; i63 <= n_vectorUB; i63 += 2) {
                            __m128d r20;
                            __m128d r21;
                            r20 = _mm_loadu_pd(&r17[i63 + r17.size(0) * i59]);
                            r21 = _mm_loadu_pd(&vmax_data[i63]);
                            _mm_storeu_pd(&r19[i63 + r19.size(0) * i59], _mm_sub_pd(r20, r21));
                        }
                        for (int i63{n_scalarLB}; i63 < rb_loop_ub; i63++) {
                            r19[i63 + r19.size(0) * i59] =
                                r17[i63 + r17.size(0) * i59] - vmax_data[i63];
                        }
                    }
                    r17.set_size(r19.size(0), r19.size(1));
                    tb_loop_ub = r19.size(1);
                    for (int i62{0}; i62 < tb_loop_ub; i62++) {
                        int ub_loop_ub;
                        ub_loop_ub = r19.size(0);
                        for (int i64{0}; i64 < ub_loop_ub; i64++) {
                            r17[i64 + r17.size(0) * i62] = r19[i64 + r19.size(0) * i62];
                        }
                    }
                    coder::internal::b_maximum(r17, &v_delta, &b_iindx);
                } else {
                    binary_expand_op(r17, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                }
                // 'zeroSpeedCurv:104' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind ) ) )
                // );
                c_jps = b_jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
            } else {
                int n_k;
                bool b_varargout_1;
                r17.set_size(A.size(0), A.size(1));
                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                    int i57;
                    i57 = A.size(1);
                    for (int l_k{0}; l_k < i57; l_k++) {
                        int i58;
                        i58 = r17.size(0);
                        for (int m_k{0}; m_k < i58; m_k++) {
                            r17[m_k + r17.size(0) * l_k] = std::abs(A[m_k + A.size(0) * l_k]);
                        }
                    }
                }
                if (r17.size(0) == c_trueCount) {
                    int qb_loop_ub;
                    b_x.set_size(r17.size(0), r17.size(1));
                    qb_loop_ub = r17.size(1);
                    for (int i60{0}; i60 < qb_loop_ub; i60++) {
                        int sb_loop_ub;
                        sb_loop_ub = r17.size(0);
                        for (int i61{0}; i61 < sb_loop_ub; i61++) {
                            b_x[i61 + b_x.size(0) * i60] =
                                (r17[i61 + r17.size(0) * i60] > amax_data[i61]);
                        }
                    }
                } else {
                    f_binary_expand_op(b_x, r17, amax_data, &c_trueCount);
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
                    if (r17.size(0) == c_trueCount) {
                        int ac_loop_ub;
                        int vb_loop_ub;
                        r22.set_size(r17.size(0), r17.size(1));
                        vb_loop_ub = r17.size(1);
                        for (int i67{0}; i67 < vb_loop_ub; i67++) {
                            int o_scalarLB;
                            int o_vectorUB;
                            int xb_loop_ub;
                            xb_loop_ub = r17.size(0);
                            o_scalarLB = (r17.size(0) / 2) << 1;
                            o_vectorUB = o_scalarLB - 2;
                            for (int i71{0}; i71 <= o_vectorUB; i71 += 2) {
                                __m128d r23;
                                __m128d r24;
                                r23 = _mm_loadu_pd(&r17[i71 + r17.size(0) * i67]);
                                r24 = _mm_loadu_pd(&amax_data[i71]);
                                _mm_storeu_pd(&r22[i71 + r22.size(0) * i67], _mm_sub_pd(r23, r24));
                            }
                            for (int i71{o_scalarLB}; i71 < xb_loop_ub; i71++) {
                                r22[i71 + r22.size(0) * i67] =
                                    r17[i71 + r17.size(0) * i67] - amax_data[i71];
                            }
                        }
                        r17.set_size(r22.size(0), r22.size(1));
                        ac_loop_ub = r22.size(1);
                        for (int i70{0}; i70 < ac_loop_ub; i70++) {
                            int bc_loop_ub;
                            bc_loop_ub = r22.size(0);
                            for (int i72{0}; i72 < bc_loop_ub; i72++) {
                                r17[i72 + r17.size(0) * i70] = r22[i72 + r22.size(0) * i70];
                            }
                        }
                        coder::internal::b_maximum(r17, &a_delta, &c_iindx);
                    } else {
                        binary_expand_op(r17, amax_data, &c_trueCount, &a_delta, &c_iindx);
                    }
                    // 'zeroSpeedCurv:107' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A( ind ) )
                    // ) );
                    c_jps = b_jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                } else {
                    int q_k;
                    bool c_varargout_1;
                    r17.set_size(J.size(0), J.size(1));
                    if ((J.size(0) != 0) && (J.size(1) != 0)) {
                        int i65;
                        i65 = J.size(1);
                        for (int o_k{0}; o_k < i65; o_k++) {
                            int i66;
                            i66 = r17.size(0);
                            for (int p_k{0}; p_k < i66; p_k++) {
                                r17[p_k + r17.size(0) * o_k] = std::abs(J[p_k + J.size(0) * o_k]);
                            }
                        }
                    }
                    if (r17.size(0) == d_trueCount) {
                        int wb_loop_ub;
                        b_x.set_size(r17.size(0), r17.size(1));
                        wb_loop_ub = r17.size(1);
                        for (int i68{0}; i68 < wb_loop_ub; i68++) {
                            int yb_loop_ub;
                            yb_loop_ub = r17.size(0);
                            for (int i69{0}; i69 < yb_loop_ub; i69++) {
                                b_x[i69 + b_x.size(0) * i68] =
                                    (r17[i69 + r17.size(0) * i68] > jmax_data[i69]);
                            }
                        }
                    } else {
                        f_binary_expand_op(b_x, r17, jmax_data, &d_trueCount);
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
                        if (r17.size(0) == d_trueCount) {
                            int cc_loop_ub;
                            int ec_loop_ub;
                            r25.set_size(r17.size(0), r17.size(1));
                            cc_loop_ub = r17.size(1);
                            for (int i73{0}; i73 < cc_loop_ub; i73++) {
                                int dc_loop_ub;
                                int p_scalarLB;
                                int p_vectorUB;
                                dc_loop_ub = r17.size(0);
                                p_scalarLB = (r17.size(0) / 2) << 1;
                                p_vectorUB = p_scalarLB - 2;
                                for (int i75{0}; i75 <= p_vectorUB; i75 += 2) {
                                    __m128d r26;
                                    __m128d r27;
                                    r26 = _mm_loadu_pd(&r17[i75 + r17.size(0) * i73]);
                                    r27 = _mm_loadu_pd(&jmax_data[i75]);
                                    _mm_storeu_pd(&r25[i75 + r25.size(0) * i73],
                                                  _mm_sub_pd(r26, r27));
                                }
                                for (int i75{p_scalarLB}; i75 < dc_loop_ub; i75++) {
                                    r25[i75 + r25.size(0) * i73] =
                                        r17[i75 + r17.size(0) * i73] - jmax_data[i75];
                                }
                            }
                            r17.set_size(r25.size(0), r25.size(1));
                            ec_loop_ub = r25.size(1);
                            for (int i74{0}; i74 < ec_loop_ub; i74++) {
                                int fc_loop_ub;
                                fc_loop_ub = r25.size(0);
                                for (int i76{0}; i76 < fc_loop_ub; i76++) {
                                    r17[i76 + r17.size(0) * i74] = r25[i76 + r25.size(0) * i74];
                                }
                            }
                            coder::internal::b_maximum(r17, &j_delta, &d_iindx);
                        } else {
                            binary_expand_op(r17, jmax_data, &d_trueCount, &j_delta, &d_iindx);
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
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i4{0}; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i4]);
        _mm_storeu_pd(&y[i4], _mm_mul_pd(r, _mm_set1_pd(ctx_cfg_dt)));
    }
    for (int i4{scalarLB}; i4 < d_loop_ub; i4++) {
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
    c_scalarLB = (y.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i8{0}; i8 <= c_vectorUB; i8 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&y[i8]);
        _mm_storeu_pd(&udd[i8], _mm_mul_pd(_mm_set1_pd(b_jps), r2));
    }
    for (int i8{c_scalarLB}; i8 < h_loop_ub; i8++) {
        udd[i8] = b_jps * y[i8];
    }
    // 'constJerkU:29' ud      = pseudoJerk .* k_vec .^2 / 2;
    r3.set_size(1, y.size(1));
    i_loop_ub = y.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        double varargin_1;
        varargin_1 = y[i9];
        r3[i9] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r3.size(1));
    j_loop_ub = r3.size(1);
    d_scalarLB = (r3.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i10{0}; i10 <= d_vectorUB; i10 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3[i10]);
        _mm_storeu_pd(&ud[i10], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r4), _mm_set1_pd(2.0)));
    }
    for (int i10{d_scalarLB}; i10 < j_loop_ub; i10++) {
        ud[i10] = b_jps * r3[i10] / 2.0;
    }
    // 'constJerkU:30' u       = pseudoJerk .* k_vec .^3 / 6;
    r3.set_size(1, y.size(1));
    l_loop_ub = y.size(1);
    for (int i12{0}; i12 < l_loop_ub; i12++) {
        double c_varargin_1;
        c_varargin_1 = y[i12];
        r3[i12] = std::pow(c_varargin_1, 3.0);
    }
    u.set_size(1, r3.size(1));
    n_loop_ub = r3.size(1);
    f_scalarLB = (r3.size(1) / 2) << 1;
    f_vectorUB = f_scalarLB - 2;
    for (int i14{0}; i14 <= f_vectorUB; i14 += 2) {
        __m128d r6;
        r6 = _mm_loadu_pd(&r3[i14]);
        _mm_storeu_pd(&u[i14], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(b_jps), r6), _mm_set1_pd(6.0)));
    }
    for (int i14{f_scalarLB}; i14 < n_loop_ub; i14++) {
        u[i14] = b_jps * r3[i14] / 6.0;
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
