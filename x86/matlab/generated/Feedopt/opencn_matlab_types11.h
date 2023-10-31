
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types11.h
//
// MATLAB Coder version            : 5.4
//

#ifndef OPENCN_MATLAB_TYPES11_H
#define OPENCN_MATLAB_TYPES11_H

// Include Files
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct Tool {
    int toolno;
    int pocketno;
    Axes offset;
    double diameter;
    double frontangle;
    double backangle;
    int orientation;
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
// File trailer for opencn_matlab_types11.h
//
// [EOF]
//
