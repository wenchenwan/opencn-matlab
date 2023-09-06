//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
//

#ifndef REPMAT_H
#define REPMAT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
namespace coder {
void repmat(const ::coder::array<double, 1U> &a, int varargin_2, ::coder::array<double, 2U> &b);

void repmat(const ::coder::array<double, 2U> &a, double varargin_1, double varargin_2,
            ::coder::array<double, 2U> &b);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for repmat.h
//
// [EOF]
//
