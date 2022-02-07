//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef LENGTHCURV_H
#define LENGTHCURV_H

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

}

// Function Declarations
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                  CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3],
                  const double Curv_CorrectedHelixCenter[3], const double Curv_evec[3],
                  double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
                  int Curv_sp_index, double Curv_a_param, double Curv_b_param);

}

#endif
//
// File trailer for LengthCurv.h
//
// [EOF]
//
