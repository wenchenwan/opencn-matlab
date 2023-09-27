//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_internal_types.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

#ifndef OPENCN_MATLAB_INTERNAL_TYPES_H
#define OPENCN_MATLAB_INTERNAL_TYPES_H

// Include Files
#include "Kinematics.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
enum TransitionResult : int
{
    TransitionResult_Ok = 0, // Default value
    TransitionResult_Collinear,
    TransitionResult_NoSolution
};

struct b_FeedoptContext {
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> BasisValDDD;
    ::coder::array<double, 1U> BasisIntegr;
    BaseSplineStruct Bl;
    ::coder::array<double, 2U> u_vec;
    queue_coder q_spline;
    queue_coder q_gcode;
    queue_coder q_compress;
    queue_coder q_smooth;
    queue_coder q_split;
    queue_coder q_opt;
    Fopt op;
    bool go_next;
    bool try_push_again;
    int n_optimized;
    bool reached_end;
    int k0;
    double v_0;
    double v_1;
    double at_0;
    double at_1;
    b_FeedoptConfig cfg;
    FeedoptPlanError errcode;
    int jmax_increase_count;
    bool zero_start;
    bool zero_end;
    int simplex_calls;
    int forced_stop;
    int programmed_stop;
    ::coder::array<double, 2U> Coeff;
    int Skipped;
    Kinematics kin;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_internal_types.h
//
// [EOF]
//
