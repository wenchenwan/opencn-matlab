//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrTransP5Struct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

#ifndef CONSTRTRANSP5STRUCT_H
#define CONSTRTRANSP5STRUCT_H

// Include Files
#include "rtwtypes.h"
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
void ConstrTransP5Struct(const double CoeffP5[6][3], double FeedRate, CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrTransP5Struct.h
//
// [EOF]
//
