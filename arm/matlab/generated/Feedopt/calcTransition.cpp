//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "calcTransition.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation.h"
#include "LengthCurv.h"
#include "PrintCurvStruct.h"
#include "SplineLengthApproxGL_bounds.h"
#include "combineVectorElements.h"
#include "constrTransP5Struct.h"
#include "cutCurvStructU.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types31.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ...
//     calcTransition(ctx, CurvStruct1, CurvStruct2)
//
// CalcTransition : Compute a transition curve using on a polynome of degree
//  5.
//
//  ctx           : The context
//  CurvStruct1   : Current structure of the curve
//  CurvStruct2   : Next structure of the curve
//
//  CurvStruct1_C : New calculated curve structure (replace CurvStruct1)
//  CurvStruct_T  : New calculated transition curve
//  CurvStruct2_C : New calculated curve structure (replace CurvStruct2)
//  status        : Status of the compuation see TransitionResult
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                double ctx_cfg_CutOff
//                double ctx_cfg_ColTolCosSmooth
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
namespace ocn {
void calcTransition(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                    int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                    const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                    const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size, double ctx_cfg_CutOff,
                    double ctx_cfg_ColTolCosSmooth, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *CurvStruct1,
                    const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                    CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C, TransitionResult *status)
{
    static const uint64m_T r12{
        {32U, 0U} // chunks
    };
    static const uint64m_T r17{
        {16U, 0U} // chunks
    };
    static const uint64m_T r2{
        {8U, 0U} // chunks
    };
    static const uint64m_T r4{
        {0U, 0U} // chunks
    };
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D0_1;
    ::coder::array<double, 1U> r0D0_2;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D1_1;
    ::coder::array<double, 1U> r0D1_2;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D0_1;
    ::coder::array<double, 1U> r1D0_2;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D1_1;
    ::coder::array<double, 1U> r1D1_2;
    ::coder::array<double, 1U> r1D2;
    ::coder::array<double, 1U> r5;
    ::coder::array<double, 1U> r6;
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    uint64m_T r;
    uint64m_T r1;
    uint64m_T r10;
    uint64m_T r14;
    uint64m_T r15;
    uint64m_T r18;
    uint64m_T r19;
    uint64m_T r20;
    uint64m_T r23;
    uint64m_T r25;
    uint64m_T r26;
    uint64m_T r27;
    uint64m_T r3;
    uint64m_T r7;
    uint64m_T r9;
    double p5[6][3];
    double CutOff;
    double Length_Threshold;
    double a__1;
    double a__2;
    int ret;
    bool guard1{false};
    TransitionResult b_status;
    // 'calcTransition:15' coder.inline("never");
    // 'calcTransition:17' CutOff              = ctx.cfg.CutOff;
    CutOff = ctx_cfg_CutOff;
    //  Length removed
    // 'calcTransition:18' ColTolCos           = ctx.cfg.ColTolCosSmooth;
    //  Tol for colinear
    //  If the 1st or the 2nd Curve lenth is shorter than 3*CutOff,
    //  we will recalculate Cutoff. This new value will be smaller than before.
    //  The 3 factor is an attempt to obtain:
    //  new CutOff at beginning + rest of Curve + new CutOff at end = curve length before cutting,
    //  with: new CutOff at beginning = rest of Curve = new CutOff at end, approx.
    // 'calcTransition:25' Length_Threshold    = 3*CutOff;
    Length_Threshold = 3.0 * ctx_cfg_CutOff;
    //
    // 'calcTransition:27' line1 = CurvStruct1.Info.gcode_source_line;
    // 'calcTransition:28' line2 = CurvStruct2.Info.gcode_source_line;
    // 'calcTransition:30' if IsEnabledDebugLog(DebugCfg.Global)
    // 'IsEnabledDebugLog:4' value = false;
    // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    r1 = r2;
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r2.chunks[0U],
                 (unsigned int *)&r3.chunks[0U]);
    if (uMultiWordNe((unsigned int *)&r3.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
        // 'IsEnabledDebugLog:7' value = true;
        // 'calcTransition:31' PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                        ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                        ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                        ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1->Info.Type,
                        CurvStruct1->Info.zspdmode, CurvStruct1->Info.FeedRate, CurvStruct1->R0,
                        CurvStruct1->R1, CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec,
                        CurvStruct1->theta, CurvStruct1->pitch, CurvStruct1->CoeffP5,
                        CurvStruct1->sp_index, CurvStruct1->UseConstJerk, CurvStruct1->ConstJerk,
                        CurvStruct1->a_param, CurvStruct1->b_param);
        // 'calcTransition:32' PrintCurvStruct(ctx, CurvStruct2);
        PrintCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                        ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                        ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                        ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2->Info.Type,
                        CurvStruct2->Info.zspdmode, CurvStruct2->Info.FeedRate, CurvStruct2->R0,
                        CurvStruct2->R1, CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec,
                        CurvStruct2->theta, CurvStruct2->pitch, CurvStruct2->CoeffP5,
                        CurvStruct2->sp_index, CurvStruct2->UseConstJerk, CurvStruct2->ConstJerk,
                        CurvStruct2->a_param, CurvStruct2->b_param);
    }
    // 'calcTransition:35' CurvStruct_T = CurvStruct1;
    *CurvStruct_T = *CurvStruct1;
    //  default value
    // 'calcTransition:36' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
    CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
    //  only value possible for a transition
    // 'calcTransition:38' [r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0);
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                     CurvStruct1->Info.Type, CurvStruct1->R0, CurvStruct1->R1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_1, r0D1_1);
    //  Curv1 @0
    // 'calcTransition:39' [r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1);
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                     CurvStruct1->Info.Type, CurvStruct1->R0, CurvStruct1->R1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
    //  Curv1 @1
    // 'calcTransition:40' [r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                     CurvStruct2->Info.Type, CurvStruct2->R0, CurvStruct2->R1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_1, r1D1_1);
    //  Curv2 @0
    // 'calcTransition:41' [r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1);
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                     CurvStruct2->Info.Type, CurvStruct2->R0, CurvStruct2->R1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);
    //  Curv2 @1
    //  colinearity test
    // 'calcTransition:44' if  CurvStruct1.Info.Type ~= CurveType.Helix ...
    // 'calcTransition:45'     && CurvStruct2.Info.Type ~= CurveType.Helix ...
    // 'calcTransition:46'     && collinear(r0D1_2, r1D1_1, ColTolCos)
    guard1 = false;
    if ((CurvStruct1->Info.Type != CurveType_Helix) &&
        (CurvStruct2->Info.Type != CurveType_Helix)) {
        bool value;
        // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
        if ((coder::b_norm(r0D1_2) < 2.2204460492503131E-16) ||
            (coder::b_norm(r1D1_1) < 2.2204460492503131E-16)) {
            // 'collinear:3' value = true;
            value = true;
        } else {
            double c;
            int b_loop_ub;
            int loop_ub;
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
            c = 0.0;
            if (r0D1_2.size(0) >= 1) {
                int ixlast;
                ixlast = r0D1_2.size(0);
                for (int k{0}; k < ixlast; k++) {
                    c += r0D1_2[k] * r1D1_1[k];
                }
            }
            r5.set_size(r0D1_2.size(0));
            loop_ub = r0D1_2.size(0);
            for (int i{0}; i < loop_ub; i++) {
                double varargin_1;
                varargin_1 = r0D1_2[i];
                r5[i] = std::pow(varargin_1, 2.0);
            }
            r6.set_size(r1D1_1.size(0));
            b_loop_ub = r1D1_1.size(0);
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                double b_varargin_1;
                b_varargin_1 = r1D1_1[i1];
                r6[i1] = std::pow(b_varargin_1, 2.0);
            }
            value = (c / (std::sqrt(coder::combineVectorElements(r5)) *
                          std::sqrt(coder::combineVectorElements(r6))) >
                     ctx_cfg_ColTolCosSmooth);
        }
        if (value) {
            // 'calcTransition:48' status = TransitionResult.Collinear;
            b_status = TransitionResult_Collinear;
            // 'calcTransition:49' CurvStruct1_C = CurvStruct1;
            *CurvStruct1_C = *CurvStruct1;
            // 'calcTransition:50' CurvStruct2_C = CurvStruct2;
            *CurvStruct2_C = *CurvStruct2;
        } else {
            guard1 = true;
        }
    } else {
        guard1 = true;
    }
    if (guard1) {
        uint64m_T r8;
        double L1;
        double L2;
        double b_u1_tilda;
        double c_u1_tilda;
        // 'calcTransition:56' L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
        L1 = LengthCurv(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                        ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                        ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                        ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1->Info.Type,
                        CurvStruct1->R0, CurvStruct1->R1, CurvStruct1->CorrectedHelixCenter,
                        CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                        CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->a_param,
                        CurvStruct1->b_param);
        // 'calcTransition:57' L2 = LengthCurv(ctx, CurvStruct2, 0, 1);
        L2 = LengthCurv(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                        ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                        ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                        ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2->Info.Type,
                        CurvStruct2->R0, CurvStruct2->R1, CurvStruct2->CorrectedHelixCenter,
                        CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                        CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->a_param,
                        CurvStruct2->b_param);
        //  CutOff calculation
        // 'calcTransition:60' if CurvStruct1.Info.Type ~= CurveType.Spline ...
        // 'calcTransition:61'    && CurvStruct2.Info.Type ~= CurveType.Spline
        if ((CurvStruct1->Info.Type != CurveType_Spline) &&
            (CurvStruct2->Info.Type != CurveType_Spline)) {
            //  If L1 or L2 is smaller than 3*CutOff
            // 'calcTransition:63' if L1 < Length_Threshold || L2 < Length_Threshold
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                // 'calcTransition:64' CutOff = min (L1,L2)/3;
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double x;
            double y;
            unsigned int b_k;
            // 'calcTransition:66' else
            // 'calcTransition:67' if CurvStruct1.Info.Type == CurveType.Spline
            if (CurvStruct1->Info.Type == CurveType_Spline) {
                double u1_tilda;
                // 'calcTransition:68' Spline=ctx.q_spline.get(CurvStruct1.sp_index);
                ctx_q_spline->get(CurvStruct1->sp_index, &expl_temp);
                // 'calcTransition:69' sp = Spline.sp;
                // 'calcTransition:70' a = CurvStruct1.a_param;
                // 'calcTransition:71' b = CurvStruct1.b_param;
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                // 'calcTransition:79' u1_tilda = a*1+b;
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                // 'calcTransition:83' k = length(sp.knots);
                // 'calcTransition:84' while sp.knots(k) >= u1_tilda
                for (b_k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(b_k) - 1] >= u1_tilda;
                     b_k = static_cast<unsigned int>(static_cast<int>(b_k) - 1)) {
                    // 'calcTransition:85' k = k - 1;
                }
                // 'calcTransition:87' u0_tilda = sp.knots(k);
                // 'calcTransition:88' l1  = SplineLengthApproxGL_bounds(ctx, CurvStruct1, u0_tilda,
                // u1_tilda)/2;
                x = SplineLengthApproxGL_bounds(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, CurvStruct1->sp_index,
                                                expl_temp.sp.knots[static_cast<int>(b_k) - 1],
                                                u1_tilda) /
                    2.0;

                // 'calcTransition:89' else
                // 'calcTransition:90' if L1<Length_Threshold
            } else if (L1 < Length_Threshold) {
                // 'calcTransition:91' l1 = L1/3;
                x = L1 / 3.0;
            } else {
                // 'calcTransition:92' else
                // 'calcTransition:93' l1 = CutOff;
                x = ctx_cfg_CutOff;
            }
            // 'calcTransition:97' if CurvStruct2.Info.Type == CurveType.Spline
            if (CurvStruct2->Info.Type == CurveType_Spline) {
                int c_loop_ub;
                // 'calcTransition:98' Spline=ctx.q_spline.get(CurvStruct2.sp_index);
                ctx_q_spline->get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                c_loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i2{0}; i2 < c_loop_ub; i2++) {
                    expl_temp.sp.knots[i2] = b_expl_temp.sp.knots[i2];
                }
                // 'calcTransition:99' sp = Spline.sp;
                // 'calcTransition:100' a = CurvStruct2.a_param;
                // 'calcTransition:101' b = CurvStruct2.b_param;
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                // 'calcTransition:109' u0_tilda = a*0+b;
                //  We need to find the next spline knot u1_tilda...
                //
                // 'calcTransition:113' k = 1;
                // 'calcTransition:114' while sp.knots(k) <= u0_tilda
                for (b_k = 1U;
                     expl_temp.sp.knots[static_cast<int>(b_k) - 1] <= CurvStruct2->b_param; b_k++) {
                    // 'calcTransition:115' k = k + 1;
                }
                // 'calcTransition:117' u1_tilda = sp.knots(k);
                // 'calcTransition:118' l2 = SplineLengthApproxGL_bounds(ctx, CurvStruct2, u0_tilda,
                // u1_tilda)/2;
                y = SplineLengthApproxGL_bounds(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, CurvStruct2->sp_index,
                                                CurvStruct2->b_param,
                                                expl_temp.sp.knots[static_cast<int>(b_k) - 1]) /
                    2.0;

                // 'calcTransition:119' else
                // 'calcTransition:120' if L2<Length_Threshold
            } else if (L2 < Length_Threshold) {
                // 'calcTransition:121' l2 = L2/3;
                y = L2 / 3.0;
            } else {
                // 'calcTransition:122' else
                // 'calcTransition:123' l2 = CutOff;
                y = ctx_cfg_CutOff;
            }
            // 'calcTransition:127' CutOff = min (l1,l2);
            CutOff = std::fmin(x, y);
        }
        // 'calcTransition:131' status = TransitionResult.Ok;
        //  Cut the curve structures
        // 'calcTransition:134' CurvStruct1_C = cutCurvStruct( ctx, CurvStruct1, 0, CutOff, false );
        //  cutCurvStruct: Cut a piece of the structure with a size of L
        //  starting at point u0
        //  Inputs :
        //  ctx   : Context
        //  curv  : Curvature
        //  u0    : Starting point of the spline
        //  L     : Length of the segment of curv
        //  isEnd : Is a zero stop curv
        //  Outputs :
        //  u1    : The last point of the splitted curv
        // 'cutCurvStruct:13' a = curv.a_param;
        // 'cutCurvStruct:14' b = curv.b_param;
        // 'cutCurvStruct:16' u1_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );
        b_u1_tilda = cutCurvStructU(
            ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_indCart_data,
            ctx_cfg_indCart_size, ctx_cfg_indRot_data, ctx_cfg_indRot_size, ctx_cfg_indTot_data,
            ctx_cfg_indTot_size, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
            CurvStruct1->Info.Type, CurvStruct1->R0, CurvStruct1->R1,
            CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
            CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->a_param,
            CurvStruct1->b_param, CutOff);
        // 'cutCurvStruct:18' curvC = curv;
        *CurvStruct1_C = *CurvStruct1;
        // 'cutCurvStruct:20' if( isEnd )
        // 'cutCurvStruct:30' else
        // 'cutCurvStruct:31' curvC.a_param = u1_tilda - curvC.b_param;
        CurvStruct1_C->a_param = b_u1_tilda - CurvStruct1->b_param;
        // 'cutCurvStruct:32' if( isAZeroStart( curvC ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((CurvStruct1->Info.zspdmode == ZSpdMode_ZN) ||
            (CurvStruct1->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:6' zeroFlag = true;
            // 'cutCurvStruct:33' curvC.Info.zspdmode = ZSpdMode.ZN;
            CurvStruct1_C->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'isAZeroStart:8' zeroFlag = false;
            // 'cutCurvStruct:34' else
            // 'cutCurvStruct:35' curvC.Info.zspdmode = ZSpdMode.NN;
            CurvStruct1_C->Info.zspdmode = ZSpdMode_NN;
        }
        // 'calcTransition:135' CurvStruct2_C = cutCurvStruct( ctx, CurvStruct2, 1, CutOff, true  );
        //  cutCurvStruct: Cut a piece of the structure with a size of L
        //  starting at point u0
        //  Inputs :
        //  ctx   : Context
        //  curv  : Curvature
        //  u0    : Starting point of the spline
        //  L     : Length of the segment of curv
        //  isEnd : Is a zero stop curv
        //  Outputs :
        //  u1    : The last point of the splitted curv
        // 'cutCurvStruct:13' a = curv.a_param;
        // 'cutCurvStruct:14' b = curv.b_param;
        // 'cutCurvStruct:16' u1_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );
        c_u1_tilda = b_cutCurvStructU(
            ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_indCart_data,
            ctx_cfg_indCart_size, ctx_cfg_indRot_data, ctx_cfg_indRot_size, ctx_cfg_indTot_data,
            ctx_cfg_indTot_size, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
            CurvStruct2->Info.Type, CurvStruct2->R0, CurvStruct2->R1,
            CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
            CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->a_param,
            CurvStruct2->b_param, CutOff);
        // 'cutCurvStruct:18' curvC = curv;
        *CurvStruct2_C = *CurvStruct2;
        // 'cutCurvStruct:20' if( isEnd )
        // 'cutCurvStruct:21' curvC.b_param = u1_tilda;
        CurvStruct2_C->b_param = c_u1_tilda;
        // 'cutCurvStruct:22' curvC.a_param = a + b - curvC.b_param;
        CurvStruct2_C->a_param = (CurvStruct2->a_param + CurvStruct2->b_param) - c_u1_tilda;
        // 'cutCurvStruct:24' if( isAZeroEnd( curvC ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((CurvStruct2->Info.zspdmode == ZSpdMode_NZ) ||
            (CurvStruct2->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:7' zeroFlag = true;
            // 'cutCurvStruct:25' curvC.Info.zspdmode = ZSpdMode.NZ;
            CurvStruct2_C->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'isAZeroEnd:9' zeroFlag = false;
            // 'cutCurvStruct:26' else
            // 'cutCurvStruct:27' curvC.Info.zspdmode = ZSpdMode.NN;
            CurvStruct2_C->Info.zspdmode = ZSpdMode_NN;
        }
        // 'calcTransition:137' if IsEnabledDebugLog(DebugCfg.Global)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        Double2MultiWord(DebugConfig, (unsigned int *)&r7.chunks[0U]);
        r8 = r2;
        MultiWordAnd((unsigned int *)&r7.chunks[0U], (unsigned int *)&r2.chunks[0U],
                     (unsigned int *)&r1.chunks[0U]);
        if (uMultiWordNe((unsigned int *)&r1.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'calcTransition:138' PrintCurvStruct(ctx, CurvStruct1_C)
            PrintCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                            ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                            ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                            ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1->Info.Type,
                            CurvStruct1_C->Info.zspdmode, CurvStruct1->Info.FeedRate,
                            CurvStruct1->R0, CurvStruct1->R1, CurvStruct1->CorrectedHelixCenter,
                            CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                            CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->UseConstJerk,
                            CurvStruct1->ConstJerk, CurvStruct1_C->a_param, CurvStruct1->b_param);
            // 'calcTransition:139' PrintCurvStruct(ctx, CurvStruct2_C)
            PrintCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                            ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                            ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                            ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2->Info.Type,
                            CurvStruct2_C->Info.zspdmode, CurvStruct2->Info.FeedRate,
                            CurvStruct2->R0, CurvStruct2->R1, CurvStruct2->CorrectedHelixCenter,
                            CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                            CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->UseConstJerk,
                            CurvStruct2->ConstJerk, CurvStruct2_C->a_param, c_u1_tilda);
        }
        // 'calcTransition:142' [r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         CurvStruct1->Info.Type, CurvStruct1->R0, CurvStruct1->R1,
                         CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                         CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                         CurvStruct1_C->a_param, CurvStruct1->b_param, r0D0, r0D1, r0D2);
        // 'calcTransition:143' [r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         CurvStruct2->Info.Type, CurvStruct2->R0, CurvStruct2->R1,
                         CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                         CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                         CurvStruct2_C->a_param, c_u1_tilda, r1D0, r1D1, r1D2);
        //  G2 transition calculation
        // 'calcTransition:146' [p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0,
        // r1D1, r1D2);
        G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &a__1, &a__2);
        // 'calcTransition:148' if ret==1
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'calcTransition:152' CurvStruct_T = constrTransP5Struct(CurvStruct1.Info,
            // CurvStruct1.R0,... 'calcTransition:153' CurvStruct1.R1, p5);
            b_constrTransP5Struct(
                CurvStruct1->Info.zspdmode, CurvStruct1->Info.TRAFO, CurvStruct1->Info.HSC,
                CurvStruct1->Info.FeedRate, CurvStruct1->Info.SpindleSpeed,
                CurvStruct1->Info.gcode_source_line, CurvStruct1->Info.G91, CurvStruct1->Info.G91_1,
                CurvStruct1->R0, CurvStruct1->R1, p5, CurvStruct_T);
            // 'calcTransition:154' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
            CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
            //  only value possible for a transition
            // 'calcTransition:155' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            uint64m_T r13;
            uint64m_T r22;
            // 'calcTransition:157' elseif ret==2
            //  badly conditioned matrix in G2_Hermite()
            // 'calcTransition:160' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'calcTransition:162' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r10.chunks[0U]);
            r13 = r12;
            MultiWordAnd((unsigned int *)&r10.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r14.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r14.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:163' DebugLog(DebugCfg.Error, '=========== Badly Cond. Matrix in
            // G2_Hermite() ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r20.chunks[0U]);
            r22 = r12;
            MultiWordAnd((unsigned int *)&r20.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r13.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r13.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== Badly Cond. Matrix in G2_Hermite() ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:164' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r26.chunks[0U]);
            MultiWordAnd((unsigned int *)&r26.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r22.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r22.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->Info.gcode_source_line,
                       CurvStruct2->Info.gcode_source_line);
                fflush(stdout);
            }
            // 'calcTransition:166' if coder.target('matlab')
        } else if (ret == 6) {
            uint64m_T r16;
            uint64m_T r24;
            // 'calcTransition:191' elseif ret==6
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'calcTransition:195' CurvStruct_T = constrTransP5Struct(CurvStruct1.Info,
            // CurvStruct1.R0,... 'calcTransition:196' CurvStruct1.R1, p5);
            b_constrTransP5Struct(
                CurvStruct1->Info.zspdmode, CurvStruct1->Info.TRAFO, CurvStruct1->Info.HSC,
                CurvStruct1->Info.FeedRate, CurvStruct1->Info.SpindleSpeed,
                CurvStruct1->Info.gcode_source_line, CurvStruct1->Info.G91, CurvStruct1->Info.G91_1,
                CurvStruct1->R0, CurvStruct1->R1, p5, CurvStruct_T);
            // 'calcTransition:197' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
            CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
            //  only value possible for a transition
            // 'calcTransition:198' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
            // 'calcTransition:200' DebugLog(DebugCfg.Warning, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r15.chunks[0U]);
            r16 = r17;
            MultiWordAnd((unsigned int *)&r15.chunks[0U], (unsigned int *)&r17.chunks[0U],
                         (unsigned int *)&r18.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r18.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:201' DebugLog(DebugCfg.Warning, '=========== status = 6
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r23.chunks[0U]);
            r24 = r17;
            MultiWordAnd((unsigned int *)&r23.chunks[0U], (unsigned int *)&r17.chunks[0U],
                         (unsigned int *)&r16.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r16.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== status = 6 ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:202' DebugLog(DebugCfg.Warning, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r27.chunks[0U]);
            MultiWordAnd((unsigned int *)&r27.chunks[0U], (unsigned int *)&r17.chunks[0U],
                         (unsigned int *)&r24.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r24.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->Info.gcode_source_line,
                       CurvStruct2->Info.gcode_source_line);
                fflush(stdout);
            }
            // 'calcTransition:204' if coder.target('matlab')
        } else {
            uint64m_T r11;
            uint64m_T r21;
            // 'calcTransition:221' else
            // 'calcTransition:223' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'calcTransition:225' DebugLog(DebugCfg.Error, '========== CalcTransition
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r9.chunks[0U]);
            r11 = r12;
            MultiWordAnd((unsigned int *)&r9.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r8.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r8.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("========== CalcTransition ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:226' DebugLog(DebugCfg.Error, '=========== No Solution
            // ==========\n');
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r19.chunks[0U]);
            r21 = r12;
            MultiWordAnd((unsigned int *)&r19.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r11.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r11.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("=========== No Solution ==========\n");
                fflush(stdout);
            }
            // 'calcTransition:227' DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
            //  1 -> stdout
            //  2 -> stderr
            // 'DebugLog:5' if IsEnabledDebugLog(cfg)
            // 'IsEnabledDebugLog:4' value = false;
            // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
            Double2MultiWord(DebugConfig, (unsigned int *)&r25.chunks[0U]);
            MultiWordAnd((unsigned int *)&r25.chunks[0U], (unsigned int *)&r12.chunks[0U],
                         (unsigned int *)&r21.chunks[0U]);
            if (uMultiWordNe((unsigned int *)&r21.chunks[0U], (unsigned int *)&r4.chunks[0U])) {
                // 'IsEnabledDebugLog:7' value = true;
                // 'DebugLog:6' fprintf(1, varargin{:});
                printf("Lines: %d, %d\n\n", CurvStruct1->Info.gcode_source_line,
                       CurvStruct2->Info.gcode_source_line);
                fflush(stdout);
            }
            // 'calcTransition:229' if coder.target('matlab')
        }
        // 'calcTransition:255' CurvStruct_T.Info.gcode_source_line = line2;
        CurvStruct_T->Info.gcode_source_line = CurvStruct2->Info.gcode_source_line;
        // 'calcTransition:256' CurvStruct_T.Info.SpindleSpeed = min(CurvStruct1.Info.SpindleSpeed,
        // CurvStruct2.Info.SpindleSpeed);
        CurvStruct_T->Info.SpindleSpeed =
            std::fmin(CurvStruct1->Info.SpindleSpeed, CurvStruct2->Info.SpindleSpeed);
        // 'calcTransition:257' if( coder.target("MATLAB") )
    }
    *status = b_status;
}

} // namespace ocn

//
// File trailer for calcTransition.cpp
//
// [EOF]
//
