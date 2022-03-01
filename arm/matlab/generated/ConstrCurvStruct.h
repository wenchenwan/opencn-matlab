//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 10:58:42
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types2.h"
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
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, bool HSC,
                      const double Poff[3], const double Aoff[3], const double Uoff[3], double Doff,
                      const double P0[3], const double P1[3], const double A0[3],
                      const double A1[3], const double U0[3], const double U1[3],
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
