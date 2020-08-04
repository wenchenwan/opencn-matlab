//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_create.h
//
//  Code generation for function 'bspline_create'
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
#include "bspline_create_types.h"

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
namespace ocn
{
  CODEGEN_EXPORT_SYM void bspline_create(int32_T degree, const coder::array<
    real_T, 2U> &breakpoints, struct0_T *Bl);
  void bspline_create_api(const mxArray * const prhs[2], int32_T nlhs, const
    mxArray *plhs[1]);
}

CODEGEN_EXPORT_SYM void bspline_create_atexit();
namespace ocn
{
  CODEGEN_EXPORT_SYM void bspline_create_initialize();
  CODEGEN_EXPORT_SYM void bspline_create_terminate();
}

// End of code generation (bspline_create.h)
