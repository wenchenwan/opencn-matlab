//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_sinspace_mex.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "_coder_sinspace_mex.h"
#include "_coder_sinspace_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray *prhs[])
{
    static const char_T *emlrtEntryPoints[22]{"sinspace",
                                              "FeedoptDefaultConfig",
                                              "InitFeedoptPlan",
                                              "ConstrCurvStructType",
                                              "EvalCurvStruct",
                                              "c_roots_",
                                              "PrintCurvStruct",
                                              "CalcTransition",
                                              "FeedoptPlan",
                                              "linspace",
                                              "ConstrLineStruct",
                                              "ConstrHelixStruct",
                                              "ConstrHelixStructFromArcFeed",
                                              "bspline_create",
                                              "ResampleState",
                                              "ResampleNoCtx",
                                              "EvalPosition",
                                              "bspline_copy",
                                              "CopyCurvStruct",
                                              "EnableDebugLog",
                                              "DisableDebugLog",
                                              "ConfigSetSource"};
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    mexAtExit(&sinspace_atexit);
    // Module initialization.
    sinspace_initialize();
    st.tls = emlrtRootTLSGlobal;
    try {
        emlrtShouldCleanupOnError((emlrtCTX *)emlrtRootTLSGlobal, false);
        // Dispatch the entry-point.
        switch (emlrtGetEntryPointIndexR2016a(&st, nrhs, &prhs[0],
                                              (const char_T **)&emlrtEntryPoints[0], 22)) {
        case 0:
            unsafe_sinspace_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 1:
            unsafe_FeedoptDefaultConfig_mexFunction(nlhs, plhs, nrhs - 1);
            break;
        case 2:
            unsafe_InitFeedoptPlan_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 3:
            unsafe_ConstrCurvStructType_mexFunction(nlhs, plhs, nrhs - 1);
            break;
        case 4:
            unsafe_EvalCurvStruct_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 5:
            unsafe_c_roots__mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 6:
            unsafe_PrintCurvStruct_mexFunction(nlhs, nrhs - 1, &prhs[1]);
            break;
        case 7:
            unsafe_CalcTransition_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 8:
            unsafe_FeedoptPlan_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 9:
            unsafe_linspace_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 10:
            unsafe_ConstrLineStruct_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 11:
            unsafe_ConstrHelixStruct_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 12:
            unsafe_ConstrHelixStructFromArcFeed_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 13:
            unsafe_bspline_create_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 14:
            unsafe_ResampleState_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 15:
            unsafe_ResampleNoCtx_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 16:
            unsafe_EvalPosition_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 17:
            unsafe_bspline_copy_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 18:
            unsafe_CopyCurvStruct_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        case 19:
            unsafe_EnableDebugLog_mexFunction(nlhs, nrhs - 1, &prhs[1]);
            break;
        case 20:
            unsafe_DisableDebugLog_mexFunction(nlhs, nrhs - 1, &prhs[1]);
            break;
        case 21:
            unsafe_ConfigSetSource_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
            break;
        }
        // Module termination.
        sinspace_terminate();
    } catch (...) {
        emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
        throw;
    }
}

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
    emlrtCreateRootTLSR2021a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1, nullptr);
    return emlrtRootTLSGlobal;
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[4]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_CalcTransition_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
                                       const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs[4];
    int32_T b_nlhs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 14,
                            "CalcTransition");
    }
    if (nlhs > 4) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                            "CalcTransition");
    }
    // Call the function.
    CalcTransition_api(prhs, nlhs, outputs);
    // Copy over outputs to the caller.
    if (nlhs < 1) {
        b_nlhs = 1;
    } else {
        b_nlhs = nlhs;
    }
    emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[2]
// Return Type  : void
//
void unsafe_ConfigSetSource_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                        const mxArray *prhs[2])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 2) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 15,
                            "ConfigSetSource");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                            "ConfigSetSource");
    }
    // Call the function.
    ConfigSetSource_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
// Return Type  : void
//
void unsafe_ConstrCurvStructType_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs)
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 0) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4, 20,
                            "ConstrCurvStructType");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                            "ConstrCurvStructType");
    }
    // Call the function.
    ConstrCurvStructType_api(&outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[11]
// Return Type  : void
//
void unsafe_ConstrHelixStructFromArcFeed_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                                     const mxArray *prhs[11])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 11) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 11, 4, 28,
                            "ConstrHelixStructFromArcFeed");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 28,
                            "ConstrHelixStructFromArcFeed");
    }
    // Call the function.
    ConstrHelixStructFromArcFeed_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[9]
// Return Type  : void
//
void unsafe_ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                          const mxArray *prhs[9])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 9) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 9, 4, 17,
                            "ConstrHelixStruct");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                            "ConstrHelixStruct");
    }
    // Call the function.
    ConstrHelixStruct_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[4]
// Return Type  : void
//
void unsafe_ConstrLineStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                         const mxArray *prhs[4])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 4) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 4, 4, 16,
                            "ConstrLineStruct");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 16,
                            "ConstrLineStruct");
    }
    // Call the function.
    ConstrLineStruct_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                       const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 14,
                            "CopyCurvStruct");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                            "CopyCurvStruct");
    }
    // Call the function.
    CopyCurvStruct_api(prhs[0], &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_DisableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 15,
                            "DisableDebugLog");
    }
    if (nlhs > 0) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                            "DisableDebugLog");
    }
    // Call the function.
    DisableDebugLog_api(prhs[0]);
}

//
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_EnableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 14,
                            "EnableDebugLog");
    }
    if (nlhs > 0) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                            "EnableDebugLog");
    }
    // Call the function.
    EnableDebugLog_api(prhs[0]);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[4]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_EvalCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
                                       const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs[4];
    int32_T b_nlhs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 14,
                            "EvalCurvStruct");
    }
    if (nlhs > 4) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                            "EvalCurvStruct");
    }
    // Call the function.
    EvalCurvStruct_api(prhs, nlhs, outputs);
    // Copy over outputs to the caller.
    if (nlhs < 1) {
        b_nlhs = 1;
    } else {
        b_nlhs = nlhs;
    }
    emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_EvalPosition_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                     const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 12,
                            "EvalPosition");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12, "EvalPosition");
    }
    // Call the function.
    EvalPosition_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
// Return Type  : void
//
void unsafe_FeedoptDefaultConfig_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs)
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 0) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4, 20,
                            "FeedoptDefaultConfig");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                            "FeedoptDefaultConfig");
    }
    // Call the function.
    FeedoptDefaultConfig_api(&outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[3]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_FeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                                    const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs[3];
    int32_T b_nlhs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 11,
                            "FeedoptPlan");
    }
    if (nlhs > 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 11, "FeedoptPlan");
    }
    // Call the function.
    FeedoptPlan_api(prhs[0], nlhs, outputs);
    // Copy over outputs to the caller.
    if (nlhs < 1) {
        b_nlhs = 1;
    } else {
        b_nlhs = nlhs;
    }
    emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_InitFeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                        const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 15,
                            "InitFeedoptPlan");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                            "InitFeedoptPlan");
    }
    // Call the function.
    InitFeedoptPlan_api(prhs[0], &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[2]
// Return Type  : void
//
void unsafe_PrintCurvStruct_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[2])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 2) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 15,
                            "PrintCurvStruct");
    }
    if (nlhs > 0) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                            "PrintCurvStruct");
    }
    // Call the function.
    PrintCurvStruct_api(prhs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_ResampleNoCtx_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                      const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 13,
                            "ResampleNoCtx");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13, "ResampleNoCtx");
    }
    // Call the function.
    ResampleNoCtx_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_ResampleState_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                      const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 13,
                            "ResampleState");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13, "ResampleState");
    }
    // Call the function.
    ResampleState_api(prhs[0], &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_bspline_copy_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                     const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 12,
                            "bspline_copy");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12, "bspline_copy");
    }
    // Call the function.
    bspline_copy_api(prhs[0], &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[2]
// Return Type  : void
//
void unsafe_bspline_create_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                       const mxArray *prhs[2])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 2) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 14,
                            "bspline_create");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                            "bspline_create");
    }
    // Call the function.
    bspline_create_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_c_roots__mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[1])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 8, "c_roots_");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8, "c_roots_");
    }
    // Call the function.
    c_roots__api(prhs[0], &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_linspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 8, "linspace");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8, "linspace");
    }
    // Call the function.
    linspace_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[3]
// Return Type  : void
//
void unsafe_sinspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[3])
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *outputs;
    st.tls = emlrtRootTLSGlobal;
    // Check for proper number of arguments.
    if (nrhs != 3) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 8, "sinspace");
    }
    if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 8, "sinspace");
    }
    // Call the function.
    sinspace_api(prhs, &outputs);
    // Copy over outputs to the caller.
    emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// File trailer for _coder_sinspace_mex.cpp
//
// [EOF]
//
