//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 15:51:08
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
    int idx;
    int ii;
    int k;
    bool exitg1;
    k = (1 <= x.size(1));
    idx = 0;
    i_size[0] = 1;
    i_size[1] = k;
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= x.size(1) - 1)) {
        if (x[ii]) {
            idx = 1;
            i_data[0] = ii + 1;
            exitg1 = true;
        } else {
            ii++;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i_size[0] = 1;
            i_size[1] = 0;
        }
    } else {
        i_size[1] = (1 <= idx);
    }
}

//
// Arguments    : const bool x_data[]
//                int x_size
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void c_eml_find(const bool x_data[], int x_size, int i_data[], int *i_size)
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
    k = (1 <= x.size(1));
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
        i_size[1] = (1 <= idx);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for find.cpp
//
// [EOF]
//
