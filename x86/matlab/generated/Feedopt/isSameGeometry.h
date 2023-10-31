
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isSameGeometry.h
//
// MATLAB Coder version            : 5.4
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
void b_binary_expand_op(::coder::array<bool, 2U> &in1, const CurvStruct *in2,
                        const CurvStruct *in3);

void c_binary_expand_op(::coder::array<bool, 1U> &in1, const CurvStruct *in2,
                        const CurvStruct *in3);

void d_binary_expand_op(::coder::array<bool, 1U> &in1, const CurvStruct *in2,
                        const CurvStruct *in3);

} // namespace ocn

#endif
//
// File trailer for isSameGeometry.h
//
// [EOF]
//
