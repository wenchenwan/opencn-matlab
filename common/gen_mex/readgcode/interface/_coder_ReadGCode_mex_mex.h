//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_ReadGCode_mex_mex.h
//
//  Code generation for function '_coder_ReadGCode_mex_mex'
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

// Function Declarations
MEXFUNCTION_LINKAGE void ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[7]);
MEXFUNCTION_LINKAGE void ConstrLineStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[4]);
MEXFUNCTION_LINKAGE void CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void ReadGCode_mexFunction(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void c_ConstrCurvStructType_mexFunct(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs);
MEXFUNCTION_LINKAGE void c_ConstrHelixStructFromArcFeed_(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[11]);
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
  const mxArray *prhs[]);
namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS();
}

// End of code generation (_coder_ReadGCode_mex_mex.h)
