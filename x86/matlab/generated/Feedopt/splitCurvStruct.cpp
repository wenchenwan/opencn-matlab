//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

// Include Files
#include "splitCurvStruct.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStructU.h"
#include "cutZeroEnd.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ ctx ] = splitCurvStruct( ctx, curv )
//
// SplitCurvStruct : Split the curv structs with a zero speed.
//  Inputs  :
//  ctx   : The context
//  curv  : The curv struct
//  Output  :
//  ctx   : The modified context
//
// Arguments    : const b_FeedoptContext *ctx
//                CurvStruct *curv
// Return Type  : void
//
namespace ocn {
void splitCurvStruct(const b_FeedoptContext *ctx, CurvStruct *curv)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_feed;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r13;
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
    ::coder::array<bool, 2U> r14;
    ::coder::array<bool, 2U> x;
    CurvStruct b_curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    double amax_data[6];
    double ctx_data[6];
    double jmax_data[6];
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double vmax_data[6];
    double params_Cprim[3];
    double params_evec[3];
    double a_delta;
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double f_delta;
    double j_delta;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_spline_Ltot;
    double v_delta;
    unsigned long params_spline_Bl_handle;
    int ctx_size[2];
    unsigned int uv[2];
    int ab_loop_ub;
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_trueCount;
    int iindx;
    int nx;
    int outsize_idx_0;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'splitCurvStruct:10' if( ~coder.target( 'MATLAB' ) )
    // 'splitCurvStruct:10' curvE = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
        &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
        &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
        &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
        &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
        &params_spline_Bl_handle, &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
        &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim, &expl_temp,
        params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode, params_gcodeInfoStruct_TRAFO,
        params_gcodeInfoStruct_HSC, params_gcodeInfoStruct_FeedRate,
        params_gcodeInfoStruct_SpindleSpeed, params_gcodeInfoStruct_gcode_source_line,
        params_gcodeInfoStruct_G91, params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
        params_spline_Bl_breakpoints, params_spline_Bl_handle, params_spline_Bl_order,
        params_spline_coeff, params_spline_knots, params_spline_Ltot, params_spline_Lk, params_R0,
        params_R1, params_Cprim, params_evec, params_CoeffP5, &curvE);
    // 'splitCurvStruct:12' if ( curv.Info.Type == CurveType.TransP5 )
    if (curv->Info.Type == CurveType_TransP5) {
        // 'splitCurvStruct:13' ctx.q_split.push( curv );
        ctx->q_split.push(curv);
    } else {
        double L;
        double L_split;
        double N;
        int k;
        bool exitg1;
        bool hasEndSpeed;
        // 'splitCurvStruct:16' if( isAZeroStart( curv ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            CurvStruct c_curv;
            double b_fmax;
            double d;
            double jps;
            double u;
            int end_tmp;
            int partialTrueCount;
            int trueCount;
            bool searchJps;
            // 'isAZeroStart:6' zeroFlag = true;
            //  cut zero Start
            // 'splitCurvStruct:18' [ curvS, curv ] = cutZeroStart( ctx, curv );
            //  cutZeroStart : Cut the start of the given to handle the zero speed.
            // 'cutZeroStart:3' u  = cutCurvStructU( ctx, curv, 0, ctx.cfg.LSplitZero, false );
            u = cutCurvStructU(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, curv,
                               ctx->cfg.LSplitZero);
            // 'cutZeroStart:5' if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
            d = curv->b_param + curv->a_param;
            if ((u >= d) || (u <= curv->b_param)) {
                // 'cutZeroStart:6' u = curv.a_param / 2 + curv.b_param;
                u = curv->a_param / 2.0 + curv->b_param;
            }
            // 'cutZeroStart:9' curv1               = curv;
            curvS = *curv;
            // 'cutZeroStart:10' curv1.a_param       = u -curv1.b_param;
            curvS.a_param = u - curvS.b_param;
            // 'cutZeroStart:11' curv1.UseConstJerk  = true;
            curvS.UseConstJerk = true;
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
            b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                             ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                             ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                             ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curvS, r0D, r1D);
            // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
            if (curvS.Info.TRAFO) {
                int loop_ub;
                // 'zeroSpeedCurv:20' r1D = ctx.kin.v_joint( r0D, r1D );
                b_r1D.set_size(r1D.size(0));
                loop_ub = r1D.size(0) - 1;
                for (int i{0}; i <= loop_ub; i++) {
                    b_r1D[i] = r1D[i];
                }
                ctx->kin.v_joint(r0D, b_r1D, r1D);
            }
            //  Compute pseudo jerk based on max allowed jerk
            // 'zeroSpeedCurv:24' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs( r1D ) );
            end_tmp = ctx->cfg.maskTot.size[1] - 1;
            trueCount = 0;
            partialTrueCount = 0;
            for (int b_i{0}; b_i <= end_tmp; b_i++) {
                if (ctx->cfg.maskTot.data[b_i]) {
                    trueCount++;
                    tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
                    partialTrueCount++;
                }
            }
            z1.set_size(r1D.size(0));
            if (r1D.size(0) != 0) {
                int i1;
                i1 = r1D.size(0);
                for (int b_k{0}; b_k < i1; b_k++) {
                    z1[b_k] = std::abs(r1D[b_k]);
                }
            }
            ctx_size[0] = 1;
            ctx_size[1] = trueCount;
            for (int i2{0}; i2 < trueCount; i2++) {
                ctx_data[i2] = ctx->cfg.jmax[tmp_data[i2] - 1];
            }
            jps = coder::internal::minimum(ctx_data, ctx_size) / coder::internal::maximum(z1);
            //  searchU   = true;
            // while searchU
            // 'zeroSpeedCurv:29' searchJps = true;
            // 'zeroSpeedCurv:31' ind = 0;
            // 'zeroSpeedCurv:32' while searchJps
            b_fmax = curvS.Info.FeedRate * 0.5;
            uv[0] = 1U;
            searchJps = true;
            while (searchJps) {
                double b_jps;
                double c_k;
                int b_end;
                int b_partialTrueCount;
                int b_scalarLB;
                int b_vectorUB;
                int c_loop_ub;
                int c_partialTrueCount;
                int c_scalarLB;
                int c_vectorUB;
                int cb_loop_ub;
                int d_loop_ub;
                int d_partialTrueCount;
                int d_scalarLB;
                int d_vectorUB;
                int e_loop_ub;
                int end;
                int f_k;
                int f_loop_ub;
                int g_loop_ub;
                int h_loop_ub;
                int hi;
                int i10;
                int i20;
                int i21;
                int i25;
                int i26;
                int i27;
                int i28;
                int i29;
                int i30;
                int i31;
                int i32;
                int i33;
                int i5;
                int i7;
                int i9;
                int p_loop_ub;
                int s_loop_ub;
                int scalarLB;
                int vectorUB;
                int y_loop_ub;
                bool b_y;
                // 'zeroSpeedCurv:33' ind = ind + 1;
                // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
                //  compute_k : Compute the vector of time steps required by the paramter u to
                //  go from 0 to 1.
                // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
                c_k = std::pow(6.0 / jps, 0.33333333333333331) / ctx->cfg.dt;
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
                        for (int i4{0}; i4 <= b_loop_ub; i4++) {
                            k_vec[i4] = i4;
                        }
                        k_vec[b_loop_ub + 1] = c_k;
                    }
                } else {
                    // 'zeroSpeedCurv:53' else
                    // 'zeroSpeedCurv:54' k_vec = 1;
                    k_vec.set_size(1, 1);
                    k_vec[0] = 1.0;
                }
                // 'zeroSpeedCurv:35' [ searchJps, jps] = calc_u( isEnd, searchJps, jps, ctx, curv,
                // k_vec );
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
                // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec * ctx.cfg.dt,
                // isEnd );
                y.set_size(1, k_vec.size(1));
                c_loop_ub = k_vec.size(1);
                scalarLB = (k_vec.size(1) / 2) << 1;
                vectorUB = scalarLB - 2;
                for (i5 = 0; i5 <= vectorUB; i5 += 2) {
                    __m128d r;
                    r = _mm_loadu_pd(&k_vec[i5]);
                    _mm_storeu_pd(&y[i5], _mm_mul_pd(r, _mm_set1_pd(ctx->cfg.dt)));
                }
                for (i5 = scalarLB; i5 < c_loop_ub; i5++) {
                    y[i5] = k_vec[i5] * ctx->cfg.dt;
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
                r1.set_size(1, y.size(1));
                d_loop_ub = y.size(1);
                for (int i6{0}; i6 < d_loop_ub; i6++) {
                    double varargin_1;
                    varargin_1 = y[i6];
                    r1[i6] = std::pow(varargin_1, 2.0);
                }
                ud.set_size(1, r1.size(1));
                e_loop_ub = r1.size(1);
                b_scalarLB = (r1.size(1) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (i7 = 0; i7 <= b_vectorUB; i7 += 2) {
                    __m128d r2;
                    r2 = _mm_loadu_pd(&r1[i7]);
                    _mm_storeu_pd(&ud[i7],
                                  _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
                }
                for (i7 = b_scalarLB; i7 < e_loop_ub; i7++) {
                    ud[i7] = jps * r1[i7] / 2.0;
                }
                // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                r1.set_size(1, y.size(1));
                f_loop_ub = y.size(1);
                for (int i8{0}; i8 < f_loop_ub; i8++) {
                    double b_varargin_1;
                    b_varargin_1 = y[i8];
                    r1[i8] = std::pow(b_varargin_1, 3.0);
                }
                b_u.set_size(1, r1.size(1));
                g_loop_ub = r1.size(1);
                c_scalarLB = (r1.size(1) / 2) << 1;
                c_vectorUB = c_scalarLB - 2;
                for (i9 = 0; i9 <= c_vectorUB; i9 += 2) {
                    __m128d r3;
                    r3 = _mm_loadu_pd(&r1[i9]);
                    _mm_storeu_pd(&b_u[i9],
                                  _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r3), _mm_set1_pd(6.0)));
                }
                for (i9 = c_scalarLB; i9 < g_loop_ub; i9++) {
                    b_u[i9] = jps * r1[i9] / 6.0;
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
                // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u, ud, udd,
                // uddd );
                udd_vec.set_size(1, y.size(1));
                h_loop_ub = y.size(1);
                d_scalarLB = (y.size(1) / 2) << 1;
                d_vectorUB = d_scalarLB - 2;
                for (i10 = 0; i10 <= d_vectorUB; i10 += 2) {
                    __m128d r4;
                    r4 = _mm_loadu_pd(&y[i10]);
                    _mm_storeu_pd(&udd_vec[i10], _mm_mul_pd(_mm_set1_pd(jps), r4));
                }
                for (i10 = d_scalarLB; i10 < h_loop_ub; i10++) {
                    udd_vec[i10] = jps * y[i10];
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
                g_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curvS, b_u, b_r0D, c_r1D, r2D, r3D);
                // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
                if (curvS.Info.TRAFO) {
                    int i_loop_ub;
                    int k_loop_ub;
                    int m_loop_ub;
                    // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D
                    // );
                    d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
                    i_loop_ub = c_r1D.size(1) - 1;
                    for (int i11{0}; i11 <= i_loop_ub; i11++) {
                        int j_loop_ub;
                        j_loop_ub = c_r1D.size(0) - 1;
                        for (int i12{0}; i12 <= j_loop_ub; i12++) {
                            d_r1D[i12 + d_r1D.size(0) * i11] = c_r1D[i12 + c_r1D.size(0) * i11];
                        }
                    }
                    b_r2D.set_size(r2D.size(0), r2D.size(1));
                    k_loop_ub = r2D.size(1) - 1;
                    for (int i13{0}; i13 <= k_loop_ub; i13++) {
                        int l_loop_ub;
                        l_loop_ub = r2D.size(0) - 1;
                        for (int i14{0}; i14 <= l_loop_ub; i14++) {
                            b_r2D[i14 + b_r2D.size(0) * i13] = r2D[i14 + r2D.size(0) * i13];
                        }
                    }
                    b_r3D.set_size(r3D.size(0), r3D.size(1));
                    m_loop_ub = r3D.size(1) - 1;
                    for (int i15{0}; i15 <= m_loop_ub; i15++) {
                        int n_loop_ub;
                        n_loop_ub = r3D.size(0) - 1;
                        for (int i16{0}; i16 <= n_loop_ub; i16++) {
                            b_r3D[i16 + b_r3D.size(0) * i15] = r3D[i16 + r3D.size(0) * i15];
                        }
                    }
                    ctx->kin.joint(b_r0D, d_r1D, b_r2D, b_r3D, a__1, c_r1D, r2D, r3D);
                }
                // 'calcRVAJfromU:23' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec,
                // ... 'calcRVAJfromU:24'                           udd_vec, uddd_vec, r0D, r1D,
                // r2D, r3D );
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
                    int o_loop_ub;
                    V.set_size(c_r1D.size(0), c_r1D.size(1));
                    o_loop_ub = c_r1D.size(1);
                    for (int i17{0}; i17 < o_loop_ub; i17++) {
                        int e_scalarLB;
                        int e_vectorUB;
                        int i19;
                        int q_loop_ub;
                        q_loop_ub = c_r1D.size(0);
                        e_scalarLB = (c_r1D.size(0) / 2) << 1;
                        e_vectorUB = e_scalarLB - 2;
                        for (i19 = 0; i19 <= e_vectorUB; i19 += 2) {
                            __m128d r5;
                            r5 = _mm_loadu_pd(&c_r1D[i19 + c_r1D.size(0) * i17]);
                            _mm_storeu_pd(&V[i19 + V.size(0) * i17],
                                          _mm_mul_pd(r5, _mm_set1_pd(ud[i17])));
                        }
                        for (i19 = e_scalarLB; i19 < q_loop_ub; i19++) {
                            V[i19 + V.size(0) * i17] = c_r1D[i19 + c_r1D.size(0) * i17] * ud[i17];
                        }
                    }
                } else {
                    b_times(V, c_r1D, ud);
                }
                // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
                r1.set_size(1, ud.size(1));
                p_loop_ub = ud.size(1);
                for (int i18{0}; i18 < p_loop_ub; i18++) {
                    double c_varargin_1;
                    c_varargin_1 = ud[i18];
                    r1[i18] = std::pow(c_varargin_1, 2.0);
                }
                if (r2D.size(1) == 1) {
                    i20 = r1.size(1);
                } else {
                    i20 = r2D.size(1);
                }
                if (c_r1D.size(1) == 1) {
                    i21 = udd_vec.size(1);
                } else {
                    i21 = c_r1D.size(1);
                }
                if ((r2D.size(1) == r1.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
                    (r2D.size(0) == c_r1D.size(0)) && (i20 == i21)) {
                    int r_loop_ub;
                    A.set_size(r2D.size(0), r2D.size(1));
                    r_loop_ub = r2D.size(1);
                    for (int i22{0}; i22 < r_loop_ub; i22++) {
                        int f_scalarLB;
                        int f_vectorUB;
                        int i24;
                        int t_loop_ub;
                        t_loop_ub = r2D.size(0);
                        f_scalarLB = (r2D.size(0) / 2) << 1;
                        f_vectorUB = f_scalarLB - 2;
                        for (i24 = 0; i24 <= f_vectorUB; i24 += 2) {
                            __m128d r6;
                            __m128d r7;
                            r6 = _mm_loadu_pd(&r2D[i24 + r2D.size(0) * i22]);
                            r7 = _mm_loadu_pd(&c_r1D[i24 + c_r1D.size(0) * i22]);
                            _mm_storeu_pd(&A[i24 + A.size(0) * i22],
                                          _mm_add_pd(_mm_mul_pd(r6, _mm_set1_pd(r1[i22])),
                                                     _mm_mul_pd(r7, _mm_set1_pd(udd_vec[i22]))));
                        }
                        for (i24 = f_scalarLB; i24 < t_loop_ub; i24++) {
                            A[i24 + A.size(0) * i22] =
                                r2D[i24 + r2D.size(0) * i22] * r1[i22] +
                                c_r1D[i24 + c_r1D.size(0) * i22] * udd_vec[i22];
                        }
                    }
                } else {
                    binary_expand_op(A, r2D, r1, c_r1D, udd_vec);
                }
                // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .*
                // udd_vec + r1D .* uddd_vec;
                r1.set_size(1, ud.size(1));
                s_loop_ub = ud.size(1);
                for (int i23{0}; i23 < s_loop_ub; i23++) {
                    double d_varargin_1;
                    d_varargin_1 = ud[i23];
                    r1[i23] = std::pow(d_varargin_1, 3.0);
                }
                if (r2D.size(1) == 1) {
                    i25 = ud.size(1);
                } else {
                    i25 = r2D.size(1);
                }
                if (r3D.size(1) == 1) {
                    i26 = r1.size(1);
                } else {
                    i26 = r3D.size(1);
                }
                if (r2D.size(1) == 1) {
                    i27 = ud.size(1);
                } else {
                    i27 = r2D.size(1);
                }
                if (i27 == 1) {
                    i28 = udd_vec.size(1);
                } else if (r2D.size(1) == 1) {
                    i28 = ud.size(1);
                } else {
                    i28 = r2D.size(1);
                }
                if (r3D.size(0) == 1) {
                    i29 = r2D.size(0);
                } else {
                    i29 = r3D.size(0);
                }
                if (r3D.size(1) == 1) {
                    i30 = r1.size(1);
                } else {
                    i30 = r3D.size(1);
                }
                if (r2D.size(1) == 1) {
                    i31 = ud.size(1);
                } else {
                    i31 = r2D.size(1);
                }
                if (i30 == 1) {
                    if (i31 == 1) {
                        i32 = udd_vec.size(1);
                    } else if (r2D.size(1) == 1) {
                        i32 = ud.size(1);
                    } else {
                        i32 = r2D.size(1);
                    }
                } else if (r3D.size(1) == 1) {
                    i32 = r1.size(1);
                } else {
                    i32 = r3D.size(1);
                }
                if (c_r1D.size(1) == 1) {
                    i33 = y.size(1);
                } else {
                    i33 = c_r1D.size(1);
                }
                if ((r3D.size(1) == r1.size(1)) && (r2D.size(1) == ud.size(1)) &&
                    (i25 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) && (i26 == i28) &&
                    (c_r1D.size(1) == y.size(1)) && (i29 == c_r1D.size(0)) && (i32 == i33)) {
                    int u_loop_ub;
                    J.set_size(r3D.size(0), r3D.size(1));
                    u_loop_ub = r3D.size(1);
                    for (int i34{0}; i34 < u_loop_ub; i34++) {
                        int g_scalarLB;
                        int g_vectorUB;
                        int i35;
                        int v_loop_ub;
                        v_loop_ub = r3D.size(0);
                        g_scalarLB = (r3D.size(0) / 2) << 1;
                        g_vectorUB = g_scalarLB - 2;
                        for (i35 = 0; i35 <= g_vectorUB; i35 += 2) {
                            __m128d r10;
                            __m128d r8;
                            __m128d r9;
                            r8 = _mm_loadu_pd(&r3D[i35 + r3D.size(0) * i34]);
                            r9 = _mm_loadu_pd(&r2D[i35 + r2D.size(0) * i34]);
                            r10 = _mm_loadu_pd(&c_r1D[i35 + c_r1D.size(0) * i34]);
                            _mm_storeu_pd(
                                &J[i35 + J.size(0) * i34],
                                _mm_add_pd(
                                    _mm_add_pd(
                                        _mm_mul_pd(r8, _mm_set1_pd(r1[i34])),
                                        _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r9),
                                                              _mm_set1_pd(ud[i34])),
                                                   _mm_set1_pd(udd_vec[i34]))),
                                    _mm_mul_pd(r10, _mm_set1_pd(jps))));
                        }
                        for (i35 = g_scalarLB; i35 < v_loop_ub; i35++) {
                            J[i35 + J.size(0) * i34] =
                                (r3D[i35 + r3D.size(0) * i34] * r1[i34] +
                                 3.0 * r2D[i35 + r2D.size(0) * i34] * ud[i34] * udd_vec[i34]) +
                                c_r1D[i35 + c_r1D.size(0) * i34] * jps;
                        }
                    }
                } else {
                    binary_expand_op(J, r3D, r1, r2D, ud, udd_vec, c_r1D, jps, uv);
                }
                // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u );
                h_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curvS, b_u, b_r0D, c_r1D);
                // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
                if (!curvS.Info.TRAFO) {
                    int w_loop_ub;
                    // 'zeroSpeedCurv:85' else
                    // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
                    e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
                    w_loop_ub = c_r1D.size(1) - 1;
                    for (int i36{0}; i36 <= w_loop_ub; i36++) {
                        int x_loop_ub;
                        x_loop_ub = c_r1D.size(0) - 1;
                        for (int i37{0}; i37 <= x_loop_ub; i37++) {
                            e_r1D[i37 + e_r1D.size(0) * i36] = c_r1D[i37 + c_r1D.size(0) * i36];
                        }
                    }
                    ctx->kin.v_relative(b_r0D, e_r1D, c_r1D);
                } else {
                    // 'zeroSpeedCurv:84' r1D_r     = r1D;
                }
                // 'zeroSpeedCurv:89' safetyFactor = 0.5;
                // 'zeroSpeedCurv:90' fmax =  curv.Info.FeedRate * safetyFactor;
                // 'zeroSpeedCurv:91' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' * safetyFactor;
                b_trueCount = 0;
                b_partialTrueCount = 0;
                for (int e_i{0}; e_i <= end_tmp; e_i++) {
                    if (ctx->cfg.maskTot.data[e_i]) {
                        b_trueCount++;
                        b_tmp_data[b_partialTrueCount] = static_cast<signed char>(e_i + 1);
                        b_partialTrueCount++;
                    }
                }
                for (int i38{0}; i38 < b_trueCount; i38++) {
                    vmax_data[i38] = ctx->cfg.vmax[b_tmp_data[i38] - 1] * 0.5;
                }
                // 'zeroSpeedCurv:92' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' * safetyFactor;
                c_trueCount = 0;
                c_partialTrueCount = 0;
                for (int f_i{0}; f_i <= end_tmp; f_i++) {
                    if (ctx->cfg.maskTot.data[f_i]) {
                        c_trueCount++;
                        c_tmp_data[c_partialTrueCount] = static_cast<signed char>(f_i + 1);
                        c_partialTrueCount++;
                    }
                }
                for (int i39{0}; i39 < c_trueCount; i39++) {
                    amax_data[i39] = ctx->cfg.amax[c_tmp_data[i39] - 1] * 0.5;
                }
                // 'zeroSpeedCurv:93' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' * safetyFactor;
                d_trueCount = 0;
                d_partialTrueCount = 0;
                for (int g_i{0}; g_i <= end_tmp; g_i++) {
                    if (ctx->cfg.maskTot.data[g_i]) {
                        d_trueCount++;
                        d_tmp_data[d_partialTrueCount] = static_cast<signed char>(g_i + 1);
                        d_partialTrueCount++;
                    }
                }
                for (int i40{0}; i40 < d_trueCount; i40++) {
                    jmax_data[i40] = ctx->cfg.jmax[d_tmp_data[i40] - 1] * 0.5;
                }
                // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
                y.set_size(1, c_r1D.size(1));
                y_loop_ub = c_r1D.size(1);
                for (int i41{0}; i41 < y_loop_ub; i41++) {
                    y[i41] = 0.0;
                }
                hi = c_r1D.size(1) - 1;
                if (0 <= c_r1D.size(1) - 1) {
                    nx = ctx->cfg.indCart.size(0);
                    outsize_idx_0 = static_cast<signed char>(ctx->cfg.indCart.size(0));
                    ab_loop_ub = static_cast<signed char>(ctx->cfg.indCart.size(0));
                }
                for (int d_k{0}; d_k <= hi; d_k++) {
                    xv.set_size(outsize_idx_0);
                    for (int i42{0}; i42 < ab_loop_ub; i42++) {
                        xv[i42] = 0.0;
                    }
                    for (int e_k{0}; e_k < nx; e_k++) {
                        xv[e_k] = c_r1D[(ctx->cfg.indCart[e_k] + c_r1D.size(0) * d_k) - 1];
                    }
                    y[d_k] = coder::b_norm(xv);
                }
                if (y.size(1) == ud.size(1)) {
                    int bb_loop_ub;
                    int h_scalarLB;
                    int h_vectorUB;
                    int i43;
                    feed.set_size(1, y.size(1));
                    bb_loop_ub = y.size(1);
                    h_scalarLB = (y.size(1) / 2) << 1;
                    h_vectorUB = h_scalarLB - 2;
                    for (i43 = 0; i43 <= h_vectorUB; i43 += 2) {
                        __m128d r11;
                        __m128d r12;
                        r11 = _mm_loadu_pd(&y[i43]);
                        r12 = _mm_loadu_pd(&ud[i43]);
                        _mm_storeu_pd(&feed[i43], _mm_mul_pd(r11, r12));
                    }
                    for (i43 = h_scalarLB; i43 < bb_loop_ub; i43++) {
                        feed[i43] = y[i43] * ud[i43];
                    }
                } else {
                    times(feed, y, ud);
                }
                // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
                x.set_size(1, feed.size(1));
                cb_loop_ub = feed.size(1);
                for (int i44{0}; i44 < cb_loop_ub; i44++) {
                    x[i44] = (feed[i44] > b_fmax);
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
                    int db_loop_ub;
                    int i47;
                    int i_scalarLB;
                    int i_vectorUB;
                    // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
                    b_feed.set_size(1, feed.size(1));
                    db_loop_ub = feed.size(1);
                    i_scalarLB = (feed.size(1) / 2) << 1;
                    i_vectorUB = i_scalarLB - 2;
                    for (i47 = 0; i47 <= i_vectorUB; i47 += 2) {
                        __m128d r15;
                        r15 = _mm_loadu_pd(&feed[i47]);
                        _mm_storeu_pd(&b_feed[i47], _mm_sub_pd(r15, _mm_set1_pd(b_fmax)));
                    }
                    for (i47 = i_scalarLB; i47 < db_loop_ub; i47++) {
                        b_feed[i47] = feed[i47] - b_fmax;
                    }
                    coder::internal::maximum(b_feed, &f_delta, &iindx);
                    // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed( ind ) ) );
                    b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
                } else {
                    int e_trueCount;
                    int eb_loop_ub;
                    int i_k;
                    int stride_0_0;
                    int stride_1_0;
                    bool c_y;
                    r13.set_size(V.size(0), V.size(1));
                    if ((V.size(0) != 0) && (V.size(1) != 0)) {
                        int i45;
                        i45 = V.size(1);
                        for (int g_k{0}; g_k < i45; g_k++) {
                            int i46;
                            i46 = r13.size(0);
                            for (int h_k{0}; h_k < i46; h_k++) {
                                r13[h_k + r13.size(0) * g_k] = std::abs(V[h_k + V.size(0) * g_k]);
                            }
                        }
                    }
                    if (b_trueCount == 1) {
                        e_trueCount = r13.size(0);
                    } else {
                        e_trueCount = b_trueCount;
                    }
                    r14.set_size(e_trueCount, r13.size(1));
                    stride_0_0 = (r13.size(0) != 1);
                    stride_1_0 = (b_trueCount != 1);
                    eb_loop_ub = r13.size(1);
                    for (int i48{0}; i48 < eb_loop_ub; i48++) {
                        int fb_loop_ub;
                        if (b_trueCount == 1) {
                            fb_loop_ub = r13.size(0);
                        } else {
                            fb_loop_ub = b_trueCount;
                        }
                        for (int i49{0}; i49 < fb_loop_ub; i49++) {
                            r14[i49 + r14.size(0) * i48] =
                                (r13[i49 * stride_0_0 + r13.size(0) * i48] >
                                 vmax_data[i49 * stride_1_0]);
                        }
                    }
                    c_y = false;
                    i_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (i_k <= r14.size(0) * r14.size(1) - 1)) {
                        if (r14[i_k]) {
                            c_y = true;
                            exitg1 = true;
                        } else {
                            i_k++;
                        }
                    }
                    if (c_y) {
                        // 'zeroSpeedCurv:100' elseif( any( abs( V ) > vmax, 'all' ) )
                        // 'zeroSpeedCurv:101' [ v_delta, ind ] = max( abs( V ) - vmax, [], 'all' );
                        if (r13.size(0) == b_trueCount) {
                            int gb_loop_ub;
                            int ib_loop_ub;
                            r16.set_size(r13.size(0), r13.size(1));
                            gb_loop_ub = r13.size(1);
                            for (int i52{0}; i52 < gb_loop_ub; i52++) {
                                int hb_loop_ub;
                                int i55;
                                int j_scalarLB;
                                int j_vectorUB;
                                hb_loop_ub = r13.size(0);
                                j_scalarLB = (r13.size(0) / 2) << 1;
                                j_vectorUB = j_scalarLB - 2;
                                for (i55 = 0; i55 <= j_vectorUB; i55 += 2) {
                                    __m128d r17;
                                    __m128d r18;
                                    r17 = _mm_loadu_pd(&r13[i55 + r13.size(0) * i52]);
                                    r18 = _mm_loadu_pd(&vmax_data[i55]);
                                    _mm_storeu_pd(&r16[i55 + r16.size(0) * i52],
                                                  _mm_sub_pd(r17, r18));
                                }
                                for (i55 = j_scalarLB; i55 < hb_loop_ub; i55++) {
                                    r16[i55 + r16.size(0) * i52] =
                                        r13[i55 + r13.size(0) * i52] - vmax_data[i55];
                                }
                            }
                            r13.set_size(r16.size(0), r16.size(1));
                            ib_loop_ub = r16.size(1);
                            for (int i53{0}; i53 < ib_loop_ub; i53++) {
                                int kb_loop_ub;
                                kb_loop_ub = r16.size(0);
                                for (int i56{0}; i56 < kb_loop_ub; i56++) {
                                    r13[i56 + r13.size(0) * i53] = r16[i56 + r16.size(0) * i53];
                                }
                            }
                            coder::internal::b_maximum(r13, &v_delta, &b_iindx);
                        } else {
                            binary_expand_op(r13, vmax_data, &b_trueCount, &v_delta, &b_iindx);
                        }
                        // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta / abs( V( ind
                        // ) ) ) );
                        b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
                    } else {
                        int b_stride_0_0;
                        int b_stride_1_0;
                        int f_trueCount;
                        int jb_loop_ub;
                        int l_k;
                        bool d_y;
                        r13.set_size(A.size(0), A.size(1));
                        if ((A.size(0) != 0) && (A.size(1) != 0)) {
                            int i50;
                            i50 = A.size(1);
                            for (int j_k{0}; j_k < i50; j_k++) {
                                int i51;
                                i51 = r13.size(0);
                                for (int k_k{0}; k_k < i51; k_k++) {
                                    r13[k_k + r13.size(0) * j_k] =
                                        std::abs(A[k_k + A.size(0) * j_k]);
                                }
                            }
                        }
                        if (c_trueCount == 1) {
                            f_trueCount = r13.size(0);
                        } else {
                            f_trueCount = c_trueCount;
                        }
                        r14.set_size(f_trueCount, r13.size(1));
                        b_stride_0_0 = (r13.size(0) != 1);
                        b_stride_1_0 = (c_trueCount != 1);
                        jb_loop_ub = r13.size(1);
                        for (int i54{0}; i54 < jb_loop_ub; i54++) {
                            int lb_loop_ub;
                            if (c_trueCount == 1) {
                                lb_loop_ub = r13.size(0);
                            } else {
                                lb_loop_ub = c_trueCount;
                            }
                            for (int i57{0}; i57 < lb_loop_ub; i57++) {
                                r14[i57 + r14.size(0) * i54] =
                                    (r13[i57 * b_stride_0_0 + r13.size(0) * i54] >
                                     amax_data[i57 * b_stride_1_0]);
                            }
                        }
                        d_y = false;
                        l_k = 0;
                        exitg1 = false;
                        while ((!exitg1) && (l_k <= r14.size(0) * r14.size(1) - 1)) {
                            if (r14[l_k]) {
                                d_y = true;
                                exitg1 = true;
                            } else {
                                l_k++;
                            }
                        }
                        if (d_y) {
                            // 'zeroSpeedCurv:103' elseif( any( abs( A ) > amax, 'all' ) )
                            // 'zeroSpeedCurv:104' [ a_delta, ind ] = max( abs( A ) - amax, [],
                            // 'all' );
                            if (r13.size(0) == c_trueCount) {
                                int mb_loop_ub;
                                int ob_loop_ub;
                                r19.set_size(r13.size(0), r13.size(1));
                                mb_loop_ub = r13.size(1);
                                for (int i60{0}; i60 < mb_loop_ub; i60++) {
                                    int i63;
                                    int k_scalarLB;
                                    int k_vectorUB;
                                    int nb_loop_ub;
                                    nb_loop_ub = r13.size(0);
                                    k_scalarLB = (r13.size(0) / 2) << 1;
                                    k_vectorUB = k_scalarLB - 2;
                                    for (i63 = 0; i63 <= k_vectorUB; i63 += 2) {
                                        __m128d r20;
                                        __m128d r21;
                                        r20 = _mm_loadu_pd(&r13[i63 + r13.size(0) * i60]);
                                        r21 = _mm_loadu_pd(&amax_data[i63]);
                                        _mm_storeu_pd(&r19[i63 + r19.size(0) * i60],
                                                      _mm_sub_pd(r20, r21));
                                    }
                                    for (i63 = k_scalarLB; i63 < nb_loop_ub; i63++) {
                                        r19[i63 + r19.size(0) * i60] =
                                            r13[i63 + r13.size(0) * i60] - amax_data[i63];
                                    }
                                }
                                r13.set_size(r19.size(0), r19.size(1));
                                ob_loop_ub = r19.size(1);
                                for (int i61{0}; i61 < ob_loop_ub; i61++) {
                                    int qb_loop_ub;
                                    qb_loop_ub = r19.size(0);
                                    for (int i64{0}; i64 < qb_loop_ub; i64++) {
                                        r13[i64 + r13.size(0) * i61] = r19[i64 + r19.size(0) * i61];
                                    }
                                }
                                coder::internal::b_maximum(r13, &a_delta, &c_iindx);
                            } else {
                                binary_expand_op(r13, amax_data, &c_trueCount, &a_delta, &c_iindx);
                            }
                            // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs( A(
                            // ind ) ) ) );
                            b_jps = jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                        } else {
                            int c_stride_0_0;
                            int c_stride_1_0;
                            int g_trueCount;
                            int o_k;
                            int pb_loop_ub;
                            bool e_y;
                            r13.set_size(J.size(0), J.size(1));
                            if ((J.size(0) != 0) && (J.size(1) != 0)) {
                                int i58;
                                i58 = J.size(1);
                                for (int m_k{0}; m_k < i58; m_k++) {
                                    int i59;
                                    i59 = r13.size(0);
                                    for (int n_k{0}; n_k < i59; n_k++) {
                                        r13[n_k + r13.size(0) * m_k] =
                                            std::abs(J[n_k + J.size(0) * m_k]);
                                    }
                                }
                            }
                            if (d_trueCount == 1) {
                                g_trueCount = r13.size(0);
                            } else {
                                g_trueCount = d_trueCount;
                            }
                            r14.set_size(g_trueCount, r13.size(1));
                            c_stride_0_0 = (r13.size(0) != 1);
                            c_stride_1_0 = (d_trueCount != 1);
                            pb_loop_ub = r13.size(1);
                            for (int i62{0}; i62 < pb_loop_ub; i62++) {
                                int rb_loop_ub;
                                if (d_trueCount == 1) {
                                    rb_loop_ub = r13.size(0);
                                } else {
                                    rb_loop_ub = d_trueCount;
                                }
                                for (int i65{0}; i65 < rb_loop_ub; i65++) {
                                    r14[i65 + r14.size(0) * i62] =
                                        (r13[i65 * c_stride_0_0 + r13.size(0) * i62] >
                                         jmax_data[i65 * c_stride_1_0]);
                                }
                            }
                            e_y = false;
                            o_k = 0;
                            exitg1 = false;
                            while ((!exitg1) && (o_k <= r14.size(0) * r14.size(1) - 1)) {
                                if (r14[o_k]) {
                                    e_y = true;
                                    exitg1 = true;
                                } else {
                                    o_k++;
                                }
                            }
                            if (e_y) {
                                // 'zeroSpeedCurv:106' elseif( any( abs( J ) > jmax, 'all' ) )
                                // 'zeroSpeedCurv:107' [ j_delta, ind ] = max( abs( J ) - jmax, [],
                                // 'all' );
                                if (r13.size(0) == d_trueCount) {
                                    int sb_loop_ub;
                                    int ub_loop_ub;
                                    r22.set_size(r13.size(0), r13.size(1));
                                    sb_loop_ub = r13.size(1);
                                    for (int i66{0}; i66 < sb_loop_ub; i66++) {
                                        int i68;
                                        int l_scalarLB;
                                        int l_vectorUB;
                                        int tb_loop_ub;
                                        tb_loop_ub = r13.size(0);
                                        l_scalarLB = (r13.size(0) / 2) << 1;
                                        l_vectorUB = l_scalarLB - 2;
                                        for (i68 = 0; i68 <= l_vectorUB; i68 += 2) {
                                            __m128d r23;
                                            __m128d r24;
                                            r23 = _mm_loadu_pd(&r13[i68 + r13.size(0) * i66]);
                                            r24 = _mm_loadu_pd(&jmax_data[i68]);
                                            _mm_storeu_pd(&r22[i68 + r22.size(0) * i66],
                                                          _mm_sub_pd(r23, r24));
                                        }
                                        for (i68 = l_scalarLB; i68 < tb_loop_ub; i68++) {
                                            r22[i68 + r22.size(0) * i66] =
                                                r13[i68 + r13.size(0) * i66] - jmax_data[i68];
                                        }
                                    }
                                    r13.set_size(r22.size(0), r22.size(1));
                                    ub_loop_ub = r22.size(1);
                                    for (int i67{0}; i67 < ub_loop_ub; i67++) {
                                        int vb_loop_ub;
                                        vb_loop_ub = r22.size(0);
                                        for (int i69{0}; i69 < vb_loop_ub; i69++) {
                                            r13[i69 + r13.size(0) * i67] =
                                                r22[i69 + r22.size(0) * i67];
                                        }
                                    }
                                    coder::internal::b_maximum(r13, &j_delta, &d_iindx);
                                } else {
                                    binary_expand_op(r13, jmax_data, &d_trueCount, &j_delta,
                                                     &d_iindx);
                                }
                                // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 - j_delta /
                                // abs( J( ind ) ) ) );
                                b_jps =
                                    jps * (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[d_iindx - 1])));
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
            // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec * ctx.cfg.dt, isEnd
            // );
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
            curvS.ConstJerk = jps;
            // 'cutZeroStart:14' curv1.Info.zspdmode = ZSpdMode.ZN;
            curvS.Info.zspdmode = ZSpdMode_ZN;
            // 'cutZeroStart:15' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
            curvS.Info.gcode_source_line = curv->Info.gcode_source_line;
            // 'cutZeroStart:17' curv2               = curv;
            c_curv = *curv;
            // 'cutZeroStart:18' curv2.UseConstJerk  = false;
            c_curv.UseConstJerk = false;
            // 'cutZeroStart:19' curv2.b_param       = u;
            c_curv.b_param = u;
            // 'cutZeroStart:20' curv2.a_param       = curv.a_param  + curv.b_param - curv2.b_param;
            c_curv.a_param = d - u;
            // 'cutZeroStart:22' if( isAZeroEnd( curv ) )
            //  isAZeroEnd : Return true if the curv ends with zero speed
            //  Input :
            //  curv  : The curve struct
            // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
            // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'cutZeroStart:23' curv2.Info.zspdmode = ZSpdMode.NZ;
                c_curv.Info.zspdmode = ZSpdMode_NZ;
            } else {
                // 'isAZeroEnd:9' zeroFlag = false;
                // 'cutZeroStart:24' else
                // 'cutZeroStart:25' curv2.Info.zspdmode = ZSpdMode.NN;
                c_curv.Info.zspdmode = ZSpdMode_NN;
            }
            // 'cutZeroStart:28' if( coder.target("MATLAB") )
            *curv = c_curv;
            // 'splitCurvStruct:19' ctx.q_split.push( curvS );
            ctx->q_split.push(&curvS);
        } else {
            // 'isAZeroStart:8' zeroFlag = false;
        }
        // 'splitCurvStruct:22' hasEndSpeed = false;
        hasEndSpeed = false;
        // 'splitCurvStruct:23' if( isAZeroEnd( curv ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:7' zeroFlag = true;
            //  cut zero End
            // 'splitCurvStruct:25' [ curv, curvE ] = cutZeroEnd( ctx, curv );
            b_curv = *curv;
            cutZeroEnd(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                       ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                       ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                       ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax,
                       ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.LSplitZero, ctx->cfg.dt,
                       ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &ctx->kin, &b_curv, curv,
                       &curvE);
            // 'splitCurvStruct:26' hasEndSpeed     = true;
            hasEndSpeed = true;
        } else {
            // 'isAZeroEnd:9' zeroFlag = false;
        }
        // 'splitCurvStruct:29' L       = LengthCurv( ctx, curv, 0, 1 );
        L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                       ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                       ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                       ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                       ctx->cfg.GaussLegendreW, curv->Info, curv->R0, curv->R1,
                       curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                       curv->CoeffP5, curv->sp_index, curv->a_param, curv->b_param);
        // 'splitCurvStruct:30' L_split = ctx.cfg.LSplit;
        //  Number of sub segments
        // 'splitCurvStruct:33' N = ceil( L / L_split );
        N = std::ceil(L / ctx->cfg.LSplit);
        //  Length of the sub segments
        // 'splitCurvStruct:36' L_split = L / N;
        L_split = L / N;
        //  Loop
        // 'splitCurvStruct:39' u0 = 0;
        // 'splitCurvStruct:41' for k = 1 : N - 1
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= static_cast<int>(N - 1.0) - 1)) {
            double u1_tilda;
            // 'splitCurvStruct:42' u1_tilda  = cutCurvStructU( ctx, curv, u0, L_split, false );
            u1_tilda =
                cutCurvStructU(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, curv, L_split);
            // 'splitCurvStruct:43' u1 = ( u1_tilda - curv.b_param ) / curv.a_param;
            // 'splitCurvStruct:44' if( u1 < 1 )
            if ((u1_tilda - curv->b_param) / curv->a_param < 1.0) {
                // 'splitCurvStruct:45' curvSplited         = curv;
                curvSplited = *curv;
                // 'splitCurvStruct:46' curvSplited.a_param = u1_tilda - curvSplited.b_param;
                curvSplited.a_param = u1_tilda - curvSplited.b_param;
                // 'splitCurvStruct:48' if( isAZeroStart( curvSplited ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  curv  : The curve struct
                // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if ((curvSplited.Info.zspdmode == ZSpdMode_ZN) ||
                    (curvSplited.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:6' zeroFlag = true;
                    // 'splitCurvStruct:49' curvSplited.Info.zspdmode = ZSpdMode.ZN;
                    curvSplited.Info.zspdmode = ZSpdMode_ZN;
                } else {
                    // 'isAZeroStart:8' zeroFlag = false;
                    // 'splitCurvStruct:50' else
                    // 'splitCurvStruct:51' curvSplited.Info.zspdmode = ZSpdMode.NN;
                    curvSplited.Info.zspdmode = ZSpdMode_NN;
                }
                // 'splitCurvStruct:54' curv.a_param        = curv.a_param  + curv.b_param...
                // 'splitCurvStruct:55'                               - u1_tilda;
                curv->a_param = (curv->a_param + curv->b_param) - u1_tilda;
                // 'splitCurvStruct:56' curv.b_param        = u1_tilda;
                curv->b_param = u1_tilda;
                // 'splitCurvStruct:58' if( isAZeroEnd( curv ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:7' zeroFlag = true;
                    // 'splitCurvStruct:59' curv.Info.zspdmode = ZSpdMode.NZ;
                    curv->Info.zspdmode = ZSpdMode_NZ;
                } else {
                    // 'isAZeroEnd:9' zeroFlag = false;
                    // 'splitCurvStruct:60' else
                    // 'splitCurvStruct:61' curv.Info.zspdmode = ZSpdMode.NN;
                    curv->Info.zspdmode = ZSpdMode_NN;
                }
                // 'splitCurvStruct:67' ctx.q_split.push( curvSplited );
                ctx->q_split.push(&curvSplited);
                k++;
            } else {
                // 'splitCurvStruct:63' else
                exitg1 = true;
            }
        }
        // 'splitCurvStruct:71' ctx.q_split.push( curv );
        ctx->q_split.push(curv);
        // 'splitCurvStruct:73' if( hasEndSpeed )
        if (hasEndSpeed) {
            //  cut zero End
            // 'splitCurvStruct:75' ctx.q_split.push( curvE );
            ctx->q_split.push(&curvE);
        }
    }
}

} // namespace ocn

//
// File trailer for splitCurvStruct.cpp
//
// [EOF]
//
