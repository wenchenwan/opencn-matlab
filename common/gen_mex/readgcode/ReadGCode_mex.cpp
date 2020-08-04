//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ReadGCode_mex.cpp
//
//  Code generation for function 'ReadGCode_mex'
//


// Include files
#include "ReadGCode_mex.h"
#include "_coder_ReadGCode_mex_mex.h"
#include "blas.h"
#include "cpp_interp.hpp"
#include "mwmathutil.h"
#include "rt_nonfinite.h"
#include <string.h>

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,// bFirstTime
  false,                               // bInitialized
  131594U,                             // fVersionInfo
  NULL,                                // fErrorFunction
  "ReadGCode_mex",                     // fFunctionName
  NULL,                                // fRTCallStack
  false,                               // bDebugMode
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },// fSigWrd
  NULL                                 // fSigMem
};

static const char * sv[5] = { "None", "Line", "Helix", "Spline", "TransP5" };

static const int32_T iv[5] = { 0, 1, 2, 3, 4 };

static const char * sv1[4] = { "NN", "ZN", "NZ", "ZZ" };

static const int32_T iv1[4] = { 0, 1, 2, 3 };

// Function Declarations
namespace ocn
{
  static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, real_T ret[3]);
  static ReadGCodeCmd b_emlrt_marshallIn(const mxArray *u, const
    emlrtMsgIdentifier *parentId);
  static const mxArray *b_emlrt_marshallOut(const CurvStruct *u);
  static void bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, real_T ret[6][3]);
  static void c_emlrt_marshallIn(const mxArray *filename, const char_T
    *identifier, char_T y_data[], int32_T y_size[2]);
  static const mxArray *c_emlrt_marshallOut(const coder::array<real_T, 2U> &u);
  static int32_T cb_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId);
  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, char_T y_data[], int32_T y_size[2]);
  static boolean_T db_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId);
  static real_T (*e_emlrt_marshallIn(const mxArray *P0, const char_T *identifier))
    [3];
  static void eb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret);
  static ReadGCodeCmd emlrt_marshallIn(const mxArray *cmd, const char_T
    *identifier);
  static const mxArray *emlrt_marshallOut(const int32_T u);
  static real_T (*f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId))[3];
  static void fb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static real_T g_emlrt_marshallIn(const mxArray *FeedRate, const char_T
    *identifier);
  static uint64_T gb_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId);
  static real_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static ZSpdMode i_emlrt_marshallIn(const mxArray *b_ZSpdMode, const char_T
    *identifier);
  static ZSpdMode j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId);
  static void k_emlrt_marshallIn(const mxArray *Curv, const char_T *identifier,
    CurvStruct *y);
  static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, CurvStruct *y);
  static CurveType m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, real_T y[3]);
  static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, real_T y[6][3]);
  static int32_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static boolean_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static void r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y);
  static void s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, SplineStruct *y);
  static void t_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, SplineBase *y);
  static uint64_T v_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId);
  static void w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, char_T ret_data[], int32_T ret_size[2]);
  static real_T (*x_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId))[3];
  static real_T y_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
    msgId);
}

// Function Definitions
namespace ocn
{
  static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, real_T ret[3])
  {
    static const int32_T dims[1] = { 3 };

    real_T (*r)[3];
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
      dims);
    r = (real_T (*)[3])emlrtMxGetData(src);
    ret[0] = (*r)[0];
    ret[1] = (*r)[1];
    ret[2] = (*r)[2];
    emlrtDestroyArray(&src);
  }

  static ReadGCodeCmd b_emlrt_marshallIn(const mxArray *u, const
    emlrtMsgIdentifier *parentId)
  {
    ReadGCodeCmd y;
    static const char * enumNames[2] = { "Load", "Read" };

    static const int32_T enumValues[2] = { 1, 2 };

    static const int32_T dims = 0;
    emlrtCheckEnumR2012b(emlrtRootTLSGlobal, "ReadGCodeCmd", 2, enumNames,
                         enumValues);
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, parentId, u, "ReadGCodeCmd",
      false, 0U, &dims);
    y = static_cast<ReadGCodeCmd>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
  }

  static const mxArray *b_emlrt_marshallOut(const CurvStruct *u)
  {
    const mxArray *y;
    static const char * b_sv[23] = { "Type", "zspdmode", "P0", "P1", "evec",
      "theta", "pitch", "CoeffP5", "sp_index", "FeedRate", "MaxConstantFeedRate",
      "i_begin_sp", "i_end_sp", "gcode_source_line", "index_smooth",
      "UseConstJerk", "ConstJerk", "ConstJerkMaxIterations", "Coeff", "a_param",
      "b_param", "end_flag", "sp" };

    const mxArray *b_y;
    const mxArray *m;
    static const int32_T b_iv[1] = { 3 };

    real_T *pData;
    static const int32_T b_iv1[1] = { 3 };

    static const int32_T iv2[1] = { 3 };

    const mxArray *m1;
    const mxArray *m2;
    static const int32_T iv3[2] = { 3, 6 };

    int32_T i;
    int32_T b_i;
    static const char * b_sv1[5] = { "CoeffX", "CoeffY", "CoeffZ", "Bl", "knots"
    };

    const mxArray *c_y;
    static const char * sv2[4] = { "ncoeff", "breakpoints", "handle", "degree" };

    const mxArray *d_y;
    y = NULL;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 23, &b_sv[0]));
    b_y = NULL;
    m = NULL;
    emlrtCheckEnumR2012b(emlrtRootTLSGlobal, "CurveType", 5, sv, iv);
    emlrtAssign(&m, emlrt_marshallOut(static_cast<int32_T>(u->Type)));
    emlrtAssign(&b_y, emlrtCreateEnumR2012b(emlrtRootTLSGlobal, "CurveType", m));
    emlrtDestroyArray(&m);
    emlrtSetFieldR2017b(y, 0, "Type", b_y, 0);
    b_y = NULL;
    m = NULL;
    emlrtCheckEnumR2012b(emlrtRootTLSGlobal, "ZSpdMode", 4, sv1, iv1);
    emlrtAssign(&m, emlrt_marshallOut(static_cast<int32_T>(u->zspdmode)));
    emlrtAssign(&b_y, emlrtCreateEnumR2012b(emlrtRootTLSGlobal, "ZSpdMode", m));
    emlrtDestroyArray(&m);
    emlrtSetFieldR2017b(y, 0, "zspdmode", b_y, 1);
    b_y = NULL;
    m = emlrtCreateNumericArray(1, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    pData[0] = u->P0[0];
    pData[1] = u->P0[1];
    pData[2] = u->P0[2];
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "P0", b_y, 2);
    b_y = NULL;
    m = emlrtCreateNumericArray(1, &b_iv1[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    pData[0] = u->P1[0];
    pData[1] = u->P1[1];
    pData[2] = u->P1[2];
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "P1", b_y, 3);
    b_y = NULL;
    m = emlrtCreateNumericArray(1, &iv2[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    pData[0] = u->evec[0];
    pData[1] = u->evec[1];
    pData[2] = u->evec[2];
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "evec", b_y, 4);
    b_y = NULL;
    m1 = emlrtCreateDoubleScalar(u->theta);
    emlrtAssign(&b_y, m1);
    emlrtSetFieldR2017b(y, 0, "theta", b_y, 5);
    b_y = NULL;
    m2 = emlrtCreateDoubleScalar(u->pitch);
    emlrtAssign(&b_y, m2);
    emlrtSetFieldR2017b(y, 0, "pitch", b_y, 6);
    b_y = NULL;
    m = emlrtCreateNumericArray(2, &iv3[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (b_i = 0; b_i < 6; b_i++) {
      pData[i] = u->CoeffP5[b_i][0];
      i++;
      pData[i] = u->CoeffP5[b_i][1];
      i++;
      pData[i] = u->CoeffP5[b_i][2];
      i++;
    }

    const mxArray *m3;
    const mxArray *m4;
    const mxArray *m5;
    const mxArray *m6;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "CoeffP5", b_y, 7);
    emlrtSetFieldR2017b(y, 0, "sp_index", emlrt_marshallOut(u->sp_index), 8);
    b_y = NULL;
    m3 = emlrtCreateDoubleScalar(u->FeedRate);
    emlrtAssign(&b_y, m3);
    emlrtSetFieldR2017b(y, 0, "FeedRate", b_y, 9);
    b_y = NULL;
    m4 = emlrtCreateDoubleScalar(u->MaxConstantFeedRate);
    emlrtAssign(&b_y, m4);
    emlrtSetFieldR2017b(y, 0, "MaxConstantFeedRate", b_y, 10);
    emlrtSetFieldR2017b(y, 0, "i_begin_sp", emlrt_marshallOut(u->i_begin_sp), 11);
    emlrtSetFieldR2017b(y, 0, "i_end_sp", emlrt_marshallOut(u->i_end_sp), 12);
    emlrtSetFieldR2017b(y, 0, "gcode_source_line", emlrt_marshallOut
                        (u->gcode_source_line), 13);
    emlrtSetFieldR2017b(y, 0, "index_smooth", emlrt_marshallOut(u->index_smooth),
                        14);
    b_y = NULL;
    m5 = emlrtCreateLogicalScalar(u->UseConstJerk);
    emlrtAssign(&b_y, m5);
    emlrtSetFieldR2017b(y, 0, "UseConstJerk", b_y, 15);
    b_y = NULL;
    m6 = emlrtCreateDoubleScalar(u->ConstJerk);
    emlrtAssign(&b_y, m6);
    emlrtSetFieldR2017b(y, 0, "ConstJerk", b_y, 16);
    emlrtSetFieldR2017b(y, 0, "ConstJerkMaxIterations", emlrt_marshallOut
                        (u->ConstJerkMaxIterations), 17);
    b_y = NULL;
    m = emlrtCreateNumericArray(1, ((coder::array<real_T, 1U> *)&u->Coeff)->size
      (), mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (b_i = 0; b_i < u->Coeff.size(0); b_i++) {
      pData[i] = u->Coeff[b_i];
      i++;
    }

    const mxArray *m7;
    const mxArray *m8;
    const mxArray *m9;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, "Coeff", b_y, 18);
    b_y = NULL;
    m7 = emlrtCreateDoubleScalar(u->a_param);
    emlrtAssign(&b_y, m7);
    emlrtSetFieldR2017b(y, 0, "a_param", b_y, 19);
    b_y = NULL;
    m8 = emlrtCreateDoubleScalar(u->b_param);
    emlrtAssign(&b_y, m8);
    emlrtSetFieldR2017b(y, 0, "b_param", b_y, 20);
    b_y = NULL;
    m9 = emlrtCreateLogicalScalar(u->end_flag);
    emlrtAssign(&b_y, m9);
    emlrtSetFieldR2017b(y, 0, "end_flag", b_y, 21);
    b_y = NULL;
    emlrtAssign(&b_y, emlrtCreateStructMatrix(1, 1, 5, &b_sv1[0]));
    emlrtSetFieldR2017b(b_y, 0, "CoeffX", c_emlrt_marshallOut(u->sp.CoeffX), 0);
    emlrtSetFieldR2017b(b_y, 0, "CoeffY", c_emlrt_marshallOut(u->sp.CoeffY), 1);
    emlrtSetFieldR2017b(b_y, 0, "CoeffZ", c_emlrt_marshallOut(u->sp.CoeffZ), 2);
    c_y = NULL;
    emlrtAssign(&c_y, emlrtCreateStructMatrix(1, 1, 4, &sv2[0]));
    emlrtSetFieldR2017b(c_y, 0, "ncoeff", emlrt_marshallOut(u->sp.Bl.ncoeff), 0);
    emlrtSetFieldR2017b(c_y, 0, "breakpoints", c_emlrt_marshallOut
                        (u->sp.Bl.breakpoints), 1);
    d_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *(uint64_T *)emlrtMxGetData(m) = u->sp.Bl.handle;
    emlrtAssign(&d_y, m);
    emlrtSetFieldR2017b(c_y, 0, "handle", d_y, 2);
    emlrtSetFieldR2017b(c_y, 0, "degree", emlrt_marshallOut(u->sp.Bl.degree), 3);
    emlrtSetFieldR2017b(b_y, 0, "Bl", c_y, 3);
    emlrtSetFieldR2017b(b_y, 0, "knots", c_emlrt_marshallOut(u->sp.knots), 4);
    emlrtSetFieldR2017b(y, 0, "sp", b_y, 22);
    return y;
  }

  static void bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, real_T ret[6][3])
  {
    static const int32_T dims[2] = { 3, 6 };

    real_T (*r)[6][3];
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
      dims);
    r = (real_T (*)[6][3])emlrtMxGetData(src);
    for (int32_T i = 0; i < 6; i++) {
      ret[i][0] = (*r)[i][0];
      ret[i][1] = (*r)[i][1];
      ret[i][2] = (*r)[i][2];
    }

    emlrtDestroyArray(&src);
  }

  static void c_emlrt_marshallIn(const mxArray *filename, const char_T
    *identifier, char_T y_data[], int32_T y_size[2])
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    d_emlrt_marshallIn(emlrtAlias(filename), &thisId, y_data, y_size);
    emlrtDestroyArray(&filename);
  }

  static const mxArray *c_emlrt_marshallOut(const coder::array<real_T, 2U> &u)
  {
    const mxArray *y;
    int32_T b_iv[2];
    const mxArray *m;
    real_T *pData;
    int32_T i;
    y = NULL;
    b_iv[0] = u.size(0);
    b_iv[1] = u.size(1);
    m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i = 0; b_i < u.size(1); b_i++) {
      pData[i] = u[b_i];
      i++;
    }

    emlrtAssign(&y, m);
    return y;
  }

  static int32_T cb_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId)
  {
    int32_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 0U,
      &dims);
    ret = *(int32_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, char_T y_data[], int32_T y_size[2])
  {
    w_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
    emlrtDestroyArray(&u);
  }

  static boolean_T db_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId)
  {
    boolean_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 0U,
      &dims);
    ret = *emlrtMxGetLogicals(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  static real_T (*e_emlrt_marshallIn(const mxArray *P0, const char_T *identifier))
    [3]
  {
    real_T (*y)[3];
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = f_emlrt_marshallIn(emlrtAlias(P0), &thisId);
    emlrtDestroyArray(&P0);
    return y;
  }
    static void eb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret)
{
    static const int32_T dims[1] = { -1 };

    const boolean_T bv[1] = { true };

    int32_T b_iv[1];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      1U, dims, &bv[0], b_iv);
    ret.set_size(b_iv[0]);
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &(ret.data())[0], 8, false);
    emlrtDestroyArray(&src);
  }

  static ReadGCodeCmd emlrt_marshallIn(const mxArray *cmd, const char_T
    *identifier)
  {
    ReadGCodeCmd y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = b_emlrt_marshallIn(emlrtAlias(cmd), &thisId);
    emlrtDestroyArray(&cmd);
    return y;
  }

  static const mxArray *emlrt_marshallOut(const int32_T u)
  {
    const mxArray *y;
    const mxArray *m;
    y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u;
    emlrtAssign(&y, m);
    return y;
  }

  static real_T (*f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId))[3]
  {
    real_T (*y)[3];
    y = x_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }
    static void fb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret)
{
    static const int32_T dims[2] = { 1, -1 };

    const boolean_T bv[2] = { false, true };

    int32_T b_iv[2];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      2U, dims, &bv[0], b_iv);
    ret.set_size(b_iv[0], b_iv[1]);
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &(ret.data())[0], 8, false);
    emlrtDestroyArray(&src);
  }

  static real_T g_emlrt_marshallIn(const mxArray *FeedRate, const char_T
    *identifier)
  {
    real_T y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = h_emlrt_marshallIn(emlrtAlias(FeedRate), &thisId);
    emlrtDestroyArray(&FeedRate);
    return y;
  }

  static uint64_T gb_emlrt_marshallIn(const mxArray *src, const
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

  static real_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    real_T y;
    y = y_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static ZSpdMode i_emlrt_marshallIn(const mxArray *b_ZSpdMode, const char_T
    *identifier)
  {
    ZSpdMode y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    y = j_emlrt_marshallIn(emlrtAlias(b_ZSpdMode), &thisId);
    emlrtDestroyArray(&b_ZSpdMode);
    return y;
  }

  static ZSpdMode j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId)
  {
    ZSpdMode y;
    static const int32_T dims = 0;
    emlrtCheckEnumR2012b(emlrtRootTLSGlobal, "ZSpdMode", 4, sv1, iv1);
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, parentId, u, "ZSpdMode", false,
      0U, &dims);
    y = static_cast<ZSpdMode>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
  }

  static void k_emlrt_marshallIn(const mxArray *Curv, const char_T *identifier,
    CurvStruct *y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    l_emlrt_marshallIn(emlrtAlias(Curv), &thisId, y);
    emlrtDestroyArray(&Curv);
  }

  static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, CurvStruct *y)
  {
    emlrtMsgIdentifier thisId;
    static const char * fieldNames[23] = { "Type", "zspdmode", "P0", "P1",
      "evec", "theta", "pitch", "CoeffP5", "sp_index", "FeedRate",
      "MaxConstantFeedRate", "i_begin_sp", "i_end_sp", "gcode_source_line",
      "index_smooth", "UseConstJerk", "ConstJerk", "ConstJerkMaxIterations",
      "Coeff", "a_param", "b_param", "end_flag", "sp" };

    static const int32_T dims = 0;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 23, fieldNames, 0U,
      &dims);
    thisId.fIdentifier = "Type";
    y->Type = m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 0, "Type")), &thisId);
    thisId.fIdentifier = "zspdmode";
    y->zspdmode = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 1, "zspdmode")), &thisId);
    thisId.fIdentifier = "P0";
    n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      2, "P0")), &thisId, y->P0);
    thisId.fIdentifier = "P1";
    n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      3, "P1")), &thisId, y->P1);
    thisId.fIdentifier = "evec";
    n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      4, "evec")), &thisId, y->evec);
    thisId.fIdentifier = "theta";
    y->theta = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 5, "theta")), &thisId);
    thisId.fIdentifier = "pitch";
    y->pitch = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 6, "pitch")), &thisId);
    thisId.fIdentifier = "CoeffP5";
    o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      7, "CoeffP5")), &thisId, y->CoeffP5);
    thisId.fIdentifier = "sp_index";
    y->sp_index = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 8, "sp_index")), &thisId);
    thisId.fIdentifier = "FeedRate";
    y->FeedRate = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 9, "FeedRate")), &thisId);
    thisId.fIdentifier = "MaxConstantFeedRate";
    y->MaxConstantFeedRate = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 10, "MaxConstantFeedRate")), &thisId);
    thisId.fIdentifier = "i_begin_sp";
    y->i_begin_sp = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 11, "i_begin_sp")), &thisId);
    thisId.fIdentifier = "i_end_sp";
    y->i_end_sp = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 12, "i_end_sp")), &thisId);
    thisId.fIdentifier = "gcode_source_line";
    y->gcode_source_line = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 13, "gcode_source_line")), &thisId);
    thisId.fIdentifier = "index_smooth";
    y->index_smooth = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 14, "index_smooth")), &thisId);
    thisId.fIdentifier = "UseConstJerk";
    y->UseConstJerk = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 15, "UseConstJerk")), &thisId);
    thisId.fIdentifier = "ConstJerk";
    y->ConstJerk = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 16, "ConstJerk")), &thisId);
    thisId.fIdentifier = "ConstJerkMaxIterations";
    y->ConstJerkMaxIterations = p_emlrt_marshallIn(emlrtAlias
      (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 17,
      "ConstJerkMaxIterations")), &thisId);
    thisId.fIdentifier = "Coeff";
    r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      18, "Coeff")), &thisId, y->Coeff);
    thisId.fIdentifier = "a_param";
    y->a_param = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 19, "a_param")), &thisId);
    thisId.fIdentifier = "b_param";
    y->b_param = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 20, "b_param")), &thisId);
    thisId.fIdentifier = "end_flag";
    y->end_flag = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 21, "end_flag")), &thisId);
    thisId.fIdentifier = "sp";
    s_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      22, "sp")), &thisId, &y->sp);
    emlrtDestroyArray(&u);
  }

  static CurveType m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    CurveType y;
    static const int32_T dims = 0;
    emlrtCheckEnumR2012b(emlrtRootTLSGlobal, "CurveType", 5, sv, iv);
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, parentId, u, "CurveType", false,
      0U, &dims);
    y = static_cast<CurveType>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
  }

  static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, real_T y[3])
  {
    ab_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, real_T y[6][3])
  {
    bb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static int32_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    int32_T y;
    y = cb_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static boolean_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    boolean_T y;
    y = db_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y)
  {
    eb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, SplineStruct *y)
  {
    emlrtMsgIdentifier thisId;
    static const char * fieldNames[5] = { "CoeffX", "CoeffY", "CoeffZ", "Bl",
      "knots" };

    static const int32_T dims = 0;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 5, fieldNames, 0U,
      &dims);
    thisId.fIdentifier = "CoeffX";
    t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      0, "CoeffX")), &thisId, y->CoeffX);
    thisId.fIdentifier = "CoeffY";
    t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      1, "CoeffY")), &thisId, y->CoeffY);
    thisId.fIdentifier = "CoeffZ";
    t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      2, "CoeffZ")), &thisId, y->CoeffZ);
    thisId.fIdentifier = "Bl";
    u_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      3, "Bl")), &thisId, &y->Bl);
    thisId.fIdentifier = "knots";
    t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      4, "knots")), &thisId, y->knots);
    emlrtDestroyArray(&u);
  }

  static void t_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    fb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, SplineBase *y)
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
    y->ncoeff = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 0, "ncoeff")), &thisId);
    thisId.fIdentifier = "breakpoints";
    t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
      1, "breakpoints")), &thisId, y->breakpoints);
    thisId.fIdentifier = "handle";
    y->handle = v_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 2, "handle")), &thisId);
    thisId.fIdentifier = "degree";
    y->degree = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
      (emlrtRootTLSGlobal, u, 0, 3, "degree")), &thisId);
    emlrtDestroyArray(&u);
  }

  static uint64_T v_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
    parentId)
  {
    uint64_T y;
    y = gb_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, char_T ret_data[], int32_T ret_size[2])
  {
    static const int32_T dims[2] = { 1, 1024 };

    const boolean_T bv[2] = { false, true };

    int32_T b_iv[2];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "char", false, 2U,
      dims, &bv[0], b_iv);
    ret_size[0] = b_iv[0];
    ret_size[1] = b_iv[1];
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, (void *)ret_data, 1, false);
    emlrtDestroyArray(&src);
  }

  static real_T (*x_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId))[3]
  {
    real_T (*ret)[3];
    static const int32_T dims[1] = { 3 };

    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
      dims);
    ret = (real_T (*)[3])emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }
    static real_T y_emlrt_marshallIn(const mxArray *src, const
    emlrtMsgIdentifier *msgId)
{
    real_T ret;
    static const int32_T dims = 0;
    emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
      &dims);
    ret = *(real_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
  }

  void ConstrCurvStructType(CurvStruct *C)
  {
    real_T dv[3];
    real_T dv1[3];
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, C);
  }

  void ConstrCurvStructType_api(int32_T, const mxArray *plhs[1])
  {
    CurvStruct r;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Invoke the target function
    // Marshall function outputs
    ConstrCurvStructType(&r);
    plhs[0] = b_emlrt_marshallOut(&r);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void ConstrHelixStruct(const real_T P0[3], const real_T P1[3], const real_T
    evec[3], real_T theta, real_T pitch, real_T FeedRate, ZSpdMode b_ZSpdMode,
    CurvStruct *b_CurvStruct)
  {
    //
    //
    //  ctxType = coder.OutputType('InitFeedoptPlan');
    b_CurvStruct->Type = CurveType_Helix;
    b_CurvStruct->zspdmode = b_ZSpdMode;
    b_CurvStruct->P0[0] = P0[0];
    b_CurvStruct->P1[0] = P1[0];
    b_CurvStruct->evec[0] = evec[0];
    b_CurvStruct->P0[1] = P0[1];
    b_CurvStruct->P1[1] = P1[1];
    b_CurvStruct->evec[1] = evec[1];
    b_CurvStruct->P0[2] = P0[2];
    b_CurvStruct->P1[2] = P1[2];
    b_CurvStruct->evec[2] = evec[2];
    b_CurvStruct->theta = theta;
    b_CurvStruct->pitch = pitch;
    for (int32_T i = 0; i < 6; i++) {
      b_CurvStruct->CoeffP5[i][0] = 0.0;
      b_CurvStruct->CoeffP5[i][1] = 0.0;
      b_CurvStruct->CoeffP5[i][2] = 0.0;
    }

    b_CurvStruct->sp_index = 1;
    b_CurvStruct->FeedRate = FeedRate;
    b_CurvStruct->MaxConstantFeedRate = 0.0;
    b_CurvStruct->i_begin_sp = 0;
    b_CurvStruct->i_end_sp = 0;
    b_CurvStruct->gcode_source_line = 0;
    b_CurvStruct->index_smooth = 0;
    b_CurvStruct->UseConstJerk = false;
    b_CurvStruct->ConstJerk = 0.0;
    b_CurvStruct->ConstJerkMaxIterations = 0;
    b_CurvStruct->Coeff.set_size(0);
    b_CurvStruct->a_param = 1.0;
    b_CurvStruct->b_param = 0.0;
    b_CurvStruct->end_flag = false;
    b_CurvStruct->sp.CoeffX.set_size(1, 1);
    b_CurvStruct->sp.CoeffX[0] = 0.0;
    b_CurvStruct->sp.CoeffY.set_size(1, 1);
    b_CurvStruct->sp.CoeffY[0] = 0.0;
    b_CurvStruct->sp.CoeffZ.set_size(1, 1);
    b_CurvStruct->sp.CoeffZ[0] = 0.0;
    b_CurvStruct->sp.Bl.ncoeff = 0;
    b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
    b_CurvStruct->sp.Bl.handle = 0UL;
    b_CurvStruct->sp.Bl.degree = 0;
    b_CurvStruct->sp.knots.set_size(1, 1);
    b_CurvStruct->sp.knots[0] = 0.0;
  }

  void ConstrHelixStructFromArcFeed(real_T p0x, real_T p0y, real_T p0z, real_T
    p1x, real_T p1y, real_T p1z, real_T cx, real_T cy, real_T cz, real_T
    rotation, const real_T evec[3], CurvStruct *b_CurvStruct)
  {
    real_T P0[3];
    real_T P1[3];
    real_T R1_idx_0;
    real_T C_idx_0;
    real_T R1_idx_1;
    real_T C_idx_1;
    real_T R1_idx_2;
    real_T C_idx_2;
    real_T R0_idx_0;
    real_T R0_idx_1;
    real_T R0_idx_2;
    real_T a_data[3];
    real_T b_data[3];
    ptrdiff_t n_t;
    ptrdiff_t incx_t;
    ptrdiff_t incy_t;
    P0[0] = p0x;
    P0[1] = p0y;
    P0[2] = p0z;
    P1[0] = p1x;
    P1[1] = p1y;
    P1[2] = p1z;
    R1_idx_0 = p0x - cx;
    C_idx_0 = p1x - cx;
    R1_idx_1 = p0y - cy;
    C_idx_1 = p1y - cy;
    R1_idx_2 = p0z - cz;
    C_idx_2 = p1z - cz;
    R0_idx_0 = evec[1] * R1_idx_2 - evec[2] * R1_idx_1;
    R0_idx_1 = evec[2] * R1_idx_0 - evec[0] * R1_idx_2;
    R0_idx_2 = evec[0] * R1_idx_1 - evec[1] * R1_idx_0;
    R1_idx_0 = evec[1] * C_idx_2 - evec[2] * C_idx_1;
    R1_idx_1 = evec[2] * C_idx_0 - evec[0] * C_idx_2;
    R1_idx_2 = evec[0] * C_idx_1 - evec[1] * C_idx_0;
    if (evec[0] > 0.5) {
      C_idx_2 = muDoubleScalarAtan2(R0_idx_2, R0_idx_1);
      C_idx_1 = muDoubleScalarAtan2(R1_idx_2, R1_idx_1);
    } else if (evec[1] > 0.5) {
      C_idx_1 = muDoubleScalarAtan2(R0_idx_2, R0_idx_0);
      C_idx_2 = muDoubleScalarAtan2(R1_idx_2, R1_idx_0);

      //      rotation = -rotation;
    } else {
      C_idx_2 = muDoubleScalarAtan2(R0_idx_1, R0_idx_0);
      C_idx_1 = muDoubleScalarAtan2(R1_idx_1, R1_idx_0);
    }

    C_idx_1 -= C_idx_2;
    a_data[0] = evec[0];
    b_data[0] = p1x;
    a_data[1] = evec[1];
    b_data[1] = p1y;
    a_data[2] = evec[2];
    b_data[2] = p1z;
    n_t = (ptrdiff_t)3;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    C_idx_2 = ddot(&n_t, &a_data[0], &incx_t, &b_data[0], &incy_t);
    a_data[0] = evec[0];
    b_data[0] = p0x;
    a_data[1] = evec[1];
    b_data[1] = p0y;
    a_data[2] = evec[2];
    b_data[2] = p0z;
    n_t = (ptrdiff_t)3;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    C_idx_0 = ddot(&n_t, &a_data[0], &incx_t, &b_data[0], &incy_t);
    if (rotation > 0.0) {
      if (C_idx_1 <= 0.0) {
        C_idx_1 += 6.2831853071795862;
      }

      C_idx_1 += (rotation - 1.0) * 2.0 * 3.1415926535897931;
    } else {
      if (C_idx_1 >= 0.0) {
        C_idx_1 -= 6.2831853071795862;
      }

      C_idx_1 += (rotation + 1.0) * 2.0 * 3.1415926535897931;
    }

    ConstrHelixStruct(P0, P1, evec, C_idx_1, (C_idx_2 - C_idx_0) / C_idx_1 * 2.0
                      * 3.1415926535897931, 1.0, ZSpdMode_NN, b_CurvStruct);
  }

  void ConstrHelixStructFromArcFeed_api(const mxArray * const prhs[11], int32_T,
    const mxArray *plhs[1])
  {
    real_T p0x;
    real_T p0y;
    real_T p0z;
    real_T p1x;
    real_T p1y;
    real_T p1z;
    real_T cx;
    real_T cy;
    real_T cz;
    real_T rotation;
    real_T (*evec)[3];
    CurvStruct b_CurvStruct;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    p0x = g_emlrt_marshallIn(emlrtAliasP(prhs[0]), "p0x");
    p0y = g_emlrt_marshallIn(emlrtAliasP(prhs[1]), "p0y");
    p0z = g_emlrt_marshallIn(emlrtAliasP(prhs[2]), "p0z");
    p1x = g_emlrt_marshallIn(emlrtAliasP(prhs[3]), "p1x");
    p1y = g_emlrt_marshallIn(emlrtAliasP(prhs[4]), "p1y");
    p1z = g_emlrt_marshallIn(emlrtAliasP(prhs[5]), "p1z");
    cx = g_emlrt_marshallIn(emlrtAliasP(prhs[6]), "cx");
    cy = g_emlrt_marshallIn(emlrtAliasP(prhs[7]), "cy");
    cz = g_emlrt_marshallIn(emlrtAliasP(prhs[8]), "cz");
    rotation = g_emlrt_marshallIn(emlrtAliasP(prhs[9]), "rotation");
    evec = e_emlrt_marshallIn(emlrtAlias(prhs[10]), "evec");

    // Invoke the target function
    ConstrHelixStructFromArcFeed(p0x, p0y, p0z, p1x, p1y, p1z, cx, cy, cz,
      rotation, *evec, &b_CurvStruct);

    // Marshall function outputs
    plhs[0] = b_emlrt_marshallOut(&b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void ConstrHelixStruct_api(const mxArray * const prhs[7], int32_T, const
    mxArray *plhs[1])
  {
    real_T (*P0)[3];
    real_T (*P1)[3];
    real_T (*evec)[3];
    real_T theta;
    real_T pitch;
    real_T FeedRate;
    ZSpdMode b_ZSpdMode;
    CurvStruct b_CurvStruct;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    P0 = e_emlrt_marshallIn(emlrtAlias(prhs[0]), "P0");
    P1 = e_emlrt_marshallIn(emlrtAlias(prhs[1]), "P1");
    evec = e_emlrt_marshallIn(emlrtAlias(prhs[2]), "evec");
    theta = g_emlrt_marshallIn(emlrtAliasP(prhs[3]), "theta");
    pitch = g_emlrt_marshallIn(emlrtAliasP(prhs[4]), "pitch");
    FeedRate = g_emlrt_marshallIn(emlrtAliasP(prhs[5]), "FeedRate");
    b_ZSpdMode = i_emlrt_marshallIn(emlrtAliasP(prhs[6]), "ZSpdMode");

    // Invoke the target function
    ConstrHelixStruct(*P0, *P1, *evec, theta, pitch, FeedRate, b_ZSpdMode,
                      &b_CurvStruct);

    // Marshall function outputs
    plhs[0] = b_emlrt_marshallOut(&b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void ConstrLineStruct(const real_T P0[3], const real_T P1[3], real_T FeedRate,
                        ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct)
  {
    //
    //
    //  ctxType = coder.OutputType('InitFeedoptPlan');
    b_CurvStruct->Type = CurveType_Line;
    b_CurvStruct->zspdmode = b_ZSpdMode;
    b_CurvStruct->P0[0] = P0[0];
    b_CurvStruct->P1[0] = P1[0];
    b_CurvStruct->evec[0] = 0.0;
    b_CurvStruct->P0[1] = P0[1];
    b_CurvStruct->P1[1] = P1[1];
    b_CurvStruct->evec[1] = 0.0;
    b_CurvStruct->P0[2] = P0[2];
    b_CurvStruct->P1[2] = P1[2];
    b_CurvStruct->evec[2] = 0.0;
    b_CurvStruct->theta = 0.0;
    b_CurvStruct->pitch = 0.0;
    for (int32_T i = 0; i < 6; i++) {
      b_CurvStruct->CoeffP5[i][0] = 0.0;
      b_CurvStruct->CoeffP5[i][1] = 0.0;
      b_CurvStruct->CoeffP5[i][2] = 0.0;
    }

    b_CurvStruct->sp_index = 1;
    b_CurvStruct->FeedRate = FeedRate;
    b_CurvStruct->MaxConstantFeedRate = 0.0;
    b_CurvStruct->i_begin_sp = 0;
    b_CurvStruct->i_end_sp = 0;
    b_CurvStruct->gcode_source_line = 0;
    b_CurvStruct->index_smooth = 0;
    b_CurvStruct->UseConstJerk = false;
    b_CurvStruct->ConstJerk = 0.0;
    b_CurvStruct->ConstJerkMaxIterations = 0;
    b_CurvStruct->Coeff.set_size(0);
    b_CurvStruct->a_param = 1.0;
    b_CurvStruct->b_param = 0.0;
    b_CurvStruct->end_flag = false;
    b_CurvStruct->sp.CoeffX.set_size(1, 1);
    b_CurvStruct->sp.CoeffX[0] = 0.0;
    b_CurvStruct->sp.CoeffY.set_size(1, 1);
    b_CurvStruct->sp.CoeffY[0] = 0.0;
    b_CurvStruct->sp.CoeffZ.set_size(1, 1);
    b_CurvStruct->sp.CoeffZ[0] = 0.0;
    b_CurvStruct->sp.Bl.ncoeff = 0;
    b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
    b_CurvStruct->sp.Bl.handle = 0UL;
    b_CurvStruct->sp.Bl.degree = 0;
    b_CurvStruct->sp.knots.set_size(1, 1);
    b_CurvStruct->sp.knots[0] = 0.0;
  }

  void ConstrLineStruct_api(const mxArray * const prhs[4], int32_T, const
    mxArray *plhs[1])
  {
    real_T (*P0)[3];
    real_T (*P1)[3];
    real_T FeedRate;
    ZSpdMode b_ZSpdMode;
    CurvStruct b_CurvStruct;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    P0 = e_emlrt_marshallIn(emlrtAlias(prhs[0]), "P0");
    P1 = e_emlrt_marshallIn(emlrtAlias(prhs[1]), "P1");
    FeedRate = g_emlrt_marshallIn(emlrtAliasP(prhs[2]), "FeedRate");
    b_ZSpdMode = i_emlrt_marshallIn(emlrtAliasP(prhs[3]), "ZSpdMode");

    // Invoke the target function
    ConstrLineStruct(*P0, *P1, FeedRate, b_ZSpdMode, &b_CurvStruct);

    // Marshall function outputs
    plhs[0] = b_emlrt_marshallOut(&b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy)
  {
    *Copy = *Curv;
  }

  void CopyCurvStruct_api(const mxArray * const prhs[1], int32_T, const mxArray *
    plhs[1])
  {
    CurvStruct Curv;
    CurvStruct r;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    k_emlrt_marshallIn(emlrtAliasP(prhs[0]), "Curv", &Curv);

    // Invoke the target function
    // Marshall function outputs
    CopyCurvStruct(&Curv, &r);
    plhs[0] = b_emlrt_marshallOut(&r);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void ReadGCode(ReadGCodeCmd cmd, const char_T filename_data[], const int32_T
                 filename_size[2], int32_T *status, CurvStruct *b_CurvStruct)
  {
    real_T dv[3];
    real_T dv1[3];
    char_T tmp_data[1025];

    //  coder.extrinsic('ReadGCode_mex');
    //  Wrapper for pulling the next gcode line from the interpreter
    dv[0] = 1.0;
    dv1[0] = 4.0;
    dv[1] = 2.0;
    dv1[1] = 5.0;
    dv[2] = 3.0;
    dv1[2] = 6.0;
    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, b_CurvStruct);
    if (cmd == ReadGCodeCmd_Load) {
      int32_T is_loaded;
      is_loaded = filename_size[1];
      if (0 <= is_loaded - 1) {
        memcpy(&tmp_data[0], &filename_data[0], is_loaded * sizeof(char_T));
      }

      tmp_data[filename_size[1]] = '\x00';
      *status = cpp_interp_init(&tmp_data[0]);
    } else {
      int32_T is_loaded;
      is_loaded = cpp_interp_loaded();
      if (is_loaded != 0) {
        *status = cpp_interp_read(b_CurvStruct);
      } else {
        *status = 0;
      }
    }
  }

  void ReadGCode_api(const mxArray * const prhs[2], int32_T nlhs, const mxArray *
                     plhs[2])
  {
    ReadGCodeCmd cmd;
    char_T filename_data[1024];
    int32_T filename_size[2];
    int32_T status;
    CurvStruct b_CurvStruct;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

    // Marshall function inputs
    cmd = emlrt_marshallIn(emlrtAliasP(prhs[0]), "cmd");
    c_emlrt_marshallIn(emlrtAliasP(prhs[1]), "filename", filename_data,
                       filename_size);

    // Invoke the target function
    ReadGCode(cmd, filename_data, filename_size, &status, &b_CurvStruct);

    // Marshall function outputs
    plhs[0] = emlrt_marshallOut(status);
    if (nlhs > 1) {
      plhs[1] = b_emlrt_marshallOut(&b_CurvStruct);
    }

    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }
}

void ReadGCode_mex_atexit()
{
  ocn::mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

namespace ocn
{
  void ReadGCode_mex_initialize()
  {
    mex_InitInfAndNan();
    mexFunctionCreateRootTLS();
    emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
    emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
    emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
  }

  void ReadGCode_mex_terminate()
  {
    emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  }
}

// End of code generation (ReadGCode_mex.cpp)
