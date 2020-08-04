/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_bspline_base_eval_mex_info.cpp
 *
 * Code generation for function '_coder_bspline_base_eval_mex_info'
 *
 */

/* Include files */
#include "_coder_bspline_base_eval_mex_info.h"
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
    "789ced56cb4edb40149db454ed061a16ed9a3dc293864a15bba629a0b44e40c482a8114ac6ce25b13a0fcb76d2844d3fa1bfd0254bbaed07f11df8357958588e"
    "62c9883647b2aeaf4e7ccfc919f9caa850ab1710425bde75f713a19d6d1460332ca818d567681171be10d5e7b15ee205da5878ae10e9fd8a7a437017c66ed870",
    "c260fa644f309313ee6a130b900d8ea023e805cc954941331934e79b86dfb1a3396adaf8947f5f1d80f1bd3964c81e38338774be09f2f07193f07f3796cce338"
    "218f628c6f1f5ee28160802d70c1c62631b1b0801b7ccf110293be773bc143c7c68cb894e8d8108c098e75c7a226878e610371416153dfe38cbedfa4f896bc21",
    "7a602ba67778362754a1c0fbee00cdf2ebaee8238e241f1252ef76453d39bf91a227f9764d6d2d1e19b12c07d72b9a5af984cfcaa57289605708aa8b31064683"
    "6b37480befcab8701897776ca979bd5ed27fbcce7eff2aa893ed93965ff3d293f85ff4f27aef34f5fcdb01ebb5eccac5fb0fe377fbe7acd4f83ae7e3344527cd",
    "074ae8f39aff54f76e37a3ef9789be434635f51abf128fb65f7fafa827e77f4cd1937cbbbad2b944f1282caff7ff6f7fb3e3d7bcf4fef495bd3cf5249eea3e7d"
    "9ba0578cf144ab18f5cfd723765cbeae1ea8a7fbc3e6c98fa37f679f66fd2efa9230bf18e333ee539d38d08191f725c916fd7733fa5fefd510ebbdfab0de7aaf",
    "8658efd5e5e6df0399490c63", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 4408U, &nameCaptureInfo);
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
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 1, "Name", emlrtMxCreateString("bspline_base_eval"));
  emlrtSetField(xEntryPoints, 1, "NumberOfInputs", emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 1, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (5.0));
  emlrtSetField(xEntryPoints, 1, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 1, "FullPath", emlrtMxCreateString(
    "/home/peter/iai/opencn-soo/agency/usr/matlab/common/bspline_base_eval.m"));
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

/* End of code generation (_coder_bspline_base_eval_mex_info.cpp) */
