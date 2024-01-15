
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CopyCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "CopyCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types111.h"

// Function Definitions
//
// function [ copy ] = CopyCurvStruct( curve )
//
// CopyCurvStruct : Copy the curve structure
//
//  Inputs :
//  Curv  : The curve to copy
//
//  Outputs :
//  Copy  : The copy of the curve
//
//
// Arguments    : const CurvStruct *curve
//                CurvStruct *copy
// Return Type  : void
//
namespace ocn {
void CopyCurvStruct(const CurvStruct *curve, CurvStruct *copy)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'CopyCurvStruct:11' copy = curve;
    *copy = *curve;
}

} // namespace ocn

//
// File trailer for CopyCurvStruct.cpp
//
// [EOF]
//
