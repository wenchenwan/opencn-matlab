//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CopyCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

// Include Files
#include "CopyCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"

// Function Definitions
//
// function Copy = CopyCurvStruct( Curv )
//
// Arguments    : const CurvStruct *Curv
//                CurvStruct *Copy
// Return Type  : void
//
namespace ocn {
void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'CopyCurvStruct:2' Copy = Curv;
    *Copy = *Curv;
}

} // namespace ocn

//
// File trailer for CopyCurvStruct.cpp
//
// [EOF]
//
