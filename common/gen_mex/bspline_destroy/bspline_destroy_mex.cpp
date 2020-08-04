//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_destroy_mex.cpp
//
//  Code generation for function 'bspline_destroy_mex'
//


// Include files
#include "bspline_destroy_mex.h"
#include "_coder_bspline_destroy_mex_mex.h"
#include "rt_nonfinite.h"
#include "src/c_spline.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,// bFirstTime
  false,                               // bInitialized
  131594U,                             // fVersionInfo
  NULL,                                // fErrorFunction
  "bspline_destroy_mex",               // fFunctionName
  NULL,                                // fRTCallStack
  false,                               // bDebugMode
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },// fSigWrd
  NULL                                 // fSigMem
};

// Function Declarations
namespace ocn
{
  static int32_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static void c_emlrt_marshallIn(const mxArray *breakpoints, const char_T
    *identifier, coder::array<real_T, 2U> &y);
  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static void e_emlrt_marshallIn(const mxArray *Bl, const char_T *identifier,
    struct0_T *y);
  static int32_T emlrt_marshallIn(const mxArray *degree, const char_T
    *identifier);
  static const mxArray *emlrt_marshallOut(const struct0_T *u);
  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, struct0_T *y);
  static void g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static uint64_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId);
  static int32_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId);
  static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static uint64_T l_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId);
}

// Function Definitions
namespace ocn
{
  static int32_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    int32_T y;
    y = i_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void c_emlrt_marshallIn(const mxArray *breakpoints, const char_T
    *identifier, coder::array<real_T, 2U> &y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    d_emlrt_marshallIn(emlrtAlias(breakpoints), &thisId, y);
    emlrtDestroyArray(&breakpoints);
  }

  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    j_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void e_emlrt_marshallIn(const mxArray *Bl, const char_T *identifier,
    struct0_T *y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    f_emlrt_marshallIn(emlrtAlias(Bl), &thisId, y);
    emlrtDestroyArray(&Bl);
  }

  static int32_T emlrt_marshallIn(const mxArray *degree, const char_T
    *identifier)
  {
    int32_T y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = b_emlrt_marshallIn(emlrtAlias(degree), &thisId);
    emlrtDestroyArray(&degree);
    return y;
  }

  static const mxArray *emlrt_marshallOut(const struct0_T *u)
  {
    const mxArray *y;
    static const char * sv[4] = { "ncoeff", "breakpoints", "handle", "degree" };

    const mxArray *b_y;
    const mxArray *m;
    int32_T iv[2];
    real_T *pData;
    int32_T i;
    y = NULL;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 4, &sv[0]));
    b_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u->ncoeff;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "ncoeff", b_y, 0);
    b_y = NULL;
    iv[0] = u->breakpoints.size(0);
    iv[1] = u->breakpoints.size(1);
    m = emlrtCreateNumericArray(2, &iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i = 0; b_i < u->breakpoints.size(1); b_i++) {
      pData[i] = u->breakpoints[b_i];
      i++;
    }

    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "breakpoints", b_y, 1);
    b_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *(uint64_T *)emlrtMxGetData(m) = u->handle;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "handle", b_y, 2);
    b_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u->degree;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "degree", b_y, 3);
    return y;
  }

  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, struct0_T *y)
  {
    emlrtMsgIdentifier thisId;
    static const char * fieldNames[4] = { "ncoeff", "breakpoints", "handle",
      "degree" };

    static const int32_T dims = 0;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 4, fieldNames, 0U,
      &dims);
    thisId.fIdentifier = "ncoeff";
    y->ncoeff = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 0, "ncoeff")), &thisId);
    thisId.fIdentifier = "breakpoints";
    g_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      1, "breakpoints")), &thisId, y->breakpoints);
    thisId.fIdentifier = "handle";
    y->handle = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 2, "handle")), &thisId);
    thisId.fIdentifier = "degree";
    y->degree = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 3, "degree")), &thisId);
    emlrtDestroyArray(&u);
  }

  static void g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    k_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static uint64_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId)
  {
    uint64_T y;
    y = l_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static int32_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId)
  {
    int32_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 0U,
      &dims);
    ret = *(int32_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret)
  {
    static const int32_T dims[2] = { 1, -1 };

    const boolean_T bv[2] = { false, true };

    int32_T iv[2];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      2U, dims, &bv[0], iv);
    ret.prealloc((iv[0] * iv[1]));
    ret.set_size(iv[0], iv[1]);
    ret.set(((real_T *)emlrtMxGetData(src)), ret.size(0), ret.size(1));
    emlrtDestroyArray(&src);
  }

  static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret)
  {
    static const int32_T dims[2] = { 1, -1 };

    const boolean_T bv[2] = { false, true };

    int32_T iv[2];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      2U, dims, &bv[0], iv);
    ret.set_size(iv[0], iv[1]);
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &(ret.data())[0], 8, false);
    emlrtDestroyArray(&src);
  }

  static uint64_T l_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId)
  {
    uint64_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint64", false, 0U,
      &dims);
    ret = *(uint64_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  void bspline_create(int32_T degree, const coder::array<real_T, 2U>
                      &breakpoints, struct0_T *Bl)
  {
    coder::array<real_T, 2U> b_breakpoints;
    int32_T loop_ub;
    int32_T i;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
    Bl->ncoeff = (breakpoints.size(1) + degree) - 2;
    b_breakpoints.set_size(1, breakpoints.size(1));
    loop_ub = breakpoints.size(1);
    for (i = 0; i < loop_ub; i++) {
      b_breakpoints[i] = breakpoints[i];
    }

    c_bspline_create_with_breakpoints(&Bl->handle, degree, &b_breakpoints[0],
      breakpoints.size(1));
    Bl->breakpoints.set_size(1, breakpoints.size(1));
    loop_ub = breakpoints.size(1);
    for (i = 0; i < loop_ub; i++) {
      Bl->breakpoints[i] = breakpoints[i];
    }

    Bl->degree = degree;
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void bspline_create_api(const mxArray * const prhs[2], int32_T, const mxArray *
    plhs[1])
  {
    int32_T degree;
    coder::array<real_T, 2U> breakpoints;
    struct0_T Bl;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    degree = emlrt_marshallIn(emlrtAliasP(prhs[0]), "degree");
    breakpoints.no_free();
    c_emlrt_marshallIn(emlrtAlias(prhs[1]), "breakpoints", breakpoints);

    // Invoke the target function
    bspline_create(degree, breakpoints, &Bl);

    // Marshall function outputs
    plhs[0] = emlrt_marshallOut(&Bl);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void bspline_destroy(const struct0_T *Bl)
  {
    if (Bl->handle > 0UL) {
      c_bspline_destroy(&Bl->handle);
    }
  }

  void bspline_destroy_api(const mxArray * const prhs[1], int32_T)
  {
    struct0_T Bl;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    e_emlrt_marshallIn(emlrtAliasP(prhs[0]), "Bl", &Bl);

    // Invoke the target function
    bspline_destroy(&Bl);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }
}

void bspline_destroy_mex_atexit()
{
  ocn::mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

namespace ocn
{
  void bspline_destroy_mex_initialize()
  {
    mex_InitInfAndNan();
    mexFunctionCreateRootTLS();
    emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
    emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
    emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
  }

  void bspline_destroy_mex_terminate()
  {
    emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  }
}

// End of code generation (bspline_destroy_mex.cpp)
