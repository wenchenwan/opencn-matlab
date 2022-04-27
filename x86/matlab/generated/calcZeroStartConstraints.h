//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcZeroStartConstraints.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef CALCZEROSTARTCONSTRAINTS_H
#define CALCZEROSTARTCONSTRAINTS_H

// Include Files
#include "opencn_matlab_types2.h"
#include "rtwtypes.h"
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
void calcZeroStartConstraints(const queue_coder *ctx_q_splines, double ctx_cfg_dt,
                              CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3],
                              const double Curv_CorrectedHelixCenter[3], const double Curv_evec[3],
                              double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
                              int Curv_sp_index, double Curv_ConstJerk, double Curv_a_param,
                              double Curv_b_param, double *v_0, double *at_0);

}

#endif
//
// File trailer for calcZeroStartConstraints.h
//
// [EOF]
//
