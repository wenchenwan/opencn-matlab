//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleStateClass.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
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
    this->go_next = false;
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
    this->go_next = true;
}

//
// Arguments    : double b_dt
// Return Type  : void
//
void ResampleStateClass::init(double b_dt)
{
    this->set_u();
    this->set_go_next();
    this->set_dt(b_dt);
}

//
// Arguments    : double val
// Return Type  : void
//
void ResampleStateClass::set_dt(double val)
{
    this->dt = val;
}

//
// Arguments    : double val
// Return Type  : void
//
void ResampleStateClass::set_u(double val)
{
    this->u = val;
}

//
// Arguments    : void
// Return Type  : void
//
void ResampleStateClass::set_u()
{
    this->u = 0.0;
}

} // namespace ocn

//
// File trailer for ResampleStateClass.cpp
//
// [EOF]
//
