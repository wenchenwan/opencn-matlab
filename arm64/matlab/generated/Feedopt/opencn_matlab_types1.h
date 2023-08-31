//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types1.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:29:48
//

#ifndef OPENCN_MATLAB_TYPES1_H
#define OPENCN_MATLAB_TYPES1_H

// Include Files
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct CurvStruct {
    GcodeInfoStruct Info;
    Tool tool;
    SplineStruct sp;
    double R0[6];
    double R1[6];
    double CorrectedHelixCenter[3];
    double delta;
    double evec[3];
    double theta;
    double pitch;
    ::coder::array<double, 2U> CoeffP5;
    unsigned int sp_index;
    int i_begin_sp;
    int i_end_sp;
    int index_smooth;
    bool UseConstJerk;
    double ConstJerk;
    ::coder::array<double, 1U> Coeff;
    double a_param;
    double b_param;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types1.h
//
// [EOF]
//
