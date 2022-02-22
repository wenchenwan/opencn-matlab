//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:18:27
//

// Include Files
#include "mldivide.h"
#include "qrsolve.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &B
//                ::coder::array<double, 1U> &Y
// Return Type  : void
//
namespace ocn {
namespace coder {
void mldivide(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U> &B,
              ::coder::array<double, 1U> &Y)
{
    ::coder::array<double, 2U> b_A;
    ::coder::array<int, 2U> ipiv;
    if (A.size(0) == A.size(1)) {
        int LDA;
        int b_LDA;
        int b_u0;
        int c_loop_ub;
        int c_u0;
        int i2;
        int ldap1;
        int loop_ub;
        int n;
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
        LDA = A.size(0);
        b_A.set_size(A.size(0), A.size(1));
        loop_ub = A.size(1);
        for (int i{0}; i < loop_ub; i++) {
            int b_loop_ub;
            b_loop_ub = A.size(0);
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                b_A[i1 + b_A.size(0) * i] = A[i1 + A.size(0) * i];
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
            i2 = c_u0;
        } else {
            i2 = n;
        }
        for (int j{0}; j < i2; j++) {
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
                    for (int c_k{2}; c_k <= mmj_tmp; c_k++) {
                        double s;
                        s = std::abs(b_A[(b + c_k) - 1]);
                        if (s > smax) {
                            a = c_k - 1;
                            smax = s;
                        }
                    }
                }
            }
            if (b_A[jj + a] != 0.0) {
                int i5;
                if (a != 0) {
                    int ipiv_tmp;
                    ipiv_tmp = j + a;
                    ipiv[j] = ipiv_tmp + 1;
                    for (int e_k{0}; e_k < n; e_k++) {
                        double b_temp;
                        int b_temp_tmp;
                        int i8;
                        int temp_tmp;
                        temp_tmp = e_k * LDA;
                        b_temp_tmp = j + temp_tmp;
                        b_temp = b_A[b_temp_tmp];
                        i8 = ipiv_tmp + temp_tmp;
                        b_A[b_temp_tmp] = b_A[i8];
                        b_A[i8] = b_temp;
                    }
                }
                i5 = jj + mmj_tmp;
                for (int c_i{jp1j}; c_i <= i5; c_i++) {
                    b_A[c_i - 1] = b_A[c_i - 1] / b_A[jj];
                }
            }
            jy = b + LDA;
            jA = jj + ldap1;
            for (int b_j{0}; b_j <= mmj_tmp - 2; b_j++) {
                double yjy;
                int yjy_tmp;
                yjy_tmp = jy + b_j * LDA;
                yjy = b_A[yjy_tmp];
                if (b_A[yjy_tmp] != 0.0) {
                    int i7;
                    int i9;
                    i7 = jA + 2;
                    i9 = mmj_tmp + jA;
                    for (int ijA{i7}; ijA <= i9; ijA++) {
                        b_A[ijA - 1] = b_A[ijA - 1] + b_A[((jj + ijA) - jA) - 1] * -yjy;
                    }
                }
                jA += LDA;
            }
        }
        Y.set_size(B.size(0));
        c_loop_ub = B.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            Y[i3] = B[i3];
        }
        b_LDA = b_A.size(0);
        for (int b_i{0}; b_i <= n - 2; b_i++) {
            int i4;
            i4 = ipiv[b_i];
            if (i4 != b_i + 1) {
                double temp;
                temp = Y[b_i];
                Y[b_i] = Y[i4 - 1];
                Y[i4 - 1] = temp;
            }
        }
        for (int b_k{0}; b_k < n; b_k++) {
            int kAcol;
            kAcol = b_LDA * b_k;
            if (Y[b_k] != 0.0) {
                int i6;
                i6 = b_k + 2;
                for (int d_i{i6}; d_i <= n; d_i++) {
                    Y[d_i - 1] = Y[d_i - 1] - Y[b_k] * b_A[(d_i + kAcol) - 1];
                }
            }
        }
        for (int d_k{n}; d_k >= 1; d_k--) {
            double d;
            int b_kAcol;
            b_kAcol = b_LDA * (d_k - 1);
            d = Y[d_k - 1];
            if (d != 0.0) {
                Y[d_k - 1] = d / b_A[(d_k + b_kAcol) - 1];
                for (int e_i{0}; e_i <= d_k - 2; e_i++) {
                    Y[e_i] = Y[e_i] - Y[d_k - 1] * b_A[e_i + b_kAcol];
                }
            }
        }
    } else {
        internal::qrsolve(A, B, Y);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for mldivide.cpp
//
// [EOF]
//
