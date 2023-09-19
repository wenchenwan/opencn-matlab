//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_simplex.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "c_simplex.h"
#include "sparse1.h"
#include "coder_array.h"
#include "cpp_simplex.hpp"
#include <emmintrin.h>

// Function Definitions
//
// function [C, success, status, msg] = c_simplex(f, A, b, Aeq, beq, ctx)
//
// Arguments    : const ::coder::array<double, 1U> &f
//                const coder::sparse *A
//                const ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &Aeq
//                const ::coder::array<double, 1U> &beq
//                ::coder::array<double, 2U> &C
//                bool *success
//                int *status
// Return Type  : void
//
namespace ocn {
void c_simplex(const ::coder::array<double, 1U> &f, const coder::sparse *A,
               const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
               const ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &C, bool *success,
               int *status)
{
    coder::sparse Atot;
    ::coder::array<double, 1U> Avs;
    ::coder::array<int, 1U> Ais;
    ::coder::array<int, 1U> Ajs;
    ::coder::array<int, 1U> b_i;
    ::coder::array<int, 1U> jj;
    int Asize[2];
    int fsize[2];
    int b_loop_ub;
    int b_n;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int cnfixeddim;
    int cnnz;
    int cnvardim;
    int i2;
    int i7;
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
    // 'c_simplex:2' msg = "";
    // 'c_simplex:3' if coder.target('rtw') || coder.target('mex')
    // 'c_simplex:4' c_prof_in(mfilename);
    // 'c_simplex:5' c_prof_in('join_A');
    // 'c_simplex:6' Atot = [A; Aeq];
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
                int i4;
                i4 = ((nzCount + kp) - kpstart) + 1;
                Atot.rowidx[i4] = A->rowidx[kp - 1];
                Atot.d[i4] = A->d[kp - 1];
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
    // 'c_simplex:7' c_prof_out('join_A');
    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    // 'c_simplex:9' [NCoeff, NHorz] = size(f);
    // 'c_simplex:10' C = zeros(NCoeff, NHorz);
    C.set_size(f.size(0), 1);
    loop_ub = f.size(0);
    for (int i3{0}; i3 < loop_ub; i3++) {
        C[i3] = 0.0;
    }
    // 'c_simplex:11' coder.varsize('C', [Inf, Inf], [1,1]);
    // 'c_simplex:13' [Aisd, Ajsd, Avs] = find(Atot);
    nx = Atot.colidx[Atot.colidx.size(0) - 1] - 2;
    if (Atot.colidx[Atot.colidx.size(0) - 1] - 1 == 0) {
        b_i.set_size(0);
        jj.set_size(0);
        Avs.set_size(0);
    } else {
        int b_idx;
        int col;
        b_i.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        jj.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        Avs.set_size(Atot.colidx[Atot.colidx.size(0) - 1] - 1);
        for (int idx{0}; idx <= nx; idx++) {
            b_i[idx] = Atot.rowidx[idx];
            Avs[idx] = Atot.d[idx];
        }
        b_idx = 0;
        col = 1;
        while (b_idx < nx + 1) {
            if (b_idx == Atot.colidx[col] - 1) {
                col++;
            } else {
                b_idx++;
                jj[b_idx - 1] = col;
            }
        }
        if (Atot.colidx[Atot.colidx.size(0) - 1] - 1 == 1) {
            if (b_idx == 0) {
                b_i.set_size(0);
                jj.set_size(0);
                Avs.set_size(0);
            }
        } else {
            int c_idx;
            int d_idx;
            int e_idx;
            if (b_idx < 1) {
                c_idx = 0;
            } else {
                c_idx = b_idx;
            }
            b_i.set_size(c_idx);
            if (b_idx < 1) {
                d_idx = 0;
            } else {
                d_idx = b_idx;
            }
            jj.set_size(d_idx);
            if (b_idx < 1) {
                e_idx = 0;
            } else {
                e_idx = b_idx;
            }
            Avs.set_size(e_idx);
        }
    }
    // 'c_simplex:14' Ais = int32(Aisd)-1;
    Ais.set_size(b_i.size(0));
    b_loop_ub = b_i.size(0);
    scalarLB = (b_i.size(0) / 4) << 2;
    vectorUB = scalarLB - 4;
    for (int i5{0}; i5 <= vectorUB; i5 += 4) {
        __m128i r;
        r = _mm_loadu_si128((const __m128i *)&b_i[i5]);
        _mm_storeu_si128((__m128i *)&Ais[i5], _mm_sub_epi32(r, _mm_set1_epi32(1)));
    }
    for (int i5{scalarLB}; i5 < b_loop_ub; i5++) {
        Ais[i5] = b_i[i5] - 1;
    }
    // 'c_simplex:15' Ajs = int32(Ajsd)-1;
    Ajs.set_size(jj.size(0));
    c_loop_ub = jj.size(0);
    b_scalarLB = (jj.size(0) / 4) << 2;
    b_vectorUB = b_scalarLB - 4;
    for (int i6{0}; i6 <= b_vectorUB; i6 += 4) {
        __m128i r1;
        r1 = _mm_loadu_si128((const __m128i *)&jj[i6]);
        _mm_storeu_si128((__m128i *)&Ajs[i6], _mm_sub_epi32(r1, _mm_set1_epi32(1)));
    }
    for (int i6{b_scalarLB}; i6 < c_loop_ub; i6++) {
        Ajs[i6] = jj[i6] - 1;
    }
    // 'c_simplex:17' coder.varsize('Avs', [Inf, 1], [1, 0]);
    // 'c_simplex:18' coder.varsize('Ais', [Inf, 1], [1, 0]);
    // 'c_simplex:19' coder.varsize('Ajs', [Inf, 1], [1, 0]);
    // 'c_simplex:21' fsize = int32(size(f));
    fsize[0] = f.size(0);
    fsize[1] = 1;
    // 'c_simplex:22' Asize = int32(size(Atot));
    Asize[0] = cnvardim;
    Asize[1] = cnfixeddim;
    // 'c_simplex:23' An = int32(nnz(Avs));
    b_n = 0;
    i7 = Avs.size(0);
    for (int b_k{0}; b_k < i7; b_k++) {
        if (Avs[b_k] != 0.0) {
            b_n++;
        }
    }
    int Csize[2];
    int beqsize[2];
    int bsize[2];
    int b_status;
    // 'c_simplex:24' bsize = int32(size(b));
    bsize[0] = b.size(0);
    bsize[1] = 1;
    // 'c_simplex:25' beqsize = int32(size(beq));
    beqsize[0] = beq.size(0);
    beqsize[1] = 1;
    // 'c_simplex:26' Csize = int32(size(C));
    Csize[0] = f.size(0);
    Csize[1] = 1;
    // 'c_simplex:27' success = int32(0);
    // 'c_simplex:28' status = int32(0);
    // 'c_simplex:30' my_path = StructTypeName.WDIR + "/src";
    // 'c_simplex:31' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'c_simplex:32' coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp', my_path);
    // 'c_simplex:33' coder.updateBuildInfo('addLinkFlags', LibInfo.clp.lflags );
    // 'c_simplex:34' coder.cinclude('cpp_simplex.hpp');
    // 'c_simplex:36' status = coder.ceval('simplex_solve', coder.rref(f), fsize,...
    // 'c_simplex:37'         coder.rref(Avs), coder.rref(Ais), coder.rref(Ajs), Asize, An,...
    // 'c_simplex:38'         coder.rref(b), bsize, coder.rref(beq),beqsize,...
    // 'c_simplex:39'         coder.ref(C), Csize);
    b_status = simplex_solve(&(((::coder::array<double, 1U> *)&f)->data())[0], &fsize[0],
                             &(Avs.data())[0], &(Ais.data())[0], &(Ajs.data())[0], &Asize[0], b_n,
                             &(((::coder::array<double, 1U> *)&b)->data())[0], &bsize[0],
                             &(((::coder::array<double, 1U> *)&beq)->data())[0], &beqsize[0], &C[0],
                             &Csize[0]);
    //          C = solution.solution;
    // 'c_simplex:41' success = status == 0;
    //  Status :
    //        0 : Primal Dual Optimality
    //        1 : Primal Infeasible
    //        2 : Dual Infeasible
    //        3 : Max iteration reached
    //        4 : isAbandoned
    // 'c_simplex:48' c_prof_out(mfilename);
    *success = (b_status == 0);
    *status = b_status;
}

} // namespace ocn

//
// File trailer for c_simplex.cpp
//
// [EOF]
//
