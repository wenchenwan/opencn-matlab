//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: div.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

#ifndef DIV_H
#define DIV_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                        const ::coder::array<double, 1U> &in3,
                        const ::coder::array<double, 1U> &in4, const double in5_data[],
                        const int *in5_size);

void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                      const double in3_data[], const int *in3_size, const double in4_data[],
                      const int *in4_size, const double in5_data[], const int *in5_size,
                      const double in6_data[], const int *in6_size, const double in7_data[],
                      const int *in7_size, const ::coder::array<double, 1U> &in8,
                      const ::coder::array<double, 1U> &in9,
                      const ::coder::array<double, 1U> &in10);

void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                      const ::coder::array<double, 1U> &in3, const ::coder::array<double, 1U> &in4,
                      const double in5_data[], const int *in5_size);

} // namespace ocn

#endif
//
// File trailer for div.h
//
// [EOF]
//
