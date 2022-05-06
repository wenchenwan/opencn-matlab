//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrBaseSpline.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-May-2022 09:00:02
//

#ifndef CONSTRBASESPLINE_H
#define CONSTRBASESPLINE_H

// Include Files
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrBaseSpline(int ncoeff, const ::coder::array<double, 2U> &breakpoints,
                             unsigned long handle, int order, BaseSplineStruct *BaseSplineStrct);

}

#endif
//
// File trailer for constrBaseSpline.h
//
// [EOF]
//
