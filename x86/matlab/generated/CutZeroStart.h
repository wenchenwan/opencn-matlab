//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroStart.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef CUTZEROSTART_H
#define CUTZEROSTART_H

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
void CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines,
                  int ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                  double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit,
                  double ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit,
                  bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
                  const CurvStruct *b_CurvStruct, double k0, CurvStruct *CurvStruct1,
                  CurvStruct *CurvStruct2);

void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines,
                    int ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                    double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit,
                    double ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit,
                    bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
                    const CurvStruct *b_CurvStruct, CurvStruct *CurvStruct1,
                    CurvStruct *CurvStruct2);

} // namespace ocn

#endif
//
// File trailer for CutZeroStart.h
//
// [EOF]
//
