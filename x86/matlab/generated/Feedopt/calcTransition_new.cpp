//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition_new.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "calcTransition_new.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation_nAxis.h"
#include "LengthCurv.h"
#include "constrTransP5Struct.h"
#include "cutCurvStructU.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [ status, curv1C, curv2C, curvT ] = calcTransition_new( ctx, curv1, curv2 )
//
// calcTransition_new : Compute a transition curve using on a polynome of
//  degree 5.
//
//  ctx           : The context
//  curv          : Current structure of the curve
//  nextCurv      : Next structure of the curve
//
//  curv          : New calculated curve structure (replace CurvStruct1)
//  curvT         : New calculated transition curve
//  nextCurv      : New calculated curve structure (replace CurvStruct2)
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv1
//                const CurvStruct *curv2
//                TransitionResult *status
//                CurvStruct *curv1C
//                CurvStruct *curv2C
//                CurvStruct *curvT
// Return Type  : void
//
namespace ocn {
void calcTransition_new(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
    const ::coder::array<bool, 2U> &ctx_cfg_maskRot, const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, double ctx_cfg_CutOff, const double ctx_cfg_GaussLegendreX[5],
    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv1, const CurvStruct *curv2,
    TransitionResult *status, CurvStruct *curv1C, CurvStruct *curv2C, CurvStruct *curvT)
{
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D2;
    double p5[6][5];
    double L1;
    double L2;
    double Lcut1;
    double Lcut2;
    double u1_tilda;
    double u2_tilda;
    int ret;
    TransitionResult b_status;
    // 'calcTransition_new:15' coder.inline( "never" );
    // 'calcTransition_new:17' CutOff = ctx.cfg.CutOff;
    // 'calcTransition_new:18' Lcut1 = CutOff;
    Lcut1 = ctx_cfg_CutOff;
    // 'calcTransition_new:18' Lcut2 = CutOff;
    Lcut2 = ctx_cfg_CutOff;
    // 'calcTransition_new:20' L1 = LengthCurv( ctx, curv1, 0, 1 );
    L1 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                    ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                    ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                    curv1->Info, curv1->R0, curv1->R1, curv1->CorrectedHelixCenter, curv1->evec,
                    curv1->theta, curv1->pitch, curv1->CoeffP5, curv1->sp_index, curv1->a_param,
                    curv1->b_param);
    // 'calcTransition_new:21' L2 = LengthCurv( ctx, curv2, 0, 1 );
    L2 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                    ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                    ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                    curv2->Info, curv2->R0, curv2->R1, curv2->CorrectedHelixCenter, curv2->evec,
                    curv2->theta, curv2->pitch, curv2->CoeffP5, curv2->sp_index, curv2->a_param,
                    curv2->b_param);
    // 'calcTransition_new:23' if( L1 / 3  < Lcut1 )
    if (L1 / 3.0 < ctx_cfg_CutOff) {
        // 'calcTransition_new:24' Lcut1 = L1 / 3;
        Lcut1 = L1 / 3.0;
    }
    // 'calcTransition_new:27' if( L2 / 3 < Lcut2 )
    if (L2 / 3.0 < ctx_cfg_CutOff) {
        // 'calcTransition_new:28' Lcut2 = L2 / 3;
        Lcut2 = L2 / 3.0;
    }
    // 'calcTransition_new:31' [ u1_tilda ] = cutCurvStructU( ctx, curv1, 0, L1 - Lcut1, false );
    u1_tilda = cutCurvStructU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                              ctx_cfg_maskCart, ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot,
                              ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                              ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv1, L1 - Lcut1);
    // 'calcTransition_new:32' curv1C              = curv1;
    *curv1C = *curv1;
    // 'calcTransition_new:33' curv1C.a_param      = u1_tilda -curv1C.b_param;
    curv1C->a_param = u1_tilda - curv1C->b_param;
    // 'calcTransition_new:35' [ u2_tilda ] = cutCurvStructU( ctx, curv2, 1, L2 - Lcut2, true );
    u2_tilda = b_cutCurvStructU(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                                ctx_cfg_maskCart, ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot,
                                ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                                ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv2, L2 - Lcut2);
    // 'calcTransition_new:37' curv2C              = curv2;
    *curv2C = *curv2;
    // 'calcTransition_new:38' curv2C.b_param      = u2_tilda;
    curv2C->b_param = u2_tilda;
    // 'calcTransition_new:39' curv2C.a_param      = curv2.a_param  + curv2.b_param -
    // curv2C.b_param;
    curv2C->a_param = (curv2->a_param + curv2->b_param) - u2_tilda;
    // 'calcTransition_new:41' [r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 );
    e_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv1C, r0D0, r0D1, r0D2);
    // 'calcTransition_new:42' [r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );
    f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                     ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv2C, r1D0, r1D1, r1D2);
    // 'calcTransition_new:45' [p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
    // 'calcTransition_new:46'                                                 r1D0, r1D1, r1D2);
    G2_Hermite_Interpolation_nAxis(ctx_cfg_NumberAxis, r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5,
                                   &ret);
    // 'calcTransition_new:48' curvT = constrTransP5Struct( curv1.Info, curv1.R1, curv2.R0, p5 );
    b_constrTransP5Struct(curv1->Info.TRAFO, curv1->Info.HSC, curv1->Info.FeedRate,
                          curv1->Info.SpindleSpeed, curv1->Info.gcode_source_line, curv1->Info.G91,
                          curv1->Info.G91_1, curv1->R1, curv2->R0, p5, curvT);
    // 'calcTransition_new:49' curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, ...
    // 'calcTransition_new:50'                                curv2.Info.SpindleSpeed );
    curvT->Info.SpindleSpeed = std::fmin(curv1->Info.SpindleSpeed, curv2->Info.SpindleSpeed);
    // 'calcTransition_new:51' curvT.Info.FeedRate     = min( curv1.Info.FeedRate, ...
    // 'calcTransition_new:52'                                curv2.Info.FeedRate );
    curvT->Info.FeedRate = std::fmin(curv1->Info.FeedRate, curv2->Info.FeedRate);
    // 'calcTransition_new:53' if( ret== 1 )
    if (ret == 1) {
        //  standard case
        //  transition CurvStruct calculation
        // 'calcTransition_new:56' status = TransitionResult.Ok;
        b_status = TransitionResult_Ok;
    } else if (ret == 2) {
        // 'calcTransition_new:57' elseif( ret == 2)
        //  badly conditioned matrix in G2_Hermite()
        // 'calcTransition_new:59' status = TransitionResult.NoSolution;
        b_status = TransitionResult_NoSolution;
    } else if (ret == 6) {
        // 'calcTransition_new:60' elseif( ret == 6)
        //  TODO: decide in the future...
        //  Now we ignore and construct the transition curve anyway
        // 'calcTransition_new:63' status = TransitionResult.Ok;
        b_status = TransitionResult_Ok;
    } else {
        // 'calcTransition_new:64' else
        // 'calcTransition_new:65' status = TransitionResult.NoSolution;
        b_status = TransitionResult_NoSolution;
    }
    // 'calcTransition_new:68' if( coder.target("MATLAB") && TransitionResult.Ok )
    *status = b_status;
}

} // namespace ocn

//
// File trailer for calcTransition_new.cpp
//
// [EOF]
//
