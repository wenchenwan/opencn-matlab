//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
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
    bool go_next;
    double dt;
};

} // namespace ocn

#endif
//
// File trailer for ResampleStateClass.h
//
// [EOF]
//
