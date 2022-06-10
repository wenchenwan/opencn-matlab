//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "feedratePlanning.h"
#include "EvalCurvStruct.h"
#include "FeedratePlanning_LP.h"
#include "calcNormVNormAT.h"
#include "combineVectorElements.h"
#include "constrCurvStruct.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types31.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Variable Definitions
namespace ocn {
static double kopt;

}

// Function Declarations
namespace ocn {
static void b_binary_expand_op(FeedoptContext *ctx, const ::coder::array<double, 1U> &r2D, double y,
                               const ::coder::array<double, 1U> &r1D, double udd, double n);

}

// Function Definitions
//
// Arguments    : FeedoptContext *ctx
//                const ::coder::array<double, 1U> &r2D
//                double y
//                const ::coder::array<double, 1U> &r1D
//                double udd
//                double n
// Return Type  : void
//
namespace ocn {
static void b_binary_expand_op(FeedoptContext *ctx, const ::coder::array<double, 1U> &r2D, double y,
                               const ::coder::array<double, 1U> &r1D, double udd, double n)
{
    ::coder::array<double, 1U> b_r2D;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (r1D.size(0) == 1) {
        i = r2D.size(0);
    } else {
        i = r1D.size(0);
    }
    b_r2D.set_size(i);
    stride_0_0 = (r2D.size(0) != 1);
    stride_1_0 = (r1D.size(0) != 1);
    stride_2_0 = (r1D.size(0) != 1);
    if (r1D.size(0) == 1) {
        loop_ub = r2D.size(0);
    } else {
        loop_ub = r1D.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_r2D[i1] =
            (r2D[i1 * stride_0_0] * y + r1D[i1 * stride_1_0] * udd) * (r1D[i1 * stride_2_0] / n);
    }
    ctx->at_1 = -coder::b_norm(b_r2D);
}

//
// function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
//
// FeedratePlanning : Compute the optimal feedrate w.r.t to a set of
//  constraints.
//
// Arguments    : FeedoptContext *ctx
//                bool *optimized
//                CurvStruct *opt_struct
//                bool *quit
// Return Type  : void
//
void feedratePlanning(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct, bool *quit)
{
    static const uint64m_T r1{
        {2U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    static const uint64m_T r5{
        {128U, 0U} // chunks
    };
    ::coder::array<CurvStruct, 2U> window;
    ::coder::array<double, 2U> Coeff;
    ::coder::array<double, 2U> params_tmp_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_tmp_spline_Lk;
    ::coder::array<double, 2U> params_tmp_spline_coeff;
    ::coder::array<double, 2U> params_tmp_spline_knots;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<double, 1U> r7;
    CurvStruct curv;
    CurvStruct opt_struct_tmp;
    uint64m_T params_tmp_spline_Bl_handle;
    uint64m_T r;
    uint64m_T r2;
    uint64m_T r4;
    uint64m_T r6;
    double dv[6];
    double dv2[6];
    double dv4[6];
    double dv6[6];
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double dv1[3];
    double dv3[3];
    double dv5[3];
    double dv7[3];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_spline_Ltot;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_spline_Bl_ncoeff;
    int params_tmp_spline_Bl_order;
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
        &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_spline_Bl_ncoeff,
        params_tmp_spline_Bl_breakpoints, &params_tmp_spline_Bl_handle, &params_tmp_spline_Bl_order,
        params_tmp_spline_coeff, params_tmp_spline_knots, &params_tmp_spline_Ltot,
        params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1, params_tmp_Cprim, &expl_temp,
        params_tmp_evec, &b_expl_temp, &c_expl_temp, params_tmp_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
                       params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
                       params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
                       params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
                       params_tmp_gcodeInfoStruct_G91_1, params_tmp_spline_Bl_ncoeff,
                       params_tmp_spline_Bl_breakpoints, params_tmp_spline_Bl_handle,
                       params_tmp_spline_Bl_order, params_tmp_spline_coeff, params_tmp_spline_knots,
                       params_tmp_spline_Ltot, params_tmp_spline_Lk, params_tmp_R0, params_tmp_R1,
                       params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &opt_struct_tmp);
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
        // 'feedratePlanning:95' if coder.target( 'MATLAB' )
        // 'feedratePlanning:98' DebugLog( DebugCfg.Validate, 'Queue empty...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r4.chunks[0U]);
        MultiWordAnd((unsigned int *)&r4.chunks[0U], (unsigned int *)&r5.chunks[0U],
                     (unsigned int *)&r6.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r6.chunks[0U], (unsigned int *)&r3.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Queue empty...\n");
            fflush(stdout);
        }
        // 'feedratePlanning:99' op      = Fopt.Finished;
        // 'feedratePlanning:100' quit    = true;
        ctx->op = Fopt_Finished;
        b_quit = true;
    } else {
        // 'feedratePlanning:16' if IsEnabledDebugLog( DebugCfg.OptimProgress )
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
        MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                     (unsigned int *)&r2.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U])) {
            unsigned int validatedHoleFilling_f2;
            // 'IsEnabledDebugLog:7' value = true;
            // 'feedratePlanning:17' fprintf( '%4d/%u\n', ctx.k0, ctx.q_split.size );
            validatedHoleFilling_f2 = ctx->q_split.size();
            printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
            fflush(stdout);
        }
        //  Increment index on q_split
        // 'feedratePlanning:21' if ctx.go_next
        if (ctx->go_next) {
            // 'feedratePlanning:21' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
        }
        // 'feedratePlanning:23' if ( ctx.k0 <= ctx.q_split.size )
        if (static_cast<double>(ctx->k0) <= ctx->q_split.size()) {
            // 'feedratePlanning:24' if ctx.try_push_again
            if (!ctx->try_push_again) {
                if (!ctx->zero_end) {
                    int NWindow;
                    int curv_ind;
                    unsigned int ind;
                    unsigned int kend;
                    int outsize_idx_1_tmp;
                    int x;
                    unsigned int y;
                    bool exitg1;
                    // 'feedratePlanning:26' elseif ~ctx.zero_end
                    // 'feedratePlanning:28' [ window, NWindow ] = get_window( ctx.k0,
                    // ctx.cfg.NHorz, ctx.q_split ); 'feedratePlanning:105' window = repmat(
                    // constrCurvStructType, 1, NHorz );
                    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                    // 'constrCurvStructType:4' if( nargin > 0 )
                    // 'constrCurvStructType:6' else
                    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                    // 'constrCurvStructType:12' else
                    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                    // params.spline, ... 'constrCurvStructType:14'         params.R0, params.R1,
                    // ... 'constrCurvStructType:15'         params.Cprim, params.delta,
                    // params.evec, params.theta, ... 'constrCurvStructType:16' params.pitch,
                    // params.CoeffP5, params.Coeff );
                    outsize_idx_1_tmp = ctx->cfg.NHorz;
                    window.set_size(1, outsize_idx_1_tmp);
                    for (int i1{0}; i1 < outsize_idx_1_tmp; i1++) {
                        window[i1] = opt_struct_tmp;
                    }
                    // 'feedratePlanning:107' kend = min( double( k0 + NHorz -1 ), q_curves.size );
                    x = (ctx->k0 + outsize_idx_1_tmp) - 1;
                    y = ctx->q_split.size();
                    if (static_cast<double>(x) > y) {
                        kend = y;
                    } else {
                        kend = static_cast<unsigned int>(x);
                    }
                    // 'feedratePlanning:109' ind = 0;
                    ind = 0U;
                    // 'feedratePlanning:110' for curv_ind = k0 : int32( kend )
                    curv_ind = ctx->k0;
                    exitg1 = false;
                    while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
                        // 'feedratePlanning:111' ind = ind + 1;
                        ind++;
                        //  store the value in the queue
                        // 'feedratePlanning:114' curv            = q_curves.get( curv_ind );
                        ctx->q_split.get(curv_ind, &curv);
                        // 'feedratePlanning:115' window( ind )   = curv;
                        window[static_cast<int>(ind) - 1] = curv;
                        //  Check if zero speed at the end
                        // 'feedratePlanning:118' if( isAZeroEnd( curv ) )
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
                    // 'feedratePlanning:121' NWindow = ind;
                    NWindow = static_cast<int>(ind);
                    // 'feedratePlanning:30' first = window( 1 );
                    // 'feedratePlanning:31' last  = window( NWindow );
                    //  Handle the zero speed at start
                    // 'feedratePlanning:34' if ( isAZeroStart( first ) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((window[0].Info.zspdmode == ZSpdMode_ZN) ||
                        (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
                        double b_unnamed_idx_0;
                        double b_y;
                        double k_vec;
                        double n;
                        double u;
                        double ud;
                        double udd;
                        double unnamed_idx_0;
                        int c_loop_ub;
                        int d_loop_ub;
                        int i9;
                        // 'isAZeroStart:6' zeroFlag = true;
                        // 'feedratePlanning:35' opt_struct      = first;
                        *opt_struct = window[0];
                        // 'feedratePlanning:36' optimized       = true;
                        b_optimized = true;
                        // 'feedratePlanning:37' [ v_0, at_0 ]   = calcZeroConstraints( ctx, first,
                        // false );
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
                        // 'calcZeroConstraints:16' else
                        // 'calcZeroConstraints:17' k   = ( 6 / jps )^( 1 / 3 );
                        // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k,
                        // isEnd );
                        k_vec = std::pow(6.0 / window[0].ConstJerk, 0.33333333333333331);
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
                        udd = window[0].ConstJerk * k_vec;
                        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
                        ud = window[0].ConstJerk * std::pow(k_vec, 2.0) / 2.0;
                        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                        u = window[0].ConstJerk * std::pow(k_vec, 3.0) / 6.0;
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
                        // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx,
                        // curv, u );
                        for (int i3{0}; i3 < 6; i3++) {
                            dv[i3] = window[0].R0[i3];
                        }
                        for (int i4{0}; i4 < 6; i4++) {
                            dv2[i4] = window[0].R1[i4];
                        }
                        dv1[0] = window[0].CorrectedHelixCenter[0];
                        dv1[1] = window[0].CorrectedHelixCenter[1];
                        dv1[2] = window[0].CorrectedHelixCenter[2];
                        dv3[0] = window[0].evec[0];
                        dv3[1] = window[0].evec[1];
                        dv3[2] = window[0].evec[2];
                        b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                         ctx->cfg.NRot, ctx->cfg.indCart.data,
                                         ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                                         ctx->cfg.indRot.size[0], ctx->cfg.indTot.data,
                                         ctx->cfg.indTot.size[0], window[0].Info.Type, dv, dv2, dv1,
                                         dv3, window[0].theta, window[0].pitch, window[0].CoeffP5,
                                         window[0].sp_index, window[0].a_param, window[0].b_param,
                                         b_unnamed_idx_0, r0D, r1D, r2D, r3D);
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
                        b_y = std::pow(ud, 2.0);
                        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec
                        // .* udd_vec + r1D .* uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]
                        // = calcNormVNormAT( V, A, r1D );
                        //  calcNormVNormAT : Compute the norm of velocity and the norm of
                        //  tangential acceleration. Inputs : V     : The velovity vector A     :
                        //  The acceleration vector r1D   : The partial derivative of R Outputs :
                        //  vNorm   : Norm of the velocity
                        //  atNorm  : Norm of the tangential acceleration
                        // 'calcNormVNormAT:12' vNorm   = mysqrt( sum( V.^2, 1 ) );
                        // 'mysqrt:3' y = sqrt(x);
                        r7.set_size(r1D.size(0));
                        c_loop_ub = r1D.size(0);
                        for (int i7{0}; i7 < c_loop_ub; i7++) {
                            double varargin_1;
                            varargin_1 = r1D[i7] * ud;
                            r7[i7] = std::pow(varargin_1, 2.0);
                        }
                        ctx->v_0 = std::sqrt(coder::combineVectorElements(r7));
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        r7.set_size(r1D.size(0));
                        d_loop_ub = r1D.size(0);
                        for (int i8{0}; i8 < d_loop_ub; i8++) {
                            double b_varargin_1;
                            b_varargin_1 = r1D[i8];
                            r7[i8] = std::pow(b_varargin_1, 2.0);
                        }
                        n = std::sqrt(coder::combineVectorElements(r7));
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'calcNormVNormAT:14' atNorm  = norm( A.*t );
                        if (r2D.size(0) == 1) {
                            i9 = r1D.size(0);
                        } else {
                            i9 = r2D.size(0);
                        }
                        if ((r2D.size(0) == r1D.size(0)) && (i9 == r1D.size(0))) {
                            int f_loop_ub;
                            f_loop_ub = r2D.size(0);
                            for (int i11{0}; i11 < f_loop_ub; i11++) {
                                r2D[i11] = (r2D[i11] * b_y + r1D[i11] * udd) * (r1D[i11] / n);
                            }
                            ctx->at_0 = coder::b_norm(r2D);
                        } else {
                            binary_expand_op(ctx, r2D, b_y, r1D, udd, n);
                        }
                        // 'feedratePlanning:38' ctx.v_0         = v_0;
                        // 'feedratePlanning:39' ctx.at_0        = at_0;
                        // 'feedratePlanning:40' ctx.zero_start  = true;
                        ctx->zero_start = true;
                        // 'feedratePlanning:41' quit            = true;
                        b_quit = true;
                    } else {
                        int b_loop_ub;
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'feedratePlanning:43' else
                        // 'feedratePlanning:44' ctx.zero_start  = false;
                        ctx->zero_start = false;
                        //  Handle the zero speed at end
                        // 'feedratePlanning:47' if( isAZeroEnd( last ) )
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if ((window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_NZ) ||
                            (window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_ZZ)) {
                            double b_k_vec;
                            double b_n;
                            double b_u;
                            double b_ud;
                            double b_udd;
                            double c_unnamed_idx_0;
                            double c_y;
                            double d_unnamed_idx_0;
                            double pseudoJerk;
                            int e_loop_ub;
                            int g_loop_ub;
                            int i13;
                            // 'isAZeroEnd:7' zeroFlag = true;
                            // 'feedratePlanning:48' [ v_1, at_1 ]   = calcZeroConstraints( ctx,
                            // last, true );
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
                            // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps,
                            // k, isEnd );
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
                            b_k_vec = std::pow(6.0 / pseudoJerk, 0.33333333333333331);
                            //  Compute u and its derivatives based on constant jerk
                            // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
                            // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
                            // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
                            b_ud = pseudoJerk * std::pow(b_k_vec, 2.0) / 2.0;
                            // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
                            b_u = pseudoJerk * std::pow(b_k_vec, 3.0) / 6.0;
                            // 'constJerkU:33' u( u > 1 ) = 1;
                            c_unnamed_idx_0 = b_u;
                            if (b_u > 1.0) {
                                c_unnamed_idx_0 = 1.0;
                            }
                            // 'constJerkU:34' u( u < 0 ) = 0;
                            d_unnamed_idx_0 = c_unnamed_idx_0;
                            if (c_unnamed_idx_0 < 0.0) {
                                d_unnamed_idx_0 = 0.0;
                            }
                            // 'constJerkU:36' if( isEnd )
                            //  Reverse time ( Backward-like integration )
                            // 'constJerkU:37' u    = 1 - u;
                            // 'constJerkU:38' ud   = ud;
                            // 'constJerkU:39' udd  = -udd;
                            b_udd = -(pseudoJerk * b_k_vec);
                            // 'constJerkU:40' uddd = uddd;
                            // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct(
                            // ctx, curv, u );
                            for (int i5{0}; i5 < 6; i5++) {
                                dv4[i5] = window[static_cast<int>(ind) - 1].R0[i5];
                            }
                            for (int i6{0}; i6 < 6; i6++) {
                                dv6[i6] = window[static_cast<int>(ind) - 1].R1[i6];
                            }
                            dv5[0] = window[static_cast<int>(ind) - 1].CorrectedHelixCenter[0];
                            dv5[1] = window[static_cast<int>(ind) - 1].CorrectedHelixCenter[1];
                            dv5[2] = window[static_cast<int>(ind) - 1].CorrectedHelixCenter[2];
                            dv7[0] = window[static_cast<int>(ind) - 1].evec[0];
                            dv7[1] = window[static_cast<int>(ind) - 1].evec[1];
                            dv7[2] = window[static_cast<int>(ind) - 1].evec[2];
                            b_EvalCurvStruct(&ctx->q_spline, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                             ctx->cfg.NRot, ctx->cfg.indCart.data,
                                             ctx->cfg.indCart.size[0], ctx->cfg.indRot.data,
                                             ctx->cfg.indRot.size[0], ctx->cfg.indTot.data,
                                             ctx->cfg.indTot.size[0],
                                             window[static_cast<int>(ind) - 1].Info.Type, dv4, dv6,
                                             dv5, dv7, window[static_cast<int>(ind) - 1].theta,
                                             window[static_cast<int>(ind) - 1].pitch,
                                             window[static_cast<int>(ind) - 1].CoeffP5,
                                             window[static_cast<int>(ind) - 1].sp_index,
                                             window[static_cast<int>(ind) - 1].a_param,
                                             window[static_cast<int>(ind) - 1].b_param,
                                             1.0 - d_unnamed_idx_0, r0D, r1D, r2D, r3D);
                            // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          =
                            // calcRVAJfromUWithoutCurv( ud, udd, uddd, r0D, ...
                            // 'calcZeroConstraints:25'                           r1D, r2D, r3D );
                            //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and
                            //  the jerk for a given set of u variable. Inputs :
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
                            c_y = std::pow(b_ud, 2.0);
                            // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .*
                            // ud_vec .* udd_vec + r1D .* uddd_vec; 'calcZeroConstraints:27' [
                            // vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
                            //  calcNormVNormAT : Compute the norm of velocity and the norm of
                            //  tangential acceleration. Inputs : V     : The velovity vector A :
                            //  The acceleration vector r1D   : The partial derivative of R Outputs
                            //  : vNorm   : Norm of the velocity atNorm  : Norm of the tangential
                            //  acceleration
                            // 'calcNormVNormAT:12' vNorm   = mysqrt( sum( V.^2, 1 ) );
                            // 'mysqrt:3' y = sqrt(x);
                            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                            sqrt_calls++;
                            // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
                            // 'MyNorm:2' coder.inline('always');
                            // 'MyNorm:3' n = mysqrt(sum(x.^2));
                            // 'mysqrt:3' y = sqrt(x);
                            r7.set_size(r1D.size(0));
                            e_loop_ub = r1D.size(0);
                            for (int i10{0}; i10 < e_loop_ub; i10++) {
                                double c_varargin_1;
                                c_varargin_1 = r1D[i10];
                                r7[i10] = std::pow(c_varargin_1, 2.0);
                            }
                            b_n = std::sqrt(coder::combineVectorElements(r7));
                            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                            sqrt_calls++;
                            // 'calcNormVNormAT:14' atNorm  = norm( A.*t );
                            // 'feedratePlanning:49' ctx.v_1         = -v_1;
                            r7.set_size(r1D.size(0));
                            g_loop_ub = r1D.size(0);
                            for (int i12{0}; i12 < g_loop_ub; i12++) {
                                double d_varargin_1;
                                d_varargin_1 = r1D[i12] * b_ud;
                                r7[i12] = std::pow(d_varargin_1, 2.0);
                            }
                            ctx->v_1 = -std::sqrt(coder::combineVectorElements(r7));
                            // 'feedratePlanning:50' ctx.at_1        = -at_1;
                            if (r2D.size(0) == 1) {
                                i13 = r1D.size(0);
                            } else {
                                i13 = r2D.size(0);
                            }
                            if ((r2D.size(0) == r1D.size(0)) && (i13 == r1D.size(0))) {
                                int h_loop_ub;
                                h_loop_ub = r2D.size(0);
                                for (int i14{0}; i14 < h_loop_ub; i14++) {
                                    r2D[i14] =
                                        (r2D[i14] * c_y + r1D[i14] * b_udd) * (r1D[i14] / b_n);
                                }
                                ctx->at_1 = -coder::b_norm(r2D);
                            } else {
                                b_binary_expand_op(ctx, r2D, c_y, r1D, b_udd, b_n);
                            }
                            // 'feedratePlanning:51' ctx.zero_end    = true;
                            ctx->zero_end = true;
                            // 'feedratePlanning:52' NWindow         = NWindow -1;
                            NWindow = static_cast<int>(ind) - 1;
                        } else {
                            // 'isAZeroEnd:9' zeroFlag = false;
                            // 'feedratePlanning:53' else
                            // 'feedratePlanning:54' ctx.v_1         = -ctx.cfg.v_1;
                            ctx->v_1 = -ctx->cfg.v_1;
                            // 'feedratePlanning:55' ctx.at_1        = -ctx.cfg.at_1;
                            ctx->at_1 = -ctx->cfg.at_1;
                            // 'feedratePlanning:56' ctx.zero_end    = false;
                            ctx->zero_end = false;
                        }
                        // 'feedratePlanning:59' [ctx, Coeff, success, status, msg] = ...
                        // 'feedratePlanning:60'     FeedratePlanning_LP( ctx, window, ctx.cfg.amax,
                        // ctx.cfg.jmax,  ... 'feedratePlanning:61'     ctx.BasisVal, ctx.BasisValD,
                        // ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:62'     ctx.u_vec,
                        // NWindow );
                        FeedratePlanning_LP(ctx, window, ctx->cfg.amax, ctx->cfg.jmax,
                                            ctx->BasisVal, ctx->BasisValD, ctx->BasisValDD,
                                            ctx->BasisIntegr, ctx->u_vec,
                                            static_cast<double>(NWindow), Coeff, &success, &status);
                        // 'feedratePlanning:64' if( success == 1 )
                        //  Optimization succed
                        // 'feedratePlanning:65' optimized   = true;
                        b_optimized = true;
                        // 'feedratePlanning:66' opt_struct  = ctx.q_split.get( ctx.k0 );
                        ctx->q_split.get(ctx->k0, opt_struct);
                        // 'feedratePlanning:67' opt_struct.Coeff = Coeff( :, 1 );
                        b_loop_ub = Coeff.size(0);
                        opt_struct->Coeff.set_size(Coeff.size(0));
                        for (int i2{0}; i2 < b_loop_ub; i2++) {
                            opt_struct->Coeff[i2] = Coeff[i2];
                        }
                        //  Check if end of the queue
                        // 'feedratePlanning:70' if( ctx.zero_end && ( ctx.k0 + NWindow ) >=
                        // ctx.q_split.size )
                        if (ctx->zero_end &&
                            (static_cast<double>(ctx->k0 + NWindow) >= ctx->q_split.size())) {
                            // 'feedratePlanning:71' ctx.reached_end = true;
                            ctx->reached_end = true;
                        }
                    }
                } else {
                    // 'feedratePlanning:76' else
                    // 'feedratePlanning:77' optimized   = true;
                    b_optimized = true;
                    // 'feedratePlanning:78' kopt = kopt + 1;
                    kopt++;
                    // 'feedratePlanning:79' opt_struct = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                    // 'feedratePlanning:81' if( opt_struct.Info.zspdmode ~= ZSpdMode.NZ )
                    if (opt_struct->Info.zspdmode != ZSpdMode_NZ) {
                        int loop_ub;
                        // 'feedratePlanning:82' opt_struct.Coeff = ctx.Coeff( :, kopt );
                        loop_ub = ctx->Coeff.size(0);
                        opt_struct->Coeff.set_size(loop_ub);
                        for (int i{0}; i < loop_ub; i++) {
                            opt_struct->Coeff[i] =
                                ctx->Coeff[i + ctx->Coeff.size(0) * (static_cast<int>(kopt) - 1)];
                        }
                    } else {
                        // 'feedratePlanning:83' else
                        // 'feedratePlanning:84' ctx.zero_end  = false;
                        ctx->zero_end = false;
                        // 'feedratePlanning:85' kopt = 1;
                        kopt = 1.0;
                    }
                }
            } else {
                //  Do nothing, we already have the last one optimized
            }
        } else {
            // 'feedratePlanning:88' else
            // 'feedratePlanning:89' ctx.op = Fopt.Finished;
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
