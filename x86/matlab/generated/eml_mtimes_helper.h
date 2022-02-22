//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_mtimes_helper.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
//

#ifndef EML_MTIMES_HELPER_H
#define EML_MTIMES_HELPER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &r1, const ::coder::array<double, 2U> &r1D,
                        double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                        const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                        double e_a, double f_a);

void binary_expand_op(::coder::array<double, 2U> &Aeq, int i16, int i17, const double t_1[3],
                      double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a);

void binary_expand_op(::coder::array<double, 2U> &r, const double t_1[3], double a,
                      const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a);

void binary_expand_op(::coder::array<double, 2U> &r1, const ::coder::array<double, 2U> &r1D,
                      double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a);

} // namespace ocn

#endif
//
// File trailer for eml_mtimes_helper.h
//
// [EOF]
//
