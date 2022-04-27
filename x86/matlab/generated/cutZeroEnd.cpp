//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
#include "constJerkU.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// function [ CurvStruct1, CurvStruct2 ] = cutZeroEnd( ctx, CurvStruct )
//
// cutZeroEnd : Cut the end of the given to handle the zero speed.
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_amax[3]
//                const double ctx_cfg_jmax[3]
//                double ctx_cfg_dt
//                const CurvStruct *b_CurvStruct
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
namespace ocn {
void cutZeroEnd(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
                const double ctx_cfg_jmax[3], double ctx_cfg_dt, const CurvStruct *b_CurvStruct,
                CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    double a__1[3];
    double r0D[3];
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double b_ex;
    double b_u;
    double ex;
    double ex_tmp;
    double jps;
    double u;
    double ud_vec;
    double udd_vec;
    double uddd_vec;
    double z1_idx_1;
    double z1_idx_2;
    bool searchU;
    // 'cutZeroEnd:3' [ u, jps ] = zeroSpeedCurv( ctx, CurvStruct, true );
    //  zeroSpeedCurv : Compute the profile paramater u in case of zero start /
    //  stop. This approach assume a constant pseudo jerk. The resulting profile
    //  will respect the velocity, acceleration and jerk constraints.
    //  Inputs  :
    //    ctx     : The context
    //    curv    : The Curve Struct
    //    isEnd   : ( Boolean ) is the end of a curve
    //  Outputs :
    //    u       : Resulting U for constant jerk
    //    jps     : Resulting Pseudo jerk
    // 'zeroSpeedCurv:13' uk = 0;
    // 'zeroSpeedCurv:13' if( isEnd )
    // 'zeroSpeedCurv:13' uk = 1;
    // 'zeroSpeedCurv:15' [ ~, r1D ] = EvalCurvStruct( ctx, curv, uk );
    c_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, a__1, r1D);
    //  Compute pseudo jerk based on max allowed jerk
    // 'zeroSpeedCurv:18' jps = min( ctx.cfg.jmax ) / max( abs( r1D ) );
    ex = ctx_cfg_jmax[0];
    if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
        ex = ctx_cfg_jmax[1];
    }
    if (ex > ctx_cfg_jmax[2]) {
        ex = ctx_cfg_jmax[2];
    }
    z1_idx_1 = std::abs(r1D[1]);
    z1_idx_2 = std::abs(r1D[2]);
    ex_tmp = std::abs(r1D[0]);
    b_ex = ex_tmp;
    if (ex_tmp < z1_idx_1) {
        b_ex = z1_idx_1;
    }
    if (b_ex < z1_idx_2) {
        b_ex = z1_idx_2;
    }
    jps = ex / b_ex;
    // 'zeroSpeedCurv:20' searchU = true;
    searchU = true;
    // 'zeroSpeedCurv:20' u = 0;
    u = 0.0;
    // 'zeroSpeedCurv:22' while searchU
    while (searchU) {
        double absxk;
        double b_jps;
        double b_y;
        double d;
        double scale;
        double t;
        double y;
        // 'zeroSpeedCurv:23' [ searchU, jps, u ] = calcU( isEnd, searchU, jps, ctx, curv );
        b_jps = jps;
        //  calcU : Calcule u for a given pseudo jerk. U is assured to give velocity,
        //  acceleration and jerk below the provided limits.
        //  Inputs :
        //    isEnd : ( Boolean ) is the end of the curve.
        //    searchU : ( Boolean ) is searching a U
        //    jps : The constant pseudo jerk
        //    ctx : The context
        //    curv : The curve
        //  Outputs :
        //    searchU : ( Boolean ) is searching a U
        //    jps : The constant pseudo jerk
        //    u : The resulting u
        // 'zeroSpeedCurv:42' if( isempty( ratio ) )
        // 'zeroSpeedCurv:45' [ u, ud, udd, uddd ]  = constJerkU( jps, ctx.cfg.dt, isEnd,
        // curv.a_param, ... 'zeroSpeedCurv:46' curv.b_param );
        constJerkU(jps, ctx_cfg_dt, true, b_CurvStruct->a_param, b_CurvStruct->b_param, &b_u,
                   &ud_vec, &udd_vec, &uddd_vec);
        u = b_u;
        // 'zeroSpeedCurv:48' [ ~, V, A, J ] = calcRVAJfromU( ctx, curv, u, ud, udd, uddd );
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ctx     : The context
        //    Curv    : The curve struct
        //    u_vec   : [ 1 x M ] The vector of u
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromU:16' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, Curv, u_vec );
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, b_u,
                         r0D, r1D, r2D, r3D);
        // 'calcRVAJfromU:17' R = r0D;
        // 'calcRVAJfromU:18' V = r1D .* ud_vec;
        // 'calcRVAJfromU:19' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        y = std::pow(ud_vec, 2.0);
        // 'calcRVAJfromU:20' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .*
        // uddd_vec;
        b_y = std::pow(ud_vec, 3.0);
        // 'zeroSpeedCurv:50' if( norm( V ) > curv.FeedRate )
        scale = 3.3121686421112381E-170;
        absxk = std::abs(r1D[0] * ud_vec);
        if (absxk > 3.3121686421112381E-170) {
            d = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            d = t * t;
        }
        absxk = std::abs(r1D[1] * ud_vec);
        if (absxk > scale) {
            t = scale / absxk;
            d = d * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            d += t * t;
        }
        absxk = std::abs(r1D[2] * ud_vec);
        if (absxk > scale) {
            t = scale / absxk;
            d = d * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            d += t * t;
        }
        d = scale * std::sqrt(d);
        if (d > b_CurvStruct->FeedRate) {
            // 'zeroSpeedCurv:51' jps = jps * ratio * ( curv.FeedRate / norm( V ) ) ^ ( 1 / 2 );
            b_jps = jps * 0.9 * std::sqrt(b_CurvStruct->FeedRate / d);
        } else {
            double b_z1_tmp;
            double c_ex;
            double c_z1_tmp;
            double d_ex;
            double z1_tmp;
            z1_tmp = std::abs(r2D[0] * y + r1D[0] * udd_vec);
            b_z1_tmp = std::abs(r2D[1] * y + r1D[1] * udd_vec);
            c_z1_tmp = std::abs(r2D[2] * y + r1D[2] * udd_vec);
            c_ex = z1_tmp;
            d_ex = ctx_cfg_amax[0];
            if (z1_tmp < b_z1_tmp) {
                c_ex = b_z1_tmp;
            }
            if (ctx_cfg_amax[0] < ctx_cfg_amax[1]) {
                d_ex = ctx_cfg_amax[1];
            }
            if (c_ex < c_z1_tmp) {
                c_ex = c_z1_tmp;
            }
            if (d_ex < ctx_cfg_amax[2]) {
                d_ex = ctx_cfg_amax[2];
            }
            if (c_ex > d_ex) {
                double b_ex_tmp;
                double e_ex;
                double h_ex;
                // 'zeroSpeedCurv:52' elseif( max( abs( A ) ) > max( ctx.cfg.amax ) )
                // 'zeroSpeedCurv:53' jps = jps * ratio * ( max( abs( A ) ) / max( abs( ctx.cfg.amax
                // ) ) ) ^ ( 1 / 4 );
                e_ex = z1_tmp;
                if (z1_tmp < b_z1_tmp) {
                    e_ex = b_z1_tmp;
                }
                if (e_ex < c_z1_tmp) {
                    e_ex = c_z1_tmp;
                }
                z1_idx_1 = std::abs(ctx_cfg_amax[1]);
                z1_idx_2 = std::abs(ctx_cfg_amax[2]);
                b_ex_tmp = std::abs(ctx_cfg_amax[0]);
                h_ex = b_ex_tmp;
                if (b_ex_tmp < z1_idx_1) {
                    h_ex = z1_idx_1;
                }
                if (h_ex < z1_idx_2) {
                    h_ex = z1_idx_2;
                }
                b_jps = jps * 0.9 * std::pow(e_ex / h_ex, 0.25);
            } else {
                double d_z1_tmp;
                double e_z1_tmp;
                double f_ex;
                double f_z1_tmp;
                double g_ex;
                d_z1_tmp =
                    std::abs((r3D[0] * b_y + 3.0 * r2D[0] * ud_vec * udd_vec) + r1D[0] * uddd_vec);
                e_z1_tmp =
                    std::abs((r3D[1] * b_y + 3.0 * r2D[1] * ud_vec * udd_vec) + r1D[1] * uddd_vec);
                f_z1_tmp =
                    std::abs((r3D[2] * b_y + 3.0 * r2D[2] * ud_vec * udd_vec) + r1D[2] * uddd_vec);
                f_ex = d_z1_tmp;
                g_ex = ctx_cfg_jmax[0];
                if (d_z1_tmp < e_z1_tmp) {
                    f_ex = e_z1_tmp;
                }
                if (ctx_cfg_jmax[0] < ctx_cfg_jmax[1]) {
                    g_ex = ctx_cfg_jmax[1];
                }
                if (f_ex < f_z1_tmp) {
                    f_ex = f_z1_tmp;
                }
                if (g_ex < ctx_cfg_jmax[2]) {
                    g_ex = ctx_cfg_jmax[2];
                }
                if (f_ex > g_ex) {
                    double c_ex_tmp;
                    double i_ex;
                    double j_ex;
                    // 'zeroSpeedCurv:54' elseif( max( abs( J ) ) > max( ctx.cfg.jmax ) )
                    // 'zeroSpeedCurv:55' jps = jps * ratio * ( max( abs( J ) ) / max( abs(
                    // ctx.cfg.jmax ) ) ) ^ ( 1 / 6 );
                    i_ex = d_z1_tmp;
                    if (d_z1_tmp < e_z1_tmp) {
                        i_ex = e_z1_tmp;
                    }
                    if (i_ex < f_z1_tmp) {
                        i_ex = f_z1_tmp;
                    }
                    z1_idx_1 = std::abs(ctx_cfg_jmax[1]);
                    z1_idx_2 = std::abs(ctx_cfg_jmax[2]);
                    c_ex_tmp = std::abs(ctx_cfg_jmax[0]);
                    j_ex = c_ex_tmp;
                    if (c_ex_tmp < z1_idx_1) {
                        j_ex = z1_idx_1;
                    }
                    if (j_ex < z1_idx_2) {
                        j_ex = z1_idx_2;
                    }
                    b_jps = jps * 0.9 * std::pow(i_ex / j_ex, 0.16666666666666666);
                } else {
                    // 'zeroSpeedCurv:56' else
                    // 'zeroSpeedCurv:57' searchU = false;
                    searchU = false;
                }
            }
        }
        jps = b_jps;
    }
    // 'cutZeroEnd:5' CurvStruct1 = CurvStruct;
    *CurvStruct1 = *b_CurvStruct;
    // 'cutZeroEnd:6' CurvStruct1.b_param = 0;
    CurvStruct1->b_param = 0.0;
    // 'cutZeroEnd:7' CurvStruct1.a_param = u;
    CurvStruct1->a_param = u;
    // 'cutZeroEnd:8' CurvStruct1.UseConstJerk = false;
    CurvStruct1->UseConstJerk = false;
    // 'cutZeroEnd:9' CurvStruct1.zspdmode = ZSpdMode.NN;
    CurvStruct1->zspdmode = ZSpdMode_NN;
    // 'cutZeroEnd:10' CurvStruct1.ConstJerkMaxIterations = int32(0);
    CurvStruct1->ConstJerkMaxIterations = 0;
    // 'cutZeroEnd:11' CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
    // 'cutZeroEnd:13' CurvStruct2 = CurvStruct1;
    *CurvStruct2 = *CurvStruct1;
    // 'cutZeroEnd:14' CurvStruct2.UseConstJerk = true;
    CurvStruct2->UseConstJerk = true;
    // 'cutZeroEnd:15' CurvStruct2.ConstJerk = jps;
    CurvStruct2->ConstJerk = jps;
    // 'cutZeroEnd:16' CurvStruct2.b_param = CurvStruct1.a_param + CurvStruct1.b_param;
    CurvStruct2->b_param = u;
    // 'cutZeroEnd:17' CurvStruct2.a_param = 1 - CurvStruct2.b_param;
    CurvStruct2->a_param = 1.0 - u;
    // 'cutZeroEnd:18' CurvStruct2.zspdmode = ZSpdMode.NZ;
    CurvStruct2->zspdmode = ZSpdMode_NZ;
    // 'cutZeroEnd:20' if( coder.target("MATLAB") )
}

} // namespace ocn

//
// File trailer for cutZeroEnd.cpp
//
// [EOF]
//
