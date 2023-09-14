//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isSameGeometry.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

#ifndef ISSAMEGEOMETRY_H
#define ISSAMEGEOMETRY_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void d_binary_expand_op(::coder::array<bool, 2U> &in1, const CurvStruct *in2,
                        const CurvStruct *in3);

}

#endif
//
// File trailer for isSameGeometry.h
//
// [EOF]
//
