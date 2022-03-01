//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 10:58:42
//

// Include Files
#include "sparse1.h"
#include "coder_array.h"
#include <cstddef>
#include <cstring>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
//                const ::coder::array<double, 2U> &varargin_2
// Return Type  : void
//
namespace ocn {
namespace coder {
void sparse::parenAssign(const ::coder::array<double, 2U> &rhs,
                         const ::coder::array<double, 2U> &varargin_1,
                         const ::coder::array<double, 2U> &varargin_2)
{
    ::coder::array<double, 1U> dt;
    ::coder::array<int, 1U> x_tmp;
    int rhsIter_idx;
    int sm;
    int sn;
    sm = varargin_1.size(1);
    sn = varargin_2.size(1);
    rhsIter_idx = 0;
    for (int cidx{0}; cidx < sn; cidx++) {
        double b_d;
        b_d = varargin_2[cidx];
        for (int ridx{0}; ridx < sm; ridx++) {
            double nt;
            double rhsv;
            double thisv;
            int i1;
            int i2;
            int loop_ub;
            int vidx;
            bool found;
            nt = varargin_1[ridx];
            x_tmp.set_size(rowidx.size(0));
            loop_ub = rowidx.size(0);
            for (int i{0}; i < loop_ub; i++) {
                x_tmp[i] = rowidx[i];
            }
            i1 = colidx[static_cast<int>(b_d) - 1];
            i2 = colidx[static_cast<int>(b_d)];
            if (i1 < i2) {
                if (static_cast<int>(nt) < rowidx[i1 - 1]) {
                    vidx = i1 - 1;
                    found = false;
                } else {
                    int high_i;
                    int low_i;
                    int low_ip1;
                    high_i = i2;
                    low_i = i1;
                    low_ip1 = colidx[static_cast<int>(b_d) - 1];
                    while (high_i > low_ip1 + 1) {
                        int mid_i;
                        mid_i = (low_i >> 1) + (high_i >> 1);
                        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                            mid_i++;
                        }
                        if (static_cast<int>(nt) >= rowidx[mid_i - 1]) {
                            low_i = mid_i;
                            low_ip1 = mid_i;
                        } else {
                            high_i = mid_i;
                        }
                    }
                    vidx = low_i;
                    found = (rowidx[low_i - 1] == static_cast<int>(nt));
                }
            } else if (i1 == i2) {
                vidx = colidx[static_cast<int>(b_d) - 1] - 1;
                found = false;
            } else {
                vidx = 0;
                found = false;
            }
            if (found) {
                thisv = d[vidx - 1];
            } else {
                thisv = 0.0;
            }
            rhsv = rhs[rhsIter_idx];
            rhsIter_idx++;
            if ((thisv != 0.0) || (rhsv != 0.0)) {
                int nz;
                nz = colidx[colidx.size(0) - 1] - 1;
                if ((thisv != 0.0) && (rhsv != 0.0)) {
                    d[vidx - 1] = rhsv;
                } else if (thisv == 0.0) {
                    int i6;
                    int i7;
                    int idx;
                    idx = vidx + 1;
                    if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
                        int b_loop_ub;
                        int highOrderA;
                        int highOrderB;
                        int lowOrderB;
                        int numAlloc;
                        int overflow;
                        int partialResults_idx_0_tmp;
                        int partialResults_idx_1;
                        int tmp;
                        dt.set_size(d.size(0));
                        b_loop_ub = d.size(0);
                        for (int i5{0}; i5 < b_loop_ub; i5++) {
                            dt[i5] = d[i5];
                        }
                        int lowOrderA;
                        highOrderA = m >> 16;
                        lowOrderA = m & 65535;
                        highOrderB = n >> 16;
                        lowOrderB = n & 65535;
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
                                    if (partialResults_idx_0_tmp >
                                        MAX_int32_T - partialResults_idx_1) {
                                        a__4 = (partialResults_idx_0_tmp + partialResults_idx_1) -
                                               MAX_int32_T;
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
                            int b_u1;
                            int u0;
                            int y;
                            u0 = colidx[colidx.size(0) - 1] + 9;
                            b_u1 = m * n;
                            if (u0 <= b_u1) {
                                y = u0;
                            } else {
                                y = b_u1;
                            }
                            if (1 >= y) {
                                numAlloc = 1;
                            } else {
                                numAlloc = y;
                            }
                        } else {
                            int u1;
                            u1 = colidx[colidx.size(0) - 1] + 9;
                            if (1 >= u1) {
                                numAlloc = 1;
                            } else {
                                numAlloc = u1;
                            }
                        }
                        rowidx.set_size(numAlloc);
                        for (int i8{0}; i8 < numAlloc; i8++) {
                            rowidx[i8] = 0;
                        }
                        d.set_size(numAlloc);
                        for (int i9{0}; i9 < numAlloc; i9++) {
                            d[i9] = 0.0;
                        }
                        maxnz = numAlloc;
                        for (int c_k{0}; c_k < vidx; c_k++) {
                            rowidx[c_k] = x_tmp[c_k];
                            d[c_k] = dt[c_k];
                        }
                        for (int d_k{idx}; d_k <= nz; d_k++) {
                            rowidx[d_k] = x_tmp[d_k - 1];
                            d[d_k] = dt[d_k - 1];
                        }
                        rowidx[vidx] = static_cast<int>(nt);
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
                        rowidx[vidx] = static_cast<int>(nt);
                    }
                    i6 = static_cast<int>(b_d) + 1;
                    i7 = n + 1;
                    for (int b_k{i6}; b_k <= i7; b_k++) {
                        colidx[b_k - 1] = colidx[b_k - 1] + 1;
                    }
                } else {
                    int i3;
                    int i4;
                    int nelem;
                    nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                    if (nelem > 0) {
                        std::memmove((void *)&rowidx[vidx - 1], (void *)&rowidx[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(int)));
                        std::memmove((void *)&d[vidx - 1], (void *)&d[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(double)));
                    }
                    i3 = static_cast<int>(b_d) + 1;
                    i4 = n + 1;
                    for (int k{i3}; k <= i4; k++) {
                        colidx[k - 1] = colidx[k - 1] - 1;
                    }
                }
            }
        }
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
