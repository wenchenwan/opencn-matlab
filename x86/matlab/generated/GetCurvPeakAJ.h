//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvPeakAJ.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

#ifndef GETCURVPEAKAJ_H
#define GETCURVPEAKAJ_H

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
void GetCurvPeakAJ(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                   const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                   const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
                   double CurvStruct_theta, double CurvStruct_pitch,
                   const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index,
                   double CurvStruct_a_param, double CurvStruct_b_param, double A[3], double J[3]);

}

#endif
//
// File trailer for GetCurvPeakAJ.h
//
// [EOF]
//
