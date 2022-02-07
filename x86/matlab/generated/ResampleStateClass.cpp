//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "ResampleStateClass.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
void ResampleStateClass::set_go_next()
{
    go_next = false;
}

//
// Arguments    : void
// Return Type  : ResampleStateClass
//
ResampleStateClass::ResampleStateClass()
{
}

//
// Arguments    : void
// Return Type  : void
//
ResampleStateClass::~ResampleStateClass()
{
}

//
// Arguments    : void
// Return Type  : void
//
void ResampleStateClass::b_set_go_next()
{
    go_next = true;
}

//
// Arguments    : double b_dt
// Return Type  : void
//
void ResampleStateClass::init(double b_dt)
{
    set_u();
    set_go_next();
    set_dt(b_dt);
}

//
// Arguments    : double val
// Return Type  : void
//
void ResampleStateClass::set_dt(double val)
{
    dt = val;
}

//
// Arguments    : double val
// Return Type  : void
//
void ResampleStateClass::set_u(double val)
{
    u = val;
}

//
// Arguments    : void
// Return Type  : void
//
void ResampleStateClass::set_u()
{
    u = 0.0;
}

} // namespace ocn

//
// File trailer for ResampleStateClass.cpp
//
// [EOF]
//
