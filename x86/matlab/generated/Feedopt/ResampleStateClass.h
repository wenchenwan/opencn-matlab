//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
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
    bool go_next;
    double dt;
    bool isOutsideRange;
};

} // namespace ocn

#endif
//
// File trailer for ResampleStateClass.h
//
// [EOF]
//
