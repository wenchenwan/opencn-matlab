//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_simplex.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "c_simplex.h"
#include "sparse1.h"
#include "coder_array.h"
#include "cpp_simplex.hpp"
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &f
//                const coder::sparse *A
//                ::coder::array<double, 2U> &b
//                const ::coder::array<double, 2U> &Aeq
//                const ::coder::array<double, 2U> &beq
//                ::coder::array<double, 2U> &C
//                bool *success
//                int *status
// Return Type  : void
//
namespace ocn {
void c_simplex(const ::coder::array<double, 2U> &f, const coder::sparse *A,
               ::coder::array<double, 2U> &b, const ::coder::array<double, 2U> &Aeq,
               const ::coder::array<double, 2U> &beq, ::coder::array<double, 2U> &C, bool *success,
               int *status)
{
    coder::sparse Atot;
    ::coder::array<double, 1U> v;
    ::coder::array<int, 1U> Ais;
    ::coder::array<int, 1U> Ajs;
    ::coder::array<int, 1U> i_tmp;
    ::coder::array<int, 1U> j;
    int Asize[2];
    int Csize[2];
    int beqsize[2];
    int bsize[2];
    int fsize[2];
    int b_n;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int cnfixeddim;
    int cnnz;
    int cnvardim;
    int d_loop_ub;
    int i11;
    int i2;
    int i6;
    int i9;
    int loop_ub;
    int numalloc;
    int nx;
    int nzCount;
    int scalarLB;
    int vectorUB;
    bool allEmpty;
    bool emptyflag_idx_0;
    bool emptyflag_idx_1;
    bool isAcceptableEmpty;
    bool isAcceptableEmpty_tmp;
    cnfixeddim = A->n;
    if ((A->m == 0) || (A->n == 0)) {
        isAcceptableEmpty_tmp = true;
    } else {
        isAcceptableEmpty_tmp = false;
    }
    isAcceptableEmpty = (Aeq.size(1) == 0);
    allEmpty = (isAcceptableEmpty_tmp && isAcceptableEmpty);
    if ((!isAcceptableEmpty) && isAcceptableEmpty_tmp) {
        cnfixeddim = Aeq.size(1);
    }
    cnnz = 0;
    cnvardim = 0;
    if (allEmpty || (!isAcceptableEmpty_tmp)) {
        cnnz = A->colidx[A->colidx.size(0) - 1] - 1;
        cnvardim = A->m;
    }
    if (allEmpty || (Aeq.size(1) != 0)) {
        int i;
        int n;
        n = 0;
        i = Aeq.size(0) * Aeq.size(1);
        for (int k{0}; k < i; k++) {
            if (Aeq[k] != 0.0) {
                n++;
            }
        }
        cnnz += n;
        cnvardim += Aeq.size(0);
    }
    if (cnnz >= 1) {
        numalloc = cnnz;
    } else {
        numalloc = 1;
    }
    Atot.d.set_size(numalloc);
    Atot.colidx.set_size(cnfixeddim + 1);
    Atot.colidx[0] = 1;
    Atot.rowidx.set_size(numalloc);
    for (int i1{0}; i1 < numalloc; i1++) {
        Atot.d[i1] = 0.0;
        Atot.rowidx[i1] = 0;
    }
    for (int c{0}; c < cnfixeddim; c++) {
        Atot.colidx[c + 1] = 1;
    }
    i2 = Atot.colidx.size(0);
    for (int b_c{0}; b_c <= i2 - 2; b_c++) {
        Atot.colidx[b_c] = 1;
    }
    Atot.colidx[Atot.colidx.size(0) - 1] = 1;
    nzCount = -1;
    if ((A->m == 0) || (A->n == 0)) {
        emptyflag_idx_0 = true;
    } else {
        emptyflag_idx_0 = false;
    }
    emptyflag_idx_1 = (Aeq.size(1) == 0);
    for (int ccol{0}; ccol < cnfixeddim; ccol++) {
        int crowoffs;
        crowoffs = 1;
        if (!emptyflag_idx_0) {
            int kpend;
            int kpend_tmp;
            int kpstart;
            kpstart = A->colidx[ccol];
            kpend_tmp = A->colidx[ccol + 1];
            kpend = kpend_tmp - 1;
            for (int kp{kpstart}; kp <= kpend; kp++) {
                int i5;
                i5 = ((nzCount + kp) - kpstart) + 1;
                Atot.rowidx[i5] = A->rowidx[kp - 1];
                Atot.d[i5] = A->d[kp - 1];
            }
            nzCount = (nzCount + kpend_tmp) - A->colidx[ccol];
            crowoffs = A->m + 1;
        }
        if (!emptyflag_idx_1) {
            int cidx;
            int nrowk;
            nrowk = Aeq.size(0);
            cidx = nzCount;
            for (int row{0}; row < nrowk; row++) {
                double dk;
                dk = Aeq[row + Aeq.size(0) * ccol];
                if (dk != 0.0) {
                    cidx++;
                    Atot.rowidx[cidx] = row + crowoffs;
                    Atot.d[cidx] = dk;
                }
            }
            nzCount = cidx;
        }
        Atot.colidx[ccol + 1] = nzCount + 2;
    }
    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    C.set_size(f.size(0), f.size(1));
    loop_ub = f.size(1);
    for (int i3{0}; i3 < loop_ub; i3++) {
        int b_loop_ub;
        b_loop_ub = f.size(0);
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            C[i4 + C.size(0) * i3] = 0.0;
        }
    }
    nx = Atot.colidx[Atot.colidx.size(0) - 1] - 2;
    if (Atot.colidx[Atot.colidx.size(0) - 1] - 1 == 0) {
        i_tmp.set_size(0);
        j.set_size(0);
        v.set_size(0);
    } else {
        int b_idx;
        int col;
        i_tmp.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        j.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        v.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        for (int idx{0}; idx <= nx; idx++) {
            i_tmp[idx] = Atot.rowidx[idx];
            v[idx] = Atot.d[idx];
        }
        b_idx = 0;
        col = 1;
        while (b_idx < nx + 1) {
            if (b_idx == Atot.colidx[col] - 1) {
                col++;
            } else {
                b_idx++;
                j[b_idx - 1] = col;
            }
        }
        if (Atot.colidx[Atot.colidx.size(0) - 1] - 1 == 1) {
            if (b_idx == 0) {
                i_tmp.set_size(0);
                j.set_size(0);
                v.set_size(0);
            }
        } else {
            int i10;
            int i7;
            int i8;
            if (1 > b_idx) {
                i7 = 0;
            } else {
                i7 = b_idx;
            }
            i_tmp.set_size(i7);
            if (1 > b_idx) {
                i8 = 0;
            } else {
                i8 = b_idx;
            }
            j.set_size(i8);
            if (1 > b_idx) {
                i10 = 0;
            } else {
                i10 = b_idx;
            }
            v.set_size(i10);
        }
    }
    Ais.set_size(i_tmp.size(0));
    c_loop_ub = i_tmp.size(0);
    scalarLB = (i_tmp.size(0) / 4) << 2;
    vectorUB = scalarLB - 4;
    for (i6 = 0; i6 <= vectorUB; i6 += 4) {
        __m128i r;
        r = _mm_loadu_si128((const __m128i *)&i_tmp[i6]);
        _mm_storeu_si128((__m128i *)&Ais[i6], _mm_sub_epi32(r, _mm_set1_epi32(1)));
    }
    for (i6 = scalarLB; i6 < c_loop_ub; i6++) {
        Ais[i6] = i_tmp[i6] - 1;
    }
    Ajs.set_size(j.size(0));
    d_loop_ub = j.size(0);
    b_scalarLB = (j.size(0) / 4) << 2;
    b_vectorUB = b_scalarLB - 4;
    for (i9 = 0; i9 <= b_vectorUB; i9 += 4) {
        __m128i r1;
        r1 = _mm_loadu_si128((const __m128i *)&j[i9]);
        _mm_storeu_si128((__m128i *)&Ajs[i9], _mm_sub_epi32(r1, _mm_set1_epi32(1)));
    }
    for (i9 = b_scalarLB; i9 < d_loop_ub; i9++) {
        Ajs[i9] = j[i9] - 1;
    }
    fsize[0] = f.size(0);
    fsize[1] = f.size(1);
    Asize[0] = cnvardim;
    Asize[1] = cnfixeddim;
    b_n = 0;
    i11 = v.size(0);
    for (int b_k{0}; b_k < i11; b_k++) {
        if (v[b_k] != 0.0) {
            b_n++;
        }
    }
    int b_status;
    bsize[0] = b.size(0);
    beqsize[0] = beq.size(0);
    bsize[1] = 1;
    beqsize[1] = 1;
    Csize[0] = f.size(0);
    Csize[1] = f.size(1);
    b_status =
        simplex_solve(&f[0], &fsize[0], &(v.data())[0], &(Ais.data())[0], &(Ajs.data())[0],
                      &Asize[0], b_n, &b[0], &bsize[0], &beq[0], &beqsize[0], &C[0], &Csize[0]);
    //          C = solution.solution;
    *success = (b_status == 0);
    *status = b_status;
}

} // namespace ocn

//
// File trailer for c_simplex.cpp
//
// [EOF]
//
