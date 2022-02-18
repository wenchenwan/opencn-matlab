//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_sinspace_api.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "_coder_sinspace_api.h"
#include "_coder_sinspace_mex.h"
#include "coder_array_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131611U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "sinspace",                                           // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

static const char_T *sv[8]{"Init",   "GCode", "Check", "Compress",
                           "Smooth", "Split", "Opt",   "Finished"};

static const int32_T iv[8]{0, 1, 2, 3, 4, 5, 6, 67};

static const char_T *sv1[4]{"Success", "SmoothingFailed", "SplittingFailed", "OptimizationFailed"};

static const int32_T iv1[4]{0, 1, 2, 3};

static const char_T *sv2[2]{"ptr", "value_type"};

static const char_T *sv3[2]{"queue_coder", "queue_coder"};

static const char_T *sv4[5]{"None", "Line", "Helix", "Spline", "TransP5"};

static const int32_T iv2[5]{0, 1, 2, 3, 4};

static const char_T *sv5[4]{"NN", "ZN", "NZ", "ZZ"};

static const char_T *sv6[3]{"u", "go_next", "dt"};

static const char_T *sv7[3]{"ResampleStateClass", "ResampleStateClass", "ResampleStateClass"};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret_data[],
                               int32_T ret_size[2]);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, char_T y[9]);

static int32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T **ret_data,
                               int32_T ret_size[2]);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 1U> &ret);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[3]);

static int32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *N, const char_T *identifier);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y);

static const mxArray *b_emlrt_marshallOut(const boolean_T u);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[1024]);

static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[6][3]);

static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *trafo,
                                    const char_T *identifier);

static const mxArray *c_emlrt_marshallOut(const coder::array<real_T, 2U> &u);

static const mxArray *c_emlrt_marshallOut(const real_T u[6][3]);

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Poff,
                                   const char_T *identifier))[3];

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[3]);

static struct0_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[9]);

static const mxArray *d_emlrt_marshallOut(const real_T u[3]);

static const mxArray *d_emlrt_marshallOut(const coder::array<real_T, 2U> &u);

static Fopt e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret);

static ZSpdMode e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_ZSpdMode,
                                   const char_T *identifier);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[3]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, SplineBase *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, CurvStruct *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, SplineStruct *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, queue_coder *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, coder::array<real_T, 1U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, char_T y[1024]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg, const char_T *identifier,
                             FeedoptConfig *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, FeedoptConfig *y);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T **y_data,
                             int32_T y_size[2]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T y[3]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *coeffs, const char_T *identifier,
                             real_T **y_data, int32_T y_size[2]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_CurvStruct,
                             const char_T *identifier, CurvStruct *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, char_T y_data[],
                             int32_T y_size[2]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *ctx, const char_T *identifier,
                             FeedoptContext *y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *filename,
                             const char_T *identifier, char_T y_data[], int32_T y_size[2]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_vec, const char_T *identifier,
                             coder::array<real_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, FeedoptContext *y);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x0, const char_T *identifier);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *Bl, const char_T *identifier,
                             SplineBase *y);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const CurvStruct *u);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const queue_coder *u);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const creal_T u_data[],
                                        const int32_T u_size);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const FeedoptContext *u);

static const mxArray *emlrt_marshallOut(const coder::array<real_T, 1U> &u);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const ResampleStateClass u);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const FeedoptConfig *u);

static const mxArray *emlrt_marshallOut(const real_T u[3]);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const TransitionResult u);

static const mxArray *emlrt_marshallOut(const SplineBase *u);

static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u);

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret);

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[6][3]);

static uint64_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *breakpoints,
                                   const char_T *identifier))[10];

static CurveType g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId);

static ResampleStateClass g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *state,
                                             const char_T *identifier);

static DebugCfg h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg,
                                   const char_T *identifier);

static ZSpdMode h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static FeedoptPlanError i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                           const emlrtMsgIdentifier *parentId);

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3];

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10];

static ResampleStateClass l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                             const emlrtMsgIdentifier *parentId);

static DebugCfg m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static real_T n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static int32_T o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId);

static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId);

static uint64_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

static real_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T (*s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10];

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y)
{
    e_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                char_T ret_data[]
//                int32_T ret_size[2]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret_data[],
                               int32_T ret_size[2])
{
    static const int32_T dims[2]{1, 1024};
    int32_T b_iv[2];
    const boolean_T bv[2]{false, true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"char", false, 2U,
                              (void *)&dims[0], &bv[0], &b_iv[0]);
    ret_size[0] = b_iv[0];
    ret_size[1] = b_iv[1];
    emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret_data[0], 1, false);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                char_T y[9]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, char_T y[9])
{
    d_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 1U> &ret
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 1U> &ret)
{
    static const int32_T dims{-1};
    int32_T i;
    const boolean_T b{true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 1U,
                              (void *)&dims, &b, &i);
    ret.set_size(i);
    emlrtImportArrayR2015b((emlrtCTX)sp, src, &(ret.data())[0], 8, false);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *N
//                const char_T *identifier
// Return Type  : int32_T
//
static int32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *N, const char_T *identifier)
{
    emlrtMsgIdentifier thisId;
    int32_T y;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = b_emlrt_marshallIn(sp, emlrtAlias(N), &thisId);
    emlrtDestroyArray(&N);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real_T y[3]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[3])
{
    e_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : int32_T
//
static int32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId)
{
    int32_T y;
    y = o_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real_T **ret_data
//                int32_T ret_size[2]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T **ret_data,
                               int32_T ret_size[2])
{
    static const int32_T dims[2]{1, 12};
    int32_T b_iv[2];
    const boolean_T bv[2]{false, true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                              (void *)&dims[0], &bv[0], &b_iv[0]);
    ret_size[0] = b_iv[0];
    ret_size[1] = b_iv[1];
    *ret_data = (real_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const boolean_T u
// Return Type  : const mxArray *
//
static const mxArray *b_emlrt_marshallOut(const boolean_T u)
{
    const mxArray *m;
    const mxArray *y;
    y = nullptr;
    m = emlrtCreateLogicalScalar(u);
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *trafo
//                const char_T *identifier
// Return Type  : boolean_T
//
static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *trafo,
                                    const char_T *identifier)
{
    emlrtMsgIdentifier thisId;
    boolean_T y;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = c_emlrt_marshallIn(sp, emlrtAlias(trafo), &thisId);
    emlrtDestroyArray(&trafo);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : boolean_T
//
static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId)
{
    boolean_T y;
    y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real_T y[6][3]
// Return Type  : void
//
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[6][3])
{
    f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                char_T ret[1024]
// Return Type  : void
//
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[1024])
{
    static const int32_T dims[2]{1, 1024};
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"char", false, 2U,
                            (void *)&dims[0]);
    emlrtImportCharArrayR2015b((emlrtCTX)sp, src, &ret[0], 1024);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y)
{
    f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const coder::array<real_T, 2U> &u
// Return Type  : const mxArray *
//
static const mxArray *c_emlrt_marshallOut(const coder::array<real_T, 2U> &u)
{
    const mxArray *m;
    const mxArray *y;
    real_T *pData;
    int32_T b_iv[2];
    int32_T i;
    y = nullptr;
    b_iv[0] = 1;
    b_iv[1] = u.size(1);
    m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i{0}; b_i < u.size(1); b_i++) {
        pData[i] = u[b_i];
        i++;
    }
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const real_T u[6][3]
// Return Type  : const mxArray *
//
static const mxArray *c_emlrt_marshallOut(const real_T u[6][3])
{
    static const int32_T b_iv[2]{3, 6};
    const mxArray *m;
    const mxArray *y;
    real_T *pData;
    int32_T i;
    y = nullptr;
    m = emlrtCreateNumericArray(2, (const void *)&b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i{0}; b_i < 6; b_i++) {
        pData[i] = u[b_i][0];
        pData[i + 1] = u[b_i][1];
        pData[i + 2] = u[b_i][2];
        i += 3;
    }
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real_T ret[3]
// Return Type  : void
//
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[3])
{
    static const int32_T dims[2]{1, 3};
    real_T(*r)[3];
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                            (void *)&dims[0]);
    r = (real_T(*)[3])emlrtMxGetData(src);
    ret[0] = (*r)[0];
    ret[1] = (*r)[1];
    ret[2] = (*r)[2];
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : struct0_T
//
static struct0_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[2]{"Skip", "ColTolDeg"};
    emlrtMsgIdentifier thisId;
    struct0_T y;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 2, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "Skip";
    y.Skip = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"Skip")),
        &thisId);
    thisId.fIdentifier = "ColTolDeg";
    y.ColTolDeg = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"ColTolDeg")),
        &thisId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                char_T ret[9]
// Return Type  : void
//
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[9])
{
    static const int32_T dims[2]{1, 9};
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"char", false, 2U,
                            (void *)&dims[0]);
    emlrtImportCharArrayR2015b((emlrtCTX)sp, src, &ret[0], 9);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 2U> &ret
// Return Type  : void
//
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret)
{
    static const int32_T dims[2]{1, -1};
    int32_T b_iv[2];
    const boolean_T bv[2]{false, true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                              (void *)&dims[0], &bv[0], &b_iv[0]);
    ret.set_size(b_iv[0], b_iv[1]);
    emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret[0], 8, false);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Poff
//                const char_T *identifier
// Return Type  : real_T (*)[3]
//
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Poff,
                                   const char_T *identifier))[3]
{
    emlrtMsgIdentifier thisId;
    real_T(*y)[3];
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = j_emlrt_marshallIn(sp, emlrtAlias(Poff), &thisId);
    emlrtDestroyArray(&Poff);
    return y;
}

//
// Arguments    : const coder::array<real_T, 2U> &u
// Return Type  : const mxArray *
//
static const mxArray *d_emlrt_marshallOut(const coder::array<real_T, 2U> &u)
{
    const mxArray *m;
    const mxArray *y;
    real_T *pData;
    int32_T b_iv[2];
    int32_T i;
    y = nullptr;
    b_iv[0] = u.size(0);
    b_iv[1] = u.size(1);
    m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i{0}; b_i < u.size(1); b_i++) {
        for (int32_T c_i{0}; c_i < u.size(0); c_i++) {
            pData[i] = u[c_i + u.size(0) * b_i];
            i++;
        }
    }
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const real_T u[3]
// Return Type  : const mxArray *
//
static const mxArray *d_emlrt_marshallOut(const real_T u[3])
{
    static const int32_T i{0};
    static const int32_T i1{3};
    const mxArray *m;
    const mxArray *y;
    y = nullptr;
    m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
    emlrtMxSetData((mxArray *)m, (void *)&u[0]);
    emlrtSetDimensions((mxArray *)m, &i1, 1);
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 2U> &ret
// Return Type  : void
//
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret)
{
    static const int32_T dims[2]{-1, -1};
    int32_T b_iv[2];
    const boolean_T bv[2]{true, true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                              (void *)&dims[0], &bv[0], &b_iv[0]);
    ret.set_size(b_iv[0], b_iv[1]);
    emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret[0], 8, false);
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : Fopt
//
static Fopt e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
    static const int32_T dims{0};
    Fopt y;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"Fopt", 8, (const char_T **)&sv[0], &iv[0]);
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, parentId, u, (const char_T *)"Fopt", false, 0U,
                            (void *)&dims);
    y = static_cast<Fopt>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_ZSpdMode
//                const char_T *identifier
// Return Type  : ZSpdMode
//
static ZSpdMode e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_ZSpdMode,
                                   const char_T *identifier)
{
    emlrtMsgIdentifier thisId;
    ZSpdMode y;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = h_emlrt_marshallIn(sp, emlrtAlias(b_ZSpdMode), &thisId);
    emlrtDestroyArray(&b_ZSpdMode);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real_T ret[3]
// Return Type  : void
//
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[3])
{
    static const int32_T dims{3};
    real_T(*r)[3];
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 1U,
                            (void *)&dims);
    r = (real_T(*)[3])emlrtMxGetData(src);
    ret[0] = (*r)[0];
    ret[1] = (*r)[1];
    ret[2] = (*r)[2];
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *cfg
//                const char_T *identifier
//                FeedoptConfig *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg, const char_T *identifier,
                             FeedoptConfig *y)
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(cfg), &thisId, y);
    emlrtDestroyArray(&cfg);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                CurvStruct *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, CurvStruct *y)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[34]{"Type",
                                        "zspdmode",
                                        "TRAFO",
                                        "Poff",
                                        "Aoff",
                                        "Uoff",
                                        "Doff",
                                        "P0",
                                        "P1",
                                        "A0",
                                        "A1",
                                        "U0",
                                        "U1",
                                        "CorrectedHelixCenter",
                                        "delta",
                                        "evec",
                                        "theta",
                                        "pitch",
                                        "CoeffP5",
                                        "sp_index",
                                        "FeedRate",
                                        "SpindleSpeed",
                                        "MaxConstantFeedRate",
                                        "i_begin_sp",
                                        "i_end_sp",
                                        "gcode_source_line",
                                        "index_smooth",
                                        "UseConstJerk",
                                        "ConstJerk",
                                        "ConstJerkMaxIterations",
                                        "Coeff",
                                        "a_param",
                                        "b_param",
                                        "sp"};
    emlrtMsgIdentifier thisId;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 34, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "Type";
    y->Type = g_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"Type")),
        &thisId);
    thisId.fIdentifier = "zspdmode";
    y->zspdmode = h_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"zspdmode")),
        &thisId);
    thisId.fIdentifier = "TRAFO";
    y->TRAFO = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2, (const char_T *)"TRAFO")),
        &thisId);
    thisId.fIdentifier = "Poff";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3, (const char_T *)"Poff")), &thisId,
        y->Poff);
    thisId.fIdentifier = "Aoff";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4, (const char_T *)"Aoff")), &thisId,
        y->Aoff);
    thisId.fIdentifier = "Uoff";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 5, (const char_T *)"Uoff")), &thisId,
        y->Uoff);
    thisId.fIdentifier = "Doff";
    y->Doff = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 6, (const char_T *)"Doff")),
        &thisId);
    thisId.fIdentifier = "P0";
    b_emlrt_marshallIn(sp,
                       emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 7, (const char_T *)"P0")),
                       &thisId, y->P0);
    thisId.fIdentifier = "P1";
    b_emlrt_marshallIn(sp,
                       emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 8, (const char_T *)"P1")),
                       &thisId, y->P1);
    thisId.fIdentifier = "A0";
    b_emlrt_marshallIn(sp,
                       emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 9, (const char_T *)"A0")),
                       &thisId, y->A0);
    thisId.fIdentifier = "A1";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 10, (const char_T *)"A1")), &thisId,
        y->A1);
    thisId.fIdentifier = "U0";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 11, (const char_T *)"U0")), &thisId,
        y->U0);
    thisId.fIdentifier = "U1";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 12, (const char_T *)"U1")), &thisId,
        y->U1);
    thisId.fIdentifier = "CorrectedHelixCenter";
    b_emlrt_marshallIn(sp,
                       emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 13,
                                                      (const char_T *)"CorrectedHelixCenter")),
                       &thisId, y->CorrectedHelixCenter);
    thisId.fIdentifier = "delta";
    y->delta = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 14, (const char_T *)"delta")),
        &thisId);
    thisId.fIdentifier = "evec";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 15, (const char_T *)"evec")),
        &thisId, y->evec);
    thisId.fIdentifier = "theta";
    y->theta = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 16, (const char_T *)"theta")),
        &thisId);
    thisId.fIdentifier = "pitch";
    y->pitch = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 17, (const char_T *)"pitch")),
        &thisId);
    thisId.fIdentifier = "CoeffP5";
    c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 18, (const char_T *)"CoeffP5")),
        &thisId, y->CoeffP5);
    thisId.fIdentifier = "sp_index";
    y->sp_index = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 19, (const char_T *)"sp_index")),
        &thisId);
    thisId.fIdentifier = "FeedRate";
    y->FeedRate = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 20, (const char_T *)"FeedRate")),
        &thisId);
    thisId.fIdentifier = "SpindleSpeed";
    y->SpindleSpeed = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 21, (const char_T *)"SpindleSpeed")),
        &thisId);
    thisId.fIdentifier = "MaxConstantFeedRate";
    y->MaxConstantFeedRate =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 22,
                                                        (const char_T *)"MaxConstantFeedRate")),
                         &thisId);
    thisId.fIdentifier = "i_begin_sp";
    y->i_begin_sp = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 23, (const char_T *)"i_begin_sp")),
        &thisId);
    thisId.fIdentifier = "i_end_sp";
    y->i_end_sp = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 24, (const char_T *)"i_end_sp")),
        &thisId);
    thisId.fIdentifier = "gcode_source_line";
    y->gcode_source_line =
        b_emlrt_marshallIn(sp,
                           emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 25,
                                                          (const char_T *)"gcode_source_line")),
                           &thisId);
    thisId.fIdentifier = "index_smooth";
    y->index_smooth = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 26, (const char_T *)"index_smooth")),
        &thisId);
    thisId.fIdentifier = "UseConstJerk";
    y->UseConstJerk = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 27, (const char_T *)"UseConstJerk")),
        &thisId);
    thisId.fIdentifier = "ConstJerk";
    y->ConstJerk = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 28, (const char_T *)"ConstJerk")),
        &thisId);
    thisId.fIdentifier = "ConstJerkMaxIterations";
    y->ConstJerkMaxIterations =
        b_emlrt_marshallIn(sp,
                           emlrtAlias(emlrtGetFieldR2017b(
                               (emlrtCTX)sp, u, 0, 29, (const char_T *)"ConstJerkMaxIterations")),
                           &thisId);
    thisId.fIdentifier = "Coeff";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 30, (const char_T *)"Coeff")),
        &thisId, y->Coeff);
    thisId.fIdentifier = "a_param";
    y->a_param = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 31, (const char_T *)"a_param")),
        &thisId);
    thisId.fIdentifier = "b_param";
    y->b_param = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 32, (const char_T *)"b_param")),
        &thisId);
    thisId.fIdentifier = "sp";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 33, (const char_T *)"sp")),
                     &thisId, &y->sp);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real_T y[3]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T y[3])
{
    d_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<real_T, 1U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, coder::array<real_T, 1U> &y)
{
    b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *x0
//                const char_T *identifier
// Return Type  : real_T
//
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x0, const char_T *identifier)
{
    emlrtMsgIdentifier thisId;
    real_T y;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = emlrt_marshallIn(sp, emlrtAlias(x0), &thisId);
    emlrtDestroyArray(&x0);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T
//
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
    real_T y;
    y = n_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, coder::array<real_T, 2U> &y)
{
    d_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Bl
//                const char_T *identifier
//                SplineBase *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *Bl, const char_T *identifier,
                             SplineBase *y)
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(Bl), &thisId, y);
    emlrtDestroyArray(&Bl);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                SplineBase *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, SplineBase *y)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[4]{"ncoeff", "breakpoints", "handle", "degree"};
    emlrtMsgIdentifier thisId;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 4, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "ncoeff";
    y->ncoeff = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"ncoeff")),
        &thisId);
    thisId.fIdentifier = "breakpoints";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"breakpoints")),
        &thisId, y->breakpoints);
    thisId.fIdentifier = "handle";
    y->handle = f_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2, (const char_T *)"handle")),
        &thisId);
    thisId.fIdentifier = "degree";
    y->degree = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3, (const char_T *)"degree")),
        &thisId);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                FeedoptConfig *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, FeedoptConfig *y)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[28]{"NDiscr",
                                        "NBreak",
                                        "UseDynamicBreakpoints",
                                        "UseLinearBreakpoints",
                                        "DynamicBreakpointsDistance",
                                        "NHorz",
                                        "vmax",
                                        "amax",
                                        "jmax",
                                        "SplineDegree",
                                        "CutOff",
                                        "LSplit",
                                        "LThreshold",
                                        "CuspThreshold",
                                        "v_0",
                                        "at_0",
                                        "v_1",
                                        "at_1",
                                        "dt",
                                        "ZeroStartAccLimit",
                                        "ZeroStartJerkLimit",
                                        "ZeroStartVelLimit",
                                        "source",
                                        "DebugCutZero",
                                        "Compressing",
                                        "CollTolDeg",
                                        "NGridLengthSpline",
                                        "LogFileName"};
    emlrtMsgIdentifier thisId;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 28, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "NDiscr";
    y->NDiscr = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"NDiscr")),
        &thisId);
    thisId.fIdentifier = "NBreak";
    y->NBreak = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"NBreak")),
        &thisId);
    thisId.fIdentifier = "UseDynamicBreakpoints";
    y->UseDynamicBreakpoints =
        c_emlrt_marshallIn(sp,
                           emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                          (const char_T *)"UseDynamicBreakpoints")),
                           &thisId);
    thisId.fIdentifier = "UseLinearBreakpoints";
    y->UseLinearBreakpoints =
        c_emlrt_marshallIn(sp,
                           emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                          (const char_T *)"UseLinearBreakpoints")),
                           &thisId);
    thisId.fIdentifier = "DynamicBreakpointsDistance";
    y->DynamicBreakpointsDistance =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b(
                             (emlrtCTX)sp, u, 0, 4, (const char_T *)"DynamicBreakpointsDistance")),
                         &thisId);
    thisId.fIdentifier = "NHorz";
    y->NHorz = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 5, (const char_T *)"NHorz")),
        &thisId);
    thisId.fIdentifier = "vmax";
    y->vmax = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 6, (const char_T *)"vmax")),
        &thisId);
    thisId.fIdentifier = "amax";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 7, (const char_T *)"amax")),
                     &thisId, y->amax);
    thisId.fIdentifier = "jmax";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 8, (const char_T *)"jmax")),
                     &thisId, y->jmax);
    thisId.fIdentifier = "SplineDegree";
    y->SplineDegree = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 9, (const char_T *)"SplineDegree")),
        &thisId);
    thisId.fIdentifier = "CutOff";
    y->CutOff = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 10, (const char_T *)"CutOff")),
        &thisId);
    thisId.fIdentifier = "LSplit";
    y->LSplit = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 11, (const char_T *)"LSplit")),
        &thisId);
    thisId.fIdentifier = "LThreshold";
    y->LThreshold = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 12, (const char_T *)"LThreshold")),
        &thisId);
    thisId.fIdentifier = "CuspThreshold";
    y->CuspThreshold = emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 13, (const char_T *)"CuspThreshold")),
        &thisId);
    thisId.fIdentifier = "v_0";
    y->v_0 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 14, (const char_T *)"v_0")),
        &thisId);
    thisId.fIdentifier = "at_0";
    y->at_0 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 15, (const char_T *)"at_0")),
        &thisId);
    thisId.fIdentifier = "v_1";
    y->v_1 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 16, (const char_T *)"v_1")),
        &thisId);
    thisId.fIdentifier = "at_1";
    y->at_1 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 17, (const char_T *)"at_1")),
        &thisId);
    thisId.fIdentifier = "dt";
    y->dt = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 18, (const char_T *)"dt")), &thisId);
    thisId.fIdentifier = "ZeroStartAccLimit";
    y->ZeroStartAccLimit =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 19,
                                                        (const char_T *)"ZeroStartAccLimit")),
                         &thisId);
    thisId.fIdentifier = "ZeroStartJerkLimit";
    y->ZeroStartJerkLimit =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 20,
                                                        (const char_T *)"ZeroStartJerkLimit")),
                         &thisId);
    thisId.fIdentifier = "ZeroStartVelLimit";
    y->ZeroStartVelLimit =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 21,
                                                        (const char_T *)"ZeroStartVelLimit")),
                         &thisId);
    thisId.fIdentifier = "source";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 22, (const char_T *)"source")),
        &thisId, y->source);
    thisId.fIdentifier = "DebugCutZero";
    y->DebugCutZero = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 23, (const char_T *)"DebugCutZero")),
        &thisId);
    thisId.fIdentifier = "Compressing";
    y->Compressing = d_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 24, (const char_T *)"Compressing")),
        &thisId);
    thisId.fIdentifier = "CollTolDeg";
    y->CollTolDeg = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 25, (const char_T *)"CollTolDeg")),
        &thisId);
    thisId.fIdentifier = "NGridLengthSpline";
    y->NGridLengthSpline =
        emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 26,
                                                        (const char_T *)"NGridLengthSpline")),
                         &thisId);
    thisId.fIdentifier = "LogFileName";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 27, (const char_T *)"LogFileName")),
        &thisId, y->LogFileName);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_CurvStruct
//                const char_T *identifier
//                CurvStruct *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_CurvStruct,
                             const char_T *identifier, CurvStruct *y)
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(b_CurvStruct), &thisId, y);
    emlrtDestroyArray(&b_CurvStruct);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                SplineStruct *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, SplineStruct *y)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[5]{"CoeffX", "CoeffY", "CoeffZ", "Bl", "knots"};
    emlrtMsgIdentifier thisId;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 5, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "CoeffX";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"CoeffX")),
        &thisId, y->CoeffX);
    thisId.fIdentifier = "CoeffY";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"CoeffY")),
        &thisId, y->CoeffY);
    thisId.fIdentifier = "CoeffZ";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2, (const char_T *)"CoeffZ")),
        &thisId, y->CoeffZ);
    thisId.fIdentifier = "Bl";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3, (const char_T *)"Bl")),
                     &thisId, &y->Bl);
    thisId.fIdentifier = "knots";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4, (const char_T *)"knots")),
        &thisId, y->knots);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                queue_coder *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, queue_coder *y)
{
    emlrtMsgIdentifier thisId;
    const mxArray *propValues[2];
    propValues[0] = nullptr;
    propValues[1] = nullptr;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, (const char_T *)"queue_coder");
    emlrtGetAllProperties((emlrtCTX)sp, u, 0, 2, (const char_T **)&sv2[0], (const char_T **)&sv3[0],
                          &propValues[0]);
    thisId.fIdentifier = "ptr";
    y->ptr = f_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId);
    thisId.fIdentifier = "value_type";
    emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId, &y->value_type);
    emlrtDestroyArrays(2, &propValues[0]);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                FeedoptContext *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, FeedoptContext *y)
{
    static const int32_T dims{0};
    static const char_T *fieldNames[31]{"op",
                                        "go_next",
                                        "q_gcode",
                                        "q_compress",
                                        "q_splines",
                                        "q_smooth",
                                        "q_split",
                                        "q_opt",
                                        "try_push_again",
                                        "n_optimized",
                                        "reached_end",
                                        "k0",
                                        "v_0",
                                        "v_1",
                                        "at_0",
                                        "at_1",
                                        "cfg",
                                        "Bl",
                                        "u_vec",
                                        "errcode",
                                        "jmax_increase_count",
                                        "zero_start",
                                        "zero_end",
                                        "forced_stop",
                                        "programmed_stop",
                                        "BasisVal",
                                        "BasisValD",
                                        "BasisValDD",
                                        "BasisIntegr",
                                        "Coeff",
                                        "Skipped"};
    emlrtMsgIdentifier thisId;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 31, (const char_T **)&fieldNames[0], 0U,
                           (void *)&dims);
    thisId.fIdentifier = "op";
    y->op = e_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0, (const char_T *)"op")), &thisId);
    thisId.fIdentifier = "go_next";
    y->go_next = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1, (const char_T *)"go_next")),
        &thisId);
    thisId.fIdentifier = "q_gcode";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2, (const char_T *)"q_gcode")),
        &thisId, &y->q_gcode);
    thisId.fIdentifier = "q_compress";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3, (const char_T *)"q_compress")),
        &thisId, &y->q_compress);
    thisId.fIdentifier = "q_splines";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4, (const char_T *)"q_splines")),
        &thisId, &y->q_splines);
    thisId.fIdentifier = "q_smooth";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 5, (const char_T *)"q_smooth")),
        &thisId, &y->q_smooth);
    thisId.fIdentifier = "q_split";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 6, (const char_T *)"q_split")),
        &thisId, &y->q_split);
    thisId.fIdentifier = "q_opt";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 7, (const char_T *)"q_opt")),
        &thisId, &y->q_opt);
    thisId.fIdentifier = "try_push_again";
    y->try_push_again = c_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 8, (const char_T *)"try_push_again")),
        &thisId);
    thisId.fIdentifier = "n_optimized";
    y->n_optimized = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 9, (const char_T *)"n_optimized")),
        &thisId);
    thisId.fIdentifier = "reached_end";
    y->reached_end = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 10, (const char_T *)"reached_end")),
        &thisId);
    thisId.fIdentifier = "k0";
    y->k0 = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 11, (const char_T *)"k0")), &thisId);
    thisId.fIdentifier = "v_0";
    y->v_0 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 12, (const char_T *)"v_0")),
        &thisId);
    thisId.fIdentifier = "v_1";
    y->v_1 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 13, (const char_T *)"v_1")),
        &thisId);
    thisId.fIdentifier = "at_0";
    y->at_0 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 14, (const char_T *)"at_0")),
        &thisId);
    thisId.fIdentifier = "at_1";
    y->at_1 = emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 15, (const char_T *)"at_1")),
        &thisId);
    thisId.fIdentifier = "cfg";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 16, (const char_T *)"cfg")),
                     &thisId, &y->cfg);
    thisId.fIdentifier = "Bl";
    emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 17, (const char_T *)"Bl")),
                     &thisId, &y->Bl);
    thisId.fIdentifier = "u_vec";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 18, (const char_T *)"u_vec")),
        &thisId, y->u_vec);
    thisId.fIdentifier = "errcode";
    y->errcode = i_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 19, (const char_T *)"errcode")),
        &thisId);
    thisId.fIdentifier = "jmax_increase_count";
    y->jmax_increase_count =
        b_emlrt_marshallIn(sp,
                           emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 20,
                                                          (const char_T *)"jmax_increase_count")),
                           &thisId);
    thisId.fIdentifier = "zero_start";
    y->zero_start = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 21, (const char_T *)"zero_start")),
        &thisId);
    thisId.fIdentifier = "zero_end";
    y->zero_end = c_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 22, (const char_T *)"zero_end")),
        &thisId);
    thisId.fIdentifier = "forced_stop";
    y->forced_stop = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 23, (const char_T *)"forced_stop")),
        &thisId);
    thisId.fIdentifier = "programmed_stop";
    y->programmed_stop = b_emlrt_marshallIn(
        sp,
        emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 24, (const char_T *)"programmed_stop")),
        &thisId);
    thisId.fIdentifier = "BasisVal";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 25, (const char_T *)"BasisVal")),
        &thisId, y->BasisVal);
    thisId.fIdentifier = "BasisValD";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 26, (const char_T *)"BasisValD")),
        &thisId, y->BasisValD);
    thisId.fIdentifier = "BasisValDD";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 27, (const char_T *)"BasisValDD")),
        &thisId, y->BasisValDD);
    thisId.fIdentifier = "BasisIntegr";
    emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 28, (const char_T *)"BasisIntegr")),
        &thisId, y->BasisIntegr);
    thisId.fIdentifier = "Coeff";
    b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 29, (const char_T *)"Coeff")),
        &thisId, y->Coeff);
    thisId.fIdentifier = "Skipped";
    y->Skipped = b_emlrt_marshallIn(
        sp, emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 30, (const char_T *)"Skipped")),
        &thisId);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u_vec
//                const char_T *identifier
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_vec, const char_T *identifier,
                             coder::array<real_T, 2U> &y)
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    c_emlrt_marshallIn(sp, emlrtAlias(u_vec), &thisId, y);
    emlrtDestroyArray(&u_vec);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real_T **y_data
//                int32_T y_size[2]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[2])
{
    real_T *r;
    b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, &r, y_size);
    *y_data = r;
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *ctx
//                const char_T *identifier
//                FeedoptContext *y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *ctx, const char_T *identifier,
                             FeedoptContext *y)
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(ctx), &thisId, y);
    emlrtDestroyArray(&ctx);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                char_T y[1024]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, char_T y[1024])
{
    c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *coeffs
//                const char_T *identifier
//                real_T **y_data
//                int32_T y_size[2]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *coeffs, const char_T *identifier,
                             real_T **y_data, int32_T y_size[2])
{
    emlrtMsgIdentifier thisId;
    real_T *r;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(coeffs), &thisId, &r, y_size);
    *y_data = r;
    emlrtDestroyArray(&coeffs);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *filename
//                const char_T *identifier
//                char_T y_data[]
//                int32_T y_size[2]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *filename,
                             const char_T *identifier, char_T y_data[], int32_T y_size[2])
{
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    emlrt_marshallIn(sp, emlrtAlias(filename), &thisId, y_data, y_size);
    emlrtDestroyArray(&filename);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                char_T y_data[]
//                int32_T y_size[2]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, char_T y_data[], int32_T y_size[2])
{
    b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_data, y_size);
    emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const ResampleStateClass u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const ResampleStateClass u)
{
    const mxArray *propValues[3];
    const mxArray *b_y;
    const mxArray *c_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m2;
    const mxArray *m3;
    const mxArray *m4;
    const mxArray *y;
    y = nullptr;
    m = nullptr;
    m1 = nullptr;
    m2 = nullptr;
    emlrtAssign(&y, emlrtCreateClassInstance((const char_T *)"ResampleStateClass"));
    m = nullptr;
    b_y = nullptr;
    m3 = emlrtCreateDoubleScalar(u.u);
    emlrtAssign(&b_y, m3);
    emlrtAssign(&m, b_y);
    propValues[0] = m;
    m1 = nullptr;
    emlrtAssign(&m1, b_emlrt_marshallOut(u.go_next));
    propValues[1] = m1;
    m2 = nullptr;
    c_y = nullptr;
    m4 = emlrtCreateDoubleScalar(u.dt);
    emlrtAssign(&c_y, m4);
    emlrtAssign(&m2, c_y);
    propValues[2] = m2;
    emlrtSetAllProperties((emlrtCTX)sp, &y, 0, 3, (const char_T **)&sv6[0],
                          (const char_T **)&sv7[0], &propValues[0]);
    emlrtAssign(&y, emlrtConvertInstanceToRedirectSource((emlrtCTX)sp, y, 0,
                                                         (const char_T *)"ResampleStateClass"));
    return y;
}

//
// Arguments    : const real_T u[3]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u[3])
{
    static const int32_T b_iv[2]{1, 3};
    const mxArray *m;
    const mxArray *y;
    real_T *pData;
    y = nullptr;
    m = emlrtCreateNumericArray(2, (const void *)&b_iv[0], mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m);
    pData[0] = u[0];
    pData[1] = u[1];
    pData[2] = u[2];
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const FeedoptConfig *u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const FeedoptConfig *u)
{
    static const int32_T b_iv[2]{1, 1024};
    static const int32_T b_iv1[2]{1, 9};
    static const char_T *b_sv[28]{"NDiscr",
                                  "NBreak",
                                  "UseDynamicBreakpoints",
                                  "UseLinearBreakpoints",
                                  "DynamicBreakpointsDistance",
                                  "NHorz",
                                  "vmax",
                                  "amax",
                                  "jmax",
                                  "SplineDegree",
                                  "CutOff",
                                  "LSplit",
                                  "LThreshold",
                                  "CuspThreshold",
                                  "v_0",
                                  "at_0",
                                  "v_1",
                                  "at_1",
                                  "dt",
                                  "ZeroStartAccLimit",
                                  "ZeroStartJerkLimit",
                                  "ZeroStartVelLimit",
                                  "source",
                                  "DebugCutZero",
                                  "Compressing",
                                  "CollTolDeg",
                                  "NGridLengthSpline",
                                  "LogFileName"};
    static const char_T *b_sv1[2]{"Skip", "ColTolDeg"};
    const mxArray *b_y;
    const mxArray *c_y;
    const mxArray *d_y;
    const mxArray *e_y;
    const mxArray *f_y;
    const mxArray *g_y;
    const mxArray *h_y;
    const mxArray *i_y;
    const mxArray *j_y;
    const mxArray *k_y;
    const mxArray *l_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m10;
    const mxArray *m11;
    const mxArray *m12;
    const mxArray *m13;
    const mxArray *m14;
    const mxArray *m15;
    const mxArray *m16;
    const mxArray *m17;
    const mxArray *m18;
    const mxArray *m19;
    const mxArray *m2;
    const mxArray *m20;
    const mxArray *m21;
    const mxArray *m22;
    const mxArray *m3;
    const mxArray *m4;
    const mxArray *m5;
    const mxArray *m6;
    const mxArray *m7;
    const mxArray *m8;
    const mxArray *m9;
    const mxArray *m_y;
    const mxArray *n_y;
    const mxArray *o_y;
    const mxArray *p_y;
    const mxArray *q_y;
    const mxArray *r_y;
    const mxArray *s_y;
    const mxArray *t_y;
    const mxArray *u_y;
    const mxArray *v_y;
    const mxArray *w_y;
    const mxArray *x_y;
    const mxArray *y;
    const mxArray *y_y;
    y = nullptr;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 28, (const char_T **)&b_sv[0]));
    b_y = nullptr;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u->NDiscr;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"NDiscr", b_y, 0);
    c_y = nullptr;
    m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m1) = u->NBreak;
    emlrtAssign(&c_y, m1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"NBreak", c_y, 1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"UseDynamicBreakpoints",
                        b_emlrt_marshallOut(u->UseDynamicBreakpoints), 2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"UseLinearBreakpoints",
                        b_emlrt_marshallOut(u->UseLinearBreakpoints), 3);
    d_y = nullptr;
    m2 = emlrtCreateDoubleScalar(u->DynamicBreakpointsDistance);
    emlrtAssign(&d_y, m2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"DynamicBreakpointsDistance", d_y, 4);
    e_y = nullptr;
    m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m3) = u->NHorz;
    emlrtAssign(&e_y, m3);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"NHorz", e_y, 5);
    f_y = nullptr;
    m4 = emlrtCreateDoubleScalar(u->vmax);
    emlrtAssign(&f_y, m4);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"vmax", f_y, 6);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"amax", emlrt_marshallOut(u->amax), 7);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"jmax", emlrt_marshallOut(u->jmax), 8);
    g_y = nullptr;
    m5 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m5) = u->SplineDegree;
    emlrtAssign(&g_y, m5);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"SplineDegree", g_y, 9);
    h_y = nullptr;
    m6 = emlrtCreateDoubleScalar(u->CutOff);
    emlrtAssign(&h_y, m6);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"CutOff", h_y, 10);
    i_y = nullptr;
    m7 = emlrtCreateDoubleScalar(u->LSplit);
    emlrtAssign(&i_y, m7);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"LSplit", i_y, 11);
    j_y = nullptr;
    m8 = emlrtCreateDoubleScalar(u->LThreshold);
    emlrtAssign(&j_y, m8);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"LThreshold", j_y, 12);
    k_y = nullptr;
    m9 = emlrtCreateDoubleScalar(u->CuspThreshold);
    emlrtAssign(&k_y, m9);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"CuspThreshold", k_y, 13);
    l_y = nullptr;
    m10 = emlrtCreateDoubleScalar(u->v_0);
    emlrtAssign(&l_y, m10);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"v_0", l_y, 14);
    m_y = nullptr;
    m11 = emlrtCreateDoubleScalar(u->at_0);
    emlrtAssign(&m_y, m11);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"at_0", m_y, 15);
    n_y = nullptr;
    m12 = emlrtCreateDoubleScalar(u->v_1);
    emlrtAssign(&n_y, m12);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"v_1", n_y, 16);
    o_y = nullptr;
    m13 = emlrtCreateDoubleScalar(u->at_1);
    emlrtAssign(&o_y, m13);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"at_1", o_y, 17);
    p_y = nullptr;
    m14 = emlrtCreateDoubleScalar(u->dt);
    emlrtAssign(&p_y, m14);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"dt", p_y, 18);
    q_y = nullptr;
    m15 = emlrtCreateDoubleScalar(u->ZeroStartAccLimit);
    emlrtAssign(&q_y, m15);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ZeroStartAccLimit", q_y, 19);
    r_y = nullptr;
    m16 = emlrtCreateDoubleScalar(u->ZeroStartJerkLimit);
    emlrtAssign(&r_y, m16);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ZeroStartJerkLimit", r_y, 20);
    s_y = nullptr;
    m17 = emlrtCreateDoubleScalar(u->ZeroStartVelLimit);
    emlrtAssign(&s_y, m17);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ZeroStartVelLimit", s_y, 21);
    t_y = nullptr;
    m18 = emlrtCreateCharArray(2, &b_iv[0]);
    emlrtInitCharArrayR2013a((emlrtCTX)sp, 1024, m18, &u->source[0]);
    emlrtAssign(&t_y, m18);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"source", t_y, 22);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"DebugCutZero", b_emlrt_marshallOut(u->DebugCutZero),
                        23);
    u_y = nullptr;
    emlrtAssign(&u_y, emlrtCreateStructMatrix(1, 1, 2, (const char_T **)&b_sv1[0]));
    emlrtSetFieldR2017b(u_y, 0, (const char_T *)"Skip", b_emlrt_marshallOut(u->Compressing.Skip),
                        0);
    v_y = nullptr;
    m19 = emlrtCreateDoubleScalar(u->Compressing.ColTolDeg);
    emlrtAssign(&v_y, m19);
    emlrtSetFieldR2017b(u_y, 0, (const char_T *)"ColTolDeg", v_y, 1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Compressing", u_y, 24);
    w_y = nullptr;
    m20 = emlrtCreateDoubleScalar(u->CollTolDeg);
    emlrtAssign(&w_y, m20);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"CollTolDeg", w_y, 25);
    x_y = nullptr;
    m21 = emlrtCreateDoubleScalar(u->NGridLengthSpline);
    emlrtAssign(&x_y, m21);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"NGridLengthSpline", x_y, 26);
    y_y = nullptr;
    m22 = emlrtCreateCharArray(2, &b_iv1[0]);
    emlrtInitCharArrayR2013a((emlrtCTX)sp, 9, m22, &u->LogFileName[0]);
    emlrtAssign(&y_y, m22);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"LogFileName", y_y, 27);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const TransitionResult u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const TransitionResult u)
{
    static const int32_T enumValues[3]{0, 1, 2};
    static const char_T *enumNames[3]{"Ok", "Collinear", "NoSolution"};
    const mxArray *b_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *y;
    y = nullptr;
    m = nullptr;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"TransitionResult", 3,
                         (const char_T **)&enumNames[0], &enumValues[0]);
    b_y = nullptr;
    m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m1) = static_cast<int32_T>(u);
    emlrtAssign(&b_y, m1);
    emlrtAssign(&m, b_y);
    emlrtAssign(&y, emlrtCreateEnumR2012b((emlrtCTX)sp, (const char_T *)"TransitionResult", m));
    emlrtDestroyArray(&m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const CurvStruct *u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const CurvStruct *u)
{
    static const int32_T i{3};
    static const int32_T i1{3};
    static const int32_T i10{3};
    static const int32_T i2{3};
    static const int32_T i3{3};
    static const int32_T i4{3};
    static const int32_T i5{3};
    static const int32_T i6{3};
    static const int32_T i7{3};
    static const int32_T i8{3};
    static const int32_T i9{3};
    static const char_T *b_sv[34]{"Type",
                                  "zspdmode",
                                  "TRAFO",
                                  "Poff",
                                  "Aoff",
                                  "Uoff",
                                  "Doff",
                                  "P0",
                                  "P1",
                                  "A0",
                                  "A1",
                                  "U0",
                                  "U1",
                                  "CorrectedHelixCenter",
                                  "delta",
                                  "evec",
                                  "theta",
                                  "pitch",
                                  "CoeffP5",
                                  "sp_index",
                                  "FeedRate",
                                  "SpindleSpeed",
                                  "MaxConstantFeedRate",
                                  "i_begin_sp",
                                  "i_end_sp",
                                  "gcode_source_line",
                                  "index_smooth",
                                  "UseConstJerk",
                                  "ConstJerk",
                                  "ConstJerkMaxIterations",
                                  "Coeff",
                                  "a_param",
                                  "b_param",
                                  "sp"};
    static const char_T *b_sv1[5]{"CoeffX", "CoeffY", "CoeffZ", "Bl", "knots"};
    const mxArray *ab_y;
    const mxArray *b_y;
    const mxArray *bb_y;
    const mxArray *c_y;
    const mxArray *cb_y;
    const mxArray *d_y;
    const mxArray *db_y;
    const mxArray *e_y;
    const mxArray *eb_y;
    const mxArray *f_y;
    const mxArray *fb_y;
    const mxArray *g_y;
    const mxArray *gb_y;
    const mxArray *h_y;
    const mxArray *hb_y;
    const mxArray *i_y;
    const mxArray *j_y;
    const mxArray *k_y;
    const mxArray *l_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m10;
    const mxArray *m11;
    const mxArray *m12;
    const mxArray *m13;
    const mxArray *m14;
    const mxArray *m15;
    const mxArray *m16;
    const mxArray *m17;
    const mxArray *m18;
    const mxArray *m19;
    const mxArray *m2;
    const mxArray *m20;
    const mxArray *m21;
    const mxArray *m22;
    const mxArray *m23;
    const mxArray *m24;
    const mxArray *m25;
    const mxArray *m26;
    const mxArray *m27;
    const mxArray *m28;
    const mxArray *m29;
    const mxArray *m3;
    const mxArray *m30;
    const mxArray *m4;
    const mxArray *m5;
    const mxArray *m6;
    const mxArray *m7;
    const mxArray *m8;
    const mxArray *m9;
    const mxArray *m_y;
    const mxArray *n_y;
    const mxArray *o_y;
    const mxArray *p_y;
    const mxArray *q_y;
    const mxArray *r_y;
    const mxArray *s_y;
    const mxArray *t_y;
    const mxArray *u_y;
    const mxArray *v_y;
    const mxArray *w_y;
    const mxArray *x_y;
    const mxArray *y;
    const mxArray *y_y;
    real_T *b_pData;
    real_T *c_pData;
    real_T *d_pData;
    real_T *e_pData;
    real_T *f_pData;
    real_T *g_pData;
    real_T *h_pData;
    real_T *i_pData;
    real_T *j_pData;
    real_T *k_pData;
    real_T *pData;
    y = nullptr;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 34, (const char_T **)&b_sv[0]));
    b_y = nullptr;
    m = nullptr;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"CurveType", 5, (const char_T **)&sv4[0],
                         &iv2[0]);
    c_y = nullptr;
    m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m1) = static_cast<int32_T>(u->Type);
    emlrtAssign(&c_y, m1);
    emlrtAssign(&m, c_y);
    emlrtAssign(&b_y, emlrtCreateEnumR2012b((emlrtCTX)sp, (const char_T *)"CurveType", m));
    emlrtDestroyArray(&m);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Type", b_y, 0);
    d_y = nullptr;
    m2 = nullptr;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"ZSpdMode", 4, (const char_T **)&sv5[0],
                         &iv1[0]);
    e_y = nullptr;
    m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m3) = static_cast<int32_T>(u->zspdmode);
    emlrtAssign(&e_y, m3);
    emlrtAssign(&m2, e_y);
    emlrtAssign(&d_y, emlrtCreateEnumR2012b((emlrtCTX)sp, (const char_T *)"ZSpdMode", m2));
    emlrtDestroyArray(&m2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"zspdmode", d_y, 1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"TRAFO", b_emlrt_marshallOut(u->TRAFO), 2);
    f_y = nullptr;
    m4 = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m4);
    pData[0] = u->Poff[0];
    pData[1] = u->Poff[1];
    pData[2] = u->Poff[2];
    emlrtAssign(&f_y, m4);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Poff", f_y, 3);
    g_y = nullptr;
    m5 = emlrtCreateNumericArray(1, (const void *)&i1, mxDOUBLE_CLASS, mxREAL);
    b_pData = emlrtMxGetPr(m5);
    b_pData[0] = u->Aoff[0];
    b_pData[1] = u->Aoff[1];
    b_pData[2] = u->Aoff[2];
    emlrtAssign(&g_y, m5);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Aoff", g_y, 4);
    h_y = nullptr;
    m6 = emlrtCreateNumericArray(1, (const void *)&i2, mxDOUBLE_CLASS, mxREAL);
    c_pData = emlrtMxGetPr(m6);
    c_pData[0] = u->Uoff[0];
    c_pData[1] = u->Uoff[1];
    c_pData[2] = u->Uoff[2];
    emlrtAssign(&h_y, m6);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Uoff", h_y, 5);
    i_y = nullptr;
    m7 = emlrtCreateDoubleScalar(u->Doff);
    emlrtAssign(&i_y, m7);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Doff", i_y, 6);
    j_y = nullptr;
    m8 = emlrtCreateNumericArray(1, (const void *)&i3, mxDOUBLE_CLASS, mxREAL);
    d_pData = emlrtMxGetPr(m8);
    d_pData[0] = u->P0[0];
    d_pData[1] = u->P0[1];
    d_pData[2] = u->P0[2];
    emlrtAssign(&j_y, m8);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"P0", j_y, 7);
    k_y = nullptr;
    m9 = emlrtCreateNumericArray(1, (const void *)&i4, mxDOUBLE_CLASS, mxREAL);
    e_pData = emlrtMxGetPr(m9);
    e_pData[0] = u->P1[0];
    e_pData[1] = u->P1[1];
    e_pData[2] = u->P1[2];
    emlrtAssign(&k_y, m9);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"P1", k_y, 8);
    l_y = nullptr;
    m10 = emlrtCreateNumericArray(1, (const void *)&i5, mxDOUBLE_CLASS, mxREAL);
    f_pData = emlrtMxGetPr(m10);
    f_pData[0] = u->A0[0];
    f_pData[1] = u->A0[1];
    f_pData[2] = u->A0[2];
    emlrtAssign(&l_y, m10);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"A0", l_y, 9);
    m_y = nullptr;
    m11 = emlrtCreateNumericArray(1, (const void *)&i6, mxDOUBLE_CLASS, mxREAL);
    g_pData = emlrtMxGetPr(m11);
    g_pData[0] = u->A1[0];
    g_pData[1] = u->A1[1];
    g_pData[2] = u->A1[2];
    emlrtAssign(&m_y, m11);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"A1", m_y, 10);
    n_y = nullptr;
    m12 = emlrtCreateNumericArray(1, (const void *)&i7, mxDOUBLE_CLASS, mxREAL);
    h_pData = emlrtMxGetPr(m12);
    h_pData[0] = u->U0[0];
    h_pData[1] = u->U0[1];
    h_pData[2] = u->U0[2];
    emlrtAssign(&n_y, m12);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"U0", n_y, 11);
    o_y = nullptr;
    m13 = emlrtCreateNumericArray(1, (const void *)&i8, mxDOUBLE_CLASS, mxREAL);
    i_pData = emlrtMxGetPr(m13);
    i_pData[0] = u->U1[0];
    i_pData[1] = u->U1[1];
    i_pData[2] = u->U1[2];
    emlrtAssign(&o_y, m13);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"U1", o_y, 12);
    p_y = nullptr;
    m14 = emlrtCreateNumericArray(1, (const void *)&i9, mxDOUBLE_CLASS, mxREAL);
    j_pData = emlrtMxGetPr(m14);
    j_pData[0] = u->CorrectedHelixCenter[0];
    j_pData[1] = u->CorrectedHelixCenter[1];
    j_pData[2] = u->CorrectedHelixCenter[2];
    emlrtAssign(&p_y, m14);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"CorrectedHelixCenter", p_y, 13);
    q_y = nullptr;
    m15 = emlrtCreateDoubleScalar(u->delta);
    emlrtAssign(&q_y, m15);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"delta", q_y, 14);
    r_y = nullptr;
    m16 = emlrtCreateNumericArray(1, (const void *)&i10, mxDOUBLE_CLASS, mxREAL);
    k_pData = emlrtMxGetPr(m16);
    k_pData[0] = u->evec[0];
    k_pData[1] = u->evec[1];
    k_pData[2] = u->evec[2];
    emlrtAssign(&r_y, m16);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"evec", r_y, 15);
    s_y = nullptr;
    m17 = emlrtCreateDoubleScalar(u->theta);
    emlrtAssign(&s_y, m17);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"theta", s_y, 16);
    t_y = nullptr;
    m18 = emlrtCreateDoubleScalar(u->pitch);
    emlrtAssign(&t_y, m18);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"pitch", t_y, 17);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"CoeffP5", c_emlrt_marshallOut(u->CoeffP5), 18);
    u_y = nullptr;
    m19 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m19) = u->sp_index;
    emlrtAssign(&u_y, m19);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"sp_index", u_y, 19);
    v_y = nullptr;
    m20 = emlrtCreateDoubleScalar(u->FeedRate);
    emlrtAssign(&v_y, m20);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"FeedRate", v_y, 20);
    w_y = nullptr;
    m21 = emlrtCreateDoubleScalar(u->SpindleSpeed);
    emlrtAssign(&w_y, m21);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"SpindleSpeed", w_y, 21);
    x_y = nullptr;
    m22 = emlrtCreateDoubleScalar(u->MaxConstantFeedRate);
    emlrtAssign(&x_y, m22);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"MaxConstantFeedRate", x_y, 22);
    y_y = nullptr;
    m23 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m23) = u->i_begin_sp;
    emlrtAssign(&y_y, m23);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"i_begin_sp", y_y, 23);
    ab_y = nullptr;
    m24 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m24) = u->i_end_sp;
    emlrtAssign(&ab_y, m24);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"i_end_sp", ab_y, 24);
    bb_y = nullptr;
    m25 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m25) = u->gcode_source_line;
    emlrtAssign(&bb_y, m25);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"gcode_source_line", bb_y, 25);
    cb_y = nullptr;
    m26 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m26) = u->index_smooth;
    emlrtAssign(&cb_y, m26);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"index_smooth", cb_y, 26);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"UseConstJerk", b_emlrt_marshallOut(u->UseConstJerk),
                        27);
    db_y = nullptr;
    m27 = emlrtCreateDoubleScalar(u->ConstJerk);
    emlrtAssign(&db_y, m27);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ConstJerk", db_y, 28);
    eb_y = nullptr;
    m28 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m28) = u->ConstJerkMaxIterations;
    emlrtAssign(&eb_y, m28);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ConstJerkMaxIterations", eb_y, 29);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Coeff", emlrt_marshallOut(u->Coeff), 30);
    fb_y = nullptr;
    m29 = emlrtCreateDoubleScalar(u->a_param);
    emlrtAssign(&fb_y, m29);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"a_param", fb_y, 31);
    gb_y = nullptr;
    m30 = emlrtCreateDoubleScalar(u->b_param);
    emlrtAssign(&gb_y, m30);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"b_param", gb_y, 32);
    hb_y = nullptr;
    emlrtAssign(&hb_y, emlrtCreateStructMatrix(1, 1, 5, (const char_T **)&b_sv1[0]));
    emlrtSetFieldR2017b(hb_y, 0, (const char_T *)"CoeffX", c_emlrt_marshallOut(u->sp.CoeffX), 0);
    emlrtSetFieldR2017b(hb_y, 0, (const char_T *)"CoeffY", c_emlrt_marshallOut(u->sp.CoeffY), 1);
    emlrtSetFieldR2017b(hb_y, 0, (const char_T *)"CoeffZ", c_emlrt_marshallOut(u->sp.CoeffZ), 2);
    emlrtSetFieldR2017b(hb_y, 0, (const char_T *)"Bl", emlrt_marshallOut(&u->sp.Bl), 3);
    emlrtSetFieldR2017b(hb_y, 0, (const char_T *)"knots", c_emlrt_marshallOut(u->sp.knots), 4);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"sp", hb_y, 33);
    return y;
}

//
// Arguments    : const coder::array<real_T, 1U> &u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const coder::array<real_T, 1U> &u)
{
    const mxArray *m;
    const mxArray *y;
    real_T *pData;
    int32_T i;
    y = nullptr;
    m = emlrtCreateNumericArray(1, ((coder::array<real_T, 1U> *)&u)->size(), mxDOUBLE_CLASS,
                                mxREAL);
    pData = emlrtMxGetPr(m);
    i = 0;
    for (int32_T b_i{0}; b_i < u.size(0); b_i++) {
        pData[i] = u[b_i];
        i++;
    }
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const SplineBase *u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const SplineBase *u)
{
    static const char_T *b_sv[4]{"ncoeff", "breakpoints", "handle", "degree"};
    const mxArray *b_y;
    const mxArray *c_y;
    const mxArray *d_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m2;
    const mxArray *y;
    y = nullptr;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 4, (const char_T **)&b_sv[0]));
    b_y = nullptr;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u->ncoeff;
    emlrtAssign(&b_y, m);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"ncoeff", b_y, 0);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"breakpoints", c_emlrt_marshallOut(u->breakpoints),
                        1);
    c_y = nullptr;
    m1 = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *(uint64_T *)emlrtMxGetData(m1) = u->handle;
    emlrtAssign(&c_y, m1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"handle", c_y, 2);
    d_y = nullptr;
    m2 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m2) = u->degree;
    emlrtAssign(&d_y, m2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"degree", d_y, 3);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const creal_T u_data[]
//                const int32_T u_size
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const creal_T u_data[],
                                        const int32_T u_size)
{
    const mxArray *m;
    const mxArray *y;
    y = nullptr;
    m = emlrtCreateNumericArray(1, (const void *)&u_size, mxDOUBLE_CLASS, mxCOMPLEX);
    emlrtExportNumericArrayR2013b((emlrtCTX)sp, m, (void *)&u_data[0], 8);
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const FeedoptContext *u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const FeedoptContext *u)
{
    static const char_T *b_sv[31]{"op",
                                  "go_next",
                                  "q_gcode",
                                  "q_compress",
                                  "q_splines",
                                  "q_smooth",
                                  "q_split",
                                  "q_opt",
                                  "try_push_again",
                                  "n_optimized",
                                  "reached_end",
                                  "k0",
                                  "v_0",
                                  "v_1",
                                  "at_0",
                                  "at_1",
                                  "cfg",
                                  "Bl",
                                  "u_vec",
                                  "errcode",
                                  "jmax_increase_count",
                                  "zero_start",
                                  "zero_end",
                                  "forced_stop",
                                  "programmed_stop",
                                  "BasisVal",
                                  "BasisValD",
                                  "BasisValDD",
                                  "BasisIntegr",
                                  "Coeff",
                                  "Skipped"};
    const coder::array<real_T, 1U> *b_u;
    const mxArray *b_y;
    const mxArray *c_y;
    const mxArray *d_y;
    const mxArray *e_y;
    const mxArray *f_y;
    const mxArray *g_y;
    const mxArray *h_y;
    const mxArray *i_y;
    const mxArray *j_y;
    const mxArray *k_y;
    const mxArray *l_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m10;
    const mxArray *m11;
    const mxArray *m12;
    const mxArray *m13;
    const mxArray *m14;
    const mxArray *m2;
    const mxArray *m3;
    const mxArray *m4;
    const mxArray *m5;
    const mxArray *m6;
    const mxArray *m7;
    const mxArray *m8;
    const mxArray *m9;
    const mxArray *m_y;
    const mxArray *n_y;
    const mxArray *o_y;
    const mxArray *p_y;
    const mxArray *y;
    real_T *pData;
    int32_T i;
    y = nullptr;
    emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 31, (const char_T **)&b_sv[0]));
    b_y = nullptr;
    m = nullptr;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"Fopt", 8, (const char_T **)&sv[0], &iv[0]);
    c_y = nullptr;
    m1 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m1) = static_cast<int32_T>(u->op);
    emlrtAssign(&c_y, m1);
    emlrtAssign(&m, c_y);
    emlrtAssign(&b_y, emlrtCreateEnumR2012b((emlrtCTX)sp, (const char_T *)"Fopt", m));
    emlrtDestroyArray(&m);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"op", b_y, 0);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"go_next", b_emlrt_marshallOut(u->go_next), 1);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_gcode", emlrt_marshallOut(sp, &u->q_gcode), 2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_compress", emlrt_marshallOut(sp, &u->q_compress),
                        3);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_splines", emlrt_marshallOut(sp, &u->q_splines), 4);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_smooth", emlrt_marshallOut(sp, &u->q_smooth), 5);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_split", emlrt_marshallOut(sp, &u->q_split), 6);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"q_opt", emlrt_marshallOut(sp, &u->q_opt), 7);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"try_push_again",
                        b_emlrt_marshallOut(u->try_push_again), 8);
    d_y = nullptr;
    m2 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m2) = u->n_optimized;
    emlrtAssign(&d_y, m2);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"n_optimized", d_y, 9);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"reached_end", b_emlrt_marshallOut(u->reached_end),
                        10);
    e_y = nullptr;
    m3 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m3) = u->k0;
    emlrtAssign(&e_y, m3);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"k0", e_y, 11);
    f_y = nullptr;
    m4 = emlrtCreateDoubleScalar(u->v_0);
    emlrtAssign(&f_y, m4);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"v_0", f_y, 12);
    g_y = nullptr;
    m5 = emlrtCreateDoubleScalar(u->v_1);
    emlrtAssign(&g_y, m5);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"v_1", g_y, 13);
    h_y = nullptr;
    m6 = emlrtCreateDoubleScalar(u->at_0);
    emlrtAssign(&h_y, m6);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"at_0", h_y, 14);
    i_y = nullptr;
    m7 = emlrtCreateDoubleScalar(u->at_1);
    emlrtAssign(&i_y, m7);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"at_1", i_y, 15);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"cfg", emlrt_marshallOut(sp, &u->cfg), 16);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Bl", emlrt_marshallOut(&u->Bl), 17);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"u_vec", c_emlrt_marshallOut(u->u_vec), 18);
    j_y = nullptr;
    m8 = nullptr;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"FeedoptPlanError", 4,
                         (const char_T **)&sv1[0], &iv1[0]);
    k_y = nullptr;
    m9 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m9) = static_cast<int32_T>(u->errcode);
    emlrtAssign(&k_y, m9);
    emlrtAssign(&m8, k_y);
    emlrtAssign(&j_y, emlrtCreateEnumR2012b((emlrtCTX)sp, (const char_T *)"FeedoptPlanError", m8));
    emlrtDestroyArray(&m8);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"errcode", j_y, 19);
    l_y = nullptr;
    m10 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m10) = u->jmax_increase_count;
    emlrtAssign(&l_y, m10);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"jmax_increase_count", l_y, 20);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"zero_start", b_emlrt_marshallOut(u->zero_start), 21);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"zero_end", b_emlrt_marshallOut(u->zero_end), 22);
    m_y = nullptr;
    m11 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m11) = u->forced_stop;
    emlrtAssign(&m_y, m11);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"forced_stop", m_y, 23);
    n_y = nullptr;
    m12 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m12) = u->programmed_stop;
    emlrtAssign(&n_y, m12);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"programmed_stop", n_y, 24);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"BasisVal", d_emlrt_marshallOut(u->BasisVal), 25);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"BasisValD", d_emlrt_marshallOut(u->BasisValD), 26);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"BasisValDD", d_emlrt_marshallOut(u->BasisValDD), 27);
    b_u = &u->BasisIntegr;
    o_y = nullptr;
    m13 = emlrtCreateNumericArray(1, ((coder::array<real_T, 1U> *)&u->BasisIntegr)->size(),
                                  mxDOUBLE_CLASS, mxREAL);
    pData = emlrtMxGetPr(m13);
    i = 0;
    for (int32_T b_i{0}; b_i < b_u->size(0); b_i++) {
        pData[i] = (*b_u)[b_i];
        i++;
    }
    emlrtAssign(&o_y, m13);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"BasisIntegr", o_y, 28);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Coeff", d_emlrt_marshallOut(u->Coeff), 29);
    p_y = nullptr;
    m14 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m14) = u->Skipped;
    emlrtAssign(&p_y, m14);
    emlrtSetFieldR2017b(y, 0, (const char_T *)"Skipped", p_y, 30);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const queue_coder *u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const queue_coder *u)
{
    const mxArray *propValues[2];
    const mxArray *b_y;
    const mxArray *m;
    const mxArray *m1;
    const mxArray *m2;
    const mxArray *y;
    y = nullptr;
    m = nullptr;
    m1 = nullptr;
    emlrtAssign(&y, emlrtCreateClassInstance((const char_T *)"queue_coder"));
    m = nullptr;
    b_y = nullptr;
    m2 = emlrtCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *(uint64_T *)emlrtMxGetData(m2) = u->ptr;
    emlrtAssign(&b_y, m2);
    emlrtAssign(&m, b_y);
    propValues[0] = m;
    m1 = nullptr;
    emlrtAssign(&m1, emlrt_marshallOut(sp, &u->value_type));
    propValues[1] = m1;
    emlrtSetAllProperties((emlrtCTX)sp, &y, 0, 2, (const char_T **)&sv2[0],
                          (const char_T **)&sv3[0], &propValues[0]);
    emlrtAssign(&y, emlrtConvertInstanceToRedirectSource((emlrtCTX)sp, y, 0,
                                                         (const char_T *)"queue_coder"));
    return y;
}

//
// Arguments    : const coder::array<real_T, 2U> &u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u)
{
    static const int32_T b_iv[2]{0, 0};
    const mxArray *m;
    const mxArray *y;
    y = nullptr;
    m = emlrtCreateNumericArray(2, (const void *)&b_iv[0], mxDOUBLE_CLASS, mxREAL);
    emlrtMxSetData((mxArray *)m, &(((coder::array<real_T, 2U> *)&u)->data())[0]);
    emlrtSetDimensions((mxArray *)m, ((coder::array<real_T, 2U> *)&u)->size(), 2);
    emlrtAssign(&y, m);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *breakpoints
//                const char_T *identifier
// Return Type  : real_T (*)[10]
//
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *breakpoints,
                                   const char_T *identifier))[10]
{
    emlrtMsgIdentifier thisId;
    real_T(*y)[10];
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = k_emlrt_marshallIn(sp, emlrtAlias(breakpoints), &thisId);
    emlrtDestroyArray(&breakpoints);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 2U> &ret
// Return Type  : void
//
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, coder::array<real_T, 2U> &ret)
{
    static const int32_T dims[2]{1, -1};
    int32_T b_iv[2];
    const boolean_T bv[2]{false, true};
    emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                              (void *)&dims[0], &bv[0], &b_iv[0]);
    ret.prealloc(b_iv[0] * b_iv[1]);
    ret.set_size(b_iv[0], b_iv[1]);
    ret.set((real_T *)emlrtMxGetData(src), ret.size(0), ret.size(1));
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : uint64_T
//
static uint64_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
    uint64_T y;
    y = q_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real_T ret[6][3]
// Return Type  : void
//
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[6][3])
{
    static const int32_T dims[2]{3, 6};
    real_T(*r)[6][3];
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                            (void *)&dims[0]);
    r = (real_T(*)[6][3])emlrtMxGetData(src);
    for (int32_T i{0}; i < 6; i++) {
        ret[i][0] = (*r)[i][0];
        ret[i][1] = (*r)[i][1];
        ret[i][2] = (*r)[i][2];
    }
    emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : CurveType
//
static CurveType g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                    const emlrtMsgIdentifier *parentId)
{
    static const int32_T dims{0};
    CurveType y;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"CurveType", 5, (const char_T **)&sv4[0],
                         &iv2[0]);
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, parentId, u, (const char_T *)"CurveType", false, 0U,
                            (void *)&dims);
    y = static_cast<CurveType>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *state
//                const char_T *identifier
// Return Type  : ResampleStateClass
//
static ResampleStateClass g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *state,
                                             const char_T *identifier)
{
    ResampleStateClass y;
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = l_emlrt_marshallIn(sp, emlrtAlias(state), &thisId);
    emlrtDestroyArray(&state);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *cfg
//                const char_T *identifier
// Return Type  : DebugCfg
//
static DebugCfg h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cfg,
                                   const char_T *identifier)
{
    emlrtMsgIdentifier thisId;
    DebugCfg y;
    thisId.fIdentifier = const_cast<const char_T *>(identifier);
    thisId.fParent = nullptr;
    thisId.bParentIsCell = false;
    y = m_emlrt_marshallIn(sp, emlrtAlias(cfg), &thisId);
    emlrtDestroyArray(&cfg);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : ZSpdMode
//
static ZSpdMode h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
    static const int32_T dims{0};
    ZSpdMode y;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"ZSpdMode", 4, (const char_T **)&sv5[0],
                         &iv1[0]);
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, parentId, u, (const char_T *)"ZSpdMode", false, 0U,
                            (void *)&dims);
    y = static_cast<ZSpdMode>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : FeedoptPlanError
//
static FeedoptPlanError i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                           const emlrtMsgIdentifier *parentId)
{
    static const int32_T dims{0};
    FeedoptPlanError y;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"FeedoptPlanError", 4,
                         (const char_T **)&sv1[0], &iv1[0]);
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, parentId, u, (const char_T *)"FeedoptPlanError", false,
                            0U, (void *)&dims);
    y = static_cast<FeedoptPlanError>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[3]
//
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3]
{
    real_T(*y)[3];
    y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[10]
//
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10]
{
    real_T(*y)[10];
    y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : ResampleStateClass
//
static ResampleStateClass l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                             const emlrtMsgIdentifier *parentId)
{
    ResampleStateClass y;
    emlrtMsgIdentifier thisId;
    const mxArray *propValues[3];
    propValues[0] = nullptr;
    propValues[1] = nullptr;
    propValues[2] = nullptr;
    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, (const char_T *)"ResampleStateClass");
    emlrtGetAllProperties((emlrtCTX)sp, u, 0, 3, (const char_T **)&sv6[0], (const char_T **)&sv7[0],
                          &propValues[0]);
    thisId.fIdentifier = "u";
    y.u = emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId);
    thisId.fIdentifier = "go_next";
    y.go_next = c_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId);
    thisId.fIdentifier = "dt";
    y.dt = emlrt_marshallIn(sp, emlrtAlias(propValues[2]), &thisId);
    emlrtDestroyArrays(3, &propValues[0]);
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : DebugCfg
//
static DebugCfg m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
    static const int32_T enumValues[8]{1, 2, 3, 4, 5, 6, 7, 8};
    static const int32_T dims{0};
    static const char_T *enumNames[8]{"Transitions", "OptimProgress", "FeedratePlanning",
                                      "Global",      "Warning",       "Error",
                                      "Plots",       "Validate"};
    DebugCfg y;
    emlrtCheckEnumR2012b((emlrtCTX)sp, (const char_T *)"DebugCfg", 8,
                         (const char_T **)&enumNames[0], &enumValues[0]);
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, parentId, u, (const char_T *)"DebugCfg", false, 0U,
                            (void *)&dims);
    y = static_cast<DebugCfg>(emlrtGetEnumElementR2009a(u, 0));
    emlrtDestroyArray(&u);
    return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T
//
static real_T n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
    static const int32_T dims{0};
    real_T ret;
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 0U,
                            (void *)&dims);
    ret = *(real_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : int32_T
//
static int32_T o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId)
{
    static const int32_T dims{0};
    int32_T ret;
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"int32", false, 0U,
                            (void *)&dims);
    ret = *(int32_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : boolean_T
//
static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId)
{
    static const int32_T dims{0};
    boolean_T ret;
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"logical", false, 0U,
                            (void *)&dims);
    ret = *emlrtMxGetLogicals(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : uint64_T
//
static uint64_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
    static const int32_T dims{0};
    uint64_T ret;
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"uint64", false, 0U,
                            (void *)&dims);
    ret = *(uint64_T *)emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[3]
//
static real_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
    static const int32_T dims{3};
    real_T(*ret)[3];
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 1U,
                            (void *)&dims);
    ret = (real_T(*)[3])emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[10]
//
static real_T (*s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10]
{
    static const int32_T dims[2]{1, 10};
    real_T(*ret)[10];
    emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double", false, 2U,
                            (void *)&dims[0]);
    ret = (real_T(*)[10])emlrtMxGetData(src);
    emlrtDestroyArray(&src);
    return ret;
}

//
// Arguments    : const mxArray * const prhs[3]
//                int32_T nlhs
//                const mxArray *plhs[4]
// Return Type  : void
//
void CalcTransition_api(const mxArray *const prhs[3], int32_T nlhs, const mxArray *plhs[4])
{
    CurvStruct CurvStruct1;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct_T;
    FeedoptContext ctx;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    TransitionResult status;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ctx", &ctx);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "CurvStruct1", &CurvStruct1);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "CurvStruct2", &CurvStruct2);
    // Invoke the target function
    CalcTransition(&ctx, &CurvStruct1, &CurvStruct2, &CurvStruct1_C, &CurvStruct_T, &CurvStruct2_C,
                   &status);
    // Marshall function outputs
    plhs[0] = emlrt_marshallOut(&st, &CurvStruct1_C);
    if (nlhs > 1) {
        plhs[1] = emlrt_marshallOut(&st, &CurvStruct_T);
    }
    if (nlhs > 2) {
        plhs[2] = emlrt_marshallOut(&st, &CurvStruct2_C);
    }
    if (nlhs > 3) {
        plhs[3] = emlrt_marshallOut(&st, status);
    }
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[2]
//                const mxArray **plhs
// Return Type  : void
//
void ConfigSetSource_api(const mxArray *const prhs[2], const mxArray **plhs)
{
    FeedoptConfig cfg;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    int32_T filename_size[2];
    char_T filename_data[1024];
    st.tls = emlrtRootTLSGlobal;
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "cfg", &cfg);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "filename", filename_data, filename_size);
    // Invoke the target function
    ConfigSetSource(&cfg, filename_data, filename_size);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &cfg);
}

//
// Arguments    : const mxArray **plhs
// Return Type  : void
//
void ConstrCurvStructType_api(const mxArray **plhs)
{
    CurvStruct C;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Invoke the target function
    ConstrCurvStructType(&C);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &C);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[20]
//                const mxArray **plhs
// Return Type  : void
//
void ConstrHelixStructFromArcFeed_api(const mxArray *const prhs[20], const mxArray **plhs)
{
    CurvStruct b_CurvStruct;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T(*A0)[3];
    real_T(*A1)[3];
    real_T(*Aoff)[3];
    real_T(*Poff)[3];
    real_T(*U0)[3];
    real_T(*U1)[3];
    real_T(*Uoff)[3];
    real_T(*evec)[3];
    real_T Doff;
    real_T cx;
    real_T cy;
    real_T cz;
    real_T p0x;
    real_T p0y;
    real_T p0z;
    real_T p1x;
    real_T p1y;
    real_T p1z;
    real_T rotation;
    boolean_T trafo;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    trafo = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "trafo");
    Poff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "Poff");
    Aoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "Aoff");
    Uoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "Uoff");
    Doff = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "Doff");
    p0x = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "p0x");
    p0y = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "p0y");
    p0z = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "p0z");
    p1x = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "p1x");
    p1y = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "p1y");
    p1z = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "p1z");
    cx = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "cx");
    cy = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "cy");
    cz = emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "cz");
    A0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[14]), "A0");
    A1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[15]), "A1");
    U0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[16]), "U0");
    U1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[17]), "U1");
    rotation = emlrt_marshallIn(&st, emlrtAliasP(prhs[18]), "rotation");
    evec = d_emlrt_marshallIn(&st, emlrtAlias(prhs[19]), "evec");
    // Invoke the target function
    ConstrHelixStructFromArcFeed(trafo, *Poff, *Aoff, *Uoff, Doff, p0x, p0y, p0z, p1x, p1y, p1z, cx,
                                 cy, cz, *A0, *A1, *U0, *U1, rotation, *evec, &b_CurvStruct);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[18]
//                const mxArray **plhs
// Return Type  : void
//
void ConstrHelixStruct_api(const mxArray *const prhs[18], const mxArray **plhs)
{
    CurvStruct b_CurvStruct;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T(*A0)[3];
    real_T(*A1)[3];
    real_T(*Aoff)[3];
    real_T(*Cprim)[3];
    real_T(*P0)[3];
    real_T(*P1)[3];
    real_T(*Poff)[3];
    real_T(*U0)[3];
    real_T(*U1)[3];
    real_T(*Uoff)[3];
    real_T(*evec)[3];
    real_T Doff;
    real_T FeedRate;
    real_T delta;
    real_T pitch;
    real_T theta;
    boolean_T trafo;
    ZSpdMode mode;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    trafo = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "trafo");
    Poff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "Poff");
    Aoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "Aoff");
    Uoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "Uoff");
    Doff = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "Doff");
    P0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "P0");
    P1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "P1");
    A0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "A0");
    A1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "A1");
    U0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "U0");
    U1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "U1");
    Cprim = d_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "Cprim");
    delta = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "delta");
    evec = d_emlrt_marshallIn(&st, emlrtAlias(prhs[13]), "evec");
    theta = emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "theta");
    pitch = emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "pitch");
    FeedRate = emlrt_marshallIn(&st, emlrtAliasP(prhs[16]), "FeedRate");
    mode = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[17]), "mode");
    // Invoke the target function
    ConstrHelixStruct(trafo, *Poff, *Aoff, *Uoff, Doff, *P0, *P1, *A0, *A1, *U0, *U1, *Cprim, delta,
                      *evec, theta, pitch, FeedRate, mode, &b_CurvStruct);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[13]
//                const mxArray **plhs
// Return Type  : void
//
void ConstrLineStruct_api(const mxArray *const prhs[13], const mxArray **plhs)
{
    CurvStruct b_CurvStruct;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T(*A0)[3];
    real_T(*A1)[3];
    real_T(*Aoff)[3];
    real_T(*P0)[3];
    real_T(*P1)[3];
    real_T(*Poff)[3];
    real_T(*U0)[3];
    real_T(*U1)[3];
    real_T(*Uoff)[3];
    real_T Doff;
    real_T FeedRate;
    boolean_T trafo;
    ZSpdMode b_ZSpdMode;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    trafo = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "trafo");
    Poff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "Poff");
    Aoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "Aoff");
    Uoff = d_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "Uoff");
    Doff = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "Doff");
    P0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "P0");
    P1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "P1");
    A0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "A0");
    A1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "A1");
    U0 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "U0");
    U1 = d_emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "U1");
    FeedRate = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "FeedRate");
    b_ZSpdMode = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "ZSpdMode");
    // Invoke the target function
    ConstrLineStruct(trafo, *Poff, *Aoff, *Uoff, Doff, *P0, *P1, *A0, *A1, *U0, *U1, FeedRate,
                     b_ZSpdMode, &b_CurvStruct);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &b_CurvStruct);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void CopyCurvStruct_api(const mxArray *prhs, const mxArray **plhs)
{
    CurvStruct Copy;
    CurvStruct Curv;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs), "Curv", &Curv);
    // Invoke the target function
    CopyCurvStruct(&Curv, &Copy);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &Copy);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray *prhs
// Return Type  : void
//
void DisableDebugLog_api(const mxArray *prhs)
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    DebugCfg cfg;
    st.tls = emlrtRootTLSGlobal;
    // Marshall function inputs
    cfg = h_emlrt_marshallIn(&st, emlrtAliasP(prhs), "cfg");
    // Invoke the target function
    DisableDebugLog(cfg);
}

//
// Arguments    : const mxArray *prhs
// Return Type  : void
//
void EnableDebugLog_api(const mxArray *prhs)
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    DebugCfg cfg;
    st.tls = emlrtRootTLSGlobal;
    // Marshall function inputs
    cfg = h_emlrt_marshallIn(&st, emlrtAliasP(prhs), "cfg");
    // Invoke the target function
    EnableDebugLog(cfg);
}

//
// Arguments    : const mxArray * const prhs[3]
//                int32_T nlhs
//                const mxArray *plhs[4]
// Return Type  : void
//
void EvalCurvStruct_api(const mxArray *const prhs[3], int32_T nlhs, const mxArray *plhs[4])
{
    coder::array<real_T, 2U> r0D;
    coder::array<real_T, 2U> r1D;
    coder::array<real_T, 2U> r2D;
    coder::array<real_T, 2U> r3D;
    coder::array<real_T, 2U> u_vec;
    CurvStruct b_CurvStruct;
    FeedoptContext ctx;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    const mxArray *prhs_copy_idx_0;
    const mxArray *prhs_copy_idx_1;
    const mxArray *prhs_copy_idx_2;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    prhs_copy_idx_0 = prhs[0];
    prhs_copy_idx_1 = prhs[1];
    prhs_copy_idx_2 = emlrtProtectR2012b(prhs[2], 2, false, -1);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs_copy_idx_0), "ctx", &ctx);
    emlrt_marshallIn(&st, emlrtAliasP(prhs_copy_idx_1), "CurvStruct", &b_CurvStruct);
    u_vec.no_free();
    emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_2), "u_vec", u_vec);
    // Invoke the target function
    EvalCurvStruct(&ctx, &b_CurvStruct, u_vec, r0D, r1D, r2D, r3D);
    // Marshall function outputs
    r0D.no_free();
    plhs[0] = emlrt_marshallOut(r0D);
    if (nlhs > 1) {
        r1D.no_free();
        plhs[1] = emlrt_marshallOut(r1D);
    }
    if (nlhs > 2) {
        r2D.no_free();
        plhs[2] = emlrt_marshallOut(r2D);
    }
    if (nlhs > 3) {
        r3D.no_free();
        plhs[3] = emlrt_marshallOut(r3D);
    }
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[3]
//                const mxArray **plhs
// Return Type  : void
//
void EvalPosition_api(const mxArray *const prhs[3], const mxArray **plhs)
{
    CurvStruct Curv;
    CurvStruct Spline;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T(*r0D)[3];
    real_T u;
    st.tls = emlrtRootTLSGlobal;
    r0D = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Curv", &Curv);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Spline", &Spline);
    u = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "u");
    // Invoke the target function
    EvalPosition(&Curv, &Spline, u, *r0D);
    // Marshall function outputs
    *plhs = d_emlrt_marshallOut(*r0D);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray **plhs
// Return Type  : void
//
void FeedoptDefaultConfig_api(const mxArray **plhs)
{
    FeedoptConfig cfg;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    // Invoke the target function
    FeedoptDefaultConfig(&cfg);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &cfg);
}

//
// Arguments    : const mxArray *prhs
//                int32_T nlhs
//                const mxArray *plhs[3]
// Return Type  : void
//
void FeedoptPlan_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[3])
{
    CurvStruct opt_struct;
    FeedoptContext ctx;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    boolean_T optimized;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs), "ctx", &ctx);
    // Invoke the target function
    FeedoptPlan(&ctx, &optimized, &opt_struct);
    // Marshall function outputs
    plhs[0] = emlrt_marshallOut(&st, &ctx);
    if (nlhs > 1) {
        plhs[1] = b_emlrt_marshallOut(optimized);
    }
    if (nlhs > 2) {
        plhs[2] = emlrt_marshallOut(&st, &opt_struct);
    }
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void InitFeedoptPlan_api(const mxArray *prhs, const mxArray **plhs)
{
    FeedoptConfig cfg;
    FeedoptContext ctx;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs), "cfg", &cfg);
    // Invoke the target function
    InitFeedoptPlan(cfg, &ctx);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, &ctx);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[2]
// Return Type  : void
//
void PrintCurvStruct_api(const mxArray *const prhs[2])
{
    CurvStruct S;
    FeedoptContext ctx;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ctx", &ctx);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "S", &S);
    // Invoke the target function
    PrintCurvStruct(&ctx, &S);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[3]
//                const mxArray **plhs
// Return Type  : void
//
void ResampleNoCtx_api(const mxArray *const prhs[3], const mxArray **plhs)
{
    CurvStruct Curv;
    ResampleStateClass state;
    SplineBase Bl;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    state = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "state");
    emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Bl", &Bl);
    emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "Curv", &Curv);
    // Invoke the target function
    ResampleNoCtx(&state, &Bl, &Curv);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, state);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void ResampleState_api(const mxArray *prhs, const mxArray **plhs)
{
    ResampleStateClass state;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T dt;
    st.tls = emlrtRootTLSGlobal;
    // Marshall function inputs
    dt = emlrt_marshallIn(&st, emlrtAliasP(prhs), "dt");
    // Invoke the target function
    ResampleState(dt, &state);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, state);
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void bspline_copy_api(const mxArray *prhs, const mxArray **plhs)
{
    SplineBase Bl;
    SplineBase Copy;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAliasP(prhs), "Bl", &Bl);
    // Invoke the target function
    bspline_copy(&Bl, &Copy);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&Copy);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[2]
//                const mxArray **plhs
// Return Type  : void
//
void bspline_create_api(const mxArray *const prhs[2], const mxArray **plhs)
{
    SplineBase Bl;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T(*breakpoints)[10];
    int32_T degree;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    degree = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "degree");
    breakpoints = f_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "breakpoints");
    // Invoke the target function
    bspline_create(degree, *breakpoints, &Bl);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&Bl);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void c_roots__api(const mxArray *prhs, const mxArray **plhs)
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    creal_T Y_data[11];
    real_T(*coeffs_data)[12];
    int32_T coeffs_size[2];
    int32_T Y_size;
    st.tls = emlrtRootTLSGlobal;
    // Marshall function inputs
    emlrt_marshallIn(&st, emlrtAlias(prhs), "coeffs", (real_T **)&coeffs_data, coeffs_size);
    // Invoke the target function
    c_roots_(*coeffs_data, coeffs_size, Y_data, *(int32_T(*)[1]) & Y_size);
    // Marshall function outputs
    *plhs = emlrt_marshallOut(&st, Y_data, Y_size);
}

//
// Arguments    : const mxArray * const prhs[3]
//                const mxArray **plhs
// Return Type  : void
//
void linspace_api(const mxArray *const prhs[3], const mxArray **plhs)
{
    coder::array<real_T, 2U> y;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T d1;
    real_T d2;
    real_T n;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    d1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "d1");
    d2 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "d2");
    n = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "n");
    // Invoke the target function
    linspace(d1, d2, n, y);
    // Marshall function outputs
    y.no_free();
    *plhs = emlrt_marshallOut(y);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : const mxArray * const prhs[3]
//                const mxArray **plhs
// Return Type  : void
//
void sinspace_api(const mxArray *const prhs[3], const mxArray **plhs)
{
    coder::array<real_T, 2U> x;
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    real_T x0;
    real_T x1;
    int32_T N;
    st.tls = emlrtRootTLSGlobal;
    emlrtHeapReferenceStackEnterFcnR2012b(&st);
    // Marshall function inputs
    x0 = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "x0");
    x1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "x1");
    N = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "N");
    // Invoke the target function
    sinspace(x0, x1, N, x);
    // Marshall function outputs
    x.no_free();
    *plhs = emlrt_marshallOut(x);
    emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : void
// Return Type  : void
//
void sinspace_atexit()
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
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

//
// Arguments    : void
// Return Type  : void
//
void sinspace_initialize()
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    mexFunctionCreateRootTLS();
    st.tls = emlrtRootTLSGlobal;
    emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
    emlrtEnterRtStackR2012b(&st);
    emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void sinspace_terminate()
{
    emlrtStack st{
        nullptr, // site
        nullptr, // tls
        nullptr  // prev
    };
    st.tls = emlrtRootTLSGlobal;
    emlrtLeaveRtStackR2012b(&st);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_sinspace_api.cpp
//
// [EOF]
//
