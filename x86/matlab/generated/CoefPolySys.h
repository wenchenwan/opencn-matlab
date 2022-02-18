//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CoefPolySys.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

#ifndef COEFPOLYSYS_H
#define COEFPOLYSYS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void CoefPolySys(const double in1[3], const double in2[3], const double in3[3], double kappa0,
                 const double in5[3], const double in6[3], const double in7[3], double kappa1,
                 double CoefPS[16]);

}

#endif
//
// File trailer for CoefPolySys.h
//
// [EOF]
//
