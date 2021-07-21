//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

#ifndef QUEUE_CODER_H
#define QUEUE_CODER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct SplineBase {
    int ncoeff;
    ::coder::array<double, 2U> breakpoints;
    unsigned long handle;
    int degree;
};

struct SplineStruct {
    ::coder::array<double, 2U> CoeffX;
    ::coder::array<double, 2U> CoeffY;
    ::coder::array<double, 2U> CoeffZ;
    SplineBase Bl;
    ::coder::array<double, 2U> knots;
};

enum ZSpdMode
{
    ZSpdMode_NN = 0, // Default value
    ZSpdMode_ZN,
    ZSpdMode_NZ,
    ZSpdMode_ZZ
};

enum CurveType
{
    CurveType_None = 0, // Default value
    CurveType_Line,
    CurveType_Helix,
    CurveType_Spline,
    CurveType_TransP5
};

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

class queue_coder {
  public:
    void init(const CurvStruct *b_value_type);
    void push(const CurvStruct *value) const;
    void get(int b_index, CurvStruct *value) const;
    bool isempty() const;
    unsigned int size() const;
    void rget(CurvStruct *value) const;
    void get(unsigned int b_index, CurvStruct *value) const;
    void set(unsigned int b_index, const CurvStruct *value) const;
    void get(double b_index, CurvStruct *value) const;
    void get(long b_index, CurvStruct *value) const;
    void get(unsigned long b_index, CurvStruct *value) const;
    queue_coder();
    ~queue_coder();
    unsigned long ptr;
    CurvStruct value_type;
};

} // namespace ocn

#endif
//
// File trailer for queue_coder.h
//
// [EOF]
//
