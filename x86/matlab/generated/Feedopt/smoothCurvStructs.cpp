//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: smoothCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "smoothCurvStructs.h"
#include "EvalCurvStruct.h"
#include "calcTransition.h"
#include "calc_t_nk_kappa.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function ctx = smoothCurvStructs(ctx)
//
// Optimal transitions calculation between segments whith G2 continuity
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void smoothCurvStructs(b_FeedoptContext *ctx)
{
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r11;
    ::coder::array<double, 1U> r1d1;
    ::coder::array<double, 1U> r1dd1;
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r21;
    ::coder::array<double, 1U> r2d1;
    ::coder::array<double, 1U> r2dd1;
    ::coder::array<double, 1U> r3;
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
    TransitionResult status;
    // 'smoothCurvStructs:5' if ctx.q_compress.isempty()
    if (!ctx->q_compress.isempty()) {
        unsigned int Ncrv;
        // 'smoothCurvStructs:7' Ncrv = ctx.q_compress.size;
        Ncrv = ctx->q_compress.size();
        // 'smoothCurvStructs:9' DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'smoothCurvStructs:10' DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'smoothCurvStructs:12' curv = ctx.q_compress.get( 1 );
        ctx->q_compress.get(&curv);
        // 'smoothCurvStructs:13' for k = 2 : Ncrv
        for (unsigned int k{2U}; k <= Ncrv; k++) {
            bool needStop;
            bool needTransition;
            // 'smoothCurvStructs:14' nextCurv = ctx.q_compress.get( k );
            ctx->q_compress.get(k, &nextCurv);
            // 'smoothCurvStructs:16' [ needStop, needTransition ] = check_stop_and_transition( ctx,
            // ... 'smoothCurvStructs:17'             curv, nextCurv,
            // ctx.cfg.Smoothing.ColTolSmooth, ... 'smoothCurvStructs:18'
            // ctx.cfg.Smoothing.ColTolCosSmooth );
            // -------------------------------------------------------------------------%
            //  Functions
            // -------------------------------------------------------------------------%
            // 'smoothCurvStructs:58' needStop        = false;
            needStop = false;
            // 'smoothCurvStructs:59' needTransition  = false;
            needTransition = false;
            // 'smoothCurvStructs:61' if( isAZeroEnd( curv ) )
            //  isAZeroEnd : Return true if the curv ends with zero speed
            //  Input :
            //  curv  : The curve struct
            // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
            // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'smoothCurvStructs:61' needStop = true;
                needStop = true;

                // 'isAZeroEnd:9' zeroFlag = false;
                // 'smoothCurvStructs:63' if( nextCurv.b_param > 0 )
            } else if (nextCurv.b_param <= 0.0) {
                int b_loop_ub;
                int c_k;
                int loop_ub;
                bool exitg1;
                bool isG1;
                bool isSmooth;
                bool y;
                // 'smoothCurvStructs:65' [ isSmooth ] = check_smoothness( ctx, curv, nextCurv, tol,
                // tol_cos );
                // -------------------------------------------------------------------------%
                // 'smoothCurvStructs:88' [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv0, 1 );
                e_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curv, r11, r1d1, r1dd1);
                // 'smoothCurvStructs:89' [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv1, 0 );
                f_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &nextCurv, r21, r2d1, r2dd1);
                // 'smoothCurvStructs:91' [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
                calc_t_nk_kappa(r1d1, r1dd1, t1, a__1, &kappa1);
                // 'smoothCurvStructs:92' [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );
                calc_t_nk_kappa(r2d1, r2dd1, t2, a__2, &kappa2);
                // 'smoothCurvStructs:94' isC0   = all( abs( r11 - r21 ) < tol, 'all' );
                loop_ub = r11.size(0);
                if (r11.size(0) == r21.size(0)) {
                    int i;
                    int scalarLB;
                    int vectorUB;
                    x.set_size(r11.size(0));
                    scalarLB = (r11.size(0) / 2) << 1;
                    vectorUB = scalarLB - 2;
                    for (i = 0; i <= vectorUB; i += 2) {
                        __m128d r;
                        __m128d r1;
                        r = _mm_loadu_pd(&r11[i]);
                        r1 = _mm_loadu_pd(&r21[i]);
                        _mm_storeu_pd(&x[i], _mm_sub_pd(r, r1));
                    }
                    for (i = scalarLB; i < loop_ub; i++) {
                        x[i] = r11[i] - r21[i];
                    }
                } else {
                    minus(x, r11, r21);
                }
                z1.set_size(x.size(0));
                if (x.size(0) != 0) {
                    int i1;
                    i1 = x.size(0);
                    for (int b_k{0}; b_k < i1; b_k++) {
                        z1[b_k] = std::abs(x[b_k]);
                    }
                }
                // 'smoothCurvStructs:95' isG1   = collinear( t1, t2, tol_cos );
                // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
                if ((coder::b_norm(t1) < 2.2204460492503131E-16) ||
                    (coder::b_norm(t2) < 2.2204460492503131E-16)) {
                    // 'collinear:3' value = true;
                    isG1 = true;
                } else {
                    double c;
                    int c_loop_ub;
                    int d_loop_ub;
                    // 'collinear:6' cos_angle = dot(u,v)/(MyNorm(u)*MyNorm(v));
                    // 'MyNorm:2' coder.inline('always');
                    // 'MyNorm:3' n = mysqrt(sum(x.^2));
                    // 'mysqrt:3' y = sqrt(x);
                    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                    sqrt_calls++;
                    // 'MyNorm:2' coder.inline('always');
                    // 'MyNorm:3' n = mysqrt(sum(x.^2));
                    // 'mysqrt:3' y = sqrt(x);
                    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                    sqrt_calls++;
                    // 'collinear:7' value = cos_angle >= tol_cos;
                    c = 0.0;
                    if (t1.size(0) >= 1) {
                        int ixlast;
                        ixlast = t1.size(0);
                        for (int d_k{0}; d_k < ixlast; d_k++) {
                            c += t1[d_k] * t2[d_k];
                        }
                    }
                    r2.set_size(t1.size(0));
                    c_loop_ub = t1.size(0);
                    for (int i3{0}; i3 < c_loop_ub; i3++) {
                        double varargin_1;
                        varargin_1 = t1[i3];
                        r2[i3] = std::pow(varargin_1, 2.0);
                    }
                    r3.set_size(t2.size(0));
                    d_loop_ub = t2.size(0);
                    for (int i4{0}; i4 < d_loop_ub; i4++) {
                        double b_varargin_1;
                        b_varargin_1 = t2[i4];
                        r3[i4] = std::pow(b_varargin_1, 2.0);
                    }
                    isG1 = (c / (std::sqrt(coder::sum(r2)) * std::sqrt(coder::sum(r3))) >=
                            ctx->cfg.Smoothing.ColTolCosSmooth);
                }
                // 'smoothCurvStructs:96' isG2   = all( abs( kappa1 -kappa2 ) < tol, 'all' );
                // 'smoothCurvStructs:98' isSmooth = ( isC0 && isG1 && isG2 );
                b_x.set_size(z1.size(0));
                b_loop_ub = z1.size(0);
                for (int i2{0}; i2 < b_loop_ub; i2++) {
                    b_x[i2] = (z1[i2] < ctx->cfg.Smoothing.ColTolSmooth);
                }
                y = true;
                c_k = 0;
                exitg1 = false;
                while ((!exitg1) && (c_k <= b_x.size(0) - 1)) {
                    if (!b_x[c_k]) {
                        y = false;
                        exitg1 = true;
                    } else {
                        c_k++;
                    }
                }
                if (y && isG1 && (std::abs(kappa1 - kappa2) < ctx->cfg.Smoothing.ColTolSmooth)) {
                    isSmooth = true;
                } else {
                    isSmooth = false;
                }
                // 'smoothCurvStructs:67' if( ~isSmooth )
                if (!isSmooth) {
                    // 'smoothCurvStructs:67' needTransition = true;
                    needTransition = true;
                }
            }
            // 'smoothCurvStructs:20' if( needStop )
            if (needStop) {
                //  Add a zero stop
                // 'smoothCurvStructs:22' [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv );
                // -------------------------------------------------------------------------%
                //
                // 'smoothCurvStructs:104' ctx.programmed_stop = ctx.programmed_stop + 1;
                ctx->programmed_stop++;
                // 'smoothCurvStructs:105' ctx.q_smooth.push( curv );
                ctx->q_smooth.push(&curv);
                // 'smoothCurvStructs:106' curv = nextCurv;
                curv = nextCurv;
            } else if (needTransition) {
                // 'smoothCurvStructs:23' elseif( needTransition  )
                // 'smoothCurvStructs:24' if( ctx.cfg.Smoothing.Skip  )
                if (ctx->cfg.Smoothing.Skip) {
                    //  Force a zero stop
                    // 'smoothCurvStructs:26' [ curv, nextCurv ] = create_zero_end( curv, nextCurv
                    // );
                    b_curv = curv;
                    curv = nextCurv;
                    // -------------------------------------------------------------------------%
                    // 'smoothCurvStructs:73' if( isAZeroStart( curv ) )
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  curv  : The curve struct
                    // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((b_curv.Info.zspdmode == ZSpdMode_ZN) ||
                        (b_curv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:6' zeroFlag = true;
                        // 'smoothCurvStructs:74' curv.Info.zspdmode = ZSpdMode.ZZ;
                        b_curv.Info.zspdmode = ZSpdMode_ZZ;
                    } else {
                        // 'isAZeroStart:8' zeroFlag = false;
                        // 'smoothCurvStructs:75' else
                        // 'smoothCurvStructs:76' curv.Info.zspdmode = ZSpdMode.NZ;
                        b_curv.Info.zspdmode = ZSpdMode_NZ;
                    }
                    // 'smoothCurvStructs:79' if( isAZeroEnd( nextCurv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv  : The curve struct
                    // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                    if ((nextCurv.Info.zspdmode == ZSpdMode_NZ) ||
                        (nextCurv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:7' zeroFlag = true;
                        // 'smoothCurvStructs:80' nextCurv.Info.zspdmode = ZSpdMode.ZZ;
                        curv.Info.zspdmode = ZSpdMode_ZZ;
                    } else {
                        // 'isAZeroEnd:9' zeroFlag = false;
                        // 'smoothCurvStructs:81' else
                        // 'smoothCurvStructs:82' nextCurv.Info.zspdmode = ZSpdMode.ZN;
                        curv.Info.zspdmode = ZSpdMode_ZN;
                    }
                    // 'smoothCurvStructs:27' [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv );
                    // -------------------------------------------------------------------------%
                    //
                    // 'smoothCurvStructs:104' ctx.programmed_stop = ctx.programmed_stop + 1;
                    ctx->programmed_stop++;
                    // 'smoothCurvStructs:105' ctx.q_smooth.push( curv );
                    ctx->q_smooth.push(&b_curv);
                    // 'smoothCurvStructs:106' curv = nextCurv;
                } else {
                    // 'smoothCurvStructs:28' else
                    //  Do the transition
                    // 'smoothCurvStructs:30' [ status, curv1C, curv2C, curvT ] = ...
                    // 'smoothCurvStructs:31'                 calcTransition( ctx, curv, nextCurv );
                    calcTransition(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                   ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                   ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                   ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                   ctx->cfg.NRot, ctx->cfg.D, ctx->cfg.CutOff,
                                   ctx->cfg.Smoothing.ColTolCosSmooth,
                                   ctx->cfg.Smoothing.ColTolSmooth, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &curv, &nextCurv, &status, &curv1C,
                                   &curv2C, &curvT);
                    // 'smoothCurvStructs:32' if( status == TransitionResult.Ok )
                    if (status == TransitionResult_Ok) {
                        // 'smoothCurvStructs:33' ctx.q_smooth.push( curv1C );
                        ctx->q_smooth.push(&curv1C);
                        // 'smoothCurvStructs:34' ctx.q_smooth.push( curvT );
                        ctx->q_smooth.push(&curvT);
                        // 'smoothCurvStructs:35' curv = curv2C;
                        curv = curv2C;
                    } else {
                        // 'smoothCurvStructs:36' else
                        //  Force a zero stop
                        // 'smoothCurvStructs:38' [ curv, nextCurv ] = create_zero_end( curv,
                        // nextCurv );
                        b_curv = curv;
                        curv = nextCurv;
                        // -------------------------------------------------------------------------%
                        // 'smoothCurvStructs:73' if( isAZeroStart( curv ) )
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  curv  : The curve struct
                        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if ((b_curv.Info.zspdmode == ZSpdMode_ZN) ||
                            (b_curv.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:6' zeroFlag = true;
                            // 'smoothCurvStructs:74' curv.Info.zspdmode = ZSpdMode.ZZ;
                            b_curv.Info.zspdmode = ZSpdMode_ZZ;
                        } else {
                            // 'isAZeroStart:8' zeroFlag = false;
                            // 'smoothCurvStructs:75' else
                            // 'smoothCurvStructs:76' curv.Info.zspdmode = ZSpdMode.NZ;
                            b_curv.Info.zspdmode = ZSpdMode_NZ;
                        }
                        // 'smoothCurvStructs:79' if( isAZeroEnd( nextCurv ) )
                        //  isAZeroEnd : Return true if the curv ends with zero speed
                        //  Input :
                        //  curv  : The curve struct
                        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                        if ((nextCurv.Info.zspdmode == ZSpdMode_NZ) ||
                            (nextCurv.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroEnd:7' zeroFlag = true;
                            // 'smoothCurvStructs:80' nextCurv.Info.zspdmode = ZSpdMode.ZZ;
                            curv.Info.zspdmode = ZSpdMode_ZZ;
                        } else {
                            // 'isAZeroEnd:9' zeroFlag = false;
                            // 'smoothCurvStructs:81' else
                            // 'smoothCurvStructs:82' nextCurv.Info.zspdmode = ZSpdMode.ZN;
                            curv.Info.zspdmode = ZSpdMode_ZN;
                        }
                        // 'smoothCurvStructs:39' [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv
                        // );
                        // -------------------------------------------------------------------------%
                        //
                        // 'smoothCurvStructs:104' ctx.programmed_stop = ctx.programmed_stop + 1;
                        ctx->programmed_stop++;
                        // 'smoothCurvStructs:105' ctx.q_smooth.push( curv );
                        ctx->q_smooth.push(&b_curv);
                        // 'smoothCurvStructs:106' curv = nextCurv;
                    }
                }
            } else {
                // 'smoothCurvStructs:42' else
                //  Nothing to do with the curve
                // 'smoothCurvStructs:44' ctx.q_smooth.push( curv );
                ctx->q_smooth.push(&curv);
                // 'smoothCurvStructs:45' curv = nextCurv;
                curv = nextCurv;
            }
        }
        // 'smoothCurvStructs:49' ctx.q_smooth.push( curv );
        ctx->q_smooth.push(&curv);
    }
}

} // namespace ocn

//
// File trailer for smoothCurvStructs.cpp
//
// [EOF]
//
