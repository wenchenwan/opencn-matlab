//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_bspline_eval_mex_mex.h
//
//  Code generation for function '_coder_bspline_eval_mex_mex'
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
#include "bspline_eval_mex_types.h"

// Function Declarations
MEXFUNCTION_LINKAGE void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void bspline_eval_mexFunction(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
  const mxArray *prhs[]);
namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS();
}

// End of code generation (_coder_bspline_eval_mex_mex.h)
