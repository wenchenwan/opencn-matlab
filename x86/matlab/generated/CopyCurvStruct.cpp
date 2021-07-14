//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CopyCurvStruct.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "CopyCurvStruct.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"

// Function Definitions
//
// Arguments    : const CurvStruct *Curv
//                CurvStruct *Copy
// Return Type  : void
//
namespace ocn {
void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy)
{
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    *Copy = *Curv;
}

} // namespace ocn

//
// File trailer for CopyCurvStruct.cpp
//
// [EOF]
//
