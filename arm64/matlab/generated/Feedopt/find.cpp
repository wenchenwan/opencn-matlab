//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "find.h"
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const bool x_data[]
//                int x_size
//                int i_data[]
//                int *i_size
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_eml_find(const bool x_data[], int x_size, int i_data[], int *i_size)
{
    int idx;
    int ii;
    bool exitg1;
    idx = 0;
    *i_size = x_size;
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= x_size - 1)) {
        if (x_data[ii]) {
            idx++;
            i_data[idx - 1] = ii + 1;
            if (idx >= x_size) {
                exitg1 = true;
            } else {
                ii++;
            }
        } else {
            ii++;
        }
    }
    if (x_size == 1) {
        if (idx == 0) {
            *i_size = 0;
        }
    } else if (1 > idx) {
        *i_size = 0;
    } else {
        *i_size = idx;
    }
}

//
// Arguments    : const sparse *x
//                ::coder::array<int, 1U> &i
//                ::coder::array<int, 1U> &j
//                ::coder::array<double, 1U> &v
// Return Type  : void
//
void c_eml_find(const sparse *x, ::coder::array<int, 1U> &i, ::coder::array<int, 1U> &j,
                ::coder::array<double, 1U> &v)
{
    int nx;
    nx = x->colidx[x->colidx.size(0) - 1] - 2;
    if (x->colidx[x->colidx.size(0) - 1] - 1 == 0) {
        i.set_size(0);
        j.set_size(0);
        v.set_size(0);
    } else {
        int b_idx;
        int col;
        i.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
        j.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
        v.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
        for (int idx{0}; idx <= nx; idx++) {
            i[idx] = x->rowidx[idx];
            v[idx] = x->d[idx];
        }
        b_idx = 0;
        col = 1;
        while (b_idx < nx + 1) {
            if (b_idx == x->colidx[col] - 1) {
                col++;
            } else {
                b_idx++;
                j[b_idx - 1] = col;
            }
        }
        if (x->colidx[x->colidx.size(0) - 1] - 1 == 1) {
            if (b_idx == 0) {
                i.set_size(0);
                j.set_size(0);
                v.set_size(0);
            }
        } else {
            int b_i;
            int i1;
            int i2;
            if (1 > b_idx) {
                b_i = 0;
            } else {
                b_i = b_idx;
            }
            i.set_size(b_i);
            if (1 > b_idx) {
                i1 = 0;
            } else {
                i1 = b_idx;
            }
            j.set_size(i1);
            if (1 > b_idx) {
                i2 = 0;
            } else {
                i2 = b_idx;
            }
            v.set_size(i2);
        }
    }
}

//
// Arguments    : const ::coder::array<bool, 2U> &x
//                ::coder::array<int, 2U> &i
// Return Type  : void
//
void eml_find(const ::coder::array<bool, 2U> &x, ::coder::array<int, 2U> &i)
{
    int idx;
    int ii;
    int nx;
    bool exitg1;
    nx = x.size(1);
    idx = 0;
    i.set_size(1, x.size(1));
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= nx - 1)) {
        if (x[ii]) {
            idx++;
            i[idx - 1] = ii + 1;
            if (idx >= nx) {
                exitg1 = true;
            } else {
                ii++;
            }
        } else {
            ii++;
        }
    }
    if (x.size(1) == 1) {
        if (idx == 0) {
            i.set_size(1, 0);
        }
    } else {
        int b_i;
        if (1 > idx) {
            b_i = 0;
        } else {
            b_i = idx;
        }
        i.set_size(i.size(0), b_i);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for find.cpp
//
// [EOF]
//
