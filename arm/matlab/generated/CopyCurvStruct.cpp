//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CopyCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CopyCurvStruct.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types1.h"

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
