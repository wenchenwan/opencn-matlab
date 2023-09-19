//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleState.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "ResampleState.h"
#include "ResampleStateClass.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include <cmath>

// Function Definitions
//
// function state = ResampleState(dt, zeroStopTime)
//
// Arguments    : double dt
//                double zeroStopTime
//                ResampleStateClass *state
// Return Type  : void
//
namespace ocn {
void ResampleState(double dt, double zeroStopTime, ResampleStateClass *state)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ResampleState:2' coder.inline("never");
    // 'ResampleState:3' state = ResampleStateClass(dt, zeroStopTime);
    state->dt = dt;
    // 'ResampleStateClass:17' this.dt             = dt;
    // 'ResampleStateClass:7' double
    // 'ResampleStateClass:7' dt
    // 'ResampleStateClass:18' this.zeroStopTime   = zeroStopTime;
    // 'ResampleStateClass:12' int32
    state->zeroStopTime = static_cast<int>(std::round(zeroStopTime));
    // 'ResampleStateClass:12' zeroStopTime
    //  Reset the parameters to default values
    // 'ResampleStateClass:20' this.u              = 0;
    // 'ResampleStateClass:3' double
    // 'ResampleStateClass:3' u
    state->u = 0.0;
    // 'ResampleStateClass:21' this.ud             = 0;
    // 'ResampleStateClass:4' double
    // 'ResampleStateClass:4' ud
    state->ud = 0.0;
    // 'ResampleStateClass:22' this.udd            = 0;
    // 'ResampleStateClass:5' double
    // 'ResampleStateClass:5' udd
    state->udd = 0.0;
    // 'ResampleStateClass:23' this.uddd           = 0;
    // 'ResampleStateClass:6' double
    // 'ResampleStateClass:6' uddd
    state->uddd = 0.0;
    // 'ResampleStateClass:24' this.go_next        = false;
    state->go_next = false;
    // 'ResampleStateClass:25' this.isOutsideRange = false;
    state->isOutsideRange = false;
    // 'ResampleStateClass:26' this.isAStop        = false;
    state->isAStop = false;
    // 'ResampleStateClass:27' this.stopCounter    = 0;
    // 'ResampleStateClass:11' int32
    // 'ResampleStateClass:11' stopCounter
    state->stopCounter = 0;
}

} // namespace ocn

//
// File trailer for ResampleState.cpp
//
// [EOF]
//
