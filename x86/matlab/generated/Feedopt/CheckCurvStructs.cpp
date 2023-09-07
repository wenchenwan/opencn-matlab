//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CheckCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:21:23
//

// Include Files
#include "CheckCurvStructs.h"
#include "EvalCurvStructInPieceFrame.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cfloat>
#include <cmath>
#include <stdio.h>

// Function Declarations
namespace ocn {
static double rt_remd(double u0, double u1);

}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace ocn {
static double rt_remd(double u0, double u1)
{
    double y;
    if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
        double q;
        q = std::abs(u0 / u1);
        if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
            y = 0.0;
        } else {
            y = std::fmod(u0, u1);
        }
    } else {
        y = std::fmod(u0, u1);
    }
    return y;
}

//
// function [ ctx ] = CheckCurvStructs( ctx )
//
// Arguments    : const b_FeedoptContext *ctx
// Return Type  : void
//
void CheckCurvStructs(const b_FeedoptContext *ctx)
{
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> b_u_data;
    ::coder::array<double, 1U> b_v_data;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r1D1;
    CurvStruct b_curv2;
    CurvStruct curv1;
    CurvStruct curv2;
    double u_data[3];
    double v_data[3];
    unsigned int N;
    // 'CheckCurvStructs:3' N = ctx.q_gcode.size;
    N = ctx->q_gcode.size();
    // 'CheckCurvStructs:5' DebugLog( DebugCfg.Validate, 'Checking for cusps...\n' );
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf( 1, varargin{:} );
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:6' DebugLog( DebugCfg.OptimProgress, 'Checking for cusps...\n' );
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf( 1, varargin{:} );
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:8' curv1 = ctx.q_gcode.get( 1 );
    ctx->q_gcode.get(&curv1);
    // 'CheckCurvStructs:9' for k = 2 : N
    for (unsigned int k{2U}; k <= N; k++) {
        bool zeroFlag;
        // 'CheckCurvStructs:10' curv2 = ctx.q_gcode.get( k );
        ctx->q_gcode.get(k, &curv2);
        //  Detect cusp in piece frame
        // 'CheckCurvStructs:13' [~, r0D1] = EvalCurvStructInPieceFrame( ctx, curv1, 1 );
        EvalCurvStructInPieceFrame(
            &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
            ctx->cfg.maskCart.size, ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
            ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, curv1.Info,
            curv1.R0, curv1.R1, curv1.CorrectedHelixCenter, curv1.evec, curv1.theta, curv1.pitch,
            curv1.CoeffP5, curv1.sp_index, curv1.a_param, curv1.b_param, a__1, r0D1);
        // 'CheckCurvStructs:14' [~, r1D1] = EvalCurvStructInPieceFrame( ctx, curv2, 0 );
        b_curv2 = curv2;
        b_EvalCurvStructInPieceFrame(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &b_curv2, a__2, r1D1);
        // 'CheckCurvStructs:16' if ( ~isAZeroEnd( curv1 ) ) && ...
        // 'CheckCurvStructs:17'         iscusp( r0D1( ctx.cfg.indCart ), r1D1( ctx.cfg.indCart ),
        // ... 'CheckCurvStructs:18'                 ctx.cfg.Cusp.CuspThreshold )
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
        if ((curv1.Info.zspdmode == ZSpdMode_NZ) || (curv1.Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:14' zeroFlag = true;
            zeroFlag = true;
        }
        if (!zeroFlag) {
            double absx;
            double b_n;
            double c;
            double x;
            int b_loop_ub;
            int loop_ub;
            int u_size;
            int v_size;
            signed char n;
            u_size = ctx->cfg.indCart.size(0);
            loop_ub = ctx->cfg.indCart.size(0);
            for (int i{0}; i < loop_ub; i++) {
                u_data[i] = r0D1[ctx->cfg.indCart[i] - 1];
            }
            v_size = ctx->cfg.indCart.size(0);
            b_loop_ub = ctx->cfg.indCart.size(0);
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                v_data[i1] = r1D1[ctx->cfg.indCart[i1] - 1];
            }
            // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) <= cosd(180 - angle_d);
            x = rt_remd(180.0 - ctx->cfg.Cusp.CuspThreshold, 360.0);
            absx = std::abs(x);
            if (absx > 180.0) {
                if (x > 0.0) {
                    x -= 360.0;
                } else {
                    x += 360.0;
                }
                absx = std::abs(x);
            }
            if (absx <= 45.0) {
                x *= 0.017453292519943295;
                n = 0;
            } else if (absx <= 135.0) {
                if (x > 0.0) {
                    x = 0.017453292519943295 * (x - 90.0);
                    n = 1;
                } else {
                    x = 0.017453292519943295 * (x + 90.0);
                    n = -1;
                }
            } else if (x > 0.0) {
                x = 0.017453292519943295 * (x - 180.0);
                n = 2;
            } else {
                x = 0.017453292519943295 * (x + 180.0);
                n = -2;
            }
            c = 0.0;
            if (ctx->cfg.indCart.size(0) >= 1) {
                int ixlast;
                ixlast = ctx->cfg.indCart.size(0);
                for (int b_k{0}; b_k < ixlast; b_k++) {
                    c += u_data[b_k] * v_data[b_k];
                }
            }
            b_u_data.set(&u_data[0], u_size);
            b_v_data.set(&v_data[0], v_size);
            if (n == 0) {
                b_n = std::cos(x);
            } else if (n == 1) {
                b_n = -std::sin(x);
            } else if (n == -1) {
                b_n = std::sin(x);
            } else {
                b_n = -std::cos(x);
            }
            if (c / (coder::b_norm(b_u_data) * coder::b_norm(b_v_data)) <= b_n) {
                // 'CheckCurvStructs:20' switch curv1.Info.zspdmode
                switch (curv1.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:21' case ZSpdMode.NN
                    // 'CheckCurvStructs:22' curv1.Info.zspdmode = ZSpdMode.NZ;
                    curv1.Info.zspdmode = ZSpdMode_NZ;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:23' case ZSpdMode.ZN
                    // 'CheckCurvStructs:24' curv1.Info.zspdmode = ZSpdMode.ZZ;
                    curv1.Info.zspdmode = ZSpdMode_ZZ;
                    break;
                }
                // 'CheckCurvStructs:27' switch curv2.Info.zspdmode
                switch (curv2.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:28' case ZSpdMode.NN
                    // 'CheckCurvStructs:29' curv2.Info.zspdmode = ZSpdMode.ZN;
                    curv2.Info.zspdmode = ZSpdMode_ZN;
                    break;
                case ZSpdMode_NZ:
                    // 'CheckCurvStructs:30' case ZSpdMode.NZ
                    // 'CheckCurvStructs:31' curv2.Info.zspdmode = ZSpdMode.ZZ;
                    curv2.Info.zspdmode = ZSpdMode_ZZ;
                    break;
                }
                // 'CheckCurvStructs:34' ctx.q_gcode.set( k - 1,   curv1 );
                ctx->q_gcode.set(k - 1U, &curv1);
                // 'CheckCurvStructs:35' ctx.q_gcode.set( k, curv2 );
                ctx->q_gcode.set(k, &curv2);
            }
        }
        // 'CheckCurvStructs:38' curv1 = curv2;
        curv1 = curv2;
    }
}

} // namespace ocn

//
// File trailer for CheckCurvStructs.cpp
//
// [EOF]
//
