//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcZeroStartConstraints.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "calcZeroStartConstraints.h"
#include "EvalCurvStruct.h"
#include "constJerkU.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// function [ v_0, at_0 ] = calcZeroStartConstraints( ctx, Curv )
//
// calcZeroStartConstraints : Compute the velocity and acceleration
//  required for the continuity at zero start.
//  Inputs :
//  ctx   : The context
//  Curv  : The curve
//  Outputs :
//  v_0   : Norm of the velocity
//  at_0  : Norm of the tangential acceleration
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_dt
//                CurveType Curv_Type
//                const double Curv_P0[3]
//                const double Curv_P1[3]
//                const double Curv_CorrectedHelixCenter[3]
//                const double Curv_evec[3]
//                double Curv_theta
//                double Curv_pitch
//                const double Curv_CoeffP5[6][3]
//                int Curv_sp_index
//                double Curv_ConstJerk
//                double Curv_a_param
//                double Curv_b_param
//                double *v_0
//                double *at_0
// Return Type  : void
//
namespace ocn {
void calcZeroStartConstraints(const queue_coder *ctx_q_splines, double ctx_cfg_dt,
                              CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3],
                              const double Curv_CorrectedHelixCenter[3], const double Curv_evec[3],
                              double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
                              int Curv_sp_index, double Curv_ConstJerk, double Curv_a_param,
                              double Curv_b_param, double *v_0, double *at_0)
{
    double a__3[3];
    double r1D[3];
    double r2D[3];
    double a__1;
    double a__2;
    double absxk;
    double n;
    double scale;
    double t;
    double ud;
    double udd;
    double y;
    // 'calcZeroStartConstraints:10' jps = Curv.ConstJerk;
    // 'calcZeroStartConstraints:12' [ ~, ud, udd, ~ ] = constJerkU( jps, ctx.cfg.dt, false,
    // Curv.a_param, ... 'calcZeroStartConstraints:13'                         Curv.b_param );
    constJerkU(Curv_ConstJerk, ctx_cfg_dt, false, Curv_a_param, Curv_b_param, &a__1, &ud, &udd,
               &a__2);
    // 'calcZeroStartConstraints:15' [~, r1D, r2D] = EvalCurvStruct( ctx, Curv, 1 );
    b_EvalCurvStruct(ctx_q_splines, Curv_Type, Curv_P0, Curv_P1, Curv_CorrectedHelixCenter,
                     Curv_evec, Curv_theta, Curv_pitch, Curv_CoeffP5, Curv_sp_index, Curv_a_param,
                     Curv_b_param, a__3, r1D, r2D);
    // 'calcZeroStartConstraints:17' V = r1D .* ud;
    // 'calcZeroStartConstraints:18' A = r2D .* ud .^2 + r1D .* udd;
    y = std::pow(ud, 2.0);
    // 'calcZeroStartConstraints:20' norm_vt = mysqrt( sum( V.^2, 1 ) );
    // 'mysqrt:3' y = sqrt(x);
    *v_0 = std::sqrt((std::pow(r1D[0] * ud, 2.0) + std::pow(r1D[1] * ud, 2.0)) +
                     std::pow(r1D[2] * ud, 2.0));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcZeroStartConstraints:21' t_end   = r1D / MyNorm( r1D );
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calcZeroStartConstraints:23' v_0  = norm_vt;
    // 'calcZeroStartConstraints:24' at_0 = norm( A.*t_end );
    scale = 3.3121686421112381E-170;
    absxk = std::abs((r2D[0] * y + r1D[0] * udd) * (r1D[0] / n));
    if (absxk > 3.3121686421112381E-170) {
        *at_0 = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        *at_0 = t * t;
    }
    absxk = std::abs((r2D[1] * y + r1D[1] * udd) * (r1D[1] / n));
    if (absxk > scale) {
        t = scale / absxk;
        *at_0 = *at_0 * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        *at_0 += t * t;
    }
    absxk = std::abs((r2D[2] * y + r1D[2] * udd) * (r1D[2] / n));
    if (absxk > scale) {
        t = scale / absxk;
        *at_0 = *at_0 * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        *at_0 += t * t;
    }
    *at_0 = scale * std::sqrt(*at_0);
}

} // namespace ocn

//
// File trailer for calcZeroStartConstraints.cpp
//
// [EOF]
//
