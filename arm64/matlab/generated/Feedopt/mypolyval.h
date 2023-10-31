
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.h
//
// MATLAB Coder version            : 5.4
//

#ifndef MYPOLYVAL_H
#define MYPOLYVAL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3);

void e_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3);

void mypolyval(const ::coder::array<double, 2U> &p, const ::coder::array<double, 1U> &x,
               ::coder::array<double, 2U> &y);

void mypolyval(const ::coder::array<double, 2U> &p, const double x[2],
               ::coder::array<double, 2U> &y);

void mypolyval(const ::coder::array<double, 2U> &p, double x, ::coder::array<double, 1U> &y);

} // namespace ocn

#endif
//
// File trailer for mypolyval.h
//
// [EOF]
//
