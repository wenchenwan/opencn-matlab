//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_ReadGCode_mex_mex.cpp
//
//  Code generation for function '_coder_ReadGCode_mex_mex'
//


// Include files
#include "_coder_ReadGCode_mex_mex.h"
#include "ReadGCode_mex.h"

// Variable Definitions
static const char * emlrtEntryPoints[6] = { "ReadGCode", "ConstrLineStruct",
  "ConstrHelixStruct", "ConstrHelixStructFromArcFeed", "ConstrCurvStructType",
  "CopyCurvStruct" };

// Function Declarations
MEXFUNCTION_LINKAGE void ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[7]);
MEXFUNCTION_LINKAGE void ConstrLineStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[4]);
MEXFUNCTION_LINKAGE void CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void ReadGCode_mexFunction(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void c_ConstrCurvStructType_mexFunct(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs);
MEXFUNCTION_LINKAGE void c_ConstrHelixStructFromArcFeed_(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[11]);

// Function Definitions
void ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[7])
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 7) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 7, 4, 17, "ConstrHelixStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "ConstrHelixStruct");
  }

  // Call the function.
  ocn::ConstrHelixStruct_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void ConstrLineStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[4])
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 4) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 4, 4, 16, "ConstrLineStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 16,
                        "ConstrLineStruct");
  }

  // Call the function.
  ocn::ConstrLineStruct_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 1, 4, 14, "CopyCurvStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "CopyCurvStruct");
  }

  // Call the function.
  ocn::CopyCurvStruct_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void ReadGCode_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs, const
  mxArray *prhs[2])
{
  const mxArray *outputs[2];
  int32_T b_nlhs;

  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 2, 4, 9, "ReadGCode");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "ReadGCode");
  }

  // Call the function.
  ocn::ReadGCode_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, &outputs[0]);
}

void c_ConstrCurvStructType_mexFunct(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs)
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 0, 4, 20, "ConstrCurvStructType");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "ConstrCurvStructType");
  }

  // Call the function.
  ocn::ConstrCurvStructType_api(nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void c_ConstrHelixStructFromArcFeed_(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[11])
{
  const mxArray *outputs[1];

  // Check for proper number of arguments.
  if (nrhs != 11) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 11, 4, 28, "ConstrHelixStructFromArcFeed");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 28,
                        "ConstrHelixStructFromArcFeed");
  }

  // Call the function.
  ocn::ConstrHelixStructFromArcFeed_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  mexAtExit(&ReadGCode_mex_atexit);

  // Module initialization.
  ocn::ReadGCode_mex_initialize();
  st.tls = emlrtRootTLSGlobal;

  // Dispatch the entry-point.
  switch (emlrtGetEntryPointIndexR2016a(&st, nrhs, prhs, emlrtEntryPoints, 6)) {
   case 0:
    ReadGCode_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[2])&prhs[1]);
    break;

   case 1:
    ConstrLineStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[4])&
      prhs[1]);
    break;

   case 2:
    ConstrHelixStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[7])
      &prhs[1]);
    break;

   case 3:
    c_ConstrHelixStructFromArcFeed_(nlhs, plhs, nrhs - 1, *(const mxArray *(*)
      [11])&prhs[1]);
    break;

   case 4:
    c_ConstrCurvStructType_mexFunct(nlhs, plhs, nrhs - 1);
    break;

   case 5:
    CopyCurvStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&
      prhs[1]);
    break;
  }

  // Module termination.
  ocn::ReadGCode_mex_terminate();
}

namespace ocn
{
  emlrtCTX mexFunctionCreateRootTLS()
  {
    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    return emlrtRootTLSGlobal;
  }
}

// End of code generation (_coder_ReadGCode_mex_mex.cpp)
