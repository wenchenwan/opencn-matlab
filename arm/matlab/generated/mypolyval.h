//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
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
void b_mypolyval(const double p[6][3], double y[3]);

void b_mypolyval(const double p[5][3], const double x[10], double y[10][3]);

void b_mypolyval(const double p[5][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y);

void b_mypolyval(const double p[5][3], double x, double y[3]);

void c_mypolyval(const double p[4][3], const double x[10], double y[10][3]);

void c_mypolyval(const double p[4][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y);

void c_mypolyval(const double p[4][3], double x, double y[3]);

void d_mypolyval(const double p[3][3], const double x[10], double y[10][3]);

void d_mypolyval(const double p[3][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y);

void d_mypolyval(const double p[3][3], double x, double y[3]);

void mypolyval(const double p[6][3], const double x[10], double y[10][3]);

void mypolyval(const double p[5][3], double y[9][3]);

void mypolyval(const double p[6][3], const ::coder::array<double, 2U> &x,
               ::coder::array<double, 2U> &y);

void mypolyval(const double p[6][3], double x, double y[3]);

} // namespace ocn

#endif
//
// File trailer for mypolyval.h
//
// [EOF]
//
