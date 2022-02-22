//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleState.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "ResampleState.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_initialize.h"
#include "ResampleStateClass.h"

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
    if (!isInitialized_EvalCurvStruct) {
        EvalCurvStruct_initialize();
    }
    // 'ResampleState:2' coder.inline("never");
    // 'ResampleState:3' state = ResampleStateClass(dt);
    state->dt = dt;
    // 'ResampleStateClass:10' this.u = 0;
    state->u = 0.0;
    // 'ResampleStateClass:11' this.go_next = false;
    state->go_next = false;
    // 'ResampleStateClass:12' this.dt = dt;
    // 'ResampleStateClass:5' double
    // 'ResampleStateClass:5' dt
}

} // namespace ocn

//
// File trailer for ResampleState.cpp
//
// [EOF]
//
