//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef CONSTRLINESTRUCT_H
#define CONSTRLINESTRUCT_H

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
extern void ConstrLineStruct(bool trafo, bool HSC, const double Poff[3], const double Aoff[3],
                             const double Uoff[3], double Doff, const double P0[3],
                             const double P1[3], const double A0[3], const double A1[3],
                             const double U0[3], const double U1[3], double FeedRate,
                             ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrLineStruct.h
//
// [EOF]
//
