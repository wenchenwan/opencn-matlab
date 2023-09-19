//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: TransP5LengthApprox.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "TransP5LengthApprox.h"
#include "mypolyder.h"
#include "mypolyval.h"
#include "opencn_matlab_data.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

// Function Definitions
//
// function L = TransP5LengthApprox(CurvStruct)
//
// Computes approximately the arc length of a parametric spline
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
// Return Type  : double
//
namespace ocn {
double TransP5LengthApprox(const ::coder::array<double, 2U> &CurvStruct_CoeffP5)
{
    static const double a[9]{
        0.055555555555555552, 0.16666666666666666, 0.27777777777777779, 0.38888888888888884, 0.5,
        0.61111111111111116,  0.7222222222222221,  0.83333333333333326, 0.94444444444444442};
    __m128d r2;
    __m128d r3;
    __m128d r4;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> y;
    ::coder::array<signed char, 2U> b;
    double Integrand[9];
    double b_y1[9];
    double x[9];
    double b_y;
    double work;
    int ixLead;
    int nD;
    int vlen;
    int xsubs_idx_1;
    short ysubs_idx_1;
    // 'TransP5LengthApprox:3' p5    = CurvStruct.CoeffP5;
    // 'TransP5LengthApprox:4' p5_1D = mypolyder(p5);
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    // 'mypolyder:5' [nD, nu] = size(u);
    // 'mypolyder:6' if nu < 2
    // 'mypolyder:8' else
    // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
    b.set_size(CurvStruct_CoeffP5.size(0), 5);
    if (CurvStruct_CoeffP5.size(0) != 0) {
        int i;
        i = CurvStruct_CoeffP5.size(0) - 1;
        for (int k{0}; k < 5; k++) {
            for (int t{0}; t <= i; t++) {
                b[t + b.size(0) * k] = static_cast<signed char>(5 - k);
            }
        }
    }
    if (CurvStruct_CoeffP5.size(0) == b.size(0)) {
        int loop_ub;
        loop_ub = CurvStruct_CoeffP5.size(0);
        p5_1D.set_size(CurvStruct_CoeffP5.size(0), 5);
        for (int i1{0}; i1 < 5; i1++) {
            for (int i2{0}; i2 < loop_ub; i2++) {
                p5_1D[i2 + p5_1D.size(0) * i1] =
                    CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1] *
                    static_cast<double>(b[i2 + b.size(0) * i1]);
            }
        }
    } else {
        c_binary_expand_op(p5_1D, CurvStruct_CoeffP5, b);
    }
    //  Derivative
    // 'TransP5LengthApprox:5' u_vec     = linspace(0,1,10);
    // 'TransP5LengthApprox:6' u_mid     = 0.5*(u_vec(1:end-1) +u_vec(2:end));
    //  Midpoint values
    // 'TransP5LengthApprox:7' du        = diff(u_vec);
    ixLead = 1;
    work = 0.0;
    for (int m{0}; m < 9; m++) {
        double tmp2;
        double work_tmp;
        tmp2 = work;
        work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
        work = work_tmp;
        b_y1[m] = work_tmp - tmp2;
        ixLead++;
    }
    // 'TransP5LengthApprox:8' Integrand = mysqrt(sum(mypolyval(p5_1D, u_mid).^2));
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    nD = p5_1D.size(0);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    y.set_size(p5_1D.size(0), 9);
    if (p5_1D.size(0) != 0) {
        int i3;
        i3 = p5_1D.size(0) - 1;
        for (int b_t{0}; b_t < 9; b_t++) {
            for (int b_k{0}; b_k <= i3; b_k++) {
                y[b_k + y.size(0) * b_t] = p5_1D[b_k];
            }
        }
    }
    // 'mypolyval:12' for i=2:nc
    for (int b_i{0}; b_i < 4; b_i++) {
        int i8;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r.set_size(nD, 9);
        if (p5_1D.size(0) != 0) {
            int i5;
            i5 = nD - 1;
            for (int c_k{0}; c_k < 9; c_k++) {
                for (int c_t{0}; c_t <= i5; c_t++) {
                    r[c_t + r.size(0) * c_k] = a[c_k];
                }
            }
        }
        r1.set_size(p5_1D.size(0), 9);
        if (p5_1D.size(0) != 0) {
            int i7;
            i7 = p5_1D.size(0) - 1;
            for (int d_t{0}; d_t < 9; d_t++) {
                for (int d_k{0}; d_k <= i7; d_k++) {
                    r1[d_k + r1.size(0) * d_t] = p5_1D[d_k + p5_1D.size(0) * (b_i + 1)];
                }
            }
        }
        if (r.size(0) == 1) {
            i8 = y.size(0);
        } else {
            i8 = r.size(0);
        }
        if ((r.size(0) == y.size(0)) && (i8 == r1.size(0))) {
            int c_loop_ub;
            int scalarLB;
            int vectorUB;
            y.set_size(r.size(0), 9);
            c_loop_ub = r.size(0);
            scalarLB = (c_loop_ub / 2) << 1;
            vectorUB = scalarLB - 2;
            for (int i9{0}; i9 < 9; i9++) {
                for (int i10{0}; i10 <= vectorUB; i10 += 2) {
                    __m128d r5;
                    __m128d r6;
                    __m128d r7;
                    r5 = _mm_loadu_pd(&r[i10 + r.size(0) * i9]);
                    r6 = _mm_loadu_pd(&y[i10 + y.size(0) * i9]);
                    r7 = _mm_loadu_pd(&r1[i10 + r1.size(0) * i9]);
                    _mm_storeu_pd(&y[i10 + y.size(0) * i9], _mm_add_pd(_mm_mul_pd(r5, r6), r7));
                }
                for (int i10{scalarLB}; i10 < c_loop_ub; i10++) {
                    y[i10 + y.size(0) * i9] = r[i10 + r.size(0) * i9] * y[i10 + y.size(0) * i9] +
                                              r1[i10 + r1.size(0) * i9];
                }
            }
        } else {
            b_binary_expand_op(y, r, r1);
        }
    }
    y.set_size(y.size(0), 9);
    for (int i4{0}; i4 < 9; i4++) {
        int b_loop_ub;
        b_loop_ub = y.size(0);
        for (int i6{0}; i6 < b_loop_ub; i6++) {
            double varargin_1;
            varargin_1 = y[i6 + y.size(0) * i4];
            y[i6 + y.size(0) * i4] = std::pow(varargin_1, 2.0);
        }
    }
    vlen = y.size(0);
    if (y.size(0) == 0) {
        std::memset(&Integrand[0], 0, 9U * sizeof(double));
    } else {
        int firstBlockLength;
        int lastBlockLength;
        int nblocks;
        if (y.size(0) <= 1024) {
            firstBlockLength = y.size(0);
            lastBlockLength = 0;
            nblocks = 1;
        } else {
            firstBlockLength = 1024;
            nblocks = y.size(0) / 1024;
            lastBlockLength = y.size(0) - (nblocks << 10);
            if (lastBlockLength > 0) {
                nblocks++;
            } else {
                lastBlockLength = 1024;
            }
        }
        for (int e_k{0}; e_k < 9; e_k++) {
            Integrand[e_k] = y[y.size(0) * e_k];
            for (int f_k{2}; f_k <= firstBlockLength; f_k++) {
                if (vlen >= 2) {
                    ysubs_idx_1 = static_cast<short>(e_k + 1);
                    Integrand[e_k] += y[(f_k + y.size(0) * e_k) - 1];
                }
            }
            if (nblocks >= 2) {
                xsubs_idx_1 = e_k + 1;
                ysubs_idx_1 = static_cast<short>(e_k + 1);
            }
            for (int ib{2}; ib <= nblocks; ib++) {
                double bsum;
                int hi;
                int offset;
                offset = (ib - 1) << 10;
                bsum = y[offset + y.size(0) * (xsubs_idx_1 - 1)];
                if (ib == nblocks) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (int g_k{2}; g_k <= hi; g_k++) {
                    double b_bsum;
                    b_bsum = bsum;
                    if (vlen >= 2) {
                        b_bsum = bsum + y[((offset + g_k) + y.size(0) * e_k) - 1];
                    }
                    bsum = b_bsum;
                }
                Integrand[ysubs_idx_1 - 1] += bsum;
            }
        }
    }
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'TransP5LengthApprox:9' L         = sum(Integrand.*du);
    r2 = _mm_loadu_pd(&Integrand[0]);
    r3 = _mm_sqrt_pd(r2);
    _mm_storeu_pd(&Integrand[0], r3);
    r4 = _mm_loadu_pd(&b_y1[0]);
    _mm_storeu_pd(&x[0], _mm_mul_pd(r3, r4));
    r2 = _mm_loadu_pd(&Integrand[2]);
    r3 = _mm_sqrt_pd(r2);
    _mm_storeu_pd(&Integrand[2], r3);
    r4 = _mm_loadu_pd(&b_y1[2]);
    _mm_storeu_pd(&x[2], _mm_mul_pd(r3, r4));
    r2 = _mm_loadu_pd(&Integrand[4]);
    r3 = _mm_sqrt_pd(r2);
    _mm_storeu_pd(&Integrand[4], r3);
    r4 = _mm_loadu_pd(&b_y1[4]);
    _mm_storeu_pd(&x[4], _mm_mul_pd(r3, r4));
    r2 = _mm_loadu_pd(&Integrand[6]);
    r3 = _mm_sqrt_pd(r2);
    _mm_storeu_pd(&Integrand[6], r3);
    r4 = _mm_loadu_pd(&b_y1[6]);
    _mm_storeu_pd(&x[6], _mm_mul_pd(r3, r4));
    x[8] = std::sqrt(Integrand[8]) * b_y1[8];
    b_y = x[0];
    for (int h_k{0}; h_k < 8; h_k++) {
        b_y += x[h_k + 1];
    }
    return b_y;
}

} // namespace ocn

//
// File trailer for TransP5LengthApprox.cpp
//
// [EOF]
//
