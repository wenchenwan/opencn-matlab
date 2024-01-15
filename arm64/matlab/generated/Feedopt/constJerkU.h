
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constJerkU.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CONSTJERKU_H
#define CONSTJERKU_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_constJerkU(double pseudoJerk, ::coder::array<double, 2U> &k_vec,
                  ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &ud,
                  ::coder::array<double, 2U> &udd, ::coder::array<double, 2U> &uddd);

void constJerkU(double pseudoJerk, ::coder::array<double, 2U> &k_vec, ::coder::array<double, 2U> &u,
                ::coder::array<double, 2U> &ud, ::coder::array<double, 2U> &udd);

void constJerkU(double pseudoJerk, const ::coder::array<double, 2U> &k_vec,
                ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &ud,
                ::coder::array<double, 2U> &udd, ::coder::array<double, 2U> &uddd);

} // namespace ocn

#endif
//
// File trailer for constJerkU.h
//
// [EOF]
//
