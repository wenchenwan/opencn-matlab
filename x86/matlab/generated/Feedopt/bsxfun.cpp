//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

// Include Files
#include "bsxfun.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &a
//                const double b[5]
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
namespace ocn {
namespace coder {
void bsxfun(const ::coder::array<double, 2U> &a, const double b[5], ::coder::array<double, 2U> &c)
{
    c.set_size(5, a.size(1));
    if (a.size(1) != 0) {
        int acoef;
        int i;
        acoef = (a.size(1) != 1);
        i = a.size(1) - 1;
        for (int k{0}; k <= i; k++) {
            __m128d r;
            int varargin_2;
            varargin_2 = acoef * k;
            r = _mm_set1_pd(a[varargin_2]);
            _mm_storeu_pd(&c[5 * k], _mm_mul_pd(r, _mm_loadu_pd((const double *)&b[0])));
            _mm_storeu_pd(&c[5 * k + 2], _mm_mul_pd(r, _mm_loadu_pd((const double *)&b[2])));
            c[5 * k + 4] = a[varargin_2] * b[4];
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
