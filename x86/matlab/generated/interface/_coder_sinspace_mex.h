//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_sinspace_mex.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef _CODER_SINSPACE_MEX_H
#define _CODER_SINSPACE_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                                     const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_CalcTransition_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
                                       const mxArray *prhs[3]);

void unsafe_ConfigSetSource_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                        const mxArray *prhs[2]);

void unsafe_ConstrCurvStructType_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs);

void unsafe_ConstrHelixStructFromArcFeed_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                                     const mxArray *prhs[16]);

void unsafe_ConstrHelixStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                          const mxArray *prhs[14]);

void unsafe_ConstrLineStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                         const mxArray *prhs[9]);

void unsafe_CopyCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                       const mxArray *prhs[1]);

void unsafe_DisableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[1]);

void unsafe_EnableDebugLog_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[1]);

void unsafe_EvalCurvStruct_mexFunction(int32_T nlhs, mxArray *plhs[4], int32_T nrhs,
                                       const mxArray *prhs[3]);

void unsafe_EvalPosition_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                     const mxArray *prhs[3]);

void unsafe_FeedoptDefaultConfig_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs);

void unsafe_FeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                                    const mxArray *prhs[1]);

void unsafe_InitFeedoptPlan_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                        const mxArray *prhs[1]);

void unsafe_PrintCurvStruct_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray *prhs[2]);

void unsafe_ResampleNoCtx_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                      const mxArray *prhs[3]);

void unsafe_ResampleState_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                      const mxArray *prhs[1]);

void unsafe_bspline_copy_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                     const mxArray *prhs[1]);

void unsafe_bspline_create_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                       const mxArray *prhs[2]);

void unsafe_c_roots__mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[1]);

void unsafe_linspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[3]);

void unsafe_sinspace_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[3]);

#endif
//
// File trailer for _coder_sinspace_mex.h
//
// [EOF]
//
