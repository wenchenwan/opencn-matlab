//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

// Include Files
#include "mldivide.h"
#include "xgeqp3.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &Y
// Return Type  : void
//
namespace ocn {
namespace coder {
void mldivide(const ::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &Y)
{
    ::coder::array<double, 2U> b_A;
    ::coder::array<double, 2U> b_B;
    ::coder::array<double, 1U> tau;
    ::coder::array<int, 2U> ipiv;
    ::coder::array<int, 2U> jpvt;
    if ((A.size(0) == 0) || ((B.size(0) == 0) || (B.size(1) == 0))) {
        int loop_ub;
        Y.set_size(A.size(1), B.size(1));
        loop_ub = B.size(1);
        for (int i{0}; i < loop_ub; i++) {
            int c_loop_ub;
            c_loop_ub = A.size(1);
            for (int i2{0}; i2 < c_loop_ub; i2++) {
                Y[i2 + Y.size(0) * i] = 0.0;
            }
        }
    } else if (A.size(0) == A.size(1)) {
        int LDA;
        int LDB;
        int b_LDA;
        int b_u0;
        int c_u0;
        int e_loop_ub;
        int i10;
        int k_loop_ub;
        int ldap1;
        int m_loop_ub;
        int n;
        int nrhs;
        int u0;
        int u1;
        int y;
        int yk;
        u0 = A.size(0);
        u1 = A.size(1);
        if (u0 <= u1) {
            y = u0;
        } else {
            y = u1;
        }
        b_u0 = B.size(0);
        if (b_u0 <= y) {
            n = b_u0;
        } else {
            n = y;
        }
        nrhs = B.size(1) - 1;
        LDA = A.size(0);
        b_A.set_size(A.size(0), A.size(1));
        e_loop_ub = A.size(1);
        for (int i4{0}; i4 < e_loop_ub; i4++) {
            int g_loop_ub;
            g_loop_ub = A.size(0);
            for (int i6{0}; i6 < g_loop_ub; i6++) {
                b_A[i6 + b_A.size(0) * i4] = A[i6 + A.size(0) * i4];
            }
        }
        ipiv.set_size(1, n);
        ipiv[0] = 1;
        yk = 1;
        for (int k{2}; k <= n; k++) {
            yk++;
            ipiv[k - 1] = yk;
        }
        ldap1 = A.size(0);
        c_u0 = n - 1;
        if (c_u0 <= n) {
            i10 = c_u0;
        } else {
            i10 = n;
        }
        for (int j{0}; j < i10; j++) {
            int a;
            int b;
            int jA;
            int jj;
            int jp1j;
            int jy;
            int mmj_tmp;
            mmj_tmp = n - j;
            b = j * (LDA + 1);
            jj = j * (ldap1 + 1);
            jp1j = b + 2;
            if (mmj_tmp < 1) {
                a = -1;
            } else {
                a = 0;
                if (mmj_tmp > 1) {
                    double smax;
                    smax = std::abs(b_A[jj]);
                    for (int d_k{2}; d_k <= mmj_tmp; d_k++) {
                        double s;
                        s = std::abs(b_A[(b + d_k) - 1]);
                        if (s > smax) {
                            a = d_k - 1;
                            smax = s;
                        }
                    }
                }
            }
            if (b_A[jj + a] != 0.0) {
                int i16;
                if (a != 0) {
                    int ipiv_tmp;
                    ipiv_tmp = j + a;
                    ipiv[j] = ipiv_tmp + 1;
                    for (int f_k{0}; f_k < n; f_k++) {
                        double b_temp;
                        int b_temp_tmp;
                        int i22;
                        int temp_tmp;
                        temp_tmp = f_k * LDA;
                        b_temp_tmp = j + temp_tmp;
                        b_temp = b_A[b_temp_tmp];
                        i22 = ipiv_tmp + temp_tmp;
                        b_A[b_temp_tmp] = b_A[i22];
                        b_A[i22] = b_temp;
                    }
                }
                i16 = jj + mmj_tmp;
                for (int f_i{jp1j}; f_i <= i16; f_i++) {
                    b_A[f_i - 1] = b_A[f_i - 1] / b_A[jj];
                }
            }
            jy = b + LDA;
            jA = jj + ldap1;
            for (int g_j{0}; g_j <= mmj_tmp - 2; g_j++) {
                double yjy;
                int yjy_tmp;
                yjy_tmp = jy + g_j * LDA;
                yjy = b_A[yjy_tmp];
                if (b_A[yjy_tmp] != 0.0) {
                    int i21;
                    int i24;
                    i21 = jA + 2;
                    i24 = mmj_tmp + jA;
                    for (int ijA{i21}; ijA <= i24; ijA++) {
                        b_A[ijA - 1] = b_A[ijA - 1] + b_A[((jj + ijA) - jA) - 1] * -yjy;
                    }
                }
                jA += LDA;
            }
        }
        b_B.set_size(B.size(0), B.size(1));
        k_loop_ub = B.size(1);
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            int l_loop_ub;
            l_loop_ub = B.size(0);
            for (int i12{0}; i12 < l_loop_ub; i12++) {
                b_B[i12 + b_B.size(0) * i11] = B[i12 + B.size(0) * i11];
            }
        }
        b_LDA = b_A.size(0);
        LDB = B.size(0);
        for (int c_i{0}; c_i <= n - 2; c_i++) {
            int i14;
            i14 = ipiv[c_i];
            if (i14 != c_i + 1) {
                for (int f_j{0}; f_j <= nrhs; f_j++) {
                    double temp;
                    temp = b_B[c_i + b_B.size(0) * f_j];
                    b_B[c_i + b_B.size(0) * f_j] = b_B[(i14 + b_B.size(0) * f_j) - 1];
                    b_B[(i14 + b_B.size(0) * f_j) - 1] = temp;
                }
            }
        }
        for (int d_j{0}; d_j <= nrhs; d_j++) {
            int jBcol;
            jBcol = LDB * d_j;
            for (int e_k{0}; e_k < n; e_k++) {
                int i18;
                int kAcol;
                kAcol = b_LDA * e_k;
                i18 = e_k + jBcol;
                if (b_B[i18] != 0.0) {
                    int i20;
                    i20 = e_k + 2;
                    for (int h_i{i20}; h_i <= n; h_i++) {
                        int i25;
                        i25 = (h_i + jBcol) - 1;
                        b_B[i25] = b_B[i25] - b_B[i18] * b_A[(h_i + kAcol) - 1];
                    }
                }
            }
        }
        for (int e_j{0}; e_j <= nrhs; e_j++) {
            int b_jBcol;
            b_jBcol = LDB * e_j - 1;
            for (int g_k{n}; g_k >= 1; g_k--) {
                int b_kAcol;
                int i19;
                b_kAcol = b_LDA * (g_k - 1) - 1;
                i19 = g_k + b_jBcol;
                if (b_B[i19] != 0.0) {
                    b_B[i19] = b_B[i19] / b_A[g_k + b_kAcol];
                    for (int i_i{0}; i_i <= g_k - 2; i_i++) {
                        int i26;
                        i26 = (i_i + b_jBcol) + 1;
                        b_B[i26] = b_B[i26] - b_B[i19] * b_A[(i_i + b_kAcol) + 1];
                    }
                }
            }
        }
        Y.set_size(b_B.size(0), b_B.size(1));
        m_loop_ub = b_B.size(1);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            int n_loop_ub;
            n_loop_ub = b_B.size(0);
            for (int i23{0}; i23 < n_loop_ub; i23++) {
                Y[i23 + Y.size(0) * i17] = b_B[i23 + b_B.size(0) * i17];
            }
        }
    } else {
        int b_loop_ub;
        int b_nb;
        int b_u1;
        int d_u0;
        int f_loop_ub;
        int i_loop_ub;
        int m;
        int maxmn;
        int minmn;
        int mn;
        int nb;
        int rankA;
        b_A.set_size(A.size(0), A.size(1));
        b_loop_ub = A.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            int d_loop_ub;
            d_loop_ub = A.size(0);
            for (int i3{0}; i3 < d_loop_ub; i3++) {
                b_A[i3 + b_A.size(0) * i1] = A[i3 + A.size(0) * i1];
            }
        }
        internal::lapack::xgeqp3(b_A, tau, jpvt);
        rankA = 0;
        if (b_A.size(0) < b_A.size(1)) {
            minmn = b_A.size(0);
            maxmn = b_A.size(1);
        } else {
            minmn = b_A.size(1);
            maxmn = b_A.size(0);
        }
        if (minmn > 0) {
            double tol;
            tol = std::fmin(1.4901161193847656E-8,
                            2.2204460492503131E-15 * static_cast<double>(maxmn)) *
                  std::abs(b_A[0]);
            while ((rankA < minmn) && (std::abs(b_A[rankA + b_A.size(0) * rankA]) > tol)) {
                rankA++;
            }
        }
        b_B.set_size(B.size(0), B.size(1));
        f_loop_ub = B.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            int h_loop_ub;
            h_loop_ub = B.size(0);
            for (int i7{0}; i7 < h_loop_ub; i7++) {
                b_B[i7 + b_B.size(0) * i5] = B[i7 + B.size(0) * i5];
            }
        }
        nb = B.size(1);
        Y.set_size(b_A.size(1), B.size(1));
        i_loop_ub = B.size(1);
        for (int i8{0}; i8 < i_loop_ub; i8++) {
            int j_loop_ub;
            j_loop_ub = b_A.size(1);
            for (int i9{0}; i9 < j_loop_ub; i9++) {
                Y[i9 + Y.size(0) * i8] = 0.0;
            }
        }
        m = b_A.size(0);
        b_nb = B.size(1);
        d_u0 = b_A.size(0);
        b_u1 = b_A.size(1);
        if (d_u0 <= b_u1) {
            mn = d_u0;
        } else {
            mn = b_u1;
        }
        for (int b_j{0}; b_j < mn; b_j++) {
            if (tau[b_j] != 0.0) {
                for (int c_k{0}; c_k < b_nb; c_k++) {
                    double wj;
                    int i13;
                    wj = b_B[b_j + b_B.size(0) * c_k];
                    i13 = b_j + 2;
                    for (int d_i{i13}; d_i <= m; d_i++) {
                        wj +=
                            b_A[(d_i + b_A.size(0) * b_j) - 1] * b_B[(d_i + b_B.size(0) * c_k) - 1];
                    }
                    wj *= tau[b_j];
                    if (wj != 0.0) {
                        b_B[b_j + b_B.size(0) * c_k] = b_B[b_j + b_B.size(0) * c_k] - wj;
                        for (int g_i{i13}; g_i <= m; g_i++) {
                            b_B[(g_i + b_B.size(0) * c_k) - 1] =
                                b_B[(g_i + b_B.size(0) * c_k) - 1] -
                                b_A[(g_i + b_A.size(0) * b_j) - 1] * wj;
                        }
                    }
                }
            }
        }
        for (int b_k{0}; b_k < nb; b_k++) {
            for (int b_i{0}; b_i < rankA; b_i++) {
                Y[(jpvt[b_i] + Y.size(0) * b_k) - 1] = b_B[b_i + b_B.size(0) * b_k];
            }
            for (int c_j{rankA}; c_j >= 1; c_j--) {
                int i15;
                i15 = jpvt[c_j - 1];
                Y[(i15 + Y.size(0) * b_k) - 1] =
                    Y[(i15 + Y.size(0) * b_k) - 1] / b_A[(c_j + b_A.size(0) * (c_j - 1)) - 1];
                for (int e_i{0}; e_i <= c_j - 2; e_i++) {
                    Y[(jpvt[e_i] + Y.size(0) * b_k) - 1] =
                        Y[(jpvt[e_i] + Y.size(0) * b_k) - 1] -
                        Y[(jpvt[c_j - 1] + Y.size(0) * b_k) - 1] *
                            b_A[e_i + b_A.size(0) * (c_j - 1)];
                }
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for mldivide.cpp
//
// [EOF]
//
