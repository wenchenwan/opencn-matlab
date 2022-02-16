//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroEnd.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
//

#ifndef CUTZEROEND_H
#define CUTZEROEND_H

// Include Files
#include "rtwtypes.h"
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
void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int ctx_cfg_NHorz,
                const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
                double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit,
                double ctx_cfg_ZeroStartVelLimit, const double ctx_cfg_GaussLegendreX[5],
                const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct, double k0,
                CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);

}

#endif
//
// File trailer for CutZeroEnd.h
//
// [EOF]
//
