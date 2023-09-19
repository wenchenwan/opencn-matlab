//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

#ifndef RESAMPLESTATECLASS_H
#define RESAMPLESTATECLASS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
class ResampleStateClass {
  public:
    ResampleStateClass();
    ~ResampleStateClass();
    double u;
    double ud;
    double udd;
    double uddd;
    double dt;
    bool go_next;
    bool isOutsideRange;
    bool isAStop;
    int stopCounter;
    int zeroStopTime;
};

} // namespace ocn

#endif
//
// File trailer for ResampleStateClass.h
//
// [EOF]
//
