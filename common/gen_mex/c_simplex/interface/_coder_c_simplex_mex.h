//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_c_simplex_mex.h
//
//  Code generation for function '_coder_c_simplex_mex'
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
#include "c_simplex_types.h"

// Function Declarations
MEXFUNCTION_LINKAGE void c_simplex_mexFunction(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[5]);
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
  const mxArray *prhs[]);
namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS();
}

// End of code generation (_coder_c_simplex_mex.h)
