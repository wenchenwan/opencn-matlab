//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:40:50
//

// Include Files
#include "feedratePlanning.h"
#include "EvalCurvStruct.h"
#include "FeedratePlanning_LP.h"
#include "calcZeroConstraints.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "sum.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
#include <stdio.h>

// Variable Definitions
namespace ocn {
static double kopt;

}

// Function Definitions
//
// function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
//
// FeedratePlanning : Compute the optimal feedrate w.r.t to a set of
//  constraints.
//
// Arguments    : b_FeedoptContext *ctx
//                bool *optimized
//                CurvStruct *opt_struct
//                bool *quit
// Return Type  : void
//
namespace ocn {
void feedratePlanning(b_FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct, bool *quit)
{
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<CurvStruct, 2U> window;
    ::coder::array<double, 2U> Coeff;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    Axes params_tmp_tool_offset;
    CurvStruct curv;
    CurvStruct opt_struct_tmp;
    SplineStruct params_tmp_spline;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_tool_backangle;
    double params_tmp_tool_diameter;
    double params_tmp_tool_frontangle;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_tool_orientation;
    int params_tmp_tool_pocketno;
    int params_tmp_tool_toolno;
    int status;
    bool b_optimized;
    bool b_quit;
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    bool success;
    CurveType params_tmp_gcodeInfoStruct_Type;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    // 'feedratePlanning:6' if( isempty( kopt ) )
    // 'feedratePlanning:7' opt_struct  = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_tmp_gcodeInfoStruct_Type, &params_tmp_gcodeInfoStruct_zspdmode,
        &params_tmp_gcodeInfoStruct_TRAFO, &params_tmp_gcodeInfoStruct_HSC,
        &params_tmp_gcodeInfoStruct_FeedRate, &params_tmp_gcodeInfoStruct_SpindleSpeed,
        &params_tmp_gcodeInfoStruct_gcode_source_line, &params_tmp_gcodeInfoStruct_G91,
        &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_tool_toolno, &params_tmp_tool_pocketno,
        &params_tmp_tool_offset, &params_tmp_tool_diameter, &params_tmp_tool_frontangle,
        &params_tmp_tool_backangle, &params_tmp_tool_orientation, &params_tmp_spline, params_tmp_R0,
        params_tmp_R1, params_tmp_Cprim, &expl_temp, params_tmp_evec, &b_expl_temp, &c_expl_temp,
        params_tmp_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
        params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
        params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
        params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
        params_tmp_gcodeInfoStruct_G91_1, params_tmp_tool_toolno, params_tmp_tool_pocketno,
        &params_tmp_tool_offset, params_tmp_tool_diameter, params_tmp_tool_frontangle,
        params_tmp_tool_backangle, params_tmp_tool_orientation, &params_tmp_spline, params_tmp_R0,
        params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &opt_struct_tmp);
    *opt_struct = opt_struct_tmp;
    //  Type of returned curvStruct
    // 'feedratePlanning:8' quit        = false;
    b_quit = false;
    //  Flag used to quit the optimization
    // 'feedratePlanning:9' optimized   = false;
    b_optimized = false;
    //  Does the optimization successed
    // 'feedratePlanning:10' ctx.op      = Fopt.Opt;
    ctx->op = Fopt_Opt;
    //  Current state of the FSM
    //  Check if empty queue after splitting. If yes, stop optimization
    // 'feedratePlanning:13' if ctx.q_split.isempty
    if (ctx->q_split.isempty()) {
        // 'feedratePlanning:13' [ ctx.op, quit ] = empty_queue_split();
        //  Treat the case of an empty queue after splitting operation
        // 'feedratePlanning:106' if coder.target( 'MATLAB' )
        // 'feedratePlanning:109' DebugLog( DebugCfg.Validate, 'Queue empty...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Queue empty...\n");
            fflush(stdout);
        }
        // 'feedratePlanning:110' op      = Fopt.Finished;
        // 'feedratePlanning:111' quit    = true;
        ctx->op = Fopt_Finished;
        b_quit = true;
    } else {
        // 'feedratePlanning:15' if coder.target( 'MATLAB' )
        //  Increment index on q_split
        // 'feedratePlanning:22' if ctx.go_next
        if (ctx->go_next) {
            // 'feedratePlanning:22' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
        }
        // 'feedratePlanning:24' if ( ctx.k0 <= ctx.q_split.size )
        if (static_cast<double>(ctx->k0) <= ctx->q_split.size()) {
            // 'feedratePlanning:25' if ctx.try_push_again
            if (!ctx->try_push_again) {
                if (!ctx->zero_end) {
                    int NWindow;
                    int b_loop_ub;
                    int curv_ind;
                    int d_loop_ub;
                    unsigned int ind;
                    unsigned int kend;
                    int outsize_idx_1_tmp;
                    int x;
                    unsigned int y;
                    bool exitg1;
                    // 'feedratePlanning:27' elseif ~ctx.zero_end
                    // 'feedratePlanning:29' [ window, NWindow ] = get_window( ctx.k0,
                    // ctx.cfg.NHorz, ctx.q_split ); 'feedratePlanning:116' window = repmat(
                    // constrCurvStructType, 1, NHorz );
                    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                    // 'constrCurvStructType:4' if( nargin > 0 )
                    // 'constrCurvStructType:6' else
                    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                    // 'constrCurvStructType:12' else
                    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                    // params.tool, ... 'constrCurvStructType:14'         params.spline, params.R0,
                    // params.R1, params.Cprim, ... 'constrCurvStructType:15'         params.delta,
                    // params.evec, params.theta, params.pitch, ... 'constrCurvStructType:16'
                    // params.CoeffP5, params.Coeff );
                    outsize_idx_1_tmp = ctx->cfg.NHorz;
                    window.set_size(1, outsize_idx_1_tmp);
                    for (int i{0}; i < outsize_idx_1_tmp; i++) {
                        window[i] = opt_struct_tmp;
                    }
                    // 'feedratePlanning:118' kend = min( double( k0 + NHorz -1 ), q_curves.size );
                    x = (ctx->k0 + outsize_idx_1_tmp) - 1;
                    y = ctx->q_split.size();
                    if (static_cast<double>(x) > y) {
                        kend = y;
                    } else {
                        kend = static_cast<unsigned int>(x);
                    }
                    // 'feedratePlanning:120' ind = 0;
                    ind = 0U;
                    // 'feedratePlanning:122' for curv_ind = k0 : int32( kend )
                    curv_ind = ctx->k0;
                    exitg1 = false;
                    while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
                        // 'feedratePlanning:123' ind = ind + 1;
                        ind++;
                        //  store the value in the queue
                        // 'feedratePlanning:126' curv            = q_curves.get( curv_ind );
                        ctx->q_split.get(curv_ind, &curv);
                        // 'feedratePlanning:127' window( ind )   = curv;
                        window[static_cast<int>(ind) - 1] = curv;
                        //  Check if zero speed at the end
                        // 'feedratePlanning:129' if( isAZeroEnd( curv ) )
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                            (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroEnd:7' zeroFlag = true;
                            exitg1 = true;
                        } else {
                            // 'isAZeroEnd:9' zeroFlag = false;
                            curv_ind++;
                        }
                    }
                    // 'feedratePlanning:132' NWindow = ind;
                    b_window.set_size(1, window.size(1));
                    b_loop_ub = window.size(1);
                    for (int i2{0}; i2 < b_loop_ub; i2++) {
                        b_window[i2] = window[i2];
                    }
                    NWindow = static_cast<int>(ind);
                    // 'feedratePlanning:31' first = window( 1 );
                    // 'feedratePlanning:32' last  = window( NWindow );
                    //  Handle the zero speed at start
                    // 'feedratePlanning:35' if ( isAZeroStart( first ) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((window[0].Info.zspdmode == ZSpdMode_ZN) ||
                        (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
                        int c_loop_ub;
                        int i3;
                        int i4;
                        // 'isAZeroStart:6' zeroFlag = true;
                        // 'feedratePlanning:36' ctx.zero_start  = true;
                        ctx->zero_start = true;
                        // 'feedratePlanning:37' window          = window( 2 : end );
                        if (window.size(1) < 2) {
                            i3 = 0;
                            i4 = 0;
                        } else {
                            i3 = 1;
                            i4 = window.size(1);
                        }
                        c_loop_ub = i4 - i3;
                        b_window.set_size(1, c_loop_ub);
                        for (int i5{0}; i5 < c_loop_ub; i5++) {
                            b_window[i5] = window[i3 + i5];
                        }
                        // 'feedratePlanning:38' NWindow         = NWindow -1;
                        NWindow = static_cast<int>(ind) - 1;
                    } else {
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'feedratePlanning:39' else
                        // 'feedratePlanning:40' ctx.zero_start  = false;
                        ctx->zero_start = false;
                    }
                    //  Handle the zero speed at end
                    // 'feedratePlanning:44' if( isAZeroEnd( last ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_NZ) ||
                        (window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'feedratePlanning:45' NWindow         = NWindow -1;
                        NWindow--;
                    } else {
                        // 'isAZeroEnd:9' zeroFlag = false;
                    }
                    // 'feedratePlanning:48' if( isAZeroEnd( last ) && ~ctx.zero_start )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if (((window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_NZ) ||
                         (window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_ZZ)) &&
                        (!ctx->zero_start)) {
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'feedratePlanning:49' ctx.zero_end    = true;
                        ctx->zero_end = true;
                    } else {
                        // 'isAZeroEnd:9' zeroFlag = false;
                        // 'feedratePlanning:50' else
                        // 'feedratePlanning:51' ctx.zero_end    = false;
                        ctx->zero_end = false;
                    }
                    // 'feedratePlanning:54' if( ctx.zero_start )
                    if (ctx->zero_start) {
                        // 'feedratePlanning:55' [ v_0, at_0 ]   = calcZeroConstraints( ctx, first,
                        // false );
                        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data,
                                            ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                            ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                            ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                            ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                            ctx->cfg.NRot, &window[0], &ctx->v_0, &ctx->at_0);
                        // 'feedratePlanning:56' ctx.v_0         = v_0;
                        // 'feedratePlanning:57' ctx.at_0        = at_0;
                    }
                    // 'feedratePlanning:60' if( ctx.zero_end )
                    if (ctx->zero_end) {
                        double b_unnamed_idx_0;
                        double b_y;
                        double k_vec;
                        double n;
                        double pseudoJerk;
                        double u;
                        double ud;
                        double udd;
                        double unnamed_idx_0;
                        int e_loop_ub;
                        int f_loop_ub;
                        int i9;
                        // 'feedratePlanning:61' [ v_1, at_1 ]   = calcZeroConstraints( ctx, last,
                        // true );
                        //  calcZeroConstraints : Compute the velocity and acceleration
                        //  required for the continuity at zero start.
                        //  Inputs :
                        //  ctx   : The context
                        //  Curv  : The curve
                        //  isEnd : (boolean) Is the end of the curve
                        //  Outputs :
                        //  v_0   : Norm of the velocity
                        //  at_0  : Norm of the tangential acceleration
                        // 'calcZeroConstraints:12' jps = curv.ConstJerk;
                        // 'calcZeroConstraints:14' if( isEnd )
                        // 'calcZeroConstraints:15' k  = 0;
                        // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k,
                        // isEnd );
                        pseudoJerk = window[static_cast<int>(ind) - 1].ConstJerk;
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
                        k_vec = std::pow(6.0 / pseudoJerk, 0.33333333333333331);
                        //  Compute u and its derivatives based on constant jerk
                        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
                        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
                        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
                        ud = pseudoJerk * (k_vec * k_vec) / 2.0;
                        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                        u = pseudoJerk * std::pow(k_vec, 3.0) / 6.0;
                        // 'constJerkU:33' u( u > 1 ) = 1;
                        unnamed_idx_0 = u;
                        if (u > 1.0) {
                            unnamed_idx_0 = 1.0;
                        }
                        // 'constJerkU:34' u( u < 0 ) = 0;
                        b_unnamed_idx_0 = unnamed_idx_0;
                        if (unnamed_idx_0 < 0.0) {
                            b_unnamed_idx_0 = 0.0;
                        }
                        // 'constJerkU:36' if( isEnd )
                        //  Reverse time ( Backward-like integration )
                        // 'constJerkU:37' u    = 1 - u;
                        // 'constJerkU:38' ud   = ud;
                        // 'constJerkU:39' udd  = -udd;
                        udd = -(pseudoJerk * k_vec);
                        // 'constJerkU:40' uddd = uddd;
                        // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx,
                        // curv, u );
                        i_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data,
                                         ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                         ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                         &window[static_cast<int>(ind) - 1], 1.0 - b_unnamed_idx_0,
                                         r0D, r1D, r2D, r3D);
                        // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          =
                        // calcRVAJfromUWithoutCurv( ud, udd, uddd, r0D, ...
                        // 'calcZeroConstraints:25'                           r1D, r2D, r3D );
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
                        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
                        b_y = ud * ud;
                        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec
                        // .* udd_vec + r1D .* uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]
                        // = calcNormVNormAT( V, A, r1D );
                        //  calcNormVNormAT : Compute the norm of velocity and the norm of
                        //  tangential acceleration. Inputs : V     : The velovity vector A     :
                        //  The acceleration vector r1D   : The partial derivative of R Outputs :
                        //  vNorm   : Norm of the velocity
                        //  atNorm  : Norm of the tangential acceleration
                        // 'calcNormVNormAT:12' vNorm   = MyNorm( V );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        r.set_size(r1D.size(0));
                        e_loop_ub = r1D.size(0);
                        for (int i7{0}; i7 < e_loop_ub; i7++) {
                            double varargin_1;
                            varargin_1 = r1D[i7];
                            r[i7] = std::pow(varargin_1, 2.0);
                        }
                        n = std::sqrt(coder::sum(r));
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'calcNormVNormAT:14' atNorm  = MyNorm( A.*t );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'feedratePlanning:62' ctx.v_1         = -v_1;
                        r.set_size(r1D.size(0));
                        f_loop_ub = r1D.size(0);
                        for (int i8{0}; i8 < f_loop_ub; i8++) {
                            double b_varargin_1;
                            b_varargin_1 = r1D[i8] * ud;
                            r[i8] = std::pow(b_varargin_1, 2.0);
                        }
                        ctx->v_1 = -std::sqrt(coder::sum(r));
                        // 'feedratePlanning:63' ctx.at_1        = -at_1;
                        if (r2D.size(0) == 1) {
                            i9 = r1D.size(0);
                        } else {
                            i9 = r2D.size(0);
                        }
                        if ((r2D.size(0) == r1D.size(0)) && (i9 == r1D.size(0))) {
                            int g_loop_ub;
                            r.set_size(r2D.size(0));
                            g_loop_ub = r2D.size(0);
                            for (int i10{0}; i10 < g_loop_ub; i10++) {
                                double c_varargin_1;
                                c_varargin_1 = (r2D[i10] * b_y + r1D[i10] * udd) * (r1D[i10] / n);
                                r[i10] = std::pow(c_varargin_1, 2.0);
                            }
                        } else {
                            binary_expand_op(r, r2D, b_y, r1D, udd, n);
                        }
                        ctx->at_1 = -std::sqrt(coder::sum(r));
                    } else {
                        // 'feedratePlanning:64' else
                        // 'feedratePlanning:65' ctx.v_1         = -ctx.cfg.v_1;
                        ctx->v_1 = -ctx->cfg.v_1;
                        // 'feedratePlanning:66' ctx.at_1        = -ctx.cfg.at_1;
                        ctx->at_1 = -ctx->cfg.at_1;
                    }
                    // 'feedratePlanning:69' [ ctx, Coeff, success, status, msg ] = ...
                    // 'feedratePlanning:70'             FeedratePlanning_LP( ctx, window,
                    // ctx.cfg.amax, ctx.cfg.jmax, ... 'feedratePlanning:71' ctx.BasisVal,
                    // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:72'
                    // ctx.u_vec, NWindow );
                    FeedratePlanning_LP(ctx, b_window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                        ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr,
                                        ctx->u_vec, static_cast<double>(NWindow), Coeff, &success,
                                        &status);
                    // 'feedratePlanning:74' if( success == 1 )
                    //  Optimization succed
                    // 'feedratePlanning:75' optimized   = true;
                    b_optimized = true;
                    // 'feedratePlanning:76' opt_struct  = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                    // 'feedratePlanning:77' opt_struct.Coeff = Coeff( :, 1 );
                    d_loop_ub = Coeff.size(0);
                    opt_struct->Coeff.set_size(Coeff.size(0));
                    for (int i6{0}; i6 < d_loop_ub; i6++) {
                        opt_struct->Coeff[i6] = Coeff[i6];
                    }
                    //  Check if end of the queue
                    // 'feedratePlanning:80' if( ctx.zero_end && ( ctx.k0 + NWindow ) >=
                    // ctx.q_split.size )
                    if (ctx->zero_end &&
                        (static_cast<double>(ctx->k0 + NWindow) >= ctx->q_split.size())) {
                        // 'feedratePlanning:81' ctx.reached_end = true;
                        ctx->reached_end = true;
                    }
                } else {
                    // 'feedratePlanning:87' else
                    // 'feedratePlanning:88' optimized   = true;
                    b_optimized = true;
                    // 'feedratePlanning:89' kopt = kopt + 1;
                    kopt++;
                    // 'feedratePlanning:90' opt_struct = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                    // 'feedratePlanning:92' if( ~isAZeroEnd( opt_struct ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((opt_struct->Info.zspdmode == ZSpdMode_NZ) ||
                        (opt_struct->Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'feedratePlanning:94' else
                        // 'feedratePlanning:95' ctx.zero_end  = false;
                        ctx->zero_end = false;
                        // 'feedratePlanning:96' kopt = 1;
                        kopt = 1.0;
                    } else {
                        int loop_ub;
                        // 'isAZeroEnd:9' zeroFlag = false;
                        // 'feedratePlanning:93' opt_struct.Coeff = ctx.Coeff( :, kopt );
                        loop_ub = ctx->Coeff.size(0);
                        opt_struct->Coeff.set_size(loop_ub);
                        for (int i1{0}; i1 < loop_ub; i1++) {
                            opt_struct->Coeff[i1] =
                                ctx->Coeff[i1 + ctx->Coeff.size(0) * (static_cast<int>(kopt) - 1)];
                        }
                    }
                }
            } else {
                //  Do nothing, we already have the last one optimized
            }
        } else {
            // 'feedratePlanning:99' else
            // 'feedratePlanning:100' ctx.op = Fopt.Finished;
            ctx->op = Fopt_Finished;
        }
    }
    *optimized = b_optimized;
    *quit = b_quit;
}

//
// function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
//
// FeedratePlanning : Compute the optimal feedrate w.r.t to a set of
//  constraints.
//
// Arguments    : void
// Return Type  : void
//
void feedratePlanning_init()
{
    // 'feedratePlanning:6' kopt = 1;
    kopt = 1.0;
}

} // namespace ocn

//
// File trailer for feedratePlanning.cpp
//
// [EOF]
//
