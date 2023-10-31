
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
#include <emmintrin.h>

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
            int scalarLB;
            int vectorUB;
            bkj = B[k + B.size(0) * j];
            scalarLB = ((mc + 1) / 2) << 1;
            vectorUB = scalarLB - 2;
            for (int b_i{0}; b_i <= vectorUB; b_i += 2) {
                __m128d r;
                r = _mm_loadu_pd(&C[b_i + C.size(0) * j]);
                _mm_storeu_pd(
                    &C[b_i + C.size(0) * j],
                    _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd((const double *)&A[b_i + A.size(0) * k]),
                                             _mm_set1_pd(bkj))));
            }
            for (int b_i{scalarLB}; b_i <= mc; b_i++) {
                C[b_i + C.size(0) * j] = C[b_i + C.size(0) * j] + A[b_i + A.size(0) * k] * bkj;
            }
        }
    }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &B
//                ::coder::array<double, 1U> &C
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B,
            ::coder::array<double, 1U> &C)
{
    int inner;
    int mc;
    mc = A.size(0) - 1;
    inner = A.size(1);
    C.set_size(A.size(0));
    for (int i{0}; i <= mc; i++) {
        C[i] = 0.0;
    }
    for (int k{0}; k < inner; k++) {
        int scalarLB;
        int vectorUB;
        scalarLB = ((mc + 1) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int b_i{0}; b_i <= vectorUB; b_i += 2) {
            __m128d r;
            r = _mm_loadu_pd(&C[b_i]);
            _mm_storeu_pd(
                &C[b_i],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd((const double *)&A[b_i + A.size(0) * k]),
                                         _mm_set1_pd(B[k]))));
        }
        for (int b_i{scalarLB}; b_i <= mc; b_i++) {
            C[b_i] = C[b_i] + A[b_i + A.size(0) * k] * B[k];
        }
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
