//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleState.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "ResampleState.h"
#include "ResampleStateClass.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"

// Function Definitions
//
// Arguments    : double dt
//                ResampleStateClass *state
// Return Type  : void
//
namespace ocn {
void ResampleState(double dt, ResampleStateClass *state)
{
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    state->init(dt);
}

} // namespace ocn

//
// File trailer for ResampleState.cpp
//
// [EOF]
//
