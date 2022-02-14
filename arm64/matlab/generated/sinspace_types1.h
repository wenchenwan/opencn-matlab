//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_types1.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

#ifndef SINSPACE_TYPES1_H
#define SINSPACE_TYPES1_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct CurvStruct {
    CurveType Type;
    ZSpdMode zspdmode;
    double P0[3];
    double P1[3];
    double CorrectedHelixCenter[3];
    double delta;
    double evec[3];
    double theta;
    double pitch;
    double CoeffP5[6][3];
    int sp_index;
    double FeedRate;
    double SpindleSpeed;
    double MaxConstantFeedRate;
    int i_begin_sp;
    int i_end_sp;
    int gcode_source_line;
    int index_smooth;
    bool UseConstJerk;
    double ConstJerk;
    int ConstJerkMaxIterations;
    ::coder::array<double, 1U> Coeff;
    double a_param;
    double b_param;
    SplineStruct sp;
};

} // namespace ocn

#endif
//
// File trailer for sinspace_types1.h
//
// [EOF]
//
