//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcTransition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 14:58:55
//

// Include Files
#include "CalcTransition.h"
#include "ConstrTransP5Struct.h"
#include "CutCurvStruct.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation.h"
#include "LengthCurv.h"
#include "PrintCurvStruct.h"
#include "SplineLengthApproxGL_bounds.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ...
//     CalcTransition(ctx, CurvStruct1, CurvStruct2)
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *CurvStruct1
//                const CurvStruct *CurvStruct2
//                CurvStruct *CurvStruct1_C
//                CurvStruct *CurvStruct_T
//                CurvStruct *CurvStruct2_C
//                TransitionResult *status
// Return Type  : void
//
namespace ocn {
void CalcTransition(const FeedoptContext *ctx, const CurvStruct *CurvStruct1,
                    const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                    CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C, TransitionResult *status)
{
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    double p5[6][3];
    double b_CurvStruct1[2][3];
    double c_CurvStruct1[2][3];
    double r0D0[3];
    double r0D0_1[3];
    double r0D0_2[3];
    double r0D1[3];
    double r0D1_1[3];
    double r0D1_2[3];
    double r0D2[3];
    double r1D0[3];
    double r1D0_1[3];
    double r1D0_2[3];
    double r1D1[3];
    double r1D1_1[3];
    double r1D1_2[3];
    double r1D2[3];
    double CutOff;
    double CutOff_tmp;
    double Length_Threshold;
    double a__1;
    double a__2;
    unsigned long u;
    int ret;
    bool guard1{false};
    TransitionResult b_status;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'CalcTransition:4' coder.inline("never");
    // 'CalcTransition:6' CutOff=ctx.cfg.CutOff;
    CutOff_tmp = ctx->cfg.CutOff;
    CutOff = CutOff_tmp;
    // 'CalcTransition:7' ColTolCos=ctx.cfg.ColTolCos;
    //  If the 1st or the 2nd Curve lenth is shorter than 3*CutOff,
    //  we will recalculate Cutoff. This new value will be smaller than before.
    //  The 3 factor is an attempt to obtain:
    //  new CutOff at beginning + rest of Curve + new CutOff at end = curve length before cutting,
    //  with: new CutOff at beginning = rest of Curve = new CutOff at end, approx.
    // 'CalcTransition:14' Length_Threshold=3*CutOff;
    Length_Threshold = 3.0 * CutOff_tmp;
    // 'CalcTransition:16' line1 = CurvStruct1.gcode_source_line;
    // 'CalcTransition:17' line2 = CurvStruct2.gcode_source_line;
    // 'CalcTransition:19' if IsEnabledDebugLog(DebugCfg.Global)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    u = static_cast<unsigned long>(DebugConfig) & 8UL;
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'CalcTransition:20' PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct1);
        // 'CalcTransition:21' PrintCurvStruct(ctx, CurvStruct2);
        PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct2);
    }
    // 'CalcTransition:24' CurvStruct_T = CurvStruct1;
    *CurvStruct_T = *CurvStruct1;
    // default value
    // 'CalcTransition:26' [r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0);
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct1, r0D0_1, r0D1_1);
    // 'CalcTransition:27' [r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1);
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
    // 'CalcTransition:28' [r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct2, r1D0_1, r1D1_1);
    // 'CalcTransition:29' [r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1);
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);
    //  colinearity test
    // 'CalcTransition:32' if CurvStruct1.Type~=CurveType.Helix && CurvStruct2.Type~=CurveType.Helix
    // && ... 'CalcTransition:33'         collinear(r0D1_2, r1D1_1, ColTolCos)
    guard1 = false;
    if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix)) {
        double absxk;
        double scale;
        double t;
        double y;
        bool value;
        // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
        scale = 3.3121686421112381E-170;
        absxk = std::abs(r0D1_2[0]);
        if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
        }
        absxk = std::abs(r0D1_2[1]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        absxk = std::abs(r0D1_2[2]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        y = scale * std::sqrt(y);
        if (y < 2.2204460492503131E-16) {
            // 'collinear:3' value = true;
            value = true;
        } else {
            double b_absxk;
            double b_scale;
            double b_t;
            double b_y;
            b_scale = 3.3121686421112381E-170;
            b_absxk = std::abs(r1D1_1[0]);
            if (b_absxk > 3.3121686421112381E-170) {
                b_y = 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / 3.3121686421112381E-170;
                b_y = b_t * b_t;
            }
            b_absxk = std::abs(r1D1_1[1]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }
            b_absxk = std::abs(r1D1_1[2]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }
            b_y = b_scale * std::sqrt(b_y);
            if (b_y < 2.2204460492503131E-16) {
                // 'collinear:3' value = true;
                value = true;
            } else {
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
                // 'collinear:7' value = cos_angle > tol_cos;
                value = (((r0D1_2[0] * r1D1_1[0] + r0D1_2[1] * r1D1_1[1]) + r0D1_2[2] * r1D1_1[2]) /
                             (std::sqrt((std::pow(r0D1_2[0], 2.0) + std::pow(r0D1_2[1], 2.0)) +
                                        std::pow(r0D1_2[2], 2.0)) *
                              std::sqrt((std::pow(r1D1_1[0], 2.0) + std::pow(r1D1_1[1], 2.0)) +
                                        std::pow(r1D1_1[2], 2.0))) >
                         ctx->cfg.ColTolCos);
            }
        }
        if (value) {
            // 'CalcTransition:35' status = TransitionResult.Collinear;
            b_status = TransitionResult_Collinear;
            // 'CalcTransition:36' CurvStruct1_C = CurvStruct1;
            *CurvStruct1_C = *CurvStruct1;
            // 'CalcTransition:37' CurvStruct2_C = CurvStruct2;
            *CurvStruct2_C = *CurvStruct2;
        } else {
            guard1 = true;
        }
    } else {
        guard1 = true;
    }
    if (guard1) {
        double L1;
        double L2;
        // 'CalcTransition:43' L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
        L1 = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct1);
        // 'CalcTransition:44' L2 = LengthCurv(ctx, CurvStruct2, 0, 1);
        L2 = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct2);
        //  CutOff calculation
        // 'CalcTransition:47' if CurvStruct1.Type ~= CurveType.Spline && CurvStruct2.Type ~=
        // CurveType.Spline
        if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline)) {
            // 'CalcTransition:48' if L1 < Length_Threshold || L2 < Length_Threshold
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                // 'CalcTransition:49' CutOff = min (L1,L2)/3;
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double c_y;
            double x;
            unsigned int k;
            // 'CalcTransition:51' else
            // 'CalcTransition:52' if CurvStruct1.Type == CurveType.Spline
            if (CurvStruct1->Type == CurveType_Spline) {
                double u1_tilda;
                // 'CalcTransition:53' Spline=ctx.q_splines.get(CurvStruct1.sp_index);
                ctx->q_splines.get(CurvStruct1->sp_index, &expl_temp);
                // 'CalcTransition:54' sp = Spline.sp;
                // 'CalcTransition:55' a = CurvStruct1.a_param;
                // 'CalcTransition:56' b = CurvStruct1.b_param;
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                // 'CalcTransition:64' u1_tilda = a*1+b;
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                // 'CalcTransition:68' k = length(sp.knots);
                // 'CalcTransition:69' while sp.knots(k) >= u1_tilda
                for (k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(k) - 1] >= u1_tilda;
                     k = static_cast<unsigned int>(static_cast<int>(k) - 1)) {
                    // 'CalcTransition:70' k = k - 1;
                }
                // 'CalcTransition:72' u0_tilda = sp.knots(k);
                // 'CalcTransition:73' l1  = SplineLengthApproxGL_bounds(ctx, CurvStruct1, u0_tilda,
                // u1_tilda)/2;
                x = SplineLengthApproxGL_bounds(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                ctx->cfg.GaussLegendreW, CurvStruct1->sp_index,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1],
                                                u1_tilda) /
                    2.0;

                // 'CalcTransition:74' else
                // 'CalcTransition:75' if L1<Length_Threshold
            } else if (L1 < Length_Threshold) {
                // 'CalcTransition:76' l1 = L1/3;
                x = L1 / 3.0;
            } else {
                // 'CalcTransition:77' else
                // 'CalcTransition:78' l1 = CutOff;
                x = CutOff_tmp;
            }
            // 'CalcTransition:82' if CurvStruct2.Type == CurveType.Spline
            if (CurvStruct2->Type == CurveType_Spline) {
                int loop_ub;
                // 'CalcTransition:83' Spline=ctx.q_splines.get(CurvStruct2.sp_index);
                ctx->q_splines.get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i{0}; i < loop_ub; i++) {
                    expl_temp.sp.knots[i] = b_expl_temp.sp.knots[i];
                }
                // 'CalcTransition:84' sp = Spline.sp;
                // 'CalcTransition:85' a = CurvStruct2.a_param;
                // 'CalcTransition:86' b = CurvStruct2.b_param;
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                // 'CalcTransition:94' u0_tilda = a*0+b;
                //  We need to find the next spline knot u1_tilda...
                //
                // 'CalcTransition:98' k = 1;
                // 'CalcTransition:99' while sp.knots(k) <= u0_tilda
                for (k = 1U; expl_temp.sp.knots[static_cast<int>(k) - 1] <= CurvStruct2->b_param;
                     k++) {
                    // 'CalcTransition:100' k = k + 1;
                }
                // 'CalcTransition:102' u1_tilda = sp.knots(k);
                // 'CalcTransition:103' l2 = SplineLengthApproxGL_bounds(ctx, CurvStruct2, u0_tilda,
                // u1_tilda)/2;
                c_y = SplineLengthApproxGL_bounds(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                  ctx->cfg.GaussLegendreW, CurvStruct2->sp_index,
                                                  CurvStruct2->b_param,
                                                  expl_temp.sp.knots[static_cast<int>(k) - 1]) /
                      2.0;

                // 'CalcTransition:104' else
                // 'CalcTransition:105' if L2<Length_Threshold
            } else if (L2 < Length_Threshold) {
                // 'CalcTransition:106' l2 = L2/3;
                c_y = L2 / 3.0;
            } else {
                // 'CalcTransition:107' else
                // 'CalcTransition:108' l2 = CutOff;
                c_y = ctx->cfg.CutOff;
            }
            // 'CalcTransition:112' CutOff = min (l1,l2);
            CutOff = std::fmin(x, c_y);
        }
        // 'CalcTransition:116' status = TransitionResult.Ok;
        // 'CalcTransition:118' CurvStruct1_C = CutCurvStruct(ctx, CurvStruct1, 0, CutOff);
        *CurvStruct1_C = *CurvStruct1;
        CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                      CurvStruct1_C, CutOff);
        // 'CalcTransition:119' CurvStruct2_C = CutCurvStruct(ctx, CurvStruct2, CutOff, 0);
        *CurvStruct2_C = *CurvStruct2;
        b_CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct2_C, CutOff);
        // 'CalcTransition:121' if IsEnabledDebugLog(DebugCfg.Global)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if (u != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'CalcTransition:122' PrintCurvStruct(ctx, CurvStruct1_C)
            PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                            CurvStruct1_C);
            // 'CalcTransition:123' PrintCurvStruct(ctx, CurvStruct2_C)
            PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                            CurvStruct2_C);
        }
        // 'CalcTransition:126' [r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
        b_EvalCurvStruct(&ctx->q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0, CurvStruct1_C->P1,
                         CurvStruct1_C->CorrectedHelixCenter, CurvStruct1_C->evec,
                         CurvStruct1_C->theta, CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5,
                         CurvStruct1_C->sp_index, CurvStruct1_C->a_param, CurvStruct1_C->b_param,
                         r0D0, r0D1, r0D2);
        // 'CalcTransition:127' [r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);
        c_EvalCurvStruct(&ctx->q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0, CurvStruct2_C->P1,
                         CurvStruct2_C->CorrectedHelixCenter, CurvStruct2_C->evec,
                         CurvStruct2_C->theta, CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5,
                         CurvStruct2_C->sp_index, CurvStruct2_C->a_param, CurvStruct2_C->b_param,
                         r1D0, r1D1, r1D2);
        //  G2 transition calculation
        // 'CalcTransition:130' [p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0,
        // r1D1, r1D2);
        G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &a__1, &a__2);
        // 'CalcTransition:132' if ret==1
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'CalcTransition:136' CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
            // 'CalcTransition:137'                    CurvStruct1.HSC, ...
            // 'CalcTransition:138'                    CurvStruct1.Poff, CurvStruct1.Aoff, ...
            // 'CalcTransition:139'                    CurvStruct1.Uoff, CurvStruct1.Doff,...
            // 'CalcTransition:140'                    [CurvStruct1.A0, CurvStruct1.A1], ...
            // 'CalcTransition:141'                    [CurvStruct1.U0, CurvStruct1.U1], ...
            // 'CalcTransition:142'                    p5, CurvStruct1.FeedRate);
            b_CurvStruct1[0][0] = CurvStruct1->A0[0];
            b_CurvStruct1[1][0] = CurvStruct1->A1[0];
            c_CurvStruct1[0][0] = CurvStruct1->U0[0];
            c_CurvStruct1[1][0] = CurvStruct1->U1[0];
            b_CurvStruct1[0][1] = CurvStruct1->A0[1];
            b_CurvStruct1[1][1] = CurvStruct1->A1[1];
            c_CurvStruct1[0][1] = CurvStruct1->U0[1];
            c_CurvStruct1[1][1] = CurvStruct1->U1[1];
            b_CurvStruct1[0][2] = CurvStruct1->A0[2];
            b_CurvStruct1[1][2] = CurvStruct1->A1[2];
            c_CurvStruct1[0][2] = CurvStruct1->U0[2];
            c_CurvStruct1[1][2] = CurvStruct1->U1[2];
            ConstrTransP5Struct(CurvStruct1->TRAFO, CurvStruct1->HSC, CurvStruct1->Poff,
                                CurvStruct1->Aoff, CurvStruct1->Uoff, CurvStruct1->Doff,
                                b_CurvStruct1, c_CurvStruct1, p5, CurvStruct1->FeedRate,
                                CurvStruct_T);
            // 'CalcTransition:143' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            unsigned long u2;
            // 'CalcTransition:145' elseif ret==2
            //  badly conditioned matrix in G2_Hermite()
            // 'CalcTransition:148' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'CalcTransition:150' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u2 = static_cast<unsigned long>(DebugConfig) & 32UL;
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:151' DebugLog(DebugCfg.Error, '=========== Badly Cond. Matrix in
            // G2_Hermite() ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== Badly Cond. Matrix in G2_Hermite() ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:152' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:154' if coder.target('matlab')
        } else if (ret == 6) {
            unsigned long u3;
            // 'CalcTransition:179' elseif ret==6
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'CalcTransition:183' CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
            // 'CalcTransition:184'                    CurvStruct1.HSC, ...
            // 'CalcTransition:185'                    CurvStruct1.Poff, CurvStruct1.Aoff, ...
            // 'CalcTransition:186'                    CurvStruct1.Uoff, CurvStruct1.Doff,...
            // 'CalcTransition:187'                    [CurvStruct1.A0, CurvStruct1.A1], ...
            // 'CalcTransition:188'                    [CurvStruct1.U0, CurvStruct1.U1], ...
            // 'CalcTransition:189'                    p5, CurvStruct1.FeedRate);
            b_CurvStruct1[0][0] = CurvStruct1->A0[0];
            b_CurvStruct1[1][0] = CurvStruct1->A1[0];
            c_CurvStruct1[0][0] = CurvStruct1->U0[0];
            c_CurvStruct1[1][0] = CurvStruct1->U1[0];
            b_CurvStruct1[0][1] = CurvStruct1->A0[1];
            b_CurvStruct1[1][1] = CurvStruct1->A1[1];
            c_CurvStruct1[0][1] = CurvStruct1->U0[1];
            c_CurvStruct1[1][1] = CurvStruct1->U1[1];
            b_CurvStruct1[0][2] = CurvStruct1->A0[2];
            b_CurvStruct1[1][2] = CurvStruct1->A1[2];
            c_CurvStruct1[0][2] = CurvStruct1->U0[2];
            c_CurvStruct1[1][2] = CurvStruct1->U1[2];
            ConstrTransP5Struct(CurvStruct1->TRAFO, CurvStruct1->HSC, CurvStruct1->Poff,
                                CurvStruct1->Aoff, CurvStruct1->Uoff, CurvStruct1->Doff,
                                b_CurvStruct1, c_CurvStruct1, p5, CurvStruct1->FeedRate,
                                CurvStruct_T);
            // 'CalcTransition:190' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
            // 'CalcTransition:192' DebugLog(DebugCfg.Warning, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u3 = static_cast<unsigned long>(DebugConfig) & 16UL;
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:193' DebugLog(DebugCfg.Warning, '=========== status = 6
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== status = 6 ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:194' DebugLog(DebugCfg.Warning, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:196' if coder.target('matlab')
        } else {
            unsigned long u1;
            // 'CalcTransition:213' else
            // 'CalcTransition:215' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'CalcTransition:217' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u1 = static_cast<unsigned long>(DebugConfig) & 32UL;
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:218' DebugLog(DebugCfg.Error, '=========== No Solution
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== No Solution ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:219' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:221' if coder.target('matlab')
        }
        // 'CalcTransition:247' CurvStruct_T.gcode_source_line = line2;
        CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
        // 'CalcTransition:248' CurvStruct_T.SpindleSpeed = min(CurvStruct1.SpindleSpeed,
        // CurvStruct2.SpindleSpeed);
        CurvStruct_T->SpindleSpeed =
            std::fmin(CurvStruct1->SpindleSpeed, CurvStruct2->SpindleSpeed);
    }
    *status = b_status;
}

//
// function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ...
//     CalcTransition(ctx, CurvStruct1, CurvStruct2)
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_CutOff
//                double ctx_cfg_ColTolCos
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *CurvStruct1
//                const CurvStruct *CurvStruct2
//                CurvStruct *CurvStruct1_C
//                CurvStruct *CurvStruct_T
//                CurvStruct *CurvStruct2_C
//                TransitionResult *status
// Return Type  : void
//
void b_CalcTransition(const queue_coder *ctx_q_splines, double ctx_cfg_CutOff,
                      double ctx_cfg_ColTolCos, const double ctx_cfg_GaussLegendreX[5],
                      const double ctx_cfg_GaussLegendreW[5], const CurvStruct *CurvStruct1,
                      const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                      CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C, TransitionResult *status)
{
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    double p5[6][3];
    double b_CurvStruct1[2][3];
    double c_CurvStruct1[2][3];
    double r0D0[3];
    double r0D0_1[3];
    double r0D0_2[3];
    double r0D1[3];
    double r0D1_1[3];
    double r0D1_2[3];
    double r0D2[3];
    double r1D0[3];
    double r1D0_1[3];
    double r1D0_2[3];
    double r1D1[3];
    double r1D1_1[3];
    double r1D1_2[3];
    double r1D2[3];
    double CutOff;
    double Length_Threshold;
    double a__1;
    double a__2;
    unsigned long u;
    int ret;
    bool guard1{false};
    TransitionResult b_status;
    // 'CalcTransition:4' coder.inline("never");
    // 'CalcTransition:6' CutOff=ctx.cfg.CutOff;
    CutOff = ctx_cfg_CutOff;
    // 'CalcTransition:7' ColTolCos=ctx.cfg.ColTolCos;
    //  If the 1st or the 2nd Curve lenth is shorter than 3*CutOff,
    //  we will recalculate Cutoff. This new value will be smaller than before.
    //  The 3 factor is an attempt to obtain:
    //  new CutOff at beginning + rest of Curve + new CutOff at end = curve length before cutting,
    //  with: new CutOff at beginning = rest of Curve = new CutOff at end, approx.
    // 'CalcTransition:14' Length_Threshold=3*CutOff;
    Length_Threshold = 3.0 * ctx_cfg_CutOff;
    // 'CalcTransition:16' line1 = CurvStruct1.gcode_source_line;
    // 'CalcTransition:17' line2 = CurvStruct2.gcode_source_line;
    // 'CalcTransition:19' if IsEnabledDebugLog(DebugCfg.Global)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    u = static_cast<unsigned long>(DebugConfig) & 8UL;
    if (u != 0UL) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'CalcTransition:20' PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1);
        // 'CalcTransition:21' PrintCurvStruct(ctx, CurvStruct2);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2);
    }
    // 'CalcTransition:24' CurvStruct_T = CurvStruct1;
    *CurvStruct_T = *CurvStruct1;
    // default value
    // 'CalcTransition:26' [r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct1, r0D0_1, r0D1_1);
    // 'CalcTransition:27' [r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
    // 'CalcTransition:28' [r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct2, r1D0_1, r1D1_1);
    // 'CalcTransition:29' [r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);
    //  colinearity test
    // 'CalcTransition:32' if CurvStruct1.Type~=CurveType.Helix && CurvStruct2.Type~=CurveType.Helix
    // && ... 'CalcTransition:33'         collinear(r0D1_2, r1D1_1, ColTolCos)
    guard1 = false;
    if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix)) {
        double absxk;
        double scale;
        double t;
        double y;
        bool value;
        // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
        scale = 3.3121686421112381E-170;
        absxk = std::abs(r0D1_2[0]);
        if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
        }
        absxk = std::abs(r0D1_2[1]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        absxk = std::abs(r0D1_2[2]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }
        y = scale * std::sqrt(y);
        if (y < 2.2204460492503131E-16) {
            // 'collinear:3' value = true;
            value = true;
        } else {
            double b_absxk;
            double b_scale;
            double b_t;
            double b_y;
            b_scale = 3.3121686421112381E-170;
            b_absxk = std::abs(r1D1_1[0]);
            if (b_absxk > 3.3121686421112381E-170) {
                b_y = 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / 3.3121686421112381E-170;
                b_y = b_t * b_t;
            }
            b_absxk = std::abs(r1D1_1[1]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }
            b_absxk = std::abs(r1D1_1[2]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }
            b_y = b_scale * std::sqrt(b_y);
            if (b_y < 2.2204460492503131E-16) {
                // 'collinear:3' value = true;
                value = true;
            } else {
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
                // 'collinear:7' value = cos_angle > tol_cos;
                value = (((r0D1_2[0] * r1D1_1[0] + r0D1_2[1] * r1D1_1[1]) + r0D1_2[2] * r1D1_1[2]) /
                             (std::sqrt((std::pow(r0D1_2[0], 2.0) + std::pow(r0D1_2[1], 2.0)) +
                                        std::pow(r0D1_2[2], 2.0)) *
                              std::sqrt((std::pow(r1D1_1[0], 2.0) + std::pow(r1D1_1[1], 2.0)) +
                                        std::pow(r1D1_1[2], 2.0))) >
                         ctx_cfg_ColTolCos);
            }
        }
        if (value) {
            // 'CalcTransition:35' status = TransitionResult.Collinear;
            b_status = TransitionResult_Collinear;
            // 'CalcTransition:36' CurvStruct1_C = CurvStruct1;
            *CurvStruct1_C = *CurvStruct1;
            // 'CalcTransition:37' CurvStruct2_C = CurvStruct2;
            *CurvStruct2_C = *CurvStruct2;
        } else {
            guard1 = true;
        }
    } else {
        guard1 = true;
    }
    if (guard1) {
        double L1;
        double L2;
        // 'CalcTransition:43' L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
        L1 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1);
        // 'CalcTransition:44' L2 = LengthCurv(ctx, CurvStruct2, 0, 1);
        L2 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2);
        //  CutOff calculation
        // 'CalcTransition:47' if CurvStruct1.Type ~= CurveType.Spline && CurvStruct2.Type ~=
        // CurveType.Spline
        if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline)) {
            // 'CalcTransition:48' if L1 < Length_Threshold || L2 < Length_Threshold
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                // 'CalcTransition:49' CutOff = min (L1,L2)/3;
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double c_y;
            double x;
            unsigned int k;
            // 'CalcTransition:51' else
            // 'CalcTransition:52' if CurvStruct1.Type == CurveType.Spline
            if (CurvStruct1->Type == CurveType_Spline) {
                double u1_tilda;
                // 'CalcTransition:53' Spline=ctx.q_splines.get(CurvStruct1.sp_index);
                ctx_q_splines->get(CurvStruct1->sp_index, &expl_temp);
                // 'CalcTransition:54' sp = Spline.sp;
                // 'CalcTransition:55' a = CurvStruct1.a_param;
                // 'CalcTransition:56' b = CurvStruct1.b_param;
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                // 'CalcTransition:64' u1_tilda = a*1+b;
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                // 'CalcTransition:68' k = length(sp.knots);
                // 'CalcTransition:69' while sp.knots(k) >= u1_tilda
                for (k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(k) - 1] >= u1_tilda;
                     k = static_cast<unsigned int>(static_cast<int>(k) - 1)) {
                    // 'CalcTransition:70' k = k - 1;
                }
                // 'CalcTransition:72' u0_tilda = sp.knots(k);
                // 'CalcTransition:73' l1  = SplineLengthApproxGL_bounds(ctx, CurvStruct1, u0_tilda,
                // u1_tilda)/2;
                x = SplineLengthApproxGL_bounds(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, CurvStruct1->sp_index,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1],
                                                u1_tilda) /
                    2.0;

                // 'CalcTransition:74' else
                // 'CalcTransition:75' if L1<Length_Threshold
            } else if (L1 < Length_Threshold) {
                // 'CalcTransition:76' l1 = L1/3;
                x = L1 / 3.0;
            } else {
                // 'CalcTransition:77' else
                // 'CalcTransition:78' l1 = CutOff;
                x = ctx_cfg_CutOff;
            }
            // 'CalcTransition:82' if CurvStruct2.Type == CurveType.Spline
            if (CurvStruct2->Type == CurveType_Spline) {
                int loop_ub;
                // 'CalcTransition:83' Spline=ctx.q_splines.get(CurvStruct2.sp_index);
                ctx_q_splines->get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i{0}; i < loop_ub; i++) {
                    expl_temp.sp.knots[i] = b_expl_temp.sp.knots[i];
                }
                // 'CalcTransition:84' sp = Spline.sp;
                // 'CalcTransition:85' a = CurvStruct2.a_param;
                // 'CalcTransition:86' b = CurvStruct2.b_param;
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                // 'CalcTransition:94' u0_tilda = a*0+b;
                //  We need to find the next spline knot u1_tilda...
                //
                // 'CalcTransition:98' k = 1;
                // 'CalcTransition:99' while sp.knots(k) <= u0_tilda
                for (k = 1U; expl_temp.sp.knots[static_cast<int>(k) - 1] <= CurvStruct2->b_param;
                     k++) {
                    // 'CalcTransition:100' k = k + 1;
                }
                // 'CalcTransition:102' u1_tilda = sp.knots(k);
                // 'CalcTransition:103' l2 = SplineLengthApproxGL_bounds(ctx, CurvStruct2, u0_tilda,
                // u1_tilda)/2;
                c_y = SplineLengthApproxGL_bounds(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                                  ctx_cfg_GaussLegendreW, CurvStruct2->sp_index,
                                                  CurvStruct2->b_param,
                                                  expl_temp.sp.knots[static_cast<int>(k) - 1]) /
                      2.0;

                // 'CalcTransition:104' else
                // 'CalcTransition:105' if L2<Length_Threshold
            } else if (L2 < Length_Threshold) {
                // 'CalcTransition:106' l2 = L2/3;
                c_y = L2 / 3.0;
            } else {
                // 'CalcTransition:107' else
                // 'CalcTransition:108' l2 = CutOff;
                c_y = ctx_cfg_CutOff;
            }
            // 'CalcTransition:112' CutOff = min (l1,l2);
            CutOff = std::fmin(x, c_y);
        }
        // 'CalcTransition:116' status = TransitionResult.Ok;
        // 'CalcTransition:118' CurvStruct1_C = CutCurvStruct(ctx, CurvStruct1, 0, CutOff);
        *CurvStruct1_C = *CurvStruct1;
        CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1_C,
                      CutOff);
        // 'CalcTransition:119' CurvStruct2_C = CutCurvStruct(ctx, CurvStruct2, CutOff, 0);
        *CurvStruct2_C = *CurvStruct2;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct2_C, CutOff);
        // 'CalcTransition:121' if IsEnabledDebugLog(DebugCfg.Global)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if (u != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'CalcTransition:122' PrintCurvStruct(ctx, CurvStruct1_C)
            PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                            CurvStruct1_C);
            // 'CalcTransition:123' PrintCurvStruct(ctx, CurvStruct2_C)
            PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                            CurvStruct2_C);
        }
        // 'CalcTransition:126' [r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
        b_EvalCurvStruct(ctx_q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0, CurvStruct1_C->P1,
                         CurvStruct1_C->CorrectedHelixCenter, CurvStruct1_C->evec,
                         CurvStruct1_C->theta, CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5,
                         CurvStruct1_C->sp_index, CurvStruct1_C->a_param, CurvStruct1_C->b_param,
                         r0D0, r0D1, r0D2);
        // 'CalcTransition:127' [r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);
        c_EvalCurvStruct(ctx_q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0, CurvStruct2_C->P1,
                         CurvStruct2_C->CorrectedHelixCenter, CurvStruct2_C->evec,
                         CurvStruct2_C->theta, CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5,
                         CurvStruct2_C->sp_index, CurvStruct2_C->a_param, CurvStruct2_C->b_param,
                         r1D0, r1D1, r1D2);
        //  G2 transition calculation
        // 'CalcTransition:130' [p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0,
        // r1D1, r1D2);
        G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &a__1, &a__2);
        // 'CalcTransition:132' if ret==1
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'CalcTransition:136' CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
            // 'CalcTransition:137'                    CurvStruct1.HSC, ...
            // 'CalcTransition:138'                    CurvStruct1.Poff, CurvStruct1.Aoff, ...
            // 'CalcTransition:139'                    CurvStruct1.Uoff, CurvStruct1.Doff,...
            // 'CalcTransition:140'                    [CurvStruct1.A0, CurvStruct1.A1], ...
            // 'CalcTransition:141'                    [CurvStruct1.U0, CurvStruct1.U1], ...
            // 'CalcTransition:142'                    p5, CurvStruct1.FeedRate);
            b_CurvStruct1[0][0] = CurvStruct1->A0[0];
            b_CurvStruct1[1][0] = CurvStruct1->A1[0];
            c_CurvStruct1[0][0] = CurvStruct1->U0[0];
            c_CurvStruct1[1][0] = CurvStruct1->U1[0];
            b_CurvStruct1[0][1] = CurvStruct1->A0[1];
            b_CurvStruct1[1][1] = CurvStruct1->A1[1];
            c_CurvStruct1[0][1] = CurvStruct1->U0[1];
            c_CurvStruct1[1][1] = CurvStruct1->U1[1];
            b_CurvStruct1[0][2] = CurvStruct1->A0[2];
            b_CurvStruct1[1][2] = CurvStruct1->A1[2];
            c_CurvStruct1[0][2] = CurvStruct1->U0[2];
            c_CurvStruct1[1][2] = CurvStruct1->U1[2];
            ConstrTransP5Struct(CurvStruct1->TRAFO, CurvStruct1->HSC, CurvStruct1->Poff,
                                CurvStruct1->Aoff, CurvStruct1->Uoff, CurvStruct1->Doff,
                                b_CurvStruct1, c_CurvStruct1, p5, CurvStruct1->FeedRate,
                                CurvStruct_T);
            // 'CalcTransition:143' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            unsigned long u2;
            // 'CalcTransition:145' elseif ret==2
            //  badly conditioned matrix in G2_Hermite()
            // 'CalcTransition:148' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'CalcTransition:150' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u2 = static_cast<unsigned long>(DebugConfig) & 32UL;
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:151' DebugLog(DebugCfg.Error, '=========== Badly Cond. Matrix in
            // G2_Hermite() ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== Badly Cond. Matrix in G2_Hermite() ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:152' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u2 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:154' if coder.target('matlab')
        } else if (ret == 6) {
            unsigned long u3;
            // 'CalcTransition:179' elseif ret==6
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'CalcTransition:183' CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
            // 'CalcTransition:184'                    CurvStruct1.HSC, ...
            // 'CalcTransition:185'                    CurvStruct1.Poff, CurvStruct1.Aoff, ...
            // 'CalcTransition:186'                    CurvStruct1.Uoff, CurvStruct1.Doff,...
            // 'CalcTransition:187'                    [CurvStruct1.A0, CurvStruct1.A1], ...
            // 'CalcTransition:188'                    [CurvStruct1.U0, CurvStruct1.U1], ...
            // 'CalcTransition:189'                    p5, CurvStruct1.FeedRate);
            b_CurvStruct1[0][0] = CurvStruct1->A0[0];
            b_CurvStruct1[1][0] = CurvStruct1->A1[0];
            c_CurvStruct1[0][0] = CurvStruct1->U0[0];
            c_CurvStruct1[1][0] = CurvStruct1->U1[0];
            b_CurvStruct1[0][1] = CurvStruct1->A0[1];
            b_CurvStruct1[1][1] = CurvStruct1->A1[1];
            c_CurvStruct1[0][1] = CurvStruct1->U0[1];
            c_CurvStruct1[1][1] = CurvStruct1->U1[1];
            b_CurvStruct1[0][2] = CurvStruct1->A0[2];
            b_CurvStruct1[1][2] = CurvStruct1->A1[2];
            c_CurvStruct1[0][2] = CurvStruct1->U0[2];
            c_CurvStruct1[1][2] = CurvStruct1->U1[2];
            ConstrTransP5Struct(CurvStruct1->TRAFO, CurvStruct1->HSC, CurvStruct1->Poff,
                                CurvStruct1->Aoff, CurvStruct1->Uoff, CurvStruct1->Doff,
                                b_CurvStruct1, c_CurvStruct1, p5, CurvStruct1->FeedRate,
                                CurvStruct_T);
            // 'CalcTransition:190' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
            // 'CalcTransition:192' DebugLog(DebugCfg.Warning, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u3 = static_cast<unsigned long>(DebugConfig) & 16UL;
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:193' DebugLog(DebugCfg.Warning, '=========== status = 6
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== status = 6 ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:194' DebugLog(DebugCfg.Warning, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u3 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:196' if coder.target('matlab')
        } else {
            unsigned long u1;
            // 'CalcTransition:213' else
            // 'CalcTransition:215' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'CalcTransition:217' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            u1 = static_cast<unsigned long>(DebugConfig) & 32UL;
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:218' DebugLog(DebugCfg.Error, '=========== No Solution
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== No Solution ==========\n");
                fflush(stdout);
            }
            // 'CalcTransition:219' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            if (u1 != 0UL) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                       CurvStruct2->gcode_source_line);
                fflush(stdout);
            }
            // 'CalcTransition:221' if coder.target('matlab')
        }
        // 'CalcTransition:247' CurvStruct_T.gcode_source_line = line2;
        CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
        // 'CalcTransition:248' CurvStruct_T.SpindleSpeed = min(CurvStruct1.SpindleSpeed,
        // CurvStruct2.SpindleSpeed);
        CurvStruct_T->SpindleSpeed =
            std::fmin(CurvStruct1->SpindleSpeed, CurvStruct2->SpindleSpeed);
    }
    *status = b_status;
}

} // namespace ocn

//
// File trailer for CalcTransition.cpp
//
// [EOF]
//
