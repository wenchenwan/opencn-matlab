//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types21.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

#ifndef OPENCN_MATLAB_TYPES21_H
#define OPENCN_MATLAB_TYPES21_H

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

struct GcodeInfoStruct {
    CurveType Type;
    ZSpdMode zspdmode;
    bool TRAFO;
    bool HSC;
    double FeedRate;
    double SpindleSpeed;
    int gcode_source_line;
    bool G91;
    bool G91_1;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types21.h
//
// [EOF]
//
