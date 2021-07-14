//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, const double P0[3], const double P1[3],
                      const double Cprim[3], double delta, const double evec[3], double theta,
                      double pitch, const double CoeffP5[6][3], double FeedRate,
                      CurvStruct *CStrct);

}

#endif
//
// File trailer for ConstrCurvStruct.h
//
// [EOF]
//
