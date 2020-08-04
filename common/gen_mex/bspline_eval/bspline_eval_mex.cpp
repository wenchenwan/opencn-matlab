//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_eval_mex.cpp
//
//  Code generation for function 'bspline_eval_mex'
//


// Include files
#include "bspline_eval_mex.h"
#include "_coder_bspline_eval_mex_mex.h"
#include "rt_nonfinite.h"
#include "src/c_spline.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,// bFirstTime
  false,                               // bInitialized
  131594U,                             // fVersionInfo
  NULL,                                // fErrorFunction
  "bspline_eval_mex",                  // fFunctionName
  NULL,                                // fRTCallStack
  false,                               // bDebugMode
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },// fSigWrd
  NULL                                 // fSigMem
};

static emlrtMCInfo emlrtMCI = { 60,    // lineNo
  18,                                  // colNo
  "fprintf",                           // fName
  "/home/peter/apps/MATLAB/R2020a/toolbox/eml/lib/matlab/iofun/fprintf.m"// pName 
};

// Function Declarations
namespace ocn
{
  static real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static const mxArray *b_emlrt_marshallOut(const struct0_T *u);
  static int32_T c_emlrt_marshallIn(const mxArray *degree, const char_T
    *identifier);
  static int32_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static void e_emlrt_marshallIn(const mxArray *breakpoints, const char_T
    *identifier, coder::array<real_T, 2U> &y);
  static real_T emlrt_marshallIn(const mxArray *a__output_of_feval_, const
    char_T *identifier);
  static const mxArray *emlrt_marshallOut(const real_T u);
  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static const mxArray *feval(const mxArray *b, const mxArray *c, const mxArray *
    d, const mxArray *e, emlrtMCInfo *location);
  static void g_emlrt_marshallIn(const mxArray *Bl, const char_T *identifier,
    struct0_T *y);
  static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, struct0_T *y);
  static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static uint64_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId);
  static void k_emlrt_marshallIn(const mxArray *coeffs, const char_T *identifier,
    coder::array<real_T, 1U> &y);
  static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y);
  static real_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
    msgId);
  static int32_T n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId);
  static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static void p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static uint64_T q_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId);
  static void r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret);
}

// Function Definitions
namespace ocn
{
  static real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    real_T y;
    y = m_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static const mxArray *b_emlrt_marshallOut(const struct0_T *u)
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

  static int32_T c_emlrt_marshallIn(const mxArray *degree, const char_T
    *identifier)
  {
    int32_T y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = d_emlrt_marshallIn(emlrtAlias(degree), &thisId);
    emlrtDestroyArray(&degree);
    return y;
  }

  static int32_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    int32_T y;
    y = n_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void e_emlrt_marshallIn(const mxArray *breakpoints, const char_T
    *identifier, coder::array<real_T, 2U> &y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    f_emlrt_marshallIn(emlrtAlias(breakpoints), &thisId, y);
    emlrtDestroyArray(&breakpoints);
  }

  static real_T emlrt_marshallIn(const mxArray *a__output_of_feval_, const
    char_T *identifier)
  {
    real_T y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = b_emlrt_marshallIn(emlrtAlias(a__output_of_feval_), &thisId);
    emlrtDestroyArray(&a__output_of_feval_);
    return y;
  }

  static const mxArray *emlrt_marshallOut(const real_T u)
  {
    const mxArray *y;
    const mxArray *m;
    y = NULL;
    m = emlrtCreateDoubleScalar(u);
    emlrtAssign(&y, m);
    return y;
  }

  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static const mxArray *feval(const mxArray *b, const mxArray *c, const mxArray *
    d, const mxArray *e, emlrtMCInfo *location)
  {
    const mxArray *pArrays[4];
    const mxArray *m;
    pArrays[0] = b;
    pArrays[1] = c;
    pArrays[2] = d;
    pArrays[3] = e;
    return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 4, &pArrays[0],
      "feval", true, location);
  }

  static void g_emlrt_marshallIn(const mxArray *Bl, const char_T *identifier,
    struct0_T *y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    h_emlrt_marshallIn(emlrtAlias(Bl), &thisId, y);
    emlrtDestroyArray(&Bl);
  }

  static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
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
    y->ncoeff = d_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 0, "ncoeff")), &thisId);
    thisId.fIdentifier = "breakpoints";
    i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      1, "breakpoints")), &thisId, y->breakpoints);
    thisId.fIdentifier = "handle";
    y->handle = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 2, "handle")), &thisId);
    thisId.fIdentifier = "degree";
    y->degree = d_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 3, "degree")), &thisId);
    emlrtDestroyArray(&u);
  }

  static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    p_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static uint64_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId)
  {
    uint64_T y;
    y = q_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void k_emlrt_marshallIn(const mxArray *coeffs, const char_T *identifier,
    coder::array<real_T, 1U> &y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    l_emlrt_marshallIn(emlrtAlias(coeffs), &thisId, y);
    emlrtDestroyArray(&coeffs);
  }

  static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y)
  {
    r_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static real_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
    msgId)
  {
    real_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
      &dims);
    ret = *(real_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  static int32_T n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

  static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

  static void p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

  static uint64_T q_emlrt_marshallIn(const mxArray *src, const
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

  static void r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret)
  {
    static const int32_T dims[1] = { -1 };

    const boolean_T bv[1] = { true };

    int32_T iv[1];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      1U, dims, &bv[0], iv);
    ret.prealloc(iv[0]);
    ret.set_size(iv[0]);
    ret.set(((real_T *)emlrtMxGetData(src)), ret.size(0));
    emlrtDestroyArray(&src);
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
    degree = c_emlrt_marshallIn(emlrtAliasP(prhs[0]), "degree");
    breakpoints.no_free();
    e_emlrt_marshallIn(emlrtAlias(prhs[1]), "breakpoints", breakpoints);

    // Invoke the target function
    bspline_create(degree, breakpoints, &Bl);

    // Marshall function outputs
    plhs[0] = b_emlrt_marshallOut(&Bl);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void bspline_eval(const struct0_T *Bl, const coder::array<real_T, 1U> &coeffs,
                    real_T *x, real_T *xd, real_T *xdd, real_T *xddd)
  {
    const mxArray *y;
    static const int32_T iv[2] = { 1, 7 };

    static const int32_T iv1[2] = { 1, 7 };

    static const char_T u[7] = { 'f', 'p', 'r', 'i', 'n', 't', 'f' };

    real_T X[4];
    const mxArray *b_y;
    static const int32_T iv2[2] = { 1, 35 };

    static const int32_T iv3[2] = { 1, 35 };

    static const char_T b_u[35] = { 'E', 'R', 'R', 'O', 'R', ':', ' ', 'C', '_',
      'B', 'S', 'P', 'L', 'I', 'N', 'E', '_', 'E', 'V', 'A', 'L', ':', ' ', 'X',
      ' ', '<', ' ', '0', ' ', '(', '%', 'f', ')', '\\', 'n' };

    static const char_T c_u[35] = { 'E', 'R', 'R', 'O', 'R', ':', ' ', 'C', '_',
      'B', 'S', 'P', 'L', 'I', 'N', 'E', '_', 'E', 'V', 'A', 'L', ':', ' ', 'X',
      ' ', '>', ' ', '1', ' ', '(', '%', 'f', ')', '\\', 'n' };

    //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]); 
    if (*x < 0.0) {
      const mxArray *m;
      const mxArray *m2;
      y = NULL;
      m = emlrtCreateCharArray(2, &iv[0]);
      emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
      emlrtAssign(&y, m);
      b_y = NULL;
      m2 = emlrtCreateCharArray(2, &iv2[0]);
      emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 35, m2, &b_u[0]);
      emlrtAssign(&b_y, m2);
      emlrt_marshallIn(feval(y, emlrt_marshallOut(1.0), b_y, emlrt_marshallOut
        (*x), &emlrtMCI), "<output of feval>");
      *x = 0.0;
    } else {
      if (*x > 1.0) {
        const mxArray *m1;
        const mxArray *m3;
        y = NULL;
        m1 = emlrtCreateCharArray(2, &iv1[0]);
        emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m1, &u[0]);
        emlrtAssign(&y, m1);
        b_y = NULL;
        m3 = emlrtCreateCharArray(2, &iv3[0]);
        emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 35, m3, &c_u[0]);
        emlrtAssign(&b_y, m3);
        emlrt_marshallIn(feval(y, emlrt_marshallOut(1.0), b_y, emlrt_marshallOut
          (*x), &emlrtMCI), "<output of feval>");
        *x = 1.0;
      }
    }

    c_bspline_eval(&Bl->handle, &(((coder::array<real_T, 1U> *)&coeffs)->data())
                   [0], *x, &X[0]);
    *x = X[0];
    *xd = X[1];
    *xdd = X[2];
    *xddd = X[3];
  }

  void bspline_eval_api(const mxArray * const prhs[3], int32_T nlhs, const
                        mxArray *plhs[4])
  {
    struct0_T Bl;
    coder::array<real_T, 1U> coeffs;
    real_T x;
    real_T xd;
    real_T xdd;
    real_T xddd;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    g_emlrt_marshallIn(emlrtAliasP(prhs[0]), "Bl", &Bl);
    coeffs.no_free();
    k_emlrt_marshallIn(emlrtAlias(prhs[1]), "coeffs", coeffs);
    x = emlrt_marshallIn(emlrtAliasP(prhs[2]), "x");

    // Invoke the target function
    bspline_eval(&Bl, coeffs, &x, &xd, &xdd, &xddd);

    // Marshall function outputs
    plhs[0] = emlrt_marshallOut(x);
    if (nlhs > 1) {
      plhs[1] = emlrt_marshallOut(xd);
    }

    if (nlhs > 2) {
      plhs[2] = emlrt_marshallOut(xdd);
    }

    if (nlhs > 3) {
      plhs[3] = emlrt_marshallOut(xddd);
    }

    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }
}

void bspline_eval_mex_atexit()
{
  ocn::mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

namespace ocn
{
  void bspline_eval_mex_initialize()
  {
    mex_InitInfAndNan();
    mexFunctionCreateRootTLS();
    emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
    emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
    emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
  }

  void bspline_eval_mex_terminate()
  {
    emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  }
}

// End of code generation (bspline_eval_mex.cpp)
