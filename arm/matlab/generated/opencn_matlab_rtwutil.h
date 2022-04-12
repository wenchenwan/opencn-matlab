//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_rtwutil.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:49:22
//

#ifndef OPENCN_MATLAB_RTWUTIL_H
#define OPENCN_MATLAB_RTWUTIL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void Double2MultiWord(double u1, unsigned int y[]);

extern void MultiWordAdd(const unsigned int u1[], const unsigned int u2[], unsigned int y[]);

extern void MultiWordAnd(const unsigned int u1[], const unsigned int u2[], unsigned int y[]);

extern void MultiWordSub(const unsigned int u1[], const unsigned int u2[], unsigned int y[]);

extern void sLong2MultiWord(int u, unsigned int y[]);

extern int uMultiWordCmp(const unsigned int u1[], const unsigned int u2[]);

extern bool uMultiWordGe(const unsigned int u1[], const unsigned int u2[]);

extern bool uMultiWordNe(const unsigned int u1[], const unsigned int u2[]);

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_rtwutil.h
//
// [EOF]
//
