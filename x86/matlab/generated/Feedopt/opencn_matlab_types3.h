//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types3.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 30-Jun-2022 11:29:54
//

#ifndef OPENCN_MATLAB_TYPES3_H
#define OPENCN_MATLAB_TYPES3_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct BaseSplineStruct {
    int ncoeff;
    ::coder::array<double, 2U> breakpoints;
    unsigned long handle;
    int order;
};

enum CurveType : int
{
    CurveType_None = 0, // Default value
    CurveType_Line,
    CurveType_Helix,
    CurveType_Spline,
    CurveType_TransP5
};

enum ZSpdMode : int
{
    ZSpdMode_NN = 0, // Default value
    ZSpdMode_ZN,
    ZSpdMode_NZ,
    ZSpdMode_ZZ
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types3.h
//
// [EOF]
//
