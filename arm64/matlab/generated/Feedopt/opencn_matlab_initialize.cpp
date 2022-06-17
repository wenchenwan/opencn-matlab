//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_initialize.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "opencn_matlab_initialize.h"
#include "EvalCurvStruct.h"
#include "feedratePlanning.h"
#include "opencn_matlab_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
void opencn_matlab_initialize()
{
    DebugConfig = 0.0;
    sin_calls = 0.0;
    cos_calls = 0.0;
    sqrt_calls = 0.0;
    EvalCurvStruct_init();
    feedratePlanning_init();
    isInitialized_opencn_matlab = true;
}

} // namespace ocn

//
// File trailer for opencn_matlab_initialize.cpp
//
// [EOF]
//
