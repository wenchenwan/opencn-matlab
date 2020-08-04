//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ReadGCode_mex.h
//
//  Code generation for function 'ReadGCode_mex'
//


#pragma once

// Include files
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "ReadGCode_mex_types.h"

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
namespace ocn
{
  CODEGEN_EXPORT_SYM void ConstrCurvStructType(CurvStruct *C);
  void ConstrCurvStructType_api(int32_T nlhs, const mxArray *plhs[1]);
  CODEGEN_EXPORT_SYM void ConstrHelixStruct(const real_T P0[3], const real_T P1
    [3], const real_T evec[3], real_T theta, real_T pitch, real_T FeedRate,
    ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);
  CODEGEN_EXPORT_SYM void ConstrHelixStructFromArcFeed(real_T p0x, real_T p0y,
    real_T p0z, real_T p1x, real_T p1y, real_T p1z, real_T cx, real_T cy, real_T
    cz, real_T rotation, const real_T evec[3], CurvStruct *b_CurvStruct);
  void ConstrHelixStructFromArcFeed_api(const mxArray * const prhs[11], int32_T
    nlhs, const mxArray *plhs[1]);
  void ConstrHelixStruct_api(const mxArray * const prhs[7], int32_T nlhs, const
    mxArray *plhs[1]);
  CODEGEN_EXPORT_SYM void ConstrLineStruct(const real_T P0[3], const real_T P1[3],
    real_T FeedRate, ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);
  void ConstrLineStruct_api(const mxArray * const prhs[4], int32_T nlhs, const
    mxArray *plhs[1]);
  CODEGEN_EXPORT_SYM void CopyCurvStruct(const CurvStruct *Curv, CurvStruct
    *Copy);
  void CopyCurvStruct_api(const mxArray * const prhs[1], int32_T nlhs, const
    mxArray *plhs[1]);
  CODEGEN_EXPORT_SYM void ReadGCode(ReadGCodeCmd cmd, const char_T
    filename_data[], const int32_T filename_size[2], int32_T *status, CurvStruct
    *b_CurvStruct);
  void ReadGCode_api(const mxArray * const prhs[2], int32_T nlhs, const mxArray *
                     plhs[2]);
}

CODEGEN_EXPORT_SYM void ReadGCode_mex_atexit();
namespace ocn
{
  CODEGEN_EXPORT_SYM void ReadGCode_mex_initialize();
  CODEGEN_EXPORT_SYM void ReadGCode_mex_terminate();
}

// End of code generation (ReadGCode_mex.h)
