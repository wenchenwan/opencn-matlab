//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitQueue.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

// Include Files
#include "splitQueue.h"
#include "Kinematics.h"
#include "LengthCurv.h"
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
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
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
    Kinematics b_ctx;
    Kinematics d_ctx;
    Kinematics e_ctx;
    Kinematics f_ctx;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    Axes params_tool_offset;
    CurvStruct b_curv;
    CurvStruct b_curvE;
    CurvStruct b_curvS;
    CurvStruct c_ctx;
    CurvStruct c_curv;
    CurvStruct c_curvS;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    CurvStruct d_curv;
    SplineStruct params_spline;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double b_ret;
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
                    double L;
                    double Lcut;
                    //  cut zero Start
                    // 'splitCurvStruct:18' [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
                    //  cutZeroStart : Cut the start of the given to handle the zero speed.
                    //  u  = cutCurvStructU( ctx, curv, 0, ctx.cfg.LSplitZero, false );
                    // 'cutZeroStart:5' L       = LengthCurv( ctx, curv, 0, 1 );
                    L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                   &curv);
                    // 'cutZeroStart:6' Lcut    = ctx.cfg.LSplitZero;
                    Lcut = ctx->cfg.LSplitZero;
                    // 'cutZeroStart:8' if( Lcut > L / 3 )
                    if (ctx->cfg.LSplitZero > L / 3.0) {
                        // 'cutZeroStart:9' Lcut = L / 3;
                        Lcut = L / 3.0;
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
                                      ctx->cfg.jmax, ctx->cfg.dt, &b_ctx, &b_curvS, a__1, a__2,
                                      a__3, &curvS.ConstJerk);
                        // 'cutZeroStart:18' curv1.ConstJerk         = jps;
                    } else {
                        // 'cutZeroStart:19' else
                        // 'cutZeroStart:20' assert( check_curv_length( ctx, curv1, Lcut ), ...
                        // 'cutZeroStart:21'             mfilename + " Curve Length not valide");
                        // 'cutZeroStart:107' tol = 1E-5;
                        // 'cutZeroStart:109' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L )
                        // <= tol );
                        LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                   &curvS);
                        curvS.UseConstJerk = true;
                        // 'cutZeroStart:23' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
                        // false );
                        d_ctx = ctx->kin;
                        c_curvS = curvS;
                        zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                      ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                      ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax,
                                      ctx->cfg.jmax, ctx->cfg.dt, &d_ctx, &c_curvS, a__4, a__5,
                                      a__6, &curvS.ConstJerk);
                        // 'cutZeroStart:24' curv1.ConstJerk         = jps;
                        // 'cutZeroStart:25' curv2.UseConstJerk      = false;
                        b_curv.UseConstJerk = false;
                        // 'cutZeroStart:26' if( coder.target("MATLAB") )
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
                        double c_L;
                        //  cut zero End
                        // 'splitCurvStruct:26' [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
                        //  cutZeroEnd : Cut the end of the given to handle the zero speed.
                        //  u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
                        // 'cutZeroEnd:5' L       = LengthCurv( ctx, curv, 0, 1 );
                        c_L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                         ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curv);
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
                            e_ctx = ctx->kin;
                            d_curv = b_curv;
                            b_zeroSpeedCurv(
                                &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &e_ctx,
                                &d_curv, a__1, a__2, a__3, &b_curv.ConstJerk);
                            // 'cutZeroEnd:18' curv1.ConstJerk         = jps;
                        } else {
                            // 'cutZeroEnd:19' else
                            // 'cutZeroEnd:20' assert( check_curv_length( ctx, curv2, Lcut ), ...
                            // 'cutZeroEnd:21'             mfilename + " Curve Length not valide");
                            // 'cutZeroStart:107' tol = 1E-5;
                            // 'cutZeroStart:109' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L
                            // ) <= tol );
                            LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                       ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                       ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                       ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                       ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, &curvE);
                            curvE.UseConstJerk = true;
                            // 'cutZeroEnd:23' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2,
                            // true );
                            f_ctx = ctx->kin;
                            b_curvE = curvE;
                            b_zeroSpeedCurv(
                                &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &f_ctx,
                                &b_curvE, a__4, a__5, a__6, &curvE.ConstJerk);
                            // 'cutZeroEnd:24' curv2.ConstJerk         = jps;
                            // 'cutZeroEnd:25' curv1.UseConstJerk      = false;
                            b_curv.UseConstJerk = false;
                            // 'cutZeroEnd:26' if( coder.target("MATLAB") )
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
                    double b_L;
                    double b_N;
                    int b_k;
                    bool exitg1;
                    // 'splitCurvStruct:34' L       = LengthCurv( ctx, curv, 0, 1 );
                    b_L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &curv);
                    // 'splitCurvStruct:35' L_split = ctx.cfg.LSplit;
                    //  Number of sub segments
                    // 'splitCurvStruct:38' N = ceil( L / L_split );
                    b_N = std::ceil(b_L / ctx->cfg.LSplit);
                    //  Length of the sub segments
                    // 'splitCurvStruct:41' L_split = L / N;
                    L_split = b_L / b_N;
                    // 'splitCurvStruct:43' for k = 1 : N - 1
                    b_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (b_k <= static_cast<int>(b_N - 1.0) - 1)) {
                        // 'splitCurvStruct:44' if( k > 1 )
                        if (static_cast<double>(b_k) + 1.0 > 1.0) {
                            // 'splitCurvStruct:45' curvTest = ctx.q_split.get( k );
                            ctx->q_split.get(static_cast<double>(b_k) + 1.0, &c_ctx);
                        }
                        // 'splitCurvStruct:47' [ ret, curvSplited, curv ] = cutCurvStruct( ctx,
                        // curv, 0, L_split, false );
                        c_curv = curv;
                        cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                      ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                      ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                      ctx->cfg.GaussLegendreW, &c_curv, L_split, &b_ret,
                                      &curvSplited, &curv);
                        // 'splitCurvStruct:48' if( ret < 0 )
                        if (b_ret < 0.0) {
                            exitg1 = true;
                        } else {
                            double x;
                            // 'splitCurvStruct:50' assert( check_curv_length( ctx, curvSplited,
                            // L_split ), ... 'splitCurvStruct:51'             mfilename + " Curve
                            // Length not valide"); 'splitCurvStruct:67' tol = 1E-3;
                            // 'splitCurvStruct:69' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) -
                            // L ) <= tol );
                            x = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                           ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                           ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                           ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                           ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                           &curvSplited) -
                                L_split;
                            // 'splitCurvStruct:71' if( ~isValid )
                            if (std::abs(x) > 0.001) {
                                // 'splitCurvStruct:72' disp("spline Length is not valid");
                                printf("%s\n", "spline Length is not valid");
                                fflush(stdout);
                            }
                            ctx->q_split.push(&curvSplited);
                            b_k++;
                        }
                    }
                    // 'splitCurvStruct:57' ctx.q_split.push( curv );
                    ctx->q_split.push(&curv);
                    // 'splitCurvStruct:59' if( hasEndSpeed )
                    if (hasEndSpeed) {
                        //  cut zero End
                        // 'splitCurvStruct:61' ctx.q_split.push( curvE );
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
