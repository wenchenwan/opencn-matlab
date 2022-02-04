//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CurvCollinear.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CurvCollinear.h"
#include "EvalCurvStruct.h"
#include "collinear.h"
#include "queue_coder.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

// Function Definitions
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType Curv1_Type
//                const double Curv1_P0[3]
//                const double Curv1_P1[3]
//                const double Curv1_CorrectedHelixCenter[3]
//                const double Curv1_evec[3]
//                double Curv1_theta
//                double Curv1_pitch
//                const double Curv1_CoeffP5[6][3]
//                int Curv1_sp_index
//                double Curv1_a_param
//                double Curv1_b_param
//                const CurvStruct *Curv2
//                double ToleranceCos
// Return Type  : bool
//
namespace ocn {
bool CurvCollinear(const queue_coder *ctx_q_splines, CurveType Curv1_Type, const double Curv1_P0[3],
                   const double Curv1_P1[3], const double Curv1_CorrectedHelixCenter[3],
                   const double Curv1_evec[3], double Curv1_theta, double Curv1_pitch,
                   const double Curv1_CoeffP5[6][3], int Curv1_sp_index, double Curv1_a_param,
                   double Curv1_b_param, const CurvStruct *Curv2, double ToleranceCos)
{
    double V0[3];
    double V1[3];
    double a__1[3];
    double a__2[3];
    c_EvalCurvStruct(ctx_q_splines, Curv1_Type, Curv1_P0, Curv1_P1, Curv1_CorrectedHelixCenter,
                     Curv1_evec, Curv1_theta, Curv1_pitch, Curv1_CoeffP5, Curv1_sp_index,
                     Curv1_a_param, Curv1_b_param, a__1, V0);
    b_EvalCurvStruct(ctx_q_splines, Curv2->Type, Curv2->P0, Curv2->P1, Curv2->CorrectedHelixCenter,
                     Curv2->evec, Curv2->theta, Curv2->pitch, Curv2->CoeffP5, Curv2->sp_index,
                     Curv2->a_param, Curv2->b_param, a__2, V1);
    return collinear(V0, V1, ToleranceCos);
}

} // namespace ocn

//
// File trailer for CurvCollinear.cpp
//
// [EOF]
//
