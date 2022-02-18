//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &y, const ::coder::array<double, 2U> &r4,
                             const ::coder::array<double, 2U> &b);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &y
//                const ::coder::array<double, 2U> &r4
//                const ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &y, const ::coder::array<double, 2U> &r4,
                             const ::coder::array<double, 2U> &b)
{
    ::coder::array<double, 2U> r;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    if (b.size(1) == 1) {
        if (y.size(1) == 1) {
            i = r4.size(1);
        } else {
            i = y.size(1);
        }
    } else {
        i = b.size(1);
    }
    r.set_size(3, i);
    stride_0_1 = (r4.size(1) != 1);
    stride_1_1 = (y.size(1) != 1);
    stride_2_1 = (b.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (b.size(1) == 1) {
        if (y.size(1) == 1) {
            loop_ub = r4.size(1);
        } else {
            loop_ub = y.size(1);
        }
    } else {
        loop_ub = b.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        __m128d r1;
        __m128d r2;
        __m128d r3;
        r1 = _mm_loadu_pd((const double *)&r4[3 * aux_0_1]);
        r2 = _mm_loadu_pd(&y[3 * aux_1_1]);
        r3 = _mm_loadu_pd((const double *)&b[3 * aux_2_1]);
        _mm_storeu_pd(&r[3 * i1], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
        r[3 * i1 + 2] = r4[3 * aux_0_1 + 2] * y[3 * aux_1_1 + 2] + b[3 * aux_2_1 + 2];
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    y.set_size(3, r.size(1));
    b_loop_ub = r.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        y[3 * i2] = r[3 * i2];
        y[3 * i2 + 1] = r[3 * i2 + 1];
        y[3 * i2 + 2] = r[3 * i2 + 2];
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[6][3]
//                double y[3]
// Return Type  : void
//
void b_mypolyval(const double p[6][3], double y[3])
{
    //
    //  Use Horner's method for general case where X is an array.
    y[0] = p[0][0];
    y[1] = p[0][1];
    y[2] = p[0][2];
    for (int i{0}; i < 5; i++) {
        __m128d r;
        r = _mm_loadu_pd(&y[0]);
        _mm_storeu_pd(&y[0], _mm_add_pd(r, _mm_loadu_pd((const double *)&p[i + 1][0])));
        y[2] += p[i + 1][2];
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[5][3]
//                const double x[10]
//                double y[10][3]
// Return Type  : void
//
void b_mypolyval(const double p[5][3], const double x[10], double y[10][3])
{
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int t{0}; t < 10; t++) {
        y[t][0] = d;
        y[t][1] = d1;
        y[t][2] = d2;
    }
    for (int i{0}; i < 4; i++) {
        for (int k{0}; k < 10; k++) {
            __m128d r;
            double d3;
            r = _mm_loadu_pd(&y[k][0]);
            d3 = x[k];
            _mm_storeu_pd(&y[k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r),
                                               _mm_loadu_pd((const double *)&p[i + 1][0])));
            y[k][2] = d3 * y[k][2] + p[i + 1][2];
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[5][3]
//                const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void b_mypolyval(const double p[5][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> r;
    //
    //  Use Horner's method for general case where X is an array.
    y.set_size(3, x.size(1));
    if (x.size(1) != 0) {
        int i;
        i = x.size(1) - 1;
        for (int t{0}; t <= i; t++) {
            y[3 * t] = p[0][0];
            y[3 * t + 1] = p[0][1];
            y[3 * t + 2] = p[0][2];
        }
    }
    for (int b_i{0}; b_i < 4; b_i++) {
        int i2;
        r.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int na;
            na = x.size(1);
            for (int k{0}; k < na; k++) {
                r[3 * k] = x[k];
                r[3 * k + 1] = x[k];
                r[3 * k + 2] = x[k];
            }
        }
        b.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int i1;
            i1 = x.size(1) - 1;
            for (int b_t{0}; b_t <= i1; b_t++) {
                b[3 * b_t] = p[b_i + 1][0];
                b[3 * b_t + 1] = p[b_i + 1][1];
                b[3 * b_t + 2] = p[b_i + 1][2];
            }
        }
        if (r.size(1) == 1) {
            i2 = y.size(1);
        } else {
            i2 = r.size(1);
        }
        if ((r.size(1) == y.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            y.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i3{0}; i3 < loop_ub; i3++) {
                __m128d r1;
                __m128d r2;
                __m128d r3;
                r1 = _mm_loadu_pd(&r[3 * i3]);
                r2 = _mm_loadu_pd(&y[3 * i3]);
                r3 = _mm_loadu_pd(&b[3 * i3]);
                _mm_storeu_pd(&y[3 * i3], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
                y[3 * i3 + 2] = r[3 * i3 + 2] * y[3 * i3 + 2] + b[3 * i3 + 2];
            }
        } else {
            binary_expand_op(y, r, b);
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[5][3]
//                double x
//                double y[3]
// Return Type  : void
//
void b_mypolyval(const double p[5][3], double x, double y[3])
{
    __m128d r;
    __m128d r1;
    //
    //  Use Horner's method for general case where X is an array.
    y[0] = p[0][0];
    y[1] = p[0][1];
    y[2] = p[0][2];
    r = _mm_loadu_pd(&y[0]);
    r1 = _mm_set1_pd(x);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[1][0])));
    y[2] = x * y[2] + p[1][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[2][0])));
    y[2] = x * y[2] + p[2][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[3][0])));
    y[2] = x * y[2] + p[3][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[4][0])));
    y[2] = x * y[2] + p[4][2];
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[4][3]
//                const double x[10]
//                double y[10][3]
// Return Type  : void
//
void c_mypolyval(const double p[4][3], const double x[10], double y[10][3])
{
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int t{0}; t < 10; t++) {
        y[t][0] = d;
        y[t][1] = d1;
        y[t][2] = d2;
    }
    for (int i{0}; i < 3; i++) {
        for (int k{0}; k < 10; k++) {
            __m128d r;
            double d3;
            r = _mm_loadu_pd(&y[k][0]);
            d3 = x[k];
            _mm_storeu_pd(&y[k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r),
                                               _mm_loadu_pd((const double *)&p[i + 1][0])));
            y[k][2] = d3 * y[k][2] + p[i + 1][2];
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[4][3]
//                const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void c_mypolyval(const double p[4][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> r;
    //
    //  Use Horner's method for general case where X is an array.
    y.set_size(3, x.size(1));
    if (x.size(1) != 0) {
        int i;
        i = x.size(1) - 1;
        for (int t{0}; t <= i; t++) {
            y[3 * t] = p[0][0];
            y[3 * t + 1] = p[0][1];
            y[3 * t + 2] = p[0][2];
        }
    }
    for (int b_i{0}; b_i < 3; b_i++) {
        int i2;
        r.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int na;
            na = x.size(1);
            for (int k{0}; k < na; k++) {
                r[3 * k] = x[k];
                r[3 * k + 1] = x[k];
                r[3 * k + 2] = x[k];
            }
        }
        b.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int i1;
            i1 = x.size(1) - 1;
            for (int b_t{0}; b_t <= i1; b_t++) {
                b[3 * b_t] = p[b_i + 1][0];
                b[3 * b_t + 1] = p[b_i + 1][1];
                b[3 * b_t + 2] = p[b_i + 1][2];
            }
        }
        if (r.size(1) == 1) {
            i2 = y.size(1);
        } else {
            i2 = r.size(1);
        }
        if ((r.size(1) == y.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            y.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i3{0}; i3 < loop_ub; i3++) {
                __m128d r1;
                __m128d r2;
                __m128d r3;
                r1 = _mm_loadu_pd(&r[3 * i3]);
                r2 = _mm_loadu_pd(&y[3 * i3]);
                r3 = _mm_loadu_pd(&b[3 * i3]);
                _mm_storeu_pd(&y[3 * i3], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
                y[3 * i3 + 2] = r[3 * i3 + 2] * y[3 * i3 + 2] + b[3 * i3 + 2];
            }
        } else {
            binary_expand_op(y, r, b);
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[4][3]
//                double x
//                double y[3]
// Return Type  : void
//
void c_mypolyval(const double p[4][3], double x, double y[3])
{
    __m128d r;
    __m128d r1;
    //
    //  Use Horner's method for general case where X is an array.
    y[0] = p[0][0];
    y[1] = p[0][1];
    y[2] = p[0][2];
    r = _mm_loadu_pd(&y[0]);
    r1 = _mm_set1_pd(x);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[1][0])));
    y[2] = x * y[2] + p[1][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[2][0])));
    y[2] = x * y[2] + p[2][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[3][0])));
    y[2] = x * y[2] + p[3][2];
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[3][3]
//                const double x[10]
//                double y[10][3]
// Return Type  : void
//
void d_mypolyval(const double p[3][3], const double x[10], double y[10][3])
{
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int t{0}; t < 10; t++) {
        y[t][0] = d;
        y[t][1] = d1;
        y[t][2] = d2;
    }
    for (int i{0}; i < 2; i++) {
        for (int k{0}; k < 10; k++) {
            __m128d r;
            double d3;
            r = _mm_loadu_pd(&y[k][0]);
            d3 = x[k];
            _mm_storeu_pd(&y[k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r),
                                               _mm_loadu_pd((const double *)&p[i + 1][0])));
            y[k][2] = d3 * y[k][2] + p[i + 1][2];
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[3][3]
//                const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void d_mypolyval(const double p[3][3], const ::coder::array<double, 2U> &x,
                 ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> r;
    //
    //  Use Horner's method for general case where X is an array.
    y.set_size(3, x.size(1));
    if (x.size(1) != 0) {
        int i;
        i = x.size(1) - 1;
        for (int t{0}; t <= i; t++) {
            y[3 * t] = p[0][0];
            y[3 * t + 1] = p[0][1];
            y[3 * t + 2] = p[0][2];
        }
    }
    for (int b_i{0}; b_i < 2; b_i++) {
        int i2;
        r.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int na;
            na = x.size(1);
            for (int k{0}; k < na; k++) {
                r[3 * k] = x[k];
                r[3 * k + 1] = x[k];
                r[3 * k + 2] = x[k];
            }
        }
        b.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int i1;
            i1 = x.size(1) - 1;
            for (int b_t{0}; b_t <= i1; b_t++) {
                b[3 * b_t] = p[b_i + 1][0];
                b[3 * b_t + 1] = p[b_i + 1][1];
                b[3 * b_t + 2] = p[b_i + 1][2];
            }
        }
        if (r.size(1) == 1) {
            i2 = y.size(1);
        } else {
            i2 = r.size(1);
        }
        if ((r.size(1) == y.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            y.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i3{0}; i3 < loop_ub; i3++) {
                __m128d r1;
                __m128d r2;
                __m128d r3;
                r1 = _mm_loadu_pd(&r[3 * i3]);
                r2 = _mm_loadu_pd(&y[3 * i3]);
                r3 = _mm_loadu_pd(&b[3 * i3]);
                _mm_storeu_pd(&y[3 * i3], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
                y[3 * i3 + 2] = r[3 * i3 + 2] * y[3 * i3 + 2] + b[3 * i3 + 2];
            }
        } else {
            binary_expand_op(y, r, b);
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[3][3]
//                double x
//                double y[3]
// Return Type  : void
//
void d_mypolyval(const double p[3][3], double x, double y[3])
{
    __m128d r;
    __m128d r1;
    //
    //  Use Horner's method for general case where X is an array.
    y[0] = p[0][0];
    y[1] = p[0][1];
    y[2] = p[0][2];
    r = _mm_loadu_pd(&y[0]);
    r1 = _mm_set1_pd(x);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[1][0])));
    y[2] = x * y[2] + p[1][2];
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(r1, r), _mm_loadu_pd((const double *)&p[2][0])));
    y[2] = x * y[2] + p[2][2];
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[6][3]
//                const double x[10]
//                double y[10][3]
// Return Type  : void
//
void mypolyval(const double p[6][3], const double x[10], double y[10][3])
{
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int t{0}; t < 10; t++) {
        y[t][0] = d;
        y[t][1] = d1;
        y[t][2] = d2;
    }
    for (int i{0}; i < 5; i++) {
        for (int k{0}; k < 10; k++) {
            __m128d r;
            double d3;
            r = _mm_loadu_pd(&y[k][0]);
            d3 = x[k];
            _mm_storeu_pd(&y[k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r),
                                               _mm_loadu_pd((const double *)&p[i + 1][0])));
            y[k][2] = d3 * y[k][2] + p[i + 1][2];
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[5][3]
//                double y[9][3]
// Return Type  : void
//
void mypolyval(const double p[5][3], double y[9][3])
{
    static const double a[9]{
        0.055555555555555552, 0.16666666666666666, 0.27777777777777779, 0.38888888888888884, 0.5,
        0.61111111111111116,  0.7222222222222221,  0.83333333333333326, 0.94444444444444442};
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int t{0}; t < 9; t++) {
        y[t][0] = d;
        y[t][1] = d1;
        y[t][2] = d2;
    }
    for (int i{0}; i < 4; i++) {
        for (int k{0}; k < 9; k++) {
            __m128d r;
            double d3;
            r = _mm_loadu_pd(&y[k][0]);
            d3 = a[k];
            _mm_storeu_pd(&y[k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r),
                                               _mm_loadu_pd((const double *)&p[i + 1][0])));
            y[k][2] = d3 * y[k][2] + p[i + 1][2];
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[6][3]
//                const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void mypolyval(const double p[6][3], const ::coder::array<double, 2U> &x,
               ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> r;
    //
    //  Use Horner's method for general case where X is an array.
    y.set_size(3, x.size(1));
    if (x.size(1) != 0) {
        int i;
        i = x.size(1) - 1;
        for (int t{0}; t <= i; t++) {
            y[3 * t] = p[0][0];
            y[3 * t + 1] = p[0][1];
            y[3 * t + 2] = p[0][2];
        }
    }
    for (int b_i{0}; b_i < 5; b_i++) {
        int i2;
        r.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int na;
            na = x.size(1);
            for (int k{0}; k < na; k++) {
                r[3 * k] = x[k];
                r[3 * k + 1] = x[k];
                r[3 * k + 2] = x[k];
            }
        }
        b.set_size(3, x.size(1));
        if (x.size(1) != 0) {
            int i1;
            i1 = x.size(1) - 1;
            for (int b_t{0}; b_t <= i1; b_t++) {
                b[3 * b_t] = p[b_i + 1][0];
                b[3 * b_t + 1] = p[b_i + 1][1];
                b[3 * b_t + 2] = p[b_i + 1][2];
            }
        }
        if (r.size(1) == 1) {
            i2 = y.size(1);
        } else {
            i2 = r.size(1);
        }
        if ((r.size(1) == y.size(1)) && (i2 == b.size(1))) {
            int loop_ub;
            y.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i3{0}; i3 < loop_ub; i3++) {
                __m128d r1;
                __m128d r2;
                __m128d r3;
                r1 = _mm_loadu_pd(&r[3 * i3]);
                r2 = _mm_loadu_pd(&y[3 * i3]);
                r3 = _mm_loadu_pd(&b[3 * i3]);
                _mm_storeu_pd(&y[3 * i3], _mm_add_pd(_mm_mul_pd(r1, r2), r3));
                y[3 * i3 + 2] = r[3 * i3 + 2] * y[3 * i3 + 2] + b[3 * i3 + 2];
            }
        } else {
            binary_expand_op(y, r, b);
        }
    }
}

//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[6][3]
//                double x
//                double y[3]
// Return Type  : void
//
void mypolyval(const double p[6][3], double x, double y[3])
{
    //
    //  Use Horner's method for general case where X is an array.
    y[0] = p[0][0];
    y[1] = p[0][1];
    y[2] = p[0][2];
    for (int i{0}; i < 5; i++) {
        __m128d r;
        r = _mm_loadu_pd(&y[0]);
        _mm_storeu_pd(&y[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(x), r),
                                        _mm_loadu_pd((const double *)&p[i + 1][0])));
        y[2] = x * y[2] + p[i + 1][2];
    }
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
