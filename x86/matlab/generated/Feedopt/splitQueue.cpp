
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitQueue.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "splitQueue.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "TransP5LengthApprox.h"
#include "constrCurvStruct.h"
#include "cutCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "splineLength.h"
#include "sum.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function ctx = splitQueue( ctx )
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void splitQueue(b_FeedoptContext *ctx)
{
    Kinematics b_ctx;
    Kinematics c_ctx;
    Kinematics d_ctx;
    Kinematics e_ctx;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    ::coder::array<double, 2U> b_a__1;
    ::coder::array<double, 2U> b_a__2;
    ::coder::array<double, 2U> b_a__3;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> a__3;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    Axes params_tool_offset;
    CurvStruct b_curv;
    CurvStruct b_curvE;
    CurvStruct b_curvS;
    CurvStruct c_curv;
    CurvStruct c_curvS;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    CurvStruct d_curv;
    CurvStruct e_expl_temp;
    CurvStruct f_expl_temp;
    SplineStruct params_spline;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double L;
    double b_L;
    double b_expl_temp;
    double b_ret;
    double c_L;
    double c_expl_temp;
    double c_ret;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    double ret;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    bool hasEndSpeed;
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
        // 'splitQueue:4' ctx.k0 = int32( 1 );
        ctx->k0 = 1;
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
        if (static_cast<int>(N) - 1 >= 0) {
            paramsDefaultCurv(
                &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                &params_tool_backangle, &params_tool_orientation, &params_spline, params_R0,
                params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp, &c_expl_temp,
                params_CoeffP5, &d_expl_temp);
        }
        for (int k{0}; k < i; k++) {
            // 'splitQueue:12' ctx.k0  = ctx.k0 + 1;
            ctx->k0++;
            // 'splitQueue:13' if(coder.target("MATLAB"))
            // 'splitQueue:15' ctx     = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
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
            // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool,
            // ... 'constrCurvStructType:14'         params.spline, params.R0, params.R1,
            // params.Cprim, ... 'constrCurvStructType:15'         params.delta, params.evec,
            // params.theta, params.pitch, ... 'constrCurvStructType:16'         params.CoeffP5,
            // params.Coeff );
            b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                               params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                               params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                               params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                               params_gcodeInfoStruct_G91_1, params_tool_toolno,
                               params_tool_pocketno, &params_tool_offset, params_tool_diameter,
                               params_tool_frontangle, params_tool_backangle,
                               params_tool_orientation, &params_spline, params_R0, params_R1,
                               params_Cprim, params_evec, params_CoeffP5, &curvE);
            // 'splitCurvStruct:12' if ( curv.Info.Type == CurveType.TransP5 )
            if (curv.Info.Type == CurveType_TransP5) {
                // 'splitCurvStruct:13' ctx.q_split.push( curv );
                ctx->q_split.push(&curv);
            } else {
                bool guard1;
                bool guard2;
                bool zeroFlag;
                // 'splitCurvStruct:16' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroStart:6' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                // 'getZspdmode:3' error = false;
                // 'getZspdmode:5' if( isenum( speed ) )
                // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                // 'isAZeroStart:10' if( error )
                // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:14' zeroFlag = true;
                    zeroFlag = true;
                }
                guard1 = false;
                guard2 = false;
                if (zeroFlag) {
                    double Lcut;
                    //  cut zero Start
                    // 'splitCurvStruct:18' [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
                    //  cutZeroStart : Cut the start of the given to handle the zero speed.
                    //  u  = cutCurvStructU( ctx, curv, 0, ctx.cfg.LSplitZero, false );
                    // 'cutZeroStart:5' L       = LengthCurv( ctx, curv, 0, 1 );
                    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type
                    // == CurveType.Line )
                    if ((curv.Info.Type == CurveType_Helix) || (curv.Info.Type == CurveType_Line)) {
                        int loop_ub;
                        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                        c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv,
                                         a__1, r1D, a__2, a__3);
                        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        loop_ub = r1D.size(0);
                        r.set_size(r1D.size(0));
                        for (int i1{0}; i1 < loop_ub; i1++) {
                            double varargin_1;
                            varargin_1 = r1D[i1];
                            r[i1] = std::pow(varargin_1, 2.0);
                        }
                        b_L = std::sqrt(coder::sum(r));
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                    } else if (curv.Info.Type == CurveType_Spline) {
                        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                        // 'LengthCurv:7' a        = curv.a_param;
                        // 'LengthCurv:8' b        = curv.b_param;
                        // 'LengthCurv:9' u0_tilda = a * u0 + b;
                        // 'LengthCurv:10' u1_tilda = a * u1 + b;
                        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                        ctx->q_spline.get(curv.sp_index, &e_expl_temp);
                        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda,
                        // u1_tilda );
                        b_L = splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                           e_expl_temp.sp.Bl.handle, e_expl_temp.sp.Bl.order,
                                           e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                           e_expl_temp.sp.Lk, curv.b_param,
                                           curv.a_param + curv.b_param);
                    } else {
                        // 'LengthCurv:15' else
                        // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV",
                        // mfilename );
                    }
                    // 'cutZeroStart:6' Lcut    = ctx.cfg.LSplitZero;
                    Lcut = ctx->cfg.LSplitZero;
                    // 'cutZeroStart:8' if( Lcut > L / 3 )
                    if (ctx->cfg.LSplitZero > b_L / 3.0) {
                        // 'cutZeroStart:9' Lcut = L / 3;
                        Lcut = b_L / 3.0;
                    }
                    // 'cutZeroStart:12' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 0, Lcut,
                    // false );
                    cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                  ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  &curv, Lcut, &ret, &curvS, &b_curv);
                    // 'cutZeroStart:14' if( ret < 0 )
                    if (ret < 0.0) {
                        // 'cutZeroStart:15' curv1                   = curv;
                        curvS = curv;
                        // 'cutZeroStart:16' curv1.UseConstJerk      = true;
                        curvS.UseConstJerk = true;
                        // 'cutZeroStart:17' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
                        // false );
                        b_ctx = ctx->kin;
                        b_curvS = curvS;
                        zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                      ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                      ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax,
                                      ctx->cfg.jmax, ctx->cfg.dt, &b_ctx, &b_curvS, b_a__1, b_a__2,
                                      b_a__3, &curvS.ConstJerk);
                        // 'cutZeroStart:18' curv1.ConstJerk         = jps;
                    } else {
                        // 'cutZeroStart:19' else
                        // 'cutZeroStart:20' ocn_assert( check_curv_length( ctx, curv1, Lcut ),
                        // "Curve Length not valide", mfilename ); 'calcTransition:96' tol = 1E-3;
                        // 'calcTransition:98' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L )
                        // <= tol ); 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || (
                        // curv.Info.Type == CurveType.Line )
                        if ((curvS.Info.Type == CurveType_Helix) ||
                            (curvS.Info.Type == CurveType_Line)) {
                            // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                            c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &curvS, a__1, r1D, a__2, a__3);
                            // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                            // 'MyNorm:2' coder.inline('always');
                            // 'MyNorm:3' n = mysqrt(sum(x.^2));
                            // 'mysqrt:3' y = sqrt(x);
                            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                            sqrt_calls++;
                        } else if (curvS.Info.Type == CurveType_Spline) {
                            int g_loop_ub;
                            int k_loop_ub;
                            int n_loop_ub;
                            // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                            // 'LengthCurv:7' a        = curv.a_param;
                            // 'LengthCurv:8' b        = curv.b_param;
                            // 'LengthCurv:9' u0_tilda = a * u0 + b;
                            // 'LengthCurv:10' u1_tilda = a * u1 + b;
                            // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                            ctx->q_spline.get(curvS.sp_index, &f_expl_temp);
                            e_expl_temp.sp.coeff.set_size(f_expl_temp.sp.coeff.size(0),
                                                          f_expl_temp.sp.coeff.size(1));
                            g_loop_ub = f_expl_temp.sp.coeff.size(1);
                            for (int i7{0}; i7 < g_loop_ub; i7++) {
                                int i_loop_ub;
                                i_loop_ub = f_expl_temp.sp.coeff.size(0);
                                for (int i9{0}; i9 < i_loop_ub; i9++) {
                                    e_expl_temp.sp.coeff[i9 + e_expl_temp.sp.coeff.size(0) * i7] =
                                        f_expl_temp.sp
                                            .coeff[i9 + f_expl_temp.sp.coeff.size(0) * i7];
                                }
                            }
                            e_expl_temp.sp.knots.set_size(1, f_expl_temp.sp.knots.size(1));
                            k_loop_ub = f_expl_temp.sp.knots.size(1);
                            for (int i11{0}; i11 < k_loop_ub; i11++) {
                                e_expl_temp.sp.knots[i11] = f_expl_temp.sp.knots[i11];
                            }
                            e_expl_temp.sp.Lk.set_size(1, f_expl_temp.sp.Lk.size(1));
                            n_loop_ub = f_expl_temp.sp.Lk.size(1);
                            for (int i14{0}; i14 < n_loop_ub; i14++) {
                                e_expl_temp.sp.Lk[i14] = f_expl_temp.sp.Lk[i14];
                            }
                            // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda,
                            // u1_tilda );
                            splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                         f_expl_temp.sp.Bl.handle, f_expl_temp.sp.Bl.order,
                                         e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                         e_expl_temp.sp.Lk, curvS.b_param,
                                         curvS.a_param + curvS.b_param);
                        } else if (curvS.Info.Type == CurveType_TransP5) {
                            // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
                            // 'LengthCurv:14' L = TransP5LengthApprox( curv );
                            TransP5LengthApprox(&curvS);
                        } else {
                            // 'LengthCurv:15' else
                            // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV",
                            // mfilename );
                        }
                        // 'cutZeroStart:21' curv1.UseConstJerk      = true;
                        curvS.UseConstJerk = true;
                        // 'cutZeroStart:22' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
                        // false );
                        c_ctx = ctx->kin;
                        c_curvS = curvS;
                        zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                      ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                      ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax,
                                      ctx->cfg.jmax, ctx->cfg.dt, &c_ctx, &c_curvS, a__4, a__5,
                                      a__6, &curvS.ConstJerk);
                        // 'cutZeroStart:23' curv1.ConstJerk         = jps;
                        // 'cutZeroStart:24' curv2.UseConstJerk      = false;
                        b_curv.UseConstJerk = false;
                        // 'cutZeroStart:25' check_continuity( ctx, curv, curv1, curv2 );
                        // 'cutZeroStart:58' curv_vec    = [ curv; curv1; curv2 ];
                        // 'cutZeroStart:59' u_vec       = [ 0, 1 ];
                        // 'cutZeroStart:60' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2,
                        // 3 ); 'cutZeroStart:61' rd          = r; 'cutZeroStart:62' rdd         =
                        // r; 'cutZeroStart:64' for j = 1 : 3 'cutZeroStart:65' [ r( :, :, j ) , rd(
                        // :, :, j ), rdd( :, :, j ) ] = ... 'cutZeroStart:66' EvalCurvStruct( ctx,
                        // curv_vec( j ),  u_vec );
                        j_EvalCurvStruct(
                            &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv, r1, r2, r3);
                        // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                        // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                        // curv_vec( j ).a_param^2; 'cutZeroStart:65' [ r( :, :, j ) , rd( :, :, j
                        // ), rdd( :, :, j ) ] = ... 'cutZeroStart:66'         EvalCurvStruct( ctx,
                        // curv_vec( j ),  u_vec );
                        j_EvalCurvStruct(
                            &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curvS, r1, r2, r3);
                        // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                        // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                        // curv_vec( j ).a_param^2; 'cutZeroStart:65' [ r( :, :, j ) , rd( :, :, j
                        // ), rdd( :, :, j ) ] = ... 'cutZeroStart:66'         EvalCurvStruct( ctx,
                        // curv_vec( j ),  u_vec );
                        j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                         &b_curv, r1, r2, r3);
                        // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                        // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                        // curv_vec( j ).a_param^2; 'cutZeroStart:72' ind1 = [ 1, 1; 1, 2; 2, 2 ];
                        // 'cutZeroStart:73' ind2 = [ 2, 1; 3, 2; 3, 1 ];
                        // 'cutZeroStart:75' for j = 1 : 3
                    }
                    //      if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
                    //          u = curv.a_param / 2 + curv.b_param;
                    //      end
                    //      curv1               = curv;
                    //      curv1.a_param       = u -curv1.b_param;
                    //  curv1.UseConstJerk  = true;
                    //  [ ~, ~, ~, jps ]    = zeroSpeedCurv( ctx, curv1, false );
                    //  curv1.ConstJerk     = jps;
                    //      curv1.Info.zspdmode = ZSpdMode.ZN;
                    //      curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
                    //      curv2               = curv;
                    //  curv2.UseConstJerk  = false;
                    //      curv2.b_param       = u;
                    //      curv2.a_param       = curv.a_param  + curv.b_param - curv2.b_param;
                    //
                    //      if( isAZeroEnd( curv ) )
                    //          curv2.Info.zspdmode = ZSpdMode.NZ;
                    //      else
                    //          curv2.Info.zspdmode = ZSpdMode.NN;
                    //      end
                    //  if( coder.target("MATLAB") )
                    //      check_continuity( ctx, curv, curv1, curv2 );
                    //  end
                    curv = b_curv;
                    // 'splitCurvStruct:19' ctx.q_split.push( curvS );
                    ctx->q_split.push(&curvS);
                    // 'splitCurvStruct:20' if( ret < 0 )
                    if (ret >= 0.0) {
                        guard2 = true;
                    }
                } else {
                    guard2 = true;
                }
                if (guard2) {
                    bool b_zeroFlag;
                    // 'splitCurvStruct:23' hasEndSpeed = false;
                    hasEndSpeed = false;
                    // 'splitCurvStruct:24' if( isAZeroEnd( curv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroEnd:6' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:10' if( error )
                    // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                    if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                        (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:14' zeroFlag = true;
                        b_zeroFlag = true;
                    }
                    if (b_zeroFlag) {
                        double b_Lcut;
                        //  cut zero End
                        // 'splitCurvStruct:26' [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
                        //  cutZeroEnd : Cut the end of the given to handle the zero speed.
                        //  u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
                        // 'cutZeroEnd:5' L       = LengthCurv( ctx, curv, 0, 1 );
                        // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || (
                        // curv.Info.Type == CurveType.Line )
                        if ((curv.Info.Type == CurveType_Helix) ||
                            (curv.Info.Type == CurveType_Line)) {
                            int h_loop_ub;
                            // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                            c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &curv, a__1, r1D, a__2, a__3);
                            // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                            // 'MyNorm:2' coder.inline('always');
                            // 'MyNorm:3' n = mysqrt(sum(x.^2));
                            // 'mysqrt:3' y = sqrt(x);
                            h_loop_ub = r1D.size(0);
                            r.set_size(r1D.size(0));
                            for (int i8{0}; i8 < h_loop_ub; i8++) {
                                double c_varargin_1;
                                c_varargin_1 = r1D[i8];
                                r[i8] = std::pow(c_varargin_1, 2.0);
                            }
                            c_L = std::sqrt(coder::sum(r));
                            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                            sqrt_calls++;
                        } else if (curv.Info.Type == CurveType_Spline) {
                            int j_loop_ub;
                            int m_loop_ub;
                            int p_loop_ub;
                            // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                            // 'LengthCurv:7' a        = curv.a_param;
                            // 'LengthCurv:8' b        = curv.b_param;
                            // 'LengthCurv:9' u0_tilda = a * u0 + b;
                            // 'LengthCurv:10' u1_tilda = a * u1 + b;
                            // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                            ctx->q_spline.get(curv.sp_index, &f_expl_temp);
                            e_expl_temp.sp.coeff.set_size(f_expl_temp.sp.coeff.size(0),
                                                          f_expl_temp.sp.coeff.size(1));
                            j_loop_ub = f_expl_temp.sp.coeff.size(1);
                            for (int i10{0}; i10 < j_loop_ub; i10++) {
                                int l_loop_ub;
                                l_loop_ub = f_expl_temp.sp.coeff.size(0);
                                for (int i12{0}; i12 < l_loop_ub; i12++) {
                                    e_expl_temp.sp.coeff[i12 + e_expl_temp.sp.coeff.size(0) * i10] =
                                        f_expl_temp.sp
                                            .coeff[i12 + f_expl_temp.sp.coeff.size(0) * i10];
                                }
                            }
                            e_expl_temp.sp.knots.set_size(1, f_expl_temp.sp.knots.size(1));
                            m_loop_ub = f_expl_temp.sp.knots.size(1);
                            for (int i13{0}; i13 < m_loop_ub; i13++) {
                                e_expl_temp.sp.knots[i13] = f_expl_temp.sp.knots[i13];
                            }
                            e_expl_temp.sp.Lk.set_size(1, f_expl_temp.sp.Lk.size(1));
                            p_loop_ub = f_expl_temp.sp.Lk.size(1);
                            for (int i16{0}; i16 < p_loop_ub; i16++) {
                                e_expl_temp.sp.Lk[i16] = f_expl_temp.sp.Lk[i16];
                            }
                            // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda,
                            // u1_tilda );
                            c_L = splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                               f_expl_temp.sp.Bl.handle, f_expl_temp.sp.Bl.order,
                                               e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                               e_expl_temp.sp.Lk, curv.b_param,
                                               curv.a_param + curv.b_param);
                        } else if (curv.Info.Type == CurveType_TransP5) {
                            // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
                            // 'LengthCurv:14' L = TransP5LengthApprox( curv );
                            c_L = TransP5LengthApprox(&curv);
                        } else {
                            // 'LengthCurv:15' else
                            // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV",
                            // mfilename );
                        }
                        // 'cutZeroEnd:6' Lcut    = ctx.cfg.LSplitZero;
                        b_Lcut = ctx->cfg.LSplitZero;
                        // 'cutZeroEnd:8' if( Lcut > L / 3 )
                        if (ctx->cfg.LSplitZero > c_L / 3.0) {
                            // 'cutZeroEnd:9' Lcut = L / 3;
                            b_Lcut = c_L / 3.0;
                        }
                        // 'cutZeroEnd:12' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 1,
                        // Lcut, true );
                        b_cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                        ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                        ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                        ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                        ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curv,
                                        b_Lcut, &c_ret, &b_curv, &curvE);
                        // 'cutZeroEnd:14' if( ret < 0 )
                        if (c_ret < 0.0) {
                            // 'cutZeroEnd:15' curv1 = curv;
                            b_curv = curv;
                            // 'cutZeroEnd:16' curv1.UseConstJerk      = true;
                            b_curv.UseConstJerk = true;
                            // 'cutZeroEnd:17' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
                            // true );
                            d_ctx = ctx->kin;
                            d_curv = b_curv;
                            b_zeroSpeedCurv(
                                &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &d_ctx,
                                &d_curv, b_a__1, b_a__2, b_a__3, &b_curv.ConstJerk);
                            // 'cutZeroEnd:18' curv1.ConstJerk         = jps;
                        } else {
                            // 'cutZeroEnd:19' else
                            // 'cutZeroEnd:20' ocn_assert( check_curv_length( ctx, curv2, Lcut ),
                            // "Curve Length not valide", mfilename ); 'calcTransition:96' tol =
                            // 1E-3; 'calcTransition:98' isValid = ( abs( LengthCurv( ctx, curv, 0,
                            // 1 ) - L ) <= tol ); 'LengthCurv:3' if ( curv.Info.Type ==
                            // CurveType.Helix ) || ( curv.Info.Type == CurveType.Line )
                            if ((curvE.Info.Type == CurveType_Helix) ||
                                (curvE.Info.Type == CurveType_Line)) {
                                // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                                c_EvalCurvStruct(
                                    &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                    ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                    ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                    ctx->cfg.NRot, &curvE, a__1, r1D, a__2, a__3);
                                // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                                // 'MyNorm:2' coder.inline('always');
                                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                                // 'mysqrt:3' y = sqrt(x);
                                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                                sqrt_calls++;
                            } else if (curvE.Info.Type == CurveType_Spline) {
                                int t_loop_ub;
                                int v_loop_ub;
                                int w_loop_ub;
                                // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                                // 'LengthCurv:7' a        = curv.a_param;
                                // 'LengthCurv:8' b        = curv.b_param;
                                // 'LengthCurv:9' u0_tilda = a * u0 + b;
                                // 'LengthCurv:10' u1_tilda = a * u1 + b;
                                // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                                ctx->q_spline.get(curvE.sp_index, &f_expl_temp);
                                e_expl_temp.sp.coeff.set_size(f_expl_temp.sp.coeff.size(0),
                                                              f_expl_temp.sp.coeff.size(1));
                                t_loop_ub = f_expl_temp.sp.coeff.size(1);
                                for (int i20{0}; i20 < t_loop_ub; i20++) {
                                    int u_loop_ub;
                                    u_loop_ub = f_expl_temp.sp.coeff.size(0);
                                    for (int i21{0}; i21 < u_loop_ub; i21++) {
                                        e_expl_temp.sp
                                            .coeff[i21 + e_expl_temp.sp.coeff.size(0) * i20] =
                                            f_expl_temp.sp
                                                .coeff[i21 + f_expl_temp.sp.coeff.size(0) * i20];
                                    }
                                }
                                e_expl_temp.sp.knots.set_size(1, f_expl_temp.sp.knots.size(1));
                                v_loop_ub = f_expl_temp.sp.knots.size(1);
                                for (int i22{0}; i22 < v_loop_ub; i22++) {
                                    e_expl_temp.sp.knots[i22] = f_expl_temp.sp.knots[i22];
                                }
                                e_expl_temp.sp.Lk.set_size(1, f_expl_temp.sp.Lk.size(1));
                                w_loop_ub = f_expl_temp.sp.Lk.size(1);
                                for (int i23{0}; i23 < w_loop_ub; i23++) {
                                    e_expl_temp.sp.Lk[i23] = f_expl_temp.sp.Lk[i23];
                                }
                                // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline,
                                // u0_tilda, u1_tilda );
                                splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                             f_expl_temp.sp.Bl.handle, f_expl_temp.sp.Bl.order,
                                             e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                             e_expl_temp.sp.Lk, curvE.b_param,
                                             curvE.a_param + curvE.b_param);
                            } else if (curvE.Info.Type == CurveType_TransP5) {
                                // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
                                // 'LengthCurv:14' L = TransP5LengthApprox( curv );
                                TransP5LengthApprox(&curvE);
                            } else {
                                // 'LengthCurv:15' else
                                // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH
                                // CURV", mfilename );
                            }
                            // 'cutZeroEnd:21' curv2.UseConstJerk      = true;
                            curvE.UseConstJerk = true;
                            // 'cutZeroEnd:22' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2,
                            // true );
                            e_ctx = ctx->kin;
                            b_curvE = curvE;
                            b_zeroSpeedCurv(
                                &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &e_ctx,
                                &b_curvE, a__4, a__5, a__6, &curvE.ConstJerk);
                            // 'cutZeroEnd:23' curv2.ConstJerk         = jps;
                            // 'cutZeroEnd:24' curv1.UseConstJerk      = false;
                            b_curv.UseConstJerk = false;
                            // 'cutZeroEnd:25' check_continuity( ctx, curv, curv1, curv2 );
                            // 'cutZeroStart:58' curv_vec    = [ curv; curv1; curv2 ];
                            // 'cutZeroStart:59' u_vec       = [ 0, 1 ];
                            // 'cutZeroStart:60' r           = repmat( curv.R0( ctx.cfg.maskTot ),
                            // 1, 2, 3 ); 'cutZeroStart:61' rd          = r; 'cutZeroStart:62' rdd
                            // = r; 'cutZeroStart:64' for j = 1 : 3 'cutZeroStart:65' [ r( :, :, j )
                            // , rd( :, :, j ), rdd( :, :, j ) ] = ... 'cutZeroStart:66'
                            // EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
                            j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &curv, r1, r2, r3);
                            // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                            // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                            // curv_vec( j ).a_param^2; 'cutZeroStart:65' [ r( :, :, j ) , rd( :, :,
                            // j ), rdd( :, :, j ) ] = ... 'cutZeroStart:66'         EvalCurvStruct(
                            // ctx, curv_vec( j ),  u_vec );
                            j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &b_curv, r1, r2, r3);
                            // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                            // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                            // curv_vec( j ).a_param^2; 'cutZeroStart:65' [ r( :, :, j ) , rd( :, :,
                            // j ), rdd( :, :, j ) ] = ... 'cutZeroStart:66'         EvalCurvStruct(
                            // ctx, curv_vec( j ),  u_vec );
                            j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &curvE, r1, r2, r3);
                            // 'cutZeroStart:67' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                            // ).a_param; 'cutZeroStart:68' rdd( :, :, j )   = rdd( :, :, j ) /
                            // curv_vec( j ).a_param^2; 'cutZeroStart:72' ind1 = [ 1, 1; 1, 2; 2, 2
                            // ]; 'cutZeroStart:73' ind2 = [ 2, 1; 3, 2; 3, 1 ]; 'cutZeroStart:75'
                            // for j = 1 : 3
                        }
                        //      if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
                        //          u = curv.a_param / 2 + curv.b_param;
                        //      end
                        //      curv2                   = curv;
                        //  curv2.UseConstJerk      = true;
                        //  curv2.b_param           = u;
                        //  curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
                        //  [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
                        //  curv2.ConstJerk         = jps;
                        //  curv2.Info.zspdmode     = ZSpdMode.NZ;
                        //
                        //  curv1                   = curv;
                        //  curv1.a_param           = u - curv1.b_param;
                        //  curv1.UseConstJerk      = false;
                        //  curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
                        //
                        //  if( isAZeroStart( curv ) )
                        //      curv1.Info.zspdmode = ZSpdMode.ZN;
                        //  else
                        //      curv1.Info.zspdmode = ZSpdMode.NN;
                        //  end
                        //
                        //  if( coder.target("MATLAB") )
                        //      check_continuity( ctx, curv, curv1, curv2 );
                        //  end
                        curv = b_curv;
                        // 'splitCurvStruct:27' if( ret < 0 )
                        if (c_ret < 0.0) {
                            // 'splitCurvStruct:28' ctx.q_split.push( curv );
                            ctx->q_split.push(&b_curv);
                        } else {
                            // 'splitCurvStruct:31' hasEndSpeed     = true;
                            hasEndSpeed = true;
                            guard1 = true;
                        }
                    } else {
                        guard1 = true;
                    }
                }
                if (guard1) {
                    double L_split;
                    double b_N;
                    int b_k;
                    bool exitg1;
                    // 'splitCurvStruct:34' L       = LengthCurv( ctx, curv, 0, 1 );
                    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type
                    // == CurveType.Line )
                    if ((curv.Info.Type == CurveType_Helix) || (curv.Info.Type == CurveType_Line)) {
                        int b_loop_ub;
                        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                        c_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv,
                                         a__1, r1D, a__2, a__3);
                        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        b_loop_ub = r1D.size(0);
                        r.set_size(r1D.size(0));
                        for (int i2{0}; i2 < b_loop_ub; i2++) {
                            double b_varargin_1;
                            b_varargin_1 = r1D[i2];
                            r[i2] = std::pow(b_varargin_1, 2.0);
                        }
                        L = std::sqrt(coder::sum(r));
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                    } else if (curv.Info.Type == CurveType_Spline) {
                        int c_loop_ub;
                        int e_loop_ub;
                        int f_loop_ub;
                        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                        // 'LengthCurv:7' a        = curv.a_param;
                        // 'LengthCurv:8' b        = curv.b_param;
                        // 'LengthCurv:9' u0_tilda = a * u0 + b;
                        // 'LengthCurv:10' u1_tilda = a * u1 + b;
                        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                        ctx->q_spline.get(curv.sp_index, &f_expl_temp);
                        e_expl_temp.sp.coeff.set_size(f_expl_temp.sp.coeff.size(0),
                                                      f_expl_temp.sp.coeff.size(1));
                        c_loop_ub = f_expl_temp.sp.coeff.size(1);
                        for (int i3{0}; i3 < c_loop_ub; i3++) {
                            int d_loop_ub;
                            d_loop_ub = f_expl_temp.sp.coeff.size(0);
                            for (int i4{0}; i4 < d_loop_ub; i4++) {
                                e_expl_temp.sp.coeff[i4 + e_expl_temp.sp.coeff.size(0) * i3] =
                                    f_expl_temp.sp.coeff[i4 + f_expl_temp.sp.coeff.size(0) * i3];
                            }
                        }
                        e_expl_temp.sp.knots.set_size(1, f_expl_temp.sp.knots.size(1));
                        e_loop_ub = f_expl_temp.sp.knots.size(1);
                        for (int i5{0}; i5 < e_loop_ub; i5++) {
                            e_expl_temp.sp.knots[i5] = f_expl_temp.sp.knots[i5];
                        }
                        e_expl_temp.sp.Lk.set_size(1, f_expl_temp.sp.Lk.size(1));
                        f_loop_ub = f_expl_temp.sp.Lk.size(1);
                        for (int i6{0}; i6 < f_loop_ub; i6++) {
                            e_expl_temp.sp.Lk[i6] = f_expl_temp.sp.Lk[i6];
                        }
                        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda,
                        // u1_tilda );
                        L = splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                         f_expl_temp.sp.Bl.handle, f_expl_temp.sp.Bl.order,
                                         e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                         e_expl_temp.sp.Lk, curv.b_param,
                                         curv.a_param + curv.b_param);
                    } else if (curv.Info.Type == CurveType_TransP5) {
                        // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
                        // 'LengthCurv:14' L = TransP5LengthApprox( curv );
                        L = TransP5LengthApprox(&curv);
                    } else {
                        // 'LengthCurv:15' else
                        // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV",
                        // mfilename );
                    }
                    // 'splitCurvStruct:35' L_split = ctx.cfg.LSplit;
                    //  Number of sub segments
                    // 'splitCurvStruct:38' N = ceil( L / L_split );
                    b_N = std::ceil(L / ctx->cfg.LSplit);
                    //  Length of the sub segments
                    // 'splitCurvStruct:41' L_split = L / N;
                    L_split = L / b_N;
                    // 'splitCurvStruct:43' for k = 1 : N - 1
                    b_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (b_k <= static_cast<int>(b_N - 1.0) - 1)) {
                        // 'splitCurvStruct:44' [ ret, curvSplited, curv ] = cutCurvStruct( ctx,
                        // curv, 0, L_split, false );
                        c_curv = curv;
                        cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                      ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                      ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                      ctx->cfg.GaussLegendreW, &c_curv, L_split, &b_ret,
                                      &curvSplited, &curv);
                        // 'splitCurvStruct:45' if( ret < 0 )
                        if (b_ret < 0.0) {
                            exitg1 = true;
                        } else {
                            // 'splitCurvStruct:47' ocn_assert( check_curv_length( ctx, curvSplited,
                            // L_split ), ... 'splitCurvStruct:48'         "Curve Length not
                            // valide", mfilename ); 'calcTransition:96' tol = 1E-3;
                            // 'calcTransition:98' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) -
                            // L ) <= tol ); 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix )
                            // || ( curv.Info.Type == CurveType.Line )
                            if ((curvSplited.Info.Type == CurveType_Helix) ||
                                (curvSplited.Info.Type == CurveType_Line)) {
                                // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
                                c_EvalCurvStruct(
                                    &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                    ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                    ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                    ctx->cfg.NRot, &curvSplited, a__1, r1D, a__2, a__3);
                                // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
                                // 'MyNorm:2' coder.inline('always');
                                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                                // 'mysqrt:3' y = sqrt(x);
                                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                                sqrt_calls++;
                            } else if (curvSplited.Info.Type == CurveType_Spline) {
                                int o_loop_ub;
                                int r_loop_ub;
                                int s_loop_ub;
                                // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
                                // 'LengthCurv:7' a        = curv.a_param;
                                // 'LengthCurv:8' b        = curv.b_param;
                                // 'LengthCurv:9' u0_tilda = a * u0 + b;
                                // 'LengthCurv:10' u1_tilda = a * u1 + b;
                                // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
                                ctx->q_spline.get(curvSplited.sp_index, &f_expl_temp);
                                e_expl_temp.sp.coeff.set_size(f_expl_temp.sp.coeff.size(0),
                                                              f_expl_temp.sp.coeff.size(1));
                                o_loop_ub = f_expl_temp.sp.coeff.size(1);
                                for (int i15{0}; i15 < o_loop_ub; i15++) {
                                    int q_loop_ub;
                                    q_loop_ub = f_expl_temp.sp.coeff.size(0);
                                    for (int i17{0}; i17 < q_loop_ub; i17++) {
                                        e_expl_temp.sp
                                            .coeff[i17 + e_expl_temp.sp.coeff.size(0) * i15] =
                                            f_expl_temp.sp
                                                .coeff[i17 + f_expl_temp.sp.coeff.size(0) * i15];
                                    }
                                }
                                e_expl_temp.sp.knots.set_size(1, f_expl_temp.sp.knots.size(1));
                                r_loop_ub = f_expl_temp.sp.knots.size(1);
                                for (int i18{0}; i18 < r_loop_ub; i18++) {
                                    e_expl_temp.sp.knots[i18] = f_expl_temp.sp.knots[i18];
                                }
                                e_expl_temp.sp.Lk.set_size(1, f_expl_temp.sp.Lk.size(1));
                                s_loop_ub = f_expl_temp.sp.Lk.size(1);
                                for (int i19{0}; i19 < s_loop_ub; i19++) {
                                    e_expl_temp.sp.Lk[i19] = f_expl_temp.sp.Lk[i19];
                                }
                                // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline,
                                // u0_tilda, u1_tilda );
                                splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                             f_expl_temp.sp.Bl.handle, f_expl_temp.sp.Bl.order,
                                             e_expl_temp.sp.coeff, e_expl_temp.sp.knots,
                                             e_expl_temp.sp.Lk, curvSplited.b_param,
                                             curvSplited.a_param + curvSplited.b_param);
                            } else if (curvSplited.Info.Type == CurveType_TransP5) {
                                // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
                                // 'LengthCurv:14' L = TransP5LengthApprox( curv );
                                TransP5LengthApprox(&curvSplited);
                            } else {
                                // 'LengthCurv:15' else
                                // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH
                                // CURV", mfilename );
                            }
                            // 'splitCurvStruct:50' ctx.q_split.push( curvSplited );
                            ctx->q_split.push(&curvSplited);
                            b_k++;
                        }
                    }
                    // 'splitCurvStruct:54' ctx.q_split.push( curv );
                    ctx->q_split.push(&curv);
                    // 'splitCurvStruct:56' if( hasEndSpeed )
                    if (hasEndSpeed) {
                        //  cut zero End
                        // 'splitCurvStruct:58' ctx.q_split.push( curvE );
                        ctx->q_split.push(&curvE);
                    }
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
