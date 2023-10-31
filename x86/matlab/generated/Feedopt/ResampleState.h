
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleState.h
//
// MATLAB Coder version            : 5.4
//

#ifndef RESAMPLESTATE_H
#define RESAMPLESTATE_H

// Include Files
#include "ResampleStateClass.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ResampleState(double dt, double zeroStopTime, ResampleStateClass *b_state);

}

#endif
//
// File trailer for ResampleState.h
//
// [EOF]
//
