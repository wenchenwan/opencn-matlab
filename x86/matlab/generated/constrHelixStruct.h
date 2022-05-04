//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 13:16:18
//

#ifndef CONSTRHELIXSTRUCT_H
#define CONSTRHELIXSTRUCT_H

// Include Files
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct, const double R0[6],
                              const double R1[6], const double Cprim[3], double delta,
                              const double evec[3], double theta, double pitch, CurvStruct *CStrct);

}

#endif
//
// File trailer for constrHelixStruct.h
//
// [EOF]
//
