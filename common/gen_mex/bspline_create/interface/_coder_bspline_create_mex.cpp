//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_bspline_create_mex.cpp
//
//  Code generation for function '_coder_bspline_create_mex'
//


// Include files
#include "_coder_bspline_create_mex.h"
#include "bspline_create.h"

// Function Declarations
MEXFUNCTION_LINKAGE void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[2]);

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

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&bspline_create_atexit);

  // Module initialization.
  ocn::bspline_create_initialize();

  // Dispatch the entry-point.
  bspline_create_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  ocn::bspline_create_terminate();
}

namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS()
  {
    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    return emlrtRootTLSGlobal;
  }
}

// End of code generation (_coder_bspline_create_mex.cpp)
