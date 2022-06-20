//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 16:00:50
//

// Include Files
#include "calcTransition.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation_nAxis.h"
#include "LengthCurv.h"
#include "combineVectorElements.h"
#include "constrTransP5Struct.h"
#include "cutCurvStructU.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "splineLength.h"
#include "coder_array.h"
#include <cmath>

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
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
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
void calcTransition(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                    const int ctx_cfg_maskTot_size[2],
                    const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                    const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                    const ::coder::array<int, 1U> &ctx_cfg_indCart,
                    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                    int ctx_cfg_NCart, int ctx_cfg_NRot, double ctx_cfg_CutOff,
                    double ctx_cfg_ColTolCosSmooth, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *CurvStruct1,
                    const CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C,
                    CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C, TransitionResult *status)
{
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D0_1;
    ::coder::array<double, 1U> r0D0_2;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D1_1;
    ::coder::array<double, 1U> r0D1_2;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D0_1;
    ::coder::array<double, 1U> r1D0_2;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D1_1;
    ::coder::array<double, 1U> r1D1_2;
    ::coder::array<double, 1U> r1D2;
    CurvStruct b_expl_temp;
    CurvStruct c_expl_temp;
    CurvStruct expl_temp;
    double p5[6][5];
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
    // 'calcTransition:30' if coder.target( 'MATLAB' )
    // 'calcTransition:37' CurvStruct_T = CurvStruct1;
    *CurvStruct_T = *CurvStruct1;
    //  default value
    // 'calcTransition:38' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
    CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
    //  only value possible for a transition
    // 'calcTransition:40' [r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0);
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct1, r0D0_1, r0D1_1);
    //  Curv1 @0
    // 'calcTransition:41' [r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1);
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct1, r0D0_2, r0D1_2);
    //  Curv1 @1
    // 'calcTransition:42' [r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct2, r1D0_1, r1D1_1);
    //  Curv2 @0
    // 'calcTransition:43' [r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1);
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct2, r1D0_2, r1D1_2);
    //  Curv2 @1
    //  colinearity test
    // 'calcTransition:46' if  CurvStruct1.Info.Type ~= CurveType.Helix ...
    // 'calcTransition:47'     && CurvStruct2.Info.Type ~= CurveType.Helix ...
    // 'calcTransition:48'     && collinear(r0D1_2, r1D1_1, ColTolCos)
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
            r.set_size(r0D1_2.size(0));
            loop_ub = r0D1_2.size(0);
            for (int i{0}; i < loop_ub; i++) {
                double varargin_1;
                varargin_1 = r0D1_2[i];
                r[i] = std::pow(varargin_1, 2.0);
            }
            r1.set_size(r1D1_1.size(0));
            b_loop_ub = r1D1_1.size(0);
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                double b_varargin_1;
                b_varargin_1 = r1D1_1[i1];
                r1[i1] = std::pow(b_varargin_1, 2.0);
            }
            value = (c / (std::sqrt(coder::combineVectorElements(r)) *
                          std::sqrt(coder::combineVectorElements(r1))) >
                     ctx_cfg_ColTolCosSmooth);
        }
        if (value) {
            // 'calcTransition:50' status = TransitionResult.Collinear;
            b_status = TransitionResult_Collinear;
            // 'calcTransition:51' CurvStruct1_C = CurvStruct1;
            *CurvStruct1_C = *CurvStruct1;
            // 'calcTransition:52' CurvStruct2_C = CurvStruct2;
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
        double b_u1_tilda;
        double c_u1_tilda;
        // 'calcTransition:58' L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
        L1 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                        ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct1->Info, CurvStruct1->R0, CurvStruct1->R1,
                        CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                        CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                        CurvStruct1->a_param, CurvStruct1->b_param);
        // 'calcTransition:59' L2 = LengthCurv(ctx, CurvStruct2, 0, 1);
        L2 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                        ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct2->Info, CurvStruct2->R0, CurvStruct2->R1,
                        CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                        CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                        CurvStruct2->a_param, CurvStruct2->b_param);
        //  CutOff calculation
        // 'calcTransition:62' if CurvStruct1.Info.Type ~= CurveType.Spline ...
        // 'calcTransition:63'    && CurvStruct2.Info.Type ~= CurveType.Spline
        if ((CurvStruct1->Info.Type != CurveType_Spline) &&
            (CurvStruct2->Info.Type != CurveType_Spline)) {
            //  If L1 or L2 is smaller than 3*CutOff
            // 'calcTransition:65' if L1 < Length_Threshold || L2 < Length_Threshold
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                // 'calcTransition:66' CutOff = min (L1,L2)/3;
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double x;
            double y;
            unsigned int b_k;
            // 'calcTransition:68' else
            // 'calcTransition:69' if CurvStruct1.Info.Type == CurveType.Spline
            if (CurvStruct1->Info.Type == CurveType_Spline) {
                double u1_tilda;
                // 'calcTransition:70' Spline=ctx.q_spline.get(CurvStruct1.sp_index);
                ctx_q_spline->get(CurvStruct1->sp_index, &expl_temp);
                // 'calcTransition:71' sp = Spline.sp;
                // 'calcTransition:72' a = CurvStruct1.a_param;
                // 'calcTransition:73' b = CurvStruct1.b_param;
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                // 'calcTransition:81' u1_tilda = a*1+b;
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                // 'calcTransition:85' k = length(sp.knots);
                // 'calcTransition:86' while sp.knots(k) >= u1_tilda
                for (b_k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(b_k) - 1] >= u1_tilda;
                     b_k = static_cast<unsigned int>(static_cast<int>(b_k) - 1)) {
                    // 'calcTransition:87' k = k - 1;
                }
                // 'calcTransition:89' u0_tilda = sp.knots(k);
                // 'calcTransition:90' spline = ctx.q_spline.get( CurvStruct1.sp_index );
                ctx_q_spline->get(CurvStruct1->sp_index, &c_expl_temp);
                // 'calcTransition:91' [ l1 ] = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda )
                // / 2 ;
                x = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                 c_expl_temp.sp.Bl.handle, c_expl_temp.sp.Bl.order,
                                 c_expl_temp.sp.coeff, c_expl_temp.sp.knots, c_expl_temp.sp.Lk,
                                 expl_temp.sp.knots[static_cast<int>(b_k) - 1], u1_tilda) /
                    2.0;

                // 'calcTransition:92' else
                // 'calcTransition:93' if L1<Length_Threshold
            } else if (L1 < Length_Threshold) {
                // 'calcTransition:94' l1 = L1/3;
                x = L1 / 3.0;
            } else {
                // 'calcTransition:95' else
                // 'calcTransition:96' l1 = CutOff;
                x = ctx_cfg_CutOff;
            }
            // 'calcTransition:100' if CurvStruct2.Info.Type == CurveType.Spline
            if (CurvStruct2->Info.Type == CurveType_Spline) {
                int c_loop_ub;
                int d_loop_ub;
                int f_loop_ub;
                int g_loop_ub;
                // 'calcTransition:101' Spline=ctx.q_spline.get(CurvStruct2.sp_index);
                ctx_q_spline->get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                c_loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i2{0}; i2 < c_loop_ub; i2++) {
                    expl_temp.sp.knots[i2] = b_expl_temp.sp.knots[i2];
                }
                // 'calcTransition:102' sp = Spline.sp;
                // 'calcTransition:103' a = CurvStruct2.a_param;
                // 'calcTransition:104' b = CurvStruct2.b_param;
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                // 'calcTransition:112' u0_tilda = a*0+b;
                //  We need to find the next spline knot u1_tilda...
                //
                // 'calcTransition:116' k = 1;
                // 'calcTransition:117' while sp.knots(k) <= u0_tilda
                for (b_k = 1U;
                     expl_temp.sp.knots[static_cast<int>(b_k) - 1] <= CurvStruct2->b_param; b_k++) {
                    // 'calcTransition:118' k = k + 1;
                }
                // 'calcTransition:120' u1_tilda = sp.knots(k);
                // 'calcTransition:121' spline = ctx.q_spline.get( CurvStruct2.sp_index );
                ctx_q_spline->get(CurvStruct2->sp_index, &b_expl_temp);
                c_expl_temp.sp.coeff.set_size(b_expl_temp.sp.coeff.size(0),
                                              b_expl_temp.sp.coeff.size(1));
                d_loop_ub = b_expl_temp.sp.coeff.size(1);
                for (int i3{0}; i3 < d_loop_ub; i3++) {
                    int e_loop_ub;
                    e_loop_ub = b_expl_temp.sp.coeff.size(0);
                    for (int i4{0}; i4 < e_loop_ub; i4++) {
                        c_expl_temp.sp.coeff[i4 + c_expl_temp.sp.coeff.size(0) * i3] =
                            b_expl_temp.sp.coeff[i4 + b_expl_temp.sp.coeff.size(0) * i3];
                    }
                }
                c_expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                f_loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i5{0}; i5 < f_loop_ub; i5++) {
                    c_expl_temp.sp.knots[i5] = b_expl_temp.sp.knots[i5];
                }
                c_expl_temp.sp.Lk.set_size(1, b_expl_temp.sp.Lk.size(1));
                g_loop_ub = b_expl_temp.sp.Lk.size(1);
                for (int i6{0}; i6 < g_loop_ub; i6++) {
                    c_expl_temp.sp.Lk[i6] = b_expl_temp.sp.Lk[i6];
                }
                // 'calcTransition:122' [ l2 ] = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda )
                // / 2 ;
                y = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                 b_expl_temp.sp.Bl.handle, b_expl_temp.sp.Bl.order,
                                 c_expl_temp.sp.coeff, c_expl_temp.sp.knots, c_expl_temp.sp.Lk,
                                 CurvStruct2->b_param,
                                 expl_temp.sp.knots[static_cast<int>(b_k) - 1]) /
                    2.0;

                // 'calcTransition:123' else
                // 'calcTransition:124' if L2<Length_Threshold
            } else if (L2 < Length_Threshold) {
                // 'calcTransition:125' l2 = L2/3;
                y = L2 / 3.0;
            } else {
                // 'calcTransition:126' else
                // 'calcTransition:127' l2 = CutOff;
                y = ctx_cfg_CutOff;
            }
            // 'calcTransition:131' CutOff = min (l1,l2);
            CutOff = std::fmin(x, y);
        }
        // 'calcTransition:135' status = TransitionResult.Ok;
        //  Cut the curve structures
        // 'calcTransition:138' CurvStruct1_C = cutCurvStruct( ctx, CurvStruct1, 0, L1 - CutOff,
        // false );
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
            ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
            ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
            ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1, L1 - CutOff);
        // 'cutCurvStruct:18' curvC = curv;
        *CurvStruct1_C = *CurvStruct1;
        // 'cutCurvStruct:20' if( isEnd )
        // 'cutCurvStruct:30' else
        // 'cutCurvStruct:31' curvC.a_param = u1_tilda - curvC.b_param;
        CurvStruct1_C->a_param = b_u1_tilda - CurvStruct1_C->b_param;
        // 'cutCurvStruct:32' if( isAZeroStart( curvC ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((CurvStruct1_C->Info.zspdmode == ZSpdMode_ZN) ||
            (CurvStruct1_C->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:6' zeroFlag = true;
            // 'cutCurvStruct:33' curvC.Info.zspdmode = ZSpdMode.ZN;
            CurvStruct1_C->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'isAZeroStart:8' zeroFlag = false;
            // 'cutCurvStruct:34' else
            // 'cutCurvStruct:35' curvC.Info.zspdmode = ZSpdMode.NN;
            CurvStruct1_C->Info.zspdmode = ZSpdMode_NN;
        }
        // 'calcTransition:139' CurvStruct2_C = cutCurvStruct( ctx, CurvStruct2, 1, L2 - CutOff,
        // true  );
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
            ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
            ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
            ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2, L2 - CutOff);
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
        if ((CurvStruct2_C->Info.zspdmode == ZSpdMode_NZ) ||
            (CurvStruct2_C->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:7' zeroFlag = true;
            // 'cutCurvStruct:25' curvC.Info.zspdmode = ZSpdMode.NZ;
            CurvStruct2_C->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'isAZeroEnd:9' zeroFlag = false;
            // 'cutCurvStruct:26' else
            // 'cutCurvStruct:27' curvC.Info.zspdmode = ZSpdMode.NN;
            CurvStruct2_C->Info.zspdmode = ZSpdMode_NN;
        }
        // 'calcTransition:141' if coder.target( 'MATLAB' )
        // 'calcTransition:148' [r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
        e_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct1_C, r0D0, r0D1, r0D2);
        // 'calcTransition:149' [r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);
        f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, CurvStruct2_C, r1D0, r1D1, r1D2);
        //  G2 transition calculation
        //  [p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2);
        // 'calcTransition:153' [p5, ret, ~, ~] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1,
        // r0D2, r1D0, r1D1, r1D2);
        G2_Hermite_Interpolation_nAxis(ctx_cfg_NumberAxis, r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5,
                                       &ret, &a__1, &a__2);
        // 'calcTransition:155' if ret==1
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'calcTransition:159' CurvStruct_T = constrTransP5Struct(CurvStruct1.Info,
            // CurvStruct1.R0,... 'calcTransition:160' CurvStruct1.R1, p5);
            b_constrTransP5Struct(
                CurvStruct1->Info.zspdmode, CurvStruct1->Info.TRAFO, CurvStruct1->Info.HSC,
                CurvStruct1->Info.FeedRate, CurvStruct1->Info.SpindleSpeed,
                CurvStruct1->Info.gcode_source_line, CurvStruct1->Info.G91, CurvStruct1->Info.G91_1,
                CurvStruct1->R0, CurvStruct1->R1, p5, CurvStruct_T);
            // 'calcTransition:161' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
            CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
            //  only value possible for a transition
            // 'calcTransition:162' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            // 'calcTransition:164' elseif ret==2
            //  badly conditioned matrix in G2_Hermite()
            // 'calcTransition:167' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'calcTransition:169' if coder.target( 'MATLAB' )
            // 'calcTransition:175' if coder.target('matlab')
        } else if (ret == 6) {
            // 'calcTransition:200' elseif ret==6
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'calcTransition:204' CurvStruct_T = constrTransP5Struct(CurvStruct1.Info,
            // CurvStruct1.R0,... 'calcTransition:205' CurvStruct1.R1, p5);
            b_constrTransP5Struct(
                CurvStruct1->Info.zspdmode, CurvStruct1->Info.TRAFO, CurvStruct1->Info.HSC,
                CurvStruct1->Info.FeedRate, CurvStruct1->Info.SpindleSpeed,
                CurvStruct1->Info.gcode_source_line, CurvStruct1->Info.G91, CurvStruct1->Info.G91_1,
                CurvStruct1->R0, CurvStruct1->R1, p5, CurvStruct_T);
            // 'calcTransition:206' CurvStruct_T.Info.zspdmode = ZSpdMode.NN;
            CurvStruct_T->Info.zspdmode = ZSpdMode_NN;
            //  only value possible for a transition
            // 'calcTransition:207' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
            // 'calcTransition:209' if coder.target( 'MATLAB' )
            // 'calcTransition:215' if coder.target('matlab')
        } else {
            // 'calcTransition:232' else
            // 'calcTransition:234' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
            // 'calcTransition:235' if coder.target( 'MATLAB' )
            // 'calcTransition:241' if coder.target('matlab')
        }
        // 'calcTransition:267' CurvStruct_T.Info.gcode_source_line = line2;
        CurvStruct_T->Info.gcode_source_line = CurvStruct2->Info.gcode_source_line;
        // 'calcTransition:268' CurvStruct_T.Info.SpindleSpeed = min(CurvStruct1.Info.SpindleSpeed,
        // CurvStruct2.Info.SpindleSpeed);
        CurvStruct_T->Info.SpindleSpeed =
            std::fmin(CurvStruct1->Info.SpindleSpeed, CurvStruct2->Info.SpindleSpeed);
        // 'calcTransition:269' if( coder.target("MATLAB") )
    }
    *status = b_status;
}

} // namespace ocn

//
// File trailer for calcTransition.cpp
//
// [EOF]
//
