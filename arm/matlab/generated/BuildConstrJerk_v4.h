//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstrJerk_v4.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef BUILDCONSTRJERK_V4_H
#define BUILDCONSTRJERK_V4_H

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

namespace coder {
class sparse;

}
} // namespace ocn

// Function Declarations
namespace ocn {
void BuildConstrJerk_v4(const queue_coder *ctx_q_splines,
                        const ::coder::array<CurvStruct, 2U> &CurvStructs,
                        const ::coder::array<double, 2U> &Coeff, const double jmax[3],
                        const ::coder::array<double, 2U> &BasisVal,
                        const ::coder::array<double, 2U> &BasisValD,
                        const ::coder::array<double, 2U> &BasisValDD,
                        const ::coder::array<double, 2U> &u_vec, coder::sparse *A,
                        ::coder::array<double, 1U> &b);

}

#endif
//
// File trailer for BuildConstrJerk_v4.h
//
// [EOF]
//
