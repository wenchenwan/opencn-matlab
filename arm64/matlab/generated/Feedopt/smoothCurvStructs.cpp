
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: smoothCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "smoothCurvStructs.h"
#include "EvalCurvStruct.h"
#include "calcTransition.h"
#include "calc_t_nk_kappa.h"
#include "norm.h"
#include "ocn_assert.h"
#include "ocn_print1.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "string1.h"
#include "sum.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void create_zero_end(CurvStruct *curv, CurvStruct *nextCurv);

}

// Function Definitions
//
// function [ curv, nextCurv ] = create_zero_end( curv, nextCurv )
//
// Arguments    : CurvStruct *curv
//                CurvStruct *nextCurv
// Return Type  : void
//
namespace ocn {
static void create_zero_end(CurvStruct *curv, CurvStruct *nextCurv)
{
    bool b_zeroFlag;
    bool zeroFlag;
    // -------------------------------------------------------------------------%
    // 'smoothCurvStructs:105' if( isAZeroStart( curv ) )
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
    if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:19' zeroFlag = true;
        zeroFlag = true;
    }
    if (zeroFlag) {
        // 'smoothCurvStructs:106' curv.Info.zspdmode = ZSpdMode.ZZ;
        curv->Info.zspdmode = ZSpdMode_ZZ;
    } else {
        // 'smoothCurvStructs:107' else
        // 'smoothCurvStructs:108' curv.Info.zspdmode = ZSpdMode.NZ;
        curv->Info.zspdmode = ZSpdMode_NZ;
    }
    // 'smoothCurvStructs:111' if( isAZeroEnd( nextCurv ) )
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
    if ((nextCurv->Info.zspdmode == ZSpdMode_NZ) || (nextCurv->Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroEnd:18' zeroFlag = true;
        b_zeroFlag = true;
    }
    if (b_zeroFlag) {
        // 'smoothCurvStructs:112' nextCurv.Info.zspdmode = ZSpdMode.ZZ;
        nextCurv->Info.zspdmode = ZSpdMode_ZZ;
    } else {
        // 'smoothCurvStructs:113' else
        // 'smoothCurvStructs:114' nextCurv.Info.zspdmode = ZSpdMode.ZN;
        nextCurv->Info.zspdmode = ZSpdMode_ZN;
    }
}

//
// function [ ctx ] = smoothCurvStructs( ctx )
//
// smoothCurvStructs : Check if the curves in the q_compress queue are G2.
//  If not, a transition is required.
//
//  Note : If the computation of a transition fails. A zero stop is forced.
//
//  Inputs :
//    ctx : Context of the computational chain.
//
//  Outputs :
//    ctx : Context of the computational chain.
//
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
void smoothCurvStructs(b_FeedoptContext *ctx)
{
    coder::rtString obj;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r11;
    ::coder::array<double, 1U> r1d1;
    ::coder::array<double, 1U> r1dd1;
    ::coder::array<double, 1U> r21;
    ::coder::array<double, 1U> r2d1;
    ::coder::array<double, 1U> r2dd1;
    ::coder::array<double, 1U> t1;
    ::coder::array<double, 1U> t2;
    ::coder::array<double, 1U> x;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 1U> b_x;
    CurvStruct b_curv;
    CurvStruct curv;
    CurvStruct curv1C;
    CurvStruct curv2C;
    CurvStruct curvT;
    CurvStruct nextCurv;
    double kappa1;
    double kappa2;
    int ret;
    char st[12];
    char b_st[11];
    char obj2Value_data[11];
    char b_obj2Value_data[10];
    TransitionResult status;
    //  Optimal transitions calculation between segments whith G2 continuity
    // 'smoothCurvStructs:16' if ctx.q_compress.isempty()
    if (!ctx->q_compress.isempty()) {
        unsigned int Ncrv;
        // 'smoothCurvStructs:17' ctx.k0  = int32( 1 );
        ctx->k0 = 1;
        // 'smoothCurvStructs:18' Ncrv    = ctx.q_compress.size;
        Ncrv = ctx->q_compress.size();
        // 'smoothCurvStructs:20' DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
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
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'smoothCurvStructs:21' DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );
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
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'smoothCurvStructs:23' curv = ctx.q_compress.get( 1 );
        ctx->q_compress.get(&curv);
        // 'smoothCurvStructs:24' for k = 2 : Ncrv
        for (unsigned int k{2U}; k <= Ncrv; k++) {
            int b_resCount;
            int resCount;
            bool needStop;
            bool needTransition;
            bool zeroFlag;
            // 'smoothCurvStructs:25' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
            // 'smoothCurvStructs:26' ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + Ncrv,
            // mfilename );
            resCount = sprintf(&st[0], "%d", ctx->k0);
            if (resCount - 1 >= 0) {
                std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
            }
            b_resCount = sprintf(&b_st[0], "%u", Ncrv);
            if (b_resCount - 1 >= 0) {
                std::copy(&b_st[0], &b_st[b_resCount], &b_obj2Value_data[0]);
            }
            obj.Value.size[0] = 1;
            obj.Value.size[1] = (resCount + b_resCount) + 1;
            if (resCount - 1 >= 0) {
                std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[0]);
            }
            obj.Value.data[resCount] = '/';
            for (int i{0}; i < b_resCount; i++) {
                obj.Value.data[(i + resCount) + 1] = b_obj2Value_data[i];
            }
            h_ocn_print(ctx->cfg.ENABLE_PRINT_MSG, &obj);
            // 'smoothCurvStructs:28' nextCurv = ctx.q_compress.get( k );
            ctx->q_compress.get(k, &nextCurv);
            // 'smoothCurvStructs:30' [ needStop, needTransition ] = check_stop_and_transition( ctx,
            // ... 'smoothCurvStructs:31'         curv, nextCurv, ctx.cfg.Smoothing.ColTolSmooth,
            // ... 'smoothCurvStructs:32'         ctx.cfg.Smoothing.ColTolCosSmooth );
            // -------------------------------------------------------------------------%
            //  Functions
            // -------------------------------------------------------------------------%
            // 'smoothCurvStructs:90' needStop        = false;
            needStop = false;
            // 'smoothCurvStructs:91' needTransition  = false;
            needTransition = false;
            // 'smoothCurvStructs:93' if( isAZeroEnd( curv ) )
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
            if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:18' zeroFlag = true;
                zeroFlag = true;
            }
            if (zeroFlag) {
                // 'smoothCurvStructs:93' needStop = true;
                needStop = true;

                // 'smoothCurvStructs:95' if( nextCurv.b_param > 0 )
            } else if (nextCurv.b_param <= 0.0) {
                int b_loop_ub;
                int c_k;
                int loop_ub;
                bool exitg1;
                bool isG1;
                bool isSmooth;
                bool varargout_1;
                // 'smoothCurvStructs:97' [ isSmooth ] = check_smoothness( ctx, curv, nextCurv, tol,
                // tol_cos );
                // -------------------------------------------------------------------------%
                // 'smoothCurvStructs:120' [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv0, 1 );
                f_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curv, r11, r1d1, r1dd1);
                // 'smoothCurvStructs:121' [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv1, 0 );
                g_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &nextCurv, r21, r2d1, r2dd1);
                // 'smoothCurvStructs:123' [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
                calc_t_nk_kappa(r1d1, r1dd1, t1, a__1, &kappa1);
                // 'smoothCurvStructs:124' [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );
                calc_t_nk_kappa(r2d1, r2dd1, t2, a__2, &kappa2);
                // 'smoothCurvStructs:126' isC0   = all( abs( r11 - r21 ) < tol, 'all' );
                loop_ub = r11.size(0);
                if (r11.size(0) == r21.size(0)) {
                    x.set_size(r11.size(0));
                    for (int i1{0}; i1 < loop_ub; i1++) {
                        x[i1] = r11[i1] - r21[i1];
                    }
                } else {
                    minus(x, r11, r21);
                }
                z1.set_size(x.size(0));
                if (x.size(0) != 0) {
                    int i2;
                    i2 = x.size(0);
                    for (int b_k{0}; b_k < i2; b_k++) {
                        z1[b_k] = std::abs(x[b_k]);
                    }
                }
                // 'smoothCurvStructs:127' isG1   = collinear( t1, t2, tol_cos );
                //  collinear : Check if the two vectors are collinear based on a given
                //  cos tolerance.
                //
                //  Inputs :
                //    u       : A vector in R^n
                //    v       : A vector in R^n
                //    tol_cos : A cos tolerance
                //
                //  Outputs :
                //    valid   : Boolean value, TRUE if the two vectors are collinear
                //
                // 'collinear:13' if ( norm( u ) < eps || norm( v ) < eps )
                if ((coder::b_norm(t1) < 2.2204460492503131E-16) ||
                    (coder::b_norm(t2) < 2.2204460492503131E-16)) {
                    // 'collinear:14' valid = true;
                    isG1 = true;
                } else {
                    double c;
                    double c_x;
                    double d_x;
                    int c_loop_ub;
                    int d_loop_ub;
                    // 'collinear:17' cos_angle   = dot( u, v ) / ( MyNorm( u ) * MyNorm( v ) );
                    //  MyNorm : My implementation of the norm computation.
                    //
                    //  Inputs :
                    //    x   : The input vector.
                    //
                    //  Outputs :
                    //    n   : The resulting norm.
                    //
                    // 'MyNorm:10' coder.inline( 'always' );
                    // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
                    r.set_size(t1.size(0));
                    c_loop_ub = t1.size(0);
                    for (int i4{0}; i4 < c_loop_ub; i4++) {
                        double varargin_1;
                        varargin_1 = t1[i4];
                        r[i4] = std::pow(varargin_1, 2.0);
                    }
                    c_x = coder::sum(r);
                    //  mysqrt : Custom implementation of the sqrt method.
                    //
                    //  Inputs :
                    //    x : Value used for the computation
                    //  Outputs :
                    //    y : Resulting value
                    //
                    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
                    ocn_assert(c_x >= 0.0);
                    // 'mysqrt:11' y = sqrt(x);
                    //  MyNorm : My implementation of the norm computation.
                    //
                    //  Inputs :
                    //    x   : The input vector.
                    //
                    //  Outputs :
                    //    n   : The resulting norm.
                    //
                    // 'MyNorm:10' coder.inline( 'always' );
                    // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
                    r.set_size(t2.size(0));
                    d_loop_ub = t2.size(0);
                    for (int i5{0}; i5 < d_loop_ub; i5++) {
                        double b_varargin_1;
                        b_varargin_1 = t2[i5];
                        r[i5] = std::pow(b_varargin_1, 2.0);
                    }
                    d_x = coder::sum(r);
                    //  mysqrt : Custom implementation of the sqrt method.
                    //
                    //  Inputs :
                    //    x : Value used for the computation
                    //  Outputs :
                    //    y : Resulting value
                    //
                    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
                    ocn_assert(d_x >= 0.0);
                    // 'mysqrt:11' y = sqrt(x);
                    // 'collinear:18' valid       = ( cos_angle >= tol_cos );
                    c = 0.0;
                    if (t1.size(0) >= 1) {
                        int ixlast;
                        ixlast = t1.size(0);
                        for (int d_k{0}; d_k < ixlast; d_k++) {
                            c += t1[d_k] * t2[d_k];
                        }
                    }
                    isG1 = (c / (std::sqrt(c_x) * std::sqrt(d_x)) >=
                            ctx->cfg.Smoothing.ColTolCosSmooth);
                }
                // 'smoothCurvStructs:128' isG2   = all( abs( kappa1 -kappa2 ) < tol, 'all' );
                // 'smoothCurvStructs:130' isSmooth = ( isC0 && isG1 && isG2 );
                b_x.set_size(z1.size(0));
                b_loop_ub = z1.size(0);
                for (int i3{0}; i3 < b_loop_ub; i3++) {
                    b_x[i3] = (z1[i3] < ctx->cfg.Smoothing.ColTolSmooth);
                }
                varargout_1 = true;
                c_k = 0;
                exitg1 = false;
                while ((!exitg1) && (c_k <= b_x.size(0) - 1)) {
                    if (!b_x[c_k]) {
                        varargout_1 = false;
                        exitg1 = true;
                    } else {
                        c_k++;
                    }
                }
                if (varargout_1 && isG1 &&
                    (std::abs(kappa1 - kappa2) < ctx->cfg.Smoothing.ColTolSmooth)) {
                    isSmooth = true;
                } else {
                    isSmooth = false;
                }
                // 'smoothCurvStructs:99' if( ~isSmooth )
                if (!isSmooth) {
                    // 'smoothCurvStructs:99' needTransition = true;
                    needTransition = true;
                }
            }
            // 'smoothCurvStructs:34' if( needStop )
            if (needStop) {
                //  Add a zero stop
                // 'smoothCurvStructs:36' [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv );
                // -------------------------------------------------------------------------%
                //
                // 'smoothCurvStructs:136' ctx.q_smooth.push( curv );
                ctx->q_smooth.push(&curv);
                // 'smoothCurvStructs:137' curv = nextCurv;
                curv = nextCurv;
                // 'smoothCurvStructs:37' if( coder.target( "MATLAB" ) )
            } else if (needTransition) {
                // 'smoothCurvStructs:40' elseif( needTransition  )
                // 'smoothCurvStructs:41' if( ctx.cfg.Smoothing.Skip  )
                if (ctx->cfg.Smoothing.Skip) {
                    //  Force a zero stop
                    // 'smoothCurvStructs:43' [ curv, nextCurv ]  = create_zero_end( curv, nextCurv
                    // );
                    b_curv = curv;
                    curv = nextCurv;
                    create_zero_end(&b_curv, &curv);
                    // 'smoothCurvStructs:44' [ ctx, curv ]       = add_zero_stop( ctx, curv,
                    // nextCurv );
                    // -------------------------------------------------------------------------%
                    //
                    // 'smoothCurvStructs:136' ctx.q_smooth.push( curv );
                    ctx->q_smooth.push(&b_curv);
                    // 'smoothCurvStructs:137' curv = nextCurv;
                    // 'smoothCurvStructs:45' if( coder.target( "MATLAB" ) )
                } else {
                    // 'smoothCurvStructs:48' else
                    //  Do the transition
                    // 'smoothCurvStructs:50' [ status, curv1C, curv2C, curvT, ret ] = ...
                    // 'smoothCurvStructs:51'                 calcTransition( ctx, curv, nextCurv );
                    calcTransition(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.D, ctx->cfg.CutOff,
                                   ctx->cfg.Smoothing.ColTolCosSmooth,
                                   ctx->cfg.Smoothing.ColTolSmooth, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &curv, &nextCurv, &status, &curv1C,
                                   &curv2C, &curvT, &ret);
                    // 'smoothCurvStructs:52' if( status == TransitionResult.Ok )
                    if (status == TransitionResult_Ok) {
                        // 'smoothCurvStructs:53' ctx.q_smooth.push( curv1C );
                        ctx->q_smooth.push(&curv1C);
                        // 'smoothCurvStructs:54' ctx.q_smooth.push( curvT );
                        ctx->q_smooth.push(&curvT);
                        // 'smoothCurvStructs:55' curv = curv2C;
                        curv = curv2C;
                        // 'smoothCurvStructs:57' if( coder.target( "MATLAB" ) )
                    } else {
                        // 'smoothCurvStructs:60' else
                        //  Force a zero stop
                        // 'smoothCurvStructs:62' [ curv, nextCurv ]  = create_zero_end( curv,
                        // nextCurv );
                        b_curv = curv;
                        curv = nextCurv;
                        create_zero_end(&b_curv, &curv);
                        // 'smoothCurvStructs:64' if( coder.target( "MATLAB" ) )
                        // 'smoothCurvStructs:67' [ ctx, curv ]       = add_zero_stop( ctx, curv,
                        // nextCurv );
                        // -------------------------------------------------------------------------%
                        //
                        // 'smoothCurvStructs:136' ctx.q_smooth.push( curv );
                        ctx->q_smooth.push(&b_curv);
                        // 'smoothCurvStructs:137' curv = nextCurv;
                    }
                }
            } else {
                // 'smoothCurvStructs:71' else
                //  Nothing to do with the curve
                // 'smoothCurvStructs:73' ctx.q_smooth.push( curv );
                ctx->q_smooth.push(&curv);
                // 'smoothCurvStructs:74' curv = nextCurv;
                curv = nextCurv;
                // 'smoothCurvStructs:75' if( coder.target( "MATLAB" ) )
            }
        }
        // 'smoothCurvStructs:81' ctx.q_smooth.push( curv );
        ctx->q_smooth.push(&curv);
    }
}

} // namespace ocn

//
// File trailer for smoothCurvStructs.cpp
//
// [EOF]
//
