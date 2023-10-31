
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "find.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<bool, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
namespace ocn {
namespace coder {
void b_eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
{
    ::coder::array<int, 2U> i;
    int idx;
    int ii;
    int k;
    int loop_ub;
    bool exitg1;
    k = (x.size(1) >= 1);
    idx = 0;
    i.set_size(1, k);
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= x.size(1) - 1)) {
        if (x[ii]) {
            idx++;
            i[idx - 1] = ii + 1;
            if (idx >= k) {
                exitg1 = true;
            } else {
                ii++;
            }
        } else {
            ii++;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i.set_size(1, 0);
        }
    } else {
        i.set_size(i.size(0), static_cast<int>(idx >= 1));
    }
    i_size[0] = 1;
    i_size[1] = i.size(1);
    loop_ub = i.size(1);
    if (loop_ub - 1 >= 0) {
        i_data[0] = i[0];
    }
}

//
// Arguments    : const ::coder::array<bool, 1U> &x
//                ::coder::array<int, 1U> &i
// Return Type  : void
//
void c_eml_find(const ::coder::array<bool, 1U> &x, ::coder::array<int, 1U> &i)
{
    int idx;
    int ii;
    int nx;
    bool exitg1;
    nx = x.size(0);
    idx = 0;
    i.set_size(x.size(0));
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
    if (x.size(0) == 1) {
        if (idx == 0) {
            i.set_size(0);
        }
    } else {
        int b_idx;
        if (idx < 1) {
            b_idx = 0;
        } else {
            b_idx = idx;
        }
        i.set_size(b_idx);
    }
}

//
// Arguments    : const ::coder::array<bool, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
void eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
{
    int idx;
    int ii;
    int k;
    bool exitg1;
    k = (x.size(1) >= 1);
    ii = x.size(1);
    idx = 0;
    i_size[0] = 1;
    i_size[1] = k;
    exitg1 = false;
    while ((!exitg1) && (ii > 0)) {
        if (x[ii - 1]) {
            idx = 1;
            i_data[0] = ii;
            exitg1 = true;
        } else {
            ii--;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i_size[0] = 1;
            i_size[1] = 0;
        }
    } else {
        i_size[1] = (idx >= 1);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for find.cpp
//
// [EOF]
//
