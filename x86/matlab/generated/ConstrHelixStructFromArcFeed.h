//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef CONSTRHELIXSTRUCTFROMARCFEED_H
#define CONSTRHELIXSTRUCTFROMARCFEED_H

// Include Files
#include "opencn_matlab_types1.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ConstrHelixStructFromArcFeed(bool trafo, bool HSC, const double Poff[3],
                                         const double Aoff[3], const double Uoff[3], double Doff,
                                         double p0x, double p0y, double p0z, double p1x, double p1y,
                                         double p1z, double cx, double cy, double cz,
                                         const double A0[3], const double A1[3], const double U0[3],
                                         const double U1[3], double rotation, const double evec[3],
                                         CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrHelixStructFromArcFeed.h
//
// [EOF]
//
