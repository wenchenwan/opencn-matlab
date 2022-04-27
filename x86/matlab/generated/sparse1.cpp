//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "sparse1.h"
#include "locBsearch.h"
#include "coder_array.h"
#include <cstddef>
#include <cstring>
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : sparse *b_this
//                int numAllocRequested
//                int ub1
//                int lb2
//                int ub2
// Return Type  : void
//
namespace ocn {
namespace coder {
void sparse::b_realloc(sparse *b_this, int numAllocRequested, int ub1, int lb2, int ub2)
{
    ::coder::array<double, 1U> dt;
    ::coder::array<int, 1U> rowidxt;
    int b_loop_ub;
    int highOrderA;
    int highOrderB;
    int loop_ub;
    int lowOrderB;
    int numAlloc;
    int overflow;
    int partialResults_idx_0_tmp;
    int partialResults_idx_1;
    int tmp;
    rowidxt.set_size(b_this->rowidx.size(0));
    loop_ub = b_this->rowidx.size(0);
    for (int i{0}; i < loop_ub; i++) {
        rowidxt[i] = b_this->rowidx[i];
    }
    dt.set_size(b_this->d.size(0));
    b_loop_ub = b_this->d.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        dt[i1] = b_this->d[i1];
    }
    int lowOrderA;
    highOrderA = b_this->m >> 16;
    lowOrderA = b_this->m & 65535;
    highOrderB = b_this->n >> 16;
    lowOrderB = b_this->n & 65535;
    partialResults_idx_0_tmp = lowOrderA * lowOrderB;
    tmp = lowOrderA * highOrderB;
    partialResults_idx_1 = tmp << 16;
    overflow = tmp >> 16;
    if (overflow <= 0) {
        tmp = highOrderA * lowOrderB;
        overflow = tmp >> 16;
        if (overflow <= 0) {
            overflow = highOrderA * highOrderB;
            if (overflow <= 0) {
                int a__4;
                if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
                    a__4 = (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
                    overflow = 1;
                } else {
                    a__4 = partialResults_idx_0_tmp + partialResults_idx_1;
                }
                if (a__4 > MAX_int32_T - (tmp << 16)) {
                    overflow++;
                }
            }
        }
    }
    if (overflow == 0) {
        int u1;
        int y;
        u1 = b_this->m * b_this->n;
        if (numAllocRequested <= u1) {
            y = numAllocRequested;
        } else {
            y = u1;
        }
        if (1 >= y) {
            numAlloc = 1;
        } else {
            numAlloc = y;
        }
    } else if (1 >= numAllocRequested) {
        numAlloc = 1;
    } else {
        numAlloc = numAllocRequested;
    }
    b_this->rowidx.set_size(numAlloc);
    b_this->d.set_size(numAlloc);
    for (int i2{0}; i2 < numAlloc; i2++) {
        b_this->rowidx[i2] = 0;
        b_this->d[i2] = 0.0;
    }
    b_this->maxnz = numAlloc;
    for (int k{0}; k < ub1; k++) {
        b_this->rowidx[k] = rowidxt[k];
        b_this->d[k] = dt[k];
    }
    for (int b_k{lb2}; b_k <= ub2; b_k++) {
        b_this->rowidx[b_k] = rowidxt[b_k - 1];
        b_this->d[b_k] = dt[b_k - 1];
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &varargin_2
//                sparse *c
// Return Type  : void
//
void sparse::b_vertcat(const ::coder::array<double, 2U> &varargin_2, sparse *c) const
{
    int cnfixeddim;
    int cnnz;
    int cnvardim;
    int i2;
    int numalloc;
    int nzCount;
    bool allEmpty;
    bool emptyflag_idx_0;
    bool emptyflag_idx_1;
    bool isAcceptableEmpty;
    bool isAcceptableEmpty_tmp;
    cnfixeddim = n;
    if ((m == 0) || (n == 0)) {
        isAcceptableEmpty_tmp = true;
    } else {
        isAcceptableEmpty_tmp = false;
    }
    isAcceptableEmpty = (varargin_2.size(1) == 0);
    allEmpty = (isAcceptableEmpty_tmp && isAcceptableEmpty);
    if ((!isAcceptableEmpty) && isAcceptableEmpty_tmp) {
        cnfixeddim = varargin_2.size(1);
    }
    cnnz = 0;
    cnvardim = 0;
    if (allEmpty || (!isAcceptableEmpty_tmp)) {
        cnnz = colidx[colidx.size(0) - 1] - 1;
        cnvardim = m;
    }
    if (allEmpty || (varargin_2.size(1) != 0)) {
        int b_n;
        int i;
        b_n = 0;
        i = varargin_2.size(0) * varargin_2.size(1);
        for (int k{0}; k < i; k++) {
            if (varargin_2[k] != 0.0) {
                b_n++;
            }
        }
        cnnz += b_n;
        cnvardim += varargin_2.size(0);
    }
    c->m = cnvardim;
    c->n = cnfixeddim;
    if (cnnz >= 1) {
        numalloc = cnnz;
    } else {
        numalloc = 1;
    }
    c->d.set_size(numalloc);
    c->maxnz = numalloc;
    c->colidx.set_size(cnfixeddim + 1);
    c->colidx[0] = 1;
    c->rowidx.set_size(numalloc);
    for (int i1{0}; i1 < numalloc; i1++) {
        c->d[i1] = 0.0;
        c->rowidx[i1] = 0;
    }
    for (int b_c{0}; b_c < cnfixeddim; b_c++) {
        c->colidx[b_c + 1] = 1;
    }
    i2 = c->colidx.size(0);
    for (int c_c{0}; c_c <= i2 - 2; c_c++) {
        c->colidx[c_c] = 1;
    }
    c->colidx[c->colidx.size(0) - 1] = 1;
    nzCount = -1;
    if ((m == 0) || (n == 0)) {
        emptyflag_idx_0 = true;
    } else {
        emptyflag_idx_0 = false;
    }
    emptyflag_idx_1 = (varargin_2.size(1) == 0);
    for (int ccol{0}; ccol < cnfixeddim; ccol++) {
        int crowoffs;
        crowoffs = 1;
        if (!emptyflag_idx_0) {
            int kpend;
            int kpend_tmp;
            int kpstart;
            kpstart = colidx[ccol];
            kpend_tmp = colidx[ccol + 1];
            kpend = kpend_tmp - 1;
            for (int kp{kpstart}; kp <= kpend; kp++) {
                int i3;
                i3 = ((nzCount + kp) - kpstart) + 1;
                c->rowidx[i3] = rowidx[kp - 1];
                c->d[i3] = d[kp - 1];
            }
            nzCount = (nzCount + kpend_tmp) - colidx[ccol];
            crowoffs = m + 1;
        }
        if (!emptyflag_idx_1) {
            int cidx;
            int nrowk;
            nrowk = varargin_2.size(0);
            cidx = nzCount;
            for (int row{0}; row < nrowk; row++) {
                double dk;
                dk = varargin_2[row + varargin_2.size(0) * ccol];
                if (dk != 0.0) {
                    cidx++;
                    c->rowidx[cidx] = row + crowoffs;
                    c->d[cidx] = dk;
                }
            }
            nzCount = cidx;
        }
        c->colidx[ccol + 1] = nzCount + 2;
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
//                double varargin_2
// Return Type  : void
//
void sparse::parenAssign(const ::coder::array<double, 2U> &varargin_1, double varargin_2)
{
    int sm;
    int vidx;
    bool found;
    sm = varargin_1.size(1);
    for (int ridx{0}; ridx < sm; ridx++) {
        double nt;
        double thisv;
        nt = varargin_1[ridx];
        sparse_locBsearch(rowidx, static_cast<int>(nt), colidx[static_cast<int>(varargin_2) - 1],
                          colidx[static_cast<int>(varargin_2)], &vidx, &found);
        if (found) {
            thisv = d[vidx - 1];
        } else {
            thisv = 0.0;
        }
        if (thisv != 0.0) {
            d[vidx - 1] = -1.0;
        } else {
            int i;
            int i1;
            int k;
            int scalarLB;
            int vectorUB;
            if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
                sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx, vidx + 1,
                                  colidx[colidx.size(0) - 1] - 1);
                rowidx[vidx] = static_cast<int>(nt);
                d[vidx] = -1.0;
            } else {
                int nelem;
                nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                if (nelem > 0) {
                    std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                                 (unsigned int)((size_t)nelem * sizeof(int)));
                    std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                                 (unsigned int)((size_t)nelem * sizeof(double)));
                }
                d[vidx] = -1.0;
                rowidx[vidx] = static_cast<int>(nt);
            }
            i = static_cast<int>(varargin_2) + 1;
            i1 = n + 1;
            scalarLB =
                ((((i1 - static_cast<int>(varargin_2)) / 4) << 2) + static_cast<int>(varargin_2)) +
                1;
            vectorUB = scalarLB - 4;
            for (k = i; k <= vectorUB; k += 4) {
                __m128i r;
                r = _mm_loadu_si128((const __m128i *)&colidx[k - 1]);
                _mm_storeu_si128((__m128i *)&colidx[k - 1], _mm_add_epi32(r, _mm_set1_epi32(1)));
            }
            for (k = scalarLB; k <= i1; k++) {
                colidx[k - 1] = colidx[k - 1] + 1;
            }
        }
    }
}

//
// Arguments    : double varargin_1
//                double varargin_2
// Return Type  : void
//
void sparse::parenAssign(double varargin_1, double varargin_2)
{
    double thisv;
    int vidx;
    bool found;
    sparse_locBsearch(rowidx, static_cast<int>(varargin_1),
                      colidx[static_cast<int>(varargin_2) - 1],
                      colidx[static_cast<int>(varargin_2)], &vidx, &found);
    if (found) {
        thisv = d[vidx - 1];
    } else {
        thisv = 0.0;
    }
    if (thisv != 0.0) {
        d[vidx - 1] = -1.0;
    } else {
        int i;
        int i1;
        int k;
        int scalarLB;
        int vectorUB;
        if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
            sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx, vidx + 1,
                              colidx[colidx.size(0) - 1] - 1);
            rowidx[vidx] = static_cast<int>(varargin_1);
            d[vidx] = -1.0;
        } else {
            int nelem;
            nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
            if (nelem > 0) {
                std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                             (unsigned int)((size_t)nelem * sizeof(int)));
                std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                             (unsigned int)((size_t)nelem * sizeof(double)));
            }
            d[vidx] = -1.0;
            rowidx[vidx] = static_cast<int>(varargin_1);
        }
        i = static_cast<int>(varargin_2) + 1;
        i1 = n + 1;
        scalarLB =
            ((((i1 - static_cast<int>(varargin_2)) / 4) << 2) + static_cast<int>(varargin_2)) + 1;
        vectorUB = scalarLB - 4;
        for (k = i; k <= vectorUB; k += 4) {
            __m128i r;
            r = _mm_loadu_si128((const __m128i *)&colidx[k - 1]);
            _mm_storeu_si128((__m128i *)&colidx[k - 1], _mm_add_epi32(r, _mm_set1_epi32(1)));
        }
        for (k = scalarLB; k <= i1; k++) {
            colidx[k - 1] = colidx[k - 1] + 1;
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
//                const ::coder::array<double, 2U> &varargin_2
// Return Type  : void
//
void sparse::parenAssign(const ::coder::array<double, 2U> &rhs,
                         const ::coder::array<double, 2U> &varargin_1,
                         const ::coder::array<double, 2U> &varargin_2)
{
    int rhsIter_idx;
    int sm;
    int sn;
    int vidx;
    bool found;
    sm = varargin_1.size(1);
    sn = varargin_2.size(1);
    rhsIter_idx = 0;
    for (int cidx{0}; cidx < sn; cidx++) {
        double nt;
        nt = varargin_2[cidx];
        for (int ridx{0}; ridx < sm; ridx++) {
            double b_nt;
            double rhsv;
            double thisv;
            b_nt = varargin_1[ridx];
            sparse_locBsearch(rowidx, static_cast<int>(b_nt), colidx[static_cast<int>(nt) - 1],
                              colidx[static_cast<int>(nt)], &vidx, &found);
            if (found) {
                thisv = d[vidx - 1];
            } else {
                thisv = 0.0;
            }
            rhsv = rhs[rhsIter_idx];
            rhsIter_idx++;
            if ((thisv != 0.0) || (rhsv != 0.0)) {
                if ((thisv != 0.0) && (rhsv != 0.0)) {
                    d[vidx - 1] = rhsv;
                } else if (thisv == 0.0) {
                    int b_k;
                    int b_scalarLB;
                    int b_vectorUB;
                    int i2;
                    int i3;
                    if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
                        sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx, vidx + 1,
                                          colidx[colidx.size(0) - 1] - 1);
                        rowidx[vidx] = static_cast<int>(b_nt);
                        d[vidx] = rhsv;
                    } else {
                        int b_nelem;
                        b_nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                        if (b_nelem > 0) {
                            std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                                         (unsigned int)((size_t)b_nelem * sizeof(int)));
                            std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                                         (unsigned int)((size_t)b_nelem * sizeof(double)));
                        }
                        d[vidx] = rhsv;
                        rowidx[vidx] = static_cast<int>(b_nt);
                    }
                    i2 = static_cast<int>(nt) + 1;
                    i3 = n + 1;
                    b_scalarLB =
                        ((((i3 - static_cast<int>(nt)) / 4) << 2) + static_cast<int>(nt)) + 1;
                    b_vectorUB = b_scalarLB - 4;
                    for (b_k = i2; b_k <= b_vectorUB; b_k += 4) {
                        __m128i r1;
                        r1 = _mm_loadu_si128((const __m128i *)&colidx[b_k - 1]);
                        _mm_storeu_si128((__m128i *)&colidx[b_k - 1],
                                         _mm_add_epi32(r1, _mm_set1_epi32(1)));
                    }
                    for (b_k = b_scalarLB; b_k <= i3; b_k++) {
                        colidx[b_k - 1] = colidx[b_k - 1] + 1;
                    }
                } else {
                    int i;
                    int i1;
                    int k;
                    int nelem;
                    int scalarLB;
                    int vectorUB;
                    nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                    if (nelem > 0) {
                        std::memmove((void *)&rowidx[vidx - 1], (void *)&rowidx[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(int)));
                        std::memmove((void *)&d[vidx - 1], (void *)&d[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(double)));
                    }
                    i = static_cast<int>(nt) + 1;
                    i1 = n + 1;
                    scalarLB =
                        ((((i1 - static_cast<int>(nt)) / 4) << 2) + static_cast<int>(nt)) + 1;
                    vectorUB = scalarLB - 4;
                    for (k = i; k <= vectorUB; k += 4) {
                        __m128i r;
                        r = _mm_loadu_si128((const __m128i *)&colidx[k - 1]);
                        _mm_storeu_si128((__m128i *)&colidx[k - 1],
                                         _mm_sub_epi32(r, _mm_set1_epi32(1)));
                    }
                    for (k = scalarLB; k <= i1; k++) {
                        colidx[k - 1] = colidx[k - 1] - 1;
                    }
                }
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
//                sparse *c
// Return Type  : void
//
void sparse::vertcat(const ::coder::array<double, 2U> &varargin_1, sparse *c) const
{
    int cnfixeddim;
    int cnnz;
    int cnvardim;
    int i2;
    int numalloc;
    int nzCount;
    bool allEmpty;
    bool emptyflag_idx_0;
    bool emptyflag_idx_1;
    bool isAcceptableEmpty;
    bool isAcceptableEmpty_tmp;
    cnfixeddim = varargin_1.size(1);
    isAcceptableEmpty = ((varargin_1.size(0) == 0) || (varargin_1.size(1) == 0));
    if ((m == 0) || (n == 0)) {
        isAcceptableEmpty_tmp = true;
    } else {
        isAcceptableEmpty_tmp = false;
    }
    allEmpty = (isAcceptableEmpty && isAcceptableEmpty_tmp);
    if ((!isAcceptableEmpty_tmp) && isAcceptableEmpty) {
        cnfixeddim = n;
    }
    cnnz = 0;
    cnvardim = 0;
    if (allEmpty || ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0))) {
        int b_n;
        int i;
        b_n = 0;
        i = varargin_1.size(0) * varargin_1.size(1);
        for (int k{0}; k < i; k++) {
            if (varargin_1[k] != 0.0) {
                b_n++;
            }
        }
        cnnz = b_n;
        cnvardim = varargin_1.size(0);
    }
    if (allEmpty || (!isAcceptableEmpty_tmp)) {
        cnnz = (cnnz + colidx[colidx.size(0) - 1]) - 1;
        cnvardim += m;
    }
    c->m = cnvardim;
    c->n = cnfixeddim;
    if (cnnz >= 1) {
        numalloc = cnnz;
    } else {
        numalloc = 1;
    }
    c->d.set_size(numalloc);
    c->maxnz = numalloc;
    c->colidx.set_size(cnfixeddim + 1);
    c->colidx[0] = 1;
    c->rowidx.set_size(numalloc);
    for (int i1{0}; i1 < numalloc; i1++) {
        c->d[i1] = 0.0;
        c->rowidx[i1] = 0;
    }
    for (int b_c{0}; b_c < cnfixeddim; b_c++) {
        c->colidx[b_c + 1] = 1;
    }
    i2 = c->colidx.size(0);
    for (int c_c{0}; c_c <= i2 - 2; c_c++) {
        c->colidx[c_c] = 1;
    }
    c->colidx[c->colidx.size(0) - 1] = 1;
    nzCount = -1;
    emptyflag_idx_0 = ((varargin_1.size(0) == 0) || (varargin_1.size(1) == 0));
    if ((m == 0) || (n == 0)) {
        emptyflag_idx_1 = true;
    } else {
        emptyflag_idx_1 = false;
    }
    for (int ccol{0}; ccol < cnfixeddim; ccol++) {
        int crowoffs;
        crowoffs = 0;
        if (!emptyflag_idx_0) {
            int cidx;
            int nrowk;
            nrowk = varargin_1.size(0);
            cidx = nzCount;
            for (int row{0}; row < nrowk; row++) {
                if (varargin_1[row + varargin_1.size(0) * ccol] != 0.0) {
                    cidx++;
                    c->rowidx[cidx] = row + 1;
                    c->d[cidx] = -1.0;
                }
            }
            nzCount = cidx;
            crowoffs = varargin_1.size(0);
        }
        if (!emptyflag_idx_1) {
            int kpend;
            int kpend_tmp;
            int kpstart;
            kpstart = colidx[ccol];
            kpend_tmp = colidx[ccol + 1];
            kpend = kpend_tmp - 1;
            for (int kp{kpstart}; kp <= kpend; kp++) {
                int i3;
                i3 = ((nzCount + kp) - kpstart) + 1;
                c->rowidx[i3] = rowidx[kp - 1] + crowoffs;
                c->d[i3] = d[kp - 1];
            }
            nzCount = (nzCount + kpend_tmp) - colidx[ccol];
        }
        c->colidx[ccol + 1] = nzCount + 2;
    }
}

//
// Arguments    : const sparse *varargin_2
//                sparse *c
// Return Type  : void
//
void sparse::vertcat(const sparse *varargin_2, sparse *c) const
{
    int cnfixeddim;
    int cnnz;
    int cnvardim;
    int i1;
    int numalloc;
    int nzCount;
    bool allEmpty;
    bool b_isAcceptableEmpty_tmp;
    bool emptyflag_idx_0;
    bool emptyflag_idx_1;
    bool isAcceptableEmpty_tmp;
    cnfixeddim = n;
    if ((m == 0) || (n == 0)) {
        isAcceptableEmpty_tmp = true;
    } else {
        isAcceptableEmpty_tmp = false;
    }
    if ((varargin_2->m == 0) || (varargin_2->n == 0)) {
        b_isAcceptableEmpty_tmp = true;
    } else {
        b_isAcceptableEmpty_tmp = false;
    }
    allEmpty = (isAcceptableEmpty_tmp && b_isAcceptableEmpty_tmp);
    if ((!b_isAcceptableEmpty_tmp) && isAcceptableEmpty_tmp) {
        cnfixeddim = varargin_2->n;
    }
    cnnz = 0;
    cnvardim = 0;
    if (allEmpty || (!isAcceptableEmpty_tmp)) {
        cnnz = colidx[colidx.size(0) - 1] - 1;
        cnvardim = m;
    }
    if (allEmpty || (!b_isAcceptableEmpty_tmp)) {
        cnnz = (cnnz + varargin_2->colidx[varargin_2->colidx.size(0) - 1]) - 1;
        cnvardim += varargin_2->m;
    }
    c->m = cnvardim;
    c->n = cnfixeddim;
    if (cnnz >= 1) {
        numalloc = cnnz;
    } else {
        numalloc = 1;
    }
    c->d.set_size(numalloc);
    c->maxnz = numalloc;
    c->colidx.set_size(cnfixeddim + 1);
    c->colidx[0] = 1;
    c->rowidx.set_size(numalloc);
    for (int i{0}; i < numalloc; i++) {
        c->d[i] = 0.0;
        c->rowidx[i] = 0;
    }
    for (int b_c{0}; b_c < cnfixeddim; b_c++) {
        c->colidx[b_c + 1] = 1;
    }
    i1 = c->colidx.size(0);
    for (int c_c{0}; c_c <= i1 - 2; c_c++) {
        c->colidx[c_c] = 1;
    }
    c->colidx[c->colidx.size(0) - 1] = 1;
    nzCount = -1;
    if ((m == 0) || (n == 0)) {
        emptyflag_idx_0 = true;
    } else {
        emptyflag_idx_0 = false;
    }
    if ((varargin_2->m == 0) || (varargin_2->n == 0)) {
        emptyflag_idx_1 = true;
    } else {
        emptyflag_idx_1 = false;
    }
    for (int ccol{0}; ccol < cnfixeddim; ccol++) {
        int crowoffs;
        int kpend;
        int kpstart;
        crowoffs = 0;
        if (!emptyflag_idx_0) {
            int kpend_tmp;
            kpstart = colidx[ccol];
            kpend_tmp = colidx[ccol + 1];
            kpend = kpend_tmp - 1;
            for (int kp{kpstart}; kp <= kpend; kp++) {
                int i2;
                i2 = ((nzCount + kp) - kpstart) + 1;
                c->rowidx[i2] = rowidx[kp - 1];
                c->d[i2] = d[kp - 1];
            }
            nzCount = (nzCount + kpend_tmp) - colidx[ccol];
            crowoffs = m;
        }
        if (!emptyflag_idx_1) {
            int b_kpend_tmp;
            kpstart = varargin_2->colidx[ccol];
            b_kpend_tmp = varargin_2->colidx[ccol + 1];
            kpend = b_kpend_tmp - 1;
            for (int b_kp{kpstart}; b_kp <= kpend; b_kp++) {
                int i3;
                i3 = ((nzCount + b_kp) - kpstart) + 1;
                c->rowidx[i3] = varargin_2->rowidx[b_kp - 1] + crowoffs;
                c->d[i3] = varargin_2->d[b_kp - 1];
            }
            nzCount = (nzCount + b_kpend_tmp) - varargin_2->colidx[ccol];
        }
        c->colidx[ccol + 1] = nzCount + 2;
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for sparse1.cpp
//
// [EOF]
//
