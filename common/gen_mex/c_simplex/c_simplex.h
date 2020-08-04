//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  c_simplex.h
//
//  Code generation for function 'c_simplex'
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

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
namespace ocn
{
  CODEGEN_EXPORT_SYM void c_simplex(const coder::array<real_T, 2U> &f, const
    coder_internal_sparse *A, coder::array<real_T, 1U> &b, const coder::array<
    real_T, 2U> &Aeq, const coder::array<real_T, 1U> &beq, coder::array<real_T,
    2U> &C, boolean_T *success, int32_T *status);
  void c_simplex_api(const mxArray * const prhs[5], int32_T nlhs, const mxArray *
                     plhs[3]);
}

CODEGEN_EXPORT_SYM void c_simplex_atexit();
namespace ocn
{
  CODEGEN_EXPORT_SYM void c_simplex_initialize();
  CODEGEN_EXPORT_SYM void c_simplex_terminate();
}

// End of code generation (c_simplex.h)
