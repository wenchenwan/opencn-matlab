//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:27
//

#ifndef CONSTRTRANSP5STRUCT_H
#define CONSTRTRANSP5STRUCT_H

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
extern void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct,
                                const ::coder::array<double, 1U> &R0,
                                const ::coder::array<double, 1U> &R1,
                                const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct);

}

#endif
//
// File trailer for constrTransP5Struct.h
//
// [EOF]
//
