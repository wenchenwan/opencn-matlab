//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanning.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "feedratePlanning.h"
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
#include "coder_array.h"
#include "coder_bounded_array.h"
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
    Axes params_tmp_tool_offset;
    CurvStruct curv;
    CurvStruct opt_struct_tmp;
    SplineStruct params_tmp_spline;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double at_1;
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_tool_backangle;
    double params_tmp_tool_diameter;
    double params_tmp_tool_frontangle;
    double v_1;
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
        // 'feedratePlanning:113' if coder.target( 'MATLAB' )
        // 'feedratePlanning:116' DebugLog( DebugCfg.Validate, 'Queue empty...\n' );
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
        // 'feedratePlanning:117' op      = Fopt.Finished;
        // 'feedratePlanning:118' quit    = true;
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
            // 'feedratePlanning:26' if ~ctx.zero_end
            if (!ctx->zero_end) {
                int NWindow;
                int b_loop_ub;
                int curv_ind;
                unsigned int ind;
                unsigned int kend;
                int outsize_idx_1_tmp;
                int x;
                unsigned int y;
                bool c_zeroFlag;
                bool d_zeroFlag;
                bool e_zeroFlag;
                bool exitg1;
                // 'feedratePlanning:28' [ window, NWindow ] = get_window( ctx.k0, ctx.cfg.NHorz,
                // ctx.q_split ); 'feedratePlanning:123' window = repmat( constrCurvStructType, 1,
                // NHorz );
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
                // 'feedratePlanning:125' kend = min( double( k0 + NHorz -1 ), q_curves.size );
                x = (ctx->k0 + outsize_idx_1_tmp) - 1;
                y = ctx->q_split.size();
                if (static_cast<double>(x) > y) {
                    kend = y;
                } else {
                    kend = static_cast<unsigned int>(x);
                }
                // 'feedratePlanning:127' ind = 0;
                ind = 0U;
                // 'feedratePlanning:129' for curv_ind = k0 : int32( kend )
                curv_ind = ctx->k0;
                exitg1 = false;
                while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
                    bool b_zeroFlag;
                    // 'feedratePlanning:130' ind = ind + 1;
                    ind++;
                    //  store the value in the queue
                    // 'feedratePlanning:133' curv            = q_curves.get( curv_ind );
                    ctx->q_split.get(curv_ind, &curv);
                    // 'feedratePlanning:134' window( ind )   = curv;
                    window[static_cast<int>(ind) - 1] = curv;
                    //  Check if zero speed at the end
                    // 'feedratePlanning:136' if( isAZeroEnd( curv ) )
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
                // 'feedratePlanning:139' NWindow = ind;
                b_window.set_size(1, window.size(1));
                b_loop_ub = window.size(1);
                for (int i2{0}; i2 < b_loop_ub; i2++) {
                    b_window[i2] = window[i2];
                }
                NWindow = static_cast<int>(ind);
                // 'feedratePlanning:30' first = window( 1 );
                // 'feedratePlanning:31' last  = window( NWindow );
                //  Handle the zero speed at start
                // 'feedratePlanning:34' if ( isAZeroStart( first ) )
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
                if ((window[0].Info.zspdmode == ZSpdMode_ZN) ||
                    (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:14' zeroFlag = true;
                    c_zeroFlag = true;
                }
                if (c_zeroFlag) {
                    int c_loop_ub;
                    int i3;
                    int i4;
                    // 'feedratePlanning:35' ctx.zero_start  = true;
                    ctx->zero_start = true;
                    // 'feedratePlanning:36' window          = window( 2 : end );
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
                    // 'feedratePlanning:37' NWindow         = NWindow -1;
                    NWindow = static_cast<int>(ind) - 1;
                } else {
                    // 'feedratePlanning:38' else
                    // 'feedratePlanning:39' ctx.zero_start  = false;
                    ctx->zero_start = false;
                }
                //  Handle the zero speed at end
                // 'feedratePlanning:43' if( isAZeroEnd( last ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroEnd:6' zeroFlag = false;
                d_zeroFlag = false;
                // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                // 'getZspdmode:3' error = false;
                // 'getZspdmode:5' if( isenum( speed ) )
                // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                // 'isAZeroEnd:10' if( error )
                // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                if ((window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_NZ) ||
                    (window[static_cast<int>(ind) - 1].Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:14' zeroFlag = true;
                    d_zeroFlag = true;
                }
                if (d_zeroFlag) {
                    int i6;
                    // 'feedratePlanning:44' ctx.zero_end    = true;
                    ctx->zero_end = true;
                    // 'feedratePlanning:45' NWindow         = NWindow -1;
                    NWindow--;
                    // 'feedratePlanning:46' window          = window( 1 : end-1 );
                    if (b_window.size(1) - 1 < 1) {
                        i6 = 0;
                    } else {
                        i6 = b_window.size(1) - 1;
                    }
                    b_window.set_size(b_window.size(0), i6);
                } else {
                    // 'feedratePlanning:47' else
                    // 'feedratePlanning:48' ctx.zero_end    = false;
                    ctx->zero_end = false;
                }
                //  Compute the boundary conditions (v_norm + at_norm)
                // 'feedratePlanning:52' if( ctx.zero_start )
                if (ctx->zero_start) {
                    // 'feedratePlanning:53' [ v_0, at_0 ]   = calcZeroConstraints( ctx, first,
                    // false );
                    calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data,
                                        ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                        ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                        ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                        &window[0], &ctx->v_0, &ctx->at_0);
                    // 'feedratePlanning:54' ctx.v_0         = v_0;
                    // 'feedratePlanning:55' ctx.at_0        = at_0;
                }
                // 'feedratePlanning:58' if( ctx.zero_end )
                if (ctx->zero_end) {
                    // 'feedratePlanning:59' [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true
                    // );
                    b_calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data,
                                          ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                                          ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                                          ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                                          ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                                          &window[static_cast<int>(ind) - 1], &v_1, &at_1);
                    // 'feedratePlanning:60' ctx.v_1         = -v_1;
                    ctx->v_1 = -v_1;
                    // 'feedratePlanning:61' ctx.at_1        = -at_1;
                    ctx->at_1 = -at_1;
                } else {
                    // 'feedratePlanning:62' else
                    // 'feedratePlanning:63' ctx.v_1         = -ctx.cfg.v_1;
                    ctx->v_1 = -ctx->cfg.v_1;
                    // 'feedratePlanning:64' ctx.at_1        = -ctx.cfg.at_1;
                    ctx->at_1 = -ctx->cfg.at_1;
                }
                //  Start the optimization
                // 'feedratePlanning:68' [ ctx, Coeff, success, status, msg ] = ...
                // 'feedratePlanning:69'             FeedratePlanning_LP( ctx, window, ctx.cfg.amax,
                // ctx.cfg.jmax, ... 'feedratePlanning:70'             ctx.BasisVal, ctx.BasisValD,
                // ctx.BasisValDD, ctx.BasisIntegr, ... 'feedratePlanning:71'             ctx.u_vec,
                // NWindow );
                FeedratePlanning_LP(ctx, b_window, ctx->cfg.amax, ctx->cfg.jmax, ctx->BasisVal,
                                    ctx->BasisValD, ctx->BasisValDD, ctx->BasisIntegr, ctx->u_vec,
                                    static_cast<double>(NWindow), Coeff, &success, &status);
                //  Extract the solution
                // 'feedratePlanning:74' if( success == 1 )
                //  Optimization succed
                // 'feedratePlanning:75' kopt = 1;
                kopt = 1.0;
                //  HGS : Probably a mistake here
                // 'feedratePlanning:77' optimized   = true;
                b_optimized = true;
                // 'feedratePlanning:78' opt_struct  = ctx.q_split.get( ctx.k0 );
                ctx->q_split.get(ctx->k0, opt_struct);
                // 'feedratePlanning:80' if( ~isAZeroStart( opt_struct ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroStart:6' zeroFlag = false;
                e_zeroFlag = false;
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
                    e_zeroFlag = true;
                }
                if (!e_zeroFlag) {
                    int d_loop_ub;
                    // 'feedratePlanning:81' opt_struct.Coeff = Coeff( :, kopt );
                    d_loop_ub = Coeff.size(0);
                    opt_struct->Coeff.set_size(Coeff.size(0));
                    for (int i7{0}; i7 < d_loop_ub; i7++) {
                        opt_struct->Coeff[i7] = Coeff[i7];
                    }
                    // 'feedratePlanning:82' kopt = kopt + 1;
                    kopt = 2.0;
                } else {
                    // 'feedratePlanning:83' else
                    // 'feedratePlanning:84' ctx.zero_start  = false;
                    ctx->zero_start = false;
                }
                //  Check if end of the queue
                // 'feedratePlanning:88' if( ctx.zero_end && ( ctx.k0 + NWindow ) >=
                // ctx.q_split.size )
                if (ctx->zero_end &&
                    (static_cast<double>(ctx->k0 + NWindow) >= ctx->q_split.size())) {
                    // 'feedratePlanning:89' ctx.reached_end = true;
                    ctx->reached_end = true;
                }
            } else {
                bool zeroFlag;
                // 'feedratePlanning:95' else
                // 'feedratePlanning:96' optimized   = true;
                b_optimized = true;
                // 'feedratePlanning:97' opt_struct = ctx.q_split.get( ctx.k0 );
                ctx->q_split.get(ctx->k0, opt_struct);
                // 'feedratePlanning:99' if( ~isAZeroEnd( opt_struct ) )
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
                    int loop_ub;
                    // 'feedratePlanning:100' opt_struct.Coeff = ctx.Coeff( :, kopt );
                    loop_ub = ctx->Coeff.size(0);
                    opt_struct->Coeff.set_size(loop_ub);
                    for (int i1{0}; i1 < loop_ub; i1++) {
                        opt_struct->Coeff[i1] =
                            ctx->Coeff[i1 + ctx->Coeff.size(0) * (static_cast<int>(kopt) - 1)];
                    }
                } else {
                    // 'feedratePlanning:101' else
                    // 'feedratePlanning:102' ctx.zero_end  = false;
                    ctx->zero_end = false;
                }
                // 'feedratePlanning:104' kopt = kopt + 1;
                kopt++;
            }
        } else {
            // 'feedratePlanning:106' else
            // 'feedratePlanning:107' ctx.op = Fopt.Finished;
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
