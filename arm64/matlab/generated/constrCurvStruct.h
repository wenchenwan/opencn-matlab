//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:06
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

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
void b_constrCurvStruct(CurvStruct *CStrct);

void b_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                        const ::coder::array<double, 1U> &R1, const double Cprim[3], double delta,
                        const double evec[3], double theta, double pitch, CurvStruct *CStrct);

void b_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                        const ::coder::array<double, 1U> &R1,
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct);

extern void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct,
                             const ::coder::array<double, 1U> &R0,
                             const ::coder::array<double, 1U> &R1, const double Cprim[3],
                             double delta, const double evec[3], double theta, double pitch,
                             const ::coder::array<double, 2U> &CoeffP5,
                             const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct);

} // namespace ocn

#endif
//
// File trailer for constrCurvStruct.h
//
// [EOF]
//
