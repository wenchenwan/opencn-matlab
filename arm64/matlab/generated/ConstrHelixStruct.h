//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStruct.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

#ifndef CONSTRHELIXSTRUCT_H
#define CONSTRHELIXSTRUCT_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ConstrHelixStruct(const double P0[3], const double P1[3], const double Cprim[3],
                              double delta, const double evec[3], double theta, double pitch,
                              double FeedRate, ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrHelixStruct.h
//
// [EOF]
//
