//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_rtwutil.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef SINSPACE_RTWUTIL_H
#define SINSPACE_RTWUTIL_H

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

extern void sLong2MultiWord(int u, unsigned int y[]);

extern double uMultiWord2Double(const unsigned int u1[]);

extern int uMultiWordCmp(const unsigned int u1[], const unsigned int u2[]);

extern bool uMultiWordGe(const unsigned int u1[], const unsigned int u2[]);

extern void uMultiWordShl(const unsigned int u1[], unsigned int n2, unsigned int y[]);

} // namespace ocn

#endif
//
// File trailer for sinspace_rtwutil.h
//
// [EOF]
//
