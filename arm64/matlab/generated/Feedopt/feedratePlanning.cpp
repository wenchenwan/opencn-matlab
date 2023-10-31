
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "feedratePlanning.h"
#include "FeedratePlanning_LP.h"
#include "Kinematics.h"
#include "constrCurvStruct.h"
#include "cutZeroEnd.h"
#include "cutZeroStart.h"
#include "feedratePlanningSetupCurves.h"
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
#include "string1.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
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
    coder::rtString msg;
    ::coder::array<CurvStruct, 2U> window;
    ::coder::array<double, 2U> Coeff;
    Axes params_tmp_tool_offset;
    CurvStruct C;
    CurvStruct b_C;
    CurvStruct curv;
    CurvStruct curv1;
    CurvStruct curv1NN;
    CurvStruct curv2;
    CurvStruct curv2NN;
    SplineStruct params_tmp_spline;
    b_CurvStruct e_expl_temp;
    b_CurvStruct expl_temp_tmp;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double NWindow;
    double a__1;
    double a__2;
    double b_expl_temp;
    double c_NWindow;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_tool_backangle;
    double params_tmp_tool_diameter;
    double params_tmp_tool_frontangle;
    int b_loop_ub;
    int b_status;
    int c_loop_ub;
    int e_loop_ub;
    int loop_ub;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_tool_orientation;
    int params_tmp_tool_pocketno;
    int params_tmp_tool_toolno;
    int status;
    bool b_optimized;
    bool b_quit;
    bool b_success;
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    bool success;
    CurveType params_tmp_gcodeInfoStruct_Type;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    // 'feedratePlanning:6' if( isempty( kopt ) )
    // 'feedratePlanning:8' opt_struct  = constrCurvStructType;
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
        params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5, &expl_temp_tmp);
    e_expl_temp = expl_temp_tmp;
    opt_struct->Info = e_expl_temp.Info;
    opt_struct->tool = e_expl_temp.tool;
    opt_struct->sp = e_expl_temp.sp;
    opt_struct->R0.set_size(e_expl_temp.R0.size[0]);
    loop_ub = e_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        opt_struct->R0[i] = e_expl_temp.R0.data[i];
    }
    opt_struct->R1.set_size(e_expl_temp.R1.size[0]);
    b_loop_ub = e_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        opt_struct->R1[i1] = e_expl_temp.R1.data[i1];
    }
    opt_struct->delta = e_expl_temp.delta;
    opt_struct->CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
    opt_struct->evec[0] = e_expl_temp.evec[0];
    opt_struct->CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
    opt_struct->evec[1] = e_expl_temp.evec[1];
    opt_struct->CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
    opt_struct->evec[2] = e_expl_temp.evec[2];
    opt_struct->theta = e_expl_temp.theta;
    opt_struct->pitch = e_expl_temp.pitch;
    opt_struct->CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    c_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            opt_struct->CoeffP5[i3 + opt_struct->CoeffP5.size(0) * i2] =
                e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    opt_struct->sp_index = e_expl_temp.sp_index;
    opt_struct->i_begin_sp = e_expl_temp.i_begin_sp;
    opt_struct->i_end_sp = e_expl_temp.i_end_sp;
    opt_struct->index_smooth = e_expl_temp.index_smooth;
    opt_struct->UseConstJerk = e_expl_temp.UseConstJerk;
    opt_struct->ConstJerk = e_expl_temp.ConstJerk;
    opt_struct->Coeff.set_size(e_expl_temp.Coeff.size(0));
    e_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        opt_struct->Coeff[i4] = e_expl_temp.Coeff[i4];
    }
    opt_struct->a_param = e_expl_temp.a_param;
    opt_struct->b_param = e_expl_temp.b_param;
    //  Type of returned curvStruct
    // 'feedratePlanning:9' quit        = false;
    b_quit = false;
    //  Flag used to quit the optimization
    // 'feedratePlanning:10' optimized   = false;
    b_optimized = false;
    //  Does the optimization successed
    // 'feedratePlanning:11' ctx.op      = Fopt.Opt;
    ctx->op = Fopt_Opt;
    //  Current state of the FSM
    //  Check if empty queue after splitting. If yes, stop optimization
    // 'feedratePlanning:14' if ctx.q_split.isempty
    if (ctx->q_split.isempty()) {
        // 'feedratePlanning:14' [ ctx.op, quit ] = empty_queue_split();
        //  Treat the case of an empty queue after splitting operation
        // 'feedratePlanning:115' if coder.target( 'MATLAB' )
        // 'feedratePlanning:118' DebugLog( DebugCfg.Validate, 'Queue empty...\n' );
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
        // 'feedratePlanning:119' op      = Fopt.Finished;
        // 'feedratePlanning:120' quit    = true;
        ctx->op = Fopt_Finished;
        b_quit = true;
    } else {
        // 'feedratePlanning:16' if coder.target( 'MATLAB' )
        //  Increment index on q_split
        // 'feedratePlanning:23' if ctx.go_next
        if (ctx->go_next) {
            // 'feedratePlanning:23' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
        }
        // 'feedratePlanning:25' if ( ctx.k0 <= ctx.q_split.size )
        if (static_cast<double>(ctx->k0) <= ctx->q_split.size()) {
            // 'feedratePlanning:27' if ~ctx.zero_end
            if (!ctx->zero_end) {
                double b_NWindow;
                int curv_ind;
                int f_loop_ub;
                int g_loop_ub;
                int h_loop_ub;
                unsigned int ind;
                int j_loop_ub;
                unsigned int kend;
                int l_loop_ub;
                int m_loop_ub;
                int n_loop_ub;
                int outsize_idx_1_tmp;
                int p_loop_ub;
                int x;
                unsigned int y;
                bool exitg1;
                //  Get window of interest in from a given queue
                // 'feedratePlanning:29' [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0,
                // ... 'feedratePlanning:30'                                 ctx.cfg.NHorz,
                // ctx.q_split ); 'feedratePlanningGetwindow:3' window = repmat(
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
                e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                f_loop_ub = expl_temp_tmp.R0.size[0];
                if (f_loop_ub - 1 >= 0) {
                    std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[f_loop_ub],
                              &e_expl_temp.R0.data[0]);
                }
                e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                g_loop_ub = expl_temp_tmp.R1.size[0];
                if (g_loop_ub - 1 >= 0) {
                    std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[g_loop_ub],
                              &e_expl_temp.R1.data[0]);
                }
                e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                             expl_temp_tmp.CoeffP5.size(1));
                h_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                for (int i5{0}; i5 < h_loop_ub; i5++) {
                    int i_loop_ub;
                    i_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                    for (int i6{0}; i6 < i_loop_ub; i6++) {
                        e_expl_temp.CoeffP5[i6 + e_expl_temp.CoeffP5.size(0) * i5] =
                            expl_temp_tmp.CoeffP5[i6 + expl_temp_tmp.CoeffP5.size(0) * i5];
                    }
                }
                e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                j_loop_ub = expl_temp_tmp.Coeff.size(0);
                for (int i7{0}; i7 < j_loop_ub; i7++) {
                    e_expl_temp.Coeff[i7] = expl_temp_tmp.Coeff[i7];
                }
                C.Info = expl_temp_tmp.Info;
                C.tool = expl_temp_tmp.tool;
                C.sp = expl_temp_tmp.sp;
                C.R0.set_size(e_expl_temp.R0.size[0]);
                l_loop_ub = e_expl_temp.R0.size[0];
                for (int i9{0}; i9 < l_loop_ub; i9++) {
                    C.R0[i9] = e_expl_temp.R0.data[i9];
                }
                C.R1.set_size(e_expl_temp.R1.size[0]);
                m_loop_ub = e_expl_temp.R1.size[0];
                for (int i10{0}; i10 < m_loop_ub; i10++) {
                    C.R1[i10] = e_expl_temp.R1.data[i10];
                }
                C.delta = expl_temp_tmp.delta;
                C.CorrectedHelixCenter[0] = expl_temp_tmp.CorrectedHelixCenter[0];
                C.evec[0] = expl_temp_tmp.evec[0];
                C.CorrectedHelixCenter[1] = expl_temp_tmp.CorrectedHelixCenter[1];
                C.evec[1] = expl_temp_tmp.evec[1];
                C.CorrectedHelixCenter[2] = expl_temp_tmp.CorrectedHelixCenter[2];
                C.evec[2] = expl_temp_tmp.evec[2];
                C.theta = expl_temp_tmp.theta;
                C.pitch = expl_temp_tmp.pitch;
                C.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
                n_loop_ub = e_expl_temp.CoeffP5.size(1);
                for (int i11{0}; i11 < n_loop_ub; i11++) {
                    int o_loop_ub;
                    o_loop_ub = e_expl_temp.CoeffP5.size(0);
                    for (int i12{0}; i12 < o_loop_ub; i12++) {
                        C.CoeffP5[i12 + C.CoeffP5.size(0) * i11] =
                            e_expl_temp.CoeffP5[i12 + e_expl_temp.CoeffP5.size(0) * i11];
                    }
                }
                C.sp_index = expl_temp_tmp.sp_index;
                C.i_begin_sp = expl_temp_tmp.i_begin_sp;
                C.i_end_sp = expl_temp_tmp.i_end_sp;
                C.index_smooth = expl_temp_tmp.index_smooth;
                C.UseConstJerk = expl_temp_tmp.UseConstJerk;
                C.ConstJerk = expl_temp_tmp.ConstJerk;
                C.Coeff.set_size(e_expl_temp.Coeff.size(0));
                p_loop_ub = e_expl_temp.Coeff.size(0);
                for (int i13{0}; i13 < p_loop_ub; i13++) {
                    C.Coeff[i13] = e_expl_temp.Coeff[i13];
                }
                C.a_param = expl_temp_tmp.a_param;
                C.b_param = expl_temp_tmp.b_param;
                outsize_idx_1_tmp = ctx->cfg.NHorz;
                window.set_size(1, outsize_idx_1_tmp);
                for (int i14{0}; i14 < outsize_idx_1_tmp; i14++) {
                    window[i14] = C;
                }
                // 'feedratePlanningGetwindow:5' kend = min( double( k0 + NHorz -1 ), q_curves.size
                // );
                x = (ctx->k0 + outsize_idx_1_tmp) - 1;
                y = ctx->q_split.size();
                if (static_cast<double>(x) > y) {
                    kend = y;
                } else {
                    kend = static_cast<unsigned int>(x);
                }
                // 'feedratePlanningGetwindow:7' ind = 0;
                ind = 0U;
                // 'feedratePlanningGetwindow:9' for curv_ind = k0 : int32( kend )
                curv_ind = ctx->k0;
                exitg1 = false;
                while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
                    bool b_zeroFlag;
                    // 'feedratePlanningGetwindow:10' ind = ind + 1;
                    ind++;
                    //  store the value in the queue
                    // 'feedratePlanningGetwindow:13' curv            = q_curves.get( curv_ind );
                    ctx->q_split.get(curv_ind, &curv);
                    // 'feedratePlanningGetwindow:14' window( ind )   = curv;
                    window[static_cast<int>(ind) - 1] = curv;
                    //  Check if zero speed at the end
                    // 'feedratePlanningGetwindow:16' if( isAZeroEnd( curv ) )
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
                        exitg1 = true;
                    } else {
                        curv_ind++;
                    }
                }
                // 'feedratePlanningGetwindow:19' NWindow = ind;
                //  Prepare the boundaries conditions of the problem
                // 'feedratePlanning:33' [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
                // 'feedratePlanning:34'                 ctx, window, NWindow );
                NWindow = ind;
                feedratePlanningSetupCurves(ctx, window, &NWindow);
                b_NWindow = NWindow;
                //  Start the optimization
                // 'feedratePlanning:38' [ ctx, Coeff, success, status, msg ] = ...
                // 'feedratePlanning:39'                 FeedratePlanning_LP( ctx, window,
                // ctx.cfg.amax, ctx.cfg.jmax, ... 'feedratePlanning:40' ctx.BasisVal,
                // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:41'
                // ctx.u_vec, NWindow );
                FeedratePlanning_LP(ctx, window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                    ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr, ctx->u_vec,
                                    NWindow, Coeff, &success, &status, &msg);
                b_success = success;
                // 'feedratePlanning:43' if( ~( success || ctx.zero_start || ctx.zero_end ) )
                if ((!success) && (!ctx->zero_start) && (!ctx->zero_end)) {
                    queue_coder curvQueue;
                    int b_curv_ind;
                    unsigned int b_ind;
                    unsigned int b_kend;
                    unsigned int b_y;
                    int cb_loop_ub;
                    int eb_loop_ub;
                    int fb_loop_ub;
                    int i33;
                    int ind1_tmp_tmp;
                    int jb_loop_ub;
                    int lb_loop_ub;
                    int mb_loop_ub;
                    int u_loop_ub;
                    int x_loop_ub;
                    int y_loop_ub;
                    bool d_zeroFlag;
                    bool e_zeroFlag;
                    // 'feedratePlanning:44' [ ctx, window, NWindow ] =
                    // feedratePlanningForceZeroStop( ... 'feedratePlanning:45' ctx, window, NWindow
                    // );
                    //  NN case :
                    //  Optimization failed due to small coefficient, so force a stop
                    // 'feedratePlanningForceZeroStop:5' curvQueue       = ctx.q_split;
                    curvQueue = ctx->q_split;
                    // 'feedratePlanningForceZeroStop:6' ctx.zero_forced = true;
                    ctx->zero_forced = true;
                    // 'feedratePlanningForceZeroStop:7' ocn_assert( ctx.k0 > 1, "Should not be
                    // called one the first set of curves", ... 'feedratePlanningForceZeroStop:8'
                    // mfilename );
                    gb_ocn_assert(ctx->k0 > 1);
                    // 'feedratePlanningForceZeroStop:10' curv0           = window( 1 );
                    // 'feedratePlanningForceZeroStop:11' curv1           = window( NWindow );
                    curv1 = window[static_cast<int>(NWindow) - 1];
                    // 'feedratePlanningForceZeroStop:12' ind1            = ctx.k0 + NWindow;
                    ind1_tmp_tmp =
                        static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow));
                    // 'feedratePlanningForceZeroStop:14' msg = "Curve should be a Zero Stop";
                    // 'feedratePlanningForceZeroStop:15' ocn_assert( ~isAZeroStart( curv0 ), msg,
                    // mfilename );
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroStart:6' zeroFlag = false;
                    d_zeroFlag = false;
                    // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroStart:10' if( error )
                    // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                    if ((window[0].Info.zspdmode == ZSpdMode_ZN) ||
                        (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:14' zeroFlag = true;
                        d_zeroFlag = true;
                    }
                    hb_ocn_assert(!d_zeroFlag);
                    // 'feedratePlanningForceZeroStop:16' ocn_assert( ~isAZeroEnd( curv1 ),   msg,
                    // mfilename );
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroEnd:6' zeroFlag = false;
                    e_zeroFlag = false;
                    // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:10' if( error )
                    // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                    if ((window[static_cast<int>(NWindow) - 1].Info.zspdmode == ZSpdMode_NZ) ||
                        (window[static_cast<int>(NWindow) - 1].Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:14' zeroFlag = true;
                        e_zeroFlag = true;
                    }
                    hb_ocn_assert(!e_zeroFlag);
                    // 'feedratePlanningForceZeroStop:17' curv1.Info.zspdmode = ZSpdMode.NZ;
                    curv1.Info.zspdmode = ZSpdMode_NZ;
                    // 'feedratePlanningForceZeroStop:19' [ ~, curv1NN, curv1NZ ]     = cutZeroEnd(
                    // ctx,  curv1 );
                    cutZeroEnd(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.LSplitZero,
                               ctx->cfg.dt, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &ctx->kin, &curv1, &a__1, &curv1NN, &ctx->zero_forced_buffer[0]);
                    // 'feedratePlanningForceZeroStop:20' ctx.zero_forced_buffer( 1 ) = curv1NZ;
                    // 'feedratePlanningForceZeroStop:21' curvQueue.set( ind1, curv1NN );
                    ctx->q_split.set(ind1_tmp_tmp, &curv1NN);
                    // 'feedratePlanningForceZeroStop:23' ind2            = ind1 + 1;
                    // 'feedratePlanningForceZeroStop:24' if( ind2 <= curvQueue.size() )
                    if (static_cast<double>(ind1_tmp_tmp + 1) <= ctx->q_split.size()) {
                        // 'feedratePlanningForceZeroStop:25' curv2       = ctx.q_split.get( ind2 );
                        ctx->q_split.get(ind1_tmp_tmp + 1, &curv2);
                        // 'feedratePlanningForceZeroStop:26' curv2.Info.zspdmode = ZSpdMode.ZN;
                        curv2.Info.zspdmode = ZSpdMode_ZN;
                        // 'feedratePlanningForceZeroStop:27' [ ~, curv2ZN, curv2NN ]     =
                        // cutZeroStart( ctx, curv2 );
                        cutZeroStart(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, ctx->cfg.vmax, ctx->cfg.amax, ctx->cfg.jmax,
                                     ctx->cfg.LSplitZero, ctx->cfg.dt, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &ctx->kin, &curv2, &a__2,
                                     &ctx->zero_forced_buffer[1], &curv2NN);
                        // 'feedratePlanningForceZeroStop:28' ctx.zero_forced_buffer( 2 ) = curv2ZN;
                        // 'feedratePlanningForceZeroStop:29' curvQueue.set( ind2, curv2NN );
                        ctx->q_split.set(ind1_tmp_tmp + 1, &curv2NN);
                    } else {
                        int ab_loop_ub;
                        int db_loop_ub;
                        int gb_loop_ub;
                        int ib_loop_ub;
                        int r_loop_ub;
                        int s_loop_ub;
                        int t_loop_ub;
                        int w_loop_ub;
                        // 'feedratePlanningForceZeroStop:30' else
                        //  Empty curve
                        // 'feedratePlanningForceZeroStop:32' ctx.zero_forced_buffer( 2 ) =
                        // constrCurvStructType;
                        //  constrCurvStructType : Constructs a constrCurvStruct with default
                        //  values.
                        // 'constrCurvStructType:4' if( nargin > 0 )
                        // 'constrCurvStructType:6' else
                        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                        // 'constrCurvStructType:12' else
                        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                        // params.tool, ... 'constrCurvStructType:14'         params.spline,
                        // params.R0, params.R1, params.Cprim, ... 'constrCurvStructType:15'
                        // params.delta, params.evec, params.theta, params.pitch, ...
                        // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
                        e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                        r_loop_ub = expl_temp_tmp.R0.size[0];
                        if (r_loop_ub - 1 >= 0) {
                            std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[r_loop_ub],
                                      &e_expl_temp.R0.data[0]);
                        }
                        e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                        s_loop_ub = expl_temp_tmp.R1.size[0];
                        if (s_loop_ub - 1 >= 0) {
                            std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[s_loop_ub],
                                      &e_expl_temp.R1.data[0]);
                        }
                        e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                                     expl_temp_tmp.CoeffP5.size(1));
                        t_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                        for (int i16{0}; i16 < t_loop_ub; i16++) {
                            int v_loop_ub;
                            v_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                            for (int i17{0}; i17 < v_loop_ub; i17++) {
                                e_expl_temp.CoeffP5[i17 + e_expl_temp.CoeffP5.size(0) * i16] =
                                    expl_temp_tmp
                                        .CoeffP5[i17 + expl_temp_tmp.CoeffP5.size(0) * i16];
                            }
                        }
                        e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                        w_loop_ub = expl_temp_tmp.Coeff.size(0);
                        for (int i18{0}; i18 < w_loop_ub; i18++) {
                            e_expl_temp.Coeff[i18] = expl_temp_tmp.Coeff[i18];
                        }
                        ctx->zero_forced_buffer[1].Info = expl_temp_tmp.Info;
                        ctx->zero_forced_buffer[1].tool = expl_temp_tmp.tool;
                        ctx->zero_forced_buffer[1].sp = expl_temp_tmp.sp;
                        ctx->zero_forced_buffer[1].R0.set_size(e_expl_temp.R0.size[0]);
                        ab_loop_ub = e_expl_temp.R0.size[0];
                        for (int i20{0}; i20 < ab_loop_ub; i20++) {
                            ctx->zero_forced_buffer[1].R0[i20] = e_expl_temp.R0.data[i20];
                        }
                        ctx->zero_forced_buffer[1].R1.set_size(e_expl_temp.R1.size[0]);
                        db_loop_ub = e_expl_temp.R1.size[0];
                        for (int i23{0}; i23 < db_loop_ub; i23++) {
                            ctx->zero_forced_buffer[1].R1[i23] = e_expl_temp.R1.data[i23];
                        }
                        ctx->zero_forced_buffer[1].delta = expl_temp_tmp.delta;
                        ctx->zero_forced_buffer[1].CorrectedHelixCenter[0] =
                            expl_temp_tmp.CorrectedHelixCenter[0];
                        ctx->zero_forced_buffer[1].evec[0] = expl_temp_tmp.evec[0];
                        ctx->zero_forced_buffer[1].CorrectedHelixCenter[1] =
                            expl_temp_tmp.CorrectedHelixCenter[1];
                        ctx->zero_forced_buffer[1].evec[1] = expl_temp_tmp.evec[1];
                        ctx->zero_forced_buffer[1].CorrectedHelixCenter[2] =
                            expl_temp_tmp.CorrectedHelixCenter[2];
                        ctx->zero_forced_buffer[1].evec[2] = expl_temp_tmp.evec[2];
                        ctx->zero_forced_buffer[1].theta = expl_temp_tmp.theta;
                        ctx->zero_forced_buffer[1].pitch = expl_temp_tmp.pitch;
                        ctx->zero_forced_buffer[1].CoeffP5.set_size(e_expl_temp.CoeffP5.size(0),
                                                                    e_expl_temp.CoeffP5.size(1));
                        gb_loop_ub = e_expl_temp.CoeffP5.size(1);
                        for (int i26{0}; i26 < gb_loop_ub; i26++) {
                            int hb_loop_ub;
                            hb_loop_ub = e_expl_temp.CoeffP5.size(0);
                            for (int i27{0}; i27 < hb_loop_ub; i27++) {
                                ctx->zero_forced_buffer[1]
                                    .CoeffP5[i27 +
                                             ctx->zero_forced_buffer[1].CoeffP5.size(0) * i26] =
                                    e_expl_temp.CoeffP5[i27 + e_expl_temp.CoeffP5.size(0) * i26];
                            }
                        }
                        ctx->zero_forced_buffer[1].sp_index = expl_temp_tmp.sp_index;
                        ctx->zero_forced_buffer[1].i_begin_sp = expl_temp_tmp.i_begin_sp;
                        ctx->zero_forced_buffer[1].i_end_sp = expl_temp_tmp.i_end_sp;
                        ctx->zero_forced_buffer[1].index_smooth = expl_temp_tmp.index_smooth;
                        ctx->zero_forced_buffer[1].UseConstJerk = expl_temp_tmp.UseConstJerk;
                        ctx->zero_forced_buffer[1].ConstJerk = expl_temp_tmp.ConstJerk;
                        ctx->zero_forced_buffer[1].Coeff.set_size(e_expl_temp.Coeff.size(0));
                        ib_loop_ub = e_expl_temp.Coeff.size(0);
                        for (int i28{0}; i28 < ib_loop_ub; i28++) {
                            ctx->zero_forced_buffer[1].Coeff[i28] = e_expl_temp.Coeff[i28];
                        }
                        ctx->zero_forced_buffer[1].a_param = expl_temp_tmp.a_param;
                        ctx->zero_forced_buffer[1].b_param = expl_temp_tmp.b_param;
                    }
                    //  Get window of interest in from a given queue
                    // 'feedratePlanningForceZeroStop:36' [ window, NWindow ] =
                    // feedratePlanningGetwindow( ctx.k0, NWindow, curvQueue );
                    // 'feedratePlanningGetwindow:3' window = repmat( constrCurvStructType, 1, NHorz
                    // );
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
                    e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                    u_loop_ub = expl_temp_tmp.R0.size[0];
                    if (u_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[u_loop_ub],
                                  &e_expl_temp.R0.data[0]);
                    }
                    e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                    x_loop_ub = expl_temp_tmp.R1.size[0];
                    if (x_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[x_loop_ub],
                                  &e_expl_temp.R1.data[0]);
                    }
                    e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                                 expl_temp_tmp.CoeffP5.size(1));
                    y_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                    for (int i19{0}; i19 < y_loop_ub; i19++) {
                        int bb_loop_ub;
                        bb_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                        for (int i21{0}; i21 < bb_loop_ub; i21++) {
                            e_expl_temp.CoeffP5[i21 + e_expl_temp.CoeffP5.size(0) * i19] =
                                expl_temp_tmp.CoeffP5[i21 + expl_temp_tmp.CoeffP5.size(0) * i19];
                        }
                    }
                    e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                    cb_loop_ub = expl_temp_tmp.Coeff.size(0);
                    for (int i22{0}; i22 < cb_loop_ub; i22++) {
                        e_expl_temp.Coeff[i22] = expl_temp_tmp.Coeff[i22];
                    }
                    b_C.Info = expl_temp_tmp.Info;
                    b_C.tool = expl_temp_tmp.tool;
                    b_C.sp = expl_temp_tmp.sp;
                    b_C.R0.set_size(e_expl_temp.R0.size[0]);
                    eb_loop_ub = e_expl_temp.R0.size[0];
                    for (int i24{0}; i24 < eb_loop_ub; i24++) {
                        b_C.R0[i24] = e_expl_temp.R0.data[i24];
                    }
                    b_C.R1.set_size(e_expl_temp.R1.size[0]);
                    fb_loop_ub = e_expl_temp.R1.size[0];
                    for (int i25{0}; i25 < fb_loop_ub; i25++) {
                        b_C.R1[i25] = e_expl_temp.R1.data[i25];
                    }
                    b_C.delta = expl_temp_tmp.delta;
                    b_C.CorrectedHelixCenter[0] = expl_temp_tmp.CorrectedHelixCenter[0];
                    b_C.evec[0] = expl_temp_tmp.evec[0];
                    b_C.CorrectedHelixCenter[1] = expl_temp_tmp.CorrectedHelixCenter[1];
                    b_C.evec[1] = expl_temp_tmp.evec[1];
                    b_C.CorrectedHelixCenter[2] = expl_temp_tmp.CorrectedHelixCenter[2];
                    b_C.evec[2] = expl_temp_tmp.evec[2];
                    b_C.theta = expl_temp_tmp.theta;
                    b_C.pitch = expl_temp_tmp.pitch;
                    b_C.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
                    jb_loop_ub = e_expl_temp.CoeffP5.size(1);
                    for (int i29{0}; i29 < jb_loop_ub; i29++) {
                        int kb_loop_ub;
                        kb_loop_ub = e_expl_temp.CoeffP5.size(0);
                        for (int i30{0}; i30 < kb_loop_ub; i30++) {
                            b_C.CoeffP5[i30 + b_C.CoeffP5.size(0) * i29] =
                                e_expl_temp.CoeffP5[i30 + e_expl_temp.CoeffP5.size(0) * i29];
                        }
                    }
                    b_C.sp_index = expl_temp_tmp.sp_index;
                    b_C.i_begin_sp = expl_temp_tmp.i_begin_sp;
                    b_C.i_end_sp = expl_temp_tmp.i_end_sp;
                    b_C.index_smooth = expl_temp_tmp.index_smooth;
                    b_C.UseConstJerk = expl_temp_tmp.UseConstJerk;
                    b_C.ConstJerk = expl_temp_tmp.ConstJerk;
                    b_C.Coeff.set_size(e_expl_temp.Coeff.size(0));
                    lb_loop_ub = e_expl_temp.Coeff.size(0);
                    for (int i31{0}; i31 < lb_loop_ub; i31++) {
                        b_C.Coeff[i31] = e_expl_temp.Coeff[i31];
                    }
                    b_C.a_param = expl_temp_tmp.a_param;
                    b_C.b_param = expl_temp_tmp.b_param;
                    window.set_size(1, static_cast<int>(NWindow));
                    mb_loop_ub = static_cast<int>(NWindow);
                    for (int i32{0}; i32 < mb_loop_ub; i32++) {
                        window[i32] = b_C;
                    }
                    // 'feedratePlanningGetwindow:5' kend = min( double( k0 + NHorz -1 ),
                    // q_curves.size );
                    i33 = static_cast<int>(std::round(static_cast<double>(ctx->k0) + NWindow));
                    b_y = ctx->q_split.size();
                    if (static_cast<double>(i33 - 1) > b_y) {
                        b_kend = b_y;
                    } else {
                        b_kend = static_cast<unsigned int>(i33 - 1);
                    }
                    // 'feedratePlanningGetwindow:7' ind = 0;
                    b_ind = 0U;
                    // 'feedratePlanningGetwindow:9' for curv_ind = k0 : int32( kend )
                    b_curv_ind = ctx->k0;
                    exitg1 = false;
                    while ((!exitg1) && (b_curv_ind <= static_cast<int>(b_kend))) {
                        bool f_zeroFlag;
                        // 'feedratePlanningGetwindow:10' ind = ind + 1;
                        b_ind++;
                        //  store the value in the queue
                        // 'feedratePlanningGetwindow:13' curv            = q_curves.get( curv_ind
                        // );
                        ctx->q_split.get(b_curv_ind, &curv);
                        // 'feedratePlanningGetwindow:14' window( ind )   = curv;
                        window[static_cast<int>(b_ind) - 1] = curv;
                        //  Check if zero speed at the end
                        // 'feedratePlanningGetwindow:16' if( isAZeroEnd( curv ) )
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv / Info / ZSpdMode : A structure containning the information of the
                        //  curv zero speed.
                        // 'isAZeroEnd:6' zeroFlag = false;
                        f_zeroFlag = false;
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
                            f_zeroFlag = true;
                        }
                        if (f_zeroFlag) {
                            exitg1 = true;
                        } else {
                            b_curv_ind++;
                        }
                    }
                    int i34;
                    // 'feedratePlanningGetwindow:19' NWindow = ind;
                    // 'feedratePlanningForceZeroStop:38' window  = [ window,
                    // ctx.zero_forced_buffer( 1 ) ]; 'feedratePlanningForceZeroStop:39' NWindow =
                    // NWindow + 1;
                    //  Prepare the boundaries conditions of the problem
                    // 'feedratePlanningForceZeroStop:42' [ ctx, window, NWindow ] =
                    // feedratePlanningSetupCurves( ... 'feedratePlanningForceZeroStop:43'     ctx,
                    // window, NWindow );
                    i34 = window.size(1);
                    window.set_size(window.size(0), window.size(1) + 1);
                    window[i34] = ctx->zero_forced_buffer[0];
                    c_NWindow = static_cast<double>(b_ind) + 1.0;
                    feedratePlanningSetupCurves(ctx, window, &c_NWindow);
                    // 'feedratePlanningForceZeroStop:45' ctx.q_split = curvQueue;
                    ctx->q_split = curvQueue;
                    b_NWindow = c_NWindow;
                    // 'feedratePlanning:46' [ ctx, Coeff, success, status, msg ] = ...
                    // 'feedratePlanning:47'                     FeedratePlanning_LP( ctx, window,
                    // ctx.cfg.amax, ctx.cfg.jmax, ... 'feedratePlanning:48' ctx.BasisVal,
                    // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:49'
                    // ctx.u_vec, NWindow );
                    FeedratePlanning_LP(ctx, window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                        ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr,
                                        ctx->u_vec, c_NWindow, Coeff, &b_success, &b_status, &msg);
                }
                //  Extract the solution
                // 'feedratePlanning:53' if( success )
                if (b_success) {
                    bool c_zeroFlag;
                    //  Optimization succed
                    // 'feedratePlanning:55' if( coder.target( 'MATLAB' ) )
                    // 'feedratePlanning:61' kopt = 1;
                    kopt = 1.0;
                    // 'feedratePlanning:63' optimized   = true;
                    b_optimized = true;
                    // 'feedratePlanning:64' opt_struct  = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                    // 'feedratePlanning:66' if( ~isAZeroStart( opt_struct ) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroStart:6' zeroFlag = false;
                    c_zeroFlag = false;
                    // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroStart:10' if( error )
                    // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                    if ((opt_struct->Info.zspdmode == ZSpdMode_ZN) ||
                        (opt_struct->Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:14' zeroFlag = true;
                        c_zeroFlag = true;
                    }
                    if (!c_zeroFlag) {
                        int q_loop_ub;
                        // 'feedratePlanning:67' opt_struct.Coeff = Coeff( :, kopt );
                        q_loop_ub = Coeff.size(0);
                        opt_struct->Coeff.set_size(Coeff.size(0));
                        for (int i15{0}; i15 < q_loop_ub; i15++) {
                            opt_struct->Coeff[i15] = Coeff[i15];
                        }
                        // 'feedratePlanning:68' kopt = kopt + 1;
                        kopt = 2.0;
                    } else {
                        // 'feedratePlanning:69' else
                        // 'feedratePlanning:70' ctx.zero_start  = false;
                        ctx->zero_start = false;
                    }
                    //  Check if end of the queue
                    // 'feedratePlanning:74' if( ctx.zero_end && ( ctx.k0 + NWindow ) >=
                    // ctx.q_split.size )
                    if (ctx->zero_end &&
                        (static_cast<double>(static_cast<int>(std::round(
                             static_cast<double>(ctx->k0) + b_NWindow))) >= ctx->q_split.size())) {
                        // 'feedratePlanning:75' ctx.reached_end = true;
                        ctx->reached_end = true;
                    }
                } else {
                    // 'feedratePlanning:78' else
                    // 'feedratePlanning:79' ocn_assert( true, "OPTIMIZATION FAILED", mfilename );
                }
            } else {
                bool zeroFlag;
                // 'feedratePlanning:81' else
                // 'feedratePlanning:82' optimized   = true;
                b_optimized = true;
                // 'feedratePlanning:84' if( ctx.zero_forced && ( kopt > size( ctx.Coeff, 2 ) ) )
                if (ctx->zero_forced && (kopt > ctx->Coeff.size(1))) {
                    // 'feedratePlanning:85' opt_struct  = ctx.zero_forced_buffer( 1 );
                    *opt_struct = ctx->zero_forced_buffer[0];
                    // 'feedratePlanning:86' ctx.q_split.set( ctx.k0, ctx.zero_forced_buffer( 2 ) );
                    ctx->q_split.set(ctx->k0, &ctx->zero_forced_buffer[1]);
                    // 'feedratePlanning:87' ctx.k0      = ctx.k0 - 1;
                    ctx->k0--;
                    // 'feedratePlanning:88' ctx.zero_forced = false;
                    ctx->zero_forced = false;
                } else {
                    // 'feedratePlanning:89' else
                    // 'feedratePlanning:90' opt_struct = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                }
                // 'feedratePlanning:93' if( ~isAZeroEnd( opt_struct ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroEnd:6' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                // 'getZspdmode:3' error = false;
                // 'getZspdmode:5' if( isenum( speed ) )
                // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                // 'isAZeroEnd:10' if( error )
                // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                if ((opt_struct->Info.zspdmode == ZSpdMode_NZ) ||
                    (opt_struct->Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:14' zeroFlag = true;
                    zeroFlag = true;
                }
                if (!zeroFlag) {
                    int k_loop_ub;
                    // 'feedratePlanning:94' opt_struct.Coeff = ctx.Coeff( :, kopt );
                    k_loop_ub = ctx->Coeff.size(0);
                    opt_struct->Coeff.set_size(k_loop_ub);
                    for (int i8{0}; i8 < k_loop_ub; i8++) {
                        opt_struct->Coeff[i8] =
                            ctx->Coeff[i8 + ctx->Coeff.size(0) * (static_cast<int>(kopt) - 1)];
                    }
                } else {
                    // 'feedratePlanning:95' else
                    // 'feedratePlanning:96' ctx.zero_end  = false;
                    ctx->zero_end = false;
                }
                // 'feedratePlanning:99' kopt = kopt + 1;
                kopt++;
            }
            // 'feedratePlanning:102' if( coder.target( "MATLAB" ) )
        } else {
            // 'feedratePlanning:108' else
            // 'feedratePlanning:109' ctx.op = Fopt.Finished;
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
