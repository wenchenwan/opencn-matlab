
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
//    ctx     :   The context structure
//    window  :   The window of curves
//    NWindow :   The number of curves in the window
//
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
    // 'feedratePlanningSetupCurves:15' first = window( 1 );
    b_first = window[0];
    // 'feedratePlanningSetupCurves:16' last  = window( NWindow );
    last = window[static_cast<int>(*NWindow) - 1];
    //  Handle the zero speed at start
    // 'feedratePlanningSetupCurves:19' if ( isAZeroStart( first ) )
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
    if ((window[0].Info.zspdmode == ZSpdMode_ZN) || (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:19' zeroFlag = true;
        zeroFlag = true;
    }
    if (zeroFlag) {
        int i;
        int i1;
        int loop_ub_tmp;
        // 'feedratePlanningSetupCurves:20' ctx.zero_start  = true;
        ctx->zero_start = true;
        // 'feedratePlanningSetupCurves:21' window          = window( 2 : end );
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
        // 'feedratePlanningSetupCurves:22' NWindow         = NWindow -1;
        (*NWindow)--;
    } else {
        // 'feedratePlanningSetupCurves:23' else
        // 'feedratePlanningSetupCurves:24' ctx.zero_start  = false;
        ctx->zero_start = false;
    }
    //  Handle the zero speed at end
    // 'feedratePlanningSetupCurves:28' if( isAZeroEnd( last ) )
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
    if ((last.Info.zspdmode == ZSpdMode_NZ) || (last.Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroEnd:18' zeroFlag = true;
        b_zeroFlag = true;
    }
    if (b_zeroFlag) {
        int i3;
        // 'feedratePlanningSetupCurves:29' ctx.zero_end    = true;
        ctx->zero_end = true;
        // 'feedratePlanningSetupCurves:30' NWindow         = NWindow -1;
        (*NWindow)--;
        // 'feedratePlanningSetupCurves:31' window          = window( 1 : end-1 );
        if (window.size(1) - 1 < 1) {
            i3 = 0;
        } else {
            i3 = window.size(1) - 1;
        }
        window.set_size(window.size(0), i3);
    } else {
        // 'feedratePlanningSetupCurves:32' else
        // 'feedratePlanningSetupCurves:33' ctx.zero_end    = false;
        ctx->zero_end = false;
    }
    //  Compute the boundary conditions (v_norm + at_norm)
    // 'feedratePlanningSetupCurves:37' if( ctx.zero_start )
    if (ctx->zero_start) {
        // 'feedratePlanningSetupCurves:38' [ v_0, at_0 ]   = calcZeroConstraints( ctx, first, false
        // );
        calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &b_first, &ctx->v_0,
                            &ctx->at_0);
        // 'feedratePlanningSetupCurves:39' ctx.v_0         = v_0;
        // 'feedratePlanningSetupCurves:40' ctx.at_0        = at_0;
    }
    // 'feedratePlanningSetupCurves:43' if( ctx.zero_end )
    if (ctx->zero_end) {
        // 'feedratePlanningSetupCurves:44' [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true
        // );
        b_calcZeroConstraints(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                              ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                              ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                              ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &last, &v_1,
                              &at_1);
        // 'feedratePlanningSetupCurves:45' ctx.v_1         = -v_1;
        ctx->v_1 = -v_1;
        // 'feedratePlanningSetupCurves:46' ctx.at_1        = -at_1;
        ctx->at_1 = -at_1;
    } else {
        // 'feedratePlanningSetupCurves:47' else
        // 'feedratePlanningSetupCurves:48' ctx.v_1         = -ctx.cfg.v_1;
        ctx->v_1 = -ctx->cfg.v_1;
        // 'feedratePlanningSetupCurves:49' ctx.at_1        = -ctx.cfg.at_1;
        ctx->at_1 = -ctx->cfg.at_1;
    }
}

} // namespace ocn

//
// File trailer for feedratePlanningSetupCurves.cpp
//
// [EOF]
//
