//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CheckCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:29:52
//

// Include Files
#include "CheckCurvStructs.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
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
// function ctx = CheckCurvStructs(ctx)
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
void CheckCurvStructs(const FeedoptContext *ctx)
{
    CurvStruct Curv1;
    CurvStruct Curv2;
    double a__1[3];
    double a__2[3];
    double r0D1[3];
    double r1D1[3];
    unsigned int N;
    int i;
    // 'CheckCurvStructs:3' N = ctx.q_gcode.size;
    N = ctx->q_gcode.size();
    // 'CheckCurvStructs:5' DebugLog(DebugCfg.Validate, 'Checking for cusps...\n');
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:6' DebugLog(DebugCfg.OptimProgress, 'Checking for cusps...\n');
    //  1 -> stdout
    //  2 -> stderr
    // 'DebugLog:5' if IsEnabledDebugLog(cfg)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'DebugLog:6' fprintf(1, varargin{:});
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:8' for k = 1:N-1
    i = static_cast<int>(N - 1U);
    for (int k{0}; k < i; k++) {
        double absx;
        double absxk;
        double b_absxk;
        double b_n;
        double b_scale;
        double b_t;
        double b_y;
        double scale;
        double t;
        double x;
        double y;
        signed char n;
        // 'CheckCurvStructs:9' Curv1 = ctx.q_gcode.get(k);
        ctx->q_gcode.get(k + 1U, &Curv1);
        // 'CheckCurvStructs:10' Curv2 = ctx.q_gcode.get(k+1);
        ctx->q_gcode.get(k - 4294967294U, &Curv2);
        // 'CheckCurvStructs:12' [~, r0D1] = EvalCurvStruct(ctx, Curv1, 1);
        b_EvalCurvStruct(&ctx->q_splines, Curv1.Type, Curv1.P0, Curv1.P1,
                         Curv1.CorrectedHelixCenter, Curv1.evec, Curv1.theta, Curv1.pitch,
                         Curv1.CoeffP5, Curv1.sp_index, Curv1.a_param, Curv1.b_param, a__1, r0D1);
        // 'CheckCurvStructs:13' [~, r1D1] = EvalCurvStruct(ctx, Curv2, 0);
        b_EvalCurvStruct(&ctx->q_splines, &Curv2, a__2, r1D1);
        // 'CheckCurvStructs:15' if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
        // 'iscusp:2' value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
        x = rt_remd(180.0 - ctx->cfg.CuspThreshold, 360.0);
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
        scale = 3.3121686421112381E-170;
        b_scale = 3.3121686421112381E-170;
        absxk = std::abs(r0D1[0]);
        if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
        }
        b_absxk = std::abs(r1D1[0]);
        if (b_absxk > 3.3121686421112381E-170) {
            b_y = 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / 3.3121686421112381E-170;
            b_y = b_t * b_t;
        }
        absxk = std::abs(r0D1[1]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        b_absxk = std::abs(r1D1[1]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            b_y = b_y * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            b_y += b_t * b_t;
        }
        absxk = std::abs(r0D1[2]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        b_absxk = std::abs(r1D1[2]);
        if (b_absxk > b_scale) {
            b_t = b_scale / b_absxk;
            b_y = b_y * b_t * b_t + 1.0;
            b_scale = b_absxk;
        } else {
            b_t = b_absxk / b_scale;
            b_y += b_t * b_t;
        }
        y = scale * std::sqrt(y);
        b_y = b_scale * std::sqrt(b_y);
        if (n == 0) {
            b_n = std::cos(x);
        } else if (n == 1) {
            b_n = -std::sin(x);
        } else if (n == -1) {
            b_n = std::sin(x);
        } else {
            b_n = -std::cos(x);
        }
        if (((r0D1[0] * r1D1[0] + r0D1[1] * r1D1[1]) + r0D1[2] * r1D1[2]) / (y * b_y) < b_n) {
            // 'CheckCurvStructs:16' switch Curv1.zspdmode
            switch (Curv1.zspdmode) {
            case ZSpdMode_NN:
                // 'CheckCurvStructs:17' case ZSpdMode.NN
                // 'CheckCurvStructs:18' Curv1.zspdmode = ZSpdMode.NZ;
                Curv1.zspdmode = ZSpdMode_NZ;
                break;
            case ZSpdMode_ZN:
                // 'CheckCurvStructs:19' case ZSpdMode.ZN
                // 'CheckCurvStructs:20' Curv1.zspdmode = ZSpdMode.ZZ;
                Curv1.zspdmode = ZSpdMode_ZZ;
                break;
            case ZSpdMode_NZ:
                // 'CheckCurvStructs:21' case ZSpdMode.NZ
                //  Nothing to do
                break;
            default:
                // 'CheckCurvStructs:23' case ZSpdMode.ZZ
                //  Nothing to do
                break;
            }
            // 'CheckCurvStructs:27' switch Curv2.zspdmode
            switch (Curv2.zspdmode) {
            case ZSpdMode_NN:
                // 'CheckCurvStructs:28' case ZSpdMode.NN
                // 'CheckCurvStructs:29' Curv2.zspdmode = ZSpdMode.ZN;
                Curv2.zspdmode = ZSpdMode_ZN;
                break;
            case ZSpdMode_ZN:
                // 'CheckCurvStructs:30' case ZSpdMode.ZN
                //  Nothing to do
                break;
            case ZSpdMode_NZ:
                // 'CheckCurvStructs:32' case ZSpdMode.NZ
                // 'CheckCurvStructs:33' Curv2.zspdmode = ZSpdMode.ZZ;
                Curv2.zspdmode = ZSpdMode_ZZ;
                break;
            default:
                // 'CheckCurvStructs:34' case ZSpdMode.ZZ
                //  Nothing to do
                break;
            }
            // 'CheckCurvStructs:38' ctx.q_gcode.set(k,   Curv1);
            ctx->q_gcode.set(k + 1U, &Curv1);
            // 'CheckCurvStructs:39' ctx.q_gcode.set(k+1, Curv2);
            ctx->q_gcode.set(k - 4294967294U, &Curv2);
        }
    }
}

} // namespace ocn

//
// File trailer for CheckCurvStructs.cpp
//
// [EOF]
//
