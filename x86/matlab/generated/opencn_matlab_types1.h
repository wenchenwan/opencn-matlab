//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types1.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

#ifndef OPENCN_MATLAB_TYPES1_H
#define OPENCN_MATLAB_TYPES1_H

// Include Files
#include "opencn_matlab_types2.h"
#include "rtwtypes.h"
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
    bool TRAFO;
    bool HSC;
    double Poff[3];
    double Aoff[3];
    double Uoff[3];
    double Doff;
    double P0[3];
    double P1[3];
    double A0[3];
    double A1[3];
    double U0[3];
    double U1[3];
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
// File trailer for opencn_matlab_types1.h
//
// [EOF]
//
