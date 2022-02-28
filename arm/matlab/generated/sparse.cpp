//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:00:32
//

// Include Files
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : double varargin_1
//                double varargin_2
//                sparse *y
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_sparse(double varargin_1, double varargin_2, sparse *y)
{
    int loop_ub_tmp;
    y->m = static_cast<int>(varargin_1);
    y->n = static_cast<int>(varargin_2);
    y->d.set_size(1);
    y->d[0] = 0.0;
    loop_ub_tmp = static_cast<int>(varargin_2) + 1;
    y->colidx.set_size(loop_ub_tmp);
    for (int i{0}; i < loop_ub_tmp; i++) {
        y->colidx[i] = 1;
    }
    y->rowidx.set_size(1);
    y->rowidx[0] = 1;
    y->maxnz = 1;
}

} // namespace coder
} // namespace ocn

//
// File trailer for sparse.cpp
//
// [EOF]
//
