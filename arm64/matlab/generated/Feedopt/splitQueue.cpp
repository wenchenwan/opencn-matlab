//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitQueue.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "splitQueue.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "calcRVAJfromUWithoutCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStructU.h"
#include "cutZeroEnd.h"
#include "minOrMax.h"
#include "norm.h"
#include "opencn_matlab_data.h"
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
#include <stdio.h>

// Function Definitions
//
// function ctx = splitQueue( ctx )
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void splitQueue(const FeedoptContext *ctx)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> J;
    ::coder::array<double, 2U> V;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_u;
    ::coder::array<double, 2U> k_vec;
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> ud_vec;
    ::coder::array<double, 2U> udd_vec;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> b_V;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 2U> b_x;
    ::coder::array<bool, 2U> x;
    CurvStruct b_curv;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    double amax_data[6];
    double jmax_data[6];
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double a_delta;
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double j_delta;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_spline_Ltot;
    double v_delta;
    unsigned long params_spline_Bl_handle;
    unsigned int uv[2];
    int b_iindx;
    int c_iindx;
    int iindx;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
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
            // 'DebugLog:6' fprintf(1, varargin{:});
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
            // 'DebugLog:6' fprintf(1, varargin{:});
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
                int i1;
                bool hasEndSpeed;
                // 'splitCurvStruct:16' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  curv  : The curve struct
                // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    CurvStruct c_curv;
                    double b_ex;
                    double d_ex;
                    double jps;
                    double u;
                    int b_last;
                    int last;
                    bool searchJps;
                    // 'isAZeroStart:6' zeroFlag = true;
                    //  cut zero Start
                    // 'splitCurvStruct:18' [ curvS, curv ] = cutZeroStart( ctx, curv );
                    //  cutZeroStart : Cut the start of the given to handle the zero speed.
                    // 'cutZeroStart:3' u  = cutCurvStructU( ctx, curv, 0, ctx.cfg.LSplitZero, false
                    // );
                    u = cutCurvStructU(
                        &ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                        ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                        ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                        ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, curv.Info.Type, curv.R0,
                        curv.R1, curv.CorrectedHelixCenter, curv.evec, curv.theta, curv.pitch,
                        curv.CoeffP5, curv.sp_index, curv.a_param, curv.b_param,
                        ctx->cfg.LSplitZero);
                    // 'cutZeroStart:5' if( u >= 1 )
                    if (u >= 1.0) {
                        // 'cutZeroStart:6' u = curv.a_param / 2 + curv.b_param;
                        u = curv.a_param / 2.0 + curv.b_param;
                    }
                    // 'cutZeroStart:9' curv1               = curv;
                    curvS = curv;
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
                    // 'zeroSpeedCurv:13' uk = 0;
                    // 'zeroSpeedCurv:15' if( isEnd )
                    // 'zeroSpeedCurv:17' [ ~, r1D ] = EvalCurvStruct( ctx, curv, uk );
                    c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                                     ctx->cfg.indRot.data, ctx->cfg.indRot.size[0],
                                     ctx->cfg.indTot.data, ctx->cfg.indTot.size[0], curvS.Info.Type,
                                     curvS.R0, curvS.R1, curvS.CorrectedHelixCenter, curvS.evec,
                                     curvS.theta, curvS.pitch, curvS.CoeffP5, curvS.sp_index,
                                     curvS.a_param, curvS.b_param, a__1, r1D);
                    //  Compute pseudo jerk based on max allowed jerk
                    // 'zeroSpeedCurv:20' jps = min( ctx.cfg.jmax( ctx.cfg.indTot ) ) / max( abs(
                    // r1D ) );
                    z1.set_size(r1D.size(0));
                    if (r1D.size(0) != 0) {
                        int i2;
                        i2 = r1D.size(0);
                        for (int c_k{0}; c_k < i2; c_k++) {
                            z1[c_k] = std::abs(r1D[c_k]);
                        }
                    }
                    last = ctx->cfg.indTot.size[0];
                    if (ctx->cfg.indTot.size[0] <= 2) {
                        if (ctx->cfg.indTot.size[0] == 1) {
                            b_ex = ctx->cfg.jmax[ctx->cfg.indTot.data[0] - 1];
                        } else {
                            double d1;
                            double d2;
                            d1 = ctx->cfg.jmax[ctx->cfg.indTot.data[0] - 1];
                            d2 = ctx->cfg
                                     .jmax[ctx->cfg.indTot.data[ctx->cfg.indTot.size[0] - 1] - 1];
                            if (d1 > d2) {
                                b_ex = d2;
                            } else {
                                b_ex = d1;
                            }
                        }
                    } else {
                        double ex;
                        ex = ctx->cfg.jmax[ctx->cfg.indTot.data[0] - 1];
                        for (int d_k{2}; d_k <= last; d_k++) {
                            double d3;
                            d3 = ctx->cfg.jmax[ctx->cfg.indTot.data[d_k - 1] - 1];
                            if (ex > d3) {
                                ex = d3;
                            }
                        }
                        b_ex = ex;
                    }
                    b_last = z1.size(0);
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
                        for (int e_k{2}; e_k <= b_last; e_k++) {
                            double d4;
                            d4 = z1[e_k - 1];
                            if (c_ex < d4) {
                                c_ex = d4;
                            }
                        }
                        d_ex = c_ex;
                    }
                    jps = b_ex / d_ex;
                    //  searchU   = true;
                    // while searchU
                    // 'zeroSpeedCurv:25' searchJps = true;
                    // 'zeroSpeedCurv:27' ind = 0;
                    // 'zeroSpeedCurv:28' while searchJps
                    uv[0] = 1U;
                    searchJps = true;
                    while (searchJps) {
                        double b_jps;
                        double f_k;
                        int b_end;
                        int b_loop_ub;
                        int c_loop_ub;
                        int d_loop_ub;
                        int e_loop_ub;
                        int end;
                        int f_loop_ub;
                        int g_k;
                        int g_loop_ub;
                        int i14;
                        int i15;
                        int i19;
                        int i20;
                        int i21;
                        int i22;
                        int i23;
                        int i24;
                        int i25;
                        int i26;
                        int i27;
                        int i_loop_ub;
                        int l_loop_ub;
                        int o_loop_ub;
                        int q_loop_ub;
                        int r_loop_ub;
                        bool b_y;
                        bool exitg1;
                        // 'zeroSpeedCurv:29' ind = ind + 1;
                        // 'zeroSpeedCurv:30' [ k_vec ]         = compute_k( jps, ctx.cfg.dt, 1 );
                        //  compute_k : Compute the vector of time steps required by the paramter u
                        //  to go from 0 to 1.
                        // 'zeroSpeedCurv:55' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
                        f_k = std::pow(6.0 / jps, 0.33333333333333331) / ctx->cfg.dt;
                        // 'zeroSpeedCurv:57' if( k > 0 )
                        if (f_k > 0.0) {
                            // 'zeroSpeedCurv:58' k_vec = 1 : k;
                            if (f_k < 1.0) {
                                k_vec.set_size(1, 0);
                            } else {
                                int loop_ub;
                                loop_ub = static_cast<int>(std::floor(f_k - 1.0));
                                k_vec.set_size(1, loop_ub + 1);
                                for (int i3{0}; i3 <= loop_ub; i3++) {
                                    k_vec[i3] = static_cast<double>(i3) + 1.0;
                                }
                            }
                            // 'zeroSpeedCurv:59' if( k_vec( end ) < k )
                            if (k_vec[k_vec.size(1) - 1] < f_k) {
                                int i4;
                                // 'zeroSpeedCurv:59' k_vec = [ k_vec, k ];
                                i4 = k_vec.size(1);
                                k_vec.set_size(k_vec.size(0), k_vec.size(1) + 1);
                                k_vec[i4] = f_k;
                            }
                        } else {
                            // 'zeroSpeedCurv:60' else
                            // 'zeroSpeedCurv:61' k_vec = 1;
                            k_vec.set_size(1, 1);
                            k_vec[0] = 1.0;
                        }
                        // 'zeroSpeedCurv:31' [ searchJps, jps] = calc_u( isEnd, searchJps, jps,
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
                        // 'zeroSpeedCurv:82' if( isempty( ratio ) )
                        // 'zeroSpeedCurv:84' [ u, ud, udd, uddd ]  = constJerkU( jps, k_vec *
                        // ctx.cfg.dt, isEnd );
                        y.set_size(1, k_vec.size(1));
                        b_loop_ub = k_vec.size(1);
                        for (int i5{0}; i5 < b_loop_ub; i5++) {
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
                        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                        r.set_size(1, y.size(1));
                        c_loop_ub = y.size(1);
                        for (int i6{0}; i6 < c_loop_ub; i6++) {
                            double varargin_1;
                            varargin_1 = y[i6];
                            r[i6] = std::pow(varargin_1, 3.0);
                        }
                        b_u.set_size(1, r.size(1));
                        d_loop_ub = r.size(1);
                        for (int i7{0}; i7 < d_loop_ub; i7++) {
                            b_u[i7] = jps * r[i7] / 6.0;
                        }
                        // 'constJerkU:33' u( u > 1 ) = 1;
                        end = b_u.size(1);
                        for (int b_i{0}; b_i < end; b_i++) {
                            if (b_u[b_i] > 1.0) {
                                b_u[b_i] = 1.0;
                            }
                        }
                        // 'constJerkU:34' u( u < 0 ) = 0;
                        b_end = b_u.size(1);
                        for (int c_i{0}; c_i < b_end; c_i++) {
                            if (b_u[c_i] < 0.0) {
                                b_u[c_i] = 0.0;
                            }
                        }
                        // 'constJerkU:36' if( isEnd )
                        // 'zeroSpeedCurv:86' [ ~, V, A, J ]        = calcRVAJfromU( ctx, curv, u,
                        // ud, udd, uddd );
                        r.set_size(1, y.size(1));
                        e_loop_ub = y.size(1);
                        for (int i8{0}; i8 < e_loop_ub; i8++) {
                            double b_varargin_1;
                            b_varargin_1 = y[i8];
                            r[i8] = std::pow(b_varargin_1, 2.0);
                        }
                        ud_vec.set_size(1, r.size(1));
                        f_loop_ub = r.size(1);
                        for (int i9{0}; i9 < f_loop_ub; i9++) {
                            ud_vec[i9] = jps * r[i9] / 2.0;
                        }
                        udd_vec.set_size(1, y.size(1));
                        g_loop_ub = y.size(1);
                        for (int i10{0}; i10 < g_loop_ub; i10++) {
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
                        // 'calcRVAJfromU:17' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv,
                        // u_vec );
                        b_EvalCurvStruct(
                            &ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                            ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                            ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                            curvS.Info.Type, curvS.R0, curvS.R1, curvS.CorrectedHelixCenter,
                            curvS.evec, curvS.theta, curvS.pitch, curvS.CoeffP5, curvS.sp_index,
                            curvS.a_param, curvS.b_param, b_u, a__2, b_r1D, r2D, r3D);
                        // 'calcRVAJfromU:18' [ R, V, A, J ]          = calcRVAJfromUWithoutCurv(
                        // ud_vec, ... 'calcRVAJfromU:19'                           udd_vec,
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
                        if (b_r1D.size(1) == ud_vec.size(1)) {
                            int h_loop_ub;
                            V.set_size(b_r1D.size(0), b_r1D.size(1));
                            h_loop_ub = b_r1D.size(1);
                            for (int i11{0}; i11 < h_loop_ub; i11++) {
                                int j_loop_ub;
                                j_loop_ub = b_r1D.size(0);
                                for (int i13{0}; i13 < j_loop_ub; i13++) {
                                    V[i13 + V.size(0) * i11] =
                                        b_r1D[i13 + b_r1D.size(0) * i11] * ud_vec[i11];
                                }
                            }
                        } else {
                            times(V, b_r1D, ud_vec);
                        }
                        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
                        r.set_size(1, ud_vec.size(1));
                        i_loop_ub = ud_vec.size(1);
                        for (int i12{0}; i12 < i_loop_ub; i12++) {
                            double c_varargin_1;
                            c_varargin_1 = ud_vec[i12];
                            r[i12] = std::pow(c_varargin_1, 2.0);
                        }
                        if (r2D.size(1) == 1) {
                            i14 = r.size(1);
                        } else {
                            i14 = r2D.size(1);
                        }
                        if (b_r1D.size(1) == 1) {
                            i15 = udd_vec.size(1);
                        } else {
                            i15 = b_r1D.size(1);
                        }
                        if ((r2D.size(1) == r.size(1)) && (b_r1D.size(1) == udd_vec.size(1)) &&
                            (r2D.size(0) == b_r1D.size(0)) && (i14 == i15)) {
                            int k_loop_ub;
                            A.set_size(r2D.size(0), r2D.size(1));
                            k_loop_ub = r2D.size(1);
                            for (int i16{0}; i16 < k_loop_ub; i16++) {
                                int m_loop_ub;
                                m_loop_ub = r2D.size(0);
                                for (int i18{0}; i18 < m_loop_ub; i18++) {
                                    A[i18 + A.size(0) * i16] =
                                        r2D[i18 + r2D.size(0) * i16] * r[i16] +
                                        b_r1D[i18 + b_r1D.size(0) * i16] * udd_vec[i16];
                                }
                            }
                        } else {
                            binary_expand_op(A, r2D, r, b_r1D, udd_vec);
                        }
                        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec
                        // .* udd_vec + r1D .* uddd_vec;
                        r.set_size(1, ud_vec.size(1));
                        l_loop_ub = ud_vec.size(1);
                        for (int i17{0}; i17 < l_loop_ub; i17++) {
                            double d_varargin_1;
                            d_varargin_1 = ud_vec[i17];
                            r[i17] = std::pow(d_varargin_1, 3.0);
                        }
                        if (r2D.size(1) == 1) {
                            i19 = ud_vec.size(1);
                        } else {
                            i19 = r2D.size(1);
                        }
                        if (r3D.size(1) == 1) {
                            i20 = r.size(1);
                        } else {
                            i20 = r3D.size(1);
                        }
                        if (r2D.size(1) == 1) {
                            i21 = ud_vec.size(1);
                        } else {
                            i21 = r2D.size(1);
                        }
                        if (i21 == 1) {
                            i22 = udd_vec.size(1);
                        } else if (r2D.size(1) == 1) {
                            i22 = ud_vec.size(1);
                        } else {
                            i22 = r2D.size(1);
                        }
                        if (r3D.size(0) == 1) {
                            i23 = r2D.size(0);
                        } else {
                            i23 = r3D.size(0);
                        }
                        if (r3D.size(1) == 1) {
                            i24 = r.size(1);
                        } else {
                            i24 = r3D.size(1);
                        }
                        if (r2D.size(1) == 1) {
                            i25 = ud_vec.size(1);
                        } else {
                            i25 = r2D.size(1);
                        }
                        if (i24 == 1) {
                            if (i25 == 1) {
                                i26 = udd_vec.size(1);
                            } else if (r2D.size(1) == 1) {
                                i26 = ud_vec.size(1);
                            } else {
                                i26 = r2D.size(1);
                            }
                        } else if (r3D.size(1) == 1) {
                            i26 = r.size(1);
                        } else {
                            i26 = r3D.size(1);
                        }
                        if (b_r1D.size(1) == 1) {
                            i27 = y.size(1);
                        } else {
                            i27 = b_r1D.size(1);
                        }
                        if ((r3D.size(1) == r.size(1)) && (r2D.size(1) == ud_vec.size(1)) &&
                            (i19 == udd_vec.size(1)) && (r3D.size(0) == r2D.size(0)) &&
                            (i20 == i22) && (b_r1D.size(1) == y.size(1)) &&
                            (i23 == b_r1D.size(0)) && (i26 == i27)) {
                            int n_loop_ub;
                            J.set_size(r3D.size(0), r3D.size(1));
                            n_loop_ub = r3D.size(1);
                            for (int i28{0}; i28 < n_loop_ub; i28++) {
                                int p_loop_ub;
                                p_loop_ub = r3D.size(0);
                                for (int i30{0}; i30 < p_loop_ub; i30++) {
                                    J[i30 + J.size(0) * i28] =
                                        (r3D[i30 + r3D.size(0) * i28] * r[i28] +
                                         3.0 * r2D[i30 + r2D.size(0) * i28] * ud_vec[i28] *
                                             udd_vec[i28]) +
                                        b_r1D[i30 + b_r1D.size(0) * i28] * jps;
                                }
                            }
                        } else {
                            binary_expand_op(J, r3D, r, r2D, ud_vec, udd_vec, b_r1D, jps, uv);
                        }
                        // 'zeroSpeedCurv:88' amax =  ctx.cfg.amax( ctx.cfg.indTot )';
                        o_loop_ub = ctx->cfg.indTot.size[0];
                        for (int i29{0}; i29 < o_loop_ub; i29++) {
                            amax_data[i29] = ctx->cfg.amax[ctx->cfg.indTot.data[i29] - 1];
                        }
                        // 'zeroSpeedCurv:89' jmax =  ctx.cfg.jmax( ctx.cfg.indTot )';
                        q_loop_ub = ctx->cfg.indTot.size[0];
                        for (int i31{0}; i31 < q_loop_ub; i31++) {
                            jmax_data[i31] = ctx->cfg.jmax[ctx->cfg.indTot.data[i31] - 1];
                        }
                        // 'zeroSpeedCurv:91' if( any( vecnorm( V ) > curv.Info.FeedRate ) )
                        coder::vecnorm(V, r);
                        x.set_size(1, r.size(1));
                        r_loop_ub = r.size(1);
                        for (int i32{0}; i32 < r_loop_ub; i32++) {
                            x[i32] = (r[i32] > curvS.Info.FeedRate);
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
                            int u_loop_ub;
                            // 'zeroSpeedCurv:92' [ v_delta, ind ] = max( vecnorm( V ) -
                            // curv.Info.FeedRate );
                            r.set_size(1, r.size(1));
                            s_loop_ub = r.size(1);
                            for (int i34{0}; i34 < s_loop_ub; i34++) {
                                r[i34] = r[i34] - curvS.Info.FeedRate;
                            }
                            coder::internal::maximum(r, &v_delta, &iindx);
                            // 'zeroSpeedCurv:93' jps = jps * ( 1 - ratio * ( 1 - v_delta / vecnorm(
                            // V( :, ind ) ) ) );
                            u_loop_ub = V.size(0);
                            b_V.set_size(V.size(0));
                            for (int i38{0}; i38 < u_loop_ub; i38++) {
                                b_V[i38] = V[i38 + V.size(0) * (iindx - 1)];
                            }
                            b_jps = jps * (1.0 - 0.9 * (1.0 - v_delta / coder::b_norm(b_V)));
                        } else {
                            int j_k;
                            bool c_y;
                            r1.set_size(A.size(0), A.size(1));
                            if ((A.size(0) != 0) && (A.size(1) != 0)) {
                                int i33;
                                i33 = A.size(1);
                                for (int h_k{0}; h_k < i33; h_k++) {
                                    int i35;
                                    i35 = r1.size(0);
                                    for (int i_k{0}; i_k < i35; i_k++) {
                                        r1[i_k + r1.size(0) * h_k] =
                                            std::abs(A[i_k + A.size(0) * h_k]);
                                    }
                                }
                            }
                            if (r1.size(0) == ctx->cfg.indTot.size[0]) {
                                int t_loop_ub;
                                b_x.set_size(r1.size(0), r1.size(1));
                                t_loop_ub = r1.size(1);
                                for (int i36{0}; i36 < t_loop_ub; i36++) {
                                    int v_loop_ub;
                                    v_loop_ub = r1.size(0);
                                    for (int i37{0}; i37 < v_loop_ub; i37++) {
                                        b_x[i37 + b_x.size(0) * i36] =
                                            (r1[i37 + r1.size(0) * i36] > amax_data[i37]);
                                    }
                                }
                            } else {
                                e_binary_expand_op(b_x, r1, amax_data, ctx);
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
                                // 'zeroSpeedCurv:94' elseif( any( abs( A ) > amax, 'all' ) )
                                // 'zeroSpeedCurv:95' [ a_delta, ind ] = max( abs( A ) - amax, [],
                                // 'all' );
                                if (r1.size(0) == ctx->cfg.indTot.size[0]) {
                                    int bb_loop_ub;
                                    int w_loop_ub;
                                    r2.set_size(r1.size(0), r1.size(1));
                                    w_loop_ub = r1.size(1);
                                    for (int i41{0}; i41 < w_loop_ub; i41++) {
                                        int y_loop_ub;
                                        y_loop_ub = r1.size(0);
                                        for (int i43{0}; i43 < y_loop_ub; i43++) {
                                            r2[i43 + r2.size(0) * i41] =
                                                r1[i43 + r1.size(0) * i41] - amax_data[i43];
                                        }
                                    }
                                    r1.set_size(r2.size(0), r2.size(1));
                                    bb_loop_ub = r2.size(1);
                                    for (int i45{0}; i45 < bb_loop_ub; i45++) {
                                        int cb_loop_ub;
                                        cb_loop_ub = r2.size(0);
                                        for (int i46{0}; i46 < cb_loop_ub; i46++) {
                                            r1[i46 + r1.size(0) * i45] = r2[i46 + r2.size(0) * i45];
                                        }
                                    }
                                    coder::internal::b_maximum(r1, &a_delta, &b_iindx);
                                } else {
                                    binary_expand_op(r1, amax_data, ctx, &a_delta, &b_iindx);
                                }
                                // 'zeroSpeedCurv:96' jps = jps * ( 1 - ratio * ( 1 - a_delta / abs(
                                // A( ind ) ) ) );
                                b_jps =
                                    jps * (1.0 - 0.9 * (1.0 - a_delta / std::abs(A[b_iindx - 1])));
                            } else {
                                int m_k;
                                bool d_y;
                                r1.set_size(J.size(0), J.size(1));
                                if ((J.size(0) != 0) && (J.size(1) != 0)) {
                                    int i39;
                                    i39 = J.size(1);
                                    for (int k_k{0}; k_k < i39; k_k++) {
                                        int i40;
                                        i40 = r1.size(0);
                                        for (int l_k{0}; l_k < i40; l_k++) {
                                            r1[l_k + r1.size(0) * k_k] =
                                                std::abs(J[l_k + J.size(0) * k_k]);
                                        }
                                    }
                                }
                                if (r1.size(0) == ctx->cfg.indTot.size[0]) {
                                    int x_loop_ub;
                                    b_x.set_size(r1.size(0), r1.size(1));
                                    x_loop_ub = r1.size(1);
                                    for (int i42{0}; i42 < x_loop_ub; i42++) {
                                        int ab_loop_ub;
                                        ab_loop_ub = r1.size(0);
                                        for (int i44{0}; i44 < ab_loop_ub; i44++) {
                                            b_x[i44 + b_x.size(0) * i42] =
                                                (r1[i44 + r1.size(0) * i42] > jmax_data[i44]);
                                        }
                                    }
                                } else {
                                    e_binary_expand_op(b_x, r1, jmax_data, ctx);
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
                                    // 'zeroSpeedCurv:97' elseif( any( abs( J ) > jmax, 'all' ) )
                                    // 'zeroSpeedCurv:98' [ j_delta, ind ] = max( abs( J ) - jmax,
                                    // [], 'all' );
                                    if (r1.size(0) == ctx->cfg.indTot.size[0]) {
                                        int db_loop_ub;
                                        int fb_loop_ub;
                                        r3.set_size(r1.size(0), r1.size(1));
                                        db_loop_ub = r1.size(1);
                                        for (int i47{0}; i47 < db_loop_ub; i47++) {
                                            int eb_loop_ub;
                                            eb_loop_ub = r1.size(0);
                                            for (int i48{0}; i48 < eb_loop_ub; i48++) {
                                                r3[i48 + r3.size(0) * i47] =
                                                    r1[i48 + r1.size(0) * i47] - jmax_data[i48];
                                            }
                                        }
                                        r1.set_size(r3.size(0), r3.size(1));
                                        fb_loop_ub = r3.size(1);
                                        for (int i49{0}; i49 < fb_loop_ub; i49++) {
                                            int gb_loop_ub;
                                            gb_loop_ub = r3.size(0);
                                            for (int i50{0}; i50 < gb_loop_ub; i50++) {
                                                r1[i50 + r1.size(0) * i49] =
                                                    r3[i50 + r3.size(0) * i49];
                                            }
                                        }
                                        coder::internal::b_maximum(r1, &j_delta, &c_iindx);
                                    } else {
                                        binary_expand_op(r1, jmax_data, ctx, &j_delta, &c_iindx);
                                    }
                                    // 'zeroSpeedCurv:99' jps = jps * ( 1 - ratio * ( 1 - j_delta /
                                    // abs( J( ind ) ) ) );
                                    b_jps =
                                        jps *
                                        (1.0 - 0.9 * (1.0 - j_delta / std::abs(J[c_iindx - 1])));
                                } else {
                                    // 'zeroSpeedCurv:100' else
                                    // 'zeroSpeedCurv:101' searchJps = false;
                                    searchJps = false;
                                }
                            }
                        }
                        jps = b_jps;
                    }
                    // 'zeroSpeedCurv:33' jps = jps /2;
                    jps /= 2.0;
                    // 'zeroSpeedCurv:34' [ k_vec ]             = compute_k( jps, ctx.cfg.dt, 1 );
                    //  compute_k : Compute the vector of time steps required by the paramter u to
                    //  go from 0 to 1.
                    // 'zeroSpeedCurv:55' k       = ( 6 * uk / jps )^( 1 / 3 ) / dt;
                    // 'zeroSpeedCurv:57' if( k > 0 )
                    // 'zeroSpeedCurv:35' [ u, ud, udd ]        = constJerkU( jps, k_vec *
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
                    //  Compute u and its derivatives based on constant jerk
                    // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
                    // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
                    // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
                    // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                    // 'constJerkU:33' u( u > 1 ) = 1;
                    // 'constJerkU:34' u( u < 0 ) = 0;
                    // 'constJerkU:36' if( isEnd )
                    //  [ k ]               = computeContinuityMat( ctx, curv, u, ud, udd, isEnd );
                    //
                    //  if( k > 1 )
                    //      u   = u( k );
                    //      ud  = ud( k );
                    //      udd = udd( k );
                    //      break;
                    //  else
                    //      jps = jps / 2;
                    //  end
                    //
                    //  end
                    // 'cutZeroStart:13' curv1.ConstJerk     = jps;
                    curvS.ConstJerk = jps;
                    // 'cutZeroStart:14' curv1.Info.zspdmode = ZSpdMode.ZN;
                    curvS.Info.zspdmode = ZSpdMode_ZN;
                    // 'cutZeroStart:15' curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
                    curvS.Info.gcode_source_line = curv.Info.gcode_source_line;
                    // 'cutZeroStart:17' curv2               = curv;
                    c_curv = curv;
                    // 'cutZeroStart:18' curv2.UseConstJerk  = false;
                    c_curv.UseConstJerk = false;
                    // 'cutZeroStart:19' curv2.b_param       = u;
                    c_curv.b_param = u;
                    // 'cutZeroStart:20' curv2.a_param       = curv.a_param  + curv.b_param -
                    // curv2.b_param;
                    c_curv.a_param = (curv.a_param + curv.b_param) - u;
                    // 'cutZeroStart:22' if( isAZeroEnd( curv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                        (curv.Info.zspdmode == ZSpdMode_ZZ)) {
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
                    curv = c_curv;
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
                if (curv.Info.zspdmode == ZSpdMode_NZ) {
                    // 'isAZeroEnd:7' zeroFlag = true;
                    //  cut zero End
                    // 'splitCurvStruct:25' [ curv, curvE ] = cutZeroEnd( ctx, curv );
                    b_curv = curv;
                    cutZeroEnd(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                               ctx->cfg.indRot.data, ctx->cfg.indRot.size[0], ctx->cfg.indTot.data,
                               ctx->cfg.indTot.size[0], ctx->cfg.amax, ctx->cfg.jmax,
                               ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                               ctx->cfg.GaussLegendreW, &b_curv, &curv, &curvE);
                    // 'splitCurvStruct:26' hasEndSpeed     = true;
                    hasEndSpeed = true;
                } else {
                    // 'isAZeroEnd:9' zeroFlag = false;
                }
                // 'splitCurvStruct:29' L       = LengthCurv( ctx, curv, 0, 1 );
                L = LengthCurv(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.indCart.data, ctx->cfg.indCart.size[0],
                               ctx->cfg.indRot.data, ctx->cfg.indRot.size[0], ctx->cfg.indTot.data,
                               ctx->cfg.indTot.size[0], ctx->cfg.GaussLegendreX,
                               ctx->cfg.GaussLegendreW, curv.Info.Type, curv.R0, curv.R1,
                               curv.CorrectedHelixCenter, curv.evec, curv.theta, curv.pitch,
                               curv.CoeffP5, curv.sp_index, curv.a_param, curv.b_param);
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
                i1 = static_cast<int>(b_N - 1.0);
                for (int b_k{0}; b_k < i1; b_k++) {
                    double d;
                    double u1_tilda;
                    // 'splitCurvStruct:42' u1_tilda  = cutCurvStructU( ctx, curv, u0, L_split,
                    // false );
                    u1_tilda = cutCurvStructU(
                        &ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                        ctx->cfg.indCart.data, ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                        ctx->cfg.indRot.size[0], ctx->cfg.indTot.data, ctx->cfg.indTot.size[0],
                        ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, curv.Info.Type, curv.R0,
                        curv.R1, curv.CorrectedHelixCenter, curv.evec, curv.theta, curv.pitch,
                        curv.CoeffP5, curv.sp_index, curv.a_param, curv.b_param, L_split);
                    // 'splitCurvStruct:43' u1 = ( u1_tilda - curv.b_param ) / curv.a_param;
                    // 'splitCurvStruct:45' if( u1 < 1 )
                    d = u1_tilda - curv.b_param;
                    if (d / curv.a_param < 1.0) {
                        // 'splitCurvStruct:46' curvSplited         = curv;
                        curvSplited = curv;
                        // 'splitCurvStruct:47' curvSplited.a_param = u1_tilda -
                        // curvSplited.b_param;
                        curvSplited.a_param = d;
                        // 'splitCurvStruct:49' if( isAZeroStart( curvSplited ) )
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  curv  : The curve struct
                        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if ((curv.Info.zspdmode == ZSpdMode_ZN) ||
                            (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:6' zeroFlag = true;
                            // 'splitCurvStruct:50' curvSplited.Info.zspdmode = ZSpdMode.ZN;
                            curvSplited.Info.zspdmode = ZSpdMode_ZN;
                        } else {
                            // 'isAZeroStart:8' zeroFlag = false;
                            // 'splitCurvStruct:51' else
                            // 'splitCurvStruct:52' curvSplited.Info.zspdmode = ZSpdMode.NN;
                            curvSplited.Info.zspdmode = ZSpdMode_NN;
                        }
                        // 'splitCurvStruct:55' curv.a_param        = curv.a_param  + curv.b_param -
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
                        if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                            (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroEnd:7' zeroFlag = true;
                            // 'splitCurvStruct:59' curv.Info.zspdmode = ZSpdMode.NZ;
                            curv.Info.zspdmode = ZSpdMode_NZ;
                        } else {
                            // 'isAZeroEnd:9' zeroFlag = false;
                            // 'splitCurvStruct:60' else
                            // 'splitCurvStruct:61' curv.Info.zspdmode = ZSpdMode.NN;
                            curv.Info.zspdmode = ZSpdMode_NN;
                        }
                    } else {
                        // 'splitCurvStruct:63' else
                        // 'splitCurvStruct:64' curvSplited         = curv;
                        curvSplited = curv;
                    }
                    // 'splitCurvStruct:67' ctx.q_split.push( curvSplited );
                    ctx->q_split.push(&curvSplited);
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
