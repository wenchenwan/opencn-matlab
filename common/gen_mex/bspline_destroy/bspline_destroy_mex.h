//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_destroy_mex.h
//
//  Code generation for function 'bspline_destroy_mex'
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
#include "bspline_destroy_mex_types.h"

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
  CODEGEN_EXPORT_SYM void bspline_destroy(const struct0_T *Bl);
  void bspline_destroy_api(const mxArray * const prhs[1], int32_T nlhs);
}

CODEGEN_EXPORT_SYM void bspline_destroy_mex_atexit();
namespace ocn
{
  CODEGEN_EXPORT_SYM void bspline_destroy_mex_initialize();
  CODEGEN_EXPORT_SYM void bspline_destroy_mex_terminate();
}

// End of code generation (bspline_destroy_mex.h)
