//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroStart.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 10:58:42
//

#ifndef CUTZEROSTART_H
#define CUTZEROSTART_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
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
                  bool ctx_cfg_DebugCutZero, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct, double k0,
                  CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);

void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines,
                    int ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                    double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit,
                    double ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit,
                    bool ctx_cfg_DebugCutZero, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct,
                    CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);

void b_binary_expand_op(::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r2D,
                        const ::coder::array<double, 2U> &d1uk,
                        const ::coder::array<double, 2U> &d2uk);

void b_binary_expand_op(::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &r,
                        const ::coder::array<double, 2U> &r1);

void binary_expand_op(::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &r,
                      const ::coder::array<double, 2U> &r1, const ::coder::array<double, 2U> &c);

} // namespace ocn

#endif
//
// File trailer for CutZeroStart.h
//
// [EOF]
//
