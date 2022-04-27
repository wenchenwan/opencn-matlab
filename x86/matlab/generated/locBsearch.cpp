//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
//

// Include Files
#include "locBsearch.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<int, 1U> &x
//                int xi
//                int xstart
//                int xend
//                int *n
//                bool *found
// Return Type  : void
//
namespace ocn {
namespace coder {
void sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart, int xend, int *n,
                       bool *found)
{
    if (xstart < xend) {
        if (xi < x[xstart - 1]) {
            *n = xstart - 1;
            *found = false;
        } else {
            int high_i;
            int low_i;
            int low_ip1;
            high_i = xend;
            low_i = xstart;
            low_ip1 = xstart;
            while (high_i > low_ip1 + 1) {
                int mid_i;
                mid_i = (low_i >> 1) + (high_i >> 1);
                if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                    mid_i++;
                }
                if (xi >= x[mid_i - 1]) {
                    low_i = mid_i;
                    low_ip1 = mid_i;
                } else {
                    high_i = mid_i;
                }
            }
            *n = low_i;
            *found = (x[low_i - 1] == xi);
        }
    } else if (xstart == xend) {
        *n = xstart - 1;
        *found = false;
    } else {
        *n = 0;
        *found = false;
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for locBsearch.cpp
//
// [EOF]
//
