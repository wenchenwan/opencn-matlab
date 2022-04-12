//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:49:22
//

// Include Files
#include "mtimes.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const double A[3]
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
namespace ocn {
namespace coder {
namespace internal {
namespace blas {
void mtimes(const double A[3], const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C)
{
    int n;
    n = B.size(1);
    C.set_size(1, B.size(1));
    for (int j{0}; j < n; j++) {
        C[j] = (A[0] * B[3 * j] + A[1] * B[3 * j + 1]) + A[2] * B[3 * j + 2];
    }
}

} // namespace blas
} // namespace internal
} // namespace coder
} // namespace ocn

//
// File trailer for mtimes.cpp
//
// [EOF]
//
