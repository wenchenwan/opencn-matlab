//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

// Include Files
#include "repmat.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const double a[7]
//                double varargin_1
//                double varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace ocn {
namespace coder {
void repmat(const double a[7], double varargin_1, double varargin_2, ::coder::array<double, 2U> &b)
{
    int i;
    i = 7 * static_cast<int>(varargin_2);
    b.set_size(static_cast<int>(varargin_1), i);
    if ((static_cast<int>(varargin_1) != 0) && (i != 0)) {
        int i1;
        i1 = static_cast<int>(varargin_2) - 1;
        for (int t{0}; t <= i1; t++) {
            int i2;
            int offset;
            offset = t * 7;
            i2 = static_cast<int>(varargin_1) - 1;
            for (int k{0}; k < 7; k++) {
                for (int b_t{0}; b_t <= i2; b_t++) {
                    b[b_t + b.size(0) * (offset + k)] = a[k];
                }
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for repmat.cpp
//
// [EOF]
//
