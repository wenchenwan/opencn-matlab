//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:06
//

#ifndef CONSTRHELIXSTRUCT_H
#define CONSTRHELIXSTRUCT_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct,
                              const ::coder::array<double, 1U> &R0,
                              const ::coder::array<double, 1U> &R1, const double Cprim[3],
                              double delta, const double evec[3], double theta, double pitch,
                              CurvStruct *CStrct);

}

#endif
//
// File trailer for constrHelixStruct.h
//
// [EOF]
//
