//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_base_eval_mex.h
//
//  Code generation for function 'bspline_base_eval_mex'
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
#include "bspline_base_eval_mex_types.h"

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
namespace ocn
{
  CODEGEN_EXPORT_SYM void bspline_base_eval(const struct0_T *Bl, const coder::
    array<real_T, 2U> &xvec, coder::array<real_T, 2U> &BasisVal, coder::array<
    real_T, 2U> &BasisValD, coder::array<real_T, 2U> &BasisValDD, coder::array<
    real_T, 2U> &BasisValDDD, coder::array<real_T, 1U> &BasisIntegr);
  void bspline_base_eval_api(const mxArray * const prhs[2], int32_T nlhs, const
    mxArray *plhs[5]);
}

CODEGEN_EXPORT_SYM void bspline_base_eval_mex_atexit();
namespace ocn
{
  CODEGEN_EXPORT_SYM void bspline_base_eval_mex_initialize();
  CODEGEN_EXPORT_SYM void bspline_base_eval_mex_terminate();
  CODEGEN_EXPORT_SYM void bspline_create(int32_T degree, const coder::array<
    real_T, 2U> &breakpoints, struct0_T *Bl);
  void bspline_create_api(const mxArray * const prhs[2], int32_T nlhs, const
    mxArray *plhs[1]);
}

// End of code generation (bspline_base_eval_mex.h)
