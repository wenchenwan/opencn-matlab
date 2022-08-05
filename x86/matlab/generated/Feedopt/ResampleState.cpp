//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleState.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "ResampleState.h"
#include "ResampleStateClass.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"

// Function Definitions
//
// function state = ResampleState(dt)
//
// Arguments    : double dt
//                ResampleStateClass *state
// Return Type  : void
//
namespace ocn {
void ResampleState(double dt, ResampleStateClass *state)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ResampleState:2' coder.inline("never");
    // 'ResampleState:3' state = ResampleStateClass(dt);
    state->dt = dt;
    // 'ResampleStateClass:13' this.u              = 0;
    state->u = 0.0;
    // 'ResampleStateClass:14' this.ud             = 0;
    state->ud = 0.0;
    // 'ResampleStateClass:15' this.udd            = 0;
    state->udd = 0.0;
    // 'ResampleStateClass:16' this.go_next        = false;
    state->go_next = false;
    // 'ResampleStateClass:17' this.isOutsideRange = false;
    state->isOutsideRange = false;
    // 'ResampleStateClass:18' this.dt             = dt;
    // 'ResampleStateClass:7' double
    // 'ResampleStateClass:7' dt
}

} // namespace ocn

//
// File trailer for ResampleState.cpp
//
// [EOF]
//
