//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef CONSTRHELIXSTRUCTFROMARCFEED_H
#define CONSTRHELIXSTRUCTFROMARCFEED_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ConstrHelixStructFromArcFeed(double p0x, double p0y, double p0z, double p1x, double p1y,
                                         double p1z, double cx, double cy, double cz,
                                         double rotation, const double evec[3],
                                         CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ConstrHelixStructFromArcFeed.h
//
// [EOF]
//
