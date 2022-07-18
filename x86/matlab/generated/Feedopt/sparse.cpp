//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
//                sparse *y
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_sparse(const ::coder::array<double, 2U> &varargin_1, sparse *y)
{
    int ctr;
    int i;
    int loop_ub;
    int mInt;
    int n;
    int nInt;
    int numalloc;
    mInt = varargin_1.size(0);
    nInt = varargin_1.size(1);
    n = 0;
    i = varargin_1.size(0) * varargin_1.size(1);
    for (int k{0}; k < i; k++) {
        if (varargin_1[k] != 0.0) {
            n++;
        }
    }
    y->m = varargin_1.size(0);
    y->n = varargin_1.size(1);
    if (n >= 1) {
        numalloc = n;
    } else {
        numalloc = 1;
    }
    y->d.set_size(numalloc);
    for (int i1{0}; i1 < numalloc; i1++) {
        y->d[i1] = 0.0;
    }
    y->colidx.set_size(varargin_1.size(1) + 1);
    loop_ub = varargin_1.size(1) + 1;
    for (int i2{0}; i2 < loop_ub; i2++) {
        y->colidx[i2] = 0;
    }
    y->colidx[0] = 1;
    y->rowidx.set_size(numalloc);
    for (int i3{0}; i3 < numalloc; i3++) {
        y->rowidx[i3] = 0;
    }
    y->rowidx[0] = 1;
    ctr = 0;
    for (int col{0}; col < nInt; col++) {
        for (int row{0}; row < mInt; row++) {
            double xrc;
            xrc = varargin_1[row + varargin_1.size(0) * col];
            if (xrc != 0.0) {
                y->rowidx[ctr] = row + 1;
                y->d[ctr] = xrc;
                ctr++;
            }
        }
        y->colidx[col + 1] = ctr + 1;
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for sparse.cpp
//
// [EOF]
//
