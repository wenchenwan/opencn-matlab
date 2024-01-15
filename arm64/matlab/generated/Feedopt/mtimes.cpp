
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "mtimes.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
namespace ocn {
namespace coder {
namespace internal {
namespace blas {
void b_mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &C)
{
    int inner;
    int nc;
    inner = A.size(1);
    nc = B.size(1);
    C.set_size(2, B.size(1));
    for (int j{0}; j < nc; j++) {
        C[2 * j] = 0.0;
        C[2 * j + 1] = 0.0;
        for (int k{0}; k < inner; k++) {
            double bkj;
            bkj = B[k + B.size(0) * j];
            C[2 * j] = C[2 * j] + A[2 * k] * bkj;
            C[2 * j + 1] = C[2 * j + 1] + A[2 * k + 1] * bkj;
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
            ::coder::array<double, 2U> &C)
{
    int inner;
    int mc;
    int nc;
    mc = A.size(0) - 1;
    inner = A.size(1);
    nc = B.size(1);
    C.set_size(A.size(0), B.size(1));
    for (int j{0}; j < nc; j++) {
        for (int i{0}; i <= mc; i++) {
            C[i + C.size(0) * j] = 0.0;
        }
        for (int k{0}; k < inner; k++) {
            double bkj;
            bkj = B[k + B.size(0) * j];
            for (int b_i{0}; b_i <= mc; b_i++) {
                C[b_i + C.size(0) * j] = C[b_i + C.size(0) * j] + A[b_i + A.size(0) * k] * bkj;
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &B
//                double C[2]
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B, double C[2])
{
    int inner;
    inner = A.size(1);
    C[0] = 0.0;
    C[1] = 0.0;
    for (int k{0}; k < inner; k++) {
        C[0] += A[2 * k] * B[k];
        C[1] += A[2 * k + 1] * B[k];
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
