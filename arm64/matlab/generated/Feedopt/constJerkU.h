//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constJerkU.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

#ifndef CONSTJERKU_H
#define CONSTJERKU_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void constJerkU(double pseudoJerk, double k_vec, bool isEnd, double *u, double *ud, double *udd,
                double *uddd);

}

#endif
//
// File trailer for constJerkU.h
//
// [EOF]
//
