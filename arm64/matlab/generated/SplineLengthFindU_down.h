//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthFindU_down.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

#ifndef SPLINELENGTHFINDU_DOWN_H
#define SPLINELENGTHFINDU_DOWN_H

// Include Files
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
double SplineLengthFindU_down(const queue_coder *ctx_q_splines,
                              const double ctx_cfg_GaussLegendreX[5],
                              const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index, double L,
                              double u1);

}

#endif
//
// File trailer for SplineLengthFindU_down.h
//
// [EOF]
//
