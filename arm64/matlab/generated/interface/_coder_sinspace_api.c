/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_sinspace_api.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 29-Mar-2021 16:21:48
 */

/* Include Files */
#include "_coder_sinspace_api.h"
#include "_coder_sinspace_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "sinspace",                          /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

static const char * sv[8] = { "Init", "GCode", "Check", "Compress", "Smooth",
  "Split", "Opt", "Finished" };

static const int32_T iv[8] = { 0, 1, 2, 3, 4, 5, 6, 67 };

static const char * sv1[4] = { "Success", "SmoothingFailed", "SplittingFailed",
  "OptimizationFailed" };

static const int32_T iv1[4] = { 0, 1, 2, 3 };

static const char * sv2[2] = { "ptr", "value_type" };

static const char * sv3[2] = { "queue_coder", "queue_coder" };

static const char * sv4[5] = { "None", "Line", "Helix", "Spline", "TransP5" };

static const int32_T iv2[5] = { 0, 1, 2, 3, 4 };

static const char * sv5[4] = { "NN", "ZN", "NZ", "ZZ" };

static const char * sv6[3] = { "u", "go_next", "dt" };

static const char * sv7[3] = { "ResampleStateClass", "ResampleStateClass",
  "ResampleStateClass" };

/* Function Declarations */
static FeedoptPlanError ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *
  u, const emlrtMsgIdentifier *parentId);
static uint64_T ac_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp, const
  FeedoptConfig *u);
static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void bc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[3]);
static int32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *N, const
  char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const boolean_T u);
static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *b_CurvStruct, const char_T *identifier, CurvStruct *y);
static void cc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[6][3]);
static int32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *d_emlrt_marshallOut(const real_T u[3]);
static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_vec,
  const char_T *identifier, emxArray_real_T *y);
static void dc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg, const
  char_T *identifier, FeedoptConfig *y);
static const mxArray *e_emlrt_marshallOut(const emlrtStack *sp, const
  FeedoptContext *u);
static void eb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void ec_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x0, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);
static void emxFreeStruct_CurvStruct(CurvStruct *pStruct);
static void emxFreeStruct_FeedoptContext(FeedoptContext *pStruct);
static void emxFreeStruct_SplineBase(SplineBase *pStruct);
static void emxFreeStruct_SplineStruct(SplineStruct *pStruct);
static void emxFreeStruct_queue_coder(queue_coder *pStruct);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInitStruct_CurvStruct(const emlrtStack *sp, CurvStruct *pStruct,
  boolean_T doPush);
static void emxInitStruct_FeedoptContext(const emlrtStack *sp, FeedoptContext
  *pStruct, boolean_T doPush);
static void emxInitStruct_SplineBase(const emlrtStack *sp, SplineBase *pStruct,
  boolean_T doPush);
static void emxInitStruct_SplineStruct(const emlrtStack *sp, SplineStruct
  *pStruct, boolean_T doPush);
static void emxInitStruct_queue_coder(const emlrtStack *sp, queue_coder *pStruct,
  boolean_T doPush);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, FeedoptConfig *y);
static const mxArray *f_emlrt_marshallOut(const emlrtStack *sp, const
  queue_coder *u);
static void fb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *coeffs,
  const char_T *identifier, real_T **y_data, int32_T y_size[2]);
static void fc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static boolean_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static const mxArray *g_emlrt_marshallOut(const emlrtStack *sp, const CurvStruct
  *u);
static void gb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[2]);
static void gc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[3]);
static const mxArray *h_emlrt_marshallOut(const emxArray_real_T *u);
static real_T (*hb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *P0,
  const char_T *identifier))[3];
static void hc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[2]);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[1024]);
static const mxArray *i_emlrt_marshallOut(const emxArray_real_T *u);
static real_T (*ib_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3];
static real_T (*ic_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static struct0_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static const mxArray *j_emlrt_marshallOut(const SplineBase u);
static ZSpdMode jb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *b_ZSpdMode, const char_T *identifier);
static real_T (*jc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[10];
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[9]);
static const mxArray *k_emlrt_marshallOut(const emxArray_real_T *u);
static real_T (*kb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *breakpoints, const char_T *identifier))[10];
static void kc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret_data[], int32_T ret_size[2]);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *ctx, const
  char_T *identifier, FeedoptContext *y);
static const mxArray *l_emlrt_marshallOut(const emlrtStack *sp, const creal_T
  u_data[], const int32_T u_size[1]);
static real_T (*lb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[10];
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, FeedoptContext *y);
static const mxArray *m_emlrt_marshallOut(const emlrtStack *sp, const
  TransitionResult u);
static ResampleStateClass mb_emlrt_marshallIn(const emlrtStack *sp, const
  mxArray *state, const char_T *identifier);
static Fopt n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *n_emlrt_marshallOut(const emlrtStack *sp, const
  ResampleStateClass u);
static ResampleStateClass nb_emlrt_marshallIn(const emlrtStack *sp, const
  mxArray *u, const emlrtMsgIdentifier *parentId);
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, queue_coder *y);
static const mxArray *o_emlrt_marshallOut(const real_T u[3]);
static void ob_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Bl, const
  char_T *identifier, SplineBase *y);
static uint64_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static DebugCfg pb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg,
  const char_T *identifier);
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, CurvStruct *y);
static DebugCfg qb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static CurveType r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static void rb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *filename,
  const char_T *identifier, char_T y_data[], int32_T y_size[2]);
static ZSpdMode s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void sb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y_data[], int32_T y_size[2]);
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[3]);
static real_T tb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[6][3]);
static int32_T ub_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static boolean_T vb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, SplineStruct *y);
static void wb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[3]);
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void xb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[1024]);
static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, SplineBase *y);
static void yb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[9]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : FeedoptPlanError
 */
static FeedoptPlanError ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *
  u, const emlrtMsgIdentifier *parentId)
{
  FeedoptPlanError y;
  static const int32_T dims = 0;
  emlrtCheckEnumR2012b(sp, "FeedoptPlanError", 4, sv1, iv1);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "FeedoptPlanError", false, 0U, &dims);
  y = (FeedoptPlanError)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : uint64_T
 */
static uint64_T ac_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  uint64_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint64", false, 0U, &dims);
  ret = *(uint64_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = tb_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const FeedoptConfig *u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp, const
  FeedoptConfig *u)
{
  const mxArray *y;
  static const char * b_sv[28] = { "NDiscr", "NBreak", "UseDynamicBreakpoints",
    "UseLinearBreakpoints", "DynamicBreakpointsDistance", "NHorz", "vmax",
    "amax", "jmax", "SplineDegree", "CutOff", "LSplit", "LThreshold",
    "CuspThreshold", "v_0", "at_0", "v_1", "at_1", "dt", "ZeroStartAccLimit",
    "ZeroStartJerkLimit", "ZeroStartVelLimit", "source", "DebugCutZero",
    "Compressing", "CollTolDeg", "NGridLengthSpline", "LogFileName" };

  const mxArray *b_y;
  const mxArray *m;
  const mxArray *c_y;
  const mxArray *m1;
  const mxArray *d_y;
  const mxArray *m2;
  const mxArray *e_y;
  const mxArray *m3;
  const mxArray *f_y;
  const mxArray *m4;
  const mxArray *g_y;
  const mxArray *m5;
  const mxArray *h_y;
  const mxArray *m6;
  const mxArray *i_y;
  const mxArray *m7;
  const mxArray *j_y;
  const mxArray *m8;
  const mxArray *k_y;
  const mxArray *m9;
  const mxArray *l_y;
  const mxArray *m10;
  const mxArray *m_y;
  const mxArray *m11;
  const mxArray *n_y;
  const mxArray *m12;
  const mxArray *o_y;
  const mxArray *m13;
  const mxArray *p_y;
  const mxArray *m14;
  const mxArray *q_y;
  const mxArray *m15;
  const mxArray *r_y;
  const mxArray *m16;
  const mxArray *s_y;
  const mxArray *m17;
  char_T b_u[1024];
  const mxArray *t_y;
  const mxArray *m18;
  static const int32_T b_iv[2] = { 1, 1024 };

  const mxArray *u_y;
  static const char * b_sv1[2] = { "Skip", "ColTolDeg" };

  const mxArray *v_y;
  const mxArray *m19;
  const mxArray *w_y;
  const mxArray *m20;
  const mxArray *x_y;
  const mxArray *m21;
  int32_T i;
  const mxArray *y_y;
  char_T c_u[9];
  const mxArray *m22;
  static const int32_T b_iv1[2] = { 1, 9 };

  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 28, b_sv));
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = u->NDiscr;
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, "NDiscr", b_y, 0);
  c_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m1) = u->NBreak;
  emlrtAssign(&c_y, m1);
  emlrtSetFieldR2017b(y, 0, "NBreak", c_y, 1);
  emlrtSetFieldR2017b(y, 0, "UseDynamicBreakpoints", c_emlrt_marshallOut
                      (u->UseDynamicBreakpoints), 2);
  emlrtSetFieldR2017b(y, 0, "UseLinearBreakpoints", c_emlrt_marshallOut
                      (u->UseLinearBreakpoints), 3);
  d_y = NULL;
  m2 = emlrtCreateDoubleScalar(u->DynamicBreakpointsDistance);
  emlrtAssign(&d_y, m2);
  emlrtSetFieldR2017b(y, 0, "DynamicBreakpointsDistance", d_y, 4);
  e_y = NULL;
  m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m3) = u->NHorz;
  emlrtAssign(&e_y, m3);
  emlrtSetFieldR2017b(y, 0, "NHorz", e_y, 5);
  f_y = NULL;
  m4 = emlrtCreateDoubleScalar(u->vmax);
  emlrtAssign(&f_y, m4);
  emlrtSetFieldR2017b(y, 0, "vmax", f_y, 6);
  emlrtSetFieldR2017b(y, 0, "amax", d_emlrt_marshallOut(u->amax), 7);
  emlrtSetFieldR2017b(y, 0, "jmax", d_emlrt_marshallOut(u->jmax), 8);
  g_y = NULL;
  m5 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m5) = u->SplineDegree;
  emlrtAssign(&g_y, m5);
  emlrtSetFieldR2017b(y, 0, "SplineDegree", g_y, 9);
  h_y = NULL;
  m6 = emlrtCreateDoubleScalar(u->CutOff);
  emlrtAssign(&h_y, m6);
  emlrtSetFieldR2017b(y, 0, "CutOff", h_y, 10);
  i_y = NULL;
  m7 = emlrtCreateDoubleScalar(u->LSplit);
  emlrtAssign(&i_y, m7);
  emlrtSetFieldR2017b(y, 0, "LSplit", i_y, 11);
  j_y = NULL;
  m8 = emlrtCreateDoubleScalar(u->LThreshold);
  emlrtAssign(&j_y, m8);
  emlrtSetFieldR2017b(y, 0, "LThreshold", j_y, 12);
  k_y = NULL;
  m9 = emlrtCreateDoubleScalar(u->CuspThreshold);
  emlrtAssign(&k_y, m9);
  emlrtSetFieldR2017b(y, 0, "CuspThreshold", k_y, 13);
  l_y = NULL;
  m10 = emlrtCreateDoubleScalar(u->v_0);
  emlrtAssign(&l_y, m10);
  emlrtSetFieldR2017b(y, 0, "v_0", l_y, 14);
  m_y = NULL;
  m11 = emlrtCreateDoubleScalar(u->at_0);
  emlrtAssign(&m_y, m11);
  emlrtSetFieldR2017b(y, 0, "at_0", m_y, 15);
  n_y = NULL;
  m12 = emlrtCreateDoubleScalar(u->v_1);
  emlrtAssign(&n_y, m12);
  emlrtSetFieldR2017b(y, 0, "v_1", n_y, 16);
  o_y = NULL;
  m13 = emlrtCreateDoubleScalar(u->at_1);
  emlrtAssign(&o_y, m13);
  emlrtSetFieldR2017b(y, 0, "at_1", o_y, 17);
  p_y = NULL;
  m14 = emlrtCreateDoubleScalar(u->dt);
  emlrtAssign(&p_y, m14);
  emlrtSetFieldR2017b(y, 0, "dt", p_y, 18);
  q_y = NULL;
  m15 = emlrtCreateDoubleScalar(u->ZeroStartAccLimit);
  emlrtAssign(&q_y, m15);
  emlrtSetFieldR2017b(y, 0, "ZeroStartAccLimit", q_y, 19);
  r_y = NULL;
  m16 = emlrtCreateDoubleScalar(u->ZeroStartJerkLimit);
  emlrtAssign(&r_y, m16);
  emlrtSetFieldR2017b(y, 0, "ZeroStartJerkLimit", r_y, 20);
  s_y = NULL;
  m17 = emlrtCreateDoubleScalar(u->ZeroStartVelLimit);
  emlrtAssign(&s_y, m17);
  emlrtSetFieldR2017b(y, 0, "ZeroStartVelLimit", s_y, 21);
  memcpy(&b_u[0], &u->source[0], 1024U * sizeof(char_T));
  t_y = NULL;
  m18 = emlrtCreateCharArray(2, &b_iv[0]);
  emlrtInitCharArrayR2013a(sp, 1024, m18, &b_u[0]);
  emlrtAssign(&t_y, m18);
  emlrtSetFieldR2017b(y, 0, "source", t_y, 22);
  emlrtSetFieldR2017b(y, 0, "DebugCutZero", c_emlrt_marshallOut(u->DebugCutZero),
                      23);
  u_y = NULL;
  emlrtAssign(&u_y, emlrtCreateStructMatrix(1, 1, 2, b_sv1));
  emlrtSetFieldR2017b(u_y, 0, "Skip", c_emlrt_marshallOut(u->Compressing.Skip),
                      0);
  v_y = NULL;
  m19 = emlrtCreateDoubleScalar(u->Compressing.ColTolDeg);
  emlrtAssign(&v_y, m19);
  emlrtSetFieldR2017b(u_y, 0, "ColTolDeg", v_y, 1);
  emlrtSetFieldR2017b(y, 0, "Compressing", u_y, 24);
  w_y = NULL;
  m20 = emlrtCreateDoubleScalar(u->CollTolDeg);
  emlrtAssign(&w_y, m20);
  emlrtSetFieldR2017b(y, 0, "CollTolDeg", w_y, 25);
  x_y = NULL;
  m21 = emlrtCreateDoubleScalar(u->NGridLengthSpline);
  emlrtAssign(&x_y, m21);
  emlrtSetFieldR2017b(y, 0, "NGridLengthSpline", x_y, 26);
  for (i = 0; i < 9; i++) {
    c_u[i] = u->LogFileName[i];
  }

  y_y = NULL;
  m22 = emlrtCreateCharArray(2, &b_iv1[0]);
  emlrtInitCharArrayR2013a(sp, 9, m22, &c_u[0]);
  emlrtAssign(&y_y, m22);
  emlrtSetFieldR2017b(y, 0, "LogFileName", y_y, 27);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  fc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[3]
 * Return Type  : void
 */
static void bc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[3])
{
  static const int32_T dims[1] = { 3 };

  real_T (*r)[3];
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  r = (real_T (*)[3])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *N
 *                const char_T *identifier
 * Return Type  : int32_T
 */
static int32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *N, const
  char_T *identifier)
{
  int32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(N), &thisId);
  emlrtDestroyArray(&N);
  return y;
}

/*
 * Arguments    : const boolean_T u
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const boolean_T u)
{
  const mxArray *y;
  const mxArray *m;
  y = NULL;
  m = emlrtCreateLogicalScalar(u);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *b_CurvStruct
 *                const char_T *identifier
 *                CurvStruct *y
 * Return Type  : void
 */
static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *b_CurvStruct, const char_T *identifier, CurvStruct *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  q_emlrt_marshallIn(sp, emlrtAlias(b_CurvStruct), &thisId, y);
  emlrtDestroyArray(&b_CurvStruct);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[6][3]
 * Return Type  : void
 */
static void cc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[6][3])
{
  static const int32_T dims[2] = { 3, 6 };

  real_T (*r)[6][3];
  int32_T i;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  r = (real_T (*)[6][3])emlrtMxGetData(src);
  for (i = 0; i < 6; i++) {
    ret[i][0] = (*r)[i][0];
    ret[i][1] = (*r)[i][1];
    ret[i][2] = (*r)[i][2];
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int32_T
 */
static int32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  int32_T y;
  y = ub_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[3]
 * Return Type  : const mxArray *
 */
static const mxArray *d_emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T b_iv[2] = { 1, 3 };

  real_T *pData;
  y = NULL;
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  pData[0] = u[0];
  pData[1] = u[1];
  pData[2] = u[2];
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u_vec
 *                const char_T *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_vec,
  const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  eb_emlrt_marshallIn(sp, emlrtAlias(u_vec), &thisId, y);
  emlrtDestroyArray(&u_vec);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void dc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv[1] = { true };

  int32_T b_iv[1];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv[0],
    b_iv);
  i = ret->size[0];
  ret->size[0] = b_iv[0];
  emxEnsureCapacity_real_T(ret, i);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *cfg
 *                const char_T *identifier
 *                FeedoptConfig *y
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg, const
  char_T *identifier, FeedoptConfig *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(cfg), &thisId, y);
  emlrtDestroyArray(&cfg);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const FeedoptContext *u
 * Return Type  : const mxArray *
 */
static const mxArray *e_emlrt_marshallOut(const emlrtStack *sp, const
  FeedoptContext *u)
{
  const mxArray *y;
  static const char * b_sv[31] = { "op", "go_next", "q_gcode", "q_compress",
    "q_splines", "q_smooth", "q_split", "q_opt", "try_push_again", "n_optimized",
    "reached_end", "k0", "v_0", "v_1", "at_0", "at_1", "cfg", "Bl", "u_vec",
    "errcode", "jmax_increase_count", "zero_start", "zero_end", "forced_stop",
    "programmed_stop", "BasisVal", "BasisValD", "BasisValDD", "BasisIntegr",
    "Coeff", "Skipped" };

  const mxArray *b_y;
  const mxArray *m;
  const mxArray *c_y;
  const mxArray *m1;
  const mxArray *d_y;
  const mxArray *m2;
  const mxArray *e_y;
  const mxArray *m3;
  const mxArray *f_y;
  const mxArray *m4;
  const mxArray *g_y;
  const mxArray *m5;
  const mxArray *h_y;
  const mxArray *m6;
  const mxArray *i_y;
  const mxArray *m7;
  const mxArray *j_y;
  const mxArray *m8;
  const mxArray *k_y;
  const mxArray *m9;
  const mxArray *l_y;
  const mxArray *m10;
  const mxArray *m_y;
  const mxArray *m11;
  const mxArray *n_y;
  const mxArray *m12;
  const mxArray *o_y;
  const mxArray *m13;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 31, b_sv));
  b_y = NULL;
  m = NULL;
  emlrtCheckEnumR2012b(sp, "Fopt", 8, sv, iv);
  c_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m1) = (int32_T)u->op;
  emlrtAssign(&c_y, m1);
  emlrtAssign(&m, c_y);
  emlrtAssign(&b_y, emlrtCreateEnumR2012b(sp, "Fopt", m));
  emlrtDestroyArray(&m);
  emlrtSetFieldR2017b(y, 0, "op", b_y, 0);
  emlrtSetFieldR2017b(y, 0, "go_next", c_emlrt_marshallOut(u->go_next), 1);
  emlrtSetFieldR2017b(y, 0, "q_gcode", f_emlrt_marshallOut(sp, &u->q_gcode), 2);
  emlrtSetFieldR2017b(y, 0, "q_compress", f_emlrt_marshallOut(sp, &u->q_compress),
                      3);
  emlrtSetFieldR2017b(y, 0, "q_splines", f_emlrt_marshallOut(sp, &u->q_splines),
                      4);
  emlrtSetFieldR2017b(y, 0, "q_smooth", f_emlrt_marshallOut(sp, &u->q_smooth), 5);
  emlrtSetFieldR2017b(y, 0, "q_split", f_emlrt_marshallOut(sp, &u->q_split), 6);
  emlrtSetFieldR2017b(y, 0, "q_opt", f_emlrt_marshallOut(sp, &u->q_opt), 7);
  emlrtSetFieldR2017b(y, 0, "try_push_again", c_emlrt_marshallOut
                      (u->try_push_again), 8);
  d_y = NULL;
  m2 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m2) = u->n_optimized;
  emlrtAssign(&d_y, m2);
  emlrtSetFieldR2017b(y, 0, "n_optimized", d_y, 9);
  emlrtSetFieldR2017b(y, 0, "reached_end", c_emlrt_marshallOut(u->reached_end),
                      10);
  e_y = NULL;
  m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m3) = u->k0;
  emlrtAssign(&e_y, m3);
  emlrtSetFieldR2017b(y, 0, "k0", e_y, 11);
  f_y = NULL;
  m4 = emlrtCreateDoubleScalar(u->v_0);
  emlrtAssign(&f_y, m4);
  emlrtSetFieldR2017b(y, 0, "v_0", f_y, 12);
  g_y = NULL;
  m5 = emlrtCreateDoubleScalar(u->v_1);
  emlrtAssign(&g_y, m5);
  emlrtSetFieldR2017b(y, 0, "v_1", g_y, 13);
  h_y = NULL;
  m6 = emlrtCreateDoubleScalar(u->at_0);
  emlrtAssign(&h_y, m6);
  emlrtSetFieldR2017b(y, 0, "at_0", h_y, 14);
  i_y = NULL;
  m7 = emlrtCreateDoubleScalar(u->at_1);
  emlrtAssign(&i_y, m7);
  emlrtSetFieldR2017b(y, 0, "at_1", i_y, 15);
  emlrtSetFieldR2017b(y, 0, "cfg", b_emlrt_marshallOut(sp, &u->cfg), 16);
  emlrtSetFieldR2017b(y, 0, "Bl", j_emlrt_marshallOut(u->Bl), 17);
  emlrtSetFieldR2017b(y, 0, "u_vec", i_emlrt_marshallOut(u->u_vec), 18);
  j_y = NULL;
  m8 = NULL;
  emlrtCheckEnumR2012b(sp, "FeedoptPlanError", 4, sv1, iv1);
  k_y = NULL;
  m9 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m9) = (int32_T)u->errcode;
  emlrtAssign(&k_y, m9);
  emlrtAssign(&m8, k_y);
  emlrtAssign(&j_y, emlrtCreateEnumR2012b(sp, "FeedoptPlanError", m8));
  emlrtDestroyArray(&m8);
  emlrtSetFieldR2017b(y, 0, "errcode", j_y, 19);
  l_y = NULL;
  m10 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m10) = u->jmax_increase_count;
  emlrtAssign(&l_y, m10);
  emlrtSetFieldR2017b(y, 0, "jmax_increase_count", l_y, 20);
  emlrtSetFieldR2017b(y, 0, "zero_start", c_emlrt_marshallOut(u->zero_start), 21);
  emlrtSetFieldR2017b(y, 0, "zero_end", c_emlrt_marshallOut(u->zero_end), 22);
  m_y = NULL;
  m11 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m11) = u->forced_stop;
  emlrtAssign(&m_y, m11);
  emlrtSetFieldR2017b(y, 0, "forced_stop", m_y, 23);
  n_y = NULL;
  m12 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m12) = u->programmed_stop;
  emlrtAssign(&n_y, m12);
  emlrtSetFieldR2017b(y, 0, "programmed_stop", n_y, 24);
  emlrtSetFieldR2017b(y, 0, "BasisVal", k_emlrt_marshallOut(u->BasisVal), 25);
  emlrtSetFieldR2017b(y, 0, "BasisValD", k_emlrt_marshallOut(u->BasisValD), 26);
  emlrtSetFieldR2017b(y, 0, "BasisValDD", k_emlrt_marshallOut(u->BasisValDD), 27);
  emlrtSetFieldR2017b(y, 0, "BasisIntegr", h_emlrt_marshallOut(u->BasisIntegr),
                      28);
  emlrtSetFieldR2017b(y, 0, "Coeff", k_emlrt_marshallOut(u->Coeff), 29);
  o_y = NULL;
  m13 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m13) = u->Skipped;
  emlrtAssign(&o_y, m13);
  emlrtSetFieldR2017b(y, 0, "Skipped", o_y, 30);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void eb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  gc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void ec_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv[0],
    b_iv);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x0
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x0, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x0), &thisId);
  emlrtDestroyArray(&x0);
  return y;
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T b_iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : emxArray_real_T *emxArray
 *                int32_T oldNumel
 * Return Type  : void
 */
static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel)
{
  int32_T newNumel;
  int32_T i;
  int32_T newCapacity;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    newCapacity = emxArray->allocatedSize;
    if (newCapacity < 16) {
      newCapacity = 16;
    }

    while (newCapacity < newNumel) {
      if (newCapacity > 1073741823) {
        newCapacity = MAX_int32_T;
      } else {
        newCapacity *= 2;
      }
    }

    newData = emlrtCallocMex((uint32_T)newCapacity, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = newCapacity;
    emxArray->canFreeData = true;
  }
}

/*
 * Arguments    : CurvStruct *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_CurvStruct(CurvStruct *pStruct)
{
  emxFree_real_T(&pStruct->Coeff);
  emxFreeStruct_SplineStruct(&pStruct->sp);
}

/*
 * Arguments    : FeedoptContext *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_FeedoptContext(FeedoptContext *pStruct)
{
  emxFreeStruct_queue_coder(&pStruct->q_gcode);
  emxFreeStruct_queue_coder(&pStruct->q_compress);
  emxFreeStruct_queue_coder(&pStruct->q_splines);
  emxFreeStruct_queue_coder(&pStruct->q_smooth);
  emxFreeStruct_queue_coder(&pStruct->q_split);
  emxFreeStruct_queue_coder(&pStruct->q_opt);
  emxFreeStruct_SplineBase(&pStruct->Bl);
  emxFree_real_T(&pStruct->u_vec);
  emxFree_real_T(&pStruct->BasisVal);
  emxFree_real_T(&pStruct->BasisValD);
  emxFree_real_T(&pStruct->BasisValDD);
  emxFree_real_T(&pStruct->BasisIntegr);
  emxFree_real_T(&pStruct->Coeff);
}

/*
 * Arguments    : SplineBase *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_SplineBase(SplineBase *pStruct)
{
  emxFree_real_T(&pStruct->breakpoints);
}

/*
 * Arguments    : SplineStruct *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_SplineStruct(SplineStruct *pStruct)
{
  emxFree_real_T(&pStruct->CoeffX);
  emxFree_real_T(&pStruct->CoeffY);
  emxFree_real_T(&pStruct->CoeffZ);
  emxFreeStruct_SplineBase(&pStruct->Bl);
  emxFree_real_T(&pStruct->knots);
}

/*
 * Arguments    : queue_coder *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_queue_coder(queue_coder *pStruct)
{
  emxFreeStruct_CurvStruct(&pStruct->value_type);
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                CurvStruct *pStruct
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInitStruct_CurvStruct(const emlrtStack *sp, CurvStruct *pStruct,
  boolean_T doPush)
{
  emxInit_real_T(sp, &pStruct->Coeff, 1, doPush);
  emxInitStruct_SplineStruct(sp, &pStruct->sp, doPush);
}

/*
 * Arguments    : const emlrtStack *sp
 *                FeedoptContext *pStruct
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInitStruct_FeedoptContext(const emlrtStack *sp, FeedoptContext
  *pStruct, boolean_T doPush)
{
  emxInitStruct_queue_coder(sp, &pStruct->q_gcode, doPush);
  emxInitStruct_queue_coder(sp, &pStruct->q_compress, doPush);
  emxInitStruct_queue_coder(sp, &pStruct->q_splines, doPush);
  emxInitStruct_queue_coder(sp, &pStruct->q_smooth, doPush);
  emxInitStruct_queue_coder(sp, &pStruct->q_split, doPush);
  emxInitStruct_queue_coder(sp, &pStruct->q_opt, doPush);
  emxInitStruct_SplineBase(sp, &pStruct->Bl, doPush);
  emxInit_real_T(sp, &pStruct->u_vec, 2, doPush);
  emxInit_real_T(sp, &pStruct->BasisVal, 2, doPush);
  emxInit_real_T(sp, &pStruct->BasisValD, 2, doPush);
  emxInit_real_T(sp, &pStruct->BasisValDD, 2, doPush);
  emxInit_real_T(sp, &pStruct->BasisIntegr, 1, doPush);
  emxInit_real_T(sp, &pStruct->Coeff, 2, doPush);
}

/*
 * Arguments    : const emlrtStack *sp
 *                SplineBase *pStruct
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInitStruct_SplineBase(const emlrtStack *sp, SplineBase *pStruct,
  boolean_T doPush)
{
  emxInit_real_T(sp, &pStruct->breakpoints, 2, doPush);
}

/*
 * Arguments    : const emlrtStack *sp
 *                SplineStruct *pStruct
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInitStruct_SplineStruct(const emlrtStack *sp, SplineStruct
  *pStruct, boolean_T doPush)
{
  emxInit_real_T(sp, &pStruct->CoeffX, 2, doPush);
  emxInit_real_T(sp, &pStruct->CoeffY, 2, doPush);
  emxInit_real_T(sp, &pStruct->CoeffZ, 2, doPush);
  emxInitStruct_SplineBase(sp, &pStruct->Bl, doPush);
  emxInit_real_T(sp, &pStruct->knots, 2, doPush);
}

/*
 * Arguments    : const emlrtStack *sp
 *                queue_coder *pStruct
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInitStruct_queue_coder(const emlrtStack *sp, queue_coder *pStruct,
  boolean_T doPush)
{
  emxInitStruct_CurvStruct(sp, &pStruct->value_type, doPush);
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void *)
      &emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                FeedoptConfig *y
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, FeedoptConfig *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[28] = { "NDiscr", "NBreak",
    "UseDynamicBreakpoints", "UseLinearBreakpoints",
    "DynamicBreakpointsDistance", "NHorz", "vmax", "amax", "jmax",
    "SplineDegree", "CutOff", "LSplit", "LThreshold", "CuspThreshold", "v_0",
    "at_0", "v_1", "at_1", "dt", "ZeroStartAccLimit", "ZeroStartJerkLimit",
    "ZeroStartVelLimit", "source", "DebugCutZero", "Compressing", "CollTolDeg",
    "NGridLengthSpline", "LogFileName" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 28, fieldNames, 0U, &dims);
  thisId.fIdentifier = "NDiscr";
  y->NDiscr = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0,
    "NDiscr")), &thisId);
  thisId.fIdentifier = "NBreak";
  y->NBreak = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1,
    "NBreak")), &thisId);
  thisId.fIdentifier = "UseDynamicBreakpoints";
  y->UseDynamicBreakpoints = g_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2017b(sp, u, 0, 2, "UseDynamicBreakpoints")), &thisId);
  thisId.fIdentifier = "UseLinearBreakpoints";
  y->UseLinearBreakpoints = g_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2017b(sp, u, 0, 3, "UseLinearBreakpoints")), &thisId);
  thisId.fIdentifier = "DynamicBreakpointsDistance";
  y->DynamicBreakpointsDistance = b_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2017b(sp, u, 0, 4, "DynamicBreakpointsDistance")), &thisId);
  thisId.fIdentifier = "NHorz";
  y->NHorz = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 5,
    "NHorz")), &thisId);
  thisId.fIdentifier = "vmax";
  y->vmax = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 6,
    "vmax")), &thisId);
  thisId.fIdentifier = "amax";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 7, "amax")),
                     &thisId, y->amax);
  thisId.fIdentifier = "jmax";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 8, "jmax")),
                     &thisId, y->jmax);
  thisId.fIdentifier = "SplineDegree";
  y->SplineDegree = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 9, "SplineDegree")), &thisId);
  thisId.fIdentifier = "CutOff";
  y->CutOff = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 10,
    "CutOff")), &thisId);
  thisId.fIdentifier = "LSplit";
  y->LSplit = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 11,
    "LSplit")), &thisId);
  thisId.fIdentifier = "LThreshold";
  y->LThreshold = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    12, "LThreshold")), &thisId);
  thisId.fIdentifier = "CuspThreshold";
  y->CuspThreshold = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 13, "CuspThreshold")), &thisId);
  thisId.fIdentifier = "v_0";
  y->v_0 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 14,
    "v_0")), &thisId);
  thisId.fIdentifier = "at_0";
  y->at_0 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 15,
    "at_0")), &thisId);
  thisId.fIdentifier = "v_1";
  y->v_1 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 16,
    "v_1")), &thisId);
  thisId.fIdentifier = "at_1";
  y->at_1 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 17,
    "at_1")), &thisId);
  thisId.fIdentifier = "dt";
  y->dt = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 18,
    "dt")), &thisId);
  thisId.fIdentifier = "ZeroStartAccLimit";
  y->ZeroStartAccLimit = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 19, "ZeroStartAccLimit")), &thisId);
  thisId.fIdentifier = "ZeroStartJerkLimit";
  y->ZeroStartJerkLimit = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 20, "ZeroStartJerkLimit")), &thisId);
  thisId.fIdentifier = "ZeroStartVelLimit";
  y->ZeroStartVelLimit = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 21, "ZeroStartVelLimit")), &thisId);
  thisId.fIdentifier = "source";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 22, "source")),
                     &thisId, y->source);
  thisId.fIdentifier = "DebugCutZero";
  y->DebugCutZero = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 23, "DebugCutZero")), &thisId);
  thisId.fIdentifier = "Compressing";
  y->Compressing = j_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 24, "Compressing")), &thisId);
  thisId.fIdentifier = "CollTolDeg";
  y->CollTolDeg = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    25, "CollTolDeg")), &thisId);
  thisId.fIdentifier = "NGridLengthSpline";
  y->NGridLengthSpline = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 26, "NGridLengthSpline")), &thisId);
  thisId.fIdentifier = "LogFileName";
  k_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 27,
    "LogFileName")), &thisId, y->LogFileName);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const queue_coder *u
 * Return Type  : const mxArray *
 */
static const mxArray *f_emlrt_marshallOut(const emlrtStack *sp, const
  queue_coder *u)
{
  const mxArray *y;
  const mxArray *m;
  const mxArray *b_y;
  const mxArray *m1;
  const mxArray *propValues[2];
  const mxArray *m2;
  y = NULL;
  emlrtAssign(&y, emlrtCreateClassInstance("queue_coder"));
  m = NULL;
  b_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
  *(uint64_T *)emlrtMxGetData(m1) = u->ptr;
  emlrtAssign(&b_y, m1);
  emlrtAssign(&m, b_y);
  propValues[0] = m;
  m2 = NULL;
  emlrtAssign(&m2, g_emlrt_marshallOut(sp, &u->value_type));
  propValues[1] = m2;
  emlrtSetAllProperties(sp, &y, 0, 2, sv2, sv3, propValues);
  emlrtAssign(&y, emlrtConvertInstanceToRedirectSource(sp, y, 0, "queue_coder"));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *coeffs
 *                const char_T *identifier
 *                real_T **y_data
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void fb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *coeffs,
  const char_T *identifier, real_T **y_data, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  gb_emlrt_marshallIn(sp, emlrtAlias(coeffs), &thisId, y_data, y_size);
  emlrtDestroyArray(&coeffs);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void fc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T bv[2] = { true, true };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv[0],
    b_iv);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : boolean_T
 */
static boolean_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  boolean_T y;
  y = vb_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const CurvStruct *u
 * Return Type  : const mxArray *
 */
static const mxArray *g_emlrt_marshallOut(const emlrtStack *sp, const CurvStruct
  *u)
{
  const mxArray *y;
  static const char * b_sv[25] = { "Type", "zspdmode", "P0", "P1",
    "CorrectedHelixCenter", "delta", "evec", "theta", "pitch", "CoeffP5",
    "sp_index", "FeedRate", "SpindleSpeed", "MaxConstantFeedRate", "i_begin_sp",
    "i_end_sp", "gcode_source_line", "index_smooth", "UseConstJerk", "ConstJerk",
    "ConstJerkMaxIterations", "Coeff", "a_param", "b_param", "sp" };

  const mxArray *b_y;
  const mxArray *m;
  const mxArray *c_y;
  const mxArray *m1;
  const mxArray *d_y;
  const mxArray *m2;
  const mxArray *e_y;
  const mxArray *m3;
  const mxArray *f_y;
  const mxArray *m4;
  static const int32_T b_iv[1] = { 3 };

  real_T *pData;
  const mxArray *g_y;
  const mxArray *m5;
  static const int32_T b_iv1[1] = { 3 };

  real_T *b_pData;
  const mxArray *h_y;
  const mxArray *m6;
  static const int32_T b_iv2[1] = { 3 };

  real_T *c_pData;
  const mxArray *i_y;
  const mxArray *m7;
  const mxArray *j_y;
  const mxArray *m8;
  static const int32_T iv3[1] = { 3 };

  real_T *d_pData;
  const mxArray *k_y;
  const mxArray *m9;
  const mxArray *l_y;
  const mxArray *m10;
  const mxArray *m_y;
  const mxArray *m11;
  static const int32_T iv4[2] = { 3, 6 };

  real_T *e_pData;
  int32_T i;
  int32_T b_i;
  const mxArray *n_y;
  const mxArray *m12;
  const mxArray *o_y;
  const mxArray *m13;
  const mxArray *p_y;
  const mxArray *m14;
  const mxArray *q_y;
  const mxArray *m15;
  const mxArray *r_y;
  const mxArray *m16;
  const mxArray *s_y;
  const mxArray *m17;
  const mxArray *t_y;
  const mxArray *m18;
  const mxArray *u_y;
  const mxArray *m19;
  const mxArray *v_y;
  const mxArray *m20;
  const mxArray *w_y;
  const mxArray *m21;
  const mxArray *x_y;
  const mxArray *m22;
  const mxArray *y_y;
  const mxArray *m23;
  const mxArray *ab_y;
  static const char * b_sv1[5] = { "CoeffX", "CoeffY", "CoeffZ", "Bl", "knots" };

  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 25, b_sv));
  b_y = NULL;
  m = NULL;
  emlrtCheckEnumR2012b(sp, "CurveType", 5, sv4, iv2);
  c_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m1) = (int32_T)u->Type;
  emlrtAssign(&c_y, m1);
  emlrtAssign(&m, c_y);
  emlrtAssign(&b_y, emlrtCreateEnumR2012b(sp, "CurveType", m));
  emlrtDestroyArray(&m);
  emlrtSetFieldR2017b(y, 0, "Type", b_y, 0);
  d_y = NULL;
  m2 = NULL;
  emlrtCheckEnumR2012b(sp, "ZSpdMode", 4, sv5, iv1);
  e_y = NULL;
  m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m3) = (int32_T)u->zspdmode;
  emlrtAssign(&e_y, m3);
  emlrtAssign(&m2, e_y);
  emlrtAssign(&d_y, emlrtCreateEnumR2012b(sp, "ZSpdMode", m2));
  emlrtDestroyArray(&m2);
  emlrtSetFieldR2017b(y, 0, "zspdmode", d_y, 1);
  f_y = NULL;
  m4 = emlrtCreateNumericArray(1, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m4);
  pData[0] = u->P0[0];
  pData[1] = u->P0[1];
  pData[2] = u->P0[2];
  emlrtAssign(&f_y, m4);
  emlrtSetFieldR2017b(y, 0, "P0", f_y, 2);
  g_y = NULL;
  m5 = emlrtCreateNumericArray(1, &b_iv1[0], mxDOUBLE_CLASS, mxREAL);
  b_pData = emlrtMxGetPr(m5);
  b_pData[0] = u->P1[0];
  b_pData[1] = u->P1[1];
  b_pData[2] = u->P1[2];
  emlrtAssign(&g_y, m5);
  emlrtSetFieldR2017b(y, 0, "P1", g_y, 3);
  h_y = NULL;
  m6 = emlrtCreateNumericArray(1, &b_iv2[0], mxDOUBLE_CLASS, mxREAL);
  c_pData = emlrtMxGetPr(m6);
  c_pData[0] = u->CorrectedHelixCenter[0];
  c_pData[1] = u->CorrectedHelixCenter[1];
  c_pData[2] = u->CorrectedHelixCenter[2];
  emlrtAssign(&h_y, m6);
  emlrtSetFieldR2017b(y, 0, "CorrectedHelixCenter", h_y, 4);
  i_y = NULL;
  m7 = emlrtCreateDoubleScalar(u->delta);
  emlrtAssign(&i_y, m7);
  emlrtSetFieldR2017b(y, 0, "delta", i_y, 5);
  j_y = NULL;
  m8 = emlrtCreateNumericArray(1, &iv3[0], mxDOUBLE_CLASS, mxREAL);
  d_pData = emlrtMxGetPr(m8);
  d_pData[0] = u->evec[0];
  d_pData[1] = u->evec[1];
  d_pData[2] = u->evec[2];
  emlrtAssign(&j_y, m8);
  emlrtSetFieldR2017b(y, 0, "evec", j_y, 6);
  k_y = NULL;
  m9 = emlrtCreateDoubleScalar(u->theta);
  emlrtAssign(&k_y, m9);
  emlrtSetFieldR2017b(y, 0, "theta", k_y, 7);
  l_y = NULL;
  m10 = emlrtCreateDoubleScalar(u->pitch);
  emlrtAssign(&l_y, m10);
  emlrtSetFieldR2017b(y, 0, "pitch", l_y, 8);
  m_y = NULL;
  m11 = emlrtCreateNumericArray(2, &iv4[0], mxDOUBLE_CLASS, mxREAL);
  e_pData = emlrtMxGetPr(m11);
  i = 0;
  for (b_i = 0; b_i < 6; b_i++) {
    e_pData[i] = u->CoeffP5[b_i][0];
    i++;
    e_pData[i] = u->CoeffP5[b_i][1];
    i++;
    e_pData[i] = u->CoeffP5[b_i][2];
    i++;
  }

  emlrtAssign(&m_y, m11);
  emlrtSetFieldR2017b(y, 0, "CoeffP5", m_y, 9);
  n_y = NULL;
  m12 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m12) = u->sp_index;
  emlrtAssign(&n_y, m12);
  emlrtSetFieldR2017b(y, 0, "sp_index", n_y, 10);
  o_y = NULL;
  m13 = emlrtCreateDoubleScalar(u->FeedRate);
  emlrtAssign(&o_y, m13);
  emlrtSetFieldR2017b(y, 0, "FeedRate", o_y, 11);
  p_y = NULL;
  m14 = emlrtCreateDoubleScalar(u->SpindleSpeed);
  emlrtAssign(&p_y, m14);
  emlrtSetFieldR2017b(y, 0, "SpindleSpeed", p_y, 12);
  q_y = NULL;
  m15 = emlrtCreateDoubleScalar(u->MaxConstantFeedRate);
  emlrtAssign(&q_y, m15);
  emlrtSetFieldR2017b(y, 0, "MaxConstantFeedRate", q_y, 13);
  r_y = NULL;
  m16 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m16) = u->i_begin_sp;
  emlrtAssign(&r_y, m16);
  emlrtSetFieldR2017b(y, 0, "i_begin_sp", r_y, 14);
  s_y = NULL;
  m17 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m17) = u->i_end_sp;
  emlrtAssign(&s_y, m17);
  emlrtSetFieldR2017b(y, 0, "i_end_sp", s_y, 15);
  t_y = NULL;
  m18 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m18) = u->gcode_source_line;
  emlrtAssign(&t_y, m18);
  emlrtSetFieldR2017b(y, 0, "gcode_source_line", t_y, 16);
  u_y = NULL;
  m19 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m19) = u->index_smooth;
  emlrtAssign(&u_y, m19);
  emlrtSetFieldR2017b(y, 0, "index_smooth", u_y, 17);
  emlrtSetFieldR2017b(y, 0, "UseConstJerk", c_emlrt_marshallOut(u->UseConstJerk),
                      18);
  v_y = NULL;
  m20 = emlrtCreateDoubleScalar(u->ConstJerk);
  emlrtAssign(&v_y, m20);
  emlrtSetFieldR2017b(y, 0, "ConstJerk", v_y, 19);
  w_y = NULL;
  m21 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m21) = u->ConstJerkMaxIterations;
  emlrtAssign(&w_y, m21);
  emlrtSetFieldR2017b(y, 0, "ConstJerkMaxIterations", w_y, 20);
  emlrtSetFieldR2017b(y, 0, "Coeff", h_emlrt_marshallOut(u->Coeff), 21);
  x_y = NULL;
  m22 = emlrtCreateDoubleScalar(u->a_param);
  emlrtAssign(&x_y, m22);
  emlrtSetFieldR2017b(y, 0, "a_param", x_y, 22);
  y_y = NULL;
  m23 = emlrtCreateDoubleScalar(u->b_param);
  emlrtAssign(&y_y, m23);
  emlrtSetFieldR2017b(y, 0, "b_param", y_y, 23);
  ab_y = NULL;
  emlrtAssign(&ab_y, emlrtCreateStructMatrix(1, 1, 5, b_sv1));
  emlrtSetFieldR2017b(ab_y, 0, "CoeffX", i_emlrt_marshallOut(u->sp.CoeffX), 0);
  emlrtSetFieldR2017b(ab_y, 0, "CoeffY", i_emlrt_marshallOut(u->sp.CoeffY), 1);
  emlrtSetFieldR2017b(ab_y, 0, "CoeffZ", i_emlrt_marshallOut(u->sp.CoeffZ), 2);
  emlrtSetFieldR2017b(ab_y, 0, "Bl", j_emlrt_marshallOut(u->sp.Bl), 3);
  emlrtSetFieldR2017b(ab_y, 0, "knots", i_emlrt_marshallOut(u->sp.knots), 4);
  emlrtSetFieldR2017b(y, 0, "sp", ab_y, 24);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T **y_data
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void gb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[2])
{
  hc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void gc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv[0],
    b_iv);
  ret->allocatedSize = b_iv[0] * b_iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[3]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[3])
{
  wb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *h_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  int32_T b_iv[1];
  const mxArray *m;
  real_T *pData;
  int32_T i;
  int32_T b_i;
  y = NULL;
  b_iv[0] = u->size[0];
  m = emlrtCreateNumericArray(1, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u->data[b_i];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *P0
 *                const char_T *identifier
 * Return Type  : real_T (*)[3]
 */
static real_T (*hb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *P0,
  const char_T *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = ib_emlrt_marshallIn(sp, emlrtAlias(P0), &thisId);
  emlrtDestroyArray(&P0);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T **ret_data
 *                int32_T ret_size[2]
 * Return Type  : void
 */
  static void hc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 12 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv[0],
    b_iv);
  ret_size[0] = b_iv[0];
  ret_size[1] = b_iv[1];
  *ret_data = (real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y[1024]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[1024])
{
  xb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *i_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  int32_T b_iv[2];
  const mxArray *m;
  real_T *pData;
  int32_T i;
  int32_T b_i;
  y = NULL;
  b_iv[0] = u->size[0];
  b_iv[1] = u->size[1];
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < u->size[1]; b_i++) {
    pData[i] = u->data[b_i];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[3]
 */
static real_T (*ib_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  real_T (*y)[3];
  y = ic_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[3]
 */
  static real_T (*ic_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real_T (*ret)[3];
  static const int32_T dims[1] = { 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : struct0_T
 */
static struct0_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  struct0_T y;
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[2] = { "Skip", "ColTolDeg" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 2, fieldNames, 0U, &dims);
  thisId.fIdentifier = "Skip";
  y.Skip = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0,
    "Skip")), &thisId);
  thisId.fIdentifier = "ColTolDeg";
  y.ColTolDeg = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    1, "ColTolDeg")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const SplineBase u
 * Return Type  : const mxArray *
 */
static const mxArray *j_emlrt_marshallOut(const SplineBase u)
{
  const mxArray *y;
  static const char * b_sv[4] = { "ncoeff", "breakpoints", "handle", "degree" };

  const mxArray *b_y;
  const mxArray *m;
  const mxArray *c_y;
  const mxArray *m1;
  const mxArray *d_y;
  const mxArray *m2;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 4, b_sv));
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = u.ncoeff;
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, "ncoeff", b_y, 0);
  emlrtSetFieldR2017b(y, 0, "breakpoints", i_emlrt_marshallOut(u.breakpoints), 1);
  c_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
  *(uint64_T *)emlrtMxGetData(m1) = u.handle;
  emlrtAssign(&c_y, m1);
  emlrtSetFieldR2017b(y, 0, "handle", c_y, 2);
  d_y = NULL;
  m2 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m2) = u.degree;
  emlrtAssign(&d_y, m2);
  emlrtSetFieldR2017b(y, 0, "degree", d_y, 3);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *b_ZSpdMode
 *                const char_T *identifier
 * Return Type  : ZSpdMode
 */
static ZSpdMode jb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *b_ZSpdMode, const char_T *identifier)
{
  ZSpdMode y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = s_emlrt_marshallIn(sp, emlrtAlias(b_ZSpdMode), &thisId);
  emlrtDestroyArray(&b_ZSpdMode);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[10]
 */
static real_T (*jc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[10]
{
  real_T (*ret)[10];
  static const int32_T dims[2] = { 1, 10 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[10])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y[9]
 * Return Type  : void
 */
  static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[9])
{
  yb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *k_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  int32_T b_iv[2];
  const mxArray *m;
  real_T *pData;
  int32_T i;
  int32_T b_i;
  int32_T c_i;
  y = NULL;
  b_iv[0] = u->size[0];
  b_iv[1] = u->size[1];
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < u->size[1]; b_i++) {
    for (c_i = 0; c_i < u->size[0]; c_i++) {
      pData[i] = u->data[c_i + u->size[0] * b_i];
      i++;
    }
  }

  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *breakpoints
 *                const char_T *identifier
 * Return Type  : real_T (*)[10]
 */
static real_T (*kb_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *breakpoints, const char_T *identifier))[10]
{
  real_T (*y)[10];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = lb_emlrt_marshallIn(sp, emlrtAlias(breakpoints), &thisId);
  emlrtDestroyArray(&breakpoints);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret_data[]
 *                int32_T ret_size[2]
 * Return Type  : void
 */
  static void kc_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId, char_T ret_data[], int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 1024 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims, &bv[0],
    b_iv);
  ret_size[0] = b_iv[0];
  ret_size[1] = b_iv[1];
  emlrtImportArrayR2015b(sp, src, (void *)ret_data, 1, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *ctx
 *                const char_T *identifier
 *                FeedoptContext *y
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *ctx, const
  char_T *identifier, FeedoptContext *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  m_emlrt_marshallIn(sp, emlrtAlias(ctx), &thisId, y);
  emlrtDestroyArray(&ctx);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const creal_T u_data[]
 *                const int32_T u_size[1]
 * Return Type  : const mxArray *
 */
static const mxArray *l_emlrt_marshallOut(const emlrtStack *sp, const creal_T
  u_data[], const int32_T u_size[1])
{
  const mxArray *y;
  int32_T b_iv[1];
  const mxArray *m;
  y = NULL;
  b_iv[0] = u_size[0];
  m = emlrtCreateNumericArray(1, &b_iv[0], mxDOUBLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b(sp, m, (void *)&u_data[0], 8);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[10]
 */
static real_T (*lb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[10]
{
  real_T (*y)[10];
  y = jc_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                FeedoptContext *y
 * Return Type  : void
 */
  static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, FeedoptContext *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[31] = { "op", "go_next", "q_gcode",
    "q_compress", "q_splines", "q_smooth", "q_split", "q_opt", "try_push_again",
    "n_optimized", "reached_end", "k0", "v_0", "v_1", "at_0", "at_1", "cfg",
    "Bl", "u_vec", "errcode", "jmax_increase_count", "zero_start", "zero_end",
    "forced_stop", "programmed_stop", "BasisVal", "BasisValD", "BasisValDD",
    "BasisIntegr", "Coeff", "Skipped" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 31, fieldNames, 0U, &dims);
  thisId.fIdentifier = "op";
  y->op = n_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0,
    "op")), &thisId);
  thisId.fIdentifier = "go_next";
  y->go_next = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1,
    "go_next")), &thisId);
  thisId.fIdentifier = "q_gcode";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2, "q_gcode")),
                     &thisId, &y->q_gcode);
  thisId.fIdentifier = "q_compress";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3,
    "q_compress")), &thisId, &y->q_compress);
  thisId.fIdentifier = "q_splines";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 4, "q_splines")),
                     &thisId, &y->q_splines);
  thisId.fIdentifier = "q_smooth";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 5, "q_smooth")),
                     &thisId, &y->q_smooth);
  thisId.fIdentifier = "q_split";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 6, "q_split")),
                     &thisId, &y->q_split);
  thisId.fIdentifier = "q_opt";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 7, "q_opt")),
                     &thisId, &y->q_opt);
  thisId.fIdentifier = "try_push_again";
  y->try_push_again = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp,
    u, 0, 8, "try_push_again")), &thisId);
  thisId.fIdentifier = "n_optimized";
  y->n_optimized = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 9, "n_optimized")), &thisId);
  thisId.fIdentifier = "reached_end";
  y->reached_end = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 10, "reached_end")), &thisId);
  thisId.fIdentifier = "k0";
  y->k0 = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 11,
    "k0")), &thisId);
  thisId.fIdentifier = "v_0";
  y->v_0 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 12,
    "v_0")), &thisId);
  thisId.fIdentifier = "v_1";
  y->v_1 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 13,
    "v_1")), &thisId);
  thisId.fIdentifier = "at_0";
  y->at_0 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 14,
    "at_0")), &thisId);
  thisId.fIdentifier = "at_1";
  y->at_1 = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 15,
    "at_1")), &thisId);
  thisId.fIdentifier = "cfg";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 16, "cfg")),
                     &thisId, &y->cfg);
  thisId.fIdentifier = "Bl";
  y_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 17, "Bl")),
                     &thisId, &y->Bl);
  thisId.fIdentifier = "u_vec";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 18, "u_vec")),
                     &thisId, y->u_vec);
  thisId.fIdentifier = "errcode";
  y->errcode = ab_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    19, "errcode")), &thisId);
  thisId.fIdentifier = "jmax_increase_count";
  y->jmax_increase_count = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 20, "jmax_increase_count")), &thisId);
  thisId.fIdentifier = "zero_start";
  y->zero_start = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    21, "zero_start")), &thisId);
  thisId.fIdentifier = "zero_end";
  y->zero_end = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    22, "zero_end")), &thisId);
  thisId.fIdentifier = "forced_stop";
  y->forced_stop = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 23, "forced_stop")), &thisId);
  thisId.fIdentifier = "programmed_stop";
  y->programmed_stop = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp,
    u, 0, 24, "programmed_stop")), &thisId);
  thisId.fIdentifier = "BasisVal";
  bb_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 25,
    "BasisVal")), &thisId, y->BasisVal);
  thisId.fIdentifier = "BasisValD";
  bb_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 26,
    "BasisValD")), &thisId, y->BasisValD);
  thisId.fIdentifier = "BasisValDD";
  bb_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 27,
    "BasisValDD")), &thisId, y->BasisValDD);
  thisId.fIdentifier = "BasisIntegr";
  v_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 28,
    "BasisIntegr")), &thisId, y->BasisIntegr);
  thisId.fIdentifier = "Coeff";
  bb_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 29, "Coeff")),
                      &thisId, y->Coeff);
  thisId.fIdentifier = "Skipped";
  y->Skipped = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    30, "Skipped")), &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const TransitionResult u
 * Return Type  : const mxArray *
 */
static const mxArray *m_emlrt_marshallOut(const emlrtStack *sp, const
  TransitionResult u)
{
  const mxArray *y;
  const mxArray *m;
  static const char * enumNames[3] = { "Ok", "Collinear", "NoSolution" };

  static const int32_T enumValues[3] = { 0, 1, 2 };

  const mxArray *b_y;
  const mxArray *m1;
  y = NULL;
  m = NULL;
  emlrtCheckEnumR2012b(sp, "TransitionResult", 3, enumNames, enumValues);
  b_y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m1) = (int32_T)u;
  emlrtAssign(&b_y, m1);
  emlrtAssign(&m, b_y);
  emlrtAssign(&y, emlrtCreateEnumR2012b(sp, "TransitionResult", m));
  emlrtDestroyArray(&m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *state
 *                const char_T *identifier
 * Return Type  : ResampleStateClass
 */
static ResampleStateClass mb_emlrt_marshallIn(const emlrtStack *sp, const
  mxArray *state, const char_T *identifier)
{
  ResampleStateClass y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = nb_emlrt_marshallIn(sp, emlrtAlias(state), &thisId);
  emlrtDestroyArray(&state);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Fopt
 */
static Fopt n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  Fopt y;
  static const int32_T dims = 0;
  emlrtCheckEnumR2012b(sp, "Fopt", 8, sv, iv);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "Fopt", false, 0U, &dims);
  y = (Fopt)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const ResampleStateClass u
 * Return Type  : const mxArray *
 */
static const mxArray *n_emlrt_marshallOut(const emlrtStack *sp, const
  ResampleStateClass u)
{
  const mxArray *y;
  const mxArray *m;
  const mxArray *b_y;
  const mxArray *m1;
  const mxArray *propValues[3];
  const mxArray *m2;
  const mxArray *m3;
  const mxArray *c_y;
  const mxArray *m4;
  y = NULL;
  emlrtAssign(&y, emlrtCreateClassInstance("ResampleStateClass"));
  m = NULL;
  b_y = NULL;
  m1 = emlrtCreateDoubleScalar(u.u);
  emlrtAssign(&b_y, m1);
  emlrtAssign(&m, b_y);
  propValues[0] = m;
  m2 = NULL;
  emlrtAssign(&m2, c_emlrt_marshallOut(u.go_next));
  propValues[1] = m2;
  m3 = NULL;
  c_y = NULL;
  m4 = emlrtCreateDoubleScalar(u.dt);
  emlrtAssign(&c_y, m4);
  emlrtAssign(&m3, c_y);
  propValues[2] = m3;
  emlrtSetAllProperties(sp, &y, 0, 3, sv6, sv7, propValues);
  emlrtAssign(&y, emlrtConvertInstanceToRedirectSource(sp, y, 0,
    "ResampleStateClass"));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : ResampleStateClass
 */
static ResampleStateClass nb_emlrt_marshallIn(const emlrtStack *sp, const
  mxArray *u, const emlrtMsgIdentifier *parentId)
{
  ResampleStateClass y;
  const mxArray *propValues[3];
  emlrtMsgIdentifier thisId;
  propValues[0] = NULL;
  propValues[1] = NULL;
  propValues[2] = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckMcosClass2017a(sp, parentId, u, "ResampleStateClass");
  emlrtGetAllProperties(sp, u, 0, 3, sv6, sv7, propValues);
  thisId.fIdentifier = "u";
  y.u = b_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId);
  thisId.fIdentifier = "go_next";
  y.go_next = g_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId);
  thisId.fIdentifier = "dt";
  y.dt = b_emlrt_marshallIn(sp, emlrtAlias(propValues[2]), &thisId);
  emlrtDestroyArrays(3, (const mxArray **)&propValues);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                queue_coder *y
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, queue_coder *y)
{
  const mxArray *propValues[2];
  emlrtMsgIdentifier thisId;
  propValues[0] = NULL;
  propValues[1] = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckMcosClass2017a(sp, parentId, u, "queue_coder");
  emlrtGetAllProperties(sp, u, 0, 2, sv2, sv3, propValues);
  thisId.fIdentifier = "ptr";
  y->ptr = p_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId);
  thisId.fIdentifier = "value_type";
  q_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId, &y->value_type);
  emlrtDestroyArrays(2, (const mxArray **)&propValues);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real_T u[3]
 * Return Type  : const mxArray *
 */
static const mxArray *o_emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T b_iv[1] = { 0 };

  static const int32_T b_iv1[1] = { 3 };

  y = NULL;
  m = emlrtCreateNumericArray(1, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, *(int32_T (*)[1])&b_iv1[0], 1);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Bl
 *                const char_T *identifier
 *                SplineBase *y
 * Return Type  : void
 */
static void ob_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Bl, const
  char_T *identifier, SplineBase *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y_emlrt_marshallIn(sp, emlrtAlias(Bl), &thisId, y);
  emlrtDestroyArray(&Bl);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : uint64_T
 */
static uint64_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  uint64_T y;
  y = ac_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *cfg
 *                const char_T *identifier
 * Return Type  : DebugCfg
 */
static DebugCfg pb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg,
  const char_T *identifier)
{
  DebugCfg y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = qb_emlrt_marshallIn(sp, emlrtAlias(cfg), &thisId);
  emlrtDestroyArray(&cfg);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                CurvStruct *y
 * Return Type  : void
 */
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, CurvStruct *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[25] = { "Type", "zspdmode", "P0", "P1",
    "CorrectedHelixCenter", "delta", "evec", "theta", "pitch", "CoeffP5",
    "sp_index", "FeedRate", "SpindleSpeed", "MaxConstantFeedRate", "i_begin_sp",
    "i_end_sp", "gcode_source_line", "index_smooth", "UseConstJerk", "ConstJerk",
    "ConstJerkMaxIterations", "Coeff", "a_param", "b_param", "sp" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 25, fieldNames, 0U, &dims);
  thisId.fIdentifier = "Type";
  y->Type = r_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0,
    "Type")), &thisId);
  thisId.fIdentifier = "zspdmode";
  y->zspdmode = s_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    1, "zspdmode")), &thisId);
  thisId.fIdentifier = "P0";
  t_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2, "P0")),
                     &thisId, y->P0);
  thisId.fIdentifier = "P1";
  t_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3, "P1")),
                     &thisId, y->P1);
  thisId.fIdentifier = "CorrectedHelixCenter";
  t_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 4,
    "CorrectedHelixCenter")), &thisId, y->CorrectedHelixCenter);
  thisId.fIdentifier = "delta";
  y->delta = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 5,
    "delta")), &thisId);
  thisId.fIdentifier = "evec";
  t_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 6, "evec")),
                     &thisId, y->evec);
  thisId.fIdentifier = "theta";
  y->theta = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 7,
    "theta")), &thisId);
  thisId.fIdentifier = "pitch";
  y->pitch = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 8,
    "pitch")), &thisId);
  thisId.fIdentifier = "CoeffP5";
  u_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 9, "CoeffP5")),
                     &thisId, y->CoeffP5);
  thisId.fIdentifier = "sp_index";
  y->sp_index = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    10, "sp_index")), &thisId);
  thisId.fIdentifier = "FeedRate";
  y->FeedRate = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    11, "FeedRate")), &thisId);
  thisId.fIdentifier = "SpindleSpeed";
  y->SpindleSpeed = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 12, "SpindleSpeed")), &thisId);
  thisId.fIdentifier = "MaxConstantFeedRate";
  y->MaxConstantFeedRate = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 13, "MaxConstantFeedRate")), &thisId);
  thisId.fIdentifier = "i_begin_sp";
  y->i_begin_sp = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    14, "i_begin_sp")), &thisId);
  thisId.fIdentifier = "i_end_sp";
  y->i_end_sp = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    15, "i_end_sp")), &thisId);
  thisId.fIdentifier = "gcode_source_line";
  y->gcode_source_line = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b
    (sp, u, 0, 16, "gcode_source_line")), &thisId);
  thisId.fIdentifier = "index_smooth";
  y->index_smooth = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 17, "index_smooth")), &thisId);
  thisId.fIdentifier = "UseConstJerk";
  y->UseConstJerk = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u,
    0, 18, "UseConstJerk")), &thisId);
  thisId.fIdentifier = "ConstJerk";
  y->ConstJerk = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    19, "ConstJerk")), &thisId);
  thisId.fIdentifier = "ConstJerkMaxIterations";
  y->ConstJerkMaxIterations = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2017b(sp, u, 0, 20, "ConstJerkMaxIterations")), &thisId);
  thisId.fIdentifier = "Coeff";
  v_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 21, "Coeff")),
                     &thisId, y->Coeff);
  thisId.fIdentifier = "a_param";
  y->a_param = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    22, "a_param")), &thisId);
  thisId.fIdentifier = "b_param";
  y->b_param = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0,
    23, "b_param")), &thisId);
  thisId.fIdentifier = "sp";
  w_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 24, "sp")),
                     &thisId, &y->sp);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : DebugCfg
 */
static DebugCfg qb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  DebugCfg y;
  static const char * enumNames[8] = { "Transitions", "OptimProgress",
    "FeedratePlanning", "Global", "Warning", "Error", "Plots", "Validate" };

  static const int32_T enumValues[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

  static const int32_T dims = 0;
  emlrtCheckEnumR2012b(sp, "DebugCfg", 8, enumNames, enumValues);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "DebugCfg", false, 0U, &dims);
  y = (DebugCfg)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : CurveType
 */
static CurveType r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  CurveType y;
  static const int32_T dims = 0;
  emlrtCheckEnumR2012b(sp, "CurveType", 5, sv4, iv2);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "CurveType", false, 0U, &dims);
  y = (CurveType)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *filename
 *                const char_T *identifier
 *                char_T y_data[]
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void rb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *filename,
  const char_T *identifier, char_T y_data[], int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  sb_emlrt_marshallIn(sp, emlrtAlias(filename), &thisId, y_data, y_size);
  emlrtDestroyArray(&filename);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : ZSpdMode
 */
static ZSpdMode s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  ZSpdMode y;
  static const int32_T dims = 0;
  emlrtCheckEnumR2012b(sp, "ZSpdMode", 4, sv5, iv1);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "ZSpdMode", false, 0U, &dims);
  y = (ZSpdMode)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y_data[]
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void sb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y_data[], int32_T y_size[2])
{
  kc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[3]
 * Return Type  : void
 */
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[3])
{
  bc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T tb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[6][3]
 * Return Type  : void
 */
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[6][3])
{
  cc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : int32_T
 */
static int32_T ub_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  int32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "int32", false, 0U, &dims);
  ret = *(int32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  dc_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : boolean_T
 */
static boolean_T vb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  boolean_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "logical", false, 0U, &dims);
  ret = *emlrtMxGetLogicals(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                SplineStruct *y
 * Return Type  : void
 */
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, SplineStruct *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[5] = { "CoeffX", "CoeffY", "CoeffZ", "Bl",
    "knots" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 5, fieldNames, 0U, &dims);
  thisId.fIdentifier = "CoeffX";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0, "CoeffX")),
                     &thisId, y->CoeffX);
  thisId.fIdentifier = "CoeffY";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1, "CoeffY")),
                     &thisId, y->CoeffY);
  thisId.fIdentifier = "CoeffZ";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2, "CoeffZ")),
                     &thisId, y->CoeffZ);
  thisId.fIdentifier = "Bl";
  y_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3, "Bl")),
                     &thisId, &y->Bl);
  thisId.fIdentifier = "knots";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 4, "knots")),
                     &thisId, y->knots);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[3]
 * Return Type  : void
 */
static void wb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[3])
{
  static const int32_T dims[2] = { 1, 3 };

  real_T (*r)[3];
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  r = (real_T (*)[3])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  ec_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret[1024]
 * Return Type  : void
 */
static void xb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[1024])
{
  static const int32_T dims[2] = { 1, 1024 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims);
  emlrtImportCharArrayR2015b(sp, src, &ret[0], 1024);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                SplineBase *y
 * Return Type  : void
 */
static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, SplineBase *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[4] = { "ncoeff", "breakpoints", "handle",
    "degree" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 4, fieldNames, 0U, &dims);
  thisId.fIdentifier = "ncoeff";
  y->ncoeff = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0,
    "ncoeff")), &thisId);
  thisId.fIdentifier = "breakpoints";
  x_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1,
    "breakpoints")), &thisId, y->breakpoints);
  thisId.fIdentifier = "handle";
  y->handle = p_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2,
    "handle")), &thisId);
  thisId.fIdentifier = "degree";
  y->degree = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3,
    "degree")), &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret[9]
 * Return Type  : void
 */
static void yb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[9])
{
  static const int32_T dims[2] = { 1, 9 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims);
  emlrtImportCharArrayR2015b(sp, src, &ret[0], 9);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[4]
 * Return Type  : void
 */
void CalcTransition_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[4])
{
  FeedoptContext ctx;
  CurvStruct CurvStruct1;
  CurvStruct CurvStruct2;
  CurvStruct CurvStruct1_C;
  CurvStruct CurvStruct_T;
  CurvStruct CurvStruct2_C;
  TransitionResult status;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_FeedoptContext(&st, &ctx, true);
  emxInitStruct_CurvStruct(&st, &CurvStruct1, true);
  emxInitStruct_CurvStruct(&st, &CurvStruct2, true);
  emxInitStruct_CurvStruct(&st, &CurvStruct1_C, true);
  emxInitStruct_CurvStruct(&st, &CurvStruct_T, true);
  emxInitStruct_CurvStruct(&st, &CurvStruct2_C, true);

  /* Marshall function inputs */
  l_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ctx", &ctx);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "CurvStruct1", &CurvStruct1);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "CurvStruct2", &CurvStruct2);

  /* Invoke the target function */
  CalcTransition(ctx, CurvStruct1, CurvStruct2, &CurvStruct1_C, &CurvStruct_T,
                 &CurvStruct2_C, &status);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &CurvStruct1_C);
  emxFreeStruct_CurvStruct(&CurvStruct1_C);
  emxFreeStruct_CurvStruct(&CurvStruct2);
  emxFreeStruct_CurvStruct(&CurvStruct1);
  emxFreeStruct_FeedoptContext(&ctx);
  if (nlhs > 1) {
    plhs[1] = g_emlrt_marshallOut(&st, &CurvStruct_T);
  }

  emxFreeStruct_CurvStruct(&CurvStruct_T);
  if (nlhs > 2) {
    plhs[2] = g_emlrt_marshallOut(&st, &CurvStruct2_C);
  }

  emxFreeStruct_CurvStruct(&CurvStruct2_C);
  if (nlhs > 3) {
    plhs[3] = m_emlrt_marshallOut(&st, status);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ConfigSetSource_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[1])
{
  FeedoptConfig cfg;
  char_T filename_data[1024];
  int32_T filename_size[2];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "cfg", &cfg);
  rb_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "filename", filename_data,
                      filename_size);

  /* Invoke the target function */
  ConfigSetSource(&cfg, filename_data, filename_size);

  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(&st, &cfg);
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ConstrCurvStructType_api(int32_T nlhs, const mxArray *plhs[1])
{
  CurvStruct C;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &C, true);

  /* Invoke the target function */
  ConstrCurvStructType(&C);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &C);
  emxFreeStruct_CurvStruct(&C);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[11]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ConstrHelixStructFromArcFeed_api(const mxArray * const prhs[11], int32_T
  nlhs, const mxArray *plhs[1])
{
  CurvStruct b_CurvStruct;
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
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &b_CurvStruct, true);

  /* Marshall function inputs */
  p0x = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "p0x");
  p0y = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "p0y");
  p0z = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "p0z");
  p1x = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "p1x");
  p1y = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "p1y");
  p1z = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "p1z");
  cx = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "cx");
  cy = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "cy");
  cz = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "cz");
  rotation = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "rotation");
  evec = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "evec");

  /* Invoke the target function */
  ConstrHelixStructFromArcFeed(p0x, p0y, p0z, p1x, p1y, p1z, cx, cy, cz,
    rotation, *evec, &b_CurvStruct);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &b_CurvStruct);
  emxFreeStruct_CurvStruct(&b_CurvStruct);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[9]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ConstrHelixStruct_api(const mxArray * const prhs[9], int32_T nlhs, const
  mxArray *plhs[1])
{
  CurvStruct b_CurvStruct;
  real_T (*P0)[3];
  real_T (*P1)[3];
  real_T (*Cprim)[3];
  real_T delta;
  real_T (*evec)[3];
  real_T theta;
  real_T pitch;
  real_T FeedRate;
  ZSpdMode b_ZSpdMode;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &b_CurvStruct, true);

  /* Marshall function inputs */
  P0 = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "P0");
  P1 = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "P1");
  Cprim = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "Cprim");
  delta = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "delta");
  evec = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "evec");
  theta = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "theta");
  pitch = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "pitch");
  FeedRate = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "FeedRate");
  b_ZSpdMode = jb_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "ZSpdMode");

  /* Invoke the target function */
  ConstrHelixStruct(*P0, *P1, *Cprim, delta, *evec, theta, pitch, FeedRate,
                    b_ZSpdMode, &b_CurvStruct);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &b_CurvStruct);
  emxFreeStruct_CurvStruct(&b_CurvStruct);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[4]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ConstrLineStruct_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[1])
{
  CurvStruct b_CurvStruct;
  real_T (*P0)[3];
  real_T (*P1)[3];
  real_T FeedRate;
  ZSpdMode b_ZSpdMode;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &b_CurvStruct, true);

  /* Marshall function inputs */
  P0 = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "P0");
  P1 = hb_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "P1");
  FeedRate = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "FeedRate");
  b_ZSpdMode = jb_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "ZSpdMode");

  /* Invoke the target function */
  ConstrLineStruct(*P0, *P1, FeedRate, b_ZSpdMode, &b_CurvStruct);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &b_CurvStruct);
  emxFreeStruct_CurvStruct(&b_CurvStruct);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void CopyCurvStruct_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1])
{
  CurvStruct Curv;
  CurvStruct Copy;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &Curv, true);
  emxInitStruct_CurvStruct(&st, &Copy, true);

  /* Marshall function inputs */
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Curv", &Curv);

  /* Invoke the target function */
  CopyCurvStruct(Curv, &Copy);

  /* Marshall function outputs */
  plhs[0] = g_emlrt_marshallOut(&st, &Copy);
  emxFreeStruct_CurvStruct(&Copy);
  emxFreeStruct_CurvStruct(&Curv);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 * Return Type  : void
 */
void DisableDebugLog_api(const mxArray * const prhs[1], int32_T nlhs)
{
  DebugCfg cfg;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  cfg = pb_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "cfg");

  /* Invoke the target function */
  DisableDebugLog(cfg);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 * Return Type  : void
 */
void EnableDebugLog_api(const mxArray * const prhs[1], int32_T nlhs)
{
  DebugCfg cfg;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  cfg = pb_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "cfg");

  /* Invoke the target function */
  EnableDebugLog(cfg);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[4]
 * Return Type  : void
 */
void EvalCurvStruct_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[4])
{
  FeedoptContext ctx;
  CurvStruct b_CurvStruct;
  emxArray_real_T *u_vec;
  emxArray_real_T *r0D;
  emxArray_real_T *r1D;
  emxArray_real_T *r2D;
  emxArray_real_T *r3D;
  const mxArray *prhs_copy_idx_0;
  const mxArray *prhs_copy_idx_1;
  const mxArray *prhs_copy_idx_2;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_FeedoptContext(&st, &ctx, true);
  emxInitStruct_CurvStruct(&st, &b_CurvStruct, true);
  emxInit_real_T(&st, &u_vec, 2, true);
  emxInit_real_T(&st, &r0D, 2, true);
  emxInit_real_T(&st, &r1D, 2, true);
  emxInit_real_T(&st, &r2D, 2, true);
  emxInit_real_T(&st, &r3D, 2, true);
  prhs_copy_idx_0 = prhs[0];
  prhs_copy_idx_1 = prhs[1];
  prhs_copy_idx_2 = emlrtProtectR2012b(prhs[2], 2, false, -1);

  /* Marshall function inputs */
  l_emlrt_marshallIn(&st, emlrtAliasP(prhs_copy_idx_0), "ctx", &ctx);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs_copy_idx_1), "CurvStruct",
                      &b_CurvStruct);
  u_vec->canFreeData = false;
  db_emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_2), "u_vec", u_vec);

  /* Invoke the target function */
  EvalCurvStruct(ctx, b_CurvStruct, u_vec, r0D, r1D, r2D, r3D);

  /* Marshall function outputs */
  r0D->canFreeData = false;
  plhs[0] = emlrt_marshallOut(r0D);
  emxFree_real_T(&r0D);
  emxFree_real_T(&u_vec);
  emxFreeStruct_CurvStruct(&b_CurvStruct);
  emxFreeStruct_FeedoptContext(&ctx);
  if (nlhs > 1) {
    r1D->canFreeData = false;
    plhs[1] = emlrt_marshallOut(r1D);
  }

  emxFree_real_T(&r1D);
  if (nlhs > 2) {
    r2D->canFreeData = false;
    plhs[2] = emlrt_marshallOut(r2D);
  }

  emxFree_real_T(&r2D);
  if (nlhs > 3) {
    r3D->canFreeData = false;
    plhs[3] = emlrt_marshallOut(r3D);
  }

  emxFree_real_T(&r3D);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void EvalPosition_api(const mxArray * const prhs[3], int32_T nlhs, const mxArray
                      *plhs[1])
{
  real_T (*r0D)[3];
  CurvStruct Curv;
  CurvStruct Spline;
  real_T u;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  r0D = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_CurvStruct(&st, &Curv, true);
  emxInitStruct_CurvStruct(&st, &Spline, true);

  /* Marshall function inputs */
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Curv", &Curv);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Spline", &Spline);
  u = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "u");

  /* Invoke the target function */
  EvalPosition(Curv, Spline, u, *r0D);

  /* Marshall function outputs */
  plhs[0] = o_emlrt_marshallOut(*r0D);
  emxFreeStruct_CurvStruct(&Spline);
  emxFreeStruct_CurvStruct(&Curv);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void FeedoptDefaultConfig_api(int32_T nlhs, const mxArray *plhs[1])
{
  FeedoptConfig cfg;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Invoke the target function */
  FeedoptDefaultConfig(&cfg);

  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(&st, &cfg);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void FeedoptPlan_api(const mxArray * const prhs[1], int32_T nlhs, const mxArray *
                     plhs[3])
{
  FeedoptContext ctx;
  CurvStruct opt_struct;
  boolean_T optimized;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_FeedoptContext(&st, &ctx, true);
  emxInitStruct_CurvStruct(&st, &opt_struct, true);

  /* Marshall function inputs */
  l_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ctx", &ctx);

  /* Invoke the target function */
  FeedoptPlan(&ctx, &optimized, &opt_struct);

  /* Marshall function outputs */
  plhs[0] = e_emlrt_marshallOut(&st, &ctx);
  emxFreeStruct_FeedoptContext(&ctx);
  if (nlhs > 1) {
    plhs[1] = c_emlrt_marshallOut(optimized);
  }

  if (nlhs > 2) {
    plhs[2] = g_emlrt_marshallOut(&st, &opt_struct);
  }

  emxFreeStruct_CurvStruct(&opt_struct);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void InitFeedoptPlan_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1])
{
  FeedoptContext ctx;
  FeedoptConfig cfg;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_FeedoptContext(&st, &ctx, true);

  /* Marshall function inputs */
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "cfg", &cfg);

  /* Invoke the target function */
  InitFeedoptPlan(cfg, &ctx);

  /* Marshall function outputs */
  plhs[0] = e_emlrt_marshallOut(&st, &ctx);
  emxFreeStruct_FeedoptContext(&ctx);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                int32_T nlhs
 * Return Type  : void
 */
void PrintCurvStruct_api(const mxArray * const prhs[2], int32_T nlhs)
{
  FeedoptContext ctx;
  CurvStruct S;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_FeedoptContext(&st, &ctx, true);
  emxInitStruct_CurvStruct(&st, &S, true);

  /* Marshall function inputs */
  l_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ctx", &ctx);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "S", &S);

  /* Invoke the target function */
  PrintCurvStruct(ctx, S);
  emxFreeStruct_CurvStruct(&S);
  emxFreeStruct_FeedoptContext(&ctx);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ResampleNoCtx_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1])
{
  SplineBase Bl;
  CurvStruct Curv;
  ResampleStateClass state;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_SplineBase(&st, &Bl, true);
  emxInitStruct_CurvStruct(&st, &Curv, true);

  /* Marshall function inputs */
  state = mb_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "state");
  ob_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Bl", &Bl);
  cb_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "Curv", &Curv);

  /* Invoke the target function */
  ResampleNoCtx(&state, Bl, Curv);

  /* Marshall function outputs */
  plhs[0] = n_emlrt_marshallOut(&st, state);
  emxFreeStruct_CurvStruct(&Curv);
  emxFreeStruct_SplineBase(&Bl);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ResampleState_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1])
{
  real_T dt;
  ResampleStateClass state;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  dt = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "dt");

  /* Invoke the target function */
  ResampleState(dt, &state);

  /* Marshall function outputs */
  plhs[0] = n_emlrt_marshallOut(&st, state);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void bspline_copy_api(const mxArray * const prhs[1], int32_T nlhs, const mxArray
                      *plhs[1])
{
  SplineBase Bl;
  SplineBase Copy;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_SplineBase(&st, &Bl, true);
  emxInitStruct_SplineBase(&st, &Copy, true);

  /* Marshall function inputs */
  ob_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Bl", &Bl);

  /* Invoke the target function */
  bspline_copy(Bl, &Copy);

  /* Marshall function outputs */
  plhs[0] = j_emlrt_marshallOut(Copy);
  emxFreeStruct_SplineBase(&Copy);
  emxFreeStruct_SplineBase(&Bl);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void bspline_create_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[1])
{
  SplineBase Bl;
  int32_T degree;
  real_T (*breakpoints)[10];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_SplineBase(&st, &Bl, true);

  /* Marshall function inputs */
  degree = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "degree");
  breakpoints = kb_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "breakpoints");

  /* Invoke the target function */
  bspline_create(degree, *breakpoints, &Bl);

  /* Marshall function outputs */
  plhs[0] = j_emlrt_marshallOut(Bl);
  emxFreeStruct_SplineBase(&Bl);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void c_roots__api(const mxArray * const prhs[1], int32_T nlhs, const mxArray
                  *plhs[1])
{
  real_T (*coeffs_data)[12];
  int32_T coeffs_size[2];
  creal_T Y_data[11];
  int32_T Y_size[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  fb_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "coeffs", (real_T **)
                      &coeffs_data, coeffs_size);

  /* Invoke the target function */
  c_roots_(*coeffs_data, coeffs_size, Y_data, Y_size);

  /* Marshall function outputs */
  plhs[0] = l_emlrt_marshallOut(&st, Y_data, Y_size);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void linspace_api(const mxArray * const prhs[3], int32_T nlhs, const mxArray
                  *plhs[1])
{
  emxArray_real_T *y;
  real_T d1;
  real_T d2;
  real_T n1;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &y, 2, true);

  /* Marshall function inputs */
  d1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "d1");
  d2 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "d2");
  n1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "n1");

  /* Invoke the target function */
  linspace(d1, d2, n1, y);

  /* Marshall function outputs */
  y->canFreeData = false;
  plhs[0] = emlrt_marshallOut(y);
  emxFree_real_T(&y);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void sinspace_api(const mxArray * const prhs[3], int32_T nlhs, const mxArray
                  *plhs[1])
{
  emxArray_real_T *x;
  real_T x0;
  real_T x1;
  int32_T N;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &x, 2, true);

  /* Marshall function inputs */
  x0 = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "x0");
  x1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "x1");
  N = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "N");

  /* Invoke the target function */
  sinspace(x0, x1, N, x);

  /* Marshall function outputs */
  x->canFreeData = false;
  plhs[0] = emlrt_marshallOut(x);
  emxFree_real_T(&x);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sinspace_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  sinspace_xil_terminate();
  sinspace_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sinspace_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sinspace_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_sinspace_api.c
 *
 * [EOF]
 */
