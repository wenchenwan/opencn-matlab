//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types2.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

#ifndef OPENCN_MATLAB_TYPES2_H
#define OPENCN_MATLAB_TYPES2_H

// Include Files
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct SplineStruct {
    BaseSplineStruct Bl;
    ::coder::array<double, 2U> coeff;
    ::coder::array<double, 2U> knots;
    double Ltot;
    ::coder::array<double, 2U> Lk;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types2.h
//
// [EOF]
//
