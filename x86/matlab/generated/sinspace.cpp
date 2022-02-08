//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "sinspace.h"
#include "linspace.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : double x0
//                double x1
//                int N
//                ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace ocn {
void sinspace(double x0, double x1, int N, ::coder::array<double, 2U> &x)
{
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> y;
    double b;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int i;
    int i1;
    int i2;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    coder::b_linspace(N, r);
    y.set_size(1, r.size(1));
    loop_ub = r.size(1);
    scalarLB = (r.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r[i]);
        _mm_storeu_pd(&y[i], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r1));
    }
    for (i = scalarLB; i < loop_ub; i++) {
        y[i] = 3.1415926535897931 * r[i];
    }
    i1 = y.size(1);
    for (int k{0}; k < i1; k++) {
        y[k] = std::cos(y[k]);
    }
    b = x1 - x0;
    x.set_size(1, y.size(1));
    b_loop_ub = y.size(1);
    b_scalarLB = (y.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
        __m128d r2;
        __m128d r3;
        r2 = _mm_loadu_pd(&y[i2]);
        r3 = _mm_set1_pd(0.5);
        _mm_storeu_pd(&x[i2],
                      _mm_add_pd(_mm_mul_pd(_mm_add_pd(_mm_mul_pd(r2, r3), r3), _mm_set1_pd(b)),
                                 _mm_set1_pd(x0)));
    }
    for (i2 = b_scalarLB; i2 < b_loop_ub; i2++) {
        x[i2] = (y[i2] * 0.5 + 0.5) * b + x0;
    }
}

} // namespace ocn

//
// File trailer for sinspace.cpp
//
// [EOF]
//
