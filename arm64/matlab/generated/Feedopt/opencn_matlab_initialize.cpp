
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_initialize.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "opencn_matlab_initialize.h"
#include "EvalCurvStruct.h"
#include "feedratePlanning.h"
#include "opencn_matlab_data.h"
#include "zeroSpeedCurv.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
void opencn_matlab_initialize()
{
    ratio_not_empty_init();
    DebugConfig = 0.0;
    sin_calls = 0.0;
    cos_calls = 0.0;
    EvalCurvStruct_init();
    calc_u_init();
    feedratePlanning_init();
    isInitialized_opencn_matlab = true;
}

} // namespace ocn

//
// File trailer for opencn_matlab_initialize.cpp
//
// [EOF]
//
