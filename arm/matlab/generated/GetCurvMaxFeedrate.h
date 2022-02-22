//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvMaxFeedrate.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 21-Feb-2022 17:59:00
//

#ifndef GETCURVMAXFEEDRATE_H
#define GETCURVMAXFEEDRATE_H

// Include Files
#include "EvalCurvStruct_types2.h"
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
double GetCurvMaxFeedrate(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
                          const double ctx_cfg_jmax[3], CurveType CurvStruct_Type,
                          const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                          const double CurvStruct_CorrectedHelixCenter[3],
                          const double CurvStruct_evec[3], double CurvStruct_theta,
                          double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                          int CurvStruct_sp_index, double CurvStruct_FeedRate,
                          double CurvStruct_a_param, double CurvStruct_b_param);

}

#endif
//
// File trailer for GetCurvMaxFeedrate.h
//
// [EOF]
//
