//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ReadGCode_mex_types.h
//
//  Code generation for function 'ReadGCode_mex_types'
//


#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
namespace ocn
{
  enum CurveType
  {
    CurveType_None = 0,                // Default value
    CurveType_Line,
    CurveType_Helix,
    CurveType_Spline,
    CurveType_TransP5
  };

  enum ReadGCodeCmd
  {
    ReadGCodeCmd_Load = 1,             // Default value
    ReadGCodeCmd_Read
  };

  enum ZSpdMode
  {
    ZSpdMode_NN = 0,                   // Default value
    ZSpdMode_ZN,
    ZSpdMode_NZ,
    ZSpdMode_ZZ
  };

  struct SplineBase
  {
    int32_T ncoeff;
    coder::array<real_T, 2U> breakpoints;
    uint64_T handle;
    int32_T degree;
  };

  struct SplineStruct
  {
    coder::array<real_T, 2U> CoeffX;
    coder::array<real_T, 2U> CoeffY;
    coder::array<real_T, 2U> CoeffZ;
    SplineBase Bl;
    coder::array<real_T, 2U> knots;
  };

  struct CurvStruct
  {
    CurveType Type;
    ZSpdMode zspdmode;
    real_T P0[3];
    real_T P1[3];
    real_T evec[3];
    real_T theta;
    real_T pitch;
    real_T CoeffP5[6][3];
    int32_T sp_index;
    real_T FeedRate;
    real_T MaxConstantFeedRate;
    int32_T i_begin_sp;
    int32_T i_end_sp;
    int32_T gcode_source_line;
    int32_T index_smooth;
    boolean_T UseConstJerk;
    real_T ConstJerk;
    int32_T ConstJerkMaxIterations;
    coder::array<real_T, 1U> Coeff;
    real_T a_param;
    real_T b_param;
    boolean_T end_flag;
    SplineStruct sp;
  };
}

#ifdef _MSC_VER

#pragma warning(pop)

#endif

// End of code generation (ReadGCode_mex_types.h)
