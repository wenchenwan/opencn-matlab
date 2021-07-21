//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EnableDebugLog.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "EnableDebugLog.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"

// Function Definitions
//
// Arguments    : DebugCfg cfg
// Return Type  : void
//
namespace ocn {
void EnableDebugLog(DebugCfg cfg)
{
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    DebugConfig = static_cast<double>(static_cast<unsigned long>(DebugConfig) |
                                      1UL << (static_cast<int>(cfg) - 1));
}

} // namespace ocn

//
// File trailer for EnableDebugLog.cpp
//
// [EOF]
//
