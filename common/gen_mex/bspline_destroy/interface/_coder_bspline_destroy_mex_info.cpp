/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_bspline_destroy_mex_info.cpp
 *
 * Code generation for function '_coder_bspline_destroy_mex_info'
 *
 */

/* Include files */
#include "_coder_bspline_destroy_mex_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[6] = {
    "789ced54cb6ed340149dd022d814d205a8ff50d5135224d45d43684b5427ad88552222d44eecdbc4621ed678d226ddf413f805962c61cb07f11dc48fc9c3c272"
    "944846153e92757d75e27b4eee680e2a359a2584d0b3c9f3fb1ea19d6d14622b2aa81cd747681149be14d78d44aff1186d2e7c578af5bec6bd2db882918a1a4e",
    "184cbf74047339e1ca1a7b8024f882de801332d72e05cb65d09e6f5a41c78ee7a8691350c17b7d00f697f6902139f0670ee97c13ee23c0f794ffbbb9e43e4e52"
    "f6514ef0dda3cf782018600f1448ec12170b0fb8cdf77c2130e94f5ec778e84bcc88a2a4876dc198e0b8e77bd4e570694b200a0c36f53d5ad3f78b0cdf9ab785",
    "03d27027872739a10605de570334dbdfd58a3e9248f3a1a1f57eaca8a7e7b732f434df6d989dc523239ee7e366cd326b6ff1876aa55a215809417b628481d1f0"
    "d90db78577f5ba70b4aec9b165eeebf992fe9375f6fba7611d6f9f75829a979ec6ffa297d7bdb3cc8b4f07cce9c8dac7d76f46aff62f58a5753ae7e33c4327cb",
    "074ae9f39aff5073f76a4ddf4f527d478ce9f61afc5afcb37cfdb6a29e9e7f98a1a7f96e7da57389d763b0bceeffaffed66550f3d2fbd937f6f2d4d378a879fa"
    "3245af9ce08955b39befee6ed849f5ae7e609eef0fdb67b7c7459eea79ef53e69713fc9a79ea80afa41867dfdf224f231c66e869bec8d3bfeb15791aa1c8d3e5",
    "e6ff011ecf0bb7", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 4400U, &nameCaptureInfo);
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

  xEntryPoints = emlrtCreateStructMatrix(1, 2, 6, epFieldName);
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
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 1, "Name", emlrtMxCreateString("bspline_destroy"));
  emlrtSetField(xEntryPoints, 1, "NumberOfInputs", emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 1, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (0.0));
  emlrtSetField(xEntryPoints, 1, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 1, "FullPath", emlrtMxCreateString(
    "/home/peter/iai/opencn-soo/agency/usr/matlab/common/bspline_destroy.m"));
  emlrtSetField(xEntryPoints, 1, "TimeStamp", emlrtMxCreateDoubleScalar
                (737986.42178240744));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1417392 (R2020a) Update 4"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_bspline_destroy_mex_info.cpp) */
