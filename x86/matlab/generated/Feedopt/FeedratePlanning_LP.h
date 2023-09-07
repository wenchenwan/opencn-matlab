//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedratePlanning_LP.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:21:23
//

#ifndef FEEDRATEPLANNING_LP_H
#define FEEDRATEPLANNING_LP_H

// Include Files
#include "opencn_matlab_types1.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct b_FeedoptContext;

}

// Function Declarations
namespace ocn {
void FeedratePlanning_LP(b_FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U> &window,
                         const double amax[6], const double jmax[6],
                         const ::coder::array<double, 2U> &BasisVal,
                         const ::coder::array<double, 2U> &BasisValD,
                         const ::coder::array<double, 2U> &BasisValDD,
                         const ::coder::array<double, 1U> &BasisIntegr,
                         const ::coder::array<double, 2U> &u_vec, double NWindow,
                         ::coder::array<double, 2U> &Coeff, bool *success, int *status);

}

#endif
//
// File trailer for FeedratePlanning_LP.h
//
// [EOF]
//
