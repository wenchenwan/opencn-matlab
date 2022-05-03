//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:10
//

#ifndef OPENCN_MATLAB_TYPES_H
#define OPENCN_MATLAB_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"

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

struct SplineStruct {
    BaseSplineStruct Bl;
    ::coder::array<double, 2U> coeff;
    ::coder::array<double, 2U> knots;
    double Ltot;
    ::coder::array<double, 2U> Lk;
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

struct GcodeInfoStruct {
    CurveType Type;
    ZSpdMode zspdmode;
    bool TRAFO;
    bool HSC;
    bool FeedRate;
    bool SpindleSpeed;
    double gcode_source_line;
    double G91;
    unsigned long G91_1;
};

struct CurvStruct {
    GcodeInfoStruct Info;
    ::coder::array<double, 1U> R0;
    ::coder::array<double, 1U> R1;
    double CorrectedHelixCenter[3];
    double delta;
    double evec[3];
    double theta;
    double pitch;
    ::coder::array<double, 2U> CoeffP5;
    int sp_index;
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
// File trailer for opencn_matlab_types.h
//
// [EOF]
//
