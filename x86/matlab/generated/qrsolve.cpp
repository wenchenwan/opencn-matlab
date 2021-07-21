//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qrsolve.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "qrsolve.h"
#include "xnrm2.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static double rt_hypotd(double u0, double u1);

}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace ocn {
static double rt_hypotd(double u0, double u1)
{
    double a;
    double b;
    double y;
    a = std::abs(u0);
    b = std::abs(u1);
    if (a < b) {
        a /= b;
        y = b * std::sqrt(a * a + 1.0);
    } else if (a > b) {
        b /= a;
        y = a * std::sqrt(b * b + 1.0);
    } else {
        y = a * 1.4142135623730951;
    }
    return y;
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &B
//                ::coder::array<double, 1U> &Y
// Return Type  : void
//
namespace coder {
namespace internal {
void qrsolve(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B,
             ::coder::array<double, 1U> &Y)
{
    static const int offsets[4]{0, 1, 2, 3};
    ::coder::array<double, 2U> b_A;
    ::coder::array<double, 1U> b_B;
    ::coder::array<double, 1U> tau;
    ::coder::array<double, 1U> vn1;
    ::coder::array<double, 1U> vn2;
    ::coder::array<double, 1U> work;
    ::coder::array<int, 2U> jpvt;
    double tol;
    int b_loop_ub;
    int b_m;
    int b_minmn;
    int b_u0;
    int b_u1;
    int c_u0;
    int c_u1;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int k;
    int loop_ub;
    int m;
    int ma;
    int maxmn;
    int minmana;
    int minmn;
    int mn;
    int n;
    int rankA;
    int scalarLB;
    int u0;
    int u1;
    int vectorUB;
    m = A.size(0);
    n = A.size(1);
    u0 = A.size(0);
    u1 = A.size(1);
    if (u0 < u1) {
        minmana = u0;
    } else {
        minmana = u1;
    }
    tau.set_size(minmana);
    for (int i{0}; i < minmana; i++) {
        tau[i] = 0.0;
    }
    jpvt.set_size(1, A.size(1));
    loop_ub = A.size(1);
    for (int i1{0}; i1 < loop_ub; i1++) {
        jpvt[i1] = 0;
    }
    scalarLB = (A.size(1) / 4) << 2;
    vectorUB = scalarLB - 4;
    for (k = 0; k <= vectorUB; k += 4) {
        _mm_storeu_si128(
            (__m128i *)&jpvt[k],
            _mm_add_epi32(_mm_add_epi32(_mm_set1_epi32(k), _mm_loadu_si128((__m128i *)&offsets[0])),
                          _mm_set1_epi32(1)));
    }
    for (k = scalarLB; k < n; k++) {
        jpvt[k] = k + 1;
    }
    b_A.set_size(A.size(0), A.size(1));
    b_loop_ub = A.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        int c_loop_ub;
        c_loop_ub = A.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_A[i3 + b_A.size(0) * i2] = A[i3 + A.size(0) * i2];
        }
    }
    ma = A.size(0);
    b_u0 = A.size(0);
    b_u1 = A.size(1);
    if (b_u0 < b_u1) {
        minmn = b_u0;
    } else {
        minmn = b_u1;
    }
    work.set_size(A.size(1));
    d_loop_ub = A.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        work[i4] = 0.0;
    }
    vn1.set_size(A.size(1));
    e_loop_ub = A.size(1);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        vn1[i5] = 0.0;
    }
    vn2.set_size(A.size(1));
    f_loop_ub = A.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        vn2[i6] = 0.0;
    }
    for (int j{0}; j < n; j++) {
        double d;
        d = blas::xnrm2(m, A, j * ma + 1);
        vn1[j] = d;
        vn2[j] = d;
    }
    for (int b_i{0}; b_i < minmn; b_i++) {
        int idxmax;
        int ii;
        int ii_tmp;
        int ip1;
        int mmi;
        int nmi;
        int pvt;
        ip1 = b_i + 2;
        ii_tmp = b_i * ma;
        ii = ii_tmp + b_i;
        nmi = n - b_i;
        mmi = m - b_i;
        if (nmi < 1) {
            idxmax = -1;
        } else {
            idxmax = 0;
            if (nmi > 1) {
                double smax;
                smax = std::abs(vn1[b_i]);
                for (int b_k{2}; b_k <= nmi; b_k++) {
                    double s;
                    s = std::abs(vn1[(b_i + b_k) - 1]);
                    if (s > smax) {
                        idxmax = b_k - 1;
                        smax = s;
                    }
                }
            }
        }
        pvt = b_i + idxmax;
        if (pvt + 1 != b_i + 1) {
            int ix;
            ix = pvt * ma;
            for (int c_k{0}; c_k < m; c_k++) {
                double temp;
                int i9;
                int temp_tmp;
                temp_tmp = ix + c_k;
                temp = b_A[temp_tmp];
                i9 = ii_tmp + c_k;
                b_A[temp_tmp] = b_A[i9];
                b_A[i9] = temp;
            }
            int itemp;
            itemp = jpvt[pvt];
            jpvt[pvt] = jpvt[b_i];
            jpvt[b_i] = itemp;
            vn1[pvt] = vn1[b_i];
            vn2[pvt] = vn2[b_i];
        }
        if (b_i + 1 < m) {
            double atmp;
            int ix0;
            atmp = b_A[ii];
            ix0 = ii + 2;
            tau[b_i] = 0.0;
            if (mmi > 0) {
                double xnorm_tmp;
                xnorm_tmp = blas::xnrm2(mmi - 1, b_A, ii + 2);
                if (xnorm_tmp != 0.0) {
                    double beta1;
                    beta1 = rt_hypotd(b_A[ii], xnorm_tmp);
                    if (b_A[ii] >= 0.0) {
                        beta1 = -beta1;
                    }
                    if (std::abs(beta1) < 1.0020841800044864E-292) {
                        double b_a;
                        int i10;
                        int knt;
                        knt = -1;
                        i10 = ii + mmi;
                        do {
                            knt++;
                            for (int e_k{ix0}; e_k <= i10; e_k++) {
                                b_A[e_k - 1] = 9.9792015476736E+291 * b_A[e_k - 1];
                            }
                            beta1 *= 9.9792015476736E+291;
                            atmp *= 9.9792015476736E+291;
                        } while (!(std::abs(beta1) >= 1.0020841800044864E-292));
                        beta1 = rt_hypotd(atmp, blas::xnrm2(mmi - 1, b_A, ii + 2));
                        if (atmp >= 0.0) {
                            beta1 = -beta1;
                        }
                        tau[b_i] = (beta1 - atmp) / beta1;
                        b_a = 1.0 / (atmp - beta1);
                        for (int f_k{ix0}; f_k <= i10; f_k++) {
                            b_A[f_k - 1] = b_a * b_A[f_k - 1];
                        }
                        for (int g_k{0}; g_k <= knt; g_k++) {
                            beta1 *= 1.0020841800044864E-292;
                        }
                        atmp = beta1;
                    } else {
                        double a;
                        int i11;
                        tau[b_i] = (beta1 - b_A[ii]) / beta1;
                        a = 1.0 / (b_A[ii] - beta1);
                        i11 = ii + mmi;
                        for (int d_k{ix0}; d_k <= i11; d_k++) {
                            b_A[d_k - 1] = a * b_A[d_k - 1];
                        }
                        atmp = beta1;
                    }
                }
            }
            b_A[ii] = atmp;
        } else {
            tau[b_i] = 0.0;
        }
        if (b_i + 1 < n) {
            double b_atmp;
            int ic0;
            int lastc;
            int lastv;
            b_atmp = b_A[ii];
            b_A[ii] = 1.0;
            ic0 = (ii + ma) + 1;
            if (tau[b_i] != 0.0) {
                int b_lastc;
                int c_i;
                bool exitg2;
                lastv = mmi - 1;
                c_i = (ii + mmi) - 1;
                while ((lastv + 1 > 0) && (b_A[c_i] == 0.0)) {
                    lastv--;
                    c_i--;
                }
                b_lastc = nmi - 2;
                exitg2 = false;
                while ((!exitg2) && (b_lastc + 1 > 0)) {
                    int coltop;
                    int exitg1;
                    int ia;
                    coltop = ic0 + b_lastc * ma;
                    ia = coltop;
                    do {
                        exitg1 = 0;
                        if (ia <= coltop + lastv) {
                            if (b_A[ia - 1] != 0.0) {
                                exitg1 = 1;
                            } else {
                                ia++;
                            }
                        } else {
                            b_lastc--;
                            exitg1 = 2;
                        }
                    } while (exitg1 == 0);
                    if (exitg1 == 1) {
                        exitg2 = true;
                    }
                }
                lastc = b_lastc;
            } else {
                lastv = -1;
                lastc = -1;
            }
            if (lastv + 1 > 0) {
                if (lastc + 1 != 0) {
                    int b_iy;
                    int i13;
                    for (int iy{0}; iy <= lastc; iy++) {
                        work[iy] = 0.0;
                    }
                    b_iy = 0;
                    i13 = ic0 + ma * lastc;
                    for (int iac{ic0}; ma < 0 ? iac >= i13 : iac <= i13; iac += ma) {
                        double c;
                        int i16;
                        c = 0.0;
                        i16 = iac + lastv;
                        for (int b_ia{iac}; b_ia <= i16; b_ia++) {
                            c += b_A[b_ia - 1] * b_A[(ii + b_ia) - iac];
                        }
                        work[b_iy] = work[b_iy] + c;
                        b_iy++;
                    }
                }
                if (-tau[b_i] != 0.0) {
                    int jA;
                    jA = ic0;
                    for (int e_j{0}; e_j <= lastc; e_j++) {
                        if (work[e_j] != 0.0) {
                            double b_temp;
                            int i15;
                            b_temp = work[e_j] * -tau[b_i];
                            i15 = lastv + jA;
                            for (int ijA{jA}; ijA <= i15; ijA++) {
                                b_A[ijA - 1] = b_A[ijA - 1] + b_A[(ii + ijA) - jA] * b_temp;
                            }
                        }
                        jA += ma;
                    }
                }
            }
            b_A[ii] = b_atmp;
        }
        for (int b_j{ip1}; b_j <= n; b_j++) {
            double d1;
            int ij;
            ij = b_i + (b_j - 1) * ma;
            d1 = vn1[b_j - 1];
            if (d1 != 0.0) {
                double temp1;
                double temp2;
                temp1 = std::abs(b_A[ij]) / d1;
                temp1 = 1.0 - temp1 * temp1;
                if (temp1 < 0.0) {
                    temp1 = 0.0;
                }
                temp2 = d1 / vn2[b_j - 1];
                temp2 = temp1 * (temp2 * temp2);
                if (temp2 <= 1.4901161193847656E-8) {
                    if (b_i + 1 < m) {
                        double d2;
                        d2 = blas::xnrm2(mmi - 1, b_A, ij + 2);
                        vn1[b_j - 1] = d2;
                        vn2[b_j - 1] = d2;
                    } else {
                        vn1[b_j - 1] = 0.0;
                        vn2[b_j - 1] = 0.0;
                    }
                } else {
                    vn1[b_j - 1] = d1 * std::sqrt(temp1);
                }
            }
        }
    }
    rankA = 0;
    if (b_A.size(0) < b_A.size(1)) {
        b_minmn = b_A.size(0);
        maxmn = b_A.size(1);
    } else {
        b_minmn = b_A.size(1);
        maxmn = b_A.size(0);
    }
    tol = std::fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * static_cast<double>(maxmn)) *
          std::abs(b_A[0]);
    while ((rankA < b_minmn) && (std::abs(b_A[rankA + b_A.size(0) * rankA]) > tol)) {
        rankA++;
    }
    b_B.set_size(B.size(0));
    g_loop_ub = B.size(0);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        b_B[i7] = B[i7];
    }
    Y.set_size(b_A.size(1));
    h_loop_ub = b_A.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        Y[i8] = 0.0;
    }
    b_m = b_A.size(0);
    c_u0 = b_A.size(0);
    c_u1 = b_A.size(1);
    if (c_u0 < c_u1) {
        mn = c_u0;
    } else {
        mn = c_u1;
    }
    for (int c_j{0}; c_j < mn; c_j++) {
        if (tau[c_j] != 0.0) {
            double wj;
            int i12;
            wj = b_B[c_j];
            i12 = c_j + 2;
            for (int e_i{i12}; e_i <= b_m; e_i++) {
                wj += b_A[(e_i + b_A.size(0) * c_j) - 1] * b_B[e_i - 1];
            }
            wj *= tau[c_j];
            if (wj != 0.0) {
                int b_scalarLB;
                int b_vectorUB;
                int g_i;
                b_B[c_j] = b_B[c_j] - wj;
                b_scalarLB = (((((b_m - c_j) - 1) / 2) << 1) + c_j) + 2;
                b_vectorUB = b_scalarLB - 2;
                for (g_i = i12; g_i <= b_vectorUB; g_i += 2) {
                    __m128d r;
                    __m128d r1;
                    r = _mm_loadu_pd(&b_A[(g_i + b_A.size(0) * c_j) - 1]);
                    r1 = _mm_loadu_pd(&b_B[g_i - 1]);
                    _mm_storeu_pd(&b_B[g_i - 1], _mm_sub_pd(r1, _mm_mul_pd(r, _mm_set1_pd(wj))));
                }
                for (g_i = b_scalarLB; g_i <= b_m; g_i++) {
                    b_B[g_i - 1] = b_B[g_i - 1] - b_A[(g_i + b_A.size(0) * c_j) - 1] * wj;
                }
            }
        }
    }
    for (int d_i{0}; d_i < rankA; d_i++) {
        Y[jpvt[d_i] - 1] = b_B[d_i];
    }
    for (int d_j{rankA}; d_j >= 1; d_j--) {
        int i14;
        i14 = jpvt[d_j - 1];
        Y[i14 - 1] = Y[i14 - 1] / b_A[(d_j + b_A.size(0) * (d_j - 1)) - 1];
        for (int f_i{0}; f_i <= d_j - 2; f_i++) {
            Y[jpvt[f_i] - 1] =
                Y[jpvt[f_i] - 1] - Y[jpvt[d_j - 1] - 1] * b_A[f_i + b_A.size(0) * (d_j - 1)];
        }
    }
}

} // namespace internal
} // namespace coder
} // namespace ocn

//
// File trailer for qrsolve.cpp
//
// [EOF]
//
