
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanningSetupCurves.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "feedratePlanningSetupCurves.h"
#include "calcZeroConstraints.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// function [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
//     ctx, window, NWindow )
//
// feedratePlanningSetupCurves : Setup the windows of curves used in the
//  optimization problem.
//
//  Inputs / Outputs :
//
//    ctx :       The context structure
//    window :    The window of curves
//    NWindow :   The number of curves in the window
//
// Arguments    : b_FeedoptContext *ctx
//                ::coder::array<CurvStruct, 2U> &window
//                double *NWindow
// Return Type  : void
//
namespace ocn {
void feedratePlanningSetupCurves(b_FeedoptContext *ctx, ::coder::array<CurvStruct, 2U> &window,
                                 double *NWindow)
{
    CurvStruct b_first;
    CurvStruct last;
    double at_1;
    double v_1;
    bool b_zeroFlag;
    bool zeroFlag;
    //  Get first and last curves
    // 'feedratePlanningSetupCurves:13' first = window( 1 );
    b_first = window[0];
    // 'feedratePlanningSetupCurves:14' last  = window( NWindow );
    last = window[static_cast<int>(*NWindow) - 1];
    //  Handle the zero speed at start
    // 'feedratePlanningSetupCurves:17' if ( isAZeroStart( first ) )
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
    if ((window[0].Info.zspdmode == ZSpdMode_ZN) || (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:14' zeroFlag = true;
        zeroFlag = true;
    }
    if (zeroFlag) {
        int i;
        int i1;
        int loop_ub_tmp;
        // 'feedratePlanningSetupCurves:18' ctx.zero_start  = true;
        ctx->zero_start = true;
        // 'feedratePlanningSetupCurves:19' window          = window( 2 : end );
        if (window.size(1) < 2) {
            i = 0;
            i1 = 0;
        } else {
            i = 1;
            i1 = window.size(1);
        }
        loop_ub_tmp = i1 - i;
        for (int i2{0}; i2 < loop_ub_tmp; i2++) {
            window[i2] = window[i + i2];
        }
        window.set_size(1, loop_ub_tmp);
        // 'feedratePlanningSetupCurves:20' NWindow         = NWindow -1;
        (*NWindow)--;
    } else {
        // 'feedratePlanningSetupCurves:21' else
        // 'feedratePlanningSetupCurves:22' ctx.zero_start  = false;
        ctx->zero_start = false;
    }
    //  Handle the zero speed at end
    // 'feedratePlanningSetupCurves:26' if( isAZeroEnd( last ) )
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
    if ((last.Info.zspdmode == ZSpdMode_NZ) || (last.Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroEnd:14' zeroFlag = true;
        b_zeroFlag = true;
    }
    if (b_zeroFlag) {
        int i3;
        // 'feedratePlanningSetupCurves:27' ctx.zero_end    = true;
        ctx->zero_end = true;
        // 'feedratePlanningSetupCurves:28' NWindow         = NWindow -1;
        (*NWindow)--;
        // 'feedratePlanningSetupCurves:29' window          = window( 1 : end-1 );
        if (window.size(1) - 1 < 1) {
            i3 = 0;
        } else {
            i3 = window.size(1) - 1;
        }
        window.set_size(window.size(0), i3);
    } else {
        // 'feedratePlanningSetupCurves:30' else
        // 'feedratePlanningSetupCurves:31' ctx.zero_end    = false;
        ctx->zero_end = false;
    }
    //  Compute the boundary conditions (v_norm + at_norm)
    // 'feedratePlanningSetupCurves:35' if( ctx.zero_start )
    if (ctx->zero_start) {
        // 'feedratePlanningSetupCurves:36' [ v_0, at_0 ]   = calcZeroConstraints( ctx, first, false
        // );
        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &b_first, &ctx->v_0,
                            &ctx->at_0);
        // 'feedratePlanningSetupCurves:37' ctx.v_0         = v_0;
        // 'feedratePlanningSetupCurves:38' ctx.at_0        = at_0;
    }
    // 'feedratePlanningSetupCurves:41' if( ctx.zero_end )
    if (ctx->zero_end) {
        // 'feedratePlanningSetupCurves:42' [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true
        // );
        b_calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                              ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                              ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                              ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &last, &v_1,
                              &at_1);
        // 'feedratePlanningSetupCurves:43' ctx.v_1         = -v_1;
        ctx->v_1 = -v_1;
        // 'feedratePlanningSetupCurves:44' ctx.at_1        = -at_1;
        ctx->at_1 = -at_1;
    } else {
        // 'feedratePlanningSetupCurves:45' else
        // 'feedratePlanningSetupCurves:46' ctx.v_1         = -ctx.cfg.v_1;
        ctx->v_1 = -ctx->cfg.v_1;
        // 'feedratePlanningSetupCurves:47' ctx.at_1        = -ctx.cfg.at_1;
        ctx->at_1 = -ctx->cfg.at_1;
    }
}

} // namespace ocn

//
// File trailer for feedratePlanningSetupCurves.cpp
//
// [EOF]
//
