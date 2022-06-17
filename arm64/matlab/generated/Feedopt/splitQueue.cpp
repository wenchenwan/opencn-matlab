//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splitQueue.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "splitQueue.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStructU.h"
#include "cutZeroEnd.h"
#include "cutZeroStart.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "coder_array.h"
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
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    CurvStruct b_curv;
    CurvStruct c_curv;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
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
                    // 'isAZeroEnd:7' zeroFlag = true;
                    //  cut zero End
                    // 'splitCurvStruct:25' [ curv, curvE ] = cutZeroEnd( ctx, curv );
                    c_curv = curv;
                    cutZeroEnd(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart, ctx->cfg.maskRot, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.LSplitZero,
                               ctx->cfg.dt, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &ctx->kin, &c_curv, &curv, &curvE);
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
