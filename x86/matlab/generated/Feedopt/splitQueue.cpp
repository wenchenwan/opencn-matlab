//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitQueue.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:55:52
//

// Include Files
#include "splitQueue.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStructU.h"
#include "cutZeroStart.h"
#include "kin_J_ar_xyzbc.h"
#include "minOrMax.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "vecnorm.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function ctx = splitQueue( ctx )
//
// Arguments    : const b_FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void splitQueue(const b_FeedoptContext *ctx)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> c_J;
    ::coder::array<double, 2U> c_feed;
    ::coder::array<double, 2U> c_r1D;
    ::coder::array<double, 2U> d_r1D;
    ::coder::array<double, 2U> e_r1D;
    ::coder::array<double, 2U> f_r1D;
    ::coder::array<double, 2U> feed;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> r15;
    ::coder::array<double, 2U> r18;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r21;
    ::coder::array<double, 2U> r24;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> ud;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<bool, 2U> b_feed;
    ::coder::array<bool, 2U> r16;
    CurvStruct b_curv;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    double J[5][5];
    double amax_data[6];
    double ctx_data[6];
    double jmax_data[6];
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double vmax_data[6];
    double b_J[5];
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
    int b_iindx;
    int b_trueCount;
    int c_iindx;
    int c_trueCount;
    int d_iindx;
    int d_trueCount;
    int iindx;
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
    // 'splitQueue:3' if ctx.q_smooth.isempty()
    if (!ctx->q_smooth.isempty()) {
        unsigned int N;
        int i;
        // 'splitQueue:5' DebugLog( DebugCfg.Validate,        'Splitting...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'splitQueue:6' DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'splitQueue:9' N = ctx.q_smooth.size;
        N = ctx->q_smooth.size();
        // 'splitQueue:11' for k = 1 : N
        i = static_cast<int>(N);
        if (0 <= static_cast<int>(N) - 1) {
            paramsDefaultCurv(
                &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff,
                params_spline_Bl_breakpoints, &params_spline_Bl_handle, &params_spline_Bl_order,
                params_spline_coeff, params_spline_knots, &params_spline_Ltot, params_spline_Lk,
                params_R0, params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp,
                &c_expl_temp, params_CoeffP5, &d_expl_temp);
        }
        for (int k{0}; k < i; k++) {
            // 'splitQueue:12' ctx = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
            ctx->q_smooth.get(k + 1U, &curv);
            //  SplitCurvStruct : Split the curv structs with a zero speed.
            //  Inputs  :
            //  ctx   : The context
            //  curv  : The curv struct
            //  Output  :
            //  ctx   : The modified context
            // 'splitCurvStruct:10' if( ~coder.target( 'MATLAB' ) )
            // 'splitCurvStruct:10' curvE = constrCurvStructType;
            //  constrCurvStructType : Constructs a constrCurvStruct with default values.
            // 'constrCurvStructType:4' if( nargin > 0 )
            // 'constrCurvStructType:6' else
            // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
            // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
            // 'constrCurvStructType:12' else
            // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
            // params.spline, ... 'constrCurvStructType:14'         params.R0, params.R1, ...
            // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec,
            // params.theta, ... 'constrCurvStructType:16'         params.pitch, params.CoeffP5,
            // params.Coeff );
            b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                               params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                               params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                               params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                               params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
                               params_spline_Bl_breakpoints, params_spline_Bl_handle,
                               params_spline_Bl_order, params_spline_coeff, params_spline_knots,
                               params_spline_Ltot, params_spline_Lk, params_R0, params_R1,
                               params_Cprim, params_evec, params_CoeffP5, &curvE);
            // 'splitCurvStruct:12' if ( curv.Info.Type == CurveType.TransP5 )
            if (curv.Info.Type == CurveType_TransP5) {
                // 'splitCurvStruct:13' ctx.q_split.push( curv );
                ctx->q_split.push(&curv);
            } else {
                double L;
                double L_split;
                double b_N;
                int b_k;
                bool exitg1;
                bool hasEndSpeed;
                // 'splitCurvStruct:16' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  curv  : The curve struct
                // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:6' zeroFlag = true;
                    //  cut zero Start
                    // 'splitCurvStruct:18' [ curvS, curv ] = cutZeroStart( ctx, curv );
                    b_curv = curv;
                    cutZeroStart(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax,
                                 ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                 ctx->cfg.GaussLegendreW, &ctx->kin, &b_curv, &curvS, &curv);
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
                if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    double b_fmax;
                    double d;
                    double jps;
                    double u;
                    int end_tmp;
                    int loop_ub;
                    int partialTrueCount;
                    int trueCount;
                    bool searchJps;
                    // 'isAZeroEnd:7' zeroFlag = true;
                    //  cut zero End
                    // 'splitCurvStruct:25' [ curv, curvE ] = cutZeroEnd( ctx, curv );
                    //  cutZeroEnd : Cut the end of the given to handle the zero speed.
                    // 'cutZeroEnd:3' u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
                    u = b_cutCurvStructU(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart, ctx->cfg.maskRot,
                                         ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                         ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                         ctx->cfg.GaussLegendreW, &curv, ctx->cfg.LSplitZero);
                    // 'cutZeroEnd:5' if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
                    d = curv.b_param + curv.a_param;
                    if ((u >= d) || (u <= curv.b_param)) {
                        // 'cutZeroEnd:6' u = curv.a_param / 2 + curv.b_param;
                        u = curv.a_param / 2.0 + curv.b_param;
                    }
                    // 'cutZeroEnd:9' curv2                   = curv;
                    curvE = curv;
                    // 'cutZeroEnd:10' curv2.UseConstJerk      = true;
                    curvE.UseConstJerk = true;
                    // 'cutZeroEnd:11' curv2.b_param           = u;
                    curvE.b_param = u;
                    // 'cutZeroEnd:12' curv2.a_param           = curv.a_param  + curv.b_param -
                    // curv2.b_param;
                    curvE.a_param = d - u;
                    // 'cutZeroEnd:13' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
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
                    // 'zeroSpeedCurv:15' uk = 1 - uk ;
                    // 'zeroSpeedCurv:17' [ r0D, r1D ] = EvalCurvStruct( ctx, curv, uk );
                    c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &curvE, r0D, r1D);
                    loop_ub = r1D.size(0);
                    b_r1D.set_size(r1D.size(0));
                    for (int i1{0}; i1 < loop_ub; i1++) {
                        b_r1D[i1] = r1D[i1];
                    }
                    // 'zeroSpeedCurv:19' if( curv.Info.TRAFO )
                    if (curvE.Info.TRAFO) {
                        int b_loop_ub;
                        int c_loop_ub;
                        // 'zeroSpeedCurv:20' r1D = ctx.kin.v_joint( r0D, r1D );
                        //              if( coder.target( 'MATLAB' ) )
                        // 'Kinematics:119' N   = size( r_r, 2 );
                        // 'Kinematics:120' v_a = zeros( size( v_r ) );
                        b_r1D.set_size(r1D.size(0));
                        b_loop_ub = r1D.size(0);
                        for (int i2{0}; i2 < b_loop_ub; i2++) {
                            b_r1D[i2] = 0.0;
                        }
                        // 'Kinematics:122' for j = 1 : N
                        // 'Kinematics:123' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                        kin_J_ar_xyzbc(r0D, ctx->kin.parameters, J);
                        // 'Kinematics:124' v_a( :, j ) = J * v_r( :, j );
                        for (int i4{0}; i4 < 5; i4++) {
                            double d1;
                            d1 = 0.0;
                            for (int i6{0}; i6 < 5; i6++) {
                                d1 += J[i6][i4] * r1D[i6];
                            }
                            b_J[i4] = d1;
                        }
                        c_loop_ub = r1D.size(0);
                        for (int i5{0}; i5 < c_loop_ub; i5++) {
                            b_r1D[i5] = b_J[i5];
                        }
                        //              end
                    }
                    //  Compute pseudo jerk based on max allowed jerk
                    // 'zeroSpeedCurv:24' jps = min( ctx.cfg.jmax( ctx.cfg.maskTot ) ) / max( abs(
                    // r1D ) );
                    end_tmp = ctx->cfg.maskTot.size[1] - 1;
                    trueCount = 0;
                    for (int b_i{0}; b_i <= end_tmp; b_i++) {
                        if (ctx->cfg.maskTot.data[b_i]) {
                            trueCount++;
                        }
                    }
                    partialTrueCount = 0;
                    for (int c_i{0}; c_i <= end_tmp; c_i++) {
                        if (ctx->cfg.maskTot.data[c_i]) {
                            tmp_data[partialTrueCount] = static_cast<signed char>(c_i + 1);
                            partialTrueCount++;
                        }
                    }
                    ctx_size[0] = 1;
                    ctx_size[1] = trueCount;
                    for (int i3{0}; i3 < trueCount; i3++) {
                        ctx_data[i3] = ctx->cfg.jmax[tmp_data[i3] - 1];
                    }
                    r.set_size(b_r1D.size(0));
                    if (b_r1D.size(0) != 0) {
                        int i7;
                        i7 = b_r1D.size(0);
                        for (int c_k{0}; c_k < i7; c_k++) {
                            r[c_k] = std::abs(b_r1D[c_k]);
                        }
                    }
                    jps =
                        coder::internal::minimum(ctx_data, ctx_size) / coder::internal::maximum(r);
                    //  searchU   = true;
                    // while searchU
                    // 'zeroSpeedCurv:29' searchJps = true;
                    // 'zeroSpeedCurv:31' ind = 0;
                    // 'zeroSpeedCurv:32' while searchJps
                    b_fmax = curvE.Info.FeedRate * 0.5;
                    uv[0] = 1U;
                    searchJps = true;
                    while (searchJps) {
                        double b_jps;
                        double d_k;
                        double k_tmp;
                        int b_end;
                        int b_partialTrueCount;
                        int b_scalarLB;
                        int b_vectorUB;
                        int c_partialTrueCount;
                        int c_scalarLB;
                        int c_vectorUB;
                        int cb_loop_ub;
                        int d_partialTrueCount;
                        int d_scalarLB;
                        int d_vectorUB;
                        int e_k;
                        int e_loop_ub;
                        int e_scalarLB;
                        int e_vectorUB;
                        int end;
                        int f_loop_ub;
                        int fb_loop_ub;
                        int g_loop_ub;
                        int h_loop_ub;
                        int i10;
                        int i12;
                        int i14;
                        int i15;
                        int i16;
                        int i26;
                        int i27;
                        int i31;
                        int i32;
                        int i33;
                        int i34;
                        int i35;
                        int i36;
                        int i37;
                        int i38;
                        int i39;
                        int i_loop_ub;
                        int j_loop_ub;
                        int k_loop_ub;
                        int s_loop_ub;
                        int scalarLB;
                        int v_loop_ub;
                        int vectorUB;
                        bool b_y;
                        // 'zeroSpeedCurv:33' ind = ind + 1;
                        // 'zeroSpeedCurv:34' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
                        //  compute_k : Compute the vector of time steps required by the paramter u
                        //  to go from 0 to 1.
                        // 'zeroSpeedCurv:48' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
                        k_tmp = std::pow(6.0 / jps, 0.33333333333333331);
                        d_k = k_tmp / ctx->cfg.dt;
                        // 'zeroSpeedCurv:50' if( k > 0 )
                        if (d_k > 0.0) {
                            int d_loop_ub;
                            // 'zeroSpeedCurv:51' k_vec = 0 : k;
                            d_loop_ub = static_cast<int>(std::floor(d_k));
                            k_vec.set_size(1, d_loop_ub + 1);
                            for (int i8{0}; i8 <= d_loop_ub; i8++) {
                                k_vec[i8] = i8;
                            }
                            // 'zeroSpeedCurv:52' if( k_vec( end ) < k )
                            if (d_loop_ub < d_k) {
                                // 'zeroSpeedCurv:52' k_vec = [ k_vec, k ];
                                k_vec.set_size(1, d_loop_ub + 2);
                                for (int i9{0}; i9 <= d_loop_ub; i9++) {
                                    k_vec[i9] = i9;
                                }
                                k_vec[d_loop_ub + 1] = d_k;
                            }
                        } else {
                            // 'zeroSpeedCurv:53' else
                            // 'zeroSpeedCurv:54' k_vec = 1;
                            k_vec.set_size(1, 1);
                            k_vec[0] = 1.0;
                        }
                        // 'zeroSpeedCurv:35' [ searchJps, jps] = calc_u( isEnd, searchJps, jps,
                        // ctx, curv, k_vec );
                        b_jps = jps;
                        //  calc_u : Calcule u for a given pseudo jerk. U is assured to give
                        //  velocity, acceleration and jerk below the provided limits. Inputs :
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
                        // 'zeroSpeedCurv:77' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec *
                        // ctx.cfg.dt, isEnd );
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
                        e_loop_ub = k_vec.size(1);
                        scalarLB = (k_vec.size(1) / 2) << 1;
                        vectorUB = scalarLB - 2;
                        for (i10 = 0; i10 <= vectorUB; i10 += 2) {
                            __m128d r1;
                            r1 = _mm_loadu_pd(&k_vec[i10]);
                            _mm_storeu_pd(&y[i10],
                                          _mm_sub_pd(_mm_set1_pd(k_tmp),
                                                     _mm_mul_pd(r1, _mm_set1_pd(ctx->cfg.dt))));
                        }
                        for (i10 = scalarLB; i10 < e_loop_ub; i10++) {
                            y[i10] = k_tmp - k_vec[i10] * ctx->cfg.dt;
                        }
                        //  Compute u and its derivatives based on constant jerk
                        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
                        uv[1] = static_cast<unsigned int>(y.size(1));
                        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
                        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
                        r2.set_size(1, y.size(1));
                        f_loop_ub = y.size(1);
                        for (int i11{0}; i11 < f_loop_ub; i11++) {
                            double varargin_1;
                            varargin_1 = y[i11];
                            r2[i11] = std::pow(varargin_1, 2.0);
                        }
                        ud.set_size(1, r2.size(1));
                        g_loop_ub = r2.size(1);
                        b_scalarLB = (r2.size(1) / 2) << 1;
                        b_vectorUB = b_scalarLB - 2;
                        for (i12 = 0; i12 <= b_vectorUB; i12 += 2) {
                            __m128d r3;
                            r3 = _mm_loadu_pd(&r2[i12]);
                            _mm_storeu_pd(&ud[i12], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r3),
                                                               _mm_set1_pd(2.0)));
                        }
                        for (i12 = b_scalarLB; i12 < g_loop_ub; i12++) {
                            ud[i12] = jps * r2[i12] / 2.0;
                        }
                        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                        r2.set_size(1, y.size(1));
                        h_loop_ub = y.size(1);
                        for (int i13{0}; i13 < h_loop_ub; i13++) {
                            double b_varargin_1;
                            b_varargin_1 = y[i13];
                            r2[i13] = std::pow(b_varargin_1, 3.0);
                        }
                        b_u.set_size(1, r2.size(1));
                        i_loop_ub = r2.size(1);
                        c_scalarLB = (r2.size(1) / 2) << 1;
                        c_vectorUB = c_scalarLB - 2;
                        for (i14 = 0; i14 <= c_vectorUB; i14 += 2) {
                            __m128d r4;
                            r4 = _mm_loadu_pd(&r2[i14]);
                            _mm_storeu_pd(&b_u[i14], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r4),
                                                                _mm_set1_pd(6.0)));
                        }
                        for (i14 = c_scalarLB; i14 < i_loop_ub; i14++) {
                            b_u[i14] = jps * r2[i14] / 6.0;
                        }
                        // 'constJerkU:33' u( u > 1 ) = 1;
                        end = b_u.size(1);
                        for (int d_i{0}; d_i < end; d_i++) {
                            if (b_u[d_i] > 1.0) {
                                b_u[d_i] = 1.0;
                            }
                        }
                        // 'constJerkU:34' u( u < 0 ) = 0;
                        b_end = b_u.size(1);
                        for (int e_i{0}; e_i < b_end; e_i++) {
                            if (b_u[e_i] < 0.0) {
                                b_u[e_i] = 0.0;
                            }
                        }
                        // 'constJerkU:36' if( isEnd )
                        //  Reverse time ( Backward-like integration )
                        // 'constJerkU:37' u    = 1 - u;
                        b_u.set_size(1, b_u.size(1));
                        j_loop_ub = b_u.size(1);
                        d_scalarLB = (b_u.size(1) / 2) << 1;
                        d_vectorUB = d_scalarLB - 2;
                        for (i15 = 0; i15 <= d_vectorUB; i15 += 2) {
                            __m128d r5;
                            r5 = _mm_loadu_pd(&b_u[i15]);
                            _mm_storeu_pd(&b_u[i15], _mm_sub_pd(_mm_set1_pd(1.0), r5));
                        }
                        for (i15 = d_scalarLB; i15 < j_loop_ub; i15++) {
                            b_u[i15] = 1.0 - b_u[i15];
                        }
                        // 'constJerkU:38' ud   = ud;
                        // 'constJerkU:39' udd  = -udd;
                        // 'constJerkU:40' uddd = uddd;
                        // 'zeroSpeedCurv:79' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u,
                        // ud, udd, uddd );
                        udd_vec.set_size(1, y.size(1));
                        k_loop_ub = y.size(1);
                        e_scalarLB = (y.size(1) / 2) << 1;
                        e_vectorUB = e_scalarLB - 2;
                        for (i16 = 0; i16 <= e_vectorUB; i16 += 2) {
                            __m128d r6;
                            r6 = _mm_loadu_pd(&y[i16]);
                            _mm_storeu_pd(
                                &udd_vec[i16],
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(jps), r6), _mm_set1_pd(-1.0)));
                        }
                        for (i16 = e_scalarLB; i16 < k_loop_ub; i16++) {
                            udd_vec[i16] = -(jps * y[i16]);
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
                        // 'calcRVAJfromU:17' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv,
                        // u_vec );
                        g_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart, ctx->cfg.maskRot,
                                         ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                         ctx->cfg.NCart, ctx->cfg.NRot, &curvE, b_u, b_r0D, c_r1D,
                                         r2D, r3D);
                        // 'calcRVAJfromU:19' if( curv.Info.TRAFO )
                        if (curvE.Info.TRAFO) {
                            int l_loop_ub;
                            int n_loop_ub;
                            int p_loop_ub;
                            // 'calcRVAJfromU:20' [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D,
                            // r2D, r3D );
                            d_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
                            l_loop_ub = c_r1D.size(1) - 1;
                            for (int i17{0}; i17 <= l_loop_ub; i17++) {
                                int m_loop_ub;
                                m_loop_ub = c_r1D.size(0) - 1;
                                for (int i18{0}; i18 <= m_loop_ub; i18++) {
                                    d_r1D[i18 + d_r1D.size(0) * i17] =
                                        c_r1D[i18 + c_r1D.size(0) * i17];
                                }
                            }
                            b_r2D.set_size(r2D.size(0), r2D.size(1));
                            n_loop_ub = r2D.size(1) - 1;
                            for (int i19{0}; i19 <= n_loop_ub; i19++) {
                                int o_loop_ub;
                                o_loop_ub = r2D.size(0) - 1;
                                for (int i20{0}; i20 <= o_loop_ub; i20++) {
                                    b_r2D[i20 + b_r2D.size(0) * i19] = r2D[i20 + r2D.size(0) * i19];
                                }
                            }
                            b_r3D.set_size(r3D.size(0), r3D.size(1));
                            p_loop_ub = r3D.size(1) - 1;
                            for (int i21{0}; i21 <= p_loop_ub; i21++) {
                                int q_loop_ub;
                                q_loop_ub = r3D.size(0) - 1;
                                for (int i22{0}; i22 <= q_loop_ub; i22++) {
                                    b_r3D[i22 + b_r3D.size(0) * i21] = r3D[i22 + r3D.size(0) * i21];
                                }
                            }
                            ctx->kin.joint(b_r0D, d_r1D, b_r2D, b_r3D, a__1, c_r1D, r2D, r3D);
                        }
                        // 'calcRVAJfromU:23' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv(
                        // ud_vec, ... 'calcRVAJfromU:24'                           udd_vec,
                        // uddd_vec, r0D, r1D, r2D, r3D );
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
                            int r_loop_ub;
                            V.set_size(c_r1D.size(0), c_r1D.size(1));
                            r_loop_ub = c_r1D.size(1);
                            for (int i23{0}; i23 < r_loop_ub; i23++) {
                                int f_scalarLB;
                                int f_vectorUB;
                                int i25;
                                int t_loop_ub;
                                t_loop_ub = c_r1D.size(0);
                                f_scalarLB = (c_r1D.size(0) / 2) << 1;
                                f_vectorUB = f_scalarLB - 2;
                                for (i25 = 0; i25 <= f_vectorUB; i25 += 2) {
                                    __m128d r7;
                                    r7 = _mm_loadu_pd(&c_r1D[i25 + c_r1D.size(0) * i23]);
                                    _mm_storeu_pd(&V[i25 + V.size(0) * i23],
                                                  _mm_mul_pd(r7, _mm_set1_pd(ud[i23])));
                                }
                                for (i25 = f_scalarLB; i25 < t_loop_ub; i25++) {
                                    V[i25 + V.size(0) * i23] =
                                        c_r1D[i25 + c_r1D.size(0) * i23] * ud[i23];
                                }
                            }
                        } else {
                            b_times(V, c_r1D, ud);
                        }
                        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
                        r2.set_size(1, ud.size(1));
                        s_loop_ub = ud.size(1);
                        for (int i24{0}; i24 < s_loop_ub; i24++) {
                            double c_varargin_1;
                            c_varargin_1 = ud[i24];
                            r2[i24] = std::pow(c_varargin_1, 2.0);
                        }
                        if (r2D.size(1) == 1) {
                            i26 = r2.size(1);
                        } else {
                            i26 = r2D.size(1);
                        }
                        if (c_r1D.size(1) == 1) {
                            i27 = udd_vec.size(1);
                        } else {
                            i27 = c_r1D.size(1);
                        }
                        if ((r2D.size(1) == r2.size(1)) && (c_r1D.size(1) == udd_vec.size(1)) &&
                            (r2D.size(0) == c_r1D.size(0)) && (i26 == i27)) {
                            int u_loop_ub;
                            A.set_size(r2D.size(0), r2D.size(1));
                            u_loop_ub = r2D.size(1);
                            for (int i28{0}; i28 < u_loop_ub; i28++) {
                                int g_scalarLB;
                                int g_vectorUB;
                                int i30;
                                int w_loop_ub;
                                w_loop_ub = r2D.size(0);
                                g_scalarLB = (r2D.size(0) / 2) << 1;
                                g_vectorUB = g_scalarLB - 2;
                                for (i30 = 0; i30 <= g_vectorUB; i30 += 2) {
                                    __m128d r8;
                                    __m128d r9;
                                    r8 = _mm_loadu_pd(&r2D[i30 + r2D.size(0) * i28]);
                                    r9 = _mm_loadu_pd(&c_r1D[i30 + c_r1D.size(0) * i28]);
                                    _mm_storeu_pd(
                                        &A[i30 + A.size(0) * i28],
                                        _mm_add_pd(_mm_mul_pd(r8, _mm_set1_pd(r2[i28])),
                                                   _mm_mul_pd(r9, _mm_set1_pd(udd_vec[i28]))));
                                }
                                for (i30 = g_scalarLB; i30 < w_loop_ub; i30++) {
                                    A[i30 + A.size(0) * i28] =
                                        r2D[i30 + r2D.size(0) * i28] * r2[i28] +
                                        c_r1D[i30 + c_r1D.size(0) * i28] * udd_vec[i28];
                                }
                            }
                        } else {
                            binary_expand_op(A, r2D, r2, c_r1D, udd_vec);
                        }
                        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec
                        // .* udd_vec + r1D .* uddd_vec;
                        r2.set_size(1, ud.size(1));
                        v_loop_ub = ud.size(1);
                        for (int i29{0}; i29 < v_loop_ub; i29++) {
                            double d_varargin_1;
                            d_varargin_1 = ud[i29];
                            r2[i29] = std::pow(d_varargin_1, 3.0);
                        }
                        if (r2D.size(1) == 1) {
                            i31 = ud.size(1);
                        } else {
                            i31 = r2D.size(1);
                        }
                        if (r3D.size(1) == 1) {
                            i32 = r2.size(1);
                        } else {
                            i32 = r3D.size(1);
                        }
                        if (r2D.size(1) == 1) {
                            i33 = ud.size(1);
                        } else {
                            i33 = r2D.size(1);
                        }
                        if (i33 == 1) {
                            i34 = udd_vec.size(1);
                        } else if (r2D.size(1) == 1) {
                            i34 = ud.size(1);
                        } else {
                            i34 = r2D.size(1);
                        }
                        if (r3D.size(0) == 1) {
                            i35 = r2D.size(0);
                        } else {
                            i35 = r3D.size(0);
                        }
                        if (r3D.size(1) == 1) {
                            i36 = r2.size(1);
                        } else {
                            i36 = r3D.size(1);
                        }
                        if (r2D.size(1) == 1) {
                            i37 = ud.size(1);
                        } else {
                            i37 = r2D.size(1);
                        }
                        if (i36 == 1) {
                            if (i37 == 1) {
                                i38 = udd_vec.size(1);
                            } else if (r2D.size(1) == 1) {
                                i38 = ud.size(1);
                            } else {
                                i38 = r2D.size(1);
                            }
                        } else if (r3D.size(1) == 1) {
                            i38 = r2.size(1);
                        } else {
                            i38 = r3D.size(1);
                        }
                        if (c_r1D.size(1) == 1) {
                            i39 = y.size(1);
                        } else {
                            i39 = c_r1D.size(1);
                        }
                        if ((r3D.size(1) == r2.size(1)) && (r2D.size(1) == ud.size(1)) &&
                            (i31 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) &&
                            (i32 == i34) && (c_r1D.size(1) == y.size(1)) &&
                            (i35 == c_r1D.size(0)) && (i38 == i39)) {
                            int x_loop_ub;
                            c_J.set_size(r3D.size(0), r3D.size(1));
                            x_loop_ub = r3D.size(1);
                            for (int i40{0}; i40 < x_loop_ub; i40++) {
                                int h_scalarLB;
                                int h_vectorUB;
                                int i41;
                                int y_loop_ub;
                                y_loop_ub = r3D.size(0);
                                h_scalarLB = (r3D.size(0) / 2) << 1;
                                h_vectorUB = h_scalarLB - 2;
                                for (i41 = 0; i41 <= h_vectorUB; i41 += 2) {
                                    __m128d r10;
                                    __m128d r11;
                                    __m128d r12;
                                    r10 = _mm_loadu_pd(&r3D[i41 + r3D.size(0) * i40]);
                                    r11 = _mm_loadu_pd(&r2D[i41 + r2D.size(0) * i40]);
                                    r12 = _mm_loadu_pd(&c_r1D[i41 + c_r1D.size(0) * i40]);
                                    _mm_storeu_pd(
                                        &c_J[i41 + c_J.size(0) * i40],
                                        _mm_add_pd(
                                            _mm_add_pd(
                                                _mm_mul_pd(r10, _mm_set1_pd(r2[i40])),
                                                _mm_mul_pd(
                                                    _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(3.0), r11),
                                                               _mm_set1_pd(ud[i40])),
                                                    _mm_set1_pd(udd_vec[i40]))),
                                            _mm_mul_pd(r12, _mm_set1_pd(jps))));
                                }
                                for (i41 = h_scalarLB; i41 < y_loop_ub; i41++) {
                                    c_J[i41 + c_J.size(0) * i40] =
                                        (r3D[i41 + r3D.size(0) * i40] * r2[i40] +
                                         3.0 * r2D[i41 + r2D.size(0) * i40] * ud[i40] *
                                             udd_vec[i40]) +
                                        c_r1D[i41 + c_r1D.size(0) * i40] * jps;
                                }
                            }
                        } else {
                            binary_expand_op(c_J, r3D, r2, r2D, ud, udd_vec, c_r1D, jps, uv);
                        }
                        // 'zeroSpeedCurv:81' [ r0D, r1D ]          = EvalCurvStruct( ctx, curv, u
                        // );
                        h_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart, ctx->cfg.maskRot,
                                         ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                         ctx->cfg.NCart, ctx->cfg.NRot, &curvE, b_u, b_r0D, c_r1D);
                        // 'zeroSpeedCurv:83' if( curv.Info.TRAFO )
                        if (!curvE.Info.TRAFO) {
                            int ab_loop_ub;
                            // 'zeroSpeedCurv:85' else
                            // 'zeroSpeedCurv:86' [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
                            e_r1D.set_size(c_r1D.size(0), c_r1D.size(1));
                            ab_loop_ub = c_r1D.size(1) - 1;
                            for (int i42{0}; i42 <= ab_loop_ub; i42++) {
                                int bb_loop_ub;
                                bb_loop_ub = c_r1D.size(0) - 1;
                                for (int i43{0}; i43 <= bb_loop_ub; i43++) {
                                    e_r1D[i43 + e_r1D.size(0) * i42] =
                                        c_r1D[i43 + c_r1D.size(0) * i42];
                                }
                            }
                            ctx->kin.v_relative(b_r0D, e_r1D, c_r1D);
                        } else {
                            // 'zeroSpeedCurv:84' r1D_r     = r1D;
                        }
                        // 'zeroSpeedCurv:89' safetyFactor = 0.5;
                        // 'zeroSpeedCurv:90' fmax =  curv.Info.FeedRate * safetyFactor;
                        // 'zeroSpeedCurv:91' vmax =  ctx.cfg.vmax( ctx.cfg.maskTot ).' *
                        // safetyFactor;
                        b_trueCount = 0;
                        for (int f_i{0}; f_i <= end_tmp; f_i++) {
                            if (ctx->cfg.maskTot.data[f_i]) {
                                b_trueCount++;
                            }
                        }
                        b_partialTrueCount = 0;
                        for (int g_i{0}; g_i <= end_tmp; g_i++) {
                            if (ctx->cfg.maskTot.data[g_i]) {
                                b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
                                b_partialTrueCount++;
                            }
                        }
                        for (int i44{0}; i44 < b_trueCount; i44++) {
                            vmax_data[i44] = ctx->cfg.vmax[b_tmp_data[i44] - 1] * 0.5;
                        }
                        // 'zeroSpeedCurv:92' amax =  ctx.cfg.amax( ctx.cfg.maskTot ).' *
                        // safetyFactor;
                        c_trueCount = 0;
                        for (int h_i{0}; h_i <= end_tmp; h_i++) {
                            if (ctx->cfg.maskTot.data[h_i]) {
                                c_trueCount++;
                            }
                        }
                        c_partialTrueCount = 0;
                        for (int i_i{0}; i_i <= end_tmp; i_i++) {
                            if (ctx->cfg.maskTot.data[i_i]) {
                                c_tmp_data[c_partialTrueCount] = static_cast<signed char>(i_i + 1);
                                c_partialTrueCount++;
                            }
                        }
                        for (int i45{0}; i45 < c_trueCount; i45++) {
                            amax_data[i45] = ctx->cfg.amax[c_tmp_data[i45] - 1] * 0.5;
                        }
                        // 'zeroSpeedCurv:93' jmax =  ctx.cfg.jmax( ctx.cfg.maskTot ).' *
                        // safetyFactor;
                        d_trueCount = 0;
                        for (int j_i{0}; j_i <= end_tmp; j_i++) {
                            if (ctx->cfg.maskTot.data[j_i]) {
                                d_trueCount++;
                            }
                        }
                        d_partialTrueCount = 0;
                        for (int k_i{0}; k_i <= end_tmp; k_i++) {
                            if (ctx->cfg.maskTot.data[k_i]) {
                                d_tmp_data[d_partialTrueCount] = static_cast<signed char>(k_i + 1);
                                d_partialTrueCount++;
                            }
                        }
                        for (int i46{0}; i46 < d_trueCount; i46++) {
                            jmax_data[i46] = ctx->cfg.jmax[d_tmp_data[i46] - 1] * 0.5;
                        }
                        // 'zeroSpeedCurv:95' feed  = vecnorm( r1D_r( ctx.cfg.indCart, : ) ) .* ud ;
                        cb_loop_ub = c_r1D.size(1);
                        f_r1D.set_size(ctx->cfg.indCart.size(0), c_r1D.size(1));
                        for (int i47{0}; i47 < cb_loop_ub; i47++) {
                            int db_loop_ub;
                            db_loop_ub = ctx->cfg.indCart.size(0);
                            for (int i48{0}; i48 < db_loop_ub; i48++) {
                                f_r1D[i48 + f_r1D.size(0) * i47] =
                                    c_r1D[(ctx->cfg.indCart[i48] + c_r1D.size(0) * i47) - 1];
                            }
                        }
                        coder::vecnorm(f_r1D, r2);
                        if (r2.size(1) == ud.size(1)) {
                            int eb_loop_ub;
                            int i49;
                            int i_scalarLB;
                            int i_vectorUB;
                            feed.set_size(1, r2.size(1));
                            eb_loop_ub = r2.size(1);
                            i_scalarLB = (r2.size(1) / 2) << 1;
                            i_vectorUB = i_scalarLB - 2;
                            for (i49 = 0; i49 <= i_vectorUB; i49 += 2) {
                                __m128d r13;
                                __m128d r14;
                                r13 = _mm_loadu_pd(&r2[i49]);
                                r14 = _mm_loadu_pd(&ud[i49]);
                                _mm_storeu_pd(&feed[i49], _mm_mul_pd(r13, r14));
                            }
                            for (i49 = i_scalarLB; i49 < eb_loop_ub; i49++) {
                                feed[i49] = r2[i49] * ud[i49];
                            }
                        } else {
                            times(feed, r2, ud);
                        }
                        // 'zeroSpeedCurv:97' if( any( feed > fmax ) )
                        b_feed.set_size(1, feed.size(1));
                        fb_loop_ub = feed.size(1);
                        for (int i50{0}; i50 < fb_loop_ub; i50++) {
                            b_feed[i50] = (feed[i50] > b_fmax);
                        }
                        b_y = false;
                        e_k = 0;
                        exitg1 = false;
                        while ((!exitg1) && (e_k <= b_feed.size(1) - 1)) {
                            if (b_feed[e_k]) {
                                b_y = true;
                                exitg1 = true;
                            } else {
                                e_k++;
                            }
                        }
                        if (b_y) {
                            int gb_loop_ub;
                            int i53;
                            int j_scalarLB;
                            int j_vectorUB;
                            // 'zeroSpeedCurv:98' [ f_delta, ind ] = max( feed - fmax );
                            c_feed.set_size(1, feed.size(1));
                            gb_loop_ub = feed.size(1);
                            j_scalarLB = (feed.size(1) / 2) << 1;
                            j_vectorUB = j_scalarLB - 2;
                            for (i53 = 0; i53 <= j_vectorUB; i53 += 2) {
                                __m128d r17;
                                r17 = _mm_loadu_pd(&feed[i53]);
                                _mm_storeu_pd(&c_feed[i53], _mm_sub_pd(r17, _mm_set1_pd(b_fmax)));
                            }
                            for (i53 = j_scalarLB; i53 < gb_loop_ub; i53++) {
                                c_feed[i53] = feed[i53] - b_fmax;
                            }
                            coder::internal::maximum(c_feed, &f_delta, &iindx);
                            // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - f_delta / feed(
                            // ind ) ) );
                            b_jps = jps * (1.0 - 0.9 * (1.0 - f_delta / feed[iindx - 1]));
                        } else {
                            int e_trueCount;
                            int h_k;
                            int hb_loop_ub;
                            int stride_0_0;
                            int stride_1_0;
                            bool c_y;
                            r15.set_size(V.size(0), V.size(1));
                            if ((V.size(0) != 0) && (V.size(1) != 0)) {
                                int i51;
                                i51 = V.size(1);
                                for (int f_k{0}; f_k < i51; f_k++) {
                                    int i52;
                                    i52 = r15.size(0);
                                    for (int g_k{0}; g_k < i52; g_k++) {
                                        r15[g_k + r15.size(0) * f_k] =
                                            std::abs(V[g_k + V.size(0) * f_k]);
                                    }
                                }
                            }
                            if (b_trueCount == 1) {
                                e_trueCount = r15.size(0);
                            } else {
                                e_trueCount = b_trueCount;
                            }
                            r16.set_size(e_trueCount, r15.size(1));
                            stride_0_0 = (r15.size(0) != 1);
                            stride_1_0 = (b_trueCount != 1);
                            hb_loop_ub = r15.size(1);
                            for (int i54{0}; i54 < hb_loop_ub; i54++) {
                                int ib_loop_ub;
                                if (b_trueCount == 1) {
                                    ib_loop_ub = r15.size(0);
                                } else {
                                    ib_loop_ub = b_trueCount;
                                }
                                for (int i55{0}; i55 < ib_loop_ub; i55++) {
                                    r16[i55 + r16.size(0) * i54] =
                                        (r15[i55 * stride_0_0 + r15.size(0) * i54] >
                                         vmax_data[i55 * stride_1_0]);
                                }
                            }
                            c_y = false;
                            h_k = 0;
                            exitg1 = false;
                            while ((!exitg1) && (h_k <= r16.size(0) * r16.size(1) - 1)) {
                                if (r16[h_k]) {
                                    c_y = true;
                                    exitg1 = true;
                                } else {
                                    h_k++;
                                }
                            }
                            if (c_y) {
                                // 'zeroSpeedCurv:100' elseif( any( abs( V ) > vmax, 'all' ) )
                                // 'zeroSpeedCurv:101' [ v_delta, ind ] = max( abs( V ) - vmax, [],
                                // 'all' );
                                if (r15.size(0) == b_trueCount) {
                                    int jb_loop_ub;
                                    int lb_loop_ub;
                                    r18.set_size(r15.size(0), r15.size(1));
                                    jb_loop_ub = r15.size(1);
                                    for (int i58{0}; i58 < jb_loop_ub; i58++) {
                                        int i61;
                                        int k_scalarLB;
                                        int k_vectorUB;
                                        int kb_loop_ub;
                                        kb_loop_ub = r15.size(0);
                                        k_scalarLB = (r15.size(0) / 2) << 1;
                                        k_vectorUB = k_scalarLB - 2;
                                        for (i61 = 0; i61 <= k_vectorUB; i61 += 2) {
                                            __m128d r19;
                                            __m128d r20;
                                            r19 = _mm_loadu_pd(&r15[i61 + r15.size(0) * i58]);
                                            r20 = _mm_loadu_pd(&vmax_data[i61]);
                                            _mm_storeu_pd(&r18[i61 + r18.size(0) * i58],
                                                          _mm_sub_pd(r19, r20));
                                        }
                                        for (i61 = k_scalarLB; i61 < kb_loop_ub; i61++) {
                                            r18[i61 + r18.size(0) * i58] =
                                                r15[i61 + r15.size(0) * i58] - vmax_data[i61];
                                        }
                                    }
                                    r15.set_size(r18.size(0), r18.size(1));
                                    lb_loop_ub = r18.size(1);
                                    for (int i59{0}; i59 < lb_loop_ub; i59++) {
                                        int nb_loop_ub;
                                        nb_loop_ub = r18.size(0);
                                        for (int i62{0}; i62 < nb_loop_ub; i62++) {
                                            r15[i62 + r15.size(0) * i59] =
                                                r18[i62 + r18.size(0) * i59];
                                        }
                                    }
                                    coder::internal::b_maximum(r15, &v_delta, &b_iindx);
                                } else {
                                    binary_expand_op(r15, vmax_data, &b_trueCount, &v_delta,
                                                     &b_iindx);
                                }
                                // 'zeroSpeedCurv:102' jps = jps * ( 1 - ratio * ( 1 - v_delta /
                                // abs( V( ind ) ) ) );
                                b_jps =
                                    jps * (1.0 - 0.9 * (1.0 - v_delta / std::abs(V[b_iindx - 1])));
                            } else {
                                int b_stride_0_0;
                                int b_stride_1_0;
                                int f_trueCount;
                                int k_k;
                                int mb_loop_ub;
                                bool d_y;
                                r15.set_size(A.size(0), A.size(1));
                                if ((A.size(0) != 0) && (A.size(1) != 0)) {
                                    int i56;
                                    i56 = A.size(1);
                                    for (int i_k{0}; i_k < i56; i_k++) {
                                        int i57;
                                        i57 = r15.size(0);
                                        for (int j_k{0}; j_k < i57; j_k++) {
                                            r15[j_k + r15.size(0) * i_k] =
                                                std::abs(A[j_k + A.size(0) * i_k]);
                                        }
                                    }
                                }
                                if (c_trueCount == 1) {
                                    f_trueCount = r15.size(0);
                                } else {
                                    f_trueCount = c_trueCount;
                                }
                                r16.set_size(f_trueCount, r15.size(1));
                                b_stride_0_0 = (r15.size(0) != 1);
                                b_stride_1_0 = (c_trueCount != 1);
                                mb_loop_ub = r15.size(1);
                                for (int i60{0}; i60 < mb_loop_ub; i60++) {
                                    int ob_loop_ub;
                                    if (c_trueCount == 1) {
                                        ob_loop_ub = r15.size(0);
                                    } else {
                                        ob_loop_ub = c_trueCount;
                                    }
                                    for (int i63{0}; i63 < ob_loop_ub; i63++) {
                                        r16[i63 + r16.size(0) * i60] =
                                            (r15[i63 * b_stride_0_0 + r15.size(0) * i60] >
                                             amax_data[i63 * b_stride_1_0]);
                                    }
                                }
                                d_y = false;
                                k_k = 0;
                                exitg1 = false;
                                while ((!exitg1) && (k_k <= r16.size(0) * r16.size(1) - 1)) {
                                    if (r16[k_k]) {
                                        d_y = true;
                                        exitg1 = true;
                                    } else {
                                        k_k++;
                                    }
                                }
                                if (d_y) {
                                    // 'zeroSpeedCurv:103' elseif( any( abs( A ) > amax, 'all' ) )
                                    // 'zeroSpeedCurv:104' [ a_delta, ind ] = max( abs( A ) - amax,
                                    // [], 'all' );
                                    if (r15.size(0) == c_trueCount) {
                                        int pb_loop_ub;
                                        int rb_loop_ub;
                                        r21.set_size(r15.size(0), r15.size(1));
                                        pb_loop_ub = r15.size(1);
                                        for (int i66{0}; i66 < pb_loop_ub; i66++) {
                                            int i69;
                                            int l_scalarLB;
                                            int l_vectorUB;
                                            int qb_loop_ub;
                                            qb_loop_ub = r15.size(0);
                                            l_scalarLB = (r15.size(0) / 2) << 1;
                                            l_vectorUB = l_scalarLB - 2;
                                            for (i69 = 0; i69 <= l_vectorUB; i69 += 2) {
                                                __m128d r22;
                                                __m128d r23;
                                                r22 = _mm_loadu_pd(&r15[i69 + r15.size(0) * i66]);
                                                r23 = _mm_loadu_pd(&amax_data[i69]);
                                                _mm_storeu_pd(&r21[i69 + r21.size(0) * i66],
                                                              _mm_sub_pd(r22, r23));
                                            }
                                            for (i69 = l_scalarLB; i69 < qb_loop_ub; i69++) {
                                                r21[i69 + r21.size(0) * i66] =
                                                    r15[i69 + r15.size(0) * i66] - amax_data[i69];
                                            }
                                        }
                                        r15.set_size(r21.size(0), r21.size(1));
                                        rb_loop_ub = r21.size(1);
                                        for (int i67{0}; i67 < rb_loop_ub; i67++) {
                                            int tb_loop_ub;
                                            tb_loop_ub = r21.size(0);
                                            for (int i70{0}; i70 < tb_loop_ub; i70++) {
                                                r15[i70 + r15.size(0) * i67] =
                                                    r21[i70 + r21.size(0) * i67];
                                            }
                                        }
                                        coder::internal::b_maximum(r15, &a_delta, &c_iindx);
                                    } else {
                                        binary_expand_op(r15, amax_data, &c_trueCount, &a_delta,
                                                         &c_iindx);
                                    }
                                    // 'zeroSpeedCurv:105' jps = jps * ( 1 - ratio * ( 1 - a_delta /
                                    // abs( A( ind ) ) ) );
                                    b_jps =
                                        jps *
                                        (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[c_iindx - 1])));
                                } else {
                                    int c_stride_0_0;
                                    int c_stride_1_0;
                                    int g_trueCount;
                                    int n_k;
                                    int sb_loop_ub;
                                    bool e_y;
                                    r15.set_size(c_J.size(0), c_J.size(1));
                                    if ((c_J.size(0) != 0) && (c_J.size(1) != 0)) {
                                        int i64;
                                        i64 = c_J.size(1);
                                        for (int l_k{0}; l_k < i64; l_k++) {
                                            int i65;
                                            i65 = r15.size(0);
                                            for (int m_k{0}; m_k < i65; m_k++) {
                                                r15[m_k + r15.size(0) * l_k] =
                                                    std::abs(c_J[m_k + c_J.size(0) * l_k]);
                                            }
                                        }
                                    }
                                    if (d_trueCount == 1) {
                                        g_trueCount = r15.size(0);
                                    } else {
                                        g_trueCount = d_trueCount;
                                    }
                                    r16.set_size(g_trueCount, r15.size(1));
                                    c_stride_0_0 = (r15.size(0) != 1);
                                    c_stride_1_0 = (d_trueCount != 1);
                                    sb_loop_ub = r15.size(1);
                                    for (int i68{0}; i68 < sb_loop_ub; i68++) {
                                        int ub_loop_ub;
                                        if (d_trueCount == 1) {
                                            ub_loop_ub = r15.size(0);
                                        } else {
                                            ub_loop_ub = d_trueCount;
                                        }
                                        for (int i71{0}; i71 < ub_loop_ub; i71++) {
                                            r16[i71 + r16.size(0) * i68] =
                                                (r15[i71 * c_stride_0_0 + r15.size(0) * i68] >
                                                 jmax_data[i71 * c_stride_1_0]);
                                        }
                                    }
                                    e_y = false;
                                    n_k = 0;
                                    exitg1 = false;
                                    while ((!exitg1) && (n_k <= r16.size(0) * r16.size(1) - 1)) {
                                        if (r16[n_k]) {
                                            e_y = true;
                                            exitg1 = true;
                                        } else {
                                            n_k++;
                                        }
                                    }
                                    if (e_y) {
                                        // 'zeroSpeedCurv:106' elseif( any( abs( J ) > jmax, 'all' )
                                        // ) 'zeroSpeedCurv:107' [ j_delta, ind ] = max( abs( J ) -
                                        // jmax, [], 'all' );
                                        if (r15.size(0) == d_trueCount) {
                                            int vb_loop_ub;
                                            int xb_loop_ub;
                                            r24.set_size(r15.size(0), r15.size(1));
                                            vb_loop_ub = r15.size(1);
                                            for (int i72{0}; i72 < vb_loop_ub; i72++) {
                                                int i74;
                                                int m_scalarLB;
                                                int m_vectorUB;
                                                int wb_loop_ub;
                                                wb_loop_ub = r15.size(0);
                                                m_scalarLB = (r15.size(0) / 2) << 1;
                                                m_vectorUB = m_scalarLB - 2;
                                                for (i74 = 0; i74 <= m_vectorUB; i74 += 2) {
                                                    __m128d r25;
                                                    __m128d r26;
                                                    r25 =
                                                        _mm_loadu_pd(&r15[i74 + r15.size(0) * i72]);
                                                    r26 = _mm_loadu_pd(&jmax_data[i74]);
                                                    _mm_storeu_pd(&r24[i74 + r24.size(0) * i72],
                                                                  _mm_sub_pd(r25, r26));
                                                }
                                                for (i74 = m_scalarLB; i74 < wb_loop_ub; i74++) {
                                                    r24[i74 + r24.size(0) * i72] =
                                                        r15[i74 + r15.size(0) * i72] -
                                                        jmax_data[i74];
                                                }
                                            }
                                            r15.set_size(r24.size(0), r24.size(1));
                                            xb_loop_ub = r24.size(1);
                                            for (int i73{0}; i73 < xb_loop_ub; i73++) {
                                                int yb_loop_ub;
                                                yb_loop_ub = r24.size(0);
                                                for (int i75{0}; i75 < yb_loop_ub; i75++) {
                                                    r15[i75 + r15.size(0) * i73] =
                                                        r24[i75 + r24.size(0) * i73];
                                                }
                                            }
                                            coder::internal::b_maximum(r15, &j_delta, &d_iindx);
                                        } else {
                                            binary_expand_op(r15, jmax_data, &d_trueCount, &j_delta,
                                                             &d_iindx);
                                        }
                                        // 'zeroSpeedCurv:108' jps = jps * ( 1 - ratio * ( 1 -
                                        // j_delta / abs( J( ind ) ) ) );
                                        b_jps =
                                            jps *
                                            (1.0 -
                                             0.9 * (1.0 - j_delta / std::abs(c_J[d_iindx - 1])));
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
                    // 'zeroSpeedCurv:41' [ u, ud, udd ]        = constJerkU( jps, k_vec *
                    // ctx.cfg.dt, isEnd );
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
                    // 'cutZeroEnd:14' curv2.ConstJerk         = jps;
                    curvE.ConstJerk = jps;
                    // 'cutZeroEnd:15' curv2.Info.zspdmode     = ZSpdMode.NZ;
                    curvE.Info.zspdmode = ZSpdMode_NZ;
                    // 'cutZeroEnd:17' curv1                   = curv;
                    // 'cutZeroEnd:18' curv1.a_param           = u - curv1.b_param;
                    curv.a_param = u - curv.b_param;
                    // 'cutZeroEnd:19' curv1.UseConstJerk      = false;
                    curv.UseConstJerk = false;
                    // 'cutZeroEnd:20' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
                    // 'cutZeroEnd:22' if( isAZeroStart( curv ) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if (curv.Info.zspdmode == ZSpdMode_ZZ) {
                        // 'isAZeroStart:6' zeroFlag = true;
                        // 'cutZeroEnd:23' curv1.Info.zspdmode = ZSpdMode.ZN;
                        curv.Info.zspdmode = ZSpdMode_ZN;
                    } else {
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'cutZeroEnd:24' else
                        // 'cutZeroEnd:25' curv1.Info.zspdmode = ZSpdMode.NN;
                        curv.Info.zspdmode = ZSpdMode_NN;
                    }
                    // 'cutZeroEnd:28' if( coder.target("MATLAB") )
                    // 'splitCurvStruct:26' hasEndSpeed     = true;
                    hasEndSpeed = true;
                } else {
                    // 'isAZeroEnd:9' zeroFlag = false;
                }
                // 'splitCurvStruct:29' L       = LengthCurv( ctx, curv, 0, 1 );
                L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, curv.Info, curv.R0,
                               curv.R1, curv.CorrectedHelixCenter, curv.evec, curv.theta,
                               curv.pitch, curv.CoeffP5, curv.sp_index, curv.a_param, curv.b_param);
                // 'splitCurvStruct:30' L_split = ctx.cfg.LSplit;
                //  Number of sub segments
                // 'splitCurvStruct:33' N = ceil( L / L_split );
                b_N = std::ceil(L / ctx->cfg.LSplit);
                //  Length of the sub segments
                // 'splitCurvStruct:36' L_split = L / N;
                L_split = L / b_N;
                //  Loop
                // 'splitCurvStruct:39' u0 = 0;
                // 'splitCurvStruct:41' for k = 1 : N - 1
                b_k = 0;
                exitg1 = false;
                while ((!exitg1) && (b_k <= static_cast<int>(b_N - 1.0) - 1)) {
                    double u1_tilda;
                    // 'splitCurvStruct:42' u1_tilda  = cutCurvStructU( ctx, curv, u0, L_split,
                    // false );
                    u1_tilda = cutCurvStructU(
                        &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                        ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart, ctx->cfg.indRot,
                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                        ctx->cfg.GaussLegendreW, &curv, L_split);
                    // 'splitCurvStruct:43' u1 = ( u1_tilda - curv.b_param ) / curv.a_param;
                    // 'splitCurvStruct:44' if( u1 < 1 )
                    if ((u1_tilda - curv.b_param) / curv.a_param < 1.0) {
                        // 'splitCurvStruct:45' curvSplited         = curv;
                        curvSplited = curv;
                        // 'splitCurvStruct:46' curvSplited.a_param = u1_tilda -
                        // curvSplited.b_param;
                        curvSplited.a_param = u1_tilda - curvSplited.b_param;
                        // 'splitCurvStruct:48' if( isAZeroStart( curvSplited ) )
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  curv  : The curve struct
                        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if (curvSplited.Info.zspdmode == ZSpdMode_ZN) {
                            // 'isAZeroStart:6' zeroFlag = true;
                            // 'splitCurvStruct:49' curvSplited.Info.zspdmode = ZSpdMode.ZN;
                            curvSplited.Info.zspdmode = ZSpdMode_ZN;
                        } else {
                            // 'isAZeroStart:8' zeroFlag = false;
                            // 'splitCurvStruct:50' else
                            // 'splitCurvStruct:51' curvSplited.Info.zspdmode = ZSpdMode.NN;
                            curvSplited.Info.zspdmode = ZSpdMode_NN;
                        }
                        // 'splitCurvStruct:54' curv.a_param        = curv.a_param  +
                        // curv.b_param... 'splitCurvStruct:55'                               -
                        // u1_tilda;
                        curv.a_param = (curv.a_param + curv.b_param) - u1_tilda;
                        // 'splitCurvStruct:56' curv.b_param        = u1_tilda;
                        curv.b_param = u1_tilda;
                        // 'splitCurvStruct:58' if( isAZeroEnd( curv ) )
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if (curv.Info.zspdmode == ZSpdMode_NZ) {
                            // 'isAZeroEnd:7' zeroFlag = true;
                            // 'splitCurvStruct:59' curv.Info.zspdmode = ZSpdMode.NZ;
                            curv.Info.zspdmode = ZSpdMode_NZ;
                        } else {
                            // 'isAZeroEnd:9' zeroFlag = false;
                            // 'splitCurvStruct:60' else
                            // 'splitCurvStruct:61' curv.Info.zspdmode = ZSpdMode.NN;
                            curv.Info.zspdmode = ZSpdMode_NN;
                        }
                        // 'splitCurvStruct:67' ctx.q_split.push( curvSplited );
                        ctx->q_split.push(&curvSplited);
                        b_k++;
                    } else {
                        // 'splitCurvStruct:63' else
                        exitg1 = true;
                    }
                }
                // 'splitCurvStruct:71' ctx.q_split.push( curv );
                ctx->q_split.push(&curv);
                // 'splitCurvStruct:73' if( hasEndSpeed )
                if (hasEndSpeed) {
                    //  cut zero End
                    // 'splitCurvStruct:75' ctx.q_split.push( curvE );
                    ctx->q_split.push(&curvE);
                }
            }
        }
    }
}

} // namespace ocn

//
// File trailer for splitQueue.cpp
//
// [EOF]
//
