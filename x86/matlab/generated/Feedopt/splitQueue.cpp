
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
#include "LengthCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStruct.h"
#include "cutZeroEnd.h"
#include "find.h"
#include "ocn_assert.h"
#include "ocn_print1.h"
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
#include "string1.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function ctx = splitQueue( ctx )
//
// splitQueue : Split the curves in the q_smooth queue.
//
//  Inputs :
//    ctx : The context of the computational chain.
//  Outputs :
//    ctx : The context of the computational chain.
//
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void splitQueue(b_FeedoptContext *ctx)
{
    static const signed char ind1[2][3]{{1, 1, 2}, {1, 2, 2}};
    static const signed char ind2[2][3]{{2, 3, 3}, {1, 2, 1}};
    Kinematics b_ctx;
    Kinematics c_ctx;
    coder::rtString obj;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> breakPoints;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 1U> b_z1;
    ::coder::array<double, 1U> c_x;
    ::coder::array<double, 1U> c_z1;
    ::coder::array<double, 1U> z1;
    ::coder::array<int, 2U> r;
    ::coder::array<bool, 2U> g_expl_temp;
    ::coder::array<bool, 1U> d_x;
    Axes params_tool_offset;
    CurvStruct curv_vec[3];
    CurvStruct b_curv;
    CurvStruct b_curvS;
    CurvStruct c_curvS;
    CurvStruct curv;
    CurvStruct curvE;
    CurvStruct curvS;
    CurvStruct curvSplited;
    CurvStruct f_expl_temp;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
    double r_data[36];
    double rd_data[36];
    double rdd_data[36];
    double b_rd_data[12];
    double b_rdd_data[12];
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
    double t9_ConstJerk;
    double t9_a_param;
    double t9_b_param;
    double t9_delta;
    double t9_pitch;
    double t9_theta;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int t9_i_begin_sp;
    int t9_i_end_sp;
    int t9_index_smooth;
    unsigned int t9_sp_index;
    char st[12];
    char b_st[11];
    char obj2Value_data[11];
    char b_obj2Value_data[10];
    signed char tmp_data[6];
    bool hasEndSpeed;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    bool t9_UseConstJerk;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'splitQueue:11' if ctx.q_smooth.isempty()
    if (!ctx->q_smooth.isempty()) {
        unsigned int N;
        int i;
        // 'splitQueue:12' ctx.k0 = int32( 1 );
        ctx->k0 = 1;
        // 'splitQueue:13' DebugLog( DebugCfg.Validate,        'Splitting...\n' );
        //  DebugLog : Print msg in log pipe.
        //
        //  Inputs :
        //  cfg       : The configuration structure
        //  varargin  : Variable types of arguments (a.k.a print msg)
        //
        // 'DebugLog:9' if IsEnabledDebugLog( cfg )
        //  IsEnableDebugLog : Is the Debug log enable
        //
        //  Inputs :
        //    cfg : Configuration structure
        //
        //  Outputs :
        //  Value : Boolean Value. TRUE means the debug log is enable.
        //
        // 'IsEnabledDebugLog:13' value = false;
        // 'IsEnabledDebugLog:15' if bitget( DebugConfig, int32( cfg ) )
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:16' value = true;
            //    Output
            //    stdout : 1
            //    stderr : 2
            // 'DebugLog:13' output  = 1;
            // 'DebugLog:14' fprintf( output, varargin{ : } );
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'splitQueue:14' DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );
        //  DebugLog : Print msg in log pipe.
        //
        //  Inputs :
        //  cfg       : The configuration structure
        //  varargin  : Variable types of arguments (a.k.a print msg)
        //
        // 'DebugLog:9' if IsEnabledDebugLog( cfg )
        //  IsEnableDebugLog : Is the Debug log enable
        //
        //  Inputs :
        //    cfg : Configuration structure
        //
        //  Outputs :
        //  Value : Boolean Value. TRUE means the debug log is enable.
        //
        // 'IsEnabledDebugLog:13' value = false;
        // 'IsEnabledDebugLog:15' if bitget( DebugConfig, int32( cfg ) )
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:16' value = true;
            //    Output
            //    stdout : 1
            //    stderr : 2
            // 'DebugLog:13' output  = 1;
            // 'DebugLog:14' fprintf( output, varargin{ : } );
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'splitQueue:17' N = ctx.q_smooth.size;
        N = ctx->q_smooth.size();
        // 'splitQueue:19' for k = 1 : N
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
            t9_delta = e_expl_temp.delta;
            t9_theta = e_expl_temp.theta;
            t9_pitch = e_expl_temp.pitch;
            t9_sp_index = e_expl_temp.sp_index;
            t9_i_begin_sp = e_expl_temp.i_begin_sp;
            t9_i_end_sp = e_expl_temp.i_end_sp;
            t9_index_smooth = e_expl_temp.index_smooth;
            t9_UseConstJerk = e_expl_temp.UseConstJerk;
            t9_ConstJerk = e_expl_temp.ConstJerk;
            t9_a_param = e_expl_temp.a_param;
            t9_b_param = e_expl_temp.b_param;
            loop_ub = e_expl_temp.R0.size[0];
            b_loop_ub = e_expl_temp.R1.size[0];
            c_loop_ub = e_expl_temp.CoeffP5.size(1);
            d_loop_ub = e_expl_temp.Coeff.size(0);
        }
        for (int k{0}; k < i; k++) {
            int b_resCount;
            int resCount;
            // 'splitQueue:20' ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + N, mfilename
            // );
            resCount = sprintf(&st[0], "%d", ctx->k0);
            if (resCount - 1 >= 0) {
                std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
            }
            b_resCount = sprintf(&b_st[0], "%u", N);
            if (b_resCount - 1 >= 0) {
                std::copy(&b_st[0], &b_st[b_resCount], &b_obj2Value_data[0]);
            }
            obj.Value.size[0] = 1;
            obj.Value.size[1] = (resCount + b_resCount) + 1;
            if (resCount - 1 >= 0) {
                std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[0]);
            }
            obj.Value.data[resCount] = '/';
            for (int i1{0}; i1 < b_resCount; i1++) {
                obj.Value.data[(i1 + resCount) + 1] = b_obj2Value_data[i1];
            }
            i_ocn_print(ctx->cfg.ENABLE_PRINT_MSG, &obj);
            // 'splitQueue:21' ctx.k0  = ctx.k0 + 1;
            ctx->k0++;
            // 'splitQueue:24' ctx     = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
            ctx->q_smooth.get(k + 1U, &curv);
            //  SplitCurvStruct : Split the curv structs based on the cutting lengeht
            //  the zero speed curve are also cutted during this step.
            //
            //  Inputs  :
            //  ctx   : The context
            //  curv  : The curv struct
            //
            //  Outputs  :
            //  ctx   : The modified context
            //
            // 'splitCurvStruct:14' if( ~coder.target( 'MATLAB' ) )
            // 'splitCurvStruct:14' curvE = constrCurvStructType;
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
            for (int i2{0}; i2 < loop_ub; i2++) {
                curvE.R0[i2] = e_expl_temp.R0.data[i2];
            }
            curvE.R1.set_size(e_expl_temp.R1.size[0]);
            for (int i3{0}; i3 < b_loop_ub; i3++) {
                curvE.R1[i3] = e_expl_temp.R1.data[i3];
            }
            curvE.delta = t9_delta;
            curvE.CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
            curvE.evec[0] = e_expl_temp.evec[0];
            curvE.CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
            curvE.evec[1] = e_expl_temp.evec[1];
            curvE.CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
            curvE.evec[2] = e_expl_temp.evec[2];
            curvE.theta = t9_theta;
            curvE.pitch = t9_pitch;
            curvE.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
            for (int i4{0}; i4 < c_loop_ub; i4++) {
                int e_loop_ub;
                e_loop_ub = e_expl_temp.CoeffP5.size(0);
                for (int i5{0}; i5 < e_loop_ub; i5++) {
                    curvE.CoeffP5[i5 + curvE.CoeffP5.size(0) * i4] =
                        e_expl_temp.CoeffP5[i5 + e_expl_temp.CoeffP5.size(0) * i4];
                }
            }
            curvE.sp_index = t9_sp_index;
            curvE.i_begin_sp = t9_i_begin_sp;
            curvE.i_end_sp = t9_i_end_sp;
            curvE.index_smooth = t9_index_smooth;
            curvE.UseConstJerk = t9_UseConstJerk;
            curvE.ConstJerk = t9_ConstJerk;
            curvE.Coeff.set_size(e_expl_temp.Coeff.size(0));
            for (int i6{0}; i6 < d_loop_ub; i6++) {
                curvE.Coeff[i6] = e_expl_temp.Coeff[i6];
            }
            curvE.a_param = t9_a_param;
            curvE.b_param = t9_b_param;
            // 'splitCurvStruct:16' if ( curv.Info.Type == CurveType.TransP5 )
            if (curv.Info.Type == CurveType_TransP5) {
                // 'splitCurvStruct:17' ctx.q_split.push( curv );
                ctx->q_split.push(&curv);
            } else {
                bool exitg1;
                bool guard1;
                bool guard2;
                bool zeroFlag;
                // 'splitCurvStruct:20' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //
                //  Inputs :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                //
                //  Outputs :
                //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
                //
                // 'isAZeroStart:11' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                //  getZspdmode: Get the current zero speed mode
                //
                //  Inputs :
                //    speed    : structure with zspdmode for the speed
                //
                //  Outputs :
                //    zspdmode : Zero speed mode
                //    error    : Error bolean value. TRUE if no zspdmode has been found.
                //
                // 'getZspdmode:13' error = false;
                // 'getZspdmode:15' if( isenum( speed ) )
                // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                // 'isAZeroStart:15' if( error )
                // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:19' zeroFlag = true;
                    zeroFlag = true;
                }
                guard1 = false;
                guard2 = false;
                if (zeroFlag) {
                    double Lcut;
                    double b_L;
                    //  cut zero Start
                    // 'splitCurvStruct:22' [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
                    //  cutZeroStart : Cut the start of the given to handle the zero speed.
                    //
                    //  Inputs :
                    //  ctx       : The context used in the computational chain.
                    //  curv      : The curve to cut the end.
                    //
                    //  Outputs :
                    //  ret       : The returned value of the operation : 1 means
                    //  curvLeft  : Resulting ZN Curve struct with constant jerk speed profile
                    //  curvRight : Resulting NN Curve struct
                    //
                    // 'cutZeroStart:14' L       = LengthCurv( ctx, curv, 0, 1 );
                    b_L = c_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                       ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                       ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                                       ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                       ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, &curv);
                    // 'cutZeroStart:15' Lcut    = ctx.cfg.LSplitZero;
                    Lcut = ctx->cfg.LSplitZero;
                    // 'cutZeroStart:17' if( Lcut > L / 3 )
                    if (ctx->cfg.LSplitZero > b_L / 3.0) {
                        // 'cutZeroStart:17' Lcut = L / 3;
                        Lcut = b_L / 3.0;
                    }
                    // 'cutZeroStart:19' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 0, Lcut,
                    // false );
                    curvS = curv;
                    c_cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                    ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                    ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                    ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                    &curvS, Lcut, &ret, &b_curv);
                    // 'cutZeroStart:21' if( ret < 0 )
                    if (ret < 0.0) {
                        // 'cutZeroStart:22' curv1                   = curv;
                        curvS = curv;
                        // 'cutZeroStart:23' curv1.UseConstJerk      = true;
                        curvS.UseConstJerk = true;
                        // 'cutZeroStart:24' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
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
                        // 'cutZeroStart:25' curv1.ConstJerk         = jps;
                    } else {
                        double x;
                        int b_scalarLB;
                        int b_vectorUB;
                        int c_scalarLB;
                        int c_vectorUB;
                        int d_scalarLB;
                        int d_vectorUB;
                        int e_scalarLB;
                        int e_vectorUB;
                        int end;
                        int partialTrueCount;
                        int rd;
                        int rdd;
                        int scalarLB;
                        int trueCount;
                        int vectorUB;
                        // 'cutZeroStart:26' else
                        // 'cutZeroStart:27' ocn_assert( check_curv_length( ctx, curv1, Lcut ),
                        // "Curve Length not valide", mfilename ); 'cutZeroStart:112' tol = 1E-1;
                        // 'cutZeroStart:114' isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L )
                        // <= tol );
                        x = c_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                         ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curvS) -
                            Lcut;
                        bb_ocn_assert(std::abs(x) <= 0.1);
                        // 'cutZeroStart:28' curv1.UseConstJerk      = true;
                        curvS.UseConstJerk = true;
                        // 'cutZeroStart:29' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1,
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
                        // 'cutZeroStart:30' curv1.ConstJerk         = jps;
                        // 'cutZeroStart:31' curv2.UseConstJerk      = false;
                        b_curv.UseConstJerk = false;
                        // 'cutZeroStart:32' check_continuity( ctx, curv, curv1, curv2 );
                        // 'cutZeroStart:65' curv_vec    = [ curv; curv1; curv2 ];
                        curv_vec[0] = curv;
                        curv_vec[1] = curvS;
                        curv_vec[2] = b_curv;
                        // 'cutZeroStart:66' u_vec       = [ 0, 1 ];
                        // 'cutZeroStart:67' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2,
                        // 3 );
                        end = ctx->cfg.maskTot.size[1] - 1;
                        trueCount = 0;
                        for (int b_i{0}; b_i <= end; b_i++) {
                            if (ctx->cfg.maskTot.data[b_i]) {
                                trueCount++;
                            }
                        }
                        partialTrueCount = 0;
                        for (int c_i{0}; c_i <= end; c_i++) {
                            if (ctx->cfg.maskTot.data[c_i]) {
                                tmp_data[partialTrueCount] = static_cast<signed char>(c_i + 1);
                                partialTrueCount++;
                            }
                        }
                        if (trueCount != 0) {
                            for (int t{0}; t < 3; t++) {
                                for (int b_t{0}; b_t < 2; b_t++) {
                                    for (int c_k{0}; c_k < trueCount; c_k++) {
                                        r_data[(c_k + trueCount * b_t) + trueCount * 2 * t] =
                                            curv.R0[tmp_data[c_k] - 1];
                                    }
                                }
                            }
                        }
                        // 'cutZeroStart:68' rd          = r;
                        // 'cutZeroStart:69' rdd         = r;
                        for (int i10{0}; i10 < 3; i10++) {
                            for (int i11{0}; i11 < 2; i11++) {
                                for (int i12{0}; i12 < trueCount; i12++) {
                                    rd_data[(i12 + trueCount * i11) + trueCount * 2 * i10] =
                                        r_data[(i12 + trueCount * i11) + trueCount * 2 * i10];
                                }
                                for (int i13{0}; i13 < trueCount; i13++) {
                                    rdd_data[(i13 + trueCount * i11) + trueCount * 2 * i10] =
                                        r_data[(i13 + trueCount * i11) + trueCount * 2 * i10];
                                }
                            }
                        }
                        // 'cutZeroStart:71' for j = 1 : 3
                        rd = trueCount - 1;
                        scalarLB = (trueCount / 2) << 1;
                        vectorUB = scalarLB - 2;
                        rdd = trueCount - 1;
                        b_scalarLB = (trueCount / 2) << 1;
                        b_vectorUB = b_scalarLB - 2;
                        for (int b_j{0}; b_j < 3; b_j++) {
                            double c;
                            int h_loop_ub;
                            int i_loop_ub;
                            int j_loop_ub;
                            // 'cutZeroStart:72' [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] =
                            // ... 'cutZeroStart:73'         EvalCurvStruct( ctx, curv_vec( j ),
                            // u_vec );
                            j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                             ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                             ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                             ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                             ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, &curv_vec[b_j], r1, r2, r3);
                            h_loop_ub = r1.size(0);
                            i_loop_ub = r2.size(0);
                            j_loop_ub = r3.size(0);
                            for (int i14{0}; i14 < 2; i14++) {
                                for (int i15{0}; i15 < h_loop_ub; i15++) {
                                    r_data[(i15 + trueCount * i14) + trueCount * 2 * b_j] =
                                        r1[i15 + r1.size(0) * i14];
                                }
                                for (int i17{0}; i17 < i_loop_ub; i17++) {
                                    rd_data[(i17 + trueCount * i14) + trueCount * 2 * b_j] =
                                        r2[i17 + r2.size(0) * i14];
                                }
                                for (int i19{0}; i19 < j_loop_ub; i19++) {
                                    rdd_data[(i19 + trueCount * i14) + trueCount * 2 * b_j] =
                                        r3[i19 + r3.size(0) * i14];
                                }
                            }
                            // 'cutZeroStart:74' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j
                            // ).a_param;
                            for (int i16{0}; i16 < 2; i16++) {
                                for (int i18{0}; i18 <= vectorUB; i18 += 2) {
                                    __m128d r4;
                                    r4 = _mm_loadu_pd(
                                        &rd_data[(i18 + trueCount * i16) + trueCount * 2 * b_j]);
                                    _mm_storeu_pd(
                                        &b_rd_data[i18 + trueCount * i16],
                                        _mm_div_pd(r4, _mm_set1_pd(curv_vec[b_j].a_param)));
                                }
                                for (int i18{scalarLB}; i18 <= rd; i18++) {
                                    b_rd_data[i18 + trueCount * i16] =
                                        rd_data[(i18 + trueCount * i16) + trueCount * 2 * b_j] /
                                        curv_vec[b_j].a_param;
                                }
                            }
                            double c_tmp;
                            // 'cutZeroStart:75' if( 1 )
                            // 'cutZeroStart:76' rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j
                            // ).a_param^2;
                            c_tmp = curv_vec[b_j].a_param;
                            c = c_tmp * c_tmp;
                            for (int i20{0}; i20 < 2; i20++) {
                                for (int i22{0}; i22 < trueCount; i22++) {
                                    rd_data[(i22 + trueCount * i20) + trueCount * 2 * b_j] =
                                        b_rd_data[i22 + trueCount * i20];
                                }
                                for (int i24{0}; i24 <= b_vectorUB; i24 += 2) {
                                    __m128d r5;
                                    r5 = _mm_loadu_pd(
                                        &rdd_data[(i24 + trueCount * i20) + trueCount * 2 * b_j]);
                                    _mm_storeu_pd(&b_rdd_data[i24 + trueCount * i20],
                                                  _mm_div_pd(r5, _mm_set1_pd(c)));
                                }
                                for (int i24{b_scalarLB}; i24 <= rdd; i24++) {
                                    b_rdd_data[i24 + trueCount * i20] =
                                        rdd_data[(i24 + trueCount * i20) + trueCount * 2 * b_j] / c;
                                }
                            }
                            for (int i21{0}; i21 < 2; i21++) {
                                for (int i23{0}; i23 < trueCount; i23++) {
                                    rdd_data[(i23 + trueCount * i21) + trueCount * 2 * b_j] =
                                        b_rdd_data[i23 + trueCount * i21];
                                }
                            }
                        }
                        // 'cutZeroStart:82' ind1 = [ 1, 1; 1, 2; 2, 2 ];
                        // 'cutZeroStart:83' ind2 = [ 2, 1; 3, 2; 3, 1 ];
                        // 'cutZeroStart:85' for j = 1 : 3
                        c_scalarLB = (trueCount / 2) << 1;
                        c_vectorUB = c_scalarLB - 2;
                        d_scalarLB = (trueCount / 2) << 1;
                        d_vectorUB = d_scalarLB - 2;
                        e_scalarLB = (trueCount / 2) << 1;
                        e_vectorUB = e_scalarLB - 2;
                        for (int c_j{0}; c_j < 3; c_j++) {
                            int b_ind1_tmp;
                            int b_ind2_tmp;
                            int g_k;
                            int h_k;
                            int i_k;
                            int ind1_tmp;
                            int ind2_tmp;
                            int k_loop_ub;
                            int l_loop_ub;
                            int m_loop_ub;
                            bool b_varargout_1;
                            bool c_varargout_1;
                            bool varargout_1;
                            // 'cutZeroStart:86' r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
                            // 'cutZeroStart:87' r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
                            // 'cutZeroStart:88' r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
                            // 'cutZeroStart:89' r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
                            // 'cutZeroStart:90' r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
                            // 'cutZeroStart:91' r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
                            // 'cutZeroStart:92' assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
                            // 'cutZeroStart:99' diff_r      = abs( r1    -r2 );
                            ind1_tmp = ind1[1][c_j];
                            b_ind1_tmp = ind1[0][c_j];
                            ind2_tmp = ind2[1][c_j];
                            b_ind2_tmp = ind2[0][c_j];
                            c_x.set_size(trueCount);
                            for (int i25{0}; i25 <= c_vectorUB; i25 += 2) {
                                __m128d r6;
                                __m128d r7;
                                r6 = _mm_loadu_pd(&r_data[(i25 + trueCount * (ind1_tmp - 1)) +
                                                          trueCount * 2 * (b_ind1_tmp - 1)]);
                                r7 = _mm_loadu_pd(&r_data[(i25 + trueCount * (ind2_tmp - 1)) +
                                                          trueCount * 2 * (b_ind2_tmp - 1)]);
                                _mm_storeu_pd(&c_x[i25], _mm_sub_pd(r6, r7));
                            }
                            for (int i25{c_scalarLB}; i25 < trueCount; i25++) {
                                c_x[i25] = r_data[(i25 + trueCount * (ind1_tmp - 1)) +
                                                  trueCount * 2 * (b_ind1_tmp - 1)] -
                                           r_data[(i25 + trueCount * (ind2_tmp - 1)) +
                                                  trueCount * 2 * (b_ind2_tmp - 1)];
                            }
                            z1.set_size(c_x.size(0));
                            if (c_x.size(0) != 0) {
                                int i26;
                                i26 = c_x.size(0);
                                for (int d_k{0}; d_k < i26; d_k++) {
                                    z1[d_k] = std::abs(c_x[d_k]);
                                }
                            }
                            // 'cutZeroStart:100' diff_rd     = abs( r1d   -r2d );
                            c_x.set_size(trueCount);
                            for (int i27{0}; i27 <= d_vectorUB; i27 += 2) {
                                __m128d r8;
                                __m128d r9;
                                r8 = _mm_loadu_pd(&rd_data[(i27 + trueCount * (ind1_tmp - 1)) +
                                                           trueCount * 2 * (b_ind1_tmp - 1)]);
                                r9 = _mm_loadu_pd(&rd_data[(i27 + trueCount * (ind2_tmp - 1)) +
                                                           trueCount * 2 * (b_ind2_tmp - 1)]);
                                _mm_storeu_pd(&c_x[i27], _mm_sub_pd(r8, r9));
                            }
                            for (int i27{d_scalarLB}; i27 < trueCount; i27++) {
                                c_x[i27] = rd_data[(i27 + trueCount * (ind1_tmp - 1)) +
                                                   trueCount * 2 * (b_ind1_tmp - 1)] -
                                           rd_data[(i27 + trueCount * (ind2_tmp - 1)) +
                                                   trueCount * 2 * (b_ind2_tmp - 1)];
                            }
                            b_z1.set_size(c_x.size(0));
                            if (c_x.size(0) != 0) {
                                int i28;
                                i28 = c_x.size(0);
                                for (int e_k{0}; e_k < i28; e_k++) {
                                    b_z1[e_k] = std::abs(c_x[e_k]);
                                }
                            }
                            // 'cutZeroStart:101' diff_rdd    = abs( r1dd  -r2dd );
                            c_x.set_size(trueCount);
                            for (int i29{0}; i29 <= e_vectorUB; i29 += 2) {
                                __m128d r10;
                                __m128d r11;
                                r10 = _mm_loadu_pd(&rdd_data[(i29 + trueCount * (ind1_tmp - 1)) +
                                                             trueCount * 2 * (b_ind1_tmp - 1)]);
                                r11 = _mm_loadu_pd(&rdd_data[(i29 + trueCount * (ind2_tmp - 1)) +
                                                             trueCount * 2 * (b_ind2_tmp - 1)]);
                                _mm_storeu_pd(&c_x[i29], _mm_sub_pd(r10, r11));
                            }
                            for (int i29{e_scalarLB}; i29 < trueCount; i29++) {
                                c_x[i29] = rdd_data[(i29 + trueCount * (ind1_tmp - 1)) +
                                                    trueCount * 2 * (b_ind1_tmp - 1)] -
                                           rdd_data[(i29 + trueCount * (ind2_tmp - 1)) +
                                                    trueCount * 2 * (b_ind2_tmp - 1)];
                            }
                            c_z1.set_size(c_x.size(0));
                            if (c_x.size(0) != 0) {
                                int i30;
                                i30 = c_x.size(0);
                                for (int f_k{0}; f_k < i30; f_k++) {
                                    c_z1[f_k] = std::abs(c_x[f_k]);
                                }
                            }
                            // 'cutZeroStart:103' tol = 1E-6;
                            // 'cutZeroStart:106' ocn_assert( all( diff_r    < tol, 'all' ),
                            // "Continuity C0 failed", mfilename );
                            d_x.set_size(z1.size(0));
                            k_loop_ub = z1.size(0);
                            for (int i31{0}; i31 < k_loop_ub; i31++) {
                                d_x[i31] = (z1[i31] < 1.0E-6);
                            }
                            varargout_1 = true;
                            g_k = 0;
                            exitg1 = false;
                            while ((!exitg1) && (g_k <= d_x.size(0) - 1)) {
                                if (!d_x[g_k]) {
                                    varargout_1 = false;
                                    exitg1 = true;
                                } else {
                                    g_k++;
                                }
                            }
                            cb_ocn_assert(varargout_1);
                            // 'cutZeroStart:107' ocn_assert( all( diff_rd   < tol, 'all' ),
                            // "Continuity C1 failed", mfilename );
                            d_x.set_size(b_z1.size(0));
                            l_loop_ub = b_z1.size(0);
                            for (int i32{0}; i32 < l_loop_ub; i32++) {
                                d_x[i32] = (b_z1[i32] < 1.0E-6);
                            }
                            b_varargout_1 = true;
                            h_k = 0;
                            exitg1 = false;
                            while ((!exitg1) && (h_k <= d_x.size(0) - 1)) {
                                if (!d_x[h_k]) {
                                    b_varargout_1 = false;
                                    exitg1 = true;
                                } else {
                                    h_k++;
                                }
                            }
                            db_ocn_assert(b_varargout_1);
                            // 'cutZeroStart:108' ocn_assert( all( diff_rdd   < tol, 'all'
                            // ),"Continuity C2 failed", mfilename );
                            d_x.set_size(c_z1.size(0));
                            m_loop_ub = c_z1.size(0);
                            for (int i33{0}; i33 < m_loop_ub; i33++) {
                                d_x[i33] = (c_z1[i33] < 1.0E-6);
                            }
                            c_varargout_1 = true;
                            i_k = 0;
                            exitg1 = false;
                            while ((!exitg1) && (i_k <= d_x.size(0) - 1)) {
                                if (!d_x[i_k]) {
                                    c_varargout_1 = false;
                                    exitg1 = true;
                                } else {
                                    i_k++;
                                }
                            }
                            eb_ocn_assert(c_varargout_1);
                        }
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
                    // 'splitCurvStruct:23' ctx.q_split.push( curvS );
                    ctx->q_split.push(&curvS);
                    // 'splitCurvStruct:24' if( ret < 0 )
                    if (ret >= 0.0) {
                        guard2 = true;
                    }
                } else {
                    guard2 = true;
                }
                if (guard2) {
                    bool b_zeroFlag;
                    // 'splitCurvStruct:27' hasEndSpeed = false;
                    hasEndSpeed = false;
                    // 'splitCurvStruct:28' if( isAZeroEnd( curv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //
                    //  Inputs :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    //
                    //  Outputs :
                    //  zeroFlag : Boolean value. TRUE mean zero flag
                    // 'isAZeroEnd:10' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
                    //  getZspdmode: Get the current zero speed mode
                    //
                    //  Inputs :
                    //    speed    : structure with zspdmode for the speed
                    //
                    //  Outputs :
                    //    zspdmode : Zero speed mode
                    //    error    : Error bolean value. TRUE if no zspdmode has been found.
                    //
                    // 'getZspdmode:13' error = false;
                    // 'getZspdmode:15' if( isenum( speed ) )
                    // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:14' if( error )
                    // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
                    if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                        (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:18' zeroFlag = true;
                        b_zeroFlag = true;
                    }
                    if (b_zeroFlag) {
                        //  cut zero End
                        // 'splitCurvStruct:30' [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
                        cutZeroEnd(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax,
                                   ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &ctx->kin, &curv, &c_ret, &b_curv,
                                   &curvE);
                        curv = b_curv;
                        // 'splitCurvStruct:31' if( ret < 0 )
                        if (c_ret < 0.0) {
                            // 'splitCurvStruct:32' ctx.q_split.push( curv );
                            ctx->q_split.push(&b_curv);
                        } else {
                            // 'splitCurvStruct:35' hasEndSpeed     = true;
                            hasEndSpeed = true;
                            guard1 = true;
                        }
                    } else {
                        guard1 = true;
                    }
                }
                if (guard1) {
                    // 'splitCurvStruct:38' if( ctx.cfg.SplitSpecialSpline && curv.Info.Type ==
                    // CurveType.Spline )
                    if (ctx->cfg.SplitSpecialSpline && (curv.Info.Type == CurveType_Spline)) {
                        double uMax;
                        double uPrevious;
                        double work_data;
                        int dimSize;
                        int f_loop_ub;
                        int g_loop_ub;
                        int i9;
                        // 'splitCurvStruct:39' bspline     = ctx.q_spline.get( curv.sp_index );
                        ctx->q_spline.get(curv.sp_index, &f_expl_temp);
                        // 'splitCurvStruct:40' breakPoints = bspline.sp.Bl.breakpoints;
                        // 'splitCurvStruct:41' uMin        = curv.b_param;
                        // 'splitCurvStruct:42' uMax        = curv.b_param + curv.a_param;
                        uMax = curv.b_param + curv.a_param;
                        // 'splitCurvStruct:43' ind         = find( breakPoints > uMin & breakPoints
                        // < uMax ); 'splitCurvStruct:44' breakPoints = [ uMin, breakPoints( ind ),
                        // uMax ] ;
                        g_expl_temp.set_size(1, f_expl_temp.sp.Bl.breakpoints.size(1));
                        f_loop_ub = f_expl_temp.sp.Bl.breakpoints.size(1);
                        for (int i7{0}; i7 < f_loop_ub; i7++) {
                            double d;
                            d = f_expl_temp.sp.Bl.breakpoints[i7];
                            g_expl_temp[i7] = ((d > curv.b_param) && (d < uMax));
                        }
                        coder::d_eml_find(g_expl_temp, r);
                        breakPoints.set_size(1, r.size(1) + 2);
                        breakPoints[0] = curv.b_param;
                        g_loop_ub = r.size(1);
                        for (int i8{0}; i8 < g_loop_ub; i8++) {
                            breakPoints[i8 + 1] = f_expl_temp.sp.Bl.breakpoints[r[i8] - 1];
                        }
                        breakPoints[r.size(1) + 1] = uMax;
                        // 'splitCurvStruct:45' deltaU      = diff( breakPoints );
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
                        // 'splitCurvStruct:46' uPrevious   = uMin;
                        uPrevious = curv.b_param;
                        // 'splitCurvStruct:47' for j = 1 : length( deltaU )
                        i9 = b_y1.size(1);
                        for (int j{0}; j < i9; j++) {
                            double d2;
                            // 'splitCurvStruct:48' curvSplited         = curv;
                            curvSplited = curv;
                            // 'splitCurvStruct:50' curvSplited.a_param = deltaU( j );
                            d2 = b_y1[j];
                            curvSplited.a_param = d2;
                            // 'splitCurvStruct:52' curvSplited.b_param = uPrevious;
                            curvSplited.b_param = uPrevious;
                            // 'splitCurvStruct:53' uPrevious           = curvSplited.a_param +
                            // curvSplited.b_param;
                            uPrevious += d2;
                            // 'splitCurvStruct:54' ctx.q_split.push( curvSplited );
                            ctx->q_split.push(&curvSplited);
                        }
                    } else {
                        double L;
                        double L_split;
                        double b_N;
                        int b_k;
                        // 'splitCurvStruct:56' else
                        // 'splitCurvStruct:57' L       = LengthCurv( ctx, curv, 0, 1 );
                        L = c_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                         ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curv);
                        // 'splitCurvStruct:58' L_split = ctx.cfg.LSplit;
                        //  Number of sub segments
                        // 'splitCurvStruct:61' N = ceil( L / L_split );
                        b_N = std::ceil(L / ctx->cfg.LSplit);
                        //  Length of the sub segments
                        // 'splitCurvStruct:64' L_split = L / N;
                        L_split = L / b_N;
                        // 'splitCurvStruct:66' for k = 1 : N - 1
                        b_k = 0;
                        exitg1 = false;
                        while ((!exitg1) && (b_k <= static_cast<int>(b_N - 1.0) - 1)) {
                            // 'splitCurvStruct:67' [ ret, curvSplited, curv ] = cutCurvStruct( ctx,
                            // curv, 0, L_split, false );
                            curvSplited = curv;
                            c_cutCurvStruct(
                                &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curvSplited,
                                L_split, &b_ret, &curv);
                            // 'splitCurvStruct:68' if( ret < 0 )
                            if (b_ret < 0.0) {
                                exitg1 = true;
                            } else {
                                double b_x;
                                // 'splitCurvStruct:70' ocn_assert( check_curv_length( ctx,
                                // curvSplited, L_split ), ... 'splitCurvStruct:71' "Curve Length
                                // not valide", mfilename ); 'splitCurvStruct:86' tol = 1E-3;
                                // 'splitCurvStruct:88' isValid = ( abs( LengthCurv( ctx, curv, 0, 1
                                // ) - L ) <= tol );
                                b_x = c_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data,
                                                   ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                                   ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                                   ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                                   ctx->cfg.indRot, ctx->cfg.NumberAxis,
                                                   ctx->cfg.NCart, ctx->cfg.NRot,
                                                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                                   &curvSplited) -
                                      L_split;
                                jb_ocn_assert(std::abs(b_x) <= 0.001);
                                // 'splitCurvStruct:73' ctx.q_split.push( curvSplited );
                                ctx->q_split.push(&curvSplited);
                                b_k++;
                            }
                        }
                        // 'splitCurvStruct:75' ctx.q_split.push( curv );
                        ctx->q_split.push(&curv);
                    }
                    // 'splitCurvStruct:78' if( hasEndSpeed )
                    if (hasEndSpeed) {
                        //  cut zero End
                        // 'splitCurvStruct:80' ctx.q_split.push( curvE );
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
