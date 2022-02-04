//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_initialize.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "sinspace_initialize.h"
#include "sinspace_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
void sinspace_initialize()
{
    DebugConfig = 0.0;
    sin_calls = 0.0;
    cos_calls = 0.0;
    sqrt_calls = 0.0;
    isInitialized_sinspace = true;
}

} // namespace ocn

//
// File trailer for sinspace_initialize.cpp
//
// [EOF]
//
