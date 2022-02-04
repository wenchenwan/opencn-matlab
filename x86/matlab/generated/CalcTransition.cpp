//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcTransition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "CalcTransition.h"
#include "ConstrTransP5Struct.h"
#include "CutCurvStruct.h"
#include "DebugLog.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation.h"
#include "LengthCurv.h"
#include "PrintCurvStruct.h"
#include "SplineLengthApproxGL_bounds.h"
#include "collinear.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
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
    int ret;
    TransitionResult b_status;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    CutOff_tmp = ctx->cfg.CutOff;
    CutOff = CutOff_tmp;
    Length_Threshold = 3.0 * CutOff_tmp;
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                          CurvStruct1);
        b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                          CurvStruct2);
    }
    *CurvStruct_T = *CurvStruct1;
    // default value
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_1, r0D1_1);
    c_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
    b_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_1, r1D1_1);
    c_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);
    //  colinearity test
    if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix) &&
        collinear(r0D1_2, r1D1_1, ctx->cfg.ColTolCos)) {
        b_status = TransitionResult_Collinear;
        *CurvStruct1_C = *CurvStruct1;
        *CurvStruct2_C = *CurvStruct2;
    } else {
        double L1;
        double L2;
        L1 = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                        CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                        CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                        CurvStruct1->a_param, CurvStruct1->b_param);
        L2 = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                        CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                        CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                        CurvStruct2->a_param, CurvStruct2->b_param);
        //  CutOff calculation
        if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline)) {
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double x;
            double y;
            unsigned int k;
            if (CurvStruct1->Type == CurveType_Spline) {
                double u1_tilda;
                ctx->q_splines.get(CurvStruct1->sp_index, &expl_temp);
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                for (k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(k) - 1] >= u1_tilda;
                     k = static_cast<unsigned int>(static_cast<int>(k) - 1)) {
                }
                x = SplineLengthApproxGL_bounds(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                ctx->cfg.GaussLegendreW, CurvStruct1->sp_index,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1],
                                                u1_tilda) /
                    2.0;
            } else if (L1 < Length_Threshold) {
                x = L1 / 3.0;
            } else {
                x = CutOff_tmp;
            }
            if (CurvStruct2->Type == CurveType_Spline) {
                int loop_ub;
                ctx->q_splines.get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i{0}; i < loop_ub; i++) {
                    expl_temp.sp.knots[i] = b_expl_temp.sp.knots[i];
                }
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                //  We need to find the next spline knot u1_tilda...
                //
                for (k = 1U; expl_temp.sp.knots[static_cast<int>(k) - 1] <= CurvStruct2->b_param;
                     k++) {
                }
                y = SplineLengthApproxGL_bounds(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                ctx->cfg.GaussLegendreW, CurvStruct2->sp_index,
                                                CurvStruct2->b_param,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1]) /
                    2.0;
            } else if (L2 < Length_Threshold) {
                y = L2 / 3.0;
            } else {
                y = ctx->cfg.CutOff;
            }
            CutOff = std::fmin(x, y);
        }
        *CurvStruct1_C = *CurvStruct1;
        CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                      CurvStruct1_C, CutOff);
        *CurvStruct2_C = *CurvStruct2;
        b_CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                        CurvStruct2_C, CutOff);
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                              CurvStruct1_C);
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                              CurvStruct2_C);
        }
        b_EvalCurvStruct(&ctx->q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0, CurvStruct1_C->P1,
                         CurvStruct1_C->CorrectedHelixCenter, CurvStruct1_C->evec,
                         CurvStruct1_C->theta, CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5,
                         CurvStruct1_C->sp_index, CurvStruct1_C->a_param, CurvStruct1_C->b_param,
                         r0D0, r0D1, r0D2);
        c_EvalCurvStruct(&ctx->q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0, CurvStruct2_C->P1,
                         CurvStruct2_C->CorrectedHelixCenter, CurvStruct2_C->evec,
                         CurvStruct2_C->theta, CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5,
                         CurvStruct2_C->sp_index, CurvStruct2_C->a_param, CurvStruct2_C->b_param,
                         r1D0, r1D1, r1D2);
        //  G2 transition calculation
        G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &a__1, &a__2);
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            //  badly conditioned matrix in G2_Hermite()
            b_status = TransitionResult_NoSolution;
            DebugLog();
            b_DebugLog();
            DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        } else if (ret == 6) {
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
            b_status = TransitionResult_Ok;
            c_DebugLog();
            d_DebugLog();
            b_DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        } else {
            b_status = TransitionResult_NoSolution;
            DebugLog();
            e_DebugLog();
            DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        }
        CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
        CurvStruct_T->SpindleSpeed =
            std::fmin(CurvStruct1->SpindleSpeed, CurvStruct2->SpindleSpeed);
    }
    *status = b_status;
}

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
    int ret;
    TransitionResult b_status;
    CutOff = ctx_cfg_CutOff;
    Length_Threshold = 3.0 * ctx_cfg_CutOff;
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        b_PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                          CurvStruct1);
        b_PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                          CurvStruct2);
    }
    *CurvStruct_T = *CurvStruct1;
    // default value
    b_EvalCurvStruct(ctx_q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_1, r0D1_1);
    c_EvalCurvStruct(ctx_q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                     CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                     CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                     CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_1, r1D1_1);
    c_EvalCurvStruct(ctx_q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                     CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                     CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                     CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);
    //  colinearity test
    if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix) &&
        collinear(r0D1_2, r1D1_1, ctx_cfg_ColTolCos)) {
        b_status = TransitionResult_Collinear;
        *CurvStruct1_C = *CurvStruct1;
        *CurvStruct2_C = *CurvStruct2;
    } else {
        double L1;
        double L2;
        L1 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                        CurvStruct1->CorrectedHelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                        CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                        CurvStruct1->a_param, CurvStruct1->b_param);
        L2 = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                        CurvStruct2->CorrectedHelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                        CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                        CurvStruct2->a_param, CurvStruct2->b_param);
        //  CutOff calculation
        if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline)) {
            if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                CutOff = std::fmin(L1, L2) / 3.0;
            }
        } else {
            double x;
            double y;
            unsigned int k;
            if (CurvStruct1->Type == CurveType_Spline) {
                double u1_tilda;
                ctx_q_splines->get(CurvStruct1->sp_index, &expl_temp);
                //  In a very general case we may cut a spline several times
                //  at the end;
                //  If a spline had already been cut at the end,
                //  we must compute the corresponding
                //  native spline parameter (u1_tilda) value
                //  This value will be different from 1 in this special case
                u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;
                //  We need to find the previous spline knot u0_tilda...
                //
                for (k = static_cast<unsigned int>(expl_temp.sp.knots.size(1));
                     expl_temp.sp.knots[static_cast<int>(k) - 1] >= u1_tilda;
                     k = static_cast<unsigned int>(static_cast<int>(k) - 1)) {
                }
                x = SplineLengthApproxGL_bounds(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, CurvStruct1->sp_index,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1],
                                                u1_tilda) /
                    2.0;
            } else if (L1 < Length_Threshold) {
                x = L1 / 3.0;
            } else {
                x = ctx_cfg_CutOff;
            }
            if (CurvStruct2->Type == CurveType_Spline) {
                int loop_ub;
                ctx_q_splines->get(CurvStruct2->sp_index, &b_expl_temp);
                expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                loop_ub = b_expl_temp.sp.knots.size(1);
                for (int i{0}; i < loop_ub; i++) {
                    expl_temp.sp.knots[i] = b_expl_temp.sp.knots[i];
                }
                //  In a very general case we may cut a spline several times
                //  at the beginning;
                //  If a spline had already been cut at the beginning,
                //  we must compute the corresponding
                //  native spline parameter (u0_tilda) value
                //  This value will be different from 0 in this special case
                //  We need to find the next spline knot u1_tilda...
                //
                for (k = 1U; expl_temp.sp.knots[static_cast<int>(k) - 1] <= CurvStruct2->b_param;
                     k++) {
                }
                y = SplineLengthApproxGL_bounds(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, CurvStruct2->sp_index,
                                                CurvStruct2->b_param,
                                                expl_temp.sp.knots[static_cast<int>(k) - 1]) /
                    2.0;
            } else if (L2 < Length_Threshold) {
                y = L2 / 3.0;
            } else {
                y = ctx_cfg_CutOff;
            }
            CutOff = std::fmin(x, y);
        }
        *CurvStruct1_C = *CurvStruct1;
        CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1_C,
                      CutOff);
        *CurvStruct2_C = *CurvStruct2;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        CurvStruct2_C, CutOff);
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                              CurvStruct1_C);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                              CurvStruct2_C);
        }
        b_EvalCurvStruct(ctx_q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0, CurvStruct1_C->P1,
                         CurvStruct1_C->CorrectedHelixCenter, CurvStruct1_C->evec,
                         CurvStruct1_C->theta, CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5,
                         CurvStruct1_C->sp_index, CurvStruct1_C->a_param, CurvStruct1_C->b_param,
                         r0D0, r0D1, r0D2);
        c_EvalCurvStruct(ctx_q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0, CurvStruct2_C->P1,
                         CurvStruct2_C->CorrectedHelixCenter, CurvStruct2_C->evec,
                         CurvStruct2_C->theta, CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5,
                         CurvStruct2_C->sp_index, CurvStruct2_C->a_param, CurvStruct2_C->b_param,
                         r1D0, r1D1, r1D2);
        //  G2 transition calculation
        G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &a__1, &a__2);
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            //  badly conditioned matrix in G2_Hermite()
            b_status = TransitionResult_NoSolution;
            DebugLog();
            b_DebugLog();
            DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        } else if (ret == 6) {
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
            b_status = TransitionResult_Ok;
            c_DebugLog();
            d_DebugLog();
            b_DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        } else {
            b_status = TransitionResult_NoSolution;
            DebugLog();
            e_DebugLog();
            DebugLog(CurvStruct1->gcode_source_line, CurvStruct2->gcode_source_line);
        }
        CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
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
