//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

#ifndef CONSTRLINESTRUCT_H
#define CONSTRLINESTRUCT_H

// Include Files
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0[6],
                             const double R1[6], CurvStruct *CStrct);

}

#endif
//
// File trailer for constrLineStruct.h
//
// [EOF]
//
