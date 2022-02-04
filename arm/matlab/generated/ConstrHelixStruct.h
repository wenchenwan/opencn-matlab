//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef CONSTRHELIXSTRUCT_H
#define CONSTRHELIXSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
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
