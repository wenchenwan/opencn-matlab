//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
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
    void init(double b_dt);
    void set_u();
    void set_go_next();
    void set_dt(double val);
    void set_u(double val);
    void b_set_go_next();
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
