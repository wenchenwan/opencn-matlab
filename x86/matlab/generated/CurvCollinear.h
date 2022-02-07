//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CurvCollinear.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef CURVCOLLINEAR_H
#define CURVCOLLINEAR_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types2.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
bool CurvCollinear(const queue_coder *ctx_q_splines, CurveType Curv1_Type, const double Curv1_P0[3],
                   const double Curv1_P1[3], const double Curv1_CorrectedHelixCenter[3],
                   const double Curv1_evec[3], double Curv1_theta, double Curv1_pitch,
                   const double Curv1_CoeffP5[6][3], int Curv1_sp_index, double Curv1_a_param,
                   double Curv1_b_param, const CurvStruct *Curv2, double ToleranceDeg);

}

#endif
//
// File trailer for CurvCollinear.h
//
// [EOF]
//
