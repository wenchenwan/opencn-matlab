
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CheckCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "CheckCurvStructs.h"
#include "EvalCurvStructInPieceFrame.h"
#include "Kinematics.h"
#include "norm.h"
#include "ocn_print1.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "string1.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
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
// CheckCurvStruct : Check if the curve contains some CUSP. If so force a
//  zero stop.
//
//  Inputs    :
//    ctx :   The context of the computational chain
//  Outputs   :
//    ctx :   The context of the computational chain
//
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
void CheckCurvStructs(b_FeedoptContext *ctx)
{
    coder::rtString obj;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> b_u_data;
    ::coder::array<double, 1U> b_v_data;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r1D1;
    CurvStruct curv1;
    CurvStruct curv2;
    double u_data[3];
    double v_data[3];
    unsigned int N;
    char st[12];
    char b_st[11];
    char obj2Value_data[11];
    char b_obj2Value_data[10];
    // 'CheckCurvStructs:10' ctx.k0  = int32( 1 );
    ctx->k0 = 1;
    // 'CheckCurvStructs:11' N       = ctx.q_gcode.size;
    N = ctx->q_gcode.size();
    // 'CheckCurvStructs:13' DebugLog( DebugCfg.Validate, 'Checking for cusps...\n' );
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
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:14' DebugLog( DebugCfg.OptimProgress, 'Checking for cusps...\n' );
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
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
    // 'CheckCurvStructs:16' curv1 = ctx.q_gcode.get( 1 );
    ctx->q_gcode.get(&curv1);
    // 'CheckCurvStructs:17' for k = 2 : N
    for (unsigned int k{2U}; k <= N; k++) {
        int b_resCount;
        int resCount;
        bool zeroFlag;
        // 'CheckCurvStructs:18' ctx.k0  = ctx.k0 + 1;
        ctx->k0++;
        // 'CheckCurvStructs:19' curv2   = ctx.q_gcode.get( k );
        ctx->q_gcode.get(k, &curv2);
        // 'CheckCurvStructs:20' ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + N,
        // mfilename );
        resCount = sprintf(&st[0], "%d", ctx->k0);
        if (resCount - 1 >= 0) {
            std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
        }
        b_resCount = sprintf(&b_st[0], "%u", N);
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
        f_ocn_print(ctx->cfg.ENABLE_PRINT_MSG, &obj);
        //  Detect cusp in piece frame
        // 'CheckCurvStructs:23' [~, r0D1] = EvalCurvStructInPieceFrame( ctx, curv1, 1 );
        EvalCurvStructInPieceFrame(
            &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
            ctx->cfg.maskCart.size, ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
            ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &ctx->kin,
            curv1.Info, curv1.R0, curv1.R1, curv1.CorrectedHelixCenter, curv1.evec, curv1.theta,
            curv1.pitch, curv1.CoeffP5, curv1.sp_index, curv1.a_param, curv1.b_param, a__1, r0D1);
        // 'CheckCurvStructs:24' [~, r1D1] = EvalCurvStructInPieceFrame( ctx, curv2, 0 );
        b_EvalCurvStructInPieceFrame(
            &ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
            ctx->cfg.maskCart.size, ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
            ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &ctx->kin,
            curv2.Info, curv2.R0, curv2.R1, curv2.CorrectedHelixCenter, curv2.evec, curv2.theta,
            curv2.pitch, curv2.CoeffP5, curv2.sp_index, curv2.a_param, curv2.b_param, a__2, r1D1);
        // 'CheckCurvStructs:26' if ( ~isAZeroEnd( curv1 ) ) && ...
        // 'CheckCurvStructs:27'         iscusp( r0D1( ctx.cfg.indCart ), r1D1( ctx.cfg.indCart ),
        // ... 'CheckCurvStructs:28'                 ctx.cfg.Cusp.CuspThreshold )
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
        if ((curv1.Info.zspdmode == ZSpdMode_NZ) || (curv1.Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
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
            for (int i1{0}; i1 < loop_ub; i1++) {
                u_data[i1] = r0D1[ctx->cfg.indCart[i1] - 1];
            }
            v_size = ctx->cfg.indCart.size(0);
            b_loop_ub = ctx->cfg.indCart.size(0);
            for (int i2{0}; i2 < b_loop_ub; i2++) {
                v_data[i2] = r1D1[ctx->cfg.indCart[i2] - 1];
            }
            //  iscusp : Perdicat, TRUE means a CUSP has been detected
            //
            //  Inputs :
            //  u : A vector left side
            //  v : A vector right side
            //  angle_d : Angle value in degree
            //
            //  Outputs :
            //  value : Boolean value. TRUE means a CUSP has been detected
            //
            // 'iscusp:12' value = dot(u,v)/(norm(u)*norm(v)) <= cosd(180 - angle_d);
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
                // 'CheckCurvStructs:30' switch curv1.Info.zspdmode
                switch (curv1.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:31' case ZSpdMode.NN
                    // 'CheckCurvStructs:32' curv1.Info.zspdmode = ZSpdMode.NZ;
                    curv1.Info.zspdmode = ZSpdMode_NZ;
                    break;
                case ZSpdMode_ZN:
                    // 'CheckCurvStructs:33' case ZSpdMode.ZN
                    // 'CheckCurvStructs:34' curv1.Info.zspdmode = ZSpdMode.ZZ;
                    curv1.Info.zspdmode = ZSpdMode_ZZ;
                    break;
                default:
                    // 'CheckCurvStructs:35' otherwise
                    break;
                }
                // 'CheckCurvStructs:38' switch curv2.Info.zspdmode
                switch (curv2.Info.zspdmode) {
                case ZSpdMode_NN:
                    // 'CheckCurvStructs:39' case ZSpdMode.NN
                    // 'CheckCurvStructs:40' curv2.Info.zspdmode = ZSpdMode.ZN;
                    curv2.Info.zspdmode = ZSpdMode_ZN;
                    break;
                case ZSpdMode_NZ:
                    // 'CheckCurvStructs:41' case ZSpdMode.NZ
                    // 'CheckCurvStructs:42' curv2.Info.zspdmode = ZSpdMode.ZZ;
                    curv2.Info.zspdmode = ZSpdMode_ZZ;
                    break;
                default:
                    // 'CheckCurvStructs:43' otherwise
                    break;
                }
                // 'CheckCurvStructs:46' ctx.q_gcode.set( k - 1,   curv1 );
                ctx->q_gcode.set(k - 1U, &curv1);
                // 'CheckCurvStructs:47' ctx.q_gcode.set( k, curv2 );
                ctx->q_gcode.set(k, &curv2);
                // 'CheckCurvStructs:49' if( coder.target( "MATLAB" ) )
            }
        }
        // 'CheckCurvStructs:54' curv1 = curv2;
        curv1 = curv2;
    }
}

} // namespace ocn

//
// File trailer for CheckCurvStructs.cpp
//
// [EOF]
//
