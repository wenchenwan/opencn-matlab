
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
#include "Kinematics.h"
#include "LengthCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStruct.h"
#include "cutZeroEnd.h"
#include "cutZeroStart.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
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
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> breakPoints;
    ::coder::array<int, 2U> ii;
    ::coder::array<bool, 2U> x;
    Axes params_tool_offset;
    CurvStruct b_curv;
    CurvStruct c_curv;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    CurvStruct d_curv;
    CurvStruct f_expl_temp;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
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
    double t3_ConstJerk;
    double t3_a_param;
    double t3_b_param;
    double t3_delta;
    double t3_pitch;
    double t3_theta;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int t3_i_begin_sp;
    int t3_i_end_sp;
    int t3_index_smooth;
    unsigned int t3_sp_index;
    bool hasEndSpeed;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    bool t3_UseConstJerk;
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
            b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                               params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                               params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                               params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                               params_gcodeInfoStruct_G91_1, params_tool_toolno,
                               params_tool_pocketno, &params_tool_offset, params_tool_diameter,
                               params_tool_frontangle, params_tool_backangle,
                               params_tool_orientation, &params_spline, params_R0, params_R1,
                               params_Cprim, params_evec, params_CoeffP5, &e_expl_temp);
            t3_delta = e_expl_temp.delta;
            t3_theta = e_expl_temp.theta;
            t3_pitch = e_expl_temp.pitch;
            t3_sp_index = e_expl_temp.sp_index;
            t3_i_begin_sp = e_expl_temp.i_begin_sp;
            t3_i_end_sp = e_expl_temp.i_end_sp;
            t3_index_smooth = e_expl_temp.index_smooth;
            t3_UseConstJerk = e_expl_temp.UseConstJerk;
            t3_ConstJerk = e_expl_temp.ConstJerk;
            t3_a_param = e_expl_temp.a_param;
            t3_b_param = e_expl_temp.b_param;
            loop_ub = e_expl_temp.R0.size[0];
            b_loop_ub = e_expl_temp.R1.size[0];
            c_loop_ub = e_expl_temp.CoeffP5.size(1);
            d_loop_ub = e_expl_temp.Coeff.size(0);
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
            curvE.Info = e_expl_temp.Info;
            curvE.tool = e_expl_temp.tool;
            curvE.sp = e_expl_temp.sp;
            curvE.R0.set_size(e_expl_temp.R0.size[0]);
            for (int i1{0}; i1 < loop_ub; i1++) {
                curvE.R0[i1] = e_expl_temp.R0.data[i1];
            }
            curvE.R1.set_size(e_expl_temp.R1.size[0]);
            for (int i2{0}; i2 < b_loop_ub; i2++) {
                curvE.R1[i2] = e_expl_temp.R1.data[i2];
            }
            curvE.delta = t3_delta;
            curvE.CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
            curvE.evec[0] = e_expl_temp.evec[0];
            curvE.CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
            curvE.evec[1] = e_expl_temp.evec[1];
            curvE.CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
            curvE.evec[2] = e_expl_temp.evec[2];
            curvE.theta = t3_theta;
            curvE.pitch = t3_pitch;
            curvE.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
            for (int i3{0}; i3 < c_loop_ub; i3++) {
                int e_loop_ub;
                e_loop_ub = e_expl_temp.CoeffP5.size(0);
                for (int i4{0}; i4 < e_loop_ub; i4++) {
                    curvE.CoeffP5[i4 + curvE.CoeffP5.size(0) * i3] =
                        e_expl_temp.CoeffP5[i4 + e_expl_temp.CoeffP5.size(0) * i3];
                }
            }
            curvE.sp_index = t3_sp_index;
            curvE.i_begin_sp = t3_i_begin_sp;
            curvE.i_end_sp = t3_i_end_sp;
            curvE.index_smooth = t3_index_smooth;
            curvE.UseConstJerk = t3_UseConstJerk;
            curvE.ConstJerk = t3_ConstJerk;
            curvE.Coeff.set_size(e_expl_temp.Coeff.size(0));
            for (int i5{0}; i5 < d_loop_ub; i5++) {
                curvE.Coeff[i5] = e_expl_temp.Coeff[i5];
            }
            curvE.a_param = t3_a_param;
            curvE.b_param = t3_b_param;
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
                    //  cut zero Start
                    // 'splitCurvStruct:18' [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
                    b_curv = curv;
                    cutZeroStart(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax,
                                 ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                 ctx->cfg.GaussLegendreW, &ctx->kin, &b_curv, &ret, &curvS, &curv);
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
                        //  cut zero End
                        // 'splitCurvStruct:26' [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
                        d_curv = curv;
                        cutZeroEnd(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax,
                                   ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &ctx->kin, &d_curv, &c_ret, &curv,
                                   &curvE);
                        // 'splitCurvStruct:27' if( ret < 0 )
                        if (c_ret < 0.0) {
                            // 'splitCurvStruct:28' ctx.q_split.push( curv );
                            ctx->q_split.push(&curv);
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
                    // 'splitCurvStruct:34' if( true && curv.Info.Type == CurveType.Spline )
                    if (curv.Info.Type == CurveType_Spline) {
                        double uMax;
                        double work_data;
                        int b_ii;
                        int dimSize;
                        int f_loop_ub;
                        int g_loop_ub;
                        int i8;
                        int idx;
                        int nx;
                        bool exitg1;
                        // 'splitCurvStruct:35' bspline     = ctx.q_spline.get( curv.sp_index );
                        ctx->q_spline.get(curv.sp_index, &f_expl_temp);
                        // 'splitCurvStruct:36' breakPoints = bspline.sp.Bl.breakpoints;
                        // 'splitCurvStruct:37' uMin        = curv.b_param;
                        // 'splitCurvStruct:38' uMax        = curv.b_param + curv.a_param;
                        uMax = curv.b_param + curv.a_param;
                        // 'splitCurvStruct:39' ind         = find( breakPoints > uMin & breakPoints
                        // < uMax );
                        x.set_size(1, f_expl_temp.sp.Bl.breakpoints.size(1));
                        f_loop_ub = f_expl_temp.sp.Bl.breakpoints.size(1);
                        for (int i6{0}; i6 < f_loop_ub; i6++) {
                            double d;
                            d = f_expl_temp.sp.Bl.breakpoints[i6];
                            x[i6] = ((d > curv.b_param) && (d < uMax));
                        }
                        nx = x.size(1);
                        idx = 0;
                        ii.set_size(1, x.size(1));
                        b_ii = 0;
                        exitg1 = false;
                        while ((!exitg1) && (b_ii <= nx - 1)) {
                            if (x[b_ii]) {
                                idx++;
                                ii[idx - 1] = b_ii + 1;
                                if (idx >= nx) {
                                    exitg1 = true;
                                } else {
                                    b_ii++;
                                }
                            } else {
                                b_ii++;
                            }
                        }
                        if (x.size(1) == 1) {
                            if (idx == 0) {
                                ii.set_size(1, 0);
                            }
                        } else {
                            int b_idx;
                            if (idx < 1) {
                                b_idx = 0;
                            } else {
                                b_idx = idx;
                            }
                            ii.set_size(ii.size(0), b_idx);
                        }
                        // 'splitCurvStruct:40' breakPoints = [ uMin, breakPoints( ind ), uMax ] ;
                        breakPoints.set_size(1, ii.size(1) + 2);
                        breakPoints[0] = curv.b_param;
                        g_loop_ub = ii.size(1);
                        for (int i7{0}; i7 < g_loop_ub; i7++) {
                            breakPoints[i7 + 1] = f_expl_temp.sp.Bl.breakpoints[ii[i7] - 1];
                        }
                        breakPoints[ii.size(1) + 1] = uMax;
                        // 'splitCurvStruct:41' deltaU      = diff( breakPoints );
                        dimSize = breakPoints.size(1);
                        b_y1.set_size(1, breakPoints.size(1) - 1);
                        work_data = breakPoints[0];
                        for (int m{2}; m <= dimSize; m++) {
                            double d1;
                            double tmp1;
                            tmp1 = breakPoints[m - 1];
                            d1 = tmp1;
                            tmp1 -= work_data;
                            work_data = d1;
                            b_y1[m - 2] = tmp1;
                        }
                        // 'splitCurvStruct:43' for j = 1 : length( deltaU )
                        i8 = b_y1.size(1);
                        for (int j{0}; j < i8; j++) {
                            // 'splitCurvStruct:44' curvSplited         = curv;
                            curvSplited = curv;
                            // 'splitCurvStruct:45' curvSplited.b_param = breakPoints( j );
                            curvSplited.b_param = breakPoints[j];
                            // 'splitCurvStruct:46' curvSplited.a_param = deltaU( j );
                            curvSplited.a_param = b_y1[j];
                            // 'splitCurvStruct:47' ctx.q_split.push( curvSplited );
                            ctx->q_split.push(&curvSplited);
                        }
                    } else {
                        double L;
                        double L_split;
                        double b_N;
                        int b_k;
                        bool exitg1;
                        // 'splitCurvStruct:49' else
                        // 'splitCurvStruct:50' L       = LengthCurv( ctx, curv, 0, 1 );
                        L = LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                       ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                       ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                       ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                       ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, &curv);
                        // 'splitCurvStruct:51' L_split = ctx.cfg.LSplit;
                        //  Number of sub segments
                        // 'splitCurvStruct:54' N = ceil( L / L_split );
                        b_N = std::ceil(L / ctx->cfg.LSplit);
                        //  Length of the sub segments
                        // 'splitCurvStruct:57' L_split = L / N;
                        L_split = L / b_N;
                        // 'splitCurvStruct:59' for k = 1 : N - 1
                        b_k = 0;
                        exitg1 = false;
                        while ((!exitg1) && (b_k <= static_cast<int>(b_N - 1.0) - 1)) {
                            // 'splitCurvStruct:60' [ ret, curvSplited, curv ] = cutCurvStruct( ctx,
                            // curv, 0, L_split, false );
                            c_curv = curv;
                            cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                          ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                          ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                          ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                          ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                          ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &c_curv,
                                          L_split, &b_ret, &curvSplited, &curv);
                            // 'splitCurvStruct:61' if( ret < 0 )
                            if (b_ret < 0.0) {
                                exitg1 = true;
                            } else {
                                double b_x;
                                // 'splitCurvStruct:63' ocn_assert( check_curv_length( ctx,
                                // curvSplited, L_split ), ... 'splitCurvStruct:64' "Curve Length
                                // not valide", mfilename ); 'calcTransition:107' tol = 1E-3;
                                // 'calcTransition:109' isValid = ( abs( LengthCurv( ctx, curv, 0, 1
                                // ) - L ) <= tol );
                                b_x =
                                    LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                               ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                               ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                               ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                               ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                               ctx->cfg.GaussLegendreW, &curvSplited) -
                                    L_split;
                                bb_ocn_assert(std::abs(b_x) <= 0.001);
                                // 'splitCurvStruct:66' ctx.q_split.push( curvSplited );
                                ctx->q_split.push(&curvSplited);
                                b_k++;
                            }
                        }
                        // 'splitCurvStruct:68' ctx.q_split.push( curv );
                        ctx->q_split.push(&curv);
                    }
                    // 'splitCurvStruct:71' if( hasEndSpeed )
                    if (hasEndSpeed) {
                        //  cut zero End
                        // 'splitCurvStruct:73' ctx.q_split.push( curvE );
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
