//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_bspline_eval_mex_mex.cpp
//
//  Code generation for function '_coder_bspline_eval_mex_mex'
//


// Include files
#include "_coder_bspline_eval_mex_mex.h"
#include "bspline_eval_mex.h"

// Variable Definitions
static const char * emlrtEntryPoints[2] = { "bspline_create", "bspline_eval" };

// Function Declarations
MEXFUNCTION_LINKAGE void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void bspline_eval_mexFunction(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[3]);

// Function Definitions
void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[2])
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 2, 4, 14, "bspline_create");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "bspline_create");
  }

  // Call the function.
  ocn::bspline_create_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void bspline_eval_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[4];
  int32_T b_nlhs;

  // Check for proper number of arguments.
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 3, 4, 12, "bspline_eval");
  }

  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12,
                        "bspline_eval");
  }

  // Call the function.
  ocn::bspline_eval_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  mexAtExit(&bspline_eval_mex_atexit);

  // Module initialization.
  ocn::bspline_eval_mex_initialize();
  st.tls = emlrtRootTLSGlobal;

  // Dispatch the entry-point.
  switch (emlrtGetEntryPointIndexR2016a(&st, nrhs, prhs, emlrtEntryPoints, 2)) {
   case 0:
    bspline_create_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[2])&
      prhs[1]);
    break;

   case 1:
    bspline_eval_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&
      prhs[1]);
    break;
  }

  // Module termination.
  ocn::bspline_eval_mex_terminate();
}

namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS()
  {
    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    return emlrtRootTLSGlobal;
  }
}

// End of code generation (_coder_bspline_eval_mex_mex.cpp)
