//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_types2.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef SINSPACE_TYPES2_H
#define SINSPACE_TYPES2_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct SplineStruct {
    ::coder::array<double, 2U> CoeffX;
    ::coder::array<double, 2U> CoeffY;
    ::coder::array<double, 2U> CoeffZ;
    SplineBase Bl;
    ::coder::array<double, 2U> knots;
};

enum ZSpdMode : int
{
    ZSpdMode_NN = 0, // Default value
    ZSpdMode_ZN,
    ZSpdMode_NZ,
    ZSpdMode_ZZ
};

enum CurveType : int
{
    CurveType_None = 0, // Default value
    CurveType_Line,
    CurveType_Helix,
    CurveType_Spline,
    CurveType_TransP5
};

} // namespace ocn

#endif
//
// File trailer for sinspace_types2.h
//
// [EOF]
//
