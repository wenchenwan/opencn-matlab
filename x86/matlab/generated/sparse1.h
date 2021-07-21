//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef SPARSE1_H
#define SPARSE1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
namespace coder {
class sparse {
  public:
    void parenAssign(const ::coder::array<double, 2U> &rhs,
                     const ::coder::array<double, 2U> &varargin_1,
                     const ::coder::array<double, 2U> &varargin_2);
    ::coder::array<double, 1U> d;
    ::coder::array<int, 1U> colidx;
    ::coder::array<int, 1U> rowidx;
    int m;
    int n;
    int maxnz;
};

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for sparse1.h
//
// [EOF]
//
