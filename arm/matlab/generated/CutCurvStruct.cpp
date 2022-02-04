//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CutCurvStruct.h"
#include "EvalCurvStruct.h"
#include "SplineLengthFindU_down.h"
#include "SplineLengthFindU_up.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include <cmath>

// Function Definitions
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
    double a__1[3];
    double a__2[3];
    double r1D0[3];
    double r1D1[3];
    double u0_tilda;
    double u1_tilda;
    if (b_CurvStruct->Type == CurveType_Spline) {
        u0_tilda = b_CurvStruct->b_param;
        if (d1 != 0.0) {
            u1_tilda = SplineLengthFindU_down(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                              ctx_cfg_GaussLegendreW, b_CurvStruct->sp_index, d1,
                                              b_CurvStruct->a_param + b_CurvStruct->b_param);
            //  RHG
        } else {
            u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
        }
    } else {
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        //  r1D0 and r1D1 are with respect to u
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__1,
                         r1D0);
        c_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__2,
                         r1D1);
        //  d0 = Integral_0_u0 ||r'(u)||du
        //  d1 = Integral_u1_1 ||r'(u)||du
        sqrt_calls++;
        sqrt_calls++;
        //  conversion to native curve parameter u_tilda
        u0_tilda = b_CurvStruct->a_param *
                       (0.0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow(r1D0[1], 2.0)) +
                                        std::pow(r1D0[2], 2.0))) +
                   b_CurvStruct->b_param;
        u1_tilda = b_CurvStruct->a_param *
                       (1.0 - d1 / std::sqrt((std::pow(r1D1[0], 2.0) + std::pow(r1D1[1], 2.0)) +
                                             std::pow(r1D1[2], 2.0))) +
                   b_CurvStruct->b_param;
    }
    b_CurvStruct->a_param = u1_tilda - u0_tilda;
    b_CurvStruct->b_param = u0_tilda;
}

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
    if (b_CurvStruct->Type == CurveType_Spline) {
        if (d0 != 0.0) {
            u0_tilda =
                SplineLengthFindU_up(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                     b_CurvStruct->sp_index, d0, b_CurvStruct->b_param);
            //  RHG
        } else {
            u0_tilda = b_CurvStruct->b_param;
        }
        u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
    } else {
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        //  r1D0 and r1D1 are with respect to u
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__1,
                         r1D0);
        c_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                         b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                         b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param, a__2,
                         r1D1);
        //  d0 = Integral_0_u0 ||r'(u)||du
        //  d1 = Integral_u1_1 ||r'(u)||du
        sqrt_calls++;
        sqrt_calls++;
        //  conversion to native curve parameter u_tilda
        u0_tilda = b_CurvStruct->a_param *
                       (d0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow(r1D0[1], 2.0)) +
                                       std::pow(r1D0[2], 2.0))) +
                   b_CurvStruct->b_param;
        u1_tilda = b_CurvStruct->a_param *
                       (1.0 - 0.0 / std::sqrt((std::pow(r1D1[0], 2.0) + std::pow(r1D1[1], 2.0)) +
                                              std::pow(r1D1[2], 2.0))) +
                   b_CurvStruct->b_param;
    }
    b_CurvStruct->a_param = u1_tilda - u0_tilda;
    b_CurvStruct->b_param = u0_tilda;
}

} // namespace ocn

//
// File trailer for CutCurvStruct.cpp
//
// [EOF]
//
