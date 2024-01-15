
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
#include "constrCurvStruct.h"
#include "feedratePlanningForceZeroStop.h"
#include "feedratePlanningSetupCurves.h"
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
//  Inputs :
//    ctx : The context of the computational chain
//
//  Outputs :
//    ctx         : The context of the computational chain
//    optimized   : Is optimized
//    opt_struct  : optimized structure
//    quit        : Quit flag
//
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
    coder::rtString obj;
    ::coder::array<CurvStruct, 2U> window;
    ::coder::array<double, 2U> Coeff;
    Axes params_tmp_tool_offset;
    CurvStruct C;
    CurvStruct curv;
    SplineStruct params_tmp_spline;
    b_CurvStruct e_expl_temp;
    b_CurvStruct expl_temp_tmp;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double NWindow;
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
    char st[12];
    char b_st[11];
    char obj2Value_data[11];
    char b_obj2Value_data[10];
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
    // 'feedratePlanning:16' if( isempty( kopt ) )
    // 'feedratePlanning:18' opt_struct  = constrCurvStructType;
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
    // 'feedratePlanning:19' quit        = false;
    b_quit = false;
    //  Flag used to quit the optimization
    // 'feedratePlanning:20' optimized   = false;
    b_optimized = false;
    //  Does the optimization successed
    // 'feedratePlanning:21' ctx.op      = Fopt.Opt;
    ctx->op = Fopt_Opt;
    //  Current state of the FSM
    //  Check if empty queue after splitting. If yes, stop optimization
    // 'feedratePlanning:24' if ctx.q_split.isempty
    if (ctx->q_split.isempty()) {
        // 'feedratePlanning:25' [ ctx.op, quit ] = empty_queue_split( ctx.cfg.ENABLE_PRINT_MSG );
        //  Treat the case of an empty queue after splitting operation
        // 'feedratePlanning:119' if coder.target( 'MATLAB' )
        // 'feedratePlanning:123' ocn_print( enablePrint, "Queue empty...", mfilename );
        j_ocn_print(ctx->cfg.ENABLE_PRINT_MSG);
        // 'feedratePlanning:124' op      = Fopt.Finished;
        // 'feedratePlanning:125' quit    = true;
        ctx->op = Fopt_Finished;
        b_quit = true;
    } else {
        int b_resCount;
        unsigned int obj2;
        int resCount;
        // 'feedratePlanning:29' ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + ...
        // 'feedratePlanning:30'     ctx.q_split.size, mfilename );
        resCount = sprintf(&st[0], "%d", ctx->k0);
        if (resCount - 1 >= 0) {
            std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
        }
        obj2 = ctx->q_split.size();
        b_resCount = sprintf(&b_st[0], "%u", obj2);
        if (b_resCount - 1 >= 0) {
            std::copy(&b_st[0], &b_st[b_resCount], &b_obj2Value_data[0]);
        }
        obj.Value.size[0] = 1;
        obj.Value.size[1] = (resCount + b_resCount) + 1;
        if (resCount - 1 >= 0) {
            std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[0]);
        }
        obj.Value.data[resCount] = '/';
        for (int i5{0}; i5 < b_resCount; i5++) {
            obj.Value.data[(i5 + resCount) + 1] = b_obj2Value_data[i5];
        }
        k_ocn_print(ctx->cfg.ENABLE_PRINT_MSG, &obj);
        //  Increment index on q_split
        // 'feedratePlanning:33' if ctx.go_next
        if (ctx->go_next) {
            // 'feedratePlanning:33' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
        }
        // 'feedratePlanning:35' if ( ctx.k0 <= ctx.q_split.size )
        if (static_cast<double>(ctx->k0) <= ctx->q_split.size()) {
            // 'feedratePlanning:37' if ~ctx.zero_end
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
                // 'feedratePlanning:39' [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0,
                // ... 'feedratePlanning:40'                                 ctx.cfg.NHorz,
                // ctx.q_split );
                //  feedratePlanningGetwindow :
                //
                //  Inputs :
                //    k0          : Index in the optimization
                //    NHorz       : Number of curves in the optimization window
                //    q_curves    : Queue of curve structures
                //
                //  Outputs :
                //    window      : Window of curves structure
                //    NWindow     : Number of curves in the structures
                //
                // 'feedratePlanningGetwindow:15' window = repmat( constrCurvStructType, 1, NHorz );
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
                for (int i6{0}; i6 < h_loop_ub; i6++) {
                    int i_loop_ub;
                    i_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                    for (int i7{0}; i7 < i_loop_ub; i7++) {
                        e_expl_temp.CoeffP5[i7 + e_expl_temp.CoeffP5.size(0) * i6] =
                            expl_temp_tmp.CoeffP5[i7 + expl_temp_tmp.CoeffP5.size(0) * i6];
                    }
                }
                e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                j_loop_ub = expl_temp_tmp.Coeff.size(0);
                for (int i8{0}; i8 < j_loop_ub; i8++) {
                    e_expl_temp.Coeff[i8] = expl_temp_tmp.Coeff[i8];
                }
                C.Info = expl_temp_tmp.Info;
                C.tool = expl_temp_tmp.tool;
                C.sp = expl_temp_tmp.sp;
                C.R0.set_size(e_expl_temp.R0.size[0]);
                l_loop_ub = e_expl_temp.R0.size[0];
                for (int i10{0}; i10 < l_loop_ub; i10++) {
                    C.R0[i10] = e_expl_temp.R0.data[i10];
                }
                C.R1.set_size(e_expl_temp.R1.size[0]);
                m_loop_ub = e_expl_temp.R1.size[0];
                for (int i11{0}; i11 < m_loop_ub; i11++) {
                    C.R1[i11] = e_expl_temp.R1.data[i11];
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
                for (int i12{0}; i12 < n_loop_ub; i12++) {
                    int o_loop_ub;
                    o_loop_ub = e_expl_temp.CoeffP5.size(0);
                    for (int i13{0}; i13 < o_loop_ub; i13++) {
                        C.CoeffP5[i13 + C.CoeffP5.size(0) * i12] =
                            e_expl_temp.CoeffP5[i13 + e_expl_temp.CoeffP5.size(0) * i12];
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
                for (int i14{0}; i14 < p_loop_ub; i14++) {
                    C.Coeff[i14] = e_expl_temp.Coeff[i14];
                }
                C.a_param = expl_temp_tmp.a_param;
                C.b_param = expl_temp_tmp.b_param;
                outsize_idx_1_tmp = ctx->cfg.NHorz;
                window.set_size(1, outsize_idx_1_tmp);
                for (int i15{0}; i15 < outsize_idx_1_tmp; i15++) {
                    window[i15] = C;
                }
                // 'feedratePlanningGetwindow:17' kend = min( double( k0 + NHorz -1 ), q_curves.size
                // );
                x = (ctx->k0 + outsize_idx_1_tmp) - 1;
                y = ctx->q_split.size();
                if (static_cast<double>(x) > y) {
                    kend = y;
                } else {
                    kend = static_cast<unsigned int>(x);
                }
                // 'feedratePlanningGetwindow:19' ind = 0;
                ind = 0U;
                // 'feedratePlanningGetwindow:21' for curv_ind = k0 : int32( kend )
                curv_ind = ctx->k0;
                exitg1 = false;
                while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
                    bool b_zeroFlag;
                    // 'feedratePlanningGetwindow:22' ind = ind + 1;
                    ind++;
                    //  store the value in the queue
                    // 'feedratePlanningGetwindow:25' curv            = q_curves.get( curv_ind );
                    ctx->q_split.get(curv_ind, &curv);
                    // 'feedratePlanningGetwindow:26' window( ind )   = curv;
                    window[static_cast<int>(ind) - 1] = curv;
                    //  Check if zero speed at the end
                    // 'feedratePlanningGetwindow:28' if( isAZeroEnd( curv ) )
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
                        exitg1 = true;
                    } else {
                        curv_ind++;
                    }
                }
                // 'feedratePlanningGetwindow:31' NWindow = ind;
                //  Prepare the boundaries conditions of the problem
                // 'feedratePlanning:43' [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
                // 'feedratePlanning:44'                 ctx, window, NWindow );
                NWindow = ind;
                feedratePlanningSetupCurves(ctx, window, &NWindow);
                b_NWindow = NWindow;
                //  Start the optimization
                // 'feedratePlanning:48' [ ctx, Coeff, success, status, msg ] = ...
                // 'feedratePlanning:49'                 FeedratePlanning_LP( ctx, window,
                // ctx.cfg.amax, ctx.cfg.jmax, ... 'feedratePlanning:50' ctx.BasisVal,
                // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:51'
                // ctx.u_vec, NWindow );
                FeedratePlanning_LP(ctx, window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                    ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr, ctx->u_vec,
                                    NWindow, Coeff, &success, &status, &msg);
                b_success = success;
                // 'feedratePlanning:53' if( ~( success || ctx.zero_start || ctx.zero_end ) )
                if ((!success) && (!ctx->zero_start) && (!ctx->zero_end)) {
                    // 'feedratePlanning:54' [ ctx, window, NWindow ] =
                    // feedratePlanningForceZeroStop( ... 'feedratePlanning:55' ctx, window, NWindow
                    // );
                    c_NWindow = NWindow;
                    feedratePlanningForceZeroStop(ctx, window, &c_NWindow);
                    b_NWindow = c_NWindow;
                    // 'feedratePlanning:56' [ ctx, Coeff, success, status, msg ] = ...
                    // 'feedratePlanning:57'                     FeedratePlanning_LP( ctx, window,
                    // ctx.cfg.amax, ctx.cfg.jmax, ... 'feedratePlanning:58' ctx.BasisVal,
                    // ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:59'
                    // ctx.u_vec, NWindow );
                    FeedratePlanning_LP(ctx, window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                        ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr,
                                        ctx->u_vec, c_NWindow, Coeff, &b_success, &b_status, &msg);
                }
                //  Extract the solution
                // 'feedratePlanning:63' if( success )
                if (b_success) {
                    bool c_zeroFlag;
                    //  Optimization succed
                    // 'feedratePlanning:65' if( coder.target( 'MATLAB' ) )
                    // 'feedratePlanning:71' kopt = 1;
                    kopt = 1.0;
                    // 'feedratePlanning:73' optimized   = true;
                    b_optimized = true;
                    // 'feedratePlanning:74' opt_struct  = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                    // 'feedratePlanning:76' if( ~isAZeroStart( opt_struct ) )
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
                    c_zeroFlag = false;
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
                    if ((opt_struct->Info.zspdmode == ZSpdMode_ZN) ||
                        (opt_struct->Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:19' zeroFlag = true;
                        c_zeroFlag = true;
                    }
                    if (!c_zeroFlag) {
                        int q_loop_ub;
                        // 'feedratePlanning:77' opt_struct.Coeff = Coeff( :, kopt );
                        q_loop_ub = Coeff.size(0);
                        opt_struct->Coeff.set_size(Coeff.size(0));
                        for (int i16{0}; i16 < q_loop_ub; i16++) {
                            opt_struct->Coeff[i16] = Coeff[i16];
                        }
                        // 'feedratePlanning:78' kopt = kopt + 1;
                        kopt = 2.0;
                    } else {
                        // 'feedratePlanning:79' else
                        // 'feedratePlanning:80' ctx.zero_start  = false;
                        ctx->zero_start = false;
                    }
                    //  Check if end of the queue
                    // 'feedratePlanning:84' if( ctx.zero_end && ( ctx.k0 + NWindow ) >=
                    // ctx.q_split.size )
                    if (ctx->zero_end &&
                        (static_cast<double>(static_cast<int>(std::round(
                             static_cast<double>(ctx->k0) + b_NWindow))) >= ctx->q_split.size())) {
                        // 'feedratePlanning:85' ctx.reached_end = true;
                        ctx->reached_end = true;
                    }
                } else {
                    // 'feedratePlanning:88' else
                    // 'feedratePlanning:89' ocn_assert( true, "OPTIMIZATION FAILED...", mfilename
                    // );
                }
            } else {
                bool zeroFlag;
                // 'feedratePlanning:91' else
                // 'feedratePlanning:92' optimized   = true;
                b_optimized = true;
                // 'feedratePlanning:94' if( ctx.zero_forced && ( kopt > size( ctx.Coeff, 2 ) ) )
                if (ctx->zero_forced && (kopt > ctx->Coeff.size(1))) {
                    // 'feedratePlanning:95' opt_struct  = ctx.zero_forced_buffer( 1 );
                    *opt_struct = ctx->zero_forced_buffer[0];
                    // 'feedratePlanning:96' ctx.q_split.set( ctx.k0, ctx.zero_forced_buffer( 2 ) );
                    ctx->q_split.set(ctx->k0, &ctx->zero_forced_buffer[1]);
                    // 'feedratePlanning:97' ctx.k0      = ctx.k0 - 1;
                    ctx->k0--;
                    // 'feedratePlanning:98' ctx.zero_forced = false;
                    ctx->zero_forced = false;
                } else {
                    // 'feedratePlanning:99' else
                    // 'feedratePlanning:100' opt_struct = ctx.q_split.get( ctx.k0 );
                    ctx->q_split.get(ctx->k0, opt_struct);
                }
                // 'feedratePlanning:103' if( ~isAZeroEnd( opt_struct ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //
                //  Inputs :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                //
                //  Outputs :
                //  zeroFlag : Boolean value. TRUE mean zero flag
                // 'isAZeroEnd:10' zeroFlag = false;
                zeroFlag = false;
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
                if ((opt_struct->Info.zspdmode == ZSpdMode_NZ) ||
                    (opt_struct->Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:18' zeroFlag = true;
                    zeroFlag = true;
                }
                if (!zeroFlag) {
                    int k_loop_ub;
                    // 'feedratePlanning:104' opt_struct.Coeff = ctx.Coeff( :, kopt );
                    k_loop_ub = ctx->Coeff.size(0);
                    opt_struct->Coeff.set_size(k_loop_ub);
                    for (int i9{0}; i9 < k_loop_ub; i9++) {
                        opt_struct->Coeff[i9] =
                            ctx->Coeff[i9 + ctx->Coeff.size(0) * (static_cast<int>(kopt) - 1)];
                    }
                } else {
                    // 'feedratePlanning:105' else
                    // 'feedratePlanning:106' ctx.zero_end  = false;
                    ctx->zero_end = false;
                }
                // 'feedratePlanning:109' kopt = kopt + 1;
                kopt++;
            }
        } else {
            // 'feedratePlanning:112' else
            // 'feedratePlanning:113' ctx.op = Fopt.Finished;
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
//  Inputs :
//    ctx : The context of the computational chain
//
//  Outputs :
//    ctx         : The context of the computational chain
//    optimized   : Is optimized
//    opt_struct  : optimized structure
//    quit        : Quit flag
//
//
// Arguments    : void
// Return Type  : void
//
void feedratePlanning_init()
{
    // 'feedratePlanning:16' kopt = 1;
    kopt = 1.0;
}

} // namespace ocn

//
// File trailer for feedratePlanning.cpp
//
// [EOF]
//
