//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_mtimes_helper.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:49:22
//

// Include Files
#include "eml_mtimes_helper.h"
#include "mtimes.h"
#include "norm.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1D
//                double a
//                const ::coder::array<double, 2U> &BasisVal
//                double b_a
//                const ::coder::array<double, 2U> &BasisValD
//                double c_a
//                double d_a
//                double e_a
//                double f_a
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r1D,
                        double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                        const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                        double e_a, double f_a)
{
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> h_a;
    ::coder::array<double, 2U> i_a;
    ::coder::array<double, 2U> j_a;
    double b_r1D[3];
    double d;
    int b_loop_ub;
    int b_stride_0_1;
    int b_stride_1_1;
    int c_loop_ub;
    int c_stride_0_1;
    int c_stride_1_1;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i;
    int i1;
    int i10;
    int i2;
    int i4;
    int i5;
    int i6;
    int i8;
    int i9;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    d = coder::b_norm(*(double(*)[3]) & r1D[0]);
    i = BasisVal.size(1);
    i1 = BasisValD.size(1);
    if (i1 == 1) {
        i2 = i;
    } else {
        i2 = i1;
    }
    g_a.set_size(1, i2);
    stride_0_1 = (i != 1);
    stride_1_1 = (i1 != 1);
    if (i1 == 1) {
        loop_ub = i;
    } else {
        loop_ub = i1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        g_a[i3] = a * BasisVal[BasisVal.size(0) * (i3 * stride_0_1)] +
                  b_a * BasisValD[BasisValD.size(0) * (i3 * stride_1_1)];
    }
    i4 = BasisVal.size(1);
    i5 = BasisValD.size(1);
    if (i5 == 1) {
        i6 = i4;
    } else {
        i6 = i5;
    }
    h_a.set_size(1, i6);
    b_stride_0_1 = (i4 != 1);
    b_stride_1_1 = (i5 != 1);
    if (i5 == 1) {
        b_loop_ub = i4;
    } else {
        b_loop_ub = i5;
    }
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        h_a[i7] = c_a * BasisVal[BasisVal.size(0) * (i7 * b_stride_0_1)] +
                  d_a * BasisValD[BasisValD.size(0) * (i7 * b_stride_1_1)];
    }
    i8 = BasisVal.size(1);
    i9 = BasisValD.size(1);
    if (i9 == 1) {
        i10 = i8;
    } else {
        i10 = i9;
    }
    i_a.set_size(1, i10);
    c_stride_0_1 = (i8 != 1);
    c_stride_1_1 = (i9 != 1);
    if (i9 == 1) {
        c_loop_ub = i8;
    } else {
        c_loop_ub = i9;
    }
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        i_a[i11] = e_a * BasisVal[BasisVal.size(0) * (i11 * c_stride_0_1)] +
                   f_a * BasisValD[BasisValD.size(0) * (i11 * c_stride_1_1)];
    }
    b_r1D[0] = r1D[0] / d;
    b_r1D[1] = r1D[1] / d;
    b_r1D[2] = r1D[2] / d;
    j_a.set_size(3, g_a.size(1));
    d_loop_ub = g_a.size(1);
    for (int i12{0}; i12 < d_loop_ub; i12++) {
        j_a[3 * i12] = g_a[i12];
    }
    e_loop_ub = h_a.size(1);
    for (int i13{0}; i13 < e_loop_ub; i13++) {
        j_a[3 * i13 + 1] = h_a[i13];
    }
    f_loop_ub = i_a.size(1);
    for (int i14{0}; i14 < f_loop_ub; i14++) {
        j_a[3 * i14 + 2] = i_a[i14];
    }
    coder::internal::blas::mtimes(b_r1D, j_a, r);
}

//
// Arguments    : ::coder::array<double, 2U> &Aeq
//                int i16
//                int i17
//                const double t_1[3]
//                double a
//                const ::coder::array<double, 2U> &BasisVal
//                double b_a
//                const ::coder::array<double, 2U> &BasisValD
//                double c_a
//                double d_a
//                double e_a
//                double f_a
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &Aeq, int i16, int i17, const double t_1[3],
                      double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a)
{
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> h_a;
    ::coder::array<double, 2U> i_a;
    ::coder::array<double, 2U> j_a;
    ::coder::array<double, 2U> r;
    int b_BasisVal;
    int b_BasisValD;
    int b_loop_ub;
    int b_stride_0_1;
    int b_stride_1_1;
    int c_BasisVal;
    int c_BasisValD;
    int c_loop_ub;
    int c_stride_0_1;
    int c_stride_1_1;
    int d_BasisVal;
    int d_BasisValD;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int i;
    int i1;
    int i10;
    int i2;
    int i4;
    int i5;
    int i6;
    int i8;
    int i9;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    b_BasisVal = BasisVal.size(0);
    b_BasisValD = BasisValD.size(0);
    c_BasisVal = BasisVal.size(0);
    c_BasisValD = BasisValD.size(0);
    d_BasisVal = BasisVal.size(0);
    d_BasisValD = BasisValD.size(0);
    i = BasisVal.size(1);
    i1 = BasisValD.size(1);
    if (i1 == 1) {
        i2 = i;
    } else {
        i2 = i1;
    }
    g_a.set_size(1, i2);
    stride_0_1 = (i != 1);
    stride_1_1 = (i1 != 1);
    if (i1 == 1) {
        loop_ub = i;
    } else {
        loop_ub = i1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        g_a[i3] = a * BasisVal[(b_BasisVal + BasisVal.size(0) * (i3 * stride_0_1)) - 1] +
                  b_a * BasisValD[(b_BasisValD + BasisValD.size(0) * (i3 * stride_1_1)) - 1];
    }
    i4 = BasisVal.size(1);
    i5 = BasisValD.size(1);
    if (i5 == 1) {
        i6 = i4;
    } else {
        i6 = i5;
    }
    h_a.set_size(1, i6);
    b_stride_0_1 = (i4 != 1);
    b_stride_1_1 = (i5 != 1);
    if (i5 == 1) {
        b_loop_ub = i4;
    } else {
        b_loop_ub = i5;
    }
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        h_a[i7] = c_a * BasisVal[(c_BasisVal + BasisVal.size(0) * (i7 * b_stride_0_1)) - 1] +
                  d_a * BasisValD[(c_BasisValD + BasisValD.size(0) * (i7 * b_stride_1_1)) - 1];
    }
    i8 = BasisVal.size(1);
    i9 = BasisValD.size(1);
    if (i9 == 1) {
        i10 = i8;
    } else {
        i10 = i9;
    }
    i_a.set_size(1, i10);
    c_stride_0_1 = (i8 != 1);
    c_stride_1_1 = (i9 != 1);
    if (i9 == 1) {
        c_loop_ub = i8;
    } else {
        c_loop_ub = i9;
    }
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        i_a[i11] = e_a * BasisVal[(d_BasisVal + BasisVal.size(0) * (i11 * c_stride_0_1)) - 1] +
                   f_a * BasisValD[(d_BasisValD + BasisValD.size(0) * (i11 * c_stride_1_1)) - 1];
    }
    j_a.set_size(3, g_a.size(1));
    d_loop_ub = g_a.size(1);
    for (int i12{0}; i12 < d_loop_ub; i12++) {
        j_a[3 * i12] = g_a[i12];
    }
    e_loop_ub = h_a.size(1);
    for (int i13{0}; i13 < e_loop_ub; i13++) {
        j_a[3 * i13 + 1] = h_a[i13];
    }
    f_loop_ub = i_a.size(1);
    for (int i14{0}; i14 < f_loop_ub; i14++) {
        j_a[3 * i14 + 2] = i_a[i14];
    }
    coder::internal::blas::mtimes(t_1, j_a, r);
    g_loop_ub = r.size(1);
    for (int i15{0}; i15 < g_loop_ub; i15++) {
        Aeq[(i16 + Aeq.size(0) * (i17 + i15)) - 1] = r[i15];
    }
}

//
// Arguments    : ::coder::array<double, 2U> &r
//                const double t_1[3]
//                double a
//                const ::coder::array<double, 2U> &BasisVal
//                double b_a
//                const ::coder::array<double, 2U> &BasisValD
//                double c_a
//                double d_a
//                double e_a
//                double f_a
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &r, const double t_1[3], double a,
                      const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a)
{
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> h_a;
    ::coder::array<double, 2U> i_a;
    ::coder::array<double, 2U> j_a;
    int b_loop_ub;
    int b_stride_0_1;
    int b_stride_1_1;
    int c_loop_ub;
    int c_stride_0_1;
    int c_stride_1_1;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i;
    int i1;
    int i10;
    int i2;
    int i4;
    int i5;
    int i6;
    int i8;
    int i9;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    i = BasisVal.size(1);
    i1 = BasisValD.size(1);
    if (i1 == 1) {
        i2 = i;
    } else {
        i2 = i1;
    }
    g_a.set_size(1, i2);
    stride_0_1 = (i != 1);
    stride_1_1 = (i1 != 1);
    if (i1 == 1) {
        loop_ub = i;
    } else {
        loop_ub = i1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        g_a[i3] = a * BasisVal[BasisVal.size(0) * (i3 * stride_0_1)] +
                  b_a * BasisValD[BasisValD.size(0) * (i3 * stride_1_1)];
    }
    i4 = BasisVal.size(1);
    i5 = BasisValD.size(1);
    if (i5 == 1) {
        i6 = i4;
    } else {
        i6 = i5;
    }
    h_a.set_size(1, i6);
    b_stride_0_1 = (i4 != 1);
    b_stride_1_1 = (i5 != 1);
    if (i5 == 1) {
        b_loop_ub = i4;
    } else {
        b_loop_ub = i5;
    }
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        h_a[i7] = c_a * BasisVal[BasisVal.size(0) * (i7 * b_stride_0_1)] +
                  d_a * BasisValD[BasisValD.size(0) * (i7 * b_stride_1_1)];
    }
    i8 = BasisVal.size(1);
    i9 = BasisValD.size(1);
    if (i9 == 1) {
        i10 = i8;
    } else {
        i10 = i9;
    }
    i_a.set_size(1, i10);
    c_stride_0_1 = (i8 != 1);
    c_stride_1_1 = (i9 != 1);
    if (i9 == 1) {
        c_loop_ub = i8;
    } else {
        c_loop_ub = i9;
    }
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        i_a[i11] = e_a * BasisVal[BasisVal.size(0) * (i11 * c_stride_0_1)] +
                   f_a * BasisValD[BasisValD.size(0) * (i11 * c_stride_1_1)];
    }
    j_a.set_size(3, g_a.size(1));
    d_loop_ub = g_a.size(1);
    for (int i12{0}; i12 < d_loop_ub; i12++) {
        j_a[3 * i12] = g_a[i12];
    }
    e_loop_ub = h_a.size(1);
    for (int i13{0}; i13 < e_loop_ub; i13++) {
        j_a[3 * i13 + 1] = h_a[i13];
    }
    f_loop_ub = i_a.size(1);
    for (int i14{0}; i14 < f_loop_ub; i14++) {
        j_a[3 * i14 + 2] = i_a[i14];
    }
    coder::internal::blas::mtimes(t_1, j_a, r);
}

//
// Arguments    : ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1D
//                double a
//                const ::coder::array<double, 2U> &BasisVal
//                double b_a
//                const ::coder::array<double, 2U> &BasisValD
//                double c_a
//                double d_a
//                double e_a
//                double f_a
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r1D,
                      double a, const ::coder::array<double, 2U> &BasisVal, double b_a,
                      const ::coder::array<double, 2U> &BasisValD, double c_a, double d_a,
                      double e_a, double f_a)
{
    ::coder::array<double, 2U> g_a;
    ::coder::array<double, 2U> h_a;
    ::coder::array<double, 2U> i_a;
    ::coder::array<double, 2U> j_a;
    double c_r1D[3];
    double d;
    int b_BasisVal;
    int b_BasisValD;
    int b_loop_ub;
    int b_r1D;
    int b_stride_0_1;
    int b_stride_1_1;
    int c_BasisVal;
    int c_BasisValD;
    int c_loop_ub;
    int c_stride_0_1;
    int c_stride_1_1;
    int d_BasisVal;
    int d_BasisValD;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i;
    int i1;
    int i10;
    int i2;
    int i4;
    int i5;
    int i6;
    int i8;
    int i9;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    b_r1D = r1D.size(1);
    d = coder::b_norm(*(double(*)[3]) & r1D[3 * (r1D.size(1) - 1)]);
    b_BasisVal = BasisVal.size(0);
    b_BasisValD = BasisValD.size(0);
    c_BasisVal = BasisVal.size(0);
    c_BasisValD = BasisValD.size(0);
    d_BasisVal = BasisVal.size(0);
    d_BasisValD = BasisValD.size(0);
    i = BasisVal.size(1);
    i1 = BasisValD.size(1);
    if (i1 == 1) {
        i2 = i;
    } else {
        i2 = i1;
    }
    g_a.set_size(1, i2);
    stride_0_1 = (i != 1);
    stride_1_1 = (i1 != 1);
    if (i1 == 1) {
        loop_ub = i;
    } else {
        loop_ub = i1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        g_a[i3] = a * BasisVal[(b_BasisVal + BasisVal.size(0) * (i3 * stride_0_1)) - 1] +
                  b_a * BasisValD[(b_BasisValD + BasisValD.size(0) * (i3 * stride_1_1)) - 1];
    }
    i4 = BasisVal.size(1);
    i5 = BasisValD.size(1);
    if (i5 == 1) {
        i6 = i4;
    } else {
        i6 = i5;
    }
    h_a.set_size(1, i6);
    b_stride_0_1 = (i4 != 1);
    b_stride_1_1 = (i5 != 1);
    if (i5 == 1) {
        b_loop_ub = i4;
    } else {
        b_loop_ub = i5;
    }
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        h_a[i7] = c_a * BasisVal[(c_BasisVal + BasisVal.size(0) * (i7 * b_stride_0_1)) - 1] +
                  d_a * BasisValD[(c_BasisValD + BasisValD.size(0) * (i7 * b_stride_1_1)) - 1];
    }
    i8 = BasisVal.size(1);
    i9 = BasisValD.size(1);
    if (i9 == 1) {
        i10 = i8;
    } else {
        i10 = i9;
    }
    i_a.set_size(1, i10);
    c_stride_0_1 = (i8 != 1);
    c_stride_1_1 = (i9 != 1);
    if (i9 == 1) {
        c_loop_ub = i8;
    } else {
        c_loop_ub = i9;
    }
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        i_a[i11] = e_a * BasisVal[(d_BasisVal + BasisVal.size(0) * (i11 * c_stride_0_1)) - 1] +
                   f_a * BasisValD[(d_BasisValD + BasisValD.size(0) * (i11 * c_stride_1_1)) - 1];
    }
    c_r1D[0] = r1D[3 * (b_r1D - 1)] / d;
    c_r1D[1] = r1D[3 * (b_r1D - 1) + 1] / d;
    c_r1D[2] = r1D[3 * (b_r1D - 1) + 2] / d;
    j_a.set_size(3, g_a.size(1));
    d_loop_ub = g_a.size(1);
    for (int i12{0}; i12 < d_loop_ub; i12++) {
        j_a[3 * i12] = g_a[i12];
    }
    e_loop_ub = h_a.size(1);
    for (int i13{0}; i13 < e_loop_ub; i13++) {
        j_a[3 * i13 + 1] = h_a[i13];
    }
    f_loop_ub = i_a.size(1);
    for (int i14{0}; i14 < f_loop_ub; i14++) {
        j_a[3 * i14 + 2] = i_a[i14];
    }
    coder::internal::blas::mtimes(c_r1D, j_a, r);
}

} // namespace ocn

//
// File trailer for eml_mtimes_helper.cpp
//
// [EOF]
//
