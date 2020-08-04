//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  c_simplex.cpp
//
//  Code generation for function 'c_simplex'
//


// Include files
#include "c_simplex.h"
#include "_coder_c_simplex_mex.h"
#include "cpp_simplex.hpp"
#include "rt_nonfinite.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,// bFirstTime
  false,                               // bInitialized
  131594U,                             // fVersionInfo
  NULL,                                // fErrorFunction
  "c_simplex",                         // fFunctionName
  NULL,                                // fRTCallStack
  false,                               // bDebugMode
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },// fSigWrd
  NULL                                 // fSigMem
};

// Function Declarations
namespace ocn
{
  static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y);
  static const mxArray *b_emlrt_marshallOut(const boolean_T u);
  static void c_emlrt_marshallIn(const mxArray *A, const char_T *identifier,
    coder_internal_sparse *y);
  static const mxArray *c_emlrt_marshallOut(const int32_T u);
  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder_internal_sparse *y);
  static void e_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y);
  static void emlrt_marshallIn(const mxArray *f, const char_T *identifier, coder::
    array<real_T, 2U> &y);
  static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u);
  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<int32_T, 1U> &y);
  static int32_T g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId);
  static void h_emlrt_marshallIn(const mxArray *b, const char_T *identifier,
    coder::array<real_T, 1U> &y);
  static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y);
  static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret);
  static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret);
  static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<int32_T, 1U> &ret);
  static int32_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId);
  static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret);
}

// Function Definitions
namespace ocn
{
  static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 2U> &y)
  {
    j_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static const mxArray *b_emlrt_marshallOut(const boolean_T u)
  {
    const mxArray *y;
    const mxArray *m;
    y = NULL;
    m = emlrtCreateLogicalScalar(u);
    emlrtAssign(&y, m);
    return y;
  }

  static void c_emlrt_marshallIn(const mxArray *A, const char_T *identifier,
    coder_internal_sparse *y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    d_emlrt_marshallIn(emlrtAlias(A), &thisId, y);
    emlrtDestroyArray(&A);
  }

  static const mxArray *c_emlrt_marshallOut(const int32_T u)
  {
    const mxArray *y;
    const mxArray *m;
    y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = u;
    emlrtAssign(&y, m);
    return y;
  }

  static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder_internal_sparse *y)
  {
    emlrtMsgIdentifier thisId;
    const mxArray *propValues[6];
    int32_T iv[2];
    boolean_T bv[2];
    const char * propNames[6] = { "d", "colidx", "rowidx", "m", "n", "maxnz" };

    const char * propClasses[6] = { "coder.internal.sparse",
      "coder.internal.sparse", "coder.internal.sparse", "coder.internal.sparse",
      "coder.internal.sparse", "coder.internal.sparse" };

    for (int32_T i = 0; i < 6; i++) {
      propValues[i] = NULL;
    }

    thisId.fParent = parentId;
    thisId.bParentIsCell = false;
    iv[0] = -1;
    bv[0] = true;
    iv[1] = -1;
    bv[1] = true;
    emlrtCheckSparse(emlrtRootTLSGlobal, parentId, u, &iv[0], &bv[0],
                     mxDOUBLE_CLASS, mxREAL);
    emlrtCheckMcosClass2017a(emlrtRootTLSGlobal, parentId, u,
      "_primitive_sparse");
    emlrtAssign(&u, emlrtConvertInstanceToRedirectTarget(emlrtRootTLSGlobal, u,
      0, "coder.internal.sparse"));
    emlrtCheckMcosClass2017a(emlrtRootTLSGlobal, parentId, u,
      "coder.internal.sparse");
    emlrtGetAllProperties(emlrtRootTLSGlobal, u, 0, 6, propNames, propClasses,
                          propValues);
    thisId.fIdentifier = "d";
    e_emlrt_marshallIn(emlrtAlias(propValues[0]), &thisId, y->d);
    thisId.fIdentifier = "colidx";
    f_emlrt_marshallIn(emlrtAlias(propValues[1]), &thisId, y->colidx);
    thisId.fIdentifier = "rowidx";
    f_emlrt_marshallIn(emlrtAlias(propValues[2]), &thisId, y->rowidx);
    thisId.fIdentifier = "m";
    y->m = g_emlrt_marshallIn(emlrtAlias(propValues[3]), &thisId);
    thisId.fIdentifier = "n";
    y->n = g_emlrt_marshallIn(emlrtAlias(propValues[4]), &thisId);
    thisId.fIdentifier = "maxnz";
    y->maxnz = g_emlrt_marshallIn(emlrtAlias(propValues[5]), &thisId);
    emlrtDestroyArrays(6, (const mxArray **)&propValues);
    emlrtDestroyArray(&u);
  }

  static void e_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y)
  {
    k_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void emlrt_marshallIn(const mxArray *f, const char_T *identifier, coder::
    array<real_T, 2U> &y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    b_emlrt_marshallIn(emlrtAlias(f), &thisId, y);
    emlrtDestroyArray(&f);
  }

  static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u)
  {
    const mxArray *y;
    const mxArray *m;
    static const int32_T iv[2] = { 0, 0 };

    y = NULL;
    m = emlrtCreateNumericArray(2, &iv[0], mxDOUBLE_CLASS, mxREAL);
    emlrtMxSetData((mxArray *)m, &(((coder::array<real_T, 2U> *)&u)->data())[0]);
    emlrtSetDimensions((mxArray *)m, ((coder::array<real_T, 2U> *)&u)->size(), 2);
    emlrtAssign(&y, m);
    return y;
  }

  static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<int32_T, 1U> &y)
  {
    l_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static int32_T g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId)
  {
    int32_T y;
    y = m_emlrt_marshallIn(emlrtAlias(u), parentId);
    emlrtDestroyArray(&u);
    return y;
  }

  static void h_emlrt_marshallIn(const mxArray *b, const char_T *identifier,
    coder::array<real_T, 1U> &y)
  {
    emlrtMsgIdentifier thisId;
    thisId.fIdentifier = const_cast<const char *>(identifier);
    thisId.fParent = NULL;
    thisId.bParentIsCell = false;
    i_emlrt_marshallIn(emlrtAlias(b), &thisId, y);
    emlrtDestroyArray(&b);
  }

  static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
    *parentId, coder::array<real_T, 1U> &y)
  {
    n_emlrt_marshallIn(emlrtAlias(u), parentId, y);
    emlrtDestroyArray(&u);
  }

  static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 2U> &ret)
  {
    static const int32_T dims[2] = { -1, -1 };

    const boolean_T bv[2] = { true, true };

    int32_T iv[2];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      2U, dims, &bv[0], iv);
    ret.prealloc((iv[0] * iv[1]));
    ret.set_size(iv[0], iv[1]);
    ret.set(((real_T *)emlrtMxGetData(src)), ret.size(0), ret.size(1));
    emlrtDestroyArray(&src);
  }

  static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<real_T, 1U> &ret)
  {
    static const int32_T dims[1] = { -1 };

    const boolean_T bv[1] = { true };

    int32_T iv[1];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false,
      1U, dims, &bv[0], iv);
    ret.set_size(iv[0]);
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &(ret.data())[0], 8, false);
    emlrtDestroyArray(&src);
  }

  static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
    *msgId, coder::array<int32_T, 1U> &ret)
  {
    static const int32_T dims[1] = { -1 };

    const boolean_T bv[1] = { true };

    int32_T iv[1];
    emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 1U,
      dims, &bv[0], iv);
    ret.set_size(iv[0]);
    emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &(ret.data())[0], 4, false);
    emlrtDestroyArray(&src);
  }

  static int32_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

  static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

  void c_simplex(const coder::array<real_T, 2U> &f, const coder_internal_sparse *
                 A, coder::array<real_T, 1U> &b, const coder::array<real_T, 2U>
                 &Aeq, const coder::array<real_T, 1U> &beq, coder::array<real_T,
                 2U> &C, boolean_T *success, int32_T *status)
  {
    int32_T cnfixeddim;
    boolean_T emptyflag_idx_0;
    boolean_T isAcceptableEmpty;
    boolean_T allEmpty;
    int32_T numalloc;
    int32_T cnvardim;
    int32_T nrowk;
    int32_T nzCount;
    int32_T kpend;
    coder::array<real_T, 1U> Atot_d;
    coder::array<int32_T, 1U> Atot_colidx;
    coder::array<int32_T, 1U> Atot_rowidx;
    coder::array<int32_T, 1U> Ais;
    coder::array<int32_T, 1U> Ajs;
    coder::array<real_T, 1U> Avs;
    int32_T fsize[2];
    int32_T Asize[2];
    int32_T bsize[2];
    int32_T beqsize[2];
    int32_T Csize[2];
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
    cnfixeddim = A->n;
    if ((A->m == 0) || (A->n == 0)) {
      emptyflag_idx_0 = true;
    } else {
      emptyflag_idx_0 = false;
    }

    isAcceptableEmpty = ((Aeq.size(0) == 0) || (Aeq.size(1) == 0));
    allEmpty = (emptyflag_idx_0 && isAcceptableEmpty);
    if ((!isAcceptableEmpty) && emptyflag_idx_0) {
      cnfixeddim = Aeq.size(1);
    }

    numalloc = 0;
    cnvardim = 0;
    if (allEmpty || (!emptyflag_idx_0)) {
      numalloc = A->colidx[A->colidx.size(0) - 1] - 1;
      cnvardim = A->m;
    }

    if (allEmpty || ((Aeq.size(0) != 0) && (Aeq.size(1) != 0))) {
      nrowk = 0;
      nzCount = Aeq.size(0) * Aeq.size(1);
      for (kpend = 0; kpend < nzCount; kpend++) {
        if (Aeq[kpend] != 0.0) {
          nrowk++;
        }
      }

      numalloc += nrowk;
      cnvardim += Aeq.size(0);
    }

    if (numalloc < 1) {
      numalloc = 1;
    }

    Atot_d.set_size(numalloc);
    Atot_colidx.set_size((cnfixeddim + 1));
    Atot_colidx[0] = 1;
    Atot_rowidx.set_size(numalloc);
    for (nzCount = 0; nzCount < numalloc; nzCount++) {
      Atot_d[nzCount] = 0.0;
      Atot_rowidx[nzCount] = 0;
    }

    for (numalloc = 0; numalloc < cnfixeddim; numalloc++) {
      Atot_colidx[numalloc + 1] = 1;
    }

    nzCount = Atot_colidx.size(0);
    for (numalloc = 0; numalloc <= nzCount - 2; numalloc++) {
      Atot_colidx[numalloc] = 1;
    }

    Atot_colidx[Atot_colidx.size(0) - 1] = 1;
    nzCount = -1;
    if ((A->m == 0) || (A->n == 0)) {
      emptyflag_idx_0 = true;
    } else {
      emptyflag_idx_0 = false;
    }

    isAcceptableEmpty = ((Aeq.size(0) == 0) || (Aeq.size(1) == 0));
    for (int32_T ccol = 0; ccol < cnfixeddim; ccol++) {
      int32_T cidx;
      numalloc = 1;
      if (!emptyflag_idx_0) {
        cidx = nzCount;
        numalloc = A->colidx[ccol];
        nrowk = A->colidx[ccol + 1];
        kpend = nrowk - 1;
        for (int32_T kp = numalloc; kp <= kpend; kp++) {
          cidx++;
          Atot_rowidx[cidx] = A->rowidx[kp - 1];
          Atot_d[cidx] = A->d[kp - 1];
        }

        nzCount = (nzCount + nrowk) - A->colidx[ccol];
        numalloc = A->m + 1;
      }

      if (!isAcceptableEmpty) {
        nrowk = Aeq.size(0);
        cidx = nzCount;
        for (kpend = 0; kpend < nrowk; kpend++) {
          real_T dk;
          dk = Aeq[kpend + Aeq.size(0) * ccol];
          if (dk != 0.0) {
            cidx++;
            Atot_rowidx[cidx] = kpend + numalloc;
            Atot_d[cidx] = dk;
          }
        }

        nzCount = cidx;
      }

      Atot_colidx[ccol + 1] = nzCount + 2;
    }

    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    C.set_size(f.size(0), f.size(1));
    numalloc = f.size(1);
    for (nzCount = 0; nzCount < numalloc; nzCount++) {
      nrowk = f.size(0);
      for (kpend = 0; kpend < nrowk; kpend++) {
        C[kpend + C.size(0) * nzCount] = 0.0;
      }
    }

    numalloc = Atot_colidx[Atot_colidx.size(0) - 1] - 2;
    if (Atot_colidx[Atot_colidx.size(0) - 1] - 1 == 0) {
      Ais.set_size(0);
      Ajs.set_size(0);
      Avs.set_size(0);
    } else {
      Ais.set_size((Atot_colidx[Atot_colidx.size(0) - 1] - 1));
      Ajs.set_size((Atot_colidx[Atot_colidx.size(0) - 1] - 1));
      Avs.set_size((Atot_colidx[Atot_colidx.size(0) - 1] - 1));
      for (kpend = 0; kpend <= numalloc; kpend++) {
        Ais[kpend] = Atot_rowidx[kpend];
        Avs[kpend] = Atot_d[kpend];
      }

      kpend = 0;
      nrowk = 1;
      while (kpend < numalloc + 1) {
        if (kpend == Atot_colidx[nrowk] - 1) {
          nrowk++;
        } else {
          kpend++;
          Ajs[kpend - 1] = nrowk;
        }
      }

      if (Atot_colidx[Atot_colidx.size(0) - 1] - 1 == 1) {
        if (kpend == 0) {
          Ais.set_size(0);
          Ajs.set_size(0);
          Avs.set_size(0);
        }
      } else {
        if (1 > kpend) {
          nrowk = 0;
        } else {
          nrowk = kpend;
        }

        Ais.set_size(nrowk);
        if (1 > kpend) {
          nrowk = 0;
        } else {
          nrowk = kpend;
        }

        Ajs.set_size(nrowk);
        if (1 > kpend) {
          kpend = 0;
        }

        Avs.set_size(kpend);
      }
    }

    numalloc = Ais.size(0);
    for (nzCount = 0; nzCount < numalloc; nzCount++) {
      Ais[nzCount] = Ais[nzCount] - 1;
    }

    numalloc = Ajs.size(0);
    for (nzCount = 0; nzCount < numalloc; nzCount++) {
      Ajs[nzCount] = Ajs[nzCount] - 1;
    }

    fsize[0] = f.size(0);
    fsize[1] = f.size(1);
    Asize[0] = cnvardim;
    Asize[1] = cnfixeddim;
    nrowk = 0;
    nzCount = Avs.size(0);
    for (kpend = 0; kpend < nzCount; kpend++) {
      if (Avs[kpend] != 0.0) {
        nrowk++;
      }
    }

    bsize[0] = b.size(0);
    bsize[1] = 1;
    beqsize[0] = beq.size(0);
    beqsize[1] = 1;
    Csize[0] = f.size(0);
    Csize[1] = f.size(1);
    *status = simplex_solve(&f[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0],
      &(Ajs.data())[0], &Asize[0], nrowk, &(b.data())[0], &bsize[0], &(((coder::
      array<real_T, 1U> *)&beq)->data())[0], &beqsize[0], &C[0], &Csize[0]);

    //          C = solution.solution;
    *success = (*status == 0);
    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }

  void c_simplex_api(const mxArray * const prhs[5], int32_T nlhs, const mxArray *
                     plhs[3])
  {
    const mxArray *prhs_copy_idx_2;
    coder::array<real_T, 2U> f;
    coder_internal_sparse A;
    coder::array<real_T, 1U> b;
    coder::array<real_T, 2U> Aeq;
    coder::array<real_T, 1U> beq;
    coder::array<real_T, 2U> C;
    boolean_T success;
    int32_T status;
    emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
    prhs_copy_idx_2 = emlrtProtectR2012b(prhs[2], 2, false, -1);

    // Marshall function inputs
    f.no_free();
    emlrt_marshallIn(emlrtAlias(prhs[0]), "f", f);
    c_emlrt_marshallIn(emlrtAliasP(prhs[1]), "A", &A);
    b.no_free();
    h_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_2), "b", b);
    Aeq.no_free();
    emlrt_marshallIn(emlrtAlias(prhs[3]), "Aeq", Aeq);
    beq.no_free();
    h_emlrt_marshallIn(emlrtAlias(prhs[4]), "beq", beq);

    // Invoke the target function
    c_simplex(f, &A, b, Aeq, beq, C, &success, &status);

    // Marshall function outputs
    C.no_free();
    plhs[0] = emlrt_marshallOut(C);
    if (nlhs > 1) {
      plhs[1] = b_emlrt_marshallOut(success);
    }

    if (nlhs > 2) {
      plhs[2] = c_emlrt_marshallOut(status);
    }

    emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  }
}

void c_simplex_atexit()
{
  ocn::mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

namespace ocn
{
  void c_simplex_initialize()
  {
    mex_InitInfAndNan();
    mexFunctionCreateRootTLS();
    emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
    emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
    emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
  }

  void c_simplex_terminate()
  {
    emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  }
}

// End of code generation (c_simplex.cpp)
