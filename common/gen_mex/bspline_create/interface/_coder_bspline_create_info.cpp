/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_bspline_create_info.cpp
 *
 * Code generation for function '_coder_bspline_create_info'
 *
 */

/* Include files */
#include "_coder_bspline_create_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[5] = {
    "789ce554cb4ac340149d88a2206a5de84f8899da0ae2ce5a1f14d32a36d462913a4daf6d701e2149b575e327f80b2e5dead62ff04bfc0e9bb4d34720a4548814"
    "2f0c772e6766cec9b9e4222597571042abddf5fd8cd0d732f263a59750a29fe7d078047125704e193f8e16d0fcd83da5cff7d2af0dc15d68bbbd821306839b75",
    "c14c4eb8ab772c403638823e40dd47ee4c0abac9a0385a14bc8a9d8c4083c283bc7db609c67db1c590dd74860ae968e1fbe1c55bc8f7ce4fe8c769881f89005e"
    "39bec14dc1005be0828d4d6262610137f8b62304268deeb6835b8e8d197129a96143302638ae39163539540d1b880b2a1be86eff52f746846e891ba20eb66a76",
    "9b677342550abce136d1d0bfdb297504234c870cc9f73e259f7cbf10c127f14a4e2b8fb78c589683f3195dcb1ce2cb54329524d81582d6441b03a3fedaf2ddc2"
    "5bd22edcb3abdbb648bfd626d41fccc3f34b7eeeac9f97bd1c179f8cffc217d77fa76ba5eb7d562fdb99abddbdf64ebac49285b3111d17113c513a50481dd7fb",
    "b33a776f7fa97b3154770fd1cc5a8edf893f9bafaf53f2c9f70f22f8245ec94ed597be3d2a8bebffff6cac54bd1c17df4743dd8e934fc6acced3cd10be440027"
    "7ac6c81f3d3db0d3d453765fbb48b78ae78f27b33f4f7f00bfb2c23f", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 3040U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties()
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("bspline_create"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "/home/peter/iai/opencn-soo/agency/usr/matlab/common/bspline_create.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737986.42178240744));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1417392 (R2020a) Update 4"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_bspline_create_info.cpp) */
