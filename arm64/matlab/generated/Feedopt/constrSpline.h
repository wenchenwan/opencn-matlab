//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSpline.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:58:50
//

#ifndef CONSTRSPLINE_H
#define CONSTRSPLINE_H

// Include Files
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrSpline(const ::coder::array<double, 2U> &coeff,
                         const ::coder::array<double, 2U> &knots, const BaseSplineStruct *BlStruct,
                         SplineStruct *SplineStrct);

}

#endif
//
// File trailer for constrSpline.h
//
// [EOF]
//
