//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"

// Function Definitions
//
// POLYVAL Evaluate array of polynomials with same degree.
//
//
// Arguments    : const double p[6][3]
//                double y[3]
// Return Type  : void
//
namespace ocn {
void b_mypolyval(const double p[6][3], double y[3])
{
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int i{0}; i < 5; i++) {
        d += p[i + 1][0];
        d1 += p[i + 1][1];
        d2 += p[i + 1][2];
    }
    y[2] = d2;
    y[1] = d1;
    y[0] = d;
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
        double d3;
        double d4;
        double d5;
        d3 = p[i + 1][0];
        d4 = p[i + 1][1];
        d5 = p[i + 1][2];
        for (int k{0}; k < 10; k++) {
            double d6;
            d6 = x[k];
            y[k][0] = d6 * y[k][0] + d3;
            y[k][1] = d6 * y[k][1] + d4;
            y[k][2] = d6 * y[k][2] + d5;
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
        int loop_ub;
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
        y.set_size(3, r.size(1));
        loop_ub = r.size(1);
        for (int i2{0}; i2 < loop_ub; i2++) {
            y[3 * i2] = r[3 * i2] * y[3 * i2] + b[3 * i2];
            y[3 * i2 + 1] = r[3 * i2 + 1] * y[3 * i2 + 1] + b[3 * i2 + 1];
            y[3 * i2 + 2] = r[3 * i2 + 2] * y[3 * i2 + 2] + b[3 * i2 + 2];
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
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int i{0}; i < 4; i++) {
        d = x * d + p[i + 1][0];
        d1 = x * d1 + p[i + 1][1];
        d2 = x * d2 + p[i + 1][2];
    }
    y[2] = d2;
    y[1] = d1;
    y[0] = d;
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
        double d3;
        double d4;
        double d5;
        d3 = p[i + 1][0];
        d4 = p[i + 1][1];
        d5 = p[i + 1][2];
        for (int k{0}; k < 10; k++) {
            double d6;
            d6 = x[k];
            y[k][0] = d6 * y[k][0] + d3;
            y[k][1] = d6 * y[k][1] + d4;
            y[k][2] = d6 * y[k][2] + d5;
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
        int loop_ub;
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
        y.set_size(3, r.size(1));
        loop_ub = r.size(1);
        for (int i2{0}; i2 < loop_ub; i2++) {
            y[3 * i2] = r[3 * i2] * y[3 * i2] + b[3 * i2];
            y[3 * i2 + 1] = r[3 * i2 + 1] * y[3 * i2 + 1] + b[3 * i2 + 1];
            y[3 * i2 + 2] = r[3 * i2 + 2] * y[3 * i2 + 2] + b[3 * i2 + 2];
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
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int i{0}; i < 3; i++) {
        d = x * d + p[i + 1][0];
        d1 = x * d1 + p[i + 1][1];
        d2 = x * d2 + p[i + 1][2];
    }
    y[2] = d2;
    y[1] = d1;
    y[0] = d;
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
        double d3;
        double d4;
        double d5;
        d3 = p[i + 1][0];
        d4 = p[i + 1][1];
        d5 = p[i + 1][2];
        for (int k{0}; k < 10; k++) {
            double d6;
            d6 = x[k];
            y[k][0] = d6 * y[k][0] + d3;
            y[k][1] = d6 * y[k][1] + d4;
            y[k][2] = d6 * y[k][2] + d5;
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
        int loop_ub;
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
        y.set_size(3, r.size(1));
        loop_ub = r.size(1);
        for (int i2{0}; i2 < loop_ub; i2++) {
            y[3 * i2] = r[3 * i2] * y[3 * i2] + b[3 * i2];
            y[3 * i2 + 1] = r[3 * i2 + 1] * y[3 * i2 + 1] + b[3 * i2 + 1];
            y[3 * i2 + 2] = r[3 * i2 + 2] * y[3 * i2 + 2] + b[3 * i2 + 2];
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
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int i{0}; i < 2; i++) {
        d = x * d + p[i + 1][0];
        d1 = x * d1 + p[i + 1][1];
        d2 = x * d2 + p[i + 1][2];
    }
    y[2] = d2;
    y[1] = d1;
    y[0] = d;
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
        double d3;
        double d4;
        double d5;
        d3 = p[i + 1][0];
        d4 = p[i + 1][1];
        d5 = p[i + 1][2];
        for (int k{0}; k < 10; k++) {
            double d6;
            d6 = x[k];
            y[k][0] = d6 * y[k][0] + d3;
            y[k][1] = d6 * y[k][1] + d4;
            y[k][2] = d6 * y[k][2] + d5;
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
        double d3;
        double d4;
        double d5;
        d3 = p[i + 1][0];
        d4 = p[i + 1][1];
        d5 = p[i + 1][2];
        for (int k{0}; k < 9; k++) {
            double d6;
            d6 = a[k];
            y[k][0] = d6 * y[k][0] + d3;
            y[k][1] = d6 * y[k][1] + d4;
            y[k][2] = d6 * y[k][2] + d5;
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
        int loop_ub;
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
        y.set_size(3, r.size(1));
        loop_ub = r.size(1);
        for (int i2{0}; i2 < loop_ub; i2++) {
            y[3 * i2] = r[3 * i2] * y[3 * i2] + b[3 * i2];
            y[3 * i2 + 1] = r[3 * i2 + 1] * y[3 * i2 + 1] + b[3 * i2 + 1];
            y[3 * i2 + 2] = r[3 * i2 + 2] * y[3 * i2 + 2] + b[3 * i2 + 2];
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
    double d;
    double d1;
    double d2;
    //
    //  Use Horner's method for general case where X is an array.
    d = p[0][0];
    d1 = p[0][1];
    d2 = p[0][2];
    for (int i{0}; i < 5; i++) {
        d = x * d + p[i + 1][0];
        d1 = x * d1 + p[i + 1][1];
        d2 = x * d2 + p[i + 1][2];
    }
    y[2] = d2;
    y[1] = d1;
    y[0] = d;
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
