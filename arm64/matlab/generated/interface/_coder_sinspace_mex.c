/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_sinspace_mex.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 29-Mar-2021 16:21:48
 */

/* Include Files */
#include "_coder_sinspace_mex.h"
#include "_coder_sinspace_api.h"

/* Variable Definitions */
static const char * emlrtEntryPoints[22] = { "sinspace", "FeedoptDefaultConfig",
  "InitFeedoptPlan", "ConstrCurvStructType", "EvalCurvStruct", "c_roots_",
  "PrintCurvStruct", "CalcTransition", "FeedoptPlan", "linspace",
  "ConstrLineStruct", "ConstrHelixStruct", "ConstrHelixStructFromArcFeed",
  "bspline_create", "ResampleState", "ResampleNoCtx", "EvalPosition",
  "bspline_copy", "CopyCurvStruct", "EnableDebugLog", "DisableDebugLog",
  "ConfigSetSource" };

/* Function Declarations */
MEXFUNCTION_LINKAGE void CalcTransition_mexFunction(int32_T nlhs, mxArray *plhs
  [4], int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void ConfigSetSource_mexFunction(int32_T nlhs, mxArray *
  plhs[1], int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[9]);
MEXFUNCTION_LINKAGE void ConstrLineStruct_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[4]);
MEXFUNCTION_LINKAGE void CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void DisableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs,
  const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void EnableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs,
  const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void EvalCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs
  [4], int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void EvalPosition_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void FeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void InitFeedoptPlan_mexFunction(int32_T nlhs, mxArray *
  plhs[1], int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void PrintCurvStruct_mexFunction(int32_T nlhs, int32_T nrhs,
  const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void ResampleNoCtx_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void ResampleState_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void bspline_copy_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs
  [1], int32_T nrhs, const mxArray *prhs[2]);
MEXFUNCTION_LINKAGE void c_ConstrCurvStructType_mexFunct(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs);
MEXFUNCTION_LINKAGE void c_ConstrHelixStructFromArcFeed_(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[11]);
MEXFUNCTION_LINKAGE void c_FeedoptDefaultConfig_mexFunct(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs);
MEXFUNCTION_LINKAGE void c_roots__mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[1]);
MEXFUNCTION_LINKAGE void linspace_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[3]);
MEXFUNCTION_LINKAGE void sinspace_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[3]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[4]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void CalcTransition_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[4];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        14, "CalcTransition");
  }

  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "CalcTransition");
  }

  /* Call the function. */
  CalcTransition_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
void ConfigSetSource_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[2])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        15, "ConfigSetSource");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "ConfigSetSource");
  }

  /* Call the function. */
  ConfigSetSource_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[9]
 * Return Type  : void
 */
void ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[9])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 9) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 9, 4,
                        17, "ConstrHelixStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "ConstrHelixStruct");
  }

  /* Call the function. */
  ConstrHelixStruct_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[4]
 * Return Type  : void
 */
void ConstrLineStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[4])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 4, 4,
                        16, "ConstrLineStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 16,
                        "ConstrLineStruct");
  }

  /* Call the function. */
  ConstrLineStruct_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        14, "CopyCurvStruct");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "CopyCurvStruct");
  }

  /* Call the function. */
  CopyCurvStruct_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void DisableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *
  prhs[1])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        15, "DisableDebugLog");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "DisableDebugLog");
  }

  /* Call the function. */
  DisableDebugLog_api(prhs, nlhs);
}

/*
 * Arguments    : int32_T nlhs
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void EnableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs
  [1])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        14, "EnableDebugLog");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "EnableDebugLog");
  }

  /* Call the function. */
  EnableDebugLog_api(prhs, nlhs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[4]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void EvalCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[4];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        14, "EvalCurvStruct");
  }

  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "EvalCurvStruct");
  }

  /* Call the function. */
  EvalCurvStruct_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void EvalPosition_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        12, "EvalPosition");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12,
                        "EvalPosition");
  }

  /* Call the function. */
  EvalPosition_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[3]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void FeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs, const
  mxArray *prhs[1])
{
  const mxArray *outputs[3];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        11, "FeedoptPlan");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 11,
                        "FeedoptPlan");
  }

  /* Call the function. */
  FeedoptPlan_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void InitFeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        15, "InitFeedoptPlan");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "InitFeedoptPlan");
  }

  /* Call the function. */
  InitFeedoptPlan_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
void PrintCurvStruct_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *
  prhs[2])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        15, "PrintCurvStruct");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "PrintCurvStruct");
  }

  /* Call the function. */
  PrintCurvStruct_api(prhs, nlhs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void ResampleNoCtx_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        13, "ResampleNoCtx");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "ResampleNoCtx");
  }

  /* Call the function. */
  ResampleNoCtx_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void ResampleState_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        13, "ResampleState");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "ResampleState");
  }

  /* Call the function. */
  ResampleState_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void bspline_copy_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        12, "bspline_copy");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12,
                        "bspline_copy");
  }

  /* Call the function. */
  bspline_copy_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
void bspline_create_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[2])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        14, "bspline_create");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "bspline_create");
  }

  /* Call the function. */
  bspline_create_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 * Return Type  : void
 */
void c_ConstrCurvStructType_mexFunct(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs)
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        20, "ConstrCurvStructType");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "ConstrCurvStructType");
  }

  /* Call the function. */
  ConstrCurvStructType_api(nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[11]
 * Return Type  : void
 */
void c_ConstrHelixStructFromArcFeed_(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[11])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 11) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 11, 4,
                        28, "ConstrHelixStructFromArcFeed");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 28,
                        "ConstrHelixStructFromArcFeed");
  }

  /* Call the function. */
  ConstrHelixStructFromArcFeed_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 * Return Type  : void
 */
void c_FeedoptDefaultConfig_mexFunct(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs)
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        20, "FeedoptDefaultConfig");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "FeedoptDefaultConfig");
  }

  /* Call the function. */
  FeedoptDefaultConfig_api(nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void c_roots__mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 8,
                        "c_roots_");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8,
                        "c_roots_");
  }

  /* Call the function. */
  c_roots__api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void linspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[3])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 8,
                        "linspace");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8,
                        "linspace");
  }

  /* Call the function. */
  linspace_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void sinspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[3])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 8,
                        "sinspace");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8,
                        "sinspace");
  }

  /* Call the function. */
  sinspace_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexAtExit(&sinspace_atexit);

  /* Module initialization. */
  sinspace_initialize();
  st.tls = emlrtRootTLSGlobal;

  /* Dispatch the entry-point. */
  switch (emlrtGetEntryPointIndexR2016a(&st, nrhs, prhs, emlrtEntryPoints, 22))
  {
   case 0:
    sinspace_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&prhs[1]);
    break;

   case 1:
    c_FeedoptDefaultConfig_mexFunct(nlhs, plhs, nrhs - 1);
    break;

   case 2:
    InitFeedoptPlan_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&
      prhs[1]);
    break;

   case 3:
    c_ConstrCurvStructType_mexFunct(nlhs, plhs, nrhs - 1);
    break;

   case 4:
    EvalCurvStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&
      prhs[1]);
    break;

   case 5:
    c_roots__mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&prhs[1]);
    break;

   case 6:
    PrintCurvStruct_mexFunction(nlhs, nrhs - 1, *(const mxArray *(*)[2])&prhs[1]);
    break;

   case 7:
    CalcTransition_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&
      prhs[1]);
    break;

   case 8:
    FeedoptPlan_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&prhs
      [1]);
    break;

   case 9:
    linspace_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&prhs[1]);
    break;

   case 10:
    ConstrLineStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[4])&
      prhs[1]);
    break;

   case 11:
    ConstrHelixStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[9])
      &prhs[1]);
    break;

   case 12:
    c_ConstrHelixStructFromArcFeed_(nlhs, plhs, nrhs - 1, *(const mxArray *(*)
      [11])&prhs[1]);
    break;

   case 13:
    bspline_create_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[2])&
      prhs[1]);
    break;

   case 14:
    ResampleState_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&
      prhs[1]);
    break;

   case 15:
    ResampleNoCtx_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&
      prhs[1]);
    break;

   case 16:
    EvalPosition_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[3])&
      prhs[1]);
    break;

   case 17:
    bspline_copy_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&
      prhs[1]);
    break;

   case 18:
    CopyCurvStruct_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[1])&
      prhs[1]);
    break;

   case 19:
    EnableDebugLog_mexFunction(nlhs, nrhs - 1, *(const mxArray *(*)[1])&prhs[1]);
    break;

   case 20:
    DisableDebugLog_mexFunction(nlhs, nrhs - 1, *(const mxArray *(*)[1])&prhs[1]);
    break;

   case 21:
    ConfigSetSource_mexFunction(nlhs, plhs, nrhs - 1, *(const mxArray *(*)[2])&
      prhs[1]);
    break;
  }

  /* Module termination. */
  sinspace_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_sinspace_mex.c
 *
 * [EOF]
 */
