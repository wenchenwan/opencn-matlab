//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_c_simplex_mex.cpp
//
//  Code generation for function '_coder_c_simplex_mex'
//


// Include files
#include "_coder_c_simplex_mex.h"
#include "c_simplex.h"

// Function Declarations
MEXFUNCTION_LINKAGE void c_simplex_mexFunction(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[5]);

// Function Definitions
void c_simplex_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs, const
  mxArray *prhs[5])
{
  const mxArray *outputs[3];
  int32_T b_nlhs;

  // Check for proper number of arguments.
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 5, 4, 9, "c_simplex");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "c_simplex");
  }

  // Call the function.
  ocn::c_simplex_api(prhs, nlhs, outputs);

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
  mexAtExit(&c_simplex_atexit);

  // Module initialization.
  ocn::c_simplex_initialize();

  // Dispatch the entry-point.
  c_simplex_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  ocn::c_simplex_terminate();
}

namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS()
  {
    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    return emlrtRootTLSGlobal;
  }
}

// End of code generation (_coder_c_simplex_mex.cpp)
