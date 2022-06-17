//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "xgeqp3.h"
#include "xnrm2.h"
#include "coder_array.h"
#include <cmath>

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
// Arguments    : ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &tau
//                ::coder::array<int, 2U> &jpvt
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(::coder::array<double, 2U> &A, ::coder::array<double, 1U> &tau,
            ::coder::array<int, 2U> &jpvt)
{
    ::coder::array<double, 1U> vn1;
    ::coder::array<double, 1U> vn2;
    ::coder::array<double, 1U> work;
    int m;
    int minmana;
    int n;
    int u0;
    int u1;
    int unnamed_idx_1;
    bool guard1{false};
    m = A.size(0);
    n = A.size(1);
    u0 = A.size(0);
    u1 = A.size(1);
    if (u0 <= u1) {
        minmana = u0;
    } else {
        minmana = u1;
    }
    tau.set_size(minmana);
    for (int i{0}; i < minmana; i++) {
        tau[i] = 0.0;
    }
    guard1 = false;
    if (A.size(0) == 0) {
        guard1 = true;
    } else {
        int b_u0;
        int b_u1;
        int y;
        b_u0 = A.size(0);
        b_u1 = A.size(1);
        if (b_u0 <= b_u1) {
            y = b_u0;
        } else {
            y = b_u1;
        }
        if (y < 1) {
            guard1 = true;
        } else {
            int b_A;
            int c_u0;
            int c_u1;
            int ma;
            int minmn;
            unnamed_idx_1 = A.size(1);
            jpvt.set_size(1, unnamed_idx_1);
            for (int i2{0}; i2 < unnamed_idx_1; i2++) {
                jpvt[i2] = 0;
            }
            for (int k{0}; k < n; k++) {
                jpvt[k] = k + 1;
            }
            tau.set_size(minmana);
            for (int i3{0}; i3 < minmana; i3++) {
                tau[i3] = 0.0;
            }
            ma = A.size(0);
            c_u0 = A.size(0);
            c_u1 = A.size(1);
            if (c_u0 <= c_u1) {
                minmn = c_u0;
            } else {
                minmn = c_u1;
            }
            b_A = A.size(1);
            work.set_size(b_A);
            for (int i4{0}; i4 < b_A; i4++) {
                work[i4] = 0.0;
            }
            b_A = A.size(1);
            vn1.set_size(b_A);
            for (int i5{0}; i5 < b_A; i5++) {
                vn1[i5] = 0.0;
            }
            b_A = A.size(1);
            vn2.set_size(b_A);
            for (int i6{0}; i6 < b_A; i6++) {
                vn2[i6] = 0.0;
            }
            for (int b_j{0}; b_j < n; b_j++) {
                double d;
                d = blas::xnrm2(m, A, b_j * ma + 1);
                vn1[b_j] = d;
                vn2[b_j] = d;
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
                        int i7;
                        int temp_tmp;
                        temp_tmp = ix + c_k;
                        temp = A[temp_tmp];
                        i7 = ii_tmp + c_k;
                        A[temp_tmp] = A[i7];
                        A[i7] = temp;
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
                    atmp = A[ii];
                    ix0 = ii + 2;
                    tau[b_i] = 0.0;
                    if (mmi > 0) {
                        double xnorm_tmp;
                        xnorm_tmp = blas::xnrm2(mmi - 1, A, ii + 2);
                        if (xnorm_tmp != 0.0) {
                            double beta1;
                            beta1 = rt_hypotd(A[ii], xnorm_tmp);
                            if (A[ii] >= 0.0) {
                                beta1 = -beta1;
                            }
                            if (std::abs(beta1) < 1.0020841800044864E-292) {
                                double b_a;
                                int i8;
                                int knt;
                                knt = -1;
                                i8 = ii + mmi;
                                do {
                                    knt++;
                                    for (int e_k{ix0}; e_k <= i8; e_k++) {
                                        A[e_k - 1] = 9.9792015476736E+291 * A[e_k - 1];
                                    }
                                    beta1 *= 9.9792015476736E+291;
                                    atmp *= 9.9792015476736E+291;
                                } while (!(std::abs(beta1) >= 1.0020841800044864E-292));
                                beta1 = rt_hypotd(atmp, blas::xnrm2(mmi - 1, A, ii + 2));
                                if (atmp >= 0.0) {
                                    beta1 = -beta1;
                                }
                                tau[b_i] = (beta1 - atmp) / beta1;
                                b_a = 1.0 / (atmp - beta1);
                                for (int f_k{ix0}; f_k <= i8; f_k++) {
                                    A[f_k - 1] = b_a * A[f_k - 1];
                                }
                                for (int g_k{0}; g_k <= knt; g_k++) {
                                    beta1 *= 1.0020841800044864E-292;
                                }
                                atmp = beta1;
                            } else {
                                double a;
                                int i9;
                                tau[b_i] = (beta1 - A[ii]) / beta1;
                                a = 1.0 / (A[ii] - beta1);
                                i9 = ii + mmi;
                                for (int d_k{ix0}; d_k <= i9; d_k++) {
                                    A[d_k - 1] = a * A[d_k - 1];
                                }
                                atmp = beta1;
                            }
                        }
                    }
                    A[ii] = atmp;
                } else {
                    tau[b_i] = 0.0;
                }
                if (b_i + 1 < n) {
                    double b_atmp;
                    int ic0;
                    int lastc;
                    int lastv;
                    b_atmp = A[ii];
                    A[ii] = 1.0;
                    ic0 = (ii + ma) + 1;
                    if (tau[b_i] != 0.0) {
                        int b_lastc;
                        int c_i;
                        bool exitg2;
                        lastv = mmi - 1;
                        c_i = (ii + mmi) - 1;
                        while ((lastv + 1 > 0) && (A[c_i] == 0.0)) {
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
                                    if (A[ia - 1] != 0.0) {
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
                            int i10;
                            for (int iy{0}; iy <= lastc; iy++) {
                                work[iy] = 0.0;
                            }
                            b_iy = 0;
                            i10 = ic0 + ma * lastc;
                            for (int iac{ic0}; ma < 0 ? iac >= i10 : iac <= i10; iac += ma) {
                                double c;
                                int i12;
                                c = 0.0;
                                i12 = iac + lastv;
                                for (int b_ia{iac}; b_ia <= i12; b_ia++) {
                                    c += A[b_ia - 1] * A[(ii + b_ia) - iac];
                                }
                                work[b_iy] = work[b_iy] + c;
                                b_iy++;
                            }
                        }
                        if (-tau[b_i] != 0.0) {
                            int jA;
                            jA = ic0;
                            for (int d_j{0}; d_j <= lastc; d_j++) {
                                if (work[d_j] != 0.0) {
                                    double b_temp;
                                    int i11;
                                    b_temp = work[d_j] * -tau[b_i];
                                    i11 = lastv + jA;
                                    for (int ijA{jA}; ijA <= i11; ijA++) {
                                        A[ijA - 1] = A[ijA - 1] + A[(ii + ijA) - jA] * b_temp;
                                    }
                                }
                                jA += ma;
                            }
                        }
                    }
                    A[ii] = b_atmp;
                }
                for (int c_j{ip1}; c_j <= n; c_j++) {
                    double d1;
                    int ij;
                    ij = b_i + (c_j - 1) * ma;
                    d1 = vn1[c_j - 1];
                    if (d1 != 0.0) {
                        double temp1;
                        double temp2;
                        temp1 = std::abs(A[ij]) / d1;
                        temp1 = 1.0 - temp1 * temp1;
                        if (temp1 < 0.0) {
                            temp1 = 0.0;
                        }
                        temp2 = d1 / vn2[c_j - 1];
                        temp2 = temp1 * (temp2 * temp2);
                        if (temp2 <= 1.4901161193847656E-8) {
                            if (b_i + 1 < m) {
                                double d2;
                                d2 = blas::xnrm2(mmi - 1, A, ij + 2);
                                vn1[c_j - 1] = d2;
                                vn2[c_j - 1] = d2;
                            } else {
                                vn1[c_j - 1] = 0.0;
                                vn2[c_j - 1] = 0.0;
                            }
                        } else {
                            vn1[c_j - 1] = d1 * std::sqrt(temp1);
                        }
                    }
                }
            }
        }
    }
    if (guard1) {
        unnamed_idx_1 = A.size(1);
        jpvt.set_size(1, unnamed_idx_1);
        for (int i1{0}; i1 < unnamed_idx_1; i1++) {
            jpvt[i1] = 0;
        }
        for (int j{0}; j < n; j++) {
            jpvt[j] = j + 1;
        }
    }
}

} // namespace lapack
} // namespace internal
} // namespace coder
} // namespace ocn

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
