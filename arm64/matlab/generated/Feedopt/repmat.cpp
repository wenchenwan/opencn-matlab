//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:29:48
//

// Include Files
#include "repmat.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                int varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace ocn {
namespace coder {
void repmat(const ::coder::array<double, 1U> &a, int varargin_2, ::coder::array<double, 2U> &b)
{
    ::coder::array<double, 2U> b_b;
    b.set_size(a.size(0), varargin_2);
    if ((a.size(0) != 0) && (varargin_2 != 0)) {
        int b_loop_ub;
        int i1;
        b_b.set_size(a.size(0), varargin_2);
        for (int i{0}; i < varargin_2; i++) {
            int loop_ub;
            loop_ub = b.size(0);
            for (int i2{0}; i2 < loop_ub; i2++) {
                b_b[i2 + b_b.size(0) * i] = b[i2 + b.size(0) * i];
            }
        }
        i1 = varargin_2 - 1;
        for (int t{0}; t <= i1; t++) {
            int na;
            na = a.size(0);
            for (int k{0}; k < na; k++) {
                b_b[k + b_b.size(0) * t] = a[k];
            }
        }
        b.set_size(b_b.size(0), b_b.size(1));
        b_loop_ub = b_b.size(1);
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            int c_loop_ub;
            c_loop_ub = b_b.size(0);
            for (int i4{0}; i4 < c_loop_ub; i4++) {
                b[i4 + b.size(0) * i3] = b_b[i4 + b_b.size(0) * i3];
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &a
//                double varargin_1
//                double varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
void repmat(const ::coder::array<double, 2U> &a, double varargin_1, double varargin_2,
            ::coder::array<double, 2U> &b)
{
    b.set_size(static_cast<int>(varargin_1), a.size(1) * static_cast<int>(varargin_2));
    if ((static_cast<int>(varargin_1) != 0) && (a.size(1) * static_cast<int>(varargin_2) != 0)) {
        int i;
        int na;
        na = a.size(1);
        i = static_cast<int>(varargin_2) - 1;
        for (int t{0}; t <= i; t++) {
            int i1;
            int offset;
            offset = t * na;
            i1 = static_cast<int>(varargin_1) - 1;
            for (int k{0}; k < na; k++) {
                for (int b_t{0}; b_t <= i1; b_t++) {
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
