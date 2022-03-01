//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_v4.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:01:39
//

#ifndef FEEDRATEPLANNING_V4_H
#define FEEDRATEPLANNING_V4_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct FeedoptContext;

struct CurvStruct;

} // namespace ocn

// Function Declarations
namespace ocn {
void FeedratePlanning_v4(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &CurvStructs0,
                         const double amax[3], double jmax[3],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle,
                         const ::coder::array<double, 2U> &u_vec, int N_Hor,
                         ::coder::array<double, 2U> &Coeff, int *NCoeff, bool *success);

}

#endif
//
// File trailer for FeedratePlanning_v4.h
//
// [EOF]
//
