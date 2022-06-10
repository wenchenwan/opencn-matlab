//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &varargin_2
//                sparse *c
// Return Type  : void
//
namespace ocn {
namespace coder {
void sparse::vertcat(const ::coder::array<double, 2U> &varargin_2, sparse *c) const
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

} // namespace coder
} // namespace ocn

//
// File trailer for sparse1.cpp
//
// [EOF]
//
