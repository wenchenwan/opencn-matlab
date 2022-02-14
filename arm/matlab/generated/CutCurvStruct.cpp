//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
//

// Include Files
#include "CutCurvStruct.h"
#include "EvalBSplineNoCtx.h"
#include "EvalCurvStruct.h"
#include "SplineLengthFindU_up.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
//
// We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
//  We determine a new value of the parameter u_tilda
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurvStruct *b_CurvStruct
//                double d1
// Return Type  : void
//
namespace ocn {
void CutCurvStruct(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                   const double ctx_cfg_GaussLegendreW[5], CurvStruct *b_CurvStruct, double d1)
{
    CurvStruct b_expl_temp;
    CurvStruct e_expl_temp;
    CurvStruct expl_temp;
    double b_a__1[5][3];
    double r1D[5][3];
    double b_uk[5];
    double d_expl_temp[5];
    double r1Dnorm[5];
    double a__1[3];
    double a__2[3];
    double b_r1D[3];
    double r1D0[3];
    double r1D1[3];
    double u0_tilda;
    double u1_tilda;
    char message[54];
    // 'CutCurvStruct:5' a = CurvStruct.a_param;
    // 'CutCurvStruct:6' b = CurvStruct.b_param;
    // 'CutCurvStruct:8' if CurvStruct.Type == CurveType.Spline
    if (b_CurvStruct->Type == CurveType_Spline) {
        // 'CutCurvStruct:10' u0_tilda = a*0+b;
        // 'CutCurvStruct:11' u1_tilda = a*1+b;
        u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
        // 'CutCurvStruct:13' if d0 ~= 0
        // 'CutCurvStruct:15' else
        // 'CutCurvStruct:16' u0_tilda = a*0+b;
        u0_tilda = b_CurvStruct->b_param;
        // 'CutCurvStruct:19' if d1 ~= 0
        if (d1 != 0.0) {
            double Lcum;
            double b_r1Dnorm;
            double c_expl_temp;
            int exitg1;
            int i;
            int i1;
            int i4;
            int k;
            // 'CutCurvStruct:20' u1_tilda  = SplineLengthFindU_down(ctx, CurvStruct, d1, u1_tilda);
            //  computes approximately the value of curve parameter u such that the arc
            //  length starting from u1 equals L.
            //  This function takes usage of the precalculated arc lengths between knots.
            //  The last integration interval is approximated by the trapezoidal rule.
            //  u1 must satisfy 0 < u1 < 1.
            //  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
            //  set to -1
            //  Warning : This function works only for B-spline of degree 3
            // 'SplineLengthFindU_down:11' DEFAULT_TOL_NR  = 1e-6;
            //  Default tolerance for Newton Raphson
            // 'SplineLengthFindU_down:12' IND_KNOTS_MULT  = 4;
            //  Index used to remove multiple knots
            //                               (ONLY TRUE FOR CUBIC SPLINE)
            //  Get the sp structure
            // 'SplineLengthFindU_down:16' Spline = ctx.q_splines.get(Curv.sp_index);
            ctx_q_splines->get(b_CurvStruct->sp_index, &expl_temp);
            // 'SplineLengthFindU_down:17' sp     = Spline.sp;
            //  Eliminate multiplicities at the end points
            // 'SplineLengthFindU_down:20' Knots  = sp.knots( IND_KNOTS_MULT : end - IND_KNOTS_MULT
            // + 1 );
            if (4 > expl_temp.sp.knots.size(1) - 3) {
                i = -1;
                i1 = -1;
            } else {
                i = 2;
                i1 = expl_temp.sp.knots.size(1) - 4;
            }
            // 'SplineLengthFindU_down:21' Lk     = sp.Lk;
            //
            // 'SplineLengthFindU_down:23' C_ASSERT_MSG = 'u1 must be %s or equal than the first
            // spline knot'; 'SplineLengthFindU_down:24' c_assert( u1 >= Knots(1),
            // sprintf(C_ASSERT_MSG, 'greater') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3'
            // if ~condition
            if (u1_tilda < expl_temp.sp.knots[i + 1]) {
                // 'c_assert:4' coder.ceval('c_assert_', message);
                for (int i2{0}; i2 < 54; i2++) {
                    message[i2] = cv2[i2];
                }
                c_assert_(&message[0]);
            }
            // 'c_assert:6' value = condition;
            // 'SplineLengthFindU_down:25' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG,
            // 'smaller') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
            if (u1_tilda > expl_temp.sp.knots[i1]) {
                // 'c_assert:4' coder.ceval('c_assert_', message);
                for (int i3{0}; i3 < 54; i3++) {
                    message[i3] = cv3[i3];
                }
                c_assert_(&message[0]);
            }
            // 'c_assert:6' value = condition;
            //
            // 'SplineLengthFindU_down:27' k = length(Knots);
            k = i1 - i;
            //
            // 'SplineLengthFindU_down:29' while u1 < Knots(k)
            do {
                exitg1 = 0;
                i4 = i + k;
                if (u1_tilda < expl_temp.sp.knots[i4]) {
                    // 'SplineLengthFindU_down:30' k = k - 1;
                    k--;
                } else {
                    exitg1 = 1;
                }
            } while (exitg1 == 0);
            //
            //  Length to next break point
            // 'SplineLengthFindU_down:34' Lcum = SplineLengthApprox_Interval1(ctx, Curv, Knots(k),
            // u1);
            //  computes approximately the arc length L with integration bounds u1 and u2.
            //  IMPORTANT : u1 and u2 should lie in the same knot interval.
            //  The computation is based on numerical Gauss Legendre integration
            //
            //  get the spline
            // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_splines.get(Curv.sp_index);
            ctx_q_splines->get(b_CurvStruct->sp_index, &b_expl_temp);
            //  get Gauss-Legendre knots and weights
            // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
            // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
            //  apply linear map from[-1, 1] to [u0, u1]
            // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
            //
            // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline, uvec);
            c_expl_temp = expl_temp.sp.knots[i4];
            for (int i5{0}; i5 < 5; i5++) {
                double d;
                d = ctx_cfg_GaussLegendreX[i5];
                d_expl_temp[i5] = (c_expl_temp * (1.0 - d) + u1_tilda * (d + 1.0)) / 2.0;
            }
            EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY, b_expl_temp.sp.CoeffZ,
                             b_expl_temp.sp.Bl.handle, d_expl_temp, b_a__1, r1D);
            // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            for (int b_k{0}; b_k < 5; b_k++) {
                r1Dnorm[b_k] = std::pow(r1D[b_k][0], 2.0);
                r1Dnorm[b_k] += std::pow(r1D[b_k][1], 2.0);
                r1Dnorm[b_k] += std::pow(r1D[b_k][2], 2.0);
            }
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
            b_r1Dnorm = 0.0;
            for (int c_k{0}; c_k < 5; c_k++) {
                double b_d1;
                b_d1 = std::sqrt(r1Dnorm[c_k]);
                r1Dnorm[c_k] = b_d1;
                b_r1Dnorm += b_d1 * ctx_cfg_GaussLegendreW[c_k];
            }
            Lcum = b_r1Dnorm * (u1_tilda - expl_temp.sp.knots[i4]) / 2.0;
            //  Gauss Legendre integration
            // 'SplineLengthApprox_Interval1:17' L = L(1);
            //  to satisfy Matlab Coder
            //
            // 'SplineLengthFindU_down:36' k = k - 1;
            // 'SplineLengthFindU_down:37' while Lcum < L
            do {
                exitg1 = 0;
                if (Lcum < d1) {
                    // 'SplineLengthFindU_down:38' if k < 1
                    if (k - 1 < 1) {
                        // 'SplineLengthFindU_down:39' u = -1;
                        u1_tilda = -1.0;
                        exitg1 = 1;
                    } else {
                        // 'SplineLengthFindU_down:42' Lcum = Lcum + Lk(k);
                        Lcum += expl_temp.sp.Lk[k - 2];
                        //  Sum up precalculated length between knots
                        // 'SplineLengthFindU_down:43' k = k - 1;
                        k--;
                    }
                } else {
                    double Lremain;
                    double u1;
                    double uk;
                    double uk_old;
                    int u1_tmp;
                    //  undo last increment
                    // 'SplineLengthFindU_down:46' k         = k + 1;
                    // 'SplineLengthFindU_down:47' Lcum      = Lcum - Lk(k);
                    Lcum -= expl_temp.sp.Lk[k - 1];
                    // 'SplineLengthFindU_down:48' Lremain   = L - Lcum;
                    Lremain = d1 - Lcum;
                    //
                    // 'SplineLengthFindU_down:51' u1     = Knots(k+1);
                    u1_tmp = i + k;
                    u1 = expl_temp.sp.knots[u1_tmp + 1];
                    //  Initial guess for Newton Raphson iteration
                    // 'SplineLengthFindU_down:53' uk     = 0.5*(Knots(k) + Knots(k+1));
                    uk = 0.5 * (expl_temp.sp.knots[u1_tmp] + expl_temp.sp.knots[u1_tmp + 1]);
                    //  Dummy value to ensure that while loop enters
                    // 'SplineLengthFindU_down:55' uk_old = 2;
                    //  Iterate until new value of uk is close to old value
                    // 'SplineLengthFindU_down:58' while abs(uk - uk_old) > DEFAULT_TOL_NR
                    uk_old = 2.0;
                    while (std::abs(uk - uk_old) > 1.0E-6) {
                        double c_r1Dnorm;
                        int b_loop_ub;
                        int c_loop_ub;
                        int loop_ub;
                        //  Evaluation of function which should become zero
                        // 'SplineLengthFindU_down:60' fk = SplineLengthApprox_Interval1(ctx, Curv,
                        // uk, u1) - Lremain;
                        //  computes approximately the arc length L with integration bounds u1 and
                        //  u2. IMPORTANT : u1 and u2 should lie in the same knot interval. The
                        //  computation is based on numerical Gauss Legendre integration
                        //
                        //  get the spline
                        // 'SplineLengthApprox_Interval1:7' Spline =
                        // ctx.q_splines.get(Curv.sp_index);
                        ctx_q_splines->get(b_CurvStruct->sp_index, &e_expl_temp);
                        b_expl_temp.sp.CoeffX.set_size(1, e_expl_temp.sp.CoeffX.size(1));
                        loop_ub = e_expl_temp.sp.CoeffX.size(1);
                        for (int i6{0}; i6 < loop_ub; i6++) {
                            b_expl_temp.sp.CoeffX[i6] = e_expl_temp.sp.CoeffX[i6];
                        }
                        b_expl_temp.sp.CoeffY.set_size(1, e_expl_temp.sp.CoeffY.size(1));
                        b_loop_ub = e_expl_temp.sp.CoeffY.size(1);
                        for (int i7{0}; i7 < b_loop_ub; i7++) {
                            b_expl_temp.sp.CoeffY[i7] = e_expl_temp.sp.CoeffY[i7];
                        }
                        b_expl_temp.sp.CoeffZ.set_size(1, e_expl_temp.sp.CoeffZ.size(1));
                        c_loop_ub = e_expl_temp.sp.CoeffZ.size(1);
                        for (int i8{0}; i8 < c_loop_ub; i8++) {
                            b_expl_temp.sp.CoeffZ[i8] = e_expl_temp.sp.CoeffZ[i8];
                        }
                        //  get Gauss-Legendre knots and weights
                        // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
                        // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
                        //  apply linear map from[-1, 1] to [u0, u1]
                        // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) +
                        // u1*(1+GL_X))/2)';
                        //
                        // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSplineNoCtx(Spline,
                        // uvec);
                        for (int i9{0}; i9 < 5; i9++) {
                            double d2;
                            d2 = ctx_cfg_GaussLegendreX[i9];
                            b_uk[i9] = (uk * (1.0 - d2) + u1 * (d2 + 1.0)) / 2.0;
                        }
                        EvalBSplineNoCtx(b_expl_temp.sp.CoeffX, b_expl_temp.sp.CoeffY,
                                         b_expl_temp.sp.CoeffZ, e_expl_temp.sp.Bl.handle, b_uk,
                                         b_a__1, r1D);
                        // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        for (int d_k{0}; d_k < 5; d_k++) {
                            r1Dnorm[d_k] = std::pow(r1D[d_k][0], 2.0);
                            r1Dnorm[d_k] += std::pow(r1D[d_k][1], 2.0);
                            r1Dnorm[d_k] += std::pow(r1D[d_k][2], 2.0);
                        }
                        // 'mysqrt:3' y = sqrt(x);
                        for (int e_k{0}; e_k < 5; e_k++) {
                            r1Dnorm[e_k] = std::sqrt(r1Dnorm[e_k]);
                        }
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
                        //  Gauss Legendre integration
                        // 'SplineLengthApprox_Interval1:17' L = L(1);
                        //  to satisfy Matlab Coder
                        // 'SplineLengthFindU_down:61' [~, r1D]  = EvalBSplineNoCtx(Spline, uk);
                        EvalBSplineNoCtx(expl_temp.sp.CoeffX, expl_temp.sp.CoeffY,
                                         expl_temp.sp.CoeffZ, expl_temp.sp.Bl.handle, uk, a__1,
                                         b_r1D);
                        //  Evaluation of the derivative of the function which should become zero
                        // 'SplineLengthFindU_down:63' Dfk       = -MyNorm(r1D);
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        //
                        // 'SplineLengthFindU_down:65' uk_old = uk;
                        uk_old = uk;
                        // 'SplineLengthFindU_down:66' uk     = uk_old - fk/Dfk;
                        c_r1Dnorm = 0.0;
                        for (int i10{0}; i10 < 5; i10++) {
                            c_r1Dnorm += r1Dnorm[i10] * ctx_cfg_GaussLegendreW[i10];
                        }
                        uk -= (c_r1Dnorm * (u1 - uk) / 2.0 - Lremain) /
                              -std::sqrt((std::pow(b_r1D[0], 2.0) + std::pow(b_r1D[1], 2.0)) +
                                         std::pow(b_r1D[2], 2.0));
                        //  Newton Raphson update
                        // 'SplineLengthFindU_down:67' if uk > u1
                        if (uk > u1) {
                            // 'SplineLengthFindU_down:68' uk = u1;
                            uk = u1;
                            //  Make sure not to run away
                        }
                    }
                    //
                    // 'SplineLengthFindU_down:72' u  = uk;
                    u1_tilda = uk;
                    exitg1 = 1;
                }
            } while (exitg1 == 0);
        } else {
            // 'CutCurvStruct:21' else
            // 'CutCurvStruct:22' u1_tilda = a*1+b;
        }
    } else {
        // 'CutCurvStruct:25' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        //  r1D0 and r1D1 are with respect to u
        // 'CutCurvStruct:31' [~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, a__1, r1D0);
        // 'CutCurvStruct:32' [~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__2,
                         r1D1);
        //  d0 = Integral_0_u0 ||r'(u)||du
        //  d1 = Integral_u1_1 ||r'(u)||du
        // 'CutCurvStruct:36' u0 = d0/MyNorm(r1D0);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'CutCurvStruct:37' u1 = 1 - d1/MyNorm(r1D1);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        //  conversion to native curve parameter u_tilda
        // 'CutCurvStruct:40' u0_tilda = a*u0+b;
        u0_tilda = b_CurvStruct->a_param *
                       (0.0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow(r1D0[1], 2.0)) +
                                        std::pow(r1D0[2], 2.0))) +
                   b_CurvStruct->b_param;
        // 'CutCurvStruct:41' u1_tilda = a*u1+b;
        u1_tilda = b_CurvStruct->a_param *
                       (1.0 - d1 / std::sqrt((std::pow(r1D1[0], 2.0) + std::pow(r1D1[1], 2.0)) +
                                             std::pow(r1D1[2], 2.0))) +
                   b_CurvStruct->b_param;
    }
    // 'CutCurvStruct:45' CurvStruct1 = CurvStruct;
    // 'CutCurvStruct:47' CurvStruct1.a_param = u1_tilda - u0_tilda;
    b_CurvStruct->a_param = u1_tilda - u0_tilda;
    // 'CutCurvStruct:48' CurvStruct1.b_param = u0_tilda;
    b_CurvStruct->b_param = u0_tilda;
}

//
// function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
//
// We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
//  We determine a new value of the parameter u_tilda
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurvStruct *b_CurvStruct
//                double d0
// Return Type  : void
//
void b_CutCurvStruct(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], CurvStruct *b_CurvStruct, double d0)
{
    double a__1[3];
    double a__2[3];
    double r1D0[3];
    double r1D1[3];
    double u0_tilda;
    double u1_tilda;
    // 'CutCurvStruct:5' a = CurvStruct.a_param;
    // 'CutCurvStruct:6' b = CurvStruct.b_param;
    // 'CutCurvStruct:8' if CurvStruct.Type == CurveType.Spline
    if (b_CurvStruct->Type == CurveType_Spline) {
        // 'CutCurvStruct:10' u0_tilda = a*0+b;
        // 'CutCurvStruct:11' u1_tilda = a*1+b;
        // 'CutCurvStruct:13' if d0 ~= 0
        if (d0 != 0.0) {
            // 'CutCurvStruct:14' u0_tilda  = SplineLengthFindU_up(ctx, CurvStruct, d0, u0_tilda);
            u0_tilda =
                SplineLengthFindU_up(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                     b_CurvStruct->sp_index, d0, b_CurvStruct->b_param);
        } else {
            // 'CutCurvStruct:15' else
            // 'CutCurvStruct:16' u0_tilda = a*0+b;
            u0_tilda = b_CurvStruct->b_param;
        }
        // 'CutCurvStruct:19' if d1 ~= 0
        // 'CutCurvStruct:21' else
        // 'CutCurvStruct:22' u1_tilda = a*1+b;
        u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
    } else {
        // 'CutCurvStruct:25' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        //  r1D0 and r1D1 are with respect to u
        // 'CutCurvStruct:31' [~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, a__1, r1D0);
        // 'CutCurvStruct:32' [~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__2,
                         r1D1);
        //  d0 = Integral_0_u0 ||r'(u)||du
        //  d1 = Integral_u1_1 ||r'(u)||du
        // 'CutCurvStruct:36' u0 = d0/MyNorm(r1D0);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'CutCurvStruct:37' u1 = 1 - d1/MyNorm(r1D1);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        //  conversion to native curve parameter u_tilda
        // 'CutCurvStruct:40' u0_tilda = a*u0+b;
        u0_tilda = b_CurvStruct->a_param *
                       (d0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow(r1D0[1], 2.0)) +
                                       std::pow(r1D0[2], 2.0))) +
                   b_CurvStruct->b_param;
        // 'CutCurvStruct:41' u1_tilda = a*u1+b;
        u1_tilda = b_CurvStruct->a_param *
                       (1.0 - 0.0 / std::sqrt((std::pow(r1D1[0], 2.0) + std::pow(r1D1[1], 2.0)) +
                                              std::pow(r1D1[2], 2.0))) +
                   b_CurvStruct->b_param;
    }
    // 'CutCurvStruct:45' CurvStruct1 = CurvStruct;
    // 'CutCurvStruct:47' CurvStruct1.a_param = u1_tilda - u0_tilda;
    b_CurvStruct->a_param = u1_tilda - u0_tilda;
    // 'CutCurvStruct:48' CurvStruct1.b_param = u0_tilda;
    b_CurvStruct->b_param = u0_tilda;
}

} // namespace ocn

//
// File trailer for CutCurvStruct.cpp
//
// [EOF]
//
