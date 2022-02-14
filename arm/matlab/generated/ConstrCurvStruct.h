//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types2.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

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
