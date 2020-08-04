//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_bspline_destroy_mex_mex.cpp
//
//  Code generation for function '_coder_bspline_destroy_mex_mex'
//


// Include files
#include "_coder_bspline_destroy_mex_mex.h"
#include "bspline_destroy_mex.h"

// Variable Definitions
static const char * emlrtEntryPoints[2] = { "bspline_create", "bspline_destroy"
};

// Function Declarations
MEXFUNCTION_LINKAGE void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void bspline_destroy_mexFunction(int32_T nlhs, int32_T nrhs,
  const mxArray *prhs[1]);

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

void bspline_destroy_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *
  prhs[1])
{
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 1, 4, 15, "bspline_destroy");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "bspline_destroy");
  }

  // Call the function.
  ocn::bspline_destroy_api(prhs, nlhs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  mexAtExit(&bspline_destroy_mex_atexit);

  // Module initialization.
  ocn::bspline_destroy_mex_initialize();
  st.tls = emlrtRootTLSGlobal;

  // Dispatch the entry-point.
  switch (emlrtGetEntryPointIndexR2016a(&st, nrhs, prhs, emlrtEntryPoints, 2)) {
   case 0:
    bspline_create_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[2])&
      prhs[1]);
    break;

   case 1:
    bspline_destroy_mexFunction(nlhs, nrhs - 1, *(const mxArray *(*)[1])&prhs[1]);
    break;
  }

  // Module termination.
  ocn::bspline_destroy_mex_terminate();
}

namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS()
  {
    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    return emlrtRootTLSGlobal;
  }
}

// End of code generation (_coder_bspline_destroy_mex_mex.cpp)
