//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "CutCurvStruct.h"
#include "EvalCurvStruct.h"
#include "SplineLengthApprox.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
//  We determine a new value of the parameter u_tilda
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                CurvStruct *b_CurvStruct
//                double d1
// Return Type  : void
//
namespace ocn {
void CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                   CurvStruct *b_CurvStruct, double d1)
{
    ::coder::array<double, 2U> Integrand;
    ::coder::array<double, 2U> du_tilda;
    ::coder::array<double, 2U> u_mid_tilda;
    CurvStruct b_ctx_q_splines;
    double a__1[3];
    double a__2[3];
    double r1D0[3];
    double r1D1[3];
    double L_tot;
    double u0_tilda;
    double u1_tilda;
    if (b_CurvStruct->Type == CurveType_Spline) {
        ctx_q_splines->get(b_CurvStruct->sp_index, &b_ctx_q_splines);
        //  discretizing along the total spline
        //  from u=0 to u=1
        SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                           b_CurvStruct->b_param, b_CurvStruct->a_param + b_CurvStruct->b_param,
                           &L_tot, Integrand, u_mid_tilda, du_tilda);
        u0_tilda = b_CurvStruct->b_param;
        if (d1 != 0.0) {
            double L;
            unsigned int k;
            //  spline-long length calculation by rectangles method
            //  beginning from u=0
            //  until L_tot-d1 is reached
            L = 0.0;
            k = 1U;
            while ((L < L_tot - d1) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                L += Integrand[static_cast<int>(k) - 1] * du_tilda[static_cast<int>(k) - 1];
                k++;
            }
            u1_tilda = u_mid_tilda[static_cast<int>(k) - 1];
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
//                double ctx_cfg_NGridLengthSpline
//                CurvStruct *b_CurvStruct
//                double d0
// Return Type  : void
//
void b_CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                     CurvStruct *b_CurvStruct, double d0)
{
    ::coder::array<double, 2U> Integrand;
    ::coder::array<double, 2U> du_tilda;
    ::coder::array<double, 2U> u_mid_tilda;
    CurvStruct b_ctx_q_splines;
    double a__1[3];
    double a__2[3];
    double r1D0[3];
    double r1D1[3];
    double L_tot;
    double u0_tilda;
    double u1_tilda;
    if (b_CurvStruct->Type == CurveType_Spline) {
        ctx_q_splines->get(b_CurvStruct->sp_index, &b_ctx_q_splines);
        //  discretizing along the total spline
        //  from u=0 to u=1
        SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                           b_CurvStruct->b_param, b_CurvStruct->a_param + b_CurvStruct->b_param,
                           &L_tot, Integrand, u_mid_tilda, du_tilda);
        if (d0 != 0.0) {
            double L;
            unsigned int k;
            //  spline-long length calculation by rectangles method
            //  beginning from u=0
            //  until d0 is reached
            L = 0.0;
            k = 1U;
            while ((L < d0) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                L += Integrand[static_cast<int>(k) - 1] * du_tilda[static_cast<int>(k) - 1];
                k++;
            }
            u0_tilda = u_mid_tilda[static_cast<int>(k) - 1];
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
