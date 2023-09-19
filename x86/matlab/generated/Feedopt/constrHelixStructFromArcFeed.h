//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStructFromArcFeed.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

#ifndef CONSTRHELIXSTRUCTFROMARCFEED_H
#define CONSTRHELIXSTRUCTFROMARCFEED_H

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
extern void constrHelixStructFromArcFeed(const GcodeInfoStruct *gcodeInfoStruct, const Tool *tool,
                                         const double P0[3], const double P1[3], const double C[3],
                                         const double A0[3], const double A1[3], double rotation,
                                         const double evec[3], CurvStruct *CStrct);

}

#endif
//
// File trailer for constrHelixStructFromArcFeed.h
//
// [EOF]
//
