//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct_types2.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

#ifndef EVALCURVSTRUCT_TYPES2_H
#define EVALCURVSTRUCT_TYPES2_H

// Include Files
#include "EvalCurvStruct_types3.h"
#include "rtwtypes.h"
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
    double Ltot;
    ::coder::array<double, 2U> Lk;
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
// File trailer for EvalCurvStruct_types2.h
//
// [EOF]
//
